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
#ifndef __BASE_STATE_OBSERVER_H
#define __BASE_STATE_OBSERVER_H


/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private Includes ----------------------------------------------------------*/

/* Private Typedefs ----------------------------------------------------------*/

/* Macros --------------------------------------------------------------------*/

/* Private Variables ---------------------------------------------------------*/

/* External Variables --------------------------------------------------------*/

/* Exported Functions --------------------------------------------------------*/
int32_t Get_ACin1(void);
int32_t Get_ACin2(void);
int32_t Get_AVin1(void);
int32_t Get_AVin2(void);
int32_t Get_Tool_Temp(void);
uint32_t Get_Power_Supply_Volt(void);
int32_t Get_Cur(void);

void Robot_State_Printf(void);

#endif
/********************** (C) COPYRIGHT 2020 Smokie Robotics *****END OF FILE****/


