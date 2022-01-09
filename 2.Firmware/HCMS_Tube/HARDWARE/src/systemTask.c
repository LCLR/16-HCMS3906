#include "systemTask.h"




#define Normal_Mode 0X01
#define Set_Mode    0X02
#define ALM_Mode    0X04
#define WIFI_Mode   0X08
#define GAME_Mode   0X10

tasksStatusObject tasksStatus = {0};
static uint32_t tick = 0;


Time_Def time_init={0x00,0x49,0x21,0x06,0x11,0x04,0x20};	//��ʼ��ʵʱʱ��
Time_Def Alarm_init={0x30,0x19,0x17,0x00,0x15,0x08,0x18};	//��ʼ������ʱ��
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
	uart1_init(115200);                  //����1������
//	uart2_init(9600);                   //BLE����������
	uart3_init(115200);                  //ESP-12Sͨ�Ų�����	
    TIM4_Int_Init(7200-1,10-1);          //״̬��	
	infraRemote_Init();                  //����ң�س�ʼ��   
    HCMS_init();                         //HCMS��ʼ��   
	SD3078_Init();                       //ʱ��оƬ��ʼ��
	LED_Init();                          //LED��ʼ��
	beepInit();                          //��������ʼ��
	KEY_Init();                          //����IO��ʼ��	
    Adc_Init();                          //��ǿ�ɼ�ADC��ʼ��
    
    
    beepCmd(DISABLE);
    
//	RTC_WriteDate(&time_init);	
	Show_Mode=Normal_Mode;               //��ʼ����ʾģʽ
	RTC_ReadDate(&sysTime);
    
    HCMS_Brightness(LINE_1,10);
    HCMS_Brightness(LINE_2,10);

	printf("д��ĳ�ʼʱ��Ϊ�� \r\n");
	printf("%02X-%02X-%02X  %02X:%02X:%02X  ����%02X\r\n\r\n", \
	sysTime.year, sysTime.month, sysTime.day, sysTime.hour,\
	sysTime.minute, sysTime.second, sysTime.week);



#ifdef SD30XX_25XX	
/*************** ����оƬ��ID����ʾ ****************/	
	I2CReadSerial(RTC_Address,ID_Address,8,data_Buf);
	printf("оƬ64bit ID��Ϊ��\r\n");
	for (u8 i=0; i<8; i++)
	printf("0x%02X ", data_Buf[i]);
	printf("\r\n----------------------------\r\n\r\n");

/**************** ���ʹ��������ʾ *****************/
	data_Buf[0] = Chg_enable;
	I2CWriteSerial(RTC_Address,Chg_MG,1,data_Buf);

/************** �����󱸵�ص�ѹ��ʾ ***************/	
	I2CReadSerial(RTC_Address,Bat_H8,2,VBAT_Buf);
	VBAT_VAL = (VBAT_Buf[0]>>7)*255 + VBAT_Buf[1];
	printf("VBAT�ŵĵ�ص�ѹΪ��%d.%d%dV\r\n\r\n", VBAT_VAL/100, VBAT_VAL%100/10, VBAT_VAL%10);
#endif

    
    
//	IWDG_Init(6,2000);//���Ź���ʼ��
}

void TIM4_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET) 
	{
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);   
		tick++;
//***************************************************
				if(RATE_READ_EXECUTE(20,tick))//vfdд��ʱ��
		{                
			tasksStatus.VFD_UPDATE = true;
		}
//***************************************************		
				if(RATE_READ_EXECUTE(125,tick))//ESP-WIFI
		{
			tasksStatus.ESP_UPDATE = true;
		}		
//***************************************************				
		if(RATE_READ_EXECUTE(30,tick))    //��ǿ�ɼ�
		{
			tasksStatus.ADC_UPDATE = true;
		}
//***************************************************				
		if(RATE_READ_EXECUTE(1000,tick))    //���Ź�ι��
		{
			tasksStatus.WatchD_UPDATE = true;
		}		
//***************************************************				
		if(RATE_READ_EXECUTE(500,tick))    //���Ӵ���
		{
			tasksStatus.BEEP_UPDATE = true;
		}			
