/*
	�汾�ţ�v1.0
	����	�����ڵ������ư��LED
*/
#include "LED.h"

void LED_GPIO_Init(void){
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(LED_GPIO_CLK, ENABLE);		// ʹ��LED�˿�ʱ��
	GPIO_InitStructure.GPIO_Pin   = LED1_GPIO_PIN|LED2_GPIO_PIN|LED3_GPIO_PIN|LED4_GPIO_PIN;// IO�ܽ�
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;					// �������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;				// IO���ٶ�Ϊ50MHz
	GPIO_Init(LED_GPIO_Port, &GPIO_InitStructure);									// �����趨������ʼ��GPIO	
		
	LED1(1);LED2(1);LED3(1);LED4(1);
	
}



