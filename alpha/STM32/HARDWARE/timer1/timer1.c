#include "timer1.h"

void Servo_TIM1_Init(u16 arr, u16 psc)
{
    RCC->APB2ENR |= 1 << 11;
    RCC->APB2ENR |= 1 << 2;
    GPIOA->CRH &= 0xFFFF0FF0;
    GPIOA->CRH |= 0x0000B00B;
    TIM1->ARR = arr;
    TIM1->PSC = psc;
    TIM1->CCMR2 |= 6 << 12;
    TIM1->CCMR1 |= 6 << 4;
    TIM1->CCMR2 |= 1 << 11;
    TIM1->CCMR1 |= 1 << 3;
    TIM1->CCER |= 1 << 12;
    TIM1->CCER |= 1 << 0;
    TIM1->BDTR |= 1 << 15;
    TIM1->CR1 = 0x8000;
    TIM1->CR1 |= 0x01;
}

