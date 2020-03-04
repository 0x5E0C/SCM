#ifndef _GYROSCOPE_H
#define _GYROSCOPE_H

#include "bsp.h"

#define Tracing_Mode  0
#define Rotation_Mode 1
#define Custom_Mode   2

typedef struct _gyro
{
	float ax;
	float ay;
	float az;
	float wx;
	float wy;
	float wz;
	float roll;
	float pitch;
	float yaw;
	float Degrees_0;
	float Degrees_90;
	float Degrees_180;
	float Degrees_270;
} Gyro;

extern volatile Gyro gyro;

float Change_Angle_Format(float original_angle);
void Set_Angle(float target,u8 mode);
float Caculate_Gyro_PID(float actual_angle,float target_angle);

#endif
