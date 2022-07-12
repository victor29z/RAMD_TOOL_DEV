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
#include "ecat_def.h"
#include "ecatappl.h"

#define __SAMPLEHW__ 1
#include "samplehw.h"
#undef __SAMPLEHW__
#define __SAMPLEHW__ 0

//#include "core_cmFunc.h"
#include "core_cm4.h"

#include <stdio.h>
#include "ToolAppl.h"
//#include "console.h"
#include "test.h"
#include "bsp_led.h"
/* NAMING CONSTANT DECLARATIONS */

/* MACRO DECLARATIONS */

#if INTERRUPTS_SUPPORTED
/*-----------------------------------------------------------------------------------------
------
------    Global Interrupt setting
------
-----------------------------------------------------------------------------------------*/
#define DISABLE_GLOBAL_INT             do {__set_PRIMASK(1);} while (0)
#define ENABLE_GLOBAL_INT              do {__set_PRIMASK(0);} while (0)
#define DISABLE_AL_EVENT_INT
#define ENABLE_AL_EVENT_INT

/*-----------------------------------------------------------------------------------------
------
------    SYNC0 Interrupt
------
-----------------------------------------------------------------------------------------*/
#if DC_SUPPORTED

#define DISABLE_SYNC0_INT
#define ENABLE_SYNC0_INT

#define DISABLE_SYNC1_INT
#define ENABLE_SYNC1_INT

#endif //#if DC_SUPPORTED

#endif //#if INTERRUPTS_SUPPORTED

/* TYPE DECLARATIONS */
typedef union
{
   unsigned short   Word;
   unsigned char    Byte[2];
} UBYTETOWORD;

typedef union 
{
   UINT8           Byte[2];
   UINT16          Word;
} UALEVENT;

/* GLOBAL VARIABLES DECLARATIONS */
#if AX58100_DEBUG_ENABLE
HW_DEBUG  HW_Debug = {0};
#endif


TIM_HandleTypeDef  TimeTick_Handle;
TIM_HandleTypeDef  TimeTask_Handle;
INTR_QUEUE         Intr;
UINT32             HW_PdiReentryCnt[HW_PDI_NUM] = {0,0};
UINT8              HW_LockFlag[HW_PDI_NUM] = {0,0};	
extern TIM_HandleTypeDef HW_TIMETASK_HANDLE;
extern TIM_HandleTypeDef HW_TIMETICK_HANDLE;
/* LOCAL VARIABLES DECLARATIONS */

 //Contains the content of the ALEvent register (0x220), this variable is updated on each Access to the Esc
UALEVENT           EscALEvent;

/* LOCAL SUBPROGRAM DECLARATIONS */
//spi not used 
#if (ETHERCAT_SLAVE_STACK_ENABLE)
static INT32 HW_CheckVendorProductID(void);
#endif

