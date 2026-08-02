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
/*!        \file  vSwUpdM_Grid_If.h
 *        \brief  vSwUpdM_Grid interface header file
 *      \details  Interface provided by the vSwUpdM_Grid subcomponent.
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's main header file.
 *
 *  FILE VERSION
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's main header file vSwUpdM.h.
 *********************************************************************************************************************/

#if !defined (VSWUPDM_GRID_IF_H)
# define VSWUPDM_GRID_IF_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
/* Grid types header */
#include "vSwUpdM_Grid_Types.h"

/* Other MultipleUnits used by Grid_If (Prefer smallest set required, i.e. prefer _Types over _If) */
#include "vSwUpdM_ExecCtrl_Types.h"
#include "vSwUpdM_Priv_Types.h"
#include "vSwUpdM_Bookkeeper_If.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

 /* Definition of invalid values  */
#define VSWUPDM_INVALID_NODE        vSwUpdM_GetSizeOfNode()
#define VSWUPDM_INVALID_NODE_GROUP  vSwUpdM_GetSizeOfNodeGroup() /* Undefined (Remote) Instance Group */

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

 /*********************
 * GRID CHANNEL
 ********************/

/*********************
 * GRID RPC
 ********************/

/*********************
 * GRID SERVICE
 ********************/

struct vSwUpdM_GridSrvc_ServiceClassBaseType_tag
{
  SwUpdM_GridSrvc_ServiceClassType ServiceClass;
};

struct vSwUpdM_GridSrvc_ServiceClassNoneType_tag
{
  vSwUpdM_GridSrvc_ServiceClassBaseType Base;
};

struct vSwUpdM_GridSrvc_ServiceClassSuspendType_tag
{
  vSwUpdM_GridSrvc_ServiceClassBaseType Base;
  vSwUpdM_GridSrvc_ServiceIdxType       ServiceIndex;
};

struct vSwUpdM_GridSrvc_ServiceClassMainBaseType_tag
{
  vSwUpdM_GridSrvc_ServiceClassBaseType Base;
  vSwUpdM_ExctSchedule_ServiceStateType ServiceState;
};

struct vSwUpdM_GridSrvc_ServiceClassGenericBaseType_tag
{
  vSwUpdM_GridSrvc_ServiceClassMainBaseType Base;
  vSwUpdM_GridSrvc_ServiceIdxType           ServiceIndex;
};

struct vSwUpdM_GridSrvc_ServiceClassMaintenanceType_tag
{
  vSwUpdM_GridSrvc_ServiceClassGenericBaseType GenericBase;
};

struct vSwUpdM_GridSrvc_ServiceClassGenericType_tag
{
  vSwUpdM_GridSrvc_ServiceClassGenericBaseType GenericBase;
};

struct vSwUpdM_GridSrvc_ServiceClassPartitionType_tag
{
  vSwUpdM_GridSrvc_ServiceClassGenericBaseType GenericBase;
  vSwUpdM_PartitionStateType PartitionState;
};

struct vSwUpdM_GridSrvc_ServiceClassModuleType_tag
{
  vSwUpdM_GridSrvc_ServiceClassGenericBaseType GenericBase;
  vSwUpdM_ModuleIdType ModuleId;
};

struct vSwUpdM_GridSrvc_ServiceClassRegionType_tag
{
  vSwUpdM_GridSrvc_ServiceClassGenericBaseType GenericBase;
  vSwUpdM_RegionIdType RegionId;
};

struct vSwUpdM_GridSrvc_ServiceClassSegmentType_tag
{
  vSwUpdM_GridSrvc_ServiceClassGenericBaseType GenericBase;
  vSwUpdM_SegmentIdType SegmentId;
};

struct vSwUpdM_GridSrvc_ServiceClassProcessModuleType_tag
{
  vSwUpdM_GridSrvc_ServiceClassGenericBaseType GenericBase;
  vSwUpdM_ModuleIdType ModuleId;
  vSwUpdM_ProcessInfoType ProcessInfo;
  vSwUpdM_ProcessIdType ProcessId;
};

struct vSwUpdM_GridSrvc_ServiceClassStreamInfoType_tag
{
  vSwUpdM_GridSrvc_ServiceClassMainBaseType Base;
  vSwUpdM_StreamInfoType StreamInfo;
};

struct vSwUpdM_GridSrvc_ServiceClassSegmentInfoType_tag
{
  vSwUpdM_GridSrvc_ServiceClassMainBaseType Base;
  /*!
   * Internal comment removed.
 *
 *
   */
  vSwUpdM_RemoteSegmentInfoType SegmentInfo;
};

struct vSwUpdM_GridSrvc_ServiceClassBkGenericBaseType_tag
{
  vSwUpdM_GridSrvc_ServiceClassBaseType Base;
};

struct vSwUpdM_GridSrvc_ServiceClassBkExecCommandType_tag
{
  vSwUpdM_GridSrvc_ServiceClassBkGenericBaseType Base;
  vSwUpdM_BkPersist_GenericServiceCommandType Command;
};

struct vSwUpdM_GridSrvc_ServiceClassBkGenericIoBaseType_tag
{
  vSwUpdM_GridSrvc_ServiceClassBkGenericBaseType Base;
  P2CONST(vSwUpdM_BkPersist_EntityType, AUTOMATIC, VSWUPDM_APPL_CONST) Entities;
  vSwUpdM_BkPersist_ParamType ParamType;
};

struct vSwUpdM_GridSrvc_ServiceClassBkSetGenericParameterType_tag
{
  vSwUpdM_GridSrvc_ServiceClassBkGenericIoBaseType Base;
  vSwUpdM_BkPersist_GenericParameterType GenericValue;
  boolean SyncFlag;
};

struct vSwUpdM_GridSrvc_ServiceClassBkGetGenericParameterType_tag
{
  vSwUpdM_GridSrvc_ServiceClassBkGenericIoBaseType Base;
};

struct vSwUpdM_GridSrvc_ServiceClassBkGetResumeInfoType_tag
{
  vSwUpdM_GridSrvc_ServiceClassBkGenericBaseType Base;
};

struct vSwUpdM_GridSrvc_ServiceClassBkGetSegmentAttributesType_tag
{
  vSwUpdM_GridSrvc_ServiceClassBkGenericBaseType Base;
  P2CONST(vSwUpdM_BkPersist_EntityType, AUTOMATIC, VSWUPDM_APPL_CONST) Entities;
};

