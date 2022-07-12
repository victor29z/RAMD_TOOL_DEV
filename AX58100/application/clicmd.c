/*
 ******************************************************************************
 *     Copyright (c) 2016	ASIX Electronic Corporation      All rights reserved.
 *
 *     This is unpublished proprietary source code of ASIX Electronic Corporation
 *
 *     The copyright notice above does not evidence any actual or intended
 *     publication of such source code.
 ******************************************************************************
 */

/* INCLUDE FILE DECLARATIONS */
#include "stm32f4xx_hal.h"
#include "clicmd.h"
#include "string.h"
#include <stdlib.h>
#include "ax_intf.h"
#include "samplehw.h"
#include "test.h"


#if (MC_STACK_ENABLE)
	#include "ui_task.h"
#endif

/* NAMING CONSTANT DECLARATIONS */
#define IsDigit(x) ((x < 0x3a && x > 0x2f) ? 1 : 0)
#define STR_ENABLE		"Enable "
#define STR_DISABLE		"Disable"
#define STR_8_BITS		"8bits "
#define STR_16_BITS		"16bits"
#define STR_HIGH			"High"
#define STR_LOW				"Low "

#define CLICMD_CTRL_C	0x03
#define CLICMD_SPACE	0x20
#define CLICMD_STR_BUF_SIZE		512

/* MACRO DECLARATIONS */

/* TYPE DECLARATIONS */

/* GLOBAL VARIABLES DECLARATIONS */
extern BOOL bDcSyncActive;

/* LOCAL VARIABLES DECLARATIONS */
static u8 StrBuf[MAX_TEMP_BUF_SIZE];
static TEST_CONTROL								clicmd_testCtrl;

/* LOCAL SUBPROGRAM DECLARATIONS */
static u8 clicmd_DecText2Char(u8 *pbuf, u8 *pValue, u8 len);
static u8 clicmd_HexText2Char(u8 *pbuf, u8 *pValue, u8 len);
static u8 clicmd_DecText2Short(u8 *pbuf, u16 *pValue, u8 len);
static u8 clicmd_HexText2Short(u8 *pbuf, u16 *pValue, u8 len);
static u8 clicmd_DecText2Long(u8 *pbuf, u32 *pValue, u8 len);
static u8 clicmd_HexText2Long(u8 *pbuf, u32 *pValue, u8 len);
static void clicmd_ShowMemoryInHex8b(CONSOLE_Inst *pInst, u8 *pbuf, u32 len);
static void clicmd_ShowMemoryInHex16b(CONSOLE_Inst *pInst, u16 *pbuf, u32 len);
static void clicmd_ShowAccessCtrlRegisters(CONSOLE_Inst *inst);
static int clicmd_SystemReboot(CONSOLE_Inst *inst, int argc, char **argv);
static int clicmd_SystemRebootHelp(CONSOLE_Inst *inst);
static int clicmd_SystemRebootUsage(CONSOLE_Inst *inst);
static int clicmd_PdiRead(CONSOLE_Inst *inst, int argc, char **argv);
static int clicmd_PdiReadHelp(CONSOLE_Inst *inst);
static int clicmd_PdiReadUsage(CONSOLE_Inst *inst);
static int clicmd_PdiWrite(CONSOLE_Inst *inst, int argc, char **argv);
static int clicmd_PdiWriteHelp(CONSOLE_Inst *inst);
static int clicmd_PdiWriteUsage(CONSOLE_Inst *inst);

#if CLI_MCU_DBG_CMD_ENABLE
static int clicmd_USARTxRegister(CONSOLE_Inst *inst, int argc, char **argv);
static int clicmd_USARTxRegisterHelp(CONSOLE_Inst *inst);
static int clicmd_USARTxRegisterUsage(CONSOLE_Inst *inst);
static int clicmd_TIMxRegister(CONSOLE_Inst *inst, int argc, char **argv);
static int clicmd_TIMxRegisterHelp(CONSOLE_Inst *inst);
static int clicmd_TIMxRegisterUsage(CONSOLE_Inst *inst);
static int clicmd_SPIxRegister(CONSOLE_Inst *inst, int argc, char **argv);
static int clicmd_SPIxRegisterHelp(CONSOLE_Inst *inst);
static int clicmd_SPIxRegisterUsage(CONSOLE_Inst *inst);
static int clicmd_RccRegister(CONSOLE_Inst *inst, int argc, char **argv);
static int clicmd_RccRegisterHelp(CONSOLE_Inst *inst);
static int clicmd_RccRegisterUsage(CONSOLE_Inst *inst);
static int clicmd_ExtiRegister(CONSOLE_Inst *inst, int argc, char **argv);
static int clicmd_ExtiRegisterHelp(CONSOLE_Inst *inst);
static int clicmd_ExtiRegisterUsage(CONSOLE_Inst *inst);
static int clicmd_GPIOxRegister(CONSOLE_Inst *inst, int argc, char **argv);
static int clicmd_GPIOxRegisterHelp(CONSOLE_Inst *inst);
static int clicmd_GPIOxRegisterUsage(CONSOLE_Inst *inst);
static int clicmd_NvicRegister(CONSOLE_Inst *inst, int argc, char **argv);
static int clicmd_NvicRegisterHelp(CONSOLE_Inst *inst);
static int clicmd_NvicRegisterUsage(CONSOLE_Inst *inst);
#endif

#if CLI_AX58100_DBG_CMD_ENABLE
static int clicmd_AX58100Register(CONSOLE_Inst *inst, int argc, char **argv);
static int clicmd_AX58100RegisterHelp(CONSOLE_Inst *inst);
static int clicmd_AX58100RegisterUsage(CONSOLE_Inst *inst);
static int clicmd_PdiMemoryTest(CONSOLE_Inst *inst, int argc, char **argv);
static int clicmd_PdiMemoryTestHelp(CONSOLE_Inst *inst);
static int clicmd_PdiMemoryTestUsage(CONSOLE_Inst *inst);
static int clicmd_CiA402Status(CONSOLE_Inst *inst, int argc, char **argv);
static int clicmd_CiA402StatusHelp(CONSOLE_Inst *inst);
static int clicmd_AccessCtrlConfig(CONSOLE_Inst *inst, int argc, char **argv);
static int clicmd_AccessCtrlConfigHelp(CONSOLE_Inst *inst);
static int clicmd_AccessCtrlConfigUsage(CONSOLE_Inst *inst);
static int clicmd_PdiReset(CONSOLE_Inst *inst, int argc, char **argv);
static int clicmd_PdiResetHelp(CONSOLE_Inst *inst);
#endif

CONSOLE_Account CLICMD_userTable[MAX_USER_ACCOUNT];

CONSOLE_CmdEntry CLICMD_userCmdTable[]=
{
	{";", NULL, NULL, 5},	
	{"reboot", clicmd_SystemReboot, clicmd_SystemRebootHelp, 5},

#if CLI_MCU_DBG_CMD_ENABLE
	{"usartx", clicmd_USARTxRegister, clicmd_USARTxRegisterHelp, 5},		
	{"timx", clicmd_TIMxRegister, clicmd_TIMxRegisterHelp, 5},
	{"spix", clicmd_SPIxRegister, clicmd_SPIxRegisterHelp, 5},		
	{"rcc", clicmd_RccRegister, clicmd_RccRegisterHelp, 5},
	{"exti", clicmd_ExtiRegister, clicmd_ExtiRegisterHelp, 5},	
	{"gpiox", clicmd_GPIOxRegister, clicmd_GPIOxRegisterHelp, 5},		
	{"nvic", clicmd_NvicRegister, clicmd_NvicRegisterHelp, 5},		
#endif
	
#if CLI_AX58100_DBG_CMD_ENABLE
	{"pdird", clicmd_PdiRead, clicmd_PdiReadHelp, 5}, 	
	{"pdiwr", clicmd_PdiWrite, clicmd_PdiWriteHelp, 5},	
	{"pdimt", clicmd_PdiMemoryTest, clicmd_PdiMemoryTestHelp, 5},		
	{"axreg", clicmd_AX58100Register, clicmd_AX58100RegisterHelp, 5},
	{"402", clicmd_CiA402Status, clicmd_CiA402StatusHelp, 5},			
	{"accfg", clicmd_AccessCtrlConfig, clicmd_AccessCtrlConfigHelp, 5},	
	{"pdirst", clicmd_PdiReset, clicmd_PdiResetHelp, 5},
#endif	
};

/* LOCAL SUBPROGRAM BODIES */

