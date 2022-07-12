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

/* INCLUDE FILE DECLARATIONS */
#include <stdio.h>
#include <string.h>
#include "ax_uart.h"
#include "samplehw.h"

/* NAMING CONSTANT DECLARATIONS */
/* MACRO DECLARATIONS */
/* TYPE DECLARATIONS */
/* GLOBAL VARIABLES DECLARATIONS */
AX_UART_OBJECT	UART_Obj;

/* LOCAL VARIABLES DECLARATIONS */

/* LOCAL SUBPROGRAM DECLARATIONS */

/* LOCAL SUBPROGRAM BODIES */

/* EXPORTED SUBPROGRAM BODIES */

/*
 * ----------------------------------------------------------------------------
 * Function Name: AX_UART_Init()
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
int AX_UART_Init(void)
{
	GPIO_InitTypeDef    GPIO_InitStructure;
	UART_HandleTypeDef *pUartHandle = &UART_Obj.Handle;

	/* Initializes UART transfer structure */
	memset (&UART_Obj, 0, sizeof(UART_Obj));
	UART_Obj.RxBufFree = AX_UART_RX_BUF_SIZE;	
	UART_Obj.TxBufFree = AX_UART_TX_BUF_SIZE;	
	pUartHandle->Instance = AX_UART_INSTANCE;

	/* Enable UART clock source */
	HW_UART_ClkSource(pUartHandle->Instance, ENABLE);

	/* Initializes UART module */
	pUartHandle->Init.BaudRate = AX_UART_BAUDRATE;
	pUartHandle->Init.WordLength = UART_WORDLENGTH_8B;
	pUartHandle->Init.StopBits = UART_STOPBITS_1;
	pUartHandle->Init.Parity = UART_PARITY_NONE;
	pUartHandle->Init.Mode = UART_MODE_TX_RX;
	pUartHandle->Init.HwFlowCtl = UART_HWCONTROL_NONE;
	pUartHandle->Init.OverSampling = UART_OVERSAMPLING_16;
	//pUartHandle->Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
	HAL_UART_Init(pUartHandle);
	
	/* Enable UART GPIO */
	HW_GPIO_ClkSource(AX_UART_GPIO_PORT, ENABLE);
	GPIO_InitStructure.Pin = AX_UART_GPIO_TX_PIN | AX_UART_GPIO_RX_PIN;
	GPIO_InitStructure.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStructure.Pull = GPIO_NOPULL;	
	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_MEDIUM;
	GPIO_InitStructure.Alternate = AX_UART_GPIO_AF;
	HAL_GPIO_Init(AX_UART_GPIO_PORT, &GPIO_InitStructure);
	
	/* Enable UART RX interrupt */
	__HAL_UART_ENABLE_IT(pUartHandle, UART_IT_RXNE);
	
	/* Enable NVIC for UART */
	HAL_NVIC_SetPriorityGrouping(AX_UART_NVIC_PRIORITY_GROUP);
	HAL_NVIC_SetPriority(AX_UART_IRQ, AX_UART_NVIC_PREEMPTION_PRIORITY, AX_UART_NVIC_SUB_PRIORITY);
	HAL_NVIC_EnableIRQ(AX_UART_IRQ);
	
	/* Enable UART module */	
	__HAL_UART_ENABLE(pUartHandle);

	return 0;
} /* End of AX_UART_Init() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: AX_UART_DeInit()
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
int AX_UART_DeInit(void)
{
	/* Disable UART interrupt */	
	HAL_NVIC_DisableIRQ(AX_UART_IRQ);
	
	/* Disable UART periphral */
	__HAL_UART_DISABLE(&UART_Obj.Handle);
	
	/* Disable UART module */
	HAL_UART_DeInit(&UART_Obj.Handle);
	return 0;
} /* End of AX_UART_DeInit() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: AX_UART_IRQHandler()
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void AX_UART_IRQHandler(void)
{
	u32 Flags, Control, tmp32;
	USART_TypeDef *pUartReg = UART_Obj.Handle.Instance;
	
	Flags   = pUartReg->SR;
	Control = pUartReg->CR1;

	if((Control & USART_CR1_RXNEIE) && (Flags & (UART_FLAG_RXNE | UART_FLAG_ORE)))	
	{
		/* RX IRQ handling */
		while(pUartReg->SR & UART_FLAG_RXNE)
		{
			/* Read data from RX data reg. and clear RX interrupt flag */
			tmp32 = pUartReg->DR;
			if (UART_Obj.RxBufFree != 0)
			{
				UART_Obj.RxBuf[UART_Obj.RxWrPtr] = (u8)tmp32;
				UART_Obj.RxWrPtr ++;
				if(UART_Obj.RxWrPtr >= AX_UART_RX_BUF_SIZE)
				{
					UART_Obj.RxWrPtr = 0;
				}
				UART_Obj.RxBufFree--;
			}
		}
	}
	if ((Control & USART_CR1_TXEIE) && (Flags & UART_FLAG_TXE))
	{
		/* TX IRQ handling */		
		while(pUartReg->SR & UART_FLAG_TXE)
		{
			/* Write TX data reg. and clear TX interrupt flag */
			pUartReg->DR = UART_Obj.TxBuf[UART_Obj.TxRdPtr];
			UART_Obj.TxRdPtr++;
			if(UART_Obj.TxRdPtr >= AX_UART_TX_BUF_SIZE)
			{
				UART_Obj.TxRdPtr = 0;
			}
			UART_Obj.TxBufFree++;
			if (UART_Obj.TxBufFree >= AX_UART_TX_BUF_SIZE)
			{
				UART_Obj.TxBufFree = AX_UART_TX_BUF_SIZE;
				__HAL_UART_DISABLE_IT(&UART_Obj.Handle, UART_IT_TXE);
				return;
			}
		}
	}
} /* End of AX_UART_IRQHandler() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: AX_UART_GetChar()
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
char AX_UART_GetChar(void)
{
	char ch;

	if (UART_Obj.RxBufFree != AX_UART_RX_BUF_SIZE)
	{
		__HAL_UART_DISABLE_IT(&UART_Obj.Handle, UART_IT_RXNE);
		ch = UART_Obj.RxBuf[UART_Obj.RxRdPtr];
		UART_Obj.RxBufFree++;
		UART_Obj.RxRdPtr++;
		if(UART_Obj.RxRdPtr >= AX_UART_RX_BUF_SIZE)
		{
			UART_Obj.RxRdPtr = 0;
		}
		__HAL_UART_ENABLE_IT(&UART_Obj.Handle, UART_IT_RXNE);
		return ch;
	}
	else
	{
		return 0;
	}

} /* End of AX_UART_GetChar() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: AX_UART_PutChar()
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
unsigned char AX_UART_PutChar(unsigned char ch)
{
	/* block mode */
	while (UART_Obj.TxBufFree == 0)
	{
	}

	__HAL_UART_DISABLE_IT(&UART_Obj.Handle, UART_IT_TXE);
	UART_Obj.TxBuf[UART_Obj.TxWrPtr] = ch;
	UART_Obj.TxBufFree--;
	UART_Obj.TxWrPtr++;
	if (UART_Obj.TxWrPtr >= AX_UART_TX_BUF_SIZE)
	{
		UART_Obj.TxWrPtr = 0;
	}
	__HAL_UART_ENABLE_IT(&UART_Obj.Handle, UART_IT_TXE);
	return ch;

} /* End of AX_UART_PutChar() */

/* End of ax_uart.c */
