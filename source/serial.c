#include "reg52.h"
#include "include/serial.h"

#define BAUD_RATE 9600
#define FOSC 11059200 // 假设晶振频率为 11.0592MHz
#define TH1_VALUE (256 - (FOSC / (32 * BAUD_RATE)))

void initSerial(void) {
    SCON = 0x50; // 设置串口工作方式1
    TMOD &= 0x0F; // 清除定时器1的高四位
    TMOD |= 0x20; // 设置定时器1为模式2（8位自动重装载）

    TH1 = TH1_VALUE; // 设置波特率
    TL1 = TH1_VALUE; // 设置定时器初值
    TR1 = 1; // 启动定时器1
    EA = 1; // 允许全局中断
    ES = 1; // 允许串口中断
}

void sendSerial(char *data) {
    while (*data) {
        SBUF = *data++; // 发送数据
        while (!TI); // 等待发送完成
        TI = 0; // 清除发送中断标志
    }
}
