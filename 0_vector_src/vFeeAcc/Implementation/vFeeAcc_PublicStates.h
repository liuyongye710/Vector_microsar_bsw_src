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
 *         \file  vFeeAcc_PublicStates.h
 *        \brief  Declares the publicly visible state machine (related types, functions, data) of vFeeAcc
 *
 *      \details  The public FSM defines the states that can be retrieved via vFeeAcc_GetStatus() and includes
 *                UNINIT, IDLE, BUSY and BUSYINTERNAL states. The implementation covers transitions and events to trigger them,
 *                including cyclic event(s) (MainFunction), and job reception/rejection
 *********************************************************************************************************************/
#ifndef VFEEACC_PUBLIC_STATES_H
#define VFEEACC_PUBLIC_STATES_H

#include "vFeeAcc_Types.h"
#include "vFeeAcc_Int.h"
#include "vFeeAcc_PrivateCfg.h"

#if(VFEEACC_DEV_ERROR_REPORT == STD_ON)
#  include "Det.h"
#endif

#include "vMem_30_Blocking_HwRequests.h"

typedef struct vFeeAcc_FeeRequestParams_s vFeeAcc_jobType;

typedef P2VAR(struct vFeeAcc_PublicModuleStateContext, AUTOMATIC, VFEEACC_PRIVATE_DATA) vFeeAcc_PublicStateContextRef;
typedef P2CONST(struct vFeeAcc_PublicModuleStateContext,
                AUTOMATIC,
                VFEEACC_PRIVATE_DATA) vFeeAcc_PublicStateContextConstRef;

#define VFEEACC_START_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

extern VAR(struct vFeeAcc_PublicModuleStateContext, VFEEACC_PRIVATE_DATA) vFeeAcc_ModuleState;

#define VFEEACC_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define VFEEACC_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  vFeeAcc_InitPublicFsm()
 *********************************************************************************************************************/
/*!
 * \brief       Initialize the public FSM, denoted by ctx parameter
 * \details     -
 * \param[out]  ctx - Pointer to a valid Public FSM context structure, with undefined contents.
 * \pre         -
 * \post        vFeeAcc_GetStatusProc(ctx) == MEMIF_IDLE
 * \post        vFeeAcc_GetJobResultProc != MEMIF_JOB_PENDING
 * \post        vFeeAcc_SetupJobProc(ctx, ...) == E_OK;
 * \context     TASK
 * \reentrant   FALSE
 * \synchronous TRUE
 */
VFEEACC_INTERNAL_FUNC(void) vFeeAcc_InitPublicFsm(vFeeAcc_PublicStateContextRef ctx);

/**********************************************************************************************************************
 *  vFeeAcc_MainProc()
 *********************************************************************************************************************/
/*!
 * \brief       Main processing function of the state machine instance identified by ctx
 * \details     -
 * \param[in,out]  ctx - Pointer to a valid Public FSM context structure (with defined contents).
 * \pre         -
 * \context     TASK
 * \reentrant   FALSE
 * \synchronous TRUE
 */
VFEEACC_INTERNAL_FUNC(void) vFeeAcc_MainProc(vFeeAcc_PublicStateContextRef ctx);

/**********************************************************************************************************************
 *  vFeeAcc_CancelProc()
 *********************************************************************************************************************/
/*!
 * \brief       Cancellation function of the state machine instance identified by ctx
 * \details     Resets the public FSM to IDLE; internal (sub-)FSM needs to be continued.
 * \param[in,out]  ctx - Pointer to a valid Public FSM context structure (with defined contents).
 * \pre         -
 * \post        (vFeeAcc_GetStatusProc(ctx) == MEMIF_IDLE) &&
 *              (vFeeAcc_GetJobResultProc(ctx) == MEMIF_JOB_CANCELED) &&
 *              (vFeeAcc_SetupJobProc(ctx, ...) == E_OK)
 * \context     TASK
 * \reentrant   FALSE
 * \synchronous TRUE
 */
VFEEACC_INTERNAL_FUNC(void) vFeeAcc_CancelProc(vFeeAcc_PublicStateContextRef ctx);

/**********************************************************************************************************************
 *  vFeeAcc_GetStatusProc()
 *********************************************************************************************************************/
/*!
 * \brief       Retrieve status from the state machine instance identified by ctx
 * \details     Does not have any side-effects
 * \param[in]  ctx - Pointer to a valid Public FSM context structure (with defined contents).
 *                   Since this function shall serve as getter; it must not modify ctx.
 * \return      see MemIf_StatusType
 * \pre         -
 * \context     TASK
 * \reentrant   FALSE
 * \synchronous TRUE
 */
VFEEACC_INTERNAL_FUNC(MemIf_StatusType) vFeeAcc_GetStatusProc(vFeeAcc_PublicStateContextConstRef ctx);

/**********************************************************************************************************************
 *  vFeeAcc_GetJobResultProc()
 *********************************************************************************************************************/
/*!
 * \brief       Retrieve most recent job result from the state machine instance identified by ctx
 * \details     Does not have any side-effects
 * \param[in,out]  ctx - Pointer to a valid Public FSM context structure (with defined contents).
 *                      Since this function shall serve as getter; it must not modify ctx.
 * \return      see MemIf_JobResultType
 * \pre         -
 * \context     TASK
 * \reentrant   FALSE
 * \synchronous TRUE
 */
