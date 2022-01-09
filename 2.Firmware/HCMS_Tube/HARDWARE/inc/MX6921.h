#ifndef __MX6921_H
#define __MX6921_H

#include "sys.h"

#define CLK  PAout(7)
#define LOAD PBout(0)
#define DIN  PBout(1)
#define BLANK  PAout(6)
#define N 17
#define Dot 0x00008

void MX6921_Init(void);
void Time_Scan(u8 Hour, u8 Min, u8 Sec);
void MX6921_Send_Data(u32 Data);
void fluoScentTube_Refresh(void);

#endif
