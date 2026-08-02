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
/*!        \file  vSwUpdM_BkPersistClient.c
 *        \brief  vSwUpdM Bookkeeper Persistor client source file
 *      \details  Implementation of the vSwUpdM_BkPersistClient subcomponent.
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

#define VSWUPDM_BKPERSISTCLIENT_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "vSwUpdM_Grid_Impl.h"

#include "vSwUpdM_Bookkeeper_Types.h"
#include "vSwUpdM_BkPersistClient_Impl.h"

#include "vSwUpdM_Queue.h"

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/
#define VSWUPDM_BKPERSISTCLIENT_REQUEST_FIRST         0x00u
#define VSWUPDM_BKPERSISTCLIENT_REQUEST_SECOND        0x01u

#define VSWUPDM_BKPERSISTCLIENT_REQUEST_COUNT         0x02u
#define VSWUPDM_BKPERSISTCLIENT_PART_STATEFLAG_COUNT  0x05u

/* One of the requests can be partition state update and this must be split-able into requests for each flag. */
#define VSWUPDM_BKPERSISTCLIENT_REQUEST_BUFFER_COUNT  (VSWUPDM_BKPERSISTCLIENT_REQUEST_COUNT - 1u + VSWUPDM_BKPERSISTCLIENT_PART_STATEFLAG_COUNT)

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/
#define VSWUPDM_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

VSWUPDM_LOCAL VAR(vSwUpdM_BkPersistClient_RequestType, VSWUPDM_VAR_NOINIT) vSwUpdM_BkPersistClient_RequestBuffer[VSWUPDM_BKPERSISTCLIENT_REQUEST_BUFFER_COUNT];
VSWUPDM_LOCAL VAR(vSwUpdM_QueueType, VSWUPDM_VAR_NOINIT)                   vSwUpdM_BkPersistClient_RequestQueue;
VSWUPDM_LOCAL VAR(vSwUpdM_QueueEntryType, VSWUPDM_VAR_NOINIT)              vSwUpdM_BkPersistClient_RequestQueueEntries[VSWUPDM_QUEUE_SIZE(VSWUPDM_BKPERSISTCLIENT_REQUEST_BUFFER_COUNT)]; /* PRQA S 3218 1 */ /* MD_vSwUpdM_Rule8.9_3218_FileScope */
VSWUPDM_LOCAL VAR(boolean, VSWUPDM_VAR_NOINIT)                             vSwUpdM_BkPersistClient_ConnectionIsOpen;

#define VSWUPDM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
#define VSWUPDM_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

VAR(vSwUpdM_PartitionStateType, VSWUPDM_VAR_NOINIT)               vSwUpdM_BkPersistClient_LastPartitionStateResult;

#define VSWUPDM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
#define VSWUPDM_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 * vSwUpdM_BkGetPersistorGroupByParamType
 *********************************************************************************************************************/
/*! \brief       Returns the configured NodeGroup for a given item.
 *  \details     -
 *  \param[in]   ParamType  Parameter type of request.
 *  \param[in]   Entities   Common entities parameter of request.
 *  \param[in]   MaskIdx    Partition state mask index (only necessary for
 *                          ParamType == VSWUPDM_BKPERSIST_PARAM_PARTITION_STATE).
 *  \return      Node group.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     BkPersistClient
 *********************************************************************************************************************/
VSWUPDM_LOCAL FUNC(vSwUpdM_NodeGroupIterType, VSWUPDM_CODE) vSwUpdM_BkPersistClient_GetNodeGroup(
  vSwUpdM_BkPersist_ParamType ParamType,
  P2CONST(vSwUpdM_BkPersist_EntityType, AUTOMATIC, VSWUPDM_APPL_CONST) Entities,
  vSwUpdM_PartitionStateMasksIterType MaskIdx);

/**********************************************************************************************************************
 * vSwUpdM_BkPersistClient_FindLastQueueHandleByState
 *********************************************************************************************************************/
/*! \brief       Reports last handle in queue with matching state.
 *  \details     -
 *  \param[in]   State      Value which shall match.
 *  \param[out]  Handle     Matching handle containing the state.
 *  \return      E_OK       Matching value was found and Entry is valid.
 *  \return      E_NOT_OK   No match. Entry is not valid.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     BkPersistClient
 *********************************************************************************************************************/
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_BkPersistClient_FindLastQueueHandleByState(
  vSwUpdM_BkPersist_RequestStateType State,
  P2VAR(vSwUpdM_QueueHandleType, AUTOMATIC, VSWUPDM_APPL_VAR) Handle);

/**********************************************************************************************************************
 * vSwUpdM_BkPersistClient_TransmitRequest
 *********************************************************************************************************************/
/*! \brief       Hands a request to the Grid for transmission.
 *  \details     -
 *  \param[in]   Request    Buffer containing request data.
 *  \return      E_OK       Request was transmitted
 *  \return      E_NOT_OK   Request was not transmitted
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     BkPersistClient
 *********************************************************************************************************************/
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_BkPersistClient_TransmitRequest(vSwUpdM_BkPersistClient_RequestPtrType Request);

/**********************************************************************************************************************
 * vSwUpdM_BkPersistClient_UpdateStates
 *********************************************************************************************************************/
/*! \brief       Trigger transmission of next request if required and maintain SyncFlag.
 *  \details     -
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     BkPersistClient
 *********************************************************************************************************************/
