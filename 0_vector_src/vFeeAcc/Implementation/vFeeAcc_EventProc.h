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
 *         \file  vFeeAcc_EventProc.h
 *        \brief  Internal FSM's event queue and processing API
 *
 *      \details  Encapsulates the details of an event queue and event processing, by means of some simple API.
 *********************************************************************************************************************/
#ifndef VFEEACC_EVENTPROC_H
#define VFEEACC_EVENTPROC_H

#include "vFeeAcc_Fsm.h"

#define VFEEACC_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


/**********************************************************************************************************************
 *  vFeeAcc_ProcessEvents()
 *********************************************************************************************************************/
/*!
 * \brief       Event processing function
 * \details     Checks for raised events and calls current state's appropriate handlers
 * \param[in]   ctx -> denotes the FSM in its current state.
 * \pre         -
 * \context     TASK
 * \reentrant   FALSE
 * \synchronous TRUE
 */
VFEEACC_INTERNAL_FUNC(void) vFeeAcc_ProcessEvents(vFeeAcc_FsmContextPtrType ctx);

/**********************************************************************************************************************
 *  vFeeAcc_SetNewJobEvent()
 *********************************************************************************************************************/
/*!
 * \brief       Raise a New Job event.
 * \details     -
 * \param[in]   The request descriptor, i.e. that will serve as event parameters
 * \pre         -
 * \context     TASK
 * \reentrant   FALSE
 * \synchronous TRUE
 */
VFEEACC_INTERNAL_FUNC(void) vFeeAcc_SetNewJobEvent(vFeeAcc_FeeRequestParams_VarPtr req);

/**********************************************************************************************************************
 *  vFeeAcc_SetCancelEvent()
 *********************************************************************************************************************/
/*!
 * \brief       Raise a Cancel event.
 * \details     -
 * \pre         -
 * \context     TASK
 * \reentrant   FALSE
 * \synchronous TRUE
 */
VFEEACC_INTERNAL_FUNC(void) vFeeAcc_SetCancelEvent(void);

#define VFEEACC_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* VFEEACC_EVENTPROC_H */

/**********************************************************************************************************************
 *  END OF FILE: vFeeAcc_EventProc.h
 *********************************************************************************************************************/

