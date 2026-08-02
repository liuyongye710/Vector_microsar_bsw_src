/*
********************************************************************************
*
* File name: E2E_P04.h
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
* Author/Date : BaoWL/2021.03.25
* Change: E2E_P04Check function. Modify the DataPtr parameter type to const uint8*.
* Cause: Bugfix
********************************************************************************
* Version: 3.4
* Author/Date: LiDaY/2024.03.18
* Change: Modifying the label of the input parameter Ptrclass for E2E function
*         and addressing some code inconsistencies.
* Cause: Optimization
********************************************************************************
* Version: 3.5
* Author/Date: LiDaY/2024.04.25
* Change: Add a memory-map label to function and variable declarations.
* Cause: Bugfix
********************************************************************************
* Version: 3.6
* Author/Date: LiDaY/2024.08.08
* Change: Change copyright information.
* Cause: Update
********************************************************************************
*/
#ifndef E2E_P04_H_
#define E2E_P04_H_

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
/* Counter max value(0..65535). */
#define E2E_P04PROTECT_COUNTERMAX (0xFFFFU)

/*
********************************************************************************
*    Global Types
********************************************************************************
*/
/* Status of the reception on one single Data in one cycle, protected
   with E2E Profile 4. */
typedef enum /* [SWS_E2E_00337] */
{
    E2E_P04STATUS_OK = 0x00U,               /* OK: the checks of the Data in
                                               this cycle were successful. */
    E2E_P04STATUS_NONEWDATA = 0x01U,        /* Error: the Check function has
                                               been invoked but no new Data
                                               is not available since the
                                               last call, according to
                                               communication medium. */
    E2E_P04STATUS_ERROR = 0x02U,            /* Error: error not related to
                                               counters occurred. */
    E2E_P04STATUS_REPEATED = 0x08U,         /* Error: the checks of the Data
                                               in this cycle were successful,
                                               with the exception of the
                                               repetition. */
    E2E_P04STATUS_OKSOMELOST= 0x20U,        /* OK: the checks of the Data in
                                               this cycle were successful. */
    E2E_P04STATUS_WRONGSEQUENCE = 0x40U,    /* Error: the checks of the Data
                                               in this cycle were successful,
                                               with the exception of counter
                                               jump, which changed more than
                                               the allowed delta. */
} E2E_P04CheckStatusType;

/* Configuration of transmitted Data (Data Element or I-PDU), for E2E Profile 4.
   For each transmitted Data, there is an instance of this typedef. */
typedef struct /* [SWS_E2E_00334] */
{
    uint32 DataID;          /* A system-unique identifier of the Data. */
    uint16 Offset;          /* Bit offset of the first bit of the E2E header
                               from the beginning of the Data Array. */
    uint16 MinDataLength;   /* Minimal length of Data array, in bits. */
    uint16 MaxDataLength;   /* Maximal length of Data, in bits. */
    uint16 MaxDeltaCounter; /* Maximum allowed gap between two counter values
                               of two consecutively received valid Data. */
} E2E_P04ConfigType;

/* State of the sender for a Data protected with E2E Profile 4. */
typedef struct /* [SWS_E2E_00335] */
{
    uint16 Counter;     /* Counter to be used for protecting the next Data. */
} E2E_P04ProtectStateType;

/* State of the reception on one single Data protected with E2E Profile 4. */
typedef struct /* [SWS_E2E_00336] */
{
    E2E_P04CheckStatusType Status;  /* Result of the verification of the Data
                                       in this cycle, determined by the Check
                                       function. */
    uint16 Counter;                 /* Counter of the data in previous cycle. */
} E2E_P04CheckStateType;

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

extern FUNC(Std_ReturnType, E2E_CODE) E2E_P04Protect
(
    P2VAR(E2E_P04ConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr,
    P2VAR(E2E_P04ProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
    P2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr,
    uint16 Length
);
extern FUNC(Std_ReturnType, E2E_CODE) E2E_P04ProtectInit
(
    P2VAR(E2E_P04ProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr
);
extern FUNC(Std_ReturnType, E2E_CODE) E2E_P04Check
(
    P2VAR(E2E_P04ConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr,
    P2VAR(E2E_P04CheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
    P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr,
    uint16 Length
);
extern FUNC(Std_ReturnType, E2E_CODE) E2E_P04CheckInit
(
    P2VAR(E2E_P04CheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr
);
extern FUNC(E2E_PCheckStatusType, E2E_CODE) E2E_P04MapStatusToSM
(
    Std_ReturnType CheckReturn,
    E2E_P04CheckStatusType Status
);

#define E2E_STOP_SEC_CODE
#include "E2E_MemMap.h"

#endif /* E2E_P04_H_ */
