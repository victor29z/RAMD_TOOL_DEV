/**
  ******************************************************************************
  * @FileName:		EEPROM_RW.c
  * @Author:		Hui
  * @Version:		V1.0.0
  * @Date:			06-23-2020
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
#include "EEPROM_RW.h"

/* Private Includes ----------------------------------------------------------*/

/* Private Typedefs ----------------------------------------------------------*/

/* Macros --------------------------------------------------------------------*/

/* Private Variables ---------------------------------------------------------*/

/* External Variables --------------------------------------------------------*/
DH_Para Robot_DH_Para ={
	{1,0,1,0,1,0},	//alpha
	{2,0,2,0,2,0},	//a
	{3,0,3,0,3,0},	//d
};


uint16_t EEPROM_MEM[EEPROM_MEM_SIZE]={
0,																//0x00						Remain.
1,																//0x01						BASE_ID             			
0,  															//0x02						DH_PARA_1_L
0,																//0x03						DH_PARA_1_H
0,																//0x04						DH_PARA_2_L
0,																//0x05						DH_PARA_2_H
0,																//0x06						DH_PARA_3_L
0,																//0x07						DH_PARA_3_H				
0,																//0x08						DH_PARA_4_L
0,																//0x09						DH_PARA_4_H
0,																//0x0a						DH_PARA_5_L
0,																//0x0b						DH_PARA_5_H
0,																//0x0c						DH_PARA_6_L
0,																//0x0d						DH_PARA_6_H
0,0,															//0x0e~0x0f				Remain.
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,	//0x10~0x1f				Remain.
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,	//0x20~0x2f				Remain.
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,	//0x30~0x3f				Remain.
0,																//0x40						ZERO_OFFSET1_L
0,																//0x41						ZERO_OFFSET1_H
0,																//0x42						ZERO_OFFSET2_L
0,																//0x43						ZERO_OFFSET2_H
0,																//0x44						ZERO_OFFSET3_L
0,																//0x45						ZERO_OFFSET3_H
0,0,0,0,0,0,0,0,0,0,							//0x46~0x4f				Remain
0,																//0x50						CALIB_DATA1_L
0,																//0x51						CALIB_DATA1_H
0,																//0x52						CALIB_DATA2_L
0,																//0x53						CALIB_DATA2_H
0,																//0x54						CALIB_DATA3_L
0,																//0x55						CALIB_DATA3_H
0,0,0,0,0,0,0,0,0,0,							//0x56~0x5f				Remain
};
/* Exported Functions --------------------------------------------------------*/
/**
  * @brief  Write robot ID into EEPROM.
	* @param  *New_Robot_ID: address of new ID.
						sizeofData: byte.
						Mem_Addr: Initial address of memory storing the data. (0x00~0x2048).
	* @retval 1:Error; 0:correct.
  */
uint8_t EEPROM_Robot_ID_Write(uint16_t *New_Robot_ID, uint16_t sizeofData, uint16_t Mem_Addr)
{
	if(BSP_I2C_Write(Mem_Addr, New_Robot_ID, sizeofData))
		return 1;
		
	memcpy(&EEPROM_MEM[BASE_ID], New_Robot_ID, sizeofData);
	return 0;
};

/**
  * @brief  Read robot ID from EEPROM.
	* @param  *Robot_ID: address of recieving ID.
						sizeofData: byte.
						Mem_Addr: Initial address of memory storing the data. (0x00~0x2048).
	* @retval 1:Error; 0:correct.
  */
uint8_t EEPROM_Robot_ID_Read(uint16_t *Robot_ID, uint16_t sizeofData, uint16_t Mem_Addr)
{
	if(BSP_I2C_Read(Mem_Addr, Robot_ID, sizeofData))
		return 1;
		
	return 0;
};

/**
  * @brief  Write robot DH parameters into EEPROM, copy it into Robot_DH_Para.
	* @param  Robot_DH_Para_Write: DH parameters.
						sizeofData: byte.
						Mem_Addr: Initial address of memory storing the data. (0x00~0x2048).						
	* @retval 1:Error; 0:correct.
  */
uint8_t EEPROM_Robot_DH_Write(DH_Para Robot_DH_Para_Write, uint16_t sizeofData, uint16_t Mem_Addr)
{
	memcpy(&EEPROM_MEM[DH_PARA_1_L], &Robot_DH_Para_Write, sizeofData);
	if(BSP_I2C_Write(Mem_Addr, &EEPROM_MEM[DH_PARA_1_L], sizeofData))
		return 1;	

	return 0;
};


/**
  * @brief  Read robot DH parameters from EEPROM, copy it into Robot_DH_Para.
	* @param  Robot_DH_Para_Write: DH parameters.
						sizeofData: byte.
						Mem_Addr: Initial address of memory storing the data. (0x00~0x2048).						
	* @retval 1:Error; 0:correct.
  */
uint8_t EEPROM_Robot_DH_Read(DH_Para *Robot_DH_Para_Read, uint16_t sizeofData, uint16_t Mem_Addr)
{
	if(BSP_I2C_Read(Mem_Addr, (uint16_t *)Robot_DH_Para_Read, sizeofData))
		return 1;
	
	return 0;
};

uint8_t EEPROM_Robot_DH_RW_Test(void)
{
	DH_Para Robot_DH_Para1 ={
		{1,2,-3,4,5,6},	//alpha
		{7,-8,9,10,11,12},	//a
		{13,14,15,-16,17,18},	//d
	};

	DH_Para Robot_DH_Para2 ={
		{0,0,0,0,0,0},	//alpha
		{0,0,0,0,0,0},	//a
		{0,0,0,0,0,0},	//d
	};
	EEPROM_Robot_DH_Write(Robot_DH_Para1, DH_PARA_DATA_SIZE, DH_PARA_MEM_ADDR);
	float data[18];
	memcpy(data,&Robot_DH_Para1, DH_PARA_DATA_SIZE);
	for(uint16_t i=0; i<18; i++)
	{
		printf("data[%d]=%f\n", i, data[i]);
	}
	uint16_t data_HW[36];
	uint16_t *pdata = (uint16_t *)&Robot_DH_Para1;
	memcpy(data_HW, &Robot_DH_Para1, DH_PARA_DATA_SIZE);
	for(uint16_t i=0; i<36; i++)
	{
		printf("data_HW[%d]=0x%04x, *pdata[%d] = 0x%04x\n", i, data_HW[i], i, *(pdata+i));
	}
	
	HAL_Delay(10);
	
	EEPROM_Robot_DH_Read(&Robot_DH_Para2, DH_PARA_DATA_SIZE, DH_PARA_MEM_ADDR);
	memcpy(data_HW, &Robot_DH_Para2, DH_PARA_DATA_SIZE);
	for(uint16_t i=0; i<36; i++)
	{
		printf("data2_HW[%d]=0x%04x, *pdata[%d] = 0x%04x\n", i, data_HW[i], i, *(pdata+i));
	}
	
	printf("result = %d\n", memcmp(data,data_HW,DH_PARA_DATA_SIZE));
	printf("result2 = %d\n", memcmp(&Robot_DH_Para2,&Robot_DH_Para1,DH_PARA_DATA_SIZE));
}

/********************** (C) COPYRIGHT 2020 Smokie Robotics *****END OF FILE****/


