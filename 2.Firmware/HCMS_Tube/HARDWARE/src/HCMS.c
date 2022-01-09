#include "HCMS.h"
#include "delay.h"
#include "usart.h"
#include "stdbool.h"
#include "string.h"
#include "HCMS_Fonth.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//创建者：鲸落LCLR
//个人论坛:www.54lcl.com
//修改日期:2020/03/20
//版本：V2.0
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////  


void HCMS_init(void)
{
	
	GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB, ENABLE);	 //使能PB,PE端口时钟
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;				 //LED0-->PB.5 端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOA, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB.5

 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14;				 //LED0-->PB.5 端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB.5
    
HCMS_BLK=0;          
     
HCMS_Write_CMD(LINE_1,0X81);
HCMS_Write_CMD(LINE_1,0X66);
HCMS_Write_CMD(LINE_2,0X81);
HCMS_Write_CMD(LINE_2,0X66);
  
}

void HCMS_Write_Mode( u16 Line ,unsigned char Mode)//HCMS写模式
{
    if(Line)HCMS_CEC =1;
    else HCMS_CE=1;
    delay_us(1);
    if(Mode)HCMS_RS=1;
    else HCMS_RS=0;
    
    delay_us(1);
    if(Line)HCMS_CEC =0;
    else HCMS_CE=0;
    delay_us(1);
    
    if(Mode)HCMS_RS=0;
    else HCMS_RS=1;
    delay_us(1);
}


void HCMS_Write_Done(u16 Line)//向HCMS写数据完成
{
    if(Line)HCMS_CEC =1;
    else HCMS_CE=1;
    delay_us(1);
    HCMS_CLK=0;
    delay_us(1);  
}


void HCMS_Write_Byte(unsigned char Data)//向HCMS写一个字节
{   
        for(unsigned i=0;i<8;i++)
        {
            HCMS_CLK=0;
            delay_us(1);            

            if(Data&0x80)	HCMS_DAIN = 1;
            else 			HCMS_DAIN = 0;
            delay_us(1);
            Data<<=1;            
   
            HCMS_CLK=1;
            delay_us(1);                
        }    
}

void HCMS_Write_ONE_Data(u8 ch)//向HCMS写一个数据
{
    
     ch=ch-32;   
    
    for(u16 i=0;i<5;i++)
    {
        HCMS_Write_Byte(Four_Fonth[ch][i]);    
    }
       
}



void HCMS_Write_Data(u16 Line,long long unsigned int Data1,long long unsigned int Data2,long long unsigned int Data3,long long unsigned int Data4)//写满一个HCMS块
{
 
    HCMS_Write_Mode(Line,DATA);    
    
        for(unsigned i=0;i<160;i++)
        {
            HCMS_CLK=0;
            delay_us(1);            
            
            if(i<40)
            {
                if(Data1&0x8000000000)	HCMS_DAIN = 1;
                else 			HCMS_DAIN = 0;
                delay_us(1);
                Data1<<=1;            
            }
            if(i>=40 && i < 80)
            {
                if(Data2&0x8000000000)	HCMS_DAIN = 1;
                else 			HCMS_DAIN = 0;
                delay_us(1);
                Data2<<=1;                 
                
            }
            if(i>=80 && i< 120)
            {
                if(Data3&0x8000000000)	HCMS_DAIN = 1;
                else 			HCMS_DAIN = 0;
                delay_us(1);
                Data3<<=1;                 
                
            }
            if(i>=120)
            {
                if(Data4&0x8000000000)	HCMS_DAIN = 1;
                else 			HCMS_DAIN = 0;
                delay_us(1);
                Data4<<=1;                 
                
            }
            
            HCMS_CLK=1;
            delay_us(1);                
        }

        
    HCMS_Write_Done(Line);   
}

void HCMS_Write_CMD(u16 Line,u16 Data)//向HCMS写命令
{
    HCMS_Write_Mode(Line,CMD); 
       
    for(unsigned i=0;i< 8;i++)
    {
        HCMS_CLK=0;
        delay_us(1);
		if(Data&0x80)	HCMS_DAIN = 1;
		else 			HCMS_DAIN = 0;
        delay_us(1);
		Data<<=1;
        
        HCMS_CLK=1;
        delay_us(1);   
    }

    HCMS_Write_Done(Line);  
}



void HCMS_Brightness(u16 Line,unsigned int HCMS_Level)//调整显示亮度，一共16级
{
    switch(HCMS_Level)
    {
        case 0 :HCMS_Write_CMD(Line,0X60);break;
        case 1 :HCMS_Write_CMD(Line,0X61);break;
        case 2 :HCMS_Write_CMD(Line,0X62);break;
        case 3 :HCMS_Write_CMD(Line,0X63);break;
        case 4 :HCMS_Write_CMD(Line,0X64);break;
        case 5 :HCMS_Write_CMD(Line,0X65);break;
        case 6 :HCMS_Write_CMD(Line,0X66);break;
        case 7 :HCMS_Write_CMD(Line,0X67);break;
        case 8 :HCMS_Write_CMD(Line,0X68);break;
        case 9 :HCMS_Write_CMD(Line,0X69);break;
        case 10:HCMS_Write_CMD(Line,0X6A);break;
        case 11:HCMS_Write_CMD(Line,0X6B);break;
        case 12:HCMS_Write_CMD(Line,0X6C);break;
        case 13:HCMS_Write_CMD(Line,0X6D);break;
        case 14:HCMS_Write_CMD(Line,0X6E);break;
        case 15:HCMS_Write_CMD(Line,0X6F);break;
        default:HCMS_Write_CMD(Line,0X7F);break;      
   }
}

