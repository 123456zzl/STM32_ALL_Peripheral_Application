
/**
  ******************************************************************************
  * @file    TIM_InputCapture.c
  * @author  Fourth Team - yanzong
  * @version 	V1.0.0 ��ʹ��TIM1 ͨ��1 	��Ƶ100	1us�ɼ�һ�Σ�ʵ����Ƶ�ʼƵ�Ч��

											
  * @date    2020-10-29
  * @brief   TIM_InputCapture program body
  ******************************************************************************
  * @attention
  * Ӳ��ƽ̨:stm32f410
  ******************************************************************************
  */

#include "TIM_InputCapture.h"


uint32_t uhIC3ReadValue1 = 0;
uint32_t uhIC3ReadValue2 = 0;
uint32_t uhCaptureNumber = 0;
uint32_t uwCapture = 0;
uint32_t uwTIM1Freq = 0;
 
static void TIM_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* TIM1 clock enable */
  RCC_APB2PeriphClockCmd(TIM1_CLK, ENABLE);

  /* GPIOA clock enable */
  RCC_AHB1PeriphClockCmd(TIM1_GPIO_CLK, ENABLE);
  
  /* TIM1 channel 2 pin (PE.11) configuration */
  GPIO_InitStructure.GPIO_Pin =  TIM1_Input1Capture_Pin;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(TIM1_InputCapture_GPIO, &GPIO_InitStructure);

  /* Connect TIM pins to AF2 */
  GPIO_PinAFConfig(TIM1_InputCapture_GPIO, GPIO_PinSource8, GPIO_AF_TIM1);
  
  /* Enable the TIM1 global Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = TIM1_IT_Source;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  
}

void TIM_IC_Config(void){
	TIM_Config();

	TIM_ICInitTypeDef  TIM_ICInitStructure;
	TIM_TimeBaseInitTypeDef	TIM_TimeBaseStructure;

	TIM_TimeBaseStructure.TIM_Prescaler=100-1;										//8��Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;		//���ϼ���
	TIM_TimeBaseStructure.TIM_Period=0xffff;								//����
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;				//��Ƶ����
	TIM_TimeBaseInit(USE_TIM_IN,&TIM_TimeBaseStructure);

	

  TIM_ICInitStructure.TIM_Channel = TIM1_InputCapture_Channel;	//ͨ��	
  TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//
  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
  TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;				//�����Ƶ
  TIM_ICInitStructure.TIM_ICFilter = 0x0;
  TIM_ICInit(USE_TIM_IN, &TIM_ICInitStructure);

	TIM_Cmd(USE_TIM_IN,ENABLE);
	TIM_ITConfig(USE_TIM_IN,TIM_IT_CC1,ENABLE);

}

void TIM1_CC_IRQHandler(void){
  if(TIM_GetITStatus(USE_TIM_IN, TIM_IT_CC1) != RESET) 
  {
		
    /* Clear TIM1 Capture compare interrupt pending bit */
    TIM_ClearITPendingBit(USE_TIM_IN, TIM_IT_CC1);
		
    if(uhCaptureNumber == 0){				//�����һ��������
			uhCaptureNumber = 1;
      /* Get the Input Capture value */
      uhIC3ReadValue1 = TIM_GetCapture1(USE_TIM_IN);
			//CCR1 Ϊ��һ�����벶�� 1 �¼� (IC1) ����ʱ�ļ�����ֵ��
      
    }else if(uhCaptureNumber == 1){	//����ڶ���������
      uhCaptureNumber = 0;
      /* Get the Input Capture value */
      uhIC3ReadValue2 = TIM_GetCapture1(USE_TIM_IN); 
			//CCR1 Ϊ��һ�����벶�� 1 �¼� (IC1) ����ʱ�ļ�����ֵ��
      
      /* Capture computation */
      if (uhIC3ReadValue2 > uhIC3ReadValue1)
      {
        uwCapture = (uhIC3ReadValue2 - uhIC3ReadValue1); 
      }
      else if (uhIC3ReadValue2 < uhIC3ReadValue1)
      {
        uwCapture = ((0xffff - uhIC3ReadValue1) + uhIC3ReadValue2); 
      }
      else
      {
        uwCapture = 0;
      }
      /* Frequency computation */ 
      uwTIM1Freq = ((uint32_t) 1000000 / uwCapture);
      
    }
  }


}
