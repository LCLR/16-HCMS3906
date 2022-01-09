#include "systemTask.h"




#define Normal_Mode 0X01
#define Set_Mode    0X02
#define ALM_Mode    0X04
#define WIFI_Mode   0X08
#define GAME_Mode   0X10

tasksStatusObject tasksStatus = {0};
static uint32_t tick = 0;


Time_Def time_init={0x00,0x49,0x21,0x06,0x11,0x04,0x20};	//初始化实时时间
Time_Def Alarm_init={0x30,0x19,0x17,0x00,0x15,0x08,0x18};	//初始化报警时间
Time_Def sysTime;

 uint8_t SENDBUF[100];
 u8      Dis_BUF[16];
 u16 ADC_data    =0;
 u16 COUNT       =5;
 u16 IR_num      =0;
 u16 Point_flick =0;
 u16 UI_num      =0;
	u8 KEY_valu    =0;
	u8 Show_Mode   =0X00;
	u8 Check_sta   =0;
u16 Tem_int;
float Temperature=0;

void systemInit(void)
{
	uart1_init(115200);                  //串口1波特率
//	uart2_init(9600);                   //BLE蓝牙波特率
	uart3_init(115200);                  //ESP-12S通信波特率	
    TIM4_Int_Init(7200-1,10-1);          //状态机	
	infraRemote_Init();                  //红外遥控初始化   
    HCMS_init();                         //HCMS初始化   
	SD3078_Init();                       //时钟芯片初始化
	LED_Init();                          //LED初始化
	beepInit();                          //蜂鸣器初始化
	KEY_Init();                          //按键IO初始化	
    Adc_Init();                          //光强采集ADC初始化
    
    
    beepCmd(DISABLE);
    
//	RTC_WriteDate(&time_init);	
	Show_Mode=Normal_Mode;               //初始化显示模式
	RTC_ReadDate(&sysTime);
    
    HCMS_Brightness(LINE_1,10);
    HCMS_Brightness(LINE_2,10);

	printf("写入的初始时间为： \r\n");
	printf("%02X-%02X-%02X  %02X:%02X:%02X  星期%02X\r\n\r\n", \
	sysTime.year, sysTime.month, sysTime.day, sysTime.hour,\
	sysTime.minute, sysTime.second, sysTime.week);



#ifdef SD30XX_25XX	
/*************** 读出芯片的ID号演示 ****************/	
	I2CReadSerial(RTC_Address,ID_Address,8,data_Buf);
	printf("芯片64bit ID号为：\r\n");
	for (u8 i=0; i<8; i++)
	printf("0x%02X ", data_Buf[i]);
	printf("\r\n----------------------------\r\n\r\n");

/**************** 充电使能设置演示 *****************/
	data_Buf[0] = Chg_enable;
	I2CWriteSerial(RTC_Address,Chg_MG,1,data_Buf);

/************** 读出后备电池电压演示 ***************/	
	I2CReadSerial(RTC_Address,Bat_H8,2,VBAT_Buf);
	VBAT_VAL = (VBAT_Buf[0]>>7)*255 + VBAT_Buf[1];
	printf("VBAT脚的电池电压为：%d.%d%dV\r\n\r\n", VBAT_VAL/100, VBAT_VAL%100/10, VBAT_VAL%10);
#endif

    
    
//	IWDG_Init(6,2000);//看门狗初始化
}

void TIM4_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET) 
	{
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);   
		tick++;
//***************************************************
				if(RATE_READ_EXECUTE(20,tick))//vfd写入时间
		{                
			tasksStatus.VFD_UPDATE = true;
		}
//***************************************************		
				if(RATE_READ_EXECUTE(125,tick))//ESP-WIFI
		{
			tasksStatus.ESP_UPDATE = true;
		}		
//***************************************************				
		if(RATE_READ_EXECUTE(30,tick))    //光强采集
		{
			tasksStatus.ADC_UPDATE = true;
		}
//***************************************************				
		if(RATE_READ_EXECUTE(1000,tick))    //看门狗喂狗
		{
			tasksStatus.WatchD_UPDATE = true;
		}		
//***************************************************				
		if(RATE_READ_EXECUTE(500,tick))    //闹钟触发
		{
			tasksStatus.BEEP_UPDATE = true;
		}			
//***************************************************		
		if(RATE_READ_EXECUTE(50,tick))     //光强调整
		{
			tasksStatus.Light_UPDATE = true;
		}		
//***************************************************
		if(RATE_READ_EXECUTE(60,tick))  //按键检测
		{
			tasksStatus.KEY_UPDATE = true;
		}	
//***************************************************		
		if(RATE_READ_EXECUTE(10,tick))    //红外遥控
		{
			tasksStatus.INFRA_UPDATE = true;
		}
//***************************************************		
		if(RATE_READ_EXECUTE(120,tick))    //UI界面
		{
			tasksStatus.UI_UPDATE = true;
		}			
//***************************************************

//***************************************************
//***************************************************
		if(RATE_READ_EXECUTE(600,tick))  //串口打印
		{
			tasksStatus.UART_UPDATE = true;
		}
	}		
}
//***************************************************




static uint32_t myabs(uint32_t a, uint32_t b)
{
	int32_t temp;
	temp = a-b;
	if(temp<0)	return (-temp);
	else				return temp;
}



