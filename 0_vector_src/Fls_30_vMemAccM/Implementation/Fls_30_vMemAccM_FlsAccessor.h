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
/*!        \file  Fls_30_vMemAccM_FlsAccessor.h
 *        \brief  Fls_30_vMemAccM fls accessor header file
 *
 *      \details  Requests job from underlying module and also prepares buffer.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *********************************************************************************************************************/

#if !defined (FLS_30_VMEMACCM_FLSACCESSOR_H)
# define FLS_30_VMEMACCM_FLSACCESSOR_H

#include "Fls_30_vMemAccM_Job.h"


/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

#define FLS_30_VMEMACCM_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap  */

/**********************************************************************************************************************
 * Fls_30_vMemAccM_FlsAccessor_RequestAsyncJob
 *********************************************************************************************************************/
/*!
 * \brief       Requests given job with given parameters from lower layer.
 * \details     Returns the number of processed bytes, returns 0 in case of job reject.
 * \param[in]   jobType: type of the job to start 
 * \param[in]   address: forwarded address
 * \param[in,out]addressPtr: pointer to user buffer for the job
 * \param[in]   length: forwarded length
 * \return      0: job rejected, otherwise: numberOfProcessedBytes
 * \pre         -
 * \context     TASK
 * \reentrant   TRUE
 * \synchronous TRUE
 */
FUNC(Fls_30_vMemAccM_LengthType, FLS_30_VMEMACCM_CODE) Fls_30_vMemAccM_FlsAccessor_RequestAsyncJob
(
  Fls_30_vMemAccM_AsyncJobType jobType,
  Fls_30_vMemAccM_AddressType address,
  const uint8 *addressPtr,
  Fls_30_vMemAccM_LengthType length
);

/**********************************************************************************************************************
 * Fls_30_vMemAccM_FlsAccessor_ConvertJobResult
 *********************************************************************************************************************/
/*!
 * \brief       Convert result from vMem solution type to AUTOSAR type.
 * \details     From vMemAccM_JobResultType to MemIf_JobResultType.
 * \param[in]   resultOfvMemAccMJob: vMem solution job result
 * \return      jobResult: AUTOSAR
 * \pre         -
 * \context     TASK
 * \reentrant   TRUE
 * \synchronous TRUE
 */
FUNC(MemIf_JobResultType, FLS_30_VMEMACCM_CODE) Fls_30_vMemAccM_FlsAccessor_ConvertJobResult
(
  vMemAccM_JobResultType resultOfvMemAccMJob
);
                                                                             
/**********************************************************************************************************************
 * Fls_30_vMemAccM_FlsAccessor_GetJobResult
 *********************************************************************************************************************/
/*!
 * \brief       Requests result of the current job from lower layer.
 * \details     -
 * \return      jobResult of the current job
 * \pre         -
 * \context     TASK
 * \reentrant   TRUE
 * \synchronous TRUE
 */
FUNC(MemIf_JobResultType, FLS_30_VMEMACCM_CODE) Fls_30_vMemAccM_FlsAccessor_GetJobResult(void);


/**********************************************************************************************************************
 * Fls_30_vMemAccM_FlsAccessor_Cancel
 *********************************************************************************************************************/
/*!
 * \brief       Cancels the job which is currently processed from lower layer. 
 * \details     -
 * \pre         -
 * \context     TASK
 * \reentrant   TRUE
 * \synchronous TRUE
 */
FUNC(void, FLS_30_VMEMACCM_CODE) Fls_30_vMemAccM_FlsAccessor_Cancel(void);

#define FLS_30_VMEMACCM_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap  */

#endif /* FLS_30_VMEMACCM_FLSACCESSOR_H */

/**********************************************************************************************************************
 *  END OF FILE: Fls_30_vMemAccM_FlsAccessor.h
 *********************************************************************************************************************/
