/*
********************************************************************************
*
* File name: E2E_PG.c
*
* Copyright 2022-2024 Neusoft Reach Corporation.All rights reserved.
*
********************************************************************************
*
* History
*-------------------------------------------------------------------------------
********************************************************************************
* Version: 3.0
* Author/Date: XieYN/2022.01.12
* Change: New created
* Cause: New
********************************************************************************
* Version: 3.1
* Author/Date: LiDaY/2024.03.18
* Change: Modifying the label of the input parameter Ptrclass for E2E function
*         and addressing some code inconsistencies.
* Cause: Optimization
********************************************************************************
* Version: 3.2
* Author/Date: LiDaY/2024.04.25
* Change: Add a memory-map label to function and variable declarations.
* Cause: Bugfix
********************************************************************************
* Version: 3.3
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
#include "E2E_PG.h"

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

static FUNC(void, E2E_CODE) E2E_PGCheck_ChkDeltaCounter
(
    uint8 DeltaCounter,
    uint8 ReceivedCounter,
    P2VAR(E2E_PGCheckStateType, AUTOMATIC, E2E_APPL_DATA) State,
    P2CONST(E2E_PGConfigType, AUTOMATIC, E2E_APPL_DATA) Config
);
static FUNC(uint8, E2E_CODE) E2E_PGProtect_ChkParam
(
    P2CONST(E2E_PGConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr,
    P2CONST(E2E_PGProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
    P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr
);
static FUNC(uint8, E2E_CODE) E2E_PGCheck_ChkParam
(
    P2CONST(E2E_PGConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr,
    P2CONST(E2E_PGCheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
    P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr
);
static FUNC(uint8, E2E_CODE) E2E_PG_CrcCalcule
(
    P2CONST(E2E_PGConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr,
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
* Function Name: E2E_PGCheck_ChkDeltaCounter
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
static FUNC(void, E2E_CODE) E2E_PGCheck_ChkDeltaCounter
(
    uint8 DeltaCounter,
    uint8 ReceivedCounter,
    P2VAR(E2E_PGCheckStateType, AUTOMATIC, E2E_APPL_DATA) State,
    P2CONST(E2E_PGConfigType, AUTOMATIC, E2E_APPL_DATA) Config
)
{
    if( E2E_JUDGE_0 == DeltaCounter ) /* [SWS_E2E_00076] */
    {
        /* [SWS_E2E_00196] */
        if( State->NoNewOrRepeatedDataCounter < E2E_PGPROTECT_COUNTERMAX )
        {
            /* increment NoNewOrRepeatedDataCounter by 1. */
            State->NoNewOrRepeatedDataCounter++; /* [SWS_E2E_00196] */
        }
        /* set status to E2E_PGSTATUS_REPEATED. */
        State->Status = E2E_PGSTATUS_REPEATED; /* [SWS_E2E_00196] */
    }
    else if( E2E_JUDGE_1 == DeltaCounter ) /* [SWS_E2E_00076] */
    {
        /* [SWS_E2E_00196] */
        /* set MaxDeltaCounter to MaxDeltaCounterInit of config. */
        State->MaxDeltaCounter = Config->MaxDeltaCounterInit;
        /* record counter of current message. */
        State->LastValidCounter = ReceivedCounter; /* [SWS_E2E_00196] */
        State->LostData = E2E_INIT_0; /* [SWS_E2E_00196] */
        /* Is NoNewOrRepeatedDataCounter acceptable in config limit. */
        if( State->NoNewOrRepeatedDataCounter <= Config->MaxNoNewOrRepeatedData )
        {
            /* [SWS_E2E_00196] */
            State->NoNewOrRepeatedDataCounter = E2E_INIT_0;
            /* SyncCounter value greater than zero,continuity check
               for the counter is not finalized yet,DeltaCounter is one. */
            if( State->SyncCounter > E2E_JUDGE_0 )
            {
                /* continuity check for the counter decrease one ,
                   DeltaCounter is one. */
                State->SyncCounter--;  /* [SWS_E2E_00196] */
                State->Status = E2E_PGSTATUS_SYNC; /* [SWS_E2E_00196] */
            }
            /* continuity check for the counter is finalized,
               no Data has been lost since the last correct data reception. */
            else
            {
                State->Status = E2E_PGSTATUS_OK; /* [SWS_E2E_00196] */
            }
        }
        else  /* NoNewOrRepeatedDataCounter is not Config limit. */
        {
            State->NoNewOrRepeatedDataCounter = E2E_INIT_0;
            State->SyncCounter = Config->SyncCounterInit;
            State->Status = E2E_PGSTATUS_SYNC; /* [SWS_E2E_00196] */
        }
    }
    /* Lose Multiple Data. */
    else if( DeltaCounter < State->MaxDeltaCounter ) /* [SWS_E2E_00076] */
    {
        /* [SWS_E2E_00196] */
        State->MaxDeltaCounter = Config->MaxDeltaCounterInit;
        State->LastValidCounter = ReceivedCounter; /* [SWS_E2E_00196] */
        State->LostData = DeltaCounter - E2E_COUNTER_1; /* [SWS_E2E_00196] */
        /* Is NoNewOrRepeatedDataCounter acceptable in config limit. */
        if( State->NoNewOrRepeatedDataCounter <= Config->MaxNoNewOrRepeatedData )
        {
            State->NoNewOrRepeatedDataCounter = E2E_INIT_0; /* [SWS_E2E_00196] */
            /* SyncCounter value greater than zero,continuity check for the
               counter is not finalized yet ,DeltaCounter in congfig limit. */
            if( State->SyncCounter > E2E_JUDGE_0 )
            {
                /* continuity check for the counter decrease one ,
                   DeltaCounter in congfig limit. */
                State->SyncCounter--;
                State->Status = E2E_PGSTATUS_SYNC; /* [SWS_E2E_00196] */
            }
            /* SyncCounter value greater than zero,continuity check for the
               counter is finalized,DeltaCounter in congfig limit. */
            else
            {
                State->Status = E2E_PGSTATUS_OKSOMELOST; /* [SWS_E2E_00196] */
            }
        }
        /* NoNewOrRepeatedDataCounter is not Config limit. */
        else
        {
            /* [SWS_E2E_00196] */
            State->NoNewOrRepeatedDataCounter = E2E_INIT_0;
            State->SyncCounter = Config->SyncCounterInit; /* [SWS_E2E_00196] */
            State->Status = E2E_PGSTATUS_SYNC; /* [SWS_E2E_00196] */
        }
    }
    /* DeltaCounter greater than config limit,wrong sequence status. */
    else /* [SWS_E2E_00076] */
    {
        State->NoNewOrRepeatedDataCounter = E2E_INIT_0; /* [SWS_E2E_00196] */
        State->SyncCounter = Config->SyncCounterInit; /* [SWS_E2E_00196] */
        /* In E2E_PGPROTECT_COUNTERMAX limit have opportunities for recovery. */
        if( State->SyncCounter > E2E_JUDGE_0 )
        {
            /* [SWS_E2E_00196] */
            State->MaxDeltaCounter = Config->MaxDeltaCounterInit;
            State->LastValidCounter = ReceivedCounter; /* [SWS_E2E_00196] */
        }
        State->Status = E2E_PGSTATUS_WRONGSEQUENCE; /* [SWS_E2E_00196] */
    }
}

