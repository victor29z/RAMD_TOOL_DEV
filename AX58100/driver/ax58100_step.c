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

#ifdef AX58100_STEP_MODULE_ENABLED
#include "ax58100_step.h"

/* NAMING CONSTANT DECLARATIONS */

/* TYPE DECLARATIONS */

/* GLOBAL VARIABLES DECLARATIONS */

/* LOCAL VARIABLES DECLARATIONS */
static SCFGR_OBJECT scfgr;
static SCTRLR_OBJECT sctrlr;
static MCTLR_OBJECT mctlr;

/* LOCAL SUBPROGRAM DECLARATIONS */

/* LOCAL SUBPROGRAM BODIES */


/* EXPORTED SUBPROGRAM BODIES */
/*
 * ----------------------------------------------------------------------------
 * Function Name: STEP_Init
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
AX_STATUS STEP_Init(STEP_OBJECT *pStepObj)
{
	if (pStepObj == 0)
	{
		return AX_STATUS_ERR;
	}
	
	STEP_DeInit();
	
	/* Set gap time */
	AX_INTF_Write(SGTLR, &pStepObj->GapTime, 4);	
	
	/* Set high pulse width */
	AX_INTF_Write(SHPWR, &pStepObj->HighPulseWidth, 2);	

	/* Set direction transform delay */
	AX_INTF_Write(TDLYR, &pStepObj->DirXferDelay, 2);		
	
	/* Set step pulse and driection polarity */
	AX_INTF_Read(SCFGR, &scfgr.d16, 2);
	scfgr.b.step_pol_is_neg = ((pStepObj->StepPulsePolarityIsNegative == 0) ? 0:1);
	scfgr.b.dir_pol_is_neg = ((pStepObj->DirectionPolarityIsNegative == 0) ? 0:1);	
	AX_INTF_Write(SCFGR, &scfgr.d16, 2);	

	return AX_STATUS_OK;
} /* End of STEP_Init() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: STEP_DeInit
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void STEP_DeInit(void)
{
	/* Disable step outputs driving */
	AX_INTF_Read(SCTRLR, &sctrlr.d16, 2);		
	sctrlr.b.free_run_enable = 0;	/* Disable free run */
	sctrlr.b.step_output_enable = 0;
	sctrlr.b.dir_output_enable = 0;	
	AX_INTF_Write(SCTRLR, &sctrlr.d16, 2);	
	
	/* Disable step funtion */
	AX_INTF_Read(MCTLR, &mctlr.d16, 2);		
	mctlr.b.pwm_func_enable = 0;
	mctlr.b.step_func_enable = 0;
	AX_INTF_Write(MCTLR, &mctlr.d16, 2);
	
} /* End of STEP_DeInit() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: STEP_Start
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
AX_STATUS STEP_Start(s32 TargetStepNumber)
{
	/* Set target pulse number */
	AX_INTF_Write(STNLR, &TargetStepNumber, 4);

	/* Disable free run */
	AX_INTF_Read(SCTRLR, &sctrlr.d16, 2);		
	sctrlr.b.free_run_enable = 0;
	sctrlr.b.step_output_enable = 1;
	sctrlr.b.dir_output_enable = 1;
	sctrlr.b.clear_counter = 1;
	AX_INTF_Write(SCTRLR, &sctrlr.d16, 2);	

	/* Enable step funtion */
	AX_INTF_Read(MCTLR, &mctlr.d16, 2);
	mctlr.b.step_func_enable = 1;
	mctlr.b.pwm_func_enable = 0;//Auto disable PWM function while STEP is enabled.	
	AX_INTF_Write(MCTLR, &mctlr.d16, 2);
	
	return AX_STATUS_OK;
} /* End of STEP_Start() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: STEP_CheckCompleted
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
AX_STATUS STEP_CheckCompleted(void)
{
	s32 tmp32;
	
	AX_INTF_Read(STNLR, &tmp32, 4);
  tmp32 &= 0x7FFFFFFF;
	return ((STEP_GetStepCounter() == tmp32) ? AX_STATUS_OK:AX_STATUS_BUSY);	
} /* End of STEP_CheckCompleted() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: STEP_GetStepCounter
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
s32 STEP_GetStepCounter(void)
{
	s32 tmp32;
	
	AX_INTF_Read(SCNTLR, &tmp32, 4);
	return tmp32;
} /* End of STEP_GetStepCounter() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: STEP_ClearStepCounter
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void STEP_ClearStepCounter(void)
{
	AX_INTF_Read(SCTRLR, &sctrlr.d16, 2);		
	sctrlr.b.clear_counter = 1;
	AX_INTF_Write(SCTRLR, &sctrlr.d16, 2);		
} /* End of STEP_ClearStepCounter() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: STEP_StartFreeRun
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
AX_STATUS STEP_StartFreeRun(u8 direction)
{
	u32 tmp32 = 0;
	
	/* Enable free run */
	AX_INTF_Read(SCTRLR, &sctrlr.d16, 2);		
	sctrlr.b.free_run_enable = 1;
	sctrlr.b.step_output_enable = 1;
	sctrlr.b.dir_output_enable = 1;
	sctrlr.b.clear_counter = 1;
	AX_INTF_Write(SCTRLR, &sctrlr.d16, 2);	

	/* Set direction */
	tmp32 |= (direction == 0) ? 0x00000000:0x80000000;
	AX_INTF_Write(STNLR, &tmp32, 4);
	
	/* Enable step funtion */
	AX_INTF_Read(MCTLR, &mctlr.d16, 2);
	mctlr.b.step_func_enable = 1;
	mctlr.b.pwm_func_enable = 0;//Auto disable PWM function while STEP is enabled.	
	AX_INTF_Write(MCTLR, &mctlr.d16, 2);
	
	return AX_STATUS_OK;
} /* End of STEP_StartFreeRun() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: STEP_StopFreeRun
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
AX_STATUS STEP_StopFreeRun(void)
{
	/* Disable step funtion */
	AX_INTF_Read(MCTLR, &mctlr.d16, 2);
	mctlr.b.step_func_enable = 0;
	mctlr.b.pwm_func_enable = 0;
	AX_INTF_Write(MCTLR, &mctlr.d16, 2);
	
	/* Disable free run */
	AX_INTF_Read(SCTRLR, &sctrlr.d16, 2);		
	sctrlr.b.free_run_enable = 0;
	sctrlr.b.step_output_enable = 0;
	sctrlr.b.dir_output_enable = 0;
	AX_INTF_Write(SCTRLR, &sctrlr.d16, 2);	
	
	return AX_STATUS_OK;
} /* End of STEP_StopFreeRun() */

#endif /* AX58100_STEP_MODULE_ENABLED */

/* End of ax58100_step.c */
