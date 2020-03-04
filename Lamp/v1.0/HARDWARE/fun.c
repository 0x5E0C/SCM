#include "fun.h"
#include "timer.h"

u8 task_id=1;

void Control_Fun(u16 pwm)
{
	TIM_SetCompare3(TIM3,pwm);
}

void Close_Fun()
{
	TIM_SetCompare3(TIM3,0);
}

void Fun_Normal_Mode()
{
	u32 time;
	time=second+40;
	Control_Fun(6000);
	while(second<time && task_id==1);
	time=second+10;
	Control_Fun(20000);
	while(second<time && task_id==1);
	time=second+10;
	Close_Fun();
	while(second<time && task_id==1);
}
