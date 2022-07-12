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
#include "Clock.h"

/* Private Includes ----------------------------------------------------------*/
#include "Test.h"

/* Private Typedefs ----------------------------------------------------------*/

/* Macros --------------------------------------------------------------------*/

/* Private Variables ---------------------------------------------------------*/

/* External Variables --------------------------------------------------------*/

/* Exported Functions --------------------------------------------------------*/
/**
  * @brief  Test function
  * @param  None
  * @retval None
  */
uint8_t Smokie_Test(void)
{
	
	/*Debug Uart Printf Test*/
//	printf("Smokie Base : STM32F405RGT6_v1.0.0\r\n");
//	printf("Uptime      : %d h %d m %d s %d ms\r", runtime_clock.h, runtime_clock.m, runtime_clock.s, runtime_clock.ms);
//	printf("Date        : 07-31-2020\r\n");
//	printf("COPYRIGHT 2020 Smokie Robotics, Inc\r\n\r\n");
//	HAL_Delay(100);
//	
//	printf("Ready to go...\r\n\r\n");
	
	/*Debug Temp Test*/
//	int16_t temp = Get_Tool_Temp();
//	printf("temp_16*10 = %d\r\n", temp);
	
	/*Debug FT_RS485 Test*/
//	uint16_t temp = 2;
//	FT_RS485_Send_msg(&temp, 2);
//	HAL_Delay(1000);
	
//	float AV;
//	int32_t AV_32;
//	AV_32 = Get_AVin1();
//	memcpy(&AV, &AV_32, 4);
//	printf("AV1 = %f\r\n", AV);
//	HAL_Delay(100);
	
//	AV_32 = Get_AVin2();
//	memcpy(&AV, &AV_32, 4);
//	printf("AV2 = %f\r\n", AV);
//	HAL_Delay(100);

	float AC;
	int32_t AC_32;
	AC_32 = Get_ACin1();
	memcpy(&AC, &AC_32, 4);
	printf("AC1 = %f\r\n", AC);
	HAL_Delay(100);
	
	return 0;
}

/********************** (C) COPYRIGHT 2020 Smokie Robotics *****END OF FILE****/

