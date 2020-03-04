#include "bsp.h"

int fputc(int ch, FILE* f)
{
    while((USART1->SR & 0X40) == 0);
    USART1->DR = (u8) ch;
    return ch;
}

void BSP_Init()
{
    USART1_Init(115200);
    Ultra_USART2_Init(9600);
    Gyro_USART3_Init(115200);
    Gray2_UART4_Init(115200);
    Openmv_UART5_Init(115200);
    Servo_TIM1_Init(19999, 71);
    Encoder_TIM2_Init();
    Encoder_TIM3_Init();
    Encoder_TIM4_Init();
    Encoder_TIM5_Init();
    PID_TIM6_Init(200, 7199);
    Motor_TIM8_Init(999, 71);
	LED_Init();
	Infrared_Init();
	PCA_MG9XX_Init(50);
}
void PID_Total_Init()
{
    PID_MotorA.P = 17.64;
    PID_MotorA.I = 3.2;
    PID_MotorA.D = 0;
    PID_MotorA.OutputMax = No_Max;
    PID_MotorA.OutputMin = No_Min;
	PID_MotorA.Threshold_I = No_Threshold_I;
    PID_Init(&PID_MotorA);

    PID_MotorB.P = 17.64;
    PID_MotorB.I = 3.2;
    PID_MotorB.D = 0;
    PID_MotorB.OutputMax = No_Max;
    PID_MotorB.OutputMin = No_Min;
	PID_MotorB.Threshold_I = No_Threshold_I;
    PID_Init(&PID_MotorB);

    PID_MotorC.P = 17.64;
    PID_MotorC.I = 3.2;
    PID_MotorC.D = 0;
    PID_MotorC.OutputMax = No_Max;
    PID_MotorC.OutputMin = No_Min;
	PID_MotorC.Threshold_I = No_Threshold_I;
    PID_Init(&PID_MotorC);

    PID_MotorD.P = 17.64;
    PID_MotorD.I = 3.2;
    PID_MotorD.D = 0;
    PID_MotorD.OutputMax = No_Max;
    PID_MotorD.OutputMin = No_Min;
	PID_MotorD.Threshold_I = No_Threshold_I;
    PID_Init(&PID_MotorD);

	PID_Gray1.P=5.5;
	PID_Gray1.I=0;
	PID_Gray1.D=0;
	PID_Gray1.OutputMax=No_Max;
	PID_Gray1.OutputMin=No_Min;
	PID_Gray1.Threshold_I = No_Threshold_I;
	PID_Init(&PID_Gray1);
	
	PID_Gray2.P=5;
	PID_Gray2.I=0;
	PID_Gray2.D=0;
	PID_Gray2.OutputMax=No_Max;
	PID_Gray2.OutputMin=No_Min;
	PID_Gray2.Threshold_I = No_Threshold_I;
	PID_Init(&PID_Gray2);

    PID_Gyro.P = 5;
    PID_Gyro.I = 0.0004;
    PID_Gyro.D = 0;
    PID_Gyro.OutputMax = 60;
    PID_Gyro.OutputMin = -60;
	PID_Gyro.Threshold_I = No_Threshold_I;
    PID_Init(&PID_Gyro);
	
}
