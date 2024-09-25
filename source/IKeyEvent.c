/* IKeyEvent.c */
#include "reg52.h"
#include "include/delay.h"
#include "include/IKeyEvent.h"
#include <intrins.h>

#define DEBOUNCE_DELAY 2 // 防抖延迟时间（单位：毫秒）

/**
 * @brief 检查所有按钮的状态
 */
void checkButtons(void) {
		// 如果按钮状态为按下（0）
		if (switchButton == 0) {
        // 延迟一段时间以防抖动
        DelayMs(DEBOUNCE_DELAY);
        // 再次检查按钮状态
        if (switchButton == 0) {
            displayTemperatureOrTime = !displayTemperatureOrTime; // 切换显示状态
            DelayMs(DEBOUNCE_DELAY); // 再次延迟以防止抖动
        }
        // 等待按钮释放（状态变为1）
        while (!switchButton);
		}
}