//***************************************************		
		if(RATE_READ_EXECUTE(50,tick))     //��ǿ����
		{
			tasksStatus.Light_UPDATE = true;
		}		
//***************************************************
		if(RATE_READ_EXECUTE(60,tick))  //�������
		{
			tasksStatus.KEY_UPDATE = true;
		}	
//***************************************************		
		if(RATE_READ_EXECUTE(10,tick))    //����ң��
		{
			tasksStatus.INFRA_UPDATE = true;
		}
//***************************************************		
		if(RATE_READ_EXECUTE(120,tick))    //UI����
		{
			tasksStatus.UI_UPDATE = true;
		}			
//***************************************************

//***************************************************
//***************************************************
		if(RATE_READ_EXECUTE(600,tick))  //���ڴ�ӡ
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
	if(tasksStatus.UART_UPDATE == true)	//���ڴ�ӡ����
{
//        VBAT_VAL = (VBAT_Buf[0]>>7)*255 + VBAT_Buf[1];
//        printf("VBAT�ŵĵ�ص�ѹΪ��%d.%d%dV\r\n\r\n", VBAT_VAL/100, VBAT_VAL%100/10, VBAT_VAL%10);
//    
        RTC_ReadDate(&sysTime);
//    
//		Point_flick=~Point_flick;//ʱ��ð����˸
        printf("%02X-%02X-%02X  %02X:%02X:%02X  ����%02X\r\n\r\n", \
        sysTime.year, sysTime.month, sysTime.day, sysTime.hour,\
        sysTime.minute, sysTime.second, sysTime.week);
        printf("%s\r\n",Dis_BUF);
        tasksStatus.UART_UPDATE = false;
}

//-------------------------------------------------------
//������Ӧ
	if(tasksStatus.BEEP_UPDATE == true && tasksStatus.ALM_Flag == true)	
{
	Beep_IO=~Beep_IO;
	Show_Mode=ALM_Mode;
}
//-------------------------------------------------------
	if(tasksStatus.UI_UPDATE == true)	//UI����
{	
        HCMS_Write_I_Str("LCLR");        
        HCMS_Write_II_Str(Dis_BUF);

//        OLED_Show_UnIntNum(12345678, 8);
	tasksStatus.UI_UPDATE = false;
}

//-------------------------------------------------------
	if(tasksStatus.VFD_UPDATE == true)	//VFDʱ�����
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
	if(tasksStatus.KEY_UPDATE == true)	//��������
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
	if(tasksStatus.ADC_UPDATE == true)	//��ǿ����
{	
	ADC_data=Get_Adc_Average(9,5);
	
	tasksStatus.ADC_UPDATE = false;
}
//-------------------------------------------------------
	if(tasksStatus.ESP_UPDATE == true)	//ESP����
{
	tasksStatus.ESP_UPDATE = false;
}
//-------------------------------------------------------
	if(tasksStatus.WatchD_UPDATE == true)	//ι��
{
	IWDG_ReloadCounter();
	tasksStatus.WatchD_UPDATE = false;
}
//-------------------------------------------------------
	if(tasksStatus.Light_UPDATE == true) //��ǿ����
{	
	
	tasksStatus.Light_UPDATE = false;
}
//-------------------------------------------------------
	if(tasksStatus.INFRA_UPDATE == true)//����ң��
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
//	if(SQW_L)//�����ж�
//	{
//		tasksStatus.ALM_Flag = true;
//		EXTI_ClearITPendingBit(EXTI_Line8);		
//	}
//-------------------------------------------------------	
}


void IWDG_Init(u8 prer,u16 rlr) 
{	
 	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);  //ʹ�ܶԼĴ���IWDG_PR��IWDG_RLR��д����
	
	IWDG_SetPrescaler(prer);  //����IWDGԤ��Ƶֵ:����IWDGԤ��ƵֵΪ64
	
	IWDG_SetReload(rlr);  //����IWDG��װ��ֵ
	
	IWDG_ReloadCounter();  //����IWDG��װ�ؼĴ�����ֵ��װ��IWDG������
	
	IWDG_Enable();  //ʹ��IWDG
}


