/**
  ******************************************************************************
  * @FileName:	BSP_SPST.c
  * @Author:		Tim
  * @Version:		V1.1.0
  * @Date:			11-02-2020
  * @Description:   复用端子通过MUX509选择电流AD、电压AD、RS485通讯
  * @Others:
  ******************************************************************************
  * @FunctionsList:	
  *
  *
  ******************************************************************************
  * @Copyright(C), 2020 Smokie Robotics, Inc
  ******************************************************************************
  * @History: V1.1.0, Hardware pin changes, Tim
  *           V1.0.0, first version, hui
  ******************************************************************************
  */


/* Includes ------------------------------------------------------------------*/


/* Private Includes ----------------------------------------------------------*/
#include "BSP_SPST.h"

/* Exported Functions --------------------------------------------------------*/
/**
  * @brief  
  * @param  None
	*
  * @retval None
  */
uint8_t BSP_SPST_Init(void)
{
	printf("Initializing SPST ... ");
	BSP_SPST_Float();

	printf("Done\r\n");
	return 0;
}

void BSP_SPST_485_EN(void) //复用端子用于485通讯
{
	BSP_SPST_OFF;
	BSP_SPST1_A0_OFF;
	BSP_SPST1_A1_OFF;
	BSP_SPST2_A0_OFF;
	BSP_SPST2_A1_OFF;
	BSP_SPST_EN;
}

void BSP_SPST_AVin_EN(void) //复用端子用于电压AD输入
{
	BSP_SPST_OFF;
	BSP_SPST1_A0_ON;
	BSP_SPST1_A1_OFF;
	BSP_SPST2_A0_ON;
	BSP_SPST2_A1_OFF;
	BSP_SPST_EN;
}

void BSP_SPST_ACin_EN(void) //复用端子用于电流AD输入
{
	BSP_SPST_OFF;
	BSP_SPST1_A0_OFF;
	BSP_SPST1_A1_ON;
	BSP_SPST2_A0_OFF;
	BSP_SPST2_A1_ON;
	BSP_SPST_EN;
}

void BSP_SPST_Float(void) //复用端子浮空
{
	BSP_SPST_OFF;
	BSP_SPST1_A0_ON;
	BSP_SPST1_A1_ON;
	BSP_SPST2_A0_ON;
	BSP_SPST2_A1_ON;
	//	BSP_SPST_EN;
}

/********************** (C) COPYRIGHT 2020 Smokie Robotics *****END OF FILE****/