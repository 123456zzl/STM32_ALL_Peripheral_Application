/**
******************************************************************************
* @file         w5100s_conf.c                                                                                              
* @version      V1.0                          
* @date         2018-06-18             
* @brief        ����MCU����ֲw5100s������Ҫ�޸ĵ��ļ�������w5100s��MAC��IP��ַ   
*        
* @company      ��������Ƽ����޹�˾
* @information  WIZnet W5100s�ٷ������̣�ȫ�̼���֧�֣��۸����ƴ�
* @website      www.wisioe.com   
* @forum        www.w5100s.com
* @qqGroup      579842114                                                     
******************************************************************************
*/

#include "stdio.h" 
#include "string.h"
#include "w5100s_conf.h"
#include "utility.h"
#include "w5100s.h"
#include "socket.h"
//#include "bsp_TiMbase.h"
//#include "bsp_flash.h"

extern TIM_HandleTypeDef htim2;

#include "DHCP.h"

CONFIG_MSG  ConfigMsg, RecvMsg;                             // ���ýṹ��

uint16 rxlen=0;
uint8 rxbuf[1024];

/*MAC��ַ���ֽڱ���Ϊż��
  ������W5100s�����������ͬһ�ֳ���������ʹ�ò�ͬ��MAC��ַ
*/
uint8 mac[6]={0x00,0x08,0xdc,0x22,0x33,0x33};

/*����Ĭ��IP��Ϣ*/
uint8 local_ip[4] = {192,168,1,233};                        // ����W5100sĬ��IP��ַ
uint8 subnet[4] = {255,255,255,0};                          // ����W5100sĬ����������
uint8 gateway[4] = {192,168,1,1};                           // ����W5100sĬ������
uint8 dns_server[4] = {114,114,114,114};                    // ����W5100sĬ��DNS

uint16 local_port = 8080;                                   // ���屾�ض˿�

/*����Զ��IP��Ϣ*/
uint8  remote_ip[4] = {192,168,1,100};                      // Զ��IP��ַ
uint16 remote_port = 8080;                                  // Զ�˶˿ں�

/*IP���÷���ѡ��������ѡ��*/
uint8  ip_from=IP_FROM_DEFINE;      

uint32 ms=0;                                                // �������
__IO uint8_t    ntptimer = 0;                                        // NPT�����



/**
*@brief  ����W5100s��IP��ַ
*@param  ��
*@return ��
*/
void set_w5100s_netinfo(void)
{
  volatile uint8 temp;
  // ���ƶ����������Ϣ�����ýṹ��
  memcpy(ConfigMsg.mac, mac, 6);
  memcpy(ConfigMsg.lip,local_ip,4);
  memcpy(ConfigMsg.sub,subnet,4);
  memcpy(ConfigMsg.gw,gateway,4);
  memcpy(ConfigMsg.dns,dns_server,4);
#ifdef DEBUG_HTTP
/*����ʹ��HTTP Server����ʱ��Ч��ʹ������"http_server.h"ͷ�ļ�������*/
  ReadFlashNBtye(0,&temp,1);
  if(temp != 255)
    ip_from = IP_FROM_FLASH;
  else
    ip_from = IP_FROM_DEFINE;
#endif
  switch(ip_from)
  {
    case IP_FROM_DEFINE:
      printf(" ʹ�ö����IP��Ϣ����W5100S��\r\n");
      break;
      
    case IP_FROM_FLASH:
      printf(" ʹ��Flash��IP��Ϣ����W5100S��\r\n");
//      ReadFlashNBtye(0,ConfigMsg.lip,12);
      break;
  }
  setSUBR(ConfigMsg.sub);
  setGAR(ConfigMsg.gw);
  setSIPR(ConfigMsg.lip);

  getSIPR (local_ip);      
  printf(" W5100S IP��ַ   : %d.%d.%d.%d\r\n", local_ip[0],local_ip[1],local_ip[2],local_ip[3]);
  getSUBR(subnet);
  printf(" W5100S �������� : %d.%d.%d.%d\r\n", subnet[0],subnet[1],subnet[2],subnet[3]);
  getGAR(gateway);
  printf(" W5100S ����     : %d.%d.%d.%d\r\n", gateway[0],gateway[1],gateway[2],gateway[3]);
}

