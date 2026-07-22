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
 *         \file  vFeeAcc_StateDefaultEventHandlers.c
 *        \brief  Implements default internal FSM's event handlers
 *
 *      \details  Default event handlers just ignore the given event.
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
#define VFEEACC_STATE_DEFAULT_EVENT_HANDLERS_SOURCE

#include "vFeeAcc_Int.h"
#include "vFeeAcc_Fsm.h"
#include "vFeeAcc_PrivateCfg.h"

#define VFEEACC_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  vFeeAcc_Default_evCyclic
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
/* PRQA S 3673 4 */ /* MD_vFeeAcc_CtxParamCouldBeConst */
VFEEACC_INTERNAL_FUNC(void) vFeeAcc_Default_evCyclic(vFeeAcc_FsmContextPtrType ctx)
{
  VFEEACC_DUMMY_STATEMENT(ctx);
}

/**********************************************************************************************************************
 *  vFeeAcc_Default_evCancel
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
/* PRQA S 3673 4 */ /* MD_vFeeAcc_CtxParamCouldBeConst */
VFEEACC_INTERNAL_FUNC(void) vFeeAcc_Default_evCancel(vFeeAcc_FsmContextPtrType ctx)
{
  VFEEACC_DUMMY_STATEMENT(ctx);
}

/**********************************************************************************************************************
 *  vFeeAcc_Default_evNewJob
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
/* PRQA S 3673 4 */ /* MD_vFeeAcc_CtxParamCouldBeConst */
VFEEACC_INTERNAL_FUNC(boolean)
vFeeAcc_Default_evNewJob(vFeeAcc_FsmContextPtrType ctx, vFeeAcc_FeeRequestParams_ConstPtr reqParams)
{
  VFEEACC_DUMMY_STATEMENT(ctx);
  VFEEACC_DUMMY_STATEMENT(reqParams);

  return FALSE; /* by default, a new job event won't be consumed; it needs to be kept until a real handler kicks in */
}

#define VFEEACC_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  END OF FILE: vFeeAcc_StateDefaultEventHandlers.c
 *********************************************************************************************************************/
