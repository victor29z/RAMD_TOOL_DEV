/**
* \addtogroup RAMDEnergyEater RAMD Energy Eater
* @{
*/

/**
\file RAMD Energy EaterObjects
\author ET9300Utilities.ApplicationHandler (Version 1.3.6.0) | EthercatSSC@beckhoff.com

\brief RAMD Energy Eater specific objects<br>
\brief NOTE : This file will be overwritten if a new object dictionary is generated!<br>
*/

#if defined(_RAMD_ENERGY_EATER_) && (_RAMD_ENERGY_EATER_ == 1)
#define PROTO
#else
#define PROTO extern
#endif
/******************************************************************************
*                    Object 0x1600 : SYS_CTRL process data mapping
******************************************************************************/
/**
* \addtogroup 0x1600 0x1600 | SYS_CTRL process data mapping
* @{
* \brief Object 0x1600 (SYS_CTRL process data mapping) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1 - Reference to 0x7000.1<br>
* SubIndex 2 - Reference to 0x7000.2<br>
* SubIndex 3 - Padding entry (14Bit)<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x1600[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex1 - Reference to 0x7000.1 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex2 - Reference to 0x7000.2 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }}; /* Subindex3 - Padding entry (14Bit) */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x1600[] = "SYS_CTRL process data mapping\000"
"SubIndex 001\000"
"SubIndex 002\000"
"SubIndex 003\000\377";
#endif //#ifdef _OBJD_

#ifndef _RAMD_ENERGY_EATER_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
UINT32 SI1; /* Subindex1 - Reference to 0x7000.1 */
UINT32 SI2; /* Subindex2 - Reference to 0x7000.2 */
UINT32 SI3; /* Subindex3 - Padding entry (14Bit) */
} OBJ_STRUCT_PACKED_END
TOBJ1600;
#endif //#ifndef _RAMD_ENERGY_EATER_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ1600 SYS_CTRLProcessDataMapping0x1600
#if defined(_RAMD_ENERGY_EATER_) && (_RAMD_ENERGY_EATER_ == 1)
={3,0x70000101,0x70000201,0x0000000E}
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

#ifndef _RAMD_ENERGY_EATER_OBJECTS_H_
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
#endif //#ifndef _RAMD_ENERGY_EATER_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ1A00 MPU_STATUSProcessDataMapping0x1A00
#if defined(_RAMD_ENERGY_EATER_) && (_RAMD_ENERGY_EATER_ == 1)
={7,0x60000110,0x60000210,0x60000310,0x60000410,0x60000510,0x60000610,0x60000710}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x1A02 : SYS_STATUS process data mapping
******************************************************************************/
/**
* \addtogroup 0x1A02 0x1A02 | SYS_STATUS process data mapping
* @{
* \brief Object 0x1A02 (SYS_STATUS process data mapping) definition
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
* SubIndex 5 - Reference to 0x6020.5<br>
* SubIndex 6 - Reference to 0x6020.6<br>
* SubIndex 7 - Reference to 0x6020.7<br>
* SubIndex 8 - Reference to 0x6020.8<br>
* SubIndex 9 - Padding entry (13Bit)<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x1A02[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex1 - Reference to 0x6020.1 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex2 - Reference to 0x6020.2 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex3 - Reference to 0x6020.3 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex4 - Reference to 0x6020.4 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex5 - Reference to 0x6020.5 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex6 - Reference to 0x6020.6 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex7 - Reference to 0x6020.7 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex8 - Reference to 0x6020.8 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }}; /* Subindex9 - Padding entry (13Bit) */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x1A02[] = "SYS_STATUS process data mapping\000"
"SubIndex 001\000"
"SubIndex 002\000"
"SubIndex 003\000"
"SubIndex 004\000"
"SubIndex 005\000"
"SubIndex 006\000"
"SubIndex 007\000"
"SubIndex 008\000"
"SubIndex 009\000\377";
#endif //#ifdef _OBJD_

#ifndef _RAMD_ENERGY_EATER_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
UINT32 SI1; /* Subindex1 - Reference to 0x6020.1 */
UINT32 SI2; /* Subindex2 - Reference to 0x6020.2 */
UINT32 SI3; /* Subindex3 - Reference to 0x6020.3 */
UINT32 SI4; /* Subindex4 - Reference to 0x6020.4 */
UINT32 SI5; /* Subindex5 - Reference to 0x6020.5 */
UINT32 SI6; /* Subindex6 - Reference to 0x6020.6 */
UINT32 SI7; /* Subindex7 - Reference to 0x6020.7 */
UINT32 SI8; /* Subindex8 - Reference to 0x6020.8 */
UINT32 SI9; /* Subindex9 - Padding entry (13Bit) */
} OBJ_STRUCT_PACKED_END
TOBJ1A02;
#endif //#ifndef _RAMD_ENERGY_EATER_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ1A02 SYS_STATUSProcessDataMapping0x1A02
#if defined(_RAMD_ENERGY_EATER_) && (_RAMD_ENERGY_EATER_ == 1)
={9,0x60200110,0x60200210,0x60200320,0x60200410,0x60200510,0x60200601,0x60200701,0x60200801,0x0000000D}
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

