#include "include/delay.h"
#include "include/18B20.h"

bit Init_DS18B20(void)
{
    // 初始化变量dat为0
    bit dat = 0;

    // 将DQ置为高电平
    DQ = 1;
    // 延时5微秒
    DelayUs2x(5);

    // 将DQ置为低电平
    DQ = 0;
    // 延时200微秒
    DelayUs2x(200);
    // 延时200微秒
    DelayUs2x(200);

    // 将DQ置为高电平
    DQ = 1;
    // 延时50微秒
    DelayUs2x(50);

    // 读取DQ的值赋给dat
    dat = DQ;
    // 延时25微秒
    DelayUs2x(25);

    // 返回dat的值
    return dat;
}

unsigned char ReadOneChar(void)
{
    unsigned char i = 0;
    unsigned char dat = 0;
    // 循环8次，每次读取一位数据
    for(i = 8; i > 0; i--) {
        // 将DQ置为0
        DQ = 0;
        // 将dat右移一位
        dat >>= 1;
        // 将DQ置为1
        DQ = 1;
        // 如果DQ为高电平，则将dat的最高位设为1
        if(DQ)
            dat |= 0x80;
        // 延时25微秒
        DelayUs2x(25);
    }
    // 返回读取到的字符
    return(dat);
}

void WriteOneChar(unsigned char dat)
{
    unsigned char i = 0;
    for(i = 8; i > 0; i--) {
        DQ = 0;
        DQ = dat & 0x01;
        DelayUs2x(25);
        DQ = 1;
        dat >>= 1;
    }
    DelayUs2x(25);
}

unsigned int ReadTemperature(void)
{
    unsigned char a = 0;
    unsigned int b = 0;
    unsigned int t = 0;
    Init_DS18B20();
    WriteOneChar(0xCC);
    WriteOneChar(0x44);
    DelayMs(10);
    Init_DS18B20();
    WriteOneChar(0xCC);
    WriteOneChar(0xBE);
    a = ReadOneChar();
    b = ReadOneChar();
    b <<= 8;
    t = a + b;
    return(t);
}
