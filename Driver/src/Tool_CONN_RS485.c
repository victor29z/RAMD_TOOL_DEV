/**
  ******************************************************************************
  * @FileName:	Tool_CONN_RS485.c
  * @Author:		Hui
  * @Version:		V1.0.0
  * @Date:			08062020
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


/* Private Includes ----------------------------------------------------------*/
#include "Tool_CONN_RS485.h"

/* Exported Functions --------------------------------------------------------*/
/**
  * @brief  
  * @param  None
	*
  * @retval None
  */
uint8_t User_RS485_Enable(void)
{
	BSP_SPST_485_EN();
	
	return 0;
}

uint8_t User_RS485_Send_msg(uint16_t *data, uint16_t NumberOfByte)
{
	uint8_t status;
	uint8_t *temp_data = (uint8_t *)data;
	
	T485_Transmit_ENABLE;
	status = BSP_UART_Send(&T485, temp_data, NumberOfByte);
	T485_Receive_ENABLE;
	
	return status;
}



/********************** (C) COPYRIGHT 2020 Smokie Robotics *****END OF FILE****/