VSWUPDM_LOCAL FUNC(void, VSWUPDM_CODE) vSwUpdM_BkPersistClient_UpdateStates(void);

/**********************************************************************************************************************
 * vSwUpdM_BkPersistClient_GetRequestByQueueHandle
 *********************************************************************************************************************/
/*! \brief       Returns pointer to Request associated with the given QueueHandle.
 *  \details     -
 *  \param[in]   QueueHandle Handle to the queue entry.
 *  \return      Pointer to the Request associated with the QueueHandle.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     BkPersistClient
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(vSwUpdM_BkPersistClient_RequestPtrType, VSWUPDM_CODE) vSwUpdM_BkPersistClient_GetRequestByQueueHandle(vSwUpdM_QueueHandleType QueueHandle);

/**********************************************************************************************************************
 * vSwUpdM_BkPersistClient_GetRequestByQueueEntry
 *********************************************************************************************************************/
/*! \brief       Returns pointer to Request associated with the given QueueEntry.
 *  \details     -
 *  \param[in]   QueueEntry Pointer to the queue entry.
 *  \return      Pointer to the Request associated with the QueueHandle.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     BkPersistClient
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(vSwUpdM_BkPersistClient_RequestPtrType, VSWUPDM_CODE) vSwUpdM_BkPersistClient_GetRequestByQueueEntry(P2CONST(vSwUpdM_QueueEntryType, AUTOMATIC, VSWUPDM_APPL_VAR) QueueEntry);

/**********************************************************************************************************************
 * vSwUpdM_BkPersistClient_Command
 *********************************************************************************************************************/
/*! \brief       Transmit Command to PersistServer.
 *  \details     To initialize the connection to the PersistServer the Open() command is transmitted.
 *  \param[in]   TargetGroup  Node group, which shall receive the request.
 *  \param[in]   Command      (OPEN | CLOSE).
 *  \return      E_OK         on success.
 *  \return      E_NOT_OK     otherwise.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     BkPersistClient
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_BkPersistClient_Command(vSwUpdM_NodeGroupIterType TargetGroup, vSwUpdM_BkPersist_GenericServiceCommandType Command);

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * vSwUpdM_BkPersistClient_GetNodeGroup
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL FUNC(vSwUpdM_NodeGroupIterType, VSWUPDM_CODE) vSwUpdM_BkPersistClient_GetNodeGroup(
  vSwUpdM_BkPersist_ParamType ParamType,
  P2CONST(vSwUpdM_BkPersist_EntityType, AUTOMATIC, VSWUPDM_APPL_CONST) Entities,
  vSwUpdM_PartitionStateMasksIterType MaskIdx)
{
  vSwUpdM_NodeGroupIterType nodeGroup;

  switch (ParamType)
  {
    case VSWUPDM_BKPERSIST_PARAM_UPDATE_STATE:
    {
      nodeGroup = vSwUpdM_GetNodeGroupClientUpdateState();
      break;
    }
    case VSWUPDM_BKPERSIST_PARAM_PARTITION_STATE:
    {
      nodeGroup = vSwUpdM_GetNodeGroupPartitionStateIdxOfPartitionStateMasks(MaskIdx);
      break;
    }
    case VSWUPDM_BKPERSIST_PARAM_PARTITION_VALIDITY:
    {
      nodeGroup = vSwUpdM_GetNodeGroupPartitionValidityIdxOfBKPartitionNodeGroupReference(vSwUpdM_GetBKPartitionNodeGroupReferenceClientIdxOfPartition(Entities->PartitionId));
      break;
    }
    case VSWUPDM_BKPERSIST_PARAM_PARTITION_REVISION:
    {
      nodeGroup = vSwUpdM_GetNodeGroupPartitionRevisionIdxOfBKPartitionNodeGroupReference(vSwUpdM_GetBKPartitionNodeGroupReferenceClientIdxOfPartition(Entities->PartitionId));
      break;
    }
    case VSWUPDM_BKPERSIST_PARAM_MODULE_STATE:
    {
      nodeGroup = vSwUpdM_GetNodeGroupModuleStateIdxOfBKModuleNodeGroupReference(vSwUpdM_GetBKModuleNodeGroupReferenceClientIdxOfModule(Entities->ModuleId));
      break;
    }
    case VSWUPDM_BKPERSIST_PARAM_MODULE_VALIDITY:
    {
      nodeGroup = vSwUpdM_GetNodeGroupModuleValidityIdxOfBKModuleNodeGroupReference(vSwUpdM_GetBKModuleNodeGroupReferenceClientIdxOfModule(Entities->ModuleId));
      break;
    }
    case VSWUPDM_BKPERSIST_PARAM_MODULE_REVISION:
    {
      nodeGroup = vSwUpdM_GetNodeGroupModuleRevisionIdxOfBKModuleNodeGroupReference(vSwUpdM_GetBKModuleNodeGroupReferenceClientIdxOfModule(Entities->ModuleId));
      break;
    }
    case VSWUPDM_BKPERSIST_PARAM_MODULE_PROGRAMMING_ATTEMPTS:
    {
      nodeGroup = vSwUpdM_GetNodeGroupModuleProgrammingAttemptsIdxOfBKModuleNodeGroupReference(vSwUpdM_GetBKModuleNodeGroupReferenceClientIdxOfModule(Entities->ModuleId));
      break;
    }
    case VSWUPDM_BKPERSIST_PARAM_MODULE_SEGMENT_COUNT:
    {
      nodeGroup = vSwUpdM_GetNodeGroupModuleSegmentDataIdxOfBKModuleNodeGroupReference(vSwUpdM_GetBKModuleNodeGroupReferenceClientIdxOfModule(Entities->ModuleId));
      break;
    }
    case VSWUPDM_BKPERSIST_PARAM_REGION_STATE:
    {
      nodeGroup = vSwUpdM_GetNodeGroupRegionStateIdxOfBKRegionNodeGroupReference(vSwUpdM_GetBKRegionNodeGroupReferenceClientIdxOfRegion(Entities->RegionId));
      break;
    }
    case VSWUPDM_BKPERSIST_PARAM_REGION_PROGRAMMING_ATTEMPTS:
    {
      nodeGroup = vSwUpdM_GetNodeGroupRegionProgrammingAttemptsIdxOfBKRegionNodeGroupReference(vSwUpdM_GetBKRegionNodeGroupReferenceClientIdxOfRegion(Entities->RegionId));
      break;
    }
    case VSWUPDM_BKPERSIST_PARAM_REGION_ERASE_ADDRESS:
    {
      nodeGroup = vSwUpdM_GetNodeGroupRegionEraseAddressIdxOfBKRegionNodeGroupReference(vSwUpdM_GetBKRegionNodeGroupReferenceClientIdxOfRegion(Entities->RegionId));
      break;
    }
    case VSWUPDM_BKPERSIST_PARAM_SEGMENT_ATTRIBUTES:
    {
      nodeGroup = vSwUpdM_GetNodeGroupModuleSegmentDataIdxOfBKModuleNodeGroupReference(vSwUpdM_GetBKModuleNodeGroupReferenceClientIdxOfModule(Entities->ModuleId));
      break;
    }
    case VSWUPDM_BKPERSIST_PARAM_SEGMENT_WRITE_ADDRESS:
    {
      nodeGroup = vSwUpdM_GetNodeGroupModuleSegmentDataIdxOfBKModuleNodeGroupReference(vSwUpdM_GetBKModuleNodeGroupReferenceClientIdxOfModule(Entities->ModuleId));
      break;
    }
    default:
    /* case VSWUPDM_BKPERSIST_PARAM_RESUME_INFO: */
    {
      nodeGroup = vSwUpdM_GetNodeGroupClientResumeInfo();
      break;
    }
  }

  return nodeGroup;
  /* PRQA S 6030 1 */ /* MD_MSR_STCYC */
} /* vSwUpdM_BkGetPersistorGroupByParamType */

