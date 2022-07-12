/*
 ******************************************************************************
 *     Copyright (c) 2018	ASIX Electronic Corporation      All rights reserved.
 *
 *     This is unpublished proprietary source code of ASIX Electronic Corporation
 *
 *     The copyright notice above does not evidence any actual or intended
 *     publication of such source code.
 ******************************************************************************
 */
#ifndef __AX_UART_H__
#define __AX_UART_H__
/* INCLUDE FILE DECLARATIONS */
#include "stm32f4xx_hal.h"
#include "ax_intf.h"

/* NAMING CONSTANT DECLARATIONS */
#define AX_UART_TX_BUF_SIZE                1024
#define AX_UART_RX_BUF_SIZE                512
#define AX_UART_BAUDRATE                   115200
#define AX_UART_NVIC_PRIORITY_GROUP        NVIC_PRIORITYGROUP_3
#define AX_UART_NVIC_PREEMPTION_PRIORITY   7
#define AX_UART_NVIC_SUB_PRIORITY          2
#define AX_UART_INSTANCE                   USART3
//#define AX_UART_IRQHandler                 USART3_IRQHandler
#define AX_UART_GPIO_AF                    GPIO_AF7_USART3
#define AX_UART_IRQ                        USART3_IRQn
#define AX_UART_GPIO_PORT                  GPIOB
#define AX_UART_GPIO_TX_PIN                GPIO_PIN_10
#define AX_UART_GPIO_RX_PIN                GPIO_PIN_11

/* TYPE DECLARATIONS */
typedef struct{
	UART_HandleTypeDef       Handle;
	
	unsigned char        RxBuf[AX_UART_RX_BUF_SIZE];
	__IO unsigned long   RxWrPtr;
	__IO unsigned long   RxRdPtr;
	__IO unsigned long   RxBufFree;
	
	unsigned char        TxBuf[AX_UART_TX_BUF_SIZE];
	__IO unsigned long   TxWrPtr;
	__IO unsigned long   TxRdPtr;
	__IO unsigned long   TxBufFree;	
} AX_UART_OBJECT;
																								
/* GLOBAL VARIABLES */
/* EXPORTED SUBPROGRAM SPECIFICATIONS */ 
int AX_UART_Init(void);
int AX_UART_DeInit(void);
char AX_UART_GetChar(void);
unsigned char AX_UART_PutChar(unsigned char);
#endif /* __AX_UART_H__ */

/* End of ax_uart.h */
