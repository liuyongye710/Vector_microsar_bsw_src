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
/*!        \file  vSwUpdM_GridNode_Impl.h
 *        \brief  vSwUpdM_GridNode implementation header file
 *      \details  vSwUpdM_GridNode subcomponent public inline implementations.
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

#if !defined (VSWUPDM_GRIDNODE_IMPL_H)
# define VSWUPDM_GRIDNODE_IMPL_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
/* GridNode interface header */
#include "vSwUpdM_GridNode_If.h"

/* Implementation header of containing MultipleUnit */
#include "vSwUpdM_Grid_Impl.h"

/* Other MultipleUnits used by GridNode_Impl (Prefer smallest set required, i.e. prefer _Types over _If over _Impl) */

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
#define VSWUPDM_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 * vSwUpdM_GridNode_GetNodeResponseClassBuffer
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(vSwUpdM_GridSrvc_ResponseClassBasePtrType, VSWUPDM_CODE) vSwUpdM_GridNode_GetNodeResponseClassBuffer( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_GridSrvc_ResponseClassBasePtrType BasePointer,
  vSwUpdM_NodeIterType NodeIndex)
{
  vSwUpdM_GridSrvc_ResponseClassBasePtrType retVal = NULL_PTR; /* PRQA S 2981 */ /* MD_MSR_RetVal */

  switch (BasePointer->ResponseClassIndex)
  {
    default:
    /* case VSWUPDM_GRIDSRVC_RESPONSECLASS_MAIN: */
    {
      retVal = (vSwUpdM_GridSrvc_ResponseClassBasePtrType) & (((vSwUpdM_GridSrvc_ResponseClassMainPtrType)BasePointer)[NodeIndex]); /* PRQA S 0310 */ /* MD_vSwUpdM_Rule11.3_0310_ServiceParameterCast */
      break;
    }
    case VSWUPDM_GRIDSRVC_RESPONSECLASS_MAINTENANCE:
    {
      retVal = (vSwUpdM_GridSrvc_ResponseClassBasePtrType) & (((vSwUpdM_GridSrvc_ResponseClassMaintenancePtrType)BasePointer)[NodeIndex]); /* PRQA S 0310 */ /* MD_vSwUpdM_Rule11.3_0310_ServiceParameterCast */
      break;
    }
    case VSWUPDM_GRIDSRVC_RESPONSECLASS_SUSPEND:
    {
      retVal = (vSwUpdM_GridSrvc_ResponseClassBasePtrType)& (((vSwUpdM_GridSrvc_ResponseClassSuspendPtrType)BasePointer)[NodeIndex]); /* PRQA S 0310 */ /* MD_vSwUpdM_Rule11.3_0310_ServiceParameterCast */
      break;
    }
    case VSWUPDM_GRIDSRVC_RESPONSECLASS_BK:
    {
      retVal = (vSwUpdM_GridSrvc_ResponseClassBasePtrType)& (((vSwUpdM_GridSrvc_ResponseClassBookkeeperPtrType)BasePointer)[NodeIndex]); /* PRQA S 0310 */ /* MD_vSwUpdM_Rule11.3_0310_ServiceParameterCast */
      break;
    }
  }

  return retVal;
} /* vSwUpdM_GridNode_GetNodeResponseClassBuffer */

/**********************************************************************************************************************
 * vSwUpdM_GridNode_GetResult
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GridNode_GetResult( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_GridSrvc_ServiceIdxType ServiceIndex,
  vSwUpdM_NodeIterType NodeIndex
)
{
  vSwUpdM_GridSrvc_ResponseClassBasePtrType responseClassBase;
  responseClassBase = vSwUpdM_GridSrvc_GetResponseClassNodeBuffer(ServiceIndex);
  return ((vSwUpdM_GridSrvc_ResponseClassSimpleResponsePtrType) vSwUpdM_GridNode_GetNodeResponseClassBuffer(responseClassBase, NodeIndex))->Result; /* PRQA S 0310 */ /* MD_vSwUpdM_Rule11.3_0310_ServiceParameterCast */
} /* vSwUpdM_GridNode_GetResult */

