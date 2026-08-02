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
/*!        \file  vSwUpdM_GridRpc_If.h
 *        \brief  vSwUpdM_GridRpc unit interface header file
 *      \details  Interface provided by the vSwUpdM_GridRpc unit.
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

#if !defined (VSWUPDM_GRIDRPC_IF_H)
# define VSWUPDM_GRIDRPC_IF_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
/* GridRpc types header */
#include "vSwUpdM_GridRpc_Types.h"

/* Interface header of containing MultipleUnit */
#include "vSwUpdM_Grid_If.h"

/* Other MultipleUnits used by GridRpc_If (Prefer smallest set required, i.e. prefer _Types over _If) */

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

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
# define VSWUPDM_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 * vSwUpdM_GridRpc_GetRpcProxyRequestOfService
 *********************************************************************************************************************/
/*! \brief       Get RpcProxyRequest for GridService.
 *  \details     -
 *  \param[in]   ServiceIndex
 *  \return      RpcProxyRequest
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     GridSrvc
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(vSwUpdM_RpcProxyServiceIdType, VSWUPDM_CODE) vSwUpdM_GridRpc_GetRpcProxyRequestOfService(
  vSwUpdM_GridSrvc_ServiceIdxType ServiceIndex);

/**********************************************************************************************************************
 * vSwUpdM_GridRpc_GetRpcProxyServiceExecutionState
 *********************************************************************************************************************/
/*! \brief       Translate vSwUpdM data type to vRpcProxy values.
 *  \details     -
 *  \param[in]   ServiceExecutionState
 *  \return      VRPCPROXY_SERVICE_PENDING      or
 *  \return      VRPCPROXY_SERVICE_FINISHED
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     GridSrvc
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(uint8, VSWUPDM_CODE) vSwUpdM_GridRpc_GetRpcProxyServiceExecutionState(
  vSwUpdM_GridRpc_ServiceExecutionStateType ServiceExecutionState);

/**********************************************************************************************************************
 *  vSwUpdM_GridRpc_GetRpcProxyTargetGroup
 *********************************************************************************************************************/
/*! \brief       Returns the RpcTargetGroup for a given Channel.
 *  \details     -
 *  \param[in]   ChannelIndex
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     GridChannel
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(vRpcProxy_TargetGroupsIterType, VSWUPDM_CODE) vSwUpdM_GridRpc_GetRpcProxyTargetGroup( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_GridChannel_ChannelIdxType ChannelIndex,
  vSwUpdM_NodeGroupIterType Destination
);

# define VSWUPDM_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* VSWUPDM_GRIDRPC_IF_H */

/**********************************************************************************************************************
 *  END OF FILE: vSwUpdM_GridRpc_If.h
 *********************************************************************************************************************/
