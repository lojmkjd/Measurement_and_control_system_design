/*ComCDT.c*/
#include "reg52.h"
#include "include/delay.h"
#include "include/ComCDT.h"

unsigned char table[] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90};

void displayTemperature(unsigned char integerPart , unsigned char decimalPart){
    // 显示整数部分
    displayDigit(integerPart / 10, 0); // 十位
    displayDigit(integerPart % 10, 1); // 个位
    // 显示小数部分
    displayDigit(decimalPart / 10, 2); // 小数第一位
    displayDigit(decimalPart % 10, 3); // 小数第二位
}

void displayDigit(unsigned char digit, unsigned char position) {
    // 根据位置设置掩码
    unsigned char mask = (position == 1) ? 0x7F : 0xFF;

    // 根据位置进行不同操作
    switch (position) {
        case 0:
            // 十位数字位设置为0
            dig_ten = 0;
            break;
        case 1:
            // 个位数字位设置为0
            dig_unit = 0;
            break;
        case 2:
            // 第一位小数位设置为0
            firstDecimalPlace = 0;
            break;
        case 3:
            // 第二位小数位设置为0
            secondDecimalPlace = 0;
            break;
        default:
            // 无效位置，直接返回
            return;
    }

    // 将数字与掩码进行与运算，并将结果输出到P0端口
    P0 = table[digit] & mask;
    // 延时
    DelayUs2x(45); // 短暂延时50us
    // 将P0端口设置为高电平
    P0 = 0xFF; 

    // 根据位置进行不同操作
    switch (position) {
        case 0:
            // 十位数字位设置为1
            dig_ten = 1;
            break;
        case 1:
            // 个位数字位设置为1
            dig_unit = 1;
            break;
        case 2:
            // 第一位小数位设置为1
            firstDecimalPlace = 1;
            break;
        case 3:
            // 第二位小数位设置为1
            secondDecimalPlace = 1;
            break;
    }
}
void displayTime(unsigned int totalSeconds) {
    // 将总秒数转换为总分钟数
    unsigned int totalMinutes = totalSeconds / 60;
    // 显示总分钟数的十位数
    displayDigit(totalMinutes / 10, 2);
    // 显示总分钟数的个位数
    displayDigit(totalMinutes % 10, 3);
}
