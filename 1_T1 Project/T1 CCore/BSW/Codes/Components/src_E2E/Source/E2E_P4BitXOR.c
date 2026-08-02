/*
********************************************************************************
*
* File name: E2E_P4BitXOR.c
*
* Copyright 2022-2024 Neusoft Reach Corporation.All rights reserved.
*
********************************************************************************
*
* History
*-------------------------------------------------------------------------------
********************************************************************************
* Version: 3.0
* Author/Date: XieYN/2022.10.31
* Change: New Created.
* Cause: New
********************************************************************************
* Version: 3.1
* Author/Date: XieYN/2022.11.17
* Change: Modify notification of function E2E_P4BitXOR_ChecksumCalculate and
*         E2E_P4BitXORMapStatusToSM.
* Cause: Optimization
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
#include "E2E_P4BitXOR.h"

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

static FUNC(void, E2E_CODE) E2E_P4BitXORCheck_ChkDeltaCounter
(
    uint8 DeltaCounter,
    uint8 ReceivedCounter,
    P2VAR(E2E_P4BitXORCheckStateType, AUTOMATIC, E2E_APPL_DATA) State,
    P2CONST(E2E_P4BitXORConfigType, AUTOMATIC, E2E_APPL_DATA) Config
);
static FUNC(uint8, E2E_CODE) E2E_P4BitXORProtect_ChkParam
(
    P2CONST(E2E_P4BitXORConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr,
    P2CONST(E2E_P4BitXORProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
    P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr
);
static FUNC(uint8, E2E_CODE) E2E_P4BitXORCheck_ChkParam
(
    P2CONST(E2E_P4BitXORConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr,
    P2CONST(E2E_P4BitXORCheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
    P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr
);
static FUNC(uint8, E2E_CODE) E2E_P4BitXOR_ChecksumCalculate
(
    P2CONST(E2E_P4BitXORConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr,
    P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr
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
* Function Name: E2E_P4BitXORCheck_ChkDeltaCounter
*
* Explanation: Verify the Deltacounter.
*
* param: DeltaCounter: This frame message counter to last frame message counter
*                      difference value.
*        ReceivedCounter: This frame message counter value.
*        State: Pointer to static configuration.
*        Config: Pointer to static configuration.
*
* retval: None
********************************************************************************
*/
static FUNC(void, E2E_CODE) E2E_P4BitXORCheck_ChkDeltaCounter
(
    uint8 DeltaCounter,
    uint8 ReceivedCounter,
    P2VAR(E2E_P4BitXORCheckStateType, AUTOMATIC, E2E_APPL_DATA) State,
    P2CONST(E2E_P4BitXORConfigType, AUTOMATIC, E2E_APPL_DATA) Config
)
{
    if( E2E_JUDGE_0 == DeltaCounter )
    {
        if( State->NoNewOrRepeatedDataCounter < E2E_P4BITXORPROTECT_COUNTERMAX )
        {
            /* Increment NoNewOrRepeatedDataCounter by 1. */
            State->NoNewOrRepeatedDataCounter++;
        }
        /* Set status to E2E_P4BITXORSTATUS_REPEATED. */
        State->Status = E2E_P4BITXORSTATUS_REPEATED;
    }
    else if( E2E_JUDGE_1 == DeltaCounter )
    {
        /* Set MaxDeltaCounter to MaxDeltaCounterInit of config. */
        State->MaxDeltaCounter = Config->MaxDeltaCounterInit;
        /* Write counter to current message. */
        State->LastValidCounter = ReceivedCounter;
        State->LostData = E2E_INIT_0;
        /* NoNewOrRepeatedDataCounter is in limited range. */
        if( State->NoNewOrRepeatedDataCounter <= Config->MaxNoNewOrRepeatedData )
        {
            State->NoNewOrRepeatedDataCounter = E2E_INIT_0;
            /* SyncCounter value is greater than zero, continue. */
            if( State->SyncCounter > E2E_JUDGE_0 )
            {
                /* Decrease SyncCounter */
                State->SyncCounter--;
                State->Status = E2E_P4BITXORSTATUS_SYNC;
            }
            /* SyncCounter is zero, no Data has been lost since the last correct
               data reception. */
            else
            {
                State->Status = E2E_P4BITXORSTATUS_OK;
            }
        }
        else  /* NoNewOrRepeatedDataCounter is out of limited range. */
        {
            State->NoNewOrRepeatedDataCounter = E2E_INIT_0;
            State->SyncCounter = Config->SyncCounterInit;
            State->Status = E2E_P4BITXORSTATUS_SYNC;
        }
    }
    /* Lose Multiple Data. */
    else if( DeltaCounter < State->MaxDeltaCounter )
    {
        State->MaxDeltaCounter = Config->MaxDeltaCounterInit;
        State->LastValidCounter = ReceivedCounter;
        State->LostData = DeltaCounter - E2E_COUNTER_1;
        /* NoNewOrRepeatedDataCounter is in config limited range. */
        if( State->NoNewOrRepeatedDataCounter <= Config->MaxNoNewOrRepeatedData )
        {
            State->NoNewOrRepeatedDataCounter = E2E_INIT_0;
            /* SyncCounter value greater than zero,continuity check for the
               counter is not finalized yet ,DeltaCounter in congfig limit. */
            if( State->SyncCounter > E2E_JUDGE_0 )
            {
                /* continuity check for the counter decrease one ,
                   DeltaCounter in congfig limit. */
                State->SyncCounter--;
                State->Status = E2E_P4BITXORSTATUS_SYNC;
            }
            /* SyncCounter value greater than zero,continuity check for the
               counter is finalized,DeltaCounter in congfig limit. */
            else
            {
                State->Status = E2E_P4BITXORSTATUS_OKSOMELOST;
            }
        }
        /* NoNewOrRepeatedDataCounter is out of limited range. */
        else
        {
            State->NoNewOrRepeatedDataCounter = E2E_INIT_0;
            State->SyncCounter = Config->SyncCounterInit;
            State->Status = E2E_P4BITXORSTATUS_SYNC;
        }
    }
    /* DeltaCounter is out of limited range, wrong sequence status. */
    else
    {
        State->NoNewOrRepeatedDataCounter = E2E_INIT_0;
        State->SyncCounter = Config->SyncCounterInit;
        /* Synchronize status. */
        if( State->SyncCounter > E2E_JUDGE_0 )
        {
            State->MaxDeltaCounter = Config->MaxDeltaCounterInit;
            State->LastValidCounter = ReceivedCounter;
        }
        State->Status = E2E_P4BITXORSTATUS_WRONGSEQUENCE;
    }
}

