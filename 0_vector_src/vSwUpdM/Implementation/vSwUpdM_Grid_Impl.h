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
/*!        \file  vSwUpdM_Grid_Impl.h
 *        \brief  vSwUpdM_Grid implementation header file
 *      \details  vSwUpdM_Grid subcomponent public inline implementations.
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

#if !defined (VSWUPDM_GRID_IMPL_H)
# define VSWUPDM_GRID_IMPL_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
/* Grid interface header */
#include "vSwUpdM_Grid_If.h"

/* Other MultipleUnits used by Grid_Impl (Prefer smallest set required, i.e. prefer _Types over _If over _Impl) */
#include "vSwUpdM_Priv.h"
#include "vSwUpdM_Bookkeeper_Impl.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/
#define VSWUPDM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#if (VSWUPDM_MULTICONTROLLER_SUPPORT == STD_ON)
extern CONST(vSwUpdM_RemoteServiceDefinitionType, VSWUPDM_CONST) vSwUpdM_RemoteServiceDefinitions[48u];
#endif /* VSWUPDM_MULTICONTROLLER_SUPPORT == STD_ON */

#define VSWUPDM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define VSWUPDM_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define VSWUPDM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/
# define VSWUPDM_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 * vSwUpdM_GridNode_LocalNodeIsChild
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(boolean, VSWUPDM_CODE) vSwUpdM_Grid_LocalNodeIsChild(void) /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
{
  boolean retVal;

  if ((vSwUpdM_RemoteLockIsGrantedTo != (vSwUpdM_NodeIterType) VSWUPDM_INVALID_NODE) && (vSwUpdM_RemoteLockIsGrantedTo != (vSwUpdM_NodeIterType) vSwUpdM_GetLocalNode()))
  {
    retVal = TRUE;
  }
  else
  {
    retVal = FALSE;
  }

  return retVal;
}

