/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2022 by Vector Informatik GmbH.                                                  All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/*!        \file  vStreamProc_Scheduler.c
 *        \brief  vStreamProc Scheduler Sub Module Source Code File
 *
 *      \details  Implementation of the vStreamProc Scheduler sub module.
 *
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's main header file.
 *
 *  FILE VERSION
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's main header file vStreamProc.h.
 *********************************************************************************************************************/
# define VSTREAMPROC_SCHEDULER_SOURCE

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "vStreamProc.h"
#include "vStreamProc_Scheduler.h"
#include "vStreamProc_Port.h"

#if (VSTREAMPROC_DEV_ERROR_REPORT == STD_ON)
# include "Det.h"
#endif

/**********************************************************************************************************************
 *  MISRA & PClint
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 **********************************************************************************************************************/
#if !defined (VSTREAMPROC_LOCAL)
# define VSTREAMPROC_LOCAL static
#endif

#if !defined (VSTREAMPROC_LOCAL_INLINE)
# define VSTREAMPROC_LOCAL_INLINE LOCAL_INLINE
#endif

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 **********************************************************************************************************************/
/* PRQA S 3453 2 */ /* MD_MSR_FctLikeMacro */
#define VSTREAMPROC_SCHEDULER_MAGIC_ENTRYUNUSED \
    ((vStreamProc_NodeIterType)(vStreamProc_GetSizeOfScheduleEntryTable()))

/* PRQA S 3453 2 */ /* MD_MSR_FctLikeMacro */
#define vStreamProc_Scheduler_Set_EntryUnused(EntryIdx) \
    (vStreamProc_SetScheduleEntryTable(EntryIdx, VSTREAMPROC_SCHEDULER_MAGIC_ENTRYUNUSED))

/* PRQA S 3453 2 */ /* MD_MSR_FctLikeMacro */
#define vStreamproc_Scheduler_Is_EntryUsed(EntryIdx) \
    (vStreamProc_GetScheduleEntryTable(EntryIdx) < VSTREAMPROC_SCHEDULER_MAGIC_ENTRYUNUSED)

/* PRQA S 3453 2 */ /* MD_MSR_FctLikeMacro */
#define vStreamProc_Scheduler_Is_EntryUnused(EntryIdx) \
    (vStreamProc_GetScheduleEntryTable(EntryIdx) >= VSTREAMPROC_SCHEDULER_MAGIC_ENTRYUNUSED)


/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 **********************************************************************************************************************/


/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 **********************************************************************************************************************/

#define VSTREAMPROC_START_SEC_CODE
#include "MemMap.h"                                                                                                     /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  vStreamProc_Scheduler_AddSchedulerEntry
 *********************************************************************************************************************/
/*!
 * \brief         Adds a node to the schedule table
 * \details       -
 * \param[in]     SchedulerId  Id of the scheduler workspace.
 * \param[in]     NodeToAdd    Id of the node that should be added to the schedule table
 * \pre           -
 * \context       TASK|ISR
 * \reentrant     TRUE
 * \synchronous   TRUE
 *********************************************************************************************************************/
VSTREAMPROC_LOCAL FUNC(void, AUTOMATIC) vStreamProc_Scheduler_AddSchedulerEntry(
  CONST(vStreamProc_SchedulerIterType, AUTOMATIC) SchedulerId,
  CONST(vStreamProc_NodeIterType, AUTOMATIC) NodeToAdd);

/**********************************************************************************************************************
 *  vStreamProc_Scheduler_ContainsSchedulerEntry
 *********************************************************************************************************************/
/*!
 * \brief         Checks if a passed node is contained in a schedule table
 * \details       -
 * \param[in]     SchedulerId    Id of the scheduler workspace.
 * \param[in]     NodeToTest     Id of the node that should be check if it is contained in the schedule table
 * \return        TRUE           Node is in schedule table
 * \return        FALSE          Node is not in schedule table
 * \pre           -
 * \context       TASK|ISR
 * \reentrant     TRUE
 * \synchronous   TRUE
 *********************************************************************************************************************/
VSTREAMPROC_LOCAL FUNC(boolean, AUTOMATIC) vStreamProc_Scheduler_ContainsSchedulerEntry(
  CONST(vStreamProc_SchedulerIterType, AUTOMATIC) SchedulerId,
  CONST(vStreamProc_NodeIterType, AUTOMATIC) NodeToTest);