struct vSwUpdM_GridSrvc_ServiceClassBkSetSegmentAttributesType_tag
{
  vSwUpdM_GridSrvc_ServiceClassBkGenericBaseType Base;
  P2CONST(vSwUpdM_BkPersist_EntityType, AUTOMATIC, VSWUPDM_APPL_CONST) Entities;
  P2CONST(vSwUpdM_BkPersist_SegmentAttributesType, AUTOMATIC, VSWUPDM_APPL_CONST) SegmentAttributes;
  boolean SyncFlag;
};

struct vSwUpdM_GridSrvc_ServiceClassBkSetResumeInfoType_tag
{
  vSwUpdM_GridSrvc_ServiceClassBkGenericBaseType Base;
  vSwUpdM_BkPersist_ResumeInfoType ResumeInfo;
  boolean SyncFlag;
};

struct vSwUpdM_GridSrvc_ResponseClassBaseType_tag
{
  vSwUpdM_GridSrvc_ResponseClassIdxType ResponseClassIndex;
  vSwUpdM_GridChannel_ServiceStateType ServiceState;
};

struct vSwUpdM_GridSrvc_ResponseClassSimpleResponseType_tag
{
  vSwUpdM_GridSrvc_ResponseClassBaseType Base;
  boolean ResultValid;
  Std_ReturnType Result;
};

struct vSwUpdM_GridRpc_ComplexResponseClassBaseType_tag
{
  vSwUpdM_GridRpc_ComplexResponseClassType ComplexResponseClassType;
  vSwUpdM_GridSrvc_ServiceIdxType RequestServiceIdx;
  Std_ReturnType Result;
};

struct vSwUpdM_GridRpc_ComplexResponseClassSimpleType_tag
{
  vSwUpdM_GridRpc_ComplexResponseClassBaseType Base;
};

struct vSwUpdM_GridRpc_ComplexResponseClassBkGetGenericType_tag
{
  vSwUpdM_GridRpc_ComplexResponseClassBaseType Base;
  vSwUpdM_BkPersist_GenericParameterType GenericValue;
};

struct vSwUpdM_GridRpc_ComplexResponseClassBkGetSegmentAttributesType_tag
{
  vSwUpdM_GridRpc_ComplexResponseClassBaseType Base;
  P2CONST(vSwUpdM_BkPersist_SegmentAttributesType, AUTOMATIC, VSWUPDM_APPL_CONST) SegmentAttributes;
};

struct vSwUpdM_GridRpc_ComplexResponseClassBkGetResumeInfoType_tag
{
  vSwUpdM_GridRpc_ComplexResponseClassBaseType Base;
  P2CONST(vSwUpdM_BkPersist_ResumeInfoType, AUTOMATIC, VSWUPDM_APPL_CONST) ResumeInfo;
};

 struct vSwUpdM_GridSrvc_ServiceType_tag
{
  SwUpdM_GridSrvc_ServiceClassType         ServiceClass;
  vSwUpdM_GridSrvc_ResponseClassIdxType    ResponseClassIndex;
};

/*********************
 * LEGACY
 ********************/

struct vSwUpdM_RemoteServiceDefinitionType_Tag
{
  vSwUpdM_GridSrvc_ServiceIdxType  RemoteServiceIndex;
  vSwUpdM_ServiceIdType            ApiServiceId;
  Std_ReturnType                   ErrorCode;
  vSwUpdM_RemoteTxErrorHandlerType TxErrorHandlerType;
};

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/
#define VSWUPDM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

extern CONST(vSwUpdM_GridSrvc_ServiceClassBasePtrType, VSWUPDM_APPL_DATA) vSwUpdM_GridChannel_RequestBuffer[VSWUPDM_GRIDCHANNEL_CHANNELIDX_COUNT];

#define VSWUPDM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
# define VSWUPDM_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  Global Inline Functions
 *********************************************************************************************************************/

/****************************
 * GRID
 ***************************/
/**********************************************************************************************************************
 *  vSwUpdM_Grid_LocalNodeIsChild()
 *********************************************************************************************************************/
/*! \brief       Checks if the local node currently acts as a child for a remote parent node.
 *  \details     Checks if the lock is granted to another node.
 *  \return      TRUE   If the local node is a child node.
 *  \return      FALSE  Otherwise.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     remote
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(boolean, VSWUPDM_CODE) vSwUpdM_Grid_LocalNodeIsChild(void);

/**********************************************************************************************************************
 *  vSwUpdM_Grid_LocalNodeIsParent()
 *********************************************************************************************************************/
/*! \brief       Checks if the local node currently acts as a parent for a remote child node.
 *  \details     Checks if a lock has been acquired.
 *  \return      TRUE   If the local node is a parent node.
 *  \return      FALSE  Otherwise.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     remote
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(boolean, VSWUPDM_CODE) vSwUpdM_Grid_LocalNodeIsParent(void);

/*********************
 * GRID SERVICE
 ********************/

/**************************
 * ServiceRequest classes
 *************************/

/**********************************************************************************************************************
 * vSwUpdM_Grid_InitServiceClassSuspend
 *********************************************************************************************************************/
/*! \brief          "Constructor" function for ServiceClassSuspend
 *  \details        Provide initialization for ServiceClass.
 *  \param[in]      ServiceIndex        Requested service.
 *  \param[in,out]  GenericServiceClass Initialized ServiceClass structure.
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *  \ingroup        GridSrvc
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_Grid_InitServiceClassSuspend( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_GridSrvc_ServiceIdxType ServiceIndex,
  vSwUpdM_GridSrvc_ServiceClassSuspendPtrType ServiceClass);

/**********************************************************************************************************************
 * vSwUpdM_Grid_InitServiceClassGenericBase
 *********************************************************************************************************************/
/*! \brief          "Constructor" function for ServiceClassGenericBase
 *  \details        Provide initialization for ServiceClass.
 *  \param[in]      ServiceState        Requested state of service.
 *  \param[in]      ServiceIndex        Requested service.
 *  \param[in]      ServiceClass        Desired ServiceClass child of ServiceClassBkGenericBase.
 *  \param[in,out]  GenericServiceClass Initialized ServiceClass structure.
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *  \ingroup        GridSrvc
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_Grid_InitServiceClassGenericBase( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_ExctSchedule_ServiceStateType ServiceState,
  vSwUpdM_GridSrvc_ServiceIdxType ServiceIndex,
  SwUpdM_GridSrvc_ServiceClassType ServiceClass,
  vSwUpdM_GridSrvc_ServiceClassGenericBasePtrType GenericServiceClass);

/**********************************************************************************************************************
 * vSwUpdM_Grid_InitServiceClassMaintenance
 *********************************************************************************************************************/
