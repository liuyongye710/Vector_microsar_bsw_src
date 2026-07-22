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
/*!        \file  vStreamProc_Pipe.c
 *        \brief  vStreamProc Pipe Sub Module Source Code File
 *
 *      \details  Implementation of the vStreamProc Pipe sub module.
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
# define VSTREAMPROC_PIPE_SOURCE

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "vStreamProc.h"
#include "vStreamProc_Pipe.h"
#include "vStreamProc_Scheduler.h"
#include "vStreamProc_Port.h"

#if (VSTREAMPROC_DEV_ERROR_REPORT == STD_ON)
# include "Det.h"
#endif

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 **********************************************************************************************************************/
#if !defined (VSTREAMPROC_LOCAL)
# define VSTREAMPROC_LOCAL static
#endif

#if !defined (VSTREAMPROC_LOCAL_INLINE)
# define VSTREAMPROC_LOCAL_INLINE LOCAL_INLINE
#endif

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 **********************************************************************************************************************/

/*! Function pointer for entry point operations (used by iterator). */
typedef P2FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE, vStreamProc_EntryPointOperationPtrType)(
  vStreamProc_PipeIdType PipeId,
  vStreamProc_EntryPointInfoPtrType EntryPointInfo);

/*! Function pointer for exit point operations (used by iterator). */
typedef P2FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE, vStreamProc_ExitPointOperationPtrType)(
  vStreamProc_PipeIdType PipeId,
  vStreamProc_ExitPointInfoPtrType ExitPointInfo);

/*! Symbolic names of access point operations (used by iterator). */
typedef enum
{
#if (VSTREAMPROC_DEV_ERROR_DETECT == STD_ON)
  VSTREAMPROC_ACCESS_POINT_OPERATION_CHECK_INFO,
#endif
  VSTREAMPROC_ACCESS_POINT_OPERATION_PREPARE_INFO,
  VSTREAMPROC_ACCESS_POINT_OPERATION_GET_INFO,
  VSTREAMPROC_ACCESS_POINT_OPERATION_REQUEST_DATA,
  VSTREAMPROC_ACCESS_POINT_OPERATION_ACKNOWLEDGE,
  VSTREAMPROC_ACCESS_POINT_OPERATION_RELEASE,
  VSTREAMPROC_ACCESS_POINT_OPERATION_COUNT
} vStreamProc_AccessPointOperationType;

/*! Configuration element for access point operations (used by iterator). */
typedef struct
{
  vStreamProc_EntryPointOperationPtrType EntryPointOperation;
  vStreamProc_ExitPointOperationPtrType  ExitPointOperation;
} vStreamProc_AccessPointOperationConfigType;

/*! Parameter structure for access point iterator. */
typedef struct
{
  vStreamProc_PipeIdType                PipeId;
  vStreamProc_AccessPointOperationType  Operation;
  boolean                               AbortOnError;
} vStreamProc_AccessPointIteratorParamType;

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
 * vStreamProc_Pipe_InitProcessingNode()
 **********************************************************************************************************************/
/*! \brief      Initialize the given processing node.
 *  \details    -
 *  \param[in]  ProcessingNodeId  The processing node's ID.
 *  \return     E_OK              Initialization was successful
 *  \return     E_NOT_OK          Initialization was not successful
 *  \context    TASK
 *  \reentrant  TRUE
 *  \pre        -
 *********************************************************************************************************************/
VSTREAMPROC_LOCAL_INLINE FUNC(Std_ReturnType, VSTREAMPROC_CODE) vStreamProc_Pipe_InitProcessingNode(
  vStreamProc_ProcessingNodeIdType ProcessingNodeId);

/**********************************************************************************************************************
 * vStreamProc_Pipe_StartFlushLevel()
 **********************************************************************************************************************/
/*! \brief      Start the given flush level.
 *  \details    -
 *  \param[in]  PipeId            The pipe to operate on.
 *  \param[in]  FlushLevelId      The flush level which shall be started.
 *  \context    TASK
 *  \reentrant  TRUE
 *  \pre        -
 *********************************************************************************************************************/
VSTREAMPROC_LOCAL FUNC(void, VSTREAMPROC_CODE) vStreamProc_Pipe_StartFlushLevel(
  vStreamProc_PipeIterType PipeId,
  vStreamProc_FlushLevelIterType FlushLevelId);

/**********************************************************************************************************************
 * vStreamProc_Pipe_PrepareFlush()
 **********************************************************************************************************************/
/*! \brief      Prepare the pipe flush operation.
 *  \details    Checks the preconditions and sets up the first flush level on the initial call.
 *  \param[in]  PipeId            The pipe to operate on.
 *  \return     VSTREAMPROC_OK        Flush of pipe already completed.
 *  \return     VSTREAMPROC_PENDING   Flush of pipe is not finished yet.
 *  \return     VSTREAMPROC_FAILED    Pipe is not in the correct state for the flush operation.
 *  \context    TASK
 *  \reentrant  TRUE
 *  \pre        Pipe is either in processing or flush state.
 *********************************************************************************************************************/
VSTREAMPROC_LOCAL_INLINE FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_Pipe_PrepareFlush(
  vStreamProc_PipeIterType PipeId);

/**********************************************************************************************************************
 * vStreamProc_Pipe_IsFlushOfEdgeRequired()
 **********************************************************************************************************************/
/*! \brief      Check whether given edge needs to be flushed.
 *  \details    -
 *  \param[in]  EdgeIdx           The edge which shall be checked.
 *  \return     TRUE              The edge needs to be flushed.
 *  \return     FALSE             The edge doesn't need to be flushed.
 *  \context    TASK
 *  \reentrant  TRUE
 *  \pre        -
 *********************************************************************************************************************/
VSTREAMPROC_LOCAL_INLINE FUNC(boolean, VSTREAMPROC_CODE) vStreamProc_Pipe_IsFlushOfEdgeRequired(
  vStreamProc_EdgeIterType EdgeIdx);

/**********************************************************************************************************************
 * vStreamProc_Pipe_FlushEdge()
 **********************************************************************************************************************/
/*! \brief      Flush the node associated with the given edge.
 *  \details    Actual flush will only be performed when edge is activate.
 *  \param[in]  PipeId            The pipe to operate on.
 *  \param[in]  EdgeIdx           The edge which shall be flushed.
 *  \return     VSTREAMPROC_OK                    Flush of node associated with edge was successful.
 *  \return     VSTREAMPROC_PENDING               Flush of node associated with edge is not yet finished.
 *  \return     VSTREAMPROC_INSUFFICIENT_INPUT    Node associated with edge cannot be flushed due to an entry point
 *                                                not containing enough data.
 *  \return     VSTREAMPROC_INSUFFICIENT_OUTPUT   Node associated with edge cannot be flushed due to an exit point
 *                                                not providing enough free memory.
 *  \return     VSTREAMPROC_FAILED                Flush of node associated with edge failed.
 *  \context    TASK
 *  \reentrant  TRUE
 *  \pre        -
 *********************************************************************************************************************/
VSTREAMPROC_LOCAL_INLINE FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_Pipe_FlushEdge(
  vStreamProc_PipeIterType PipeId,
  vStreamProc_EdgeIterType EdgeIdx);

/**********************************************************************************************************************
 * vStreamProc_Pipe_ConcludeEdgeFlush()
 **********************************************************************************************************************/
/*! \brief          Conclude the successful flush of an edge.
 *  \details        Forwards the flush level if necessary or reports that all levels are flushed.
 *  \param[in]      PipeId            The pipe to operate on.
 *  \param[in,out]  FlushLevelIdx     In: The current flush level.
 *                                    Out: The flush level to be used for the next cycle.
 *  \param[in,out]  EdgeIdx           In: The edge which was successfully flushed.
 *                                    Out: First edge if new flush level is started. Unchanged otherwise.
 *  \return         VSTREAMPROC_OK        Flush of pipe completed.
 *  \return         VSTREAMPROC_PENDING   Flush of pipe is not finished yet.
 *  \context        TASK
 *  \reentrant      TRUE
 *  \pre            -
 *********************************************************************************************************************/
VSTREAMPROC_LOCAL_INLINE FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_Pipe_ConcludeEdgeFlush(
  vStreamProc_PipeIterType PipeId,
  P2VAR(vStreamProc_FlushLevelIterType, AUTOMATIC, VSTREAMPROC_APPL_DATA) FlushLevelIdx,
  P2VAR(vStreamProc_EdgeIterType, AUTOMATIC, VSTREAMPROC_APPL_DATA) EdgeIdx);

/**********************************************************************************************************************
 * vStreamProc_Pipe_FinishFlush()
 **********************************************************************************************************************/
/*! \brief      Finish the flushing of the pipe.
 *  \details    Check whether all output ports of storage nodes with internal scope were completely consumed.
 *  \param[in]  PipeId                The pipe to operate on.
 *  \return     VSTREAMPROC_OK        Flush of pipe successfully completed.
 *  \return     VSTREAMPROC_FAILED    Flush of pipe failed - not all internal data was consumed.
 *  \context    TASK
 *  \reentrant  TRUE
 *  \pre        -
 *********************************************************************************************************************/
VSTREAMPROC_LOCAL_INLINE FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_Pipe_FinishFlush(
  vStreamProc_PipeIterType PipeId);

/**********************************************************************************************************************
 * vStreamProc_Pipe_ConcludeFlushCycle()
 **********************************************************************************************************************/
/*! \brief          Conclude the current flush cycle.
 *  \details        Search next edge in current level which wasn't flushed yet.
 *  \param[in]      FlushLevelIdx   The current flush level.
 *  \param[in,out]  EdgeIdx         In: The edge which was processed.
 *                                  Out: The next edge in the current level which wasn't flushed yet.
 *  \context        TASK
 *  \reentrant      TRUE
 *  \pre            Current level mustn't be completely flushed.
 *********************************************************************************************************************/
VSTREAMPROC_LOCAL_INLINE FUNC(void, VSTREAMPROC_CODE) vStreamProc_Pipe_ConcludeFlushCycle(
  vStreamProc_FlushLevelIterType FlushLevelIdx,
  P2VAR(vStreamProc_EdgeIterType, AUTOMATIC, VSTREAMPROC_APPL_DATA) EdgeIdx);

/**********************************************************************************************************************
 * vStreamProc_Pipe_PerformFlush()
 **********************************************************************************************************************/
/*! \brief      Perform actual flush of the pipe.
 *  \details    -
 *  \param[in]  PipeId            The pipe to operate on.
 *  \return     VSTREAMPROC_OK                    Flush of pipe completed.
 *  \return     VSTREAMPROC_PENDING               Flush of pipe is not finished yet.
 *  \return     VSTREAMPROC_INSUFFICIENT_INPUT    Pipe cannot be flushed due to an entry point not containing
 *                                                enough data.
 *  \return     VSTREAMPROC_INSUFFICIENT_OUTPUT   Pipe cannot be flushed due to an exit point not providing enough
 *                                                free memory.
 *  \return     VSTREAMPROC_FAILED                Flush of pipe failed.
 *  \context    TASK
 *  \reentrant  TRUE
 *  \pre        -
 *********************************************************************************************************************/
VSTREAMPROC_LOCAL_INLINE FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_Pipe_PerformFlush(
  vStreamProc_PipeIterType PipeId);

/**********************************************************************************************************************
 * vStreamProc_Pipe_ApplyMode()
 **********************************************************************************************************************/
/*! \brief      Apply the given mode to the pipe.
 *  \details    Switches base states configured for given mode.
 *              Stores a copy of the previous base state values, which is used by vStreamProc_Pipe_RevertModeApplication.
 *  \param[in]  PipeId            The pipe to operate on.
 *  \param[in]  PipeModeId        The mode to apply.
 *                                Use VSTREAMPROC_NO_MODE to set all base states to their default values.
 *  \context    TASK
 *  \reentrant  TRUE
 *  \pre        -
 *********************************************************************************************************************/
VSTREAMPROC_LOCAL_INLINE FUNC(void, VSTREAMPROC_CODE) vStreamProc_Pipe_ApplyMode(
  vStreamProc_PipeIterType PipeId,
  vStreamProc_ModeIterType PipeModeId);