/* LOCAL SUBPROGRAM BODIES */
/*
 * ----------------------------------------------------------------------------
 * Function Name: HW_GPIO_ClkSource()
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void HW_GPIO_ClkSource(GPIO_TypeDef* GpioPort, UINT8 NewState)
{
	if (GpioPort == GPIOA)
	{
		if (NewState == ENABLE)
		{
			__HAL_RCC_GPIOA_CLK_ENABLE();
		}
		else
		{
			__HAL_RCC_GPIOA_CLK_DISABLE();
		}
	}
	else if  (GpioPort == GPIOB)
	{
		if (NewState == ENABLE)
		{
			__HAL_RCC_GPIOB_CLK_ENABLE();
		}
		else
		{
			__HAL_RCC_GPIOB_CLK_DISABLE();
		}
	}
	else if  (GpioPort == GPIOC)
	{
		if (NewState == ENABLE)
		{
			__HAL_RCC_GPIOC_CLK_ENABLE();
		}
		else
		{
			__HAL_RCC_GPIOC_CLK_DISABLE();
		}
	}
	else if  (GpioPort == GPIOD)
	{
		if (NewState == ENABLE)
		{
			__HAL_RCC_GPIOD_CLK_ENABLE();
		}
		else
		{
			__HAL_RCC_GPIOD_CLK_DISABLE();
		}
	}
	else if  (GpioPort == GPIOE)
	{
		if (NewState == ENABLE)
		{
			__HAL_RCC_GPIOE_CLK_ENABLE();
		}
		else
		{
			__HAL_RCC_GPIOE_CLK_DISABLE();
		}
	}	
	else if  (GpioPort == GPIOF)
	{
		if (NewState == ENABLE)
		{
			__HAL_RCC_GPIOF_CLK_ENABLE();
		}
		else
		{
			__HAL_RCC_GPIOF_CLK_DISABLE();
		}
	}
	else if  (GpioPort == GPIOG)
	{
		if (NewState == ENABLE)
		{
			__HAL_RCC_GPIOG_CLK_ENABLE();
		}
		else
		{
			__HAL_RCC_GPIOG_CLK_DISABLE();
		}
	}
	else if  (GpioPort == GPIOH)
	{
		if (NewState == ENABLE)
		{
			__HAL_RCC_GPIOH_CLK_ENABLE();
		}
		else
		{
			__HAL_RCC_GPIOH_CLK_DISABLE();
		}
	}
	else
	{
		ESC_DEBUG("Unsupported GPIO clock source.(0x%lx)\r\n", (u32)GpioPort);
	}

} /* End of HW_GPIO_ClkSource() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: HW_TIM_ClkSource()
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void HW_TIM_ClkSource(TIM_TypeDef* Instance, UINT8 NewState)
{
	if (Instance == TIM1)
	{
		if (NewState == ENABLE)
		{
			__HAL_RCC_TIM1_CLK_ENABLE();
		}
		else
		{
			__HAL_RCC_TIM1_CLK_DISABLE();
		}
	}
	else if (Instance == TIM2)
	{
		if (NewState == ENABLE)
		{
			__HAL_RCC_TIM2_CLK_ENABLE();
		}
		else
		{
			__HAL_RCC_TIM2_CLK_DISABLE();
		}
	}
	else if (Instance == TIM3)
	{
		if (NewState == ENABLE)
		{
			__HAL_RCC_TIM3_CLK_ENABLE();
		}
		else
		{
			__HAL_RCC_TIM3_CLK_DISABLE();
		}
	}
	else if (Instance == TIM4)
	{
		if (NewState == ENABLE)
		{
			__HAL_RCC_TIM4_CLK_ENABLE();
		}
		else
		{
			__HAL_RCC_TIM4_CLK_DISABLE();
		}
	}
	else if (Instance == TIM6)
	{
		if (NewState == ENABLE)
		{
			__HAL_RCC_TIM6_CLK_ENABLE();
		}
		else
		{
			__HAL_RCC_TIM6_CLK_DISABLE();
		}
	}
	else if (Instance == TIM7)
	{
		if (NewState == ENABLE)
		{
			__HAL_RCC_TIM7_CLK_ENABLE();
		}
		else
		{
			__HAL_RCC_TIM7_CLK_DISABLE();
		}
	}	
	else if (Instance == TIM8)
	{
		if (NewState == ENABLE)
		{
			__HAL_RCC_TIM8_CLK_ENABLE();
		}
		else
		{
			__HAL_RCC_TIM8_CLK_DISABLE();
		}
	}		
	else
	{
		ESC_DEBUG("Unsupported TMR clock source.(0x%lx)\r\n", (u32)Instance);
		return;
	}
} /* End of HW_TIM_ClkSource() */