/*
 * ----------------------------------------------------------------------------
 * Function Name: clicmd_DecText2Char
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
static u8 clicmd_DecText2Char(u8 *pbuf, u8 *pValue, u8 len)
{
	*pValue = 0;

	if ((len == 0) || (len > 3))
	{
		return 0xFF;
	}

	while (len--)
	{
		*pValue *= 10;

		if ((*pbuf < 0x3A) && (*pbuf > 0x2F))
		{
			*pValue += (*pbuf - 0x30);
		}
		else
		{
			return 0xFF;
		}

		pbuf++;
	}

	if (*pValue > 255)
	{
		return 0xFF;
	}

	return 0;

} /* End of  clicmd_DecText2Char() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: clicmd_HexText2Char
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
static u8 clicmd_HexText2Char(u8 *pbuf, u8 *pValue, u8 len)
{
	*pValue = 0;

	if ((len == 0) || (len > 2))
	{
		return 0xFF;
	}

	while (len--)
	{
		*pValue *= 16;

		if ((*pbuf < 0x3A) && (*pbuf > 0x2F))
			*pValue += (*pbuf - 0x30);
		else if ((*pbuf < 0x47) && (*pbuf > 0x40))
			*pValue += (*pbuf - 0x37);
		else if ((*pbuf < 0x67) && (*pbuf > 0x60))
			*pValue += (*pbuf - 0x57);
		else
			return 0xFF;

		pbuf++;
	}

	return 0;

} /* End of  clicmd_HexText2Char() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: clicmd_DecText2Short
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
static u8 clicmd_DecText2Short(u8 *pbuf, unsigned short *pValue, u8 len)
{
	*pValue = 0;

	if ((len == 0) || (len > 5))
		return 0xff;

	while (len--)
	{
		*pValue *= 10;

		if ((*pbuf < 0x3a) && (*pbuf > 0x2f))
			*pValue += (*pbuf - 0x30);
		else
			return 0xff;

		pbuf++;
	}

	if (*pValue > 65535)
		return 0xff;

	return 0;

} /* End of  clicmd_DecText2Short() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: clicmd_HexText2Short
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
static u8 clicmd_HexText2Short(u8 *pbuf, u16 *pValue, u8 len)
{
	*pValue = 0;

	if ((len == 0) || (len > 4))
		return 0xff;

	while (len--)
	{
		*pValue *= 16;

		if ((*pbuf < 0x3a) && (*pbuf > 0x2f))
			*pValue += (*pbuf - 0x30);
		else if ((*pbuf < 0x47) && (*pbuf > 0x40))
			*pValue += (*pbuf - 0x37);
		else if ((*pbuf < 0x67) && (*pbuf > 0x60))
			*pValue += (*pbuf - 0x57);
		else
			return 0xff;

		pbuf++;
	}

	return 0;

} /* End of  clicmd_HexaText2Short() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: clicmd_DecText2Long
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
static u8 clicmd_DecText2Long(u8 *pbuf, u32 *pValue, u8 len)
{
	*pValue = 0;

	if ((len == 0) || (len > 10))
		return 0xff;

	while (len--)
	{
		*pValue *= 10;

		if ((*pbuf < 0x3a) && (*pbuf > 0x2f))
			*pValue += (*pbuf - 0x30);
		else
			return 0xff;

		pbuf++;
	}

	if (*pValue > 0xffffffff)
		return 0xff;

	return 0;

} /* End of  clicmd_DecText2Long() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: clicmd_HexText2Long
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
static u8 clicmd_HexText2Long(u8 *pbuf, u32 *pValue, u8 len)
{
	*pValue = 0;

	if ((len == 0) || (len > 8))
		return 0xff;

	while (len--)
	{
		*pValue *= 16;

		if ((*pbuf < 0x3a) && (*pbuf > 0x2f))
			*pValue += (*pbuf - 0x30);
		else if ((*pbuf < 0x47) && (*pbuf > 0x40))
			*pValue += (*pbuf - 0x37);
		else if ((*pbuf < 0x67) && (*pbuf > 0x60))
			*pValue += (*pbuf - 0x57);
		else
			return 0xff;

		pbuf++;
	}

	return 0;

} /* End of  clicmd_HexText2Long() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: clicmd_ShowMemoryInHex8b()
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
static void clicmd_ShowMemoryInHex8b(CONSOLE_Inst *inst, u8 *pbuf, u32 len)
{
	u32 i;
	
	for (i=0; i<len; i++)
	{
		CONSOLE_PutMessage(inst, "0x%02x%s", pbuf[i], ((i+1) == len) ? "\r\n":", ");
		if ((i%16)==15)
		{
			CONSOLE_PutMessage(inst, "\r\n");
		}
	}
	CONSOLE_PutMessage(inst, "\r\n");	
} /* End of clicmd_ShowMemoryInHex8b() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: clicmd_ShowMemoryInHex16b()
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
static void clicmd_ShowMemoryInHex16b(CONSOLE_Inst *inst, u16 *pbuf, u32 WordLen)
{
	u32 i;
	
	for (i=0; i<WordLen; i++)
	{
		CONSOLE_PutMessage(inst, "0x%04x%s", pbuf[i], ((i+1) == WordLen) ? "\r\n":", ");
		if ((i%16)==15)
		{
			CONSOLE_PutMessage(inst, "\r\n");
		}
	}
	CONSOLE_PutMessage(inst, "\r\n");	
} /* End of clicmd_ShowMemoryInHex16b() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: clicmd_ShowAccessCtrlRegisters()
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
static void clicmd_ShowAccessCtrlRegisters(CONSOLE_Inst *inst)
{
	u8 tmp8;
	u16 tmp16;
	
	CONSOLE_PutMessage(inst, "Current Access Control Registers:\r\n");
	
	/* MC Access Control Registers */	
	AX_INTF_EscRead(MCTLACR, (u8*)&tmp8, 1);
	CONSOLE_PutMessage(inst, "       MCTLACR(0x%04x):0x%02x\r\n", MCTLACR, tmp8);
	AX_INTF_EscRead(PXCFGACR, (u8*)&tmp8, 1);
	CONSOLE_PutMessage(inst, "       PXCFGACR(0x%04x):0x%02x\r\n", PXCFGACR, tmp8);
	AX_INTF_EscRead(PTACFGACR, (u8*)&tmp8, 1);
	CONSOLE_PutMessage(inst, "       PTACFGACR(0x%04x):0x%02x\r\n", PTACFGACR, tmp8);
	AX_INTF_EscRead(PTBCFGACR, (u8*)&tmp8, 1);
	CONSOLE_PutMessage(inst, "       PTBCFGACR(0x%04x):0x%02x\r\n", PTBCFGACR, tmp8);
	AX_INTF_EscRead(PPCACR, (u8*)&tmp8, 1);
	CONSOLE_PutMessage(inst, "       PPCACR(0x%04x):0x%02x\r\n", PPCACR, tmp8);
	AX_INTF_EscRead(PBBMACR, (u8*)&tmp8, 1);
	CONSOLE_PutMessage(inst, "       PBBMACR(0x%04x):0x%02x\r\n", PBBMACR, tmp8);
	AX_INTF_EscRead(P1CTRLACR, (u8*)&tmp8, 1);
	CONSOLE_PutMessage(inst, "       P1CTRLACR(0x%04x):0x%02x\r\n", P1CTRLACR, tmp8);
	AX_INTF_EscRead(P1SHACR, (u8*)&tmp8, 1);
	CONSOLE_PutMessage(inst, "       P1SHACR(0x%04x):0x%02x\r\n", P1SHACR, tmp8);
	AX_INTF_EscRead(P1HPWACR, (u8*)&tmp8, 1);
	CONSOLE_PutMessage(inst, "       P1HPWACR(0x%04x):0x%02x\r\n", P1HPWACR, tmp8);	
	AX_INTF_EscRead(P2CTRLACR, (u8*)&tmp8, 1);
	CONSOLE_PutMessage(inst, "       P2CTRLACR(0x%04x):0x%02x\r\n", P2CTRLACR, tmp8);
	AX_INTF_EscRead(P2SHACR, (u8*)&tmp8, 1);
	CONSOLE_PutMessage(inst, "       P2SHACR(0x%04x):0x%02x\r\n", P2SHACR, tmp8);
	AX_INTF_EscRead(P2HPWACR, (u8*)&tmp8, 1);
	CONSOLE_PutMessage(inst, "       P2HPWACR(0x%04x):0x%02x\r\n", P2HPWACR, tmp8);		
	AX_INTF_EscRead(P3CTRLACR, (u8*)&tmp8, 1);
	CONSOLE_PutMessage(inst, "       P3CTRLACR(0x%04x):0x%02x\r\n", P3CTRLACR, tmp8);
	AX_INTF_EscRead(P3SHACR, (u8*)&tmp8, 1);
	CONSOLE_PutMessage(inst, "       P3SHACR(0x%04x):0x%02x\r\n", P3SHACR, tmp8);
	AX_INTF_EscRead(P3HPWACR, (u8*)&tmp8, 1);
	CONSOLE_PutMessage(inst, "       P3HPWACR(0x%04x):0x%02x\r\n", P3HPWACR, tmp8);			
	AX_INTF_EscRead(SGTACR, (u8*)&tmp8, 1);
	CONSOLE_PutMessage(inst, "       SGTACR(0x%04x):0x%02x\r\n", SGTACR, tmp8);	
	AX_INTF_EscRead(SHPWACR, (u8*)&tmp8, 1);
	CONSOLE_PutMessage(inst, "       SHPWACR(0x%04x):0x%02x\r\n", SHPWACR, tmp8);
	AX_INTF_EscRead(TDLYACR, (u8*)&tmp8, 1);
	CONSOLE_PutMessage(inst, "       TDLYACR(0x%04x):0x%02x\r\n", TDLYACR, tmp8);
	AX_INTF_EscRead(STNACR, (u8*)&tmp8, 1);
	CONSOLE_PutMessage(inst, "       STNACR(0x%04x):0x%02x\r\n", STNACR, tmp8);
	AX_INTF_EscRead(SCFGACR, (u8*)&tmp8, 1);
	CONSOLE_PutMessage(inst, "       SCFGACR(0x%04x):0x%02x\r\n", SCFGACR, tmp8);
	AX_INTF_EscRead(SCTRLACR, (u8*)&tmp8, 1);
	CONSOLE_PutMessage(inst, "       SCTRLACR(0x%04x):0x%02x\r\n", SCTRLACR, tmp8);
	AX_INTF_EscRead(SCNTACR, (u8*)&tmp8, 1);
	CONSOLE_PutMessage(inst, "       SCNTACR(0x%04x):0x%02x\r\n", SCNTACR, tmp8);
	
	/* Encoder Access Control Registers */
	AX_INTF_EscRead(ECNTVACR, (u8*)&tmp8, 1);
	CONSOLE_PutMessage(inst, "       ECNTVACR(0x%04x):0x%02x\r\n", ECNTVACR, tmp8);
	AX_INTF_EscRead(ECNSTACR, (u8*)&tmp8, 1);
	CONSOLE_PutMessage(inst, "       ECNSTACR(0x%04x):0x%02x\r\n", ECNSTACR, tmp8);
	AX_INTF_EscRead(ELATACR, (u8*)&tmp8, 1);
	CONSOLE_PutMessage(inst, "       ELATACR(0x%04x):0x%02x\r\n", ELATACR, tmp8);
	AX_INTF_EscRead(EMODACR, (u8*)&tmp8, 1);
	CONSOLE_PutMessage(inst, "       EMODACR(0x%04x):0x%02x\r\n", EMODACR, tmp8);
	AX_INTF_EscRead(ENCSTACR, (u8*)&tmp8, 1);
	CONSOLE_PutMessage(inst, "       ENCSTACR(0x%04x):0x%02x\r\n", ENCSTACR, tmp8);	
	AX_INTF_EscRead(HSTACR, (u8*)&tmp8, 1);
	CONSOLE_PutMessage(inst, "       HSTACR(0x%04x):0x%02x\r\n", HSTACR, tmp8);	 
	
	/* I/O Watchdog Access Control Registers */	
	AX_INTF_EscRead(WTACR, (u8*)&tmp8, 1);
	CONSOLE_PutMessage(inst, "       WTACR(0x%04x):0x%02x\r\n", WTACR, tmp8);	 
	AX_INTF_EscRead(WCACR, (u8*)&tmp8, 1);
	CONSOLE_PutMessage(inst, "       WCACR(0x%04x):0x%02x\r\n", WCACR, tmp8);	
	AX_INTF_EscRead(WPCACR, (u8*)&tmp8, 1);
	CONSOLE_PutMessage(inst, "       WPCACR(0x%04x):0x%02x\r\n", WPCACR, tmp8);
	AX_INTF_EscRead(WPACR, (u8*)&tmp8, 1);
	CONSOLE_PutMessage(inst, "       WPACR(0x%04x):0x%02x\r\n", WPACR, tmp8);	 
	AX_INTF_EscRead(WMACR, (u8*)&tmp8, 1);
	CONSOLE_PutMessage(inst, "       WMACR(0x%04x):0x%02x\r\n", WMACR, tmp8);	 
	AX_INTF_EscRead(WOMACR, (u8*)&tmp8, 1);
	CONSOLE_PutMessage(inst, "       WOMACR(0x%04x):0x%02x\r\n", WOMACR, tmp8);	 
	AX_INTF_EscRead(WOEACR, (u8*)&tmp8, 1);
	CONSOLE_PutMessage(inst, "       WOEACR(0x%04x):0x%02x\r\n", WOEACR, tmp8);	 
	AX_INTF_EscRead(WOPACR, (u8*)&tmp8, 1);
	CONSOLE_PutMessage(inst, "       WOPACR(0x%04x):0x%02x\r\n", WOPACR, tmp8);	 
	AX_INTF_EscRead(WPKACR, (u8*)&tmp8, 1);
	CONSOLE_PutMessage(inst, "       WPKACR(0x%04x):0x%02x\r\n", WPKACR, tmp8);	 

	/* SPI Master Access Control Registers */	
	AX_INTF_EscRead(SPICFIGACR, (u8*)&tmp8, 1);
	CONSOLE_PutMessage(inst, "       SPICFGACR(0x%04x):0x%02x\r\n", SPICFIGACR, tmp8);	 
	AX_INTF_EscRead(SPIBRACR, (u8*)&tmp8, 1);
	CONSOLE_PutMessage(inst, "       SPIBRACR(0x%04x):0x%02x\r\n", SPIBRACR, tmp8);	 
	AX_INTF_EscRead(SPIDBSACR, (u8*)&tmp8, 1);
	CONSOLE_PutMessage(inst, "       SPIDBSACR(0x%04x):0x%02x\r\n", SPIDBSACR, tmp8);	 
	AX_INTF_EscRead(SPIDTACR, (u8*)&tmp8, 1);
	CONSOLE_PutMessage(inst, "       SPIDTACR(0x%04x):0x%02x\r\n", SPIDTACR, tmp8);	 
	AX_INTF_EscRead(SPIRPTACR, (u8*)&tmp8, 1);
	CONSOLE_PutMessage(inst, "       SPIRPTACR(0x%04x):0x%02x\r\n", SPIRPTACR, tmp8);	 
	AX_INTF_EscRead(SPILDTACR, (u8*)&tmp8, 1);
	CONSOLE_PutMessage(inst, "       SPILDTACR(0x%04x):0x%02x\r\n", SPILDTACR, tmp8);	 
	AX_INTF_EscRead(SPIPRLFACR, (u8*)&tmp8, 1);
	CONSOLE_PutMessage(inst, "       SPIPRLFACR(0x%04x):0x%02x\r\n", SPIPRLFACR, tmp8);	 
	AX_INTF_EscRead(SPI01BCACR, (u8*)&tmp8, 1);
	CONSOLE_PutMessage(inst, "       SPI01BCACR(0x%04x):0x%02x\r\n", SPI01BCACR, tmp8);	
	AX_INTF_EscRead(SPI23BCACR, (u8*)&tmp8, 1);
	CONSOLE_PutMessage(inst, "       SPI23BCACR(0x%04x):0x%02x\r\n", SPI23BCACR, tmp8);	
	AX_INTF_EscRead(SPI45BCACR, (u8*)&tmp8, 1);
	CONSOLE_PutMessage(inst, "       SPI45BCACR(0x%04x):0x%02x\r\n", SPI45BCACR, tmp8);	
	AX_INTF_EscRead(SPI67BCACR, (u8*)&tmp8, 1);
	CONSOLE_PutMessage(inst, "       SPI67BCACR(0x%04x):0x%02x\r\n", SPI67BCACR, tmp8);		
	AX_INTF_EscRead(SPI03SACR, (u8*)&tmp8, 1);
	CONSOLE_PutMessage(inst, "       SPI03SACR(0x%04x):0x%02x\r\n", SPI03SACR, tmp8);	 
	AX_INTF_EscRead(SPI47SACR, (u8*)&tmp8, 1);
	CONSOLE_PutMessage(inst, "       SPI47SACR(0x%04x):0x%02x\r\n", SPI47SACR, tmp8);	
	AX_INTF_EscRead(SPIINTSACR, (u8*)&tmp8, 1);
	CONSOLE_PutMessage(inst, "       SPIINTSACR(0x%04x):0x%02x\r\n", SPIINTSACR, tmp8);		
	AX_INTF_EscRead(SPITSACR, (u8*)&tmp8, 1);
	CONSOLE_PutMessage(inst, "       SPITSACR(0x%04x):0x%02x\r\n", SPITSACR, tmp8);		
	AX_INTF_EscRead(SPIPOSACR, (u8*)&tmp8, 1);
	CONSOLE_PutMessage(inst, "       SPIPOSACR(0x%04x):0x%02x\r\n", SPIPOSACR, tmp8);		
	AX_INTF_EscRead(SPIDSACR, (u8*)&tmp8, 1);
	CONSOLE_PutMessage(inst, "       SPIDSACR(0x%04x):0x%02x\r\n", SPIDSACR, tmp8);			
	AX_INTF_EscRead(SPIC0DACR, (u8*)&tmp8, 1);
	CONSOLE_PutMessage(inst, "       SPIC0DACR(0x%04x):0x%02x\r\n", SPIC0DACR, tmp8);			
	AX_INTF_EscRead(SPIC1DACR, (u8*)&tmp8, 1);
	CONSOLE_PutMessage(inst, "       SPIC1DACR(0x%04x):0x%02x\r\n", SPIC1DACR, tmp8);			
	AX_INTF_EscRead(SPIC2DACR, (u8*)&tmp8, 1);
	CONSOLE_PutMessage(inst, "       SPIC2DACR(0x%04x):0x%02x\r\n", SPIC2DACR, tmp8);			
	AX_INTF_EscRead(SPIC3DACR, (u8*)&tmp8, 1);
	CONSOLE_PutMessage(inst, "       SPIC3DACR(0x%04x):0x%02x\r\n", SPIC3DACR, tmp8);			
	AX_INTF_EscRead(SPIC4DACR, (u8*)&tmp8, 1);
	CONSOLE_PutMessage(inst, "       SPIC4DACR(0x%04x):0x%02x\r\n", SPIC4DACR, tmp8);				
	AX_INTF_EscRead(SPIC5DACR, (u8*)&tmp8, 1);
	CONSOLE_PutMessage(inst, "       SPIC5DACR(0x%04x):0x%02x\r\n", SPIC5DACR, tmp8);			
	AX_INTF_EscRead(SPIC6DACR, (u8*)&tmp8, 1);
	CONSOLE_PutMessage(inst, "       SPIC6DACR(0x%04x):0x%02x\r\n", SPIC6DACR, tmp8);			
	AX_INTF_EscRead(SPIC7DACR, (u8*)&tmp8, 1);
	CONSOLE_PutMessage(inst, "       SPIC7DACR(0x%04x):0x%02x\r\n", SPIC7DACR, tmp8);			
	AX_INTF_EscRead(SPICACR, (u8*)&tmp8, 1);
	CONSOLE_PutMessage(inst, "       SPICACR(0x%04x):0x%02x\r\n", SPICACR, tmp8);		

	/* Interrupt Access Control Registers */
	AX_INTF_EscRead(INTCACR, (u8*)&tmp8, 1);
	CONSOLE_PutMessage(inst, "       INTCACR(0x%04x):0x%02x\r\n", INTCACR, tmp8);	 	
	AX_INTF_EscRead(INTSACR, (u8*)&tmp8, 1);
	CONSOLE_PutMessage(inst, "       INTSACR(0x%04x):0x%02x\r\n", INTSACR, tmp8);	 	

	/* Function mirror */
	AX_INTF_EscRead(FMIRER, (u8*)&tmp8, 1);
	CONSOLE_PutMessage(inst, "       FMIRER(0x%04x):0x%02x\r\n", FMIRER, tmp8);	

	/* Override function */
	AX_INTF_FunRead(ESTOR, (u8*)&tmp16, 2);
	CONSOLE_PutMessage(inst, "       ESTOR(0x%04x):0x%04x\r\n", ESTOR, tmp16);	
	
} /* End of clicmd_ShowAccessCtrlRegisters() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: CLICMD_GetCmdTableSize()
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
u16 CLICMD_GetCmdTableSize(void)
{
    return sizeof(CLICMD_userCmdTable)/sizeof(CONSOLE_CmdEntry);
} /* End of CLICMD_GetCmdTableSize() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: CLICMD_GetCmdTable()
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void *CLICMD_GetCmdTable(void)
{
    return ((void*)CLICMD_userCmdTable);
} /* End of CLICMD_GetCmdTableSize() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: clicmd_SystemReboot()
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
static int clicmd_SystemReboot(CONSOLE_Inst *inst, int argc, char **argv)
{
	NVIC_SystemReset();
	return 1;
} /* End of clicmd_SystemReboot() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: clicmd_SystemRebootHelp()
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
static int clicmd_SystemRebootHelp(CONSOLE_Inst *inst)
{
	// Set processor clock to default before system reset
	CONSOLE_PutMessage(inst, "        reboot: System reboot\r\n");
	return 1;
} /* End of clicmd_SystemRebootHelp() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: clicmd_SystemRebootUsage()
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
static int clicmd_SystemRebootUsage(CONSOLE_Inst *inst)
{
	// Set processor clock to default before system reset
	clicmd_SystemRebootHelp(inst);
	
	CONSOLE_PutMessage(inst, "Usage: reboot\r\n");
	return 1;
} /* End of clicmd_SystemRebootUsage() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: clicmd_PdiRead()
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
static int clicmd_PdiRead(CONSOLE_Inst *inst, int argc, char **argv)
{
	u32 CS, HexOffset, ByteLen;
	
	if (argc == 1)
	{
		clicmd_PdiReadUsage(inst);
		return 1;
	}
	else if (argc != 4)
	{
		return -1;
	}
	
	if (clicmd_HexText2Long((u8*)argv[1], &CS, strlen(argv[1])) != 0)
	{
		return -1;
	}
	
	if (clicmd_HexText2Long((u8*)argv[2], &HexOffset, strlen(argv[2])) != 0)
	{
		return -1;
	}

	if (clicmd_HexText2Long((u8*)argv[3], &ByteLen, strlen(argv[3])) != 0)
	{
		return -1;
	}
		
		CONSOLE_PutMessage(inst, "Start byte read, addr=0x%x, len=0x%x byte use %s chip select\r\n"
										, HexOffset
										, ByteLen
										, (CS == 0) ? "FUN":"ESC");
	memset(StrBuf, 0, ByteLen);
	if (CS == 0)
	{
		HW_FunRead((MEM_ADDR*)StrBuf, HexOffset,  ByteLen);
	}
	else
	{
		HW_EscRead((MEM_ADDR*)StrBuf, HexOffset,  ByteLen);
	}
	clicmd_ShowMemoryInHex8b(inst, StrBuf, ByteLen);		
	return 1;
} /* End of clicmd_PdiRead() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: clicmd_PdiReadHelp()
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
static int clicmd_PdiReadHelp(CONSOLE_Inst *inst)
{
	CONSOLE_PutMessage(inst, "         pdird: Process data interface reading\r\n");
	return 1;
} /* End of clicmd_PdiReadHelp() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: clicmd_PdiReadUsage()
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
static int clicmd_PdiReadUsage(CONSOLE_Inst *inst)
{
	clicmd_PdiReadHelp(inst);
	CONSOLE_PutMessage(inst, "Usage: pdird <HexChipSelect> <HexOffset> <HexByteLen>\r\n");
	return 1;
} /* End of clicmd_PdiReadUsage() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: clicmd_PdiWrite()
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
static int clicmd_PdiWrite(CONSOLE_Inst *inst, int argc, char **argv)
{
	u32 CS, HexOffset, i, ByteLen;
	u8 *pValue8b;
	
	if (argc == 1)
	{
		clicmd_PdiWriteUsage(inst);
		return 1;
	}
	else if (argc < 4)
	{
		return -1;
	}

	if (clicmd_HexText2Long((u8*)argv[1], &CS, strlen(argv[1])) != 0) 
	{
		return -1;
	}
	
	if (clicmd_HexText2Long((u8*)argv[2], &HexOffset, strlen(argv[2])) != 0) 
	{
		return -1;
	}
	
	ByteLen = argc - 3;
		
	pValue8b = StrBuf;
	for (i=0; i<ByteLen; i++)
	{
		if (clicmd_HexText2Char((u8*)argv[i+3], pValue8b, strlen(argv[i+3])) != 0)
		{
			return -1;
		}
		pValue8b++;				
	}
	
	CONSOLE_PutMessage(inst, "Start byte write, addr=0x%x, len=0x%x byte use %s chip select\r\n"
											, HexOffset
											, ByteLen
											, (CS == 0) ? "FUN":"ESC");
	if (CS == 0)
	{
		HW_FunWrite((MEM_ADDR*)StrBuf, HexOffset,  ByteLen);					
	}
	else
	{
		HW_EscWrite((MEM_ADDR*)StrBuf, HexOffset,  ByteLen);			
	}
	clicmd_ShowMemoryInHex8b(inst, StrBuf, ByteLen);		

	return 1;
} /* End of clicmd_PdiWrite() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: clicmd_PdiWriteHelp()
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
static int clicmd_PdiWriteHelp(CONSOLE_Inst *inst)
{
	CONSOLE_PutMessage(inst, "         pdiwr: Process data interface writing\r\n");
	return 1;
} /* End of clicmd_PdiWriteHelp() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: clicmd_PdiWriteUsage()
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
static int clicmd_PdiWriteUsage(CONSOLE_Inst *inst)
{
	clicmd_PdiWriteHelp(inst);
	CONSOLE_PutMessage(inst, "Usage: pdiwr <HexChipSelect> <HexOffset> <HexValue 0> <HexValue 1>..<HexValue N>]\r\n");
	return 1;
} /* End of clicmd_PdiWriteUsage() */

