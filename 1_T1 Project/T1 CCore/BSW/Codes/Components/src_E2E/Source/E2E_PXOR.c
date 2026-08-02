/*
********************************************************************************
*
* File name: E2E_PXOR.c
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
* Author/Date: LiDY/2023.08.03
* Change: Compilation warning optimization
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
#include "E2E_PXOR.h"

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

static FUNC(void, E2E_CODE) E2E_PXORCheck_ChkDeltaCounter
(
    uint8 DeltaCounter,
    uint8 ReceivedCounter,
    P2VAR(E2E_PXORCheckStateType, AUTOMATIC, E2E_APPL_DATA) State,
    P2CONST(E2E_PXORConfigType, AUTOMATIC, E2E_APPL_DATA) Config
);
static FUNC(uint8, E2E_CODE) E2E_PXORProtect_ChkParam
(
    P2CONST(E2E_PXORConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr,
    P2CONST(E2E_PXORProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
    P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr
);
static FUNC(uint8, E2E_CODE) E2E_PXORCheck_ChkParam
(
    P2CONST(E2E_PXORConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr,
    P2CONST(E2E_PXORCheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
    P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr
);
static FUNC(uint8, E2E_CODE) E2E_PXOR_ChecksumCalculate
(
    P2CONST(E2E_PXORConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr,
    P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr,
    uint8 counter
);
static FUNC(void, E2E_CODE) E2E_PXOR_WriteCounter
(
    P2CONST(E2E_PXORConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr,
    P2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr,
    uint8 counterVal
);
static FUNC(uint8, E2E_CODE) E2E_PXOR_ReadCounter
(
    P2CONST(E2E_PXORConfigType, AUTOMATIC, E2E_APPL_DATA) Config,
    P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) Data
);
static FUNC(uint8, E2E_CODE) E2E_PXOR_CalculateDeltaCounter
(
    P2VAR(E2E_PXORCheckStateType, AUTOMATIC, E2E_APPL_DATA) State,
    uint8 receivedCounter
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
* Function Name: E2E_PXORCheck_ChkDeltaCounter
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
static FUNC(void, E2E_CODE) E2E_PXORCheck_ChkDeltaCounter
(
    uint8 DeltaCounter,
    uint8 ReceivedCounter,
    P2VAR(E2E_PXORCheckStateType, AUTOMATIC, E2E_APPL_DATA) State,
    P2CONST(E2E_PXORConfigType, AUTOMATIC, E2E_APPL_DATA) Config
)
{
    if( E2E_JUDGE_0 == DeltaCounter )
    {
        if( State->NoNewOrRepeatedDataCounter < E2E_PXORPROTECT_COUNTERMAX )
        {
            /* Increment NoNewOrRepeatedDataCounter by 1. */
            State->NoNewOrRepeatedDataCounter++;
        }
        /* Set status to E2E_PXORSTATUS_REPEATED. */
        State->Status = E2E_PXORSTATUS_REPEATED;
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
                State->Status = E2E_PXORSTATUS_SYNC;
            }
            /* SyncCounter is zero, no Data has been lost since the last correct
               data reception. */
            else
            {
                State->Status = E2E_PXORSTATUS_OK;
            }
        }
        /* NoNewOrRepeatedDataCounter is out of limited range. */
        else
        {
            State->NoNewOrRepeatedDataCounter = E2E_INIT_0;
            State->SyncCounter = Config->SyncCounterInit;
            State->Status = E2E_PXORSTATUS_SYNC;
        }
    }
    /* Lose multiple data. */
    else if( DeltaCounter < State->MaxDeltaCounter )
    {
        State->MaxDeltaCounter = Config->MaxDeltaCounterInit;
        State->LastValidCounter = ReceivedCounter;
        State->LostData = DeltaCounter - E2E_COUNTER_1;
        /* NoNewOrRepeatedDataCounter is in configured limited range. */
        if( State->NoNewOrRepeatedDataCounter <= Config->MaxNoNewOrRepeatedData )
        {
            State->NoNewOrRepeatedDataCounter = E2E_INIT_0;
            /* SyncCounter is greater than zero, continuily check for the
               counter is not finalized yet, DeltaCounter is in limited range. */
            if( State->SyncCounter > E2E_JUDGE_0 )
            {
                /* Decrease SyncCounter by 1. */
                State->SyncCounter--;
                State->Status = E2E_PXORSTATUS_SYNC;
            }
            /* SyncCounter is greater than zero, continuily check for the
               counter is finalized, DeltaCounter in congfigured limit range. */
            else
            {
                State->Status = E2E_PXORSTATUS_OKSOMELOST;
            }
        }
        /* NoNewOrRepeatedDataCounter is out of limited range. */
        else
        {
            State->NoNewOrRepeatedDataCounter = E2E_INIT_0;
            State->SyncCounter = Config->SyncCounterInit;
            State->Status = E2E_PXORSTATUS_SYNC;
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
        State->Status = E2E_PXORSTATUS_WRONGSEQUENCE;
    }
}

