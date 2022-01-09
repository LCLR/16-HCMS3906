#include "infraRemote.h"
#include "clock_param.h"
#include "SD3078.h"
#include "usart.h"
#include "M11BT.h"
#include "led.h"
#include "beep.h"
infraRecStatus_t infraRecStatus = {0};


extern u8 Show_Mode;
/*
EQ: 	144
CH-: 	162
CH:		98
CH+: 	226
|<<(PREV): 	34
>>|(NEXT):	2
>||(PP): 	194
-:	 	224
+:   	168
0:	 	104
100+:	152
200+:	176
1:		48
2:		24
3:		122
4:		16
5:		56
6:		90
7:		66
8:		74
9:		82
*/

void infraRemote_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_ICInitTypeDef  TIM_ICInitStructure;  
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 		
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOB, &GPIO_InitStructure);
 	GPIO_SetBits(GPIOB,GPIO_Pin_0);
	
	TIM_TimeBaseStructure.TIM_Period = 10000;
	TIM_TimeBaseStructure.TIM_Prescaler =(72-1); 
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

  TIM_ICInitStructure.TIM_Channel = TIM_Channel_3; 
  TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	
  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
  TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	
  TIM_ICInitStructure.TIM_ICFilter = 0x03; //配置输入滤波器,8个定时器时钟周期滤波
  TIM_ICInit(TIM3, &TIM_ICInitStructure);
 
	TIM_Cmd(TIM3,ENABLE);
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	TIM_ITConfig(TIM3, TIM_IT_Update|TIM_IT_CC3,ENABLE);
	
}

void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET)
	{
		if(infraRecStatus.bcodeSta & 0x80)
		{
			infraRecStatus.bcodeSta &= ~0x10;
			if((infraRecStatus.bcodeSta & 0x0F) == 0x00)
				infraRecStatus.bcodeSta |= 1<<6;
			if((infraRecStatus.bcodeSta & 0x0F) < 14)
				infraRecStatus.bcodeSta++;
			else
			{
				infraRecStatus.bcodeSta &= ~(1<<7);
				infraRecStatus.bcodeSta &= 0xF0;
			}
		}
	}
	if(TIM_GetITStatus(TIM3,TIM_IT_CC3)==SET)
	{
		if(infraPin)
		{
			TIM_OC3PolarityConfig(TIM3, TIM_ICPolarity_Falling);
			TIM_SetCounter(TIM3,0);
			infraRecStatus.bcodeSta |= 0x10;
		}
		else
		{
			infraRecStatus.downVal = TIM_GetCapture3(TIM3);
			TIM_OC3PolarityConfig(TIM3, TIM_ICPolarity_Rising);
			if(infraRecStatus.bcodeSta & 0x10)
			{
				if(infraRecStatus.bcodeSta & 0x80)
				{
					if(300 < infraRecStatus.downVal && infraRecStatus.downVal < 800)
					{
						infraRecStatus.bcodeRec <<= 1;
						infraRecStatus.bcodeRec |= 0;
					}
					else if(1400 < infraRecStatus.downVal && infraRecStatus.downVal < 1800)
					{
						infraRecStatus.bcodeRec <<= 1;
						infraRecStatus.bcodeRec |= 1;
					}
					else if(2200 < infraRecStatus.downVal && infraRecStatus.downVal < 2600)
					{
						infraRecStatus.pressCnt++;
						infraRecStatus.bcodeSta &= 0xF0;
					}
				}
				else if(4200 < infraRecStatus.downVal && infraRecStatus.downVal < 4700)
				{
					infraRecStatus.bcodeSta |= 1<<7;
					infraRecStatus.pressCnt = 0;
				}
			}
			infraRecStatus.bcodeSta &= ~(1<<4);
		}
	}
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update|TIM_IT_CC3);
}


uint8_t infraRemote_Scan(void)
{
	uint8_t sta = 0, t1, t2;
	
	if(infraRecStatus.bcodeSta & (1<<6)) //得到一个按键的所有信息了
	{
		t1 = infraRecStatus.bcodeRec >> 24;
		t2 = (infraRecStatus.bcodeRec >> 16) & 0xFF;
		if((t1==(uint8_t)~t2) && t1 == REMOTE_ID)
		{
			t1 = infraRecStatus.bcodeRec >> 8;
			t2 = infraRecStatus.bcodeRec;
			if(t1 == (uint8_t)~t2) //键值正确	 
			{
				sta = t1;
			}
		}
		if((sta==0) || ((infraRecStatus.bcodeSta & 0x80) == 0)) //按键数据错误/遥控已经没有按下了
		{
			infraRecStatus.bcodeSta &= ~(1<<6);
			infraRecStatus.pressCnt = 0;
		}
	}
	return sta;
}



void infraAnalysis(uint8_t value)
{
	enum infraKeyValue_e temp = INFRA_NULL;
	
	switch(value)
	{ 
		case 0: 	temp = INFRA_NULL; break;
		case 144: temp = INFRA_EQ; break;
		case 162: temp = INFRA_CH_LESS; break;
		case 98: 	temp = INFRA_CH; break;
		case 226: temp = INFRA_CH_PLUS; break;
		case 34: 	temp = INFRA_PREV; break;
		case 2: 	temp = INFRA_NEXT; break;
		case 194: temp = INFRA_PP; break;
		case 224: temp = INFRA_VOL_LESS; break;
		case 168: temp = INFRA_VOL_PLUS; break;
		case 104: temp = INFRA_0; break;
		case 152: temp = INFRA_100_PLUS; break;
		case 176: temp = INFRA_200_PLUS; break;
		case 48: 	temp = INFRA_1; break;
		case 24: 	temp = INFRA_2; break;
		case 122: temp = INFRA_3; break;
		case 16: 	temp = INFRA_4; break;
		case 56: 	temp = INFRA_5; break;
		case 90: 	temp = INFRA_6; break;
		case 66: 	temp = INFRA_7; break;
		case 74: 	temp = INFRA_8; break;
		case 82: 	temp = INFRA_9; break;
		default:  temp = INFRA_NULL; break;
	}
	if(temp == INFRA_NULL)
		return;
	
	if(temp == INFRA_CH)
	{
		    M11BT222A_BOOSTER=~M11BT222A_BOOSTER;
				LED1=~LED1;
	}
	else if(temp == INFRA_CH_LESS)
	{
		beepCmd(ENABLE);
	}	
	else if(temp == INFRA_CH_PLUS)
	{
		beepCmd(DISABLE);
	}
	else if(temp == INFRA_PREV)
	{
		if(Show_Mode==0X01)Show_Mode=0X10;	
		else Show_Mode=Show_Mode>>1;
	}
	else if(temp == INFRA_NEXT)
	{
		if(Show_Mode==0X10)Show_Mode=0X01;	
		else Show_Mode=Show_Mode<<1;
	}		
	else if(0<=temp&&temp<=9)
	{

	}
	else if(temp == INFRA_PP)
	{

	}
	else if(temp == INFRA_EQ)
	{

	}
}