/**********************************************************************************************************************
*  vStreamProc_Scheduler_IsScheduleTableEmpty
*********************************************************************************************************************/
/*!
* \brief         Checks if the schedule table of the passed node is empty
* \details       -
* \param[in]     SchedulerId    Id of the scheduler workspace.
* \return        TRUE           Schedule table is empty
* \return        FALSE          Schedule table is not empty
* \pre           -
* \context       TASK|ISR
* \reentrant     TRUE
* \synchronous   TRUE
*********************************************************************************************************************/
VSTREAMPROC_LOCAL FUNC(boolean, AUTOMATIC) vStreamProc_Scheduler_IsScheduleTableEmpty(
  CONST(vStreamProc_SchedulerIterType, AUTOMATIC) SchedulerId);

/**********************************************************************************************************************
*  vStreamProc_Scheduler_ProcessNode
*********************************************************************************************************************/
/*!
 * \brief         Processes the currently scheduled node.
 * \details       -
 * \param[in]     ScheduleEntryValue    The current scheduler entry.
 * \param[out]    WorkDone              TRUE if node performed some actual work, FALSE otherwise.
 * \return        VSTREAMPROC_OK                    Processing of node finished successfully.
 * \return        VSTREAMPROC_PENDING               Processing of node associated is not yet finished.
 * \return        VSTREAMPROC_INSUFFICIENT_INPUT    Node cannot continue processing due to an entry point not containing
 *                                                  enough data.
 * \return        VSTREAMPROC_INSUFFICIENT_OUTPUT   Node cannot continue processing due to an exit point not providing
 *                                                  enough free memory.
 * \return        VSTREAMPROC_FAILED                Processing of node failed.
 * \pre           -
 * \context       TASK|ISR
 * \reentrant     TRUE
 * \synchronous   TRUE
 *********************************************************************************************************************/
VSTREAMPROC_LOCAL_INLINE FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_Scheduler_ProcessNode(
  vStreamProc_ScheduleEntryTableIterType ScheduleEntryValue,
  P2VAR(boolean, AUTOMATIC, VSTREAMPROC_APPL_DATA) WorkDone);

/**********************************************************************************************************************
*  LOCAL FUNCTIONS
*********************************************************************************************************************/

/***********************************************************************************************************************
 *  vStreamProc_Scheduler_AddSchedulerEntry
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
VSTREAMPROC_LOCAL FUNC(void, AUTOMATIC)  vStreamProc_Scheduler_AddSchedulerEntry(
  CONST(vStreamProc_SchedulerIterType, AUTOMATIC) SchedulerId,
  CONST(vStreamProc_NodeIterType, AUTOMATIC) NodeToAdd)
{
  /* ----- Local Variables ---------------------------------------------- */
  vStreamProc_ScheduleEntryTableIterType entryIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if node is already in scheduler:
          It is not: Add the passed node to the schedule table
          It is: Do not add the node to the schedule table */
  if (vStreamProc_Scheduler_ContainsSchedulerEntry(SchedulerId, NodeToAdd) == FALSE)
  {
    /* Find empty schedule table entry */
    for (entryIdx = vStreamProc_GetScheduleEntryTableStartIdxOfScheduler(SchedulerId); entryIdx < vStreamProc_GetScheduleEntryTableEndIdxOfScheduler(SchedulerId); entryIdx++)
    {
      if (vStreamProc_Scheduler_Is_EntryUnused(entryIdx))
      {
        vStreamProc_SetScheduleEntryTable(entryIdx, NodeToAdd);
        break;
      }
    }
  }
}

/***********************************************************************************************************************
 *  vStreamProc_Scheduler_ContainsSchedulerEntry
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
VSTREAMPROC_LOCAL FUNC(boolean, AUTOMATIC) vStreamProc_Scheduler_ContainsSchedulerEntry(
  CONST(vStreamProc_SchedulerIterType, AUTOMATIC) SchedulerId,
  CONST(vStreamProc_NodeIterType, AUTOMATIC) NodeToTest)
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean retVal = FALSE;
  vStreamProc_ScheduleEntryTableIterType entryIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if passed node is already in schedule table:
          It is not: return false
          It is: return true */
  for (entryIdx = vStreamProc_GetScheduleEntryTableStartIdxOfScheduler(SchedulerId);
       entryIdx < vStreamProc_GetScheduleEntryTableEndIdxOfScheduler(SchedulerId);
       entryIdx++)
  {
    if (vStreamProc_GetScheduleEntryTable(entryIdx) == NodeToTest)
    {
      retVal = TRUE;
      break;
    }
  }

  return retVal;
}

