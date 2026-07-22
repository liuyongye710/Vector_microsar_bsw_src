/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2021 by Vector Informatik GmbH.                                              All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/*!        \file  vSwUpdM_Priv_Types.h
 *        \brief  vSwUpdM private type declarations.
 *      \details  Header for vSwUpdM private type declarations.
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *
 *  FILE VERSION
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the VERSION CHECK below.
 *********************************************************************************************************************/

#ifndef VSWUPDM_PRIV_TYPES_H
# define VSWUPDM_PRIV_TYPES_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "vSwUpdM.h"
#include "vSwUpdM_CfgTypes.h"
#include "vSwUpdM_Grid_Types.h"

#include "vStreamProc_Types.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/*! Helper macro to determine array size. */
#define VSWUPDM_ARRAY_SIZE(arr)         (sizeof(arr) / sizeof((arr)[0]))

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/*! Standard return type for efficient return of boolean values. */
typedef unsigned int vSwUpdM_StdReturnType;

/*! Range check result type */
typedef enum
{
  VSWUPDM_RANGE_CHECK_MISMATCH,
  VSWUPDM_RANGE_CHECK_CONTAINED,
  VSWUPDM_RANGE_CHECK_OVERLAP_START,
  VSWUPDM_RANGE_CHECK_OVERLAP_END
} vSwUpdM_RangeCheckType;

typedef enum
{
  VSWUPDM_QUEUE_PRIO_ORDER_DESC,  /**< Descending order: Higher values result in higher priority */
  VSWUPDM_QUEUE_PRIO_ORDER_ASC    /**< Ascending order: Lower values result in higher priority */
} vSwUpdM_QueuePrioOrderType;

typedef struct
{
  vSwUpdM_VarDataPointerType  Buffer;     /**< Pointer to referenced buffer */
  vSwUpdM_LengthType          Size;       /**< Size of referenced buffer */
  vSwUpdM_LengthType          Position;   /**< Current position in buffer */
  vSwUpdM_LengthType          Used;       /**< Current data length */
  vSwUpdM_LengthType          Free;
} vSwUpdM_BufferInfoType;

typedef struct
{
  uint32 PartitionCount;
  uint32 ModuleCount;
  uint32 RegionCount;                 /**< Region count of opened module */
  uint32 InternalSegmentCount;        /**< Segment count of opened module */
  uint32 ExternalSegmentCount;
  uint32 WriteSegmentCount;           /**< Count of segments which will be written */
  boolean ExternalSegmentCountDirty;  /**< Flag to mark external segment count as "dirty". */
} vSwUpdM_EntityCountType;

typedef struct
{
  vSwUpdM_VarPartitionsPtrType  Partition;
  vSwUpdM_VarModulesPtrType     Module;
  vSwUpdM_VarRegionsPtrType     Region;
  vSwUpdM_VarSegmentsPtrType    Segment;
} vSwUpdM_EntityObjectsType;

typedef struct
{
  vSwUpdM_EntityCountType     Count;
  vSwUpdM_EntityIdsType       OpenIds;
  vSwUpdM_EntityObjectsType   OpenObjects;
} vSwUpdM_EntityDataType;

typedef struct
{
  Std_ReturnType      Result;
  vSwUpdM_AddressType TargetAddress;
  boolean             Valid;
  boolean             Pending;
} vSwUpdM_LinkedResultType;

typedef enum
{
  VSWUPDM_JOB_PHASE_PRE_HOOK,
  VSWUPDM_JOB_PHASE_EVAL_PRE_HOOK,
  VSWUPDM_JOB_PHASE_MAIN_HANDLER,
  VSWUPDM_JOB_PHASE_POST_HOOK,
  VSWUPDM_JOB_PHASE_EVAL_POST_HOOK,
  VSWUPDM_JOB_PHASE_FINISH
} vSwUpdM_JobPhaseType;

typedef enum
{
  VSWUPDM_TRIM_TYPE_SINGLE,
  VSWUPDM_TRIM_TYPE_MAX,
  VSWUPDM_TRIM_TYPE_BURST
} vSwUpdM_TrimTypeType;

typedef enum
{
  VSWUPDM_STREAMPROCRESULT_EMPTY,
  VSWUPDM_STREAMPROCRESULT_BLOCKED,
  VSWUPDM_STREAMPROCRESULT_FULL,
  VSWUPDM_STREAMPROCRESULT_PARTIALLY,
  VSWUPDM_STREAMPROCRESULT_FAIL
} vSwUpdM_StreamProcessResultType;

/*!
 * Internal comment removed.
 *
 *
 */
