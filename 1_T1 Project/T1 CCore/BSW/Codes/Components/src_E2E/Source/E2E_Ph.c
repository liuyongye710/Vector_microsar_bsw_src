/*
********************************************************************************
*
* File name: E2E_Ph.c
*
* Copyright 2021-2024 Neusoft Reach Corporation.All rights reserved.
*
********************************************************************************
*
* History
*-------------------------------------------------------------------------------
********************************************************************************
* Version: 1.0
* Author/Date: XieYN/2021.11.03
* Change: New created.
* Cause: New
********************************************************************************
* Version: 1.1
* Author/Date: XieYN/2021.11.12
* Change: 1. Modify file name and function name.
*         2. Modify code format.
*         3. Modify E2E_PhCheck_ChkParam/E2E_PhProtect_ChkParam parameter type.
*         4. Add E2E_PhCalculate_DataIDSum.
* Cause: Optimization
********************************************************************************
* Version: 1.2
* Author/Date: XieYN/2022.09.26
* Change: Modify E2E_Counter_1 to E2E_COUNTER_1.
* Cause: Bugfix
********************************************************************************
* Version: 1.3
* Author/Date: XieYN/2022.11.10
* Change: Modify polyspace problems.
* Cause: Optimization
********************************************************************************
* Version: 1.4
* Author/Date: LiDaY/2024.02.05
* Change: Modifying the label of the input parameter Ptrclass for E2E function
*         and addressing some code inconsistencies.
* Cause: Optimization
********************************************************************************
* Version: 1.5
* Author/Date: LiDaY/2024.03.18
* Change: Modifying the label of the input parameter Ptrclass for E2E function
*         and addressing some code inconsistencies.
* Cause: Optimization
********************************************************************************
* Version: 1.6
* Author/Date: LiDaY/2024.04.25
* Change: Add a memory-map label to function and variable declarations.
* Cause: Bugfix
********************************************************************************
* Version: 3.0
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
#include "E2E_Ph.h"

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

static FUNC(Std_ReturnType, E2E_CODE) E2E_PhCheck_ChkParam
(
    P2CONST(E2E_PhConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr,
    P2VAR(E2E_PhCheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
    P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr
);

static FUNC(Std_ReturnType, E2E_CODE) E2E_PhProtect_ChkParam
(
    P2CONST(E2E_PhConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr,
    P2VAR(E2E_PhProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
    P2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr
);

static FUNC(uint8, E2E_CODE) E2E_PhCalculate_DataIDSum
(
    P2CONST(E2E_PhConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr
);

static FUNC(void, E2E_CODE) E2E_PhCheck_ChkDeltaCounter
(
    uint8 DeltaCounter,
    uint8 ReceivedCounter,
    P2VAR(E2E_PhCheckStateType, AUTOMATIC, E2E_APPL_DATA) State,
    P2CONST(E2E_PhConfigType, AUTOMATIC, E2E_APPL_DATA) Config
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
* Function Name: E2E_PhCheck_ChkParam
*
* Explanation: Parameter verification of data check. (Synchronous)
*
* param:  ConfigPtr: Pointer to static configuration.
*         StatePtr: Pointer to data communication state.
*         DataPtr: Pointer to data to be transmitted.
*
* retval: Std_ReturnType
********************************************************************************
*/
static FUNC(Std_ReturnType, E2E_CODE) E2E_PhCheck_ChkParam
(
    P2CONST(E2E_PhConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr,
    P2VAR(E2E_PhCheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
    P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr
)
{
    Std_ReturnType rtrnValu;

    if( (NULL_PTR == ConfigPtr) || (NULL_PTR == StatePtr) || (NULL_PTR == DataPtr) )
    {
        /* At least one pointer parameter is a NULL pointer. */
        rtrnValu = E2E_E_INPUTERR_NULL;
    }
    else
    {
        /* All parameter is ok. */
        rtrnValu = E2E_E_OK;
    }

    return rtrnValu;
}

/*
********************************************************************************
* Function Name: E2E_PhProtect_ChkParam
*
* Explanation: Parameter verification of data protection. (Synchronous)
*
* param:  ConfigPtr: Pointer to static configuration.
*         StatePtr: Pointer to data communication state.
*         DataPtr: Pointer to data to be transmitted.
*
* retval: Std_ReturnType
********************************************************************************
*/
static FUNC(Std_ReturnType, E2E_CODE) E2E_PhProtect_ChkParam
(
    P2CONST(E2E_PhConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr,
    P2VAR(E2E_PhProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
    P2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr
)
{
    Std_ReturnType rtrnValu;

    if ((NULL_PTR == ConfigPtr) || (NULL_PTR == StatePtr) || (NULL_PTR == DataPtr))
    {
        /* At least one pointer parameter is a NULL pointer. */
        rtrnValu = E2E_E_INPUTERR_NULL;
    }
    else
    {
        if ( StatePtr->Counter > E2E_PHPROTECT_COUNTERMAX )
        {
            /* Counter is out of range (0-3). */
            rtrnValu = E2E_E_INPUTERR_WRONG;
        }
        else
        {
            /* All parameter is ok. */
            rtrnValu = E2E_E_OK;
        }
    }

    return rtrnValu;
}

/*
********************************************************************************
* Function Name: E2E_PhCalculate_DataIDSum
*
* Explanation: Calculate the sum value of dataID. (Synchronous)
*
* param: ConfigPtr: Pointer to static configuration.
*
* retval: dataIDSum
********************************************************************************
*/
static FUNC(uint8, E2E_CODE) E2E_PhCalculate_DataIDSum
(
    P2CONST(E2E_PhConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr
)
{
    uint8 acByteIndex = E2E_INDEX_0;
	uint8 dataIDSum = E2E_INIT_0;
    uint32 alIDmesg = ConfigPtr->DataID;

    if( E2E_PH_EXTENDEDFRAME == ConfigPtr->FrameType )
	{
	    alIDmesg |= E2E_PH_EXTENDED_OR;
	    for( acByteIndex = E2E_INIT_0; acByteIndex < E2E_PH_DATAID_8_NIBBYTES ; acByteIndex++ )
	    {
	        dataIDSum += (uint8)((alIDmesg >> (E2E_4BIT * acByteIndex)) & E2E_PH_LOWNIBBLE);
	    }
	}
	else if( E2E_PH_STANDARDFRAME == ConfigPtr->FrameType )
	{
	    alIDmesg |= E2E_PH_STANDARD_OR;
	    for( acByteIndex = E2E_INIT_0; acByteIndex < E2E_PH_DATAID_3_NIBBYTES; acByteIndex++ )
	    {
	        dataIDSum += (uint8)((alIDmesg >> (E2E_4BIT * acByteIndex)) & E2E_PH_LOWNIBBLE);
	    }
	}
	else
	{
	/* Do nothing. */
	}

    return (dataIDSum);
}

/*
********************************************************************************
* Function Name: E2E_PhCheck_ChkDeltaCounter
*
* Explanation: Verify the Deltacounter.
*
* param:  DeltaCounter: The difference between this frame message counter and
*                       last frame message counter .
*         ReceivedCounter: Counter value of this frame message.
*         State: Pointer to data communication state.
*         Config: Pointer to static configuration.
*
* retval: void
********************************************************************************
*/
static FUNC(void, E2E_CODE) E2E_PhCheck_ChkDeltaCounter
(
    uint8 DeltaCounter,
    uint8 ReceivedCounter,
    P2VAR(E2E_PhCheckStateType, AUTOMATIC, E2E_APPL_DATA) State,
    P2CONST(E2E_PhConfigType, AUTOMATIC, E2E_APPL_DATA) Config
)
{
    if( E2E_JUDGE_0 == DeltaCounter )
    {
        if( State->NoNewOrRepeatedDataCounter < E2E_PHPROTECT_COUNTERMAX )
        {
            /* Increment NoNewOrRepeatedDataCounter by 1. */
            State->NoNewOrRepeatedDataCounter++;
        }
        /* Set status to E2E_PhSTATUS_REPEATED. */
        State->Status = E2E_PHSTATUS_REPEATED;
    }
    else if( E2E_JUDGE_1 == DeltaCounter )
    {
        /* Set MaxDeltaCounter to the configured MaxDeltaCounterInit. */
        State->MaxDeltaCounter = Config->MaxDeltaCounterInit;
        /* Record counter of current message. */
        State->LastValidCounter = ReceivedCounter;
        State->LostData = E2E_INIT_0;
        /* Is NoNewOrRepeatedDataCounter is within the allowed range of configuration. */
        if( State->NoNewOrRepeatedDataCounter <= Config->MaxNoNewOrRepeatedData )
        {
            State->NoNewOrRepeatedDataCounter = E2E_INIT_0;
            /* SyncCounter is greater than zero, continually check the SyncCounter. */
            if( State->SyncCounter > E2E_JUDGE_0 )
            {
                /* SyncCounter decrease by one. */
                State->SyncCounter--;
                State->Status = E2E_PHSTATUS_SYNC;
            }
            /* Check SyncCounter is completely, no Data has been
               lost since the last correct data reception. */
            else
            {
                State->Status = E2E_PHSTATUS_OK;
            }
        }
        /* NoNewOrRepeatedDataCounter is not Config limit. */
        else
        {
            State->NoNewOrRepeatedDataCounter = E2E_INIT_0;
            State->SyncCounter = Config->SyncCounterInit;
            State->Status = E2E_PHSTATUS_SYNC;
        }
    }
    /* Lose Multiple Data. */
    else if( DeltaCounter < State->MaxDeltaCounter )
    {
        State->MaxDeltaCounter = Config->MaxDeltaCounterInit;
        State->LastValidCounter = ReceivedCounter;
        State->LostData = DeltaCounter - E2E_COUNTER_1;
        /* Is NoNewOrRepeatedDataCounter acceptable in config limit. */
        if( State->NoNewOrRepeatedDataCounter <= Config->MaxNoNewOrRepeatedData )
        {
            State->NoNewOrRepeatedDataCounter = E2E_INIT_0;
            /* SyncCounter value greater than zero, continuity check for the
               counter is not finalized yet, DeltaCounter in congfig limit. */
            if( State->SyncCounter > E2E_JUDGE_0 )
            {
                /* Continuity check for the counter decrease one ,DeltaCounter
                   in congfig limit. */
                State->SyncCounter--;
                State->Status = E2E_PHSTATUS_SYNC;
            }
            /* SyncCounter value greater than zero, continuity check for the
               counter is finalized,DeltaCounter in congfig limit. */
            else
            {
                State->Status = E2E_PHSTATUS_OKSOMELOST;
            }
        }
        /* NoNewOrRepeatedDataCounter is out of range of configuration. */
        else
        {
            State->NoNewOrRepeatedDataCounter = E2E_INIT_0;
            State->SyncCounter = Config->SyncCounterInit;
            State->Status = E2E_PHSTATUS_SYNC;
        }
    }
    /* DeltaCounter is out of range of configuration, wrong sequence status. */
    else
    {
        State->NoNewOrRepeatedDataCounter = E2E_INIT_0;
        State->SyncCounter = Config->SyncCounterInit;
        /* In E2E_PhPROTECT_COUNTERMAX limit have opportunities for recovery. */
        if( State->SyncCounter > E2E_JUDGE_0 )
        {
            State->MaxDeltaCounter = Config->MaxDeltaCounterInit;
            State->LastValidCounter = ReceivedCounter;
        }
        State->Status = E2E_PHSTATUS_WRONGSEQUENCE;
    }
}

/*
********************************************************************************
* Function Name: E2E_PhProtect
*
* Explanation: Protect the data to be transmitted by using the E2E_PhProtect.
*              This includes checksum calculation, handling of counter and Data ID.
*              (Synchronous)
*
* param:  ConfigPtr: Pointer to static configuration.
*         StatePtr: Pointer to data communication state.
*         DataPtr: Pointer to data to be transmitted.
*
* retval: Std_ReturnType
********************************************************************************
*/
FUNC(Std_ReturnType, E2E_CODE) E2E_PhProtect
(
    P2CONST(E2E_PhConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr,
    P2VAR(E2E_PhProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
    P2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr
)
{
    Std_ReturnType rtrnValu;
    uint8 checksumValu = E2E_INIT_0;
    uint8 dataIDSum;
    uint16 dataLen = ConfigPtr->DataLength;

    /* Check all parameters. */
    rtrnValu = E2E_PhProtect_ChkParam(ConfigPtr, StatePtr, DataPtr);
    /* All parameters are valid. */
    if( E2E_E_OK == rtrnValu )
    {
        /* Increment the counter modulo 4(0-3). */
        StatePtr->Counter = (StatePtr->Counter + E2E_INIT_1) % E2E_PHPROTECT_COUNTERMOD;
        /* Set counter. */
        DataPtr[ConfigPtr->CounterOffset / E2E_8BIT]
               = (uint8)((DataPtr[ConfigPtr->CounterOffset / E2E_8BIT] & E2E_PH_RESERVEBIT)
                         | ((uint8)(StatePtr->Counter << E2E_4BIT) & E2E_PH_HIGH2BITS_NIBBLE));
        dataIDSum = E2E_PhCalculate_DataIDSum(ConfigPtr);
        /* Calculate checksum over Data. */
        checksumValu = Crc_CalculateAccumulation(dataLen, dataIDSum, DataPtr);
        /* Copy checksum to the Data at configured location. */
        DataPtr[ConfigPtr->ChecksumOffset / E2E_8BIT]
               = (uint8)(DataPtr[ConfigPtr->ChecksumOffset / E2E_8BIT] | (checksumValu & E2E_PH_LOWNIBBLE));
    }

    return rtrnValu;
}

/*
********************************************************************************
* Function Name: E2E_PhProtectInit
*
* Explanation: Initializes the protection state.(Synchronous)
*
* param:  StatePtr: Pointer to data communication state.
*
* retval: Std_ReturnType
********************************************************************************
*/
FUNC(Std_ReturnType, E2E_CODE) E2E_PhProtectInit
(
    P2VAR(E2E_PhProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr
)
{
    Std_ReturnType rtrnValu = E2E_E_INPUTERR_NULL;
    /* Check whether the input parameter has a null pointer. */
    if( NULL_PTR != StatePtr )
    {
        /* Initializes the counter. */
        StatePtr->Counter = E2E_INIT_0;
        rtrnValu = E2E_E_OK;
    }

    return rtrnValu;
}

/*
********************************************************************************
* Function Name: E2E_PhCheck
*
* Explanation: Checks the Data received by using the E2E_PhCheck. This includes
*              checksum calculation,handling of Counter and Data ID.(Synchronous)
*
* param:  Config: Pointer to static configuration.
*         Data: Poiter to received data.
*         State: Pointer to data communication state.
*
* retval: Std_ReturnType
********************************************************************************
*/
FUNC(Std_ReturnType, E2E_CODE) E2E_PhCheck
(
    P2CONST(E2E_PhConfigType, AUTOMATIC, E2E_APPL_DATA) Config,
    P2VAR(E2E_PhCheckStateType, AUTOMATIC, E2E_APPL_DATA) State,
    P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) Data
)
{
    Std_ReturnType rtrnValu;
    uint8 receivedCounter = E2E_INIT_0;
    uint8 receivedChecksum= E2E_INIT_0;
    uint8 calculatedChecksum = E2E_INIT_0;
    uint8 deltaCounter = E2E_INIT_0;
    uint8 dataIDSum = E2E_INIT_0;
    uint16 dataLen = Config->DataLength;

    /* Check all parameters. */
    rtrnValu = E2E_PhCheck_ChkParam(Config, State, Data);
    if( E2E_E_OK == rtrnValu )
    {
        if( State->MaxDeltaCounter < E2E_PHPROTECT_COUNTERMAX )
        {
            State->MaxDeltaCounter++;
        }
        /* If any new data is available to be checked. */
        if( TRUE == State->NewDataAvailable )
        {
            receivedCounter = (Data[Config->CounterOffset / E2E_8BIT] >> E2E_4BIT)
                              & E2E_PH_LOW2BITS_NIBBLE;
            /* Read Checksum from Data. */
            receivedChecksum = Data[Config->ChecksumOffset / E2E_8BIT] & E2E_LOW_NIBBLE;
            dataIDSum = E2E_PhCalculate_DataIDSum(Config);
            /* Calculate Checksum in the same way as the Sender did. */
            calculatedChecksum = Crc_CalculateAccumulation(dataLen, dataIDSum, Data);
            /* ReceivedChecksum is ok? */
            if( receivedChecksum == calculatedChecksum )
            {
                /* Check if any correct data has already be received. */
                if( (boolean)TRUE == State->WaitForFirstData )
                {
                    /* This is the first message with correct Checksum, WaitForFirstData
                       is therefore set to false. Counter is not checked as it
                       cannot be done yet. */
                    State->WaitForFirstData = FALSE;
                    State->MaxDeltaCounter = Config->MaxDeltaCounterInit;
                    State->LastValidCounter = receivedCounter;
                    State->Status = E2E_PHSTATUS_INITIAL;
                }
                else
                {
                    /* Compute the deltaCounter, taking into account the overflow. */
                    if( receivedCounter >= State->LastValidCounter )
                    {
                        deltaCounter = receivedCounter - State->LastValidCounter;
                    }
                    else
                    {
                        deltaCounter = E2E_PHPROTECT_COUNTERMOD
                                       + receivedCounter
                                       - State->LastValidCounter;
                    }
                    /* Verify the counter. */
                    E2E_PhCheck_ChkDeltaCounter(deltaCounter, receivedCounter,
                                                State, Config);
                }
            }
            /* ReceivedChecksum and CalculatedChecksum are diffrent. */
            else
            {
                State->Status = E2E_PHSTATUS_WRONGCHECKSUM;
            }
        }
        else
        {
            /* NoNewOrRepeatedDataCounter is increase. */
            if( State->NoNewOrRepeatedDataCounter < E2E_PHPROTECT_COUNTERMAX )
            {
                State->NoNewOrRepeatedDataCounter++;
            }
            State->Status = E2E_PHSTATUS_NONEWDATA;
        }
    }

    return (rtrnValu);
}

/*
********************************************************************************
* Function Name: E2E_PhCheckInit
*
* Explanation: Initializes the check state.(Synchronous)
*
* param: StatePtr: Pointer to data communication state.
*
* retval: Std_ReturnType
********************************************************************************
*/
FUNC(Std_ReturnType, E2E_CODE) E2E_PhCheckInit
(
    P2VAR(E2E_PhCheckStateType, AUTOMATIC, E2E_APPL_DATA) State
)
{
    Std_ReturnType rtrnValu = E2E_E_INPUTERR_NULL;

    /* Check whether the input parameter is a null pointer. */
    if( NULL_PTR != State )
    {
        State->LastValidCounter = E2E_INIT_0;
        State->MaxDeltaCounter = E2E_INIT_0;
        State->WaitForFirstData = FALSE;
        State->NewDataAvailable = TRUE;
        State->LostData = E2E_INIT_0;
        State->Status = E2E_PHSTATUS_NONEWDATA;
        State->SyncCounter = E2E_INIT_0;
        State->NoNewOrRepeatedDataCounter = E2E_INIT_0;
        rtrnValu = E2E_E_OK;
    }

    return rtrnValu;
}

/*
********************************************************************************
* Function Name: E2E_PhMapStatusToSM
*
* Explanation: The function maps the check status of E2E_PhCheck to a generic check status,
*              which can be used by E2E state machine check function. (Synchronous)
*
* param:  CheckReturn: Return value of the E2E_PhCheck function.
*         Status: Status determined by E2E_PhCheck function.
*         profileBehavior: FALSE: check has the legacy behavior, before R4.2.
*                          TRUE: after R4.2.(include R4.2)
*
* retval: E2E_PCheckStatusType
********************************************************************************
*/
FUNC(E2E_PCheckStatusType, E2E_CODE) E2E_PhMapStatusToSM
(
    Std_ReturnType CheckReturn,
    E2E_PhCheckStatusType Status,
    boolean profileBehavior
)
{
    E2E_PCheckStatusType rtrnValu = E2E_P_ERROR;
    E2E_PCheckStatusType Status_Sync = E2E_P_ERROR;
    E2E_PCheckStatusType Status_Initial = E2E_P_ERROR;

    if( E2E_E_OK == CheckReturn )
    {
        /* Check whether the profileBehavior is before or after the R4.2. */
        /* After R4.2.(Include R4.2) */
        if( TRUE == profileBehavior )
        {
            Status_Sync = E2E_P_OK;
            Status_Initial = E2E_P_WRONGSEQUENCE;
        }
        /* Before R4.2. */
        else
        {
            Status_Sync = E2E_P_WRONGSEQUENCE;
            Status_Initial = E2E_P_OK;
        }
        switch ( Status )
        {
            case E2E_PHSTATUS_OK:
                /* The checks of the Data in this cycle were successful */
                rtrnValu = E2E_P_OK;
                break;
            case E2E_PHSTATUS_OKSOMELOST:
                /* The checks of the Data in this cycle were successful */
                rtrnValu = E2E_P_OK;
                break;
            case E2E_PHSTATUS_INITIAL:
                /* Return depending on profileBehavior */
                rtrnValu = Status_Initial;
                break;
            case E2E_PHSTATUS_WRONGCHECKSUM:
                /* Error not related to counters occurred or the return of the
                   check function was not OK. */
                rtrnValu = E2E_P_ERROR;
                break;
            case E2E_PHSTATUS_REPEATED:
                /* Data has a repeated counter */
                rtrnValu = E2E_P_REPEATED;
                break;
            case E2E_PHSTATUS_NONEWDATA:
                /* No new data is available */
                rtrnValu = E2E_P_NONEWDATA;
                break;
            case E2E_PHSTATUS_WRONGSEQUENCE:
                /* The checks of the Data in this cycle were successful, with
                   the exception of counter jump, which changed more than the
                   allowed delta. */
                rtrnValu = E2E_P_WRONGSEQUENCE;
                break;
            case E2E_PHSTATUS_SYNC:
                /* Return depending on profileBehavior */
                rtrnValu = Status_Sync;
                break;
            default:
                break;
        }
    }

    return rtrnValu;
}

#define E2E_STOP_SEC_CODE
#include "E2E_MemMap.h"
