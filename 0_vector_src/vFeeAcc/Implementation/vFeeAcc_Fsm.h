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
 *         \file  vFeeAcc_Fsm.h
 *        \brief  Declares the internal FSM's public interface: types/structures, functions
 *
 *      \details  The internal FSM defines the job processing (get lock, process/wait for FEE, release lock).
 *                The API of this (bunch of) sub-component(s) is split into vtable-like structures, and constructor-like
 *                entry functions. Additionally there's an FSM initialization function, responsible for define and set
 *                the initial state.
 *********************************************************************************************************************/
#ifndef VFEEACC_FSM_H
#define VFEEACC_FSM_H

#include "Std_Types.h"
#include "MemIf_Types.h"

#include "vFeeAcc_Int.h"
#include "vFeeAcc_ForwardReq.h"
#include "vFeeAcc_MemLocking.h"

typedef P2VAR(struct vFeeAcc_FsmContext_s, AUTOMATIC, VFEEACC_PRIVATE_DATA) vFeeAcc_FsmContextPtrType;

/**********************************************************************************************************************
 *  vFeeAcc_Fsm_evCyclicPtr
 *********************************************************************************************************************/
/*!
 * \brief       Cyclic event handler for this state
 * \details     Essentially some polling functionality. Polling is the main reason, why this FSM exists...
 *              Nevertheless a concrete handler may decide to do nothing - it may wait for another type of event.
 * \param[out]  ctx - Pointer to a valid Public FSM context structure.
 * \pre         -
 * \context     TASK
 * \reentrant   FALSE
 * \synchronous TRUE 
 */
typedef VFEEACC_P2INTERNAL_FUNC(void, vFeeAcc_Fsm_evCyclicPtr)(vFeeAcc_FsmContextPtrType ctx);

/**********************************************************************************************************************
 *  vFeeAcc_Fsm_evCancelPtr
 *********************************************************************************************************************/
/*!
 * \brief       Cancel event handler for a state
 * \details     Will always be delivered; cannot be ignored/deferred. Handler may decide to do nothing.
 * \param[out]  ctx - Pointer to a valid Public FSM context structure.
 * \pre         -
 * \context     TASK
 * \reentrant   FALSE
 * \synchronous TRUE
 */
typedef VFEEACC_P2INTERNAL_FUNC(void, vFeeAcc_Fsm_evCancelPtr)(vFeeAcc_FsmContextPtrType ctx);

/**********************************************************************************************************************
 *  vFeeAcc_Fsm_evNewJobFuncPtr
 *********************************************************************************************************************/
/*!
 * \brief       New Job event handler for a state
 * \details     May accept (consume) or ignore (defer) the event. A deferred event shall be kept by the caller;
 *              it shall deliver it later (to another state/handler).
 * \param[in,out]  ctx - Pointer to a valid Public FSM context structure.
 * \param[in]     req - Pointer to a valid FEE request structure.
 * \return      TRUE if the event was consumed, FALSE if it shall be deferred.
 * \pre         -
 * \context     TASK
 * \reentrant   FALSE
 * \synchronous TRUE
 */
typedef VFEEACC_P2INTERNAL_FUNC(boolean, vFeeAcc_Fsm_evNewJobFuncPtr)(vFeeAcc_FsmContextPtrType         ctx,
                                                                      vFeeAcc_FeeRequestParams_ConstPtr req);


/*! The state "class"; a state's behavior is solely implemented by its event handlers
 (and its entry function; see below) */
struct vFeeAcc_State_s
{
  /*! A "cyclic" event will always be consumed; no need for a retval to indicate what happened. */
  vFeeAcc_Fsm_evCyclicPtr evCyclic;

  /*! A "cancel" event will always be consumed; no need for a retval to indicate what happened. */
  vFeeAcc_Fsm_evCancelPtr evCancel;

  /*! A "new job" event may be deferred. It can only be consumed if the state itself is able to react properly.
   *  Otherwise the event needs to be kept active, until an appropriate state _can_ consume it */
  vFeeAcc_Fsm_evNewJobFuncPtr evNewJob;
};

/*! A state descriptor instance is constant; therefore it is stored in ROM. This pointer type
 *  defines the reference type */
typedef P2CONST(struct vFeeAcc_State_s, AUTOMATIC, VFEEACC_PRIVATE_DATA) vFeeAcc_StatePtr;

/*! Structure, aggregating current state along with FSM-global data, such as the current FEE job,
 *  along with its parameters, and current locking state.
 *  Those data "live" throughout the whole FSM; they are needed in different states. */
struct vFeeAcc_FsmContext_s
{
  vFeeAcc_StatePtr                       currState; /*!< The current state (reference) */
  struct vFeeAcc_RequestParams_s         request; /*!< FEE request and its params */
  struct vMem_30_Blocking_HwLockParams_s LockingState; /*!< Own Lock structure (to acquire and release locks) */
};


