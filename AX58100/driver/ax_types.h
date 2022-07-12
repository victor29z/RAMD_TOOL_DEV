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
#ifndef __AX_TYPES_H__
#define __AX_TYPES_H__

/* INCLUDE FILE DECLARATIONS */

/* NAMING CONSTANT DECLARATIONS */
#ifndef TRUE
#define TRUE  1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef NULL
#define NULL  0
#endif

#define BIT_0              0x00000001
#define BIT_1              0x00000002
#define BIT_2              0x00000004
#define BIT_3              0x00000008
#define BIT_4              0x00000010
#define BIT_5              0x00000020
#define BIT_6              0x00000040
#define BIT_7              0x00000080
#define BIT_8              0x00000100
#define BIT_9              0x00000200
#define BIT_10             0x00000400
#define BIT_11             0x00000800
#define BIT_12             0x00001000
#define BIT_13             0x00002000
#define BIT_14             0x00004000
#define BIT_15             0x00008000
#define BIT_16             0x00010000
#define BIT_17             0x00020000
#define BIT_18             0x00040000
#define BIT_19             0x00080000
#define BIT_20             0x00100000
#define BIT_21             0x00200000
#define BIT_22             0x00400000
#define BIT_23             0x00800000
#define BIT_24             0x01000000
#define BIT_25             0x02000000
#define BIT_26             0x04000000
#define BIT_27             0x08000000
#define BIT_28             0x10000000
#define BIT_29             0x20000000
#define BIT_30             0x40000000
#define BIT_31             0x80000000

typedef signed char        s8;
typedef signed short int   s16;
typedef signed int         s32;
typedef unsigned char      u8;
typedef unsigned short int u16;
typedef unsigned int       u32;

/* TYPE DECLARATIONS */
typedef enum
{
	AX_STATUS_OK                    =  0,
	AX_STATUS_ERR                   = -1,
	AX_STATUS_BUSY                  = -2,
	AX_STATUS_TIMEOUT               = -3,	
	AX_STATUS_TRG_PULSE_OVERRUN     = -4,		//SPI master trigger pulse overrun
	AX_STATUS_RX_BUF_OVERRUN        = -5,	
	AX_STATUS_TRG_PULSE_TIMEOUT     = -6,		//SPI master wait trigger pulse timeout
	AX_STATUS_RDY_PULSE_TIMEOUT     = -7,		//SPI master wait ready pulse timeout	
	AX_STATUS_COMPLETE_TIMEOUT      = -8,		//Check process timeout			

} AX_STATUS;

/* GLOBAL VARIABLES */

/* EXPORTED SUBPROGRAM SPECIFICATIONS */

#endif /* __AX_TYPES_H__ */

/* End of ax_types.h */
