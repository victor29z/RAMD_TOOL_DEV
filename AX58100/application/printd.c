/*
 ******************************************************************************
 *     Copyright (c) 2019	ASIX Electronic Corporation      All rights reserved.
 *
 *     This is unpublished proprietary source code of ASIX Electronic Corporation
 *
 *     The copyright notice above does not evidence any actual or intended
 *     publication of such source code.
 ******************************************************************************
 */

/* INCLUDE FILE DECLARATIONS */
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include "printd.h"

/* NAMING CONSTANT DECLARATIONS */

/* MACRO DECLARATIONS */

/* TYPE DECLARATIONS */

/* GLOBAL VARIABLES DECLARATIONS */

/* LOCAL VARIABLES DECLARATIONS */
static char pBuf[PRINTD_MESSAGE_LEN];

/* LOCAL SUBPROGRAM DECLARATIONS */
static short printd_PutString(char *strData, short len);

/* LOCAL SUBPROGRAM BODIES */
/*
 * ----------------------------------------------------------------------------
 * Function Name: printd_PutString()
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
static short printd_PutString(char *strData, short len)
{
    char *pStr=strData;
    
    if (!pStr)
        return -1;

    while (len-- >0)
    {
        PRINTD_PUT_STRING(*(unsigned char*)(pStr));
        pStr++;
    }
    return 1;	
} /* End of printd_PutString() */

/* EXPORTED SUBPROGRAM BODIES */

/*
 * ----------------------------------------------------------------------------
 * Function Name: printd()
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
short printd(const char *fmt, ...)
{
    short ret;
    va_list args;

    va_start(args, fmt);
    ret = vsprintf(pBuf,fmt,args);  /* process fmt & args into buf */
    printd_PutString(pBuf, ret);
    va_end(args);

    return ret;
} /* End of printd() */

/* End of printd.c */

