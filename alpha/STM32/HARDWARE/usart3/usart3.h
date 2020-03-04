#ifndef _USART3_H
#define _USART3_H

#include "bsp.h"

#define USART3_REC_LEN 66

extern u8 USART3_RX_BUF[USART3_REC_LEN];
extern u8 USART3_byteNum;

void Gyro_USART3_Init(u32 bound);

#endif
