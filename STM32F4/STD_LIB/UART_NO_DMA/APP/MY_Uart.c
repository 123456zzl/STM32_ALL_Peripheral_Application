#include "stdio.h"
#include "MY_Uart.h"
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
void USART_Config()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	RCC_AHB1PeriphClockCmd(UART_GPIO_CLOCK, ENABLE);
	// �򿪴���GPIO��ʱ��
	
	RCC_APB1PeriphClockCmd(UART_CLOCK, ENABLE);
	// �򿪴��������ʱ��
	GPIO_PinAFConfig(USART_GPIO_PORT,UART_TX_AF_PIN,GPIO_AF_USART2); //GPIOA2����ΪUSART2
	GPIO_PinAFConfig(USART_GPIO_PORT,UART_RX_AF_PIN,GPIO_AF_USART2); //GPIOA3����ΪUSART2
	GPIO_InitStructure.GPIO_Pin = UART_TX_PIN|UART_RX_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;			//GPIO_Mode_AF v1.8 GPIO_Mode_AF_PP v3.5
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;			//��������
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;				//����
	GPIO_Init(USART_GPIO_PORT, &GPIO_InitStructure);
	
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
	USART_Init(USE_UART2, &USART_InitStructure);
	// ��ɴ��ڵĳ�ʼ������
	
	UART_NVIC_Config();
	// �����ж����ȼ�����
	
	USART_ITConfig(USE_UART2, USART_IT_RXNE, ENABLE);	
	// ʹ�ܴ��ڽ����ж�
	
	USART_Cmd(USE_UART2, ENABLE);		
	// ʹ�ܴ���
	USART_ClearFlag(USE_UART2, USART_FLAG_TC); 
	// ���������ɱ�־	
}

//========����������һ���ַ�===================
void Uart_Send_Data_Nowait( USART_TypeDef * pUSARTx, uint8_t ch){
	/* ����һ���ֽ����ݵ�USART */
	USART_SendData(pUSARTx,ch);
}

//========�����������ַ�=======================
void Uart_Send_Data(USART_TypeDef *pUSARTx,uint8_t ch){
	/* ����һ���ֽ����ݵ�USART */
	USART_SendData(pUSARTx,ch);
	/* �ȴ��������ݼĴ���Ϊ�� */
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);	

}

//============���������ַ���========================
void Uart_Send_String(USART_TypeDef * pUSARTx, char *str)
{
	unsigned int k=0;
  do{
		USART_SendData( pUSARTx, *(str + k) );
		k++;
  }while(*(str + k)!='\0');
	
	while(USART_GetFlagStatus(pUSARTx,USART_FLAG_TC)==RESET);
}

//=============��������һ��16λ��=====================
void Uart_Send_Halfworld(USART_TypeDef * pUSARTx, uint16_t ch)
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
		USART_SendData(UART_Print, (uint8_t) ch);
		
		/* �ȴ�������� */
		while (USART_GetFlagStatus(UART_Print, USART_FLAG_TXE) == RESET);		
	
		return (ch);
}

//�ض���scanf�����ڣ���д����ʹ��scanf��getchar�Ⱥ���
int fgetc(FILE *f)
{
		/* �ȴ������������� */
		while (USART_GetFlagStatus(UART_Print, USART_FLAG_RXNE) == RESET);

		return (int)USART_ReceiveData(UART_Print);
}

void USART2_IRQHandler(void){
	uint8_t read_point;
	if(USART_GetITStatus(USART2,USART_IT_RXNE)!=RESET)
	{		
		read_point = USART_ReceiveData(USART2);
		Uart_Send_Data(USART2,read_point);   		//�����ܵ������ݷ��� 
	}	
}



