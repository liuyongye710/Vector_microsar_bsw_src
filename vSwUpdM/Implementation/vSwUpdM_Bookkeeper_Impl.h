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
/*!        \file  vSwUpdM_Bookkeeper_Impl.h
 *        \brief  vSwUpdM_Bookkeeper implementation header file
 *      \details  vSwUpdM_Bookkeeper subcomponent public inline implementations.
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

#if !defined (VSWUPDM_BOOKKEEPER_IMPL_H)
# define VSWUPDM_BOOKKEEPER_IMPL_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
/* Bookkeeper interface header */
#include "vSwUpdM_Bookkeeper_If.h"
#include "vSwUpdM_BkPersistClient_If.h"

/* Other MultipleUnits used by Bookkeeper_Impl (Prefer smallest set required, i.e. prefer _Types over _If over _Impl) */
#include "vSwUpdM_DevError_Impl.h"

#include "vSwUpdM_Lcfg.h"

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
 * vSwUpdM_Bookkeeper_GetHandlesByIds
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_Bookkeeper_GetHandlesByIds(    /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  P2CONST(vSwUpdM_BkPersist_EntityType, AUTOMATIC, VSWUPDM_APPL_DATA) IdEntities,
  P2VAR(vSwUpdM_BkPersist_EntityHandleType, AUTOMATIC, VSWUPDM_APPL_VRPCPROXY_DATA) HandleEntities)
{
  if (IdEntities->PartitionId != VSWUPDM_INVALID_ID)
  {
    HandleEntities->PartitionHandle = vSwUpdM_GetPartitionHandleOfPartition(IdEntities->PartitionId);
  }
  else
  {
    HandleEntities->PartitionHandle = VSWUPDM_NO_PARTITIONHANDLEOFPARTITION;
  }

  if (IdEntities->ModuleId != VSWUPDM_INVALID_ID)
  {
    HandleEntities->ModuleHandle = vSwUpdM_GetModuleHandleOfModule(IdEntities->ModuleId);
  }
  else
  {
    HandleEntities->ModuleHandle = VSWUPDM_NO_MODULEHANDLEOFMODULE;
  }

  if (IdEntities->RegionId != VSWUPDM_INVALID_ID)
  {
    HandleEntities->RegionHandle = vSwUpdM_GetRegionHandleOfRegion(IdEntities->RegionId);
  }
  else
  {
    HandleEntities->RegionHandle = VSWUPDM_NO_REGIONHANDLEOFREGION;
  }

  HandleEntities->SegmentIdx               = IdEntities->SegmentIdx;
  HandleEntities->PartitionStateChangeMask = IdEntities->PartitionStateChangeMask;
} /* vSwUpdM_Bookkeeper_GetHandlesByIds */

/**********************************************************************************************************************
 * vSwUpdM_Bookkeeper_ExtendedResumeInfo2BkResumeInfoType
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_Bookkeeper_ConvertExtended2BkResumeInfo(   /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  P2VAR(vSwUpdM_BkPersist_ResumeInfoType, AUTOMATIC, VSWUPDM_APPL_VAR) BkResumeInfo,
  P2CONST(vSwUpdM_ExtendedResumeInfoType, AUTOMATIC, VSWUPDM_APPL_VAR) ExtendedResumeInfo)
{
  BkResumeInfo->StreamAddress  = ExtendedResumeInfo->ResumeInfo.StreamAddress;
  BkResumeInfo->MemoryAddress  = ExtendedResumeInfo->ResumeInfo.MemoryAddress;
  BkResumeInfo->PartitionState = ExtendedResumeInfo->ResumeInfo.PartitionState;
  BkResumeInfo->CurrentService = ExtendedResumeInfo->ResumeInfo.CurrentService;
  BkResumeInfo->ServiceState   = ExtendedResumeInfo->ResumeInfo.ServiceState;
  BkResumeInfo->IsAddressValid = ExtendedResumeInfo->ResumeInfo.IsAddressValid;
  BkResumeInfo->TriggerAddress = ExtendedResumeInfo->TriggerAddress;
} /* vSwUpdM_Bookkeeper_ConvertExtended2BkResumeInfo */

/**********************************************************************************************************************
 * vSwUpdM_Bookkeeper_BkResumeInfoType2ExtendedResumeInfo
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_Bookkeeper_ConvertBk2ExtendedResumeInfo(  /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  P2VAR(vSwUpdM_ExtendedResumeInfoType, AUTOMATIC, VSWUPDM_APPL_VAR) ExtendedResumeInfo,
  P2CONST(vSwUpdM_BkPersist_ResumeInfoType, AUTOMATIC, VSWUPDM_APPL_VAR) BkResumeInfo)
{
  ExtendedResumeInfo->ResumeInfo.StreamAddress  = BkResumeInfo->StreamAddress;
  ExtendedResumeInfo->ResumeInfo.MemoryAddress  = BkResumeInfo->MemoryAddress;
  ExtendedResumeInfo->ResumeInfo.PartitionState = BkResumeInfo->PartitionState;
  ExtendedResumeInfo->ResumeInfo.CurrentService = BkResumeInfo->CurrentService;
  ExtendedResumeInfo->ResumeInfo.ServiceState   = BkResumeInfo->ServiceState;
  ExtendedResumeInfo->ResumeInfo.IsAddressValid = BkResumeInfo->IsAddressValid;
  ExtendedResumeInfo->TriggerAddress            = BkResumeInfo->TriggerAddress;
} /* vSwUpdM_Bookkeeper_ConvertBk2ExtendedResumeInfo */

/**********************************************************************************************************************
 * vSwUpdM_Bookkeeper_Sync
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_Bookkeeper_Sync(void) /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
{
  vSwUpdM_BkPersistClient_Sync();
} /* vSwUpdM_Bookkeeper_Sync */

/**********************************************************************************************************************
 * vSwUpdM_Bookkeeper_ClientExecute
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Bookkeeper_ClientExecute(void) /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
{
  Std_ReturnType retVal;

  switch (vSwUpdM_BkPersistClient_Execute())
  {
    case VSWUPDM_BKPERSIST_REQUESTSTATE_WAIT_RESPONSE:
    case VSWUPDM_BKPERSIST_REQUESTSTATE_READY:
    {
      retVal = VSWUPDM_E_PENDING;
      break;
    }
    case VSWUPDM_BKPERSIST_REQUESTSTATE_IDLE:
    {
      retVal = E_OK;
      break;
    }
    default:
    /* case VSWUPDM_BKPERSIST_REQUESTSTATE_FAILED: */
    {
      retVal = E_NOT_OK;
      break;
    }
  }
  return retVal;
}

# define VSWUPDM_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* VSWUPDM_BOOKKEEPER_IMPL_H */

/**********************************************************************************************************************
 *  END OF FILE: vSwUpdM_Bookkeeper_Impl.h
 *********************************************************************************************************************/
