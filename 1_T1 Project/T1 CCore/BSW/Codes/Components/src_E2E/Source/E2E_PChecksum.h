/*
********************************************************************************
*
* File name: E2E_PChecksum.h
*
* Copyright 2022-2024 Neusoft Reach Corporation.All rights reserved.
*
********************************************************************************
*
* History
*-------------------------------------------------------------------------------
********************************************************************************
* Version: 3.0
* Author/Date: XieYN/2022.08.29
* Change: New created.
* Cause: New
********************************************************************************
* Version: 3.1
* Author/Date: XieYN/2022.09.20
* Change: Modify the type of LastValidCounter, MaxDeltaCounter, LostData,
*         SyncCounter and NoNewOrRepeatedDataCounter from uint8 to uint16.
* Cause: Optimization
********************************************************************************
* Version: 3.2
* Author/Date: XieYN/2022.09.20
* Change: 1. Modify E2E_PChecksumCheckStatusType enum value.
*         2. Add E2E_PCHECKSUM_CHECKSUMSIZE_0 for configuration ChecksumSize is 0.
*         3. Modify code specifications.
* Cause: Optimization
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
#ifndef E2E_PCHECKSUM_H_
#define E2E_PCHECKSUM_H_

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

/* CounterSize */
#define E2E_PCHECKSUM_COUNTERSIZE_0              (0U)
#define E2E_PCHECKSUM_COUNTERSIZE_4              (4U)
#define E2E_PCHECKSUM_COUNTERSIZE_16             (16U)

/* CounterSize */
#define E2E_PCHECKSUM_CHECKSUMSIZE_0             (0U)
#define E2E_PCHECKSUM_CHECKSUMSIZE_4             (4U)
#define E2E_PCHECKSUM_CHECKSUMSIZE_8             (8U)

/* Counter max value(According to CounterSize) */
#define E2E_PCHECKSUMPROTECT_COUNTERMAX_4        (15U)
#define E2E_PCHECKSUMPROTECT_COUNTERMOD_4        (16U)

#define E2E_PCHECKSUMPROTECT_COUNTERMAX_16       (65535U)
#define E2E_PCHECKSUMPROTECT_COUNTERMOD_16       (65536U)

/* Byte deal with */
#define E2E_PCHECKSUM_HIGH2BITS_NIBBLE           (0x30U)
#define E2E_PCHECKSUM_LOW2BITS_NIBBLE            (0x03U)

/* Counter deal with */
#define E2E_PCHECKSUM_LOWNIBBLE                  (0x0FU)
#define E2E_PCHECKSUM_RESERVEBIT                 (0xC0U)

/* PChecksum DataID. */
#define E2E_PCHECKSUM_EXTENDED_OR                (0xE0000000U)
#define E2E_PCHECKSUM_STANDARD_OR                (0x0800U)

#define E2E_EXTENDED_DATAIDBITS                  (32U)
#define E2E_STANDARD_DATAIDBITS                  (12U)

/* DataID length */
#define E2E_PCHECKSUM_DATAID_8_NIBBYTES          (8U)
#define E2E_PCHECKSUM_DATAID_3_NIBBYTES          (3U)

/*
********************************************************************************
*    Global Types
********************************************************************************
*/
/* Configuration of transmitted Data (Data Element or I-PDU), for E2E Profile
   PChecksum. For each transmitted Data, there is an instance of this typedef. */
typedef struct
{
    uint16 CounterOffset;         /* Bit offset of Counter. */
    uint16 ChecksumOffset;        /* Bit offset of checksum. */
    uint8 CounterSize;            /* CounterSize. */
    E2EPW_EndianessType CounterEndianess;       /* CounterEndianess. */
    uint8 ChecksumSize;           /* ChecksumSize. */
    uint8 ChecksumXORValue;       /* ChecksumXORValue. */
    uint16 DataLength;            /* Length of data, in bits. */
    uint8 MaxDeltaCounterInit;    /* Initial maximum allowed gap between two counter
                                     values of two consecutively receivedvalid Data. */
    uint8 MaxNoNewOrRepeatedData; /* The maximum amount of missing or repeated Data */
    uint8 SyncCounterInit;        /* Number of Data required for validating the
                                     consistency of the counter that must be received
                                     with a valid counter after the detection of
                                     an unexpected behavior of a received counter. */
} E2E_PChecksumConfigType;

/* State of the sender for a Data protected with E2E Profile PChecksum. */
typedef struct
{
    /* Counter to be used for protecting the next Data. */
    uint16 Counter;
} E2E_PChecksumProtectStateType;

