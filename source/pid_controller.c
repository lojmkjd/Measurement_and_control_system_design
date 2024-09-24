/* pid_controller.c */

#include "include/pid_controller.h"
#include "include/relay.h"
#include "include/buzzer.h"
#include "reg52.h"

// PID 控制参数
float KP = 1.0;     // 比例系数
float KI = 0.1;     // 积分系数
float KD = 0.01;    // 微分系数

// 全局变量
float setpoint = 0.0;      // 设定点
float temperature = 0.0;   // 当前温度
float integral = 0.0;      // 积分值
float previous_error = 0.0; // 上一时刻的误差

/**
 * @brief PID 控制函数
 *
 * 根据当前温度与设定点的误差计算 PID 输出，并控制继电器
 */
void pIDControl() {
    // 计算当前误差
    float error = setpoint - temperature; 

    // 更新积分值
    integral += error; 

    // 计算微分值
    float derivative = error - previous_error; 

    // 保存当前误差用于下次计算
    previous_error = error; 

    // 计算 PID 输出
    float output = (KP * error) + (KI * integral) + (KD * derivative);

    // 根据 PID 输出控制继电器
    if (output > 0) {
        relayOpened();  // 打开继电器
    } else {
        relayClosed();  // 关闭继电器
    }
}
