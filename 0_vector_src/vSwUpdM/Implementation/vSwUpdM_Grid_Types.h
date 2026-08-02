/***********************************************************************************************************************
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
/*!        \file  vSwUpdM_Grid_Types.h
 *        \brief  vSwUpdM_Grid types header file
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's main header file.
 *
 *  FILE VERSION
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's main header file vSwUpdM.h.
 *********************************************************************************************************************/

#if !defined (VSWUPDM_GRID_TYPES_H)
#define VSWUPDM_GRID_TYPES_H

/***********************************************************************************************************************
 * INCLUDES
 **********************************************************************************************************************/
/* Other MultipleUnit's Type Headers used by Grid_Types */
#include "vSwUpdM_Types.h"

/***********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 **********************************************************************************************************************/
#define VSWUPDM_GRIDNODE_INVALID_NODE               vSwUpdM_GetSizeOfNode()
#define VSWUPDM_GRIDNODE_SINGLE_NODE_CFG_NODE_IDX   vSwUpdM_GetLocalNode()

 /***********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 **********************************************************************************************************************/

/*********************
 * GRID CHANNEL
 ********************/
typedef enum
{
  VSWUPDM_GRIDCHANNEL_CHANNELIDX_ZERO = 0,
  VSWUPDM_GRIDCHANNEL_CHANNELIDX_MAIN = VSWUPDM_GRIDCHANNEL_CHANNELIDX_ZERO,
  VSWUPDM_GRIDCHANNEL_CHANNELIDX_MAINTENANCE,
  VSWUPDM_GRIDCHANNEL_CHANNELIDX_SUSPEND,
  VSWUPDM_GRIDCHANNEL_CHANNELIDX_BOOKKEEPER,
  VSWUPDM_GRIDCHANNEL_CHANNELIDX_COUNT, /* PRQA S 0724 */ /* MD_vSwUpdM_Rule8.12_0724_EnumCountEqualsInvalid */
  VSWUPDM_GRIDCHANNEL_CHANNELIDX_INVALID = VSWUPDM_GRIDCHANNEL_CHANNELIDX_COUNT
} vSwUpdM_GridChannel_ChannelIdxType;

typedef enum
{
  VSWUPDM_GRIDCHANNEL_SERVICESTATE_UNUSED,
  VSWUPDM_GRIDCHANNEL_SERVICESTATE_INITIAL,
  VSWUPDM_GRIDCHANNEL_SERVICESTATE_TX_TP_ERROR,
  VSWUPDM_GRIDCHANNEL_SERVICESTATE_ACK,
  VSWUPDM_GRIDCHANNEL_SERVICESTATE_NACK,
  VSWUPDM_GRIDCHANNEL_SERVICESTATE_ACK_TIMEOUT,
  VSWUPDM_GRIDCHANNEL_SERVICESTATE_RESPONSE_TIMEOUT
} vSwUpdM_GridChannel_ServiceStateType;

typedef enum
{
  VSWUPDM_GRIDSRVC_GRIDSTATE_UNLOCKED,
  VSWUPDM_GRIDSRVC_GRIDSTATE_LOCK_REQUEST,
  VSWUPDM_GRIDSRVC_GRIDSTATE_LOCK_PENDING,
  VSWUPDM_GRIDSRVC_GRIDSTATE_LOCKED,
  VSWUPDM_GRIDSRVC_GRIDSTATE_CLEANUP,
  VSWUPDM_GRIDSRVC_GRIDSTATE_UNLOCK_REQUEST,
  VSWUPDM_GRIDSRVC_GRIDSTATE_UNLOCK_PENDING
} vSwUpdM_GridSrvc_GridStateType;

typedef enum
{
  VSWUPDM_GRIDSRVC_AGGREGATERESULT_DONE,
  VSWUPDM_GRIDSRVC_AGGREGATERESULT_PENDING
} vSwUpdM_GridSrvc_AggregateResultType;

/*********************
 * GRID RPC
 ********************/

/*! vRpcProxy data types */
typedef uint16 vSwUpdM_RpcProxyServiceIdType;
typedef uint16 vSwUpdM_RpcProxySourceIdType;
typedef uint16 vSwUpdM_RpcProxyTargetIdType;
typedef uint16 vSwUpdM_RpcProxyTargetGroupIdType;

