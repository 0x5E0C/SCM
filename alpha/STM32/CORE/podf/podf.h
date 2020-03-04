#ifndef _PODF_H
#define _PODF_H

#include "bsp.h"

typedef struct _PODF 
{
	float a0;
	float a1;
	float a2;
	float a3;
	float a4;
	float a5;
	float q_t;
	float v_t;
	float acc_t;
	float t1;
	float t0;
} PODF;

extern PODF PODF_Vy,PODF_Vx,PODF_W;

float podf_cal(PODF*podf);
void podf_reinit(PODF*podf,float q0,float q1,float v0,float v1,float acc0,float acc1,float t0,float t1);

#endif

