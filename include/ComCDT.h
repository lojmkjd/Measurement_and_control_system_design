#ifndef _COMCDT_H 
#define _COMCDT_H

#include "reg52.h" 

// 数码管位选引脚定义
sbit dig_ten = P3^2;           // 控制显示十位数字
sbit dig_unit = P3^3;          // 控制显示个位数字
sbit firstDecimalPlace = P3^4; // 控制显示小数第一位
sbit secondDecimalPlace = P3^5;// 控制显示小数第二位

// 函数声明

/**
 * @brief 显示温度（整数部分和小数部分）
 * @param integerPart 温度的整数部分
 * @param decimalPart 温度的小数部分
 */
void displayTemperature(unsigned char integerPart, unsigned char decimalPart);

/**
 * @brief 在指定位置显示单个数字
 * @param digit 要显示的数字（0-9）
 * @param position 显示的位置（0: 十位, 1: 个位, 2: 小数第一位, 3: 小数第二位）
 */
void displayDigit(unsigned char digit, unsigned char position);

/**
 * @brief 显示时间（以分钟显示）
 * @param totalSeconds 总的秒数，将其转换为分钟进行显示
 */
void displayTime(unsigned int totalSeconds);

#endif // _COMCDT_H