/*
********************************************************************************
*
* File name: E2E_PHail.c
*
* Copyright 2022-2024 Neusoft Reach Corporation.All rights reserved.
*
********************************************************************************
*
* History
*-------------------------------------------------------------------------------
********************************************************************************
********************************************************************************
* Version: 1.0
* Author/Date: XieYN/2022.06.29
* Change: New created.
* Cause: New
********************************************************************************
* Version: 1.1
* Author/Date: XieYN/2022.09.26
* Change: Modify E2E_Counter_1 to E2E_COUNTER_1.
* Cause: Bugfix
********************************************************************************
* Version: 1.2
* Author/Date: XieYN/2022.11.10
* Change: Modify polyspace problems.
* Cause: Optimization
********************************************************************************
* Version: 1.3
* Author/Date: LiDY/2023.08.03
* Change: Compilation warning optimization
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
#include "E2E_PHail.h"

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

static FUNC(void, E2E_CODE) E2E_PHailCheck_ChkDeltaCounter
(
    uint8 DeltaCounter,
    uint8 ReceivedCounter,
    P2VAR(E2E_PHailCheckStateType, AUTOMATIC, E2E_APPL_DATA) State,
    P2CONST(E2E_PHailConfigType, AUTOMATIC, E2E_APPL_DATA) Config
);
static FUNC(uint8, E2E_CODE) E2E_PHailProtect_ChkParam
(
    P2CONST(E2E_PHailConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr,
    P2CONST(E2E_PHailProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
    P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr
);
static FUNC(uint8, E2E_CODE) E2E_PHailCheck_ChkParam
(
    P2CONST(E2E_PHailConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr,
    P2CONST(E2E_PHailCheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
    P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr
);
static FUNC(uint8, E2E_CODE) E2E_PHail_CrcCalcule
(
    P2CONST(E2E_PHailConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr,
    uint8 Counter,
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
* Function Name: E2E_PHailCheck_ChkDeltaCounter
*
* Explanation: verify the Deltacounter.
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
/* [SWS_E2E_00076] */
static FUNC(void, E2E_CODE) E2E_PHailCheck_ChkDeltaCounter
(
    uint8 DeltaCounter,
    uint8 ReceivedCounter,
    P2VAR(E2E_PHailCheckStateType, AUTOMATIC, E2E_APPL_DATA) State,
    P2CONST(E2E_PHailConfigType, AUTOMATIC, E2E_APPL_DATA) Config
)
{
    if( E2E_JUDGE_0 == DeltaCounter )
    {
        if( State->NoNewOrRepeatedDataCounter < E2E_PHAILPROTECT_COUNTERMAX )
        {
            /* increment NoNewOrRepeatedDataCounter by 1. */
            State->NoNewOrRepeatedDataCounter++;
        }
        /* set status to E2E_PHAILSTATUS_REPEATED. */
        State->Status = E2E_PHAILSTATUS_REPEATED;
    }
    else if( E2E_JUDGE_1 == DeltaCounter )
    {
        /* set MaxDeltaCounter to MaxDeltaCounterInit of config. */
        State->MaxDeltaCounter = Config->MaxDeltaCounterInit;
        /* record counter of current message. */
        State->LastValidCounter = ReceivedCounter;
        State->LostData = E2E_INIT_0;

        /* Is NoNewOrRepeatedDataCounter acceptable in config limit. */
        if( State->NoNewOrRepeatedDataCounter
            <= Config->MaxNoNewOrRepeatedData )
        {
            State->NoNewOrRepeatedDataCounter = E2E_INIT_0;

            /* SyncCounter value greater than zero,continuity check
               for the counter is not finalized yet,DeltaCounter is one. */
            if( State->SyncCounter > E2E_JUDGE_0 )
            {
                /* continuity check for the counter decrease one ,
                   DeltaCounter is one. */
                State->SyncCounter--;
                State->Status = E2E_PHAILSTATUS_SYNC;
            }
            /* continuity check for the counter is finalized,
               no Data has been lost since the last correct data reception. */
            else
            {
                State->Status = E2E_PHAILSTATUS_OK;
            }
        }
        else  /* NoNewOrRepeatedDataCounter is not Config limit. */
        {
            State->NoNewOrRepeatedDataCounter = E2E_INIT_0;
            State->SyncCounter = Config->SyncCounerInit;
            State->Status = E2E_PHAILSTATUS_SYNC;
        }
    }
    /* Lose Multiple Data. */
    else if( DeltaCounter < State->MaxDeltaCounter )
    {
        State->MaxDeltaCounter = Config->MaxDeltaCounterInit;
        State->LastValidCounter = ReceivedCounter;
        State->LostData = DeltaCounter - E2E_COUNTER_1;

        /* Is NoNewOrRepeatedDataCounter acceptable in config limit. */
        if( State->NoNewOrRepeatedDataCounter
            <= Config->MaxNoNewOrRepeatedData )
        {
            State->NoNewOrRepeatedDataCounter = E2E_INIT_0;

            /* SyncCounter value greater than zero,continuity check for the
               counter is not finalized yet ,DeltaCounter in congfig limit. */
            if( State->SyncCounter > E2E_JUDGE_0 )
            {
                /* continuity check for the counter decrease one ,
                   DeltaCounter in congfig limit. */
                State->SyncCounter--;
                State->Status = E2E_PHAILSTATUS_SYNC;
            }
            /* SyncCounter value greater than zero,continuity check for the
               counter is finalized,DeltaCounter in congfig limit. */
            else
            {
                State->Status = E2E_PHAILSTATUS_OKSOMELOST;
            }
        }
        /* NoNewOrRepeatedDataCounter is not Config limit. */
        else
        {
            State->NoNewOrRepeatedDataCounter = E2E_INIT_0;
            State->SyncCounter = Config->SyncCounerInit;
            State->Status = E2E_PHAILSTATUS_SYNC;
        }
    }
    /* DeltaCounter greater than config limit,wrong sequence status. */
    else
    {
        State->NoNewOrRepeatedDataCounter = E2E_INIT_0;
        State->SyncCounter = Config->SyncCounerInit;

        /* In E2E_PHAILPROTECT_COUNTERMAX limit have opportunities for recovery. */
        if( State->SyncCounter > E2E_JUDGE_0 )
        {
            State->MaxDeltaCounter = Config->MaxDeltaCounterInit;
            State->LastValidCounter = ReceivedCounter;
        }
        State->Status = E2E_PHAILSTATUS_WRONGSEQUENCE;
    }
}

