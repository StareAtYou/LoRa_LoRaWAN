#ifndef _usart3_H
#define _usart3_H

#include "general_type.h"
#include "stm32l1xx_usart.h"
#include "stdarg.h"
#include "stdio.h"	 	 
#include "string.h"

#define USART3_REC_LEN  	600  	//�����������ֽ��� 600
#define USART3_SEND_LEN		600		//����ͻ����ֽ��� 600
#define EN_USART3_RX 			1		//ʹ�ܣ�1��/��ֹ��0������3����

extern u8  USART3_TX_BUF[USART3_SEND_LEN]; 		//���ͻ���,���USART3_MAX_SEND_LEN�ֽ�  	
extern u8  USART3_RX_BUF[USART3_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u16 USART3_RX_STA;        		//����״̬���	
extern u16 i3,rxlen3;	//���ڽ������ݵ�ת������

void USART3_Configuration(u32 baund);
void USART3_OUT(USART_TypeDef* USARTx, uint8_t *Data,uint16_t Len);
void u3_printf(char* fmt,...);
#endif
