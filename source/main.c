/*main.c*/
#include "include/18B20.h"
#include "include/ComCDT.h"
#include "include/Relay.h"
#include "include/buzzer.h"
#include "include/pid_controller.h"
#include "include/IKeyEvent.h"

#define TIMER_0_RELOADS_VALUE 1000    // 定时器0重装值，为每1ms
#define TEMP_CONVERSION_FACTOR 0.0625 // 温度转换系数
#define LOWER_TEMP_LIMIT 25            
#define UPPER_TEMP_LIMIT 30
#define TARGET_TEMPERATURE 28 // 目标温度

typedef struct
{
    void (*taskFunction)(void);
    unsigned int period;
    unsigned int nextExecution;
} Task;

#define MAX_TASKS 5
Task tasks[MAX_TASKS];
unsigned char taskCount = 0;

// 调度器函数声明
void initializeSystem();
void addTask(void (*taskFunction)(void), unsigned int period);
void scheduler();

// 任务函数声明
void taskTemperatureUpdate();
void taskControlRelay();

// 定时器函数声明
void initializeTimer0();
void timer0InterruptHandling(void);

// 全局变量声明
unsigned int currentTime = 0;                   // 当前时间，为中断周期的整数倍，时间单位为1ms
unsigned char temperature = 0;                  // 温度值
unsigned char integerPart = 0, decimalPart = 0; // 温度的整数部分和小数部分
unsigned char setpoint=TARGET_TEMPERATURE; // 目标温度
unsigned char integral=0;  // 积分值
unsigned char previous_error=0; // 上一个误差
bit displayTemperatureOrTime=1;

void main(void)
{
    // 初始化DS19B20模块
    Init_DS18B20();

    // 初始化调度器
    initializeSystem();

    // 无限循环
    while (1)
    {
        // 扫描键盘事件
        checkButtons();

        // 调用调度器
        scheduler();
    }
}

// 初始化系统函数
void initializeSystem()
{
    // 初始化定时器0
    initializeTimer0();
    // 添加任务到调度器
    addTask(taskTemperatureUpdate, 8); // 每8s执行一次温度显示更新
    addTask(taskControlRelay, 1000);   // 每1s时间单位执行一次继电器控制
}

// 初始化定时器
void initializeTimer0()
{
    // 设置定时器0为模式1（16位定时器/计数器模式）
    TMOD &= 0xF0; // 清除定时器 0 的模式位
    TMOD |= 0x01; // 设置定时器 0 为模式 1（16 位定时器）

    // 初始化定时器0的初值
    TH0 = (65536 - TIMER_0_RELOADS_VALUE) / 256;
    TL0 = (65536 - TIMER_0_RELOADS_VALUE) % 256;

    // 开启全局中断
    EA = 1;
    // 开启定时器0中断
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

    // 每次溢出都使用当前时间加1
    currentTime++;
}

// 添加任务的函数
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

// 温度-时间显示更新
void taskTemperatureUpdate()
{
    // 读取温度
    temperature = ReadTemperature() * TEMP_CONVERSION_FACTOR;

    // 计算温度的整数部分和小数部分
    integerPart = (unsigned int)temperature;
    decimalPart = (unsigned int)((temperature - integerPart + 0.5) * 100);

    if(displayTemperatureOrTime==1){
        // 调用晶体管显示
    displayTemperature(integerPart, decimalPart);
    }else{
        // 调用数码管显示
    displayTime(60);
    }
}

void taskControlRelay(){
    // 如果温度低于下限温度
    if (temperature < LOWER_TEMP_LIMIT) {
        // 打开继电器
        relayOpened();
        // 发出蜂鸣器警告
        buzzerOn();
    }
    // 如果温度高于上限温度
    else if (temperature > UPPER_TEMP_LIMIT) {
        // 关闭继电器
        relayClosed();
        // 发出蜂鸣器警告
        buzzerOn();
    }
    // 如果温度在上下限之间
    else {
        pIDControl();
        buzzerOff();
    }
}

// 调度器函数
void scheduler() {
		unsigned char i;
    for (i = 0; i < taskCount; i++) {
        if (currentTime >= tasks[i].nextExecution) {
            tasks[i].taskFunction(); // 调用任务函数
            tasks[i].nextExecution = currentTime + tasks[i].period; // 更新下次执行时间
        }
    }
}