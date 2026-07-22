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
/*!        \file  vSwUpdM_ExctJob_If.h
 *        \brief  vSwUpdM_ExctJob unit interface header file
 *      \details  Interface provided by the vSwUpdM_ExctJob unit.
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

#if !defined (VSWUPDM_EXCTJOB_IF_H)
# define VSWUPDM_EXCTJOB_IF_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
/* ExctJob types header */
#include "vSwUpdM_ExctJob_Types.h"

/* Interface header of containing MultipleUnit */
#include "vSwUpdM_ExecCtrl_If.h"

/* Other MultipleUnits used by ExctJob_If (Prefer smallest set required, i.e. prefer _Types over _If) */

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
 *  vSwUpdM_Job_InitVolatileAttributes()
 *********************************************************************************************************************/
/*! \brief       Initialize volatile attributes of object of specific job type.
 *  \details     Job attributes are set to default values.
 *  \param[in]   JobType        Type of job to be initialized.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     job
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_Job_InitVolatileAttributes(
  vSwUpdM_JobTypeType JobType);

/**********************************************************************************************************************
 *  vSwUpdM_Job_Init()
 *********************************************************************************************************************/
/*! \brief       Initialize object of specific job type.
 *  \details     Set service ID, priority and suspendable attribute to given values.
 *               All other job attributes are set to default values.
 *  \param[in]   JobType        Type of job to be initialized.
 *  \param[in]   ServiceId      ID of service associated with this job. Passed to hook functions.
 *                              VSWUPDM_SID_NONE if no service is associated with job.
 *  \param[in]   Priority       Default priority of job. Higher values equal higher priority.
 *  \param[in]   Suspendable    TRUE when job can be suspended at any time. FALSE when job must be called with
 *                              a matching processing state (VSWUPDM_STATE_SUSPENDING) instead.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     job
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_Job_Init(
  vSwUpdM_JobTypeType JobType,
  vSwUpdM_ServiceIdType ServiceId,
  vSwUpdM_QueuePrioType Priority,
  boolean Suspendable);

/**********************************************************************************************************************
 *  vSwUpdM_Job_LinkParentJobResult()
 *********************************************************************************************************************/
/*! \brief       Link result of job to child result member of parent job.
 *  \details     Result of job is mirrored into child result member of parent job.
 *  \param[in]   Job              Pointer to job.
 *  \param[in]   ParentJob        Pointer to parent job.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     job
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_Job_LinkParentJobResult(
  vSwUpdM_JobPtrType Job,
  vSwUpdM_JobPtrType ParentJob);

/**********************************************************************************************************************
 *  vSwUpdM_Job_SetLinkedResult()
 *********************************************************************************************************************/
/*! \brief       Set linked result to given values and mark valid.
 *  \details     -
 *  \param[in,out]  Linked result   Pointer to linked result.
 *  \param[in]   Result             Result to be set.
 *  \param[in]   TargetAddress      Target address to be set.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     job
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_Job_SetLinkedResult(
  P2VAR(vSwUpdM_LinkedResultType, AUTOMATIC, VSWUPDM_APPL_VAR) LinkedResult,
  Std_ReturnType Result,
  vSwUpdM_AddressType TargetAddress);

/**********************************************************************************************************************
 *  vSwUpdM_Job_UpdateLinkedResult()
 *********************************************************************************************************************/
/*! \brief       Update the linked result variable.
 *  \details     Linked result is updated to match the current job result.
 *  \param[in]   Job              Pointer to job.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     job
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_Job_UpdateLinkedResult(
  vSwUpdM_JobPtrType Job);

/**********************************************************************************************************************
 *  vSwUpdM_Job_ResetChildResult()
 *********************************************************************************************************************/
/*! \brief       Reset child result of job to default values.
 *  \details     -
 *  \param[in,out]  Job               Pointer to job.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     job
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_Job_ResetChildResult(
  vSwUpdM_JobPtrType Job);

/**********************************************************************************************************************
 *  vSwUpdM_Job_ApplyChildResult()
 *********************************************************************************************************************/
/*! \brief       Apply the child result of the job.
 *  \details     The job result will be overwritten by the child result, in case it is valid.
 *  \param[in,out]   Job              Pointer to job.
 *  \param[in]   ApplyAddress         Overwrite job target address with child address when TRUE.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     job
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_Job_ApplyChildResult(
  vSwUpdM_JobPtrType Job,
  boolean ApplyAddress);

/**********************************************************************************************************************
 *  vSwUpdM_Job_EvaluateChildResult()
 *********************************************************************************************************************/
