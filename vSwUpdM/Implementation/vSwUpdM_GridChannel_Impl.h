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
/*!        \file  vSwUpdM_GridChannel_Impl.h
 *        \brief  vSwUpdM_GridChannel implementation header file
 *      \details  vSwUpdM_GridChannel subcomponent public inline implementations.
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

#if !defined (VSWUPDM_GRIDCHANNEL_IMPL_H)
# define VSWUPDM_GRIDCHANNEL_IMPL_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
/* GridChannel interface header */
#include "vSwUpdM_GridChannel_If.h"

/* Implementation header of containing MultipleUnit */
#include "vSwUpdM_Grid_Impl.h"
#include "vSwUpdM_GridSrvc_Impl.h"
#include "vSwUpdM_GridNode_Impl.h"

/* Other MultipleUnits used by GridChannel_Impl (Prefer smallest set required, i.e. prefer _Types over _If over _Impl) */
#include "vSwUpdM_DevError_Impl.h"

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
#define VSWUPDM_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

extern VAR(vSwUpdM_GridChannel_VarChannelType, VSWUPDM_APPL_DATA)    vSwUpdM_GridChannel_VarChannel[VSWUPDM_GRIDCHANNEL_CHANNELIDX_COUNT];

#define VSWUPDM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/
# define VSWUPDM_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 * vSwUpdM_GridChannel_Prepare
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_GridChannel_Prepare(
  vSwUpdM_GridChannel_ChannelIdxType ChannelIndex,
  vSwUpdM_GridSrvc_ServiceIdxType ServiceIndex,
  vSwUpdM_NodeGroupIterType Destination)
{
  vSwUpdM_DevError_Assert((vSwUpdM_GridChannel_GetState(ChannelIndex) == VSWUPDM_GRIDCHANNEL_STATE_IDLE), VSWUPDM_DEVERROR_ASSERT_4);  /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */

  /* #10 Clear results. */
  vSwUpdM_GridChannel_ClearAggregatedResult(ChannelIndex);
  vSwUpdM_GridNode_SetServiceStateByGroup(ServiceIndex, Destination, VSWUPDM_GRIDCHANNEL_SERVICESTATE_INITIAL);
  vSwUpdM_GridNode_ClearResultByGroup(ServiceIndex, Destination);

  /* #20 Set Service Properties. */
  vSwUpdM_GridChannel_SetService(ChannelIndex, ServiceIndex);
  vSwUpdM_GridChannel_SetDestination(ChannelIndex, Destination);
  vSwUpdM_GridChannel_SetState(ChannelIndex, VSWUPDM_GRIDCHANNEL_STATE_RX_WAITRESPONSE);

  /* PRQA S 6010, 6030, 6050, 6080 1 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */
} /* vSwUpdM_GridChannel_Prepare */

/**********************************************************************************************************************
 * vSwUpdM_GridChannel_GetState
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(vSwUpdM_GridChannel_StateType, VSWUPDM_CODE) vSwUpdM_GridChannel_GetState( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_GridChannel_ChannelIdxType ChannelIndex
)
{
  return vSwUpdM_GridChannel_VarChannel[ChannelIndex].State;
} /* vSwUpdM_GridChannel_GetState */

/**********************************************************************************************************************
 * vSwUpdM_GridChannel_SetState
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_GridChannel_SetState( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_GridChannel_ChannelIdxType ChannelIndex,
  vSwUpdM_GridChannel_StateType State
)
{
  vSwUpdM_GridChannel_VarChannel[ChannelIndex].State = State;
} /* vSwUpdM_GridChannel_SetState */

/**********************************************************************************************************************
 * vSwUpdM_GridChannel_GetDestination
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(vSwUpdM_NodeGroupIterType, VSWUPDM_CODE) vSwUpdM_GridChannel_GetDestination( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_GridChannel_ChannelIdxType ChannelIndex
)
{
  return vSwUpdM_GridChannel_VarChannel[ChannelIndex].Destination;
} /* vSwUpdM_GridChannel_GetDestination */

