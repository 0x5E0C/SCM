#include "button.h"

void Button_Init()
{
	RCC->APB2ENR |= 1 << 8;
	GPIOG->CRH &= 0xFFF0000F;
    GPIOG->CRH |= 0x00088880;
}	
