/**
  ******************************************************************************
  * @FileName:	BSP_Timer.h
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
#ifndef __BSP_TIMER_H
#define __BSP_TIMER_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private Includes ----------------------------------------------------------*/

/* Private Typedefs ----------------------------------------------------------*/
typedef struct
{
	uint16_t ms;
	uint16_t s; 
	uint16_t m; 
	uint16_t h;
} Clock;
/* Macros --------------------------------------------------------------------*/
#define Delay_ms(cnt) 		HAL_Delay(cnt)
/* Private Variables ---------------------------------------------------------*/
extern uint32_t tic_toc_ms_cnt;
extern __IO uint16_t clock_ms_cnt; 

extern __IO uint16_t s_cnt; 
extern __IO uint16_t m_cnt; 
extern __IO uint16_t h_cnt; 
/* Exported Functions --------------------------------------------------------*/
uint8_t BSP_Timer_Init(void);
void BSP_Timer_Delay_Us(uint32_t us);
//static void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
uint8_t BSP_Clock_Register(Clock *temp);


#endif 
/********************** (C) COPYRIGHT 2020 Smokie Robotics *****END OF FILE****/
