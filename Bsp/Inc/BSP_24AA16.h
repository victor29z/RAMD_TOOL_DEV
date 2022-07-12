/**
  ******************************************************************************
  * @FileName:		BSP_24AA16.h
  * @Author:		Hui
  * @Version:		V1.0.0
  * @Date:			06-15-2020
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
#ifndef __BSP_24AA16_H
#define __BSP_24AA16_H


/* Private Includes ----------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "BSP_UART.h"
#include "i2c.h"
#include "string.h"
/* Private Typedefs ----------------------------------------------------------*/

/* Macros --------------------------------------------------------------------*/
#define BASE_ADDR_24AA16_Write 0xA0
#define BASE_ADDR_24AA16_Read 0xA1
#define I2C_handle hi2c2
#define ROM_SIZE_24AA16  2048

//Macros of error code
#define WDATA_OVERFLOW_24AA16  	0x01
#define WDATA_HAL_ERR_24AA16		0x02
#define RDATA_OVERFLOW_24AA16   0x03
#define RDATA_HAL_ERR_24AA16 		0x04


#define EEPROM_PAGESIZE					16

/* Private Variables ---------------------------------------------------------*/

/* External Variables --------------------------------------------------------*/

/* Exported Functions --------------------------------------------------------*/
uint8_t BSP_24AA16_Init(void);
uint16_t BSP_I2C_Write(uint16_t Mem_Addr, uint16_t *WriteBuffer, uint16_t NumByteToWrite);
uint16_t BSP_I2C_Block_Write(uint16_t Addr_Block, uint16_t Mem_Addr, uint16_t *WriteBuffer, uint16_t NumByteToWrite);
uint16_t BSP_I2C_Read(uint16_t Mem_Addr, uint16_t *ReadBuffer, uint16_t NumByteToWrite);
uint16_t BSP_I2C_Block_Read(uint16_t Block_Num, uint16_t Mem_Addr, uint16_t *ReadBuffer, uint16_t NumByteToWrite);
void BSP_I2C_test(void);



#endif 
/********************** (C) COPYRIGHT 2020 Smokie Robotics *****END OF FILE****/
