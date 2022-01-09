#include "clock_param.h"
#include "config.h"

enum clockShowSwitch_e showMode = NormalShow;
uint8_t nixieTempMemory[6] = {0};
uint8_t setPos = 0;

clockEventObject clock = 
{
	.timeRead.sec = 0,
	.timeRead.min = 0,
	.timeRead.hour = 0,
	.timeRead.day = 0,
	.timeRead.date = 0,
	.timeRead.month = 0,
	.timeRead.year = 0,

	.timeSet.sec = 0,
	.timeSet.min = 0,
	.timeSet.hour = 0,
	.timeSet.day = 0,
	.timeSet.date = 0,
	.timeSet.month = 0,
	.timeSet.year = 0,

	.alarmSet1.min = 0,
	.alarmSet1.hour = 0,
	.alarmSet1.day = 0,
	
	.alarmSet2.min = 0,
	.alarmSet2.hour = 0,
	.alarmSet2.day = 0,
	
	.alarmBeepFlag = 0,
	.alarmTemper = 0,
	.alarmSetFlag = 0,
};