/***********************************************************************************************************************
 *  vStreamProc_Scheduler_IsScheduleTableEmpty
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
VSTREAMPROC_LOCAL FUNC(boolean, AUTOMATIC) vStreamProc_Scheduler_IsScheduleTableEmpty(
  CONST(vStreamProc_SchedulerIterType, AUTOMATIC) SchedulerId)
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean retVal = TRUE;
  vStreamProc_ScheduleEntryTableIterType scheduleTableEntryIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Verify for each schedule table entry that it is empty:
          It is not: return false
          It is: return true */
  for ( scheduleTableEntryIdx = vStreamProc_GetScheduleEntryTableStartIdxOfScheduler(SchedulerId);
        scheduleTableEntryIdx < vStreamProc_GetScheduleEntryTableEndIdxOfScheduler(SchedulerId);
        scheduleTableEntryIdx++)
  {
    if (vStreamproc_Scheduler_Is_EntryUsed(scheduleTableEntryIdx))
    {
      retVal = FALSE;
      break;
    }
  }

  return retVal;
}

/***********************************************************************************************************************
 *  vStreamProc_Scheduler_ProcessNode
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
VSTREAMPROC_LOCAL_INLINE FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_Scheduler_ProcessNode(
  vStreamProc_ScheduleEntryTableIterType ScheduleEntryValue,
  P2VAR(boolean, AUTOMATIC, VSTREAMPROC_APPL_DATA) WorkDone)
{
  vStreamProc_ReturnType retVal = VSTREAMPROC_FAILED;                                                                   /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vStreamProc_NodeIdType                                nodeId              = (vStreamProc_NodeIdType)vStreamProc_GetScheduleEntryTable(ScheduleEntryValue);
  vStreamProc_One2OneIndirectionWorkspaceIdxOfNodeType  specificNodeIdx     = vStreamProc_GetOne2OneIndirectionWorkspaceIdxOfNode(nodeId);
  boolean                                               removeFromSchedule  = TRUE;
  boolean                                               workDone            = TRUE;

  /* #10 Differentiate between processing and storage nodes. */
  if (vStreamProc_GetTypeOfNode(nodeId) == VSTREAMPROC_PROCESSING_NODE_TYPEOFNODE)
  {
    vStreamProc_ProcessingNodeInfoType  nodeInfo;
    vStreamProc_ReturnType              inputPortResults[vStreamProcConf_MaxInputPortCount];
    vStreamProc_ReturnType              outputPortResults[vStreamProcConf_MaxOutputPortCount];

    vStreamProc_InitProcessingNodeInfo((vStreamProc_ProcessingNodeIdType)specificNodeIdx, inputPortResults, outputPortResults, &nodeInfo);

    /* #20 Call process function of processing node. */
    retVal   = vStreamProc_GetProcessFctOfProcessingNodeDef(vStreamProc_GetProcessingNodeDefIdxOfProcessingNode(specificNodeIdx))(&nodeInfo);

    /* #30 Remap insufficient memory failures for processing nodes, which are not connected to entry or exit points. */
    switch (retVal)
    {
      case VSTREAMPROC_PENDING:
      {
        removeFromSchedule = FALSE;
        break;
      }
      case VSTREAMPROC_INSUFFICIENT_INPUT:
      {
        /* Only nodes at the border of the pipe should trigger this return value. Remap to pending result for others. */
        if (vStreamProc_Scheduler_IsStarvedInputPortConnectedToEntryPoint(&nodeInfo) != TRUE)
        {
          retVal = VSTREAMPROC_PENDING;
        }

        workDone = FALSE;

        break;
      }
      case VSTREAMPROC_INSUFFICIENT_OUTPUT:
      {
        /* Only nodes at the border of the pipe should trigger this return value. Remap to pending result for others. */
        if (vStreamProc_Scheduler_IsStarvedOutputPortConnectedToExitPoint(&nodeInfo) != TRUE)
        {
          retVal = VSTREAMPROC_PENDING;
        }

        workDone = FALSE;

        break;
      }
      default:
      /* Values remain unchanged. */
      {
        break;
      }
    }
  }
  else /* VSTREAMPROC_STORAGE_NODE_TYPEOFNODE */
  {
    /* #40 Call process function of storage node. */
    retVal = vStreamProc_GetProcessFctOfStorageNodeDef(vStreamProc_GetStorageNodeDefIdxOfStorageNode(specificNodeIdx))((vStreamProc_StorageNodeIdType)specificNodeIdx);

    if (retVal == VSTREAMPROC_PENDING)
    {
      removeFromSchedule = FALSE;
    }
  }

  /* #50 Remove node from schedule table, unless (original) result was "pending". */
  if (removeFromSchedule == TRUE)
  {
    vStreamProc_Scheduler_Set_EntryUnused(ScheduleEntryValue);
  }

  /* #60 Report whether some actual work was done, when processing was finished or is still pending. */
  *WorkDone = workDone;

  return retVal;
}

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  vStreamProc_Scheduler_Init
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, VSTREAMPROC_CODE) vStreamProc_Scheduler_Init(
  CONST(vStreamProc_SchedulerIterType, AUTOMATIC) SchedulerId)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;
  vStreamProc_ScheduleEntryTableIterType entryIdx;
  vStreamProc_CurrentScheduleEntryIdxOfSchedulerType currentScheduleEntryIdxOfScheduler = vStreamProc_GetCurrentScheduleEntryIdxOfScheduler(SchedulerId);


  /* ----- Implementation ----------------------------------------------- */
  /* #10 For each schedule table entry, initialize the entry */
  for (entryIdx = vStreamProc_GetScheduleEntryTableStartIdxOfScheduler(SchedulerId);
       entryIdx < vStreamProc_GetScheduleEntryTableEndIdxOfScheduler(SchedulerId);
       entryIdx++)
  {
    vStreamProc_Scheduler_Set_EntryUnused(entryIdx);
  }

  vStreamProc_SetCurrentScheduleEntry(
    currentScheduleEntryIdxOfScheduler, vStreamProc_GetScheduleEntryTableStartIdxOfScheduler(SchedulerId));

  retVal = E_OK;

  return retVal;
}

