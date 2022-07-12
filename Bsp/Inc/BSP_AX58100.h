/**
  ******************************************************************************
  * @FileName:		BSP_AX58100.h
  * @Author:			Ning (Frank) Li
  * @Version:			V1.0.0
  * @Date:				10-28-2021
  * @Description:   
  * @Others:			None
  ******************************************************************************
  * @Copyright(C), 2021, Azure Medical Innovation Corp.
  ******************************************************************************
  * @History:
  * @Contact:			tech@azrmed.com
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BSP_AX58100_H
#define __BSP_AX58100_H

/*
	PE_5 <----> AX58100_RST
	PE_1 <----> AX_RSTO
	
	PB_5 <----> EEP_DONE
	PC_9 <----> LED_ERR
	PD_2 <----> LED_RUN
	
	PC_13 <----> SYNC_L0
	PC_14 <----> SYNC_L1
	PC_15 <----> LINT0
	
	//FSMC Control IO
	PD_4 	<--FSMC_NOE--> 		LRDn
	PD_5 	<--FSMC_NWE--> 		LWRn
	PD_6 	<--FSMC_NWAIT--> 	LRDY
	PD_7 	<--FSMC_NE1--> 		LFCSn
	PG_12 <--FSMC_NE4--> 		LESCn
	
	//16-bit Local Bus Addressing
	PF_0 	<--FSMC_A0--> 		LA1
	PF_1 	<--FSMC_A1--> 		LA2
	PF_2 	<--FSMC_A2--> 		LA3
	PF_3 	<--FSMC_A3--> 		LA4
	PF_4 	<--FSMC_A4--> 		LA5
	PF_5 	<--FSMC_A5--> 		LA6
	PF_12 <--FSMC_A6--> 		LA7
	PF_13	<--FSMC_A7--> 		LA8
	PF_14 <--FSMC_A8--> 		LA9
	PF_15 <--FSMC_A9--> 		LA10
	PG_0 	<--FSMC_A10--> 		LA11
	PG_1 	<--FSMC_A11--> 		LA12
	PG_2 	<--FSMC_A12--> 		LA13
	
	//16-bit Data
	PD_14 <--FSMC_D0--> 		LDA0
	PD_15 <--FSMC_D1--> 		LDA1
	PD_0 	<--FSMC_D2--> 		LDA2
	PD_1 	<--FSMC_D3--> 		LDA3
	PE_7 	<--FSMC_D4--> 		LDA4
	PE_8 	<--FSMC_D5--> 		LDA5
	PE_9 	<--FSMC_D6--> 		LDA6
	PE_10	<--FSMC_D7--> 		LDA7
	PE_11 <--FSMC_D8--> 		LDA8
	PE_12 <--FSMC_D9--> 		LDA9
	PE_13 <--FSMC_D10--> 		LDA10
	PE_14 <--FSMC_D11--> 		LDA11
	PE_15 <--FSMC_D12--> 		LDA12
	PD_8 	<--FSMC_D13--> 		LDA13
	PD_9 	<--FSMC_D14--> 		LDA14
	PD_10 <--FSMC_D15--> 		LDA15
*/

/* Includes ------------------------------------------------------------------*/

/* Private Includes ----------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private Typedefs ----------------------------------------------------------*/

/* Macros --------------------------------------------------------------------*/
#define AX58100_RST_PORT		GPIOE
#define AX58100_RST_PIN			GPIO_PIN_5

#define AX_RSTO_PORT				GPIOE
#define AX_RSTO_PIN					GPIO_PIN_1

#define AX_EEP_DONE_PORT		GPIOB
#define AX_EEP_DONE_PIN			GPIO_PIN_5

#define AX_LED_ERR_PORT			GPIOC
#define AX_LED_ERR_PIN			GPIO_PIN_9

#define AX_LED_RUN_PORT			GPIOD
#define AX_LED_RUN_PIN			GPIO_PIN_2

#define AX_RST_SET  	 			HAL_GPIO_WritePin(AX58100_RST_PORT, AX58100_RST_PIN, GPIO_PIN_SET)
#define AX_RST_RESET				HAL_GPIO_WritePin(AX58100_RST_PORT, AX58100_RST_PIN, GPIO_PIN_RESET)



/* Private Variables ---------------------------------------------------------*/

/* Exported Functions --------------------------------------------------------*/
uint8_t BSP_AX58100_Init(void);
void BSP_AX58100_Reset(void);


#endif 
/******* (C) COPYRIGHT 2021 Azure Medical Innovation Corp. *****END OF FILE****/


