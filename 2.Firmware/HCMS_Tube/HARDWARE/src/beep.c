#include "beep.h"

void beepInit(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_SetBits(GPIOA, GPIO_Pin_3);
}

void beepCmd(uint8_t newState)
{
	if(newState == ENABLE)
		GPIO_ResetBits(GPIOA, GPIO_Pin_3);
	else
		GPIO_SetBits(GPIOA, GPIO_Pin_3);
}