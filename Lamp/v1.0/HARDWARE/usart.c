#include <stdio.h>
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "fun.h"

#if USART1_DMA_MODE
u8 USART1_RX_BUF[USART1_REC_LEN];
u8 USART1_byteNum;
#endif

int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);//循环发送,直到发送完毕   
    USART1->DR = (u8) ch;      
	return ch;
}

void USART1_Init(u32 bound)
{
#if USART1_DMA_MODE
    //USART1 GPIO设置
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    DMA_InitTypeDef DMA_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //TX			   //串口输出PA9
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //RX			 //串口输入PA10
    GPIO_Init(GPIOA, &GPIO_InitStructure);



    //USART1 NVIC 配置
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_Init(&NVIC_InitStructure);



    //USART1 初始化设置
    USART_InitStructure.USART_BaudRate = bound;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_Init(USART1, &USART_InitStructure);



    //DMA设置
    DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)&USART1->DR;
    DMA_InitStructure.DMA_MemoryBaseAddr = (u32)USART1_RX_BUF;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
    DMA_InitStructure.DMA_BufferSize = USART1_REC_LEN;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
    DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    DMA_Init(DMA1_Channel5, &DMA_InitStructure);


    USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);
    USART_ClearFlag(USART1, USART_FLAG_TC);
    USART_DMACmd(USART1, USART_DMAReq_Rx, ENABLE);
    USART_Cmd(USART1, ENABLE);
    DMA_Cmd(DMA1_Channel5, ENABLE);
#else
    //USART1 GPIO设置
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //TX			   //串口输出PA9
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //RX			 //串口输入PA10
    GPIO_Init(GPIOA, &GPIO_InitStructure);



    //USART1 NVIC 配置
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_Init(&NVIC_InitStructure);



    //USART1 初始化设置
    USART_InitStructure.USART_BaudRate = bound;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_Init(USART1, &USART_InitStructure);

    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
    USART_ClearFlag(USART1, USART_FLAG_TC);
    USART_Cmd(USART1, ENABLE);
#endif
}



void USART2_Init(u32 bound)
{
    //USART2 GPIO设置
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);


    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //TX			   //串口输出PA2
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3; //RX			 //串口输入PA3
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);


    //USART2 初始化设置
    USART_InitStructure.USART_BaudRate = bound;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART2, &USART_InitStructure);

    while(USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
    USART_Cmd(USART2, ENABLE);

    USART_ClearFlag(USART2, USART_FLAG_TC);

    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);

    //USART2 NVIC 配置
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}



void USART3_Init(u32 bound)
{
    //USART3 GPIO设置
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //TX			   //串口输出PB10
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11; //RX			   //串口输入PB11
    GPIO_Init(GPIOB, &GPIO_InitStructure);


    //USART3 NVIC 配置
    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_Init(&NVIC_InitStructure);



    //USART3 初始化设置
    USART_InitStructure.USART_BaudRate = bound;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_Init(USART3, &USART_InitStructure);

    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
    USART_ClearFlag(USART3, USART_FLAG_TC);
    USART_Cmd(USART3, ENABLE);
}



//void UART4_Init(unsigned int bound)
//{
//    //UART4 GPIO设置
//    GPIO_InitTypeDef GPIO_InitStructure;
//    USART_InitTypeDef USART_InitStructure;
//    NVIC_InitTypeDef NVIC_InitStructure;

//    RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //TX			   //串口输出PC10
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//    GPIO_Init(GPIOC, &GPIO_InitStructure);

//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11; //RX			   //串口输入PC11
//    GPIO_Init(GPIOC, &GPIO_InitStructure);


//    //UART4 NVIC 配置
//    NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;
//    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
//    NVIC_Init(&NVIC_InitStructure);

//    USART_InitStructure.USART_BaudRate = bound;
//    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
//    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
//    USART_InitStructure.USART_Parity = USART_Parity_No;
//    USART_InitStructure.USART_StopBits = USART_StopBits_1;
//    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
//    USART_Init(UART4, &USART_InitStructure);