/*! \brief       Evaluate child result.
 *  \details     Form aggregated result, based on whether child is valid and/or expected.
 *  \param[in,out]   Job              Pointer to job.
 *  \return      Child result value                     Child result valid.
 *  \return      VSWUPDM_E_JOB_INVALID_CHILD_RESULT     Child result expected, but no valid result available.
 *  \return      E_OK                                   No child result expected and none available.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     job
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Job_EvaluateChildResult(
  vSwUpdM_JobPtrType Job);

/**********************************************************************************************************************
 * vSwUpdM_Job_EvaluateAndApplyChildResult
 *********************************************************************************************************************/
/*! \brief       Evaluate child result and apply it on job if necessary.
 *  \details     -
 *  \param[in,out] Job          Pointer to job.
 *  \param[in]   ApplyAddress   Apply address on child result.
 *  \return      Child result value                     Child result valid.
 *  \return      VSWUPDM_E_JOB_INVALID_CHILD_RESULT     Child result expected, but no valid result available.
 *  \return      E_OK                                   No child result expected and none available.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     job
 *********************************************************************************************************************/
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Job_EvaluateAndApplyChildResult(
  vSwUpdM_JobPtrType Job,
  boolean ApplyAddress);

/**********************************************************************************************************************
 * vSwUpdM_Job_EvaluateChildResultOrSuspend
 *********************************************************************************************************************/
/*! \brief       Evaluate child result, apply it on job and check if Suspend is requested.
 *  \details     Form aggregated result, based on whether child is valid and/or expected.
 *  \param[in]   ActiveState    Current Active State.
 *  \param[in,out] Job          Pointer to job.
 *  \param[in]   ApplyAddress   Apply address on child result.
 *  \return      VSWUPDM_JOB_STATUS_SUSPENDED Suspend is requested and child(s) are suspended.
 *  \return      VSWUPDM_JOB_STATUS_PENDING   Else.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     job
 *********************************************************************************************************************/
VSWUPDM_LOCAL FUNC(vSwUpdM_JobStatusType, VSWUPDM_CODE) vSwUpdM_Job_EvaluateChildResultOrSuspend(
  vSwUpdM_StateType ActiveState,
  vSwUpdM_JobPtrType Job,
  boolean ApplyAddress);

/**********************************************************************************************************************
 *  vSwUpdM_Job_PrepareWriteOperation()
 *********************************************************************************************************************/
/*! \brief       Updates the states of all entities affected by a write operation.
 *  \details     Optionally resume information is also updated.
 *  \param[in]   Job                  Pointer to job.
 *  \param[in]   Segment              Pointer to segment to be updated.
 *  \param[in]   UpdateEntityStates   Update states of affected module, region and segment when TRUE.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     job
 *********************************************************************************************************************/
VSWUPDM_LOCAL FUNC(void, VSWUPDM_CODE) vSwUpdM_Job_PrepareWriteOperation(
  vSwUpdM_JobPtrType Job,
  vSwUpdM_VarSegmentsPtrType Segment,
  boolean UpdateEntityStates);

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_<operation>()
 *********************************************************************************************************************/
/*! \defgroup    JobHandler           Common job handler API.
 *  \brief       Job handler for a specific task.
 *  \param[in]   ActiveState          VSWUPDM_STATE_ACTIVE              Normal job execution.
 *                                    VSWUPDM_STATE_SUSPENDING          Suspend of operation in progress.
 *                                    VSWUPDM_STATE_SHUT_DOWN_PENDING   Shutdown of operation in progress.
 *  \param[in,out] ActiveJob          Pointer to active job.
 *  \param[in]   ProcessingLength     Current processing length, dependent on used input buffer and segmentation.
 *  \return      VSWUPDM_JOB_STATUS_ACTIVE        Job operation active - re-execute in same main function cycle,
 *                                                unless higher priority job was spawned.
 *  \return      VSWUPDM_JOB_STATUS_PENDING       Job operation pending - re-execute on next main function cycle.
 *  \return      VSWUPDM_JOB_STATUS_FINISHED      Job operation finished - trigger confirmation if applicable and
 *                                                remove job from queue.
 *  \return      VSWUPDM_JOB_STATUS_SUSPENDED     Job operation suspended - trigger confirmation if applicable and
 *                                                move job to suspended queue.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     job
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_InitComponent()
 *********************************************************************************************************************/