/*********************
 * GRID SERVICE
 ********************/

typedef enum
{
  /* Indices to GridSrvc_Services table */
  VSWUPDM_GRIDSRVC_SERVICEIDX_ZERO = 0,

  VSWUPDM_GRIDSRVC_SERVICEIDX_LOCK = VSWUPDM_GRIDSRVC_SERVICEIDX_ZERO,
  VSWUPDM_GRIDSRVC_SERVICEIDX_SHUTDOWN,
  VSWUPDM_GRIDSRVC_SERVICEIDX_UNLOCK,

  VSWUPDM_GRIDSRVC_SERVICEIDX_SUSPEND,
  VSWUPDM_GRIDSRVC_SERVICEIDX_RESUME,

  VSWUPDM_GRIDSRVC_SERVICEIDX_START,

  VSWUPDM_GRIDSRVC_SERVICEIDX_END_STREAM,

  VSWUPDM_GRIDSRVC_SERVICEIDX_OPEN_PARTITION,
  VSWUPDM_GRIDSRVC_SERVICEIDX_CHECK_PARTITION,
  VSWUPDM_GRIDSRVC_SERVICEIDX_SET_PARTITION_VALID,
  VSWUPDM_GRIDSRVC_SERVICEIDX_SET_PARTITION_INVALID,
  VSWUPDM_GRIDSRVC_SERVICEIDX_SYNC_PARTITION,
  VSWUPDM_GRIDSRVC_SERVICEIDX_SWAP_PARTITION,

  VSWUPDM_GRIDSRVC_SERVICEIDX_OPEN_MODULE,
  VSWUPDM_GRIDSRVC_SERVICEIDX_CLOSE_MODULE,
  VSWUPDM_GRIDSRVC_SERVICEIDX_ERASE_MODULE,
  VSWUPDM_GRIDSRVC_SERVICEIDX_FINALIZE_MODULE,
  VSWUPDM_GRIDSRVC_SERVICEIDX_SYNC_MODULE,
  VSWUPDM_GRIDSRVC_SERVICEIDX_VALIDATE_MODULE,
  VSWUPDM_GRIDSRVC_SERVICEIDX_INVALIDATE_MODULE,
  VSWUPDM_GRIDSRVC_SERVICEIDX_CLEAR_SEGMENTS_OF_MODULE,
  VSWUPDM_GRIDSRVC_SERVICEIDX_INDICATE_WRITE_TO_MODULE,

  VSWUPDM_GRIDSRVC_SERVICEIDX_ERASE_REGION,

  VSWUPDM_GRIDSRVC_SERVICEIDX_OPEN_SEGMENT,
  VSWUPDM_GRIDSRVC_SERVICEIDX_CLOSE_SEGMENT,
  VSWUPDM_GRIDSRVC_SERVICEIDX_FINALIZE_SEGMENT,

  VSWUPDM_GRIDSRVC_SERVICEIDX_VERIFY_MODULE,
  VSWUPDM_GRIDSRVC_SERVICEIDX_PROCESS_MODULE,

  VSWUPDM_GRIDSRVC_SERVICEIDX_START_STREAM,
  VSWUPDM_GRIDSRVC_SERVICEIDX_ADD_SEGMENT,

  VSWUPDM_GRIDSRVC_SERVICEIDX_VERIFY_SEGMENT,

  /* Bookkeeper */
  VSWUPDM_GRIDSRVC_SERVICEIDX_BK_SET_GENERIC_PARAMETER,
  VSWUPDM_GRIDSRVC_SERVICEIDX_BK_SET_SEGMENT_ATTRIBUTES,
  VSWUPDM_GRIDSRVC_SERVICEIDX_BK_SET_RESUME_INFO,
  VSWUPDM_GRIDSRVC_SERVICEIDX_BK_GET_GENERIC_PARAMETER,
  VSWUPDM_GRIDSRVC_SERVICEIDX_BK_GET_SEGMENT_ATTRIBUTES,
  VSWUPDM_GRIDSRVC_SERVICEIDX_BK_GET_RESUME_INFO,
  VSWUPDM_GRIDSRVC_SERVICEIDX_BK_EXEC_COMMAND,

  /* Legacy services */
  VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_CONCLUDE_SEGMENT,
  VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_COPY_STREAM_DATA,
  VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_REQUEST_PROCESS_INFO,
  VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_PROCESS_STREAM_DATA,
  VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_RESPONSE_COPY_STREAM_DATA,
  VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_PERSIST_MODULE_STATE,
  VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_PERSIST_MODULE_VALID,
  VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_PERSIST_MODULE_PROGRAMMING_ATTEMPTS,
  VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_PERSIST_REGION_STATE,
  VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_PERSIST_REGION_PROGRAMMING_ATTEMPTS,
  VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_PERSIST_SEGMENT_ATTRIBUTES,
  VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_PERSIST_RESUME_INFO,
  VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_CONFIRMATION,
  VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_STREAM_COPY,
  VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_STREAM_END,
  VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_STREAM_REQUEST,
  VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_STREAM_START,

  VSWUPDM_GRIDSRVC_SERVICEIDX_COUNT,
  VSWUPDM_GRIDSRVC_SERVICEIDX_UNDEFINED = 0xFFu
}vSwUpdM_GridSrvc_ServiceIdxType;