/**********************************************************************************************************************
 * vSwUpdM_GridChannel_SetDestination
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_GridChannel_SetDestination( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_GridChannel_ChannelIdxType ChannelIndex,
  vSwUpdM_NodeGroupIterType Destination
)
{
  vSwUpdM_GridChannel_VarChannel[ChannelIndex].Destination = Destination;
} /* vSwUpdM_GridChannel_SetDestination */

/**********************************************************************************************************************
 * vSwUpdM_GridChannel_GetService
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(vSwUpdM_GridSrvc_ServiceIdxType, VSWUPDM_CODE) vSwUpdM_GridChannel_GetService( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_GridChannel_ChannelIdxType ChannelIndex
)
{
  return vSwUpdM_GridChannel_VarChannel[ChannelIndex].Service;
} /* vSwUpdM_GridChannel_GetService */

/**********************************************************************************************************************
 * vSwUpdM_GridChannel_SetService
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_GridChannel_SetService( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_GridChannel_ChannelIdxType ChannelIndex,
  vSwUpdM_GridSrvc_ServiceIdxType Service
)
{
  vSwUpdM_GridChannel_VarChannel[ChannelIndex].Service = Service;
} /* vSwUpdM_GridChannel_SetService */

/**********************************************************************************************************************
 * vSwUpdM_GridChannel_GetAggregatedResultPtr
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(vSwUpdM_GridSrvc_ResponseClassBasePtrType, VSWUPDM_CODE) vSwUpdM_GridChannel_GetAggregatedResultPtr( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_GridChannel_ChannelIdxType ChannelIndex
)
{
  return vSwUpdM_GridSrvc_GetResponseClassAggregationBuffer(vSwUpdM_GridChannel_GetService(ChannelIndex));
} /* vSwUpdM_GridChannel_GetAggregatedResultPtr */

/**********************************************************************************************************************
 * vSwUpdM_GridChannel_SetAggregatedResult
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_GridChannel_SetAggregatedResult( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_GridChannel_ChannelIdxType ChannelIndex,
  Std_ReturnType Value
)
{
  vSwUpdM_GridSrvc_ResponseClassSimpleResponsePtrType simpleResponse;
  simpleResponse = (vSwUpdM_GridSrvc_ResponseClassSimpleResponsePtrType)vSwUpdM_GridChannel_GetAggregatedResultPtr(ChannelIndex); /* PRQA S 0310 */ /* MD_vSwUpdM_Rule11.3_0310_ServiceParameterCast */

  simpleResponse->Result = Value;
} /* vSwUpdM_GridChannel_SetAggregatedResult */

/**********************************************************************************************************************
 * vSwUpdM_GridChannel_SetAggregatedResultToErrorCondition
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */

VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_GridChannel_SetAggregatedResultToErrorCondition( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_GridChannel_ChannelIdxType ChannelIndex,
  Std_ReturnType Value
)
{
  ((vSwUpdM_GridSrvc_ResponseClassSimpleResponsePtrType)vSwUpdM_GridChannel_GetAggregatedResultPtr(ChannelIndex))->Result = Value; /* PRQA S 0310 */ /* MD_vSwUpdM_Rule11.3_0310_ServiceParameterCast */
} /* vSwUpdM_GridChannel_SetAggregatedResultToErrorCondition */

