/* main.c */
#include "include/18B20.h"
#include "include/ComCDT.h"
#include "include/Relay.h"
#include "include/buzzer.h"
#include "include/pid_controller.h"
#include "include/IKeyEvent.h"
#include "include/serial.h"
#include <intrins.h>
#include <stdio.h>
#include "include/delay.h"

// 定义常量
#define TIMER_0_RELOADS_VALUE 1000    // 定时器0重装值，为每1ms
#define TEMP_CONVERSION_FACTOR 0.0625 // 温度转换系数
#define LOWER_TEMP_LIMIT 28           // 温度下限
#define UPPER_TEMP_LIMIT 30           // 温度上限
#define TARGET_TEMPERATURE 28         // 目标温度
#define RELAY_HYSTERESIS 2            // 滞后带宽，单位°C

// 任务调度器的任务结构体
typedef struct
{
    void (*taskFunction)(void); // 任务函数指针
    unsigned int period;        // 任务执行的周期
    unsigned int nextExecution; // 任务下次执行的时间
} Task;

#define MAX_TASKS 5
Task tasks[MAX_TASKS];      // 任务列表
unsigned int taskCount = 0; // 任务数量

// 调度器函数声明
void initializeSystem();
void addTask(void (*taskFunction)(void), unsigned int period);
void scheduler();

// 任务函数声明
void taskTemperatureUpdate();
void taskControlRelay();
void taskSendTemperature();
void taskControlBuzzer();

// 定时器函数声明
void initializeTimer0();
void timer0InterruptHandling(void);

// 全局变量声明
unsigned char currentTime = 0;                  // 当前时间，以1ms为单位
float temperature = 0.0;                        // 当前温度
unsigned char integerPart = 0, decimalPart = 0; // 温度的整数部分和小数部分
unsigned char setpoint = TARGET_TEMPERATURE;    // 目标温度
unsigned char integral = 0;                     // PID积分项
unsigned char previous_error = 0;               // 上一个误差
bit displayTemperatureOrTime = 1;               // 控制温度/时间显示切换

void main(void)
{
    // 初始化DS18B20温度传感器模块
    Init_DS18B20();

    // 初始化串口
    initSerial(); // 初始化串口函数

    // 初始化调度器和任务
    initializeSystem();

    // 无限循环
    while (1)
    {
        // 调用调度器处理任务
        scheduler();
        checkButtons();
    }
}

// 初始化系统
void initializeSystem()
{
    // 初始化定时器0
    initializeTimer0();

    // 添加任务到调度器
    addTask(taskTemperatureUpdate, 10); // 每10毫秒更新一次温度
    addTask(taskControlRelay, 1000);    // 每1秒控制一次继电器
    addTask(taskControlBuzzer, 2);      // 每1秒发送一次温度信息
    // addTask(taskSendTemperature, 500);  // 每0.5秒发送一次温度信息
}

// 初始化定时器0
void initializeTimer0()
{
    // 设置定时器0为模式1（16位定时器/计数器模式）
    TMOD &= 0xF0; // 清除定时器0的模式位
    TMOD |= 0x01; // 设置定时器0为模式1（16位定时器）

    // 初始化定时器0的初值
    TH0 = (65536 - TIMER_0_RELOADS_VALUE) / 256;
    TL0 = (65536 - TIMER_0_RELOADS_VALUE) % 256;

    // 开启全局中断和定时器0中断
    EA = 1;
    ET0 = 1;

    // 启动定时器0
    TR0 = 1;
}

// 定时器0中断处理函数
void timer0InterruptHandling(void) interrupt 1
{
    // 重新装载定时器0的初值
    TH0 = (65536 - TIMER_0_RELOADS_VALUE) / 256;
    TL0 = (65536 - TIMER_0_RELOADS_VALUE) % 256;

    // 更新当前时间，每次中断表示1ms
    currentTime++;
}

// 添加任务
void addTask(void (*taskFunction)(void), unsigned int period)
{
    if (taskCount < MAX_TASKS)
    {
        tasks[taskCount].taskFunction = taskFunction;
        tasks[taskCount].period = period;
        tasks[taskCount].nextExecution = currentTime + period;
        taskCount++;
    }
}

// 温度更新任务
void taskTemperatureUpdate()
{
    // 读取温度并转换为实际温度值
    temperature = ReadTemperature() * TEMP_CONVERSION_FACTOR;

    // 计算温度的整数部分和小数部分
    integerPart = (int)temperature;
    decimalPart = (int)((temperature - integerPart) * 100);

    // 根据显示模式，显示温度或时间
    if (displayTemperatureOrTime)
    {
        displayTemperature(integerPart, decimalPart);
    }
    else
    {
        displayTime(60); // 示例：显示60分钟
    }
}

// 继电器控制任务
void taskControlRelay()
{
    // 控制逻辑：低于下限温度-滞后带宽打开继电器，超过上限温度+滞后带宽关闭继电器
    if (temperature < (LOWER_TEMP_LIMIT - RELAY_HYSTERESIS))
    {
        relayOpened();
        DelayUs2x(25);
    }
    else if (temperature > (UPPER_TEMP_LIMIT + RELAY_HYSTERESIS))
    {
        relayClosed();
        DelayUs2x(25);
    }
    else
    {
        // 当温度在上下限之间时使用PID控制
        pIDControl();
        DelayUs2x(25);
    }
}

void taskControlBuzzer()
{
    // 根据温度判断蜂鸣器状态
    if (temperature < LOWER_TEMP_LIMIT)
    {
        buzzerOn(); // 温度低于下限时，打开蜂鸣器
        DelayUs2x(25);
    }
    else if (temperature > UPPER_TEMP_LIMIT)
    {
        buzzerOff(); // 温度高于上限时，关闭蜂鸣器
        DelayUs2x(25);
    }
    else
    {
        // 在温度正常范围内，可以选择关闭蜂鸣器或保持当前状态
        buzzerOff(); // 可选：在正常范围内关闭蜂鸣器
        DelayUs2x(25);
    }
}

// 调度器：检查并执行每个任务
void scheduler()
{
    unsigned char i;
    for (i = 0; i < taskCount; i++)
    {
        if (currentTime >= tasks[i].nextExecution)
        {
            tasks[i].taskFunction();                                // 执行任务
            tasks[i].nextExecution = currentTime + tasks[i].period; // 更新下次执行时间
        }
    }
}

// 发送温度任务
void taskSendTemperature()
{
    unsigned char buffer[10];
    sprintf(buffer, "Temperature: %d.%d C", integerPart, decimalPart);
    sendSerial(buffer); // 发送温度信息
    DelayUs2x(25);
}