typedef P2VAR(vSwUpdM_GridSrvc_ServiceIdxType, AUTOMATIC, VSWUPDM_APPL_VAR) vSwUpdM_GridSrvc_ServiceIdxPtrType;

/* Definition of Service Classes */
typedef enum
{
  VSWUPDM_GRIDSRVC_CLASS_NONE,
  VSWUPDM_GRIDSRVC_CLASS_SUSPEND,
  VSWUPDM_GRIDSRVC_CLASS_GENERIC,
  VSWUPDM_GRIDSRVC_CLASS_MAINTENANCE,
  VSWUPDM_GRIDSRVC_CLASS_PARTITION,
  VSWUPDM_GRIDSRVC_CLASS_MODULE,
  VSWUPDM_GRIDSRVC_CLASS_REGION,
  VSWUPDM_GRIDSRVC_CLASS_SEGMENT,
  VSWUPDM_GRIDSRVC_CLASS_PROCESS_MODULE,
  VSWUPDM_GRIDSRVC_CLASS_STREAM_INFO,
  VSWUPDM_GRIDSRVC_CLASS_SEGMENT_INFO,

  VSWUPDM_GRIDSRVC_CLASS_BK_EXEC_COMMAND,
  VSWUPDM_GRIDSRVC_CLASS_BK_GET_GENERIC,
  VSWUPDM_GRIDSRVC_CLASS_BK_GET_SEGMENT_ATTRIBUTES,
  VSWUPDM_GRIDSRVC_CLASS_BK_GET_RESUME_INFO,
  VSWUPDM_GRIDSRVC_CLASS_BK_SET_GENERIC,
  VSWUPDM_GRIDSRVC_CLASS_BK_SET_SEGMENT_ATTRIBUTES,
  VSWUPDM_GRIDSRVC_CLASS_BK_SET_RESUME_INFO,

  VSWUPDM_GRIDSRVC_CLASS_SEGMENT_COUNT,
  VSWUPDM_GRIDSRVC_CLASS_SEGMENT_UNDEFINED = 0xFFu
} SwUpdM_GridSrvc_ServiceClassType;

typedef struct vSwUpdM_GridSrvc_ServiceClassBaseType_tag vSwUpdM_GridSrvc_ServiceClassBaseType;
typedef P2VAR(vSwUpdM_GridSrvc_ServiceClassBaseType, AUTOMATIC, VSWUPDM_APPL_VAR) vSwUpdM_GridSrvc_ServiceClassBasePtrType;
typedef P2VAR(vSwUpdM_GridSrvc_ServiceClassBasePtrType, AUTOMATIC, VSWUPDM_APPL_VAR) vSwUpdM_GridSrvc_ServiceClassBasePtrPtrType;

typedef struct vSwUpdM_GridSrvc_ServiceClassNoneType_tag vSwUpdM_GridSrvc_ServiceClassNoneType;
typedef P2VAR(vSwUpdM_GridSrvc_ServiceClassNoneType, AUTOMATIC, VSWUPDM_APPL_VAR) vSwUpdM_GridSrvc_ServiceClassNonePtrType;

