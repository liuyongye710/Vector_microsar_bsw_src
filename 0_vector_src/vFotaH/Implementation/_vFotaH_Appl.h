/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2021 by Vector Informatik GmbH.                                                  All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**       \file   _vFotaH_Appl.h
 *        \brief  vFotaH application header file
 *
 *        \details
 *
 *********************************************************************************************************************/

/***********************************************************************************************************************
 *  REVISION HISTORY
 *  --------------------------------------------------------------------------------------------------------------------
 *  Refer to vFotaH.h.
 **********************************************************************************************************************/

#if !defined(VFOTAH_APPL_H)
#define VFOTAH_APPL_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "vFotaH_Types.h"
#include "vFotaH.h"


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
#define VFOTAH_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e451 */

#define VFOTAH_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e451 */

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
#define VFOTAH_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e451 */

/**********************************************************************************************************************
 *  vSwUpdM_Appl_WritePartitionInfoToNvm()
 *********************************************************************************************************************/
/*! \brief       Writes update partition information to NvM.
 *  \details     This API must be implemented by vSwUpdM in the vSwUpdM_Appl.c by the user.
 *  \return      E_OK               Write successful.
 *  \return      VSWUPDM_E_PENDING  Write pending.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         -
 *  \ingroup     vSwUpdMApplication
 *********************************************************************************************************************/
extern FUNC(Std_ReturnType, VFOTAH_CODE) vSwUpdM_Appl_WritePartitionInfoToNvm(void);

/**********************************************************************************************************************
 *  vFotaH_Appl_vSwUpdMConfirmation()
 *********************************************************************************************************************/
/*! \brief       Confirms the finalization of a request on vSwUpdM.
 *  \details     -
 *  \param[in]   ConfirmedServiceId    The vSwUpdM service id for which the confirmation occurred.
 *  \param[in]   Result                The result of the confirmation:
 *                                      - VFOTAH_RETVAL_OK: Request was performed successfully.
 *                                      - VFOTAH_RETVAL_NOT_OK: Request failed.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     application
 *********************************************************************************************************************/
FUNC(void, VFOTAH_CODE) vFotaH_Appl_vSwUpdMConfirmation(
  vSwUpdM_ServiceIdType ConfirmedServiceId,
  Std_ReturnType Result);

/**********************************************************************************************************************
*  vFotaH_Appl_GetSoftwareVersionAddr()
*********************************************************************************************************************/
/*! \brief         Get the software version number for an individual module.
 *  \details       Each Module contains a software version number. Its location is defined by this call-out.
 *  \param         ModuleId     The module id of the requested module version number.
 *  \return        address      Returns the virtual memory address of the software version number.
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 *  \ingroup       application
*********************************************************************************************************************/
FUNC(uint32, VFOTAH_CODE) vFotaH_Appl_GetSoftwareVersionAddr(vSwUpdM_ModuleIdType ModuleId);


/**********************************************************************************************************************
*  vFotaH_Appl_CheckUpdateStart()
*********************************************************************************************************************/
/*! \brief         Check during UpdateStart if it shall proceed.
 *  \details       Can be used to perform a check before download actually starts and prevent it should anything
 *                 be not ok.
 *  \return        E_OK        The conditions are ok.
 *  \return        E_NOT_OK    The conditions failed.
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 *  \ingroup       application
*********************************************************************************************************************/
FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_Appl_CheckUpdateStart(void);


/**********************************************************************************************************************
*  vFotaH_Appl_CheckProgrammingPreconditions()
*********************************************************************************************************************/
/*! \brief         Checks the programming preconditions.
 *  \details       The vehicle must be in a safe state before the software can be activated. This call-out checks
 *                 if this is given.
 *  \return        E_OK        The conditions are ok.
 *  \return        E_NOT_OK    The conditions failed.
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 *  \ingroup       application
*********************************************************************************************************************/
FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_Appl_CheckProgrammingPreconditions(void);


/**********************************************************************************************************************
*  vFotaH_Appl_CheckProgrammingDependencies()
*********************************************************************************************************************/
/*! \brief         Checks the programming dependencies.
 *  \details       Checks if all Modules are updated with correct software. Only then the new software can be activated.
 *  \return        VFOTAH_CHECK_PROGRAMMING_DEPENDENCIES_GENERAL_FAILURE     A general failure occured.
 *  \return        VFOTAH_CHECK_PROGRAMMING_DEPENDENCIES_HWSW_INCOMP         A hardware/software incompatibility occured.
 *  \return        VFOTAH_CHECK_PROGRAMMING_DEPENDENCIES_SWSW_INCOMP         A software/software incompatibility occured.
 *  \return        VFOTAH_CHECK_PROGRAMMING_DEPENDENCIES_BLOCK_MISSING       An block is missing, download incomplete.
 *  \return        VFOTAH_CHECK_PROGRAMMING_DEPENDENCIES_SUCCESS             All ok, software can be activated.
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 *  \ingroup       application
*********************************************************************************************************************/
FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_Appl_CheckProgrammingDependencies(void);


/**********************************************************************************************************************
 *  vFotaH_Appl_RequestReset()
 *********************************************************************************************************************/
/*! \brief         Request of a system Reset to start the FBL.
 *  \details       The bootloader is responsible to activate the new software. This call-out is called after Activate
 *                 request and triggers Bootloader start.
 *  \return        E_OK      The reset request has been accepted.
 *  \return        VFOTAH_E_PENDING  The reset request has been accepted and is pending.
 *  \return        E_NOT_OK  The reset request has been denied.
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 *  \ingroup       application
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_Appl_RequestReset(void);

/**********************************************************************************************************************
 *  vFotaH_Appl_Init()
 *********************************************************************************************************************/
/*! \brief         Initializes global variables of vFotaH_Appl.c.
 *  \details       -
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 *  \ingroup       application
 *********************************************************************************************************************/
FUNC(void, VFOTAH_CODE) vFotaH_Appl_Init(void);

/**********************************************************************************************************************
 *  vFotaH_Appl_MainFunction()
 *********************************************************************************************************************/
/*! \brief         Execute asynchronous actions.
 *  \details       -
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 *  \ingroup       application
 *********************************************************************************************************************/
FUNC(void, VFOTAH_CODE) vFotaH_Appl_MainFunction(void);

#define VFOTAH_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e451 */

#endif /* VFOTAH_APPL_H */

/**********************************************************************************************************************
 *  END OF FILE: vFotaH_Appl.h
 *********************************************************************************************************************/
