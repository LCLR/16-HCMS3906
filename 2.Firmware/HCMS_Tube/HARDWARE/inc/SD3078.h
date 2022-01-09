#ifndef __SD3078_H__
#define __SD3078_H__
#include "config.h"
#include "clock_param.h"

#define SD_SDADIR_IN()	{GPIOA->CRL&=0XFFFFF0FF;GPIOA->CRL|=(u32)8<<8;}
#define SD_SDADIR_OUT() {GPIOA->CRL&=0XFFFFF0FF;GPIOA->CRL|=(u32)8<<8;}

#define SD_SCL		PAout(0)
#define SD_SDA		PAout(2)
#define SD_SDAin	PAin(2)
#define SD_SQW		PAin(1)

#define  SCL_H         GPIOA->BSRR = GPIO_Pin_0 
#define  SCL_L         GPIOA->BRR  = GPIO_Pin_0 

#define  SDA_H         GPIOA->BSRR = GPIO_Pin_2
#define  SDA_L         GPIOA->BRR  = GPIO_Pin_2
#define  SDA_read     (GPIOA->IDR  & GPIO_Pin_2)


#define  SQW_H         GPIOA->BSRR = GPIO_Pin_1
#define  SQW_L         GPIOA->BRR  = GPIO_Pin_1



extern u8	data_Buf[8];
extern u8	VBAT_Buf[2];
extern u16	VBAT_VAL;



enum Freq{F_0Hz, F32KHz, F4096Hz, F1024Hz, F64Hz, F32Hz, F16Hz, F8Hz, \
					F4Hz, F2Hz, F1Hz, F1_2Hz, F1_4Hz, F1_8Hz, F1_16Hz, F_1s};

enum clk_Souce{S_4096Hz, S_1024Hz, S_1s, S_1min};

/*�˽ṹ�嶨����ʱ����Ϣ�����ꡢ�¡��ա����ڡ�ʱ���֡���*/
typedef	struct
{
	u8	second;
	u8	minute;
	u8	hour;
	u8	week;
	u8	day;
	u8	month;
	u8	year;
} Time_Def;

/*�˽ṹ�嶨���˵���ʱ�жϿɹ����õ�Ƶ��Դ��IM�ͳ�ֵ��Ҫ����*/
typedef	struct
{
	enum clk_Souce d_clk;
	u8   IM;	//IM=1:�������ж�
	u32  init_val;
} CountDown_Def;

/*
 * ͨ���궨��ѡ��ʹ�õ�RTC�ͺ�
 * SD30XX_25XX -> ʹ��SD30��SD25ϵ��
 * SD20XX_24XX -> ʹ��SD20��SD24ϵ��
 */
#define		SD30XX_25XX
#undef		SD20XX_24XX

/********************************************************/
#define		TRUE            1
#define		FALSE           0
#define		H               1
#define		L               0
#define		Chg_enable		0x82
#define		Chg_disable		0

/******************** Device Address ********************/
#define		RTC_Address     0x64 

/******************** Alarm register ********************/
#define		Alarm_SC				0x07
#define		Alarm_MN				0x08
#define		Alarm_HR				0x09
#define		Alarm_WK				0x0A
#define		Alarm_DY				0x0B
#define		Alarm_MO				0x0C
#define		Alarm_YR				0x0D
#define		Alarm_EN				0x0E

/******************** Control Register *******************/
#define		CTR1            0x0F
#define		CTR2            0x10
#define		CTR3            0x11

/***************** Timer Counter Register ****************/
#define		Timer_Counter1	0x13
#define		Timer_Counter2	0x14
#define		Timer_Counter3	0x15

/******************** Battery Register ********************/
#define		Chg_MG          0x18		//������Ĵ�����ַ
#define		Bat_H8          0x1A		//�������λ�Ĵ�����ַ
#define		Bat_L8          0x1B		//�����Ͱ�λ�Ĵ�����ַ

/*********************** ID Register **********************/
#define		ID_Address			0x72		//ID����ʼ��ַ

/********************** �����жϺ궨�� *********************/
#define		sec_ALM					0x01
#define		min_ALM					0x02
#define		hor_ALM					0x04
#define		wek_ALM					0x08
#define		day_ALM					0x10
#define		mon_ALM					0x20
#define		yar_ALM					0x40

/********************** �ж�ʹ�ܺ궨�� **********************/
#define		INTDE						0x04		//����ʱ�ж�
#define		INTAE						0x02		//�����ж�
#define		INTFE						0x01		//Ƶ���ж�

/********************** �ж���ʾ�궨�� **********************/
#define 	FREQUENCY				0				//Ƶ���ж�
#define 	ALARM						1				//�����ж�
#define 	COUNTDOWN				2				//����ʱ�ж�
#define 	DISABLE					3				//��ֹ�ж�

/*************** �ж��������ѡ��������ѡ�� ****************/
#define 	INT_TYPE			COUNTDOWN //�����ж��������

/***********��дʱ�亯��*************/
u8 RTC_WriteDate(Time_Def	*psRTC);
u8 RTC_ReadDate(Time_Def	*psRTC);

/*******I2C���ֽ�������д����********/
u8 I2CWriteSerial(u8 DeviceAddress,u8 Address,u8 length,u8 *ps);
u8 I2CReadSerial(u8 DeviceAddress,u8 Address,u8 length,u8 *ps);

/*********I2C�˿ڳ�ʼ������*********/
void SD3078_Init(void);
unsigned char BCDtoNum(unsigned char val);
/*********RTC�ж����ú���*********/
void Set_CountDown(CountDown_Def *CountDown_Init);
void Set_Alarm(u8 Enable_config, Time_Def *psRTC);
void SetFrq(enum Freq F_Out);
void ClrINT(u8 int_EN);

#endif /* __RTC_H */
