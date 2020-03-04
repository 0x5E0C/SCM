#include "timer8.h"

void Motor_TIM8_Init(u16 arr, u16 psc)
{
    GPIOB->CRL &= 0xFF00FFFF;
    GPIOB->CRL |= 0x00330000;
    GPIOB->CRH &= 0x0000FF00;
    GPIOB->CRH |= 0x33330033;
    A1 = 0;
    A2 = 0;
    B1 = 0;
    B2 = 0;
    C1 = 0;
    C2 = 0;
    D1 = 0;
    D2 = 0;
    RCC->APB2ENR |= 1 << 4;
    RCC->APB2ENR |= 1 << 13;
    GPIOC->CRL &= 0X00FFFFFF;
    GPIOC->CRL |= 0XBB000000;
    GPIOC->CRH &= 0XFFFFFF00;
    GPIOC->CRH |= 0X000000BB;
    TIM8->ARR = arr;
    TIM8->PSC = psc;
    TIM8->CCMR2 |= 6 << 12;
    TIM8->CCMR2 |= 6 << 4;
    TIM8->CCMR1 |= 6 << 12;
    TIM8->CCMR1 |= 6 << 4;
    TIM8->CCMR2 |= 1 << 11;
    TIM8->CCMR2 |= 1 << 3;
    TIM8->CCMR1 |= 1 << 11;
    TIM8->CCMR1 |= 1 << 3;
    TIM8->CCER |= 1 << 12;
    TIM8->CCER |= 1 << 8;
    TIM8->CCER |= 1 << 4;
    TIM8->CCER |= 1 << 0;
    TIM8->BDTR |= 1 << 15;
    TIM8->CR1 = 0x8000;
    TIM8->CR1 |= 0x01;
}
