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
#ifndef __AX58100_ENC_H__
#define __AX58100_ENC_H__

/* INCLUDE FILE DECLARATIONS */
#include "ax58100_regobjs.h"

/* NAMING CONSTANT DECLARATIONS */
typedef enum
{
	ENC_ABZ_RATIO_4X = 1,	
	ENC_ABZ_RATIO_2X,
	ENC_ABZ_RATIO_3X,
} ENC_ABZ_RATIO;

typedef enum
{
	ENC_NO_CLR_EVENT = 0,	
	ENC_GEN_CLR_AT_IZ_ASSERT,		
	ENC_GEN_CLR_AT_IZ_DEASSERT,
	ENC_GEN_CLR_AT_BOTH,	
} ENC_CLR_EVENT_AT_IZ_EDGE;

/* TYPE DECLARATIONS */
typedef struct _ENC_ABZ_OBJECT
{
	u8                              A_InputPolarityPositive;
	u8                              B_InputPolarityPositive;	
	u8                              Z_InputPolarityPositive;
	u8                              IgnoreAB_Inputs;
	ENC_ABZ_RATIO                   Ratio;	
	ENC_CLR_EVENT_AT_IZ_EDGE        ClearEventGeneratedEdge;
	u8                              EnableDecimalMode;
	u16                             ConstantFractional;	
	u16                             ConstantInteger;
} ENC_ABZ_OBJECT;

typedef struct _ENC_CWCCW_OBJECT
{
	u8                              EnableDecimalMode;
	u16                             ConstantFractional;	
	u16                             ConstantInteger;
} ENC_CWCCW_OBJECT;

typedef struct _ENC_CLKDIR_OBJECT
{
	u8                              EnableDecimalMode;
	u16                             ConstantFractional;	
	u16                             ConstantInteger;
} ENC_CLKDIR_OBJECT;

/* GLOBAL VARIABLES */

/* EXPORTED SUBPROGRAM SPECIFICATIONS */
AX_STATUS ENC_ABZ_Init(ENC_ABZ_OBJECT *pAbzObj);
void      ENC_ABZ_DeInit(void);

AX_STATUS ENC_CWCCW_Init(ENC_CWCCW_OBJECT *pCwccwObj);
void      ENC_CWCCW_DeInit(void);

AX_STATUS ENC_CLKDIR_Init(ENC_CLKDIR_OBJECT *pClkDirObj);
void      ENC_CLKDIR_DeInit(void);

u32       ENC_GetLatchedValue(void);
u32       ENC_GetCounter(void);
void      ENC_ClearCounter(void);

void      ENC_HAll_Init(void);
void      ENC_HAll_DeInit(void);
void      ENC_HAll_GetStatus(u8 *pCurrStatus, u8 *pKeepStatus, u8 *pOverrun);
u32       ENC_HAll_GetPhaseDuration(void);
void      ENC_HAll_ClearOverrun(void);

#endif /* __AX58100_ENC_H__ */

/* End of ax58100_enc.h */
