#ifndef __HC05_H
#define __HC05_H	 
#include "sys.h" 
#include "general_type.h"
#include "stdarg.h"
#include "stdio.h"	 	 
#include "string.h"	
#include "math.h"
#include "delay.h" 


#define HC05_EN  	PAout(8)		//À¶ÑÀ¿ØÖÆENÐÅºÅ
#define HC05_LED  PAin(15)		//À¶ÑÀÁ¬½Ó×´Ì¬ÐÅºÅ
  
u8 HC05_Init(void);
void HC05_CFG_CMD(u8 *str);
u8 HC05_Get_Role(void);
u8 HC05_Set_Cmd(u8* atstr);	     

#endif  

