#ifndef _SysTick_H
#define _SysTick_H

#include "system.h"

void SysTick_Init(u8 SYSCLK);
void Delay_ms(u32 nms);
void Delay_us(u32 nus);
void Delay_xms(u32 nms);



#endif
