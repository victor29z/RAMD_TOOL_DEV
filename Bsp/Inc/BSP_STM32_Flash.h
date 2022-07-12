/**
  ******************************************************************************
  * @FileName:		Flash_RW.h
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
#ifndef __BSP_STM32_FLASH_H
#define __BSP_STM32_FLASH_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "BSP_UART.h"
/* Private Includes ----------------------------------------------------------*/

/* Private Typedefs ----------------------------------------------------------*/

/* Macros --------------------------------------------------------------------*/
/************************** STM32 �ڲ� FLASH ���� *****************************/

#define ADDR_FLASH_SECTOR_0     ((uint32_t)0x08000000) /* Base address of Sector 0, 16 Kbytes   */
#define ADDR_FLASH_SECTOR_1     ((uint32_t)0x08004000) /* Base address of Sector 1, 16 Kbytes   */
#define ADDR_FLASH_SECTOR_2     ((uint32_t)0x08008000) /* Base address of Sector 2, 16 Kbytes   */
#define ADDR_FLASH_SECTOR_3     ((uint32_t)0x0800C000) /* Base address of Sector 3, 16 Kbytes   */
#define ADDR_FLASH_SECTOR_4     ((uint32_t)0x08010000) /* Base address of Sector 4, 64 Kbytes   */
#define ADDR_FLASH_SECTOR_5     ((uint32_t)0x08020000) /* Base address of Sector 5, 128 Kbytes  */
#define ADDR_FLASH_SECTOR_6     ((uint32_t)0x08040000) /* Base address of Sector 6, 128 Kbytes  */
#define ADDR_FLASH_SECTOR_7     ((uint32_t)0x08060000) /* Base address of Sector 7, 128 Kbytes  */
#define ADDR_FLASH_SECTOR_8     ((uint32_t)0x08080000) /* Base address of Sector 8, 128 Kbytes  */
#define ADDR_FLASH_SECTOR_9     ((uint32_t)0x080A0000) /* Base address of Sector 9, 128 Kbytes  */
#define ADDR_FLASH_SECTOR_10    ((uint32_t)0x080C0000) /* Base address of Sector 10, 128 Kbytes */
#define ADDR_FLASH_SECTOR_11    ((uint32_t)0x080E0000) /* Base address of Sector 11, 128 Kbytes */

/* Ҫ�����ڲ�FLASH����ʼ��ַ */
#define FLASH_USER_START_ADDR   ADDR_FLASH_SECTOR_8   
/* Ҫ�����ڲ�FLASH�Ľ�����ַ */
#define FLASH_USER_END_ADDR     ADDR_FLASH_SECTOR_11 + BSP_STM32_Flash_Get_Sector_Size(ADDR_FLASH_SECTOR_11) - 1 

#define ADDR_OVERFLOW_FLASH 0x01
#define WDATA_HAL_ERR_FLASH 0x02

/* Private Variables ---------------------------------------------------------*/

/* External Variables --------------------------------------------------------*/

/* Exported Functions --------------------------------------------------------*/
uint8_t BSP_STM32_Flash_Init(void);
static uint32_t BSP_STM32_Flash_Get_Sector_Size(uint32_t Sector);
static uint32_t BSP_STM32_Flash_Get_Sector(uint32_t Address);
uint8_t BSP_STM32_Flash_HW_Write(uint16_t *Data, uint16_t NumberOfByte, uint32_t Address);
uint8_t BSP_STM32_Flash_HW_Read(uint16_t *data, uint16_t NumberOfByte, uint32_t Address);


#endif /* __STM32FLASH */

/********************** (C) COPYRIGHT 2020 Smokie Robotics *****END OF FILE****/
