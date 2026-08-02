/*
********************************************************************************
*
* File name: E2E_P02.c
*
* Copyright 2019-2024 Neusoft Reach Corporation.All rights reserved.
*
********************************************************************************
*
* History
*-------------------------------------------------------------------------------
********************************************************************************
* Version: 1.0
* Author/Date: WangJipeng/2019.04.20
* Change: New created
* Cause: New
********************************************************************************
* Version: 1.1
* Author/Date: wanghe/2019.05.06
* Change: Change E2E_P02Protect And E2E_P02Check Parameter From
          DataLength = ConfigPtr->DataLength - 1u to
          DataLength = ConfigPtr->DataLength/E2E_8BIT - 1u
* Cause: Bugfix
********************************************************************************
* Version: 1.2
* Author/Date: wanghe/2019.05.06
* Change: Change E2E_P02Protect And E2E_P02Check CrcValu
          From
          CrcValu = Crc_CalculateCRC8H2F(&DataID, 0x01u, 0xFFu, TRUE);
          CrcValu
            = Crc_CalculateCRC8H2F(&DataPtr[1u], DataLength, CrcValu, FALSE);
          to
          CrcValu = Crc_CalculateCRC8H2F(&DataPtr[1u], DataLength, 0xFFu, TRUE);
          CrcValu = Crc_CalculateCRC8H2F(&DataID, 0x01u, CrcValu, FALSE);
* Cause: Bugfix
********************************************************************************
* Version: 1.3
* Author/Date: wanghe/2019.05.06
* Change: Change E2E_P02Check_ChkDeltaCounter Judge Branch From
          else if( (1u < DeltaCounter <= State->MaxDeltaCounter) to
          else if( (1u < DeltaCounter) &&
          (DeltaCounter <= State->MaxDeltaCounter) )
* Cause: BugRevise
********************************************************************************
* Version: 1.4
* Author/Date: wanghe/2019.05.06
* Change: Change E2E_P02Check_ChkDeltaCounter Judge Branch From
          else to else if(DeltaCounter > State->MaxDeltaCounter)
* Cause: Bugfix
********************************************************************************
* Version: 2.0
* Author/Date: WangHe/2019.05.20
* Change: Optimization All Function
* Cause:  Optimization
********************************************************************************
* Version: 2.1
* Author/Date: WangHe/2019.11.22
* Change: Local variables are defined by hump standard and format modification.
* Cause:  Optimization
********************************************************************************
* Version: 3.0
* Author/Date : Baowanglong/2020.03.27
* Change: Nothing
* Cause: Update to V3.0
********************************************************************************
* Version: 3.1
* Author/Date : Tanjingyang/2020.09.29
* Change: 1.Add function of MemMap
*         2.Modify the function name according to the AUTOSAR specification.
* Cause: Optimization
********************************************************************************
* Version: 3.2
* Author/Date : Tanjingyang/2020.10.29
* Change: 1.Modify the function name according to the AUTOSAR specification.
* Cause: Optimization
********************************************************************************
* Version: 3.3
* Author/Date : TanJY/2020.11.03
* Change: Modify code format.
* Cause: Optimization
********************************************************************************
* Version: 3.4
* Author/Date : BaoWL/2021.03.25
* Change: E2E_P02Check function. Modify the DataPtr parameter type to const uint8*.
* Cause: Bugfix
********************************************************************************
* Version: 3.5
* Author/Date: XieYN/2021.08.12
* Change:Modify code specifications.
* Cause: Optimization
********************************************************************************
* Version: 3.6
* Author/Date: LiDaY/2024.03.18
* Change: Modifying the label of the input parameter Ptrclass for E2E function
*         and addressing some code inconsistencies.
* Cause: Optimization
********************************************************************************
* Version: 3.7
* Author/Date: LiDaY/2024.04.25
* Change: Add a memory-map label to function and variable declarations.
* Cause: Bugfix
********************************************************************************
* Version: 3.8
* Author/Date: LiDaY/2024.08.08
* Change: Change copyright information.
* Cause: Update
********************************************************************************
* Version: 3.9
* Author/Date: LiDaY/2024.08.27
* Change: Change the initial value of State ->WaitForFirstData to TRUE in
*         E2E_P02CeckInit.
* Cause: Bugfix
********************************************************************************
*/
/*
********************************************************************************
*    Includes
********************************************************************************
*/
#include "E2E_P02.h"

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

