#include "LED.h"

void LED_Init(void){
		GPIO_InitTypeDef GPIO_InitStructure;
		RCC_APB2PeriphClockCmd(Color_LED_CLK, ENABLE);
		RCC_APB2PeriphClockCmd(LED_CLK , ENABLE);
		//��GPIOʱ��
		
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;
		GPIO_InitStructure.GPIO_Pin =GREEN_LED_PIN|RED_LED_PIN|BLUE_LED_PIN;
		GPIO_InitStructure.GPIO_Speed =GPIO_Speed_50MHz;
		GPIO_Init(Color_LED_PORT ,&GPIO_InitStructure);
		//����ʼ�� �� ���ø��ʵ�
	
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;
		GPIO_InitStructure.GPIO_Pin =LED1_PIN |LED2_PIN ;
		GPIO_InitStructure.GPIO_Speed =GPIO_Speed_50MHz;
		GPIO_Init(LED_PORT  ,&GPIO_InitStructure);
		//����ʼ�������ø���ͨ��
		
		GPIO_SetBits(LED_PORT,LED1_PIN |LED2_PIN);
		GPIO_SetBits(Color_LED_PORT,GREEN_LED_PIN|RED_LED_PIN|BLUE_LED_PIN);
}



