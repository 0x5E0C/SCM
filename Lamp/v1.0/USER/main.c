#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "timer.h"
#include "led.h"
#include "fun.h"

int main()
{	
	delay_init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 
	USART1_Init(9600);
	TIM1_PWM_Init(1000,71);
	TIM3_PWM_Init(19999,71);
	TIM4_Init(49999,71);
	while(1)
	{
		switch(task_id)
		{
			case 1:
				Fun_Normal_Mode();
				break;
			case 2:
				TIM_SetCompare3(TIM3,20000);
				break;
			default:
				break;
		}
	}
}