/**********************************************************************************************************************
 * vSwUpdM_GridNode_SetResult
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_GridNode_SetResult( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_GridSrvc_ServiceIdxType ServiceIndex,
  vSwUpdM_NodeIterType NodeIndex,
  Std_ReturnType Result
)
{
  vSwUpdM_GridSrvc_ResponseClassBasePtrType baseResponse;
  vSwUpdM_GridSrvc_ResponseClassSimpleResponsePtrType simpleResponse;

  baseResponse = vSwUpdM_GridSrvc_GetResponseClassNodeBuffer(ServiceIndex);
  simpleResponse = (vSwUpdM_GridSrvc_ResponseClassSimpleResponsePtrType) vSwUpdM_GridNode_GetNodeResponseClassBuffer(baseResponse, NodeIndex); /* PRQA S 0310 */ /* MD_vSwUpdM_Rule11.3_0310_ServiceParameterCast */

  simpleResponse->Result = Result;
} /* vSwUpdM_GridNode_SetResult */

/**********************************************************************************************************************
 * vSwUpdM_GridNode_GetResultValid
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(boolean, VSWUPDM_CODE) vSwUpdM_GridNode_GetResultValid( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_GridSrvc_ServiceIdxType ServiceIndex,
  vSwUpdM_NodeIterType NodeIndex
)
{
  vSwUpdM_GridSrvc_ResponseClassBasePtrType responseClassBase;
  responseClassBase = vSwUpdM_GridSrvc_GetResponseClassNodeBuffer(ServiceIndex);
  return ((vSwUpdM_GridSrvc_ResponseClassSimpleResponsePtrType)vSwUpdM_GridNode_GetNodeResponseClassBuffer(responseClassBase, NodeIndex))->ResultValid; /* PRQA S 0310 */ /* MD_vSwUpdM_Rule11.3_0310_ServiceParameterCast */
} /* vSwUpdM_GridNode_GetResultValid */

/**********************************************************************************************************************
 * vSwUpdM_GridNode_SetResultValid
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_GridNode_SetResultValid( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_GridSrvc_ServiceIdxType ServiceIndex,
  vSwUpdM_NodeIterType NodeIndex,
  boolean ResultValid
)
{
  vSwUpdM_GridSrvc_ResponseClassBasePtrType responseClassBase;
  responseClassBase = vSwUpdM_GridSrvc_GetResponseClassNodeBuffer(ServiceIndex);
  ((vSwUpdM_GridSrvc_ResponseClassSimpleResponsePtrType)vSwUpdM_GridNode_GetNodeResponseClassBuffer(responseClassBase, NodeIndex))->ResultValid = ResultValid; /* PRQA S 0310 */ /* MD_vSwUpdM_Rule11.3_0310_ServiceParameterCast */
} /* vSwUpdM_GridNode_SetResultValid */

/**********************************************************************************************************************
 * vSwUpdM_GridNode_GetServiceState
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(vSwUpdM_GridChannel_ServiceStateType, VSWUPDM_CODE) vSwUpdM_GridNode_GetServiceState( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_GridSrvc_ServiceIdxType ServiceIndex,
  vSwUpdM_NodeIterType NodeIndex
)
{
  vSwUpdM_GridSrvc_ResponseClassBasePtrType responseClassBase;
  responseClassBase = vSwUpdM_GridSrvc_GetResponseClassNodeBuffer(ServiceIndex);
  return vSwUpdM_GridNode_GetNodeResponseClassBuffer(responseClassBase, NodeIndex)->ServiceState;
} /* vSwUpdM_GridNode_GetServiceState */

/**********************************************************************************************************************
 * vSwUpdM_GridNode_SetServiceState
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_GridNode_SetServiceState( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_GridSrvc_ServiceIdxType ServiceIndex,
  vSwUpdM_NodeIterType NodeIndex,
  vSwUpdM_GridChannel_ServiceStateType State
)
{
  vSwUpdM_GridSrvc_ResponseClassBasePtrType responseClassBase;
  responseClassBase = vSwUpdM_GridSrvc_GetResponseClassNodeBuffer(ServiceIndex);
  vSwUpdM_GridNode_GetNodeResponseClassBuffer(responseClassBase, NodeIndex)->ServiceState = State;
} /* vSwUpdM_GridNode_SetServiceState */

# define VSWUPDM_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* VSWUPDM_GRIDNODE_IMPL_H */

/**********************************************************************************************************************
 *  END OF FILE: vSwUpdM_GridNode_Impl.h
 *********************************************************************************************************************/