/**********************************************************************************************************************
 * vSwUpdM_Grid_LocalNodeIsParent
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(boolean, VSWUPDM_CODE) vSwUpdM_Grid_LocalNodeIsParent(void) /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
{
  boolean retVal;

 if (vSwUpdM_GridSrvc_GetCommunicationState() == VSWUPDM_GRIDSRVC_GRIDSTATE_LOCKED)
  {
    retVal = TRUE;
  }
  else
  {
    retVal = FALSE;
  }

  return retVal;
}

/**********************************************************************************************************************
 * vSwUpdM_Grid_InitServiceClassSuspend
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_Grid_InitServiceClassSuspend( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_GridSrvc_ServiceIdxType ServiceIndex,
  vSwUpdM_GridSrvc_ServiceClassSuspendPtrType ServiceClass
)
{
  ServiceClass->Base.ServiceClass = VSWUPDM_GRIDSRVC_CLASS_SUSPEND;
  ServiceClass->ServiceIndex = ServiceIndex;
}

/**********************************************************************************************************************
 * vSwUpdM_Grid_InitServiceClassMainBase
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_Grid_InitServiceClassMainBase( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_ExctSchedule_ServiceStateType ServiceState,
  SwUpdM_GridSrvc_ServiceClassType ServiceClass,
  vSwUpdM_GridSrvc_ServiceClassMainBasePtrType MainServiceClass
)
{
  MainServiceClass->Base.ServiceClass = ServiceClass;
  MainServiceClass->ServiceState = ServiceState;
}

/**********************************************************************************************************************
 * vSwUpdM_Grid_InitServiceClassGenericBase
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_Grid_InitServiceClassGenericBase( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_ExctSchedule_ServiceStateType ServiceState,
  vSwUpdM_GridSrvc_ServiceIdxType ServiceIndex,
  SwUpdM_GridSrvc_ServiceClassType ServiceClass,
  vSwUpdM_GridSrvc_ServiceClassGenericBasePtrType GenericServiceClass
)
{
  vSwUpdM_Grid_InitServiceClassMainBase(ServiceState, ServiceClass, &GenericServiceClass->Base);
  GenericServiceClass->ServiceIndex = ServiceIndex;
}

/**********************************************************************************************************************
 * vSwUpdM_Grid_InitServiceClassMaintenance
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_Grid_InitServiceClassMaintenance( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_ExctSchedule_ServiceStateType ServiceState,
  vSwUpdM_GridSrvc_ServiceIdxType ServiceIndex,
  vSwUpdM_GridSrvc_ServiceClassMaintenancePtrType ServiceClass
)
{
  vSwUpdM_Grid_InitServiceClassGenericBase(ServiceState, ServiceIndex, VSWUPDM_GRIDSRVC_CLASS_MAINTENANCE, &ServiceClass->GenericBase);
}

/**********************************************************************************************************************
 * vSwUpdM_Grid_InitServiceClassGeneric
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_Grid_InitServiceClassGeneric( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_ExctSchedule_ServiceStateType ServiceState,
  vSwUpdM_GridSrvc_ServiceIdxType ServiceIndex,
  vSwUpdM_GridSrvc_ServiceClassGenericPtrType ServiceClass
)
{
  vSwUpdM_Grid_InitServiceClassGenericBase(ServiceState, ServiceIndex, VSWUPDM_GRIDSRVC_CLASS_GENERIC, &ServiceClass->GenericBase);
}

/**********************************************************************************************************************
 * vSwUpdM_Grid_InitServiceClassPartition
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_Grid_InitServiceClassPartition( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_ExctSchedule_ServiceStateType ServiceState,
  vSwUpdM_GridSrvc_ServiceIdxType ServiceIndex,
  vSwUpdM_PartitionStateType PartitionState,
  vSwUpdM_GridSrvc_ServiceClassPartitionPtrType ServiceClass
)
{
  vSwUpdM_Grid_InitServiceClassGenericBase(ServiceState, ServiceIndex, VSWUPDM_GRIDSRVC_CLASS_PARTITION, &ServiceClass->GenericBase);
  ServiceClass->PartitionState = PartitionState;
}

/**********************************************************************************************************************
 * vSwUpdM_Grid_InitServiceClassModule
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_Grid_InitServiceClassModule( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_ExctSchedule_ServiceStateType ServiceState,
  vSwUpdM_GridSrvc_ServiceIdxType ServiceIndex,
  vSwUpdM_ModuleIdType ModuleId,
  vSwUpdM_GridSrvc_ServiceClassModulePtrType ServiceClass
)
{
  vSwUpdM_Grid_InitServiceClassGenericBase(ServiceState, ServiceIndex, VSWUPDM_GRIDSRVC_CLASS_MODULE, &ServiceClass->GenericBase);
  ServiceClass->ModuleId = ModuleId;
}

/**********************************************************************************************************************
 * vSwUpdM_Grid_InitServiceClassRegion
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_Grid_InitServiceClassRegion( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_ExctSchedule_ServiceStateType ServiceState,
  vSwUpdM_GridSrvc_ServiceIdxType ServiceIndex,
  vSwUpdM_RegionIdType RegionId,
  vSwUpdM_GridSrvc_ServiceClassRegionPtrType ServiceClass
)
{
  vSwUpdM_Grid_InitServiceClassGenericBase(ServiceState, ServiceIndex, VSWUPDM_GRIDSRVC_CLASS_REGION, &ServiceClass->GenericBase);
  ServiceClass->RegionId = RegionId;
}

/**********************************************************************************************************************
 * vSwUpdM_Grid_InitServiceClassSegment
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_Grid_InitServiceClassSegment( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_ExctSchedule_ServiceStateType ServiceState,
  vSwUpdM_GridSrvc_ServiceIdxType ServiceIndex,
  vSwUpdM_SegmentIdType  SegmentId,
  vSwUpdM_GridSrvc_ServiceClassSegmentPtrType ServiceClass
)
{
  vSwUpdM_Grid_InitServiceClassGenericBase(ServiceState, ServiceIndex, VSWUPDM_GRIDSRVC_CLASS_SEGMENT, &ServiceClass->GenericBase);
  ServiceClass->SegmentId = SegmentId;
}

/**********************************************************************************************************************
 * vSwUpdM_Grid_InitServiceClassProcessModule
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_Grid_InitServiceClassProcessModule( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_ExctSchedule_ServiceStateType ServiceState,
  vSwUpdM_GridSrvc_ServiceIdxType ServiceIndex,
  vSwUpdM_ModuleIdType ModuleId,
  vSwUpdM_ProcessIdType ProcessId,
  P2VAR(vSwUpdM_ProcessInfoType, AUTOMATIC, VSWUPDM_APPL_VAR) ProcessInfo, /* PRQA S 3673 */ /* MD_vSwUpdM_Rule8.13_3673_PointerToConstParameter */
  vSwUpdM_GridSrvc_ServiceClassProcessModulePtrType ServiceClass
)
{
  vSwUpdM_Grid_InitServiceClassGenericBase(ServiceState, ServiceIndex, VSWUPDM_GRIDSRVC_CLASS_PROCESS_MODULE, &ServiceClass->GenericBase);
  ServiceClass->ModuleId    = ModuleId;
  ServiceClass->ProcessId   = ProcessId;
  ServiceClass->ProcessInfo = *ProcessInfo;
  /* PRQA S 6060 1 */ /* MD_MSR_STPAR */
}

