#ifndef SERIAL_H
#define SERIAL_H

/**
 * @brief 初始化串口
 *
 * 配置串口工作模式和波特率，并启动定时器
 */
void initSerial(void);

/**
 * @brief 发送串口数据
 *
 * @param tmpdata 指向要发送的数据的指针
 */
void sendSerial(char *tmpdata);

#endif // SERIAL_H
