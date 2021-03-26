//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//�о�԰����
//���̵�ַ��http://shop73023976.taobao.com/?spm=2013.1.0.0.M4PqC2
//
//  �� �� ��   : main.c
//  �� �� ��   : v2.0
//  ��    ��   : Evk123
//  ��������   : 2014-0101
//  ����޸�   : 
//  ��������   : 0.69��OLED �ӿ���ʾ����(STM32F103ZEϵ��IIC)
//              ˵��: 
//              ----------------------------------------------------------------
//              GND   ��Դ��
//              VCC   ��5V��3.3v��Դ
//              SCL   ��PD6��SCL��
//              SDA   ��PD7��SDA��            
//              ----------------------------------------------------------------
//Copyright(C) �о�԰����2014/3/16
//All rights reserved
//////////////////////////////////////////////////////////////////////////////////
#ifndef __OLED_H
#define __OLED_H 

#include "sys.h"
#include "stdlib.h"	


#define OLED_MODE 0
#define SIZE 8
#define XLevelL		0x00
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xFF 
#define X_WIDTH 	128
#define Y_WIDTH 	64	    						  
//-----------------OLED IIC�˿ڶ���----------------  
/*OLED IIC  ��ģ��IIC ��������ſɱ�   ��Ҫ�޸Ĵ�Ϊ     
       1.#define OLED_SCLK_Clr() GPIO_ResetBits(GPIOA,GPIO_Pin_4)//SCL IIC�ӿڵ�ʱ���ź�
//     #define OLED_SCLK_Set() GPIO_SetBits(GPIOA,GPIO_Pin_4)

//     #define OLED_SDIN_Clr() GPIO_ResetBits(GPIOA,GPIO_Pin_5)//SDA IIC�ӿڵ������ź�
//     #define OLED_SDIN_Set() GPIO_SetBits(GPIOA,GPIO_Pin_5)

//     2.OLED �ĳ�ʼ��
       	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_4|GPIO_Pin_5;	 //PD3,PD6�������  
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
				GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//�ٶ�50MHz
				GPIO_Init(GPIOA, &GPIO_InitStructure);	  //��ʼ��GPIOD3,6
				GPIO_SetBits(GPIOA,GPIO_Pin_4|GPIO_Pin_5);*/
			 
//-----------------OLED�˿ڶ���---------------- 

#define OLED_SCL_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_6)//SCL IIC�ӿڵ�ʱ���ź�
#define OLED_SCL_Set() GPIO_SetBits(GPIOB,GPIO_Pin_6)

#define OLED_SDA_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_5)//SDA IIC�ӿڵ������ź�
#define OLED_SDA_Set() GPIO_SetBits(GPIOB,GPIO_Pin_5)

#define OLED_RES_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_4)//RES
#define OLED_RES_Set() GPIO_SetBits(GPIOB,GPIO_Pin_4)

#define OLED_CMD  0	//д����
#define OLED_DATA 1	//д����

#define u8 unsigned char 
#define u16 unsigned int
#define u32 unsigned long

//OLED�����ú���
void OLED_ClearPoint(u8 x,u8 y);
void OLED_ColorTurn(u8 i);
void OLED_DisplayTurn(u8 i);
void I2C_Start(void);
void I2C_Stop(void);
void I2C_WaitAck(void);
void Send_Byte(u8 dat);
void OLED_WR_Byte(u8 dat,u8 mode);
void OLED_DisPlay_On(void);
void OLED_DisPlay_Off(void);
void OLED_Refresh(void);
void OLED_Clear(void);
void OLED_DrawPoint(u8 x,u8 y,u8 t);
void OLED_DrawLine(u8 x1,u8 y1,u8 x2,u8 y2,u8 mode);
void OLED_DrawCircle(u8 x,u8 y,u8 r);
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 size1,u8 mode);
void OLED_ShowChar6x8(u8 x,u8 y,u8 chr,u8 mode);
void OLED_ShowString(u8 x,u8 y,u8 *chr,u8 size1,u8 mode);
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size1,u8 mode);
void OLED_ShowChinese(u8 x,u8 y,u8 num,u8 size1,u8 mode);
void OLED_ScrollDisplay(u8 num,u8 space,u8 mode);
void OLED_ShowPicture(u8 x,u8 y,u8 sizex,u8 sizey,u8 BMP[],u8 mode);
void OLED_Init(void);

#endif


