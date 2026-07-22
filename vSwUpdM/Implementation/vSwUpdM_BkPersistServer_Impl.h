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
/*!        \file  vSwUpdM_BkPersistServer_Impl.h
 *        \brief  vSwUpdM_BkPersistServer implementation header file
 *      \details  vSwUpdM_BkPersistServer subcomponent public inline implementations.
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

#if !defined (VSWUPDM_BKPERSISTSERVER_IMPL_H)
# define VSWUPDM_BKPERSISTSERVER_IMPL_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
/* BkPersistServer interface header */
#include "vSwUpdM_BkPersistServer_If.h"

/* Implementation header of containing MultipleUnit */
#include "vSwUpdM_Bookkeeper_Impl.h"

/* Other MultipleUnits used by BkPersistServer_Impl (Prefer smallest set required, i.e. prefer _Types over _If over _Impl) */

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

extern VAR(boolean, VSWUPDM_VAR_NOINIT) vSwUpdM_BkPersistServer_EventPending;
extern VAR(boolean, VSWUPDM_VAR_NOINIT) vSwUpdM_BkPersistServer_IsActive;

#define VSWUPDM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/
# define VSWUPDM_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 * vSwUpdM_BkPersistServer_NeedsExecution
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(boolean, VSWUPDM_CODE) vSwUpdM_BkPersistServer_NeedsExecution(void) /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
{
  boolean retVal = FALSE;

  if ((vSwUpdM_BkPersistServer_EventPending == TRUE) || (vSwUpdM_BkPersistServer_IsActive == TRUE))
  {
    retVal = TRUE;
  }
  return retVal;
} /* vSwUpdM_BkPersistServer_NeedsExecution */

# define VSWUPDM_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* VSWUPDM_BKPERSISTSERVER_IMPL_H */

/**********************************************************************************************************************
 *  END OF FILE: vSwUpdM_BkPersistServer_Impl.h
 *********************************************************************************************************************/
