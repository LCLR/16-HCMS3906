#ifndef __BEEP_H
#define __BEEP_H

#include "sys.h"
#define Beep_IO PAout(4)
void beepInit(void);
void beepCmd(uint8_t newState);

#endif
