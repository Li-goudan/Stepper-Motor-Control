#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "pwm.h"
#include "key.h"


//ALIENTEK ̽����STM32F407������ ʵ��9
//PWM���ʵ��-�⺯���汾
//����֧�֣�www.openedv.com
//�Ա����̣�http://eboard.taobao.com  
//������������ӿƼ����޹�˾  
//���ߣ�����ԭ�� @ALIENTEK

int main(void)
{ 
  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);  //��ʼ����ʱ����
	
	uart_init(115200);//��ʼ�����ڲ�����Ϊ115200
	LED_Init();
	
	GPIO_ResetBits(GPIOE,GPIO_Pin_5);	 
	GPIO_SetBits(GPIOE,GPIO_Pin_0);	
	TIM3_PWM_Init(65535,167);
	
 	TIM14_PWM_Init(270,42-1);	//84M/42=2Mhz�ļ���Ƶ��,��װ��ֵ500������PWMƵ��Ϊ 2M/500=4Khz.     
	TIM13_PWM_Init(270,42-1);
  
	EXTIX_Init();
	
	
	 
  
	while(1)
	{
		
	}

		
	
}
