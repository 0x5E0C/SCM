#ifndef __PCA_H
#define __PCA_H	

#include "bsp.h"

#define pca_adrr 0x80//器件地址

#define pca_mode1 0x0
#define pca_pre 0xFE

#define LED0_ON_L 0x6
#define LED0_ON_H 0x7
#define LED0_OFF_L 0x8
#define LED0_OFF_H 0x9

#define jdMIN  115 // minimum
#define jdMAX  590 // maximum
#define jd000  130 //0度对应4096的脉宽计数值
#define jd180  520 //180度对应4096的脉宽计算值

void pca_write(u8 adrr,u8 data);
u8 pca_read(u8 adrr);
void PCA_MG9XX_Init(float hz);
void pca_setfreq(float freq);
void pca_setpwm(u8 num, u32 on, u32 off);
void PCA_MG9XX(u8 num,u8 start_angle,u8 end_angle,u8 mode,u8 speed);
void shoottttt(u8 num,u8 start_angle,u8 end_angle,u8 mode,u8 speed);
#endif
