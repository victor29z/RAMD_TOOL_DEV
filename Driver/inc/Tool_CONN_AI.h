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
#ifndef __TOOL_CONN_AI_H
#define __TOOL_CONN_AI_H
/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private Includes ----------------------------------------------------------*/
#include "BSP_SPST.h"
#include "State_Observer.h"
/* Private Typedefs ----------------------------------------------------------*/

/* Macros --------------------------------------------------------------------*/
#define 	Read_Current	0
#define 	Read_Voltage	1

#define		Port_AI0	0
#define		Port_AI1	1


/* Private Variables ---------------------------------------------------------*/

/* Exported Functions --------------------------------------------------------*/
uint8_t AI_Port_Config(uint8_t Read_Type);
int32_t AI_Port_Read(uint8_t port, uint8_t Read_Type);

#endif
/********************** (C) COPYRIGHT 2020 Smokie Robotics *****END OF FILE****/
