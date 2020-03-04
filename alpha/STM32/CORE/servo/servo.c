#include "servo.h"

void Set_Servo_Angle(u8 id, u16 angle)
{
    int pwm = (2000 / 180 * angle + 500);
    switch(id)
    {
    case 1:
        TIM1->CCR1 = pwm;
        break;
    case 2:
        TIM1->CCR2 = pwm;
        break;
    case 3:
        TIM1->CCR3 = pwm;
        break;
    case 4:
        TIM1->CCR4 = pwm;
        break;
    default:
        break;
    }
}
