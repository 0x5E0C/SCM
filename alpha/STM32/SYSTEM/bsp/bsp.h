#ifndef _BSP_H
#define _BSP_H

#include <stdio.h>
#include <string.h>
#include <float.h>
#include <stdbool.h>
#include <math.h>
#include "sys.h"
#include "priority.h"
#include "stm32f10x.h"
#include "delay.h"
#include "usart1.h"
#include "usart2.h"
#include "usart3.h"
#include "uart4.h"
#include "uart5.h"
#include "timer1.h"
#include "timer8.h"
#include "timerx.h"
#include "iic.h"
#include "pid.h"
#include "motor.h"
#include "encoder.h"
#include "servo.h"
#include "gyroscope.h"
#include "gray.h"
#include "map.h"
#include "led.h"
#include "podf.h"
#include "button.h"
#include "event.h"
#include "infrared.h"
#include "pca9685.h"


#define Global_Speed 90

void BSP_Init(void);
void PID_Total_Init(void);

#endif
