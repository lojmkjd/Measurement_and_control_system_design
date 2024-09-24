/*pid_controller.h*/

#ifndef _PID_CONTROLLER_H
#define _PID_CONTROLLER_H

#define KP 1.0    // 比例系数
#define KI 0.1    // 积分系数
#define KD 0.05   // 微分系数

extern unsigned char setpoint; // 目标温度
extern unsigned char integral;  // 积分值
extern unsigned char previous_error; // 上一个误差

extern unsigned char temperature; // 当前温度

void pIDControl();

#endif  /*_PID_CONTROLLER_H*/