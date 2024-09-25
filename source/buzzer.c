/* buzzer.c */
#include "include/buzzer.h"
#include "reg52.h"
#include "include/delay.h"
#include <intrins.h>

/**
 * @brief 打开蜂鸣器
 */
void buzzerOn(void)
{
    buzzerPin = 1; // 打开蜂鸣器
    DelayUs2x(25);
}

/**
 * @brief 关闭蜂鸣器
 */
void buzzerOff(void)
{
    buzzerPin = 0; // 关闭蜂鸣器
    DelayUs2x(25);
}