/*! \brief          "Constructor" function for ServiceClassMaintenance
 *  \details        Provide initialization for ServiceClass.
 *  \param[in]      ServiceState   Requested state of service.
 *  \param[in]      ServiceIndex   Requested service.
 *  \param[in,out]  ServiceClass   Initialized ServiceClass structure.
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *  \ingroup        GridSrvc
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_Grid_InitServiceClassMaintenance( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_ExctSchedule_ServiceStateType ServiceState,
  vSwUpdM_GridSrvc_ServiceIdxType ServiceIndex,
  vSwUpdM_GridSrvc_ServiceClassMaintenancePtrType ServiceClass);

/**********************************************************************************************************************
 * vSwUpdM_Grid_InitServiceClassGeneric
 *********************************************************************************************************************/
/*! \brief          "Constructor" function for ServiceClassGeneral
 *  \details        Provide initialization for ServiceClass.
 *  \param[in]      ServiceState   Requested state of service.
 *  \param[in]      ServiceIndex   Requested service.
 *  \param[in,out]  ServiceClass   Initialized ServiceClass structure.
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *  \ingroup        GridSrvc
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_Grid_InitServiceClassGeneric(
  vSwUpdM_ExctSchedule_ServiceStateType ServiceState,
  vSwUpdM_GridSrvc_ServiceIdxType ServiceIndex,
  vSwUpdM_GridSrvc_ServiceClassGenericPtrType ServiceClass);

/**********************************************************************************************************************
 * vSwUpdM_Grid_InitServiceClassPartition
 *********************************************************************************************************************/
/*! \brief          "Constructor" function for ServiceClassPartition
 *  \details        Provide initialization for ServiceClass.
 *  \param[in]      ServiceState    Requested state of service.
 *  \param[in]      ServiceIndex    Requested service.
 *  \param[in]      PartitionState  State of partition.
 *  \param[in,out]  ServiceClass    Initialized ServiceClass structure.
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *  \ingroup        GridSrvc
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_Grid_InitServiceClassPartition(
  vSwUpdM_ExctSchedule_ServiceStateType ServiceState,
  vSwUpdM_GridSrvc_ServiceIdxType ServiceIndex,
  vSwUpdM_PartitionStateType PartitionState,
  vSwUpdM_GridSrvc_ServiceClassPartitionPtrType ServiceClass);

/**********************************************************************************************************************
 * vSwUpdM_Grid_InitServiceClassModule
 *********************************************************************************************************************/
/*! \brief          "Constructor" function for ServiceClassModule
 *  \details        Provide initialization for ServiceClass.
 *  \param[in]      ServiceState   Requested state of service.
 *  \param[in]      ServiceIndex   Requested service.
 *  \param[in]      ModuleId       ID of module.
 *  \param[in,out]  ServiceClass   Initialized ServiceClass structure.
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *  \ingroup        GridSrvc
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_Grid_InitServiceClassModule(
  vSwUpdM_ExctSchedule_ServiceStateType ServiceState,
  vSwUpdM_GridSrvc_ServiceIdxType ServiceIndex,
  vSwUpdM_ModuleIdType ModuleId,
  vSwUpdM_GridSrvc_ServiceClassModulePtrType ServiceClass);

/**********************************************************************************************************************
 * vSwUpdM_Grid_InitServiceClassRegion
 *********************************************************************************************************************/
/*! \brief          "Constructor" function for ServiceClassRegion
 *  \details        Provide initialization for ServiceClass.
 *  \param[in]      ServiceState   Requested state of service.
 *  \param[in]      ServiceIndex   Requested service.
 *  \param[in]      RegionId       ID of region.
 *  \param[in,out]  ServiceClass   Initialized ServiceClass structure.
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *  \ingroup        GridSrvc
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_Grid_InitServiceClassRegion(
  vSwUpdM_ExctSchedule_ServiceStateType ServiceState,
  vSwUpdM_GridSrvc_ServiceIdxType ServiceIndex,
  vSwUpdM_RegionIdType RegionId,
  vSwUpdM_GridSrvc_ServiceClassRegionPtrType ServiceClass);

/**********************************************************************************************************************
 * vSwUpdM_Grid_InitServiceClassSegment
 *********************************************************************************************************************/
/*! \brief          "Constructor" function for ServiceClassSegment
 *  \details        Provide initialization for ServiceClass.
 *  \param[in]      ServiceState   Requested state of service.
 *  \param[in]      ServiceIndex   Requested service.
 *  \param[in]      SegmentId      ID of segment.
 *  \param[in,out]  ServiceClass   Initialized ServiceClass structure.
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *  \ingroup        GridSrvc
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_Grid_InitServiceClassSegment(
  vSwUpdM_ExctSchedule_ServiceStateType ServiceState,
  vSwUpdM_GridSrvc_ServiceIdxType ServiceIndex,
  vSwUpdM_SegmentIdType SegmentId,
  vSwUpdM_GridSrvc_ServiceClassSegmentPtrType ServiceClass);

/**********************************************************************************************************************
 * vSwUpdM_Grid_InitServiceClassProcessModule
 *********************************************************************************************************************/
/*! \brief          "Constructor" function for ServiceClassProcessModule
 *  \details        Provide initialization for ServiceClass.
 *  \param[in]      ServiceState  Requested state of service.
 *  \param[in]      ServiceIndex  Requested service.
 *  \param[in]      ModuleId      ID of module.
 *  \param[in]      ProcessId     ID of requested data process.
 *  \param[in]      ProcessInfo   Describes parameters for ProcessModuleService.
 *  \param[in,out]  ServiceClass  Initialized ServiceClass structure.
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *  \ingroup        GridSrvc
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_Grid_InitServiceClassProcessModule(
  vSwUpdM_ExctSchedule_ServiceStateType ServiceState,
  vSwUpdM_GridSrvc_ServiceIdxType ServiceIndex,
  vSwUpdM_ModuleIdType ModuleId,
  vSwUpdM_ProcessIdType ProcessId,
  P2VAR(vSwUpdM_ProcessInfoType, AUTOMATIC, VSWUPDM_APPL_VAR) ProcessInfo,
  vSwUpdM_GridSrvc_ServiceClassProcessModulePtrType ServiceClass);

/**********************************************************************************************************************
 * vSwUpdM_Grid_InitServiceClassStreamInfo
 *********************************************************************************************************************/
