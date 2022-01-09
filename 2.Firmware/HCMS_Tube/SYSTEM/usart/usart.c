#include "sys.h"
#include "usart.h"	 
#include "stdarg.h"	 	 
#include "stdio.h"	 	 
#include "string.h"
#include "led.h"
//֧����Ӧ��ͬƵ���µĴ��ڲ���������.
//�����˶�printf��֧��
//�����˴��ڽ��������.
//������printf��һ���ַ���ʧ��bug
//V1.4�޸�˵��
//1,�޸Ĵ��ڳ�ʼ��IO��bug
//2,�޸���USART_RX_STA,ʹ�ô����������ֽ���Ϊ2��14�η�
//3,������USART_REC_LEN,���ڶ��崮�����������յ��ֽ���(������2��14�η�)
//4,�޸���EN_USART1_RX��ʹ�ܷ�ʽ
//V1.5�޸�˵��
//1,�����˶�UCOSII��֧��
 
//�������´���,֧��printf����,������Ҫѡ��use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc���� 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);//ѭ������,ֱ���������   
    USART1->DR = (u8) ch;      
	return ch;
}
#endif 

/*ʹ��microLib�ķ���*/
 /* 
int fputc(int ch, FILE *f)
{
	USART_SendData(USART1, (uint8_t) ch);

	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET) {}	
   
    return ch;
}
int GetKey (void)  { 

    while (!(USART1->SR & USART_FLAG_RXNE));

    return ((int)(USART1->DR & 0x1FF));
}
*/

//����1�жϷ������
//ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ���  

