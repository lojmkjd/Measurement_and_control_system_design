#ifndef BUZZER_H
#define BUZZER_H

#include "reg52.h"

// 引脚定义:
// 定义蜂鸣器连接的引脚（P1.0）
sbit buzzerPin = P1^0; 

// 函数声明

/**
 * @brief 打开蜂鸣器
 */
void buzzerOn(void);

/**
 * @brief 关闭蜂鸣器
 */
void buzzerOff(void);

#endif // BUZZER_H
