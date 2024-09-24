/* 18B20.c */
#include "include/delay.h"
#include "include/18B20.h"

// 初始化 DS18B20，返回 1 表示初始化成功，0 表示失败
bit Init_DS18B20(void)
{
    bit dat = 0;

    DQ = 1;                // DQ 置为高电平
    DelayUs2x(5);          // 延时 5 微秒
    DQ = 0;                // DQ 置为低电平
    DelayUs2x(400);        // 延时 400 微秒
    DQ = 1;                // DQ 置为高电平
    DelayUs2x(50);         // 延时 50 微秒
    dat = DQ;              // 读取 DQ 状态
    DelayUs2x(25);         // 延时 25 微秒

    return dat;
}

// 读取一个字节
unsigned char ReadOneChar(void)
{
    unsigned char i, dat = 0;

    for (i = 0; i < 8; i++)
    {
        DQ = 0;            // 将 DQ 置为低电平开始传输
        dat >>= 1;         // 数据右移一位
        DQ = 1;            // DQ 置为高电平准备读取
        if (DQ)            // 若 DQ 为高电平，将最高位设为 1
            dat |= 0x80;
        DelayUs2x(25);     // 延时 25 微秒
    }
    return dat;            // 返回读取到的字节
}

// 写入一个字节
void WriteOneChar(unsigned char dat)
{
    unsigned char i;

    for (i = 0; i < 8; i++)
    {
        DQ = 0;            // 将 DQ 置为低电平开始写入
        DQ = dat & 0x01;   // 写入最低位
        DelayUs2x(25);     // 延时 25 微秒
        DQ = 1;            // 释放总线
        dat >>= 1;         // 数据右移一位
    }
    DelayUs2x(25);         // 延时 25 微秒结束传输
}

// 读取温度
unsigned int ReadTemperature(void)
{
    unsigned char lsb, msb;
    unsigned int temperature;

    if (!Init_DS18B20())   // 初始化 DS18B20
        return 0xFFFF;     // 若初始化失败，返回错误代码

    WriteOneChar(0xCC);    // 跳过 ROM 命令
    WriteOneChar(0x44);    // 启动温度转换
    DelayMs(10);           // 等待转换完成

    Init_DS18B20();        // 再次初始化传感器
    WriteOneChar(0xCC);    // 跳过 ROM 命令
    WriteOneChar(0xBE);    // 读取 Scratchpad 数据

    lsb = ReadOneChar();   // 读取低字节
    msb = ReadOneChar();   // 读取高字节

    temperature = (msb << 8) | lsb; // 合并为完整的 16 位温度数据

    // 检查温度值是否在有效范围内
    if (temperature > 1000) // 根据具体情况修改有效范围
        return 0xFFFF;     // 若超出范围，返回错误代码

    return temperature;    // 返回温度值
}
