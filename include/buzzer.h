/* buzzer.h */

#ifndef BUZZER_H
#define BUZZER_H

#include "reg52.h"

//引脚定义:
sbit buzzerPin=P1^0;	//定义蜂鸣器

// 蜂鸣器控制函数声明
void buzzerOn(void);
void buzzerOff(void);

#endif // BUZZER_H