//����3���ջ����� 	
u8 USART3_TX_BUF[USART3_MAX_SEND_LEN]; 			//���ͻ���,���USART3_MAX_SEND_LEN�ֽ�
u8 USART3_RX_BUF[USART3_MAX_RECV_LEN]; 			//���ջ���,���USART3_MAX_RECV_LEN���ֽ�.
u8 USART_RX_BUF[USART_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.	
u8 TxBuffer3[256];
u8 TxCounter3=0;
u8 count3=0;
vu16 USART3_RX_STA=0;  


//����2���ջ����� 	
u8 USART2_TX_BUF[USART2_MAX_SEND_LEN]; 			//���ͻ���,���USART2_MAX_SEND_LEN�ֽ�
u8 USART2_RX_BUF[USART2_MAX_RECV_LEN]; 			//���ջ���,���USART2_MAX_RECV_LEN���ֽ�.
u8 TxBuffer2[256];
u8 TxCounter2=0;
u8 count2=0;
vu16 USART2_RX_STA=0;  


//����1���ջ����� 	
u8 USART1_TX_BUF[USART1_MAX_SEND_LEN]; 			//���ͻ���,���USART1_MAX_SEND_LEN�ֽ�
u8 USART1_RX_BUF[USART1_MAX_RECV_LEN]; 			//���ջ���,���USART1_MAX_RECV_LEN���ֽ�.
u8 TxBuffer1[256];
u8 TxCounter1=0;
u8 count1=0;
vu16 USART1_RX_STA=0;	
	
	
	
	
	
void uart1_init(u32 bound)
{
	//GPIO�˿�����
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure; 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//ʹ��USART1��GPIOAʱ��
	//USART1_TX   GPIOA.9
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.9  
	//USART1_RX	  GPIOA.10��ʼ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10void 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.10  
	//Usart1 NVIC ����
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ; //��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		   //�����ȼ�2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			     //IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	                         //����ָ���Ĳ�����ʼ��VIC�Ĵ���
	//USART ��ʼ������
	USART_InitStructure.USART_BaudRate = bound;//���ڲ�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

	USART_Init(USART1, &USART_InitStructure); //��ʼ������1
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
	USART_Cmd(USART1, ENABLE);                    //ʹ�ܴ���1 
}

void uart2_init(u32 bound)
{
  //GPIO�˿�����
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//ʹ��USART1��GPIOAʱ��
  USART_DeInit(USART2); //��λ����
	//USART_TX   GPIOA.2
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIO
  //USART_RX	  GPIOA.3��ʼ��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIO
  //Usart NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
  //USART ��ʼ������
	USART_InitStructure.USART_BaudRate = bound;//���ڲ�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

	USART_Init(USART2, &USART_InitStructure); 		//��ʼ������
  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
  USART_Cmd(USART2, ENABLE);                    //ʹ�ܴ���

}



void uart3_init(u32 bound)
{
  //GPIO�˿�����
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	//ʹ��USART3��GPIOBʱ��
  USART_DeInit(USART3); //��λ����
	//USART_TX   GPIOB.10
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
  GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIO
  //USART_RX	  GPIOB.11��ʼ��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
  GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIO
  //Usart NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1 ;//��ռ���ȼ�0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		//�����ȼ�0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
  //USART ��ʼ������
	USART_InitStructure.USART_BaudRate = bound;//���ڲ�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

  USART_Init(USART3, &USART_InitStructure); 		//��ʼ������
  USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
  USART_Cmd(USART3, ENABLE);                    //ʹ�ܴ���
}








void USART1_IRQHandler(void)                	//����1�жϷ������
{
	u8 Res,i;
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
	{
		Res =USART_ReceiveData(USART1);	//��ȡ���յ�������

		if((USART1_RX_STA&0x8000)==0)//����δ���
		{
			if(USART1_RX_STA&0x4000)//���յ���0x0d
			{
				if(Res!=0x0a)USART1_RX_STA=0;//���մ���,���¿�ʼ
				else USART1_RX_STA|=0x8000;	//��������� 
			}
			else //��û�յ�0X0D
			{	
				if(Res==0x0d)USART1_RX_STA|=0x4000;
				else
				{
					USART_RX_BUF[USART1_RX_STA&0X3FFF]=Res ;
					USART1_RX_STA++;
					if(USART1_RX_STA>(USART_REC_LEN-1))USART1_RX_STA=0;//�������ݴ���,���¿�ʼ����	  
				}		 
			}
//			if(USART1_RX_STA&0x8000)USART1_RX_BUF[USART1_RX_STA&0X3FFF]='\0';
		} 
//		
			if(USART1_RX_STA & 0X8000)
	{
		u1_printf("%s\r\n", USART1_RX_BUF);				
		USART1_RX_STA = 0; 
	}
	} 
	
	if((USART1->SR & (1<<7))&&(USART1->CR1 & USART_CR1_TXEIE))
	{
		USART1->DR = TxBuffer1[TxCounter1++]; //дDR����жϱ�־ 
		if(TxCounter1 == count1)
		{
			USART1->CR1 &= ~USART_CR1_TXEIE;		//�ر�TXE�ж�
		}
	}		
}



void USART2_IRQHandler(void)                		//����2�жϷ������
{
	u8 Res;
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
	{
		Res =USART_ReceiveData(USART2);	//��ȡ���յ�������
		
		if((USART2_RX_STA&0x8000)==0)//����δ���
		{
			
			if(USART2_RX_STA&0x4000)//���յ���0x0d
			{
				
				if(Res!=0x0a)USART2_RX_STA=0;//���մ���,���¿�ʼ
				else 
					USART2_RX_STA|=0x8000;	//��������� 
			}
			else //��û�յ�0X0D
			{			
				if(Res==0x0d)USART2_RX_STA|=0x4000;
				else
				{	
					USART2_RX_BUF[USART2_RX_STA&0X3FFF]=Res ;
					USART2_RX_STA++;
					if(USART2_RX_STA>(USART_REC_LEN-1))USART2_RX_STA=0;//�������ݴ���,���¿�ʼ����	  
				}		 
			}		
			if(USART2_RX_STA&0x8000)USART2_RX_BUF[USART2_RX_STA&0X3FFF]='\0';		
		}
		
		if(USART2_RX_STA & 0X8000)
	{
		u1_printf("%s\r\n", USART2_RX_BUF);				
		USART2_RX_STA = 0;
	}
	} 
	
	if((USART2->SR & (1<<7))&&(USART2->CR1 & USART_CR1_TXEIE))
	{
		USART2->DR = TxBuffer2[TxCounter2++]; //дDR����жϱ�־ 
		if(TxCounter2 == count2)
		{
			USART2->CR1 &= ~USART_CR1_TXEIE;		//�ر�TXE�ж�
		}
	}	
}




//void USART3_IRQHandler(void)                		//����3�жϷ������
//{

//	u8 Res;
//	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
//	{
//		AT
//		Res =USART_ReceiveData(USART3);	//��ȡ���յ�������
//		sprintf(USART3_RX_BUF,"%d",Res);
//		u1_printf("%s\r\n", USART3_RX_BUF);
//	}

//}







void USART3_IRQHandler(void)                		//����3�жϷ������
{
	u8 Res;
	
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
	{
		Res =USART_ReceiveData(USART3);	//��ȡ���յ�������
		USART3_RX_BUF[USART3_RX_STA++]=Res;

//----------------------------------------------
			if(USART3_RX_STA>=2 && USART3_RX_STA <100)
		{
			if(USART3_RX_BUF[USART3_RX_STA-1]==0X4B && USART3_RX_BUF[USART3_RX_STA-2]==0X4F)
			{
				USART3_RX_STA=0;
				Check_sta=1;
				u1_printf("CMD\r\n");
			}
			else Check_sta=0;
		}
		 else if(USART3_RX_STA>=100)
		{
			if(USART3_RX_BUF[USART3_RX_STA-1]==0X7D && USART3_RX_BUF[USART3_RX_STA-2]==0X5D && USART3_RX_BUF[USART3_RX_STA-3]==0X7D)
			{
				USART3_RX_STA=0;
				Check_sta=1;
				u1_printf("DAT\r\n");				
			}
			else Check_sta=0;
		}	
//----------------------------------------
		
	}
	
	if((USART3->SR & (1<<7))&&(USART3->CR1 & USART_CR1_TXEIE))
	{
		USART3->DR = TxBuffer3[TxCounter3++]; //дDR����жϱ�־ 
		if(TxCounter3 == count3)
		{
			USART3->CR1 &= ~USART_CR1_TXEIE;		//�ر�TXE�ж�
		}
	}		
} 




	
//����1,printf ����
//ȷ��һ�η������ݲ�����USART3_MAX_SEND_LEN�ֽ�
void u1_printf(char* fmt  ,...)  
{  
	u16 i,j; 
	va_list ap; 
	va_start(ap,fmt);
	vsprintf((char*)USART1_TX_BUF,fmt,ap);
	va_end(ap);
	i=strlen((const char*)USART1_TX_BUF);		//�˴η������ݵĳ���
	for(j=0;j<i;j++)							//ѭ����������
	{
	  while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET); //ѭ������,ֱ���������   
		USART_SendData(USART1,USART1_TX_BUF[j]); 
	} 
}




