/* buzzer.c */
#include "include/buzzer.h"
#include "reg52.h"
#include "include/delay.h"

/**
 * @brief 设置蜂鸣器的状态
 * @param state 蜂鸣器的状态，0 为关，1 为开
 */
void setBuzzerState(unsigned char state)
{
    buzzerPin = state; // 设置蜂鸣器引脚状态
}

/**
 * @brief 打开蜂鸣器
 */
void buzzerOn(void)
{
    setBuzzerState(1); // 打开蜂鸣器
}

/**
 * @brief 关闭蜂鸣器
 */
void buzzerOff(void)
{
    setBuzzerState(0); // 关闭蜂鸣器
}