/***********************************************************************************************************************
 *  vStreamProc_Scheduler_Process
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_Scheduler_Process(
  CONST(vStreamProc_SchedulerIterType, AUTOMATIC) SchedulerId)
{
  /* ----- Local Variables ---------------------------------------------- */
  vStreamProc_ReturnType                                retVal = VSTREAMPROC_OK;
  vStreamProc_MaxNumberOfNodesToProcessOfSchedulerType  maxNumOfNodesToProcess =
    vStreamProc_GetMaxNumberOfNodesToProcessOfScheduler(SchedulerId);
  vStreamProc_CurrentScheduleEntryIdxOfSchedulerType    currentScheduleEntryIdxOfScheduler =
    vStreamProc_GetCurrentScheduleEntryIdxOfScheduler(SchedulerId);
  vStreamProc_ScheduleEntryTableLengthOfSchedulerType   iterationCntThreshold =
    vStreamProc_GetScheduleEntryTableLengthOfScheduler(SchedulerId);
  vStreamProc_ScheduleEntryTableIterType                iterationCnt;

  /* ----- Implementation ----------------------------------------------- */

  /* #10 Loop over the schedule table limited by the max number of nodes to process. */
  for (iterationCnt = 0u; iterationCnt < iterationCntThreshold; iterationCnt++)
  {
    vStreamProc_ScheduleEntryTableIterType currenScheduleEntryValue = vStreamProc_GetCurrentScheduleEntry(currentScheduleEntryIdxOfScheduler);

    /* #20 Execute a non empty schedule table entry. */
    if (vStreamproc_Scheduler_Is_EntryUsed(currenScheduleEntryValue))
    {
      boolean                 workDone;
      vStreamProc_ReturnType  currentNodeRetVal = vStreamProc_Scheduler_ProcessNode(currenScheduleEntryValue, &workDone);

      /* Only overwrite lower prior return values */
      if (retVal < currentNodeRetVal)
      {
        retVal = currentNodeRetVal;
      }

      /* #30 Count as processed node, if some actual work was done. */
      if (workDone == TRUE)
      {
        maxNumOfNodesToProcess--;
      }
    }

    /* Update the schedule table entry index and wrap around if necessary */
    vStreamProc_IncCurrentScheduleEntry(currentScheduleEntryIdxOfScheduler);
    if (vStreamProc_GetCurrentScheduleEntry(currentScheduleEntryIdxOfScheduler)
      >= vStreamProc_GetScheduleEntryTableEndIdxOfScheduler(SchedulerId))
    {
      vStreamProc_SetCurrentScheduleEntry(currentScheduleEntryIdxOfScheduler,
        vStreamProc_GetScheduleEntryTableStartIdxOfScheduler(SchedulerId));
    }

    if ( (maxNumOfNodesToProcess == 0u)
      || (retVal == VSTREAMPROC_FAILED) )
    {
      break;
    }
  }

  if (retVal == VSTREAMPROC_OK)
  {
    if (vStreamProc_Scheduler_IsScheduleTableEmpty(SchedulerId) == FALSE)
    {
      /* If there are still nodes to process return pending */
      retVal = VSTREAMPROC_PENDING;
    }
  }

  return retVal;
}

