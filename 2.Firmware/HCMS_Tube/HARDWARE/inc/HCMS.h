#ifndef HCMS_H
#define HCMS_H
#include "sys.h"
#include "stdbool.h"

//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//创建者：鲸落LCLR
//个人论坛:www.54lcl.com
//修改日期:2020/03/20
//版本：V2.0
//All rights reserved									  

#define HCMS_BLK  PBout(13)   // HCMS空白位 
#define HCMS_RS   PAout(7)    // 控制/数据寄存器
#define HCMS_CLK  PBout(12)   // 点寄存器/控制寄存器
#define HCMS_DAIN PAout(6)    // 数据线。
#define HCMS_CE   PBout(14)   // 片选信号，0-不选 1-选中。
#define HCMS_CEC  PAout(5)    // 片选信号，0-不选 1-选中。
#define CMD  1
#define DATA 0

#define LINE_1 1
#define LINE_2 0
//-----------底层函数--------------------
void HCMS_Write_Mode( u16 Line ,unsigned char Mode);   
void HCMS_Write_Done(u16 Line);
void HCMS_Write_CMD(u16 Line,u16 Data);
void HCMS_Write_Byte(unsigned char Data);
void HCMS_Write_ONE_Data(u8 ch);
u32 Getpow(u8 m, u8 n);
//-----------用户函数--------------------
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


