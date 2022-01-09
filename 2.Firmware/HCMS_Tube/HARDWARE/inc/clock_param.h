#ifndef __CLOCK_PRARAM_H
#define __CLOCK_PRARAM_H

#include "sys.h"
#include "stdbool.h"

enum clockShowSwitch_e
{
	NormalShow = 1,
	DateShow	 = 2,
//	YearShow	 = 3,
	TemperShow = 3,
	AlarmSetShow = 4,
	nixieShowOff = 5,
};

enum alarm_e
{
	alarm1 = 1,
	alarm2 = 2,
	setFinishFlag,
};

typedef struct
{
	uint8_t sec; /*00-59*/
	uint8_t min; /*00-59*/
	uint8_t hour; /*00-23*/
	uint8_t day; /*1-7*/
	uint8_t date; /*01-31*/
	uint8_t month; /*01-12*/
	uint8_t year; /*00-99*/
}normalTimeObject;

typedef struct
{
	uint8_t min; /*00-59*/
	uint8_t hour; /*00-59*/
	uint8_t day; /*1-7*/
	uint8_t sec; /*1-7*/
}alarmSetTimeObject;

typedef struct
{
	normalTimeObject timeRead;
	normalTimeObject timeSet;
	alarmSetTimeObject alarmSet1;
	alarmSetTimeObject alarmSet2;
	uint8_t alarmBeepFlag;
	float alarmTemper;
	uint8_t alarmSetFlag;
}clockEventObject;
extern clockEventObject clock;

extern enum clockShowSwitch_e showMode;
extern uint8_t nixieTempMemory[6];
extern uint8_t setPos;

#endif

