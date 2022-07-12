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
#include "ax58100_misc.h"

/* NAMING CONSTANT DECLARATIONS */

/* TYPE DECLARATIONS */

/* GLOBAL VARIABLES DECLARATIONS */

/* LOCAL VARIABLES DECLARATIONS */
static ESTOR_OBJECT estor;

/* LOCAL SUBPROGRAM DECLARATIONS */

/* LOCAL SUBPROGRAM BODIES */


/* EXPORTED SUBPROGRAM BODIES */
/*
 * ----------------------------------------------------------------------------
 * Function Name: MISC_InterruptsEnable
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void MISC_InterruptsEnable(u16 EnableMask)
{
	u16 tmp16;
	
	if (EnableMask)
	{	
		AX_INTF_Read(INTCR, &tmp16, 2);
		tmp16 |= EnableMask;
		AX_INTF_Write(INTCR, &tmp16, 2);
	}
} /* End of MISC_InterruptsEnable() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: MISC_InterruptsDisable
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void MISC_InterruptsDisable(u16 DisableMask)
{
	u16 tmp16;
	
	if (DisableMask)
	{
		AX_INTF_Read(INTCR, &tmp16, 2);
		tmp16 &= (~DisableMask);
		AX_INTF_Write(INTCR, &tmp16, 2);
	}
} /* End of MISC_InterruptsDisable() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: MISC_GetIRQ
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
u16 MISC_GetIRQ(void)
{
	u16 tmp16[2];
	
	/* Read INTCR and INTSR */
	AX_INTF_Read(INTCR, tmp16, 4);
	
	return ((tmp16[0] & tmp16[1]) | (tmp16[1] & ESC_INTR_STATUS));//Retain ESC interrupt flag
} /* End of MISC_GetIRQ() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: MISC_EfuseRead
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
AX_STATUS MISC_EfuseRead(u8 Addr, u8 *pBuf, u8 Size)
{
	ECTRLR_OBJECT ectrlr;

	if ((Size == 0) || ((Size + Addr) > 8))
	{		
		return AX_STATUS_ERR;
	}
	
	while (Size--)
	{
		ectrlr.b.efuse_byte_addr = Addr;
		ectrlr.b.efuse_cmd = 0x01;
		AX_INTF_FunWrite(ECTRLR, &(ectrlr.d16), 2);
	
		/* Wait byte read operation done */
		do
		{
			AX_INTF_FunRead(ECTRLR, &(ectrlr.d16), 2);
		} while (ectrlr.b.efuse_cmd);
	
		AX_INTF_FunRead(ERDR, pBuf, 1);	
	
		pBuf++;
		Addr++;
	}
	
	return AX_STATUS_OK;
} /* End of MISC_EfuseRead() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: MISC_EfuseWrite
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
AX_STATUS MISC_EfuseWrite(u8 Addr, u8 *pData, u8 Len)
{
	ECTRLR_OBJECT ectrlr;
	u8 i;
	
	if ((Len == 0) || ((Len + Addr) > 8))
	{
		return AX_STATUS_ERR;
	}
	
	while (Len--)
	{
		for (i=0; i<8; i++)
		{
			/* Check bit value need to be wrtten */
			if (((*pData) & (1<<i))==0)
			{
				continue;
			}
			
			/* Bit write start */			
			ectrlr.b.efuse_byte_addr = Addr;
			ectrlr.b.efuse_cmd = 0x02;			
			ectrlr.b.efuse_bit_addr	= i;
			AX_INTF_FunWrite(ECTRLR, &(ectrlr.d16), 2);
	
			/* Wait write operation done */
			do
			{
				AX_INTF_FunRead(ECTRLR, &(ectrlr.d16), 2);
			} while (ectrlr.b.efuse_cmd);
		}
		pData++;
		Addr++;
	}
	return AX_STATUS_OK;
} /* End of MISC_EfuseWrite() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: MISC_MotorControlOverride
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void MISC_MotorControlOverride(u8 Enable)
{
	AX_INTF_FunRead(ESTOR, &estor.d16, 2);
	estor.b.motor_ctrl_override = ((Enable == 0) ? 0:1);
	AX_INTF_FunWrite(ESTOR, &estor.d16, 2);	

} /* End of MISC_MotorControlOverride() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: MISC_SpiMasterOverride
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void MISC_SpiMasterOverride(u8 Enable)
{
	AX_INTF_FunRead(ESTOR, &estor.d16, 2);
	estor.b.spi_master_override = ((Enable == 0) ? 0:1);
	AX_INTF_FunWrite(ESTOR, &estor.d16, 2);	

} /* End of MISC_SpiMasterOverride() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: MISC_BridgeOverride
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void MISC_BridgeOverride(u8 Enable)
{
	AX_INTF_FunRead(ESTOR, &estor.d16, 2);
	estor.b.brg_override = ((Enable == 0) ? 0:1);
	AX_INTF_FunWrite(ESTOR, &estor.d16, 2);	

} /* End of MISC_BridgeOverride() */

/* End of ax58100_misc.c */
