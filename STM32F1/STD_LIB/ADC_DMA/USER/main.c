#include "stm32f10x.h"
#include "ADC_DMA.h"
#include "MY_ADC.h"
#include "Systick.h"
#include "UART.h"
#include "LED.h"

#include "stdio.h"
#define SYSCLK_FREQ_HSE

extern uint16_t __IO ADC1_DMA_Data_Buf[ADC1_DMA_Data_Size];

int main(void){
		//uint8_t i;
		SysTick_Init();
	
		ADC1_Config();
		//ADC1��ʼ��
		ADC1_DMA_Init();
		//ADC1 DMA�ĳ�ʼ��
		USART_Config();
		//���ڳ�ʼ��
	
		
		LED_Init();
		RED_LED_ON;
		//LED��ʼ��
		
		//uart_send_string(USART2,"c");
		printf("This is a ADC DMA Test!\r\n");
		while(1){
				delay_ms(1000);
				
				printf("NOW ADC1 DATA[0]=%d\r\n",ADC1_DMA_Data_Buf[0]);
		}

}








