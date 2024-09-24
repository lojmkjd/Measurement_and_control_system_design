/* Relay.h */

#ifndef RELAY_H
#define RELAY_H

#include "reg52.h"

// 声明继电器引脚
sbit relayPin=P2^0;

// 声明函数
void relayClosed(void);
void relayOpened(void);

#endif // RELAY_H