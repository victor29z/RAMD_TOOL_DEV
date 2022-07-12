
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
#include "BSP_UART.h"

/* Private Includes ----------------------------------------------------------*/

/* Private Typedefs ----------------------------------------------------------*/

/* Macros --------------------------------------------------------------------*/

/* Private Variables ---------------------------------------------------------*/
uint8_t debug_uart_recv_buf[DEBUG_UART_BUFF_SIZE] = {0}, T485_recv_buf[T485_BUFF_SIZE] = {0}, FT485_recv_buf[FT485_BUFF_SIZE] = {0};	//debug uart raw data buffer
/* External Variables --------------------------------------------------------*/
uint8_t uart_frame_data[DEBUG_UART_BUFF_SIZE] = {0}, T485_cmd_data[T485_BUFF_SIZE] = {0}, FT485_cmd_data[FT485_BUFF_SIZE] = {0};		
uint8_t uart_frame_size = 0, T485_cmd_size = 0, FT485_cmd_size = 0;
bool new_uart_frame_flag = false, new_T485_cmd_flag = false, new_FT485_cmd_flag= false;// new cmd in serial_cmd_data

/* Exported Functions --------------------------------------------------------*/



/**
  * @brief  
  * @param  None
	*
  * @retval None
  */
uint8_t BSP_UART_Init(void)
{
	printf("Initializing Debug UART ... ");
	
	BSP_Serial_CMD_Clear();
	
	__HAL_UART_ENABLE_IT(&debug_uart,UART_IT_IDLE);	//�������ڿ����ж�
	__HAL_UART_ENABLE_IT(&T485,UART_IT_IDLE);	//�������ڿ����ж�
	__HAL_UART_ENABLE_IT(&FT485,UART_IT_IDLE);	//�������ڿ����ж�
	
	HAL_UART_Receive_DMA(&debug_uart, debug_uart_recv_buf, DEBUG_UART_BUFF_SIZE);
	HAL_UART_Receive_DMA(&T485, T485_recv_buf, T485_BUFF_SIZE);
	HAL_UART_Receive_DMA(&FT485, FT485_recv_buf, FT485_BUFF_SIZE);
	
	
	
	printf("Done\r\n");
	return 0;
}

/**
  * @brief  Retargets the C library printf function to the USARTx.
  * @param  None
  * @retval None
  */
//int fputc(int ch, FILE *f)
//{
//  HAL_UART_Transmit(&debug_uart, (uint8_t *)&ch, 1, 0xffff);
//  return ch;
//}


// int __io_putchar(int ch)
// {
// 	HAL_UART_Transmit(&debug_uart, (uint8_t *)&ch, 1, 0xffff);
//   return ch;
// }

/**
  * @brief  Retargets the C library getchar,scanf function to the USARTx.
  * @param  None
  * @retval None
  */
//int fgetc(FILE * f)
//{
//  uint8_t ch = 0;
//  HAL_UART_Receive(&debug_uart,&ch, 1, 0xffff);
//  return ch;
//}

/**
  * @brief  Retargets the C library printf function to the USARTx.
  * @param  None
  * @retval None
  */
int fputc(int ch, FILE *f)
{
  HAL_UART_Transmit(&debug_uart, (uint8_t *)&ch, 1, 0xffff);
  return ch;
}


/**
  * @brief  
  * @param  None
	*
  * @retval None
  */
void UART_IDLE_Callback(UART_HandleTypeDef *huart)
{
  uint32_t temp;

	if( __HAL_UART_GET_FLAG(huart, UART_FLAG_IDLE) != RESET)
  {
		__HAL_UART_CLEAR_IDLEFLAG(huart);//�����־λ
		temp = huart->Instance->SR;  //���״̬�Ĵ���SR,��ȡSR�Ĵ�������ʵ�����SR�Ĵ����Ĺ���
		temp = huart->Instance->DR; //��ȡ���ݼĴ����е�����
		
		HAL_UART_DMAStop(huart); // clear dma buffer

		if(huart->Instance == USART2) //debug uart
	  {
			uart_frame_size = DEBUG_UART_BUFF_SIZE - __HAL_DMA_GET_COUNTER(&hdma_usart2_rx);// ��ȡDMA�д�������ݸ���
	      
			if(uart_frame_size != 0)
			{
				memcpy(uart_frame_data,debug_uart_recv_buf,uart_frame_size);
				new_uart_frame_flag = true;
			}
			HAL_UART_Receive_DMA(&huart2,debug_uart_recv_buf,DEBUG_UART_BUFF_SIZE);
	  }

		else if(huart->Instance == USART1) //FT485
	  {
			FT485_cmd_size = FT485_BUFF_SIZE - __HAL_DMA_GET_COUNTER(&hdma_usart1_rx);// ��ȡDMA�д�������ݸ���
	      
			if(FT485_cmd_size != 0)
			{
				memcpy(FT485_cmd_data, FT485_recv_buf, FT485_cmd_size);
				new_uart_frame_flag = true;
			}
			HAL_UART_Receive_DMA(&huart1, FT485_recv_buf, FT485_BUFF_SIZE);
	  } 

		else if(huart->Instance == USART6)
	  {
			uart_frame_size = DEBUG_UART_BUFF_SIZE - __HAL_DMA_GET_COUNTER(&hdma_usart6_rx);// ��ȡDMA�д�������ݸ���
	      
			if(uart_frame_size != 0)
			{
				memcpy(T485_cmd_data, T485_recv_buf, T485_cmd_size);
				new_T485_cmd_flag = true;
			}
			HAL_UART_Receive_DMA(&huart6, T485_recv_buf, T485_BUFF_SIZE);
	  }     
  }
}

/**
  * @brief  clear serial command buffer and flag
  * @param  None
  * @retval None
  */
void BSP_Serial_CMD_Clear(void)
{
	memset(uart_frame_data, 0,DEBUG_UART_BUFF_SIZE);
	memset(FT485_cmd_data, 0, FT485_BUFF_SIZE);
	memset(T485_cmd_data, 0, T485_BUFF_SIZE);
	
	uart_frame_size = 0;
	FT485_cmd_size = 0;
	T485_cmd_size = 0;
	
	new_uart_frame_flag = false;
	new_FT485_cmd_flag = false;
	new_T485_cmd_flag = false;
}

/**
  * @brief  Send uart ack msg after uart decoding
  * @param  None
  * @retval None
  */
uint8_t BSP_UART_Send(UART_HandleTypeDef *huart, uint8_t *data, uint16_t size)
{
	uint8_t status;
	
	status = HAL_UART_Transmit(huart, data, size, 0xff);
	
	return status;
}

/********************** (C) COPYRIGHT 2020 Smokie Robotics *****END OF FILE****/
