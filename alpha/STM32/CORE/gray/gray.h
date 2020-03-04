#ifndef _GRAY_H
#define _GRAY_H

#include "bsp.h"

#define Gray1 0x01
#define Gray2 0x10

extern volatile u16 gray1_value;
extern volatile u16 gray2_value;

void Ask_Gray1(void);
void Ask_Gray2(void);
void Set_Gray_Send_Speed(u8 gray,u8 speed);
bool Read_Gray_State(u8 gray,u8 id);
u8 Read_Gray_Number(u8 gray);
float Caculate_Gray_PID(u8 gray);

#endif
