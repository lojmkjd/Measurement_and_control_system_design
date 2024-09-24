/* buzzer.c */

#include "include/buzzer.h"
#include "reg52.h"
#include "include/delay.h"

void setBuzzerState(unsigned char state)
{
    buzzerPin = state; // 设置蜂鸣器状态，0 为开，1 为关
}

void buzzerOn(void)
{
    setBuzzerState(0); // 打开蜂鸣器
}

void buzzerOff(void)
{
    setBuzzerState(1); // 关闭蜂鸣器
}

void buzzerWarning(unsigned int duration)
{
    if (!buzzerIsOn)
    {                               // 只有在蜂鸣器未开启时才执行
        buzzerOn();                 // 打开蜂鸣器
        buzzerCountdown = duration; // 设置倒计时
        buzzerIsOn = 1;             // 标记蜂鸣器处于响铃状态
    }
}
