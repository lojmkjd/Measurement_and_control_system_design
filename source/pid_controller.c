/* pid_controller.c */

#include "include/pid_controller.h"
#include "include/relay.h"
#include "include/buzzer.h"
#include "reg52.h"
#include <intrins.h>
#include "include/delay.h"

/**
 * @brief PID 控制函数
 *
 * 根据当前温度与设定点的误差计算 PID 输出，并控制继电器
 */
void pIDControl()
{

    char error, derivative, output;
    // 计算当前误差
    error = setpoint - temperature;

    // 更新积分值
    integral += error;

    // 计算微分值
    derivative = error - previous_error;

    // 保存当前误差用于下次计算
    previous_error = error;

    // 计算 PID 输出
    output = (KP * error) + (KI * integral) + (KD * derivative);

    // 根据 PID 输出控制继电器
    if (output > 0)
    {
        relayOpened();  // 打开继电器
        DelayUs2x(25); // 延时，防止继电器频繁开关
    }
    else
    {
        relayClosed();  // 关闭继电器
        DelayUs2x(25); // 延时，防止继电器频繁开关
    }
}
