/**
  ******************************************************************************
  * @FileName:	Tool_CONN_AI.h
  * @Author:		Hui
  * @Version:		V1.0.0
  * @Date:			08072020
  * @Description:   
  * @Others:
  ******************************************************************************
  * @Copyright(C), 2020, Smokie Robotics, Inc
  ******************************************************************************
  * @History:
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TOOL_CONN_RS485_H
#define __TOOL_CONN_RS485_H
/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private Includes ----------------------------------------------------------*/
#include "BSP_UART.h"
#include "BSP_SPST.h"

/* Private Typedefs ----------------------------------------------------------*/

/* Macros --------------------------------------------------------------------*/
#define 	T485_Receive_ENABLE 		HAL_GPIO_WritePin(RS485CS_GPIO_Port, RS485CS_Pin, GPIO_PIN_RESET)
#define 	T485_Transmit_ENABLE 		HAL_GPIO_WritePin(RS485CS_GPIO_Port, RS485CS_Pin, GPIO_PIN_SET)
#define 	FT485_Receive_ENABLE 		HAL_GPIO_WritePin(FT485CS_GPIO_Port, FT485CS_Pin, GPIO_PIN_RESET)
#define 	FT485_Transmit_ENABLE 		HAL_GPIO_WritePin(FT485CS_GPIO_Port, FT485CS_Pin, GPIO_PIN_SET)
#define 	User_RS485_ENABLE 			T485_Receive_ENABLE;BSP_SPST_485_EN()



/* Private Variables ---------------------------------------------------------*/

/* Exported Functions --------------------------------------------------------*/
uint8_t User_RS485_Enable(void);
uint8_t User_RS485_Send_msg(uint16_t *data, uint16_t NumberOfByte);
#endif
/********************** (C) COPYRIGHT 2020 Smokie Robotics *****END OF FILE****/
