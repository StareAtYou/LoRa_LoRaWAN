#include "usart1.h" 			  			 
#include "bluetooth.h" 



void Blue_receive()
{
		u16 i1,rxlen1;
		rxlen1=USART1_RX_STA&0X7FFF;	//�õ����ݳ���
		for(i1=0;i1<rxlen1;i1++)
			{
				USART_SendData(USART1, USART1_RX_BUF[i1]);         //�򴮿�1��������
				while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
			}
			
}









