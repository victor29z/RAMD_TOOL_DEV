/**
  ******************************************************************************
  * @FileName:	BSP_DO_PWR_CTRL.h
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
#ifndef __BSP_DO_PWR_CTRL_H
#define __BSP_DO_PWR_CTRL_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private Includes ----------------------------------------------------------*/


/* Private Typedefs ----------------------------------------------------------*/

/* Macros --------------------------------------------------------------------*/
#define BSP_DO_PWR_CTRL_EN		HAL_GPIO_WritePin(CPUEN_GPIO_Port, CPUEN_Pin, GPIO_PIN_SET)
#define BSP_DO_PWR_CTRL_DEN		HAL_GPIO_WritePin(CPUEN_GPIO_Port, CPUEN_Pin, GPIO_PIN_RESET)
#define BSP_DO_PWR_CTRL_12V 	BSP_DO_PWR_CTRL_EN;HAL_GPIO_WritePin(CPU_POWER_GPIO_Port, CPU_POWER_Pin, GPIO_PIN_SET)
#define BSP_DO_PWR_CTRL_24V 	BSP_DO_PWR_CTRL_EN;HAL_GPIO_WritePin(CPU_POWER_GPIO_Port, CPU_POWER_Pin, GPIO_PIN_RESET)

/* Private Variables ---------------------------------------------------------*/

/* Exported Functions --------------------------------------------------------*/
uint8_t BSP_DO_PWR_CTRL_Init(void);

void BSP_DO_PWR_CTRL_Test(void);

#endif 
/********************** (C) COPYRIGHT 2020 Smokie Robotics *****END OF FILE****/