/*
********************************************************************************
* Function Name: E2E_PHailProtect_ChkParam
*
* Explanation: Protect Check Parameter.(Synchronous)
*
* param: ConfigPtr: Pointer to static configuration.
*        StatePtr: Pointer to port/data communication state.
*        DataPtr: Pointer to Data to be transmitted.
*
* retval: Std_ReturnType
********************************************************************************
*/
static FUNC(uint8, E2E_CODE) E2E_PHailProtect_ChkParam
(
    P2CONST(E2E_PHailConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr,
    P2CONST(E2E_PHailProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
    P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr
)
{
    uint8 rtrnValu = E2E_E_INPUTERR_NULL;

    if( (NULL_PTR == ConfigPtr)
        || (NULL_PTR == StatePtr) || (NULL_PTR == DataPtr) )
    {
        /* At least one pointer parameter is a NULL pointer. */
        rtrnValu = E2E_E_INPUTERR_NULL;
    }
    else
    {
        if( (StatePtr->Counter > E2E_PHAILPROTECT_COUNTERMAX) ||
			(E2E_INIT_0 == StatePtr->Counter) )
        {
            /* Counter is out of range (1-15). */
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
* Function Name: E2E_PHailCheck_ChkParam
*
* Explanation: Check Parameter.(Synchronous)
*
* param: ConfigPtr: Pointer to static configuration.
*        StatePtr: Pointer to port/data communication state.
*        DataPtr: Pointer to Data to be transmitted.
*
* retval: Std_ReturnType
********************************************************************************
*/
static FUNC(uint8, E2E_CODE) E2E_PHailCheck_ChkParam
(
    P2CONST(E2E_PHailConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr,
    P2CONST(E2E_PHailCheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
    P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr
)
{
    uint8 rtrnValu = E2E_E_INPUTERR_NULL;

    if( (NULL_PTR == ConfigPtr)
        || (NULL_PTR == StatePtr) || (NULL_PTR == DataPtr) )
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
* Function Name: E2E_PHail_CrcCalcule
*
* Explanation: Protect&Check Calculate CRC.(Synchronous)
*
* param: ConfigPtr: Pointer to static configuration.
*        Counter: This frame message counter value.
*        DataPtr: Pointer to Data to be transmitted.
*
* retval: CrcValu
********************************************************************************
*/
static FUNC(uint8, E2E_CODE) E2E_PHail_CrcCalcule
(
    P2CONST(E2E_PHailConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr,
    uint8 Counter,
    P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr
)
{
    uint8 crcValu = E2E_INIT_0;
    uint16 crcLength = E2E_INIT_0;

    E2E_DUMMY_STATEMENT(Counter);
    /* Compute CRC over the area before the
       CRC (if CRC is not the first byte). */
    if( ConfigPtr->CRCOffset >= E2E_8BIT )
    {
        crcLength = ConfigPtr->CRCOffset / E2E_8BIT;
        crcValu = Crc_CalculateCRC8 (DataPtr, crcLength, crcValu, TRUE);
    }

    /* Compute CRC over the area after the CRC (if CRC is not the last byte). */
    if( (ConfigPtr->CRCOffset / E2E_8BIT)
          < ((ConfigPtr->DataLength / E2E_8BIT) - E2E_INIT_1) )
    {
        crcLength
          = (ConfigPtr->DataLength / E2E_8BIT)
            - (ConfigPtr->CRCOffset / E2E_8BIT) - E2E_INIT_1;
        crcValu
          = Crc_CalculateCRC8(&DataPtr[(ConfigPtr->CRCOffset / E2E_8BIT) + E2E_INIT_1],
                              crcLength, crcValu, FALSE);
    }

    return crcValu;
}

/*
********************************************************************************
* Function Name: E2E_PHailProtect
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
/* [SWRD-BMU-ECAN-035] */
FUNC(Std_ReturnType, E2E_CODE) E2E_PHailProtect
(
    P2CONST(E2E_PHailConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr,
    P2VAR(E2E_PHailProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
    P2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr
)
{
    Std_ReturnType rtrnValu = E2E_E_INPUTERR_NULL;
    uint8 crcValu = E2E_JUDGE_0;

    /* Check all parameters. */
    rtrnValu = E2E_PHailProtect_ChkParam(ConfigPtr, StatePtr, DataPtr);

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

        /* Calculate CRC over Data. */
        crcValu = E2E_PHail_CrcCalcule(ConfigPtr, StatePtr->Counter, DataPtr);
        /* Copy CRC to the Data at configured location. */
        DataPtr[ConfigPtr->CRCOffset / E2E_8BIT] = crcValu;
        /* increment the counter modulo 15, next value after 15 is 1. */
        StatePtr->Counter
          = (StatePtr->Counter % E2E_PHAILPROTECT_COUNTERMOD) + E2E_INIT_1;
    }

    return rtrnValu;
}

/*
********************************************************************************
* Function Name: E2E_PHailProtectInit
*
* Explanation: Initializes the protection state.(Synchronous)
*
* param: StatePtr: Pointer to port/data communication state.
*
* retval: Std_ReturnType
********************************************************************************
*/
FUNC(Std_ReturnType, E2E_CODE) E2E_PHailProtectInit
(
    P2VAR(E2E_PHailProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr
)
{
    Std_ReturnType rtrnValu = E2E_E_INPUTERR_NULL;

	/* The param is valid. */
    if( StatePtr != NULL_PTR )
    {
        /* Initializes the counter. */
        StatePtr->Counter = E2E_INIT_1;
        rtrnValu = E2E_E_OK;
    }

    return rtrnValu;
}

/*
********************************************************************************
* Function Name: E2E_PHailCheck
*
* Explanation: Checks the Data received using the E2E profile 1. This includes
*              CRC calculation,handling of Counter and Data ID.(Synchronous)
*
* param: Config: Pointer to static configuration
*        Data: Pointer to received data
*        State: Pointer to port/data communication state
*
* retval: Std_ReturnType
********************************************************************************
*/
FUNC(Std_ReturnType, E2E_CODE) E2E_PHailCheck
(
    P2CONST(E2E_PHailConfigType, AUTOMATIC, E2E_APPL_DATA) Config,
    P2VAR(E2E_PHailCheckStateType, AUTOMATIC, E2E_APPL_DATA) State,
    P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) Data
)
{
    Std_ReturnType rtrnValu = E2E_E_INPUTERR_NULL;
    uint8 receivedCounter = E2E_INIT_0;
    uint8 receivedCrc = E2E_INIT_0;
    uint8 calculatedCrc = E2E_INIT_0;
    uint8 deltaCounter = E2E_INIT_0;

    rtrnValu = E2E_PHailCheck_ChkParam(Config, State, Data);
    /* Check all parameters */
    if( E2E_E_OK == rtrnValu )
    {
        /* At every function invocation, the maximum allowed delta
           between previous and current Counter is incremented. */
        if( State->MaxDeltaCounter < E2E_PHAILPROTECT_COUNTERMAX )
        {
            State->MaxDeltaCounter++;
        }
        /* If any NEW data is available to be checked. */
        if( TRUE == State->NewDataAvailable )
        {
            /* Read the Counter from Data, at the configured offset. */
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
            /* ReceivedCounter is out of range. */
            if( E2E_INIT_0 != receivedCounter )
            {
                /* Read CRC from Data. */
                receivedCrc = Data[Config->CRCOffset / E2E_8BIT];

                /* Calculate CRC in the same way as the Sender did. */
                calculatedCrc
                  = E2E_PHail_CrcCalcule(Config, receivedCounter, Data);

                /* ReceivedCRC is ok? */
                if( receivedCrc == calculatedCrc )
                {
                    /* Check if any correct data has already be received. */
                    /* This is the first message with correct CRC,
                       WaitForFirstData is therefore set to false.
                       Counter is not checked as it cannot be done yet. */
                    if( TRUE == State->WaitForFirstData )
                    {
                        State->WaitForFirstData= FALSE;
                        State->MaxDeltaCounter
                          = Config->MaxDeltaCounterInit;
                        State->LastValidCounter = receivedCounter;
                        State->Status = E2E_PHAILSTATUS_INITIAL;
                    }
                    /* Compute the delta, taking into account the overflow. */
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
                              = E2E_PHAILPROTECT_COUNTERMOD
                              + receivedCounter - State->LastValidCounter;
                        }
                        /* The previous and the current data have correct
                           CRC, verify the counter. */
                        E2E_PHailCheck_ChkDeltaCounter(deltaCounter,
                                                     receivedCounter,
                                                     State,
                                                     Config);
                    }
                }
                else /* ReceivedCRC, CalculatedCRC are diffrent. */
                {
                    State->Status = E2E_PHAILSTATUS_WRONGCRC;
                }
            }
            else /* ReceivedCounter is out of range. */
            {
                rtrnValu = E2E_E_INPUTERR_WRONG;
            }
        }
        else
        {
            /* NoNewOrRepeatedDataCounter is increase. */
            if( State->NoNewOrRepeatedDataCounter < E2E_PHAILPROTECT_COUNTERMAX )
            {
                State->NoNewOrRepeatedDataCounter++;
            }
            State->Status = E2E_PHAILSTATUS_NONEWDATA;
        }
    }

    return rtrnValu;
}

/*
********************************************************************************
* Function Name: E2E_PHailCheckInit
*
* Explanation: Initializes the check state.(Synchronous)
*
* param: StatePtr: Pointer to port/data communication state.
*
* retval: Std_ReturnType
********************************************************************************
*/
FUNC(Std_ReturnType, E2E_CODE) E2E_PHailCheckInit
(
    P2VAR(E2E_PHailCheckStateType, AUTOMATIC, E2E_APPL_DATA) State
)
{
    Std_ReturnType rtrnValu = E2E_E_INPUTERR_NULL;

    /* The param is valid. */
    if( State != NULL_PTR )
    {
        State->LastValidCounter = E2E_INIT_0;
        State->MaxDeltaCounter = E2E_INIT_0;
        State->WaitForFirstData = FALSE;
        State->NewDataAvailable = TRUE;
        State->LostData = E2E_INIT_0;
        State->Status = E2E_PHAILSTATUS_NONEWDATA;
        State->SyncCounter = E2E_INIT_0;
        State->NoNewOrRepeatedDataCounter = E2E_INIT_0;
        rtrnValu = E2E_E_OK;
    }

    return rtrnValu;
}

/*
********************************************************************************
* Function Name: E2E_PHailMapStatusToSM
*
* Explanation: The function maps the check status of Profile 1 to a generic
*              check status,which can be used by E2E state machine check
*              function. (Synchronous)
*
* param: CheckReturn: Return value of the E2E_PHailCheck function.
*        Status: Status determined by E2E_PHailCheck function.
*        profileBehavior: FALSE is check has the legacy behavior before R4.2,
*                         TRUE is check behaves like new P4/P5/P6 profiles
*                         introduced  in R4.2.
*
* retval: E2E_PCheckStatusType
********************************************************************************
*/
FUNC(E2E_PCheckStatusType, E2E_CODE) E2E_PHailMapStatusToSM
(
    Std_ReturnType CheckReturn,
    E2E_PHailCheckStatusType Status,
    boolean profileBehavior
)
{
    E2E_PCheckStatusType rtrnValu = E2E_P_ERROR;
    E2E_PCheckStatusType statusSync = E2E_P_ERROR;
    E2E_PCheckStatusType statusInitial = E2E_P_ERROR;

    if( E2E_E_OK == CheckReturn )
    {
        /* Check behaves introduced in R4.2. */
        if( TRUE == profileBehavior )
        {
            statusSync = E2E_P_OK;
            statusInitial = E2E_P_WRONGSEQUENCE;
        }
        /* Check has the legacy behavior, before R4.2. */
        else
        {
            statusSync = E2E_P_WRONGSEQUENCE;
            statusInitial = E2E_P_OK;
        }
        switch( Status )
        {
            case E2E_PHAILSTATUS_OK:
                /* The checks of the Data in this cycle were successful. */
                rtrnValu = E2E_P_OK;
                break;
            case E2E_PHAILSTATUS_OKSOMELOST:
                /* The checks of the Data in this cycle were successful. */
                rtrnValu = E2E_P_OK;
                break;
            case E2E_PHAILSTATUS_INITIAL:
                /* Return depending on profileBehavior. */
                rtrnValu = statusInitial;
                break;
            case E2E_PHAILSTATUS_WRONGCRC:
                /* Error not related to counters occurred or the
                   return of the check function was not OK. */
                rtrnValu = E2E_P_ERROR;
                break;
            case E2E_PHAILSTATUS_REPEATED:
                /* Data has a repeated counter. */
                rtrnValu = E2E_P_REPEATED;
                break;
            case E2E_PHAILSTATUS_NONEWDATA:
                /* No new data is available. */
                rtrnValu = E2E_P_NONEWDATA;
                break;
            case E2E_PHAILSTATUS_WRONGSEQUENCE:
                /* The checks of the Data in this cycle were successful,
                   counter jumpchanged more than the allowed delta. */
                rtrnValu = E2E_P_WRONGSEQUENCE;
                break;
            case E2E_PHAILSTATUS_SYNC:
                /* return depending on profileBehavior. */
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