typedef struct vSwUpdM_GridSrvc_ServiceClassSuspendType_tag vSwUpdM_GridSrvc_ServiceClassSuspendType;
typedef P2VAR(vSwUpdM_GridSrvc_ServiceClassSuspendType, AUTOMATIC, VSWUPDM_APPL_VAR) vSwUpdM_GridSrvc_ServiceClassSuspendPtrType;

typedef struct vSwUpdM_GridSrvc_ServiceClassMainBaseType_tag vSwUpdM_GridSrvc_ServiceClassMainBaseType;
typedef P2VAR(vSwUpdM_GridSrvc_ServiceClassMainBaseType, AUTOMATIC, VSWUPDM_APPL_VAR) vSwUpdM_GridSrvc_ServiceClassMainBasePtrType;

typedef struct vSwUpdM_GridSrvc_ServiceClassGenericBaseType_tag vSwUpdM_GridSrvc_ServiceClassGenericBaseType;
typedef P2VAR(vSwUpdM_GridSrvc_ServiceClassGenericBaseType, AUTOMATIC, VSWUPDM_APPL_VAR) vSwUpdM_GridSrvc_ServiceClassGenericBasePtrType;

typedef struct vSwUpdM_GridSrvc_ServiceClassMaintenanceType_tag vSwUpdM_GridSrvc_ServiceClassMaintenanceType;
typedef P2VAR(vSwUpdM_GridSrvc_ServiceClassMaintenanceType, AUTOMATIC, VSWUPDM_APPL_VAR) vSwUpdM_GridSrvc_ServiceClassMaintenancePtrType;

typedef struct vSwUpdM_GridSrvc_ServiceClassGenericType_tag vSwUpdM_GridSrvc_ServiceClassGenericType;
typedef P2VAR(vSwUpdM_GridSrvc_ServiceClassGenericType, AUTOMATIC, VSWUPDM_APPL_VAR) vSwUpdM_GridSrvc_ServiceClassGenericPtrType;

typedef struct vSwUpdM_GridSrvc_ServiceClassPartitionType_tag vSwUpdM_GridSrvc_ServiceClassPartitionType;
typedef P2VAR(vSwUpdM_GridSrvc_ServiceClassPartitionType, AUTOMATIC, VSWUPDM_APPL_VAR) vSwUpdM_GridSrvc_ServiceClassPartitionPtrType;

typedef struct vSwUpdM_GridSrvc_ServiceClassModuleType_tag vSwUpdM_GridSrvc_ServiceClassModuleType;
typedef P2VAR(vSwUpdM_GridSrvc_ServiceClassModuleType, AUTOMATIC, VSWUPDM_APPL_VAR) vSwUpdM_GridSrvc_ServiceClassModulePtrType;

typedef struct vSwUpdM_GridSrvc_ServiceClassRegionType_tag vSwUpdM_GridSrvc_ServiceClassRegionType;
typedef P2VAR(vSwUpdM_GridSrvc_ServiceClassRegionType, AUTOMATIC, VSWUPDM_APPL_VAR) vSwUpdM_GridSrvc_ServiceClassRegionPtrType;

typedef struct vSwUpdM_GridSrvc_ServiceClassSegmentType_tag vSwUpdM_GridSrvc_ServiceClassSegmentType;
typedef P2VAR(vSwUpdM_GridSrvc_ServiceClassSegmentType, AUTOMATIC, VSWUPDM_APPL_VAR) vSwUpdM_GridSrvc_ServiceClassSegmentPtrType;

typedef struct vSwUpdM_GridSrvc_ServiceClassProcessModuleType_tag vSwUpdM_GridSrvc_ServiceClassProcessModuleType;
typedef P2VAR(vSwUpdM_GridSrvc_ServiceClassProcessModuleType, AUTOMATIC, VSWUPDM_APPL_VAR) vSwUpdM_GridSrvc_ServiceClassProcessModulePtrType;
typedef P2CONST(vSwUpdM_GridSrvc_ServiceClassProcessModuleType, AUTOMATIC, VSWUPDM_APPL_VAR) vSwUpdM_GridSrvc_ServiceClassProcessModuleConstPtrType;

typedef struct vSwUpdM_GridSrvc_ServiceClassStreamInfoType_tag vSwUpdM_GridSrvc_ServiceClassStreamInfoType;
typedef P2VAR(vSwUpdM_GridSrvc_ServiceClassStreamInfoType, AUTOMATIC, VSWUPDM_APPL_VAR) vSwUpdM_GridSrvc_ServiceClassStreamInfoPtrType;

