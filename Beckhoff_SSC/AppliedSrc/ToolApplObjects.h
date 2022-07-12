/**
* \addtogroup ToolAppl ToolAppl
* @{
*/
#include "ecat_def.h"
/**
\file ToolApplObjects
\author ET9300Utilities.ApplicationHandler (Version 1.3.6.0) | EthercatSSC@beckhoff.com

\brief ToolAppl specific objects<br>
\brief NOTE : This file will be overwritten if a new object dictionary is generated!<br>
*/

#if defined(_TOOL_APPL_) && (_TOOL_APPL_ == 1)
#define PROTO
#else
#define PROTO extern
#endif
/******************************************************************************
*                    Object 0x1600 : TERM_CTRL process data mapping
******************************************************************************/
/**
* \addtogroup 0x1600 0x1600 | TERM_CTRL process data mapping
* @{
* \brief Object 0x1600 (TERM_CTRL process data mapping) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1 - Reference to 0x7000.1<br>
* SubIndex 2 - Reference to 0x7000.2<br>
* SubIndex 3 - Reference to 0x7000.3<br>
* SubIndex 4 - Reference to 0x7000.4<br>
* SubIndex 5 - Reference to 0x7000.5<br>
* SubIndex 6 - Padding entry (13Bit)<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x1600[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex1 - Reference to 0x7000.1 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex2 - Reference to 0x7000.2 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex3 - Reference to 0x7000.3 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex4 - Reference to 0x7000.4 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex5 - Reference to 0x7000.5 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }}; /* Subindex6 - Padding entry (13Bit) */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x1600[] = "TERM_CTRL process data mapping\000"
"SubIndex 001\000"
"SubIndex 002\000"
"SubIndex 003\000"
"SubIndex 004\000"
"SubIndex 005\000"
"SubIndex 006\000\377";
#endif //#ifdef _OBJD_

#ifndef _TOOL_APPL_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
UINT32 SI1; /* Subindex1 - Reference to 0x7000.1 */
UINT32 SI2; /* Subindex2 - Reference to 0x7000.2 */
UINT32 SI3; /* Subindex3 - Reference to 0x7000.3 */
UINT32 SI4; /* Subindex4 - Reference to 0x7000.4 */
UINT32 SI5; /* Subindex5 - Reference to 0x7000.5 */
UINT32 SI6; /* Subindex6 - Padding entry (13Bit) */
} OBJ_STRUCT_PACKED_END
TOBJ1600;
#endif //#ifndef _TOOL_APPL_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ1600 TERM_CTRLProcessDataMapping0x1600
#if defined(_TOOL_APPL_) && (_TOOL_APPL_ == 1)
={6,0x70000108,0x70000208,0x70000301,0x70000401,0x70000501,0x0000000D}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x1A00 : MPU_STATUS process data mapping
******************************************************************************/
/**
* \addtogroup 0x1A00 0x1A00 | MPU_STATUS process data mapping
* @{
* \brief Object 0x1A00 (MPU_STATUS process data mapping) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1 - Reference to 0x6000.1<br>
* SubIndex 2 - Reference to 0x6000.2<br>
* SubIndex 3 - Reference to 0x6000.3<br>
* SubIndex 4 - Reference to 0x6000.4<br>
* SubIndex 5 - Reference to 0x6000.5<br>
* SubIndex 6 - Reference to 0x6000.6<br>
* SubIndex 7 - Reference to 0x6000.7<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x1A00[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex1 - Reference to 0x6000.1 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex2 - Reference to 0x6000.2 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex3 - Reference to 0x6000.3 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex4 - Reference to 0x6000.4 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex5 - Reference to 0x6000.5 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex6 - Reference to 0x6000.6 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }}; /* Subindex7 - Reference to 0x6000.7 */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x1A00[] = "MPU_STATUS process data mapping\000"
"SubIndex 001\000"
"SubIndex 002\000"
"SubIndex 003\000"
"SubIndex 004\000"
"SubIndex 005\000"
"SubIndex 006\000"
"SubIndex 007\000\377";
#endif //#ifdef _OBJD_