/*! \ingroup     JobHandler
 *  \brief       Job handler for initialization of component.
 *  \details     -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *********************************************************************************************************************/
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_InitComponent);

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_InitPartitions()
 *********************************************************************************************************************/
/*! \ingroup     JobHandler
 *  \brief       Job handler for initialization of partition attributes.
 *  \details     -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *********************************************************************************************************************/
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_InitPartitions);

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_InitModules()
 *********************************************************************************************************************/
/*! \ingroup     JobHandler
 *  \brief       Job handler for initialization of module attributes.
 *  \details     -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *********************************************************************************************************************/
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_InitModules);

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_InitRegions()
 *********************************************************************************************************************/
/*! \ingroup     JobHandler
 *  \brief       Job handler for initialization of region attributes.
 *  \details     -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *********************************************************************************************************************/
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_InitRegions);

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_InitSegments()
 *********************************************************************************************************************/
/*! \ingroup     JobHandler
 *  \brief       Job handler for initialization of segment attributes.
 *  \details     -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *********************************************************************************************************************/
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_InitSegments);

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_FinalizeModuleUpdateLocal()
 *********************************************************************************************************************/
/*! \ingroup     JobHandler
 *  \brief       Job handler for closing a module.
 *  \details     -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *********************************************************************************************************************/
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_FinalizeModuleUpdateLocal);

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_OpenModuleLocal()
 *********************************************************************************************************************/
/*! \ingroup     JobHandler
 *  \brief       Job handler for opening a module.
 *  \details     -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *********************************************************************************************************************/
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_OpenModuleLocal);

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_CleanupModule()
 *********************************************************************************************************************/
/*! \ingroup     JobHandler
 *  \brief       Job handler for cleaning up a module in a dirty state.
 *  \details     -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *********************************************************************************************************************/
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_CleanupModule);

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_CloseModuleLocal()
 *********************************************************************************************************************/
/*! \ingroup     JobHandler
 *  \brief       Job handler for closing a module.
 *  \details     -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *********************************************************************************************************************/
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_CloseModuleLocal);

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_HandleUpdateState()
 *********************************************************************************************************************/
/*! \ingroup     JobHandler
 *  \brief       Job handler for evaluation and persisting of update state.
 *  \details     -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *********************************************************************************************************************/
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_HandleUpdateState);

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_HandleResumeInfo()
 *********************************************************************************************************************/
/*! \ingroup     JobHandler
 *  \brief       Job handler for evaluation and persisting of resume information.
 *  \details     -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *********************************************************************************************************************/
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_HandleResumeInfo);

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_PartitionValidityLocal()
 *********************************************************************************************************************/
/*! \ingroup     JobHandler
 *  \brief       Job handler for updating partition validity.
 *  \details     -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *********************************************************************************************************************/
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_PartitionValidityLocal);

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_CheckPartitionConsistency()
 *********************************************************************************************************************/
/*! \ingroup     JobHandler
 *  \brief       Job handler for checking the partition consistency.
 *  \details     -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *********************************************************************************************************************/
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_CheckPartitionConsistency);

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_PersistPartitionState()
 *********************************************************************************************************************/
/*! \ingroup     JobHandler
 *  \brief       Job handler for persisting of partition state.
 *  \details     -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *********************************************************************************************************************/
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_PersistPartitionState);

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_ModuleValidity()
 *********************************************************************************************************************/
/*! \ingroup     JobHandler
 *  \brief       Job handler for updating module validity.
 *  \details     -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *********************************************************************************************************************/
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_ModuleValidity);

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_PersistModuleState()
 *********************************************************************************************************************/
/*! \ingroup     JobHandler
 *  \brief       Job handler for persisting of module state.
 *  \details     -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *********************************************************************************************************************/
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_PersistModuleState);

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_PersistRegionState()
 *********************************************************************************************************************/
/*! \ingroup     JobHandler
 *  \brief       Job handler for persisting of region state.
 *  \details     -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *********************************************************************************************************************/
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_PersistRegionState);

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_PersistAllRegionStates()
 *********************************************************************************************************************/
