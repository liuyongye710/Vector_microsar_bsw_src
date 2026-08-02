/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2021 by Vector Informatik GmbH.                                              All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/*!        \file  vMem_30_Blocking_HwRequests.h
 *        \brief  vMem_30_Blocking API header describing HW specific requests
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *********************************************************************************************************************/

#if !defined (VMEM_30_BLOCKING_HW_REQUESTS_H)
# define VMEM_30_BLOCKING_HW_REQUESTS_H

#include "vMem_30_Blocking_Types.h"

/* Hardware dependent request IDs */
/*! Request ID to be passed as argument for parameter vMemHwSpecificFuncIndex to vMemAccM_HwSpecificReq to address function
 *  vMem_30_Blocking_AcquireLock. DataPtr and Length shall be NULL_PTR and 0, respecively, because this HW specific request,
 *  does not have any parameters/data.
 */
#define VMEM_HW_REQ_ID_ACQUIRE_LOCK (0u)

struct vMem_30_Blocking_HwLockParams_s 
{
  enum vMem_30_Blocking_LockState_tag
  {
    VMEM_30_BLOCKING_UNLOCKED,
    VMEM_30_BLOCKING_LOCKED
  } LockState;
};

typedef P2VAR(struct vMem_30_Blocking_HwLockParams_s, AUTOMATIC, VMEM_30_BLOCKING_APPL_VAR) vMem_30_Blocking_HwLockParamsRefType;

# define VMEM_30_BLOCKING_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


/**********************************************************************************************************************
 *  vMem_30_Blocking_ReleaseLock()
 *********************************************************************************************************************/
/*! \brief       Releases Memory Device stack global Lock.
 *  \details     Ensures that pending (HW specific) job completes; vMemAccM continues its internal processing.
 *  \param[out]  lockParams          Points to a valid lockParams structure.
 *  \return      E_OK, if lock was released; E_NOT_OK if lockParams (pointer itself) did not denote lock's ownership
 *  \pre         -
 *  \post        RetVal == E_OK => vMem_30_Blocking_GetJobResult() == VMEM_JOB_OK && lockParams.LockState == UNLOCKED
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \trace CREQ-188024
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VMEM_30_BLOCKING_CODE) vMem_30_Blocking_ReleaseLock(vMem_30_Blocking_HwLockParamsRefType lockParams);

# define VMEM_30_BLOCKING_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */  /* MD_MSR_MemMap */
#endif /* VMEM_30_BLOCKING_HW_REQUESTS_H */

/**********************************************************************************************************************
 *  END OF FILE: vMem_30_Blocking_HwRequests.h
 *********************************************************************************************************************/
