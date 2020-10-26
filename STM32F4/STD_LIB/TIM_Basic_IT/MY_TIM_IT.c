/**
  ******************************************************************************
  * @file    STM32_ALL_Peripheral_Application\STM32F4\STD_LIB\UART_USE_DMA\APP\MY_TIM_IT.c
  * @author  Fourth Team - yanzong
  * @version V1.0.0
  * @date    2020-10-21
  * @brief   basic TIMER interrupt
  ******************************************************************************
  * @attention
  * Ӳ��ƽ̨:stm32f407zgt6
	* ������ʱ���ж�
  ******************************************************************************
  */
#include "MY_TIM_IT.h"


/*
	param:
	*psc:��Ƶ
	*arr:����

*/

void Basic_TIM_Init(uint16_t psc,uint32_t arr){
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	RCC_APB1PeriphClockCmd(USE_Basic_TIM_CLK,ENABLE);  ///ʹ��USE_Basic_TIMʱ��
	
	NVIC_InitStructure.NVIC_IRQChannel=USE_Basic_TIM_IRQn; 							//��ʱ��3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x03; 	//��ռ���ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x03; 				//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
  TIM_TimeBaseInitStructure.TIM_Period = arr; 			//�Զ���װ��ֵ
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  		//��ʱ����Ƶ
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(USE_Basic_TIM,&TIM_TimeBaseInitStructure);//��ʼ��USE_Basic_TIM
	TIM_ClearFlag(USE_Basic_TIM, TIM_FLAG_Update);
	TIM_ITConfig(USE_Basic_TIM,TIM_IT_Update,ENABLE); //����ʱ��3�����ж�
	TIM_Cmd(USE_Basic_TIM,ENABLE); 										//ʹ�ܶ�ʱ��3
	
	
	
}


__weak void Basic_IT_Callback(void){
									
}

//��ʱ��2�жϷ�����
void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(USE_Basic_TIM,TIM_IT_Update)!= RESET) //����ж�
	{
		Basic_IT_Callback();
		TIM_ClearITPendingBit(USE_Basic_TIM,TIM_IT_Update);  //����жϱ�־λ
	}
	
}