/***********************************************************************************************************************
 *  vStreamProc_Scheduler_HandleStreamAvailableCallout
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, VSTREAMPROC_CODE) vStreamProc_Scheduler_HandleStreamAvailableCallout(
  CONST(vStreamProc_NodeIdType, AUTOMATIC) NodeId,
  CONST(vStreamProc_SchedulerIdType, AUTOMATIC) SchedulerId)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 If the node being added is not flushed. */
  if (!vStreamProc_IsFlushedOfNodeInfo(NodeId))
  {
    boolean addEntry = TRUE;

    /* #20 Determine whether or not to schedule the node based on pipe phase and current flush level. */
    if (vStreamProc_GetPhaseOfPipeInfo(SchedulerId) == VSTREAMPROC_FLUSH_PHASEOFPIPEINFO)
    {
      vStreamProc_FlushLevelIterType currentFlushLvl = vStreamProc_GetFlushLevelIdxOfPipeInfo(SchedulerId);
      vStreamProc_EdgeIterType edge;

      for ( edge = vStreamProc_GetEdgeStartIdxOfFlushLevel(currentFlushLvl);
            edge < vStreamProc_GetEdgeEndIdxOfFlushLevel(currentFlushLvl);
            edge++ )
      {
        if (vStreamProc_GetNodeIdxOfEdge(edge) == NodeId)
        {
          /* The node being added is on the current flush level. */
          addEntry = FALSE;
          break;
        }
      }
    }

    if (addEntry == TRUE)
    {
      /* #30 Add the passed node to the schedule table. */
      vStreamProc_Scheduler_AddSchedulerEntry((vStreamProc_SchedulerIterType)SchedulerId, (vStreamProc_NodeIterType)NodeId);
    }
  }
}

/***********************************************************************************************************************
 *  vStreamProc_Scheduler_HandleDataAvailableCallout
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, VSTREAMPROC_CODE) vStreamProc_Scheduler_HandleDataAvailableCallout(
  CONST(vStreamProc_OutputPortIdType, AUTOMATIC) OutputPortId,
  CONST(vStreamProc_SchedulerIdType, AUTOMATIC) SchedulerId)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 If the passed output port has an internal scope, then add it's associated node to the scheduler. */
  if ( vStreamProc_GetPortScopeOfStorageOutputPort(OutputPortId) == VSTREAMPROC_INTERNAL_PORTSCOPEOFSTORAGEOUTPUTPORT)
  {
    vStreamProc_Scheduler_AddSchedulerEntry((vStreamProc_SchedulerIterType)SchedulerId, vStreamProc_GetNodeIdxOfStorageOutputPort(OutputPortId));
  }
}