/*! \ingroup     JobHandler
 *  \brief       Job handler for persisting of all pending region states.
 *  \details     -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *********************************************************************************************************************/
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_PersistAllRegionStates);

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_PersistSegmentState()
 *********************************************************************************************************************/
/*! \ingroup     JobHandler
 *  \brief       Job handler for persisting of segment state.
 *  \details     -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *********************************************************************************************************************/
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_PersistSegmentState);

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_PersistSegmentCount()
 *********************************************************************************************************************/
/*! \ingroup     JobHandler
 *  \brief       Job handler for persisting of segment count.
 *  \details     -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *********************************************************************************************************************/
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_PersistSegmentCount);

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_CloseSegment()
 *********************************************************************************************************************/
/*! \ingroup     JobHandler
 *  \brief       Job handler for opening and closing of segment.
 *  \details     -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *********************************************************************************************************************/
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_CloseSegment);

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_OpenSegment()
 *********************************************************************************************************************/
/*! \ingroup     JobHandler
 *  \brief       Job handler for opening and closing of segment.
 *  \details     -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *********************************************************************************************************************/
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_OpenSegment);

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_WaitForBookkeeperOperation()
 *********************************************************************************************************************/
/*! \ingroup     JobHandler
 *  \brief       Job handler for execution and waiting for bookkeeper operation.
 *  \details     -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *********************************************************************************************************************/
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_WaitForBookkeeperOperation);

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_EraseModuleLocal()
 *********************************************************************************************************************/
/*! \ingroup     JobHandler
 *  \brief       Job handler for erasing of module.
 *  \details     -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *********************************************************************************************************************/
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_EraseModuleLocal);

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_EraseRegion()
 *********************************************************************************************************************/
/*! \ingroup     JobHandler
 *  \brief       Job handler for erasing of region.
 *  \details     -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *********************************************************************************************************************/
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_EraseRegion);

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_EraseRange()
 *********************************************************************************************************************/
/*! \ingroup     JobHandler
 *  \brief       Job handler for erasing of memory range.
 *  \details     -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *********************************************************************************************************************/
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_EraseRange);

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_StartStream()
 *********************************************************************************************************************/
/*! \ingroup     JobHandler
 *  \brief       Job handler to initialize a download stream.
 *  \details     -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *********************************************************************************************************************/
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_StartStream);

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_ProcessStreamData()
 *********************************************************************************************************************/
/*! \ingroup     JobHandler
 *  \brief       Job handler for processing of download stream.
 *  \details     -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *********************************************************************************************************************/
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_ProcessStreamData);

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_EndStream()
 *********************************************************************************************************************/
/*! \ingroup     JobHandler
 *  \brief       Job handler to end stream download.
 *  \details     -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *********************************************************************************************************************/
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_EndStream);

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_FillMemory()
 *********************************************************************************************************************/
/*! \ingroup     JobHandler
 *  \brief       Job handler for filling of memory range.
 *  \details     -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *********************************************************************************************************************/
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_FillMemory);

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_ReadData()
 *********************************************************************************************************************/
/*! \ingroup     JobHandler
 *  \brief       Job handler for reading of memory range.
 *  \details     -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *********************************************************************************************************************/
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_ReadData);

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_WriteData()
 *********************************************************************************************************************/
/*! \ingroup     JobHandler
 *  \brief       Job handler for writing of memory range.
 *  \details     -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *********************************************************************************************************************/
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_WriteData);

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_ProcessStreamPipelined()
 *********************************************************************************************************************/
/*! \ingroup     JobHandler
 *  \brief       Job handler for pipelined data processing.
 *  \details     -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *********************************************************************************************************************/
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_ProcessStreamPipelined);

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_WaitForMemoryOperation()
 *********************************************************************************************************************/
/*! \ingroup     JobHandler
 *  \brief       Job handler to wait for pending memory operation.
 *  \details     -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *********************************************************************************************************************/
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_WaitForMemoryOperation);

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_FinalizeModuleLocal()
 *********************************************************************************************************************/
/*! \ingroup     JobHandler
 *  \brief       Job handler for finalization of module.
 *  \details     -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *********************************************************************************************************************/
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_FinalizeModuleLocal);

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_ProcessModuleLocal()
 *********************************************************************************************************************/
