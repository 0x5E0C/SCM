#include "pid.h"

volatile PID PID_MotorA, PID_MotorB, PID_MotorC, PID_MotorD;
volatile PID PID_Gray1, PID_Gray2;
volatile PID PID_Gyro;

void PID_Init(volatile PID* pid)
{
    pid->ActualValue = 0;
    pid->Err = 0;
    pid->Last_Err = 0;
    pid->Last_Err2 = 0;
}

float Incremental_PID(volatile PID* pid)
{
    pid->Err = pid->ActualValue - pid->SetValue;
    pid->OutputPoint += pid->P * (pid->Err - pid->Last_Err) +
                        pid->I * pid->Err +
                        pid->D * (pid->Err - 2 * pid->Last_Err + pid->Last_Err2);
    pid->Last_Err2 = pid->Last_Err;
    pid->Last_Err = pid->Err;
    if(pid->OutputPoint > pid->OutputMax)
    {
        pid->OutputPoint = pid->OutputMax;
    }
    else if(pid->OutputPoint < pid->OutputMin)
    {
        pid->OutputPoint = pid->OutputMin;
    }
    return pid->OutputPoint;
}

float Positional_PID(volatile PID* pid)
{
    pid->Err = pid->ActualValue - pid->SetValue;
    pid->Err_Sum += pid->Err;
    pid->OutputPoint += pid->P * pid->Err +
                        pid->I * pid->Err_Sum +
                        pid->D * (pid->Err - pid->Last_Err);
    pid->Last_Err = pid->Err;
    if(pid->OutputPoint > pid->OutputMax)
    {
        pid->OutputPoint = pid->OutputMax;
    }
    else if(pid->OutputPoint < pid->OutputMin)
    {
        pid->OutputPoint = pid->OutputMin;
    }
    return pid->OutputPoint;
}
