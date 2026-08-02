/*
********************************************************************************
*
* File name: E2E_P02.h
*
* Copyright 2019-2024 Neusoft Reach Corporation.All rights reserved.
*
********************************************************************************
*
* History
*-------------------------------------------------------------------------------
********************************************************************************
* Version: 1.0
* Author/Date : WangJipeng/2019.04.20
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
* Author/Date : BaoWL/2021.03.25
* Change: E2E_P02Check function. Modify the DataPtr parameter type to const uint8*.
* Cause: Bugfix
********************************************************************************
* Version: 3.4
* Author/Date : BaoWL/2021.05.14
* Change: E2E_P01CheckStatusType. Modify the type definition according to AUTOSAR 4.4.
* Cause: Bugfix
********************************************************************************
* Version: 3.5
* Author/Date: XieYN/2021.08.13
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
*/
#ifndef E2E_P02_H_
#define E2E_P02_H_

/*
********************************************************************************
*    Includes
********************************************************************************
*/
#include "E2E.h"

/*
********************************************************************************
*    Global Macros
********************************************************************************
*/
/* Counter max value(0..15). */
#define E2E_P02PROTECT_COUNTERMAX   (15U)
#define E2E_P02PROTECT_COUNTERMod   (16U)

/*
********************************************************************************
*    Global Types
********************************************************************************
*/

/* Result of the verification of the Data in E2E Profile 2, determined by
   the Check function. */
typedef enum /* [SWS_E2E_00214] */
{
    E2E_P02STATUS_OK = 0x00U,          /* OK. */
    E2E_P02STATUS_NONEWDATA = 0x01U,        /* Error: no new Data is not available. */
    E2E_P02STATUS_WRONGCRC = 0x02U,         /* Error: the CRC is incorrect or the low
                                       nibble of the high byte of Data ID is
                                       incorrect. */
    E2E_P02STATUS_SYNC = 0x03U,             /* NOT VALID: The new data has been
                                       received after detection of an
                                       unexpected behavior of counter. */
    E2E_P02STATUS_INITIAL = 0x04U,          /* Initial: the CRC is correct, the first
                                       Data since the receiver's initialization
                                       or reinitialization. */
    E2E_P02STATUS_REPEATED = 0x08U,         /* Error: the CRC is correct, but the
                                       Counter is identical to the most recent
                                       Data received with Status _INITIAL, _OK,
                                       or _OKSOMELOST. */
    E2E_P02STATUS_OKSOMELOST = 0x20U,       /* OK. */
    E2E_P02STATUS_WRONGSEQUENCE = 0x40U,    /* Error: the CRCis correct, but the
                                       Counter Delta is too big. */
} E2E_P02CheckStatusType;

/* State of the sender for a Data protected with E2E Profile 2. */
typedef struct /* [SWS_E2E_00154] */
{
    uint8 LastValidCounter;             /* Counter of last valid received
                                           message. */
    uint8 MaxDeltaCounter;              /* MaxDeltaCounter specifies the
                                           maximum allowed difference between
                                           two counter values of consecutively
                                           received valid messages. */
    boolean WaitForFirstData;           /* If true means that no correct data
                                           has been yet received after the
                                           receiver initialization or
                                           reinitialization. */
    boolean NewDataAvailable;           /* Indicates to E2E Library that a new
                                           data is available for Library to be
                                           checked. */
    uint8 LostData;                     /* Number of data (messages) lost since
                                           reception of last valid one. */
    E2E_P02CheckStatusType Status;      /* Result of the verification of the
                                           Data, determined by the Check
                                           function. */
    uint8 SyncCounter;                  /* Number of Data required for
                                           validating the consistency of the
                                           counter that must be received with
                                           a valid counter. */
    uint8 NoNewOrRepeatedDataCounter;   /* Amount of consecutive reception
                                           cycles in which either (1) there was
                                           no new  data, or (2) when the data
                                           was repeated. */
} E2E_P02CheckStateType;

/* Non-modifiable configuration of the data element sent over an RTE port,
   for E2E profile 2. */
typedef struct /* [SWS_E2E_00152] */
{
    uint16 DataLength;              /* Length of Data, in bits. The value shall
                                       be a multiple of 8. */
    uint8 DataIDList[16];           /* An array of appropriately chosen Data
                                       IDs for protection against
                                       masquerading. */
    uint8 MaxDeltaCounterInit;      /* Initial maximum allowed gap between two
                                       counter values of two consecutively
                                       received valid Data. */
    uint8 MaxNoNewOrRepeatedData;   /* The maximum amount of missing or repeated
                                       Data which the receiver does not expect
                                       to exceed under normal communication
                                       conditions. */
    uint8 SyncCounterInit;          /* Number of Data required for validating
                                       the consistency of the counter that must
                                       be received with a valid counter. */
    uint16 Offset;                  /* Offset of the E2E header in the Data[]
                                       array in bits. */
} E2E_P02ConfigType;

/* State of the sender for a Data protected with E2E Profile 2. */
typedef struct /* [SWS_E2E_00153] */
{
    uint8 Counter;                  /* Counter to be used for protecting
                                       the Data. */
} E2E_P02ProtectStateType;

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

extern FUNC(Std_ReturnType, E2E_CODE) E2E_P02Protect
(
    P2VAR(E2E_P02ConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr,
    P2VAR(E2E_P02ProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
    P2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr
);
extern FUNC(Std_ReturnType, E2E_CODE) E2E_P02ProtectInit
(
    P2VAR(E2E_P02ProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr
);
extern FUNC(Std_ReturnType, E2E_CODE) E2E_P02Check
(
    P2VAR(E2E_P02ConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr,
    P2VAR(E2E_P02CheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
    P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr
);
extern FUNC(Std_ReturnType, E2E_CODE) E2E_P02CheckInit
(
    P2VAR(E2E_P02CheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr
);
extern FUNC(E2E_PCheckStatusType, E2E_CODE) E2E_P02MapStatusToSM
(
    Std_ReturnType CheckReturn,
    E2E_P02CheckStatusType Status,
    boolean profileBehavior
);

#define E2E_STOP_SEC_CODE
#include "E2E_MemMap.h"

#endif /* E2E_P02_H_ */
