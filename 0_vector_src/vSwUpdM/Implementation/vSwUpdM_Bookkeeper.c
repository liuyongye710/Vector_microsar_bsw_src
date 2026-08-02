/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2021 by Vector Informatik GmbH.                                                  All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/*!        \file  vSwUpdM_Bookkeeper.c
 *        \brief  vSwUpdM_Bookkeeper source file
 *      \details  Implementation of the vSwUpdM_Bookkeeper subcomponent.
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

#define VSWUPDM_BOOKKEEPER_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
/* Bookkeeper implementation header */
#include "vSwUpdM_Bookkeeper_Impl.h"

/* Implementation headers of all contained Units */
#include "vSwUpdM_BkPersistServer_Impl.h"
#include "vSwUpdM_BkPersistClient_Impl.h"

#include "vSwUpdM_Grid_Impl.h"
#include "vSwUpdM_CfgTypes.h"

#include "vSwUpdM.h"
#include "vSwUpdM_CfgTypes.h"
#include "vSwUpdM_Lcfg.h"
/* Other MultipleUnits used by Bookkeeper (Prefer smallest set required, i.e. prefer _Types over _If over _Impl) */

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/
#define VSWUPDM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define VSWUPDM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
#define VSWUPDM_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * vSwUpdM_Bookkeeper_InitMemory
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(void, VSWUPDM_CODE) vSwUpdM_Bookkeeper_InitMemory(void)
{
  vSwUpdM_BkPersistServer_InitMemory();
} /* vSwUpdM_Bookkeeper_InitMemory */

/**********************************************************************************************************************
 * vSwUpdM_Bookkeeper_Init
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(void, VSWUPDM_CODE) vSwUpdM_Bookkeeper_Init(void)
{
  vSwUpdM_BkPersistServer_Init();
  vSwUpdM_BkPersistClient_Init();
} /* vSwUpdM_Bookkeeper_Init */

/**********************************************************************************************************************
 * vSwUpdM_Bookkeeper_Set
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Bookkeeper_Set(
  P2CONST(vSwUpdM_EntityIdsType, AUTOMATIC, VSWUPDM_APPL_CONST) EntityIds,
  vSwUpdM_BkPersist_ParamType ParamType,
  vSwUpdM_BkPersist_SizeOfParameterType ParameterSize,
  P2VAR(void, AUTOMATIC, VSWUPDM_APPL_VAR) Parameter)
{
  vSwUpdM_BkPersist_EntityType Entities;

  /* #10 Initialize values. */
  Entities.PartitionId              = EntityIds->PartitionId;
  Entities.ModuleId                 = EntityIds->ModuleId;
  Entities.RegionId                 = EntityIds->RegionId;
  Entities.SegmentIdx               = EntityIds->SegmentIdx;
  Entities.PartitionStateChangeMask = VSWUPDM_PART_STATE_UNDEFINED;

  /* #20 In case of segment write address write segment index has to be used as segment index. */
  if (ParamType == VSWUPDM_BKPERSIST_PARAM_SEGMENT_WRITE_ADDRESS)
  {
    Entities.SegmentIdx = vSwUpdM_GetVarSegments(EntityIds->SegmentId.DynamicSegmentId).WriteSegmentIdx;
  }

  /* #30 Calculate partition state change mask in case its needed. */
  if (ParamType == VSWUPDM_BKPERSIST_PARAM_PARTITION_STATE)
  {
    /* PRQA S 0311, 0316 1 */ /* MD_vSwUpdM_Rule11.5_0311_RemoteBufferConstConfigValues, MD_vSwUpdM_Rule11.5_0316_VoidPtrTypedPtr */
    Entities.PartitionStateChangeMask = vSwUpdM_GetVarPartitions(Entities.PartitionId).DynamicAttributesOfVarPartitions.State ^ *(vSwUpdM_PartitionStateType*)Parameter;
  }

  /* #40 Forward setter request to BkPersistClient. */
  return vSwUpdM_BkPersistClient_Set(&Entities, ParamType, ParameterSize, Parameter);
} /* vSwUpdM_Bookkeeper_Set */

