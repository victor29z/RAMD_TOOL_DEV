/**
  ******************************************************************************
  * @FileName:	
  * @Author:		Frank
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
#ifndef __BSP_LED_H
#define __BSP_LED_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"


/* Private Includes ----------------------------------------------------------*/


/* Private Typedefs ----------------------------------------------------------*/

/* Macros --------------------------------------------------------------------*/
#define BSP_LED1_ON   			HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET)
#define BSP_LED1_OFF				HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET)
#define BSP_LED1_Toggle 		HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin)

#define IMU_Not_Found				BSP_LED1_ON
/* Private Variables ---------------------------------------------------------*/

/* Exported Functions --------------------------------------------------------*/
uint8_t BSP_LED_Init(void);



#endif 
/********************** (C) COPYRIGHT 2020 Smokie Robotics *****END OF FILE****/
