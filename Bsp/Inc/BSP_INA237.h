/**
  ******************************************************************************
  * @FileName:	BSP_INA237.h
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BSP_INA237_H
#define __BSP_INA237_H


/* Private Includes ----------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "BSP_UART.h"
#include "i2c.h"
#include "string.h"
/* Private Typedefs ----------------------------------------------------------*/

/* Macros --------------------------------------------------------------------*/
#define BASE_ADDR_INA237_Write 0X80 //bits 10000000=0x80
#define BASE_ADDR_INA237_Read  0X81	//bits 10000001=0x81 
#define I2C_handle hi2c2

//Macros of error code
#define WDATA_OVERFLOW_INA237  	0x01
#define WDATA_HAL_ERR_INA237		0x02
#define RDATA_OVERFLOW_INA237   0x03
#define RDATA_HAL_ERR_INA237		0x04

//INA237 Register Maps
#define CURRLSBCALC_3	          0x02 //Shunt Calibration 
#define VBUS	                  0x05 //Bus Voltage Measurement
#define CURRENT	                0x07 //Current Result
#define BOVL	                  0x0E //Bus Overvoltage Threshold
#define MANUFACTURER_ID	        0x3E //Manufacturer ID:0x5449
 
//INA237 Register Value
#define MANUFACTURER_ID_VALUE 	0x5449 //Manufacturer ID:0x5449
/* Private Variables ---------------------------------------------------------*/

/* External Variables --------------------------------------------------------*/

/* Exported Functions --------------------------------------------------------*/
uint8_t BSP_INA237_Init(void);
uint16_t BSP_PWR_I2C_Read_Voltage(void);
uint32_t BSP_PWR_I2C_Read_Current(void);
uint16_t BSP_PWR_I2C_Block_Write(uint16_t Offset, uint16_t *WriteBuffer, uint16_t NumByteToWrite);
uint16_t BSP_PWR_I2C_Block_Read(uint16_t Offset, uint16_t *ReadBuffer, uint16_t NumByteToWrite);
void BSP_PWR_I2C_test(void);



#endif 
/********************** (C) COPYRIGHT 2020 Smokie Robotics *****END OF FILE****/
