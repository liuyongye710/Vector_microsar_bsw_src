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
/*!        \file  vSwUpdM_SrvcUpperLayer_If.h
 *        \brief  vSwUpdM_SrvcUpperLayer unit interface header file
 *      \details  Interface provided by the vSwUpdM_SrvcUpperLayer unit.
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

#if !defined (VSWUPDM_SRVCUPPERLAYER_IF_H)
# define VSWUPDM_SRVCUPPERLAYER_IF_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
/* SrvcUpperLayer types header */
#include "vSwUpdM_SrvcUpperLayer_Types.h"

/* Interface header of containing MultipleUnit */
#include "vSwUpdM_Services_If.h"

/* Other MultipleUnits used by SrvcUpperLayer_If (Prefer smallest set required, i.e. prefer _Types over _If) */

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

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
# define VSWUPDM_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*!
 * Internal comment removed.
 *
 *
 */
/**********************************************************************************************************************
 *  vSwUpdM_UlConfirmation()
 *********************************************************************************************************************/
/*! \brief          Trigger upper-layer confirmation function.
 *  \details        Will call confirmation function of upper-layer when necessary.
 *  \param[in]      ConfirmationService   Service ID passed to confirmation function.
 *  \param[in]      Source                Source node of the request which is confirmed here.
 *                                        When VSWUPDM_SID_NONE is passed, confirmation function will not be called.
 *  \param[in]      Result                Result code of service.
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *  \ingroup        general
 *********************************************************************************************************************/
FUNC(void, VSWUPDM_CODE) vSwUpdM_UlConfirmation(
  vSwUpdM_ServiceIdType ConfirmationService,
  vSwUpdM_NodeIterType Source,
  Std_ReturnType Result);

# define VSWUPDM_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* VSWUPDM_SRVCUPPERLAYER_IF_H */

/**********************************************************************************************************************
 *  END OF FILE: vSwUpdM_SrvcUpperLayer_If.h
 *********************************************************************************************************************/
