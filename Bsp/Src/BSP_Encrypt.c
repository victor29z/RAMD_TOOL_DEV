/**
  ******************************************************************************
  * @FileName:	encrypt.c
  * @Author:		Victor
  * @Version:		V1.0.0
  * @Date:			06-08-2020
  * @Description:   
  * @Others:
  ******************************************************************************
  * @FunctionsList:	
  *
  *
  ******************************************************************************
  * @Copyright(C), 2020 Smokie Robotics, Inc
  ******************************************************************************
  * @History:
  *
  ******************************************************************************
  */


/* Includes ------------------------------------------------------------------*/


/* Private Includes ----------------------------------------------------------*/
#include "BSP_Encrypt.h"
#include "BSP_Timer.h"
#include "BSP_UART.h"
#include "BSP_LED.h"



/* Variables -----------------------------------------------------------------*/
const uint8_t Head_Buf[4]={0x80,0x08,0x00,0x00}; 
const uint8_t Cmd_Buf[4]={0x00,0xc0,0x00,0x00};

uint8_t transmit_data[64];
uint8_t receive_data[64];   // ���ڽ������ݻ�����


/* Private Functions ---------------------------------------------------------*/
static void BSP_Set_Encrypt_IO_Input(void);
static void BSP_Set_Encrypt_IO_Output(void);
static void BSP_Encrypt_Reset(void);

static uint8_t BSP_Uart_Rev(uint8_t counter, uint8_t* rev_buf);
static void BSP_Uart_Send(uint8_t counter, const uint8_t* send_buf);

/* Exported Functions --------------------------------------------------------*/

/**
  * @Name   uint8_t bsp_Encrypt_init(void)
  * @Param  None
  * @retval None
  * @brief  
  *
  */
uint8_t BSP_Encrypt_Init(void)
{
  printf("Initializing Encryption ... ");
  
  BSP_Encrypt_Reset();
  
	printf("Done\r\n");
  
  return 0;
}

/***********************************************************************************************
	�������ƣ�uint8_t Countbit(uint8_t x)
	�������룺x�����ջ��͵ĵ��ֽ�����
	�����������
	�������ܣ����㵥�ֽ����ݵ�ż����λ
	����˵����
************************************************************************************************/
uint8_t Countbit(uint8_t x)
{
	x = (x & 0x55) + ((x >> 1)  & 0x55);
	x = (x & 0x33) + ((x >> 2)  & 0x33);
	x = (x & 0x0f) + ((x >> 4)  & 0x0f);
	return (x);
}


/**
  * @Name   static void BSP_Set_Encrypt_IO_Input(void)
  * @Param  None
  * @retval None
  * @brief  
  *
  */
static void BSP_Set_Encrypt_IO_Input(void)
{
  GPIO_InitTypeDef GPIO_InitStructure = {0};
    
  GPIO_InitStructure.Pin = ENCRYPT_IO_PIN;
	GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
	GPIO_InitStructure.Pull = GPIO_NOPULL;
	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_VERY_HIGH;

	HAL_GPIO_Init(GPIO_PORT_ENCRYPT_IO, &GPIO_InitStructure);
}

/**
  * @Name   static set_Encrypt_IO_output(void)
  * @Param  None
  * @retval None
  * @brief  
  *
  */
static void BSP_Set_Encrypt_IO_Output(void)
{
  GPIO_InitTypeDef GPIO_InitStructure = {0};
  
  GPIO_InitStructure.Pin = ENCRYPT_IO_PIN;
	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStructure.Pull = GPIO_NOPULL;
	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_VERY_HIGH;

	HAL_GPIO_Init(GPIO_PORT_ENCRYPT_IO, &GPIO_InitStructure);
}


/**
  * @Name   static void Encrypt_reset(void)
  * @Param  None
  * @retval None
  * @brief  
  *
  */
static void BSP_Encrypt_Reset(void)
{
  BSP_Set_Encrypt_IO_Output();
	
	/* ����Ϊ�ߣ��ȴ�����LKT����оƬ���͵���ʼλ */
  ENCRYPT_RST_1();
	
  ENCRYPT_RST_0();
  HAL_Delay(5);
	
  ENCRYPT_RST_1();
	
  BSP_Uart_Rev(18,receive_data);			//  ��λ���ո�λ��Ϣ
  if(receive_data[0] != 0x3B || receive_data[1] != 0x7D)
	{		
		printf("fail\n");
    while(1);
	}
  HAL_Delay(1);           //add 100us delay before sending new msg.
}



/**
  * @Name   static uint8_t BSP_Uart_Rev_Char(uint8_t counter)
  * @Param  None
  * @retval None
  * @brief  
  *
  */