/**********************************************************************************************************************
 * vSwUpdM_Grid_InitServiceClassStreamInfo
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_Grid_InitServiceClassStreamInfo( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_ExctSchedule_ServiceStateType ServiceState,
  P2VAR(vSwUpdM_StreamInfoType, AUTOMATIC, VSWUPDM_APPL_VAR) StreamInfo, /* PRQA S 3673 */ /* MD_vSwUpdM_Rule8.13_3673_PointerToConstParameter */
  vSwUpdM_GridSrvc_ServiceClassStreamInfoPtrType ServiceClass
)
{
  vSwUpdM_Grid_InitServiceClassMainBase(ServiceState, VSWUPDM_GRIDSRVC_CLASS_STREAM_INFO, &ServiceClass->Base);
  ServiceClass->StreamInfo = (*StreamInfo);
}

/**********************************************************************************************************************
 * vSwUpdM_Grid_InitServiceClassSegmentInfo
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_Grid_InitServiceClassSegmentInfo( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_ExctSchedule_ServiceStateType ServiceState,
  P2VAR(vSwUpdM_RemoteSegmentInfoType, AUTOMATIC, VSWUPDM_APPL_VAR) SegmentInfo, /* PRQA S 3673 */ /* MD_vSwUpdM_Rule8.13_3673_PointerToConstParameter */
  vSwUpdM_GridSrvc_ServiceClassSegmentInfoPtrType ServiceClass)
{
  vSwUpdM_Grid_InitServiceClassMainBase(ServiceState, VSWUPDM_GRIDSRVC_CLASS_SEGMENT_INFO, &ServiceClass->Base);
  ServiceClass->SegmentInfo = (*SegmentInfo);
}

