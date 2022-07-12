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
#include "ax_intf.h"

#ifdef AX58100_IOWD_MODULE_ENABLED
#include "ax58100_iowd.h"

/* NAMING CONSTANT DECLARATIONS */

/* TYPE DECLARATIONS */

/* GLOBAL VARIABLES DECLARATIONS */

/* LOCAL VARIABLES DECLARATIONS */
static WCFGR_OBJECT wcfgr;

/* LOCAL SUBPROGRAM DECLARATIONS */

/* LOCAL SUBPROGRAM BODIES */

/* EXPORTED SUBPROGRAM BODIES */
/*
 * ----------------------------------------------------------------------------
 * Function Name: IOWDEM_Init
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
AX_STATUS IOWDEM_Init(IOWDEM_OBJECT *pIowdEmObj)
{
  if (pIowdEmObj == NULL)
  {
    return AX_STATUS_ERR;
  }
	
  IOWDEM_DeInit();
	
	/* Set monitor sources */
  AX_INTF_Read(WCFGR, &wcfgr.d16, 2);
  wcfgr.b.sof_detect_enable = ((pIowdEmObj->EnableSofInputMonitor == 0) ? 0:1);
  wcfgr.b.esc_cs_enable = ((pIowdEmObj->EnableEscCsInputMonitor == 0) ? 0:1);
  wcfgr.b.fun_cs_enable = ((pIowdEmObj->EnableFunCsInputMonitor == 0) ? 0:1);
  wcfgr.b.detect_input_rising = ((pIowdEmObj->DetectInputRisingEdge == 0) ? 0:1);
  wcfgr.b.watchdog_enable = 0;
  wcfgr.b.emergency_enable = 0;
  AX_INTF_Write(WCFGR, &wcfgr.d16, 2);
	
  /* Set monitor pattern mask */
  AX_INTF_Write(WMSMLR, &pIowdEmObj->InputMonitorMask, 4);
	
  /* Set monitor pattern polarity */
  AX_INTF_Write(WMSPLR, &pIowdEmObj->InputMonitorPolarity, 4);

  /* Set output mask */
  AX_INTF_Write(WMSOMLR, &pIowdEmObj->OutputActionMask, 4);

  /* Set output enable */	
  AX_INTF_Write(WMSOELR, &pIowdEmObj->OutputActionEnable, 4);

  /* Set output polarity */	
  AX_INTF_Write(WMSOPLR, &pIowdEmObj->OutputActionPolarity, 4);

  return AX_STATUS_OK;
} /* End of IOWDEM_Init() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: IOWDEM_DeInit
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void IOWDEM_DeInit(void)
{
	IOWD_Stop();
	EM_Stop();
} /* End of IOWDEM_DeInit() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: IOWD_Start
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void IOWD_Start(void)
{
	/* Enable function */
	AX_INTF_Read(WCFGR, &wcfgr.d16, 2);
	if (wcfgr.b.watchdog_enable == 0)
	{
		wcfgr.b.watchdog_enable = 1;
		AX_INTF_Write(WCFGR, &wcfgr.d16, 2);
	}
} /* End of IOWD_Start() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: IOWD_Stop
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void IOWD_Stop(void)
{
	/* Disable function */
	AX_INTF_Read(WCFGR, &wcfgr.d16, 2);
	if (wcfgr.b.watchdog_enable)
	{
		wcfgr.b.watchdog_enable = 0;
		AX_INTF_Write(WCFGR, &wcfgr.d16, 2);
	}
} /* End of IOWD_Stop() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: IOWD_SetTimeout
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void IOWD_SetTimeout(u32 Timeout)
{
	AX_INTF_Write(WTLR, &Timeout, 4);
} /* End of IOWD_SetTimeout() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: IOWD_GetTimerPeakValue
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
u32 IOWD_GetTimerPeakValue(void)
{
	u32 tmp32;
	AX_INTF_Read(WTPVLR, &tmp32, 4);	
	return tmp32;
} /* End of IOWD_GetTimerPeakValue() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: IOWD_ClearTimerPeakValue
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void IOWD_ClearTimerPeakValue(void)
{
	WTPVCR_OBJECT wtpcvr;

	wtpcvr.d16 = 0;
	wtpcvr.b.clear_peak_value = 1;
	AX_INTF_Write(WTPVCR, &wtpcvr, 2);	
	
	return;
} /* End of IOWD_ClearTimerPeakValue() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: IOWD_UnlockIO
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void IOWD_UnlockIO(void)
{
	u32 tmp32[2];
	
	/* Set maximum timeout value and avoid to trigger watchdog timeout */
	AX_INTF_Read(WTLR, &tmp32[0], 4);
	tmp32[1] = 0xffffffff;
	AX_INTF_Write(WTLR, &tmp32[1], 4);
	
	/* Follows the procedure as below to unlock I/Os */
	AX_INTF_Read(WCFGR, &wcfgr.d16, 2);
	wcfgr.b.watchdog_enable = 0;
	AX_INTF_Write(WCFGR, &wcfgr.d16, 2);
	wcfgr.b.watchdog_enable = 1;
	AX_INTF_Write(WCFGR, &wcfgr.d16, 2);
	wcfgr.b.watchdog_enable = 0;
	AX_INTF_Write(WCFGR, &wcfgr.d16, 2);

	/* Recovery timeout value as user setting */	
	AX_INTF_Write(WTLR, &tmp32[0], 4);
} /* End of IOWD_UnlockIO() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: EM_Start
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void EM_Start(void)
{
	/* Enable function */
	AX_INTF_Read(WCFGR, &wcfgr.d16, 2);
	if (wcfgr.b.emergency_enable == 0)
	{
		wcfgr.b.emergency_enable = 1;
		AX_INTF_Write(WCFGR, &wcfgr.d16, 2);
	}
	
} /* End of EM_Start() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: EM_Stop
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void EM_Stop(void)
{
	/* Disable function */
	AX_INTF_Read(WCFGR, &wcfgr.d16, 2);
	if (wcfgr.b.emergency_enable)
	{
		wcfgr.b.emergency_enable = 0;
		AX_INTF_Write(WCFGR, &wcfgr.d16, 2);
	}

} /* End of EM_Stop() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: EM_UnlockIO
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void EM_UnlockIO(void)
{
	/* Follows the procedure as below to unlock I/Os */
	AX_INTF_Read(WCFGR, &wcfgr.d16, 2);
	wcfgr.b.emergency_enable = 0;
	AX_INTF_Write(WCFGR, &wcfgr.d16, 2);
	wcfgr.b.emergency_enable = 1;
	AX_INTF_Write(WCFGR, &wcfgr.d16, 2);
	wcfgr.b.emergency_enable = 0;
	AX_INTF_Write(WCFGR, &wcfgr.d16, 2);

} /* End of EM_UnlockIO() */

#endif /* AX58100_IOWD_MODULE_ENABLED */

/* End of ax58100_iowd.c */