/*! \ingroup     JobHandler
 *  \brief       Job handler for processing of module.
 *  \details     Also used for verification of module.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *********************************************************************************************************************/
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_ProcessModuleLocal);

/**********************************************************************************************************************
 *  vSwUpdM_SubJobHandler_ProcessEntityRemoteInput()
 *********************************************************************************************************************/
/*! \ingroup     JobHandler
 *  \brief       Sub-job handler for handling remote inputs during processing of an entity.
 *  \details     Used by vSwUpdM_JobHandler_ProcessEntity.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *********************************************************************************************************************/
VSWUPDM_SUB_JOB_HANDLER(vSwUpdM_SubJobHandler_ProcessEntityRemoteInput);

/**********************************************************************************************************************
 *  vSwUpdM_SubJobHandler_ProcessEntityRemoteOutput()
 *********************************************************************************************************************/
/*! \ingroup     JobHandler
 *  \brief       Sub-job handler for handling remote outputs during processing of an entity.
 *  \details     Used by vSwUpdM_JobHandler_ProcessEntity.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *********************************************************************************************************************/
VSWUPDM_SUB_JOB_HANDLER(vSwUpdM_SubJobHandler_ProcessEntityRemoteOutput);

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_ProcessEntity()
 *********************************************************************************************************************/
/*! \ingroup     JobHandler
 *  \brief       Job handler for processing data of an entity.
 *  \details     -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *********************************************************************************************************************/
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_ProcessEntity);

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_RemoteProcessInfo()
 *********************************************************************************************************************/
/*! \ingroup     JobHandler
 *  \brief       JobHandler to provide a ProcessInfo to a remote node.
 *  \details     -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *********************************************************************************************************************/
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_RemoteProcessInfo);

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_RemoteStreamScheduler()
 *********************************************************************************************************************/
/*! \ingroup     JobHandler
 *  \brief       Job handler to schedule RemoteStreams
 *  \details     -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *********************************************************************************************************************/
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_RemoteStreamScheduler);

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_FinalizeSegment()
 *********************************************************************************************************************/
/*! \ingroup     JobHandler
 *  \brief       Job handler for finalization of segment.
 *  \details     -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *********************************************************************************************************************/
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_FinalizeSegment);

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_FinalizeSegmentUpdateLocalState()
 *********************************************************************************************************************/
/*! \ingroup     JobHandler
 *  \brief       Job handler to update entity states after segment finalization.
 *  \details     -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *********************************************************************************************************************/
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_FinalizeSegmentUpdateLocalState);

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_RemoteStreamCleanup()
 *********************************************************************************************************************/
/*! \ingroup     JobHandler
 *  \brief       JobHandler to set RemoteStream state from DONE to IDLE
 *  \details     -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *********************************************************************************************************************/
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_RemoteStreamCleanup);

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_SyncPartitionLocal()
 *********************************************************************************************************************/
/*! \ingroup     JobHandler
 *  \brief       Job handler for syncing of partition.
 *  \details     -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *********************************************************************************************************************/
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_SyncPartitionLocal);

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_SyncModule()
 *********************************************************************************************************************/
/*! \ingroup     JobHandler
 *  \brief       Job handler for syncing of module.
 *  \details     -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *********************************************************************************************************************/
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_SyncModule);

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_CompareModule()
 *********************************************************************************************************************/
/*! \ingroup     JobHandler
 *  \brief       Job handler for comparing the contents of a synced module.
 *  \details     -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *********************************************************************************************************************/
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_CompareModule);

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_ValidateModuleUpdateLocalState()
 *********************************************************************************************************************/
/*! \ingroup     JobHandler
 *  \brief       Job handler for set module to valid state
 *  \details     -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *********************************************************************************************************************/
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_ValidateModuleUpdateLocalState);

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_InvalidateModuleUpdateLocalState()
 *********************************************************************************************************************/
/*! \ingroup     JobHandler
 *  \brief       Job handler for set module to invalid state
 *  \details     -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *********************************************************************************************************************/
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_InvalidateModuleUpdateLocalState);

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_FinalizeSyncPartition()
 *********************************************************************************************************************/
/*! \ingroup     JobHandler
 *  \brief       Job handler to finalize SyncPartition.
 *  \details     -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *********************************************************************************************************************/
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_FinalizeSyncPartition);

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_SwapPartitionCheck()
 *********************************************************************************************************************/
