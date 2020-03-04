#ifndef _ENCODER_H
#define _ENCODER_H

#include "bsp.h"

extern volatile float Encoder_Motor_A;
extern volatile float Encoder_Motor_B;
extern volatile float Encoder_Motor_C;
extern volatile float Encoder_Motor_D;

int Read_Encoder(u8 TIMX);
void Calculate_Distance(void);
void Clear_Encoder(void);

#endif
