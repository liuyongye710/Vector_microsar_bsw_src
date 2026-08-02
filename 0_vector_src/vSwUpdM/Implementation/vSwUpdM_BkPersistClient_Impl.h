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
/*!        \file  vSwUpdM_BkPersistClient_Impl.h
 *        \brief  vSwUpdM_BkPersistClient implementation header file
 *      \details  vSwUpdM_BkPersistClient subcomponent public inline implementations.
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

#if !defined (VSWUPDM_BKPERSISTCLIENT_IMPL_H)
# define VSWUPDM_BKPERSISTCLIENT_IMPL_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
/* BkPersistClient interface header */
#include "vSwUpdM_BkPersistClient_If.h"

/* Implementation header of containing MultipleUnit */
#include "vSwUpdM_Bookkeeper_Impl.h"

/* Other MultipleUnits used by BkPersistClient_Impl (Prefer smallest set required, i.e. prefer _Types over _If over _Impl) */

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
 * vSwUpdM_BkPersistClient_StoreGetGenericParameterResponse
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_BkPersistClient_StoreGetGenericParameterResponse( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_BkPersist_GenericParameterType GenericValue)
{
  vSwUpdM_BkPersistClient_RequestPtrType activeRequest = vSwUpdM_BkPersistClient_GetActiveRequest(); /* PRQA S 3679 */ /* MD_vSwUpdM_Rule8.13_3679_PointerToModifiableData */

  /* Aggregate partition state multi responses. */
  if (activeRequest->ParamType == VSWUPDM_BKPERSIST_PARAM_PARTITION_STATE)
  {
    vSwUpdM_BkPersistClient_LastPartitionStateResult |= (vSwUpdM_PartitionStateType)GenericValue;
    /* PRQA S 0311, 0316 1 */ /* MD_vSwUpdM_Rule11.5_0311_RemoteBufferConstConfigValues, MD_vSwUpdM_Rule11.5_0316_VoidPtrTypedPtr */
    *(P2VAR(vSwUpdM_PartitionStateType, AUTOMATIC, VSWUPDM_APPL_VAR))activeRequest->ResponseBuffer = vSwUpdM_BkPersistClient_LastPartitionStateResult;
  }
  else
  {
    switch (activeRequest->ResponseSize)
    {
      case sizeof(uint32):
      {
        /* PRQA S 0311 1 */ /* MD_vSwUpdM_Rule11.5_0311_RemoteBufferConstConfigValues */
        *(P2VAR(uint32, AUTOMATIC, VSWUPDM_APPL_VAR))activeRequest->ResponseBuffer = (uint32)GenericValue; /* PRQA S 0316 */ /* MD_vSwUpdM_Rule11.5_0316_PersistCastPtrVoidPtrObj */
        break;
      }
      case sizeof(uint16):
      {
        /* PRQA S 0311 1 */ /* MD_vSwUpdM_Rule11.5_0311_RemoteBufferConstConfigValues */
        *(P2VAR(uint16, AUTOMATIC, VSWUPDM_APPL_VAR))activeRequest->ResponseBuffer = (uint16)GenericValue; /* PRQA S 0316 */ /* MD_vSwUpdM_Rule11.5_0316_PersistCastPtrVoidPtrObj */
        break;
      }
      default:
      /* case sizeof(uint8): - smallest memory usage */
      {
        /* PRQA S 0311 1 */ /* MD_vSwUpdM_Rule11.5_0311_RemoteBufferConstConfigValues */
        *(P2VAR(uint8, AUTOMATIC, VSWUPDM_APPL_VAR))activeRequest->ResponseBuffer = (uint8)GenericValue; /* PRQA S 0316 */ /* MD_vSwUpdM_Rule11.5_0316_PersistCastPtrVoidPtrObj */
        break;
      }
    }
  }

  /* Reset last result with each single request and with last multi request. */
  if (activeRequest->RemainingMultiReq == 0u)
  {
    vSwUpdM_BkPersistClient_LastPartitionStateResult = 0u;
  }
} /* vSwUpdM_BkPersistClient_StoreGetGenericParameterResponse */

/**********************************************************************************************************************
 * vSwUpdM_BkPersistClient_StoreGetSegmentAttributesResponse
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_BkPersistClient_StoreGetSegmentAttributesResponse( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  P2CONST(vSwUpdM_BkPersist_SegmentAttributesType, AUTOMATIC, VSWUPDM_APPL_VRPCPROXY_DATA) SegmentAttributes)
{
  vSwUpdM_BkPersistClient_RequestPtrType activeRequest = vSwUpdM_BkPersistClient_GetActiveRequest(); /* PRQA S 3679 */ /* MD_vSwUpdM_Rule8.13_3679_PointerToModifiableData */

  /* PRQA S 0311 1 */ /* MD_vSwUpdM_Rule11.5_0311_RemoteBufferConstConfigValues */
  *(vSwUpdM_BkPersist_SegmentAttributesType*)activeRequest->ResponseBuffer = *SegmentAttributes; /* PRQA S 0316 */ /* MD_vSwUpdM_Rule11.5_0316_PersistCastPtrVoidPtrObj */
} /* vSwUpdM_BkPersistClient_StoreGetSegmentAttributesResponse */

/**********************************************************************************************************************
 * vSwUpdM_BkPersistClient_StoreGetResumeInfoResponse
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_BkPersistClient_StoreGetResumeInfoResponse( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  P2CONST(vSwUpdM_BkPersist_ResumeInfoType, AUTOMATIC, VSWUPDM_APPL_VAR) ResumeInfo)
{
  vSwUpdM_BkPersistClient_RequestPtrType activeRequest = vSwUpdM_BkPersistClient_GetActiveRequest(); /* PRQA S 3679 */ /* MD_vSwUpdM_Rule8.13_3679_PointerToModifiableData */
  /* PRQA S 0311 1 */ /* MD_vSwUpdM_Rule11.5_0311_RemoteBufferConstConfigValues */
  vSwUpdM_Bookkeeper_ConvertBk2ExtendedResumeInfo((vSwUpdM_ExtendedResumeInfoType*)activeRequest->ResponseBuffer, ResumeInfo); /* PRQA S 0316 */ /* MD_vSwUpdM_Rule11.5_0316_PersistCastPtrVoidPtrObj */
} /* vSwUpdM_BkPersistClient_StoreGetResumeInfoResponse */

# define VSWUPDM_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* VSWUPDM_BKPERSISTCLIENT_IMPL_H */

/**********************************************************************************************************************
 *  END OF FILE: vSwUpdM_BkPersistClient_Impl.h
 *********************************************************************************************************************/