VFEEACC_INTERNAL_FUNC(MemIf_JobResultType) vFeeAcc_GetJobResultProc(vFeeAcc_PublicStateContextConstRef ctx);


/**********************************************************************************************************************
 *  vFeeAcc_SetupJobProc()
 *********************************************************************************************************************/
/*!
 * \brief       Setup a new request for the FSM instance identified by ctx.
 * \details     Just forward to current state (In C++ this would be called "non virtual interface (NVI)" idiom)
 * \param[in,out]  ctx - Pointer to a valid Public FSM context structure (with defined contents). It holds the state
 *                      object this request will be forwarded to.
 * \param[in]   reqDesc - Request descriptor (Forwarding function and Service ID) - by value. Forwading function
 *                        must not be NULL
 * \param[in]   reqParams - Request parameters to be forwarded to FEE; their validity depends on actual request.
 *                          (no checks here)
 * \return      E_OK if request was accepted; E_NOT_OK otherwise.
 * \pre         -
 * \post        if accepted (E_OK returned): (vFeeAcc_GetStatusProc(ctx) == MEMIF_BUSY) &&
 *                                           (vFeeAcc_GetJobResultProc(ctx) == MEMIF_JOB_PENDING) &&
 *                                           (vFeeAcc_SetupJobProc(ctx, ...) == E_NOT_OK)
 * \post        if rejected (E_NOT_OK returned): No side-effects (on ctx).
 * \context     TASK
 * \reentrant   FALSE
 * \synchronous TRUE
 */
VFEEACC_INTERNAL_FUNC(Std_ReturnType)
vFeeAcc_SetupJobProc(vFeeAcc_PublicStateContextRef ctx, vFeeAcc_RequestDescrType reqDesc, vFeeAcc_jobType reqParams);


/**********************************************************************************************************************
 *  vFeeAcc_ReportErrorToDet()
 *********************************************************************************************************************/
/*!
 * \brief       Helper function to call Det (if configured)
 * \details     Add ModuleId and Instance Id; forward ApiId and ErrorId
 * \param[in]   ApiId - Service Id (one of VFEEACC_SID_ constants) - service function that failed
 * \param[in]   ErrorId - one of VFEEACC_E_ constants (but could be any value)
 * \pre         -
 * \context     TASK
 * \reentrant   FALSE
 * \synchronous TRUE
 */
VFEEACC_INLINE_FUNC(void)
vFeeAcc_ReportErrorToDet(uint8 ApiId, uint8 ErrorId);


/**********************************************************************************************************************
 *  vFeeAcc_EnterIdle()
 *********************************************************************************************************************/
/*!
 * \brief       Signal to public FSM that internal FSM completed (entered IDLE state).
 * \details     Function handles this signal; if it is a "normal job termination" (no cancel inbetween: the
 *              public FSM is BUSY and there's no new job request) the result will be stored.
 *              Otherwise the signal will be ignored.
 * \param[in]   result - see MemIf_JobResultType, except MEMIF_JOB_PENDING
 * \pre         -
 * \post        If internal FSM terminated normally (no cancellation)
 *               (vFeeAcc_GetStatusProc(ctx) == MEMIF_IDLE)
 *               (vFeeAcc_GetJobResultProc(ctx) == result)
 *               (vFeeAcc_SetupJobProc(ctx, ...) == E_OK)
 * \post        otherwise, no side-effects
 * \context     TASK
 * \reentrant   FALSE
 * \synchronous TRUE
 */
VFEEACC_INTERNAL_FUNC(void) vFeeAcc_EnterIdle(MemIf_JobResultType result);

/**********************************************************************************************************************
 *  vFeeAcc_EnterBusyInternal()
 *********************************************************************************************************************/
/*!
 * \brief       Signal to public FSM that internal FSM completed the actual Fee request from the user, and now runs internal operation.
 * \details     -
 * \param[in]   result - see MemIf_JobResultType, except MEMIF_JOB_PENDING
 * \pre         -
 * \post        Fee is in state BusyInternal and ready to accept new jobs.
 *               (vFeeAcc_GetStatusProc(ctx) == MEMIF_BUSY_INTERNAL)
 *               (vFeeAcc_GetJobResultProc(ctx) == result)
 *               (vFeeAcc_SetupJobProc(ctx, ...) == E_OK)
 * \post        otherwise, no side-effects
 * \context     TASK
 * \reentrant   FALSE
 * \synchronous TRUE
 */
VFEEACC_INTERNAL_FUNC(void) vFeeAcc_EnterBusyInternal(MemIf_JobResultType result);

/**********************************************************************************************************************
 *  vFeeAcc_ReportErrorToDet()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
/* PRQA S 3219 10 */ /* MD_vFeeAcc_UnsuedFunction */
VFEEACC_INLINE_FUNC(void)
vFeeAcc_ReportErrorToDet(uint8 ApiId, uint8 ErrorId)
{
#if(VFEEACC_DEV_ERROR_REPORT == STD_ON)
  (void)Det_ReportError(VFEEACC_MODULE_ID, VFEEACC_INSTANCE_ID, ApiId, ErrorId);
#else
  VFEEACC_DUMMY_STATEMENT(ApiId);
  VFEEACC_DUMMY_STATEMENT(ErrorId);
#endif
}

#define VFEEACC_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* VFEEACC_PUBLIC_STATES_H */

/**********************************************************************************************************************
 *  END OF FILE: vFeeAcc_PublicStates.h
 *********************************************************************************************************************/
