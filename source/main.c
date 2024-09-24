#include "include/18B20.h"
#include "include/delay.h"
#include "include/ComCDT.h"
#include "include/IKeyEvent.h"
#include "include/Relay.h"
#include "include/buzzer.h"

#define TEMPERATURE_REFRESH_CYCLE 500  
#define BUZZER_WARNING_DURATION 3000   
#define TIMER0_RELOAD_VALUE 2000       
#define LOWER_TEMP_LIMIT 25            
#define UPPER_TEMP_LIMIT 30            
#define TIME_DISPLAY_VALUE 60          
#define TEMP_CONVERSION_FACTOR 0.0625  

unsigned int nReadTemperatureCycle = TEMPERATURE_REFRESH_CYCLE; // 温度读取循环周期
bit bReadTemperatureIndicator = 0; // 温度读取指示器
bit TEMPERATURE_OR_TIME = 1; // 指示当前是温度还是时间控制
bit IS_THE_RELAY_RUNNING = 0; // 继电器是否正在运行
bit buzzerIsOn = 0; // 蜂鸣器是否开启
unsigned int buzzerCountdown = 0; // 蜂鸣器倒计时
unsigned char integerPart = 0, decimalPart = 0; // 温度的整数部分和小数部分
unsigned int LOWER_LIMIT_TEMPERATURE = LOWER_TEMP_LIMIT; // 温度下限
unsigned int UPPER_LIMIT_TEMPERATURE = UPPER_TEMP_LIMIT; // 温度上限
float temperature; // 当前温度

// 初始化定时器0的函数
void initializeTimer0();

// 更新温度显示的函数
void updateTemperatureDisplay();

// 计算当前温度的函数
float calculateTemperature();

// 根据温度控制继电器的函数
void controlRelayBasedOnTemperature();

// 处理蜂鸣器的函数
void handleBuzzer();

void initializeTimer0() {
    // 设置定时器0为模式1（16位定时器/计数器模式）
    TMOD |= 0x01;  

    // 开启全局中断
    EA = 1;        

    // 开启定时器0中断
    ET0 = 1;       

    // 启动定时器0
    TR0 = 1;       
}

void timer0InterruptHandling(void) interrupt 1 {
    // 初始化定时器0的初值
    static unsigned int nReinstallTimes = 0;
    TH0 = (65536 - TIMER0_RELOAD_VALUE) / 256;
    TL0 = (65536 - TIMER0_RELOAD_VALUE) % 256;

    // 重装计数器
    nReinstallTimes++;
    
    // 根据条件显示温度或时间
    if (TEMPERATURE_OR_TIME) {
        displayTemperature(integerPart, decimalPart);
    } else {
        displayTime(TIME_DISPLAY_VALUE);
    }

    // 达到一定重装次数后，重置并设置读温度标志
    if (nReinstallTimes >= nReadTemperatureCycle / 2) {
        nReinstallTimes = 0;
        bReadTemperatureIndicator = 1;
    }

    // 处理蜂鸣器逻辑
    handleBuzzer();
}

void handleBuzzer() {
    // 如果蜂鸣器正在响且倒计时大于0
    if (buzzerIsOn && buzzerCountdown > 0) {
        // 倒计时减一
        buzzerCountdown--;
        // 如果倒计时为0
        if (buzzerCountdown == 0) {
            // 关闭蜂鸣器
            buzzerOff();
            // 设置蜂鸣器状态为关闭
            buzzerIsOn = 0;
        }
    }
}

void initializeSystem() {
    // 初始化定时器0
    initializeTimer0();
}

void updateTemperatureDisplay() {
    // 如果温度读取指示标志为真
    if (bReadTemperatureIndicator) {
        // 将温度读取指示标志置为假
        bReadTemperatureIndicator = 0;
        // 计算温度值
        temperature = calculateTemperature();
        // 将温度值转换为整数部分
        integerPart = (unsigned int)temperature;
        // 将温度值的小数部分乘以100并转换为整数部分
        decimalPart = (unsigned int)((temperature - integerPart) * 100);
    }
}

float calculateTemperature() {
    // 调用ReadTemperature函数获取温度值
    // 将温度值乘以转换因子TEMP_CONVERSION_FACTOR
    return ReadTemperature() * TEMP_CONVERSION_FACTOR;
}

void controlRelayBasedOnTemperature() {
    // 判断继电器是否正在运行
    if (IS_THE_RELAY_RUNNING) {
        // 如果温度低于下限温度
        if (temperature < LOWER_LIMIT_TEMPERATURE) {
            // 关闭继电器
            relayClosed();
            // 发出蜂鸣器警告，持续时间为BUZZER_WARNING_DURATION
            buzzerWarning(BUZZER_WARNING_DURATION);
        // 如果温度高于上限温度
        } else if (temperature > UPPER_LIMIT_TEMPERATURE) {
            // 打开继电器
            relayOpened();
            // 发出蜂鸣器警告，持续时间为BUZZER_WARNING_DURATION
            buzzerWarning(BUZZER_WARNING_DURATION);
        }
    // 如果继电器未运行
    } else {
        // 关闭继电器
        relayClosed();
    }
}

void main(void) {
    // 初始化系统
    initializeSystem();

    // 无限循环
    while (1) {
        // 检查按钮状态
        checkButtons();

        // 更新温度显示
        updateTemperatureDisplay();

        // 根据温度控制继电器
        controlRelayBasedOnTemperature();
    }
}
