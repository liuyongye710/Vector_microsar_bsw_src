/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2020 by Vector Informatik GmbH.                                              All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         \file  vFeeAcc_PublicStates.c
 *        \brief  Implements the publicly visible state machine of vFeeAcc
 *
 *      \details  The public FSM defines the states that can be retrieved via vFeeAcc_GetStatus() and includes
 *                UNINIT, IDLE, BUSY and BUSYINTERNAL states. The implementation covers transitions and events to trigger them,
 *                including cyclic event(s) (MainFunction), and job reception/rejection
 *********************************************************************************************************************/
#define VFEEACC_PUBLIC_STATES_SOURCE

#include "vFeeAcc_PublicStates.h"
#include "vFeeAcc_EventProc.h"

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/*! The function pointer table of the strategy class */
struct vFeeAcc_PublicModuleStateDescr
{
  VFEEACC_P2INTERNAL_FUNC(void, mainProc)(vFeeAcc_PublicStateContextRef ctx);
  VFEEACC_P2INTERNAL_FUNC(MemIf_JobResultType, getJobResult)(vFeeAcc_PublicStateContextConstRef ctx);
  VFEEACC_P2INTERNAL_FUNC(Std_ReturnType, newJob)(vFeeAcc_PublicStateContextRef ctx, vFeeAcc_FeeRequestParams_ConstPtr jobType);
  VFEEACC_P2INTERNAL_FUNC(void, cancel)(vFeeAcc_PublicStateContextRef ctx);
  MemIf_StatusType statusName; /* to be returned by GetStatus() */
};

/*! Const-Reference type to such a state describing object */
typedef P2CONST(struct vFeeAcc_PublicModuleStateDescr, AUTOMATIC, VFEEACC_CONST) vFeeAcc_PublicStateDescrRef;

/*! Structure describing the public state and related context of the module (one instance) */
struct vFeeAcc_PublicModuleStateContext
{
  vFeeAcc_PublicStateDescrRef    state; /*!< the current state - requests/calls will be redirected to this object */
  struct vFeeAcc_FsmContext_s    internalFsmCtx; /*!< internal state machine context */
  struct vFeeAcc_RequestParams_s recentUserRequest;
  MemIf_JobResultType jobResult; /*!< just a slot to store most recent job result (only relevant when IDLE) */
};


#define VFEEACC_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  vFeeAcc_IdleOrBusyInternalSetUserParameter()
 *********************************************************************************************************************/
/*!
 * \brief      Setup a new job, when module is IDLE or BUSYINTERNAL.
 * \details    Store request, transit to BUSY, signal New Job event to internal FSM
 *             No DET checks, as parameters cannot be checked (expected to be done by underlying FEE)
 * \param[in,out] ctx - public FSM's context
 * \param[in]  jobType - valid pointer to structure identifying the request and its parameters.
 * \return     always E_OK
 * \pre        -
 * \post       (vFeeAcc_GetStatusProc(ctx) == MEMIF_BUSY) && (vFee_GetJobResultProc(ctx) == MEMIF_JOB_PENDING)
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
VFEEACC_INLINE_FUNC(Std_ReturnType)
vFeeAcc_IdleOrBusyInternalSetUserParameter(vFeeAcc_PublicStateContextRef ctx, vFeeAcc_FeeRequestParams_ConstPtr jobType);

/**********************************************************************************************************************
 *  vFeeAcc_BusySetUserParameterFails()
 *********************************************************************************************************************/
/*!
 * \brief      Setup a new job, when module is already or still BUSY.
 * \details    Not allowed - report BUSY to DET (if configured)
 * \param[in,out] ctx - public FSM's Context - ignored
 * \param[in]  jobType - valid pointer to structure identifying the request and its parameters.
 * \return     always E_NOT_OK
 * \pre        -
 * \post       no side-effects (except DET error reporting)
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
VFEEACC_INLINE_FUNC(Std_ReturnType)
vFeeAcc_BusySetUserParameterFails(vFeeAcc_PublicStateContextRef ctx, vFeeAcc_FeeRequestParams_ConstPtr jobType);

/**********************************************************************************************************************
 *  vFeeAcc_UninitSetUserParameterFails()
 *********************************************************************************************************************/
