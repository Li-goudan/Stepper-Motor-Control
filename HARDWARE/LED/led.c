#include "led.h" 
#include "delay.h"
int finish=0;;
void LED_Init(void)
{    	 
  GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);//使能GPIOF时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//使能GPIOA
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);//使能GPIOE时钟
	
	//                             限位开关
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11|GPIO_Pin_13|GPIO_Pin_1;                 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;//下 拉
  GPIO_Init(GPIOF, &GPIO_InitStructure);
	
		//                          右边电机
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1; //DRIVER_DIR DRIVER_OE对应引脚
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
	GPIO_Init(GPIOE, &GPIO_InitStructure);//初始化GPIOE0,1
	
	 //												左边电机
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6; //DRIVER_DIR DRIVER_OE对应引脚
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
	 GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
	 GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
	 GPIO_Init(GPIOE, &GPIO_InitStructure);//初始化GPIOE0,1
	 
	 
	 //									按键  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4; //KEY0 KEY1 KEY2对应引脚
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOE, &GPIO_InitStructure);//初始化GPIOE2,3,4
	
	 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;//WK_UP对应引脚PA0
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN ;//下拉
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA0
	 
	 GPIO_ResetBits(GPIOE,GPIO_Pin_6);
	 GPIO_ResetBits(GPIOE,GPIO_Pin_1);             //使能*/
}

void EXTI15_10_IRQHandler(void)
{
   delay_ms(2);
  if(EXTI_GetITStatus(EXTI_Line11)==1&&finish==0)
			{		
				  DRE2=1;
				  delay_ms(300);
				  TIM_Cmd(TIM13, DISABLE);
					EXTI_ClearITPendingBit(EXTI_Line11);				
			
			}		
			
   else if(EXTI_GetITStatus(EXTI_Line13)==1&&GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_13)==1&&finish==0)
			{		
				  DRE=0;
				   // GPIO_ResetBits(GPIOE,GPIO_Pin_0);
           EXTI_ClearITPendingBit(EXTI_Line13);
			}		
			
			
}

void EXTI1_IRQHandler(void)
{

  delay_ms(2);
  if(GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_1)==1&&EXTI_GetITStatus(EXTI_Line1)==1&&finish==0)
			{		
				delay_ms(160);
				  TIM_Cmd(TIM14, DISABLE);
          finish=1;
			}	
   EXTI_ClearITPendingBit(EXTI_Line1);					
}
	
//外部中断0服务程序
void EXTI0_IRQHandler(void)
{ 
	
	 
	 delay_ms(2);	//消抖
	 if(EXTI_GetITStatus(EXTI_Line0)==1)
	 { 
		  DRE=1;
		  DRE2=1;
	    TIM_Cmd(TIM13, ENABLE);
	    TIM_Cmd(TIM14, ENABLE);
		   delay_ms(3456);
		  DRE=0;
		  DRE2=0;
		  delay_ms(3456);
		 
		 
		  DRE=1;
		  DRE2=1;
		  delay_ms(3456);
		  DRE=0;
		  DRE2=0;
		  delay_ms(3456);
		 
		 
		  DRE=1;
		  DRE2=1;
			
			delay_ms(3456);
		  DRE=0;
		  DRE2=0;
		  delay_ms(3456);
		  DRE=1;
		  DRE2=1;
			delay_ms(3456);
			
			TIM_Cmd(TIM14, DISABLE);
		  TIM_Cmd(TIM13, DISABLE);
		  delay_ms(3320);
		   
		  DRE2=0;
		  TIM_Cmd(TIM13, ENABLE);
		  delay_ms(1000);
		 
		  TIM_Cmd(TIM13, DISABLE);
			
		  
	 }
	 EXTI_ClearITPendingBit(EXTI_Line0); 
}	
//外部中断2服务程序
void EXTI2_IRQHandler(void)
{
	delay_ms(10);	//消抖
	if(EXTI_GetITStatus(EXTI_Line2)==1)
	 {
	    DRE=1;
		  DRE2=1;
	    TIM_Cmd(TIM13, ENABLE);
	    TIM_Cmd(TIM14, ENABLE);
		   delay_ms(3700);
		  TIM_Cmd(TIM14, DISABLE);
		  TIM_Cmd(TIM13, DISABLE);
		  delay_ms(3700);
		   
		  DRE2=0;
		  TIM_Cmd(TIM13, ENABLE);
		  delay_ms(1000);
		 
		  TIM_Cmd(TIM13, DISABLE);
	 
	 }
	 EXTI_ClearITPendingBit(EXTI_Line2);//清除LINE2上的中断标志位 
}
//外部中断3服务程序
void EXTI3_IRQHandler(void)
{
	 
	delay_ms(10);	//消抖
	
		TIM_Cmd(TIM3, ENABLE);
	 delay_ms(1990);
			TIM_Cmd(TIM3, DISABLE);
					
	
	 EXTI_ClearITPendingBit(EXTI_Line3);  //清除LINE3上的中断标志位  
}
//外部中断4服务程序
void EXTI4_IRQHandler(void)
{
	delay_ms(2);	//消抖
	if(EXTI_GetITStatus(EXTI_Line4)==1)
	 {
	      
		 
		    DRE=1;
		    DRE2=1;
	      TIM_Cmd(TIM13, ENABLE);
	      TIM_Cmd(TIM14, ENABLE);
		    delay_ms(2600);
		    TIM_Cmd(TIM14, DISABLE);
		    TIM_Cmd(TIM13, DISABLE);  
		   TIM_Cmd(TIM3, ENABLE);
		    delay_ms(1300);
		   TIM_Cmd(TIM3, DISABLE);
		  
		    
		 
		 
		    DRE=0;
		    DRE2=0;
	      TIM_Cmd(TIM13, ENABLE);
	      TIM_Cmd(TIM14, ENABLE);
		    delay_ms(2600);
		    TIM_Cmd(TIM14, DISABLE);
		    TIM_Cmd(TIM13, DISABLE);
			
				
		 
		   TIM_Cmd(TIM3, ENABLE);
		    delay_ms(1300);
		   TIM_Cmd(TIM3, DISABLE);
			
		
				
				
				DRE=1;
		    DRE2=1;
	      TIM_Cmd(TIM13, ENABLE);
	      TIM_Cmd(TIM14, ENABLE);
		    delay_ms(2600);
		    TIM_Cmd(TIM14, DISABLE);
		    TIM_Cmd(TIM13, DISABLE);
				TIM_Cmd(TIM3, ENABLE);
		    delay_ms(1300);
		   TIM_Cmd(TIM3, DISABLE);
				
				
				
				delay_ms(4000);
				
				DRE2=0;
		    TIM_Cmd(TIM13, ENABLE);
				delay_ms(1000);
				TIM_Cmd(TIM13, DISABLE);
				
				
	 }
	 EXTI_ClearITPendingBit(EXTI_Line4);//清除LINE4上的中断标志位  
}
	   
