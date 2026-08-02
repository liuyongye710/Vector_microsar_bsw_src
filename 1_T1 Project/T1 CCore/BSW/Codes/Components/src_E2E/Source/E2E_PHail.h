/*
********************************************************************************
*
* File name: E2E_PHail.h
*
* Copyright 2022-2024 Neusoft Reach Corporation.All rights reserved.
*
********************************************************************************
*
* History
*-------------------------------------------------------------------------------
********************************************************************************
* Version: 1.0
* Author/Date: XieYN/2022.06.29
* Change: New created.
* Cause: New
********************************************************************************
* Version: 1.1
* Author/Date: LiDaY/2024.02.05
* Change: Modifying the label of the input parameter Ptrclass for E2E function
*         and addressing some code inconsistencies.
* Cause: Optimization
********************************************************************************
* Version: 1.2
* Author/Date: LiDaY/2024.03.18
* Change: Modifying the label of the input parameter Ptrclass for E2E function
*         and addressing some code inconsistencies.
* Cause: Optimization
********************************************************************************
* Version: 1.3
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
#ifndef E2E_PHail_H_
#define E2E_PHail_H_

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
/* Counter max value(1..15). */
#define E2E_PHAILPROTECT_COUNTERMAX  (15U) /* [SWS_E2E_00218] */
#define E2E_PHAILPROTECT_COUNTERMOD  (15U)

/* DataID length */
#define E2E_DATAID_2BYTES   (2U)
#define E2E_DATAID_1BYTE    (1U)

/*
********************************************************************************
*    Global Types
********************************************************************************
*/

/* Configuration of transmitted Data (Data Element or I-PDU), for E2E Profile 1.
   For each transmitted Data, there is an instance of this typedef. */
typedef struct
{
    uint16 CounterOffset;          /* Bit offset of Counter. */
    uint16 CRCOffset;              /* Bit offset of CRC. */
    uint16 DataLength;             /* Length of data, in bits. */
    uint8 MaxDeltaCounterInit;     /* Initial maximum allowed gap between two
                                      counter values of two consecutively
                                      receivedvalid Data. */
    uint8 MaxNoNewOrRepeatedData;  /* The maximum amount of missing or repeated
                                      Data. */
    uint8 SyncCounerInit;         /* Number of Data required for validating
                                      the consistency of the counter that must
                                      be received with a valid counter after
                                      the detection of an unexpected behavior
                                      of a received counter. */
} E2E_PHailConfigType;

/* State of the sender for a Data protected with E2E Profile 1. */
typedef struct
{
    uint8 Counter;                  /* Counter to be used for protecting the
                                       next Data. */
} E2E_PHailProtectStateType;

/* Result of the verification of the Data in E2E Profile 1, determined by the
   Check function. */
typedef enum /* [SWS_E2E_00022] */
{
    E2E_PHAILSTATUS_OK = 0x00U,          /* OK */
    E2E_PHAILSTATUS_NONEWDATA = 0x01U,        /* Error: no new Data is not available. */
    E2E_PHAILSTATUS_WRONGCRC = 0x02U,         /* Error: the CRC is incorrect or the low
                                       nibble of the high byte of Data ID is
                                       incorrect. */
    E2E_PHAILSTATUS_SYNC = 0x03U,             /* NOT VALID: The new data has been
                                       received after detection of an
                                       unexpected behavior of counter. */
    E2E_PHAILSTATUS_INITIAL = 0x04U,          /* Initial: the CRC is correct, the
                                       first Data since the receiver's
                                       initialization or reinitialization. */
    E2E_PHAILSTATUS_REPEATED = 0x08U,         /* Error: the CRC is correct, but the
                                       Counter is identical to the most
                                       recent Data received with Status
                                       _INITIAL, _OK, or _OKSOMELOST. */
    E2E_PHAILSTATUS_OKSOMELOST = 0x20U,       /* OK */
    E2E_PHAILSTATUS_WRONGSEQUENCE = 0x40U,    /* Error: the CRCis correct, but the
                                       Counter Delta is too big. */
} E2E_PHailCheckStatusType;

/* State of the receiver for a Data protected with E2E Profile 1. */
typedef struct /* [SWS_E2E_00021] */
{
    uint8 LastValidCounter;             /* Counter value most recently
                                           received. */
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
    E2E_PHailCheckStatusType Status;      /* Result of the verification of the
                                           Data, determined by the Check
                                           function. */
    uint8 SyncCounter;                  /* Number of Data required for
                                           validating the consistency of
                                           the counter. */
    uint8 NoNewOrRepeatedDataCounter;   /* Amount of consecutive reception
                                           cycles in which either (1) there
                                           was no new data, or (2) when the
                                           data was repeated. */
} E2E_PHailCheckStateType;

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

extern FUNC(Std_ReturnType, E2E_CODE) E2E_PHailProtect
(
    P2CONST(E2E_PHailConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr,
    P2VAR(E2E_PHailProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
    P2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr
);
extern FUNC(Std_ReturnType, E2E_CODE) E2E_PHailProtectInit
(
    P2VAR(E2E_PHailProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr
);
extern FUNC(Std_ReturnType, E2E_CODE) E2E_PHailCheck
(
    P2CONST(E2E_PHailConfigType, AUTOMATIC, E2E_APPL_DATA) Config,
    P2VAR(E2E_PHailCheckStateType, AUTOMATIC, E2E_APPL_DATA) State,
    P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) Data
);
extern FUNC(Std_ReturnType, E2E_CODE) E2E_PHailCheckInit
(
    P2VAR(E2E_PHailCheckStateType, AUTOMATIC, E2E_APPL_DATA) State
);
extern FUNC(E2E_PCheckStatusType, E2E_CODE) E2E_PHailMapStatusToSM
(
    Std_ReturnType CheckReturn,
    E2E_PHailCheckStatusType Status,
    boolean profileBehavior
);

#define E2E_STOP_SEC_CODE
#include "E2E_MemMap.h"

#endif /* E2E_PHail_H_ */
