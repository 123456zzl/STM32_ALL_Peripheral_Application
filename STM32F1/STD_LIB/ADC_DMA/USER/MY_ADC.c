#include "MY_ADC.h"


//ADC1 GPIO�ĳ�ʼ��
static void ADC1_GPIO_Config(void){
		GPIO_InitTypeDef GPIO_InitStructure;
		RCC_AHBPeriphClockCmd (RCC_AHBPeriph_DMA1 ,ENABLE );
		//����DMA1ʱ��
		RCC_APB2PeriphClockCmd (RCC_APB2Periph_ADC1|RCC_APB2Periph_GPIOC ,ENABLE );
		//����GPIOC��ADC1��ʱ��
		GPIO_InitStructure.GPIO_Pin =GPIO_Pin_1;
		GPIO_InitStructure.GPIO_Mode =GPIO_Mode_AIN;
		//ģ������ģʽ
		GPIO_Init(GPIOC,&GPIO_InitStructure);
	
}
//ADC1 �ĳ�ʼ��
void ADC1_Config(void){
		
		ADC_InitTypeDef ADC_InitStructure;
		
		ADC1_GPIO_Config();		//ADC1 GPIO ��ʼ��
	
		ADC_InitStructure.ADC_ContinuousConvMode =ENABLE ;
		//����ת��ģʽ����ͣ�Ľ���ADCת��
		ADC_InitStructure.ADC_DataAlign=ADC_DataAlign_Right ;
		//ͨ�������Ҷ���
		ADC_InitStructure.ADC_ExternalTrigConv=ADC_ExternalTrigConv_None ;
		//��ʹ���ⲿ����
		ADC_InitStructure.ADC_Mode=ADC_Mode_Independent ;
		//����ADCģʽ
		ADC_InitStructure.ADC_NbrOfChannel=1;
		//Ҫת����ͨ����Ŀ1
		ADC_InitStructure.ADC_ScanConvMode =DISABLE ;
		//��ʹ��ɨ��ģʽ,ɨ��ģʽ�Ƕ�ͨ��ADCʹ�õ�
		ADC_Init(ADC1,&ADC_InitStructure);
		
		RCC_ADCCLKConfig (RCC_PCLK2_Div8 );
		//����ADCʱ�ӣ�Ϊ8��Ƶ   9MHZ
		ADC_RegularChannelConfig (ADC1,ADC_Channel_11 ,1,ADC_SampleTime_55Cycles5 );
		//����ADC1��ͨ��Ϊ11Ϊ55.5����������
		ADC_Cmd (ADC1,ENABLE );
		ADC_ResetCalibration (ADC1);
		//��λУ׼�Ĵ���
		while(ADC_GetResetCalibrationStatus (ADC1));
		//�ȴ�У׼�Ĵ�����λ���
		ADC_SoftwareStartConvCmd (ADC1,ENABLE);

}







