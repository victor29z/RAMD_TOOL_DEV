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
#ifndef __AX58100_SPIM_H__
#define __AX58100_SPIM_H__

/* INCLUDE FILE DECLARATIONS */
#include "ax58100_regobjs.h"

/* NAMING CONSTANT DECLARATIONS */
#define SPIM_MAX_SLAVE_NUM             8
#define SPIM_MAX_CHANNEL_NUM           8
#define SPIM_MAX_BUF_SIZE_PER_CH       8
#define SPIM_CLK_SRC_FRQ               (100000000) //100MHz
#define SPIM_MAX_BAUDRATE              (SPIM_CLK_SRC_FRQ/0x02)
#define SPIM_MIN_BAUDRATE              (SPIM_CLK_SRC_FRQ/0xff)

	/* TYPE DECLARATIONS */
typedef enum 
{
	SPIM_STATE_DE_INITED = 0,
	SPIM_STATE_INITED,
	SPIM_STATE_BUSY,
	SPIM_STATE_READY,	
	SPIM_STATE_ERR,	
}SPIM_STATE;

typedef enum 
{
	SPIM_STATUS_OK = 0,
	SPIM_STATUS_ERR,
	SPIM_STATUS_TRG_PULSE_OVERRUN,	
	SPIM_STATUS_RX_BUF_OVERRUN,		
	SPIM_STATUS_TRG_PULSE_TIMEOUT,
	SPIM_STATUS_READY_PULSE_TIMEOUT,	
	SPIM_STATUS_COMPLETE_TIMEOUT,	
	SPIM_STATUS_SLAVE_SELECT_ERR,			
}SPIM_STATUS;

typedef enum 
{
	SCLK_MODE_0 = 0,
	SCLK_MODE_1,	
	SCLK_MODE_2,
	SCLK_MODE_3,
}SPIM_CLK_MODE;

typedef enum
{
	SPIM_PolarityActiveLow = 0,
	SPIM_PolarityActiveHigh,
}SPIM_POLARITY;

typedef enum
{
	SPIM_EnableSS_0 = 0x01,
	SPIM_EnableSS_1 = 0x02,
	SPIM_EnableSS_2 = 0x04,
	SPIM_EnableSS_3 = 0x08,
	SPIM_EnableSS_4 = 0x10,
	SPIM_EnableSS_5 = 0x20,
	SPIM_EnableSS_6 = 0x40,
	SPIM_EnableSS_7 = 0x80,
}SPIM_SLAVE_ENABLE;

typedef enum
{
	SPIM_SlaveId_0 = 0,
	SPIM_SlaveId_1,
	SPIM_SlaveId_2,
	SPIM_SlaveId_3,
	SPIM_SlaveId_4,
	SPIM_SlaveId_5,
	SPIM_SlaveId_6,
	SPIM_SlaveId_7,
}SPIM_SLAVE_ID;

typedef enum
{
	SPIM_Channel_0 = 0,
	SPIM_Channel_1,
	SPIM_Channel_2,
	SPIM_Channel_3,
	SPIM_Channel_4,
	SPIM_Channel_5,
	SPIM_Channel_6,
	SPIM_Channel_7,
}SPIM_CHANNELS;

typedef struct _SPIM_CFG_OBJECT
{
	/* Timing */
	SPIM_CLK_MODE ClkMode;
	u8  LsbXferFirst;	
	u8  LateSampleEnable;
	u32 Baudrate;
	u32 FirstClkDelay;
	u32 InterSlaveSelectDelay;
	u32 ReadyTrgPulseTimeout;	
	u32 LatchPulseGap;	
	u32 LatchPulseWidth;
	
	/* Polarity */
	SPIM_POLARITY TrgPulsePolarity;
	SPIM_POLARITY ReadyLatchPulsePolarity;
	SPIM_POLARITY InterruptPolarity;

	/* Operation mode */
	u8 InterruptModeEnable;
	u8 RxBufHandshakeEnable;
	u8 TrgPulseEnable;
	u8 ReadyOrLatchPulseEnable;	
	u8 DacModeEnable;
	u8 AutoKeepSlaveSelectEnable;
	u8 ContinueXferEnable;
	u8 ReadyCombinedWithMiso;
	u8 ExtDecoderEnable;
	
	/* Operation timeout */
	u32 TransferTimeout;
	
}SPIM_CFG_OBJECT;

typedef struct _SPIM_SLAVE_INFO
{
	u8 InUse;
	u16 TxBufAddr;
	u16 RxBufAddr;
	u8 TxLen;
	u8 RxLen;
	u8 RxStartByte;
	u8 StartChannel;
	u8 UsedChannels;
}SPIM_SLAVE_INFO;

typedef struct _SPIM_OBJECT
{
	SPIM_REGS            *SpimRegs;	
	SPIM_STATE           State;

	/* Slave allocations */	
	u8 SlaveNum;	
	SPIM_SLAVE_INFO      SlaveInfo[SPIM_MAX_SLAVE_NUM];

	/* Channels allocations */
	u8 CurrSlaveId;	
	u8 SlaveIdOfChannel[SPIM_MAX_CHANNEL_NUM];	
	u8 ChannelNumInUse;		
	SPIM_CFG_OBJECT Cfg;

}SPIM_OBJECT;

/* GLOBAL VARIABLES */

/* EXPORTED SUBPROGRAM SPECIFICATIONS */
AX_STATUS   SPIM_Init(SPIM_OBJECT *pSpimObj);
void        SPIM_DeInit(SPIM_OBJECT *pSpimObj);
AX_STATUS   SPIM_Config(SPIM_OBJECT *pSpimObj);
void        SPIM_SetRxStartByte(SPIM_OBJECT *pSpimObj, u8 StartByte);
void        SPIM_ClearInterrupt(void);
AX_STATUS   SPIM_OneShotStart(SPIM_OBJECT *pSpimObj);
AX_STATUS   SPIM_ContinueStart(SPIM_OBJECT *pSpimObj);
AX_STATUS   SPIM_ContinueStop(SPIM_OBJECT *pSpimObj);
void        SPIM_ReadyLatchPulseCtrl(SPIM_OBJECT *pSpimObj, u8 Enable);

/* For Multiple Slaves Transfer */
AX_STATUS   SPIM_ClearSlaveAllocation(SPIM_OBJECT *pSpimObj);
AX_STATUS   SPIM_SwitchSlave(SPIM_OBJECT *pSpimObj, SPIM_SLAVE_ID SlaveId);
s32         SPIM_WriteTxBuf(SPIM_OBJECT *pSpimObj, u8 *pData, u8 Len);
AX_STATUS   SPIM_Start(SPIM_OBJECT *pSpimObj);
AX_STATUS   SPIM_CheckComplete(SPIM_OBJECT *pSpimObj, u32 Timeout);
s32         SPIM_ReadRxBuf(SPIM_OBJECT *pSpimObj, u8 *pBuf, u8 Size);

/* For Signal Slave Transfer */
s32         SPIM_TransmitReceive(SPIM_OBJECT *pSpimObj, u8 *pData, u8 *pBuf, u32 Len);

#endif /* __AX58100_SPIM_H__ */

/* End of ax58100_spim.h */
