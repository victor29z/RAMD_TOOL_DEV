/*
 ******************************************************************************
 *     Copyright (c) 2016	ASIX Electronic Corporation      All rights reserved.
 *
 *     This is unpublished proprietary source code of ASIX Electronic Corporation
 *
 *     The copyright notice above does not evidence any actual or intended
 *     publication of such source code.
 ******************************************************************************
 */
#ifndef __TEST_H__
#define __TEST_H__

/* INCLUDE FILE DECLARATIONS */
#include "ax_types.h"
#include "ax58100_spim.h"
#include "ax58100_enc.h"

/* NAMING CONSTANT DECLARATIONS */
#define TEST_SEC_TICK_COUNT			1000
#define TEST_INIT_DATA_BUF_SIZE	128
#define TEST_TX_BUF_SIZE				1024
#define TEST_RX_BUF_SIZE				TEST_TX_BUF_SIZE

#define DBG_TriggerOutput(x)
	
	/* Default value */
#define TEST_DEF_LOOP_COUNT							0
#define TEST_DEF_START_RAMADDR					0x1000
#define TEST_DEF_RAM_SIZE								0x0FFF
#define TEST_DEF_PATTERN_TYPE						TEST_PATTERN_RANDOM
#define TEST_DEF_LOG_UPDATE_TIME				500

#define TEST_DEF_SPI_DATA_SIZE_IN_WR		TEST_SPI_DATA_SIZE_AUTO
#define TEST_DEF_SPI_DATA_SIZE_IN_RD		TEST_SPI_4BYTE_DATA
#define TEST_DEF_SPI_WRITE_DUMMY_CYCLES	0
#define TEST_DEF_SPI_ADDR_SIZE					TEST_SPI_ADDR_SIZE_AUTO

#define TEST_AUTO_CHANGE_CONDITION   		0xff
#define TEST_MAX_RANDOM_COUNT           5


/* TYPE DECLARATIONS */
typedef enum{
	TEST_IDLE = 0,
	TEST_ROUND_START,
	TEST_BUSY,	
	TEST_RUN,
	TEST_RUN_WAIT,
	TEST_CHANGE_CONDITION,
	TEST_ROUND_DONE,
	TEST_EXIT,
	TEST_ERROR,	
	TEST_DONE,
} TEST_STATE;

typedef enum{
	TEST_PATTERN_FIXED = 0,
	TEST_PATTERN_INCREMENT,
	TEST_PATTERN_DECREMENT,	
	TEST_PATTERN_RANDOM,
	TEST_MAX_PATTERN_TYPE,	
} TEST_PATTERN_TYPE;

typedef enum
{
	TEST_SPI_DATA_SIZE_AUTO = 0,
	TEST_SPI_1BYTE_DATA     = 1,
	TEST_SPI_2BYTE_DATA     = 2,
	TEST_SPI_4BYTE_DATA     = 4,	
} TEST_SPI_DATA_SIZE_TYPE;

typedef enum
{
	TEST_SPI_ADDR_SIZE_AUTO = 0,	
	TEST_SPI_2BYTE_ADDR     = 2,
	TEST_SPI_3BYTE_ADDR     = 3,
} TEST_SPI_ADDR_SIZE_TYPE;

typedef struct{
  TEST_SPI_DATA_SIZE_TYPE  DataSizeInWrite;
  TEST_SPI_DATA_SIZE_TYPE  DataSizeInRead;	
  TEST_SPI_ADDR_SIZE_TYPE  AddrSize;		
} TEST_SPIS_PARAMETER;

typedef struct{
	u32	LoopCount;
	u32	LogUpdateTime;
	u32 InterRoundDelay;
	u32	Prescaler;
	u8  ChipSelectMode;
	u8  MonitorModeEnable;
	u32 TransferTimeout;
	
	/* PDI memory test parameters */
	u32 StartAddress;
	u32 EndAddress;	
	u32 PatternType;
	u32 Range;
	u8	InitData[TEST_INIT_DATA_BUF_SIZE];	
	u32	InitDataLen;
	
	/* 446 TIMER */
	u16	TimerPrescaler;	
	
	TEST_SPIS_PARAMETER	Spis;

} TEST_PARAMETER;

typedef struct{
	u32 Second;
	u32 Minute;
	u32 Hour;
	u32 Day;
	u32 RunFlag;
	u32 TickCnt;	
} TEST_TIME;

typedef struct{
	u32 RoundCnt;
	u32 OkCnt;
	u32 ErrorCnt;
	u8  *pErrMsg;
	
} TEST_RECORD;

typedef struct{
	u32 DataSizeInWrite;
	u32 DataSizeInRead;	
	u32 AddrSizeInWrite;
	u32 AddrSizeInRead;
} TEST_SPIS_TEMP;

typedef struct{
	u32 Type;
	u8	Data[TEST_INIT_DATA_BUF_SIZE];	
	u32	DataLen;	
	u32	Seed;		
} TEST_PATTERN_TEMP;

typedef struct{
	/* General use */
	u32	CtrlFlags;	
	u32 TransferTimeout;		
	u8	HostInterfaceErrorStatus;	
	u32 Temp32;
	u32	RandomCaseCounter[TEST_MAX_RANDOM_COUNT];
	
	/* Memory test */	
	u8	TxBuf[TEST_TX_BUF_SIZE];
	u32	TxLen;	
	u8	RxBuf[TEST_RX_BUF_SIZE];
	u32	RxLen;
	u32	RemainLen;
	u32	AddrOffset;
	TEST_PATTERN_TEMP Pattern;
	
	/* SPI Slave test */	
	TEST_SPIS_TEMP Spis;


} TEST_TEMP;

typedef struct{
	u32							State;	
	u32							Terminated;
	TEST_RECORD			Record;
	TEST_PARAMETER	Parameter;
	TEST_TEMP				Temp;	
} TEST_CONTROL;

/* GLOBAL VARIABLES */

/* EXPORTED SUBPROGRAM SPECIFICATIONS */
void TEST_Init(void);

void TEST_Timer(void const *argument);
void TEST_ResetTime(void);
void TEST_CtrlTime(u8 start);
TEST_TIME* TEST_GetTime(void);

s32 TEST_PatternInit(TEST_PATTERN_TEMP *pPattern, u8 PatternType, u8 *pInitData, u32 InitDataLen);
s32 TEST_PatternGenerator(TEST_PATTERN_TEMP *pPattern, u8 *pBuf, u32 Len);

	/* Test Process Funcrions */
s16 TEST_PdiMemoryTest(TEST_CONTROL *pCtrl);

#endif /* __TEST_H__ */

/* End of test.h */