/**********************************************************************************************************************
 * vSwUpdM_Grid_InitServiceClassBkGenericBase
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_Grid_InitServiceClassBkGenericBase( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  SwUpdM_GridSrvc_ServiceClassType ServiceClass,
  vSwUpdM_GridSrvc_ServiceClassBkGenericBasePtrType ServiceClassBkGeneric)
{
  ServiceClassBkGeneric->Base.ServiceClass = ServiceClass;
}

/**********************************************************************************************************************
 * vSwUpdM_Grid_InitServiceClassBkExecCommand
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_Grid_InitServiceClassBkExecCommand( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_BkPersist_GenericServiceCommandType Command,
  vSwUpdM_GridSrvc_ServiceClassBkExecCommandPtrType ServiceClassBkExecCommand)
{
  ServiceClassBkExecCommand->Command = Command;
  vSwUpdM_Grid_InitServiceClassBkGenericBase(VSWUPDM_GRIDSRVC_CLASS_BK_EXEC_COMMAND, &(ServiceClassBkExecCommand->Base));
}

/**********************************************************************************************************************
 * vSwUpdM_Grid_InitServiceClassBkSetResumeInfo
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
/*!
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_Grid_InitServiceClassBkSetResumeInfo( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  P2CONST(vSwUpdM_ExtendedResumeInfoType, AUTOMATIC, VSWUPDM_APPL_CONST) ExtendedResumeInfo,
  boolean SyncFlag,
  vSwUpdM_GridSrvc_ServiceClassBkSetResumeInfoPtrType ServiceClassBkSetResumeInfo)
{
  vSwUpdM_Bookkeeper_ConvertExtended2BkResumeInfo(&ServiceClassBkSetResumeInfo->ResumeInfo, ExtendedResumeInfo);
  ServiceClassBkSetResumeInfo->SyncFlag = SyncFlag;
  vSwUpdM_Grid_InitServiceClassBkGenericBase(VSWUPDM_GRIDSRVC_CLASS_BK_SET_RESUME_INFO, &(ServiceClassBkSetResumeInfo->Base));
}

/**********************************************************************************************************************
 * vSwUpdM_Grid_InitServiceClassBkSetSegmentAttributes
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_Grid_InitServiceClassBkSetSegmentAttributes( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  P2CONST(vSwUpdM_BkPersist_EntityType, AUTOMATIC, VSWUPDM_APPL_CONST) Entities,
  P2CONST(vSwUpdM_BkPersist_SegmentAttributesType, AUTOMATIC, VSWUPDM_APPL_CONST) SegmentAttributes,
  boolean SyncFlag,
  vSwUpdM_GridSrvc_ServiceClassBkSetSegmentAttributesPtrType ServiceClassBkSetSegmentAttributes)
{
  ServiceClassBkSetSegmentAttributes->Entities = Entities;
  ServiceClassBkSetSegmentAttributes->SegmentAttributes = SegmentAttributes;
  ServiceClassBkSetSegmentAttributes->SyncFlag = SyncFlag;
  vSwUpdM_Grid_InitServiceClassBkGenericBase(VSWUPDM_GRIDSRVC_CLASS_BK_SET_SEGMENT_ATTRIBUTES, &(ServiceClassBkSetSegmentAttributes->Base));
}

/**********************************************************************************************************************
 * vSwUpdM_Grid_InitServiceClassBkGenericIoBase
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_Grid_InitServiceClassBkGenericIoBase( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  P2CONST(vSwUpdM_BkPersist_EntityType, AUTOMATIC, VSWUPDM_APPL_CONST) Entities,
  vSwUpdM_BkPersist_ParamType ParamType,
  SwUpdM_GridSrvc_ServiceClassType ServiceClass,
  vSwUpdM_GridSrvc_ServiceClassBkGenericIoBasePtrType ServiceClassBkGenericIo)
{
  ServiceClassBkGenericIo->Entities = Entities;
  ServiceClassBkGenericIo->ParamType = ParamType;
  vSwUpdM_Grid_InitServiceClassBkGenericBase(ServiceClass, &(ServiceClassBkGenericIo->Base));
}

/**********************************************************************************************************************
 * vSwUpdM_Grid_InitServiceClassBkSetGeneric
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_Grid_InitServiceClassBkSetGenericParameter( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  P2CONST(vSwUpdM_BkPersist_EntityType, AUTOMATIC, VSWUPDM_APPL_CONST) Entities,
  vSwUpdM_BkPersist_ParamType ParamType,
  vSwUpdM_BkPersist_SizeOfParameterType ParameterSize,
  P2VAR(void, AUTOMATIC, VSWUPDM_APPL_VAR) Parameter, /* PRQA S 3673 */ /* MD_vSwUpdM_Rule8.13_3673_PointerToConstParameter */
  boolean SyncFlag,
  vSwUpdM_GridSrvc_ServiceClassBkSetGenericParameterPtrType ServiceClassBkSetGenericParameter)
{
  /* Ensure correct aligned access for Parameter pointer. */
  switch (ParameterSize)
  {
    case sizeof(uint32):
    {
      ServiceClassBkSetGenericParameter->GenericValue = *(P2VAR(uint32, AUTOMATIC, VSWUPDM_APPL_VAR))Parameter; /* PRQA S 0316 */ /* MD_vSwUpdM_Rule11.5_0316_PersistCastPtrVoidPtrObj */
      break;
    }
    case sizeof(uint16):
    {
      ServiceClassBkSetGenericParameter->GenericValue = *(P2VAR(uint16, AUTOMATIC, VSWUPDM_APPL_VAR))Parameter; /* PRQA S 0316 */ /* MD_vSwUpdM_Rule11.5_0316_PersistCastPtrVoidPtrObj */
      break;
    }
    default:
    /* case sizeof(uint8): */
    {
      ServiceClassBkSetGenericParameter->GenericValue = *(P2VAR(uint8, AUTOMATIC, VSWUPDM_APPL_VAR))Parameter; /* PRQA S 0316 */ /* MD_vSwUpdM_Rule11.5_0316_PersistCastPtrVoidPtrObj */
      break;
    }
  }

  ServiceClassBkSetGenericParameter->SyncFlag = SyncFlag;
  vSwUpdM_Grid_InitServiceClassBkGenericIoBase(Entities, ParamType, VSWUPDM_GRIDSRVC_CLASS_BK_SET_GENERIC, &(ServiceClassBkSetGenericParameter->Base));
  /* PRQA S 6060 1 */ /* MD_MSR_STPAR */
} /* vSwUpdM_Grid_InitServiceClassBkSetGenericParameter */