/**********************************************************************************************************************
 * vStreamProc_Pipe_RevertModeApplication()
 **********************************************************************************************************************/
/*! \brief      Reverts the previous application of a mode.
 *  \details    Restores the previous base state values.
 *  \param[in]  PipeId            The pipe to operate on.
 *  \context    TASK
 *  \reentrant  TRUE
 *  \pre        vStreamProc_Pipe_ApplyMode must be called before to create a copy of the base state values.
 *********************************************************************************************************************/
VSTREAMPROC_LOCAL_INLINE FUNC(void, VSTREAMPROC_CODE) vStreamProc_Pipe_RevertModeApplication(
  vStreamProc_PipeIterType PipeId);

/**********************************************************************************************************************
 * vStreamProc_Pipe_EvaluateMetaStates()
 **********************************************************************************************************************/
/*! \brief      Evaluate active meta states for current base state values.
 *  \details    -
 *  \param[in]  PipeId            The pipe to operate on.
 *  \context    TASK
 *  \reentrant  TRUE
 *  \pre        -
 *********************************************************************************************************************/
VSTREAMPROC_LOCAL FUNC(void, VSTREAMPROC_CODE) vStreamProc_Pipe_EvaluateMetaStates(
  vStreamProc_PipeIterType PipeId);

/**********************************************************************************************************************
 * vStreamProc_Pipe_SwitchPortActivations()
 **********************************************************************************************************************/
/*! \brief      Switch port activations based on active meta states.
 *  \details    -
 *  \param[in]  PipeId            The pipe to operate on.
 *  \return     E_OK - success
 *  \return     E_NOT_OK - error
 *  \context    TASK
 *  \reentrant  TRUE
 *  \pre        -
 *********************************************************************************************************************/
VSTREAMPROC_LOCAL FUNC(Std_ReturnType, VSTREAMPROC_CODE) vStreamProc_Pipe_SwitchPortActivations(
  vStreamProc_PipeIterType PipeId);

/**********************************************************************************************************************
 * vStreamProc_Pipe_HandleMetaStateSwitching()
 **********************************************************************************************************************/
/*! \brief      Switch active ports, based on given mode.
 *  \details    Applies mode, evaluates active meta states and switches port activations.
 *  \param[in]  PipeId            The pipe to operate on.
 *  \param[in]  PipeModeId        The mode to apply.
 *                                Use VSTREAMPROC_NO_MODE to reset activation to default configuration.
 *  \return     E_OK - success
 *  \return     E_NOT_OK - error
 *  \context    TASK
 *  \reentrant  TRUE
 *  \pre        -
 *********************************************************************************************************************/
VSTREAMPROC_LOCAL FUNC(Std_ReturnType, VSTREAMPROC_CODE) vStreamProc_Pipe_HandleMetaStateSwitching(
  vStreamProc_PipeIterType PipeId,
  vStreamProc_ModeIterType PipeModeId);

/**********************************************************************************************************************
 * vStreamProc_Pipe_RevertMetaStateSwitching()
 **********************************************************************************************************************/
/*! \brief      Reverts the previous port activation before a mode switch.
 *  \details    -
 *  \param[in]  PipeId            The pipe to operate on.
 *  \context    TASK
 *  \reentrant  TRUE
 *  \pre        vStreamProc_Pipe_ApplyMode must be called before to create a copy of the base state values.
 *********************************************************************************************************************/
VSTREAMPROC_LOCAL_INLINE FUNC(void, VSTREAMPROC_CODE) vStreamProc_Pipe_RevertMetaStateSwitching(
  vStreamProc_PipeIterType PipeId);

/**********************************************************************************************************************
 * vStreamProc_Pipe_PrepareStorageInfo()
 **********************************************************************************************************************/
/*! \brief      Initialize storage info structure with default values.
 *  \details    -
 *  \param[out] StorageInfo   The storage info structure to be initialized.
 *  \context    TASK
 *  \reentrant  TRUE
 *  \pre        -
 *********************************************************************************************************************/
VSTREAMPROC_LOCAL FUNC(void, VSTREAMPROC_CODE) vStreamProc_Pipe_PrepareStorageInfo(
  P2VAR(vStreamProc_StorageInfoType, AUTOMATIC, VSTREAMPROC_APPL_VAR) StorageInfo);

#if (VSTREAMPROC_DEV_ERROR_DETECT == STD_ON)
/**********************************************************************************************************************
 *  vStreamProc_Pipe_CheckEntryPointInfo()
 *********************************************************************************************************************/
/*!
 * \brief         Check the entry point info attributes for plausibility.
 * \details       -
 * \param[in]     PipeId            Id of the desired pipe.
 * \param[in]     EntryPointInfo    Pointer to entry point information structure.
 *                - WriteRequest.StorageInfo.DataTypeInfo.Id    Id of the expected data type of the storage node
 *                                                              connected to the access point.
 *                                                              vStreamProcConf_vStreamProcDataType_Undefined if no
 *                                                              specific data type is expected.
 *                - EntryPointId                                Id of an entry point of the desired pipe.
 * \return        VSTREAMPROC_OK                    Operation was successful.
 * \return        VSTREAMPROC_FAILED                Operation was unsuccessful.
 * \pre           The pipe is open.
 * \context       TASK|ISR
 * \reentrant     TRUE
 * \synchronous   TRUE
 *********************************************************************************************************************/
VSTREAMPROC_LOCAL FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_Pipe_CheckEntryPointInfo(
  vStreamProc_PipeIdType PipeId,
  vStreamProc_EntryPointInfoPtrType EntryPointInfo);

/**********************************************************************************************************************
 *  vStreamProc_Pipe_CheckExitPointInfo()
 *********************************************************************************************************************/
/*!
 * \brief         Check the exit point info attributes for plausibility.
 * \details       -
 * \param[in]     PipeId            Id of the desired pipe.
 * \param[in]     ExitPointInfo     Pointer to exit point information structure.
 *                - ReadRequest.StorageInfo.DataTypeInfo.Id     Id of the expected data type of the storage node
 *                                                              connected to the access point.
 *                                                              vStreamProcConf_vStreamProcDataType_Undefined if no
 *                                                              specific data type is expected.
 *                - ExitPointId                                 Id of an entry point of the desired pipe.
 * \return        VSTREAMPROC_OK                    Operation was successful.
 * \return        VSTREAMPROC_FAILED                Operation was unsuccessful.
 * \pre           The pipe is open.
 * \context       TASK|ISR
 * \reentrant     TRUE
 * \synchronous   TRUE
 *********************************************************************************************************************/
VSTREAMPROC_LOCAL FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_Pipe_CheckExitPointInfo(
  vStreamProc_PipeIdType PipeId,
  vStreamProc_ExitPointInfoPtrType ExitPointInfo);
#endif

/**********************************************************************************************************************
 *  vStreamProc_Pipe_ReleaseEntryPoint()
 *********************************************************************************************************************/
/*!
 * \brief         Releases storage lock of an entry point.
 * \details       -
 * \param[in]     PipeId            Id of the desired pipe.
 * \param[in]     EntryPointInfo    Pointer to entry point information structure.
 *                - EntryPointId                                Id of an entry point of the desired pipe.
 * \return        VSTREAMPROC_OK                    Operation was successful.
 * \return        VSTREAMPROC_FAILED                Operation was unsuccessful.
 * \pre           The pipe is open.
 * \context       TASK|ISR
 * \reentrant     TRUE
 * \synchronous   TRUE
 *********************************************************************************************************************/
VSTREAMPROC_LOCAL FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_Pipe_ReleaseEntryPoint(
  vStreamProc_PipeIdType PipeId,
  vStreamProc_EntryPointInfoPtrType EntryPointInfo);


/**********************************************************************************************************************
 *  vStreamProc_Pipe_ReleaseExitPoint()
 *********************************************************************************************************************/
/*!
 * \brief         Releases storage lock of an exit point.
 * \details       -
 * \param[in]     PipeId            Id of the desired pipe.
 * \param[in]     ExitPointInfo     Pointer to exit point information structure.
 *                - ExitPointId                                Id of an exit point of the desired pipe.
 * \return        VSTREAMPROC_OK                    Operation was successful.
 * \return        VSTREAMPROC_FAILED                Operation was unsuccessful.
 * \pre           The pipe is open.
 * \context       TASK|ISR
 * \reentrant     TRUE
 * \synchronous   TRUE
 *********************************************************************************************************************/
VSTREAMPROC_LOCAL FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_Pipe_ReleaseExitPoint(
  vStreamProc_PipeIdType PipeId,
  vStreamProc_ExitPointInfoPtrType ExitPointInfo);

/**********************************************************************************************************************
 * vStreamProc_Pipe_InitAccessPointIteratorParam()
 **********************************************************************************************************************/
/*! \brief          Initialize parameter structure for access point iterator.
 *  \details        -
 *  \param[in]      PipeId            The pipe to operate on.
 *  \param[in]      Operation         The operation to apply to all access point structures.
 *  \param[in]      AbortOnError      Abort the iteration in case any other result than VSTREAMPROC_OK is returned
 *                                    when applying the operation to an access point structure.
 *  \return         Initialized vStreamProc_AccessPointIteratorParamType structure.
 *  \context        TASK
 *  \reentrant      TRUE
 *  \pre            -
 *********************************************************************************************************************/
VSTREAMPROC_LOCAL_INLINE FUNC(vStreamProc_AccessPointIteratorParamType, VSTREAMPROC_CODE) vStreamProc_Pipe_InitAccessPointIteratorParam(
  vStreamProc_PipeIdType PipeId,
  vStreamProc_AccessPointOperationType Operation,
  boolean AbortOnError);

/**********************************************************************************************************************
 * vStreamProc_Pipe_IterateAccessPointInfos()
 **********************************************************************************************************************/
/*! \brief          Iterate over all passed access point structures and apply the given operation.
 *  \details        -
 *  \param[in]      IteratorParam     The iterator parameter structure.
 *  \param[in,out]  EntryPointInfos   Entry point information structures. NULL_PTR if not used.
 *  \param[in]      EntryPointCount   Number of entry point information structures.
 *  \param[in,out]  ExitPointInfos    Exit point information structures. NULL_PTR if not used.
 *  \param[in]      ExitPointCount    Number of exit point information structures.
 *  \return         VSTREAMPROC_FAILED                Operation failed for at least one access point.
 *  \return         VSTREAMPROC_INSUFFICIENT_OUTPUT   At least one access point cannot provide the requested minimum storage.
 *  \return         VSTREAMPROC_INSUFFICIENT_INPUT    At least one access point cannot provide the requested minimum data.
 *  \return         VSTREAMPROC_OK                    Operation was successful for all access points.
 *  \context        TASK
 *  \reentrant      TRUE
 *  \pre            -
 *********************************************************************************************************************/
