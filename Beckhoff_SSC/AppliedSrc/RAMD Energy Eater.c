/**
\addtogroup RAMDEnergyEater RAMD Energy Eater
@{
*/

/**
\file RAMD Energy Eater.c
\brief Implementation

\version 1.0.0.11
*/


/*-----------------------------------------------------------------------------------------
------
------    Includes
------
-----------------------------------------------------------------------------------------*/
#include "ecat_def.h"

#include "applInterface.h"

#define _RAMD_ENERGY_EATER_ 1
#include "RAMD Energy Eater.h"
#undef _RAMD_ENERGY_EATER_

#include "Protocol.h"
#include "BSP_Global.h"
/*--------------------------------------------------------------------------------------
------
------    local types and defines
------
--------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------
------
------    local variables and constants
------
-----------------------------------------------------------------------------------------*/
TOBJ7000 sSYS_CTRL;
TOBJ6000 sMPU_STATUS;

TOBJ6020 sSYS_STATUS;


//extern int16_t base_state[BASE_STATE_BUF_SIZE];
/*-----------------------------------------------------------------------------------------
------
------    application specific functions
------
-----------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------
------
------    generic functions
------
-----------------------------------------------------------------------------------------*/

/////////////////////////////////////////////////////////////////////////////////////////
/**
 \brief    The function is called when an error state was acknowledged by the master

*////////////////////////////////////////////////////////////////////////////////////////

void    APPL_AckErrorInd(UINT16 stateTrans)
{

}

/////////////////////////////////////////////////////////////////////////////////////////
/**
 \return    AL Status Code (see ecatslv.h ALSTATUSCODE_....)

 \brief    The function is called in the state transition from INIT to PREOP when
             all general settings were checked to start the mailbox handler. This function
             informs the application about the state transition, the application can refuse
             the state transition when returning an AL Status error code.
            The return code NOERROR_INWORK can be used, if the application cannot confirm
            the state transition immediately, in that case this function will be called cyclically
            until a value unequal NOERROR_INWORK is returned

*////////////////////////////////////////////////////////////////////////////////////////

UINT16 APPL_StartMailboxHandler(void)
{
    return ALSTATUSCODE_NOERROR;
}

/////////////////////////////////////////////////////////////////////////////////////////
/**
 \return     0, NOERROR_INWORK

 \brief    The function is called in the state transition from PREEOP to INIT
             to stop the mailbox handler. This functions informs the application
             about the state transition, the application cannot refuse
             the state transition.

*////////////////////////////////////////////////////////////////////////////////////////

UINT16 APPL_StopMailboxHandler(void)
{
    return ALSTATUSCODE_NOERROR;
}

/////////////////////////////////////////////////////////////////////////////////////////
/**
 \param    pIntMask    pointer to the AL Event Mask which will be written to the AL event Mask
                        register (0x204) when this function is succeeded. The event mask can be adapted
                        in this function
 \return    AL Status Code (see ecatslv.h ALSTATUSCODE_....)

 \brief    The function is called in the state transition from PREOP to SAFEOP when
           all general settings were checked to start the input handler. This function
           informs the application about the state transition, the application can refuse
           the state transition when returning an AL Status error code.
           The return code NOERROR_INWORK can be used, if the application cannot confirm
           the state transition immediately, in that case the application need to be complete 
           the transition by calling ECAT_StateChange.
*////////////////////////////////////////////////////////////////////////////////////////

UINT16 APPL_StartInputHandler(UINT16 *pIntMask)
{
    return ALSTATUSCODE_NOERROR;
}

/////////////////////////////////////////////////////////////////////////////////////////
/**
 \return     0, NOERROR_INWORK

 \brief    The function is called in the state transition from SAFEOP to PREEOP
             to stop the input handler. This functions informs the application
             about the state transition, the application cannot refuse
             the state transition.

*////////////////////////////////////////////////////////////////////////////////////////

UINT16 APPL_StopInputHandler(void)
{
    return ALSTATUSCODE_NOERROR;
}