/**********************************************************************************************************************
 * vSwUpdM_Grid_InitServiceClassBkGetGenericParameter
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_Grid_InitServiceClassBkGetGenericParameter( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  P2CONST(vSwUpdM_BkPersist_EntityType, AUTOMATIC, VSWUPDM_APPL_CONST) Entities,
  vSwUpdM_BkPersist_ParamType ParamType,
  vSwUpdM_GridSrvc_ServiceClassBkGetGenericParameterPtrType ServiceClassBkGetGenericParameter)
{
  vSwUpdM_Grid_InitServiceClassBkGenericIoBase(Entities, ParamType, VSWUPDM_GRIDSRVC_CLASS_BK_GET_GENERIC, &(ServiceClassBkGetGenericParameter->Base));
}

/**********************************************************************************************************************
 * vSwUpdM_Grid_InitServiceClassBkGetResumeInfo
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_Grid_InitServiceClassBkGetResumeInfo( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_GridSrvc_ServiceClassBkGetResumeInfoPtrType ServiceClassBkGetResumeInfo)
{
  vSwUpdM_Grid_InitServiceClassBkGenericBase(VSWUPDM_GRIDSRVC_CLASS_BK_GET_RESUME_INFO, &(ServiceClassBkGetResumeInfo->Base));
}

/**********************************************************************************************************************
 * vSwUpdM_Grid_InitServiceClassBkGetSegmentAttributes
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_Grid_InitServiceClassBkGetSegmentAttributes( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  P2CONST(vSwUpdM_BkPersist_EntityType, AUTOMATIC, VSWUPDM_APPL_CONST) Entities,
  vSwUpdM_GridSrvc_ServiceClassBkGetSegmentAttributesPtrType ServiceClassBkGetSegmentAttributes)
{
  ServiceClassBkGetSegmentAttributes->Entities = Entities;
  vSwUpdM_Grid_InitServiceClassBkGenericBase(VSWUPDM_GRIDSRVC_CLASS_BK_GET_SEGMENT_ATTRIBUTES, &(ServiceClassBkGetSegmentAttributes->Base));
}

/**********************************************************************************************************************
 * vSwUpdM_GridRpc_InitComplexResponseClassBaseType
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_GridRpc_InitComplexResponseClassBaseType( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_GridSrvc_ServiceIdxType RequestServiceIdx,
  Std_ReturnType Result,
  vSwUpdM_GridRpc_ComplexResponseClassType ComplexResponseClassType,
  vSwUpdM_GridRpc_ComplexResponseClassBasePtrType ComplexResponseClassBase)
{
  ComplexResponseClassBase->RequestServiceIdx        = RequestServiceIdx;
  ComplexResponseClassBase->ComplexResponseClassType = ComplexResponseClassType;
  ComplexResponseClassBase->Result                   = Result;
}

/**********************************************************************************************************************
 * vSwUpdM_GridRpc_InitComplexResponseClassSimpleType
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_GridRpc_InitComplexResponseClassSimpleType( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_GridSrvc_ServiceIdxType RequestServiceIdx,
  Std_ReturnType Result,
  vSwUpdM_GridRpc_ComplexResponseClassSimplePtrType ComplexResponseClassSimple)
{
  vSwUpdM_GridRpc_InitComplexResponseClassBaseType(RequestServiceIdx, Result, VSWUPDM_GRIDRPC_COMPLEXREPONSECLASS_SIMPLE, &ComplexResponseClassSimple->Base);
}

/**********************************************************************************************************************
 * vSwUpdM_GridRpc_InitComplexResponseClassBkGetGenericType
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_GridRpc_InitComplexResponseClassBkGetGenericType( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_GridSrvc_ServiceIdxType RequestServiceIdx,
  Std_ReturnType Result,
  vSwUpdM_BkPersist_GenericParameterType GenericValue,
  vSwUpdM_GridRpc_ComplexResponseClassBkGetGenericPtrType ComplexResponseClassBkGetGeneric)
{
  ComplexResponseClassBkGetGeneric->GenericValue = GenericValue;
  vSwUpdM_GridRpc_InitComplexResponseClassBaseType(RequestServiceIdx, Result, VSWUPDM_GRIDRPC_COMPLEXREPONSECLASS_BK_GET_GENERIC_PARAMETER, &ComplexResponseClassBkGetGeneric->Base);
}

/**********************************************************************************************************************
 * vSwUpdM_GridRpc_InitComplexResponseClassBkGetSegmentAttributesType
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_GridRpc_InitComplexResponseClassBkGetSegmentAttributesType( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_GridSrvc_ServiceIdxType RequestServiceIdx,
  Std_ReturnType Result,
  P2CONST(vSwUpdM_BkPersist_SegmentAttributesType, AUTOMATIC, VSWUPDM_APPL_CONST) SegmentAttributes,
  vSwUpdM_GridRpc_ComplexResponseClassBkGetSegmentAttributesPtrType ComplexResponseClassBkGetSegmentAttributes)
{
  ComplexResponseClassBkGetSegmentAttributes->SegmentAttributes = SegmentAttributes;
  vSwUpdM_GridRpc_InitComplexResponseClassBaseType(RequestServiceIdx, Result, VSWUPDM_GRIDRPC_COMPLEXREPONSECLASS_BK_GET_SEGMENT_ATTRIBUTES, &ComplexResponseClassBkGetSegmentAttributes->Base);
}

/**********************************************************************************************************************
 * vSwUpdM_GridRpc_InitComplexResponseClassBkGetResumeInfoType
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_GridRpc_InitComplexResponseClassBkGetResumeInfoType( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_GridSrvc_ServiceIdxType RequestServiceIdx,
  Std_ReturnType Result,
  P2CONST(vSwUpdM_BkPersist_ResumeInfoType, AUTOMATIC, VSWUPDM_APPL_CONST) ResumeInfo,
  vSwUpdM_GridRpc_ComplexResponseClassBkGetResumeInfoPtrType ComplexResponseClassBkGetResumeInfo)
{
  ComplexResponseClassBkGetResumeInfo->ResumeInfo = ResumeInfo;
  vSwUpdM_GridRpc_InitComplexResponseClassBaseType(RequestServiceIdx, Result, VSWUPDM_GRIDRPC_COMPLEXREPONSECLASS_BK_GET_RESUME_INFO, &ComplexResponseClassBkGetResumeInfo->Base);
}

/*********************
 * GRID SERVICE
 ********************/

