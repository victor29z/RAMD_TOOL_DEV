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
#ifndef __SAMPLEHW_H__
#define __SAMPLEHW_H__

/* INCLUDE FILE DECLARATIONS */
#include <stdio.h>
#include "stm32f4xx_hal.h"
//#include "stm32f4xx_ll_exti.h"
#include "esc.h" 
#include "ax_intf.h" 
#include "BSP_UART.h"
/* NAMING CONSTANT DECLARATIONS */

	/* Interrupt, Sync0 and Syn1 */
#define HW_NVIC_PRIORITY_GROUP             NVIC_PRIORITYGROUP_4

#define HW_SYNC0_PORT                      GPIOC
#define HW_SYNC0_PIN                       GPIO_PIN_13
#define HW_SYNC0_IRQ                       EXTI15_10_IRQn
#define HW_SYNC0_NVIC_PREEMPTION_PRIORITY  0
#define HW_SYNC0_NVIC_SUB_PRIORITY         0

#define HW_SYNC1_PORT                      GPIOC
#define HW_SYNC1_PIN                       GPIO_PIN_14
#define HW_SYNC1_IRQ                       EXTI15_10_IRQn
#define HW_SYNC1_NVIC_PREEMPTION_PRIORITY  0  // need to be modified
#define HW_SYNC1_NVIC_SUB_PRIORITY         0	// need to be modified

	/* Timer for tick or delay function use */
#define HW_TIMETICK_CLOCK                  84000000	//72000000
#define HW_TIMETICK_COUNTING_RATE          1000000
#define HW_TIMETICK_PRELOAD                0xFFFFU
#define HW_TIMETICK_PRESCALER              ((HW_TIMETICK_CLOCK/HW_TIMETICK_COUNTING_RATE)-1)
#define HW_TIMETICK_INSTANCE               TIM7
#define HW_TIMETICK_HANDLE                  htim7
#define HW_TIMETICK_MAX_VALUE              (HW_TIMETICK_PRELOAD>>1)

	/* Timer for periodic task execution */
#define HW_TIMETASK_CLOCK                  84000000
#define HW_TIMETASK_UPDATE_RATE            1000
#define HW_TIMETASK_PRESCALER              ((HW_TIMETASK_CLOCK/1000000)-1)
#define HW_TIMETASK_PRELOAD                (HW_TIMETASK_CLOCK/((HW_TIMETASK_PRESCALER+1)*HW_TIMETASK_UPDATE_RATE))
#define HW_TIMETASK_INSTANCE               TIM9
#define HW_TIMETASK_HANDLE                  htim9
//#define HW_TIMETASK_IRQHandler             TIM7_IRQHandler
#define HW_TIMETASK_IRQ                    
#define HW_TIMETASK_NVIC_PREEMPTION_PRIORITY  0//7
#define HW_TIMETASK_NVIC_SUB_PRIORITY         0// 1

	/* SPI PDI */
#define HW_SPI_MAX_DATA_FRAGMENT_SIZE      8
#define HW_SPI_MAX_ADDR_DUMMY_BYTES        4
#define HW_SPI_MAX_XFER_BUF_SIZE           (HW_SPI_MAX_ADDR_DUMMY_BYTES + HW_SPI_MAX_DATA_FRAGMENT_SIZE)
#define HW_SPI_XFER_TIMEOUT                10//ms
#define HW_MAX_DELAY                       0xFFFFFFFFU

	/* SPI PDI */
#define HW_SPI_ESC_INSTANCE                SPI1//SPI2
#define HW_SPI_ESC_GPIO_AF                 GPIO_AF5_SPI1//GPIO_AF5_SPI2

#define HW_SPI_ESC_CS_PORT                 GPIOA//GPIOB
#define HW_SPI_ESC_CS_PIN                  GPIO_PIN_4//GPIO_PIN_12

#define HW_SPI_FUN_CS_PORT                 GPIOC
#define HW_SPI_FUN_CS_PIN                  GPIO_PIN_2//GPIO_PIN_8

#define HW_SPI_ESC_SCLK_PORT               GPIOA//GPIOF
#define HW_SPI_ESC_SCLK_PIN                GPIO_PIN_5//GPIO_PIN_1

#define HW_SPI_ESC_MISO_PORT               GPIOA//GPIOB
#define HW_SPI_ESC_MISO_PIN                GPIO_PIN_6//GPIO_PIN_14

