#ifndef _UART5_H
#define _UART5_H

#include "bsp.h"

#define UART5_REC_LEN 10

extern u8 finish_flag;

void UART5_Send(u8 data);
void Openmv_UART5_Init(u32 bound);

#endif