#ifndef _RAMD_ENERGY_EATER_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16   u16SubIndex0;  /**< \brief Subindex 0 */
UINT16 aEntries[1];  /**< \brief Subindex 1 - 1 */
} OBJ_STRUCT_PACKED_END
TOBJ1C12;
#endif //#ifndef _RAMD_ENERGY_EATER_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ1C12 sRxPDOassign
#if defined(_RAMD_ENERGY_EATER_) && (_RAMD_ENERGY_EATER_ == 1)
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

#ifndef _RAMD_ENERGY_EATER_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16   u16SubIndex0;  /**< \brief Subindex 0 */
UINT16 aEntries[2];  /**< \brief Subindex 1 - 2 */
} OBJ_STRUCT_PACKED_END
TOBJ1C13;
#endif //#ifndef _RAMD_ENERGY_EATER_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ1C13 sTxPDOassign
#if defined(_RAMD_ENERGY_EATER_) && (_RAMD_ENERGY_EATER_ == 1)
={2,{0x1A00,0x1A02}}
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

#ifndef _RAMD_ENERGY_EATER_OBJECTS_H_
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
#endif //#ifndef _RAMD_ENERGY_EATER_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ6000 MPU_STATUS0x6000
#if defined(_RAMD_ENERGY_EATER_) && (_RAMD_ENERGY_EATER_ == 1)
={7,0,0,0,0,0,0,0}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x6020 : SYS_STATUS
******************************************************************************/
/**
* \addtogroup 0x6020 0x6020 | SYS_STATUS
* @{
* \brief Object 0x6020 (SYS_STATUS) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1 - SYS_VOLTAGE<br>
* SubIndex 2 - SYS_ROBOT_VOLTAGE<br>
* SubIndex 3 - SYS_CURRENT<br>
* SubIndex 4 - SYS_TEMP<br>
* SubIndex 5 - SYS_ERROR_NO<br>
* SubIndex 6 - SYS_ENGY_EATER_ENABLE<br>
* SubIndex 7 - STO1<br>
* SubIndex 8 - STO2<br>
* SubIndex 9<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x6020[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READ | OBJACCESS_TXPDOMAPPING }, /* Subindex1 - SYS_VOLTAGE */
{ DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READ | OBJACCESS_TXPDOMAPPING }, /* Subindex2 - SYS_ROBOT_VOLTAGE */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ | OBJACCESS_TXPDOMAPPING }, /* Subindex3 - SYS_CURRENT */
{ DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READ | OBJACCESS_TXPDOMAPPING }, /* Subindex4 - SYS_TEMP */
{ DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READ | OBJACCESS_TXPDOMAPPING }, /* Subindex5 - SYS_ERROR_NO */
{ DEFTYPE_BOOLEAN , 0x1 , ACCESS_READ | OBJACCESS_TXPDOMAPPING }, /* Subindex6 - SYS_ENGY_EATER_ENABLE */
{ DEFTYPE_BOOLEAN , 0x1 , ACCESS_READ | OBJACCESS_TXPDOMAPPING }, /* Subindex7 - STO1 */
{ DEFTYPE_BOOLEAN , 0x1 , ACCESS_READ | OBJACCESS_TXPDOMAPPING }, /* Subindex8 - STO2 */
{ DEFTYPE_NULL , 0xD , ACCESS_READ | OBJACCESS_TXPDOMAPPING }}; /* Subindex9 */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x6020[] = "SYS_STATUS\000"
"SYS_VOLTAGE\000"
"SYS_ROBOT_VOLTAGE\000"
"SYS_CURRENT\000"
"SYS_TEMP\000"
"SYS_ERROR_NO\000"
"SYS_ENGY_EATER_ENABLE\000"
"STO1\000"
"STO2\000"
"\000\377";
#endif //#ifdef _OBJD_

