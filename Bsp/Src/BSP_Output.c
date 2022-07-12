/**
  ******************************************************************************
  * @FileName:	BSP_Output.c
  * @Author:		Tim
  * @Version:		V1.1.0
  * @Date:			11-02-2020		
  * @Description:   
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
  *
  ******************************************************************************
  */


/* Includes ------------------------------------------------------------------*/


/* Private Includes ----------------------------------------------------------*/
#include "BSP_Output.h"

/* Exported Functions --------------------------------------------------------*/
/**
  * @brief  
  * @param  None
	*
  * @retval None
  */

uint8_t BSP_Output_Init(void)
{
	printf("Initializing Output ... ");
	BSP_Output_DO0(Port_OFF);
	BSP_Output_DO1(Port_OFF);
	BSP_Output_PWR(Port_OFF);
	BSP_12_24_Power_EN;	

	printf("Done\r\n");
	return 0;
}

void BSP_Output_PWR(uint8_t status) 
{
	switch(status)
	{
		case Port_ON:
			BSP_CPUIO0_ON;
			break;
		case Port_OFF:
			BSP_CPUIO0_OFF;
			break;
		default:
			BSP_CPUIO0_OFF;
			break;
	}
}	
	
void BSP_Output_DO0(uint8_t status) 
{
	switch(status)
	{
		case Port_GND:
			BSP_CPUIO2_OFF;
			BSP_CPUIO3_ON;
			break;
		case Port_ON:
			BSP_CPUIO2_ON;
			BSP_CPUIO3_OFF;
			break;
		case Port_OFF:
			BSP_CPUIO2_OFF;
			BSP_CPUIO3_OFF;
			break;
		default:
			break;
	}
}	
	
void BSP_Output_DO1(uint8_t status) 
{
	switch(status)
	{
		case Port_GND:
			BSP_CPUIO4_OFF;
			BSP_CPUIO5_ON;
			break;
		case Port_ON:
			BSP_CPUIO4_ON;
			BSP_CPUIO5_OFF;
			break;
		case Port_OFF:
			BSP_CPUIO4_OFF;
			BSP_CPUIO5_OFF;
			break;
		default:
			break;
	}
}
	

void BSP_Output_PWR_Test(void){
	printf("Turning Output Power ON...\r\n\n");
	HAL_Delay(2000);
	BSP_Output_PWR(Port_ON);
	BSP_12_24_Power_EN;
	HAL_Delay(3000);

	printf("Configuring Power to 12V...\r\n\n");
	HAL_Delay(2000);
	BSP_12_Power_ON;
	HAL_Delay(3000);

	printf("Configuring Power to 24V...\r\n\n");
	HAL_Delay(2000);
	BSP_24_Power_ON;
	HAL_Delay(3000);

	printf("Disabling Power Output...\r\n\n");
	BSP_Output_PWR(Port_OFF);
	BSP_12_24_Power_DEN;
}

void BSP_Output_DO_Test(void){
	printf("Turning Output Power ON...\r\n\n");
	HAL_Delay(2000);
	BSP_Output_PWR(Port_ON);
	BSP_12_24_Power_EN;
	HAL_Delay(3000);

	printf("Configuring DO0 to GND...\r\n\n");
	BSP_Output_DO0(Port_GND);
	HAL_Delay(3000);

	printf("Configuring DO0 to 12V...\r\n\n");
	BSP_12_Power_ON;
	BSP_Output_DO0(Port_ON);
	HAL_Delay(3000);

	printf("Configuring DO0 to 24V...\r\n\n");
	BSP_24_Power_ON;
	BSP_Output_DO0(Port_ON);
	HAL_Delay(6000);


	printf("Configuring DO1 to GND...\r\n\n");
	BSP_Output_DO1(Port_GND);
	HAL_Delay(3000);

	printf("Configuring DO1 to 12V...\r\n\n");
	BSP_12_Power_ON;
	BSP_Output_DO1(Port_ON);
	HAL_Delay(3000);

	printf("Configuring DO1 to 24V...\r\n\n");
	BSP_24_Power_ON;
	BSP_Output_DO1(Port_ON);
	HAL_Delay(3000);

	printf("Disabling Power Output...\r\n\n");
	BSP_Output_PWR(Port_OFF);
	BSP_12_24_Power_DEN;
}
/********************** (C) COPYRIGHT 2020 Smokie Robotics *****END OF FILE****/
