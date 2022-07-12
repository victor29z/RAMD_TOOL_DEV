/**
  ******************************************************************************
  * @FileName:		Flash_RW.c
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
#include "Flash_RW.h"

/* Private Includes ----------------------------------------------------------*/

/* Private Typedefs ----------------------------------------------------------*/

/* Macros --------------------------------------------------------------------*/

/* Private Variables ---------------------------------------------------------*/

/* External Variables --------------------------------------------------------*/

/* Exported Functions --------------------------------------------------------*/
/**
  * @brief  Write robot ID into EEPROM.
  * @param  None
	* @retval 1:Error; 0:correct.
  */
uint8_t Flash_Mem_Write(uint16_t *Data, uint16_t NumberOfByte, uint32_t Address)
{
	uint8_t status;
	status = BSP_STM32_Flash_HW_Write(Data, NumberOfByte, Address);
	
	return status;
};

uint8_t Flash_Mem_Read(uint16_t *Data, uint16_t NumberOfByte, uint32_t Address)
{
	uint8_t status;
	status = BSP_STM32_Flash_HW_Read(tool_state, TOOL_STATE_BUF_SIZE, FLASH_START_ADDR_SYSTEM_STATE);
	
	return status;
}

uint8_t Flash_Mem_Erase()
{
	uint8_t status;
	uint16_t flash_erase[TOOL_STATE_BUF_SIZE] = {0};
	status = BSP_STM32_Flash_HW_Write(flash_erase, TOOL_STATE_BUF_SIZE, FLASH_START_ADDR_SYSTEM_STATE);
	
	return status;
};
/********************** (C) COPYRIGHT 2020 Smokie Robotics *****END OF FILE****/


