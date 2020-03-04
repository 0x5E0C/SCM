#ifndef _INFRARED_H
#define _INFRARED_H

#include "bsp.h"

#define Red_Infrared  PEin(10)
#define Blue_Infrared PEin(11)

void Infrared_Init(void);

#endif