//����2,printf ����
//ȷ��һ�η������ݲ�����USART3_MAX_SEND_LEN�ֽ�
void u2_printf(char* fmt  ,...)  
{  
	u16 i,j; 
	va_list ap; 
	va_start(ap,fmt);
	vsprintf((char*)USART2_TX_BUF,fmt,ap);
	va_end(ap);
	i=strlen((const char*)USART2_TX_BUF);		//�˴η������ݵĳ���
	for(j=0;j<i;j++)							//ѭ����������
	{
	  while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET); //ѭ������,ֱ���������   
		USART_SendData(USART2,USART2_TX_BUF[j]); 
	} 
}


//����3,printf ����
//ȷ��һ�η������ݲ�����USART3_MAX_SEND_LEN�ֽ�
void u3_printf(char* fmt  ,...)  
{  
	u16 i,j; 
	va_list ap; 
	va_start(ap,fmt);
	vsprintf((char*)USART3_TX_BUF,fmt,ap);
	va_end(ap);
	i=strlen((const char*)USART3_TX_BUF);		//�˴η������ݵĳ���
	for(j=0;j<i;j++)							//ѭ����������
	{
	  while(USART_GetFlagStatus(USART3,USART_FLAG_TC)==RESET); //ѭ������,ֱ���������   
		USART_SendData(USART3,USART3_TX_BUF[j]); 
	} 
}




