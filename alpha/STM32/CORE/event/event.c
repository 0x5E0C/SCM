#include "event.h"

u8 color;
u32 time_count;

void Choose_Color()
{
	while(1)
	{
		if(Red_Infrared==0)
		{
			color=Red;
			break;
		}
		else if(Blue_Infrared==0)
		{
			color=Blue;
			break;
		}
	}
    PID_Total_Init();
}

void Enter_Map()
{
	Servo_Event(Close);
	Servo_Event(Down);
	gyro.Degrees_0=0;
	gyro.Degrees_90=90;
	gyro.Degrees_180=180;
	gyro.Degrees_270=270;
    while(Global_Motion.S_Distance < 150)
    {
        Global_Motion.Vx = 0;
        Global_Motion.Vy = 40;
        Set_Angle(0, Tracing_Mode);
    }
    while(Global_Motion.Vy > 1)
    {
        Global_Motion.Vx = 0;
        Global_Motion.Vy = Caculate_Gray_PID(Gray2);
        Ask_Gray2();
        Set_Angle(0, Tracing_Mode);
        delay_ms(20);
    }
    Clear_Encoder();
	if(color==Red)
	{
		Set_Axis(1,0);
	}
	else if(color==Blue)
	{
		Set_Axis(3,0);
	}
	Stop(1000);
}

void Enter_Line()
{
	Move_Distance(-60,60,0,552,No_Tracing);
	Global_Motion.Vx=0;
}

void Go_To_Red_Workplace()
{
	Move_By_Tracing(1,3,Global_Speed,Y_First,no_stop);
	Move_Distance(0,Global_Speed,0,360,Y_Tracing);
	Stop(1000);
	podf_reinit(&PODF_Vx, 0, 860, 0, 0, 0, 0, millis, millis + 2500);
    while(millis < PODF_Vx.t1)
    {
        Global_Motion.Vx = -podf_cal(&PODF_Vx) * 20 * 1560 / 3.14 / 58;
        Global_Motion.Vy = 0;
		Set_Angle(0,Tracing_Mode);
	}
	Stop(1000);
	Set_Angle(180,Rotation_Mode);
	Servo_Event(Up);
	Stop(1000);	
	while(Button1==0 || Button2==0)
	{
		Global_Motion.Vx=0;
		Global_Motion.Vy=30;
	}
	Global_Motion.Vy=20;
	delay_ms(1000);
	Stop(1000);
}

void Go_To_Blue_Workplace()
{
	Move_By_Tracing(3,1,Global_Speed,Y_First,stop);
	Move_By_Tracing(1,1,Global_Speed,Y_First,no_stop);
	Move_Distance(-Global_Speed/1.4,Global_Speed/1.4,0,618,No_Tracing);
	Servo_Event(Up);
	Stop(1000);
}

void Adjust()
{
	Global_Motion.Vx=Caculate_Gray_PID(Gray1);
	Global_Motion.Vy=0;
	while(Global_Motion.Vx!=0)
	{	
		Global_Motion.Vx=Caculate_Gray_PID(Gray1);
		Global_Motion.Vy=0;
		Ask_Gray1();
	}
	Stop(1000);
}

void Call_Openmv()
{
	if(color==Red)
	{
		UART5_Send(0xFF);
		delay_ms(1);
		UART5_Send(0x01);
		delay_ms(1);
		UART5_Send(0x23);
		delay_ms(1);
	}
	else if(color==Blue)
	{
		UART5_Send(0xFF);
		delay_ms(1);
		UART5_Send(0x02);
		delay_ms(1);
		UART5_Send(0x23);
		delay_ms(1);
	}
}

void Servo_Event(u8 event)
{
	if(event==Up)
	{
		PCA_MG9XX(15,0,60,0,1);
	}
	else if(event==Down)
	{
		PCA_MG9XX(15,0,120,0,1);
	}
	else if(event==Put_Yellow_Ball)
	{
		PCA_MG9XX(1,0,45,0,1);
	}
	else if(event==Put_Target_Ball)
	{
		PCA_MG9XX(0,0,80,0,1);
	}
	else if(event==Close)
	{	
		PCA_MG9XX(0,0,40,0,1);
		PCA_MG9XX(1,0,100,0,1);
	}
}

void Servo_Down()
{
	PCA_MG9XX(15,0,120,0,1);
}

