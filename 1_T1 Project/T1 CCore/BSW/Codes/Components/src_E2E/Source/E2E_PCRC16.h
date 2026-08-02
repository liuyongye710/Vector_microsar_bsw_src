/*
********************************************************************************
*
* File name: E2E_PCRC16.h
*
* Copyright 2022-2024 Neusoft Reach Corporation.All rights reserved.
*
********************************************************************************
*
* History
*-------------------------------------------------------------------------------
********************************************************************************
* Version: 3.0
* Author/Date: XieYN/2022.09.09
* Change: New Created.
* Cause: New
********************************************************************************
* Version: 3.1
* Author/Date: XieYN/2022.10.31
* Change: Increase the configurable range of counter: 4, 8, 16.
* Cause: Update
********************************************************************************
* Version: 3.2
* Author/Date: XieYN/2022.12.02
* Change: Modify element order in E2E_PCRC16CheckStateType.
* Cause: Bugfix
********************************************************************************
* Version: 3.3
* Author/Date: LiDaY/2024.02.05
* Change: Modifying the label of the input parameter Ptrclass for E2E function
*         and addressing some code inconsistencies.
* Cause: Optimization
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
#ifndef E2E_PCRC16_H_
#define E2E_PCRC16_H_

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
/* Counter max value. */
#define E2E_PCRC16PROTECT_COUNTERMAX_4        (15U)
#define E2E_PCRC16PROTECT_COUNTERMOD_4        (16U)
#define E2E_PCRC16PROTECT_COUNTERMAX_8        (255U)
#define E2E_PCRC16PROTECT_COUNTERMOD_8        (256U)
#define E2E_PCRC16PROTECT_COUNTERMAX_16       (65535U)
#define E2E_PCRC16PROTECT_COUNTERMOD_16       (65536U)

/* CounterSize */
#define E2E_PCRC16_COUNTERSIZE_0              (0U)
#define E2E_PCRC16_COUNTERSIZE_4              (4U)
#define E2E_PCRC16_COUNTERSIZE_8              (8U)
#define E2E_PCRC16_COUNTERSIZE_16             (16U)

/*
********************************************************************************
*    Global Types
********************************************************************************
*/
/* Status of the reception on one single Data in one cycle, protected
   with E2E Profile CRC16. */
typedef enum
{
    E2E_PCRC16STATUS_OK = 0x00U,               /* OK: the checks of the Data in
                                               this cycle were successful. */
    E2E_PCRC16STATUS_NONEWDATA = 0x01U,        /* Error: the Check function has
                                               been invoked but no new Data
                                               is not available since the
                                               last call. */
    E2E_PCRC16STATUS_ERROR= 0x07U,             /* Error: error not related to
                                               counters occurred. */
    E2E_PCRC16STATUS_REPEATED = 0x08U,         /* Error: the checks of the Data
                                               in this cycle were successful,
                                               with the exception of the
                                               repetition. */
    E2E_PCRC16STATUS_OKSOMELOST = 0x20U,       /* OK: the checks of the Data in
                                               this cycle were successful. */
    E2E_PCRC16STATUS_WRONGSEQUENCE = 0x40U,    /* Error: the checks of the Data
                                               in this cycle were successful,
                                               with the exception of counter
                                               jump, which changed more than
                                               the allowed delta. */
} E2E_PCRC16CheckStatusType;

/* Configuration of transmitted Data (Data Element or I-PDU), for E2E Profile CRC16.
   For each transmitted Data, there is an instance of this typedef. */
typedef struct
{
    uint16 CounterOffset;   /* Bit offset of Counter. */
    uint16 CRCOffset;       /* Bit offset of CRC. */
    uint8 CounterSize;      /* CounterSize. */
    E2EPW_EndianessType CounterEndianess;   /* CounterEndianess. */
    E2EPW_EndianessType CRCEndianess;       /* CounterEndianess. */
    uint16 DataLength;      /* Length of data, in bits. */
    uint16 MaxDeltaCounter;  /* Maximum allowed gap between two counter values
                               of two consecutively received valid Data. */
} E2E_PCRC16ConfigType;

/* State of the sender for a Data protected with E2E Profile CRC16. */
typedef struct
{
    uint16 Counter; /* Counter to be used for protecting the next Data. */
} E2E_PCRC16ProtectStateType;

/* State of the reception on one single Data protected with E2E Profile CRC16. */
typedef struct
{
    uint16 Counter;          /* Counter of the data in previous cycle. */
	E2E_PCRC16CheckStatusType Status;  /* Result of the verification of the Data
                                          in this cycle, determined by the Check
                                          function. */
} E2E_PCRC16CheckStateType;

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

extern FUNC(Std_ReturnType, E2E_CODE) E2E_PCRC16Protect
(
    P2CONST(E2E_PCRC16ConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr,
    P2VAR(E2E_PCRC16ProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
    P2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr
);
extern FUNC(Std_ReturnType, E2E_CODE) E2E_PCRC16ProtectInit
(
    P2VAR(E2E_PCRC16ProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr
);
extern FUNC(Std_ReturnType, E2E_CODE) E2E_PCRC16Check
(
    P2CONST(E2E_PCRC16ConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr,
    P2VAR(E2E_PCRC16CheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
    P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr
);
extern FUNC(Std_ReturnType, E2E_CODE) E2E_PCRC16CheckInit
(
    P2VAR(E2E_PCRC16CheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr
);
extern FUNC(E2E_PCheckStatusType, E2E_CODE) E2E_PCRC16MapStatusToSM
(
    Std_ReturnType CheckReturn,
    E2E_PCRC16CheckStatusType Status
);

#define E2E_STOP_SEC_CODE
#include "E2E_MemMap.h"

#endif /* E2E_PCRC16_H_ */