void  USART1_Put_Char(unsigned char DataToSend)
{
	TxBuffer1[count1++] = DataToSend;
  //if(!(USART1->CR1 & USART_CR1_TXEIE))
		USART_ITConfig(USART1, USART_IT_TXE, ENABLE); 
}
void  USART1_Put_String(unsigned char *Str)
{
	//�ж�Strָ��������Ƿ���Ч.
	while(*Str)
	{
		//�Ƿ��ǻس��ַ� �����,������Ӧ�Ļس� 0x0d 0x0a
		if(*Str=='\r') USART1_Put_Char(0x0d);
			else if(*Str=='\n') USART1_Put_Char(0x0a);
				else  USART1_Put_Char(*Str);
		//ָ��++ ָ����һ���ֽ�.
		Str++;
	}
}
void  USART1_Put_Buf(unsigned char *DataToSend , u8 data_num)
{
	for(u8 i=0;i<data_num;i++)
		TxBuffer1[count1++] = *(DataToSend+i);
	if(!(USART1->CR1 & USART_CR1_TXEIE))
		USART_ITConfig(USART1, USART_IT_TXE, ENABLE);  
}

















void  USART2_Put_Char(unsigned char DataToSend)
{
	TxBuffer2[count2++] = DataToSend;
  //if(!(USART2->CR1 & USART_CR1_TXEIE))
		USART_ITConfig(USART2, USART_IT_TXE, ENABLE); 
}
void  USART2_Put_String(unsigned char *Str)
{
	//�ж�Strָ��������Ƿ���Ч.
	while(*Str)
	{
		//�Ƿ��ǻس��ַ� �����,������Ӧ�Ļس� 0x0d 0x0a
		if(*Str=='\r') USART2_Put_Char(0x0d);
			else if(*Str=='\n') USART2_Put_Char(0x0a);
				else  USART2_Put_Char(*Str);
		//ָ��++ ָ����һ���ֽ�.
		Str++;
	}
}
void  USART2_Put_Buf(unsigned char *DataToSend , u8 data_num)
{
	for(u8 i=0;i<data_num;i++)
		TxBuffer2[count2++] = *(DataToSend+i);
	if(!(USART2->CR1 & USART_CR1_TXEIE))
		USART_ITConfig(USART2, USART_IT_TXE, ENABLE);  
}






void  USART3_Put_Char(unsigned char DataToSend)
{
	TxBuffer3[count3++] = DataToSend;
  //if(!(USART2->CR1 & USART_CR1_TXEIE))
		USART_ITConfig(USART3, USART_IT_TXE, ENABLE); 
}
void  USART3_Put_String(unsigned char *Str)
{
	//�ж�Strָ��������Ƿ���Ч.
	while(*Str)
	{
		//�Ƿ��ǻس��ַ� �����,������Ӧ�Ļس� 0x0d 0x0a
		if(*Str=='\r') USART3_Put_Char(0x0d);
			else if(*Str=='\n') USART3_Put_Char(0x0a);
				else  USART3_Put_Char(*Str);
		//ָ��++ ָ����һ���ֽ�.
		Str++;
	}
}
void  USART3_Put_Buf(unsigned char *DataToSend , u8 data_num)
{
	for(u8 i=0;i<data_num;i++)
		TxBuffer3[count3++] = *(DataToSend+i);
	if(!(USART3->CR1 & USART_CR1_TXEIE))
		USART_ITConfig(USART3, USART_IT_TXE, ENABLE);  
}





