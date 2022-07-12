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

#ifdef AX58100_ENC_MODULE_ENABLED
#include "ax58100_enc.h"

/* NAMING CONSTANT DECLARATIONS */

/* TYPE DECLARATIONS */

/* GLOBAL VARIABLES DECLARATIONS */

/* LOCAL VARIABLES DECLARATIONS */
static EMOD_OBJECT     emod;
static ECLR_OBJECT     eclr;
static HALLST_OBJECT   hallst;

/* LOCAL SUBPROGRAM DECLARATIONS */
static AX_STATUS ENC_SetCountValue(u32 CountValue);

/* LOCAL SUBPROGRAM BODIES */
/*
 * ----------------------------------------------------------------------------
 * Function Name: ENC_SetCountValue
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
static AX_STATUS ENC_SetCountValue(u32 CountValue)
{
	ACCESSCTRL_OBJECT acr;
	
	if (AX58100_REGS_WR_BASE == AX58100_ESC_WR_REGS_ADDR &&
	    AX58100_REGS_RD_BASE == AX58100_ESC_RD_REGS_ADDR)
	{
		AX_INTF_EscRead(ECNTVACR, &acr.d8, 1);
		acr.b.is_writable_with_esc = 1;
		AX_INTF_EscWrite(ECNTVACR, &acr.d8, 1);
	}
	
	AX_INTF_Write(ECNTVL, &CountValue, 4);
	
  if (AX58100_REGS_WR_BASE == AX58100_ESC_WR_REGS_ADDR &&
      AX58100_REGS_RD_BASE == AX58100_ESC_RD_REGS_ADDR)
	{	
		acr.b.is_writable_with_esc = 0;
		AX_INTF_EscWrite(ECNTVACR, &acr.d8, 1);	
	}

	return AX_STATUS_OK;
} /* End of ENC_SetCountValue() */

/* EXPORTED SUBPROGRAM BODIES */

