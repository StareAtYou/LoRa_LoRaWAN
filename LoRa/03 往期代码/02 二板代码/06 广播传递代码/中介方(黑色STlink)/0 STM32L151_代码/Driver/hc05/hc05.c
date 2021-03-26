//#include "usart1.h" 			 		 
//#include "hc05.h" 
//#include "pbdata.h"
// 
////初始化ATK-HC05模块
////返回值:0,成功;1,失败.
//u8 HC05_Init(void)
//{
//u8 retry=10,t;	  		 
//u8 temp=1;

//GPIO_InitTypeDef GPIO_InitStructure;

//RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA,ENABLE);	//使能PORTA

//GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;				 // 端口配置
//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; 		 //推挽输出
//GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;		 //IO口速度为50MHz
//GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
//GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
//GPIO_Init(GPIOA, &GPIO_InitStructure);					 //根据设定参数初始化GPIOA8

//GPIO_SetBits(GPIOA,GPIO_Pin_4);
//// 	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);
////HC05_EN=1; 

////Usart1_Init(9600);	//初始化串口1为:9600,波特率.

//while(retry--)
//{
//	HC05_EN=1;					//KEY置高,进入AT模式
//	delay_ms(10);
//	u1_printf("AT\r\n");		//发送AT测试指令
//	HC05_EN=0;					//KEY拉低,退出AT模式
//	for(t=0;t<10;t++) 			//最长等待50ms,来接收HC05模块的回应
//	{
//		if(USART1_RX_STA&0X8000)break;
//		delay_ms(5);
//	}		
//	if(USART1_RX_STA&0X8000)	//接收到一次数据了
//	{
//		temp=USART1_RX_STA&0X7FFF;	//得到数据长度
//		USART1_RX_STA=0;			 
//		if(temp==4&&USART1_RX_BUF[0]=='O'&&USART1_RX_BUF[1]=='K')
//		{
//			temp=0;//接收到OK响应
//			break;
//		}
//	}			    		
//}		    
//if(retry==0)temp=1;	//检测失败
//return temp;	  
//}	 
////获取ATK-HC05模块的角色
////返回值:0,从机;1,主机;0XFF,获取失败.							  
//u8 HC05_Get_Role(void)
//{	 		    
//	u8 retry=0X0F;
//	u8 temp,t;
//	while(retry--)
//	{
//		HC05_EN=1;					//KEY置高,进入AT模式
//		delay_ms(10);
//		u1_printf("AT+ROLE?\r\n");	//查询角色
//		for(t=0;t<20;t++) 			//最长等待200ms,来接收HC05模块的回应
//		{
//			delay_ms(10);
//			if(USART1_RX_STA&0X8000)break;
//		}		
//		HC05_EN=0;					//KEY拉低,退出AT模式
//		if(USART1_RX_STA&0X8000)	//接收到一次数据了
//		{
//			temp=USART1_RX_STA&0X7FFF;	//得到数据长度
//			USART1_RX_STA=0;			 
//			if(temp==13&&USART1_RX_BUF[0]=='+')//接收到正确的应答了
//			{
//				temp=USART1_RX_BUF[6]-'0';//得到主从模式值
//				break;
//			}
//		}		
//	}
//	if(retry==0)temp=0XFF;//查询失败.
//	return temp;
//} 							   

////ATK-HC05设置命令
////此函数用于设置ATK-HC05,适用于仅返回OK应答的AT指令
////atstr:AT指令串.比如:"AT+RESET"/"AT+UART=9600,0,0"/"AT+ROLE=0"等字符串
////返回值:0,设置成功;其他,设置失败.							  
//u8 HC05_Set_Cmd(u8* atstr)
//{	 		    
//	u8 retry=0X0F;
//	u8 temp,t;
//	while(retry--)
//	{
//		HC05_EN=1;					//KEY置高,进入AT模式
//		delay_ms(10);
//		u1_printf("%s\r\n",atstr);	//发送AT字符串
//		HC05_EN=0;					//KEY拉低,退出AT模式
//		for(t=0;t<20;t++) 			//最长等待100ms,来接收HC05模块的回应
//		{
//			if(USART1_RX_STA&0X8000)break;
//			delay_ms(5);
//		}		
//		if(USART1_RX_STA&0X8000)	//接收到一次数据了
//		{
//			temp=USART1_RX_STA&0X7FFF;	//得到数据长度
//			USART1_RX_STA=0;			 
//			if(temp==4&&USART1_RX_BUF[0]=='O')//接收到正确的应答了
//			{			
//				temp=0;
//				break;			 
//			}
//		}		
//	}
//	if(retry==0)temp=0XFF;//设置失败.
//	return temp;
//} 	 											    