#ifndef _TOOL_APPL_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
UINT32 SI1; /* Subindex1 - Reference to 0x6000.1 */
UINT32 SI2; /* Subindex2 - Reference to 0x6000.2 */
UINT32 SI3; /* Subindex3 - Reference to 0x6000.3 */
UINT32 SI4; /* Subindex4 - Reference to 0x6000.4 */
UINT32 SI5; /* Subindex5 - Reference to 0x6000.5 */
UINT32 SI6; /* Subindex6 - Reference to 0x6000.6 */
UINT32 SI7; /* Subindex7 - Reference to 0x6000.7 */
} OBJ_STRUCT_PACKED_END
TOBJ1A00;
#endif //#ifndef _TOOL_APPL_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ1A00 MPU_STATUSProcessDataMapping0x1A00
#if defined(_TOOL_APPL_) && (_TOOL_APPL_ == 1)
={7,0x60000110,0x60000210,0x60000310,0x60000410,0x60000510,0x60000610,0x60000710}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x1A01 : FT_VALUES process data mapping
******************************************************************************/
/**
* \addtogroup 0x1A01 0x1A01 | FT_VALUES process data mapping
* @{
* \brief Object 0x1A01 (FT_VALUES process data mapping) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1 - Reference to 0x6010.1<br>
* SubIndex 2 - Reference to 0x6010.2<br>
* SubIndex 3 - Reference to 0x6010.3<br>
* SubIndex 4 - Reference to 0x6010.4<br>
* SubIndex 5 - Reference to 0x6010.5<br>
* SubIndex 6 - Reference to 0x6010.6<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x1A01[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex1 - Reference to 0x6010.1 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex2 - Reference to 0x6010.2 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex3 - Reference to 0x6010.3 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex4 - Reference to 0x6010.4 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex5 - Reference to 0x6010.5 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }}; /* Subindex6 - Reference to 0x6010.6 */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x1A01[] = "FT_VALUES process data mapping\000"
"SubIndex 001\000"
"SubIndex 002\000"
"SubIndex 003\000"
"SubIndex 004\000"
"SubIndex 005\000"
"SubIndex 006\000\377";
#endif //#ifdef _OBJD_

#ifndef _TOOL_APPL_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
UINT32 SI1; /* Subindex1 - Reference to 0x6010.1 */
UINT32 SI2; /* Subindex2 - Reference to 0x6010.2 */
UINT32 SI3; /* Subindex3 - Reference to 0x6010.3 */
UINT32 SI4; /* Subindex4 - Reference to 0x6010.4 */
UINT32 SI5; /* Subindex5 - Reference to 0x6010.5 */
UINT32 SI6; /* Subindex6 - Reference to 0x6010.6 */
} OBJ_STRUCT_PACKED_END
TOBJ1A01;
#endif //#ifndef _TOOL_APPL_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ1A01 FT_VALUESProcessDataMapping0x1A01
#if defined(_TOOL_APPL_) && (_TOOL_APPL_ == 1)
={6,0x60100110,0x60100210,0x60100310,0x60100410,0x60100510,0x60100610}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x1A02 : IO_STATUS process data mapping
******************************************************************************/
/**
* \addtogroup 0x1A02 0x1A02 | IO_STATUS process data mapping
* @{
* \brief Object 0x1A02 (IO_STATUS process data mapping) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1 - Reference to 0x6020.1<br>
* SubIndex 2 - Reference to 0x6020.2<br>
* SubIndex 3 - Reference to 0x6020.3<br>
* SubIndex 4 - Reference to 0x6020.4<br>
* SubIndex 5 - Padding entry (14Bit)<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x1A02[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex1 - Reference to 0x6020.1 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex2 - Reference to 0x6020.2 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex3 - Reference to 0x6020.3 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex4 - Reference to 0x6020.4 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }}; /* Subindex5 - Padding entry (14Bit) */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x1A02[] = "IO_STATUS process data mapping\000"
"SubIndex 001\000"
"SubIndex 002\000"
"SubIndex 003\000"
"SubIndex 004\000"
"SubIndex 005\000\377";
#endif //#ifdef _OBJD_

