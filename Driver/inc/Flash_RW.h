/**
  ******************************************************************************
  * @FileName:		Flash_RW.h
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
#ifndef __FLASH_RW_H
#define __FLASH_RW_H


/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private Includes ----------------------------------------------------------*/
#include "BSP_UART.h"
#include "BSP_STM32_Flash.h"
#include "Protocol.h"

/* Private Typedefs ----------------------------------------------------------*/

/* Macros --------------------------------------------------------------------*/
#define FLASH_START_ADDR_SYSTEM_STATE   ADDR_FLASH_SECTOR_11 

/* Private Variables ---------------------------------------------------------*/

/* External Variables --------------------------------------------------------*/

/* Exported Functions --------------------------------------------------------*/

uint8_t Flash_Mem_Write(uint16_t *Data, uint16_t NumberOfByte, uint32_t Address);
uint8_t Flash_Mem_Read(uint16_t *Data, uint16_t NumberOfByte, uint32_t Address);
uint8_t Flash_Mem_Erase(void);



#endif
/********************** (C) COPYRIGHT 2020 Smokie Robotics *****END OF FILE****/


