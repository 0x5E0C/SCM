#include "map.h"

int X_Crossing = 0;
int Y_Crossing = 0;

void Set_Axis(int x, int y)
{
    X_Crossing = x;
    Y_Crossing = y;
    Clear_Encoder();
}

void Detect_X_Crossing()
{
    int diretion = 1;
    if(fabs(gyro.yaw - 180) < 45)
    {
        diretion = -1;
    }
    if(Read_Gray_Number(Gray2) >= 5 && Global_Motion.S_Distance > 60)
    {
        if(Global_Motion.Vx > 0)
        {
            X_Crossing += diretion;
        }
        else if(Global_Motion.Vx < 0)
        {
            X_Crossing -= diretion;
        }
        Clear_Encoder();
    }
}

void Detect_Y_Crossing()
{
    int diretion = 1;
    if(fabs(gyro.yaw  - 180) < 45)
    {
        diretion = -1;
    }
    if(Read_Gray_Number(Gray1) >= 5 && Global_Motion.S_Distance > 60)
    {
        if(Global_Motion.Vy > 0)
        {
            Y_Crossing += diretion;
        }
        else if(Global_Motion.Vy < 0)
        {
            Y_Crossing -= diretion;
        }
        Clear_Encoder();
    }
}

void Tracing_X(u8 x_target, float speed, u8 flag)
{
    float diretion = 1, angle = gyro.Degrees_0;
    if((x_target - X_Crossing) != 0)
    {
        if(x_target - X_Crossing < 0)
        {
            diretion = -diretion;
        }
        if(fabs(gyro.yaw  - 180) < 45)
        {
            diretion = -diretion;
            angle = gyro.Degrees_180;
        }
        while(1)
        {
            Global_Motion.Vx = diretion * speed;;
            Global_Motion.Vy = Caculate_Gray_PID(Gray2);
            Set_Angle(angle, Tracing_Mode);
            Ask_Gray2();
            Detect_X_Crossing();
            if(X_Crossing == x_target)
            {
                Clear_Encoder();
                break;
            }
        }
        while(Global_Motion.S_Distance < 165)
        {
            Global_Motion.Vx = diretion * speed;
            Global_Motion.Vy = 0;
            Set_Angle(angle, Tracing_Mode);
        }
        if(flag == stop)
        {
            Stop(1000);
        }
    }
}

void Tracing_Y(u8 y_target, float speed, u8 flag)
{
    float diretion = 1, angle = gyro.Degrees_0;
    if((y_target - Y_Crossing) != 0)
    {
        if(y_target - Y_Crossing < 0)
        {
            diretion = -diretion;
        }
        if(fabs(gyro.yaw - 180) < 45)
        {
            diretion = -diretion;
            angle = gyro.Degrees_180;
        }
        while(1)
        {
            Global_Motion.Vx = Caculate_Gray_PID(Gray1);
            Global_Motion.Vy = diretion * speed;
            Set_Angle(angle, Tracing_Mode);
            Ask_Gray1();
            Detect_Y_Crossing();
			if(Red_Infrared!=1 || Blue_Infrared!=1)
			{
				time_count=millis+5000;
				while(Red_Infrared!=1 || Blue_Infrared!=1)
				{
					Stop(1000);
					if(millis>time_count)
					{
						break;
					}
				}
			}
            if(Y_Crossing == y_target)
            {
                Clear_Encoder();
                break;
            }
        }
        while(Global_Motion.S_Distance < 165)
        {
            Global_Motion.Vx = 0;
            Global_Motion.Vy = diretion * speed;
            Set_Angle(angle, Tracing_Mode);
        }
        if(flag == stop)
        {
            Stop(1000);
        }
    }
}

void Move_By_Tracing(u8 x_destination, u8 y_destination, float speed, u8 priority, u8 flag)
{
    if(priority == X_First)
    {
        if((x_destination - X_Crossing) != 0)
        {
            Tracing_X(x_destination, speed, flag);
        }
        Clear_Encoder();
        if((y_destination - Y_Crossing) != 0)
        {
            Tracing_Y(y_destination, speed, flag);
        }
        Clear_Encoder();
    }
    else
    {
        if((y_destination - Y_Crossing) != 0)
        {
            Tracing_Y(y_destination, speed, flag);
        }
        Clear_Encoder();
        if((x_destination - X_Crossing) != 0)
        {
            Tracing_X(x_destination, speed, flag);
        }
        Clear_Encoder();
    }
}

void Move_Distance(float x_speed, float y_speed, float angle, float distance, u8 mode)
{
    Clear_Encoder();
    switch(mode)
    {
    case No_Tracing:
        while(Global_Motion.S_Distance < distance)
        {
            Global_Motion.Vx = x_speed;
            Global_Motion.Vy = y_speed;
            Set_Angle(angle, Tracing_Mode);
        }
        break;
    case X_Tracing:
        while(Global_Motion.S_Distance < distance)
        {
            Global_Motion.Vx = x_speed;
            Global_Motion.Vy = Caculate_Gray_PID(Gray2);
            Set_Angle(angle, Tracing_Mode);
			Ask_Gray2();
			Detect_X_Crossing();
        }
        break;
    case Y_Tracing:
        while(Global_Motion.S_Distance < distance)
        {
            Global_Motion.Vx = Caculate_Gray_PID(Gray1);
            Global_Motion.Vy = y_speed;
            Set_Angle(angle, Tracing_Mode);
			Ask_Gray1();
			Detect_Y_Crossing();
        }
        break;
    }
	Clear_Encoder();
}
