/**
  ******************************************************************************
  * @FileName:	
  * @Author:		Hui
  * @Version:		V1.0.0
  * @Date:			06-16-2020
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
#include "Robot_Drive.h"

/* Private Includes ----------------------------------------------------------*/

/* Private Typedefs ----------------------------------------------------------*/


/* Macros --------------------------------------------------------------------*/

/* Private Variables ---------------------------------------------------------*/

/* External Variables --------------------------------------------------------*/

/* Exported Functions --------------------------------------------------------*/

/**
  * @brief  Search IMU device; try on reading addr of MPU9250 with SPI.
  * @param  None.
  * @retval 0-success; 1-fail.
  */
uint8_t Search_IMU(void)
{
	for(uint8_t i=0; i<10; i++)
	{
		printf("Searching IMU...");
		if(BSP_IMU_Found())	
		{
			printf("IMU found.\n");
			return 0;
		}		
		IMU_Not_Found;	//LED indication. LED1 and LED2 on.
		printf("IMU not found.\n");
		HAL_Delay(100);
	}
	
	return 1;
};


/**
  * @brief  Power on robot; output 100 dutycyle PWM on TIMI CH1.
  * @param  None.
  * @retval None.
  */
void Robot_Power_On(void)
{

};


/**
  * @brief  Power off robot; output 0 dutycyle PWM on TIMI CH1.
  * @param  None.
  * @retval None.
  */
void Robot_Power_Off(void)
{

};


/**
  * @brief  command event; Power control and update system status.
  * @param  None.
  * @retval None.
  */
uint8_t Cmd_Evt(void)
{
	/*Power on/off*/
//	if(System_State[SYS_ENABLE_ON_POWER])
//		Robot_Power_On();
//	else
//		Robot_Power_Off();
	
	/*check system voltage*/
//	uint16_t sys_volt = BSP_ADC_Read_PWR_Volt();
//	System_State[SYS_VOLTAGE] = sys_volt;
	
	/*updata temperature*/
//	System_State[SYS_TEMP] = BSP_ADC_Read_Temp();
		
	/*check system current*/
//	float sys_cur = BSP_ADC_Read_Cur();
//	uint16_t *pdata = (uint16_t *)&sys_cur;

//	System_State[SYS_CURRENT_L] = *(pdata+1);
//	System_State[SYS_CURRENT_H] = *pdata;
	
	/*check robot voltage*/
//	uint16_t rob_volt = BSP_ADC_Read_Robot_PWR_Volt();
//	System_State[SYS_VOLTAGE] = sys_volt;
	
	/*energy eater control*/
//	if(System_State[SYS_ENABLE_ENGY_EATER])
//		Energy_Eater_Crl(sys_volt, rob_volt, VOLT_LIMIT);
	
	/*updata MPU data*/
//	BSP_MPU9250_Read_All();
//	System_State[MPU_TEMP_DATA] = mpu9250_raw_data.temp;
//	
//	System_State[MPU_ACC_X_DATA] = mpu9250_raw_data.acc.x*4*98/32767;
//	System_State[MPU_ACC_Y_DATA] = mpu9250_raw_data.acc.y*4*98/32767;
//	System_State[MPU_ACC_Z_DATA] = mpu9250_raw_data.acc.z*4*98/32767;
//	
//	System_State[MPU_GYR_X_DATA] = mpu9250_raw_data.gyro.x*500*10/32767;
//	System_State[MPU_GYR_Y_DATA] = mpu9250_raw_data.gyro.y*500*10/32767;
//	System_State[MPU_GYR_Z_DATA] = mpu9250_raw_data.gyro.z*500*10/32767;
//	
//	System_State[MPU_MAG_X_DATA] = mpu9250_raw_data.mag.x*4900/32767;
//	System_State[MPU_MAG_Y_DATA] = mpu9250_raw_data.mag.y*4900/32767;
//	System_State[MPU_MAG_Z_DATA] = mpu9250_raw_data.mag.z*4900/32767;
//	
//	/*check installation pose*/
//	if((int16_t)System_State[MPU_ACC_Z_DATA] > 0)	//acc_z>0 -> upwards, LED2 on.
//	{
//		System_State[MPU_INST_DRCT] = 0;
//		BSP_LED1_ON;
//	}
//	
//	else	//acc_z<0 -> downwards, LED2 off.
//	{
//		System_State[MPU_INST_DRCT] = 1;
//		BSP_LED1_OFF;
//	}
//	
//	/*Write system_state into Flash*/
//	if(System_State[SYS_SAVE_TO_FLASH])
//	{
//		System_State[SYS_SAVE_TO_FLASH] = 0;
//		Flash_Mem_Write(System_State, System_State_Size*2, FLASH_START_ADDR_SYSTEM_STATE);
//	}
	
	return 0;
};


/**
  * @brief  Energy eater control. 
  * @param  sys_volt-system voltage; rob_volt-robot voltage; volt_limit-voltage limitation.
  * @retval None.
  */
void Energy_Eater_Crl(uint16_t sys_volt, uint16_t rob_volt, uint16_t volt_limit)
{

};