/*
 * ----------------------------------------------------------------------------
 * Function Name: ENC_ABZ_Init
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
AX_STATUS ENC_ABZ_Init(ENC_ABZ_OBJECT *pAbzObj)
{
	u16 tmp16[2];
	
	if (pAbzObj == 0)
	{
		return AX_STATUS_ERR;
	}
	
	eclr.d16 = 0;
	eclr.b.latch_value_before_clr = 1;
	if (pAbzObj->ClearEventGeneratedEdge != ENC_NO_CLR_EVENT)
	{
		eclr.b.clr_value_every_event = 1;
	}
	
	/* Clear counter value at initial stage */
	eclr.b.clr_value_directly = 1;
	AX_INTF_Write(ECLR, &eclr.d16, 2);

	/* Set constant value */
	tmp16[0] = pAbzObj->ConstantInteger;	
	tmp16[1] = pAbzObj->ConstantFractional;
	AX_INTF_Write(ECNSTL, tmp16, 4);
	
	/* Set Z event trigger conditions */
	emod.d16 = 0;
	emod.b.a_pol_to_gen_iz = ((pAbzObj->A_InputPolarityPositive == 0) ? 0:1);
	emod.b.b_pol_to_gen_iz = ((pAbzObj->B_InputPolarityPositive == 0) ? 0:1);
	emod.b.ignore_ab_to_gen_iz = ((pAbzObj->Z_InputPolarityPositive == 0) ? 0:1);
	emod.b.z_pol_to_gen_iz = ((pAbzObj->IgnoreAB_Inputs == 0) ? 0:1);
	switch (pAbzObj->ClearEventGeneratedEdge)
	{
	default:
	case ENC_NO_CLR_EVENT:
		emod.b.trg_event_at_iz_assert = 0;
		emod.b.trg_event_at_iz_deassert = 0;	
		break;
	case ENC_GEN_CLR_AT_IZ_ASSERT:
		emod.b.trg_event_at_iz_assert = 1;
		emod.b.trg_event_at_iz_deassert = 0;			
		break;
	case ENC_GEN_CLR_AT_IZ_DEASSERT:
		emod.b.trg_event_at_iz_assert = 0;
		emod.b.trg_event_at_iz_deassert = 1;			
		break;
	case ENC_GEN_CLR_AT_BOTH:
		emod.b.trg_event_at_iz_assert = 1;
		emod.b.trg_event_at_iz_deassert = 1;			
		break;	
	}
	
	emod.b.encoder_decimal = ((pAbzObj->EnableDecimalMode == 0) ? 0:1);
	
	/* Set ratio to be X1 */
	emod.b.encoder_ratio = (pAbzObj->Ratio & 0x03);
	
	/* Enable ABZ encoder mode */
	emod.b.encoder_mode = 0;
	
	/* Enable encoder function */	
	emod.b.enc_func_enable = 1;
	AX_INTF_Write(EMOD, &emod.d16, 2);
	
	return AX_STATUS_OK;
} /* End of ENC_ABZ_Init() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: ENC_ABZ_DeInit
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void ENC_ABZ_DeInit(void)
{
	/* Disable encoder function */
	AX_INTF_Read(EMOD, &emod.d16, 2);	
	emod.b.enc_func_enable = 0;
	AX_INTF_Write(EMOD, &emod.d16, 2);
	
} /* End of ENC_ABZ_DeInit() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: ENC_CWCCW_Init
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
AX_STATUS ENC_CWCCW_Init(ENC_CWCCW_OBJECT *pCwccwObj)
{
	u16 tmp16[2];
	
	if (pCwccwObj == 0)
	{
		return AX_STATUS_ERR;
	}
	
	eclr.d16 = 0;
	/* Enable counter value latch */	
	eclr.b.latch_value_before_clr = 1;
	
	/* Set counter clear conditions */
	eclr.b.clr_value_every_event = 1;
	
	/* Clear counter value at initial stage */	
	eclr.b.clr_value_directly = 1;
	AX_INTF_Write(ECLR, &eclr.d16, 2);

	/* Set constant value */
	tmp16[0] = pCwccwObj->ConstantInteger;	
	tmp16[1] = pCwccwObj->ConstantFractional;
	AX_INTF_Write(ECNSTL, tmp16, 4);
	
	emod.d16 = 0;
	emod.b.trg_event_at_iz_assert = 1;
	emod.b.encoder_decimal = ((pCwccwObj->EnableDecimalMode == 0) ? 0:1);
	
	/* Enable CW/CCW encoder mode */	
	emod.b.encoder_mode = 2;
	
	/* Enable encoder module */	
	emod.b.enc_func_enable = 1;
	AX_INTF_Write(EMOD, &emod.d16, 2);
	
	return AX_STATUS_OK;
} /* End of ENC_CWCCW_Init() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: ENC_CWCCW_DeInit
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void ENC_CWCCW_DeInit(void)
{
	/* Disable encoder function */
	AX_INTF_Read(EMOD, &emod.d16, 2);	
	emod.b.enc_func_enable = 0;
	AX_INTF_Write(EMOD, &emod.d16, 2);
	
} /* End of ENC_CWCCW_DeInit() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: ENC_CLKDIR_Init
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
AX_STATUS ENC_CLKDIR_Init(ENC_CLKDIR_OBJECT *pClkDirObj)
{
	u16 tmp16[2];
	
	if (pClkDirObj == 0)
	{
		return AX_STATUS_ERR;
	}
	
	eclr.d16 = 0;
	/* Enable counter value latch */		
	eclr.b.latch_value_before_clr = 1;
	
	/* Set counter clear conditions */
	eclr.b.clr_value_every_event = 1;
	
	/* Clear counter value at initial stage */
	eclr.b.clr_value_directly = 1;
	AX_INTF_Write(ECLR, &eclr.d16, 2);

	/* Set constant value */
	tmp16[0] = pClkDirObj->ConstantInteger;	
	tmp16[1] = pClkDirObj->ConstantFractional;
	AX_INTF_Write(ECNSTL, tmp16, 4);
	
	emod.d16 = 0;
	emod.b.trg_event_at_iz_assert = 1;
	emod.b.encoder_decimal = ((pClkDirObj->EnableDecimalMode == 0) ? 0:1);
	
	/* Enable CLK/DIR encoder mode */		
	emod.b.encoder_mode = 3;
	
	/* Enable encoder module */	
	emod.b.enc_func_enable = 1;
	AX_INTF_Write(EMOD, &emod.d16, 2);
	
	return AX_STATUS_OK;
} /* End of ENC_CLKDIR_Init() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: ENC_CLKDIR_DeInit
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void ENC_CLKDIR_DeInit(void)
{
	/* Disable encoder function */
	AX_INTF_Read(EMOD, &emod.d16, 2);	
	emod.b.enc_func_enable = 0;
	AX_INTF_Write(EMOD, &emod.d16, 2);
	
} /* End of ENC_CLKDIR_DeInit() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: ENC_GetLatchedValue
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
u32 ENC_GetLatchedValue(void)
{
	u32 tmp32;
	
	AX_INTF_Read(ELATL, &tmp32, 4);	
	return (tmp32);
} /* End of ENC_GetLatchedValue() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: ENC_GetCounter
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
u32 ENC_GetCounter(void)
{
	u32 tmp32;
	
	AX_INTF_Read(ECNTVL, &tmp32, 4);	
	return (tmp32);
} /* End of ENC_GetCounter() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: ENC_ClearCounter
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void ENC_ClearCounter(void)
{
	AX_INTF_Read(ECLR, &eclr.d16, 2);
	eclr.b.clr_value_directly = 1;
	AX_INTF_Write(ECLR, &eclr.d16, 2);
} /* End of ENC_ClearCounter() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: ENC_HAll_Init
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void ENC_HAll_Init(void)
{
	u32 tmp32;
	
	eclr.d16 = 0;
	/* Enable counter value latch */		
	eclr.b.latch_value_before_clr = 1;
	
	/* Set counter clear conditions */
	eclr.b.clr_value_every_event = 1;
	
	/* Clear counter value at initial stage */	
	eclr.b.clr_value_directly = 1;
	AX_INTF_Write(ECLR, &eclr.d16, 2);

	/* Set constant value */
	tmp32 = 0x00010000;	
	AX_INTF_Write(ECNSTL, &tmp32, 4);
	
	emod.d16 = 0;
	
	/* Enable HALL mode */	
	emod.b.hall_sensor_select = 1;
	
	/* Enable encoder function */
	emod.b.enc_func_enable = 1;
	emod.b.trg_event_at_iz_assert = 1;
	AX_INTF_Write(EMOD, &emod.d16, 2);
	
} /* End of ENC_HAll_Init() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: ENC_HAll_DeInit
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void ENC_HAll_DeInit(void)
{
	/* Disable encoder function */
	AX_INTF_Read(EMOD, &emod.d16, 2);	
	emod.b.enc_func_enable = 0;
	AX_INTF_Write(EMOD, &emod.d16, 2);
	
} /* End of ENC_HAll_DeInit() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: ENC_HAll_GetStatus
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void ENC_HAll_GetStatus(u8 *pCurrStatus, u8 *pKeepStatus, u8 *pOverrun)
{
	AX_INTF_Read(HALLST, &hallst.d16, 2);
	
	if (pCurrStatus)
	{
		*pCurrStatus = hallst.d16 & ENC_CURR_STATUS_MASK;
	}
	if (pKeepStatus)
	{
		*pKeepStatus = hallst.d16 & ENC_KEEP_STATUS_MASK;
	}
	if (pOverrun)
	{
		*pOverrun = hallst.b.over_run;
	}
} /* End of ENC_HallMode_GetStatus() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: ENC_HAll_GetPhaseDuration
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
u32 ENC_HAll_GetPhaseDuration(void)
{
	u32 tmp32;
	
	AX_INTF_Read(ELATL, &tmp32, 4);	
	return (tmp32);
} /* End of ENC_HAll_GetPhaseDuration() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: ENC_HAll_ClearOverrun
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void ENC_HAll_ClearOverrun(void)
{
	AX_INTF_Read(ECLR, &eclr.d16, 2);
	eclr.b.clr_value_once_event = 0;
	eclr.b.clr_value_directly = 0;
	eclr.b.clr_hall_overrun = 1;
	AX_INTF_Write(ECLR, &eclr.d16, 2);
} /* End of ENC_HAll_ClearOverrun() */

#endif /* AX58100_ENC_MODULE_ENABLED */

/* End of ax58100_enc.c */