//    USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);
//    USART_ClearFlag(UART4, USART_FLAG_TC);
//    USART_Cmd(UART4, ENABLE);
//}



//void UART5_Init(u32 bound)
//{
//    //UART5 GPIO设置
//    GPIO_InitTypeDef GPIO_InitStructure;
//    USART_InitTypeDef USART_InitStructure;
//    NVIC_InitTypeDef NVIC_InitStructure;

//    RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE);
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);

//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12; //TX			   //串口输出PC12
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//    GPIO_Init(GPIOC, &GPIO_InitStructure);

//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //RX			   //串口输入PD2
//    GPIO_Init(GPIOD, &GPIO_InitStructure);


//    //UART5 NVIC 配置
//    NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn;
//    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
//    NVIC_Init(&NVIC_InitStructure);

//    USART_InitStructure.USART_BaudRate = bound;
//    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
//    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
//    USART_InitStructure.USART_Parity = USART_Parity_No;
//    USART_InitStructure.USART_StopBits = USART_StopBits_1;
//    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
//    USART_Init(UART5, &USART_InitStructure);

//    USART_ITConfig(UART5, USART_IT_RXNE, ENABLE);
//    USART_ClearFlag(UART5, USART_FLAG_TC);
//    USART_Cmd(UART5, ENABLE);
//}



void USART1_IRQHandler(void)                	//串口1中断服务程序
{
#if USART1_DMA_MODE
    if(USART_GetITStatus(USART1, USART_IT_IDLE))
    {
        USART_ReceiveData(USART1);
        USART1_byteNum = USART1_REC_LEN - DMA_GetCurrDataCounter(DMA1_Channel5);
		if(USART1_byteNum==6)
		{
			if(USART1_RX_BUF[0]==0xA5 && \
			   USART1_RX_BUF[1]==0x5A && \
			   USART1_RX_BUF[2]==0x04 && \
			   USART1_RX_BUF[5]==0xAA)
			{
				switch(USART1_RX_BUF[3])
				{
					case 0xB1:
						Open_LED();
						break;
					case 0xB2:
						Turn_Up_LED();
						break;
					case 0xB3:
						if(task_id!=1)
						{
							task_id=1;
						}
						break;
					case 0xB4:
						Close_LED();
						break;
					case 0xB5:
						Turn_Down_LED();
						break;
					case 0xB6:
						if(task_id!=2)
						{
							task_id=2;
						}
						break;
					default:
						break;
				}
			}
		}
        USART_ClearITPendingBit(USART1, USART_IT_IDLE);
        DMA_Cmd(DMA1_Channel5, DISABLE);
        DMA_SetCurrDataCounter(DMA1_Channel5, USART1_REC_LEN);
        DMA_Cmd(DMA1_Channel5, ENABLE);
    }
#else
    if(USART_GetITStatus(USART1, USART_IT_RXNE))
    {

    }
    USART_ClearFlag(USART1, USART_FLAG_TC);
#endif
}



void USART2_IRQHandler(void)                	//串口2中断服务程序
{
    if(USART_GetITStatus(USART2, USART_IT_RXNE))
    {

    }
    USART_ClearFlag(USART2, USART_FLAG_TC);
}



void USART3_IRQHandler(void)                	//串口3中断服务程序
{
    if(USART_GetITStatus(USART3, USART_IT_RXNE))
    {

    }
    USART_ClearFlag(USART3, USART_FLAG_TC);
}



//void UART4_IRQHandler(void)                	//串口4中断服务程序
//{
//    if(USART_GetITStatus(UART4, USART_IT_RXNE))
//    {

//    }
//    USART_ClearFlag(UART4, USART_FLAG_TC);
//}



//void UART5_IRQHandler(void)                	//串口4中断服务程序
//{
//    if(USART_GetITStatus(UART5, USART_IT_RXNE))
//    {

//    }
//    USART_ClearFlag(UART5, USART_FLAG_TC);
//}

