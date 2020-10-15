#include "ADC_DMA.h"

uint16_t __IO ADC1_DMA_Data_Buf[ADC1_DMA_Data_Size];
//ADC1 DMA�ĳ�ʼ��
void ADC1_DMA_Init(void){
	
		DMA_InitTypeDef DMA_InitStructure;
	
		DMA_InitStructure.DMA_PeripheralBaseAddr =ADC1_DR_Addr;
		//�������ַ
		DMA_InitStructure.DMA_BufferSize =ADC1_DMA_Data_Size;
		//��������Ĵ�С
		DMA_InitStructure.DMA_DIR =DMA_DIR_PeripheralSRC;
		//DMA���ͷ���
		DMA_InitStructure.DMA_M2M =DISABLE ;
		//�ڴ浽�ڴ淽��
		DMA_InitStructure.DMA_MemoryBaseAddr =(u32)ADC1_DMA_Data_Buf;
		//�����ַ
		DMA_InitStructure.DMA_MemoryDataSize =DMA_MemoryDataSize_HalfWord;
		//�ڴ����ݵ�λ
		DMA_InitStructure.DMA_MemoryInc =DMA_MemoryInc_Enable;
		//�ڴ�����
		DMA_InitStructure.DMA_Mode =DMA_Mode_Circular;
		//DMAmode
		DMA_InitStructure.DMA_PeripheralDataSize =DMA_PeripheralDataSize_HalfWord;
		//�������ݵ�λ
		DMA_InitStructure.DMA_PeripheralInc  =DMA_PeripheralInc_Disable;
		//�����ַ������
		DMA_InitStructure.DMA_Priority =DMA_Priority_High;
		//�������ȼ�
		DMA_Init(DMA1_Channel1 ,&DMA_InitStructure);
		
		DMA_Cmd (DMA1_Channel1,ENABLE );
		ADC_DMACmd (ADC1,ENABLE );
	
}