/////////////////////////////////////////////////////////////////////////////////////////
/**
 \return    AL Status Code (see ecatslv.h ALSTATUSCODE_....)

 \brief    The function is called in the state transition from SAFEOP to OP when
             all general settings were checked to start the output handler. This function
             informs the application about the state transition, the application can refuse
             the state transition when returning an AL Status error code.
           The return code NOERROR_INWORK can be used, if the application cannot confirm
           the state transition immediately, in that case the application need to be complete 
           the transition by calling ECAT_StateChange.
*////////////////////////////////////////////////////////////////////////////////////////

UINT16 APPL_StartOutputHandler(void)
{
    return ALSTATUSCODE_NOERROR;
}

/////////////////////////////////////////////////////////////////////////////////////////
/**
 \return     0, NOERROR_INWORK

 \brief    The function is called in the state transition from OP to SAFEOP
             to stop the output handler. This functions informs the application
             about the state transition, the application cannot refuse
             the state transition.

*////////////////////////////////////////////////////////////////////////////////////////

UINT16 APPL_StopOutputHandler(void)
{
    return ALSTATUSCODE_NOERROR;
}

/////////////////////////////////////////////////////////////////////////////////////////
/**
\return     0(ALSTATUSCODE_NOERROR), NOERROR_INWORK
\param      pInputSize  pointer to save the input process data length
\param      pOutputSize  pointer to save the output process data length

\brief    This function calculates the process data sizes from the actual SM-PDO-Assign
            and PDO mapping
*////////////////////////////////////////////////////////////////////////////////////////
UINT16 APPL_GenerateMapping(UINT16 *pInputSize,UINT16 *pOutputSize)
{
    UINT16 result = ALSTATUSCODE_NOERROR;
    UINT16 InputSize = 0;
    UINT16 OutputSize = 0;

#if COE_SUPPORTED
    UINT16 PDOAssignEntryCnt = 0;
    OBJCONST TOBJECT OBJMEM * pPDO = NULL;
    UINT16 PDOSubindex0 = 0;
    UINT32 *pPDOEntry = NULL;
    UINT16 PDOEntryCnt = 0;
   
    /*Scan object 0x1C12 RXPDO assign*/
    for(PDOAssignEntryCnt = 0; PDOAssignEntryCnt < sRxPDOassign.u16SubIndex0; PDOAssignEntryCnt++)
    {
        pPDO = OBJ_GetObjectHandle(sRxPDOassign.aEntries[PDOAssignEntryCnt]);
        if(pPDO != NULL)
        {
            PDOSubindex0 = *((UINT16 *)pPDO->pVarPtr);
            for(PDOEntryCnt = 0; PDOEntryCnt < PDOSubindex0; PDOEntryCnt++)
            {
                pPDOEntry = (UINT32 *)((UINT8 *)pPDO->pVarPtr + (OBJ_GetEntryOffset((PDOEntryCnt+1),pPDO)>>3));    //goto PDO entry
                // we increment the expected output size depending on the mapped Entry
                OutputSize += (UINT16) ((*pPDOEntry) & 0xFF);
            }
        }
        else
        {
            /*assigned PDO was not found in object dictionary. return invalid mapping*/
            OutputSize = 0;
            result = ALSTATUSCODE_INVALIDOUTPUTMAPPING;
            break;
        }
    }

    OutputSize = (OutputSize + 7) >> 3;

    if(result == 0)
    {
        /*Scan Object 0x1C13 TXPDO assign*/
        for(PDOAssignEntryCnt = 0; PDOAssignEntryCnt < sTxPDOassign.u16SubIndex0; PDOAssignEntryCnt++)
        {
            pPDO = OBJ_GetObjectHandle(sTxPDOassign.aEntries[PDOAssignEntryCnt]);
            if(pPDO != NULL)
            {
                PDOSubindex0 = *((UINT16 *)pPDO->pVarPtr);
                for(PDOEntryCnt = 0; PDOEntryCnt < PDOSubindex0; PDOEntryCnt++)
                {
                    pPDOEntry = (UINT32 *)((UINT8 *)pPDO->pVarPtr + (OBJ_GetEntryOffset((PDOEntryCnt+1),pPDO)>>3));    //goto PDO entry
                    // we increment the expected output size depending on the mapped Entry
                    InputSize += (UINT16) ((*pPDOEntry) & 0xFF);
                }
            }
            else
            {
                /*assigned PDO was not found in object dictionary. return invalid mapping*/
                InputSize = 0;
                result = ALSTATUSCODE_INVALIDINPUTMAPPING;
                break;
            }
        }
    }
    InputSize = (InputSize + 7) >> 3;

#else
#if _WIN32
   #pragma message ("Warning: Define 'InputSize' and 'OutputSize'.")
#else
    #warning "Define 'InputSize' and 'OutputSize'."
#endif
#endif

    *pInputSize = InputSize;
    *pOutputSize = OutputSize;
    return result;
}

