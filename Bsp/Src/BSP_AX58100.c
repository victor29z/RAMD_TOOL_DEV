/**
  ******************************************************************************
  * @FileName:		BSP_AX58100.c
  * @Author:			Ning (Frank) Li
  * @Version:			V1.0.0
  * @Date:				10-28-2021
  * @Description:   
  * @Others:			None
  ******************************************************************************
  * @Copyright(C), 2021, Azure Medical Innovation Corp.
  ******************************************************************************
  * @History:
  * @Contact:			tech@azrmed.com
  ******************************************************************************
  */


/* Includes ------------------------------------------------------------------*/
#include "BSP_UART.h"

/* Private Includes ----------------------------------------------------------*/
#include "BSP_AX58100.h"
#include "samplehw.h"

/**
  * @brief  initialize ax58100
  * @param  None
  * @retval Error number
  */
uint8_t BSP_AX58100_Init(void)
{
	printf("Initializing AX58100 ... ");
	
	BSP_AX58100_Reset();
  if (HW_Init())
	{
		ESC_DEBUG("Initializa ESC hardware timeout!\r\n");
		HW_Release();
	}
	else
	{
#if (ETHERCAT_SLAVE_STACK_ENABLE)
		MainInit();
		ESC_DEBUG("Start EtherCAT slave stack OK!\r\n");
#else
		ESC_DEBUG("EtherCAT slave stack has disabled!\r\n");
#endif
	}
	
	printf("Done\r\n");
	return 0;
}

/**
  * @brief  generate reset pulse to reset ax58100
  * @param  None
  * @retval None
  */

void BSP_AX58100_Reset(void)
{
	AX_RST_RESET;
	HAL_Delay(1);
	AX_RST_SET;
}






/******* (C) COPYRIGHT 2021 Azure Medical Innovation Corp. *****END OF FILE****/

