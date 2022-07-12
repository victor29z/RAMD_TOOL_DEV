/**
  ******************************************************************************
  * @FileName:		FT_Sensor.h
  * @Author:		Hui
  * @Version:		V1.0.0
  * @Date:			08062020
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
#ifndef __FT_SENSOR_H
#define __FT_SENSOR_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "BSP_UART.h"
/* Private Includes ----------------------------------------------------------*/

/* Private Typedefs ----------------------------------------------------------*/

/* Macros --------------------------------------------------------------------*/
#define FT485_Receive_ENABLE 		HAL_GPIO_WritePin(FT485CS_GPIO_Port, FT485CS_Pin, GPIO_PIN_RESET)
#define FT485_Transmit_ENABLE 	HAL_GPIO_WritePin(FT485CS_GPIO_Port, FT485CS_Pin, GPIO_PIN_SET)
/* Private Variables ---------------------------------------------------------*/

/* External Variables --------------------------------------------------------*/

/* Exported Functions --------------------------------------------------------*/
uint8_t FT_RS485_Send_msg(uint16_t *data, uint16_t NumberOfByte);

#endif 
/********************** (C) COPYRIGHT 2020 Smokie Robotics *****END OF FILE****/