VSTREAMPROC_LOCAL FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_Pipe_IterateAccessPointInfos(
  vStreamProc_AccessPointIteratorParamType IteratorParam,
  vStreamProc_EntryPointInfoPtrType EntryPointInfos,
  vStreamProc_EntryPointIdType EntryPointCount,
  vStreamProc_ExitPointInfoPtrType ExitPointInfos,
  vStreamProc_ExitPointIdType ExitPointCount);

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * vStreamProc_Pipe_InitProcessingNode()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
VSTREAMPROC_LOCAL_INLINE FUNC(Std_ReturnType, VSTREAMPROC_CODE) vStreamProc_Pipe_InitProcessingNode(
  vStreamProc_ProcessingNodeIdType ProcessingNodeId)
{
  Std_ReturnType retVal;

  vStreamProc_NamedInputPorts2ActualPortsIterType inputPortIdx;
  vStreamProc_ProcessingNodeInfoType              nodeInfo;
  vStreamProc_ReturnType                          inputPortResults[vStreamProcConf_MaxInputPortCount];
  vStreamProc_ReturnType                          outputPortResults[vStreamProcConf_MaxOutputPortCount];

  /* #10 Reset dynamic input port mapping of processing node. */
  for ( inputPortIdx = vStreamProc_GetNamedInputPorts2ActualPortsStartIdxOfProcessingNode(ProcessingNodeId);
        inputPortIdx < vStreamProc_GetNamedInputPorts2ActualPortsEndIdxOfProcessingNode(ProcessingNodeId);
        inputPortIdx++ )
  {
    vStreamProc_ProcNode_StorageOutputPortsInputPortDynIterType dynIndex =
      vStreamProc_GetProcNode_StorageOutputPortsInputPortDynIdxOfNamedInputPorts2ActualPorts(inputPortIdx);

    if (dynIndex != VSTREAMPROC_NO_PROCNODE_STORAGEOUTPUTPORTSINPUTPORTDYNIDXOFNAMEDINPUTPORTS2ACTUALPORTS)
    {
      vStreamProc_SetProcNode_StorageOutputPortsInputPortDyn(dynIndex, VSTREAMPROC_NO_STORAGEOUTPUTPORTIDXOFEDGE);
    }
  }

  /* #20 Trigger the init function of the node. */
  vStreamProc_InitProcessingNodeInfo(ProcessingNodeId, inputPortResults, outputPortResults, &nodeInfo);

  retVal = vStreamProc_GetInitFctOfProcessingNodeDef(vStreamProc_GetProcessingNodeDefIdxOfProcessingNode(ProcessingNodeId))(&nodeInfo);

  return retVal;
}

/**********************************************************************************************************************
 * vStreamProc_Pipe_StartFlushLevel()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
VSTREAMPROC_LOCAL FUNC(void, VSTREAMPROC_CODE) vStreamProc_Pipe_StartFlushLevel(
  vStreamProc_PipeIterType PipeId,
  vStreamProc_FlushLevelIterType FlushLevelId)
{
  /* ----- Local Variables ---------------------------------------------- */
  vStreamProc_EdgeIterType edgeStartIdx = vStreamProc_GetEdgeStartIdxOfFlushLevel(FlushLevelId);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Set active flush level in pipe info. */
  vStreamProc_SetFlushLevelIdxOfPipeInfo(PipeId, FlushLevelId);
  /* #20 Set first edge and pending edge count in flush level info. */
  vStreamProc_SetEdgeIdxOfFlushLevelInfo(FlushLevelId, edgeStartIdx);
  vStreamProc_SetPendingCountOfFlushLevelInfo(FlushLevelId, vStreamProc_GetEdgeEndIdxOfFlushLevel(FlushLevelId) - edgeStartIdx);
}

/**********************************************************************************************************************
 * vStreamProc_Pipe_PrepareFlush()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
VSTREAMPROC_LOCAL_INLINE FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_Pipe_PrepareFlush(
  vStreamProc_PipeIterType PipeId)
{
  /* ----- Local Variables ---------------------------------------------- */
  vStreamProc_ReturnType retVal = VSTREAMPROC_FAILED;                                                                   /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 If this is the initial call to flush the pipe. */
  if (vStreamProc_GetPhaseOfPipeInfo(PipeId) == VSTREAMPROC_PROCESS_PHASEOFPIPEINFO)
  {
    /* #20 Set state to flush. No new data shall be written to pipe */
    vStreamProc_SetPhaseOfPipeInfo(PipeId, VSTREAMPROC_FLUSH_PHASEOFPIPEINFO);
    /* #30 Start first flush level of pipe. */
    vStreamProc_Pipe_StartFlushLevel(PipeId, vStreamProc_GetFlushLevelStartIdxOfPipe(PipeId));
  }

  /* #40 If pipe is being flushed */
  if (vStreamProc_GetPhaseOfPipeInfo(PipeId) == VSTREAMPROC_FLUSH_PHASEOFPIPEINFO)
  {
    /* #50 Check whether last flush was already completed. */
    if (vStreamProc_GetFlushLevelIdxOfPipeInfo(PipeId) < vStreamProc_GetFlushLevelEndIdxOfPipe(PipeId))
    {
      retVal = VSTREAMPROC_PENDING;
    }
    else
    {
      retVal = VSTREAMPROC_OK;
    }
  }

  return retVal;
}

/**********************************************************************************************************************
 * vStreamProc_Pipe_IsFlushOfEdgeRequired()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
VSTREAMPROC_LOCAL_INLINE FUNC(boolean, VSTREAMPROC_CODE) vStreamProc_Pipe_IsFlushOfEdgeRequired(
  vStreamProc_EdgeIterType EdgeIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean                       retVal        = FALSE;
  vStreamProc_MetaStateIterType metaStateIdx  = vStreamProc_GetMetaStateIdxOfEdge(EdgeIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 If edge is always active (because it has no meta state dependency) or meta state referenced by edge is active */
  if ( (metaStateIdx == VSTREAMPROC_NO_METASTATEIDXOFEDGE)
    || (vStreamProc_HasMetaStateInfo() && vStreamProc_IsActiveOfMetaStateInfo(metaStateIdx)) )
  {
    vStreamProc_NodeIterType nodeIdx = vStreamProc_GetNodeIdxOfEdge(EdgeIdx);

    /* #20 Check whether node wasn't flushed before. */
    if (!vStreamProc_IsFlushedOfNodeInfo(nodeIdx))
    {
      retVal = TRUE;
    }
  }

  return retVal;
}

/**********************************************************************************************************************
 * vStreamProc_Pipe_FlushEdge()
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
VSTREAMPROC_LOCAL_INLINE FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_Pipe_FlushEdge(
  vStreamProc_PipeIterType PipeId,
  vStreamProc_EdgeIterType EdgeIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  vStreamProc_ReturnType retVal = VSTREAMPROC_FAILED;                                                                   /* PRQA S 2981 */ /* MD_MSR_RetVal */

  vStreamProc_NodeIterType                          nodeId          = vStreamProc_GetNodeIdxOfEdge(EdgeIdx);
  vStreamProc_One2OneIndirectionWorkspaceOfNodeType specificNodeIdx = vStreamProc_GetOne2OneIndirectionWorkspaceIdxOfNode(nodeId);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Remove node referenced by edge from scheduler table. */
  vStreamProc_Scheduler_RemoveFromScheduleTable(PipeId, nodeId);

  /* #20 Differentiate between processing and storage nodes. */
  if (vStreamProc_GetTypeOfNode(nodeId) == VSTREAMPROC_PROCESSING_NODE_TYPEOFNODE)
  {
    vStreamProc_ProcessingNodeInfoType  nodeInfo;
    vStreamProc_ReturnType              inputPortResults[vStreamProcConf_MaxInputPortCount];
    vStreamProc_ReturnType              outputPortResults[vStreamProcConf_MaxOutputPortCount];

    vStreamProc_InitProcessingNodeInfo((vStreamProc_ProcessingNodeIdType)specificNodeIdx, inputPortResults, outputPortResults, &nodeInfo);

    /* #30 Call flush function of processing node. */
    retVal = vStreamProc_GetFlushFctOfProcessingNodeDef(vStreamProc_GetProcessingNodeDefIdxOfProcessingNode(specificNodeIdx))(&nodeInfo);

    /* #40 Remap insufficient memory failures for processing nodes, which are not connected to entry or exit points. */
    switch (retVal)
    {
      case VSTREAMPROC_INSUFFICIENT_INPUT:
      {
        /* Only nodes at the border of the pipe should trigger this return value. Remap to general failure for others. */
        if (vStreamProc_Scheduler_IsStarvedInputPortConnectedToEntryPoint(&nodeInfo) != TRUE)
        {
          retVal = VSTREAMPROC_FAILED;
        }

        break;
      }
      case VSTREAMPROC_INSUFFICIENT_OUTPUT:
      {
        /* Only nodes at the border of the pipe should trigger this return value. Remap to pending result for others. */
        if (vStreamProc_Scheduler_IsStarvedOutputPortConnectedToExitPoint(&nodeInfo) != TRUE)
        {
          retVal = VSTREAMPROC_PENDING;
        }

        break;
      }
      default:
      {
        /* Nothing to be done for other values. */
        break;
      }
    }
  }
  else /* VSTREAMPROC_STORAGE_NODE_TYPEOFNODE */
  {
    /* #50 Call flush function of storage node. */
    retVal = vStreamProc_GetFlushFctOfStorageNodeDef(vStreamProc_GetStorageNodeDefIdxOfStorageNode(specificNodeIdx))((vStreamProc_StorageNodeIdType)specificNodeIdx);
  }

  /* #60 Mark node as flushed when operation finished. */
  if (retVal == VSTREAMPROC_OK)
  {
    vStreamProc_SetFlushedOfNodeInfo(nodeId, TRUE);
  }

  return retVal;
}

/**********************************************************************************************************************
 *  vStreamProc_Pipe_ConcludeEdgeFlush()
 *********************************************************************************************************************/
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
VSTREAMPROC_LOCAL_INLINE FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_Pipe_ConcludeEdgeFlush(
  vStreamProc_PipeIterType PipeId,
  P2VAR(vStreamProc_FlushLevelIterType, AUTOMATIC, VSTREAMPROC_APPL_DATA) FlushLevelIdx,
  P2VAR(vStreamProc_EdgeIterType, AUTOMATIC, VSTREAMPROC_APPL_DATA) EdgeIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  vStreamProc_ReturnType          retVal        = VSTREAMPROC_PENDING;
  vStreamProc_FlushLevelIterType  flushLevelIdx = *FlushLevelIdx;
  vStreamProc_EdgeIterType        edgeIdx       = *EdgeIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Mark current edge as flushed and decrement pending edges in active flush level. */
  vStreamProc_SetFlushedOfEdgeInfo(edgeIdx, TRUE);
  vStreamProc_DecPendingCountOfFlushLevelInfo(flushLevelIdx);

  /* #20 If all edges/nodes of the active level where flushed
   *   Continue with the next level. */
  if (vStreamProc_GetPendingCountOfFlushLevelInfo(flushLevelIdx) == 0u)
  {
    flushLevelIdx++;

    /* #30 If there are still further flush level
     *   Start the next one. */
    if (flushLevelIdx < vStreamProc_GetFlushLevelEndIdxOfPipe(PipeId))
    {
      vStreamProc_Pipe_StartFlushLevel(PipeId, flushLevelIdx);

      edgeIdx = vStreamProc_GetEdgeIdxOfFlushLevelInfo(flushLevelIdx);
    }
    /* #40 Otherwise, all edges/nodes are flushed. */
    else
    {
      vStreamProc_SetFlushLevelIdxOfPipeInfo(PipeId, flushLevelIdx);

      retVal = VSTREAMPROC_OK;
    }
  }

  *FlushLevelIdx  = flushLevelIdx;
  *EdgeIdx        = edgeIdx;

  return retVal;
}

/**********************************************************************************************************************
 *  vStreamProc_Pipe_FinishFlush()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
VSTREAMPROC_LOCAL_INLINE FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_Pipe_FinishFlush(
  vStreamProc_PipeIterType PipeId)
{
  /* ----- Local Variables ---------------------------------------------- */
  vStreamProc_ReturnType    retVal = VSTREAMPROC_OK;
  vStreamProc_NodeIterType  nodeIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 For all storage nodes associated with the passed pipe */
  for (nodeIdx = vStreamProc_GetNodeStartIdxOfPipe(PipeId); nodeIdx < vStreamProc_GetNodeEndIdxOfPipe(PipeId); nodeIdx++)
  {
    vStreamProc_One2OneIndirectionWorkspaceIdxOfNodeType storageNodeIdx = vStreamProc_GetOne2OneIndirectionWorkspaceIdxOfNode(nodeIdx);

    if (vStreamProc_GetTypeOfNode(nodeIdx) == VSTREAMPROC_STORAGE_NODE_TYPEOFNODE)
    {
      vStreamProc_StorageOutputPortIterType outputPortIdx;

      /* #20 For all output ports of the storage node with internal scope */
      for ( outputPortIdx = vStreamProc_GetStorageOutputPortStartIdxOfStorageNode(storageNodeIdx);
            outputPortIdx < vStreamProc_GetStorageOutputPortEndIdxOfStorageNode(storageNodeIdx);
            outputPortIdx++ )
      {
        if (vStreamProc_GetPortScopeOfStorageOutputPort(outputPortIdx) == VSTREAMPROC_INTERNAL_PORTSCOPEOFSTORAGEOUTPUTPORT)
        {
          /* #30 Check that all data was completely consumed. */
          if (vStreamProc_GetIsEmptyOfStorageNodeDef(vStreamProc_GetStorageNodeDefIdxOfStorageNode(storageNodeIdx))(
            (vStreamProc_StorageNodeIdType)storageNodeIdx, (vStreamProc_OutputPortIdType)outputPortIdx) != TRUE)
          {
            retVal = VSTREAMPROC_FAILED;

            break;
          }
        }
      }
    }
  }

  return retVal;
} /* PRQA S 6080 */ /* MD_MSR_STMIF */