/**********************************************************************************************************************
 * vSwUpdM_Bookkeeper_Get
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Bookkeeper_Get(
  P2CONST(vSwUpdM_EntityIdsType, AUTOMATIC, VSWUPDM_APPL_CONST) EntityIds,
  vSwUpdM_BkPersist_ParamType ParamType,
  vSwUpdM_BkPersist_SizeOfParameterType ParameterSize,
  P2VAR(void, AUTOMATIC, VSWUPDM_APPL_VAR) Parameter)
{
  vSwUpdM_BkPersist_EntityType Entities;

  /* #10 Initialize values. */
  Entities.PartitionId              = EntityIds->PartitionId;
  Entities.ModuleId                 = EntityIds->ModuleId;
  Entities.RegionId                 = EntityIds->RegionId;
  Entities.SegmentIdx               = EntityIds->SegmentIdx;
  Entities.PartitionStateChangeMask = VSWUPDM_PART_STATE_UNDEFINED;

  /* #20 In case of segment write address write segment index has to be used as segment index. */
  if (ParamType == VSWUPDM_BKPERSIST_PARAM_SEGMENT_WRITE_ADDRESS)
  {
    Entities.SegmentIdx = vSwUpdM_GetVarSegments(EntityIds->SegmentId.DynamicSegmentId).WriteSegmentIdx;
  }

  /* #30 Forward setter request to BkPersistClient. */
  return vSwUpdM_BkPersistClient_Get(&Entities, ParamType, ParameterSize, Parameter);
} /* vSwUpdM_Bookkeeper_Get */

/**********************************************************************************************************************
 * vSwUpdM_Bookkeeper_Open
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Bookkeeper_Open(vSwUpdM_NodeGroupIterType TargetGroup)
{
   return vSwUpdM_BkPersistClient_Open(TargetGroup);

} /* vSwUpdM_Bookkeeper_Open */

/**********************************************************************************************************************
 * vSwUpdM_Bookkeeper_Close
 *********************************************************************************************************************/
 /*!
 * Internal comment removed.
 *
 *
 *
 *
 */
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Bookkeeper_Close(vSwUpdM_NodeGroupIterType TargetGroup)
{
   return vSwUpdM_BkPersistClient_Close(TargetGroup);

} /* vSwUpdM_Bookkeeper_Close */

/**********************************************************************************************************************
 * vSwUpdM_Bookkeeper_ServerExecute
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(void, VSWUPDM_CODE) vSwUpdM_Bookkeeper_ServerExecute(void)
{
  boolean hasPersistServer = (boolean) vSwUpdM_HasBkPersistServer_VarSlots(); /* PRQA S 2981, 2995, 4304 */ /* MD_vSwUpdM_Rule2.2_2981_2892_RedundantInitialization, MD_vSwUpdM_Rule14.3_2991_2992_2995_2996_Rule2.2_AlwaysTrueFalse, MD_MSR_AutosarBoolean */

  /* Avoid execution if no PersistServer_Slot available */
  if (hasPersistServer == TRUE) /* PRQA S 2991, 2995 */ /* MD_vSwUpdM_Rule14.3_2991_2992_2995_2996_Rule2.2_AlwaysTrueFalse, MD_vSwUpdM_Rule14.3_2991_2992_2995_2996_Rule2.2_AlwaysTrueFalse */
  {
    if(vSwUpdM_BkPersistServer_NeedsExecution() == TRUE)
    {
      vSwUpdM_BkPersistServer_Execute();
    }
  }
} /* vSwUpdM_Bookkeeper_ServerExecute */

/**********************************************************************************************************************
 * vSwUpdM_GetCurrentPersistClientNode
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GetCurrentPersistClientNode(P2VAR(vSwUpdM_NodeIterType, AUTOMATIC, VSWUPDM_APPL_VAR) Node)
{
  Std_ReturnType retVal = E_NOT_OK;

  *Node = vSwUpdM_BkPersistServer_GetCurrentClientNode();

  if (*Node < vSwUpdM_GetSizeOfNode())
  {
    retVal = E_OK;
  }

  return retVal;
} /* vSwUpdM_GetCurrentPersistClientNode */