/*! \brief          "Constructor" function for ServiceClassStreamInfo
 *  \details        Provide initialization for ServiceClass.
 *  \param[in]      ServiceState  Requested state of service.
 *  \param[in]      StreamInfo    Describes parameters for Stream.
 *  \param[in,out]  ServiceClass  Initialized ServiceClass structure.
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *  \ingroup        GridSrvc
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_Grid_InitServiceClassStreamInfo(
  vSwUpdM_ExctSchedule_ServiceStateType ServiceState,
  P2VAR(vSwUpdM_StreamInfoType, AUTOMATIC, VSWUPDM_APPL_VAR) StreamInfo,
  vSwUpdM_GridSrvc_ServiceClassStreamInfoPtrType ServiceClass);

/**********************************************************************************************************************
 * vSwUpdM_Grid_InitServiceClassSegmentInfo
 *********************************************************************************************************************/
/*! \brief          "Constructor" function for ServiceClassSegmentInfo
 *  \details        Provide initialization for ServiceClass.
 *  \param[in]      ServiceState  Requested state of service.
 *  \param[in]      SegmentInfo   Describes parameters for AddSegment RPC.
 *  \param[in,out]  ServiceClass  Initialized ServiceClass structure.
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *  \ingroup        GridSrvc
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_Grid_InitServiceClassSegmentInfo(
  vSwUpdM_ExctSchedule_ServiceStateType ServiceState,
  P2VAR(vSwUpdM_RemoteSegmentInfoType, AUTOMATIC, VSWUPDM_APPL_VAR) SegmentInfo,
  vSwUpdM_GridSrvc_ServiceClassSegmentInfoPtrType ServiceClass);

/**********************************************************************************************************************
 * vSwUpdM_Grid_InitServiceClassBkGenericBase
 *********************************************************************************************************************/
/*! \brief          "Constructor" function for ServiceClassBkGenericBase
 *  \details        Provide initialization for ServiceClass.
 *  \param[in]      ServiceClass          Desired ServiceClass child of ServiceClassBkGenericBase.
 *  \param[in,out]  ServiceClassBkGeneric Initialized ServiceClass structure.
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *  \ingroup        GridSrvc
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_Grid_InitServiceClassBkGenericBase( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  SwUpdM_GridSrvc_ServiceClassType ServiceClass,
  vSwUpdM_GridSrvc_ServiceClassBkGenericBasePtrType ServiceClassBkGeneric);

/**********************************************************************************************************************
 * vSwUpdM_Grid_InitServiceClassBkExecCommand
 *********************************************************************************************************************/
/*! \brief          "Constructor" function for ServiceClassBkExecCommand
 *  \details        Provide initialization for ServiceClass.
 *  \param[in]      Command                   Command value.
 *  \param[in,out]  ServiceClassBkExecCommand Initialized ServiceClass structure.
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *  \ingroup        GridSrvc
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_Grid_InitServiceClassBkExecCommand( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_BkPersist_GenericServiceCommandType Command,
  vSwUpdM_GridSrvc_ServiceClassBkExecCommandPtrType ServiceClassBkExecCommand);

/**********************************************************************************************************************
 * vSwUpdM_Grid_InitServiceClassBkSetResumeInfo
 *********************************************************************************************************************/
/*! \brief          "Constructor" function for ServiceClassBkSetResumeInfo
 *  \details        Provide initialization for ServiceClass.
 *  \param[in]      ExtendedResumeInfo          ResumeInfo to persist.
 *  \param[in]      SyncFlag                    Flag indicates whether a NvM synchronization is required or not.
 *  \param[in,out]  ServiceClassBkSetResumeInfo Initialized ServiceClass structure.
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *  \ingroup        GridSrvc
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_Grid_InitServiceClassBkSetResumeInfo( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  P2CONST(vSwUpdM_ExtendedResumeInfoType, AUTOMATIC, VSWUPDM_APPL_CONST) ExtendedResumeInfo,
  boolean SyncFlag,
  vSwUpdM_GridSrvc_ServiceClassBkSetResumeInfoPtrType ServiceClassBkSetResumeInfo);
/**********************************************************************************************************************
 * vSwUpdM_Grid_InitServiceClassBkSetSegmentAttributes
 *********************************************************************************************************************/
/*! \brief          "Constructor" function for ServiceClassBkSetSegmentAttributes
 *  \details        Provide initialization for ServiceClass.
 *  \param[in]      Entities                           Entities describing request.
 *  \param[in]      SegmentAttributes                  Segment attributes to persist.
 *  \param[in]      SyncFlag                           Flag indicates whether a NvM synchronization is required or not.
 *  \param[in,out]  ServiceClassBkSetSegmentAttributes Initialized ServiceClass structure.
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *  \ingroup        GridSrvc
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_Grid_InitServiceClassBkSetSegmentAttributes( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  P2CONST(vSwUpdM_BkPersist_EntityType, AUTOMATIC, VSWUPDM_APPL_CONST) Entities,
  P2CONST(vSwUpdM_BkPersist_SegmentAttributesType, AUTOMATIC, VSWUPDM_APPL_CONST) SegmentAttributes,
  boolean SyncFlag,
  vSwUpdM_GridSrvc_ServiceClassBkSetSegmentAttributesPtrType ServiceClassBkSetSegmentAttributes);

/**********************************************************************************************************************
 * vSwUpdM_Grid_InitServiceClassBkGenericIoBase
 *********************************************************************************************************************/
/*! \brief          "Constructor" function for ServiceClassBkGenericIo
 *  \details        Provide initialization for ServiceClass.
 *  \param[in]      Entities                Entities describing request.
 *  \param[in]      ParamType               Parameter type to persist.
 *  \param[in]      ServiceClass            Desired ServiceClass child of ServiceClassBkGenericBase.
 *  \param[in,out]  ServiceClassBkGenericIo Initialized ServiceClass structure.
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *  \ingroup        GridSrvc
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_Grid_InitServiceClassBkGenericIoBase( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  P2CONST(vSwUpdM_BkPersist_EntityType, AUTOMATIC, VSWUPDM_APPL_CONST) Entities,
  vSwUpdM_BkPersist_ParamType ParamType,
  SwUpdM_GridSrvc_ServiceClassType ServiceClass,
  vSwUpdM_GridSrvc_ServiceClassBkGenericIoBasePtrType ServiceClassBkGenericIo);

/**********************************************************************************************************************
 * vSwUpdM_Grid_InitServiceClassBkSetGenericParameter
 *********************************************************************************************************************/