static FUNC(void, E2E_CODE) E2E_P02Check_ChkDeltaCounter
(
    sint8 DeltaCounter,
    uint8 ReceivedCounter,
    P2VAR(E2E_P02CheckStateType, AUTOMATIC, E2E_APPL_DATA) State,
    P2CONST(E2E_P02ConfigType, AUTOMATIC, E2E_APPL_DATA) Config
);
static FUNC(uint8, E2E_CODE) E2E_P02Protect_ChkParam
(
    P2CONST(E2E_P02ConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr,
    P2CONST(E2E_P02ProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
    P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr
);
static FUNC(uint8, E2E_CODE) E2E_P02Check_ChkParam
(
    P2CONST(E2E_P02ConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr,
    P2CONST(E2E_P02CheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
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
* Function Name: E2E_P02Check_ChkDeltaCounter
*
* Explanation: Check the DeltaCounter.
*
* param: DeltaCounter: This frame message counter to last frame message counter
*        difference value.
*        ReceivedCounter: This frame message counter value.
*        State: Pointer to static configuration.
*        Config: Pointer to static configuration.
*
* retval: None
********************************************************************************
*/
static FUNC(void, E2E_CODE) E2E_P02Check_ChkDeltaCounter
(
    sint8 DeltaCounter,
    uint8 ReceivedCounter,
    P2VAR(E2E_P02CheckStateType, AUTOMATIC, E2E_APPL_DATA) State,
    P2CONST(E2E_P02ConfigType, AUTOMATIC, E2E_APPL_DATA) Config
)
{
    sint8 e2eJudge0 = (sint8)E2E_JUDGE_0;
    sint8 e2eJudge1 = (sint8)E2E_JUDGE_1;

    if( e2eJudge0 == DeltaCounter ) /* [SWS_E2E_00146] */
    {
        /* [SWS_E2E_00301] */
        if( State->NoNewOrRepeatedDataCounter < E2E_P02PROTECT_COUNTERMAX )
        {
            /* increment NoNewOrRepeatedDataCounter by 1. */
            State->NoNewOrRepeatedDataCounter++; /* [SWS_E2E_00301] */
        }
        /* set status to E2E_P01STATUS_REPEATED. */
        State->Status = E2E_P02STATUS_REPEATED; /* [SWS_E2E_00146] */
    }
    else if( e2eJudge1 == DeltaCounter ) /* [SWS_E2E_00147] */
    {
        /* [SWS_E2E_00149] */
        /* set MaxDeltaCounter to MaxDeltaCounterInit of config. */
        State->MaxDeltaCounter = Config->MaxDeltaCounterInit;
        /* record counter of current message. */
        State->LastValidCounter = ReceivedCounter; /* [SWS_E2E_00151] */
        State->LostData = E2E_INIT_0;
        /* [SWS_E2E_00147] */
        /* Is NoNewOrRepeatedDataCounter acceptable in config limit. */
        if( State->NoNewOrRepeatedDataCounter <= Config->MaxNoNewOrRepeatedData )
        {
            /* [SWS_E2E_00300] */
            State->NoNewOrRepeatedDataCounter = E2E_INIT_0;
            /* SyncCounter value greater than zero,continuity check for the
               counter is not finalized yet,DeltaCounter is one. */
            if( State->SyncCounter > E2E_JUDGE_0 )
            {
                /* continuity check for the counter decrease one ,
                   DeltaCounter is one. */
                State->SyncCounter--; /* [SWS_E2E_00299] */
                State->Status = E2E_P02STATUS_SYNC;
            }
            /* continuity check for the counter is finalized,no Data has been
               lost since the last correct data reception. */
            else /* [SWS_E2E_00147] */
            {
                State->Status = E2E_P02STATUS_OK; /* [SWS_E2E_00147] */
            }
        }
        else /* NoNewOrRepeatedDataCounter is not Config limit. */
        {
            State->NoNewOrRepeatedDataCounter = E2E_INIT_0;
            /* [SWS_E2E_00300] */
            State->SyncCounter = Config->SyncCounterInit;
            State->Status = E2E_P02STATUS_SYNC;
        }
    }
    /* [SWS_E2E_00298] [SWS_E2E_00299] [SWS_E2E_00148] */
    /* Lose Multiple Data. */
    else if( (e2eJudge1 < DeltaCounter) && (DeltaCounter <= (sint8)State->MaxDeltaCounter) )
    {
        /* [SWS_E2E_00149] */
        State->MaxDeltaCounter = Config->MaxDeltaCounterInit;
        State->LastValidCounter = ReceivedCounter; /* [SWS_E2E_00151] */
        State->LostData = (uint8)DeltaCounter - (uint8)E2E_COUNTER_1;
        /* [SWS_E2E_00299] [SWS_E2E_00148] */
        /* Is NoNewOrRepeatedDataCounter acceptable in config limit. */
        if( State->NoNewOrRepeatedDataCounter <= Config->MaxNoNewOrRepeatedData )
        {
            /* [SWS_E2E_00300] */
            /* SyncCounter value greater than zero,continuity check for the
               counter is not finalized yet ,DeltaCounter in congfig limit. */
            State->NoNewOrRepeatedDataCounter = E2E_INIT_0;
            if( State->SyncCounter > E2E_JUDGE_0 ) /* [SWS_E2E_00299] */
            {
                /* continuity check for the counter decrease one ,
                   DeltaCounter in congfig limit. */
                State->SyncCounter--; /* [SWS_E2E_00299] */
                State->Status = E2E_P02STATUS_SYNC; /* [SWS_E2E_00299] */
            }
            /* SyncCounter value greater than zero,continuity check for
               the counter is finalized,DeltaCounter in congfig limit. */
            else /* [SWS_E2E_00148] */
            {
                State->Status = E2E_P02STATUS_OKSOMELOST; /* [SWS_E2E_00148] */
            }
        }
        /* [SWS_E2E_00298] */
        /* NoNewOrRepeatedDataCounter is not Config limit. */
        else
        {
            /* [SWS_E2E_00300] */
            State->NoNewOrRepeatedDataCounter = E2E_INIT_0;
            /* [SWS_E2E_00298] */
            State->SyncCounter = Config->SyncCounterInit;
            /* [SWS_E2E_00298] */
            State->Status = E2E_P02STATUS_SYNC;
        }
    }
    /* [SWS_E2E_00145] */
    /* DeltaCounter greater than config limit,wrong sequence status. */
    else if( DeltaCounter > (sint8)(State->MaxDeltaCounter) )
    {
        State->NoNewOrRepeatedDataCounter = E2E_INIT_0; /* [SWS_E2E_00300] */
        State->SyncCounter = Config->SyncCounterInit; /* [SWS_E2E_00145] */
        /* in E2E_P01PROTECT_COUNTERMAX have opportunities for recovery. */
        if( State->SyncCounter > E2E_JUDGE_0 )
        {
            /* [SWS_E2E_00149] */
            State->MaxDeltaCounter = Config->MaxDeltaCounterInit;
            State->LastValidCounter = ReceivedCounter; /* [SWS_E2E_00151] */
        }
        State->Status = E2E_P02STATUS_WRONGSEQUENCE; /* [SWS_E2E_00145] */
    }
    else
    {
        /* do nothing. */
    }
}

/*
********************************************************************************
* Function Name: E2E_P02Protect_ChkParam
*
* Explanation: Calculate CRC.(Synchronous)
*
* param: ConfigPtr: Pointer to static configuration.
*        StatePtr: Pointer to port/data communication state.
*        DataPtr: Pointer to Data to be transmitted.
*
* retval: CrcValu
********************************************************************************
*/
static FUNC(uint8, E2E_CODE) E2E_P02Protect_ChkParam
(
    P2CONST(E2E_P02ConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr,
    P2CONST(E2E_P02ProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
    P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr
)
{
    uint8 rtrnValu = E2E_INIT_0;

    if( (NULL_PTR == ConfigPtr) || (NULL_PTR == StatePtr) || (NULL_PTR == DataPtr) )
    {
        /* At least one pointer parameter is a NULL pointer. */
        rtrnValu = E2E_E_INPUTERR_NULL;
    }
    else
    {
        if( StatePtr->Counter > E2E_P02PROTECT_COUNTERMAX )
        {
            /* Counter is out of range (0-15). */
            rtrnValu = E2E_E_INPUTERR_WRONG;
        }
        else
        {
            rtrnValu = E2E_E_OK;
        }
    }

    return rtrnValu;
}

/*
********************************************************************************
* Function Name: E2E_P02Check_ChkParam
*
* Explanation: Calculate CRC.(Synchronous)
*
* param: ConfigPtr: Pointer to static configuration.
*        StatePtr: Pointer to port/data communication state.
*        DataPtr: Pointer to Data to be transmitted.
*
* retval: CrcValu
********************************************************************************
*/
static FUNC(uint8, E2E_CODE) E2E_P02Check_ChkParam
(
    P2CONST(E2E_P02ConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr,
    P2CONST(E2E_P02CheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
    P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr
)
{
    uint8 rtrnValu = E2E_INIT_0;

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
* Function Name: E2E_P02Protect
*
* Explanation: Protects the array/buffer to be transmitted using the E2E profile
*              2.(Synchronous)
* param: ConfigPtr: Pointer to static configuration.
*        StatePtr: Pointer to port/data communication state.
*        DataPtr: Pointer to Data to be transmitted
*
* retval: Std_ReturnType
********************************************************************************
*/
/* [SWS_E2E_00160]  [SWS_E2E_00126] */
FUNC(Std_ReturnType, E2E_CODE) E2E_P02Protect
(
    P2VAR(E2E_P02ConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr,
    P2VAR(E2E_P02ProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
    P2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr
)
{
    Std_ReturnType rtrnValu = E2E_E_INPUTERR_NULL;
    uint8 dataId = E2E_INIT_0;
    uint8 crcValu = E2E_INIT_0;
    uint16 dataLength = E2E_INIT_0;

    /* Check all parameters. */
    rtrnValu = E2E_P02Protect_ChkParam(ConfigPtr, StatePtr, DataPtr);
    if( E2E_E_OK == rtrnValu )
    {
        /* counter in limit range. */ /* [SWS_E2E_00128] */
        if( StatePtr->Counter < E2E_P02PROTECT_COUNTERMAX )
        {
            StatePtr->Counter++; /* [SWS_E2E_00127] */
        }
        /* [SWS_E2E_00128] */
        /* counter is not in limit range, Reinitialization. */
        else
        {
            StatePtr->Counter = E2E_INIT_0; /* [SWS_E2E_00129] */
        }
        /* [SWS_E2E_00130] */ /* Counter is written to Bits0...3 of Data[1]. */
        DataPtr[E2E_INDEX_1] = (DataPtr[E2E_INDEX_1] & E2E_HIGH_NIBBLE) |
                               (StatePtr->Counter & E2E_LOW_NIBBLE);
        /* [SWS_E2E_00120] */ /* Counter is written to Bits0...3 of Data[1]. */
        dataId = ConfigPtr->DataIDList[StatePtr->Counter];
        /* [SWS_E2E_00132] */
        dataLength = (ConfigPtr->DataLength / E2E_8BIT) - E2E_INIT_1;
        /* [SWS_E2E_00118] [SWS_E2E_00132] [SWS_E2E_00117] */
        crcValu = Crc_CalculateCRC8H2F(&DataPtr[E2E_INDEX_1], dataLength,
                                       E2E_FULL_BYTE, TRUE);
        /* [SWS_E2E_00119] [SWS_E2E_00132] [SWS_E2E_00117] */
        crcValu = Crc_CalculateCRC8H2F(&dataId, E2E_INIT_1, crcValu, FALSE);
        /* [SWS_E2E_00122] [SWS_E2E_00124] [SWS_E2E_00133] */
        /* CRC is written to Data[0]. */
        DataPtr[E2E_INDEX_0] = crcValu;
    }

    return rtrnValu;
}

/*
********************************************************************************
* Function Name: E2E_P02ProtectInit
*
* Explanation: Initializes the protection state.(Synchronous)
*
* param: StatePtr: Pointer to port/data communication state.
*
* retval: Std_ReturnType
********************************************************************************
*/
/* [SWS_E2E_00387] */
FUNC(Std_ReturnType, E2E_CODE) E2E_P02ProtectInit
(
    P2VAR(E2E_P02ProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr
)
{
    Std_ReturnType rtrnValu = E2E_E_INPUTERR_NULL; /* [SWS_E2E_00388] */

    if( NULL_PTR != StatePtr ) /* [SWS_E2E_00388] */ /* the param is valid. */
    {
        /* [SWS_E2E_00388] */ /* Initializes the counter. */
        StatePtr->Counter = E2E_INIT_0;
        rtrnValu = E2E_E_OK; /* [SWS_E2E_00388] */
    }

    return rtrnValu; /* [SWS_E2E_00388] */
}

/*
********************************************************************************
* Function Name: E2E_P02Check
*
* Explanation: Initializes the protection state.(Synchronous)
*
* param: ConfigPtr:Pointer to static configuration.
*        StatePtr:Pointer to port/data communication state.
*        DataPtr:Pointer to Data to be transmitted.
*
* retval: Std_ReturnType
********************************************************************************
*/
/* [SWS_E2E_00161] [SWS_E2E_00134] */
FUNC(Std_ReturnType, E2E_CODE) E2E_P02Check
(
    P2VAR(E2E_P02ConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr,
    P2VAR(E2E_P02CheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
    P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr
)
{
    Std_ReturnType rtrnValu = E2E_E_INPUTERR_NULL;
    uint8 dataId = E2E_INIT_0;
    uint8 crcValu = E2E_INIT_0;
    uint8 receivedCounter = E2E_INIT_0;
    sint8 deltaCounter = (sint8)E2E_INIT_0;
    sint8 e2eJudge0 = (sint8)E2E_INIT_0;
    uint16 dataLength = E2E_INIT_0;

    /* Check all parameters */
    rtrnValu = E2E_P02Check_ChkParam(ConfigPtr, StatePtr, DataPtr);
    if( E2E_E_OK == rtrnValu )
    {
        /* [SWS_E2E_00136] */
        if( StatePtr->MaxDeltaCounter < E2E_P02PROTECT_COUNTERMAX )
        {
            /* MaxDeltaCounter specifies the maximum allowed difference between
               two counter values of consecutively received valid messages. */
            StatePtr->MaxDeltaCounter ++; /* [SWS_E2E_00137] */
        }
        /* If any NEW data is available to be checked. */
        if( TRUE == StatePtr->NewDataAvailable )
        {
            /* [SWS_E2E_00139] */  /* Read the Counter from Data. */
            receivedCounter = DataPtr[E2E_INDEX_1] & E2E_LOW_NIBBLE;
            /* [SWS_E2E_00139] */ /* Read the Counter from Data ID. */
            dataId = ConfigPtr->DataIDList[receivedCounter];
            /* [SWS_E2E_00140] */
            dataLength = (ConfigPtr->DataLength / E2E_8BIT) - E2E_JUDGE_1;
            /* [SWS_E2E_00140] */
            crcValu = Crc_CalculateCRC8H2F(&DataPtr[E2E_INDEX_1], dataLength,
                                           E2E_FULL_BYTE, TRUE);
            /* [SWS_E2E_00140] */ /* Read the Counter from CRC. */
            crcValu = Crc_CalculateCRC8H2F(&dataId, E2E_INIT_1, crcValu, FALSE);
            if( crcValu == DataPtr[E2E_INDEX_0] )
            {
                /* This is the first message with correct CRC, WaitForFirstData
                   is therefore set to false.Counter is not checked as it cannot
                   be done yet. */
                if( TRUE == StatePtr->WaitForFirstData ) /* [SWS_E2E_00142] */
                {
                    /* [SWS_E2E_00143] */
                    StatePtr->WaitForFirstData = (boolean)FALSE;
                    /* [SWS_E2E_00142] */
                    StatePtr->MaxDeltaCounter = ConfigPtr->MaxDeltaCounterInit;
                    /* [SWS_E2E_00142] */
                    StatePtr->LastValidCounter = receivedCounter;
                    /* [SWS_E2E_00142] */
                    StatePtr->Status = E2E_P02STATUS_INITIAL;
                }
                else /* Compute the delta. */
                {
                    /* [SWS_E2E_00135] */
                    deltaCounter = (sint8)(receivedCounter) -
                                   (sint8)(StatePtr->LastValidCounter);
                    if( deltaCounter < e2eJudge0 ) /* [SWS_E2E_00135] */
                    {
                        /* [SWS_E2E_00135] */
                        deltaCounter = deltaCounter + (sint8)E2E_P02PROTECT_COUNTERMod;
                    }
                    /* The previous and the current data have correct CRC,
                       verify the counter. */
                    E2E_P02Check_ChkDeltaCounter(deltaCounter, receivedCounter,
                                                 StatePtr, ConfigPtr);
                }
            }
            /* ReceivedCRC, CalculatedCRC are diffrent. */ /* [SWS_E2E_00141] */
            else
            {
                StatePtr->Status = E2E_P02STATUS_WRONGCRC; /* [SWS_E2E_00141] */
            }
        }
        else /* [SWS_E2E_00138] */
        {
            /* NoNewOrRepeatedDataCounter is increase. */ /* [SWS_E2E_00301] */
            if( StatePtr->NoNewOrRepeatedDataCounter
                < E2E_P02PROTECT_COUNTERMAX )
            {
                StatePtr->NoNewOrRepeatedDataCounter++; /* [SWS_E2E_00301] */
            }
            StatePtr->Status = E2E_P02STATUS_NONEWDATA; /* [SWS_E2E_00138] */
        }
    }

    return rtrnValu;
}

/*
********************************************************************************
* Function Name: E2E_P02CheckInit
*
* Explanation: Initializes the check state.(Synchronous)
*
* param: StatePtr: Pointer to port/data communication state.
*
* retval: Std_ReturnType
********************************************************************************
*/
/* [SWS_E2E_00391] */
FUNC(Std_ReturnType, E2E_CODE) E2E_P02CheckInit
(
    P2VAR(E2E_P02CheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr
)
{
    Std_ReturnType rtrnValu = E2E_E_INPUTERR_NULL;

    if( NULL_PTR != StatePtr )  /* the param is valid. */
    {
        StatePtr->LastValidCounter = E2E_INIT_0;          /* [SWS_E2E_00392] */
        StatePtr->MaxDeltaCounter = E2E_INIT_0;           /* [SWS_E2E_00392] */
        StatePtr->WaitForFirstData = TRUE;                /* Autosar 4.4 [SWS_E2E_00392] */
        StatePtr->NewDataAvailable = TRUE;                /* [SWS_E2E_00392] */
        StatePtr->LostData = E2E_INIT_0;                  /* [SWS_E2E_00392] */
        StatePtr->Status = E2E_P02STATUS_NONEWDATA;       /* [SWS_E2E_00392] */
        StatePtr->SyncCounter = E2E_INIT_0;               /* [SWS_E2E_00392] */
        StatePtr->NoNewOrRepeatedDataCounter = E2E_INIT_0;/* [SWS_E2E_00392] */
        rtrnValu = E2E_E_OK;                              /* [SWS_E2E_00392] */
    }

    return rtrnValu;
}

/*
********************************************************************************
* Function Name: E2E_P02MapStatusToSM
*
* Explanation: Initializes the check state.(Synchronous)
*
* param: CheckReturn: Return value of the E2E_P02Check function.
*        Status: Status determined by E2E_P02Check function.
*        profileBehavior: FALSE is check has the legacy behavior, before R4.2,
*                         TRUE is check behaves like new P4/P5/P6 profiles
*                         introduced in R4.2
*
* retval: Std_ReturnType
********************************************************************************
*/
/* [SWS_E2E_00379] */
FUNC(E2E_PCheckStatusType, E2E_CODE) E2E_P02MapStatusToSM
(
    Std_ReturnType CheckReturn,
    E2E_P02CheckStatusType Status,
    boolean profileBehavior
)
{
    E2E_PCheckStatusType rtrnValu = E2E_P_ERROR;
    E2E_PCheckStatusType statusSync = E2E_P_ERROR;
    E2E_PCheckStatusType statusInitial = E2E_P_ERROR;

    if( E2E_E_OK == CheckReturn ) /* [SWS_E2E_00380] [SWS_E2E_00477] */
    {
        /* check behaves like new P4/P5/P6 profiles introduced in R4.2. */
        if( TRUE == profileBehavior ) /* [SWS_E2E_00380] */
        {
            statusSync = E2E_P_OK;
            statusInitial = E2E_P_WRONGSEQUENCE;
        }
        /* [SWS_E2E_00477] */
        /* check has the legacy behavior, before R4.2. */
        else
        {
            statusSync = E2E_P_WRONGSEQUENCE;
            statusInitial = E2E_P_OK;
        }
        switch( Status )
        {
            case E2E_P02STATUS_OK:
                /* the checks of the Data in this cycle were successful. */
                rtrnValu = E2E_P_OK; /* [SWS_E2E_00380] [SWS_E2E_00477] */
                break;
            case E2E_P02STATUS_OKSOMELOST:
                /* the checks of the Data in this cycle were successful. */
                rtrnValu = E2E_P_OK; /* [SWS_E2E_00380] [SWS_E2E_00477] */
                break;
            case E2E_P02STATUS_INITIAL:
                /* return depending on profileBehavior. */
                rtrnValu = statusInitial; /* [SWS_E2E_00380] [SWS_E2E_00477] */
                break;
            case E2E_P02STATUS_WRONGCRC:
                /* Error not related to counters occurred or the return of
                   the check function was not OK. */
                rtrnValu = E2E_P_ERROR; /* [SWS_E2E_00380] [SWS_E2E_00477] */
                break;
            case E2E_P02STATUS_REPEATED:
                /* [SWS_E2E_00380] [SWS_E2E_00477] */
                /* Data has a repeated counter. */
                rtrnValu = E2E_P_REPEATED; /* [SWS_E2E_00380] [SWS_E2E_00477] */
                break;
            case E2E_P02STATUS_NONEWDATA:
                /* [SWS_E2E_00380] [SWS_E2E_00477] */
                /* No new data is available. */
                rtrnValu = E2E_P_NONEWDATA;
                break;
            case E2E_P02STATUS_WRONGSEQUENCE:
                /* [SWS_E2E_00380] [SWS_E2E_00477] */
                /* The checks of the Data in this cycle were successful, with
                   the exception of counter jump, which changed more than the
                   allowed delta. */
                rtrnValu = E2E_P_WRONGSEQUENCE;
                break;
            case E2E_P02STATUS_SYNC:
                rtrnValu = statusSync; /* [SWS_E2E_00380] [SWS_E2E_00477] */
                break;
            default:
                break;
        }
    }
    else
    {
        rtrnValu = E2E_P_ERROR; /* [SWS_E2E_00380] [SWS_E2E_00477] */
    }

    return rtrnValu; /* [SWS_E2E_00380] [SWS_E2E_00477] */
}

#define E2E_STOP_SEC_CODE
#include "E2E_MemMap.h"
