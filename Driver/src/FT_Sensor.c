/**
  ******************************************************************************
  * @FileName:	FT_Sensor.c
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


/* Includes ------------------------------------------------------------------*/


/* Private Includes ----------------------------------------------------------*/
#include "FT_Sensor.h"

/* Exported Functions --------------------------------------------------------*/
/**
  * @brief  
  * @param  None
	*
  * @retval None
  */

uint8_t FT_RS485_Send_msg(uint16_t *data, uint16_t NumberOfByte)
{
	uint8_t status;
	uint8_t *temp_data = (uint8_t *)data;
	
	FT485_Transmit_ENABLE;
	status = BSP_UART_Send(&FT485, temp_data, NumberOfByte);
	FT485_Receive_ENABLE;
	
	return status;
}

	
/********************** (C) COPYRIGHT 2020 Smokie Robotics *****END OF FILE****/