/**********************************************************************************************************************
 *  vStreamProc_Pipe_ConcludeFlushCycle()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VSTREAMPROC_LOCAL_INLINE FUNC(void, VSTREAMPROC_CODE) vStreamProc_Pipe_ConcludeFlushCycle(
  vStreamProc_FlushLevelIterType FlushLevelIdx,
  P2VAR(vStreamProc_EdgeIterType, AUTOMATIC, VSTREAMPROC_APPL_DATA) EdgeIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  vStreamProc_EdgeIterType edgeIdx = *EdgeIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Search next edge in current level which wasn't flushed yet. */
  do
  {
    edgeIdx++;

    if (edgeIdx >= vStreamProc_GetEdgeEndIdxOfFlushLevel(FlushLevelIdx))
    {
      edgeIdx = vStreamProc_GetEdgeStartIdxOfFlushLevel(FlushLevelIdx);
    }
  } while (vStreamProc_IsFlushedOfEdgeInfo(edgeIdx));

  vStreamProc_SetEdgeIdxOfFlushLevelInfo(FlushLevelIdx, edgeIdx);

  *EdgeIdx = edgeIdx;
}

/**********************************************************************************************************************
 *  vStreamProc_Pipe_PerformFlush()
 *********************************************************************************************************************/
/*!
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
 */
VSTREAMPROC_LOCAL_INLINE FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_Pipe_PerformFlush(
  vStreamProc_PipeIterType PipeId)
{
  vStreamProc_ReturnType          retVal        = VSTREAMPROC_PENDING;
  vStreamProc_FlushLevelIterType  flushLevelIdx = vStreamProc_GetFlushLevelIdxOfPipeInfo(PipeId);
  vStreamProc_EdgeIterType        edgeIdx       = vStreamProc_GetEdgeIdxOfFlushLevelInfo(flushLevelIdx);
  vStreamProc_MaxNumberOfNodesToProcessOfSchedulerType pendingFlushCalls =
    vStreamProc_GetMaxNumberOfNodesToProcessOfScheduler(PipeId);

  /* #10 While not all edges/nodes are flushed */
  while (retVal != VSTREAMPROC_OK)
  {
    /* #20 Flush the active edge/node of the current flush level. */
    vStreamProc_ReturnType flushRetVal = VSTREAMPROC_OK;

    if (vStreamProc_Pipe_IsFlushOfEdgeRequired(edgeIdx) == TRUE)
    {
      flushRetVal = vStreamProc_Pipe_FlushEdge(PipeId, edgeIdx);

      /* #30 If an actual flush operation was executed, reduce the number of calls for this cycle. */
      pendingFlushCalls--;
    }

    /* #40 If flush of edge/node finished */
    if (flushRetVal == VSTREAMPROC_OK)
    {
      /* #50 Mark edge as flushed and potentially switch to next flush level or finish flush. */
      if (vStreamProc_Pipe_ConcludeEdgeFlush(PipeId, &flushLevelIdx, &edgeIdx) == VSTREAMPROC_OK)
      {
        retVal = VSTREAMPROC_OK;
      }
    }
    /* #60 Report other result instead. */
    else
    {
      /* Only overwrite lower prior return values. */
      if (retVal < flushRetVal)
      {
        retVal = flushRetVal;
      }
    }

    /* #70 If pipe is completely flushed now
     *  Check that all data at internal edges was completely consumed. */
    if (retVal == VSTREAMPROC_OK)
    {
      retVal = vStreamProc_Pipe_FinishFlush(PipeId);
    }
    /* #80 Otherwise, search next edge in current level which wasn't flushed yet. */
    else
    {
      vStreamProc_Pipe_ConcludeFlushCycle(flushLevelIdx, &edgeIdx);
    }

    /* #90 End current flush cycle if maximum number of configured nodes were processed or operation failed. */
    if ( (pendingFlushCalls == 0u)
      || (retVal == VSTREAMPROC_FAILED) )
    {
      break;
    }
  }

  return retVal;
}

/**********************************************************************************************************************
 * vStreamProc_Pipe_ApplyMode()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
VSTREAMPROC_LOCAL_INLINE FUNC(void, VSTREAMPROC_CODE) vStreamProc_Pipe_ApplyMode(
  vStreamProc_PipeIterType PipeId,
  vStreamProc_ModeIterType PipeModeId)
{
  if ( vStreamProc_HasBaseState()
    && vStreamProc_HasBaseStateInfo()
    && vStreamProc_HasMode()
    && vStreamProc_HasMode2BaseState() )
  {
    vStreamProc_BaseStateIterType baseStateIdx;

    /* #10 Backup current values of all base states. */
    for ( baseStateIdx = vStreamProc_GetBaseStateStartIdxOfPipe(PipeId);
          baseStateIdx < vStreamProc_GetBaseStateEndIdxOfPipe(PipeId);
          baseStateIdx++ )
    {
      vStreamProc_SetPreviousActivationOfBaseStateInfo(baseStateIdx, vStreamProc_IsActiveOfBaseStateInfo(baseStateIdx)); /* PRQA S 4404 2 */ /* MD_MSR_AutosarBoolean */

      /* #20 If no configured mode is requested
       *   Set all base states to their default values. */
      if (PipeModeId == VSTREAMPROC_NO_MODE)
      {
        vStreamProc_SetActiveOfBaseStateInfo(baseStateIdx, vStreamProc_IsDefaultActivationOfBaseState(baseStateIdx));   /* PRQA S 4404 2 */ /* MD_MSR_AutosarBoolean */
      }
    }

    /* #30 If an actual mode is requested
     *   Modify base states values as configured for given mode. */
    if (PipeModeId != VSTREAMPROC_NO_MODE)
    {
      vStreamProc_Mode2BaseStateIterType mode2BaseStateIdx;

      for ( mode2BaseStateIdx = vStreamProc_GetMode2BaseStateStartIdxOfMode(PipeModeId);
            mode2BaseStateIdx < vStreamProc_GetMode2BaseStateEndIdxOfMode(PipeModeId);
            mode2BaseStateIdx++ )
      {
        baseStateIdx = vStreamProc_GetBaseStateIdxOfMode2BaseState(mode2BaseStateIdx);

        vStreamProc_SetActiveOfBaseStateInfo(baseStateIdx, vStreamProc_IsBaseStateActivationOfMode2BaseState(mode2BaseStateIdx)); /* PRQA S 4404 2 */ /* MD_MSR_AutosarBoolean */
      }
    }
  }
}

/**********************************************************************************************************************
 * vStreamProc_Pipe_RevertModeApplication()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VSTREAMPROC_LOCAL_INLINE FUNC(void, VSTREAMPROC_CODE) vStreamProc_Pipe_RevertModeApplication(
  vStreamProc_PipeIterType PipeId)
{
  if (vStreamProc_HasBaseStateInfo())
  {
    vStreamProc_BaseStateIterType baseStateIdx;

    /* #10 Restore values of all base states from previously created backup. */
    for ( baseStateIdx = vStreamProc_GetBaseStateStartIdxOfPipe(PipeId);
          baseStateIdx < vStreamProc_GetBaseStateEndIdxOfPipe(PipeId);
          baseStateIdx++ )
    {
      vStreamProc_SetActiveOfBaseStateInfo(baseStateIdx, vStreamProc_IsPreviousActivationOfBaseStateInfo(baseStateIdx)); /* PRQA S 4404 2 */ /* MD_MSR_AutosarBoolean */
    }
  }
}

/**********************************************************************************************************************
 * vStreamProc_Pipe_EvaluateMetaStates()
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
 *
 */
VSTREAMPROC_LOCAL FUNC(void, VSTREAMPROC_CODE) vStreamProc_Pipe_EvaluateMetaStates(
  vStreamProc_PipeIterType PipeId)
{
  if ( vStreamProc_HasBaseStateInfo()
    && vStreamProc_HasMetaState()
    && vStreamProc_HasMetaStateInfo()
    && vStreamProc_HasMetaState2BaseState()
    && vStreamProc_HasMetaStateTruthTable() )
  {
    vStreamProc_MetaStateIterType metaStateIdx;

    /* #10 Iterate all meta states of the pipe */
    for ( metaStateIdx = vStreamProc_GetMetaStateStartIdxOfPipe(PipeId);
          metaStateIdx < vStreamProc_GetMetaStateEndIdxOfPipe(PipeId);
          metaStateIdx++ )
    {
      vStreamProc_MetaStateTruthTableIterType truthTableRow;
      vStreamProc_MetaStateTruthTableIterType truthTableRowStartIdx = vStreamProc_GetMetaStateTruthTableStartIdxOfMetaState(metaStateIdx);
      boolean                                 truthTableMatch       = FALSE;
      boolean                                 stateActivation       = FALSE;

      /* #20 Iterate all rows of the truth table of the meta state */
      for ( truthTableRow = 0u;
            truthTableRow < vStreamProc_GetTruthTableCountOfMetaState(metaStateIdx);
            truthTableRow++ )
      {
        vStreamProc_MetaState2BaseStateIterType metaState2BaseStateIdx;
        vStreamProc_MetaStateTruthTableIterType truthTableIdx = truthTableRowStartIdx;

        truthTableMatch = TRUE;

        /* #30 Compare current activation of all base states referenced by meta state against expected values. */
        for ( metaState2BaseStateIdx = vStreamProc_GetMetaState2BaseStateStartIdxOfMetaState(metaStateIdx);
              metaState2BaseStateIdx < vStreamProc_GetMetaState2BaseStateEndIdxOfMetaState(metaStateIdx);
              metaState2BaseStateIdx++ )
        {
          vStreamProc_BaseStateIterType baseStateIdx = vStreamProc_GetBaseStateIdxOfMetaState2BaseState(metaState2BaseStateIdx);

          if ( vStreamProc_IsExpectedStateActivationOfMetaStateTruthTable(truthTableIdx)
            != vStreamProc_IsActiveOfBaseStateInfo(baseStateIdx) )
          {
            truthTableMatch = FALSE;

            break;
          }

          truthTableIdx++;
        }

        /* #40 End search if matching base state combination was found in truth table. */
        if (truthTableMatch == TRUE)
        {
          break;
        }

        truthTableRowStartIdx += vStreamProc_GetMetaState2BaseStateLengthOfMetaState(metaStateIdx);
      }

      /* #50 Activate meta state depending on result of truth table evaluation:
       *   + Normal truth table: Match was found.
       *   + Inverse truth table: No match was found. */
      if (truthTableMatch == vStreamProc_IsMatchActivationOfMetaState(metaStateIdx))                                    /* PRQA S 1881 */ /* MD_MSR_AutosarBoolean */
      {
        stateActivation = TRUE;
      }

      vStreamProc_SetActiveOfMetaStateInfo(metaStateIdx, stateActivation);
    }
  }
} /* PRQA S 6080 */ /* MD_MSR_STMIF */

/**********************************************************************************************************************
 * vStreamProc_Pipe_SwitchPortActivations()
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
 *
 *
 *
 *
 *
 */
