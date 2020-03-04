#include "gyroscope.h"

volatile Gyro gyro;

float Change_Angle_Format(float original_angle)
{
	if(original_angle<=90 || original_angle>=270)
	{
		if(original_angle>180)
		{
			original_angle-=360;
		}
	}
	return original_angle;
}

void Set_Angle(float target,u8 mode)
{
	float err=3;
	float now_angle;
	float diretion;
	u32 time;
	if(target>=360)
	{
		target=fmod(target,360);
	}
	if(mode==Tracing_Mode)
	{
		now_angle=gyro.yaw;
		now_angle=Change_Angle_Format(now_angle);
		target=Change_Angle_Format(target);
		if(target==180)
		{
			Global_Motion.W=Caculate_Gyro_PID(now_angle-180,target-180);
		}
		else
		{
			Global_Motion.W=Caculate_Gyro_PID(now_angle,target);
		}
		delay_ms(20);
	}
	else if(mode==Rotation_Mode)
	{
		time=millis+1500;
		while(millis<time)
		{
			now_angle=gyro.yaw;
			if(now_angle>270)
			{
				now_angle-=360;
			}
			Global_Motion.W=Caculate_Gyro_PID(now_angle,target);
		}
	}
	else if(mode==Custom_Mode)
	{
		now_angle=gyro.yaw;
		while(fabs(now_angle-target)>err)
		{
			now_angle=gyro.yaw;
			if(now_angle-target<0)
			{
				diretion=-1;		
				if(fabs(now_angle-target)>180)
				{
					diretion=1;
				}
			}
			else
			{
				diretion=1;
			}
			Global_Motion.W=diretion*20;
		}
	}
}

float Caculate_Gyro_PID(float actual_angle,float target_angle)
{
	PID_Gyro.ActualValue=actual_angle;
	PID_Gyro.SetValue=target_angle;
    return Incremental_PID(&PID_Gyro);
}