/*
********************************************************************************
* Function Name: E2E_P4BitXORProtect_ChkParam
*
* Explanation: Check Parameter for E2E_P4BitXORProtect.(Synchronous)
*
* param: ConfigPtr: Pointer to static configuration.
*        StatePtr: Pointer to port/data communication state.
*        DataPtr: Pointer to Data to be transmitted.
*
* retval: Std_ReturnType
********************************************************************************
*/
static FUNC(uint8, E2E_CODE) E2E_P4BitXORProtect_ChkParam
(
    P2CONST(E2E_P4BitXORConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr,
    P2CONST(E2E_P4BitXORProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
    P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr
)
{
    uint8 rtrnValu = E2E_E_INPUTERR_NULL;

    if( (NULL_PTR == ConfigPtr) || (NULL_PTR == StatePtr) || (NULL_PTR == DataPtr) )
    {
        /* At least one pointer parameter is a NULL pointer. */
        rtrnValu = E2E_E_INPUTERR_NULL;
    }
    else
    {
        if( StatePtr->Counter > E2E_P4BITXORPROTECT_COUNTERMAX )
        {
            /* Counter is out of range (0-15). */
            rtrnValu = E2E_E_INPUTERR_WRONG;
        }
        else
        {
            /* All parameters are ok. */
            rtrnValu = E2E_E_OK;
        }
    }

    return rtrnValu;
}

/*
********************************************************************************
* Function Name: E2E_P4BitXORCheck_ChkParam
*
* Explanation: Check Parameter for E2E_P4BitXORCheck.(Synchronous)
*
* param: ConfigPtr: Pointer to static configuration.
*        StatePtr: Pointer to port/data communication state.
*        DataPtr: Pointer to Data to be transmitted.
*
* retval: Std_ReturnType
********************************************************************************
*/
static FUNC(uint8, E2E_CODE) E2E_P4BitXORCheck_ChkParam
(
    P2CONST(E2E_P4BitXORConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr,
    P2CONST(E2E_P4BitXORCheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
    P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr
)
{
    uint8 rtrnValu = E2E_E_INPUTERR_NULL;

    if( (NULL_PTR == ConfigPtr) || (NULL_PTR == StatePtr) || (NULL_PTR == DataPtr) )
    {
        /* At least one pointer parameter is a NULL pointer. */
        rtrnValu = E2E_E_INPUTERR_NULL;
    }
    else
    {
       /* All parameters are ok. */
        rtrnValu = E2E_E_OK;
    }

    return rtrnValu;
}

/*
********************************************************************************
* Function Name: E2E_P4BitXOR_ChecksumCalculate
*
* Explanation: Protect&Check Calculate Checksum.(Synchronous)
*
* param: ConfigPtr: Pointer to static configuration.
*        DataPtr: Pointer to Data to be transmitted.
*
* retval: Checksum Value
********************************************************************************
*/
static FUNC(uint8, E2E_CODE) E2E_P4BitXOR_ChecksumCalculate
(
    P2CONST(E2E_P4BitXORConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr,
    P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr
)
{
    uint8 checksumVal = E2E_INIT_0;
    uint16 checksumLen = E2E_INIT_0;

    /* Compute checksum over the area except counter and checksum byte. */
    if( ConfigPtr->ChecksumOffset >= E2E_8BIT )
    {
        checksumLen = ConfigPtr->ChecksumOffset / E2E_8BIT;
        checksumVal = Crc_CalculateXORAccumulation(DataPtr, checksumLen);
    }
    /* Compute CRC over the area after the CRC (if CRC is not the last byte). */
    if( (ConfigPtr->ChecksumOffset / E2E_8BIT)
         < ((ConfigPtr->DataLength / E2E_8BIT) - E2E_INIT_1) )
    {
        checksumLen = (ConfigPtr->DataLength / E2E_8BIT)
                    - (ConfigPtr->ChecksumOffset / E2E_8BIT) - E2E_INIT_1;
        checksumVal = Crc_CalculateXORAccumulation
                      (&DataPtr[(ConfigPtr->ChecksumOffset / E2E_8BIT) + E2E_INIT_1],
                       checksumLen);
    }

    return checksumVal;
}

/*
********************************************************************************
* Function Name: E2E_P4BitXORProtect
*
* Explanation: Protects the array/buffer to be transmitted using the E2E profile
*              1.This includes checksum calculation, handling of counter and
*              Data ID.(Synchronous)
*
* param: ConfigPtr: Pointer to static configuration.
*        StatePtr: Pointer to port/data communication state.
*        DataPtr: Pointer to Data to be transmitted.
*
* retval: Std_ReturnType
********************************************************************************
*/
FUNC(Std_ReturnType, E2E_CODE) E2E_P4BitXORProtect
(
    P2CONST(E2E_P4BitXORConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr,
    P2VAR(E2E_P4BitXORProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
    P2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr
)
{
    Std_ReturnType rtrnValu = E2E_E_INPUTERR_NULL;
    uint8 checksumVal = E2E_INIT_0;

    /* Check all parameters. */
    rtrnValu = E2E_P4BitXORProtect_ChkParam(ConfigPtr, StatePtr, DataPtr);
    /* All parameters are valid. */
    if( E2E_E_OK == rtrnValu )
    {
        /* Counter in low nibble. */
        if( E2E_JUDGE_0 == (ConfigPtr->CounterOffset % E2E_8BIT) )
        {
            /* Counter in high nibble. */
            DataPtr[ConfigPtr->CounterOffset / E2E_8BIT]
              = (uint8)
                ((DataPtr[ConfigPtr->CounterOffset / E2E_8BIT] & E2E_HIGH_NIBBLE)
                | ((StatePtr->Counter) & E2E_LOW_NIBBLE));
        }
        else
        {
            /* Set counter. */
            DataPtr[ConfigPtr->CounterOffset / E2E_8BIT]
              = (uint8)
                ((DataPtr[ConfigPtr->CounterOffset / E2E_8BIT] & E2E_LOW_NIBBLE)
                | ((uint8)(StatePtr->Counter << E2E_4BIT) & E2E_HIGH_NIBBLE));
        }
        /* Calculate Checksum over Data. */
        checksumVal = E2E_P4BitXOR_ChecksumCalculate(ConfigPtr, DataPtr);
        checksumVal = ((checksumVal & E2E_HIGH_NIBBLE) >> E2E_4BIT) ^ (checksumVal & E2E_LOW_NIBBLE);
        checksumVal = (checksumVal ^ (StatePtr->Counter)) & E2E_LOW_NIBBLE;
        if( E2E_JUDGE_0 == (ConfigPtr->ChecksumOffset % E2E_8BIT) )
         {
             /* Checksum is in high nibble. */
             DataPtr[ConfigPtr->ChecksumOffset / E2E_8BIT]
               = ((DataPtr[ConfigPtr->ChecksumOffset / E2E_8BIT] & E2E_HIGH_NIBBLE)
                 | ((checksumVal) & E2E_LOW_NIBBLE));
         }
         else
         {
             /* Set checksumVal. */
             DataPtr[ConfigPtr->ChecksumOffset / E2E_8BIT]
               = ((DataPtr[ConfigPtr->ChecksumOffset / E2E_8BIT] & E2E_LOW_NIBBLE)
                 | ((uint8)(checksumVal << E2E_4BIT) & E2E_HIGH_NIBBLE));
         }
        /* Increment the counter modulo 16, next value after 15 is 0. */
        StatePtr->Counter = (StatePtr->Counter + E2E_INIT_1) % E2E_P4BITXORPROTECT_COUNTERMOD;
    }

    return rtrnValu;
}

/*
********************************************************************************
* Function Name: E2E_P4BitXORProtectInit
*
* Explanation: Initializes the protection state.(Synchronous)
*
* param: StatePtr: Pointer to port/data communication state.
*
* retval: Std_ReturnType
********************************************************************************
*/
FUNC(Std_ReturnType, E2E_CODE) E2E_P4BitXORProtectInit
(
    P2VAR(E2E_P4BitXORProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr
)
{
    Std_ReturnType rtrnValu = E2E_E_INPUTERR_NULL;

    /* The parameter is valid. */
    if( NULL_PTR != StatePtr )
    {
        /* Initialize the counter. */
        StatePtr->Counter = E2E_INIT_0;
        rtrnValu = E2E_E_OK;
    }

    return rtrnValu;
}

/*
********************************************************************************
* Function Name: E2E_P4BitXORCheck
*
* Explanation: Checks the Data received using the E2E profile 4BitXOR. This
*              includes CRC calculation,handling of Counter and Data ID.
*              (Synchronous)
*
* param: Config: Pointer to static configuration
*        Data: Pointer to received data
*        State: Pointer to port/data communication state
*
* retval: Std_ReturnType
********************************************************************************
*/
FUNC(Std_ReturnType, E2E_CODE) E2E_P4BitXORCheck
(
    P2CONST(E2E_P4BitXORConfigType, AUTOMATIC, E2E_APPL_DATA) Config,
    P2VAR(E2E_P4BitXORCheckStateType, AUTOMATIC, E2E_APPL_DATA) State,
    P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) Data
)
{
    Std_ReturnType rtrnValu = E2E_E_INPUTERR_NULL;
    uint8 receivedCounter = E2E_INIT_0;
    uint8 receivedChk = E2E_INIT_0;
    uint8 calculatedChk = E2E_INIT_0;
    uint8 deltaCounter = E2E_INIT_0;

    rtrnValu = E2E_P4BitXORCheck_ChkParam(Config, State, Data);
    /* Check all parameters */
    if( E2E_E_OK == rtrnValu )
    {
        /* At every function invocation, the maximum allowed delta
           between previous and current Counter is incremented. */
        if( State->MaxDeltaCounter < E2E_P4BITXORPROTECT_COUNTERMAX )
        {
            State->MaxDeltaCounter++;
        }
        /* If any new data is available to be checked. */
        if( TRUE == State->NewDataAvailable )
        {
            /* Read the Counter from Data. */
            if( E2E_JUDGE_0 == (Config->CounterOffset % E2E_8BIT) )
            {
                receivedCounter
                  = Data[Config->CounterOffset / E2E_8BIT] & E2E_LOW_NIBBLE;
            }
            else
            {
                receivedCounter
                  = (Data[Config->CounterOffset / E2E_8BIT] >> E2E_4BIT)
                    & E2E_LOW_NIBBLE;
            }
            /* Read Checksum from Data. */
            if( E2E_JUDGE_0 == (Config->ChecksumOffset % E2E_8BIT) )
            {
                receivedChk
                  = Data[Config->ChecksumOffset / E2E_8BIT] & E2E_LOW_NIBBLE;
            }
            else
            {
                receivedChk
                  = (Data[Config->ChecksumOffset / E2E_8BIT] >> E2E_4BIT)
                    & E2E_LOW_NIBBLE;
            }
            /* Calculate Checksum in the same way as the Sender did. */
            calculatedChk = E2E_P4BitXOR_ChecksumCalculate(Config, Data);
            calculatedChk = ((calculatedChk & E2E_HIGH_NIBBLE) >> E2E_4BIT) ^ (calculatedChk & E2E_LOW_NIBBLE);
            calculatedChk = (calculatedChk ^ (receivedCounter)) & E2E_LOW_NIBBLE;
            /* Received Checksum is ok? */
            if( receivedChk == calculatedChk )
            {
                /* Check if any correct data has already be received. */
                /* This is the first message with correct Checksum,
                   WaitForFirstData is therefore set to false.
                   Counter is not checked as it cannot be done yet. */
                if( TRUE == State->WaitForFirstData )
                {
                    State->WaitForFirstData= FALSE;
                    State->MaxDeltaCounter
                          = Config->MaxDeltaCounterInit;
                    State->LastValidCounter = receivedCounter;
                    State->Status = E2E_P4BITXORSTATUS_INITIAL;
                }
                /* Compute the delta Counter, taking into account the overflow. */
                else
                {
                    if( receivedCounter >= State->LastValidCounter )
                    {
                        deltaCounter
                          = receivedCounter - State->LastValidCounter;
                    }
                    else
                    {
                        deltaCounter
                          = E2E_P4BITXORPROTECT_COUNTERMOD
                          + receivedCounter - State->LastValidCounter;
                    }
                    /* Checksum is ok, verify the counter. */
                    E2E_P4BitXORCheck_ChkDeltaCounter(deltaCounter,
                                                      receivedCounter,
                                                      State,
                                                      Config);
                }
            }
            /* Received Checksum is diffrent from Calculated Checksum. */
            else
            {
                State->Status = E2E_P4BITXORSTATUS_WRONGCHECKSUM;
            }

        }
        else
        {
            /* Increase NoNewOrRepeatedDataCounter. */
            if( State->NoNewOrRepeatedDataCounter < E2E_P4BITXORPROTECT_COUNTERMAX )
            {
                State->NoNewOrRepeatedDataCounter++;
            }
            State->Status = E2E_P4BITXORSTATUS_NONEWDATA;
        }
    }

    return rtrnValu;
}

/*
********************************************************************************
* Function Name: E2E_P4BitXORCheckInit
*
* Explanation: Initializes the check state.(Synchronous)
*
* param: StatePtr: Pointer to port/data communication state.
*
* retval: Std_ReturnType
********************************************************************************
*/
FUNC(Std_ReturnType, E2E_CODE) E2E_P4BitXORCheckInit
(
    P2VAR(E2E_P4BitXORCheckStateType, AUTOMATIC, E2E_APPL_DATA) State
)
{
    Std_ReturnType rtrnValu = E2E_E_INPUTERR_NULL;

    /* The parameter is valid. */
    if( NULL_PTR != State )
    {
        State->LastValidCounter = E2E_INIT_0;
        State->MaxDeltaCounter = E2E_INIT_0;
        State->WaitForFirstData = FALSE;
        State->NewDataAvailable = TRUE;
        State->LostData = E2E_INIT_0;
        State->Status = E2E_P4BITXORSTATUS_NONEWDATA;
        State->SyncCounter = E2E_INIT_0;
        State->NoNewOrRepeatedDataCounter = E2E_INIT_0;
        rtrnValu = E2E_E_OK;
    }

    return rtrnValu;
}

/*
********************************************************************************
* Function Name: E2E_P4BitXORMapStatusToSM
*
* Explanation: The function maps the check status of Profile 4BitXOR to a generic
*              check status,which can be used by E2E state machine check
*              function. (Synchronous)
*
* param: CheckReturn: Return value of the E2E_P4BitXORCheck function.
*        Status: Status determined by E2E_P4BitXORCheck function.
*
* retval: E2E_PCheckStatusType
********************************************************************************
*/
FUNC(E2E_PCheckStatusType, E2E_CODE) E2E_P4BitXORMapStatusToSM
(
    Std_ReturnType CheckReturn,
    E2E_P4BitXORCheckStatusType Status
)
{
    E2E_PCheckStatusType rtrnValu = E2E_P_ERROR;
    E2E_PCheckStatusType statusSync = E2E_P_ERROR;
    E2E_PCheckStatusType statusInitial = E2E_P_ERROR;

    if( E2E_E_OK == CheckReturn )
    {
        switch( Status )
        {
            case E2E_P4BITXORSTATUS_OK:
                /* The checks of the Data in this cycle were successful. */
                rtrnValu = E2E_P_OK;
                break;
            case E2E_P4BITXORSTATUS_OKSOMELOST:
                /* The checks of the Data in this cycle were successful. */
                rtrnValu = E2E_P_OK;
                break;
            case E2E_P4BITXORSTATUS_INITIAL:
                /* Return depending on profileBehavior. */
                rtrnValu = statusInitial;
                break;
            case E2E_P4BITXORSTATUS_WRONGCHECKSUM:
                /* Error not related to counters occurred or the
                   return of the check function was not OK. */
                rtrnValu = E2E_P_ERROR;
                break;
            case E2E_P4BITXORSTATUS_REPEATED:
                /* Data has a repeated counter. */
                rtrnValu = E2E_P_REPEATED;
                break;
            case E2E_P4BITXORSTATUS_NONEWDATA:
                /* No new data is available. */
                rtrnValu = E2E_P_NONEWDATA;
                break;
            case E2E_P4BITXORSTATUS_WRONGSEQUENCE:
                /* The checks of the Data in this cycle were successful,
                   counter jumpchanged more than the allowed delta. */
                rtrnValu = E2E_P_WRONGSEQUENCE;
                break;
            case E2E_P4BITXORSTATUS_SYNC:
                /* Return depending on profileBehavior. */
                rtrnValu = statusSync;
                break;
            default:
                break;
        }
    }

    return rtrnValu;
}

#define E2E_STOP_SEC_CODE
#include "E2E_MemMap.h"