/*
 * ----------------------------------------------------------------------------
 * Function Name: HW_UART_ClkSource()
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void HW_UART_ClkSource(USART_TypeDef* Instance, UINT8 NewState)
{
	if (Instance == USART1)
	{
		if (NewState == ENABLE)
		{
			__HAL_RCC_USART1_CLK_ENABLE();
		}
		else
		{
			__HAL_RCC_USART1_CLK_DISABLE();
		}
	}		
	else if (Instance == USART2)
	{
		if (NewState == ENABLE)
		{
			__HAL_RCC_USART2_CLK_ENABLE();
		}
		else
		{
			__HAL_RCC_USART2_CLK_DISABLE();
		}
	}		
	else if (Instance == USART3)
	{
		if (NewState == ENABLE)
		{
			__HAL_RCC_USART3_CLK_ENABLE();
		}
		else
		{
			__HAL_RCC_USART3_CLK_DISABLE();
		}
	}			
	else
	{
		ESC_DEBUG("Unsupported UART/USART clock source.(0x%lx)\r\n", (u32)Instance);
		return;
	}
} /* End of HW_UART_ClkSource() */



/**
  * @brief  The function operates a SPI access without addressing. 
  * @note   The first two bytes of an access to the EtherCAT ASIC always deliver the AL_Event register (0x220).
  *         It will be saved in the global "EscALEvent"
  * @param  None
  * @retval None
  */
static void GetInterruptRegister(void)
{
//#if AL_EVENT_ENABLED
//    DISABLE_AL_EVENT_INT;
//#endif

		HW_EscRead((MEM_ADDR*)EscALEvent.Byte, ESC_AL_EVENT_OFFSET, 2);
	
//#if AL_EVENT_ENABLED
//		ENABLE_AL_EVENT_INT;
//#endif
}

/**
  * @brief  The function operates a SPI access without addressing.
  * @note   Shall be implemented if interrupts are supported else this function is equal to "GetInterruptRegsiter()"
  * @note   The first two bytes of an access to the EtherCAT ASIC always deliver the AL_Event register (0x220).
  *         It will be saved in the global "EscALEvent"
  * @param  None
  * @retval None
  */
#if !INTERRUPTS_SUPPORTED
#define ISR_GetInterruptRegister GetInterruptRegister
#else
static void ISR_GetInterruptRegister(void)
{
		HW_EscReadIsr((MEM_ADDR*)EscALEvent.Byte, ESC_AL_EVENT_OFFSET, 2);
}
#endif //#else #if !INTERRUPTS_SUPPORTED

/* EXPORTED SUBPROGRAM BODIES */

/**
  * @brief  This function intialize the Process Data Interface (PDI) and the host controller.
  * @param  None
  * @retval 0 if initialization was successful
  */
