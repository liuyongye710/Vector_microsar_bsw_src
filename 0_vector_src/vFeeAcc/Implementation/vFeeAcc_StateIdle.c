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
 *         \file  vFeeAcc_StateIdle.c
 *        \brief  Implements the internal IDLE state.
 *
 *      \details  In idle state the module is capable of accepting a new job, i.e. it starts a new job processing.
 *                When entering this state it propagates the job result to the public FSM
 *********************************************************************************************************************/

#define VFEEACC_STATE_IDLE_SOURCE

#include "Std_Types.h"
#include "vFeeAcc_Int.h"
#include "vFeeAcc_Fsm.h"
#include "vFeeAcc_PublicStates.h"


#define VFEEACC_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  vFeeAcc_StateIdle_evNewJob
 *********************************************************************************************************************/
/*!
 * \brief       New Job event handler for state Idle.
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
vFeeAcc_StateIdle_evNewJob(vFeeAcc_FsmContextPtrType ctx, vFeeAcc_FeeRequestParams_ConstPtr reqParams);

#define VFEEACC_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


#define VFEEACC_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! IdleState descriptor; Idle "inherits" default implementations of evCyclic and evCancel
 *  \trace DSGN-vFeeAcc22802 */
VFEEACC_LOCAL CONST(struct vFeeAcc_State_s, VFEEACC_PRIVATE_CONST) vFeeAcc_StateIdle = 
                         {vFeeAcc_Default_evCyclic, vFeeAcc_Default_evCancel, vFeeAcc_StateIdle_evNewJob};

#define VFEEACC_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


#define VFEEACC_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  vFeeAcc_StateIdle_evNewJob()
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
vFeeAcc_StateIdle_evNewJob(vFeeAcc_FsmContextPtrType ctx, vFeeAcc_FeeRequestParams_ConstPtr reqParams)
{
  /* We might have been cancelled in-between */
  if(reqParams->requestDescr.requestFunc != NULL_PTR)
  {
    ctx->request = *reqParams;
    vFeeAcc_StateWaitLock_onEnter(ctx);
  }

  return TRUE;
}

/**********************************************************************************************************************
 *  vFeeAcc_StateIdle_onEnter()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */

VFEEACC_INTERNAL_FUNC(void) vFeeAcc_StateIdle_onEnter(vFeeAcc_FsmContextPtrType ctx, MemIf_JobResultType result)
{
  vFeeAcc_EnterIdle(result);
  ctx->currState = &vFeeAcc_StateIdle;
}

/**********************************************************************************************************************
 *  vFeeAcc_InitInternalFsm
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
void vFeeAcc_InitInternalFsm(vFeeAcc_FsmContextPtrType ctx)
{
  ctx->currState = &vFeeAcc_StateIdle;
}

#define VFEEACC_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  END OF FILE: vFeeAcc_StateIdle.c
 *********************************************************************************************************************/