void systemLoop(void)
{		
//-------------------------------------------------------	
	if(tasksStatus.UART_UPDATE == true)	//串口打印数据
{
//        VBAT_VAL = (VBAT_Buf[0]>>7)*255 + VBAT_Buf[1];
//        printf("VBAT脚的电池电压为：%d.%d%dV\r\n\r\n", VBAT_VAL/100, VBAT_VAL%100/10, VBAT_VAL%10);
//    
        RTC_ReadDate(&sysTime);
//    
//		Point_flick=~Point_flick;//时间冒号闪烁
        printf("%02X-%02X-%02X  %02X:%02X:%02X  星期%02X\r\n\r\n", \
        sysTime.year, sysTime.month, sysTime.day, sysTime.hour,\
        sysTime.minute, sysTime.second, sysTime.week);
        printf("%s\r\n",Dis_BUF);
        tasksStatus.UART_UPDATE = false;
}

//-------------------------------------------------------
//闹钟响应
	if(tasksStatus.BEEP_UPDATE == true && tasksStatus.ALM_Flag == true)	
{
	Beep_IO=~Beep_IO;
	Show_Mode=ALM_Mode;
}
//-------------------------------------------------------
	if(tasksStatus.UI_UPDATE == true)	//UI界面
{	
        HCMS_Write_I_Str("LCLR");        
        HCMS_Write_II_Str(Dis_BUF);

//        OLED_Show_UnIntNum(12345678, 8);
	tasksStatus.UI_UPDATE = false;
}

//-------------------------------------------------------
	if(tasksStatus.VFD_UPDATE == true)	//VFD时间更新
{
//    RTC_WriteDate(&time_init);
    RTC_ReadDate(&sysTime);
    
    Dis_BUF[0] =BCDtoNum(sysTime.year)%100/10+'0';
    Dis_BUF[1] =BCDtoNum(sysTime.year)%100%10+'0';
    Dis_BUF[2] =BCDtoNum(sysTime.month) /10+'0';
    Dis_BUF[3] =BCDtoNum(sysTime.month) %10+'0';
    Dis_BUF[4] =BCDtoNum(sysTime.day) %10+'0';
    Dis_BUF[5] =BCDtoNum(sysTime.day) %10+'0';    
    Dis_BUF[6] ='<';    
    Dis_BUF[7] =BCDtoNum(sysTime.hour) /10+'0';
    Dis_BUF[8] =BCDtoNum(sysTime.hour) % 10+'0';
    Dis_BUF[9] =':';    
    Dis_BUF[10]=BCDtoNum(sysTime.minute) /10+'0';
    Dis_BUF[11]=BCDtoNum(sysTime.minute) %10+'0';
    Dis_BUF[12]=':';
    Dis_BUF[13]=BCDtoNum(sysTime.second) /10+'0';
    Dis_BUF[14]=BCDtoNum(sysTime.second) %10+'0';
    Dis_BUF[15]='>';
	tasksStatus.VFD_UPDATE = false;
}
//-------------------------------------------------------
	if(tasksStatus.KEY_UPDATE == true)	//按键处理
{
	if(!KEY1)
	{
		delay_ms(10);
		if(!KEY1)
		{
			while(!KEY1);
			COUNT++;
			if(COUNT>10)COUNT=5;
		}
	}
	else if(!KEY2)
	{
		delay_ms(10);
		if(!KEY2)
		{
			while(!KEY2);
			COUNT--;
			if(COUNT<1)COUNT=5;
		}
	}
		tasksStatus.KEY_UPDATE = false;
}
//-------------------------------------------------------
	if(tasksStatus.ADC_UPDATE == true)	//光强更新
{	
	ADC_data=Get_Adc_Average(9,5);
	
	tasksStatus.ADC_UPDATE = false;
}
//-------------------------------------------------------
	if(tasksStatus.ESP_UPDATE == true)	//ESP处理
{
	tasksStatus.ESP_UPDATE = false;
}
//-------------------------------------------------------
	if(tasksStatus.WatchD_UPDATE == true)	//喂狗
{
	IWDG_ReloadCounter();
	tasksStatus.WatchD_UPDATE = false;
}
//-------------------------------------------------------
	if(tasksStatus.Light_UPDATE == true) //光强调整
{	
	
	tasksStatus.Light_UPDATE = false;
}
//-------------------------------------------------------
	if(tasksStatus.INFRA_UPDATE == true)//红外遥控
	{
		static uint32_t infiraLastWakeTime = 0;
		uint8_t keyValue = 0;
		enum infraKeyValue_e infraKeyValue = INFRA_NULL;
		keyValue = infraRemote_Scan();
		if(keyValue)
		{
			if(myabs(infiraLastWakeTime, tick) >= 500)
				infiraLastWakeTime = tick;
			else
				keyValue = 0;
			
			infraAnalysis(keyValue);
			
			if(keyValue)
			{
				IR_num=keyValue;
			}
		}

		keyValue=0;
		tasksStatus.INFRA_UPDATE = false;
	}
//-------------------------------------------------------

}

void EXTI9_5_IRQHandler(void)
{	
//-------------------------------------------------------	
//	if(SQW_L)//闹钟中断
//	{
//		tasksStatus.ALM_Flag = true;
//		EXTI_ClearITPendingBit(EXTI_Line8);		
//	}
//-------------------------------------------------------	
}


void IWDG_Init(u8 prer,u16 rlr) 
{	
 	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);  //使能对寄存器IWDG_PR和IWDG_RLR的写操作
	
	IWDG_SetPrescaler(prer);  //设置IWDG预分频值:设置IWDG预分频值为64
	
	IWDG_SetReload(rlr);  //设置IWDG重装载值
	
	IWDG_ReloadCounter();  //按照IWDG重装载寄存器的值重装载IWDG计数器
	
	IWDG_Enable();  //使能IWDG
}


