#include "infrared.h"

void Infrared_Init()
{
	RCC->APB2ENR |= 1 << 6;
	GPIOE->CRH &= 0xFFFF00FF;
    GPIOE->CRH |= 0x00004400;	
}