typedef struct vSwUpdM_GridSrvc_ServiceClassSegmentInfoType_tag vSwUpdM_GridSrvc_ServiceClassSegmentInfoType;
typedef P2VAR(vSwUpdM_GridSrvc_ServiceClassSegmentInfoType, AUTOMATIC, VSWUPDM_APPL_VAR) vSwUpdM_GridSrvc_ServiceClassSegmentInfoPtrType;

typedef struct vSwUpdM_GridSrvc_ServiceClassBkGenericBaseType_tag vSwUpdM_GridSrvc_ServiceClassBkGenericBaseType;
typedef P2VAR(vSwUpdM_GridSrvc_ServiceClassBkGenericBaseType, AUTOMATIC, VSWUPDM_APPL_VAR) vSwUpdM_GridSrvc_ServiceClassBkGenericBasePtrType;

typedef struct vSwUpdM_GridSrvc_ServiceClassBkExecCommandType_tag vSwUpdM_GridSrvc_ServiceClassBkExecCommandType;
typedef P2VAR(vSwUpdM_GridSrvc_ServiceClassBkExecCommandType, AUTOMATIC, VSWUPDM_APPL_VAR) vSwUpdM_GridSrvc_ServiceClassBkExecCommandPtrType;

typedef struct vSwUpdM_GridSrvc_ServiceClassBkGenericIoBaseType_tag vSwUpdM_GridSrvc_ServiceClassBkGenericIoBaseType;
typedef P2VAR(vSwUpdM_GridSrvc_ServiceClassBkGenericIoBaseType, AUTOMATIC, VSWUPDM_APPL_VAR) vSwUpdM_GridSrvc_ServiceClassBkGenericIoBasePtrType;

typedef struct vSwUpdM_GridSrvc_ServiceClassBkSetGenericParameterType_tag vSwUpdM_GridSrvc_ServiceClassBkSetGenericParameterType;
typedef P2VAR(vSwUpdM_GridSrvc_ServiceClassBkSetGenericParameterType, AUTOMATIC, VSWUPDM_APPL_VAR) vSwUpdM_GridSrvc_ServiceClassBkSetGenericParameterPtrType;

typedef struct vSwUpdM_GridSrvc_ServiceClassBkGetGenericParameterType_tag vSwUpdM_GridSrvc_ServiceClassBkGetGenericParameterType;
typedef P2VAR(vSwUpdM_GridSrvc_ServiceClassBkGetGenericParameterType, AUTOMATIC, VSWUPDM_APPL_VAR) vSwUpdM_GridSrvc_ServiceClassBkGetGenericParameterPtrType;

typedef struct vSwUpdM_GridSrvc_ServiceClassBkGetResumeInfoType_tag vSwUpdM_GridSrvc_ServiceClassBkGetResumeInfoType;
typedef P2VAR(vSwUpdM_GridSrvc_ServiceClassBkGetResumeInfoType, AUTOMATIC, VSWUPDM_APPL_VAR) vSwUpdM_GridSrvc_ServiceClassBkGetResumeInfoPtrType;

typedef struct vSwUpdM_GridSrvc_ServiceClassBkGetSegmentAttributesType_tag vSwUpdM_GridSrvc_ServiceClassBkGetSegmentAttributesType;
typedef P2VAR(vSwUpdM_GridSrvc_ServiceClassBkGetSegmentAttributesType, AUTOMATIC, VSWUPDM_APPL_VAR) vSwUpdM_GridSrvc_ServiceClassBkGetSegmentAttributesPtrType;

typedef struct vSwUpdM_GridSrvc_ServiceClassBkSetSegmentAttributesType_tag vSwUpdM_GridSrvc_ServiceClassBkSetSegmentAttributesType;
typedef P2VAR(vSwUpdM_GridSrvc_ServiceClassBkSetSegmentAttributesType, AUTOMATIC, VSWUPDM_APPL_VAR) vSwUpdM_GridSrvc_ServiceClassBkSetSegmentAttributesPtrType;

