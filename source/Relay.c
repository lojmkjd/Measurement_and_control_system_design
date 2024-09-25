/* Relay.c */
#include "reg52.h"
#include <intrins.h>
#include "include/delay.h"

// 继电器引脚定义
sbit relayPin = P1^4; // 定义继电器控制引脚

/**
 * @brief 关闭继电器
 * 
 * 将继电器引脚设置为高电平（关闭状态）
 */
void relayClosed() {
    relayPin = 1; // 关闭继电器
    DelayUs2x(25); // 延时25us
}

/**
 * @brief 打开继电器
 * 
 * 将继电器引脚设置为低电平（打开状态）
 */
void relayOpened() {
    relayPin = 0; // 打开继电器
    DelayUs2x(25); // 延时25us
}
