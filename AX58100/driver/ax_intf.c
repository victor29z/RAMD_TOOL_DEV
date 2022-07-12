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
#include <string.h>
#include "stm32f4xx_hal.h"
#include "ax_intf.h"

/* NAMING CONSTANT DECLARATIONS */

/* TYPE DECLARATIONS */

/* GLOBAL VARIABLES DECLARATIONS */

/* LOCAL VARIABLES DECLARATIONS */


/* LOCAL SUBPROGRAM DECLARATIONS */

/* LOCAL SUBPROGRAM BODIES */


/* EXPORTED SUBPROGRAM BODIES */
/*
 * ----------------------------------------------------------------------------
 * Function Name: AX_INTF_CheckTimeout
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
u8 AX_INTF_CheckTimeout(u16 StartTime, u16 Timeout)
{
	u16 tmp16 = AX_INTF_GetTime();
	
	if (tmp16 < StartTime)
	{
		tmp16 = (0x7FFFU - StartTime) + tmp16;
	}
	else
	{
		tmp16 = tmp16 - StartTime;		
	}

	return ((tmp16 >= Timeout) ? 1:0);
}/* End of AX_INTF_CheckTimeout() */

/* End of ax_intf.c */
