#ifndef __SYSTEMTASK_H
#define __SYSTEMTASK_H

#include "config.h"
#include "stdio.h"
#include "task_param.h"
#include "clock_param.h"
#include "timer.h"
#include "infraRemote.h"
#include "usart.h"
#include "beep.h"
#include "led.h"
#include "key.h"
#include "SD3078.h"
#include "adc.h"
#include "delay.h" 
#include "esp12s.h"
#include "stdlib.h"
#include <stdarg.h>
#include "stdio.h"
#include <string.h>
#include "cJSON.h"
#include "HCMS.h"


extern tasksStatusObject tasksStatus;

void systemInit(void);
void systemLoop(void);
void IWDG_Init(u8 prer,u16 rlr);//ø¥√≈π∑
#endif