#if CLI_MCU_DBG_CMD_ENABLE
/*
 * ----------------------------------------------------------------------------
 * Function Name: clicmd_USARTxRegisterDisplay()
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
static int clicmd_USARTxRegisterDisplay(CONSOLE_Inst *inst, USART_TypeDef* USARTx)
{
	USART_TypeDef *USARTxOffset = 0;

	/* Show current settings */
	CONSOLE_PutMessage(inst, "USART_ISR(0x%08lx): 0x%08lx\r\n", (u32)&(USARTxOffset->SR), USARTx->SR);
	CONSOLE_PutMessage(inst, "USART_RDR(0x%08lx): 0x%08lx\r\n", (u32)&(USARTxOffset->DR), USARTx->DR);
	CONSOLE_PutMessage(inst, "USART_BRR(0x%08lx): 0x%08lx\r\n", (u32)&(USARTxOffset->BRR), USARTx->BRR);
	CONSOLE_PutMessage(inst, "USART_CR1(0x%08lx): 0x%08lx\r\n", (u32)&(USARTxOffset->CR1), USARTx->CR1);
	CONSOLE_PutMessage(inst, "USART_CR2(0x%08lx): 0x%08lx\r\n", (u32)&(USARTxOffset->CR2), USARTx->CR2);
	CONSOLE_PutMessage(inst, "USART_CR3(0x%08lx): 0x%08lx\r\n", (u32)&(USARTxOffset->CR3), USARTx->CR3);	
	CONSOLE_PutMessage(inst, "USART_GTPR(0x%08lx): 0x%08lx\r\n", (u32)&(USARTxOffset->GTPR), USARTx->GTPR);		
	return 0;
}

/*
 * ----------------------------------------------------------------------------
 * Function Name: clicmd_USARTxRegister()
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
static int clicmd_USARTxRegister(CONSOLE_Inst *inst, int argc, char **argv)
{
	u32 HexOffset, HexValue;
	u8 HexIndex;
	USART_TypeDef *USARTx = 0;
	
	if (argc != 2 && argc != 4)
	{
		return -1;
	}
	else
	{
		/* Get instance index */	
		if (clicmd_HexText2Char((u8*)argv[1], &HexIndex, strlen(argv[1])) != 0)
		{
			return -1;
		}

		switch (HexIndex)
		{
		case 1:
			USARTx = USART1;
			break;
		case 2:
			USARTx = USART2;
			break;
		case 3:
			USARTx = USART3;
			break;
		default:
			return 1;
		}
	
		if (argc == 2)
		{
			clicmd_USARTxRegisterUsage(inst);

			CONSOLE_PutMessage(inst, "Current USART%01d registers...\r\n", HexIndex);	
			clicmd_USARTxRegisterDisplay(inst, USARTx);
			return 1;
		}
	
		/* Get register offset */
		if (clicmd_HexText2Long((u8*)argv[2], &HexOffset, strlen(argv[2])) != 0)
		{
			return -1;
		}
	
		/* Get register value */	
		if (clicmd_HexText2Long((u8*)argv[3], &HexValue, strlen(argv[3])) != 0)
		{
			return -1;
		}
	
		/* Set register value */
		*((u32 *)(((u32)USARTx) + HexOffset)) = HexValue;

		CONSOLE_PutMessage(inst, "Write USART%01d Register, Offset: 0x%08lx, vlaue: 0x%08lx\r\n", HexIndex, HexOffset, HexValue);	
		return 1;
	}
} /* End of clicmd_USARTxRegister() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: clicmd_USARTxRegisterHelp()
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
static int clicmd_USARTxRegisterHelp(CONSOLE_Inst *inst)
{
	CONSOLE_PutMessage(inst, "        usartx: Access MCU USARTx reigisters\r\n");
	return 1;
} /* End of clicmd_USARTxRegisterHelp() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: clicmd_USARTxRegisterUsage()
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
static int clicmd_USARTxRegisterUsage(CONSOLE_Inst *inst)
{
	clicmd_USARTxRegisterHelp(inst);
	CONSOLE_PutMessage(inst, "Usage: usartx <HexIndex> [<HexOffset> <HexValue>]\r\n");
	return 1;
} /* End of clicmd_USARTxRegisterUsage() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: clicmd_TIMxRegisterDisplay()
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
static int clicmd_TIMxRegisterDisplay(CONSOLE_Inst *inst, TIM_TypeDef* TIMx)
{
	TIM_TypeDef *TIMxOffet = 0;
	
	/* Show current settings */
	CONSOLE_PutMessage(inst, "CR1(0x%08lx): 0x%08lx\r\n", (u32)&(TIMxOffet->CR1), TIMx->CR1);
	CONSOLE_PutMessage(inst, "CR2(0x%08lx): 0x%08lx\r\n", (u32)&(TIMxOffet->CR2), TIMx->CR2);
	CONSOLE_PutMessage(inst, "SMCR(0x%08lx): 0x%08lx\r\n", (u32)&(TIMxOffet->SMCR), TIMx->SMCR);
	CONSOLE_PutMessage(inst, "DIER(0x%08lx): 0x%08lx\r\n", (u32)&(TIMxOffet->DIER), TIMx->DIER);
	CONSOLE_PutMessage(inst, "SR(0x%08lx): 0x%08lx\r\n", (u32)&(TIMxOffet->SR), TIMx->SR);
	CONSOLE_PutMessage(inst, "EGR(0x%08lx): 0x%08lx\r\n", (u32)&(TIMxOffet->EGR), TIMx->EGR);	
	CONSOLE_PutMessage(inst, "CCMR1(0x%08lx): 0x%08lx\r\n", (u32)&(TIMxOffet->CCMR1), TIMx->CCMR1);	
	CONSOLE_PutMessage(inst, "CCMR2(0x%08lx): 0x%08lx\r\n", (u32)&(TIMxOffet->CCMR2), TIMx->CCMR2);	
	CONSOLE_PutMessage(inst, "CCER(0x%08lx): 0x%08lx\r\n", (u32)&(TIMxOffet->CCER), TIMx->CCER);		
	CONSOLE_PutMessage(inst, "CNT(0x%08lx): 0x%08lx\r\n", (u32)&(TIMxOffet->CNT), TIMx->CNT);	
	CONSOLE_PutMessage(inst, "PSC(0x%08lx): 0x%08lx\r\n", (u32)&(TIMxOffet->PSC), TIMx->PSC);	
	CONSOLE_PutMessage(inst, "ARR(0x%08lx): 0x%08lx\r\n", (u32)&(TIMxOffet->ARR), TIMx->ARR);		
//	CONSOLE_PutMessage(inst, "RCR(0x%08lx): 0x%08lx\r\n", (u32)&(TIMxOffet->RCR), TIMx->RCR);			
	CONSOLE_PutMessage(inst, "CCR1(0x%08lx): 0x%08lx\r\n", (u32)&(TIMxOffet->CCR1), TIMx->CCR1);		
	CONSOLE_PutMessage(inst, "CCR2(0x%08lx): 0x%08lx\r\n", (u32)&(TIMxOffet->CCR2), TIMx->CCR2);		
	CONSOLE_PutMessage(inst, "CCR3(0x%08lx): 0x%08lx\r\n", (u32)&(TIMxOffet->CCR3), TIMx->CCR3);		
	CONSOLE_PutMessage(inst, "CCR4(0x%08lx): 0x%08lx\r\n", (u32)&(TIMxOffet->CCR4), TIMx->CCR4);		
//	CONSOLE_PutMessage(inst, "BDTR(0x%08lx): 0x%08lx\r\n", (u32)&(TIMxOffet->BDTR), TIMx->BDTR);			
	CONSOLE_PutMessage(inst, "DCR(0x%08lx): 0x%08lx\r\n", (u32)&(TIMxOffet->DCR), TIMx->DCR);		
	CONSOLE_PutMessage(inst, "DMAR(0x%08lx): 0x%08lx\r\n", (u32)&(TIMxOffet->DMAR), TIMx->DMAR);		
	CONSOLE_PutMessage(inst, "OR(0x%08lx): 0x%08lx\r\n", (u32)&(TIMxOffet->OR), TIMx->OR);		
	return 0;
}

