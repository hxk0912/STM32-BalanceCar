#ifndef __CONTROL_H
#define __CONTROL_H

#include "main.h"


extern int count_tar;
extern int count_now ;
extern int count_time;
extern float speed_now;
extern float speed_tar;

extern float Position_KP;
extern float Position_KI;
extern float Position_KD;
extern float Velocity_KP;
extern float Velocity_KI;


void PWM_Init(void);
void Encoder_Init(void);
int Position_PID(float Encoder,short gyro,float Target);
int Incremental_PI (float Encoder_Left,float Encoder_Right,float Target);
int Incremental_PI (float Encoder_Left,float Encoder_Right,float Target);
int ReadEncoder_Left(void);
int ReadEncoder_Right(void);
void Motor_Left(int pwm);
void Motor_Right(int pwm);
int limit_pwm(int pwm);


#endif /*control.h*/
