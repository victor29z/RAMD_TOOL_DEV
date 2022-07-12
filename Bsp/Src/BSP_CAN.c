/**
  ******************************************************************************
  * @FileName:		BSP_CAN.c
  * @Author:		Hui
  * @Version:		V1.0.0
  * @Date:			06-22-2020
  * @Description:   
  * @Others:
  ******************************************************************************
  * @FunctionsList:	
  *
  *
  ******************************************************************************
  * @Copyright(C), 2020 Smokie Robotics, Inc
  ******************************************************************************
  * @History:
  *
  ******************************************************************************
  */


/* Private Includes ----------------------------------------------------------*/
#include "BSP_CAN.h"

/* Private Typedefs ----------------------------------------------------------*/

/* Macros --------------------------------------------------------------------*/

/* Private Variables ---------------------------------------------------------*/
CAN_RxHeaderTypeDef     RxMsg;

/* External Variables --------------------------------------------------------*/
uint8_t can_cmd_data[DEBUG_CAN_BUFF_SIZE] = {0};
uint8_t can_cmd_size = 0;
bool new_can_cmd_flag = 0;

/* Exported Functions --------------------------------------------------------*/
/**
  * @brief  initialize can filter and interrupt
  * @param  hcan: can handler
  * @retval None
  */
 
uint8_t BSP_CAN_Init(void)   //�û���ʼ������
{
	printf("Initializing CAN ... ");
	
	can_cmd_size = 0;
	new_can_cmd_flag = false;
	
	CAN_FilterTypeDef  sFilterConfig;
	HAL_StatusTypeDef  HAL_Status;
	
	sFilterConfig.FilterBank = 0;                       //use filter0
	sFilterConfig.FilterMode =  CAN_FILTERMODE_IDLIST;  //use id list mode
	sFilterConfig.FilterScale = CAN_FILTERSCALE_16BIT;    
		
	sFilterConfig.FilterIdHigh = CAN_ID_BASE<<5;   //BASE_ID������ʶ��4��ID
	sFilterConfig.FilterIdLow  = (CAN_ID_BASE + 1) <<5;  //BASE_ID+1  
		
	sFilterConfig.FilterMaskIdHigh =(CAN_ID_BASE + 2) << 5;//BASE_ID+2
//	sFilterConfig.FilterMaskIdLow =(CAN_ID_BASE + 3) << 5;//BASE_ID+2
	sFilterConfig.FilterMaskIdLow  =CAN_ID_BROADCAST << 5; //Broadcast ID
	sFilterConfig.FilterFIFOAssignment = CAN_RX_FIFO0;	// use can_rx_fifo0    

	sFilterConfig.FilterActivation = ENABLE;  	//enable filter
	sFilterConfig.SlaveStartFilterBank  = 0; 

	HAL_Status=HAL_CAN_ConfigFilter(CAN_HANDLE, &sFilterConfig);
	HAL_Status=HAL_CAN_Start(CAN_HANDLE);  //enable CAN
		
	HAL_Status=HAL_CAN_ActivateNotification(CAN_HANDLE, CAN_IT_RX_FIFO0_MSG_PENDING); // enable interrupt
	
	printf("Done\r\n");
	
	return 0;
}

/**
  * @brief  overrided can receive pending interrupt callback
  * @param  hcan: can handler
  * @retval None
  */

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)  //���ջص�����
{
  uint8_t  Data[8];
  HAL_StatusTypeDef	HAL_RetVal;
  
	if(hcan ==&hcan1)
	{
		HAL_RetVal=HAL_CAN_GetRxMessage(CAN_HANDLE, CAN_RX_FIFO0, &RxMsg, Data); //copy data from canrxfifo into Data[8]
		if(HAL_OK==HAL_RetVal)
		{                              			
				//�������������
			can_cmd_size = RxMsg.DLC;
			memcpy(can_cmd_data, Data, can_cmd_size);
			new_can_cmd_flag = true;
//			for(uint16_t i=0; i<8; i++)
//			{
//				printf("data[%d] = %d\r\n", i, Data[i]);
//			}
		}
	}
}

/**
  * @brief  send a can message
  * @param  hcan: can handler
  			ID: CAN ID
  			pData: data bytes
  			Len: Length of data
  * @retval Error number
  */

uint8_t BSP_CANx_SendNormalData(uint16_t ID,uint8_t *pData,uint16_t Len)
{
	HAL_StatusTypeDef	HAL_RetVal;
  uint16_t SendTimes, SendCNT=0;
	uint8_t  FreeTxNum=0;
	static CAN_TxHeaderTypeDef     TxMsg;
	TxMsg.StdId=ID;
	
	if(!pData || !Len)  return 1;
	
	SendTimes = Len/8+(Len%8?1:0);
	FreeTxNum = HAL_CAN_GetTxMailboxesFreeLevel(CAN_HANDLE);
	TxMsg.DLC = 8;
	
	while(SendTimes--)
	{
		if(0==SendTimes)
		{
			if(Len%8)
				TxMsg.DLC=Len%8;
		}
		while(0==FreeTxNum)
		{
			FreeTxNum = HAL_CAN_GetTxMailboxesFreeLevel(CAN_HANDLE);
		}
//		HAL_Delay(1);  
		HAL_RetVal = HAL_CAN_AddTxMessage(CAN_HANDLE, &TxMsg, pData+SendCNT, (uint32_t*)CAN_TX_MAILBOX0); 
		if(HAL_RetVal!=HAL_OK)
		{
			return 2;
		}
		SendCNT+=8;
	}
	
  return 0;
}

void BSP_CAN_Test()
{
	uint8_t TempData[3]={0x01, 0x02, 0x03};
	BSP_CANx_SendNormalData(0xfe, TempData, 3);
	HAL_Delay(1000);
}
/********************** (C) COPYRIGHT 2020 Smokie Robotics *****END OF FILE****/


