/*
********************************************************************************
*
* File name: E2E_P05.c
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
* Change: Change E2E_P05Check_ChkParam And E2E_P05Protect_ChkParam Judge Branch
          From if( Length == ConfigPtr->DataLength )
          to if( Length == (ConfigPtr->DataLength/E2E_8BIT) ).
* Cause: Bugfix
********************************************************************************
* Version: 1.2
* Author/Date: wanghe/2019.05.06
* Change: Change E2E_P05_ComputeCrc Pass Parameter From
*         ComputedCRC
*         = Crc_CalculateCRC16(Config->DataID & 0xFF, 1u, ComputedCRC, FALSE),
*         to ComputedCRC
*         = Crc_CalculateCRC16(DataID, 2u, ComputedCRC, FALSE).
* Cause: Bugfix
********************************************************************************
* Version: 1.3
* Author/Date: WangHe/2019.05.20
* Change: Optimization All Function
* Cause:  Optimization
********************************************************************************
* Version: 2.0
* Author/Date: wanghe/2019.7.25
* Change: Change E2E_P05_ComputeCrc Pass Parameter From
          LengthAf = ConfigPtr->DataLength - Offset - E2E_2BIT;
          to LengthAf = (ConfigPtr->DataLength / E2E_8BIT) - Offset - E2E_2BIT;
* Cause: Bugfix
********************************************************************************
* Version: 2.1
* Author/Date: WangHe/2019.11.22
* Change: Local variables are defined by hump standard and format modification.
* Cause:  Optimization
********************************************************************************
* Version: 2.2
* Author/Date: WangHe/2019.12.13
* Change: E2E_P05Check function counter difference value reverse.
* Cause:  Bugfix
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
* Change: E2E_P05Check function. Modify the DataPtr parameter type to const uint8*.
* Cause: Bugfix
********************************************************************************
* Version: 3.5
* Author/Date : BaoWL/2021.04.09
* Change: In the E2E_P05Check function.
*         Use newDataAvailable as the parameter of the E2E_P05Check_ChkParam function.
* Cause: Bugfix
********************************************************************************
* Version: 3.6
* Author/Date: XieYN/2021.08.13
* Change:Modify code specifications.
* Cause: Optimization
********************************************************************************
* Version: 3.7
* Author/Date : XieYN/2022.06.06
* Change: Modify Crc byte order in E2E_P05Protect and E2E_P05Check.
* Cause: Bugfix
********************************************************************************
* Version: 3.8
* Author/Date: LiDY/2023.07.13
* Change:E2E_P05CheckInit the counter shall be initialized with 0xFF
* Cause: Bugfix
********************************************************************************
* Version: 3.9
* Author/Date: LiDaY/2024.03.18
* Change: Modifying the label of the input parameter Ptrclass for E2E function
*         and addressing some code inconsistencies.
* Cause: Optimization
********************************************************************************
* Version: 3.10
* Author/Date: LiDaY/2024.04.25
* Change: Add a memory-map label to function and variable declarations.
* Cause: Bugfix
********************************************************************************
* Version: 3.11
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
#include "E2E_P05.h"

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

static FUNC(uint16, E2E_CODE) E2E_P05_ComputeCrc
(
    P2CONST(E2E_P05ConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr,
    P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr,
    uint16 Offset
);
static FUNC(uint8, E2E_CODE) E2E_P05Check_ChkParam
(
    P2CONST(E2E_P05ConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr,
    P2CONST(E2E_P05CheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
    P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr,
    P2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) NewDataAvailable,
    uint16 Length
);
static FUNC(uint8, E2E_CODE) E2E_P05Protect_ChkParam
(
    P2CONST(E2E_P05ConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr,
    P2CONST(E2E_P05ProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
    P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr,
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
* Function Name: E2E_P05_ComputeCrc
*
* Explanation: Calculate CRC.(Synchronous)
*
* param: ConfigPtr: Pointer to static configuration.
*        DataPtr: Pointer to Data to be transmitted.
*        Offset: Byte offset of the first bit of the E2E header.
*
* retval: CrcValu
********************************************************************************
*/
/* [SWS_E2E_00406] */
static FUNC(uint16, E2E_CODE) E2E_P05_ComputeCrc
(
    P2CONST(E2E_P05ConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr,
    P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr,
    uint16 Offset
)
{
    uint16 lengthAf = E2E_INIT_0;
    uint16 computedCrc = E2E_INIT_0;
    uint8 dataID[E2E_INDEX_2] = {E2E_INIT_0,E2E_INIT_0};

    /* [SWS_E2E_00406] */
    lengthAf = (ConfigPtr->DataLength / E2E_8BIT) - Offset - E2E_2BIT;
    /* Calculation CRC, Before data and after data of crc. */
    if( ConfigPtr->Offset > E2E_JUDGE_0 ) /* [SWS_E2E_00406] */
    {
        /* [SWS_E2E_00400] [SWS_E2E_00406] */
        computedCrc = Crc_CalculateCRC16(DataPtr, Offset, E2E_FULL_2BYTE, TRUE);
        /* [SWS_E2E_00400] [SWS_E2E_00406] */
        computedCrc = Crc_CalculateCRC16(&DataPtr[Offset + E2E_2BIT],
                                         lengthAf, computedCrc, FALSE);
    }
    else /* [SWS_E2E_00406] */ /* Calculation CRC,after data of crc. */
    {
        /* [SWS_E2E_00400] [SWS_E2E_00406] */
        computedCrc = Crc_CalculateCRC16(&DataPtr[Offset + E2E_2BIT],
                                         lengthAf, E2E_FULL_2BYTE, TRUE);
    }
    /* [SWS_E2E_00399] [SWS_E2E_00406] */
    dataID[E2E_INDEX_0] = (uint8)ConfigPtr->DataID & E2E_FULL_BYTE;
    /* [SWS_E2E_00399] [SWS_E2E_00406] */
    dataID[E2E_INDEX_1] = (uint8)(ConfigPtr->DataID >> E2E_8BIT) & E2E_FULL_BYTE;
    /* [SWS_E2E_00399] [SWS_E2E_00400] [SWS_E2E_00401] [SWS_E2E_00406] */
    /* Calculation CRC,data ID. */
    computedCrc = Crc_CalculateCRC16(dataID, E2E_2BIT, computedCrc, FALSE);

    return computedCrc; /* [SWS_E2E_00406] */
}

/*
********************************************************************************
* Function Name: E2E_P04Check_ChkParam
*
* Explanation: Chekck parameter.(Synchronous)
*
* param: ConfigPtr: Pointer to static configuration.
*        StatePtr: Pointer to port/data communication state.
*        DataPtr: Pointer to Data to be transmitted.
*        NewDataAvailable: New data available.
*        Length: Data length.
*
* retval: CrcValu
********************************************************************************
*/
/* [SWS_E2E_00412] */
static FUNC(uint8, E2E_CODE) E2E_P05Check_ChkParam
(
    P2CONST(E2E_P05ConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr,
    P2CONST(E2E_P05CheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
    P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr,
    P2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) NewDataAvailable,
    uint16 Length
)
{
    uint8 rtrnValu = E2E_E_INPUTERR_NULL; /* [SWS_E2E_00412] */

    /* [SWS_E2E_00412] */
    /* At least one pointer parameter is a NULL pointer. */
    if( (NULL_PTR != ConfigPtr) && (NULL_PTR != StatePtr) )
    {
        /* [SWS_E2E_00412] */ /* data Meet the requirements. */
        if( ((NULL_PTR != DataPtr) && (E2E_JUDGE_0 != Length)) ||
            ((NULL_PTR == DataPtr) && (E2E_JUDGE_0 == Length)) )
        {
            if( NULL_PTR != DataPtr ) /* [SWS_E2E_00412] */
            {
                /* [SWS_E2E_00412] */ /* data length is in limit range. */
                if( Length == (ConfigPtr->DataLength / E2E_8BIT) )
                {
                    *NewDataAvailable = TRUE; /* [SWS_E2E_00412] */
                    rtrnValu = E2E_E_OK; /* [SWS_E2E_00412] */
                }
                else /* [SWS_E2E_00412] */
                {
                    rtrnValu = E2E_E_INPUTERR_WRONG; /* [SWS_E2E_00412] */
                }
            }
            else /* [SWS_E2E_00412] */ /* data pointer is ok. */
            {
                rtrnValu = E2E_E_OK; /* [SWS_E2E_00412] */
            }
        }
        else /* [SWS_E2E_00412] */
        {
            rtrnValu = E2E_E_INPUTERR_WRONG; /* [SWS_E2E_00412] */
        }
    }
    else /* [SWS_E2E_00412] */
    {
        rtrnValu = E2E_E_INPUTERR_NULL; /* [SWS_E2E_00412] */
    }

    return rtrnValu; /* [SWS_E2E_00412] */
}

/*
********************************************************************************
* Function Name: E2E_P05Protect_ChkParam
*
* Explanation: Calculate CRC.(Synchronous)
*
* param: ConfigPtr: Pointer to static configuration.
*        StatePtr: Pointer to port/data communication state.
*        DataPtr: Pointer to Data to be transmitted.
*        Length: Data length.
*
* retval: CrcValu
********************************************************************************
*/
/* [SWS_E2E_00404] */
static FUNC(uint8, E2E_CODE) E2E_P05Protect_ChkParam
(
    P2CONST(E2E_P05ConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr,
    P2CONST(E2E_P05ProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
    P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr,
    uint16 Length
)
{
    uint8 rtrnValu = E2E_E_INPUTERR_NULL;

    /* [SWS_E2E_00404] */
    if( (NULL_PTR == ConfigPtr) || (NULL_PTR == StatePtr) || (NULL_PTR == DataPtr) )
    {
        /* At least one pointer parameter is a NULL pointer. */
        rtrnValu = E2E_E_INPUTERR_NULL; /* [SWS_E2E_00404] */
    }
    else /* [SWS_E2E_00404] */
    {
        /* data length is in limit range */
        if( Length == (ConfigPtr->DataLength / E2E_8BIT) ) /* [SWS_E2E_00404] */
        {
            rtrnValu = E2E_E_OK; /* [SWS_E2E_00404] */
        }
        else
        {
            rtrnValu = E2E_E_INPUTERR_WRONG; /* [SWS_E2E_00404] */
        }
    }

    return rtrnValu; /* [SWS_E2E_00404] */
}

/*
********************************************************************************
* Function Name: E2E_P05Protect
*
* Explanation: Protects the array/buffer to be transmitted using the E2E profile
*              5.(Synchronous)
* param: ConfigPtr: Pointer to static configuration.
*        StatePtr: Pointer to port/data communication state.
*        DataPtr: Pointer to Data to be transmitted.
*        Length: Length of the data in bytes.
*
* retval: Std_ReturnType
********************************************************************************
*/
/* [SWS_E2E_00446] [SWS_E2E_00403] */
FUNC(Std_ReturnType, E2E_CODE) E2E_P05Protect
(
    P2VAR(E2E_P05ConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr,
    P2VAR(E2E_P05ProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
    P2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr,
    uint16 Length
)
{
    Std_ReturnType rtrnValu = E2E_E_INPUTERR_NULL;
    uint16 offset = E2E_INIT_0;
    uint16 computedCrc = E2E_INIT_0;

    /* [SWS_E2E_00403] */ /* Check all parameters. */
    rtrnValu = E2E_P05Protect_ChkParam(ConfigPtr, StatePtr, DataPtr, Length);
    if( E2E_E_OK == rtrnValu )
    {
        /* [SWS_E2E_00403] [SWS_E2E_00469] */ /* Compute offset. */
        offset = ConfigPtr->Offset / E2E_8BIT;
        /* [SWS_E2E_00403] [SWS_E2E_00405]*/ /* Write Counter. */
        DataPtr[offset + E2E_2BIT] = StatePtr->Counter;
        /* [SWS_E2E_00403] */ /* Compute CRC. */
        computedCrc = E2E_P05_ComputeCrc(ConfigPtr, DataPtr, offset);
        /* [SWS_E2E_00403] [SWS_E2E_00407] */  /* Write CRC. */
        DataPtr[offset] = (uint8)computedCrc & E2E_FULL_BYTE;
        /* [SWS_E2E_00403] [SWS_E2E_00407] */
        DataPtr[offset + E2E_1BIT] = (uint8)(computedCrc >> E2E_8BIT) & E2E_FULL_BYTE;

        /* [SWS_E2E_00403] [SWS_E2E_00397] [SWS_E2E_00409] */
        /* Increment Counter,Counter beyond range. */
        if( StatePtr->Counter >= E2E_P05PROTECT_COUNTERMAX )
        {
            /* [SWS_E2E_00403] [SWS_E2E_00397] [SWS_E2E_00409] */
            StatePtr->Counter = E2E_INIT_0;
        }
        /* [SWS_E2E_00403] [SWS_E2E_00397] [SWS_E2E_00409] */
        /* Increment Counter. */
        else
        {
            /* [SWS_E2E_00403] [SWS_E2E_00397]  [SWS_E2E_00409]*/
            StatePtr->Counter++;
        }
    }

    return rtrnValu;
}

/*
********************************************************************************
* Function Name: E2E_P05ProtectInit
*
* Explanation: Initializes the protection state.(Synchronous)
*
* param: StatePtr: Pointer to port/data communication state.
*
* retval: Std_ReturnType
********************************************************************************
*/
/* [SWS_E2E_00447] */
FUNC(Std_ReturnType, E2E_CODE) E2E_P05ProtectInit
(
    P2VAR(E2E_P05ProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr
)
{
    Std_ReturnType rtrnValu = E2E_E_INPUTERR_NULL; /* [SWS_E2E_00448] */

    if( NULL_PTR != StatePtr ) /* [SWS_E2E_00448] */ /* the param is valid. */
    {
        StatePtr->Counter = E2E_INIT_0; /* [SWS_E2E_00448] */
        rtrnValu = E2E_E_OK; /* [SWS_E2E_00448] */
    }

    return rtrnValu; /* [SWS_E2E_00448] */
}

/*
********************************************************************************
* Function Name: E2E_P05Check
*
* Explanation: Checks the Data received using the E2E profile 5.(Synchronous)
*
* param: ConfigPtr: Pointer to static configuration.
*        StatePtr: Pointer to port/data communication state.
*        DataPtr: Pointer to received data.
*        Length: Length of the data in bytes.
*
* retval: Std_ReturnType
********************************************************************************
*/
/* [SWS_E2E_00449] [SWS_E2E_00411] */
FUNC(Std_ReturnType, E2E_CODE) E2E_P05Check
(
    P2VAR(E2E_P05ConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr,
    P2VAR(E2E_P05CheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
    P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr,
    uint16 Length
)
{
    Std_ReturnType rtrnValu = E2E_E_INPUTERR_NULL;
    uint8 newDataAvailable = FALSE;
    uint8 receivedCounter = E2E_INIT_FULL1BYTE; /* [SWS_E2E_00472] */
    uint16 offset = E2E_INIT_0;
    uint16 receivedCrc = E2E_INIT_0;
    uint16 computedCrc = E2E_INIT_0;
    sint16 deltaCounter = (sint16)E2E_INIT_0;
    sint16 e2eJudge0 = (sint16)E2E_INIT_0;
    sint16 e2eJudge1 = (sint16)E2E_INIT_1;

    /* [SWS_E2E_00411] */ /* Verify inputs of the protect function. */
    rtrnValu = E2E_P05Check_ChkParam(ConfigPtr, StatePtr, DataPtr,
                                     &newDataAvailable, Length);
    if( E2E_E_OK == rtrnValu ) /* [SWS_E2E_00411] */
    {
        /* If any NEW data is available to be checked. */
        if( TRUE == newDataAvailable ) /* [SWS_E2E_00411] */
        {
            /* [SWS_E2E_00411] [SWS_E2E_00413] */
            offset = ConfigPtr->Offset / E2E_8BIT;
            /* [SWS_E2E_00411] */ /* Read Data counter. */
            receivedCounter = DataPtr[offset + E2E_2BIT];
            /* [SWS_E2E_00411] [SWS_E2E_00414] */ /* Read Data crc. */
            receivedCrc = (uint16)(DataPtr[offset]) & E2E_INIT_FULL1BYTE;
            /* [SWS_E2E_00411] [SWS_E2E_00414] */ /* Read Data crc. */
            receivedCrc |= (uint16)((uint16)(DataPtr[offset + E2E_1BIT]) << E2E_8BIT);
            /* [SWS_E2E_00411] */ /* compute crc. */
            computedCrc = E2E_P05_ComputeCrc(ConfigPtr, DataPtr, offset);
            /* compare received crc and compute crc. */
            if( receivedCrc == computedCrc ) /* [SWS_E2E_00416] */
            {
                /* [SWS_E2E_00416] */
                if( receivedCounter >= StatePtr->Counter )
                {
                    deltaCounter = (sint16)receivedCounter - (sint16)StatePtr->Counter;
                }
                else /* [SWS_E2E_00416] */
                {
                    /* [SWS_E2E_00416] */
                    deltaCounter = (sint16)receivedCounter - (sint16)StatePtr->Counter
                                   + (sint16)E2E_P05PROTECT_COUNTERMAX
                                   + (sint16)E2E_COUNTER_1;
                }
                if( (deltaCounter <= (sint16)ConfigPtr->MaxDeltaCounter) &&
                    (deltaCounter >= e2eJudge0) ) /* [SWS_E2E_00416] */
                {
                    if( deltaCounter > e2eJudge0 ) /* [SWS_E2E_00416] */
                    {
                        /* the checks of the Data in this cycle were successful
                           including counter check, which was incremented by 1. */
                        if( e2eJudge1 == deltaCounter ) /* [SWS_E2E_00416] */
                        {
                            StatePtr->Status = E2E_P05STATUS_OK;
                            /* [SWS_E2E_00416] */
                        }
                        /* the checks of the Data in this cycle were successful,
                           ounter check which was incremented within the allowed
                           configured delta. */
                        else /* [SWS_E2E_00416] */
                        {
                            StatePtr->Status = E2E_P05STATUS_OKSOMELOST;
                            /* [SWS_E2E_00416] */
                        }
                    } /* [SWS_E2E_00416] */
                    else /* [SWS_E2E_00416] */ /* repeate data. */
                    {
                        StatePtr->Status = E2E_P05STATUS_REPEATED;
                        /* [SWS_E2E_00416] */
                    }
                }
                /* with the exception of counter jump,
                   which changed more than the allowed delta. */
                else /* [SWS_E2E_00416] */
                {
                    StatePtr->Status = E2E_P05STATUS_WRONGSEQUENCE;
                    /* [SWS_E2E_00416] */
                }
                StatePtr->Counter = receivedCounter; /* [SWS_E2E_00416] */
            }
            else /* [SWS_E2E_00416] */
            {
                StatePtr->Status = E2E_P05STATUS_ERROR; /* [SWS_E2E_00416] */
            }
        }
        else /* [SWS_E2E_00416] */
        {
            StatePtr->Status = E2E_P05STATUS_NONEWDATA; /* [SWS_E2E_00416] */
        }
    }

    return rtrnValu; /* [SWS_E2E_00411] */
}

/*
********************************************************************************
* Function Name: E2E_P05CheckInit
*
* Explanation: Initializes the check state.(Synchronous)
*
* param: StatePtr: Pointer to port/data communication state.
*
* retval: Std_ReturnType
********************************************************************************
*/
/* [SWS_E2E_00450] */
FUNC(Std_ReturnType, E2E_CODE) E2E_P05CheckInit
(
    P2VAR(E2E_P05CheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr
)
{
    Std_ReturnType rtrnValu = E2E_E_INPUTERR_NULL; /* [SWS_E2E_00451] */
    if( NULL_PTR != StatePtr ) /* [SWS_E2E_00451] */ /* the param is valid. */
    {
        StatePtr->Counter = E2E_INIT_FULL1BYTE;            /* [SWS_E2E_00451] */
        StatePtr->Status = E2E_P05STATUS_ERROR;   /* [SWS_E2E_00451] */
        rtrnValu = E2E_E_OK;                       /* [SWS_E2E_00451] */
    }

    return rtrnValu; /* [SWS_E2E_00451] */
}

/*
********************************************************************************
* Function Name: E2E_P05MapStatusToSM
*
* Explanation: The function maps the check status of Profile 5 to a generic
*              check status,which can be used by E2E state machine check
*              function. The E2E Profile 5 delivers a more fine-granular status,
*              but this is not relevant for the E2E state machine.(Synchronous)
*
* param: CheckReturn: Return value of the E2E_P04Check function.
*        Status: Status determined by E2E_P04Check function.
*
* retval: Std_ReturnType
********************************************************************************
*/
/* [SWS_E2E_00452] */
FUNC(E2E_PCheckStatusType, E2E_CODE) E2E_P05MapStatusToSM
(
    Std_ReturnType CheckReturn,
    E2E_P05CheckStatusType Status
)
{
    E2E_PCheckStatusType rtrnValu = E2E_P_ERROR; /* [SWS_E2E_00454] */

    if( E2E_E_OK == CheckReturn ) /* [SWS_E2E_00453] */
    {
        switch( Status ) /* [SWS_E2E_00453] */
        {
            case E2E_P05STATUS_OK:
                rtrnValu = E2E_P_OK; /* [SWS_E2E_00453] */
                break;
            case E2E_P05STATUS_OKSOMELOST:
                rtrnValu = E2E_P_OK; /* [SWS_E2E_00453] */
                break;
            case E2E_P05STATUS_ERROR:
                rtrnValu = E2E_P_ERROR; /* [SWS_E2E_00453] */
                break;
            case E2E_P05STATUS_REPEATED:
                rtrnValu = E2E_P_REPEATED; /* [SWS_E2E_00453] */
                break;
            case E2E_P05STATUS_NONEWDATA:
                rtrnValu = E2E_P_NONEWDATA; /* [SWS_E2E_00453] */
                break;
            case E2E_P05STATUS_WRONGSEQUENCE:
                rtrnValu = E2E_P_WRONGSEQUENCE; /* [SWS_E2E_00453] */
                break;
            default:
                break;
        }
    }

    return rtrnValu; /* [SWS_E2E_00454] */
}

#define E2E_STOP_SEC_CODE
#include "E2E_MemMap.h"