/////////////////////////////////////////////////////////////////////////////////////////
/**
\param      pData  pointer to input process data

\brief      This function will copies the inputs from the local memory to the ESC memory
            to the hardware
*////////////////////////////////////////////////////////////////////////////////////////
void APPL_InputMapping(UINT16* pData)
{

    UINT16 j = 0;
    UINT8 *pTmpData = (UINT8 *)pData;
    UINT8 AxisIndex;

    for (j = 0; j < sTxPDOassign.u16SubIndex0; j++)
    {
        switch ((sTxPDOassign.aEntries[j]& 0x000F))
        {
        case 0:    //copy 1A00 TxPDO entries
            {
                TPDO1A00 *pInputs = (TPDO1A00 *)pTmpData;
                
                pInputs->objMPU_ACC_X_DATA = sMPU_STATUS.wMPU_ACC_X_DATA;
                pInputs->objMPU_ACC_Y_DATA = sMPU_STATUS.wMPU_ACC_Y_DATA;
                pInputs->objMPU_ACC_Z_DATA = sMPU_STATUS.wMPU_ACC_Z_DATA;
                pInputs->objMPU_GYR_X_DATA = sMPU_STATUS.wMPU_GYR_X_DATA;
                pInputs->objMPU_GYR_Y_DATA = sMPU_STATUS.wMPU_GYR_Y_DATA;
                pInputs->objMPU_GYR_Z_DATA = sMPU_STATUS.wMPU_GYR_Z_DATA;
                pInputs->objMPU_TEMP_DATA = sMPU_STATUS.wMPU_TEMP_DATA;
                

                /*shift pointer PDO mapping object following*/
                if(j < (sTxPDOassign.u16SubIndex0 - 1))
                    pTmpData += SIZEOF(TPDO1A00);
				
            }
            break;
        case 1://copy 1A01 TxPDO entries
            // not used
            break;
        case 2://copy 1A02 TxPDO entries
            {
                TPDO1A02 *pInputs = (TPDO1A02 *)pTmpData;

                pInputs->objSYS_VOLTAGE = sSYS_STATUS.wSYS_VOLTAGE;
                pInputs->objSYS_ROBOT_VOLTAGE = sSYS_STATUS.wSYS_ROBOT_VOLTAGE;
                pInputs->objSYS_CURRENT = sSYS_STATUS.wSYS_CURRENT;
                pInputs->objSYS_TEMP = sSYS_STATUS.wSYS_TEMP;
                pInputs->objSYS_ERROR_NO = sSYS_STATUS.wSYS_ERROR_NO;
                pInputs->objSYS_STAT = ((UINT16 *) &sSYS_STATUS)[7];

                /*shift pointer PDO mapping object following*/
                if(j < (sTxPDOassign.u16SubIndex0 - 1))
                    pTmpData += SIZEOF(TPDO1A02);
            }
            break;
        }    //switch TXPDO entry
    }
}