//外部中断初始化程序
//初始化PE2~4,PA0为中断输入.

void EXTIX_Init(void)
{
	NVIC_InitTypeDef   NVIC_InitStructure;
	EXTI_InitTypeDef   EXTI_InitStructure;
	
 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//使能SYSCFG时钟
	
 
	
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOF, EXTI_PinSource11);//PF11 连接到中断线11
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOF, EXTI_PinSource13);//PF13 连接到中断线13
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOF, EXTI_PinSource1); //PF1
	
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource2);//PE2 连接到中断线2
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource3);//PE3 连接到中断线3
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource4);//PE4 连接到中断线4
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource0);//PA0 连接到中断线0

	/* 配置EXTI_Line13|11 */
	EXTI_InitStructure.EXTI_Line = EXTI_Line11|EXTI_Line13;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//中断事件
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //上 升
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;//中断线使能
  EXTI_Init(&EXTI_InitStructure);//配置
	
	
	EXTI_InitStructure.EXTI_Line = EXTI_Line1;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//中断事件
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //上 升
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;//中断线使能
  EXTI_Init(&EXTI_InitStructure);//配置

 
  /* 配置EXTI_Line0 */
  EXTI_InitStructure.EXTI_Line = EXTI_Line0;//LINE0
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//中断事件
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //上升沿触发 
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;//使能LINE0
  EXTI_Init(&EXTI_InitStructure);//配置
	
	/* 配置EXTI_Line2,3,4 */
	EXTI_InitStructure.EXTI_Line = EXTI_Line2 | EXTI_Line3 | EXTI_Line4;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//中断事件
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising; //下降沿触发
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;//中断线使能
  EXTI_Init(&EXTI_InitStructure);//配置
 
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;//外部中断0
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;//抢占优先级0
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//子优先级2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
  NVIC_Init(&NVIC_InitStructure);//配置
	
	
  NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;//外部中断0
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;//抢占优先级0
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//子优先级2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
  NVIC_Init(&NVIC_InitStructure);//配置
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;//外部中断2
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;//抢占优先级3
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//子优先级2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
  NVIC_Init(&NVIC_InitStructure);//配置
	
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;//外部中断3
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;//抢占优先级2
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//子优先级2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
  NVIC_Init(&NVIC_InitStructure);//配置
	
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;//外部中断4
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;//抢占优先级1
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//子优先级2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
  NVIC_Init(&NVIC_InitStructure);//配置
	
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;//外部中断0
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;//抢占优先级0
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//子优先级2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
  NVIC_Init(&NVIC_InitStructure);//配置


	   
}












