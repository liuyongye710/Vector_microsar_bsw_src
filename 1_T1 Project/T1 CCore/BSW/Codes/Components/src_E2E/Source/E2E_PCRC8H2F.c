/*
********************************************************************************
*
* File name: E2E_PCRC8H2F.c
*
* Copyright 2022-2024 Neusoft Reach Corporation.All rights reserved.
*
********************************************************************************
*
* History
*-------------------------------------------------------------------------------
********************************************************************************
* Version: 3.0
* Author/Date: XieYN/2022.10.24
* Change: New created
* Cause: New
********************************************************************************
* Version: 3.1
* Author/Date: XieYN/2023.01.10
* Change: 1. Modify read Counter when CounterSize is 4, and which is located in
*            high nibble of the data in E2E_PCRC8H2F_ReadCounter.
*         2. Delete unused state E2E_PCRC8H2FSTATUS_SYNC in
*            E2E_PCRC8H2FMapStatusToSM.
* Cause: Bugfix
********************************************************************************
* Version: 3.2
* Author/Date: LiDaY/2024.02.05
* Change: Modifying the label of the input parameter Ptrclass for E2E function
*         and addressing some code inconsistencies.
* Cause: Optimization
********************************************************************************
* Version: 3.3
* Author/Date: LiDaY/2024.03.18
* Change: Modifying the label of the input parameter Ptrclass for E2E function
*         and addressing some code inconsistencies.
* Cause: Optimization
********************************************************************************
* Version: 3.4
* Author/Date: LiDaY/2024.04.25
* Change: Add a memory-map label to function and variable declarations.
* Cause: Bugfix
********************************************************************************
* Version: 3.5
* Author/Date: LiDaY/2024.08.08
* Change: Change copyright information.
* Cause: Update
********************************************************************************
*/
/*
********************************************************************************
*    Includes
********************************************************************************
*/
#include "E2E_PCRC8H2F.h"

/*
********************************************************************************
*    Local Macros
********************************************************************************
*/
/*
********************************************************************************
*    Local Types
********************************************************************************
*/
/*
********************************************************************************
*    Local Variables
********************************************************************************
*/
/*
********************************************************************************
*    Local Constants
********************************************************************************
*/
/*
********************************************************************************
*    Local Functions
********************************************************************************
*/
#define E2E_START_SEC_CODE
#include "E2E_MemMap.h"