/**********************************************************************************************************************
 * vSwUpdM_BkPersistClient_FindLastQueueHandleByState
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_BkPersistClient_FindLastQueueHandleByState(
  vSwUpdM_BkPersist_RequestStateType State,
  P2VAR(vSwUpdM_QueueHandleType, AUTOMATIC, VSWUPDM_APPL_VAR) Handle)
{
  Std_ReturnType               retVal = E_NOT_OK;
  vSwUpdM_QueueHandleType queueHandle = vSwUpdM_QueueGetLastUsedHandle(&vSwUpdM_BkPersistClient_RequestQueue);

  /* Queue is empty if last used handle is VSWUPDM_QUEUE_HANDLE_HEAD_USED. */
  while (queueHandle != VSWUPDM_QUEUE_HANDLE_HEAD_USED)
  {
    P2CONST(vSwUpdM_QueueEntryType, AUTOMATIC, VSWUPDM_APPL_VAR) currentEntry;

    /* Get entry for accessing state. */
    currentEntry = &vSwUpdM_QueueGetEntry(&vSwUpdM_BkPersistClient_RequestQueue, queueHandle);

    /* Quit if matching entry was found. */
    if (vSwUpdM_BkPersistClient_GetRequestByQueueEntry(currentEntry)->State == State)
    {
      *Handle = queueHandle;
      retVal = E_OK;
      break;
    }

    /* Get next queue handle. */
    queueHandle = currentEntry->prev;
  }

  return retVal;
} /* vSwUpdM_BkPersistClient_FindLastQueueHandleByState */

