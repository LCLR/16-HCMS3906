#include <MX6921.h>
//#include <led.h>
#include "delay.h"
#include "ds3231.h"
#include "clock_param.h"
#include "systemTask.h"

void MX6921_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	  //使能PB,PE端口时钟
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;				       
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		   
	GPIO_Init(GPIOA, &GPIO_InitStructure);					       
	GPIO_ResetBits(GPIOA,GPIO_Pin_7);						           
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;              
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;        
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);                 
	GPIO_ResetBits(GPIOA,GPIO_Pin_6);		                   

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;		
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		   
	GPIO_Init(GPIOB, &GPIO_InitStructure);					       
	GPIO_SetBits(GPIOB,GPIO_Pin_1|GPIO_Pin_0);						 
}

u32 Duan[10] = {0x0c017, 0x08002, 0x18015, 0x18016, 0x1c002, 
								0x14016, 0x14017, 0x08012, 0x1c017, 0x1c012};
u32 Wei[10] = {0x00000, 0x01000, 0x00020, 0x00800, 0x00040,
							 0x00400, 0x00080, 0x00100, 0x00200, 0x02000};
u32 Time = 0x00000;
unsigned int i, k, j;
u8 Hour = 12, Min = 34, Sec = 56;

void TIM2_IRQHandler(void)
{
	i++;
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)  //检查TIM3更新中断发生与否
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);  //清除TIMx更新中断标志 
		if (i <= 50)
			MX6921_Send_Data(Duan[clock.timeRead.hour / 10] | Wei[8]);
		else if ((i > 100) && (i <= 150))
			MX6921_Send_Data(Duan[clock.timeRead.hour % 10] | Wei[7]);
		else if ((i > 200) && (i <= 250))
			MX6921_Send_Data(Duan[clock.timeRead.min / 10] | Wei[5]);
		else if ((i > 300) && (i <= 350))
			MX6921_Send_Data(Duan[clock.timeRead.min % 10] | Wei[4]);
		else if ((i > 400) && (i <= 450))
			MX6921_Send_Data(Duan[clock.timeRead.sec / 10] | Wei[2]);
		else if ((i > 500) && (i <= 550))
			MX6921_Send_Data(Duan[clock.timeRead.sec % 10] | Wei[1]);
		else if ((i > 600) && (i <= 650)) 
			MX6921_Send_Data(0x0000F | ((clock.timeRead.sec % 2) << 13 ));
		else if ((i > 700) && (i <= 750)) 
			MX6921_Send_Data(0x10000 | Wei[3] | Wei[6]);
		else if (i > 800) 
			i = 0;
	}
}






void MX6921_Send_Data(u32 Data)
{
	for (k = 0; k < N; k++)
	{
		DIN = (Data >> k) & 0x00001;
		CLK = 1;
		__NOP();
		CLK = 0;
		__NOP();
	}
	
	LOAD = 1;
	__NOP();
	LOAD = 0;
	__NOP();
}

