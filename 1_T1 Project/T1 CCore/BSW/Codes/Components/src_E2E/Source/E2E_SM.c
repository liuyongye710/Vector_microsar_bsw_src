/*
********************************************************************************
*
* File name: E2E_SM.c
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
* Author/Date: WangHe/2019.05.20
* Change: Optimization All Function
* Cause:  Optimization
********************************************************************************
* Version: 2.0
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
* Change: Modify the function name according to the AUTOSAR specification.
* Cause: Optimization
********************************************************************************
* Version: 3.3
* Author/Date : TanJY/2020.11.03
* Change: Modify code format.
* Cause: Optimization
********************************************************************************
* Version: 3.4
* Author/Date: XieYN/2021.08.13
* Change:Modify code specifications.
* Cause: Optimization
********************************************************************************
* Version: 3.5
* Author/Date: LiDaY/2024.03.18
* Change: Modifying the label of the input parameter Ptrclass for E2E function
*         and addressing some code inconsistencies.
* Cause: Optimization
********************************************************************************
* Version: 3.6
* Author/Date: LiDaY/2024.04.25
* Change: Add a memory-map label to function and variable declarations.
* Cause: Bugfix
********************************************************************************
* Version: 3.7
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
#include "E2E_SM.h"

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

static FUNC(Std_ReturnType, E2E_CODE) E2E_SMCheck_ChkParam
(
    P2CONST(E2E_SMCheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
    P2CONST(E2E_SMConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr
);
static FUNC(void, E2E_CODE) E2E_SMAddStatus
(
    E2E_PCheckStatusType ProfileStatus,
    P2CONST(E2E_SMConfigType, AUTOMATIC, E2E_APPL_DATA) Config,
    P2VAR(E2E_SMCheckStateType, AUTOMATIC, E2E_APPL_DATA) State
);
static FUNC(void, E2E_CODE) E2E_SMClearStatus
(
    P2CONST(E2E_SMConfigType, AUTOMATIC, E2E_APPL_DATA) Config,
    P2VAR(E2E_SMCheckStateType, AUTOMATIC, E2E_APPL_DATA) State
);

#define E2E_STOP_SEC_CODE
#include "E2E_MemMap.h"

/*
********************************************************************************
*    Global Variable
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
* Function Name: E2E_SMCheck_ChkParam
*
* Explanation: Checks parameter.(Synchronous)
*
* param: ConfigPtr: Pointer to static configuration.
*        StatePtr: Pointer to port/data communication state.
*
* retval: Std_ReturnType
********************************************************************************
*/
static FUNC(Std_ReturnType, E2E_CODE) E2E_SMCheck_ChkParam
(
    P2CONST(E2E_SMCheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
    P2CONST(E2E_SMConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr
)
{
    Std_ReturnType rtrnValu = E2E_E_INPUTERR_NULL;

    /* At least one pointer parameter is a NULL pointer. */
    if( (NULL_PTR == StatePtr) || (NULL_PTR == ConfigPtr) )
    {
        rtrnValu = E2E_E_INPUTERR_NULL;
    }
    else  /* all pointer is not null pointer. */
    {
        if( NULL_PTR == StatePtr->ProfileStatusWindow )
        {
            rtrnValu = E2E_E_INPUTERR_NULL;
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
* Function Name: E2E_SMAddStatus
*
* Explanation: E2E_SMAddStatus is just a logical step in the algorithm, it may
*              (but it does not have to be) implemented a a separate function.
*              It is not a module API function.(Synchronous)
*
* param: ProfileStatus: Profile-independent status of the reception on
*                       one single Data in one cycle.
*        ConfigPtr: Pointer to static configuration.
*        StatePtr: Pointer to port/data communication state.
*
* retval: None
********************************************************************************
*/
/* [SWS_E2E_00466] */
static FUNC(void, E2E_CODE) E2E_SMAddStatus
(
    E2E_PCheckStatusType ProfileStatus,
    P2CONST(E2E_SMConfigType, AUTOMATIC, E2E_APPL_DATA) Config,
    P2VAR(E2E_SMCheckStateType, AUTOMATIC, E2E_APPL_DATA) State
)
{
    uint8 profileIdx = E2E_INIT_0;

    State->OkCount = E2E_INIT_0;
    State->ErrorCount = E2E_INIT_0;
    /* [SWS_E2E_00466] */
    State->ProfileStatusWindow[State->WindowTopIndex] = (uint8)ProfileStatus;
    /* [SWS_E2E_00466] */ /* Monitoring state of whole state machine. */
    for( profileIdx = E2E_INIT_0; profileIdx < Config->WindowSize; profileIdx++ )
    {
        /* [SWS_E2E_00466] */ /* E2E_check is ok state. */
        if( (uint8)E2E_P_OK == State->ProfileStatusWindow[profileIdx] )
        {
            /* [SWS_E2E_00466] */ /* cumulation of E2E_check ok state. */
            State->OkCount++;
        }
        /* [SWS_E2E_00466] */ /* E2E_check is error state. */
        else if( (uint8)E2E_P_ERROR == State->ProfileStatusWindow[profileIdx] )
        {
            /* [SWS_E2E_00466] */ /* cumulation of E2E_check error state. */
            State->ErrorCount++;
        }
        else
        {
            /* do nothing */
        }
    }
    /* [SWS_E2E_00466] */
    /* Monitoring window index whether or not is Maximum value. */
    if( State->WindowTopIndex == (Config->WindowSize - E2E_NUMBER_1) )
    {
        /* [SWS_E2E_00466] */ /* WindowTopIndex polling from zero begin. */
        State->WindowTopIndex = E2E_INIT_0;
    }
    else /* [SWS_E2E_00466] */
    {
        /* [SWS_E2E_00466] */ /* WindowTopIndex increase. */
        State->WindowTopIndex++;
    }
}

/*
********************************************************************************
* Function Name: E2E_SMClearStatus
*
* Explanation: Checks the communication channel.(Synchronous)
*
* param: ConfigPtr: Pointer to static configuration.
*        StatePtr: Pointer to port/data communication state.
*
* retval: None
********************************************************************************
*/
/* [SWS_E2E_00467] */
static FUNC(void, E2E_CODE) E2E_SMClearStatus
(
    P2CONST(E2E_SMConfigType, AUTOMATIC, E2E_APPL_DATA) Config,
    P2VAR(E2E_SMCheckStateType, AUTOMATIC, E2E_APPL_DATA) State
)
{
    uint8 profileIdx = E2E_INIT_0;

    /* [SWS_E2E_00467] */
    for( profileIdx = E2E_INIT_0; profileIdx < Config->WindowSize; profileIdx++ )
    {
        /* [SWS_E2E_00467] */
        /* Clear each element of the ProfileStatusWindow[] array. */
        State->ProfileStatusWindow[profileIdx] = (uint8)E2E_P_NOTAVAILABLE;
    }
    /* [SWS_E2E_00467] */ /* clear okcounter parameter set is zero. */
    State->OkCount = E2E_INIT_0;
    /* [SWS_E2E_00467] */ /* clear errorcounter parameter set is zero. */
    State->ErrorCount = E2E_INIT_0;
    State->WindowTopIndex = E2E_INIT_0; /* [SWS_E2E_00467] */
}

/*
********************************************************************************
* Function Name: E2E_SMCheck
*
* Explanation: Checks the communication channel.(Synchronous)
*
* param: ProfileStatus: Profile-independent status of the reception
*                       on one single Data in one cycle.
*        ConfigPtr: Pointer to static configuration.
*        StatePtr: Pointer to port/data communication state.
*
* retval: Std_ReturnType
********************************************************************************
*/
/* [SWS_E2E_00340] [SWS_E2E_00354] */
FUNC(Std_ReturnType, E2E_CODE) E2E_SMCheck
(
    E2E_PCheckStatusType ProfileStatus,
    P2VAR(E2E_SMConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr,
    P2VAR(E2E_SMCheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr
)
{
    Std_ReturnType rtrnValu = E2E_E_INPUTERR_NULL; /* [SWS_E2E_00371] */

    /* [SWS_E2E_00371] */ /* Check pointer parameter. */
    rtrnValu = E2E_SMCheck_ChkParam(StatePtr, ConfigPtr);
    if( E2E_E_OK == rtrnValu )
    {
        /* [SWS_E2E_00345] */
        /* Status of the communication channel exchanging the data. */
        switch( StatePtr->SMState )
        {
            case E2E_SM_DEINIT: /* [SWS_E2E_00345] */
                rtrnValu = E2E_E_WRONGSTATE; /* [SWS_E2E_00345] */
                break;
            case E2E_SM_NODATA: /* [SWS_E2E_00345] */
                /* [SWS_E2E_00345] */
                if( (E2E_P_ERROR != ProfileStatus)
                    && (E2E_P_NONEWDATA != ProfileStatus) )
                {
                    /* [SWS_E2E_00345]  */
                    /* add status to the monitoring window
                       for the state machine. */
                    E2E_SMAddStatus(ProfileStatus, ConfigPtr, StatePtr);
                    /* [SWS_E2E_00345] */ /* set state machine state. */
                    StatePtr->SMState = E2E_SM_INIT;
                }
                break;
            case E2E_SM_INIT: /* [SWS_E2E_00345] */
                /* [SWS_E2E_00345] */
                /* add status to the monitoring window for the state machine. */
                E2E_SMAddStatus(ProfileStatus, ConfigPtr, StatePtr);
                /* [SWS_E2E_00345] */
                /* state of OK and state of error in config limit. */
                if( (StatePtr->ErrorCount <= ConfigPtr->MaxErrorStateInit) &&
                    (StatePtr->OkCount >= ConfigPtr->MinOkStateInit) )
                {
                    /* [SWS_E2E_00345] */ /* set state machine state. */
                    StatePtr->SMState = E2E_SM_VALID;
                }
                /* [SWS_E2E_00345] */ /* state of error in config limit. */
                else if( StatePtr->ErrorCount > ConfigPtr->MaxErrorStateInit )
                {
                    /* [SWS_E2E_00345] */ /* set state machine state. */
                    StatePtr->SMState = E2E_SM_INVALID;
                }
                else
                {
                    /* do nothing */
                }
                break;
            case E2E_SM_VALID: /* [SWS_E2E_00345] */
                /* [SWS_E2E_00345] */
                /* add status to the monitoring window for the state machine. */
                E2E_SMAddStatus(ProfileStatus, ConfigPtr, StatePtr);
                /* [SWS_E2E_00345] */
                /* state of OK and state of error in config limit. */
                if( (StatePtr->ErrorCount <= ConfigPtr->MaxErrorStateValid) &&
                    (StatePtr->OkCount >= ConfigPtr->MinOkStateValid) )
                {
                    /* [SWS_E2E_00345] */ /* set state machine state. */
                    StatePtr->SMState = E2E_SM_VALID;
                }
                else
                {
                    /* [SWS_E2E_00345] */ /* set state machine state. */
                    StatePtr->SMState = E2E_SM_INVALID;
                }
                break;
            case E2E_SM_INVALID: /* [SWS_E2E_00345] */
                /* [SWS_E2E_00345] */
                /* add status to the monitoring window for the state machine. */
                E2E_SMAddStatus(ProfileStatus, ConfigPtr, StatePtr);
                /* [SWS_E2E_00345] */
                /* state of OK and state of error in config limit. */
                if( (StatePtr->ErrorCount <= ConfigPtr->MaxErrorStateInvalid) &&
                    (StatePtr->OkCount >= ConfigPtr->MinOkStateInvalid) )
                {
                    /* [SWS_E2E_00345] */ /* set state machine state. */
                    StatePtr->SMState = E2E_SM_VALID;
                }
                else
                {
                    /* [SWS_E2E_00345] */ /* set state machine state. */
                    StatePtr->SMState = E2E_SM_INVALID;
                }
                break;
            default:
                rtrnValu = E2E_E_INTERR;
                break;
        }
    }

    return rtrnValu; /* [SWS_E2E_00371] */
}

/*
********************************************************************************
* Function Name: E2E_SMCheckInit
*
* Explanation: Initializes the state machine.(Synchronous)
*
* param: ConfigPtr: Pointer to configuration of the state machine.
*        StatePtr: Pointer to port/data communication state.
*
* retval: Std_ReturnType
********************************************************************************
*/
/* [SWS_E2E_00353] [SWS_E2E_00354] */
FUNC(Std_ReturnType, E2E_CODE) E2E_SMCheckInit
(
    P2VAR(E2E_SMCheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
    P2VAR(E2E_SMConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr
)
{
    Std_ReturnType rtrnValu = E2E_E_INPUTERR_NULL; /* [SWS_E2E_00370] */

    /* [SWS_E2E_00370] */ /* Check parameter. */
    rtrnValu = E2E_SMCheck_ChkParam(StatePtr, ConfigPtr);
    if( E2E_E_OK == rtrnValu ) /* [SWS_E2E_00370] */
    {
        /* [SWS_E2E_00370] */
        /* clear State of the protection of a communication channel. */
        E2E_SMClearStatus(ConfigPtr, StatePtr);
        StatePtr->SMState = E2E_SM_NODATA; /* [SWS_E2E_00370] */
    }

    return rtrnValu; /* [SWS_E2E_00370] */
}

#define E2E_STOP_SEC_CODE
#include "E2E_MemMap.h"
