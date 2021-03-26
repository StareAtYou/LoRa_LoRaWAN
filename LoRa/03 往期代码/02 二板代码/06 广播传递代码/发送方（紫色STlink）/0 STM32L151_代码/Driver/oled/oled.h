//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//中景园电子
//店铺地址：http://shop73023976.taobao.com/?spm=2013.1.0.0.M4PqC2
//
//  文 件 名   : main.c
//  版 本 号   : v2.0
//  作    者   : Evk123
//  生成日期   : 2014-0101
//  最近修改   : 
//  功能描述   : 0.69寸OLED 接口演示例程(STM32F103ZE系列IIC)
//              说明: 
//              ----------------------------------------------------------------
//              GND   电源地
//              VCC   接5V或3.3v电源
//              SCL   接PD6（SCL）
//              SDA   接PD7（SDA）            
//              ----------------------------------------------------------------
//Copyright(C) 中景园电子2014/3/16
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
//-----------------OLED IIC端口定义----------------  
/*OLED IIC  是模拟IIC 定义的引脚可变   需要修改处为     
       1.#define OLED_SCLK_Clr() GPIO_ResetBits(GPIOA,GPIO_Pin_4)//SCL IIC接口的时钟信号
//     #define OLED_SCLK_Set() GPIO_SetBits(GPIOA,GPIO_Pin_4)

//     #define OLED_SDIN_Clr() GPIO_ResetBits(GPIOA,GPIO_Pin_5)//SDA IIC接口的数据信号
//     #define OLED_SDIN_Set() GPIO_SetBits(GPIOA,GPIO_Pin_5)

//     2.OLED 的初始化
       	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_4|GPIO_Pin_5;	 //PD3,PD6推挽输出  
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
				GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//速度50MHz
				GPIO_Init(GPIOA, &GPIO_InitStructure);	  //初始化GPIOD3,6
				GPIO_SetBits(GPIOA,GPIO_Pin_4|GPIO_Pin_5);*/
			 
//-----------------OLED端口定义---------------- 

#define OLED_SCL_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_6)//SCL IIC接口的时钟信号
#define OLED_SCL_Set() GPIO_SetBits(GPIOB,GPIO_Pin_6)

#define OLED_SDA_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_5)//SDA IIC接口的数据信号
#define OLED_SDA_Set() GPIO_SetBits(GPIOB,GPIO_Pin_5)

#define OLED_RES_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_4)//RES
#define OLED_RES_Set() GPIO_SetBits(GPIOB,GPIO_Pin_4)

#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据

#define u8 unsigned char 
#define u16 unsigned int
#define u32 unsigned long

//OLED控制用函数
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


