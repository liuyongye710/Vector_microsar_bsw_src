/*
********************************************************************************
*
* File name: Rte_Dlt_Type.h
*
* Copyright 2018-2024 Neusoft Reach Corporation. All rights reserved.
*
********************************************************************************
*
* History
*-------------------------------------------------------------------------------
********************************************************************************
* Version: 1.0
* Author/Date : ZhangDX/2019.04.23
* Change: New
* Cause: New
********************************************************************************
* Version: 1.0
* Author/Date : ZhangDX/2019.04.26
* Change: change file struct
* Cause: update
********************************************************************************
* Version: 1.2
* Author/Date : ZhangDX/2019.05.22
* Change: add Dcm module interface
* Cause: add Functions
********************************************************************************
* Version: 1.3
* Author/Date : ChenQJ/2023.07.31
* Change: Modify module type definition for R21-11.
* Cause: Update
********************************************************************************
* Version: 1.4
* Author/Date : ChenQJ/2023.09.21
* Change: 1. Modify Dlt_MessageLogLevelType, add DLT_LOG_USE_DEFAULT.
*         2. Add Dlt_LogChannelNameType.
* Cause: Update
********************************************************************************
* Version: 1.5
* Author/Date : ChenQJ/2023.10.07
* Change: 1. Add marco DLT_TRACE_STATUS_USE_DEFAULT.
*         2. Add Dlt_AssignmentOperation.
* Cause: Update
********************************************************************************
*/
#ifndef RTE_DLT_TYPE_H_
#define RTE_DLT_TYPE_H_

/*
********************************************************************************
*    Includes
********************************************************************************
*/
#include "Platform_Types.h"

/*
********************************************************************************
*    Global Macros
********************************************************************************
*/
#define DLT_TRACE_STATUS_USE_DEFAULT        (0xFFU)

/*
********************************************************************************
*    Global Types
********************************************************************************
*/
/* This type identifies the session. */
#ifndef Rte_TypeDef_Dlt_SessionIDType
#define Rte_TypeDef_Dlt_SessionIDType
typedef uint32 Dlt_SessionIDType;
#endif

/* This type describes the count of arguments provided to a message. */
#ifndef Rte_TypeDef_Dlt_MessageArgumentCount
#define Rte_TypeDef_Dlt_MessageArgumentCount
typedef uint16 Dlt_MessageArgumentCount;
#endif

/* This type describes the log level for each log message. */
#ifndef Rte_TypeDef_Dlt_MessageLogLevelType
#define Rte_TypeDef_Dlt_MessageLogLevelType
typedef enum
{
    DLT_LOG_OFF = 0U,
    DLT_LOG_FATAL = 1U,
    DLT_LOG_ERROR = 2U,
    DLT_LOG_WARN = 3U,
    DLT_LOG_INFO = 4U,
    DLT_LOG_DEBUG = 5U,
    DLT_LOG_VERBOSE = 6U,
    DLT_LOG_USE_DEFAULT = 0xFFU,
} Dlt_MessageLogLevelType;
#endif

/* This type describes labels for trace messages. */
#ifndef Rte_TypeDef_Dlt_MessageTraceType
#define Rte_TypeDef_Dlt_MessageTraceType
typedef enum
{
    DLT_TRACE_VARIABLE = 1U,
    DLT_TRACE_FUNCTION_IN = 2U,
    DLT_TRACE_FUNCTION_OUT = 3U,
    DLT_TRACE_STATE = 4U,
    DLT_TRACE_VFB = 5U,
} Dlt_MessageTraceType;
#endif

/* Dlt_MessageOptionsType. */
#ifndef Rte_TypeDef_Dlt_MessageOptionsType
#define Rte_TypeDef_Dlt_MessageOptionsType
typedef uint8 Dlt_MessageOptionsType;
#endif

/* This type describes the ContextId. 0x00000000 means the so-called wildcard. */
#ifndef Rte_TypeDef_Dlt_ContextIDType
#define Rte_TypeDef_Dlt_ContextIDType
typedef uint32 Dlt_ContextIDType;
#endif

/* This type describes the ApplicationId. 0x00000000 means the so-called wildcard. */
#ifndef Rte_TypeDef_Dlt_ApplicationIDType
#define Rte_TypeDef_Dlt_ApplicationIDType
typedef uint32 Dlt_ApplicationIDType;
#endif

/* This type describes the LogChannel name. */
#ifndef Rte_TypeDef_Dlt_LogChannelNameType
#define Rte_TypeDef_Dlt_LogChannelNameType
typedef uint8 Dlt_LogChannelNameType[4U];
#endif

/* Dlt_MessageLogInfoType. */
#ifndef Rte_TypeDef_Dlt_MessageLogInfoType
#define Rte_TypeDef_Dlt_MessageLogInfoType
typedef struct
{
    Dlt_MessageArgumentCount argCount;
    Dlt_MessageLogLevelType logLevel;
    Dlt_MessageOptionsType options;
    Dlt_ContextIDType contextId;
    Dlt_ApplicationIDType appId;
} Dlt_MessageLogInfoType;
#endif

/* Dlt_MessageTraceInfoType. */
#ifndef Rte_TypeDef_Dlt_MessageTraceInfoType
#define Rte_TypeDef_Dlt_MessageTraceInfoType
typedef struct
{
    Dlt_MessageTraceType traceInfo;
    Dlt_MessageOptionsType options;
    Dlt_ContextIDType contextId;
    Dlt_ApplicationIDType appId;
} Dlt_MessageTraceInfoType;
#endif

/* Adding or removing a LogChannel assignment for the given tuple of ApplicationId/ContextId. */
#ifndef Rte_TypeDef_Dlt_AssignmentOperation
#define Rte_TypeDef_Dlt_AssignmentOperation
typedef uint8 Dlt_AssignmentOperation;
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

#endif /* RTE_DLT_TYPE_H_ */