#ifndef _TOOL_APPL_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
UINT32 SI1; /* Subindex1 - Reference to 0x6020.1 */
UINT32 SI2; /* Subindex2 - Reference to 0x6020.2 */
UINT32 SI3; /* Subindex3 - Reference to 0x6020.3 */
UINT32 SI4; /* Subindex4 - Reference to 0x6020.4 */
UINT32 SI5; /* Subindex5 - Padding entry (14Bit) */
} OBJ_STRUCT_PACKED_END
TOBJ1A02;
#endif //#ifndef _TOOL_APPL_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ1A02 IO_STATUSProcessDataMapping0x1A02
#if defined(_TOOL_APPL_) && (_TOOL_APPL_ == 1)
={5,0x60200110,0x60200210,0x60200301,0x60200401,0x0000000E}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x1C12 : SyncManager 2 assignment
******************************************************************************/
/**
* \addtogroup 0x1C12 0x1C12 | SyncManager 2 assignment
* @{
* \brief Object 0x1C12 (SyncManager 2 assignment) definition
*/
#ifdef _OBJD_
/**
* \brief Entry descriptions<br>
* 
* Subindex 0<br>
* Subindex 1 - n (the same entry description is used)<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x1C12[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READ }};

/**
* \brief Object name definition<br>
* For Subindex 1 to n the syntax 'Subindex XXX' is used
*/
OBJCONST UCHAR OBJMEM aName0x1C12[] = "SyncManager 2 assignment\000\377";
#endif //#ifdef _OBJD_

#ifndef _TOOL_APPL_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16   u16SubIndex0;  /**< \brief Subindex 0 */
UINT16 aEntries[1];  /**< \brief Subindex 1 - 1 */
} OBJ_STRUCT_PACKED_END
TOBJ1C12;
#endif //#ifndef _TOOL_APPL_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ1C12 sRxPDOassign
#if defined(_TOOL_APPL_) && (_TOOL_APPL_ == 1)
={1,{0x1600}}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x1C13 : SyncManager 3 assignment
******************************************************************************/
/**
* \addtogroup 0x1C13 0x1C13 | SyncManager 3 assignment
* @{
* \brief Object 0x1C13 (SyncManager 3 assignment) definition
*/
#ifdef _OBJD_
/**
* \brief Entry descriptions<br>
* 
* Subindex 0<br>
* Subindex 1 - n (the same entry description is used)<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x1C13[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READ }};

/**
* \brief Object name definition<br>
* For Subindex 1 to n the syntax 'Subindex XXX' is used
*/
OBJCONST UCHAR OBJMEM aName0x1C13[] = "SyncManager 3 assignment\000\377";
#endif //#ifdef _OBJD_

#ifndef _TOOL_APPL_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16   u16SubIndex0;  /**< \brief Subindex 0 */
UINT16 aEntries[3];  /**< \brief Subindex 1 - 3 */
} OBJ_STRUCT_PACKED_END
TOBJ1C13;
#endif //#ifndef _TOOL_APPL_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ1C13 sTxPDOassign
#if defined(_TOOL_APPL_) && (_TOOL_APPL_ == 1)
={3,{0x1A00,0x1A01,0x1A02}}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x6000 : MPU_STATUS
******************************************************************************/
/**
* \addtogroup 0x6000 0x6000 | MPU_STATUS
* @{
* \brief Object 0x6000 (MPU_STATUS) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1 - MPU_ACC_X_DATA<br>
* SubIndex 2 - MPU_ACC_Y_DATA<br>
* SubIndex 3 - MPU_ACC_Z_DATA<br>
* SubIndex 4 - MPU_GYR_X_DATA<br>
* SubIndex 5 - MPU_GYR_Y_DATA<br>
* SubIndex 6 - MPU_GYR_Z_DATA<br>
* SubIndex 7 - MPU_TEMP_DATA<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x6000[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READ | OBJACCESS_TXPDOMAPPING }, /* Subindex1 - MPU_ACC_X_DATA */
{ DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READ | OBJACCESS_TXPDOMAPPING }, /* Subindex2 - MPU_ACC_Y_DATA */
{ DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READ | OBJACCESS_TXPDOMAPPING }, /* Subindex3 - MPU_ACC_Z_DATA */
{ DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READ | OBJACCESS_TXPDOMAPPING }, /* Subindex4 - MPU_GYR_X_DATA */
{ DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READ | OBJACCESS_TXPDOMAPPING }, /* Subindex5 - MPU_GYR_Y_DATA */
{ DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READ | OBJACCESS_TXPDOMAPPING }, /* Subindex6 - MPU_GYR_Z_DATA */
{ DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READ | OBJACCESS_TXPDOMAPPING }}; /* Subindex7 - MPU_TEMP_DATA */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x6000[] = "MPU_STATUS\000"
"MPU_ACC_X_DATA\000"
"MPU_ACC_Y_DATA\000"
"MPU_ACC_Z_DATA\000"
"MPU_GYR_X_DATA\000"
"MPU_GYR_Y_DATA\000"
"MPU_GYR_Z_DATA\000"
"MPU_TEMP_DATA\000\377";
#endif //#ifdef _OBJD_

