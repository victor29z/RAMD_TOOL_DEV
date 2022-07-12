/**
  ******************************************************************************
  * @FileName:	Tool_CONN_AI.c
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

/* Private Includes ----------------------------------------------------------*/
#include "Tool_CONN_AI.h"

/* Exported Functions --------------------------------------------------------*/
/**
  * @brief  
  * @param  None
	*
  * @retval None
  */

uint8_t AI_Port_Config(uint8_t Read_Type)
{
	if(Read_Type == Read_Current)
	{
		BSP_SPST_ACin_EN();	
	}

	else if(Read_Type == Read_Voltage)
	{
		BSP_SPST_AVin_EN();
	}
	
	return 0;
}


int32_t AI_Port_Read(uint8_t port, uint8_t Read_Type)
{
	//���ж�һ��PWR���Ƿ񹩵磿
	int32_t AI_value;
	
	if(port == Port_AI0)
	{
		if(Read_Type == Read_Current)
			AI_value = Get_ACin1();
		else if(Read_Type == Read_Voltage)
			AI_value = Get_AVin1();
	}
	else if(port == Port_AI1)
	{
		if(Read_Type == Read_Current)
			AI_value = Get_ACin2();
		else if(Read_Type == Read_Voltage)
			AI_value = Get_AVin2();	
	}
	
	return AI_value;
}

/********************** (C) COPYRIGHT 2020 Smokie Robotics *****END OF FILE****/