/*
 * ----------------------------------------------------------------------------
 * Function Name: clicmd_TIMxRegister()
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
static int clicmd_TIMxRegister(CONSOLE_Inst *inst, int argc, char **argv)
{
	u32 HexOffset, HexValue;
	u8 HexIndex;
	TIM_TypeDef *TIMx = 0;
	
	if (argc != 2 && argc != 4)
	{
		return -1;
	}
	else
	{
		/* Get instance index */	
		if (clicmd_HexText2Char((u8*)argv[1], &HexIndex, strlen(argv[1])) != 0)
		{
			return -1;
		}

		switch (HexIndex)
		{
		case 1:
			TIMx = TIM1;
			break;
		case 2:
			TIMx = TIM2;
			break;
		case 3:
			TIMx = TIM3;
			break;
		case 4:
			TIMx = TIM4;
			break;	
		case 6:
			TIMx = TIM6;
			break;
		case 7:
			TIMx = TIM7;
			break;
		case 8:
			TIMx = TIM8;
			break;
		default:
			return -1;
		}
	
		if (argc == 2)
		{
			clicmd_TIMxRegisterUsage(inst);

			CONSOLE_PutMessage(inst, "Current TIM%01d registers...\r\n", HexIndex);	
			clicmd_TIMxRegisterDisplay(inst, TIMx);
			return 1;
		}
	
		/* Get register offset */
		if (clicmd_HexText2Long((u8*)argv[2], &HexOffset, strlen(argv[2])) != 0)
		{
			return -1;
		}
	
		/* Get register value */	
		if (clicmd_HexText2Long((u8*)argv[3], &HexValue, strlen(argv[3])) != 0)
		{
			return -1;
		}
	
		/* Set register value */
		*((u32 *)(((u32)TIMx) + HexOffset)) = HexValue;

		CONSOLE_PutMessage(inst, "Write TIM%01d Register, Offset: 0x%08lx, vlaue: 0x%08lx\r\n", HexIndex, HexOffset, HexValue);	
		return 1;
	}
} /* End of clicmd_TIMxRegister() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: clicmd_TIMxRegisterHelp()
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
static int clicmd_TIMxRegisterHelp(CONSOLE_Inst *inst)
{
	CONSOLE_PutMessage(inst, "          timx: Access MCU TIMx registers\r\n");
	return 1;
} /* End of clicmd_TIMxRegisterHelp() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: clicmd_TIMxRegisterUsage()
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
static int clicmd_TIMxRegisterUsage(CONSOLE_Inst *inst)
{
	clicmd_TIMxRegisterHelp(inst);
	CONSOLE_PutMessage(inst, "Usage: timx <HexIndex> [<HexOffset> <HexValue>]\r\n");
	return 1;
} /* End of clicmd_TIMxRegisterUsage() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: clicmd_SPIxRegisterDisplay()
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
static int clicmd_SPIxRegisterDisplay(CONSOLE_Inst *inst, SPI_TypeDef* SPIx)
{
	SPI_TypeDef *SPIxOffet = 0;
	
	/* Show current settings */
	CONSOLE_PutMessage(inst, "SPI_CR1(0x%08lx): 0x%08lx\r\n", (u32)&(SPIxOffet->CR1), SPIx->CR1);
	CONSOLE_PutMessage(inst, "SPI_CR2(0x%08lx): 0x%08lx\r\n", (u32)&(SPIxOffet->CR2), SPIx->CR2);
	CONSOLE_PutMessage(inst, "SPI_SR(0x%08lx): 0x%08lx\r\n", (u32)&(SPIxOffet->SR), SPIx->SR);
	CONSOLE_PutMessage(inst, "SPI_DR(0x%08lx): 0x%08lx\r\n", (u32)&(SPIxOffet->DR), SPIx->DR);
	CONSOLE_PutMessage(inst, "SPI_CRCPR(0x%08lx): 0x%08lx\r\n", (u32)&(SPIxOffet->CRCPR), SPIx->CRCPR);
	CONSOLE_PutMessage(inst, "SPI_RXCRCR(0x%08lx): 0x%08lx\r\n", (u32)&(SPIxOffet->RXCRCR), SPIx->RXCRCR);
	CONSOLE_PutMessage(inst, "SPI_TXCRCR(0x%08lx): 0x%08lx\r\n", (u32)&(SPIxOffet->TXCRCR), SPIx->TXCRCR);	
	CONSOLE_PutMessage(inst, "SPI_I2SCFGR(0x%08lx): 0x%08lx\r\n", (u32)&(SPIxOffet->I2SCFGR), SPIx->I2SCFGR);	
	CONSOLE_PutMessage(inst, "SPI_I2SPR(0x%08lx): 0x%08lx\r\n", (u32)&(SPIxOffet->I2SPR), SPIx->I2SPR);	
	return 0;
}

/*
 * ----------------------------------------------------------------------------
 * Function Name: clicmd_SPIxRegister()
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
static int clicmd_SPIxRegister(CONSOLE_Inst *inst, int argc, char **argv)
{
	u32 HexOffset, HexValue;
	u8 HexIndex;
	SPI_TypeDef *SPIx = 0;
	
	if (argc != 2 && argc != 4)
	{
		return -1;
	}
	else
	{
		/* Get instance index */	
		if (clicmd_HexText2Char((u8*)argv[1], &HexIndex, strlen(argv[1])) != 0)
		{
			return -1;
		}

		switch (HexIndex)
		{
		case 1:
			SPIx = SPI1;
			break;
		case 2:
			SPIx = SPI2;
			break;
		case 3:
			SPIx = SPI3;
			break;
/*//not applicable

		case 4:
			SPIx = SPI4;
			break;
*/
		default:
			return 1;
		}
	
		if (argc == 2)
		{
			clicmd_SPIxRegisterUsage(inst);

			CONSOLE_PutMessage(inst, "Current SPI%01d registers...\r\n", HexIndex);	
			clicmd_SPIxRegisterDisplay(inst, SPIx);
			return 1;
		}
	
		/* Get register offset */
		if (clicmd_HexText2Long((u8*)argv[2], &HexOffset, strlen(argv[2])) != 0)
		{
			return -1;
		}
	
		/* Get register value */	
		if (clicmd_HexText2Long((u8*)argv[3], &HexValue, strlen(argv[3])) != 0)
		{
			return -1;
		}
	
		/* Set register value */
		*((u32 *)(((u32)SPIx) + HexOffset)) = HexValue;

		CONSOLE_PutMessage(inst, "Write SPI%01d Register, Offset: 0x%08lx, vlaue: 0x%08lx\r\n", HexIndex, HexOffset, HexValue);	
		return 1;
	}
} /* End of clicmd_SPIxRegister() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: clicmd_SPIxRegisterHelp()
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
static int clicmd_SPIxRegisterHelp(CONSOLE_Inst *inst)
{
	CONSOLE_PutMessage(inst, "          spix: Access MCU SPIx registers\r\n");
	return 1;
} /* End of clicmd_SPIxRegisterHelp() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: clicmd_SPIxRegisterUsage()
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
static int clicmd_SPIxRegisterUsage(CONSOLE_Inst *inst)
{
	clicmd_SPIxRegisterHelp(inst);
	CONSOLE_PutMessage(inst, "Usage: spix <HexIndex> [<HexOffset> <HexValue>]\r\n");
	return 1;
} /* End of clicmd_SPIxRegisterUsage() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: clicmd_RccRegisterDisplay()
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
static int clicmd_RccRegisterDisplay(CONSOLE_Inst *inst)
{
	RCC_TypeDef *RccOffet = 0;
	RCC_OscInitTypeDef RccOscInit;
	RCC_ClkInitTypeDef RccClkInit;
	uint32_t tmp32;
	
	/* Show current settings */
	CONSOLE_PutMessage(inst, "Current RCC registers...\r\n");		
	CONSOLE_PutMessage(inst, "CR(0x%08lx): 0x%08lx\r\n", (u32)&(RccOffet->CR), RCC->CR);
	CONSOLE_PutMessage(inst, "CFGR(0x%08lx): 0x%08lx\r\n", (u32)&(RccOffet->CFGR), RCC->CFGR);
	CONSOLE_PutMessage(inst, "CIR(0x%08lx): 0x%08lx\r\n", (u32)&(RccOffet->CIR), RCC->CIR);
	CONSOLE_PutMessage(inst, "APB1RSTR(0x%08lx): 0x%08lx\r\n", (u32)&(RccOffet->APB1RSTR), RCC->APB1RSTR);
	CONSOLE_PutMessage(inst, "APB2RSTR(0x%08lx): 0x%08lx\r\n", (u32)&(RccOffet->APB2RSTR), RCC->APB2RSTR);
	CONSOLE_PutMessage(inst, "AHB1ENR(0x%08lx): 0x%08lx\r\n", (u32)&(RccOffet->AHB1ENR), RCC->AHB1ENR);	
	CONSOLE_PutMessage(inst, "AHB2ENR(0x%08lx): 0x%08lx\r\n", (u32)&(RccOffet->AHB2ENR), RCC->AHB2ENR);	
	CONSOLE_PutMessage(inst, "AHB3ENR(0x%08lx): 0x%08lx\r\n", (u32)&(RccOffet->AHB3ENR), RCC->AHB3ENR);	
	CONSOLE_PutMessage(inst, "APB1ENR(0x%08lx): 0x%08lx\r\n", (u32)&(RccOffet->APB1ENR), RCC->APB1ENR);
	CONSOLE_PutMessage(inst, "APB2ENR(0x%08lx): 0x%08lx\r\n", (u32)&(RccOffet->APB2ENR), RCC->APB2ENR);
	CONSOLE_PutMessage(inst, "BDCR(0x%08lx): 0x%08lx\r\n", (u32)&(RccOffet->BDCR), RCC->BDCR);	
	CONSOLE_PutMessage(inst, "CSR(0x%08lx): 0x%08lx\r\n", (u32)&(RccOffet->CSR), RCC->CSR);	
	CONSOLE_PutMessage(inst, "AHB1RSTR(0x%08lx): 0x%08lx\r\n", (u32)&(RccOffet->AHB1RSTR), RCC->AHB1RSTR);	
	CONSOLE_PutMessage(inst, "AHB2RSTR(0x%08lx): 0x%08lx\r\n", (u32)&(RccOffet->AHB2RSTR), RCC->AHB2RSTR);	
	CONSOLE_PutMessage(inst, "AHB3RSTR(0x%08lx): 0x%08lx\r\n", (u32)&(RccOffet->AHB3RSTR), RCC->AHB3RSTR);	
	//CONSOLE_PutMessage(inst, "CFGR2(0x%08lx): 0x%08lx\r\n", (u32)&(RccOffet->CFGR2), RCC->CFGR2);	
	//CONSOLE_PutMessage(inst, "CFGR3(0x%08lx): 0x%08lx\r\n", (u32)&(RccOffet->CFGR3), RCC->CFGR3);	
	CONSOLE_PutMessage(inst, "\r\n");				
	
	CONSOLE_PutMessage(inst, "SYSCLK_Frequency = %d Hz\r\n", HAL_RCC_GetSysClockFreq());
	CONSOLE_PutMessage(inst, "HCLK_Frequency = %d Hz\r\n", HAL_RCC_GetHCLKFreq());
	CONSOLE_PutMessage(inst, "PCLK1_Frequency = %d Hz\r\n", HAL_RCC_GetPCLK1Freq());
	CONSOLE_PutMessage(inst, "PCLK2_Frequency = %d Hz\r\n", HAL_RCC_GetPCLK2Freq());

	HAL_RCC_GetOscConfig(&RccOscInit);
	HAL_RCC_GetClockConfig(&RccClkInit, &tmp32);

	return 0;
}

/*
 * ----------------------------------------------------------------------------
 * Function Name: clicmd_RccRegister()
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
static int clicmd_RccRegister(CONSOLE_Inst *inst, int argc, char **argv)
{
	u32 HexOffset, HexValue;
	u8 HexIndex;
	
	if (argc == 1)
	{
		clicmd_RccRegisterUsage(inst);
		clicmd_RccRegisterDisplay(inst);
		return 1;		
	}
	else if (argc != 3)
	{
		return -1;
	}
	
	/* Get register offset */
	if (clicmd_HexText2Long((u8*)argv[1], &HexOffset, strlen(argv[1])) != 0)
	{
		return -1;
	}
	
	/* Get register value */	
	if (clicmd_HexText2Long((u8*)argv[2], &HexValue, strlen(argv[2])) != 0)
	{
		return -1;
	}
	
	/* Set register value */
	*((u32 *)(((u32)RCC) + HexOffset)) = HexValue;

	CONSOLE_PutMessage(inst, "Write RCC Register, Offset: 0x%08lx, vlaue: 0x%08lx\r\n", HexIndex, HexOffset, HexValue);	
	return 1;
} /* End of clicmd_RccRegister() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: clicmd_RccRegisterHelp()
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
static int clicmd_RccRegisterHelp(CONSOLE_Inst *inst)
{
	CONSOLE_PutMessage(inst, "           rcc: Access MCU RCC registers\r\n");
	return 1;
} /* End of clicmd_RccRegisterHelp() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: clicmd_RccRegisterUsage()
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
static int clicmd_RccRegisterUsage(CONSOLE_Inst *inst)
{
	clicmd_RccRegisterHelp(inst);
	CONSOLE_PutMessage(inst, "Usage: rcc [<HexOffset> <HexValue>]\r\n");
	return 1;
} /* End of clicmd_RccRegisterUsage() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: clicmd_ExtiRegisterDisplay()
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
static int clicmd_ExtiRegisterDisplay(CONSOLE_Inst *inst)
{
	EXTI_TypeDef *ExtiOffet = 0;
		
	CONSOLE_PutMessage(inst, "Current EXTI registers...\r\n");		
	CONSOLE_PutMessage(inst, "IMR(0x%08lx): 0x%08lx\r\n", (u32)&(ExtiOffet->IMR), EXTI->IMR);
	CONSOLE_PutMessage(inst, "EMR(0x%08lx): 0x%08lx\r\n", (u32)&(ExtiOffet->EMR), EXTI->EMR);
	CONSOLE_PutMessage(inst, "RTSR(0x%08lx): 0x%08lx\r\n", (u32)&(ExtiOffet->RTSR), EXTI->RTSR);
	CONSOLE_PutMessage(inst, "FTSR(0x%08lx): 0x%08lx\r\n", (u32)&(ExtiOffet->FTSR), EXTI->FTSR);
	CONSOLE_PutMessage(inst, "SWIER(0x%08lx): 0x%08lx\r\n", (u32)&(ExtiOffet->SWIER), EXTI->SWIER);
	CONSOLE_PutMessage(inst, "PR(0x%08lx): 0x%08lx\r\n", (u32)&(ExtiOffet->PR), EXTI->PR);
/*
	CONSOLE_PutMessage(inst, "IMR2(0x%08lx): 0x%08lx\r\n", (u32)&(ExtiOffet->IMR2), EXTI->IMR2);
	CONSOLE_PutMessage(inst, "EMR2(0x%08lx): 0x%08lx\r\n", (u32)&(ExtiOffet->EMR2), EXTI->EMR2);
	CONSOLE_PutMessage(inst, "RTSR2(0x%08lx): 0x%08lx\r\n", (u32)&(ExtiOffet->RTSR2), EXTI->RTSR2);
	CONSOLE_PutMessage(inst, "FTSR2(0x%08lx): 0x%08lx\r\n", (u32)&(ExtiOffet->FTSR2), EXTI->FTSR2);
	CONSOLE_PutMessage(inst, "SWIER2(0x%08lx): 0x%08lx\r\n", (u32)&(ExtiOffet->SWIER2), EXTI->SWIER2);
	CONSOLE_PutMessage(inst, "PR2(0x%08lx): 0x%08lx\r\n", (u32)&(ExtiOffet->PR2), EXTI->PR2);
	CONSOLE_PutMessage(inst, "\r\n");				
*/
	return 0;
}

