#ifndef __LED_H
#define __LED_H
#include "sys.h"

//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F407������
//LED��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2014/5/2
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	


//LED�˿ڶ���
#define LED0 PFout(9)	// DS0
#define LED1 PFout(10)	// DS1	 


#define DRE PEout(0)
#define ENA PEout(1)
#define P11EAB  GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_11)


#define DRE2 PEout(5)
#define ENA2 PEout(6)
#define P13EAB  GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_13)


void LED_Init(void);//��ʼ��
void EXTIX_Init(void);	//�ⲿ�жϳ�ʼ��
void mode1(void );
extern int finish;
#endif
