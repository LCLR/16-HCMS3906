#ifndef __TIMER_H
#define __TIMER_H

#include "config.h"
#include "systemTask.h"

#define CYCLE_10_MS			10
#define CYCLE_300_MS		300

#define RATE_READ_EXECUTE(RATE_MS,TICK)	((TICK%RATE_MS == 0))

void TIM4_Int_Init(u16 arr,u16 psc);
void TIM2_Int_Init(u16 arr,u16 psc);
 
#endif
