/**
 * \addtogroup RAMDEnergyEater RAMD Energy Eater
 * @{
 */

/**
\file RAMD Energy Eater.h
\brief RAMD Energy Eater function prototypes and defines

\version 1.0.0.11
 */

 
 #ifndef _RAMD_ENERGY_EATER_H_
#define _RAMD_ENERGY_EATER_H_


/*-----------------------------------------------------------------------------------------
------
------    Includes
------
-----------------------------------------------------------------------------------------*/
#include "ecat_def.h"

#include "ecatappl.h"

/*-----------------------------------------------------------------------------------------
------
------    Defines and Types
------
-----------------------------------------------------------------------------------------*/

#endif //_RAMD_ENERGY_EATER_H_

//include custom application object dictionary 
#include "RAMD Energy EaterObjects.h"


#if defined(_RAMD_ENERGY_EATER_) && (_RAMD_ENERGY_EATER_ == 1)
    #define PROTO
#else
    #define PROTO extern
#endif


typedef struct STRUCT_PACKED_START
{
    UINT16 objMPU_ACC_X_DATA;
    UINT16 objMPU_ACC_Y_DATA;	
    UINT16 objMPU_ACC_Z_DATA;	
    UINT16 objMPU_GYR_X_DATA;	
    UINT16 objMPU_GYR_Y_DATA;	
    UINT16 objMPU_GYR_Z_DATA;	
    UINT16 objMPU_TEMP_DATA;	
}STRUCT_PACKED_END
TPDO1A00;

typedef struct STRUCT_PACKED_START
{
    UINT16 objSYS_VOLTAGE;	
    UINT16 objSYS_ROBOT_VOLTAGE;	
    UINT32 objSYS_CURRENT;	
    UINT16 objSYS_TEMP;	
    UINT16 objSYS_ERROR_NO;	
    UINT16 objSYS_STAT;

}STRUCT_PACKED_END
TPDO1A02;

typedef struct STRUCT_PACKED_START
{
    UINT16 objSYS_CTRL;	
}STRUCT_PACKED_END
RPDO1600;

PROTO void APPL_Application(void);
#if EXPLICIT_DEVICE_ID
PROTO UINT16 APPL_GetDeviceID(void);
#endif

PROTO void   APPL_AckErrorInd(UINT16 stateTrans);
PROTO UINT16 APPL_StartMailboxHandler(void);
PROTO UINT16 APPL_StopMailboxHandler(void);
PROTO UINT16 APPL_StartInputHandler(UINT16 *pIntMask);
PROTO UINT16 APPL_StopInputHandler(void);
PROTO UINT16 APPL_StartOutputHandler(void);
PROTO UINT16 APPL_StopOutputHandler(void);

PROTO UINT16 APPL_GenerateMapping(UINT16 *pInputSize,UINT16 *pOutputSize);
PROTO void APPL_InputMapping(UINT16* pData);
PROTO void APPL_OutputMapping(UINT16* pData);

#undef PROTO
/** @}*/

