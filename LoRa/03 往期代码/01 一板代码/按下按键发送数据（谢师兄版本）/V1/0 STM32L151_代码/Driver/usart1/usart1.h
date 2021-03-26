#ifndef _usart1_H
#define _usart1_H

#include "general_type.h"
#include "stm32l1xx_usart.h"
#include "stdarg.h"
#include "stdio.h"	 	 
#include "string.h"	

#define USART1_REC_LEN  	600  	//定义最大接收字节数 600
#define USART1_SEND_LEN		600		//最大发送缓存字节数 600
#define EN_USART1_RX 			1		//使能（1）/禁止（0）串口1接收

extern u8  USART1_RX_BUF[USART1_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern u8  USART1_TX_BUF[USART1_SEND_LEN]; 		//发送缓冲,最大USART3_MAX_SEND_LEN字节 
extern u16 USART1_RX_STA;    
extern u16 i1,rxlen1;	//用于接收数据的转换长度

void USART1_Configuration(u32 baund);
void USART1_OUT(USART_TypeDef* USARTx, uint8_t *Data,uint16_t Len);
void u1_printf(char* fmt,...);
#endif