#define VFEEACC_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  vFeeAcc_InitInternalFsm()
 *********************************************************************************************************************/
/*!
 * \brief       Initialize FSM denoted by parameter
 * \details     Implemented along with the initial state (IDLE)
 * \param[in,out] ctx - pointer to FSM's data.
 * \pre         -
 * \post        current state (in ctx) == DefaultState (i.e. StateIdle)
 * \context     TASK
 * \reentrant   FALSE
 * \synchronous TRUE
 */
VFEEACC_INTERNAL_FUNC(void) vFeeAcc_InitInternalFsm(vFeeAcc_FsmContextPtrType ctx);

/**********************************************************************************************************************
 *  State Entry functions
 *  Every state must define an entry functions.
 *  It is responsible to update the FSM data, to make the state the current one.
 *  These functions shall only be called on transition paths (which are implemented in event handlers)
 *  Every state transition (including external self-transition) shall end with entering the new state,
 *  Calling a state's entry function shall be the last action in a state transition.
 *  Internal self-transitions shall not call any entry function (that's why they are "internal").
 *
 *  Subsequent function's pre-conditions, are also the pre-conditions for entering the associated state.
 *  In contrast, their post-conditions are only related to the functions themselves.
 *
 *  Note:
 *  State exit functions, as well as any other related functions are not part of a state's interface.
 *  Rather, they are implementation details. If necessary, they should be locally visible/callable only.
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  vFeeAcc_StateIdle_onEnter()
 *********************************************************************************************************************/
/*!
 * \brief       Enter IDLE state
 * \details     -
 * \param[in,out] ctx - pointer to FSM's data.
 * \param[in]   result - Most recent FEE result, to be propagated to public FSM; shall not be MEMIF_JOB_PENDING
 * \pre         vMemAccM (vFeeAcc's virtual address area) is IDLE
 * \post        current state (in ctx) == StateIdle
 * \context     TASK
 * \reentrant   FALSE
 * \synchronous TRUE
 */
VFEEACC_INTERNAL_FUNC(void) vFeeAcc_StateIdle_onEnter(vFeeAcc_FsmContextPtrType ctx, MemIf_JobResultType result);

/**********************************************************************************************************************
 *  vFeeAcc_StateWaitUnlock_onEnter()
 *********************************************************************************************************************/
/*!
 * \brief       Enters WaitUnlock state.
 * \details     Note: The result will be forwarded successor state (IDLE), it stems from predecessor.
 * \param[in,out] ctx - pointer to FSM's data.
 * \param[in]   result - Most recent FEE result, to be eventually propagated to public FSM; shall not be
                         MEMIF_JOB_PENDING
 * \pre         Underlying FEE is IDLE
 * \post        current state (in ctx) == StateWaitUnlock
 * \post        Unlock Request was issued: ctx->LockingState.LockState == VMEM_30_BLOCKING_UNLOCKED
 * \context     TASK
 * \reentrant   FALSE
 * \synchronous TRUE
 */
VFEEACC_INTERNAL_FUNC(void) vFeeAcc_StateWaitUnlock_onEnter(vFeeAcc_FsmContextPtrType ctx, MemIf_JobResultType result);

/**********************************************************************************************************************
 *  vFeeAcc_StateWaitLock_onEnter()
 *********************************************************************************************************************/
/*!
 * \brief       Enters WaitLock state.
 * \details     This state waits for the asynchronous lock request to be granted.
 * \param[in,out] ctx - pointer to FSM's data.
 * \pre         Underlying FEE is IDLE
 * \pre         vFeeAcc's virtual address space is IDLE: vMemAccM_GetJobResult(addrId) != MEMIF_JOB_PENDING
 * \post        current state (in ctx) == StateWaitLock
 * \context     TASK
 * \reentrant   FALSE
 * \synchronous TRUE
 */
VFEEACC_INTERNAL_FUNC(void) vFeeAcc_StateWaitLock_onEnter(vFeeAcc_FsmContextPtrType ctx);

/**********************************************************************************************************************
 *  vFeeAcc_StateWaitFee_onEnter()
 *********************************************************************************************************************/
/*!
 * \brief       Enters WaitFee state.
 * \details     On enter, forward the request to FEE, then wait for FEE becoming IDLE.
 * \param[in,out] ctx - pointer to FSM's data (it also contains request and its params).
 * \pre         Underlying FEE is IDLE
 * \pre         Memory Lock was aquired: (vMemAccM_GetJobResult(addrId) == MEMIF_JOB_PENDING) &&
 *               ctx->LockingState.LockState == VMEM_30_BLOCKING_LOCKED
 * \post        current state (in ctx) == StateWaitFee
 * \context     TASK
 * \reentrant   FALSE
 * \synchronous TRUE
 */