UINT8 HW_Init(void)
{
#if (ETHERCAT_SLAVE_STACK_ENABLE)
	UINT32            intMask;
#endif
	GPIO_InitTypeDef  GPIO_InitStructure;
	UINT16            tmp16;
	
	//__HAL_RCC_SYSCFG_CLK_ENABLE();
	
#if AX58100_DEBUG_ENABLE
	memset(&HW_Debug, 0, sizeof(HW_Debug));		
#endif	
	/* Initialize PDIs */
	// Local bus initialized in cubemx

	/* Enable Indicator GPIOs */



	/* Enable time tick peripheral */
	//TimeTick_Handle.Instance = HW_TIMETICK_INSTANCE;
	//HAL_TIM_Base_Start(&TimeTick_Handle);
	// initialized in cubemx
	/* Enable time tick peripheral */
	TimeTick_Handle = HW_TIMETICK_HANDLE;
	HW_TIM_ClkSource(TimeTick_Handle.Instance, ENABLE);
	TimeTick_Handle.Init.Prescaler = HW_TIMETICK_PRESCALER;
	TimeTick_Handle.Init.CounterMode = TIM_COUNTERMODE_UP;
	TimeTick_Handle.Init.Period = HW_TIMETICK_PRELOAD;
	TimeTick_Handle.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	TimeTick_Handle.Init.RepetitionCounter = 0;
	TimeTick_Handle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	HAL_TIM_Base_Init(&TimeTick_Handle);
	/* Start time tick */	
	HAL_TIM_Base_Start(&TimeTick_Handle);

	
	
	/* Enable EEPROM done GPIO */
	// eepdone gpio initialized in cubemx

#if (ETHERCAT_SLAVE_STACK_ENABLE)	
	/* Wait ESC ready by checking EEPDONE pin goes high */
	tmp16 = HW_GetTimer();
	/*//not applicable
	

	do
	{
		if (HW_CheckTimeout(tmp16, HW_EEPROM_RELOAD_TIMEOUT))
		{
			return 1;
		}
	} while (HAL_GPIO_ReadPin(HW_EEPROM_PORT, HW_EEPROM_PIN) == GPIO_PIN_RESET);
	*/
	do
	{
		;// wait for eeprom done
	} while(!HW_CheckTimeout(tmp16, 100));// wait 100ms

	do
	{
		intMask = 0x93;
		HW_EscWriteDWord(intMask, ESC_AL_EVENTMASK_OFFSET);
		intMask = 0;
		HW_EscReadDWord(intMask, ESC_AL_EVENTMASK_OFFSET);
		printf("esc read intMask=0x%x\r\n", intMask);
	} while (intMask != 0x93);
	intMask = 0x00;
	HW_EscWriteDWord(intMask, ESC_AL_EVENTMASK_OFFSET);
	
	/* Check Chip ID */
	if (HW_CheckVendorProductID() < 0)
	{
		return 2;
	}
#endif
	
	/* Enable interrupt */
	memset(&Intr, 0, sizeof(Intr));
	
#if AL_EVENT_ENABLED
	/* Enable ESC interrupt */	
	ENABLE_ESC_INT();
#endif	

#if DC_SUPPORTED
	/* Enable SYNC0 GPIO */
	//done in cubemx 

	/* Enable SYNC0 interrupt source at NVIC */	
	//done in cubemx

	/* Enable SYNC1 GPIO */
	// done in cubemx

	/* Enable SYNC1 interrupt source at NVIC */
	//done in cubemx

	HAL_NVIC_EnableIRQ(HW_SYNC1_IRQ);

	/* Enable SYNC0/SYNC1 interrupt */
	ENABLE_SYNC0_INT;
	ENABLE_SYNC1_INT;
#endif
	
#if ECAT_TIMER_INT
	/* Enable time task peripheral */
	//TimeTask_Handle.Instance = HW_TIMETASK_INSTANCE;
	TimeTask_Handle = HW_TIMETASK_HANDLE;
	// done in cubemx

	/* Enable timer interrupt source at NVIC */
	// done in cubemx
	
	/* Start timer with interrupt */
	HAL_TIM_Base_Start_IT(&TimeTask_Handle);
	
#endif

//#if (!ETHERCAT_SLAVE_STACK_ENABLE)
//	MISC_BridgeOverride(1);
//	MISC_SpiMasterOverride(1);
//	MISC_MotorControlOverride(1);
//#endif	

//#ifdef AX58100_ALWAYS_USE_FUN_PDI
//	BRG_AllModulesEscAccess(0);
//#else	
//	BRG_AllModulesEscAccess(1);
//#endif	

#if INTERRUPTS_SUPPORTED
	/* Clear all pended interrupts */
//	tmp16 = 0xFFFF;
//	MISC_CLR_INTR_STATUS(&tmp16);

	/* enable all interrupts */
	ENABLE_GLOBAL_INT;
#endif
	
	return 0;
}

/**
  * @brief  This function shall be implemented if hardware resources need to be release
  *         when the sample application stops.
  * @param  None
  * @retval None
  */
void HW_Release(void)
{

}



