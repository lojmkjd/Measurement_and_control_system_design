/* ComCDT.c */
#include "reg52.h"
#include "include/delay.h"
#include "include/ComCDT.h"
#include <intrins.h>

// 数码管显示的数字编码表，0~9对应的编码
unsigned char table[] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90};

/**
 * @brief 显示温度的整数和小数部分
 * @param integerPart 温度的整数部分
 * @param decimalPart 温度的小数部分
 */
void displayTemperature(unsigned char integerPart , unsigned char decimalPart) {
    // 显示整数部分
    displayDigit(integerPart / 10, 0); // 显示十位
    displayDigit(integerPart % 10, 1); // 显示个位
    
    // 显示小数部分
    displayDigit(decimalPart / 10, 2); // 显示小数第一位
    displayDigit(decimalPart % 10, 3); // 显示小数第二位
}

/**
 * @brief 在指定位置显示数字
 * @param digit 要显示的数字（0~9）
 * @param position 显示数字的位置（0: 十位, 1: 个位, 2: 小数第一位, 3: 小数第二位）
 */
void displayDigit(unsigned char digit, unsigned char position) {
    // 根据位置设置掩码：个位位置为1时，打开小数点
    unsigned char mask = (position == 1) ? 0x7F : 0xFF;

    // 控制对应数码管位的信号
    switch (position) {
        case 0:
            dig_ten = 0;  // 十位数码管
            break;
        case 1:
            dig_unit = 0; // 个位数码管
            break;
        case 2:
            firstDecimalPlace = 0; // 小数第一位
            break;
        case 3:
            secondDecimalPlace = 0; // 小数第二位
            break;
        default:
            return; // 无效位置直接返回
    }

    // 将数字通过查表法取出编码，并与掩码运算后输出到P0端口
    P0 = table[digit] & mask;

    // 短暂延时确保显示稳定
    DelayUs2x(25);

    // 将P0恢复为高电平，表示释放总线
    P0 = 0xFF;

    // 重新设置数码管为高电平，关闭显示
    switch (position) {
        case 0:
            dig_ten = 1;  // 关闭十位数码管
            break;
        case 1:
            dig_unit = 1; // 关闭个位数码管
            break;
        case 2:
            firstDecimalPlace = 1; // 关闭小数第一位
            break;
        case 3:
            secondDecimalPlace = 1; // 关闭小数第二位
            break;
    }
}

/**
 * @brief 显示时间（以分钟显示）
 * @param totalSeconds 总的秒数，自动转换为分钟显示
 */
void displayTime(unsigned int totalSeconds) {
    // 将总秒数转换为分钟
    unsigned int totalMinutes = totalSeconds / 60;

    // 显示分钟的十位
    displayDigit(totalMinutes / 10, 2);

    // 显示分钟的个位
    displayDigit(totalMinutes % 10, 3);
}