/**********************************************************************************************************************
 * vSwUpdM_GridChannel_InitAggregatedResult
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_GridChannel_InitAggregatedResult( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_GridChannel_ChannelIdxType ChannelIndex
)
{
  switch (vSwUpdM_GridSrvc_GetResponseClassIndexOfService(vSwUpdM_GridChannel_GetService(ChannelIndex)))
  {
    default:
    /* case VSWUPDM_GRIDSRVC_RESPONSECLASS_MAIN: */
    {
      vSwUpdM_GridSrvc_InitResponseClassMain(E_OK, (vSwUpdM_GridSrvc_ResponseClassMainPtrType) vSwUpdM_GridChannel_GetAggregatedResultPtr(ChannelIndex)); /* PRQA S 0310 */ /* MD_vSwUpdM_Rule11.3_0310_ServiceParameterCast */
      break;
    }
    case VSWUPDM_GRIDSRVC_RESPONSECLASS_MAINTENANCE:
    {
      vSwUpdM_GridSrvc_InitResponseClassMaintenance(E_OK, (vSwUpdM_GridSrvc_ResponseClassMaintenancePtrType) vSwUpdM_GridChannel_GetAggregatedResultPtr(ChannelIndex)); /* PRQA S 0310 */ /* MD_vSwUpdM_Rule11.3_0310_ServiceParameterCast */
      break;
    }
    case VSWUPDM_GRIDSRVC_RESPONSECLASS_SUSPEND:
    {
      vSwUpdM_GridSrvc_InitResponseClassSuspend(E_OK, (vSwUpdM_GridSrvc_ResponseClassSuspendPtrType) vSwUpdM_GridChannel_GetAggregatedResultPtr(ChannelIndex)); /* PRQA S 0310 */ /* MD_vSwUpdM_Rule11.3_0310_ServiceParameterCast */
      break;
    }
    case VSWUPDM_GRIDSRVC_RESPONSECLASS_BK:
    {
      vSwUpdM_GridSrvc_InitResponseClassBookkeeper(E_OK, (vSwUpdM_GridSrvc_ResponseClassSuspendPtrType) vSwUpdM_GridChannel_GetAggregatedResultPtr(ChannelIndex)); /* PRQA S 0310 */ /* MD_vSwUpdM_Rule11.3_0310_ServiceParameterCast */
      break;
    }
  }
} /* vSwUpdM_GridChannel_InitAggregatedResult */

/**********************************************************************************************************************
 * vSwUpdM_GridChannel_GetAggregatedResultDirty
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(boolean, VSWUPDM_CODE) vSwUpdM_GridChannel_GetAggregatedResultDirty( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_GridChannel_ChannelIdxType ChannelIndex
)
{
  return vSwUpdM_GridChannel_VarChannel[ChannelIndex].AggregatedResultDirty;
} /* vSwUpdM_GridChannel_GetAggregatedResultDirty */

/**********************************************************************************************************************
 * vSwUpdM_GridChannel_SetAggregatedResultDirty
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_GridChannel_SetAggregatedResultDirty( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_GridChannel_ChannelIdxType ChannelIndex,
  boolean Value
)
{
  vSwUpdM_GridChannel_VarChannel[ChannelIndex].AggregatedResultDirty = Value;
} /* vSwUpdM_GridChannel_SetAggregatedResultDirty */

/**********************************************************************************************************************
 * vSwUpdM_GridChannel_GetResponseCount
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(uint8, VSWUPDM_CODE) vSwUpdM_GridChannel_GetResponseCount( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_GridChannel_ChannelIdxType ChannelIndex
)
{
  return vSwUpdM_GridChannel_VarChannel[ChannelIndex].ResponseCount;
} /* vSwUpdM_GridChannel_GetResponseCount */

/**********************************************************************************************************************
 * vSwUpdM_GridChannel_SetResponseCount
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_GridChannel_SetResponseCount( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_GridChannel_ChannelIdxType ChannelIndex,
  uint8 ResponseCount
)
{
  vSwUpdM_GridChannel_VarChannel[ChannelIndex].ResponseCount = ResponseCount;
} /* vSwUpdM_GridChannel_SetResponseCount */

/**********************************************************************************************************************
 * vSwUpdM_GridChannel_IncResponseCount
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_GridChannel_IncResponseCount( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_GridChannel_ChannelIdxType ChannelIndex
)
{
  vSwUpdM_GridChannel_VarChannel[ChannelIndex].ResponseCount++;
} /* vSwUpdM_GridChannel_IncResponseCount */

/**********************************************************************************************************************
 * vSwUpdM_GridChannel_ClearAggregatedResult
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_GridChannel_ClearAggregatedResult( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_GridChannel_ChannelIdxType ChannelIndex
)
{
  vSwUpdM_GridChannel_SetResponseCount(ChannelIndex, 0u);
  vSwUpdM_GridChannel_InitAggregatedResult(ChannelIndex);
} /* vSwUpdM_GridChannel_ClearAggregatedResult */