#if UC_SET_ECAT_LED
/**
  * @brief  This function updates the EtherCAT run and error led.
  * @param  RunLed  desired EtherCAT Run led state
  * @param  ErrLed  desired EtherCAT Error led state
  * @retval None
  */
void HW_SetLed(UINT8 RunLed,UINT8 ErrLed)
{
	
}
#endif //#if UC_SET_ECAT_LED

/**
  * @brief  This function operates the SPI read access by Function chip select
  * @param  pData     Pointer to a byte array which holds data to write or saves read data.
  * @param  Address   Function register address.
  * @param  Len       Access size in Bytes.
  * @retval None
  */
void HW_FunRead( MEM_ADDR *pData, UINT16 Address, UINT16 Len )
{
#if AL_EVENT_ENABLED
		DISABLE_AL_EVENT_INT;
#endif		
		
		//HW_SPI_Read(&HW_SpiObj[HW_FUN_PDI], (UINT8*)pData, Address, Len);
		
#if AL_EVENT_ENABLED
		ENABLE_AL_EVENT_INT;
#endif
}

/**
  * @brief  This function operates the SPI write access by Function chip select.
  * @param  pData       Pointer to a byte array which holds data to write or saves write data.
  * @param  Address     Function register address.
  * @param  Len         Access size in Bytes.
  * @retval None
  */
void HW_FunWrite( MEM_ADDR *pData, UINT16 Address, UINT16 Len )
{
#if AL_EVENT_ENABLED
		DISABLE_AL_EVENT_INT;
#endif
		
		//HW_SPI_Write(&HW_SpiObj[HW_FUN_PDI], (UINT8*)pData, Address, Len);

#if AL_EVENT_ENABLED
		ENABLE_AL_EVENT_INT;
#endif
}

#if BOOTSTRAPMODE_SUPPORTED
/**
  * @brief  This function resets the hardware
  * @param  None
  * @retval None
  */
void HW_RestartTarget(void)
{
}
#endif

#if ESC_EEPROM_EMULATION
/**
  * @brief  This function is called when the master has request an EEPROM reload during EEPROM emulation
  * @param  None
  * @retval 0 if reload was successful
  */
UINT16 HW_EepromReload (void)
{
    return 0;
}
#endif

#if (AL_EVENT_ENABLED || DC_SUPPORTED)
/**
  * @brief  Interrupt service routine for AL/SYNC0/SYNC1
  * @param  None
  * @retval None
  */
void HW_ALEVENT_SYNC0_SYNC1_IRQHandler(void)
{
#if DC_SUPPORTED
	

	if (__HAL_GPIO_EXTI_GET_FLAG(HW_SYNC0_PIN))
	{
		__HAL_GPIO_EXTI_CLEAR_FLAG(HW_SYNC0_PIN);
		
		HW_IntrEnqueue(INTR_SYNC0);
#if AX58100_DEBUG_ENABLE	
		HW_Debug.Sync0IsrCnt++;
#endif			
	}
	
	if (__HAL_GPIO_EXTI_GET_FLAG(HW_SYNC1_PIN))
	{
		__HAL_GPIO_EXTI_CLEAR_FLAG(HW_SYNC1_PIN);
		HW_IntrEnqueue(INTR_SYNC1);
#if AX58100_DEBUG_ENABLE	
		HW_Debug.Sync1IsrCnt++;
#endif			
	}
#endif
	
	if (__HAL_GPIO_EXTI_GET_FLAG(HW_SPI_ESC_INT_PIN))
	{	
		__HAL_GPIO_EXTI_CLEAR_FLAG(HW_SPI_ESC_INT_PIN);
		HW_IntrEnqueue(INTR_ESC);
#if AX58100_DEBUG_ENABLE
		HW_Debug.EscIsrCnt ++;
#endif		
	}
	
} /* End of HW_ALEVENT_SYNC0_SYNC1_IRQHandler() */
#endif

#if ECAT_TIMER_INT
/**
  * @brief  Interrupt service routine for the Timer
  * @param  None
  * @retval None
  */