/*
********************************************************************************
* Function Name: E2E_PGProtect_ChkParam
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
static FUNC(uint8, E2E_CODE) E2E_PGProtect_ChkParam
(
    P2CONST(E2E_PGConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr,
    P2CONST(E2E_PGProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
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
        if( StatePtr->Counter > E2E_PGPROTECT_COUNTERMAX )
        {
            /* Counter is out of range (0-14). */
            rtrnValu = E2E_E_INPUTERR_WRONG;
        }
        else
        {
            rtrnValu = E2E_E_OK;    /* All parameter is ok. */
        }
    }

    return rtrnValu;
}

/*
********************************************************************************
* Function Name: E2E_PGCheck_ChkParam
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
static FUNC(uint8, E2E_CODE) E2E_PGCheck_ChkParam
(
    P2CONST(E2E_PGConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr,
    P2CONST(E2E_PGCheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
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
        rtrnValu = E2E_E_OK;    /* All parameter is ok. */
    }

    return rtrnValu;
}

/*
********************************************************************************
* Function Name: E2E_PG_CrcCalcule
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
/* [SWS_E2E_00190] */
static FUNC(uint8, E2E_CODE) E2E_PG_CrcCalcule
(
    P2CONST(E2E_PGConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr,
    uint8 Counter,
    P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr
)
{
    uint8 dataLength = E2E_INIT_0;
    uint8 crcValu = E2E_INIT_0;
    uint8 evenCounter = Counter % E2E_INIT_2;
    uint8 dataId[E2E_INDEX_2] = {E2E_INIT_0,E2E_INIT_0};
    uint16 crcLength = E2E_INIT_0;

    switch( ConfigPtr->DataIDMode ) /* [SWS_E2E_00082] */
    {
        /* Both two bytes are used. */
        case E2E_PG_DATAID_BOTH :  /* [SWS_E2E_00082] */
            /* [SWS_E2E_00163] */
            dataId[E2E_INDEX_0] = (uint8)(ConfigPtr->DataID);
            /* [SWS_E2E_00163] */
            dataId[E2E_INDEX_1] = (uint8)(ConfigPtr->DataID >> E2E_8BIT);
            /* [SWS_E2E_00163] */
            dataLength = E2E_PG_DATAID_2BYTES;
            break;
        /* Only the low byte is used. */
        case E2E_PG_DATAID_LOW : /* [SWS_E2E_00082] */
            /* [SWS_E2E_00163] */
            dataId[E2E_INDEX_0] = (uint8)(ConfigPtr->DataID);
            /* [SWS_E2E_00163] */
            dataLength = E2E_PG_DATAID_1BYTE;
            break;
        case E2E_PG_DATAID_ALT : /* [SWS_E2E_00082] */
            /* Even counter the low byte is used. */
            if( E2E_JUDGE_0 == evenCounter )
            {
                /* [SWS_E2E_00163] */
                dataId[E2E_INDEX_0] = (uint8)(ConfigPtr->DataID);
                dataLength = E2E_PG_DATAID_1BYTE; /* [SWS_E2E_00163] */
            }
            else /* Odd counter the low byte is used. */
            {
                /* [SWS_E2E_00163] */
                dataId[E2E_INDEX_0] = (uint8)(ConfigPtr->DataID >> E2E_8BIT);
                dataLength = E2E_PG_DATAID_1BYTE; /* [SWS_E2E_00163] */
            }
            break;
        /* Low byte is used, high byte is 0 instead. */
        case E2E_PG_DATAID_NIBBLE : /* [SWS_E2E_00082] */
            /* [SWS_E2E_00163] */
            dataId[E2E_INDEX_0] = (uint8)(ConfigPtr->DataID);
            dataId[E2E_INDEX_1] = E2E_INIT_0; /* [SWS_E2E_00163] */
            dataLength = E2E_PG_DATAID_2BYTES; /* [SWS_E2E_00163] */
            break;
        default:
            break;
    }
    /* [SWS_E2E_00083] */ /* [SWS_E2E_00190] */
    crcValu = Crc_CalculateCRC8(dataId, dataLength, E2E_FULL_BYTE, FALSE);
    /* Compute CRC over the area before the
       CRC (if CRC is not the first byte). */
    if( ConfigPtr->CRCOffset >= E2E_8BIT )
    {
        crcLength = ConfigPtr->CRCOffset / E2E_8BIT;
        /* [SWS_E2E_00190] */
        crcValu = Crc_CalculateCRC8 (DataPtr, crcLength, crcValu, FALSE);
    }
    /* Compute CRC over the area after the CRC (if CRC is not the last byte). */
    if( (ConfigPtr->CRCOffset / E2E_8BIT)
          < ((ConfigPtr->DataLength / E2E_8BIT) - E2E_INIT_1) )
    {
        crcLength = (ConfigPtr->DataLength / E2E_8BIT)
                    - (ConfigPtr->CRCOffset / E2E_8BIT) - E2E_INIT_1;
        crcValu = Crc_CalculateCRC8(&DataPtr[(ConfigPtr->CRCOffset / E2E_8BIT)
			                        + E2E_INIT_1],
                                    crcLength,
                                    crcValu,
                                    FALSE); /* [SWS_E2E_00190] */
    }

    return (crcValu ^ E2E_FULL_BYTE);
}

/*
********************************************************************************
* Function Name: E2E_PGProtect
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
/* [SWS_E2E_00166] */
FUNC(Std_ReturnType, E2E_CODE) E2E_PGProtect
(
    P2VAR(E2E_PGConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr,
    P2VAR(E2E_PGProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
    P2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr
)
{
    Std_ReturnType rtrnValu = E2E_E_INPUTERR_NULL;
    uint8 crcValu = E2E_JUDGE_0;

    /* Check all parameters. */
    rtrnValu = E2E_PGProtect_ChkParam(ConfigPtr, StatePtr, DataPtr);
    if( E2E_E_OK == rtrnValu )  /* All parameters are valid. */
    {
        /* [SWS_E2E_00195] */ /* Counter in low nibble. */
        if( E2E_JUDGE_0 == (ConfigPtr->CounterOffset % E2E_8BIT) )
        {
            /* [SWS_E2E_00195] *//* Counter in high nibble. */
            DataPtr[ConfigPtr->CounterOffset / E2E_8BIT]
              = (uint8)
                ((DataPtr[ConfigPtr->CounterOffset / E2E_8BIT] & E2E_HIGH_NIBBLE)
                | ((StatePtr->Counter) & E2E_LOW_NIBBLE));
        }
        else
        {
            /* [SWS_E2E_00195] */ /* Set counter. */
            DataPtr[ConfigPtr->CounterOffset / E2E_8BIT]
              = (uint8)
                ((DataPtr[ConfigPtr->CounterOffset / E2E_8BIT] & E2E_LOW_NIBBLE)
                | ((uint8)(StatePtr->Counter << E2E_4BIT) & E2E_HIGH_NIBBLE));
        }
        /* [SWS_E2E_00195] */
        /* write DataID nibble in Data (E2E_PG_DATAID_NIBBLE) in Data. */
        if( E2E_PG_DATAID_NIBBLE == ConfigPtr->DataIDMode )
        {
            /* [SWS_E2E_00195] */ /* Current high byte is used, next is low. */
            if( E2E_JUDGE_0 == (ConfigPtr->DataIDNibbleOffset % E2E_8BIT) )
            {
                /* [SWS_E2E_00195] */
                /* Current low byte is used, nest is high. */
                DataPtr[ConfigPtr->DataIDNibbleOffset / E2E_8BIT]
                  = (uint8)
                    ((DataPtr[ConfigPtr->DataIDNibbleOffset / E2E_8BIT]
                    & E2E_HIGH_NIBBLE)
                    | ((uint8)(ConfigPtr->DataID >> E2E_8BIT) & E2E_LOW_NIBBLE));
            }
            else
            {
                /* [SWS_E2E_00195] */
                DataPtr[ConfigPtr->DataIDNibbleOffset / E2E_8BIT]
                  = (uint8)
                    ((DataPtr[ConfigPtr->DataIDNibbleOffset / E2E_8BIT]
                    & E2E_LOW_NIBBLE)
                    | ((uint8)(ConfigPtr->DataID >> E2E_4BIT) & E2E_HIGH_NIBBLE));
            }
        }
        /* [SWS_E2E_00195] */ /* Calculate CRC over Data. */
        crcValu = E2E_PG_CrcCalcule(ConfigPtr, StatePtr->Counter, DataPtr);
        /* [SWS_E2E_00195] */ /* Copy CRC to the Data at configured location. */
        DataPtr[ConfigPtr->CRCOffset / E2E_8BIT] = crcValu;
        /* [SWS_E2E_00075] */ /* [SWS_E2E_00195] */
        /* increment the counter modulo 15, next value after 14 is 0. */
        StatePtr->Counter = (StatePtr->Counter + E2E_INIT_1) % E2E_PGPROTECT_COUNTERMod;
    }

    return rtrnValu;
}

/*
********************************************************************************
* Function Name: E2E_PGProtectInit
*
* Explanation: Initializes the protection state.(Synchronous)
*
* param: StatePtr: Pointer to port/data communication state.
*
* retval: Std_ReturnType
********************************************************************************
*/
/* [SWS_E2E_00385] */
FUNC(Std_ReturnType, E2E_CODE) E2E_PGProtectInit
(
    P2VAR(E2E_PGProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr
)
{
    Std_ReturnType rtrnValu = E2E_E_INPUTERR_NULL; /* [SWS_E2E_00386] */

    if( NULL_PTR != StatePtr )  /* [SWS_E2E_00386] */ /* the param is valid. */
    {
        /* Initializes the counter. */
        StatePtr->Counter = E2E_INIT_0; /* [SWS_E2E_00386] */
        rtrnValu = E2E_E_OK; /* [SWS_E2E_00386] */
    }

    return rtrnValu; /* [SWS_E2E_00386] */
}

/*
********************************************************************************
* Function Name: E2E_PGCheck
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
/* [SWS_E2E_00158] */
FUNC(Std_ReturnType, E2E_CODE) E2E_PGCheck
(
    P2VAR(E2E_PGConfigType, AUTOMATIC, E2E_APPL_DATA) Config,
    P2VAR(E2E_PGCheckStateType, AUTOMATIC, E2E_APPL_DATA) State,
    P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) Data
)
{
    Std_ReturnType rtrnValu = E2E_E_INPUTERR_NULL;
    uint8 receivedCounter = E2E_INIT_0;
    uint8 receivedCrc = E2E_INIT_0;
    uint8 receivedDataIdNibble = E2E_INIT_0;
    uint8 calculatedCrc = E2E_INIT_0;
    uint8 deltaCounter = E2E_INIT_0;

    rtrnValu = E2E_PGCheck_ChkParam(Config, State, Data);
    /* Check all parameters */
    if( E2E_E_OK == rtrnValu )
    {
        /* At every function invocation, the maximum allowed delta
           between previous and current Counter is incremented. */
        if( State->MaxDeltaCounter < E2E_PGPROTECT_COUNTERMAX )
        {
            State->MaxDeltaCounter++;
        }
        /* If any NEW data is available to be checked. */
        if( TRUE == State->NewDataAvailable )
        {
            /* Read the Counter from Data, at the configured offset. */
            if( E2E_JUDGE_0 == (Config->CounterOffset % E2E_8BIT) )
            {
                /* [SWS_E2E_00196] */
                receivedCounter
                  = Data[Config->CounterOffset / E2E_8BIT] & E2E_LOW_NIBBLE;
            }
            else
            {
                /* [SWS_E2E_00196] */
                receivedCounter
                  = (Data[Config->CounterOffset / E2E_8BIT] >> E2E_4BIT)
                    & E2E_LOW_NIBBLE;
            }
            /* [SWS_E2E_00196] */ /* ReceivedCounter is out of range. */
            if( receivedCounter < (E2E_PGPROTECT_COUNTERMAX + E2E_INIT_1) )
            {
                /* [SWS_E2E_00196] */ /* Read CRC from Data. */
                receivedCrc = Data[Config->CRCOffset / E2E_8BIT];

                /* [SWS_E2E_00196] */
                /* Read low nibble of high byte of Data ID from Data. */
                if( E2E_PG_DATAID_NIBBLE == Config->DataIDMode )
                {
                    if( E2E_JUDGE_0 == (Config->DataIDNibbleOffset % E2E_8BIT) )
                    {
                        receivedDataIdNibble
                          = Data[Config->DataIDNibbleOffset / E2E_8BIT]
                            & E2E_LOW_NIBBLE; /* [SWS_E2E_00196] */
                    }
                    else
                    {
                        receivedDataIdNibble
                          = (Data[Config->DataIDNibbleOffset / E2E_8BIT] >> E2E_4BIT)
                            & E2E_LOW_NIBBLE; /* [SWS_E2E_00196] */
                    }
                }
                /* [SWS_E2E_00196] */
                /* Calculate CRC in the same way as the Sender did. */
                calculatedCrc = E2E_PG_CrcCalcule(Config, receivedCounter, Data);
                /* [SWS_E2E_00196] */ /* ReceivedCRC is ok? */
                if( receivedCrc == calculatedCrc )
                {
                    /* Check if received nibble is
                       identical to the one in DataID. */ /* [SWS_E2E_00196] */
                    if( (E2E_PG_DATAID_NIBBLE == Config->DataIDMode) &&
                        (receivedDataIdNibble != (Config->DataID >> E2E_8BIT)) )
                    {
                        /* [SWS_E2E_00196] */
                        State->Status = E2E_PGSTATUS_WRONGCRC;
                    }
                    /* Check if any correct data has already be received. */
                    else
                    {
                        /* This is the first message with correct CRC,
                           WaitForFirstData is therefore set to false.
                           Counter is not checked as it cannot be done yet. */
                        if( TRUE == State->WaitForFirstData )
                        {
                            /* [SWS_E2E_00196] */
                            State->WaitForFirstData= FALSE;
                            /* [SWS_E2E_00196] */
                            State->MaxDeltaCounter
                              = Config->MaxDeltaCounterInit;
                            /* [SWS_E2E_00196] */
                            State->LastValidCounter = receivedCounter;
                            /* [SWS_E2E_00196] */
                            State->Status = E2E_PGSTATUS_INITIAL;
                        }
                        /* Compute the delta, taking into account the overflow. */
                        else
                        {
                            if( receivedCounter >= State->LastValidCounter )
                            {
                                /* [SWS_E2E_00076] */
                                deltaCounter
                                  = receivedCounter - State->LastValidCounter;
                            }
                            else
                            {
                                /* [SWS_E2E_00076] */
                                deltaCounter
                                  = E2E_PGPROTECT_COUNTERMod
                                  + receivedCounter - State->LastValidCounter;
                            }
                            /* The previous and the current data have correct
                               CRC, verify the counter. */
                            E2E_PGCheck_ChkDeltaCounter(deltaCounter,
                                                         receivedCounter,
                                                         State,
                                                         Config);
                        }
                    }
                }
                else /* ReceivedCRC, CalculatedCRC are diffrent. */
                {
                    /* [SWS_E2E_00196] */
                    State->Status = E2E_PGSTATUS_WRONGCRC;
                }
            }
            else    /* ReceivedCounter is out of range. */
            {
                rtrnValu = E2E_E_INPUTERR_WRONG;
            }
        }
        else
        {
            /* NoNewOrRepeatedDataCounter is increase. */
            if( State->NoNewOrRepeatedDataCounter < E2E_PGPROTECT_COUNTERMAX )
            {
                State->NoNewOrRepeatedDataCounter++;
            }
            State->Status = E2E_PGSTATUS_NONEWDATA; /* [SWS_E2E_00196] */
        }
    }

    return rtrnValu;
}

/*
********************************************************************************
* Function Name: E2E_PGCheckInit
*
* Explanation: Initializes the check state.(Synchronous)
*
* param: StatePtr: Pointer to port/data communication state.
*
* retval: Std_ReturnType
********************************************************************************
*/
/* [SWS_E2E_00390] */
FUNC(Std_ReturnType, E2E_CODE) E2E_PGCheckInit
(
    P2VAR(E2E_PGCheckStateType, AUTOMATIC, E2E_APPL_DATA) State
)
{
    Std_ReturnType rtrnValu = E2E_E_INPUTERR_NULL;

    if( NULL_PTR != State ) /* the param is valid. */
    {
        State->LastValidCounter = E2E_INIT_0;           /* [SWS_E2E_00389] */
        State->MaxDeltaCounter = E2E_INIT_0;            /* [SWS_E2E_00389] */
        State->WaitForFirstData = FALSE;                /* [SWS_E2E_00389] */
        State->NewDataAvailable = TRUE;                 /* [SWS_E2E_00389] */
        State->LostData = E2E_INIT_0;                   /* [SWS_E2E_00389] */
        State->Status = E2E_PGSTATUS_NONEWDATA;         /* [SWS_E2E_00389] */
        State->SyncCounter = E2E_INIT_0;                /* [SWS_E2E_00389] */
        State->NoNewOrRepeatedDataCounter = E2E_INIT_0; /* [SWS_E2E_00389] */
        rtrnValu = E2E_E_OK;                            /* [SWS_E2E_00389] */
    }

    return rtrnValu;
}

/*
********************************************************************************
* Function Name: E2E_PGMapStatusToSM
*
* Explanation: The function maps the check status of Profile 1 to a generic
*              check status,which can be used by E2E state machine check
*              function. (Synchronous)
*
* param: CheckReturn: Return value of the E2E_PGCheck function.
*        Status: Status determined by E2E_PGCheck function.
*        profileBehavior: FALSE is check has the legacy behavior before R4.2,
*                         TRUE is check behaves like new P4/P5/P6 profiles
*                         introduced  in R4.2.
*
* retval: E2E_PCheckStatusType
********************************************************************************
*/
/* [SWS_E2E_00382] */
FUNC(E2E_PCheckStatusType, E2E_CODE) E2E_PGMapStatusToSM
(
    Std_ReturnType CheckReturn,
    E2E_PGCheckStatusType Status,
    boolean profileBehavior
)
{
    E2E_PCheckStatusType rtrnValu = E2E_P_ERROR; /* [SWS_E2E_00384] */
    E2E_PCheckStatusType statusSync = E2E_P_ERROR;
    E2E_PCheckStatusType statusInitial = E2E_P_ERROR;

    if( E2E_E_OK == CheckReturn )
    {
        /* check behaves like new P4/P5/P6 profiles introduced in R4.2. */
        if( TRUE == profileBehavior ) /* [SWS_E2E_00383] */
        {
            statusSync = E2E_P_OK;
            statusInitial = E2E_P_WRONGSEQUENCE;
        }
        /* [SWS_E2E_00476] */ /* check has the legacy behavior, before R4.2. */
        else
        {
            statusSync = E2E_P_WRONGSEQUENCE;
            statusInitial = E2E_P_OK;
        }
        switch( Status )
        {
            case E2E_PGSTATUS_OK:
                /* the checks of the Data in this cycle were successful. */
                rtrnValu = E2E_P_OK; /* [SWS_E2E_00383] [SWS_E2E_00476] */
                break;
            case E2E_PGSTATUS_OKSOMELOST:
                /* the checks of the Data in this cycle were successful. */
                rtrnValu = E2E_P_OK; /* [SWS_E2E_00383] [SWS_E2E_00476] */
                break;
            case E2E_PGSTATUS_INITIAL:
                /* return depending on profileBehavior. */
                rtrnValu = statusInitial; /* [SWS_E2E_00383] [SWS_E2E_00476] */
                break;
            case E2E_PGSTATUS_WRONGCRC:
                /* Error not related to counters occurred or the
                   return of the check function was not OK. */
                rtrnValu = E2E_P_ERROR; /* [SWS_E2E_00383] [SWS_E2E_00476] */
                break;
            case E2E_PGSTATUS_REPEATED:
                /* Data has a repeated counter. */
                rtrnValu = E2E_P_REPEATED; /* [SWS_E2E_00383] [SWS_E2E_00476] */
                break;
            case E2E_PGSTATUS_NONEWDATA:
                /* No new data is available. */
                rtrnValu = E2E_P_NONEWDATA; /* [SWS_E2E_00383] [SWS_E2E_00476] */
                break;
            case E2E_PGSTATUS_WRONGSEQUENCE:
                /* The checks of the Data in this cycle were successful,
                   counter jumpchanged more than the allowed delta. */
                /* [SWS_E2E_00383] [SWS_E2E_00476] */
                rtrnValu = E2E_P_WRONGSEQUENCE;
                break;
            case E2E_PGSTATUS_SYNC:
                /* return depending on profileBehavior. */
                rtrnValu = statusSync; /* [SWS_E2E_00383] [SWS_E2E_00476] */
                break;
            default:
                break;
        }
    }

    return rtrnValu;
}

#define E2E_STOP_SEC_CODE
#include "E2E_MemMap.h"
