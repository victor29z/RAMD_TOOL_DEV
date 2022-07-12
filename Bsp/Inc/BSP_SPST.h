/**
  ******************************************************************************
  * @FileName:	BSP_SPST.h
  * @Author:		Tim
  * @Version:		V1.1.0
  * @Date:			11-02-2020
  * @Description:   
  * @Others:
  ******************************************************************************
  * @Copyright(C), 2020, Smokie Robotics, Inc
  ******************************************************************************
  * @History: V1.1.0, Hardware pin changes, Tim
  *           V1.0.0, first version, hui
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BSP_SPST_H
#define __BSP_SPST_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "BSP_UART.h"

/* Private Includes ----------------------------------------------------------*/


/* Private Typedefs ----------------------------------------------------------*/

/* Macros --------------------------------------------------------------------*/
//#define BSP_SPST_EN   		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET) //�����·ѡ�����
//#define BSP_SPST_OFF   		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET) //��ֹ��·ѡ�����
#define BSP_SPST_EN   		HAL_GPIO_WritePin(MUX_EN_GPIO_Port, MUX_EN_Pin, GPIO_PIN_SET) //�����·ѡ�����
#define BSP_SPST_OFF   		HAL_GPIO_WritePin(MUX_EN_GPIO_Port, MUX_EN_Pin, GPIO_PIN_RESET) //��ֹ��·ѡ�����

//#define BSP_SPST1_A0_ON   HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_SET) //MUX1_A0=1
//#define BSP_SPST1_A0_OFF  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_RESET) //MUX1_A0=0
//
//#define BSP_SPST1_A1_ON   HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_SET) //MUX1_A1=1
//#define BSP_SPST1_A1_OFF  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_RESET) //MUX1_A1=0
//
//#define BSP_SPST2_A0_ON   HAL_GPIO_WritePin(GPIOC, GPIO_PIN_14, GPIO_PIN_SET) //MUX2_A0=1
//#define BSP_SPST2_A0_OFF  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_14, GPIO_PIN_RESET) //MUX2_A0=0
//
//#define BSP_SPST2_A1_ON   HAL_GPIO_WritePin(GPIOC, GPIO_PIN_15, GPIO_PIN_SET) //MUX2_A1=1
//#define BSP_SPST2_A1_OFF  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_15, GPIO_PIN_RESET) //MUX2_A1=0

#define BSP_SPST1_A0_ON   HAL_GPIO_WritePin(MUX1_A0_GPIO_Port, MUX1_A0_Pin, GPIO_PIN_SET) //MUX1_A0=1
#define BSP_SPST1_A0_OFF  HAL_GPIO_WritePin(MUX1_A0_GPIO_Port, MUX1_A0_Pin, GPIO_PIN_RESET) //MUX1_A0=0

#define BSP_SPST1_A1_ON   HAL_GPIO_WritePin(MUX1_A1_GPIO_Port, MUX1_A1_Pin, GPIO_PIN_SET) //MUX1_A1=1
#define BSP_SPST1_A1_OFF  HAL_GPIO_WritePin(MUX1_A1_GPIO_Port, MUX1_A1_Pin, GPIO_PIN_RESET) //MUX1_A1=0

#define BSP_SPST2_A0_ON   HAL_GPIO_WritePin(MUX2_A0_GPIO_Port, MUX2_A0_Pin, GPIO_PIN_SET) //MUX2_A0=1
#define BSP_SPST2_A0_OFF  HAL_GPIO_WritePin(MUX2_A0_GPIO_Port, MUX2_A0_Pin, GPIO_PIN_RESET) //MUX2_A0=0

#define BSP_SPST2_A1_ON   HAL_GPIO_WritePin(MUX2_A1_GPIO_Port, MUX2_A1_Pin, GPIO_PIN_SET) //MUX2_A1=1
#define BSP_SPST2_A1_OFF  HAL_GPIO_WritePin(MUX2_A1_GPIO_Port, MUX2_A1_Pin, GPIO_PIN_RESET) //MUX2_A1=0

/* Private Variables ---------------------------------------------------------*/

/* Exported Functions --------------------------------------------------------*/
uint8_t BSP_SPST_Init(void);
void BSP_SPST_485_EN(void); //���ö�������485ͨѶ
void BSP_SPST_AVin_EN(void); //���ö������ڵ�ѹAD����
void BSP_SPST_ACin_EN(void); //���ö������ڵ���AD����
void BSP_SPST_Float(void); //���ö��Ӹ���

#endif
/********************** (C) COPYRIGHT 2020 Smokie Robotics *****END OF FILE****/
