/**
  ******************************************************************************
  * @FileName:		BSP_Global.h
  * @Author:		Hui
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
#ifndef __BSP_GLOBAL_H
#define __BSP_GLOBAL_H


/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private Includes ----------------------------------------------------------*/
#include "BSP_LED.h"
#include "BSP_UART.h"
#include "BSP_ADC.h"
#include "BSP_24AA16.h"
#include "BSP_ICM20600.h"
#include "BSP_CAN.h"
#include "BSP_STM32_Flash.h"
#include "BSP_Encrypt.h"
#include "BSP_Timer.h"
#include "BSP_CPU_ID.h"
#include "BSP_Output.h"
#include "BSP_SPST.h"
#include "BSP_STO.h"
#include "BSP_AX58100.h"
/* Private Typedefs ----------------------------------------------------------*/

/* Macros --------------------------------------------------------------------*/

/* Private Variables ---------------------------------------------------------*/

/* External Variables --------------------------------------------------------*/

/* Exported Functions --------------------------------------------------------*/
uint8_t BSP_Global_Init(void);

#endif
/********************** (C) COPYRIGHT 2020 Smokie Robotics *****END OF FILE****/


