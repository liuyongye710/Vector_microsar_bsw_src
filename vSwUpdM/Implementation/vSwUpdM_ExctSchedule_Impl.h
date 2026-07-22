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
/*!        \file  vSwUpdM_ExctSchedule_Impl.h
 *        \brief  vSwUpdM_ExctSchedule implementation header file
 *      \details  vSwUpdM_ExctSchedule subcomponent public inline implementations.
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

#if !defined (VSWUPDM_EXCTSCHEDULE_IMPL_H)
# define VSWUPDM_EXCTSCHEDULE_IMPL_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
/* ExctSchedule interface header */
#include "vSwUpdM_ExctSchedule_If.h"

/* Implementation header of containing MultipleUnit */
#include "vSwUpdM_ExecCtrl_Impl.h"

/* Other MultipleUnits used by ExctSchedule_Impl (Prefer smallest set required, i.e. prefer _Types over _If over _Impl) */
#include "vSwUpdM_Priv.h"
#include "vSwUpdM_Queue.h"

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
 * vSwUpdM_General_ConcludeJobProcessing
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
 */
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_General_ConcludeJobProcessing( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_JobPtrType ActiveJob,
  vSwUpdM_StateType ActiveState,
  vSwUpdM_JobStatusType JobStatus,
  vSwUpdM_JobPhaseType JobPhase,
  Std_ReturnType Result)
{
  Std_ReturnType           result              = Result;
  vSwUpdM_JobPhaseType     jobPhase            = JobPhase;
  vSwUpdM_ServiceIdType    confirmationService = VSWUPDM_SID_NONE;
  vSwUpdM_NodeIterType source              = VSWUPDM_INVALID_NODE;

  /* #10 Enter critical section to ensure exclusive access during (potential) queue removal and state change. */
  VSWUPDM_ENTER_CRITICAL_SECTION();

  /* #20 Evaluate status returned by job. */
  switch (JobStatus)
  {
    case VSWUPDM_JOB_STATUS_FINISHED:
    /* #100 If job finished */
    {
      /* #110 Determine job phase to be executed on next cycle, based on current job phase */
      switch (jobPhase)
      {
        case VSWUPDM_JOB_PHASE_PRE_HOOK:
        /* #120 If pre-hook was executed */
        {
          /* #121 If default hook action was returned */
          if (ActiveJob->HookAction == VSWUPDM_HOOK_ACTION_DEFAULT)
          {
            /* #122 Continue with job main handler. */
            jobPhase = VSWUPDM_JOB_PHASE_MAIN_HANDLER;
          }
          else
          {
            /* #123 Evaluate result of pre-hook execution. */
            jobPhase = VSWUPDM_JOB_PHASE_EVAL_PRE_HOOK;
          }

          break;
        }
        case VSWUPDM_JOB_PHASE_EVAL_PRE_HOOK:
        /* #130 If result of pre-hook was evaluated */
        {
          /* #131 Default: Finish current job. */
          jobPhase = VSWUPDM_JOB_PHASE_FINISH;

          switch (ActiveJob->HookAction)
          {
            case VSWUPDM_HOOK_ACTION_RETRY:
            case VSWUPDM_HOOK_ACTION_RESTART:
            /* #132 If retry was requested, increment retry counter and re-issue pre-hook execution. */
            {
              if (result == E_OK)
              {
                ActiveJob->RetryCount++;
                jobPhase = VSWUPDM_JOB_PHASE_PRE_HOOK;
              }

              break;
            }
            default:
            /* #133 Otherwise: Finish job. */
            {
              break;
            }
          }

          break;
        }
        case VSWUPDM_JOB_PHASE_MAIN_HANDLER:
        /* #140 If main handler was executed */
        {
          if (ActiveJob->ChildResult.Valid == TRUE)
          {
            /* #141 If child result is present and wasn't evaluated
             *   Report error. */
            result = VSWUPDM_E_JOB_CHILD_RESULT_NOT_EVALUATED;
          }
          else if (ActiveJob->ChildResult.Pending == TRUE)
          {
            /* #142 If child result was expected, but wasn't set
             *   Report error. */
            result = VSWUPDM_E_JOB_INVALID_CHILD_RESULT;
          }
          else
          {
            /* #143: Otherwise: Any child result was handled correctly. */
          }

          /* #144 If no post-hook is present, finish job.
           * Otherwise, proceed with post-hook execution. */
          if (ActiveJob->PostHookFct == NULL_PTR)
          {
            jobPhase = VSWUPDM_JOB_PHASE_FINISH;
          }
          else
          {
            jobPhase = VSWUPDM_JOB_PHASE_POST_HOOK;
          }

          break;
        }
        case VSWUPDM_JOB_PHASE_POST_HOOK:
        /* #150 If post-hook was executed */
        {
          /* #151 If default hook action was returned */
          if (ActiveJob->HookAction == VSWUPDM_HOOK_ACTION_DEFAULT)
          {
            /* #152 Finish current job. */
            jobPhase = VSWUPDM_JOB_PHASE_FINISH;
          }
          else
          {
            /* #153 Evaluate result of post-hook execution. */
            jobPhase = VSWUPDM_JOB_PHASE_EVAL_POST_HOOK;
          }

          break;
        }
        case VSWUPDM_JOB_PHASE_EVAL_POST_HOOK:
        /* #160 If result of post-hook was evaluated */
        {
          /* #161 Default: Finish current job. */
          jobPhase = VSWUPDM_JOB_PHASE_FINISH;

          switch (ActiveJob->HookAction)
          {
            case VSWUPDM_HOOK_ACTION_CONTINUE:
            /* #162 If continuation was requested, resume main handler execution. */
            {
              if (result == E_OK)
              {
                jobPhase = VSWUPDM_JOB_PHASE_MAIN_HANDLER;
              }

              break;
            }
            case VSWUPDM_HOOK_ACTION_RETRY:
            case VSWUPDM_HOOK_ACTION_RESTART:
            /* #163 If retry was requested, increment retry counter and re-issue pre-hook execution. */
            {
              if (result == E_OK)
              {
                ActiveJob->RetryCount++;
                jobPhase = VSWUPDM_JOB_PHASE_PRE_HOOK;
              }

              break;
            }
            default:
            /* #164: Otherwise: Finish job. */
            {
              break;
            }
          }

          break;
        }
        default:
        /* #170: Otherwise: Error because of invalid state. */
        {
          result = VSWUPDM_E_INV_STATE;

          break;
        }
      }

      /* #180 Store updated job phase in current job. */
      ActiveJob->Phase = jobPhase;

      /* #200 Additional actions depending on next job phase */
      switch (jobPhase)
      {
        case VSWUPDM_JOB_PHASE_EVAL_PRE_HOOK:
        case VSWUPDM_JOB_PHASE_EVAL_POST_HOOK:
        /* #210 If result of pre- or post-hook shall be evaluated
         *        Set matching job state as indication for main handler. */
        {
          ActiveJob->State = VSWUPDM_JOB_STATE_EVAL_HOOK;
          break;
        }
        case VSWUPDM_JOB_PHASE_FINISH:
        /* #220 If job shall be finished */
        {
          /* #221 Update potential linked (parent) result. */
          vSwUpdM_Job_UpdateLinkedResult(ActiveJob);

          /* #222 Remember potential service ID for confirmation (may be "none")
           *      and reset ID in job object. */
          confirmationService = ActiveJob->ConfirmationService;
          source = ActiveJob->Source;
          ActiveJob->ConfirmationService = VSWUPDM_SID_NONE;

          /* #223 Remove current job from pending jobs queue. */
          (void)vSwUpdM_QueueRemove(&vSwUpdM_JobQueue, ActiveJob->QueueHandle);
          ActiveJob->QueueHandle = (vSwUpdM_QueueHandleType)VSWUPDM_QUEUE_HANDLE_NONE;

          break;
        }
        default:
        /* #230 Otherwise, setup initial job state for next phase. */
        {
          ActiveJob->State = VSWUPDM_JOB_STATE_INITIAL;
          break;
        }
      }

      break;
    }
    case VSWUPDM_JOB_STATUS_SUSPENDED:
    /* #300 If job reported successful suspending. */
    {
      /* #310 Was suspend requested? */
      if (ActiveState == VSWUPDM_STATE_SUSPENDING)
      {
        /* #320 Ensure queue for suspended jobs isn't full. */
        if (!vSwUpdM_QueueIsFull(&vSwUpdM_SuspendedJobQueue))
        {
          P2VAR(vSwUpdM_QueueEntryType, AUTOMATIC, VSWUPDM_APPL_VAR) queueEntry;

          /* #321 Append job to end of suspended jobs queue. */
          queueEntry = &vSwUpdM_QueueGetEntry(&vSwUpdM_SuspendedJobQueue, vSwUpdM_QueueAppend(&vSwUpdM_SuspendedJobQueue));
          queueEntry->entity = (vSwUpdM_EntityHandleType)ActiveJob->Type;
          queueEntry->prio   = (vSwUpdM_EntityHandleType)ActiveJob->CurrentPrio;

          /* #322 Remove job from pending jobs queue. */
          (void)vSwUpdM_QueueRemove(&vSwUpdM_JobQueue, ActiveJob->QueueHandle);
          ActiveJob->QueueHandle = (vSwUpdM_QueueHandleType)VSWUPDM_QUEUE_HANDLE_NONE;

          /* #323 Remember potential service ID for confirmation (may be "none")
           *      and overwrite positive result with "suspended" result code. */
          confirmationService = ActiveJob->ConfirmationService;
          source              = ActiveJob->Source;
          result              = VSWUPDM_E_SUSPENDED;

          if (ActiveJob->LinkedResult != NULL_PTR)
          {
            if (ActiveJob->LinkedResult->Valid == FALSE)
            {
              ActiveJob->LinkedResult->Result = VSWUPDM_E_SUSPENDED;
              ActiveJob->LinkedResult->Valid = TRUE;
            }
          }
        }
        /* #330 Otherwise: Error because of invalid state. */
        else
        {
          result = VSWUPDM_E_INV_STATE;
        }
      }
      /* #340 Otherwise: Error because of invalid state. */
      else
      {
        result = VSWUPDM_E_INV_STATE;
      }

      break;
    }
    case VSWUPDM_JOB_STATUS_ACTIVE:
    case VSWUPDM_JOB_STATUS_PENDING:
    default:
    /* #400 Otherwise: Job still pending. */
    {
      break;
    }
  }

  /* #500 Update global state. */
  vSwUpdM_General_UpdateGlobalState();

  /* #510 Leave critical section ensuring exclusive access during (potential) queue removal and state change. */
  VSWUPDM_LEAVE_CRITICAL_SECTION();

  /* #520 Inform caller through confirmation function. */
  vSwUpdM_UlConfirmation(confirmationService, source, result);
  /* PRQA S 6030, 6080 1 */ /* MD_MSR_STCYC, MD_MSR_STMIF  */
} /* vSwUpdM_General_ConcludeJobProcessing */

# define VSWUPDM_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* VSWUPDM_EXCTSCHEDULE_IMPL_H */

/**********************************************************************************************************************
 *  END OF FILE: vSwUpdM_ExctSchedule_Impl.h
 *********************************************************************************************************************/