typedef struct vSwUpdM_GridSrvc_ServiceClassBkSetResumeInfoType_tag vSwUpdM_GridSrvc_ServiceClassBkSetResumeInfoType;
typedef P2VAR(vSwUpdM_GridSrvc_ServiceClassBkSetResumeInfoType, AUTOMATIC, VSWUPDM_APPL_VAR) vSwUpdM_GridSrvc_ServiceClassBkSetResumeInfoPtrType;

typedef struct vSwUpdM_GridSrvc_ResponseClassBaseType_tag vSwUpdM_GridSrvc_ResponseClassBaseType;
typedef P2VAR(vSwUpdM_GridSrvc_ResponseClassBaseType, AUTOMATIC, VSWUPDM_APPL_VAR) vSwUpdM_GridSrvc_ResponseClassBasePtrType;

/* Definition of GridSrvc Response Class types (for providing buffers for reception of responses). */

typedef enum
{
  VSWUPDM_GRIDSRVC_RESPONSECLASS_MAIN,
  VSWUPDM_GRIDSRVC_RESPONSECLASS_MAINTENANCE,
  VSWUPDM_GRIDSRVC_RESPONSECLASS_SUSPEND,
  VSWUPDM_GRIDSRVC_RESPONSECLASS_BK,
  VSWUPDM_GRIDSRVC_RESPONSECLASS_BK_GET,
  VSWUPDM_GRIDSRVC_RESPONSECLASS_BK_GET_SEGMENT_ATTRIBUTES,
  VSWUPDM_GRIDSRVC_RESPONSECLASS_BK_GET_RESUME_INFO,
  VSWUPDM_GRIDSRVC_RESPONSECLASS_LEGACY,
  VSWUPDM_GRIDSRVC_RESPONSECLASS_COUNT,
  VSWUPDM_GRIDSRVC_RESPONSECLASS_NONE = 0xFFu
}vSwUpdM_GridSrvc_ResponseClassIdxType;

typedef struct vSwUpdM_GridSrvc_ResponseClassSimpleResponseType_tag vSwUpdM_GridSrvc_ResponseClassSimpleResponseType;
typedef P2VAR(vSwUpdM_GridSrvc_ResponseClassSimpleResponseType, AUTOMATIC, VSWUPDM_APPL_VAR) vSwUpdM_GridSrvc_ResponseClassSimpleResponsePtrType;

typedef struct vSwUpdM_GridSrvc_ResponseClassSimpleResponseType_tag vSwUpdM_GridSrvc_ResponseClassMainType;
typedef P2VAR(vSwUpdM_GridSrvc_ResponseClassMainType, AUTOMATIC, VSWUPDM_APPL_VAR) vSwUpdM_GridSrvc_ResponseClassMainPtrType;

typedef struct vSwUpdM_GridSrvc_ResponseClassSimpleResponseType_tag vSwUpdM_GridSrvc_ResponseClassMaintenanceType;
typedef P2VAR(vSwUpdM_GridSrvc_ResponseClassMaintenanceType, AUTOMATIC, VSWUPDM_APPL_VAR) vSwUpdM_GridSrvc_ResponseClassMaintenancePtrType;

typedef struct vSwUpdM_GridSrvc_ResponseClassSimpleResponseType_tag vSwUpdM_GridSrvc_ResponseClassSuspendType;
typedef P2VAR(vSwUpdM_GridSrvc_ResponseClassSuspendType, AUTOMATIC, VSWUPDM_APPL_VAR) vSwUpdM_GridSrvc_ResponseClassSuspendPtrType;

/* Definition of GridRpc Response Class types (for transmission of responses). */

typedef enum
{
  VSWUPDM_GRIDRPC_COMPLEXREPONSECLASS_SIMPLE,
  VSWUPDM_GRIDRPC_COMPLEXREPONSECLASS_BK_GET_GENERIC_PARAMETER,
  VSWUPDM_GRIDRPC_COMPLEXREPONSECLASS_BK_GET_SEGMENT_ATTRIBUTES,
  VSWUPDM_GRIDRPC_COMPLEXREPONSECLASS_BK_GET_RESUME_INFO,

  VSWUPDM_GRIDRPC_COMPLEXREPONSECLASS_COUNT,
  VSWUPDM_GRIDRPC_COMPLEXREPONSECLASS_UNDEFINED = 0xFFu
} vSwUpdM_GridRpc_ComplexResponseClassType;

