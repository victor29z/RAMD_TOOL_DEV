/**
  ******************************************************************************
  * @FileName:	BSP_Delay.c
  * @Author:		Victor
  * @Version:		V1.0.0
  * @Date:			06-08-2020
  * @Description:   
  * @Others:
  ******************************************************************************
  * @FunctionsList:	
  *
  *
  ******************************************************************************
  * @Copyright(C), 2020 Smokie Robotics, Inc
  ******************************************************************************
  * @History:
  *
  ******************************************************************************
  */


/* Includes ------------------------------------------------------------------*/


/* Private Includes ----------------------------------------------------------*/
#include "tim.h"
#include "BSP_Timer.h"
#include "BSP_UART.h"
#include "ecatappl.h"
#include "samplehw.h"
/* Variables -----------------------------------------------------------------*/
uint32_t tic_toc_ms_cnt = 0;

__IO uint16_t clock_ms_cnt = 0; 

__IO uint16_t s_cnt = 0; 
__IO uint16_t m_cnt = 0; 
__IO uint16_t h_cnt = 0; 

__IO Clock *pclock = NULL;
/* Private Functions ---------------------------------------------------------*/

/* Exported Functions --------------------------------------------------------*/

/**
  * @brief  Timer initialization.
  * @param  None
	* @retval 0:correct.
  */
uint8_t BSP_Timer_Init(void)
{
  printf("Initializing Delay ... ");
	HAL_TIM_Base_Start_IT(&htim4);
	HAL_TIM_Base_Stop(&htim4);
	HAL_TIM_Base_Start_IT(&htim6);
	//HAL_TIM_Base_Start_IT(&htim9);
	printf("Done\r\n");
	
	return 0;
}

/**
  * @brief  Us delay timer.
  * @param  us.
	* @retval None.
  */
void BSP_Timer_Delay_Us(uint32_t us)
{
	__HAL_TIM_SetCounter(&htim3,0);

	HAL_TIM_Base_Start(&htim3);

	while(__HAL_TIM_GetCounter(&htim3) < us);

	HAL_TIM_Base_Stop(&htim3);
}

uint8_t BSP_Clock_Register(Clock *temp)
{
	pclock = temp;
}

static void BSP_H_M_S(void)
{
	if (pclock != NULL)
	{
		pclock->ms++;
		
		if(pclock->ms >= 1000)
		{
			pclock->s++;
			pclock->ms =0;
		}
		if(pclock->s >= 60)
		{
			pclock->m++;
			pclock->s = 0;
		}
		if(pclock->m >= 60)
		{
			pclock->h++;
			pclock->m = 0;
		}
	}

}

/**
  * @brief  IT of Tictoc to calculate elapse time over 1ms.
  * @param  timer handle
	* @retval None.
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
		if (htim == &htim4)
	{
		tic_toc_ms_cnt++;
		//printf("Timer4 1ms int works!\r\r");	
	}	
	
	if (htim == &htim6)
	{
		clock_ms_cnt++;
		BSP_H_M_S();	
		//printf("Timer6 1ms int works!\r\r");	
	}
	if (htim == &htim9)
	{
		HW_TIMETASK_IRQHandler();
		//ECAT_CheckTimer();
	
	}

}

/********************** (C) COPYRIGHT 2020 Smokie Robotics *****END OF FILE****/

