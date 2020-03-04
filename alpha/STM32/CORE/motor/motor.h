#ifndef _MOTOR_H
#define _MOTOR_H

#include "bsp.h"

#define L 1.575
#define cos_45 0.707107
#define sin_45 0.707107

typedef struct _motion
{
	float Vx;
	float Vy;
	float W;
	float X_Distance;
	float Y_Distance;
	float S_Distance;
} Motion;

extern volatile Motion Global_Motion;

void Motor_Drive(int SpeedA,int SpeedB,int SpeedC,int SpeedD);
void Move(void);
void Stop(u16 time);
#endif
