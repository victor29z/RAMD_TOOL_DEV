/**
  ******************************************************************************
  * @FileName:	BSP_Output.h
  * @Author:		Tim
  * @Version:		V1.1.0
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
  * @History: V1.1.0, Hardware pin changes, Tim
  *           V1.0.0, first version, hui
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BSP_OUTPUT_H
#define __BSP_OUTPUT_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private Includes ----------------------------------------------------------*/
#include "BSP_UART.h"

/* Private Typedefs ----------------------------------------------------------*/

/* Macros --------------------------------------------------------------------*/
//#define 	BSP_12_24_Power_EN   	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_12, GPIO_PIN_SET) //����12/24V��Դ���
//#define 	BSP_12_24_Power_DEN   HAL_GPIO_WritePin(GPIOC, GPIO_PIN_12, GPIO_PIN_RESET) //������12/24V��Դ���
//#define 	BSP_24_Power_ON   		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_11, GPIO_PIN_SET) //24��Դ���
//#define 	BSP_12_Power_ON   		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_11, GPIO_PIN_RESET) //12��Դ���

#define 	BSP_12_24_Power_EN   	HAL_GPIO_WritePin(CPUEN_GPIO_Port, CPUEN_Pin, GPIO_PIN_SET) //����12/24V��Դ���
#define 	BSP_12_24_Power_DEN   HAL_GPIO_WritePin(CPUEN_GPIO_Port, CPUEN_Pin, GPIO_PIN_RESET) //������12/24V��Դ���
#define 	BSP_24_Power_ON   		HAL_GPIO_WritePin(CPU_POWER_GPIO_Port, CPU_POWER_Pin, GPIO_PIN_SET) //24��Դ���
#define 	BSP_12_Power_ON   		HAL_GPIO_WritePin(CPU_POWER_GPIO_Port, CPU_POWER_Pin, GPIO_PIN_RESET) //12��Դ���

//#define 	BSP_CPUIO0_ON   			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_SET) 		//CPUIO0=1
//#define 	BSP_CPUIO0_OFF  			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_RESET) 	//CPUIO0=0
//#define 	BSP_CPUIO2_ON   			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_SET) 		//CPUIO2=1
//#define 	BSP_CPUIO2_OFF  			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_RESET) 	//CPUIO2=0
//#define 	BSP_CPUIO3_ON   			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET) 		//CPUIO3=1
//#define 	BSP_CPUIO3_OFF   			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET) 	//CPUIO3=0
//#define 	BSP_CPUIO4_ON   			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET) 		//CPUIO4=1
//#define 	BSP_CPUIO4_OFF  			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET) 	//CPUIO4=0

#define 	BSP_CPUIO0_ON   			HAL_GPIO_WritePin(CPUIO0_GPIO_Port, CPUIO0_Pin, GPIO_PIN_SET) 		//CPUIO0=1
#define 	BSP_CPUIO0_OFF  			HAL_GPIO_WritePin(CPUIO0_GPIO_Port, CPUIO0_Pin, GPIO_PIN_RESET) 	//CPUIO0=0
#define 	BSP_CPUIO2_ON   			HAL_GPIO_WritePin(CPUIO2_GPIO_Port, CPUIO2_Pin, GPIO_PIN_SET) 		//CPUIO2=1
#define 	BSP_CPUIO2_OFF  			HAL_GPIO_WritePin(CPUIO2_GPIO_Port, CPUIO2_Pin, GPIO_PIN_RESET) 	//CPUIO2=0
#define 	BSP_CPUIO3_ON   			HAL_GPIO_WritePin(CPUIO3_GPIO_Port, CPUIO3_Pin, GPIO_PIN_SET) 		//CPUIO3=1
#define 	BSP_CPUIO3_OFF   			HAL_GPIO_WritePin(CPUIO3_GPIO_Port, CPUIO3_Pin, GPIO_PIN_RESET) 	//CPUIO3=0
#define 	BSP_CPUIO4_ON   			HAL_GPIO_WritePin(CPUIO4_GPIO_Port, CPUIO4_Pin, GPIO_PIN_SET) 		//CPUIO4=1
#define 	BSP_CPUIO4_OFF  			HAL_GPIO_WritePin(CPUIO4_GPIO_Port, CPUIO4_Pin, GPIO_PIN_RESET) 	//CPUIO4=0
#define 	BSP_CPUIO5_ON   			HAL_GPIO_WritePin(CPUIO5_GPIO_Port, CPUIO5_Pin, GPIO_PIN_SET) 		//CPUIO5=1
#define 	BSP_CPUIO5_OFF   			HAL_GPIO_WritePin(CPUIO5_GPIO_Port, CPUIO5_Pin, GPIO_PIN_RESET) 	//CPUIO5=0


#define		Port_GND		2
#define 	Port_ON			1
#define 	Port_OFF	  0


/* Private Variables ---------------------------------------------------------*/

/* Exported Functions --------------------------------------------------------*/
uint8_t BSP_Output_Init(void);
void BSP_Output_PWR(uint8_t status);
void BSP_Output_DO0(uint8_t status);
void BSP_Output_DO1(uint8_t status);

void BSP_Output_PWR_Test(void);
void BSP_Output_DO_Test(void);

#endif
/********************** (C) COPYRIGHT 2020 Smokie Robotics *****END OF FILE****/
