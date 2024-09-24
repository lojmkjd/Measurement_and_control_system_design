/* IKeyEvent.c */
#include "reg52.h"
#include "include/delay.h"
#include "include/IKeyEvent.h"

#define DEBOUNCE_DELAY 2 // 防抖延迟时间（单位：毫秒）

/**
 * @brief 检查按钮状态并处理防抖
 * 
 * @param button 按钮的当前状态（0 表示按下，1 表示释放）
 */
void checkButtonState(bit button) {
    // 如果按钮状态为按下（0）
    if (button == 0) {
        // 延迟一段时间以防抖动
        DelayMs(DEBOUNCE_DELAY);
        // 再次检查按钮状态
        if (button == 0) {
            displayTemperatureOrTime = !displayTemperatureOrTime; // 切换显示状态
            DelayMs(DEBOUNCE_DELAY); // 再次延迟以防止抖动
        }
        // 等待按钮释放（状态变为1）
        while (!button);
    }
}

/**
 * @brief 检查所有按钮的状态
 */
void checkButtons(void) {
    // 检查温度或时间切换按钮的状态
    checkButtonState(switchButton); // 更新状态
}
