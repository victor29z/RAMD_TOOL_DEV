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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __PID_CTRL_H
#define __PID_CTRL_H


/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include <stdio.h>
#include <math.h>
/* Private Includes ----------------------------------------------------------*/
#include "BSP_UART.h"

/* Private Typedefs ----------------------------------------------------------*/
typedef struct{
	float SetValue;
	float ActualValue;
	float Err;
	float Err_last;
	float Kp, Ki, Kd;
	float output;
	float integral;
	float integral_threshold;
	float output_max;
	float output_min;
}_pid;

typedef struct{
	float SetValue;
	float ActualValue;
	float Err;
	float Err_last;
	float Err_next;
	float Kp, Ki, Kd;
}_pid_inc;
/* Macros --------------------------------------------------------------------*/

/* Private Variables ---------------------------------------------------------*/

/* External Variables --------------------------------------------------------*/
extern _pid pid;
/* Exported Functions --------------------------------------------------------*/
void PID_Init(_pid pid);
void PID_Inc_Init(_pid_inc pid_inc);
float PID_Realize(float target_value, float real_value);
float PID_Inc_Realize(_pid_inc pid_inc, float target_value);


#endif
/********************** (C) COPYRIGHT 2020 Smokie Robotics *****END OF FILE****/