#ifndef _TOOL_APPL_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
UINT16 wMPU_ACC_X_DATA; /* Subindex1 - MPU_ACC_X_DATA */
UINT16 wMPU_ACC_Y_DATA; /* Subindex2 - MPU_ACC_Y_DATA */
UINT16 wMPU_ACC_Z_DATA; /* Subindex3 - MPU_ACC_Z_DATA */
UINT16 wMPU_GYR_X_DATA; /* Subindex4 - MPU_GYR_X_DATA */
UINT16 wMPU_GYR_Y_DATA; /* Subindex5 - MPU_GYR_Y_DATA */
UINT16 wMPU_GYR_Z_DATA; /* Subindex6 - MPU_GYR_Z_DATA */
UINT16 wMPU_TEMP_DATA; /* Subindex7 - MPU_TEMP_DATA */
} OBJ_STRUCT_PACKED_END
TOBJ6000;
#endif //#ifndef _TOOL_APPL_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ6000 MPU_STATUS0x6000
#if defined(_TOOL_APPL_) && (_TOOL_APPL_ == 1)
={7,0,0,0,0,0,0,0}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x6010 : FT_VALUES
******************************************************************************/
/**
* \addtogroup 0x6010 0x6010 | FT_VALUES
* @{
* \brief Object 0x6010 (FT_VALUES) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1 - FT_FX_DATA<br>
* SubIndex 2 - FT_FY_DATA<br>
* SubIndex 3 - FT_FZ_DATA<br>
* SubIndex 4 - FT_TX_DATA<br>
* SubIndex 5 - FT_TY_DATA<br>
* SubIndex 6 - FT_TZ_DATA<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x6010[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READ | OBJACCESS_TXPDOMAPPING }, /* Subindex1 - FT_FX_DATA */
{ DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READ | OBJACCESS_TXPDOMAPPING }, /* Subindex2 - FT_FY_DATA */
{ DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READ | OBJACCESS_TXPDOMAPPING }, /* Subindex3 - FT_FZ_DATA */
{ DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READ | OBJACCESS_TXPDOMAPPING }, /* Subindex4 - FT_TX_DATA */
{ DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READ | OBJACCESS_TXPDOMAPPING }, /* Subindex5 - FT_TY_DATA */
{ DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READ | OBJACCESS_TXPDOMAPPING }}; /* Subindex6 - FT_TZ_DATA */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x6010[] = "FT_VALUES\000"
"FT_FX_DATA\000"
"FT_FY_DATA\000"
"FT_FZ_DATA\000"
"FT_TX_DATA\000"
"FT_TY_DATA\000"
"FT_TZ_DATA\000\377";
#endif //#ifdef _OBJD_

