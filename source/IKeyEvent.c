#include "reg52.h"
#include "include/delay.h"
#include "include/IKeyEvent.h"

extern bit TEMPERATURE_OR_TIME;
extern bit IS_THE_RELAY_RUNNING;
#define DEBOUNCE_DELAY 2

void checkButtonState(bit stateFlag, bit button) {
    // 如果按钮状态等于防抖延迟时间
    if (button == 0) {
        // 延迟2毫秒
        DelayMs(DEBOUNCE_DELAY);
        // 如果按钮状态为0（按下状态）
        if (button == 0) {
            // 切换状态标志位的值
            stateFlag = !(stateFlag);
        }
        // 等待按钮状态不为0（即等待按钮释放）
        while (!button);
    }
}

void checkButtons(void) {
    // 检查温度或时间按钮的状态
    checkButtonState(TEMPERATURE_OR_TIME, switchButton);
    // 检查继电器是否正在运行的按钮状态
    checkButtonState(IS_THE_RELAY_RUNNING, startButton);
}
