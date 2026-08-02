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
 *         \file  vFeeAcc_StateCancelWaitFee.c
 *        \brief  Implements the internal state "CancelWait"
 *
 *      \details  -
 *********************************************************************************************************************/
#define VFEEACC_STATE_CANCEL_WAIT_SOURCE

#include "Std_Types.h"
#include "vFeeAcc_Fsm.h"
#include "vFeeAcc_FeeCfg.h"

#define VFEEACC_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  vFeeAcc_StateCancelWaitFee_evNewJob
 *********************************************************************************************************************/
/*!
 * \brief       New Job event handler for state CancelWaitFee.
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
vFeeAcc_StateCancelWaitFee_evNewJob(vFeeAcc_FsmContextPtrType ctx, vFeeAcc_FeeRequestParams_ConstPtr reqParams);


/**********************************************************************************************************************
 *  vFeeAcc_StateCancelWaitFee_evCyclic
 *********************************************************************************************************************/
/*!
 * \brief       Cyclic event handler for state CancelWaitFee.
 * \details     Waiting till Fee is IDLE.
 * \param[out]  ctx - Pointer to a valid Public FSM context structure.
 * \pre         -
 * \context     TASK
 * \reentrant   FALSE
 * \synchronous TRUE 
 */
VFEEACC_INTERNAL_FUNC(void) vFeeAcc_StateCancelWaitFee_evCyclic(vFeeAcc_FsmContextPtrType ctx);

#define VFEEACC_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


#define VFEEACC_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! "Wait For FEE after cancel" state descriptor
 *  \trace DSGN-vFeeAcc22793 */
VFEEACC_LOCAL CONST(struct vFeeAcc_State_s,
             VFEEACC_PRIVATE_CONST) StateCancelWaitFeeDesc = /* PRQA S 3218 */ /* MD_vFeeAcc_GlobalStaticGenConst */
    {vFeeAcc_StateCancelWaitFee_evCyclic, vFeeAcc_Default_evCancel, vFeeAcc_StateCancelWaitFee_evNewJob};

#define VFEEACC_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


#define VFEEACC_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


/**********************************************************************************************************************
 *  vFeeAcc_StateCancelWaitFee_evNewJob()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VFEEACC_INTERNAL_FUNC(boolean)
vFeeAcc_StateCancelWaitFee_evNewJob(vFeeAcc_FsmContextPtrType ctx, vFeeAcc_FeeRequestParams_ConstPtr reqParams)
{
   /* We might have been cancelled in-between. This means new job was setup while we are in CancelWaitFee, but it is cancelled
     before we could start it.*/
  if(reqParams->requestDescr.requestFunc != NULL_PTR)
  {
  /* Fee has just been canceled and now a new job arrived (which was not again cancelled). We are not allowed to forward it immediately. 
     We have to wait until Fee is idle. So we just store the new job here and will forward it later, when we noticed that the Fee got idle.*/
    ctx->request = *reqParams;
  }
  return TRUE;
}


/**********************************************************************************************************************
 *  vFeeAcc_StateCancelWaitFee_evCyclic
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
VFEEACC_INTERNAL_FUNC(void) vFeeAcc_StateCancelWaitFee_evCyclic(vFeeAcc_FsmContextPtrType ctx)
{
  MemIf_StatusType status = VFEEACC_Fee_GetStatus();

  if(ctx->request.requestDescr.requestFunc != NULL_PTR) /* New job was set up */
  {
    if((status == MEMIF_IDLE) || (status == MEMIF_BUSY_INTERNAL)) /* Fee is in a state to process the new request */
    {
      vFeeAcc_StateWaitFee_onEnter(ctx);
    }
  }
  /* NO new job was set up */
  else if(status == MEMIF_IDLE) /* Fee is Idle, therefore no hardware access takes place anymore */
  {
     {
       vFeeAcc_StateWaitUnlock_onEnter(ctx, MEMIF_JOB_CANCELED); 
     }
  }
  else
  {
    /* Do nothing */
  }
  
}

/**********************************************************************************************************************
 *  vFeeAcc_StateCancelWaitFee_onEnter()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
VFEEACC_INTERNAL_FUNC(void) vFeeAcc_StateCancelWaitFee_onEnter(vFeeAcc_FsmContextPtrType ctx)
{
  /* Fee might have left status BUSY, when entering this state. According to AUTOSAR it shall (may) reject a cancel
   * request, and report an error to DET. */
  if(VFEEACC_Fee_GetStatus() == MEMIF_BUSY)
  {
    VFEEACC_Fee_Cancel();
  }

  /* Reset the current job. Otherwise, if no new job after a cancel operation would come, we would restart the old job.*/
  ctx->request.requestDescr.requestFunc = NULL_PTR;

  ctx->currState = &StateCancelWaitFeeDesc;
}

#define VFEEACC_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  END OF FILE: vFeeAcc_StateCancelWaitFee.c
 *********************************************************************************************************************/
