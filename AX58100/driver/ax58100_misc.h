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
#ifndef __AX58100_MISC_H__
#define __AX58100_MISC_H__

/* INCLUDE FILE DECLARATIONS */
#include "ax58100_regobjs.h"

/* NAMING CONSTANT DECLARATIONS */
#define AX58100_CHIP_REVISION      0x01
#define AX58100_PRODUCT_ID         0x00058100
#define AX58100_VENDOR_ID          0x00000B95

/* MACRO DECLARATIONS */
#define MISC_GET_HOST_INTF_STATUS(pcStu) {AX_INTF_FunRead(HSTSR, pcStu, 1);}
#define MISC_GET_INTR_CONTROL(pwCtrl)    {AX_INTF_Read(INTCR, pwCtrl, 2);}
#define MISC_GET_INTR_STATUS(pwFlags)    {AX_INTF_Read(INTSR, pwFlags, 2);}
#define MISC_CLR_INTR_STATUS(pwFlags)    {AX_INTF_Write(INTSR, pwFlags, 2);}

/* TYPE DECLARATIONS */

/* GLOBAL VARIABLES */

/* EXPORTED SUBPROGRAM SPECIFICATIONS */
void MISC_InterruptsEnable(u16 EnableMask);
void MISC_InterruptsDisable(u16 DisableMask);
u16 MISC_GetIRQ(void);

	/* Efuse access commands */
AX_STATUS MISC_EfuseRead(u8 Addr, u8 *pBuf, u8 Size);
AX_STATUS MISC_EfuseWrite(u8 Addr, u8 *pData, u8 Len);

	/* These overrided functins are used to enforce some of hardware modules to be availabled
     without entered OP mode, typically used for debugging.
  */
void MISC_MotorControlOverride(u8 Enable);
void MISC_SpiMasterOverride(u8 Enable);
void MISC_BridgeOverride(u8 Enable);

#endif /* __AX58100_MISC_H__ */

/* End of ax58100_misc.h */