#define HW_SPI_ESC_MOSI_PORT               GPIOA//GPIOB
#define HW_SPI_ESC_MOSI_PIN                GPIO_PIN_7//GPIO_PIN_15

#define HW_SPI_ESC_INT_PORT                GPIOC
#define HW_SPI_ESC_INT_PIN                 GPIO_PIN_15//GPIO_PIN_6
#define HW_SPI_ESC_INT_IRQ                 EXTI15_10_IRQn//EXTI9_5_IRQn
#define HW_SPI_ESC_INT_NVIC_PREEMPTION_PRIORITY  0//7
#define HW_SPI_ESC_INT_NVIC_SUB_PRIORITY         0//	1
//#define HW_ALEVENT_SYNC0_SYNC1_IRQHandler  EXTI15_10_IRQHandler//EXTI9_5_IRQHandler

	/* Indicators */
#define HW_RUNLED_PORT                     GPIOD
#define HW_RUNLED_PIN                      GPIO_PIN_2

#define HW_ERRLED_PORT                     GPIOC
#define HW_ERRLED_PIN                      GPIO_PIN_9

	/* EEPROM done check pin */
#define HW_EEPROM_RELOAD_TIMEOUT           10000//unit in 1ms
#define HW_EEPROM_PORT                     //GPIOB	//not applicable
#define HW_EEPROM_PIN                      //GPIO_PIN_7	//not applicable

	/* SPI command definition */
#define HW_SPI_NOP_CMD                     0x00
#define HW_SPI_READ_CMD                    0x02
#define HW_SPI_READ_WITH_WAIT_CMD          0x03
#define HW_SPI_WRITE_CMD                   0x04
#define HW_SPI_ADDR_EXT_CMD                0x06
#define HW_SPI_CMD_MASK                    0x07

/* TYPE DECLARATIONS */

/* GLOBAL VARIABLES */

/* EXPORTED SUBPROGRAM SPECIFICATIONS */

/**
  * @brief  1000 ticks per ms
  */
#define ECAT_TIMER_INC_P_MS    1000

/**
  * @brief  Disable interrupt source INT1
  */
#ifndef DISABLE_ESC_INT
#define DISABLE_ESC_INT() NVIC_DisableIRQ(EXTI15_10_IRQn)
#endif

/**
  * @brief  ENABLE interrupt source INT1
  */
#ifndef ENABLE_ESC_INT
#define ENABLE_ESC_INT()  NVIC_EnableIRQ(EXTI15_10_IRQn)
#endif

/**
  * @brief  Access to the hardware timer
  */
#ifndef HW_GetTimer
#define HW_GetTimer()          ((UINT16)(HW_TIMETICK_INSTANCE->CNT>>1))
#endif

/**
  * @brief  Clear the hardware timer
  */
#ifndef HW_ClearTimer
#define HW_ClearTimer()        (HW_TIMETICK_INSTANCE->CNT = 0)
#endif

#define ET1100_PDI_BASEADDR  ((uint32_t)0x6c000000) /*Bank1_SRAM4_ADDR*/
#define ESC_MEM_ADDR    UINT16 /**< \brief ESC address type (16Bit)*/

/**
  * @brief  No interrupts are supported so the default Get AL Event register (0x220) function is used
  */
#if !INTERRUPTS_SUPPORTED
#define HW_GetALEventRegister_Isr HW_GetALEventRegister
#else
#define     HW_GetALEventRegister()             (*(volatile UINT16 ESCMEM *)(ET1100_PDI_BASEADDR+(ESC_AL_EVENT_OFFSET))) /**< \brief Returns the first 16Bit of the AL Event register (0x220)*/
#define     HW_GetALEventRegister_Isr           HW_GetALEventRegister /**< \brief Returns the first 16Bit of the AL Event register (0x220).<br>Called from ISRs.*/

#define     HW_EscRead(pData,Address,Len)  			ESCMEMCPY((MEM_ADDR *)(pData), (ESC_MEM_ADDR ESCMEM *)(ET1100_PDI_BASEADDR+((Address))), (Len)) /**< \brief Generic ESC (register and DPRAM) read access.*/