/**********************************************************************************************************************
 * vSwUpdM_BkPersistClient_TransmitRequest
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_BkPersistClient_TransmitRequest(vSwUpdM_BkPersistClient_RequestPtrType Request)
{
  vSwUpdM_GridSrvc_ServiceClassBasePtrType  param;
  Std_ReturnType retVal;

  /* Ensure that state has correct value in case of immediate asynchronous vRpcProxy actions. */
  Request->State = VSWUPDM_BKPERSIST_REQUESTSTATE_WAIT_RESPONSE;
  vSwUpdM_GridSrvc_Register(Request->ServiceIndex, &param);

  /* #10 Initiate transmission based on ServiceIndex. */
  switch (Request->ServiceIndex)
  {
    case VSWUPDM_GRIDSRVC_SERVICEIDX_BK_EXEC_COMMAND:
    {
      vSwUpdM_Grid_InitServiceClassBkExecCommand(Request->Command, (vSwUpdM_GridSrvc_ServiceClassBkExecCommandPtrType) param); /* PRQA S 0310 */ /* MD_vSwUpdM_Rule11.3_0310_ServiceParameterCast */
      break;
    }
    case VSWUPDM_GRIDSRVC_SERVICEIDX_BK_GET_SEGMENT_ATTRIBUTES:
    {
      vSwUpdM_Grid_InitServiceClassBkGetSegmentAttributes(&Request->Entities, (vSwUpdM_GridSrvc_ServiceClassBkGetSegmentAttributesPtrType)param); /* PRQA S 0310 */ /* MD_vSwUpdM_Rule11.3_0310_ServiceParameterCast */
      break;
    }
    case VSWUPDM_GRIDSRVC_SERVICEIDX_BK_GET_RESUME_INFO:
    {
      vSwUpdM_Grid_InitServiceClassBkGetResumeInfo((vSwUpdM_GridSrvc_ServiceClassBkGetResumeInfoPtrType) param); /* PRQA S 0310 */ /* MD_vSwUpdM_Rule11.3_0310_ServiceParameterCast */
      break;
    }
    case VSWUPDM_GRIDSRVC_SERVICEIDX_BK_GET_GENERIC_PARAMETER:
    {
      vSwUpdM_Grid_InitServiceClassBkGetGenericParameter(&Request->Entities, Request->ParamType, (vSwUpdM_GridSrvc_ServiceClassBkGetGenericParameterPtrType) param); /* PRQA S 0310 */ /* MD_vSwUpdM_Rule11.3_0310_ServiceParameterCast */
      break;
    }
    case VSWUPDM_GRIDSRVC_SERVICEIDX_BK_SET_SEGMENT_ATTRIBUTES:
    {
      vSwUpdM_Grid_InitServiceClassBkSetSegmentAttributes(
        &Request->Entities,
        ((P2CONST(vSwUpdM_BkPersist_SegmentAttributesType, AUTOMATIC, VSWUPDM_APPL_CONST))Request->RequestParam), /* PRQA S 0316 */ /* MD_vSwUpdM_Rule11.5_0316_PersistCastPtrVoidPtrObj */
        Request->SyncFlag,
        (vSwUpdM_GridSrvc_ServiceClassBkSetSegmentAttributesPtrType) param);     /* PRQA S 0310 */ /* MD_vSwUpdM_Rule11.3_0310_ServiceParameterCast */
      break;
    }
    case VSWUPDM_GRIDSRVC_SERVICEIDX_BK_SET_RESUME_INFO:
    {
      vSwUpdM_Grid_InitServiceClassBkSetResumeInfo(
        ((P2CONST(vSwUpdM_ExtendedResumeInfoType, AUTOMATIC, VSWUPDM_APPL_CONST))Request->RequestParam), /* PRQA S 0316 */ /* MD_vSwUpdM_Rule11.5_0316_PersistCastPtrVoidPtrObj */
        Request->SyncFlag,
        (vSwUpdM_GridSrvc_ServiceClassBkSetResumeInfoPtrType) param);       /* PRQA S 0310 */ /* MD_vSwUpdM_Rule11.3_0310_ServiceParameterCast */
      break;
    }
    default:
    /* case VSWUPDM_GRIDSRVC_SERVICEIDX_BK_SET_GENERIC_PARAMETER: */
    {
      vSwUpdM_Grid_InitServiceClassBkSetGenericParameter(
        &Request->Entities,
        Request->ParamType,
        Request->RequestSize,
        Request->RequestParam,
        Request->SyncFlag,
        (vSwUpdM_GridSrvc_ServiceClassBkSetGenericParameterPtrType) param);      /* PRQA S 0310 */ /* MD_vSwUpdM_Rule11.3_0310_ServiceParameterCast */
      break;
    }
  }

  retVal = vSwUpdM_GridSrvc_Start(Request->TargetGroup, Request->ServiceIndex);

  return retVal;
  /* PRQA S 6050 1 */ /* MD_MSR_STCAL */
} /* vSwUpdM_BkPersistClient_TransmitRequest */

/**********************************************************************************************************************
 * vSwUpdM_BkPersistClient_UpdateStates
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
VSWUPDM_LOCAL FUNC(void, VSWUPDM_CODE) vSwUpdM_BkPersistClient_UpdateStates(void)
{
  /* #10 Necessary check to get first used entry - Decide if we have something to do. */
  if (!vSwUpdM_QueueIsEmpty(&vSwUpdM_BkPersistClient_RequestQueue))
  {
    /* #20 Get first used entry. */
    P2CONST(vSwUpdM_QueueEntryType, AUTOMATIC, VSWUPDM_APPL_VAR)  activeRequestHandle = &vSwUpdM_QueueGetFirstUsedEntry(&vSwUpdM_BkPersistClient_RequestQueue);
    vSwUpdM_BkPersistClient_RequestPtrType activeRequest = vSwUpdM_BkPersistClient_GetActiveRequest();

    /* #30 Handle DELAYED state and SyncFlag. */
    if (activeRequestHandle != &vSwUpdM_QueueGetLastUsedEntry(&vSwUpdM_BkPersistClient_RequestQueue))
    {
      if (activeRequest->State == VSWUPDM_BKPERSIST_REQUESTSTATE_DELAYED)
      {
        activeRequest->State = VSWUPDM_BKPERSIST_REQUESTSTATE_READY;
        {
          vSwUpdM_BkPersistClient_RequestPtrType nextEntry = vSwUpdM_BkPersistClient_GetRequestByQueueHandle(activeRequestHandle->next); /* PRQA S 3679 */ /* MD_vSwUpdM_Rule8.13_3679_PointerToModifiableData */

          if ((nextEntry->Command != VSWUPDM_BKPERSIST_GENERICSERVICECOMMAND_SET)
            || (activeRequest->TargetGroup != nextEntry->TargetGroup))
          {
            activeRequest->SyncFlag = TRUE;
          }
        }
      }
    }

    /* #40 Check if active request is ready for transmission. */
    if (activeRequest->State == VSWUPDM_BKPERSIST_REQUESTSTATE_READY)
    {
      if (vSwUpdM_BkPersistClient_TransmitRequest(activeRequest) != E_OK)
      {
        /* Update state in case of error: */
        activeRequest->State = VSWUPDM_BKPERSIST_REQUESTSTATE_FAILED;
      }
    }
  }
} /* vSwUpdM_BkPersistClient_UpdateStates */

