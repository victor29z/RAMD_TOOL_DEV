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
#include "State_Observer.h"

/* Private Includes ----------------------------------------------------------*/
#include "BSP_ADC.h"

/* Private Typedefs ----------------------------------------------------------*/

/* Macros --------------------------------------------------------------------*/

/* Private Variables ---------------------------------------------------------*/

/* External Variables --------------------------------------------------------*/

/* Exported Functions --------------------------------------------------------*/

/**
  * @brief  Get voltage of Power Input
  * @param  None
* @retval voltage of Power Input (unit: 0.1v)
  */
int32_t Get_ACin1(void)
{
	uint32_t ad = 0, Cur_32;
	float Cur_Volt, Cur;
	
	for(uint8_t i=0; i<100; i++)
	{
		if(i%5 == 1)
			ad += adc_value[i];
	}
	ad /= 20;

	Cur_Volt = ad * 3.3f /4096;
	//printf("Cur_Volt1 = %f\r\n", Cur_Volt);
	Cur = Cur_Volt*1000/150;		//mA
	
	
	memcpy(&Cur_32, &Cur, 4);
	return Cur_32;
}

int32_t Get_ACin2(void)
{
	uint32_t ad = 0, Cur_32;
	float Cur_Volt, Cur;
	
	for(uint8_t i=0; i<100; i++)
	{
		if(i%5 == 0)
			ad += adc_value[i];
	}
	ad /= 20;

	Cur_Volt = ad * 3.3f /4096;
	//printf("Cur_Volt2 = %f\r\n", Cur_Volt);
	Cur = Cur_Volt*1000/150;
	
	memcpy(&Cur_32, &Cur, 4);
	return Cur_32;	
}

int32_t Get_AVin1(void)
{
	uint32_t ad = 0, Vol_32;
	float Vin1, AVin1;
	
	for(uint8_t i=0; i<100; i++)
	{
		if(i%5 == 2)
			ad += adc_value[i];
	}
	ad /= 20;

	Vin1 = ad * 3.3f /4096;
	AVin1 = Vin1/0.3;
//	printf("Get_AVin1 = %f\r\n", AVin1);
	memcpy(&Vol_32, &AVin1, 4);
	
	return Vol_32;	
}


int32_t Get_AVin2(void)
{
	uint32_t ad = 0, Vol_32;
	float Vin2, AVin2;
	
	for(uint8_t i=0; i<100; i++)
	{
		if(i%5 == 3)
			ad += adc_value[i];
	}
	ad /= 20;

	Vin2 = ad * 3.3f /4096;
	AVin2 = Vin2/0.3;
//	printf("Get_AVin2 = %f\r\n", AVin2);
	memcpy(&Vol_32, &AVin2, 4);
	return Vol_32;	
}

int32_t Get_Tool_Temp(void)
{
	uint32_t ad = 0;
	float Temp_16;
	float Temp;
	
	for(uint8_t i=0; i<100; i++)
	{
		if(i%5 == 4)
			ad += adc_value[i];
	}
	ad/=20.0;

	Temp = (ad * 3300.0 /4096.0 -760.0)/2.5+25;
	Temp_16 = 10* Temp;

	//printf("Tool temperature: %f\r\n", Temp_16);
	return Temp_16;	
}

uint32_t Get_Power_Supply_Volt(void)
{
	return BSP_PWR_I2C_Read_Voltage();	
}

int32_t Get_Cur(void)
{
	return BSP_PWR_I2C_Read_Current();	
}
/**
  * @brief  Debug ADC read. Display all 4 ADC channel voltage through UART.
  * @param  None
	* @retval None.
  */
void Robot_State_Printf(void)
{
	printf("\r\n******** ADC DMA Example ********\r\n\r\n");
	printf(" ACin1 = 0x%x4mA \r\n", Get_ACin1());
	printf(" ACin2 = 0x%x4mA \r\n", Get_ACin2());
	printf(" AVin1 = 0x%x4V \r\n", Get_AVin1());
	printf(" AVin2 = 0x%x4V \r\n", Get_AVin2());
}

/********************** (C) COPYRIGHT 2020 Smokie Robotics *****END OF FILE****/


