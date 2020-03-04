/*README*/

#include "bsp.h"

int main()
{
	Stm32_Clock_Init(9);
    delay_init(72);
    BSP_Init();
	Choose_Color();
	Execute_Process();
    while(1);
}

 




