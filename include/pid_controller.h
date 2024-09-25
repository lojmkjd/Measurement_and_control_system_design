/* pid_controller.h */

#ifndef _PID_CONTROLLER_H
#define _PID_CONTROLLER_H

// PID 控制参数定义
#define KP 1.0  // 比例系数
#define KI 0.1  // 积分系数
#define KD 0.05 // 微分系数

// 外部变量声明
extern unsigned char setpoint;       // 目标温度（设定点）
extern unsigned char integral;       // 积分值
extern unsigned char previous_error; // 上一个误差
extern float temperature;    // 当前温度

/**
 * @brief PID 控制函数
 *
 * 计算误差并根据 PID 控制算法调整继电器状态
 */
void pIDControl();

#endif /* _PID_CONTROLLER_H */
