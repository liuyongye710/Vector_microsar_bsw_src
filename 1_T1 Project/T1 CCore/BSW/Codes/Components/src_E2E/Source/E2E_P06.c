/*
********************************************************************************
*
* File name: E2E_P06.c
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
* Change: Change E2E_P06_ComputeCrc Pass Parameter From
*         ComputedCRC = Crc_CalculateCRC16(DataID, 2u, 0xFFFFu, TRUE);
*         to ComputedCRC = Crc_CalculateCRC16(DataID, 2u, ComputedCRC, FALSE);
* Cause: Bugfix
********************************************************************************
* Version: 1.2
* Author/Date: wanghe/2019.05.06
* Change: Change E2E_P06Check_ChkParam And E2E_P06Protect_ChkParam Judge Branch
*         From if ((Length >= ConfigPtr->MinDataLength)
*         && (Length <= ConfigPtr->MaxDataLength))
*         to if ((Length >= ConfigPtr->MinDataLength/E2E_8BIT)
*         && (Length <= ConfigPtr->MaxDataLength/E2E_8BIT)).
* Cause: Bugfix
********************************************************************************
* Version: 1.3
* Author/Date: wanghe/2019.05.06
* Change: Change E2E_P06Protect Data Ptr Offset From
*         DataPtr[0u] = ComputedCRC>>8u & 0xFFu;
*         DataPtr[1u] = ComputedCRC & 0xFFu
*         to DataPtr[Offset] = ComputedCRC>>8u & 0xFFu;
*         DataPtr[Offset+1u] = ComputedCRC & 0xFFu.
* Cause: Bugfix
********************************************************************************
* Version: 1.4
* Author/Date: WangHe/2019.05.20
* Change: Optimization All Function.
* Cause:  Optimization
********************************************************************************
* Version: 2.0
* Author/Date: wanghe/2019.6.17
* Change: Change E2E_P06_ComputeCrc 148 line From
*         ComputedCRC
*         = Crc_CalculateCRC16(DataID, E2E_INIT_2, E2E_FULL_2BYTE, FALSE) to
*         ComputedCRC
*         = Crc_CalculateCRC16(DataID, E2E_INIT_2, ComputedCRC, FALSE).
* Cause: Bugfix
********************************************************************************
* Version: 2.1
* Author/Date: WangHe/2019.11.22
* Change: Local variables are defined by hump standard and format modification.
* Cause:  Optimization
********************************************************************************
* Version: 2.2
* Author/Date: WangHe/2019.12.13
* Change: E2E_P06Check Function counter difference value reverse.
* Cause:  Bugfix
********************************************************************************
* Version: 3.0
* Author/Date : Baowanglong/2020.03.27
* Change: Change E2E_INIT_0 to E2E_INIT_0S
* Cause: QAC
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
* Change: E2E_P06Check function. Modify the DataPtr parameter type to const uint8*.
* Cause: Bugfix
********************************************************************************
* Version: 3.5
* Author/Date: XieYN/2021.08.13
* Change:Modify code specifications.
* Cause: Optimization
********************************************************************************
* Version: 3.6
* Author/Date: LiDY/2023.07.13
* Change:E2E_P06CheckInit the counter shall be initialized with 0xFF
* Cause: Bugfix
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
#include "E2E_P06.h"

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

static FUNC(uint16, E2E_CODE) E2E_P06_ComputeCrc
(
    P2CONST(E2E_P06ConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr,
    uint16 Offset,
    P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr,
    uint16 Length
);
static FUNC(void, E2E_CODE) E2E_P06Check_ChkDeltaCounter
(
    P2CONST(E2E_P06ConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr,
    P2VAR(E2E_P06CheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
    sint16 DeltaCounter
);
static FUNC(uint8, E2E_CODE) E2E_P06Protect_ChkParam
(
    P2CONST(E2E_P06ConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr,
    P2CONST(E2E_P06ProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
    P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr,
    uint16 Length
);
static FUNC(uint8, E2E_CODE) E2E_P06Check_ChkParam
(
    P2CONST(E2E_P06ConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr,
    P2CONST(E2E_P06CheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
    P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr,
    P2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) NewDataAvailable,
    uint16 Length
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
* Function Name: E2E_P06_ComputeCrc
*
* Explanation: Calculate CRC.(Synchronous)
*
* param: ConfigPtr: Pointer to static configuration.
*        StatePtr: Pointer to port/data communication state.
*        DataPtr: Pointer to Data to be transmitted.
*        Length: Data Length.
*
* retval: CrcValu
********************************************************************************
*/
/* [SWS_E2E_00427] */
static FUNC(uint16, E2E_CODE) E2E_P06_ComputeCrc
(
    P2CONST(E2E_P06ConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr,
    uint16 Offset,
    P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr,
    uint16 Length
)
{
    uint16 computedCrc = E2E_INIT_0;
    uint16 lengthAf = E2E_INIT_0;
    uint8 dataId[E2E_INDEX_2] = {E2E_INIT_0,E2E_INIT_0};

    lengthAf = Length - (Offset + E2E_2BIT); /* [SWS_E2E_00427] */
    /* Calculation CRC, Before data and after data of crc. */
    if( ConfigPtr->Offset > E2E_JUDGE_0 ) /* [SWS_E2E_00427] */
    {
        /* [SWS_E2E_00427] [SWS_E2E_00420] */
        computedCrc = Crc_CalculateCRC16(DataPtr, Offset, E2E_FULL_2BYTE, TRUE);
        /* [SWS_E2E_00427] [SWS_E2E_00420] */
        computedCrc = Crc_CalculateCRC16(&DataPtr[Offset + E2E_2BIT],
                                         lengthAf, computedCrc, FALSE);
    }
    else /* [SWS_E2E_00427] */ /* Calculation CRC,after data of crc. */
    {
        /* [SWS_E2E_00427] [SWS_E2E_00420] */
        computedCrc = Crc_CalculateCRC16(&DataPtr[Offset + E2E_2BIT],
                                         lengthAf, E2E_FULL_2BYTE, TRUE);
    }
    /* [SWS_E2E_00419] [SWS_E2E_00427] */
    dataId[E2E_INDEX_0] = (uint8)(ConfigPtr->DataID >> E2E_8BIT) & E2E_FULL_BYTE;
    /* [SWS_E2E_00419] [SWS_E2E_00427] */
    dataId[E2E_INDEX_1] = (uint8)(ConfigPtr->DataID) & E2E_FULL_BYTE;
    /* [SWS_E2E_00419] [SWS_E2E_00420] [SWS_E2E_00421] [SWS_E2E_00427] */
    /* Calculation CRC,data ID. */
    computedCrc = Crc_CalculateCRC16(dataId, E2E_INIT_2, computedCrc, FALSE);

    return computedCrc; /* [SWS_E2E_00427] */
}

/*
********************************************************************************
* Function Name: E2E_P06Check_ChkDeltaCounter
*
* Explanation: Check parameter.(Synchronous)
*
* param: ConfigPtr: Pointer to static configuration.
*        StatePtr: Pointer to port/data communication state.
*        DeltaCounter: between two counter values of two consecutively received
*                      valid Data.
*
* retval: None
********************************************************************************
*/
static FUNC(void, E2E_CODE) E2E_P06Check_ChkDeltaCounter
(
    P2CONST(E2E_P06ConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr,
    P2VAR(E2E_P06CheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
    sint16 DeltaCounter
)
{
    sint16 e2eJudge0 = (sint16)E2E_INIT_0;
    sint16 e2eJudge1 = (sint16)E2E_INIT_1;

    if( (DeltaCounter <= (sint16)ConfigPtr->MaxDeltaCounter) &&
        (DeltaCounter >= e2eJudge0) )
    {
        if( DeltaCounter > e2eJudge0 )
        {
            /* the checks of the Data in this cycle were successful
               including counter check, which was incremented by 1. */
            if( e2eJudge1 == DeltaCounter )
            {
                StatePtr->Status = E2E_P06STATUS_OK;
            }
            /* the checks of the Data in this cycle were successful,
               ounter check which was incremented within the allowed
               configured delta. */
            else
            {
                StatePtr->Status = E2E_P06STATUS_OKSOMELOST;
            }
        }
        else   /* repeate data. */
        {
            StatePtr->Status = E2E_P06STATUS_REPEATED;
        }
    }
    /* with the exception of counter jump,
       which changed more than the allowed delta. */
    else
    {
        StatePtr->Status = E2E_P06STATUS_WRONGSEQUENCE;
    }
}

/*
********************************************************************************
* Function Name: E2E_P06Protect_ChkParam
*
* Explanation: Calculate CRC.(Synchronous)
*
* param: ConfigPtr: Pointer to static configuration.
*        StatePtr: Pointer to port/data communication state.
*        DataPtr: Pointer to Data to be transmitted.
*        Length: Data Length.
*
* retval: CrcValu
********************************************************************************
*/
/* [SWS_E2E_00424] */
static FUNC(uint8, E2E_CODE) E2E_P06Protect_ChkParam
(
    P2CONST(E2E_P06ConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr,
    P2CONST(E2E_P06ProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
    P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr,
    uint16 Length
)
{
    uint8 rtrnValu = E2E_E_INPUTERR_NULL;
    uint16 minDataByte = E2E_INIT_0; /* [SWS_E2E_00424] */
    uint16 maxDataByte = E2E_INIT_0; /* [SWS_E2E_00424] */

    if( (NULL_PTR == ConfigPtr) || (NULL_PTR == StatePtr) || (NULL_PTR == DataPtr) )
        /* [SWS_E2E_00424] */
    {
        /* At least one pointer parameter is a NULL pointer. */
        rtrnValu = E2E_E_INPUTERR_NULL; /* [SWS_E2E_00424] */
    }
    else
    {
        minDataByte = ConfigPtr->MinDataLength / E2E_8BIT; /* [SWS_E2E_00424] */
        maxDataByte = ConfigPtr->MaxDataLength / E2E_8BIT; /* [SWS_E2E_00424] */
        /* [SWS_E2E_00424] */ /* data length is in limit range. */
        if( (Length >= minDataByte) && (Length <= maxDataByte) )
        {
            rtrnValu = E2E_E_OK; /* [SWS_E2E_00424] */
        }
        else
        {
            rtrnValu = E2E_E_INPUTERR_WRONG; /* [SWS_E2E_00424] */
        }
    }

    return rtrnValu; /* [SWS_E2E_00424] */
}

/*
********************************************************************************
* Function Name: E2E_P06Check_ChkParam
*
* Explanation: Check parameter.(Synchronous)
*
* param: ConfigPtr: Pointer to static configuration.
*        StatePtr: Pointer to port/data communication state.
*        DataPtr: Pointer to Data to be transmitted.
*        NewDataAvailable: New Data Available.
*        Length: Data Length.
*
* retval: CrcValu
********************************************************************************
*/
/* [SWS_E2E_00431] */
static FUNC(uint8, E2E_CODE) E2E_P06Check_ChkParam
(
    P2CONST(E2E_P06ConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr,
    P2CONST(E2E_P06CheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
    P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr,
    P2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) NewDataAvailable,
    uint16 Length
)
{
    uint8 rtrnValu = E2E_E_INPUTERR_NULL;
    uint16 minDataByte = E2E_INIT_0;
    uint16 maxDataByte = E2E_INIT_0;

    /* [SWS_E2E_00431] */
    /* At least one pointer parameter is a NULL pointer. */
    if( (NULL_PTR != ConfigPtr) && (NULL_PTR != StatePtr) )
    {
        /* [SWS_E2E_00431] */ /* data Meet the requirements. */
        if( ((NULL_PTR != DataPtr) && (E2E_JUDGE_0 != Length)) ||
            ((NULL_PTR == DataPtr) && (E2E_JUDGE_0 == Length)) )
        {
            if( NULL_PTR != DataPtr ) /* [SWS_E2E_00431] */
            {
                minDataByte = ConfigPtr->MinDataLength / E2E_8BIT;
                maxDataByte = ConfigPtr->MaxDataLength / E2E_8BIT;
                /* [SWS_E2E_00431] */ /* data length is in limit range. */
                if( (Length >= minDataByte) && (Length <= maxDataByte) )
                {
                    *NewDataAvailable = TRUE; /* [SWS_E2E_00431] */
                    rtrnValu = E2E_E_OK; /* [SWS_E2E_00431] */
                }
                else /* [SWS_E2E_00431] */
                {
                    rtrnValu = E2E_E_INPUTERR_WRONG; /* [SWS_E2E_00431] */
                }
            }
            else /* [SWS_E2E_00431] */ /* data pointer is ok. */
            {
                rtrnValu = E2E_E_OK; /* [SWS_E2E_00431] */
            }
        }
        else /* [SWS_E2E_00431] */
        {
            rtrnValu = E2E_E_INPUTERR_WRONG; /* [SWS_E2E_00431] */
        }
    }
    else /* [SWS_E2E_00431] */
    {
        rtrnValu = E2E_E_INPUTERR_NULL; /* [SWS_E2E_00431] */
    }

    return rtrnValu; /* [SWS_E2E_00431] */
}

/*
********************************************************************************
* Function Name: E2E_P06Protect
*
* Explanation: Protects the array/buffer to be transmitted using the E2E profile
*              6.This includes checksum calculation, handling of counter.
*              (Synchronous)
*
* param: ConfigPtr: Pointer to static configuration.
*        StatePtr: Pointer to port/data communication state.
*        DataPtr: Pointer to Data to be transmitted.
*        Length: Length of the data in bytes.
*
* retval: Std_ReturnType
********************************************************************************
*/
/* [SWS_E2E_00393] [SWS_E2E_00423] */
FUNC(Std_ReturnType, E2E_CODE) E2E_P06Protect
(
    P2VAR(E2E_P06ConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr,
    P2VAR(E2E_P06ProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
    P2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr,
    uint16 Length
)
{
    Std_ReturnType rtrnValu = E2E_E_INPUTERR_NULL;
    uint16 offset = E2E_INIT_0;
    uint16 computedCrc = E2E_INIT_0;

    /* [SWS_E2E_00423] [SWS_E2E_00424] */   /* Check parameter. */
    rtrnValu = E2E_P06Protect_ChkParam(ConfigPtr, StatePtr, DataPtr, Length);
    if( E2E_E_OK == rtrnValu )
    {
        /* [SWS_E2E_00423] [SWS_E2E_00470] */ /* Compute offset. */
        offset = ConfigPtr->Offset / E2E_8BIT;
        /* [SWS_E2E_00423] [SWS_E2E_00425] */ /* Write Length. */
        DataPtr[offset + E2E_INDEX_2] = (uint8)(Length >> E2E_8BIT) & E2E_FULL_BYTE;
        /* [SWS_E2E_00423] [SWS_E2E_00425] */
        DataPtr[offset + E2E_INDEX_3] = (uint8)Length & E2E_FULL_BYTE;
        /* [SWS_E2E_00423] [SWS_E2E_00426] */ /* Write Counter. */
        DataPtr[offset + E2E_INDEX_4] = StatePtr->Counter;
        /* [SWS_E2E_00423] [SWS_E2E_00427] */   /* Compute CRC. */
        computedCrc = E2E_P06_ComputeCrc(ConfigPtr, offset, DataPtr, Length);
        /* [SWS_E2E_00423] [SWS_E2E_00428] */ /* Write CRC. */
        DataPtr[offset] = (uint8)(computedCrc >> E2E_8BIT) & E2E_FULL_BYTE;
        /* [SWS_E2E_00423] [SWS_E2E_00428] */
        DataPtr[offset + E2E_INDEX_1] = (uint8)computedCrc & E2E_FULL_BYTE;
        /* [SWS_E2E_00417] [SWS_E2E_00429] */ /* Increment Counter. */
        if( StatePtr->Counter >= E2E_FULL_BYTE )
        {
            /* [SWS_E2E_00417] [SWS_E2E_00429] */
            /* After 0xFF, the next value is 0. */
            StatePtr->Counter = E2E_INIT_0;
        }
        else /* [SWS_E2E_00417] [SWS_E2E_00429] */
        {
            /* [SWS_E2E_00417] [SWS_E2E_00423] [SWS_E2E_00429] */
            StatePtr->Counter++;
        }
    }

    return rtrnValu; /* [SWS_E2E_00423] */
}

/*
********************************************************************************
* Function Name: E2E_P06ProtectInit
*
* Explanation: Initializes the protection state.(Synchronous)
*
* param: StatePtr: Pointer to port/data communication state.
*
* retval: Std_ReturnType
********************************************************************************
*/
/* [SWS_E2E_00455] */
FUNC(Std_ReturnType, E2E_CODE) E2E_P06ProtectInit
(
    P2VAR(E2E_P06ProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr
)
{
    Std_ReturnType rtrnValu = E2E_E_INPUTERR_NULL; /* [SWS_E2E_00456] */

    if( NULL_PTR != StatePtr ) /* [SWS_E2E_00456] */ /* the param is valid. */
    {
        StatePtr->Counter = E2E_INIT_0; /* [SWS_E2E_00456] */
        rtrnValu = E2E_E_OK; /* [SWS_E2E_00456] */
    }

    return rtrnValu; /* [SWS_E2E_00456] */
}

/*
********************************************************************************
* Function Name: E2E_P06Check
*
* Explanation: Checks the Data received using the E2E profile 6. This includes
*              CRC calculation,handling of Counter.The function checks only one
*              single data in one cycle, it does not determine/compute the
*              accumulated state of the communication link.(Synchronous)
*
* param: ConfigPtr: Pointer to static configuration.
*        StatePtr: Pointer to port/data communication state.
*        DataPtr: Pointer to received data.
*        Length: Length of the data in bytes.
*
* retval: Std_ReturnType
********************************************************************************
*/
/* [SWS_E2E_00457] [SWS_E2E_00430] */
FUNC(Std_ReturnType, E2E_CODE) E2E_P06Check
(
    P2VAR(E2E_P06ConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr,
    P2VAR(E2E_P06CheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
    P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr,
    uint16 Length
)
{
    Std_ReturnType rtrnValu = E2E_E_INPUTERR_NULL;
    uint8 newDataAvailable = FALSE;
    uint16 offset = E2E_INIT_0;
    uint16 receivedLength = E2E_INIT_0;
    uint16 receivedCounter = E2E_INIT_FULL1BYTE; /* [SWS_E2E_00473] */
    uint16 receivedCrc = E2E_INIT_0;
    uint16 computedCrc = E2E_INIT_0;
    sint16 deltaCounter = E2E_INIT_0S;

    /* [SWS_E2E_00430] [SWS_E2E_00431] */
    /* Verify inputs of the protect function. */
    rtrnValu = E2E_P06Check_ChkParam(ConfigPtr, StatePtr, DataPtr,
                                     &newDataAvailable, Length);
    if( E2E_E_OK == rtrnValu )
    {
        /* If any NEW data is available to be checked. */
        if( (uint8)TRUE == newDataAvailable ) /* [SWS_E2E_00430] */
        {
            offset = ConfigPtr->Offset / E2E_8BIT; /* [SWS_E2E_00430] */
            /* [SWS_E2E_00430]  [SWS_E2E_00432]*/
            receivedLength = (uint16)((uint16)DataPtr[offset + E2E_INDEX_2] << E2E_8BIT)
                & E2E_HIGH_BYTE;
            /* [SWS_E2E_00430] [SWS_E2E_00432] */ /* receive data length. */
            receivedLength |= ((uint16)DataPtr[offset + E2E_INDEX_3] & E2E_FULL_BYTE);
            /* [SWS_E2E_00430] [SWS_E2E_00433] */ /* receive data counter. */
            receivedCounter = (uint16)DataPtr[offset + E2E_INDEX_4];
            /* [SWS_E2E_00430] [SWS_E2E_00434] */
            receivedCrc = (uint16)((uint16)DataPtr[offset] << E2E_8BIT) & E2E_HIGH_BYTE;
            /* [SWS_E2E_00430] [SWS_E2E_00434] */ /* receive data crc. */
            receivedCrc |= ((uint16)DataPtr[offset + E2E_INDEX_1] & E2E_FULL_BYTE);
            /* [SWS_E2E_00430] */ /* Compute CRC. */
            computedCrc = E2E_P06_ComputeCrc(ConfigPtr, offset, DataPtr, Length);
            /* [SWS_E2E_00436] */ /* compare received crc and compute crc. */
            if( receivedCrc == computedCrc )
            {
                /* [SWS_E2E_00436] */
                /* compare received data length and actual data length. */
                if( receivedLength == Length )
                {
                    /* [SWS_E2E_00436] */ /* Calculation this time counter
                       and Last time counter difference value. */
                    if( receivedCounter >= StatePtr->Counter )
                    {
                        deltaCounter = (sint16)receivedCounter
                                       - (sint16)StatePtr->Counter;
                    }
                    else /* [SWS_E2E_00416] */
                    {
                        /* [SWS_E2E_00416] */
                        deltaCounter = (sint16)receivedCounter
                                       - (sint16)StatePtr->Counter
                                       + (sint16)E2E_P06PROTECT_COUNTERMAX
                                       + (sint16)E2E_COUNTER_1;
                    }
                     E2E_P06Check_ChkDeltaCounter(ConfigPtr, StatePtr, deltaCounter);
                     /* [SWS_E2E_00436] */
                }
                else /* [SWS_E2E_00436] */
                {
                    StatePtr->Status = E2E_P06STATUS_ERROR;
                    /* [SWS_E2E_00436] */
                }
            }
            else /* [SWS_E2E_00436] */ /* CRC error. */
            {
                StatePtr->Status = E2E_P06STATUS_ERROR; /* [SWS_E2E_00436] */
            }
            StatePtr->Counter = (uint8)receivedCounter; /* [SWS_E2E_00436] */
        }
        else /* [SWS_E2E_00436] */ /* no new data. */
        {
            StatePtr->Status = E2E_P06STATUS_NONEWDATA; /* [SWS_E2E_00436] */
        }
    }

    return rtrnValu; /* [SWS_E2E_00431] */
}

/*
********************************************************************************
* Function Name: E2E_P06CheckInit
*
* Explanation: Initializes the check state.(Synchronous)
*
* param: StatePtr: Pointer to port/data communication state.
*
* retval: Std_ReturnType
********************************************************************************
*/
/* [SWS_E2E_00458] */
FUNC(Std_ReturnType, E2E_CODE) E2E_P06CheckInit
(
    P2VAR(E2E_P06CheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr
)
{
    Std_ReturnType rtrnValu = E2E_E_INPUTERR_NULL; /* [SWS_E2E_00459] */

    if( NULL_PTR != StatePtr) /* [SWS_E2E_00459] */ /* the param is valid. */
    {
        StatePtr->Counter = E2E_INIT_FULL1BYTE; /* [SWS_E2E_00459] */
        StatePtr->Status = E2E_P06STATUS_ERROR; /* [SWS_E2E_00459] */
        rtrnValu = E2E_E_OK; /* [SWS_E2E_00459] */
    }

    return rtrnValu; /* [SWS_E2E_00459] */
}

/*
********************************************************************************
* Function Name: E2E_P06MapStatusToSM
*
* Explanation: The function maps the check status of Profile 1 to a generic
*              check status,which can be used by E2E state machine check
*              function.(Synchronous)
*
* param: CheckReturn: Return value of the E2E_P01Check function.
*        Status: Status determined by E2E_P01Check function.
*
* retval: E2E_PCheckStatusType
********************************************************************************
*/
/* [SWS_E2E_00460] */
FUNC(E2E_PCheckStatusType, E2E_CODE) E2E_P06MapStatusToSM
(
    Std_ReturnType CheckReturn,
    E2E_P06CheckStatusType Status
)
{
    E2E_PCheckStatusType rtrnValu = E2E_P_ERROR; /* [SWS_E2E_00462] */

    if( E2E_E_OK == CheckReturn ) /* [SWS_E2E_00461] */
    {
        switch( Status ) /* [SWS_E2E_00461] */
        {
            case E2E_P06STATUS_OK:
                rtrnValu = E2E_P_OK; /* [SWS_E2E_00461] */
                break;
            case E2E_P06STATUS_OKSOMELOST:
                rtrnValu = E2E_P_OK; /* [SWS_E2E_00461] */
                break;
            case E2E_P06STATUS_ERROR:
                rtrnValu = E2E_P_ERROR; /* [SWS_E2E_00461] */
                break;
            case E2E_P06STATUS_REPEATED:
                rtrnValu = E2E_P_REPEATED; /* [SWS_E2E_00461] */
                break;
            case E2E_P06STATUS_NONEWDATA:
                rtrnValu = E2E_P_NONEWDATA; /* [SWS_E2E_00461] */
                break;
            case E2E_P06STATUS_WRONGSEQUENCE:
                rtrnValu = E2E_P_WRONGSEQUENCE; /* [SWS_E2E_00461] */
                break;
            default:
                break;
        }
    }

    return rtrnValu; /* [SWS_E2E_00461] [SWS_E2E_00462] */
}

#define E2E_STOP_SEC_CODE
#include "E2E_MemMap.h"
