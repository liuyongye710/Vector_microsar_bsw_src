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
 *         \file  vFeeAcc_StateWaitFeeBusyInternal.c
 *        \brief  Implementation of state "Wait for Fee Busy Internal".
 *
 *      \details  On entering this state the vFeeAcc waits until the underlying Fee has finished an optional internal
 *                operation and is not MEMIF_BUSY_INTERNAL anymore. Within state we poll cyclically, but we do not have
 *                to react on cancel event. NvM "promises" to not cancel the Fee when it is MEMIF_BUSY_INTERNAL
 *                In case a new job arrives while being at this state, it shall be accepted and Fee shall go back to
 *                the state "Wait for Fee".
 *********************************************************************************************************************/
#define VFEEACC_STATE_WAIT_FEE_BUSY_INTERNAL_SOURCE

#include "Std_Types.h"

#include "vFeeAcc_Int.h"
#include "vFeeAcc_Fsm.h"
#include "vFeeAcc_FeeCfg.h"
#include "vFeeAcc_PublicStates.h"


#define VFEEACC_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define VFEEACC_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


#define VFEEACC_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


/**********************************************************************************************************************
 *  vFeeAcc_StateWaitFeeBusyInternal_evNewJob
 *********************************************************************************************************************/
/*!
 * \brief       New Job event handler for state WaitFeeBusyInternal.
 * \details     -
 * \param[in,out]  ctx - Pointer to a valid Public FSM context structure.
 * \param[in]     req - Pointer to a valid FEE request structure.
 * \return      TRUE if the event was consumed, FALSE if it shall be deferred.
 * \pre         -
 * \context     TASK
 * \reentrant   FALSE
 * \synchronous TRUE
 */
VFEEACC_INTERNAL_FUNC(boolean)
vFeeAcc_StateWaitFeeBusyInternal_evNewJob(vFeeAcc_FsmContextPtrType ctx, vFeeAcc_FeeRequestParams_ConstPtr reqParams);


/**********************************************************************************************************************
 *  vFeeAcc_StateWaitFeeBusyInternal_evCyclic
 *********************************************************************************************************************/
/*!
 * \brief       Cyclic event handler for state WaitFeeBusyInternal.
 * \details     Within this event it will be waited till Fee is IDLE.
 * \param[out]  ctx - Pointer to a valid Public FSM context structure.
 * \pre         -
 * \context     TASK
 * \reentrant   FALSE
 * \synchronous TRUE 
 */
VFEEACC_INLINE_FUNC(void)
vFeeAcc_StateWaitFeeBusyInternal_evCyclic(vFeeAcc_FsmContextPtrType ctx);

#define VFEEACC_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


#define VFEEACC_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! "Waiting for FEE Busy Internal" state descriptor
 * \trace DSGN-vFeeAcc22800 */
VFEEACC_LOCAL CONST(struct vFeeAcc_State_s,
             VFEEACC_PRIVATE_CONST) StateWaitFeeBusyInternalDesc = /* PRQA S 3218 */ /* MD_vFeeAcc_GlobalStaticGenConst */
    {vFeeAcc_StateWaitFeeBusyInternal_evCyclic, vFeeAcc_Default_evCancel, vFeeAcc_StateWaitFeeBusyInternal_evNewJob};

#define VFEEACC_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


#define VFEEACC_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


/**********************************************************************************************************************
 *  vFeeAcc_StateWaitFeeBusyInternal_evNewJob()
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
VFEEACC_INTERNAL_FUNC(boolean)
vFeeAcc_StateWaitFeeBusyInternal_evNewJob(vFeeAcc_FsmContextPtrType ctx, vFeeAcc_FeeRequestParams_ConstPtr reqParams)
{
  /* We might have been cancelled in-between. This means new job was setup while we are in BusyInternal, but it is cancelled
     before we could start it.*/
  if(reqParams->requestDescr.requestFunc != NULL_PTR)
  {
    ctx->request = *reqParams;
    /* We do not have to set the state of the public FSM here. It will be set by the public fsm on its own.*/
    vFeeAcc_StateWaitFee_onEnter(ctx);
  }
  return TRUE;
}

/**********************************************************************************************************************
 *  vFeeAcc_StateWaitFeeBusyInternal_evCyclic
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VFEEACC_INLINE_FUNC(void)
vFeeAcc_StateWaitFeeBusyInternal_evCyclic(vFeeAcc_FsmContextPtrType ctx)
{
  if(VFEEACC_Fee_GetStatus() == MEMIF_IDLE)
  {
    /* Actually, the result of the job is already set after leaving state WaitFee. However, the onEnter function of the
       Unlock state demands that we set a result. Since the internal operation does not touch the job result, we can
       use the GetJobResult function to get the job result, which will be the same as in the WaitFeeState. */
    vFeeAcc_StateWaitUnlock_onEnter(ctx, VFEEACC_Fee_GetJobResult());
  }
}

/**********************************************************************************************************************
 *  vFeeAcc_StateWaitFeeBusyInternal_onEnter()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
VFEEACC_INTERNAL_FUNC(void) vFeeAcc_StateWaitFeeBusyInternal_onEnter(vFeeAcc_FsmContextPtrType ctx, MemIf_JobResultType result)
{
  ctx->currState = &StateWaitFeeBusyInternalDesc;
  vFeeAcc_EnterBusyInternal(result);
}

#define VFEEACC_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  END OF FILE: vFeeAcc_StateWaitFee.c
 *********************************************************************************************************************/
