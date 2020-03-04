#include "led.h"

u8 color=White;
u8 state=Close;

void Open_LED()
{
	if(state==Close)
	{
		state=Open;
		TIM_SetCompare1(TIM1,1000);
	}
}

void Close_LED()
{
	if(state==Open)
	{
		state=Close;
		TIM_SetCompare1(TIM1,0);
		TIM_SetCompare4(TIM1,0);
	}
}

void Turn_Up_LED()
{
	u16 temp;
	if(state==Open)
	{
		if(color==White)
		{
			temp=TIM_GetCapture1(TIM1);
			temp+=100;
			if(temp>=1000)
			{
				temp=1000;
			}
			TIM_SetCompare1(TIM1,temp);
		}
		else if(color==Yellow)
		{
			temp=TIM_GetCapture4(TIM1);
			temp+=100;
			if(temp>=1000)
			{
				temp=1000;
			}
			TIM_SetCompare4(TIM1,temp);
		}
	}
}

void Turn_Down_LED()
{
	u16 temp;
	if(state==Open)
	{
		if(color==White)
		{
			temp=TIM_GetCapture1(TIM1);
			temp-=100;
			if(temp<=100)
			{
				temp=100;
			}
			TIM_SetCompare1(TIM1,temp);
		}
		else if(color==Yellow)
		{
			temp=TIM_GetCapture4(TIM1);
			temp-=100;
			if(temp<=100)
			{
				temp=100;
			}
			TIM_SetCompare4(TIM1,temp);
		}
	}
}

void Change_Color()
{
	if(color==White)
	{
		color=Yellow;
		TIM_SetCompare4(TIM1,TIM_GetCapture1(TIM1));
		TIM_SetCompare1(TIM1,0);
	}
	else if(color==Yellow)
	{
		color=White;
		TIM_SetCompare1(TIM1,TIM_GetCapture4(TIM1));
		TIM_SetCompare4(TIM1,0);
	}
}