VSTREAMPROC_LOCAL FUNC(Std_ReturnType, VSTREAMPROC_CODE) vStreamProc_Pipe_SwitchPortActivations(
  vStreamProc_PipeIterType PipeId)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType            retVal = E_OK;                                                                              /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vStreamProc_EdgeIterType  edgeIdx;

  /* #10 Iterate all edges of the pipe */
  for ( edgeIdx = vStreamProc_GetEdgeStartIdxOfPipe(PipeId);
        edgeIdx < vStreamProc_GetEdgeEndIdxOfPipe(PipeId);
        edgeIdx++ )
  {
    vStreamProc_OutputPortIdType outputPortIdx = vStreamProc_GetStorageOutputPortIdxOfEdge(edgeIdx);

    /* #20 If an output port (of a storage node) is referenced by the edge,
     *   it is either a consumer edge (from storage node output to processing node input)
     *   or an edge from storage node output to an exit point.
     *   Otherwise, it is an edge from an entry point to a storage node and is always active. */
    if (outputPortIdx != VSTREAMPROC_NO_STORAGEOUTPUTPORTIDXOFEDGE)
    {
      vStreamProc_MetaStateIterType metaStateIdx      = vStreamProc_GetMetaStateIdxOfEdge(edgeIdx);
      boolean                       pendingActivation = FALSE;

      /* #30 Edge is either always active (because it has no meta state dependency)
       *   or when meta state referenced by edge is active. */
      if ( (metaStateIdx == VSTREAMPROC_NO_METASTATEIDXOFEDGE)
        || (vStreamProc_HasMetaStateInfo() && vStreamProc_IsActiveOfMetaStateInfo(metaStateIdx)) )
      {
        pendingActivation = TRUE;
      }

      /* #40 Set the new port activation if it has changed. */
      if (pendingActivation != vStreamProc_IsActiveInformationOfStorageOutputPortInfo(outputPortIdx))                   /* PRQA S 1881 */ /* MD_MSR_AutosarBoolean */
      {
        Std_ReturnType                  currentActionRetVal;
        vStreamProc_StorageNodeIdType   storageNodeIdx = vStreamProc_GetStorageNodeIdxOfStorageOutputPort(outputPortIdx);

        currentActionRetVal = vStreamProc_GetSetActivationSignalOfStorageNodeDef(
          vStreamProc_GetStorageNodeDefIdxOfStorageNode(storageNodeIdx))(storageNodeIdx, outputPortIdx, pendingActivation);

        if (currentActionRetVal == E_OK)
        {
          vStreamProc_ProcNode_StorageOutputPortsInputPortDynIterType inputPortIdx =
            vStreamProc_GetProcNode_StorageOutputPortsInputPortDynIdxOfEdge(edgeIdx);

          /* #50 If an input port is referenced by the edge (as it is a consumer edge)
           *   Set the (potentially updated) input connection. */
          if ( (pendingActivation == TRUE)
            && (inputPortIdx != VSTREAMPROC_NO_PROCNODE_STORAGEOUTPUTPORTSINPUTPORTDYNIDXOFEDGE) )
          {
            vStreamProc_SetProcNode_StorageOutputPortsInputPortDyn(inputPortIdx, outputPortIdx);
          }
        }
        else
        {
          /* #60 If one signal can not be changed stop changing others. */
          retVal = E_NOT_OK;

          break;
        }
      }
    }
  }

  return retVal;
} /* PRQA S 6080 */ /* MD_MSR_STMIF */

/**********************************************************************************************************************
 * vStreamProc_Pipe_HandleMetaStateSwitching()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
VSTREAMPROC_LOCAL FUNC(Std_ReturnType, VSTREAMPROC_CODE) vStreamProc_Pipe_HandleMetaStateSwitching(
  vStreamProc_PipeIterType PipeId,
  vStreamProc_ModeIterType PipeModeId)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;

  /* #10 Apply given mode, switching the affected base state values. */
  vStreamProc_Pipe_ApplyMode(PipeId, PipeModeId);
  /* #20 Evaluate active meta states for new base state values. */
  vStreamProc_Pipe_EvaluateMetaStates(PipeId);

  /* #30 Switch port activations based on active meta states. */
  retVal = vStreamProc_Pipe_SwitchPortActivations(PipeId);

  return retVal;
}

/**********************************************************************************************************************
 * vStreamProc_Pipe_RevertMetaStateSwitching()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
VSTREAMPROC_LOCAL_INLINE FUNC(void, VSTREAMPROC_CODE) vStreamProc_Pipe_RevertMetaStateSwitching(
  vStreamProc_PipeIterType PipeId)
{
  /* #10 Revert to the previous base state values before the last mode application. */
  vStreamProc_Pipe_RevertModeApplication(PipeId);
  /* #20 Evaluate active meta states for base state values. */
  vStreamProc_Pipe_EvaluateMetaStates(PipeId);

  /* #30 Switch port activations based on active meta states. */
  (void)vStreamProc_Pipe_SwitchPortActivations(PipeId);
}

/**********************************************************************************************************************
 *  vStreamProc_Pipe_PrepareStorageInfo()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VSTREAMPROC_LOCAL FUNC(void, VSTREAMPROC_CODE) vStreamProc_Pipe_PrepareStorageInfo(
  P2VAR(vStreamProc_StorageInfoType, AUTOMATIC, VSTREAMPROC_APPL_VAR) StorageInfo)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Initialize storage info structure with default values. */
  StorageInfo->DataTypeInfo.Id    = vStreamProcConf_vStreamProcDataType_Undefined;
  StorageInfo->DataTypeInfo.Size  = 0u;
  StorageInfo->AvailableLength    = 0u;
  StorageInfo->RequestLength      = 0u;
  StorageInfo->ReleaseFlag        = TRUE;
} /* vStreamProc_Pipe_PrepareStorageInfo */

/**********************************************************************************************************************
 *  vStreamProc_Pipe_InitAccessPointIteratorParam()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VSTREAMPROC_LOCAL_INLINE FUNC(vStreamProc_AccessPointIteratorParamType, VSTREAMPROC_CODE) vStreamProc_Pipe_InitAccessPointIteratorParam(
  vStreamProc_PipeIdType PipeId,
  vStreamProc_AccessPointOperationType Operation,
  boolean AbortOnError)
{
  vStreamProc_AccessPointIteratorParamType iteratorParam;

  /* #10 Assign passed parameters to structure members and return by value. */
  iteratorParam.PipeId        = PipeId;
  iteratorParam.Operation     = Operation;
  iteratorParam.AbortOnError  = AbortOnError;

  return iteratorParam;
}

#if (VSTREAMPROC_DEV_ERROR_DETECT == STD_ON)
/**********************************************************************************************************************
 *  vStreamProc_Pipe_CheckEntryPointInfo()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VSTREAMPROC_LOCAL FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_Pipe_CheckEntryPointInfo(
  vStreamProc_PipeIdType PipeId,
  vStreamProc_EntryPointInfoPtrType EntryPointInfo) /* PRQA S 3673 */ /* MD_vStreamProc_Rule8.13_3673_NonConstPtrParam */
{
  /* ----- Local Variables ---------------------------------------------- */
  vStreamProc_ReturnType retVal = VSTREAMPROC_FAILED;                                                                   /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check plausibility of all input parameters */
  /* Verify that the passed entry point ID is valid. */
  if (EntryPointInfo->EntryPointId >= vStreamProc_GetEntryPointLengthOfPipe(PipeId))
  {
  }
  /* Verify that the passed data type ID is valid. */
  else if (EntryPointInfo->WriteRequest.StorageInfo.DataTypeInfo.Id >= vStreamProcConf_vStreamProcDataTypeCount)
  {
  }
  else
  {
    retVal = VSTREAMPROC_OK;
  }

  return retVal;
} /* vStreamProc_Pipe_CheckEntryPointInfo */

/**********************************************************************************************************************
 *  vStreamProc_Pipe_CheckExitPointInfo()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VSTREAMPROC_LOCAL FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_Pipe_CheckExitPointInfo(
  vStreamProc_PipeIdType PipeId,
  vStreamProc_ExitPointInfoPtrType ExitPointInfo) /* PRQA S 3673 */ /* MD_vStreamProc_Rule8.13_3673_NonConstPtrParam */
{
  /* ----- Local Variables ---------------------------------------------- */
  vStreamProc_ReturnType retVal = VSTREAMPROC_FAILED;                                                                   /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check plausibility of all input parameters */
  /* Verify that the passed exit point ID is valid. */
  if (ExitPointInfo->ExitPointId >= vStreamProc_GetExitPointLengthOfPipe(PipeId))
  {
  }
  /* Verify that the passed data type ID is valid. */
  else if (ExitPointInfo->ReadRequest.StorageInfo.DataTypeInfo.Id >= vStreamProcConf_vStreamProcDataTypeCount)
  {
  }
  else
  {
    retVal = VSTREAMPROC_OK;
  }

  return retVal;
} /* vStreamProc_Pipe_CheckExitPointInfo */
#endif

/**********************************************************************************************************************
 *  vStreamProc_Pipe_ReleaseEntryPoint()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
VSTREAMPROC_LOCAL FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_Pipe_ReleaseEntryPoint(
  vStreamProc_PipeIdType PipeId,
  vStreamProc_EntryPointInfoPtrType EntryPointInfo) /* PRQA S 3673 */ /* MD_vStreamProc_Rule8.13_3673_NonConstPtrParam */
{
  /* ----- Local Variables ---------------------------------------------- */
  vStreamProc_ReturnType retVal = VSTREAMPROC_FAILED;                                                                   /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Ensure that pipe is in the processing phase. */
  if (vStreamProc_GetPhaseOfPipeInfo(PipeId) == VSTREAMPROC_PROCESS_PHASEOFPIPEINFO)
  {
    vStreamProc_StorageNodeIdType storageNodeId =
      vStreamProc_GetStorageNodeIdxOfEntryPoint(vStreamProc_GetEntryPointStartIdxOfPipe(PipeId) + EntryPointInfo->EntryPointId);

    /* #20 Issue acknowledge request with zero length to storage node connected to entry point. */
    retVal = vStreamProc_CallWriteAckOfStorageNode(storageNodeId, 0u);
  }

  return retVal;
} /* vStreamProc_Pipe_ReleaseEntryPoint */

/**********************************************************************************************************************
 *  vStreamProc_Pipe_ReleaseExitPoint()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VSTREAMPROC_LOCAL FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_Pipe_ReleaseExitPoint(
  vStreamProc_PipeIdType PipeId,
  vStreamProc_ExitPointInfoPtrType ExitPointInfo) /* PRQA S 3673 */ /* MD_vStreamProc_Rule8.13_3673_NonConstPtrParam */
{
  /* ----- Local Variables ---------------------------------------------- */
  vStreamProc_ReturnType retVal = VSTREAMPROC_FAILED;                                                                   /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vStreamProc_OutputPortIdType  storageOutputPortId   =
    vStreamProc_GetStorageOutputPortIdxOfExitPoint(vStreamProc_GetExitPointStartIdxOfPipe(PipeId) + ExitPointInfo->ExitPointId);
  vStreamProc_StorageNodeIdType storageNodeId         = vStreamProc_GetStorageNodeIdxOfStorageOutputPort(storageOutputPortId);

  /* ----- Implementation ----------------------------------------------- */
  /* Hint: Exit points can also be evaluated when pipe is flushed or failed. */
  /* #10 Issue acknowledge request with zero length to storage node connected to exit point. */
  retVal = vStreamProc_CallReadAckOfStorageNode(storageNodeId, 0u, storageOutputPortId);

  return retVal;
} /* vStreamProc_Pipe_ReleaseExitPoint */

