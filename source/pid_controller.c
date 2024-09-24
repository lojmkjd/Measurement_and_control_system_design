/*pid_controller.c*/

#include "include/pid_controller.h"
#include "include/relay.h"
#include "include/buzzer.h"
#include "reg52.h"


void pIDControl() {
    // 确保在函数开始时声明所有变量
    float error;
    float output;
    float derivative; // 声明变量，不赋值

    error = setpoint - temperature; // 计算误差
    integral += error; // 更新积分值
    derivative = error - previous_error; // 计算微分值
    previous_error = error; // 保存当前误差

    // 计算 PID 输出
    output = (KP * error) + (KI * integral) + (KD * derivative);

    // 根据 PID 输出控制继电器
    if (output > 0) {
        relayOpened();
    } else {
        relayClosed();
    }
}
