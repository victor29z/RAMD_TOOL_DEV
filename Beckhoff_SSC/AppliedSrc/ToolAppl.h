/**
 * \addtogroup ToolAppl ToolAppl
 * @{
 */

/**
\file ToolAppl.h
\brief ToolAppl function prototypes and defines

\version 1.0.0.11
 */

 
 #ifndef _TOOL_APPL_H_
#define _TOOL_APPL_H_


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

#endif //_TOOL_APPL_H_

//include custom application object dictionary 
#include "ToolApplObjects.h"


#if defined(_TOOL_APPL_) && (_TOOL_APPL_ == 1)
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
    UINT16 objFT_FX_DATA;
    UINT16 objFT_FY_DATA;	
    UINT16 objFT_FZ_DATA;	
    UINT16 objFT_TX_DATA;	
    UINT16 objFT_TY_DATA;	
    UINT16 objFT_TZ_DATA;	
}STRUCT_PACKED_END
TPDO1A01;

typedef struct STRUCT_PACKED_START
{
    UINT16 objAI0_VALUE;	
    UINT16 objAI1_VALUE;	
    UINT16 objTI;

}STRUCT_PACKED_END
TPDO1A02;
#pragma pack (1)
typedef struct STRUCT_PACKED_START
{
    UINT8 objTMUX1_CH;	
    UINT8 objTMUX2_CH;	
    UINT16 objTO;
}STRUCT_PACKED_END
RPDO1600;
#pragma pack ()

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