#ifndef _RAMD_ENERGY_EATER_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
UINT16 wSYS_VOLTAGE; /* Subindex1 - SYS_VOLTAGE */
UINT16 wSYS_ROBOT_VOLTAGE; /* Subindex2 - SYS_ROBOT_VOLTAGE */
UINT32 wSYS_CURRENT; /* Subindex3 - SYS_CURRENT */
UINT16 wSYS_TEMP; /* Subindex4 - SYS_TEMP */
UINT16 wSYS_ERROR_NO; /* Subindex5 - SYS_ERROR_NO */
BOOLEAN(bSYS_ENGY_EATER_ENABLE); /* Subindex6 - SYS_ENGY_EATER_ENABLE */
BOOLEAN(bSTO1); /* Subindex7 - STO1 */
BOOLEAN(bSTO2); /* Subindex8 - STO2 */
ALIGN13(SI9) /* Subindex9 */
} OBJ_STRUCT_PACKED_END
TOBJ6020;
#endif //#ifndef _RAMD_ENERGY_EATER_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ6020 SYS_STATUS0x6020
#if defined(_RAMD_ENERGY_EATER_) && (_RAMD_ENERGY_EATER_ == 1)
={9,0,0,0,0,0,0,0,0,0}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x7000 : SYS_CTRL
******************************************************************************/
/**
* \addtogroup 0x7000 0x7000 | SYS_CTRL
* @{
* \brief Object 0x7000 (SYS_CTRL) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1 - SYS_ENABLE_ROBOT_POWER<br>
* SubIndex 2 - SYS_CLEAR_ERROR<br>
* SubIndex 3<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x7000[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_BOOLEAN , 0x1 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING }, /* Subindex1 - SYS_ENABLE_ROBOT_POWER */
{ DEFTYPE_BOOLEAN , 0x1 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING }, /* Subindex2 - SYS_CLEAR_ERROR */
{ DEFTYPE_NULL , 0xE , 0x0000 }}; /* Subindex3 */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x7000[] = "SYS_CTRL\000"
"SYS_ENABLE_ROBOT_POWER\000"
"SYS_CLEAR_ERROR\000"
"\000\377";
#endif //#ifdef _OBJD_

#ifndef _RAMD_ENERGY_EATER_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
BOOLEAN(bSYS_ENABLE_ROBOT_POWER); /* Subindex1 - SYS_ENABLE_ROBOT_POWER */
BOOLEAN(bSYS_CLEAR_ERROR); /* Subindex2 - SYS_CLEAR_ERROR */
ALIGN14(SI3) /* Subindex3 */
} OBJ_STRUCT_PACKED_END
TOBJ7000;
#endif //#ifndef _RAMD_ENERGY_EATER_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ7000 SYS_CTRL0x7000
#if defined(_RAMD_ENERGY_EATER_) && (_RAMD_ENERGY_EATER_ == 1)
={3,0,0,0}
#endif
;
/** @}*/







#ifdef _OBJD_
TOBJECT    OBJMEM ApplicationObjDic[] = {
/* Object 0x1600 */
{NULL , NULL ,  0x1600 , {DEFTYPE_PDOMAPPING , 3 | (OBJCODE_REC << 8)} , asEntryDesc0x1600 , aName0x1600 , &SYS_CTRLProcessDataMapping0x1600, NULL , NULL , 0x0000 },
/* Object 0x1A00 */
{NULL , NULL ,  0x1A00 , {DEFTYPE_PDOMAPPING , 7 | (OBJCODE_REC << 8)} , asEntryDesc0x1A00 , aName0x1A00 , &MPU_STATUSProcessDataMapping0x1A00, NULL , NULL , 0x0000 },
/* Object 0x1A02 */
{NULL , NULL ,  0x1A02 , {DEFTYPE_PDOMAPPING , 9 | (OBJCODE_REC << 8)} , asEntryDesc0x1A02 , aName0x1A02 , &SYS_STATUSProcessDataMapping0x1A02, NULL , NULL , 0x0000 },
/* Object 0x1C12 */
{NULL , NULL ,  0x1C12 , {DEFTYPE_UNSIGNED16 , 1 | (OBJCODE_ARR << 8)} , asEntryDesc0x1C12 , aName0x1C12 , &sRxPDOassign, NULL , NULL , 0x0000 },
/* Object 0x1C13 */
{NULL , NULL ,  0x1C13 , {DEFTYPE_UNSIGNED16 , 2 | (OBJCODE_ARR << 8)} , asEntryDesc0x1C13 , aName0x1C13 , &sTxPDOassign, NULL , NULL , 0x0000 },
/* Object 0x6000 */
{NULL , NULL ,  0x6000 , {DEFTYPE_RECORD , 7 | (OBJCODE_REC << 8)} , asEntryDesc0x6000 , aName0x6000 , &MPU_STATUS0x6000, NULL , NULL , 0x0000 },
/* Object 0x6020 */
{NULL , NULL ,  0x6020 , {DEFTYPE_RECORD , 9 | (OBJCODE_REC << 8)} , asEntryDesc0x6020 , aName0x6020 , &SYS_STATUS0x6020, NULL , NULL , 0x0000 },
/* Object 0x7000 */
{NULL , NULL ,  0x7000 , {DEFTYPE_RECORD , 3 | (OBJCODE_REC << 8)} , asEntryDesc0x7000 , aName0x7000 , &SYS_CTRL0x7000, NULL , NULL , 0x0000 },
{NULL,NULL, 0xFFFF, {0, 0}, NULL, NULL, NULL, NULL}};
#endif    //#ifdef _OBJD_
#undef PROTO

/** @}*/
#define _RAMD_ENERGY_EATER_OBJECTS_H_
