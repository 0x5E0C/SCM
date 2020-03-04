#include "usart1.h"

void USART1_Send(u8 data)
{
	while((USART1->SR & 0X40) == 0);
    USART1->DR = data;
}

void USART1_Init(u32 bound)
{
    float temp;
    temp = 72000000 / bound;
    RCC->APB2ENR |= 1 << 2;
    RCC->APB2ENR |= 1 << 14;
    RCC->APB2RSTR |= 1 << 14;
    RCC->APB2RSTR &= ~(1 << 14);
    GPIOA->CRH &= 0xFFFFF00F;
    GPIOA->CRH |= 0x000008B0;
    USART1->BRR = (u16)temp;
    MY_NVIC_Init(2, 2, USART1_IRQn, 2);
    USART1->CR1 = 0x202C;
}


void USART1_IRQHandler(void)
{
    u8 temp;
    if(USART1->SR & (1 << 5))
    {
        temp = USART1->DR;
        USART1->DR = temp;
        while((USART1->SR & 0X40) == 0);
    }
}
