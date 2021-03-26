#ifndef _usart2_H
#define _usart2_H

#include "general_type.h"
#include "stm32l1xx_usart.h"
#include "stdarg.h"
#include "stdio.h"	 	 
#include "string.h"

#define USART2_REC_LEN  	600  	//定义最大接收字节数 600
#define USART2_SEND_LEN		600		//最大发送缓存字节数 600
#define EN_USART2_RX 			1		//使能（1）/禁止（0）串口1接收
	  	
extern u8  USART2_RX_BUF[USART2_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern u8  USART2_TX_BUF[USART2_SEND_LEN]; 		//发送缓冲,最大USART3_MAX_SEND_LEN字节 
extern u16 USART2_RX_STA;         		//接收状态标记	
extern u16 i2,rxlen2;	//用于接收数据的转换长度

void USART2_Configuration(u32 baund);
void USART2_OUT(USART_TypeDef* USARTx, uint8_t *Data,uint16_t Len);
void u2_printf(char* fmt,...);
#endif