#if (VSWUPDM_LOCALINSTANCE_ACTS_AS_SLAVE == STD_ON)

/**********************************************************************************************************************
 * vSwUpdM_RemoteBookkeeperRequest_IsRemoteUpdateResumeInfoAllowed
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(boolean, VSWUPDM_CODE) vSwUpdM_RemoteBookkeeperRequest_IsRemoteUpdateResumeInfoAllowed(void) /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
{
  boolean retVal;

  /* #10 If ResumeInfo is ACTIVE:
   *     RemoteUpdateResumeInfo shall be sent. */
  if (vSwUpdM_ResumeInfo.ResumeInfo.ServiceState == VSWUPDM_RESUME_STATE_ACTIVE)
  {
    retVal = TRUE;
  }
  else
  {
    switch (vSwUpdM_ResumeInfo.ResumeInfo.CurrentService)
    {
      case VSWUPDM_SID_OPEN_PARTITION:
      case VSWUPDM_SID_VALIDATE_PARTITION:
      case VSWUPDM_SID_INVALIDATE_PARTITION:
      case VSWUPDM_SID_SWAP_ACTIVE_PARTITION:
      case VSWUPDM_SID_SYNC_PARTITION:
      /* #20 If Partition-Services:
       *     RemoteUpdateResumeInfo shall not be sent. */
      {
        /* Do not send remoteUpdateResumeInfor for Partition-Services: */
        retVal = FALSE;
        break;
      }
      default:
      /* #30 Else:
       *     RemoteUpdateResumeInfo shall be sent. */
      {
        retVal = TRUE;
        break;
      }
    }
  }

  return retVal;
} /* vSwUpdM_RemoteBookkeeperRequest_IsRemoteUpdateResumeInfoAllowed */

