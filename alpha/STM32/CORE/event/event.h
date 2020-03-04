#ifndef _EVENT_H
#define _EVENT_H

#include "bsp.h"

#define Red  0
#define Blue 1

#define Up   0
#define Down 1
#define Put_Yellow_Ball  2
#define Put_Target_Ball  3
#define Close 4

extern u8 color;
extern u32 time_count;

void Choose_Color(void);
void Enter_Map(void);
void Enter_Line(void);
void Go_To_Red_Workplace(void);
void Go_To_Blue_Workplace(void);
void Adjust(void);
void Call_Openmv(void);
void Servo_Event(u8 event);
void Go_To_Red_Storehouse(void);
void Go_To_Blue_Storehouse(void);
void Go_Back_Home(void);
void Correct_Gyroscope(void);
void Execute_Process(void);
void Execute_Red_Process(void);
void Execute_Blue_Process(void);

#endif
