/**
  ******************************************************************************
  * @FileName:		bsp_encrypt.h
  * @Author:		Tim
  * @Version:		V1.0.0
  * @Date:			14-April-2019
  * @Description:   This file is about Encrypt related configuration.
  * @Others:
  ******************************************************************************
  *@Copyright(C), 2010-2011, Your Company
  ******************************************************************************
  * @History:
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BSP_ENCRYPT_H__
#define __BSP_ENCRYPT_H__


/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Macro Definitions --------------------------------------------------------*/
          	 									//一次循环所花的周期数
#define  us_delay_adjust      4         	  									//调用、初始化、返回总共所用的周期数
#define	 etu 									104															//delay for sending 1 bit

/* 3DES 固定密钥 */
static uint8_t des_key[16] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F};
  

/* IO相关定义 */
#define GPIO_PORT_ENCRYPT_IO									GPIOB
#define ENCRYPT_IO_PIN											  GPIO_PIN_8

#define GPIO_PORT_ENCRYPT_RST									GPIOB
#define ENCRYPT_RST_PIN											  GPIO_PIN_9

#define ENCRYPT_IO_1()      									HAL_GPIO_WritePin(GPIO_PORT_ENCRYPT_IO, ENCRYPT_IO_PIN, GPIO_PIN_SET)
#define ENCRYPT_IO_0()      									HAL_GPIO_WritePin(GPIO_PORT_ENCRYPT_IO, ENCRYPT_IO_PIN, GPIO_PIN_RESET)
#define ENCRYPT_IO_READ()   									HAL_GPIO_ReadPin(GPIO_PORT_ENCRYPT_IO,ENCRYPT_IO_PIN)

#define ENCRYPT_RST_1()     									HAL_GPIO_WritePin(GPIO_PORT_ENCRYPT_RST, ENCRYPT_RST_PIN, GPIO_PIN_SET)
#define ENCRYPT_RST_0()     									HAL_GPIO_WritePin(GPIO_PORT_ENCRYPT_RST, ENCRYPT_RST_PIN, GPIO_PIN_RESET)

/* 加密芯片相关 */
#define FUNC_CHIP_ID                                            0x01            // 获取8字节芯片ID
#define FUNC_IC_CHECK                                           0x03            // 型号
#define FUNC_CHIP_DATA                                          0x04            // get chip_iddata,乱序排列4次，排列顺序见加密程序
#define FUNC_WRITE_KEY                                          0x05            // 写入NVM区，16字节3DES加密秘钥

/* Exported Functions -------------------------------------------------------*/
uint8_t BSP_Encrypt_Init(void);
uint8_t BSP_Encrypt_Chip_Check(void);
void BSP_Encrypt_Write_Key(void);
void BSP_Encrypt_Get_Stream(uint8_t cmd, uint8_t retLength);
void BSP_Encrypt_Send_Stream(uint8_t cmd, uint8_t* inbuf, uint8_t* outbuf);
  
#endif /* __BSP_ENCRYPT_H__ */
/************************ (C) COPYRIGHT Smokie-Robotics *****END OF FILE****/