/*
 * ----------------------------------------------------------------------------
 * Function Name: clicmd_ExtiRegister()
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
static int clicmd_ExtiRegister(CONSOLE_Inst *inst, int argc, char **argv)
{
	u32 HexOffset, HexValue;
	u8 HexIndex;
	
	if (argc == 1)
	{
		clicmd_ExtiRegisterUsage(inst);
		clicmd_ExtiRegisterDisplay(inst);
		return 1;		
	}
	else if (argc != 3)
	{
		return -1;
	}
	
	/* Get register offset */
	if (clicmd_HexText2Long((u8*)argv[1], &HexOffset, strlen(argv[1])) != 0)
	{
		return -1;
	}
	
	/* Get register value */	
	if (clicmd_HexText2Long((u8*)argv[2], &HexValue, strlen(argv[2])) != 0)
	{
		return -1;
	}

	/* Set register value */
	*((u32 *)(((u32)EXTI) + HexOffset)) = HexValue;

	CONSOLE_PutMessage(inst, "Write EXTI Register, Offset: 0x%08lx, vlaue: 0x%08lx\r\n", HexIndex, HexOffset, HexValue);	
	return 1;
} /* End of clicmd_ExtiRegister() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: clicmd_ExtiRegisterHelp()
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
static int clicmd_ExtiRegisterHelp(CONSOLE_Inst *inst)
{
	CONSOLE_PutMessage(inst, "          exti: Access MCU EXTI registers\r\n");
	return 1;
} /* End of clicmd_ExtiRegisterHelp() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: clicmd_ExtiRegisterUsage()
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
static int clicmd_ExtiRegisterUsage(CONSOLE_Inst *inst)
{
	clicmd_ExtiRegisterHelp(inst);
	CONSOLE_PutMessage(inst, "Usage: exti [<HexOffset> <HexValue>]\r\n");
	return 1;
} /* End of clicmd_ExtiRegisterUsage() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: clicmd_GPIOxRegisterDisplay()
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
static int clicmd_GPIOxRegisterDisplay(CONSOLE_Inst *inst, u8 Port, GPIO_TypeDef *GPIOx)
{
	GPIO_TypeDef *GPIOxOffet = 0;
	
	CONSOLE_PutMessage(inst, "Current GPIO%c(0x%08lx) registers...\r\n", Port, (u32)GPIOx);		
	CONSOLE_PutMessage(inst, "MODER(0x%08lx): 0x%08lx\r\n", (u32)&(GPIOxOffet->MODER), GPIOx->MODER);
	CONSOLE_PutMessage(inst, "OTYPER(0x%08lx): 0x%08lx\r\n", (u32)&(GPIOxOffet->OTYPER), GPIOx->OTYPER);
	CONSOLE_PutMessage(inst, "OSPEEDR(0x%08lx): 0x%08lx\r\n", (u32)&(GPIOxOffet->OSPEEDR), GPIOx->OSPEEDR);
	CONSOLE_PutMessage(inst, "PUPDR(0x%08lx): 0x%08lx\r\n", (u32)&(GPIOxOffet->PUPDR), GPIOx->PUPDR);
	CONSOLE_PutMessage(inst, "IDR(0x%08lx): 0x%08lx\r\n", (u32)&(GPIOxOffet->IDR), GPIOx->IDR);
	CONSOLE_PutMessage(inst, "ODR(0x%08lx): 0x%08lx\r\n", (u32)&(GPIOxOffet->ODR), GPIOx->ODR);
	CONSOLE_PutMessage(inst, "BSRR(0x%08lx): 0x%08lx\r\n", (u32)&(GPIOxOffet->BSRR), GPIOx->BSRR);
	CONSOLE_PutMessage(inst, "LCKR(0x%08lx): 0x%08lx\r\n", (u32)&(GPIOxOffet->LCKR), GPIOx->LCKR);
	CONSOLE_PutMessage(inst, "AFR[0](0x%08lx): 0x%08lx\r\n", (u32)&(GPIOxOffet->AFR[0]), GPIOx->AFR[0]);
	CONSOLE_PutMessage(inst, "AFR[1](0x%08lx): 0x%08lx\r\n", (u32)&(GPIOxOffet->AFR[1]), GPIOx->AFR[1]);	
	CONSOLE_PutMessage(inst, "BSRR(0x%08lx): 0x%08lx\r\n", (u32)&(GPIOxOffet->BSRR), GPIOx->BSRR);	
	CONSOLE_PutMessage(inst, "\r\n");

	return 0;
}

/*
 * ----------------------------------------------------------------------------
 * Function Name: clicmd_GPIOxRegister()
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
static int clicmd_GPIOxRegister(CONSOLE_Inst *inst, int argc, char **argv)
{
	u32 HexOffset, HexValue;
	u8 HexPort;
	GPIO_TypeDef *GPIOx;
	
	if (argc == 1)
	{
		clicmd_GPIOxRegisterUsage(inst);
		return 1;		
	}
	else if (argc == 2)
	{
		HexPort = argv[1][0] & 0xdf;
	
		switch (HexPort)
		{
		case 'A': GPIOx = (GPIO_TypeDef*)GPIOA_BASE; break;
		case 'B': GPIOx = (GPIO_TypeDef*)GPIOB_BASE; break;
		case 'C': GPIOx = (GPIO_TypeDef*)GPIOC_BASE; break;
		case 'D': GPIOx = (GPIO_TypeDef*)GPIOD_BASE; break;
		case 'E': GPIOx = (GPIO_TypeDef*)GPIOE_BASE; break;
		case 'F': GPIOx = (GPIO_TypeDef*)GPIOF_BASE; break;
		case 'G': GPIOx = (GPIO_TypeDef*)GPIOG_BASE; break;
		case 'H': GPIOx = (GPIO_TypeDef*)GPIOH_BASE; break;
		default: return -1;
		}
		clicmd_GPIOxRegisterDisplay(inst, HexPort, (GPIO_TypeDef*)GPIOx);
		return 1;
	}
	else if (argc != 4)
	{
		return -1;
	}
	
	/* Get port index */
	if (strlen(argv[1]) != 1)
	{
		return -1;
	}

	HexPort = argv[1][0] & 0xdf;
	
	switch (HexPort)
	{
	case 'A': GPIOx = (GPIO_TypeDef*)GPIOA_BASE; break;
	case 'B': GPIOx = (GPIO_TypeDef*)GPIOB_BASE; break;
	case 'C': GPIOx = (GPIO_TypeDef*)GPIOC_BASE; break;
	case 'D': GPIOx = (GPIO_TypeDef*)GPIOD_BASE; break;
	case 'E': GPIOx = (GPIO_TypeDef*)GPIOE_BASE; break;
	case 'F': GPIOx = (GPIO_TypeDef*)GPIOF_BASE; break;
	case 'G': GPIOx = (GPIO_TypeDef*)GPIOG_BASE; break;
	case 'H': GPIOx = (GPIO_TypeDef*)GPIOH_BASE; break;
	default: return -1;		
	}
	
	/* Get register offset */
	if (clicmd_HexText2Long((u8*)argv[2], &HexOffset, strlen(argv[2])) != 0)
	{
		return -1;
	}
	
	/* Get register value */	
	if (clicmd_HexText2Long((u8*)argv[3], &HexValue, strlen(argv[3])) != 0)
	{
		return -1;
	}
	
	/* Set register value */
	*((u32 *)(((u32)GPIOx) + HexOffset)) = HexValue;

	CONSOLE_PutMessage(inst, "Write GPIO%c Register, Offset: 0x%08lx, vlaue: 0x%08lx\r\n", HexPort, HexOffset, HexValue);	
	return 1;
} /* End of clicmd_GPIOxRegister() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: clicmd_GPIOxRegisterHelp()
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
static int clicmd_GPIOxRegisterHelp(CONSOLE_Inst *inst)
{
	CONSOLE_PutMessage(inst, "         gpiox: Access MCU GPIOx registers\r\n");
	return 1;
} /* End of clicmd_GPIOxRegisterHelp() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: clicmd_GPIOxRegisterUsage()
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
static int clicmd_GPIOxRegisterUsage(CONSOLE_Inst *inst)
{
	clicmd_GPIOxRegisterHelp(inst);
	CONSOLE_PutMessage(inst, "Usage: gpiox [<HexPort> <HexOffset> <HexValue>]\r\n");
	return 1;
} /* End of clicmd_GPIOxRegisterUsage() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: clicmd_NvicRegisterDisplay()
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
static int clicmd_NvicRegisterDisplay(CONSOLE_Inst *inst)
{
	NVIC_Type *NvicOffet = 0;
	u32 i;
	
	CONSOLE_PutMessage(inst, "Current NVIC(0x%08lx) registers...\r\n", (u32)NVIC);		
	for (i=0; i<8; i++)
	{
		CONSOLE_PutMessage(inst, "ISER[%d](0x%08lx): 0x%08lx\r\n", i, (u32)&(NvicOffet->ISER[i]), NVIC->ISER[i]);
	}
	for (i=0; i<8; i++)
	{
		CONSOLE_PutMessage(inst, "ICER[%d](0x%08lx): 0x%08lx\r\n", i, (u32)&(NvicOffet->ICER[i]), NVIC->ICER[i]);
	}	
	for (i=0; i<8; i++)
	{
		CONSOLE_PutMessage(inst, "ISPR[%d](0x%08lx): 0x%08lx\r\n", i, (u32)&(NvicOffet->ISPR[i]), NVIC->ISPR[i]);
	}	
	for (i=0; i<8; i++)
	{
		CONSOLE_PutMessage(inst, "ICPR[%d](0x%08lx): 0x%08lx\r\n", i, (u32)&(NvicOffet->ICPR[i]), NVIC->ICPR[i]);
	}	
	for (i=0; i<8; i++)
	{
		CONSOLE_PutMessage(inst, "IABR[%d](0x%08lx): 0x%08lx\r\n", i, (u32)&(NvicOffet->IABR[i]), NVIC->IABR[i]);
	}	
	CONSOLE_PutMessage(inst, "\r\n");				

	
	return 0;
}

/*
 * ----------------------------------------------------------------------------
 * Function Name: clicmd_NvicRegister()
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
static int clicmd_NvicRegister(CONSOLE_Inst *inst, int argc, char **argv)
{
	u32 HexOffset, HexValue;
		
	if (argc == 1)
	{
		clicmd_NvicRegisterUsage(inst);
		clicmd_NvicRegisterDisplay(inst);		
		return 1;		
	}
	else if (argc != 3)
	{
		return -1;
	}
	
	/* Get register offset */
	if (clicmd_HexText2Long((u8*)argv[1], &HexOffset, strlen(argv[1])) != 0)
	{
		return -1;
	}
	
	/* Get register value */	
	if (clicmd_HexText2Long((u8*)argv[2], &HexValue, strlen(argv[2])) != 0)
	{
		return -1;
	}
	
	/* Set register value */
	*((u32 *)(((u32)NVIC) + HexOffset)) = HexValue;

	CONSOLE_PutMessage(inst, "Write MVIC Register, Offset: 0x%08lx, vlaue: 0x%08lx\r\n", HexOffset, HexValue);	
	return 1;
} /* End of clicmd_NvicRegister() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: clicmd_NvicRegisterHelp()
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
static int clicmd_NvicRegisterHelp(CONSOLE_Inst *inst)
{
	CONSOLE_PutMessage(inst, "          nvic: Access MCU NVIC registers\r\n");
	return 1;
} /* End of clicmd_NvicRegisterHelp() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: clicmd_NvicRegisterUsage()
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
static int clicmd_NvicRegisterUsage(CONSOLE_Inst *inst)
{
	clicmd_NvicRegisterHelp(inst);
	CONSOLE_PutMessage(inst, "Usage: nvic [<HexOffset> <HexValue>]\r\n");
	return 1;
} /* End of clicmd_NvicRegisterUsage() */

#endif

