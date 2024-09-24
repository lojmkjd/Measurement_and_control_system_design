#ifndef _COMCDT_H 
#define _COMCDT_H

#include "reg52.h" 

// 假设这些变量在其他地方已经定义
sbit dig_ten=P3^2;
sbit dig_unit=P3^3;
sbit firstDecimalPlace=P3^4;
sbit secondDecimalPlace=P3^5;

// 显示温度的函数
void displayTemperature(unsigned char integerPart, unsigned char decimalPart);

// 显示单个数字的函数
void displayDigit(unsigned char digit, unsigned char position);

// 显示时间的函数
void displayTime(unsigned int totalSeconds);

#endif