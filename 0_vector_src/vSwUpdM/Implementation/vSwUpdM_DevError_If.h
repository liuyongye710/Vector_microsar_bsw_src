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
/*!        \file  vSwUpdM_DevError_If.h
 *        \brief  vSwUpdM_DevError interface header file
 *      \details  Interface provided by the vSwUpdM_DevError subcomponent.
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

#if !defined (VSWUPDM_DEVERROR_IF_H)
# define VSWUPDM_DEVERROR_IF_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
/* DevError types header */
#include "vSwUpdM_DevError_Types.h"

/* Other MultipleUnits used by DevError_If (Prefer smallest set required, i.e. prefer _Types over _If) */
#include "vSwUpdM_Priv_Types.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/
#if !defined(VSWUPDM_DEVERROR_ASSERTEXTERNAL)
#define vSwUpdM_DevError_AssertFail(ErrorCode) vSwUpdM_DevError_AssertInternal((boolean)(1==0), (ErrorCode))
#define vSwUpdM_DevError_Assert(Condition, ErrorCode) vSwUpdM_DevError_AssertInternal((boolean)(Condition), (ErrorCode))
#endif

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
# define VSWUPDM_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  vSwUpdM_DevErrorAssert()
 *********************************************************************************************************************/
/*! \brief       general Assertion handling function.
 *  \details     -
 *  \param[in]   Condition
 *  \param[in]   ErrorCode
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     segment
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_DevError_AssertInternal(boolean Condition, vSwUpdM_DevError_AssertErrorCodeType ErrorCode);

# define VSWUPDM_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* VSWUPDM_DEVERROR_IF_H */

/**********************************************************************************************************************
 *  END OF FILE: vSwUpdM_DevError_If.h
 *********************************************************************************************************************/
