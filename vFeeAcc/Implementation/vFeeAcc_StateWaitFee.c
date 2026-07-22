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
 *         \file  vFeeAcc_StateWaitFee.c
 *        \brief  Implementation of state "Wait for Fee".
 *
 *      \details  On entering this state the FEE request get forwarded. Within state we poll cyclically, and we have to
 *                react properly on cancel event.
 *                When Fee completed processing, the job result will be forwarded to subsequent state.
 *********************************************************************************************************************/
#define VFEEACC_STATE_WAIT_FEE_SOURCE

#include "Std_Types.h"

#include "vFeeAcc_Int.h"
#include "vFeeAcc_Fsm.h"
#include "vFeeAcc_ForwardReq.h"
#include "vFeeAcc_FeeCfg.h"


#define VFEEACC_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! Stores, whether the request was accepted by FEE, i.e. whether it makes sense to poll for it's status.
    This is necessary, since we cannot initiate another transition from enter state.
    Any transition must complete before another one can be triggered; or in other words: Only
    event handlers may trigger state transitions (entry function EXECUTE them). */
VFEEACC_LOCAL VAR(boolean, VFEEACC_PRIVATE_DATA) vFeeAcc_StateWaitFee_ForwardReqAccepted;

#define VFEEACC_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


#define VFEEACC_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  vFeeAcc_StateWaitFee_evCancel
 *********************************************************************************************************************/
/*!
 * \brief       Cancel event handler for state WaitFee.
 * \details     Triggers transistion to state CancelWaitFee, where Fee_Cancel will be invoked.
 * \param[out]  ctx - Pointer to a valid Public FSM context structure.
 * \pre         -
 * \context     TASK
 * \reentrant   FALSE
 * \synchronous TRUE
 */
VFEEACC_INLINE_FUNC(void)
vFeeAcc_StateWaitFee_evCancel(vFeeAcc_FsmContextPtrType ctx);

/**********************************************************************************************************************
 *  vFeeAcc_StateWaitFee_evCyclic
 *********************************************************************************************************************/
/*!
 * \brief       Cyclic event handler for state WaitFee.
 * \details     Within this event is will be waited till Fee is IDLE.
 * \param[out]  ctx - Pointer to a valid Public FSM context structure.
 * \pre         -
 * \context     TASK
 * \reentrant   FALSE
 * \synchronous TRUE 
 */
VFEEACC_INLINE_FUNC(void)
vFeeAcc_StateWaitFee_evCyclic(vFeeAcc_FsmContextPtrType ctx);

#define VFEEACC_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


#define VFEEACC_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! "Waiting for FEE" state descriptor
 * \trace DSGN-vFeeAcc22800 */
VFEEACC_LOCAL CONST(struct vFeeAcc_State_s,
             VFEEACC_PRIVATE_CONST) StateWaitFeeDesc = /* PRQA S 3218 */ /* MD_vFeeAcc_GlobalStaticGenConst */
    {vFeeAcc_StateWaitFee_evCyclic, vFeeAcc_StateWaitFee_evCancel, vFeeAcc_Default_evNewJob};

#define VFEEACC_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


#define VFEEACC_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  vFeeAcc_StateWaitFee_evCancel
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VFEEACC_INLINE_FUNC(void)
vFeeAcc_StateWaitFee_evCancel(vFeeAcc_FsmContextPtrType ctx)
{
  vFeeAcc_StateCancelWaitFee_onEnter(ctx);
}


/**********************************************************************************************************************
 *  vFeeAcc_StateWaitFee_evCyclic
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
vFeeAcc_StateWaitFee_evCyclic(vFeeAcc_FsmContextPtrType ctx)
{
  if(!vFeeAcc_StateWaitFee_ForwardReqAccepted)
  {
    vFeeAcc_StateWaitUnlock_onEnter(ctx, MEMIF_JOB_FAILED);
  }
  else if(VFEEACC_Fee_GetStatus() == MEMIF_IDLE)
  {
    vFeeAcc_StateWaitUnlock_onEnter(ctx, VFEEACC_Fee_GetJobResult());
  }
  else if(VFEEACC_Fee_GetStatus() == MEMIF_BUSY_INTERNAL)
  {
    vFeeAcc_StateWaitFeeBusyInternal_onEnter(ctx, VFEEACC_Fee_GetJobResult());
  }
  else
  {
    /* PRQA S 2013 */ /* MD_MSR_EmptyClause */
  }
}

/**********************************************************************************************************************
 *  vFeeAcc_StateWaitFee_onEnter()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
VFEEACC_INTERNAL_FUNC(void) vFeeAcc_StateWaitFee_onEnter(vFeeAcc_FsmContextPtrType ctx)
{
  vFeeAcc_StateWaitFee_ForwardReqAccepted = (ctx->request.requestDescr.requestFunc(ctx->request.reqParams) == E_OK);
  ctx->currState = &StateWaitFeeDesc;
}

#define VFEEACC_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  END OF FILE: vFeeAcc_StateWaitFee.c
 *********************************************************************************************************************/
