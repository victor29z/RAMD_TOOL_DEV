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
#include "Delay.h"

/* Private Includes ----------------------------------------------------------*/
#include "tim.h"
#include "BSP_UART.h"

/* Private Typedefs ----------------------------------------------------------*/

/* Macros --------------------------------------------------------------------*/

/* Private Variables ---------------------------------------------------------*/

/* External Variables --------------------------------------------------------*/

/* Exported Functions --------------------------------------------------------*/
/**
  * @brief  Us delay timer.
  * @param  cnt, max 65535
	* @retval None.
  */
void Delay_us(uint32_t cnt)
{
	__HAL_TIM_SetCounter(&htim3,0);

	HAL_TIM_Base_Start(&htim3);

	while(__HAL_TIM_GetCounter(&htim3) < cnt);

	HAL_TIM_Base_Stop(&htim3);
}
/********************** (C) COPYRIGHT 2020 Smokie Robotics *****END OF FILE****/


