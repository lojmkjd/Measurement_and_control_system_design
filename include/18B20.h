#ifndef __18B20_H__
#define __18B20_H__

#include <reg52.h>
#include <intrins.h>

#define uchar unsigned char
#define uint   unsigned int

sbit DQ = P1^1;

// 读取温度的函数声明
unsigned int ReadTemperature(void);

// 初始化DS18B20温度传感器的函数声明
bit Init_DS18B20(void);

// 读取一个字节数据的函数声明
unsigned char ReadOneChar(void);

// 写入一个字节数据的函数声明
void WriteOneChar(unsigned char dat);

#endif