#ifndef _TOOL_APPL_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
UINT16 FT_FX_DATA; /* Subindex1 - FT_FX_DATA */
UINT16 FT_FY_DATA; /* Subindex2 - FT_FY_DATA */
UINT16 FT_FZ_DATA; /* Subindex3 - FT_FZ_DATA */
UINT16 FT_TX_DATA; /* Subindex4 - FT_TX_DATA */
UINT16 FT_TY_DATA; /* Subindex5 - FT_TY_DATA */
UINT16 FT_TZ_DATA; /* Subindex6 - FT_TZ_DATA */
} OBJ_STRUCT_PACKED_END
TOBJ6010;
#endif //#ifndef _TOOL_APPL_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ6010 FT_VALUES0x6010
#if defined(_TOOL_APPL_) && (_TOOL_APPL_ == 1)
={6,0,0,0,0,0,0}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x6020 : IO_STATUS
******************************************************************************/
/**
* \addtogroup 0x6020 0x6020 | IO_STATUS
* @{
* \brief Object 0x6020 (IO_STATUS) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1 - AI0_VALUE<br>
* SubIndex 2 - AI1_VALUE<br>
* SubIndex 3 - TI0_VALUE<br>
* SubIndex 4 - TI1_VALUE<br>
* SubIndex 5<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x6020[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READ | OBJACCESS_TXPDOMAPPING }, /* Subindex1 - AI0_VALUE */
{ DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READ | OBJACCESS_TXPDOMAPPING }, /* Subindex2 - AI1_VALUE */
{ DEFTYPE_BOOLEAN , 0x1 , ACCESS_READ | OBJACCESS_TXPDOMAPPING }, /* Subindex3 - TI0_VALUE */
{ DEFTYPE_BOOLEAN , 0x1 , ACCESS_READ | OBJACCESS_TXPDOMAPPING }, /* Subindex4 - TI1_VALUE */
{ DEFTYPE_NULL , 0xE , ACCESS_READ | OBJACCESS_TXPDOMAPPING }}; /* Subindex5 */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x6020[] = "IO_STATUS\000"
"AI0_VALUE\000"
"AI1_VALUE\000"
"TI0_VALUE\000"
"TI1_VALUE\000"
"\000\377";
#endif //#ifdef _OBJD_

#ifndef _TOOL_APPL_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
UINT16 AI0_VALUE; /* Subindex1 - AI0_VALUE */
UINT16 AI1_VALUE; /* Subindex2 - AI1_VALUE */
BOOLEAN(TI0_VALUE); /* Subindex3 - TI0_VALUE */
BOOLEAN(TI1_VALUE); /* Subindex4 - TI1_VALUE */
ALIGN14(SI5) /* Subindex5 */
} OBJ_STRUCT_PACKED_END
TOBJ6020;
#endif //#ifndef _TOOL_APPL_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ6020 IO_STATUS0x6020
#if defined(_TOOL_APPL_) && (_TOOL_APPL_ == 1)
={5,0,0,0,0,0}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x7000 : TERM_CTRL
******************************************************************************/
/**
* \addtogroup 0x7000 0x7000 | TERM_CTRL
* @{
* \brief Object 0x7000 (TERM_CTRL) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1 - TMUX1_CH<br>
* SubIndex 2 - TMUX2_CH<br>
* SubIndex 3 - TO0<br>
* SubIndex 4 - TO1<br>
* SubIndex 5 - TPWR_EN<br>
* SubIndex 6<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x7000[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING }, /* Subindex1 - TMUX1_CH */
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING }, /* Subindex2 - TMUX2_CH */
{ DEFTYPE_BOOLEAN , 0x1 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING }, /* Subindex3 - TO0 */
{ DEFTYPE_BOOLEAN , 0x1 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING }, /* Subindex4 - TO1 */
{ DEFTYPE_BOOLEAN , 0x1 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING }, /* Subindex5 - TPWR_EN */
{ DEFTYPE_NULL , 0xD , 0x0000 }}; /* Subindex6 */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x7000[] = "TERM_CTRL\000"
"TMUX1_CH\000"
"TMUX2_CH\000"
"TO0\000"
"TO1\000"
"TPWR_EN\000"
"\000\377";
#endif //#ifdef _OBJD_

#ifndef _TOOL_APPL_OBJECTS_H_
/**
* \brief Object structure
*/

