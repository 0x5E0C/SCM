#ifndef _TIMERX_H
#define _TIMERX_H

#include "bsp.h"

extern u32 millis;

void Encoder_TIM2_Init(void);
void Encoder_TIM3_Init(void);
void Encoder_TIM4_Init(void);
void Encoder_TIM5_Init(void);
void PID_TIM6_Init(unsigned int arr,unsigned int psc);

#endif
