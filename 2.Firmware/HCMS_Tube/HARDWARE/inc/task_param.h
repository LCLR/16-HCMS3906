#ifndef __TASK_PARAM_H
#define __TASK_PARAM_H

#include "config.h"

typedef struct
{
	uint8_t ALM_UPDATE;
	uint8_t ALM_Flag;
	uint8_t VFD_UPDATE;
	uint8_t INFRA_UPDATE;
	uint8_t BEEP_UPDATE;
	uint8_t UART_UPDATE;
	uint8_t ADC_UPDATE;
	uint8_t Light_UPDATE;
	uint8_t KEY_UPDATE;
	uint8_t ESP_UPDATE;
	uint8_t UI_UPDATE;
	uint8_t WatchD_UPDATE;
}tasksStatusObject;

#endif

