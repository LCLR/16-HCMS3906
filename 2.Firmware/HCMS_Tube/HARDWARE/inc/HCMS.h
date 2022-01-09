#ifndef HCMS_H
#define HCMS_H
#include "sys.h"
#include "stdbool.h"

//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//�����ߣ�����LCLR
//������̳:www.54lcl.com
//�޸�����:2020/03/20
//�汾��V2.0
//All rights reserved									  

#define HCMS_BLK  PBout(13)   // HCMS�հ�λ 
#define HCMS_RS   PAout(7)    // ����/���ݼĴ���
#define HCMS_CLK  PBout(12)   // ��Ĵ���/���ƼĴ���
#define HCMS_DAIN PAout(6)    // �����ߡ�
#define HCMS_CE   PBout(14)   // Ƭѡ�źţ�0-��ѡ 1-ѡ�С�
#define HCMS_CEC  PAout(5)    // Ƭѡ�źţ�0-��ѡ 1-ѡ�С�
#define CMD  1
#define DATA 0

#define LINE_1 1
#define LINE_2 0
//-----------�ײ㺯��--------------------
void HCMS_Write_Mode( u16 Line ,unsigned char Mode);   
void HCMS_Write_Done(u16 Line);
void HCMS_Write_CMD(u16 Line,u16 Data);
void HCMS_Write_Byte(unsigned char Data);
void HCMS_Write_ONE_Data(u8 ch);
u32 Getpow(u8 m, u8 n);
//-----------�û�����--------------------
void HCMS_init(void);
void HCMS_Write_Data(u16 Line,long long unsigned int Data1,long long unsigned int Data2,long long unsigned int Data3,long long unsigned int Data4);
void HCMS_Brightness(u16 Line,unsigned int HCMS_Level);
void HCMS_Show_Char(u16 Line,u8 ch1,u8 ch2,u8 ch3,u8 ch4);
void HCMS_Show_Str(u16 Line,const u8 *p);
void HCMS_Write_I_Str(const u8 *p);
void HCMS_Write_II_Str(const u8 *p);
void HCMS_Show_Flow(const u8 *p);
void OLED_Show_UnIntNum(u32 num, u8 figure);
#endif


