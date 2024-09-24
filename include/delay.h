#ifndef __DELAY_H__
#define __DELAY_H__

/**
 * @brief 2x延迟微秒函数
 * 
 * @param t 要延迟的次数（每次循环约1个微秒）
 */
void DelayUs2x(unsigned char t);

/**
 * @brief 延迟毫秒函数
 *
 * @param t 延迟的毫秒数
 */
void DelayMs(unsigned char t);

#endif // __DELAY_H__