static uint8_t BSP_Uart_Rev(uint8_t counter, uint8_t* rev_buf)
{
	uint8_t   i , n , cIO;
	uint32_t  time=0;																											 

  BSP_Set_Encrypt_IO_Input();     																									//��ʼ��io����?
	for(n = 0; n < counter; n++)				   					    					//����m���ֽڵ�����
	{			
		while( ENCRYPT_IO_READ() ) 								//�ж���ʼλ
		{
		    BSP_Timer_Delay_Us(2);
		    time++;	
				if(time>=0x600000)
				{
					return 1;	                          										//��ʱ���� 1����ʱʱ��ɸ������������㷨������ʱ�����
				}
		}  
		cIO = 0x00;
		BSP_Timer_Delay_Us(30);
		for(i = 0; i < 8; i++)   		   	  														// ����1�ֽڵ�����
		{
		    BSP_Timer_Delay_Us(etu);
			  cIO |= ((ENCRYPT_IO_READ()) ? (1 << i) : (0 << i));	    
    }			
		rev_buf[n] = cIO;	                 
		BSP_Timer_Delay_Us(etu);					 						      								//����ʱ����У��λ������У��ɽ���У��λ���д���
	  BSP_Timer_Delay_Us(2*etu);																						//����2ֹͣλ
	}
	return 0;              																					// ͨѶ�������� 0
}


/**
  * @Name   static void BSP_Uart_Send(uint8_t counter, uint8_t* send_buf)
  * @Param  None
  * @retval None
  * @brief  
  *
  */
static void BSP_Uart_Send(uint8_t counter, const uint8_t* send_buf)
{
	uint8_t i , n , uChar = 0 , Even = 0;

	BSP_Set_Encrypt_IO_Output();      															//��ʼ��io���š�
	for(n = 0;n < counter; n++)				 															//����m���ֽڵ�����
	{	
		uChar  = send_buf[n];
		Even   = Countbit(uChar); 
		ENCRYPT_IO_0();	 
		for(i = 0; i < 8; i++)				 																//����һ�ֽ�����
		{	
			BSP_Timer_Delay_Us(etu);
			(uChar & (1 << i)) ? (ENCRYPT_IO_1()) : (ENCRYPT_IO_0());
		}  			   

		BSP_Timer_Delay_Us(etu);
		(Even % 2 == 1) ? ENCRYPT_IO_1() : (ENCRYPT_IO_0());					//�ж���żУ��λ	
		BSP_Timer_Delay_Us(etu);
		ENCRYPT_IO_1();   
		BSP_Timer_Delay_Us(2*etu);						  											//����2ֹͣλ 					
	}
}

/**
  * @Name   static void Encrypt_Get_Stream(uint8_t cmd, uint8_t retLength)
  * @Param  None
  * @retval None
  * @brief  
  *
  */
void BSP_Encrypt_Get_Stream(uint8_t cmd, uint8_t retLength)
{
  uint8_t ucTmp[32];
  uint8_t i;
  uint8_t com_length = retLength+1;
  
	/* ����T=0Э������LKT����оƬ����ǰ5�ֽڣ�LKT����оƬӦ���صڶ��ֽ� */
  /* 80 08 00 00 */
  BSP_Uart_Send(4, Head_Buf);

  ucTmp[0] = retLength+1;
  /* data length = 0x09 */
  BSP_Uart_Send(1, &com_length);
  
  BSP_Timer_Delay_Us(etu);		//?????
  
  /* 0x08 */
  BSP_Uart_Rev(1,receive_data);			//recieve	INS
  
  ucTmp[0] = cmd;			//�㷨�������
  
  for(i = 1; i < com_length; i++)
  {
    ucTmp[i] = transmit_data[i-1];	//�����㷨�����еĲ���
  }
  BSP_Timer_Delay_Us(2*etu);		//??????

  BSP_Uart_Send(com_length, ucTmp);
  
  BSP_Uart_Rev(2,receive_data);         // 0x61, ret length; Recieve SW

  if(receive_data[0] != 0x61 || receive_data[1] != retLength)
    return;

  BSP_Timer_Delay_Us(etu);
	BSP_Uart_Send(4, Cmd_Buf);			//���ͻ�ȡ�������� 00 c0 00 00
  
  BSP_Uart_Send(1, &retLength);   //get retLength data

	BSP_Uart_Rev(1,receive_data);         // 0xc0 + retLength byte + 0x90 + 0x00; INS + return values + SW(2 bytes)
	BSP_Uart_Rev(retLength+2,receive_data);

  BSP_Timer_Delay_Us(etu);
}


/**
  * @Name   static uint8_t Encrypt_ChipID_Check(void)
  * @Param  None
  * @retval None
  * @brief  
  *
  */
uint8_t BSP_Encrypt_Chip_Check(void)
{
  uint8_t i = 0;
	uint8_t ucBoardID[8];
  
  for (i = 0; i< 8; i++)
  {
    ucBoardID[i] = i+1;
  }
  
  memcpy(transmit_data, ucBoardID, 8);
  memset(receive_data, 0, sizeof(receive_data));
  HAL_Delay(100);
  __disable_irq();
	BSP_Encrypt_Get_Stream(FUNC_CHIP_ID,8);
  __enable_irq();
  
  for (i = 0; i < 8; i++) {
    if ((ucBoardID[i] + receive_data[i]) != 0xff )  //ȡ��
    {
      printf("Encryption check fail! \r\n");
      return 1;
    }
  }
  
  printf("Encryption check pass! \r\n\r\n");
  return 0;
}

/********************** (C) COPYRIGHT 2020 Smokie Robotics *****END OF FILE****/