/**********************************************************************************************************************
 * vSwUpdM_BkPersistClient_GetRequestByQueueHandle
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(vSwUpdM_BkPersistClient_RequestPtrType, VSWUPDM_CODE) vSwUpdM_BkPersistClient_GetRequestByQueueHandle(vSwUpdM_QueueHandleType QueueHandle)
{
  return &vSwUpdM_BkPersistClient_RequestBuffer[vSwUpdM_QueueGetEntityHandle(&vSwUpdM_BkPersistClient_RequestQueue, QueueHandle)];
} /* vSwUpdM_BkPersistClient_GetRequestByQueueHandle */


/**********************************************************************************************************************
 * vSwUpdM_BkPersistClient_GetRequestByQueueEntry
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(vSwUpdM_BkPersistClient_RequestPtrType, VSWUPDM_CODE) vSwUpdM_BkPersistClient_GetRequestByQueueEntry(P2CONST(vSwUpdM_QueueEntryType, AUTOMATIC, VSWUPDM_APPL_VAR) QueueEntry)
{
  return &vSwUpdM_BkPersistClient_RequestBuffer[QueueEntry->entity];
} /* vSwUpdM_BkPersistClient_GetRequestByQueueEntry */

/**********************************************************************************************************************
 * vSwUpdM_BkPersistClient_Command
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_BkPersistClient_Command(vSwUpdM_NodeGroupIterType TargetGroup, vSwUpdM_BkPersist_GenericServiceCommandType Command)
{
  Std_ReturnType retVal = E_OK;

  /* Check available space in queue. */
  if (vSwUpdM_QueueGetNumberOfFreeEntries(&vSwUpdM_BkPersistClient_RequestQueue) < 1u)
  {
    retVal = E_NOT_OK;
  }

  /* Store request in queue. */
  if (retVal == E_OK)
  {
    vSwUpdM_QueueHandleType                                      reqHandle;
    vSwUpdM_BkPersistClient_RequestPtrType                       request;

    /* Add request to queue. */
    reqHandle = vSwUpdM_QueueAppend(&vSwUpdM_BkPersistClient_RequestQueue);
    request   = vSwUpdM_BkPersistClient_GetRequestByQueueHandle(reqHandle);

    request->Command      = Command;
    request->ServiceIndex = VSWUPDM_GRIDSRVC_SERVICEIDX_BK_EXEC_COMMAND;
    request->TargetGroup  = TargetGroup;
    request->State        = VSWUPDM_BKPERSIST_REQUESTSTATE_READY;

    /* Update internal states and start transmission if possible. */
    vSwUpdM_BkPersistClient_UpdateStates();
  }

  return retVal;
} /* vSwUpdM_BkPersistClient_Command */

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * vSwUpdM_BkPersistClient_GetActiveRequest
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(vSwUpdM_BkPersistClient_RequestPtrType, VSWUPDM_CODE) vSwUpdM_BkPersistClient_GetActiveRequest(void)
{
  P2CONST(vSwUpdM_QueueEntryType, AUTOMATIC, VSWUPDM_APPL_VAR)  reqEntry = &vSwUpdM_QueueGetFirstUsedEntry(&vSwUpdM_BkPersistClient_RequestQueue);

  return vSwUpdM_BkPersistClient_GetRequestByQueueEntry(reqEntry);
} /* vSwUpdM_BkPersistClient_GetActiveRequest */

/**********************************************************************************************************************
 * vSwUpdM_BkPersistClient_Init
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(void, VSWUPDM_CODE) vSwUpdM_BkPersistClient_Init(void)
{
  vSwUpdM_QueueInit(&vSwUpdM_BkPersistClient_RequestQueue,
                    vSwUpdM_BkPersistClient_RequestQueueEntries,
                    VSWUPDM_ARRAY_SIZE(vSwUpdM_BkPersistClient_RequestQueueEntries),
                    VSWUPDM_QUEUE_PRIO_ORDER_ASC, 0u, 1u);

  vSwUpdM_BkPersistClient_LastPartitionStateResult = 0u;
  vSwUpdM_BkPersistClient_ConnectionIsOpen = FALSE;
} /* vSwUpdM_BkPersistClient_Init */

