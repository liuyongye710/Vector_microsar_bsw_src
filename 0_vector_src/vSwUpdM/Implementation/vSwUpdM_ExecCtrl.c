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
/*!        \file  vSwUpdM_ExecCtrl.c
 *        \brief  vSwUpdM_ExecCtrl source file
 *      \details  Implementation of the vSwUpdM_ExecCtrl subcomponent.
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

#define VSWUPDM_EXECCTRL_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
/* ExecCtrl implementation header */
#include "vSwUpdM_ExecCtrl_Impl.h"

/* Implementation headers of all contained Units */
#include "vSwUpdM_ExctJob_Impl.h"
#include "vSwUpdM_ExctSchedule_Impl.h"

/* Other MultipleUnits used by ExecCtrl (Prefer smallest set required, i.e. prefer _Types over _If over _Impl) */
#include "vSwUpdM_Grid_Impl.h"
#include "vSwUpdM_Services_Impl.h"
#include "vSwUpdM_BkPersistServer_Impl.h"

/*!
 * Internal comment removed.
 *
 *
 */
#include "vSwUpdM_Range.h"
#include "vStreamProc.h"
#if (VSWUPDM_MULTICONTROLLER_SUPPORT == STD_ON)
# include "vRpcProxy_vSwUpdM.h"
# include "vRpcProxy_Service.h"
#include "vSwUpdM_GridRpc_Impl.h"
#endif

#include "vSwUpdM_Lcfg.h"

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/
#define VSWUPDM_EXECCTRL_SEQUENCEFLAG_NONE          0u
#define VSWUPDM_EXECCTRL_SEQUENCEFLAG_MULTINODE     1u
#define VSWUPDM_EXECCTRL_SEQUENCEFLAG_SPAWNJOB      2u
#define VSWUPDM_EXECCTRL_SEQUENCEFLAG_CALLFUNCTION  4u

#define VSWUPDM_EXECCTRL_SEQ_NO_FUNCTION ((vSwUpdM_ExecCtrl_SequneceExecFnType)0)

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *********************************************************************************************************************/
#define VSWUPDM_EXECCTRL_MIN(a, b) (((a) < (b)) ? (a) : (b))

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

typedef Std_ReturnType (*vSwUpdM_ExecCtrl_SequneceExecFnType)(vSwUpdM_JobPtrType ParentJob);

typedef struct
{
  vSwUpdM_JobTypeType Job;
  vSwUpdM_ExecCtrl_SequneceExecFnType Fn;
  uint8 Flags;
}vSwUpdM_ExecCtrl_SequenceEntryType;

typedef P2CONST(vSwUpdM_ExecCtrl_SequenceEntryType, AUTOMATIC, VSWUPDM_APPL_DATA) vSwUpdM_ExecCtrl_SequenceEntryConstPtrType;

typedef struct
{
  vSwUpdM_ExecCtrl_SequenceEntryConstPtrType Sequence;
  CONST(uint32_least, VSWUPDM_APPL_DATA) SequenceSize;
}vSwUpdM_ExecCtrl_SequencesListType;

typedef CONST(vSwUpdM_ExecCtrl_SequencesListType, VSWUPDM_APPL_DATA) vSwUpdM_ExecCtrl_SequencesListConstType;

/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/
#define VSWUPDM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* PRQA S 3218 1 */ /* MD_vSwUpdM_Rule8.9_3218_FileScope */
VSWUPDM_LOCAL CONST(vSwUpdM_JobHandlerType, VSWUPDM_CONST) vSwUpdM_JobHandlers[VSWUPDM_JOB_TYPE_COUNT] =
{
  vSwUpdM_JobHandler_InitComponent,
  vSwUpdM_JobHandler_InitPartitions,
  vSwUpdM_JobHandler_InitModules,
  vSwUpdM_JobHandler_InitRegions,
  vSwUpdM_JobHandler_InitSegments,
  vSwUpdM_JobHandler_FinalizeSyncPartition,
  vSwUpdM_JobHandler_SwapPartitionCheck,
  vSwUpdM_JobHandler_SwapPartitionWork,
  vSwUpdM_JobHandler_FinalizeModuleUpdateLocal,
  vSwUpdM_JobHandler_OpenModuleLocal,
  vSwUpdM_JobHandler_CleanupModule,
  vSwUpdM_JobHandler_CloseModuleLocal,
  vSwUpdM_JobHandler_HandleUpdateState,
  vSwUpdM_JobHandler_HandleResumeInfo,
  vSwUpdM_JobHandler_PersistPartitionState,
  vSwUpdM_JobHandler_PartitionValidityLocal,        /* InvalidatePartition */
  vSwUpdM_JobHandler_PartitionValidityLocal,        /* ValidatePartition */
  vSwUpdM_JobHandler_CheckPartitionConsistency,
  vSwUpdM_JobHandler_PersistModuleState,
  vSwUpdM_JobHandler_ModuleValidity,                /* InvalidateModule */
  vSwUpdM_JobHandler_ModuleValidity,                /* ValidateModule */
  vSwUpdM_JobHandler_PersistRegionState,
  vSwUpdM_JobHandler_PersistAllRegionStates,
  vSwUpdM_JobHandler_PersistSegmentState,
  vSwUpdM_JobHandler_PersistSegmentCount,
  vSwUpdM_JobHandler_OpenSegment,
  vSwUpdM_JobHandler_CloseSegment,
  vSwUpdM_JobHandler_WaitForBookkeeperOperation,
  vSwUpdM_JobHandler_EraseModuleLocal,
  vSwUpdM_JobHandler_EraseRegion,
  vSwUpdM_JobHandler_EraseRange,
  vSwUpdM_JobHandler_StartStream,
  vSwUpdM_JobHandler_ProcessStreamData,
  vSwUpdM_JobHandler_EndStream,
  vSwUpdM_JobHandler_FillMemory,
  vSwUpdM_JobHandler_ReadData,
  vSwUpdM_JobHandler_WriteData,
  vSwUpdM_JobHandler_ProcessStreamPipelined,
  vSwUpdM_JobHandler_WaitForMemoryOperation,
  vSwUpdM_JobHandler_FinalizeModuleLocal,
  vSwUpdM_JobHandler_ProcessModuleLocal,             /* VerifyModule */
  vSwUpdM_JobHandler_ProcessModuleLocal,             /* ProcessModule */
  vSwUpdM_JobHandler_FinalizeSegment,
  vSwUpdM_JobHandler_FinalizeSegmentUpdateLocalState,
  vSwUpdM_JobHandler_SyncPartitionLocal,
  vSwUpdM_JobHandler_SyncModule,
  vSwUpdM_JobHandler_CompareModule,
  vSwUpdM_JobHandler_ValidateModuleUpdateLocalState,
  vSwUpdM_JobHandler_InvalidateModuleUpdateLocalState,
  vSwUpdM_JobHandler_Suspend,
  vSwUpdM_JobHandler_Resume,
  vSwUpdM_JobHandler_Start,
  vSwUpdM_JobHandler_Shutdown,
  vSwUpdM_JobHandler_RemoteLock,
  vSwUpdM_JobHandler_RemoteGroupConfirmation,
  vSwUpdM_JobHandler_RemoteGroupConfirmation,  /* SuspendConfirmation */
  vSwUpdM_JobHandler_RemoteGroupConfirmation,  /* ResumeConfirmation */
  vSwUpdM_JobHandler_RemoteGroupConfirmation,  /* ShutdownConfirmation */
  vSwUpdM_JobHandler_RemoteTargetConfirmation,
  vSwUpdM_JobHandler_ServiceDispatcher,
  vSwUpdM_JobHandler_TriggerConfirmation,       /* OpenPartitionLocalHooks */
  vSwUpdM_JobHandler_EraseRegionLocalWork,
  vSwUpdM_JobHandler_RemoteAddSegments,
  vSwUpdM_JobHandler_ClearSegmentsOfModule,
  vSwUpdM_JobHandler_RemoteProcessStreamData,
  vSwUpdM_JobHandler_ProcessEntity,
  vSwUpdM_JobHandler_RemoteProcessInfo,
  vSwUpdM_JobHandler_RemoteStreamScheduler,
  vSwUpdM_JobHandler_RemoteStreamCleanup,
  vSwUpdM_JobHandler_IndicateWriteToModule
};

/**********************************************************************************************************************
 *  vSwUpdM_ExecCtrl_ValidatePartition
 *********************************************************************************************************************/
/*! \brief       Set partition validity.
 *  \details     Spawns job to set partition validity.
 *  \param[in]   ParentJob Reference to parent job.
 *  \return      E_OK on success
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     ExecCtrlSequence
 *********************************************************************************************************************/
Std_ReturnType vSwUpdM_ExecCtrl_ValidatePartition(vSwUpdM_JobPtrType ParentJob);

/**********************************************************************************************************************
 *  vSwUpdM_ExecCtrl_InvalidatePartition
 *********************************************************************************************************************/
/*! \brief       Clear partition validity.
 *  \details     Spawns job to clear partition validity.
 *  \param[in]   ParentJob Reference to parent job.
 *  \return      E_OK on success
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     ExecCtrlSequence
 *********************************************************************************************************************/
Std_ReturnType vSwUpdM_ExecCtrl_InvalidatePartition(vSwUpdM_JobPtrType ParentJob);

/**********************************************************************************************************************
 *  vSwUpdM_ExecCtrl_TriggerRemoteWork
 *********************************************************************************************************************/
/*! \brief       Distribute current service to all children.
 *  \details     Spawns job to wait for results.
 *  \param[in]   ParentJob Reference to parent job.
 *  \return      E_OK on success
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     ExecCtrlSequence
 *********************************************************************************************************************/
Std_ReturnType vSwUpdM_ExecCtrl_TriggerRemoteWork(vSwUpdM_JobPtrType ParentJob);

/**********************************************************************************************************************
 *  vSwUpdM_ExecCtrl_FinalizeModule
 *********************************************************************************************************************/
/*! \brief       Trigger finalization of module.
 *  \details     Spawns job to finalize module.
 *  \param[in]   ParentJob Reference to parent job.
 *  \return      E_OK on success
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     ExecCtrlSequence
 *********************************************************************************************************************/
Std_ReturnType vSwUpdM_ExecCtrl_FinalizeModule(vSwUpdM_JobPtrType ParentJob);

/**********************************************************************************************************************
 *  vSwUpdM_ExecCtrl_SyncModule
 *********************************************************************************************************************/
/*! \brief       Trigger synchronization of module.
 *  \details     Spawns job to synchronize module.
 *  \param[in]   ParentJob Reference to parent job.
 *  \return      E_OK on success
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     ExecCtrlSequence
 *********************************************************************************************************************/
Std_ReturnType vSwUpdM_ExecCtrl_SyncModule(vSwUpdM_JobPtrType ParentJob);

/**********************************************************************************************************************
 *  vSwUpdM_ExecCtrl_SyncPartition
 *********************************************************************************************************************/
/*! \brief       Trigger synchronization of partition.
 *  \details     Spawns job to synchronize partition.
 *  \param[in]   ParentJob Reference to parent job.
 *  \return      E_OK on success
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     ExecCtrlSequence
 *********************************************************************************************************************/
Std_ReturnType vSwUpdM_ExecCtrl_SyncPartition(vSwUpdM_JobPtrType ParentJob);

/**********************************************************************************************************************
 *  vSwUpdM_ExecCtrl_OpenModule
 *********************************************************************************************************************/
/*! \brief       Trigger module open.
 *  \details     Spawns job to open module.
 *  \param[in]   ParentJob Reference to parent job.
 *  \return      E_OK on success
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     ExecCtrlSequence
 *********************************************************************************************************************/
Std_ReturnType vSwUpdM_ExecCtrl_OpenModule(vSwUpdM_JobPtrType ParentJob);

/**********************************************************************************************************************
 *  vSwUpdM_ExecCtrl_OpenModuleImplicit
 *********************************************************************************************************************/
/*! \brief       Trigger implicit module open.
 *  \details     Spawns job to open module.
 *  \param[in]   ParentJob Reference to parent job.
 *  \return      E_OK on success
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     ExecCtrlSequence
 *********************************************************************************************************************/
Std_ReturnType vSwUpdM_ExecCtrl_OpenModuleImplicit(vSwUpdM_JobPtrType ParentJob);

/**********************************************************************************************************************
 *  vSwUpdM_ExecCtrl_CloseModuleImplicit
 *********************************************************************************************************************/
/*! \brief       Trigger implicit module close.
 *  \details     Spawns job to open module.
 *  \param[in]   ParentJob Reference to parent job.
 *  \return      E_OK on success
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     ExecCtrlSequence
 *********************************************************************************************************************/
Std_ReturnType vSwUpdM_ExecCtrl_CloseModuleImplicit(vSwUpdM_JobPtrType ParentJob);

/* PRQA S 3218 1 */ /* MD_vSwUpdM_Rule8.9_3218_FileScope */
VSWUPDM_LOCAL CONST(vSwUpdM_ExecCtrl_SequenceEntryType, VSWUPDM_APPL_DATA) vSwUpdM_ExecCtrl_OpenPartitionSeq[] =
{
  /* Job,                                                 Function,                             Flags */
  {VSWUPDM_JOB_TYPE_INVALID,                              vSwUpdM_ExecCtrl_TriggerRemoteWork,   VSWUPDM_EXECCTRL_SEQUENCEFLAG_CALLFUNCTION | VSWUPDM_EXECCTRL_SEQUENCEFLAG_MULTINODE  },
  {VSWUPDM_JOB_TYPE_OPEN_PARTITION_LOCAL_HOOKS,           VSWUPDM_EXECCTRL_SEQ_NO_FUNCTION,     VSWUPDM_EXECCTRL_SEQUENCEFLAG_SPAWNJOB                                                }
};

/* PRQA S 3218 1 */ /* MD_vSwUpdM_Rule8.9_3218_FileScope */
VSWUPDM_LOCAL CONST(vSwUpdM_ExecCtrl_SequenceEntryType, VSWUPDM_APPL_DATA) vSwUpdM_ExecCtrl_ValidatePartitionSeq[] =
{
  /* Job,                                                 Function,                             Flags */
  {VSWUPDM_JOB_TYPE_INVALID,                              vSwUpdM_ExecCtrl_TriggerRemoteWork,   VSWUPDM_EXECCTRL_SEQUENCEFLAG_CALLFUNCTION | VSWUPDM_EXECCTRL_SEQUENCEFLAG_MULTINODE  },
  {VSWUPDM_JOB_TYPE_INVALID,                              vSwUpdM_ExecCtrl_ValidatePartition,   VSWUPDM_EXECCTRL_SEQUENCEFLAG_CALLFUNCTION                                            }
};

/* PRQA S 3218 1 */ /* MD_vSwUpdM_Rule8.9_3218_FileScope */
VSWUPDM_LOCAL CONST(vSwUpdM_ExecCtrl_SequenceEntryType, VSWUPDM_APPL_DATA) vSwUpdM_ExecCtrl_InvalidatePartitionSeq[] =
{
  /* Job,                                                 Function,                             Flags */
  {VSWUPDM_JOB_TYPE_INVALID,                              vSwUpdM_ExecCtrl_TriggerRemoteWork,   VSWUPDM_EXECCTRL_SEQUENCEFLAG_CALLFUNCTION | VSWUPDM_EXECCTRL_SEQUENCEFLAG_MULTINODE  },
  {VSWUPDM_JOB_TYPE_INVALID,                              vSwUpdM_ExecCtrl_InvalidatePartition, VSWUPDM_EXECCTRL_SEQUENCEFLAG_CALLFUNCTION                                            }
};

/* PRQA S 3218 1 */ /* MD_vSwUpdM_Rule8.9_3218_FileScope */
VSWUPDM_LOCAL CONST(vSwUpdM_ExecCtrl_SequenceEntryType, VSWUPDM_APPL_DATA) vSwUpdM_ExecCtrl_SwapPartitionSeq[] =
{
  /* Job,                                                 Function,                             Flags */
  {VSWUPDM_JOB_TYPE_SWAP_ACTIVE_PARTITION_CHECK,          VSWUPDM_EXECCTRL_SEQ_NO_FUNCTION,     VSWUPDM_EXECCTRL_SEQUENCEFLAG_SPAWNJOB                                               },
  {VSWUPDM_JOB_TYPE_INVALID,                              vSwUpdM_ExecCtrl_TriggerRemoteWork,   VSWUPDM_EXECCTRL_SEQUENCEFLAG_CALLFUNCTION | VSWUPDM_EXECCTRL_SEQUENCEFLAG_MULTINODE },
  {VSWUPDM_JOB_TYPE_SWAP_ACTIVE_PARTITION_WORK,           VSWUPDM_EXECCTRL_SEQ_NO_FUNCTION,     VSWUPDM_EXECCTRL_SEQUENCEFLAG_SPAWNJOB                                               }
};

/* PRQA S 3218 1 */ /* MD_vSwUpdM_Rule8.9_3218_FileScope */
VSWUPDM_LOCAL CONST(vSwUpdM_ExecCtrl_SequenceEntryType, VSWUPDM_APPL_DATA) vSwUpdM_ExecCtrl_FinalizeModuleSeq[] =
{
  /* Job,                                                 Function,                             Flags */
  {VSWUPDM_JOB_TYPE_REMOTE_ADD_SEGMENTS,                  VSWUPDM_EXECCTRL_SEQ_NO_FUNCTION,     VSWUPDM_EXECCTRL_SEQUENCEFLAG_SPAWNJOB |     VSWUPDM_EXECCTRL_SEQUENCEFLAG_MULTINODE },
  {VSWUPDM_JOB_TYPE_INVALID,                              vSwUpdM_ExecCtrl_FinalizeModule,      VSWUPDM_EXECCTRL_SEQUENCEFLAG_CALLFUNCTION                                           },
  {VSWUPDM_JOB_TYPE_INVALID,                              vSwUpdM_ExecCtrl_TriggerRemoteWork,   VSWUPDM_EXECCTRL_SEQUENCEFLAG_CALLFUNCTION | VSWUPDM_EXECCTRL_SEQUENCEFLAG_MULTINODE },
  {VSWUPDM_JOB_TYPE_FINALIZE_MODULE_UPDATE_LOCAL,         VSWUPDM_EXECCTRL_SEQ_NO_FUNCTION,     VSWUPDM_EXECCTRL_SEQUENCEFLAG_SPAWNJOB                                               }
};

/* PRQA S 3218 1 */ /* MD_vSwUpdM_Rule8.9_3218_FileScope */
VSWUPDM_LOCAL CONST(vSwUpdM_ExecCtrl_SequenceEntryType, VSWUPDM_APPL_DATA) vSwUpdM_ExecCtrl_VerifyModuleSeq[] =
{
  /* Job,                                                 Function,                             Flags */
  {VSWUPDM_JOB_TYPE_VERIFY_MODULE_LOCAL,                  VSWUPDM_EXECCTRL_SEQ_NO_FUNCTION,     VSWUPDM_EXECCTRL_SEQUENCEFLAG_SPAWNJOB                                               },
  {VSWUPDM_JOB_TYPE_INVALID,                              vSwUpdM_ExecCtrl_TriggerRemoteWork,   VSWUPDM_EXECCTRL_SEQUENCEFLAG_CALLFUNCTION | VSWUPDM_EXECCTRL_SEQUENCEFLAG_MULTINODE },
  {VSWUPDM_JOB_TYPE_REMOTE_STREAM_CLEANUP,                VSWUPDM_EXECCTRL_SEQ_NO_FUNCTION,     VSWUPDM_EXECCTRL_SEQUENCEFLAG_SPAWNJOB                                               }
};

/* PRQA S 3218 1 */ /* MD_vSwUpdM_Rule8.9_3218_FileScope */
VSWUPDM_LOCAL CONST(vSwUpdM_ExecCtrl_SequenceEntryType, VSWUPDM_APPL_DATA) vSwUpdM_ExecCtrl_ProcessModuleSeq[] =
{
  /* Job,                                                 Function,                             Flags */
  {VSWUPDM_JOB_TYPE_PROCESS_MODULE_LOCAL,                 VSWUPDM_EXECCTRL_SEQ_NO_FUNCTION,     VSWUPDM_EXECCTRL_SEQUENCEFLAG_SPAWNJOB                                               },
  {VSWUPDM_JOB_TYPE_INVALID,                              vSwUpdM_ExecCtrl_TriggerRemoteWork,   VSWUPDM_EXECCTRL_SEQUENCEFLAG_CALLFUNCTION | VSWUPDM_EXECCTRL_SEQUENCEFLAG_MULTINODE },
  {VSWUPDM_JOB_TYPE_REMOTE_STREAM_CLEANUP,                VSWUPDM_EXECCTRL_SEQ_NO_FUNCTION,     VSWUPDM_EXECCTRL_SEQUENCEFLAG_SPAWNJOB                                               }
};

/* PRQA S 3218 1 */ /* MD_vSwUpdM_Rule8.9_3218_FileScope */
VSWUPDM_LOCAL CONST(vSwUpdM_ExecCtrl_SequenceEntryType, VSWUPDM_APPL_DATA) vSwUpdM_ExecCtrl_VerifySegmentSeq[] =
{
  /* Simply do nothing, empty sequence. */
  /* Job,                                                 Function,                             Flags */
  {VSWUPDM_JOB_TYPE_INVALID,                              VSWUPDM_EXECCTRL_SEQ_NO_FUNCTION,     VSWUPDM_EXECCTRL_SEQUENCEFLAG_NONE                                                   }
};

/* PRQA S 3218 1 */ /* MD_vSwUpdM_Rule8.9_3218_FileScope */
VSWUPDM_LOCAL CONST(vSwUpdM_ExecCtrl_SequenceEntryType, VSWUPDM_APPL_DATA) vSwUpdM_ExecCtrl_SyncModuleSeq[] =
{
  /* Job,                                                 Function,                             Flags */
  {VSWUPDM_JOB_TYPE_INVALID,                              vSwUpdM_ExecCtrl_TriggerRemoteWork,   VSWUPDM_EXECCTRL_SEQUENCEFLAG_CALLFUNCTION | VSWUPDM_EXECCTRL_SEQUENCEFLAG_MULTINODE },
  {VSWUPDM_JOB_TYPE_INVALID,                              vSwUpdM_ExecCtrl_SyncModule,          VSWUPDM_EXECCTRL_SEQUENCEFLAG_CALLFUNCTION                                           }
};

/* PRQA S 3218 1 */ /* MD_vSwUpdM_Rule8.9_3218_FileScope */
VSWUPDM_LOCAL CONST(vSwUpdM_ExecCtrl_SequenceEntryType, VSWUPDM_APPL_DATA) vSwUpdM_ExecCtrl_ValidateModuleSeq[] =
{
  /* Job,                                                 Function,                             Flags */
  {VSWUPDM_JOB_TYPE_INVALID,                              vSwUpdM_ExecCtrl_TriggerRemoteWork,   VSWUPDM_EXECCTRL_SEQUENCEFLAG_CALLFUNCTION | VSWUPDM_EXECCTRL_SEQUENCEFLAG_MULTINODE },
  /* Job must be called here to trigger Hooks. */
  {VSWUPDM_JOB_TYPE_VALIDATE_MODULE_UPDATE_LOCAL_STATE,   VSWUPDM_EXECCTRL_SEQ_NO_FUNCTION,     VSWUPDM_EXECCTRL_SEQUENCEFLAG_SPAWNJOB                                               }
};

/* PRQA S 3218 1 */ /* MD_vSwUpdM_Rule8.9_3218_FileScope */
VSWUPDM_LOCAL CONST(vSwUpdM_ExecCtrl_SequenceEntryType, VSWUPDM_APPL_DATA) vSwUpdM_ExecCtrl_InvalidateModuleSeq[] =
{
  /* Job,                                                 Function,                             Flags */
  {VSWUPDM_JOB_TYPE_INVALID,                              vSwUpdM_ExecCtrl_TriggerRemoteWork,   VSWUPDM_EXECCTRL_SEQUENCEFLAG_CALLFUNCTION | VSWUPDM_EXECCTRL_SEQUENCEFLAG_MULTINODE },
  /* Job must be called here to trigger Hooks. */
  {VSWUPDM_JOB_TYPE_INVALIDATE_MODULE_UPDATE_LOCAL_STATE, VSWUPDM_EXECCTRL_SEQ_NO_FUNCTION,     VSWUPDM_EXECCTRL_SEQUENCEFLAG_SPAWNJOB                                               }
};

/* PRQA S 3218 1 */ /* MD_vSwUpdM_Rule8.9_3218_FileScope */
VSWUPDM_LOCAL CONST(vSwUpdM_ExecCtrl_SequenceEntryType, VSWUPDM_APPL_DATA) vSwUpdM_ExecCtrl_EraseModuleSeq[] =
{
  /* Job,                                                 Function,                             Flags */
  {VSWUPDM_JOB_TYPE_INVALID,                              vSwUpdM_ExecCtrl_OpenModuleImplicit,  VSWUPDM_EXECCTRL_SEQUENCEFLAG_CALLFUNCTION                                           },
  {VSWUPDM_JOB_TYPE_INVALID,                              vSwUpdM_ExecCtrl_TriggerRemoteWork,   VSWUPDM_EXECCTRL_SEQUENCEFLAG_CALLFUNCTION | VSWUPDM_EXECCTRL_SEQUENCEFLAG_MULTINODE },
  {VSWUPDM_JOB_TYPE_ERASE_MODULE_LOCAL,                   VSWUPDM_EXECCTRL_SEQ_NO_FUNCTION,     VSWUPDM_EXECCTRL_SEQUENCEFLAG_SPAWNJOB                                               },
  {VSWUPDM_JOB_TYPE_INVALID,                              vSwUpdM_ExecCtrl_CloseModuleImplicit, VSWUPDM_EXECCTRL_SEQUENCEFLAG_CALLFUNCTION                                           }
};

/* PRQA S 3218 1 */ /* MD_vSwUpdM_Rule8.9_3218_FileScope */
VSWUPDM_LOCAL CONST(vSwUpdM_ExecCtrl_SequenceEntryType, VSWUPDM_APPL_DATA) vSwUpdM_ExecCtrl_EraseRegionSeq[] =
{
  /* Job,                                                 Function,                             Flags */
  {VSWUPDM_JOB_TYPE_INVALID,                              vSwUpdM_ExecCtrl_TriggerRemoteWork,   VSWUPDM_EXECCTRL_SEQUENCEFLAG_CALLFUNCTION | VSWUPDM_EXECCTRL_SEQUENCEFLAG_MULTINODE },
  {VSWUPDM_JOB_TYPE_ERASE_REGION_LOCAL_WORK,              VSWUPDM_EXECCTRL_SEQ_NO_FUNCTION,     VSWUPDM_EXECCTRL_SEQUENCEFLAG_SPAWNJOB                                               }
};

/* PRQA S 3218 1 */ /* MD_vSwUpdM_Rule8.9_3218_FileScope */
VSWUPDM_LOCAL CONST(vSwUpdM_ExecCtrl_SequenceEntryType, VSWUPDM_APPL_DATA) vSwUpdM_ExecCtrl_OpenSegmentSeq[] =
{
  /* Job,                                                 Function,                             Flags */
  {VSWUPDM_JOB_TYPE_REMOTE_ADD_SEGMENTS,                  VSWUPDM_EXECCTRL_SEQ_NO_FUNCTION,     VSWUPDM_EXECCTRL_SEQUENCEFLAG_SPAWNJOB     | VSWUPDM_EXECCTRL_SEQUENCEFLAG_MULTINODE },
  {VSWUPDM_JOB_TYPE_INVALID,                              vSwUpdM_ExecCtrl_TriggerRemoteWork,   VSWUPDM_EXECCTRL_SEQUENCEFLAG_CALLFUNCTION | VSWUPDM_EXECCTRL_SEQUENCEFLAG_MULTINODE },
  {VSWUPDM_JOB_TYPE_OPEN_SEGMENT,                         VSWUPDM_EXECCTRL_SEQ_NO_FUNCTION,     VSWUPDM_EXECCTRL_SEQUENCEFLAG_SPAWNJOB                                               }
};

/* PRQA S 3218 1 */ /* MD_vSwUpdM_Rule8.9_3218_FileScope */
VSWUPDM_LOCAL CONST(vSwUpdM_ExecCtrl_SequenceEntryType, VSWUPDM_APPL_DATA) vSwUpdM_ExecCtrl_CloseSegmentSeq[] =
{
  /* Job,                                                 Function,                             Flags */
  {VSWUPDM_JOB_TYPE_INVALID,                              vSwUpdM_ExecCtrl_TriggerRemoteWork,   VSWUPDM_EXECCTRL_SEQUENCEFLAG_CALLFUNCTION | VSWUPDM_EXECCTRL_SEQUENCEFLAG_MULTINODE },
  {VSWUPDM_JOB_TYPE_CLOSE_SEGMENT,                        VSWUPDM_EXECCTRL_SEQ_NO_FUNCTION,     VSWUPDM_EXECCTRL_SEQUENCEFLAG_SPAWNJOB                                               }
};

/* PRQA S 3218 1 */ /* MD_vSwUpdM_Rule8.9_3218_FileScope */
VSWUPDM_LOCAL CONST(vSwUpdM_ExecCtrl_SequenceEntryType, VSWUPDM_APPL_DATA) vSwUpdM_ExecCtrl_ClearSegmentsSeq[] =
{
  /* Job,                                                 Function,                             Flags */
  {VSWUPDM_JOB_TYPE_INVALID,                              vSwUpdM_ExecCtrl_TriggerRemoteWork,   VSWUPDM_EXECCTRL_SEQUENCEFLAG_CALLFUNCTION | VSWUPDM_EXECCTRL_SEQUENCEFLAG_MULTINODE },
  {VSWUPDM_JOB_TYPE_CLEAR_SEGMENTS_OF_MODULE,             VSWUPDM_EXECCTRL_SEQ_NO_FUNCTION,     VSWUPDM_EXECCTRL_SEQUENCEFLAG_SPAWNJOB                                               }
};

/* PRQA S 3218 1 */ /* MD_vSwUpdM_Rule8.9_3218_FileScope */
VSWUPDM_LOCAL CONST(vSwUpdM_ExecCtrl_SequenceEntryType, VSWUPDM_APPL_DATA) vSwUpdM_ExecCtrl_FinalizeSegmentSeq[] =
{
  /* Job,                                                 Function,                             Flags */
  {VSWUPDM_JOB_TYPE_FINALIZE_SEGMENT,                     VSWUPDM_EXECCTRL_SEQ_NO_FUNCTION,     VSWUPDM_EXECCTRL_SEQUENCEFLAG_SPAWNJOB                                               },
  {VSWUPDM_JOB_TYPE_INVALID,                              vSwUpdM_ExecCtrl_TriggerRemoteWork,   VSWUPDM_EXECCTRL_SEQUENCEFLAG_CALLFUNCTION | VSWUPDM_EXECCTRL_SEQUENCEFLAG_MULTINODE },
  {VSWUPDM_JOB_TYPE_FINALIZE_SEGMENT_UPDATE_LOCAL_STATE,  VSWUPDM_EXECCTRL_SEQ_NO_FUNCTION,     VSWUPDM_EXECCTRL_SEQUENCEFLAG_SPAWNJOB                                               }
};

/* PRQA S 3218 1 */ /* MD_vSwUpdM_Rule8.9_3218_FileScope */
VSWUPDM_LOCAL CONST(vSwUpdM_ExecCtrl_SequenceEntryType, VSWUPDM_APPL_DATA) vSwUpdM_ExecCtrl_SyncPartitionSeq[] =
{
  /* Job,                                                 Function,                             Flags */
  {VSWUPDM_JOB_TYPE_INVALID,                              vSwUpdM_ExecCtrl_SyncPartition,       VSWUPDM_EXECCTRL_SEQUENCEFLAG_CALLFUNCTION                                           },
  {VSWUPDM_JOB_TYPE_INVALID,                              vSwUpdM_ExecCtrl_TriggerRemoteWork,   VSWUPDM_EXECCTRL_SEQUENCEFLAG_CALLFUNCTION | VSWUPDM_EXECCTRL_SEQUENCEFLAG_MULTINODE },
  {VSWUPDM_JOB_TYPE_FINALIZE_SYNC_PARTITION,              VSWUPDM_EXECCTRL_SEQ_NO_FUNCTION,     VSWUPDM_EXECCTRL_SEQUENCEFLAG_SPAWNJOB                                               }
};

/* PRQA S 3218 1 */ /* MD_vSwUpdM_Rule8.9_3218_FileScope */
VSWUPDM_LOCAL CONST(vSwUpdM_ExecCtrl_SequenceEntryType, VSWUPDM_APPL_DATA) vSwUpdM_ExecCtrl_StartStreamSeq[] =
{
  /* Job,                                                 Function,                             Flags */
  {VSWUPDM_JOB_TYPE_INVALID,                              vSwUpdM_ExecCtrl_TriggerRemoteWork,   VSWUPDM_EXECCTRL_SEQUENCEFLAG_CALLFUNCTION | VSWUPDM_EXECCTRL_SEQUENCEFLAG_MULTINODE },
  /* Job must be called here to trigger Hooks. */
  {VSWUPDM_JOB_TYPE_START_STREAM,                         VSWUPDM_EXECCTRL_SEQ_NO_FUNCTION,     VSWUPDM_EXECCTRL_SEQUENCEFLAG_SPAWNJOB                                               }
};

/* PRQA S 3218 1 */ /* MD_vSwUpdM_Rule8.9_3218_FileScope */
VSWUPDM_LOCAL CONST(vSwUpdM_ExecCtrl_SequenceEntryType, VSWUPDM_APPL_DATA) vSwUpdM_ExecCtrl_EndStreamSeq[] =
{
  /* Job,                                                 Function,                             Flags */
  {VSWUPDM_JOB_TYPE_INVALID,                              vSwUpdM_ExecCtrl_TriggerRemoteWork,   VSWUPDM_EXECCTRL_SEQUENCEFLAG_CALLFUNCTION | VSWUPDM_EXECCTRL_SEQUENCEFLAG_MULTINODE },
  {VSWUPDM_JOB_TYPE_END_STREAM,                           VSWUPDM_EXECCTRL_SEQ_NO_FUNCTION,     VSWUPDM_EXECCTRL_SEQUENCEFLAG_SPAWNJOB                                               }
};

/* PRQA S 3218 1 */ /* MD_vSwUpdM_Rule8.9_3218_FileScope */
VSWUPDM_LOCAL CONST(vSwUpdM_ExecCtrl_SequenceEntryType, VSWUPDM_APPL_DATA) vSwUpdM_ExecCtrl_OpenModuleSeq[] =
{
  /* Job,                                                 Function,                             Flags */
  {VSWUPDM_JOB_TYPE_INVALID,                              vSwUpdM_ExecCtrl_OpenModule,          VSWUPDM_EXECCTRL_SEQUENCEFLAG_CALLFUNCTION                                           },
  {VSWUPDM_JOB_TYPE_INVALID,                              vSwUpdM_ExecCtrl_TriggerRemoteWork,   VSWUPDM_EXECCTRL_SEQUENCEFLAG_CALLFUNCTION | VSWUPDM_EXECCTRL_SEQUENCEFLAG_MULTINODE },
};

/* PRQA S 3218 1 */ /* MD_vSwUpdM_Rule8.9_3218_FileScope */
VSWUPDM_LOCAL CONST(vSwUpdM_ExecCtrl_SequenceEntryType, VSWUPDM_APPL_DATA) vSwUpdM_ExecCtrl_CloseModuleSeq[] =
{
  /* Job,                                                 Function,                             Flags */
  {VSWUPDM_JOB_TYPE_REMOTE_ADD_SEGMENTS,                  VSWUPDM_EXECCTRL_SEQ_NO_FUNCTION,     VSWUPDM_EXECCTRL_SEQUENCEFLAG_SPAWNJOB     | VSWUPDM_EXECCTRL_SEQUENCEFLAG_MULTINODE },
  {VSWUPDM_JOB_TYPE_INVALID,                              vSwUpdM_ExecCtrl_TriggerRemoteWork,   VSWUPDM_EXECCTRL_SEQUENCEFLAG_CALLFUNCTION | VSWUPDM_EXECCTRL_SEQUENCEFLAG_MULTINODE },
  {VSWUPDM_JOB_TYPE_CLOSE_MODULE_LOCAL,                   VSWUPDM_EXECCTRL_SEQ_NO_FUNCTION,     VSWUPDM_EXECCTRL_SEQUENCEFLAG_SPAWNJOB                                               }
};

/* PRQA S 3218 1 */ /* MD_vSwUpdM_Rule8.9_3218_FileScope */
VSWUPDM_LOCAL CONST(vSwUpdM_ExecCtrl_SequenceEntryType, VSWUPDM_APPL_DATA) vSwUpdM_ExecCtrl_CheckPartitionSeq[] =
{
  /* Job,                                                 Function,                             Flags */
  {VSWUPDM_JOB_TYPE_INVALID,                              vSwUpdM_ExecCtrl_TriggerRemoteWork,   VSWUPDM_EXECCTRL_SEQUENCEFLAG_CALLFUNCTION | VSWUPDM_EXECCTRL_SEQUENCEFLAG_MULTINODE },
  /* Job must be called here to trigger Hooks. */
  {VSWUPDM_JOB_TYPE_CHECK_PARTITION_CONSISTENCY,          VSWUPDM_EXECCTRL_SEQ_NO_FUNCTION,     VSWUPDM_EXECCTRL_SEQUENCEFLAG_SPAWNJOB                                               }
};

/* PRQA S 3218 1 */ /* MD_vSwUpdM_Rule8.9_3218_FileScope */
VSWUPDM_LOCAL CONST(vSwUpdM_ExecCtrl_SequenceEntryType, VSWUPDM_APPL_DATA) vSwUpdM_ExecCtrl_IndicateWriteToModuleSeq[] =
{
  /* Job,                                                 Function,                             Flags */
  {VSWUPDM_JOB_TYPE_INVALID,                              vSwUpdM_ExecCtrl_OpenModuleImplicit,  VSWUPDM_EXECCTRL_SEQUENCEFLAG_CALLFUNCTION                                           },
  {VSWUPDM_JOB_TYPE_INVALID,                              vSwUpdM_ExecCtrl_TriggerRemoteWork,   VSWUPDM_EXECCTRL_SEQUENCEFLAG_CALLFUNCTION | VSWUPDM_EXECCTRL_SEQUENCEFLAG_MULTINODE },
  {VSWUPDM_JOB_TYPE_INDICATE_WRITE_TO_MODULE,             VSWUPDM_EXECCTRL_SEQ_NO_FUNCTION,     VSWUPDM_EXECCTRL_SEQUENCEFLAG_SPAWNJOB                                               },
  {VSWUPDM_JOB_TYPE_INVALID,                              vSwUpdM_ExecCtrl_CloseModuleImplicit, VSWUPDM_EXECCTRL_SEQUENCEFLAG_CALLFUNCTION                                           }
};

/* PRQA S 3218 1 */ /* MD_vSwUpdM_Rule8.9_3218_FileScope */
VSWUPDM_LOCAL vSwUpdM_ExecCtrl_SequencesListConstType vSwUpdM_ExecCtrl_SequencesList[] =
{
  {vSwUpdM_ExecCtrl_OpenPartitionSeq,         VSWUPDM_ARRAY_SIZE(vSwUpdM_ExecCtrl_OpenPartitionSeq)         }, /**< VSWUPDM_SID_OPEN_PARTITION              */
  {vSwUpdM_ExecCtrl_ValidatePartitionSeq,     VSWUPDM_ARRAY_SIZE(vSwUpdM_ExecCtrl_ValidatePartitionSeq)     }, /**< VSWUPDM_SID_VALIDATE_PARTITION          */
  {vSwUpdM_ExecCtrl_InvalidatePartitionSeq,   VSWUPDM_ARRAY_SIZE(vSwUpdM_ExecCtrl_InvalidatePartitionSeq)   }, /**< VSWUPDM_SID_INVALIDATE_PARTITION        */
  {vSwUpdM_ExecCtrl_SwapPartitionSeq,         VSWUPDM_ARRAY_SIZE(vSwUpdM_ExecCtrl_SwapPartitionSeq)         }, /**< VSWUPDM_SID_SWAP_ACTIVE_PARTITION       */
  {vSwUpdM_ExecCtrl_FinalizeModuleSeq,        VSWUPDM_ARRAY_SIZE(vSwUpdM_ExecCtrl_FinalizeModuleSeq)        }, /**< VSWUPDM_SID_FINALIZE_MODULE             */
  {vSwUpdM_ExecCtrl_VerifyModuleSeq,          VSWUPDM_ARRAY_SIZE(vSwUpdM_ExecCtrl_VerifyModuleSeq)          }, /**< VSWUPDM_SID_VERIFY_MODULE               */
  {vSwUpdM_ExecCtrl_ProcessModuleSeq,         VSWUPDM_ARRAY_SIZE(vSwUpdM_ExecCtrl_ProcessModuleSeq)         }, /**< VSWUPDM_SID_PROCESS_MODULE              */
  {vSwUpdM_ExecCtrl_VerifySegmentSeq,         VSWUPDM_ARRAY_SIZE(vSwUpdM_ExecCtrl_VerifySegmentSeq)         }, /**< VSWUPDM_SID_VERIFY_SEGMENT              */
  {vSwUpdM_ExecCtrl_SyncModuleSeq,            VSWUPDM_ARRAY_SIZE(vSwUpdM_ExecCtrl_SyncModuleSeq)            }, /**< VSWUPDM_SID_SYNC_MODULE                 */
  {vSwUpdM_ExecCtrl_ValidateModuleSeq,        VSWUPDM_ARRAY_SIZE(vSwUpdM_ExecCtrl_ValidateModuleSeq)        }, /**< VSWUPDM_SID_VALIDATE_MODULE             */
  {vSwUpdM_ExecCtrl_InvalidateModuleSeq,      VSWUPDM_ARRAY_SIZE(vSwUpdM_ExecCtrl_InvalidateModuleSeq)      }, /**< VSWUPDM_SID_INVALIDATE_MODULE           */
  {vSwUpdM_ExecCtrl_EraseModuleSeq,           VSWUPDM_ARRAY_SIZE(vSwUpdM_ExecCtrl_EraseModuleSeq)           }, /**< VSWUPDM_SID_ERASE_MODULE                */
  {vSwUpdM_ExecCtrl_EraseRegionSeq,           VSWUPDM_ARRAY_SIZE(vSwUpdM_ExecCtrl_EraseRegionSeq)           }, /**< VSWUPDM_SID_ERASE_REGION                */
  {vSwUpdM_ExecCtrl_OpenSegmentSeq,           VSWUPDM_ARRAY_SIZE(vSwUpdM_ExecCtrl_OpenSegmentSeq)           }, /**< VSWUPDM_SID_OPEN_SEGMENT                */
  {vSwUpdM_ExecCtrl_CloseSegmentSeq,          VSWUPDM_ARRAY_SIZE(vSwUpdM_ExecCtrl_CloseSegmentSeq)          }, /**< VSWUPDM_SID_CLOSE_SEGMENT               */
  {vSwUpdM_ExecCtrl_ClearSegmentsSeq,         VSWUPDM_ARRAY_SIZE(vSwUpdM_ExecCtrl_ClearSegmentsSeq)         }, /**< VSWUPDM_SID_CLEAR_SEGMENTS_OF_MODULE    */
  {vSwUpdM_ExecCtrl_FinalizeSegmentSeq,       VSWUPDM_ARRAY_SIZE(vSwUpdM_ExecCtrl_FinalizeSegmentSeq)       }, /**< VSWUPDM_SID_FINALIZE_SEGMENT            */
  {vSwUpdM_ExecCtrl_SyncPartitionSeq,         VSWUPDM_ARRAY_SIZE(vSwUpdM_ExecCtrl_SyncPartitionSeq)         }, /**< VSWUPDM_SID_SYNC_PARTITION              */
  {vSwUpdM_ExecCtrl_StartStreamSeq,           VSWUPDM_ARRAY_SIZE(vSwUpdM_ExecCtrl_StartStreamSeq)           }, /**< VSWUPDM_SID_START_STREAM                */
  {vSwUpdM_ExecCtrl_EndStreamSeq,             VSWUPDM_ARRAY_SIZE(vSwUpdM_ExecCtrl_EndStreamSeq)             }, /**< VSWUPDM_SID_END_STREAM                  */
  {vSwUpdM_ExecCtrl_OpenModuleSeq,            VSWUPDM_ARRAY_SIZE(vSwUpdM_ExecCtrl_OpenModuleSeq)            }, /**< VSWUPDM_SID_OPEN_MODULE                 */
  {vSwUpdM_ExecCtrl_CloseModuleSeq,           VSWUPDM_ARRAY_SIZE(vSwUpdM_ExecCtrl_CloseModuleSeq)           }, /**< VSWUPDM_SID_CLOSE_MODULE                */
  {vSwUpdM_ExecCtrl_CheckPartitionSeq,        VSWUPDM_ARRAY_SIZE(vSwUpdM_ExecCtrl_CheckPartitionSeq)        }, /**< VSWUPDM_SID_CHECK_PARTITION_CONSISTENCY */
  {vSwUpdM_ExecCtrl_IndicateWriteToModuleSeq, VSWUPDM_ARRAY_SIZE(vSwUpdM_ExecCtrl_IndicateWriteToModuleSeq) }  /**< VSWUPDM_SID_INDICATE_WRITE_TO_MODULE    */
};

/* PRQA S 3218 1 */ /* MD_vSwUpdM_Rule8.9_3218_FileScope */
VSWUPDM_LOCAL CONST(vSwUpdM_JobDefinitionType, VSWUPDM_CONST) vSwUpdM_JobDefinitions[VSWUPDM_JOB_TYPE_COUNT] =
{
  { VSWUPDM_JOB_TYPE_INIT_COMPONENT,                        VSWUPDM_SID_NONE,                         VSWUPDM_JOB_PRIO_INIT_COMPONENT,                        TRUE   },
  { VSWUPDM_JOB_TYPE_INIT_PARTITIONS,                       VSWUPDM_SID_NONE,                         VSWUPDM_JOB_PRIO_INIT_PARTITIONS,                       FALSE  },
  { VSWUPDM_JOB_TYPE_INIT_MODULES,                          VSWUPDM_SID_NONE,                         VSWUPDM_JOB_PRIO_INIT_MODULES,                          FALSE  },
  { VSWUPDM_JOB_TYPE_INIT_REGIONS,                          VSWUPDM_SID_NONE,                         VSWUPDM_JOB_PRIO_INIT_REGIONS,                          TRUE   },
  { VSWUPDM_JOB_TYPE_INIT_SEGMENTS,                         VSWUPDM_SID_NONE,                         VSWUPDM_JOB_PRIO_INIT_SEGMENTS,                         TRUE   },
  { VSWUPDM_JOB_TYPE_FINALIZE_SYNC_PARTITION,               VSWUPDM_SID_NONE,                         VSWUPDM_JOB_PRIO_FINALIZE_SYNC_PARTITION,               TRUE   },
  { VSWUPDM_JOB_TYPE_SWAP_ACTIVE_PARTITION_CHECK,           VSWUPDM_SID_NONE,                         VSWUPDM_JOB_PRIO_SWAP_ACTIVE_PARTITION_CHECK,           TRUE   },
  { VSWUPDM_JOB_TYPE_SWAP_ACTIVE_PARTITION_WORK,            VSWUPDM_SID_SWAP_ACTIVE_PARTITION,        VSWUPDM_JOB_PRIO_SWAP_ACTIVE_PARTITION_WORK,            TRUE   },
  { VSWUPDM_JOB_TYPE_FINALIZE_MODULE_UPDATE_LOCAL,          VSWUPDM_SID_NONE,                         VSWUPDM_JOB_PRIO_FINALIZE_MODULE_UPDATE_LOCAL,          TRUE   },
  { VSWUPDM_JOB_TYPE_OPEN_MODULE_LOCAL,                     VSWUPDM_SID_OPEN_MODULE,                  VSWUPDM_JOB_PRIO_OPEN_MODULE_LOCAL,                     TRUE   },
  { VSWUPDM_JOB_TYPE_CLEANUP_MODULE,                        VSWUPDM_SID_NONE,                         VSWUPDM_JOB_PRIO_CLEANUP_MODULE,                        TRUE   },
  { VSWUPDM_JOB_TYPE_CLOSE_MODULE_LOCAL,                    VSWUPDM_SID_CLOSE_MODULE,                 VSWUPDM_JOB_PRIO_CLOSE_MODULE_LOCAL,                    TRUE   },
  { VSWUPDM_JOB_TYPE_HANDLE_UPDATE_STATE,                   VSWUPDM_SID_NONE,                         VSWUPDM_JOB_PRIO_HANDLE_UPDATE_STATE,                   FALSE  },
  { VSWUPDM_JOB_TYPE_HANDLE_RESUME_INFO,                    VSWUPDM_SID_NONE,                         VSWUPDM_JOB_PRIO_HANDLE_RESUME_INFO,                    FALSE  },
  { VSWUPDM_JOB_TYPE_PERSIST_PARTITION_STATE,               VSWUPDM_SID_NONE,                         VSWUPDM_JOB_PRIO_PERSIST_PARTITION_STATE,               FALSE  },
  { VSWUPDM_JOB_TYPE_INVALIDATE_PARTITION_LOCAL,            VSWUPDM_SID_INVALIDATE_PARTITION,         VSWUPDM_JOB_PRIO_INVALIDATE_PARTITION_LOCAL,            FALSE  },
  { VSWUPDM_JOB_TYPE_VALIDATE_PARTITION_LOCAL,              VSWUPDM_SID_VALIDATE_PARTITION,           VSWUPDM_JOB_PRIO_VALIDATE_PARTITION_LOCAL,              FALSE  },
  { VSWUPDM_JOB_TYPE_CHECK_PARTITION_CONSISTENCY,           VSWUPDM_SID_CHECK_PARTITION_CONSISTENCY,  VSWUPDM_JOB_PRIO_CHECK_PARTITION_CONSISTENCY,           FALSE  },
  { VSWUPDM_JOB_TYPE_PERSIST_MODULE_STATE,                  VSWUPDM_SID_NONE,                         VSWUPDM_JOB_PRIO_PERSIST_MODULE_STATE,                  FALSE  },
  { VSWUPDM_JOB_TYPE_INVALIDATE_MODULE_INTERNAL,            VSWUPDM_SID_NONE,                         VSWUPDM_JOB_PRIO_INVALIDATE_MODULE_INTERNAL,            FALSE  },
  { VSWUPDM_JOB_TYPE_VALIDATE_MODULE_INTERNAL,              VSWUPDM_SID_NONE,                         VSWUPDM_JOB_PRIO_VALIDATE_MODULE_INTERNAL,              FALSE  },
  { VSWUPDM_JOB_TYPE_PERSIST_REGION_STATE,                  VSWUPDM_SID_NONE,                         VSWUPDM_JOB_PRIO_PERSIST_REGION_STATE,                  FALSE  },
  { VSWUPDM_JOB_TYPE_PERSIST_ALL_REGION_STATES,             VSWUPDM_SID_NONE,                         VSWUPDM_JOB_PRIO_PERSIST_ALL_REGION_STATES,             FALSE  },
  { VSWUPDM_JOB_TYPE_PERSIST_SEGMENT_STATE,                 VSWUPDM_SID_NONE,                         VSWUPDM_JOB_PRIO_PERSIST_SEGMENT_STATE,                 FALSE  },
  { VSWUPDM_JOB_TYPE_PERSIST_SEGMENT_COUNT,                 VSWUPDM_SID_NONE,                         VSWUPDM_JOB_PRIO_PERSIST_SEGMENT_COUNT,                 FALSE  },
  { VSWUPDM_JOB_TYPE_OPEN_SEGMENT,                          VSWUPDM_SID_OPEN_SEGMENT,                 VSWUPDM_JOB_PRIO_OPEN_SEGMENT,                          FALSE  },
  { VSWUPDM_JOB_TYPE_CLOSE_SEGMENT,                         VSWUPDM_SID_CLOSE_SEGMENT,                VSWUPDM_JOB_PRIO_CLOSE_SEGMENT,                         FALSE  },
  { VSWUPDM_JOB_TYPE_WAIT_FOR_BOOKKEEPER_OPERATION,         VSWUPDM_SID_NONE,                         VSWUPDM_JOB_PRIO_WAIT_FOR_BOOKKEEPER_OPERATION,         FALSE  },
  { VSWUPDM_JOB_TYPE_ERASE_MODULE_LOCAL,                    VSWUPDM_SID_ERASE_MODULE,                 VSWUPDM_JOB_PRIO_ERASE_MODULE_LOCAL,                    TRUE   },
  { VSWUPDM_JOB_TYPE_ERASE_REGION,                          VSWUPDM_SID_ERASE_REGION,                 VSWUPDM_JOB_PRIO_ERASE_REGION,                          TRUE   },
  { VSWUPDM_JOB_TYPE_ERASE_RANGE,                           VSWUPDM_SID_ERASE_RANGE,                  VSWUPDM_JOB_PRIO_ERASE_RANGE,                           TRUE   },
  { VSWUPDM_JOB_TYPE_START_STREAM,                          VSWUPDM_SID_START_STREAM,                 VSWUPDM_JOB_PRIO_START_STREAM,                          FALSE  },
  { VSWUPDM_JOB_TYPE_PROCESS_STREAM_DATA,                   VSWUPDM_SID_PROCESS_STREAM_DATA,          VSWUPDM_JOB_PRIO_PROCESS_STREAM_DATA,                   FALSE  },
  { VSWUPDM_JOB_TYPE_END_STREAM,                            VSWUPDM_SID_END_STREAM,                   VSWUPDM_JOB_PRIO_END_STREAM,                            TRUE   },
  { VSWUPDM_JOB_TYPE_FILL_MEMORY,                           VSWUPDM_SID_NONE,                         VSWUPDM_JOB_PRIO_FILL_MEMORY,                           TRUE   },
  { VSWUPDM_JOB_TYPE_READ_DATA,                             VSWUPDM_SID_READ_RANGE,                   VSWUPDM_JOB_PRIO_READ_DATA,                             FALSE  },
  { VSWUPDM_JOB_TYPE_WRITE_DATA,                            VSWUPDM_SID_WRITE_RANGE,                  VSWUPDM_JOB_PRIO_WRITE_DATA,                            FALSE  },
  { VSWUPDM_JOB_TYPE_PROCESS_STREAM_PIPELINED,              VSWUPDM_SID_NONE,                         VSWUPDM_JOB_PRIO_PROCESS_STREAM_PIPELINED,              TRUE   },
  { VSWUPDM_JOB_TYPE_WAIT_FOR_MEMORY_OPERATION,             VSWUPDM_SID_NONE,                         VSWUPDM_JOB_PRIO_WAIT_FOR_MEMORY_OPERATION,             FALSE  },
  { VSWUPDM_JOB_TYPE_FINALIZE_MODULE_LOCAL,                 VSWUPDM_SID_FINALIZE_MODULE,              VSWUPDM_JOB_PRIO_FINALIZE_MODULE_LOCAL,                 TRUE   },
  { VSWUPDM_JOB_TYPE_VERIFY_MODULE_LOCAL,                   VSWUPDM_SID_VERIFY_MODULE,                VSWUPDM_JOB_PRIO_VERIFY_MODULE_LOCAL,                   TRUE   },
  { VSWUPDM_JOB_TYPE_PROCESS_MODULE_LOCAL,                  VSWUPDM_SID_PROCESS_MODULE,               VSWUPDM_JOB_PRIO_PROCESS_MODULE_LOCAL,                  TRUE   },
  { VSWUPDM_JOB_TYPE_FINALIZE_SEGMENT,                      VSWUPDM_SID_FINALIZE_SEGMENT,             VSWUPDM_JOB_PRIO_FINALIZE_SEGMENT,                      TRUE   },
  { VSWUPDM_JOB_TYPE_FINALIZE_SEGMENT_UPDATE_LOCAL_STATE,   VSWUPDM_SID_NONE,                         VSWUPDM_JOB_PRIO_FINALIZE_SEGMENT_UPDATE_LOCAL_STATE,   TRUE   },
  { VSWUPDM_JOB_TYPE_SYNC_PARTITION_LOCAL,                  VSWUPDM_SID_SYNC_PARTITION,               VSWUPDM_JOB_PRIO_SYNC_PARTITION_LOCAL,                  TRUE   },
  { VSWUPDM_JOB_TYPE_SYNC_MODULE,                           VSWUPDM_SID_SYNC_MODULE,                  VSWUPDM_JOB_PRIO_SYNC_MODULE,                           TRUE   },
  { VSWUPDM_JOB_TYPE_COMPARE_MODULE,                        VSWUPDM_SID_NONE,                         VSWUPDM_JOB_PRIO_COMPARE_MODULE,                        TRUE   },
  { VSWUPDM_JOB_TYPE_VALIDATE_MODULE_UPDATE_LOCAL_STATE,    VSWUPDM_SID_VALIDATE_MODULE,              VSWUPDM_JOB_PRIO_VALIDATE_MODULE_UPDATE_LOCAL_STATE,    TRUE   },
  { VSWUPDM_JOB_TYPE_INVALIDATE_MODULE_UPDATE_LOCAL_STATE,  VSWUPDM_SID_INVALIDATE_MODULE,            VSWUPDM_JOB_PRIO_INVALIDATE_MODULE_UPDATE_LOCAL_STATE,  TRUE   },
  { VSWUPDM_JOB_TYPE_SUSPEND,                               VSWUPDM_SID_SUSPEND,                      VSWUPDM_JOB_PRIO_SUSPEND,                               FALSE  },
  { VSWUPDM_JOB_TYPE_RESUME,                                VSWUPDM_SID_RESUME,                       VSWUPDM_JOB_PRIO_RESUME,                                FALSE  },
  { VSWUPDM_JOB_TYPE_START,                                 VSWUPDM_SID_START,                        VSWUPDM_JOB_PRIO_START,                                 FALSE  },
  { VSWUPDM_JOB_TYPE_SHUTDOWN,                              VSWUPDM_SID_SHUTDOWN,                     VSWUPDM_JOB_PRIO_SHUTDOWN,                              FALSE  },
  { VSWUPDM_JOB_TYPE_REMOTE_LOCK,                           VSWUPDM_SID_NONE,                         VSWUPDM_JOB_PRIO_REMOTE_LOCK,                           FALSE  },
  { VSWUPDM_JOB_TYPE_REMOTE_GROUP_CONFIRMATION,             VSWUPDM_SID_NONE,                         VSWUPDM_JOB_PRIO_REMOTE_GROUP_CONFIRMATION,             FALSE  },
  { VSWUPDM_JOB_TYPE_REMOTE_SUSPEND_CONFIRMATION,           VSWUPDM_SID_NONE,                         VSWUPDM_JOB_PRIO_REMOTE_SUSPEND_CONFIRMATION,           FALSE  },
  { VSWUPDM_JOB_TYPE_REMOTE_RESUME_CONFIRMATION,            VSWUPDM_SID_NONE,                         VSWUPDM_JOB_PRIO_REMOTE_RESUME_CONFIRMATION,            FALSE  },
  { VSWUPDM_JOB_TYPE_REMOTE_SHUTDOWN_CONFIRMATION,          VSWUPDM_SID_NONE,                         VSWUPDM_JOB_PRIO_REMOTE_SHUTDOWN_CONFIRMATION,          FALSE  },
  { VSWUPDM_JOB_TYPE_REMOTE_TARGET_CONFIRMATION,            VSWUPDM_SID_NONE,                         VSWUPDM_JOB_PRIO_REMOTE_TARGET_CONFIRMATION,            FALSE  },
  { VSWUPDM_JOB_TYPE_SERVICE_DISPATCHER,                    VSWUPDM_SID_NONE,                         VSWUPDM_JOB_PRIO_SERVICE_DISPATCHER,                    FALSE  },
  { VSWUPDM_JOB_TYPE_OPEN_PARTITION_LOCAL_HOOKS,            VSWUPDM_SID_OPEN_PARTITION,               VSWUPDM_JOB_PRIO_OPEN_PARTITION_LOCAL_HOOKS,            TRUE   },
  { VSWUPDM_JOB_TYPE_ERASE_REGION_LOCAL_WORK,               VSWUPDM_SID_NONE,                         VSWUPDM_JOB_PRIO_ERASE_REGION_LOCAL_WORK,               TRUE   },
  { VSWUPDM_JOB_TYPE_REMOTE_ADD_SEGMENTS,                   VSWUPDM_SID_NONE,                         VSWUPDM_JOB_PRIO_REMOTE_ADD_SEGMENTS,                   TRUE   },
  { VSWUPDM_JOB_TYPE_CLEAR_SEGMENTS_OF_MODULE,              VSWUPDM_SID_NONE,                         VSWUPDM_JOB_PRIO_CLEAR_SEGMENTS_OF_MODULE,              TRUE   },
  { VSWUPDM_JOB_TYPE_REMOTE_PROCESS_STREAM_DATA,            VSWUPDM_SID_NONE,                         VSWUPDM_JOB_PRIO_REMOTE_PROCESS_STREAM_DATA,            FALSE  },
  { VSWUPDM_JOB_TYPE_PROCESS_ENTITY,                        VSWUPDM_SID_PROCESS_MODULE,               VSWUPDM_JOB_PRIO_PROCESS,                               FALSE  },
  { VSWUPDM_JOB_TYPE_REMOTE_PROCESS_INFO,                   VSWUPDM_SID_NONE,                         VSWUPDM_JOB_PRIO_REMOTE_PROCESS_INFO,                   FALSE  },
  { VSWUPDM_JOB_TYPE_REMOTE_STREAM_SCHEDULER,               VSWUPDM_SID_NONE,                         VSWUPDM_JOB_PRIO_REMOTE_STREAM_SCHEDULER,               FALSE  },
  { VSWUPDM_JOB_TYPE_REMOTE_STREAM_CLEANUP,                 VSWUPDM_SID_NONE,                         VSWUPDM_JOB_PRIO_REMOTE_STREAM_CLEANUP,                 FALSE  },
  { VSWUPDM_JOB_TYPE_INDICATE_WRITE_TO_MODULE,              VSWUPDM_SID_INDICATE_WRITE_TO_MODULE,     VSWUPDM_JOB_PRIO_INDICATE_WRITE_TO_MODULE,              FALSE  }
};

/*! Configuration of module state-dependent startup operation modes for CopyModule data process. */
VSWUPDM_LOCAL CONST(vSwUpdM_ProcessOpSelectType, AUTOMATIC) vSwUpdM_ProcessOpSelect_CopyModule[] =
{
  { VSWUPDM_MODULE_STATE_ERASED,        VSWUPDM_PROC_NODE_OPERATION_START         },
  { VSWUPDM_MODULE_STATE_SYNC_DIRTY,    VSWUPDM_PROC_NODE_OPERATION_DIRTY_RESTART },
  { VSWUPDM_MODULE_STATE_SYNC_CLEAN,    VSWUPDM_PROC_NODE_OPERATION_CLEAN_RESTART },
  { VSWUPDM_MODULE_STATE_SYNC_FINISHED, VSWUPDM_PROC_NODE_OPERATION_NONE          }
};

/*! Configuration for CopyModule data process. */
VSWUPDM_LOCAL CONST(vSwUpdM_ProcessConfigType, AUTOMATIC) vSwUpdM_ProcessConfig_CopyModule =  /* PRQA S 3218 1 */ /* MD_vSwUpdM_Rule8.9_3218_FileScope */
{
  {
    { VSWUPDM_MODULE_STATE_UNDEFINED,     FALSE },
    { VSWUPDM_MODULE_STATE_SYNC_DIRTY,    TRUE  },
    { VSWUPDM_MODULE_STATE_SYNC_FINISHED, FALSE },
  },
  vSwUpdM_ProcessOpSelect_CopyModule,
  VSWUPDM_ARRAY_SIZE(vSwUpdM_ProcessOpSelect_CopyModule)
};

/*! Configuration of module state-dependent startup operation modes for CompareModule data process. */
VSWUPDM_LOCAL CONST(vSwUpdM_ProcessOpSelectType, AUTOMATIC) vSwUpdM_ProcessOpSelect_CompareModule[] =
{
  { VSWUPDM_MODULE_STATE_SYNC_FINISHED,   VSWUPDM_PROC_NODE_OPERATION_START         },
  { VSWUPDM_MODULE_STATE_COMPARE_PENDING, VSWUPDM_PROC_NODE_OPERATION_CLEAN_RESTART },
  { VSWUPDM_MODULE_STATE_VERIFIED,        VSWUPDM_PROC_NODE_OPERATION_NONE          }
};

/*! Configuration of module states forwarded during CompareModule data process. */
VSWUPDM_LOCAL CONST(vSwUpdM_ProcessConfigType, AUTOMATIC) vSwUpdM_ProcessConfig_CompareModule = /* PRQA S 3218 1 */ /* MD_vSwUpdM_Rule8.9_3218_FileScope */
{
  {
    { VSWUPDM_MODULE_STATE_UNDEFINED,       FALSE },
    { VSWUPDM_MODULE_STATE_COMPARE_PENDING, TRUE  },
    { VSWUPDM_MODULE_STATE_VERIFIED,        FALSE },
  },
  vSwUpdM_ProcessOpSelect_CompareModule,
  VSWUPDM_ARRAY_SIZE(vSwUpdM_ProcessOpSelect_CompareModule)
};

#define VSWUPDM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

#define VSWUPDM_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

VAR(vSwUpdM_JobType, VSWUPDM_VAR_NOINIT)            vSwUpdM_Jobs[VSWUPDM_JOB_TYPE_COUNT];
VAR(vSwUpdM_QueueType, VSWUPDM_VAR_NOINIT)          vSwUpdM_JobQueue;
/* PRQA S 3218 1 */ /* MD_vSwUpdM_Rule8.9_3218_FileScope */
VSWUPDM_LOCAL VAR(vSwUpdM_QueueEntryType, VSWUPDM_VAR_NOINIT)     vSwUpdM_JobQueueEntries[VSWUPDM_QUEUE_SIZE(VSWUPDM_JOB_TYPE_COUNT)];

VAR(vSwUpdM_QueueType, VSWUPDM_VAR_NOINIT)          vSwUpdM_SuspendedJobQueue;
/* PRQA S 3218 1 */ /* MD_vSwUpdM_Rule8.9_3218_FileScope */
VSWUPDM_LOCAL VAR(vSwUpdM_QueueEntryType, VSWUPDM_VAR_NOINIT)     vSwUpdM_SuspendedJobQueueEntries[VSWUPDM_QUEUE_SIZE(VSWUPDM_JOB_TYPE_COUNT)];

/* PRQA S 3218 1 */ /* MD_vSwUpdM_Rule8.9_3218_FileScope */
VSWUPDM_LOCAL VAR(vSwUpdM_ExecCtrl_RemoteResumeServiceType, VSWUPDM_VAR_NOINIT) vSwUpdM_ExecCtrl_RemoteResumeService;

#define VSWUPDM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
#define VSWUPDM_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  vSwUpdM_General_ExecuteActiveJob()
 *********************************************************************************************************************/
/*! \brief       Execute active job.
 *  \details     Execute job with highest priority from processing queue.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     general
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_General_ExecuteActiveJob(vSwUpdM_StateType ActiveState);

/**********************************************************************************************************************
 *  vSwUpdM_TranslateErrorCode
 *********************************************************************************************************************/
/*! \brief       Translate a vRpcProxy Error Code into a vSwUpdM value
 *  \details     -
 *
 *  \param[in]   RemoteServiceId
 *  \param[in]   Result
 *  \return      Translated error code.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     remote
 *********************************************************************************************************************/
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_TranslateErrorCode(
  vSwUpdM_GridSrvc_ServiceIdxType RemoteServiceIndex,
  Std_ReturnType Result);

/**********************************************************************************************************************
 *  vSwUpdM_HandleSubscopeOpenSegment
 *********************************************************************************************************************/
/*! \brief       Checks if the subscope attributes 'OpenSegment' is set, if so the segment of the ActiveJob is opened.
 *  \details     -
 *  \param[in]   subScopeAttributes Attributes of the scope
 *  \param[in]   ActiveJob          Currently active job
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     general
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_HandleSubscopeOpenSegment(
  vSwUpdM_SubScopeAttributeType subScopeAttributes,
  vSwUpdM_JobPtrType ActiveJob);

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * vSwUpdM_ExecCtrl_ValidatePartition
 *********************************************************************************************************************/
 /*!
 *
 * Internal comment removed.
 *
 *
 */
Std_ReturnType vSwUpdM_ExecCtrl_ValidatePartition(vSwUpdM_JobPtrType ParentJob)
{
  /* Trigger persisting of all pending partition states. */
  return vSwUpdM_Part_UpdateValid(vSwUpdM_EntityData.OpenIds.PartitionId, vSwUpdM_EntityData.OpenIds.PartitionState, VSWUPDM_VALIDITY_VALID, ParentJob, ParentJob->Source);
}

/**********************************************************************************************************************
 * vSwUpdM_ExecCtrl_InvalidatePartition
 *********************************************************************************************************************/
 /*!
 *
 * Internal comment removed.
 *
 *
 */
Std_ReturnType vSwUpdM_ExecCtrl_InvalidatePartition(vSwUpdM_JobPtrType ParentJob)
{
  /* Trigger persisting of all pending partition states. */
  return vSwUpdM_Part_UpdateValid(vSwUpdM_EntityData.OpenIds.PartitionId, vSwUpdM_EntityData.OpenIds.PartitionState, VSWUPDM_VALIDITY_INVALID, ParentJob, ParentJob->Source);
}

/**********************************************************************************************************************
 * vSwUpdM_ExecCtrl_TriggerRemoteWork
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 */
Std_ReturnType vSwUpdM_ExecCtrl_TriggerRemoteWork(vSwUpdM_JobPtrType ParentJob) /* PRQA S 3673 */ /* MD_vSwUpdM_Rule8.13_3673_PointerToConstParameter */
{
  Std_ReturnType retVal = E_NOT_OK;

  VSWUPDM_DUMMY_STATEMENT(ParentJob);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

#if (VSWUPDM_MULTICONTROLLER_SUPPORT == STD_ON)
  /* #10 If local node is the parent: */
  if (vSwUpdM_Grid_LocalNodeIsParent() == TRUE)
  {
    /* #20 If targets are remote: */
    if (    (vSwUpdM_GetNNodesOfNodeGroup(ParentJob->RemoteTargetGroup) > 1u)
          || (!vSwUpdM_IsWithLocalNodeOfNodeGroup(ParentJob->RemoteTargetGroup)
        )
      )
    {
      /* #30 Transmit request. */
      retVal = vSwUpdM_RemoteService(ParentJob->RemoteServiceIndex, VSWUPDM_EXCTSCHEDULE_SERVICESTATE_RUN, ParentJob->RemoteTargetGroup, ParentJob);

      if(retVal == E_OK)
      {
        /* #40 Store current service for eventual resume. */
        vSwUpdM_ExecCtrl_StoreRemoteResumeService(ParentJob->RemoteServiceIndex, ParentJob->RemoteTargetGroup, VSWUPDM_INVALID_NODE);
      }
    }
    else
    {
      retVal = E_OK;
    }
  }
#endif

  return retVal;
}

/**********************************************************************************************************************
 * vSwUpdM_ExecCtrl_FinalizeModule
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
Std_ReturnType vSwUpdM_ExecCtrl_FinalizeModule(vSwUpdM_JobPtrType ParentJob)
{
  Std_ReturnType retVal;
  vSwUpdM_ModuleIdType  moduleId = ParentJob->EntityIds.ModuleId;

#if (VSWUPDM_MULTICONTROLLER_SUPPORT == STD_ON)
  /* #10 If Module is remote only:
   *     Nothing to do here. */
  if (!vSwUpdM_IsWithLocalNodeOfNodeGroup(vSwUpdM_GetNodeGroupOwnersIdxOfModule(moduleId)))
  {
    retVal = E_OK;
  }
  else
#endif
  {
    /* #20 Else:
     * Trigger finalizing of requested module. */
    retVal = vSwUpdM_Module_FinalizeModule(moduleId, ParentJob->Source, ParentJob);
  }

  return retVal;
}

/**********************************************************************************************************************
 * vSwUpdM_ExecCtrl_SyncModule
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
Std_ReturnType vSwUpdM_ExecCtrl_SyncModule(vSwUpdM_JobPtrType ParentJob)
{
  Std_ReturnType retVal;
  vSwUpdM_ModuleIdType  moduleId = ParentJob->EntityIds.ModuleId;

#if VSWUPDM_MULTICONTROLLER_SUPPORT == STD_ON
  /* #10 If Module is remote only:
   *      Nothing to do here. */
  if (!vSwUpdM_IsWithLocalNodeOfNodeGroup(vSwUpdM_GetNodeGroupOwnersIdxOfModule(ParentJob->EntityIds.ModuleId)))
  {
    retVal = E_OK;
  }
  else
#endif
  /* #100 Else: */
  {
    /* #110 Initialize resume information for SyncModule service. */
    vSwUpdM_ResumeInfo_InitModuleService(moduleId, VSWUPDM_SID_SYNC_MODULE);

    /* #120 Trigger synchronization of given module. */
    retVal = vSwUpdM_Module_SyncModule(moduleId, VSWUPDM_SID_NONE, TRUE, ParentJob->Source, ParentJob);

    /* #130 If spawning of job failed:
      *  Reset resume information. */
    if (retVal != E_OK)
    {
      vSwUpdM_ResumeInfo_ResetState();
    }
  }

  return retVal;
}

/**********************************************************************************************************************
 * vSwUpdM_ExecCtrl_SyncPartition
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
Std_ReturnType vSwUpdM_ExecCtrl_SyncPartition(vSwUpdM_JobPtrType ParentJob)
{
  Std_ReturnType retVal = E_NOT_OK;

  /* #10 If the opened partition isn't the active partition and the opened partition is swappable. */
  if ((vSwUpdM_Part_IsPartitionStateSet(vSwUpdM_EntityData.OpenObjects.Partition->DynamicAttributesOfVarPartitions.State, VSWUPDM_PART_STATE_ACTIVE) == FALSE)
    && (vSwUpdM_EntityData.OpenObjects.Partition->SwappableOfVarPartitions == TRUE))
  {
    vSwUpdM_JobPtrType spawnedJob;

    /* #20 Initialize resume information for SyncPartition service. */
    vSwUpdM_ResumeInfo_InitState(&vSwUpdM_EntityData.OpenIds, VSWUPDM_SID_SYNC_PARTITION, VSWUPDM_UNDEFINED_ADDRESS, FALSE);

    /* #30 Enter critical section to ensure exclusive access of state and job queue. */
    VSWUPDM_ENTER_CRITICAL_SECTION();

    /* #40 Spawn job to synchronize opened partition with active partition. */
    spawnedJob = vSwUpdM_Job_Spawn(&retVal, VSWUPDM_JOB_TYPE_SYNC_PARTITION_LOCAL, VSWUPDM_JOB_OPERATION_DEFAULT, (vSwUpdM_QueuePrioType)VSWUPDM_JOB_PRIO_DEFAULT, VSWUPDM_SID_NONE, ParentJob, ParentJob->Source);

    /* #50 Job attributes are safe to be modified when job was successfully spawned and access is still protected by critical section. */
    if (retVal == E_OK)
    {
      /* #51 Pass open entity IDs to job. */
      spawnedJob->EntityIds = vSwUpdM_EntityData.OpenIds;
    }
    /* #60 If spawning of job failed
      *  Reset resume information. */
    else
    {
      vSwUpdM_ResumeInfo_ResetState();
    }

    /* #70 Leave critical section ensuring exclusive access of state and job queue. */
    VSWUPDM_LEAVE_CRITICAL_SECTION();
  }

  return retVal;
}
/**********************************************************************************************************************
 * vSwUpdM_ExecCtrl_OpenModule
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
Std_ReturnType vSwUpdM_ExecCtrl_OpenModule(vSwUpdM_JobPtrType ParentJob)
{
  vSwUpdM_ModuleIdType  moduleId = ParentJob->EntityIds.ModuleId;

  /* Trigger opening of requested module. */
  return vSwUpdM_Module_OpenModule(moduleId, TRUE, VSWUPDM_SID_NONE, ParentJob->Source, ParentJob);
}

/**********************************************************************************************************************
 * vSwUpdM_ExecCtrl_OpenModuleImplicit
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
Std_ReturnType vSwUpdM_ExecCtrl_OpenModuleImplicit(vSwUpdM_JobPtrType ParentJob)
{
  Std_ReturnType retVal;

  /* #120 If module isn't opened yet. */
  if (vSwUpdM_EntityData.OpenIds.ModuleId == VSWUPDM_INVALID_ID)
  {
    /* #121 Trigger opening of requested module.
      *   Remember that module was opened implicitly. */
    retVal = vSwUpdM_Module_OpenModule(ParentJob->EntityIds.ModuleId, TRUE, VSWUPDM_SID_NONE, ParentJob->Source, ParentJob);
    vSwUpdM_ImplicitModuleOpenFlag = TRUE;
  }
  else
  {
    /* #130 Otherwise: Nothing needed to be done,
      *   Remember that module was not opened implicitly. */
    vSwUpdM_ImplicitModuleOpenFlag = FALSE;
    retVal = E_OK;
  }

  return retVal;
}

/**********************************************************************************************************************
 * vSwUpdM_ExecCtrl_CloseModuleImplicit
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
Std_ReturnType vSwUpdM_ExecCtrl_CloseModuleImplicit(vSwUpdM_JobPtrType ParentJob)
{
  Std_ReturnType retVal;

  /* #110 If modules was opened implicitly by erase request (indicated by job operation). */
  if (vSwUpdM_ImplicitModuleOpenFlag == TRUE)
  {
    /* #111 Trigger closing of requested module. */
    retVal = vSwUpdM_Module_CloseModule(ParentJob->EntityIds.ModuleId, VSWUPDM_SID_NONE, ParentJob->Source, ParentJob);

    /* #112 Reset job operation to default value. */
    vSwUpdM_ImplicitModuleOpenFlag = FALSE;
  }
  /* #120 Otherwise: Indicate that job is finished. */
  else
  {
    retVal = E_OK;
  }

  return retVal;
  /* PRQA S 6030 1 */ /* MD_MSR_STCYC */
}

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

 /**********************************************************************************************************************
 * vSwUpdM_General_ExecuteActiveJob
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
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_General_ExecuteActiveJob(vSwUpdM_StateType ActiveState)
{
  Std_ReturnType          result            = E_OK;  /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vSwUpdM_QueueHandleType activeQueueHandle = vSwUpdM_QueueGetFirstUsedHandle(&vSwUpdM_JobQueue);
  vSwUpdM_JobPtrType      activeJob         = &vSwUpdM_Jobs[vSwUpdM_QueueGetEntityHandle(&vSwUpdM_JobQueue, activeQueueHandle)];
  vSwUpdM_JobStatusType   jobStatus         = VSWUPDM_JOB_STATUS_ACTIVE;
  vSwUpdM_JobPhaseType    jobPhase          = activeJob->Phase;

  /* #10 If pre-hook job phase is active, but no pre-hook is given
   *      Start with main handler execution. */
  if ( (jobPhase == VSWUPDM_JOB_PHASE_PRE_HOOK)
    && (activeJob->PreHookFct == NULL_PTR) )
  {
    jobPhase = VSWUPDM_JOB_PHASE_MAIN_HANDLER;
  }

  /* #100 Verify that job type is valid. */
  if (activeJob->Type < VSWUPDM_JOB_TYPE_COUNT)
  {
    P2CONST(vSwUpdM_BufferInfoType, AUTOMATIC, VSWUPDM_APPL_VAR) inputBuffer = activeJob->InputBuffer;
    /* #110 Processing length defaults to zero. */
    vSwUpdM_LengthType processingLength = 0u;

    /* #120 If operation shall be suspended and job is marked to be immediately suspendable */
    if ( (ActiveState == VSWUPDM_STATE_SUSPENDING) && (activeJob->Suspendable == TRUE) )
    {
      /* #121 If execution of main handler is pending and no child result is present
       *   Skip job execution and report successfully suspended job. */
      if (jobPhase == VSWUPDM_JOB_PHASE_MAIN_HANDLER)
      {
        if ( (activeJob->ChildResult.Valid == FALSE)
          || (activeJob->ChildResult.Result == VSWUPDM_E_SUSPENDED) )
        {
          jobStatus = VSWUPDM_JOB_STATUS_SUSPENDED;
        }
      }
    }

    /* #200 Continue job execution while job reports "active" state.
     *   Reduces number of main function cycles needed for simple state transitions. */
    while (jobStatus == VSWUPDM_JOB_STATUS_ACTIVE)
    {
      /* #201 If input buffer is present, default processing length is set to size of remaining buffer contents. */
      if (inputBuffer != NULL_PTR)
      {
        processingLength = inputBuffer->Used;
      }

      /* #210 Evaluate current job phase */
      switch (jobPhase)
      {
        case VSWUPDM_JOB_PHASE_PRE_HOOK:
        case VSWUPDM_JOB_PHASE_POST_HOOK:
        /* #220 Execute pre-/post-hook function. */
        {
          jobStatus = vSwUpdM_JobHandler_WaitForHookOperation(ActiveState, activeJob, processingLength);
          break;
        }
        case VSWUPDM_JOB_PHASE_EVAL_PRE_HOOK:
        case VSWUPDM_JOB_PHASE_MAIN_HANDLER:
        case VSWUPDM_JOB_PHASE_EVAL_POST_HOOK:
        /* #230 Execution of main handler or evaluation of hook result is requested. */
        {
          /* #231 Limit processing length to segmentation specified for job. */
          vSwUpdM_LengthType segmentation = activeJob->Segmentation;

          if ( (segmentation != VSWUPDM_UNDEFINED_LENGTH)
            && (processingLength > segmentation) )
          {
            processingLength = segmentation;
          }

          /* #232 Execute main handler of job. */
          jobStatus = vSwUpdM_JobHandlers[activeJob->Type](ActiveState, activeJob, processingLength);

          break;
        }
        case VSWUPDM_JOB_PHASE_FINISH:
        default:
        /* #240 Otherwise: Nothing to be done. */
        {
          jobStatus = VSWUPDM_JOB_STATUS_FINISHED;
          break;
        }
      }

      /* #250 Ensure that job is finished in case of error. */
      if (activeJob->Result != E_OK)
      {
        /* #251 Handling dependent on current phase */
        switch (jobPhase)
        {
          case VSWUPDM_JOB_PHASE_MAIN_HANDLER:
          /* #252 Main handler executed: Finish job. */
          {
            jobStatus = VSWUPDM_JOB_STATUS_FINISHED;
            break;
          }
          case VSWUPDM_JOB_PHASE_EVAL_POST_HOOK:
          /* #253 Post-hook executed: Result of post-hook has to be evaluated by main handler.
           *   Only finish job when an invalid state was detected. */
          {
            if (activeJob->Result == VSWUPDM_E_INV_STATE)
            {
              jobStatus = VSWUPDM_JOB_STATUS_FINISHED;
            }

            break;
          }
          default:
          /* #254 Otherwise: Job status remains unchanged. */
          {
            break;
          }
        }
      }

      /* #260 If job is still active. */
      if (jobStatus == VSWUPDM_JOB_STATUS_ACTIVE)
      {
        /* #261 Enter critical section to ensure exclusive access of state and active job (first queue entry). */
        VSWUPDM_ENTER_CRITICAL_SECTION();

        /* #262 If another job with higher priority was spawned meanwhile
         *   Overwrite status to enforce that loop is left. */
        if (vSwUpdM_QueueGetFirstUsedHandle(&vSwUpdM_JobQueue) != activeQueueHandle)
        {
          jobStatus = VSWUPDM_JOB_STATUS_PENDING;
        }

        /* #263 If operation shall be suspended and job is marked to be immediately suspendable
         *   Overwrite status to enforce that loop is left. */
        if ( (ActiveState == VSWUPDM_STATE_SUSPENDING) && (activeJob->Suspendable == TRUE) )
        {
          jobStatus = VSWUPDM_JOB_STATUS_PENDING;
        }

        /* #264 Leave critical section ensuring exclusive access of state and active job (first queue entry). */
        VSWUPDM_LEAVE_CRITICAL_SECTION();
      }
    }

    /* #270 Take over result of job execution. */
    result = activeJob->Result;
  }
  /* #300 Otherwise: Report error. */
  else
  {
    result = E_NOT_OK;
  }

  /* #400 Update processing states based on results of current execution cycle. */
  vSwUpdM_General_ConcludeJobProcessing(activeJob, ActiveState, jobStatus, jobPhase, result);
  /* PRQA S 6010, 6030, 6080 1 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STMIF */
} /* vSwUpdM_General_ExecuteActiveJob */

/**********************************************************************************************************************
 * vSwUpdM_Job_Spawn
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
 */
FUNC(vSwUpdM_JobPtrType, VSWUPDM_CODE) vSwUpdM_Job_Spawn(
  P2VAR(Std_ReturnType, AUTOMATIC, VSWUPDM_APPL_VAR) Result,
  vSwUpdM_JobTypeType JobType,
  vSwUpdM_JobOperationType Operation,
  vSwUpdM_QueuePrioType Priority,
  vSwUpdM_ServiceIdType ConfirmationService,
  vSwUpdM_JobPtrType ParentJob,
  vSwUpdM_NodeIterType Source)
{
  Std_ReturnType          retVal = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vSwUpdM_QueueHandleType queueHandle;
  vSwUpdM_QueuePrioType   queuePrio;

  /* #10 If requested job type is scheduled already
   *   Return busy result. */
  if (vSwUpdM_Jobs[JobType].QueueHandle != (vSwUpdM_QueueHandleType)VSWUPDM_QUEUE_HANDLE_NONE)
  {
    retVal = VSWUPDM_E_BUSY;
  }
  /* #11 Otherwise: */
  else
  {
    /* #12 If job queue isn't full */
    if (!vSwUpdM_QueueIsFull(&vSwUpdM_JobQueue))
    {
      /* #20 If requested, use default priority of job type.
       *     Use passed value otherwise. */
      if (Priority == (vSwUpdM_QueuePrioType)VSWUPDM_JOB_PRIO_DEFAULT)
      {
        queuePrio = vSwUpdM_Jobs[JobType].DefaultPrio;
      }
      else
      {
        queuePrio = Priority;
      }

      /* #30 Insert into processing queue, using priority. */
      queueHandle = vSwUpdM_QueuePrioInsert(&vSwUpdM_JobQueue, queuePrio);
      vSwUpdM_QueueGetEntry(&vSwUpdM_JobQueue, queueHandle).entity = (vSwUpdM_EntityHandleType)JobType;

      /* #40 Initialize queue related job attributes. */
      vSwUpdM_Jobs[JobType].CurrentPrio         = queuePrio;
      vSwUpdM_Jobs[JobType].QueueHandle         = queueHandle;
      /* #41 Initialize job attributes passed in parameters. */
      vSwUpdM_Jobs[JobType].ConfirmationService = ConfirmationService;
      vSwUpdM_Jobs[JobType].Operation           = Operation;
      vSwUpdM_Jobs[JobType].Source              = Source;
      /* #42 Initialize job attributes with default values. */
      vSwUpdM_Job_InitVolatileAttributes(JobType);

      /* #50 When global processing state is idle, change to pending. */
      if (vSwUpdM_GlobalState == VSWUPDM_STATE_IDLE)
      {
        vSwUpdM_GlobalState = VSWUPDM_STATE_PENDING;
      }

      /* #60 Link potential child result of potential parent job. */
      vSwUpdM_Job_LinkParentJobResult(&vSwUpdM_Jobs[JobType], ParentJob);

      retVal = E_OK;
    }
  }

  /* #100 When result pointer was passed, update it with result of operation. */
  if (Result != NULL_PTR)
  {
    *Result = retVal;
  }

  /* #110 When operation failed, update child result of potential parent job. */
  if (retVal != E_OK)
  {
    vSwUpdM_Job_SetChildResult(ParentJob, retVal, VSWUPDM_UNDEFINED_ADDRESS);
  }

  /* #200 Return pointer to job of requested type.
   *   Equals the spawned job object if operation succeeded. */
  return &vSwUpdM_Jobs[JobType];
  /* PRQA S 6060 1 */ /* MD_MSR_STPAR */
} /* vSwUpdM_JobHandler_Spawn */

/**********************************************************************************************************************
 * vSwUpdM_Job_LinkResult
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, VSWUPDM_CODE) vSwUpdM_Job_LinkResult(
  vSwUpdM_JobPtrType Job,
  P2VAR(vSwUpdM_LinkedResultType, AUTOMATIC, VSWUPDM_APPL_VAR) LinkedResult)
{
  Job->LinkedResult     = LinkedResult;
  LinkedResult->Pending = TRUE;
} /* vSwUpdM_JobHandler_LinkResult */

/**********************************************************************************************************************
 * vSwUpdM_Job_ResetLinkedResult
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(void, VSWUPDM_CODE) vSwUpdM_Job_ResetLinkedResult(
  P2VAR(vSwUpdM_LinkedResultType, AUTOMATIC, VSWUPDM_APPL_VAR) LinkedResult)
{
  if (LinkedResult != NULL_PTR)
  {
    LinkedResult->Result        = E_OK;
    LinkedResult->TargetAddress = 0u;
    LinkedResult->Valid         = FALSE;
    LinkedResult->Pending       = FALSE;
  }
} /* vSwUpdM_JobHandler_ResetLinkedResult */

/**********************************************************************************************************************
 * vSwUpdM_Job_SetChildResult
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(void, VSWUPDM_CODE) vSwUpdM_Job_SetChildResult(
  vSwUpdM_JobPtrType Job,
  Std_ReturnType Result,
  vSwUpdM_AddressType TargetAddress)
{
  if (Job != NULL_PTR)
  {
    vSwUpdM_Job_SetLinkedResult(&Job->ChildResult, Result, TargetAddress);
  }
} /* vSwUpdM_JobHandler_SetChildResult */

/**********************************************************************************************************************
 * vSwUpdM_Job_SetChildResultAndConfirm
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, VSWUPDM_CODE) vSwUpdM_Job_SetChildResultAndConfirm(
  vSwUpdM_JobPtrType Job,
  vSwUpdM_NodeIterType Source,
  vSwUpdM_ServiceIdType ConfirmationService,
  Std_ReturnType Result)
{
  vSwUpdM_Job_SetChildResult(Job, Result, VSWUPDM_UNDEFINED_ADDRESS);
  vSwUpdM_UlConfirmation(ConfirmationService, Source, Result);
} /* vSwUpdM_Job_SetChildResultAndConfirm */

/**********************************************************************************************************************
 * vSwUpdM_Job_EvaluateResult
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
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Job_EvaluateResult(
  P2VAR(vSwUpdM_LinkedResultType, AUTOMATIC, VSWUPDM_APPL_VAR) LinkedResult)
{
  Std_ReturnType retVal;

  /* #10 If child result of job is present (marked valid) */
  if (LinkedResult->Valid == TRUE)
  {
    /* #11 Set return value to value of child result of job. */
    retVal = LinkedResult->Result;

    /* #12 If child result is OK, reset child result. */
    if (retVal == E_OK)
    {
      vSwUpdM_Job_ResetLinkedResult(LinkedResult);
    }
  }
  /* #20 Otherwise, if child result is expected (but not valid) */
  else if (LinkedResult->Pending == TRUE)
  {
    /* Set return value and child result value to JOB_INVALID_CHILD_RESULT error. */
    retVal               = VSWUPDM_E_JOB_INVALID_CHILD_RESULT;
    LinkedResult->Result = retVal;
    LinkedResult->Valid  = TRUE;
  }
  /* #30 Otherwise */
  else
  {
    /* #31 No child result present, but none expected either.
     *     Set return value to OK. */
    retVal = E_OK;
  }

  return retVal;
} /* vSwUpdM_Job_EvaluateResult */

/**********************************************************************************************************************
 * vSwUpdM_Job_EvaluateAndApplyChildResult
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 */
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Job_EvaluateAndApplyChildResult(
  vSwUpdM_JobPtrType Job,
  boolean ApplyAddress)
{
  Std_ReturnType retVal;

  /* #10 Evaluate child result from previous cycle.
   *   If not okay, apply child result and set job state to "failed". */
  retVal = vSwUpdM_Job_EvaluateChildResult(Job);

  if (retVal != E_OK)
  {
    vSwUpdM_Job_ApplyChildResult(Job, ApplyAddress);
    Job->State = VSWUPDM_JOB_STATE_FAILED;
  }

  return retVal;
} /* vSwUpdM_Job_EvaluateAndApplyChildResult */

/**********************************************************************************************************************
 * vSwUpdM_Job_EvaluateChildResultOrSuspend
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
 */
VSWUPDM_LOCAL FUNC(vSwUpdM_JobStatusType, VSWUPDM_CODE) vSwUpdM_Job_EvaluateChildResultOrSuspend(
  vSwUpdM_StateType ActiveState,
  vSwUpdM_JobPtrType Job,
  boolean ApplyAddress)
{
  vSwUpdM_JobStatusType retVal = VSWUPDM_JOB_STATUS_PENDING; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  Std_ReturnType result;
  boolean isFail = FALSE;

  /* #10 Evaluate child result from previous cycle. */
  result = vSwUpdM_Job_EvaluateChildResult(Job);

  switch (result)
  {
    case E_OK:
    /* #100 If child has finished with E_OK. */
    {
       /* #130 If suspend of operation is requested indicate that job is suspended. */
      if (ActiveState == VSWUPDM_STATE_SUSPENDING)
      {
        retVal = VSWUPDM_JOB_STATUS_SUSPENDED;
      }
      else /* #140 Otherwise job is still pending. */
      {
        retVal = VSWUPDM_JOB_STATUS_PENDING;
      }
      break;
    }
    case VSWUPDM_E_SUSPENDED:
    /* #200 If child has finished with E_SUSPENDED. */
    {
      /* #210 If suspend of operation is requested and child has suspended. */
      if (ActiveState == VSWUPDM_STATE_SUSPENDING)
      {
        /* #220 Reset result and suspend current job. The child is re-executed after Resume. */
        retVal = VSWUPDM_JOB_STATUS_SUSPENDED;

        Job->ChildResult.Pending = TRUE;
        Job->ChildResult.Valid = FALSE;
      }
      else
      {
        /* #230 If no suspend requested, but child has suspended: Invalid state reached, set Fail flag. */
        isFail = TRUE;
      }
      break;
    }
    default:
    /* #300 Otherwise: Child reports error, set Fail flag. */
    {
      isFail = TRUE;
      break;
    }
  }

  /* #400 If Fail flag is set, apply child result and set job state to "failed". */
  if (isFail == TRUE)
  {
    vSwUpdM_Job_ApplyChildResult(Job, ApplyAddress);

    Job->State = VSWUPDM_JOB_STATE_FAILED;
  }

  return retVal;
} /* vSwUpdM_Job_EvaluateChildResultOrSuspend */

/**********************************************************************************************************************
 * vSwUpdM_Job_PrepareWriteOperation
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
 */
VSWUPDM_LOCAL FUNC(void, VSWUPDM_CODE) vSwUpdM_Job_PrepareWriteOperation(
  vSwUpdM_JobPtrType Job,
  vSwUpdM_VarSegmentsPtrType Segment,
  boolean UpdateEntityStates)
{
  if (UpdateEntityStates == TRUE)
  {
    /* #10 Change state of opened module and region in which given segment is located to "dirty". */
    (void)vSwUpdM_Region_UpdateAndPersistState(Job->EntityIds.PartitionId, Job->EntityIds.ModuleId, Segment->RegionIdxOfVarSegments, VSWUPDM_REGION_STATE_DIRTY, Job, Job->Source);
    /* #20 Change state of given segment to "pending". */
    (void)vSwUpdM_Segment_UpdateAndPersistState(Job->EntityIds.SegmentId, VSWUPDM_SEGMENT_STATE_PENDING, Job->Source, Job);
  }

  /* #30 If resume info shall be updated by job */
  if (Job->UpdateResumeInfo == TRUE)
  {
    vSwUpdM_ServiceIdType initialService = vSwUpdM_ResumeInfo.ResumeInfo.CurrentService;
    /* #40 If fine-grained resume is enabled */
#if (VSWUPDM_FINE_GRAINED_RESUME == STD_ON)
    vSwUpdM_AddressType   apparentWriteAddress;

    /* #41 Update and persist resume information for next checkpoint after current (apparent) write address. */
    vSwUpdM_Segment_GetApparentWriteAddress(Segment, &apparentWriteAddress);
    (void)vSwUpdM_ResumeInfo_PersistForNextCheckpoint(Job->EntityIds.PartitionId, Job->EntityIds.PartitionState, Job->EntityIds.SegmentId.DynamicSegmentId, apparentWriteAddress, FALSE, Job->Source);
#else
    vSwUpdM_SegmentIdType segmentId;

    /* #50 Update resume information to indicate that service is active,
     *   using ProcessStreamData as service and start address of the very first dynamic segment.
     *   Force persisting of resume information. */
    if (vSwUpdM_GetSegmentIdOfModuleByIndex(&segmentId, Job->EntityIds.ModuleId, 0u) == E_OK)
    {
      (void)vSwUpdM_ResumeInfo_UpdateAndPersistState(Job->EntityIds.PartitionState, VSWUPDM_SID_PROCESS_STREAM_DATA, VSWUPDM_RESUME_STATE_ACTIVE, vSwUpdM_GetVarSegments(segmentId.DynamicSegmentId).DynamicAttributesOfVarSegment.StartAddress, vSwUpdM_GetVarSegments(segmentId.DynamicSegmentId).DynamicAttributesOfVarSegment.StartAddress, Segment->WriteAddressOfVarSegments, TRUE, Job->Source);
    }
    else
    {
      (void)vSwUpdM_ResumeInfo_UpdateAndPersistState(Job->EntityIds.PartitionState, vSwUpdM_ResumeInfo.ResumeInfo.CurrentService, VSWUPDM_RESUME_STATE_ACTIVE, VSWUPDM_UNDEFINED_ADDRESS, VSWUPDM_UNDEFINED_ADDRESS, VSWUPDM_UNDEFINED_ADDRESS, FALSE, Job->Source);
    }
#endif

    /* #60 Update resume information to indicate that service is active,
     *   using apparent write address of the given segment. */
    vSwUpdM_ResumeInfo_UpdateWriteService(Job->EntityIds.PartitionState, Segment, initialService);
  }
} /* vSwUpdM_Job_PrepareWriteOperation */

/**********************************************************************************************************************
 * vSwUpdM_Init_SetupJobs
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
 */
FUNC(void, VSWUPDM_CODE) vSwUpdM_Init_SetupJobs(void)
{
  vSwUpdM_EntityHandleType jobIndex;

  /* #10 Setup queues for pending and suspended jobs. */
  vSwUpdM_QueueInit(&vSwUpdM_JobQueue, vSwUpdM_JobQueueEntries, VSWUPDM_ARRAY_SIZE(vSwUpdM_JobQueueEntries), VSWUPDM_QUEUE_PRIO_ORDER_DESC, VSWUPDM_QUEUE_ENTITY_HANDLE_NONE, 0);
  vSwUpdM_QueueInit(&vSwUpdM_SuspendedJobQueue, vSwUpdM_SuspendedJobQueueEntries, VSWUPDM_ARRAY_SIZE(vSwUpdM_SuspendedJobQueueEntries), VSWUPDM_QUEUE_PRIO_ORDER_DESC, VSWUPDM_QUEUE_ENTITY_HANDLE_NONE, 0);

  /* #20 For all job objects */
  for (jobIndex = 0u; jobIndex < VSWUPDM_ARRAY_SIZE(vSwUpdM_Jobs); jobIndex++)
  {
    /* #30 Evaluate service ID. */
    vSwUpdM_ServiceIdType serviceId = vSwUpdM_JobDefinitions[jobIndex].ServiceId;

    /* #40 Initialize job object with default values. */
    vSwUpdM_Job_Init(vSwUpdM_JobDefinitions[jobIndex].JobType, serviceId, (vSwUpdM_QueuePrioType)vSwUpdM_JobDefinitions[jobIndex].Priority, vSwUpdM_JobDefinitions[jobIndex].Suspendable);

    /* #50 If job is assigned to an API service */
    if (serviceId != VSWUPDM_SID_NONE)
    {
      vSwUpdM_PreServiceHooksIterType   preHookIndex;
      vSwUpdM_PostServiceHooksIterType  postHookIndex;

      /* #60 Iterate over all configured service pre-hooks. */
      for (preHookIndex = 0u; preHookIndex < vSwUpdM_GetSizeOfPreServiceHooks(); preHookIndex++)
      {
        /* #61 If configured service ID of hook matches the service ID assigned to the job */
        if (vSwUpdM_GetServiceIdOfPreServiceHooks(preHookIndex) == serviceId)
        {
          /* #62 Assign service pre-hook to job and finish search. */
          vSwUpdM_Jobs[jobIndex].PreHookFct = vSwUpdM_GetFuncPtrOfPreServiceHooks(preHookIndex);

          break;
        }
      }

      /* #70 Iterate over all configured service post-hooks. */
      for (postHookIndex = 0u; postHookIndex < vSwUpdM_GetSizeOfPostServiceHooks(); postHookIndex++)
      {
        /* #71 If configured service ID of hook matches the service ID assigned to the job */
        if (vSwUpdM_GetServiceIdOfPostServiceHooks(postHookIndex) == serviceId)
        {
          /* #72 Assign service pre-hook to job and finish search. */
          vSwUpdM_Jobs[jobIndex].PostHookFct = vSwUpdM_GetFuncPtrOfPostServiceHooks(postHookIndex);

          break;
        }
      }
    }
  }

  /* #100 Set non-default attributes of specific jobs. */
  vSwUpdM_Jobs[VSWUPDM_JOB_TYPE_PROCESS_STREAM_DATA].Segmentation = vSwUpdM_GetDefaultProcessingSegmentation();
  vSwUpdM_Jobs[VSWUPDM_JOB_TYPE_PROCESS_STREAM_DATA].InputBuffer  = &vSwUpdM_BufferInfoProcessInputStream;

  vSwUpdM_Jobs[VSWUPDM_JOB_TYPE_REMOTE_PROCESS_STREAM_DATA].Segmentation = vSwUpdM_GetMaxInputStreamSize();
  vSwUpdM_Jobs[VSWUPDM_JOB_TYPE_REMOTE_PROCESS_STREAM_DATA].InputBuffer  = &vSwUpdM_BufferInfoWriteData;

  vSwUpdM_Jobs[VSWUPDM_JOB_TYPE_FILL_MEMORY].Segmentation         = vSwUpdM_GetDefaultProcessingSegmentation();
  vSwUpdM_Jobs[VSWUPDM_JOB_TYPE_FILL_MEMORY].InputBuffer          = &vSwUpdM_BufferInfoCopyMemory;
  vSwUpdM_Jobs[VSWUPDM_JOB_TYPE_FILL_MEMORY].OutputBuffer         = &vSwUpdM_BufferInfoWriteData;

  vSwUpdM_Jobs[VSWUPDM_JOB_TYPE_READ_DATA].Segmentation           = vSwUpdM_GetDefaultProcessingSegmentation();
  vSwUpdM_Jobs[VSWUPDM_JOB_TYPE_READ_DATA].InputBuffer            = &vSwUpdM_BufferInfoReadData;
  vSwUpdM_Jobs[VSWUPDM_JOB_TYPE_READ_DATA].OutputBuffer           = &vSwUpdM_BufferInfoWriteData;

  vSwUpdM_Jobs[VSWUPDM_JOB_TYPE_WRITE_DATA].Segmentation          = vSwUpdM_GetDefaultProcessingSegmentation();
  vSwUpdM_Jobs[VSWUPDM_JOB_TYPE_WRITE_DATA].InputBuffer           = &vSwUpdM_BufferInfoWriteData;

  vSwUpdM_Jobs[VSWUPDM_JOB_TYPE_ERASE_RANGE].InputBuffer          = &vSwUpdM_BufferInfoEraseRange;

  /* #110 Initialize RemoteResumeService. */
  vSwUpdM_ExecCtrl_RemoteResumeService.IsValid = FALSE;
} /* vSwUpdM_Init_SetupJobs */

/**********************************************************************************************************************
 *  vSwUpdM_Job_HandleDefaultRetry
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
VSWUPDM_LOCAL FUNC(vSwUpdM_JobStatusType, VSWUPDM_CODE) vSwUpdM_Job_HandleDefaultRetry(vSwUpdM_JobPtrType ActiveJob)
{
  vSwUpdM_JobStatusType retVal  = VSWUPDM_JOB_STATUS_FINISHED;
  boolean               allowed = FALSE;

  /* #10 Verify whether requested hook operation is applicable. */
  switch (ActiveJob->HookAction)
  {
    case VSWUPDM_HOOK_ACTION_RETRY:
    case VSWUPDM_HOOK_ACTION_RESTART:
    /* #20 If retry or restart action is requested */
    {
      /* #30 Verify requested retry granularity. */
      switch (ActiveJob->RetryGranularity)
      {
        case VSWUPDM_RETRY_GRANULARITY_DEFAULT:
        /* #31 Default granularity is allowed. */
        {
          allowed = TRUE;

          /* #32 If retry is requested
           *   Overwrite result with positive return code. */
          if (ActiveJob->HookAction == VSWUPDM_HOOK_ACTION_RETRY)
          {
            ActiveJob->Result = E_OK;
          }

          break;
        }
        default:
        /* #40 Otherwise: Unsupported retry granularity. */
        {
          break;
        }
      }

      break;
    }
    default:
    /* #50 Otherwise: Unsupported hook action. */
    {
      break;
    }
  }

  /* #60 If requested hook isn't allowed
   *   Overwrite result with "unsupported hook action" error. */
  if (allowed != TRUE)
  {
    ActiveJob->Result = VSWUPDM_E_HOOK_UNSUPPORTED_ACTION;
  }

  /* #70 Indicate that job is finished. */
  return retVal;
}

/**********************************************************************************************************************
 *  vSwUpdM_Job_HandleWriteRetry
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
VSWUPDM_LOCAL FUNC(vSwUpdM_JobStatusType, VSWUPDM_CODE) vSwUpdM_Job_HandleWriteRetry(
  vSwUpdM_JobPtrType ActiveJob,
  vSwUpdM_ServiceIdType ResumeService)
{
  vSwUpdM_JobStatusType       retVal = VSWUPDM_JOB_STATUS_FINISHED;
  vSwUpdM_AddressType         writeAddress = vSwUpdM_GetVarSegments(ActiveJob->EntityIds.SegmentId.DynamicSegmentId).WriteAddressOfVarSegments;
  vSwUpdM_AddressType         streamAddress;
  vSwUpdM_VarSegmentsPtrType  segment; /* PRQA S 3679 */ /* MD_vSwUpdM_Rule8.13_3679_PointerToModifiableData */

  boolean allowed = FALSE;

  /* #10 Calculate stream address for given segment. */
  segment = vSwUpdM_GetAddrVarSegments(ActiveJob->EntityIds.SegmentId.DynamicSegmentId);
  (void)vSwUpdM_ResumeInfo_CalculateStreamAddress(segment, writeAddress, &streamAddress);

  /* #20 Evaluate action requested by hook function. */
  switch (ActiveJob->HookAction)
  {
    case VSWUPDM_HOOK_ACTION_RETRY:
    /* #100 If a retry is requested */
    {
      /* #110 Evaluate retry granularity requested by hook function. */
      switch (ActiveJob->RetryGranularity)
      {
        case VSWUPDM_RETRY_GRANULARITY_DEFAULT:
        /* #120 If default granularity is requested */
        {
          /* #121 Hook request is allowed. Overwrite job result with positive return code. */
          allowed           = TRUE;
          ActiveJob->Result = E_OK;

          /* #122 Update resume information: Set state to "active" and resume address to write address of currently opened segment.
           *   Do not force persisting of resume information. */
          vSwUpdM_ResumeInfo_UpdateState(ActiveJob->EntityIds.PartitionState, ResumeService, VSWUPDM_RESUME_STATE_ACTIVE, writeAddress, streamAddress, writeAddress, TRUE);

          break;
        }
        default:
        /* #130 Otherwise: Unsupported retry granularity. */
        {
          break;
        }
      }

      break;
    }
    case VSWUPDM_HOOK_ACTION_RESTART:
    /* #200 If a restart is requested */
    {
      /* #210 Evaluate retry granularity requested by hook function. */
      switch (ActiveJob->RetryGranularity)
      {
        case VSWUPDM_RETRY_GRANULARITY_DEFAULT:
        /* #220 If default granularity is requested */
        {
          vSwUpdM_AddressType     endAddress      = vSwUpdM_GetVarSegments(ActiveJob->EntityIds.SegmentId.DynamicSegmentId).EndAddressOfVarSegments;
          vSwUpdM_ResumeStateType resumeState     = VSWUPDM_RESUME_STATE_ACTIVE;
          vSwUpdM_AddressType     reportedAddress = writeAddress;

          /* #221 Hook request is allowed. Do not overwrite negative job result. */
          allowed = TRUE;

          /* #222 If current write address lies behind end of segment
           *   Set state to "pending" and resume address to end address of segment. */
          if (writeAddress > endAddress)
          {
            resumeState = VSWUPDM_RESUME_STATE_PENDING;
            reportedAddress = endAddress;
          }
          /* #223 Otherwise:
           *  Set state to "active" and resume address to write address. */

          /* #224 Set state of module instance to "dirty". */
          (void)vSwUpdM_Module_UpdateAndPersistState(ActiveJob->EntityIds.PartitionId, ActiveJob->EntityIds.PartitionState, ActiveJob->EntityIds.ModuleId, VSWUPDM_MODULE_STATE_DIRTY, ActiveJob, ActiveJob->Source);

          /* #225 Update resume information. */
          vSwUpdM_ResumeInfo_UpdateState(ActiveJob->EntityIds.PartitionState, ResumeService, resumeState, reportedAddress, streamAddress, reportedAddress, TRUE);

          /* #226 Advance job state to wait for persisting of module state. */
          ActiveJob->State = VSWUPDM_JOB_STATE_FINAL;
          retVal           = VSWUPDM_JOB_STATUS_PENDING;

          break;
        }
        case VSWUPDM_RETRY_GRANULARITY_MODULE:
        /* #230 If module granularity is requested */
        {
          vSwUpdM_SegmentIdType segmentId;

          /* #231 Hook request is allowed. Do not overwrite negative job result. */
          allowed = TRUE;

          /* #232 Set state of module instance to "restart" to trigger implicit erase on next power-cycle. */
          (void)vSwUpdM_Module_UpdateAndPersistState(ActiveJob->EntityIds.PartitionId, ActiveJob->EntityIds.PartitionState, ActiveJob->EntityIds.ModuleId, VSWUPDM_MODULE_STATE_RESTART, ActiveJob, ActiveJob->Source);

          /* #233 Update resume information: Set state to "active" and resume address to start address of the very first segment. */
          (void)vSwUpdM_GetSegmentIdOfModuleByIndex(&segmentId, ActiveJob->EntityIds.ModuleId, 0u);
          writeAddress = vSwUpdM_GetVarSegments(segmentId.DynamicSegmentId).DynamicAttributesOfVarSegment.StartAddress;

          vSwUpdM_ResumeInfo_UpdateState(ActiveJob->EntityIds.PartitionState, ResumeService, VSWUPDM_RESUME_STATE_ACTIVE, writeAddress, streamAddress, writeAddress, TRUE);

          /* #234 Advance job state to wait for persisting of module state. */
          ActiveJob->State = VSWUPDM_JOB_STATE_FINAL;
          retVal           = VSWUPDM_JOB_STATUS_PENDING;

          break;
        }
        default:
        /* #240 Otherwise: Unsupported retry granularity. */
        {
          break;
        }
      }

      break;
    }
    default:
    /* #300 Otherwise: Unsupported hook action. */
    {
      break;
    }
  }

  /* #400 If hook request isn't allowed, set job result to "unsupported hook action". */
  if (allowed != TRUE)
  {
    ActiveJob->Result = VSWUPDM_E_HOOK_UNSUPPORTED_ACTION;
  }

  return retVal;
} /* vSwUpdM_Job_HandleWriteRetry */

/**********************************************************************************************************************
 * vSwUpdM_HandleSubscopeOpenSegment
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_HandleSubscopeOpenSegment(
  vSwUpdM_SubScopeAttributeType subScopeAttributes,
  vSwUpdM_JobPtrType ActiveJob)
{
  /* PRQA S 3679 1 */ /* MD_vSwUpdM_Rule8.13_3679_PointerToModifiableData */
  vSwUpdM_VarSegmentsPtrType      segment = vSwUpdM_GetAddrVarSegments(ActiveJob->EntityIds.SegmentId.DynamicSegmentId);

  /* #10 Check if subscope is set to open segment. */
  if ( (vSwUpdM_Pipe_IsSubScopeAttributeSet(subScopeAttributes, VSWUPDM_SUB_SCOPE_ATTRIBUTE_OPEN_SEGMENT) == TRUE))
  {
    /* #20 Trigger opening of current segment. */
    (void)vSwUpdM_Segment_OpenSegment(ActiveJob->EntityIds.SegmentId, VSWUPDM_SID_NONE, ActiveJob, ActiveJob->Source);

    /* #30 Update the states of all entities affected by upcoming write operation. */
    vSwUpdM_Job_PrepareWriteOperation(ActiveJob, segment, TRUE);
  }
} /* vSwUpdM_HandleSubscopeOpenSegment */

#if (VSWUPDM_MULTICONTROLLER_SUPPORT == STD_ON)
/**********************************************************************************************************************
 * vSwUpdM_RemoteWaitForResponsesGroup
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
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_RemoteWaitForResponsesGroup(
  vSwUpdM_JobTypeType JobType,
  vSwUpdM_NodeGroupIterType SourceGroupIndex,
  vSwUpdM_GridSrvc_ServiceIdxType RemoteServiceIndex,
  vSwUpdM_JobPtrType ParentJob)
{
  Std_ReturnType retVal;
  vSwUpdM_JobPtrType spawnedJob;

  /* #10 Enter critical section to ensure exclusive access of job queue. */
  VSWUPDM_ENTER_CRITICAL_SECTION();

  /* #20 Spawn job to aggregate responses from a group of remote nodes. */
  spawnedJob = vSwUpdM_Job_Spawn(&retVal, JobType, VSWUPDM_JOB_OPERATION_DEFAULT, (vSwUpdM_QueuePrioType)VSWUPDM_JOB_PRIO_DEFAULT,  VSWUPDM_SID_NONE, ParentJob, ParentJob->Source);
    /* #30 Job attributes are safe to be modified when job was successfully spawned and access is still protected by critical section. */
  if (retVal == E_OK)
  {
    spawnedJob->RemoteTargetGroup  = SourceGroupIndex;
    spawnedJob->RemoteTarget       = VSWUPDM_INVALID_NODE;
    spawnedJob->RemoteServiceIndex = RemoteServiceIndex;
  }

  /* #40 Leave critical section to ensure exclusive access of job queue. */
  VSWUPDM_LEAVE_CRITICAL_SECTION();

  return retVal;
} /* vSwUpdM_RemoteWaitForResponsesGroup */

/**********************************************************************************************************************
 * vSwUpdM_TranslateErrorCode
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 */

VSWUPDM_LOCAL_INLINE FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_TranslateErrorCode(
  vSwUpdM_GridSrvc_ServiceIdxType RemoteServiceIndex,
  Std_ReturnType Result)
{
  Std_ReturnType result = VSWUPDM_E_INV_STATE;

  uint32_least index;

  index = 0u;
  do
  {
    if (vSwUpdM_RemoteServiceDefinitions[index].RemoteServiceIndex == RemoteServiceIndex)
    {
      if (vSwUpdM_RemoteServiceDefinitions[index].ErrorCode != VSWUPDM_E_NO_ERROR)
      {
        /* Overwrite error with REMOTE_<...>_FAILED error code to differentiate between remote and local errors. */
        result = vSwUpdM_RemoteServiceDefinitions[index].ErrorCode;
      }
      else
      {
        result = Result;
      }
      break;
    }
    index++;
  } while (vSwUpdM_RemoteServiceDefinitions[index].RemoteServiceIndex != VSWUPDM_GRIDSRVC_SERVICEIDX_UNDEFINED);

  return result;
} /* vSwUpdM_TranslateErrorCode */

/**********************************************************************************************************************
 * vSwUpdM_RemoteService
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 */

VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_RemoteService(
  vSwUpdM_GridSrvc_ServiceIdxType ServiceIndex,
  vSwUpdM_ExctSchedule_ServiceStateType ServiceState,
  vSwUpdM_NodeGroupIterType TargetGroup,
  vSwUpdM_JobPtrType ParentJob)
{
  Std_ReturnType retVal = E_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vSwUpdM_GridSrvc_ServiceClassBasePtrType param = NULL_PTR;

  vSwUpdM_GridSrvc_Register(ServiceIndex, &param);
  switch (ServiceIndex)
  {
    case VSWUPDM_GRIDSRVC_SERVICEIDX_SHUTDOWN:
    {
      vSwUpdM_Grid_InitServiceClassMaintenance(ServiceState, ServiceIndex, (vSwUpdM_GridSrvc_ServiceClassMaintenancePtrType) param);  /* PRQA S 0310 */ /* MD_vSwUpdM_Rule11.3_0310_ServiceParameterCast */
      break;
    }
    case VSWUPDM_GRIDSRVC_SERVICEIDX_SUSPEND:
    case VSWUPDM_GRIDSRVC_SERVICEIDX_RESUME:
    {
      vSwUpdM_Grid_InitServiceClassSuspend(ServiceIndex, (vSwUpdM_GridSrvc_ServiceClassSuspendPtrType) param);  /* PRQA S 0310 */ /* MD_vSwUpdM_Rule11.3_0310_ServiceParameterCast */
      break;
    }
    case VSWUPDM_GRIDSRVC_SERVICEIDX_OPEN_PARTITION:
    {
      vSwUpdM_Grid_InitServiceClassPartition(ServiceState, ServiceIndex, ParentJob->EntityIds.PartitionState, (vSwUpdM_GridSrvc_ServiceClassPartitionPtrType) param);  /* PRQA S 0310 */ /* MD_vSwUpdM_Rule11.3_0310_ServiceParameterCast */
      break;
    }
    case VSWUPDM_GRIDSRVC_SERVICEIDX_START:
    case VSWUPDM_GRIDSRVC_SERVICEIDX_CHECK_PARTITION:
    case VSWUPDM_GRIDSRVC_SERVICEIDX_SET_PARTITION_VALID:
    case VSWUPDM_GRIDSRVC_SERVICEIDX_SET_PARTITION_INVALID:
    case VSWUPDM_GRIDSRVC_SERVICEIDX_SYNC_PARTITION:
    case VSWUPDM_GRIDSRVC_SERVICEIDX_SWAP_PARTITION:
    case VSWUPDM_GRIDSRVC_SERVICEIDX_END_STREAM:
    {
      vSwUpdM_Grid_InitServiceClassGeneric(ServiceState, ServiceIndex, (vSwUpdM_GridSrvc_ServiceClassGenericPtrType) param);  /* PRQA S 0310 */ /* MD_vSwUpdM_Rule11.3_0310_ServiceParameterCast */
      break;
    }
    case VSWUPDM_GRIDSRVC_SERVICEIDX_OPEN_MODULE:
    case VSWUPDM_GRIDSRVC_SERVICEIDX_CLOSE_MODULE:
    case VSWUPDM_GRIDSRVC_SERVICEIDX_ERASE_MODULE:
    case VSWUPDM_GRIDSRVC_SERVICEIDX_FINALIZE_MODULE:
    case VSWUPDM_GRIDSRVC_SERVICEIDX_SYNC_MODULE:
    case VSWUPDM_GRIDSRVC_SERVICEIDX_VALIDATE_MODULE:
    case VSWUPDM_GRIDSRVC_SERVICEIDX_INVALIDATE_MODULE:
    case VSWUPDM_GRIDSRVC_SERVICEIDX_CLEAR_SEGMENTS_OF_MODULE:
    case VSWUPDM_GRIDSRVC_SERVICEIDX_INDICATE_WRITE_TO_MODULE:
    {
      vSwUpdM_Grid_InitServiceClassModule(ServiceState, ServiceIndex, ParentJob->EntityIds.ModuleId, (vSwUpdM_GridSrvc_ServiceClassModulePtrType) param);  /* PRQA S 0310 */ /* MD_vSwUpdM_Rule11.3_0310_ServiceParameterCast */
      break;
    }
    case VSWUPDM_GRIDSRVC_SERVICEIDX_ERASE_REGION:
    {
      vSwUpdM_Grid_InitServiceClassRegion(ServiceState, ServiceIndex, ParentJob->EntityIds.RegionId, (vSwUpdM_GridSrvc_ServiceClassRegionPtrType) param);  /* PRQA S 0310 */ /* MD_vSwUpdM_Rule11.3_0310_ServiceParameterCast */
      break;
    }

    case VSWUPDM_GRIDSRVC_SERVICEIDX_OPEN_SEGMENT:
    case VSWUPDM_GRIDSRVC_SERVICEIDX_CLOSE_SEGMENT:
    case VSWUPDM_GRIDSRVC_SERVICEIDX_FINALIZE_SEGMENT:
    {
      vSwUpdM_Grid_InitServiceClassSegment(ServiceState, ServiceIndex, ParentJob->EntityIds.SegmentId, (vSwUpdM_GridSrvc_ServiceClassSegmentPtrType) param);  /* PRQA S 0310 */ /* MD_vSwUpdM_Rule11.3_0310_ServiceParameterCast */
      break;
    }
    case VSWUPDM_GRIDSRVC_SERVICEIDX_VERIFY_MODULE:
    case VSWUPDM_GRIDSRVC_SERVICEIDX_PROCESS_MODULE:
    {
      vSwUpdM_Grid_InitServiceClassProcessModule(ServiceState, ServiceIndex, ParentJob->EntityIds.ModuleId, (vSwUpdM_ProcessIdType)vSwUpdM_ProcessData.ProcessId, &vSwUpdM_ProcessUserData, (vSwUpdM_GridSrvc_ServiceClassProcessModulePtrType) param);  /* PRQA S 0310 */ /* MD_vSwUpdM_Rule11.3_0310_ServiceParameterCast */
      break;
    }
    case VSWUPDM_GRIDSRVC_SERVICEIDX_START_STREAM:
    {
      vSwUpdM_StreamInfoType streamInfo;

      streamInfo.InputLength = vSwUpdM_StreamData.MaxLength;
      streamInfo.Operation   = vSwUpdM_StreamData.Operation;

      vSwUpdM_Grid_InitServiceClassStreamInfo(ServiceState, &streamInfo, (vSwUpdM_GridSrvc_ServiceClassStreamInfoPtrType) param);  /* PRQA S 0310 */ /* MD_vSwUpdM_Rule11.3_0310_ServiceParameterCast */
      break;
    }
    case VSWUPDM_GRIDSRVC_SERVICEIDX_ADD_SEGMENT:
    {
      P2CONST(vSwUpdM_VarSegmentsType, AUTOMATIC, VSWUPDM_APPL_VAR) segment = vSwUpdM_GetAddrVarSegments(ParentJob->EntityIds.SegmentId.DynamicSegmentId);
      vSwUpdM_RemoteSegmentInfoType segmentInfo;

      segmentInfo.StartAddress   = segment->DynamicAttributesOfVarSegment.StartAddress;
      segmentInfo.InitialLength  = segment->DynamicAttributesOfVarSegment.InitialLength;
      segmentInfo.LengthHandling = segment->DynamicAttributesOfVarSegment.LengthHandling;
      segmentInfo.State          = segment->DynamicAttributesOfVarSegment.State;
      segmentInfo.Type           = segment->TypeOfVarSegments;
      segmentInfo.IsOverflowable = segment->IsOverflowableOfVarSegments;

      vSwUpdM_Grid_InitServiceClassSegmentInfo(ServiceState, &segmentInfo, (vSwUpdM_GridSrvc_ServiceClassSegmentInfoPtrType) param);  /* PRQA S 0310 */ /* MD_vSwUpdM_Rule11.3_0310_ServiceParameterCast */
      break;
    }
    default:
    {
      retVal = E_NOT_OK;
      break;
    }
  }

  if (retVal == E_OK)
  {
    retVal = vSwUpdM_GridSrvc_Start(TargetGroup, ServiceIndex);
  }

  /* #20 Spawn job to wait for response. */
  if (retVal == E_OK)
  {
    switch (ServiceIndex)
    {
      case VSWUPDM_GRIDSRVC_SERVICEIDX_ADD_SEGMENT:
      case VSWUPDM_GRIDSRVC_SERVICEIDX_CHECK_PARTITION:
      case VSWUPDM_GRIDSRVC_SERVICEIDX_CLEAR_SEGMENTS_OF_MODULE:
      case VSWUPDM_GRIDSRVC_SERVICEIDX_CLOSE_MODULE:
      case VSWUPDM_GRIDSRVC_SERVICEIDX_CLOSE_SEGMENT:
      case VSWUPDM_GRIDSRVC_SERVICEIDX_END_STREAM:
      case VSWUPDM_GRIDSRVC_SERVICEIDX_ERASE_MODULE:
      case VSWUPDM_GRIDSRVC_SERVICEIDX_ERASE_REGION:
      case VSWUPDM_GRIDSRVC_SERVICEIDX_FINALIZE_MODULE:
      case VSWUPDM_GRIDSRVC_SERVICEIDX_FINALIZE_SEGMENT:
      case VSWUPDM_GRIDSRVC_SERVICEIDX_INDICATE_WRITE_TO_MODULE:
      case VSWUPDM_GRIDSRVC_SERVICEIDX_INVALIDATE_MODULE:
      case VSWUPDM_GRIDSRVC_SERVICEIDX_OPEN_MODULE:
      case VSWUPDM_GRIDSRVC_SERVICEIDX_OPEN_PARTITION:
      case VSWUPDM_GRIDSRVC_SERVICEIDX_OPEN_SEGMENT:
      case VSWUPDM_GRIDSRVC_SERVICEIDX_SET_PARTITION_INVALID:
      case VSWUPDM_GRIDSRVC_SERVICEIDX_SET_PARTITION_VALID:
      case VSWUPDM_GRIDSRVC_SERVICEIDX_START:
      case VSWUPDM_GRIDSRVC_SERVICEIDX_START_STREAM:
      case VSWUPDM_GRIDSRVC_SERVICEIDX_SWAP_PARTITION:
      case VSWUPDM_GRIDSRVC_SERVICEIDX_SYNC_MODULE:
      case VSWUPDM_GRIDSRVC_SERVICEIDX_VALIDATE_MODULE:
      case VSWUPDM_GRIDSRVC_SERVICEIDX_VERIFY_MODULE:
      case VSWUPDM_GRIDSRVC_SERVICEIDX_PROCESS_MODULE:
      case VSWUPDM_GRIDSRVC_SERVICEIDX_SYNC_PARTITION:
      {
        retVal = vSwUpdM_RemoteWaitForResponsesGroup(VSWUPDM_JOB_TYPE_REMOTE_GROUP_CONFIRMATION, TargetGroup, ServiceIndex, ParentJob);
        break;
      }
      case VSWUPDM_GRIDSRVC_SERVICEIDX_RESUME:
      {
        retVal = vSwUpdM_RemoteWaitForResponsesGroup(VSWUPDM_JOB_TYPE_REMOTE_RESUME_CONFIRMATION, TargetGroup, ServiceIndex, ParentJob);
        break;
      }
      case VSWUPDM_GRIDSRVC_SERVICEIDX_SUSPEND:
      {
        retVal = vSwUpdM_RemoteWaitForResponsesGroup(VSWUPDM_JOB_TYPE_REMOTE_SUSPEND_CONFIRMATION, TargetGroup, ServiceIndex, ParentJob);
        break;
      }
      default:
      {
        retVal = VSWUPDM_E_INV_STATE;
        break;
      }
    }
  }

  return retVal;
} /* vSwUpdM_RemoteService */ /* PRQA S 6010, 6030, 6050, 6080 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */

/**********************************************************************************************************************
 * vSwUpdM_ExecCtrl_StoreRemoteResumeService
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */

VSWUPDM_LOCAL FUNC(void, VSWUPDM_CODE) vSwUpdM_ExecCtrl_StoreRemoteResumeService(
  vSwUpdM_GridSrvc_ServiceIdxType ServiceIndex,
  vSwUpdM_NodeGroupIterType TargetGroup,
  vSwUpdM_NodeIterType Target)
{

  vSwUpdM_DevError_Assert((vSwUpdM_ExecCtrl_RemoteResumeService.IsValid == FALSE), VSWUPDM_DEVERROR_ASSERT_47); /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */

  vSwUpdM_ExecCtrl_RemoteResumeService.ServiceIndex = ServiceIndex;
  vSwUpdM_ExecCtrl_RemoteResumeService.TargetGroup = TargetGroup;
  vSwUpdM_ExecCtrl_RemoteResumeService.Target = Target;
  vSwUpdM_ExecCtrl_RemoteResumeService.IsValid = TRUE;
} /* vSwUpdM_ExecCtrl_StoreRemoteResumeService */

/**********************************************************************************************************************
 * vSwUpdM_ExecCtrl_ClearRemoteResumeService
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */

VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_ExecCtrl_ClearRemoteResumeService(vSwUpdM_GridSrvc_ServiceIdxType ServiceIdx)
{
  vSwUpdM_DevError_Assert((vSwUpdM_ExecCtrl_RemoteResumeService.IsValid == TRUE), VSWUPDM_DEVERROR_ASSERT_50); /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */
  vSwUpdM_DevError_Assert((vSwUpdM_ExecCtrl_RemoteResumeService.ServiceIndex == ServiceIdx), VSWUPDM_DEVERROR_ASSERT_51); /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */

  if (vSwUpdM_ExecCtrl_RemoteResumeService.ServiceIndex == ServiceIdx)
  {
    vSwUpdM_ExecCtrl_RemoteResumeService.IsValid = FALSE;
  }
} /* vSwUpdM_ExecCtrl_ClearRemoteResumeService */

/**********************************************************************************************************************
 * vSwUpdM_ExecCtrl_TriggerRemoteResumeService
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 */

VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_ExecCtrl_TriggerRemoteResumeService(void)
{
  Std_ReturnType result = E_OK;

  /* #10 If remote request was previously suspended: */
  if (vSwUpdM_ExecCtrl_RemoteResumeService.IsValid == TRUE)
  {
    /* #20 Retransmit request to open channel again. */
    switch (vSwUpdM_ExecCtrl_RemoteResumeService.ServiceIndex)
    {
      case VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_PROCESS_STREAM_DATA:
      {
        result = vRpcProxy_vSwUpdM_RemoteProcessStreamData_TargetGroup(
          vSwUpdM_GetDestinationMainOfNodeGroup(vSwUpdM_ExecCtrl_RemoteResumeService.TargetGroup),
          (uint8) VSWUPDM_EXCTSCHEDULE_SERVICESTATE_RESUME,
          VSWUPDM_MAX_LENGTH);
        break;
      }
      case VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_REQUEST_PROCESS_INFO:
      {
        result = vRpcProxy_vSwUpdM_RemoteProcessRequestInput_Target(
          vSwUpdM_GetDestinationMainOfNode(vSwUpdM_ExecCtrl_RemoteResumeService.Target),
          (uint8) VSWUPDM_EXCTSCHEDULE_SERVICESTATE_RESUME,
          vSwUpdM_GetProcessHandleOfDataProcesses(vSwUpdM_ProcessData.ProcessId),
          0xFFu);
        break;
      }
      case VSWUPDM_GRIDSRVC_SERVICEIDX_START:
      {
         /* Send remote start resume and attach wait-for-response job to START job. */
        vSwUpdM_JobPtrType parentJob = &vSwUpdM_Jobs[VSWUPDM_JOB_TYPE_START];
        vSwUpdM_DevError_Assert((vSwUpdM_ExctSchedule_IsJobRunningInSlot(VSWUPDM_JOB_TYPE_START) == TRUE), VSWUPDM_DEVERROR_ASSERT_48); /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */

        result = vSwUpdM_RemoteService(
          vSwUpdM_ExecCtrl_RemoteResumeService.ServiceIndex,
          VSWUPDM_EXCTSCHEDULE_SERVICESTATE_RESUME,
          vSwUpdM_ExecCtrl_RemoteResumeService.TargetGroup,
          parentJob);
        break;
      }
      default:
      {
        /* Send remote request and attach wait-for-response job to SERVICE_DISPATCHER job.  */
        vSwUpdM_JobPtrType parentJob = &vSwUpdM_Jobs[VSWUPDM_JOB_TYPE_SERVICE_DISPATCHER];

        vSwUpdM_DevError_Assert((vSwUpdM_ExctSchedule_IsJobRunningInSlot(VSWUPDM_JOB_TYPE_SERVICE_DISPATCHER) == TRUE), VSWUPDM_DEVERROR_ASSERT_52); /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */

        result = vSwUpdM_RemoteService(vSwUpdM_ExecCtrl_RemoteResumeService.ServiceIndex,
          VSWUPDM_EXCTSCHEDULE_SERVICESTATE_RESUME,
          vSwUpdM_ExecCtrl_RemoteResumeService.TargetGroup,
          parentJob);
        break;
      }
    }
  }

  return result;
} /* vSwUpdM_ExecCtrl_TriggerRemoteResumeService */
#endif

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_InitComponent
 *********************************************************************************************************************/
 /*!
 * Internal comment removed.
 *
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
 *
 *
 */
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_InitComponent)
{
  vSwUpdM_JobStatusType retVal;

  VSWUPDM_DUMMY_STATEMENTS_JOB_HANDLER(); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  /* #10 Evaluate child result from previous cycle.
   *   If not okay, apply child result.
   *   If result is SUSPENDED suspend job. */
  retVal = vSwUpdM_Job_EvaluateChildResultOrSuspend(ActiveState, ActiveJob, FALSE);

  /* #20 Enter critical section to ensure exclusive access of state and job queue. */
  VSWUPDM_ENTER_CRITICAL_SECTION();

  /* #30 Evaluate job state. */
  if (retVal != VSWUPDM_JOB_STATUS_SUSPENDED)
  {
    switch (ActiveJob->State)
    {
      case VSWUPDM_JOB_STATE_INITIAL:
      /* #100 If callouts shall be initialized: */
      {
        /* #110 Spawn job to execute the initialization of the user callouts.
         *   Use a higher priority than active job. */
        (void)vSwUpdM_Job_Spawn(NULL_PTR, VSWUPDM_JOB_TYPE_WAIT_FOR_BOOKKEEPER_OPERATION, VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_CALLOUT_INIT, ActiveJob->CurrentPrio + 1u, VSWUPDM_SID_NONE, ActiveJob, ActiveJob->Source);

        /* #120 Advance job state to initialize the Bookkeeper connection. */
        ActiveJob->State = VSWUPDM_JOB_STATE_INIT_COMPONENT_BOOKKEEPER_OPEN_LOCAL;

        break;
      }
      case VSWUPDM_JOB_STATE_INIT_COMPONENT_BOOKKEEPER_OPEN_LOCAL:
      /* #200 If Bookkeeper connection shall be opened (local): */
      {
        /* #210 Spawn job to open the connection to the (local) Bookkeeper. */
        if (vSwUpdM_GetNNodesOfNodeGroup(vSwUpdM_GetNodeGroupIdxOfAllPersistorServerGroupLocal(VSWUPDM_BKPERISTCLIENT_PERSISTSERVERGROUPREMOTEINDEX)) > 0u)
        {
          (void)vSwUpdM_Job_Spawn(NULL_PTR, VSWUPDM_JOB_TYPE_WAIT_FOR_BOOKKEEPER_OPERATION, VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_OPEN_LOCAL, ActiveJob->CurrentPrio + 1u, VSWUPDM_SID_NONE, ActiveJob, ActiveJob->Source);
        }
        else
        {
          retVal = VSWUPDM_JOB_STATUS_ACTIVE;
        }

        ActiveJob->State = VSWUPDM_JOB_STATE_INIT_COMPONENT_BOOKKEEPER_OPEN;

        break;
      }
      case VSWUPDM_JOB_STATE_INIT_COMPONENT_BOOKKEEPER_OPEN:
      /* #300 If Bookkeeper connection shall be opened (remote): */
      {
        /* #310 Spawn job to open the connection to the (remote) Bookkeeper. */
        if (vSwUpdM_GetNNodesOfNodeGroup(vSwUpdM_GetNodeGroupIdxOfAllPersistorServerGroupRemote(VSWUPDM_BKPERISTCLIENT_PERSISTSERVERGROUPREMOTEINDEX))> 0u)
        {
          (void)vSwUpdM_Job_Spawn(NULL_PTR, VSWUPDM_JOB_TYPE_WAIT_FOR_BOOKKEEPER_OPERATION, VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_OPEN, ActiveJob->CurrentPrio + 1u, VSWUPDM_SID_NONE, ActiveJob, ActiveJob->Source);
        }
        else
        {
          retVal = VSWUPDM_JOB_STATUS_ACTIVE;
        }

        /* #320 Advance job state to initialize partitions next. */
        ActiveJob->State = VSWUPDM_JOB_STATE_INIT_COMPONENT_PARTITIONS;

        break;
      }
      case VSWUPDM_JOB_STATE_INIT_COMPONENT_PARTITIONS:
      /* #400 If partitions shall be initialized: */
      {
        /* #410 Spawn job for initialization of partition attributes.
         *   Use a higher priority than active job. */
        (void)vSwUpdM_Job_Spawn(NULL_PTR, VSWUPDM_JOB_TYPE_INIT_PARTITIONS, VSWUPDM_JOB_OPERATION_DEFAULT, ActiveJob->CurrentPrio + 1u, VSWUPDM_SID_NONE, ActiveJob, ActiveJob->Source);

        /* #420 Advance job state to get update state next. */
        ActiveJob->State = VSWUPDM_JOB_STATE_INIT_COMPONENT_UPDATE_STATE;

        break;
      }
      case VSWUPDM_JOB_STATE_INIT_COMPONENT_UPDATE_STATE:
      /* #500 If persisted update state shall be evaluated: */
      {
        /* #510 Spawn job to get persisted update state.
         *   Use a higher priority than active job. */
        (void)vSwUpdM_Job_Spawn(NULL_PTR, VSWUPDM_JOB_TYPE_HANDLE_UPDATE_STATE, VSWUPDM_JOB_OPERATION_HANDLE_UPDATE_STATE_GET, ActiveJob->CurrentPrio + 1u, VSWUPDM_SID_NONE, ActiveJob, ActiveJob->Source);

        /* #520 Advance job state to get resume information next. */
        ActiveJob->State = VSWUPDM_JOB_STATE_INIT_COMPONENT_RESUME_INFO;

        break;
      }
      case VSWUPDM_JOB_STATE_INIT_COMPONENT_RESUME_INFO:
      /* #600 If persisted resume information shall be evaluated: */
      {
        /* #610 Spawn job get persisted resume information.
         *   Use a higher priority than active job. */
        (void)vSwUpdM_Job_Spawn(NULL_PTR, VSWUPDM_JOB_TYPE_HANDLE_RESUME_INFO, VSWUPDM_JOB_OPERATION_HANDLE_RESUME_INFO_GET, ActiveJob->CurrentPrio + 1u, VSWUPDM_SID_NONE, ActiveJob, ActiveJob->Source);

        /* #620 Forward to final state, waiting for result of getting the resume information. */
        ActiveJob->State = VSWUPDM_JOB_STATE_FINAL;

        break;
      }
      case VSWUPDM_JOB_STATE_FINAL:
      /* #700 If waiting for result of final operation: */
      {
        /* #710 Set initialization state to indicate that component is now initialized. */
        vSwUpdM_InitState = VSWUPDM_INIT_STATE_INITIALIZED;
        /* #720 Indicate that job is finished. */
        retVal            = VSWUPDM_JOB_STATUS_FINISHED;

        break;
      }
      case VSWUPDM_JOB_STATE_FAILED:
      /* #800 If job state is "failed", because of negative child result: */
      {
        /* #810 Set initialization state to indicate that initialization failed. */
        vSwUpdM_InitState   = VSWUPDM_INIT_STATE_FAILED;
        /* #820 Set global state to shut down pending, allowing for retry of initialization by calling Start service. */
        vSwUpdM_GlobalState = VSWUPDM_STATE_SHUT_DOWN_PENDING;

        break;
      }
      /* #900 Otherwise: Invalid state.
       *   Set error in job result. */
      default:
      {
        ActiveJob->Result = VSWUPDM_E_INV_STATE;
        break;
      }
    }
  }

  /* #1000 Leave critical section ensuring exclusive access of state and job queue. */
  VSWUPDM_LEAVE_CRITICAL_SECTION();

  return retVal;
  /* PRQA S 6030 1 */ /* MD_MSR_STCYC */
} /* vSwUpdM_JobHandler_InitComponent */

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_InitPartitions
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
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_InitPartitions)
{
  vSwUpdM_JobStatusType    retVal              = VSWUPDM_JOB_STATUS_PENDING; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vSwUpdM_JobOperationType bookkeeperOperation = VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_NONE;

  VSWUPDM_DUMMY_STATEMENTS_JOB_HANDLER(); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  /* #10 Evaluate child result from previous cycle.
   *   If not okay, apply child result.
   *   If result is SUSPENDED suspend job. */
  retVal = vSwUpdM_Job_EvaluateChildResultOrSuspend(ActiveState, ActiveJob, FALSE);

  /* #20 Evaluate job state. */
  switch (ActiveJob->State)
  {
    case VSWUPDM_JOB_STATE_INITIAL:
    /* #100 If initial conditions for first actual phase shall be established */
    {
      /* #110 Start with initializing attributes of first partition. */
      vSwUpdM_Init_EntityIdsDefaults(&ActiveJob->EntityIds);
      ActiveJob->EntityIds.PartitionId    = 0u;
      ActiveJob->EntityIds.PartitionState = VSWUPDM_PART_STATE_UNDEFINED;

      /* #120 Trigger bookkeeper to get the state of the first partition.
       *   Advance job state accordingly. */
      ActiveJob->State    = VSWUPDM_JOB_STATE_INIT_PARTITIONS_STATE;
      bookkeeperOperation = VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_GET_PARTITION_STATE;

      break;
    }
    case VSWUPDM_JOB_STATE_INIT_PARTITIONS_STATE:
    /* #200 If waiting for the bookkeeper to get the state of the partition */
    {
      /* #210 Trigger bookkeeper to get the validity of the current partition.
       *   Advance job state accordingly. */
      ActiveJob->State    = VSWUPDM_JOB_STATE_INIT_PARTITIONS_VALID;
      bookkeeperOperation = VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_GET_PARTITION_VALID;

      break;
    }
    case VSWUPDM_JOB_STATE_INIT_PARTITIONS_VALID:
    /* #300 If waiting for the bookkeeper to get the validity of the partition */
    {
      vSwUpdM_VarPartitionsPtrType partition = vSwUpdM_GetAddrVarPartitions(ActiveJob->EntityIds.PartitionId);

      /* #310 Advance job state init module instances of current partition next. */
      ActiveJob->State = VSWUPDM_JOB_STATE_INIT_PARTITIONS_REVISION;

      /* #320 If current partition is valid */
      if (partition->DynamicAttributesOfVarPartitions.IsValid == TRUE)
      {
        /* #330 Trigger bookkeeper to get the revision of the current partition. */
        bookkeeperOperation = VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_GET_PARTITION_REVISION;
      }
      /* #340 Otherwise:
       *   Mark revision as invalid */
      else
      {
        partition->DynamicAttributesOfVarPartitions.Revision = VSWUPDM_INVALID_REVISION;

        retVal = VSWUPDM_JOB_STATUS_ACTIVE;
      }

      break;
    }
    case VSWUPDM_JOB_STATE_INIT_PARTITIONS_REVISION:
    /* #400 If waiting for the bookkeeper to get the revision of the partition */
    {
      vSwUpdM_JobPtrType spawnedJob;
      Std_ReturnType     spawnResult;

      /* #410 Advance job state to wait for result of module initialization. */
      ActiveJob->State = VSWUPDM_JOB_STATE_INIT_PARTITIONS_MODULES;

      /* #420 Enter critical section to ensure exclusive access of state and job queue. */
      VSWUPDM_ENTER_CRITICAL_SECTION();

      /* #430 Spawn job to initialize module instances of the current partition.
       *   Use a higher priority than active job. */
      spawnedJob = vSwUpdM_Job_Spawn(&spawnResult, VSWUPDM_JOB_TYPE_INIT_MODULES, VSWUPDM_JOB_OPERATION_DEFAULT, ActiveJob->CurrentPrio + 1u, VSWUPDM_SID_NONE, ActiveJob, ActiveJob->Source);

      /* #440 Job attributes are safe to be modified when job was successfully spawned and access is still protected by critical section. */
      if (spawnResult == E_OK)
      {
        /* #450 Spawned job operates on same entities as active job.  */
        spawnedJob->EntityIds = ActiveJob->EntityIds;
      }

      /* #460 Leave critical section ensuring exclusive access of state and job queue. */
      VSWUPDM_LEAVE_CRITICAL_SECTION();

      break;
    }
    case VSWUPDM_JOB_STATE_INIT_PARTITIONS_MODULES:
    /* #500 If waiting for the initialization of the module instances of the partition */
    {
      /* #510 Handle the next partition. */
      ActiveJob->EntityIds.PartitionId++;

      /* #520 If this wasn't the last partition */
      if (ActiveJob->EntityIds.PartitionId < vSwUpdM_GetStaticNumberOfPartitions())
      {
        /* #530 Trigger bookkeeper to get the state of the next partition.
         *   Advance job state accordingly. */
        ActiveJob->State    = VSWUPDM_JOB_STATE_INIT_PARTITIONS_STATE;
        bookkeeperOperation = VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_GET_PARTITION_STATE;
      }
      /* #540 Otherwise: All partitions initialized.
       *   Finish job execution. */
      else
      {
        retVal = VSWUPDM_JOB_STATUS_FINISHED;
      }

      break;
    }
    case VSWUPDM_JOB_STATE_FAILED:
    /* #600 If job state is "failed", because of negative child result
     *   Return with negative result taken over from child job. */
    {
      break;
    }
    default:
    /* #700 Otherwise: Invalid state.
     *   Set error in job result. */
    {
      ActiveJob->Result = VSWUPDM_E_INV_STATE;
      break;
    }
  }

  /* #1000 If any bookkeeper operation shall be triggered */
  if (bookkeeperOperation != VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_NONE)
  {
    /* #1010 Trigger bookkeeper.
     *   Result will be evaluated during next job cycle. */
    retVal = vSwUpdM_Job_TriggerBookkeeper(bookkeeperOperation, ActiveJob);
  }

  return retVal;
  /* PRQA S 6030 1 */ /* MD_MSR_STCYC */
} /* vSwUpdM_JobHandler_InitPartitions */

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_InitModules
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
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_InitModules)
{
  vSwUpdM_JobStatusType    retVal              = VSWUPDM_JOB_STATUS_PENDING; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vSwUpdM_JobOperationType bookkeeperOperation = VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_NONE;

  VSWUPDM_DUMMY_STATEMENTS_JOB_HANDLER(); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  /* #10 Evaluate child result from previous cycle.
   *   If not okay, apply child result.
   *   If result is SUSPENDED suspend job. */
  retVal = vSwUpdM_Job_EvaluateChildResultOrSuspend(ActiveState, ActiveJob, FALSE);

  /* #20 Evaluate job state. */
  switch (ActiveJob->State)
  {
    case VSWUPDM_JOB_STATE_INITIAL:
    /* #100 If initial conditions for first actual phase shall be established */
    {
      /* #110 Start with initializing attributes of first module. */
      ActiveJob->EntityIds.ModuleId = 0u;

      /* #120 Advance job state to check whether module is instantiated in requested partition. */
      ActiveJob->State = VSWUPDM_JOB_STATE_INIT_MODULES_CHECK_PARTITION;
      retVal           = VSWUPDM_JOB_STATUS_ACTIVE;

      break;
    }
    case VSWUPDM_JOB_STATE_INIT_MODULES_CHECK_PARTITION:
    /* #200 If check whether module is instantiated in requested partition shall be done */
    {
      /* #210 If module is instantiated in requested partition
       *   Set relative partition index in entity IDs. */
      if (vSwUpdM_Module_GetRelativePartitionIdxByPartition(&ActiveJob->EntityIds.PartitionIdx, ActiveJob->EntityIds.ModuleId, ActiveJob->EntityIds.PartitionId) == E_OK)
      {
        /* #220 Trigger bookkeeper to get the state of the current module.
         *   Advance job state accordingly. */
        ActiveJob->State    = VSWUPDM_JOB_STATE_INIT_MODULES_STATE;
        bookkeeperOperation = VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_GET_MODULE_STATE;
      }
      /* #230 Otherwise:
       *   Forward state to handle next module. */
      else
      {
        ActiveJob->State = VSWUPDM_JOB_STATE_INIT_MODULES_REVISION;
        retVal           = VSWUPDM_JOB_STATUS_ACTIVE;
      }

      break;
    }
    case VSWUPDM_JOB_STATE_INIT_MODULES_STATE:
    /* #300 If waiting for the bookkeeper to get the state of the module */
    {
      /* #310 Trigger bookkeeper to get the validity of the current module.
       *   Advance job state accordingly. */
      ActiveJob->State    = VSWUPDM_JOB_STATE_INIT_MODULES_VALID;
      bookkeeperOperation = VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_GET_MODULE_VALID;

      break;
    }
    case VSWUPDM_JOB_STATE_INIT_MODULES_VALID:
    /* #350 If waiting for the bookkeeper to get the validity of the module */
    {
      /* #360 Trigger bookkeeper to get the programming attempt counter of the current module.
       *   Advance job state accordingly. */
      ActiveJob->State    = VSWUPDM_JOB_STATE_INIT_MODULES_PROGRAMMING_ATTEMPTS;
      bookkeeperOperation = VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_GET_MODULE_PROGRAMMING_ATTEMPTS;

      break;
    }
    case VSWUPDM_JOB_STATE_INIT_MODULES_PROGRAMMING_ATTEMPTS:
    /* #400 If waiting for the bookkeeper to get the validity of the module */
    {
      vSwUpdM_PartitionIdxType  partitionIdx = ActiveJob->EntityIds.PartitionIdx;
      vSwUpdM_VarModulesPtrType module       = vSwUpdM_GetAddrVarModules(ActiveJob->EntityIds.ModuleId);

      /* #410 If module instance in requested partition is valid */
      if (module->DynamicAttributesOfVarModules[partitionIdx].IsValid == TRUE)
      {
        /* #420 Trigger bookkeeper to get the revision of the current module.
         *   Advance job state accordingly. */
        bookkeeperOperation = VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_GET_MODULE_REVISION;
      }
      /* #430 Otherwise:
       *   Mark revision as invalid */
      else
      {
        module->DynamicAttributesOfVarModules[partitionIdx].Revision = VSWUPDM_INVALID_REVISION;

        retVal = VSWUPDM_JOB_STATUS_ACTIVE;
      }

      /* #440 Advance job state to handle next module. */
      ActiveJob->State = VSWUPDM_JOB_STATE_INIT_MODULES_REVISION;

      break;
    }
    case VSWUPDM_JOB_STATE_INIT_MODULES_REVISION:
    /* #500 If waiting for evaluation of the revision of the module */
    {
      /* #510 Handle the next module */
      ActiveJob->EntityIds.ModuleId++;

      /* #520 If this wasn't the last module */
      if (ActiveJob->EntityIds.ModuleId < vSwUpdM_GetStaticNumberOfModules())
      {
        /* #530 Advance job state to check whether module is instantiated in requested partition. */
        ActiveJob->State = VSWUPDM_JOB_STATE_INIT_MODULES_CHECK_PARTITION;
        retVal           = VSWUPDM_JOB_STATUS_ACTIVE;
      }
      /* #540 Otherwise: All module instances of requested partition initialized.
       *   Finish job execution. */
      else
      {
        retVal = VSWUPDM_JOB_STATUS_FINISHED;
      }

      break;
    }
    case VSWUPDM_JOB_STATE_FAILED:
    /* #600 If job state is "failed", because of negative child result
     *   Return with negative result taken over from child job. */
    {
      break;
    }
    default:
    /* #700 Otherwise: Invalid state.
     *   Set error in job result. */
    {
      ActiveJob->Result = VSWUPDM_E_INV_STATE;
      break;
    }
  }

  /* #1000 If any bookkeeper operation shall be triggered */
  if (bookkeeperOperation != VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_NONE)
  {
    /* #1010 Trigger bookkeeper.
     *   Result will be evaluated during next job cycle. */
    retVal = vSwUpdM_Job_TriggerBookkeeper(bookkeeperOperation, ActiveJob);
  }

  return retVal;
  /* PRQA S 6030 1 */ /* MD_MSR_STCYC */
} /* vSwUpdM_JobHandler_InitModules */

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_InitRegions
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
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_InitRegions)
{
  vSwUpdM_JobStatusType    retVal              = VSWUPDM_JOB_STATUS_PENDING;
  vSwUpdM_JobOperationType bookkeeperOperation = VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_NONE;

  VSWUPDM_DUMMY_STATEMENTS_JOB_HANDLER(); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  /* #10 Evaluate child result from previous cycle. */
  (void)vSwUpdM_Job_EvaluateAndApplyChildResult(ActiveJob, FALSE);

  /* #20 Evaluate job state. */
  switch (ActiveJob->State)
  {
    case VSWUPDM_JOB_STATE_INITIAL:
    /* #100 If initial conditions for first actual phase shall be established */
    {
      /* #110 Start with initializing attributes of first region, using relative index of region in requested module. */
      ActiveJob->EntityIds.RegionIdx = 0u;

      /* #120 Trigger bookkeeper to get the state of the first region.
        *   Advance job state accordingly. */
      ActiveJob->State    = VSWUPDM_JOB_STATE_INIT_REGIONS_GET_REGION_STATE;
      bookkeeperOperation = VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_GET_REGION_STATE;

      break;
    }
    case VSWUPDM_JOB_STATE_INIT_REGIONS_GET_REGION_STATE:
    /* #150 If waiting for the bookkeeper to get the state of the region */
    {
      /* #120 Trigger bookkeeper to get the programming attempt counter of the region.
        *   Advance job state accordingly. */
      ActiveJob->State    = VSWUPDM_JOB_STATE_INIT_REGIONS_GET_REGION_PROGRAMMING_ATTEMPTS;
      bookkeeperOperation = VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_GET_REGION_PROGRAMMING_ATTEMPTS;

      break;
    }
    case VSWUPDM_JOB_STATE_INIT_REGIONS_GET_REGION_PROGRAMMING_ATTEMPTS:
    /* #150 If waiting for the bookkeeper to get the programming attempt counter of the region */
    {
      /* #210 If no erase operation is currently pending for current region */
      if (vSwUpdM_GetVarRegions(ActiveJob->EntityIds.RegionIdx).DynamicAttributesOfVarRegion.State != VSWUPDM_REGION_STATE_ERASE_PENDING)
      {
        /* #220 Forward state to skip getting persisted erase address. */
        ActiveJob->State = VSWUPDM_JOB_STATE_INIT_REGIONS_NEXT_REGION;
        retVal           = VSWUPDM_JOB_STATUS_ACTIVE;
      }
      else
      {
        /* #230 Trigger bookkeeper to get the erase address of the current region.
         *   Advance job state accordingly. */
        ActiveJob->State    = VSWUPDM_JOB_STATE_INIT_REGIONS_GET_ERASE_ADDRESS;
        bookkeeperOperation = VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_GET_REGION_ERASE_ADDRESS;
      }

      break;
    }
    case VSWUPDM_JOB_STATE_INIT_REGIONS_GET_ERASE_ADDRESS:
    /* #300 If waiting for the bookkeeper to get the erase address of the region */
    {
      vSwUpdM_VarRegionsPtrType region = vSwUpdM_GetAddrVarRegions(ActiveJob->EntityIds.RegionIdx);
      vSwUpdM_LengthType        reservedLength;

      /* #310 If the recovered erase address isn't located within the reserved range of the region or directly points behind it. */
      reservedLength = (region->ReservedEndAddressOfVarRegions - region->ReservedStartAddressOfVarRegions) + 2u;

      if (vSwUpdM_Range_IsAddressInRange(region->EraseAddressOfVarRegion, region->ReservedStartAddressOfVarRegions, reservedLength) == FALSE)
      {
        /* #320 Information is inconsistent, set state of region to "undefined". */
        region->DynamicAttributesOfVarRegion.State = VSWUPDM_REGION_STATE_UNDEFINED;
        region->EraseAddressOfVarRegion            = region->ReservedStartAddressOfVarRegions;
      }

      /* #330 Forward state to handle next region. */
      ActiveJob->State = VSWUPDM_JOB_STATE_INIT_REGIONS_NEXT_REGION;
      retVal           = VSWUPDM_JOB_STATUS_ACTIVE;

      break;
    }
    case VSWUPDM_JOB_STATE_INIT_REGIONS_NEXT_REGION:
    /* #400 If next region shall be handled */
    {
      /* #410 Handle the next region of the module. */
      ActiveJob->EntityIds.RegionIdx++;

      /* #420 If this wasn't the last region of the requested module */
      if (ActiveJob->EntityIds.RegionIdx < vSwUpdM_GetNRegionsOfModule(ActiveJob->EntityIds.ModuleId))
      {
        /* #430 Trigger bookkeeper to get the state of the next region.
          *   Advance job state accordingly. */
        ActiveJob->State    = VSWUPDM_JOB_STATE_INIT_REGIONS_GET_REGION_STATE;
        bookkeeperOperation = VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_GET_REGION_STATE;
      }
      /* #440 Otherwise: All regions of requested module initialized.
       *   Finish job execution. */
      else
      {
        retVal = VSWUPDM_JOB_STATUS_FINISHED;
      }

      break;
    }
    case VSWUPDM_JOB_STATE_FAILED:
    /* #500 If job state is "failed", because of negative child result
     *   Return with negative result taken over from child job. */
    {
      break;
    }
    default:
    /* #600 Otherwise: Invalid state.
     *   Set error in job result. */
    {
      ActiveJob->Result = VSWUPDM_E_INV_STATE;
      break;
    }
  }

  /* #1000 If any bookkeeper operation shall be triggered */
  if (bookkeeperOperation != VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_NONE)
  {
    vSwUpdM_Module2RegionIdxOfModuleType module2RegionIdx;

    /* #1010 Evaluate static region ID for current relative region index in requested module and set in entity IDs. */
    module2RegionIdx              = vSwUpdM_GetModule2RegionIdxOfModule(ActiveJob->EntityIds.ModuleId) + (vSwUpdM_Module2RegionIdxOfModuleType)ActiveJob->EntityIds.RegionIdx;
    ActiveJob->EntityIds.RegionId = vSwUpdM_GetRegionIdxOfModule2Region(module2RegionIdx);

    /* #1020 Trigger bookkeeper.
     *   Result will be evaluated during next job cycle. */
    retVal = vSwUpdM_Job_TriggerBookkeeper(bookkeeperOperation, ActiveJob);
  }

  return retVal;
  /* PRQA S 6030 1 */ /* MD_MSR_STCYC */
} /* vSwUpdM_JobHandler_InitRegions */

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_InitSegments
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
 *
 *
 *
 */
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_InitSegments)
{
  vSwUpdM_JobStatusType    retVal              = VSWUPDM_JOB_STATUS_PENDING;
  vSwUpdM_JobOperationType bookkeeperOperation = VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_NONE;

  VSWUPDM_DUMMY_STATEMENTS_JOB_HANDLER(); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  /* #10 Evaluate job state. */
  switch (ActiveJob->State)
  {
    case VSWUPDM_JOB_STATE_INITIAL:
    /* #100 If initial conditions for first actual phase shall be established */
    {
      /* #110 Keep track of processed dynamic segments of module using relative index of segment in entity IDs.
       *   Reset value to zero. */
      ActiveJob->EntityIds.SegmentIdx  = 0u;

      /* #120 Trigger bookkeeper to get the number of dynamic segments of the requested module.
        *   Advance job state accordingly. */
      ActiveJob->State    = VSWUPDM_JOB_STATE_INIT_SEGMENTS_COUNT;
      bookkeeperOperation = VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_GET_SEGMENT_COUNT;

      break;
    }
    case VSWUPDM_JOB_STATE_INIT_SEGMENTS_COUNT:
    /* #200 If waiting for the bookkeeper to get the number of dynamic segments of the requested module */
    {
      /* #210 Evaluate child result from previous cycle.
       * If not okay */
      if (vSwUpdM_Job_EvaluateChildResult(ActiveJob) != E_OK)
      {
        /* #220 Do not apply child result, but reset it. */
        vSwUpdM_Job_ResetChildResult(ActiveJob);
        ActiveJob->Result           = E_OK;
        /* #221 Set pending count of dynamic segments to be initialized to zero. */
        vSwUpdM_SegmentPendingCount = 0u;

        retVal = VSWUPDM_JOB_STATUS_FINISHED;
      }
      else
      {
        /* #230 If there are any pending dynamic segment to be initialized */
        if (vSwUpdM_SegmentPendingCount > 0u)
        {
          /* #231 If only first segment shall be initialized, as requested by job operation
           *   Used for recovery from unintended shutdown, where update is resumed from start of first segment.
           *   Limit pending count to one. */
          if (ActiveJob->Operation == VSWUPDM_JOB_OPERATION_INIT_SEGMENTS_FIRST_SEGMENT)
          {
            vSwUpdM_SegmentPendingCount = 1u;
          }

          /* #240 Trigger bookkeeper to initialize the attributes of the first dynamic segment.
            *   Advance job state accordingly. */
          ActiveJob->State    = VSWUPDM_JOB_STATE_INIT_SEGMENTS_ATTRIBUTES;
          bookkeeperOperation = VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_GET_SEGMENT_ATTRIBUTES;
        }
        else
        {
          /* #250 Advance job state to check whether write address needs to be initialized for the first internal segment. */
          ActiveJob->EntityIds.SegmentId.DynamicSegmentId = 0u;

          ActiveJob->State = VSWUPDM_JOB_STATE_INIT_SEGMENTS_CHECK_SEGMENT;
          retVal           = VSWUPDM_JOB_STATUS_ACTIVE;
        }
      }

      break;
    }
    case VSWUPDM_JOB_STATE_INIT_SEGMENTS_ATTRIBUTES:
    /* #300 If waiting for the bookkeeper to get the attributes of a dynamic segment */
    {
      /* #310 Evaluate child result from previous cycle.
       * If okay */
      if (vSwUpdM_Job_EvaluateAndApplyChildResult(ActiveJob, FALSE) == E_OK)
      {
        vSwUpdM_SegmentInfoType    segmentInfo;
        vSwUpdM_VarSegmentsPtrType segment;

        /* #320 Create dynamic segment for update data, using the persisted attributes. */
        (void)vSwUpdM_InitSegmentInfo(&segmentInfo);
        segmentInfo.StartAddress   = vSwUpdM_SegmentPendingAttributes.StartAddress;
        segmentInfo.Length         = vSwUpdM_SegmentPendingAttributes.InitialLength;
        segmentInfo.LengthHandling = vSwUpdM_SegmentPendingAttributes.LengthHandling;
        segmentInfo.State          = vSwUpdM_SegmentPendingAttributes.State;

        ActiveJob->Result = vSwUpdM_Segment_AddSegment(&segmentInfo, VSWUPDM_CLASS_OF_VAR_SEGMENTS_USED, VSWUPDM_ALIGN_GRANULARITY_PAGE, FALSE);

        if (ActiveJob->Result == E_OK)
        {
          segment = vSwUpdM_GetAddrVarSegments(segmentInfo.Id.DynamicSegmentId);
          ActiveJob->EntityIds.SegmentId.DynamicSegmentId = segmentInfo.Id.DynamicSegmentId;

          /* Reset "dirty" flag of the restored segment. */
          segment->AttributesDirty = FALSE;

          /* #330 Evaluate state of region in which the current segment is located. */
          if (ActiveJob->Operation != VSWUPDM_JOB_OPERATION_INIT_SEGMENTS_KEEP_STATE)
          {
            switch (vSwUpdM_GetVarRegions(segment->RegionIdxOfVarSegments).DynamicAttributesOfVarRegion.State)
            {
              case VSWUPDM_REGION_STATE_UNDEFINED:
              case VSWUPDM_REGION_STATE_ERASE_PENDING:
              case VSWUPDM_REGION_STATE_DIRTY:
              /* #331 If state is "undefined", "erase pending" or "dirty"
               *   Change state of segment to "undefined". */
              {
                segment->DynamicAttributesOfVarSegment.State = VSWUPDM_SEGMENT_STATE_UNDEFINED;

                break;
              }
              default:
              /* #332 Otherwise:
               *   Segment state remains unchanged. */
              {
                break;
              }
            }
          }

          /* #340 Handle the next dynamic segment. */
          ActiveJob->EntityIds.SegmentIdx++;

          /* #350 If this wasn't the last dynamic segment of the requested module
           *   Trigger bookkeeper to initialize the attributes of the next dynamic segment. */
          if (ActiveJob->EntityIds.SegmentIdx < vSwUpdM_SegmentPendingCount)
          {
            bookkeeperOperation = VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_GET_SEGMENT_ATTRIBUTES;
          }
          /* #360 Otherwise */
          else
          {
            /* #370 If only first segment shall be initialized, as requested by job operation */
            if (ActiveJob->Operation == VSWUPDM_JOB_OPERATION_INIT_SEGMENTS_FIRST_SEGMENT)
            {
              /* #371 Finish job execution.
               *   Do not restore write address. */
              retVal = VSWUPDM_JOB_STATUS_FINISHED;
            }
            /* #380 Otherwise */
            else
            {
              /* #381 Advance job state to check whether write address needs to be initialized for the first internal segment. */
              ActiveJob->EntityIds.SegmentId.DynamicSegmentId = 0u;

              ActiveJob->State = VSWUPDM_JOB_STATE_INIT_SEGMENTS_CHECK_SEGMENT;
              retVal           = VSWUPDM_JOB_STATUS_ACTIVE;
            }
          }
        }
      }

      break;
    }
    case VSWUPDM_JOB_STATE_INIT_SEGMENTS_CHECK_SEGMENT:
    /* #400 If check whether write address needs to be initialized for the current internal segment shall be executed */
    {
      /* PRQA S 3679 1 */ /* MD_vSwUpdM_Rule8.13_3679_PointerToModifiableData */
      vSwUpdM_VarSegmentsPtrType segment = vSwUpdM_GetAddrVarSegments(ActiveJob->EntityIds.SegmentId.DynamicSegmentId);

      ActiveJob->State = VSWUPDM_JOB_STATE_INIT_SEGMENTS_NEXT_SEGMENT;
      retVal           = VSWUPDM_JOB_STATUS_ACTIVE;

      switch (segment->ClassOfVarSegments)
      {
        case VSWUPDM_CLASS_OF_VAR_SEGMENTS_USED:
        case VSWUPDM_CLASS_OF_VAR_SEGMENTS_RESERVED:
        /* #410 If segment represents a free memory area or is used for updated data */
        {
          /* #411 Trigger bookkeeper to initialize the write address of the current internal segment.
            *   Advance job state accordingly. */
          ActiveJob->State    = VSWUPDM_JOB_STATE_INIT_SEGMENTS_WRITE_ADDRESSES;
          bookkeeperOperation = VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_GET_SEGMENT_WRITE_ADDRESS;

          break;
        }
        case VSWUPDM_CLASS_OF_VAR_SEGMENTS_FREE:
        {
          if (segment->WriteSegmentIdx == segment->RegionIdxOfVarSegments)
          {
            ActiveJob->State    = VSWUPDM_JOB_STATE_INIT_SEGMENTS_WRITE_ADDRESSES;
            bookkeeperOperation = VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_GET_SEGMENT_WRITE_ADDRESS;
          }

          break;
        }
        default:
        /* #420 Otherwise
         *   Advance job state to handle next segment. */
        {
          break;
        }
      }

      break;
    }
    case VSWUPDM_JOB_STATE_INIT_SEGMENTS_WRITE_ADDRESSES:
    /* #500 If waiting for the bookkeeper to get the write address of the current internal segment */
    {
      vSwUpdM_VarSegmentsPtrType segment = vSwUpdM_GetAddrVarSegments(ActiveJob->EntityIds.SegmentId.DynamicSegmentId);

      /* #510 Evaluate child result from previous cycle.
       * If okay */
      if (vSwUpdM_Job_EvaluateChildResult(ActiveJob) == E_OK)
      {
        segment->WriteAddressDirty = FALSE;

        if ( (segment->ReservedEndAddressOfVarSegments < VSWUPDM_MAX_ADDRESS)
          && (segment->WriteAddressOfVarSegments > 0u) )
        {
          vSwUpdM_SegmentIdValueType freeSegmentId = 0u;
          vSwUpdM_VarSegmentsPtrType freeSegment;

          (void)vSwUpdM_Segment_SearchSegment(&freeSegmentId, segment->ReservedEndAddressOfVarSegments + 1u);
          freeSegment = vSwUpdM_GetAddrVarSegments(freeSegmentId);

          if (freeSegment->ClassOfVarSegments == VSWUPDM_CLASS_OF_VAR_SEGMENTS_FREE)
          {
            vSwUpdM_LengthType reservedLength;

            /* #522 If the recovered write address isn't located within the reserved range of the segment or directly points behind it. */
            reservedLength = (freeSegment->ReservedEndAddressOfVarSegments - freeSegment->ReservedStartAddressOfVarSegments) + 2u;

            if (vSwUpdM_Range_IsAddressInRange((segment->WriteAddressOfVarSegments - 1u), freeSegment->ReservedStartAddressOfVarSegments, reservedLength) == TRUE)
            {
              freeSegment->DynamicAttributesOfVarSegment.State = VSWUPDM_SEGMENT_STATE_PENDING;
              freeSegment->WriteAddressOfVarSegments           = segment->WriteAddressOfVarSegments;
              freeSegment->WriteAddressDirty                   = FALSE;
              segment->WriteAddressOfVarSegments               = segment->ReservedEndAddressOfVarSegments + 1u;
            }
          }
        }
      }
      /* #560 Otherwise */
      else
      {
        /* #561 Change state of segment to "undefined". */
        segment->DynamicAttributesOfVarSegment.State = VSWUPDM_SEGMENT_STATE_UNDEFINED;

        /* #562 Reset child result. */
        vSwUpdM_Job_ResetChildResult(ActiveJob);
      }

      /* #570 Advance job state to handle next segment. */
      ActiveJob->State = VSWUPDM_JOB_STATE_INIT_SEGMENTS_NEXT_SEGMENT;
      retVal           = VSWUPDM_JOB_STATUS_ACTIVE;

      break;
    }
    case VSWUPDM_JOB_STATE_INIT_SEGMENTS_NEXT_SEGMENT:
    /* #600 If next internal segment shall be handled */
    {
      /* #610 Handle the next internal segment */
      ActiveJob->EntityIds.SegmentId.DynamicSegmentId++;

      /* #620 If this wasn't the last internal segment of the requested module
        *   Trigger bookkeeper to get the write address of next internal segment. */
      if (ActiveJob->EntityIds.SegmentId.DynamicSegmentId < vSwUpdM_EntityData.Count.InternalSegmentCount)
      {
        ActiveJob->State = VSWUPDM_JOB_STATE_INIT_SEGMENTS_CHECK_SEGMENT;
        retVal           = VSWUPDM_JOB_STATUS_ACTIVE;
      }
      /* #630 Otherwise
       *   Reset "dirty" flag of external segment count and finish job execution. */
      else
      {
        vSwUpdM_EntityData.Count.ExternalSegmentCountDirty = FALSE;

        retVal = VSWUPDM_JOB_STATUS_FINISHED;
      }

      break;
    }
    default:
    /* #700 Otherwise: Invalid state.
     *   Set error in job result. */
    {
      ActiveJob->Result = VSWUPDM_E_INV_STATE;

      break;
    }
  }

  /* #1000 If any bookkeeper operation shall be triggered */
  if (bookkeeperOperation != VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_NONE)
  {
    /* #1010 Trigger bookkeeper.
     *   Result will be evaluated during next job cycle. */
    retVal = vSwUpdM_Job_TriggerBookkeeper(bookkeeperOperation, ActiveJob);
  }

  return retVal;
  /* PRQA S 6030, 6050, 6080 1 */ /* MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */
} /* vSwUpdM_JobHandler_InitSegments */

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_FinalizeModuleUpdateLocal
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
 */
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_FinalizeModuleUpdateLocal)
{
  vSwUpdM_JobStatusType retVal;
#if (VSWUPDM_MULTICONTROLLER_SUPPORT == STD_ON)
  vSwUpdM_ModuleIdType  moduleId = ActiveJob->EntityIds.ModuleId;
#endif

  VSWUPDM_DUMMY_STATEMENTS_JOB_HANDLER(); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  /* #10 Evaluate child result from previous cycle.
   *   If not okay, apply child result.
   *   If result is SUSPENDED suspend job. */
  retVal = vSwUpdM_Job_EvaluateChildResultOrSuspend(ActiveState, ActiveJob, FALSE);

  if (retVal != VSWUPDM_JOB_STATUS_SUSPENDED)
  {

    /* #20 Evaluate job state. */
    switch (ActiveJob->State)
    {
      case VSWUPDM_JOB_STATE_INITIAL:
      {
        /* #100 If the module is local: */
#if (VSWUPDM_MULTICONTROLLER_SUPPORT == STD_ON)
        if (!vSwUpdM_IsWithLocalNodeOfNodeGroup(vSwUpdM_GetNodeGroupOwnersIdxOfModule(moduleId)))
        {
          /* #110 If resume info shall be updated by job
           *   Update resume information to indicate that service is finished, taking over service ID and address.
           *   Force persisting of resume information. */
          if (ActiveJob->UpdateResumeInfo == TRUE)
          {
            (void)vSwUpdM_ResumeInfo_UpdateAndPersistState(VSWUPDM_PART_STATE_UNDEFINED, VSWUPDM_SID_FINALIZE_MODULE, VSWUPDM_RESUME_STATE_FINISHED, vSwUpdM_ResumeInfo.ResumeInfo.MemoryAddress, vSwUpdM_ResumeInfo.ResumeInfo.StreamAddress, vSwUpdM_ResumeInfo.TriggerAddress, vSwUpdM_ResumeInfo.ResumeInfo.IsAddressValid, ActiveJob->Source);
          }

          /* #120 Update state of requested module to "finalized" and trigger persisting of module state. */
          (void)vSwUpdM_Module_UpdateAndPersistState(ActiveJob->EntityIds.PartitionId, ActiveJob->EntityIds.PartitionState, ActiveJob->EntityIds.ModuleId, VSWUPDM_MODULE_STATE_FINALIZED, ActiveJob, ActiveJob->Source);

        }
#endif
        ActiveJob->State = VSWUPDM_JOB_STATE_FINAL;
        break;
      }

      case VSWUPDM_JOB_STATE_FINAL:
      /* #200 If waiting for result of final operation
       *   Indicate that job is finished. */
      {
        retVal = VSWUPDM_JOB_STATUS_FINISHED;
        break;
      }
      case VSWUPDM_JOB_STATE_FAILED:
      /* #300 If job state is "failed", because of negative child result
       *   Return with negative result taken over from child job. */
      {
        break;
      }
      default:
      /* #400 Otherwise: Invalid state.
       *   Set error in job result. */
      {
        ActiveJob->Result = VSWUPDM_E_INV_STATE;
        break;
      }
    }
  }

  return retVal;
  /* PRQA S 6030 1 */ /* MD_MSR_STCYC */
} /* vSwUpdM_JobHandler_FinalizeModuleUpdateLocal */


/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_OpenModuleLocal
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
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_OpenModuleLocal)
{
  vSwUpdM_JobStatusType retVal;
  vSwUpdM_ModuleIdType  partitionId = ActiveJob->EntityIds.PartitionId;
  vSwUpdM_ModuleIdType  moduleId    = ActiveJob->EntityIds.ModuleId;

  VSWUPDM_DUMMY_STATEMENTS_JOB_HANDLER(); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  /* #10 Evaluate child result from previous cycle.
   *   If not okay, apply child result.
   *   If result is SUSPENDED suspend job. */
  retVal = vSwUpdM_Job_EvaluateChildResultOrSuspend(ActiveState, ActiveJob, FALSE);
  if (retVal != VSWUPDM_JOB_STATUS_SUSPENDED)
  {

    /* #20 Evaluate job state. */
    switch (ActiveJob->State)
    {
      case VSWUPDM_JOB_STATE_INITIAL:
      /* #100 If initial conditions for first actual phase shall be established */
      {
        /* #120 Trigger initialization of regions of requested module. */
        (void)vSwUpdM_Module_InitRegions(moduleId, VSWUPDM_SID_NONE, ActiveJob);

        /* #130 Forward state to finish initialization of regions next. */
        ActiveJob->State = VSWUPDM_JOB_STATE_OPEN_MODULE_INIT_REGIONS;

        break;
      }
      case VSWUPDM_JOB_STATE_OPEN_MODULE_INIT_REGIONS:
      /* #200 If initialization of regions shall be finished */
      {
        vSwUpdM_ModuleStateType         moduleState;
        vSwUpdM_ProgrammingAttemptsType moduleAttempts = 0u;

        ActiveJob->Result = vSwUpdM_Module_GetStateByPartition(&moduleState, moduleId, partitionId);

        if (ActiveJob->Result == E_OK)
        {
          ActiveJob->Result = vSwUpdM_Module_GetProgrammingAttemptsByPartition(&moduleAttempts, moduleId, partitionId);
        }

        if (ActiveJob->Result == E_OK)
        {
          vSwUpdM_RegionIterType            regionIdx;
          vSwUpdM_ProgrammingAttemptsType   maxAttempts = 0u;

          /* #210 Determine maximum programming attempts of all regions. */
          for (regionIdx = 0u; regionIdx < vSwUpdM_GetNRegionsOfModule(moduleId); regionIdx++)
          {
            vSwUpdM_VarRegionsPtrType region = vSwUpdM_GetAddrVarRegions(regionIdx); /* PRQA S 3679 */ /* MD_vSwUpdM_Rule8.13_3679_PointerToModifiableData */

            if (region->DynamicAttributesOfVarRegion.ProgrammingAttempts > maxAttempts)
            {
              maxAttempts = region->DynamicAttributesOfVarRegion.ProgrammingAttempts;
            }
          }

          /* #220 If maximum value is larger than programming attempts counter of module instance */
          if (maxAttempts > moduleAttempts)
          {
            /* #221 Set programming attempts of module instance to maximum value. */
            ActiveJob->Result = vSwUpdM_Module_UpdateProgrammingAttempts(maxAttempts, partitionId, moduleId);

            /* #222 Trigger persisting of changed value. */
            if (ActiveJob->Result == E_OK)
            {
              (void)vSwUpdM_Module_UpdateAndPersistState(partitionId, ActiveJob->EntityIds.PartitionState, moduleId, moduleState, ActiveJob, ActiveJob->Source);
            }
          }
          /* #230 If maximum value is smaller than programming attempts counter of module instance */
          else if (maxAttempts < moduleAttempts)
          {
            Std_ReturnType                  spawnResult;
            vSwUpdM_JobPtrType              spawnedJob;
            /* #231 Increment programming attempts of all regions by difference to module value. */
            vSwUpdM_ProgrammingAttemptsType diff = moduleAttempts - maxAttempts;

            for (regionIdx = 0u; regionIdx < vSwUpdM_GetNRegionsOfModule(moduleId); regionIdx++)
            {
              vSwUpdM_VarRegionsPtrType region = vSwUpdM_GetAddrVarRegions(regionIdx); /* PRQA S 3679 */ /* MD_vSwUpdM_Rule8.13_3679_PointerToModifiableData */

              vSwUpdM_Region_UpdateProgrammingAttempts((vSwUpdM_RegionIdxType)regionIdx, region->DynamicAttributesOfVarRegion.ProgrammingAttempts + diff);
            }

            /* #232 Enter critical section to ensure exclusive access of state and job queue. */
            VSWUPDM_ENTER_CRITICAL_SECTION();

            /* #233 Spawn job to persist changed programming counters. */
            spawnedJob = vSwUpdM_Job_Spawn(&spawnResult, VSWUPDM_JOB_TYPE_PERSIST_ALL_REGION_STATES, VSWUPDM_JOB_OPERATION_DEFAULT, (vSwUpdM_QueuePrioType)VSWUPDM_JOB_PRIO_DEFAULT, VSWUPDM_SID_NONE, ActiveJob, ActiveJob->Source);

            /* #234 Job attributes are safe to be modified when job was successfully spawned and access is still protected by critical section. */
            if (spawnResult == E_OK)
            {
              spawnedJob->EntityIds = ActiveJob->EntityIds;
            }

            /* #235 Leave critical section ensuring exclusive access of state and job queue. */
            VSWUPDM_LEAVE_CRITICAL_SECTION();
          }
          else
          {
            /* Values match: Nothing to do. */
          }

          /* #240 Forward state to initialize segments of module next. */
          ActiveJob->State = VSWUPDM_JOB_STATE_OPEN_MODULE_INIT_SEGMENTS;
        }

        break;
      }
      case VSWUPDM_JOB_STATE_OPEN_MODULE_INIT_SEGMENTS:
      /* #300 If segments of module shall be initialized */
      {
        vSwUpdM_ModuleStateType moduleState;

        /* #310 Evaluate state of module instance in the requested partition. */
        ActiveJob->Result = vSwUpdM_Module_GetStateByPartition(&moduleState, moduleId, partitionId);

        if (ActiveJob->Result == E_OK)
        {
          boolean                     moduleDirty = FALSE;
          vSwUpdM_RestoreSegmentsType restoreSegments = VSWUPDM_RESTORE_SEGMENTS_NONE;

          switch (moduleState)
          {
            case VSWUPDM_MODULE_STATE_DIRTY:
            case VSWUPDM_MODULE_STATE_RESTART:
            /* #320 If module state is "dirty" or "restart" */
            {
              /* #321 and resume information indicates service ProcessStreamData or FinalizeModule was interrupted */
              if ( (vSwUpdM_ResumeInfo.ResumeInfo.CurrentService == VSWUPDM_SID_PROCESS_STREAM_DATA)
                || (vSwUpdM_ResumeInfo.ResumeInfo.CurrentService == VSWUPDM_SID_FINALIZE_MODULE) )
              {
                /* #322 Update of module may be interrupted by unintended shutdown and recovery could be required. */
                moduleDirty = TRUE;
              }

              break;
            }
            case VSWUPDM_MODULE_STATE_SYNC_DIRTY:
            /* #330 If module state is "sync dirty" */
            {
              /* #331 and resume information indicates service SyncModule or SyncPartition was interrupted */
              if ( (vSwUpdM_ResumeInfo.ResumeInfo.CurrentService == VSWUPDM_SID_SYNC_MODULE)
                || (vSwUpdM_ResumeInfo.ResumeInfo.CurrentService == VSWUPDM_SID_SYNC_PARTITION) )
              {
                /* #332 Sync of module may be interrupted by unintended shutdown and recovery could be required. */
                moduleDirty = TRUE;
              }

              break;
            }
#if (VSWUPDM_FINE_GRAINED_RESUME == STD_ON)
            case VSWUPDM_MODULE_STATE_CLEAN:
            case VSWUPDM_MODULE_STATE_FINALIZED:
            /* #340 If module state is "clean" or "finalized" */
            {
              /* #341 and resume information indicates service ProcessStreamData was interrupted */
              if (vSwUpdM_ResumeInfo.ResumeInfo.CurrentService == VSWUPDM_SID_PROCESS_STREAM_DATA)
              {
                /* #342 Update of module may be interrupted by unintended shutdown and recovery could be required. */
                moduleDirty = TRUE;
              }

              break;
            }
#endif
            default:
            /* #350 Otherwise: Module is clean. */
            {
              break;
            }
          }

          /* #360 If recovery of current module could be required */
          if (moduleDirty == TRUE)
          {
            moduleDirty = FALSE;

            /* #361 and resume information indicates an active service was interrupted */
            if ( (vSwUpdM_ResumeInfo.ResumeInfo.ServiceState == VSWUPDM_RESUME_STATE_ACTIVE)
              && (vSwUpdM_ResumeInfo.ResumeInfo.IsAddressValid == TRUE) )
            {
              /* #362 and entities derived from resume information match the current module
                *   Processing of module was actually interrupted by unintended shutdown and recovery is actually required. */
              if (vSwUpdM_ResumeInfo_CompareEntities(&ActiveJob->EntityIds) == FALSE)
              {
                moduleDirty = TRUE;
              }
            }
          }

          /* #370 If job operation request that previously persisted segment information shall be restored */
          if (ActiveJob->Operation == VSWUPDM_JOB_OPERATION_OPEN_MODULE_RESTORE_SEGMENTS)
          {
            /* #371 If recovery from unintended shutdown is required
              *   Keep restored states of segments. */
            if (moduleDirty == TRUE)
            {
#if (VSWUPDM_FINE_GRAINED_RESUME == STD_ON)
              restoreSegments = VSWUPDM_RESTORE_SEGMENTS_KEEP_STATE;
#else
              restoreSegments = VSWUPDM_RESTORE_SEGMENTS_FIRST;
#endif
            }
            /* #373 Otherwise
              *   Restore all persisted segments. */
            else
            {
              restoreSegments = VSWUPDM_RESTORE_SEGMENTS_FULL;
            }
          }

          /* #380 Trigger initialization of segments of requested module. */
          (void)vSwUpdM_Module_InitSegments(restoreSegments, TRUE, VSWUPDM_SID_NONE, ActiveJob, ActiveJob->Source);

          /* #390 If recovery from unintended shutdown is required
            *   Forward state to perform cleanup of module. */
          if (moduleDirty == TRUE)
          {
            ActiveJob->State = VSWUPDM_JOB_STATE_OPEN_MODULE_CLEANUP;
          }
          /* #391 Otherwise
           *   Forward to final state, waiting for the result of the segment initialization. */
          else
          {
            ActiveJob->State = VSWUPDM_JOB_STATE_FINAL;
          }
        }

        break;
      }
#if (VSWUPDM_FINE_GRAINED_RESUME == STD_ON)
      /* #400 If fine-grained resume is enabled */
      case VSWUPDM_JOB_STATE_OPEN_MODULE_CLEANUP:
      /* #410 If cleanup of module shall be performed */
      {
        Std_ReturnType spawnResult;
        vSwUpdM_JobPtrType spawnedJob;

        /* #420 Enter critical section to ensure exclusive access of state and job queue. */
        VSWUPDM_ENTER_CRITICAL_SECTION();

        /* #430 Spawn job to persist module state. */
        spawnedJob = vSwUpdM_Job_Spawn(&spawnResult, VSWUPDM_JOB_TYPE_CLEANUP_MODULE, VSWUPDM_JOB_OPERATION_DEFAULT, (vSwUpdM_QueuePrioType)VSWUPDM_JOB_PRIO_DEFAULT, VSWUPDM_SID_NONE, ActiveJob, ActiveJob->Source);

        /* #440 Job attributes are safe to be modified when job was successfully spawned and access is still protected by critical section. */
        if (spawnResult == E_OK)
        {
          spawnedJob->EntityIds = ActiveJob->EntityIds;
        }

        /* #450 Leave critical section ensuring exclusive access of state and job queue. */
        VSWUPDM_LEAVE_CRITICAL_SECTION();

        /* #460 Forward state to update state of module next. */
        ActiveJob->State = VSWUPDM_JOB_STATE_OPEN_MODULE_UPDATE_STATE;

        break;
      }
      case VSWUPDM_JOB_STATE_OPEN_MODULE_UPDATE_STATE:
      /* #500 If module state shall be updated */
      {
        vSwUpdM_ModuleStateType moduleState;

        /* #510 Evaluate state of module instance in the requested partition. */
        ActiveJob->Result = vSwUpdM_Module_GetStateByPartition(&moduleState, moduleId, partitionId);

        if (ActiveJob->Result == E_OK)
        {
          /* #520 If module state is "sync dirty"
           *   Set module state to "sync clean". */
          if (moduleState == VSWUPDM_MODULE_STATE_SYNC_DIRTY)
          {
            moduleState = VSWUPDM_MODULE_STATE_SYNC_CLEAN;
          }
          /* #530 Otherwise: Set module state to "clean". */
          else
          {
            moduleState = VSWUPDM_MODULE_STATE_CLEAN;
          }

          /* #540 Set module state and trigger persisting. */
          (void)vSwUpdM_Module_UpdateAndPersistState(partitionId, ActiveJob->EntityIds.PartitionState, moduleId, moduleState, ActiveJob, ActiveJob->Source);

          /* #550 Restart opening of module to take segment changes caused by cleanup into account. */
          ActiveJob->State = VSWUPDM_JOB_STATE_INITIAL;
        }

        break;
      }
#else
      /* #600 If fine-grained resume is disabled */
      case VSWUPDM_JOB_STATE_OPEN_MODULE_CLEANUP:
      /* #610 If cleanup of module shall be performed */
      {
        /* #620 Trigger erasing of requested module to re-establish a known good state.
         *   Use a higher priority than active job. */
        (void)vSwUpdM_Module_EraseModule(ActiveJob->EntityIds.ModuleId, (ActiveJob->CurrentPrio + 1u), FALSE, ActiveJob, ActiveJob->Source);

        /* #630 Forward to final state, waiting for the result of the cleanup. */
        ActiveJob->State = VSWUPDM_JOB_STATE_FINAL;

        break;
      }
#endif
      case VSWUPDM_JOB_STATE_FINAL:
      /* #700 If waiting for result of final operation
       *   Indicate that job is finished. */
      {
        /* #710 Set ID of opened module and point to module in entity data structure. */
        vSwUpdM_EntityData.OpenIds.ModuleId = moduleId;
        vSwUpdM_EntityData.OpenObjects.Module = vSwUpdM_GetAddrVarModules(moduleId);

        /* #720 Reset stream data. */
        vSwUpdM_Init_ResetStreamData();

        retVal = VSWUPDM_JOB_STATUS_FINISHED;

        break;
      }
      case VSWUPDM_JOB_STATE_FAILED:
      /* #800 If job state is "failed", because of negative child result
       *   Return with negative result taken over from child job. */
      {
        break;
      }
      default:
      /* #900 Otherwise: Invalid state.
       *   Set error in job result. */
      {
        ActiveJob->Result = VSWUPDM_E_INV_STATE;
        break;
      }
    }
  }

  return retVal;
  /* PRQA S 6010, 6030, 6050, 6080 1 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */
} /* vSwUpdM_JobHandler_OpenModuleLocal */

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_CleanupModule
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
 *
 *
 *
 *
 */
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_CleanupModule) /* PRQA S 3673 */ /* MD_vSwUpdM_Rule8.13_3673_PointerToConstParameter */
{
#if (VSWUPDM_FINE_GRAINED_RESUME == STD_ON)
  vSwUpdM_JobStatusType       retVal      = VSWUPDM_JOB_STATUS_PENDING;
  vSwUpdM_PartitionIdType     partitionId = ActiveJob->EntityIds.PartitionId;
  vSwUpdM_RegionIdxType       regionIdx   = 0u;
  vSwUpdM_SegmentIdValueType  segmentId   = 0u;
  vSwUpdM_VarRegionsPtrType   region;  /* PRQA S 3679 */ /* MD_vSwUpdM_Rule8.13_3679_PointerToModifiableData */
  vSwUpdM_VarSegmentsPtrType  segment; /* PRQA S 3679 */ /* MD_vSwUpdM_Rule8.13_3679_PointerToModifiableData */

  VSWUPDM_DUMMY_STATEMENTS_JOB_HANDLER(); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  /* #10 Region and segment accessed in multiple states.
   *   Region index and segment ID not initialized in initial state yet. */
  if (ActiveJob->State != VSWUPDM_JOB_STATE_INITIAL)
  {
    regionIdx = ActiveJob->EntityIds.RegionIdx;
    segmentId = ActiveJob->EntityIds.SegmentId.DynamicSegmentId;
  }

  region  = vSwUpdM_GetAddrVarRegions(regionIdx);
  segment = vSwUpdM_GetAddrVarSegments(segmentId);

  /* #20 Evaluate child result from previous cycle. */
  (void)vSwUpdM_Job_EvaluateAndApplyChildResult(ActiveJob, FALSE);

  /* #30 Evaluate job state. */
  switch (ActiveJob->State)
  {
    case VSWUPDM_JOB_STATE_INITIAL:
    /* #100 If initial conditions for first actual phase shall be established */
    {
      vSwUpdM_SegmentIdValueType  firstSegmentId = 0u;

      /* #110 Evaluate first segment affected by resume address. */
      (void)vSwUpdM_Segment_SearchSegment(&firstSegmentId, vSwUpdM_ResumeInfo.ResumeInfo.MemoryAddress);

      /* #120 Use segment index of job entity IDs to store external segment index of first affected segment.
       *   Determines order in which external segments were added. */
      ActiveJob->EntityIds.SegmentIdx = vSwUpdM_GetVarSegments(firstSegmentId).ExternalSegmentIdx;
      /* #130 Iterate over all regions of affected module, starting at last one. */
      ActiveJob->EntityIds.RegionIdx  = (vSwUpdM_RegionIdxType)vSwUpdM_GetNRegionsOfModule(ActiveJob->EntityIds.ModuleId) - 1u;

      /* #140 If the first affected segment is a free segment
       *   Remark: Such a free segment can only be located at the very beginning of a region.
       *   Otherwise at least one used segment would be affected. */
      if (vSwUpdM_GetVarSegments(firstSegmentId).ClassOfVarSegments == VSWUPDM_CLASS_OF_VAR_SEGMENTS_FREE)
      {
        /* #141 Start memory sweep at current segment. */
        ActiveJob->EntityIds.SegmentId.DynamicSegmentId = firstSegmentId;
        /* #142 Only region in which free segment is located is affected. */
        ActiveJob->EntityIds.RegionIdx                  = vSwUpdM_GetVarSegments(firstSegmentId).RegionIdxOfVarSegments;

        /* #143 Forward job state to evaluate affected memory ranges next. */
        ActiveJob->State = VSWUPDM_JOB_STATE_CLEANUP_MODULE_SWEEP_EVALUATE;
      }
      else
      /* #150 Otherwise:
       *   Forward job state to start sweep over first region. */
      {
        ActiveJob->State = VSWUPDM_JOB_STATE_CLEANUP_MODULE_SWEEP_START;
      }

      retVal = VSWUPDM_JOB_STATUS_ACTIVE;

      break;
    }
    case VSWUPDM_JOB_STATE_CLEANUP_MODULE_SWEEP_START:
    /* #200 If sweep over region shall be started */
    {
      vSwUpdM_SegmentIdValueType  localSegmentId = VSWUPDM_INVALID_ID;

      /* #210 Start sweep with segment at end of current region. */
      (void)vSwUpdM_Segment_SearchSegment(&localSegmentId, region->EndAddressOfVarRegions);
      ActiveJob->EntityIds.SegmentId.DynamicSegmentId = localSegmentId;

      /* #220 Forward job state to evaluate affected memory ranges next. */
      ActiveJob->State = VSWUPDM_JOB_STATE_CLEANUP_MODULE_SWEEP_EVALUATE;
      retVal           = VSWUPDM_JOB_STATUS_ACTIVE;

      break;
    }
    case VSWUPDM_JOB_STATE_CLEANUP_MODULE_SWEEP_EVALUATE:
    /* #300 If affected memory ranges shall be evaluated. */
    {
      vSwUpdM_SegmentIdValueType triggerSegmentId = VSWUPDM_INVALID_ID;

      /* #310 Default to continue with next segment. */
      ActiveJob->State = VSWUPDM_JOB_STATE_CLEANUP_MODULE_SWEEP_NEXT;
      retVal           = VSWUPDM_JOB_STATUS_ACTIVE;

      /* #311 Evaluate segment (written last) which triggered the persisting of the resume information. */
      (void)vSwUpdM_Segment_SearchSegment(&triggerSegmentId, vSwUpdM_ResumeInfo.TriggerAddress);

      /* #320 If the current segment is any of the following:
       *   - The first affected segment (same external segment index).
       *   - An external segment which was added before the first affected segment.
       *   - The triggering segment.
       *   => Segment is potentially affected by cleanup. */
      if ( (segment->ExternalSegmentIdx == ActiveJob->EntityIds.SegmentIdx)
        || ( (segment->ExternalSegmentIdx != VSWUPDM_INVALID_ID)
          && (segment->ExternalSegmentIdx >= ActiveJob->EntityIds.SegmentIdx) )
        || (segmentId == triggerSegmentId) )
      {
        vSwUpdM_AddressType firstAffectedAddress;
        vSwUpdM_AddressType lastAffectedAddress;

        /* #330 If the current segment is the first affected segment
         *   The first affected address is the resume address. */
        if (segment->ExternalSegmentIdx == ActiveJob->EntityIds.SegmentIdx)
        {
          firstAffectedAddress = vSwUpdM_ResumeInfo.ResumeInfo.MemoryAddress;
        }
        /* #331 Otherwise, if the current segment is the triggering free segment
         *   The first affected address is the write address of the segment. */
        else if (segment->ClassOfVarSegments == VSWUPDM_CLASS_OF_VAR_SEGMENTS_FREE)
        {
          firstAffectedAddress = segment->WriteAddressOfVarSegments;
        }
        /* #332 Otherwise:
         *   The first affected address is the reserved start address of the segment. */
        else
        {
          firstAffectedAddress = segment->ReservedStartAddressOfVarSegments;
        }

        /* #340 If the current segment is the triggering segment. */
        if (segmentId == triggerSegmentId)
        {
          vSwUpdM_AddressType reservedEndAddress = segment->ReservedEndAddressOfVarSegments;

          /* #341 The last affected address is either the address before the next checkpoint
           *   behind the current write address of the segment... */
          vSwUpdM_ResumeInfo_GetCheckpointAddress(&lastAffectedAddress, segment->WriteAddressOfVarSegments, partitionId);
          if ( (lastAffectedAddress != VSWUPDM_MAX_ADDRESS)
            && (lastAffectedAddress > 0u) )
          {
            lastAffectedAddress--;
          }

          /* #342 ...or the reserved end address of the segment, whichever comes first. */
          if (reservedEndAddress < lastAffectedAddress)
          {
            lastAffectedAddress = reservedEndAddress;
          }
        }
        /* #350 Otherwise: */
        else
        {
          /* #351 If segment is already partially written
           *   The last affected address is the last written address. */
          if (segment->WriteAddressOfVarSegments > segment->DynamicAttributesOfVarSegment.StartAddress)
          {
            lastAffectedAddress = segment->WriteAddressOfVarSegments - 1u;
          }
          /* #352 Otherwise:
           *   No cleanup necessary for this segment. Indicated by setting last affected address equal to first one. */
          else
          {
            lastAffectedAddress = firstAffectedAddress;
          }
        }

        /* #360 If any cleanup is necessary */
        if (lastAffectedAddress > firstAffectedAddress)
        {
          /* #361 Align first and last affected address to front or back of sector respectively. */
          (void)vSwUpdM_Range_AlignAddress(&firstAffectedAddress, partitionId, VSWUPDM_ADDRESS_ALIGNMENT_FRONT, VSWUPDM_ALIGN_GRANULARITY_SECTOR);
          (void)vSwUpdM_Range_AlignAddress(&lastAffectedAddress, partitionId, VSWUPDM_ADDRESS_ALIGNMENT_BACK, VSWUPDM_ALIGN_GRANULARITY_SECTOR);

          if (lastAffectedAddress > firstAffectedAddress)
          {
            /* #362 Perform cleanup by erasing potentially affected memory range. */
            vSwUpdM_LengthType eraseLength = (lastAffectedAddress - firstAffectedAddress) + 1u;

            /* #363 Check whether programming attempts were exceeded. */
            ActiveJob->Result = vSwUpdM_Region_CheckProgrammingAttempts(ActiveJob->EntityIds.ModuleId, regionIdx);

            if (ActiveJob->Result == E_OK)
            {
              /* #364 Change state of current region to "dirty". */
              (void)vSwUpdM_Region_UpdateAndPersistState(partitionId, ActiveJob->EntityIds.ModuleId, regionIdx, VSWUPDM_REGION_STATE_DIRTY, ActiveJob, ActiveJob->Source);

              /* #365 Forward job state to erase affected memory range next. */
              ActiveJob->TargetAddress = firstAffectedAddress;
              ActiveJob->PendingLength = eraseLength;
              ActiveJob->State         = VSWUPDM_JOB_STATE_CLEANUP_MODULE_SWEEP_ERASE;
              retVal                   = VSWUPDM_JOB_STATUS_PENDING;
            }
          }
        }
      }

      break;
    }
    case VSWUPDM_JOB_STATE_CLEANUP_MODULE_SWEEP_ERASE:
    /* #370 If affected memory range shall be erased */
    {
      /* #371 Perform cleanup by erasing potentially affected memory range. */
      ActiveJob->Result = vSwUpdM_Range_EraseRange(partitionId, ActiveJob->EntityIds.PartitionState, ActiveJob->TargetAddress, ActiveJob->PendingLength, VSWUPDM_SID_NONE, ActiveJob, ActiveJob->Source);
      /* #372 Forward job state to update segment states next. */
      ActiveJob->State  = VSWUPDM_JOB_STATE_CLEANUP_MODULE_SWEEP_UPDATE;

      break;
    }
    case VSWUPDM_JOB_STATE_CLEANUP_MODULE_SWEEP_UPDATE:
    /* #400 If segment states shall be updated. */
    {
      /* #410 Sweep over erased memory range, starting at last affected address. */
      vSwUpdM_AddressType         firstAffectedAddress = ActiveJob->TargetAddress;
      vSwUpdM_AddressType         rangeSweepAddress    = firstAffectedAddress + (ActiveJob->PendingLength - 1u);
      vSwUpdM_SegmentIdValueType  affectedSegmentId    = segmentId;
      boolean                     attributesDirty      = FALSE;

      /* #411 Default to continue with next segment. */
      ActiveJob->State = VSWUPDM_JOB_STATE_CLEANUP_MODULE_SWEEP_NEXT;

      /* #412 Sweep over erased memory range, ending at first affected address. */
      while (rangeSweepAddress > firstAffectedAddress)
      {
        vSwUpdM_VarSegmentsPtrType affectedSegment;

        /* #420 Evaluate segment at current sweep address. */
        (void)vSwUpdM_Segment_SearchSegment(&affectedSegmentId, rangeSweepAddress);
        affectedSegment = vSwUpdM_GetAddrVarSegments(affectedSegmentId);

        switch (affectedSegment->ClassOfVarSegments)
        {
          case VSWUPDM_CLASS_OF_VAR_SEGMENTS_USED:
          case VSWUPDM_CLASS_OF_VAR_SEGMENTS_FREE:
          /* #421 If segment represents a free memory area or is used for updated data */
          {
            /* #430 If current segment was written up to or behind first affected address */
            if (affectedSegment->WriteAddressOfVarSegments >= firstAffectedAddress)
            {
              /* #431 If reserved start address of current segment is located in front of first affected address
               *   Set segment state to "pending" and truncate written range to first affected address. */
              if (affectedSegment->ReservedStartAddressOfVarSegments < firstAffectedAddress)
              {
                (void)vSwUpdM_Segment_UpdateState(affectedSegment, VSWUPDM_SEGMENT_STATE_PENDING);
                (void)vSwUpdM_Segment_UpdateWriteAddress(affectedSegment, firstAffectedAddress);
              }
              /* #432 Otherwise:
               *   Set segment state to "erased" and reset write address to reserved start address of segment. */
              else
              {
                (void)vSwUpdM_Segment_UpdateState(affectedSegment, VSWUPDM_SEGMENT_STATE_ERASED);
                (void)vSwUpdM_Segment_UpdateWriteAddress(affectedSegment, affectedSegment->ReservedStartAddressOfVarSegments);
              }
            }
            /* #440 Otherwise:
             *   Set segment state to "pending". */
            else
            {
              (void)vSwUpdM_Segment_UpdateState(affectedSegment, VSWUPDM_SEGMENT_STATE_PENDING);
            }

            /* #450 If attributes or write address were changed
             *   Remember that attributes of at least one segment are "dirty". */
            if ( (affectedSegment->AttributesDirty == TRUE)
              || (affectedSegment->WriteAddressDirty == TRUE) )
            {
              attributesDirty = TRUE;
            }

            /* #460 If current segment isn't located at the end of the address space. */
            if (affectedSegment->ReservedEndAddressOfVarSegments < VSWUPDM_MAX_ADDRESS)
            {
              vSwUpdM_SegmentIdValueType freeSegmentId = VSWUPDM_INVALID_ID;
              vSwUpdM_VarSegmentsPtrType freeSegment;

              /* #461 Evaluate segment directly following the current segment. */
              ActiveJob->Result = vSwUpdM_Segment_SearchSegment(&freeSegmentId, affectedSegment->ReservedEndAddressOfVarSegments + 1u);
              if (ActiveJob->Result == E_OK)
              {
                freeSegment = vSwUpdM_GetAddrVarSegments(freeSegmentId);

                /* #462 If this segment is used to represent a free memory area
                 *   Set state of this segment to "erased" as well.
                 *   Clear dirty flag of write address, as not separately stored for free segment. */
                if (freeSegment->ClassOfVarSegments == VSWUPDM_CLASS_OF_VAR_SEGMENTS_FREE)
                {
                  (void)vSwUpdM_Segment_UpdateState(freeSegment, VSWUPDM_SEGMENT_STATE_ERASED);
                  freeSegment->WriteAddressDirty = FALSE;
                }
              }
            }

            break;
          }
          default:
          /* #470 Otherwise:
           *   Nothing to be done. */
          {
            break;
          }
        }

        /* #480 Unless current segment is located at the very beginning of the address space,
         *   set sweep address to address directly before reserved start address of current segment.
         *   Otherwise, use unaltered start address. */
        rangeSweepAddress = affectedSegment->ReservedStartAddressOfVarSegments;

        if (rangeSweepAddress > 0u)
        {
          rangeSweepAddress--;
        }
      }

      /* #490 If a segment different from the one which triggered the erasing was affected
       *   Re-evaluate affected memory ranges with current segment. */
      if (segmentId != affectedSegmentId)
      {
        ActiveJob->EntityIds.SegmentId.DynamicSegmentId = affectedSegmentId;
        ActiveJob->State                                = VSWUPDM_JOB_STATE_CLEANUP_MODULE_SWEEP_EVALUATE;
      }

      /* #495 If attributes of any segment have changed
       *   Trigger persisting of segment attributes. */
      if (attributesDirty == TRUE)
      {
        (void)vSwUpdM_Segment_PersistState(&ActiveJob->EntityIds, VSWUPDM_SID_NONE, FALSE, ActiveJob, ActiveJob->Source);
      }

      break;
    }
    case VSWUPDM_JOB_STATE_CLEANUP_MODULE_SWEEP_NEXT:
    /* #500 If next segment shall be handled */
    {
      /* #510 If current segment isn't located at the very beginning of the current region */
      if (segment->ReservedStartAddressOfVarSegments > region->StartAddressOfVarRegions)
      {
        /* #511 Evaluate segment directly before the current segment. */
        (void)vSwUpdM_Segment_SearchSegment(&segmentId, (segment->ReservedStartAddressOfVarSegments - 1u));
        ActiveJob->EntityIds.SegmentId.DynamicSegmentId = segmentId;

        /* #512 Forward job state to evaluate affected memory ranges next. */
        ActiveJob->State = VSWUPDM_JOB_STATE_CLEANUP_MODULE_SWEEP_EVALUATE;
        retVal           = VSWUPDM_JOB_STATUS_ACTIVE;
      }
      else
      /* #520 Otherwise, the sweep over the region is finished: */
      {
        /* #530 If current region instance is marked as "dirty"
         *   Increment the programming attempt counter. */
        if (region->DynamicAttributesOfVarRegion.State == VSWUPDM_REGION_STATE_DIRTY)
        {
          ActiveJob->Result = vSwUpdM_Region_IncProgrammingAttempts(ActiveJob->EntityIds.PartitionId, ActiveJob->EntityIds.ModuleId, ActiveJob->EntityIds.RegionIdx);
        }

        if (ActiveJob->Result == E_OK)
        {
          /* #531 Mark current region as "clean". */
          (void)vSwUpdM_Region_UpdateAndPersistState(partitionId, ActiveJob->EntityIds.ModuleId, regionIdx, VSWUPDM_REGION_STATE_CLEAN, ActiveJob, ActiveJob->Source);
        }

        /* #540 Change service state in resume information to "started",
         *   as "active" is an additional trigger for the module cleanup,
         *   even when the module is marked as "clean". */
        vSwUpdM_ResumeInfo.ResumeInfo.ServiceState = VSWUPDM_RESUME_STATE_STARTED;
        vSwUpdM_ResumeInfoDirty                    = TRUE;
        (void)vSwUpdM_ResumeInfo_PersistState(ActiveJob->Source);

        /* #550 If the first affected segment wasn't a free segment at the very beginning of the current region
         *   and the current region isn't the very first one */
        if ( (ActiveJob->EntityIds.SegmentIdx != VSWUPDM_INVALID_ID)
          && (regionIdx > 0u) )
        {
          /* #551 Forward job state to start sweep over next region. */
          ActiveJob->EntityIds.RegionIdx = regionIdx - 1u;
          ActiveJob->State               = VSWUPDM_JOB_STATE_CLEANUP_MODULE_SWEEP_START;
        }
        /* #552 Otherwise:
         *   Forward to final state, waiting for result of updating the region state. */
        else
        {
          ActiveJob->State = VSWUPDM_JOB_STATE_FINAL;
        }
      }

      break;
    }
    case VSWUPDM_JOB_STATE_FINAL:
    /* #600 If waiting for region state to be persisted
     *   Indicate that job is finished. */
    {
      retVal = VSWUPDM_JOB_STATUS_FINISHED;

      break;
    }
    case VSWUPDM_JOB_STATE_FAILED:
    /* #700 If job state is "failed", because of negative child result
     *   Return with negative result taken over from child job. */
    {
      break;
    }
    default:
    /* #800 Otherwise: Invalid state.
     *   Set error in job result. */
    {
      ActiveJob->Result = VSWUPDM_E_INV_STATE;
      break;
    }
  }

  return retVal;
#else
  VSWUPDM_DUMMY_STATEMENTS_JOB_HANDLER(); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  return VSWUPDM_JOB_STATUS_FINISHED;
#endif
  /* PRQA S 6010, 6030, 6050, 6080 1 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */
} /* vSwUpdM_JobHandler_CleanupModule */

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_CloseModuleLocal
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
 *
 *
 *
 *
 *
 *
 */
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_CloseModuleLocal)
{
  vSwUpdM_JobStatusType retVal = VSWUPDM_JOB_STATUS_PENDING;

  VSWUPDM_DUMMY_STATEMENTS_JOB_HANDLER(); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  /* #10 Evaluate child result from previous cycle. */
  (void)vSwUpdM_Job_EvaluateAndApplyChildResult(ActiveJob, FALSE);

  /* #20 Evaluate job state. */
  switch (ActiveJob->State)
  {
    case VSWUPDM_JOB_STATE_INITIAL:
    /* #100 If initial conditions for first actual phase shall be established */
    {
      /* #110 Trigger persisting of any modified segment states. */
      (void)vSwUpdM_Segment_PersistState(&ActiveJob->EntityIds, VSWUPDM_SID_NONE, TRUE, ActiveJob, ActiveJob->Source);

      /* #120 Forward state to wait for result of operation. */
      ActiveJob->State = VSWUPDM_JOB_STATE_PENDING;

      break;
    }
    case VSWUPDM_JOB_STATE_PENDING:
    /* #200 If waiting for persisting of segment states. */
    {
      vSwUpdM_ModuleStateType moduleState;

      /* #210 Evaluate state of module instance in the requested partition. */
      ActiveJob->Result = vSwUpdM_Module_GetStateByPartition(&moduleState, ActiveJob->EntityIds.ModuleId, ActiveJob->EntityIds.PartitionId);

      if (ActiveJob->Result == E_OK)
      {
        switch (moduleState)
        {
          case VSWUPDM_MODULE_STATE_DIRTY:
          /* #220 If module state is "dirty", indicating a previously pending stream operation
           *   Change module state to "clean". */
          {
            moduleState = VSWUPDM_MODULE_STATE_CLEAN;

            break;
          }
          case VSWUPDM_MODULE_STATE_SYNC_DIRTY:
          /* #221 If module state is "sync dirty", indicating a previously pending synchronization operation
           *   Change module state to "sync clean". */
          {
            moduleState = VSWUPDM_MODULE_STATE_SYNC_CLEAN;

            break;
          }
          case VSWUPDM_MODULE_STATE_PROCESS_DIRTY:
          /* #222 If module state is "process dirty", indicating a previously pending processing operation
           *   Change module state to "process clean". */
          {
            moduleState = VSWUPDM_MODULE_STATE_PROCESS_CLEAN;

            break;
          }
          default:
          /* #230 Otherwise
           *   Module state doesn't need to be changed. */
          {
            break;
          }
        }

        /* #240 Update module state if necessary and/or trigger persisting of any pending update. */
        (void)vSwUpdM_Module_UpdateAndPersistState(ActiveJob->EntityIds.PartitionId, ActiveJob->EntityIds.PartitionState, ActiveJob->EntityIds.ModuleId, moduleState, ActiveJob, ActiveJob->Source);

        /* #250 Forward state to wait for result of operation. */
        ActiveJob->State = VSWUPDM_JOB_STATE_FINAL;
      }

      break;
    }
    case VSWUPDM_JOB_STATE_FINAL:
    /* #300 If waiting for result of operation */
    {
      /* #310 Clear ID and pointer of opened module in entity data structure. */
      vSwUpdM_EntityData.OpenIds.ModuleId   = VSWUPDM_INVALID_ID;
      vSwUpdM_EntityData.OpenObjects.Module = NULL_PTR;

      /* #320 Reset region and segment counts */
      vSwUpdM_EntityData.Count.RegionCount          = 0u;
      vSwUpdM_EntityData.Count.InternalSegmentCount = 0u;
      vSwUpdM_EntityData.Count.ExternalSegmentCount = 0u;

      /* #330 Indicate that job is finished. */
      retVal = VSWUPDM_JOB_STATUS_FINISHED;

      break;
    }
    case VSWUPDM_JOB_STATE_FAILED:
    /* #400 If job state is "failed", because of negative child result
     *   Return with negative result taken over from child job. */
    {
      break;
    }
    default:
    /* #500 Otherwise: Invalid state.
     *   Set error in job result. */
    {
      ActiveJob->Result = VSWUPDM_E_INV_STATE;
      break;
    }
  }

  return retVal;
  /* PRQA S 6030 1 */ /* MD_MSR_STCYC */
} /* vSwUpdM_JobHandler_CloseModuleLocal */

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_HandleUpdateState
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
 */
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_HandleUpdateState)
{
  vSwUpdM_JobStatusType    retVal              = VSWUPDM_JOB_STATUS_PENDING;
  vSwUpdM_JobOperationType bookkeeperOperation = VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_NONE;

  VSWUPDM_DUMMY_STATEMENTS_JOB_HANDLER(); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  /* #10 Evaluate job operation. */
  switch (ActiveJob->Operation)
  {
    case VSWUPDM_JOB_OPERATION_DEFAULT:
    /* #100 If default operation is set */
    {
      /* #110 Evaluate child result from previous cycle. */
      (void)vSwUpdM_Job_EvaluateAndApplyChildResult(ActiveJob, FALSE);

      /* #120 Indicate that job is finished. */
      retVal = VSWUPDM_JOB_STATUS_FINISHED;

      break;
    }
    case VSWUPDM_JOB_OPERATION_HANDLE_UPDATE_STATE_GET:
    /* #200 If persisted update state shall be evaluated */
    {
      /* #210 Trigger bookkeeper to get the update state. */
      bookkeeperOperation = VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_GET_UPDATE_STATE;
      break;
    }
    case VSWUPDM_JOB_OPERATION_HANDLE_UPDATE_STATE_SET:
    /* #300 If update state shall be persisted */
    {
      /* #310 Trigger bookkeeper to set the update state. */
      bookkeeperOperation = VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_SET_UPDATE_STATE;
      break;
    }
    default:
    /* #400 Otherwise: Invalid state.
     *   Set error in job result. */
    {
      ActiveJob->Result = VSWUPDM_E_INV_STATE;
      break;
    }
  }

  /* #1000 If any bookkeeper operation shall be triggered */
  if (bookkeeperOperation != VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_NONE)
  {
    /* #1010 Trigger bookkeeper.
     *   Result will be evaluated during next job cycle (indicated by default operation). */
    ActiveJob->Operation = VSWUPDM_JOB_OPERATION_DEFAULT;

    retVal = vSwUpdM_Job_TriggerBookkeeper(bookkeeperOperation, ActiveJob);
  }

  return retVal;
} /* vSwUpdM_JobHandler_HandleUpdateState */

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_HandleResumeInfo
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
 */
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_HandleResumeInfo)
{
  vSwUpdM_JobStatusType    retVal              = VSWUPDM_JOB_STATUS_PENDING;
  vSwUpdM_JobOperationType bookkeeperOperation = VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_NONE;

  VSWUPDM_DUMMY_STATEMENTS_JOB_HANDLER(); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  /* #10 Evaluate job operation. */
  switch (ActiveJob->Operation)
  {
    case VSWUPDM_JOB_OPERATION_DEFAULT:
    /* #100 If default operation is set */
    {
      /* #110 Evaluate child result from previous cycle. */
      (void)vSwUpdM_Job_EvaluateAndApplyChildResult(ActiveJob, FALSE);

      /* #120 Indicate that job is finished. */
      retVal = VSWUPDM_JOB_STATUS_FINISHED;

      break;
    }
    case VSWUPDM_JOB_OPERATION_HANDLE_RESUME_INFO_GET:
    /* #200 If persisted resume information shall be evaluated */
    {
      /* #210 Trigger bookkeeper to get the resume information. */
      bookkeeperOperation = VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_GET_RESUME_INFO;
      break;
    }
    case VSWUPDM_JOB_OPERATION_HANDLE_RESUME_INFO_SET:
    /* #300 If resume information shall be persisted */
    {
      /* #310 Trigger bookkeeper to set the resume information. */
      bookkeeperOperation = VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_SET_RESUME_INFO;
      break;
    }
    default:
    /* #400 Otherwise: Invalid state.
     *   Set error in job result. */
    {
      ActiveJob->Result = VSWUPDM_E_INV_STATE;
      break;
    }
  }

  /* #1000 If any bookkeeper operation shall be triggered */
  if (bookkeeperOperation != VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_NONE)
  {
    /* #1010 Trigger bookkeeper.
     *   Result will be evaluated during next job cycle (indicated by default operation). */
    ActiveJob->Operation = VSWUPDM_JOB_OPERATION_DEFAULT;

    retVal = vSwUpdM_Job_TriggerBookkeeper(bookkeeperOperation, ActiveJob);
  }

  return retVal;
} /* vSwUpdM_JobHandler_HandleResumeInfo */

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_PartitionValidityLocal
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
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_PartitionValidityLocal)
{
  vSwUpdM_JobStatusType retVal = VSWUPDM_JOB_STATUS_PENDING;

  VSWUPDM_DUMMY_STATEMENTS_JOB_HANDLER(); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  /* #10 Evaluate job state. */
  switch (ActiveJob->State)
  {
    case VSWUPDM_JOB_STATE_INITIAL:
    /* #100 If initial operation shall be triggered */
    {
      /* #110 Trigger persisting of all pending partition states. */
      (void)vSwUpdM_Part_PersistState(VSWUPDM_SID_NONE, ActiveJob);

      /* #120 Forward state to wait for result of operation. */
      ActiveJob->State = VSWUPDM_JOB_STATE_PENDING;

      break;
    }
    case VSWUPDM_JOB_STATE_PENDING:
    /* #200 If waiting for result of operation */
    {
      /* #210 Evaluate child result from previous cycle. */
      (void)vSwUpdM_Job_EvaluateAndApplyChildResult(ActiveJob, FALSE);

      /* #220 Indicate that job is finished. */
      retVal = VSWUPDM_JOB_STATUS_FINISHED;

      break;
    }
    default:
    /* #300 Otherwise: Invalid state.
     *   Set error in job result. */
    {
      ActiveJob->Result = VSWUPDM_E_INV_STATE;

      break;
    }
  }

  return retVal;
} /* vSwUpdM_JobHandler_PartitionValidityLocal */

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_CheckPartitionConsistency
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_CheckPartitionConsistency)
{
  /* #100 Simply return success. */
  vSwUpdM_JobStatusType retVal = VSWUPDM_JOB_STATUS_FINISHED;

  VSWUPDM_DUMMY_STATEMENTS_JOB_HANDLER(); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  ActiveJob->State = VSWUPDM_JOB_STATE_FINAL;

  return retVal;
} /* vSwUpdM_JobHandler_CheckPartitionConsistency */

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_PersistPartitionState
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
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_PersistPartitionState)
{
  vSwUpdM_JobStatusType         retVal = VSWUPDM_JOB_STATUS_PENDING;
  vSwUpdM_VarPartitionsPtrType  partition;

  VSWUPDM_DUMMY_STATEMENTS_JOB_HANDLER(); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  /* #10 Evaluate child result from previous cycle. */
  (void)vSwUpdM_Job_EvaluateAndApplyChildResult(ActiveJob, FALSE);

  /* #100 If initial conditions for first actual phase shall be established */
  if (ActiveJob->State == VSWUPDM_JOB_STATE_INITIAL)
  {
    /* #110 Start with attributes of first partition. */
    ActiveJob->EntityIds.PartitionId = 0u;
    partition = vSwUpdM_GetAddrVarPartitions(ActiveJob->EntityIds.PartitionId);

    ActiveJob->State = VSWUPDM_JOB_STATE_PENDING;
  }
  /* #200 Otherwise */
  else
  {
    partition = vSwUpdM_GetAddrVarPartitions(ActiveJob->EntityIds.PartitionId);
    ActiveJob->EntityIds.PartitionState = partition->AffectedState;

    /* #210 Evaluate job operation set during previous cycle. */
    switch (ActiveJob->Operation)
    {
      case VSWUPDM_JOB_OPERATION_DEFAULT:
      /* #220 If default operation is set
       *   Nothing to be done. */
      {
        break;
      }
      case VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_SET_PARTITION_STATE:
      /* #230 If state of the current partition was persisted
       *   Take over pending value to become effective. */
      {
        partition->DynamicAttributesOfVarPartitions.State = partition->PendingAttributesOfVarPartitions.State;

        break;
      }
      case VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_SET_PARTITION_REVISION:
      /* #240 If revision of the current partition was persisted
       *   Take over pending value to become effective. */
      {
        partition->DynamicAttributesOfVarPartitions.Revision = partition->PendingAttributesOfVarPartitions.Revision;

        break;
      }
      case VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_SET_PARTITION_VALID:
      /* #250 If validity of the current partition was persisted
       *   Take over pending value to become effective. */
      {
        partition->DynamicAttributesOfVarPartitions.IsValid = partition->PendingAttributesOfVarPartitions.IsValid;

        /* #260 If current partition is invalid
         *   Mark revision as invalid */
        if (partition->DynamicAttributesOfVarPartitions.IsValid == FALSE)
        {
          partition->DynamicAttributesOfVarPartitions.Revision = VSWUPDM_INVALID_REVISION;
          partition->PendingAttributesOfVarPartitions.Revision = VSWUPDM_INVALID_REVISION;
        }

        break;
      }
      default:
      /* Otherwise: Unknown operation, report error. */
      {
        ActiveJob->Result = VSWUPDM_E_INV_STATE;

        break;
      }
    }
  }

  /* #300 If attributes of current partition are marked as dirty
   *   Evaluate which of the pending attributes differ from the attributes currently in effect. */
  if (partition->AttributesDirty == TRUE)
  {
    /* #310 If the pending state differs from the current state
     *   Trigger bookkeeper to persist the state of the current partition. */
    if (partition->DynamicAttributesOfVarPartitions.State != partition->PendingAttributesOfVarPartitions.State)
    {
      ActiveJob->Operation = VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_SET_PARTITION_STATE;
    }
    /* #320 If the pending revision differs from the current revision
     *   Trigger bookkeeper to persist the revision of the current partition. */
    else if (partition->DynamicAttributesOfVarPartitions.Revision != partition->PendingAttributesOfVarPartitions.Revision)
    {
      ActiveJob->Operation = VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_SET_PARTITION_REVISION;
    }
    /* #330 If the pending validity differs from the current validity
     *   Trigger bookkeeper to persist the validity of the current partition. */
    else if (partition->DynamicAttributesOfVarPartitions.IsValid != partition->PendingAttributesOfVarPartitions.IsValid)
    {
      ActiveJob->Operation = VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_SET_PARTITION_VALID;
    }
    /* #340 Otherwise: All attributes match.
     *   Reset job operation and mark attributes of current partition as clean. */
    else
    {
      ActiveJob->Operation       = VSWUPDM_JOB_OPERATION_DEFAULT;
      partition->AttributesDirty = FALSE;
      partition->AffectedState   = VSWUPDM_PART_STATE_UNDEFINED;

      retVal = VSWUPDM_JOB_STATUS_ACTIVE;
    }
  }
  /* #400 Otherwise */
  else
  {
    /* #410 Handle the next partition. */
    ActiveJob->EntityIds.PartitionId++;

    /* #420 If this wasn't the last partition
     *   Evaluate attribute state of next partition on next job cycle. */
    if (ActiveJob->EntityIds.PartitionId < vSwUpdM_EntityData.Count.PartitionCount)
    {
      retVal = VSWUPDM_JOB_STATUS_ACTIVE;
    }
    /* #430 Otherwise: All partitions handled.
      *   Finish job execution. */
    else
    {
      retVal = VSWUPDM_JOB_STATUS_FINISHED;
    }
  }

  /* #1000 If job result is okay and any bookkeeper operation shall be triggered */
  if ( (ActiveJob->Result == E_OK)
    && (ActiveJob->Operation != VSWUPDM_JOB_OPERATION_DEFAULT) )
  {
    /* #1010 Trigger bookkeeper.
     *   Result will be evaluated during next job cycle. */
    retVal = vSwUpdM_Job_TriggerBookkeeper(ActiveJob->Operation, ActiveJob);
  }

  return retVal;
  /* PRQA S 6010, 6030 1 */ /* MD_MSR_STPTH, MD_MSR_STCYC */
} /* vSwUpdM_JobHandler_PersistPartitionState */

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_ModuleValidity
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
 */
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_ModuleValidity)
{
  vSwUpdM_JobStatusType retVal = VSWUPDM_JOB_STATUS_PENDING;

  VSWUPDM_DUMMY_STATEMENTS_JOB_HANDLER(); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  /* #10 Evaluate child result from previous cycle. */
  (void)vSwUpdM_Job_EvaluateAndApplyChildResult(ActiveJob, FALSE);

  /* #20 Evaluate job state. */
  switch (ActiveJob->State)
  {
    case VSWUPDM_JOB_STATE_INITIAL:
    /* #100 If initial operation shall be triggered */
    {
      Std_ReturnType spawnResult;
      vSwUpdM_JobPtrType spawnedJob;

      /* #110 Enter critical section to ensure exclusive access of state and job queue. */
      VSWUPDM_ENTER_CRITICAL_SECTION();

      /* #120 Spawn job to persist module state. */
      spawnedJob = vSwUpdM_Job_Spawn(&spawnResult, VSWUPDM_JOB_TYPE_PERSIST_MODULE_STATE, VSWUPDM_JOB_OPERATION_DEFAULT, (vSwUpdM_QueuePrioType)VSWUPDM_JOB_PRIO_DEFAULT, VSWUPDM_SID_NONE, ActiveJob, ActiveJob->Source);

      /* #130 Job attributes are safe to be modified when job was successfully spawned and access is still protected by critical section. */
      if (spawnResult == E_OK)
      {
        spawnedJob->EntityIds = ActiveJob->EntityIds;
      }

      /* #140 Leave critical section ensuring exclusive access of state and job queue. */
      VSWUPDM_LEAVE_CRITICAL_SECTION();

      /* #150 Forward state to wait for result of operation. */
      ActiveJob->State = VSWUPDM_JOB_STATE_PENDING;

      break;
    }
    case VSWUPDM_JOB_STATE_PENDING:
    /* #200 If waiting for result of operation: */
    {
      /* #210 Indicate that job is finished. */
      retVal = VSWUPDM_JOB_STATUS_FINISHED;
      break;
    }
    case VSWUPDM_JOB_STATE_FAILED:
    /* #300 If job state is "failed", because of negative child result
     *   Return with negative result taken over from child job. */
    {
      break;
    }
    default:
    /* #400 Otherwise: Invalid state.
     *   Set error in job result. */
    {
      ActiveJob->Result = VSWUPDM_E_INV_STATE;

      break;
    }
  }

  return retVal;
} /* vSwUpdM_JobHandler_ModuleValidity */

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_PersistModuleState
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
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_PersistModuleState)
{
  vSwUpdM_JobStatusType     retVal = VSWUPDM_JOB_STATUS_PENDING;

  VSWUPDM_DUMMY_STATEMENTS_JOB_HANDLER(); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  /* #10 Evaluate child result from previous cycle. */
  (void)vSwUpdM_Job_EvaluateAndApplyChildResult(ActiveJob, FALSE);

  /* #20 If job result is okay */
  if (ActiveJob->Result == E_OK)
  {
    vSwUpdM_VarModulesPtrType module = vSwUpdM_GetAddrVarModules(ActiveJob->EntityIds.ModuleId);
    vSwUpdM_PartitionIdxType  relativePartitionIdx = 0u; /* Redundant initialization to prevent non suppress able PRQA message 2963. */

    /* #100 Evaluate relative partition index of module instance in given partition. */
    ActiveJob->Result = vSwUpdM_Module_GetRelativePartitionIdxByPartition(&relativePartitionIdx, ActiveJob->EntityIds.ModuleId, ActiveJob->EntityIds.PartitionId);

    if (ActiveJob->Result == E_OK)
    {
      ActiveJob->EntityIds.PartitionIdx = relativePartitionIdx;

      /* #200 Evaluate job operation. */
      switch (ActiveJob->Operation)
      {
        case VSWUPDM_JOB_OPERATION_DEFAULT:
        /* #210 If default operation is set
          *   Nothing to be done. */
        {
          break;
        }
        case VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_SET_MODULE_PROGRAMMING_ATTEMPTS:
        /* #220 If programming attempt counter of the current module instance was persisted
         *   Take over pending value to become effective. */
        {
          module->DynamicAttributesOfVarModules[relativePartitionIdx].ProgrammingAttempts = vSwUpdM_ModulePendingAttributes.Attributes.ProgrammingAttempts;
          break;
        }
        case VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_SET_MODULE_STATE:
        /* #230 If state of the current module instance was persisted
         *   Take over pending value to become effective. */
        {
          module->DynamicAttributesOfVarModules[relativePartitionIdx].State = vSwUpdM_ModulePendingAttributes.Attributes.State;
          break;
        }
        case VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_SET_MODULE_REVISION:
        /* #240 If revision of the current module instance was persisted
         *   Take over pending value to become effective. */
        {
          module->DynamicAttributesOfVarModules[relativePartitionIdx].Revision = vSwUpdM_ModulePendingAttributes.Attributes.Revision;
          break;
        }
        case VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_SET_MODULE_VALID:
        /* #250 If validity of the current module instance was persisted
         *   Take over pending value to become effective. */
        {
          module->DynamicAttributesOfVarModules[relativePartitionIdx].IsValid = vSwUpdM_ModulePendingAttributes.Attributes.IsValid;

          /* #260 If module instance in requested partition is invalid
           *   Mark revision as invalid */
          if (vSwUpdM_ModulePendingAttributes.Attributes.IsValid == FALSE)
          {
            module->DynamicAttributesOfVarModules[relativePartitionIdx].Revision = VSWUPDM_INVALID_REVISION;
            vSwUpdM_ModulePendingAttributes.Attributes.Revision                  = VSWUPDM_INVALID_REVISION;
          }

          break;
        }
        default:
        /* Otherwise: Unknown operation, report error. */
        {
          ActiveJob->Result = VSWUPDM_E_INV_STATE;
          break;
        }
      }

      /* #300 Evaluate which of the pending attributes differ from the attributes currently in effect. */
      /* #310 If the programming attempt counter differs from the current counter
       *   Trigger bookkeeper to persist the state of the current module instance. */
      if (module->DynamicAttributesOfVarModules[relativePartitionIdx].ProgrammingAttempts != vSwUpdM_ModulePendingAttributes.Attributes.ProgrammingAttempts)
      {
        ActiveJob->Operation = VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_SET_MODULE_PROGRAMMING_ATTEMPTS;
      }
      /* #320 If the pending state differs from the current state
       *   Trigger bookkeeper to persist the state of the current module instance. */
      else if (module->DynamicAttributesOfVarModules[relativePartitionIdx].State != vSwUpdM_ModulePendingAttributes.Attributes.State)
      {
        ActiveJob->Operation = VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_SET_MODULE_STATE;
      }
      /* #330 If the pending revision differs from the current revision
       *   Trigger bookkeeper to persist the state of the current module instance. */
      else if (module->DynamicAttributesOfVarModules[relativePartitionIdx].Revision != vSwUpdM_ModulePendingAttributes.Attributes.Revision)
      {
        ActiveJob->Operation = VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_SET_MODULE_REVISION;
      }
      /* #340 If the pending validity differs from the current validity
       *   Trigger bookkeeper to persist the state of the current module instance. */
      else if (module->DynamicAttributesOfVarModules[relativePartitionIdx].IsValid != vSwUpdM_ModulePendingAttributes.Attributes.IsValid)
      {
        ActiveJob->Operation = VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_SET_MODULE_VALID;
      }
      /* #350 Otherwise: All attributes match.
       *   Reset job operation and finish job execution. */
      else
      {
        vSwUpdM_ModulePendingAttributes.AttributesDirty = FALSE;

        ActiveJob->Operation = VSWUPDM_JOB_OPERATION_DEFAULT;
        retVal               = VSWUPDM_JOB_STATUS_FINISHED;
      }
    }
  }

  /* #1000 If job result is okay and any bookkeeper operation shall be triggered */
  if ( (ActiveJob->Result == E_OK)
    && (ActiveJob->Operation != VSWUPDM_JOB_OPERATION_DEFAULT) )
  {
    /* #1010 Trigger bookkeeper.
     *   Result will be evaluated during next job cycle. */
    retVal = vSwUpdM_Job_TriggerBookkeeper(ActiveJob->Operation, ActiveJob);
  }

  return retVal;
  /* PRQA S 6010, 6030, 6080 1 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STMIF */
} /* vSwUpdM_JobHandler_PersistModuleState */

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_PersistRegionState
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
 *
 *
 *
 *
 */
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_PersistRegionState)
{
  vSwUpdM_JobStatusType retVal = VSWUPDM_JOB_STATUS_PENDING;
  vSwUpdM_VarRegionsPtrType region;

  VSWUPDM_DUMMY_STATEMENTS_JOB_HANDLER(); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  region = vSwUpdM_GetAddrVarRegions(ActiveJob->EntityIds.RegionIdx);

  /* #10 Evaluate child result from previous cycle. */
  (void)vSwUpdM_Job_EvaluateAndApplyChildResult(ActiveJob, FALSE);

  /* #20 If job result is okay */
  if (ActiveJob->Result == E_OK)
  {
    /* #100 Evaluate job operation. */
    switch (ActiveJob->Operation)
    {
      case VSWUPDM_JOB_OPERATION_DEFAULT:
      /* #110 If default operation is set
        *   Nothing to be done. */
      {
        break;
      }
      case VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_SET_REGION_PROGRAMMING_ATTEMPTS:
      /* #120 If programming attempt counter of the current region instance was persisted
       *   Take over pending value to become effective. */
      {
        region->DynamicAttributesOfVarRegion.ProgrammingAttempts = region->PendingAttributesOfVarRegion.ProgrammingAttempts;

        break;
      }
      case VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_SET_REGION_STATE:
      /* #130 If state of the current region instance was persisted
       *   Take over pending value to become effective. */
      {
        region->DynamicAttributesOfVarRegion.State = region->PendingAttributesOfVarRegion.State;

        break;
      }
      case VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_SET_REGION_ERASE_ADDRESS:
      /* #140 If erase address of the current region instance was persisted
       *   Take over pending value to become effective. */
      {
        region->EraseAddressDirty = FALSE;

        break;
      }
      default:
      /* #150 Otherwise: Unknown operation, report error. */
      {
        ActiveJob->Result = VSWUPDM_E_INV_STATE;

        break;
      }
    }

    /* #300 If the programming attempt counter differs from the current value
     *   Trigger bookkeeper to persist the state of the current region instance. */
    if (region->DynamicAttributesOfVarRegion.ProgrammingAttempts != region->PendingAttributesOfVarRegion.ProgrammingAttempts)
    {
      ActiveJob->Operation = VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_SET_REGION_PROGRAMMING_ATTEMPTS;
    }
    /* #310 If the pending state differs from the current state
     *   Trigger bookkeeper to persist the state of the current region instance. */
    else if (region->DynamicAttributesOfVarRegion.State != region->PendingAttributesOfVarRegion.State)
    {
      ActiveJob->Operation = VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_SET_REGION_STATE;
    }
    /* #320 Otherwise, if erase address is marked dirty
     *   Trigger bookkeeper to persist the erase address of the current region instance. */
    else if (region->EraseAddressDirty == TRUE)
    {
      ActiveJob->Operation = VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_SET_REGION_ERASE_ADDRESS;
    }
    /* #330 Otherwise: All attributes match.
     *   Reset job operation and finish job execution. */
    else
    {
      region->AttributesDirty = FALSE;

      ActiveJob->Operation = VSWUPDM_JOB_OPERATION_DEFAULT;
      retVal               = VSWUPDM_JOB_STATUS_FINISHED;
    }
  }

  /* #1000 If job result is okay and any bookkeeper operation shall be triggered */
  if ( (ActiveJob->Result == E_OK)
    && (ActiveJob->Operation != VSWUPDM_JOB_OPERATION_DEFAULT) )
  {
    /* #1010 Trigger bookkeeper.
     *   Result will be evaluated during next job cycle. */
    retVal = vSwUpdM_Job_TriggerBookkeeper(ActiveJob->Operation, ActiveJob);
  }

  return retVal;
  /* PRQA S 6010, 6030 1 */ /* MD_MSR_STPTH, MD_MSR_STCYC */
} /* vSwUpdM_JobHandler_PersistRegionState */

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_PersistAllRegionStates
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
 */
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_PersistAllRegionStates)
{
  vSwUpdM_JobStatusType retVal = VSWUPDM_JOB_STATUS_PENDING;

  VSWUPDM_DUMMY_STATEMENTS_JOB_HANDLER(); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  /* #10 Evaluate child result from previous cycle. */
  (void)vSwUpdM_Job_EvaluateAndApplyChildResult(ActiveJob, FALSE);

  /* #20 Evaluate job state. */
  switch (ActiveJob->State)
  {
    case VSWUPDM_JOB_STATE_INITIAL:
    /* #100 If initial conditions for first actual phase shall be established */
    {
      /* #110 Start persisting attributes of first region, using relative index of region in requested module. */
      ActiveJob->EntityIds.RegionIdx = 0u;

      /* #120 Advance job state to persist attributes of current region next. */
      ActiveJob->State = VSWUPDM_JOB_STATE_PENDING;

      break;
    }
    case VSWUPDM_JOB_STATE_PENDING:
    /* #200 If attributes of current region shall be persisted. */
    {
      /* #210 Persist any pending attributes of the current region. */
      (void)vSwUpdM_Region_PersistState(ActiveJob->EntityIds.PartitionId, ActiveJob->EntityIds.ModuleId, ActiveJob->EntityIds.RegionIdx, VSWUPDM_SID_NONE, ActiveJob, ActiveJob->Source);

      /* #220 Advance job state to handle next region. */
      ActiveJob->State = VSWUPDM_JOB_STATE_FINAL;

      break;
    }
    case VSWUPDM_JOB_STATE_FINAL:
    /* #300 If next region shall be handled */
    {
      /* #310 Handle the next region of the module. */
      ActiveJob->EntityIds.RegionIdx++;

      /* #320 If this wasn't the last region of the requested module */
      if (ActiveJob->EntityIds.RegionIdx < vSwUpdM_GetNRegionsOfModule(ActiveJob->EntityIds.ModuleId))
      {
        /* #330 Advance job state to persist attributes of current region next. */
        ActiveJob->State = VSWUPDM_JOB_STATE_PENDING;
        retVal           = VSWUPDM_JOB_STATUS_ACTIVE;
      }
      /* #340 Otherwise: All regions of requested module persisted.
       *   Finish job execution. */
      else
      {
        retVal = VSWUPDM_JOB_STATUS_FINISHED;
      }

      break;
    }
    case VSWUPDM_JOB_STATE_FAILED:
    /* #400 If job state is "failed", because of negative child result
     *   Return with negative result taken over from child job. */
    {
      break;
    }
    default:
    /* #500 Otherwise: Invalid state.
     *   Set error in job result. */
    {
      ActiveJob->Result = VSWUPDM_E_INV_STATE;
      break;
    }
  }

  return retVal;
  /* PRQA S 6030 1 */ /* MD_MSR_STCYC */
} /* vSwUpdM_JobHandler_PersistAllRegionStates */

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_PersistSegmentState
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
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_PersistSegmentState)
{
  vSwUpdM_JobStatusType    retVal              = VSWUPDM_JOB_STATUS_PENDING;
  vSwUpdM_JobOperationType bookkeeperOperation = VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_NONE;

  VSWUPDM_DUMMY_STATEMENTS_JOB_HANDLER(); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  /* #100 If initial conditions for first actual phase shall be established */
  if (ActiveJob->State == VSWUPDM_JOB_STATE_INITIAL)
  {
    /* #110 Reset the relative segment index to an invalid value. */
    ActiveJob->EntityIds.SegmentIdx = VSWUPDM_INVALID_ID;
    /* #120 Start with attributes of first internal segment. */
    ActiveJob->EntityIds.SegmentId.DynamicSegmentId = 0u;

    /* #130 Forward state to wait for result of potential operation. */
    ActiveJob->State = VSWUPDM_JOB_STATE_PENDING;
  }
  /* #200 Otherwise */
  else
  {
    vSwUpdM_VarSegmentsPtrType segment = vSwUpdM_GetAddrVarSegments(ActiveJob->EntityIds.SegmentId.DynamicSegmentId);

    /* #210 Evaluate child result from previous cycle.
     *   If okay */
    if (vSwUpdM_Job_EvaluateAndApplyChildResult(ActiveJob, FALSE) == E_OK)
    {
      /* #220 If the relative segment index holds a valid value and the attributes of the current segment are marked as dirty,
       *   the attributes of a dynamic segment were persisted.
       *   Mark attributes of current segment as clean. */
      if (segment->AttributesDirty == TRUE)
      {
        segment->AttributesDirty = FALSE;
      }
      /* #230 Otherwise, if the write address of the current segment is marked as dirty, the value was persisted.
       *   Mark write address of current segment as clean. */
      else if (segment->WriteAddressDirty == TRUE)
      {
        segment->WriteAddressDirty = FALSE;
      }
      /* #240 Otherwise: All dirty attributes persisted.
       *   Handle next internal segment. */
      else
      {
        ActiveJob->EntityIds.SegmentId.DynamicSegmentId++;
      }
    }
  }

  /* #500 If this wasn't the last internal segment */
  if (ActiveJob->EntityIds.SegmentId.DynamicSegmentId < vSwUpdM_EntityData.Count.InternalSegmentCount)
  {
    /* PRQA S 3679 1 */ /* MD_vSwUpdM_Rule8.13_3679_PointerToModifiableData */
    vSwUpdM_VarSegmentsPtrType segment = vSwUpdM_GetAddrVarSegments(ActiveJob->EntityIds.SegmentId.DynamicSegmentId);

    /* #510 Assign external segment index to relative segment index of the jobs entity IDs. */
    ActiveJob->EntityIds.SegmentIdx = segment->ExternalSegmentIdx;

    /* #520 If the external segment index holds a valid value (indicating a dynamic segment)
     *   and the attributes of the current segment are marked as dirty */
    if (segment->AttributesDirty == TRUE)
    {
      /* #521 Trigger bookkeeper to persist the attributes of the current segment. */
      vSwUpdM_SegmentPendingAttributes = segment->DynamicAttributesOfVarSegment;
      bookkeeperOperation = VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_SET_SEGMENT_ATTRIBUTES;
    }
    /* #530 Otherwise, if write address of current segment is marked as dirty
     *   Trigger bookkeeper to persist the write address of the current segment. */
    else if (segment->WriteAddressDirty == TRUE)
    {
      bookkeeperOperation = VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_SET_SEGMENT_WRITE_ADDRESS;
    }
    /* #540 Otherwise
     *   Evaluate attribute state of next segment on next job cycle. */
    else
    {
      retVal = VSWUPDM_JOB_STATUS_ACTIVE;
    }
  }
  /* #600 Otherwise: All segments handled.
    *   Finish job execution. */
  else
  {
    retVal = VSWUPDM_JOB_STATUS_FINISHED;
  }

  /* #1000 If job result is okay and any bookkeeper operation shall be triggered */
  if ( (ActiveJob->Result == E_OK)
    && (bookkeeperOperation != VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_NONE) )
  {
    /* #1010 Trigger bookkeeper.
     *   Result will be evaluated during next job cycle. */
    retVal = vSwUpdM_Job_TriggerBookkeeper(bookkeeperOperation, ActiveJob);
  }

  return retVal;
} /* vSwUpdM_JobHandler_PersistSegmentState */

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_PersistSegmentCount
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
 */
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_PersistSegmentCount)
{
  vSwUpdM_JobStatusType retVal = VSWUPDM_JOB_STATUS_PENDING;  /* PRQA S 2981 */ /* MD_MSR_RetVal */

  VSWUPDM_DUMMY_STATEMENTS_JOB_HANDLER(); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  /* #10 Evaluate child result from previous cycle. */
  (void)vSwUpdM_Job_EvaluateAndApplyChildResult(ActiveJob, FALSE);

  /* #100 If operation shall be triggered */
  if (ActiveJob->Operation == VSWUPDM_JOB_OPERATION_DEFAULT)
  {
    /* #110 Trigger bookkeeper to persist the segment count.
     *   Result will be evaluated during next job cycle. */
    ActiveJob->Operation = VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_SET_SEGMENT_COUNT;

    retVal = vSwUpdM_Job_TriggerBookkeeper(ActiveJob->Operation, ActiveJob);
  }
  /* #200 Otherwise */
  else
  {
    /* #210 If job result is okay
     *   Mark segment count clean. */
    if (ActiveJob->Result == E_OK)
    {
      vSwUpdM_EntityData.Count.ExternalSegmentCountDirty = FALSE;
    }

    /* #220 Indicate that job is finished. */
    retVal = VSWUPDM_JOB_STATUS_FINISHED;
  }

  return retVal;
} /* vSwUpdM_JobHandler_PersistSegmentCount */

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_CloseSegment
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
 */
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_CloseSegment)
{
  vSwUpdM_JobStatusType retVal = VSWUPDM_JOB_STATUS_PENDING;

  VSWUPDM_DUMMY_STATEMENTS_JOB_HANDLER(); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  /* #10 Evaluate child result from previous cycle. */
  (void)vSwUpdM_Job_EvaluateAndApplyChildResult(ActiveJob, FALSE);

  /* #20 Evaluate job state. */
  switch (ActiveJob->State)
  {
    case VSWUPDM_JOB_STATE_INITIAL:
    /* #100 If operations shall be triggered */
    {
      /* #110 Trigger persisting of any modified segment states. */
      (void)vSwUpdM_Segment_PersistState(&ActiveJob->EntityIds, VSWUPDM_SID_NONE, TRUE, ActiveJob, ActiveJob->Source);

      /* #120 Forward state to wait for result of operation. */
      ActiveJob->State = VSWUPDM_JOB_STATE_PENDING;

      break;
    }
    case VSWUPDM_JOB_STATE_PENDING:
    {
      /* #130 Change state of region in which given segment lies to "clean". */
      (void)vSwUpdM_Region_UpdateAndPersistState(ActiveJob->EntityIds.PartitionId, ActiveJob->EntityIds.ModuleId,
        vSwUpdM_GetVarSegments(ActiveJob->EntityIds.SegmentId.DynamicSegmentId).RegionIdxOfVarSegments,
        VSWUPDM_REGION_STATE_CLEAN, ActiveJob, ActiveJob->Source);

      /* #140 Forward state to wait for result of operation. */
      ActiveJob->State = VSWUPDM_JOB_STATE_FINAL;

      break;
    }
    case VSWUPDM_JOB_STATE_FINAL:
    /* #200 If waiting for result of operation */
    {
      /* #210 Clear ID and pointer of opened segment in entity data structure. */
      vSwUpdM_SegmentIdType invalidId = VSWUPDM_SEGMENT_ID_DEFAULT;

      vSwUpdM_EntityData.OpenIds.SegmentId   = invalidId;
      vSwUpdM_EntityData.OpenObjects.Segment = NULL_PTR;

      /* #220 Indicate that job is finished. */
      retVal = VSWUPDM_JOB_STATUS_FINISHED;

      break;
    }
    case VSWUPDM_JOB_STATE_FAILED:
    /* #300 If job state is "failed", because of negative child result
     *   Return with negative result taken over from child job. */
    {
      break;
    }
    default:
    /* #400 Otherwise: Invalid state.
     *   Set error in job result. */
    {
      ActiveJob->Result = VSWUPDM_E_INV_STATE;
      break;
    }
  }

  return retVal;
} /* vSwUpdM_JobHandler_CloseSegment */

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_OpenSegment
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
 */
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_OpenSegment)
{
  vSwUpdM_JobStatusType retVal = VSWUPDM_JOB_STATUS_PENDING;  /* PRQA S 2981 */ /* MD_MSR_RetVal */

  VSWUPDM_DUMMY_STATEMENTS_JOB_HANDLER(); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  /* #10 Evaluate child result from previous cycle. */
  (void)vSwUpdM_Job_EvaluateAndApplyChildResult(ActiveJob, FALSE);

  /* #20 Evaluate job state. */
  switch (ActiveJob->State)
  {
    case VSWUPDM_JOB_STATE_INITIAL:
    /* #100 If operations shall be triggered. */
    {
      if (ActiveJob->Result == E_OK)
      {
        (void)vSwUpdM_Segment_PersistState(&ActiveJob->EntityIds, VSWUPDM_SID_NONE, TRUE, ActiveJob, ActiveJob->Source);

        ActiveJob->State = VSWUPDM_JOB_STATE_PENDING;
      }

      break;
    }
    case VSWUPDM_JOB_STATE_PENDING:
    /* #200 If waiting for result of operation: */
    {
      /* #210 Set ID of opened segment and point to segment in entity data structure. */
      vSwUpdM_EntityData.OpenIds.SegmentId = ActiveJob->EntityIds.SegmentId;
      vSwUpdM_EntityData.OpenObjects.Segment = vSwUpdM_GetAddrVarSegments(ActiveJob->EntityIds.SegmentId.DynamicSegmentId);

      /* #220 Indicate that job is finished. */
      retVal = VSWUPDM_JOB_STATUS_FINISHED;

      break;
    }
    case VSWUPDM_JOB_STATE_FAILED:
    /* #300 If job state is "failed", because of negative child result
     *   Return with negative result taken over from child job. */
    {
      break;
    }
    default:
    /* #400 Otherwise: Invalid state.
    *   Set error in job result. */
    {
      ActiveJob->Result = VSWUPDM_E_INV_STATE;
      break;
    }
  }

  return retVal;
  /* PRQA S 6010, 6030, 6050, 6080 1 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */
} /* vSwUpdM_JobHandler_OpenSegment */

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_WaitForBookkeeperOperation
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
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_WaitForBookkeeperOperation)
{
  vSwUpdM_JobStatusType retVal = VSWUPDM_JOB_STATUS_PENDING;
  Std_ReturnType        bookkeeperResult;
  vSwUpdM_OpStatusType  bookkeeperStatus;

  VSWUPDM_DUMMY_STATEMENTS_JOB_HANDLER(); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  /* #10 Map job status to status passed to bookkeeper handler. */
  switch (ActiveJob->State)
  {
    case VSWUPDM_JOB_STATE_INITIAL:
    {
      bookkeeperStatus = VSWUPDM_OP_STATUS_INITIAL;
      break;
    }
    case VSWUPDM_JOB_STATE_PENDING:
    {
      bookkeeperStatus = VSWUPDM_OP_STATUS_PENDING;
      break;
    }
    case VSWUPDM_JOB_STATE_FINAL:
    {
      bookkeeperStatus = VSWUPDM_OP_STATUS_FINAL;
      break;
    }
    case VSWUPDM_JOB_STATE_CANCEL:
    default:
    {
      bookkeeperStatus = VSWUPDM_OP_STATUS_CANCEL;
      break;
    }
  }

  /* #20 Execute bookkeeper handler with requested operation. */
  bookkeeperResult = vSwUpdM_BookkeeperHandler(ActiveJob->Operation, bookkeeperStatus, &ActiveJob->EntityIds);

  /* #100 Evaluate result of bookkeeper handler. */
  switch (bookkeeperResult)
  {
    case E_OK:
    /* #110 If bookkeeper returned a positive result
     *  Indicate that job is finished. */
    {
      retVal = VSWUPDM_JOB_STATUS_FINISHED;

      break;
    }
    case VSWUPDM_E_PENDING:
    /* #120 If bookkeeper accepted request, but the result is pending
     *   Advance job state to wait for result of operation, using "pending" as state for next call. */
    {
      ActiveJob->State = VSWUPDM_JOB_STATE_PENDING;

      break;
    }
    case VSWUPDM_E_BUSY:
    /* #130 If bookkeeper didn't accept the request yet, because it is busy
     *   Advance job state to retry operation, using "initial" as state for next call. */
    {
      ActiveJob->State = VSWUPDM_JOB_STATE_INITIAL;

      break;
    }
    default:
    /* #140 If bookkeeper returned a negative result
     *  Overwrite result with "callout failed" error and indicate that job is finished. */
    {
      ActiveJob->Result = VSWUPDM_E_CALLOUT_FAILED;
      retVal = VSWUPDM_JOB_STATUS_FINISHED;

      break;
    }
  }

  return retVal;
} /* vSwUpdM_JobHandler_WaitForBookkeeperOperation */

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_WaitForHookOperation
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
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_WaitForHookOperation)
{
  vSwUpdM_JobStatusType       retVal = VSWUPDM_JOB_STATUS_PENDING;
  Std_ReturnType              calloutResult;
  vSwUpdM_OpStatusType        calloutStatus;
  vSwUpdM_ServiceHookPtrType  hookFunction;
  vSwUpdM_HookInfoType        hookInfo;
  vSwUpdM_HookResultType      hookResult;

  VSWUPDM_DUMMY_STATEMENTS_JOB_HANDLER(); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  /* #10 Map job status to status passed to bookkeeper handler. */
  switch (ActiveJob->State)
  {
    case VSWUPDM_JOB_STATE_INITIAL:
    {
      calloutStatus = VSWUPDM_OP_STATUS_INITIAL;
      break;
    }
    case VSWUPDM_JOB_STATE_PENDING:
    {
      calloutStatus = VSWUPDM_OP_STATUS_PENDING;
      break;
    }
    case VSWUPDM_JOB_STATE_FINAL:
    {
      calloutStatus = VSWUPDM_OP_STATUS_FINAL;
      break;
    }
    case VSWUPDM_JOB_STATE_CANCEL:
    default:
    {
      calloutStatus = VSWUPDM_OP_STATUS_CANCEL;
      break;
    }
  }

  /* #100 Determine hook type and matching function pointer based on current job phase. */
  if (ActiveJob->Phase == VSWUPDM_JOB_PHASE_PRE_HOOK)
  {
    hookFunction      = ActiveJob->PreHookFct;
    hookInfo.HookType = VSWUPDM_HOOK_TYPE_PRE;
  }
  else
  {
    hookFunction      = ActiveJob->PostHookFct;
    hookInfo.HookType = VSWUPDM_HOOK_TYPE_POST;
  }

  /* #200 Pass information about current service state to hook function. */
  hookInfo.ServiceId          = ActiveJob->ServiceId;
  hookInfo.EntityIds          = &ActiveJob->EntityIds;
  hookInfo.TargetAddress      = ActiveJob->TargetAddress;
  hookInfo.ProcessingLength   = ProcessingLength;
  hookInfo.RetryCount         = ActiveJob->RetryCount;

  /* #210 Initialize hook result structure, presetting with current job result, default action and granularity. */
  hookResult.Result           = ActiveJob->Result;
  hookResult.HookAction       = VSWUPDM_HOOK_ACTION_DEFAULT;
  hookResult.RetryGranularity = VSWUPDM_RETRY_GRANULARITY_DEFAULT;

  /* #220 Execute hook function. */
  calloutResult = hookFunction(calloutStatus, &hookInfo, &hookResult);

  /* #230 Evaluate result of hook function. */
  switch (calloutResult)
  {
    case E_OK:
    /* #240 If hook returned a positive result */
    {
      boolean allowed = FALSE;

      /* #300 Verify consistency of returned hook result */
      switch (hookResult.HookAction)
      {
        case VSWUPDM_HOOK_ACTION_DEFAULT:
        /* #310 If default hook action is requested */
        {
          /* #311 Default action only allows to overwrite an error with another error code.
            *   Or leave a positive result intact.
            *   But neither can a positive result be overwritten with an error, nor vice-versa.
            *   No difference between pre- and post-hook. */
          if ((ActiveJob->Result == E_OK) == (hookResult.Result == E_OK))
          {
            allowed = TRUE;
          }

          break;
        }
        case VSWUPDM_HOOK_ACTION_CONTINUE:
        case VSWUPDM_HOOK_ACTION_ABORT:
        /* #320 If continue or abort hook action is requested */
        {
          /* #321 Only applicable when job failed.
            *   Overwritten result must stay an error.
            *   Only applicable for post-hook. */
          if ( (hookInfo.HookType == VSWUPDM_HOOK_TYPE_POST)
            && (ActiveJob->Result != E_OK)
            && (hookResult.Result != E_OK) )
          {
            allowed = TRUE;
          }

          break;
        }
        case VSWUPDM_HOOK_ACTION_SKIP:
        /* #330 If skip hook action is requested */
        {
          /* #331 Only applicable for pre-hook.
            *   Arbitrary return value (positive or negative) allowed. */
          if (hookInfo.HookType == VSWUPDM_HOOK_TYPE_PRE)
          {
            allowed = TRUE;
          }

          break;
        }
        case VSWUPDM_HOOK_ACTION_RETRY:
        /* #340 If retry hook action is requested */
        {
          /* #341 Only applicable for post-hook.
            *   Arbitrary return value (positive or negative) allowed. */
          if (hookInfo.HookType == VSWUPDM_HOOK_TYPE_POST)
          {
            allowed = TRUE;
          }

          break;
        }
        case VSWUPDM_HOOK_ACTION_RESTART:
        /* #350 If retry hook action is requested */
        {
          /* #341 Overwritten result must be an error.
            *   No difference between pre- and post-hook. */
          if (hookResult.Result != E_OK)
          {
            allowed = TRUE;
          }

          break;
        }
        default:
        /* #360 Otherwise: Invalid hook action. */
        {
          break;
        }
      }

      /* #370 If requested hook isn't allowed */
      if (allowed != TRUE)
      {
        /* #371 Overwrite result with "unsupported hook action" error and reset hook action and granularity to default values. */
        hookResult.Result           = VSWUPDM_E_HOOK_UNSUPPORTED_ACTION;
        hookResult.HookAction       = VSWUPDM_HOOK_ACTION_DEFAULT;
        hookResult.RetryGranularity = VSWUPDM_RETRY_GRANULARITY_DEFAULT;
      }

      /* #380 Overwrite job result, hook action and granularity with updated values. */
      ActiveJob->Result           = hookResult.Result;
      ActiveJob->HookAction       = hookResult.HookAction;
      ActiveJob->RetryGranularity = hookResult.RetryGranularity;

      /* #390 Indicate that job is finished. */
      retVal = VSWUPDM_JOB_STATUS_FINISHED;

      break;
    }
    case VSWUPDM_E_PENDING:
    /* #400 If hook accepted request, but the result is pending
      *   Advance job state to wait for result of operation, using "pending" as state for next call. */
    {
      ActiveJob->State = VSWUPDM_JOB_STATE_PENDING;

      break;
    }
    case VSWUPDM_E_BUSY:
    /* #410 If hook didn't accept the request yet, because it is busy
      *   Advance job state to retry operation, using "initial" as state for next call. */
    {
      ActiveJob->State = VSWUPDM_JOB_STATE_INITIAL;

      break;
    }
    default:
    /* #420 If hook returned a negative result
      *  Overwrite result with "hook failed" error and indicate that job is finished. */
    {
      ActiveJob->Result = VSWUPDM_E_HOOK_FAILED;
      retVal            = VSWUPDM_JOB_STATUS_FINISHED;

      break;
    }
  }

  return retVal;
  /* PRQA S 6010, 6030 1 */ /* MD_MSR_STPTH, MD_MSR_STCYC */
} /* vSwUpdM_JobHandler_WaitForHookOperation */

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_EraseModuleLocal
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
 *
 *
 *
 */
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_EraseModuleLocal)
{
  vSwUpdM_JobStatusType retVal = VSWUPDM_JOB_STATUS_PENDING;

  VSWUPDM_DUMMY_STATEMENTS_JOB_HANDLER(); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  /* #10 Evaluate child result from previous cycle. */
  (void)vSwUpdM_Job_EvaluateAndApplyChildResult(ActiveJob, TRUE);

  /* #20 Evaluate job state. */
  switch (ActiveJob->State)
  {
    case VSWUPDM_JOB_STATE_INITIAL:
    /* #100 If initial conditions for first actual phase shall be established */
    {
      /* #110 Start with first region of module (addressed by relative region index). */
      ActiveJob->EntityIds.RegionIdx = 0u;
      retVal = VSWUPDM_JOB_STATUS_ACTIVE;
      /* #140 Advance job state to erase regions of module next. */
      ActiveJob->State = VSWUPDM_JOB_STATE_LOCAL_ERASE_MODULE_ERASE_REGION;
      break;
    }
    case VSWUPDM_JOB_STATE_LOCAL_ERASE_MODULE_ERASE_REGION:
      /* #200 If regions of module shall be erased */
    {
      /* #210 If this wasn't the last region of the requested module */
      if (ActiveJob->EntityIds.RegionIdx < vSwUpdM_GetNRegionsOfModule(ActiveJob->EntityIds.ModuleId))
      {
        /* #220 Evaluate static region ID for current relative region index in requested module and set in entity IDs. */
        ActiveJob->EntityIds.RegionId = vSwUpdM_GetRegionIdxOfModule2Region(vSwUpdM_GetModule2RegionIdxOfModule(ActiveJob->EntityIds.ModuleId) + ActiveJob->EntityIds.RegionIdx);
#if (VSWUPDM_MULTICONTROLLER_SUPPORT == STD_ON)
        if (vSwUpdM_IsWithLocalNodeOfNodeGroup(vSwUpdM_GetNodeGroupOwnersIdxOfRegion(ActiveJob->EntityIds.RegionId)))
#endif
        {
          /* #230 Trigger erasing of current region. */
          (void)vSwUpdM_Region_EraseRegion(&ActiveJob->EntityIds, ActiveJob->UpdateResumeInfo, VSWUPDM_JOB_OPERATION_DEFAULT, ActiveJob->Source, ActiveJob);
        }

        /* #240 Handle next region. */
        ActiveJob->EntityIds.RegionIdx++;

        /* #250 Advance job state to wait for result of erase operation.*/
        ActiveJob->State = VSWUPDM_JOB_STATE_LOCAL_ERASE_MODULE_ERASE_REGION_CHECK;
      }
      /* #260 Otherwise
       *   Advance job state to update the state of the requested module */
      else
      {
        ActiveJob->State = VSWUPDM_JOB_STATE_LOCAL_ERASE_MODULE_UPDATE_STATE;
        retVal = VSWUPDM_JOB_STATUS_ACTIVE;
      }

      break;
    }
    case VSWUPDM_JOB_STATE_LOCAL_ERASE_MODULE_ERASE_REGION_CHECK:
    /* #300 If waiting for the result of the region erase operation
     *   Advance job state to trigger erase of next region. */
    {
      ActiveJob->State = VSWUPDM_JOB_STATE_LOCAL_ERASE_MODULE_ERASE_REGION;
      retVal = VSWUPDM_JOB_STATUS_ACTIVE;

      break;
    }
    case VSWUPDM_JOB_STATE_LOCAL_ERASE_MODULE_UPDATE_STATE:
      /* #400 If state of requested module shall be updated */
    {
      /* #410 If resume info shall be updated by job
       *   Update resume information to indicate that service is finished, taking over service ID and address.
       *   Force persisting of resume information. */
      if (ActiveJob->UpdateResumeInfo == TRUE)
      {
        (void)vSwUpdM_ResumeInfo_UpdateAndPersistState(VSWUPDM_PART_STATE_UNDEFINED, VSWUPDM_SID_NONE, VSWUPDM_RESUME_STATE_FINISHED, vSwUpdM_ResumeInfo.ResumeInfo.MemoryAddress, vSwUpdM_ResumeInfo.ResumeInfo.StreamAddress, vSwUpdM_ResumeInfo.TriggerAddress, vSwUpdM_ResumeInfo.ResumeInfo.IsAddressValid, ActiveJob->Source);
      }

#if (VSWUPDM_MULTICONTROLLER_SUPPORT == STD_ON)
      if (vSwUpdM_IsWithLocalNodeOfNodeGroup(vSwUpdM_GetNodeGroupOwnersIdxOfModule(ActiveJob->EntityIds.ModuleId)))
#endif
      {
        /* #420 Update state of requested module to "erased" and trigger persisting of module state. */
        (void)vSwUpdM_Module_UpdateAndPersistState(ActiveJob->EntityIds.PartitionId, ActiveJob->EntityIds.PartitionState, ActiveJob->EntityIds.ModuleId, VSWUPDM_MODULE_STATE_ERASED, ActiveJob, ActiveJob->Source);
      }

      /* #430 Advance job state to close module. */
      ActiveJob->State = VSWUPDM_JOB_STATE_FINAL;

      break;
    }
    case VSWUPDM_JOB_STATE_FINAL:
    /* #600 If waiting for module to be closed
     *   Indicate that job is finished. */
    {
      retVal = VSWUPDM_JOB_STATUS_FINISHED;

      break;
    }
    case VSWUPDM_JOB_STATE_EVAL_HOOK:
    /* #700 If result of hook function shall be evaluated */
    {
      /* #710 Handle hook return value. */
      retVal = vSwUpdM_Job_HandleDefaultRetry(ActiveJob);

      break;
    }
    case VSWUPDM_JOB_STATE_FAILED:
    /* #800 If job state is "failed", because of negative child result
     *   Return with negative result taken over from child job. */
    {
      break;
    }
    default:
    /* #900 Otherwise: Invalid state.
     *   Set error in job result. */
    {
      ActiveJob->Result = VSWUPDM_E_INV_STATE;

      break;
    }
  }

  return retVal;
  /* PRQA S 6030 1 */ /* MD_MSR_STCYC */
} /* vSwUpdM_JobHandler_EraseModuleLocal */

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_EraseRegion
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
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_EraseRegion)
{
  vSwUpdM_JobStatusType retVal = VSWUPDM_JOB_STATUS_PENDING;
  vSwUpdM_VarRegionsPtrType region; /* PRQA S 3679 */ /* MD_vSwUpdM_Rule8.13_3679_PointerToModifiableData */

  VSWUPDM_DUMMY_STATEMENTS_JOB_HANDLER(); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  region = vSwUpdM_GetAddrVarRegions(ActiveJob->EntityIds.RegionIdx);

  /* #10 Evaluate child result from previous cycle. */
  (void)vSwUpdM_Job_EvaluateAndApplyChildResult(ActiveJob, TRUE);

  /* #20 Evaluate job state. */
  switch (ActiveJob->State)
  {
    case VSWUPDM_JOB_STATE_INITIAL:
    /* #100 If initial operation shall be triggered */
    {
      /* #110 Evaluate state of requested region. */
      switch (region->DynamicAttributesOfVarRegion.State)
      {
        case VSWUPDM_REGION_STATE_ERASED:
        /* #120 If region is already erased
         *   Nothing to be done. Indicate that job is finished. */
        {
          retVal = VSWUPDM_JOB_STATUS_FINISHED;

          break;
        }
        case VSWUPDM_REGION_STATE_ERASE_PENDING:
        /* #130 If an erase of the region was issued during a previous cycle, but wasn't finished yet
         *   Advance job state to continue erasing the requested region. */
        {
          ActiveJob->State = VSWUPDM_JOB_STATE_ERASE_REGION_START;
          retVal           = VSWUPDM_JOB_STATUS_ACTIVE;

          break;
        }
        default:
        /* #140 Otherwise */
        {
          /* #150 Set erase address of requested region to the reserved start address. */
          vSwUpdM_Region_UpdateEraseAddress(ActiveJob->EntityIds.RegionIdx, region->ReservedStartAddressOfVarRegions);

          /* #160 If resume info shall be updated by job
           *   Update resume information to indicate that service is active, using the original start address of the region,
           *   while taking over the service ID already set.
           *   Force persisting of resume information. */
          if (ActiveJob->UpdateResumeInfo == TRUE)
          {
            (void)vSwUpdM_ResumeInfo_UpdateAndPersistState(VSWUPDM_PART_STATE_UNDEFINED, VSWUPDM_SID_NONE, VSWUPDM_RESUME_STATE_ACTIVE, region->StartAddressOfVarRegions, VSWUPDM_UNDEFINED_ADDRESS, region->StartAddressOfVarRegions, TRUE, ActiveJob->Source);
          }
          {
            /* #100 Trigger invalidation of given module. */
            vSwUpdM_JobPtrType spawnedJob;
            Std_ReturnType result;

            /* #110 Enter critical section to ensure exclusive access of state and job queue. */
            VSWUPDM_ENTER_CRITICAL_SECTION();

            /* #120 Spawn job to synchronize opened partition with active partition. */
            spawnedJob = vSwUpdM_Job_Spawn(&result, VSWUPDM_JOB_TYPE_INVALIDATE_MODULE_UPDATE_LOCAL_STATE, VSWUPDM_JOB_OPERATION_DEFAULT, (vSwUpdM_QueuePrioType)VSWUPDM_JOB_PRIO_DEFAULT, VSWUPDM_SID_NONE, ActiveJob, ActiveJob->Source);

            /* #130 Job attributes are safe to be modified when job was successfully spawned and access is still protected by critical section. */
            if (result == E_OK)
            {
              /* #131 Pass open entity IDs to job. */
              spawnedJob->EntityIds = ActiveJob->EntityIds;
            }

            /* #140 Leave critical section ensuring exclusive access of state and job queue. */
            VSWUPDM_LEAVE_CRITICAL_SECTION();
          }

          /* #180 Advance job state to update the region state. */
          ActiveJob->State = VSWUPDM_JOB_STATE_ERASE_REGION_STATE;

          break;
        }
      }

      /* #190 Continue erase operation at the erase address of the requested region. */
      ActiveJob->TargetAddress = region->EraseAddressOfVarRegion;

      break;
    }
    case VSWUPDM_JOB_STATE_ERASE_REGION_STATE:
    /* #200 If region state shall be updated */
    {
      /* #210 Update the state of the module, the requested region is part of, to "erase pending". */
      (void)vSwUpdM_Module_UpdateAndPersistState(ActiveJob->EntityIds.PartitionId, ActiveJob->EntityIds.PartitionState, ActiveJob->EntityIds.ModuleId, VSWUPDM_MODULE_STATE_ERASE_PENDING, ActiveJob, ActiveJob->Source);
      /* #220 Update the state of the requested region to "erase pending". */
      (void)vSwUpdM_Region_UpdateAndPersistState(ActiveJob->EntityIds.PartitionId, ActiveJob->EntityIds.ModuleId, ActiveJob->EntityIds.RegionIdx, VSWUPDM_REGION_STATE_ERASE_PENDING, ActiveJob, ActiveJob->Source);

      /* #230 Advance job state to start erasing the requested region. */
      ActiveJob->State = VSWUPDM_JOB_STATE_ERASE_REGION_START;

      break;
    }
    case VSWUPDM_JOB_STATE_ERASE_REGION_START:
    /* #300 If requested region shall be erased */
    {
      /* #310 Calculate pending length from current target address to end of region (including any reserved area). */
      vSwUpdM_LengthType eraseLength = (region->ReservedEndAddressOfVarRegions - ActiveJob->TargetAddress) + 1u;
      ActiveJob->PendingLength       = eraseLength;

      /* #320 Limit length of erase operation to a single sector or an erase burst of applicable. */
      (void)vSwUpdM_Range_TrimLength(&eraseLength, ActiveJob->EntityIds.PartitionId, ActiveJob->TargetAddress, VSWUPDM_ALIGN_GRANULARITY_SECTOR, VSWUPDM_TRIM_TYPE_SINGLE);

      /* #330 Trigger erasing of memory range with calculated length. */
      ActiveJob->Result = vSwUpdM_Range_EraseRange(ActiveJob->EntityIds.PartitionId, ActiveJob->EntityIds.PartitionState, ActiveJob->TargetAddress, eraseLength, VSWUPDM_SID_NONE, ActiveJob, ActiveJob->Source);
      /* #340 Advance job state to update region state. */
      ActiveJob->State = VSWUPDM_JOB_STATE_ERASE_REGION_UPDATE;

      break;
    }
    case VSWUPDM_JOB_STATE_ERASE_REGION_UPDATE:
    /* #400 If region state shall be updated */
    {
      vSwUpdM_LengthType      eraseLength;
      vSwUpdM_AddressType     resumeAddress;
      vSwUpdM_AddressType     prevAddress = ActiveJob->TargetAddress;

      /* #410 Recalculate length of erased range from current pending length. */
      eraseLength = ActiveJob->PendingLength;
      (void)vSwUpdM_Range_TrimLength(&eraseLength, ActiveJob->EntityIds.PartitionId, prevAddress, VSWUPDM_ALIGN_GRANULARITY_SECTOR, VSWUPDM_TRIM_TYPE_SINGLE);

      /* #420 Update the resume address to match the end of the erased range
       *   and the (next) target address to point directly behind it. */
      resumeAddress            =  prevAddress + (eraseLength - 1u);
      ActiveJob->TargetAddress = resumeAddress + 1u;

      /* #430 If the pending length wasn't completely erased yet */
      if (ActiveJob->PendingLength > eraseLength)
      {
        vSwUpdM_AddressType checkpointAddress;

        /* #440 Update erase address of region to match target address. */
        vSwUpdM_Region_UpdateEraseAddress(ActiveJob->EntityIds.RegionIdx, ActiveJob->TargetAddress);

        /* #441 Trigger persisting of erase address when checkpoint is crossed. */
        vSwUpdM_ResumeInfo_GetCheckpointAddress(&checkpointAddress, prevAddress, ActiveJob->EntityIds.PartitionId);

        if (ActiveJob->TargetAddress >= checkpointAddress)
        {
          (void)vSwUpdM_Region_PersistState(ActiveJob->EntityIds.PartitionId, ActiveJob->EntityIds.ModuleId, ActiveJob->EntityIds.RegionIdx, VSWUPDM_SID_NONE, ActiveJob, ActiveJob->Source);
        }

        /* #450 Advance job state to continue erasing the requested region. */
        ActiveJob->State = VSWUPDM_JOB_STATE_ERASE_REGION_START;
      }
      /* #500 Otherwise: Region is completely erased. */
      else
      {
        /* #510 Increment the programming attempt counter of the current region. */
        ActiveJob->Result = vSwUpdM_Region_IncProgrammingAttempts(ActiveJob->EntityIds.PartitionId, ActiveJob->EntityIds.ModuleId, ActiveJob->EntityIds.RegionIdx);

        /* #520 If operation was successful
         *   Change region state to "erased". */
        if (ActiveJob->Result == E_OK)
        {
          (void)vSwUpdM_Region_UpdateAndPersistState(ActiveJob->EntityIds.PartitionId, ActiveJob->EntityIds.ModuleId, ActiveJob->EntityIds.RegionIdx, VSWUPDM_REGION_STATE_ERASED, ActiveJob, ActiveJob->Source);
        }

        /* #530 Forward job state to update module state next. */
        ActiveJob->State = VSWUPDM_JOB_STATE_ERASE_REGION_UPDATE_MODULE_STATE;
      }

      /* #600 If resume info shall be updated by job:
       *   Update resume information with the values set previously, taking over the service ID already set. */
      if ( (ActiveJob->Result == E_OK)
        && (ActiveJob->UpdateResumeInfo == TRUE) )
      {
        vSwUpdM_ResumeInfo_UpdateState(VSWUPDM_PART_STATE_UNDEFINED, VSWUPDM_SID_NONE, VSWUPDM_RESUME_STATE_PENDING, resumeAddress, VSWUPDM_UNDEFINED_ADDRESS, resumeAddress, TRUE);
      }

      break;
    }
    case VSWUPDM_JOB_STATE_ERASE_REGION_UPDATE_MODULE_STATE:
    /* #700 If module state shall be updated */
    {
      /* #710 Forward to final state, waiting for result of the concluding operations. */
      ActiveJob->State = VSWUPDM_JOB_STATE_FINAL;

      /* #720 If module state shall be updated, as requested by job operation */
      if (ActiveJob->Operation == VSWUPDM_JOB_OPERATION_ERASE_REGION_UPDATE_MODULE_STATE)
      {
        /* #721 If resume info shall be updated by job:
         * Persist ResumeInfo. */
        if (ActiveJob->UpdateResumeInfo == TRUE)
        {
          ActiveJob->Result = vSwUpdM_ResumeInfo_UpdateAndPersistState(VSWUPDM_PART_STATE_UNDEFINED, VSWUPDM_SID_NONE, VSWUPDM_RESUME_STATE_FINISHED, region->EndAddressOfVarRegions, VSWUPDM_UNDEFINED_ADDRESS, region->EndAddressOfVarRegions, TRUE, ActiveJob->Source);
        }

        /* #722 Update state of requested module to "clean"  */
        (void)vSwUpdM_Module_UpdateState(ActiveJob->EntityIds.PartitionId, ActiveJob->EntityIds.ModuleId, VSWUPDM_MODULE_STATE_CLEAN);
      }

      /* #730 Trigger persisting of potentially changed module state and or programming attempts. */
      (void)vSwUpdM_Module_PersistState(ActiveJob->EntityIds.PartitionId, ActiveJob->EntityIds.PartitionState, ActiveJob->EntityIds.ModuleId, ActiveJob, ActiveJob->Source);

      break;
    }
    case VSWUPDM_JOB_STATE_FINAL:
    /* #800 If waiting for result of final operations
     *   Indicate that job is finished. */
    {
      retVal = VSWUPDM_JOB_STATUS_FINISHED;
      break;
    }
    case VSWUPDM_JOB_STATE_EVAL_HOOK:
    /* #900 If result of hook function shall be evaluated */
    {
      boolean allowed = FALSE;

      /* #910 Verify whether requested hook operation is applicable. */
      switch (ActiveJob->HookAction)
      {
        case VSWUPDM_HOOK_ACTION_RETRY:
        case VSWUPDM_HOOK_ACTION_RESTART:
        /* #920 If retry or restart action is requested */
        {
          /* #930 Verify requested retry granularity. */
          switch (ActiveJob->RetryGranularity)
          {
            case VSWUPDM_RETRY_GRANULARITY_DEFAULT:
            /* #931 Default granularity is allowed. */
            {
              allowed = TRUE;

              /* #932 If retry is requested
               *   Overwrite result with positive return code. */
              if (ActiveJob->HookAction == VSWUPDM_HOOK_ACTION_RETRY)
              {
                ActiveJob->Result = E_OK;
              }

              /* #933 Set erase address of region to target address, taken over from failed child job.
               *   Erase range job has set the value to point to the address where the operation failed. */
              vSwUpdM_Region_UpdateEraseAddress(ActiveJob->EntityIds.RegionIdx, ActiveJob->TargetAddress);

              break;
            }
            default:
            /* #940 Otherwise: Unsupported retry granularity. */
            {
              break;
            }
          }

          break;
        }
        default:
        /* #950 Otherwise: Unsupported hook action. */
        {
          break;
        }
      }

      /* #960 If requested hook isn't allowed
       *   Overwrite result with "unsupported hook action" error. */
      if (allowed != TRUE)
      {
        ActiveJob->Result = VSWUPDM_E_HOOK_UNSUPPORTED_ACTION;
      }

      /* #970 Indicate that job is finished. */
      retVal = VSWUPDM_JOB_STATUS_FINISHED;

      break;
    }
    case VSWUPDM_JOB_STATE_FAILED:
    /* #1000 If job state is "failed", because of negative child result
     *   Return with negative result taken over from child job. */
    {
      break;
    }
    default:
    /* #1100 Otherwise: Invalid state.
     *   Set error in job result. */
    {
      ActiveJob->Result = VSWUPDM_E_INV_STATE;
      break;
    }
  }

  return retVal;
  /* PRQA S 6010, 6030, 6050 1 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL */
} /* vSwUpdM_JobHandler_EraseRegion */

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_EraseRange
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
 *
 *
 *
 */
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_EraseRange)
{
  vSwUpdM_JobStatusType retVal = VSWUPDM_JOB_STATUS_PENDING;
  P2VAR(vSwUpdM_BufferInfoType, AUTOMATIC, VSWUPDM_APPL_VAR)  inputBuffer = ActiveJob->InputBuffer;

  VSWUPDM_DUMMY_STATEMENTS_JOB_HANDLER(); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  /* #10 Evaluate job state. */
  switch (ActiveJob->State)
  {
    case VSWUPDM_JOB_STATE_INITIAL:
    /* #100 If initial operation shall be triggered */
    {
      /* #110 Input buffer doesn't hold actual data, but is used to keep track of progress.
       * If virtual input buffer still indicates remaining data */
      if (inputBuffer->Used > 0u)
      {
        /* #111 If suspend of operation is requested
         *   Indicate that job is suspended. */
        if (ActiveState == VSWUPDM_STATE_SUSPENDING)
        {
          retVal = VSWUPDM_JOB_STATUS_SUSPENDED;
        }
        /* #112 Otherwise */
        else
        {
          /* #120 Trigger erase of requested memory range in address area associated with opened partition, by calling vMemAccM.
           * If vMemAccM accepts request */
          if (vMemAccM_Erase(vSwUpdM_EntityData.OpenObjects.Partition->AddrAreaIdOfPartitions, ActiveJob->TargetAddress, ProcessingLength) == E_OK)
          {
            Std_ReturnType spawnResult;
            vSwUpdM_JobPtrType spawnedJob;

            /* #130 Enter critical section to ensure exclusive access of state and job queue. */
            VSWUPDM_ENTER_CRITICAL_SECTION();

            /* #140 Spawn job to wait for memory operation to finish. */
            spawnedJob = vSwUpdM_Job_Spawn(&spawnResult, VSWUPDM_JOB_TYPE_WAIT_FOR_MEMORY_OPERATION, VSWUPDM_JOB_OPERATION_DEFAULT, ActiveJob->CurrentPrio + 1u, VSWUPDM_SID_NONE, ActiveJob, ActiveJob->Source);

            /* #150 Job attributes are safe to be modified when job was successfully spawned and access is still protected by critical section. */
            if (spawnResult == E_OK)
            {
              spawnedJob->EntityIds     = ActiveJob->EntityIds;
              spawnedJob->TargetAddress = ActiveJob->TargetAddress;
              ActiveJob->PendingLength  = ProcessingLength;
            }

            /* #160 Leave critical section ensuring exclusive access of state and job queue. */
            VSWUPDM_LEAVE_CRITICAL_SECTION();

            /* #170 Advance job state to wait for result of memory operation. */
            ActiveJob->State = VSWUPDM_JOB_STATE_PENDING;
          }
          /* #180 Otherwise: Set error to indicate failed erase. */
          else
          {
            ActiveJob->Result = VSWUPDM_E_MEM_ERASE;
          }
        }
      }
      /* #190 Otherwise
       *   Indicate that job is finished. */
      else
      {
        retVal = VSWUPDM_JOB_STATUS_FINISHED;
      }

      break;
    }
    case VSWUPDM_JOB_STATE_PENDING:
    /* #200 If waiting for result of memory operation */
    {
      /* #210 Evaluate child result from previous cycle.
       *   If okay */
      if (vSwUpdM_Job_EvaluateChildResult(ActiveJob) == E_OK)
      {
        /* #220 Update remaining length to be erased, by consuming data from virtual input buffer. */
        (void)vSwUpdM_Buffer_ConsumeData(inputBuffer, ActiveJob->PendingLength);
        /* #230 Update target address, by adding erased length. */
        ActiveJob->TargetAddress += ActiveJob->PendingLength;

        /* #240 Advance job state to re-evaluate remainder and trigger another erase operation if necessary. */
        ActiveJob->State = VSWUPDM_JOB_STATE_INITIAL;
        retVal           = VSWUPDM_JOB_STATUS_ACTIVE;
      }
      /* #250 Otherwise */
      else
      {
        /* #260 Update remaining length to be erased, taking into account the address where the erase failed.
         *   This information is stored in the target address of the child result. */
        (void)vSwUpdM_Buffer_ConsumeData(inputBuffer, ActiveJob->ChildResult.TargetAddress - ActiveJob->TargetAddress);

        /* #270 Set error to indicate failed erase. */
        vSwUpdM_Job_ApplyChildResult(ActiveJob, TRUE);
        ActiveJob->Result = VSWUPDM_E_MEM_ERASE;
      }

      break;
    }
    case VSWUPDM_JOB_STATE_EVAL_HOOK:
    /* #300 If result of hook function shall be evaluated */
    {
      boolean allowed = FALSE;

      /* #310 Verify whether requested hook operation is applicable. */
      switch (ActiveJob->HookAction)
      {
        case VSWUPDM_HOOK_ACTION_RETRY:
        /* #320 If retry action is requested */
        {
          /* #330 Verify requested retry granularity. */
          switch (ActiveJob->RetryGranularity)
          {
            case VSWUPDM_RETRY_GRANULARITY_DEFAULT:
            case VSWUPDM_RETRY_GRANULARITY_SECTOR:
            /* #340 Default and sector granularity are allowed. */
            {
              /* #341 Overwrite result with positive return code. */
              ActiveJob->Result = E_OK;
              allowed           = TRUE;

              break;
            }
            case VSWUPDM_RETRY_GRANULARITY_OPERATION:
            /* #350 Operation granularity is allowed. */
            {
              /* #351 Reset target address and remainder (in virtual input buffer) to values at start of operation.
               *   Current position in virtual input buffer can be used as indication for the progress .*/
              vSwUpdM_LengthType consumed = inputBuffer->Position;

              ActiveJob->TargetAddress -= consumed;
              inputBuffer->Used        += consumed;
              inputBuffer->Position    = 0u;

              /* #352 Overwrite result with positive return code. */
              ActiveJob->Result = E_OK;
              allowed           = TRUE;

              break;
            }
            default:
            /* #360 Otherwise: Unsupported retry granularity. */
            {
              break;
            }
          }

          break;
        }
        default:
        /* #370 Otherwise: Unsupported hook action. */
        {
          break;
        }
      }

      /* #380 If requested hook isn't allowed
       *   Overwrite result with "unsupported hook action" error. */
      if (allowed != TRUE)
      {
        ActiveJob->Result = VSWUPDM_E_HOOK_UNSUPPORTED_ACTION;
      }

      /* #390 Indicate that job is finished. */
      retVal = VSWUPDM_JOB_STATUS_FINISHED;

      break;
    }
    default:
    /* #400 Otherwise: Invalid state.
     *   Set error in job result. */
    {
      ActiveJob->Result = VSWUPDM_E_INV_STATE;
      break;
    }
  }

  return retVal;
  /* PRQA S 6030, 6080 2 */ /* MD_MSR_STCYC, MD_MSR_STMIF */
} /* vSwUpdM_JobHandler_EraseRange */

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_RemoteProcessStreamData
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
 *
 *
 *
 *
 *
 *
 */
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_RemoteProcessStreamData) /* PRQA S 3673 */ /* MD_vSwUpdM_Rule8.13_3673_PointerToConstParameter */
{
  vSwUpdM_JobStatusType retVal = VSWUPDM_JOB_STATUS_PENDING; /* PRQA S 2981 */ /* MD_MSR_RetVal */
#if (VSWUPDM_MULTICONTROLLER_SUPPORT == STD_ON)
  P2VAR(vSwUpdM_BufferInfoType, AUTOMATIC, VSWUPDM_APPL_VAR)  inputBuffer = ActiveJob->InputBuffer;
#endif

  VSWUPDM_DUMMY_STATEMENTS_JOB_HANDLER(); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */

#if (VSWUPDM_MULTICONTROLLER_SUPPORT == STD_ON)
  /* #10 Evaluate job state. */
  switch (ActiveJob->State)
  {
    case VSWUPDM_JOB_STATE_INITIAL:
    /* #100 If initial actions shall be performed */
    {
      /* #110 Suspend job when requested. */
      if (ActiveState == VSWUPDM_STATE_SUSPENDING)
      {
        retVal = VSWUPDM_JOB_STATUS_SUSPENDED;
      }
      else
      {
        /* #120 Prepare reception of remote responses. */
        vSwUpdM_RemoteClearListOfResponses(ActiveJob->RemoteTargetGroup);

        /* #130 Announce available stream data to all instances in current target group. */
        ActiveJob->Result = vRpcProxy_vSwUpdM_RemoteProcessStreamData_TargetGroup(
          vSwUpdM_GetDestinationMainOfNodeGroup(ActiveJob->RemoteTargetGroup),
          (uint8) VSWUPDM_EXCTSCHEDULE_SERVICESTATE_RUN,
          inputBuffer->Used);

        if (ActiveJob->Result == E_OK)
        {
          /* #140 Store current request for eventual resume. */
          vSwUpdM_ExecCtrl_StoreRemoteResumeService(
            VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_PROCESS_STREAM_DATA,
            ActiveJob->RemoteTargetGroup,
            VSWUPDM_INVALID_NODE);
        }
        /* #150 Advance job state to wait for responses from child nodes. */
        ActiveJob->State = VSWUPDM_JOB_STATE_PENDING;
      }

      break;
    }
    case VSWUPDM_JOB_STATE_PENDING:
    /* #200 If waiting for responses from slaves. */
    {
      vSwUpdM_GridSrvc_ServiceIdxType           remoteService = VSWUPDM_GRIDSRVC_SERVICEIDX_UNDEFINED;
      vSwUpdM_LengthType                        minLength     = VSWUPDM_MAX_LENGTH;
      Std_ReturnType                            requestResult;

      /* #210 Evaluate responses from slaves. */
      requestResult = vSwUpdM_RemoteEvalStreamDataRequest(ActiveJob->RemoteTargetGroup, &remoteService, &minLength);

      /* #220 Evaluation of response is service specific. */
      switch (remoteService)
      {
        case VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_COPY_STREAM_DATA:
        /* #300 If CopyStreamData request was received. */
        {
          /* #301 Evaluate aggregated result */
          switch (requestResult)
          {
            case E_OK:
            /* #310 If result is positive */
            {
              P2CONST(uint8, AUTOMATIC, VSWUPDM_APPL_VAR) data;
              vSwUpdM_NodeGroup2NodeIndIterType nodeIndIndex;

              /* #311 Limit data to be transmitted to minimum of requested length and current processing length. */
              if (minLength > ProcessingLength)
              {
                minLength = ProcessingLength;
              }

              /* #312 Transmit requested data and wait for next request. */
              vSwUpdM_RemoteClearListOfResponses(ActiveJob->RemoteTargetGroup);

              /* #313 If this was the last chunk of data
               *   Wait for confirmation of ProcessStreamData request next. */
              data = vSwUpdM_Buffer_GetUsedBuffer(inputBuffer);

              (void)vSwUpdM_Buffer_ConsumeData(inputBuffer, minLength);

              if (inputBuffer->Used == 0u)
              {
                ActiveJob->State = VSWUPDM_JOB_STATE_FINAL;
              }

              /* #314 Iterate over all nodes of active group:
               *      Send response to each. */
              for (nodeIndIndex = vSwUpdM_GetNodeGroup2NodeIndStartIdxOfNodeGroup(ActiveJob->RemoteTargetGroup);
                   nodeIndIndex < vSwUpdM_GetNodeGroup2NodeIndEndIdxOfNodeGroup(ActiveJob->RemoteTargetGroup);
                   nodeIndIndex++)
              {
                vSwUpdM_NodeIterType nodeIndex = vSwUpdM_GetNodeGroup2NodeInd(nodeIndIndex);

                ActiveJob->Result = vRpcProxy_vSwUpdM_RemoteResponseCopyStreamData_Target(
                  vSwUpdM_GetDestinationMainOfNode(nodeIndex),
                  vSwUpdM_GridRpc_GetRpcProxyRequestOfService(VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_COPY_STREAM_DATA),
                  vSwUpdM_GridRpc_GetRpcProxyServiceExecutionState(VSWUPDM_GRIDRPC_SERVICEXECUTIONSTATE_FINISHED),
                  data,
                  (vSwUpdM_RemoteProcessingSegmentationType)minLength,
                  inputBuffer->Used);

                if (ActiveJob->Result != E_OK)
                {
                  break;
                }
              }

              break;
            }
            case VSWUPDM_E_PENDING:
            /* #320 If operation is pending: Re-evaluate on next cycle. */
            {
              break;
            }
            case VSWUPDM_E_SUSPENDED:
            /* #330 If suspended operation is indicated
             *   Unexpected result for CopyStreamData: Report error. */
            {
              ActiveJob->Result = E_NOT_OK;

              break;
            }
            default:
            /* #340 Otherwise: Report aggregated negative result. */
            {
              ActiveJob->Result = requestResult;

              break;
            }
          }
          break;
        }
        case VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_PROCESS_STREAM_DATA:
        /* #400 If response to ProcessStreamData was received. */
        {
          switch (requestResult)
          {
            case E_OK:
            case VSWUPDM_E_PENDING:
            /* #410 If result is positive or pending operation is indicated
             *   Currently unexpected: Report error. */
            {
              ActiveJob->Result = VSWUPDM_E_REMOTE_RESPONSE_WRONG_SERVICE;
              vSwUpdM_ExecCtrl_ClearRemoteResumeService(VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_PROCESS_STREAM_DATA);

              break;
            }
            case VSWUPDM_E_SUSPENDED:
            /* #420 If suspended operation is indicated */
            {
              /* #421 Suspend job when requested. */
              if (ActiveState == VSWUPDM_STATE_SUSPENDING)
              {
                retVal = VSWUPDM_JOB_STATUS_SUSPENDED;
              }
              else
              {
                ActiveJob->Result = E_NOT_OK;
              }

              break;
            }
            default:
            /* #430 Otherwise: Report aggregated negative result. */
            {
              /* #431 No resume of request is required anymore. */
              vSwUpdM_ExecCtrl_ClearRemoteResumeService(VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_PROCESS_STREAM_DATA);
              ActiveJob->Result = requestResult;

              break;
            }
          }

          break;
        }
        default:
        /* #500 Otherwise: Report aggregated negative result, unless operation is pending. */
        {
          if (requestResult != VSWUPDM_E_PENDING)
          {
            ActiveJob->Result = requestResult;
          }

          break;
        }
      }

      break;
    }
    case VSWUPDM_JOB_STATE_FINAL:
    /* #600 If waiting for confirmation of ProcessStreamData */
    {
      vSwUpdM_GridSrvc_ServiceIdxType      remoteService = VSWUPDM_GRIDSRVC_SERVICEIDX_UNDEFINED;
      vSwUpdM_LengthType                        minLength     = VSWUPDM_MAX_LENGTH;
      Std_ReturnType                            requestResult;

      /* #610 Evaluate responses from slaves. */
      requestResult = vSwUpdM_RemoteEvalStreamDataRequest(ActiveJob->RemoteTargetGroup, &remoteService, &minLength);

      /* #620 If response to ProcessStreamData was received. */
      if (remoteService == VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_PROCESS_STREAM_DATA)
      {
        /* #621 Evaluate aggregated result */
        switch (requestResult)
        {
          case E_OK:
          /* #622 If result is positive
           *   Indicate that job is finished. */
          {
            /* #623 No resume of request is required anymore. */
            vSwUpdM_ExecCtrl_ClearRemoteResumeService(VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_PROCESS_STREAM_DATA);

            retVal = VSWUPDM_JOB_STATUS_FINISHED;
            break;
          }
          case VSWUPDM_E_PENDING:
          /* #624 If operation is pending: Re-evaluate on next cycle. */
          {
            break;
          }
          case VSWUPDM_E_SUSPENDED:
          /* #625 If suspended operation is indicated
           *   Indicate that job is suspended. */
          {
            retVal = VSWUPDM_JOB_STATUS_SUSPENDED;
            break;
          }
          default:
          /* #626 Otherwise: Report aggregated negative result. */
          {
            vSwUpdM_ExecCtrl_ClearRemoteResumeService(VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_PROCESS_STREAM_DATA);
            ActiveJob->Result = requestResult;
            break;
          }
        }
      }
      /* #630 Otherwise: Report unexpected service, unless operation is pending. */
      else
      {
        if (requestResult != VSWUPDM_E_PENDING)
        {
          ActiveJob->Result = VSWUPDM_E_REMOTE_RESPONSE_WRONG_SERVICE;
        }
      }

      break;
    }
    default:
    /* #700 Otherwise: Invalid state.
      *   Set error in job result. */
    {
      ActiveJob->Result = VSWUPDM_E_INV_STATE;
      break;
    }
  }
#else
  retVal = VSWUPDM_JOB_STATUS_FINISHED;
#endif

  return retVal;
  /* PRQA S 6010, 6030, 6050, 6080 1 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */
} /* vSwUpdM_JobHandler_RemoteProcessStreamData */

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_StartStream
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
 */
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_StartStream)
{
  vSwUpdM_JobStatusType       retVal  = VSWUPDM_JOB_STATUS_PENDING;
  vSwUpdM_VarSegmentsPtrType  segment = vSwUpdM_GetAddrVarSegments(ActiveJob->EntityIds.SegmentId.DynamicSegmentId);

  VSWUPDM_DUMMY_STATEMENTS_JOB_HANDLER(); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  /* #10 Evaluate job state. */
  switch (ActiveJob->State)
  {
    case VSWUPDM_JOB_STATE_INITIAL:
    /* #100 If initial operations shall be triggered */
    {
      boolean updateEntityStates = TRUE;

#if (VSWUPDM_MULTICONTROLLER_SUPPORT == STD_ON)
      vSwUpdM_NodeGroupOwnersIdxOfRegionType regionOwnerGroupIndex = vSwUpdM_Segment_GetRegionOwnerGroupIndex(ActiveJob->EntityIds.SegmentId);

      if (!vSwUpdM_IsWithLocalNodeOfNodeGroup(regionOwnerGroupIndex))
      {
        updateEntityStates = FALSE;
      }

      /* #110 Update the states of all entities affected by upcoming write operation. */
      if (updateEntityStates == TRUE)
#endif
      {
        (void)vSwUpdM_Module_UpdateAndPersistState(ActiveJob->EntityIds.PartitionId, ActiveJob->EntityIds.PartitionState, ActiveJob->EntityIds.ModuleId, VSWUPDM_MODULE_STATE_DIRTY, ActiveJob, ActiveJob->Source);
      }

      vSwUpdM_Job_PrepareWriteOperation(ActiveJob, segment, updateEntityStates);

#if (VSWUPDM_PIPELINED_PROGRAMMING == STD_ON)
      /* #120 Reset pipelined programming state. */
      vSwUpdM_Init_InitPipelinedProgramming();
#endif

      /* #130 Advance job state to wait for result of initial operations. */
      ActiveJob->State = VSWUPDM_JOB_STATE_PENDING;

      break;
    }
    case VSWUPDM_JOB_STATE_PENDING:
    /* #200 If waiting for result of initial operations */
    {
      /* #210 Evaluate child result from previous cycle.
       *   If okay */
      if (vSwUpdM_Job_EvaluateAndApplyChildResult(ActiveJob, FALSE) == E_OK)
      {
        /* #220 Indicate that job is finished */
        retVal = VSWUPDM_JOB_STATUS_FINISHED;
      }

      break;
    }
    default:
    /* #300 Otherwise: Invalid state.
     *   Set error in job result. */
    {
      ActiveJob->Result = VSWUPDM_E_INV_STATE;
      break;
    }
  }

  return retVal;
  /* PRQA S 6050 1 */ /* MD_MSR_STCAL */
} /* vSwUpdM_JobHandler_StartStream */

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_ProcessStreamData
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
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_ProcessStreamData)
{
  vSwUpdM_JobStatusType retVal;
  P2VAR(vSwUpdM_BufferInfoType, AUTOMATIC, VSWUPDM_APPL_VAR)  inputBuffer   = ActiveJob->InputBuffer;
  vSwUpdM_LengthType    processingLength = ProcessingLength;

  VSWUPDM_DUMMY_STATEMENTS_JOB_HANDLER(); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

#if (VSWUPDM_PIPELINED_PROGRAMMING == STD_ON)
  /* #10 Evaluate possible pending pipelined operation result. */
  if (vSwUpdM_PipelinedProgramming.State == VSWUPDM_PIPELINED_STATE_DONE)
  {
    vSwUpdM_PipelinedProgramming.State = VSWUPDM_PIPELINED_STATE_IDLE;

    if (vSwUpdM_PipelinedProgramming.PreviousWriteResult != E_OK)
    {
      ActiveJob->Result = vSwUpdM_PipelinedProgramming.PreviousWriteResult;
      ActiveJob->State  = VSWUPDM_JOB_STATE_FAILED;
    }
  }
#endif /* VSWUPDM_PIPELINED_PROGRAMMING == STD_ON */

  /* #20 Evaluate child result from previous cycle.
   *   If not okay, apply child result.
   *   If result is SUSPENDED suspend job. */
  retVal = vSwUpdM_Job_EvaluateChildResultOrSuspend(ActiveState, ActiveJob, FALSE);

  if (retVal != VSWUPDM_JOB_STATUS_SUSPENDED)
  {
    /* #50 Evaluate job state. */
    switch (ActiveJob->State)
    {
      case VSWUPDM_JOB_STATE_INITIAL:
      /* #100 If initial conditions for first actual phase shall be established */
      {
#if (VSWUPDM_MULTICONTROLLER_SUPPORT == STD_ON)
        /* PRQA S 3679 2 */ /* MD_vSwUpdM_Rule8.13_3679_PointerToModifiableData */
        vSwUpdM_VarSegmentsPtrType varSegment = vSwUpdM_GetAddrVarSegments(ActiveJob->EntityIds.SegmentId.DynamicSegmentId);
        vSwUpdM_VarRegionsPtrType  varRegion = vSwUpdM_GetAddrVarRegions(varSegment->RegionIdxOfVarSegments);

        ActiveJob->RemoteTargetGroup = vSwUpdM_GetNodeGroupOwnersIdxOfRegion(varRegion->RegionIDOfVarRegions);
#endif

        /* #110 Set pending length to zero and advance job state to copy first chunk of input stream data. */
        ActiveJob->PendingLength = 0u;
        ActiveJob->State         = VSWUPDM_JOB_STATE_PROCESS_STREAM_DATA_COPY;

        retVal = VSWUPDM_JOB_STATUS_ACTIVE;

        break;
      }
      case VSWUPDM_JOB_STATE_PROCESS_STREAM_DATA_COPY:
      /* #200 If input data stream shall be copied */
      {
        Std_ReturnType                 streamResult;
        vStreamProc_EntryPointInfoType dataEntryPointInfo;

        /* #220 If there is any data to be copied */
        if (processingLength > 0u)
        {
          /* #221 Check if there is any empty space in the entry point. */
          if (vSwUpdM_Pipe_GetEntryPoint(vSwUpdM_StreamData.PipeId, vSwUpdM_StreamData.PipeEntryPointData, vStreamProcConf_vStreamProcDataType_uint8, &dataEntryPointInfo) == E_OK)
          {
            if (dataEntryPointInfo.WriteRequest.StorageInfo.AvailableLength < processingLength)
            {
              processingLength = dataEntryPointInfo.WriteRequest.StorageInfo.AvailableLength;
            }
          }
          else
          {
            ActiveJob->Result = VSWUPDM_E_STREAM_OPERATION_FAILED;
            processingLength = 0u;
          }
        }

        if (processingLength > 0u)
        {
          streamResult = vSwUpdM_Pipe_RequestEntryPoint(vSwUpdM_StreamData.PipeId, vSwUpdM_StreamData.PipeEntryPointData, vStreamProcConf_vStreamProcDataType_uint8, processingLength, &dataEntryPointInfo);

          /* #231 If buffer capacity could be successfully evaluated
           *   Limit processing length to available capacity. */
          if (streamResult == E_OK)
          {
            if (processingLength > dataEntryPointInfo.WriteRequest.StorageInfo.AvailableLength)
            {
              processingLength = dataEntryPointInfo.WriteRequest.StorageInfo.AvailableLength;
            }
          }
          /* #232 Otherwise:
           *   Report failed stream operation */
          else
          {
            ActiveJob->Result = VSWUPDM_E_STREAM_OPERATION_FAILED;
            processingLength = 0u;
          }
        }

        /* #240 If there is any data to be copied */
        if (processingLength > 0u)
        {
          if (ActiveJob->Source == (vSwUpdM_NodeIterType)vSwUpdM_GetLocalNode())
          {
            /* #250 Copy data stream into pipe. */
            Std_ReturnType copyResult = vSwUpdM_Stream_CopyData(&dataEntryPointInfo, &processingLength, inputBuffer);

            switch (copyResult)
            {
              case E_OK:
              /* #260 If copy was successful */
              {
                /* #261 Keep track of offset into input stream in target address. */
                ActiveJob->TargetAddress += processingLength;

#if (VSWUPDM_PIPELINED_PROGRAMMING == STD_ON)
                /* #262 If input buffer is empty
                 *   Advance job state to trigger pipelined processing. */
                if (inputBuffer->Used == 0u)
                {
                  ActiveJob->State = VSWUPDM_JOB_STATE_PROCESS_STREAM_DATA_PROCESS_PIPELINED;
                  retVal = VSWUPDM_JOB_STATUS_ACTIVE;
                }
                /* #263 Otherwise: */
                else
#endif
                {
                  /* #264 Advance job state to process data stream. */
                  ActiveJob->State = VSWUPDM_JOB_STATE_PROCESS_STREAM_DATA_PROCESS;
                }

                break;
              }
              case VSWUPDM_E_PENDING:
              /* #265 If result is "pending"
               *   Continue copying in next job cycle */
              {
                break;
              }
              default:
              /* #266 Otherwise: Copy failed.
               *   Report negative result. */
              {
                ActiveJob->Result = copyResult;
                break;
              }
            }
          }
#if (VSWUPDM_MULTICONTROLLER_SUPPORT == STD_ON)
          else
          {
            vSwUpdM_RemotePrepareResponseRxTarget(ActiveJob->Source, VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_COPY_STREAM_DATA, ActiveJob);
            ActiveJob->Result = vRpcProxy_vSwUpdM_RemoteCopyStreamData_Target(vSwUpdM_GetDestinationMainOfNode(ActiveJob->Source), processingLength, inputBuffer->Position);
            ActiveJob->State = VSWUPDM_JOB_STATE_PROCESS_STREAM_EVALUATE_REMOTE_COPY;
          }
#endif
        }
        /* #270 Otherwise: */
        else
        {
          /* #280 If input buffer is empty
           *   Indicate that job is finished. */
          if (inputBuffer->Used == 0u)
          {
            retVal = VSWUPDM_JOB_STATUS_FINISHED;
          }
          /* #281 Otherwise:
           *  Advance job state to process data stream. */
          else
          {
            ActiveJob->State = VSWUPDM_JOB_STATE_PROCESS_STREAM_DATA_PROCESS;
            retVal           = VSWUPDM_JOB_STATUS_ACTIVE;
          }
        }

        break;
      }
#if (VSWUPDM_MULTICONTROLLER_SUPPORT == STD_ON)
      case VSWUPDM_JOB_STATE_PROCESS_STREAM_EVALUATE_REMOTE_COPY:
      {
        if (!vSwUpdM_IsResponseProcessingOfVarNode(ActiveJob->Source))
        {
          ActiveJob->Result = VSWUPDM_E_REMOTE_SERVICE_TARGET_NOT_PROCESSING;
        }
        else if ((vSwUpdM_GridSrvc_ServiceIdxType) vSwUpdM_GetServiceIdOfResponseOfVarNode(ActiveJob->Source) != VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_COPY_STREAM_DATA) /* PRQA S 4342 */ /* MD_vSwUpdM_Rule10.5_4342_EnumParameterCast */
        {
          ActiveJob->Result = VSWUPDM_E_REMOTE_RESPONSE_WRONG_SERVICE;
        }
        else
        {
          ActiveJob->Result = vSwUpdM_GetResultOfResponseOfVarNode(ActiveJob->Source);
        }

        if (ActiveJob->Result == E_OK)
        {
          /* #20 Request buffer from vStreamProc. */
          Std_ReturnType                streamResult;
          vStreamProc_EntryPointInfoType dataEntryPointInfo;
          vSwUpdM_LengthType            receivedLength = vSwUpdM_GetLengthOfResponseOfVarNode(ActiveJob->Source);

          /* Select InputData entry point */
            streamResult = vSwUpdM_Pipe_GetInternalEntryPoint(&dataEntryPointInfo.EntryPointId, vSwUpdMConf_vSwUpdMDataProcess_StreamData, vSwUpdMConf_vSwUpdMDataInputType_InputData);

          /* Consume data */
          if (streamResult == E_OK)
          {
            if (vStreamProc_AcknowledgeEntryPoint(
              vSwUpdM_StreamData.PipeId,
              receivedLength,
              TRUE,
              &dataEntryPointInfo) != VSTREAMPROC_OK)
            {
              streamResult = E_NOT_OK;
            }

            (void)vSwUpdM_Buffer_ConsumeData(inputBuffer, receivedLength);
          }

          if (streamResult == E_OK)
          {
            /* If either output buffer is completely filled or input data stream was completely consumed
              * Otherwise: Continue copying in next job cycle. */
            if (inputBuffer->Used == 0u)
            {
# if (VSWUPDM_PIPELINED_PROGRAMMING == STD_ON)
              /* If input Buffer is empty */
              if (inputBuffer->Used == 0u)
              {
                /* Process data pipelined */
                ActiveJob->State = VSWUPDM_JOB_STATE_PROCESS_STREAM_DATA_PROCESS_PIPELINED;
              }
              else
# endif
              {
                ActiveJob->State = VSWUPDM_JOB_STATE_PROCESS_STREAM_DATA_PROCESS;
              }
            }
            else
            {
              ActiveJob->State = VSWUPDM_JOB_STATE_PROCESS_STREAM_DATA_COPY;
            }
          }
          else
          {
            ActiveJob->Result = VSWUPDM_E_STREAM_OPERATION_FAILED;
          }

          retVal = VSWUPDM_JOB_STATUS_ACTIVE;
        }
        break;
      }
#endif
      case VSWUPDM_JOB_STATE_PROCESS_STREAM_DATA_PROCESS:
        /* #300 If data stream shall be processed */
      {
#if (VSWUPDM_PIPELINED_PROGRAMMING == STD_ON)
        /* #310 If input buffer is empty
          *   Advance job state to trigger pipelined processing. */
        if (inputBuffer->Used == 0u)
        {
          ActiveJob->State = VSWUPDM_JOB_STATE_PROCESS_STREAM_DATA_PROCESS_PIPELINED;
          retVal = VSWUPDM_JOB_STATUS_ACTIVE;
        }
        /* #311 Otherwise: */
        else
#endif
        {
          vSwUpdM_StreamProcessResultType result;

          /* #420 Trigger processing of data stream. */
          result = vSwUpdM_Stream_Process();

          switch (result)
          {
            case VSWUPDM_STREAMPROCRESULT_EMPTY:
            case VSWUPDM_STREAMPROCRESULT_BLOCKED:
            /* #330 If stream buffer is empty or blocked */
            {
              /* #331 Check if input buffer is empty. */
              if (inputBuffer->Used == 0u)
              {
#if (VSWUPDM_PIPELINED_PROGRAMMING == STD_OFF)
                if (    (vSwUpdM_Jobs[VSWUPDM_JOB_TYPE_WRITE_DATA].QueueHandle != (vSwUpdM_QueueHandleType)VSWUPDM_QUEUE_HANDLE_NONE)
                     || (vSwUpdM_Jobs[VSWUPDM_JOB_TYPE_READ_DATA].QueueHandle != (vSwUpdM_QueueHandleType)VSWUPDM_QUEUE_HANDLE_NONE)
                     || (vSwUpdM_Jobs[VSWUPDM_JOB_TYPE_REMOTE_PROCESS_STREAM_DATA].QueueHandle != (vSwUpdM_QueueHandleType)VSWUPDM_QUEUE_HANDLE_NONE)
                   )
                {
                  /* #332 Check if there is still a pending job in the jobs queue.
                   *   Then indicate that job is pending. */
                  retVal = VSWUPDM_JOB_STATUS_PENDING;
                }
                else
#endif
                {
                  /* #333 Otherwise:
                   *   Indicate that job is finished. */
                  retVal = VSWUPDM_JOB_STATUS_FINISHED;
                }
              }
              /* #332 Otherwise:
               *   Advance job state to copy next chunk of input stream data. */
              else
              {
                ActiveJob->State = VSWUPDM_JOB_STATE_PROCESS_STREAM_DATA_COPY;
              }

              break;
            }
            case VSWUPDM_STREAMPROCRESULT_FULL:
            /* #340 If stream buffer is completely filled
             *   Continue processing during next job cycle. */
            {
              break;
            }
            case VSWUPDM_STREAMPROCRESULT_PARTIALLY:
            /* #350 If stream buffer is partially filled */
            {
              /* #351 If input buffer still holds data
               *   Advance job state to copy next chunk of input stream data. */
              if (inputBuffer->Used > 0u)
              {
                ActiveJob->State = VSWUPDM_JOB_STATE_PROCESS_STREAM_DATA_COPY;
              }

              break;
            }
            case VSWUPDM_STREAMPROCRESULT_FAIL:
            default:
            /* #360 If stream buffer reports failure */
            {
              vSwUpdM_Stream_Abort(ActiveJob);
              ActiveJob->State = VSWUPDM_JOB_STATE_PROCESS_STREAM_DATA_ABORT;

              break;
            }
          }
        }

        break;
      }
#if (VSWUPDM_PIPELINED_PROGRAMMING == STD_ON)
      case VSWUPDM_JOB_STATE_PROCESS_STREAM_DATA_PROCESS_PIPELINED:
      /* #400 If pipelined programming shall be triggered: */
      {
        /* #410 If job for pipelined programming is not yet started: */
        if (vSwUpdM_ExctSchedule_IsJobRunningInSlot(VSWUPDM_JOB_TYPE_PROCESS_STREAM_PIPELINED) == FALSE)
        {
          vSwUpdM_PipelinedProgramming.State = VSWUPDM_PIPELINED_STATE_PENDING;

          /* #420 Enter critical section to ensure exclusive access of job queue. */
          VSWUPDM_ENTER_CRITICAL_SECTION();

          /* #430 Spawn background job for pipelined programming. */
          (void)vSwUpdM_Job_Spawn(&ActiveJob->Result, VSWUPDM_JOB_TYPE_PROCESS_STREAM_PIPELINED, VSWUPDM_JOB_OPERATION_DEFAULT, (vSwUpdM_QueuePrioType)VSWUPDM_JOB_PRIO_DEFAULT, VSWUPDM_SID_NONE, NULL_PTR, ActiveJob->Source);

          /* #440 Leave critical section to ensure exclusive access of job queue. */
          VSWUPDM_LEAVE_CRITICAL_SECTION();
        }

        /* #430 Indicate that job is finished. */
        retVal = VSWUPDM_JOB_STATUS_FINISHED;

        break;
      }
#endif
      case VSWUPDM_JOB_STATE_PROCESS_STREAM_DATA_ABORT:
      /* #500 If stream processing shall be aborted */
      {
        /* #510 Evaluate result of processing pipe. */
        vSwUpdM_Job_ResetChildResult(ActiveJob);
        ActiveJob->Result = vSwUpdM_Pipe_ReadResult(vSwUpdMConf_vSwUpdMDataProcess_StreamData, vSwUpdMConf_vSwUpdMDataOutputType_OutputResult);

        break;
      }
      case VSWUPDM_JOB_STATE_FINAL:
      /* #600 If waiting for persisting of module state (triggered by hook evaluation) */
      {
        /* #620 Indicate that job is finished. */
        retVal = VSWUPDM_JOB_STATUS_FINISHED;

        break;
      }
      case VSWUPDM_JOB_STATE_EVAL_HOOK:
      /* #700 If result of hook function shall be evaluated */
      {
        /* #710 Handle retry action for write operation during ProcessStreamData sequence. */
        if (ActiveJob->HookAction == VSWUPDM_HOOK_ACTION_RESTART)
        {
          retVal = vSwUpdM_Job_HandleWriteRetry(ActiveJob, VSWUPDM_SID_PROCESS_STREAM_DATA);
        }
        else
        {
          ActiveJob->Result = VSWUPDM_E_HOOK_UNSUPPORTED_ACTION;
          retVal = VSWUPDM_JOB_STATUS_FINISHED;
        }

        break;
      }
      case VSWUPDM_JOB_STATE_FAILED:
      /* #800 If job state is "failed", because of negative result of pipelined programming.
       *   Return with negative result taken over from child job. */
      {
        break;
      }
      default:
      /* #900 Otherwise: Invalid state.
        *   Set error in job result. */
      {
        ActiveJob->Result = VSWUPDM_E_INV_STATE;
        break;
      }
    }
  }

  /* #1000 If job result indicates a failed operation */
  if (ActiveJob->Result != E_OK)
  {
    /* #1010 Reset state of global stream data information to idle. */
    vSwUpdM_StreamData.State     = VSWUPDM_STREAM_STATE_IDLE;
    vSwUpdM_StreamData.SegmentId = VSWUPDM_INVALID_ID;
  }

  return retVal;
  /* PRQA S 6010, 6030, 6050, 6080 1 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */
} /* vSwUpdM_JobHandler_ProcessStreamData */

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_EndStream
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
 */
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_EndStream) /* PRQA S 3673 */ /* MD_vSwUpdM_Rule8.13_3673_PointerToConstParameter */
{
  vSwUpdM_JobStatusType retVal = VSWUPDM_JOB_STATUS_FINISHED;

  VSWUPDM_DUMMY_STATEMENTS_JOB_HANDLER(); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

#if (VSWUPDM_PIPELINED_PROGRAMMING == STD_ON)
  /* #100 Evaluate pipelined programming state. */
  switch (vSwUpdM_PipelinedProgramming.State)
  {
    case VSWUPDM_PIPELINED_STATE_IDLE:
    /* #110 If no ProcessStream() call since StartStream() */
    {
      /* #111 Successfully end stream. */
      break;
    }
    case VSWUPDM_PIPELINED_STATE_DONE:
    /* #120 If Write job has finished */
    {
      /* #121 Propagate result of pipelined write job. */
      ActiveJob->Result = vSwUpdM_PipelinedProgramming.PreviousWriteResult;
      vSwUpdM_PipelinedProgramming.State = VSWUPDM_PIPELINED_STATE_IDLE;
      break;
    }
    case VSWUPDM_PIPELINED_STATE_PENDING:
    /* #130 Write job has not yet finished. Should never happen because Write Job has higher priority */
    default:
    /* #140 Otherwise: Invalid state. Set error in job result. */
    {
      ActiveJob->Result = VSWUPDM_E_INV_STATE;
      break;
    }
  }
#endif

  /* #200 Close the pipe used for the processing of the input data stream. */
  (void)vStreamProc_Close(vSwUpdM_StreamData.PipeId);

  return retVal;
} /* vSwUpdM_JobHandler_EndStream */

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_FillMemory
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
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_FillMemory)
{
  vSwUpdM_JobStatusType retVal = VSWUPDM_JOB_STATUS_PENDING;
  P2VAR(vSwUpdM_BufferInfoType, AUTOMATIC, VSWUPDM_APPL_VAR)  inputBuffer  = ActiveJob->InputBuffer;
  P2VAR(vSwUpdM_BufferInfoType, AUTOMATIC, VSWUPDM_APPL_VAR)  outputBuffer = ActiveJob->OutputBuffer;

  VSWUPDM_DUMMY_STATEMENTS_JOB_HANDLER(); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  /* #10 Evaluate child result from previous cycle. */
  (void)vSwUpdM_Job_EvaluateAndApplyChildResult(ActiveJob, TRUE);

  /* #20 Evaluate job state. */
  switch (ActiveJob->State)
  {
    /* #100 If initial conditions for first actual phase shall be established */
    case VSWUPDM_JOB_STATE_INITIAL:
    {
      /* #110 Enter critical section to ensure exclusive access of state and job queue. */
      VSWUPDM_ENTER_CRITICAL_SECTION();

      /* #120 Initialize write buffer. */
      (void)vSwUpdM_Buffer_Init(&vSwUpdM_BufferInfoWriteData, (vSwUpdM_VarDataPointerType)vSwUpdM_BufferWriteData, vSwUpdM_GetMaxInputStreamSize());
      /* #130 Initialize target address of write job to current target address of active job.
       *   Must be done here, as address of copy job does not necessarily coincide with actual write address during processing,
       *   e.g. because of remainder handling in write job. */
      vSwUpdM_Jobs[VSWUPDM_JOB_TYPE_WRITE_DATA].TargetAddress = ActiveJob->TargetAddress;

      /* #140 Leave critical section ensuring exclusive access of state and job queue. */
      VSWUPDM_LEAVE_CRITICAL_SECTION();

      /* #150 Set pending length to zero and advance job state to fill requested memory range next. */
      ActiveJob->PendingLength = 0u;
      ActiveJob->State         = VSWUPDM_JOB_STATE_FILL_MEMORY_FILL;

      retVal = VSWUPDM_JOB_STATUS_ACTIVE;

      break;
    }
    case VSWUPDM_JOB_STATE_FILL_MEMORY_FILL:
    /* #200 If write buffer shall be filled */
    {
      vSwUpdM_LengthType processingLength = ProcessingLength;

      /* #210 Limit processed length to available space in write buffer. */
      if (processingLength > outputBuffer->Free)
      {
        processingLength = outputBuffer->Free;
      }

      /* #220 If write buffer needs to be filled more */
      if (processingLength > 0u)
      {
        /* #230 Fill write buffer with configured fill pattern, starting at first free position. */
        vSwUpdM_Buffer_Fill(vSwUpdM_Buffer_GetFreeBuffer(outputBuffer), vSwUpdM_GetFillByte(), processingLength);
        (void)vSwUpdM_Buffer_AddData(outputBuffer, processingLength);
        (void)vSwUpdM_Buffer_ConsumeData(inputBuffer, processingLength);

        /* #240 Remember length of fill data. */
        ActiveJob->PendingLength += processingLength;
      }
      /* #250 Otherwise
       *   Advance job state to write fill data next. */
      else
      {
        ActiveJob->State = VSWUPDM_JOB_STATE_FILL_MEMORY_WRITE;
        retVal           = VSWUPDM_JOB_STATUS_ACTIVE;
      }

      break;
    }
    case VSWUPDM_JOB_STATE_FILL_MEMORY_WRITE:
    /* #300 If fill data shall be written */
    {
      Std_ReturnType spawnResult;
      vSwUpdM_JobPtrType spawnedJob;

      /* #310 Enter critical section to ensure exclusive access of state and job queue. */
      VSWUPDM_ENTER_CRITICAL_SECTION();

      /* #320 Spawn job to write data to requested range.
        *   Use a higher priority than active job. */
      spawnedJob = vSwUpdM_Job_Spawn(&spawnResult, VSWUPDM_JOB_TYPE_WRITE_DATA, VSWUPDM_JOB_OPERATION_DEFAULT, ActiveJob->CurrentPrio + 1u, VSWUPDM_SID_NONE, ActiveJob, ActiveJob->Source);

      /* #330 Job attributes are safe to be modified when job was successfully spawned and access is still protected by critical section. */
      if (spawnResult == E_OK)
      {
        /* #340 Pass entity IDs to write job. */
        spawnedJob->EntityIds = ActiveJob->EntityIds;
      }

      /* #350 Leave critical section ensuring exclusive access of state and job queue. */
      VSWUPDM_LEAVE_CRITICAL_SECTION();

      /* #360 Advance job state to handle next chunk of data. */
      ActiveJob->State = VSWUPDM_JOB_STATE_FILL_MEMORY_NEXT_CHUNK;

      break;
    }
    case VSWUPDM_JOB_STATE_FILL_MEMORY_NEXT_CHUNK:
    /* #400 If next chunk of data shall be handled */
    {
      vSwUpdM_LengthType pendingLength = ActiveJob->PendingLength;

      /* #410 Keep track of progress by updating target address. */
      ActiveJob->TargetAddress += pendingLength;

      /* #420 If virtual input buffer is empty, requested range was completely filled. */
      if (inputBuffer->Used == 0u)
      {
        /* #421 Indicate that job is finished. */
        retVal = VSWUPDM_JOB_STATUS_FINISHED;
      }
      /* #430 Otherwise
       *   Continue to fill requested range. */
      else
      {
        /* #431 Limit length to remaining range. */
        if (pendingLength > inputBuffer->Used)
        {
          pendingLength = inputBuffer->Used;
        }

        (void)vSwUpdM_Buffer_AddData(outputBuffer, pendingLength);
        (void)vSwUpdM_Buffer_ConsumeData(inputBuffer, pendingLength);

        /* #432 Advance job state to continue to fill requested range. */
        ActiveJob->State = VSWUPDM_JOB_STATE_FILL_MEMORY_WRITE;
        retVal           = VSWUPDM_JOB_STATUS_ACTIVE;
      }
      break;
    }
    case VSWUPDM_JOB_STATE_FAILED:
    /* #500 If job state is "failed", because of negative child result
     *   Return with negative result taken over from child job. */
    {
      break;
    }
    default:
    /* #600 Otherwise: Invalid state.
     *   Set error in job result. */
    {
      ActiveJob->Result = VSWUPDM_E_INV_STATE;
      break;
    }
  }

  return retVal;
  /* PRQA S 6030, 6050 1 */ /* MD_MSR_STCYC, MD_MSR_STCAL */
} /* vSwUpdM_JobHandler_FillMemory */

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_ReadData
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
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_ReadData)
{
  vSwUpdM_JobStatusType retVal = VSWUPDM_JOB_STATUS_PENDING;
  P2VAR(vSwUpdM_BufferInfoType, AUTOMATIC, VSWUPDM_APPL_VAR)  inputBuffer  = ActiveJob->InputBuffer;
  P2VAR(vSwUpdM_BufferInfoType, AUTOMATIC, VSWUPDM_APPL_VAR)  outputBuffer = ActiveJob->OutputBuffer;

  VSWUPDM_DUMMY_STATEMENTS_JOB_HANDLER(); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  /* #10 Evaluate job state. */
  switch (ActiveJob->State)
  {
    case VSWUPDM_JOB_STATE_INITIAL:
    /* #100 If read operation shall be triggered */
    {
      /* #110 Input buffer doesn't hold actual data, but is used to keep track of progress.
       *   If virtual input buffer is empty, all requested data was read. */
      if (inputBuffer->Used == 0u)
      {
        /* #111 Indicate the job is finished. */
        retVal = VSWUPDM_JOB_STATUS_FINISHED;
      }
      /* #120 Otherwise, if output buffer doesn't offer enough free space for data to be read
       *   Set error in job result. */
      else if (outputBuffer->Free < ProcessingLength)
      {
        ActiveJob->Result = E_NOT_OK;
      }
      /* #130 Otherwise */
      else
      {
        /* #140 Trigger read of requested memory range in address area associated with opened partition, by calling vMemAccM.
         * If vMemAccM accepts request */
        /* PRQA S 0315 1 */ /* MD_vSwUpdM_Dir1.1_0315_TypedPtrVoidPtr */
        if (vMemAccM_Read(vSwUpdM_GetVarPartitions(ActiveJob->EntityIds.PartitionId).AddrAreaIdOfPartitions, ActiveJob->TargetAddress, vSwUpdM_Buffer_GetFreeBuffer(outputBuffer), ProcessingLength) == E_OK)
        {
          Std_ReturnType spawnResult;
          vSwUpdM_JobPtrType spawnedJob;

          /* #141 Enter critical section to ensure exclusive access of state and job queue. */
          VSWUPDM_ENTER_CRITICAL_SECTION();

          /* #142 Spawn job to wait for memory operation to finish. */
          spawnedJob = vSwUpdM_Job_Spawn(&spawnResult, VSWUPDM_JOB_TYPE_WAIT_FOR_MEMORY_OPERATION, VSWUPDM_JOB_OPERATION_DEFAULT, ActiveJob->CurrentPrio + 1u, VSWUPDM_SID_NONE, ActiveJob, ActiveJob->Source);

          /* #143 Job attributes are safe to be modified when job was successfully spawned and access is still protected by critical section. */
          if (spawnResult == E_OK)
          {
            spawnedJob->EntityIds     = ActiveJob->EntityIds;
            spawnedJob->TargetAddress = ActiveJob->TargetAddress;
            ActiveJob->PendingLength  = ProcessingLength;
          }

          /* #144 Leave critical section ensuring exclusive access of state and job queue. */
          VSWUPDM_LEAVE_CRITICAL_SECTION();

          /* #145 Advance job state to wait for result of memory operation. */
          ActiveJob->State = VSWUPDM_JOB_STATE_PENDING;
        }
        /* #150 Otherwise: Set error to indicate failed read. */
        else
        {
          ActiveJob->Result = VSWUPDM_E_MEM_READ;
        }
      }

      break;
    }
    case VSWUPDM_JOB_STATE_PENDING:
    /* #200 If waiting for result of memory operation */
    {
      /* #210 Evaluate child result from previous cycle.
       *   If okay */
      if (vSwUpdM_Job_EvaluateChildResult(ActiveJob) == E_OK)
      {
        /* #220 Update remaining length to be read, by consuming data from virtual input buffer. */
        ActiveJob->TargetAddress += ProcessingLength;
        (void)vSwUpdM_Buffer_ConsumeData(inputBuffer, ProcessingLength);
        /* #230 Update output buffer to include previously read data. */
        (void)vSwUpdM_Buffer_AddData(outputBuffer, ProcessingLength);

        /* #240 Advance job state to re-evaluate remainder and trigger another read operation if necessary. */
        ActiveJob->State = VSWUPDM_JOB_STATE_INITIAL;
        retVal           = VSWUPDM_JOB_STATUS_ACTIVE;
      }
      /* #250 Otherwise */
      else
      {
        /* #260 Update remaining length to be read, taking into account the address where the read failed.
         *   This information is stored in the target address of the child result. */
        vSwUpdM_LengthType consumed = ActiveJob->ChildResult.TargetAddress - ActiveJob->TargetAddress;

        ActiveJob->PendingLength -= consumed;
        (void)vSwUpdM_Buffer_ConsumeData(inputBuffer, consumed);

        /* #270 Update output buffer to include data read successfully. */
        (void)vSwUpdM_Buffer_AddData(outputBuffer, consumed);

        /* #280 Apply child result (taking over the address). */
        vSwUpdM_Job_ApplyChildResult(ActiveJob, TRUE);
      }

      break;
    }
    case VSWUPDM_JOB_STATE_EVAL_HOOK:
    /* #300 If result of hook function shall be evaluated */
    {
      boolean allowed = FALSE;

      /* #310 Verify whether requested hook operation is applicable. */
      switch (ActiveJob->HookAction)
      {
        case VSWUPDM_HOOK_ACTION_RETRY:
        /* #400 If retry action is requested */
        {
          /* #410 Verify requested retry granularity. */
          switch (ActiveJob->RetryGranularity)
          {
            case VSWUPDM_RETRY_GRANULARITY_DEFAULT:
            /* #420 Default granularity is allowed. */
            {
              /* #421 Overwrite result with positive return code. */
              ActiveJob->Result = E_OK;
              allowed           = TRUE;

              break;
            }
            case VSWUPDM_RETRY_GRANULARITY_OPERATION:
            /* #430 Operation granularity is allowed. */
            {
              vSwUpdM_LengthType consumed = outputBuffer->Used;

              /* #431 Overwrite result with positive return code. */
              allowed           = TRUE;
              ActiveJob->Result = E_OK;

              /* #432 Reset target address and remainder (in virtual input buffer) to values at start of operation.
               *   Current data length in output buffer can be used as indication for the progress. */
              ActiveJob->TargetAddress -= consumed;
              inputBuffer->Position    = 0u;
              inputBuffer->Used        += consumed;
              /* #433 Reset output buffer to initial empty state. */
              outputBuffer->Used       = 0u;
              outputBuffer->Free       += consumed;

              break;
            }
            case VSWUPDM_RETRY_GRANULARITY_PAGE:
            /* #440 Page granularity is allowed. */
            {
              vSwUpdM_AddressType         currentAddress;
              vSwUpdM_AddressType         pageAddress;
              vSwUpdM_LengthType          reservedLength;
              vSwUpdM_LengthType          offset;
              /* PRQA S 3679 1 */ /* MD_vSwUpdM_Rule8.13_3679_PointerToModifiableData */
              vSwUpdM_VarSegmentsPtrType  segment = vSwUpdM_GetAddrVarSegments(ActiveJob->EntityIds.SegmentId.DynamicSegmentId);

              currentAddress = ActiveJob->TargetAddress;
              pageAddress    = currentAddress;
              reservedLength = (segment->ReservedEndAddressOfVarSegments - segment->ReservedStartAddressOfVarSegments) + 1u;

              if (vSwUpdM_Range_IsAddressInRange(pageAddress, segment->ReservedStartAddressOfVarSegments, reservedLength) == TRUE)
              {
                /* #441 If error address reported by child job can be aligned to front of occupied memory page */
                if (vSwUpdM_Range_AlignAddress(&pageAddress, vSwUpdM_EntityData.OpenIds.PartitionId, VSWUPDM_ADDRESS_ALIGNMENT_FRONT, VSWUPDM_ALIGN_GRANULARITY_PAGE) == E_OK)
                {
                  /* #442 Overwrite result with positive return code. */
                  allowed           = TRUE;
                  ActiveJob->Result = E_OK;

                  /* #443 Update target address and remainder (in virtual input buffer) to retry the read from the beginning of the page. */
                  ActiveJob->TargetAddress = pageAddress;

                  offset                   = currentAddress - pageAddress;
                  inputBuffer->Position    -= offset;
                  inputBuffer->Used        += offset;
                  /* #444 Remove any data of the affected page from the output buffer. */
                  outputBuffer->Used       -= offset;
                  outputBuffer->Free       += offset;
                }
              }
              else
              {
                /* Segment was read completely, nothing to do. */
                allowed           = TRUE;
                ActiveJob->Result = E_OK;
              }

              break;
            }
            default:
            /* #450 Otherwise: Unsupported retry granularity. */
            {
              break;
            }
          }

          break;
        }
        case VSWUPDM_HOOK_ACTION_CONTINUE:
        /* #500 If retry action is requested */
        {
          /* #510 Overwrite result with positive return code. */
          allowed           = TRUE;
          ActiveJob->Result = E_OK;

          break;
        }
        default:
        /* #600 Otherwise: Unsupported hook action. */
        {
          break;
        }
      }

      /* #600 If hook request isn't allowed, set job result to "unsupported hook action". */
      if (allowed != TRUE)
      {
        ActiveJob->Result = VSWUPDM_E_HOOK_UNSUPPORTED_ACTION;
      }

      /* #610 Indicate that job is finished. */
      retVal = VSWUPDM_JOB_STATUS_FINISHED;

      break;
    }
    default:
    /* #700 Otherwise: Invalid state.
     *   Set error in job result. */
    {
      ActiveJob->Result = VSWUPDM_E_INV_STATE;
      break;
    }
  }

  return retVal;
  /* PRQA S 6030, 6050, 6080 1 */ /* MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */
} /* vSwUpdM_JobHandler_ReadData */

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_WriteData
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
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_WriteData)
{
  vSwUpdM_JobStatusType retVal = VSWUPDM_JOB_STATUS_PENDING;
  P2VAR(vSwUpdM_BufferInfoType, AUTOMATIC, VSWUPDM_APPL_VAR) inputBuffer = ActiveJob->InputBuffer;

  VSWUPDM_DUMMY_STATEMENTS_JOB_HANDLER(); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  /* #10 Evaluate job state. */
  switch (ActiveJob->State)
  {
    case VSWUPDM_JOB_STATE_INITIAL:
    /* #100 If write operation shall be triggered */
    {
      /* #110 Limit length of write operation to multiples of page size.
       *   If supported align to burst boundaries, to increase chance that burst writes can be issued. */
      vSwUpdM_LengthType processingLength   = ProcessingLength;
      vSwUpdM_AddressType targetAddress     = ActiveJob->TargetAddress;

      if ( (ActiveJob->EntityIds.SegmentId.DynamicSegmentId < vSwUpdM_EntityData.Count.InternalSegmentCount)
        && (targetAddress < vSwUpdM_CheckpointAddress) )
      {
        vSwUpdM_LengthType distance = vSwUpdM_CheckpointAddress - targetAddress;

        if (processingLength > distance)
        {
          processingLength = distance;
        }
      }

      (void)vSwUpdM_Range_TrimLength(&processingLength, ActiveJob->EntityIds.PartitionId, ActiveJob->TargetAddress, VSWUPDM_ALIGN_GRANULARITY_PAGE, VSWUPDM_TRIM_TYPE_BURST);

      /* #120 If there is any data to be written */
      if (processingLength > 0u)
      {
        /* #121 If suspend of operation is requested
         *   Indicate that job is suspended. */
        if (ActiveState == VSWUPDM_STATE_SUSPENDING)
        {
          retVal = VSWUPDM_JOB_STATUS_SUSPENDED;
        }
        /* #122 Otherwise */
        else
        {
          /* #130 Remember length of data to be written for later steps. */
          ActiveJob->PendingLength = processingLength;

          /* #140 Trigger write of requested memory range in address area associated with opened partition, by calling vMemAccM.
           * If vMemAccM accepts request */
          /* PRQA S 0315 1 */ /* MD_vSwUpdM_Dir1.1_0315_TypedPtrVoidPtr */
          if (vMemAccM_Write(vSwUpdM_GetVarPartitions(ActiveJob->EntityIds.PartitionId).AddrAreaIdOfPartitions, ActiveJob->TargetAddress, vSwUpdM_Buffer_GetUsedBuffer(inputBuffer), processingLength) == E_OK)
          {
            Std_ReturnType      spawnResult;
            vSwUpdM_JobPtrType  spawnedJob;

            /* #141 Enter critical section to ensure exclusive access of state and job queue. */
            VSWUPDM_ENTER_CRITICAL_SECTION();

            /* #142 Spawn job to wait for memory operation to finish. */
            spawnedJob = vSwUpdM_Job_Spawn(&spawnResult, VSWUPDM_JOB_TYPE_WAIT_FOR_MEMORY_OPERATION, VSWUPDM_JOB_OPERATION_DEFAULT, ActiveJob->CurrentPrio + 1u, VSWUPDM_SID_NONE, ActiveJob, ActiveJob->Source);

            /* #143 Job attributes are safe to be modified when job was successfully spawned and access is still protected by critical section. */
            if (spawnResult == E_OK)
            {
              spawnedJob->EntityIds     = ActiveJob->EntityIds;
              spawnedJob->TargetAddress = ActiveJob->TargetAddress;

              /* #144 If a segment is opened
               *   Mark segment as "dirty". */
              if (ActiveJob->EntityIds.SegmentId.DynamicSegmentId < vSwUpdM_EntityData.Count.InternalSegmentCount)
              {
                vSwUpdM_GetVarSegments(ActiveJob->EntityIds.SegmentId.DynamicSegmentId).SegmentClean = FALSE;
              }
            }

            /* #145 Leave critical section ensuring exclusive access of state and job queue. */
            VSWUPDM_LEAVE_CRITICAL_SECTION();

            /* #146 Advance job state to wait for result of memory operation. */
            ActiveJob->State = VSWUPDM_JOB_STATE_PENDING;
          }
          /* #150 Otherwise: Set error to indicate failed write. */
          else
          {
            ActiveJob->Result = VSWUPDM_E_MEM_WRITE;
          }
        }
      }
      /* #160 Otherwise */
      else
      {
        /* #170 Move any remainder not aligned to page (or burst) size to front of write buffer. */
        (void)vSwUpdM_Buffer_MoveRemainder(inputBuffer);

        ActiveJob->PendingLength = 0u;
        /* #180 Indicate that job is finished. */
        retVal                   = VSWUPDM_JOB_STATUS_FINISHED;
      }

      break;
    }
    case VSWUPDM_JOB_STATE_PENDING:
    /* #200 If waiting for result of memory operation */
    {
      /* #210 Evaluate child result from previous cycle.
       *   If okay */
      if (vSwUpdM_Job_EvaluateAndApplyChildResult(ActiveJob, TRUE) == E_OK)
      {
        vSwUpdM_ResumeInfo_IncreaseAddress(ActiveJob, ActiveJob->PendingLength);

        /* #260 Update remaining length to be written, by consuming data from the input buffer. */
        (void)vSwUpdM_Buffer_ConsumeData(inputBuffer, ActiveJob->PendingLength);

        /* #261 If a segment is opened
          *   Mark segment as "clean". */
        if (ActiveJob->EntityIds.SegmentId.DynamicSegmentId < vSwUpdM_EntityData.Count.InternalSegmentCount)
        {
          vSwUpdM_GetVarSegments(ActiveJob->EntityIds.SegmentId.DynamicSegmentId).SegmentClean = TRUE;
        }

        /* #270 Advance job state to re-evaluate remainder and trigger another read operation if necessary. */
        ActiveJob->State = VSWUPDM_JOB_STATE_INITIAL;
        retVal           = VSWUPDM_JOB_STATUS_ACTIVE;
      }
      /* #300 Otherwise */
      else
      {
        /* #320 If a segment is opened */
        if (ActiveJob->EntityIds.SegmentId.DynamicSegmentId < vSwUpdM_EntityData.Count.InternalSegmentCount)
        {
          /* #321 Update resume information: Set state to "failed" and invalidate resume address.
            *   Do not force persisting of resume information. */
          vSwUpdM_ResumeInfo_UpdateState(VSWUPDM_PART_STATE_UNDEFINED, VSWUPDM_SID_NONE, VSWUPDM_RESUME_STATE_FAILED, VSWUPDM_UNDEFINED_ADDRESS, VSWUPDM_UNDEFINED_ADDRESS, VSWUPDM_UNDEFINED_ADDRESS, FALSE);
        }
      }

      break;
    }
    case VSWUPDM_JOB_STATE_EVAL_HOOK:
    /* #400 If result of hook function shall be evaluated */
    {
      boolean allowed = FALSE;

      /* #410 Verify whether requested hook operation is applicable. */
      switch (ActiveJob->HookAction)
      {
        case VSWUPDM_HOOK_ACTION_RETRY:
        /* #420 If retry action is requested */
        {
          /* #430 Retry only applicable if any data was processed. */
          if (ActiveJob->PendingLength > 0u)
          {
            /* #440 Verify requested retry granularity. */
            switch (ActiveJob->RetryGranularity)
            {
              case VSWUPDM_RETRY_GRANULARITY_DEFAULT:
              case VSWUPDM_RETRY_GRANULARITY_PAGE:
              /* #450 Default and page granularity is allowed. */
              {
                /* #451 Overwrite result with positive return code. */
                allowed           = TRUE;
                ActiveJob->Result = E_OK;

                break;
              }
              case VSWUPDM_RETRY_GRANULARITY_OPERATION:
              /* #460 Operation granularity is allowed. */
              {
                vSwUpdM_LengthType consumed = inputBuffer->Position;

                /* #461 Reset target address and remainder (in input buffer) to values at start of operation.
                 *   Current position in input buffer can be used as indication for the progress .*/
                ActiveJob->TargetAddress -= consumed;
                inputBuffer->Used        += consumed;
                inputBuffer->Position    = 0u;

                /* #462 Overwrite result with positive return code. */
                allowed                  = TRUE;
                ActiveJob->Result        = E_OK;

                break;
              }
              default:
              /* #470 Otherwise: Unsupported retry granularity. */
              {
                break;
              }
            }
          }

          break;
        }
        default:
        /* #480 Otherwise: Unsupported hook action. */
        {
          /* Unsupported hook action. */
          break;
        }
      }

      /* #500 If requested hook isn't allowed
       *   Overwrite result with "unsupported hook action" error. */
      if (allowed != TRUE)
      {
        ActiveJob->Result = VSWUPDM_E_HOOK_UNSUPPORTED_ACTION;
      }

      /* #510 Indicate that job is finished. */
      retVal = VSWUPDM_JOB_STATUS_FINISHED;

      break;
    }
    default:
    /* #600 Otherwise: Invalid state.
     *   Set error in job result. */
    {
      ActiveJob->Result = VSWUPDM_E_INV_STATE;
      break;
    }
  }

  return retVal;
  /* PRQA S 6030, 6050, 6080 1 */ /* MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */
} /* vSwUpdM_JobHandler_WriteData */

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_ProcessStreamPipelined
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
 */
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_ProcessStreamPipelined)
{
  vSwUpdM_JobStatusType retVal = VSWUPDM_JOB_STATUS_PENDING;

  VSWUPDM_DUMMY_STATEMENTS_JOB_HANDLER(); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

#if (VSWUPDM_PIPELINED_PROGRAMMING == STD_ON)
  /* #10 Evaluate stream process result. */
  switch (vSwUpdM_Stream_Process())
  {
    case VSWUPDM_STREAMPROCRESULT_EMPTY:
    case VSWUPDM_STREAMPROCRESULT_BLOCKED:
    /* #100 If stream buffer is empty or blocked */
    {
      /* #110 Mark job as finished. */
      retVal = VSWUPDM_JOB_STATUS_FINISHED;
      break;
    }
    case VSWUPDM_STREAMPROCRESULT_FULL:
    case VSWUPDM_STREAMPROCRESULT_PARTIALLY:
    /* #200 If stream buffer still contains data */
    {
      /* #210 Wait for state updates. */
      break;
    }
    case VSWUPDM_STREAMPROCRESULT_FAIL:
    /* #300 If stream buffer reports failure */
    {
      /* #310 Report detailed result. */
      ActiveJob->Result = vSwUpdM_Pipe_ReadResult(vSwUpdMConf_vSwUpdMDataProcess_StreamData, vSwUpdMConf_vSwUpdMDataOutputType_OutputResult);
      break;
    }
    default:
    /* #400 Otherwise: Invalid state.
     *   Set error in job result. */
    {
      ActiveJob->Result = VSWUPDM_E_INV_STATE;
      break;
    }
  }

  /* #20 If this job has ended (FINISHED or failure) */
  if ((retVal == VSWUPDM_JOB_STATUS_FINISHED) || (ActiveJob->Result != E_OK))
  {
    /* #30 Propagate Result and set state for pipelined programming. */
    vSwUpdM_PipelinedProgramming.State = VSWUPDM_PIPELINED_STATE_DONE;
    vSwUpdM_PipelinedProgramming.PreviousWriteResult = ActiveJob->Result;
  }
#else
  ActiveJob->Result = E_NOT_OK;
#endif

  return retVal;
} /* vSwUpdM_JobHandler_ProcessStreamPipelined */

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_WaitForMemoryOperation
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
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_WaitForMemoryOperation)
{
  vSwUpdM_JobStatusType       retVal = VSWUPDM_JOB_STATUS_FINISHED;
  vMemAccM_JobResultType      memoryResult;
  vMemAccM_AddressAreaIdType  addressArea;

  VSWUPDM_DUMMY_STATEMENTS_JOB_HANDLER(); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  /* #10 Get job result of memory operation in address area associated with opened partition. */
  addressArea  = vSwUpdM_GetVarPartitions(ActiveJob->EntityIds.PartitionId).AddrAreaIdOfPartitions;
  memoryResult = vMemAccM_GetJobResult(addressArea);

  /* #100 Evaluate result of memory operation to determine job status and update potential error address. */
  switch (memoryResult)
  {
    case VMEMACCM_JOB_OK:
    /* #110 If okay
     *  Indicate that job is finished. */
    {
      break;
    }
    case VMEMACCM_JOB_PENDING:
    /* #120 If pending
     *  Memory operation not finished yet, re-evaluate on next job cycle. */
    {
      retVal = VSWUPDM_JOB_STATUS_PENDING;

      break;
    }
    case VMEMACCM_JOB_CANCELED:
    case VMEMACCM_JOB_FAILED:
    case VMEMACCM_READ_CORRECTED_ERRORS:
    case VMEMACCM_READ_UNCORRECTABLE_ERRORS:
    default:
    /* #130 Otherwise, error was reported.
     *   Indicate that job is finished. */
    {
      vMemAccM_AddressType processedLength;

      /* #131 Get length of successfully processed data, before error occurred. */
      if (vMemAccM_GetProcessedLength(addressArea, &processedLength) == E_OK)
      {
        /* #132 Update target address to point to location where error occurred. */
        ActiveJob->TargetAddress += processedLength;
      }

      break;
    }
  }

  /* #200 Evaluate result of memory operation to set job result. */
  switch (memoryResult)
  {
    case VMEMACCM_JOB_OK:
    case VMEMACCM_JOB_PENDING:
    /* #210 If okay or pending
     *   Do not update (positive) job result. */
    {
      break;
    }
    case VMEMACCM_READ_CORRECTED_ERRORS:
    /* #220 If correctable read errors were reported
     *   Set matching error code. */
    {
      ActiveJob->Result = VSWUPDM_E_MEM_READ_CORRECTED_ERRORS;
      break;
    }
    case VMEMACCM_READ_UNCORRECTABLE_ERRORS:
    /* #230 If uncorrectable read errors were reported
     *   Set matching error code. */
    {
      ActiveJob->Result = VSWUPDM_E_MEM_READ_UNCORRECTABLE_ERRORS;
      break;
    }
    case VMEMACCM_JOB_CANCELED:
    case VMEMACCM_JOB_FAILED:
    default:
    /* #240 Otherwise, if any other error was reported
     *   Set error code for failed memory operation. */
    {
      switch (ActiveJob->Operation)
      {
        case VSWUPDM_JOB_OPERATION_WAIT_MEMORY_READ:
        {
          ActiveJob->Result = VSWUPDM_E_MEM_READ;
          break;
        }
        case VSWUPDM_JOB_OPERATION_WAIT_MEMORY_WRITE:
        {
          ActiveJob->Result = VSWUPDM_E_MEM_WRITE;
          break;
        }
        case VSWUPDM_JOB_OPERATION_WAIT_MEMORY_ERASE:
        {
          ActiveJob->Result = VSWUPDM_E_MEM_ERASE;
          break;
        }
        default:
        {
          ActiveJob->Result = VSWUPDM_E_MEM_FAILED;
          break;
        }
      }
      break;
    }
  }

  return retVal;
} /* vSwUpdM_JobHandler_WaitForMemoryOperation */

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_FinalizeModuleLocal
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
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_FinalizeModuleLocal)
{
  vSwUpdM_JobStatusType retVal = VSWUPDM_JOB_STATUS_PENDING;

  VSWUPDM_DUMMY_STATEMENTS_JOB_HANDLER(); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  /* #10 Evaluate child result from previous cycle. */
  (void)vSwUpdM_Job_EvaluateAndApplyChildResult(ActiveJob, TRUE);

  /* #20 Evaluate job state. */
  switch (ActiveJob->State)
  {
    case VSWUPDM_JOB_STATE_INITIAL:
    /* #100 If initial conditions for first actual phase shall be established */
    {
      /* #110 Reset region and segment indices. */
      ActiveJob->EntityIds.RegionIdx  = 0u;
      ActiveJob->EntityIds.SegmentIdx = 0u;

      /* #120 If module isn't opened yet */
      if (vSwUpdM_EntityData.OpenIds.ModuleId == VSWUPDM_INVALID_ID)
      {
        /* #130 Trigger opening of requested module.
         *   Use job operation to remember that module was opened implicitly. */
        (void)vSwUpdM_Module_OpenModule(ActiveJob->EntityIds.ModuleId, TRUE, VSWUPDM_SID_NONE, ActiveJob->Source, ActiveJob);
        ActiveJob->Operation = VSWUPDM_JOB_OPERATION_CLOSE_MODULE;
      }
      else
      {
        /* #140 Otherwise: Trigger persisting of any modified segment states. */
        (void)vSwUpdM_Segment_PersistState(&ActiveJob->EntityIds, VSWUPDM_SID_NONE, TRUE, ActiveJob, ActiveJob->Source);
      }

      /* #150 Advance job state to check the states of the segments next. */
      ActiveJob->State = VSWUPDM_JOB_STATE_FINALIZE_MODULE_CHECK_SEGMENT_STATE;

      break;
    }
    case VSWUPDM_JOB_STATE_FINALIZE_MODULE_CHECK_SEGMENT_STATE:
    /* #200 If states of segments shall be checked */
    {
      vSwUpdM_VarSegmentsPtrType  segment; /* PRQA S 3679 */ /* MD_vSwUpdM_Rule8.13_3679_PointerToModifiableData */
      vSwUpdM_SegmentIdValueType  segmentId;
      boolean                     allowed = TRUE;

      /* #220 For all internal segments */
      for (segmentId = 0u; segmentId < vSwUpdM_EntityData.Count.InternalSegmentCount; segmentId++)
      {
        segment = vSwUpdM_GetAddrVarSegments(segmentId);

        switch (segment->ClassOfVarSegments)
        {
          case VSWUPDM_CLASS_OF_VAR_SEGMENTS_FREE:
          /* #230 If segment represents a free memory area */
          {
            /* #231 If segment is in an undefined state
             *   Preconditions for module finalization not fulfilled. */
            if (segment->DynamicAttributesOfVarSegment.State == VSWUPDM_SEGMENT_STATE_UNDEFINED)
            {
              allowed = FALSE;
            }

            break;
          }
          case VSWUPDM_CLASS_OF_VAR_SEGMENTS_USED:
          /* #240 If segment represents a free memory area or is used for updated data */
          {
            /* #241 If segment wasn't finalized before
             *   Preconditions for module finalization not fulfilled. */
            if (segment->DynamicAttributesOfVarSegment.State != VSWUPDM_SEGMENT_STATE_FINALIZED)
            {
              allowed = FALSE;
            }

            break;
          }
          default:
          /* #250 Otherwise, reserved segments and gaps do not affect the preconditions. */
          {
            break;
          }
        }
      }

      /* #260 If preconditions for module finalization aren't fulfilled
       *  Invalid state of segments, report error. */
      if (allowed == FALSE)
      {
        ActiveJob->Result = VSWUPDM_E_INVALID_SEGMENT_STATE;
      }
      /* #270 Otherwise
       *   Advance job state to evaluate potential free segment at start of region next */
      else
      {
        ActiveJob->State = VSWUPDM_JOB_STATE_FINALIZE_MODULE_EVAL_FREE_SEGMENT;
        retVal           = VSWUPDM_JOB_STATUS_ACTIVE;
      }

      break;
    }
    case VSWUPDM_JOB_STATE_FINALIZE_MODULE_EVAL_FREE_SEGMENT:
    /* #300 If potential free segment at start of region shall be evaluated */
    {
      vSwUpdM_VarSegmentsPtrType  segment; /* PRQA S 3679 */ /* MD_vSwUpdM_Rule8.13_3679_PointerToModifiableData */

      ActiveJob->EntityIds.RegionId = vSwUpdM_GetVarRegions(ActiveJob->EntityIds.RegionIdx).RegionIDOfVarRegions;

      /* #310 Search segment at start of current region. */
      (void)vSwUpdM_Segment_SearchSegment(&ActiveJob->EntityIds.SegmentId.DynamicSegmentId, vSwUpdM_GetVarRegions(ActiveJob->EntityIds.RegionIdx).ReservedStartAddressOfVarRegions);
      segment = vSwUpdM_GetAddrVarSegments(ActiveJob->EntityIds.SegmentId.DynamicSegmentId);

      /* #320 If segment is a free segment
       *   Advance job state to prepare segment for filling next. */
      if (segment->ClassOfVarSegments == VSWUPDM_CLASS_OF_VAR_SEGMENTS_FREE)
      {
        ActiveJob->State  = VSWUPDM_JOB_STATE_FINALIZE_MODULE_PREPARE_SEGMENT;
      }
      else
      /* #330 Otherwise, nothing left to do for current segment.
       *   Advance job state to continue with next segment. */
      {
        ActiveJob->State = VSWUPDM_JOB_STATE_FINALIZE_MODULE_NEXT_SEGMENT;
        retVal           = VSWUPDM_JOB_STATUS_ACTIVE;
      }

      break;
    }
#if (VSWUPDM_SEGMENT == STD_ON)
    case VSWUPDM_JOB_STATE_FINALIZE_MODULE_EVAL_RESERVED_SEGMENT:
    /* #400 If current reserved segment shall be evaluated */
    {
      vSwUpdM_SegmentIdValueType  staticSegmentId;
      vSwUpdM_SegmentIdValueType  dynamicSegmentId;
      vSwUpdM_VarSegmentsPtrType  segment; /* PRQA S 3679 */ /* MD_vSwUpdM_Rule8.13_3679_PointerToModifiableData */

      /* #410 Search reserved segment based on configured start address. */
      staticSegmentId = vSwUpdM_GetSegmentIdxOfRegion(ActiveJob->EntityIds.RegionId) + (ActiveJob->EntityIds.SegmentIdx - 1u);

      ActiveJob->Result = vSwUpdM_Segment_SearchSegment(&dynamicSegmentId, vSwUpdM_GetStartAddressOfSegment(staticSegmentId));
      if (ActiveJob->Result == E_OK)
      {
        segment = vSwUpdM_GetAddrVarSegments(dynamicSegmentId); /* PRQA S 2963 */ /* MD_vSwUpdM_2963_InitializationChecked */

        /* #420 If nothing is left to do for current segment
         *   Advance job state to continue with next segment. */
        ActiveJob->State = VSWUPDM_JOB_STATE_FINALIZE_MODULE_NEXT_SEGMENT;

        /* #430 If segment doesn't end at the very end of address area. */
        if (segment->ReservedEndAddressOfVarSegments < VSWUPDM_MAX_ADDRESS)
        {
          vSwUpdM_SegmentIdValueType freeSegmentId;

          /* #440 Search segment directly behind reserved segment. */
          ActiveJob->Result = vSwUpdM_Segment_SearchSegment(&freeSegmentId, segment->ReservedEndAddressOfVarSegments + 1u);

          if (ActiveJob->Result == E_OK)
          {
            /* #450 If segment is a free segment
             *   Advance job state to prepare segment for filling next. */
            if (vSwUpdM_GetVarSegments(freeSegmentId).ClassOfVarSegments == VSWUPDM_CLASS_OF_VAR_SEGMENTS_FREE) /* PRQA S 2963 */ /* MD_vSwUpdM_2963_InitializationChecked */
            {
              ActiveJob->EntityIds.SegmentId.DynamicSegmentId = freeSegmentId;
              ActiveJob->State = VSWUPDM_JOB_STATE_FINALIZE_MODULE_PREPARE_SEGMENT;
            }
          }
        }
      }

      break;
    }
#endif
    case VSWUPDM_JOB_STATE_FINALIZE_MODULE_EVAL_USED_SEGMENT:
    /* #500 If current used segment shall be evaluated */
    {
      vSwUpdM_SegmentIdType       segmentId;
      vSwUpdM_VarSegmentsPtrType  segment; /* PRQA S 3679 */ /* MD_vSwUpdM_Rule8.13_3679_PointerToModifiableData */

      /* #510 Get used segment of module by current index. */
      (void)vSwUpdM_GetSegmentIdOfModuleByIndex(&segmentId, ActiveJob->EntityIds.ModuleId, ActiveJob->EntityIds.SegmentIdx);
      segment = vSwUpdM_GetAddrVarSegments(segmentId.DynamicSegmentId);

      /* #520 If nothing is left to do for current segment
       *   Advance job state to continue with next segment. */
      ActiveJob->State = VSWUPDM_JOB_STATE_FINALIZE_MODULE_NEXT_SEGMENT;

      /* #530 If segment doesn't end at the very end of address area. */
      if (segment->ReservedEndAddressOfVarSegments < VSWUPDM_MAX_ADDRESS)
      {
        vSwUpdM_SegmentIdValueType freeSegmentId;

        /* #540 Search segment directly behind reserved segment. */
        if (vSwUpdM_Segment_SearchSegment(&freeSegmentId, segment->ReservedEndAddressOfVarSegments + 1u) == E_OK)
        {
          /* #550 If segment is a free segment
           *   Advance job state to prepare segment for filling next. */
          if (vSwUpdM_GetVarSegments(freeSegmentId).ClassOfVarSegments == VSWUPDM_CLASS_OF_VAR_SEGMENTS_FREE)
          {
            ActiveJob->EntityIds.SegmentId.DynamicSegmentId = freeSegmentId;
            ActiveJob->State = VSWUPDM_JOB_STATE_FINALIZE_MODULE_PREPARE_SEGMENT;
          }
        }
      }

      break;
    }
    case VSWUPDM_JOB_STATE_FINALIZE_MODULE_PREPARE_SEGMENT:
    /* #600 If segment shall be prepared for filling */
    {
      vSwUpdM_LengthOfVarSegmentsType fillRemainder;
      vSwUpdM_VarSegmentsPtrType      segment = vSwUpdM_GetAddrVarSegments(ActiveJob->EntityIds.SegmentId.DynamicSegmentId);

      /* #610 If nothing is left to do for current segment
       *   Advance job state to continue with next segment. */
      ActiveJob->State = VSWUPDM_JOB_STATE_FINALIZE_MODULE_NEXT_SEGMENT;

      /* #620 Calculate remaining length to reserved end of segment, which wasn't filled yet. */
      fillRemainder = (segment->ReservedEndAddressOfVarSegments - segment->WriteAddressOfVarSegments) + 1u;

      /* #630 If segment was already filled completely */
      if (fillRemainder == 0u)
      {
        /* #631 Nothing left to do for current segment.
          *  Advance job state to continue with next segment. */
        retVal = VSWUPDM_JOB_STATUS_ACTIVE;
      }
      /* #640 Otherwise */
      else
      {
        /* #641 Trigger opening of current segment.
          *   Required for updating of resume information. */
        (void)vSwUpdM_Segment_OpenSegment(ActiveJob->EntityIds.SegmentId, VSWUPDM_SID_NONE, ActiveJob, ActiveJob->Source);

        /* #641 Update the states of all entities affected by upcoming write operation. */
        (void)vSwUpdM_Module_UpdateAndPersistState(ActiveJob->EntityIds.PartitionId, ActiveJob->EntityIds.PartitionState, ActiveJob->EntityIds.ModuleId, VSWUPDM_MODULE_STATE_DIRTY, ActiveJob, ActiveJob->Source);
        vSwUpdM_Job_PrepareWriteOperation(ActiveJob, segment, TRUE);

        /* #643 Advance job state to fill current segment next. */
        ActiveJob->State = VSWUPDM_JOB_STATE_FINALIZE_MODULE_FILL_SEGMENT;
      }
      /* #650 Otherwise, nothing to be done for current segment.
       *   Advance job state to continue with next segment. */

      break;
    }
    case VSWUPDM_JOB_STATE_FINALIZE_MODULE_FILL_SEGMENT:
    /* #700 If current segment shall be filled */
    {
      vSwUpdM_VarSegmentsPtrType      segment = vSwUpdM_GetAddrVarSegments(ActiveJob->EntityIds.SegmentId.DynamicSegmentId);
      vSwUpdM_LengthOfVarSegmentsType length  = (segment->ReservedEndAddressOfVarSegments - segment->WriteAddressOfVarSegments) + 1u;
      Std_ReturnType                  spawnResult;
      vSwUpdM_JobPtrType              spawnedJob;

      /* #710 If resume info shall be updated by job
       *   Update resume information: Set state to "active" and resume address to write address of current segment. */
      if (ActiveJob->UpdateResumeInfo == TRUE)
      {
        vSwUpdM_AddressType writeAddress;
        vSwUpdM_Segment_GetApparentWriteAddress(segment, &writeAddress);

        vSwUpdM_ResumeInfo_UpdateState(ActiveJob->EntityIds.PartitionState, VSWUPDM_SID_FINALIZE_MODULE, VSWUPDM_RESUME_STATE_ACTIVE, writeAddress, VSWUPDM_UNDEFINED_ADDRESS, writeAddress, TRUE);
      }

      /* #720 Enter critical section to ensure exclusive access of state and job queue. */
      VSWUPDM_ENTER_CRITICAL_SECTION();

      /* #730 Spawn job to fill (remaining) range of current segment with configured pattern.
        *   Use a higher priority than active job. */
      spawnedJob = vSwUpdM_Job_Spawn(&spawnResult, VSWUPDM_JOB_TYPE_FILL_MEMORY, VSWUPDM_JOB_OPERATION_DEFAULT, ActiveJob->CurrentPrio + 1u, VSWUPDM_SID_NONE, ActiveJob, ActiveJob->Source);

      /* #740 Job attributes are safe to be modified when job was successfully spawned and access is still protected by critical section. */
      if (spawnResult == E_OK)
      {
        /* #741 Pass entity IDs to fill job and use target address to pass the write address of the current segment. */
        spawnedJob->EntityIds     = ActiveJob->EntityIds;
        spawnedJob->TargetAddress = segment->WriteAddressOfVarSegments;

        /* #742 Pass length to be filled as used space of the virtual input buffer of the fill job. */
        (void) vSwUpdM_Buffer_InitAndAddData(spawnedJob->InputBuffer, NULL_PTR, length);
      }

      /* #750 Leave critical section ensuring exclusive access of state and job queue. */
      VSWUPDM_LEAVE_CRITICAL_SECTION();

      /* #760 Advance job state to close current segment next. */
      ActiveJob->State = VSWUPDM_JOB_STATE_FINALIZE_MODULE_CLOSE_SEGMENT;

      break;
    }
    case VSWUPDM_JOB_STATE_FINALIZE_MODULE_CLOSE_SEGMENT:
    /* #800 If current segment shall be closed */
    {
      /* #810 Trigger closing of current segment. */
      (void)vSwUpdM_Segment_CloseSegment(ActiveJob->EntityIds.SegmentId, VSWUPDM_SID_NONE, ActiveJob, ActiveJob->Source);

      /* #820 Advance job state to handle the next segment. */
      ActiveJob->State = VSWUPDM_JOB_STATE_FINALIZE_MODULE_NEXT_SEGMENT;

      break;
    }
    case VSWUPDM_JOB_STATE_FINALIZE_MODULE_NEXT_SEGMENT:
    /* #900 If the next segment shall be handled */
    {
      retVal = VSWUPDM_JOB_STATUS_ACTIVE;

      /* #910 Handle the next segment */
      ActiveJob->EntityIds.SegmentIdx++;

      /* #920 If at least one region is still pending */
      if (ActiveJob->EntityIds.RegionIdx < vSwUpdM_EntityData.Count.RegionCount)
      {

#if (VSWUPDM_SEGMENT == STD_ON)
        /* #930 If this wasn't the last segment of the current region
         *   Advance job state to evaluate the next reserved segment. */
        if (ActiveJob->EntityIds.SegmentIdx < ((vSwUpdM_SegmentIdxType)vSwUpdM_GetNumSegmentsOfRegion(ActiveJob->EntityIds.RegionId) + 1u))
        {
          ActiveJob->State = VSWUPDM_JOB_STATE_FINALIZE_MODULE_EVAL_RESERVED_SEGMENT;
        }
        /* #931 Otherwise: */
        else
#endif
        {
          /* #940 Handle the next region of the module, while resetting the segment index. */
          ActiveJob->EntityIds.RegionIdx++;
          ActiveJob->EntityIds.SegmentIdx = 0u;

          /* #950 If this wasn't the last region of the requested module
           *   Advance job state to evaluate the next free segment. */
          if (ActiveJob->EntityIds.RegionIdx < vSwUpdM_EntityData.Count.RegionCount)
          {
            ActiveJob->State = VSWUPDM_JOB_STATE_FINALIZE_MODULE_EVAL_FREE_SEGMENT;
          }
          /* #951 Otherwise, if there are any used segments
           *   Advance job state to evaluate the first used segment next. */
          else
          {
            if (vSwUpdM_EntityData.Count.ExternalSegmentCount > 0u)
            {
              ActiveJob->State = VSWUPDM_JOB_STATE_FINALIZE_MODULE_EVAL_USED_SEGMENT;
            }
          }
        }
      }
      /* #960 Otherwise: */
      else
      {
        /* #970 If this wasn't the last external segment
         *   Advance job state to handle the next used segment. */
        if (ActiveJob->EntityIds.SegmentIdx < vSwUpdM_EntityData.Count.ExternalSegmentCount)
        {
          ActiveJob->State = VSWUPDM_JOB_STATE_FINALIZE_MODULE_EVAL_USED_SEGMENT;
        }
        /* #980 Otherwise: */
        else
        {
          retVal = VSWUPDM_JOB_STATUS_PENDING;

          /* #981 If resume info shall be updated by job
           *   Update resume information to indicate that service is finished, taking over service ID and address.
           *   Force persisting of resume information. */
          if (ActiveJob->UpdateResumeInfo == TRUE)
          {
            (void)vSwUpdM_ResumeInfo_UpdateAndPersistState(VSWUPDM_PART_STATE_UNDEFINED, VSWUPDM_SID_NONE, VSWUPDM_RESUME_STATE_FINISHED, vSwUpdM_ResumeInfo.ResumeInfo.MemoryAddress, vSwUpdM_ResumeInfo.ResumeInfo.StreamAddress, vSwUpdM_ResumeInfo.TriggerAddress, vSwUpdM_ResumeInfo.ResumeInfo.IsAddressValid, ActiveJob->Source);
          }

          /* #982 Update state of requested module to "finalized" and trigger persisting of module state. */
          (void)vSwUpdM_Module_UpdateAndPersistState(ActiveJob->EntityIds.PartitionId, ActiveJob->EntityIds.PartitionState, ActiveJob->EntityIds.ModuleId, VSWUPDM_MODULE_STATE_FINALIZED, ActiveJob, ActiveJob->Source);

          /* #983 Advance job state to close module. */
          ActiveJob->State = VSWUPDM_JOB_STATE_FINALIZE_MODULE_CLOSE;
        }
      }

      break;
    }
    case VSWUPDM_JOB_STATE_FINALIZE_MODULE_CLOSE:
    /* #1000 If module shall be closed */
    {
      /* #1010 If modules was opened implicitly by finalize request (indicated by job operation) */
      if (ActiveJob->Operation == VSWUPDM_JOB_OPERATION_CLOSE_MODULE)
      {
        /* #1011 Trigger closing of requested module. */
        (void)vSwUpdM_Module_CloseModule(ActiveJob->EntityIds.ModuleId, VSWUPDM_SID_NONE, ActiveJob->Source, ActiveJob);

        /* #1012 Reset job operation to default value. */
        ActiveJob->Operation = VSWUPDM_JOB_OPERATION_DEFAULT;
        /* #1013 Forward to final state, waiting for result of closing the module. */
        ActiveJob->State     = VSWUPDM_JOB_STATE_FINAL;
      }
      /* #1020 Otherwise
       *   Indicate that job is finished. */
      else
      {
        retVal = VSWUPDM_JOB_STATUS_FINISHED;
      }

      break;
    }
    case VSWUPDM_JOB_STATE_FINAL:
    /* #1100 If waiting for module to be closed
     *   Indicate that job is finished. */
    {
      retVal = VSWUPDM_JOB_STATUS_FINISHED;

      break;
    }
    case VSWUPDM_JOB_STATE_EVAL_HOOK:
    /* #1200 If result of hook function shall be evaluated */
    {
      /* #1201 If module isn't opened yet */
      if (vSwUpdM_EntityData.OpenIds.ModuleId == VSWUPDM_INVALID_ID)
      {
        /* #1202 Use default handling for hook return value. */
        retVal = vSwUpdM_Job_HandleDefaultRetry(ActiveJob);
      }
      /* #1203 Otherwise: */
      else
      {
        vSwUpdM_ServiceIdType resumeService = VSWUPDM_SID_FINALIZE_MODULE;

        /* #1210 If restart action with a module granularity is requested
         *   Module must be re-erased and contents must be requested again, using ProcessStreamData sequence. */
        if ( (ActiveJob->HookAction == VSWUPDM_HOOK_ACTION_RESTART)
          && (ActiveJob->RetryGranularity == VSWUPDM_RETRY_GRANULARITY_MODULE) )
        {
          resumeService = VSWUPDM_SID_PROCESS_STREAM_DATA;
        }
        /* #1220 Otherwise
         *   Restart or retry action can directly be done for FinalizeModule service. */

        /* #1230 Handle retry action for write operation of service determined before. */
        retVal = vSwUpdM_Job_HandleWriteRetry(ActiveJob, resumeService);
      }

      break;
    }
    case VSWUPDM_JOB_STATE_FAILED:
    /* #1300 If job state is "failed", because of negative child result
     *   Return with negative result taken over from child job. */
    {
      break;
    }
    default:
    /* #1400 Otherwise: Invalid state.
     *   Set error in job result. */
    {
      ActiveJob->Result = VSWUPDM_E_INV_STATE;
      break;
    }
  }

  return retVal;
  /* PRQA S 6010, 6030, 6050, 6080 1 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */
} /* vSwUpdM_JobHandler_FinalizeModuleLocal */

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_ProcessModuleLocal
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
 */
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_ProcessModuleLocal)
{
  vSwUpdM_JobStatusType retVal = VSWUPDM_JOB_STATUS_PENDING; /* PRQA S 2981 */ /* MD_MSR_RetVal */

  VSWUPDM_DUMMY_STATEMENTS_JOB_HANDLER(); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  /* #10 Evaluate child result from previous cycle.
   *   If not okay, apply child result.
   *   If result is SUSPENDED suspend job. */
  retVal = vSwUpdM_Job_EvaluateChildResultOrSuspend(ActiveState, ActiveJob, FALSE);

  if (retVal != VSWUPDM_JOB_STATUS_SUSPENDED)
  {
    /* #20 Evaluate job state. */
    switch (ActiveJob->State)
    {
      case VSWUPDM_JOB_STATE_INITIAL:
      /* #100 In initial state: */
      {
        /* #110 If VerifyModule service is requested */
        if (ActiveJob->ServiceId == VSWUPDM_SID_VERIFY_MODULE)
        {
#if (VSWUPDM_EXISTS_VERIFY_MODULE_TYPEOFDATAPROCESSES == STD_OFF)
          /* #111 If no verify module pipe is configured and local node is owner of module: Set module to verified. */
# if (VSWUPDM_MULTICONTROLLER_SUPPORT == STD_ON)
          vSwUpdM_NodeGroupIterType groupIndex = vSwUpdM_GetNodeGroupOwnersIdxOfModule(ActiveJob->EntityIds.ModuleId);

          if (vSwUpdM_IsWithLocalNodeOfNodeGroup(groupIndex))
# endif
          {
            (void)vSwUpdM_Module_UpdateAndPersistState(ActiveJob->EntityIds.PartitionId, ActiveJob->EntityIds.PartitionState, ActiveJob->EntityIds.ModuleId, VSWUPDM_MODULE_STATE_VERIFIED, ActiveJob, ActiveJob->Source);
          }
#else
          /* #112 Otherwise: Process module using verify pipe (set in service function).
           *   Do not update resume information. */
          vSwUpdM_Module_ProcessModule(ActiveJob, FALSE);
#endif
        }
        /* #120 Otherwise: Process module using pipe set in service function. */
        else
        {
          vSwUpdM_Module_ProcessModule(ActiveJob, ActiveJob->UpdateResumeInfo);
        }

        /* #130 Wait for processing to finish. */
        ActiveJob->State = VSWUPDM_JOB_STATE_FINAL;

        break;
      }
      case VSWUPDM_JOB_STATE_FINAL:
      /* #300 In final state: Just finish. */
      {
        retVal = VSWUPDM_JOB_STATUS_FINISHED;

        break;
      }
      case VSWUPDM_JOB_STATE_EVAL_HOOK:
      /* #400 In hook evaluation state: Handle hook return value. */
      {
        retVal = vSwUpdM_Job_HandleDefaultRetry(ActiveJob);

        break;
      }
      case VSWUPDM_JOB_STATE_FAILED:
      /* #500 In failed state: Report error. */
      {
        break;
      }
      default:
      /* #600 Otherwise: Report invalid state. */
      {
        ActiveJob->Result = VSWUPDM_E_INV_STATE;
        break;
      }
    }
  }

  return retVal;
} /* vSwUpdM_JobHandler_ProcessModuleLocal */

/**********************************************************************************************************************
 *  vSwUpdM_SubJobHandler_ProcessEntityRemoteInput
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
 */
VSWUPDM_SUB_JOB_HANDLER(vSwUpdM_SubJobHandler_ProcessEntityRemoteInput) /* PRQA S 3673 */ /* MD_vSwUpdM_Rule8.13_3673_PointerToConstParameter */
{
  vSwUpdM_JobStatusType retVal = VSWUPDM_JOB_STATUS_FINISHED; /* PRQA S 2981 */ /* MD_MSR_RetVal */

  VSWUPDM_DUMMY_STATEMENTS_JOB_HANDLER(); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

#if (VSWUPDM_MULTICONTROLLER_SUPPORT == STD_ON)
# if (VSWUPDM_EXTDATAINPUT == STD_ON)

  retVal = VSWUPDM_JOB_STATUS_PENDING;

  /* #10 Evaluate job state. */
  switch (ActiveJob->State)
  {
    case VSWUPDM_JOB_STATE_PROCESS_REMOTE_REQUEST_NEXT_INPUT:
    /* #100 If next remote input shall be requested: */
    {
      vSwUpdM_NodeIterType master = vSwUpdM_RemoteLockIsGrantedTo;

      /* #110 For each external input do: */
      if (ActiveJob->Count < vSwUpdM_ProcessUserData.InputCount)
      {
        vStreamProc_EntryPointInfoType entryPoint;
        vSwUpdM_DataStreamPtrType      data = NULL_PTR; /* PRQA S 2981 */ /* MD_vSwUpdM_Rule2.2_2981_2892_RedundantInitialization */

        /* #120 Get reference on output. */
        ActiveJob->Result = vSwUpdM_Pipe_RequestEntryPoint(
          vSwUpdM_ProcessData.PipeId,
          vSwUpdM_GetEntryPointIdOfExtDataInput((vSwUpdM_GetExtDataOutputStartIdxOfDataProcesses(vSwUpdM_ProcessData.ProcessId) + ActiveJob->Count)),
          vStreamProcConf_vStreamProcDataType_Undefined,
          1u,
          &entryPoint);

        if (ActiveJob->Result == E_OK)
        {
          data = vSwUpdM_Pipe_GetLiteralWriteBuffer(&entryPoint);

          if (data == NULL_PTR)
          {
            /* Unsupported datatype */
            ActiveJob->Result = E_NOT_OK;
          }
        }

        if (ActiveJob->Result == E_OK)
        {
          /* #140 Prepare buffer for data from remote node. */
          vSwUpdM_RemoteStreamHandleType handle = (vSwUpdM_RemoteStreamHandleType)ActiveJob->Count;

          ActiveJob->Result = vSwUpdM_RemoteStreamPrepareRx(handle, (P2VAR(uint8, AUTOMATIC, VSWUPDM_APPL_VAR)) data, entryPoint.WriteRequest.StorageInfo.DataTypeInfo.Size * entryPoint.WriteRequest.StorageInfo.AvailableLength, master);

          if (ActiveJob->Result == E_OK)
          {
            /* #150 Request data from remote node. */
#   if (VSWUPDM_LOCALINSTANCE_ACTS_AS_SLAVE == STD_ON)
          /* Wait for confirmation for RemoteProcessRequestInput */
            vSwUpdM_RemotePrepareResponseRxTarget(master, VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_REQUEST_PROCESS_INFO, ActiveJob);
            ActiveJob->Result = vRpcProxy_vSwUpdM_RemoteProcessRequestInput_Target(
              vSwUpdM_GetDestinationMainOfNode(master),
              (uint8) VSWUPDM_EXCTSCHEDULE_SERVICESTATE_RUN,
              vSwUpdM_GetProcessHandleOfDataProcesses(vSwUpdM_ProcessData.ProcessId),
              (uint8)ActiveJob->Count);

            if (ActiveJob->Result == E_OK)
            {
              /* #151 Store current service for eventual resume. */
              vSwUpdM_ExecCtrl_StoreRemoteResumeService(
                VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_REQUEST_PROCESS_INFO,
                VSWUPDM_INVALID_NODE_GROUP,
                master);
            }

            ActiveJob->State = VSWUPDM_JOB_STATE_PROCESS_REMOTE_WAIT_RX;
#   endif
          }
        }
      }
      else
        /* #160 No further external inputs left. Go to next state. */
      {
        ActiveJob->State = VSWUPDM_JOB_STATE_PROCESS_INIT_INTERNAL_EVAL_SCOPE;
        ActiveJob->Count = 0; /* Re initialize counter for next operation */
      }

      break;
    }
    case VSWUPDM_JOB_STATE_PROCESS_REMOTE_WAIT_RX:
    /* #200 If waiting for remote response: */
    {
      /* #210 In case of a failure: Abort stream. */
      if (vSwUpdM_RemoteStream_List[ActiveJob->Count].State == VSWUPDM_REMOTESTREAMSTATE_FAIL)
      {
        ActiveJob->Result = E_NOT_OK;
      }
      else
      {
          /* #220 Otherwise: If stream is done: */
        if (vSwUpdM_RemoteStream_List[ActiveJob->Count].State == VSWUPDM_REMOTESTREAMSTATE_DONE)
        {
          vStreamProc_EntryPointInfoType entryPoint;

          /* #230 Get reference on output. */
          if (vSwUpdM_Pipe_GetEntryPoint(
            vSwUpdM_ProcessData.PipeId,
            vSwUpdM_GetEntryPointIdOfExtDataInput(vSwUpdM_GetExtDataOutputStartIdxOfDataProcesses(vSwUpdM_ProcessData.ProcessId) + ActiveJob->Count),
            vStreamProcConf_vStreamProcDataType_Undefined,
            &entryPoint) == E_OK)
          {
            if (vStreamProc_AcknowledgeEntryPoint(vSwUpdM_ProcessData.PipeId, vSwUpdM_RemoteStream_List[ActiveJob->Count].AvailableLength, TRUE, &entryPoint) == VSTREAMPROC_OK)
            {
              vSwUpdM_RemoteStream_List[ActiveJob->Count].State = VSWUPDM_REMOTESTREAMSTATE_IDLE;

              /* #240 Request next input. */
              ActiveJob->Count++;
              ActiveJob->State = VSWUPDM_JOB_STATE_PROCESS_REMOTE_REQUEST_NEXT_INPUT;
            }
            else
            {
              ActiveJob->Result = VSWUPDM_E_STREAM_OPERATION_FAILED;
            }
          }
        }
      }

      break;
    }
    default:
    /* Nothing to do. */
    {
      break;
    }
  }
# endif
#endif

  return retVal;
  /* PRQA S 6030, 6050, 6080 1 */ /* MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF  */
} /* vSwUpdM_SubJobHandler_ProcessEntityRemoteInput */

/**********************************************************************************************************************
 *  vSwUpdM_SubJobHandler_ProcessEntityRemoteOutput
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
 *
 */
VSWUPDM_SUB_JOB_HANDLER(vSwUpdM_SubJobHandler_ProcessEntityRemoteOutput)  /* PRQA S 3673 */ /* MD_vSwUpdM_Rule8.13_3673_PointerToConstParameter */
{
  vSwUpdM_JobStatusType retVal = VSWUPDM_JOB_STATUS_FINISHED; /* PRQA S 2981 */ /* MD_MSR_RetVal */

  VSWUPDM_DUMMY_STATEMENTS_JOB_HANDLER(); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

#if (VSWUPDM_MULTICONTROLLER_SUPPORT == STD_ON)
# if (VSWUPDM_EXTDATAOUTPUT == STD_ON)

  retVal = VSWUPDM_JOB_STATUS_PENDING;

  /* #10 Evaluate job state. */
  switch (ActiveJob->State)
  {
    case VSWUPDM_JOB_STATE_PROCESS_PROVIDE_EXTERNAL_RESULTS_REMOTE:
    /* #100 If remote results shall be provided: */
    {
      /* #110 For each external output do: */
      if (ActiveJob->Count < vSwUpdM_ProcessUserData.OutputCount)
      {
        Std_ReturnType                 streamResult = E_NOT_OK;
        vStreamProc_ExitPointInfoType  exitPoint;
        vSwUpdM_NodeIterType           master = vSwUpdM_RemoteLockIsGrantedTo;
        Std_ReturnType                 result;

        vSwUpdM_DataReadStreamPtrType data = NULL_PTR; /* PRQA S 2981 */ /* MD_vSwUpdM_Rule2.2_2981_2892_RedundantInitialization */

        /* #120 Read data from pipe. */
        if (vSwUpdM_Pipe_RequestExitPoint(
          vSwUpdM_ProcessData.PipeId,
          vSwUpdM_GetExitPointIdOfExtDataOutput(vSwUpdM_GetExtDataOutputStartIdxOfDataProcesses(vSwUpdM_ProcessData.ProcessId) + ActiveJob->Count),
          vStreamProcConf_vStreamProcDataType_Undefined,
          1u,
          &exitPoint) == E_OK)
        {
          streamResult = E_OK;

          data = vSwUpdM_Pipe_GetLiteralReadBuffer(&exitPoint);
          if (data == NULL_PTR)
          {
            /* Unsupported datatype */
            streamResult = E_NOT_OK;
          }
        }
        /* #130 Initiate a remote stream to transmit data to remote node. */
        if ((streamResult == E_OK) && (exitPoint.ReadRequest.StorageInfo.AvailableLength > 0u))
        {
          vSwUpdM_RemoteStreamHandleType handle = (vSwUpdM_RemoteStreamHandleType)(ActiveJob->Count + vSwUpdM_ProcessUserData.InputCount);

          /* PRQA S 0311 1 */ /* MD_vSwUpdM_Rule11.5_0311_RemoteBufferConstConfigValues */
          result = vSwUpdM_RemoteStreamStartTx(handle, (P2VAR(uint8, AUTOMATIC, VSWUPDM_APPL_VAR)) data, exitPoint.ReadRequest.StorageInfo.AvailableLength * exitPoint.ReadRequest.StorageInfo.DataTypeInfo.Size, master);

          /* #140 Evaluate result of transmission: */
          switch (result)
          {
            case E_OK:
            /* #141 On success: Wait until data is transmitted. */
            {
              ActiveJob->State = VSWUPDM_JOB_STATE_PROCESS_PROVIDE_EXTERNAL_RESULTS_REMOTE_WAIT;
              break;
            }
            case E_NOT_OK:
            /* #142 Transmission failed (busy) - try again next time. */
            {
              break;
            }
            case VSWUPDM_E_INVALID_STREAM_STATE:
            case VSWUPDM_E_OUT_OF_RANGE:
            default:
            /* #142 Transmission failed - propagate error. */
            {
              ActiveJob->Result = result;
              break;
            }
          }
        }
        else
        {
          ActiveJob->Result = E_NOT_OK;
        }
      }
      else
      {
        /* #200 No more external outputs left. Go to next state. */
        ActiveJob->State = VSWUPDM_JOB_STATE_PROCESS_COLLECT_INTERNAL_RESULTS;
        retVal = VSWUPDM_JOB_STATUS_ACTIVE; /* Just call this handler again in same MainFunction cycle to start initialization of first node */
      }

      break;
    }
    case VSWUPDM_JOB_STATE_PROCESS_PROVIDE_EXTERNAL_RESULTS_REMOTE_WAIT:
    /* #300 If state is REMOTE PROVIDE EXTERNAl RESULTS WAIT:
      *   Transmission of external output data is done.
      */
    {
      vSwUpdM_RemoteStreamHandleType handle = (vSwUpdM_RemoteStreamHandleType)(ActiveJob->Count + vSwUpdM_ProcessUserData.InputCount);

      /* #310 Evaluate result of transmission. */
      switch (vSwUpdM_RemoteStream_List[handle].State)
      {
        case  VSWUPDM_REMOTESTREAMSTATE_FAIL:
        /* #320 In case of failure: Propagate error. */
        {
          ActiveJob->Result = E_NOT_OK;
          vSwUpdM_RemoteStream_List[handle].State = VSWUPDM_REMOTESTREAMSTATE_IDLE;

          break;
        }
        case VSWUPDM_REMOTESTREAMSTATE_IDLE:
        /* #330 On success: */
        {
          vStreamProc_ExitPointInfoType   exitPoint;

          /* #331 Release buffer. */
          if (ActiveJob->Result == E_OK)
          {
            ActiveJob->Result = vSwUpdM_Pipe_GetExitPoint(
              vSwUpdM_ProcessData.PipeId,
              vSwUpdM_GetExitPointIdOfExtDataOutput(vSwUpdM_GetExtDataOutputStartIdxOfDataProcesses(vSwUpdM_ProcessData.ProcessId) + ActiveJob->Count),
              vStreamProcConf_vStreamProcDataType_Undefined,
              &exitPoint);
          }

          if (ActiveJob->Result == E_OK)
          {
            if (vStreamProc_AcknowledgeExitPoint(vSwUpdM_ProcessData.PipeId, vSwUpdM_RemoteStream_List[handle].AvailableLength, TRUE, &exitPoint) != VSTREAMPROC_OK)
            {
              ActiveJob->Result = E_NOT_OK;
            }
          }

          if (ActiveJob->Result == E_OK)
          {
            /* #331 Transmit next external output to remote node. */
            ActiveJob->Count++;

            ActiveJob->State = VSWUPDM_JOB_STATE_PROCESS_PROVIDE_EXTERNAL_RESULTS_REMOTE;
          }
          break;
        }
        case VSWUPDM_REMOTESTREAMSTATE_TX_RESPONSE:
        case VSWUPDM_REMOTESTREAMSTATE_TX_WAIT_END:
        /* #340 Still waiting for a response or end of transmission:
         *   Do nothing. */
        {
          break;
        }
        default:
        {
          ActiveJob->Result = E_NOT_OK;
          break;
        }
      }

      break;
    }
    default:
    /* Nothing to do. */
    {
      break;
    }
  }
# endif
#endif

  return retVal;
  /* PRQA S 6030 1 */ /* MD_MSR_STCYC */
} /* vSwUpdM_SubJobHandler_ProcessEntityRemoteOutput */

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_ProcessEntity
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
 *
 *
 *
 *
 *
 *
 */
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_ProcessEntity)
{
  vSwUpdM_JobStatusType retVal  = VSWUPDM_JOB_STATUS_PENDING; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  boolean               cleanup = FALSE;
  Std_ReturnType        streamResult;

  vSwUpdM_SubScopeOfDataProcessesType subScope           = vSwUpdM_GetSubScopeOfDataProcesses(vSwUpdM_ProcessData.ProcessId);
  vSwUpdM_SubScopeAttributeType       subScopeAttributes = vSwUpdM_Pipe_GetSubScopeAttributes(subScope);

  VSWUPDM_DUMMY_STATEMENTS_JOB_HANDLER(); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  /* #10 Evaluate child result from previous cycle.
   *   If not okay, apply child result.
   *   If result is SUSPENDED suspend job. */
  retVal = vSwUpdM_Job_EvaluateChildResultOrSuspend(ActiveState, ActiveJob, TRUE);

  if (retVal != VSWUPDM_JOB_STATUS_SUSPENDED)
  {
    /* #20 Evaluate job state. */
    switch (ActiveJob->State)
    {
      case VSWUPDM_JOB_STATE_INITIAL:
      /* #1000 If state is INITIAL: */
      {
        /* #1100 Open module if not already open. */
        if (vSwUpdM_EntityData.OpenIds.ModuleId == VSWUPDM_INVALID_ID)
        {
          (void)vSwUpdM_Module_OpenModule(ActiveJob->EntityIds.ModuleId, TRUE, VSWUPDM_SID_NONE, ActiveJob->Source, ActiveJob);
          /* Use job operation to remember that module was opened implicitly. */
          ActiveJob->Operation = VSWUPDM_JOB_OPERATION_CLOSE_MODULE;
        }
        else
        {
          retVal = VSWUPDM_JOB_STATUS_ACTIVE;
        }

        /* #1200 Next state init pipe. */
        ActiveJob->State = VSWUPDM_JOB_STATE_PROCESS_INIT_PIPE;

        break;
      }
      case VSWUPDM_JOB_STATE_PROCESS_INIT_PIPE:
      /* #2000 If state is INIT PIPE: */
      {
        /* #2100 Initialize counter for setting up pipe entry and exit nodes. */
        ActiveJob->Count = 0;

        /* #2200 Initialize configured process. */
        streamResult = vStreamProc_InitPipe(vSwUpdM_ProcessData.PipeId);

        if (streamResult == E_OK)
        {
          /* #2300 Open configured pipe. */
          streamResult = vStreamProc_Open(vSwUpdM_ProcessData.PipeId);
        }

        if (streamResult == E_OK)
        {
          /* #2400 Set internal mode. */
          streamResult = vStreamProc_SetMode(vSwUpdM_ProcessData.PipeId, vSwUpdM_ProcessData.Operation);
        }

        if (streamResult == E_OK)
        {
          /* #2500 Set user mode. */
          streamResult = vStreamProc_SetMode(vSwUpdM_ProcessData.PipeId, vSwUpdM_ProcessUserData.Operation);
        }

        /* #2700 Trigger post actions based on current state. */
        if (streamResult == E_OK)
        {
#if (VSWUPDM_MULTICONTROLLER_SUPPORT == STD_ON)
          /* #2710 If this stream process is triggered by a remote node: */
          if ( (vSwUpdM_Pipe_IsSubScopeAttributeSet(subScopeAttributes, VSWUPDM_SUB_SCOPE_ATTRIBUTE_REMOTE_EXECUTION) == TRUE)
            && (ActiveJob->Source != (vSwUpdM_NodeIterType)vSwUpdM_GetLocalNode()) )
          {
# if (VSWUPDM_EXTDATAINPUT == STD_ON)
            if (vSwUpdM_IsProcessHandleUsedOfDataProcesses(vSwUpdM_ProcessData.ProcessId))
            {
              /* #2711 If remote input data is required, go to state REMOTE_REQUEST_NEXT_INPUT. */
              ActiveJob->State = VSWUPDM_JOB_STATE_PROCESS_REMOTE_REQUEST_NEXT_INPUT;
            }
            else
            {
              ActiveJob->Result = VSWUPDM_E_INVALID_STREAM_OPERATION;
            }
# else
            /* #2712 Otherwise: No remote input data is required. Go to INIT_INTERNAL_SELECT_SEGMENT. */
            ActiveJob->State = VSWUPDM_JOB_STATE_PROCESS_INIT_INTERNAL_EVAL_SCOPE;
# endif
          }
          else
#endif
          {
            /* #2720 Local input data is required. */
            ActiveJob->State = VSWUPDM_JOB_STATE_PROCESS_INIT_EXTERNAL_ENTRY_NODES;
          }
        }

        /* #2900 If pipe has input for operation mode and this is a fresh start:
         *   Forward to initial module state (if any is configured). */
        if (streamResult == E_OK)
        {
          vSwUpdM_ModuleStateType       initialModuleState = vSwUpdM_ProcessData.ProcessConfig->StateForward.Initial.ModuleState;

          if ( (vSwUpdM_Pipe_HasInternalEntryPoint(vSwUpdM_ProcessData.ProcessId, vSwUpdMConf_vSwUpdMDataInputType_InputOperation) == TRUE)
            && (vSwUpdM_ProcessData.ProcOperation == VSWUPDM_PROC_NODE_OPERATION_START)
            && (initialModuleState != VSWUPDM_MODULE_STATE_UNDEFINED) )
          {
            streamResult = vSwUpdM_Module_UpdateAndPersistState(ActiveJob->EntityIds.PartitionId, ActiveJob->EntityIds.PartitionState, ActiveJob->EntityIds.ModuleId, initialModuleState, ActiveJob, ActiveJob->Source);
          }
        }

        /* #2910 If resume info shall be updated by job
         *   Update resume information: Persist state "active" and directly set to "pending" for later shutdown. */
        if (streamResult == E_OK)
        {
          if ( (ActiveJob->UpdateResumeInfo == TRUE)
            && (vSwUpdM_ProcessData.ProcessConfig->StateForward.Initial.UpdateResumeInfo == TRUE) )
          {
            streamResult = vSwUpdM_ResumeInfo_UpdateAndPersistState(VSWUPDM_PART_STATE_UNDEFINED, VSWUPDM_SID_NONE, VSWUPDM_RESUME_STATE_ACTIVE, vSwUpdM_ResumeInfo.ResumeInfo.MemoryAddress, vSwUpdM_ResumeInfo.ResumeInfo.StreamAddress, vSwUpdM_ResumeInfo.TriggerAddress, vSwUpdM_ResumeInfo.ResumeInfo.IsAddressValid, ActiveJob->Source);
            vSwUpdM_ResumeInfo_UpdateState(VSWUPDM_PART_STATE_UNDEFINED, VSWUPDM_SID_NONE, VSWUPDM_RESUME_STATE_PENDING, vSwUpdM_ResumeInfo.ResumeInfo.MemoryAddress, vSwUpdM_ResumeInfo.ResumeInfo.StreamAddress, vSwUpdM_ResumeInfo.TriggerAddress, vSwUpdM_ResumeInfo.ResumeInfo.IsAddressValid);
          }
        }

        if (streamResult == E_OK)
        {
          ActiveJob->Count = 0; /* Counter to iterate over all inputs. */
          /* HINT: ACTIVE will be ignored if update of module state and/or resume info is scheduled. */
          retVal = VSWUPDM_JOB_STATUS_ACTIVE; /* Just call this handler again in same MainFunction cycle to start initialization of first node */
        }
        else
        {
          ActiveJob->Result = E_NOT_OK;
        }
        break;
      }
      case VSWUPDM_JOB_STATE_PROCESS_REMOTE_REQUEST_NEXT_INPUT:
      /* #3000 If state is VSWUPDM_JOB_STATE_PROCESS_REMOTE_REQUEST_NEXT_INPUT: */
      case VSWUPDM_JOB_STATE_PROCESS_REMOTE_WAIT_RX:
      /* #4000 If state is REMOTE WAIT RX: */
      {
        /* #4100 Handle remote inputs in sub-job handler. */
        retVal = vSwUpdM_SubJobHandler_ProcessEntityRemoteInput(ActiveState, ActiveJob, ProcessingLength);

        break;
      }
      case VSWUPDM_JOB_STATE_PROCESS_INIT_EXTERNAL_ENTRY_NODES:  /**< Loop over external entry nodes and write data to stream processor */
      /* #5000 If state is INIT EXTERNAL ENTRY NODES: */
      {
#if (VSWUPDM_EXTDATAINPUT == STD_ON)
        if (ActiveJob->Count < vSwUpdM_ProcessUserData.InputCount)
          /* #5100 If there is still at least one external entry point not initialized, provide given data to entry point. */
        {
          streamResult = vSwUpdM_Pipe_WriteExtInputData(
            vSwUpdM_ProcessData.PipeId,
            (vSwUpdM_ExtDataInputIterType) (vSwUpdM_GetExtDataInputStartIdxOfDataProcesses(vSwUpdM_ProcessData.ProcessId) + ActiveJob->Count),
            (vSwUpdM_ConstDataPointerType) vSwUpdM_ProcessUserData.InputData[ActiveJob->Count].DataPtr,
            vSwUpdM_ProcessUserData.InputData[ActiveJob->Count].Length);

          if (streamResult == E_OK)
          {
            ActiveJob->Count++;
          }
          else
          {
            ActiveJob->Result = E_NOT_OK;
          }
        }
        else
#endif
        /* #5200 Otherwise: switch to next state. */
        {
          ActiveJob->State = VSWUPDM_JOB_STATE_PROCESS_INIT_INTERNAL_EVAL_SCOPE; /* Continue directly with processing the pipe */
          retVal = VSWUPDM_JOB_STATUS_ACTIVE; /* Just call this handler again in same MainFunction cycle to start initialization of first node */
        }
        break;
      }
      case VSWUPDM_JOB_STATE_PROCESS_INIT_INTERNAL_EVAL_SCOPE:
      /* #6000 If state is INIT INTERNAL ENTRY NODES EVAL SCOPE: */
      {
        /* #6100 Depending on (sub-)scope, select next state. */
        /* #6130 When sub-scope determines that segments shall be handled */
        if (vSwUpdM_Pipe_IsSubScopeAttributeSet(subScopeAttributes, VSWUPDM_SUB_SCOPE_ATTRIBUTE_SEGMENTS) == TRUE)
        {
          /* #6131 Select first segment (by address). */
          ActiveJob->Result = vSwUpdM_Segment_SearchSegment(&ActiveJob->EntityIds.SegmentId.DynamicSegmentId, 0u);
          /* #6132 Advance job state to select matching segments next. */
          ActiveJob->State = VSWUPDM_JOB_STATE_PROCESS_INIT_INTERNAL_SELECT_SEGMENT;
        }
        /* #6140 Otherwise: Advance job state to handle internal entry nodes next. */
        else
        {
          ActiveJob->State = VSWUPDM_JOB_STATE_PROCESS_INIT_INTERNAL_ENTRY_NODES;
        }

        retVal = VSWUPDM_JOB_STATUS_ACTIVE; /* Just call this handler again in same MainFunction cycle to start initialization of first node */

        break;
      }
      case VSWUPDM_JOB_STATE_PROCESS_INIT_INTERNAL_SELECT_SEGMENT:
      /* #7000 If state is INIT INTERNAL ENTRY NODES SELECT SEGMENT: */
      {
        boolean                         processSegment = FALSE;
        /* PRQA S 3679 1 */ /* MD_vSwUpdM_Rule8.13_3679_PointerToModifiableData */
        vSwUpdM_VarSegmentsPtrType      segment = vSwUpdM_GetAddrVarSegments(ActiveJob->EntityIds.SegmentId.DynamicSegmentId);

        /* #7100 Determine if the current segment needs to be processed for given sub scope. */
        switch (segment->ClassOfVarSegments)
        {
          case VSWUPDM_CLASS_OF_VAR_SEGMENTS_USED:
          {
            processSegment = vSwUpdM_Pipe_IsSubScopeAttributeSet(subScopeAttributes, VSWUPDM_SUB_SCOPE_ATTRIBUTE_SEGMENT_CLASS_USED);

            break;
          }
          case VSWUPDM_CLASS_OF_VAR_SEGMENTS_FREE:
          {
            processSegment = vSwUpdM_Pipe_IsSubScopeAttributeSet(subScopeAttributes, VSWUPDM_SUB_SCOPE_ATTRIBUTE_SEGMENT_CLASS_FREE);

            break;
          }
          default:
          {
            /* PRQA S 2016 */ /* MD_MSR_EmptyClause */
            break;
          }
        }

        /* #7200 Depending on sub scope, Fully written segments may not need to be processed. */
        if ((vSwUpdM_Pipe_IsSubScopeAttributeSet(subScopeAttributes, VSWUPDM_SUB_SCOPE_ATTRIBUTE_PARTIAL_SEGMENT) == TRUE)
          && (processSegment == TRUE))
        {
          if (segment->WriteAddressOfVarSegments >= segment->ReservedEndAddressOfVarSegments)
          {
            processSegment = FALSE;
          }
        }

        /* #7300 If segment is selected for processing go to next state. */
        if (processSegment == TRUE)
        {
          ActiveJob->State = VSWUPDM_JOB_STATE_PROCESS_INIT_INTERNAL_ENTRY_NODES;
        }
        else
          /* #7400 Otherwise get next segment. */
        {
          ActiveJob->State = VSWUPDM_JOB_STATE_PROCESS_INIT_INTERNAL_NEXT_SEGMENT;
        }

        retVal = VSWUPDM_JOB_STATUS_ACTIVE;
        break;
      }
      case VSWUPDM_JOB_STATE_PROCESS_INIT_INTERNAL_NEXT_SEGMENT:
      /* #8000 If state is INIT_INTERNAL_NEXT_SEGMENT: */
      {
        /* #8100 If this was not the last segment: */
        vSwUpdM_EndAddressOfVarSegmentsType endAddress = vSwUpdM_GetVarSegments(ActiveJob->EntityIds.SegmentId.DynamicSegmentId).ReservedEndAddressOfVarSegments;

        if (endAddress < VSWUPDM_MAX_ADDRESS)
        {
          /* #8110 Get next segment. */
          ActiveJob->Result = vSwUpdM_Segment_SearchSegment(&ActiveJob->EntityIds.SegmentId.DynamicSegmentId, endAddress + 1u);
          ActiveJob->State = VSWUPDM_JOB_STATE_PROCESS_INIT_INTERNAL_SELECT_SEGMENT;
        }
        else
        {
          if (vSwUpdM_Pipe_IsSubScopeAttributeSet(subScopeAttributes, VSWUPDM_SUB_SCOPE_ATTRIBUTE_FLUSH_SEGMENT) == TRUE)
          {
            ActiveJob->State = VSWUPDM_JOB_STATE_PROCESS_POST_ACTION;
          }
          else
          {
            /* #8120 Otherwise: Continue with next state.
             *   No remaining data to process, cause flush. */
            ActiveJob->State = VSWUPDM_JOB_STATE_PROCESS_FLUSH;
          }
        }

        break;
      }
      case VSWUPDM_JOB_STATE_PROCESS_INIT_INTERNAL_ENTRY_NODES:
      /* #9000 If state is INIT_INTERNAL_ENTRY_NODES: */
      {
        /* #9100 Evaluate (sub-)scope. */
        streamResult = E_OK;

        /* #9199 If sub scope attribute SEGMENTS is set. */
        if (vSwUpdM_Pipe_IsSubScopeAttributeSet(subScopeAttributes, VSWUPDM_SUB_SCOPE_ATTRIBUTE_SEGMENTS) == TRUE)
        {
          /* PRQA S 3679 1 */ /* MD_vSwUpdM_Rule8.13_3679_PointerToModifiableData */
          vSwUpdM_VarSegmentsPtrType segment = vSwUpdM_GetAddrVarSegments(ActiveJob->EntityIds.SegmentId.DynamicSegmentId);

          /* #9200 If sub scope attribute FLUSH SEGMENT is set. */
          if ( (vSwUpdM_Pipe_IsSubScopeAttributeSet(subScopeAttributes, VSWUPDM_SUB_SCOPE_ATTRIBUTE_FLUSH_SEGMENT) == TRUE)
            && (vSwUpdM_ProcessData.PipeState == VSWUPDM_PIPE_STATE_IDLE) )
          {
            /* #9210 Initialize configured process. */
            streamResult = vStreamProc_InitPipe(vSwUpdM_ProcessData.PipeId);

            if (streamResult == E_OK)
            {
              /* #9220 Open configured pipe. */
              streamResult = vStreamProc_Open(vSwUpdM_ProcessData.PipeId);
            }

            if (streamResult == E_OK)
            {
              /* #9230 Set internal mode. */
              streamResult = vStreamProc_SetMode(vSwUpdM_ProcessData.PipeId, vSwUpdM_ProcessData.Operation);
            }

            if (streamResult == E_OK)
            {
              /* #9240 Set user mode. */
              streamResult = vStreamProc_SetMode(vSwUpdM_ProcessData.PipeId, vSwUpdM_ProcessUserData.Operation);
            }
          }

          /* #9300 If sub scope attribute PROVIDE_RANGE is set: */
          if ( (vSwUpdM_Pipe_IsSubScopeAttributeSet(subScopeAttributes, VSWUPDM_SUB_SCOPE_ATTRIBUTE_PROVIDE_RANGE) == TRUE)
            && (streamResult == E_OK) )
          {
            /* #9310 Set start and end of range as default. */
            vSwUpdM_AddressType startAddress = segment->DynamicAttributesOfVarSegment.StartAddress;
            vSwUpdM_AddressType endAddress = segment->EndAddressOfVarSegments;

            /* #9320 If sub scope attribute RESERVED AREA is set:
              *   Use reserved start and reserved end of segment. */
            if (vSwUpdM_Pipe_IsSubScopeAttributeSet(subScopeAttributes, VSWUPDM_SUB_SCOPE_ATTRIBUTE_RESERVED_AREA) == TRUE)
            {
              /* PRQA S 3679 1 */ /* MD_vSwUpdM_Rule8.13_3679_PointerToModifiableData */
              vSwUpdM_VarRegionsPtrType region = vSwUpdM_GetAddrVarRegions(segment->RegionIdxOfVarSegments);

              if (segment->ReservedStartAddressOfVarSegments > region->StartAddressOfVarRegions)
              {
                startAddress = segment->ReservedStartAddressOfVarSegments;
              }
              else
              {
                startAddress = region->StartAddressOfVarRegions;
              }

              if (segment->ReservedEndAddressOfVarSegments < region->EndAddressOfVarRegions)
              {
                endAddress = segment->ReservedEndAddressOfVarSegments;
              }
              else
              {
                endAddress = region->EndAddressOfVarRegions;
              }
            }

            /* #9330 If sub scope attribute PARTIAL SEGMENT is set:
              *   Use WriteAddress of segment if it is partially written. */
            if (vSwUpdM_Pipe_IsSubScopeAttributeSet(subScopeAttributes, VSWUPDM_SUB_SCOPE_ATTRIBUTE_PARTIAL_SEGMENT) == TRUE)
            {
              if (segment->WriteAddressOfVarSegments > startAddress)
              {
                startAddress = segment->WriteAddressOfVarSegments;
              }
            }

            /* #9340 Pass range to pipe. */
            streamResult = vSwUpdM_Pipe_WriteRangeInfo(vSwUpdM_ProcessData.ProcessId, vSwUpdMConf_vSwUpdMDataInputType_InputRange, startAddress, (endAddress - startAddress) + 1u);
          }

          /* #9400 If sub scope attribute OPEN_SEGMENT is set: */
          if (streamResult == E_OK)
          {
            if ((vSwUpdM_Pipe_HasInternalEntryPoint(vSwUpdM_ProcessData.ProcessId, vSwUpdMConf_vSwUpdMDataInputType_InputOperation) == FALSE) || (vSwUpdM_ProcessData.PipeStarted == TRUE))
            {
              vSwUpdM_HandleSubscopeOpenSegment(subScopeAttributes, ActiveJob);
            }
          }
        }

        if (streamResult == E_OK)
        {

          /* #9450 Startup pipe processing. */
          vSwUpdM_ProcessData.PipeState = VSWUPDM_PIPE_STATE_PROCESSING;

          switch (vSwUpdM_ProcessData.ProcOperation)
          {
            case VSWUPDM_PROC_NODE_OPERATION_START:
            case VSWUPDM_PROC_NODE_OPERATION_CLEAN_RESTART:
            case VSWUPDM_PROC_NODE_OPERATION_DIRTY_RESTART:
            {
              /* #9460 If pipe has input for operation mode: */
              if (vSwUpdM_Pipe_HasInternalEntryPoint(vSwUpdM_ProcessData.ProcessId, vSwUpdMConf_vSwUpdMDataInputType_InputOperation) == TRUE)
              {
                /* #9461 Provide initial value of operation to StreamProc. */
                streamResult = vSwUpdM_Pipe_WriteProcessOperation(vSwUpdM_ProcessData.ProcessId, vSwUpdMConf_vSwUpdMDataInputType_InputOperation, vSwUpdM_ProcessData.ProcOperation);

                vSwUpdM_ProcessData.PipeStarted = TRUE;
              }

              break;
            }
            default:
            {
              /* Nothing to do. */
              break;
            }
          }
        }

        /* Entity IDs were always provided to an entry point ----------------------------------------------------------------------------- */
        /* #9500 Pass current entity IDs to pipe in every loop cycle. */
        if (streamResult == E_OK)
        {
          streamResult = vSwUpdM_Pipe_WriteEntityIds(vSwUpdM_ProcessData.ProcessId, vSwUpdMConf_vSwUpdMDataInputType_InputEntities, &ActiveJob->EntityIds);
        }

        /* #9600 If sub scope attribute SOURCE ENTITIES is set. */
        if ( (vSwUpdM_Pipe_IsSubScopeAttributeSet(subScopeAttributes, VSWUPDM_SUB_SCOPE_ATTRIBUTE_SOURCE_ENTITES) == TRUE)
          && (streamResult == E_OK) )
        {
          vSwUpdM_EntityIdsType sourceIds;

          sourceIds = ActiveJob->EntityIds;

          /* #9610 Use active partition as source. */
          sourceIds.PartitionState = VSWUPDM_PART_STATE_ACTIVE;
          streamResult = vSwUpdM_Part_GetIdByState(&sourceIds.PartitionId, VSWUPDM_PART_STATE_ACTIVE);

          if (streamResult == E_OK)
          {
            /* #9620 Pass source entities to pipe. */
            streamResult = vSwUpdM_Pipe_WriteEntityIds(vSwUpdM_ProcessData.ProcessId, vSwUpdMConf_vSwUpdMDataInputType_InputEntitiesSource, &sourceIds);
          }
        }

        /* #9700 Report error or continue with next loop. */
        if (streamResult == E_OK)
        {
          /* #9710 If pipe doesn't use operation mode
           *   Forward to pending module state (if any is configured). */
          if (vSwUpdM_ProcessData.PipeStarted == FALSE)
          {
            vSwUpdM_ModuleStateType pendingModuleState = vSwUpdM_ProcessData.ProcessConfig->StateForward.Pending.ModuleState;

            if (pendingModuleState != VSWUPDM_MODULE_STATE_UNDEFINED)
            {
              ActiveJob->Result = vSwUpdM_Module_UpdateAndPersistState(ActiveJob->EntityIds.PartitionId, ActiveJob->EntityIds.PartitionState, ActiveJob->EntityIds.ModuleId, pendingModuleState, ActiveJob, ActiveJob->Source);
            }
          }

          ActiveJob->State = VSWUPDM_JOB_STATE_PROCESS_PROCESS_PIPE;
        }
        else
        {
          ActiveJob->Result = streamResult;
        }

        break;
      }
      case VSWUPDM_JOB_STATE_PROCESS_PROCESS_PIPE:  /**< process pipe until idle */
      /* #10000 If processing of pipe was requested. */
      {
        /* #10100 Update and evaluate pipe state. */
        vStreamProc_ReturnType result = vStreamProc_Process(vSwUpdM_ProcessData.PipeId);

        /* #10200 If pipe has output for operation mode: */
        if (vSwUpdM_ProcessData.PipeStarted == TRUE)
        {
          if ((result == VSTREAMPROC_OK) || (result == VSTREAMPROC_PENDING))
          {
            vSwUpdM_ProcNodeOperationType procOperation;

            /* #10210 Get response for operation mode (if available). */
            if (vSwUpdM_Pipe_ReadProcessOperation(vSwUpdM_ProcessData.ProcessId, vSwUpdMConf_vSwUpdMDataOutputType_OutputOperation, &procOperation) == E_OK)
            {
              /* #10220 If response matches START,
               *   Switch to PROCESS */
              if (procOperation == VSWUPDM_PROC_NODE_OPERATION_START)
              {
                vSwUpdM_ProcessData.ProcOperation = VSWUPDM_PROC_NODE_OPERATION_PROCESS;
                vSwUpdM_ProcessData.PipeStarted   = FALSE;

                ActiveJob->Result = vSwUpdM_Pipe_WriteProcessOperation(vSwUpdM_ProcessData.ProcessId, vSwUpdMConf_vSwUpdMDataInputType_InputOperation, vSwUpdM_ProcessData.ProcOperation);
                ActiveJob->State  = VSWUPDM_JOB_STATE_PROCESS_PROCESS_PIPE;

                /* #10230 Forward to pending module state (if any is configured). */
                if (ActiveJob->Result == E_OK)
                {
                  /* HINT: For pipes without operation mode, the pending module state is set after internal entry notes are handled. */
                  vSwUpdM_ModuleStateType pendingModuleState = vSwUpdM_ProcessData.ProcessConfig->StateForward.Pending.ModuleState;

                  vSwUpdM_HandleSubscopeOpenSegment(subScopeAttributes, ActiveJob);

                  if (pendingModuleState != VSWUPDM_MODULE_STATE_UNDEFINED)
                  {
                    ActiveJob->Result = vSwUpdM_Module_UpdateAndPersistState(ActiveJob->EntityIds.PartitionId, ActiveJob->EntityIds.PartitionState, ActiveJob->EntityIds.ModuleId, pendingModuleState, ActiveJob, ActiveJob->Source);
                  }
                }
              }
            }
          }
        }

        /* #10300 Evaluate processing result. */
        switch (result)
        {
          case VSTREAMPROC_OK:
          /* #10310 If processing has come to an end: Continue with next state. */
          {
            /* This result indicate that the processing has come to end. Let the internal state decides whether the next
               set of data can be provided or if we have to flush */

            /* #10311 Close segment (if it was opened before). */
            if (vSwUpdM_Pipe_IsSubScopeAttributeSet(subScopeAttributes, VSWUPDM_SUB_SCOPE_ATTRIBUTE_OPEN_SEGMENT) == TRUE)
            {
              (void)vSwUpdM_Segment_CloseSegment(ActiveJob->EntityIds.SegmentId, VSWUPDM_SID_NONE, ActiveJob, ActiveJob->Source);
            }

            /* #10312 Call flush to finalize overall processing. */
            ActiveJob->State = VSWUPDM_JOB_STATE_PROCESS_FLUSH;

            /* #10313 If segments are handled, but individual segments aren't flushed
             *   Request next segment instead. */
            if (vSwUpdM_Pipe_IsSubScopeAttributeSet(subScopeAttributes, VSWUPDM_SUB_SCOPE_ATTRIBUTE_SEGMENTS) == TRUE)
            {
              if (vSwUpdM_Pipe_IsSubScopeAttributeSet(subScopeAttributes, VSWUPDM_SUB_SCOPE_ATTRIBUTE_FLUSH_SEGMENT) == FALSE)
              {
                ActiveJob->State = VSWUPDM_JOB_STATE_PROCESS_INIT_INTERNAL_NEXT_SEGMENT;
              }
            }

            break;
          }
          /* #10320 If processing is still ongoing: Just wait for final result. */
          case VSTREAMPROC_PENDING:
          {
            break;
          }
          /* #10330 Otherwise: Reset pipe state and report error. */
          case VSTREAMPROC_INSUFFICIENT_INPUT:   /* Configuration issue shall never happen. */
          case VSTREAMPROC_INSUFFICIENT_OUTPUT:  /* Configuration issue shall never happen. */
          case VSTREAMPROC_FAILED:
          default:
          {
            vSwUpdM_ProcessData.PipeState   = VSWUPDM_PIPE_STATE_IDLE;
            vSwUpdM_ProcessData.PipeStarted = FALSE;

            ActiveJob->State = VSWUPDM_JOB_STATE_PROCESS_COLLECT_INTERNAL_RESULTS;
            break;
          }
        }

        break;
      }
      case VSWUPDM_JOB_STATE_PROCESS_FLUSH:
      /* #11000 If flush was requested: */
      {
        vStreamProc_ReturnType result;

        vSwUpdM_ProcessData.PipeState = VSWUPDM_PIPE_STATE_FLUSHING;

        /* #11100 Execute flush and evaluate response. */
        result = vStreamProc_Flush(vSwUpdM_ProcessData.PipeId);
        switch (result)
        {
          case VSTREAMPROC_OK:
          /* #11200 If flush ended successfully: Continue with next state. */
          {
            vSwUpdM_ProcessData.PipeState   = VSWUPDM_PIPE_STATE_IDLE;
            vSwUpdM_ProcessData.PipeStarted = FALSE;

            /* Pipe flush finished - switch to next state */
#if (VSWUPDM_MULTICONTROLLER_SUPPORT == STD_ON)
            if (ActiveJob->Source != (vSwUpdM_NodeIterType)vSwUpdM_GetLocalNode())
            {
# if (VSWUPDM_EXTDATAOUTPUT == STD_ON)
              ActiveJob->State = VSWUPDM_JOB_STATE_PROCESS_PROVIDE_EXTERNAL_RESULTS_REMOTE;
# else
              ActiveJob->State = VSWUPDM_JOB_STATE_PROCESS_COLLECT_INTERNAL_RESULTS;
# endif
            }
            else
#endif
            {
              ActiveJob->State = VSWUPDM_JOB_STATE_PROCESS_COLLECT_EXTERNAL_RESULTS;
            }

            /* Reset counter for next step */
            ActiveJob->Count = 0;

            break;
          }
          case VSTREAMPROC_PENDING:
          /* #11300 If processing is still ongoing: Just wait for final result. */
          {
            break;
          }
          /* #11400 Otherwise: Reset pipe state and report error. */
          case VSTREAMPROC_FAILED:
          case VSTREAMPROC_INSUFFICIENT_INPUT:
          case VSTREAMPROC_INSUFFICIENT_OUTPUT:
          default:
          {
            vSwUpdM_ProcessData.PipeState   = VSWUPDM_PIPE_STATE_IDLE;
            vSwUpdM_ProcessData.PipeStarted = FALSE;

            ActiveJob->Result = VSWUPDM_E_STREAM_OPERATION_FAILED;

            break;
          }
        }
        break;
      }
      case VSWUPDM_JOB_STATE_PROCESS_PROVIDE_EXTERNAL_RESULTS_REMOTE:
      /* #12000 If state is REMOTE PROVIDE EXTERNAL RESULTS: */
      case VSWUPDM_JOB_STATE_PROCESS_PROVIDE_EXTERNAL_RESULTS_REMOTE_WAIT:
      /* #13000 If state is REMOTE PROVIDE EXTERNAL RESULTS WAIT:
       *   Transmission of external output data is done.
       */
      {
        /* #13100 Handle remote inputs in sub-job handler. */
        retVal = vSwUpdM_SubJobHandler_ProcessEntityRemoteOutput(ActiveState, ActiveJob, ProcessingLength);

        break;
      }
      case VSWUPDM_JOB_STATE_PROCESS_COLLECT_EXTERNAL_RESULTS_FAIL:
      /* #14000 If state is COLLECT EXTERNAL RESULTS FAIL: */
      case VSWUPDM_JOB_STATE_PROCESS_COLLECT_EXTERNAL_RESULTS:
      /* #15000 If state is COLLECT EXTERNAL RESULTS: */
      {
#if (VSWUPDM_EXTDATAOUTPUT == STD_ON)
        /* #15100 For each external output do: */
        if (ActiveJob->Count < vSwUpdM_ProcessUserData.OutputCount)
        /* #15110 Get reference on output data. */
        {
          vStreamProc_ExitPointInfoType exitPoint;
          vSwUpdM_VarDataPointerType    dataPtr;
          vSwUpdM_DataReadStreamPtrType data = NULL_PTR; /* PRQA S 2981 */ /* MD_vSwUpdM_Rule2.2_2981_2892_RedundantInitialization */

          dataPtr = vSwUpdM_ProcessUserData.OutputData[ActiveJob->Count].DataPtr;

          /* #15120 Read data from pipe. */
          if (vSwUpdM_ProcessUserData.OutputData[ActiveJob->Count].BufferSize > 0u)
          {
             /* #15130 Read data from pipe. */
            if (vSwUpdM_Pipe_RequestExitPoint(
              vSwUpdM_ProcessData.PipeId,
              vSwUpdM_GetExitPointIdOfExtDataOutput(vSwUpdM_GetExtDataOutputStartIdxOfDataProcesses(vSwUpdM_ProcessData.ProcessId) + ActiveJob->Count),
              vStreamProcConf_vStreamProcDataType_Undefined,
              1u,
              &exitPoint) == E_OK)
            {
              data = vSwUpdM_Pipe_GetLiteralReadBuffer(&exitPoint);
              if (data == NULL_PTR)
              {
                /* Unsupported datatype. Error will be propagated later. */
                ActiveJob->State = VSWUPDM_JOB_STATE_PROCESS_COLLECT_EXTERNAL_RESULTS_FAIL;
                exitPoint.ReadRequest.StorageInfo.RequestLength = 0u;
              }
              else
              {
                /* #15130 Copy content to user provided buffer. */
                vSwUpdM_LengthType length;

                /* #15131 The smaller buffer determines the length to copy. */
                length = VSWUPDM_EXECCTRL_MIN(exitPoint.ReadRequest.StorageInfo.AvailableLength, vSwUpdM_ProcessUserData.OutputData[ActiveJob->Count].BufferSize);

                if (length < exitPoint.ReadRequest.StorageInfo.AvailableLength)
                {
                  /* Error will be propagated later. */
                  ActiveJob->State = VSWUPDM_JOB_STATE_PROCESS_COLLECT_EXTERNAL_RESULTS_FAIL;
                }

                /* #15132 Do the actual copy. */
                vSwUpdM_Buffer_Copy(data, dataPtr, length);

                /* #15133 Return number of copied bytes. */
                vSwUpdM_ProcessUserData.OutputData[ActiveJob->Count].AvailableLength = length;
              }

              /* #15140 Release buffer. */
              if (vStreamProc_AcknowledgeExitPoint(vSwUpdM_ProcessData.PipeId, exitPoint.ReadRequest.StorageInfo.AvailableLength, TRUE, &exitPoint) != VSTREAMPROC_OK)
              {
                /* Error will be propagated later. */
                ActiveJob->State = VSWUPDM_JOB_STATE_PROCESS_COLLECT_EXTERNAL_RESULTS_FAIL;
              }
            }
          }

          /* #15150 Go to next ExitPoint. */
          ActiveJob->Count++;
        }
        else
#endif
        {
#if (VSWUPDM_EXTDATAOUTPUT == STD_ON)
          if (ActiveJob->State == VSWUPDM_JOB_STATE_PROCESS_COLLECT_EXTERNAL_RESULTS_FAIL)
          {
            /* #15200 Propagate error now, if one was logged before. */
            ActiveJob->Result = E_NOT_OK;
          }
          else
#endif
          {
            /* #15300 If no more external outputs left: switch to next state. */
            ActiveJob->State = VSWUPDM_JOB_STATE_PROCESS_COLLECT_INTERNAL_RESULTS;
            retVal = VSWUPDM_JOB_STATUS_ACTIVE; /* Just call this handler again in same MainFunction cycle to start initialization of first node */
          }
        }

        break;
      }
      case VSWUPDM_JOB_STATE_PROCESS_COLLECT_INTERNAL_RESULTS:
      /* #16000 If internal results shall be collected: */
      {
        /* #16100 Read result of processing pipe and switch to next state. */
        ActiveJob->Result = vSwUpdM_Pipe_ReadResult(vSwUpdM_ProcessData.ProcessId, vSwUpdMConf_vSwUpdMDataOutputType_OutputResult);

        if (vSwUpdM_Pipe_IsSubScopeAttributeSet(subScopeAttributes, VSWUPDM_SUB_SCOPE_ATTRIBUTE_FLUSH_SEGMENT) == TRUE)
        {
          vSwUpdM_ProcessData.ProcOperation = VSWUPDM_PROC_NODE_OPERATION_START;
          ActiveJob->State = VSWUPDM_JOB_STATE_PROCESS_INIT_INTERNAL_NEXT_SEGMENT;
        }
        else
        {
          ActiveJob->State = VSWUPDM_JOB_STATE_PROCESS_POST_ACTION;
        }

        break;
      }
      case VSWUPDM_JOB_STATE_PROCESS_POST_ACTION:
      /* #17000 If post action are requested: */
      {
        /* #17100 Forward to final module state (if any is configured). */
        vSwUpdM_ModuleStateType finalModuleState = vSwUpdM_ProcessData.ProcessConfig->StateForward.Final.ModuleState;

        if (finalModuleState != VSWUPDM_MODULE_STATE_UNDEFINED)
        {
          ActiveJob->Result = vSwUpdM_Module_UpdateAndPersistState(ActiveJob->EntityIds.PartitionId, ActiveJob->EntityIds.PartitionState, ActiveJob->EntityIds.ModuleId, finalModuleState, ActiveJob, ActiveJob->Source);
        }

        /* #17200 If resume info shall be updated by job
          *   Update resume information: Persist state "finished". */
        if ( (ActiveJob->Result == E_OK)
          && (ActiveJob->UpdateResumeInfo == TRUE)
          && (vSwUpdM_ProcessData.ProcessConfig->StateForward.Final.UpdateResumeInfo == TRUE) )
        {
          (void)vSwUpdM_ResumeInfo_UpdateAndPersistState(VSWUPDM_PART_STATE_UNDEFINED, VSWUPDM_SID_NONE, VSWUPDM_RESUME_STATE_FINISHED, vSwUpdM_ResumeInfo.ResumeInfo.MemoryAddress, vSwUpdM_ResumeInfo.ResumeInfo.StreamAddress, vSwUpdM_ResumeInfo.TriggerAddress, vSwUpdM_ResumeInfo.ResumeInfo.IsAddressValid, ActiveJob->Source);
        }

        /* #17300 If modules was opened implicitly by finalize request (indicated by job operation), close module. */
        if (ActiveJob->Operation == VSWUPDM_JOB_OPERATION_CLOSE_MODULE)
        {
          (void)vSwUpdM_Module_CloseModule(ActiveJob->EntityIds.ModuleId, VSWUPDM_SID_NONE, ActiveJob->Source, ActiveJob);

          /* Reset job operation to default value. */
          ActiveJob->Operation = VSWUPDM_JOB_OPERATION_DEFAULT;
        }

        /* #17400 Switch to final state. */
        ActiveJob->State = VSWUPDM_JOB_STATE_FINAL;
        break;
      }
      case VSWUPDM_JOB_STATE_EVAL_HOOK:
      /* #18000 If hook was called: */
      {
        /* #18100 Handle hook return value. */
        retVal = vSwUpdM_Job_HandleDefaultRetry(ActiveJob);

        break;
      }
      case VSWUPDM_JOB_STATE_FINAL:
      case VSWUPDM_JOB_STATE_FAILED:
      /* #19000 If job state is "failed", because of negative child result or if job is passed successfully: */
      {
        cleanup = TRUE;
        break;
      }
      default:
      /* #20000 Otherwise: Invalid state. */
      {
        ActiveJob->Result = VSWUPDM_E_INV_STATE;
        break;
      }
    }

    /* #30000 on error or cleanup: */
    if ((ActiveJob->Result != E_OK) || (cleanup == TRUE))
    {
      /* #30100 Close pipe. */
      (void)vStreamProc_Close(vSwUpdM_ProcessData.PipeId);

      /* #30200 Clear ProcessId. */
      vSwUpdM_ProcessData.ProcessId = 0xFFu;
      vSwUpdM_ProcessData.PipeId = 0xFFu;

      /* #30300 Indicate that job is finished. */
      retVal = VSWUPDM_JOB_STATUS_FINISHED;
    }
  }

  return retVal;
  /* PRQA S 6010, 6030, 6050, 6080 1 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */
} /* vSwUpdM_JobHandler_ProcessEntity */

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_RemoteProcessInfo
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
 */
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_RemoteProcessInfo) /* PRQA S 3673 */ /* MD_vSwUpdM_Rule8.13_3673_PointerToConstParameter */
{
  vSwUpdM_JobStatusType retVal;
#if (VSWUPDM_MULTICONTROLLER_SUPPORT == STD_ON)
  vSwUpdM_RemoteStreamHandleType handle;
  Std_ReturnType                 result;
#endif

  VSWUPDM_DUMMY_STATEMENTS_JOB_HANDLER(); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#if (VSWUPDM_MULTICONTROLLER_SUPPORT == STD_ON)

  /* #10 Evaluate child result from previous cycle.
   *   If not okay, apply child result.
   *   If result is SUSPENDED suspend job. */
  retVal = vSwUpdM_Job_EvaluateChildResultOrSuspend(ActiveState, ActiveJob, FALSE);

  /* #20 Check input parameter. */
  handle = (vSwUpdM_RemoteStreamHandleType) ActiveJob->Count;

  if ((vSwUpdM_ProcessCountType)handle >= vSwUpdM_ProcessUserData.InputCount)
  {
    ActiveJob->State = VSWUPDM_JOB_STATE_FAILED;
    ActiveJob->Result = VSWUPDM_E_INV_RANGE;
  }

  if (retVal != VSWUPDM_JOB_STATUS_SUSPENDED)
  {
    /* #30 Evaluate job state. */
    switch (ActiveJob->State)
    {
      case VSWUPDM_JOB_STATE_INITIAL:
      /* #100 If state is INITIAL: */
      {
        /* #110 Set up RemoteStream transfer (TX) and send StreamStart frame. */
        /* PRQA S 0311 1 */ /* MD_vSwUpdM_Rule11.5_0311_RemoteBufferConstConfigValues */
        result = vSwUpdM_RemoteStreamStartTx(handle, (P2VAR(uint8, AUTOMATIC, VSWUPDM_APPL_VAR)) vSwUpdM_ProcessUserData.InputData[ActiveJob->Count].DataPtr, vSwUpdM_ProcessUserData.InputData[ActiveJob->Count].Length, ActiveJob->RemoteTarget);

        switch (result)
        {
          case E_OK:
          {
            /* #120 On success set job state to PENDING. */
            ActiveJob->State = VSWUPDM_JOB_STATE_PENDING;
            break;
          }
          case E_NOT_OK:
          {
            /* #130 StreamStart Transmission failed - try again next time. */
            break;
          }
          case VSWUPDM_E_INVALID_STREAM_STATE:
          case VSWUPDM_E_OUT_OF_RANGE:
          default:
          {
            ActiveJob->Result = result;
            break;
          }
        }
        break;
      }
      case VSWUPDM_JOB_STATE_PENDING:
      /* #200 If state is PENDING: */
      {
        /* #210 Wait until StreamState is FAIL or IDLE. */
        if (vSwUpdM_RemoteStream_List[handle].State == VSWUPDM_REMOTESTREAMSTATE_FAIL)
        {
          ActiveJob->Result = E_NOT_OK;
          vSwUpdM_RemoteStream_List[handle].State = VSWUPDM_REMOTESTREAMSTATE_IDLE;
        }
        if (vSwUpdM_RemoteStream_List[handle].State == VSWUPDM_REMOTESTREAMSTATE_IDLE)
        {
          retVal = VSWUPDM_JOB_STATUS_FINISHED;
        }
        break;
      }
      case VSWUPDM_JOB_STATE_FAILED:
      /* #300 In failed state: Report error. */
      {
        break;
      }
      /* #400 Otherwise: Invalid state.
       *   Set error in job result. */
      default:
      {
        ActiveJob->Result = VSWUPDM_E_INV_STATE;
        break;
      }
    }
  }
#else
  retVal = VSWUPDM_JOB_STATUS_FINISHED;
#endif

  return retVal;
  /* PRQA S 6030, 6080 1 */ /* MD_MSR_STCYC, MD_MSR_STMIF */
} /* vSwUpdM_JobHandler_RemoteProcessInfo */

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_RemoteStreamScheduler
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
 */
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_RemoteStreamScheduler) /* PRQA S 3673 */ /* MD_vSwUpdM_Rule8.13_3673_PointerToConstParameter */
{
  vSwUpdM_JobStatusType           retVal = VSWUPDM_JOB_STATUS_FINISHED; /* PRQA S 2981 */ /* MD_MSR_RetVal */
#if (VSWUPDM_MULTICONTROLLER_SUPPORT == STD_ON)
  Std_ReturnType                  result;
  vSwUpdM_RemoteStreamHandleType  handle;
  boolean                         exitLoop;
#endif

  VSWUPDM_DUMMY_STATEMENTS_JOB_HANDLER(); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

#if (VSWUPDM_MULTICONTROLLER_SUPPORT == STD_ON)
  /* #10 Loop over all (parallel) remote streams. */
  for (handle = 0u; handle < (vSwUpdM_RemoteStreamHandleType)VSWUPDM_REMOTESTREAMHANDLE_SIZE; handle++)
  {
    /* #20 call StreamScheduler function. */
    result = vSwUpdM_RemoteStreamSchedule(handle);

    /* Performance optimization: Only one stream can be active at a time.
      * For all but one case below, no further streams need to be processed. */
    exitLoop = TRUE;

    switch (result)
    {
      case E_OK:
      /* #30 If no further scheduling needed, finish this job. */
      {
        /* Nothing to do for this stream. */
        exitLoop = FALSE;
        break;
      }
      case VSWUPDM_E_BUSY:
      /* #40 If further scheduling needed repeat call next time. */
      {
        /* At least this stream needs further processing: */
        retVal = VSWUPDM_JOB_STATUS_PENDING;
        break;
      }
      case VSWUPDM_E_REMOTE_STREAM_FAILED:
      /* #50 On fail, return error. */
      {
        ActiveJob->Result = VSWUPDM_E_REMOTE_STREAM_FAILED;
        break;
      }
      default:
      {
        ActiveJob->Result = VSWUPDM_E_INV_STATE;
        break;
      }
    }

    if (exitLoop == TRUE)
    {
      break;
    }
  }
#endif

  return retVal;
} /* vSwUpdM_JobHandler_RemoteStreamScheduler */

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_RemoteStreamCleanup
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 */
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_RemoteStreamCleanup) /* PRQA S 3673 */ /* MD_vSwUpdM_Rule8.13_3673_PointerToConstParameter */
{
  vSwUpdM_JobStatusType retVal;
#if (VSWUPDM_MULTICONTROLLER_SUPPORT == STD_ON)
  vSwUpdM_RemoteStreamHandleType handle;
  vSwUpdM_ProcessCountType outputIndex;
#endif

  VSWUPDM_DUMMY_STATEMENTS_JOB_HANDLER(); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

#if (VSWUPDM_MULTICONTROLLER_SUPPORT == STD_ON)
  /* #10 Check if this is handling a remote module. */
  if (!vSwUpdM_IsWithLocalNodeOfNodeGroup(vSwUpdM_GetNodeGroupOwnersIdxOfModule(ActiveJob->EntityIds.ModuleId)))
  {
    ActiveJob->State = VSWUPDM_JOB_STATE_PENDING;

    /* #20 Wait for result in output buffers. In case of an error, abort. */
    for (outputIndex = 0u; outputIndex < vSwUpdM_ProcessUserData.OutputCount; outputIndex++)
    {
      handle = (vSwUpdM_RemoteStreamHandleType)(outputIndex + vSwUpdM_ProcessUserData.InputCount);
      if (vSwUpdM_RemoteStream_List[handle].State == VSWUPDM_REMOTESTREAMSTATE_FAIL)
      {
        ActiveJob->Result = VSWUPDM_E_STREAM_OPERATION_FAILED;
        vSwUpdM_RemoteStream_List[handle].State = VSWUPDM_REMOTESTREAMSTATE_IDLE;
      }
      if (vSwUpdM_RemoteStream_List[handle].State == VSWUPDM_REMOTESTREAMSTATE_DONE)
      {
        vSwUpdM_RemoteStream_List[handle].State = VSWUPDM_REMOTESTREAMSTATE_IDLE;
        vSwUpdM_ProcessUserData.OutputData[outputIndex].AvailableLength = vSwUpdM_RemoteStream_List[handle].AvailableLength;
      }
    }

    /* #30 If all RemoteStreams are IDLE, this job is finished. */
    retVal = VSWUPDM_JOB_STATUS_FINISHED;
    for (outputIndex = 0u; outputIndex < vSwUpdM_ProcessUserData.OutputCount; outputIndex++)
    {
      handle = (vSwUpdM_RemoteStreamHandleType)(outputIndex + vSwUpdM_ProcessUserData.InputCount);
      if (vSwUpdM_RemoteStream_List[handle].State != VSWUPDM_REMOTESTREAMSTATE_IDLE)
      {
        retVal = VSWUPDM_JOB_STATUS_PENDING;
        break;
      }
    }
  }
  else
#endif
  {
    retVal = VSWUPDM_JOB_STATUS_FINISHED;
  }

  return retVal;
} /* vSwUpdM_JobHandler_RemoteStreamCleanup */

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_FinalizeSegment
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
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_FinalizeSegment)
{
  vSwUpdM_JobStatusType       retVal = VSWUPDM_JOB_STATUS_PENDING;
  vSwUpdM_VarSegmentsPtrType  segment;
  Std_ReturnType              streamResult;

  VSWUPDM_DUMMY_STATEMENTS_JOB_HANDLER(); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  /* #10 Evaluate child result from previous cycle. */
  (void)vSwUpdM_Job_EvaluateAndApplyChildResult(ActiveJob, TRUE);

  segment = vSwUpdM_GetAddrVarSegments(ActiveJob->EntityIds.SegmentId.DynamicSegmentId);

  /* #20 Evaluate job state. */
  switch (ActiveJob->State)
  {
    case VSWUPDM_JOB_STATE_INITIAL:
    /* #100 If initial conditions for first actual phase shall be established */
    {
      /* #110 If segment is closed
       *   Trigger opening of requested segment.
       *   Use job operation to remember that segment was opened implicitly. */
      if (vSwUpdM_EntityData.OpenIds.SegmentId.DynamicSegmentId == VSWUPDM_INVALID_ID)
      {
        ActiveJob->Result = vSwUpdM_Segment_OpenSegment(ActiveJob->EntityIds.SegmentId, VSWUPDM_SID_NONE, ActiveJob, ActiveJob->Source);

        ActiveJob->Operation = VSWUPDM_JOB_OPERATION_CLOSE_SEGMENT;
      }
      else
      {
        retVal = VSWUPDM_JOB_STATUS_ACTIVE;
      }

      /* #120 If previously processed segment doesn't match the requested one
       *   or no segment was processed before. */
      if (vSwUpdM_StreamData.SegmentId != ActiveJob->EntityIds.SegmentId.DynamicSegmentId)
      {
        ActiveJob->TargetAddress = segment->WriteAddressOfVarSegments;
        ActiveJob->PendingLength = 0u;

        /* #121 Advance job state to conclude operation next. */
        ActiveJob->State = VSWUPDM_JOB_STATE_FINALIZE_SEGMENT_CONCLUDE;
      }
      /* #122 Otherwise: */
      else
      {
        /* #123 Advance job state to prepare processing of segment next. */
        ActiveJob->State = VSWUPDM_JOB_STATE_FINALIZE_SEGMENT_PREPARE;
      }

      break;
    }
    case VSWUPDM_JOB_STATE_FINALIZE_SEGMENT_PREPARE:
    /* #200 If processing of segment shall be prepared. */
    {
      boolean                                updateEntityStates    = TRUE;
      vSwUpdM_TypeOfIntModeType              internalMode     = vSwUpdMConf_vSwUpdMModeType_Local;
      vSwUpdM_NodeGroupOwnersIdxOfRegionType regionOwnerGroupIndex = vSwUpdM_Segment_GetRegionOwnerGroupIndex(ActiveJob->EntityIds.SegmentId);

# if (VSWUPDM_LOCALINSTANCE_ACTS_AS_MASTER == STD_ON)
      /* #210 Local node is the parent and region is remote,
       *   Set meta-state to "remote". */
      if (vSwUpdM_Grid_LocalNodeIsParent() == TRUE)
      {
        if (   (vSwUpdM_GetNNodesOfNodeGroup(ActiveJob->RemoteTargetGroup) > 1u)
            || (!vSwUpdM_IsWithLocalNodeOfNodeGroup(ActiveJob->RemoteTargetGroup))
           )
        {
          internalMode = vSwUpdMConf_vSwUpdMModeType_Remote;
        }
      }
# endif

      if (!vSwUpdM_IsWithLocalNodeOfNodeGroup(regionOwnerGroupIndex))
      {
        updateEntityStates = FALSE;
      }

      /* #220 If affected segment isn't completely used */
      if (segment->WriteAddressOfVarSegments <= segment->EndAddressOfVarSegments)
      {
        /* #221 Update the states of all entities affected by potential upcoming write operation. */
        if (updateEntityStates == TRUE)
        {
          (void)vSwUpdM_Module_UpdateAndPersistState(ActiveJob->EntityIds.PartitionId, ActiveJob->EntityIds.PartitionState, ActiveJob->EntityIds.ModuleId, VSWUPDM_MODULE_STATE_DIRTY, ActiveJob, ActiveJob->Source);
        }

        vSwUpdM_Job_PrepareWriteOperation(ActiveJob, segment, updateEntityStates);
      }

      ActiveJob->Result = vSwUpdM_Stream_Open(vSwUpdM_EntityData.OpenIds.SegmentId, &vSwUpdM_EntityData.OpenIds, internalMode, vSwUpdM_StreamData.Operation);

      /* #230 Advance job state to finish processing of segment next. */
      ActiveJob->State  = VSWUPDM_JOB_STATE_FINALIZE_SEGMENT_PROCESS;

      break;
    }
    case VSWUPDM_JOB_STATE_FINALIZE_SEGMENT_PROCESS:
    /* #300 If processing of segment shall be finished */
    {
      vSwUpdM_StreamData.PipeState = VSWUPDM_PIPE_STATE_FLUSHING;

      /* #310 Execute flush and evaluate response */
      switch (vStreamProc_Flush(vSwUpdM_StreamData.PipeId))
      {
        case VSTREAMPROC_OK:
        /* #320 If flush ended successfully */
        {
#if (VSWUPDM_MULTICONTROLLER_SUPPORT == STD_ON)
          if (vSwUpdM_IsWithLocalNodeOfNodeGroup(ActiveJob->RemoteTargetGroup))
#endif
          {
            vSwUpdM_RangeInfoType rangeInfo[2u] = { 0u };

            streamResult = vSwUpdM_Pipe_ReadRange(vSwUpdMConf_vSwUpdMDataProcess_StreamData, vSwUpdMConf_vSwUpdMDataOutputType_ResultingRanges, VSWUPDM_ARRAY_SIZE(rangeInfo), rangeInfo);

            /* #340 If operation succeeded and enough data is available */
            if (streamResult == E_OK)
            {
              /* #341 Take range information from exit point. */
              ActiveJob->TargetAddress = rangeInfo[0u].Address;
              ActiveJob->PendingLength = rangeInfo[1u].Address - rangeInfo[0u].Address;

              /* #342 Evaluate result of processing pipe. */
              ActiveJob->Result = vSwUpdM_Pipe_ReadResult(vSwUpdMConf_vSwUpdMDataProcess_StreamData, vSwUpdMConf_vSwUpdMDataOutputType_OutputResult);
            }
            /* #343 Otherwise:
             *   Report failed stream operation */
            else
            {
              ActiveJob->Result = VSWUPDM_E_STREAM_OPERATION_FAILED;
            }
          }

          vSwUpdM_StreamData.PipeState   = VSWUPDM_PIPE_STATE_IDLE;
          vSwUpdM_StreamData.PipeStarted = FALSE;

          /* #350 Advance job state to conclude operation next. */
          ActiveJob->State = VSWUPDM_JOB_STATE_FINALIZE_SEGMENT_CONCLUDE;

          break;
        }
        case VSTREAMPROC_PENDING:
        /* #360 If flush is ongoing
         *   Continue on next cycle. */
        {
          break;
        }
        case VSTREAMPROC_INSUFFICIENT_OUTPUT:
        case VSTREAMPROC_INSUFFICIENT_INPUT:
        /* #370 If flush reports idle operation or insufficient input/output
         *   Evaluate result of processing pipe. */
        {
          ActiveJob->Result = vSwUpdM_Pipe_ReadResult(vSwUpdMConf_vSwUpdMDataProcess_StreamData, vSwUpdMConf_vSwUpdMDataOutputType_OutputResult);

          if (ActiveJob->Result != E_OK)
          {
            ActiveJob->Result = VSWUPDM_E_STREAM_OPERATION_FAILED;
          }

          break;
        }
        case VSTREAMPROC_FAILED:
        default:
        /* #380 Otherwise:
         *   Abort stream operation and advance job state to wait for result. */
        {
          vSwUpdM_Stream_Abort(ActiveJob);
          ActiveJob->State = VSWUPDM_JOB_STATE_FINALIZE_SEGMENT_ABORT;

          break;
        }
      }

      break;
    }
    case VSWUPDM_JOB_STATE_FINALIZE_SEGMENT_CONCLUDE:
    /* #400 If operation shall be concluded */
    {
      retVal = VSWUPDM_JOB_STATUS_ACTIVE;

#if (VSWUPDM_MULTICONTROLLER_SUPPORT == STD_ON)
      if (ActiveJob->Source != (vSwUpdM_NodeIterType)vSwUpdM_GetLocalNode())
      {
        (void)vSwUpdM_RemotePrepareResponseRxTarget(ActiveJob->Source, VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_CONCLUDE_SEGMENT, ActiveJob);

        if (ActiveJob->Result == E_OK)
        {
          ActiveJob->Result = vRpcProxy_vSwUpdM_RemoteConcludeSegment_Target(vSwUpdM_GetDestinationMainOfNode(ActiveJob->Source), segment->DynamicAttributesOfVarSegment.StartAddress, ActiveJob->TargetAddress);
          retVal = VSWUPDM_JOB_STATUS_PENDING;
        }
      }

      if (vSwUpdM_IsWithLocalNodeOfNodeGroup(ActiveJob->RemoteTargetGroup))
#endif
      {
        /* #420 Conclude the writing to a segment by updating the covered range if necessary. */
        vSwUpdM_Segment_ConcludeSegment(segment, (ActiveJob->TargetAddress + ActiveJob->PendingLength), ActiveJob->TargetAddress);
      }

      /* #430 Advance job state to close implicitly opened segment. */
      ActiveJob->State = VSWUPDM_JOB_STATE_FINALIZE_SEGMENT_CLOSE;

      break;
    }
    case VSWUPDM_JOB_STATE_FINALIZE_SEGMENT_CLOSE:
    /* #500 If implicitly opened segment shall be closed. */
    {
      /* #510 If segment was opened implicitly by finalize request (indicated by job operation) */
      if (ActiveJob->Operation == VSWUPDM_JOB_OPERATION_CLOSE_SEGMENT)
      {
        /* #511 Trigger closing of requested segment. */
        ActiveJob->Result = vSwUpdM_Segment_CloseSegment(ActiveJob->EntityIds.SegmentId, VSWUPDM_SID_NONE, ActiveJob, ActiveJob->Source);

        /* #512 Reset job operation to default value. */
        ActiveJob->Operation = VSWUPDM_JOB_OPERATION_DEFAULT;
      }
      else
      {
        retVal = VSWUPDM_JOB_STATUS_FINISHED;
      }

      /* #520 Advance job state to wait for result of any operation triggered above. */
      ActiveJob->State = VSWUPDM_JOB_STATE_FINAL;

      break;
    }
    case VSWUPDM_JOB_STATE_FINALIZE_SEGMENT_ABORT:
    /* #600 If waiting for abortion of stream operation */
    {
      /* #610 Evaluate result of processing pipe. */
      ActiveJob->Result = vSwUpdM_Pipe_ReadResult(vSwUpdMConf_vSwUpdMDataProcess_StreamData, vSwUpdMConf_vSwUpdMDataOutputType_OutputResult);

      break;
    }
    case VSWUPDM_JOB_STATE_FINAL:
    /* #700 If waiting for result of final operations
     *   Indicate that job is finished. */
    {
      retVal = VSWUPDM_JOB_STATUS_FINISHED;

      break;
    }
    case VSWUPDM_JOB_STATE_EVAL_HOOK:
    /* #800 If result of hook function shall be evaluated */
    {
      /* #810 Handle retry action for write operation during ProcessStreamData sequence. */
      if (ActiveJob->HookAction == VSWUPDM_HOOK_ACTION_RESTART)
      {
        retVal = vSwUpdM_Job_HandleWriteRetry(ActiveJob, VSWUPDM_SID_PROCESS_STREAM_DATA);
      }
      else
      {
        ActiveJob->Result = VSWUPDM_E_HOOK_UNSUPPORTED_ACTION;
        retVal = VSWUPDM_JOB_STATUS_FINISHED;
      }

      break;
    }
    case VSWUPDM_JOB_STATE_FAILED:
    /* #900 If job state is "failed", because of negative child result
     *   Return with negative result taken over from child job. */
    {
      break;
    }
    default:
    /* #1000 Otherwise: Invalid state.
     *   Set error in job result. */
    {
      ActiveJob->Result = VSWUPDM_E_INV_STATE;
      break;
    }
  }

  return retVal;
  /* PRQA S 6030, 6050 1 */ /* MD_MSR_STCYC, MD_MSR_STCAL */
} /* vSwUpdM_JobHandler_FinalizeSegment */

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_FinalizeSegmentUpdateLocalState
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
 *
 *
 */
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_FinalizeSegmentUpdateLocalState)
{
  vSwUpdM_JobStatusType       retVal      = VSWUPDM_JOB_STATUS_PENDING;
  /* PRQA S 3679 1 */ /* MD_vSwUpdM_Rule8.13_3679_PointerToModifiableData */
  vSwUpdM_VarSegmentsPtrType  segment     = vSwUpdM_GetAddrVarSegments(ActiveJob->EntityIds.SegmentId.DynamicSegmentId); /* PRQA S 2981 */ /* MD_vSwUpdM_Rule2.2_2981_2892_RedundantInitialization */
  vSwUpdM_ModuleStateType     moduleState = VSWUPDM_MODULE_STATE_UNDEFINED; /* PRQA S 2981 */ /* MD_vSwUpdM_Rule2.2_2981_2892_RedundantInitialization */

  VSWUPDM_DUMMY_STATEMENTS_JOB_HANDLER(); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  /* #10 Evaluate child result from previous cycle. */
  if (vSwUpdM_Job_EvaluateAndApplyChildResult(ActiveJob, TRUE) == E_OK)
  {
    /* #20 Evaluate state of requested module instance. */
    ActiveJob->Result = vSwUpdM_Module_GetStateByPartition(&moduleState, ActiveJob->EntityIds.ModuleId, ActiveJob->EntityIds.PartitionId);

    if (ActiveJob->Result != E_OK)
    {
      ActiveJob->State = VSWUPDM_JOB_STATE_FAILED;
    }
  }

  /* #30 Evaluate job state. */
  switch (ActiveJob->State)
  {
    case VSWUPDM_JOB_STATE_INITIAL:
    /* #100 Initial state: Change state of segment to "finalized". */
    {

      ActiveJob->Result = vSwUpdM_Segment_UpdateAndPersistState(ActiveJob->EntityIds.SegmentId, VSWUPDM_SEGMENT_STATE_FINALIZED, ActiveJob->Source, ActiveJob);

      /* #110 Advance job state to wait for result of any operation triggered above. */
      ActiveJob->State = VSWUPDM_JOB_STATE_FINALIZE_SEGMENT_UPDATE_REGION_STATE;

      break;
    }
    case VSWUPDM_JOB_STATE_FINALIZE_SEGMENT_UPDATE_REGION_STATE:
    /* #200 If waiting for persisting of segment information. */
    {
      /* #210 If module state is "dirty"
        *   Change module state to "clean". */
      if (moduleState == VSWUPDM_MODULE_STATE_DIRTY)
      {
        (void)vSwUpdM_Region_UpdateAndPersistState(ActiveJob->EntityIds.PartitionId, ActiveJob->EntityIds.ModuleId, segment->RegionIdxOfVarSegments, VSWUPDM_REGION_STATE_CLEAN, ActiveJob, ActiveJob->Source);
      }
      else
      {
        retVal = VSWUPDM_JOB_STATUS_ACTIVE;
      }

      ActiveJob->State = VSWUPDM_JOB_STATE_FINALIZE_SEGMENT_UPDATE_MODULE_STATE;

      break;
    }
    case VSWUPDM_JOB_STATE_FINALIZE_SEGMENT_UPDATE_MODULE_STATE:
    /* #300 If waiting for persisting of module information. */
    {
      /* #310 If module state is "dirty"
        *   Change module state to "clean". */
      if (moduleState == VSWUPDM_MODULE_STATE_DIRTY)
      {
        (void)vSwUpdM_Module_UpdateAndPersistState(ActiveJob->EntityIds.PartitionId, ActiveJob->EntityIds.PartitionState, ActiveJob->EntityIds.ModuleId, VSWUPDM_MODULE_STATE_CLEAN, ActiveJob, ActiveJob->Source);
      }

      /* #320 If resume info shall be updated by job
        *   Update resume information to indicate that service is finished, taking over service ID and address.
        *   Force persisting of resume information. */
      if ( (ActiveJob->Result == E_OK)
        && (ActiveJob->UpdateResumeInfo == TRUE) )
      {
        ActiveJob->Result = vSwUpdM_ResumeInfo_UpdateAndPersistState(VSWUPDM_PART_STATE_UNDEFINED, VSWUPDM_SID_NONE, VSWUPDM_RESUME_STATE_FINISHED, segment->EndAddressOfVarSegments, VSWUPDM_UNDEFINED_ADDRESS, segment->EndAddressOfVarSegments, TRUE, ActiveJob->Source);
      }

      /* #340 Advance job state to wait for result of any operation triggered above. */
      ActiveJob->State = VSWUPDM_JOB_STATE_FINAL;

      break;
    }
    case VSWUPDM_JOB_STATE_FINAL:
    /* #400 If waiting for result of final operations
     *   Indicate that job is finished. */
    {
      retVal = VSWUPDM_JOB_STATUS_FINISHED;

      break;
    }
    case VSWUPDM_JOB_STATE_FAILED:
    /* #500 If job state is "failed", because of negative child result
     *   Return with negative result taken over from child job. */
    {
      break;
    }
    default:
    /* #600 Otherwise: Invalid state.
     *   Set error in job result. */
    {
      ActiveJob->Result = VSWUPDM_E_INV_STATE;
      break;
    }
  }

  return retVal;
  /* PRQA S 6030, 6050 1 */ /* MD_MSR_STCYC, MD_MSR_STCAL */
} /* vSwUpdM_JobHandler_FinalizeSegmentUpdateLocalState */

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_SyncPartitionLocal
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
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_SyncPartitionLocal)
{
  vSwUpdM_JobStatusType retVal = VSWUPDM_JOB_STATUS_ACTIVE;

  VSWUPDM_DUMMY_STATEMENTS_JOB_HANDLER(); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  /* #10 Evaluate child result from previous cycle. */
  (void)vSwUpdM_Job_EvaluateAndApplyChildResult(ActiveJob, TRUE);

  /* #20 Evaluate job state. */
  switch (ActiveJob->State)
  {
    case VSWUPDM_JOB_STATE_INITIAL:
    /* #100 If initial conditions for first actual phase shall be established */
    {
      /* #110 Start with first module. */
      ActiveJob->EntityIds.ModuleId = 0u;

      /* #120 Advance job state to check whether first module must be synchronized. */
      ActiveJob->State = VSWUPDM_JOB_STATE_SYNC_PARTITION_CHECK_MODULE;
      retVal           = VSWUPDM_JOB_STATUS_ACTIVE;

      break;
    }
    case VSWUPDM_JOB_STATE_SYNC_PARTITION_CHECK_MODULE:
    /* #200 If check whether current module must be synchronized shall be done */
    {
      vSwUpdM_VarModulesPtrType module = vSwUpdM_GetAddrVarModules(ActiveJob->EntityIds.ModuleId); /* PRQA S 3679 */ /* MD_vSwUpdM_Rule8.13_3679_PointerToModifiableData */

      /* #210 If current module is swappable and instantiated in requested partition */
      if (module->SwappableOfVarModules == TRUE)
      {
        if (vSwUpdM_Module_IsModuleInstantiatedInPartition(ActiveJob->EntityIds.ModuleId, ActiveJob->EntityIds.PartitionId) == TRUE)
        {
#if (VSWUPDM_MULTICONTROLLER_SUPPORT == STD_ON)
          if (!vSwUpdM_IsWithLocalNodeOfNodeGroup(vSwUpdM_GetNodeGroupOwnersIdxOfModule(ActiveJob->EntityIds.ModuleId)))
          {
            retVal = VSWUPDM_JOB_STATUS_ACTIVE;
          }
          else
#endif
          {
            /* #220 Check whether module must be synchronized. */
            (void)vSwUpdM_Module_SyncModule(ActiveJob->EntityIds.ModuleId, VSWUPDM_SID_NONE, FALSE, ActiveJob->Source, ActiveJob);
            retVal = VSWUPDM_JOB_STATUS_PENDING;
          }
        }
      }

      /* #230 Advance job state to handle next module. */
      ActiveJob->State = VSWUPDM_JOB_STATE_SYNC_PARTITION_NEXT_MODULE;

      break;
    }
    case VSWUPDM_JOB_STATE_SYNC_PARTITION_NEXT_MODULE:
    /* #300 If next module shall be handled */
    {
      /* #310 Handle next module. */
      ActiveJob->EntityIds.ModuleId++;

      /* #320 If this wasn't the last module */
      if (ActiveJob->EntityIds.ModuleId < vSwUpdM_GetStaticNumberOfModules())
      {
        /* #330 Advance job state to check whether module is instantiated in requested partition. */
        ActiveJob->State = VSWUPDM_JOB_STATE_SYNC_PARTITION_CHECK_MODULE;
      }
      /* #340 Otherwise: All module instances of requested partition are synchronized. */
      else
      {
        /* #350 Indicate that job is finished. */
        retVal = VSWUPDM_JOB_STATUS_FINISHED;
      }

      break;
    }
    case VSWUPDM_JOB_STATE_FINAL:
    /* #400 If waiting for result of final operations
     *   Indicate that job is finished. */
    {
      retVal = VSWUPDM_JOB_STATUS_FINISHED;
      break;
    }
    case VSWUPDM_JOB_STATE_EVAL_HOOK:
    /* #500 If result of hook function shall be evaluated */
    {
      boolean allowed = FALSE;

      retVal                   = VSWUPDM_JOB_STATUS_FINISHED;
      /* #510 Clear current target address, as not relevant for potential retry. */
      ActiveJob->TargetAddress = VSWUPDM_UNDEFINED_ADDRESS;

      /* #520 Verify whether requested hook operation is applicable. */
      switch (ActiveJob->HookAction)
      {
        case VSWUPDM_HOOK_ACTION_SKIP:
        /* #600 If skip action is requested */
        {
          allowed = TRUE;

          /* #610 If resume info shall be updated by job
           *   Update resume information to indicate that service is finished, taking over service ID, while invalidating the resume address.
           *   Force persisting of resume information. */
          if (ActiveJob->UpdateResumeInfo == TRUE)
          {
            (void)vSwUpdM_ResumeInfo_UpdateAndPersistState(VSWUPDM_PART_STATE_UNDEFINED, VSWUPDM_SID_NONE, VSWUPDM_RESUME_STATE_FINISHED, VSWUPDM_UNDEFINED_ADDRESS, VSWUPDM_UNDEFINED_ADDRESS, VSWUPDM_UNDEFINED_ADDRESS, FALSE, ActiveJob->Source);

            /* #620 Advance job state to wait for persisting of resume information. */
            ActiveJob->State = VSWUPDM_JOB_STATE_FINAL;
            retVal           = VSWUPDM_JOB_STATUS_PENDING;
          }

          break;
        }
        case VSWUPDM_HOOK_ACTION_RETRY:
        case VSWUPDM_HOOK_ACTION_RESTART:
        /* #700 If retry or restart action is requested */
        {
          vSwUpdM_ModuleIdType moduleId = ActiveJob->EntityIds.ModuleId;

          /* #710 Verify requested retry granularity. */
          switch (ActiveJob->RetryGranularity)
          {
            case VSWUPDM_RETRY_GRANULARITY_DEFAULT:
            /* #720 Check whether default granularity is allowed. */
            {
              /* #730 If job failed during synchronization of a module */
              if (moduleId < vSwUpdM_GetStaticNumberOfModules())
              {
                vSwUpdM_ModuleStateType moduleState;

                /* #740 Evaluate state of module instance in requested partition. */
                if (vSwUpdM_Module_GetStateByPartition(&moduleState, moduleId, ActiveJob->EntityIds.PartitionId) == E_OK)
                {
                  /* #741 Requested hook action is allowed. */
                  allowed = TRUE;

                  /* #742 If module is marked dirty */
                  if (moduleState == VSWUPDM_MODULE_STATE_SYNC_DIRTY)
                  {
                    /* #743 Change module state to "clean". */
                    (void)vSwUpdM_Module_UpdateAndPersistState(ActiveJob->EntityIds.PartitionId, ActiveJob->EntityIds.PartitionState, moduleId, VSWUPDM_MODULE_STATE_SYNC_CLEAN, ActiveJob, ActiveJob->Source);

                    /* #744 Advance job state to wait for persisting of module state. */
                    ActiveJob->State = VSWUPDM_JOB_STATE_FINAL;
                    retVal           = VSWUPDM_JOB_STATUS_PENDING;
                  }
                }
              }
              /* #750 Otherwise
               *   Requested hook action is allowed. */
              else
              {
                allowed = TRUE;
              }

              break;
            }
            case VSWUPDM_RETRY_GRANULARITY_MODULE:
            /* #800 Module granularity is allowed. */
            {
              allowed = TRUE;

              /* #810 If retry was requested after all modules were synchronized
               *  Retry last module. */
              if (moduleId >= vSwUpdM_GetStaticNumberOfModules())
              {
                moduleId = vSwUpdM_GetStaticNumberOfModules() - 1u;
              }

              /* #820 Change module state to "undefined" to force re-synchronization. */
              (void)vSwUpdM_Module_UpdateAndPersistState(ActiveJob->EntityIds.PartitionId, ActiveJob->EntityIds.PartitionState, moduleId, VSWUPDM_MODULE_STATE_UNDEFINED, ActiveJob, ActiveJob->Source);

              /* #830 If module is still opened */
              if (moduleId == vSwUpdM_EntityData.OpenIds.ModuleId)
              {
                /* #831 Trigger closing of module. */
                (void)vSwUpdM_Module_CloseModule(moduleId, VSWUPDM_SID_NONE, ActiveJob->Source, NULL_PTR);

                /* #832 Advance job state to wait for closing of module. */
                ActiveJob->State = VSWUPDM_JOB_STATE_FINAL;
                retVal           = VSWUPDM_JOB_STATUS_PENDING;
              }

              break;
            }
            default:
            /* #840 Otherwise: Unsupported retry granularity. */
            {
              break;
            }
          }

          /* #760 If requested hook is allowed */
          if (allowed == TRUE)
          {
            /* #761 Update resume information: Set state to "active", taking over the service ID, while invalidating the resume address. */
            vSwUpdM_ResumeInfo_UpdateState(ActiveJob->EntityIds.PartitionState, vSwUpdM_ResumeInfo.ResumeInfo.CurrentService, VSWUPDM_RESUME_STATE_ACTIVE, VSWUPDM_UNDEFINED_ADDRESS, VSWUPDM_UNDEFINED_ADDRESS, VSWUPDM_UNDEFINED_ADDRESS, FALSE);
          }

          break;
        }
        default:
        /* #770 Otherwise: Unsupported hook action. */
        {
          break;
        }
      }

      /* #800 If hook request isn't allowed, set job result to "unsupported hook action". */
      if (allowed != TRUE)
      {
        ActiveJob->Result = VSWUPDM_E_HOOK_UNSUPPORTED_ACTION;
      }
      /* #810 Otherwise */
      else
      {
        /* #811 If retry action is requested
         *   Overwrite job result with positive return code. */
        if (ActiveJob->HookAction == VSWUPDM_HOOK_ACTION_RETRY)
        {
          ActiveJob->Result = E_OK;
        }
      }

      break;
    }
    case VSWUPDM_JOB_STATE_FAILED:
    /* #900 If job state is "failed", because of negative child result
     *   Return with negative result taken over from child job. */
    {
      break;
    }
    default:
    /* #1000 Otherwise: Invalid state.
     *   Set error in job result. */
    {
      ActiveJob->Result = VSWUPDM_E_INV_STATE;
      break;
    }
  }

  return retVal;
  /* PRQA S 6010, 6030, 6050, 6080 1 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */
} /* vSwUpdM_JobHandler_SyncPartitionLocal */

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_SyncModule
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
 *
 *
 *
 *
 *
 *
 *
 *
 */
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_SyncModule)
{
  vSwUpdM_JobStatusType retVal = VSWUPDM_JOB_STATUS_PENDING; /* PRQA S 2981 */ /* MD_MSR_RetVal */

  VSWUPDM_DUMMY_STATEMENTS_JOB_HANDLER(); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  /* #10 Evaluate child result from previous cycle.
   *   If not okay, apply child result.
   *   If result is SUSPENDED suspend job. */
  retVal = vSwUpdM_Job_EvaluateChildResultOrSuspend(ActiveState, ActiveJob, TRUE);

  if (retVal != VSWUPDM_JOB_STATUS_SUSPENDED)
  {
    vSwUpdM_ModuleStateType moduleState = VSWUPDM_MODULE_STATE_UNDEFINED;

    if (ActiveJob->Result == E_OK)
    {
      /* #20 Get state of module instance in requested partition. */
      ActiveJob->Result = vSwUpdM_Module_GetStateByPartition(&moduleState, ActiveJob->EntityIds.ModuleId, ActiveJob->EntityIds.PartitionId);

      if (ActiveJob->Result != E_OK)
      {
        ActiveJob->State = VSWUPDM_JOB_STATE_FAILED;
      }
    }

    /* #30 Evaluate job state. */
    switch (ActiveJob->State)
    {
      case VSWUPDM_JOB_STATE_INITIAL:
      /* #100 If initial conditions for first actual phase shall be established */
      {
        if (ActiveJob->Result == E_OK)
        {
          boolean restoreSegments = FALSE;
          boolean openModule      = TRUE;

          /* #110 Evaluate state of module instance in requested partition. */
          switch (moduleState)
          {
            case VSWUPDM_MODULE_STATE_SYNC_CLEAN:
            /* #120 If module state is "sync clean"
             *   Synchronization of module was started before, but was suspended by an intended shutdown. */
            {
              /* #121 Restore previous state of segments when opening module. */
              restoreSegments = TRUE;
              /* #122 Advance job state to continue the module synchronization next. */
              ActiveJob->State = VSWUPDM_JOB_STATE_SYNC_MODULE_START_SYNC;

              break;
            }
            case VSWUPDM_MODULE_STATE_SYNC_DIRTY:
            /* #130 If module state is "sync dirty"
             *   Synchronization of module was started before, but was interrupted by an unintended reset. */
            {
              /* #131 If fine-grained resume is enabled */
#if (VSWUPDM_FINE_GRAINED_RESUME == STD_ON)
              /* #132 Restore previous state of segments when opening module. */
              restoreSegments = TRUE;
              /* #133 Advance job state to continue the module synchronization next. */
              ActiveJob->State = VSWUPDM_JOB_STATE_SYNC_MODULE_START_SYNC;
#else
              /* #134 Otherwise: Advance job state to erase module next. */
              ActiveJob->State = VSWUPDM_JOB_STATE_SYNC_MODULE_ERASE;
#endif

              break;
            }
            case VSWUPDM_MODULE_STATE_SYNC_FINISHED:
            case VSWUPDM_MODULE_STATE_COMPARE_PENDING:
            /* #140 If module state is "sync finished" or "compare pending"
             *   Copying of module was finished, but comparison was suspended by a shutdown. */
            {
              /* #141 Advance job state to continue the module comparison next, but skip opening the module. */
              ActiveJob->State = VSWUPDM_JOB_STATE_SYNC_MODULE_COMPARE;
              openModule       = FALSE;

              break;
            }
            case VSWUPDM_MODULE_STATE_ERASED:
            /* #150 If module state is "erased" */
            {
              /* #151 Advance job state to continue the module synchronization next. */
              ActiveJob->State = VSWUPDM_JOB_STATE_SYNC_MODULE_START_SYNC;

              break;
            }
            default:
            /* #160 Otherwise, module synchronization was not started yet.
             *   Do not restore any persisted segments, but only initialize free and reserved segments. */
            {
              /* #161 Advance job state to erase module next. */
              ActiveJob->State = VSWUPDM_JOB_STATE_SYNC_MODULE_ERASE;

              break;
            }
          }

          /* #170 If module shall be opened */
          if (openModule == TRUE)
          {
            /* #171 If module isn't opened yet */
            if (vSwUpdM_EntityData.OpenIds.ModuleId == VSWUPDM_INVALID_ID)
            {
              /* #172 Use job operation to remember that module was opened implicitly. */
              ActiveJob->Operation = VSWUPDM_JOB_OPERATION_CLOSE_MODULE;
            }
            else
            {
              vSwUpdM_EntityData.OpenIds.ModuleId = VSWUPDM_INVALID_ID;
            }

            /* #180 Trigger opening of requested module. */
            (void)vSwUpdM_Module_OpenModule(ActiveJob->EntityIds.ModuleId, restoreSegments, VSWUPDM_SID_NONE, ActiveJob->Source, ActiveJob);
          }
        }

        break;
      }
      case VSWUPDM_JOB_STATE_SYNC_MODULE_ERASE:
      /* #200 If requested module shall be erased */
      {
        /* #210 Update and persist resume information to indicate that service is active, taking over service ID and address,
         *   regardless of whether UpdateResumeInfo flag is set or not.
         *   directly set to "pending" for later shutdown. */
        ActiveJob->Result = vSwUpdM_ResumeInfo_UpdateAndPersistState(VSWUPDM_PART_STATE_UNDEFINED, VSWUPDM_SID_NONE, VSWUPDM_RESUME_STATE_ACTIVE, vSwUpdM_ResumeInfo.ResumeInfo.MemoryAddress, vSwUpdM_ResumeInfo.ResumeInfo.StreamAddress, vSwUpdM_ResumeInfo.TriggerAddress, vSwUpdM_ResumeInfo.ResumeInfo.IsAddressValid, ActiveJob->Source);
        vSwUpdM_ResumeInfo_UpdateState(VSWUPDM_PART_STATE_UNDEFINED, VSWUPDM_SID_NONE, VSWUPDM_RESUME_STATE_PENDING, vSwUpdM_ResumeInfo.ResumeInfo.MemoryAddress, vSwUpdM_ResumeInfo.ResumeInfo.StreamAddress, vSwUpdM_ResumeInfo.TriggerAddress, vSwUpdM_ResumeInfo.ResumeInfo.IsAddressValid);

        if (ActiveJob->Result == E_OK)
        {
          /* #220 Trigger erasing of requested module. */
          (void)vSwUpdM_Module_EraseModule(ActiveJob->EntityIds.ModuleId, (vSwUpdM_QueuePrioType)VSWUPDM_JOB_PRIO_DEFAULT, FALSE, ActiveJob, ActiveJob->Source);

          /* #230 Advance job state to start the module synchronization next. */
          ActiveJob->State = VSWUPDM_JOB_STATE_SYNC_MODULE_START_SYNC;
        }

        break;
      }
      case VSWUPDM_JOB_STATE_SYNC_MODULE_START_SYNC:
      /* #300 If module synchronization shall be started: */
      {
        vSwUpdM_ProcessInfoType processInfo;

        /* #310 Process module using CopyModule data process. */
        (void)vSwUpdM_InitProcessInfo(&processInfo);
        vSwUpdM_Pipe_PrepareProcessData(vSwUpdM_ProcessScope_Module, vSwUpdMConf_vSwUpdMDataProcess_CopyModule, &vSwUpdM_ProcessConfig_CopyModule, &processInfo);
        vSwUpdM_Module_ProcessModule(ActiveJob, TRUE);

        /* #320 Advance job state to compare module contents next. */
        ActiveJob->State = VSWUPDM_JOB_STATE_SYNC_MODULE_COMPARE;

        break;
      }
      case VSWUPDM_JOB_STATE_SYNC_MODULE_COMPARE:
      /* #400 If module contents shall be compared */
      {
        Std_ReturnType      spawnResult;
        vSwUpdM_JobPtrType  spawnedJob;

        /* #420 Enter critical section to ensure exclusive access of state and job queue. */
        VSWUPDM_ENTER_CRITICAL_SECTION();

        /* #430 Spawn job to copy memory contents of current segment. */
        spawnedJob = vSwUpdM_Job_Spawn(&spawnResult, VSWUPDM_JOB_TYPE_COMPARE_MODULE, VSWUPDM_JOB_OPERATION_DEFAULT, ActiveJob->CurrentPrio + 1u, VSWUPDM_SID_NONE, ActiveJob, ActiveJob->Source);

        /* #431 Job attributes are safe to be modified when job was successfully spawned and access is still protected by critical section. */
        if (spawnResult == E_OK)
        {
          /* #432 Pass entity IDs to compare module job. */
          spawnedJob->EntityIds = ActiveJob->EntityIds;
        }

        /* #440 Leave critical section ensuring exclusive access of state and job queue. */
        VSWUPDM_LEAVE_CRITICAL_SECTION();

        /* #450 Advance job state to finalize synchronization of module next. */
        ActiveJob->State = VSWUPDM_JOB_STATE_SYNC_MODULE_FINALIZE;

        break;
      }
      case VSWUPDM_JOB_STATE_SYNC_MODULE_FINALIZE:
      /* #500 If synchronization of module shall be finalized */
      {
        /* #510 Set state of module instance to "finalized", to signal successful synchronization. */
        (void)vSwUpdM_Module_UpdateAndPersistState(ActiveJob->EntityIds.PartitionId, ActiveJob->EntityIds.PartitionState, ActiveJob->EntityIds.ModuleId, VSWUPDM_MODULE_STATE_VERIFIED, ActiveJob, ActiveJob->Source);
        /* #520 Advance job state to validate the module next */
        ActiveJob->State = VSWUPDM_JOB_STATE_SYNC_MODULE_VALIDATE;

        break;
      }
      case VSWUPDM_JOB_STATE_SYNC_MODULE_VALIDATE:
      /* #600 If module instance shall be validated */
      {
        /* #610 Trigger the validation of the synchronized module, taking over the revision from the module instance in the active partition. */
        (void)vSwUpdM_Module_UpdateValid(ActiveJob->EntityIds.PartitionState, ActiveJob->EntityIds.ModuleId, VSWUPDM_VALIDITY_VALID, VSWUPDM_REVISION_UPDATE_TAKE_OVER, VSWUPDM_SID_NONE, ActiveJob->Source, ActiveJob);
        /* #620 If modules was opened implicitly by erase request (indicated by job operation) */
        if (ActiveJob->Operation == VSWUPDM_JOB_OPERATION_CLOSE_MODULE)
        {
          /* #621 Trigger closing of module afterwards (order ensured by job priority). */
          (void)vSwUpdM_Module_CloseModule(ActiveJob->EntityIds.ModuleId, VSWUPDM_SID_NONE, ActiveJob->Source, ActiveJob);
        }

        /* #630 If resume info shall be updated by job
         *   Update resume information to indicate that service is finished, taking over service ID, while invalidating the resume address.
         *   Force persisting of resume information. */
        if (ActiveJob->UpdateResumeInfo == TRUE)
        {
          (void)vSwUpdM_ResumeInfo_UpdateAndPersistState(VSWUPDM_PART_STATE_UNDEFINED, VSWUPDM_SID_NONE, VSWUPDM_RESUME_STATE_FINISHED, vSwUpdM_ResumeInfo.ResumeInfo.MemoryAddress, vSwUpdM_ResumeInfo.ResumeInfo.StreamAddress, vSwUpdM_ResumeInfo.TriggerAddress, vSwUpdM_ResumeInfo.ResumeInfo.IsAddressValid, ActiveJob->Source);
        }

        /* #640 Advance job state to wait for result of triggered operations. */
        ActiveJob->State = VSWUPDM_JOB_STATE_FINAL;

        break;
      }
      case VSWUPDM_JOB_STATE_FINAL:
      /* #700 If waiting for result of final operations
       *   Indicate that job is finished. */
      {
        retVal = VSWUPDM_JOB_STATUS_FINISHED;
        break;
      }
      case VSWUPDM_JOB_STATE_EVAL_HOOK:
      /* #800 If result of hook function shall be evaluated */
      {
        boolean allowed = FALSE;

        retVal                   = VSWUPDM_JOB_STATUS_FINISHED;
        /* #810 Clear current target address, as not relevant for potential retry. */
        ActiveJob->TargetAddress = VSWUPDM_UNDEFINED_ADDRESS;

        /* #820 Verify whether requested hook operation is applicable. */
        switch (ActiveJob->HookAction)
        {
          case VSWUPDM_HOOK_ACTION_RETRY:
          case VSWUPDM_HOOK_ACTION_RESTART:
          /* #830 If retry or restart action is requested */
          {
            /* #840 Verify requested retry granularity. */
            switch (ActiveJob->RetryGranularity)
            {
              case VSWUPDM_RETRY_GRANULARITY_DEFAULT:
              /* #850 Check whether default granularity is allowed. */
              {
                /* #851 Requested hook action is allowed. */
                allowed = TRUE;

                /* #852 If module is marked dirty */
                if (moduleState == VSWUPDM_MODULE_STATE_SYNC_DIRTY)
                {
                  /* #853 Change module state to "sync clean". */
                  (void)vSwUpdM_Module_UpdateAndPersistState(ActiveJob->EntityIds.PartitionId, ActiveJob->EntityIds.PartitionState, ActiveJob->EntityIds.ModuleId, VSWUPDM_MODULE_STATE_SYNC_CLEAN, NULL_PTR, ActiveJob->Source);

                  /* #854 Advance job state to wait for persisting of module state. */
                  ActiveJob->State = VSWUPDM_JOB_STATE_FINAL;
                  retVal           = VSWUPDM_JOB_STATUS_PENDING;
                }

                break;
              }
              case VSWUPDM_RETRY_GRANULARITY_OPERATION:
              case VSWUPDM_RETRY_GRANULARITY_MODULE:
              /* #860 Operation or module granularity is allowed */
              {
                allowed = TRUE;

                /* #861 Change module state to "undefined" to force re-synchronization. */
                (void)vSwUpdM_Module_UpdateAndPersistState(ActiveJob->EntityIds.PartitionId, ActiveJob->EntityIds.PartitionState, ActiveJob->EntityIds.ModuleId, VSWUPDM_MODULE_STATE_UNDEFINED, NULL_PTR, ActiveJob->Source);
                /* #862 Trigger closing of requested module. */
                (void)vSwUpdM_Module_CloseModule(ActiveJob->EntityIds.ModuleId, VSWUPDM_SID_NONE, ActiveJob->Source, NULL_PTR);

                /* #863 Advance job state to wait for result of triggered operations. */
                ActiveJob->State = VSWUPDM_JOB_STATE_FINAL;
                retVal           = VSWUPDM_JOB_STATUS_PENDING;

                break;
              }
              default:
              /* #870 Otherwise: Unsupported retry granularity. */
              {
                break;
              }
            }

            /* #880 If requested hook is allowed */
            if (allowed == TRUE)
            {
              vSwUpdM_AddressType startAddress = vSwUpdM_GetStartAddressOfRegion(vSwUpdM_GetRegionIdxOfModule2Region(vSwUpdM_GetModule2RegionIdxOfModule(ActiveJob->EntityIds.ModuleId)));

              /* #881 Update resume information: Set state to "active", taking over the service ID,
               *   while setting the resume address to the start address of the first module region. */
              vSwUpdM_ResumeInfo_UpdateState(ActiveJob->EntityIds.PartitionState, vSwUpdM_ResumeInfo.ResumeInfo.CurrentService, VSWUPDM_RESUME_STATE_ACTIVE, startAddress, VSWUPDM_UNDEFINED_ADDRESS, startAddress, TRUE);
            }

            break;
          }
          default:
          /* #890 Otherwise: Unsupported hook action. */
          {
            break;
          }
        }

        /* #900 If hook request isn't allowed, set job result to "unsupported hook action". */
        if (allowed != TRUE)
        {
          ActiveJob->Result = VSWUPDM_E_HOOK_UNSUPPORTED_ACTION;
        }
        /* #910 Otherwise */
        else
        {
          /* #911 If retry action is requested
           *   Overwrite job result with positive return code. */
          if (ActiveJob->HookAction == VSWUPDM_HOOK_ACTION_RETRY)
          {
            ActiveJob->Result = E_OK;
          }
        }

        break;
      }
      case VSWUPDM_JOB_STATE_FAILED:
      /* #1000 If job state is "failed", because of negative child result
       *   Return with negative result taken over from child job. */
      {
        break;
      }
      default:
      /* #1100 Otherwise: Invalid state.
       *   Set error in job result. */
      {
        ActiveJob->Result = VSWUPDM_E_INV_STATE;
        break;
      }
    }
  }

  return retVal;
  /* PRQA S 6010, 6030, 6050, 6080 1 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */
} /* vSwUpdM_JobHandler_SyncModule */

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_CompareModule
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
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_CompareModule)
{
  vSwUpdM_JobStatusType   retVal = VSWUPDM_JOB_STATUS_PENDING;

  VSWUPDM_DUMMY_STATEMENTS_JOB_HANDLER(); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  /* #10 Evaluate child result from previous cycle. */
  (void)vSwUpdM_Job_EvaluateAndApplyChildResult(ActiveJob, TRUE);

  /* #20 Evaluate job state. */
  switch (ActiveJob->State)
  {
    case VSWUPDM_JOB_STATE_INITIAL:
    /* #100 If initial conditions for first actual phase shall be established */
    {
      vSwUpdM_ModuleStateType moduleState;

      /* #110 Evaluate state of module instance in requested partition. */
      ActiveJob->Result = vSwUpdM_Module_GetStateByPartition(&moduleState, ActiveJob->EntityIds.ModuleId, ActiveJob->EntityIds.PartitionId);

      if (ActiveJob->Result == E_OK)
      {
        boolean restoreSegments = FALSE;

        /* #120 Advance job state to start the module comparison next. */
        ActiveJob->State = VSWUPDM_JOB_STATE_COMPARE_MODULE_TRIGGER_PROCESSING;

        /* #130 If module state is "compare pending"
         *   Comparison of module was started before, but was suspended by an intended or unintended shutdown. */
        if (moduleState == VSWUPDM_MODULE_STATE_COMPARE_PENDING)
        {
          /* #131 Restore previous state of segments when opening module. */
          restoreSegments = TRUE;
        }
        /* #140 Otherwise, module comparison wasn't started yet.
         *   Do not restore any persisted segments, but only initialize free and reserved segments. */

        /* #150 If module isn't opened yet */
        if (vSwUpdM_EntityData.OpenIds.ModuleId == VSWUPDM_INVALID_ID)
        {
          /* #151 Use job operation to remember that module was opened implicitly. */
          ActiveJob->Operation = VSWUPDM_JOB_OPERATION_CLOSE_MODULE;

        }
        else
        {
          vSwUpdM_EntityData.OpenIds.ModuleId = VSWUPDM_INVALID_ID;
        }

        /* #160 Trigger opening of requested module. */
        (void)vSwUpdM_Module_OpenModule(ActiveJob->EntityIds.ModuleId, restoreSegments, VSWUPDM_SID_NONE, ActiveJob->Source, ActiveJob);
      }

      break;
    }
    case VSWUPDM_JOB_STATE_COMPARE_MODULE_TRIGGER_PROCESSING:
    /* #200 Compare processing required: */
    {
      vSwUpdM_ProcessInfoType processInfo;

      /* #210 Process module using CompareModule data process. */
      (void)vSwUpdM_InitProcessInfo(&processInfo);
      vSwUpdM_Pipe_PrepareProcessData(vSwUpdM_ProcessScope_Module, vSwUpdMConf_vSwUpdMDataProcess_CompareModule, &vSwUpdM_ProcessConfig_CompareModule, &processInfo);
      vSwUpdM_Module_ProcessModule(ActiveJob, TRUE);

      ActiveJob->State = VSWUPDM_JOB_STATE_COMPARE_MODULE_CLOSE_MODULE;
      break;
    }
    case VSWUPDM_JOB_STATE_FAILED:
    /* #300 If child job has returned an error: */
    {
      /* #310 If module was opened implicitly:
       *   Trigger closing of module. */
      if (ActiveJob->Operation == VSWUPDM_JOB_OPERATION_CLOSE_MODULE)
      {
        /* Remember that CloseModule was requested, so if this fails
         * do not try again. */
        ActiveJob->Operation = VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_NONE;
        (void)vSwUpdM_Module_CloseModule(ActiveJob->EntityIds.ModuleId, VSWUPDM_SID_NONE, ActiveJob->Source, ActiveJob);
      }
      else
      {
        retVal = VSWUPDM_JOB_STATUS_ACTIVE;
      }

      /* #320 Suppress negative result. Will be returned in next step. */
      ActiveJob->Result = E_OK;

      ActiveJob->State = VSWUPDM_JOB_STATE_COMPARE_MODULE_FAIL_CLOSE_MODULE;
      break;
    }
    case VSWUPDM_JOB_STATE_COMPARE_MODULE_FAIL_CLOSE_MODULE:
    /* #400 Fail return state. */
    {
      /* #410 Return error. */
      ActiveJob->Result = VSWUPDM_E_COMPARE_FAILED;

      /* #420 Indicate that job is finished. */
      retVal = VSWUPDM_JOB_STATUS_FINISHED;

      break;
    }
    case VSWUPDM_JOB_STATE_COMPARE_MODULE_CLOSE_MODULE:
    /* #500 If compare processing has finished: */
    {
      /* #510 If module was opened implicitly:
       *   Trigger closing of module. */
      if (ActiveJob->Operation == VSWUPDM_JOB_OPERATION_CLOSE_MODULE)
      {
        /* Remember that CloseModule was requested, so if this fails
         * do not try again. */
        ActiveJob->Operation = VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_NONE;
        (void)vSwUpdM_Module_CloseModule(ActiveJob->EntityIds.ModuleId, VSWUPDM_SID_NONE, ActiveJob->Source, ActiveJob);
      }
      else
      {
        retVal = VSWUPDM_JOB_STATUS_ACTIVE;
      }

      ActiveJob->State = VSWUPDM_JOB_STATE_FINAL;
      break;
    }
    case VSWUPDM_JOB_STATE_FINAL:
    /* #600 Final state. */
    {

      /* #610 Indicate that job is finished. */
      retVal = VSWUPDM_JOB_STATUS_FINISHED;

      break;
    }
    default:
    /* #700 Otherwise: Invalid state.
     *   Set error in job result. */
    {
      ActiveJob->Result = VSWUPDM_E_INV_STATE;
      break;
    }
  }

  return retVal;
  /* PRQA S 6010, 6030, 6050, 6080 1 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */
} /* vSwUpdM_JobHandler_CompareModule */

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_ValidateModuleUpdateLocalState
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
 */
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_ValidateModuleUpdateLocalState)
{
  vSwUpdM_JobStatusType retVal = VSWUPDM_JOB_STATUS_PENDING;

  /* #10 Evaluate child result from previous cycle. */
  (void)vSwUpdM_Job_EvaluateAndApplyChildResult(ActiveJob, FALSE);

  VSWUPDM_DUMMY_STATEMENTS_JOB_HANDLER(); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  if (ActiveState == VSWUPDM_STATE_SUSPENDING)
  {
    retVal = VSWUPDM_JOB_STATUS_SUSPENDED;
  }

  /* #20 Evaluate job state. */
  switch (ActiveJob->State)
  {
    case VSWUPDM_JOB_STATE_INITIAL:
    /* #100 INITIAL state: Trigger validation of given module. */
    {
      ActiveJob->Result = vSwUpdM_Module_UpdateValid(vSwUpdM_EntityData.OpenIds.PartitionState, ActiveJob->EntityIds.ModuleId, VSWUPDM_VALIDITY_VALID, VSWUPDM_REVISION_UPDATE_INCREMENT, VSWUPDM_SID_NONE, ActiveJob->Source, ActiveJob);

      ActiveJob->State = VSWUPDM_JOB_STATE_FINAL;
      break;
    }
    case VSWUPDM_JOB_STATE_FINAL:
    /* #110 FINAL state: Finish job. */
    {
      retVal = VSWUPDM_JOB_STATUS_FINISHED;
      break;
    }
    case VSWUPDM_JOB_STATE_FAILED:
    /* #120 FAILED state: Finish job. */
    {
      break;
    }
    default:
    {
      ActiveJob->Result = VSWUPDM_E_INV_STATE;
      break;
    }
  }

  return retVal;
} /* vSwUpdM_JobHandler_ValidateModuleUpdateLocalState */

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_InvalidateModuleUpdateLocalState
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
 */
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_InvalidateModuleUpdateLocalState)
{
  vSwUpdM_JobStatusType retVal = VSWUPDM_JOB_STATUS_PENDING;

  VSWUPDM_DUMMY_STATEMENTS_JOB_HANDLER(); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  /* #10 Evaluate child result from previous cycle. */
  (void)vSwUpdM_Job_EvaluateAndApplyChildResult(ActiveJob, FALSE);

  if (ActiveState == VSWUPDM_STATE_SUSPENDING)
  {
    retVal = VSWUPDM_JOB_STATUS_SUSPENDED;
  }

  /* #20 Evaluate job state. */
  switch (ActiveJob->State)
  {
    case VSWUPDM_JOB_STATE_INITIAL:
    /* #100 INITIAL state: Trigger invalidation of given module. */
    {
      ActiveJob->Result = vSwUpdM_Module_UpdateValid(vSwUpdM_EntityData.OpenIds.PartitionState, ActiveJob->EntityIds.ModuleId, VSWUPDM_VALIDITY_INVALID, VSWUPDM_REVISION_UPDATE_NONE, VSWUPDM_SID_NONE, ActiveJob->Source, ActiveJob);

      ActiveJob->State = VSWUPDM_JOB_STATE_FINAL;
      break;
    }
    case VSWUPDM_JOB_STATE_FINAL:
    /* #110 FINAL state: Finish job. */
    {
      retVal = VSWUPDM_JOB_STATUS_FINISHED;

      break;
    }
    case VSWUPDM_JOB_STATE_FAILED:
    /* #120 FAILED state: Finish job. */
    {
      break;
    }
    default:
    {
      ActiveJob->Result = VSWUPDM_E_INV_STATE;
      break;
    }
  }

  return retVal;
} /* vSwUpdM_JobHandler_InvalidateModuleUpdateLocalState */

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_FinalizeSyncPartition
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
 */
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_FinalizeSyncPartition)
{
  vSwUpdM_JobStatusType retVal = VSWUPDM_JOB_STATUS_PENDING; /* PRQA S 2981 */ /* MD_MSR_RetVal */

  VSWUPDM_DUMMY_STATEMENTS_JOB_HANDLER(); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  /* #10 Evaluate child result from previous cycle.
   *   If not okay, apply child result.
   *   If result is SUSPENDED suspend job. */
  retVal = vSwUpdM_Job_EvaluateChildResultOrSuspend(ActiveState, ActiveJob, FALSE);

  /* #20 If suspend of operation is requested
   *     Indicate that job is suspended. */
  if (retVal != VSWUPDM_JOB_STATUS_SUSPENDED)
  {
    /* #30 Otherwise: Evaluate job State: */
    switch (ActiveJob->State)
    {
      case VSWUPDM_JOB_STATE_INITIAL:
      /* #100 If this is the initial call. */
      {
         /* #110 If resume info shall be updated by job
         *   Update resume information to indicate that service is finished, taking over service ID, while invalidating the resume address.
         *   Force persisting of resume information. */
        if (ActiveJob->UpdateResumeInfo == TRUE)
        {
          (void)vSwUpdM_ResumeInfo_UpdateAndPersistState(VSWUPDM_PART_STATE_UNDEFINED, VSWUPDM_SID_NONE, VSWUPDM_RESUME_STATE_FINISHED, VSWUPDM_UNDEFINED_ADDRESS, VSWUPDM_UNDEFINED_ADDRESS, VSWUPDM_UNDEFINED_ADDRESS, FALSE, ActiveJob->Source);

          retVal = VSWUPDM_JOB_STATUS_PENDING;
        }

        /* #120 If requested partition is the backup target, the synchronization was used to create the backup. */
        if (vSwUpdM_Part_IsPartitionStateSet(vSwUpdM_GetVarPartitions(ActiveJob->EntityIds.PartitionId).DynamicAttributesOfVarPartitions.State, VSWUPDM_PART_STATE_BACKUP_TARGET) == TRUE)
        {
          /* #121 Partition is now backup source as well. Update and persist partition state. */
          ActiveJob->Result = vSwUpdM_Part_UpdateState(vSwUpdM_EntityData.OpenIds.PartitionId, vSwUpdM_EntityData.OpenIds.PartitionState, (VSWUPDM_PART_STATE_BACKUP_TARGET | VSWUPDM_PART_STATE_BACKUP_SOURCE));

          if (ActiveJob->Result == E_OK)
          {
            ActiveJob->Result = vSwUpdM_Part_PersistState(VSWUPDM_SID_NONE, ActiveJob);
          }

          retVal = VSWUPDM_JOB_STATUS_PENDING;
        }

        ActiveJob->State = VSWUPDM_JOB_STATE_FINAL;

        break;
      }
      case VSWUPDM_JOB_STATE_FINAL:
      /* #200 In case all children are finished, finish this job. */
      {
        retVal = VSWUPDM_JOB_STATUS_FINISHED;

        break;
      }
      case VSWUPDM_JOB_STATE_FAILED:
      /* #300 In case a child job has reported an error, finish this job. */
      {
        break;
      }
      default:
      {
        ActiveJob->Result = VSWUPDM_E_INV_STATE;
        break;
      }
    }
  }
  return retVal;
} /* vSwUpdM_JobHandler_FinalizeSyncPartition */

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_SwapPartitionCheck
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
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_SwapPartitionCheck)
{
  vSwUpdM_JobStatusType       retVal = VSWUPDM_JOB_STATUS_PENDING;
  vSwUpdM_PartitionStateType  state;

  VSWUPDM_DUMMY_STATEMENTS_JOB_HANDLER(); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  /* #10 Evaluate child result from previous cycle. */
  (void)vSwUpdM_Job_EvaluateAndApplyChildResult(ActiveJob, FALSE);

  state = vSwUpdM_GetVarPartitions(ActiveJob->EntityIds.PartitionId).DynamicAttributesOfVarPartitions.State;

  /* #20 If the requested partition is the inactive partition
   *   Collapse compound partition state to "inactive" only. */
  if (vSwUpdM_Part_IsPartitionStateSet(state, VSWUPDM_PART_STATE_INACTIVE) == TRUE)
  {
    state = VSWUPDM_PART_STATE_INACTIVE;
  }
  /* #22 Otherwise, if the requested partition is the backup source
   *   Collapse compound partition state to "backup source" only. */
  else if (vSwUpdM_Part_IsPartitionStateSet(state, VSWUPDM_PART_STATE_BACKUP_SOURCE) == TRUE)
  {
    state = VSWUPDM_PART_STATE_BACKUP_SOURCE;
  }
  /* #23 Otherwise */
  else
  {
    /* #24 Partition state remains unchanged. */
  }

  /* #30 Evaluate job state. */
  switch (ActiveJob->State)
  {
    case VSWUPDM_JOB_STATE_INITIAL:
    /* #100 If state of partition shall be changed */
    {
      /* #110 Evaluate current partition state. */
      switch (state)
      {
        case VSWUPDM_PART_STATE_INACTIVE:
        case VSWUPDM_PART_STATE_BACKUP_SOURCE:
        /* #120 If the inactive partition shall be activated or the backup shall be restored */
        {
          /* #121 Set the activation pending flag in the partition state. */
          state |= VSWUPDM_PART_STATE_ACTIVATION_PENDING;

          ActiveJob->Result = vSwUpdM_Part_UpdateState(vSwUpdM_EntityData.OpenIds.PartitionId, vSwUpdM_EntityData.OpenIds.PartitionState, state);

          break;
        }
        case VSWUPDM_PART_STATE_ACTIVE:
        /* #130 If an early rollback to the still active partition shall be performed */
        {
          vSwUpdM_PartitionIdType pendingPartitionId;

          /* #131 Determine the partition which is marked to be activated. */
          ActiveJob->Result = vSwUpdM_Part_GetIdByState(&pendingPartitionId, VSWUPDM_PART_STATE_ACTIVATION_PENDING);

          /* #132 If found */
          if (ActiveJob->Result == E_OK)
          {
            /* #133 Clear the activation pending flag in the partition state. */
            ActiveJob->Result = vSwUpdM_Part_UpdateState(pendingPartitionId, VSWUPDM_PART_STATE_ACTIVATION_PENDING, (vSwUpdM_GetVarPartitions(pendingPartitionId).DynamicAttributesOfVarPartitions.State ^ VSWUPDM_PART_STATE_ACTIVATION_PENDING));
          }
          /* #134 Otherwise
           *   Report error. */

          break;
        }
        default:
        /* #140 Swap not allowed for requested partition
          *   Report error. */
        {
          ActiveJob->Result = VSWUPDM_E_INV_STATE;

          break;
        }
      }

      ActiveJob->State = VSWUPDM_JOB_STATE_FINAL;

      break;
    }
    case VSWUPDM_JOB_STATE_FINAL:
    /* #300 If waiting for result of final operation
     *   Indicate that job is finished. */
    {
      retVal = VSWUPDM_JOB_STATUS_FINISHED;
      break;
    }
    case VSWUPDM_JOB_STATE_FAILED:
    /* #400 If job state is "failed", because of negative child result
     *   Return with negative result taken over from child job. */
    {
      break;
    }
    default:
    /* #500 Otherwise: Invalid state.
     *   Set error in job result. */
    {
      ActiveJob->Result = VSWUPDM_E_INV_STATE;
      break;
    }
  }

  return retVal;
  /* PRQA S 6010, 6030 1 */ /* MD_MSR_STPTH, MD_MSR_STCYC */
} /* vSwUpdM_JobHandler_SwapPartitionCheck */

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_SwapPartitionWork
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
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_SwapPartitionWork)
{
  vSwUpdM_JobStatusType       retVal = VSWUPDM_JOB_STATUS_PENDING;
  Std_ReturnType              result = E_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vSwUpdM_PartitionStateType  state;

  VSWUPDM_DUMMY_STATEMENTS_JOB_HANDLER(); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  /* #10 Evaluate child result from previous cycle. */
  (void)vSwUpdM_Job_EvaluateAndApplyChildResult(ActiveJob, FALSE);

  state = vSwUpdM_GetVarPartitions(ActiveJob->EntityIds.PartitionId).DynamicAttributesOfVarPartitions.State;

  /* #20 If the requested partition is the inactive partition
   *   Collapse compound partition state to "inactive" only. */
  if (vSwUpdM_Part_IsPartitionStateSet(state, VSWUPDM_PART_STATE_INACTIVE) == TRUE)
  {
    state = VSWUPDM_PART_STATE_INACTIVE;
  }
  /* #22 Otherwise, if the requested partition is the backup source
   *   Collapse compound partition state to "backup source" only. */
  else if (vSwUpdM_Part_IsPartitionStateSet(state, VSWUPDM_PART_STATE_BACKUP_SOURCE) == TRUE)
  {
    state = VSWUPDM_PART_STATE_BACKUP_SOURCE;
  }
  /* #23 Otherwise */
  else
  {
    /* #24 Partition state remains unchanged. */
  }

  /* #30 Evaluate job state. */
  switch (ActiveJob->State)
  {
    case VSWUPDM_JOB_STATE_INITIAL:
    {
      /* #151 Persist updated partition state. */
      ActiveJob->Result = vSwUpdM_Part_PersistState(VSWUPDM_SID_NONE, ActiveJob);

      /* #152 Advance job state to change update state next. */
      ActiveJob->State = VSWUPDM_JOB_STATE_PENDING;

      break;
    }
    case VSWUPDM_JOB_STATE_PENDING:
    /* #200 If update state shall be changed */
    {
      /* #210 Evaluate current partition state. */
      switch (state)
      {
        case VSWUPDM_PART_STATE_INACTIVE:
        case VSWUPDM_PART_STATE_BACKUP_SOURCE:
        /* #220 If the requested partition is the inactive partition or the backup source
         *  Change update state to indicate pending swap. */
        {
          result = vSwUpdM_General_UpdateState(VSWUPDM_UPDATE_STATE_SWAP, VSWUPDM_SID_NONE, ActiveJob, ActiveJob->Source);

          break;
        }
        case VSWUPDM_PART_STATE_ACTIVE:
        /* #230 If the requested partition is the active partition
         *  Reset update state to idle. */
        {
          result = vSwUpdM_General_UpdateState(VSWUPDM_UPDATE_STATE_IDLE, VSWUPDM_SID_NONE, ActiveJob, ActiveJob->Source);

          break;
        }
        default:
        /* #240 Otherwise
         *  Report error. */
        {
          result = VSWUPDM_E_INV_STATE;

          break;
        }
      }

      ActiveJob->Result = result;
      /* #250 Advance job state to wait for persisting of update state. */
      ActiveJob->State  = VSWUPDM_JOB_STATE_FINAL;

      break;
    }
    case VSWUPDM_JOB_STATE_FINAL:
    /* #300 If waiting for result of final operation
     *   Indicate that job is finished. */
    {
      retVal = VSWUPDM_JOB_STATUS_FINISHED;
      break;
    }
    case VSWUPDM_JOB_STATE_FAILED:
    /* #400 If job state is "failed", because of negative child result
     *   Return with negative result taken over from child job. */
    {
      break;
    }
    default:
    /* #500 Otherwise: Invalid state.
     *   Set error in job result. */
    {
      ActiveJob->Result = VSWUPDM_E_INV_STATE;
      break;
    }
  }

  return retVal;
  /* PRQA S 6010, 6030 1 */ /* MD_MSR_STPTH, MD_MSR_STCYC */
} /* vSwUpdM_JobHandler_SwapPartitionWork */

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_TriggerConfirmation
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 */
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_TriggerConfirmation) /* PRQA S 3673 */ /* MD_vSwUpdM_Rule8.13_3673_PointerToConstParameter */
{
  vSwUpdM_JobStatusType retVal = VSWUPDM_JOB_STATUS_FINISHED;

  VSWUPDM_DUMMY_STATEMENTS_JOB_HANDLER(); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  if (ActiveState == VSWUPDM_STATE_SUSPENDING)
  {
    retVal = VSWUPDM_JOB_STATUS_SUSPENDED;
  }

  return retVal;
} /* vSwUpdM_JobHandler_TriggerConfirmation */

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_Suspend
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
 */
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_Suspend)
{
  vSwUpdM_JobStatusType retVal = VSWUPDM_JOB_STATUS_PENDING;

  VSWUPDM_DUMMY_STATEMENTS_JOB_HANDLER(); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  /* #10 Evaluate child result from previous cycle. */
  (void)vSwUpdM_Job_EvaluateAndApplyChildResult(ActiveJob, FALSE);

  /* #11 Evaluate job state. */
  switch (ActiveJob->State)
  {
    case VSWUPDM_JOB_STATE_INITIAL:
    /* #20 If this is the initial call */
    {
      /* #21 Job was spawned with high priority to get an accurate pre-hook indication.
       *   Reschedule job with (almost) lowest priority. */
      (void)vSwUpdM_QueuePrioUpdate(&vSwUpdM_JobQueue, ActiveJob->QueueHandle, (vSwUpdM_QueuePrioType)VSWUPDM_JOB_PRIO_SUSPEND_LOW);
      /* #22 Advance job state to wait for all other jobs (beside shutdown) to be suspended (or finished). */
      ActiveJob->State = VSWUPDM_JOB_STATE_FINAL;

#if (VSWUPDM_MULTICONTROLLER_SUPPORT == STD_ON)
      /* If Suspend is requested wait for remote responses. If Shutdown causes suspend, do not wait. */
      if (ActiveJob->ConfirmationService == VSWUPDM_SID_SUSPEND)
      {
        /* If local node is the parent: */
        if (vSwUpdM_Grid_LocalNodeIsParent() == TRUE)
        {
          ActiveJob->Result = vSwUpdM_RemoteService(
            VSWUPDM_GRIDSRVC_SERVICEIDX_SUSPEND,
            VSWUPDM_EXCTSCHEDULE_SERVICESTATE_RUN,
            vSwUpdM_GetBroadcastGroup(),
            ActiveJob);
        }
        else
        {
          /* If Suspend is called before Start has finished, the local node is not yet the the master but will be soon. */
          ActiveJob->State = VSWUPDM_JOB_STATE_PENDING;
        }
      }
#endif
      break;
    }
    case VSWUPDM_JOB_STATE_PENDING:
    {
#if (VSWUPDM_MULTICONTROLLER_SUPPORT == STD_ON)
      /* If Suspend is requested wait for remote responses. If Shutdown causes suspend, do not wait. */
      if (ActiveJob->ConfirmationService == VSWUPDM_SID_SUSPEND)
      {
        /* Check again for being the master. */
        if (vSwUpdM_GridSrvc_GetCommunicationState() == VSWUPDM_GRIDSRVC_GRIDSTATE_LOCKED)
        {
          ActiveJob->Result = vSwUpdM_RemoteService(
            VSWUPDM_GRIDSRVC_SERVICEIDX_SUSPEND,
            VSWUPDM_EXCTSCHEDULE_SERVICESTATE_RUN,
            vSwUpdM_GetBroadcastGroup(),
            ActiveJob);
        }
        ActiveJob->State = VSWUPDM_JOB_STATE_FINAL;
      }
#endif
      break;
    }
    case VSWUPDM_JOB_STATE_FINAL:
    /* #30 If waiting for all other jobs (beside shutdown) to be suspended (or finished) */
    {
      /* #31 Indicate that job is finished. */
      retVal = VSWUPDM_JOB_STATUS_FINISHED;
      break;
    }
    case VSWUPDM_JOB_STATE_FAILED:
    /* #500 If job state is "failed", because of negative child result
     *   Return with negative result taken over from child job. */
    {
      break;
    }
    default:
    /* #40 Otherwise: Invalid state.
     *   Set error in job result. */
    {
      ActiveJob->Result = VSWUPDM_E_INV_STATE;
      break;
    }
  }

  return retVal;
} /* vSwUpdM_JobHandler_Suspend */

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_Resume
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
 *
 */
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_Resume)
{
  vSwUpdM_JobStatusType retVal = VSWUPDM_JOB_STATUS_PENDING;

  /* #10 Evaluate child result from previous cycle. */
  (void)vSwUpdM_Job_EvaluateAndApplyChildResult(ActiveJob, FALSE);

  VSWUPDM_DUMMY_STATEMENTS_JOB_HANDLER(); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  /* #20 Evaluate job state. */
  switch (ActiveJob->State)
  {
    case VSWUPDM_JOB_STATE_INITIAL:
    /* #100 If initial operation shall be triggered */
    {
      ActiveJob->State = VSWUPDM_JOB_STATE_RESUME_ENQUEUE_JOBS;

      /* #110 If local node is the child:
       *      Wait for pending request resume call. */
      if (vSwUpdM_Grid_LocalNodeIsChild() == TRUE)
      {
        if (vSwUpdM_SrvcRouting_IsRequestResumePending() == TRUE)
        {
          ActiveJob->State = VSWUPDM_JOB_STATE_INITIAL;
        }
      }
      break;
    }
    case VSWUPDM_JOB_STATE_RESUME_ENQUEUE_JOBS:
    {
      /* #120 While suspended job queue isn't empty */
      while (!vSwUpdM_QueueIsEmpty(&vSwUpdM_SuspendedJobQueue))
      {
        vSwUpdM_QueueHandleType suspendedHandle;
        vSwUpdM_QueueHandleType jobHandle;
        P2CONST(vSwUpdM_QueueEntryType, AUTOMATIC, VSWUPDM_APPL_VAR) suspendedEntry;
        P2VAR(vSwUpdM_QueueEntryType, AUTOMATIC, VSWUPDM_APPL_VAR) jobEntry;

        /* #130 Re-append job to end of pending jobs queue.
         *   Restoring them in the same order as they where suspended. */
        suspendedHandle  = vSwUpdM_QueueGetFirstUsedHandle(&vSwUpdM_SuspendedJobQueue);
        suspendedEntry   = &vSwUpdM_QueueGetEntry(&vSwUpdM_SuspendedJobQueue, suspendedHandle);
        jobHandle        = vSwUpdM_QueueAppend(&vSwUpdM_JobQueue);
        jobEntry         = &vSwUpdM_QueueGetEntry(&vSwUpdM_JobQueue, jobHandle);

        /* #140 Restore the entity ID and priority of the previously suspended job. */
        jobEntry->entity = suspendedEntry->entity;
        jobEntry->prio   = suspendedEntry->prio;

        /* #150 Re-assign the job handle to the job object. */
        vSwUpdM_Jobs[jobEntry->entity].QueueHandle = jobHandle;

        /* #160 Remove the restored job from the suspended jobs queue. */
        (void)vSwUpdM_QueueRemove(&vSwUpdM_SuspendedJobQueue, suspendedHandle);
      }

#if (VSWUPDM_MULTICONTROLLER_SUPPORT == STD_OFF)
      ActiveJob->State = VSWUPDM_JOB_STATE_FINAL;
#else
      /* #170 Trigger RESUME requests for ongoing services. */
      ActiveJob->Result = vSwUpdM_ExecCtrl_TriggerRemoteResumeService();

      /* If local node is the parent: */
      if (vSwUpdM_Grid_LocalNodeIsParent() == TRUE)
      {
        ActiveJob->State = VSWUPDM_JOB_STATE_RESUME_REMOTE;
      }
      else
      {
        ActiveJob->State = VSWUPDM_JOB_STATE_FINAL;
      }
      break;
    }
    case VSWUPDM_JOB_STATE_RESUME_REMOTE:
    /* #200 Trigger remote resume. */
    {
      /* Trigger remote operation */
      ActiveJob->Result = vSwUpdM_RemoteService(
        VSWUPDM_GRIDSRVC_SERVICEIDX_RESUME,
        VSWUPDM_EXCTSCHEDULE_SERVICESTATE_RUN,
        vSwUpdM_GetBroadcastGroup(),
        ActiveJob);

      ActiveJob->State = VSWUPDM_JOB_STATE_SYNC_RESUME;
      break;
    }
    case VSWUPDM_JOB_STATE_SYNC_RESUME:
    {
      /* #300 Wait for pending request resume call. */
      if (vSwUpdM_SrvcRouting_IsRequestResumePending() == FALSE)
      {
        ActiveJob->State = VSWUPDM_JOB_STATE_FINAL;
      }
#endif
      break;
    }
    case VSWUPDM_JOB_STATE_FINAL:
    /* #400 If waiting for result of final operation
     *   Indicate that job is finished. */
    {
      retVal = VSWUPDM_JOB_STATUS_FINISHED;
      break;
    }
    case VSWUPDM_JOB_STATE_FAILED:
    /* #500 If job state is "failed", because of negative child result
     *   Return with negative result taken over from child job. */
    {
      break;
    }
    default:
    /* #600 Otherwise: Invalid state.
     *   Set error in job result. */
    {
      ActiveJob->Result = VSWUPDM_E_INV_STATE;
      break;
    }
  }

  return retVal;

  /* PRQA S 6030, 6050 1 */ /* MD_MSR_STCYC, MD_MSR_STCAL */
} /* vSwUpdM_JobHandler_Resume */

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_Start
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
 *
 *
 *
 */
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_Start)
{
  vSwUpdM_JobStatusType retVal = VSWUPDM_JOB_STATUS_PENDING;

  VSWUPDM_DUMMY_STATEMENTS_JOB_HANDLER(); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  /* #10 Evaluate child result from previous cycle.
   *     If not okay, apply child result (without taking over the address) and set job state to "failed". */
  if (vSwUpdM_Job_EvaluateChildResult(ActiveJob) != E_OK)
  {
    if ((ActiveState == VSWUPDM_STATE_SUSPENDING)
      && (ActiveJob->ChildResult.Result == VSWUPDM_E_SUSPENDED))
    {
      retVal = VSWUPDM_JOB_STATUS_SUSPENDED;

      ActiveJob->ChildResult.Pending = TRUE;
      ActiveJob->ChildResult.Valid = FALSE;
    }
    else
    {
      vSwUpdM_Job_ApplyChildResult(ActiveJob, FALSE);
      ActiveJob->State = VSWUPDM_JOB_STATE_FAILED;
    }
  }
  else
  {
    if (ActiveState == VSWUPDM_STATE_SUSPENDING)
    {
      retVal = VSWUPDM_JOB_STATUS_SUSPENDED;
    }
  }

  if (ActiveState != VSWUPDM_STATE_SUSPENDING)
  {
    /* #20 Evaluate job state. */
    switch (ActiveJob->State)
    {
      case VSWUPDM_JOB_STATE_INITIAL:
      /* #100 If state is INITIAL: */
      {
        retVal = VSWUPDM_JOB_STATUS_FINISHED;

        /* #110 If init state doesn't indicate a successful initialization: */
        if (vSwUpdM_InitState != VSWUPDM_INIT_STATE_INITIALIZED)
        {
          /* #111 Report error about failed initialization. */
          ActiveJob->Result = VSWUPDM_E_INIT_FAILED;
        }
#if (VSWUPDM_MULTICONTROLLER_SUPPORT == STD_ON)
        else
        {
          /* #120 Otherwise:
           * If this instance allowed to be a master: */
          if (ActiveJob->Source == (vSwUpdM_NodeIterType)vSwUpdM_GetLocalNode())
          {
            /* #121 Enter critical section to ensure exclusive access of job queue. */
            VSWUPDM_ENTER_CRITICAL_SECTION();

            /* #122 Spawn job to acquire the Lock. */
            (void)vSwUpdM_Job_Spawn(NULL_PTR, VSWUPDM_JOB_TYPE_REMOTE_LOCK, VSWUPDM_JOB_OPERATION_DEFAULT, ActiveJob->CurrentPrio + 1u,  VSWUPDM_SID_NONE, ActiveJob, ActiveJob->Source);
            ActiveJob->State = VSWUPDM_JOB_STATE_PENDING;
            retVal           = VSWUPDM_JOB_STATUS_PENDING;

            /* #123 Leave critical section to ensure exclusive access of job queue. */
            VSWUPDM_LEAVE_CRITICAL_SECTION();
          }
        }
#endif
        break;
      }
      case VSWUPDM_JOB_STATE_PENDING:
      /* #200 If state is PENDING: */
      {
#if (VSWUPDM_MULTICONTROLLER_SUPPORT == STD_ON)
        /* #210 If local node is the parent: */
        if (vSwUpdM_Grid_LocalNodeIsParent() == TRUE)
        {
          /* Local node has the lock (= is the parent). */

          /* #211 Trigger Start() of remote nodes. */
          ActiveJob->Result = vSwUpdM_RemoteService(
            VSWUPDM_GRIDSRVC_SERVICEIDX_START,
            VSWUPDM_EXCTSCHEDULE_SERVICESTATE_RUN,
            vSwUpdM_GetBroadcastGroup(),
            ActiveJob);

          if (ActiveJob->Result == E_OK)
          {
          /* #212 Store current request for eventual resume. */
            vSwUpdM_ExecCtrl_StoreRemoteResumeService(
              VSWUPDM_GRIDSRVC_SERVICEIDX_START,
              vSwUpdM_GetBroadcastGroup(),
              VSWUPDM_INVALID_NODE);
          }

          /* #213 Go to final state. */
          ActiveJob->State = VSWUPDM_JOB_STATE_FINAL;
        }
        else
#endif
        {
          /* #220 Otherwise:
           * Indicate that job is finished. */
          retVal = VSWUPDM_JOB_STATUS_FINISHED;
        }

        break;
      }
      case VSWUPDM_JOB_STATE_FINAL:
       /* #300 If state is FINAL:
        *      Indicate that job is finished. */
      {
        retVal = VSWUPDM_JOB_STATUS_FINISHED;
        break;
      }
      case VSWUPDM_JOB_STATE_FAILED:
      /* #400 If job state is "failed", because of negative child result
       *      Return with negative result taken over from child job. */
      {
        break;
      }
      default: /* PRQA S 2013 */ /* MD_MSR_EmptyClause */
      {
        break;
      }
    }
  }

  return retVal;
  /* PRQA S 6030, 6050 1 */ /* MD_MSR_STCYC, MD_MSR_STCAL */
} /* vSwUpdM_JobHandler_Start */

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_Shutdown
 *********************************************************************************************************************/
 /*!
 * Internal comment removed.
 *
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
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_Shutdown)
{
  vSwUpdM_JobStatusType           retVal           = VSWUPDM_JOB_STATUS_PENDING;
  boolean                         useOperationPort = FALSE;
  vSwUpdM_DataProcessesIterType   currentProcessId = 0u; /* PRQA S 2981 */ /* MD_vSwUpdM_Rule2.2_2981_2892_RedundantInitialization */

  VSWUPDM_DUMMY_STATEMENTS_JOB_HANDLER(); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  if (vSwUpdM_StreamData.PipeState == VSWUPDM_PIPE_STATE_PROCESSING)
  {
    currentProcessId = vSwUpdMConf_vSwUpdMDataProcess_StreamData;
    /* Configuration dependent handling of usage for StreamData. */
    useOperationPort = vSwUpdM_StreamData.RestartHandling;
  }
  else
  {
    if (vSwUpdM_ProcessData.PipeState == VSWUPDM_PIPE_STATE_PROCESSING)
    {
      currentProcessId = vSwUpdM_ProcessData.ProcessId;
      useOperationPort = TRUE;
    }
  }

  if (useOperationPort == TRUE)
  {
    if (vSwUpdM_Pipe_HasInternalEntryPoint(currentProcessId, vSwUpdMConf_vSwUpdMDataInputType_InputOperation) == FALSE)
    {
      useOperationPort = FALSE;
    }
  }

  /* #10 Evaluate child result from previous cycle. */
  (void)vSwUpdM_Job_EvaluateAndApplyChildResult(ActiveJob, FALSE);

  /* #20 Evaluate job state. */
  switch (ActiveJob->State)
  {
    case VSWUPDM_JOB_STATE_INITIAL:
    /* #100 If this is the initial call: */
    {
      ActiveJob->State = VSWUPDM_JOB_STATE_SHUTDOWN_REDUCE_PRIO;

#if (VSWUPDM_MULTICONTROLLER_SUPPORT == STD_ON)
      /* #110 If local node is the parent:
       *       Trigger closing of connection. */
      if (vSwUpdM_Grid_LocalNodeIsParent() == TRUE)
      {
        vSwUpdM_GridSrvc_Close(vSwUpdM_GetBroadcastGroup());
        ActiveJob->State = VSWUPDM_JOB_STATE_SHUTDOWN_GRID_WAIT;
      }
#endif

      /* #120 If operation shall be suspended, as indicated by job operation: */
      if (ActiveJob->Operation == VSWUPDM_JOB_OPERATION_SHUTDOWN_SUSPEND)
      {
        /* #121 Trigger suspending of all pending operations. */
        if (vSwUpdM_State_Suspend(VSWUPDM_SID_NONE, ActiveJob, ActiveJob->Source) != E_OK)
        {
          ActiveJob->Result = E_NOT_OK;
        }
      }

      /* #130 Job was spawned with high priority to get an accurate pre-hook indication.
       *   Reschedule job with lowest priority. */
      (void)vSwUpdM_QueuePrioUpdate(&vSwUpdM_JobQueue, ActiveJob->QueueHandle, (vSwUpdM_QueuePrioType)VSWUPDM_JOB_PRIO_SHUTDOWN_LOW);

      break;
    }
#if (VSWUPDM_MULTICONTROLLER_SUPPORT == STD_ON)
    case VSWUPDM_JOB_STATE_SHUTDOWN_GRID_WAIT:
    /* #200 Wait for connection to close. */
    {
      vSwUpdM_GridSrvc_GridStateType state = vSwUpdM_GridSrvc_GetCommunicationState();

      if (state == VSWUPDM_GRIDSRVC_GRIDSTATE_LOCKED)
      {
        ActiveJob->Result = E_NOT_OK;
      }
      else if (state == VSWUPDM_GRIDSRVC_GRIDSTATE_UNLOCKED)
      {
        ActiveJob->State = VSWUPDM_JOB_STATE_SHUTDOWN_REDUCE_PRIO;
      }
      else
      {
        /* Pending. */
      }
      break;
    }
#endif
    case VSWUPDM_JOB_STATE_SHUTDOWN_REDUCE_PRIO:
    {
      if (useOperationPort == TRUE)
      {
        /* #321 Advance job state to wait for all other jobs (beside shutdown) to be suspended (or finished). */
        ActiveJob->State = VSWUPDM_JOB_STATE_SHUTDOWN_PIPE_PREPARE;
      }
      else
      {
        ActiveJob->State = VSWUPDM_JOB_STATE_SHUTDOWN_CLEANUP;
      }

      break;
    }
    case VSWUPDM_JOB_STATE_SHUTDOWN_PIPE_PREPARE:
    /* #400 If shutdown of pending data processing shall be prepared: */
    {
      /* #410 Enter critical section to ensure exclusive access of state and job queue. */
      VSWUPDM_ENTER_CRITICAL_SECTION();

      /* #420 Leave suspended state and resume normal job operation.
       *   Necessary for execution of final clean-up operations */
      vSwUpdM_GlobalState = VSWUPDM_STATE_ACTIVE;

       /* #430 If processing of pipe is pending: */
      if ( (vSwUpdM_StreamData.PipeState == VSWUPDM_PIPE_STATE_PROCESSING)
        || (vSwUpdM_ProcessData.PipeState == VSWUPDM_PIPE_STATE_PROCESSING))
      {
        /* #431 Trigger shutdown of pipe by passing process operation. */
        ActiveJob->Result = vSwUpdM_Pipe_WriteProcessOperation(currentProcessId, vSwUpdMConf_vSwUpdMDataInputType_InputOperation, VSWUPDM_PROC_NODE_OPERATION_SHUTDOWN);

        if (ActiveJob->Result == E_OK)
        {
          vSwUpdM_QueueHandleType suspendedHandle;
          vSwUpdM_QueueHandleType jobHandle;
          P2CONST(vSwUpdM_QueueEntryType, AUTOMATIC, VSWUPDM_APPL_VAR) suspendedEntry;
          P2VAR(vSwUpdM_QueueEntryType, AUTOMATIC, VSWUPDM_APPL_VAR) jobEntry;

          suspendedHandle = vSwUpdM_QueueGetFirstUsedHandle(&vSwUpdM_SuspendedJobQueue);
          suspendedEntry = &vSwUpdM_QueueGetEntry(&vSwUpdM_SuspendedJobQueue, suspendedHandle);

          while (suspendedHandle != VSWUPDM_QUEUE_HANDLE_HEAD_USED)
          {
            /* #440 If a write data job (triggered by pipe) is in the suspended job queue:*/
            if (suspendedEntry->entity == (vSwUpdM_EntityHandleType)VSWUPDM_JOB_TYPE_WRITE_DATA)
            {
              /* #441 Re-add job to pending jobs queue. */
              jobHandle = vSwUpdM_QueuePrioInsert(&vSwUpdM_JobQueue, suspendedEntry->prio);
              jobEntry = &vSwUpdM_QueueGetEntry(&vSwUpdM_JobQueue, jobHandle);

              /* #442 Restore the entity ID and priority of the previously suspended job. */
              jobEntry->entity = suspendedEntry->entity;
              jobEntry->prio = suspendedEntry->prio;

              /* #443 Re-assign the job handle to the job object. */
              vSwUpdM_Jobs[jobEntry->entity].QueueHandle = jobHandle;

              break;
            }

            suspendedHandle = vSwUpdM_QueueGetEntry(&vSwUpdM_SuspendedJobQueue, suspendedHandle).next;
            suspendedEntry = &vSwUpdM_QueueGetEntry(&vSwUpdM_SuspendedJobQueue, suspendedHandle);
          }
        }

        /* #450 Forward job state to wait for successful shutdown of pipe. */
        ActiveJob->State = VSWUPDM_JOB_STATE_SHUTDOWN_PIPE_PROCESS;

      }
      else
      {
        /* #460 Otherwise: Forward job state to perform final clean-up actions. */

        ActiveJob->State = VSWUPDM_JOB_STATE_SHUTDOWN_CLEANUP;
      }

      /* #470 Leave critical section ensuring exclusive access of state and job queue. */
      VSWUPDM_LEAVE_CRITICAL_SECTION();

      break;
    }
    case VSWUPDM_JOB_STATE_SHUTDOWN_PIPE_PROCESS:
    /* #500 If waiting for successful shutdown of pipe: */
    {
      vStreamProc_ReturnType pipeResult;
      boolean setStateIdle = FALSE;

      /* #510 Process pipe to wait for shutdown acknowledge. */
      pipeResult = vStreamProc_Process(vSwUpdM_ProcessData.PipeId);

      /* #520 Evaluate pipe result */
      switch (pipeResult)
      {
        case VSTREAMPROC_OK:
        /* #530 If processing has come to an end: */
        {
          /* #531 Forward job state to perform final clean-up actions. */
          setStateIdle = TRUE;
          ActiveJob->State = VSWUPDM_JOB_STATE_SHUTDOWN_CLEANUP;

          break;
        }
        case VSTREAMPROC_PENDING:
        /* #540 If processing is ongoing: */
        {
          vSwUpdM_ProcNodeOperationType procOperation;

          /* #541 If shutdown operation is acknowledged: */
          while (vSwUpdM_Pipe_ReadProcessOperation(currentProcessId, vSwUpdMConf_vSwUpdMDataOutputType_OutputOperation, &procOperation) == E_OK)
          {
            if (procOperation == VSWUPDM_PROC_NODE_OPERATION_SHUTDOWN)
            {
              /* #542 Forward job state to perform final clean-up actions. */
              setStateIdle = TRUE;
              ActiveJob->State = VSWUPDM_JOB_STATE_SHUTDOWN_CLEANUP;
            }
          }

          break;
        }
        case VSTREAMPROC_INSUFFICIENT_INPUT:   /* Configuration issue shall never happen. */
        case VSTREAMPROC_INSUFFICIENT_OUTPUT:  /* Configuration issue shall never happen. */
        case VSTREAMPROC_FAILED:
        default:
        /* #550 Otherwise: Reset pipe state and report error. */
        {
          setStateIdle = TRUE;
          ActiveJob->Result = E_NOT_OK;
          break;
        }
      }

      if (setStateIdle == TRUE)
      {
        if (vSwUpdM_StreamData.PipeState == VSWUPDM_PIPE_STATE_PROCESSING)
        {
          vSwUpdM_StreamData.PipeState = VSWUPDM_PIPE_STATE_IDLE;
        }
        else if (vSwUpdM_ProcessData.PipeState == VSWUPDM_PIPE_STATE_PROCESSING)
        {
          vSwUpdM_ProcessData.PipeState = VSWUPDM_PIPE_STATE_IDLE;
        }
        else
        {
          ActiveJob->State = VSWUPDM_JOB_STATE_FAILED;
        }
      }

      break;
    }
    case VSWUPDM_JOB_STATE_SHUTDOWN_CLEANUP:
    /* #600 If final clean-up actions shall be performed: */
    {
      /* #610 Enter critical section to ensure exclusive access of state and job queue. */
      VSWUPDM_ENTER_CRITICAL_SECTION();

      /* #611 Leave suspended state and resume normal job operation.
       *   Necessary for execution of final clean-up operations. */
      vSwUpdM_GlobalState = VSWUPDM_STATE_ACTIVE;

      /* #620 Clear the suspended jobs queue. */
      while (!vSwUpdM_QueueIsEmpty(&vSwUpdM_SuspendedJobQueue))
      {
        (void)vSwUpdM_QueueRemove(&vSwUpdM_SuspendedJobQueue, vSwUpdM_QueueGetFirstUsedHandle(&vSwUpdM_SuspendedJobQueue));
      }

      /* #630 Leave critical section ensuring exclusive access of state and job queue. */
      VSWUPDM_LEAVE_CRITICAL_SECTION();

      /* #640 If segment is still opened: */
      if (vSwUpdM_EntityData.OpenIds.SegmentId.DynamicSegmentId != VSWUPDM_INVALID_ID)
      {
        /* #641 Trigger closing of segment. */
        (void)vSwUpdM_Segment_CloseSegment(vSwUpdM_EntityData.OpenIds.SegmentId, VSWUPDM_SID_NONE, ActiveJob, ActiveJob->Source);
      }
      else
      {
        retVal = VSWUPDM_JOB_STATUS_ACTIVE;
      }

      /* #650 Advance job state to close any opened module next. */
      ActiveJob->State = VSWUPDM_JOB_STATE_SHUTDOWN_CLOSE_MODULE;

      break;
    }
    case VSWUPDM_JOB_STATE_SHUTDOWN_CLOSE_MODULE:
    /* #700 If opened module shall be closed: */
    {
      /* #710 If segment is still opened: */
      if (vSwUpdM_EntityData.OpenIds.ModuleId != VSWUPDM_INVALID_ID)
      {
        /* #711 Trigger closing of module. */
        (void)vSwUpdM_Module_CloseModule(vSwUpdM_EntityData.OpenIds.ModuleId, VSWUPDM_SID_NONE, ActiveJob->Source, ActiveJob);
        /* #712 Trigger persisting of any modified segment states. */
        (void)vSwUpdM_Segment_PersistState(&vSwUpdM_EntityData.OpenIds, VSWUPDM_SID_NONE, TRUE, ActiveJob, ActiveJob->Source);
      }
      else
      {
        retVal = VSWUPDM_JOB_STATUS_ACTIVE;
      }

      /* #720 Advance job state to update resume information next. */
      ActiveJob->State = VSWUPDM_JOB_STATE_SHUTDOWN_UPDATE_RESUME_INFO;

      break;
    }
    case VSWUPDM_JOB_STATE_SHUTDOWN_UPDATE_RESUME_INFO:
    /* #800 If resume information shall be updated: */
    {
      /* #810 Trigger persisting of resume information. */
      if (ActiveJob->UpdateResumeInfo == TRUE)
      {
        (void)vSwUpdM_ResumeInfo_PersistState(ActiveJob->Source);
      }
      else
      {
        retVal = VSWUPDM_JOB_STATUS_ACTIVE;
      }

      /* #820 Forward job state to bookkeeper close. */
      ActiveJob->State = VSWUPDM_JOB_STATE_SHUTDOWN_BOOKKEEPER_CLOSE;

      break;
    }
    case VSWUPDM_JOB_STATE_SHUTDOWN_BOOKKEEPER_CLOSE:
    /* #900 Close bookkeeper connection (remote). */
    {
      if (vSwUpdM_GetNNodesOfNodeGroup(vSwUpdM_GetNodeGroupIdxOfAllPersistorServerGroupRemote(VSWUPDM_BKPERISTCLIENT_PERSISTSERVERGROUPREMOTEINDEX))> 0u)
      {
        /* #910 Enter critical section to ensure exclusive access of job queue. */
        VSWUPDM_ENTER_CRITICAL_SECTION();

        /* #920 Spawn job to close bookkeeper connection. */
        (void)vSwUpdM_Job_Spawn(NULL_PTR, VSWUPDM_JOB_TYPE_WAIT_FOR_BOOKKEEPER_OPERATION, VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_CLOSE, ActiveJob->CurrentPrio + 1u, VSWUPDM_SID_NONE, ActiveJob, ActiveJob->Source);

        /* #930 Leave critical section to ensure exclusive access of job queue. */
        VSWUPDM_LEAVE_CRITICAL_SECTION();
      }
      else
      {
        retVal = VSWUPDM_JOB_STATUS_ACTIVE;
      }

      ActiveJob->State = VSWUPDM_JOB_STATE_SHUTDOWN_BOOKKEEPER_CLOSE_LOCAL;

      break;
    }
    case VSWUPDM_JOB_STATE_SHUTDOWN_BOOKKEEPER_CLOSE_LOCAL:
    /* #1000 Close bookkeeper connection (local). */
    {
      if (vSwUpdM_GetNNodesOfNodeGroup(vSwUpdM_GetNodeGroupIdxOfAllPersistorServerGroupLocal(VSWUPDM_BKPERISTCLIENT_PERSISTSERVERGROUPREMOTEINDEX)) > 0u)
      {
        /* #1010 Enter critical section to ensure exclusive access of job queue. */
        VSWUPDM_ENTER_CRITICAL_SECTION();

        /* #1020 Spawn job to close bookkeeper connection. */
        (void)vSwUpdM_Job_Spawn(NULL_PTR, VSWUPDM_JOB_TYPE_WAIT_FOR_BOOKKEEPER_OPERATION, VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_CLOSE_LOCAL, ActiveJob->CurrentPrio + 1u, VSWUPDM_SID_NONE, ActiveJob, ActiveJob->Source);

        /* #1030 Leave critical section to ensure exclusive access of job queue. */
        VSWUPDM_LEAVE_CRITICAL_SECTION();
      }
      else
      {
        retVal = VSWUPDM_JOB_STATUS_ACTIVE;
      }

      /* #1040 Forward job state to finalize shutdown. */
      ActiveJob->State = VSWUPDM_JOB_STATE_FINAL;

      break;
    }
    case VSWUPDM_JOB_STATE_FINAL:
    /* #1100 If shutdown shall be finalized: */
    {
      /* #1110 Clear entity, stream data, data processing and pipelined programming. */
      vSwUpdM_Init_InitEntityData();
      vSwUpdM_Init_InitStreamData();
      vSwUpdM_Init_InitProcessData();
#if (VSWUPDM_PIPELINED_PROGRAMMING == STD_ON)
      vSwUpdM_Init_InitPipelinedProgramming();
#endif

#if (VSWUPDM_MULTICONTROLLER_SUPPORT == STD_ON)
      /* #1120 Release lock. */
      vSwUpdM_RemoteLockIsGrantedTo = VSWUPDM_INVALID_NODE;
#endif

      /* #1130 Update global state to "shut down pending". */
      vSwUpdM_GlobalState = VSWUPDM_STATE_SHUT_DOWN_PENDING;

      /* #1140 Indicate that job is finished. */
      retVal              = VSWUPDM_JOB_STATUS_FINISHED;

      break;
    }
    case VSWUPDM_JOB_STATE_FAILED:
    /* #1200 If job state is "failed", because of negative child result:
     *   Return with negative result taken over from child job. */
    {
      break;
    }
    default:
    /* #1300 Otherwise: Invalid state:
     *   Set error in job result. */
    {
      ActiveJob->Result = VSWUPDM_E_INV_STATE;
      break;
    }
  }

  return retVal;
  /* PRQA S 6010, 6030, 6050, 6080 1 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */
} /* vSwUpdM_JobHandler_Shutdown */

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_RemoteLock
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
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_RemoteLock)
{
  vSwUpdM_JobStatusType retVal = VSWUPDM_JOB_STATUS_PENDING; /* PRQA S 2981 */ /* MD_MSR_RetVal */

  VSWUPDM_DUMMY_STATEMENTS_JOB_HANDLER(); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */

  /* #10 Evaluate child result from previous cycle. */
  (void)vSwUpdM_Job_EvaluateAndApplyChildResult(ActiveJob, FALSE);

#if (VSWUPDM_MULTICONTROLLER_SUPPORT == STD_ON)
  /* #20 Evaluate job state. */
  switch(ActiveJob->State)
  {
    /* #100 If this is the initial call. */
    case VSWUPDM_JOB_STATE_INITIAL:
    {
      vSwUpdM_GridSrvc_Open(vSwUpdM_GetBroadcastGroup());
      ActiveJob->State = VSWUPDM_JOB_STATE_FINAL;
      break;
    }
    case VSWUPDM_JOB_STATE_FINAL:
    /* #200 Check for result. */
    {
      vSwUpdM_GridSrvc_GridStateType state = vSwUpdM_GridSrvc_GetCommunicationState();

      if (state == VSWUPDM_GRIDSRVC_GRIDSTATE_UNLOCKED)
      {
        ActiveJob->Result = E_NOT_OK;
      }
      else if (state == VSWUPDM_GRIDSRVC_GRIDSTATE_LOCKED)
      {
        /* #210 Current node now has the master role. */
        retVal = VSWUPDM_JOB_STATUS_FINISHED;
      }
      else
      {
        /* Pending. */
      }

      break;
    }
    /* #300 Something went wrong. Do nothing and propagate Result to parent job. */
    case VSWUPDM_JOB_STATE_FAILED:
    {
      break;
    }
    default:
    {
      ActiveJob->Result = VSWUPDM_E_INV_STATE;
      break;
    }
  }
#else
  retVal = VSWUPDM_JOB_STATUS_FINISHED;
#endif

  return retVal;
} /* vSwUpdM_JobHandler_RemoteLock */

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_RemoteGroupConfirmation
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
 */
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_RemoteGroupConfirmation) /* PRQA S 3673 */ /* MD_vSwUpdM_Rule8.13_3673_PointerToConstParameter */
{
  vSwUpdM_JobStatusType retVal;

#if (VSWUPDM_MULTICONTROLLER_SUPPORT == STD_ON)
  vSwUpdM_GridSrvc_ResponseClassSimpleResponsePtrType response = NULL_PTR;
#endif

  VSWUPDM_DUMMY_STATEMENTS_JOB_HANDLER(); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */

#if (VSWUPDM_MULTICONTROLLER_SUPPORT == STD_ON)

  /* #10 Get collected responses from child nodes. */
  if (vSwUpdM_GridSrvc_GetAggregatedResult(ActiveJob->RemoteServiceIndex, &response) == VSWUPDM_GRIDSRVC_AGGREGATERESULT_DONE)
  {
    /* #100 Evaluate aggregated Result: */
    switch (response->Result)
    {
      case E_OK:
      /* #110 Result is E_OK:
       *      Return positive result,
       *      Request is finished and wont be resumed. */
      {
        ActiveJob->Result = E_OK;
        if (ActiveJob->Type == VSWUPDM_JOB_TYPE_REMOTE_GROUP_CONFIRMATION)
        {
          vSwUpdM_ExecCtrl_ClearRemoteResumeService(ActiveJob->RemoteServiceIndex);
        }
        break;
      }
      case VSWUPDM_E_SUSPENDED:
      /* #120 Child has suspended request execution:
       *      To resume the request must be retransmitted (ServiceState=RESUME). This will restart this job.
       *      Hide SUSPENDED response from caller. */
      {
        vSwUpdM_DevError_Assert((vSwUpdM_ExecCtrl_RemoteResumeService.IsValid == TRUE), VSWUPDM_DEVERROR_ASSERT_49); /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */
        ActiveJob->Result = E_OK;
        break;
      }
      default:
      /* #130 Any error occured:
       *      Translate error code to show that it is occured remote.
       *      Request is finished and wont be resumed. */
      {
        ActiveJob->Result = vSwUpdM_TranslateErrorCode(ActiveJob->RemoteServiceIndex, response->Result);
        if (ActiveJob->Type == VSWUPDM_JOB_TYPE_REMOTE_GROUP_CONFIRMATION)
        {
          vSwUpdM_ExecCtrl_ClearRemoteResumeService(ActiveJob->RemoteServiceIndex);
        }
        break;
      }
    }

    retVal = VSWUPDM_JOB_STATUS_FINISHED;
    vSwUpdM_GridSrvc_Finish(ActiveJob->RemoteServiceIndex);
  }
  else
  {
    retVal = VSWUPDM_JOB_STATUS_PENDING;
  }

#else
  retVal = VSWUPDM_JOB_STATUS_FINISHED;
#endif
  return retVal;
} /* vSwUpdM_JobHandler_RemoteGroupConfirmation */

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_RemoteTargetConfirmation
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
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_RemoteTargetConfirmation) /* PRQA S 3673 */ /* MD_vSwUpdM_Rule8.13_3673_PointerToConstParameter */
{
  vSwUpdM_JobStatusType retVal = VSWUPDM_JOB_STATUS_PENDING; /* PRQA S 2981 */ /* MD_MSR_RetVal */

  VSWUPDM_DUMMY_STATEMENTS_JOB_HANDLER(); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */

#if (VSWUPDM_MULTICONTROLLER_SUPPORT == STD_ON)
    /* #10 Evaluate child result from previous cycle.
   *   If not okay, apply child result (without taking over the address) and set job state to "failed". */

  ActiveJob->Result = E_OK;

  /* #10 If no response is expected from this target,
          return error. */
  if (!vSwUpdM_IsResponseProcessingOfVarNode(ActiveJob->RemoteTarget))
  {
    ActiveJob->Result = VSWUPDM_E_REMOTE_SERVICE_TARGET_NOT_PROCESSING;
  }
  /* #20 If response is received and Service Id match the expectations,
          return result value from response. */
  if (vSwUpdM_IsResponseValidOfVarNode(ActiveJob->RemoteTarget))
  {
    if ((vSwUpdM_GridSrvc_ServiceIdxType) vSwUpdM_GetServiceIdOfResponseOfVarNode(ActiveJob->RemoteTarget) == ActiveJob->RemoteServiceIndex) /* PRQA S 4342 */ /* MD_vSwUpdM_Rule10.5_4342_EnumParameterCast */
    {
      ActiveJob->Result = vSwUpdM_GetResultOfResponseOfVarNode(ActiveJob->RemoteTarget);

      if (ActiveJob->Result != VSWUPDM_E_SUSPENDED)
      {
        switch (ActiveJob->RemoteServiceIndex)
        {
          /* Non-resumable services: */
          case VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_PERSIST_MODULE_STATE:
          case VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_PERSIST_MODULE_VALID:
          case VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_PERSIST_MODULE_PROGRAMMING_ATTEMPTS:
          case VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_PERSIST_REGION_STATE:
          case VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_PERSIST_REGION_PROGRAMMING_ATTEMPTS:
          case VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_PERSIST_SEGMENT_ATTRIBUTES:
          case VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_PERSIST_RESUME_INFO:
          case VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_COPY_STREAM_DATA:
          case VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_CONCLUDE_SEGMENT:
          {
            break;
          }
          default:
          {
            vSwUpdM_ExecCtrl_ClearRemoteResumeService(ActiveJob->RemoteServiceIndex);
            break;
          }
        }
      }
    }
    else
    {
      /* #30 If wrong Service Id is received,
      return error. */
      ActiveJob->Result = VSWUPDM_E_REMOTE_RESPONSE_WRONG_SERVICE;
    }

    /* #40 If response is "SUSPENDED" suspend this job.
            It will be continued after a Resume. */
    if (ActiveJob->Result == VSWUPDM_E_SUSPENDED)
    {
      if (ActiveState == VSWUPDM_STATE_SUSPENDING)
      {
        retVal = VSWUPDM_JOB_STATUS_SUSPENDED;
        ActiveJob->Result = E_OK;
        vSwUpdM_SetResponseValidOfVarNode(ActiveJob->RemoteTarget, FALSE);
      }
      else
      {
        ActiveJob->Result = VSWUPDM_E_INV_STATE;
      }
    }
    else
    {
      retVal = VSWUPDM_JOB_STATUS_FINISHED;
    }
  }
  else
  {
    /* Target has not yet responded */
  }
#else
  retVal = VSWUPDM_JOB_STATUS_FINISHED;
#endif
  return retVal;

 /* PRQA S 6030, 6080 1 */ /* MD_MSR_STCYC, MD_MSR_STMIF */
} /* vSwUpdM_JobHandler_RemoteTargetConfirmation */

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_ServiceDispatcher
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
 */
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_ServiceDispatcher)
{
  vSwUpdM_JobStatusType retVal = VSWUPDM_JOB_STATUS_PENDING; /* PRQA S 2981 */ /* MD_MSR_RetVal */

  VSWUPDM_DUMMY_STATEMENTS_JOB_HANDLER(); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */

  /*  #10 Evaluate child result from previous cycle.
   *   If not okay, apply child result.
   *   If result is SUSPENDED suspend job.
   */
  retVal = vSwUpdM_Job_EvaluateChildResultOrSuspend(ActiveState, ActiveJob, FALSE);

  if (ActiveState != VSWUPDM_STATE_SUSPENDING)
  {
    switch (ActiveJob->State)
    {
      case VSWUPDM_JOB_STATE_INITIAL:
      /* #100 If initial operation shall be triggered */
      {
        vSwUpdM_DevError_Assert(((uint32_least)ActiveJob->SequenceIdx < VSWUPDM_ARRAY_SIZE(vSwUpdM_ExecCtrl_SequencesList)), VSWUPDM_DEVERROR_ASSERT_58); /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */

        ActiveJob->Count = 0u;
        ActiveJob->State = VSWUPDM_JOB_STATE_PENDING;
        retVal = VSWUPDM_JOB_STATUS_ACTIVE;
        break;
      }
      case VSWUPDM_JOB_STATE_PENDING:
      {
        vSwUpdM_ExecCtrl_SequencesListConstType * seq = &vSwUpdM_ExecCtrl_SequencesList[ActiveJob->SequenceIdx];

        if (ActiveJob->Count >= seq->SequenceSize)
        {
          ActiveJob->State = VSWUPDM_JOB_STATE_FINAL;
        }
        else
        {
          vSwUpdM_ExecCtrl_SequenceEntryConstPtrType entry = &seq->Sequence[ActiveJob->Count];

          /* Do not execute Multi-node functionality in non-Multi-node configuration. */
#if (VSWUPDM_MULTICONTROLLER_SUPPORT == STD_ON)
          boolean exec = TRUE;

          if ((entry->Flags & VSWUPDM_EXECCTRL_SEQUENCEFLAG_MULTINODE) == VSWUPDM_EXECCTRL_SEQUENCEFLAG_MULTINODE)
          {
            if (vSwUpdM_Grid_LocalNodeIsParent() != TRUE)
            {
              /* Local node is leaf, has no children. "Parent" behavior must be omited. */
              exec = FALSE;
              retVal = VSWUPDM_JOB_STATUS_ACTIVE;
            }
          }

          if (exec == TRUE)
#else
          if ((entry->Flags & VSWUPDM_EXECCTRL_SEQUENCEFLAG_MULTINODE) != VSWUPDM_EXECCTRL_SEQUENCEFLAG_MULTINODE)
#endif
          {
            if ((entry->Flags & VSWUPDM_EXECCTRL_SEQUENCEFLAG_SPAWNJOB) == VSWUPDM_EXECCTRL_SEQUENCEFLAG_SPAWNJOB)
            {
              vSwUpdM_JobPtrType spawnedJob;

              vSwUpdM_DevError_Assert((entry->Job != VSWUPDM_JOB_TYPE_INVALID), VSWUPDM_DEVERROR_ASSERT_60); /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */

              /* #110 Enter critical section to ensure exclusive access of state and job queue. */
              VSWUPDM_ENTER_CRITICAL_SECTION();

              /* #120 Spawn job. */
              spawnedJob = vSwUpdM_Job_Spawn(&ActiveJob->Result, entry->Job, ActiveJob->Operation, (vSwUpdM_QueuePrioType)VSWUPDM_JOB_PRIO_DEFAULT, VSWUPDM_SID_NONE, ActiveJob, ActiveJob->Source);

              /* #130 Job attributes are safe to be modified when job was successfully spawned and access is still protected by critical section. */
              if (ActiveJob->Result == E_OK)
              {
                spawnedJob->EntityIds = ActiveJob->EntityIds;
                spawnedJob->RemoteServiceIndex = ActiveJob->RemoteServiceIndex;
                spawnedJob->RemoteTarget = ActiveJob->RemoteTarget;
                spawnedJob->RemoteTargetGroup = ActiveJob->RemoteTargetGroup;
                spawnedJob->UpdateResumeInfo = ActiveJob->UpdateResumeInfo;
              }

              /* #140 Leave critical section ensuring exclusive access of state and job queue. */
              VSWUPDM_LEAVE_CRITICAL_SECTION();

              retVal = VSWUPDM_JOB_STATUS_PENDING;
            }

            if ((entry->Flags & VSWUPDM_EXECCTRL_SEQUENCEFLAG_CALLFUNCTION) == VSWUPDM_EXECCTRL_SEQUENCEFLAG_CALLFUNCTION)
            {
              vSwUpdM_DevError_Assert((entry->Fn != NULL_PTR), VSWUPDM_DEVERROR_ASSERT_59); /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */

              ActiveJob->Result = entry->Fn(ActiveJob);

              retVal = VSWUPDM_JOB_STATUS_PENDING;
            }
          }
        }

        ActiveJob->Count++;
        break;
      }
      case VSWUPDM_JOB_STATE_FINAL:
      {
#if (VSWUPDM_MULTICONTROLLER_SUPPORT == STD_ON)
        /* #210 Cleanup remote streams. */
        vSwUpdM_Init_RemoteStream();
#endif

        retVal = VSWUPDM_JOB_STATUS_FINISHED;
        break;
      }
      default:
      /* case VSWUPDM_JOB_STATE_FAILED: */
      {
        break;
      }
    }
  }

  return retVal;
  /* PRQA S 6010, 6030, 6080 1 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCYC */
} /* vSwUpdM_JobHandler_ServiceDispatcher */

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_EraseRegionLocalWork
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
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_EraseRegionLocalWork)
{
  vSwUpdM_JobStatusType retVal = VSWUPDM_JOB_STATUS_PENDING;

  VSWUPDM_DUMMY_STATEMENTS_JOB_HANDLER(); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */

  /* #10 Evaluate child result from previous cycle. */
  (void)vSwUpdM_Job_EvaluateAndApplyChildResult(ActiveJob, FALSE);

  /* #20 If suspend of operation is requested
   *   Indicate that job is suspended. */
  if (ActiveState == VSWUPDM_STATE_SUSPENDING)
  {
    retVal = VSWUPDM_JOB_STATUS_SUSPENDED;
  }
  /* #30 Otherwise: Evaluate job State: */
  else
  {
    switch(ActiveJob->State)
    {
      case VSWUPDM_JOB_STATE_INITIAL:
      /* #100 If this is the initial call. */
      {
        vSwUpdM_RegionIdType  regionId     = ActiveJob->EntityIds.RegionId;
        vSwUpdM_AddressType   startAddress = vSwUpdM_GetStartAddressOfRegion(regionId);

        vSwUpdM_ResumeInfo_InitState(&ActiveJob->EntityIds, VSWUPDM_SID_ERASE_REGION, startAddress, TRUE);

#if (VSWUPDM_MULTICONTROLLER_SUPPORT == STD_ON)
        /* #110 If the region is local, */
        if (vSwUpdM_IsWithLocalNodeOfNodeGroup(vSwUpdM_GetNodeGroupOwnersIdxOfRegion(regionId)))
#endif
        {
          /* #120 Trigger erasing of given region. */
          ActiveJob->Result = vSwUpdM_Region_EraseRegion(&ActiveJob->EntityIds, TRUE, VSWUPDM_JOB_OPERATION_ERASE_REGION_UPDATE_MODULE_STATE, ActiveJob->Source, ActiveJob);
        }

        /* #130 If spawning of job failed
          *  Reset resume information. */
        if (ActiveJob->Result != E_OK)
        {
          vSwUpdM_ResumeInfo_ResetState();
        }

        ActiveJob->State = VSWUPDM_JOB_STATE_FINAL;
        break;
      }
      case VSWUPDM_JOB_STATE_FAILED:
      /* #200 In case a child job has reported an error, finish this job. */
      {
        break;
      }
      case VSWUPDM_JOB_STATE_FINAL:
      /* #300 In case all children are finished, finish this job. */
      {
        retVal = VSWUPDM_JOB_STATUS_FINISHED;
        break;
      }
      default: /* PRQA S 2013 */ /* MD_MSR_EmptyClause */
      {
        break;
      }
    }
  }

  return retVal;
} /* vSwUpdM_JobHandler_EraseRegionLocalWork */

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_RemoteAddSegments
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
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_RemoteAddSegments)
{
  vSwUpdM_JobStatusType retVal = VSWUPDM_JOB_STATUS_PENDING;

  VSWUPDM_DUMMY_STATEMENTS_JOB_HANDLER(); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */

  /* #10 Evaluate child result from previous cycle. */
  (void)vSwUpdM_Job_EvaluateAndApplyChildResult(ActiveJob, FALSE);

  /* #20 If suspend of operation is requested
   *   Indicate that job is suspended. */
  if (ActiveState == VSWUPDM_STATE_SUSPENDING)
  {
    retVal = VSWUPDM_JOB_STATUS_SUSPENDED;
  }
  /* #30 Otherwise */
  else
  {
    switch(ActiveJob->State)
    {
      case VSWUPDM_JOB_STATE_INITIAL:
      {
#if (VSWUPDM_MULTICONTROLLER_SUPPORT == STD_ON)
        /* #40 If the local node is the parent and a module is opened:
               Trigger remote operation. */
        if ( (vSwUpdM_Grid_LocalNodeIsParent() == TRUE)
          && (vSwUpdM_EntityData.OpenIds.ModuleId != VSWUPDM_INVALID_ID) )
        {
          ActiveJob->State = VSWUPDM_JOB_STATE_PENDING;
          /* Use TargetAddress as temporary buffer for segmentId */
          ActiveJob->TargetAddress = ActiveJob->EntityIds.SegmentId.DynamicSegmentId;
          ActiveJob->EntityIds.SegmentId.DynamicSegmentId = 0u;
        }
        else
#endif
        {
          /* Nothing to do here: Finish job */
          retVal = VSWUPDM_JOB_STATUS_FINISHED;
        }
        break;
      }
      case VSWUPDM_JOB_STATE_PENDING:
      {
#if (VSWUPDM_MULTICONTROLLER_SUPPORT == STD_ON)
        /* #100 Iterate over all segments until a segment with RemoteDirty == TRUE is found. */
        while(vSwUpdM_GetVarSegments(ActiveJob->EntityIds.SegmentId.DynamicSegmentId).RemoteDirty == FALSE)
        {
          if (ActiveJob->EntityIds.SegmentId.DynamicSegmentId == vSwUpdM_EntityData.Count.InternalSegmentCount)
          {
            break;
          }
          ActiveJob->EntityIds.SegmentId.DynamicSegmentId++;
        }
        /* #110 If a RemoteDirty segment is found, trigger remote service to add segment on slave. */
        if (ActiveJob->EntityIds.SegmentId.DynamicSegmentId < vSwUpdM_EntityData.Count.InternalSegmentCount)
        {
          vSwUpdM_VarSegmentsPtrType segment = vSwUpdM_GetAddrVarSegments(ActiveJob->EntityIds.SegmentId.DynamicSegmentId);

          ActiveJob->Result = vSwUpdM_RemoteService(
            VSWUPDM_GRIDSRVC_SERVICEIDX_ADD_SEGMENT,
            VSWUPDM_EXCTSCHEDULE_SERVICESTATE_RUN,
            ActiveJob->RemoteTargetGroup,
            ActiveJob);

          if (ActiveJob->Result == E_OK)
          {
            /* #120 Store current request for eventual resume. */
            vSwUpdM_ExecCtrl_StoreRemoteResumeService(
              VSWUPDM_GRIDSRVC_SERVICEIDX_ADD_SEGMENT,
              ActiveJob->RemoteTargetGroup,
              VSWUPDM_INVALID_NODE);
          }

          /* #130 Segment is not RemoteDirty any more. */
          if(E_OK == ActiveJob->Result)
          {
            segment->RemoteDirty = FALSE;
            break;
          }
        }
        else
        {
          /* #140 No RemoteDirty segments left, finish job. */
          retVal = VSWUPDM_JOB_STATUS_FINISHED;
        }
#endif
        break;
      }
      case VSWUPDM_JOB_STATE_FAILED:
      {
        break;
      }
      default: /* PRQA S 2013 */ /* MD_MSR_EmptyClause */
      {
        break;
      }
    }
  }

  return retVal;
  /* PRQA S 6010, 6030 1 */ /* MD_MSR_STPTH, MD_MSR_STCYC */
} /* vSwUpdM_JobHandler_RemoteAddSegments */

/**********************************************************************************************************************
 *  vSwUpdM_JobHandler_ClearSegmentsOfModule
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
 */
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_ClearSegmentsOfModule)
{
  vSwUpdM_JobStatusType retVal = VSWUPDM_JOB_STATUS_PENDING;

  VSWUPDM_DUMMY_STATEMENTS_JOB_HANDLER(); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */

  /* #10 Evaluate child result from previous cycle. */
  (void)vSwUpdM_Job_EvaluateAndApplyChildResult(ActiveJob, FALSE);

  /* #20 If suspend of operation is requested
   *   Indicate that job is suspended. */
  if (ActiveState == VSWUPDM_STATE_SUSPENDING)
  {
    retVal = VSWUPDM_JOB_STATUS_SUSPENDED;
  }
  /* #30 Otherwise */
  else
  {
    switch(ActiveJob->State)
    {
      case VSWUPDM_JOB_STATE_INITIAL:
      {
        /* #100 Trigger clearing of segments of given module by re-initializing segments without restoring persisted values. */
        ActiveJob->Result = vSwUpdM_Module_InitSegments(VSWUPDM_RESTORE_SEGMENTS_NONE, TRUE, VSWUPDM_SID_NONE, ActiveJob, ActiveJob->Source);

        ActiveJob->State = VSWUPDM_JOB_STATE_FINAL;
        break;
      }
      case VSWUPDM_JOB_STATE_FAILED:
      {
        break;
      }
      case VSWUPDM_JOB_STATE_FINAL:
      {
        retVal = VSWUPDM_JOB_STATUS_FINISHED;
        break;
      }
      default: /* PRQA S 2013 */ /* MD_MSR_EmptyClause */
      {
        break;
      }
    }
  }

  return retVal;
} /* vSwUpdM_JobHandler_ClearSegmentsOfModule */

/***********************************************************************************************************************
 *  vSwUpdM_JobHandler_IndicateWriteToModule
 **********************************************************************************************************************/
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
VSWUPDM_JOB_HANDLER(vSwUpdM_JobHandler_IndicateWriteToModule)
{
  vSwUpdM_JobStatusType retVal = VSWUPDM_JOB_STATUS_PENDING;

  VSWUPDM_DUMMY_STATEMENTS_JOB_HANDLER(); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  /* #10 Evaluate child result from previous cycle.
   *   If not okay, apply child result (not taking over the address) and set job state to "failed". */
  if (vSwUpdM_Job_EvaluateChildResult(ActiveJob) != E_OK)
  {
    vSwUpdM_Job_ApplyChildResult(ActiveJob, FALSE);
    ActiveJob->State = VSWUPDM_JOB_STATE_FAILED;
  }

  /* #20 Evaluate job state. */
  switch (ActiveJob->State)
  {
    case VSWUPDM_JOB_STATE_INITIAL:
    /* #100 If initial conditions for first actual phase shall be established */
    {
      /* #110 Start with updating state attributes of first region, using relative index of region in requested module. */
      ActiveJob->EntityIds.RegionIdx = 0u;

      /* #140 Advance job state to update state of the first region. */
      ActiveJob->State = VSWUPDM_JOB_STATE_PENDING;
      retVal = VSWUPDM_JOB_STATUS_ACTIVE;

      break;
    }
    case VSWUPDM_JOB_STATE_PENDING:
    /* #200 If operation is in progress */
    {
      /* #210 If this isn't the last region of the requested module */
      if (ActiveJob->EntityIds.RegionIdx < vSwUpdM_GetNRegionsOfModule(ActiveJob->EntityIds.ModuleId))
      {
        /* #220 Evaluate state of region in which the current segment is located. */
        switch (vSwUpdM_GetVarRegions(ActiveJob->EntityIds.RegionIdx).DynamicAttributesOfVarRegion.State)
        {
          case VSWUPDM_REGION_STATE_ERASED:
          /* #221 If state is "erased": Change state of region to "clean". */
          {
            (void)vSwUpdM_Region_UpdateAndPersistState(ActiveJob->EntityIds.PartitionId, ActiveJob->EntityIds.ModuleId,
              ActiveJob->EntityIds.RegionIdx, VSWUPDM_REGION_STATE_CLEAN, ActiveJob, ActiveJob->Source);

            break;
          }
          case VSWUPDM_REGION_STATE_CLEAN:
          /* #222 If state is "clean": Nothing to be done. */
          {
            retVal = VSWUPDM_JOB_STATUS_ACTIVE;

            break;
          }
          default:
          /* #223 Otherwise: Invalid state, report error. */
          {
            ActiveJob->Result = E_NOT_OK;

            break;
          }
        }

        /* #230 Handle the next region of the module. */
        ActiveJob->EntityIds.RegionIdx++;
      }
      /* #240 Otherwise: All regions of requested module handled. */
      else
      {
        /* #250 Change state of module to "clean". */
        (void)vSwUpdM_Module_UpdateAndPersistState(ActiveJob->EntityIds.PartitionId, ActiveJob->EntityIds.PartitionState,
          ActiveJob->EntityIds.ModuleId, VSWUPDM_MODULE_STATE_CLEAN, ActiveJob, ActiveJob->Source);

        /* #260 Advance job state to close module. */
        ActiveJob->State = VSWUPDM_JOB_STATE_FINAL;
      }

      break;
    }
    case VSWUPDM_JOB_STATE_FINAL:
    case VSWUPDM_JOB_STATE_FAILED:
    /* #400 If job state is "failed", because of negative child result or if job is passed successfully */
    {
      /* #410 Indicate that job is finished. */
      retVal = VSWUPDM_JOB_STATUS_FINISHED;

      break;
    }
    default:
    /* #500 Otherwise: Invalid state.
     *   Set error in job result. */
    {
      ActiveJob->Result = VSWUPDM_E_INV_STATE;
      break;
    }
  }

  return retVal;
  /* PRQA S 6030 1 */ /* MD_MSR_STCYC */
} /* vSwUpdM_JobHandler_IndicateWriteToModule */

/**********************************************************************************************************************
 *  vSwUpdM_MainFunction
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
 *
 *
 *
 *
 *
 *
 */
FUNC(void, VSWUPDM_CODE) vSwUpdM_MainFunction(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  vSwUpdM_ErrorCode errorId = VSWUPDM_E_NO_ERROR;

  /* ----- Development Error Checks --------------------------------------- */
#if (VSWUPDM_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check that component is initialized or initialization is pending. */
  if (((vSwUpdM_InitState == VSWUPDM_INIT_STATE_UNINIT) || (vSwUpdM_InitState == VSWUPDM_INIT_STATE_PENDING))
    && (vSwUpdM_GlobalState == VSWUPDM_STATE_IDLE))
  {
    errorId = VSWUPDM_E_NOT_INITIALIZED;
  }
  /* #-- Otherwise: */
  else
#endif
  /* ----- Implementation ------------------------------------------------- */
  {
    vSwUpdM_StateType activeState;

    /* #100 Enter critical section to ensure exclusive access of state and active job (first queue entry). */
    VSWUPDM_ENTER_CRITICAL_SECTION();

    /* #110 If no job is pending */
    if (vSwUpdM_QueueIsEmpty(&vSwUpdM_JobQueue))
    {
      /* #120 Update global operation state. */
      switch (vSwUpdM_GlobalState)
      {
        case VSWUPDM_STATE_SUSPENDED:
        case VSWUPDM_STATE_SHUT_DOWN:
        /* #130 If operation is suspended or shut down
         *   Do not alter operation state */
        {
          break;
        }
        default:
        /* #140 Otherwise
         *   Fall back to idle operation state. */
        {
          vSwUpdM_GlobalState = VSWUPDM_STATE_IDLE;
          break;
        }
      }
    }

    /* #200 Update global state: */
    switch (vSwUpdM_GlobalState)
    {
      case (VSWUPDM_STATE_PENDING):
      /* #210 If operation is pending
       *   Switch to active state. */
      {
        vSwUpdM_GlobalState = VSWUPDM_STATE_ACTIVE;
        break;
      }
      case (VSWUPDM_STATE_SUSPEND_PENDING):
      /* #220 If suspend of operation is requested
       *   Switch to suspending state. */
      {
        vSwUpdM_GlobalState = VSWUPDM_STATE_SUSPENDING;
        break;
      }
      default:
      /* #230 Otherwise
       *   State remains unchanged. */
      {
        break;
      }
    }

    /* #300 Copy current state to evaluate below, without the need to include the complete processing in the critical section. */
    activeState = vSwUpdM_GlobalState;

    /* #310 Leave critical section ensuring exclusive access of state and active job (first queue entry). */
    VSWUPDM_LEAVE_CRITICAL_SECTION();

    /* #400 Schedule Bookkeeper Server. */
    vSwUpdM_Bookkeeper_ServerExecute();

    /* #410 Trigger (Pending) Responses. */
    vSwUpdM_SrvcRouting_HandleRxChannels();

    /* #500 Evaluate local copy of operation state. */
    switch (activeState)
    {
      case VSWUPDM_STATE_ACTIVE:
      case VSWUPDM_STATE_SUSPENDING:
      case VSWUPDM_STATE_SHUT_DOWN_PENDING:
      /* #510 If operation shall be carried out (either active, suspending or shutdown pending) */
      {
        /* #520 Execute the active job. */
        vSwUpdM_General_ExecuteActiveJob(activeState);

        break;
      }
      case VSWUPDM_STATE_IDLE:
      case VSWUPDM_STATE_SUSPENDED:
      default:
      /* #530 Otherwise, state is idle or suspended
       *   Nothing to be done. */
      {
        break;
      }
    }
  }

  /* ----- Development Error Report --------------------------------------- */
  vSwUpdM_General_HandleDetError(VSWUPDM_SID_MAIN_FUNCTION, errorId);
} /* vSwUpdM_MainFunction */

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
 *  END OF FILE: vSwUpdM_ExecCtrl.c
 *********************************************************************************************************************/