#define     HW_EscReadIsr                       HW_EscRead /**< \brief Generic ESC (register and DPRAM) read access.<br>Called for ISRs.*/
#define     HW_EscReadDWord(DWordValue, Address)    ((DWordValue) = (UINT32)(*(volatile UINT32 *)(ET1100_PDI_BASEADDR+(Address)))) /**< \brief 32Bit specific ESC (register and DPRAM) read access.*/
#define     HW_EscReadDWordIsr(DWordValue, Address) ((DWordValue) =(UINT32)(*(volatile UINT32 *)(ET1100_PDI_BASEADDR+(Address))))  /**< \brief 32Bit specific ESC (register and DPRAM) read access.<br>Called from ISRs.*/
#if !ESC_32BIT_ACCESS
#define     HW_EscReadWord(WordValue, Address)  ((WordValue) = (*(volatile UINT16 *)(ET1100_PDI_BASEADDR+(Address)))) /**< \brief 16Bit specific ESC (register and DPRAM) read access.*/
#define     HW_EscReadWordIsr(WordValue, Address) HW_EscReadWord(WordValue, Address) /**< \brief 16Bit specific ESC (register and DPRAM) read access.<br>Called from ISRs.*/
#if !ESC_16BIT_ACCESS
#define     HW_EscReadByte(ByteValue, Address)  ((ByteValue) = (*(volatile UINT8 *)(ET1100_PDI_BASEADDR+Address))) /**< \brief 8Bit specific ESC (register and DPRAM) read access.*/
#define     HW_EscReadByteIsr(ByteValue, Address) HW_EscReadByte(ByteValue, Address) /**< \brief 8Bit specific ESC (register and DPRAM) read access.<br>Called from ISRs.*/
#endif
#endif
#define     HW_EscReadMbxMem(pData,Address,Len) ESCMBXMEMCPY((MEM_ADDR *)(pData), (ESC_MEM_ADDR ESCMEM *)(ET1100_PDI_BASEADDR+((Address))), (Len)) /**< \brief Macro to copy data from the application mailbox memory(not the ESC memory, this access is handled by HW_EscRead).*/


#define     HW_EscWrite(pData,Address,Len)      ESCMEMCPY((ESC_MEM_ADDR ESCMEM *)(ET1100_PDI_BASEADDR+(Address)), (MEM_ADDR *)(pData), (Len)) /**< \brief Generic ESC (register and DPRAM) write access.*/
#define     HW_EscWriteIsr                      HW_EscWrite /**< \brief Generic ESC (register and DPRAM) write access.<br>Called for ISRs.*/
#define     HW_EscWriteDWord(DWordValue, Address)   ((*(volatile UINT32 *)(ET1100_PDI_BASEADDR+(Address))) = (DWordValue)) /**< \brief 32Bit specific ESC (register and DPRAM) write access.*/
#define     HW_EscWriteDWordIsr(DWordValue, Address)((*(volatile UINT32 *)(ET1100_PDI_BASEADDR+(Address)))= (DWordValue)) /**< \brief 32Bit specific ESC (register and DPRAM) write access.<br>Called from ISRs.*/
#if !ESC_32BIT_ACCESS
#define     HW_EscWriteWord(WordValue, Address) ((*(volatile UINT16 *)(ET1100_PDI_BASEADDR+(Address))) = (WordValue)) /**< \brief 16Bit specific ESC (register and DPRAM) write access.*/
#define     HW_EscWriteWordIsr(WordValue, Address) HW_EscWriteWord(WordValue, Address) /**< \brief 16Bit specific ESC (register and DPRAM) write access.<br>Called from ISRs.*/
#if !ESC_16BIT_ACCESS
#define     HW_EscWriteByte(ByteValue, Address) ((*(volatile UINT8 *)(ET1100_PDI_BASEADDR+Address)) = (ByteValue)) /**< \brief 8Bit specific ESC (register and DPRAM) write access.*/
#define     HW_EscWriteByteIsr(ByteValue, Address) HW_EscWriteByte(ByteValue, Address) /**< \brief 8Bit specific ESC (register and DPRAM) write access.<br>Called from ISRs.*/
#endif
#endif
#define     HW_EscWriteMbxMem(pData,Address,Len)    ESCMBXMEMCPY(((ESC_MEM_ADDR ESCMEM *)(ET1100_PDI_BASEADDR+((Address)))),(MEM_ADDR *)(pData), (Len)) /**< \brief Macro to copy data from the application mailbox memory (not the ESC memory, this access is handled by HW_EscWrite).*/


#ifndef TIMER_INT_HEADER
#define    TIMER_INT_HEADER /**< \brief Compiler directive before the hardware timer ISR function*/
#endif

