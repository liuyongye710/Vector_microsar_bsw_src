/*
********************************************************************************
*
* File name: E2E_PCRC8H2F.h
*
* Copyright 2022-2024 Neusoft Reach Corporation.All rights reserved.
*
********************************************************************************
*
* History
*-------------------------------------------------------------------------------
********************************************************************************
* Version: 3.0
* Author/Date: XieYN/2022.10.24
* Change: New Created.
* Cause: New
********************************************************************************
* Version: 3.1
* Author/Date: XieYN/2023.01.10
* Change: 1. Delete unused state in E2E_PCRC8H2FCheckStatusType and
*            E2E_PCRC8H2FCheckStateType.
*         2. Delete unused configured information in E2E_PCRC8H2FConfigType.
* Cause: Bugfix
********************************************************************************
* Version: 3.2
* Author/Date: LiDaY/2024.02.05
* Change: Modifying the label of the input parameter Ptrclass for E2E function
*         and addressing some code inconsistencies.
* Cause: Optimization
********************************************************************************
* Version: 3.3
* Author/Date: LiDaY/2024.03.18
* Change: Modifying the label of the input parameter Ptrclass for E2E function
*         and addressing some code inconsistencies.
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
#ifndef E2E_PCRC8H2F_H_
#define E2E_PCRC8H2F_H_

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
#define E2E_PCRC8H2FPROTECT_COUNTERMAX_4        (15U)
#define E2E_PCRC8H2FPROTECT_COUNTERMOD_4        (16U)
#define E2E_PCRC8H2FPROTECT_COUNTERMAX_8        (255U)
#define E2E_PCRC8H2FPROTECT_COUNTERMOD_8        (256U)
#define E2E_PCRC8H2FPROTECT_COUNTERMAX_16       (65535U)
#define E2E_PCRC8H2FPROTECT_COUNTERMOD_16       (65536U)

/* CounterSize */
#define E2E_PCRC8H2F_COUNTERSIZE_0              (0U)
#define E2E_PCRC8H2F_COUNTERSIZE_4              (4U)
#define E2E_PCRC8H2F_COUNTERSIZE_8              (8U)
#define E2E_PCRC8H2F_COUNTERSIZE_16             (16U)

/*
********************************************************************************
*    Global Types
********************************************************************************
*/
/* Status of the reception on one single Data in one cycle, protected
   with E2E Profile CRC8H2F. */
typedef enum
{
    E2E_PCRC8H2FSTATUS_OK = 0x00U,            /* OK. */
    E2E_PCRC8H2FSTATUS_NONEWDATA = 0x01U,     /* Error: no new Data is not available. */
    E2E_PCRC8H2FSTATUS_WRONGCRC = 0x02U,      /* Error: the CRC is incorrect or the low
                                                 nibble of the high byte of Data ID is
                                                 incorrect. */
    E2E_PCRC8H2FSTATUS_INITIAL = 0x04U,       /* Initial: the CRC is correct, the first
                                                 Data since the receiver's
                                                 initialization or reinitialization. */
    E2E_PCRC8H2FSTATUS_REPEATED = 0x08U,      /* Error: the CRC is correct, but the
                                                 Counter is identical to the most recent
                                                 Data received with Status _INITIAL, _OK,
                                                 or _OKSOMELOST. */
    E2E_PCRC8H2FSTATUS_OKSOMELOST = 0x20U,    /* OK. */
    E2E_PCRC8H2FSTATUS_WRONGSEQUENCE = 0x40U, /* Error: the CRCis correct, but the
                                                 Counter Delta is too big. */
} E2E_PCRC8H2FCheckStatusType;


/* Configuration of transmitted Data (Data Element or I-PDU), for E2E Profile CRC8H2F.
   For each transmitted Data, there is an instance of this typedef. */
typedef struct
{
    uint16 CounterOffset;                     /* Bit offset of Counter. */
    uint16 CRCOffset;                         /* Bit offset of CRC. */
    uint8 CounterSize;                        /* CounterSize. */
    E2EPW_EndianessType CounterEndianess;     /* CounterEndianess. */
    uint16 DataLength;                        /* Length of data, in bits. */
    uint16 MaxDeltaCounter;                   /* Maximum allowed gap between two counter
                                                 values of two consecutively received
                                                 valid Data. */
} E2E_PCRC8H2FConfigType;

/* State of the sender for a Data protected with E2E Profile CRC8H2F. */
typedef struct
{
    uint16 Counter; /* Counter to be used for protecting the next Data. */
} E2E_PCRC8H2FProtectStateType;

/* State of the reception on one single Data protected with E2E Profile CRC8H2F. */
typedef struct
{
    uint16 LastValidCounter;                  /* Counter of last valid received
                                                 message. */
    boolean NewDataAvailable;                 /* Indicates to E2E Library that a new
                                                 data is available for Library to be
                                                 checked. */
    E2E_PCRC8H2FCheckStatusType Status;       /* Result of the verification of the
                                                 Data, determined by the Check
                                                 function. */
} E2E_PCRC8H2FCheckStateType;


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

extern FUNC(uint16, E2E_CODE) E2E_PCRC8H2F_ReadCounter
(
    P2CONST(E2E_PCRC8H2FConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr,
    P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr
);
extern FUNC(Std_ReturnType, E2E_CODE) E2E_PCRC8H2FProtect
(
    P2CONST(E2E_PCRC8H2FConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr,
    P2VAR(E2E_PCRC8H2FProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
    P2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr
);
extern FUNC(Std_ReturnType, E2E_CODE) E2E_PCRC8H2FProtectInit
(
    P2VAR(E2E_PCRC8H2FProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr
);
extern FUNC(Std_ReturnType, E2E_CODE) E2E_PCRC8H2FCheck
(
    P2CONST(E2E_PCRC8H2FConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr,
    P2VAR(E2E_PCRC8H2FCheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
    P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr
);
extern FUNC(Std_ReturnType, E2E_CODE) E2E_PCRC8H2FCheckInit
(
    P2VAR(E2E_PCRC8H2FCheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr
);
extern FUNC(E2E_PCheckStatusType, E2E_CODE) E2E_PCRC8H2FMapStatusToSM
(
    Std_ReturnType CheckReturn,
    E2E_PCRC8H2FCheckStatusType Status
);

#define E2E_STOP_SEC_CODE
#include "E2E_MemMap.h"

#endif /* E2E_PCRC8H2F_H_ */
