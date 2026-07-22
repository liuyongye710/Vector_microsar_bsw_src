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
/*!        \file  vSwUpdM_GridNode_If.h
 *        \brief  vSwUpdM_GridNode unit interface header file
 *      \details  Interface provided by the vSwUpdM_GridNode unit.
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

#if !defined (VSWUPDM_GRIDNODE_IF_H)
# define VSWUPDM_GRIDNODE_IF_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
/* GridNode types header */
#include "vSwUpdM_GridNode_Types.h"

/* Interface header of containing MultipleUnit */
#include "vSwUpdM_Grid_If.h"

/* Other MultipleUnits used by GridNode_If (Prefer smallest set required, i.e. prefer _Types over _If) */

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
 *  Global Inline Functions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  vSwUpdM_GridNode_GetNodeResponseClassBuffer
 *********************************************************************************************************************/
/*! \brief       Returns a pointer to the response buffer for a given node.
 *  \details     The configuration contains buffers for each ResponseClass and node. This allows that different
 *               independent responses can arrive in parallel. (Independent = in different Channels).
 *               Because the size of the individual ResponseClass types may vary, the defined type needs to take in
 *               account when selecting then n'th buffer for the array (for the n'th node).
 *               The BasePointer can be found by vSwUpdM_GridSrvc_GetResponseClassNodeBuffer(). The ResponseClass
 *               data structures contain an enum entry defining the instantiated type (and therefore the size of one
 *               array member).
 *  \param[in]   BasePointer Pointer to first response buffer for the desired ResponseClass type.
 *  \param[in]   NodeIndex
 *  \return      Pointer to the NodeIndex'th entry of the configured array of response buffers of desired type.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     GridNode
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(vSwUpdM_GridSrvc_ResponseClassBasePtrType, VSWUPDM_CODE) vSwUpdM_GridNode_GetNodeResponseClassBuffer( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_GridSrvc_ResponseClassBasePtrType BasePointer,
  vSwUpdM_NodeIterType NodeIndex
);

/**********************************************************************************************************************
 *  vSwUpdM_GridNode_GetResult
 *********************************************************************************************************************/
/*! \brief       Get result of a response from a node for a given service
 *  \details     -
 *  \param[in]   ServiceIndex   The service defines the type of the ResponseClass.
 *  \param[in]   NodeIndex      The requested node.
 *  \return      Result for given node.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     GridNode
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GridNode_GetResult( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_GridSrvc_ServiceIdxType ServiceIndex,
  vSwUpdM_NodeIterType NodeIndex
);

/**********************************************************************************************************************
 *  vSwUpdM_GridNode_SetResult
 *********************************************************************************************************************/
/*! \brief      Set result of a response from a node for a given service
 *  \details     -
 *  \param[in]   ServiceIndex  The service defines the type of the ResponseClass.
 *  \param[in]   NodeIndex     The requested node.
 *  \param[in]   Result        Pointer to ResponseClass structure, containing result for given node.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     GridNode
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_GridNode_SetResult( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_GridSrvc_ServiceIdxType ServiceIndex,
  vSwUpdM_NodeIterType NodeIndex,
  Std_ReturnType Result
);

/**********************************************************************************************************************
 *  vSwUpdM_GridNode_GetResultValid
 *********************************************************************************************************************/
/*! \brief       Get valid flag of result for a response from a node for a given service
 *  \details     -
 *  \param[in]   ServiceIndex  The service defines the type of the ResponseClass.
 *  \param[in]   NodeIndex     The requested node.
 *  \return      Validity of result for given node.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     GridNode
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(boolean, VSWUPDM_CODE) vSwUpdM_GridNode_GetResultValid( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_GridSrvc_ServiceIdxType ServiceIndex,
  vSwUpdM_NodeIterType NodeIndex
);

/**********************************************************************************************************************
 *  vSwUpdM_GridNode_SetResultValid
 *********************************************************************************************************************/
/*! \brief       Set valid flag of result for a response from a node for a given service
 *  \details     -
 *  \param[in]   ServiceIndex  The service defines the type of the ResponseClass.
 *  \param[in]   NodeIndex     The requested node.
 *  \param[in]   ResultValid   Value to set for result validity.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     GridNode
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_GridNode_SetResultValid( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_GridSrvc_ServiceIdxType ServiceIndex,
  vSwUpdM_NodeIterType NodeIndex,
  boolean ResultValid
);

/**********************************************************************************************************************
 *  vSwUpdM_GridNode_GetServiceState
 *********************************************************************************************************************/
/*! \brief       Returns the ServiceState for a given Service (indicates affected channel) and Node.
 *  \details     -
 *  \param[in]   ServiceIndex
 *  \param[in]   NodeIndex
 *  \return      Service state.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     GridNode
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(vSwUpdM_GridChannel_ServiceStateType, VSWUPDM_CODE) vSwUpdM_GridNode_GetServiceState( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_GridSrvc_ServiceIdxType ServiceIndex,
  vSwUpdM_NodeIterType NodeIndex
);

/**********************************************************************************************************************
 *  vSwUpdM_GridNode_SetState
 *********************************************************************************************************************/
