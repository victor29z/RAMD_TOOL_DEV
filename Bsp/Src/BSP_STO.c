/*
 * BSP_STO.c
 *
 *  Created on: May 10, 2022
 *      Author: Nathan
 */


#include "BSP_STO.h"
#include "gpio.h"

int STO0_Read(void){
	return HAL_GPIO_ReadPin(STO0_GPIO_Port, STO0_Pin);
}


int STO1_Read(void){
	return HAL_GPIO_ReadPin(STO1_GPIO_Port, STO1_Pin);
}