typedef struct OBJ_STRUCT_PACKED_START {
#pragma pack (1)
UINT16 u16SubIndex0;
UINT8 TMUX1_CH; /* Subindex1 - TMUX1_CH */
UINT8 TMUX2_CH; /* Subindex2 - TMUX2_CH */
BOOLEAN(TO0); /* Subindex3 - TO0 */
BOOLEAN(TO1); /* Subindex4 - TO1 */
BOOLEAN(TPWR_EN); /* Subindex5 - TPWR_EN */
ALIGN13(SI6) /* Subindex6 */
#pragma pack ()
} OBJ_STRUCT_PACKED_END
TOBJ7000;

#endif //#ifndef _TOOL_APPL_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ7000 TERM_CTRL0x7000
#if defined(_TOOL_APPL_) && (_TOOL_APPL_ == 1)
={6,0,0,0,0,0,0}
#endif
;
/** @}*/







#ifdef _OBJD_
TOBJECT    OBJMEM ApplicationObjDic[] = {
/* Object 0x1600 */
{NULL , NULL ,  0x1600 , {DEFTYPE_PDOMAPPING , 6 | (OBJCODE_REC << 8)} , asEntryDesc0x1600 , aName0x1600 , &TERM_CTRLProcessDataMapping0x1600, NULL , NULL , 0x0000 },
/* Object 0x1A00 */
{NULL , NULL ,  0x1A00 , {DEFTYPE_PDOMAPPING , 7 | (OBJCODE_REC << 8)} , asEntryDesc0x1A00 , aName0x1A00 , &MPU_STATUSProcessDataMapping0x1A00, NULL , NULL , 0x0000 },
/* Object 0x1A01 */
{NULL , NULL ,  0x1A01 , {DEFTYPE_PDOMAPPING , 6 | (OBJCODE_REC << 8)} , asEntryDesc0x1A01 , aName0x1A01 , &FT_VALUESProcessDataMapping0x1A01, NULL , NULL , 0x0000 },
/* Object 0x1A02 */
{NULL , NULL ,  0x1A02 , {DEFTYPE_PDOMAPPING , 5 | (OBJCODE_REC << 8)} , asEntryDesc0x1A02 , aName0x1A02 , &IO_STATUSProcessDataMapping0x1A02, NULL , NULL , 0x0000 },
/* Object 0x1C12 */
{NULL , NULL ,  0x1C12 , {DEFTYPE_UNSIGNED16 , 1 | (OBJCODE_ARR << 8)} , asEntryDesc0x1C12 , aName0x1C12 , &sRxPDOassign, NULL , NULL , 0x0000 },
/* Object 0x1C13 */
{NULL , NULL ,  0x1C13 , {DEFTYPE_UNSIGNED16 , 3 | (OBJCODE_ARR << 8)} , asEntryDesc0x1C13 , aName0x1C13 , &sTxPDOassign, NULL , NULL , 0x0000 },
/* Object 0x6000 */
{NULL , NULL ,  0x6000 , {DEFTYPE_RECORD , 7 | (OBJCODE_REC << 8)} , asEntryDesc0x6000 , aName0x6000 , &MPU_STATUS0x6000, NULL , NULL , 0x0000 },
/* Object 0x6010 */
{NULL , NULL ,  0x6010 , {DEFTYPE_RECORD , 6 | (OBJCODE_REC << 8)} , asEntryDesc0x6010 , aName0x6010 , &FT_VALUES0x6010, NULL , NULL , 0x0000 },
/* Object 0x6020 */
{NULL , NULL ,  0x6020 , {DEFTYPE_RECORD , 5 | (OBJCODE_REC << 8)} , asEntryDesc0x6020 , aName0x6020 , &IO_STATUS0x6020, NULL , NULL , 0x0000 },
/* Object 0x7000 */
{NULL , NULL ,  0x7000 , {DEFTYPE_RECORD , 6 | (OBJCODE_REC << 8)} , asEntryDesc0x7000 , aName0x7000 , &TERM_CTRL0x7000, NULL , NULL , 0x0000 },
{NULL,NULL, 0xFFFF, {0, 0}, NULL, NULL, NULL, NULL}};
#endif    //#ifdef _OBJD_
#undef PROTO

/** @}*/
#define _TOOL_APPL_OBJECTS_H_
