#ifndef _MAP_H
#define _MAP_H

#include "bsp.h"

#define X_First 0
#define Y_First 1

#define stop    0
#define no_stop 1

#define X_Tracing  0
#define Y_Tracing  1
#define No_Tracing 2

extern int X_Crossing;
extern int Y_Crossing;

void Set_Axis(int x,int y);
void Detect_X_Crossing(void);
void Detect_Y_Crossing(void);
void Tracing_X(u8 x_target,float speed,u8 flag);
void Tracing_Y(u8 y_target,float speed,u8 flag);
void Move_By_Tracing(u8 x_destination,u8 y_destination,float speed,u8 priority,u8 flag);
void Move_Distance(float x_speed,float y_speed,float angle,float distance,u8 mode);

#endif

