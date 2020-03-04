#ifndef _UART4_H
#define _UART4_H

#include "bsp.h"

#define UART4_REC_LEN 50

extern u8 UART4_RX_BUF[UART4_REC_LEN];
extern u8 UART4_byteNum;

void UART4_Send(u8 data);
void Gray2_UART4_Init(u32 bound);

#endif
