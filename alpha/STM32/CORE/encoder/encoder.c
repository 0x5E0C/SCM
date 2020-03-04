#include "encoder.h"

volatile float Encoder_Motor_A;
volatile float Encoder_Motor_B;
volatile float Encoder_Motor_C;
volatile float Encoder_Motor_D;

int Read_Encoder(u8 TIMX)
{
    short Encoder_TIM;
    switch(TIMX)
    {
    case 2:
        Encoder_TIM = (short)TIM2 -> CNT;
        TIM2 -> CNT = 0;
        if(Encoder_TIM > 15000)
        {
            Encoder_TIM -= 30000;
        }
        Encoder_Motor_A += Encoder_TIM;
        break;
    case 3:
        Encoder_TIM = (short)TIM3 -> CNT;
        TIM3 -> CNT = 0;
        if(Encoder_TIM > 15000)
        {
            Encoder_TIM -= 30000;
        }
        Encoder_Motor_B += Encoder_TIM;
        break;
    case 4:
        Encoder_TIM = (short)TIM4 -> CNT;
        TIM4 -> CNT = 0;
        if(Encoder_TIM > 15000)
        {
            Encoder_TIM -= 30000;
        }
        Encoder_Motor_C += Encoder_TIM;
        break;
    case 5:
        Encoder_TIM = (short)TIM5 -> CNT;
        TIM5 -> CNT = 0;
        if(Encoder_TIM > 15000)
        {
            Encoder_TIM -= 30000;
        }
        Encoder_Motor_D += Encoder_TIM;
        break;
    default:
        Encoder_TIM = 0;
    }
    return Encoder_TIM;
}

void Calculate_Distance()
{
    Global_Motion.X_Distance = (-Encoder_Motor_A + Encoder_Motor_B + Encoder_Motor_C - Encoder_Motor_D) / 4 / 1560 * 3.14 * 58 * 2 * cos_45;
    Global_Motion.Y_Distance = (-Encoder_Motor_A - Encoder_Motor_B + Encoder_Motor_C + Encoder_Motor_D) / 4 / 1560 * 3.14 * 58 * 2 * sin_45;
    Global_Motion.S_Distance = (float)sqrt(Global_Motion.X_Distance * Global_Motion.X_Distance + Global_Motion.Y_Distance * Global_Motion.Y_Distance);
}

void Clear_Encoder()
{
    Encoder_Motor_A = 0;
    Encoder_Motor_B = 0;
    Encoder_Motor_C = 0;
    Encoder_Motor_D = 0;
    Global_Motion.X_Distance = 0;
    Global_Motion.Y_Distance = 0;
	Global_Motion.S_Distance = 0;
}
