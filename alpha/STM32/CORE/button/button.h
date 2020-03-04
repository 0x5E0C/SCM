#ifndef _BUTTON_H
#define _BUTTON_H

#include "bsp.h"

#define Button1 PGin(9)
#define Button2 PGin(10)
#define Button3 PGin(11)
#define Button4 PGin(12)

void Button_Init(void);

#endif
