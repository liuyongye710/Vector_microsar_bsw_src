/*
********************************************************************************
*
* File name: E2E_Ph.h
*
* Copyright 2021-2024 Neusoft Reach Corporation.All rights reserved.
*
********************************************************************************
*
* History
*-------------------------------------------------------------------------------
********************************************************************************
* Version: 1.0
* Author/Date: XieYN/2021.11.03
* Change: New created.
* Cause: New
********************************************************************************
* Version: 1.1
* Author/Date: XieYN/2021.11.12
* Change: Add Ph DataID definations.
* Cause: Optimization
********************************************************************************
* Version: 1.2
* Author/Date: LiDaY/2024.02.05
* Change: Modifying the label of the input parameter Ptrclass for E2E function
*         and addressing some code inconsistencies.
* Cause: Optimization
********************************************************************************
* Version: 1.3
* Author/Date: LiDaY/2024.03.18
* Change: Modifying the label of the input parameter Ptrclass for E2E function
*         and addressing some code inconsistencies.
* Cause: Optimization
********************************************************************************
* Version: 1.4
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
#ifndef E2E_Ph_H_
#define E2E_Ph_H_

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
/* Counter max value(0..3) */
#define E2E_PHPROTECT_COUNTERMAX        (3U)
#define E2E_PHPROTECT_COUNTERMOD        (4U)

/* Byte deal with */
#define E2E_PH_HIGH2BITS_NIBBLE         (0x30U)
#define E2E_PH_LOW2BITS_NIBBLE          (0x03U)

/* Counter deal with */
#define E2E_PH_LOWNIBBLE                (0x0FU)
#define E2E_PH_RESERVEBIT               (0xC0U)

/* FrameType */
#define E2E_PH_STANDARDFRAME            (0U)
#define E2E_PH_EXTENDEDFRAME            (1U)

/* Ph DataID. */
#define E2E_PH_EXTENDED_OR              (0xE0000000U)
#define E2E_PH_STANDARD_OR              (0x0800U)

#define E2E_EXTENDED_DATAIDBITS         (32U)
#define E2E_STANDARD_DATAIDBITS         (12U)

/* DataID length */
#define E2E_PH_DATAID_8_NIBBYTES        (8U)
#define E2E_PH_DATAID_3_NIBBYTES        (3U)

/*
********************************************************************************
*    Global Types
********************************************************************************
*/
/* Configuration of transmitted Data (Data Element or I-PDU), for E2E Profile
   Ph. For each transmitted Data, there is an instance of this typedef. */
typedef struct
{
    uint16 CounterOffset;         /* Bit offset of Counter. */
    uint16 ChecksumOffset;        /* Bit offset of checksum. */
    uint8 FrameType;              /* FrameType. */
    uint32 DataID;                /* A unique identifier, for protection against
                                     masquerading. */
    uint16 DataLength;            /* Length of data, in bits. */
    uint8 MaxDeltaCounterInit;    /* Initial maximum allowed gap between two counter
                                     values of two consecutively receivedvalid Data. */
    uint8 MaxNoNewOrRepeatedData; /* The maximum amount of missing or repeated Data */
    uint8 SyncCounterInit;        /* Number of Data required for validating the
                                     consistency of the counter that must be received
                                     with a valid counter after the detection of
                                     an unexpected behavior of a received counter. */
} E2E_PhConfigType;

/* State of the sender for a Data protected with E2E Profile Ph. */
typedef struct
{
    /* Counter to be used for protecting the next Data. */
    uint8 Counter;
} E2E_PhProtectStateType;

/* Result of the verification of the Data in E2E Profile Ph, determined by
   the Check function. */
typedef enum
{
    E2E_PHSTATUS_OK = 0U,       /* OK. */
    E2E_PHSTATUS_NONEWDATA,     /* Error: no new Data is not available */
    E2E_PHSTATUS_WRONGCHECKSUM, /* Error: the checksum is incorrect or the low nibble
                                       of the high byte of Data ID is incorrect.  */
    E2E_PHSTATUS_SYNC,          /* NOT VALID: The new data has been received after
                                       detection of an unexpected behavior of counter */
    E2E_PHSTATUS_INITIAL,       /* Initial: the checksum is correct, the first Data since
                                       the receiver's initialization or reinitialization */
    E2E_PHSTATUS_REPEATED,      /* Error: the checksum is correct, but the Counter is
                                       identical to the most recent Data received
                                       with Status _INITIAL, _OK, or _OKSOMELOST. */
    E2E_PHSTATUS_OKSOMELOST,    /* OK. */
    E2E_PHSTATUS_WRONGSEQUENCE, /* Error: the checksum is correct, but the DeltaCounter
                                       is out of range. */
} E2E_PhCheckStatusType;

/* State of the receiver for a Data protected with E2E Profile Ph. */
typedef struct
{
    uint8 LastValidCounter;           /* Counter value most recently received. */
    uint8 MaxDeltaCounter;            /* MaxDeltaCounter specifies the maximum
                                         allowed difference between two counter
                                         values of consecutively received valid
                                         messages. */
    boolean WaitForFirstData;         /* If true means that no correct data has
                                         been yet received after the receiver
                                         initialization or reinitialization. */
    boolean NewDataAvailable;         /* Indicates to E2E Library that a new data
                                         is available for Library to be checked. */
    uint8 LostData;                   /* Number of data (messages) lost since
                                         reception of last valid one. */
    E2E_PhCheckStatusType Status;     /* Result of the verification of the Data,
                                         determined by the Check function. */
    uint8 SyncCounter;                /* Number of Data required for validating
                                         the consistency of the counter  */
    uint8 NoNewOrRepeatedDataCounter; /* Amount of consecutive reception cycles
                                         in which either (1) there was no new data,
                                         or (2) when the data was repeated. */
} E2E_PhCheckStateType;

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

extern FUNC(Std_ReturnType, E2E_CODE) E2E_PhProtect
(
    P2CONST(E2E_PhConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr,
    P2VAR(E2E_PhProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
    P2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr
);
extern FUNC(Std_ReturnType, E2E_CODE) E2E_PhProtectInit
(
    P2VAR(E2E_PhProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr
);
extern FUNC(Std_ReturnType, E2E_CODE) E2E_PhCheck
    (
    P2CONST(E2E_PhConfigType, AUTOMATIC, E2E_APPL_DATA) Config,
    P2VAR(E2E_PhCheckStateType, AUTOMATIC, E2E_APPL_DATA) State,
    P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) Data
);
extern FUNC(Std_ReturnType, E2E_CODE) E2E_PhCheckInit
(
    P2VAR(E2E_PhCheckStateType, AUTOMATIC, E2E_APPL_DATA) State
);
extern FUNC(E2E_PCheckStatusType, E2E_CODE) E2E_PhMapStatusToSM
(
    Std_ReturnType CheckReturn,
    E2E_PhCheckStatusType Status,
    boolean profileBehavior
);

#define E2E_STOP_SEC_CODE
#include "E2E_MemMap.h"

#endif /* E2E_Ph_H_ */
