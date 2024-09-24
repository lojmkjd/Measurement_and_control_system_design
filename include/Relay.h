/* Relay.h */

#ifndef RELAY_H
#define RELAY_H

#include "reg52.h"

// 定义继电器控制引脚
sbit relayPin = P2^0; // 继电器控制引脚定义

// 函数声明
/**
 * @brief 关闭继电器
 */
void relayClosed(void);

/**
 * @brief 打开继电器
 */
void relayOpened(void);

#endif // RELAY_H
