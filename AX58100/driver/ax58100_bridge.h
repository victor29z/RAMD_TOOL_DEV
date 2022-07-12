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
#ifndef __AX58100_BRIDGE_H__
#define __AX58100_BRIDGE_H__

/* INCLUDE FILE DECLARATIONS */
#include "ax58100_regobjs.h"

/* NAMING CONSTANT DECLARATIONS */
	
/* TYPE DECLARATIONS */

/* GLOBAL VARIABLES */

/* EXPORTED SUBPROGRAM SPECIFICATIONS */
void BRG_MotorControlEscAccess(u8 Enable);
void BRG_EncoderEscAccess(u8 Enable);
void BRG_EmIowdEscAccess(u8 Enable);
void BRG_SpiMasterEscAccess(u8 Enable);
void BRG_AllModulesEscAccess(u8 Enable);

#endif /* __AX58100_BRIDGE_H__ */

/* End of ax58100_bridge.h */