/*
********************************************************************************
* Function Name: E2E_PXORProtect_ChkParam
*
* Explanation: Check Parameter for E2E_PXORProtect.(Synchronous)
*
* param: ConfigPtr: Pointer to static configuration.
*        StatePtr: Pointer to port/data communication state.
*        DataPtr: Pointer to Data to be transmitted.
*
* retval: Std_ReturnType
********************************************************************************
*/
static FUNC(uint8, E2E_CODE) E2E_PXORProtect_ChkParam
(
    P2CONST(E2E_PXORConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr,
    P2CONST(E2E_PXORProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
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
        if( StatePtr->Counter > E2E_PXORPROTECT_COUNTERMAX )
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
* Function Name: E2E_PXORCheck_ChkParam
*
* Explanation: Check Parameter for E2E_PXORCheck.(Synchronous)
*
* param: ConfigPtr: Pointer to static configuration.
*        StatePtr: Pointer to port/data communication state.
*        DataPtr: Pointer to Data to be transmitted.
*
* retval: Std_ReturnType
********************************************************************************
*/
static FUNC(uint8, E2E_CODE) E2E_PXORCheck_ChkParam
(
    P2CONST(E2E_PXORConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr,
    P2CONST(E2E_PXORCheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
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
* Function Name: E2E_PXOR_ChecksumCalculate
*
* Explanation: Protect&Check Calculate Checksum.(Synchronous)
*
* param: ConfigPtr: Pointer to static configuration.
*        DataPtr: Pointer to Data to be transmitted.
*
* retval: Checksum Value
********************************************************************************
*/
static FUNC(uint8, E2E_CODE) E2E_PXOR_ChecksumCalculate
(
    P2CONST(E2E_PXORConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr,
    P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr,
    uint8 counter
)
{
    uint8 checksumVal = E2E_INIT_0;
    uint8 collisionSig = E2E_INIT_0;
	uint8 counterSig = E2E_INIT_0;

    E2E_DUMMY_STATEMENT(ConfigPtr);
    /* Get collision signal from data. */
    collisionSig = DataPtr[E2E_INDEX_0];
    /* Get counter signal from data. */
    counterSig = (counter << E2E_4BIT) & E2E_HIGH_NIBBLE;
	/* Calculate checksum. */
    checksumVal = collisionSig ^ counterSig;

    return checksumVal;
}

/*
********************************************************************************
* Function Name: E2E_PXOR_WriteCounter
*
* Explanation: Write Counter to data.(Synchronous)
*
* param: ConfigPtr: Pointer to static configuration.
*        DataPtr: Pointer to Data to be transmitted.
*        counterVal: Counter.
*
* retval: none
********************************************************************************
*/
static FUNC(void, E2E_CODE) E2E_PXOR_WriteCounter
(
    P2CONST(E2E_PXORConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr,
    P2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr,
    uint8 counterVal
)
{
    /* Counter is in low nibble. */
    if( E2E_JUDGE_0 == (ConfigPtr->CounterOffset % E2E_8BIT) )
    {
        DataPtr[ConfigPtr->CounterOffset / E2E_8BIT]
          = (uint8)
            ((DataPtr[ConfigPtr->CounterOffset / E2E_8BIT] & E2E_HIGH_NIBBLE)
            | (counterVal & E2E_LOW_NIBBLE));
    }
	/* Counter is in high nibble. */
    else
    {
        /* Write counter to data. */
        DataPtr[ConfigPtr->CounterOffset / E2E_8BIT]
          = (uint8)
            ((DataPtr[ConfigPtr->CounterOffset / E2E_8BIT] & E2E_LOW_NIBBLE)
            | ((uint8)(counterVal << E2E_4BIT) & E2E_HIGH_NIBBLE));
    }
}

/*
********************************************************************************
* Function Name: E2E_PXOR_ReadCounter
*
* Explanation: Read Counter from data.(Synchronous)
*
* param: ConfigPtr: Pointer to static configuration.
*        DataPtr: Pointer to Data to be transmitted.
*
* retval: counter
********************************************************************************
*/
static FUNC(uint8, E2E_CODE) E2E_PXOR_ReadCounter
(
    P2CONST(E2E_PXORConfigType, AUTOMATIC, E2E_APPL_DATA) Config,
    P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) Data
)
{
    uint8 receivedCounter;

    /* Counter is in low nibble. */
    if( E2E_JUDGE_0 == (Config->CounterOffset % E2E_8BIT) )
    {
        /* Read Counter from data. */
        receivedCounter = Data[Config->CounterOffset / E2E_8BIT] & E2E_LOW_NIBBLE;
    }
    /* Counter is in high nibble. */
    else
    {
        /* Read Counter from data. */
        receivedCounter
          = (Data[Config->CounterOffset / E2E_8BIT] >> E2E_4BIT) & E2E_LOW_NIBBLE;
    }

     return receivedCounter;
}

/*
********************************************************************************
* Function Name: E2E_PXOR_CalculateDeltaCounter
*
* Explanation: Calculate delta counter.(Synchronous)
*
* param: ConfigPtr: Pointer to static configuration.
*        DataPtr: Pointer to Data to be transmitted.
*
* retval: DeltaCounter
********************************************************************************
*/
static FUNC(uint8, E2E_CODE) E2E_PXOR_CalculateDeltaCounter
(
    P2VAR(E2E_PXORCheckStateType, AUTOMATIC, E2E_APPL_DATA) State,
    uint8 receivedCounter
)
{
    uint8 deltaCounter;

    /* ReceivedCounter is greater than the last one. */
    if( receivedCounter >= State->LastValidCounter )
    {
        deltaCounter = receivedCounter - State->LastValidCounter;
    }
    /* ReceivedCounter enters the next cycle. */
    else
    {
        deltaCounter
          = E2E_PXORPROTECT_COUNTERMOD + receivedCounter - State->LastValidCounter;
    }

    return deltaCounter;
}

/*
********************************************************************************
* Function Name: E2E_PXORProtect
*
* Explanation: Protects the array/buffer to be transmitted using the E2E profile
*              XOR, which includes checksum calculation and handling of counter.
*              (Synchronous)
*
* param: ConfigPtr: Pointer to static configuration.
*        StatePtr: Pointer to port/data communication state.
*        DataPtr: Pointer to Data to be transmitted.
*
* retval: Std_ReturnType
********************************************************************************
*/
FUNC(Std_ReturnType, E2E_CODE) E2E_PXORProtect
(
    P2CONST(E2E_PXORConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr,
    P2VAR(E2E_PXORProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
    P2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr
)
{
    Std_ReturnType rtrnValu = E2E_E_INPUTERR_NULL;
    uint8 checksumVal = E2E_INIT_0;
    uint8 counterVal = StatePtr->Counter;

    /* Check all parameters. */
    rtrnValu = E2E_PXORProtect_ChkParam(ConfigPtr, StatePtr, DataPtr);
    /* All parameters are valid. */
    if( E2E_E_OK == rtrnValu )
    {
        /* Write counter to data. */
        E2E_PXOR_WriteCounter(ConfigPtr, DataPtr, counterVal);
        /* Calculate Checksum over Data. */
        checksumVal = E2E_PXOR_ChecksumCalculate(ConfigPtr, DataPtr, counterVal);
        /* Write checksum to data. */
        DataPtr[ConfigPtr->ChecksumOffset / E2E_8BIT] = checksumVal & E2E_FULL_BYTE;
        /* Increment the counter by 1, next value after 15 is 0. */
        StatePtr->Counter
          = (StatePtr->Counter + E2E_INIT_1) % E2E_PXORPROTECT_COUNTERMOD;
    }

    return rtrnValu;
}

/*
********************************************************************************
* Function Name: E2E_PXORProtectInit
*
* Explanation: Initializes the protection state.(Synchronous)
*
* param: StatePtr: Pointer to port/data communication state.
*
* retval: Std_ReturnType
********************************************************************************
*/
FUNC(Std_ReturnType, E2E_CODE) E2E_PXORProtectInit
(
    P2VAR(E2E_PXORProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr
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
* Function Name: E2E_PXORCheck
*
* Explanation: Checks the Data received using the E2E profile XOR which
*              includes Checksum calculation, and the handling of Counter.
*              (Synchronous)
*
* param: Config: Pointer to static configuration.
*        State: Pointer to port/data communication state.
*        Data: Pointer to received data.
*
* retval: Std_ReturnType
********************************************************************************
*/
FUNC(Std_ReturnType, E2E_CODE) E2E_PXORCheck
(
    P2CONST(E2E_PXORConfigType, AUTOMATIC, E2E_APPL_DATA) Config,
    P2VAR(E2E_PXORCheckStateType, AUTOMATIC, E2E_APPL_DATA) State,
    P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) Data
)
{
    Std_ReturnType rtrnValu = E2E_E_INPUTERR_NULL;
    uint8 receivedCounter = E2E_INIT_0;
    uint8 receivedChk = E2E_INIT_0;
    uint8 calculatedChk = E2E_INIT_0;
    uint8 deltaCounter = E2E_INIT_0;

    rtrnValu = E2E_PXORCheck_ChkParam(Config, State, Data);
    /* Check all parameters */
    if( E2E_E_OK == rtrnValu )
    {
        /* At every function invocation, the maximum allowed delta
           between previous and current Counter is incremented. */
        if( State->MaxDeltaCounter < E2E_PXORPROTECT_COUNTERMAX )
        {
            State->MaxDeltaCounter++;
        }
        /* If any new data is available to be checked. */
        if( TRUE == State->NewDataAvailable )
        {
            /* Read Counter from Data. */
            receivedCounter = E2E_PXOR_ReadCounter(Config, Data);
            /* Read Checksum from Data. */
            receivedChk = Data[Config->ChecksumOffset / E2E_8BIT];
            /* Calculate Checksum in the same way as the Sender did. */
            calculatedChk = E2E_PXOR_ChecksumCalculate(Config, Data, receivedCounter);
            /* Received Checksum is ok? */
            if( receivedChk == calculatedChk )
            {
                /* Check if any correct data has already be received. */
                /* This is the first message with correct Checksum. */
                if( TRUE == State->WaitForFirstData )
                {
                    State->WaitForFirstData= FALSE;
                    State->MaxDeltaCounter = Config->MaxDeltaCounterInit;
                    State->LastValidCounter = receivedCounter;
                    State->Status = E2E_PXORSTATUS_INITIAL;
                }
                else
                {
                    /* Calculate delta counter. */
                    deltaCounter = E2E_PXOR_CalculateDeltaCounter(State, receivedCounter);
                    /* Checksum is ok, verify the counter. */
                    E2E_PXORCheck_ChkDeltaCounter(deltaCounter,
                                                  receivedCounter,
                                                  State,
                                                  Config);
                }
            }
            /* Received Checksum is diffrent from Calculated Checksum. */
            else
            {
                State->Status = E2E_PXORSTATUS_WRONGCHECKSUM;
            }
        }
        else
        {
            /* Increase NoNewOrRepeatedDataCounter by 1. */
            if( State->NoNewOrRepeatedDataCounter < E2E_PXORPROTECT_COUNTERMAX )
            {
                State->NoNewOrRepeatedDataCounter++;
            }
            State->Status = E2E_PXORSTATUS_NONEWDATA;
        }
    }

    return rtrnValu;
}

/*
********************************************************************************
* Function Name: E2E_PXORCheckInit
*
* Explanation: Initializes the check state.(Synchronous)
*
* param: StatePtr: Pointer to port/data communication state.
*
* retval: Std_ReturnType
********************************************************************************
*/
FUNC(Std_ReturnType, E2E_CODE) E2E_PXORCheckInit
(
    P2VAR(E2E_PXORCheckStateType, AUTOMATIC, E2E_APPL_DATA) State
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
        State->Status = E2E_PXORSTATUS_NONEWDATA;
        State->SyncCounter = E2E_INIT_0;
        State->NoNewOrRepeatedDataCounter = E2E_INIT_0;
        rtrnValu = E2E_E_OK;
    }

    return rtrnValu;
}

/*
********************************************************************************
* Function Name: E2E_PXORMapStatusToSM
*
* Explanation: The function maps the check status of Profile XOR to a generic
*              check status,which can be used by E2E state machine check
*              function. (Synchronous)
*
* param: CheckReturn: Return value of the E2E_PXORCheck function.
*        Status: Status determined by E2E_PXORCheck function.
*
* retval: E2E_PCheckStatusType
********************************************************************************
*/
FUNC(E2E_PCheckStatusType, E2E_CODE) E2E_PXORMapStatusToSM
(
    Std_ReturnType CheckReturn,
    E2E_PXORCheckStatusType Status
)
{
    E2E_PCheckStatusType rtrnValu = E2E_P_ERROR;
    E2E_PCheckStatusType statusSync = E2E_P_ERROR;
    E2E_PCheckStatusType statusInitial = E2E_P_ERROR;

    if( E2E_E_OK == CheckReturn )
    {
        switch( Status )
        {
            case E2E_PXORSTATUS_OK:
                /* The checks of the Data in this cycle were successful. */
                rtrnValu = E2E_P_OK;
                break;
            case E2E_PXORSTATUS_OKSOMELOST:
                /* The checks of the Data in this cycle were successful. */
                rtrnValu = E2E_P_OK;
                break;
            case E2E_PXORSTATUS_INITIAL:
                /* Return depending on profileBehavior. */
                rtrnValu = statusInitial;
                break;
            case E2E_PXORSTATUS_WRONGCHECKSUM:
                /* Error not related to counters occurred or the
                   return of the check function was not OK. */
                rtrnValu = E2E_P_ERROR;
                break;
            case E2E_PXORSTATUS_REPEATED:
                /* Data has a repeated counter. */
                rtrnValu = E2E_P_REPEATED;
                break;
            case E2E_PXORSTATUS_NONEWDATA:
                /* No new data is available. */
                rtrnValu = E2E_P_NONEWDATA;
                break;
            case E2E_PXORSTATUS_WRONGSEQUENCE:
                /* The checks of the Data in this cycle were successful,
                   counter jumpchanged more than the allowed delta. */
                rtrnValu = E2E_P_WRONGSEQUENCE;
                break;
            case E2E_PXORSTATUS_SYNC:
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
