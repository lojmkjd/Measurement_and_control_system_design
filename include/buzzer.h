/* buzzer.h */

#ifndef BUZZER_H
#define BUZZER_H

#include "reg52.h"

//引脚定义:
sbit buzzerPin=P1^0;	//定义蜂鸣器

extern bit buzzerIsOn; // 记录蜂鸣器是否在响
extern unsigned int buzzerCountdown; // 记录蜂鸣器的倒计时


// 蜂鸣器控制函数声明
void buzzerOn(void);
void buzzerOff(void);
void buzzerWarning(unsigned int duration); // 持续时间以毫秒为单位

#endif // BUZZER_H