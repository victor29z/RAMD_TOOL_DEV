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
/*=============================================================================
 * Module Name: CONSOLE
 * Purpose: The purpose of this package provides the services to CONSOLE
 * Author:
 * Date:
 * Notes:
*=============================================================================
*/
#ifndef __CLICMD_H__
#define __CLICMD_H__

/* INCLUDE FILE DECLARATIONS */
#include "console.h"

/* NAMING CONSTANT DECLARATIONS */
#define CLI_MCU_DBG_CMD_ENABLE          0
#define CLI_AX58100_DBG_CMD_ENABLE      0

#define MAX_USER_ACCOUNT	   1
#define	BUF_LEN		           32
#define MAX_TEMP_BUF_SIZE	   1024

/* MACRO DECLARATIONS */

/* GLOBAL VARIABLES */
extern CONSOLE_Account CLICMD_userTable[];

/* EXPORTED SUBPROGRAM SPECIFICATIONS */ 
unsigned short CLICMD_GetCmdTableSize(void);
void* CLICMD_GetCmdTable(void);

#endif /* __CLICMD_H__ */

/* End of clicmd.h */
