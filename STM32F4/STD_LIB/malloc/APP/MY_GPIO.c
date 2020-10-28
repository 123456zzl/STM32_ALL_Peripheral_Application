#include "MY_GPIO.h"
#include "main.h"

void LED_GPIO_Init(void){
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);		// ʹ��GPIOC�˿�ʱ��
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);		// ʹ��GPIOC�˿�ʱ��
	
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_0;					// IO�ܽ�8
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;			// �������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;			// IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOC, &GPIO_InitStructure);						// �����趨������ʼ��GPIO	
	
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_13;					
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;	
	GPIO_Init(GPIOC, &GPIO_InitStructure);						// �����趨������ʼ��GPIO	
	
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_3;					
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;	
	GPIO_Init(GPIOE, &GPIO_InitStructure);						// �����趨������ʼ��GPIO

	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_2;					
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;	
	GPIO_Init(GPIOE, &GPIO_InitStructure);						// �����趨������ʼ��GPIO		
	
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_5;					
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;	
	GPIO_Init(GPIOE, &GPIO_InitStructure);						// �����趨������ʼ��GPIO		
	
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_6;					
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;	
	GPIO_Init(GPIOE, &GPIO_InitStructure);						// �����趨������ʼ��GPIO		

}













