#ifndef _PID_H
#define _PID_H

#include "bsp.h"

#define No_Max	FLT_MAX
#define No_Min  -FLT_MAX
#define No_Threshold_I	1000

typedef struct _PID 
{
	float SetValue;
	float ActualValue;
	float Err;
	float Last_Err;
	float Last_Err2;
	float Err_Sum;
	float P,I,D;
	float OutputMax;
	float OutputMin;
	float OutputPoint;
	float Threshold_I;
} PID;

extern volatile PID PID_MotorA,PID_MotorB,PID_MotorC,PID_MotorD;
extern volatile PID PID_Gray1,PID_Gray2;
extern volatile PID PID_Gyro;

void PID_Init(volatile PID *pid);
float Incremental_PID(volatile PID *pid);
float Positional_PID(volatile PID *pid);

#endif