/*! \brief          "Constructor" function for ServiceClassBkSetGenericParameter
 *  \details        Provide initialization for ServiceClass.
 *  \param[in]      Entities                Entities describing request.
 *  \param[in]      ParamType               Parameter type to persist.
 *  \param[in]      ParameterSize           Size of value in bytes.
 *  \param[in]      Parameter               Points to value, which shall be set.
 *  \param[in]      SyncFlag                Flag indicates whether a NvM synchronization is required or not.
 *  \param[in,out]  ServiceClassBkSetGenericParameter Initialized ServiceClass structure.
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *  \ingroup        GridSrvc
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_Grid_InitServiceClassBkSetGenericParameter( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  P2CONST(vSwUpdM_BkPersist_EntityType, AUTOMATIC, VSWUPDM_APPL_CONST) Entities,
  vSwUpdM_BkPersist_ParamType ParamType,
  vSwUpdM_BkPersist_SizeOfParameterType ParameterSize,
  P2VAR(void, AUTOMATIC, VSWUPDM_APPL_VAR) Parameter,
  boolean SyncFlag,
  vSwUpdM_GridSrvc_ServiceClassBkSetGenericParameterPtrType ServiceClassBkSetGenericParameter);

/**********************************************************************************************************************
 * vSwUpdM_Grid_InitServiceClassBkGetGenericParameter
 *********************************************************************************************************************/
/*! \brief          "Constructor" function for ServiceClassBkGetGenericParameter
 *  \details        Provide initialization for ServiceClass.
 *  \param[in]      Entities                Entities describing request.
 *  \param[in]      ParamType               Parameter type to persist.
 *  \param[in,out]  ServiceClassBkGetGenericParameter Initialized ServiceClass structure.
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *  \ingroup        GridSrvc
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_Grid_InitServiceClassBkGetGenericParameter( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  P2CONST(vSwUpdM_BkPersist_EntityType, AUTOMATIC, VSWUPDM_APPL_CONST) Entities,
  vSwUpdM_BkPersist_ParamType ParamType,
  vSwUpdM_GridSrvc_ServiceClassBkGetGenericParameterPtrType ServiceClassBkGetGenericParameter);

/**********************************************************************************************************************
 * vSwUpdM_Grid_InitServiceClassBkGetResumeInfo
 *********************************************************************************************************************/
/*! \brief          "Constructor" function for ServiceClassBkGetResumeInfo
 *  \details        Provide initialization for ServiceClass.
 *  \param[in,out]  ServiceClassBkGetResumeInfo Initialized ServiceClass structure.
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *  \ingroup        GridSrvc
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_Grid_InitServiceClassBkGetResumeInfo( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_GridSrvc_ServiceClassBkGetResumeInfoPtrType ServiceClassBkGetResumeInfo);

/**********************************************************************************************************************
 * vSwUpdM_Grid_InitServiceClassBkGetSegmentAttributes
 *********************************************************************************************************************/
/*! \brief          "Constructor" function for ServiceClassBkGetSegmentAttributes
 *  \details        Provide initialization for ServiceClass.
 *  \param[in]      Entities                Entities describing request.
 *  \param[in,out]  ServiceClassBkGetSegmentAttributes Initialized ServiceClass structure.
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *  \ingroup        GridSrvc
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_Grid_InitServiceClassBkGetSegmentAttributes( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  P2CONST(vSwUpdM_BkPersist_EntityType, AUTOMATIC, VSWUPDM_APPL_CONST) Entities,
  vSwUpdM_GridSrvc_ServiceClassBkGetSegmentAttributesPtrType ServiceClassBkGetSegmentAttributes);

 /****************************
  * Complex Response Classes
  ***************************/

/**********************************************************************************************************************
 * vSwUpdM_GridRpc_InitComplexResponseClassBaseType
 *********************************************************************************************************************/
/*! \brief          "Constructor" function for ComplexResponseClassBase
 *  \details        Provide initialization for ComplexResponseClass.
 *  \param[in]      RequestServiceIdx         Index of requested service.
 *  \param[in]      Result                    Result of initial request.
 *  \param[in]      ComplexResponseClassType  Desired ComplexResponseClass child of ComplexResponseClassBase.
 *  \param[in,out]  ComplexResponseClassBase  Initialized ResponseClass structure.
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *  \ingroup        GridSrvc
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_GridRpc_InitComplexResponseClassBaseType( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_GridSrvc_ServiceIdxType RequestServiceIdx,
  Std_ReturnType Result,
  vSwUpdM_GridRpc_ComplexResponseClassType ComplexResponseClassType,
  vSwUpdM_GridRpc_ComplexResponseClassBasePtrType ComplexResponseClassBase);

/**********************************************************************************************************************
 * vSwUpdM_GridRpc_InitComplexResponseClassSimpleType
 *********************************************************************************************************************/
/*! \brief          "Constructor" function for ComplexResponseClassSimple
 *  \details        Provide initialization for ComplexResponseClass.
 *  \param[in]      RequestServiceIdx         Index of requested service.
 *  \param[in]      Result                    Result of initial request.
 *  \param[in,out]  ComplexResponseClassSimple  Initialized ResponseClass structure.
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *  \ingroup        GridSrvc
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_GridRpc_InitComplexResponseClassSimpleType( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_GridSrvc_ServiceIdxType RequestServiceIdx,
  Std_ReturnType Result,
  vSwUpdM_GridRpc_ComplexResponseClassSimplePtrType ComplexResponseClassSimple);

/**********************************************************************************************************************
 * vSwUpdM_GridRpc_InitComplexResponseClassBkGetGenericType
 *********************************************************************************************************************/
/*! \brief          "Constructor" function for ComplexResponseClassBkGetGeneric
 *  \details        Provide initialization for ComplexResponseClass.
 *  \param[in]      RequestServiceIdx                 Index of requested service.
 *  \param[in]      Result                            Result of initial request.
 *  \param[in]      GenericValue                      Resulting value for Get request.
 *  \param[in,out]  ComplexResponseClassBkGetGeneric  Initialized ResponseClass structure.
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *  \ingroup        GridSrvc
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_GridRpc_InitComplexResponseClassBkGetGenericType( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_GridSrvc_ServiceIdxType RequestServiceIdx,
  Std_ReturnType Result,
  vSwUpdM_BkPersist_GenericParameterType GenericValue,
  vSwUpdM_GridRpc_ComplexResponseClassBkGetGenericPtrType ComplexResponseClassBkGetGeneric);

/**********************************************************************************************************************
 * vSwUpdM_GridRpc_InitComplexResponseClassBkGetSegmentAttributesType
 *********************************************************************************************************************/