/**********************************************************************************************************************
 * vSwUpdM_BkPersistClient_Set
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
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
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_BkPersistClient_Set(
  P2CONST(vSwUpdM_BkPersist_EntityType, AUTOMATIC, VSWUPDM_APPL_CONST) Entities,
  vSwUpdM_BkPersist_ParamType ParamType,
  vSwUpdM_BkPersist_SizeOfParameterType ParameterSize,
  P2VAR(void, AUTOMATIC, VSWUPDM_APPL_VAR) Parameter)
{
  Std_ReturnType                      retVal = E_OK;
  vSwUpdM_NodeGroupIterType           bkNodeGroup;

  vSwUpdM_PartitionStateMasksIterType requestIdx, requestEndIdx;

  /* Determine the max amount of requests. */
  if (ParamType == VSWUPDM_BKPERSIST_PARAM_PARTITION_STATE)
  {
    /* In case of partition state the number of requests is equal to the number of configured client masks. */
    requestIdx    = vSwUpdM_GetPartitionStateMasksStartIdxOfBKPartitionNodeGroupReference(vSwUpdM_GetBKPartitionNodeGroupReferenceClientIdxOfPartition(Entities->PartitionId));
    requestEndIdx = vSwUpdM_GetPartitionStateMasksEndIdxOfBKPartitionNodeGroupReference(vSwUpdM_GetBKPartitionNodeGroupReferenceClientIdxOfPartition(Entities->PartitionId));
  }
  else
  {
    /* All other requests are single requests only. */
    requestIdx    = 0u;
    requestEndIdx = 1u;
  }

  /* Check that there is enough free space in queue to hold the request.
   * HINT: The cast to vSwUpdM_PartitionStateMasksIterType is required to avoid an undesired integer promotion to signed (!) integer (see C99 6.3.1.1). */
  if (((vSwUpdM_PartitionStateMasksIterType)(requestEndIdx - requestIdx)) > vSwUpdM_QueueGetNumberOfFreeEntries(&vSwUpdM_BkPersistClient_RequestQueue))
  {
    retVal = E_NOT_OK;
  }

  if (retVal == E_OK)
  {
    for (; requestIdx < requestEndIdx; requestIdx++)
    {
      vSwUpdM_QueueHandleType                                       reqHandle;
      vSwUpdM_PartitionStateType                                    tmpChangeMask;
      vSwUpdM_BkPersistClient_RequestPtrType                        request;

      tmpChangeMask = Entities->PartitionStateChangeMask & vSwUpdM_GetPartitionStateBitmaskOfPartitionStateMasks(requestIdx);

      /* Check for setting partition state whether it's necessary to update current mask. */
      if (ParamType == VSWUPDM_BKPERSIST_PARAM_PARTITION_STATE)
      {
        if (tmpChangeMask == 0u)
        {
          /* Current state mask is not affected continue with next. retVal stays valid since it was initialized with E_OK. */
          continue;
        }
      }

      /* Add request to queue. */
      reqHandle   = vSwUpdM_QueueAppend(&vSwUpdM_BkPersistClient_RequestQueue);
      bkNodeGroup = vSwUpdM_BkPersistClient_GetNodeGroup(ParamType, Entities, requestIdx);
      request     = vSwUpdM_BkPersistClient_GetRequestByQueueHandle(reqHandle);

      request->Command      = VSWUPDM_BKPERSIST_GENERICSERVICECOMMAND_SET;
      request->ParamType    = ParamType;
      request->TargetGroup  = bkNodeGroup;
      request->RequestParam = Parameter;
      request->RequestSize  = ParameterSize;
      request->Entities     = *Entities;
      request->SyncFlag     = FALSE;
      request->State        = VSWUPDM_BKPERSIST_REQUESTSTATE_DELAYED;

      /* Limit the scope of change mask according to current mask. */
      if (ParamType == VSWUPDM_BKPERSIST_PARAM_PARTITION_STATE)
      {
        request->Entities.PartitionStateChangeMask = tmpChangeMask;
      }

      switch (ParamType)
      {
        case VSWUPDM_BKPERSIST_PARAM_SEGMENT_ATTRIBUTES:
        {
          request->ServiceIndex = VSWUPDM_GRIDSRVC_SERVICEIDX_BK_SET_SEGMENT_ATTRIBUTES;
          break;
        }
        case VSWUPDM_BKPERSIST_PARAM_RESUME_INFO:
        {
          request->ServiceIndex = VSWUPDM_GRIDSRVC_SERVICEIDX_BK_SET_RESUME_INFO;
          break;
        }
        default:
        {
          request->ServiceIndex = VSWUPDM_GRIDSRVC_SERVICEIDX_BK_SET_GENERIC_PARAMETER;
          break;
        }
      }
    }

    vSwUpdM_BkPersistClient_UpdateStates();
  }

  return retVal;
/* PRQA S 6010, 6030 1 */ /* MD_MSR_STPTH, MD_MSR_STCYC */
} /* vSwUpdM_BkPersistClient_Set */