#if CLI_AX58100_DBG_CMD_ENABLE
/*
 * ----------------------------------------------------------------------------
 * Function Name: clicmd_AX58100RegisterDisplay()
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
static int clicmd_AX58100RegisterDisplay(CONSOLE_Inst *inst)
{
	u16 tmp16;
	
	/* Show current settings */
	CONSOLE_PutMessage(inst, "Current AX58100 registers: \r\n");
	
	/* Bridge */
	CONSOLE_PutMessage(inst, "Bridge Registers: \r\n");	
	AX_INTF_Read(INTCR, &tmp16, 2);
	CONSOLE_PutMessage(inst, "   INTCR(0x%04x): 0x%04x\r\n", INTCR, tmp16);
	
	AX_INTF_Read(INTSR, &tmp16, 2);
	CONSOLE_PutMessage(inst, "   INTSR(0x%04x): 0x%04x\r\n", INTSR, tmp16);
	
	AX_INTF_FunRead(ESTOR, &tmp16, 2);	
	CONSOLE_PutMessage(inst, "   ESTOR(0x%04x): 0x%04x\r\n", ESTOR, tmp16);
	
	AX_INTF_FunRead(HSTSR, &tmp16, 2);		
	CONSOLE_PutMessage(inst, "   HSTSR(0x%04x): 0x%04x\r\n", HSTSR, tmp16);
	CONSOLE_PutMessage(inst, "\r\n");
	
	/* MC */
	CONSOLE_PutMessage(inst, "MC Registers: \r\n");		
	AX_INTF_Read(MCTLR, &tmp16, 2);
	CONSOLE_PutMessage(inst, "   MCTLR(0x%04x): 0x%04x\r\n", MCTLR, tmp16);	

	AX_INTF_Read(PXCFGR, &tmp16, 2);
	CONSOLE_PutMessage(inst, "   PXCFGR(0x%04x): 0x%04x\r\n", PXCFGR, tmp16);

	AX_INTF_Read(PTAPPR, &tmp16, 2);
	CONSOLE_PutMessage(inst, "   PTAPPR(0x%04x): 0x%04x\r\n", PTAPPR, tmp16);
	
	AX_INTF_Read(PTBPPR, &tmp16, 2);
	CONSOLE_PutMessage(inst, "   PTBPPR(0x%04x): 0x%04x\r\n", PTBPPR, tmp16);

	AX_INTF_Read(PPCR, &tmp16, 2);
	CONSOLE_PutMessage(inst, "   PPCR(0x%04x): 0x%04x\r\n", PPCR, tmp16);
	
	AX_INTF_Read(PBBMR, &tmp16, 2);
	CONSOLE_PutMessage(inst, "   PBBMR(0x%04x): 0x%04x\r\n", PBBMR, tmp16);	

	AX_INTF_Read(P1CTRLR, &tmp16, 2);
	CONSOLE_PutMessage(inst, "   P1CTRLR(0x%04x): 0x%04x\r\n", P1CTRLR, tmp16);	

	AX_INTF_Read(P1SHR, &tmp16, 2);
	CONSOLE_PutMessage(inst, "   P1SHR(0x%04x): 0x%04x\r\n", P1SHR, tmp16);	

	AX_INTF_Read(P1HPWR, &tmp16, 2);
	CONSOLE_PutMessage(inst, "   P1HPWR(0x%04x): 0x%04x\r\n", P1HPWR, tmp16);	

	AX_INTF_Read(P2CTRLR, &tmp16, 2);
	CONSOLE_PutMessage(inst, "   P2CTRLR(0x%04x): 0x%04x\r\n", P2CTRLR, tmp16);	

	AX_INTF_Read(P2SHR, &tmp16, 2);
	CONSOLE_PutMessage(inst, "   P2SHR(0x%04x): 0x%04x\r\n", P2SHR, tmp16);	

	AX_INTF_Read(P2HPWR, &tmp16, 2);
	CONSOLE_PutMessage(inst, "   P2HPWR(0x%04x): 0x%04x\r\n", P2HPWR, tmp16);	

	AX_INTF_Read(P3CTRLR, &tmp16, 2);
	CONSOLE_PutMessage(inst, "   P3CTRLR(0x%04x): 0x%04x\r\n", P3CTRLR, tmp16);	

	AX_INTF_Read(P3SHR, &tmp16, 2);
	CONSOLE_PutMessage(inst, "   P3SHR(0x%04x): 0x%04x\r\n", P3SHR, tmp16);	

	AX_INTF_Read(P3HPWR, &tmp16, 2);
	CONSOLE_PutMessage(inst, "   P3HPWR(0x%04x): 0x%04x\r\n", P3HPWR, tmp16);	

	AX_INTF_Read(SGTLR, &tmp16, 2);
	CONSOLE_PutMessage(inst, "   SGTLR(0x%04x): 0x%04x\r\n", SGTLR, tmp16);	

	AX_INTF_Read(SGTHR, &tmp16, 2);
	CONSOLE_PutMessage(inst, "   SGTHR(0x%04x): 0x%04x\r\n", SGTHR, tmp16);	

	AX_INTF_Read(SHPWR, &tmp16, 2);
	CONSOLE_PutMessage(inst, "   SHPWR(0x%04x): 0x%04x\r\n", SHPWR, tmp16);	

	AX_INTF_Read(TDLYR, &tmp16, 2);
	CONSOLE_PutMessage(inst, "   TDLYR(0x%04x): 0x%04x\r\n", TDLYR, tmp16);	

	AX_INTF_Read(STNLR, &tmp16, 2);
	CONSOLE_PutMessage(inst, "   STNLR(0x%04x): 0x%04x\r\n", STNLR, tmp16);	

	AX_INTF_Read(STNHR, &tmp16, 2);
	CONSOLE_PutMessage(inst, "   STNHR(0x%04x): 0x%04x\r\n", STNHR, tmp16);	

	AX_INTF_Read(SCFGR, &tmp16, 2);
	CONSOLE_PutMessage(inst, "   SCFGR(0x%04x): 0x%04x\r\n", SCFGR, tmp16);	
	
	AX_INTF_Read(SCTRLR, &tmp16, 2);
	CONSOLE_PutMessage(inst, "   SCTRLR(0x%04x): 0x%04x\r\n", SCTRLR, tmp16);	

	AX_INTF_Read(SCNTLR, &tmp16, 2);
	CONSOLE_PutMessage(inst, "   SCNTLR(0x%04x): 0x%04x\r\n", SCNTLR, tmp16);	
	
	AX_INTF_Read(SCNTHR, &tmp16, 2);
	CONSOLE_PutMessage(inst, "   SCNTHR(0x%04x): 0x%04x\r\n", SCNTHR, tmp16);	
	CONSOLE_PutMessage(inst, "\r\n");
	
	/* ENC */	
	CONSOLE_PutMessage(inst, "ENC Registers:\r\n");
	AX_INTF_Read(ECNTVL, &tmp16, 2);
	CONSOLE_PutMessage(inst, "   ECNTVL(0x%04x):0x%04x\r\n", ECNTVL, tmp16);
	
	AX_INTF_Read(ECNTVH, &tmp16, 2);
	CONSOLE_PutMessage(inst, "   ECNTVH(0x%04x):0x%04x\r\n", ECNTVH, tmp16);
	
	AX_INTF_Read(ECNSTL, &tmp16, 2);
	CONSOLE_PutMessage(inst, "   ECNSTL(0x%04x):0x%04x\r\n", ECNSTL, tmp16);		
	
	AX_INTF_Read(ECNSTH, &tmp16, 2);
	CONSOLE_PutMessage(inst, "   ECNSTH(0x%04x):0x%04x\r\n", ECNSTH, tmp16);				
	
	AX_INTF_Read(ELATL, &tmp16, 2);
	CONSOLE_PutMessage(inst, "   ELATL(0x%04x):0x%04x\r\n", ELATL, tmp16);
	
	AX_INTF_Read(ELATH, &tmp16, 2);
	CONSOLE_PutMessage(inst, "   ELATH(0x%04x):0x%04x\r\n", ELATH, tmp16);
	
	AX_INTF_Read(EMOD, &tmp16, 2);
	CONSOLE_PutMessage(inst, "   EMOD(0x%04x):0x%04x\r\n", EMOD, tmp16);		
	
	AX_INTF_Read(ECLR, &tmp16, 2);
	CONSOLE_PutMessage(inst, "   ECLR(0x%04x):0x%04x\r\n", ECLR, tmp16);		
	
	AX_INTF_Read(HALLST, &tmp16, 2);	
	CONSOLE_PutMessage(inst, "   HALLST(0x%04x):0x%04x\r\n", HALLST, tmp16);			
	CONSOLE_PutMessage(inst, "\r\n");	
	
	/* SPIM */
	CONSOLE_PutMessage(inst, "SPIM Registers: \r\n");		
	AX_INTF_Read(SPICFGR, &tmp16, 2);
	CONSOLE_PutMessage(inst, "   SPICFGR(0x%04x): 0x%04x\r\n", SPICFGR, tmp16);		
	
	AX_INTF_Read(SPIBRR, &tmp16, 2);
	CONSOLE_PutMessage(inst, "   SPIBRR(0x%04x): 0x%04x\r\n", SPIBRR, tmp16);
	
	AX_INTF_Read(SPIDBSR, &tmp16, 2);
	CONSOLE_PutMessage(inst, "   SPIDBSR(0x%04x): 0x%04x\r\n", SPIDBSR, tmp16);

	AX_INTF_Read(SPIDTR, &tmp16, 2);
	CONSOLE_PutMessage(inst, "   SPIDTR(0x%04x): 0x%04x\r\n", SPIDTR, tmp16);
	
	AX_INTF_Read(SPIRPTR, &tmp16, 2);
	CONSOLE_PutMessage(inst, "   SPIRPTR(0x%04x): 0x%04x\r\n", SPIRPTR, tmp16);

	AX_INTF_Read(SPILTR, &tmp16, 2);
	CONSOLE_PutMessage(inst, "   SPILTR(0x%04x): 0x%04x\r\n", SPILTR, tmp16);
	
	AX_INTF_Read(SPIPRLR, &tmp16, 2);
	CONSOLE_PutMessage(inst, "   SPIPRLR(0x%04x): 0x%04x\r\n", SPIPRLR, tmp16);

	AX_INTF_Read(SPI01BCR, &tmp16, 2);
	CONSOLE_PutMessage(inst, "   SPI01BCR(0x%04x): 0x%04x\r\n", SPI01BCR, tmp16);
	
	AX_INTF_Read(SPI23BCR, &tmp16, 2);
	CONSOLE_PutMessage(inst, "   SPI23BCR(0x%04x): 0x%04x\r\n", SPI23BCR, tmp16);

	AX_INTF_Read(SPI45BCR, &tmp16, 2);
	CONSOLE_PutMessage(inst, "   SPI45BCR(0x%04x): 0x%04x\r\n", SPI45BCR, tmp16);
	
	AX_INTF_Read(SPI67BCR, &tmp16, 2);
	CONSOLE_PutMessage(inst, "   SPI67BCR(0x%04x): 0x%04x\r\n", SPI67BCR, tmp16);

	AX_INTF_Read(SPI03SSR, &tmp16, 2);
	CONSOLE_PutMessage(inst, "   SPI03SSR(0x%04x): 0x%04x\r\n", SPI03SSR, tmp16);
	
	AX_INTF_Read(SPI47SSR, &tmp16, 2);
	CONSOLE_PutMessage(inst, "   SPI47SSR(0x%04x): 0x%04x\r\n", SPI47SSR, tmp16);

	AX_INTF_Read(SPINTSR, &tmp16, 2);
	CONSOLE_PutMessage(inst, "   SPINTSR(0x%04x): 0x%04x\r\n", SPINTSR, tmp16);
	
	AX_INTF_Read(SPITSR, &tmp16, 2);
	CONSOLE_PutMessage(inst, "   SPITSR(0x%04x): 0x%04x\r\n", SPITSR, tmp16);

	AX_INTF_Read(SPIPOSR, &tmp16, 2);
	CONSOLE_PutMessage(inst, "   SPIPOSR(0x%04x): 0x%04x\r\n", SPIPOSR, tmp16);
	
	AX_INTF_Read(SPIDSR, &tmp16, 2);
	CONSOLE_PutMessage(inst, "   SPIDSR(0x%04x): 0x%04x\r\n", SPIDSR, tmp16);	

	AX_INTF_Read(SPIC0DR, &StrBuf, 8);
	CONSOLE_PutMessage(inst, "   SPIC0DR(0x%04x): 0x%08lx%08lx\r\n", SPIC0DR, *((u32*)&StrBuf[0]), *((u32*)&StrBuf[4]));	

	AX_INTF_Read(SPIC1DR, &StrBuf, 8);
	CONSOLE_PutMessage(inst, "   SPIC0DR(0x%04x): 0x%08lx%08lx\r\n", SPIC1DR, *((u32*)&StrBuf[0]), *((u32*)&StrBuf[4]));	

	AX_INTF_Read(SPIC2DR, &StrBuf, 8);
	CONSOLE_PutMessage(inst, "   SPIC2DR(0x%04x): 0x%08lx%08lx\r\n", SPIC2DR, *((u32*)&StrBuf[0]), *((u32*)&StrBuf[4]));	

	AX_INTF_Read(SPIC3DR, &StrBuf, 8);
	CONSOLE_PutMessage(inst, "   SPIC3DR(0x%04x): 0x%08lx%08lx\r\n", SPIC3DR, *((u32*)&StrBuf[0]), *((u32*)&StrBuf[4]));	

	AX_INTF_Read(SPIC4DR, &StrBuf, 8);
	CONSOLE_PutMessage(inst, "   SPIC4DR(0x%04x): 0x%08lx%08lx\r\n", SPIC4DR, *((u32*)&StrBuf[0]), *((u32*)&StrBuf[4]));	

	AX_INTF_Read(SPIC5DR, &StrBuf, 8);
	CONSOLE_PutMessage(inst, "   SPIC5DR(0x%04x): 0x%08lx%08lx\r\n", SPIC5DR, *((u32*)&StrBuf[0]), *((u32*)&StrBuf[4]));	

	AX_INTF_Read(SPIC6DR, &StrBuf, 8);
	CONSOLE_PutMessage(inst, "   SPIC6DR(0x%04x): 0x%08lx%08lx\r\n", SPIC6DR, *((u32*)&StrBuf[0]), *((u32*)&StrBuf[4]));	

	AX_INTF_Read(SPIC7DR, &StrBuf, 8);
	CONSOLE_PutMessage(inst, "   SPIC7DR(0x%04x): 0x%08lx%08lx\r\n", SPIC7DR, *((u32*)&StrBuf[0]), *((u32*)&StrBuf[4]));	

	AX_INTF_Read(SPIDSMR, &tmp16, 2);
	CONSOLE_PutMessage(inst, "   SPIDSMR(0x%04x): 0x%04x\r\n", SPIDSMR, tmp16);	

	AX_INTF_Read(SPIMCR, &tmp16, 2);
	CONSOLE_PutMessage(inst, "   SPIMCR(0x%04x): 0x%04x\r\n", SPIMCR, tmp16);
	return 0;
}

