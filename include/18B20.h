#ifndef __18B20_H__
#define __18B20_H__

#include <reg52.h>
#include <intrins.h>

// 类型定义：简化代码中的类型书写
#define uchar unsigned char
#define uint  unsigned int

// DS18B20 数据线连接到 P1.1 引脚
sbit DQ = P1^1;

// 函数声明

/**
 * @brief 读取温度
 * @return 读取到的温度值（单位取决于具体实现），若出错则返回 0xFFFF
 */
unsigned int ReadTemperature(void);

/**
 * @brief 初始化 DS18B20 传感器
 * @return 成功返回 1，失败返回 0
 */
bit Init_DS18B20(void);

/**
 * @brief 读取一个字节的数据
 * @return 读取到的一个字节
 */
unsigned char ReadOneChar(void);

/**
 * @brief 写入一个字节的数据
 * @param dat 要写入的字节数据
 */
void WriteOneChar(unsigned char dat);

#endif // __18B20_H__
