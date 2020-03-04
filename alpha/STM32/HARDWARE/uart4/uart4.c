#include "uart4.h"

u8 UART4_RX_BUF[UART4_REC_LEN];
u8 UART4_byteNum;

void UART4_Send(u8 data)
{
	while((UART4->SR & 0X40) == 0);
    UART4->DR = data;
}

void Gray2_UART4_Init(u32 bound)
{
    float temp;
    temp = 36000000 / bound;
    RCC->APB2ENR |= 1 << 4;
    RCC->APB1ENR |= 1 << 19;
    RCC->AHBENR |= 1 << 1;
    RCC->APB1RSTR |= 1 << 19;
    RCC->APB1RSTR &= ~(1 << 19);
    GPIOC->CRH &= 0xFFFF00FF;
    GPIOC->CRH |= 0x00008B00;
    UART4->BRR = (u16)temp;
    DMA2_Channel3->CNDTR = UART4_REC_LEN;
    DMA2_Channel3->CPAR = (u32)(&UART4->DR);
    DMA2_Channel3->CMAR = (u32)UART4_RX_BUF;
    DMA2_Channel3->CCR |= 0X3081;
    UART4->CR3 |= 1 << 6;
    MY_NVIC_Init(0, 2, UART4_IRQn, 2);
    UART4->CR1 = 0x201C;
}


void UART4_IRQHandler(void)
{
    if(UART4->SR & (1 << 3))
    {
        UART4->DR;
        UART4->SR &= ~(1 << 3);
    }
    if(UART4->SR & (1 << 4))
    {
        UART4_byteNum = UART4->SR;
        UART4_byteNum = UART4->DR;
        UART4_byteNum = UART4_REC_LEN - DMA2_Channel3->CNDTR;
        DMA2_Channel3->CCR &= ~(1 << 0);
	    if(UART4_RX_BUF[0]==0xFF && UART4_RX_BUF[1]==0xFF && UART4_RX_BUF[3]==0x05 && UART4_RX_BUF[4]==0x08)
		{	
			if(UART4_RX_BUF[2]==0x01)
			{	
				gray1_value=(u16)UART4_RX_BUF[5]<<8|UART4_RX_BUF[6]<<4|UART4_RX_BUF[7];

			}
			else if(UART4_RX_BUF[2]==0x02)
			{
				gray2_value=(u16)UART4_RX_BUF[5]<<8|UART4_RX_BUF[6]<<4|UART4_RX_BUF[7];

			}										
		}	
        DMA2_Channel3->CNDTR = UART4_REC_LEN;
        DMA2_Channel3->CCR |= 1 << 0;
    }
}

