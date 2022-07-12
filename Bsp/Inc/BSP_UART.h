
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BSP_DEBUG_USART_H
#define __BSP_DEBUG_USART_H


/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "usart.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/* Private Includes ----------------------------------------------------------*/

/* Private Typedefs ----------------------------------------------------------*/

/* Macros --------------------------------------------------------------------*/
#define debug_uart		huart2				//map debug_uart to huart1, huart2, or huart3，对TOOL串口2是调试口
#define T485					huart6
#define	FT485					huart1

#define DEBUG_UART_BUFF_SIZE	64
#define T485_BUFF_SIZE				64
#define FT485_BUFF_SIZE				64

/* Private Variables ---------------------------------------------------------*/


/* External Variables --------------------------------------------------------*/
//串口1用于485力传感器，串口2用于Debug，串口6用于485通信
extern DMA_HandleTypeDef hdma_usart1_rx;
extern DMA_HandleTypeDef hdma_usart2_rx;
extern DMA_HandleTypeDef hdma_usart6_rx;

extern uint8_t debug_uart_recv_buf[DEBUG_UART_BUFF_SIZE], T485_recv_buf[T485_BUFF_SIZE], FT485_recv_buf[FT485_BUFF_SIZE];
extern bool new_uart_frame_flag, new_T485_cmd_flag, new_FT485_cmd_flag;
extern uint8_t uart_frame_data[DEBUG_UART_BUFF_SIZE], T485_cmd_data[T485_BUFF_SIZE], FT485_cmd_data[FT485_BUFF_SIZE];		
extern uint8_t uart_frame_size, T485_cmd_size, FT485_cmd_size;

/* Exported Functions --------------------------------------------------------*/
uint8_t BSP_UART_Init(void);
void BSP_Serial_CMD_Clear(void);
void UART_IDLE_Callback(UART_HandleTypeDef *huart);
uint8_t BSP_UART_Send(UART_HandleTypeDef *huart, uint8_t *data, uint16_t size);

#endif
