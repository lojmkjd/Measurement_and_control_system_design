// my_relay_control.h

#ifndef _MY_RELAY_CONTROL_H_
#define _MY_RELAY_CONTROL_H_

#include "reg52.h"

// 定义按键引脚
sbit switchButton = P1 ^ 2; // 温度-时间切换显示按键引脚

// 定义全局变量
extern bit displayTemperatureOrTime;  // 控制当前显示的内容（温度或时间）

// 函数声明
/**
 * @brief 检查所有按钮的状态
 */
void checkButtons(void);

/**
 * @brief 检查单个按钮的状态并处理防抖
 * 
 * @param button 按钮的当前状态（0 表示按下，1 表示释放）
 */
void checkButtonState(bit button);

#endif // _MY_RELAY_CONTROL_H_
