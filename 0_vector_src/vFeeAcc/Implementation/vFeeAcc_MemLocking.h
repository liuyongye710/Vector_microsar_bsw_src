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
 *         \file  vFeeAcc_MemLocking.h
 *        \brief  Encapsulates the calls to vMemAccM and vMem_30_Blocking that request lock, poll for granting and
 *                release lock.
 *
 *      \details  The idea was to keep vMemAccM and vMem_30_Blocking related code together, instead of spreading it
 *                throughout the files (states)
 *********************************************************************************************************************/
#ifndef VFEEACC_MEMLOCKING_H
#define VFEEACC_MEMLOCKING_H

#include "Std_Types.h"
#include "vMemAccM.h"
#include "vMem_30_Blocking_HwRequests.h"
#include "vFeeAcc_PrivateCfg.h"
#include "vFeeAcc_Int.h"

#define VFEEACC_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

typedef vMem_30_Blocking_HwLockParamsRefType vFeeAcc_vMemHwLockParamsRefType;
typedef P2CONST(struct vMem_30_Blocking_HwLockParams_s,
                AUTOMATIC,
                VFEEACC_PRIVATE_DATA) vFeeAcc_vMemHwLockParamsRefConstType;

/**********************************************************************************************************************
 *  vFeeAcc_HaveLock()
 *********************************************************************************************************************/
/*!
 * \brief       Check whether lock was acquired.
 * \details     Checks lockingState's member. Does not have any side-effects.
 * \param[out]  lockingState - pointer to a valid Locking Structure (parameter for HW specific request)
 * \return      TRUE if lock was acquired, false otherwise.
 * \pre         -
 * \context     TASK
 * \reentrant   FALSE
 * \synchronous TRUE
 */
VFEEACC_INLINE_FUNC(boolean)
vFeeAcc_HaveLock(vFeeAcc_vMemHwLockParamsRefConstType lockingState);

/**********************************************************************************************************************
 *  vFeeAcc_IsAccMPending()
 *********************************************************************************************************************/
/*!
 * \brief       Check whether vMemAccM is pending on configured Virtual Address Area
 * \details     Does not have any side-effects
 * \return      TRUE if vMemAccM_GetJobResult(...) == VMEMACCM_JOB_PENDING
 * \pre         -
 * \context     TASK
 * \reentrant   FALSE
 * \synchronous TRUE
 */
VFEEACC_INLINE_FUNC(boolean)
vFeeAcc_IsAccMPending(void);


/**********************************************************************************************************************
 *  vFeeAcc_RequestLock()
 *********************************************************************************************************************/
/*!
 * \brief       Issue the lock request to vMemAccM
 * \details     It's a HW-specific request for the configured Address Area and, within, the configured HW Id.
 * \param[in,out]  lockingState - Pointer to a valid Locking Structure (parameter for HW specific request)
 *                               Will be updated asynchronously
 * \return      E_OK, on success, i.e. vMemAccM accepted and queued the request, E_NOT_OK otherwise
 * \pre         vFeeAcc_IsAccMPending() == FALSE
 * \pre         lockingState->LockState == VMEM_30_BLOCKING_UNLOCKED;
 * \post        HaveLock(lockingState) == FALSE
 * \post        on success: vFeeAcc_IsAccMPending() == TRUE
 * \post        on failure: vFeeAcc_IsAccMPending() == FALSE
 * \context     TASK
 * \reentrant   FALSE
 * \synchronous TRUE
 */
VFEEACC_INLINE_FUNC(Std_ReturnType)
vFeeAcc_RequestLock(vFeeAcc_vMemHwLockParamsRefType lockingState);

/**********************************************************************************************************************
 *  vFeeAcc_CancelAcquireLock()
 *********************************************************************************************************************/
/*!
 * \brief       Attempt to cancel a pending lock request
 * \details     Signal to vMemAccM, that a queued request shall be discarded.
 * \pre         -
 * \context     TASK
 * \reentrant   FALSE
 * \synchronous TRUE
 */
VFEEACC_INLINE_FUNC(void)
vFeeAcc_CancelAcquireLock(void);

/**********************************************************************************************************************
 *  vFeeAcc_ReleaseLock()
 *********************************************************************************************************************/
/*!
 * \brief       Attempt to release a lock
 * \details     Just inform vMem_30_Blocking that the lock shall be released.
 * \param[out]  lockingState - pointer to a valid Locking Structure (parameter for HW specific request)
 * \pre         -
 * \post        side-effects result from vMem_30_Blocking release lock.
 * \context     TASK
 * \reentrant   FALSE
 * \synchronous TRUE
 */
VFEEACC_INLINE_FUNC(void)
vFeeAcc_ReleaseLock(vFeeAcc_vMemHwLockParamsRefType lockingState);

/**********************************************************************************************************************
 *  vFeeAcc_RequestLock()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
/* PRQA S 3219 11 */ /* MD_vFeeAcc_UnsuedFunction */
VFEEACC_INLINE_FUNC(Std_ReturnType)
vFeeAcc_RequestLock(vFeeAcc_vMemHwLockParamsRefType lockingState)
{
  return vMemAccM_HwSpecificReq(vFeeAcc_AddressArea_t,
                                vFeeAcc_AccMHwId,
                                VMEM_HW_REQ_ID_ACQUIRE_LOCK,
                                        lockingState, /* PRQA S 0315 */ /* MD_vFeeAcc_ImplicitConvToVoidPtrExternal */                               
                                sizeof(struct vMem_30_Blocking_HwLockParams_s));
}

/**********************************************************************************************************************
 *  vFeeAcc_CancelAcquireLock()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
/* PRQA S 3219 4 */ /* MD_vFeeAcc_UnsuedFunction */
VFEEACC_INLINE_FUNC(void)
vFeeAcc_CancelAcquireLock(void)
{
  vMemAccM_Cancel(vFeeAcc_AddressArea_t);
}

/**********************************************************************************************************************
 *  vFeeAcc_HaveLock()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
/* PRQA S 3219 4 */ /* MD_vFeeAcc_UnsuedFunction */
VFEEACC_INLINE_FUNC(boolean)
vFeeAcc_HaveLock(vFeeAcc_vMemHwLockParamsRefConstType lockingState)
{
  return (lockingState->LockState == VMEM_30_BLOCKING_LOCKED);
}

/**********************************************************************************************************************
 *  vFeeAcc_IsAccMPending()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
/* PRQA S 3219 4 */ /* MD_vFeeAcc_UnsuedFunction */
VFEEACC_INLINE_FUNC(boolean)
vFeeAcc_IsAccMPending(void)
{
  /* We may ignore the case VMEM == PENDING && VMEMACCM != PENDING (for this address area):
      This cannot happen, as long as one VMEM instance has only one (this) single using address area. */
  return (vMemAccM_GetJobResult(vFeeAcc_AddressArea_t) == VMEMACCM_JOB_PENDING);
}

/**********************************************************************************************************************
 *  vFeeAcc_ReleaseLock()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
/* PRQA S 3219 7 */ /* MD_vFeeAcc_UnsuedFunction */
VFEEACC_INLINE_FUNC(void)
vFeeAcc_ReleaseLock(vFeeAcc_vMemHwLockParamsRefType lockingState)
{
  /* we are not interested in return value (success/failure) -> there is nothing we (or caller)
     could do about it */
  (void)vMem_30_Blocking_ReleaseLock(lockingState);
}

#define VFEEACC_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* VFEEACC_MEMLOCKING_H */

/**********************************************************************************************************************
 *  END OF FILE: vFeeAcc_MemLocking.h
 *********************************************************************************************************************/