/*! \brief          "Constructor" function for ComplexResponseClassBkGetSegmentAttributes
 *  \details        Provide initialization for ComplexResponseClass.
 *  \param[in]      RequestServiceIdx                           Index of requested service.
 *  \param[in]      Result                                      Result of initial request.
 *  \param[in]      SegmentAttributes                           Resulting value for Get request.
 *  \param[in,out]  ComplexResponseClassBkGetSegmentAttributes  Initialized ResponseClass structure.
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *  \ingroup        GridSrvc
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_GridRpc_InitComplexResponseClassBkGetSegmentAttributesType( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_GridSrvc_ServiceIdxType RequestServiceIdx,
  Std_ReturnType Result,
  P2CONST(vSwUpdM_BkPersist_SegmentAttributesType, AUTOMATIC, VSWUPDM_APPL_CONST) SegmentAttributes,
  vSwUpdM_GridRpc_ComplexResponseClassBkGetSegmentAttributesPtrType ComplexResponseClassBkGetSegmentAttributes);

/**********************************************************************************************************************
 * vSwUpdM_GridRpc_InitComplexResponseClassBkGetResumeInfoType
 *********************************************************************************************************************/
/*! \brief          "Constructor" function for ComplexResponseClassBkGetResumeInfo
 *  \details        Provide initialization for ComplexResponseClass.
 *  \param[in]      RequestServiceIdx                    Index of requested service.
 *  \param[in]      Result                               Result of initial request.
 *  \param[in]      ResumeInfo                           Resulting value for Get request.
 *  \param[in,out]  ComplexResponseClassBkGetResumeInfo  Initialized ResponseClass structure.
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *  \ingroup        GridSrvc
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_GridRpc_InitComplexResponseClassBkGetResumeInfoType( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_GridSrvc_ServiceIdxType RequestServiceIdx,
  Std_ReturnType Result,
  P2CONST(vSwUpdM_BkPersist_ResumeInfoType, AUTOMATIC, VSWUPDM_APPL_CONST) ResumeInfo,
  vSwUpdM_GridRpc_ComplexResponseClassBkGetResumeInfoPtrType ComplexResponseClassBkGetResumeInfo);

/*********************
 * LEGACY
 ********************/

/**********************************************************************************************************************
 * vSwUpdM_RemoteBookkeeperRequest
 *********************************************************************************************************************/
/*! \brief       Map Operation to Bookkeeper service, prepare reception of response and trigger Bookkeeper service.
 *  \details     -
 *  \param[in]   Target     Bookkeeper node.
 *  \param[in]   Operation  Kind of desired request.
 *  \param[in]   EntityIds  Payload data to be transmitted.
 *  \param[in]   ParentJob  Pointer to parent job.
 *  \return      E_OK on success.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     remote
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_RemoteBookkeeperRequest(
  vSwUpdM_NodeIterType Target,
  vSwUpdM_JobOperationType Operation,
  P2CONST(vSwUpdM_EntityIdsType, AUTOMATIC, VSWUPDM_APPL_CONST) EntityIds,
  vSwUpdM_JobPtrType ParentJob);

/**********************************************************************************************************************
 * vSwUpdM_RemoteBookkeeperRequest_IsRemoteUpdateResumeInfoAllowed
 *********************************************************************************************************************/
/*! \brief       Decides if a RemoteUpdateResumeInfo request is required.
 *  \details     -
 *  \return      TRUE  if a RemoteUpdateResumeInfo request is required.
 *  \return      FALSE Else.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     remote
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(boolean, VSWUPDM_CODE) vSwUpdM_RemoteBookkeeperRequest_IsRemoteUpdateResumeInfoAllowed(void);

/**********************************************************************************************************************
 * vSwUpdM_RemoteTransmitBookkeeperRequest
 *********************************************************************************************************************/
/*! \brief       Transmit Bookkeeper Request.
 *  \details     -
 *  \param[in]   Target          TxTarget for Bookkeeper node.
 *  \param[in]   RemoteServiceId ID of request.
 *  \param[in]   EntityIds       Payload data to be transmitted.
 *  \return      E_OK on success
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     remote
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_RemoteTransmitBookkeeperRequest(
  vSwUpdM_DestinationBookkeeperOfNodeType Target,
  vSwUpdM_GridSrvc_ServiceIdxType RemoteServiceId,
  P2CONST(vSwUpdM_EntityIdsType, AUTOMATIC, VSWUPDM_APPL_CONST) EntityIds);

/**********************************************************************************************************************
 * vSwUpdM_GetProcessIdByProcessHandle
 *********************************************************************************************************************/
/*! \brief       Determines the (local) DataProcess index associated with a DataProcessHandle
 *  \details     Each DataProcess has one Handle. The Handles are unique for all (remote) nodes and can be used to
 *               identify a (remote) DataProcess by the handle.
 *  \param[in]   DataProcessHandle    The handle identifying the data process.
 *  \param[out]  ProcessId            The ID of the data process.
 *  \return      E_OK     if ProcessId could be found
 *  \return      E_NOT_OK else
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     remote
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GetProcessIdByProcessHandle(
  vSwUpdM_ProcessHandleOfDataProcessesType DataProcessHandle,
  P2VAR(vSwUpdM_DataProcessesIterType, AUTOMATIC, VSWUPDM_APPL_VAR) ProcessId);

/**********************************************************************************************************************
 *  Global Functions
 *********************************************************************************************************************/

/*********************
 * GRID CHANNEL
 ********************/

/**********************************************************************************************************************
 *  vSwUpdM_GridChannel_Init
 *********************************************************************************************************************/
/*! \brief       Initializes GridChannel data structures.
 *  \details     -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     GridChannel
 *********************************************************************************************************************/
FUNC(void, VSWUPDM_CODE) vSwUpdM_GridChannel_Init(void);

/*********************
 * GRID NODE
 ********************/

/**********************************************************************************************************************
 *  vSwUpdM_GridNode_Init
 *********************************************************************************************************************/
/*! \brief       Initializes GridNode data structures.
 *  \details     -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     GridCSrvc
 *********************************************************************************************************************/
FUNC(void, VSWUPDM_CODE) vSwUpdM_GridNode_Init(void);

/**********************************************************************************************************************
 *  vSwUpdM_GridNode_IsNodeContainedInNodeGroup
 *********************************************************************************************************************/
/*! \brief       Evaluate if remote node group contains the given node.
 *  \details     -
 *  \param[in]   Group Node group.
 *  \param[in]   Node  Node to search for in group.
 *  \return      TRUE  The group contains the node.
 *  \return      FALSE The group does not contain the node.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     remote
 *********************************************************************************************************************/
