// my_relay_control.h

#ifndef _MY_RELAY_CONTROL_H_
#define _MY_RELAY_CONTROL_H_

#include "reg52.h"

// 定义按键引脚口
sbit switchButton = P1 ^ 2; // 定义温度-时间切换显示按键
sbit startButton = P1 ^ 3;  // 定义继电器启动按键

// 定义全局变量
extern bit TEMPERATURE_OR_TIME;  // 定义显示温度还是时间
extern bit IS_THE_RELAY_RUNNING; // 定义继电器是否启动

// 定义函数声明
void checkButtons(void);

#endif // _MY_RELAY_CONTROL_H_
