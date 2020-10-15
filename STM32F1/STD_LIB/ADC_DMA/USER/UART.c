#include "stdio.h"
#include "UART.h"
 /**
  * @brief  ����Ƕ�������жϿ�����NVIC
  * @param  ��
  * @retval ��
  */
static void UART_NVIC_Config(void)
{
  NVIC_InitTypeDef NVIC_InitStructure; 
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  /* Ƕ�������жϿ�������ѡ�� */
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
 /* ����USARTΪ�ж�Դ */
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
   /* �������ȼ�*/
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  /* �����ȼ� */
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  /* ʹ���ж� */
  NVIC_Init(&NVIC_InitStructure);
	/* ��ʼ������NVIC */
}

 /**
  * @brief  USART GPIO ����,������������
  * @param  ��
  * @retval ��
  */
void USART_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	// �򿪴���GPIO��ʱ��
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	// �򿪴��������ʱ��

	GPIO_InitStructure.GPIO_Pin = UART2_TX_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(USART2_GPIO_PORT, &GPIO_InitStructure);
	// ��USART Tx��GPIO����Ϊ���츴��ģʽ

	GPIO_InitStructure.GPIO_Pin = UART2_RX_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(USART2_GPIO_PORT, &GPIO_InitStructure);
	// ��USART Rx��GPIO����Ϊ��������ģʽ
	
	//���ô��ڵĹ�������
	USART_InitStructure.USART_BaudRate = 115200;
	// ���ò�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	// ���� �������ֳ�
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	// ����ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	// ����У��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	// ����Ӳ��������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	// ���ù���ģʽ���շ�һ��
	USART_Init(USART2, &USART_InitStructure);
	// ��ɴ��ڵĳ�ʼ������
	
	UART_NVIC_Config();
	// �����ж����ȼ�����
	
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);	
	// ʹ�ܴ��ڽ����ж�
	
	USART_Cmd(USART2, ENABLE);		
	// ʹ�ܴ���
	//USART_ClearFlag(USART1, USART_FLAG_TC); 
	// ���������ɱ�־	
}

//========����������һ���ַ�===================
void uart_send_data_nowait( USART_TypeDef * pUSARTx, uint8_t ch){
	/* ����һ���ֽ����ݵ�USART */
	USART_SendData(pUSARTx,ch);
}

//========�����������ַ�=======================
void uart_send_data(USART_TypeDef *pUSARTx,uint8_t ch){
	/* ����һ���ֽ����ݵ�USART */
	USART_SendData(pUSARTx,ch);
	/* �ȴ��������ݼĴ���Ϊ�� */
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);	

}

//============�����ַ���========================
void uart_send_string(USART_TypeDef * pUSARTx, char *str)
{
	unsigned int k=0;
  do{
		USART_SendData( pUSARTx, *(str + k) );
		k++;
  }while(*(str + k)!='\0');
	
	while(USART_GetFlagStatus(pUSARTx,USART_FLAG_TC)==RESET);
}

//=============����һ��16λ��=====================
void uart_send_halfworld(USART_TypeDef * pUSARTx, uint16_t ch)
{
	uint8_t temp_h, temp_l;
	/* ȡ���߰�λ */
	temp_h = (ch&0XFF00)>>8;
	/* ȡ���Ͱ�λ */
	temp_l = ch&0XFF;
	
	/* ���͸߰�λ */
	USART_SendData(pUSARTx,temp_h);	
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
	
	/* ���͵Ͱ�λ */
	USART_SendData(pUSARTx,temp_l);	
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);	
}


//�ض���printf�����ڣ��ض�����ʹ��printf����
int fputc(int ch, FILE *f)
{
		/* ����һ���ֽ����ݵ����� */
		USART_SendData(USART2, (uint8_t) ch);
		
		/* �ȴ�������� */
		while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);		
	
		return (ch);
}

//�ض���scanf�����ڣ���д����ʹ��scanf��getchar�Ⱥ���
int fgetc(FILE *f)
{
		/* �ȴ������������� */
		while (USART_GetFlagStatus(USART2, USART_FLAG_RXNE) == RESET);

		return (int)USART_ReceiveData(USART2);
}

void USART2_IRQHandler(void){
	uint8_t read_point;
	if(USART_GetITStatus(USART2,USART_IT_RXNE)!=RESET)
	{		
		read_point = USART_ReceiveData(USART2);
    uart_send_data(USART2,read_point);   		//�����ܵ������ݷ��� 
	}	
}



