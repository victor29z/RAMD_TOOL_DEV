/**
  ******************************************************************************
  * @FileName:		EEPROM_RW.h
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
#ifndef __EEPROM_RW_H
#define __EEPROM_RW_H


/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private Includes ----------------------------------------------------------*/
#include "BSP_UART.h"
#include "BSP_24AA16.h"

/* Private Typedefs ----------------------------------------------------------*/
typedef struct
{
	float alpha[6];
	float a[6];
	float d[6];
}DH_Para;


/* Macros --------------------------------------------------------------------*/
//address of 1st block; 24aa16 has 8 blocks.
#define ADDR_24AA16_Write 			0xA0   
#define ADDR_24AA16_Read 				0xA1

//Initial addresses of data on EEPROM
#define EEPROM_BASE_ADDR				0x0000

#define BASE_ID_MEM_ADDR 				EEPROM_BASE_ADDR + BASE_ID*2
#define DH_PARA_MEM_ADDR 				EEPROM_BASE_ADDR + DH_PARA_1_L*2
#define ZERO_OFFSET_MEM_ADDR 		EEPROM_BASE_ADDR + ZERO_OFFSET1_L*2
#define CALIB_DATA_MEM_ADDR 		EEPROM_BASE_ADDR + CALIB_DATA1_L*2

//Data size (Byte)
#define BASE_ID_DATA_SIZE				2
#define DH_PARA_DATA_SIZE				4*18
#define ZERO_OFFSET_DATA_SIZE		4*3
#define CALIB_DATA_SIZE					4*3

#define EEPROM_MEM_SIZE  				126  //EEPROM has 8 blocks, each block has 128bytes.

/* Private Variables ---------------------------------------------------------*/

/* External Variables --------------------------------------------------------*/
extern DH_Para Robot_DH_Para;
extern uint16_t EEPROM_MEM[EEPROM_MEM_SIZE];

//Address of EEPROM memary data in EEPROM_MEM array.
#define				BASE_ID											0x01						             			
#define  			DH_PARA_1_L									0x02						
#define				DH_PARA_1_H									0x03						
#define				DH_PARA_2_L									0x04						
#define				DH_PARA_2_H									0x05						
#define				DH_PARA_3_L									0x06						
#define				DH_PARA_3_H									0x07										
#define				DH_PARA_4_L									0x08						
#define				DH_PARA_4_H									0x09						
#define				DH_PARA_5_L									0x0a						
#define				DH_PARA_5_H									0x0b						
#define				DH_PARA_6_L									0x0c						
#define				DH_PARA_6_H									0x0d						

#define				ZERO_OFFSET1_L							0x40						
#define				ZERO_OFFSET1_H							0x41						
#define				ZERO_OFFSET2_L							0x42						
#define				ZERO_OFFSET2_H							0x43						
#define				ZERO_OFFSET3_L							0x44						
#define				ZERO_OFFSET3_H							0x45						

#define				CALIB_DATA1_L								0x50						
#define				CALIB_DATA1_H								0x51						
#define				CALIB_DATA2_L								0x52						
#define				CALIB_DATA2_H								0x53						
#define				CALIB_DATA3_L								0x54						
#define				CALIB_DATA3_H								0x55						
/* Exported Functions --------------------------------------------------------*/

uint8_t EEPROM_Robot_ID_Write(uint16_t *New_Robot_ID, uint16_t sizeofData, uint16_t Mem_Addr);
uint8_t EEPROM_Robot_ID_Read(uint16_t *New_Robot_ID, uint16_t sizeofData, uint16_t Mem_Addr);

uint8_t EEPROM_Robot_DH_Write(DH_Para Robot_DH_Para, uint16_t sizeofData, uint16_t Mem_Addr);
uint8_t EEPROM_Robot_DH_Read(DH_Para * Robot_DH_Para_Read, uint16_t sizeofData, uint16_t Mem_Addr);
uint8_t EEPROM_Robot_DH_RW_Test(void);

#endif
/********************** (C) COPYRIGHT 2020 Smokie Robotics *****END OF FILE****/


