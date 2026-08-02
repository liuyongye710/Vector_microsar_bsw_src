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
/*!        \file  Fls_30_vMemAccM_Cbk.h
 *        \brief  Fls_30_vMemAccM callback header file
 *      \details  This file declares callback function Fls_30_vMemAccM_JobNotification.
 *                Callbacks are public, i.e. they will be called from outside of the Fls_30_vMemAccM - usually vMemAccM.
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *********************************************************************************************************************/

#if (!defined FLS_30_VMEMACCM_CBK_H)
#define FLS_30_VMEMACCM_CBK_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "Fls_30_vMemAccM_Cfg.h"
# include "vMemAccM_Types.h"

# if (FLS_30_VMEMACCM_POLLING_MODE == STD_OFF)

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
# define FLS_30_VMEMACCM_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 * Fls_30_vMemAccM_JobNotification
 *********************************************************************************************************************/
/*!
 * \brief Current running fls job will be finished or next splitted write job step will be forwarded to vMemAccM.
 * \details It will set the current pending job result to VMEMACCM_JOB_OK or to corresponding error result.
 * \param[in]   AddressAreaId  AddressAreaId of the finished job
 * \param[in]   Result         Job result of the vMemAccM job
 * \pre         -
 * \context TASK
 * \reentrant FALSE
 * \synchronous TRUE
 */
extern FUNC(void, FLS_30_VMEMACCM_CODE) Fls_30_vMemAccM_JobNotification
(
  vMemAccM_AddressAreaIdType AddressAreaId,
  vMemAccM_JobResultType Result
);

# define FLS_30_VMEMACCM_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

# endif /* (FLS_30_VMEMACCM_POLLING_MODE == STD_OFF) */

#endif /* FLS_30_VMEMACCM_CBK_H */

/**********************************************************************************************************************
 *  END OF FILE: Fls_30_vMemAccM_Cbk.h
 *********************************************************************************************************************/
 


