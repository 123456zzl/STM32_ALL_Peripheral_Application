/**
  ******************************************************************************
  * @file    Project/STM32F4xx_StdPeriph_Templates/main.c 
  * @author  MCD Application Team
  * @version V1.8.0
  * @date    04-November-2016
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2016 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "string.h"


extern uint8_t Uart_Rec_Buf[USE_UART_REC_LEN];		//��������
/** @addtogroup Template_Project
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
	u8 run_time=0;
	u8 *p=0;
	u8 *tp=0;
	u8 paddr[18]; //��� P Addr:+p ��ַ�� ASCII ֵ
	u8 sramx=0; //Ĭ��Ϊ�ڲ� sram
	Systick_Init();
	
	LED_GPIO_Init();
	
	USART_Config();
	
	Delay_ms(100);
	
	printf("hello,world\r\n");
	
	Delay_ms(500);
	
	my_mem_init(SRAMIN); //��ʼ���ڲ��ڴ��
	my_mem_init(SRAMCCM); //��ʼ�� CCM �ڴ��
     
	/* Infinite loop */
	while (1)
	{
		if(KEY_UP==0){
			Delay_ms(30);
			if(KEY_UP==0){
				p=mymalloc(sramx,2048);//���� 2K �ֽ�
				if(p!=NULL)sprintf((char*)p,"Memory Malloc Test%03d",run_time);//�� p д������
			}
		}
		if(KEY_DOWN==0){
			Delay_ms(30);
			if(KEY_DOWN==0){
				if(p!=NULL)
				{
					sprintf((char*)p,"Memory Malloc Test%03d",run_time);//������ʾ����
					printf("p is %s\r\n",p);
				}
			}
		}
		if(KEY_Left==0){
			Delay_ms(30);
			if(KEY_Left==0){
				myfree(sramx,p); //�ͷ��ڴ�
				p=0; //ָ��յ�ַ
			}
		}
		if(KEY_Right==0){
			Delay_ms(30);
			if(KEY_Right==0){
				sramx++;
				if(sramx>1)sramx=0;
				if(sramx==0)printf("SRAMIN\r\n");
				else if(sramx==1)printf("SRAMEX\r\n");
			}
		}
		
		if(tp!=p)
		{
			tp=p;
			sprintf((char*)paddr,"P Addr:0X%08X",(u32)tp);
			printf("paddr:%s\r\n",paddr);	 //��ʾ p �ĵ�ַ
			if(p)printf("p:%s\r\n",p);//��ʾ P ������
		}
		Delay_ms(10);
		run_time++;
		if(run_time%100==0){
			run_time=0;
			LED_CON=!LED_CON;
		}
		//printf("%s\r\n",Uart_Rec_Buf);
	}
}


#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