/**********************************************************************************************************************
 * vSwUpdM_GridChannel_StoreResponseResult
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_GridChannel_StoreResponseResult(
  vSwUpdM_GridChannel_ChannelIdxType ChannelIndex,
  vSwUpdM_NodeIterType NodeIndex,
  vSwUpdM_GridSrvc_ServiceIdxType ServiceIdx,
  uint8 ServiceResult)
{
  /* #10 Store result.
   *     And set AggregatedResultDirty flag. */
  vSwUpdM_GridNode_SetResult(ServiceIdx, NodeIndex, ServiceResult);
  vSwUpdM_GridNode_SetResultValid(ServiceIdx, NodeIndex, TRUE);

  VSWUPDM_ENTER_CRITICAL_SECTION();
  vSwUpdM_GridChannel_SetAggregatedResultDirty(ChannelIndex, TRUE);
  VSWUPDM_LEAVE_CRITICAL_SECTION();
} /* vSwUpdM_GridChannel_StoreResponseResult */

/**********************************************************************************************************************
 * vSwUpdM_GridChannel_StoreResponseServiceState
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_GridChannel_StoreResponseServiceState( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_GridChannel_ChannelIdxType ChannelIndex,
  vSwUpdM_NodeIterType NodeIndex,
  vSwUpdM_GridSrvc_ServiceIdxType ServiceIdx,
  vSwUpdM_GridChannel_ServiceStateType ServiceState)
{
  /* #10 Store ServiceState.
   *     And set AggregatedResultDirty flag. */
  vSwUpdM_GridNode_SetServiceState(ServiceIdx, NodeIndex, ServiceState);

  VSWUPDM_ENTER_CRITICAL_SECTION();
  vSwUpdM_GridChannel_SetAggregatedResultDirty(ChannelIndex, TRUE);
  VSWUPDM_LEAVE_CRITICAL_SECTION();

} /* vSwUpdM_GridChannel_StoreResponseServiceState */

/**********************************************************************************************************************
 * vSwUpdM_GridChannel_LegacyIsIncrementOnLocalNodeRequired
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(boolean, VSWUPDM_CODE) vSwUpdM_GridChannel_LegacyIsIncrementOnLocalNodeRequired(
  vSwUpdM_GridSrvc_ServiceIdxType ServiceIdx )
{
  boolean retVal;

  switch (ServiceIdx)
  {
    case VSWUPDM_GRIDSRVC_SERVICEIDX_BK_SET_GENERIC_PARAMETER:
    case VSWUPDM_GRIDSRVC_SERVICEIDX_BK_SET_SEGMENT_ATTRIBUTES:
    case VSWUPDM_GRIDSRVC_SERVICEIDX_BK_SET_RESUME_INFO:
    case VSWUPDM_GRIDSRVC_SERVICEIDX_BK_GET_GENERIC_PARAMETER:
    case VSWUPDM_GRIDSRVC_SERVICEIDX_BK_GET_SEGMENT_ATTRIBUTES:
    case VSWUPDM_GRIDSRVC_SERVICEIDX_BK_GET_RESUME_INFO:
    case VSWUPDM_GRIDSRVC_SERVICEIDX_BK_EXEC_COMMAND:
    {
      retVal = FALSE;
      break;
    }
    default:
    {
      retVal = TRUE;
      break;
    }
  }

  return retVal;

} /* vSwUpdM_GridChannel_LegacyIsIncrementOnLocalNodeRequired */

/**********************************************************************************************************************
 * vSwUpdM_GridChannel_GetRequestBuffer
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_GridChannel_GetRequestBuffer( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_GridChannel_ChannelIdxType ChannelIndex,
  vSwUpdM_GridSrvc_ServiceClassBasePtrPtrType Parameter
)
{
  (*Parameter) = vSwUpdM_GridChannel_RequestBuffer[ChannelIndex];
} /* vSwUpdM_GridChannel_SetResponseCount */

# define VSWUPDM_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* VSWUPDM_GRIDCHANNEL_IMPL_H */

/**********************************************************************************************************************
 *  END OF FILE: vSwUpdM_GridChannel_Impl.h
 *********************************************************************************************************************/