/**********************************************************************************************************************
 * vSwUpdM_BkPersistClient_Get
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
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_BkPersistClient_Get(
  P2CONST(vSwUpdM_BkPersist_EntityType, AUTOMATIC, VSWUPDM_APPL_CONST) Entities,
  vSwUpdM_BkPersist_ParamType ParamType,
  vSwUpdM_BkPersist_SizeOfParameterType ResponseSize,
  P2VAR(void, AUTOMATIC, VSWUPDM_APPL_VAR) ResponseBuffer
)
{
  Std_ReturnType                            retVal = E_OK;
  vSwUpdM_NodeGroupIterType                 bkNodeGroup;
  vSwUpdM_PartitionStateMasksIterType       requestIdx, requestEndIdx;

  /* Determine the amount of requests. */
  if (ParamType == VSWUPDM_BKPERSIST_PARAM_PARTITION_STATE)
  {
    /* In case of partition state the number of requests is equal to the number of configured client masks. */
    requestIdx    = vSwUpdM_GetPartitionStateMasksStartIdxOfBKPartitionNodeGroupReference(vSwUpdM_GetBKPartitionNodeGroupReferenceClientIdxOfPartition(Entities->PartitionId));
    requestEndIdx = vSwUpdM_GetPartitionStateMasksEndIdxOfBKPartitionNodeGroupReference(vSwUpdM_GetBKPartitionNodeGroupReferenceClientIdxOfPartition(Entities->PartitionId));
  }
  else
  {
    /* All other requests are single requests only. */
    requestIdx    = 0u;
    requestEndIdx = 1u; /* EndIdx always point to the element behind last. */
  }

  /* Check that there is enough free space in queue to hold the request.
   * HINT: The cast to vSwUpdM_PartitionStateMasksIterType is required to avoid an undesired integer promotion to signed (!) integer (see C99 6.3.1.1). */
  if (((vSwUpdM_PartitionStateMasksIterType)(requestEndIdx - requestIdx)) > vSwUpdM_QueueGetNumberOfFreeEntries(&vSwUpdM_BkPersistClient_RequestQueue))
  {
    retVal = E_NOT_OK;
  }

  /* Store request(s) */
  if(retVal == E_OK)
  {
    for (; requestIdx < requestEndIdx; requestIdx++)
    {
      vSwUpdM_QueueHandleType                                       reqHandle;
      vSwUpdM_BkPersistClient_RequestPtrType                        request;

      /* Add request to queue. */
      reqHandle   = vSwUpdM_QueueAppend(&vSwUpdM_BkPersistClient_RequestQueue);
      bkNodeGroup = vSwUpdM_BkPersistClient_GetNodeGroup(ParamType, Entities, requestIdx);
      request     = vSwUpdM_BkPersistClient_GetRequestByQueueHandle(reqHandle);

      request->Command           = VSWUPDM_BKPERSIST_GENERICSERVICECOMMAND_GET;
      request->ParamType         = ParamType;
      request->ResponseSize      = ResponseSize;
      request->ResponseBuffer    = ResponseBuffer;
      request->TargetGroup       = bkNodeGroup;
      request->Entities          = *Entities;
      request->SyncFlag          = FALSE;
      request->State             = VSWUPDM_BKPERSIST_REQUESTSTATE_READY;
      request->RemainingMultiReq = requestEndIdx - requestIdx - 1u; /*!< Always 0 except for partition status get with multiple masks. */

      switch (ParamType)
      {
        case VSWUPDM_BKPERSIST_PARAM_SEGMENT_ATTRIBUTES:
        {
          request->ServiceIndex = VSWUPDM_GRIDSRVC_SERVICEIDX_BK_GET_SEGMENT_ATTRIBUTES;
          break;
        }
        case VSWUPDM_BKPERSIST_PARAM_RESUME_INFO:
        {
          request->ServiceIndex = VSWUPDM_GRIDSRVC_SERVICEIDX_BK_GET_RESUME_INFO;
          break;
        }
        default:
        {
          request->ServiceIndex = VSWUPDM_GRIDSRVC_SERVICEIDX_BK_GET_GENERIC_PARAMETER;
          break;
        }
      }
    }

    vSwUpdM_BkPersistClient_UpdateStates();
  }

  return retVal;

} /* vSwUpdM_BkPersistClient_Get */

/**********************************************************************************************************************
 * vSwUpdM_BkPersistClient_Open
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_BkPersistClient_Open(vSwUpdM_NodeGroupIterType TargetGroup)
{
  return vSwUpdM_BkPersistClient_Command(TargetGroup, VSWUPDM_BKPERSIST_GENERICSERVICECOMMAND_OPEN);
} /* vSwUpdM_BkPersistClient_Open */

/**********************************************************************************************************************
 * vSwUpdM_BkPersistClient_Close
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
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_BkPersistClient_Close(vSwUpdM_NodeGroupIterType TargetGroup)
{
  Std_ReturnType retVal;

  /* #10 If Connection is open: */
  if(vSwUpdM_BkPersistClient_ConnectionIsOpen == TRUE)
  {
    /* #11 Transmit Close command to PersistServer. */
    retVal = vSwUpdM_BkPersistClient_Command(TargetGroup, VSWUPDM_BKPERSIST_GENERICSERVICECOMMAND_CLOSE);
  }
  else
  {
    /* #12 Else:
     *     Nothing to do. */
    retVal = E_OK;
  }

  return retVal;
} /* vSwUpdM_BkPersistClient_Close */

