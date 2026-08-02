/*
********************************************************************************
*
* File name: E2E_P4BitXOR.h
*
* Copyright 2022-2024 Neusoft Reach Corporation.All rights reserved.
*
********************************************************************************
*
* History
*-------------------------------------------------------------------------------
********************************************************************************
* Version: 3.0
* Author/Date: XieYN/2022.10.31
* Change: New Created.
* Cause: New
********************************************************************************
* Version: 3.1
* Author/Date: LiDaY/2024.02.05
* Change: Modifying the label of the input parameter Ptrclass for E2E function
*         and addressing some code inconsistencies.
* Cause: Optimization
********************************************************************************
* Version: 3.2
* Author/Date: LiDaY/2024.03.18
* Change: Modifying the label of the input parameter Ptrclass for E2E function
*         and addressing some code inconsistencies.
* Cause: Optimization
********************************************************************************
* Version: 3.3
* Author/Date: LiDaY/2024.04.25
* Change: Add a memory-map label to function and variable declarations.
* Cause: Bugfix
********************************************************************************
* Version: 3.4
* Author/Date: LiDaY/2024.08.08
* Change: Change copyright information.
* Cause: Update
********************************************************************************
*/
#ifndef E2E_P4BITXOR_H_
#define E2E_P4BITXOR_H_

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
#define E2E_P4BITXORPROTECT_COUNTERMAX  (15U)
#define E2E_P4BITXORPROTECT_COUNTERMOD  (16U)

/*
********************************************************************************
*    Global Types
********************************************************************************
*/
/* Configuration of transmitted Data (Data Element or I-PDU), for E2E Profile
   4BitXOR. For each transmitted Data, there is an instance of this typedef. */
typedef struct
{
    uint16 CounterOffset;          /* Bit offset of Counter. */
    uint16 ChecksumOffset;         /* Bit offset of Checksum. */
    uint16 DataLength;             /* Length of data, in bits. */
    uint8 MaxDeltaCounterInit;     /* Initial maximum allowed gap between two
                                      counter values of two consecutively
                                      receivedvalid Data. */
    uint8 MaxNoNewOrRepeatedData;  /* The maximum amount of missing or repeated
                                      Data. */
    uint8 SyncCounterInit;         /* Number of Data required for validating
                                      the consistency of the counter that must
                                      be received with a valid counter after
                                      the detection of an unexpected behavior
                                      of a received counter. */
} E2E_P4BitXORConfigType;

/* State of the sender for a Data protected with E2E Profile 4BitXOR. */
typedef struct
{
    uint8 Counter;                  /* Counter to be used for protecting the
                                       next Data. */
} E2E_P4BitXORProtectStateType;

/* Result of the verification of the Data in E2E Profile 4BitXOR, determined by the
   Check function. */
typedef enum
{
    E2E_P4BITXORSTATUS_OK = 0x00U,        /* OK */
    E2E_P4BITXORSTATUS_NONEWDATA = 0x01U, /* Error: no new Data is not available. */
    E2E_P4BITXORSTATUS_WRONGCHECKSUM = 0x02U,  /* Error: the CRC is incorrect. */
    E2E_P4BITXORSTATUS_SYNC = 0x03U,      /* NOT VALID: The new data has been
                                             received after detection of an
                                             unexpected behavior of counter. */
    E2E_P4BITXORSTATUS_INITIAL = 0x04U,   /* Initial: the CRC is correct, the
                                             first Data since the receiver's
                                             initialization or reinitialization. */
    E2E_P4BITXORSTATUS_REPEATED = 0x08U,  /* Error: the CRC is correct, but the
                                             Counter is identical to the most
                                             recent Data received with Status
                                             _INITIAL, _OK, or _OKSOMELOST. */
    E2E_P4BITXORSTATUS_OKSOMELOST = 0x20U,    /* OK */
    E2E_P4BITXORSTATUS_WRONGSEQUENCE = 0x40U, /* Error: the CRCis correct, but the
                                             Counter Delta is too big. */
} E2E_P4BitXORCheckStatusType;

/* State of the receiver for a Data protected with E2E Profile 4BitXOR. */
typedef struct
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
    E2E_P4BitXORCheckStatusType Status; /* Result of the verification of the Data,
                                           determined by the Check function. */
    uint8 SyncCounter;                  /* Number of Data required for validating
                                            the consistency of the counter. */
    uint8 NoNewOrRepeatedDataCounter;   /* Amount of consecutive reception
                                           cycles in which either (1) there
                                           was no new data, or (2) when the
                                           data was repeated. */
} E2E_P4BitXORCheckStateType;

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

extern FUNC(Std_ReturnType, E2E_CODE) E2E_P4BitXORProtect
(
    P2CONST(E2E_P4BitXORConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr,
    P2VAR(E2E_P4BitXORProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
    P2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr
);
extern FUNC(Std_ReturnType, E2E_CODE) E2E_P4BitXORProtectInit
(
    P2VAR(E2E_P4BitXORProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr
);
extern FUNC(Std_ReturnType, E2E_CODE) E2E_P4BitXORCheck
(
    P2CONST(E2E_P4BitXORConfigType, AUTOMATIC, E2E_APPL_DATA) Config,
    P2VAR(E2E_P4BitXORCheckStateType, AUTOMATIC, E2E_APPL_DATA) State,
    P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) Data
);
extern FUNC(Std_ReturnType, E2E_CODE) E2E_P4BitXORCheckInit
(
    P2VAR(E2E_P4BitXORCheckStateType, AUTOMATIC, E2E_APPL_DATA) State
);
extern FUNC(E2E_PCheckStatusType, E2E_CODE) E2E_P4BitXORMapStatusToSM
(
    Std_ReturnType CheckReturn,
    E2E_P4BitXORCheckStatusType Status
);

#define E2E_STOP_SEC_CODE
#include "E2E_MemMap.h"

#endif /* E2E_P4BITXOR_H_ */
