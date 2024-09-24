/*Relay.c*/ 
#include "reg52.h"

// 继电器引脚定义
sbit relayPin=P1^4;

void relayClosed()
{
    relayPin=1; // 关闭继电器
}

void relayOpened()
{
    relayPin=0; // 打开继电器
}
