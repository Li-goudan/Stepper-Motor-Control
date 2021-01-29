#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "pwm.h"
#include "key.h"


//ALIENTEK 探索者STM32F407开发板 实验9
//PWM输出实验-库函数版本
//技术支持：www.openedv.com
//淘宝店铺：http://eboard.taobao.com  
//广州市星翼电子科技有限公司  
//作者：正点原子 @ALIENTEK

int main(void)
{ 
  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init(168);  //初始化延时函数
	
	uart_init(115200);//初始化串口波特率为115200
	LED_Init();
	
	GPIO_ResetBits(GPIOE,GPIO_Pin_5);	 
	GPIO_SetBits(GPIOE,GPIO_Pin_0);	
	TIM3_PWM_Init(65535,167);
	
 	TIM14_PWM_Init(270,42-1);	//84M/42=2Mhz的计数频率,重装载值500，所以PWM频率为 2M/500=4Khz.     
	TIM13_PWM_Init(270,42-1);
  
	EXTIX_Init();
	
	
	 
  
	while(1)
	{
		
	}

		
	
}
