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
 *         \file  vFeeAcc_StateWaitUnlock.c
 *        \brief  Implementation of internal state "wait for unlock"
 *
 *      \details  On enter, the vMem_30_Blocking gets informed that it shall stop blocking (complete its job),
 *                then the vMemAccM is cyclically polled for its completion (=> release lock got propagated).
 *                No need to react on cancel events, because this state is mandatory to complete job processing,
 *                even if it was cancelled. We have to unlock the resource "Flash".
 *                The FEE job result, received on entry, just gets forwarded to successor state (which is always IDLE).
 *********************************************************************************************************************/

#include "Std_Types.h"
#include "MemIf_Types.h"
#include "vFeeAcc_Fsm.h"
#include "vFeeAcc_Int.h"
#include "vFeeAcc_MemLocking.h"

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

#define VFEEACC_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! The FEE job result to be forwarded to next state after lock was released.
 *  \trace DSGN-vFeeAcc22798 */
VFEEACC_LOCAL VAR(MemIf_JobResultType, VFEEACC_PRIVATE_DATA) vFeeAcc_StateWaitUnlock_FeeJobResult;

#define VFEEACC_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


#define VFEEACC_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  vFeeAcc_StateWaitUnLock_evCyclic
 *********************************************************************************************************************/
/*!
 * \brief       Cyclic event handler for state WaitUnlock.
 * \details     Wait till vMemAccM is not pending anymore.
 * \param[out]  ctx - Pointer to a valid Public FSM context structure.
 * \pre         -
 * \context     TASK
 * \reentrant   FALSE
 * \synchronous TRUE 
 */
VFEEACC_INLINE_FUNC(void)
vFeeAcc_StateWaitUnLock_evCyclic(vFeeAcc_FsmContextPtrType ctx);

#define VFEEACC_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


#define VFEEACC_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! "Wait for Lock Release" state descriptor */
VFEEACC_LOCAL CONST(struct vFeeAcc_State_s,
             VFEEACC_PRIVATE_CONST) UnlockStateDescr = /* PRQA S 3218 */ /* MD_vFeeAcc_GlobalStaticGenConst */
    {vFeeAcc_StateWaitUnLock_evCyclic, vFeeAcc_Default_evCancel, vFeeAcc_Default_evNewJob};

#define VFEEACC_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


#define VFEEACC_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  vFeeAcc_StateWaitUnock()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
VFEEACC_INLINE_FUNC(void)
vFeeAcc_StateWaitUnLock_evCyclic(vFeeAcc_FsmContextPtrType ctx)
{
  if(!vFeeAcc_IsAccMPending())
  {
    vFeeAcc_StateIdle_onEnter(ctx, vFeeAcc_StateWaitUnlock_FeeJobResult);
  }
}

/**********************************************************************************************************************
 *  vFeeAcc_StateWaitUnlock_onEnter()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
VFEEACC_INTERNAL_FUNC(void) vFeeAcc_StateWaitUnlock_onEnter(vFeeAcc_FsmContextPtrType ctx, MemIf_JobResultType result)
{
  vFeeAcc_ReleaseLock(&ctx->LockingState);
  vFeeAcc_StateWaitUnlock_FeeJobResult = result;
  ctx->currState = &UnlockStateDescr;
}

#define VFEEACC_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  END OF FILE: vFeeAcc_StateWaitUnlock.c
 *********************************************************************************************************************/