FUNC(boolean, VSWUPDM_CODE) vSwUpdM_GridNode_IsNodeContainedInNodeGroup(
  vSwUpdM_NodeGroupIterType Group,
  vSwUpdM_NodeIterType Node);

/*********************
 * GRID RPC
 ********************/

/**********************************************************************************************************************
 *  vSwUpdM_GridRpc_TransmitResponse
 *********************************************************************************************************************/
/*! \brief       Transmits a response for a RPC request.
 *  \details     -
 *  \param[in]   RequestOrigin          Source of the initial RPC request.
 *  \param[in]   ServiceExecutionState  State of service execution.
 *  \param[in]   ResponseClass          Parameters for response.
 *  \return      E_OK Transmission successful forwarded to vRpcProxy
 *  \return      else Transmission failed
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     GridRpc
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GridRpc_TransmitResponse(
  vSwUpdM_NodeIterType RequestOrigin,
  vSwUpdM_GridRpc_ServiceExecutionStateType ServiceExecutionState,
  vSwUpdM_GridRpc_ComplexResponseClassBasePtrType ResponseClass);

/*********************
 * GRID SERVICE
 ********************/

/**********************************************************************************************************************
 *  vSwUpdM_GridSrvc_Init
 *********************************************************************************************************************/
/*! \brief       Acquires the lock from all members of destination node group.
 *  \details     -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     GridSrvc
 *********************************************************************************************************************/
FUNC(void, VSWUPDM_CODE) vSwUpdM_GridSrvc_Init(void);

/**********************************************************************************************************************
 *  vSwUpdM_GridSrvc_Open
 *********************************************************************************************************************/
/*! \brief       Acquires the lock from all members of destination node group.
 *  \details     -
 *  \param[in]   Destination  Target node group.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     GridSrvc
 *********************************************************************************************************************/
FUNC(void, VSWUPDM_CODE) vSwUpdM_GridSrvc_Open(
  vSwUpdM_NodeGroupIterType Destination
);

/**********************************************************************************************************************
 *  vSwUpdM_GridSrvc_GetCommunicationState
 *********************************************************************************************************************/
/*! \brief       Polls for responses during locking.
 *  \details     -
 *  \return      Communication state.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         vSwUpdM_GridSrvc_Open() has to be called before.
 *  \ingroup     GridSrvc
 *********************************************************************************************************************/
FUNC(vSwUpdM_GridSrvc_GridStateType, VSWUPDM_CODE) vSwUpdM_GridSrvc_GetCommunicationState(void);

/**********************************************************************************************************************
 *  vSwUpdM_GridSrvc_Close
 *********************************************************************************************************************/
/*! \brief       Release the lock from all members of destination node group.
 *  \details     -
 *  \param[in]   Destination  Target node group.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     GridSrvc
 *********************************************************************************************************************/
FUNC(void, VSWUPDM_CODE) vSwUpdM_GridSrvc_Close(vSwUpdM_NodeGroupIterType Destination);

/**********************************************************************************************************************
 *  vSwUpdM_GridSrvc_Register
 *********************************************************************************************************************/
/*! \brief       Register a RPC
 *  \details     -
 *  \param[in]   ServiceIndex Index of service.
 *  \param[out]  Parameter    Provided buffer for assembly of request parameters.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     GridSrvc
 *********************************************************************************************************************/
FUNC(void, VSWUPDM_CODE) vSwUpdM_GridSrvc_Register(
  vSwUpdM_GridSrvc_ServiceIdxType ServiceIndex,
  vSwUpdM_GridSrvc_ServiceClassBasePtrPtrType Parameter);

/**********************************************************************************************************************
 *  vSwUpdM_GridSrvc_Start
 *********************************************************************************************************************/
/*! \brief       Transmit a RPC request and initialize response aggregation.
 *  \details     -
 *  \param[in]   Destination    Targets for request.
 *  \param[in]   ServiceIndex   Index of service.
 *  \return      E_OK Transmission successful forwarded to vRpcProxy.
 *  \return      else Transmission failed.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     GridSrvc
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GridSrvc_Start(
  vSwUpdM_NodeGroupIterType Destination,
  vSwUpdM_GridSrvc_ServiceIdxType ServiceIndex);

/**********************************************************************************************************************
 *  vSwUpdM_GridSrvc_GetAggregatedResult
 *********************************************************************************************************************/
/*! \brief       Evaluates pending results of SimpleResponse type and aggregates them.
 *  \details     Collects the responses from all nodes that are requested. The aggregated result will be "OK" if all
 *               responses are received and "OK". If at least one response is missing or not "OK", the aggregated Result
 *               will be negative. The first observed error is reported.
 *  \param[in]   ServiceIndex   Index of service.
 *  \param[out]  Result         Aggregated result.
 *  \return      VSWUPDM_GRIDSRVC_AGGREGATE_DONE    Aggregation successful.
 *  \return      VSWUPDM_GRIDSRVC_AGGREGATE_PENDING else
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     GridSrvc
 *********************************************************************************************************************/
FUNC(vSwUpdM_GridSrvc_AggregateResultType, VSWUPDM_CODE) vSwUpdM_GridSrvc_GetAggregatedResult(
  vSwUpdM_GridSrvc_ServiceIdxType ServiceIndex,
  P2VAR(vSwUpdM_GridSrvc_ResponseClassSimpleResponsePtrType, AUTOMATIC, VSWUPDM_APPL_VAR) Result);

/**********************************************************************************************************************
 *  vSwUpdM_GridSrvc_Finish
 *********************************************************************************************************************/
/*! \brief       Clean up RPC processing, free channel.
 *  \details     -
 *  \param[in]   ServiceIndex   Index of service.
 *  \return      E_OK Transmission successful forwarded to vRpcProxy.
 *  \return      else Transmission failed
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         All responses for request have arrived (or will never arrive, because errors have been detected.)
 *  \ingroup     GridSrvc
 *********************************************************************************************************************/
FUNC(void, VSWUPDM_CODE) vSwUpdM_GridSrvc_Finish(
  vSwUpdM_GridSrvc_ServiceIdxType ServiceIndex);

/*********************
 * LEGACY
 ********************/

/**********************************************************************************************************************
 *  vSwUpdM_GridSrvc_ServiceHandlingIsLegacy
 *********************************************************************************************************************/
/*! \brief       Switch for legacy-handling of remote services.
 *  \details     -
 *  \param[in]   RemoteServiceId  ID of remote service.
 *  \return      TRUE If service is legacy service.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     GridSrvc
 *********************************************************************************************************************/