void HCMS_Show_Char(u16 Line,u8 ch1,u8 ch2,u8 ch3,u8 ch4)//向HCMS四个位分别显示数据
{
	u8 i;
    long long unsigned int temp1,temp2,temp3,temp4;
    ch1=ch1-32;
    ch2=ch2-32;
    ch3=ch3-32;
    ch4=ch4-32;   
    temp1=Fonth[ch1];
    temp2=Fonth[ch2];
    temp3=Fonth[ch3];
    temp4=Fonth[ch4];
    HCMS_Write_Data(Line,temp1,temp2,temp3,temp4);        
}


void HCMS_Show_Str(u16 Line,const u8 *p)//HCMS显示字符串
{
    while((*p <= '~')&&(*p >= ' '))		//判断是不是非法字符!
        { 
            HCMS_Show_Char(Line,*p,*(p+1),*(p+2),*(p+3));//显示这个字符
        }  

}


void HCMS_Write_I_Str(const u8 *p)
{
    HCMS_Write_Mode(LINE_1,DATA);
//    HCMS_Write_Mode(LINE_2,CMD);
    u8 H_count=0;
    while((*p <= '~')&&(*p >= ' '))		//判断是不是非法字符!
        {        

         HCMS_Write_ONE_Data(*p);
         H_count++;
         p++;
        }
       H_count=4-H_count;
        if(H_count)
        {
            for(u8 i=0;i<H_count;i++)
            {
                HCMS_Write_ONE_Data(' ');   
            }
    }
        
    HCMS_Write_Done(LINE_1);     
}

void HCMS_Write_II_Str(const u8 *p)
{     
    u8 H_count=0;
    u8 *q;
    u8 lenth=strlen(p);
//    u1_printf("%d\r\n",lenth);
    HCMS_Write_Mode(LINE_2,DATA); 
if(lenth < 5)
{
         H_count=16-lenth;
        for(u8 i=0;i<H_count;i++)
        {
            HCMS_Write_ONE_Data(' ');   
        } 
        H_count=0;
        while((*p <= '~')&&(*p >= ' '))		//判断是不是非法字符!
        {        
            HCMS_Write_ONE_Data(*p);
            H_count++;
            p++;
        }        
         H_count=4-lenth;
        for(u8 i=0;i<H_count;i++)
        {
            HCMS_Write_ONE_Data(' ');   
        }        
    } 
else if(lenth >= 5 && lenth<9)
{    
         H_count=8;
        for(u8 i=0;i<H_count;i++)
        {
            HCMS_Write_ONE_Data(' ');   
        } 
 
         H_count=8-lenth; 
         for(u8 i=0;i<lenth-4;i++)
        {
            HCMS_Write_ONE_Data(*(p+4+i));   
        }        
        for(u8 i=0;i<H_count;i++)
        {
            HCMS_Write_ONE_Data(' ');   
        }        
     
        for(u8 i=0;i<4;i++)
        {                
            HCMS_Write_ONE_Data(*p);
            p++; 
        }            
}
else if(lenth >= 9 && lenth<13)
{
         H_count=16-12;
        for(u8 i=0;i<H_count;i++)
        {
            HCMS_Write_ONE_Data(' ');   
        }

        
        H_count=12-lenth;
        
         for(u8 i=0;i<lenth-8;i++)
        {
            HCMS_Write_ONE_Data(*(p+8+i));   
        }        
        for(u8 i=0;i<H_count;i++)
        {
            HCMS_Write_ONE_Data(' ');   
        } 
 

        for(u8 i=4;i>0;i--)
        {                
            HCMS_Write_ONE_Data(*(p+8-i));
        }
        for(u8 i=4;i>0;i--)
        {                
            HCMS_Write_ONE_Data(*(p+4-i));
        }

        
//        for(u8 i=0;i<8;i++)
//        {                
//            HCMS_Write_ONE_Data(*p);
//            p++; 
//        }
        
}    
else if(lenth >= 13 && lenth<17)
{

        H_count=16-lenth;        
         for(u8 i=0;i<lenth-12;i++)
        {
            HCMS_Write_ONE_Data(*(p+12+i));   
        }        
        for(u8 i=0;i<H_count;i++)
        {
            HCMS_Write_ONE_Data(' ');   
        }    

        for(u8 i=4;i>0;i--)
        {                
            HCMS_Write_ONE_Data(*(p+12-i));
        }    
        for(u8 i=4;i>0;i--)
        {                
            HCMS_Write_ONE_Data(*(p+8-i));
        }
        for(u8 i=4;i>0;i--)
        {                
            HCMS_Write_ONE_Data(*(p+4-i));
        }   
}         
    HCMS_Write_Done(LINE_2);     
}


/*
函数功能：计算m^n
*/
u32 Getpow(u8 m, u8 n)
{
	u8 i;
	u32 sum = 1;
	
	for (i = 0; i < n;i++)
	{
		sum *= m;
	}
	
	return sum;
}