VFEEACC_INTERNAL_FUNC(void) vFeeAcc_StateWaitFee_onEnter(vFeeAcc_FsmContextPtrType ctx);

/**********************************************************************************************************************
 *  vFeeAcc_StateWaitFeeBusyInternal_onEnter()
 *********************************************************************************************************************/
/*!
 * \brief       Enters WaitFeeBusyInternal state.
 * \details     On enter, set the public fsm state to BusyInternal and forward the result.
 * \param[in,out] ctx - pointer to FSM's data (it also contains request and its params).
 * \param[in]   result - Most recent FEE result, to be eventually propagated to public FSM; shall not be
                MEMIF_JOB_PENDING.
 * \pre         Underlying FEE is MEMIF_BUSY_INTERNAL
 * \pre         Memory Lock was aquired: (vMemAccM_GetJobResult(addrId) != MEMIF_JOB_PENDING) &&
 *               ctx->LockingState.LockState == VMEM_30_BLOCKING_LOCKED
 * \post        current state (in ctx) == StateWaitFeeBusyInternal
 * \context     TASK
 * \reentrant   FALSE
 * \synchronous TRUE
 */
VFEEACC_INTERNAL_FUNC(void) vFeeAcc_StateWaitFeeBusyInternal_onEnter(vFeeAcc_FsmContextPtrType ctx, MemIf_JobResultType result);

/**********************************************************************************************************************
 *  vFeeAcc_StateCancelWaitFee_onEnter()
 *********************************************************************************************************************/
/*!
 * \brief       Enters WaitCancelFee state.
 * \details     Call FEE cancel; then wait until it becomes IDLE.
 * \param[in,out] ctx - pointer to FSM's data (it also contains request and its params).
 * \pre         Underlying FEE is BUSY
 * \pre         Memory Lock was aquired: (vMemAccM_GetJobResult(addrId) == MEMIF_JOB_PENDING) &&
 *               ctx->LockingState.LockState == VMEM_30_BLOCKING_LOCKED
 * \post        current state (in ctx) == StateWaitCancleFee
 * \context     TASK
 * \reentrant   FALSE
 * \synchronous TRUE
 */
VFEEACC_INTERNAL_FUNC(void) vFeeAcc_StateCancelWaitFee_onEnter(vFeeAcc_FsmContextPtrType ctx);

/**********************************************************************************************************************
 * Default Event handlers
 *
 * Since not all state act on every event that may occur, we define default, empty handlers
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  vFeeAcc_Default_evCyclic()
 *********************************************************************************************************************/
/*!
 * \brief       Default Cyclic event handler; fulfills vFeeAcc_Fsm_evCyclicPtr
 * \details     Does not have any side-effects
 * \param[in,out] ctx - pointer to FSM's data (it also contains request and its params).
 * \pre         -
 * \post        pre(ctx) == post(ctx) (deep)
 * \context     TASK
 * \reentrant   FALSE
 * \synchronous TRUE
 */
VFEEACC_INTERNAL_FUNC(void) vFeeAcc_Default_evCyclic(vFeeAcc_FsmContextPtrType ctx);

/**********************************************************************************************************************
 *  vFeeAcc_Default_evCancel()
 *********************************************************************************************************************/
/*!
 * \brief       Default Cancel event handler; fulfills vFeeAcc_Fsm_evCyclicPtr
 * \details     Does not have any side-effects
 * \param[in,out] ctx - pointer to FSM's data (it also contains request and its params).
 * \pre         -
 * \post        pre(ctx) == post(ctx) (deep)
 * \context     TASK
 * \reentrant   FALSE
 * \synchronous TRUE */
VFEEACC_INTERNAL_FUNC(void) vFeeAcc_Default_evCancel(vFeeAcc_FsmContextPtrType ctx);

/**********************************************************************************************************************
 *  vFeeAcc_Default_evNewJob()
 *********************************************************************************************************************/
/*!
 * \brief       Default New Job  event handler; fulfills vFeeAcc_Fsm_evCyclicPtr
 * \details     Does not have any side-effects
 * \param[in,out] ctx - pointer to FSM's data (it also contains request and its params).
 * \return      Always returns FALSE, as this handler does not process the New Job event; it shall be deferred.
 * \pre         -
 * \post        pre(ctx) == post(ctx) (deep)
 * \context     TASK
 * \reentrant   FALSE
 * \synchronous TRUE
 */
VFEEACC_INTERNAL_FUNC(boolean)
vFeeAcc_Default_evNewJob(vFeeAcc_FsmContextPtrType ctx, vFeeAcc_FeeRequestParams_ConstPtr reqParams);

#define VFEEACC_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* VFEEACC_FSM_H */

/**********************************************************************************************************************
 *  END OF FILE: vFeeAcc_Fsm.h
 *********************************************************************************************************************/