/**********************************************************************************************************************
 *  vStreamProc_Pipe_IterateAccessPointInfos()
 *********************************************************************************************************************/
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
VSTREAMPROC_LOCAL FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_Pipe_IterateAccessPointInfos(
  vStreamProc_AccessPointIteratorParamType IteratorParam,
  vStreamProc_EntryPointInfoPtrType EntryPointInfos,
  vStreamProc_EntryPointIdType EntryPointCount,
  vStreamProc_ExitPointInfoPtrType ExitPointInfos,
  vStreamProc_ExitPointIdType ExitPointCount)
{
  /* ----- Local Constants ---------------------------------------------- */
  /*! Lookup table for access point operation functions. */
  CONST(vStreamProc_AccessPointOperationConfigType, AUTOMATIC) vStreamProc_AccessPointOperationConfig[VSTREAMPROC_ACCESS_POINT_OPERATION_COUNT] =
  {
#if (VSTREAMPROC_DEV_ERROR_DETECT == STD_ON)
    { vStreamProc_Pipe_CheckEntryPointInfo,       vStreamProc_Pipe_CheckExitPointInfo },
#endif
    { vStreamProc_Pipe_PrepareEntryPointInfo,   vStreamProc_Pipe_PrepareExitPointInfo },
    { vStreamProc_Pipe_GetEntryPointInfo,       vStreamProc_Pipe_GetExitPointInfo },
    { vStreamProc_Pipe_RequestEntryPointData,   vStreamProc_Pipe_RequestExitPointData },
    { vStreamProc_Pipe_AcknowledgeEntryPoint,   vStreamProc_Pipe_AcknowledgeExitPoint },
    { vStreamProc_Pipe_ReleaseEntryPoint,       vStreamProc_Pipe_ReleaseExitPoint }
  };

  /* ----- Local Variables ---------------------------------------------- */
  vStreamProc_ReturnType          retVal = VSTREAMPROC_OK;                                                              /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vStreamProc_ReturnType          opRetVal;
  vStreamProc_EntryPointIterType  entryPointIndex;
  vStreamProc_ExitPointIterType   exitPointIndex;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 For all entry point infos */
  for (entryPointIndex = 0u; entryPointIndex < EntryPointCount; entryPointIndex++)
  {
    /* #20 Execute entry point operation. */
    opRetVal = vStreamProc_AccessPointOperationConfig[IteratorParam.Operation].EntryPointOperation(IteratorParam.PipeId, &EntryPointInfos[entryPointIndex]);

    /* Results with higher severity overwrite existing value. */
    if (opRetVal > retVal)
    {
      retVal = opRetVal;

      /* #30 Abort further processing if requested. */
      if (IteratorParam.AbortOnError == TRUE)
      {
        break;
      }
    }
  }

  if ( (retVal == VSTREAMPROC_OK) || (IteratorParam.AbortOnError == FALSE) )
  {
    /* #40 For all exit point infos */
    for (exitPointIndex = 0u; exitPointIndex < ExitPointCount; exitPointIndex++)
    {
      /* #50 Execute exit point operation. */
      opRetVal = vStreamProc_AccessPointOperationConfig[IteratorParam.Operation].ExitPointOperation(IteratorParam.PipeId, &ExitPointInfos[exitPointIndex]);

      /* Results with higher severity overwrite existing value. */
      if (opRetVal > retVal)
      {
        retVal = opRetVal;

        /* #60 Abort further processing if requested. */
        if (IteratorParam.AbortOnError == TRUE)
        {
          break;
        }
      }
    }
  }

  return retVal;
}

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  vStreamProc_Pipe_Init
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
 *
 */
FUNC(Std_ReturnType, VSTREAMPROC_CODE) vStreamProc_Pipe_Init(
  CONST(vStreamProc_PipeIterType, AUTOMATIC) PipeId)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Initialize the pipe's scheduler. 1:1 relation between pipe and scheduler. */
  retVal = vStreamProc_Scheduler_Init((vStreamProc_SchedulerIterType)PipeId);

  if (retVal == E_OK)
  {
    vStreamProc_NodeIterType nodeIdx;

    /* #20 Pipe is closed after initialization. */
    vStreamProc_SetPipeState(PipeId, VSTREAMPROC_CLOSED_PIPESTATE);
    vStreamProc_SetPhaseOfPipeInfo(PipeId, VSTREAMPROC_PROCESS_PHASEOFPIPEINFO);

    /* #30 Loop all nodes associated with the passed pipe */
    for (nodeIdx = vStreamProc_GetNodeStartIdxOfPipe(PipeId); nodeIdx < vStreamProc_GetNodeEndIdxOfPipe(PipeId); nodeIdx++)
    {
      vStreamProc_One2OneIndirectionWorkspaceIdxOfNodeType specificNodeIdx = vStreamProc_GetOne2OneIndirectionWorkspaceIdxOfNode(nodeIdx);

      /* #40 Trigger the init function of the node. */
      if (vStreamProc_GetTypeOfNode(nodeIdx) == VSTREAMPROC_PROCESSING_NODE_TYPEOFNODE)
      {
        retVal = vStreamProc_Pipe_InitProcessingNode((vStreamProc_ProcessingNodeIdType)specificNodeIdx);
      }
      else /* VSTREAMPROC_STORAGE_NODE_TYPEOFNODE */
      {
        retVal = vStreamProc_GetInitFctOfStorageNodeDef(vStreamProc_GetStorageNodeDefIdxOfStorageNode(specificNodeIdx))((vStreamProc_StorageNodeIdType)specificNodeIdx);
      }

      /* #50 Reset flag for flushing of node. */
      vStreamProc_SetFlushedOfNodeInfo(nodeIdx, FALSE);

      /* Break loop if one init function from a node failed. */
      if (retVal != E_OK)
      {
        break;
      }
    }
  }

  if (retVal == E_OK)
  {
    vStreamProc_EdgeIterType edgeIdx;

    /* #60 Reset all flags for flushing of edges. */
    for ( edgeIdx = vStreamProc_GetEdgeStartIdxOfPipe(PipeId);
          edgeIdx < vStreamProc_GetEdgeEndIdxOfPipe(PipeId);
          edgeIdx++ )
    {
      vStreamProc_SetFlushedOfEdgeInfo(edgeIdx, FALSE);
    }

    /* #70 Set port activations to default configuration. */
    retVal = vStreamProc_Pipe_HandleMetaStateSwitching(PipeId, VSTREAMPROC_NO_MODE);
  }

  return retVal;
}

/***********************************************************************************************************************
*  vStreamProc_Pipe_Open
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, VSTREAMPROC_CODE) vStreamProc_Pipe_Open(
  CONST(vStreamProc_PipeIterType, AUTOMATIC) PipeId)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;                                                                                     /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Open the pipe. */
  vStreamProc_SetPipeState(PipeId, VSTREAMPROC_OPENED_PIPESTATE);
  retVal = E_OK;

  return retVal;
}

/***********************************************************************************************************************
*  vStreamProc_Pipe_Close
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, VSTREAMPROC_CODE) vStreamProc_Pipe_Close(
  CONST(vStreamProc_PipeIterType, AUTOMATIC) PipeId)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Close the pipe. */
  vStreamProc_SetPipeState(PipeId, VSTREAMPROC_CLOSED_PIPESTATE);
  retVal = E_OK;

  return retVal;
}

 /***********************************************************************************************************************
  *  vStreamProc_Pipe_Process
  **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_Pipe_Process(
  CONST(vStreamProc_PipeIterType, AUTOMATIC) PipeId)
{
  /* ----- Local Variables ---------------------------------------------- */
  vStreamProc_ReturnType retVal = VSTREAMPROC_FAILED;                                                                   /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Ensure that pipe is in the processing phase. */
  if (vStreamProc_GetPhaseOfPipeInfo(PipeId) == VSTREAMPROC_PROCESS_PHASEOFPIPEINFO)
  {
    /* #20 Start the scheduler. 1:1 relation between pipe and scheduler. */
    retVal = vStreamProc_Scheduler_Process((vStreamProc_SchedulerIterType)PipeId);

    /* #30 Change pipe to "failed" state if operation didn't succeed. */
    if (retVal == VSTREAMPROC_FAILED)
    {
      vStreamProc_SetPhaseOfPipeInfo(PipeId, VSTREAMPROC_FAILED_PHASEOFPIPEINFO);
    }
  }

  return retVal;
}

/***********************************************************************************************************************
 *  vStreamProc_Pipe_Flush
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
 *
 */
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_Pipe_Flush(
  CONST(vStreamProc_PipeIterType, AUTOMATIC) PipeId)
{
  /* ----- Local Variables ---------------------------------------------- */
  vStreamProc_ReturnType          retVal = VSTREAMPROC_FAILED;                                                          /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Prepare flushing of pipe and check preconditions. */
  retVal = vStreamProc_Pipe_PrepareFlush(PipeId);

  /* #20 Perform actual flushing of pipe. */
  if (retVal == VSTREAMPROC_PENDING)
  {
    retVal = vStreamProc_Pipe_PerformFlush(PipeId);
  }

  if (retVal != VSTREAMPROC_FAILED)
  {
    /* #30 Call default scheduling to handle remaining nodes. 1:1 relation between pipe and scheduler. */
    vStreamProc_ReturnType processRetVal = vStreamProc_Scheduler_Process((vStreamProc_SchedulerIterType)PipeId);

    /* #40 Processing result overwrites current flush result under certain conditions. */
    /* Only overwrite lower prior return values. */
    if (retVal < processRetVal)
    {
      retVal = processRetVal;
    }
  }

  /* #50 Change pipe to "failed" state if operation didn't succeed.
   *  Insufficient input at an entry point must be treated as unsuccessful as well.
   */
  if ( (retVal == VSTREAMPROC_FAILED)
    || (retVal == VSTREAMPROC_INSUFFICIENT_INPUT) )
  {
    vStreamProc_SetPhaseOfPipeInfo(PipeId, VSTREAMPROC_FAILED_PHASEOFPIPEINFO);
  }

  return retVal;
}

/***********************************************************************************************************************
 *  vStreamProc_Pipe_SetMode
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VSTREAMPROC_CODE) vStreamProc_Pipe_SetMode(
  CONST(vStreamProc_PipeIterType, AUTOMATIC) PipeId,
  CONST(vStreamProc_ModeIterType, AUTOMATIC) PipeModeId)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;                                                                                     /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Ensure that pipe is in the processing phase. */
  if (vStreamProc_GetPhaseOfPipeInfo(PipeId) == VSTREAMPROC_PROCESS_PHASEOFPIPEINFO)
  {
    /* #20 Ensure that given mode belongs to this pipe. */
    if ( (PipeModeId == VSTREAMPROC_NO_MODE)
      || (vStreamProc_GetPipeIdxOfMode(PipeModeId) == PipeId) )
    {
      /* #30 Set the mode for the pipe. */
      retVal = vStreamProc_Pipe_HandleMetaStateSwitching(PipeId, PipeModeId);

      /* #40 Revert application of mode in case of failure. */
      if (retVal != E_OK)
      {
        vStreamProc_Pipe_RevertMetaStateSwitching(PipeId);
      }
    }
  }

  return retVal;
}

/***********************************************************************************************************************
 *  vStreamProc_Pipe_AnnounceStream
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, VSTREAMPROC_CODE) vStreamProc_Pipe_AnnounceStream(
  CONST(vStreamProc_PipeIterType, AUTOMATIC) PipeId,
  CONST(vStreamProc_EntryPointIterType, AUTOMATIC) EntryPointId,
  CONST(vStreamProc_LengthType, AUTOMATIC) Length,
  VAR(vStreamProc_ProduceCallbackType, AUTOMATIC) ProduceCbk)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;                                                                                     /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Ensure that pipe is in the processing phase. */
  if (vStreamProc_GetPhaseOfPipeInfo(PipeId) == VSTREAMPROC_PROCESS_PHASEOFPIPEINFO)
  {
    vStreamProc_StorageNodeIdxOfEntryPointType storageNodeId
      = vStreamProc_GetStorageNodeIdxOfEntryPoint(vStreamProc_GetEntryPointStartIdxOfPipe(PipeId) + EntryPointId);

    /* #20 Issue announce stream request to storage node connected to entry point. */
    vStreamProc_GetAnnounceStreamOfStorageNodeDef(vStreamProc_GetStorageNodeDefIdxOfStorageNode(storageNodeId))(
      storageNodeId, Length, ProduceCbk);

    retVal = E_OK;
  }

  return retVal;
}

