#include "include/delay.h"

void DelayUs2x(unsigned char t)
{
    // 循环直到 t 减到 0
    while(--t);
}

/**
 * @brief 延迟毫秒函数
 *
 * 通过循环调用 DelayUs2x 函数实现毫秒级别的延迟。
 *
 * @param t 延迟的毫秒数
 */
void DelayMs(unsigned char t)
{
    // 循环 t 次
    while(t--) {
        // 调用 DelayUs2x 函数，参数为 245，延迟一段时间
        DelayUs2x(245);
        // 再次调用 DelayUs2x 函数，参数为 245，继续延迟一段时间
        DelayUs2x(245);
    }
}