#include "motor.h"

volatile Motion Global_Motion;

void Motor_Drive(int SpeedA, int SpeedB, int SpeedC, int SpeedD)
{
    if(SpeedA > 0)
    {
        A1 = 1;
        A2 = 0;
        PWMA = SpeedA;
    }
    else if(SpeedA < 0)
    {
        A1 = 0;
        A2 = 1;
        PWMA = -SpeedA;
    }
    else
    {
        A1 = 0;
        A2 = 0;
        PWMA = 0;
    }

    if(SpeedB > 0)
    {
        B1 = 1;
        B2 = 0;
        PWMB = SpeedB;
    }
    else if(SpeedB < 0)
    {
        B1 = 0;
        B2 = 1;
        PWMB = -SpeedB;
    }
    else
    {
        B1 = 0;
        B2 = 0;
        PWMB = 0;
    }

    if(SpeedC > 0)
    {
        C1 = 1;
        C2 = 0;
        PWMC = SpeedC;
    }
    else if(SpeedC < 0)
    {
        C1 = 0;
        C2 = 1;
        PWMC = -SpeedC;
    }
    else
    {
        C1 = 0;
        C2 = 0;
        PWMC = 0;
    }
    if(SpeedD > 0)
    {
        D1 = 1;
        D2 = 0;
        PWMD = SpeedD;
    }
    else if(SpeedD < 0)
    {
        D1 = 0;
        D2 = 1;
        PWMD = -SpeedD;
    }
    else
    {
        D1 = 0;
        D2 = 0;
        PWMD = 0;
    }
}

void Move()
{
    PID_MotorA.ActualValue = Read_Encoder(2);
    PID_MotorB.ActualValue = Read_Encoder(3);
    PID_MotorC.ActualValue = Read_Encoder(4);
    PID_MotorD.ActualValue = Read_Encoder(5);
    PID_MotorA.SetValue = -cos_45 * Global_Motion.Vx - sin_45 * Global_Motion.Vy - L * Global_Motion.W;
    PID_MotorB.SetValue = cos_45 * Global_Motion.Vx - sin_45 * Global_Motion.Vy - L * Global_Motion.W;
    PID_MotorC.SetValue = cos_45 * Global_Motion.Vx + sin_45 * Global_Motion.Vy - L * Global_Motion.W;
    PID_MotorD.SetValue = -cos_45 * Global_Motion.Vx + sin_45 * Global_Motion.Vy - L * Global_Motion.W;
	if(Global_Motion.Vx==0 && Global_Motion.Vy==0 && Global_Motion.W==0)
	{
		Motor_Drive(0,0,0,0);
	}
	else
	{
		Motor_Drive(Incremental_PID(&PID_MotorA),Incremental_PID(&PID_MotorB),Incremental_PID(&PID_MotorC),Incremental_PID(&PID_MotorD));
	}
}

void Stop(u16 time)
{
	Global_Motion.Vx=0;
	Global_Motion.Vy=0;
	Global_Motion.W=0;
	delay_ms(time);
}