typedef enum
{
  VSWUPDM_REMOTESTREAMSTATE_IDLE,
  VSWUPDM_REMOTESTREAMSTATE_RX_PREPARED,
  VSWUPDM_REMOTESTREAMSTATE_TX_RESPONSE,
  VSWUPDM_REMOTESTREAMSTATE_TX_RESPONSE_TRANSMIT,
  VSWUPDM_REMOTESTREAMSTATE_RX_COPY_RESPOND,
  VSWUPDM_REMOTESTREAMSTATE_RX_REQUEST_TRANSMIT,
  VSWUPDM_REMOTESTREAMSTATE_RX_COPY,
  VSWUPDM_REMOTESTREAMSTATE_TX_COPY,
  VSWUPDM_REMOTESTREAMSTATE_RX_TRANSMIT_END,
  VSWUPDM_REMOTESTREAMSTATE_TX_WAIT_END,
  VSWUPDM_REMOTESTREAMSTATE_DONE,
  VSWUPDM_REMOTESTREAMSTATE_FAIL
}vSwUpdM_RemoteStream_StateType;

typedef uint8 vSwUpdM_RemoteStreamHandleType;
typedef uint32 vSwUpdM_RemoteStreamSizeType;

typedef struct
{
  vSwUpdM_RemoteStream_StateType            State;
  P2VAR(uint8, AUTOMATIC, VSWUPDM_APPL_VAR) Buffer;
  vSwUpdM_RemoteStreamSizeType              BufferSize;
  vSwUpdM_RemoteStreamSizeType              AvailableLength;
  vSwUpdM_RemoteStreamSizeType              Offset;
  vSwUpdM_NodeIterType                      Source;
  vSwUpdM_NodeIterType                      Target;
} vSwUpdM_RemoteStream_ListType;

typedef enum
{
  VSWUPDM_RESTORE_SEGMENTS_NONE,
  VSWUPDM_RESTORE_SEGMENTS_FIRST,
  VSWUPDM_RESTORE_SEGMENTS_KEEP_STATE,
  VSWUPDM_RESTORE_SEGMENTS_FULL
} vSwUpdM_RestoreSegmentsType;

typedef enum
{
  VSWUPDM_PIPELINED_STATE_IDLE,
  VSWUPDM_PIPELINED_STATE_PENDING,
  VSWUPDM_PIPELINED_STATE_DONE
} vSwUpdM_PipelinedStateType;

typedef struct
{
  vSwUpdM_PipelinedStateType State;
  Std_ReturnType             PreviousWriteResult;
} vSwUpdM_PipelinedProgrammingType;

typedef enum
{
  VSWUPDM_PIPE_STATE_IDLE,
  VSWUPDM_PIPE_STATE_PROCESSING,
  VSWUPDM_PIPE_STATE_FLUSHING
} vSwUpdM_PipeStateType;

typedef struct
{
  vSwUpdM_StreamLengthType          Length;
  vSwUpdM_StreamLengthType          MaxLength;
  vSwUpdM_StreamLengthType          Remainder;
  vSwUpdM_ProcessingOperationType   Operation;
  vSwUpdM_StreamStateType           State;
  vSwUpdM_SegmentIdValueType        SegmentId;

  vStreamProc_PipeIdType            PipeId;
  vStreamProc_EntryPointIdType      PipeEntryPointData;
  vSwUpdM_PipeStateType             PipeState;

  boolean                           RestartHandling;
  boolean                           PipeStarted;
} vSwUpdM_StreamDataType;

typedef struct vSwUpdM_ProcessDataType_Tag vSwUpdM_ProcessDataType;

/*!
 * Internal comment removed.
 *
 *
 */
typedef uint16 vSwUpdM_SubScopeAttributeType;

typedef struct
{
  vSwUpdM_SubScopeOfDataProcessesType SubScope;
  vSwUpdM_SubScopeAttributeType       Attributes;
} vSwUpdM_SubScopeDefinitionType;

typedef enum
{
#if (VSWUPDM_DEV_ERROR_DETECT == STD_ON)
  VSWUPDM_COMMON_DET_CHECK_INITIALIZED,
#endif
  VSWUPDM_COMMON_DET_CHECK_PARTITION,
  VSWUPDM_COMMON_DET_CHECK_MODULE,
  VSWUPDM_COMMON_DET_CHECK_SEGMENT,
  VSWUPDM_COMMON_DET_CHECK_STREAM
} vSwUpdM_CommonDetCheckType;

typedef enum
{
  VSWUPDM_STATE_CHECK_IDLE,
  VSWUPDM_STATE_CHECK_PIPELINED,
  VSWUPDM_STATE_CHECK_NONE
} vSwUpdM_StateCheckType;

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

#endif /* VSWUPDM_PRIV_TYPES_H */

/**********************************************************************************************************************
 *  END OF FILE: vSwUpdM_Priv_Types.h
 *********************************************************************************************************************/