/**********************************************************************************************************************
 *  vStreamProc_Pipe_PrepareEntryPointInfo()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_Pipe_PrepareEntryPointInfo(
  vStreamProc_PipeIdType PipeId,
  vStreamProc_EntryPointInfoPtrType EntryPointInfo)
{
  /* ----- Local Variables ---------------------------------------------- */
  vStreamProc_ReturnType retVal = VSTREAMPROC_OK;                                                                       /* PRQA S 2981 */ /* MD_MSR_RetVal */
  P2VAR(vStreamProc_WriteRequestType, AUTOMATIC, VSTREAMPROC_APPL_VAR) writeRequest =
    &EntryPointInfo->WriteRequest;

  VSTREAMPROC_DUMMY_STATEMENT(PipeId);                                                                                  /* PRQA S 2983,3112 */ /* MD_MSR_DummyStmt */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Initialize write request with default values. */
  writeRequest->Buffer = NULL_PTR;
  vStreamProc_Pipe_PrepareStorageInfo(&writeRequest->StorageInfo);

  return retVal;
} /* vStreamProc_Pipe_PrepareEntryPointInfo */

/**********************************************************************************************************************
 *  vStreamProc_Pipe_GetEntryPointInfo()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_Pipe_GetEntryPointInfo(
  vStreamProc_PipeIdType PipeId,
  vStreamProc_EntryPointInfoPtrType EntryPointInfo)
{
  /* ----- Local Variables ---------------------------------------------- */
  vStreamProc_ReturnType retVal = VSTREAMPROC_FAILED;                                                                   /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Ensure that pipe is in the processing phase. */
  if (vStreamProc_GetPhaseOfPipeInfo(PipeId) == VSTREAMPROC_PROCESS_PHASEOFPIPEINFO)
  {
    vStreamProc_StorageNodeIdType   storageNodeId       =
      vStreamProc_GetStorageNodeIdxOfEntryPoint(vStreamProc_GetEntryPointStartIdxOfPipe(PipeId) + EntryPointInfo->EntryPointId);
    vStreamProc_StorageInfoPtrType  storageInfo         = &EntryPointInfo->WriteRequest.StorageInfo;
    vStreamProc_DataTypeIdType      expectedDataTypeId  = storageInfo->DataTypeInfo.Id;

    /* #20 Issue info request to storage node connected to entry point. */
    retVal = vStreamProc_CallWriteInfoOfStorageNode(storageNodeId, storageInfo);

    /* #30 Check against expected data type, skip if "undefined" type is given. */
    if ( (retVal != VSTREAMPROC_FAILED)
      && (storageInfo->DataTypeInfo.Id != expectedDataTypeId) )
    {
      if (expectedDataTypeId != (vStreamProc_DataTypeIdType)vStreamProcConf_vStreamProcDataType_Undefined)
      {
        retVal = VSTREAMPROC_FAILED;
      }
    }
  }

  return retVal;
} /* vStreamProc_Pipe_GetEntryPointInfo */

/**********************************************************************************************************************
 *  vStreamProc_Pipe_RequestEntryPointData()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_Pipe_RequestEntryPointData(
  vStreamProc_PipeIdType PipeId,
  vStreamProc_EntryPointInfoPtrType EntryPointInfo)
{
  /* ----- Local Variables ---------------------------------------------- */
  vStreamProc_ReturnType retVal = VSTREAMPROC_FAILED;                                                                   /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Ensure that pipe is in the processing phase. */
  if (vStreamProc_GetPhaseOfPipeInfo(PipeId) == VSTREAMPROC_PROCESS_PHASEOFPIPEINFO)
  {
    vStreamProc_StorageNodeIdType         storageNodeId       =
      vStreamProc_GetStorageNodeIdxOfEntryPoint(vStreamProc_GetEntryPointStartIdxOfPipe(PipeId) + EntryPointInfo->EntryPointId);
    vStreamProc_StorageInfoConstPtrType   storageInfo         = &EntryPointInfo->WriteRequest.StorageInfo;
    vStreamProc_DataTypeIdType            expectedDataTypeId  = storageInfo->DataTypeInfo.Id;

    /* #20 Issue write request to storage node connected to entry point. */
    retVal = vStreamProc_CallWriteRequestOfStorageNode(storageNodeId, &EntryPointInfo->WriteRequest);

    /* #30 Check against expected data type. */
    if ( (retVal != VSTREAMPROC_FAILED)
      && (storageInfo->DataTypeInfo.Id != expectedDataTypeId) )
    {
      retVal = VSTREAMPROC_FAILED;
      /* #40 Release storage lock in case of mismatch. */
      (void)vStreamProc_Pipe_ReleaseEntryPoint(PipeId, EntryPointInfo);
    }
  }

  return retVal;
} /* vStreamProc_Pipe_RequestEntryPointData */

/**********************************************************************************************************************
 *  vStreamProc_Pipe_AcknowledgeEntryPoint()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_Pipe_AcknowledgeEntryPoint(
  vStreamProc_PipeIdType PipeId,
  vStreamProc_EntryPointInfoPtrType EntryPointInfo)
{
  /* ----- Local Variables ---------------------------------------------- */
  vStreamProc_ReturnType retVal = VSTREAMPROC_FAILED;                                                                   /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Ensure that pipe is in the processing phase. */
  if (vStreamProc_GetPhaseOfPipeInfo(PipeId) == VSTREAMPROC_PROCESS_PHASEOFPIPEINFO)
  {
    vStreamProc_StorageNodeIdType   storageNodeId =
      vStreamProc_GetStorageNodeIdxOfEntryPoint(vStreamProc_GetEntryPointStartIdxOfPipe(PipeId) + EntryPointInfo->EntryPointId);
    vStreamProc_StorageInfoPtrType  storageInfo   = &EntryPointInfo->WriteRequest.StorageInfo;

    /* #20 Issue acknowledge request to storage node connected to entry point. */
    retVal = vStreamProc_CallWriteAckOfStorageNode(storageNodeId, storageInfo->RequestLength);

    /* #30 Evaluate storage release flag. */
    if (storageInfo->ReleaseFlag == TRUE)
    {
      /* #40 Clear buffer and available length when release is requested. */
      EntryPointInfo->WriteRequest.Buffer = NULL_PTR;
      storageInfo->AvailableLength        = 0u;
    }
    /* #50 Otherwise: Issue re-request (with zero length). */
    else
    {
      storageInfo->RequestLength = 0u;

      retVal = vStreamProc_Pipe_RequestEntryPointData(PipeId, EntryPointInfo);
    }
  }

  return retVal;
} /* vStreamProc_Pipe_AcknowledgeEntryPoint */

/***********************************************************************************************************************
 *  vStreamProc_Pipe_RequestStream
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, VSTREAMPROC_CODE) vStreamProc_Pipe_RequestStream(
  CONST(vStreamProc_PipeIterType, AUTOMATIC) PipeId,
  CONST(vStreamProc_ExitPointIterType, AUTOMATIC) ExitPointId,
  CONST(vStreamProc_LengthType, AUTOMATIC) Length,
  VAR(vStreamProc_ConsumeCallbackType, AUTOMATIC) ConsumeCbk)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;                                                                                     /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Ensure that pipe is in the processing phase. */
  if (vStreamProc_GetPhaseOfPipeInfo(PipeId) == VSTREAMPROC_PROCESS_PHASEOFPIPEINFO)
  {
    vStreamProc_OutputPortIdType  storageOutputPortId =
      vStreamProc_GetStorageOutputPortIdxOfExitPoint(vStreamProc_GetExitPointStartIdxOfPipe(PipeId) + ExitPointId);
    vStreamProc_StorageNodeIdType storageNodeId       = vStreamProc_GetStorageNodeIdxOfStorageOutputPort(storageOutputPortId);

    /* #20 Issue stream request to storage node connected to exit point. */
    retVal = vStreamProc_GetRequestStreamOfStorageNodeDef(vStreamProc_GetStorageNodeDefIdxOfStorageNode(storageNodeId))(
      storageNodeId, Length, ConsumeCbk, storageOutputPortId);
  }

  return retVal;
}

/**********************************************************************************************************************
 *  vStreamProc_Pipe_PrepareExitPointInfo()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_Pipe_PrepareExitPointInfo(
  vStreamProc_PipeIdType PipeId,
  vStreamProc_ExitPointInfoPtrType ExitPointInfo)
{
  /* ----- Local Variables ---------------------------------------------- */
  vStreamProc_ReturnType retVal = VSTREAMPROC_OK;                                                                       /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* ----- Implementation ----------------------------------------------- */
  P2VAR(vStreamProc_ReadRequestType, AUTOMATIC, VSTREAMPROC_APPL_VAR) readRequest =
    &ExitPointInfo->ReadRequest;

  VSTREAMPROC_DUMMY_STATEMENT(PipeId);                                                                                  /* PRQA S 2983,3112 */ /* MD_MSR_DummyStmt */

  /* #10 Initialize read request with default values. */
  readRequest->Buffer = NULL_PTR;
  vStreamProc_Pipe_PrepareStorageInfo(&readRequest->StorageInfo);

  return retVal;
}

/**********************************************************************************************************************
 *  vStreamProc_Pipe_GetExitPointInfo()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_Pipe_GetExitPointInfo(
  vStreamProc_PipeIdType PipeId,
  vStreamProc_ExitPointInfoPtrType ExitPointInfo)
{
  /* ----- Local Variables ---------------------------------------------- */
  vStreamProc_ReturnType retVal = VSTREAMPROC_FAILED;                                                                   /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vStreamProc_OutputPortIdType    storageOutputPortId   =
    vStreamProc_GetStorageOutputPortIdxOfExitPoint(vStreamProc_GetExitPointStartIdxOfPipe(PipeId) + ExitPointInfo->ExitPointId);
  vStreamProc_StorageNodeIdType   storageNodeId         = vStreamProc_GetStorageNodeIdxOfStorageOutputPort(storageOutputPortId);
  vStreamProc_StorageInfoPtrType  storageInfo           = &ExitPointInfo->ReadRequest.StorageInfo;
  vStreamProc_DataTypeIdType      expectedDataTypeId    = storageInfo->DataTypeInfo.Id;

  /* ----- Implementation ----------------------------------------------- */
  /* Hint: Exit points can also be evaluated when pipe is flushed or failed. */
  /* #10 Issue info request to storage node connected to exit point. */
  retVal = vStreamProc_CallReadInfoOfStorageNode(storageNodeId, storageInfo, storageOutputPortId);

  /* #20 Check against expected data type, skip if "undefined" type is given. */
  if ( (retVal != VSTREAMPROC_FAILED)
    && (storageInfo->DataTypeInfo.Id != expectedDataTypeId) )
  {
    if (expectedDataTypeId != (vStreamProc_DataTypeIdType)vStreamProcConf_vStreamProcDataType_Undefined)
    {
      retVal = VSTREAMPROC_FAILED;
    }
  }

  return retVal;
}

/**********************************************************************************************************************
 *  vStreamProc_Pipe_RequestExitPointData()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_Pipe_RequestExitPointData(
  vStreamProc_PipeIdType PipeId,
  vStreamProc_ExitPointInfoPtrType ExitPointInfo)
{
  /* ----- Local Variables ---------------------------------------------- */
  vStreamProc_ReturnType retVal = VSTREAMPROC_FAILED;                                                                   /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vStreamProc_OutputPortIdType          storageOutputPortId   =
    vStreamProc_GetStorageOutputPortIdxOfExitPoint(vStreamProc_GetExitPointStartIdxOfPipe(PipeId) + ExitPointInfo->ExitPointId);
  vStreamProc_StorageNodeIdType         storageNodeId         = vStreamProc_GetStorageNodeIdxOfStorageOutputPort(storageOutputPortId);
  vStreamProc_StorageInfoConstPtrType   storageInfo           = &ExitPointInfo->ReadRequest.StorageInfo;
  vStreamProc_DataTypeIdType            expectedDataTypeId    = storageInfo->DataTypeInfo.Id;

  /* ----- Implementation ----------------------------------------------- */
  /* Hint: Exit points can also be evaluated when pipe is flushed or failed. */
  /* #10 Issue read request to storage node connected to exit point. */
  retVal = vStreamProc_CallReadRequestOfStorageNode(storageNodeId, &ExitPointInfo->ReadRequest, storageOutputPortId);

  /* #20 Check against expected data type */
  if ( (retVal != VSTREAMPROC_FAILED)
    && (storageInfo->DataTypeInfo.Id != expectedDataTypeId) )
  {
    retVal = VSTREAMPROC_FAILED;
    /* #30 Release storage lock in case of mismatch. */
    (void)vStreamProc_Pipe_ReleaseExitPoint(PipeId, ExitPointInfo);
  }

  return retVal;
}

