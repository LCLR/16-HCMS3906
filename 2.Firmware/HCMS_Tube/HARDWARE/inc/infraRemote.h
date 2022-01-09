#ifndef __INFRAREMOTE_H
#define __INFRAREMOTE_H

#include "sys.h"

#define infraPin		PBin(0)
#define REMOTE_ID		0

typedef struct
{
	uint8_t bcodeSta;
	uint16_t downVal;
	uint32_t bcodeRec;
	 
	uint8_t pressCnt;
}infraRecStatus_t;
extern infraRecStatus_t infraRecStatus;

//enum infraKeyValue_e
//{
//	INFRA_NULL = 0,
//	INFRA_EQ = 144,
//	INFRA_CH_LESS = 162,
//	INFRA_CH = 98,
//	INFRA_CH_PLUS = 226,
//	INFRA_PREV = 34,
//	INFRA_NEXT = 2,
//	INFRA_PP = 194,
//	INFRA_VOL_LESS = 224,
//	INFRA_VOL_PLUS = 168,
//	INFRA_0 = 104,
//	INFRA_100_PLUS = 152,
//	INFRA_200_PLUS = 176,
//	INFRA_1 = 48,
//	INFRA_2 = 24,
//	INFRA_3 = 122,
//	INFRA_4 = 16,
//	INFRA_5 = 56,
//	INFRA_6 = 90,
//	INFRA_7 = 66,
//	INFRA_8 = 74,
//	INFRA_9 = 82,
//};

enum infraKeyValue_e
{
	INFRA_NULL = 0xff,
	INFRA_0 = 0,
	INFRA_1,
	INFRA_2,
	INFRA_3,
	INFRA_4,
	INFRA_5,
	INFRA_6,
	INFRA_7,
	INFRA_8,
	INFRA_9,
	INFRA_EQ,
	INFRA_CH_LESS,
	INFRA_CH,
	INFRA_CH_PLUS,
	INFRA_PREV,
	INFRA_NEXT,
	INFRA_PP,
	INFRA_VOL_LESS,
	INFRA_VOL_PLUS,
	INFRA_100_PLUS,
	INFRA_200_PLUS, 
};

void infraRemote_Init(void);
uint8_t infraRemote_Scan(void);
void infraAnalysis(uint8_t value);

#endif
