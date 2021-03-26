#ifndef _usart1_H
#define _usart1_H

#include "general_type.h"
#include "stm32l1xx_usart.h"
#include "stdarg.h"
#include "stdio.h"	 	 
#include "string.h"	

#define USART1_REC_LEN  	600  	//�����������ֽ��� 600
#define USART1_SEND_LEN		600		//����ͻ����ֽ��� 600
#define EN_USART1_RX 			1		//ʹ�ܣ�1��/��ֹ��0������1����

extern u8  USART1_RX_BUF[USART1_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u8  USART1_TX_BUF[USART1_SEND_LEN]; 		//���ͻ���,���USART3_MAX_SEND_LEN�ֽ� 
extern u16 USART1_RX_STA;    
extern u16 i1,rxlen1;	//���ڽ������ݵ�ת������

void USART1_Configuration(u32 baund);
void USART1_OUT(USART_TypeDef* USARTx, uint8_t *Data,uint16_t Len);
void u1_printf(char* fmt,...);
#endif