/***********************************************************************************************************************
 *  vStreamProc_Scheduler_HandleStorageAvailableCallout
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(void, VSTREAMPROC_CODE) vStreamProc_Scheduler_HandleStorageAvailableCallout(
  vStreamProc_InputPortIdType InputPortId,
  CONST(vStreamProc_SchedulerIdType, AUTOMATIC) SchedulerId)
{
  vStreamProc_ProcessingNodeIterType  procNodeId    = vStreamProc_GetProducerOfStorageInputPort(InputPortId);
  vStreamProc_NodeIterType            genericNodeId = vStreamProc_GetNodeIdxOfProcessingNode(procNodeId);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 If the passed input port has an internal scope and the associated node isn't already scheduled or flushed: */
  if ( (vStreamProc_GetPortScopeOfStorageInputPort(InputPortId) == VSTREAMPROC_INTERNAL_PORTSCOPEOFSTORAGEINPUTPORT)
    && (vStreamProc_Scheduler_ContainsSchedulerEntry((vStreamProc_SchedulerIterType)SchedulerId, genericNodeId) == FALSE)
    && !vStreamProc_IsFlushedOfNodeInfo(genericNodeId) )
  {
    vStreamProc_NamedInputPorts2ActualPortsIterType inputPortIdx;
    boolean addEntry = TRUE;

    /* #20 Determine whether or not to schedule the node based on pipe phase and current flush level. */
    if (vStreamProc_GetPhaseOfPipeInfo(SchedulerId) == VSTREAMPROC_FLUSH_PHASEOFPIPEINFO)
    {
      vStreamProc_FlushLevelIterType currentFlushLvl = vStreamProc_GetFlushLevelIdxOfPipeInfo(SchedulerId);
      vStreamProc_EdgeIterType edge;

      for (edge = vStreamProc_GetEdgeStartIdxOfFlushLevel(currentFlushLvl);
            edge < vStreamProc_GetEdgeEndIdxOfFlushLevel(currentFlushLvl);
            edge++)
      {
        if (vStreamProc_GetNodeIdxOfEdge(edge) == genericNodeId)
        {
          /* The node being added is on the current flush level. */
          addEntry = FALSE;
          break;
        }
      }
    }

    if (addEntry == TRUE)
    {
      /* #30 Processing node is the active producer, if any of its input ports is connected to an active storage output port. */
      for (inputPortIdx = vStreamProc_GetNamedInputPorts2ActualPortsStartIdxOfProcessingNode(procNodeId);
           inputPortIdx < vStreamProc_GetNamedInputPorts2ActualPortsEndIdxOfProcessingNode(procNodeId);
           inputPortIdx++)
      {
        vStreamProc_ProcNode_StorageOutputPortsInputPortDynIterType dynIndex =
          vStreamProc_GetProcNode_StorageOutputPortsInputPortDynIdxOfNamedInputPorts2ActualPorts(inputPortIdx);

        if (dynIndex != VSTREAMPROC_NO_PROCNODE_STORAGEOUTPUTPORTSINPUTPORTDYNIDXOFNAMEDINPUTPORTS2ACTUALPORTS)
        {
          vStreamProc_ProcNode_StorageOutputPortsInputPortDynType storageOutputPortIdx =
            vStreamProc_GetProcNode_StorageOutputPortsInputPortDyn(dynIndex);

          if ((storageOutputPortIdx != VSTREAMPROC_NO_STORAGEOUTPUTPORTIDXOFEDGE)
              && vStreamProc_IsActiveInformationOfStorageOutputPortInfo(storageOutputPortIdx))
          {
            /* #40 Then add the node associated with the passed input port to the scheduler. */
            vStreamProc_Scheduler_AddSchedulerEntry((vStreamProc_SchedulerIterType)SchedulerId, genericNodeId);

            break;
          }
        }
      }
    }
  }
} /* PRQA S 6080 */ /* MD_MSR_STMIF */

/***********************************************************************************************************************
*  vStreamProc_Scheduler_IsStarvedInputPortConnectedToEntryPoint
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(boolean, AUTOMATIC) vStreamProc_Scheduler_IsStarvedInputPortConnectedToEntryPoint(
  P2CONST(vStreamProc_ProcessingNodeInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA) ProcNodeInfo)
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean retVal = FALSE;
  vStreamProc_NamedInputPorts2ActualPortsIterType procInputPortIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 If any of the provided input port specific results signals an insufficient input: */
  for (procInputPortIdx = 0u; procInputPortIdx < ProcNodeInfo->InputPortCount; procInputPortIdx++)
  {
    if (ProcNodeInfo->InputPortResults[procInputPortIdx] == VSTREAMPROC_INSUFFICIENT_INPUT)
    {
      vStreamProc_InputPortHandleType procInputPortHandle;
      boolean                         isConnected;

      /* #20 Check whether the associated storage node is connected to an entry point. */
      if ( (vStreamProc_GetInputPortHandle(ProcNodeInfo->ProcessingNodeId, (vStreamProc_InputPortSymbolicNameType)procInputPortIdx, &procInputPortHandle, &isConnected) == VSTREAMPROC_OK)
        && (isConnected == TRUE) )
      {
        vStreamProc_StorageNodeIdType         storageNodeId = procInputPortHandle.StorageNodeId;
        vStreamProc_StorageInputPortIterType  storageInputPortId;

        for ( storageInputPortId = vStreamProc_GetStorageInputPortStartIdxOfStorageNode(storageNodeId);
              storageInputPortId < vStreamProc_GetStorageInputPortEndIdxOfStorageNode(storageNodeId);
              storageInputPortId++ )
        {
          if (vStreamProc_GetPortScopeOfStorageInputPort(storageInputPortId) == VSTREAMPROC_EXTERNAL_PORTSCOPEOFSTORAGEINPUTPORT)
          {
            retVal = TRUE;
            break;
          }
        }
      }
    }

    if (retVal == TRUE)
    {
      break;
    }
  }

  return retVal;
} /* PRQA S 6080 */ /* MD_MSR_STMIF */

