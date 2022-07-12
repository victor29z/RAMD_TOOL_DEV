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


/* Includes ------------------------------------------------------------------*/
#include "BSP_Global.h"

/* Private Includes ----------------------------------------------------------*/

/* Private Typedefs ----------------------------------------------------------*/

/* Macros --------------------------------------------------------------------*/

/* Private Variables ---------------------------------------------------------*/

/* External Variables --------------------------------------------------------*/

/* Exported Functions --------------------------------------------------------*/
uint8_t BSP_Global_Init(void)
{
	printf("BSP Init ... Start\r\n");

	BSP_Chip_ID_Init();
	BSP_LED_Init();
	BSP_UART_Init();
	BSP_24AA16_Init();
	BSP_INA237_Init();
	BSP_ADC_Init();
	BSP_CAN_Init();
//	BSP_MPU9250_Init();
  BSP_ICM20600_Init();
//	BSP_STM32_Flash_Init();
//	BSP_Encrypt_Init();
  BSP_Timer_Init();
	BSP_SPST_Init();
	BSP_DO_PWR_CTRL_Init();
	BSP_Output_Init();


	/* Init AX58100 */
  BSP_AX58100_Init();

	
	
	
	printf("BSP Init ... Done\r\n\r\n");
	return 0;
}

/********************** (C) COPYRIGHT 2020 Smokie Robotics *****END OF FILE****/