/*! \ingroup     JobHandler
 *  \brief       Job handler for swapping of active partition.
 *  \details     -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *********************************************************************************************************************/
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_SwapPartitionCheck);

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_SwapPartitionWork()
 *********************************************************************************************************************/
/*! \ingroup     JobHandler
 *  \brief       Job handler for swapping of active partition.
 *  \details     -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *********************************************************************************************************************/
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_SwapPartitionWork);

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_TriggerConfirmation()
 *********************************************************************************************************************/
/*! \ingroup     JobHandler
 *  \brief       Job handler to trigger confirmation.
 *  \details     -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *********************************************************************************************************************/
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_TriggerConfirmation);

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_Suspend()
 *********************************************************************************************************************/
/*! \ingroup     JobHandler
 *  \brief       Job handler for suspending of current operation.
 *  \details     -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *********************************************************************************************************************/
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_Suspend);

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_Resume()
 *********************************************************************************************************************/
/*! \ingroup     JobHandler
 *  \brief       Job handler to resume previously suspended operation.
 *  \details     -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *********************************************************************************************************************/
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_Resume);

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_Start()
 *********************************************************************************************************************/
/*! \ingroup     JobHandler
 *  \brief       Job handler to start download sequence.
 *  \details     -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *********************************************************************************************************************/
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_Start);

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_Shutdown()
 *********************************************************************************************************************/
/*! \ingroup     JobHandler
 *  \brief       Job handler for shutting down component.
 *  \details     -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *********************************************************************************************************************/
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_Shutdown);

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_RemoteLock()
 *********************************************************************************************************************/
/*! \ingroup     JobHandler
 *  \brief       Job handler to request for lock master/slave role.
 *  \details     -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *********************************************************************************************************************/
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_RemoteLock);

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_RemoteGroupConfirmation()
 *********************************************************************************************************************/
/*! \ingroup     JobHandler
 *  \brief       Job handler to process received responses of a group of slaves.
 *  \details     -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *********************************************************************************************************************/
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_RemoteGroupConfirmation);

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_RemoteTargetConfirmation()
 *********************************************************************************************************************/
/*! \ingroup     JobHandler
 *  \brief       Job handler to process received response of a single slave.
 *  \details     -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *********************************************************************************************************************/
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_RemoteTargetConfirmation);

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_RemoteProcessStreamData()
 *********************************************************************************************************************/
/*! \ingroup      JobHandler
 *  \brief        JobHandler to transmit StreamData to slave nodes.
 *  \details     -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *********************************************************************************************************************/
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_RemoteProcessStreamData);

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_ServiceDispatcher()
 *********************************************************************************************************************/
/*! \ingroup     JobHandler
 *  \brief       Job handler to dispatch the local/remote services
 *  \details     -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *********************************************************************************************************************/
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_ServiceDispatcher);

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_EraseRegionLocalWork()
 *********************************************************************************************************************/
/*! \ingroup     JobHandler
 *  \brief       Job handler to erase a region of the local node
 *  \details     -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *********************************************************************************************************************/
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_EraseRegionLocalWork);

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_RemoteAddSegments()
 *********************************************************************************************************************/
/*! \ingroup     JobHandler
 *  \brief       Job handler to transmit AddSegment requests to remote nodes
 *  \details     -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *********************************************************************************************************************/
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_RemoteAddSegments);

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_ClearSegmentsOfModule()
 *********************************************************************************************************************/
/*! \ingroup     JobHandler
 *  \brief       Job handler to clear the segments of a given module
 *  \details     -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *********************************************************************************************************************/
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_ClearSegmentsOfModule);

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_WaitForHookOperation()
 *********************************************************************************************************************/
/*! \ingroup     JobHandler
 *  \brief       Job handler for execution and waiting for hook function.
 *  \details     -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *********************************************************************************************************************/
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_WaitForHookOperation);

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_IndicateWriteToModule()
 *********************************************************************************************************************/
/*! \ingroup     JobHandler
 *  \brief       Job handler for handling indication that data will be written to the module by third-party component.
 *  \details     -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *********************************************************************************************************************/
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_IndicateWriteToModule);

# define VSWUPDM_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* VSWUPDM_EXCTJOB_IF_H */

/**********************************************************************************************************************
 *  END OF FILE: vSwUpdM_ExctJob_If.h
 *********************************************************************************************************************/
