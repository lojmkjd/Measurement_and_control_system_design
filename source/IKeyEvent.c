/*IKeyEvent.c*/
#include "reg52.h"
#include "include/delay.h"
#include "include/IKeyEvent.h"

#define DEBOUNCE_DELAY 2

void checkButtonState(bit button) {
    // 如果按钮状态等于防抖延迟时间
    if (button == 0) {
        // 延迟2毫秒
        DelayMs(DEBOUNCE_DELAY);
        // 如果按钮状态为0（按下状态）
        if (button == 0) {
            displayTemperatureOrTime = !displayTemperatureOrTime; // 切换状态
            DelayMs(DEBOUNCE_DELAY); // 延迟2毫秒
        }
        // 等待按钮状态不为0（即等待按钮释放）
        while (!button);
    }
}

void checkButtons(void) {
    // 检查温度或时间按钮的状态
    checkButtonState(switchButton); // 更新状态
}