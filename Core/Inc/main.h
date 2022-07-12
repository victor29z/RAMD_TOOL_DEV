/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "BSP_Global.h"
#include "App_Global.h"
#include "EEPROM_RW.h"
#include "Flash_RW.h"
#include "FT_Sensor.h"
#include "Tool_CONN_DIO.h"
#include "Tool_CONN_AI.h"
#include "Tool_CONN_RS485.h"
#include "Tic_Toc.h"
#include "Clock.h"
#include "Test.h"

#include "BSP_INA237.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define CPUEN_Pin GPIO_PIN_3
#define CPUEN_GPIO_Port GPIOE
#define MUX_EN_Pin GPIO_PIN_2
#define MUX_EN_GPIO_Port GPIOE
#define MUX1_A0_Pin GPIO_PIN_1
#define MUX1_A0_GPIO_Port GPIOE
#define MUX1_A1_Pin GPIO_PIN_0
#define MUX1_A1_GPIO_Port GPIOE
#define EEP_DONE_Pin GPIO_PIN_5
#define EEP_DONE_GPIO_Port GPIOB
#define TOOL_IN0_Pin GPIO_PIN_14
#define TOOL_IN0_GPIO_Port GPIOG
#define TOOL_IN1_Pin GPIO_PIN_13
#define TOOL_IN1_GPIO_Port GPIOG
#define MUX2_A1_Pin GPIO_PIN_4
#define MUX2_A1_GPIO_Port GPIOB
#define MUX2_A0_Pin GPIO_PIN_3
#define MUX2_A0_GPIO_Port GPIOB
#define CPU_POWER_Pin GPIO_PIN_4
#define CPU_POWER_GPIO_Port GPIOE
#define ESC_RSTn_Pin GPIO_PIN_5
#define ESC_RSTn_GPIO_Port GPIOE
#define PWR_ALERT_Pin GPIO_PIN_10
#define PWR_ALERT_GPIO_Port GPIOG
#define LED1_Pin GPIO_PIN_10
#define LED1_GPIO_Port GPIOC
#define CAN_TX_Pin GPIO_PIN_12
#define CAN_TX_GPIO_Port GPIOA
#define CPUIO2_Pin GPIO_PIN_9
#define CPUIO2_GPIO_Port GPIOG
#define STO1_Pin GPIO_PIN_3
#define STO1_GPIO_Port GPIOI
#define STO0_Pin GPIO_PIN_2
#define STO0_GPIO_Port GPIOI
#define CAN_RX_Pin GPIO_PIN_11
#define CAN_RX_GPIO_Port GPIOA
#define ESC_RUN_Pin GPIO_PIN_2
#define ESC_RUN_GPIO_Port GPIOD
#define FT485_RX_Pin GPIO_PIN_10
#define FT485_RX_GPIO_Port GPIOA
#define FT485_TX_Pin GPIO_PIN_9
#define FT485_TX_GPIO_Port GPIOA
#define ESC_ERR_Pin GPIO_PIN_9
#define ESC_ERR_GPIO_Port GPIOC
#define FT485CS_Pin GPIO_PIN_8
#define FT485CS_GPIO_Port GPIOA
#define RS485CS_Pin GPIO_PIN_8
#define RS485CS_GPIO_Port GPIOC
#define RS485RX_Pin GPIO_PIN_7
#define RS485RX_GPIO_Port GPIOC
#define CPUIO3_Pin GPIO_PIN_8
#define CPUIO3_GPIO_Port GPIOG
#define RS485TX_Pin GPIO_PIN_6
#define RS485TX_GPIO_Port GPIOC
#define CPUIO4_Pin GPIO_PIN_7
#define CPUIO4_GPIO_Port GPIOG
#define CPUIO5_Pin GPIO_PIN_6
#define CPUIO5_GPIO_Port GPIOG
#define CPUIO0_Pin GPIO_PIN_5
#define CPUIO0_GPIO_Port GPIOG
#define CIN1_AD_Pin GPIO_PIN_1
#define CIN1_AD_GPIO_Port GPIOA
#define CIN2_AD_Pin GPIO_PIN_0
#define CIN2_AD_GPIO_Port GPIOA
#define VIN1_AD_Pin GPIO_PIN_4
#define VIN1_AD_GPIO_Port GPIOA
#define MPU_INT1_Pin GPIO_PIN_6
#define MPU_INT1_GPIO_Port GPIOA
#define VIN2_AD_Pin GPIO_PIN_5
#define VIN2_AD_GPIO_Port GPIOA
#define MPU_INT1A7_Pin GPIO_PIN_7
#define MPU_INT1A7_GPIO_Port GPIOA
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
