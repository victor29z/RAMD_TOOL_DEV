/**
  ******************************************************************************
  * @FileName:	BSP_DO_PWR_CTRL.c
  * @Author:		Hui
  * @Version:		V1.0.0
  * @Date:			08062020
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
#include "BSP_DO_PWR_CTRL.h"
#include "BSP_UART.h"


/* Exported Functions --------------------------------------------------------*/
/**
  * @brief  
  * @param  None
	*
  * @retval None
  */

uint8_t BSP_DO_PWR_CTRL_Init(void)
{
	printf("Initializing DO power control ... ");
	
	//BSP_DO_PWR_CTRL_EN;
	//HAL_Delay(2000);
	
	//printf("Done\r\n");
	return 0;
}

void BSP_DO_PWR_CTRL_Test(void){
	printf("Testing power output 12V...\r\n");
	BSP_DO_PWR_CTRL_12V;
	HAL_Delay(10000);
	printf("Testing power output 24V...\r\n");
	BSP_DO_PWR_CTRL_24V;
	HAL_Delay(10000);

}

/********************** (C) COPYRIGHT 2020 Smokie Robotics *****END OF FILE****/