/*
 * ----------------------------------------------------------------------------
 * Function Name: clicmd_AX58100Register()
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
static int clicmd_AX58100Register(CONSOLE_Inst *inst, int argc, char **argv)
{
	
	if (argc == 1)
	{
		clicmd_AX58100RegisterUsage(inst);
		clicmd_AX58100RegisterDisplay(inst);
		return 1;
	}
	return -1;

} /* End of clicmd_AX58100Register() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: clicmd_AX58100RegisterHelp()
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
static int clicmd_AX58100RegisterHelp(CONSOLE_Inst *inst)
{
	CONSOLE_PutMessage(inst, "         axreg: Dump AX58100 registers\r\n");
	return 1;
} /* End of clicmd_AX58100RegisterHelp() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: clicmd_AX58100RegisterUsage()
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
static int clicmd_AX58100RegisterUsage(CONSOLE_Inst *inst)
{
	clicmd_AX58100RegisterHelp(inst);
	CONSOLE_PutMessage(inst, "Usage: axreg\r\n");
	return 1;
} /* End of clicmd_AX58100RegisterUsage() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: clicmd_ShowTestBuffer()
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
static int clicmd_ShowTestBuffer(CONSOLE_Inst *inst, TEST_CONTROL *pTestCtrl)
{
	TEST_TEMP *pTemp = &pTestCtrl->Temp;
	
	CONSOLE_PutMessage(inst, "Current transfer buffer content...\r\n");
	CONSOLE_PutMessage(inst, "StartAddress=0x%x, EndAddress=0x%x\r\n"
								, pTestCtrl->Parameter.StartAddress
								, pTestCtrl->Parameter.EndAddress
								);

	CONSOLE_PutMessage(inst, "TxLen=0x%x, TxBuf[]=\r\n", pTemp->TxLen);
	clicmd_ShowMemoryInHex8b(inst, pTemp->TxBuf, pTemp->TxLen);		
	
	CONSOLE_PutMessage(inst, "RxLen=0x%x, RxBuf[]=\r\n", pTemp->RxLen);
	clicmd_ShowMemoryInHex8b(inst, pTemp->RxBuf, pTemp->RxLen);		
	
	CONSOLE_PutMessage(inst, "\r\n");	
	return 0;
}

/*
 * ----------------------------------------------------------------------------
 * Function Name: clicmd_ShowTestTemporaryStatus()
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
static int clicmd_ShowTestTemporaryStatus(CONSOLE_Inst *inst, TEST_CONTROL *pTestCtrl)
{
	TEST_TEMP *pTemp = &pTestCtrl->Temp;
	
	CONSOLE_PutMessage(inst, "Current temporary status...\r\n");
	CONSOLE_PutMessage(inst, "  SPI DataSizeInWrite = %d\r\n", pTemp->Spis.DataSizeInWrite);
	CONSOLE_PutMessage(inst, "  SPI DataSizeInRead = %d\r\n", pTemp->Spis.DataSizeInRead);	
	CONSOLE_PutMessage(inst, "  SPI AddrSizeInWrite = %d\r\n", pTemp->Spis.AddrSizeInWrite);
	CONSOLE_PutMessage(inst, "  SPI AddrSizeInRead = %d\r\n", pTemp->Spis.AddrSizeInRead);
	
	CONSOLE_PutMessage(inst, "\r\n");	
	return 0;
}

/*
 * ----------------------------------------------------------------------------
 * Function Name: clicmd_ShowPdiMemoryTestLog()
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
static int clicmd_ShowPdiMemoryTestLog(CONSOLE_Inst *inst, TEST_CONTROL *pTestCtrl)
{
	int lineNum;
	TEST_TIME *pTime;
	TEST_TEMP *pTemp = &pTestCtrl->Temp;
	
	CONSOLE_PutMessage(inst, "PDI echo test log...\r\n");
	CONSOLE_PutMessage(inst, "DD:HH:MM:SS Round    Ok       Err      SpiWr/RdAddrSize SpiWr/RdDataSize HSTSR\r\n");
	lineNum	= 2;

	pTime = TEST_GetTime();
	CONSOLE_PutMessage(inst, "%02d:%02d:%02d:%02d %08lx %08lx %08lx %01d/%01d              %01d/%01d              %02x\r\n"
								, pTime->Day
								, pTime->Hour
								, pTime->Minute
								, pTime->Second
								, pTestCtrl->Record.RoundCnt
								, pTestCtrl->Record.OkCnt
								, pTestCtrl->Record.ErrorCnt
								, pTemp->Spis.AddrSizeInWrite
								, pTemp->Spis.AddrSizeInRead
								, pTemp->Spis.DataSizeInWrite
								, pTemp->Spis.DataSizeInRead
								, pTemp->HostInterfaceErrorStatus
								);								
	lineNum++;
	return lineNum;
}

/*
 * ----------------------------------------------------------------------------
 * Function Name: clicmd_ShowPdiMemoryTestParameter()
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
static int clicmd_ShowPdiMemoryTestParameter(CONSOLE_Inst *inst, TEST_CONTROL *pTestCtrl)
{
	TEST_PARAMETER *pParameter = &pTestCtrl->Parameter;
	
	CONSOLE_PutMessage(inst, "Your test parameter...\r\n");
	CONSOLE_PutMessage(inst, "-loop=0x%x, -sta=0x%x, -end=0x%x, -ptt=0x%x, -lut=%d, -dfm=0x%x, -dfmr=0x%x, -sam=0x%x\r\n"
								, pParameter->LoopCount
								, pParameter->StartAddress
								, pParameter->EndAddress
								, pParameter->PatternType	
								, pParameter->LogUpdateTime		
								, pParameter->Spis.DataSizeInWrite			
								, pParameter->Spis.DataSizeInRead				
								, pParameter->Spis.AddrSize
								);
	CONSOLE_PutMessage(inst, "-ptn(%dBytes)=", pParameter->InitDataLen);
	clicmd_ShowMemoryInHex8b(inst, pParameter->InitData, pParameter->InitDataLen);		
	
	CONSOLE_PutMessage(inst, "\r\n");	
	return 0;
}

/*
 * ----------------------------------------------------------------------------
 * Function Name: clicmd_PdiMemoryTest()
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
static int clicmd_PdiMemoryTest(CONSOLE_Inst *inst, int argc, char **argv)
{
	u8 lineNum;
	u32 i;
	TEST_PARAMETER *pParameter = &clicmd_testCtrl.Parameter;
	
	if (inst->State == CLI_STATE_COMMAND_WAIT)
	{
		if (inst->GetChar() == CLICMD_CTRL_C)
		{
			clicmd_testCtrl.Terminated = 1;
		}		
			
		TEST_PdiMemoryTest(&clicmd_testCtrl);			

		if (inst->Timer==0)
		{
			lineNum = clicmd_ShowPdiMemoryTestLog(inst, &clicmd_testCtrl);			
			if (clicmd_testCtrl.State == TEST_DONE)
			{
				inst->State = CLI_STATE_COMMAND;
				CONSOLE_PutMessage(inst, "\r\n");
				if (clicmd_testCtrl.Record.ErrorCnt)
				{
					clicmd_ShowTestBuffer(inst, &clicmd_testCtrl);				
					clicmd_ShowTestTemporaryStatus(inst, &clicmd_testCtrl);					
					return -1;
				}
				else
				{
					return 1;		
				}
			}
			else
			{			
				inst->PutChar(0x0D);
				while (lineNum--)
				{
					inst->PutChar(0x1B);
					inst->PutChar(0x5B);		
					inst->PutChar(0x41);					
				}
				inst->Timer = pParameter->LogUpdateTime;
			}
		}
		return 1;
	}
	else if (argc == 1)
	{
		clicmd_PdiMemoryTestUsage(inst);
		clicmd_ShowTestBuffer(inst, &clicmd_testCtrl);
		clicmd_ShowTestTemporaryStatus(inst, &clicmd_testCtrl);
		return 1;
	}
	else
	{
		memset((u8*)&clicmd_testCtrl, 0, sizeof(clicmd_testCtrl));
		
		/* Load default parameters */
		pParameter->LoopCount = TEST_DEF_LOOP_COUNT;
		pParameter->LogUpdateTime = TEST_DEF_LOG_UPDATE_TIME;
		pParameter->StartAddress = TEST_DEF_START_RAMADDR;
		pParameter->EndAddress = TEST_DEF_START_RAMADDR + TEST_DEF_RAM_SIZE;		
		pParameter->PatternType = TEST_DEF_PATTERN_TYPE;				
		pParameter->InitDataLen = 2;
		pParameter->InitData[0] = 0x55;		
		pParameter->InitData[1] = 0xAA;				
		pParameter->Spis.AddrSize = TEST_DEF_SPI_ADDR_SIZE;
		pParameter->Spis.DataSizeInWrite = TEST_DEF_SPI_DATA_SIZE_IN_WR;				
		pParameter->Spis.DataSizeInRead = TEST_DEF_SPI_DATA_SIZE_IN_RD;		
		pParameter->ChipSelectMode = 1;
		
		for (i=1; i<argc; i++)
		{
			if (!strcmp(argv[i], "-loop") && strlen(argv[i])==5)
			{
				i++;			
				if (clicmd_HexText2Long((u8*)argv[i], &pParameter->LoopCount, strlen(argv[i])) != 0)
				{
					return -1;
				}
			}
			else if (!strcmp(argv[i], "-lut") && strlen(argv[i])==4)
			{
				i++;
				if (clicmd_DecText2Long((u8*)argv[i], &pParameter->LogUpdateTime, strlen(argv[i])) != 0)
				{
					return -1;
				}
			}			
			else if (!strcmp(argv[i], "-sta") && strlen(argv[i])==4)
			{
				i++;
				if (clicmd_HexText2Long((u8*)argv[i], &pParameter->StartAddress, strlen(argv[i])) != 0)
				{
					return -1;
				}
			}		
			else if (!strcmp(argv[i], "-end") && strlen(argv[i])==4)
			{
				i++;
				if (clicmd_HexText2Long((u8*)argv[i], &pParameter->EndAddress, strlen(argv[i])) != 0)
				{
					return -1;
				}
			}
			else if (!strcmp(argv[i], "-ptt") && strlen(argv[i])==4)
			{
				i++;
				if (clicmd_HexText2Long((u8*)argv[i], &pParameter->PatternType, strlen(argv[i])) != 0)
				{
					return -1;
				}
			}
			else if (!strcmp(argv[i], "-ptn") && strlen(argv[i])==4)
			{
				i++;
				
					u8 *pbuf8 = pParameter->InitData;	
					pParameter->InitDataLen = 0;
					for (; i<argc; i++)
					{					
						if ((argv[i][0] == '-') ||
								(pParameter->InitDataLen >= TEST_INIT_DATA_BUF_SIZE) || 
								(clicmd_HexText2Char((u8*)argv[i], pbuf8, strlen(argv[i])) != 0))
						{
							i--;
							break;
						}
						pbuf8++;
						pParameter->InitDataLen++;						
					}					
			}
			else if (!strcmp(argv[i], "-dfm") && strlen(argv[i])==4)
			{
				i++;
				if (clicmd_HexText2Char((u8*)argv[i], (u8*)&pParameter->Spis.DataSizeInWrite, strlen(argv[i])) != 0)
				{
					return -1;
				}
			}
			else if (!strcmp(argv[i], "-dfmr") && strlen(argv[i])==5)
			{
				i++;
				if (clicmd_HexText2Char((u8*)argv[i], (u8*)&pParameter->Spis.DataSizeInRead, strlen(argv[i])) != 0)
				{
					return -1;
				}
			}			
			else if (!strcmp(argv[i], "-sam") && strlen(argv[i])==4)
			{
				i++;
				if (clicmd_HexText2Char((u8*)argv[i], (u8*)&pParameter->Spis.AddrSize, strlen(argv[i])) != 0)
				{
					return -1;
				}
			}
			else if (!strcmp(argv[i], "-csm") && strlen(argv[i])==4)
			{
				i++;
				if (clicmd_HexText2Char((u8*)argv[i], (u8*)&pParameter->ChipSelectMode, strlen(argv[i])) != 0)
				{
					return -1;
				}
			}			
			else if (!strcmp(argv[i], "-trg") && strlen(argv[i])==4)
			{
			  DBG_TriggerOutput(1);
				DBG_TriggerOutput(0);
				CONSOLE_PutMessage(inst, "Generate trigger output!\r\n");
				return 1;
			}			
			else
			{
				CONSOLE_PutMessage(inst, "Unsupported parameter:%s\r\n", argv[i]);				
				return -1;
			}
		}//for
		
		/* Parameter check */
		if (pParameter->StartAddress > pParameter->EndAddress)
		{
			CONSOLE_PutMessage(inst, "StartAddress cannot larger than EndAddress\r\n");			
			return -1;
		}
		
		clicmd_ShowPdiMemoryTestParameter(inst, &clicmd_testCtrl);
		CONSOLE_PutMessage(inst, "Start PDI memory test use %s chip select...\r\n"
											, pParameter->ChipSelectMode ? "ESC":"Function");
		inst->State = CLI_STATE_COMMAND_WAIT;		
	}

	return 1;
} /* End of clicmd_PdiMemoryTest() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: clicmd_PdiMemoryTestHelp()
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
static int clicmd_PdiMemoryTestHelp(CONSOLE_Inst *inst)
{
	CONSOLE_PutMessage(inst, "         pdimt: PDI memory access test\r\n");	
	return 1;
} /* End of clicmd_PdiMemoryTest() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: clicmd_PdiMemoryTestUsage()
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
static int clicmd_PdiMemoryTestUsage(CONSOLE_Inst *inst)
{
	clicmd_PdiMemoryTestHelp(inst);
	CONSOLE_PutMessage(inst, "Usage: pdimt [-loop HexValue] [-sta HexValue] [-end HexValue] [-ptt HexValue] [-ptn <HexValue0>...<HexValueN>]\r\n");
	CONSOLE_PutMessage(inst, "             [-lut DecValue] [-dfm HexValue] [-dfmr HexValue] [-sam HexValue] [-csm HexValue] [-trg]\r\n");	
	CONSOLE_PutMessage(inst, "       -loop: Specifies the number of test rounds.\r\n");	
	CONSOLE_PutMessage(inst, "              0: Infinite test, until press \"Ctrl-C\".\r\n");
	CONSOLE_PutMessage(inst, "              Default: %d\r\n", TEST_DEF_LOOP_COUNT);
	CONSOLE_PutMessage(inst, "       -lut: Specifies the update time of log, unit in 100ms\r\n");		
	CONSOLE_PutMessage(inst, "              Default: %d\r\n", TEST_DEF_LOG_UPDATE_TIME);		
	CONSOLE_PutMessage(inst, "       -sta: Specifies the start address of target memory to be test.\r\n");	
	CONSOLE_PutMessage(inst, "              Default: 0x%08lx\r\n", TEST_DEF_START_RAMADDR);	
	CONSOLE_PutMessage(inst, "       -end: Specifies the end address of target memory to be test.\r\n");		
	CONSOLE_PutMessage(inst, "              Default: 0x%08lx\r\n", TEST_DEF_START_RAMADDR + TEST_DEF_RAM_SIZE);
	CONSOLE_PutMessage(inst, "       -ptt: Specifies the data pattern type.\r\n");	
	CONSOLE_PutMessage(inst, "              0: Fixed, using \"-ptn\" parameter to specify pattern.\r\n");		
	CONSOLE_PutMessage(inst, "              1: Increment, using \"-ptn\" parameter to specify initial pattern.\r\n");			
	CONSOLE_PutMessage(inst, "              2: Decrement, using \"-ptn\" parameter to specify initial pattern.\r\n");		
	CONSOLE_PutMessage(inst, "              3: Random.\r\n");
	CONSOLE_PutMessage(inst, "              Default: %d\r\n", TEST_DEF_PATTERN_TYPE);
	CONSOLE_PutMessage(inst, "       -ptn: Specifies the pattern for \"Fixed\" type\r\n");		
	CONSOLE_PutMessage(inst, "             or initial pattern for other types.\r\n");
	CONSOLE_PutMessage(inst, "              Default: 0x55 0xAA\r\n");	
	CONSOLE_PutMessage(inst, "       -dfm: Specifies data fragment mode for ASIX_SPI/BECKHOFF_SPI write operation.\r\n");		
	CONSOLE_PutMessage(inst, "             this parameter is valid only for ASIX_SPI/BECKHOFF_SPI pdi mode.\r\n");
	CONSOLE_PutMessage(inst, "              0: Randomly change data fragment size being 1, 2 or 4Byte(s) for write operation\r\n");
	CONSOLE_PutMessage(inst, "              1: 1 byte write\r\n");
	CONSOLE_PutMessage(inst, "              2: 2 byte write\r\n");		
	CONSOLE_PutMessage(inst, "              3: 3 byte write\r\n");				
	CONSOLE_PutMessage(inst, "              4: 4 byte write\r\n");			
	CONSOLE_PutMessage(inst, "              N: N byte write\r\n");
	CONSOLE_PutMessage(inst, "              Default: %d\r\n", TEST_DEF_SPI_DATA_SIZE_IN_WR);
	CONSOLE_PutMessage(inst, "       -dfmr: Specifies data fragment mode for ASIX_SPI/BECKHOFF_SPI read operation.\r\n");		
	CONSOLE_PutMessage(inst, "             this parameter is valid only for ASIX_SPI/BECKHOFF_SPI pdi mode.\r\n");
	CONSOLE_PutMessage(inst, "              0: Randomly change data fragment size being 1, 2 or 4Byte(s) for read operation\r\n");
	CONSOLE_PutMessage(inst, "              1: 1 byte read\r\n");
	CONSOLE_PutMessage(inst, "              2: 2 byte read\r\n");		
	CONSOLE_PutMessage(inst, "              3: 3 byte read\r\n");				
	CONSOLE_PutMessage(inst, "              4: 4 byte read\r\n");			
	CONSOLE_PutMessage(inst, "              N: N byte read\r\n");
	CONSOLE_PutMessage(inst, "              Default: %d\r\n", TEST_DEF_SPI_DATA_SIZE_IN_RD);	
	CONSOLE_PutMessage(inst, "       -sam: Specifies ASIX_SPI/BECKHOFF_SPI address mode.\r\n");
	CONSOLE_PutMessage(inst, "             this parameter is valid only for ASIX_SPI/BECKHOFF_SPI pdi mode.\r\n");
	CONSOLE_PutMessage(inst, "              0: Randomly address byte size between 2, 3Bytes for write/read operation\r\n");
	CONSOLE_PutMessage(inst, "              2: 2 byte address\r\n");		
	CONSOLE_PutMessage(inst, "              3: 3 byte address\r\n");				
	CONSOLE_PutMessage(inst, "              Default: %d\r\n", TEST_DEF_SPI_ADDR_SIZE);
	CONSOLE_PutMessage(inst, "       -csm: Chip Select Mode.\r\n");	
	CONSOLE_PutMessage(inst, "             0: FUN_CS, 1: ESC_CS\r\n");			
	CONSOLE_PutMessage(inst, "       -trg: Trigger output test for debugging.\r\n");	
	CONSOLE_PutMessage(inst, "             Note: please connect PA.15 of Nucleo EVB. to trigger in of your instrument\r\n");			
	CONSOLE_PutMessage(inst, "\r\n");		
	return 1;
} /* End of clicmd_PdiMemoryTestUsage() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: clicmd_CiA402Status()
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
static int clicmd_CiA402Status(CONSOLE_Inst *inst, int argc, char **argv)
{
	u32 i;
	char *str;
	
#if (MC_STACK_ENABLE)	
	UI_Handle_t *pUI = &(GetMCP()->_Super);
#endif
	
#if (AX58100_DEBUG_ENABLE)
		HW_DEBUG *pDbgCnt;
		
		pDbgCnt = HW_GetDebugCounter();
		
		CONSOLE_PutMessage(inst, "EscIsrCnt=0x%08lx\r\n", pDbgCnt->EscIsrCnt);		
		CONSOLE_PutMessage(inst, "Sync0IsrCnt=0x%08lx\r\n", pDbgCnt->Sync0IsrCnt);	
		CONSOLE_PutMessage(inst, "Sync1IsrCnt=0x%08lx\r\n", pDbgCnt->Sync1IsrCnt);
		//CONSOLE_PutMessage(inst, "PdiReentryCnt=0x%08lx\r\n", *(HW_SpiObj[HW_ESC_PDI].pPdiReentryCnt));
		CONSOLE_PutMessage(inst, "EncIsrCnt=0x%08lx\r\n", pDbgCnt->EncIsrCnt);		
	
#endif	
	
//	CONSOLE_PutMessage(inst, "\r\n/* CiA402 Status */\r\n");	
//	CONSOLE_PutMessage(inst, "bDcSyncActive=%d\r\n", bDcSyncActive);	
//	for(i=0; i<MAX_AXES; i++)
//	{
//		
//		if(LocalAxes[i].bAxisIsActive)
//    {
//			CONSOLE_PutMessage(inst, "LocalAxes[%d] status:\r\n", i);			
//			CONSOLE_PutMessage(inst, "bAxisIsActive=%d,\r\n", LocalAxes[i].bAxisIsActive);
//			CONSOLE_PutMessage(inst, "bBrakeApplied=%d,\r\n", LocalAxes[i].bBrakeApplied);
//			CONSOLE_PutMessage(inst, "bLowLevelPowerApplied=%d,\r\n", LocalAxes[i].bLowLevelPowerApplied);			
//			CONSOLE_PutMessage(inst, "bHighLevelPowerApplied=%d,\r\n", LocalAxes[i].bHighLevelPowerApplied);			
//			CONSOLE_PutMessage(inst, "bAxisFunctionEnabled=%d,\r\n", LocalAxes[i].bAxisFunctionEnabled);						
//			CONSOLE_PutMessage(inst, "bConfigurationAllowed=%d,\r\n", LocalAxes[i].bConfigurationAllowed);
//			switch (LocalAxes[i].i16State)
//			{
//				case STATE_NOT_READY_TO_SWITCH_ON: str = "NOT_READY_TO_SWITCH_ON"; break;
//				case STATE_SWITCH_ON_DISABLED: str = "SWITCH_ON_DISABLED"; break;
//				case STATE_READY_TO_SWITCH_ON: str = "READY_TO_SWITCH_ON"; break;
//				case STATE_SWITCHED_ON: str = "SWITCHED_ON"; break;
//				case STATE_OPERATION_ENABLED: str = "OPERATION_ENABLED"; break;
//				case STATE_QUICK_STOP_ACTIVE: str = "QUICK_STOP_ACTIVE"; break;
//				case STATE_FAULT_REACTION_ACTIVE: str = "FAULT_REACTION_ACTIVE"; break;
//				case STATE_FAULT:	str = "FAULT"; break;
//			}
//			CONSOLE_PutMessage(inst, "i16State=0x%04x, %s\r\n", LocalAxes[i].i16State, str);
//			CONSOLE_PutMessage(inst, "u16PendingOptionCode=0x%04x,\r\n", LocalAxes[i].u16PendingOptionCode);
//			CONSOLE_PutMessage(inst, "u32CycleTime=%d,\r\n", LocalAxes[i].u32CycleTime);			
//			CONSOLE_PutMessage(inst, "\r\n");						

