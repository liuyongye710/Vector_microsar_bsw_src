/*
********************************************************************************
*
* File name: E2E_SM.h
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
* Version: 2.0
* Author/Date: WangHe/2019.11.22
* Change: Format modification.
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
* Author/Date : TanJY/2020.11.03
* Change: Modify code format.
* Cause: Optimization
********************************************************************************
* Version: 3.3
* Author/Date: XieYN/2021.08.13
* Change:Modify code specifications.
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
#ifndef E2E_SM_H_
#define E2E_SM_H_

/*
********************************************************************************
*    Includes
********************************************************************************
*/
#include "Std_Types.h"
#include "E2E.h"

/*
********************************************************************************
*    Global Macros
********************************************************************************
*/
/*
********************************************************************************
*    Global Types
********************************************************************************
*/
/* Profile-independent status of the reception on one single Data
   in one cycle. */
typedef enum /* [SWS_E2E_00347] */
{
    E2E_P_OK = 0x00U,               /* OK: the checks of the Data in this cycle
                                       were successful. */
    E2E_P_REPEATED = 0x01U,         /* Data has a repeated counter. */
    E2E_P_WRONGSEQUENCE = 0x02U,    /* The checks of the Data in this cycle were
                                       successful, with the exception of counter
                                       jump, which changed more than the allowed
                                       delta. */
    E2E_P_ERROR = 0x03U,            /* Error not related to counters occurred or
                                       the return of the check function was not
                                       OK. */
    E2E_P_NOTAVAILABLE= 0x04U,      /* No value has been received yet. */
    E2E_P_NONEWDATA = 0x05U,        /* No new data is available. */
                                    /* 0x07-0x0F reserved. */
} E2E_PCheckStatusType;

/* Status of the communication channel exchanging the data. If the status is OK,
   then the data may be used. */
typedef enum /* [SWS_E2E_00344] */
{
    E2E_SM_VALID = 0x00U,   /* Communication functioning properly according to
                               E2E, data can be used. */
    E2E_SM_DEINIT = 0x01U,  /* State before E2E_SMCheckInit() is invoked,
                               data cannot be used. */
    E2E_SM_NODATA = 0x02U,  /* No data from the sender is available since the
                               initialization, data cannot be used. */
    E2E_SM_INIT = 0x03U,    /* There has been some data received since startup,
                               but it is not yet possible use it, data cannot
                               be used. */
    E2E_SM_INVALID = 0x04U, /* Communication not functioning properly, data
                               cannot be used. */
                            /* 0x07..0x0F,reserved for runtime errors. */
} E2E_SMStateType;

/* Configuration of a communication channel for exchanging Data. */
typedef struct /* [SWS_E2E_00342] */
{
    uint8 WindowSize;           /* Size of the monitoring window for the state
                                   machine. */
    uint8 MinOkStateInit;       /* Minimal number of checks in which
                                   ProfileStatus equal to E2E_P_OK was
                                   determined within the last WindowSize
                                   checks required to change to state
                                   E2E_SM_VALID. */
    uint8 MaxErrorStateInit;    /* Maximal number of checks in which
                                   ProfileStatus equal to E2E_P_ERROR was
                                   determined, within the last WindowSize
                                   checks. */
    uint8 MinOkStateValid;      /* Minimal number of checks in which
                                   ProfileStatus equal to E2E_P_OK was
                                   determined within the last WindowSize
                                   checks required to keep in state
                                   E2E_SM_VALID. */
    uint8 MaxErrorStateValid;   /* Maximal number of checks in which
                                   ProfileStatus equal to E2E_P_ERROR was
                                   determined, within the last WindowSize
                                   checks. */
    uint8 MinOkStateInvalid;    /* Minimum number of checks in which
                                   ProfileStatus equal to E2E_P_OK was
                                   determined within the last WindowSize
                                   checks required to change to state
                                   E2E_SM_VALID. */
    uint8 MaxErrorStateInvalid; /* Maximal number of checks in which
                                   ProfileStatus equal to E2E_P_ERROR was
                                   determined, within the last WindowSize
                                   checks. */
} E2E_SMConfigType;

/* State of the protection of a communication channel. */
typedef struct /* [SWS_E2E_00343] */
{
    uint8* ProfileStatusWindow; /* Pointer to an array, in which the
                                   ProfileStatus-es of the last E2Echecks
                                   are stored. */
    uint8 WindowTopIndex;       /* Index in the array, at which the next
                                   ProfileStatus is to be written. */
    uint8 OkCount;              /* Count of checks in which ProfileStatus
                                   equal to E2E_P_OK was determined, within
                                   the last WindowSize checks. */
    uint8 ErrorCount;           /* Count of checks in which ProfileStatus
                                   equal to E2E_P_ERROR was determined. */
    E2E_SMStateType SMState;    /* The current state in the state machine. */
} E2E_SMCheckStateType;

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
/*
********************************************************************************
*    Global Functions
********************************************************************************
*/
#define E2E_START_SEC_CODE
#include "E2E_MemMap.h"

extern FUNC(Std_ReturnType, E2E_CODE) E2E_SMCheck
(
    E2E_PCheckStatusType ProfileStatus,
    P2VAR(E2E_SMConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr,
    P2VAR(E2E_SMCheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr
);
extern FUNC(Std_ReturnType, E2E_CODE) E2E_SMCheckInit
(
    P2VAR(E2E_SMCheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
    P2VAR(E2E_SMConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr
);

#define E2E_STOP_SEC_CODE
#include "E2E_MemMap.h"

#endif /* E2E_SM_H_ */
