/**
  ******************************************************************************
  * @FileName:	BSP_INA237.c
  * @Author:		Tim
  * @Version:		V1.0.0
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
  * @History: 
  *
  ******************************************************************************
  */



/* Private Includes ----------------------------------------------------------*/
#include "BSP_INA237.h"


/* Private Includes ----------------------------------------------------------*/

/* Private Typedefs ----------------------------------------------------------*/

/* Macros --------------------------------------------------------------------*/

/* Private Variables ---------------------------------------------------------*/

/* External Variables --------------------------------------------------------*/

/* Exported Functions --------------------------------------------------------*/

uint8_t BSP_INA237_Init(void)
{
	uint16_t M_ID[2];
	printf("Initializing INA237 ... ");
	
	if(BSP_PWR_I2C_Block_Read(MANUFACTURER_ID, M_ID, 2)==0)
	{
		if(M_ID[0]==MANUFACTURER_ID_VALUE)
		{
			printf("Done\r\n");
		}
		else
			printf("Fail\r\n");	
	}
	
	return 0;
}

/**
  * @brief  I2C read bus voltage value
  * @param
	* @retval Bus Voltage Value.
  */
uint16_t BSP_PWR_I2C_Read_Voltage(void)
{
	uint16_t Bus_Voltage[2];
	
	if(BSP_PWR_I2C_Block_Read(VBUS, Bus_Voltage, 2)==0)
		Bus_Voltage[1]=Bus_Voltage[0]*3.125;
//		printf("Bus_Voltage=%d\n", Bus_Voltage[1]);

	return Bus_Voltage[1];
}

/**
  * @brief  I2C read bus current value
  * @param  
	* @retval Current Current Value
  */
uint32_t BSP_PWR_I2C_Read_Current(void)
{
	uint16_t Bus_Current_temp[2];
	uint32_t Bus_Current;
	
	if(BSP_PWR_I2C_Block_Read(CURRENT, Bus_Current_temp, 2)==0)
		Bus_Current=Bus_Current_temp[0]*0x1000;
//		printf("Bus_current=%x\n", Bus_Current_temp[0]*0x1000);
//	  printf("Bus_current=%d\n", Bus_Current);

	return Bus_Current;
}

/**
  * @brief  I2C read uint16_t data from INA237
	* @param  Offset: MemAddress Internal memory address
						*ReadBuffer: uint16_t pointer of input data.
						NumByteToWrite: Size Amount of data to be sent
	* @retval Err_State: 1:error. 0:correct.
  */
uint16_t BSP_PWR_I2C_Block_Read(uint16_t Offset, uint16_t *ReadBuffer, uint16_t NumByteToWrite)
{
	uint8_t ReadBuffer_temp[NumByteToWrite];
	uint16_t Value[NumByteToWrite/2];
	
	if (HAL_I2C_Mem_Read(&I2C_handle, BASE_ADDR_INA237_Read, Offset, I2C_MEMADD_SIZE_8BIT, ReadBuffer_temp, NumByteToWrite, 0xffff) != HAL_OK) //读取数据多的话，timeout要给够
		return RDATA_HAL_ERR_INA237;
//	printf("ReadBuffer_temp[0]=%x\n", ReadBuffer_temp[0]);
//	printf("ReadBuffer_temp[1]=%x\n", ReadBuffer_temp[1]);
	Value[0] = ((uint16_t)ReadBuffer_temp[0] << 8) | ReadBuffer_temp[1];
	
	memcpy(ReadBuffer,Value,NumByteToWrite);
//	printf("ReadBuffer=%x\n", ReadBuffer[0]);
	return 0;
}

/**
  * @brief  I2C write uint16_t data to INA237
	* @param  Offset: MemAddress Internal memory address
						*WriteBuffer: uint16_t pointer of input data.
						NumByteToWrite: Size Amount of data to be sent
	* @retval Err_State: 1:error. 0:correct.
  */
uint16_t BSP_PWR_I2C_Block_Write(uint16_t Offset, uint16_t *WriteBuffer, uint16_t NumByteToWrite)
{
	uint8_t *pdata = (uint8_t *)WriteBuffer;
	memcpy(pdata,pdata,sizeof(*pdata));
	
	if (HAL_I2C_Mem_Write(&I2C_handle, BASE_ADDR_INA237_Read, Offset,I2C_MEMADD_SIZE_8BIT, pdata, NumByteToWrite, 0xffff)!= HAL_OK) //读取数据多的话，timeout要给够
	return RDATA_HAL_ERR_INA237;
	HAL_Delay(5);

	return 0;
}

/**
  * @brief  Testing I2C write and Read uint16_t data.
  * @param  Addr_Write：Write address of EEPROM.
						Addr_Read：Read address of EEPROM.
	* @retval None.
  */
void BSP_PWR_I2C_test(void)
{
	uint16_t i;
	uint16_t WriteBuffer[1] = {0x0010};
	uint16_t ReadBuffer[1] = {0};
	
	BSP_INA237_Init();
	if(BSP_PWR_I2C_Block_Write(CURRLSBCALC_3, WriteBuffer, 2)==0)
	
	while(1)
	{
		BSP_PWR_I2C_Read_Voltage();
		BSP_PWR_I2C_Read_Current();
//		if(BSP_PWR_I2C_Block_Read(CURRLSBCALC_3, ReadBuffer, 2)==0)
//			printf("CURRLSBCALC_3 Value:%x\r\n",ReadBuffer[0]);
//	  if(BSP_PWR_I2C_Block_Read(CURRENT, ReadBuffer, 2)==0)
//	    printf("Bus_current=%x\n", ReadBuffer[0]);
//	    printf("Bus_current=%d\n", ReadBuffer[0]*0x1000);
//		if(BSP_PWR_I2C_Block_Read(MANUFACTURER_ID, ReadBuffer, 2)==0)
//			printf("MANUFACTURER_ID Value:%x\r\n",ReadBuffer[0]);
//		BSP_PWR_I2C_Read_Voltage();
		HAL_Delay(1000);
	}


}
/********************** (C) COPYRIGHT 2020 Smokie Robotics *****END OF FILE****/