/***********************************************************************************************************************
*  vStreamProc_Scheduler_IsStarvedOutputPortConnectedToExitPoint
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(boolean, AUTOMATIC) vStreamProc_Scheduler_IsStarvedOutputPortConnectedToExitPoint(
  P2CONST(vStreamProc_ProcessingNodeInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA) ProcNodeInfo)
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean retVal = FALSE;
  vStreamProc_NamedOutputPorts2ActualPortsIterType procOutputPortIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 If any of the provided output port specific results signals an insufficient output: */
  for (procOutputPortIdx = 0u; procOutputPortIdx < ProcNodeInfo->OutputPortCount; procOutputPortIdx++)
  {
    if (ProcNodeInfo->OutputPortResults[procOutputPortIdx] == VSTREAMPROC_INSUFFICIENT_OUTPUT)
    {
      vStreamProc_OutputPortHandleType  procOutputPortHandle;
      boolean                           isConnected;

      /* #20 Check whether the associated storage node is connected to an (active) exit point. */
      if ( (vStreamProc_GetOutputPortHandle(ProcNodeInfo->ProcessingNodeId, (vStreamProc_OutputPortSymbolicNameType)procOutputPortIdx, &procOutputPortHandle, &isConnected) == VSTREAMPROC_OK)
        && (isConnected == TRUE) )
      {
        vStreamProc_StorageNodeIdType         storageNodeId = procOutputPortHandle;
        vStreamProc_StorageOutputPortIterType storageOutputPortId;

        for ( storageOutputPortId = vStreamProc_GetStorageOutputPortStartIdxOfStorageNode(storageNodeId);
              storageOutputPortId < vStreamProc_GetStorageOutputPortEndIdxOfStorageNode(storageNodeId);
              storageOutputPortId++ )
        {
          if ( (vStreamProc_GetPortScopeOfStorageOutputPort(storageOutputPortId) == VSTREAMPROC_EXTERNAL_PORTSCOPEOFSTORAGEOUTPUTPORT)
            && (vStreamProc_IsActiveInformationOfStorageOutputPortInfo(storageOutputPortId) == TRUE) )                  /* PRQA S 1881 */ /* MD_MSR_AutosarBoolean */
          {
            retVal = TRUE;
            break;
          }
        }
      }

      if (retVal == TRUE)
      {
        break;
      }
    }
  }

  return retVal;
} /* PRQA S 6080 */ /* MD_MSR_STMIF */

/***********************************************************************************************************************
*  vStreamProc_Scheduler_RemoveFromScheduleTable
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, AUTOMATIC) vStreamProc_Scheduler_RemoveFromScheduleTable(
  CONST(vStreamProc_SchedulerIterType, AUTOMATIC) SchedulerId,
  CONST(vStreamProc_NodeIterType, AUTOMATIC) NodeToRemove)
{
  /* ----- Local Variables ---------------------------------------------- */
  vStreamProc_ScheduleEntryTableIterType entryIdx;


  /* ----- Implementation ----------------------------------------------- */
  /* #10 Search the passed node in the schedule table:
          It is not found: Do nothing
          It is found: Remove it from the schedule table */
  for (entryIdx = vStreamProc_GetScheduleEntryTableStartIdxOfScheduler(SchedulerId);
        entryIdx < vStreamProc_GetScheduleEntryTableEndIdxOfScheduler(SchedulerId);
        entryIdx++)
  {
    if (vStreamProc_GetScheduleEntryTable(entryIdx) == NodeToRemove)
    {
      vStreamProc_Scheduler_Set_EntryUnused(entryIdx);
      break;
    }
  }
}

#define VSTREAMPROC_STOP_SEC_CODE
#include "MemMap.h"                                                                                                     /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  END OF FILE: vStreamProc_Scheduler.c
 *********************************************************************************************************************/
