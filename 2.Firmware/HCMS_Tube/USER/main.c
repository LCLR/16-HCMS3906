#include "systemTask.h"
//AT ��֤
//AT+CWMODE_DEF=1 ����ΪSTAģʽ
//AT+CWLAP_DEF ����wifi
//AT+CWJAP_DEF="TDHK","123456789000"
//AT+CIPMUX=0//������ģʽ
//AT+CIPMUX=0    ����͸����ʼ�������ݡ�
//AT+CIPSTART="TCP","192.168.88.157",8080  192.168.137.1
//AT+CWAUTOCONN=1 ������!!ʹ���ϵ��Զ�����AP
//AT+CIPMODE=1 ��������!!����͸��
//AT+CIPSEND ����������!!�������� SThMNt41Q_F1U8j9X

//GET https://api.seniverse.com/v3/weather/now.json?key=Sl9bqQC25KhaVdUFs&location=beijing&language=en&unit=c
//��Ѱ� GET https://api.seniverse.com/v3/weather/now.json?key=SThMNt41Q_F1U8j9X&location=dongguan&language=en&unit=c

//69fbcd62605f4a92a983521ba92585cb
//{"method":"update","gatewayNo":"D1","userkey":"69fbcd62605f4a92a983521ba92585cb"}&^!
//{"method":"send","gatewayNo":"D1","userkey":"69fbcd62605f4a92a983521ba92585cb","f":"getAllSensors"}&^!




 uint8_t SendBUF[100];
 u16 time=150;
 u16 state=0;
 u16 A1_COUNT=0;
 unsigned char Dat=0XFF;
 
int main(void)
 {	
//-----------------------------------------------	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	delay_init();
	systemInit();
//	beepCmd(ENABLE);	
	u1_printf("TEST_Begin\r\n");
	delay_ms(300);             
//----------------------------------------------
//	Creat_Json(USART3_RX_BUF);
	while(1)	
	{             
		systemLoop();        
	}
}


















