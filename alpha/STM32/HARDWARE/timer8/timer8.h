#ifndef _TIMER8_H
#define _TIMER8_H

#include "bsp.h"

#define A1 PBout(12)
#define A2 PBout(13)
#define B1 PBout(14)
#define B2 PBout(15)
#define C1 PBout(9)
#define C2 PBout(8)
#define D1 PBout(4)
#define D2 PBout(5)

#define PWMA TIM8->CCR1
#define PWMB TIM8->CCR2
#define PWMC TIM8->CCR3
#define PWMD TIM8->CCR4

void Motor_TIM8_Init(u16 arr,u16 psc);

#endif