/**********************************************************************************************************************
 * vSwUpdM_RemoteBookkeeperRequest
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_RemoteBookkeeperRequest( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_NodeIterType Target,
  vSwUpdM_JobOperationType Operation,
  P2CONST(vSwUpdM_EntityIdsType, AUTOMATIC, VSWUPDM_APPL_CONST) EntityIds,
  vSwUpdM_JobPtrType ParentJob)
{
  Std_ReturnType result; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vSwUpdM_GridSrvc_ServiceIdxType remoteServiceId = VSWUPDM_GRIDSRVC_SERVICEIDX_UNDEFINED; /* PRQA S 2981 */ /* MD_vSwUpdM_Rule2.2_2981_2892_RedundantInitialization */
  boolean isValidRemoteService = TRUE;

  VSWUPDM_DUMMY_STATEMENT(EntityIds); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  /* #10 Map Operation to Remote Service. */
  switch (Operation)
  {
    case VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_SET_MODULE_STATE:
    {
      remoteServiceId = VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_PERSIST_MODULE_STATE;
      break;
    }
    case VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_SET_MODULE_PROGRAMMING_ATTEMPTS:
    {
      remoteServiceId = VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_PERSIST_MODULE_PROGRAMMING_ATTEMPTS;
      break;
    }
    case VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_SET_MODULE_VALID:
    {
      remoteServiceId = VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_PERSIST_MODULE_VALID;
      break;
    }
    case VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_SET_REGION_STATE:
    {
      remoteServiceId = VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_PERSIST_REGION_STATE;
      break;
    }
    case VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_SET_REGION_PROGRAMMING_ATTEMPTS:
    {
      remoteServiceId = VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_PERSIST_REGION_PROGRAMMING_ATTEMPTS;
      break;
    }
    case VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_SET_SEGMENT_ATTRIBUTES:
    {
      remoteServiceId = VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_PERSIST_SEGMENT_ATTRIBUTES;
      break;
    }
    case VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_SET_RESUME_INFO:
    {
      if (vSwUpdM_RemoteBookkeeperRequest_IsRemoteUpdateResumeInfoAllowed() == TRUE)
      {
        remoteServiceId = VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_PERSIST_RESUME_INFO;
      }
      else
      {
        isValidRemoteService = FALSE;
      }
      break;
    }
    default:
    {
      isValidRemoteService = FALSE;
      break;
    }
  }

  if (isValidRemoteService == TRUE)
  {
    /* #20 On success prepare reception of Confirmation service. */
     vSwUpdM_RemotePrepareResponseRxTarget(Target, remoteServiceId, ParentJob);

    /* #30 On success trigger transmission of remote service. */
    result = vSwUpdM_RemoteTransmitBookkeeperRequest(vSwUpdM_GetDestinationMainOfNode(Target), remoteServiceId, EntityIds);
  }
  else
  {
    /* #40 Otherwise: No remote service required. */
    result = E_OK;
  }
  return result;
}
/* vSwUpdM_RemoteBookkeeperRequest */