typedef enum
{
  VSWUPDM_GRIDRPC_SERVICEXECUTIONSTATE_PENDING,
  VSWUPDM_GRIDRPC_SERVICEXECUTIONSTATE_FINISHED
} vSwUpdM_GridRpc_ServiceExecutionStateType;

typedef struct vSwUpdM_GridRpc_ComplexResponseClassBaseType_tag vSwUpdM_GridRpc_ComplexResponseClassBaseType;
typedef P2VAR(vSwUpdM_GridRpc_ComplexResponseClassBaseType, AUTOMATIC, VSWUPDM_APPL_VAR) vSwUpdM_GridRpc_ComplexResponseClassBasePtrType;

typedef struct vSwUpdM_GridRpc_ComplexResponseClassSimpleType_tag vSwUpdM_GridRpc_ComplexResponseClassSimpleType;
typedef P2VAR(vSwUpdM_GridRpc_ComplexResponseClassSimpleType, AUTOMATIC, VSWUPDM_APPL_VAR) vSwUpdM_GridRpc_ComplexResponseClassSimplePtrType;

typedef struct vSwUpdM_GridSrvc_ResponseClassSimpleResponseType_tag vSwUpdM_GridSrvc_ResponseClassBookkeeperType;
typedef P2VAR(vSwUpdM_GridSrvc_ResponseClassBookkeeperType, AUTOMATIC, VSWUPDM_APPL_VAR) vSwUpdM_GridSrvc_ResponseClassBookkeeperPtrType;

typedef struct vSwUpdM_GridRpc_ComplexResponseClassBkGetGenericType_tag vSwUpdM_GridRpc_ComplexResponseClassBkGetGenericType;
typedef P2VAR(vSwUpdM_GridRpc_ComplexResponseClassBkGetGenericType, AUTOMATIC, VSWUPDM_APPL_VAR) vSwUpdM_GridRpc_ComplexResponseClassBkGetGenericPtrType;

typedef struct vSwUpdM_GridRpc_ComplexResponseClassBkGetSegmentAttributesType_tag vSwUpdM_GridRpc_ComplexResponseClassBkGetSegmentAttributesType;
typedef P2VAR(vSwUpdM_GridRpc_ComplexResponseClassBkGetSegmentAttributesType, AUTOMATIC, VSWUPDM_APPL_VAR) vSwUpdM_GridRpc_ComplexResponseClassBkGetSegmentAttributesPtrType;

typedef struct vSwUpdM_GridRpc_ComplexResponseClassBkGetResumeInfoType_tag vSwUpdM_GridRpc_ComplexResponseClassBkGetResumeInfoType;
typedef P2VAR(vSwUpdM_GridRpc_ComplexResponseClassBkGetResumeInfoType, AUTOMATIC, VSWUPDM_APPL_VAR) vSwUpdM_GridRpc_ComplexResponseClassBkGetResumeInfoPtrType;

typedef enum
{
  VSWUPDM_GRIDSRVC_SERVICESTATE_PENDING,
  VSWUPDM_GRIDSRVC_SERVICESTATE_FINISHED,
  VSWUPDM_GRIDSRVC_SERVICESTATE_SUSPENDED
} vSwUpdM_GridSrvc_ServiceStateType;

typedef struct vSwUpdM_GridSrvc_ServiceType_tag vSwUpdM_GridSrvc_ServiceType;

/*********************
 * LEGACY
 ********************/

typedef enum
{
  VSWUPDM_REMOTE_TX_ERROR_HANDLER_NONE,
  VSWUPDM_REMOTE_TX_ERROR_HANDLER_CONFIRMATION,
  VSWUPDM_REMOTE_TX_ERROR_HANDLER_STREAM,
  VSWUPDM_REMOTE_TX_ERROR_HANDLER_PROC_STREAM,
  VSWUPDM_REMOTE_TX_ERROR_HANDLER_ABORT_WAIT
}vSwUpdM_RemoteTxErrorHandlerType;               /* Legacy Remote error handling. */

typedef struct vSwUpdM_RemoteServiceDefinitionType_Tag vSwUpdM_RemoteServiceDefinitionType;

/***********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 **********************************************************************************************************************/

#endif  /* VSWUPDM_GRID_TYPES_H */

/***********************************************************************************************************************
 *  END OF FILE: vSwUpdM_Grid_Types.h
 **********************************************************************************************************************/
