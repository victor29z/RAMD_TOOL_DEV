/**
  ******************************************************************************
  * @FileName:		Tool_CONN_DIO.h
  * @Author:		Hui
  * @Version:		V1.0.0
  * @Date:			
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
#ifndef __TOOL_CONN_DIO_H
#define __TOOL_CONN_DIO_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private Includes ----------------------------------------------------------*/
#include "BSP_Output.h"
#include "BSP_DO_PWR_CTRL.h"


/* Private Typedefs ----------------------------------------------------------*/

/* Macros --------------------------------------------------------------------*/
#define 	Port_PWR			0
#define 	Port_TO0			1
#define		Port_TO1			2

#define		Port_TI0			0
#define		Port_TI1			1

#define 	PWR_0					0
#define		PWR_12				1
#define		PWR_24				2
#define		PWR_GND				3

#define		DO_Port_Active			1
#define		DO_Port_Inactive		0

#define		DO_Port_Type_NPN 		0
#define		DO_Port_Type_PNP		1
#define		DO_Port_Type_PP			2
#define		DO_Port_Type_DPP		3 //Dual Pin Power


/* Private Variables ---------------------------------------------------------*/

/* Exported Functions --------------------------------------------------------*/
uint8_t DIO_Power_On(void);
uint8_t DIO_Power_Off(void);
void DO_PWR_Config(uint8_t status);
void DO0_Config(uint8_t status, uint8_t port_type);
void DO1_Config(uint8_t status, uint8_t port_type);
uint8_t Read_DI_Port(uint8_t port);

#endif
/********************** (C) COPYRIGHT 2020 Smokie Robotics *****END OF FILE****/
