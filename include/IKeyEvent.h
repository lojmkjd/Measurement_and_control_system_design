// my_relay_control.h

#ifndef _MY_RELAY_CONTROL_H_
#define _MY_RELAY_CONTROL_H_

#include "reg52.h"

// 定义按键引脚口
sbit switchButton = P1 ^ 2; // 定义温度-时间切换显示按键

// 定义全局变量
extern bit displayTemperatureOrTime;  // 定义显示温度还是时间

// 定义函数声明
void checkButtons(void);
void checkButtonState(bit button);

#endif // _MY_RELAY_CONTROL_H_
