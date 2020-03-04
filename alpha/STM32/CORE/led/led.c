#include "led.h"

void LED_Init()
{	
	RCC->APB2ENR |= 1 << 8;
	GPIOG->CRH &= 0x0FFFFFFF;
    GPIOG->CRH |= 0x30000000;
	LED=1;
}
