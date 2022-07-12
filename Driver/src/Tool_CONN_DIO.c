/**
  ******************************************************************************
  * @FileName:	Tool_CONN_DIO.c
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
#include "Tool_CONN_DIO.h"

/* Exported Functions --------------------------------------------------------*/
/**
  * @brief  
  * @param  None
	*
  * @retval None
  */

uint8_t DIO_Power_On(void)
{
	BSP_12_24_Power_EN;
	return 0;
}

uint8_t DIO_Power_Off(void)
{
	BSP_12_24_Power_DEN;
	return 0;
}

void DO_PWR_Config(uint8_t status)
{
	switch(status)
	{
		case PWR_0:
			BSP_Output_PWR(Port_OFF);
			BSP_Output_DO0(Port_OFF);
			BSP_Output_DO1(Port_OFF);
			break;
		case PWR_12:
			BSP_12_Power_ON;
			BSP_Output_PWR(Port_ON);
			break;
		case PWR_24:
			BSP_24_Power_ON;
			BSP_Output_PWR(Port_ON);
			break;
//		case PWR_GND:
//			BSP_Output_DO0(Port_OFF);
//			BSP_Output_DO1(Port_OFF);
//			BSP_Output_PWR(Port_GND);
//			break;
		default: break;			
	}
}

void DO0_Config(uint8_t status, uint8_t port_type)
{
	switch(port_type)
	{
		case DO_Port_Type_NPN:
			if(status == DO_Port_Active)
				BSP_Output_DO0(Port_GND);
			else
				BSP_Output_DO0(Port_OFF);
			break;
		
		case DO_Port_Type_PNP:
			if(status == DO_Port_Active)
				BSP_Output_DO0(Port_ON);
			else
				BSP_Output_DO0(Port_OFF);
			break;
		
		case DO_Port_Type_PP:
			if(status == DO_Port_Active)
				BSP_Output_DO0(Port_ON);
			else
				BSP_Output_DO0(Port_GND);
			break;
		
		case DO_Port_Type_DPP:
			BSP_Output_DO0(Port_ON);
			break;
		
		default: break;
	}
}

void DO1_Config(uint8_t status, uint8_t port_type)
{
	switch(port_type)
	{
		case DO_Port_Type_NPN:
			if(status == DO_Port_Active)
				BSP_Output_DO1(Port_GND);
			else
				BSP_Output_DO1(Port_OFF);
			break;
		
		case DO_Port_Type_PNP:
			if(status == DO_Port_Active)
				BSP_Output_DO1(Port_ON);
			else
				BSP_Output_DO1(Port_OFF);
			break;
		
		case DO_Port_Type_PP:
			if(status == DO_Port_Active)
				BSP_Output_DO1(Port_ON);
			else
				BSP_Output_DO1(Port_GND);
			break;
			
		case DO_Port_Type_DPP:
			BSP_Output_DO1(Port_GND);
			break;
		
		default: break;
	}
}

uint8_t Read_DI_Port(uint8_t port)
{
	//���ж�һ��PWR���Ƿ񹩵磿
	uint8_t status;
	
	if(port == Port_TI0)
		status = !HAL_GPIO_ReadPin(TOOL_IN0_GPIO_Port, TOOL_IN0_Pin);//�߼�ȡ����Ӳ�����
	else if(port == Port_TI1)
		status = !HAL_GPIO_ReadPin(TOOL_IN1_GPIO_Port, TOOL_IN1_Pin);	//�߼�ȡ����Ӳ�����
	
	return status;
}

/********************** (C) COPYRIGHT 2020 Smokie Robotics *****END OF FILE****/
