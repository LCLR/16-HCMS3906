#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "sys.h" 

#pragma anon_unions

#define USART_REC_LEN  			200  	//�����������ֽ��� 200
#define USART3_MAX_RECV_LEN		600					//�����ջ����ֽ���
#define USART3_MAX_SEND_LEN		600					//����ͻ����ֽ���
#define USART2_MAX_RECV_LEN		600					//�����ջ����ֽ���
#define USART2_MAX_SEND_LEN		600					//����ͻ����ֽ���
#define USART1_MAX_RECV_LEN		600					//�����ջ����ֽ���
#define USART1_MAX_SEND_LEN		600					//����ͻ����ֽ���
#define EN_USART1_RX 			1		//ʹ�ܣ�1��/��ֹ��0������1����
			
extern struct USART_TypedefStructInit
{
	char RX_DataBuf[USART_REC_LEN];
	union
	{
		volatile uint16_t infAll;
		struct
		{
			volatile uint16_t frameLength 		:15;
			volatile uint16_t frameFinishFlag :1;
		}infBit;
	};
}USART1_FrameRecord;


extern u8 USART_RX_BUF[USART_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u8 USART3_RX_BUF[USART3_MAX_RECV_LEN]; 			//���ջ���,���USART2_MAX_RECV_LEN���ֽ�.
extern u8 USART3_TX_BUF[USART3_MAX_SEND_LEN]; 			//���ͻ���,���USART2_MAX_SEND_LEN�ֽ�
extern vu16 USART3_RX_STA;

extern u8 USART2_RX_BUF[USART2_MAX_RECV_LEN]; 			//���ջ���,���USART2_MAX_RECV_LEN���ֽ�.
extern u8 USART2_TX_BUF[USART2_MAX_SEND_LEN]; 			//���ͻ���,���USART2_MAX_SEND_LEN�ֽ�
extern vu16 USART2_RX_STA;

extern u8 USART_RX_BUF[USART_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u8 USART1_RX_BUF[USART1_MAX_RECV_LEN]; 			//���ջ���,���USART2_MAX_RECV_LEN���ֽ�.
extern u8 USART1_TX_BUF[USART1_MAX_SEND_LEN]; 			//���ͻ���,���USART2_MAX_SEND_LEN�ֽ�
extern vu16 USART1_RX_STA;
extern	u8 Check_sta;



void uart1_init(u32 bound);
void u1_printf(char* fmt  ,...);
void uart2_init(u32 bound);
void u2_printf(char* fmt  ,...);
void  USART2_Put_Char(unsigned char DataToSend);
void  USART2_Put_String(unsigned char *Str);
void  USART2_Put_Buf(unsigned char *DataToSend , u8 data_num);

void uart3_init(u32 bound);
void u3_printf(char* fmt  ,...);

void  USART1_Put_Char(unsigned char DataToSend);
void  USART1_Put_String(unsigned char *Str);
void  USART1_Put_Buf(unsigned char *DataToSend , u8 data_num);


void  USART3_Put_Char(unsigned char DataToSend);
void  USART3_Put_String(unsigned char *Str);
void  USART3_Put_Buf(unsigned char *DataToSend , u8 data_num);


#endif


