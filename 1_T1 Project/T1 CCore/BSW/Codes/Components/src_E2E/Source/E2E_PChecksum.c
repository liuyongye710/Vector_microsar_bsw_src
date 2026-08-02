/*
********************************************************************************
*
* File name: E2E_PChecksum.c
*
* Copyright 2022-2024 Neusoft Reach Corporation.All rights reserved.
*
********************************************************************************
*
* History
*-------------------------------------------------------------------------------
********************************************************************************
* Version: 3.0
* Author/Date: XieYN/2022.08.29
* Change: New created.
* Cause: New
********************************************************************************
* Version: 3.1
* Author/Date: XieYN/2022.09.19
* Change: Delete the judgement of counter range when counter size is 16.
* Cause: Optimization
********************************************************************************
* Version: 3.2
* Author/Date: XieYN/2022.09.19
* Change: 1. Increase the configurable range of Checksum: 0 bits.
*         2. Modify code specifications.
*         3. Modify all counters to type uint16.
* Cause: Update
********************************************************************************
* Version: 3.3
* Author/Date: XieYN/2022.12.01
* Change: Modify Counter increment in E2E_PChecksumProtect_WriteCounter.
* Cause: Bugfix
********************************************************************************
* Version: 3.4
* Author/Date: XieYN/2023.01.05
* Change: Add the judgment on whether it is the first frame message when the
*         checksumsize is configured to 0 in E2E_PChecksumCheck.
* Cause: Bugfix
********************************************************************************
* Version: 3.5
* Author/Date: LiDY/2023.08.03
* Change: Compilation warning optimization
* Cause: Optimization
********************************************************************************
* Version: 3.6
* Author/Date: LiDaY/2024.02.05
* Change: Modifying the label of the input parameter Ptrclass for E2E function
*         and addressing some code inconsistencies.
* Cause: Optimization
********************************************************************************
* Version: 3.7
* Author/Date: LiDaY/2024.03.18
* Change: Modifying the label of the input parameter Ptrclass for E2E function
*         and addressing some code inconsistencies.
* Cause: Optimization
********************************************************************************
* Version: 3.8
* Author/Date: LiDaY/2024.04.25
* Change: Add a memory-map label to function and variable declarations.
* Cause: Bugfix
********************************************************************************
* Version: 3.9
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
#include "E2E_PChecksum.h"

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

static FUNC(Std_ReturnType, E2E_CODE) E2E_PChecksumCheck_ChkParam
(
    P2CONST(E2E_PChecksumConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr,
    P2VAR(E2E_PChecksumCheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
    P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr
);
static FUNC(Std_ReturnType, E2E_CODE) E2E_PChecksumProtect_ChkParam
(
    P2CONST(E2E_PChecksumConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr,
    P2VAR(E2E_PChecksumProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
    P2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr
);
static FUNC(void, E2E_CODE) E2E_PChecksumProtect_WriteChecksum
(
    P2CONST(E2E_PChecksumConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr,
    P2VAR(E2E_PChecksumProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
    P2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr,
    VAR(uint8, E2E_APPL_DATA)checksumValu
);
static FUNC(void, E2E_CODE) E2E_PChecksumProtect_WriteCounter
(
    P2CONST(E2E_PChecksumConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr,
    P2VAR(E2E_PChecksumProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
    P2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr
);
static FUNC(Std_ReturnType, E2E_CODE) E2E_PChecksum_CalChecksum
(
    P2CONST(E2E_PChecksumConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr,
    P2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr
);
static FUNC(uint16, E2E_CODE) E2E_PChecksum_CalDeltaCounter
(
    VAR(uint16, E2E_APPL_DATA) receivedCounter,
    P2CONST(E2E_PChecksumConfigType, AUTOMATIC, E2E_APPL_DATA) Config,
    P2VAR(E2E_PChecksumCheckStateType, AUTOMATIC, E2E_APPL_DATA) State
);
static FUNC(void, E2E_CODE) E2E_PChecksum_ChkDeltaCounter
(
    VAR(uint16, E2E_APPL_DATA) DeltaCounter,
    VAR(uint16, E2E_APPL_DATA) ReceivedCounter,
    P2VAR(E2E_PChecksumCheckStateType, AUTOMATIC, E2E_APPL_DATA) State,
    P2CONST(E2E_PChecksumConfigType, AUTOMATIC, E2E_APPL_DATA) Config
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
* Function Name: E2E_PChecksumCheck_ChkParam
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
static FUNC(Std_ReturnType, E2E_CODE) E2E_PChecksumCheck_ChkParam
(
    P2CONST(E2E_PChecksumConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr,
    P2VAR(E2E_PChecksumCheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
    P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr
)
{
    Std_ReturnType rtrnValu;

    E2E_DUMMY_STATEMENT(StatePtr);
    if( (NULL_PTR == ConfigPtr) || (NULL_PTR == StatePtr) || (NULL_PTR == DataPtr) )
    {
        /* At least one pointer parameter is a NULL pointer. */
        rtrnValu = E2E_E_INPUTERR_NULL;
    }
    else
    {
        if( (E2E_PCHECKSUM_COUNTERSIZE_0 == ConfigPtr->CounterSize) &&
            (E2E_PCHECKSUM_CHECKSUMSIZE_0 == ConfigPtr->ChecksumSize)  )
        {
            /* Parameter is invalid. */
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
* Function Name: E2E_PChecksumProtect_ChkParam
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
static FUNC(Std_ReturnType, E2E_CODE) E2E_PChecksumProtect_ChkParam
(
    P2CONST(E2E_PChecksumConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr,
    P2VAR(E2E_PChecksumProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
    P2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr
)
{
    Std_ReturnType rtrnValu;

    if((NULL_PTR == ConfigPtr) || (NULL_PTR == StatePtr) || (NULL_PTR == DataPtr))
    {
        /* At least one pointer parameter is a NULL pointer. */
        rtrnValu = E2E_E_INPUTERR_NULL;
    }
    else
    {
        /* Counter is out of range. */
        if( (E2E_PCHECKSUM_COUNTERSIZE_4 == ConfigPtr->CounterSize) &&
            (StatePtr->Counter > E2E_PCHECKSUMPROTECT_COUNTERMAX_4))
        {
            /* Counter is out of range (0-15). */
            rtrnValu = E2E_E_INPUTERR_WRONG;
        }
        /* E2E is invalid, Counter and checksum cannot be empty at the same time. */
        else if( (E2E_PCHECKSUM_COUNTERSIZE_0 == ConfigPtr->CounterSize) &&
            ( E2E_PCHECKSUM_CHECKSUMSIZE_0 == ConfigPtr->ChecksumSize )  )
        {
            /* E2E is invalid. */
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
* Function Name: E2E_PChecksumProtect_WriteChecksum
*
* Explanation: Write Checksum to data.(Synchronous)
*
* param:  ConfigPtr: Pointer to static configuration.
*         StatePtr: Pointer to data communication state.
*         DataPtr: Pointer to data to be transmitted.
*         checksumValu: Calculated checksum value.
*
* retval: none
********************************************************************************
*/
static FUNC(void, E2E_CODE) E2E_PChecksumProtect_WriteChecksum
(
    P2CONST(E2E_PChecksumConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr,
    P2VAR(E2E_PChecksumProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
    P2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr,
    VAR(uint8, E2E_APPL_DATA)checksumValu
)
{
    E2E_DUMMY_STATEMENT(StatePtr);
    /* ChecksumSize is 4 bits. */
    if( E2E_PCHECKSUM_CHECKSUMSIZE_4 == ConfigPtr->ChecksumSize )
    {
        /* Checksum is located in low nibble. */
        if( E2E_JUDGE_0 == (ConfigPtr->ChecksumOffset % E2E_8BIT) )
        {
            /* Copy checksum to the Data at configured location. */
            DataPtr[ConfigPtr->ChecksumOffset / E2E_8BIT]
              = (uint8)
                ((DataPtr[ConfigPtr->ChecksumOffset / E2E_8BIT] & E2E_HIGH_NIBBLE)
                | ((checksumValu) & E2E_LOW_NIBBLE));
        }
        /* Checksum is located in high nibble. */
        else
        {
            /* Copy checksum to the Data at configured location. */
            DataPtr[ConfigPtr->ChecksumOffset / E2E_8BIT]
              = (uint8)
                ((DataPtr[ConfigPtr->ChecksumOffset / E2E_8BIT] & E2E_LOW_NIBBLE)
                | ((uint8)(checksumValu << E2E_4BIT) & E2E_HIGH_NIBBLE));
        }
    }
    /* ChecksumSize is 8 bits. */
    else
    {
        /* Copy checksum to the Data at configured location. */
        DataPtr[ConfigPtr->ChecksumOffset / E2E_8BIT] = (uint8)checksumValu;
    }

}

/*
********************************************************************************
* Function Name: E2E_PChecksumProtect_WriteCounter
*
* Explanation: Write Counter.(Synchronous)
*
* param:  ConfigPtr: Pointer to static configuration.
*         StatePtr: Pointer to data communication state.
*         DataPtr: Pointer to data to be transmitted.
*
* retval: none
********************************************************************************
*/
static FUNC(void, E2E_CODE) E2E_PChecksumProtect_WriteCounter
(
    P2CONST(E2E_PChecksumConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr,
    P2VAR(E2E_PChecksumProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
    P2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr
)
{
    /* CounterSize is 4. */
    if( E2E_PCHECKSUM_COUNTERSIZE_4 == ConfigPtr->CounterSize )
    {
        /* Counter is in low nibble. */
        if( E2E_JUDGE_0 == (ConfigPtr->CounterOffset % E2E_8BIT) )
        {
           /* Copy counter to the Data at configured location. */
            DataPtr[ConfigPtr->CounterOffset / E2E_8BIT]
              = (uint8)
                ((DataPtr[ConfigPtr->CounterOffset / E2E_8BIT] & E2E_HIGH_NIBBLE)
                | ((StatePtr->Counter) & E2E_LOW_NIBBLE));
        }
        /* Counter is in high nibble. */
        else
        {
            /* Copy counter to the Data at configured location. */
            DataPtr[ConfigPtr->CounterOffset / E2E_8BIT]
              = (uint8)
                ((DataPtr[ConfigPtr->CounterOffset / E2E_8BIT] & E2E_LOW_NIBBLE)
                | ((uint8)(StatePtr->Counter << E2E_4BIT) & E2E_HIGH_NIBBLE));
        }
        /* Increment the counter by 1, next value after 15 is 0. */
        StatePtr->Counter
          = (StatePtr->Counter + E2E_INIT_1) % E2E_PCHECKSUMPROTECT_COUNTERMOD_4;
    }
    /* CounterSize is 16. */
    else
    {
        /* Counter is stored in big endian. */
        if( E2E_BIGENDIANESS == ConfigPtr->CounterEndianess )
        {
            /* Copy counter to the Data at configured location. */
            DataPtr[ConfigPtr->CounterOffset / E2E_8BIT] = (uint8)(StatePtr->Counter);
            DataPtr[ConfigPtr->CounterOffset / E2E_8BIT - E2E_INIT_1]
                = (uint8)(StatePtr->Counter >> E2E_8BIT);
        }
        /* Counter is stored in little endian. */
        else
        {
            DataPtr[ConfigPtr->CounterOffset / E2E_8BIT] = (uint8)(StatePtr->Counter);
            DataPtr[ConfigPtr->CounterOffset / E2E_8BIT + E2E_INIT_1]
                = (uint8)(StatePtr->Counter >> E2E_8BIT);
        }
        /* Increment the counter by 1, next value after 65535 is 0. */
        StatePtr->Counter
          = (StatePtr->Counter + E2E_INIT_1) % E2E_PCHECKSUMPROTECT_COUNTERMOD_16;
    }
}

/*
********************************************************************************
* Function Name: E2E_PChecksumCheck_ReadCounter
*
* Explanation: Write Checksum.(Synchronous)
*
* param:  Config: Pointer to static configuration.
*         Data: Pointer to data to be transmitted.
*
* retval: receivedChecksum.
********************************************************************************
*/
FUNC(uint16, E2E_CODE) E2E_PChecksum_ReadCounter
(
    P2CONST(E2E_PChecksumConfigType, AUTOMATIC, E2E_APPL_DATA) Config,
    P2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) Data
)
{
    uint16 readCounter= E2E_INIT_0;

    if( E2E_PCHECKSUM_COUNTERSIZE_4 == Config->CounterSize )
    {
        if( E2E_JUDGE_0 == (Config->CounterOffset % E2E_8BIT) )
        {
            readCounter
              = Data[Config->CounterOffset / E2E_8BIT] & E2E_PCHECKSUM_LOWNIBBLE;
        }
        else
        {
            readCounter
              = (Data[Config->CounterOffset / E2E_8BIT] >> E2E_4BIT) &
                E2E_PCHECKSUM_LOWNIBBLE;
        }
    }
    else
    {
        if( E2E_BIGENDIANESS == Config->CounterEndianess )
        {
            readCounter
              = ((uint16)(Data[Config->CounterOffset / E2E_8BIT])) |
                 (uint16)(Data[Config->CounterOffset / E2E_8BIT - E2E_INIT_1]
                          << E2E_8BIT);
        }
        else
        {
            readCounter
              = ((uint16)(Data[Config->CounterOffset / E2E_8BIT])) |
                 (uint16)(Data[Config->CounterOffset / E2E_8BIT + E2E_INIT_1]
                          << E2E_8BIT);
        }
    }

    return readCounter;
}

/*
********************************************************************************
* Function Name: E2E_PChecksum_ReadChecksum
*
* Explanation: Read Checksum from data. (Synchronous)
*
* param: Config: Pointer to static configuration.
*        Data: Pointer to data to be transmitted.
*
* retval: receivedChecksum
********************************************************************************
*/
FUNC(Std_ReturnType, E2E_CODE) E2E_PChecksum_ReadChecksum
(
    P2CONST(E2E_PChecksumConfigType, AUTOMATIC, E2E_APPL_DATA) Config,
    P2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) Data
)
{
    Std_ReturnType readChecksum= E2E_INIT_0;

    /* ChecksumSize is 4 bits. */
    if( E2E_PCHECKSUM_CHECKSUMSIZE_4 == Config->ChecksumSize )
    {
        /* ChecksumSize is located in low nibble. */
        if( E2E_JUDGE_0 == (Config->ChecksumOffset % E2E_8BIT) )
        {
            /* Read Checksum from data. */
            readChecksum
              = (Data[Config->ChecksumOffset / E2E_8BIT] & E2E_PCHECKSUM_LOWNIBBLE);
        }
        /* ChecksumSize is located in high nibble. */
        else
        {
            /* Read Checksum from data. */
            readChecksum
              = (Data[Config->ChecksumOffset / E2E_8BIT] >> E2E_4BIT) &
                E2E_PCHECKSUM_LOWNIBBLE;
        }
    }
    /* ChecksumSize is 8 bits. */
    else
    {
        /* Read Checksum from data. */
        readChecksum = (Data[Config->ChecksumOffset / E2E_8BIT]);
    }

    return readChecksum;
}

/*
********************************************************************************
* Function Name: E2E_PChecksum_CalChecksum
*
* Explanation: Calculate Checksum.(Synchronous)
*
* param:  ConfigPtr: Pointer to static configuration.
*         DataPtr: Pointer to data to be transmitted.
*
* retval: none
********************************************************************************
*/
static FUNC(Std_ReturnType, E2E_CODE) E2E_PChecksum_CalChecksum
(
    P2CONST(E2E_PChecksumConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr,
    P2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr
)
{
    Std_ReturnType checksumValu = E2E_INIT_0;
    uint8 checksumXORValu = ConfigPtr->ChecksumXORValue;
    uint16 checksumLen = E2E_INIT_0;

    /* Compute checksum before the checksum (checksum is not located in the first
       byte). */
    if( ConfigPtr->ChecksumOffset >= E2E_8BIT )
    {
        checksumLen = ConfigPtr->ChecksumOffset / E2E_8BIT;
        checksumValu = Crc_CalculateCommonAccumulation (checksumLen, DataPtr);
    }
    /* Compute checksum over the area after the checksum (checksum is not located
       in the last byte). */
    if( (ConfigPtr->ChecksumOffset / E2E_8BIT)
          < ((ConfigPtr->DataLength / E2E_8BIT) - E2E_INIT_1) )
    {
        checksumLen = (ConfigPtr->DataLength / E2E_8BIT) -
                      (ConfigPtr->ChecksumOffset / E2E_8BIT) - E2E_INIT_1;
        checksumValu += Crc_CalculateCommonAccumulation(checksumLen,
                        &DataPtr[(ConfigPtr->ChecksumOffset / E2E_8BIT) + E2E_INIT_1]);
    }
    checksumValu = checksumValu ^ checksumXORValu;
    /* ChecksumSize is 4 bits. */
    if( E2E_PCHECKSUM_CHECKSUMSIZE_4 == ConfigPtr->ChecksumSize )
    {
        /* Checksum is located in low nibble. */
        if( E2E_JUDGE_0 == (ConfigPtr->ChecksumOffset % E2E_8BIT) )
        {
            checksumValu = checksumValu & E2E_LOW_NIBBLE;
        }
        /* Checksum is located in high nibble. */
        else
        {
            checksumValu = checksumValu & E2E_HIGH_NIBBLE;
        }
    }

    return checksumValu;
}

/*
********************************************************************************
* Function Name: E2E_PChecksum_Chk_CalDeldaCounter
*
* Explanation: Calculate DeldaCounter.(Synchronous)
*
* param:  receivedCounter: Counter value of this frame message.
*         Config: Pointer to static configuration.
*         State: Pointer to data communication state.
*
* retval: void
********************************************************************************
*/
static FUNC(uint16, E2E_CODE) E2E_PChecksum_CalDeltaCounter
(
    VAR(uint16, E2E_APPL_DATA) receivedCounter,
    P2CONST(E2E_PChecksumConfigType, AUTOMATIC, E2E_APPL_DATA) Config,
    P2VAR(E2E_PChecksumCheckStateType, AUTOMATIC, E2E_APPL_DATA) State
)
{
    uint16 deltaCounter = E2E_INIT_0;

    if( receivedCounter >= State->LastValidCounter )
    {
        deltaCounter = receivedCounter - State->LastValidCounter;
    }
    else
    {
        /* CounterSize is 4 bits. */
        if( E2E_PCHECKSUM_COUNTERSIZE_4 == Config->CounterSize )
        {
            deltaCounter = E2E_PCHECKSUMPROTECT_COUNTERMOD_4
                           + receivedCounter
                           - State->LastValidCounter;
        }
        /* CounterSize is 16 bits. */
        else
        {
            deltaCounter = E2E_PCHECKSUMPROTECT_COUNTERMOD_16
                           + receivedCounter
                           - State->LastValidCounter;
        }

    }

    return deltaCounter;
}

/*
********************************************************************************
* Function Name: E2E_PChecksumCheck_ChkDeltaCounter
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
static FUNC(void, E2E_CODE) E2E_PChecksum_ChkDeltaCounter
(
    VAR(uint16, E2E_APPL_DATA) DeltaCounter,
    VAR(uint16, E2E_APPL_DATA) ReceivedCounter,
    P2VAR(E2E_PChecksumCheckStateType, AUTOMATIC, E2E_APPL_DATA) State,
    P2CONST(E2E_PChecksumConfigType, AUTOMATIC, E2E_APPL_DATA) Config
)
{
    if( E2E_JUDGE_0 == DeltaCounter )
    {
        /* CounterSize is 4. */
        if( E2E_PCHECKSUM_COUNTERSIZE_4 == Config->CounterSize )
        {
            if( State->NoNewOrRepeatedDataCounter < E2E_PCHECKSUMPROTECT_COUNTERMAX_4 )
            {
                /* Increment NoNewOrRepeatedDataCounter by 1. */
                State->NoNewOrRepeatedDataCounter++;
            }
        }
        /* CounterSize is 16. */
        else
        {
            if( State->NoNewOrRepeatedDataCounter < E2E_PCHECKSUMPROTECT_COUNTERMAX_16 )
            {
                /* Increment NoNewOrRepeatedDataCounter by 1. */
                State->NoNewOrRepeatedDataCounter++;
            }
        }
        /* Set status to E2E_PCHECKSUMSTATUS_REPEATED. */
        State->Status = E2E_PCHECKSUMSTATUS_REPEATED;
    }
    else if( E2E_JUDGE_1 == DeltaCounter )
    {
        /* Set MaxDeltaCounter to the configured MaxDeltaCounterInit. */
        State->MaxDeltaCounter = Config->MaxDeltaCounterInit;
        /* Record counter of current message. */
        State->LastValidCounter = ReceivedCounter;
        State->LostData = E2E_INIT_0;
        /* NoNewOrRepeatedDataCounter is in configured limited range. */
        if( State->NoNewOrRepeatedDataCounter <= Config->MaxNoNewOrRepeatedData )
        {
            State->NoNewOrRepeatedDataCounter = E2E_INIT_0;
            /* SyncCounter is greater than zero, continually check the SyncCounter. */
            if( State->SyncCounter > E2E_JUDGE_0 )
            {
                /* SyncCounter decrease by one. */
                State->SyncCounter--;
                State->Status = E2E_PCHECKSUMSTATUS_SYNC;
            }
            /* Check SyncCounter is completely, no Data has been lost since the
               last correct data reception. */
            else
            {
                State->Status = E2E_PCHECKSUMSTATUS_OK;
            }
        }
        /* NoNewOrRepeatedDataCounter is out of configured limit range. */
        else
        {
            State->NoNewOrRepeatedDataCounter = E2E_INIT_0;
            State->SyncCounter = Config->SyncCounterInit;
            State->Status = E2E_PCHECKSUMSTATUS_SYNC;
        }
    }
    /* Lose Multiple Data. */
    else if( DeltaCounter < State->MaxDeltaCounter )
    {
        State->MaxDeltaCounter = Config->MaxDeltaCounterInit;
        State->LastValidCounter = ReceivedCounter;
        State->LostData = DeltaCounter - E2E_COUNTER_1;
        /* NoNewOrRepeatedDataCounter is in configured limited range. */
        if( State->NoNewOrRepeatedDataCounter <= Config->MaxNoNewOrRepeatedData )
        {
            State->NoNewOrRepeatedDataCounter = E2E_INIT_0;
            /* SyncCounter is greater than zero, continue to check. */
            if( State->SyncCounter > E2E_JUDGE_0 )
            {
                /* Continue to check, decrease SyncCounter by 1. */
                State->SyncCounter--;
                State->Status = E2E_PCHECKSUMSTATUS_SYNC;
            }
            /* SyncCounter is zero. */
            else
            {
                State->Status = E2E_PCHECKSUMSTATUS_OKSOMELOST;
            }
        }
        /* NoNewOrRepeatedDataCounter is out of configured limited range. */
        else
        {
            State->NoNewOrRepeatedDataCounter = E2E_INIT_0;
            State->SyncCounter = Config->SyncCounterInit;
            State->Status = E2E_PCHECKSUMSTATUS_SYNC;
        }
    }
    /* DeltaCounter is out of configured limited range, wrong sequence status. */
    else
    {
        State->NoNewOrRepeatedDataCounter = E2E_INIT_0;
        State->SyncCounter = Config->SyncCounterInit;
        /* In E2E_PCHECKSUMPROTECT_COUNTERMAX limit have opportunities for recovery. */
        if( State->SyncCounter > E2E_JUDGE_0 )
        {
            State->MaxDeltaCounter = Config->MaxDeltaCounterInit;
            State->LastValidCounter = ReceivedCounter;
        }
        State->Status = E2E_PCHECKSUMSTATUS_WRONGSEQUENCE;
    }
}

/*
********************************************************************************
* Function Name: E2E_PChecksumProtect
*
* Explanation: Protect the data to be transmitted by using the E2E_PChecksumProtect.
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
FUNC(Std_ReturnType, E2E_CODE) E2E_PChecksumProtect
(
    P2CONST(E2E_PChecksumConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr,
    P2VAR(E2E_PChecksumProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
    P2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr
)
{
    Std_ReturnType rtrnValu;
    uint8 checksumValu;

    /* Check all parameters. */
    rtrnValu = E2E_PChecksumProtect_ChkParam(ConfigPtr, StatePtr, DataPtr);
    /* All parameters are valid. */
    if( E2E_E_OK == rtrnValu )
    {
        /* Counter is used. */
        if( E2E_JUDGE_0 < ConfigPtr->CounterSize )
        {
            /* Write Counter to data. */
            E2E_PChecksumProtect_WriteCounter(ConfigPtr, StatePtr, DataPtr);
        }
        /* Checksum is used. */
        if( E2E_JUDGE_0 < ConfigPtr->ChecksumSize )
        {
            /* Calculate checksum over Data. */
            checksumValu = E2E_PChecksum_CalChecksum(ConfigPtr, DataPtr);
            /* Write Checksum to data. */
            E2E_PChecksumProtect_WriteChecksum(ConfigPtr, StatePtr, DataPtr, checksumValu);
        }
    }

    return rtrnValu;
}

/*
********************************************************************************
* Function Name: E2E_PChecksumProtectInit
*
* Explanation: Initializes the protection state.(Synchronous)
*
* param:  StatePtr: Pointer to data communication state.
*
* retval: Std_ReturnType
********************************************************************************
*/
FUNC(Std_ReturnType, E2E_CODE) E2E_PChecksumProtectInit
(
    P2VAR(E2E_PChecksumProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr
)
{
    Std_ReturnType rtrnValu = E2E_E_INPUTERR_NULL;
    /* Check whether the input parameter is a null pointer. */
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
* Function Name: E2E_PChecksumCheck
*
* Explanation: Checks the Data received by using the E2E_PChecksumCheck. This includes
*              checksum calculation,handling of Counter and Data ID.(Synchronous)
*
* param:  Config: Pointer to static configuration.
*         Data: Poiter to received data.
*         State: Pointer to data communication state.
*
* retval: Std_ReturnType
********************************************************************************
*/
FUNC(Std_ReturnType, E2E_CODE) E2E_PChecksumCheck
(
    P2CONST(E2E_PChecksumConfigType, AUTOMATIC, E2E_APPL_DATA) Config,
    P2VAR(E2E_PChecksumCheckStateType, AUTOMATIC, E2E_APPL_DATA) State,
    P2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) Data
)
{
    Std_ReturnType rtrnValu;
    uint8 receivedChecksum= E2E_INIT_0;
    uint8 calculatedChecksum = E2E_INIT_0;
    uint16 receivedCounter = E2E_INIT_0;
    uint16 deltaCounter = E2E_INIT_0;

    /* Check all parameters. */
    rtrnValu = E2E_PChecksumCheck_ChkParam(Config, State, Data);
    if( E2E_E_OK == rtrnValu )
    {
        /* Counter is used. */
        if( ((E2E_PCHECKSUM_COUNTERSIZE_4 == Config->CounterSize) &&
            (State->MaxDeltaCounter < E2E_PCHECKSUMPROTECT_COUNTERMAX_4)) ||
            (E2E_PCHECKSUM_COUNTERSIZE_16 == Config->CounterSize &&
            (State->MaxDeltaCounter < E2E_PCHECKSUMPROTECT_COUNTERMAX_16)) )
        {
            /* Increase MaxDeltaCounter by 1. */
            State->MaxDeltaCounter++;
        }
        /* If any new data is available to be checked. */
        if( TRUE == State->NewDataAvailable )
        {
            /* Counter is used. */
            if( E2E_PCHECKSUM_COUNTERSIZE_0 != Config->CounterSize )
            {
                /* Read Counter from Data. */
                receivedCounter = E2E_PChecksum_ReadCounter(Config, Data);
                /* ReceivedCounter is in limited range. */
                if( ((E2E_PCHECKSUM_COUNTERSIZE_4 == Config->CounterSize) &&
                    (receivedCounter <= E2E_PCHECKSUMPROTECT_COUNTERMAX_4)) ||
                    (E2E_PCHECKSUM_COUNTERSIZE_16 == Config->CounterSize) )
                {
                    /* Checksum is used. */
                    if( (E2E_PCHECKSUM_CHECKSUMSIZE_0 != Config->ChecksumSize) )
                    {
                        /* Read Checksum from Data. */
                        receivedChecksum = E2E_PChecksum_ReadChecksum(Config, Data);
                        /* Calculate Checksum in the same way as the Sender did. */
                        calculatedChecksum = E2E_PChecksum_CalChecksum(Config, Data);
                        /* ReceivedChecksum is ok. */
                        if( receivedChecksum == calculatedChecksum )
                        {
                            /* Check if any correct data has already be received. */
                            if( (boolean)TRUE == State->WaitForFirstData )
                            {
                                /* This is the first message with correct Checksum,
                                   WaitForFirstData is therefore set to false.
                                   Counter is not checked as it cannot be done yet. */
                                State->WaitForFirstData = FALSE;
                                State->MaxDeltaCounter = Config->MaxDeltaCounterInit;
                                State->LastValidCounter = receivedCounter;
                                State->Status = E2E_PCHECKSUMSTATUS_INITIAL;
                            }
                            else
                            {
                                /* Calculate the deltaCounter. */
                                deltaCounter
                                  = E2E_PChecksum_CalDeltaCounter(receivedCounter,
                                                                  Config,
                                                                  State);
                                /* Verify the counter. */
                                E2E_PChecksum_ChkDeltaCounter(deltaCounter,
                                                              receivedCounter,
                                                              State,
                                                              Config);
                            }
                        }

                        /* ReceivedChecksum and CalculatedChecksum are diffrent. */
                        else
                        {
                            State->Status = E2E_PCHECKSUMSTATUS_WRONGCHECKSUM;
                        }
                     }
                    else
                    {
                        if( (boolean)TRUE == State->WaitForFirstData )
                        {
                            /* This is the first message with correct Checksum,
                               WaitForFirstData is therefore set to false.
                               Counter is not checked as it cannot be done yet. */
                            State->WaitForFirstData = FALSE;
                            State->MaxDeltaCounter = Config->MaxDeltaCounterInit;
                            State->LastValidCounter = receivedCounter;
                            State->Status = E2E_PCHECKSUMSTATUS_INITIAL;
                        }
                        else
                        {
                            /* Calculate the deltaCounter. */
                            deltaCounter
                              = E2E_PChecksum_CalDeltaCounter(receivedCounter, Config, State);

                            /* Verify the counter. */
                            E2E_PChecksum_ChkDeltaCounter(deltaCounter, receivedCounter,
                                                          State, Config);
                        }
                    }
                }
                /* ReceivedCounter is out of range. */
                else
                {
                    rtrnValu = E2E_E_INPUTERR_WRONG;
                }
            }
            /* No Counter. */
            else
            {
                /* Read Checksum from Data. */
                receivedChecksum = E2E_PChecksum_ReadChecksum(Config, Data);
                /* Calculate Checksum in the same way as the Sender did. */
                calculatedChecksum = E2E_PChecksum_CalChecksum(Config, Data);
                /* ReceivedChecksum is ok? */
                if( receivedChecksum == calculatedChecksum )
                {
                    /* Check if any correct data has already been received. */
                    if( (boolean)TRUE == State->WaitForFirstData )
                    {
                        /* This is the first message with correct Checksum,
                           WaitForFirstData is therefore set to false. Counter
                           is not checked as it cannot be done yet. */
                        State->WaitForFirstData = FALSE;
                        State->Status = E2E_PCHECKSUMSTATUS_INITIAL;
                    }
                    else
                    {
                        State->Status = E2E_PCHECKSUMSTATUS_OK;
                    }
                }
                /* ReceivedChecksum and CalculatedChecksum are diffrent. */
                else
                {
                    State->Status = E2E_PCHECKSUMSTATUS_WRONGCHECKSUM;
                }
            }
        }
        else
        {
            /* Increase NoNewOrRepeatedDataCounter by 1. */
            if( ((E2E_PCHECKSUM_COUNTERSIZE_4 == Config->CounterSize) &&
                (State->NoNewOrRepeatedDataCounter < E2E_PCHECKSUMPROTECT_COUNTERMAX_4)) ||
                (E2E_PCHECKSUM_COUNTERSIZE_16 == Config->CounterSize &&
                (State->NoNewOrRepeatedDataCounter < E2E_PCHECKSUMPROTECT_COUNTERMAX_16)) )
            {
                State->NoNewOrRepeatedDataCounter++;
            }
            State->Status = E2E_PCHECKSUMSTATUS_NONEWDATA;
        }
    }

    return (rtrnValu);
}

/*
********************************************************************************
* Function Name: E2E_PChecksumCheckInit
*
* Explanation: Initializes the check state.(Synchronous)
*
* param: State: Pointer to data communication state.
*
* retval: Std_ReturnType
********************************************************************************
*/
FUNC(Std_ReturnType, E2E_CODE) E2E_PChecksumCheckInit
(
    P2VAR(E2E_PChecksumCheckStateType, AUTOMATIC, E2E_APPL_DATA) State
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
        State->Status = E2E_PCHECKSUMSTATUS_NONEWDATA;
        State->SyncCounter = E2E_INIT_0;
        State->NoNewOrRepeatedDataCounter = E2E_INIT_0;
        rtrnValu = E2E_E_OK;
    }

    return rtrnValu;
}

/*
********************************************************************************
* Function Name: E2E_PChecksumMapStatusToSM
*
* Explanation: The function maps the check status of E2E_PChecksumCheck to a generic check status,
*              which can be used by E2E state machine check function. (Synchronous)
*
* param:  CheckReturn: Return value of the E2E_PChecksumCheck function.
*         Status: Status determined by E2E_PChecksumCheck function.
*
* retval: E2E_PCheckStatusType
********************************************************************************
*/
FUNC(E2E_PCheckStatusType, E2E_CODE) E2E_PChecksumMapStatusToSM
(
    Std_ReturnType CheckReturn,
    E2E_PChecksumCheckStatusType Status
)
{
    E2E_PCheckStatusType rtrnValu = E2E_P_ERROR;
    E2E_PCheckStatusType Status_Sync = E2E_P_ERROR;
    E2E_PCheckStatusType Status_Initial = E2E_P_ERROR;

    if( E2E_E_OK == CheckReturn )
    {
        switch ( Status )
        {
            case E2E_PCHECKSUMSTATUS_OK:
                /* The checks of the Data in this cycle were successful. */
                rtrnValu = E2E_P_OK;
                break;
            case E2E_PCHECKSUMSTATUS_OKSOMELOST:
                /* The checks of the Data in this cycle were successful. */
                rtrnValu = E2E_P_OK;
                break;
            case E2E_PCHECKSUMSTATUS_INITIAL:
                /* Return depending on profileBehavior */
                rtrnValu = Status_Initial;
                break;
            case E2E_PCHECKSUMSTATUS_WRONGCHECKSUM:
                /* Error not related to counters occurred or the return of the
                   check function was not OK. */
                rtrnValu = E2E_P_ERROR;
                break;
            case E2E_PCHECKSUMSTATUS_REPEATED:
                /* Data has a repeated counter */
                rtrnValu = E2E_P_REPEATED;
                break;
            case E2E_PCHECKSUMSTATUS_NONEWDATA:
                /* No new data is available */
                rtrnValu = E2E_P_NONEWDATA;
                break;
            case E2E_PCHECKSUMSTATUS_WRONGSEQUENCE:
                /* The checks of Data in this cycle were successful with the
                   exception of counter, which exceeded the limited range. */
                rtrnValu = E2E_P_WRONGSEQUENCE;
                break;
            case E2E_PCHECKSUMSTATUS_SYNC:
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
