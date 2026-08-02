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
/*!        \file  vSwUpdM_Grid.c
 *        \brief  vSwUpdM_Grid source file
 *      \details  Implementation of the vSwUpdM_Grid subcomponent.
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

#define VSWUPDM_GRID_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
 /* Grid implementation header */
#include "vSwUpdM_Grid_Impl.h"

/* Implementation headers of all contained Units */
#include "vSwUpdM_GridChannel_Impl.h"
#include "vSwUpdM_GridNode_Impl.h"
#include "vSwUpdM_BkPersistClient_Impl.h"
#include "vSwUpdM_BkPersistServer_Impl.h"
#if (VSWUPDM_MULTICONTROLLER_SUPPORT == STD_ON)
# include "vSwUpdM_GridRpc_Impl.h"
#endif
#include "vSwUpdM_GridRpcStub_Impl.h"
#include "vSwUpdM_GridSrvc_Impl.h"

/* Other MultipleUnits used by Grid (Prefer smallest set required, i.e. prefer _Types over _If over _Impl) */
#include "vSwUpdM.h"
#include "vSwUpdM_DevError_Impl.h"

#include "vSwUpdM_Lcfg.h"

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/*********************
 * GRID CHANNEL
 ********************/

typedef union
{ /* PRQA S 0750 */  /* MD_CSL_Union */
  vSwUpdM_GridSrvc_ServiceClassBkSetSegmentAttributesType SetSegmentAttributesType;
  vSwUpdM_GridSrvc_ServiceClassBkSetResumeInfoType        SetResumeInfoType;
  vSwUpdM_GridSrvc_ServiceClassBkSetGenericParameterType  SetGenericParameterType;

  vSwUpdM_GridSrvc_ServiceClassBkGetSegmentAttributesType GetSegmentAttributesType;
  vSwUpdM_GridSrvc_ServiceClassBkGetResumeInfoType        GetResumeInfoType;
  vSwUpdM_GridSrvc_ServiceClassBkGetGenericParameterType  GetGenericParameterType;

  vSwUpdM_GridSrvc_ServiceClassBkExecCommandType          ExecCommandType;
}vSwUpdM_GridChannel_RequestBufferBookkeeperChannelType;

typedef union
{ /* PRQA S 0750 */  /* MD_CSL_Union */
  vSwUpdM_GridSrvc_ServiceClassMaintenanceType Maintencance;
}vSwUpdM_GridChannel_RequestBufferMaintenanceChannelType;

typedef union
{  /* PRQA S 0750 */  /* MD_CSL_Union */
  vSwUpdM_GridSrvc_ServiceClassSuspendType Suspend;
}vSwUpdM_GridChannel_RequestBufferSuspendChannelType;

typedef union
{ /* PRQA S 0750 */  /* MD_CSL_Union */
  vSwUpdM_GridSrvc_ServiceClassPartitionType      PartitionType;
  vSwUpdM_GridSrvc_ServiceClassGenericType        GenericType;
  vSwUpdM_GridSrvc_ServiceClassModuleType         ModuleType;
  vSwUpdM_GridSrvc_ServiceClassRegionType         RegionType;
  vSwUpdM_GridSrvc_ServiceClassSegmentType        SegmentType;
  vSwUpdM_GridSrvc_ServiceClassProcessModuleType  ProcessModuleType;
  vSwUpdM_GridSrvc_ServiceClassStreamInfoType     StreamInfoType;
  vSwUpdM_GridSrvc_ServiceClassSegmentInfoType    SegmentInfoType;
}vSwUpdM_GridChannel_RequestBufferMainChannelType;

/*********************
 * GRID RPC
 ********************/

typedef Std_ReturnType (* vSwUpdM_GridRpc_RequestServiceType) ( vSwUpdM_NodeGroupIterType Destination, vSwUpdM_GridSrvc_ServiceClassBasePtrType Parameter);
typedef Std_ReturnType (* vSwUpdM_GridRpc_ResponseServiceType) (vSwUpdM_NodeIterType Origin, vSwUpdM_GridRpc_ServiceExecutionStateType ServiceExecutionState, vSwUpdM_GridRpc_ComplexResponseClassBasePtrType ResponseClass);

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
#define VSWUPDM_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*********************
 * GRID CHANNEL
 ********************/

/**********************************************************************************************************************
 *  vSwUpdM_GridChannel_ConfirmationParameterCheck
 *********************************************************************************************************************/
/*! \brief       Evaluates incoming confirmation parameters.
 *  \details     -
 *  \param[in]   ChannelIndex   Index of grid channel.
 *  \param[in]   NodeIndex      Node index of source node.
 *  \param[in]   ServiceId      ID of service associated with this job.
 *  \return      E_OK     If parameters are valid.
 *  \return      E_NOT_OK Else.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     GridChannel
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GridChannel_ConfirmationParameterCheck(
  vSwUpdM_GridChannel_ChannelIdxType ChannelIndex,
  vSwUpdM_NodeIterType NodeIndex,
  vSwUpdM_GridSrvc_ServiceIdxType ServiceId);

/**********************************************************************************************************************
 *  vSwUpdM_GridChannel_ProcessConfirmation
 *********************************************************************************************************************/
/*! \brief       Handle generic confirmation processing.
 *  \details     -
 *  \param[in]   ChannelIndex   Index of grid channel.
 *  \param[in]   NodeIndex      Node index of source node.
 *  \param[in]   ResponseClass  Initialized response class structure.
 *  \return      E_OK     If confirmation could be evaluated.
 *  \return      E_NOT_OK Else.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     GridChannel
 *********************************************************************************************************************/
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GridChannel_ProcessConfirmation(
  vSwUpdM_GridChannel_ChannelIdxType ChannelIndex,
  vSwUpdM_NodeIterType NodeIndex,
  vSwUpdM_GridRpc_ComplexResponseClassBasePtrType ResponseClass);

/*********************
 * GRID NODE
 ********************/

/*********************
 * GRID RPC
 ********************/
#if (VSWUPDM_MULTICONTROLLER_SUPPORT == STD_ON)
/**********************************************************************************************************************
 * vSwUpdM_vSwUpdM_GridRpc_HandleConfirmation
 *********************************************************************************************************************/
/*! \brief       Helper function to handle confirmations.
 *  \details     Convert input data to vSwUpdM types and store confirmation.
 *  \param[in]   ChannelIdx     Channel for which response is received.
 *  \param[in]   ResponseClassIdx  Expected response class.
 *  \param[in]   SourceHandleId vRpcProx source
 *  \param[in]   ServiceId      Received ServiceId of request
 *  \param[in]   ServiceResult  Received result of request.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     GridRpc
 *********************************************************************************************************************/

VSWUPDM_LOCAL FUNC(void, VSWUPDM_CODE) vSwUpdM_GridRpc_HandleConfirmation(
  vSwUpdM_GridChannel_ChannelIdxType ChannelIdx,
  vSwUpdM_GridSrvc_ResponseClassIdxType ResponseClassIdx,
  vRpcProxy_SourcesIterType SourceHandleId,
  uint8 ServiceId,
  uint8 ServiceResult);
/**********************************************************************************************************************
 * vSwUpdM_GridRpc_RemoteCallCheckPreconditions
 *********************************************************************************************************************/
/*! \brief       Checks if a request by node SourceIndex is allowed.
 *  \details     -
 *  \param[in]   SourceIndex    Source node, node which sends the request.
 *  \return      Result
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     GridRpc
 *********************************************************************************************************************/
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GridRpc_RemoteCallCheckPreconditions(
  vSwUpdM_NodeIterType SourceIndex);

/**********************************************************************************************************************
 * vSwUpdM_GridRpc_RemotePrepareRequestProcessing
 *********************************************************************************************************************/
/*! \brief       Helper function to handle common tasks on reception of a (legacy) request from a child.
 *  \details     Get vSwUpdM node index by vRprProxy SourceHandleId and check if requester is allowed.
 *  \param[in]   SourceHandleId    RxSource to search for.
 *  \param[out]  SourceIndex       Index of found node.
 *  \return      E_OK     If request can be processed.
 *  \return      E_NOT_OK Else.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     GridRpc
 *********************************************************************************************************************/
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GridRpc_RemotePrepareRequestProcessing(
  vSwUpdM_RpcProxySourceIdType SourceHandleId,
  P2VAR(vSwUpdM_NodeIterType, AUTOMATIC, VSWUPDM_APPL_VAR) SourceIndex);

/**********************************************************************************************************************
 * vSwUpdM_GridRpc_GenericRequestPreconditionCheck
 *********************************************************************************************************************/
/*! \brief       Checks if vRpcProxy inputs are valid and vSwUpdM is in correct state.
 *  \details     Check vSwUpdM state and applies range checks on enum values.
 *  \param[in]   ServiceState    Value received from remote.
 *  \param[in]   Service         Value received from remote.
 *  \return      Result
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     GridRpc
 *********************************************************************************************************************/
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GridRpc_GenericRequestPreconditionCheck(
  uint8 ServiceState,
  uint8 Service);

/**********************************************************************************************************************
 * vSwUpdM_GridRpc_GetServiceIndexByService
 *********************************************************************************************************************/
/*! \brief       Evaluates received Service id and checks if it is part of the expected service class.
 *  \details     Returns valid ServiceIndex if applicable to service class, otherwise UNDEFINED value.
 *  \param[in]   Service      ServiceIdx of service to check.
 *  \param[in]   ServiceClass ServiceClass to check.
 *  \param[out]  ServiceIndex On success.
 *  \return      E_OK         On success.
 *  \return      E_NOT_OK     Otherwise.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     GridRpc
 *********************************************************************************************************************/
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GridRpc_GetServiceIndexByService(
  uint8 Service,
  SwUpdM_GridSrvc_ServiceClassType ServiceClass,
  vSwUpdM_GridSrvc_ServiceIdxPtrType ServiceIndex);

/**********************************************************************************************************************
 * vSwUpdM_GridRpc_GetServiceIndexByResponseService
 *********************************************************************************************************************/
/*! \brief       Evaluates received Service id and checks if it is part of the expected response class.
 *  \details     Returns valid ServiceIndex if applicable to resonse class, otherwise UNDEFINED value.
 *  \param[in]   Service       ServiceIdx of service to check.
 *  \param[in]   ResponseClass ResponseClass to check.
 *  \param[out]  ServiceIndex  On success.
 *  \return      E_OK          On success.
 *  \return      E_NOT_OK      Otherwise.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     GridRpc
 *********************************************************************************************************************/
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GridRpc_GetServiceIndexByResponseService(
  uint8 Service,
  vSwUpdM_GridSrvc_ResponseClassIdxType ResponseClass,
  vSwUpdM_GridSrvc_ServiceIdxPtrType ServiceIndex);

/**********************************************************************************************************************
 * vSwUpdM_GridRpc_GetResponseTarget
 *********************************************************************************************************************/
/*! \brief       Selects the Target to transmit a response for a given origin of a request.
 *  \details     -
 *  \param[in]   RequestOrigin Origin of Request.
 *  \param[in]   ServiceIndex  Service of Request.
 *  \return      Target for response.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     GridRpc
 *********************************************************************************************************************/
VSWUPDM_LOCAL FUNC(vRpcProxy_CTargetsIterType, VSWUPDM_CODE) vSwUpdM_GridRpc_GetResponseTarget(
  vSwUpdM_NodeIterType RequestOrigin,
  vSwUpdM_GridSrvc_ServiceIdxType ServiceIndex);

/**********************************************************************************************************************
 *  vSwUpdM_GridRpc_GetServiceByRpcProxyRequestService
 *********************************************************************************************************************/
/*! \brief       Translate a vRpcProxy service Id into a vSwUpdM_GridSrv_ServiceIdx Id.
 *  \details     -
 *  \param[in]   RpcProxyRequestService   Remote service ID.
 *  \param[out]  ServiceIdx               Local service ID.
 *  \return      E_OK if successful.
 *  \return      else failed.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     GridRpc
 *********************************************************************************************************************/
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GridRpc_GetServiceByRpcProxyRequestService(
  vSwUpdM_RpcProxyServiceIdType RpcProxyRequestService,
  P2VAR(vSwUpdM_GridSrvc_ServiceIdxType, AUTOMATIC, VSWUPDM_APPL_VAR) ServiceIdx);

/**********************************************************************************************************************
 *  vSwUpdM_GridRpc_GetServiceStateFromRpcProxyError
 *********************************************************************************************************************/
/*! \brief       Translate a vRpcProxy error code into a ServiceState.
 *  \details     -
 *  \param[in]   Result         Error code, which shall be translated.
 *  \return      ServiceState   Resulting service state.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     GridRpc
 *********************************************************************************************************************/
VSWUPDM_LOCAL FUNC(vSwUpdM_GridChannel_ServiceStateType, VSWUPDM_CODE) vSwUpdM_GridRpc_GetServiceStateFromRpcProxyError(
  TxService_StatusType Result);

/**********************************************************************************************************************
 *  vSwUpdM_GridRpc_GetServiceStateFromRpcProxyError
 *********************************************************************************************************************/
/*! \brief       Translate a vRpcProxy error code into a vSwUpdM error code (legacy).
 *  \details     -
 *  \param[in]   Result         Error code, which shall be translated.
 *  \return      errorCode      Resulting vSwUpdM error code.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     GridRpc
 *********************************************************************************************************************/
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GridRpc_GetLegacyErrorCodeFromRpcProxyError(
  TxService_StatusType Result);

/**********************************************************************************************************************
 *  vSwUpdM_GridRpc_LegacyServiceErrorHandling
 *********************************************************************************************************************/
/*! \brief       Handle an error reported for a legacy RPC
 *  \details     -
 *  \param[in]   TargetId       TxTarget ID.
 *  \param[in]   ServiceIndex   Service index of given service.
 *  \param[in]   Result         Error input.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     GridRpc
 *********************************************************************************************************************/
VSWUPDM_LOCAL FUNC(void, VSWUPDM_CODE) vSwUpdM_GridRpc_LegacyServiceErrorHandling(
  uint8 TargetId,
  vSwUpdM_GridSrvc_ServiceIdxType ServiceIndex,
  TxService_StatusType Result);

/*******************************
 * vRpcProxy Redirect Functions
 ******************************/

/**********************************************************************************************************************
 * vSwUpdM_GridRpc_ProxyMaintenanceService
 *********************************************************************************************************************/
/*! \brief       Helper function to call vRpcProxy callout
 *  \details     -
 *  \param[in]   Destination Target for RPC
 *  \param[in]   Parameter   Parameters for RPC
 *  \return      Result of RPC request
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     GridRpc
 *********************************************************************************************************************/
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GridRpc_ProxyMaintenanceService(
  vSwUpdM_NodeGroupIterType Destination,
  vSwUpdM_GridSrvc_ServiceClassBasePtrType Parameter);

/**********************************************************************************************************************
 * vSwUpdM_GridRpc_ProxySuspendService
 *********************************************************************************************************************/
/*! \brief       Helper function to call vRpcProxy callout
 *  \details     -
 *  \param[in]   Destination Target for RPC
 *  \param[in]   Parameter   Parameters for RPC
 *  \return      Result of RPC request
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     GridRpc
 *********************************************************************************************************************/
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GridRpc_ProxySuspendService(
  vSwUpdM_NodeGroupIterType Destination,
  vSwUpdM_GridSrvc_ServiceClassBasePtrType Parameter);

/**********************************************************************************************************************
 * vSwUpdM_GridRpc_ProxyGenericService
 *********************************************************************************************************************/
/*! \brief       Helper function to call vRpcProxy callout
 *  \details     -
 *  \param[in]   Destination Target for RPC
 *  \param[in]   Parameter   Parameters for RPC
 *  \return      Result of RPC request
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     GridRpc
 *********************************************************************************************************************/
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GridRpc_ProxyGenericService(
  vSwUpdM_NodeGroupIterType Destination,
  vSwUpdM_GridSrvc_ServiceClassBasePtrType Parameter);

/**********************************************************************************************************************
 * vSwUpdM_GridRpc_ProxyPartitionService
 *********************************************************************************************************************/
/*! \brief       Helper function to call vRpcProxy callout
 *  \details     -
 *  \param[in]   Destination Target for RPC
 *  \param[in]   Parameter   Parameters for RPC
 *  \return      Result of RPC request
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     GridRpc
 *********************************************************************************************************************/
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GridRpc_ProxyPartitionService(
  vSwUpdM_NodeGroupIterType Destination,
  vSwUpdM_GridSrvc_ServiceClassBasePtrType Parameter);

/**********************************************************************************************************************
 * vSwUpdM_GridRpc_ProxyModuleService
 *********************************************************************************************************************/
/*! \brief       Helper function to call vRpcProxy callout
 *  \details     -
 *  \param[in]   Destination Target for RPC
 *  \param[in]   Parameter   Parameters for RPC
 *  \return      Result of RPC request
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     GridRpc
 *********************************************************************************************************************/
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GridRpc_ProxyModuleService(
  vSwUpdM_NodeGroupIterType Destination,
  vSwUpdM_GridSrvc_ServiceClassBasePtrType Parameter);

/**********************************************************************************************************************
 * vSwUpdM_GridRpc_ProxyRegionService
 *********************************************************************************************************************/
/*! \brief       Helper function to call vRpcProxy callout
 *  \details     -
 *  \param[in]   Destination Target for RPC
 *  \param[in]   Parameter   Parameters for RPC
 *  \return      Result of RPC request
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     GridRpc
 *********************************************************************************************************************/
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GridRpc_ProxyRegionService(
  vSwUpdM_NodeGroupIterType Destination,
  vSwUpdM_GridSrvc_ServiceClassBasePtrType Parameter);

/**********************************************************************************************************************
 * vSwUpdM_GridRpc_ProxyRegionService
 *********************************************************************************************************************/
/*! \brief       Helper function to call vRpcProxy callout
 *  \details     -
 *  \param[in]   Destination Target for RPC
 *  \param[in]   Parameter   Parameters for RPC
 *  \return      Result of RPC request
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     GridRpc
 *********************************************************************************************************************/
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GridRpc_ProxyRegionService(
  vSwUpdM_NodeGroupIterType Destination,
  vSwUpdM_GridSrvc_ServiceClassBasePtrType Parameter);

/**********************************************************************************************************************
 * vSwUpdM_GridRpc_ProxySegmentService
 *********************************************************************************************************************/
/*! \brief       Helper function to call vRpcProxy callout
 *  \details     -
 *  \param[in]   Destination Target for RPC
 *  \param[in]   Parameter   Parameters for RPC
 *  \return      Result of RPC request
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     GridRpc
 *********************************************************************************************************************/
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GridRpc_ProxySegmentService(
  vSwUpdM_NodeGroupIterType Destination,
  vSwUpdM_GridSrvc_ServiceClassBasePtrType Parameter);

/**********************************************************************************************************************
 * vSwUpdM_GridRpc_ProxyProcessModuleService
 *********************************************************************************************************************/
/*! \brief       Helper function to call vRpcProxy callout
 *  \details     -
 *  \param[in]   Destination Target for RPC
 *  \param[in]   Parameter   Parameters for RPC
 *  \return      Result of RPC request
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     GridRpc
 *********************************************************************************************************************/
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GridRpc_ProxyProcessModuleService(
  vSwUpdM_NodeGroupIterType Destination,
  vSwUpdM_GridSrvc_ServiceClassBasePtrType Parameter);

/**********************************************************************************************************************
 * vSwUpdM_GridRpc_ProxyAddSegmentService
 *********************************************************************************************************************/
/*! \brief       Helper function to call vRpcProxy callout
 *  \details     -
 *  \param[in]   Destination Target for RPC
 *  \param[in]   Parameter   Parameters for RPC
 *  \return      Result of RPC request
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     GridRpc
 *********************************************************************************************************************/
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GridRpc_ProxyAddSegmentService(
  vSwUpdM_NodeGroupIterType Destination,
  vSwUpdM_GridSrvc_ServiceClassBasePtrType Parameter);

/**********************************************************************************************************************
 * vSwUpdM_GridRpc_ProxyStartStreamService
 *********************************************************************************************************************/
/*! \brief       Helper function to call vRpcProxy callout
 *  \details     -
 *  \param[in]   Destination Target for RPC
 *  \param[in]   Parameter   Parameters for RPC
 *  \return      Result of RPC request
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     GridRpc
 *********************************************************************************************************************/
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GridRpc_ProxyStartStreamService(
  vSwUpdM_NodeGroupIterType Destination,
  vSwUpdM_GridSrvc_ServiceClassBasePtrType Parameter);

/**********************************************************************************************************************
 * vSwUpdM_GridRpc_ProxyBkExecCommandService
 *********************************************************************************************************************/
/*! \brief       Helper function to call vRpcProxy callout
 *  \details     -
 *  \param[in]   Destination Target for RPC
 *  \param[in]   Parameter   Parameters for RPC
 *  \return      Result of RPC request
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     GridRpc
 *********************************************************************************************************************/
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GridRpc_ProxyBkExecCommandService(
  vSwUpdM_NodeGroupIterType Destination,
  vSwUpdM_GridSrvc_ServiceClassBasePtrType Parameter);

/**********************************************************************************************************************
 * vSwUpdM_GridRpc_ProxyBkGetGenericParameterService
 *********************************************************************************************************************/
/*! \brief       Helper function to call vRpcProxy callout
 *  \details     -
 *  \param[in]   Destination Target for RPC
 *  \param[in]   Parameter   Parameters for RPC
 *  \return      Result of RPC request
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     GridRpc
 *********************************************************************************************************************/
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GridRpc_ProxyBkGetGenericParameterService(
  vSwUpdM_NodeGroupIterType Destination,
  vSwUpdM_GridSrvc_ServiceClassBasePtrType Parameter);

/**********************************************************************************************************************
 * vSwUpdM_GridRpc_ProxyBkGetSegmentAttributesService
 *********************************************************************************************************************/
/*! \brief       Helper function to call vRpcProxy callout
 *  \details     -
 *  \param[in]   Destination Target for RPC
 *  \param[in]   Parameter   Parameters for RPC
 *  \return      Result of RPC request
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     GridRpc
 *********************************************************************************************************************/
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GridRpc_ProxyBkGetSegmentAttributesService(
  vSwUpdM_NodeGroupIterType Destination,
  vSwUpdM_GridSrvc_ServiceClassBasePtrType Parameter);

/**********************************************************************************************************************
 * vSwUpdM_GridRpc_ProxyBkGetResumeInfoService
 *********************************************************************************************************************/
/*! \brief       Helper function to call vRpcProxy callout
 *  \details     -
 *  \param[in]   Destination Target for RPC
 *  \param[in]   Parameter   Parameters for RPC
 *  \return      Result of RPC request
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     GridRpc
 *********************************************************************************************************************/
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GridRpc_ProxyBkGetResumeInfoService(
  vSwUpdM_NodeGroupIterType Destination,
  vSwUpdM_GridSrvc_ServiceClassBasePtrType Parameter);

/**********************************************************************************************************************
 * vSwUpdM_GridRpc_ProxyBkSetGenericParameterService
 *********************************************************************************************************************/
/*! \brief       Helper function to call vRpcProxy callout
 *  \details     -
 *  \param[in]   Destination Target for RPC
 *  \param[in]   Parameter   Parameters for RPC
 *  \return      Result of RPC request
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     GridRpc
 *********************************************************************************************************************/
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GridRpc_ProxyBkSetGenericParameterService(
  vSwUpdM_NodeGroupIterType Destination,
  vSwUpdM_GridSrvc_ServiceClassBasePtrType Parameter);

/**********************************************************************************************************************
 * vSwUpdM_GridRpc_ProxyBkSetSegmentAttributesService
 *********************************************************************************************************************/
/*! \brief       Helper function to call vRpcProxy callout
 *  \details     -
 *  \param[in]   Destination Target for RPC
 *  \param[in]   Parameter   Parameters for RPC
 *  \return      Result of RPC request
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     GridRpc
 *********************************************************************************************************************/
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GridRpc_ProxyBkSetSegmentAttributesService(
  vSwUpdM_NodeGroupIterType Destination,
  vSwUpdM_GridSrvc_ServiceClassBasePtrType Parameter);

/**********************************************************************************************************************
 * vSwUpdM_GridRpc_ProxyBkSetResumeInfoService
 *********************************************************************************************************************/
/*! \brief       Helper function to call vRpcProxy callout
 *  \details     -
 *  \param[in]   Destination Target for RPC
 *  \param[in]   Parameter   Parameters for RPC
 *  \return      Result of RPC request
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     GridRpc
 *********************************************************************************************************************/
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GridRpc_ProxyBkSetResumeInfoService(
  vSwUpdM_NodeGroupIterType Destination,
  vSwUpdM_GridSrvc_ServiceClassBasePtrType Parameter);

/**********************************************************************************************************************
 * vSwUpdM_GridRpc_ProxyMainConfirmation
 *********************************************************************************************************************/
/*! \brief       Helper function to call vRpcProxy callout
 *  \details     -
 *  \param[in]   RequestOrigin Source of initial RPC request.
 *  \param[in]   ServiceIndex  Initial RPC request
 *  \param[in]   ResponseClass Parameters for RPC Response
 *  \return      Result of transmission.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     GridRpc
 *********************************************************************************************************************/
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GridRpc_ProxyMainConfirmation(
  vSwUpdM_NodeIterType RequestOrigin,
    vSwUpdM_GridRpc_ServiceExecutionStateType ServiceExecutionState,
  vSwUpdM_GridRpc_ComplexResponseClassBasePtrType ResponseClass);

/**********************************************************************************************************************
 * vSwUpdM_GridRpc_ProxyMaintenanceConfirmation
 *********************************************************************************************************************/
/*! \brief       Helper function to call vRpcProxy callout
 *  \details     -
 *  \param[in]   RequestOrigin Source of initial RPC request.
 *  \param[in]   ServiceIndex  Initial RPC request
 *  \param[in]   ResponseClass Parameters for RPC Response
 *  \return      Result of transmission.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     GridRpc
 *********************************************************************************************************************/
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GridRpc_ProxyMaintenanceConfirmation(
  vSwUpdM_NodeIterType RequestOrigin,
  vSwUpdM_GridRpc_ServiceExecutionStateType ServiceExecutionState,
  vSwUpdM_GridRpc_ComplexResponseClassBasePtrType ResponseClass);

/**********************************************************************************************************************
 * vSwUpdM_GridRpc_ProxySuspendConfirmation
 *********************************************************************************************************************/
/*! \brief       Helper function to call vRpcProxy callout
 *  \details     -
 *  \param[in]   RequestOrigin Source of initial RPC request.
 *  \param[in]   ServiceIndex  Initial RPC request
 *  \param[in]   ResponseClass Parameters for RPC Response
 *  \return      Result of transmission.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     GridRpc
 *********************************************************************************************************************/
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GridRpc_ProxySuspendConfirmation(
  vSwUpdM_NodeIterType RequestOrigin,
  vSwUpdM_GridRpc_ServiceExecutionStateType ServiceExecutionState,
  vSwUpdM_GridRpc_ComplexResponseClassBasePtrType ResponseClass);

/**********************************************************************************************************************
 * vSwUpdM_GridRpc_ProxyBookkeeperConfirmation
 *********************************************************************************************************************/
/*! \brief       Helper function to call vRpcProxy callout
 *  \details     -
 *  \param[in]   RequestOrigin Source of initial RPC request.
 *  \param[in]   ServiceIndex  Initial RPC request
 *  \param[in]   ResponseClass Parameters for RPC Response
 *  \return      Result of transmission.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     GridRpc
 *********************************************************************************************************************/
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GridRpc_ProxyBookkeeperConfirmation(
  vSwUpdM_NodeIterType RequestOrigin,
  vSwUpdM_GridRpc_ServiceExecutionStateType ServiceExecutionState,
  vSwUpdM_GridRpc_ComplexResponseClassBasePtrType ResponseClass);

/**********************************************************************************************************************
 * vSwUpdM_GridRpc_ProxyBkGetGenericParameterResponse
 *********************************************************************************************************************/
/*! \brief       Helper function to call vRpcProxy callout
 *  \details     -
 *  \param[in]   RequestOrigin Source of initial RPC request.
 *  \param[in]   ServiceIndex  Initial RPC request
 *  \param[in]   ResponseClass Parameters for RPC Response
 *  \return      Result of transmission.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     GridRpc
 *********************************************************************************************************************/
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GridRpc_ProxyBkGetGenericParameterResponse(
  vSwUpdM_NodeIterType RequestOrigin,
  vSwUpdM_GridRpc_ServiceExecutionStateType ServiceExecutionState,
  vSwUpdM_GridRpc_ComplexResponseClassBasePtrType ResponseClass);

/**********************************************************************************************************************
 * vSwUpdM_GridRpc_ProxyBkGetSegmentAttributesResponse
 *********************************************************************************************************************/
/*! \brief       Helper function to call vRpcProxy callout
 *  \details     -
 *  \param[in]   RequestOrigin Source of initial RPC request.
 *  \param[in]   ServiceIndex  Initial RPC request
 *  \param[in]   ResponseClass Parameters for RPC Response
 *  \return      Result of transmission.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     GridRpc
 *********************************************************************************************************************/
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GridRpc_ProxyBkGetSegmentAttributesResponse(
  vSwUpdM_NodeIterType RequestOrigin,
  vSwUpdM_GridRpc_ServiceExecutionStateType ServiceExecutionState,
  vSwUpdM_GridRpc_ComplexResponseClassBasePtrType ResponseClass);

/**********************************************************************************************************************
 * vSwUpdM_GridRpc_ProxyBkGetSegmentAttributesResponse
 *********************************************************************************************************************/
/*! \brief       Helper function to call vRpcProxy callout
 *  \details     -
 *  \param[in]   RequestOrigin Source of initial RPC request.
 *  \param[in]   ServiceIndex  Initial RPC request
 *  \param[in]   ResponseClass Parameters for RPC Response
 *  \return      Result of transmission.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     GridRpc
 *********************************************************************************************************************/
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GridRpc_ProxyBkGetResumeInfoResponse(
  vSwUpdM_NodeIterType RequestOrigin,
  vSwUpdM_GridRpc_ServiceExecutionStateType ServiceExecutionState,
  vSwUpdM_GridRpc_ComplexResponseClassBasePtrType ResponseClass);

/**********************************************************************************************************************
 * vSwUpdM_GridRpc_ProxyLegacyResponse
 *********************************************************************************************************************/
/*! \brief       Helper function to call vRpcProxy callout
 *  \details     -
 *  \param[in]   RequestOrigin Source of initial RPC request.
 *  \param[in]   ServiceIndex  Initial RPC request
 *  \param[in]   ResponseClass Parameters for RPC Response
 *  \return      Result of transmission.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     GridRpc
 *********************************************************************************************************************/
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GridRpc_ProxyLegacyResponse(
  vSwUpdM_NodeIterType RequestOrigin,
  vSwUpdM_GridRpc_ServiceExecutionStateType ServiceExecutionState,
  vSwUpdM_GridRpc_ComplexResponseClassBasePtrType ResponseClass);
#endif

/*******************************
 * Local Redirect Functions
 ******************************/

/**********************************************************************************************************************
 * vSwUpdM_GridRpc_LocalBkExecCommandService
 *********************************************************************************************************************/
/*! \brief       Helper function to call local redirect.
 *  \details     -
 *  \param[in]   Destination Target for RPC
 *  \param[in]   Parameter   Parameters for RPC
 *  \return      Result of RPC request
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     GridRpc
 *********************************************************************************************************************/
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GridRpc_LocalBkExecCommandService(
  vSwUpdM_NodeGroupIterType Destination,
  vSwUpdM_GridSrvc_ServiceClassBasePtrType Parameter);

/**********************************************************************************************************************
 * vSwUpdM_GridRpc_LocalBkGetGenericParameterService
 *********************************************************************************************************************/
/*! \brief       Helper function to call local redirect.
 *  \details     -
 *  \param[in]   Destination Target for RPC
 *  \param[in]   Parameter   Parameters for RPC
 *  \return      Result of RPC request
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     GridRpc
 *********************************************************************************************************************/
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GridRpc_LocalBkGetGenericParameterService(
  vSwUpdM_NodeGroupIterType Destination,
  vSwUpdM_GridSrvc_ServiceClassBasePtrType Parameter);

/**********************************************************************************************************************
 * vSwUpdM_GridRpc_LocalBkGetSegmentAttributesService
 *********************************************************************************************************************/
/*! \brief       Helper function to call local redirect.
 *  \details     -
 *  \param[in]   Destination Target for RPC
 *  \param[in]   Parameter   Parameters for RPC
 *  \return      Result of RPC request
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     GridRpc
 *********************************************************************************************************************/
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GridRpc_LocalBkGetSegmentAttributesService(
  vSwUpdM_NodeGroupIterType Destination,
  vSwUpdM_GridSrvc_ServiceClassBasePtrType Parameter);

/**********************************************************************************************************************
 * vSwUpdM_GridRpc_LocalBkGetResumeInfoService
 *********************************************************************************************************************/
/*! \brief       Helper function to call local redirect.
 *  \details     -
 *  \param[in]   Destination Target for RPC
 *  \param[in]   Parameter   Parameters for RPC
 *  \return      Result of RPC request
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     GridRpc
 *********************************************************************************************************************/
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GridRpc_LocalBkGetResumeInfoService(
  vSwUpdM_NodeGroupIterType Destination,
  vSwUpdM_GridSrvc_ServiceClassBasePtrType Parameter);

/**********************************************************************************************************************
 * vSwUpdM_GridRpc_LocalBkSetGenericParameterService
 *********************************************************************************************************************/
/*! \brief       Helper function to call local redirect.
 *  \details     -
 *  \param[in]   Destination Target for RPC
 *  \param[in]   Parameter   Parameters for RPC
 *  \return      Result of RPC request
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     GridRpc
 *********************************************************************************************************************/
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GridRpc_LocalBkSetGenericParameterService(
  vSwUpdM_NodeGroupIterType Destination,
  vSwUpdM_GridSrvc_ServiceClassBasePtrType Parameter);

/**********************************************************************************************************************
 * vSwUpdM_GridRpc_LocalBkSetSegmentAttributesService
 *********************************************************************************************************************/
/*! \brief       Helper function to call local redirect.
 *  \details     -
 *  \param[in]   Destination Target for RPC
 *  \param[in]   Parameter   Parameters for RPC
 *  \return      Result of RPC request
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     GridRpc
 *********************************************************************************************************************/
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GridRpc_LocalBkSetSegmentAttributesService(
  vSwUpdM_NodeGroupIterType Destination,
  vSwUpdM_GridSrvc_ServiceClassBasePtrType Parameter);

/**********************************************************************************************************************
 * vSwUpdM_GridRpc_LocalBkSetResumeInfoService
 *********************************************************************************************************************/
/*! \brief       Helper function to call local redirect.
 *  \details     -
 *  \param[in]   Destination Target for RPC
 *  \param[in]   Parameter   Parameters for RPC
 *  \return      Result of RPC request
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     GridRpc
 *********************************************************************************************************************/
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GridRpc_LocalBkSetResumeInfoService(
  vSwUpdM_NodeGroupIterType Destination,
  vSwUpdM_GridSrvc_ServiceClassBasePtrType Parameter);

/**********************************************************************************************************************
 * vSwUpdM_GridRpc_LocalBookkeeperConfirmation
 *********************************************************************************************************************/
/*! \brief       Helper function to call local redirect.
 *  \details     -
 *  \param[in]   RequestOrigin Source of initial RPC request.
 *  \param[in]   ServiceIndex  Initial RPC request
 *  \param[in]   ResponseClass Parameters for RPC Response
 *  \return      Result of transmission.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     GridRpc
 *********************************************************************************************************************/
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GridRpc_LocalBookkeeperConfirmation(
  vSwUpdM_NodeIterType RequestOrigin,
  vSwUpdM_GridRpc_ServiceExecutionStateType ServiceExecutionState,
  vSwUpdM_GridRpc_ComplexResponseClassBasePtrType ResponseClass);

/**********************************************************************************************************************
 * vSwUpdM_GridRpc_LocalBkGetGenericParameterResponse
 *********************************************************************************************************************/
/*! \brief       Helper function to call local redirect.
 *  \details     -
 *  \param[in]   RequestOrigin Source of initial RPC request.
 *  \param[in]   ServiceIndex  Initial RPC request
 *  \param[in]   ResponseClass Parameters for RPC Response
 *  \return      Result of transmission.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     GridRpc
 *********************************************************************************************************************/
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GridRpc_LocalBkGetGenericParameterResponse(
  vSwUpdM_NodeIterType RequestOrigin,
  vSwUpdM_GridRpc_ServiceExecutionStateType ServiceExecutionState,
  vSwUpdM_GridRpc_ComplexResponseClassBasePtrType ResponseClass);

/**********************************************************************************************************************
 * vSwUpdM_GridRpc_LocalBkGetSegmentAttributesResponse
 *********************************************************************************************************************/
/*! \brief       Helper function to call local redirect.
 *  \details     -
 *  \param[in]   RequestOrigin Source of initial RPC request.
 *  \param[in]   ServiceIndex  Initial RPC request
 *  \param[in]   ResponseClass Parameters for RPC Response
 *  \return      Result of transmission.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     GridRpc
 *********************************************************************************************************************/
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GridRpc_LocalBkGetSegmentAttributesResponse(
  vSwUpdM_NodeIterType RequestOrigin,
  vSwUpdM_GridRpc_ServiceExecutionStateType ServiceExecutionState,
  vSwUpdM_GridRpc_ComplexResponseClassBasePtrType ResponseClass);

/**********************************************************************************************************************
 * vSwUpdM_GridRpc_LocalBkGetResumeInfoResponse
 *********************************************************************************************************************/
/*! \brief       Helper function to call local redirect.
 *  \details     -
 *  \param[in]   RequestOrigin Source of initial RPC request.
 *  \param[in]   ServiceIndex  Initial RPC request
 *  \param[in]   ResponseClass Parameters for RPC Response
 *  \return      Result of transmission.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     GridRpc
 *********************************************************************************************************************/
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GridRpc_LocalBkGetResumeInfoResponse(
  vSwUpdM_NodeIterType RequestOrigin,
  vSwUpdM_GridRpc_ServiceExecutionStateType ServiceExecutionState,
  vSwUpdM_GridRpc_ComplexResponseClassBasePtrType ResponseClass);

/*********************
 * GRID SERVICE
 ********************/

/**********************************************************************************************************************
 * vSwUpdM_GridSrvc_ApplyLockResponses
 *********************************************************************************************************************/
/*! \brief       Evaluates the single responses for a Lock/Unlock request and sets the lock state flags for each node.
 *  \details     -
 *  \param[in]   Destination
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     GridSrvc
 *********************************************************************************************************************/
VSWUPDM_LOCAL FUNC(void, VSWUPDM_CODE) vSwUpdM_GridSrvc_ApplyLockResponses(
vSwUpdM_NodeGroupIterType Destination);

/**********************************************************************************************************************
 * vSwUpdM_GridSrvc_HandleCommunicationState
 *********************************************************************************************************************/
/*! \brief       Polls the Grid for responses for Lock/Unlock requests. Triggers cleanup if required.
 *  \details     If a Lock request fails because some nodes refuse to lock, the others which are already locked need
 *               To be unlocked again (= cleanup).
 *  \param[in]   Destination
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     GridSrvc
 *********************************************************************************************************************/
VSWUPDM_LOCAL FUNC(void, VSWUPDM_CODE) vSwUpdM_GridSrvc_HandleCommunicationState(
  vSwUpdM_NodeGroupIterType Destination);

/*********************
 * GRID STREAM
 ********************/

/*********************
 * LEGACY
 ********************/

/**********************************************************************************************************************
 * vSwUpdM_RemoteProcessResponse
 *********************************************************************************************************************/
/*! \brief  Set flag to indicate response reception and store result from response.
 *  \details There are three different flags for responses:
 *            - Suspend/Resume
 *            - Shutdown
 *            - other
 *           because it these three classes of requests are asynchronous to each other. Depending on the ServiceId,
 *           the appropriate flag is selected.
 *  \param[in]   NodeIndex     Transmitting node of the response.
 *  \param[in]   ServiceId     Service that is responded.
 *  \param[in]   Result        Responded result of the remote service.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     remote
 *********************************************************************************************************************/
VSWUPDM_LOCAL FUNC(void, VSWUPDM_CODE) vSwUpdM_RemoteProcessResponse(
  vSwUpdM_NodeIterType NodeIndex,
  vSwUpdM_GridSrvc_ServiceIdxType ServiceId,
  Std_ReturnType Result);

/**********************************************************************************************************************
 *  vSwUpdM_RemoteStreamPrepareTx()
 *********************************************************************************************************************/
/*! \brief       Set up a RemoteStream for transmission.
 *  \details     Takes a pointer to a buffer of data to be transmitted.
 *  \param[in]   Handle          Handle of a RemoteStream.
 *  \param[in]   Buffer          Pointer to a buffer for Rx.
 *  \param[in]   AvailableLength Length of data in Buffer
 *  \param[in]   Target          Target for transmission.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     remote
 *********************************************************************************************************************/
VSWUPDM_LOCAL FUNC(void, VSWUPDM_CODE) vSwUpdM_RemoteStreamPrepareTx(
  vSwUpdM_RemoteStreamHandleType Handle,
  P2VAR(uint8, AUTOMATIC, VSWUPDM_APPL_VAR) Buffer,
  vSwUpdM_RemoteStreamSizeType AvailableLength,
  vSwUpdM_NodeIterType Target);

/**********************************************************************************************************************
 vSwUpdM_RemoteStreamAbort
**********************************************************************************************************************/
/*! \brief       Aborts the current active remote stream in case of an error.
 *  \details     -
 *  \param[in]   ServiceId      ID of the remote service which triggers an error.
 *  \context     ISR
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     remote
**********************************************************************************************************************/
VSWUPDM_LOCAL FUNC(void, VSWUPDM_CODE) vSwUpdM_RemoteStreamAbort(vSwUpdM_GridSrvc_ServiceIdxType ServiceId);

#define VSWUPDM_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/
#define VSWUPDM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*********************
 * GRID CHANNEL
 ********************/
/* PRQA S 0759, 3218 5 */ /* MD_CSL_Union, MD_vSwUpdM_Rule8.9_3218_FileScope */
VSWUPDM_LOCAL VAR(vSwUpdM_GridChannel_RequestBufferMainChannelType, VSWUPDM_APPL_DATA)        vSwUpdM_GridChannel_RequestBufferMainChannel;            /* PRQA S 3218 */ /* MD_vSwUpdM_Rule8.9_3218_FileScope */
VSWUPDM_LOCAL VAR(vSwUpdM_GridChannel_RequestBufferMaintenanceChannelType, VSWUPDM_APPL_DATA) vSwUpdM_GridChannel_RequestBufferMaintenanceChannel;     /* PRQA S 3218 */ /* MD_vSwUpdM_Rule8.9_3218_FileScope */
VSWUPDM_LOCAL VAR(vSwUpdM_GridChannel_RequestBufferSuspendChannelType, VSWUPDM_APPL_DATA)     vSwUpdM_GridChannel_RequestBufferSuspendChannel;         /* PRQA S 3218 */ /* MD_vSwUpdM_Rule8.9_3218_FileScope */
VSWUPDM_LOCAL VAR(vSwUpdM_GridChannel_RequestBufferBookkeeperChannelType, VSWUPDM_APPL_DATA)  vSwUpdM_GridChannel_RequestBufferBookkeeperChannel;      /* PRQA S 3218 */ /* MD_vSwUpdM_Rule8.9_3218_FileScope */
/*********************
 * GRID SRVC
 ********************/

VSWUPDM_LOCAL VAR(vSwUpdM_GridSrvc_GridStateType, VSWUPDM_APPL_DATA) vSwUpdM_GridSrvc_GridState;      /* PRQA S 3218 */ /* MD_vSwUpdM_Rule8.9_3218_FileScope */

#define VSWUPDM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
#define VSWUPDM_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

VAR(vSwUpdM_GridSrvc_ResponseClassMainType, VSWUPDM_APPL_DATA)              vSwUpdM_GridSrvc_ResponseMain_Aggregated;
VAR(vSwUpdM_GridSrvc_ResponseClassSuspendType, VSWUPDM_APPL_DATA)           vSwUpdM_GridSrvc_ResponseSuspend_Aggregated;
VAR(vSwUpdM_GridSrvc_ResponseClassMaintenanceType, VSWUPDM_APPL_DATA)       vSwUpdM_GridSrvc_ResponseMaintenance_Aggregated;
VAR(vSwUpdM_GridSrvc_ResponseClassBookkeeperType, VSWUPDM_APPL_DATA)        vSwUpdM_GridSrvc_ResponseBookkeeper_Aggregated;

#define VSWUPDM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define VSWUPDM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

CONST(vSwUpdM_GridSrvc_ServiceType, VSWUPDM_CONST) vSwUpdM_GridSrvc_Service[] =
{
  /* ServiceClass                           ResponseClass */
  /* Maintenance Channel */
  { VSWUPDM_GRIDSRVC_CLASS_MAINTENANCE,     VSWUPDM_GRIDSRVC_RESPONSECLASS_MAINTENANCE },       /* VSWUPDM_GRIDSRVC_SERVICEIDX_LOCK */
  { VSWUPDM_GRIDSRVC_CLASS_MAINTENANCE,     VSWUPDM_GRIDSRVC_RESPONSECLASS_MAINTENANCE },       /* VSWUPDM_GRIDSRVC_SERVICEIDX_SHUTDOWN */
  { VSWUPDM_GRIDSRVC_CLASS_MAINTENANCE,     VSWUPDM_GRIDSRVC_RESPONSECLASS_MAINTENANCE },       /* VSWUPDM_GRIDSRVC_SERVICEIDX_UNLOCK */
  /*  Suspend Channel */
  { VSWUPDM_GRIDSRVC_CLASS_SUSPEND,         VSWUPDM_GRIDSRVC_RESPONSECLASS_SUSPEND     },       /* VSWUPDM_GRIDSRVC_SERVICEIDX_SUSPEND */
  { VSWUPDM_GRIDSRVC_CLASS_SUSPEND,         VSWUPDM_GRIDSRVC_RESPONSECLASS_SUSPEND     },       /* VSWUPDM_GRIDSRVC_SERVICEIDX_RESUME */

  /*  Main Channel */
  { VSWUPDM_GRIDSRVC_CLASS_GENERIC,         VSWUPDM_GRIDSRVC_RESPONSECLASS_MAIN        },       /* VSWUPDM_GRIDSRVC_SERVICEIDX_START */

  { VSWUPDM_GRIDSRVC_CLASS_GENERIC,         VSWUPDM_GRIDSRVC_RESPONSECLASS_MAIN        },       /* VSWUPDM_GRIDSRVC_SERVICEIDX_END_STREAM */

  { VSWUPDM_GRIDSRVC_CLASS_PARTITION,       VSWUPDM_GRIDSRVC_RESPONSECLASS_MAIN        },       /* VSWUPDM_GRIDSRVC_SERVICEIDX_OPEN_PARTITION */

  { VSWUPDM_GRIDSRVC_CLASS_GENERIC,         VSWUPDM_GRIDSRVC_RESPONSECLASS_MAIN        },       /* VSWUPDM_GRIDSRVC_SERVICEIDX_CHECK_PARTITION */
  { VSWUPDM_GRIDSRVC_CLASS_GENERIC,         VSWUPDM_GRIDSRVC_RESPONSECLASS_MAIN        },       /* VSWUPDM_GRIDSRVC_SERVICEIDX_SET_PARTITION_VALID */
  { VSWUPDM_GRIDSRVC_CLASS_GENERIC,         VSWUPDM_GRIDSRVC_RESPONSECLASS_MAIN        },       /* VSWUPDM_GRIDSRVC_SERVICEIDX_SET_PARTITION_INVALID */
  { VSWUPDM_GRIDSRVC_CLASS_GENERIC,         VSWUPDM_GRIDSRVC_RESPONSECLASS_MAIN        },       /* VSWUPDM_GRIDSRVC_SERVICEIDX_SYNC_PARTITION */
  { VSWUPDM_GRIDSRVC_CLASS_GENERIC,         VSWUPDM_GRIDSRVC_RESPONSECLASS_MAIN        },       /* VSWUPDM_GRIDSRVC_SERVICEIDX_SWAP_PARTITION */

  { VSWUPDM_GRIDSRVC_CLASS_MODULE,          VSWUPDM_GRIDSRVC_RESPONSECLASS_MAIN        },       /* VSWUPDM_GRIDSRVC_SERVICEIDX_OPEN_MODULE */
  { VSWUPDM_GRIDSRVC_CLASS_MODULE,          VSWUPDM_GRIDSRVC_RESPONSECLASS_MAIN        },       /* VSWUPDM_GRIDSRVC_SERVICEIDX_CLOSE_MODULE */
  { VSWUPDM_GRIDSRVC_CLASS_MODULE,          VSWUPDM_GRIDSRVC_RESPONSECLASS_MAIN        },       /* VSWUPDM_GRIDSRVC_SERVICEIDX_ERASE_MODULE */
  { VSWUPDM_GRIDSRVC_CLASS_MODULE,          VSWUPDM_GRIDSRVC_RESPONSECLASS_MAIN        },       /* VSWUPDM_GRIDSRVC_SERVICEIDX_FINALIZE_MODULE */
  { VSWUPDM_GRIDSRVC_CLASS_MODULE,          VSWUPDM_GRIDSRVC_RESPONSECLASS_MAIN        },       /* VSWUPDM_GRIDSRVC_SERVICEIDX_SYNC_MODULE */
  { VSWUPDM_GRIDSRVC_CLASS_MODULE,          VSWUPDM_GRIDSRVC_RESPONSECLASS_MAIN        },       /* VSWUPDM_GRIDSRVC_SERVICEIDX_VALIDATE_MODULE */
  { VSWUPDM_GRIDSRVC_CLASS_MODULE,          VSWUPDM_GRIDSRVC_RESPONSECLASS_MAIN        },       /* VSWUPDM_GRIDSRVC_SERVICEIDX_INVALIDATE_MODULE */
  { VSWUPDM_GRIDSRVC_CLASS_MODULE,          VSWUPDM_GRIDSRVC_RESPONSECLASS_MAIN        },       /* VSWUPDM_GRIDSRVC_SERVICEIDX_CLEAR_SEGMENTS_OF_MODULE */
  { VSWUPDM_GRIDSRVC_CLASS_MODULE,          VSWUPDM_GRIDSRVC_RESPONSECLASS_MAIN        },       /* VSWUPDM_GRIDSRVC_SERVICEIDX_INDICATE_WRITE_TO_MODULE */

  { VSWUPDM_GRIDSRVC_CLASS_REGION,          VSWUPDM_GRIDSRVC_RESPONSECLASS_MAIN        },       /* VSWUPDM_GRIDSRVC_SERVICEIDX_ERASE_REGION */

  { VSWUPDM_GRIDSRVC_CLASS_SEGMENT,         VSWUPDM_GRIDSRVC_RESPONSECLASS_MAIN        },       /* VSWUPDM_GRIDSRVC_SERVICEIDX_OPEN_SEGMENT */
  { VSWUPDM_GRIDSRVC_CLASS_SEGMENT,         VSWUPDM_GRIDSRVC_RESPONSECLASS_MAIN        },       /* VSWUPDM_GRIDSRVC_SERVICEIDX_CLOSE_SEGMENT */
  { VSWUPDM_GRIDSRVC_CLASS_SEGMENT,         VSWUPDM_GRIDSRVC_RESPONSECLASS_MAIN        },       /* VSWUPDM_GRIDSRVC_SERVICEIDX_FINALIZE_SEGMENT */

  { VSWUPDM_GRIDSRVC_CLASS_PROCESS_MODULE,  VSWUPDM_GRIDSRVC_RESPONSECLASS_MAIN        },       /* VSWUPDM_GRIDSRVC_SERVICEIDX_VERIFY_MODULE */
  { VSWUPDM_GRIDSRVC_CLASS_PROCESS_MODULE,  VSWUPDM_GRIDSRVC_RESPONSECLASS_MAIN        },       /* VSWUPDM_GRIDSRVC_SERVICEIDX_PROCESS_MODULE */

  { VSWUPDM_GRIDSRVC_CLASS_STREAM_INFO,     VSWUPDM_GRIDSRVC_RESPONSECLASS_MAIN        },       /* VSWUPDM_GRIDSRVC_SERVICEIDX_START_STREAM */
  { VSWUPDM_GRIDSRVC_CLASS_SEGMENT_INFO,    VSWUPDM_GRIDSRVC_RESPONSECLASS_MAIN        },       /* VSWUPDM_GRIDSRVC_SERVICEIDX_ADD_SEGMENT */

  { VSWUPDM_GRIDSRVC_CLASS_SEGMENT,         VSWUPDM_GRIDSRVC_RESPONSECLASS_MAIN        },       /* VSWUPDM_GRIDSRVC_SERVICEIDX_VERIFY_SEGMENT */

  /* Bookkeeper */
  { VSWUPDM_GRIDSRVC_CLASS_BK_SET_GENERIC,            VSWUPDM_GRIDSRVC_RESPONSECLASS_BK      }, /* VSWUPDM_GRIDSRVC_SERVICEIDX_BK_SET_GENERIC */
  { VSWUPDM_GRIDSRVC_CLASS_BK_SET_SEGMENT_ATTRIBUTES, VSWUPDM_GRIDSRVC_RESPONSECLASS_BK      }, /* VSWUPDM_GRIDSRVC_SERVICEIDX_BK_SET_SEGMENT_ATTRIBUTES */
  { VSWUPDM_GRIDSRVC_CLASS_BK_SET_RESUME_INFO,        VSWUPDM_GRIDSRVC_RESPONSECLASS_BK      }, /* VSWUPDM_GRIDSRVC_SERVICEIDX_BK_SET_RESUME_INFO */
  { VSWUPDM_GRIDSRVC_CLASS_BK_GET_GENERIC,            VSWUPDM_GRIDSRVC_RESPONSECLASS_BK_GET  }, /* VSWUPDM_GRIDSRVC_SERVICEIDX_BK_GET_GENERIC */
  { VSWUPDM_GRIDSRVC_CLASS_BK_GET_SEGMENT_ATTRIBUTES, VSWUPDM_GRIDSRVC_RESPONSECLASS_BK_GET_SEGMENT_ATTRIBUTES  }, /* VSWUPDM_GRIDSRVC_SERVICEIDX_BK_GET_SEGMENT_ATTRIBUTES */
  { VSWUPDM_GRIDSRVC_CLASS_BK_GET_RESUME_INFO,        VSWUPDM_GRIDSRVC_RESPONSECLASS_BK_GET_RESUME_INFO  }, /* VSWUPDM_GRIDSRVC_SERVICEIDX_BK_GET_RESUME_INFO */
  { VSWUPDM_GRIDSRVC_CLASS_BK_EXEC_COMMAND,           VSWUPDM_GRIDSRVC_RESPONSECLASS_BK      }, /* VSWUPDM_GRIDSRVC_SERVICEIDX_BK_EXEC_COMMAND */

  /*  Legacy Services */
  { VSWUPDM_GRIDSRVC_CLASS_NONE,            VSWUPDM_GRIDSRVC_RESPONSECLASS_LEGACY      },       /* SWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_CONCLUDE_SEGMENT */
  { VSWUPDM_GRIDSRVC_CLASS_NONE,            VSWUPDM_GRIDSRVC_RESPONSECLASS_LEGACY      },       /* VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_COPY_STREAM_DATA */
  { VSWUPDM_GRIDSRVC_CLASS_NONE,            VSWUPDM_GRIDSRVC_RESPONSECLASS_LEGACY      },       /* VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_REQUEST_PROCESS_INFO */
  { VSWUPDM_GRIDSRVC_CLASS_NONE,            VSWUPDM_GRIDSRVC_RESPONSECLASS_LEGACY      },       /* VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_PROCESS_STREAM_DATA */
  { VSWUPDM_GRIDSRVC_CLASS_NONE,            VSWUPDM_GRIDSRVC_RESPONSECLASS_LEGACY      },       /* VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_RESPONSE_COPY_STREAM_DATA */
  { VSWUPDM_GRIDSRVC_CLASS_NONE,            VSWUPDM_GRIDSRVC_RESPONSECLASS_LEGACY      },       /* VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_PERSIST_MODULE_STATE */
  { VSWUPDM_GRIDSRVC_CLASS_NONE,            VSWUPDM_GRIDSRVC_RESPONSECLASS_LEGACY      },       /* VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_PERSIST_MODULE_VALID */
  { VSWUPDM_GRIDSRVC_CLASS_NONE,            VSWUPDM_GRIDSRVC_RESPONSECLASS_LEGACY      },       /* VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_PERSIST_MODULE_PROGRAMMING_ATTEMPTS */
  { VSWUPDM_GRIDSRVC_CLASS_NONE,            VSWUPDM_GRIDSRVC_RESPONSECLASS_LEGACY      },       /* VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_PERSIST_REGION_STATE */
  { VSWUPDM_GRIDSRVC_CLASS_NONE,            VSWUPDM_GRIDSRVC_RESPONSECLASS_LEGACY      },       /* VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_PERSIST_REGION_PROGRAMMING_ATTEMPTS */
  { VSWUPDM_GRIDSRVC_CLASS_NONE,            VSWUPDM_GRIDSRVC_RESPONSECLASS_LEGACY      },       /* VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_PERSIST_SEGMENT_ATTRIBUTES */
  { VSWUPDM_GRIDSRVC_CLASS_NONE,            VSWUPDM_GRIDSRVC_RESPONSECLASS_LEGACY      },       /* VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_PERSIST_RESUME_INFO */
  { VSWUPDM_GRIDSRVC_CLASS_NONE,            VSWUPDM_GRIDSRVC_RESPONSECLASS_NONE        },       /* VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_CONFIRMATION */
  { VSWUPDM_GRIDSRVC_CLASS_NONE,            VSWUPDM_GRIDSRVC_RESPONSECLASS_NONE        },       /* VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_STREAM_COPY */
  { VSWUPDM_GRIDSRVC_CLASS_NONE,            VSWUPDM_GRIDSRVC_RESPONSECLASS_NONE        },       /* VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_STREAM_END */
  { VSWUPDM_GRIDSRVC_CLASS_NONE,            VSWUPDM_GRIDSRVC_RESPONSECLASS_NONE        },       /* VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_STREAM_REQUEST */
  { VSWUPDM_GRIDSRVC_CLASS_NONE,            VSWUPDM_GRIDSRVC_RESPONSECLASS_NONE        }        /* VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_STREAM_START */
};

CONST(vSwUpdM_GridSrvc_ResponseClassConstType, VSWUPDM_CONST) vSwUpdM_GridSrvc_ResponseClassConst[VSWUPDM_GRIDSRVC_RESPONSECLASS_COUNT] =
{
  /* Channel,                                   Buffer,                                                                                                                       AggregatedResult */
  /* PRQA S 0310 8 */ /* MD_vSwUpdM_Rule11.3_0310_ServiceParameterCast */
  { VSWUPDM_GRIDCHANNEL_CHANNELIDX_MAIN,        (vSwUpdM_GridSrvc_ResponseClassBasePtrType) vSwUpdM_GridNode_ResponseMain,        (vSwUpdM_GridSrvc_ResponseClassBasePtrType) &vSwUpdM_GridSrvc_ResponseMain_Aggregated        }, /* VSWUPDM_GRIDSRVC_RESPONSECLASS_MAIN,    */
  { VSWUPDM_GRIDCHANNEL_CHANNELIDX_MAINTENANCE, (vSwUpdM_GridSrvc_ResponseClassBasePtrType) vSwUpdM_GridNode_ResponseMaintenance, (vSwUpdM_GridSrvc_ResponseClassBasePtrType) &vSwUpdM_GridSrvc_ResponseMaintenance_Aggregated }, /* VSWUPDM_GRIDSRVC_RESPONSECLASS_MAINTENANCE,    */
  { VSWUPDM_GRIDCHANNEL_CHANNELIDX_SUSPEND,     (vSwUpdM_GridSrvc_ResponseClassBasePtrType) vSwUpdM_GridNode_ResponseSuspend,     (vSwUpdM_GridSrvc_ResponseClassBasePtrType) &vSwUpdM_GridSrvc_ResponseSuspend_Aggregated     }, /* VSWUPDM_GRIDSRVC_RESPONSECLASS_SUSPEND, */
  { VSWUPDM_GRIDCHANNEL_CHANNELIDX_BOOKKEEPER,  (vSwUpdM_GridSrvc_ResponseClassBasePtrType) vSwUpdM_GridNode_ResponseBookkeeper,  (vSwUpdM_GridSrvc_ResponseClassBasePtrType) &vSwUpdM_GridSrvc_ResponseBookkeeper_Aggregated  }, /* VSWUPDM_GRIDSRVC_RESPONSECLASS_BK, */
  { VSWUPDM_GRIDCHANNEL_CHANNELIDX_BOOKKEEPER,  (vSwUpdM_GridSrvc_ResponseClassBasePtrType) vSwUpdM_GridNode_ResponseBookkeeper,  (vSwUpdM_GridSrvc_ResponseClassBasePtrType) &vSwUpdM_GridSrvc_ResponseBookkeeper_Aggregated  }, /* VSWUPDM_GRIDSRVC_RESPONSECLASS_BK_GET */
  { VSWUPDM_GRIDCHANNEL_CHANNELIDX_BOOKKEEPER,  (vSwUpdM_GridSrvc_ResponseClassBasePtrType) vSwUpdM_GridNode_ResponseBookkeeper,  (vSwUpdM_GridSrvc_ResponseClassBasePtrType) &vSwUpdM_GridSrvc_ResponseBookkeeper_Aggregated  }, /* VSWUPDM_GRIDSRVC_RESPONSECLASS_BK_GET_SEGMENT_ATTRIBUTES */
  { VSWUPDM_GRIDCHANNEL_CHANNELIDX_BOOKKEEPER,  (vSwUpdM_GridSrvc_ResponseClassBasePtrType) vSwUpdM_GridNode_ResponseBookkeeper,  (vSwUpdM_GridSrvc_ResponseClassBasePtrType) &vSwUpdM_GridSrvc_ResponseBookkeeper_Aggregated  }, /* VSWUPDM_GRIDSRVC_RESPONSECLASS_BK_GET_RESUME_INFO */
  { VSWUPDM_GRIDCHANNEL_CHANNELIDX_MAIN,        (vSwUpdM_GridSrvc_ResponseClassBasePtrType) NULL_PTR,                             (vSwUpdM_GridSrvc_ResponseClassBasePtrType) NULL_PTR                                         }  /* VSWUPDM_GRIDSRVC_RESPONSECLASS_LEGACY    */
};

#if (VSWUPDM_MULTICONTROLLER_SUPPORT == STD_ON)
/*!
* Internal comment removed.
 *
 *
*/

CONST(vSwUpdM_RemoteServiceDefinitionType, VSWUPDM_CONST) vSwUpdM_RemoteServiceDefinitions[48u] =
{
  { VSWUPDM_GRIDSRVC_SERVICEIDX_ADD_SEGMENT,                                VSWUPDM_SID_ADD_SEGMENT,                         VSWUPDM_E_REMOTE_ADD_SEGMENT_FAILED,              VSWUPDM_REMOTE_TX_ERROR_HANDLER_CONFIRMATION },
  { VSWUPDM_GRIDSRVC_SERVICEIDX_CHECK_PARTITION,                            VSWUPDM_SID_CHECK_PARTITION_CONSISTENCY,         VSWUPDM_E_REMOTE_CHECK_PARTITION_FAILED,          VSWUPDM_REMOTE_TX_ERROR_HANDLER_CONFIRMATION },
  { VSWUPDM_GRIDSRVC_SERVICEIDX_CLEAR_SEGMENTS_OF_MODULE,                   VSWUPDM_SID_CLEAR_SEGMENTS_OF_MODULE,            VSWUPDM_E_REMOTE_CLEAR_SEGMENTS_OF_MODULE_FAILED, VSWUPDM_REMOTE_TX_ERROR_HANDLER_CONFIRMATION },
  { VSWUPDM_GRIDSRVC_SERVICEIDX_CLOSE_MODULE,                               VSWUPDM_SID_CLOSE_MODULE,                        VSWUPDM_E_REMOTE_CLOSE_MODULE_FAILED,             VSWUPDM_REMOTE_TX_ERROR_HANDLER_CONFIRMATION },
  { VSWUPDM_GRIDSRVC_SERVICEIDX_CLOSE_SEGMENT,                              VSWUPDM_SID_CLOSE_SEGMENT,                       VSWUPDM_E_REMOTE_CLOSE_SEGMENT_FAILED,            VSWUPDM_REMOTE_TX_ERROR_HANDLER_CONFIRMATION },
  { VSWUPDM_GRIDSRVC_SERVICEIDX_END_STREAM,                                 VSWUPDM_SID_END_STREAM,                          VSWUPDM_E_REMOTE_END_STREAM_FAILED,               VSWUPDM_REMOTE_TX_ERROR_HANDLER_CONFIRMATION },
  { VSWUPDM_GRIDSRVC_SERVICEIDX_ERASE_MODULE,                               VSWUPDM_SID_ERASE_MODULE,                        VSWUPDM_E_REMOTE_ERASE_MODULE_FAILED,             VSWUPDM_REMOTE_TX_ERROR_HANDLER_CONFIRMATION },
  { VSWUPDM_GRIDSRVC_SERVICEIDX_ERASE_REGION,                               VSWUPDM_SID_ERASE_REGION,                        VSWUPDM_E_REMOTE_ERASE_REGION_FAILED,             VSWUPDM_REMOTE_TX_ERROR_HANDLER_CONFIRMATION },
  { VSWUPDM_GRIDSRVC_SERVICEIDX_FINALIZE_MODULE,                            VSWUPDM_SID_FINALIZE_MODULE,                     VSWUPDM_E_REMOTE_FINALIZE_MODULE_FAILED,          VSWUPDM_REMOTE_TX_ERROR_HANDLER_CONFIRMATION },
  { VSWUPDM_GRIDSRVC_SERVICEIDX_FINALIZE_SEGMENT,                           VSWUPDM_SID_FINALIZE_SEGMENT,                    VSWUPDM_E_REMOTE_FINALIZE_SEGMENT_FAILED,         VSWUPDM_REMOTE_TX_ERROR_HANDLER_CONFIRMATION },
  { VSWUPDM_GRIDSRVC_SERVICEIDX_INVALIDATE_MODULE,                          VSWUPDM_SID_INVALIDATE_MODULE,                   VSWUPDM_E_REMOTE_INVALIDATE_MODULE_FAILED,        VSWUPDM_REMOTE_TX_ERROR_HANDLER_CONFIRMATION },
  { VSWUPDM_GRIDSRVC_SERVICEIDX_INDICATE_WRITE_TO_MODULE,                   VSWUPDM_SID_INDICATE_WRITE_TO_MODULE,            VSWUPDM_E_REMOTE_INDICATE_WRITE_TO_MODULE_FAILED, VSWUPDM_REMOTE_TX_ERROR_HANDLER_CONFIRMATION },
  { VSWUPDM_GRIDSRVC_SERVICEIDX_LOCK,                                       VSWUPDM_SID_NONE,                                VSWUPDM_E_REMOTE_LOCK_FAILED,                     VSWUPDM_REMOTE_TX_ERROR_HANDLER_CONFIRMATION },
  { VSWUPDM_GRIDSRVC_SERVICEIDX_OPEN_MODULE,                                VSWUPDM_SID_OPEN_MODULE,                         VSWUPDM_E_REMOTE_OPEN_MODULE_FAILED,              VSWUPDM_REMOTE_TX_ERROR_HANDLER_CONFIRMATION },
  { VSWUPDM_GRIDSRVC_SERVICEIDX_OPEN_PARTITION,                             VSWUPDM_SID_OPEN_PARTITION,                      VSWUPDM_E_REMOTE_OPEN_PARTITION_FAILED,           VSWUPDM_REMOTE_TX_ERROR_HANDLER_CONFIRMATION },
  { VSWUPDM_GRIDSRVC_SERVICEIDX_OPEN_SEGMENT,                               VSWUPDM_SID_OPEN_SEGMENT,                        VSWUPDM_E_REMOTE_OPEN_SEGMENT_FAILED,             VSWUPDM_REMOTE_TX_ERROR_HANDLER_CONFIRMATION },
  { VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_PROCESS_STREAM_DATA,                 VSWUPDM_SID_PROCESS_STREAM_DATA,                 VSWUPDM_E_INV_STATE /* Unused */,                 VSWUPDM_REMOTE_TX_ERROR_HANDLER_PROC_STREAM  },
  { VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_COPY_STREAM_DATA,                    VSWUPDM_SID_NONE,                                VSWUPDM_E_INV_STATE /* Unused */,                 VSWUPDM_REMOTE_TX_ERROR_HANDLER_PROC_STREAM  },
  { VSWUPDM_GRIDSRVC_SERVICEIDX_RESUME,                                     VSWUPDM_SID_RESUME,                              VSWUPDM_E_REMOTE_RESUME_FAILED,                   VSWUPDM_REMOTE_TX_ERROR_HANDLER_CONFIRMATION },
  { VSWUPDM_GRIDSRVC_SERVICEIDX_SET_PARTITION_INVALID,                      VSWUPDM_SID_INVALIDATE_PARTITION,                VSWUPDM_E_REMOTE_INVALIDATE_PARTITION_FAILED,     VSWUPDM_REMOTE_TX_ERROR_HANDLER_CONFIRMATION },
  { VSWUPDM_GRIDSRVC_SERVICEIDX_SET_PARTITION_VALID,                        VSWUPDM_SID_VALIDATE_PARTITION,                  VSWUPDM_E_REMOTE_VALIDATE_PARTITION_FAILED,       VSWUPDM_REMOTE_TX_ERROR_HANDLER_CONFIRMATION },
  { VSWUPDM_GRIDSRVC_SERVICEIDX_START,                                      VSWUPDM_SID_START,                               VSWUPDM_E_REMOTE_START_FAILED,                    VSWUPDM_REMOTE_TX_ERROR_HANDLER_CONFIRMATION },
  { VSWUPDM_GRIDSRVC_SERVICEIDX_START_STREAM,                               VSWUPDM_SID_START_STREAM,                        VSWUPDM_E_REMOTE_START_STREAM_FAILED,             VSWUPDM_REMOTE_TX_ERROR_HANDLER_CONFIRMATION },
  { VSWUPDM_GRIDSRVC_SERVICEIDX_SUSPEND,                                    VSWUPDM_SID_SUSPEND,                             VSWUPDM_E_REMOTE_SUSPEND_FAILED,                  VSWUPDM_REMOTE_TX_ERROR_HANDLER_CONFIRMATION },
  { VSWUPDM_GRIDSRVC_SERVICEIDX_SWAP_PARTITION,                             VSWUPDM_SID_SWAP_ACTIVE_PARTITION,               VSWUPDM_E_REMOTE_SWAP_PARTITION_FAILED,           VSWUPDM_REMOTE_TX_ERROR_HANDLER_CONFIRMATION },
  { VSWUPDM_GRIDSRVC_SERVICEIDX_SYNC_MODULE,                                VSWUPDM_SID_SYNC_MODULE,                         VSWUPDM_E_REMOTE_SYNC_MODULE_FAILED,              VSWUPDM_REMOTE_TX_ERROR_HANDLER_CONFIRMATION },
  { VSWUPDM_GRIDSRVC_SERVICEIDX_SYNC_PARTITION,                             VSWUPDM_SID_SYNC_PARTITION,                      VSWUPDM_E_REMOTE_SYNC_PARTITION_FAILED,           VSWUPDM_REMOTE_TX_ERROR_HANDLER_CONFIRMATION },
  { VSWUPDM_GRIDSRVC_SERVICEIDX_UNLOCK,                                     VSWUPDM_SID_SHUTDOWN,                            VSWUPDM_E_NO_ERROR /* Keep remote error code. */, VSWUPDM_REMOTE_TX_ERROR_HANDLER_CONFIRMATION },
  { VSWUPDM_GRIDSRVC_SERVICEIDX_VALIDATE_MODULE,                            VSWUPDM_SID_VALIDATE_MODULE,                     VSWUPDM_E_REMOTE_VALIDATE_MODULE_FAILED,          VSWUPDM_REMOTE_TX_ERROR_HANDLER_CONFIRMATION },
  { VSWUPDM_GRIDSRVC_SERVICEIDX_VERIFY_MODULE,                              VSWUPDM_SID_VERIFY_MODULE,                       VSWUPDM_E_REMOTE_VERIFY_MODULE_FAILED,            VSWUPDM_REMOTE_TX_ERROR_HANDLER_CONFIRMATION },
  { VSWUPDM_GRIDSRVC_SERVICEIDX_PROCESS_MODULE,                             VSWUPDM_SID_PROCESS_MODULE,                      VSWUPDM_E_REMOTE_PROCESS_MODULE_FAILED,           VSWUPDM_REMOTE_TX_ERROR_HANDLER_CONFIRMATION },
  { VSWUPDM_GRIDSRVC_SERVICEIDX_VERIFY_SEGMENT,                             VSWUPDM_SID_VERIFY_SEGMENT,                      VSWUPDM_E_REMOTE_VERIFY_SEGMENT_FAILED,           VSWUPDM_REMOTE_TX_ERROR_HANDLER_CONFIRMATION },
  { VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_REQUEST_PROCESS_INFO,                VSWUPDM_SID_REQUEST_PROCESS_INFO,                VSWUPDM_E_REMOTE_REQUEST_PROCESS_INFO,            VSWUPDM_REMOTE_TX_ERROR_HANDLER_CONFIRMATION },
  { VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_CONCLUDE_SEGMENT,                    VSWUPDM_SID_CONCLUDE_SEGMENT,                    VSWUPDM_E_REMOTE_CONCLUDE_SEGMENT,                VSWUPDM_REMOTE_TX_ERROR_HANDLER_CONFIRMATION },
  { VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_RESPONSE_COPY_STREAM_DATA,           VSWUPDM_SID_NONE,                                VSWUPDM_E_INV_STATE /* Unused. */,                VSWUPDM_REMOTE_TX_ERROR_HANDLER_PROC_STREAM  },
  { VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_PERSIST_MODULE_STATE,                VSWUPDM_SID_UPDATE_MODULE_STATE,                 VSWUPDM_E_NO_ERROR /* Keep remote error code. */, VSWUPDM_REMOTE_TX_ERROR_HANDLER_CONFIRMATION },
  { VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_PERSIST_MODULE_VALID,                VSWUPDM_SID_UPDATE_MODULE_VALID,                 VSWUPDM_E_NO_ERROR /* Keep remote error code. */, VSWUPDM_REMOTE_TX_ERROR_HANDLER_CONFIRMATION },
  { VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_PERSIST_MODULE_PROGRAMMING_ATTEMPTS, VSWUPDM_SID_UPDATE_MODULE_PROGRAMMING_ATTEMPTS,  VSWUPDM_E_NO_ERROR /* Keep remote error code. */, VSWUPDM_REMOTE_TX_ERROR_HANDLER_CONFIRMATION },
  { VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_PERSIST_REGION_STATE,                VSWUPDM_SID_UPDATE_REGION_STATE,                 VSWUPDM_E_NO_ERROR /* Keep remote error code. */, VSWUPDM_REMOTE_TX_ERROR_HANDLER_CONFIRMATION },
  { VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_PERSIST_REGION_PROGRAMMING_ATTEMPTS, VSWUPDM_SID_UPDATE_REGION_PROGRAMMING_ATTEMPTS,  VSWUPDM_E_NO_ERROR /* Keep remote error code. */, VSWUPDM_REMOTE_TX_ERROR_HANDLER_CONFIRMATION },
  { VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_PERSIST_SEGMENT_ATTRIBUTES,          VSWUPDM_SID_UPDATE_SEGMENT_ATTRIBUTES,           VSWUPDM_E_NO_ERROR /* Keep remote error code. */, VSWUPDM_REMOTE_TX_ERROR_HANDLER_CONFIRMATION },
  { VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_PERSIST_RESUME_INFO,                 VSWUPDM_SID_UPDATE_RESUME_INFO,                  VSWUPDM_E_NO_ERROR /* Keep remote error code. */, VSWUPDM_REMOTE_TX_ERROR_HANDLER_CONFIRMATION },
  { VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_CONFIRMATION,                        VSWUPDM_SID_NONE,                                VSWUPDM_E_INV_STATE /* Unused */,                 VSWUPDM_REMOTE_TX_ERROR_HANDLER_ABORT_WAIT   },
  { VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_STREAM_COPY,                         VSWUPDM_SID_NONE,                                VSWUPDM_E_INV_STATE /* Unused */,                 VSWUPDM_REMOTE_TX_ERROR_HANDLER_STREAM       },
  { VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_STREAM_END,                          VSWUPDM_SID_NONE,                                VSWUPDM_E_INV_STATE /* Unused */,                 VSWUPDM_REMOTE_TX_ERROR_HANDLER_ABORT_WAIT   },
  { VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_STREAM_REQUEST,                      VSWUPDM_SID_NONE,                                VSWUPDM_E_INV_STATE /* Unused */,                 VSWUPDM_REMOTE_TX_ERROR_HANDLER_STREAM       },
  { VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_STREAM_START,                        VSWUPDM_SID_NONE,                                VSWUPDM_E_INV_STATE /* Unused */,                 VSWUPDM_REMOTE_TX_ERROR_HANDLER_STREAM       },
  /* End marker */
  { VSWUPDM_GRIDSRVC_SERVICEIDX_UNDEFINED,                                  VSWUPDM_SID_NONE,                                VSWUPDM_E_INV_STATE /* Unused */,                 VSWUPDM_REMOTE_TX_ERROR_HANDLER_STREAM       }
};
#endif /* VSWUPDM_MULTICONTROLLER_SUPPORT == STD_ON */

#define VSWUPDM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define VSWUPDM_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define VSWUPDM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*********************
 * GRID CHANNEL
 ********************/

#define VSWUPDM_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

VAR(vSwUpdM_GridChannel_VarChannelType, VSWUPDM_APPL_DATA)    vSwUpdM_GridChannel_VarChannel[VSWUPDM_GRIDCHANNEL_CHANNELIDX_COUNT];

#define VSWUPDM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define VSWUPDM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* PRQA S 0310, 1514 5 */ /* MD_vSwUpdM_Rule11.3_0310_ServiceParameterCast, MD_CSL_ObjectOnlyAccessedOnce */
CONST(vSwUpdM_GridSrvc_ServiceClassBasePtrType, VSWUPDM_APPL_DATA) vSwUpdM_GridChannel_RequestBuffer[VSWUPDM_GRIDCHANNEL_CHANNELIDX_COUNT] = {
  (vSwUpdM_GridSrvc_ServiceClassBasePtrType)&vSwUpdM_GridChannel_RequestBufferMainChannel,        /* VSWUPDM_GRIDCHANNEL_CHANNELIDX_MAIN */
  (vSwUpdM_GridSrvc_ServiceClassBasePtrType)&vSwUpdM_GridChannel_RequestBufferMaintenanceChannel, /* VSWUPDM_GRIDCHANNEL_CHANNELIDX_MAINTENANCE */
  (vSwUpdM_GridSrvc_ServiceClassBasePtrType)&vSwUpdM_GridChannel_RequestBufferSuspendChannel,     /* VSWUPDM_GRIDCHANNEL_CHANNELIDX_SUSPEND */
  (vSwUpdM_GridSrvc_ServiceClassBasePtrType)&vSwUpdM_GridChannel_RequestBufferBookkeeperChannel   /* VSWUPDM_GRIDCHANNEL_CHANNELIDX_BOOKKEEPER */
};

/*********************
 * GRID RPC
 ********************/
#if (VSWUPDM_MULTICONTROLLER_SUPPORT == STD_ON)
/*!
 * Internal comment removed.
 *
 *
 */
CONST(vSwUpdM_RpcProxyServiceIdType, VSWUPDM_CONST) vSwUpdM_GridRpc_ProxyService[VSWUPDM_GRIDSRVC_SERVICEIDX_COUNT] =
{
  /* Maintenance Channel */
  vRpcProxyConf_vRpcProxyTxService_vSwUpdM_GridRpc_MaintenanceService,             /* VSWUPDM_GRIDSRVC_SERVICEIDX_LOCK */
  vRpcProxyConf_vRpcProxyTxService_vSwUpdM_GridRpc_MaintenanceService,             /* VSWUPDM_GRIDSRVC_SERVICEIDX_SHUTDOWN */
  vRpcProxyConf_vRpcProxyTxService_vSwUpdM_GridRpc_MaintenanceService,             /* VSWUPDM_GRIDSRVC_SERVICEIDX_UNLOCK */
  /* Suspend Channel */
  vRpcProxyConf_vRpcProxyTxService_vSwUpdM_GridRpc_SuspendService,                 /* VSWUPDM_GRIDSRVC_SERVICEIDX_SUSPEND */
  vRpcProxyConf_vRpcProxyTxService_vSwUpdM_GridRpc_SuspendService,                 /* VSWUPDM_GRIDSRVC_SERVICEIDX_RESUME */
  /* Main Channel */
  vRpcProxyConf_vRpcProxyTxService_vSwUpdM_GridRpc_GenericService,                 /* VSWUPDM_GRIDSRVC_SERVICEIDX_START */
  vRpcProxyConf_vRpcProxyTxService_vSwUpdM_GridRpc_GenericService,                 /* VSWUPDM_GRIDSRVC_SERVICEIDX_END_STREAM */
  vRpcProxyConf_vRpcProxyTxService_vSwUpdM_GridRpc_PartitionService,               /* VSWUPDM_GRIDSRVC_SERVICEIDX_OPEN_PARTITION */

  vRpcProxyConf_vRpcProxyTxService_vSwUpdM_GridRpc_GenericService,                 /* VSWUPDM_GRIDSRVC_SERVICEIDX_CHECK_PARTITION */
  vRpcProxyConf_vRpcProxyTxService_vSwUpdM_GridRpc_GenericService,                 /* VSWUPDM_GRIDSRVC_SERVICEIDX_SET_PARTITION_VALID */
  vRpcProxyConf_vRpcProxyTxService_vSwUpdM_GridRpc_GenericService,                 /* VSWUPDM_GRIDSRVC_SERVICEIDX_SET_PARTITION_INVALID */
  vRpcProxyConf_vRpcProxyTxService_vSwUpdM_GridRpc_GenericService,                 /* VSWUPDM_GRIDSRVC_SERVICEIDX_SYNC_PARTITION */
  vRpcProxyConf_vRpcProxyTxService_vSwUpdM_GridRpc_GenericService,                 /* VSWUPDM_GRIDSRVC_SERVICEIDX_SWAP_PARTITION */

  vRpcProxyConf_vRpcProxyTxService_vSwUpdM_GridRpc_ModuleService,                  /* VSWUPDM_GRIDSRVC_SERVICEIDX_OPEN_MODULE */
  vRpcProxyConf_vRpcProxyTxService_vSwUpdM_GridRpc_ModuleService,                  /* VSWUPDM_GRIDSRVC_SERVICEIDX_CLOSE_MODULE */
  vRpcProxyConf_vRpcProxyTxService_vSwUpdM_GridRpc_ModuleService,                  /* VSWUPDM_GRIDSRVC_SERVICEIDX_ERASE_MODULE */
  vRpcProxyConf_vRpcProxyTxService_vSwUpdM_GridRpc_ModuleService,                  /* VSWUPDM_GRIDSRVC_SERVICEIDX_FINALIZE_MODULE */
  vRpcProxyConf_vRpcProxyTxService_vSwUpdM_GridRpc_ModuleService,                  /* VSWUPDM_GRIDSRVC_SERVICEIDX_SYNC_MODULE */
  vRpcProxyConf_vRpcProxyTxService_vSwUpdM_GridRpc_ModuleService,                  /* VSWUPDM_GRIDSRVC_SERVICEIDX_VALIDATE_MODULE */
  vRpcProxyConf_vRpcProxyTxService_vSwUpdM_GridRpc_ModuleService,                  /* VSWUPDM_GRIDSRVC_SERVICEIDX_INVALIDATE_MODULE */
  vRpcProxyConf_vRpcProxyTxService_vSwUpdM_GridRpc_ModuleService,                  /* VSWUPDM_GRIDSRVC_SERVICEIDX_CLEAR_SEGMENTS_OF_MODULE */
  vRpcProxyConf_vRpcProxyTxService_vSwUpdM_GridRpc_ModuleService,                  /* VSWUPDM_GRIDSRVC_SERVICEIDX_INDICATE_WRITE_TO_MODULE */

  vRpcProxyConf_vRpcProxyTxService_vSwUpdM_GridRpc_RegionService,                  /* VSWUPDM_GRIDSRVC_SERVICEIDX_ERASE_REGION */

  vRpcProxyConf_vRpcProxyTxService_vSwUpdM_GridRpc_SegmentService,                 /* VSWUPDM_GRIDSRVC_SERVICEIDX_OPEN_SEGMENT */
  vRpcProxyConf_vRpcProxyTxService_vSwUpdM_GridRpc_SegmentService,                 /* VSWUPDM_GRIDSRVC_SERVICEIDX_CLOSE_SEGMENT */
  vRpcProxyConf_vRpcProxyTxService_vSwUpdM_GridRpc_SegmentService,                 /* VSWUPDM_GRIDSRVC_SERVICEIDX_FINALIZE_SEGMENT */

  vRpcProxyConf_vRpcProxyTxService_vSwUpdM_GridRpc_ProcessModuleService,           /* VSWUPDM_GRIDSRVC_SERVICEIDX_VERIFY_MODULE */
  vRpcProxyConf_vRpcProxyTxService_vSwUpdM_GridRpc_ProcessModuleService,           /* VSWUPDM_GRIDSRVC_SERVICEIDX_PROCESS_MODULE */

  vRpcProxyConf_vRpcProxyTxService_vSwUpdM_GridRpc_StartStream,                    /* VSWUPDM_GRIDSRVC_SERVICEIDX_START_STREAM */
  vRpcProxyConf_vRpcProxyTxService_vSwUpdM_GridRpc_AddSegment,                     /* VSWUPDM_GRIDSRVC_SERVICEIDX_ADD_SEGMENT */

  vRpcProxyConf_vRpcProxyTxService_vSwUpdM_GridRpc_SegmentService,                 /* VSWUPDM_GRIDSRVC_SERVICEIDX_VERIFY_SEGMENT */
  /* Bookkeeper */
  vRpcProxyConf_vRpcProxyTxService_vSwUpdM_GridRpc_BkSetGenericParameter,          /* VSWUPDM_GRIDSRVC_SERVICEIDX_BK_SET_GENERIC_PARAMETER */
  vRpcProxyConf_vRpcProxyTxService_vSwUpdM_GridRpc_BkSetSegmentAttributes,         /* VSWUPDM_GRIDSRVC_SERVICEIDX_BK_SET_SEGMENT_ATTRIBUTES */
  vRpcProxyConf_vRpcProxyTxService_vSwUpdM_GridRpc_BkSetResumeInfo,                /* VSWUPDM_GRIDSRVC_SERVICEIDX_BK_SET_RESUME_INFO */
  vRpcProxyConf_vRpcProxyTxService_vSwUpdM_GridRpc_BkGetGenericParameter,          /* VSWUPDM_GRIDSRVC_SERVICEIDX_BK_GET_GENERIC_PARAMETER */
  vRpcProxyConf_vRpcProxyTxService_vSwUpdM_GridRpc_BkGetSegmentAttributes,         /* VSWUPDM_GRIDSRVC_SERVICEIDX_BK_GET_SEGMENT_ATTRIBUTES */
  vRpcProxyConf_vRpcProxyTxService_vSwUpdM_GridRpc_BkGetResumeInfo,                /* VSWUPDM_GRIDSRVC_SERVICEIDX_BK_GET_RESUME_INFO */
  vRpcProxyConf_vRpcProxyTxService_vSwUpdM_GridRpc_BkExecCommand,                  /* VSWUPDM_GRIDSRVC_SERVICEIDX_BK_EXEC_COMMAND */
  /* Legacy Services */
  vRpcProxyConf_vRpcProxyTxService_vSwUpdM_RemoteConcludeSegment,                  /* VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_CONCLUDE_SEGMENT */
  vRpcProxyConf_vRpcProxyTxService_vSwUpdM_RemoteCopyStreamData,                   /* VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_COPY_STREAM_DATA */
  vRpcProxyConf_vRpcProxyTxService_vSwUpdM_RemoteProcessRequestInput,              /* VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_REQUEST_PROCESS_INFO */
  vRpcProxyConf_vRpcProxyTxService_vSwUpdM_RemoteProcessStreamData,                /* VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_PROCESS_STREAM_DATA */
  vRpcProxyConf_vRpcProxyTxService_vSwUpdM_RemoteResponseCopyStreamData,           /* VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_RESPONSE_COPY_STREAM_DATA */

  vRpcProxyConf_vRpcProxyTxService_vSwUpdM_RemoteUpdateModuleState,                /* VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_PERSIST_MODULE_STATE */
  vRpcProxyConf_vRpcProxyTxService_vSwUpdM_RemoteUpdateModuleValid,                /* VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_PERSIST_MODULE_VALID */
  vRpcProxyConf_vRpcProxyTxService_vSwUpdM_RemoteUpdateModuleProgrammingAttempts,  /* VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_PERSIST_MODULE_PROGRAMMING_ATTEMPTS */
  vRpcProxyConf_vRpcProxyTxService_vSwUpdM_RemoteUpdateRegionState,                /* VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_PERSIST_REGION_STATE */
  vRpcProxyConf_vRpcProxyTxService_vSwUpdM_RemoteUpdateRegionProgrammingAttempts,  /* VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_PERSIST_REGION_PROGRAMMING_ATTEMPTS */
  vRpcProxyConf_vRpcProxyTxService_vSwUpdM_RemoteUpdateSegmentAttributes,          /* VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_PERSIST_SEGMENT_ATTRIBUTES */
  vRpcProxyConf_vRpcProxyTxService_vSwUpdM_RemoteUpdateResumeInfo,                 /* VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_PERSIST_RESUME_INFO */
  vRpcProxyConf_vRpcProxyTxService_vSwUpdM_RemoteConfirmation,                     /* VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_CONFIRMATION */
  vRpcProxyConf_vRpcProxyTxService_vSwUpdM_RemoteStreamCopy,                       /* VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_STREAM_COPY */
  vRpcProxyConf_vRpcProxyTxService_vSwUpdM_RemoteStreamEnd,                        /* VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_STREAM_END */
  vRpcProxyConf_vRpcProxyTxService_vSwUpdM_RemoteStreamRequest,                    /* VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_STREAM_REQUEST */
  vRpcProxyConf_vRpcProxyTxService_vSwUpdM_RemoteStreamStart,                      /* VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_STREAM_START */
};
#endif

VSWUPDM_LOCAL CONST(vSwUpdM_GridRpc_RequestServiceType, VSWUPDM_CONST) vSwUpdM_GridRpc_RequestService[VSWUPDM_GRIDSRVC_CLASS_SEGMENT_COUNT] =    /* PRQA S 3218 */ /* MD_vSwUpdM_Rule8.9_3218_FileScope */
{
#if (VSWUPDM_MULTICONTROLLER_SUPPORT == STD_ON)
    NULL_PTR,                                            /* VSWUPDM_GRIDSRVC_CLASS_NONE */
    &vSwUpdM_GridRpc_ProxySuspendService,                /* VSWUPDM_GRIDSRVC_CLASS_SUSPEND */
    &vSwUpdM_GridRpc_ProxyGenericService,                /* VSWUPDM_GRIDSRVC_CLASS_GENERIC */
    &vSwUpdM_GridRpc_ProxyMaintenanceService,            /* VSWUPDM_GRIDSRVC_CLASS_MAINTENANCE */
    &vSwUpdM_GridRpc_ProxyPartitionService,              /* VSWUPDM_GRIDSRVC_CLASS_PARTITION */
    &vSwUpdM_GridRpc_ProxyModuleService,                 /* VSWUPDM_GRIDSRVC_CLASS_MODULE */
    &vSwUpdM_GridRpc_ProxyRegionService,                 /* VSWUPDM_GRIDSRVC_CLASS_REGION */
    &vSwUpdM_GridRpc_ProxySegmentService,                /* VSWUPDM_GRIDSRVC_CLASS_SEGMENT */
    &vSwUpdM_GridRpc_ProxyProcessModuleService,          /* VSWUPDM_GRIDSRVC_CLASS_PROCESS_MODULE */
    &vSwUpdM_GridRpc_ProxyStartStreamService,            /* VSWUPDM_GRIDSRVC_CLASS_STREAM_INFO */
    &vSwUpdM_GridRpc_ProxyAddSegmentService,             /* VSWUPDM_GRIDSRVC_CLASS_SEGMENT_INFO */
    &vSwUpdM_GridRpc_ProxyBkExecCommandService,          /* VSWUPDM_GRIDSRVC_CLASS_BK_EXEC_COMMAND */
    &vSwUpdM_GridRpc_ProxyBkGetGenericParameterService,  /* VSWUPDM_GRIDSRVC_CLASS_BK_GET_GENERIC_PARAMETER */
    &vSwUpdM_GridRpc_ProxyBkGetSegmentAttributesService, /* VSWUPDM_GRIDSRVC_CLASS_BK_GET_SEGMENT_ATTRIBUTES */
    &vSwUpdM_GridRpc_ProxyBkGetResumeInfoService,        /* VSWUPDM_GRIDSRVC_CLASS_BK_GET_RESUME_INFO */
    &vSwUpdM_GridRpc_ProxyBkSetGenericParameterService,  /* VSWUPDM_GRIDSRVC_CLASS_BK_SET_GENERIC_PARAMETER */
    &vSwUpdM_GridRpc_ProxyBkSetSegmentAttributesService, /* VSWUPDM_GRIDSRVC_CLASS_BK_SET_SEGMENT_ATTRIBUTES */
    &vSwUpdM_GridRpc_ProxyBkSetResumeInfoService         /* VSWUPDM_GRIDSRVC_CLASS_BK_SET_RESUME_INFO */
#else
    NULL_PTR,                                            /* VSWUPDM_GRIDSRVC_CLASS_NONE */
    NULL_PTR,                                            /* VSWUPDM_GRIDSRVC_CLASS_SUSPEND */
    NULL_PTR,                                            /* VSWUPDM_GRIDSRVC_CLASS_GENERIC */
    NULL_PTR,                                            /* VSWUPDM_GRIDSRVC_CLASS_MAINTENANCE */
    NULL_PTR,                                            /* VSWUPDM_GRIDSRVC_CLASS_PARTITION */
    NULL_PTR,                                            /* VSWUPDM_GRIDSRVC_CLASS_MODULE */
    NULL_PTR,                                            /* VSWUPDM_GRIDSRVC_CLASS_REGION */
    NULL_PTR,                                            /* VSWUPDM_GRIDSRVC_CLASS_SEGMENT */
    NULL_PTR,                                            /* VSWUPDM_GRIDSRVC_CLASS_PROCESS_MODULE */
    NULL_PTR,                                            /* VSWUPDM_GRIDSRVC_CLASS_STREAM_INFO */
    NULL_PTR,                                            /* VSWUPDM_GRIDSRVC_CLASS_SEGMENT_INFO */
    &vSwUpdM_GridRpc_LocalBkExecCommandService,          /* VSWUPDM_GRIDSRVC_CLASS_BK_EXEC_COMMAND */
    &vSwUpdM_GridRpc_LocalBkGetGenericParameterService,  /* VSWUPDM_GRIDSRVC_CLASS_BK_GET_GENERIC_PARAMETER */
    &vSwUpdM_GridRpc_LocalBkGetSegmentAttributesService, /* VSWUPDM_GRIDSRVC_CLASS_BK_GET_SEGMENT_ATTRIBUTES */
    &vSwUpdM_GridRpc_LocalBkGetResumeInfoService,        /* VSWUPDM_GRIDSRVC_CLASS_BK_GET_RESUME_INFO */
    &vSwUpdM_GridRpc_LocalBkSetGenericParameterService,  /* VSWUPDM_GRIDSRVC_CLASS_BK_SET_GENERIC_PARAMETER */
    &vSwUpdM_GridRpc_LocalBkSetSegmentAttributesService, /* VSWUPDM_GRIDSRVC_CLASS_BK_SET_SEGMENT_ATTRIBUTES */
    &vSwUpdM_GridRpc_LocalBkSetResumeInfoService         /* VSWUPDM_GRIDSRVC_CLASS_BK_SET_RESUME_INFO */
#endif
};

VSWUPDM_LOCAL CONST(vSwUpdM_GridRpc_ResponseServiceType, VSWUPDM_CONST) vSwUpdM_GridRpc_ResponseService[VSWUPDM_GRIDSRVC_RESPONSECLASS_COUNT] =    /* PRQA S 3218 */ /* MD_vSwUpdM_Rule8.9_3218_FileScope */
{
#if (VSWUPDM_MULTICONTROLLER_SUPPORT == STD_ON)
  &vSwUpdM_GridRpc_ProxyMainConfirmation,               /* VSWUPDM_GRIDSRVC_RESPONSECLASS_MAIN */
  &vSwUpdM_GridRpc_ProxyMaintenanceConfirmation,        /* VSWUPDM_GRIDSRVC_RESPONSECLASS_MAINTENANCE */
  &vSwUpdM_GridRpc_ProxySuspendConfirmation,            /* VSWUPDM_GRIDSRVC_RESPONSECLASS_SUSPEND */
  &vSwUpdM_GridRpc_ProxyBookkeeperConfirmation,         /* VSWUPDM_GRIDSRVC_RESPONSECLASS_BK */
  &vSwUpdM_GridRpc_ProxyBkGetGenericParameterResponse,  /* VSWUPDM_GRIDSRVC_RESPONSECLASS_BK_GET_GENERIC_PARAMETER */
  &vSwUpdM_GridRpc_ProxyBkGetSegmentAttributesResponse, /* VSWUPDM_GRIDSRVC_RESPONSECLASS_BK_GET_SEGMENT_ATTRIBUTES */
  &vSwUpdM_GridRpc_ProxyBkGetResumeInfoResponse,        /* VSWUPDM_GRIDSRVC_RESPONSECLASS_BK_GET_RESUME_INFO */
  &vSwUpdM_GridRpc_ProxyLegacyResponse,                 /* VSWUPDM_GRIDSRVC_RESPONSECLASS_LEGACY */
#else
  NULL_PTR,                                             /* VSWUPDM_GRIDSRVC_RESPONSECLASS_MAIN */
  NULL_PTR,                                             /* VSWUPDM_GRIDSRVC_RESPONSECLASS_MAINTENANCE */
  NULL_PTR,                                             /* VSWUPDM_GRIDSRVC_RESPONSECLASS_SUSPEND */
  &vSwUpdM_GridRpc_LocalBookkeeperConfirmation,         /* VSWUPDM_GRIDSRVC_RESPONSECLASS_BK */
  &vSwUpdM_GridRpc_LocalBkGetGenericParameterResponse,  /* VSWUPDM_GRIDSRVC_RESPONSECLASS_BK_GET_GENERIC_PARAMETER */
  &vSwUpdM_GridRpc_LocalBkGetSegmentAttributesResponse, /* VSWUPDM_GRIDSRVC_RESPONSECLASS_BK_GET_SEGMENT_ATTRIBUTES */
  &vSwUpdM_GridRpc_LocalBkGetResumeInfoResponse,        /* VSWUPDM_GRIDSRVC_RESPONSECLASS_BK_GET_RESUME_INFO */
  NULL_PTR,                                             /* VSWUPDM_GRIDSRVC_RESPONSECLASS_LEGACY */
#endif
};

#define VSWUPDM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/
#define VSWUPDM_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 * vSwUpdM_GridChannel_ConfirmationParameterCheck
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GridChannel_ConfirmationParameterCheck(
  vSwUpdM_GridChannel_ChannelIdxType ChannelIndex,
  vSwUpdM_NodeIterType NodeIndex,
  vSwUpdM_GridSrvc_ServiceIdxType ServiceId)
{
  Std_ReturnType retVal;

  if (vSwUpdM_GridNode_IsNodeContainedInNodeGroup(vSwUpdM_GridChannel_GetDestination(ChannelIndex), NodeIndex) == FALSE)
  {
    retVal = E_NOT_OK;
  }
  else if (vSwUpdM_GridChannel_GetService(ChannelIndex) != ServiceId)
  {
    retVal = E_NOT_OK;
  }
  else if (vSwUpdM_GridNode_GetResultValid(ServiceId, NodeIndex) == TRUE)
  {
    retVal = E_NOT_OK;
  }
  else
  {
    retVal = E_OK;
  }

  return retVal;
} /* vSwUpdM_GridChannel_ConfirmationParameterCheck */

/**********************************************************************************************************************
 * vSwUpdM_GridChannel_ProcessConfirmation
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
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GridChannel_ProcessConfirmation(
  vSwUpdM_GridChannel_ChannelIdxType ChannelIndex,
  vSwUpdM_NodeIterType NodeIndex,
  vSwUpdM_GridRpc_ComplexResponseClassBasePtrType ResponseClass)  /* PRQA S 3673 */ /* MD_vSwUpdM_Rule8.13_3673_PointerToConstParameter */
{
  Std_ReturnType retVal;

  /* #10 Enter critical section to ensure exclusive access on response buffers. */
  VSWUPDM_ENTER_CRITICAL_SECTION();

  /* #20 Check input parameters. */
  retVal = vSwUpdM_GridChannel_ConfirmationParameterCheck(ChannelIndex, NodeIndex, ResponseClass->RequestServiceIdx);

  /* #30 If input parameters valid:*/
  if (retVal == E_OK)
  {
    /* #40 Store complex response part only if response was positive. */
    if (ResponseClass->Result == E_OK)
    {
      switch (ResponseClass->ComplexResponseClassType)
      {
        case VSWUPDM_GRIDRPC_COMPLEXREPONSECLASS_BK_GET_GENERIC_PARAMETER:
        {
          vSwUpdM_BkPersistClient_StoreGetGenericParameterResponse(((vSwUpdM_GridRpc_ComplexResponseClassBkGetGenericPtrType)ResponseClass)->GenericValue);  /* PRQA S 0310 */ /* MD_vSwUpdM_Rule11.3_0310_ServiceParameterCast */
          break;
        }
        case VSWUPDM_GRIDRPC_COMPLEXREPONSECLASS_BK_GET_SEGMENT_ATTRIBUTES:
        {
          vSwUpdM_BkPersistClient_StoreGetSegmentAttributesResponse(((vSwUpdM_GridRpc_ComplexResponseClassBkGetSegmentAttributesPtrType)ResponseClass)->SegmentAttributes);  /* PRQA S 0310 */ /* MD_vSwUpdM_Rule11.3_0310_ServiceParameterCast */
          break;
        }
        case VSWUPDM_GRIDRPC_COMPLEXREPONSECLASS_BK_GET_RESUME_INFO:
        {
          vSwUpdM_BkPersistClient_StoreGetResumeInfoResponse(((vSwUpdM_GridRpc_ComplexResponseClassBkGetResumeInfoPtrType)ResponseClass)->ResumeInfo);  /* PRQA S 0310 */ /* MD_vSwUpdM_Rule11.3_0310_ServiceParameterCast */
          break;
        }
        default:
        {
          /* Simple response */
          break;
        }
      }
    }

    /* #50 Store simple response parameter for aggregation. */
    vSwUpdM_GridChannel_StoreResponseResult(ChannelIndex, NodeIndex, ResponseClass->RequestServiceIdx, ResponseClass->Result);
  }
  /* #60 Leave critical section. */
  VSWUPDM_LEAVE_CRITICAL_SECTION();

  return retVal;
} /* vSwUpdM_GridChannel_ProcessConfirmation */

/*********************
 * GRID NODE
 ********************/

/*********************
 * GRID RPC
 ********************/
#if (VSWUPDM_MULTICONTROLLER_SUPPORT == STD_ON)
/**********************************************************************************************************************
 * vSwUpdM_vSwUpdM_GridRpc_HandleConfirmation
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 */

VSWUPDM_LOCAL FUNC(void, VSWUPDM_CODE) vSwUpdM_GridRpc_HandleConfirmation(
  vSwUpdM_GridChannel_ChannelIdxType ChannelIdx,
  vSwUpdM_GridSrvc_ResponseClassIdxType ResponseClassIdx,
  vRpcProxy_SourcesIterType SourceHandleId,
  uint8 ServiceId,
  uint8 ServiceResult)
{
  vSwUpdM_NodeIterType nodeIndex;
  Std_ReturnType result;
  vSwUpdM_GridRpc_ComplexResponseClassSimpleType responseClass;
  vSwUpdM_GridSrvc_ServiceIdxType serviceIdx  = VSWUPDM_GRIDSRVC_SERVICEIDX_UNDEFINED;

  /* #10 Convert vRpcProxy source to node. */
  result = vSwUpdM_GridNode_GetNodeIndexFromRpcProxySourceAndChannel((vSwUpdM_RpcProxySourceIdType) SourceHandleId, ChannelIdx, &nodeIndex);

  /* #20 Convert service to enum and check for plausibility. */
  if (result == E_OK)
  {
    result = vSwUpdM_GridRpc_GetServiceIndexByResponseService(ServiceId, ResponseClassIdx, &serviceIdx);
  }

  /* #30 Store response. */
  if (result == E_OK)
  {
    /* Pack response for generic response processing. */
    vSwUpdM_GridRpc_InitComplexResponseClassSimpleType(serviceIdx, ServiceResult, &responseClass); /* PRQA S 4342 */ /* MD_vSwUpdM_Rule10.5_4342_EnumParameterCast */

    /* Future vRpcProxy will evaluate return value. */
    (void)vSwUpdM_GridChannel_ProcessConfirmation(ChannelIdx, nodeIndex, (vSwUpdM_GridRpc_ComplexResponseClassBasePtrType)&responseClass); /* PRQA S 0310, 4342 */ /* MD_vSwUpdM_Rule11.3_0310_ServiceParameterCast, MD_vSwUpdM_Rule10.5_4342_EnumParameterCast */
  }
  /* PRQA S 6060 1 */ /* MD_MSR_STPAR */
} /* vSwUpdM_vSwUpdM_GridRpc_HandleConfirmation */

/**********************************************************************************************************************
 * vSwUpdM_GridRpc_RemoteCallCheckPreconditions
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 */
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GridRpc_RemoteCallCheckPreconditions(
  vSwUpdM_NodeIterType SourceIndex)
{
  Std_ReturnType result = E_OK;

  /* #10 Check if the source is fitting to the lock setting. */
  switch (vSwUpdM_GridSrvc_GetCommunicationState())
  {
    case VSWUPDM_GRIDSRVC_GRIDSTATE_LOCKED:
    case VSWUPDM_GRIDSRVC_GRIDSTATE_UNLOCK_PENDING:
    {
      /* #20 If the local node is the master but has not locked the source of this request, report error. */
      if (!vSwUpdM_IsLockedOfVarNode(SourceIndex))
      {
        result = VSWUPDM_E_RESPONSE_PRIVILEGE;
      }

      break;
    }
    default:
    {
      /* #30 If the local node is a slave but the request's source is not the master which is granted the lock, report error. */
      if (vSwUpdM_RemoteLockIsGrantedTo != SourceIndex)
      {
        result = VSWUPDM_E_RESPONSE_PRIVILEGE;
      }

      break;
    }
  }

  return result;

} /* vSwUpdM_GridRpc_RemoteCallCheckPreconditions */

/**********************************************************************************************************************
 * vSwUpdM_GridRpc_RemotePrepareRequestProcessing
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 */
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GridRpc_RemotePrepareRequestProcessing(
  vSwUpdM_RpcProxySourceIdType SourceHandleId,
   P2VAR(vSwUpdM_NodeIterType, AUTOMATIC, VSWUPDM_APPL_VAR) SourceIndex)
{
  Std_ReturnType       result;

  /* #10 Get for vSwUpdM node index by vRprProxy SourceHandleId. */
  result = vSwUpdM_GridNode_GetNodeIndexFromRpcProxySource((vSwUpdM_RpcProxySourceIdType) SourceHandleId, SourceIndex);

  if (result == E_OK)
  {
    /* #20 Check if requester is allowed. */
    result = vSwUpdM_GridRpc_RemoteCallCheckPreconditions(*SourceIndex);
  }

  return result;
} /* vSwUpdM_GridRpc_RemotePrepareRequestProcessing */

/**********************************************************************************************************************
 * vSwUpdM_GridRpc_GenericRequestPreconditionCheck
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GridRpc_GenericRequestPreconditionCheck(
  uint8 ServiceState,
  uint8 Service)
{
  Std_ReturnType retVal = E_OK;

  if ((Service >= ((uint8) VSWUPDM_GRIDSRVC_SERVICEIDX_COUNT))
   || (ServiceState >= ((uint8) VSWUPDM_EXCTSCHEDULE_SERVICESTATE_COUNT))
   || (vSwUpdM_InitState == VSWUPDM_INIT_STATE_UNINIT))
  {
    retVal = E_NOT_OK;
  }

  return retVal;
}

/**********************************************************************************************************************
 * vSwUpdM_GridRpc_GetServiceIndexByService
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GridRpc_GetServiceIndexByService(
  uint8 Service,
  SwUpdM_GridSrvc_ServiceClassType ServiceClass,
  vSwUpdM_GridSrvc_ServiceIdxPtrType ServiceIndex)
{
  Std_ReturnType retVal = E_NOT_OK;
  vSwUpdM_GridSrvc_ServiceIdxType serviceIndex = (vSwUpdM_GridSrvc_ServiceIdxType) Service; /* PRQA S 4342 */ /* MD_vSwUpdM_Rule10.5_4342_EnumParameterCast */

  if (serviceIndex < VSWUPDM_GRIDSRVC_SERVICEIDX_COUNT)
  {
    if (vSwUpdM_GridSrvc_GetServiceClassOfService(serviceIndex) == ServiceClass)
    {
      (*ServiceIndex) = serviceIndex;
      retVal = E_OK;
    }
  }

  return retVal;
}

/**********************************************************************************************************************
 * vSwUpdM_GridRpc_GetServiceIndexByResponseService
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GridRpc_GetServiceIndexByResponseService(
  uint8 Service,
  vSwUpdM_GridSrvc_ResponseClassIdxType ResponseClass,
  vSwUpdM_GridSrvc_ServiceIdxPtrType ServiceIndex)
{
  Std_ReturnType retVal = E_NOT_OK;
  vSwUpdM_GridSrvc_ServiceIdxType serviceIndex = (vSwUpdM_GridSrvc_ServiceIdxType) Service; /* PRQA S 4342 */ /* MD_vSwUpdM_Rule10.5_4342_EnumParameterCast */

  if (serviceIndex < VSWUPDM_GRIDSRVC_SERVICEIDX_COUNT)
  {
    if (vSwUpdM_GridSrvc_GetResponseClassIndexOfService(serviceIndex) == ResponseClass)
    {
      (*ServiceIndex) = serviceIndex;
      retVal = E_OK;
    }
  }

  return retVal;
}

/**********************************************************************************************************************
 * vSwUpdM_GridRpc_GetResponseTarget
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL FUNC(vRpcProxy_CTargetsIterType, VSWUPDM_CODE) vSwUpdM_GridRpc_GetResponseTarget(
  vSwUpdM_NodeIterType RequestOrigin,
  vSwUpdM_GridSrvc_ServiceIdxType ServiceIndex)
{
  vRpcProxy_CTargetsIterType target;

  switch (vSwUpdM_GridSrvc_GetChannelOfService(ServiceIndex))
  {
    default:
    /* case  VSWUPDM_GRIDCHANNEL_CHANNELIDX_MAIN: */
    /* case  VSWUPDM_GRIDCHANNEL_CHANNELIDX_LEGACY: */
    {
     target = vSwUpdM_GetDestinationMainOfNode(RequestOrigin);
     break;
    }
    case VSWUPDM_GRIDCHANNEL_CHANNELIDX_MAINTENANCE:
    {
     target = vSwUpdM_GetDestinationMaintenanceOfNode(RequestOrigin);
     break;
    }
    case VSWUPDM_GRIDCHANNEL_CHANNELIDX_SUSPEND:
    {
     target = vSwUpdM_GetDestinationSuspendOfNode(RequestOrigin);
     break;
    }
    case VSWUPDM_GRIDCHANNEL_CHANNELIDX_BOOKKEEPER:
    {
     target = vSwUpdM_GetDestinationBookkeeperOfNode(RequestOrigin);
     break;
    }
  }

  return target;
  /* PRQA S 6030, 6050 1 */ /* MD_MSR_STCAL, MD_MSR_STCYC */
}/* vSwUpdM_GridRpc_GetResponseTarget */

/**********************************************************************************************************************
 * vSwUpdM_GridRpc_GetServiceByRpcProxyRequestService
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GridRpc_GetServiceByRpcProxyRequestService(
  vSwUpdM_RpcProxyServiceIdType RpcProxyRequestService,
  P2VAR(vSwUpdM_GridSrvc_ServiceIdxType, AUTOMATIC, VSWUPDM_APPL_VAR) ServiceIdx)
{
  Std_ReturnType result = E_NOT_OK;
  vSwUpdM_GridSrvc_ServiceIdxType serviceIndex;

  /*#10 Get RemoteServiceId by vSwUpdM ServiceId. */
  for (serviceIndex = VSWUPDM_GRIDSRVC_SERVICEIDX_ZERO; serviceIndex < VSWUPDM_GRIDSRVC_SERVICEIDX_COUNT; serviceIndex++) /* PRQA S 4527 1 */ /* MD_vSwUpdM_Rule10.1_4527_EnumLoop */
  {
    if (vSwUpdM_GridRpc_GetRpcProxyRequestOfService(serviceIndex) == RpcProxyRequestService)
    {
      (*ServiceIdx) = serviceIndex;
      result = E_OK;
      break;
    }
  }

  return result;
} /* vSwUpdM_GridRpc_GetServiceByRpcProxyRequestService */

/**********************************************************************************************************************
 * vSwUpdM_GridRpc_GetServiceStateFromRpcProxyError
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL FUNC(vSwUpdM_GridChannel_ServiceStateType, VSWUPDM_CODE) vSwUpdM_GridRpc_GetServiceStateFromRpcProxyError(
  TxService_StatusType Result)
{
  vSwUpdM_GridChannel_ServiceStateType serviceState = VSWUPDM_GRIDCHANNEL_SERVICESTATE_UNUSED; /* PRQA S 2981 */ /* MD_MSR_RetVal */

  switch (Result)
  {
    case VRPCPROXY_E_POSITIVE_ACK:
    {
      serviceState = VSWUPDM_GRIDCHANNEL_SERVICESTATE_ACK;
      break;
    }
    case VRPCPROXY_E_LOCAL_TX_TP_ERROR:
    {
      serviceState = VSWUPDM_GRIDCHANNEL_SERVICESTATE_TX_TP_ERROR;
      break;
    }
    case VRPCPROXY_E_NEGATIVE_ACK:
    {
      serviceState = VSWUPDM_GRIDCHANNEL_SERVICESTATE_NACK;
      break;
    }
    case VRPCPROXY_E_ACK_TIMEOUT:
    {
      serviceState = VSWUPDM_GRIDCHANNEL_SERVICESTATE_ACK_TIMEOUT;
      break;
    }
      case VRPCPROXY_E_RESPONSE_TIMEOUT:
    {
      serviceState = VSWUPDM_GRIDCHANNEL_SERVICESTATE_RESPONSE_TIMEOUT;
      break;
    }
    default:
    {
      vSwUpdM_DevError_AssertFail(VSWUPDM_DEVERROR_ASSERT_3); /* PRQA S 4304, 2996 */ /* MD_MSR_AutosarBoolean, MD_vSwUpdM_Rule14.3_2991_2992_2995_2996_Rule2.2_AlwaysTrueFalse */
      break;
    }
  }

  return serviceState;
} /* vSwUpdM_GridRpc_GetServiceStateFromRpcProxyError */

/**********************************************************************************************************************
 * vSwUpdM_GridRpc_GetLegacyErrorCodeFromRpcProxyError
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GridRpc_GetLegacyErrorCodeFromRpcProxyError(
  TxService_StatusType Result)
{
  Std_ReturnType errorCode;

  switch (Result)
  {
    case VRPCPROXY_E_POSITIVE_ACK:
    {
      errorCode = E_OK;
      break;
    }
    case VRPCPROXY_E_LOCAL_TX_TP_ERROR:
    {
      errorCode = VSWUPDM_E_REMOTE_LOCAL_TX_TP_ERROR;
      break;
    }
    case VRPCPROXY_E_NEGATIVE_ACK:
    {
      errorCode = VSWUPDM_E_REMOTE_NEGATIVE_ACK;
      break;
    }
    case VRPCPROXY_E_ACK_TIMEOUT:
    {
      errorCode = VSWUPDM_E_REMOTE_ACK_TIMEOUT;
      break;
    }
    case VRPCPROXY_E_RESPONSE_TIMEOUT:
    {
      errorCode = VSWUPDM_E_REMOTE_RESPONSE_TIMEOUT;
      break;
    }
    default:
    {
      errorCode = E_NOT_OK;
      break;
    }
  }

  return errorCode;
}/* vSwUpdM_GridRpc_GetLegacyErrorCodeFromRpcProxyError */

/**********************************************************************************************************************
 * vSwUpdM_GridRpc_LegacyServiceErrorHandling
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
 *
 *
 *
 */
VSWUPDM_LOCAL FUNC(void, VSWUPDM_CODE) vSwUpdM_GridRpc_LegacyServiceErrorHandling(
  uint8 TargetId,
  vSwUpdM_GridSrvc_ServiceIdxType ServiceIndex,
  TxService_StatusType Result)
{
  Std_ReturnType              errorCode;

  /* #10 Map vRpcProxy error codes to vSwUpdM error codes. */
  errorCode = vSwUpdM_GridRpc_GetLegacyErrorCodeFromRpcProxyError(Result);

  /* #20 In case of any failure: */
  if (errorCode != E_OK)
  {
    uint8_least index = 0u;
    /* #21 Check for appropriate reaction: */
    do
    {
      if (vSwUpdM_RemoteServiceDefinitions[index].RemoteServiceIndex == ServiceIndex)
      {
        break;
      }
      index++;
    } while (vSwUpdM_RemoteServiceDefinitions[index].RemoteServiceIndex != VSWUPDM_GRIDSRVC_SERVICEIDX_UNDEFINED);

    if (vSwUpdM_RemoteServiceDefinitions[index].RemoteServiceIndex != VSWUPDM_GRIDSRVC_SERVICEIDX_UNDEFINED)
    {
      /* #30 Select error handling for given service. */
      switch (vSwUpdM_RemoteServiceDefinitions[index].TxErrorHandlerType)
      {
        default:
        /* case VSWUPDM_REMOTE_TX_ERROR_HANDLER_ABORT_WAIT:   */
        /* case VSWUPDM_REMOTE_TX_ERROR_HANDLER_NONE:         */
        /*   */
        /* #31 No error handler:
          *      Do nothing. */
        {
          break;
        }
        case VSWUPDM_REMOTE_TX_ERROR_HANDLER_PROC_STREAM:
        case VSWUPDM_REMOTE_TX_ERROR_HANDLER_CONFIRMATION:
        /* #32 Inject negative response. */
        {
          Std_ReturnType result;
          vSwUpdM_NodeIterType nodeIndex = VSWUPDM_INVALID_NODE;
          result = vSwUpdM_GridNode_GetNodeIndexFromRpcProxyTargetAndChannel((vSwUpdM_RpcProxySourceIdType) TargetId, VSWUPDM_GRIDCHANNEL_CHANNELIDX_MAIN, &nodeIndex);

          if (result == E_OK)
          {
            vSwUpdM_RemoteProcessResponse(nodeIndex, ServiceIndex, errorCode);
          }
          break;
        }

        case VSWUPDM_REMOTE_TX_ERROR_HANDLER_STREAM:
        /* #33 Stream error handler:
          *      Find currently active stream and abort it. */
        {
          vSwUpdM_RemoteStreamAbort(ServiceIndex);
          break;
        }
      }
    }
  }
}
/* vSwUpdM_GridRpc_LegacyServiceErrorHandling */

/*******************************
 * vRpcProxy Redirect Functions
 ******************************/

/**********************************************************************************************************************
 * vSwUpdM_GridRpc_ProxyMaintenanceService
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GridRpc_ProxyMaintenanceService(
  vSwUpdM_NodeGroupIterType Destination,
  vSwUpdM_GridSrvc_ServiceClassBasePtrType Parameter) /* PRQA S 3673 */ /* MD_vSwUpdM_Rule8.13_3673_PointerToConstParameter */
{
  Std_ReturnType retVal;
  vRpcProxy_TargetGroupsIterType targetGroup = vSwUpdM_GridRpc_GetRpcProxyTargetGroup(VSWUPDM_GRIDCHANNEL_CHANNELIDX_MAINTENANCE, Destination);

  /* PRQA S 0310 4 */ /* MD_vSwUpdM_Rule11.3_0310_ServiceParameterCast */
  retVal = vRpcProxy_vSwUpdM_GridRpc_MaintenanceService_TargetGroup(
    targetGroup,
    (uint8) ((vSwUpdM_GridSrvc_ServiceClassMaintenancePtrType)Parameter)->GenericBase.Base.ServiceState,
    (uint8) ((vSwUpdM_GridSrvc_ServiceClassMaintenancePtrType)Parameter)->GenericBase.ServiceIndex);

  return retVal;
} /* vSwUpdM_GridRpc_ProxyMaintenanceService */

/**********************************************************************************************************************
 * vSwUpdM_GridRpc_ProxySuspendService
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GridRpc_ProxySuspendService(
  vSwUpdM_NodeGroupIterType Destination,
  vSwUpdM_GridSrvc_ServiceClassBasePtrType Parameter) /* PRQA S 3673 */ /* MD_vSwUpdM_Rule8.13_3673_PointerToConstParameter */
{
  Std_ReturnType retVal;
  vRpcProxy_TargetGroupsIterType targetGroup = vSwUpdM_GridRpc_GetRpcProxyTargetGroup(VSWUPDM_GRIDCHANNEL_CHANNELIDX_SUSPEND, Destination);

  /* PRQA S 0310 3 */ /* MD_vSwUpdM_Rule11.3_0310_ServiceParameterCast */
  retVal = vRpcProxy_vSwUpdM_GridRpc_SuspendService_TargetGroup(
    targetGroup,
    (uint8) ((vSwUpdM_GridSrvc_ServiceClassSuspendPtrType)Parameter)->ServiceIndex);

  return retVal;
} /* vSwUpdM_GridRpc_ProxySuspendService */

/**********************************************************************************************************************
 * vSwUpdM_GridRpc_ProxyGenericService
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GridRpc_ProxyGenericService(
  vSwUpdM_NodeGroupIterType Destination,
  vSwUpdM_GridSrvc_ServiceClassBasePtrType Parameter) /* PRQA S 3673 */ /* MD_vSwUpdM_Rule8.13_3673_PointerToConstParameter */
{
  Std_ReturnType retVal;
  vRpcProxy_TargetGroupsIterType targetGroup = vSwUpdM_GridRpc_GetRpcProxyTargetGroup(VSWUPDM_GRIDCHANNEL_CHANNELIDX_MAIN, Destination);

  /* PRQA S 0310 5 */ /* MD_vSwUpdM_Rule11.3_0310_ServiceParameterCast */
  retVal = vRpcProxy_vSwUpdM_GridRpc_GenericService_TargetGroup(
    targetGroup,
    (uint8) ((vSwUpdM_GridSrvc_ServiceClassGenericPtrType)Parameter)->GenericBase.Base.ServiceState,
    (uint8) ((vSwUpdM_GridSrvc_ServiceClassGenericPtrType)Parameter)->GenericBase.ServiceIndex);

  return retVal;
} /* vSwUpdM_GridRpc_ProxyGenericService */

/**********************************************************************************************************************
 * vSwUpdM_GridRpc_ProxyPartitionService
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GridRpc_ProxyPartitionService(
  vSwUpdM_NodeGroupIterType Destination,
  vSwUpdM_GridSrvc_ServiceClassBasePtrType Parameter) /* PRQA S 3673 */ /* MD_vSwUpdM_Rule8.13_3673_PointerToConstParameter */
{
  Std_ReturnType retVal;
  vRpcProxy_TargetGroupsIterType targetGroup = vSwUpdM_GridRpc_GetRpcProxyTargetGroup(VSWUPDM_GRIDCHANNEL_CHANNELIDX_MAIN, Destination);

  /* PRQA S 0310 5 */ /* MD_vSwUpdM_Rule11.3_0310_ServiceParameterCast */
  retVal = vRpcProxy_vSwUpdM_GridRpc_PartitionService_TargetGroup(
    targetGroup,
    (uint8)((vSwUpdM_GridSrvc_ServiceClassModulePtrType)Parameter)->GenericBase.Base.ServiceState,
    (uint8)((vSwUpdM_GridSrvc_ServiceClassModulePtrType)Parameter)->GenericBase.ServiceIndex,
    (uint8) ((vSwUpdM_GridSrvc_ServiceClassPartitionPtrType)Parameter)->PartitionState);

  return retVal;
} /* vSwUpdM_GridRpc_ProxyPartitionService */

/**********************************************************************************************************************
 * vSwUpdM_GridRpc_ProxyModuleService
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GridRpc_ProxyModuleService(
  vSwUpdM_NodeGroupIterType Destination,
  vSwUpdM_GridSrvc_ServiceClassBasePtrType Parameter) /* PRQA S 3673 */ /* MD_vSwUpdM_Rule8.13_3673_PointerToConstParameter */
{
  Std_ReturnType retVal;
  vRpcProxy_TargetGroupsIterType targetGroup = vSwUpdM_GridRpc_GetRpcProxyTargetGroup(VSWUPDM_GRIDCHANNEL_CHANNELIDX_MAIN, Destination);

  /* PRQA S 0310 5 */ /* MD_vSwUpdM_Rule11.3_0310_ServiceParameterCast */
  retVal = vRpcProxy_vSwUpdM_GridRpc_ModuleService_TargetGroup(
    targetGroup,
    (uint8)((vSwUpdM_GridSrvc_ServiceClassModulePtrType)Parameter)->GenericBase.Base.ServiceState,
    (uint8)((vSwUpdM_GridSrvc_ServiceClassModulePtrType)Parameter)->GenericBase.ServiceIndex,
    vSwUpdM_GetModuleHandleOfModule(((vSwUpdM_GridSrvc_ServiceClassModulePtrType)Parameter)->ModuleId));

  return retVal;
} /* vSwUpdM_GridRpc_ProxyModuleService */

/**********************************************************************************************************************
 * vSwUpdM_GridRpc_ProxyRegionService
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GridRpc_ProxyRegionService(
  vSwUpdM_NodeGroupIterType Destination,
  vSwUpdM_GridSrvc_ServiceClassBasePtrType Parameter) /* PRQA S 3673 */ /* MD_vSwUpdM_Rule8.13_3673_PointerToConstParameter */
{
  Std_ReturnType retVal;
  vRpcProxy_TargetGroupsIterType targetGroup = vSwUpdM_GridRpc_GetRpcProxyTargetGroup(VSWUPDM_GRIDCHANNEL_CHANNELIDX_MAIN, Destination);

  /* PRQA S 0310 5 */ /* MD_vSwUpdM_Rule11.3_0310_ServiceParameterCast */
  retVal = vRpcProxy_vSwUpdM_GridRpc_RegionService_TargetGroup(
    targetGroup,
    (uint8)((vSwUpdM_GridSrvc_ServiceClassRegionPtrType)Parameter)->GenericBase.Base.ServiceState,
    (uint8)((vSwUpdM_GridSrvc_ServiceClassRegionPtrType)Parameter)->GenericBase.ServiceIndex,
    vSwUpdM_GetRegionHandleOfRegion(((vSwUpdM_GridSrvc_ServiceClassRegionPtrType)Parameter)->RegionId));

  return retVal;
} /* vSwUpdM_GridRpc_ProxyRegionService */

/**********************************************************************************************************************
 * vSwUpdM_GridRpc_ProxySegmentService
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GridRpc_ProxySegmentService(
  vSwUpdM_NodeGroupIterType Destination,
  vSwUpdM_GridSrvc_ServiceClassBasePtrType Parameter) /* PRQA S 3673 */ /* MD_vSwUpdM_Rule8.13_3673_PointerToConstParameter */
{
  Std_ReturnType retVal;
  vRpcProxy_TargetGroupsIterType targetGroup = vSwUpdM_GridRpc_GetRpcProxyTargetGroup(VSWUPDM_GRIDCHANNEL_CHANNELIDX_MAIN, Destination);

  /* PRQA S 0310 5 */ /* MD_vSwUpdM_Rule11.3_0310_ServiceParameterCast */
  retVal = vRpcProxy_vSwUpdM_GridRpc_SegmentService_TargetGroup(
    targetGroup,
    (uint8)((vSwUpdM_GridSrvc_ServiceClassSegmentPtrType)Parameter)->GenericBase.Base.ServiceState,
    (uint8)((vSwUpdM_GridSrvc_ServiceClassSegmentPtrType)Parameter)->GenericBase.ServiceIndex,
    vSwUpdM_GetVarSegments(((vSwUpdM_GridSrvc_ServiceClassSegmentPtrType)Parameter)->SegmentId.DynamicSegmentId).DynamicAttributesOfVarSegment.StartAddress);

  return retVal;
} /* vSwUpdM_GridRpc_ProxySegmentService */

/**********************************************************************************************************************
 * vSwUpdM_GridRpc_ProxyProcessModuleService
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GridRpc_ProxyProcessModuleService(
  vSwUpdM_NodeGroupIterType Destination,
  vSwUpdM_GridSrvc_ServiceClassBasePtrType Parameter) /* PRQA S 3673 */ /* MD_vSwUpdM_Rule8.13_3673_PointerToConstParameter */
{
  Std_ReturnType                retVal;
  vSwUpdM_RemoteProcessInfoType processInfo;

  /* PRQA S 0310 1 */ /* MD_vSwUpdM_Rule11.3_0310_ServiceParameterCast */
  vSwUpdM_GridSrvc_ServiceClassProcessModuleConstPtrType parameter = (vSwUpdM_GridSrvc_ServiceClassProcessModuleConstPtrType)Parameter;
  vRpcProxy_TargetGroupsIterType targetGroup = vSwUpdM_GridRpc_GetRpcProxyTargetGroup(VSWUPDM_GRIDCHANNEL_CHANNELIDX_MAIN, Destination);

  processInfo.InputCount  = parameter->ProcessInfo.InputCount;
  processInfo.OutputCount = parameter->ProcessInfo.OutputCount;
  processInfo.Operation   = parameter->ProcessInfo.Operation;
  processInfo.Handle      = vSwUpdM_GetProcessHandleOfDataProcesses(parameter->ProcessId);

  retVal = vRpcProxy_vSwUpdM_GridRpc_ProcessModuleService_TargetGroup(
    targetGroup,
    (uint8)parameter->GenericBase.Base.ServiceState,
    (uint8)parameter->GenericBase.ServiceIndex,
     vSwUpdM_GetModuleHandleOfModule(parameter->ModuleId),
    &processInfo);

  return retVal;
} /* vSwUpdM_GridRpc_ProxyProcessModuleService */

/**********************************************************************************************************************
 * vSwUpdM_GridRpc_ProxyAddSegmentService
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GridRpc_ProxyAddSegmentService(
  vSwUpdM_NodeGroupIterType Destination,
  vSwUpdM_GridSrvc_ServiceClassBasePtrType Parameter) /* PRQA S 3673 */ /* MD_vSwUpdM_Rule8.13_3673_PointerToConstParameter */
{
  Std_ReturnType retVal;
  vRpcProxy_TargetGroupsIterType targetGroup = vSwUpdM_GridRpc_GetRpcProxyTargetGroup(VSWUPDM_GRIDCHANNEL_CHANNELIDX_MAIN, Destination);

  /* PRQA S 0310 4 */ /* MD_vSwUpdM_Rule11.3_0310_ServiceParameterCast */
  retVal = vRpcProxy_vSwUpdM_GridRpc_AddSegment_TargetGroup(/* PRQA S 0310 */ /* MD_vSwUpdM_Rule11.3_0310_ServiceParameterCast */
   targetGroup,
    (uint8) ((vSwUpdM_GridSrvc_ServiceClassSegmentInfoPtrType )Parameter)->Base.ServiceState,
   &((vSwUpdM_GridSrvc_ServiceClassSegmentInfoPtrType )Parameter)->SegmentInfo);

  return retVal;
} /* vSwUpdM_GridRpc_ProxyAddSegmentService */

/**********************************************************************************************************************
 * vSwUpdM_GridRpc_ProxyStartStreamService
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GridRpc_ProxyStartStreamService(
  vSwUpdM_NodeGroupIterType Destination,
  vSwUpdM_GridSrvc_ServiceClassBasePtrType Parameter) /* PRQA S 3673 */ /* MD_vSwUpdM_Rule8.13_3673_PointerToConstParameter */
{
  Std_ReturnType retVal;
  vRpcProxy_TargetGroupsIterType targetGroup = vSwUpdM_GridRpc_GetRpcProxyTargetGroup(VSWUPDM_GRIDCHANNEL_CHANNELIDX_MAIN, Destination);

  /* PRQA S 0310 4 */ /* MD_vSwUpdM_Rule11.3_0310_ServiceParameterCast */
  retVal = vRpcProxy_vSwUpdM_GridRpc_StartStream_TargetGroup(/* PRQA S 0310 */ /* MD_vSwUpdM_Rule11.3_0310_ServiceParameterCast */
    targetGroup,
    (uint8) ((vSwUpdM_GridSrvc_ServiceClassStreamInfoPtrType)Parameter)->Base.ServiceState,
    &((vSwUpdM_GridSrvc_ServiceClassStreamInfoPtrType)Parameter)->StreamInfo);

  return retVal;
} /* vSwUpdM_GridRpc_ProxyStartStreamService */

/**********************************************************************************************************************
 * vSwUpdM_GridRpc_ProxyBkExecCommandService
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GridRpc_ProxyBkExecCommandService(
  vSwUpdM_NodeGroupIterType Destination,
  vSwUpdM_GridSrvc_ServiceClassBasePtrType Parameter) /* PRQA S 3673 */ /* MD_vSwUpdM_Rule8.13_3673_PointerToConstParameter */
{
  Std_ReturnType retVal;

  /*!
   * Internal comment removed.
 *
 *
   */
  if (vSwUpdM_IsWithLocalNodeOfNodeGroup(Destination))
  {
    retVal = vSwUpdM_GridRpc_LocalBkExecCommandService(Destination, Parameter);
  }
  else
  {
    vRpcProxy_TargetGroupsIterType targetGroup = vSwUpdM_GridRpc_GetRpcProxyTargetGroup(VSWUPDM_GRIDCHANNEL_CHANNELIDX_BOOKKEEPER, Destination);

    /* PRQA S 0310 4 */ /* MD_vSwUpdM_Rule11.3_0310_ServiceParameterCast */
    retVal = vRpcProxy_vSwUpdM_GridRpc_BkExecCommand_TargetGroup(/* PRQA S 0310 */ /* MD_vSwUpdM_Rule11.3_0310_ServiceParameterCast */
      targetGroup,
      (uint8)((vSwUpdM_GridSrvc_ServiceClassBkExecCommandPtrType)Parameter)->Command);
  }
  return retVal;
} /* vSwUpdM_GridRpc_ProxyBkExecCommandService */

/**********************************************************************************************************************
 * vSwUpdM_GridRpc_ProxyBkGetGenericParameterService
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GridRpc_ProxyBkGetGenericParameterService(
  vSwUpdM_NodeGroupIterType Destination,
  vSwUpdM_GridSrvc_ServiceClassBasePtrType Parameter) /* PRQA S 3673 */ /* MD_vSwUpdM_Rule8.13_3673_PointerToConstParameter */
{
  Std_ReturnType retVal;
  vSwUpdM_BkPersist_EntityHandleType HandleEntities;

  /*!
   * Internal comment removed.
 *
 *
   */
  if (vSwUpdM_IsWithLocalNodeOfNodeGroup(Destination))
  {
    retVal = vSwUpdM_GridRpc_LocalBkGetGenericParameterService(Destination, Parameter);
  }
  else
  {
    vRpcProxy_TargetGroupsIterType targetGroup = vSwUpdM_GridRpc_GetRpcProxyTargetGroup(VSWUPDM_GRIDCHANNEL_CHANNELIDX_BOOKKEEPER, Destination);
    /* PRQA S 0310 1 */ /* MD_vSwUpdM_Rule11.3_0310_ServiceParameterCast */
    vSwUpdM_Bookkeeper_GetHandlesByIds(((vSwUpdM_GridSrvc_ServiceClassBkGetGenericParameterPtrType)Parameter)->Base.Entities, &HandleEntities);

    /* PRQA S 0310 4 */ /* MD_vSwUpdM_Rule11.3_0310_ServiceParameterCast */
    retVal = vRpcProxy_vSwUpdM_GridRpc_BkGetGenericParameter_TargetGroup(/* PRQA S 0310 */ /* MD_vSwUpdM_Rule11.3_0310_ServiceParameterCast */
      targetGroup,
      &HandleEntities,
      (uint8)((vSwUpdM_GridSrvc_ServiceClassBkGetGenericParameterPtrType)Parameter)->Base.ParamType);
  }

  return retVal;
} /* vSwUpdM_GridRpc_ProxyBkGetGenericParameterService */

/**********************************************************************************************************************
 * vSwUpdM_GridRpc_ProxyBkGetSegmentAttributesService
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GridRpc_ProxyBkGetSegmentAttributesService(
  vSwUpdM_NodeGroupIterType Destination,
  vSwUpdM_GridSrvc_ServiceClassBasePtrType Parameter) /* PRQA S 3673 */ /* MD_vSwUpdM_Rule8.13_3673_PointerToConstParameter */
{
  Std_ReturnType retVal;
  vSwUpdM_BkPersist_EntityHandleType HandleEntities;

  /*!
   * Internal comment removed.
 *
 *
   */
  if (vSwUpdM_IsWithLocalNodeOfNodeGroup(Destination))
  {
    retVal = vSwUpdM_GridRpc_LocalBkGetSegmentAttributesService(Destination, Parameter);
  }
  else
  {
    vRpcProxy_TargetGroupsIterType targetGroup = vSwUpdM_GridRpc_GetRpcProxyTargetGroup(VSWUPDM_GRIDCHANNEL_CHANNELIDX_BOOKKEEPER, Destination);
    /* PRQA S 0310 1 */ /* MD_vSwUpdM_Rule11.3_0310_ServiceParameterCast */
    vSwUpdM_Bookkeeper_GetHandlesByIds(((vSwUpdM_GridSrvc_ServiceClassBkGetGenericParameterPtrType)Parameter)->Base.Entities, &HandleEntities);

    /* PRQA S 0310 4 */ /* MD_vSwUpdM_Rule11.3_0310_ServiceParameterCast */
    retVal = vRpcProxy_vSwUpdM_GridRpc_BkGetSegmentAttributes_TargetGroup(/* PRQA S 0310 */ /* MD_vSwUpdM_Rule11.3_0310_ServiceParameterCast */
      targetGroup,
      &HandleEntities);
  }

  return retVal;
} /* vSwUpdM_GridRpc_ProxyBkGetSegmentAttributesService */

/**********************************************************************************************************************
 * vSwUpdM_GridRpc_ProxyBkGetResumeInfoService
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GridRpc_ProxyBkGetResumeInfoService(
  vSwUpdM_NodeGroupIterType Destination,
  vSwUpdM_GridSrvc_ServiceClassBasePtrType Parameter) /* PRQA S 3673 */ /* MD_vSwUpdM_Rule8.13_3673_PointerToConstParameter */
{
  Std_ReturnType retVal;

  /*!
   * Internal comment removed.
 *
 *
   */
  if (vSwUpdM_IsWithLocalNodeOfNodeGroup(Destination))
  {
    retVal = vSwUpdM_GridRpc_LocalBkGetResumeInfoService(Destination, Parameter);
  }
  else
  {
    vRpcProxy_TargetGroupsIterType targetGroup = vSwUpdM_GridRpc_GetRpcProxyTargetGroup(VSWUPDM_GRIDCHANNEL_CHANNELIDX_BOOKKEEPER, Destination);

    /* PRQA S 0310 4 */ /* MD_vSwUpdM_Rule11.3_0310_ServiceParameterCast */
    retVal = vRpcProxy_vSwUpdM_GridRpc_BkGetResumeInfo_TargetGroup(/* PRQA S 0310 */ /* MD_vSwUpdM_Rule11.3_0310_ServiceParameterCast */
      targetGroup);
  }
  return retVal;
} /* vSwUpdM_GridRpc_ProxyBkGetResumeInfoService */

/**********************************************************************************************************************
 * vSwUpdM_GridRpc_ProxyBkSetGenericParameterService
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GridRpc_ProxyBkSetGenericParameterService(
  vSwUpdM_NodeGroupIterType Destination,
  vSwUpdM_GridSrvc_ServiceClassBasePtrType Parameter) /* PRQA S 3673 */ /* MD_vSwUpdM_Rule8.13_3673_PointerToConstParameter */
{
  Std_ReturnType retVal;
  vSwUpdM_BkPersist_EntityHandleType HandleEntities;

  /*!
   * Internal comment removed.
 *
 *
   */
  if (vSwUpdM_IsWithLocalNodeOfNodeGroup(Destination))
  {
    retVal = vSwUpdM_GridRpc_LocalBkSetGenericParameterService(Destination, Parameter);
  }
  else
  {
    vRpcProxy_TargetGroupsIterType targetGroup = vSwUpdM_GridRpc_GetRpcProxyTargetGroup(VSWUPDM_GRIDCHANNEL_CHANNELIDX_BOOKKEEPER, Destination);
    /* PRQA S 0310 1 */ /* MD_vSwUpdM_Rule11.3_0310_ServiceParameterCast */
    vSwUpdM_Bookkeeper_GetHandlesByIds(((vSwUpdM_GridSrvc_ServiceClassBkGetGenericParameterPtrType)Parameter)->Base.Entities, &HandleEntities);

    /* PRQA S 0310 6 */ /* MD_vSwUpdM_Rule11.3_0310_ServiceParameterCast */
    retVal = vRpcProxy_vSwUpdM_GridRpc_BkSetGenericParameter_TargetGroup(
      targetGroup,
      &HandleEntities,
      (uint8)((vSwUpdM_GridSrvc_ServiceClassBkSetGenericParameterPtrType)Parameter)->Base.ParamType,
      ((vSwUpdM_GridSrvc_ServiceClassBkSetGenericParameterPtrType)Parameter)->GenericValue,
      ((vSwUpdM_GridSrvc_ServiceClassBkSetGenericParameterPtrType)Parameter)->SyncFlag);
  }

  return retVal;
} /* vSwUpdM_GridRpc_ProxyBkSetGenericParameterService */

/**********************************************************************************************************************
 * vSwUpdM_GridRpc_ProxyBkSetSegmentAttributesService
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GridRpc_ProxyBkSetSegmentAttributesService(
  vSwUpdM_NodeGroupIterType Destination,
  vSwUpdM_GridSrvc_ServiceClassBasePtrType Parameter) /* PRQA S 3673 */ /* MD_vSwUpdM_Rule8.13_3673_PointerToConstParameter */
{
  Std_ReturnType retVal;
  vSwUpdM_BkPersist_EntityHandleType HandleEntities;

  /*!
   * Internal comment removed.
 *
 *
   */
  if (vSwUpdM_IsWithLocalNodeOfNodeGroup(Destination))
  {
    retVal = vSwUpdM_GridRpc_LocalBkSetSegmentAttributesService(Destination, Parameter);
  }
  else
  {
    vRpcProxy_TargetGroupsIterType targetGroup = vSwUpdM_GridRpc_GetRpcProxyTargetGroup(VSWUPDM_GRIDCHANNEL_CHANNELIDX_BOOKKEEPER, Destination);
    /* PRQA S 0310 1 */ /* MD_vSwUpdM_Rule11.3_0310_ServiceParameterCast */
    vSwUpdM_Bookkeeper_GetHandlesByIds(((vSwUpdM_GridSrvc_ServiceClassBkGetGenericParameterPtrType)Parameter)->Base.Entities, &HandleEntities);

    /* PRQA S 0310 5 */ /* MD_vSwUpdM_Rule11.3_0310_ServiceParameterCast */
    retVal = vRpcProxy_vSwUpdM_GridRpc_BkSetSegmentAttributes_TargetGroup(
      targetGroup,
      &HandleEntities,
      ((vSwUpdM_GridSrvc_ServiceClassBkSetSegmentAttributesPtrType)Parameter)->SegmentAttributes,
      ((vSwUpdM_GridSrvc_ServiceClassBkSetSegmentAttributesPtrType)Parameter)->SyncFlag);
  }

  return retVal;
} /* vSwUpdM_GridRpc_ProxyBkSetSegmentAttributesService */

/**********************************************************************************************************************
 * vSwUpdM_GridRpc_ProxyBkSetResumeInfoService
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GridRpc_ProxyBkSetResumeInfoService(
  vSwUpdM_NodeGroupIterType Destination,
  vSwUpdM_GridSrvc_ServiceClassBasePtrType Parameter) /* PRQA S 3673 */ /* MD_vSwUpdM_Rule8.13_3673_PointerToConstParameter */
{
  Std_ReturnType retVal;

  /*!
   * Internal comment removed.
 *
 *
   */
  if (vSwUpdM_IsWithLocalNodeOfNodeGroup(Destination))
  {
    retVal = vSwUpdM_GridRpc_LocalBkSetResumeInfoService(Destination, Parameter);
  }
  else
  {
    vRpcProxy_TargetGroupsIterType targetGroup = vSwUpdM_GridRpc_GetRpcProxyTargetGroup(VSWUPDM_GRIDCHANNEL_CHANNELIDX_BOOKKEEPER, Destination);

    /* PRQA S 0310 4 */ /* MD_vSwUpdM_Rule11.3_0310_ServiceParameterCast */
    retVal = vRpcProxy_vSwUpdM_GridRpc_BkSetResumeInfo_TargetGroup(
      targetGroup,
      &((vSwUpdM_GridSrvc_ServiceClassBkSetResumeInfoPtrType)Parameter)->ResumeInfo,
      ((vSwUpdM_GridSrvc_ServiceClassBkSetResumeInfoPtrType)Parameter)->SyncFlag);
  }

  return retVal;
} /* vSwUpdM_GridRpc_ProxyBkSetResumeInfoService */

/**********************************************************************************************************************
 * vSwUpdM_GridRpc_ProxyMainConfirmation
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GridRpc_ProxyMainConfirmation(
  vSwUpdM_NodeIterType RequestOrigin,
  vSwUpdM_GridRpc_ServiceExecutionStateType ServiceExecutionState,
  vSwUpdM_GridRpc_ComplexResponseClassBasePtrType ResponseClass) /* PRQA S 3673 */ /* MD_vSwUpdM_Rule8.13_3673_PointerToConstParameter */
{
  Std_ReturnType retVal = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vRpcProxy_CTargetsIterType target;

  vSwUpdM_DevError_Assert(ResponseClass->ComplexResponseClassType == VSWUPDM_GRIDRPC_COMPLEXREPONSECLASS_SIMPLE, VSWUPDM_DEVERROR_ASSERT_14); /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */

  /* #10 Select RpcProxyTarget by Channel. */
  target = vSwUpdM_GridRpc_GetResponseTarget(RequestOrigin, ResponseClass->RequestServiceIdx);

  /* #20 Trigger Confirmation. */
  retVal = vRpcProxy_vSwUpdM_GridRpc_MainConfirmation_Target(target, (uint16)vSwUpdM_GridRpc_GetRpcProxyRequestOfService(ResponseClass->RequestServiceIdx), vSwUpdM_GridRpc_GetRpcProxyServiceExecutionState(ServiceExecutionState), (uint8)ResponseClass->RequestServiceIdx, ResponseClass->Result);

  return retVal;
} /* vSwUpdM_GridRpc_ProxyMainConfirmation */

/**********************************************************************************************************************
 * vSwUpdM_GridRpc_ProxyMaintenanceConfirmation
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GridRpc_ProxyMaintenanceConfirmation(
  vSwUpdM_NodeIterType RequestOrigin,
  vSwUpdM_GridRpc_ServiceExecutionStateType ServiceExecutionState,
  vSwUpdM_GridRpc_ComplexResponseClassBasePtrType ResponseClass) /* PRQA S 3673 */ /* MD_vSwUpdM_Rule8.13_3673_PointerToConstParameter */
{
  Std_ReturnType retVal = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vRpcProxy_CTargetsIterType target;

  vSwUpdM_DevError_Assert(ResponseClass->ComplexResponseClassType == VSWUPDM_GRIDRPC_COMPLEXREPONSECLASS_SIMPLE, VSWUPDM_DEVERROR_ASSERT_15); /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */

  /* #10 Select RpcProxyTarget by Channel. */
  target = vSwUpdM_GridRpc_GetResponseTarget(RequestOrigin, ResponseClass->RequestServiceIdx);

  /* #20 Trigger Confirmation. */
  retVal = vRpcProxy_vSwUpdM_GridRpc_MaintenanceConfirmation_Target(target, (uint16) vSwUpdM_GridRpc_GetRpcProxyRequestOfService(ResponseClass->RequestServiceIdx), vSwUpdM_GridRpc_GetRpcProxyServiceExecutionState(ServiceExecutionState), (uint8)ResponseClass->RequestServiceIdx, ResponseClass->Result);

  return retVal;
} /* vSwUpdM_GridRpc_ProxyMaintenanceConfirmation */

/**********************************************************************************************************************
 * vSwUpdM_GridRpc_ProxySuspendConfirmation
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GridRpc_ProxySuspendConfirmation(
  vSwUpdM_NodeIterType RequestOrigin,
  vSwUpdM_GridRpc_ServiceExecutionStateType ServiceExecutionState,
  vSwUpdM_GridRpc_ComplexResponseClassBasePtrType ResponseClass) /* PRQA S 3673 */ /* MD_vSwUpdM_Rule8.13_3673_PointerToConstParameter */
{
  Std_ReturnType retVal = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vRpcProxy_CTargetsIterType target;

  vSwUpdM_DevError_Assert(ResponseClass->ComplexResponseClassType == VSWUPDM_GRIDRPC_COMPLEXREPONSECLASS_SIMPLE, VSWUPDM_DEVERROR_ASSERT_16); /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */

  /* #10 Select RpcProxyTarget by Channel. */
  target = vSwUpdM_GridRpc_GetResponseTarget(RequestOrigin, ResponseClass->RequestServiceIdx);

  /* #20 Trigger Confirmation. */
  retVal = vRpcProxy_vSwUpdM_GridRpc_SuspendConfirmation_Target(target, (uint16) vSwUpdM_GridRpc_GetRpcProxyRequestOfService(ResponseClass->RequestServiceIdx), vSwUpdM_GridRpc_GetRpcProxyServiceExecutionState(ServiceExecutionState), (uint8)ResponseClass->RequestServiceIdx, ResponseClass->Result);

  return retVal;
} /* vSwUpdM_GridRpc_ProxySuspendConfirmation */

/**********************************************************************************************************************
 * vSwUpdM_GridRpc_ProxyBookkeeperConfirmation
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
 *
 */
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GridRpc_ProxyBookkeeperConfirmation(
  vSwUpdM_NodeIterType RequestOrigin,
  vSwUpdM_GridRpc_ServiceExecutionStateType ServiceExecutionState,
  vSwUpdM_GridRpc_ComplexResponseClassBasePtrType ResponseClass)  /* PRQA S 3673 */ /* MD_vSwUpdM_Rule8.13_3673_PointerToConstParameter */
{
  Std_ReturnType retVal = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vRpcProxy_CTargetsIterType target;

  vSwUpdM_DevError_Assert(ResponseClass->ComplexResponseClassType == VSWUPDM_GRIDRPC_COMPLEXREPONSECLASS_SIMPLE, VSWUPDM_DEVERROR_ASSERT_17); /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */

  if (RequestOrigin == (vSwUpdM_NodeIterType) vSwUpdM_GetLocalNode())
  {
    retVal = vSwUpdM_GridRpc_LocalBookkeeperConfirmation(RequestOrigin, ServiceExecutionState, ResponseClass);
  }
  else
  {
    /* #10 Select RpcProxyTarget by Channel. */
    target = vSwUpdM_GridRpc_GetResponseTarget(RequestOrigin, ResponseClass->RequestServiceIdx);

    /* #20 Trigger Confirmation. */
    retVal = vRpcProxy_vSwUpdM_GridRpc_BookkeeperConfirmation_Target(target, (uint16)vSwUpdM_GridRpc_GetRpcProxyRequestOfService(ResponseClass->RequestServiceIdx), vSwUpdM_GridRpc_GetRpcProxyServiceExecutionState(ServiceExecutionState), (uint8)ResponseClass->RequestServiceIdx, ResponseClass->Result);
  }

  return retVal;
} /* vSwUpdM_GridRpc_ProxyBookkeeperConfirmation */

/**********************************************************************************************************************
 * vSwUpdM_GridRpc_ProxyBkGetGenericParameterResponse
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
 *
 */
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GridRpc_ProxyBkGetGenericParameterResponse(
  vSwUpdM_NodeIterType RequestOrigin,
  vSwUpdM_GridRpc_ServiceExecutionStateType ServiceExecutionState,
  vSwUpdM_GridRpc_ComplexResponseClassBasePtrType ResponseClass)  /* PRQA S 3673 */ /* MD_vSwUpdM_Rule8.13_3673_PointerToConstParameter */
{
  Std_ReturnType retVal = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vRpcProxy_CTargetsIterType target;

  vSwUpdM_DevError_Assert(ResponseClass->ComplexResponseClassType == VSWUPDM_GRIDRPC_COMPLEXREPONSECLASS_BK_GET_GENERIC_PARAMETER, VSWUPDM_DEVERROR_ASSERT_18); /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */

  if (RequestOrigin == (vSwUpdM_NodeIterType) vSwUpdM_GetLocalNode())
  {
    retVal = vSwUpdM_GridRpc_LocalBkGetGenericParameterResponse(RequestOrigin, ServiceExecutionState, ResponseClass);
  }
  else
  {
    /* #10 Select RpcProxyTarget by Channel. */
    target = vSwUpdM_GridRpc_GetResponseTarget(RequestOrigin, ResponseClass->RequestServiceIdx);

    /* #20 Trigger Confirmation. */
    /* PRQA S 0310 1 */ /* MD_vSwUpdM_Rule11.3_0310_ServiceParameterCast */
    retVal = vRpcProxy_vSwUpdM_GridRpc_BkGetGenericParameterResponse_Target(target, (uint16)vSwUpdM_GridRpc_GetRpcProxyRequestOfService(ResponseClass->RequestServiceIdx), vSwUpdM_GridRpc_GetRpcProxyServiceExecutionState(ServiceExecutionState), ResponseClass->Result, ((vSwUpdM_GridRpc_ComplexResponseClassBkGetGenericPtrType)ResponseClass)->GenericValue);
  }

  return retVal;
} /* vSwUpdM_GridRpc_ProxyBkGetGenericParameterResponse */

/**********************************************************************************************************************
 * vSwUpdM_GridRpc_ProxyBkGetSegmentAttributesResponse
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
 *
 */
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GridRpc_ProxyBkGetSegmentAttributesResponse(
  vSwUpdM_NodeIterType RequestOrigin,
  vSwUpdM_GridRpc_ServiceExecutionStateType ServiceExecutionState,
  vSwUpdM_GridRpc_ComplexResponseClassBasePtrType ResponseClass)   /* PRQA S 3673 */ /* MD_vSwUpdM_Rule8.13_3673_PointerToConstParameter */
{
  Std_ReturnType retVal = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vRpcProxy_CTargetsIterType target;

  vSwUpdM_DevError_Assert(ResponseClass->ComplexResponseClassType == VSWUPDM_GRIDRPC_COMPLEXREPONSECLASS_BK_GET_SEGMENT_ATTRIBUTES, VSWUPDM_DEVERROR_ASSERT_19); /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */

  if (RequestOrigin == (vSwUpdM_NodeIterType) vSwUpdM_GetLocalNode())
  {
    retVal = vSwUpdM_GridRpc_LocalBkGetSegmentAttributesResponse(RequestOrigin, ServiceExecutionState, ResponseClass);
  }
  else
  {
    /* #10 Select RpcProxyTarget by Channel. */
    target = vSwUpdM_GridRpc_GetResponseTarget(RequestOrigin, ResponseClass->RequestServiceIdx);

    /* #20 Trigger Confirmation. */
    /* PRQA S 0310 1 */ /* MD_vSwUpdM_Rule11.3_0310_ServiceParameterCast */
    retVal = vRpcProxy_vSwUpdM_GridRpc_BkGetSegmentAttributesResponse_Target(target, (uint16)vSwUpdM_GridRpc_GetRpcProxyRequestOfService(ResponseClass->RequestServiceIdx), vSwUpdM_GridRpc_GetRpcProxyServiceExecutionState(ServiceExecutionState), ResponseClass->Result, ((vSwUpdM_GridRpc_ComplexResponseClassBkGetSegmentAttributesPtrType)ResponseClass)->SegmentAttributes);
  }

  return retVal;
} /* vSwUpdM_GridRpc_ProxyBkGetSegmentAttributesResponse */

/**********************************************************************************************************************
 * vSwUpdM_GridRpc_ProxyBkGetResumeInfoResponse
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
 *
 */
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GridRpc_ProxyBkGetResumeInfoResponse(
  vSwUpdM_NodeIterType RequestOrigin,
  vSwUpdM_GridRpc_ServiceExecutionStateType ServiceExecutionState,
  vSwUpdM_GridRpc_ComplexResponseClassBasePtrType ResponseClass)  /* PRQA S 3673 */ /* MD_vSwUpdM_Rule8.13_3673_PointerToConstParameter */
{
  Std_ReturnType retVal = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vRpcProxy_CTargetsIterType target;

  vSwUpdM_DevError_Assert(ResponseClass->ComplexResponseClassType == VSWUPDM_GRIDRPC_COMPLEXREPONSECLASS_BK_GET_RESUME_INFO, VSWUPDM_DEVERROR_ASSERT_20); /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */

  if (RequestOrigin == (vSwUpdM_NodeIterType) vSwUpdM_GetLocalNode())
  {
    retVal = vSwUpdM_GridRpc_LocalBkGetResumeInfoResponse(RequestOrigin, ServiceExecutionState, ResponseClass);
  }
  else
  {
    /* #10 Select RpcProxyTarget by Channel. */
    target = vSwUpdM_GridRpc_GetResponseTarget(RequestOrigin, ResponseClass->RequestServiceIdx);

    /* #20 Trigger Confirmation. */
    /* PRQA S 0310 1 */ /* MD_vSwUpdM_Rule11.3_0310_ServiceParameterCast */
    retVal = vRpcProxy_vSwUpdM_GridRpc_BkGetResumeInfoResponse_Target(target, (uint16)vSwUpdM_GridRpc_GetRpcProxyRequestOfService(ResponseClass->RequestServiceIdx), vSwUpdM_GridRpc_GetRpcProxyServiceExecutionState(ServiceExecutionState), ResponseClass->Result, ((vSwUpdM_GridRpc_ComplexResponseClassBkGetResumeInfoPtrType)ResponseClass)->ResumeInfo);
  }

  return retVal;
} /* vSwUpdM_GridRpc_ProxyBkGetResumeInfoResponse */

/**********************************************************************************************************************
 * vSwUpdM_GridRpc_ProxyLegacyResponse
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GridRpc_ProxyLegacyResponse(
  vSwUpdM_NodeIterType RequestOrigin,
  vSwUpdM_GridRpc_ServiceExecutionStateType ServiceExecutionState,
  vSwUpdM_GridRpc_ComplexResponseClassBasePtrType ResponseClass)  /* PRQA S 3673 */ /* MD_vSwUpdM_Rule8.13_3673_PointerToConstParameter */
{
  Std_ReturnType retVal = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vRpcProxy_CTargetsIterType target;

  vSwUpdM_DevError_Assert(ResponseClass->ComplexResponseClassType == VSWUPDM_GRIDRPC_COMPLEXREPONSECLASS_SIMPLE, VSWUPDM_DEVERROR_ASSERT_28); /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */

  /* #10 Select RpcProxyTarget by Channel. */
  target = vSwUpdM_GridRpc_GetResponseTarget(RequestOrigin, ResponseClass->RequestServiceIdx);

  /* #20 Trigger Confirmation. */
  retVal = vRpcProxy_vSwUpdM_RemoteConfirmation_Target(target, (uint16) vSwUpdM_GridRpc_GetRpcProxyRequestOfService(ResponseClass->RequestServiceIdx), vSwUpdM_GridRpc_GetRpcProxyServiceExecutionState(ServiceExecutionState), (uint8) ResponseClass->RequestServiceIdx, ResponseClass->Result);

  return retVal;
} /* vSwUpdM_GridRpc_ProxyBkGetResumeInfoResponse */
#endif

/*******************************
 * Local Redirect Functions
 ******************************/

/**********************************************************************************************************************
 * vSwUpdM_GridRpc_LocalBkExecCommandService
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GridRpc_LocalBkExecCommandService( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_RpcProxyRedirect */
  vSwUpdM_NodeGroupIterType Destination,
  vSwUpdM_GridSrvc_ServiceClassBasePtrType Parameter) /* PRQA S 3673 */ /* MD_vSwUpdM_Rule8.13_3673_PointerToConstParameter */
{
  Std_ReturnType retVal;

  VSWUPDM_DUMMY_STATEMENT(Destination); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  /* PRQA S 0310 3 */ /* MD_vSwUpdM_Rule11.3_0310_ServiceParameterCast */
  retVal = vSwUpdM_BkPersistServer_ExecCommand(
    VSWUPDM_GRIDNODE_SINGLE_NODE_CFG_NODE_IDX,
    ((vSwUpdM_GridSrvc_ServiceClassBkExecCommandPtrType)Parameter)->Command);

  return retVal;
} /* vSwUpdM_GridRpc_LocalBkExecCommandService */

/**********************************************************************************************************************
 * vSwUpdM_GridRpc_LocalBkGetGenericParameterService
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GridRpc_LocalBkGetGenericParameterService( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_RpcProxyRedirect */
  vSwUpdM_NodeGroupIterType Destination,
  vSwUpdM_GridSrvc_ServiceClassBasePtrType Parameter) /* PRQA S 3673 */ /* MD_vSwUpdM_Rule8.13_3673_PointerToConstParameter */
{
    Std_ReturnType retVal;

  VSWUPDM_DUMMY_STATEMENT(Destination); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  /* PRQA S 0310 4 */ /* MD_vSwUpdM_Rule11.3_0310_ServiceParameterCast */
  retVal = vSwUpdM_BkPersistServer_RequestGetGenericParameter(
    VSWUPDM_GRIDNODE_SINGLE_NODE_CFG_NODE_IDX,
    ((vSwUpdM_GridSrvc_ServiceClassBkGetGenericParameterPtrType)Parameter)->Base.Entities,
    ((vSwUpdM_GridSrvc_ServiceClassBkGetGenericParameterPtrType)Parameter)->Base.ParamType);

  return retVal;
} /* vSwUpdM_GridRpc_LocalBkGetGenericParameterService */

/**********************************************************************************************************************
 * vSwUpdM_GridRpc_LocalBkGetSegmentAttributesService
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GridRpc_LocalBkGetSegmentAttributesService( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_RpcProxyRedirect */
  vSwUpdM_NodeGroupIterType Destination,
  vSwUpdM_GridSrvc_ServiceClassBasePtrType Parameter) /* PRQA S 3673 */ /* MD_vSwUpdM_Rule8.13_3673_PointerToConstParameter */
{
  Std_ReturnType retVal;

  VSWUPDM_DUMMY_STATEMENT(Destination); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  /* PRQA S 0310 3 */ /* MD_vSwUpdM_Rule11.3_0310_ServiceParameterCast */
  retVal = vSwUpdM_BkPersistServer_RequestGetSegmentAttributes(
    VSWUPDM_GRIDNODE_SINGLE_NODE_CFG_NODE_IDX,
    ((vSwUpdM_GridSrvc_ServiceClassBkGetSegmentAttributesPtrType)Parameter)->Entities);

  return retVal;
} /* vSwUpdM_GridRpc_LocalBkGetSegmentAttributesService */

/**********************************************************************************************************************
 * vSwUpdM_GridRpc_LocalBkGetResumeInfoService
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GridRpc_LocalBkGetResumeInfoService( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_RpcProxyRedirect */
  vSwUpdM_NodeGroupIterType Destination,
  vSwUpdM_GridSrvc_ServiceClassBasePtrType Parameter) /* PRQA S 3673 */ /* MD_vSwUpdM_Rule8.13_3673_PointerToConstParameter */
{
   Std_ReturnType retVal;

  VSWUPDM_DUMMY_STATEMENT(Destination); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(Parameter); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  retVal = vSwUpdM_BkPersistServer_RequestGetResumeInfo(VSWUPDM_GRIDNODE_SINGLE_NODE_CFG_NODE_IDX);

  return retVal;
} /* vSwUpdM_GridRpc_LocalBkGetResumeInfoService */

/**********************************************************************************************************************
 * vSwUpdM_GridRpc_LocalBkSetGenericParameterService
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GridRpc_LocalBkSetGenericParameterService( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_RpcProxyRedirect */
  vSwUpdM_NodeGroupIterType Destination,
  vSwUpdM_GridSrvc_ServiceClassBasePtrType Parameter) /* PRQA S 3673 */ /* MD_vSwUpdM_Rule8.13_3673_PointerToConstParameter */
{
  Std_ReturnType retVal;

  VSWUPDM_DUMMY_STATEMENT(Destination); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  /* PRQA S 0310 6 */ /* MD_vSwUpdM_Rule11.3_0310_ServiceParameterCast */
  retVal = vSwUpdM_BkPersistServer_SetGenericParameter(
    VSWUPDM_GRIDNODE_SINGLE_NODE_CFG_NODE_IDX,
    ((vSwUpdM_GridSrvc_ServiceClassBkSetGenericParameterPtrType)Parameter)->Base.Entities,
    ((vSwUpdM_GridSrvc_ServiceClassBkSetGenericParameterPtrType)Parameter)->Base.ParamType,
    ((vSwUpdM_GridSrvc_ServiceClassBkSetGenericParameterPtrType)Parameter)->GenericValue,
    ((vSwUpdM_GridSrvc_ServiceClassBkSetGenericParameterPtrType)Parameter)->SyncFlag);

  return retVal;
} /* vSwUpdM_GridRpc_LocalBkSetGenericParameterService */

/**********************************************************************************************************************
 * vSwUpdM_GridRpc_LocalBkSetSegmentAttributesService
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GridRpc_LocalBkSetSegmentAttributesService( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_RpcProxyRedirect */
  vSwUpdM_NodeGroupIterType Destination,
  vSwUpdM_GridSrvc_ServiceClassBasePtrType Parameter) /* PRQA S 3673 */ /* MD_vSwUpdM_Rule8.13_3673_PointerToConstParameter */
{
  Std_ReturnType retVal;

  VSWUPDM_DUMMY_STATEMENT(Destination); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  /* PRQA S 0310 5 */ /* MD_vSwUpdM_Rule11.3_0310_ServiceParameterCast */
  retVal = vSwUpdM_BkPersistServer_SetSegmentAttributes(
    VSWUPDM_GRIDNODE_SINGLE_NODE_CFG_NODE_IDX,
    ((vSwUpdM_GridSrvc_ServiceClassBkSetSegmentAttributesPtrType)Parameter)->Entities,
    ((vSwUpdM_GridSrvc_ServiceClassBkSetSegmentAttributesPtrType)Parameter)->SegmentAttributes,
    ((vSwUpdM_GridSrvc_ServiceClassBkSetSegmentAttributesPtrType)Parameter)->SyncFlag);

  return retVal;
} /* vSwUpdM_GridRpc_LocalBkSetSegmentAttributesService */

/**********************************************************************************************************************
 * vSwUpdM_GridRpc_LocalBkSetResumeInfoService
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GridRpc_LocalBkSetResumeInfoService( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_RpcProxyRedirect */
  vSwUpdM_NodeGroupIterType Destination,
  vSwUpdM_GridSrvc_ServiceClassBasePtrType Parameter) /* PRQA S 3673 */ /* MD_vSwUpdM_Rule8.13_3673_PointerToConstParameter */
{
  Std_ReturnType retVal;

  VSWUPDM_DUMMY_STATEMENT(Destination); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  /* PRQA S 0310 4 */ /* MD_vSwUpdM_Rule11.3_0310_ServiceParameterCast */
  retVal = vSwUpdM_BkPersistServer_SetResumeInfo(
    VSWUPDM_GRIDNODE_SINGLE_NODE_CFG_NODE_IDX,
    &((vSwUpdM_GridSrvc_ServiceClassBkSetResumeInfoPtrType)Parameter)->ResumeInfo,
    ((vSwUpdM_GridSrvc_ServiceClassBkSetResumeInfoPtrType)Parameter)->SyncFlag);

  return retVal;
} /* vSwUpdM_GridRpc_LocalBkSetResumeInfoService */

/**********************************************************************************************************************
 * vSwUpdM_GridRpc_LocalBookkeeperConfirmation
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GridRpc_LocalBookkeeperConfirmation( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_RpcProxyRedirect */
  vSwUpdM_NodeIterType RequestOrigin,
  vSwUpdM_GridRpc_ServiceExecutionStateType ServiceExecutionState,
  vSwUpdM_GridRpc_ComplexResponseClassBasePtrType ResponseClass)
{
  Std_ReturnType retVal;

  VSWUPDM_DUMMY_STATEMENT(RequestOrigin);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(ServiceExecutionState);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  vSwUpdM_DevError_Assert(ResponseClass->ComplexResponseClassType == VSWUPDM_GRIDRPC_COMPLEXREPONSECLASS_SIMPLE, VSWUPDM_DEVERROR_ASSERT_23); /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */

  if (ServiceExecutionState == VSWUPDM_GRIDRPC_SERVICEXECUTIONSTATE_FINISHED)
  {
    retVal = vSwUpdM_GridChannel_ProcessConfirmation(VSWUPDM_GRIDCHANNEL_CHANNELIDX_BOOKKEEPER, RequestOrigin, ResponseClass);
  }
  else
  {
    retVal = E_OK;
  }

  return retVal;
} /* vSwUpdM_GridRpc_LocalBookkeeperConfirmation */

/**********************************************************************************************************************
 * vSwUpdM_GridRpc_LocalBkGetGenericParameterResponse
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GridRpc_LocalBkGetGenericParameterResponse( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_RpcProxyRedirect */
  vSwUpdM_NodeIterType RequestOrigin,
  vSwUpdM_GridRpc_ServiceExecutionStateType ServiceExecutionState,
  vSwUpdM_GridRpc_ComplexResponseClassBasePtrType ResponseClass)
{
  Std_ReturnType retVal = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */

  VSWUPDM_DUMMY_STATEMENT(RequestOrigin);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(ServiceExecutionState);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  vSwUpdM_DevError_Assert(ResponseClass->ComplexResponseClassType == VSWUPDM_GRIDRPC_COMPLEXREPONSECLASS_BK_GET_GENERIC_PARAMETER, VSWUPDM_DEVERROR_ASSERT_25); /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */

  if (ServiceExecutionState == VSWUPDM_GRIDRPC_SERVICEXECUTIONSTATE_FINISHED)
  {
    retVal = vSwUpdM_GridChannel_ProcessConfirmation(
      VSWUPDM_GRIDCHANNEL_CHANNELIDX_BOOKKEEPER,
      RequestOrigin,
      ResponseClass); /* PRQA S 4342 */ /* MD_vSwUpdM_Rule10.5_4342_EnumParameterCast */
  }
  else
  {
    retVal = E_OK;
  }

  return retVal;
} /* vSwUpdM_GridRpc_LocalBkGetGenericParameterResponse */

/**********************************************************************************************************************
 * vSwUpdM_GridRpc_LocalBkGetSegmentAttributesResponse
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GridRpc_LocalBkGetSegmentAttributesResponse( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_RpcProxyRedirect */
  vSwUpdM_NodeIterType RequestOrigin,
  vSwUpdM_GridRpc_ServiceExecutionStateType ServiceExecutionState,
  vSwUpdM_GridRpc_ComplexResponseClassBasePtrType ResponseClass)
{
  Std_ReturnType retVal = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */

  VSWUPDM_DUMMY_STATEMENT(RequestOrigin);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(ServiceExecutionState);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  vSwUpdM_DevError_Assert(ResponseClass->ComplexResponseClassType == VSWUPDM_GRIDRPC_COMPLEXREPONSECLASS_BK_GET_SEGMENT_ATTRIBUTES, VSWUPDM_DEVERROR_ASSERT_26); /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */

  if (ServiceExecutionState == VSWUPDM_GRIDRPC_SERVICEXECUTIONSTATE_FINISHED)
  {
    retVal = vSwUpdM_GridChannel_ProcessConfirmation(
      VSWUPDM_GRIDCHANNEL_CHANNELIDX_BOOKKEEPER,
      RequestOrigin,
      ResponseClass); /* PRQA S 4342 */ /* MD_vSwUpdM_Rule10.5_4342_EnumParameterCast */
  }
  else
  {
    retVal = E_OK;
  }

  return retVal;
} /* vSwUpdM_GridRpc_LocalBkGetSegmentAttributesResponse */

/**********************************************************************************************************************
 * vSwUpdM_GridRpc_LocalBkGetResumeInfoResponse
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GridRpc_LocalBkGetResumeInfoResponse( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_RpcProxyRedirect */
  vSwUpdM_NodeIterType RequestOrigin,
  vSwUpdM_GridRpc_ServiceExecutionStateType ServiceExecutionState,
  vSwUpdM_GridRpc_ComplexResponseClassBasePtrType ResponseClass)
{
  Std_ReturnType retVal = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */

  VSWUPDM_DUMMY_STATEMENT(RequestOrigin);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(ServiceExecutionState);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  vSwUpdM_DevError_Assert(ResponseClass->ComplexResponseClassType == VSWUPDM_GRIDRPC_COMPLEXREPONSECLASS_BK_GET_RESUME_INFO, VSWUPDM_DEVERROR_ASSERT_27); /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */

  if (ServiceExecutionState == VSWUPDM_GRIDRPC_SERVICEXECUTIONSTATE_FINISHED)
  {
    retVal = vSwUpdM_GridChannel_ProcessConfirmation(
      VSWUPDM_GRIDCHANNEL_CHANNELIDX_BOOKKEEPER,
      RequestOrigin,
      ResponseClass); /* PRQA S 4342 */ /* MD_vSwUpdM_Rule10.5_4342_EnumParameterCast */
  }
  else
  {
    retVal = E_OK;
  }

  return retVal;
} /* vSwUpdM_GridRpc_LocalBkGetResumeInfoResponse */

/*********************
 * GRID SERVICE
 ********************/

/**********************************************************************************************************************
 * vSwUpdM_GridSrvc_ApplyLockResponses
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 */
VSWUPDM_LOCAL FUNC(void, VSWUPDM_CODE) vSwUpdM_GridSrvc_ApplyLockResponses(
vSwUpdM_NodeGroupIterType Destination)
{
  vSwUpdM_GridSrvc_ServiceIdxType serviceIndex = vSwUpdM_GridChannel_GetService(VSWUPDM_GRIDCHANNEL_CHANNELIDX_MAINTENANCE);
  vSwUpdM_NodeGroup2NodeIndIterType nodeIndIndex;
  boolean lockTargetValue;

  /* #10 Define target value. */
  if (serviceIndex == VSWUPDM_GRIDSRVC_SERVICEIDX_LOCK)
  {
    lockTargetValue = TRUE;
  }
  else /* VSWUPDM_GRIDSRVC_SERVICEIDX_UNLOCK */
  {
    lockTargetValue = FALSE;
  }

  /* #20 Iterate over NodeGroup. */
  for (nodeIndIndex = vSwUpdM_GetNodeGroup2NodeIndStartIdxOfNodeGroup(Destination);
       nodeIndIndex < vSwUpdM_GetNodeGroup2NodeIndEndIdxOfNodeGroup(Destination);
       nodeIndIndex++)
  {
    vSwUpdM_NodeIterType nodeIndex = vSwUpdM_GetNodeGroup2NodeInd(nodeIndIndex);

    /* #30 Set Locked-flag according to Request and Result. */
    if (vSwUpdM_GridNode_GetResultValid(serviceIndex, nodeIndex) == TRUE)
    {
      if (vSwUpdM_GridNode_GetResult(serviceIndex, nodeIndex) == E_OK)
      {
        vSwUpdM_SetLockedOfVarNode(nodeIndex, lockTargetValue);
      }
    }
  }
} /* vSwUpdM_GridSrvc_ApplyLockResponses */

/**********************************************************************************************************************
 * vSwUpdM_GridSrvc_HandleCommunicationState
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
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
VSWUPDM_LOCAL FUNC(void, VSWUPDM_CODE) vSwUpdM_GridSrvc_HandleCommunicationState(
  vSwUpdM_NodeGroupIterType Destination)
{
  vSwUpdM_GridSrvc_ServiceIdxType serviceIndex = vSwUpdM_GridChannel_GetService(VSWUPDM_GRIDCHANNEL_CHANNELIDX_MAINTENANCE);
  vSwUpdM_GridSrvc_ResponseClassMaintenancePtrType response = NULL_PTR;
  vSwUpdM_GridSrvc_ServiceClassBasePtrType param = NULL_PTR;

  /* #10 Evaluate GridState: */
  switch (vSwUpdM_GridSrvc_GridState)
  {
    default:
    /* case VSWUPDM_GRIDSRVC_GRIDSTATE_UNLOCKED: */
    /* case VSWUPDM_GRIDSRVC_GRIDSTATE_LOCKED: */
    /* #100 If "stable" state reached:
     *      Nothing to do.*/
    {
      break;
    }
    case VSWUPDM_GRIDSRVC_GRIDSTATE_LOCK_REQUEST:
    /* #200 If Lock requested:
     *      Trigger Lock request and go to next state. */
    {
      vSwUpdM_GridSrvc_Register(VSWUPDM_GRIDSRVC_SERVICEIDX_LOCK, &param);
      vSwUpdM_Grid_InitServiceClassMaintenance(VSWUPDM_EXCTSCHEDULE_SERVICESTATE_RUN, VSWUPDM_GRIDSRVC_SERVICEIDX_LOCK, (vSwUpdM_GridSrvc_ServiceClassMaintenancePtrType) param);  /* PRQA S 0310 */ /* MD_vSwUpdM_Rule11.3_0310_ServiceParameterCast */
      if (vSwUpdM_GridSrvc_Start(Destination, VSWUPDM_GRIDSRVC_SERVICEIDX_LOCK) == E_OK)
      {
        vSwUpdM_GridSrvc_GridState = VSWUPDM_GRIDSRVC_GRIDSTATE_LOCK_PENDING;
      }
      else
      {
        vSwUpdM_GridSrvc_GridState = VSWUPDM_GRIDSRVC_GRIDSTATE_UNLOCKED;
      }
      break;
    }
    case VSWUPDM_GRIDSRVC_GRIDSTATE_LOCK_PENDING:
    /* #300 If locking is in progress: */
    {
      /* #310 If all responses are collected: */
      if (vSwUpdM_GridSrvc_GetAggregatedResult(serviceIndex, &response) == VSWUPDM_GRIDSRVC_AGGREGATERESULT_DONE)
      {
        /* #320 Set locked-flag of responding nodes. */
        vSwUpdM_GridSrvc_ApplyLockResponses(Destination);

        /* #330 Check if locking was successful. */
        if (response->Result == E_OK)
        {
          vSwUpdM_GridSrvc_GridState = VSWUPDM_GRIDSRVC_GRIDSTATE_LOCKED;
        }
        else
        {
          /* #340 Otherwise: Trigger cleanup.*/
          vSwUpdM_GridSrvc_GridState = VSWUPDM_GRIDSRVC_GRIDSTATE_CLEANUP;
        }

        /* #350 Free channel. */
        vSwUpdM_GridSrvc_Finish(serviceIndex);
      }
      break;
    }
    case VSWUPDM_GRIDSRVC_GRIDSTATE_UNLOCK_REQUEST:
    /* #400 If unlock is requested:
     *      Trigger Unlock request and go to next state. */
    {
      vSwUpdM_GridSrvc_Register(VSWUPDM_GRIDSRVC_SERVICEIDX_UNLOCK, &param);
      vSwUpdM_Grid_InitServiceClassMaintenance(VSWUPDM_EXCTSCHEDULE_SERVICESTATE_RUN, VSWUPDM_GRIDSRVC_SERVICEIDX_UNLOCK, (vSwUpdM_GridSrvc_ServiceClassMaintenancePtrType) param);  /* PRQA S 0310 */ /* MD_vSwUpdM_Rule11.3_0310_ServiceParameterCast */
      if (vSwUpdM_GridSrvc_Start(Destination, VSWUPDM_GRIDSRVC_SERVICEIDX_UNLOCK) == E_OK)
      {
        vSwUpdM_GridSrvc_GridState = VSWUPDM_GRIDSRVC_GRIDSTATE_UNLOCK_PENDING;
      }
      else
      {
        vSwUpdM_GridSrvc_GridState = VSWUPDM_GRIDSRVC_GRIDSTATE_LOCKED;
      }
      break;
    }
    case VSWUPDM_GRIDSRVC_GRIDSTATE_CLEANUP:
    /* #500 If unlock is requested:
     *      Trigger Unlock request and go to next state. */
    {
      vSwUpdM_GridSrvc_Register(VSWUPDM_GRIDSRVC_SERVICEIDX_UNLOCK, &param);
      vSwUpdM_Grid_InitServiceClassMaintenance(VSWUPDM_EXCTSCHEDULE_SERVICESTATE_RUN, VSWUPDM_GRIDSRVC_SERVICEIDX_UNLOCK, (vSwUpdM_GridSrvc_ServiceClassMaintenancePtrType) param);  /* PRQA S 0310 */ /* MD_vSwUpdM_Rule11.3_0310_ServiceParameterCast */
      if (vSwUpdM_GridSrvc_Start(Destination, VSWUPDM_GRIDSRVC_SERVICEIDX_UNLOCK) == E_OK)
      {
        vSwUpdM_GridSrvc_GridState = VSWUPDM_GRIDSRVC_GRIDSTATE_UNLOCK_PENDING;
      }
      else
      {
        vSwUpdM_GridSrvc_GridState = VSWUPDM_GRIDSRVC_GRIDSTATE_UNLOCKED;
      }
      break;
    }
    case VSWUPDM_GRIDSRVC_GRIDSTATE_UNLOCK_PENDING:
      /* #600 If unlocking is in progress: */
    {
      /* #610 If all responses are collected: */
      if (vSwUpdM_GridSrvc_GetAggregatedResult(serviceIndex, &response) == VSWUPDM_GRIDSRVC_AGGREGATERESULT_DONE)
      {
        /* #620 Set locked-flag of responding nodes. */
        vSwUpdM_GridSrvc_ApplyLockResponses(Destination);

        vSwUpdM_GridSrvc_GridState = VSWUPDM_GRIDSRVC_GRIDSTATE_UNLOCKED;

        /* #640 Free channel. */
        vSwUpdM_GridSrvc_Finish(serviceIndex);
      }
      break;
    }
  }
} /* vSwUpdM_GridSrvc_HandleCommunicationState */ /* PRQA S 6030 1 */ /* MD_MSR_STCYC */

/*********************
 * LEGACY
 ********************/
#if (VSWUPDM_MULTICONTROLLER_SUPPORT == STD_ON)
/**********************************************************************************************************************
 * vSwUpdM_RemoteProcessResponse
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL FUNC(void, VSWUPDM_CODE) vSwUpdM_RemoteProcessResponse(
  vSwUpdM_NodeIterType NodeIndex,
  vSwUpdM_GridSrvc_ServiceIdxType ServiceId,
  Std_ReturnType Result)
{
  vSwUpdM_SetServiceIdOfResponseOfVarNode(NodeIndex, (uint8) ServiceId);
  vSwUpdM_SetResultOfResponseOfVarNode(NodeIndex, Result);
  vSwUpdM_SetResponseValidOfVarNode(NodeIndex, TRUE);
} /* vSwUpdM_RemoteProcessResponse */
#endif

/*********************
 * GRID STREAM
 ********************/

#if (VSWUPDM_MULTICONTROLLER_SUPPORT == STD_ON)
/**********************************************************************************************************************
  * vSwUpdM_RemoteStreamPrepareTx
  *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 */
VSWUPDM_LOCAL FUNC(void, VSWUPDM_CODE) vSwUpdM_RemoteStreamPrepareTx(
  vSwUpdM_RemoteStreamHandleType Handle,
  P2VAR(uint8, AUTOMATIC, VSWUPDM_APPL_VAR) Buffer,
  vSwUpdM_RemoteStreamSizeType AvailableLength,
  vSwUpdM_NodeIterType Target)
{

  /* #10 Check input parameters. */
  vSwUpdM_DevError_Assert((Handle < VSWUPDM_REMOTESTREAMHANDLE_SIZE), VSWUPDM_DEVERROR_ASSERT_8); /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */
  vSwUpdM_DevError_Assert((vSwUpdM_RemoteStream_List[Handle].State == VSWUPDM_REMOTESTREAMSTATE_IDLE), VSWUPDM_DEVERROR_ASSERT_9); /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */

  /* #20 Set RemoteStream properties. */
  vSwUpdM_RemoteStream_List[Handle].Buffer = Buffer;
  vSwUpdM_RemoteStream_List[Handle].AvailableLength = AvailableLength;
  vSwUpdM_RemoteStream_List[Handle].Offset = 0u;
  vSwUpdM_RemoteStream_List[Handle].Source = (vSwUpdM_NodeIterType) vSwUpdM_GetLocalNode();
  vSwUpdM_RemoteStream_List[Handle].Target = Target;

} /* vSwUpdM_RemoteStreamPrepareTx */

/**********************************************************************************************************************
 * vSwUpdM_RemoteStreamAbort
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 */
VSWUPDM_LOCAL FUNC(void, VSWUPDM_CODE) vSwUpdM_RemoteStreamAbort(vSwUpdM_GridSrvc_ServiceIdxType ServiceId)
{
  uint8_least index;
  boolean found = FALSE;
  vSwUpdM_RemoteStream_StateType streamState;

  /* #10 Find active remote stream. */
  for (index = 0u; index < (uint8)VSWUPDM_REMOTESTREAMHANDLE_SIZE; index++)
  {
    streamState = vSwUpdM_RemoteStream_List[index].State;
    /* This will fail if multiple streams are processed in parallel. */
    /* #20 Check for expected service -> stream state. */
    switch (ServiceId)
    {
      case VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_STREAM_START:
      /* If transmission of RemoteStreamStart failed, stream is in state TX_RESPONSE. */
      {
        if (streamState == VSWUPDM_REMOTESTREAMSTATE_TX_RESPONSE)
        {
          found = TRUE;
        }
        break;
      }
      case VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_STREAM_REQUEST:
      /* If transmission of RemoteStreamRequest failed, stream is in state RX_COPY. */
      {
        if (streamState == VSWUPDM_REMOTESTREAMSTATE_RX_COPY)
        {
          found = TRUE;
        }
        break;
      }
      case VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_STREAM_COPY:
      /* If transmission of RemoteStreamCopyt failed, stream is in state TX_WAIT_END or TX_RESPONSE. */
      {
        if ((streamState == VSWUPDM_REMOTESTREAMSTATE_TX_WAIT_END) || (streamState == VSWUPDM_REMOTESTREAMSTATE_TX_RESPONSE))
        {
          found = TRUE;
        }
        break;
      }
      default: /* PRQA S 2016 */ /* MD_MSR_EmptyClause */
      {
        break;
      }
    }
    /* #30 If stream is found, abort loop and set stream to FAILED state. */
    if (found == TRUE)
    {
      vSwUpdM_RemoteStream_List[index].State = VSWUPDM_REMOTESTREAMSTATE_FAIL;
      break;
    }
  }
} /* vSwUpdM_RemoteStreamAbort */
#endif

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  Global functions inside multi-unit
 *********************************************************************************************************************/

/*********************
 * GRID NODE
 ********************/
/**********************************************************************************************************************
 * vSwUpdM_GridNode_SetServiceStateByGroup
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(void, VSWUPDM_CODE) vSwUpdM_GridNode_SetServiceStateByGroup(
  vSwUpdM_GridSrvc_ServiceIdxType ServiceIndex,
  vSwUpdM_NodeGroupIterType Group,
  vSwUpdM_GridChannel_ServiceStateType State)
{
  vSwUpdM_NodeGroup2NodeIndIterType          nodeIndIndex;

  /* #10 Set requested State for each node in Group. */
  for (nodeIndIndex = vSwUpdM_GetNodeGroup2NodeIndStartIdxOfNodeGroup(Group);
       nodeIndIndex < vSwUpdM_GetNodeGroup2NodeIndEndIdxOfNodeGroup(Group); nodeIndIndex++)
  {
    vSwUpdM_NodeIterType nodeIndex = vSwUpdM_GetNodeGroup2NodeInd(nodeIndIndex);
    vSwUpdM_GridNode_SetServiceState(ServiceIndex, nodeIndex, State);
  }
} /* vSwUpdM_GridNode_SetServiceStateByGroup */

/**********************************************************************************************************************
 * vSwUpdM_GridNodeClearResultByGroup
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(void, VSWUPDM_CODE) vSwUpdM_GridNode_ClearResultByGroup(
  vSwUpdM_GridSrvc_ServiceIdxType ServiceIndex,
  vSwUpdM_NodeGroupIterType Group
  )
{
  vSwUpdM_NodeGroup2NodeIndIterType          nodeIndIndex;

  /* #10 Invalidate result for each node in Group. */
  for (nodeIndIndex = vSwUpdM_GetNodeGroup2NodeIndStartIdxOfNodeGroup(Group);
       nodeIndIndex < vSwUpdM_GetNodeGroup2NodeIndEndIdxOfNodeGroup(Group); nodeIndIndex++)
  {
    vSwUpdM_NodeIterType nodeIndex = vSwUpdM_GetNodeGroup2NodeInd(nodeIndIndex);
    vSwUpdM_GridNode_SetResultValid(ServiceIndex, nodeIndex, FALSE);
  }
} /* vSwUpdM_GridNode_ClearResultByGroup */

/**********************************************************************************************************************
 * vSwUpdM_GridNode_GetNodeIndexFromRpcProxySource
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GridNode_GetNodeIndexFromRpcProxySource(
  vSwUpdM_RpcProxySourceIdType SourceHandleId,
  P2VAR(vSwUpdM_NodeIterType, AUTOMATIC, VSWUPDM_APPL_VAR) NodeIndex) /* PRQA S 3673 */ /* MD_vSwUpdM_Rule8.13_3673_PointerToConstParameter */
{
  Std_ReturnType retVal = E_NOT_OK;
#if (VSWUPDM_RPCPROXYORIGIN == STD_ON)
  vSwUpdM_RpcProxyOriginIterType originIndex;
#endif

  VSWUPDM_DUMMY_STATEMENT(SourceHandleId);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(NodeIndex);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

#if (VSWUPDM_RPCPROXYORIGIN == STD_ON)
  /*  #10 Iterate over all configured origins. */
  for (originIndex = 0u; originIndex < vSwUpdM_GetSizeOfRpcProxyOrigin(); originIndex++)
  {
    /* #20 Get the related NodeIndex and return it. */
    if (vSwUpdM_GetVRpcProxySourceOfRpcProxyOrigin(originIndex) == SourceHandleId)
    {
      (*NodeIndex) = vSwUpdM_GetNodeInd(vSwUpdM_GetNodeIndStartIdxOfRpcProxyOrigin(originIndex));
      retVal = E_OK;
      break;
    }
  }
#endif

  return retVal;
} /* vSwUpdM_GridNode_GetNodeIndexFromRpcProxySource */

/**********************************************************************************************************************
 * vSwUpdM_GridNode_GetNodeIndexFromRpcProxySourceAndChannel
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GridNode_GetNodeIndexFromRpcProxySourceAndChannel(
  vSwUpdM_RpcProxySourceIdType SourceHandleId,
  vSwUpdM_GridChannel_ChannelIdxType ChannelIndex,
  P2VAR(vSwUpdM_NodeIterType, AUTOMATIC, VSWUPDM_APPL_VAR) NodeIndex)    /* PRQA S 3673 */ /* MD_vSwUpdM_Rule8.13_3673_PointerToConstParameter */
{
  Std_ReturnType                          retVal = E_NOT_OK;
#if (VSWUPDM_RPCPROXYORIGIN == STD_ON)
  vSwUpdM_NodeIterType                    nodeIndex;
  vSwUpdM_RpcProxyOriginMainIdxOfNodeType rpcNodeIdx;
#endif

  VSWUPDM_DUMMY_STATEMENT(SourceHandleId);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(ChannelIndex);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(NodeIndex);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

#if (VSWUPDM_RPCPROXYORIGIN == STD_ON)
  for(nodeIndex = 0u; nodeIndex < vSwUpdM_GetSizeOfNode(); nodeIndex++)
  {
    switch (ChannelIndex)
    {
      case VSWUPDM_GRIDCHANNEL_CHANNELIDX_MAINTENANCE:
      {
        rpcNodeIdx = vSwUpdM_GetRpcProxyOriginMaintenanceIdxOfNode(nodeIndex);
        break;
      }
      case VSWUPDM_GRIDCHANNEL_CHANNELIDX_SUSPEND:
      {
        rpcNodeIdx = vSwUpdM_GetRpcProxyOriginSuspendIdxOfNode(nodeIndex);
        break;
      }
      case VSWUPDM_GRIDCHANNEL_CHANNELIDX_BOOKKEEPER:
      {
        rpcNodeIdx = vSwUpdM_GetRpcProxyOriginBookkeeperIdxOfNode(nodeIndex);
        break;
      }
      default: /* VSWUPDM_GRIDCHANNEL_CHANNELIDX_MAIN */
      {
        rpcNodeIdx = vSwUpdM_GetRpcProxyOriginMainIdxOfNode(nodeIndex);
        break;
      }
    }

    if (rpcNodeIdx < vSwUpdM_GetSizeOfRpcProxyOrigin())
    {
      if (vSwUpdM_GetVRpcProxySourceOfRpcProxyOrigin(rpcNodeIdx) == SourceHandleId)
      {
        retVal = E_OK;
        (*NodeIndex) = nodeIndex;
        break;
      }
    }
  }
#endif

  return retVal;
} /* vSwUpdM_GridNode_GetNodeIndexFromRpcProxySourceAndChannel */ /* PRQA S 6080 1 */ /* MD_MSR_STMIF */

/**********************************************************************************************************************
 * vSwUpdM_GridNode_GetNodeIndexFromRpcProxyTargetAndChannel
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GridNode_GetNodeIndexFromRpcProxyTargetAndChannel(
  vSwUpdM_RpcProxyTargetIdType TargetHandleId,
  vSwUpdM_GridChannel_ChannelIdxType ChannelIndex,
  P2VAR(vSwUpdM_NodeIterType, AUTOMATIC, VSWUPDM_APPL_VAR) NodeIndex)
{
  Std_ReturnType                retVal = E_NOT_OK;
  vSwUpdM_NodeIterType          nodeIndex;
  vSwUpdM_RpcProxyTargetIdType  destId;

  for(nodeIndex = 0u; nodeIndex < vSwUpdM_GetSizeOfNode(); nodeIndex++)
  {
    switch (ChannelIndex)
    {
      case VSWUPDM_GRIDCHANNEL_CHANNELIDX_MAINTENANCE:
      {
        destId = vSwUpdM_GetDestinationMaintenanceOfNode(nodeIndex);
        break;
      }
      case VSWUPDM_GRIDCHANNEL_CHANNELIDX_SUSPEND:
      {
        destId = vSwUpdM_GetDestinationSuspendOfNode(nodeIndex);
        break;
      }
      case VSWUPDM_GRIDCHANNEL_CHANNELIDX_BOOKKEEPER:
      {
        destId = vSwUpdM_GetDestinationBookkeeperOfNode(nodeIndex);
        break;
      }
      default: /* VSWUPDM_GRIDCHANNEL_CHANNELIDX_MAIN */
      {
        destId = vSwUpdM_GetDestinationMainOfNode(nodeIndex);
        break;
      }
    }

     /*!
     *
     * Internal comment removed.
 *
 *
 *
     */
    if (destId != VSWUPDM_NO_DESTINATIONMAINOFNODE)
    {
      if (destId == TargetHandleId)
      {
        retVal = E_OK;
        (*NodeIndex) = nodeIndex;
        break;
      }
    }
  }

  return retVal;
} /* vSwUpdM_GridNode_GetNodeIndexFromRpcProxyTargetAndChannel */ /* PRQA S 6030, 6080 1 */ /* MD_MSR_STCYC, MD_MSR_STMIF */

/*********************
 * GRID RPC
 ********************/

/**********************************************************************************************************************
 * vSwUpdM_GridRpcStub_RemoteProcedureCall
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */

FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GridRpcStub_RemoteProcedureCall(
  vSwUpdM_NodeGroupIterType Destination,
  /*!
   * Internal comment removed.
 *
 *
   */
  vSwUpdM_GridSrvc_ServiceIdxType ServiceIndex,
  vSwUpdM_GridSrvc_ServiceClassBasePtrType Parameter) /* PRQA S 3673 */ /* MD_vSwUpdM_Rule8.13_3673_PointerToConstParameter */
{
  Std_ReturnType retVal = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */

  vSwUpdM_GridRpc_RequestServiceType calloutFunction;

  vSwUpdM_DevError_Assert((Parameter->ServiceClass == vSwUpdM_GridSrvc_GetServiceClassOfService(ServiceIndex)), VSWUPDM_DEVERROR_ASSERT_2); /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */

  calloutFunction = vSwUpdM_GridRpc_RequestService[vSwUpdM_GridSrvc_GetServiceClassOfService(ServiceIndex)];

  if (calloutFunction != NULL_PTR)
  {
    retVal = calloutFunction(Destination, Parameter);
  }

  return retVal;
  /* PRQA S 6030, 6050 1 */ /* MD_MSR_STCAL, MD_MSR_STCYC */
} /* vSwUpdM_GridRpcStub_RemoteProcedureCall */

/**********************************************************************************************************************
 *  Global functions outside multi-unit
 *********************************************************************************************************************/

/*********************
 * GRID CHANNEL
 ********************/

/**********************************************************************************************************************
 * vSwUpdM_GridChannel_Init
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(void, VSWUPDM_CODE) vSwUpdM_GridChannel_Init(void)
{
  vSwUpdM_GridChannel_ChannelIdxType channelIndex;

  /* PRQA S 4527 1 */ /* MD_vSwUpdM_Rule10.1_4527_EnumLoop */
  for (channelIndex = VSWUPDM_GRIDCHANNEL_CHANNELIDX_ZERO; channelIndex < VSWUPDM_GRIDCHANNEL_CHANNELIDX_COUNT; channelIndex++)
  {
    vSwUpdM_GridChannel_SetState(channelIndex, VSWUPDM_GRIDCHANNEL_STATE_IDLE);
    vSwUpdM_GridChannel_SetResponseCount(channelIndex, 0u);
  }
}    /* vSwUpdM_GridChannel_Init */

/*********************
 * GRID NODE
 ********************/

/**********************************************************************************************************************
 * vSwUpdM_GridNode_Init
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */

FUNC(void, VSWUPDM_CODE) vSwUpdM_GridNode_Init(void)
{
  uint8_least index;
  for (index = 0; index < vSwUpdM_GetSizeOfNode(); index++)
  {
    vSwUpdM_GridSrvc_InitResponseClassMain(E_OK, &vSwUpdM_GridNode_ResponseMain[index]);
    vSwUpdM_GridSrvc_InitResponseClassMaintenance(E_OK, &vSwUpdM_GridNode_ResponseMaintenance[index]);
    vSwUpdM_GridSrvc_InitResponseClassSuspend(E_OK, &vSwUpdM_GridNode_ResponseSuspend[index]);
    vSwUpdM_GridSrvc_InitResponseClassBookkeeper(E_OK, &vSwUpdM_GridNode_ResponseBookkeeper[index]);
  }
} /* vSwUpdM_GridNode_Init */

/**********************************************************************************************************************
 * vSwUpdM_GridNode_IsNodeContainedInNodeGroup
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(boolean, VSWUPDM_CODE) vSwUpdM_GridNode_IsNodeContainedInNodeGroup(
  vSwUpdM_NodeGroupIterType Group,
  vSwUpdM_NodeIterType Node)
{
  vSwUpdM_NodeGroup2NodeIndIterType iterIdx;
  boolean retVal = FALSE;

  /* Optimization for local node: */
  if (Node == (vSwUpdM_NodeIterType) vSwUpdM_GetLocalNode())
  {
    if (vSwUpdM_IsWithLocalNodeOfNodeGroup(Group))
    {
      retVal = TRUE;
    }
  }
  else
  {
    for (iterIdx = vSwUpdM_GetNodeGroup2NodeIndStartIdxOfNodeGroup(Group);
      iterIdx < vSwUpdM_GetNodeGroup2NodeIndEndIdxOfNodeGroup(Group);
      iterIdx++)
    {
      /* If node is member of the Group */
      if (vSwUpdM_GetNodeGroup2NodeInd(iterIdx) == Node)
      {
        retVal = TRUE;
        break;
      }
    }
  }

  return retVal;
}
/* vSwUpdM_GridNode_IsNodeContainedInNodeGroup */

/*********************
 * GRID RPC
 ********************/

/**********************************************************************************************************************
 * vSwUpdM_GridRpc_TransmitResponse
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */

FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GridRpc_TransmitResponse(
  vSwUpdM_NodeIterType RequestOrigin,
  vSwUpdM_GridRpc_ServiceExecutionStateType ServiceExecutionState,
  vSwUpdM_GridRpc_ComplexResponseClassBasePtrType ResponseClass)
{
  Std_ReturnType retVal = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */

  vSwUpdM_GridRpc_ResponseServiceType calloutFunction;

  vSwUpdM_DevError_Assert(vSwUpdM_GridSrvc_GetResponseClassIndexOfService(ResponseClass->RequestServiceIdx) <= VSWUPDM_GRIDSRVC_RESPONSECLASS_COUNT, VSWUPDM_DEVERROR_ASSERT_29); /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */

  calloutFunction = vSwUpdM_GridRpc_ResponseService[vSwUpdM_GridSrvc_GetResponseClassIndexOfService(ResponseClass->RequestServiceIdx)];

  if (calloutFunction != NULL_PTR)
  {
    retVal = calloutFunction(RequestOrigin, ServiceExecutionState, ResponseClass);
  }

  return retVal;
} /* vSwUpdM_GridRpc_TransmitResponse */

#if (VSWUPDM_MULTICONTROLLER_SUPPORT == STD_ON)
/*********************************
 * vRpcProxy Rx Call-In Functions
 ********************************/

/**********************************************************************************************************************
 vSwUpdM_vSwUpdM_GridRpc_StartStream
 *********************************************************************************************************************/
/*!
 *  \brief vRpcProxy receive callout function for StartStream call.
 *  \details     -
 *  \param[in]   sourceHandleId Source of the request.
 *  \param[in]   ServiceState
 *  \param[in]   StreamInfo
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     remote
 */
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, VSWUPDM_CODE) vSwUpdM_vSwUpdM_GridRpc_StartStream(
  vRpcProxy_SourcesIterType sourceHandleId,
  uint8 ServiceState,
  P2CONST(vSwUpdM_StreamInfoType, AUTOMATIC, VSWUPDM_APPL_DATA)StreamInfo)
{
  vSwUpdM_NodeIterType sourceIndex = VSWUPDM_INVALID_NODE;
  Std_ReturnType       result;

  /* #10 Get for vSwUpdM node index by vRprProxy SourceHandleId. */
  result = vSwUpdM_GridNode_GetNodeIndexFromRpcProxySource((vSwUpdM_RpcProxySourceIdType) sourceHandleId, &sourceIndex);

  /* #20 Range check input parameters. */
  if (result == E_OK)
  {
    if (ServiceState >= ((uint8)VSWUPDM_EXCTSCHEDULE_SERVICESTATE_COUNT))
    {
      result = E_NOT_OK;
    }
  }

  if (result == E_OK)
  {
    /* #30 Call internal function to process request. */
    (void) vSwUpdM_SrvcRouting_StartStream(sourceIndex, (vSwUpdM_ExctSchedule_ServiceStateType) ServiceState, StreamInfo); /* PRQA S 4342 */ /* MD_vSwUpdM_Rule10.5_4342_EnumParameterCast */
  }
} /* vSwUpdM_vSwUpdM_GridRpc_StartStream */

/**********************************************************************************************************************
 vSwUpdM_vSwUpdM_RemoteProcessStreamData
 *********************************************************************************************************************/
/*!
 *  \brief vRpcProxy receive callout function for ProcessStreamData call.
 *  \details     -
 *  \param[in]   sourceHandleId Source of the request.
 *  \param[in]   ServiceState
 *  \param[in]   StreamLength
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     remote
 */
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, VSWUPDM_CODE) vSwUpdM_vSwUpdM_RemoteProcessStreamData(vRpcProxy_SourcesIterType sourceHandleId, uint8 ServiceState,  uint32 StreamLength)
{
  vSwUpdM_NodeIterType sourceIndex = VSWUPDM_INVALID_NODE;
  Std_ReturnType       result;

  /* #10 Get for vSwUpdM node index by vRprProxy SourceHandleId. */
  result = vSwUpdM_GridNode_GetNodeIndexFromRpcProxySource((vSwUpdM_RpcProxySourceIdType) sourceHandleId, &sourceIndex);

  if (result == E_OK)
  {
    /* #30 Call internal function to process request. */
    (void) vSwUpdM_SrvcRouting_RemoteProcessStreamData(sourceIndex, (vSwUpdM_ExctSchedule_ServiceStateType) ServiceState, (vSwUpdM_LengthType)StreamLength); /* PRQA S 4342 */ /* MD_vSwUpdM_Rule10.5_4342_EnumParameterCast */
  }
} /* vSwUpdM_RemoteProcessStreamData */

/**********************************************************************************************************************
 vSwUpdM_vSwUpdM_RemoteResponseCopyStreamData
 *********************************************************************************************************************/
/*!
 *  \brief vRpcProxy receive callout function for CopyStreamData call.
 *  \details     -
 *  \param[in]   sourceHandleId         Source of the response.
 *  \param[in]   targetHandleId         Target of the initial request.
 *  \param[in]   responseOfServiceId    ServiceId of the initial request.
 *  \param[in]   serviceExecutionStatus Legacy, will be removed by further vRpcProxy version.
 *  \param[in]   StreamBuffer
 *  \param[in]   StreamBuffer_Length
 *  \param[in]   AvailableLength
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     remote
 */
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, VSWUPDM_CODE) vSwUpdM_vSwUpdM_RemoteResponseCopyStreamData(
  vRpcProxy_SourcesIterType sourceHandleId,
  vRpcProxy_CTargetsIterType targetHandleId,
  uint16 responseOfServiceId,
  uint8 serviceExecutionStatus,
  P2VAR(uint8, AUTOMATIC, VSWUPDM_APPL_VAR) StreamBuffer, /* PRQA S 3673 */ /* MD_MSR_Rule8.13 */
  uint16 StreamBuffer_Length,
  uint32 AvailableLength)
{
  vSwUpdM_NodeIterType sourceIndex = VSWUPDM_INVALID_NODE;
  Std_ReturnType       result;

  VSWUPDM_DUMMY_STATEMENT(targetHandleId);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(responseOfServiceId);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(serviceExecutionStatus);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  /* #10 Get for vSwUpdM node index by vRprProxy SourceHandleId. */
  result = vSwUpdM_GridNode_GetNodeIndexFromRpcProxySource((vSwUpdM_RpcProxySourceIdType) sourceHandleId, &sourceIndex);

  if (result == E_OK)
  {
    /* #30 Call internal function to process request. */
    (void) vSwUpdM_SrvcRouting_RemoteResponseCopyStreamData(sourceIndex, StreamBuffer, (vSwUpdM_LengthType)StreamBuffer_Length, (vSwUpdM_LengthType)AvailableLength);
  }
  /* PRQA S 6060 1 */ /* MD_MSR_STPAR */
} /* vSwUpdM_RemoteResponseCopyStreamData */

/**********************************************************************************************************************
 vSwUpdM_vSwUpdM_RemoteStreamStart
 *********************************************************************************************************************/
/*!
 *  \brief vRpcProxy receive callout function for RemoteStreamStart call.
 *  \details     -
 *  \param[in]   sourceHandleId  Source of the request.
 *  \param[in]   ProcessHandle   Handle of DataProcess.
 *  \param[in]   Handle          Handle of RemoteStream.
 *  \param[in]   AvailableLength Available length of data.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     remote
 */
/*!
 *
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, VSWUPDM_CODE) vSwUpdM_vSwUpdM_RemoteStreamStart(
  vRpcProxy_SourcesIterType sourceHandleId,
  uint8 ProcessHandle,
  uint8 Handle,
  uint32 AvailableLength)
{
  vSwUpdM_NodeIterType sourceIndex = VSWUPDM_INVALID_NODE;
  Std_ReturnType       result;

  /* #10 Get vSwUpdM node index by vRprProxy SourceHandleId and check if requester is allowed. */
  result = vSwUpdM_GridRpc_RemotePrepareRequestProcessing((vSwUpdM_RpcProxySourceIdType) sourceHandleId, &sourceIndex);

  if (result == E_OK)
  {
    /* #20 Call internal function to process request. */
    (void) vSwUpdM_SrvcRouting_RemoteStreamStart(sourceIndex, ProcessHandle, Handle, (vSwUpdM_LengthType)AvailableLength);
  }
} /* vSwUpdM_RemoteStreamStart */

/**********************************************************************************************************************
 vSwUpdM_vSwUpdM_RemoteStreamCopy
 *********************************************************************************************************************/
/*!
 *  \brief vRpcProxy receive callout function for StreamCopy call.
 *  \details     -
 *  \param[in]   sourceHandleId         Source of the response.
 *  \param[in]   targetHandleId         Target of the initial request.
 *  \param[in]   responseOfServiceId    ServiceId of the initial request.
 *  \param[in]   serviceExecutionStatus Legacy, will be removed by further vRpcProxy version.
 *  \param[in]   ProcessHandle          Handle of DataProcess.
 *  \param[in]   Handle                 Handle of RemoteStream.
 *  \param[in]   StreamBuffer           Buffer containing data.
 *  \param[in]   StreamBuffer_Length    Length of data.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     remote
 */
/*!
 *
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, VSWUPDM_CODE) vSwUpdM_vSwUpdM_RemoteStreamCopy(
  vRpcProxy_SourcesIterType sourceHandleId,
  vRpcProxy_CTargetsIterType targetHandleId,
  uint16 responseOfServiceId,
  uint8 serviceExecutionStatus,
  uint8 ProcessHandle,
  uint8 Handle,
  P2VAR(uint8, AUTOMATIC, VSWUPDM_APPL_VAR) StreamBuffer, /* PRQA S 3673 */ /* MD_MSR_Rule8.13 */
  uint16 StreamBuffer_Length,
  uint8 Result)
{
  vSwUpdM_NodeIterType sourceIndex = VSWUPDM_INVALID_NODE;
  Std_ReturnType       result;

  VSWUPDM_DUMMY_STATEMENT(targetHandleId);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(responseOfServiceId);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(serviceExecutionStatus);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  /* #10 Get vSwUpdM node index by vRprProxy SourceHandleId and check if requester is allowed. */
  result = vSwUpdM_GridRpc_RemotePrepareRequestProcessing((vSwUpdM_RpcProxySourceIdType) sourceHandleId, &sourceIndex);

  if (result == E_OK)
  {
    /* #20 Call internal function to process request. */
    (void) vSwUpdM_SrvcRouting_RemoteStreamCopy(sourceIndex, ProcessHandle, Handle, StreamBuffer, (vSwUpdM_LengthType)StreamBuffer_Length, (Std_ReturnType)Result);
  }
  /* PRQA S 6060 1 */ /* MD_MSR_STPAR */
} /* vSwUpdM_RemoteStreamCopy */

/**********************************************************************************************************************
 * vSwUpdM_vSwUpdM_GridRpc_AddSegment
 *********************************************************************************************************************/
/*!
 *  \brief vRpcProxy receive callout function for AddSegment call.
 *  \details     -
 *  \param[in]   sourceHandleId  Source of the request.
 *  \param[in]   ServiceState
 *  \param[in]   RemoteSegmentInfo
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     remote
 */
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, VSWUPDM_CODE) vSwUpdM_vSwUpdM_GridRpc_AddSegment(
  vRpcProxy_SourcesIterType sourceHandleId,
  uint8 ServiceState,
  P2CONST(vSwUpdM_RemoteSegmentInfoType, AUTOMATIC, VSWUPDM_APPL_DATA) SegmentInfo)
{
  vSwUpdM_NodeIterType sourceIndex = VSWUPDM_INVALID_NODE;
  Std_ReturnType       result;

  /* #10 Get for vSwUpdM node index by vRprProxy SourceHandleId. */
  result = vSwUpdM_GridNode_GetNodeIndexFromRpcProxySource((vSwUpdM_RpcProxySourceIdType) sourceHandleId, &sourceIndex);

  /* #20 Range check input parameters. */
  if (result == E_OK)
  {
    if (ServiceState >= ((uint8)VSWUPDM_EXCTSCHEDULE_SERVICESTATE_COUNT))
    {
      result = E_NOT_OK;
    }
  }

  if (result == E_OK)
  {
    /* #30 Call internal function to process request. */
    (void) vSwUpdM_SrvcRouting_AddSegment(sourceIndex, (vSwUpdM_ExctSchedule_ServiceStateType) ServiceState, SegmentInfo); /* PRQA S 4342 */ /* MD_vSwUpdM_Rule10.5_4342_EnumParameterCast */
  }
} /* vSwUpdM_vSwUpdM_GridRpc_AddSegment */

/**********************************************************************************************************************
 * vSwUpdM_vSwUpdM_GridRpc_ProcessModuleService
 *********************************************************************************************************************/
/*!
 *  \brief vRpcProxy receive callout function for VerifyModule call.
 *  \details     -
 *  \param[in]   sourceHandleId  Source of the request.
 *  \param[in]   ServiceState
 *  \param[in]   ModuleHandle
 *  \param[in]   RemoteProcessInfo
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     remote
 */
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
FUNC(void, VSWUPDM_CODE) vSwUpdM_vSwUpdM_GridRpc_ProcessModuleService(
  vRpcProxy_SourcesIterType sourceHandleId,
  uint8 ServiceState,
  uint8 Service,
  uint32 ModuleHandle,
  P2CONST(vSwUpdM_RemoteProcessInfoType, AUTOMATIC, VSWUPDM_APPL_DATA) RemoteProcessInfo)
{
  Std_ReturnType                  result;
  vSwUpdM_NodeIterType            sourceIndex = VSWUPDM_INVALID_NODE;
  vSwUpdM_ModuleIdType            moduleId    = VSWUPDM_INVALID_ID;
  vSwUpdM_ProcessInfoType         processInfo;
  P2CONST(vSwUpdM_ProcessInfoType, AUTOMATIC, VSWUPDM_APPL_DATA) processInfoPtr = NULL_PTR;
  vSwUpdM_DataProcessesIterType   processId   = vSwUpdM_GetSizeOfDataProcesses();
  vSwUpdM_GridSrvc_ServiceIdxType serviceIdx  = VSWUPDM_GRIDSRVC_SERVICEIDX_UNDEFINED;

  /* #10 Get for vSwUpdM node index by vRprProxy SourceHandleId. */
  result = vSwUpdM_GridNode_GetNodeIndexFromRpcProxySource((vSwUpdM_RpcProxySourceIdType) sourceHandleId, &sourceIndex);

  /* #20 Range check input parameters. */
  if (result == E_OK)
  {
    result = vSwUpdM_GridRpc_GenericRequestPreconditionCheck(ServiceState, Service);
  }

  /* #30 Get ServiceIdx. */
  if (result == E_OK)
  {
    result = vSwUpdM_GridRpc_GetServiceIndexByService(Service, VSWUPDM_GRIDSRVC_CLASS_PROCESS_MODULE, &serviceIdx);
  }

  /* #40 Get ModuleId. */
  if (result == E_OK)
  {
    /* If handle is unknown: Invalid handle is caught internally and causes negative response. */
    (void)vSwUpdM_GetModuleIdByHandle(&moduleId, ModuleHandle);

    /* Forward NULL_PTR to inner function for proper error handling. */
    if (RemoteProcessInfo != NULL_PTR)
    {
      (void)vSwUpdM_InitProcessInfo(&processInfo);

      processInfo.InputCount  = RemoteProcessInfo->InputCount;
      processInfo.OutputCount = RemoteProcessInfo->OutputCount;
      processInfo.Operation   = RemoteProcessInfo->Operation;
      processInfo.InputData   = NULL_PTR;
      processInfo.OutputData  = NULL_PTR;
      processInfoPtr          = &processInfo;

      if (serviceIdx != VSWUPDM_GRIDSRVC_SERVICEIDX_VERIFY_MODULE)
      {
        (void)vSwUpdM_GetProcessIdByProcessHandle(RemoteProcessInfo->Handle, &processId);
      }
    }
  }

  if (result == E_OK)
  {
    /* #50 Call internal function to process request. */
    /* PRQA S 4342 2 */ /* MD_vSwUpdM_Rule10.5_4342_EnumParameterCast */
    (void) vSwUpdM_SrvcRouting_ProcessModuleService(sourceIndex, (vSwUpdM_ExctSchedule_ServiceStateType)ServiceState,
      serviceIdx, moduleId, (vSwUpdM_ProcessIdType)processId, processInfoPtr);
  }
  /* PRQA S 6060 1 */ /* MD_MSR_STPAR */
} /* vSwUpdM_vSwUpdM_GridRpc_ProcessModuleService */

/**********************************************************************************************************************
 * vSwUpdM_vSwUpdM_RemoteUpdateModuleState
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, VSWUPDM_CODE) vSwUpdM_vSwUpdM_RemoteUpdateModuleState(
  vRpcProxy_SourcesIterType sourceHandleId,
  uint32 ModuleHandle,
  uint32 State)
{
  vSwUpdM_NodeIterType sourceIndex = VSWUPDM_INVALID_NODE;
  Std_ReturnType       result;

  /* #10 Get vSwUpdM node index by vRprProxy SourceHandleId and check if requester is allowed. */
  result = vSwUpdM_GridRpc_RemotePrepareRequestProcessing((vSwUpdM_RpcProxySourceIdType) sourceHandleId, &sourceIndex);

  if (result == E_OK)
  {
    /* #20 Call internal function to process request. */
    (void) vSwUpdM_SrvcRouting_RemoteUpdateModuleState(sourceIndex, (vSwUpdM_ModuleHandleIdType)ModuleHandle, (vSwUpdM_ModuleStateType)State);
  }
} /* vSwUpdM_RemoteUpdateModuleState */

/**********************************************************************************************************************
 * vSwUpdM_vSwUpdM_RemoteUpdateModuleValid
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, VSWUPDM_CODE) vSwUpdM_vSwUpdM_RemoteUpdateModuleValid(
  vRpcProxy_SourcesIterType sourceHandleId,
  uint32 ModuleHandle,
  uint32 Validity,
  uint32 RevisionUpdate)
{
  vSwUpdM_NodeIterType sourceIndex = VSWUPDM_INVALID_NODE;
  Std_ReturnType       result;

  /* #10 Get vSwUpdM node index by vRprProxy SourceHandleId and check if requester is allowed. */
  result = vSwUpdM_GridRpc_RemotePrepareRequestProcessing((vSwUpdM_RpcProxySourceIdType) sourceHandleId, &sourceIndex);

  if (result == E_OK)
  {
    /* #20 Call internal function to process request. */
    (void) vSwUpdM_SrvcRouting_RemoteUpdateModuleValid(sourceIndex, (vSwUpdM_ModuleHandleIdType)ModuleHandle, (vSwUpdM_ValidType)Validity, (vSwUpdM_RevisionUpdateType)RevisionUpdate);
  }
} /* vSwUpdM_RemoteUpdateModuleValid */

/**********************************************************************************************************************
 * vSwUpdM_vSwUpdM_RemoteUpdateModuleProgrammingAttempts
 *********************************************************************************************************************/
/*!
 *  \brief vRpcProxy receive callout function for UpdateModuleValid call.
 *  \details     -
 *  \param[in]   sourceHandleId       Source of the RPC request.
 *  \param[in]   ModuleHandle         RPC parameter: module handle.
 *  \param[in]   ProgrammingAttempts  RPC parameter: Programming attempts.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     remote
 */
/*!
 *
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, VSWUPDM_CODE) vSwUpdM_vSwUpdM_RemoteUpdateModuleProgrammingAttempts(
  vRpcProxy_SourcesIterType sourceHandleId,
  uint32 ModuleHandle,
  uint32 ProgrammingAttempts)
{
  vSwUpdM_NodeIterType sourceIndex = VSWUPDM_INVALID_NODE;
  Std_ReturnType       result;

  /* #10 Get vSwUpdM node index by vRprProxy SourceHandleId and check if requester is allowed. */
  result = vSwUpdM_GridRpc_RemotePrepareRequestProcessing((vSwUpdM_RpcProxySourceIdType) sourceHandleId, &sourceIndex);

  if (result == E_OK)
  {
    /* #20 Call internal function to process request. */
    (void) vSwUpdM_SrvcRouting_RemoteUpdateModuleProgrammingAttempts(sourceIndex, (vSwUpdM_ModuleHandleIdType)ModuleHandle, (vSwUpdM_ProgrammingAttemptsType)ProgrammingAttempts);
  }
} /* vSwUpdM_RemoteUpdateModuleProgrammingAttempts */

/**********************************************************************************************************************
 * vSwUpdM_vSwUpdM_RemoteUpdateRegionState
 *********************************************************************************************************************/
/*!
 *  \brief vRpcProxy receive callout function for UpdateRegionState call.
 *  \details     -
 *  \param[in]   sourceHandleId  Source of the RPC request.
 *  \param[in]   RegionHandle    RPC parameter: Region handle.
 *  \param[in]   State           RPC parameter: Parameter state.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     remote
 */
/*!
 *
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, VSWUPDM_CODE) vSwUpdM_vSwUpdM_RemoteUpdateRegionState(
  vRpcProxy_SourcesIterType sourceHandleId,
  uint32 RegionHandle,
  uint32 State)
{
  vSwUpdM_NodeIterType sourceIndex = VSWUPDM_INVALID_NODE;
  Std_ReturnType       result;

  /* #10 Get vSwUpdM node index by vRprProxy SourceHandleId and check if requester is allowed. */
  result = vSwUpdM_GridRpc_RemotePrepareRequestProcessing((vSwUpdM_RpcProxySourceIdType) sourceHandleId, &sourceIndex);

  if (result == E_OK)
  {
    /* #20 Call internal function to process request. */
    (void) vSwUpdM_SrvcRouting_RemoteUpdateRegionState(sourceIndex, (vSwUpdM_RegionHandleIdType)RegionHandle, (vSwUpdM_RegionStateType)State);
  }
} /* vSwUpdM_RemoteUpdateRegionState */

/**********************************************************************************************************************
 * vSwUpdM_vSwUpdM_RemoteUpdateRegionProgrammingAttempts
 *********************************************************************************************************************/
/*!
 *  \brief vRpcProxy receive callout function for UpdateRegionProgrammingAttempts call.
 *  \details     -
 *  \param[in]   sourceHandleId       Source of the RPC request.
 *  \param[in]   RegionHandle         RPC parameter: region handle.
 *  \param[in]   ProgrammingAttempts  RPC parameter: programming attempts.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     remote
 */
/*!
 *
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, VSWUPDM_CODE) vSwUpdM_vSwUpdM_RemoteUpdateRegionProgrammingAttempts(
  vRpcProxy_SourcesIterType sourceHandleId,
  uint32 RegionHandle,
  uint32 ProgrammingAttempts)
{
  vSwUpdM_NodeIterType sourceIndex = VSWUPDM_INVALID_NODE;
  Std_ReturnType       result;

  /* #10 Get vSwUpdM node index by vRprProxy SourceHandleId and check if requester is allowed. */
  result = vSwUpdM_GridRpc_RemotePrepareRequestProcessing((vSwUpdM_RpcProxySourceIdType) sourceHandleId, &sourceIndex);

  if (result == E_OK)
  {
    /* #20 Call internal function to process request. */
    (void) vSwUpdM_SrvcRouting_RemoteUpdateRegionProgrammingAttempts(sourceIndex, (vSwUpdM_RegionHandleIdType)RegionHandle, (vSwUpdM_ProgrammingAttemptsType)ProgrammingAttempts);
  }
} /* vSwUpdM_RemoteUpdateRegionProgrammingAttempts */

/**********************************************************************************************************************
 * vSwUpdM_vSwUpdM_RemoteUpdateSegmentAttributes
 *********************************************************************************************************************/
/*!
 *  \brief vRpcProxy receive callout function for UpdateSegmentAttributes call.
 *  \details     -
 *  \param[in]   sourceHandleId     Source of the RPC request.
 *  \param[in]   RemoteSegmentInfo  RPC parameter: remote segment info.
 *  \param[in]   State              RPC parameter: state.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     remote
 */
/*!
 *
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, VSWUPDM_CODE) vSwUpdM_vSwUpdM_RemoteUpdateSegmentAttributes(
  vRpcProxy_SourcesIterType sourceHandleId,
  P2CONST(vSwUpdM_RemoteSegmentInfoType, AUTOMATIC, VSWUPDM_APPL_DATA) RemoteSegmentInfo,
  uint32 State)
{
  vSwUpdM_NodeIterType sourceIndex = VSWUPDM_INVALID_NODE;
  Std_ReturnType       result;

  /* #10 Get vSwUpdM node index by vRprProxy SourceHandleId and check if requester is allowed. */
  result = vSwUpdM_GridRpc_RemotePrepareRequestProcessing((vSwUpdM_RpcProxySourceIdType) sourceHandleId, &sourceIndex);

  if (result == E_OK)
  {
    /* #20 Call internal function to process request. */
    (void) vSwUpdM_SrvcRouting_RemoteUpdateSegmentAttributes(sourceIndex, RemoteSegmentInfo, (vSwUpdM_SegmentStateType)State);
  }
} /* vSwUpdM_RemoteUpdateSegmentAttributes */

/**********************************************************************************************************************
 * vSwUpdM_vSwUpdM_RemoteUpdateResumeInfo
 *********************************************************************************************************************/
/*!
 *  \brief vRpcProxy receive callout function for UpdateResumeInfo call.
 *  \details     -
 *  \param[in]   sourceHandleId  Source of the request.
 *  \param[in]   ResumeInfo Resume info structure from remote child.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     remote
 */
/*!
 *
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, VSWUPDM_CODE) vSwUpdM_vSwUpdM_RemoteUpdateResumeInfo(
  vRpcProxy_SourcesIterType sourceHandleId,
  P2CONST(vSwUpdM_BkPersist_ResumeInfoType, AUTOMATIC, VSWUPDM_APPL_DATA) ResumeInfo)
{
  vSwUpdM_NodeIterType sourceIndex = VSWUPDM_INVALID_NODE;
  Std_ReturnType       result;

  /* #10 Get vSwUpdM node index by vRprProxy SourceHandleId and check if requester is allowed. */
  result = vSwUpdM_GridRpc_RemotePrepareRequestProcessing((vSwUpdM_RpcProxySourceIdType) sourceHandleId, &sourceIndex);

  if (result == E_OK)
  {
    /* #20 Call internal function to process request. */
    (void) vSwUpdM_SrvcRouting_RemoteUpdateResumeInfo(sourceIndex, ResumeInfo);
  }
} /* vSwUpdM_vSwUpdM_RemoteUpdateResumeInfo */

/**********************************************************************************************************************
 * vSwUpdM_vSwUpdM_RemoteProcessRequestInput
 *********************************************************************************************************************/
/*!
 *  \brief vRpcProxy receive callout function for ProcessRequestInput call.
 *  \details     -
 *  \param[in]   sourceHandleId     Source of the RPC request.
 *  \param[in]   ServiceState
 *  \param[in]   DataProcessHandle  RPC parameter: data process handle.
 *  \param[in]   InputIndex         RPC parameter: input index.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     remote
 */
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, VSWUPDM_CODE) vSwUpdM_vSwUpdM_RemoteProcessRequestInput(
  vRpcProxy_SourcesIterType sourceHandleId,
  uint8 ServiceState,
  uint8 DataProcessHandle,
  uint8 InputIndex)
{
  vSwUpdM_NodeIterType sourceIndex = VSWUPDM_INVALID_NODE;
  Std_ReturnType       result;

  /* #10 Get vSwUpdM node index by vRprProxy SourceHandleId and check if requester is allowed. */
  result = vSwUpdM_GridRpc_RemotePrepareRequestProcessing((vSwUpdM_RpcProxySourceIdType) sourceHandleId, &sourceIndex);

  /* #20 Range check input parameters. */
  if (result == E_OK)
  {
    if (ServiceState >= ((uint8)VSWUPDM_EXCTSCHEDULE_SERVICESTATE_COUNT))
    {
      result = E_NOT_OK;
    }
  }

  if (result == E_OK)
  {
    /* #30 Call internal function to process request. */
    (void) vSwUpdM_SrvcRouting_RemoteProcessRequestInput(sourceIndex, (vSwUpdM_ExctSchedule_ServiceStateType)ServiceState, (vSwUpdM_ProcessHandleOfDataProcessesType)DataProcessHandle, InputIndex); /* PRQA S 4342 */ /* MD_vSwUpdM_Rule10.5_4342_EnumParameterCast */
  }
} /* vSwUpdM_RemoteProcessRequestInput */

/**********************************************************************************************************************
 * vSwUpdM_vSwUpdM_RemoteConcludeSegment
 *********************************************************************************************************************/
/*!
 *  \brief vRpcProxy receive callout function for ConcludeSegment call.
 *  \details     -
 *  \param[in]   sourceHandleId  Source of the RPC request.
 *  \param[in]   StartAddress    RPC parameter: start address.
 *  \param[in]   WriteAddress    RPC parameter: write address.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     remote
 */
/*!
 *
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, VSWUPDM_CODE) vSwUpdM_vSwUpdM_RemoteConcludeSegment(
  vRpcProxy_SourcesIterType sourceHandleId,
  uint32 StartAddress,
  uint32 WriteAddress)
{
  vSwUpdM_NodeIterType sourceIndex = VSWUPDM_INVALID_NODE;
  Std_ReturnType       result;

  /* #10 Get vSwUpdM node index by vRprProxy SourceHandleId and check if requester is allowed. */
  result = vSwUpdM_GridRpc_RemotePrepareRequestProcessing((vSwUpdM_RpcProxySourceIdType) sourceHandleId, &sourceIndex);

  if (result == E_OK)
  {
    /* #20 Call internal function to process request. */
    (void) vSwUpdM_SrvcRouting_RemoteConcludeSegment(sourceIndex, (vSwUpdM_AddressType)StartAddress, (vSwUpdM_AddressType)WriteAddress);
  }
} /* vSwUpdM_RemoteConcludeSegment */

/**********************************************************************************************************************
 * vSwUpdM_vSwUpdM_GridRpc_GenericService
 *********************************************************************************************************************/
/*!
 *  \brief vRpcProxy receive callout function for GeneralService call.
 *  \details     -
 *  \param[in]   sourceHandleId  Source of the RPC request.
 *  \param[in]   ServiceState    RPC parameter: service state.
 *  \param[in]   Service         RPC parameter: service.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     remote
 */
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(void, VSWUPDM_CODE) vSwUpdM_vSwUpdM_GridRpc_GenericService(
  vRpcProxy_SourcesIterType sourceHandleId,
  uint8 ServiceState,
  uint8 Service)
{
  vSwUpdM_NodeIterType sourceIndex = VSWUPDM_INVALID_NODE;
  Std_ReturnType result;
  vSwUpdM_GridSrvc_ServiceIdxType serviceIdx = VSWUPDM_GRIDSRVC_SERVICEIDX_UNDEFINED;

  /* #10 Get for vSwUpdM node index by vRprProxy SourceHandleId. */
  result = vSwUpdM_GridNode_GetNodeIndexFromRpcProxySource((vSwUpdM_RpcProxySourceIdType) sourceHandleId, &sourceIndex);

  /* #20 Range check input parameters. */
  if (result == E_OK)
  {
    result = vSwUpdM_GridRpc_GenericRequestPreconditionCheck(ServiceState, Service);
  }

  /* #40 Get ServiceIndex. */
  if (result == E_OK)
  {
    result = vSwUpdM_GridRpc_GetServiceIndexByService(Service, VSWUPDM_GRIDSRVC_CLASS_GENERIC, &serviceIdx);
  }

  if (result == E_OK)
  {
    /* #50 Call internal function to process request. */
    (void) vSwUpdM_SrvcRouting_GenericService(sourceIndex, (vSwUpdM_ExctSchedule_ServiceStateType) ServiceState, serviceIdx); /* PRQA S 4342 */ /* MD_vSwUpdM_Rule10.5_4342_EnumParameterCast */
  }
} /* vSwUpdM_vSwUpdM_GridRpc_GenericService */

/**********************************************************************************************************************
 * vSwUpdM_vSwUpdM_GridRpc_PartitionService
 *********************************************************************************************************************/
/*!
 *  \brief vRpcProxy receive callout function for ModuleService call.
 *  \details     -
 *  \param[in]   sourceHandleId  Source of the RPC request.
 *  \param[in]   ServiceState    RPC parameter: service state.
 *  \param[in]   Service         RPC parameter: service.
 *  \param[in]   PartitionState  RPC parameter: partition state.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     remote
 */
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(void, VSWUPDM_CODE) vSwUpdM_vSwUpdM_GridRpc_PartitionService(
  vRpcProxy_SourcesIterType sourceHandleId,
  uint8 ServiceState,
  uint8 Service,
  uint8 PartitionState)
{
  vSwUpdM_NodeIterType sourceIndex = VSWUPDM_INVALID_NODE;
  Std_ReturnType result;
  vSwUpdM_GridSrvc_ServiceIdxType serviceIdx = VSWUPDM_GRIDSRVC_SERVICEIDX_UNDEFINED;

  /* #10 Get for vSwUpdM node index by vRprProxy SourceHandleId. */
  result = vSwUpdM_GridNode_GetNodeIndexFromRpcProxySource((vSwUpdM_RpcProxySourceIdType) sourceHandleId, &sourceIndex);

  /* #20 Range check input parameters. */
  if (result == E_OK)
  {
    result = vSwUpdM_GridRpc_GenericRequestPreconditionCheck(ServiceState, Service);
  }

  /* #40 Get ServiceIndex. */
  if (result == E_OK)
  {
    result = vSwUpdM_GridRpc_GetServiceIndexByService(Service, VSWUPDM_GRIDSRVC_CLASS_PARTITION, &serviceIdx);
  }

  if (result == E_OK)
  {
    /* #50 Call internal function to process request. */
    (void) vSwUpdM_SrvcRouting_PartitionService(sourceIndex, (vSwUpdM_ExctSchedule_ServiceStateType) ServiceState, serviceIdx, PartitionState); /* PRQA S 4342 */ /* MD_vSwUpdM_Rule10.5_4342_EnumParameterCast */
  }
} /* vSwUpdM_vSwUpdM_GridRpc_PartitionService */

/**********************************************************************************************************************
 * vSwUpdM_vSwUpdM_GridRpc_ModuleService
 *********************************************************************************************************************/
/*!
 *  \brief vRpcProxy receive callout function for ModuleService call.
 *  \details     -
 *  \param[in]   sourceHandleId  Source of the RPC request.
 *  \param[in]   ServiceState    RPC parameter: service state.
 *  \param[in]   Service         RPC parameter: service.
 *  \param[in]   ModuleHandle    RPC parameter: module handle.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     remote
 */
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(void, VSWUPDM_CODE) vSwUpdM_vSwUpdM_GridRpc_ModuleService(
  vRpcProxy_SourcesIterType sourceHandleId,
  uint8 ServiceState,
  uint8 Service,
  uint32 ModuleHandle)
{
  vSwUpdM_NodeIterType sourceIndex = VSWUPDM_INVALID_NODE;
  vSwUpdM_ModuleIdType moduleId = VSWUPDM_INVALID_ID;
  Std_ReturnType result;
  vSwUpdM_GridSrvc_ServiceIdxType serviceIdx = VSWUPDM_GRIDSRVC_SERVICEIDX_UNDEFINED;

  /* #10 Get for vSwUpdM node index by vRprProxy SourceHandleId. */
  result = vSwUpdM_GridNode_GetNodeIndexFromRpcProxySource((vSwUpdM_RpcProxySourceIdType) sourceHandleId, &sourceIndex);

  /* #20 Range check input parameters. */
  if (result == E_OK)
  {
    result = vSwUpdM_GridRpc_GenericRequestPreconditionCheck(ServiceState, Service);
  }

  if (result == E_OK)
  {
    result = vSwUpdM_GetModuleIdByHandle(&moduleId, (vSwUpdM_ModuleHandleIdType)ModuleHandle);
  }

  /* #40 Get ServiceIndex. */
  if (result == E_OK)
  {
    result = vSwUpdM_GridRpc_GetServiceIndexByService(Service, VSWUPDM_GRIDSRVC_CLASS_MODULE, &serviceIdx);
  }

  if (result == E_OK)
  {
    /* #50 Call internal function to process request. */
    (void) vSwUpdM_SrvcRouting_ModuleService(sourceIndex, (vSwUpdM_ExctSchedule_ServiceStateType) ServiceState, serviceIdx, moduleId); /* PRQA S 4342 */ /* MD_vSwUpdM_Rule10.5_4342_EnumParameterCast */
  }
} /* vSwUpdM_vSwUpdM_GridRpc_ModuleService */

/**********************************************************************************************************************
 * vSwUpdM_vSwUpdM_GridRpc_RegionService
 *********************************************************************************************************************/
/*!
 *  \brief vRpcProxy receive callout function for RegionService call.
 *  \details     -
 *  \param[in]   sourceHandleId  Source of the RPC request.
 *  \param[in]   ServiceState    RPC parameter: service state.
 *  \param[in]   Service         RPC parameter: service.
 *  \param[in]   RegionHandle    RPC parameter: region handle.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     remote
 */
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(void, VSWUPDM_CODE) vSwUpdM_vSwUpdM_GridRpc_RegionService(
  vRpcProxy_SourcesIterType sourceHandleId,
  uint8 ServiceState,
  uint8 Service,
  uint32 RegionHandle)
{
  vSwUpdM_NodeIterType sourceIndex = VSWUPDM_INVALID_NODE;
  vSwUpdM_RegionIdType regionId = VSWUPDM_INVALID_ID;
  Std_ReturnType result;
  vSwUpdM_GridSrvc_ServiceIdxType serviceIdx = VSWUPDM_GRIDSRVC_SERVICEIDX_UNDEFINED;

  /* #10 Get for vSwUpdM node index by vRprProxy SourceHandleId. */
  result = vSwUpdM_GridNode_GetNodeIndexFromRpcProxySource((vSwUpdM_RpcProxySourceIdType) sourceHandleId, &sourceIndex);

  /* #20 Range check input parameters. */
  if (result == E_OK)
  {
    result = vSwUpdM_GridRpc_GenericRequestPreconditionCheck(ServiceState, Service);
  }

  if (result == E_OK)
  {
    result = vSwUpdM_GetRegionIdByHandle(&regionId, (vSwUpdM_ModuleHandleIdType)RegionHandle);
  }

  /* #40 Get ServiceIndex. */
  if (result == E_OK)
  {
    result = vSwUpdM_GridRpc_GetServiceIndexByService(Service, VSWUPDM_GRIDSRVC_CLASS_REGION, &serviceIdx);
  }

  if (result == E_OK)
  {
    /* #50 Call internal function to process request. */
    (void) vSwUpdM_SrvcRouting_RegionService(sourceIndex, (vSwUpdM_ExctSchedule_ServiceStateType) ServiceState, serviceIdx, regionId); /* PRQA S 4342 */ /* MD_vSwUpdM_Rule10.5_4342_EnumParameterCast */
  }
} /* vSwUpdM_vSwUpdM_GridRpc_RegionService */

/**********************************************************************************************************************
 * vSwUpdM_vSwUpdM_GridRpc_SegmentService
 *********************************************************************************************************************/
/*!
 *  \brief vRpcProxy receive callout function for SegmentService call.
 *  \details     -
 *  \param[in]   sourceHandleId  Source of the RPC request.
 *  \param[in]   ServiceState    RPC parameter: service state.
 *  \param[in]   Service         RPC parameter: service.
 *  \param[in]   StartAddress    RPC parameter: start address.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     remote
 */
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
FUNC(void, VSWUPDM_CODE) vSwUpdM_vSwUpdM_GridRpc_SegmentService(
  vRpcProxy_SourcesIterType sourceHandleId,
  uint8 ServiceState,
  uint8 Service,
  uint32 StartAddress)
{
  vSwUpdM_NodeIterType sourceIndex = VSWUPDM_INVALID_NODE;
  vSwUpdM_SegmentIdType segmentId = VSWUPDM_SEGMENT_ID_DEFAULT;
  Std_ReturnType result;
  vSwUpdM_GridSrvc_ServiceIdxType serviceIdx = VSWUPDM_GRIDSRVC_SERVICEIDX_UNDEFINED;

  /* #10 Get for vSwUpdM node index by vRprProxy SourceHandleId. */
  result = vSwUpdM_GridNode_GetNodeIndexFromRpcProxySource((vSwUpdM_RpcProxySourceIdType) sourceHandleId, &sourceIndex);

  /* #20 Range check input parameters. */
  if (result == E_OK)
  {
    result = vSwUpdM_GridRpc_GenericRequestPreconditionCheck(ServiceState, Service);
  }

  /* #30 Check if StartAddress is valid. */
  if (result == E_OK)
  {
    result = vSwUpdM_Segment_GetSegmentIdByStartAddress(&segmentId, (vSwUpdM_AddressType)StartAddress, &vSwUpdM_ExternalSegmentsQueue);
  }

  /* #40 Get ServiceIndex. */
  if (result == E_OK)
  {
    result = vSwUpdM_GridRpc_GetServiceIndexByService(Service, VSWUPDM_GRIDSRVC_CLASS_SEGMENT, &serviceIdx);
  }

  if (result == E_OK)
  {
    /* #50 Call internal function to process request. */
    (void) vSwUpdM_SrvcRouting_SegmentService(sourceIndex, (vSwUpdM_ExctSchedule_ServiceStateType) ServiceState, serviceIdx, segmentId); /* PRQA S 4342 */ /* MD_vSwUpdM_Rule10.5_4342_EnumParameterCast */
  }
} /* vSwUpdM_vSwUpdM_GridRpc_SegmentService */

/**********************************************************************************************************************
 * vSwUpdM_vSwUpdM_GridRpc_MaintenanceService
 *********************************************************************************************************************/
/*!
 *  \brief vRpcProxy receive callout function for MaintenanceService call.
 *  \details     -
 *  \param[in]   sourceHandleId  Source of the RPC request.
 *  \param[in]   ServiceState    RPC parameter: service state.
 *  \param[in]   Service         RPC parameter: service.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     remote
 */
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
FUNC(void, VSWUPDM_CODE) vSwUpdM_vSwUpdM_GridRpc_MaintenanceService(
  vRpcProxy_SourcesIterType sourceHandleId,
  uint8 ServiceState,
  uint8 Service)
{
  vSwUpdM_NodeIterType sourceIndex = VSWUPDM_INVALID_NODE;
  Std_ReturnType result;
  vSwUpdM_GridSrvc_ServiceIdxType serviceIdx = VSWUPDM_GRIDSRVC_SERVICEIDX_UNDEFINED;

  /* #10 Get for vSwUpdM node index by vRprProxy SourceHandleId. */
  result = vSwUpdM_GridNode_GetNodeIndexFromRpcProxySource((vSwUpdM_RpcProxySourceIdType) sourceHandleId, &sourceIndex);

  /* #20 Range check input parameters. */
  if (result == E_OK)
  {
    result = vSwUpdM_GridRpc_GenericRequestPreconditionCheck(ServiceState, Service);
  }

  /* #40 Get ServiceIndex. */
  if (result == E_OK)
  {
    result = vSwUpdM_GridRpc_GetServiceIndexByService(Service, VSWUPDM_GRIDSRVC_CLASS_MAINTENANCE, &serviceIdx);
  }

  if (result == E_OK)
  {
    /* #50 Call internal function to process request. */
    (void)vSwUpdM_SrvcRouting_MaintenanceService(sourceIndex, (vSwUpdM_ExctSchedule_ServiceStateType) ServiceState, serviceIdx); /* PRQA S 4342 */ /* MD_vSwUpdM_Rule10.5_4342_EnumParameterCast */
  }
} /* vSwUpdM_vSwUpdM_GridRpc_MaintenanceService */

/**********************************************************************************************************************
 * vSwUpdM_vSwUpdM_GridRpc_SuspendService
 *********************************************************************************************************************/
/*!
 *  \brief vRpcProxy receive callout function for SuspendService call.
 *  \details     -
 *  \param[in]   sourceHandleId  Source of the RPC request.
 *  \param[in]   Service         RPC parameter: service.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     remote
 */
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(void, VSWUPDM_CODE) vSwUpdM_vSwUpdM_GridRpc_SuspendService(
  vRpcProxy_SourcesIterType sourceHandleId,
  uint8 Service)
{
  vSwUpdM_NodeIterType sourceIndex = VSWUPDM_INVALID_NODE;
  vSwUpdM_GridSrvc_ServiceIdxType serviceIdx = VSWUPDM_GRIDSRVC_SERVICEIDX_UNDEFINED;
  Std_ReturnType       result;

  /* #10 Get for vSwUpdM node index by vRprProxy SourceHandleId. */
  result = vSwUpdM_GridNode_GetNodeIndexFromRpcProxySource((vSwUpdM_RpcProxySourceIdType) sourceHandleId, &sourceIndex);

  /* #20 Range check input parameters. */
  if (result == E_OK)
  {
    result = vSwUpdM_GridRpc_GetServiceIndexByService(Service, VSWUPDM_GRIDSRVC_CLASS_SUSPEND, &serviceIdx);
  }

  /* #30 Check if initialization is already done. */
  if (result == E_OK)
  {
    if (vSwUpdM_InitState == VSWUPDM_INIT_STATE_UNINIT)
    {
      result = E_NOT_OK;
    }
  }

  if (result == E_OK)
  {
    /* #40 Call internal function to process request. */
    (void) vSwUpdM_SrvcRouting_SuspendService(sourceIndex, serviceIdx);
  }
} /* vSwUpdM_vSwUpdM_GridRpc_SuspendService */

/**********************************************************************************************************************
 * vSwUpdM_vSwUpdM_GridRpc_BkExecCommand
 *********************************************************************************************************************/
/*!
 *  \brief vRpcProxy receive callout function for BkExecCommand call.
 *  \details     -
 *  \param[in]   sourceHandleId  Source of the RPC request.
 *  \param[in]   Service         RPC parameter: command action.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     remote
 */
/*!
 *
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, VSWUPDM_CODE) vSwUpdM_vSwUpdM_GridRpc_BkExecCommand(
  vRpcProxy_SourcesIterType sourceHandleId,
  uint8 Command)
{
  vSwUpdM_NodeIterType sourceIndex = VSWUPDM_INVALID_NODE;
  Std_ReturnType       result;

  /* #10 Get for vSwUpdM node index by vRprProxy SourceHandleId. */
  result = vSwUpdM_GridNode_GetNodeIndexFromRpcProxySource((vSwUpdM_RpcProxySourceIdType) sourceHandleId, &sourceIndex);

  if (result == E_OK)
  {
    /* #20 Call internal function to process request. */
    (void) vSwUpdM_BkPersistServer_ExecCommand(sourceIndex, (vSwUpdM_BkPersist_GenericServiceCommandType)Command);  /* PRQA S 4342 */ /* MD_vSwUpdM_Rule10.5_4342_EnumParameterCast */
  }
} /* vSwUpdM_vSwUpdM_GridRpc_BkExecCommand */

/**********************************************************************************************************************
 * vSwUpdM_vSwUpdM_GridRpc_BkSetGenericParameter
 *********************************************************************************************************************/
/*!
 *  \brief vRpcProxy receive callout function for BkSetGeneric call.
 *  \details     -
 *  \param[in]   sourceHandleId  Source of the RPC request.
 *  \param[in]   Entities        RPC parameter: entities.
 *  \param[in]   ParamType       RPC parameter: parameter type.
 *  \param[in]   GenericValue    RPC parameter: generic value.
 *  \param[in]   SyncFlag        RPC parameter: sync flag.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     remote
 */
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, VSWUPDM_CODE) vSwUpdM_vSwUpdM_GridRpc_BkSetGenericParameter(
  vRpcProxy_SourcesIterType sourceHandleId,
  P2CONST(vSwUpdM_BkPersist_EntityHandleType, AUTOMATIC, VSWUPDM_APPL_VRPCPROXY_DATA) Entities,
  uint8 ParamType,
  uint32 GenericValue,
  boolean SyncFlag)
{
  vSwUpdM_NodeIterType sourceIndex = VSWUPDM_INVALID_NODE;
  Std_ReturnType       result;
  vSwUpdM_BkPersist_EntityType entitiesIds;

  /* #10 Get for vSwUpdM node index by vRprProxy SourceHandleId. */
  result = vSwUpdM_GridNode_GetNodeIndexFromRpcProxySource((vSwUpdM_RpcProxySourceIdType) sourceHandleId, &sourceIndex);

  vSwUpdM_Bookkeeper_GetIdsByHandles(Entities, &entitiesIds);

  if (result == E_OK)
  {
    /* #30 Call internal function to process request. */
    (void) vSwUpdM_BkPersistServer_SetGenericParameter(sourceIndex, &entitiesIds, (vSwUpdM_BkPersist_ParamType) ParamType, GenericValue, SyncFlag); /* PRQA S 4342 */ /* MD_vSwUpdM_Rule10.5_4342_EnumParameterCast */
  }
} /* vSwUpdM_vSwUpdM_GridRpc_BkSetGenericParameter */

/**********************************************************************************************************************
 * vSwUpdM_vSwUpdM_GridRpc_BkSetSegmentAttributes
 *********************************************************************************************************************/
/*!
 *  \brief vRpcProxy receive callout function for BkSetSegmentAttributes call.
 *  \details     -
 *  \param[in]   sourceHandleId     Source of the RPC request.
 *  \param[in]   Entities           RPC parameter: entities.
 *  \param[in]   SegmentAttributes  RPC parameter: segment attributes.
 *  \param[in]   SyncFlag           RPC parameter: sync flag.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     remote
 */
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, VSWUPDM_CODE) vSwUpdM_vSwUpdM_GridRpc_BkSetSegmentAttributes(
  vRpcProxy_SourcesIterType sourceHandleId,
  P2CONST(vSwUpdM_BkPersist_EntityHandleType, AUTOMATIC, VSWUPDM_APPL_VRPCPROXY_DATA) Entities,
  P2CONST(vSwUpdM_BkPersist_SegmentAttributesType, AUTOMATIC, VSWUPDM_APPL_VRPCPROXY_DATA) SegmentAttributes,
  boolean SyncFlag)
{
  vSwUpdM_NodeIterType sourceIndex = VSWUPDM_INVALID_NODE;
  Std_ReturnType       result;
  vSwUpdM_BkPersist_EntityType entitiesIds;

  /* #10 Get for vSwUpdM node index by vRprProxy SourceHandleId. */
  result = vSwUpdM_GridNode_GetNodeIndexFromRpcProxySource((vSwUpdM_RpcProxySourceIdType) sourceHandleId, &sourceIndex);

  vSwUpdM_Bookkeeper_GetIdsByHandles(Entities, &entitiesIds);

  if (result == E_OK)
  {
    /* #30 Call internal function to process request. */
    (void) vSwUpdM_BkPersistServer_SetSegmentAttributes(sourceIndex, &entitiesIds, SegmentAttributes, SyncFlag);
  }
} /* vSwUpdM_vSwUpdM_GridRpc_BkSetSegmentAttributes */

/**********************************************************************************************************************
 * vSwUpdM_vSwUpdM_GridRpc_BkSetResumeInfo
 *********************************************************************************************************************/
/*!
 *  \brief vRpcProxy receive callout function for BkSetResumeInfo call.
 *  \details     -
 *  \param[in]   sourceHandleId     Source of the RPC request.
 *  \param[in]   ResumeInfo         RPC parameter: resume info.
 *  \param[in]   SyncFlag           RPC parameter: sync flag.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     remote
 */
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, VSWUPDM_CODE) vSwUpdM_vSwUpdM_GridRpc_BkSetResumeInfo(
  vRpcProxy_SourcesIterType sourceHandleId,
  P2CONST(vSwUpdM_BkPersist_ResumeInfoType, AUTOMATIC, VSWUPDM_APPL_VRPCPROXY_DATA) ResumeInfo,
  boolean SyncFlag)
{
  vSwUpdM_NodeIterType sourceIndex = VSWUPDM_INVALID_NODE;
  Std_ReturnType       result;

  /* #10 Get for vSwUpdM node index by vRprProxy SourceHandleId. */
  result = vSwUpdM_GridNode_GetNodeIndexFromRpcProxySource((vSwUpdM_RpcProxySourceIdType) sourceHandleId, &sourceIndex);

  if (result == E_OK)
  {
    /* #30 Call internal function to process request. */
    (void) vSwUpdM_BkPersistServer_SetResumeInfo(sourceIndex, ResumeInfo, SyncFlag);
  }
} /* vSwUpdM_vSwUpdM_GridRpc_BkSetResumeInfo */

/**********************************************************************************************************************
 * vSwUpdM_vSwUpdM_GridRpc_BkGetGenericParameter
 *********************************************************************************************************************/
/*!
 *  \brief vRpcProxy receive callout function for BkGetGeneric call.
 *  \details     -
 *  \param[in]   sourceHandleId     Source of the RPC request.
 *  \param[in]   Entities           RPC parameter: entities.
 *  \param[in]   ParamType          RPC parameter: parameter type.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     remote
 */
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, VSWUPDM_CODE) vSwUpdM_vSwUpdM_GridRpc_BkGetGenericParameter(
  vRpcProxy_SourcesIterType sourceHandleId,
  P2CONST(vSwUpdM_BkPersist_EntityHandleType, AUTOMATIC, VSWUPDM_APPL_VRPCPROXY_DATA) Entities,
  uint8 ParamType)
{
  vSwUpdM_NodeIterType sourceIndex = VSWUPDM_INVALID_NODE;
  Std_ReturnType       result;
  vSwUpdM_BkPersist_EntityType entitiesIds;

  /* #10 Get for vSwUpdM node index by vRprProxy SourceHandleId. */
  result = vSwUpdM_GridNode_GetNodeIndexFromRpcProxySource((vSwUpdM_RpcProxySourceIdType) sourceHandleId, &sourceIndex);

  vSwUpdM_Bookkeeper_GetIdsByHandles(Entities, &entitiesIds);

  if (result == E_OK)
  {
    /* #30 Call internal function to process request. */
    (void) vSwUpdM_BkPersistServer_RequestGetGenericParameter(sourceIndex, &entitiesIds, (vSwUpdM_BkPersist_ParamType) ParamType); /* PRQA S 4342 */ /* MD_vSwUpdM_Rule10.5_4342_EnumParameterCast */
  }
} /* vSwUpdM_vSwUpdM_GridRpc_BkGetGenericParameter */

/**********************************************************************************************************************
 * vSwUpdM_vSwUpdM_GridRpc_BkGetSegmentAttributes
 *********************************************************************************************************************/
/*!
 *  \brief vRpcProxy receive callout function for BkGetSegmentAttributes call.
 *  \details     -
 *  \param[in]   sourceHandleId     Source of the RPC request.
 *  \param[in]   Entities           RPC parameter: entities.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     remote
 */
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, VSWUPDM_CODE) vSwUpdM_vSwUpdM_GridRpc_BkGetSegmentAttributes(
  vRpcProxy_SourcesIterType sourceHandleId,
  P2CONST(vSwUpdM_BkPersist_EntityHandleType, AUTOMATIC, VSWUPDM_APPL_VRPCPROXY_DATA) Entities)
{
  vSwUpdM_NodeIterType sourceIndex = VSWUPDM_INVALID_NODE;
  Std_ReturnType       result;
  vSwUpdM_BkPersist_EntityType entitiesIds;

  /* #10 Get for vSwUpdM node index by vRprProxy SourceHandleId. */
  result = vSwUpdM_GridNode_GetNodeIndexFromRpcProxySource((vSwUpdM_RpcProxySourceIdType) sourceHandleId, &sourceIndex);

  vSwUpdM_Bookkeeper_GetIdsByHandles(Entities, &entitiesIds);
  if (result == E_OK)
  {
    /* #30 Call internal function to process request. */
    (void) vSwUpdM_BkPersistServer_RequestGetSegmentAttributes(sourceIndex, &entitiesIds);
  }
} /* vSwUpdM_vSwUpdM_GridRpc_BkGetSegmentAttributes */

/**********************************************************************************************************************
 * vSwUpdM_vSwUpdM_GridRpc_BkGetResumeInfo
 *********************************************************************************************************************/
/*!
 *  \brief vRpcProxy receive callout function for BkGetResumeInfo call.
 *  \details     -
 *  \param[in]   sourceHandleId     Source of the RPC request.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     remote
 */
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, VSWUPDM_CODE) vSwUpdM_vSwUpdM_GridRpc_BkGetResumeInfo(
  vRpcProxy_SourcesIterType sourceHandleId)
{
  vSwUpdM_NodeIterType sourceIndex = VSWUPDM_INVALID_NODE;
  Std_ReturnType       result;

  /* #10 Get for vSwUpdM node index by vRprProxy SourceHandleId. */
  result = vSwUpdM_GridNode_GetNodeIndexFromRpcProxySource((vSwUpdM_RpcProxySourceIdType) sourceHandleId, &sourceIndex);

  if (result == E_OK)
  {
    /* #30 Call internal function to process request. */
    (void) vSwUpdM_BkPersistServer_RequestGetResumeInfo(sourceIndex);
  }
} /* vSwUpdM_vSwUpdM_GridRpc_BkGetResumeInfo */

/**********************************************************************************************************************
 * vSwUpdM_vSwUpdM_RemoteConfirmation
 *********************************************************************************************************************/
/*!
 *  \brief vRpcProxy receive callout function for Confirmation call.
 *  \details     -
 *  \param[in]   sourceHandleId         Source of the response.
 *  \param[in]   targetHandleId         Target of the initial request.
 *  \param[in]   responseOfServiceId    ServiceId of the initial request.
 *  \param[in]   serviceExecutionStatus Legacy, will be removed by further vRpcProxy version.
 *  \param[in]   ServiceId              ServiceId of the request.
 *  \param[in]   Result                 Result of the request.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     remote
 */
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
FUNC(void, VSWUPDM_CODE) vSwUpdM_vSwUpdM_RemoteConfirmation(
  vRpcProxy_SourcesIterType sourceHandleId,
  vRpcProxy_CTargetsIterType targetHandleId,
  uint16 responseOfServiceId,
  uint8 serviceExecutionStatus,
  uint8 ServiceId,
  uint8 Result)
{
  Std_ReturnType result;

  vSwUpdM_NodeIterType nodeIndex = VSWUPDM_INVALID_NODE;
  vSwUpdM_GridSrvc_ServiceIdxType serviceIdx  = VSWUPDM_GRIDSRVC_SERVICEIDX_UNDEFINED;

  VSWUPDM_DUMMY_STATEMENT(targetHandleId);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(responseOfServiceId);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(serviceExecutionStatus);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  /* #10 If Legacy handling:
    *      Check if source of confirmation is known.
    *      Legacy services use only default channel. */
  result = vSwUpdM_GridNode_GetNodeIndexFromRpcProxySourceAndChannel((vSwUpdM_RpcProxySourceIdType) sourceHandleId, VSWUPDM_GRIDCHANNEL_CHANNELIDX_MAIN, &nodeIndex);

  /* #20 Get ServiceIdx. */
  if (result == E_OK)
  {
    result = vSwUpdM_GridRpc_GetServiceIndexByResponseService(ServiceId, VSWUPDM_GRIDSRVC_RESPONSECLASS_LEGACY, &serviceIdx);
  }

  /* #30 Store response for further processing. */
  if (result == E_OK)
  {
    vSwUpdM_RemoteProcessResponse(nodeIndex, serviceIdx, Result);
  }

  /* PRQA S 6060 1 */ /* MD_MSR_STPAR */
} /* vSwUpdM_vSwUpdM_RemoteConfirmation */ /* PRQA S 6010, 6030, 6050, 6080 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */

/**********************************************************************************************************************
 * vSwUpdM_vSwUpdM_GridRpc_MainConfirmation
 *********************************************************************************************************************/
/*!
 *  \brief vRpcProxy receive callout function for MainChannel Confirmation call.
 *  \details     -
 *  \param[in]   sourceHandleId         Source of the response.
 *  \param[in]   targetHandleId         Target of the initial request.
 *  \param[in]   responseOfServiceId    ServiceId of the initial request.
 *  \param[in]   serviceExecutionStatus Legacy, will be removed by further vRpcProxy version.
 *  \param[in]   ServiceId              Id of the confirmed service.
 *  \param[in]   ServiceResult          Result of the confirmed service
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     remote
 */
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(void, VSWUPDM_CODE) vSwUpdM_vSwUpdM_GridRpc_MainConfirmation(
  vRpcProxy_SourcesIterType sourceHandleId,
  vRpcProxy_CTargetsIterType targetHandleId,
  uint16 responseOfServiceId,
  uint8 serviceExecutionStatus,
  uint8 ServiceId,
  uint8 ServiceResult)
{
  VSWUPDM_DUMMY_STATEMENT(targetHandleId);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(responseOfServiceId);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(serviceExecutionStatus);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  /* Call helper function: */
  vSwUpdM_GridRpc_HandleConfirmation(VSWUPDM_GRIDCHANNEL_CHANNELIDX_MAIN, VSWUPDM_GRIDSRVC_RESPONSECLASS_MAIN, sourceHandleId, ServiceId, ServiceResult);

  /* PRQA S 6060 1 */ /* MD_MSR_STPAR */
} /* vSwUpdM_vSwUpdM_GridRpc_MainConfirmation */

/**********************************************************************************************************************
 * vSwUpdM_vSwUpdM_GridRpc_MaintenanceConfirmation
 *********************************************************************************************************************/
/*!
 *  \brief vRpcProxy receive callout function for MaintenanceChannel Confirmation call.
 *  \details     -
 *  \param[in]   sourceHandleId         Source of the response.
 *  \param[in]   targetHandleId         Target of the initial request.
 *  \param[in]   responseOfServiceId    ServiceId of the initial request.
 *  \param[in]   serviceExecutionStatus Legacy, will be removed by further vRpcProxy version.
 *  \param[in]   ServiceId              Id of the confirmed service.
 *  \param[in]   ServiceResult          Result of the confirmed service
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     remote
 */
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(void, VSWUPDM_CODE) vSwUpdM_vSwUpdM_GridRpc_MaintenanceConfirmation(
  vRpcProxy_SourcesIterType sourceHandleId,
  vRpcProxy_CTargetsIterType targetHandleId,
  uint16 responseOfServiceId,
  uint8 serviceExecutionStatus,
  uint8 ServiceId,
  uint8 ServiceResult)
{
  VSWUPDM_DUMMY_STATEMENT(targetHandleId);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(responseOfServiceId);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(serviceExecutionStatus);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  /* Call helper function: */
  vSwUpdM_GridRpc_HandleConfirmation(VSWUPDM_GRIDCHANNEL_CHANNELIDX_MAINTENANCE, VSWUPDM_GRIDSRVC_RESPONSECLASS_MAINTENANCE, sourceHandleId, ServiceId, ServiceResult);

  /* PRQA S 6060 1 */ /* MD_MSR_STPAR */
} /* vSwUpdM_vSwUpdM_GridRpc_MaintenanceConfirmation */

/**********************************************************************************************************************
 * vSwUpdM_vSwUpdM_GridRpc_SuspendConfirmation
 *********************************************************************************************************************/
/*!
 *  \brief vRpcProxy receive callout function for SuspendChannel Confirmation call.
 *  \details     -
 *  \param[in]   sourceHandleId         Source of the response.
 *  \param[in]   targetHandleId         Target of the initial request.
 *  \param[in]   responseOfServiceId    ServiceId of the initial request.
 *  \param[in]   serviceExecutionStatus Legacy, will be removed by further vRpcProxy version.
 *  \param[in]   ServiceId              Id of the confirmed service.
 *  \param[in]   ServiceResult          Result of the confirmed service.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     remote
 */
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(void, VSWUPDM_CODE) vSwUpdM_vSwUpdM_GridRpc_SuspendConfirmation(
  vRpcProxy_SourcesIterType sourceHandleId,
  vRpcProxy_CTargetsIterType targetHandleId,
  uint16 responseOfServiceId,
  uint8 serviceExecutionStatus,
  uint8 ServiceId,
  uint8 ServiceResult)
{
  VSWUPDM_DUMMY_STATEMENT(targetHandleId);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(responseOfServiceId);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(serviceExecutionStatus);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  /* Call helper function: */
  vSwUpdM_GridRpc_HandleConfirmation(VSWUPDM_GRIDCHANNEL_CHANNELIDX_SUSPEND, VSWUPDM_GRIDSRVC_RESPONSECLASS_SUSPEND, sourceHandleId, ServiceId, ServiceResult);

  /* PRQA S 6060 1 */ /* MD_MSR_STPAR */
} /* vSwUpdM_vSwUpdM_GridRpc_SuspendConfirmation */

/**********************************************************************************************************************
 * vSwUpdM_vSwUpdM_GridRpc_BookkeeperConfirmation
 *********************************************************************************************************************/
/*!
 *  \brief vRpcProxy receive callout function for BookkeeperChannel Confirmation call.
 *  \details     -
 *  \param[in]   sourceHandleId         Source of the response.
 *  \param[in]   targetHandleId         Target of the initial request.
 *  \param[in]   responseOfServiceId    ServiceId of the initial request.
 *  \param[in]   serviceExecutionStatus Legacy, will be removed by further vRpcProxy version.
 *  \param[in]   ServiceId              Id of the confirmed service.
 *  \param[in]   ServiceResult          Result of the confirmed service.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     remote
 */
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(void, VSWUPDM_CODE) vSwUpdM_vSwUpdM_GridRpc_BookkeeperConfirmation(
  vRpcProxy_SourcesIterType sourceHandleId,
  vRpcProxy_CTargetsIterType targetHandleId,
  uint16 responseOfServiceId,
  uint8 serviceExecutionStatus,
  uint8 ServiceId,
  uint8 ServiceResult)
{
  VSWUPDM_DUMMY_STATEMENT(targetHandleId);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(responseOfServiceId);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(serviceExecutionStatus);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  /* Call helper function: */
  vSwUpdM_GridRpc_HandleConfirmation(VSWUPDM_GRIDCHANNEL_CHANNELIDX_BOOKKEEPER, VSWUPDM_GRIDSRVC_RESPONSECLASS_BK, sourceHandleId, ServiceId, ServiceResult);

  /* PRQA S 6060 1 */ /* MD_MSR_STPAR */
} /* vSwUpdM_vSwUpdM_GridRpc_BookkeeperConfirmation */

/**********************************************************************************************************************
 * vSwUpdM_vSwUpdM_GridRpc_BkGetGenericParameterResponse
 *********************************************************************************************************************/
/*!
 *  \brief vRpcProxy receive callout function for BookkeeperChannel Confirmation call.
 *  \details     -
 *  \param[in]   sourceHandleId         Source of the response.
 *  \param[in]   targetHandleId         Target of the initial request.
 *  \param[in]   responseOfServiceId    ServiceId of the initial request.
 *  \param[in]   serviceExecutionStatus Legacy, will be removed by further vRpcProxy version. *  \param[in]   ServiceId     Id of the confirmed service.
 *  \param[in]   Result                 Result of the confirmed service.
 *  \param[in]   GenericValue           Generic value of the confirmed service.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     remote
 */
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(void, VSWUPDM_CODE) vSwUpdM_vSwUpdM_GridRpc_BkGetGenericParameterResponse(
  vRpcProxy_SourcesIterType sourceHandleId,
  vRpcProxy_CTargetsIterType targetHandleId,
  uint16 responseOfServiceId,
  uint8 serviceExecutionStatus,
  uint8 Result,
  uint32 GenericValue)
{
  vSwUpdM_NodeIterType nodeIndex;
  Std_ReturnType retVal;
  vSwUpdM_GridRpc_ComplexResponseClassBkGetGenericType responseClass;

  VSWUPDM_DUMMY_STATEMENT(targetHandleId);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(responseOfServiceId);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(serviceExecutionStatus);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  retVal = vSwUpdM_GridNode_GetNodeIndexFromRpcProxySourceAndChannel((vSwUpdM_RpcProxySourceIdType) sourceHandleId, VSWUPDM_GRIDCHANNEL_CHANNELIDX_BOOKKEEPER, &nodeIndex);

  if (retVal == E_OK)
  {
    /* Pack response for generic response processing. */
    vSwUpdM_GridRpc_InitComplexResponseClassBkGetGenericType(VSWUPDM_GRIDSRVC_SERVICEIDX_BK_GET_GENERIC_PARAMETER, Result, GenericValue, &responseClass);

    /* Future vRpcProxy will evaluate return value. */
    (void) vSwUpdM_GridChannel_ProcessConfirmation(VSWUPDM_GRIDCHANNEL_CHANNELIDX_BOOKKEEPER, nodeIndex, (vSwUpdM_GridRpc_ComplexResponseClassBasePtrType) &responseClass); /* PRQA S 0310, 4342 */ /* MD_vSwUpdM_Rule11.3_0310_ServiceParameterCast, MD_vSwUpdM_Rule10.5_4342_EnumParameterCast */
  }

  /* PRQA S 6060 1 */ /* MD_MSR_STPAR */
} /* vSwUpdM_vSwUpdM_GridRpc_BkGetGenericParameterResponse */

/**********************************************************************************************************************
 * vSwUpdM_vSwUpdM_GridRpc_BkGetSegmentAttributesResponse
 *********************************************************************************************************************/
/*!
 *  \brief vRpcProxy receive callout function for BookkeeperChannel Confirmation call.
 *  \details     -
 *  \param[in]   sourceHandleId         Source of the response.
 *  \param[in]   targetHandleId         Target of the initial request.
 *  \param[in]   responseOfServiceId    ServiceId of the initial request.
 *  \param[in]   serviceExecutionStatus Legacy, will be removed by further vRpcProxy version.
 *  \param[in]   Result                 Result of the confirmed service.
 *  \param[in]   SegmentAttributes      SegmentAttributes.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     remote
 */
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(void, VSWUPDM_CODE) vSwUpdM_vSwUpdM_GridRpc_BkGetSegmentAttributesResponse(
  vRpcProxy_SourcesIterType sourceHandleId,
  vRpcProxy_CTargetsIterType targetHandleId,
  uint16 responseOfServiceId,
  uint8 serviceExecutionStatus,
  uint8 Result,
  P2CONST(vSwUpdM_BkPersist_SegmentAttributesType, AUTOMATIC, VSWUPDM_APPL_VRPCPROXY_DATA) SegmentAttributes)
{
  vSwUpdM_NodeIterType nodeIndex;
  Std_ReturnType retVal;
  vSwUpdM_GridRpc_ComplexResponseClassBkGetSegmentAttributesType responseClass;

  VSWUPDM_DUMMY_STATEMENT(targetHandleId);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(responseOfServiceId);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(serviceExecutionStatus);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  retVal = vSwUpdM_GridNode_GetNodeIndexFromRpcProxySourceAndChannel((vSwUpdM_RpcProxySourceIdType) sourceHandleId, VSWUPDM_GRIDCHANNEL_CHANNELIDX_BOOKKEEPER, &nodeIndex);

  if (retVal == E_OK)
  {
    /* Pack response for generic response processing. */
    vSwUpdM_GridRpc_InitComplexResponseClassBkGetSegmentAttributesType(VSWUPDM_GRIDSRVC_SERVICEIDX_BK_GET_SEGMENT_ATTRIBUTES, Result, SegmentAttributes, &responseClass);

    /* Future vRpcProxy will evaluate return value. */
    (void) vSwUpdM_GridChannel_ProcessConfirmation(VSWUPDM_GRIDCHANNEL_CHANNELIDX_BOOKKEEPER, nodeIndex, (vSwUpdM_GridRpc_ComplexResponseClassBasePtrType) &responseClass); /* PRQA S 0310, 4342 */ /* MD_vSwUpdM_Rule11.3_0310_ServiceParameterCast, MD_vSwUpdM_Rule10.5_4342_EnumParameterCast */
  }

  /* PRQA S 6060 1 */ /* MD_MSR_STPAR */
} /* vSwUpdM_vSwUpdM_GridRpc_BkGetSegmentAttributesResponse */

/**********************************************************************************************************************
 * vSwUpdM_vSwUpdM_GridRpc_BkGetResumeInfoResponse
 *********************************************************************************************************************/
/*!
 *  \brief vRpcProxy receive callout function for BookkeeperChannel Confirmation call.
 *  \details     -
 *  \param[in]   sourceHandleId         Source of the response.
 *  \param[in]   targetHandleId         Target of the initial request.
 *  \param[in]   responseOfServiceId    ServiceId of the initial request.
 *  \param[in]   serviceExecutionStatus Legacy, will be removed by further vRpcProxy version.
 *  \param[in]   Result                 Result of the confirmed service.
 *  \param[in]   ResumeInfo             ResumeInfo.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     remote
 */
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(void, VSWUPDM_CODE) vSwUpdM_vSwUpdM_GridRpc_BkGetResumeInfoResponse(
  vRpcProxy_SourcesIterType sourceHandleId,
  vRpcProxy_CTargetsIterType targetHandleId,
  uint16 responseOfServiceId,
  uint8 serviceExecutionStatus,
  uint8 Result,
  P2CONST(vSwUpdM_BkPersist_ResumeInfoType, AUTOMATIC, VSWUPDM_APPL_VRPCPROXY_DATA) ResumeInfo)
{
  vSwUpdM_NodeIterType nodeIndex = VSWUPDM_INVALID_NODE;
  Std_ReturnType retVal;
  vSwUpdM_GridRpc_ComplexResponseClassBkGetResumeInfoType responseClass;

  VSWUPDM_DUMMY_STATEMENT(targetHandleId);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(responseOfServiceId);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(serviceExecutionStatus);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  retVal = vSwUpdM_GridNode_GetNodeIndexFromRpcProxySourceAndChannel((vSwUpdM_RpcProxySourceIdType) sourceHandleId, VSWUPDM_GRIDCHANNEL_CHANNELIDX_BOOKKEEPER, &nodeIndex);

  if (retVal == E_OK)
  {
    /* Pack response for generic response processing. */
    vSwUpdM_GridRpc_InitComplexResponseClassBkGetResumeInfoType(VSWUPDM_GRIDSRVC_SERVICEIDX_BK_GET_RESUME_INFO, Result, ResumeInfo, &responseClass);

    /* Future vRpcProxy will evaluate return value. */
    (void) vSwUpdM_GridChannel_ProcessConfirmation(VSWUPDM_GRIDCHANNEL_CHANNELIDX_BOOKKEEPER, nodeIndex, (vSwUpdM_GridRpc_ComplexResponseClassBasePtrType) &responseClass); /* PRQA S 0310, 4342 */ /* MD_vSwUpdM_Rule11.3_0310_ServiceParameterCast, MD_vSwUpdM_Rule10.5_4342_EnumParameterCast */
  }
  /* PRQA S 6060 1 */ /* MD_MSR_STPAR */
} /* vSwUpdM_vSwUpdM_GridRpc_BkGetResumeInfoResponse */

/**********************************************************************************************************************
 vSwUpdM_vSwUpdM_RemoteCopyStreamData
 *********************************************************************************************************************/
/*!
 *  \brief vRpcProxy receive callout function for CopyStreamData call.
 *  \details     -
 *  \param[in]   sourceHandleId   Source of the request.
 *  \param[in]   Length           Copy length.
 *  \param[in]   Offset           Copy offset.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     remote
 */
/*!
 *
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, VSWUPDM_CODE) vSwUpdM_vSwUpdM_RemoteCopyStreamData(
  vRpcProxy_SourcesIterType sourceHandleId,
  uint32 Length,
  uint32 Offset)
{
  vSwUpdM_NodeIterType sourceIndex = VSWUPDM_INVALID_NODE;
  Std_ReturnType           result;

  VSWUPDM_DUMMY_STATEMENT(Offset); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  /* #10 Get vSwUpdM node index by vRprProxy SourceHandleId and check if requester is allowed. */
  result = vSwUpdM_GridRpc_RemotePrepareRequestProcessing((vSwUpdM_RpcProxySourceIdType) sourceHandleId, &sourceIndex);

  if (result == E_OK)
  {
    /* #20 Set flag to indicate reception of message. */
    vSwUpdM_SetServiceIdOfResponseOfVarNode(sourceIndex, (uint8) VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_COPY_STREAM_DATA);
    vSwUpdM_SetLengthOfResponseOfVarNode(sourceIndex, Length);
    vSwUpdM_SetResponseValidOfVarNode(sourceIndex, TRUE);
  }
} /* vSwUpdM_vSwUpdM_RemoteCopyStreamData */

/**********************************************************************************************************************
 vSwUpdM_vSwUpdM_RemoteStreamRequest
 *********************************************************************************************************************/
/*!
 *  \brief vRpcProxy receive callout function for StreamRequest call.
 *  \details     -
 *  \param[in]   sourceHandleId  Source of the request.
 *  \param[in]   ProcessHandle   Handle of DataProcess.
 *  \param[in]   Handle          Handle of RemoteStream.
 *  \param[in]   Result          Result of previous request.
 *  \param[in]   BufferSize      Available buffer size on receives side.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     remote
 */
/*!
 *
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, VSWUPDM_CODE) vSwUpdM_vSwUpdM_RemoteStreamRequest(
  vRpcProxy_SourcesIterType sourceHandleId,
  uint8 ProcessHandle,
  uint8 Handle,
  uint8 Result,
  uint32 BufferSize)
{
  vSwUpdM_NodeIterType sourceIndex = VSWUPDM_INVALID_NODE;
  Std_ReturnType       result;

  /* #10 Get vSwUpdM node index by vRprProxy SourceHandleId and check if requester is allowed. */
  result = vSwUpdM_GridRpc_RemotePrepareRequestProcessing((vSwUpdM_RpcProxySourceIdType) sourceHandleId, &sourceIndex);

  if (result == E_OK)
  {
    /* #20 Call internal function to process request. */
    (void) vSwUpdM_SrvcRouting_RemoteStreamRequest(sourceIndex, ProcessHandle, Handle, Result, BufferSize);
  }
} /* vSwUpdM_vSwUpdM_RemoteStreamRequest */

/**********************************************************************************************************************
 vSwUpdM_vSwUpdM_RemoteStreamEnd
 *********************************************************************************************************************/
/*!
 *  \brief vRpcProxy receive callout function for StreamEnd call.
 *  \details     -
 *  \param[in]   sourceHandleId         Source of the response.
 *  \param[in]   targetHandleId         Target of the initial request.
 *  \param[in]   responseOfServiceId    ServiceId of the initial request.
 *  \param[in]   serviceExecutionStatus Legacy, will be removed by further vRpcProxy version.
 *  \param[in]   ProcessHandle          Handle of DataProcess.
 *  \param[in]   Handle                 Handle of RemoteStream.
 *  \param[in]   Result                 Result of previous request.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     remote
 */
/*!
 *
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, VSWUPDM_CODE) vSwUpdM_vSwUpdM_RemoteStreamEnd(
  vRpcProxy_SourcesIterType sourceHandleId,
  vRpcProxy_CTargetsIterType targetHandleId,
  uint16 responseOfServiceId,
  uint8 serviceExecutionStatus,
  uint8 ProcessHandle,
  uint8 Handle,
  uint8 Result)
{
  vSwUpdM_NodeIterType sourceIndex = VSWUPDM_INVALID_NODE;
  Std_ReturnType       result;

  VSWUPDM_DUMMY_STATEMENT(targetHandleId);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(responseOfServiceId);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(serviceExecutionStatus);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  /* #10 Get vSwUpdM node index by vRprProxy SourceHandleId and check if requester is allowed. */
  result = vSwUpdM_GridRpc_RemotePrepareRequestProcessing((vSwUpdM_RpcProxySourceIdType) sourceHandleId, &sourceIndex);

  if (result == E_OK)
  {
    /* #20 Call internal function to process request. */
    (void) vSwUpdM_SrvcRouting_RemoteStreamEnd(sourceIndex, ProcessHandle, Handle, Result);
  }
  /* PRQA S 6060 1 */ /* MD_MSR_STPAR */
} /* vSwUpdM_vSwUpdM_RemoteStreamEnd */

/**********************************************************************************************************************
 * vSwUpdM_GridRpc_ServiceStatusIndication
 *********************************************************************************************************************/
/*!
 *  \brief vRpcProxy status indication callout function. Specified by vRpcProxy component.
 *  \details     -
 *  \param[in]   ServiceId      Service ID of indication.
 *  \param[in]   TargetId       TxTarget ID
 *  \param[in]   TargetGroupId  TxTarget group ID
 *  \param[in]   Result         Current result.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     remote
 */
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
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(void, VSWUPDM_CODE) vSwUpdM_GridRpc_ServiceStatusIndication(
  uint16 ServiceId,
  uint8 TargetId,
  uint8 TargetGroupId,
  TxService_StatusType Result)
{
  vSwUpdM_RpcProxyServiceIdType remoteServiceId = (vSwUpdM_RpcProxyServiceIdType) ServiceId;
  vSwUpdM_GridSrvc_ServiceIdxType serviceIndex = VSWUPDM_GRIDSRVC_SERVICEIDX_UNDEFINED;

  VSWUPDM_DUMMY_STATEMENT(TargetGroupId);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  if (vSwUpdM_GridRpc_GetServiceByRpcProxyRequestService(remoteServiceId, &serviceIndex) == E_OK)
  {
    /* #10 Check if legacy handling required for given service: */
    if (vSwUpdM_GridSrvc_ServiceHandlingIsLegacy(serviceIndex) == TRUE)
    {
      /* #100 If LegacyHandling:
       *      Map vRpcProxy error codes to vSwUpdM error codes. */
      vSwUpdM_GridRpc_LegacyServiceErrorHandling(TargetId, serviceIndex, Result);
    }
    else   /* End legacy handling */
    {
      vSwUpdM_NodeIterType nodeIndex = VSWUPDM_INVALID_NODE;
      vSwUpdM_GridChannel_ChannelIdxType channelIndex = vSwUpdM_GridSrvc_GetChannelOfService(serviceIndex);
      Std_ReturnType result;
      vSwUpdM_GridChannel_ServiceStateType serviceState = VSWUPDM_GRIDCHANNEL_SERVICESTATE_UNUSED; /* PRQA S 2981 */ /* MD_vSwUpdM_Rule2.2_2981_2892_RedundantInitialization */

      /* #200 Otherwise:
       * Get Node by given (Service, TargetId). */
      result = vSwUpdM_GridNode_GetNodeIndexFromRpcProxyTargetAndChannel(TargetId, channelIndex, &nodeIndex);

      /* #210 Map vRpcProxy error codes to vSwUpdM error codes. */
      serviceState = vSwUpdM_GridRpc_GetServiceStateFromRpcProxyError(Result);

      /* #220 Store serviceState for aggregation. */
      if (result == E_OK)
      {
        vSwUpdM_GridChannel_StoreResponseServiceState(channelIndex, nodeIndex, vSwUpdM_GridChannel_GetService(channelIndex), serviceState);
      }
    }
  }
  /* PRQA S 6010, 6030, 6050, 6080 1 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */
} /* vSwUpdM_GridRpc_ServiceStatusIndication */

#endif /* (VSWUPDM_MULTICONTROLLER_SUPPORT == STD_ON) */

/*********************
 * GRID SERVICES
 ********************/

/**********************************************************************************************************************
 * vSwUpdM_GridSrvc_Init
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(void, VSWUPDM_CODE) vSwUpdM_GridSrvc_Init(void)
{
  vSwUpdM_GridSrvc_GridState = VSWUPDM_GRIDSRVC_GRIDSTATE_UNLOCKED;
} /* vSwUpdM_GridSrvc_Init */
/**********************************************************************************************************************
 * vSwUpdM_GridSrvc_Open
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(void, VSWUPDM_CODE) vSwUpdM_GridSrvc_Open(
  vSwUpdM_NodeGroupIterType Destination
)
{
  if (vSwUpdM_GridSrvc_GridState == VSWUPDM_GRIDSRVC_GRIDSTATE_UNLOCKED )
  {
    vSwUpdM_GridSrvc_GridState = VSWUPDM_GRIDSRVC_GRIDSTATE_LOCK_REQUEST;
  }
  else
  {
    vSwUpdM_GridSrvc_GridState = VSWUPDM_GRIDSRVC_GRIDSTATE_CLEANUP;
  }
  vSwUpdM_GridSrvc_HandleCommunicationState(Destination);
} /* vSwUpdM_GridSrvc_Open */

/**********************************************************************************************************************
 * vSwUpdM_GridSrvc_FinishOpen
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(vSwUpdM_GridSrvc_GridStateType, VSWUPDM_CODE) vSwUpdM_GridSrvc_GetCommunicationState(void)
{
  vSwUpdM_GridSrvc_HandleCommunicationState(vSwUpdM_GridChannel_GetDestination(VSWUPDM_GRIDCHANNEL_CHANNELIDX_MAINTENANCE));

  return vSwUpdM_GridSrvc_GridState;
} /* vSwUpdM_GridSrvc_FinishOpen */

/**********************************************************************************************************************
 * vSwUpdM_GridSrvc_Close
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(void, VSWUPDM_CODE) vSwUpdM_GridSrvc_Close(vSwUpdM_NodeGroupIterType Destination)
{
  vSwUpdM_GridSrvc_GridState = VSWUPDM_GRIDSRVC_GRIDSTATE_UNLOCK_REQUEST;
  vSwUpdM_GridSrvc_HandleCommunicationState(Destination);
} /* vSwUpdM_GridSrvc_Close */

/**********************************************************************************************************************
 * vSwUpdM_GridSrvc_Register
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */

FUNC(void, VSWUPDM_CODE) vSwUpdM_GridSrvc_Register(
  vSwUpdM_GridSrvc_ServiceIdxType ServiceIndex,
  vSwUpdM_GridSrvc_ServiceClassBasePtrPtrType Parameter) /* PRQA S 3673 */ /* MD_vSwUpdM_Rule8.13_3673_PointerToConstParameter */
{
  vSwUpdM_GridChannel_ChannelIdxType channelIndex = vSwUpdM_GridSrvc_GetChannelOfService(ServiceIndex);

  vSwUpdM_GridChannel_GetRequestBuffer(channelIndex, Parameter);
} /* vSwUpdM_GridSrvc_Register */

/**********************************************************************************************************************
 * vSwUpdM_GridSrvc_Start
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

FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GridSrvc_Start(
  vSwUpdM_NodeGroupIterType Destination,
  vSwUpdM_GridSrvc_ServiceIdxType ServiceIndex)
{
  Std_ReturnType retVal;
  vSwUpdM_GridSrvc_ServiceClassBasePtrType parameter = NULL_PTR;
  vSwUpdM_GridChannel_ChannelIdxType channelIndex = vSwUpdM_GridSrvc_GetChannelOfService(ServiceIndex);

  /* #10 Prepare reception of responses. */
  vSwUpdM_GridChannel_Prepare(channelIndex, ServiceIndex, Destination);

  vSwUpdM_GridChannel_GetRequestBuffer(channelIndex, &parameter);

  /* #20 Trigger RPC. */
  retVal = vSwUpdM_GridRpcStub_RemoteProcedureCall(vSwUpdM_GridChannel_GetDestination(channelIndex), ServiceIndex, parameter);

  /* #30 If RPC fails (e.g. due to communication issue):
   *       Clear channel. */
  if (retVal != E_OK)
  {
    vSwUpdM_GridChannel_SetState(vSwUpdM_GridSrvc_GetChannelOfService(ServiceIndex), VSWUPDM_GRIDCHANNEL_STATE_IDLE);
  }

  return retVal;
} /* vSwUpdM_GridSrvc_Start */

/**********************************************************************************************************************
 * vSwUpdM_GridSrvc_GetAggregatedResult
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
 *
 *
 *
 *
 *
 */

FUNC(vSwUpdM_GridSrvc_AggregateResultType, VSWUPDM_CODE) vSwUpdM_GridSrvc_GetAggregatedResult(
  vSwUpdM_GridSrvc_ServiceIdxType ServiceIndex,
  P2VAR(vSwUpdM_GridSrvc_ResponseClassSimpleResponsePtrType, AUTOMATIC, VSWUPDM_APPL_VAR) Result)
{
  vSwUpdM_GridSrvc_AggregateResultType retVal = VSWUPDM_GRIDSRVC_AGGREGATERESULT_PENDING;
  vSwUpdM_GridChannel_ChannelIdxType channelIndex = vSwUpdM_GridSrvc_GetChannelOfService(ServiceIndex);
  vSwUpdM_NodeGroupIterType destination = vSwUpdM_GridChannel_GetDestination(channelIndex);
  vSwUpdM_NodeGroup2NodeIndIterType nodeIndIndex;
  boolean isGood = TRUE;
  boolean isDirty = FALSE;

  /* #10 If new information available:
   *     Reset global flag. */

  VSWUPDM_ENTER_CRITICAL_SECTION();
  if (vSwUpdM_GridChannel_GetAggregatedResultDirty(channelIndex) == TRUE)
  {
    vSwUpdM_GridChannel_SetAggregatedResultDirty(channelIndex, FALSE);
    isDirty = TRUE;
  }
  VSWUPDM_LEAVE_CRITICAL_SECTION();

  if (isDirty == TRUE)
  {
    /* #100 Aggregate result:
     *      Reset aggregation buffer. */
    vSwUpdM_GridChannel_ClearAggregatedResult(channelIndex);

    /* #110 Check for each node that is requested: */
    for (nodeIndIndex = vSwUpdM_GetNodeGroup2NodeIndStartIdxOfNodeGroup(destination);
         nodeIndIndex < vSwUpdM_GetNodeGroup2NodeIndEndIdxOfNodeGroup(destination); nodeIndIndex++)
    {
      vSwUpdM_NodeIterType nodeIndex = vSwUpdM_GetNodeGroup2NodeInd(nodeIndIndex);

      /* #120 If pending result is available:
       *      Aggregate it. */
      if (vSwUpdM_GridNode_GetResultValid(ServiceIndex, nodeIndex) == TRUE)
      {
          /* Aggregate until negative result appears - first negative result is reported. */
        if (isGood == TRUE)
        {
          Std_ReturnType result = vSwUpdM_GridNode_GetResult(ServiceIndex, nodeIndex);
          vSwUpdM_GridChannel_SetAggregatedResult(channelIndex, result);
          if (result != E_OK)
          {
            isGood = FALSE;
          }
        }
        vSwUpdM_GridChannel_IncResponseCount(channelIndex);
      }
      else
      {
        /* #130 Otherwise:
         *      Check for remote transmission error. */
        switch (vSwUpdM_GridNode_GetServiceState(ServiceIndex, nodeIndex))
        {
          default:
          case VSWUPDM_GRIDCHANNEL_SERVICESTATE_INITIAL:
          case VSWUPDM_GRIDCHANNEL_SERVICESTATE_ACK:
          {
            /* Nothing to do. */
            break;
          }
          case VSWUPDM_GRIDCHANNEL_SERVICESTATE_TX_TP_ERROR:
          {
            if (isGood == TRUE)
            {
              vSwUpdM_GridChannel_SetAggregatedResultToErrorCondition(channelIndex, VSWUPDM_E_REMOTE_LOCAL_TX_TP_ERROR);
              isGood = FALSE;
            }
            vSwUpdM_GridChannel_IncResponseCount(channelIndex);
            break;
          }
          case VSWUPDM_GRIDCHANNEL_SERVICESTATE_NACK:
          {
            if (isGood == TRUE)
            {
              vSwUpdM_GridChannel_SetAggregatedResultToErrorCondition(channelIndex, VSWUPDM_E_REMOTE_NEGATIVE_ACK);
              isGood = FALSE;
            }
            vSwUpdM_GridChannel_IncResponseCount(channelIndex);
            break;
          }
          case VSWUPDM_GRIDCHANNEL_SERVICESTATE_ACK_TIMEOUT:
          {
            if (isGood == TRUE)
            {
              vSwUpdM_GridChannel_SetAggregatedResultToErrorCondition(channelIndex, VSWUPDM_E_REMOTE_ACK_TIMEOUT);
              isGood = FALSE;
            }
            vSwUpdM_GridChannel_IncResponseCount(channelIndex);
            break;
          }
          case VSWUPDM_GRIDCHANNEL_SERVICESTATE_RESPONSE_TIMEOUT:
          {
            if (isGood == TRUE)
            {
              vSwUpdM_GridChannel_SetAggregatedResultToErrorCondition(channelIndex, VSWUPDM_E_REMOTE_RESPONSE_TIMEOUT);
              isGood = FALSE;
            }
            vSwUpdM_GridChannel_IncResponseCount(channelIndex);
            break;
          }
        }
      }
    }
  }

  /* This is legacy: Local node should respond like remote nodes. */
  if (vSwUpdM_GridChannel_LegacyIsIncrementOnLocalNodeRequired(ServiceIndex) == TRUE)
  {
    if (vSwUpdM_IsWithLocalNodeOfNodeGroup(destination))
    {
      if (vSwUpdM_GridChannel_GetResponseCount(channelIndex) == (vSwUpdM_GetNNodesOfNodeGroup(destination) - 1u))
      {
        vSwUpdM_GridChannel_IncResponseCount(channelIndex);
      }
    }
  }

  /* #200 If all slaves have sent a response or transmission error is indicated: */
  if (vSwUpdM_GridChannel_GetResponseCount(channelIndex) == vSwUpdM_GetNNodesOfNodeGroup(destination))
  {
    Std_ReturnType result;
    /* This is legacy, only needed for E_SUSPENDED-handling */

    result = ((vSwUpdM_GridSrvc_ResponseClassSimpleResponsePtrType)vSwUpdM_GridChannel_GetAggregatedResultPtr(channelIndex))->Result; /* PRQA S 0310 */ /* MD_vSwUpdM_Rule11.3_0310_ServiceParameterCast */

    if (result == VSWUPDM_E_SUSPENDED)
    {
      vSwUpdM_GridNode_ClearResultByGroup(ServiceIndex, destination);
    }

    /* #210 Provide accumulated result to calling job. */
    (*Result) = (vSwUpdM_GridSrvc_ResponseClassSimpleResponsePtrType) vSwUpdM_GridChannel_GetAggregatedResultPtr(channelIndex);  /* PRQA S 0310 */ /* MD_vSwUpdM_Rule11.3_0310_ServiceParameterCast */
    retVal = VSWUPDM_GRIDSRVC_AGGREGATERESULT_DONE;
  }

  return retVal;
  /* PRQA S 6010, 6030, 6050, 6080 1 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */
} /* vSwUpdM_GridSrvc_GetAggregatedResult */

/**********************************************************************************************************************
 * vSwUpdM_GridSrvc_Finish
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */

FUNC(void, VSWUPDM_CODE) vSwUpdM_GridSrvc_Finish(
  vSwUpdM_GridSrvc_ServiceIdxType ServiceIndex)
{
  vSwUpdM_GridChannel_ChannelIdxType channelIndex = vSwUpdM_GridSrvc_GetChannelOfService(ServiceIndex);

  vSwUpdM_DevError_Assert(vSwUpdM_GridChannel_GetResponseCount(channelIndex) == vSwUpdM_GetNNodesOfNodeGroup(vSwUpdM_GridChannel_GetDestination(channelIndex)), VSWUPDM_DEVERROR_ASSERT_6); /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */

  /* #10 Free Channel. */
  vSwUpdM_GridChannel_SetState(channelIndex, VSWUPDM_GRIDCHANNEL_STATE_IDLE);

} /* vSwUpdM_GridSrvc_Finish */

/*********************
 * LEGACY
 ********************/

/**********************************************************************************************************************
 * vSwUpdM_GridSrvc_ServiceHandlingIsLegacy
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */

FUNC(boolean, VSWUPDM_CODE) vSwUpdM_GridSrvc_ServiceHandlingIsLegacy(
  vSwUpdM_GridSrvc_ServiceIdxType RemoteServiceId)
{
  boolean retVal;

  switch (RemoteServiceId)
  {
    case VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_REQUEST_PROCESS_INFO:
    case VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_CONCLUDE_SEGMENT:
    case VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_COPY_STREAM_DATA:
    case VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_RESPONSE_COPY_STREAM_DATA:
    case VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_PROCESS_STREAM_DATA:
    case VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_CONFIRMATION:
    case VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_PERSIST_MODULE_STATE:
    case VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_PERSIST_MODULE_VALID:
    case VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_PERSIST_MODULE_PROGRAMMING_ATTEMPTS:
    case VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_PERSIST_REGION_STATE:
    case VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_PERSIST_REGION_PROGRAMMING_ATTEMPTS:
    case VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_PERSIST_SEGMENT_ATTRIBUTES:
    case VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_PERSIST_RESUME_INFO:
    case VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_STREAM_COPY:
    case VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_STREAM_END:
    case VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_STREAM_REQUEST:
    case VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_STREAM_START:
    {
      retVal = TRUE;
      break;
    }
    default:
    {
      retVal = FALSE;
      break;
    }
  }

  return retVal;
} /* vSwUpdM_GridSrvc_ServiceHandlingIsLegacy */

/**********************************************************************************************************************
 * vSwUpdM_RemoteConcludeResponses
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
FUNC(void, VSWUPDM_CODE) vSwUpdM_RemoteConcludeResponses(
  vSwUpdM_NodeGroupIterType SourceGroupIndex,
  boolean IsSuspended)
{
  vSwUpdM_NodeGroup2NodeIndIterType sourceIndIndex;

  /* #10 Iterate over all nodes in given remote group */
  for ( sourceIndIndex = vSwUpdM_GetNodeGroup2NodeIndStartIdxOfNodeGroup(SourceGroupIndex);
        sourceIndIndex < vSwUpdM_GetNodeGroup2NodeIndEndIdxOfNodeGroup(SourceGroupIndex);
        sourceIndIndex++)
  {
    vSwUpdM_NodeIterType sourceIndex = vSwUpdM_GetNodeGroup2NodeInd(sourceIndIndex);

    /* #20 If operation was suspended
     *   Prepare for actual response after resume. */
    if (IsSuspended == TRUE)
    {
      vSwUpdM_SetResponseProcessingOfVarNode(sourceIndex, TRUE);
      vSwUpdM_SetResponseValidOfVarNode(sourceIndex, FALSE);
    }
    /* #30 Otherwise: Conclude response processing. */
    else
    {
      vSwUpdM_SetResponseProcessingOfVarNode(sourceIndex, FALSE);
    }
  }
} /* vSwUpdM_RemoteConcludeResponses */

/**********************************************************************************************************************
 * vSwUpdM_RemotePrepareResponseRxTarget
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
FUNC(void, VSWUPDM_CODE) vSwUpdM_RemotePrepareResponseRxTarget(
  vSwUpdM_NodeIterType TargetIndex,
  vSwUpdM_GridSrvc_ServiceIdxType RemoteServiceIndex,
  vSwUpdM_JobPtrType ParentJob)
{
  Std_ReturnType retVal;
  vSwUpdM_JobPtrType spawnedJob;

  vSwUpdM_SetResponseValidOfVarNode(TargetIndex, FALSE);
  vSwUpdM_SetResponseProcessingOfVarNode(TargetIndex, TRUE);

  /* #10 Enter critical section to ensure exclusive access of job queue. */
  VSWUPDM_ENTER_CRITICAL_SECTION();
  /* #20 Spawn job to wait for a response from a remote node. */
  spawnedJob = vSwUpdM_Job_Spawn(&retVal, VSWUPDM_JOB_TYPE_REMOTE_TARGET_CONFIRMATION, VSWUPDM_JOB_OPERATION_DEFAULT, ParentJob->CurrentPrio + 1u,  VSWUPDM_SID_NONE, ParentJob, ParentJob->Source);
    /* #30 Job attributes are safe to be modified when job was successfully spawned and access is still protected by critical section. */

  vSwUpdM_DevError_Assert((retVal == E_OK), VSWUPDM_DEVERROR_ASSERT_13); /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */

  spawnedJob->RemoteTargetGroup  = VSWUPDM_INVALID_NODE_GROUP;
  spawnedJob->RemoteTarget       = TargetIndex;
  spawnedJob->RemoteServiceIndex = RemoteServiceIndex;

  /* #40 Leave critical section to ensure exclusive access of job queue. */
  VSWUPDM_LEAVE_CRITICAL_SECTION();

} /* vSwUpdM_RemotePrepareResponseRxTarget */

/**********************************************************************************************************************
 * vSwUpdM_RemoteClearListOfResponses
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 */

FUNC(void, VSWUPDM_CODE) vSwUpdM_RemoteClearListOfResponses(vSwUpdM_NodeGroupIterType SourceGroupIndex)
{
  vSwUpdM_NodeGroup2NodeIndIterType          sourceIndIndex;

  /* #10 Iterate over all list entries. */
  for(sourceIndIndex = vSwUpdM_GetNodeGroup2NodeIndStartIdxOfNodeGroup(SourceGroupIndex); sourceIndIndex < vSwUpdM_GetNodeGroup2NodeIndEndIdxOfNodeGroup(SourceGroupIndex); sourceIndIndex++)
  {
    vSwUpdM_NodeIterType sourceIndex = vSwUpdM_GetNodeGroup2NodeInd(sourceIndIndex);
    /* #20 set each entry to "invalid". */
    vSwUpdM_SetResponseValidOfVarNode(sourceIndex, FALSE);
    /* Check if a entry is left unprocessed. */
    vSwUpdM_DevError_Assert((vSwUpdM_IsResponseProcessingOfVarNode(sourceIndex) == FALSE), VSWUPDM_DEVERROR_ASSERT_12); /* PRQA S 1881, 4304 */ /* MD_MSR_AutosarBoolean */

      /* #30 set each entry to "unprocessed". */
    vSwUpdM_SetResponseProcessingOfVarNode(sourceIndex, TRUE);
  }
} /* vSwUpdM_RemoteClearListOfResponses */

/*********************
 * REMOTE STREAM (LEGACY)
 ********************/

/**********************************************************************************************************************
 * vSwUpdM_RemoteStreamCallPostHandler
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
 *
 */
FUNC(void, VSWUPDM_CODE) vSwUpdM_RemoteStreamCallPostHandler(
  Std_ReturnType Result,
  vSwUpdM_NodeIterType SourceIndex,
  vSwUpdM_ProcessHandleOfDataProcessesType ProcessHandle,
  vSwUpdM_RemoteStreamHandleType Handle,
  vSwUpdM_GridSrvc_ServiceIdxType ResponseServiceIndex)
{
  Std_ReturnType result = Result;

  VSWUPDM_DUMMY_STATEMENT(Handle);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(ProcessHandle);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(ResponseServiceIndex);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  /* #10 If the processing of the initial Stream request was successful. */
  if(result == E_OK)
  {
    /* #20 If RemoteStream scheduling job is not running: */
    if (vSwUpdM_ExctSchedule_IsJobRunningInSlot(VSWUPDM_JOB_TYPE_REMOTE_STREAM_SCHEDULER) == FALSE)
    {
      /* #21 Enter critical section to ensure exclusive access of job queue. */
      VSWUPDM_ENTER_CRITICAL_SECTION();

      /* #22 Spawn RemoteStream scheduling job. */
      (void) vSwUpdM_Job_Spawn(&result, VSWUPDM_JOB_TYPE_REMOTE_STREAM_SCHEDULER, VSWUPDM_JOB_OPERATION_DEFAULT, (vSwUpdM_QueuePrioType)VSWUPDM_JOB_PRIO_DEFAULT, VSWUPDM_SID_NONE, NULL_PTR, SourceIndex);

      /* #23 Leave critical section to ensure exclusive access of job queue. */
      VSWUPDM_LEAVE_CRITICAL_SECTION();
    }
  }

  /* #30 If something went wrong and source of initial request is valid, */
  if (result != E_OK)
  {
    /* #40 Transmit negative response immediately. */
#if (VSWUPDM_MULTICONTROLLER_SUPPORT == STD_ON)  /* Legacy code */
    if (ResponseServiceIndex == VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_STREAM_COPY)
    {
       (void) vRpcProxy_vSwUpdM_RemoteStreamCopy_Target(
        vSwUpdM_GetDestinationMainOfNode(SourceIndex),
        vSwUpdM_GridRpc_GetRpcProxyRequestOfService(VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_STREAM_REQUEST),
        vSwUpdM_GridRpc_GetRpcProxyServiceExecutionState(VSWUPDM_GRIDRPC_SERVICEXECUTIONSTATE_FINISHED),
        ProcessHandle,
        Handle,
        NULL_PTR,
        0u,
        result);
    }
    else /* (ResponseServiceIndex == VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_STREAM_END) */
    {
      (void) vRpcProxy_vSwUpdM_RemoteStreamEnd_Target(
        vSwUpdM_GetDestinationMainOfNode(SourceIndex),
        vSwUpdM_GridRpc_GetRpcProxyRequestOfService(VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_STREAM_START),
        vSwUpdM_GridRpc_GetRpcProxyServiceExecutionState(VSWUPDM_GRIDRPC_SERVICEXECUTIONSTATE_FINISHED),
        ProcessHandle,
        Handle,
        result);
    }
#endif /* (VSWUPDM_MULTICONTROLLER_SUPPORT == STD_ON) */
  }

  /* PRQA S 6050 1 */ /* MD_MSR_STCAL */
} /* vSwUpdM_RemoteStreamCallPostHandler */

/**********************************************************************************************************************
 * vSwUpdM_RemoteStreamPrepareRx
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_RemoteStreamPrepareRx(
  vSwUpdM_RemoteStreamHandleType Handle,
  P2VAR(uint8, AUTOMATIC, VSWUPDM_APPL_VAR) Buffer,
  vSwUpdM_RemoteStreamSizeType BufferSize,
  vSwUpdM_NodeIterType Source)
{
  Std_ReturnType retVal;

  vSwUpdM_DevError_Assert((Handle < VSWUPDM_REMOTESTREAMHANDLE_SIZE), VSWUPDM_DEVERROR_ASSERT_10);  /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */

  if (Handle < VSWUPDM_REMOTESTREAMHANDLE_SIZE)
  {
    vSwUpdM_DevError_Assert((vSwUpdM_RemoteStream_List[Handle].State == VSWUPDM_REMOTESTREAMSTATE_IDLE), VSWUPDM_DEVERROR_ASSERT_11);  /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */

    /* #10 Set RemoteStream properties. */
    vSwUpdM_RemoteStream_List[Handle].Buffer = Buffer;
    vSwUpdM_RemoteStream_List[Handle].BufferSize = BufferSize;
    vSwUpdM_RemoteStream_List[Handle].Offset = 0u;
    vSwUpdM_RemoteStream_List[Handle].State = VSWUPDM_REMOTESTREAMSTATE_RX_PREPARED;
    vSwUpdM_RemoteStream_List[Handle].Source = Source;
    vSwUpdM_RemoteStream_List[Handle].Target = (vSwUpdM_NodeIterType)vSwUpdM_GetLocalNode();

    retVal = E_OK;
  }
  else
  {
    retVal = VSWUPDM_E_OUT_OF_RANGE;
  }

  return retVal;
} /* vSwUpdM_RemoteStreamPrepareRx */

#if (VSWUPDM_MULTICONTROLLER_SUPPORT == STD_ON) /* Legacy code */
/**********************************************************************************************************************
 * vSwUpdM_RemoteStreamStartTx
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
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_RemoteStreamStartTx(
  vSwUpdM_RemoteStreamHandleType Handle,
  P2VAR(uint8, AUTOMATIC, VSWUPDM_APPL_VAR) Buffer,
  vSwUpdM_RemoteStreamSizeType AvailableLength,
  vSwUpdM_NodeIterType Target)
{
  Std_ReturnType result;

  if (Handle < VSWUPDM_REMOTESTREAMHANDLE_SIZE)
  {
    /* #10 Set RemoteStream properties. */
    vSwUpdM_RemoteStreamPrepareTx(Handle, Buffer, AvailableLength, Target);

    /* #20 Set next state. */
    vSwUpdM_RemoteStream_List[Handle].State = VSWUPDM_REMOTESTREAMSTATE_TX_RESPONSE;
    /* #30 Transmit StreamStart frame. */
    result = vRpcProxy_vSwUpdM_RemoteStreamStart_Target(vSwUpdM_GetDestinationMainOfNode(Target), vSwUpdM_GetProcessHandleOfDataProcesses(vSwUpdM_ProcessData.ProcessId), Handle, AvailableLength);
    /* #40 On fail, set state back to IDLE. */
    if (result != E_OK)
    {
      vSwUpdM_RemoteStream_List[Handle].State = VSWUPDM_REMOTESTREAMSTATE_IDLE;
    }
  }
  else
  {
    result = VSWUPDM_E_OUT_OF_RANGE;
  }

  return result;
} /* vSwUpdM_RemoteStreamStartTx */

/**********************************************************************************************************************
 * vSwUpdM_RemoteStreamSchedule
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
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_RemoteStreamSchedule(vSwUpdM_RemoteStreamHandleType Handle)
{
  Std_ReturnType retVal = E_OK;
  vSwUpdM_RemoteStream_ListType * stream;

  vSwUpdM_ProcessHandleOfDataProcessesType processHandle = vSwUpdM_GetProcessHandleOfDataProcesses(vSwUpdM_ProcessData.ProcessId);
  stream = &vSwUpdM_RemoteStream_List[Handle];
  /* #200 Check if transition in the current remote stream's state required. */
  switch (stream->State)
  {
    default:
    /* case VSWUPDM_REMOTESTREAMSTATE_IDLE:         */
    /* case VSWUPDM_REMOTESTREAMSTATE_RX_PREPARED:  */
    /* case VSWUPDM_REMOTESTREAMSTATE_RX_COPY:      */
    /* case VSWUPDM_REMOTESTREAMSTATE_TX_RESPONSE:  */
    /* case VSWUPDM_REMOTESTREAMSTATE_TX_COPY:      */
    /* case VSWUPDM_REMOTESTREAMSTATE_TX_WAIT_END:  */
    /* case VSWUPDM_REMOTESTREAMSTATE_DONE:         */
    {
      /* #210 If waiting for event, nothing to be done. */
      break;
    }

    case VSWUPDM_REMOTESTREAMSTATE_RX_COPY_RESPOND:
    /* #220 If Start received,
            Trigger PENDING signal for vRpcProxy. */
    {
      (void)vRpcProxy_vSwUpdM_RemoteStreamEnd_Target(
        vSwUpdM_GetDestinationMainOfNode(stream->Source),
        vSwUpdM_GridRpc_GetRpcProxyRequestOfService(VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_STREAM_START),
        vSwUpdM_GridRpc_GetRpcProxyServiceExecutionState(VSWUPDM_GRIDRPC_SERVICEXECUTIONSTATE_PENDING),
        processHandle,
        Handle,
        E_OK);

      stream->State = VSWUPDM_REMOTESTREAMSTATE_RX_REQUEST_TRANSMIT;

      retVal = VSWUPDM_E_BUSY;
      break;
    }
    case VSWUPDM_REMOTESTREAMSTATE_RX_REQUEST_TRANSMIT:
    /* #230 Transmit next request: */
    {
      /* #231 Determine available buffer size. */
      vSwUpdM_RemoteStreamSizeType length = stream->BufferSize;
      if (length > stream->AvailableLength)
      {
        length = stream->AvailableLength;
      }

      stream->State = VSWUPDM_REMOTESTREAMSTATE_RX_COPY;

      /* #232 Request transmission of data. */
      if (vRpcProxy_vSwUpdM_RemoteStreamRequest_Target(vSwUpdM_GetDestinationMainOfNode(stream->Source), processHandle, Handle, E_OK, length) != E_OK)
      {
        /* #233 If transmission was not initiated, e.g because TP buffer is full, retry next time. */
        stream->State = VSWUPDM_REMOTESTREAMSTATE_RX_REQUEST_TRANSMIT;
        retVal = VSWUPDM_E_BUSY;
      }
      break;
    }
    case VSWUPDM_REMOTESTREAMSTATE_TX_RESPONSE_TRANSMIT:
    /* #240 If Request for data is received, */
    {
      /* #241 Determine appropriate length for transmission, */
      vSwUpdM_RemoteStreamSizeType length           = stream->BufferSize;
      vSwUpdM_RemoteStreamSizeType streamRemainder  = stream->AvailableLength - stream->Offset;

      if (length > vSwUpdM_GetRemoteProcessingSegmentation())
      {
        length = (vSwUpdM_RemoteStreamSizeType)vSwUpdM_GetRemoteProcessingSegmentation();
      }

      /* #242 If the last data will be transmitted, wait for End. */
      if (length >= streamRemainder)
      {
        length        = streamRemainder;
        stream->State = VSWUPDM_REMOTESTREAMSTATE_TX_WAIT_END;
      }
      /* #243 Otherwise wait for response. */
      else
      {
        stream->State = VSWUPDM_REMOTESTREAMSTATE_TX_RESPONSE;
      }

      /* #244 Transmit data. */
      if (vRpcProxy_vSwUpdM_RemoteStreamCopy_Target(
        vSwUpdM_GetDestinationMainOfNode(stream->Target),
        vSwUpdM_GridRpc_GetRpcProxyRequestOfService(VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_STREAM_REQUEST),
        vSwUpdM_GridRpc_GetRpcProxyServiceExecutionState(VSWUPDM_GRIDRPC_SERVICEXECUTIONSTATE_FINISHED),
        processHandle,
        Handle,
        &stream->Buffer[stream->Offset],
        (uint16)length, E_OK) == E_OK)
      {
        stream->Offset += length;
      }
      else
      {
        /* #245 If transmission was not initiated, e.g because TP buffer is full, retry next time. */
        retVal        = VSWUPDM_E_BUSY;
        stream->State = VSWUPDM_REMOTESTREAMSTATE_TX_RESPONSE_TRANSMIT;
      }
      break;
    }
    case VSWUPDM_REMOTESTREAMSTATE_RX_TRANSMIT_END:
    /* #250 If End shall be transmitted, */
    {
      /* #251 Transmit End. */
      if (vRpcProxy_vSwUpdM_RemoteStreamEnd_Target(
          vSwUpdM_GetDestinationMainOfNode(stream->Source),
          vSwUpdM_GridRpc_GetRpcProxyRequestOfService(VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_STREAM_START),
          vSwUpdM_GridRpc_GetRpcProxyServiceExecutionState(VSWUPDM_GRIDRPC_SERVICEXECUTIONSTATE_FINISHED),
          processHandle,
          Handle,
          E_OK) == E_OK)
      {
        stream->State = VSWUPDM_REMOTESTREAMSTATE_DONE;
      }
      else
      {
        /* #252 If transmission was not initiated, e.g because TP buffer is full, retry next time. */
        retVal = VSWUPDM_E_BUSY;
      }
      break;
    }
    case VSWUPDM_REMOTESTREAMSTATE_FAIL:
    {
      retVal = VSWUPDM_E_REMOTE_STREAM_FAILED;
      break;
    }
  }

  return retVal;
  /* PRQA S 6030 1 */ /* MD_MSR_STCYC */
} /* vSwUpdM_RemoteStreamSchedule */
#endif /* (VSWUPDM_MULTICONTROLLER_SUPPORT == STD_ON) */

#define VSWUPDM_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/***********************************************************************************************************************
 *  SILENTBSW JUSTIFICATIONS
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  COVERAGE JUSTIFICATIONS
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  END OF FILE: vSwUpdM_Grid.c
 *********************************************************************************************************************/