/**********************************************************************************************************************
 * vSwUpdM_RemoteTransmitBookkeeperRequest
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_RemoteTransmitBookkeeperRequest(
  vSwUpdM_DestinationBookkeeperOfNodeType Target,
  vSwUpdM_GridSrvc_ServiceIdxType RemoteServiceId,
  P2CONST(vSwUpdM_EntityIdsType, AUTOMATIC, VSWUPDM_APPL_CONST) EntityIds)
{
  Std_ReturnType result;

  /* Trigger remote service depending on RemoteServiceId. */
  switch (RemoteServiceId)
  {
    case VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_PERSIST_MODULE_STATE:
    {
      result = vRpcProxy_vSwUpdM_RemoteUpdateModuleState_Target(Target, vSwUpdM_GetModuleHandleOfModule(EntityIds->ModuleId), vSwUpdM_ModulePendingAttributes.Attributes.State);
      break;
    }
    case VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_PERSIST_MODULE_VALID:
    {
      result = vRpcProxy_vSwUpdM_RemoteUpdateModuleValid_Target(Target, vSwUpdM_GetModuleHandleOfModule(EntityIds->ModuleId), vSwUpdM_ModulePendingAttributes.Attributes.IsValid, (uint32)vSwUpdM_ModulePendingAttributes.RevisionUpdate);
      break;
    }
    case VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_PERSIST_MODULE_PROGRAMMING_ATTEMPTS:
    {
      result = vRpcProxy_vSwUpdM_RemoteUpdateModuleProgrammingAttempts_Target(Target, vSwUpdM_GetModuleHandleOfModule(EntityIds->ModuleId), (uint32) vSwUpdM_ModulePendingAttributes.Attributes.ProgrammingAttempts);
      break;
    }
    case VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_PERSIST_REGION_STATE:
    {
      result = vRpcProxy_vSwUpdM_RemoteUpdateRegionState_Target(Target, vSwUpdM_GetRegionHandleOfRegion(EntityIds->RegionId), vSwUpdM_GetVarRegions(EntityIds->RegionIdx).PendingAttributesOfVarRegion.State);
      break;
    }
    case VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_PERSIST_REGION_PROGRAMMING_ATTEMPTS:
    {
      result = vRpcProxy_vSwUpdM_RemoteUpdateRegionProgrammingAttempts_Target(Target, vSwUpdM_GetRegionHandleOfRegion(EntityIds->RegionId), (uint32) vSwUpdM_GetVarRegions(EntityIds->RegionIdx).PendingAttributesOfVarRegion.ProgrammingAttempts);
      break;
    }
    case VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_PERSIST_SEGMENT_ATTRIBUTES:
    {
      vSwUpdM_RemoteSegmentInfoType remoteSegmentInfo;
      P2CONST(vSwUpdM_VarSegmentsType, AUTOMATIC, VSWUPDM_APPL_VAR) segment = vSwUpdM_GetAddrVarSegments(EntityIds->SegmentId.DynamicSegmentId);

      remoteSegmentInfo.StartAddress = segment->DynamicAttributesOfVarSegment.StartAddress;
      remoteSegmentInfo.InitialLength = segment->DynamicAttributesOfVarSegment.InitialLength;
      remoteSegmentInfo.LengthHandling = segment->DynamicAttributesOfVarSegment.LengthHandling;
      remoteSegmentInfo.State = segment->DynamicAttributesOfVarSegment.State;
      remoteSegmentInfo.Type = segment->TypeOfVarSegments;
      remoteSegmentInfo.IsOverflowable = segment->IsOverflowableOfVarSegments;

      result = vRpcProxy_vSwUpdM_RemoteUpdateSegmentAttributes_Target(Target, &remoteSegmentInfo, segment->DynamicAttributesOfVarSegment.State);
      break;
    }
    case VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_PERSIST_RESUME_INFO:
    {
      vSwUpdM_BkPersist_ResumeInfoType BkResumeInfo;

      vSwUpdM_Bookkeeper_ConvertExtended2BkResumeInfo(&BkResumeInfo, &vSwUpdM_PendingResumeInfo);

      result = vRpcProxy_vSwUpdM_RemoteUpdateResumeInfo_Target(Target, &BkResumeInfo);
      break;
    }
    default:
    {
      result = VSWUPDM_E_INV_STATE;
      break;
    }
  }

  return result;
  /* PRQA S 6050 1 */ /* MD_MSR_STCAL */
}
/* vSwUpdM_RemoteTransmitBookkeeperRequest */
#endif

/**********************************************************************************************************************
 * vSwUpdM_GetProcessIdByProcessHandle
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GetProcessIdByProcessHandle( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_ProcessHandleOfDataProcessesType DataProcessHandle,
  P2VAR(vSwUpdM_DataProcessesIterType, AUTOMATIC, VSWUPDM_APPL_VAR) ProcessId)
{
  Std_ReturnType result = E_NOT_OK;
  vSwUpdM_DataProcessesIterType processId;

  /* #10 Iterate over all data processes. */
  for (processId = 0; processId < vSwUpdM_GetSizeOfDataProcesses(); processId++)
  {
    /* #20 Find the one with matching handle value. */
    if ( (vSwUpdM_IsProcessHandleUsedOfDataProcesses(processId))
      && (vSwUpdM_GetProcessHandleOfDataProcesses(processId) == DataProcessHandle) )
    {
      /* #30 Stop search and return index of found data process. */
      result = E_OK;
      (*ProcessId) = processId;
      break;
    }
  }

  return result;
} /* vSwUpdM_GetProcessIdByProcessHandle */

/*********************
 * GRID NODE
 ********************/

# define VSWUPDM_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* VSWUPDM_GRID_IMPL_H */

/**********************************************************************************************************************
 *  END OF FILE: vSwUpdM_Grid_Impl.h
 *********************************************************************************************************************/