//			CONSOLE_PutMessage(inst, "objErrorCode=0x%04x,\r\n", LocalAxes[i].Objects.objErrorCode);
//			CONSOLE_PutMessage(inst, "objControlWord=0x%04x,\r\n", LocalAxes[i].Objects.objControlWord);
//			CONSOLE_PutMessage(inst, "objStatusWord=0x%04x,\r\n", LocalAxes[i].Objects.objStatusWord);
//			CONSOLE_PutMessage(inst, "objVlRampFunctionTime=0x%04x,\r\n", LocalAxes[i].Objects.objVlRampFunctionTime);			
//			CONSOLE_PutMessage(inst, "objQuickStopOptionCode=0x%04x,\r\n", LocalAxes[i].Objects.objQuickStopOptionCode);
//			CONSOLE_PutMessage(inst, "objShutdownOptionCode=0x%04x,\r\n", LocalAxes[i].Objects.objShutdownOptionCode);
//			CONSOLE_PutMessage(inst, "objDisableOperationOptionCode=0x%04x,\r\n", LocalAxes[i].Objects.objDisableOperationOptionCode);
//			CONSOLE_PutMessage(inst, "objFaultReactionCode=0x%04x,\r\n", LocalAxes[i].Objects.objFaultReactionCode);
//			CONSOLE_PutMessage(inst, "objModesOfOperation=0x%04x,\r\n", LocalAxes[i].Objects.objModesOfOperation);
//			CONSOLE_PutMessage(inst, "objModesOfOperationDisplay=0x%04x,\r\n", LocalAxes[i].Objects.objModesOfOperationDisplay);
//			CONSOLE_PutMessage(inst, "objPositionActualValue=0x%08lx,\r\n", LocalAxes[i].Objects.objPositionActualValue);
//			CONSOLE_PutMessage(inst, "objVelocityActualValue=0x%08lx,\r\n", LocalAxes[i].Objects.objVelocityActualValue);
//			CONSOLE_PutMessage(inst, "objTorqueActualValue=0x%04x,\r\n", LocalAxes[i].Objects.objTorqueActualValue);
//			CONSOLE_PutMessage(inst, "objTargetPosition=0x%08lx,\r\n", LocalAxes[i].Objects.objTargetPosition);		
////    TOBJ607D objSoftwarePositionLimit; /**< \brief Software Position limit (0x607D)*/
//			CONSOLE_PutMessage(inst, "objQuickStopDeclaration=0x%08lx,\r\n", LocalAxes[i].Objects.objQuickStopDeclaration);
// //   TOBJ60C2 objInterpolationTimePeriod; /**< \brief Interpolation Time Period (0x60C2)*/
//			CONSOLE_PutMessage(inst, "objTargetVelocity=0x%08lx,\r\n", LocalAxes[i].Objects.objTargetVelocity);		
//			CONSOLE_PutMessage(inst, "objSupportedDriveModes=0x%08lx,\r\n", LocalAxes[i].Objects.objSupportedDriveModes);		
//		}
	}

#if (MC_STACK_ENABLE)
	CONSOLE_PutMessage(inst, "\r\n/* FOC Stack Status */\r\n");
	switch(UI_GetReg(pUI, MC_PROTOCOL_REG_STATUS))
	{
	case ICLWAIT: str = "ICLWAIT"; break;
	case IDLE: str = "IDLE"; break;
	case IDLE_ALIGNMENT: str = "IDLE_ALIGNMENT"; break;
	case ALIGN_CHARGE_BOOT_CAP: str = "ALIGN_CHARGE_BOOT_CAP"; break;	  
	case ALIGN_OFFSET_CALIB: str = "ALIGN_OFFSET_CALIB"; break;
	case ALIGN_CLEAR: str = "ALIGN_CLEAR"; break;
	case ALIGNMENT: str = "ALIGNMENT"; break;
	case IDLE_START: str = "IDLE_START"; break;		
	case CHARGE_BOOT_CAP: str = "CHARGE_BOOT_CAP"; break;		
	case OFFSET_CALIB: str = "OFFSET_CALIB"; break;		
	case CLEAR: str = "CLEAR"; break;		
	case START: str = "START"; break;		
	case START_RUN: str = "START_RUN"; break;		
	case RUN: str = "RUN"; break;		
	case ANY_STOP: str = "ANY_STOP"; break;		
	case STOP: str = "STOP"; break;		
	case STOP_IDLE: str = "STOP_IDLE"; break;		
	case FAULT_NOW: str = "FAULT_NOW"; break;				
	case FAULT_OVER: str = "FAULT_OVER"; break;				  
	}
	
	CONSOLE_PutMessage(inst, "MC_PROTOCOL_REG_STATUS=%s\r\n", str);	
	
#endif

	return 1;
} /* End of clicmd_CiA402Status() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: clicmd_CiA402StatusHelp()
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
static int clicmd_CiA402StatusHelp(CONSOLE_Inst *inst)
{
	CONSOLE_PutMessage(inst, "           402: Shows CiA402 status and object dictionary\r\n");	
	return 1;
} /* End of clicmd_CiA402StatusHelp() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: clicmd_AccessCtrlConfig()
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
static int clicmd_AccessCtrlConfig(CONSOLE_Inst *inst, int argc, char **argv)
{
  u32 i;
  u8 tmp8;
	
	if (argc == 1)
	{
		clicmd_AccessCtrlConfigUsage(inst);
		clicmd_ShowAccessCtrlRegisters(inst);
		return 1;
	}

	for (i=1; i<argc; i++)
	{
		if (!strcmp(argv[i], "-mf") && strlen(argv[i])==3)
		{
			i++;
			if (clicmd_HexText2Char((u8*)argv[i], &tmp8, strlen(argv[i])) != 0)
			{
				return -1;
			}
			AX_INTF_EscWrite(FMIRER, &tmp8, 1);
		}
		else if (!strcmp(argv[i], "-or") && strlen(argv[i])==3)
		{
			i++;
			if (clicmd_HexText2Char((u8*)argv[i], &tmp8, strlen(argv[i])) != 0)
			{
				return -1;
			}
			AX_INTF_FunWrite(ESTOR, &tmp8, 1);
		}
		else
		{
			CONSOLE_PutMessage(inst, "Unsupported parameters.\r\n");								
			return -1;
		}
	}
	
	CONSOLE_PutMessage(inst, "       Your settings:\r\n");			
	clicmd_ShowAccessCtrlRegisters(inst);	
	return 1;
} /* End of clicmd_AccessCtrlConfig() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: clicmd_AccessCtrlConfigHelp()
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
static int clicmd_AccessCtrlConfigHelp(CONSOLE_Inst *inst)
{
	CONSOLE_PutMessage(inst, "         accfg: Access control register configuration\r\n");	
	return 1;
} /* End of clicmd_AccessCtrlConfigHelp() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: clicmd_AccessCtrlConfigUsage()
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
static int clicmd_AccessCtrlConfigUsage(CONSOLE_Inst *inst)
{
	clicmd_AccessCtrlConfigHelp(inst);
	
	CONSOLE_PutMessage(inst, "Usage: accfg [-mf HexValue] [-or HexValue]\r\n");
	CONSOLE_PutMessage(inst, "       -mf: MirrorFunctionConfig, Specify the value of mirror function register(ESC side 0x05C1).\r\n");		
	CONSOLE_PutMessage(inst, "       -or: OverrideConfig, Specify the value of ESC state override register(FUN side 0x0104).\r\n");			
	return 1;
} /* End of clicmd_AccessCtrlConfigUsage() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: clicmd_PdiReset()
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
static int clicmd_PdiReset(CONSOLE_Inst *inst, int argc, char **argv)
{
	u8 tmp8;
	
	tmp8 = 'R';
	AX_INTF_EscWrite(0x41, (u8*)&tmp8, 1);
	tmp8 = 'E';
	AX_INTF_EscWrite(0x41, (u8*)&tmp8, 1);
	tmp8 = 'S';
	AX_INTF_EscWrite(0x41, (u8*)&tmp8, 1);
	
	return 1;
} /* End of clicmd_PdiReset() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: clicmd_PdiResetHelp()
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
static int clicmd_PdiResetHelp(CONSOLE_Inst *inst)
{
	CONSOLE_PutMessage(inst, "        pdirst: Perform PDI reset\r\n");	
	return 1;
} /* End of clicmd_PdiResetHelp() */

#endif

/* End of clicmd.c */
