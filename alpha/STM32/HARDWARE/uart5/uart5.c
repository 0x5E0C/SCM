#include "uart5.h"

u8 finish_flag = 0;
u8 UART5_RX_BUF[UART5_REC_LEN];
u16 UART5_RX_STA;

void UART5_Send(u8 data)
{
    while((UART5->SR & 0X40) == 0);
    UART5->DR = data;
}

void Openmv_UART5_Init(u32 bound)
{
    float temp;
    temp = 36000000 / bound;
    RCC->APB1ENR |= 1 << 20;
    RCC->APB2ENR |= 3 << 4;
    RCC->APB1RSTR |= 1 << 20;
    RCC->APB1RSTR &= ~(1 << 20);
    GPIOC->CRH &= 0xFFF0FFFF;
    GPIOC->CRH |= 0x000B0000;
    GPIOD->CRL &= 0xFFFFF0FF;
    GPIOD->CRL |= 0x00000800;
    UART5->BRR = (u16)temp;
    MY_NVIC_Init(2, 0, UART5_IRQn, 2);
    UART5->CR1 = 0X202C;
}

//UART5_RX_STA
//7:完成
//6:包头
void UART5_IRQHandler(void)
{
    u8 res;
    if(UART5->SR & (1 << 5))
    {
        res = UART5->DR;
        if((UART5_RX_STA & 0x8000) == 0)
        {
            if(UART5_RX_STA & 0x4000)
            {
                UART5_RX_BUF[UART5_RX_STA & 0X3FFF] = res;
                UART5_RX_STA++;
                if((UART5_RX_STA & 0X3FFF) >= 3)
                {
                    if((UART5_RX_BUF[0] == 0xff) & (UART5_RX_BUF[2] == 0x23))
                    {
                        finish_flag = 1;
                        UART5_RX_STA = 0;
                    }
                    else
                    {
                        finish_flag = 0;
                    }
                }
            }
            else
            {
                if(res == 0xff)
                {
                    UART5_RX_STA |= 0x4000;
                    UART5_RX_BUF[UART5_RX_STA & 0X3FFF] = res;
                    UART5_RX_STA++;
                }
            }

        }
    }
}

