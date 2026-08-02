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
 *         \file  vFeeAcc_StateWaitLock.c
 *        \brief  implementation of internal state "wait for lock"
 *
 *      \details  On Enter, the HW specific "lock" request is issued to vMemAccM; then it cyclically polls for progress
 *                Has to react properly on cancel event.
 *********************************************************************************************************************/
#define VFEEACC_STATE_WAIT_LOCK_SOURCE

#include "Std_Types.h"
#include "vFeeAcc_Int.h"
#include "vFeeAcc_Fsm.h"
#include "vFeeAcc_MemLocking.h"


#define VFEEACC_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! Stores, whether the lock request was accepted by vMemAccM, i.e. whether it makes sense to poll for it's status.
    This is necessary, since we cannot initiate another transition from enter state.
    Any transition must complete before another one can be triggered; or in other words: Only
    event handlers may trigger state transitions (entry function EXECUTE them). */
VFEEACC_LOCAL VAR(boolean, VFEEACC_PRIVATE_DATA) vFeeAcc_StateWaitLock_LockRequestAccepted;

#define VFEEACC_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define VFEEACC_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  vFeeAcc_StateWaitLock_evCancel
 *********************************************************************************************************************/
/*!
 * \brief       Cancel event handler for state WaitLock.
 * \details     -
 * \param[out]  ctx - Pointer to a valid Public FSM context structure.
 * \pre         -
 * \context     TASK
 * \reentrant   FALSE
 * \synchronous TRUE
 */
VFEEACC_INLINE_FUNC(void)
vFeeAcc_StateWaitLock_evCancel(vFeeAcc_FsmContextPtrType ctx);

/**********************************************************************************************************************
 *  vFeeAcc_StateWaitLock_evCyclic
 *********************************************************************************************************************/
/*!
 * \brief       Cyclic event handler for state WaitLock.
 * \details     -
 * \param[out]  ctx - Pointer to a valid Public FSM context structure.
 * \pre         -
 * \context     TASK
 * \reentrant   FALSE
 * \synchronous TRUE 
 */
VFEEACC_INLINE_FUNC(void)
vFeeAcc_StateWaitLock_evCyclic(vFeeAcc_FsmContextPtrType ctx);

#define VFEEACC_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define VFEEACC_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! "Waiting for Lock" state descriptor
 * \trace DSGN-vFeeAcc22801 */
VFEEACC_LOCAL CONST(struct vFeeAcc_State_s,
             VFEEACC_PRIVATE_CONST) StateWaitLockDescr = /* PRQA S 3218 */ /* MD_vFeeAcc_GlobalStaticGenConst */
    {vFeeAcc_StateWaitLock_evCyclic, vFeeAcc_StateWaitLock_evCancel, vFeeAcc_Default_evNewJob};

#define VFEEACC_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


#define VFEEACC_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
/**********************************************************************************************************************
 *  vFeeAcc_StateWaitLock_evCancel()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
VFEEACC_INLINE_FUNC(void)
vFeeAcc_StateWaitLock_evCancel(vFeeAcc_FsmContextPtrType ctx)
{
  vFeeAcc_CancelAcquireLock();
  vFeeAcc_StateWaitUnlock_onEnter(ctx, MEMIF_JOB_CANCELED);
}


/**********************************************************************************************************************
 *  vFeeAcc_StateWaitLock_evCyclic()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
VFEEACC_INLINE_FUNC(void)
vFeeAcc_StateWaitLock_evCyclic(vFeeAcc_FsmContextPtrType ctx)
{
  if(vFeeAcc_IsAccMPending() && vFeeAcc_StateWaitLock_LockRequestAccepted)
  {
    if(vFeeAcc_HaveLock(&ctx->LockingState))
    {
      vFeeAcc_StateWaitFee_onEnter(ctx);
    }
  }
  else
  {
    vFeeAcc_StateIdle_onEnter(ctx, MEMIF_JOB_FAILED);
  }
}

/**********************************************************************************************************************
 *  vFeeAcc_StateWaitLock_onEnter()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
VFEEACC_INTERNAL_FUNC(void) vFeeAcc_StateWaitLock_onEnter(vFeeAcc_FsmContextPtrType ctx)
{
  ctx->LockingState.LockState = VMEM_30_BLOCKING_UNLOCKED;
  vFeeAcc_StateWaitLock_LockRequestAccepted = (vFeeAcc_RequestLock(&ctx->LockingState) == E_OK);
  ctx->currState = &StateWaitLockDescr;
}

#define VFEEACC_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  END OF FILE: vFeeAcc_StateWaitLock.c
 *********************************************************************************************************************/