/*!
 * \brief      Setup a new job, when module was not initialized yet.
 * \details    Not allowed - report UNINIT to DET (if configured)
 * \param[in,out] ctx - public FSM's context - ignored
 * \param[in]  jobType - valid pointer to structure identifying the request and its parameters.
 * \return     always E_NOT_OK
 * \pre        -
 * \post       no side-effects (except DET error reporting)
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
VFEEACC_INLINE_FUNC(Std_ReturnType)
vFeeAcc_UninitSetUserParameterFails(vFeeAcc_PublicStateContextRef ctx, vFeeAcc_FeeRequestParams_ConstPtr jobType);


/**********************************************************************************************************************
 *  vFeeAcc_BusyCancel()
 *********************************************************************************************************************/
/*!
 * \brief      Cancel function, when module is actually BUSY.
 * \details    Discard job, become IDLE, notify internal FSM about cancellation.
 * \param[in,out] ctx - public FSM's context
 * \pre        -
 * \post       (vFeeAcc_GetStatusProc(ctx) == MEMIF_IDLE) && (vFeeAcc_GetJobResultProc(ctx) == MEMIF_JOB_IDLE)
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */

VFEEACC_INLINE_FUNC(void)
vFeeAcc_BusyCancel(vFeeAcc_PublicStateContextRef ctx);

/**********************************************************************************************************************
 *  vFeeAcc_UninitCancelFails()
 *********************************************************************************************************************/
/*!
 * \brief      Cancel function, when module was not initialized, yet.
 * \details    Cancel attempt has no effects, except an error reporting to DET (if configured).
 * \param[in,out] ctx - public FSM's context - ignored
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
VFEEACC_INLINE_FUNC(void)
vFeeAcc_UninitCancelFails(vFeeAcc_PublicStateContextRef ctx);

/**********************************************************************************************************************
 *  vFeeAcc_IdleOrBusyInternalCancel()
 *********************************************************************************************************************/
/*!
 * \brief      Cancel function, when module is in IDLE or BUSYINTERNAL state
 * \details    Attempting to cancel an IDLE or BUSYINTERNAL module, has no effects - it does nothing.
 * \param[in,out]  ctx - public FSM's context - ignored
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
VFEEACC_INLINE_FUNC(void)
vFeeAcc_IdleOrBusyInternalCancel(vFeeAcc_PublicStateContextRef ctx);

/**********************************************************************************************************************
 *  vFeeAcc_IdleOrBusyInternalGetJobResult()
 *********************************************************************************************************************/
/*!
 * \brief      Get Job Result function, when module is in IDLE or BUSYINTERNAL state
 * \details    Only when IDLE or BUSYINTERNAL, different job results can be returned.
 * \param[in,out]  ctx - public FSM's context
 * \return     the value stored in FSM context (when entering IDLE or BUSYINTERNAL state) see MemIf_JobResultType
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
VFEEACC_INLINE_FUNC(MemIf_JobResultType)
vFeeAcc_IdleOrBusyInternalGetJobResult(vFeeAcc_PublicStateContextConstRef ctx);

/**********************************************************************************************************************
 *  vFeeAcc_BusyGetJobResult()
 *********************************************************************************************************************/
/*!
 * \brief      Get Job Result function, when module is in BUSY state
 * \details    -
 * \param[in,out]  ctx - public FSM's context - ignored
 * \return     Always MEMIF_JOB_PENDING
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
VFEEACC_INLINE_FUNC(MemIf_JobResultType)
vFeeAcc_BusyGetJobResult(vFeeAcc_PublicStateContextConstRef ctx);

/**********************************************************************************************************************
 *  vFeeAcc_UninitGetJobResult()
 *********************************************************************************************************************/
/*!
 * \brief      Get Job Result function, when module was not yet initialized (but startup code initialized our RAM)
 * \details    Unconditionally reports UNINIT error to DET.
 * \param[in,out]  ctx - public FSM's context - ignored
 * \return     Always MEMIF_JOB_FAILED
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
VFEEACC_INLINE_FUNC(MemIf_JobResultType)
vFeeAcc_UninitGetJobResult(vFeeAcc_PublicStateContextConstRef ctx);


/**********************************************************************************************************************
 *  vFeeAcc_UninitMainProc()
 *********************************************************************************************************************/
