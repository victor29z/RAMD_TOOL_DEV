/**
  ******************************************************************************
  * @FileName:		BSP_ADC.c
  * @Author:		Hui Liu
  * @Version:		V1.0.0
  * @Date:			06-12-2020
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

/* Private Typedefs ----------------------------------------------------------*/

/* Macros --------------------------------------------------------------------*/

/* Private Includes ----------------------------------------------------------*/
#include "BSP_ADC.h"

/* External Variables --------------------------------------------------------*/
//uint16_t adc_value[100]={0};
uint32_t adc_value[100]={0};

/* Exported Functions --------------------------------------------------------*/
/**
  * @brief  Initialize ADC DMA port.
  * @param  None
	* @retval 1:fail. 0:correct.
  */
uint8_t BSP_ADC_Init()
{
	printf("Initializing ADC ... ");
//	if(HAL_ADC_Start_DMA(&BSP_ADC, (uint16_t*)&adc_value, 100))
	if(HAL_ADC_Start_DMA(&BSP_ADC, (uint32_t*)&adc_value, 100))
	{
		printf("Fail to initialize ADC.\r\n");
		return 1;
	}
	
	printf("Done\r\n");
	return 0;
};

/********************** (C) COPYRIGHT 2020 Smokie Robotics *****END OF FILE****/
