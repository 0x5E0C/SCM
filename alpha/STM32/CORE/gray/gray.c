#include "gray.h"

volatile u16 gray1_value;
volatile u16 gray2_value;

float gray_weight[10]={-4,-3,-2,-1,0,0,1,2,3,4};

void Ask_Gray1()
{
	UART4_Send(0xFF);
	delay_ms(1);
	UART4_Send(0xFF);
	delay_ms(1);
	UART4_Send(0x01);
	delay_ms(1);
	UART4_Send(0x02);
	delay_ms(1);
	UART4_Send(0x08);
	delay_ms(1);
	UART4_Send(0x0B);
	delay_ms(1);
}

void Ask_Gray2()
{
	UART4_Send(0xFF);
	delay_ms(1);
	UART4_Send(0xFF);
	delay_ms(1);
	UART4_Send(0x02);
	delay_ms(1);
	UART4_Send(0x02);
	delay_ms(1);
	UART4_Send(0x08);
	delay_ms(1);
	UART4_Send(0x0C);
	delay_ms(1);
}

void Set_Gray_Send_Speed(u8 gray,u8 speed)
{
	if(gray&0x01)
	{
		USART2_Send(0xFF);
		USART2_Send(0xFF);
		USART2_Send(0x01);
		USART2_Send(0x03);
		USART2_Send(0x0B);
		USART2_Send(speed);
		USART2_Send(speed+0x0F);
	}
	if(gray&0x10)
	{
		UART4_Send(0xFF);
		UART4_Send(0xFF);
		UART4_Send(0x01);
		UART4_Send(0x03);
		UART4_Send(0x0B);
		UART4_Send(speed);
		UART4_Send(speed+0x0F);
	}
}

bool Read_Gray_State(u8 gray,u8 id)
{
	if(gray==Gray1)
	{
		return gray1_value&((u16)1<<id);
	}
	else if(gray==Gray2)
	{
		return gray2_value&((u16)1<<id);
	}
    return 0;	
}

u8 Read_Gray_Number(u8 gray)
{
	u8 i;
	u8 num=0;
	for(i=0;i<10;i++)
	{
		if(Read_Gray_State(gray,i))
		{
			num++;
		}
	}
	return num;
}

float Caculate_Gray_PID(u8 gray)
{
	u8 i;
	float temp=0;
	if(gray==Gray1)
	{
		PID_Gray1.SetValue=0;
		for(i=0;i<10;i++)
		{
			temp+=Read_Gray_State(gray,i)*gray_weight[i];
		}
		PID_Gray1.ActualValue=temp;
		return Incremental_PID(&PID_Gray1);
	}
	else if(gray==Gray2)
	{
		PID_Gray2.SetValue=0;
		for(i=0;i<10;i++)
		{
			temp+=Read_Gray_State(gray,i)*gray_weight[i];
		}
		PID_Gray2.ActualValue=temp;
		return -Incremental_PID(&PID_Gray2);
	}
    return 0;	
}