/*!
 * \brief      Main processing function, when module was not yet initialized (but startup code initialized our RAM)
 * \details    Do nothing, of course. Not even DET.
 * \param[in,out]  ctx - public FSM's context - ignored
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
VFEEACC_INLINE_FUNC(void)
vFeeAcc_UninitMainProc(vFeeAcc_PublicStateContextRef ctx);

/**********************************************************************************************************************
 *  vFeeAcc_IdleOrBusyOrBusyInternalMainProc()
 *********************************************************************************************************************/
/*!
 * \brief      Normal Main processing function, when module is initialized
 * \details    Same for BUSY,IDLE and BUSYINTERNAL
 * \param[in,out]  ctx - public FSM's context
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
VFEEACC_INLINE_FUNC(void)
vFeeAcc_IdleOrBusyOrBusyInternalMainProc(vFeeAcc_PublicStateContextRef ctx);

#define VFEEACC_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


#define VFEEACC_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! Statically describe the public UNINIT state
 *  \trace DSGN-vFeeAcc22799 */
VFEEACC_LOCAL CONST(struct vFeeAcc_PublicModuleStateDescr, VFEEACC_PRIVATE_CONST) ModState_Uninit = 
                                                                    {
                                                                    &vFeeAcc_UninitMainProc,
                                                                    &vFeeAcc_UninitGetJobResult,
                                                                    &vFeeAcc_UninitSetUserParameterFails,
                                                                    &vFeeAcc_UninitCancelFails,
                                                                    MEMIF_UNINIT
                                                                    };

/*! Statically describe the public IDLE state
 * \trace DSGN-vFeeAcc22796 */
VFEEACC_LOCAL CONST(struct vFeeAcc_PublicModuleStateDescr, VFEEACC_PRIVATE_CONST) ModState_Idle = 
                                                                    {
                                                                    &vFeeAcc_IdleOrBusyOrBusyInternalMainProc,
                                                                    &vFeeAcc_IdleOrBusyInternalGetJobResult,
                                                                    &vFeeAcc_IdleOrBusyInternalSetUserParameter,
                                                                    &vFeeAcc_IdleOrBusyInternalCancel,
                                                                    MEMIF_IDLE
                                                                    };

/*! Statically describe the public BUSY state
 * \trace DSGN-vFeeAcc22795 */
VFEEACC_LOCAL CONST(struct vFeeAcc_PublicModuleStateDescr, VFEEACC_PRIVATE_CONST) ModState_Busy = 
                                                                    {
                                                                    &vFeeAcc_IdleOrBusyOrBusyInternalMainProc,
                                                                    &vFeeAcc_BusyGetJobResult,
                                                                    &vFeeAcc_BusySetUserParameterFails,
                                                                    &vFeeAcc_BusyCancel,
                                                                    MEMIF_BUSY
                                                                    };

/*! Statically describe the public BUSYINTERNAL state
 * \trace DSGN-vFeeAcc22983 */
VFEEACC_LOCAL CONST(struct vFeeAcc_PublicModuleStateDescr, VFEEACC_PRIVATE_CONST) ModState_BusyInternal =         /* PRQA S 3218 */ /* MD_vFeeAcc_StateFileScopeStatic */
                                                                    {
                                                                    &vFeeAcc_IdleOrBusyOrBusyInternalMainProc,
                                                                    &vFeeAcc_IdleOrBusyInternalGetJobResult,
                                                                    &vFeeAcc_IdleOrBusyInternalSetUserParameter,
                                                                    &vFeeAcc_IdleOrBusyInternalCancel,
                                                                    MEMIF_BUSY_INTERNAL
                                                                    };

#define VFEEACC_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


#define VFEEACC_START_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! Module is initially in UNINIT state */
VAR(struct vFeeAcc_PublicModuleStateContext, VFEEACC_PRIVATE_DATA)
vFeeAcc_ModuleState = {&ModState_Uninit, {0}, {0}, MEMIF_JOB_FAILED};

#define VFEEACC_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define VFEEACC_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  vFeeAcc_InitPublicFsm
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
VFEEACC_INTERNAL_FUNC(void) vFeeAcc_InitPublicFsm(vFeeAcc_PublicStateContextRef ctx)
{
  ctx->state = &ModState_Idle;
  ctx->jobResult = MEMIF_JOB_OK;

  vFeeAcc_InitInternalFsm(&(ctx->internalFsmCtx));
}

