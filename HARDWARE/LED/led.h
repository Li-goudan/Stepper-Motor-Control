#ifndef __LED_H
#define __LED_H
#include "sys.h"

//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32F407开发板
//LED驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2014/5/2
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	


//LED端口定义
#define LED0 PFout(9)	// DS0
#define LED1 PFout(10)	// DS1	 


#define DRE PEout(0)
#define ENA PEout(1)
#define P11EAB  GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_11)


#define DRE2 PEout(5)
#define ENA2 PEout(6)
#define P13EAB  GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_13)


void LED_Init(void);//初始化
void EXTIX_Init(void);	//外部中断初始化
void mode1(void );
extern int finish;
#endif