static FUNC(uint8, E2E_CODE) E2E_PCRC8H2F_ComputeCrc
(
    P2CONST(E2E_PCRC8H2FConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr,
    P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr,
    uint16 crcStartByte
);
static FUNC(uint8, E2E_CODE) E2E_PCRC8H2FCheck_ChkParam
(
    P2CONST(E2E_PCRC8H2FConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr,
    P2VAR(E2E_PCRC8H2FCheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
    P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr,
    P2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) NewDataAvailable
);
static FUNC(uint8, E2E_CODE) E2E_PCRC8H2FProtect_ChkParam
(
    P2CONST(E2E_PCRC8H2FConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr,
    P2VAR(E2E_PCRC8H2FProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
    P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr
);
static FUNC(uint16, E2E_CODE) E2E_PCRC8H2F_CalDeltaCounter
(
    VAR(uint16, E2E_APPL_DATA) receivedCounter,
    P2CONST(E2E_PCRC8H2FConfigType, AUTOMATIC, E2E_APPL_DATA) Config,
    P2VAR(E2E_PCRC8H2FCheckStateType, AUTOMATIC, E2E_APPL_DATA) State
);
static FUNC(void, E2E_CODE) E2E_PCRC8H2F_WriteCounter
(
    P2CONST(E2E_PCRC8H2FConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr,
    P2VAR(E2E_PCRC8H2FProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
    P2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr
);


#define E2E_STOP_SEC_CODE
#include "E2E_MemMap.h"

/*
********************************************************************************
*    Global Variables
********************************************************************************
*/
/*
********************************************************************************
*    Global Constants
********************************************************************************
*/
#define E2E_START_SEC_CODE
#include "E2E_MemMap.h"

/*
********************************************************************************
* Function Name: E2E_PCRC8H2F_ComputeCrc
*
* Explanation: Calculate for profile CRC8H2F.(Synchronous)
*
* param: ConfigPtr: Pointer to static configuration.
*        DataPtr: Pointer to Data to be transmitted.
*        crcByte: The location of CRC.
*
* retval: Crc Value.
********************************************************************************
*/
static FUNC(uint8, E2E_CODE) E2E_PCRC8H2F_ComputeCrc
(
    P2CONST(E2E_PCRC8H2FConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr,
    P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr,
    uint16 crcByte
)
{
    uint8 computedCrc = E2E_INIT_0;
    uint16 lengthBf = E2E_INIT_0;
    uint16 lengthAf = E2E_INIT_0;

    lengthAf = (ConfigPtr->DataLength / E2E_8BIT) - crcByte - E2E_INDEX_1;
    /* Calculation CRC, Before data and after data of CRC. */
    if( ConfigPtr->CRCOffset > E2E_INDEX_0 )
    {
        lengthBf = crcByte;
        computedCrc = Crc_CalculateCRC8H2F(DataPtr, lengthBf, E2E_FULL_BYTE, TRUE);
        computedCrc = Crc_CalculateCRC8H2F(&DataPtr[crcByte + E2E_INDEX_1],
                                           lengthAf, computedCrc, FALSE);
    }
    else /* Calculation CRC, after data of CRC. */
    {
        computedCrc = Crc_CalculateCRC8H2F(&DataPtr[crcByte + E2E_INDEX_1],
                                           lengthAf, E2E_FULL_BYTE, TRUE);
    }

    return computedCrc;
}

/*
********************************************************************************
* Function Name: E2E_PCRC8H2FCheck_ChkParam
*
* Explanation: Chekck parameter for profile CRC8H2F.(Synchronous)
*
* param: ConfigPtr: Pointer to static configuration.
*        StatePtr: Pointer to port/data communication state.
*        DataPtr: Pointer to Data to be transmitted.
*        NewDataAvailable: New data available.
*
* retval: uint8
********************************************************************************
*/
static FUNC(uint8, E2E_CODE) E2E_PCRC8H2FCheck_ChkParam
(
    P2CONST(E2E_PCRC8H2FConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr,
    P2VAR(E2E_PCRC8H2FCheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
    P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr,
    P2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) NewDataAvailable
)
{
    uint8 rtrnValu;

    /* At least one pointer parameter is a NULL pointer. */
    if( (NULL_PTR == ConfigPtr) || (NULL_PTR == StatePtr) || (NULL_PTR == DataPtr))
    {
         rtrnValu = E2E_E_INPUTERR_NULL;
    }
    else if( ((ConfigPtr->CounterSize == E2E_PCRC8H2F_COUNTERSIZE_4) &&
              (E2E_PCRC8H2FPROTECT_COUNTERMAX_4 < StatePtr->LastValidCounter)) ||
             ((ConfigPtr->CounterSize == E2E_PCRC8H2F_COUNTERSIZE_8) &&
              (E2E_PCRC8H2FPROTECT_COUNTERMAX_8 < StatePtr->LastValidCounter)) )

    {
        rtrnValu = E2E_E_INPUTERR_WRONG;
    }
    else
    {
        *NewDataAvailable = TRUE;
        rtrnValu = E2E_E_OK;
    }

    return rtrnValu;
}

/*
********************************************************************************
* Function Name: E2E_PCRC8H2FProtect_ChkParam
*
* Explanation: Check parameter of E2E_PCRC8H2FProtect.(Synchronous)
*
* param: ConfigPtr: Pointer to static configuration.
*        StatePtr: Pointer to port/data communication state.
*        DataPtr: Pointer to Data to be transmitted.
*
* retval: uint8
********************************************************************************
*/
static FUNC(uint8, E2E_CODE) E2E_PCRC8H2FProtect_ChkParam
(
    P2CONST(E2E_PCRC8H2FConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr,
    P2VAR(E2E_PCRC8H2FProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
    P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr
)
{
    uint8 rtrnValu;

    if( (NULL_PTR == ConfigPtr) || (NULL_PTR == StatePtr) || (NULL_PTR == DataPtr) )
    {
        /* At least one pointer parameter is a NULL pointer. */
        rtrnValu = E2E_E_INPUTERR_NULL;
    }
    else
    {
        rtrnValu = E2E_E_OK;
    }

    return rtrnValu;
}

/*
********************************************************************************
* Function Name: E2E_PCRC8H2F_WriteCounter
*
* Explanation: Write Counter for profile CRC8H2F.(Synchronous)
*
* param:  ConfigPtr: Pointer to static configuration.
*         StatePtr: Pointer to data communication state.
*         DataPtr: Pointer to data to be transmitted.
*
* retval: void
********************************************************************************
*/
static FUNC(void, E2E_CODE) E2E_PCRC8H2F_WriteCounter
(
    P2CONST(E2E_PCRC8H2FConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr,
    P2VAR(E2E_PCRC8H2FProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
    P2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr
)
{
    uint16 cntrStartByte = ConfigPtr->CounterOffset / E2E_8BIT;;

    if( E2E_PCRC8H2F_COUNTERSIZE_16 == ConfigPtr->CounterSize )
    {
        /* Counter is stored in big endian. */
        if( E2E_BIGENDIANESS == ConfigPtr->CounterEndianess )
        {
            /* Compute the byte where the Counter is Located in. */
            DataPtr[cntrStartByte] = (uint8)StatePtr->Counter;
            DataPtr[cntrStartByte - E2E_INDEX_1] = (uint8)(StatePtr->Counter >> E2E_8BIT);
        }
        else
        {
            /* Compute the byte where the Counter is Located in. */
            cntrStartByte = ConfigPtr->CounterOffset / E2E_8BIT;
            DataPtr[cntrStartByte] = (uint8)StatePtr->Counter;
            DataPtr[cntrStartByte + E2E_INDEX_1] = (uint8)(StatePtr->Counter >> E2E_8BIT);
        }
    }
    else if( E2E_PCRC8H2F_COUNTERSIZE_8 == ConfigPtr->CounterSize )
    {
        DataPtr[cntrStartByte] = (uint8)StatePtr->Counter;
    }
    else if( E2E_PCRC8H2F_COUNTERSIZE_4 == ConfigPtr->CounterSize )
    {
        if( E2E_JUDGE_0 == (ConfigPtr->CounterOffset % E2E_8BIT) )
        {
            DataPtr[cntrStartByte]
                  = (uint8)((DataPtr[cntrStartByte] & E2E_HIGH_NIBBLE)
                           | ((uint8)StatePtr->Counter & E2E_LOW_NIBBLE));
        }
        else
        {
            DataPtr[cntrStartByte]
              = (uint8)((DataPtr[cntrStartByte] & E2E_LOW_NIBBLE)
                       | ((uint8)StatePtr->Counter << E2E_4BIT) & E2E_HIGH_NIBBLE);
        }
    }
    else
    {
        /* Do nothing. */
    }
}

/*
********************************************************************************
* Function Name: E2E_PCRC8H2F_ReadCounter
*
* Explanation: Read Counter from received data for profile CRC8H2F.(Synchronous)
*
* param:  ConfigPtr: Pointer to static configuration.
*         DataPtr: Pointer to data to be transmitted.
*
* retval: uint16
********************************************************************************
*/
FUNC(uint16, E2E_CODE) E2E_PCRC8H2F_ReadCounter
(
    P2CONST(E2E_PCRC8H2FConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr,
    P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr
)
{
    uint16 receivedCounter = E2E_INIT_FULL1BYTE;
    uint16 cntrStartByte = ConfigPtr->CounterOffset / E2E_8BIT;;

    if( E2E_PCRC8H2F_COUNTERSIZE_16 == ConfigPtr->CounterSize )
    {
        /* Counter is stored in big endian. */
        /* Read Data counter. */
        if( E2E_BIGENDIANESS == ConfigPtr->CounterEndianess )
        {
            receivedCounter = ((uint16)DataPtr[cntrStartByte]) |
                              ((uint16)DataPtr[cntrStartByte - E2E_INDEX_1] << E2E_8BIT );
        }
        else
        {
            receivedCounter = ((uint16)DataPtr[cntrStartByte]) |
                              ((uint16)DataPtr[cntrStartByte + E2E_INDEX_1] << E2E_8BIT );
        }
    }
    else if( E2E_PCRC8H2F_COUNTERSIZE_8 == ConfigPtr->CounterSize )
    {
        receivedCounter = (uint16)DataPtr[cntrStartByte];
    }
    else if( E2E_PCRC8H2F_COUNTERSIZE_4 == ConfigPtr->CounterSize )
    {
        if( E2E_JUDGE_0 == (ConfigPtr->CounterOffset % E2E_8BIT) )
        {
            receivedCounter = (uint16)(DataPtr[cntrStartByte] & E2E_LOW_NIBBLE);
        }
        else
        {
            receivedCounter = (uint16)((DataPtr[cntrStartByte] >> E2E_4BIT) & E2E_LOW_NIBBLE);
        }
    }
    else
    {
        /* Do nothing. */
    }

    return receivedCounter;
}

/*
********************************************************************************
* Function Name: E2E_PCRC8H2F_CalDeltaCounter
*
* Explanation: Calculate delta Counter for profile CRC8H2F.(Synchronous)
*
* param:  receivedCounter: Counter value of this frame message.
*         Config: Pointer to static configuration.
*         State: Pointer to data communication state.
*
* retval: sint16
********************************************************************************
*/
static FUNC(uint16, E2E_CODE) E2E_PCRC8H2F_CalDeltaCounter
(
    VAR(uint16, E2E_APPL_DATA) receivedCounter,
    P2CONST(E2E_PCRC8H2FConfigType, AUTOMATIC, E2E_APPL_DATA) Config,
    P2VAR(E2E_PCRC8H2FCheckStateType, AUTOMATIC, E2E_APPL_DATA) State
)
{
    uint16 deltaCounter = E2E_INIT_0;

    if( receivedCounter >= State->LastValidCounter )
    {
        deltaCounter = receivedCounter - State->LastValidCounter;
    }
    else
    {
        if( E2E_PCRC8H2F_COUNTERSIZE_4 == Config->CounterSize )
        {
            deltaCounter = E2E_PCRC8H2FPROTECT_COUNTERMOD_4
                           + receivedCounter
                           - State->LastValidCounter;
        }
        else if( E2E_PCRC8H2F_COUNTERSIZE_8 == Config->CounterSize )
        {
            deltaCounter = E2E_PCRC8H2FPROTECT_COUNTERMOD_8
                           + receivedCounter
                           - State->LastValidCounter;
        }
        else
        {
            deltaCounter = E2E_PCRC8H2FPROTECT_COUNTERMOD_16
                           + receivedCounter
                           - State->LastValidCounter;
        }
    }

    return deltaCounter;
}

/*
********************************************************************************
* Function Name: E2E_PCRC8H2FProtect
*
* Explanation: Protects the array/buffer to be transmitted which uses the E2E
*              profile CRC8H2F.(Synchronous)
* param: ConfigPtr: Pointer to static configuration.
*        StatePtr: Pointer to port/data communication state.
*        DataPtr: Pointer to Data to be transmitted.
*
* retval: Std_ReturnType
********************************************************************************
*/
FUNC(Std_ReturnType, E2E_CODE) E2E_PCRC8H2FProtect
(
    P2CONST(E2E_PCRC8H2FConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr,
    P2VAR(E2E_PCRC8H2FProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
    P2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr
)
{
    Std_ReturnType rtrnValu = E2E_E_INPUTERR_NULL;
    uint8 computedCrc = E2E_INIT_0;
    uint16 crcByte = E2E_INIT_0;

    /* Check all parameters. */
    rtrnValu = E2E_PCRC8H2FProtect_ChkParam(ConfigPtr, StatePtr, DataPtr);
    if( E2E_E_OK == rtrnValu )
    {
        /* Write Counter. */
        E2E_PCRC8H2F_WriteCounter(ConfigPtr, StatePtr, DataPtr);
        /* Compute and Write Crc. */
        /* Compute the byte where the Crc and Counter Located in. */
        crcByte = ConfigPtr->CRCOffset / E2E_8BIT;
        /* Compute Crc. */
        computedCrc = E2E_PCRC8H2F_ComputeCrc(ConfigPtr, DataPtr, crcByte);
        DataPtr[crcByte] = (uint8)computedCrc & E2E_FULL_BYTE;

        /* Increment Counter when Counter is out of range. */
        if( ((ConfigPtr->CounterSize == E2E_PCRC8H2F_COUNTERSIZE_4) &&
            (StatePtr->Counter >= E2E_PCRC8H2FPROTECT_COUNTERMAX_4)) ||
            ((ConfigPtr->CounterSize == E2E_PCRC8H2F_COUNTERSIZE_8) &&
            (StatePtr->Counter >= E2E_PCRC8H2FPROTECT_COUNTERMAX_8)) ||
            ((ConfigPtr->CounterSize == E2E_PCRC8H2F_COUNTERSIZE_16) &&
            (StatePtr->Counter >= E2E_PCRC8H2FPROTECT_COUNTERMAX_16)) )
        {
            StatePtr->Counter = E2E_INIT_0;
        }
        /* Increment Counter. */
        else
        {
            StatePtr->Counter++;
        }
    }

    return rtrnValu;
}

/*
********************************************************************************
* Function Name: E2E_PCRC8H2FProtectInit
*
* Explanation: Initializes the protection state for profile CRC8H2F.(Synchronous)
*
* param: StatePtr: Pointer to port/data communication state.
*
* retval: Std_ReturnType
********************************************************************************
*/
FUNC(Std_ReturnType, E2E_CODE) E2E_PCRC8H2FProtectInit
(
    P2VAR(E2E_PCRC8H2FProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr
)
{
    Std_ReturnType rtrnValu = E2E_E_INPUTERR_NULL;

    /* The parameter is valid. */
    if( NULL_PTR != StatePtr )
    {
        StatePtr->Counter = E2E_INIT_0;
        rtrnValu = E2E_E_OK;
    }

    return rtrnValu;
}

/*
********************************************************************************
* Function Name: E2E_PCRC8H2FCheck
*
* Explanation: Checks the received Data which uses the E2E profile CRC8H2F.
*              (Synchronous)
*
* param: ConfigPtr: Pointer to static configuration.
*        StatePtr: Pointer to port/data communication state.
*        DataPtr: Pointer to received data.
*
* retval: Std_ReturnType
********************************************************************************
*/
FUNC(Std_ReturnType, E2E_CODE) E2E_PCRC8H2FCheck
(
    P2CONST(E2E_PCRC8H2FConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr,
    P2VAR(E2E_PCRC8H2FCheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
    P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr
)
{
    Std_ReturnType rtrnValu = E2E_E_INPUTERR_NULL;
    uint8 newDataAvailable = FALSE;
    uint16 receivedCounter = E2E_INIT_FULL1BYTE;
    uint16 crcByte = ConfigPtr->CRCOffset / E2E_8BIT;
    uint16 receivedCrc = E2E_INIT_0;
    uint16 computedCrc = E2E_INIT_0;
    uint16 deltaCounter = E2E_INIT_0;

    /* Verify inputs of the protect function. */
    rtrnValu = E2E_PCRC8H2FCheck_ChkParam(ConfigPtr, StatePtr, DataPtr,
                                          &newDataAvailable);
    if( E2E_E_OK == rtrnValu )
    {
        /* If any NEW data is available to be checked. */
        if( TRUE == newDataAvailable )
        {
            receivedCounter = E2E_PCRC8H2F_ReadCounter(ConfigPtr, DataPtr);
            /* Read Data Crc. */
            receivedCrc = DataPtr[crcByte];
            /* Compute Crc. */
            computedCrc = E2E_PCRC8H2F_ComputeCrc(ConfigPtr, DataPtr, crcByte);
            /* Compare received Crc and compute Crc. */
            if( receivedCrc == computedCrc )
            {
                if( E2E_PCRC8H2F_COUNTERSIZE_0 != ConfigPtr->CounterSize )
                {
                    /* Compute deltaCounter. */
                    deltaCounter = E2E_PCRC8H2F_CalDeltaCounter(receivedCounter, ConfigPtr, StatePtr);
                    if( deltaCounter <= ConfigPtr->MaxDeltaCounter )
                    {
                        if( deltaCounter > E2E_JUDGE_0 )
                        {
                            /* The checks of the Data in this cycle were successful
                               including counter check, which was incremented by 1. */
                            if( E2E_JUDGE_1 == deltaCounter )
                            {
                                StatePtr->Status = E2E_PCRC8H2FSTATUS_OK;
                            }
                            /* The checks of the Data in this cycle were successful,
                               ounter check which was incremented within the allowed
                               configured delta. */
                            else
                            {
                                StatePtr->Status = E2E_PCRC8H2FSTATUS_OKSOMELOST;
                            }
                        }
                        /* Data repeated. */
                        else
                        {
                            StatePtr->Status = E2E_PCRC8H2FSTATUS_REPEATED;
                        }
                    }
                    /* With the exception of counter jump, which changed more
                       than the allowed delta. */
                    else
                    {
                        StatePtr->Status = E2E_PCRC8H2FSTATUS_WRONGSEQUENCE;
                    }
                    StatePtr->LastValidCounter = receivedCounter;
                }
                else
                {
                    StatePtr->Status = E2E_PCRC8H2FSTATUS_OK;
                }
            }
            else
            {
                StatePtr->Status = E2E_PCRC8H2FSTATUS_WRONGCRC;
            }
        }
        else
        {
            StatePtr->Status = E2E_PCRC8H2FSTATUS_NONEWDATA;
        }
    }

    return rtrnValu;
}

/*
********************************************************************************
* Function Name: E2E_PCRC8H2FCheckInit
*
* Explanation: Initializes the check state for profile CRC8H2F.(Synchronous)
*
* param: StatePtr: Pointer to port/data communication state.
*
* retval: Std_ReturnType
********************************************************************************
*/
FUNC(Std_ReturnType, E2E_CODE) E2E_PCRC8H2FCheckInit
(
    P2VAR(E2E_PCRC8H2FCheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr
)
{
    Std_ReturnType rtrnValu = E2E_E_INPUTERR_NULL;

    /* The parameter is valid. */
    if( NULL_PTR != StatePtr )
    {
        StatePtr->LastValidCounter = E2E_INIT_0;
        StatePtr->Status = E2E_PCRC8H2FSTATUS_INITIAL;
        rtrnValu = E2E_E_OK;
    }

    return rtrnValu;
}

/*
********************************************************************************
* Function Name: E2E_PCRC8H2FMapStatusToSM
*
* Explanation: The function maps the check status of Profile CRC8H2F to a generic
*              check status,which can be used by E2E state machine check
*              function. The E2E Profile CRC8H2F delivers a more fine-granular status,
*              but this is not relevant for the E2E state machine.(Synchronous)
*
* param: CheckReturn: Return value of the E2E_PCRC8H2FCheck function.
*        Status: Status determined by E2E_PCRC8H2FCheck function.
*
* retval: Std_ReturnType
********************************************************************************
*/
FUNC(E2E_PCheckStatusType, E2E_CODE) E2E_PCRC8H2FMapStatusToSM
(
    Std_ReturnType CheckReturn,
    E2E_PCRC8H2FCheckStatusType Status
)
{
    E2E_PCheckStatusType rtrnValu = E2E_P_ERROR;
    E2E_PCheckStatusType statusInitial = E2E_P_ERROR;

    if( E2E_E_OK == CheckReturn )
    {
        switch( Status )
        {
            case E2E_PCRC8H2FSTATUS_OK:
                /* The checks of the Data in this cycle were successful. */
                rtrnValu = E2E_P_OK;
                break;
            case E2E_PCRC8H2FSTATUS_OKSOMELOST:
                /* The checks of the Data in this cycle were successful. */
                rtrnValu = E2E_P_OK;
                break;
            case E2E_PCRC8H2FSTATUS_INITIAL:
                /* Return depending on profileBehavior. */
                rtrnValu = statusInitial;
                break;
            case E2E_PCRC8H2FSTATUS_WRONGCRC:
                /* Error not related to counters occurred or the return of
                   the check function was not OK. */
                rtrnValu = E2E_P_ERROR;
                break;
            case E2E_PCRC8H2FSTATUS_REPEATED:
                /* Data has a repeated counter. */
                rtrnValu = E2E_P_REPEATED;
                break;
            case E2E_PCRC8H2FSTATUS_NONEWDATA:
                /* No new data is available. */
                rtrnValu = E2E_P_NONEWDATA;
                break;
            case E2E_PCRC8H2FSTATUS_WRONGSEQUENCE:
                /* The checks of the Data in this cycle were successful, with
                   the exception of counter jump, which changed more than the
                   allowed delta. */
                rtrnValu = E2E_P_WRONGSEQUENCE;
                break;
            default:
                break;
        }
    }
    else
    {
        rtrnValu = E2E_P_ERROR;
    }

    return rtrnValu;
}

#define E2E_STOP_SEC_CODE
#include "E2E_MemMap.h"