/**********************************************************************************************************************
 *  vFeeAcc_GetStatusProc
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VFEEACC_INTERNAL_FUNC(MemIf_StatusType) vFeeAcc_GetStatusProc(vFeeAcc_PublicStateContextConstRef ctx)
{
  return ctx->state->statusName;
}


/**********************************************************************************************************************
 *  vFeeAcc_SetupJobProc
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VFEEACC_INTERNAL_FUNC(Std_ReturnType)
vFeeAcc_SetupJobProc(vFeeAcc_PublicStateContextRef ctx, vFeeAcc_RequestDescrType reqDesc, vFeeAcc_jobType reqParams)
{
  struct vFeeAcc_RequestParams_s req;
  req.requestDescr = reqDesc;
  req.reqParams = reqParams;
  return ctx->state->newJob(ctx, &req);
}


/**********************************************************************************************************************
 *  vFeeAcc_MainProc()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VFEEACC_INTERNAL_FUNC(void) vFeeAcc_MainProc(vFeeAcc_PublicStateContextRef ctx)
{
  ctx->state->mainProc(ctx);
}

/**********************************************************************************************************************
 *  vFeeAcc_IdleOrBusyOrBusyInternalMainProc()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VFEEACC_INLINE_FUNC(void)
vFeeAcc_IdleOrBusyOrBusyInternalMainProc(vFeeAcc_PublicStateContextRef ctx)
{
  vFeeAcc_ProcessEvents(&ctx->internalFsmCtx);
}

/**********************************************************************************************************************
 *  vFeeAcc_UninitMainProc()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
/* PRQA S 3673 4 */ /* MD_vFeeAcc_CtxParamCouldBeConst */
VFEEACC_INLINE_FUNC(void)
vFeeAcc_UninitMainProc(vFeeAcc_PublicStateContextRef ctx)
{
  VFEEACC_DUMMY_STATEMENT(ctx);
}

/**********************************************************************************************************************
 *  vFeeAcc_IdleOrBusyInternalSetUserParameter()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
VFEEACC_INLINE_FUNC(Std_ReturnType)
 vFeeAcc_IdleOrBusyInternalSetUserParameter(vFeeAcc_PublicStateContextRef ctx, vFeeAcc_FeeRequestParams_ConstPtr jobType)
{
  ctx->state = &ModState_Busy;

  ctx->recentUserRequest = *jobType;
  vFeeAcc_SetNewJobEvent(&ctx->recentUserRequest);
  return E_OK;
}

/**********************************************************************************************************************
 *  vFeeAcc_BusySetUserParameterFails()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
/* PRQA S 3673 6 */ /* MD_vFeeAcc_CtxParamCouldBeConst */
VFEEACC_INLINE_FUNC(Std_ReturnType)
vFeeAcc_BusySetUserParameterFails(vFeeAcc_PublicStateContextRef ctx, vFeeAcc_FeeRequestParams_ConstPtr jobType)
{
  vFeeAcc_ReportErrorToDet(jobType->requestDescr.ApiId, VFEEACC_E_BUSY);
  VFEEACC_DUMMY_STATEMENT(ctx);
  return E_NOT_OK;
}

/**********************************************************************************************************************
 *  vFeeAcc_UninitSetUserParameterFails()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
/* PRQA S 3673 6 */ /* MD_vFeeAcc_CtxParamCouldBeConst */
VFEEACC_INLINE_FUNC(Std_ReturnType)
vFeeAcc_UninitSetUserParameterFails(vFeeAcc_PublicStateContextRef ctx, vFeeAcc_FeeRequestParams_ConstPtr jobType)
{
  vFeeAcc_ReportErrorToDet(jobType->requestDescr.ApiId, VFEEACC_E_UNINIT);
  VFEEACC_DUMMY_STATEMENT(ctx);
  return E_NOT_OK;
}