#define     ESC_RD                    0x02 /**< \brief Indicates a read access to ESC or EEPROM*/
#define     ESC_WR                    0x04 /**< \brief Indicates a write access to ESC or EEPROM.*/

#endif //end of INTERRUPTS_SUPPORTED

#if __SAMPLEHW__
    #define PROTO
#else
    #define PROTO extern
#endif

PROTO UINT8 HW_Init(void);
PROTO void HW_Release(void);
// PROTO UINT16 HW_GetALEventRegister(void);

// #if INTERRUPTS_SUPPORTED
// PROTO UINT16 HW_GetALEventRegister_Isr(void);
// #endif //end of INTERRUPTS_SUPPORTED

#if UC_SET_ECAT_LED
PROTO void HW_SetLed(UINT8 RunLed,UINT8 ErrLed);
#endif //end of UC_SET_ECAT_LED

// PROTO void HW_EscRead( MEM_ADDR * pData, UINT16 Address, UINT16 Len );
// #if INTERRUPTS_SUPPORTED
// PROTO void HW_EscReadIsr( MEM_ADDR *pData, UINT16 Address, UINT16 Len );
// #endif

// PROTO void HW_EscWrite( MEM_ADDR *pData, UINT16 Address, UINT16 Len );

// #if INTERRUPTS_SUPPORTED
// PROTO void HW_EscWriteIsr( MEM_ADDR *pData, UINT16 Address, UINT16 Len );
// #endif

#if BOOTSTRAPMODE_SUPPORTED
PROTO void HW_RestartTarget(void);
#endif

#if ESC_EEPROM_EMULATION
PROTO UINT16 HW_EepromReload (void);
#endif

#if AL_EVENT_ENABLED
PROTO void HW_ESC_IRQHandler(void);
PROTO void HW_FUN_IRQHandler(void);

#define HW_MAX_INTR_QUEUE 100
typedef enum {
	INTR_ESC = 0,
	INTR_SYNC0,	
	INTR_SYNC1,	
	INTR_TIMETASK,	
} INTR_TYPE;

typedef struct{
	INTR_TYPE  Queue[HW_MAX_INTR_QUEUE];
	UINT32     EnQueuePtr;
	UINT32     DeQueuePtr;	
} INTR_QUEUE;
PROTO void HW_IntrEnqueue(INTR_TYPE IntrType);
PROTO void HW_IntrDequeue(void);
#endif

#if DC_SUPPORTED
PROTO void HW_SYNC0_IRQHandler(void);
PROTO void HW_SYNC1_IRQHandler(void);
#endif

PROTO void   HW_GPIO_ClkSource(GPIO_TypeDef* GpioPort, UINT8 NewState);
PROTO void   HW_TIM_ClkSource(TIM_TypeDef* Instance, UINT8 NewState);
PROTO void   HW_UART_ClkSource(USART_TypeDef* Instance, UINT8 NewState);

#undef PROTO

void HW_FunRead( MEM_ADDR *pData, UINT16 Address, UINT16 Len );
void HW_FunWrite( MEM_ADDR *pData, UINT16 Address, UINT16 Len );
UINT8 HW_CheckTimeout(UINT16 StartTime, UINT16 Timeout);
void HW_TIMETASK_IRQHandler(void);
#if (AX58100_DEBUG_ENABLE)
	#define ESC_DEBUG(f, ...)	{printf((const char*)f, ## __VA_ARGS__);}
#else
	#define ESC_DEBUG(f, ...)	{}
#endif

typedef enum {
	HW_FUN_PDI = 0,
	HW_ESC_PDI,
	HW_PDI_NUM,
} HW_PDI_TYPE;

#if AX58100_DEBUG_ENABLE
typedef struct{
  UINT32  EscIsrCnt;
  UINT32  FunIsrCnt;
  UINT32  Sync0IsrCnt;
  UINT32  Sync1IsrCnt;
  UINT32  AdcTrgCnt;	
  UINT32  TIM1IsrCnt;
  UINT32  EncIsrCnt;	
  UINT32  TmrTskIsrCnt;	
} HW_DEBUG;

HW_DEBUG* HW_GetDebugCounter(void);
void HW_TIMETASK_IRQHandler(void);
#define HW_Get500usTimer()          ((UINT16)HW_TIMETICK_INSTANCE->CNT)
#endif



#endif /* __SAMPLEHW_H__ */

/* End of samplehw.h */
