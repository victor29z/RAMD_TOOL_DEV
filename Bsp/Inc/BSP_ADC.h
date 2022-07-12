/**
  ******************************************************************************
  * @FileName:		BSP_ADC.h
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
#ifndef __BSP_ADC_H
#define __BSP_ADC_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "BSP_UART.h"
/* Private Includes ----------------------------------------------------------*/
#include "adc.h"
#include <stdio.h>
#include <string.h>
#include <math.h>

/* Private Typedefs ----------------------------------------------------------*/

/* Macros --------------------------------------------------------------------*/
#define BSP_ADC	hadc1

/* Private Variables ---------------------------------------------------------*/
//extern uint16_t adc_value[100];
extern uint32_t adc_value[100];


/* External Variables --------------------------------------------------------*/

/* Exported Functions --------------------------------------------------------*/
uint8_t BSP_ADC_Init(void);
//float BSP_ADC_Read_Cin1(void);
//float BSP_ADC_Read_Cin2(void);
//float BSP_ADC_Read_AVin1(void);
//float BSP_ADC_Read_AVin2(void);

//void BSP_Display_All_ADC(void);

#endif 
/********************** (C) COPYRIGHT 2020 Smokie Robotics *****END OF FILE****/
