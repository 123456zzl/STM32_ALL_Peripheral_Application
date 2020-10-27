/**
  ******************************************************************************
  * @file    MY_IWDG.c 
  * @author  yanzong
  * @version V1.0.1
  * @date    
  * @brief   
  ******************************************************************************
  * @attention
		�û���Ҫ�õĺ�����MY_IWDG_Feed_Dog();
  ******************************************************************************
  */
#include "MY_IWDG.h"


/*
param:

���Ź���Ƶ��32khz

pres:��Ƶ
	IWDG_Prescaler_4			���512ms
	IWDG_Prescaler_8			���1024ms
	IWDG_Prescaler_16			���2048ms
	IWDG_Prescaler_32			���4096ms
	IWDG_Prescaler_64			���8192ms
	IWDG_Prescaler_128		���16384ms
	IWDG_Prescaler_256		���32768ms
ms:����

*/
void MY_IWDG_Init(uint8_t pres,uint16_t  ms)
{
	IWDG_WriteAccessCmd (IWDG_WriteAccess_Enable);
	IWDG_SetPrescaler (pres);
	IWDG_SetReload(ms);
	IWDG_ReloadCounter();
	IWDG_Enable();
	
}
 void MY_IWDG_Feed_Dog(void)
{
	IWDG_ReloadCounter();
}



