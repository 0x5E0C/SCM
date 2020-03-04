#include "timerx.h"

u32 millis=0;

void Encoder_TIM2_Init(void)
{
    RCC->APB2ENR |= 1 << 0;
    AFIO->MAPR &= 0xF8FFFFFF;
    AFIO->MAPR |= 2 << 24;
    AFIO->MAPR &= 0xFFFFFCFF;
    AFIO->MAPR |= 1 << 8;
    RCC->APB1ENR |= 1 << 0;
    RCC->APB2ENR |= 1 << 2;
    RCC->APB2ENR |= 1 << 3;
    GPIOA->CRH &= 0X0FFFFFFF;
    GPIOA->CRH |= 0X40000000;
    GPIOB->CRL &= 0XFFFF0FFF;
    GPIOB->CRL |= 0X00004000;
    TIM2->DIER |= 1 << 0;
    TIM2->DIER |= 1 << 6;
    TIM2->PSC = 0x0;
    TIM2->ARR = 29999;
    TIM2->CR1 &= ~(3 << 8);
    TIM2->CR1 &= ~(3 << 5);
    TIM2->CCMR1 |= 1 << 0;
    TIM2->CCMR1 |= 1 << 8;
    TIM2->CCER &= ~(1 << 1);
    TIM2->CCER &= ~(1 << 5);
    TIM2->CCMR1 |= 3 << 4;
    TIM2->SMCR |= 3 << 0;
    MY_NVIC_Init(1, 0, TIM2_IRQn, 2);
    TIM2->CR1 |= 0x01;
}

void Encoder_TIM3_Init(void)
{
    RCC->APB2ENR |= 1 << 0;
    AFIO->MAPR &= 0xFFFFF3FF;
    AFIO->MAPR |= 0 << 10;
    RCC->APB1ENR |= 1 << 1;
    RCC->APB2ENR |= 1 << 2;
    GPIOA->CRL &= 0XFFFFFFFF;
    GPIOA->CRL |= 0X44000000;
    TIM3->DIER |= 1 << 0;
    TIM3->DIER |= 1 << 6;
    TIM3->PSC = 0x0;
    TIM3->ARR = 29999;
    TIM3->CR1 &= ~(3 << 8);
    TIM3->CR1 &= ~(3 << 5);
    TIM3->CCMR1 |= 1 << 0;
    TIM3->CCMR1 |= 1 << 8;
    TIM3->CCER &= ~(1 << 1);
    TIM3->CCER &= ~(1 << 5);
    TIM3->CCMR1 |= 3 << 4;
    TIM3->SMCR |= 3 << 0;
    MY_NVIC_Init(1, 0, TIM3_IRQn, 2);
    TIM3->CR1 |= 0x01;
}

void Encoder_TIM4_Init(void)
{
    RCC->APB1ENR |= 1 << 2;
    RCC->APB2ENR |= 1 << 3;
    GPIOB->CRL &= 0X00FFFFFF;
    GPIOB->CRL |= 0X44000000;
    TIM4->DIER |= 1 << 0;
    TIM4->DIER |= 1 << 6;
    TIM4->PSC = 0x0;
    TIM4->ARR = 29999;
    TIM4->CR1 &= ~(3 << 8);
    TIM4->CR1 &= ~(3 << 5);
    TIM4->CCMR1 |= 1 << 0;
    TIM4->CCMR1 |= 1 << 8;
    TIM4->CCER &= ~(1 << 1);
    TIM4->CCER &= ~(1 << 5);
    TIM4->CCMR1 |= 3 << 4;
    TIM4->SMCR |= 3 << 0;
    MY_NVIC_Init(1, 0, TIM4_IRQn, 2);
    TIM4->CR1 |= 0x01;
}

void Encoder_TIM5_Init(void)
{
    RCC->APB1ENR |= 1 << 3;
    RCC->APB2ENR |= 1 << 2;
    GPIOA->CRL &= 0XFFFFFF00;
    GPIOA->CRL |= 0X00000044;
    TIM5->DIER |= 1 << 0;
    TIM5->DIER |= 1 << 6;
    TIM5->PSC = 0x0;
    TIM5->ARR = 29999;
    TIM5->CR1 &= ~(3 << 8);
    TIM5->CR1 &= ~(3 << 5);
    TIM5->CCMR1 |= 1 << 0;
    TIM5->CCMR1 |= 1 << 8;
    TIM5->CCER &= ~(1 << 1);
    TIM5->CCER &= ~(1 << 5);
    TIM5->CCMR1 |= 3 << 4;
    TIM5->SMCR |= 3 << 0;
    MY_NVIC_Init(1, 0, TIM5_IRQn, 2);
    TIM5->CR1 |= 0x01;
}

void PID_TIM6_Init(unsigned int arr, unsigned int psc)
{
    RCC->APB1ENR |= 1 << 4;
    TIM6->ARR = arr;
    TIM6->PSC = psc;
    TIM6->DIER |= 1 << 0;
    MY_NVIC_Init(0, 0, TIM6_IRQn, 2);
    TIM6->CR1 |= 0x01;
}

void TIM2_IRQHandler(void)
{
    if(TIM2->SR & 0X0001)
    {
    }
    TIM2->SR &= ~(1 << 0);
}

void TIM3_IRQHandler(void)
{
    if(TIM3->SR & 0X0001)
    {
    }
    TIM3->SR &= ~(1 << 0);
}

void TIM4_IRQHandler(void)
{
    if(TIM4->SR & 0X0001)
    {
    }
    TIM4->SR &= ~(1 << 0);
}

void TIM5_IRQHandler(void)
{
    if(TIM5->SR & 0X0001)
    {
    }
    TIM5->SR &= ~(1 << 0);
}

void TIM6_IRQHandler(void)
{
    if(TIM6->SR & 0X0001)
    {
		millis+=20;
        Move();
        Calculate_Distance();
    }
    TIM6->SR &= ~(1 << 0);
}

