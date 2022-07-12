/**
  ******************************************************************************
  * @FileName:	
  * @Author:		Frank
  * @Version:		V1.0.0
  * @Date:			03-11-2020
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
#ifndef __APP_GLOBAL_H
#define __APP_GLOBAL_H


/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private Includes ----------------------------------------------------------*/
#include <stdbool.h> 
#include "Tool_CONN_DIO.h"
/* Private Typedefs ----------------------------------------------------------*/

/* Macros --------------------------------------------------------------------*/

/* Private Variables ---------------------------------------------------------*/

/* External Variables --------------------------------------------------------*/
extern bool firmware_update; 
extern uint16_t uart_err_frame_cnt;

/* Exported Functions --------------------------------------------------------*/
void House_Keeping(void);
void CMD_Processing(void);
uint8_t Find_IMU(void);


#endif
/********************** (C) COPYRIGHT 2020 Smokie Robotics *****END OF FILE****/


