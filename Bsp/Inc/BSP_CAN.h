/**
  ******************************************************************************
  * @FileName:		BSP_CAN.h
  * @Author:		Hui
  * @Version:		V1.0.0
  * @Date:			
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
#ifndef __BSP_CAN_H
#define __BSP_CAN_H

/* Private Includes ----------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "BSP_UART.h"
#include <stdbool.h>

/* Private Typedefs ----------------------------------------------------------*/

/* Macros --------------------------------------------------------------------*/
#define CAN_ID_BASE    	  		0x0FD
#define CAN_ID_BROADCAST			0x0ff
#define CAN_HANDLE    	  		&hcan1
#define DEBUG_CAN_BUFF_SIZE 	8

/* Private Variables ---------------------------------------------------------*/

/* External Variables --------------------------------------------------------*/
extern CAN_HandleTypeDef hcan1;
extern uint8_t can_cmd_data[DEBUG_CAN_BUFF_SIZE];
extern uint8_t can_cmd_size;
extern bool new_can_cmd_flag;

/* Exported Functions --------------------------------------------------------*/
uint8_t BSP_CAN_Init(void);
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan);
uint8_t BSP_CANx_SendNormalData(uint16_t ID,uint8_t *pData,uint16_t Len);

void BSP_CAN_Test();

#endif
/********************** (C) COPYRIGHT 2020 Smokie Robotics *****END OF FILE****/

