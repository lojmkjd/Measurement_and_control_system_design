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
    setBuzzerState(1); // 打开蜂鸣器
}

void buzzerOff(void)
{
    setBuzzerState(0); // 关闭蜂鸣器
}

