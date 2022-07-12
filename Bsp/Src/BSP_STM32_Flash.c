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
	
/* Includes ------------------------------------------------------------------*/
#include "BSP_STM32_Flash.h"

/* Private Includes ----------------------------------------------------------*/

/* Private Typedefs ----------------------------------------------------------*/

/* Macros --------------------------------------------------------------------*/


/* Private Variables ---------------------------------------------------------*/
static FLASH_EraseInitTypeDef EraseInitStruct;


/* External Variables --------------------------------------------------------*/


/* Private Functions --------------------------------------------------------*/

uint8_t BSP_STM32_Flash_Init(void)
{
	printf("Initializing STM32 Flash ... ");
	
	printf("Done\r\n");
	return 0;
}


/**
  * @brief  ��������ĵ�ַ���������ڵ�sector
  * @param  Address flash��ַ
	*
  * @retval None
  */
static uint32_t BSP_STM32_Flash_Get_Sector(uint32_t Address)
{
  uint32_t sector = 0;
  
  if((Address < ADDR_FLASH_SECTOR_1) && (Address >= ADDR_FLASH_SECTOR_0))
  {
    sector = FLASH_SECTOR_0;  
  }
  else if((Address < ADDR_FLASH_SECTOR_2) && (Address >= ADDR_FLASH_SECTOR_1))
  {
    sector = FLASH_SECTOR_1;  
  }
  else if((Address < ADDR_FLASH_SECTOR_3) && (Address >= ADDR_FLASH_SECTOR_2))
  {
    sector = FLASH_SECTOR_2;  
  }
  else if((Address < ADDR_FLASH_SECTOR_4) && (Address >= ADDR_FLASH_SECTOR_3))
  {
    sector = FLASH_SECTOR_3;  
  }
  else if((Address < ADDR_FLASH_SECTOR_5) && (Address >= ADDR_FLASH_SECTOR_4))
  {
    sector = FLASH_SECTOR_4;  
  }
  else if((Address < ADDR_FLASH_SECTOR_6) && (Address >= ADDR_FLASH_SECTOR_5))
  {
    sector = FLASH_SECTOR_5;  
  }
  else if((Address < ADDR_FLASH_SECTOR_7) && (Address >= ADDR_FLASH_SECTOR_6))
  {
    sector = FLASH_SECTOR_6;  
  }
  else if((Address < ADDR_FLASH_SECTOR_8) && (Address >= ADDR_FLASH_SECTOR_7))
  {
    sector = FLASH_SECTOR_7;  
  }
  else if((Address < ADDR_FLASH_SECTOR_9) && (Address >= ADDR_FLASH_SECTOR_8))
  {
    sector = FLASH_SECTOR_8;  
  }
  else if((Address < ADDR_FLASH_SECTOR_10) && (Address >= ADDR_FLASH_SECTOR_9))
  {
    sector = FLASH_SECTOR_9;  
  }
  else if((Address < ADDR_FLASH_SECTOR_11) && (Address >= ADDR_FLASH_SECTOR_10))
  {
    sector = FLASH_SECTOR_10;  
  }
  else /* (Address < FLASH_END_ADDR) && (Address >= ADDR_FLASH_SECTOR_11) */
  {
    sector = FLASH_SECTOR_11;  
  }

  return sector;
}


/**
  * @brief  ����������Ż�ȡ������С
  * @param  Sector
	*
  * @retval None
  */
static uint32_t BSP_STM32_Flash_Get_Sector_Size(uint32_t Sector)
{
  uint32_t sectorsize = 0x00;

  if((Sector == FLASH_SECTOR_0) || (Sector == FLASH_SECTOR_1) || (Sector == FLASH_SECTOR_2) || (Sector == FLASH_SECTOR_3))
  {
    sectorsize = 16 * 1024;
  }
  else if(Sector == FLASH_SECTOR_4)
  {
    sectorsize = 64 * 1024;
  }
  else
  {
    sectorsize = 128 * 1024;
  }  
  return sectorsize;
}

/* Exported Functions --------------------------------------------------------*/

uint8_t BSP_STM32_Flash_HW_Write(uint16_t *Data, uint16_t NumberOfByte, uint32_t Address)
{
	/* ��ȡҪ�������׸����� */
	uint32_t FirstSector = 0, LastSector = 0, last_address = 0, SectorError = 0;
	uint16_t NbOfSectors = 0;
	

  FirstSector = BSP_STM32_Flash_Get_Sector(Address);
	last_address = Address + NumberOfByte - sizeof(uint16_t);
	LastSector = BSP_STM32_Flash_Get_Sector(last_address);
	NbOfSectors = LastSector - FirstSector + 1;
	
	/* �ж��Ƿ����ڲ�Flash�ڴ淶Χ�� */
	if(last_address > FLASH_USER_END_ADDR)
		return ADDR_OVERFLOW_FLASH;
	
	/* ����,ɾ����д������Ƚ��� */
  HAL_FLASH_Unlock();

  /* ��ʼ�������ṹ�� */
  EraseInitStruct.TypeErase = FLASH_TYPEERASE_SECTORS;
  EraseInitStruct.VoltageRange = FLASH_VOLTAGE_RANGE_3;
  EraseInitStruct.Sector = FirstSector;
  EraseInitStruct.NbSectors = NbOfSectors;
  if(HAL_FLASHEx_Erase(&EraseInitStruct, &SectorError) != HAL_OK)
  { 
    /* �˴�����ʹ��HAL_FLASH_GetError()����ȡ��������������� */
		return HAL_FLASH_GetError();
  }
  	
  /* ����halfwordд�����ݵ��ڲ�flash */
	for(uint16_t i=0; i<NumberOfByte/2; i++)
  {
    if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, Address, *(Data+i)) != HAL_OK)
			return WDATA_HAL_ERR_FLASH;
    Address = Address + 2;
  }
  /* ����������Ƕ�ȡ�Ļ���������� */
  HAL_FLASH_Lock(); 

	return 0;
};

uint8_t BSP_STM32_Flash_HW_Read(uint16_t *data, uint16_t NumberOfByte, uint32_t Address)
{
	for(uint16_t i=0; i<NumberOfByte/2; i++)
  {
    *(data+i) = *(__IO uint16_t*)Address;
    Address = Address + 2;
  }

	return 0;
}


/********************** (C) COPYRIGHT 2020 Smokie Robotics *****END OF FILE****/
