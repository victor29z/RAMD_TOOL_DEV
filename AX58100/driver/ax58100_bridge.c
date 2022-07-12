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

#ifdef AX58100_BRIDGE_MODULE_ENABLED
#include "ax58100_bridge.h"

/* NAMING CONSTANT DECLARATIONS */

/* TYPE DECLARATIONS */
typedef enum
{
	BRG_ALWAYS = 0,	
	BRG_SOF,	
	BRG_EOF,		
	BRG_SYNC_0,
	BRG_LATCH_0,
	BRG_SYNC_1,	
	BRG_LATCH_1,	
	BRG_AFTER_WRITE,
	BRG_DATA_VALUE_CHANGE,
	BRG_ESC_CS_ASSERT,
	BRG_ESC_CS_DEASSERT,
	BRG_FUN_CS_ASSERT,
	BRG_FUN_CS_DEASSERT,
	BRG_PWM_CYCLE_START,
	
	BRG_MAX_SYNC_TYPES,
} BRG_SYNC_SOURCE_TYPE;

/* GLOBAL VARIABLES DECLARATIONS */

/* LOCAL VARIABLES DECLARATIONS */
ACCESSCTRL_OBJECT acc_ctrl_reg;
FMIRER_OBJECT     fmirer;

/* LOCAL SUBPROGRAM DECLARATIONS */

/* LOCAL SUBPROGRAM BODIES */


/* EXPORTED SUBPROGRAM BODIES */

/*
 * ----------------------------------------------------------------------------
 * Function Name: BRG_MotorControlEscAccess
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void BRG_MotorControlEscAccess(u8 Enable)
{
	u32 i;

	/* Set access sync type and access right */
	acc_ctrl_reg.d8 = 0;
	acc_ctrl_reg.b.data_sync_trg_type = BRG_ALWAYS;
	acc_ctrl_reg.b.is_writable_with_esc = ((Enable == 0) ? 0:1);
	for (i=INTCACR; i<=INTSACR; i++)
	{
		AX_INTF_EscWrite(i, &(acc_ctrl_reg.d8), 1);
	}		
	for (i=MCTLACR; i<=SCNTACR; i++)
	{
		AX_INTF_EscWrite(i, &(acc_ctrl_reg.d8), 1);
	}
	
	/* Dependent on application, override sync types or access right here */
	
	/* Enable mirror function */
	AX_INTF_EscRead(FMIRER, &fmirer.d8, 1);
	fmirer.b.pwm_func_mirror = ((Enable == 0) ? 0:1);
	AX_INTF_EscWrite(FMIRER, &fmirer.d8, 1);

} /* End of BRG_MotorControlEscAccess() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: BRG_EncoderEscAccess
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void BRG_EncoderEscAccess(u8 Enable)
{
	u32 i;

	/* Set access sync type and access right */
	acc_ctrl_reg.d8 = 0;
	acc_ctrl_reg.b.data_sync_trg_type = BRG_DATA_VALUE_CHANGE;
	acc_ctrl_reg.b.is_writable_with_esc = ((Enable == 0) ? 0:1);
	for (i=INTCACR; i<=INTSACR; i++)
	{
		AX_INTF_EscWrite(i, &(acc_ctrl_reg.d8), 1);
	}		
	for (i=ECNTVACR; i<=HSTACR; i++)
	{
		AX_INTF_EscWrite(i, &(acc_ctrl_reg.d8), 1);
	}
	
	/* Dependent on application, override sync types or access right here */
	
	/* Enable mirror function */
	AX_INTF_EscRead(FMIRER, &fmirer.d8, 1);
	fmirer.b.enc_func_mirror = ((Enable == 0) ? 0:1);
	AX_INTF_EscWrite(FMIRER, &fmirer.d8, 1);

} /* End of BRG_EncoderEscAccess() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: BRG_EmIowdEscAccess
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void BRG_EmIowdEscAccess(u8 Enable)
{
	u32 i;

	/* Set access sync type and access right */
	acc_ctrl_reg.d8 = 0;
	acc_ctrl_reg.b.data_sync_trg_type = BRG_ALWAYS;
	acc_ctrl_reg.b.is_writable_with_esc = ((Enable == 0) ? 0:1);
	for (i=INTCACR; i<=INTSACR; i++)
	{
		AX_INTF_EscWrite(i, &(acc_ctrl_reg.d8), 1);
	}		
	for (i=WTACR; i<=WPKACR; i++)
	{
		AX_INTF_EscWrite(i, &(acc_ctrl_reg.d8), 1);
	}
	
	/* Dependent on application, override sync types or access right here */
	
	/* Enable mirror function */
	AX_INTF_EscRead(FMIRER, &fmirer.d8, 1);
	fmirer.b.iowd_func_mirror = ((Enable == 0) ? 0:1);
	AX_INTF_EscWrite(FMIRER, &fmirer.d8, 1);

} /* End of BRG_EmIowdEscAccess() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: BRG_SpiMasterEscAccess
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void BRG_SpiMasterEscAccess(u8 Enable)
{
	u32 i;

	/* Set access sync type and access right */
	acc_ctrl_reg.d8 = 0;
	acc_ctrl_reg.b.data_sync_trg_type = BRG_DATA_VALUE_CHANGE;
	acc_ctrl_reg.b.is_writable_with_esc = ((Enable == 0) ? 0:1);
	for (i=INTCACR; i<=INTSACR; i++)
	{
		AX_INTF_EscWrite(i, &(acc_ctrl_reg.d8), 1);
	}	
	for (i=SPICFIGACR; i<=SPICACR; i++)
	{
		AX_INTF_EscWrite(i, &(acc_ctrl_reg.d8), 1);
	}
	
	/* Dependent on application, override sync types or access right here */
	
	/* Enable mirror function */
	AX_INTF_EscRead(FMIRER, &fmirer.d8, 1);
	fmirer.b.spim_func_mirror = ((Enable == 0) ? 0:1);
	AX_INTF_EscWrite(FMIRER, &fmirer.d8, 1);

} /* End of BRG_SpiMasterEscAccess() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: BRG_AllModulesEscAccess
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void BRG_AllModulesEscAccess(u8 Enable)
{
  BRG_MotorControlEscAccess(Enable);
  BRG_EncoderEscAccess(Enable);
  BRG_EmIowdEscAccess(Enable);
  BRG_SpiMasterEscAccess(Enable);

} /* End of BRG_AllModulesEscAccess() */

#endif /* AX58100_BRIDGE_MODULE_ENABLED */

/* End of ax58100_bridge.c */
