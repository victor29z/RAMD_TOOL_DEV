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
#ifndef __ROBOT_DRIVE_H
#define __ROBOT_DRIVE_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"


/* Private Includes ----------------------------------------------------------*/
#include "BSP_ICM20600.h"
#include "BSP_ADC.h"
#include "Protocol.h"
#include "Flash_RW.h"

/* Private Typedefs ----------------------------------------------------------*/

/* Macros --------------------------------------------------------------------*/
#define PWR_Threshold 48.0*3.0/103.0
#define VOLT_LIMIT		4900


/* Private Variables ---------------------------------------------------------*/



/* External Variables --------------------------------------------------------*/

/* Exported Functions --------------------------------------------------------*/
uint8_t Search_IMU(void);
void Robot_Power_On(void);
void Robot_Power_Down(void);
void Energy_Eater_Crl(uint16_t sys_volt, uint16_t rob_volt, uint16_t volt_limit);
uint8_t Cmd_Evt(void);

#endif


/********************** (C) COPYRIGHT 2020 Smokie Robotics *****END OF FILE****/