FUNC(boolean, VSWUPDM_CODE) vSwUpdM_GridSrvc_ServiceHandlingIsLegacy(
  vSwUpdM_GridSrvc_ServiceIdxType RemoteServiceId);

/**********************************************************************************************************************
 *  vSwUpdM_RemoteConcludeResponses()
 *********************************************************************************************************************/
/*! \brief       Conclude reception of responses from a remote group of nodes.
 *  \details     Standard use case (IsSuspended==FALSE): Clears the processing flag for all responses of a group of
 *               nodes. This denotes that the processing of the received data has ceased.
 *               Instead, if a Suspend is in progress (IsSuspended==TRUE), the responses are prepared to be received
 *               again after resume (Valid flag is cleared).
 *  \param[in]   SourceGroupIndex The transmitting group for this response.
 *  \param[in]   IsSuspended      TRUE : A Suspend is in progress.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     remote
 *********************************************************************************************************************/
FUNC(void, VSWUPDM_CODE) vSwUpdM_RemoteConcludeResponses(
  vSwUpdM_NodeGroupIterType SourceGroupIndex,
  boolean IsSuspended);

/**********************************************************************************************************************
 *  vSwUpdM_RemotePrepareResponseRxTarget
 *********************************************************************************************************************/
/*! \brief       Prepare reception of responses from a single remote slave.
 *  \details     Clears the response valid flags and spawns a job to wait for the response.
 *  \param[in]   TargetIndex     Target for transmission.
 *  \param[in]   RemoteServiceId Service that shall be transmitted.
 *  \param[in]   ParentJob       The result will be propagated to this job.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     remote
 *********************************************************************************************************************/
FUNC(void, VSWUPDM_CODE) vSwUpdM_RemotePrepareResponseRxTarget(
  vSwUpdM_NodeIterType TargetIndex,
  vSwUpdM_GridSrvc_ServiceIdxType RemoteServiceIndex,
  vSwUpdM_JobPtrType ParentJob);

/**********************************************************************************************************************
 *  vSwUpdM_RemoteClearListOfResponses
 *********************************************************************************************************************/
/*! \brief       Prepare reception of responses from a remote group of slaves.
 *  \details     Clear list, number and overall result of previous responses.
 *  \param[in]   SourceGroupIndex  Index of source group.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     remote
 *********************************************************************************************************************/
FUNC(void, VSWUPDM_CODE) vSwUpdM_RemoteClearListOfResponses(
  vSwUpdM_NodeGroupIterType SourceGroupIndex);

/*********************
 * REMOTE STREAM
 ********************/

/**********************************************************************************************************************
 *  vSwUpdM_RemoteStreamCallPostHandler()
 *********************************************************************************************************************/
/*! \brief       Handles the results of a remote Stream request.
 *  \details     Spawns Stream scheduler job if required or transmits negative response in case of an error.
 *  \param[in]   Result               Result of initial Stream request
 *  \param[in]   SourceIndex          Source of initial Stream request.
 *  \param[in]   ProcessHandle        The handle identifying the data process.
 *  \param[in]   Handle               Handle of initial Stream request.
 *  \param[in]   ResponseServiceIndex Response service that shall be transmitted on error.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     remote
 *********************************************************************************************************************/
FUNC(void, VSWUPDM_CODE) vSwUpdM_RemoteStreamCallPostHandler(
  Std_ReturnType Result,
  vSwUpdM_NodeIterType SourceIndex,
  vSwUpdM_ProcessHandleOfDataProcessesType ProcessHandle,
  vSwUpdM_RemoteStreamHandleType Handle,
  vSwUpdM_GridSrvc_ServiceIdxType ResponseServiceIndex);

/**********************************************************************************************************************
 *  vSwUpdM_RemoteStreamPrepareRx()
 *********************************************************************************************************************/
/*! \brief       Set up a RemoteStream for reception.
 *  \details     Takes a pointer to a buffer where the received data shall be stored.
 *  \param[in]   Handle      Handle of a RemoteStream.
 *  \param[in]   Buffer      Pointer to a buffer for Rx.
 *  \param[in]   BufferSize  Size of the Buffer.
 *  \param[in]   Source      Expected Source for RemoteStream.
 *  \return      E_OK                   On success.
 *  \return      VSWUPDM_E_OUT_OF_RANGE Handle has wrong value.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         RemoteStream must be in IDLE state.
 *  \ingroup     remote
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_RemoteStreamPrepareRx(
  vSwUpdM_RemoteStreamHandleType Handle,
  P2VAR(uint8, AUTOMATIC, VSWUPDM_APPL_VAR) Buffer,
  vSwUpdM_RemoteStreamSizeType BufferSize,
  vSwUpdM_NodeIterType Source);

/**********************************************************************************************************************
 *  vSwUpdM_RemoteStreamStartTx()
 *********************************************************************************************************************/
/*! \brief       Set up a RemoteStream for transmission.
 *  \details     Takes a pointer to a buffer of data to be transmitted.
 *  \param[in]   Handle          Handle of a RemoteStream.
 *  \param[in]   Buffer          Pointer to a buffer for Rx.
 *  \param[in]   AvailableLength Length of data in Buffer
 *  \param[in]   Target          Target for transmission.
 *  \return      E_OK                            Function was successful.
 *  \return      VSWUPDM_E_INVALID_STREAM_STATE  RemoteStream is not idle.
 *  \return      VSWUPDM_E_OUT_OF_RANGE          Handle has wrong value.
 *  \return      E_NOT_OK                        From vRpcProxy: Transmission of initial StreamStart frame failed.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     remote
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_RemoteStreamStartTx(
  vSwUpdM_RemoteStreamHandleType Handle,
  P2VAR(uint8, AUTOMATIC, VSWUPDM_APPL_VAR) Buffer,
  vSwUpdM_RemoteStreamSizeType AvailableLength,
  vSwUpdM_NodeIterType Target);

/**********************************************************************************************************************
 * vSwUpdM_RemoteStreamSchedule
 *********************************************************************************************************************/
/*! \brief       Maintain the state machines of the RemoteStreams
 *  \details     -
 *  \param[in]   Handle         Handle of a RemoteStream.
 *  \return      E_OK           All Remote Streams are finished or waiting for an event.
 *  \return      VSWUPDM_E_BUSY At least one Remote Stream needs further scheduling.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     remote
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_RemoteStreamSchedule(vSwUpdM_RemoteStreamHandleType Handle);

# define VSWUPDM_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* VSWUPDM_GRID_IF_H */

/**********************************************************************************************************************
 *  END OF FILE: vSwUpdM_Grid_If.h
 *********************************************************************************************************************/
