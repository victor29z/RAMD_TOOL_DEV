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
#ifndef __AX58100_IOWD_H__
#define __AX58100_IOWD_H__

/* INCLUDE FILE DECLARATIONS */
#include "ax58100_regobjs.h"

/* NAMING CONSTANT DECLARATIONS */

/* TYPE DECLARATIONS */
typedef struct _IOWDEM_OBJECT
{
	u32         InputMonitorMask;
	u32         InputMonitorPolarity;
	u32         OutputActionMask;
	u32         OutputActionEnable;
	u32         OutputActionPolarity;
	u8          EnableSofInputMonitor;
	u8          EnableEscCsInputMonitor;
	u8          EnableFunCsInputMonitor;
	u8          DetectInputRisingEdge;
} IOWDEM_OBJECT;

/* GLOBAL VARIABLES */

/* EXPORTED SUBPROGRAM SPECIFICATIONS */
AX_STATUS IOWDEM_Init(IOWDEM_OBJECT *pIowdEmObj);
void      IOWDEM_DeInit(void);

void      IOWD_Start(void);
void      IOWD_Stop(void);
void      IOWD_SetTimeout(u32 Timeout);
u32       IOWD_GetTimerPeakValue(void);
void      IOWD_ClearTimerPeakValue(void);
void      IOWD_UnlockIO(void);

void      EM_Start(void);
void      EM_Stop(void);
void      EM_UnlockIO(void);

#endif /* __AX58100_IOWD_H__ */

/* End of ax58100_iowd.h */