/**********************************************************************************************************************
 *  vFeeAcc_GetJobResultProc()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VFEEACC_INTERNAL_FUNC(MemIf_JobResultType) vFeeAcc_GetJobResultProc(vFeeAcc_PublicStateContextConstRef ctx)
{
  return ctx->state->getJobResult(ctx);
}


/**********************************************************************************************************************
 *  vFeeAcc_IdleOrBusyInternalGetJobResult()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VFEEACC_INLINE_FUNC(MemIf_JobResultType)
vFeeAcc_IdleOrBusyInternalGetJobResult(vFeeAcc_PublicStateContextConstRef ctx)
{
  return ctx->jobResult;
}


/**********************************************************************************************************************
 *  vFeeAcc_BusyGetJobResult()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VFEEACC_INLINE_FUNC(MemIf_JobResultType)
vFeeAcc_BusyGetJobResult(vFeeAcc_PublicStateContextConstRef ctx)
{
  VFEEACC_DUMMY_STATEMENT(ctx);
  return MEMIF_JOB_PENDING;
}


/**********************************************************************************************************************
 *  vFeeAcc_UninitGetJobResult()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VFEEACC_INLINE_FUNC(MemIf_JobResultType)
vFeeAcc_UninitGetJobResult(vFeeAcc_PublicStateContextConstRef ctx)
{
  vFeeAcc_ReportErrorToDet(VFEEACC_SID_GET_JOB_RESULT, VFEEACC_E_UNINIT);
  VFEEACC_DUMMY_STATEMENT(ctx);
  return MEMIF_JOB_FAILED;
}

/**********************************************************************************************************************
 *  vFeeAcc_EnterIdle()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
VFEEACC_INTERNAL_FUNC(void) vFeeAcc_EnterIdle(MemIf_JobResultType result)
{
  /* only the transition from BUSY/BUSYINTERNAL to IDLE, and only if there isn't another request pending.
     This deals with UNINIT as well as cancellation with or without new pending request */
  if(((vFeeAcc_ModuleState.state == &ModState_Busy) || (vFeeAcc_ModuleState.state == &ModState_BusyInternal))
     && (vFeeAcc_ModuleState.recentUserRequest.requestDescr.requestFunc == NULL_PTR))
  {
    vFeeAcc_ModuleState.jobResult = result;
    vFeeAcc_ModuleState.state = &ModState_Idle;
  }
}

/**********************************************************************************************************************
 *  vFeeAcc_EnterBusyInternal()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
VFEEACC_INTERNAL_FUNC(void) vFeeAcc_EnterBusyInternal(MemIf_JobResultType result)
{
  vFeeAcc_ModuleState.jobResult = result;
  vFeeAcc_ModuleState.state = &ModState_BusyInternal;
}

/**********************************************************************************************************************
 *  vFeeAcc_CancelProc()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VFEEACC_INTERNAL_FUNC(void) vFeeAcc_CancelProc(vFeeAcc_PublicStateContextRef ctx)
{
  ctx->state->cancel(ctx);
}

/**********************************************************************************************************************
 *  vFeeAcc_UninitCancelFails()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
/* PRQA S 3673 6 */ /* MD_vFeeAcc_CtxParamCouldBeConst */
VFEEACC_INLINE_FUNC(void)
vFeeAcc_UninitCancelFails(vFeeAcc_PublicStateContextRef ctx)
{
  vFeeAcc_ReportErrorToDet(VFEEACC_SID_CANCEL, VFEEACC_E_UNINIT);
  VFEEACC_DUMMY_STATEMENT(ctx);
}

/**********************************************************************************************************************
 *  vFeeAcc_BusyCancel()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
VFEEACC_INLINE_FUNC(void)
vFeeAcc_BusyCancel(vFeeAcc_PublicStateContextRef ctx)
{
  const struct vFeeAcc_RequestParams_s noJob = {0};

  /* clear job data (a started job got its own copy) */
  ctx->recentUserRequest = noJob;  /* PRQA S 2916 */ /* MD_vFeeAcc_PointerWithGreaterLifetime */
  ctx->jobResult = MEMIF_JOB_CANCELED;
  ctx->state = &ModState_Idle;
  vFeeAcc_SetCancelEvent();
}

/**********************************************************************************************************************
 *  vFeeAcc_IdleOrBusyInternalCancel()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
/* PRQA S 3673 6 */ /* MD_vFeeAcc_CtxParamCouldBeConst */
VFEEACC_INLINE_FUNC(void)
vFeeAcc_IdleOrBusyInternalCancel(vFeeAcc_PublicStateContextRef ctx)
{
  /* In case of Idle or BusyInternal, there is no job to cancel. So do nothing here.*/
  VFEEACC_DUMMY_STATEMENT(ctx);
}

#define VFEEACC_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  END OF FILE: vFeeAcc_PublicStates.c
 *********************************************************************************************************************/
