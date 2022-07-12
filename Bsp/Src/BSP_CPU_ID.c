/**
  ******************************************************************************
  * @FileName:	
  * @Author:		Frank
  * @Version:		V1.0.1
  * @Date:			06-17-2020
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

/* Private Includes ----------------------------------------------------------*/
#include "BSP_CPU_ID.h"
#include "BSP_UART.h"

/* Private Typedefs ----------------------------------------------------------*/

/* Macros --------------------------------------------------------------------*/

/* Private Variables ---------------------------------------------------------*/
uint32_t CPU_ID[3];

/* External Variables --------------------------------------------------------*/

/* Exported Functions --------------------------------------------------------*/	
/**
  * @brief  
  * @param  None
	*
  * @retval None
  */
uint8_t BSP_Chip_ID_Init(void)
{
	printf("Initializing Chip ID ... ");
	
	printf("Done\r\n");
	return 0;
}


/**
  * @brief  Get Chip ID, Each chip has an 96_bit unique ID  
  * @param  None
	*
  * @retval None
  */
void BSP_Get_Chip_ID(void)
{
	CPU_ID[0] = *(__IO uint32_t *)(0X1FFF7A10); // ���ֽ�
	CPU_ID[1] = *(__IO uint32_t *)(0X1FFF7A14); // 
	CPU_ID[2] = *(__IO uint32_t *)(0X1FFF7A18); // ���ֽ�
	printf("Chip ID: %X.%X.%X\r\n", CPU_ID[0], CPU_ID[1], CPU_ID[2]);
}
/********************** (C) COPYRIGHT 2020 Smokie Robotics *****END OF FILE****/