/**********************************************************************************************************************
 *  vStreamProc_Pipe_AcknowledgeExitPoint()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_Pipe_AcknowledgeExitPoint(
  vStreamProc_PipeIdType PipeId,
  vStreamProc_ExitPointInfoPtrType ExitPointInfo)
{
  /* ----- Local Variables ---------------------------------------------- */
  vStreamProc_ReturnType retVal = VSTREAMPROC_FAILED;                                                                   /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vStreamProc_OutputPortIdType    storageOutputPortId   =
    vStreamProc_GetStorageOutputPortIdxOfExitPoint(vStreamProc_GetExitPointStartIdxOfPipe(PipeId) + ExitPointInfo->ExitPointId);
  vStreamProc_StorageNodeIdType   storageNodeId         = vStreamProc_GetStorageNodeIdxOfStorageOutputPort(storageOutputPortId);
  vStreamProc_StorageInfoPtrType  storageInfo           = &ExitPointInfo->ReadRequest.StorageInfo;

  /* ----- Implementation ----------------------------------------------- */
  /* Hint: Exit points can also be evaluated when pipe is flushed or failed. */
  /* #10 Issue acknowledge request to storage node connected to exit point. */
  retVal = vStreamProc_CallReadAckOfStorageNode(storageNodeId, storageInfo->RequestLength, storageOutputPortId);

  /* #20 Evaluate storage release flag. */
  if (storageInfo->ReleaseFlag == TRUE)
  {
    /* #30 Clear buffer and available length when release is requested. */
    ExitPointInfo->ReadRequest.Buffer = NULL_PTR;
    storageInfo->AvailableLength      = 0u;
  }
  /* #40 Otherwise: Issue re-request (with zero length). */
  else
  {
    storageInfo->RequestLength = 0u;

    retVal = vStreamProc_Pipe_RequestExitPointData(PipeId, ExitPointInfo);
  }

  return retVal;
}

/**********************************************************************************************************************
 *  vStreamProc_Pipe_PrepareAccessPointInfos()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_Pipe_PrepareAccessPointInfos(
  vStreamProc_PipeIdType PipeId,
  vStreamProc_EntryPointInfoPtrType EntryPointInfos,
  vStreamProc_EntryPointIdType EntryPointCount,
  vStreamProc_ExitPointInfoPtrType ExitPointInfos,
  vStreamProc_ExitPointIdType ExitPointCount)
{
  /* ----- Local Variables ---------------------------------------------- */
  vStreamProc_ReturnType retVal = VSTREAMPROC_FAILED;                                                                   /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all passed access point structures and apply prepare operation. */
  retVal = vStreamProc_Pipe_IterateAccessPointInfos(
    vStreamProc_Pipe_InitAccessPointIteratorParam(PipeId, VSTREAMPROC_ACCESS_POINT_OPERATION_PREPARE_INFO, FALSE),
    EntryPointInfos, EntryPointCount, ExitPointInfos, ExitPointCount);

  return retVal;
}

/**********************************************************************************************************************
 *  vStreamProc_Pipe_PrepareAllAccessPointInfos()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_Pipe_PrepareAllAccessPointInfos(
  vStreamProc_PipeIdType PipeId,
  vStreamProc_EntryPointInfoPtrType EntryPointInfos,
  vStreamProc_EntryPointIdType EntryPointCount,
  vStreamProc_ExitPointInfoPtrType ExitPointInfos,
  vStreamProc_ExitPointIdType ExitPointCount)
{
  /* ----- Local Variables ---------------------------------------------- */
  vStreamProc_ReturnType          retVal = VSTREAMPROC_FAILED;                                                          /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vStreamProc_EntryPointIterType  entryPointIndex;
  vStreamProc_ExitPointIterType   exitPointIndex;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Initialize IDs of passed access point structures to be equal to the zero-based index. */
  for (entryPointIndex = 0u; entryPointIndex < EntryPointCount; entryPointIndex++)
  {
    EntryPointInfos[entryPointIndex].EntryPointId = (vStreamProc_EntryPointIdType)entryPointIndex;
  }

  for (exitPointIndex = 0u; exitPointIndex < ExitPointCount; exitPointIndex++)
  {
    ExitPointInfos[exitPointIndex].ExitPointId = (vStreamProc_ExitPointIdType)exitPointIndex;
  }

  /* #20 Iterate over all passed access point infos and apply prepare operation. */
  retVal = vStreamProc_Pipe_IterateAccessPointInfos(
    vStreamProc_Pipe_InitAccessPointIteratorParam(PipeId, VSTREAMPROC_ACCESS_POINT_OPERATION_PREPARE_INFO, FALSE),
    EntryPointInfos, EntryPointCount, ExitPointInfos, ExitPointCount);

  return retVal;
}

/**********************************************************************************************************************
 *  vStreamProc_Pipe_GetAccessPointInfos()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_Pipe_GetAccessPointInfos(
  vStreamProc_PipeIdType PipeId,
  vStreamProc_EntryPointInfoPtrType EntryPointInfos,
  vStreamProc_EntryPointIdType EntryPointCount,
  vStreamProc_ExitPointInfoPtrType ExitPointInfos,
  vStreamProc_ExitPointIdType ExitPointCount)
{
  /* ----- Local Variables ---------------------------------------------- */
  vStreamProc_ReturnType retVal = VSTREAMPROC_FAILED;                                                                   /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all passed access point infos and apply getter operation. */
  retVal = vStreamProc_Pipe_IterateAccessPointInfos(
    vStreamProc_Pipe_InitAccessPointIteratorParam(PipeId, VSTREAMPROC_ACCESS_POINT_OPERATION_GET_INFO, FALSE),
    EntryPointInfos, EntryPointCount, ExitPointInfos, ExitPointCount);

  return retVal;
}

/**********************************************************************************************************************
 *  vStreamProc_Pipe_RequestAccessPointData()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_Pipe_RequestAccessPointData(
  vStreamProc_PipeIdType PipeId,
  vStreamProc_EntryPointInfoPtrType EntryPointInfos,
  vStreamProc_EntryPointIdType EntryPointCount,
  vStreamProc_ExitPointInfoPtrType ExitPointInfos,
  vStreamProc_ExitPointIdType ExitPointCount)
{
  /* ----- Local Variables ---------------------------------------------- */
  vStreamProc_ReturnType retVal = VSTREAMPROC_FAILED;                                                                   /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all passed access point infos and apply request operation. */
  retVal = vStreamProc_Pipe_IterateAccessPointInfos(
    vStreamProc_Pipe_InitAccessPointIteratorParam(PipeId, VSTREAMPROC_ACCESS_POINT_OPERATION_REQUEST_DATA, FALSE),
    EntryPointInfos, EntryPointCount, ExitPointInfos, ExitPointCount);

  /* #20 If operation failed, iterate over all passed access point infos and apply release operation. */
  if (retVal != VSTREAMPROC_OK)
  {
    (void)vStreamProc_Pipe_IterateAccessPointInfos(
      vStreamProc_Pipe_InitAccessPointIteratorParam(PipeId, VSTREAMPROC_ACCESS_POINT_OPERATION_RELEASE, FALSE),
      EntryPointInfos, EntryPointCount, ExitPointInfos, ExitPointCount);
  }

  return retVal;
}

/**********************************************************************************************************************
 *  vStreamProc_Pipe_AcknowledgeAccessPoints()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_Pipe_AcknowledgeAccessPoints(
  vStreamProc_PipeIdType PipeId,
  vStreamProc_EntryPointInfoPtrType EntryPointInfos,
  vStreamProc_ExitPointIdType EntryPointCount,
  vStreamProc_ExitPointInfoPtrType ExitPointInfos,
  vStreamProc_EntryPointIdType ExitPointCount)
{
  /* ----- Local Variables ---------------------------------------------- */
  vStreamProc_ReturnType retVal = VSTREAMPROC_FAILED;                                                                   /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all passed access point infos and apply acknowledge operation. */
  retVal = vStreamProc_Pipe_IterateAccessPointInfos(
    vStreamProc_Pipe_InitAccessPointIteratorParam(PipeId, VSTREAMPROC_ACCESS_POINT_OPERATION_ACKNOWLEDGE, FALSE),
    EntryPointInfos, EntryPointCount, ExitPointInfos, ExitPointCount);

  return retVal;
}

/**********************************************************************************************************************
 *  vStreamProc_Pipe_ReleaseAllAccessPoints()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_Pipe_ReleaseAllAccessPoints(
  vStreamProc_PipeIdType PipeId)
{
  /* ----- Local Variables ---------------------------------------------- */
  vStreamProc_ReturnType retVal = VSTREAMPROC_FAILED;                                                                   /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* ----- Implementation ----------------------------------------------- */
  vStreamProc_EntryPointInfoType  entryPointInfos[vStreamProcConf_MaxEntryPointCount];
  vStreamProc_ExitPointInfoType   exitPointInfos[vStreamProcConf_MaxExitPointCount];
  vStreamProc_EntryPointIdType    entryPointCount = vStreamProc_GetEntryPointLengthOfPipe(PipeId);
  vStreamProc_ExitPointIdType     exitPointCount  = vStreamProc_GetExitPointLengthOfPipe(PipeId);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Prepare all access point infos, e.g. initialize IDs.  */
  retVal = vStreamProc_Pipe_PrepareAllAccessPointInfos(PipeId, entryPointInfos, entryPointCount, exitPointInfos, exitPointCount);

  /* #20 Iterate over all access point infos and apply prepare operation. */
  if (retVal == VSTREAMPROC_OK)
  {
    retVal = vStreamProc_Pipe_IterateAccessPointInfos(
      vStreamProc_Pipe_InitAccessPointIteratorParam(PipeId, VSTREAMPROC_ACCESS_POINT_OPERATION_RELEASE, FALSE),
      entryPointInfos, entryPointCount, exitPointInfos, exitPointCount);
  }

  return retVal;
}

#if (VSTREAMPROC_DEV_ERROR_DETECT == STD_ON)
/**********************************************************************************************************************
 *  vStreamProc_Pipe_DetChecksAccessPointInfos()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(uint8, VSTREAMPROC_CODE) vStreamProc_Pipe_DetChecksAccessPointInfos(
  vStreamProc_PipeIdType PipeId,
  vStreamProc_EntryPointInfoPtrType EntryPointInfos,
  vStreamProc_EntryPointIdType EntryPointCount,
  vStreamProc_ExitPointInfoPtrType ExitPointInfos,
  vStreamProc_ExitPointIdType ExitPointCount,
  P2VAR(uint8, AUTOMATIC, VSTREAMPROC_APPL_DATA) ErrorId)
{
  uint8 errorID;

  /* #10 Check plausibility of all input parameters. */
  /* Iterate over all passed access point infos and apply check operation. */
  if (vStreamProc_Pipe_IterateAccessPointInfos(
    vStreamProc_Pipe_InitAccessPointIteratorParam(PipeId, VSTREAMPROC_ACCESS_POINT_OPERATION_CHECK_INFO, TRUE),
    EntryPointInfos, EntryPointCount, ExitPointInfos, ExitPointCount) != VSTREAMPROC_OK)
  {
    errorID = VSTREAMPROC_E_ID_PARAM;
  }
  else
  {
    /* Default to no error. */
    errorID = VSTREAMPROC_E_NO_ERROR;
  }

  *ErrorId = errorID;

  return errorID;
} /* PRQA S 6060 */ /* MD_MSR_STPAR */
#endif

#define VSTREAMPROC_STOP_SEC_CODE
#include "MemMap.h"                                                                                                     /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
*  END OF FILE: vStreamProc_Pipe.c
*********************************************************************************************************************/
