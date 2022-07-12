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
#ifndef __PRINTD_H__
#define __PRINTD_H__

/* INCLUDE FILE DECLARATIONS */
#include "ax_uart.h"

/* NAMING CONSTANT DECLARATIONS */
#define PRINTD_MESSAGE_LEN       512 
#define PRINTD_PUT_STRING        AX_UART_PutChar

/* TYPE DECLARATIONS */
																								
/* GLOBAL VARIABLES */

/* EXPORTED SUBPROGRAM SPECIFICATIONS */ 
short printd(const char *fmt, ...);

#endif /* __PRINTD_H__ */

/* End of printd.h */
