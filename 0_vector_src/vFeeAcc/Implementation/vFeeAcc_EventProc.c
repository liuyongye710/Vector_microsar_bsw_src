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
 *         \file  vFeeAcc_EventProc.c
 *        \brief  Implementation of VFeeAcc's internal FSM event processor
 *
 *      \details  Set event (cancel, newJob) and act upon them, including cyclic event (MainFunction)
 *********************************************************************************************************************/
#define VFEEACC_EVENT_PROC_SOURCE

#include "vFeeAcc_EventProc.h"

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

struct vFeeAcc_EventQueueContext
{
  boolean cancel; /*!< cancel processing event; just set or cleared */
  vFeeAcc_FeeRequestParams_VarPtr
      newJob; /*< new Job event carries parameters (which request), if set; therefore a pointer */
};


#define VFEEACC_START_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! internal structure that mimics a very simple event queue. It just holds one occurrence of the events
    That may trigger the FSM. Cyclic event is not contained, as each single MainFunction call itself
    implicitly fires that event. */

VFEEACC_LOCAL VAR(struct vFeeAcc_EventQueueContext, VFEEACC_PRIVATE_DATA) vFeeAcc_EventQueue = {FALSE, NULL_PTR};

#define VFEEACC_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define VFEEACC_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  vFeeAcc_ProcessEvents()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
VFEEACC_INTERNAL_FUNC(void) vFeeAcc_ProcessEvents(vFeeAcc_FsmContextPtrType ctx)
{
  if(vFeeAcc_EventQueue.cancel)
  {
    ctx->currState->evCancel(ctx);
    vFeeAcc_EventQueue.cancel = FALSE;
  }

  if(vFeeAcc_EventQueue.newJob != NULL_PTR)
  {
    if(ctx->currState->evNewJob(ctx, vFeeAcc_EventQueue.newJob))
    {
      vFeeAcc_EventQueue.newJob->requestDescr.requestFunc = NULL_PTR;
      vFeeAcc_EventQueue.newJob = NULL_PTR;
    }
  }

  ctx->currState->evCyclic(ctx);
}

/**********************************************************************************************************************
 *  vFeeAcc_SetNewJobEvent()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VFEEACC_INTERNAL_FUNC(void) vFeeAcc_SetNewJobEvent(vFeeAcc_FeeRequestParams_VarPtr req)
{
  vFeeAcc_EventQueue.newJob = req;
}

/**********************************************************************************************************************
 *  vFeeAcc_SetCancelEvent()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VFEEACC_INTERNAL_FUNC(void) vFeeAcc_SetCancelEvent(void)
{
  vFeeAcc_EventQueue.cancel = TRUE;
}

#define VFEEACC_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  END OF FILE: vFeeAcc_EventProc.c
 *********************************************************************************************************************/