/////////////////////////////////////////////////////////////////////////////////////////
/**
\param      pData  pointer to output process data

\brief    This function will copies the outputs from the ESC memory to the local memory
            to the hardware
*////////////////////////////////////////////////////////////////////////////////////////
void APPL_OutputMapping(UINT16* pData)
{
    UINT8 *pTmpData = (UINT8 *)pData;    
    RPDO1600 *pOutputs = (RPDO1600 *)pTmpData;
	

    ((UINT16 *) &sSYS_CTRL)[1] = SWAPDWORD(pOutputs->objSYS_CTRL);
}

/////////////////////////////////////////////////////////////////////////////////////////
/**
\brief    This function will called from the synchronisation ISR 
            or from the mainloop if no synchronisation is supported
*////////////////////////////////////////////////////////////////////////////////////////
void APPL_Application(void)
{
    /*
    base_state[SYS_ENABLE_ON_POWER] = sSYS_CTRL.bSYS_ENABLE_ROBOT_POWER;
    base_state[SYS_CLEAR_ERROR] = sSYS_CTRL.bSYS_CLEAR_ERROR;

    sSYS_STATUS.wSYS_VOLTAGE = base_state[SYS_VOLTAGE];
    sSYS_STATUS.wSYS_ROBOT_VOLTAGE = base_state[SYS_ROBOT_VOLTAGE];
    sSYS_STATUS.wSYS_CURRENT = base_state[SYS_CURRENT_H]<<16 | base_state[SYS_CURRENT_L];
    sSYS_STATUS.wSYS_TEMP = base_state[SYS_TEMP];
    sSYS_STATUS.wSYS_ERROR_NO = base_state[SYS_ERROR];
    sSYS_STATUS.bSYS_ENGY_EATER_ENABLE = base_state[SYS_ENABLE_ENGY_EATER]; 
    sSYS_STATUS.bSTO1 = BSP_GET_STOx(1);
    sSYS_STATUS.bSTO2 = BSP_GET_STOx(2);

    
    sMPU_STATUS.wMPU_ACC_X_DATA = base_state[MPU_ACC_X_DATA];
	sMPU_STATUS.wMPU_ACC_Y_DATA = base_state[MPU_ACC_Y_DATA];
	sMPU_STATUS.wMPU_ACC_Z_DATA = base_state[MPU_ACC_Z_DATA];
	
	sMPU_STATUS.wMPU_GYR_X_DATA = base_state[MPU_GYR_X_DATA];
	sMPU_STATUS.wMPU_GYR_Y_DATA = base_state[MPU_GYR_Y_DATA];
	sMPU_STATUS.wMPU_GYR_Z_DATA = base_state[MPU_GYR_Z_DATA];
	
	sMPU_STATUS.wMPU_TEMP_DATA = base_state[MPU_TEMP_DATA];
*/
}

#if EXPLICIT_DEVICE_ID
/////////////////////////////////////////////////////////////////////////////////////////
/**
 \return    The Explicit Device ID of the EtherCAT slave

 \brief     Calculate the Explicit Device ID
*////////////////////////////////////////////////////////////////////////////////////////
UINT16 APPL_GetDeviceID()
{
#if _WIN32
   #pragma message ("Warning: Implement explicit Device ID latching")
#else
    #warning "Implement explicit Device ID latching"
#endif
    /* Explicit Device 5 is expected by Explicit Device ID conformance tests*/
    return 0x5;
}
#endif



#if USE_DEFAULT_MAIN
/////////////////////////////////////////////////////////////////////////////////////////
/**

 \brief    This is the main function

*////////////////////////////////////////////////////////////////////////////////////////
#if _PIC24
int main(void)
#else
void main(void)
#endif
{
    /* initialize the Hardware and the EtherCAT Slave Controller */
#if FC1100_HW
    if(HW_Init())
    {
        HW_Release();
        return;
    }
#else
    HW_Init();
#endif
    MainInit();

    bRunApplication = TRUE;
    do
    {
        MainLoop();
        
    } while (bRunApplication == TRUE);

    HW_Release();
#if _PIC24
    return 0;
#endif
}
#endif //#if USE_DEFAULT_MAIN
/** @} */