/**********************************************************************************************************************
 * vSwUpdM_BkPersistClient_Sync
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
FUNC(void, VSWUPDM_CODE) vSwUpdM_BkPersistClient_Sync(void)
{
  vSwUpdM_QueueHandleType delayedHandle;

  while (vSwUpdM_BkPersistClient_FindLastQueueHandleByState(VSWUPDM_BKPERSIST_REQUESTSTATE_DELAYED, &delayedHandle) == E_OK)
  {
    P2CONST(vSwUpdM_QueueEntryType, AUTOMATIC, VSWUPDM_APPL_VAR) delayedEntry = &vSwUpdM_QueueGetEntry(&vSwUpdM_BkPersistClient_RequestQueue, delayedHandle);
    P2CONST(vSwUpdM_QueueEntryType, AUTOMATIC, VSWUPDM_APPL_VAR) tmpEntry;
    vSwUpdM_BkPersistClient_RequestPtrType delayedRequest = vSwUpdM_BkPersistClient_GetRequestByQueueHandle(delayedHandle);

    /* Set for found request sync flag and new state. */
    delayedRequest->SyncFlag = TRUE;
    delayedRequest->State    = VSWUPDM_BKPERSIST_REQUESTSTATE_READY;

    /* Search in the remaining queue for requests with the same target group and delayed state. */
    for (tmpEntry = &vSwUpdM_QueueGetFirstUsedEntry(&vSwUpdM_BkPersistClient_RequestQueue);
         tmpEntry != delayedEntry;
         tmpEntry = &vSwUpdM_QueueGetEntry(&vSwUpdM_BkPersistClient_RequestQueue, tmpEntry->next))
    {
      vSwUpdM_BkPersistClient_RequestPtrType tmpRequest = vSwUpdM_BkPersistClient_GetRequestByQueueEntry(tmpEntry); /* PRQA S 3679 */ /* MD_vSwUpdM_Rule8.13_3679_PointerToModifiableData */

      if ((delayedRequest->TargetGroup == tmpRequest->TargetGroup)
       && (tmpRequest->State == VSWUPDM_BKPERSIST_REQUESTSTATE_DELAYED))
      {
        /* Sync flag can stay at false, just update state to ensure that the message will be transmitted asap. */
        tmpRequest->State = VSWUPDM_BKPERSIST_REQUESTSTATE_READY;
      }
    }
  }
} /* vSwUpdM_BkPersistClient_Sync */

/**********************************************************************************************************************
 * vSwUpdM_BkPersistClient_Execute
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
FUNC(vSwUpdM_BkPersist_RequestStateType, VSWUPDM_CODE) vSwUpdM_BkPersistClient_Execute(void)
{
  vSwUpdM_BkPersist_RequestStateType retVal = VSWUPDM_BKPERSIST_REQUESTSTATE_IDLE;

  /* #100 If there is a pending request: */
  if (!vSwUpdM_QueueIsEmpty(&vSwUpdM_BkPersistClient_RequestQueue))
  {
    vSwUpdM_GridSrvc_ResponseClassBookkeeperPtrType response;
    vSwUpdM_QueueHandleType activeRequestHandle = vSwUpdM_QueueGetFirstUsedHandle(&vSwUpdM_BkPersistClient_RequestQueue);
    vSwUpdM_BkPersistClient_RequestPtrType activeRequest = vSwUpdM_BkPersistClient_GetActiveRequest(); /* PRQA S 3679 */ /* MD_vSwUpdM_Rule8.13_3679_PointerToModifiableData */

    /* initialize retVal with state of active request. */
    retVal = activeRequest->State;

    if(activeRequest->State == VSWUPDM_BKPERSIST_REQUESTSTATE_WAIT_RESPONSE)
    {
      vSwUpdM_GridSrvc_ServiceIdxType serviceIndex = activeRequest->ServiceIndex;

      /* #110 Check for responses. */
      if (vSwUpdM_GridSrvc_GetAggregatedResult(activeRequest->ServiceIndex, &response) == VSWUPDM_GRIDSRVC_AGGREGATERESULT_DONE)
      {
        /* Take over result. */
        if (response->Result == E_OK)
        {
          /* #111 Remember connection state if applicable. */
          switch (activeRequest->Command)
          {
            case VSWUPDM_BKPERSIST_GENERICSERVICECOMMAND_OPEN:
            {
              vSwUpdM_BkPersistClient_ConnectionIsOpen = TRUE;
              break;
            }
            case VSWUPDM_BKPERSIST_GENERICSERVICECOMMAND_CLOSE:
            {
              vSwUpdM_BkPersistClient_ConnectionIsOpen = FALSE;
              break;
            }
            default:
            {
              /* Nothing to do here. */
              break;
            }
          }

          retVal = VSWUPDM_BKPERSIST_REQUESTSTATE_IDLE;
        }
        else
        {
          retVal = VSWUPDM_BKPERSIST_REQUESTSTATE_FAILED;
        }

        /* Remove request from queue. */
        (void)vSwUpdM_QueueRemove(&vSwUpdM_BkPersistClient_RequestQueue, activeRequestHandle);
        /* Hint: activeRequest pointer is now invalid. */

        /* #120 Free channel. */
        vSwUpdM_GridSrvc_Finish(serviceIndex);
      }
    }

    /* Update / Handle Queue */
    vSwUpdM_BkPersistClient_UpdateStates();

    /* If there is a new request, take over state of new request. */
    if (!vSwUpdM_QueueIsEmpty(&vSwUpdM_BkPersistClient_RequestQueue))
    {
      retVal = vSwUpdM_BkPersistClient_GetActiveRequest()->State;
    }

    /* Delayed state is an internal one - inform upper layer that queue is not empty. */
    if (retVal == VSWUPDM_BKPERSIST_REQUESTSTATE_DELAYED)
    {
      retVal = VSWUPDM_BKPERSIST_REQUESTSTATE_WAIT_RESPONSE;
    }
  }

  if (   (retVal != VSWUPDM_BKPERSIST_REQUESTSTATE_IDLE)
      && (retVal != VSWUPDM_BKPERSIST_REQUESTSTATE_READY)
      && (retVal != VSWUPDM_BKPERSIST_REQUESTSTATE_WAIT_RESPONSE))
  {
    retVal = VSWUPDM_BKPERSIST_REQUESTSTATE_FAILED;
  }

  return retVal;
  /* PRQA S 6080 1 */ /* MD_MSR_STMIF */
} /* vSwUpdM_BkPersistClient_Execute */

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
