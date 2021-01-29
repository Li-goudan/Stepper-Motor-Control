#include "led.h" 
#include "delay.h"
int finish=0;;
void LED_Init(void)
{    	 
  GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);//ʹ��GPIOFʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//ʹ��GPIOA
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);//ʹ��GPIOEʱ��
	
	//                             ��λ����
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11|GPIO_Pin_13|GPIO_Pin_1;                 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//��ͨ����ģʽ
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;//�� ��
  GPIO_Init(GPIOF, &GPIO_InitStructure);
	
		//                          �ұߵ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1; //DRIVER_DIR DRIVER_OE��Ӧ����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
	GPIO_Init(GPIOE, &GPIO_InitStructure);//��ʼ��GPIOE0,1
	
	 //												��ߵ��
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6; //DRIVER_DIR DRIVER_OE��Ӧ����
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
	 GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
	 GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
	 GPIO_Init(GPIOE, &GPIO_InitStructure);//��ʼ��GPIOE0,1
	 
	 
	 //									����  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4; //KEY0 KEY1 KEY2��Ӧ����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//��ͨ����ģʽ
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
  GPIO_Init(GPIOE, &GPIO_InitStructure);//��ʼ��GPIOE2,3,4
	
	 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;//WK_UP��Ӧ����PA0
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN ;//����
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA0
	 
	 GPIO_ResetBits(GPIOE,GPIO_Pin_6);
	 GPIO_ResetBits(GPIOE,GPIO_Pin_1);             //ʹ��*/
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
	
//�ⲿ�ж�0�������
void EXTI0_IRQHandler(void)
{ 
	
	 
	 delay_ms(2);	//����
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
//�ⲿ�ж�2�������
void EXTI2_IRQHandler(void)
{
	delay_ms(10);	//����
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
	 EXTI_ClearITPendingBit(EXTI_Line2);//���LINE2�ϵ��жϱ�־λ 
}
//�ⲿ�ж�3�������
void EXTI3_IRQHandler(void)
{
	 
	delay_ms(10);	//����
	
		TIM_Cmd(TIM3, ENABLE);
	 delay_ms(1990);
			TIM_Cmd(TIM3, DISABLE);
					
	
	 EXTI_ClearITPendingBit(EXTI_Line3);  //���LINE3�ϵ��жϱ�־λ  
}
//�ⲿ�ж�4�������
void EXTI4_IRQHandler(void)
{
	delay_ms(2);	//����
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
	 EXTI_ClearITPendingBit(EXTI_Line4);//���LINE4�ϵ��жϱ�־λ  
}
	   
//�ⲿ�жϳ�ʼ������
//��ʼ��PE2~4,PA0Ϊ�ж�����.

void EXTIX_Init(void)
{
	NVIC_InitTypeDef   NVIC_InitStructure;
	EXTI_InitTypeDef   EXTI_InitStructure;
	
 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//ʹ��SYSCFGʱ��
	
 
	
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOF, EXTI_PinSource11);//PF11 ���ӵ��ж���11
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOF, EXTI_PinSource13);//PF13 ���ӵ��ж���13
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOF, EXTI_PinSource1); //PF1
	
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource2);//PE2 ���ӵ��ж���2
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource3);//PE3 ���ӵ��ж���3
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource4);//PE4 ���ӵ��ж���4
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource0);//PA0 ���ӵ��ж���0

	/* ����EXTI_Line13|11 */
	EXTI_InitStructure.EXTI_Line = EXTI_Line11|EXTI_Line13;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//�ж��¼�
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //�� ��
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;//�ж���ʹ��
  EXTI_Init(&EXTI_InitStructure);//����
	
	
	EXTI_InitStructure.EXTI_Line = EXTI_Line1;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//�ж��¼�
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //�� ��
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;//�ж���ʹ��
  EXTI_Init(&EXTI_InitStructure);//����

 
  /* ����EXTI_Line0 */
  EXTI_InitStructure.EXTI_Line = EXTI_Line0;//LINE0
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//�ж��¼�
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //�����ش��� 
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;//ʹ��LINE0
  EXTI_Init(&EXTI_InitStructure);//����
	
	/* ����EXTI_Line2,3,4 */
	EXTI_InitStructure.EXTI_Line = EXTI_Line2 | EXTI_Line3 | EXTI_Line4;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//�ж��¼�
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising; //�½��ش���
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;//�ж���ʹ��
  EXTI_Init(&EXTI_InitStructure);//����
 
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;//�ⲿ�ж�0
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;//��ռ���ȼ�0
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//�����ȼ�2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
  NVIC_Init(&NVIC_InitStructure);//����
	
	
  NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;//�ⲿ�ж�0
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;//��ռ���ȼ�0
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//�����ȼ�2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
  NVIC_Init(&NVIC_InitStructure);//����
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;//�ⲿ�ж�2
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;//��ռ���ȼ�3
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//�����ȼ�2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
  NVIC_Init(&NVIC_InitStructure);//����
	
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;//�ⲿ�ж�3
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;//��ռ���ȼ�2
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//�����ȼ�2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
  NVIC_Init(&NVIC_InitStructure);//����
	
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;//�ⲿ�ж�4
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;//��ռ���ȼ�1
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//�����ȼ�2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
  NVIC_Init(&NVIC_InitStructure);//����
	
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;//�ⲿ�ж�0
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;//��ռ���ȼ�0
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//�����ȼ�2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
  NVIC_Init(&NVIC_InitStructure);//����


	   
}