void Go_To_Red_Storehouse()
{
	int t;
	podf_reinit(&PODF_Vx, 0, 820, 0, 0, 0, 0, millis, millis + 2500);
    while(millis < PODF_Vx.t1)
    {
        Global_Motion.Vx = podf_cal(&PODF_Vx) * 20 * 1560 / 3.14 / 58;
        Global_Motion.Vy = 0;
		Set_Angle(0,Tracing_Mode);
	}
	Move_By_Tracing(1,5,Global_Speed,Y_First,stop);
	Move_Distance(40,0,gyro.Degrees_0,780+390,No_Tracing);
	Set_Axis(2,5);
	Move_By_Tracing(3,5,Global_Speed,Y_First,stop);
	Set_Angle(gyro.Degrees_180,Rotation_Mode);
	Move_By_Tracing(3,2,Global_Speed,Y_First,no_stop);
	Move_Distance(0,Global_Speed,gyro.Degrees_180,390,Y_Tracing);
	Stop(1000);
	podf_reinit(&PODF_Vx, 0, 780, 0, 0, 0, 0, millis, millis+2500);
    while(millis < PODF_Vx.t1)
    {
        Global_Motion.Vx = -podf_cal(&PODF_Vx) * 20 * 1560 / 3.14 / 58;
        Global_Motion.Vy = 0;
		Set_Angle(gyro.Degrees_180,Tracing_Mode);
	}
	Stop(1000);
	Set_Angle(90,Rotation_Mode);
	Stop(1000);
	Clear_Encoder();
	Move_Distance(0,-40,90,300,No_Tracing);
	Stop(1000);
	Servo_Event(Put_Target_Ball);
	Stop(1000);
	Stop(1000);
	Move_Distance(0,40,90,300,No_Tracing);
	Stop(1000);
	Set_Angle(gyro.Degrees_180,Rotation_Mode);	
	for(t=0;t<90;t++)
	{
		Stop(1000);
	}
	Stop(1000);
}

void Go_To_Blue_Storehouse()
{
	int t;
	Move_Distance(0,-Global_Speed,gyro.Degrees_0,350,No_Tracing);
	Servo_Event(Down);
	Stop(1000);
	Move_Distance(40,0,gyro.Degrees_0,780,No_Tracing);
	Set_Axis(1,1);
	Clear_Encoder();
	Move_By_Tracing(1,2,Global_Speed,Y_First,stop);
	Move_By_Tracing(4,2,Global_Speed,Y_First,stop);
	Move_By_Tracing(4,3,Global_Speed,X_First,no_stop);
	Move_Distance(0,Global_Speed,gyro.Degrees_0,390,No_Tracing);
	Stop(1000);
	Set_Angle(gyro.Degrees_90,Rotation_Mode);
	Stop(1000);
	Clear_Encoder();
	Move_Distance(0,-40,gyro.Degrees_90,300,No_Tracing);
	Stop(1000);
	Servo_Event(Put_Target_Ball);
	Stop(1000);
	Stop(1000);
	Move_Distance(0,40,gyro.Degrees_90,300,No_Tracing);
	Stop(1000);
	Set_Angle(180,Rotation_Mode);
	for(t=0;t<90;t++)
	{
		Stop(1000);
	}
	Move_Distance(40,0,80,780,No_Tracing);
}

void Go_Back_Home()
{
	if(color==Red)
	{
		Set_Axis(3,2);
		Move_By_Tracing(2,1,Global_Speed,Y_First,no_stop);
		Move_Distance(0.37*Global_Speed,Global_Speed,gyro.Degrees_180,1220,No_Tracing);		
		Stop(1000);
	}
	else if(color==Blue)
	{
		Set_Axis(3,4);
		Move_By_Tracing(3,1,Global_Speed,Y_First,no_stop);
		Move_Distance(0.37*Global_Speed,Global_Speed,gyro.Degrees_180,1220,No_Tracing);
		Stop(1000);
	}
}

void Correct_Gyroscope()
{
	if(color==Red)
	{
		Move_Distance(0,-40,180,150,No_Tracing);
		Servo_Event(Down);
		Stop(1000);
		Set_Angle(0,Custom_Mode);
		Stop(1000);	
		while(Button3==0 || Button4==0)
		{
			Global_Motion.Vx=0;
			Global_Motion.Vy=-30;
		}
	}
	else if(color==Blue)
	{
		while(Button1==0 || Button2==0)
		{
			Global_Motion.Vx=0;
			Global_Motion.Vy=30;
		}
	}
	Global_Motion.Vy=20;
	delay_ms(1000);
	Stop(1000);
	gyro.Degrees_0=gyro.yaw;
	if(gyro.Degrees_0>180)
	{		
		gyro.Degrees_90=gyro.Degrees_0-270;
		gyro.Degrees_180=gyro.Degrees_0-180;
		gyro.Degrees_270=gyro.Degrees_0-90;
	}
	else
	{
		gyro.Degrees_90=gyro.Degrees_0+90;
		gyro.Degrees_180=gyro.Degrees_0+180;
		gyro.Degrees_270=gyro.Degrees_0+270;
	}
	Clear_Encoder();
}

void Execute_Process()
{
	if(color==Red)
	{
		Execute_Red_Process();
	}
	else if(color==Blue)
	{
		Execute_Blue_Process();
	}
}
	
void Execute_Red_Process()
{
	Enter_Map();
	Enter_Line();
	Go_To_Red_Workplace();
	Adjust();
	Call_Openmv();
	while(finish_flag==0);
	Correct_Gyroscope();
	Move_Distance(0,40,gyro.Degrees_0,340,No_Tracing);
	Stop(1000);
	Go_To_Red_Storehouse();
	Go_Back_Home();
}

void Execute_Blue_Process()
{
	Enter_Map();
	Go_To_Blue_Workplace();
	Correct_Gyroscope();
	Adjust();
	Call_Openmv();
  	while(finish_flag==0);
	Go_To_Blue_Storehouse();
	Go_Back_Home();	
}
