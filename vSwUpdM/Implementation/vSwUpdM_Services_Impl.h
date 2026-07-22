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
/*!        \file  vSwUpdM_Services_Impl.h
 *        \brief  vSwUpdM_Services implementation header file
 *      \details  vSwUpdM_Services subcomponent public inline implementations.
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's main header file.
 *
 *  FILE VERSION
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's main header file vSwUpdM.h.
 *********************************************************************************************************************/

#if !defined (VSWUPDM_SERVICES_IMPL_H)
# define VSWUPDM_SERVICES_IMPL_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
/* Services interface header */
#include "vSwUpdM_Services_If.h"

/* Other MultipleUnits used by Services_Impl (Prefer smallest set required, i.e. prefer _Types over _If over _Impl) */
#include "vSwUpdM_Priv.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/
#define VSWUPDM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define VSWUPDM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define VSWUPDM_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

extern VAR(uint8, VSWUPDM_APPL_DATA)   vSwUpdM_SrvcRouting_NumberOfPendingResponses;                               /* PRQA S 3218 */ /* MD_vSwUpdM_Rule8.9_3218_FileScope */

#define VSWUPDM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/
# define VSWUPDM_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 * vSwUpdM_Init_InitPipelinedProgramming
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_Init_InitPipelinedProgramming(void) /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
{
  /* ----- Implementation ------------------------------------------------- */
  /* #10 Set all pipelined programming attributes to default values. */
  vSwUpdM_PipelinedProgramming.State = VSWUPDM_PIPELINED_STATE_IDLE;
  vSwUpdM_PipelinedProgramming.PreviousWriteResult = E_OK;
} /* vSwUpdM_Init_InitPipelinedProgramming */

/**********************************************************************************************************************
 * vSwUpdM_SrvcRouting_GetNumberOfPendingResponses
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(uint8, VSWUPDM_CODE) vSwUpdM_SrvcRouting_GetNumberOfPendingResponses(void) /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
{
  /* ----- Implementation ------------------------------------------------- */
  return vSwUpdM_SrvcRouting_NumberOfPendingResponses;
} /* vSwUpdM_SrvcRouting_GetNumberOfPendingResponses */


# define VSWUPDM_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* VSWUPDM_SERVICES_IMPL_H */

/**********************************************************************************************************************
 *  END OF FILE: vSwUpdM_Services_Impl.h
 *********************************************************************************************************************/
