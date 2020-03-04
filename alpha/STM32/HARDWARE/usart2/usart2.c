#include "usart2.h"

u8 USART2_RX_BUF[USART2_REC_LEN];
u8 USART2_byteNum;
u8 length_cm = 0;
u8 ut_length[8] = {0};
u8 ut_data;

void USART2_Send(u8 data)
{
	while((USART2->SR & 0X40) == 0);
    USART2->DR = data;
}

void Ultra_USART2_Init(u32 bound)
{
    float temp;
    temp = 36000000 / bound;
    RCC->APB2ENR |= 1 << 2;
    RCC->APB1ENR |= 1 << 17;
    RCC->AHBENR |= 1 << 0;
    RCC->APB1RSTR |= 1 << 17;
    RCC->APB1RSTR &= ~(1 << 17);
    GPIOA->CRL &= 0xFFFF00FF;
    GPIOA->CRL |= 0x00008B00;
    USART2->BRR = (u16)temp;
    DMA1_Channel6->CNDTR = USART2_REC_LEN;
    DMA1_Channel6->CPAR = (u32)(&USART2->DR);
    DMA1_Channel6->CMAR = (u32)USART2_RX_BUF;
    DMA1_Channel6->CCR |= 0X3081;
    USART2->CR3 |= 1 << 6;
    MY_NVIC_Init(2, 1, USART2_IRQn, 2);
    USART2->CR1 = 0x201C;
}

void USART2_IRQHandler(void)
{
	u8 i;
    if(USART2->SR & (1 << 3))
    {
        USART2->DR;
        USART2->SR &= ~(1 << 3);
    }
    if(USART2->SR & (1 << 4))
    {
        USART2_byteNum = USART2->SR;
        USART2_byteNum = USART2->DR;
        USART2_byteNum = USART2_REC_LEN - DMA1_Channel6->CNDTR;
		if((USART2_RX_BUF[0]==0xff))
		{
			ut_data=USART2_RX_BUF[1];
			for(i=0;i<8;i++)
			{
				ut_length[i]=USART2_RX_BUF[i+1];
			}
		}
        DMA1_Channel6->CCR &= ~(1 << 0);
        DMA1_Channel6->CNDTR = USART2_REC_LEN;
        DMA1_Channel6->CCR |= 1 << 0;
    }
}


