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
#ifndef __AX_INTF_H__
#define __AX_INTF_H__

/* INCLUDE FILE DECLARATIONS */
#include "ax_cfg.h"
#include "samplehw.h"
#include "ax58100_misc.h"
#include "ax_esc_regs.h"
//#include "printd.h"

#ifdef AX58100_ENC_MODULE_ENABLED
#include "ax58100_enc.h"
#endif /* AX58100_ENC_MODULE_ENABLED */

#ifdef AX58100_IOWD_MODULE_ENABLED
#include "ax58100_iowd.h"
#endif /* AX58100_IOWD_MODULE_ENABLED */

#ifdef AX58100_PWM_MODULE_ENABLED
#include "ax58100_pwm.h"
#endif /* AX58100_PWM_MODULE_ENABLED */

#ifdef AX58100_SPIM_MODULE_ENABLED
#include "ax58100_spim.h"
#endif /* AX58100_SPIM_MODULE_ENABLED */

#ifdef AX58100_STEP_MODULE_ENABLED
#include "ax58100_step.h"
#endif /* AX58100_STEP_MODULE_ENABLED */

#ifdef AX58100_BRIDGE_MODULE_ENABLED
#include "ax58100_bridge.h"
#endif /* AX58100_BRIDGE_MODULE_ENABLED */

/* NAMING CONSTANT DECLARATIONS */
#define AX_INTF_FunRead(a,b,c)       HW_FunRead((MEM_ADDR*)b, (UINT16)a, (UINT16)c)
#define AX_INTF_FunWrite(a,b,c)      HW_FunWrite((MEM_ADDR*)b, (UINT16)a, (UINT16)c)
#define AX_INTF_EscRead(a,b,c)       HW_EscRead((MEM_ADDR*)b, (UINT16)a, (UINT16)c)
#define AX_INTF_EscWrite(a,b,c)      HW_EscWrite((MEM_ADDR*)b, (UINT16)a, (UINT16)c)
#ifdef AX58100_ALWAYS_USE_FUN_PDI
	#define AX_INTF_Read(a,b,c)        HW_FunRead((MEM_ADDR*)b, (UINT16)a, (UINT16)c)
	#define AX_INTF_Write(a,b,c)       HW_FunWrite((MEM_ADDR*)b, (UINT16)a, (UINT16)c)
#else
	#define AX_INTF_Read(a,b,c)        HW_EscRead((MEM_ADDR*)b, (UINT16)a, (UINT16)c)
	#define AX_INTF_Write(a,b,c)       HW_EscWrite((MEM_ADDR*)b, (UINT16)a, (UINT16)c)
#endif
#define AX_INTF_GetTime()            ((u16)(HW_TIMETICK_INSTANCE->CNT>>1))

/* TYPE DECLARATIONS */
	
/* GLOBAL VARIABLES */

/* EXPORTED SUBPROGRAM SPECIFICATIONS */
u8 AX_INTF_CheckTimeout(u16 StartTime, u16 Timeout);

#endif /* __AX_INTF_H__ */

/* End of ax_intf.h */