/**
*@brief  ����W5100S��MAC��ַ
*@param  ��
*@return ��
*/
void set_w5100s_mac(void)
{
  // ����������Ϣ��������Ҫѡ��  
  ConfigMsg.sw_ver[0]=FW_VER_HIGH;
  ConfigMsg.sw_ver[1]=FW_VER_LOW;  
  
  memcpy(ConfigMsg.mac, mac, 6);
  setSHAR(ConfigMsg.mac);
  getSHAR(mac);
  printf(" W5100S MAC��ַ  : %02x.%02x.%02x.%02x.%02x.%02x\r\n", mac[0],mac[1],mac[2],mac[3],mac[4],mac[5]);
}
  

/**
*@brief  W5100s��λ���ú���
*@param  ��
*@return ��
*/
void reset_w5100s(void)
{
  HAL_GPIO_WritePin(W5100S_RESET_GPIO,W5100S_RESET_PIN,GPIO_PIN_RESET);
  HAL_Delay(500);  
  HAL_GPIO_WritePin(W5100S_RESET_GPIO,W5100S_RESET_PIN,GPIO_PIN_SET);
  HAL_Delay(1500);  

}

/**
*@brief  STM32ϵͳ��λ����
*@param  ��
*@return ��
*/
void reboot(void)
{
  pFunction Jump_To_Application;
  uint32 JumpAddress;
  printf(" ϵͳ�����С���\r\n");
  JumpAddress = *(__IO uint32_t*) (0x00000004);
  Jump_To_Application = (pFunction) JumpAddress;
  Jump_To_Application();
}

/**
*@brief  dhcp�õ��Ķ�ʱ����ʼ��
*@param  ��
*@return ��
*/
void dhcp_timer_init(void)
{
  MX_TIM2_Init();                                 
}

/**
*@brief  ntp�õ��Ķ�ʱ����ʼ��
*@param  ��
*@return ��
*/
void ntp_timer_init(void)
{
  MX_TIM2_Init();                                 
}

/**
*@brief  STM32��ʱ��2��ʼ��
*@param  ��
*@return ��
*/
void timer2_init(void)
{
    HAL_TIM_Base_MspInit(&htim2);     //  TIM2 ���¿�ʱ�ӣ���ʼ��ʱ
		HAL_TIM_Base_Start(&htim2);
}

/**
*@brief  ��ʱ��2�жϺ���
*@param  ��
*@return ��
*/
void timer2_isr(void)
{
  ms++;  
  if(ms>=1000)
  {  
    ms=0;
    dhcp_time++;             // DHCP��ʱ��1S
#ifndef __NTP_H__
    ntptimer++;              // NTP����ʱ���1S
#endif
  }
}

/**
*@brief  ������������
*@param  ��
*@return ��
*/
void PHY_check(void)
{
  uint8 PHY_connect=0;
  PHY_connect=0x01&getPHYStatus();
  if(PHY_connect==0)
  {
    printf(" \r\n ���������Ƿ�����?\r\n");
    PHY_connect = 0;
    do
    {
      close(PHY_connect++);
    }while(PHY_connect < 4);
    PHY_connect = 0;
    while(PHY_connect == 0) { 
      PHY_connect=0x01&getPHYStatus();  
      printf(" .");
      HAL_Delay(500);
    }
    printf(" \r\n");  
  }
}
/**
*@brief  ��ȡPHY�Ĵ�������
*@param  ��
*@return PHYSR�Ĵ�����ֵ
*/
uint8 getPHYStatus( void )
{
  return IINCHIP_READ(PHYSR);
}

/**
*@brief  ����4��socket�շ������С
*@param  tx_size:���ͻ��棻rx_size:���ջ���
*@return ��
//RX memory size register, R/W, default=0x55
//--------------------------------------------------------    S1      S0      Memory size
//  Socket3    |  Socket2    |  Socket1    |  Socket0    |    0       0           1KB
//-------------|-------------|-------------|-------------|    0       1           2KB
//S1       S0  |S1       S0  |S1       S0  |S1       S0  |    1       0           4KB
//--------------------------------------------------------    1       1           8KB
*/
void sysinit(uint8 tx_size,uint8 rx_size)
{
	IINCHIP_WRITE(RMSR,tx_size);
	IINCHIP_WRITE(TMSR,rx_size);
}