/* Result of the verification of the Data in E2E Profile PChecksum, determined by
   the Check function. */
typedef enum
{
    E2E_PCHECKSUMSTATUS_OK = 0x00U,       /* OK */
    E2E_PCHECKSUMSTATUS_NONEWDATA = 0x01U, /* Error: no new Data is not available. */
    E2E_PCHECKSUMSTATUS_WRONGCHECKSUM = 0x02U, /* Error: the CRC is incorrect or the low
                                           nibble of the high byte of Data ID is
                                           incorrect. */
    E2E_PCHECKSUMSTATUS_SYNC = 0x03U,     /* NOT VALID: The new data has been
                                             received after detection of an
                                             unexpected behavior of counter. */
    E2E_PCHECKSUMSTATUS_INITIAL = 0x04U,  /* Initial: the CRC is correct, the
                                             first Data since the receiver's
                                             initialization or reinitialization. */
    E2E_PCHECKSUMSTATUS_REPEATED = 0x08U, /* Error: the CRC is correct, but the
                                             Counter is identical to the most
                                             recent Data received with Status
                                             _INITIAL, _OK, or _OKSOMELOST. */
    E2E_PCHECKSUMSTATUS_OKSOMELOST = 0x20U, /* OK */
    E2E_PCHECKSUMSTATUS_WRONGSEQUENCE = 0x40U, /* Error: the CRCis correct, but the
                                           Counter Delta is too big. */

} E2E_PChecksumCheckStatusType;

/* State of the receiver for a Data protected with E2E Profile PChecksum. */
typedef struct
{
    uint16 LastValidCounter;             /* Counter value most recently received. */
    uint16 MaxDeltaCounter;              /* MaxDeltaCounter specifies the maximum
                                            allowed difference between two counter
                                            values of consecutively received valid
                                            messages. */
    boolean WaitForFirstData;            /* If true means that no correct data has
                                            been yet received after the receiver
                                            initialization or reinitialization. */
    boolean NewDataAvailable;            /* Indicates to E2E Library that a new data
                                            is available for Library to be checked. */
    uint16 LostData;                     /* Number of data (messages) lost since
                                            reception of last valid one. */
    E2E_PChecksumCheckStatusType Status; /* Result of the verification of the Data,
                                            determined by the Check function. */
    uint16 SyncCounter;                  /* Number of Data required for validating
                                            the consistency of the counter  */
    uint16 NoNewOrRepeatedDataCounter;   /* Amount of consecutive reception cycles
                                            in which either (1) there was no new data,
                                            or (2) when the data was repeated. */
} E2E_PChecksumCheckStateType;

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

extern FUNC(Std_ReturnType, E2E_CODE) E2E_PChecksumProtect
(
    P2CONST(E2E_PChecksumConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr,
    P2VAR(E2E_PChecksumProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
    P2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr
);
extern FUNC(Std_ReturnType, E2E_CODE) E2E_PChecksumProtectInit
(
    P2VAR(E2E_PChecksumProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr
);
extern FUNC(uint16, E2E_CODE) E2E_PChecksum_ReadCounter
(
    P2CONST(E2E_PChecksumConfigType, AUTOMATIC, E2E_APPL_DATA) Config,
    P2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) Data
);
extern FUNC(Std_ReturnType, E2E_CODE) E2E_PChecksum_ReadChecksum
(
    P2CONST(E2E_PChecksumConfigType, AUTOMATIC, E2E_APPL_DATA) Config,
    P2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) Data
);
extern FUNC(Std_ReturnType, E2E_CODE) E2E_PChecksumCheck
(
    P2CONST(E2E_PChecksumConfigType, AUTOMATIC, E2E_APPL_DATA) Config,
    P2VAR(E2E_PChecksumCheckStateType, AUTOMATIC, E2E_APPL_DATA) State,
    P2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) Data
);
extern FUNC(Std_ReturnType, E2E_CODE) E2E_PChecksumCheckInit
(
    P2VAR(E2E_PChecksumCheckStateType, AUTOMATIC, E2E_APPL_DATA) State
);
extern FUNC(E2E_PCheckStatusType, E2E_CODE) E2E_PChecksumMapStatusToSM
(
    Std_ReturnType CheckReturn,
    E2E_PChecksumCheckStatusType Status
);

#define E2E_STOP_SEC_CODE
#include "E2E_MemMap.h"

#endif /* E2E_PCHECKSUM_H_ */