void HW_TIMETASK_IRQHandler(void)
{
// called by timer9 callback function
#if AX58100_DEBUG_ENABLE		
		HW_Debug.TmrTskIsrCnt ++;
#endif		
		HW_IntrEnqueue(INTR_TIMETASK);
		//CONSOLE_TimeTick();
		//TEST_Timer(0);
	
} /* End of HW_TIMETASK_IRQHandler() */
#endif

/*
 * ----------------------------------------------------------------------------
 * Function Name: HW_IntrEnqueue
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void HW_IntrEnqueue(INTR_TYPE IntrType)
{
	Intr.Queue[Intr.EnQueuePtr] = IntrType;
	Intr.EnQueuePtr++;	
	if (Intr.EnQueuePtr >= HW_MAX_INTR_QUEUE)
	{
		Intr.EnQueuePtr = 0;
	}
} /* End of HW_IntrEnqueue() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: HW_IntrDequeue
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void HW_IntrDequeue(void)
{
	if (Intr.DeQueuePtr != Intr.EnQueuePtr)
	{
		if (Intr.Queue[Intr.DeQueuePtr] == INTR_TIMETASK)
		{
			ECAT_CheckTimer();
		}
		else if (Intr.Queue[Intr.DeQueuePtr] == INTR_SYNC0)
		{
			Sync0_Isr();
		}
		else if (Intr.Queue[Intr.DeQueuePtr] == INTR_SYNC1)
		{
			Sync1_Isr();
		}
		else if (Intr.Queue[Intr.DeQueuePtr] == INTR_ESC)
		{
			PDI_Isr();
		}
		
		Intr.DeQueuePtr++;
		if (Intr.DeQueuePtr >= HW_MAX_INTR_QUEUE)
		{
			Intr.DeQueuePtr = 0;
		}
	}
} /* End of HW_IntrDequeue() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: HW_CheckTimeout
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
UINT8 HW_CheckTimeout(UINT16 StartTime, UINT16 Timeout)
{
	u16 tmp16 = HW_GetTimer();
	
	if (tmp16 < StartTime)
	{
		tmp16 = (HW_TIMETICK_MAX_VALUE - StartTime) + tmp16;
	}
	else
	{
		tmp16 = tmp16 - StartTime;		
	}

	return ((tmp16 >= Timeout) ? 1:0);
}/* End of HW_CheckTimeout() */

#if (ETHERCAT_SLAVE_STACK_ENABLE)
/*
 * ----------------------------------------------------------------------------
 * Function Name: HW_CheckVendorProductID
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
INT32 HW_CheckVendorProductID(void)
{
	oIC_VENDOR_ID    vendor_id;	
	oIC_PRODUCT_ID   product_id;
	
	AX_INTF_EscRead(IC_VENDOR_ID, vendor_id.d32, sizeof(oIC_VENDOR_ID));
	printf("esc read vendor_id=0x%x\r\n", vendor_id.b.vendor_id);

	if (vendor_id.b.vendor_id != AX58100_VENDOR_ID)
	{
		return -1;
	}
	
	AX_INTF_EscRead(IC_PRODUCT_ID, product_id.d32, sizeof(oIC_PRODUCT_ID));	
	printf("esc read chip_revision=0x%x\r\n", product_id.b.chip_revision);
	printf("esc read product_id=0x%x\r\n", product_id.b.product_id);
	if (product_id.b.chip_revision != AX58100_CHIP_REVISION)
	{
		return -2;
	}
	
	if (product_id.b.product_id != AX58100_PRODUCT_ID)
	{
		return -3;
	}
	
	return 0;
} /* End of HW_CheckVendorProductID() */
#endif

#if AX58100_DEBUG_ENABLE
HW_DEBUG* HW_GetDebugCounter(void)
{
	return (&HW_Debug);
}
#endif

/* End of samplehw.c */