/*! \brief       Set ServiceState for a given Service (indicates affected channel) and Node.
 *  \details     -
 *  \param[in]   ServiceIndex
 *  \param[in]   NodeIndex
 *  \param[in]   State         Value of ServiceState for given Node and Service to set.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     GridNode
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_GridNode_SetServiceState( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_GridSrvc_ServiceIdxType ServiceIndex,
  vSwUpdM_NodeIterType NodeIndex,
  vSwUpdM_GridChannel_ServiceStateType State
);

/**********************************************************************************************************************
 *  Global Functions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  vSwUpdM_GridNode_SetServiceStateByGroup
 *********************************************************************************************************************/
/*! \brief       Set ServiceState for all nodes in a Group in a given Service.
 *  \details     For each receiver of a Service, the ServiceState is tracked. The buffers used to store the
 *               ServiceStates have the size of the total number of nodes. But only the subset of the currently used
 *               nodes (those in Group) need to be set to process a service. Therefore only the ServiceStates of
 *               the nodes contained in the Group are set to the given State value.
 *  \param[in]   ServiceIndex
 *  \param[in]   Group
 *  \param[in]   State
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     GridNode
 *********************************************************************************************************************/
FUNC(void, VSWUPDM_CODE) vSwUpdM_GridNode_SetServiceStateByGroup(
  vSwUpdM_GridSrvc_ServiceIdxType ServiceIndex,
  vSwUpdM_NodeGroupIterType Group,
  vSwUpdM_GridChannel_ServiceStateType State);

/**********************************************************************************************************************
 *  vSwUpdM_GridNode_ClearResultByGroup
 *********************************************************************************************************************/
/*! \brief       Invalidate the results for all nodes in a Group in a given Service.
 *  \details     For each receiver of a Service, the Result is tracked. The buffers used to store the
 *               Results have the size of the total number of nodes. But only the subset of the currently used
 *               nodes (those in Group) need to be set to process a service. Therefore only the ServiceStates of
 *               the nodes contained in the Group are set invalid.
 *  \param[in]   ServiceIndex
 *  \param[in]   Group
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         Destination of Channel must be set to proper value!
 *  \ingroup     GridNode
 *********************************************************************************************************************/
FUNC(void, VSWUPDM_CODE) vSwUpdM_GridNode_ClearResultByGroup(
  vSwUpdM_GridSrvc_ServiceIdxType ServiceIndex,
  vSwUpdM_NodeGroupIterType Group
);

/**********************************************************************************************************************
 *  vSwUpdM_GridNode_GetNodeIndexFromRpcProxySource()
 *********************************************************************************************************************/
/*! \brief       Search for the node by RxSource.
 *  \details     -
 *  \param[in]   SourceHandleId RxSource to search for.
 *  \param[out]  NodeIndex      Index of found node.
 *  \return      E_NOT_OK       If no node found.
 *  \return      E_OK           otherwise.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     remote
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GridNode_GetNodeIndexFromRpcProxySource(
  vSwUpdM_RpcProxySourceIdType SourceHandleId,
  P2VAR(vSwUpdM_NodeIterType, AUTOMATIC, VSWUPDM_APPL_VAR) NodeIndex);

/**********************************************************************************************************************
 *  vSwUpdM_GridNode_GetNodeIndexFromRpcProxySourceAndChannel()
 *********************************************************************************************************************/
/*! \brief       Search for the node by RxSource and Channel.
 *  \details     -
 *  \param[in]   SourceHandleId RxSource to search for.
 *  \param[in]   ChannelIndex   Expected Channel.
 *  \param[out]  NodeIndex      Index of found node.
 *  \return      E_NOT_OK       If no node found.
 *  \return      E_OK           otherwise.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     remote
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GridNode_GetNodeIndexFromRpcProxySourceAndChannel(
  vSwUpdM_RpcProxySourceIdType SourceHandleId,
  vSwUpdM_GridChannel_ChannelIdxType ChannelIndex,
  P2VAR(vSwUpdM_NodeIterType, AUTOMATIC, VSWUPDM_APPL_VAR) NodeIndex);

/**********************************************************************************************************************
 *  vSwUpdM_GridNode_GetNodeIndexFromRpcProxyTargetAndChannel()
 *********************************************************************************************************************/
/*! \brief       Search for the node by TxTarget and Channel.
 *  \details     -
 *  \param[in]   TargetHandleId TxTarget to search for.
 *  \param[in]   ChannelIndex   Expected Channel.
 *  \param[out]  NodeIndex      Index of found node.
 *  \return      E_NOT_OK       If no node found.
 *  \return      E_OK           otherwise.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     remote
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GridNode_GetNodeIndexFromRpcProxyTargetAndChannel(
  vSwUpdM_RpcProxyTargetIdType TargetHandleId,
  vSwUpdM_GridChannel_ChannelIdxType ChannelIndex,
  P2VAR(vSwUpdM_NodeIterType, AUTOMATIC, VSWUPDM_APPL_VAR) NodeIndex);

# define VSWUPDM_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* VSWUPDM_GRIDNODE_IF_H */

/**********************************************************************************************************************
 *  END OF FILE: vSwUpdM_GridNode_If.h
 *********************************************************************************************************************/
