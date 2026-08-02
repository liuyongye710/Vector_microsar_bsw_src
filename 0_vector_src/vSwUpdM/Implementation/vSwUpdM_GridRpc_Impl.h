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
/*!        \file  vSwUpdM_GridRpc_Impl.h
 *        \brief  vSwUpdM_GridRpc implementation header file
 *      \details  vSwUpdM_GridRpc subcomponent public inline implementations.
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

#if !defined (VSWUPDM_GRIDRPC_IMPL_H)
# define VSWUPDM_GRIDRPC_IMPL_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
/* GridRpc interface header */
#include "vSwUpdM_GridRpc_If.h"

/* Implementation header of containing MultipleUnit */
#include "vSwUpdM_Grid_Impl.h"

/* Other MultipleUnits used by GridRpc_Impl (Prefer smallest set required, i.e. prefer _Types over _If over _Impl) */
#include "vRpcProxy_vSwUpdM.h"
#include "vRpcProxy_Service.h"

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
#define VSWUPDM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#if (VSWUPDM_MULTICONTROLLER_SUPPORT == STD_ON)
 /*!
 * Internal comment removed.
 *
 *
 */
extern CONST(vSwUpdM_RpcProxyServiceIdType, VSWUPDM_CONST) vSwUpdM_GridRpc_ProxyService[VSWUPDM_GRIDSRVC_SERVICEIDX_COUNT];
#endif
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
 * vSwUpdM_GridRpc_GetRpcProxyRequestOfService
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */

VSWUPDM_LOCAL_INLINE FUNC(vSwUpdM_RpcProxyServiceIdType, VSWUPDM_CODE) vSwUpdM_GridRpc_GetRpcProxyRequestOfService(
  vSwUpdM_GridSrvc_ServiceIdxType ServiceIndex)
{
  vSwUpdM_DevError_Assert((uint32)ServiceIndex < VSWUPDM_ARRAY_SIZE(vSwUpdM_GridRpc_ProxyService), VSWUPDM_DEVERROR_ASSERT_30); /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */

  return vSwUpdM_GridRpc_ProxyService[ServiceIndex];
} /* vSwUpdM_GridRpc_GetRpcProxyRequestOfService */

/**********************************************************************************************************************
 * vSwUpdM_GridRpc_GetRpcProxyServiceExecutionState
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */

VSWUPDM_LOCAL_INLINE FUNC(uint8, VSWUPDM_CODE) vSwUpdM_GridRpc_GetRpcProxyServiceExecutionState(
  vSwUpdM_GridRpc_ServiceExecutionStateType ServiceExecutionState)
{
  uint8 rpcProxyServiceExecutionState;

  if (ServiceExecutionState == VSWUPDM_GRIDRPC_SERVICEXECUTIONSTATE_PENDING)
  {
    rpcProxyServiceExecutionState = VRPCPROXY_SERVICE_PENDING;
  }
  else
  {
    rpcProxyServiceExecutionState = VRPCPROXY_SERVICE_FINISHED;
  }

  return rpcProxyServiceExecutionState;
} /* vSwUpdM_GridRpc_GetRpcProxyServiceExecutionState */

/**********************************************************************************************************************
 * vSwUpdM_GridRpc_GetRpcProxyTargetGroup
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(vRpcProxy_TargetGroupsIterType, VSWUPDM_CODE) vSwUpdM_GridRpc_GetRpcProxyTargetGroup( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_GridChannel_ChannelIdxType ChannelIndex,
  vSwUpdM_NodeGroupIterType Destination
)
{
  vRpcProxy_TargetGroupsIterType targetGroup;

  switch (ChannelIndex)
  {
    default:
    /* case  VSWUPDM_GRIDCHANNEL_CHANNELIDX_MAIN: */
    {
     targetGroup = vSwUpdM_GetDestinationMainOfNodeGroup(Destination);
     break;
    }
    case VSWUPDM_GRIDCHANNEL_CHANNELIDX_MAINTENANCE:
    {
     targetGroup = vSwUpdM_GetDestinationMaintenanceOfNodeGroup(Destination);
     break;
    }
    case VSWUPDM_GRIDCHANNEL_CHANNELIDX_SUSPEND:
    {
     targetGroup = vSwUpdM_GetDestinationSuspendOfNodeGroup(Destination);
     break;
    }
    case VSWUPDM_GRIDCHANNEL_CHANNELIDX_BOOKKEEPER:
    {
     targetGroup = vSwUpdM_GetDestinationBookkeeperOfNodeGroup(Destination);
     break;
    }
  }

  /* Hint: No Group configured: 0xFF = UNUSED */
  vSwUpdM_DevError_Assert(targetGroup != 0xFFu, VSWUPDM_DEVERROR_ASSERT_31); /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */

  return targetGroup;
} /* vSwUpdM_GridRpc_GetRpcProxyTargetGroup */

# define VSWUPDM_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* VSWUPDM_GRIDRPC_IMPL_H */

/**********************************************************************************************************************
 *  END OF FILE: vSwUpdM_GridRpc_Impl.h
 *********************************************************************************************************************/
