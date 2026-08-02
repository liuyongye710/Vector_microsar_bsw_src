/*
********************************************************************************
*
* File name: Rte_StbM_Type.h
*
* Copyright 2018-2024 Neusoft Reach Corporation. All rights reserved.
*
********************************************************************************
*
* History
*-------------------------------------------------------------------------------
********************************************************************************
* Version: 1.0
* Author/Date : Zhidx/2021.05.11
* Change: New Created
* Cause: New
********************************************************************************

*/
#ifndef RTE_STBM_TYPES_H_
#define RTE_STBM_TYPES_H_

/*
********************************************************************************
*    Includes
********************************************************************************
*/
#include "Std_Types.h"

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
/* Rte Data Types Temporarily defined here */
/* Variables of this type are used to represent the kind of synchronized time-base */
#ifndef Rte_TypeDef_StbM_SynchronizedTimeBaseType
#define Rte_TypeDef_StbM_SynchronizedTimeBaseType
typedef uint16 StbM_SynchronizedTimeBaseType;
#endif

/* Variables of this type are used to express if and how a Local Time Base is synchronized to 
    the Global Time Master. The type is a bitfield of individual status bits, although not every 
    combination is possible, i.e. any of the bits TIMEOUT, TIMELEAP_FUTURE, TIMELEAP_PAST 
    and SYNC_TO_GATEWAY can only be set if the GLOBAL_TIME_BASE bit is set */
#ifndef Rte_TypeDef_StbM_TimeBaseStatusType
#define Rte_TypeDef_StbM_TimeBaseStatusType
typedef uint8 StbM_TimeBaseStatusType;
#endif

/* Variables of this type are used for expressing time stamps including relative time and absolute 
    calendar time. The absolute time starts from 1970-01-01. */
#ifndef Rte_TypeDef_StbM_TimeStampType
#define Rte_TypeDef_StbM_TimeStampType
typedef struct
{
    /* Status of the Time Base */
    StbM_TimeBaseStatusType timeBaseStatus;
    /* Nanoseconds part of the time */
    uint32 nanoseconds;
    /* 32 bit LSB of the 48 bits Seconds part of the time */
    uint32 seconds;
    /* 16 bit MSB of the 48 bits Seconds part of the time */
    uint16 secondsHi;
} StbM_TimeStampType;
#endif

/* Variables of this type are used for expressing time stamps including relative 
    time and absolute calendar time. The absolute time starts from 1970-01-01. */
#ifndef Rte_TypeDef_StbM_TimeStampExtendedType
#define Rte_TypeDef_StbM_TimeStampExtendedType
typedef struct
{
    /* Status of the Time Base */
    StbM_TimeBaseStatusType timeBaseStatus;
    /* Nanoseconds part of the time */
    uint32 nanoseconds;
    /* 48 bit Seconds part of the time */
    uint64 seconds;
} StbM_TimeStampExtendedType;
#endif

/* Variables of this type are used to express time differences / offsets as signed 
    values in in nanoseconds */
#ifndef Rte_TypeDef_StbM_TimeDiffType
#define Rte_TypeDef_StbM_TimeDiffType
typedef sint32 StbM_TimeDiffType;
#endif

/* Variables of this type are used to express a rate deviation in ppm */
#ifndef Rte_TypeDef_StbM_RateDeviationType
#define Rte_TypeDef_StbM_RateDeviationType
typedef sint16 StbM_RateDeviationType;
#endif

/* Current user data of the Time Base */
#ifndef Rte_TypeDef_StbM_UserDataType
#define Rte_TypeDef_StbM_UserDataType
typedef struct
{
    /* User Data Length in bytes */
    uint8 userDataLength;
    /* User Byte 0 */
    uint8 userByte0;
    /* User Byte 1 */
    uint8 userByte1;
    /* User Byte 2 */
    uint8 userByte2;
} StbM_UserDataType;
#endif

/* unique identifier of a notification customer */
#ifndef Rte_TypeDef_StbM_CustomerIdType
#define Rte_TypeDef_StbM_CustomerIdType
typedef uint16 StbM_CustomerIdType;
#endif

/* The StbM_TimeBaseNotificationType type defines a number of global time related events. 
    The type definition is used for storing the events in the status variable NotificationEvents 
    and for setting the mask variable NotificationMask which defines a subset of events for which 
    an interrupt request shall be raised */
#ifndef Rte_TypeDef_StbM_TimeBaseNotificationType
#define Rte_TypeDef_StbM_TimeBaseNotificationType
typedef uint32 StbM_TimeBaseNotificationType;
#endif

/* Synchronized Time Base Record Table Header */
#ifndef Rte_TypeDef_StbM_SyncRecordTableHeadType
#define Rte_TypeDef_StbM_SyncRecordTableHeadType
typedef struct
{
    /* Time Domain 0..15 */
    uint8 SynchronizedTimeDomain;
    /* HW Frequency in Hz */
    uint32 HWfrequency;
    /* Prescaler value */
    uint32 HWprescaler;
} StbM_SyncRecordTableHeadType;
#endif

/* Synchronized Time Base Record Table Block */
#ifndef Rte_TypeDef_StbM_SyncRecordTableBlockType
#define Rte_TypeDef_StbM_SyncRecordTableBlockType
typedef struct
{
    /* Seconds of the Local Time Base directly after synchronization with the Global Time Base */
    uint32 GlbSeconds;
    /* Nanoseconds of the Local Time Base directly after synchronization with the Global Time Base */
    uint32 GlbNanoSeconds;
    /* Time Base Status of the Local Time Base directly after synchronization with the Global Time Base */
    StbM_TimeBaseStatusType TimeBaseStatus;
    /* Least significant 32 bit of the Virtual Local Time directly after synchronization with the Global Time Bases */
    uint32 VirtualLocalTimeLow;
    /* Calculated Rate Deviation directly after rate deviation measurement */
    StbM_RateDeviationType RateDeviation;
    /* Seconds of the Local Time Base directly before synchronization with the Global Time Base */
    uint32 LocSeconds;
    /* Nanoseconds of the Local Time Base directly before synchronization with the Global Time Base */
    uint32 LocNanoSeconds;
    /* Current propagation delay in nanoseconds */
    uint32 PathDelay;
} StbM_SyncRecordTableBlockType;
#endif

/* Offset Time Base Record Table Header */
#ifndef Rte_TypeDef_StbM_OffsetRecordTableHeadType
#define Rte_TypeDef_StbM_OffsetRecordTableHeadType
typedef struct
{
    /* Time Domain 16..31 */ 
    uint8 OffsetTimeDomain;
} StbM_OffsetRecordTableHeadType;
#endif

/* Offset Time Base Record Table Block */
#ifndef Rte_TypeDef_StbM_OffsetRecordTableBlockType
#define Rte_TypeDef_StbM_OffsetRecordTableBlockType
typedef struct 
{
    /* Seconds of the Offset Time Base */
    uint32 GlbSeconds;
    /* Nanoseconds of the Offset Time Base */
    uint32 GlbNanoSeconds;
    /* Time Base Status of the Local Time Base directly after synchronization with the 
        Global Time Base */
    StbM_TimeBaseStatusType TimeBaseStatus;
} StbM_OffsetRecordTableBlockType;
#endif

/* This type indicates if an ECU is configured for a system wide master for a given Time Base 
    is available or not */
#ifndef Rte_TypeDef_StbM_MasterConfigType
#define Rte_TypeDef_StbM_MasterConfigType
typedef uint8 StbM_MasterConfigType;
#endif

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
#endif /* RTE_STBM_TYPES_H_ */

