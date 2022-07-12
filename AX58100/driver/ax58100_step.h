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
#ifndef __AX58100_STEP_H__
#define __AX58100_STEP_H__

/* INCLUDE FILE DECLARATIONS */
#include "ax58100_regobjs.h"

/* NAMING CONSTANT DECLARATIONS */

/* TYPE DECLARATIONS */
typedef struct _STEP_OBJECT
{
	u32             GapTime;	
	u16             HighPulseWidth;
	u16             DirXferDelay;
	u8              DirectionPolarityIsNegative;
	u8              StepPulsePolarityIsNegative;
} STEP_OBJECT;

/* GLOBAL VARIABLES */

/* EXPORTED SUBPROGRAM SPECIFICATIONS */
AX_STATUS STEP_Init(STEP_OBJECT *pStepObj);
void      STEP_DeInit(void);
AX_STATUS STEP_Start(s32 TargetStepNumber);
AX_STATUS STEP_CheckCompleted(void);
void      STEP_ClearStepCounter(void);
s32       STEP_GetStepCounter(void);

AX_STATUS STEP_StartFreeRun(u8 direction);
AX_STATUS STEP_StopFreeRun(void);

#endif /* __AX58100_STEP_H__ */

/* End of ax58100_step.h */