/**********************************************************************************************************************
 * vSwUpdM_Bookkeeper_GetIdsByHandles
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(void, VSWUPDM_CODE) vSwUpdM_Bookkeeper_GetIdsByHandles(
  P2CONST(vSwUpdM_BkPersist_EntityHandleType, AUTOMATIC, VSWUPDM_APPL_VRPCPROXY_DATA) HandleEntities,
  P2VAR(vSwUpdM_BkPersist_EntityType, AUTOMATIC, VSWUPDM_APPL_DATA) IdEntities)
{
  vSwUpdM_PartitionIterType partitionId;
  vSwUpdM_ModuleIdType      moduleId = VSWUPDM_INVALID_ID;
  vSwUpdM_RegionIdType      regionId = VSWUPDM_INVALID_ID;

  /* #10 Initialize with invalid values. */
  IdEntities->PartitionId = VSWUPDM_INVALID_ID;
  IdEntities->ModuleId    = VSWUPDM_INVALID_ID;
  IdEntities->RegionId    = VSWUPDM_INVALID_ID;

  vSwUpdM_DevError_Assert(HandleEntities != NULL_PTR, VSWUPDM_DEVERROR_ASSERT_35); /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */

  /* #20 Get PartitionId. */
  if (HandleEntities->PartitionHandle != VSWUPDM_NO_PARTITIONHANDLEOFPARTITION)
  {
    for (partitionId = 0; partitionId < vSwUpdM_GetStaticNumberOfPartitions(); partitionId++)
    {
      if (vSwUpdM_GetPartitionHandleOfPartition(partitionId) == HandleEntities->PartitionHandle)
      {
        IdEntities->PartitionId = (vSwUpdM_PartitionIdType)partitionId;
        break;
      }
    }
  }

  /* #30 Get Module Id. */
  if (HandleEntities->ModuleHandle != VSWUPDM_NO_MODULEHANDLEOFMODULE)
  {
    if (vSwUpdM_GetModuleIdByHandle(&moduleId, HandleEntities->ModuleHandle) == E_OK)
    {
      IdEntities->ModuleId = moduleId;
    }
  }

  /* #40 Get Region Id. */
  if (HandleEntities->RegionHandle != VSWUPDM_NO_REGIONHANDLEOFREGION)
  {
    if (vSwUpdM_GetRegionIdByHandle(&regionId, HandleEntities->RegionHandle) == E_OK)
    {
      IdEntities->RegionId = regionId;
    }
  }

  /* #50 Get Segment Index. */
  IdEntities->SegmentIdx = HandleEntities->SegmentIdx;

  /* #60 Get partition state change mask. */
  IdEntities->PartitionStateChangeMask = HandleEntities->PartitionStateChangeMask;
} /* vSwUpdM_Bookkeeper_GetIdsByHandles */

/**********************************************************************************************************************
 * vSwUpdM_Bookkeeper_GetOwnerGroupOfEntity
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Bookkeeper_GetOwnerGroupOfEntity(
  P2CONST(vSwUpdM_BkPersist_EntityType, AUTOMATIC, VSWUPDM_APPL_VAR) EntityIds,
  vSwUpdM_BkPersist_ParamType ParamType,
  P2VAR(vSwUpdM_NodeGroupIterType, AUTOMATIC, VSWUPDM_APPL_VAR) OwnerGroup)
{
  Std_ReturnType retVal = E_NOT_OK;
  switch (ParamType)
  {
    case VSWUPDM_BKPERSIST_PARAM_MODULE_STATE:
    case VSWUPDM_BKPERSIST_PARAM_MODULE_VALIDITY:
    case VSWUPDM_BKPERSIST_PARAM_MODULE_REVISION:
    case VSWUPDM_BKPERSIST_PARAM_MODULE_PROGRAMMING_ATTEMPTS:
    case VSWUPDM_BKPERSIST_PARAM_MODULE_SEGMENT_COUNT:
    case VSWUPDM_BKPERSIST_PARAM_SEGMENT_ATTRIBUTES:
    case VSWUPDM_BKPERSIST_PARAM_SEGMENT_WRITE_ADDRESS:
    {
      /* Return owner of the module. */
      (*OwnerGroup) = vSwUpdM_GetNodeGroupOwnersIdxOfModule(EntityIds->ModuleId);
      retVal = E_OK;

      break;
    }
    case VSWUPDM_BKPERSIST_PARAM_REGION_STATE:
    case VSWUPDM_BKPERSIST_PARAM_REGION_PROGRAMMING_ATTEMPTS:
    case VSWUPDM_BKPERSIST_PARAM_REGION_ERASE_ADDRESS:
    {
      /* Return owner of the region. */
      (*OwnerGroup) = vSwUpdM_GetNodeGroupOwnersIdxOfRegion(EntityIds->RegionId);
      retVal = E_OK;

      break;
    }
    default:
    /* case VSWUPDM_BKPERSIST_PARAM_UPDATE_STATE: */
    /* case VSWUPDM_BKPERSIST_PARAM_PARTITION_STATE: */
    /* case VSWUPDM_BKPERSIST_PARAM_PARTITION_VALIDITY: */
    /* case VSWUPDM_BKPERSIST_PARAM_PARTITION_REVISION: */
    /* case VSWUPDM_BKPERSIST_PARAM_RESUME_INFO: */
    {
      /* These entities don't have a specified owner. */
      break;
    }
  }

  return retVal;
} /* vSwUpdM_Bookkeeper_GetOwnerGroupOfEntity */

#define VSWUPDM_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/***********************************************************************************************************************
 *  MISRA JUSTIFICATIONS
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  SILENTBSW JUSTIFICATIONS
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  COVERAGE JUSTIFICATIONS
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  END OF FILE: vSwUpdM_Bookkeeper.c
 *********************************************************************************************************************/
