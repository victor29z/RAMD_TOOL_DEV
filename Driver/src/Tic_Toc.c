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



/* Includes ------------------------------------------------------------------*/
#include "Tic_Toc.h"

/* Private Includes ----------------------------------------------------------*/
#include "tim.h"
#include "BSP_Timer.h"
#include "BSP_UART.h"

/* Private Typedefs ----------------------------------------------------------*/

/* Macros --------------------------------------------------------------------*/

/* Private Variables ---------------------------------------------------------*/


/* External Variables --------------------------------------------------------*/


/* Exported Functions --------------------------------------------------------*/

/**
  * @brief  Calculate elapse time of running code. Tictoc start.
  * @param  None.
	* @retval None.
  */
void Tic(void)
{
	tic_toc_ms_cnt = 0;
	
	__HAL_TIM_SetCounter(&htim4,0);
	HAL_TIM_Base_Start(&htim4);	
}


/**
  * @brief  Calculate elapse time of running code. Tictoc stop.
  * @param  None
	* @retval elapse time in us.
  */
uint32_t Toc(void)
{
	uint32_t result;
	
	result = __HAL_TIM_GetCounter(&htim4);
	HAL_TIM_Base_Stop(&htim4);
	
	result += tic_toc_ms_cnt * 1000;
	
	printf("Elapsed time is %d us\r\n", result);
	
	return result;
}


/********************** (C) COPYRIGHT 2020 Smokie Robotics *****END OF FILE****/


