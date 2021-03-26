#ifndef _usart2_H
#define _usart2_H

#include "general_type.h"
#include "stm32l1xx_usart.h"
#include "stdarg.h"
#include "stdio.h"	 	 
#include "string.h"

#define USART2_REC_LEN  	600  	//�����������ֽ��� 600
#define USART2_SEND_LEN		600		//����ͻ����ֽ��� 600
#define EN_USART2_RX 			1		//ʹ�ܣ�1��/��ֹ��0������1����
	  	
extern u8  USART2_RX_BUF[USART2_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u8  USART2_TX_BUF[USART2_SEND_LEN]; 		//���ͻ���,���USART3_MAX_SEND_LEN�ֽ� 
extern u16 USART2_RX_STA;         		//����״̬���	
extern u16 i2,rxlen2;	//���ڽ������ݵ�ת������

void USART2_Configuration(u32 baund);
void USART2_OUT(USART_TypeDef* USARTx, uint8_t *Data,uint16_t Len);
void u2_printf(char* fmt,...);
#endif
