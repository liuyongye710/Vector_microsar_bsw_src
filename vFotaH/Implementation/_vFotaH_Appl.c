/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2021 by Vector Informatik GmbH. All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  _vFotaH_Appl.c
 *        \brief  vFotaH source file for application
 *
 *      \details
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *
 *  FILE VERSION
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the VERSION CHECK below.
 *********************************************************************************************************************/

#define VFOTAH_APPL_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "vFotaH_Appl.h"
#include "vSwUpdM.h"
#include "NvM.h"
#include "vSwUpdM_Appl.h"
#include "vFotaH_States.h"


/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 **********************************************************************************************************************/

#define VFOTAH_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e451 */

#define VFOTAH_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e451 */

#define VFOTAH_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e451 */

#define VFOTAH_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e451 */

/**********************************************************************************************************************
 *  GLOBAL DATA
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 **********************************************************************************************************************/

#define VFOTAH_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e451 */

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  vFotaH_Hlp_SwapFingerprint()
 *********************************************************************************************************************/
/*! \brief       Only required when no Bootloader is used to swap the Fingerprint between active and inactive.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         -
 *  \ingroup     vSwUpdMApplication
 *********************************************************************************************************************/
FUNC(void, VFOTAH_CODE) vFotaH_Hlp_SwapFingerprint(void)
{
  /* ----- Local Variables --------------------------------------------------------------------- */
  uint16_least i;
  uint16_least j;

  /* ----- Implementation ---------------------------------------------------------------------- */
  /* Swap Fingerprint */

  for (i = 0u; i < VFOTAH_NUMBER_OF_MODULES; i++)
  {
    for (j = 0u; j < VFOTAH_FINGERPRINT_SIZE; j++)
    {
      uint8 temp;

      temp = vFotaH_NvMInfoBlock[i].Fingerprint_Inactive[j];
      vFotaH_NvMInfoBlock[i].Fingerprint_Inactive[j] = vFotaH_NvMInfoBlock[i].Fingerprint_Active[j];
      vFotaH_NvMInfoBlock[i].Fingerprint_Active[j] = temp;
    }
  }
  (void)NvM_SetRamBlockStatus(vFotaH_GetFotaModuleInfoNvMSnv(), TRUE);
} /* vFotaH_Hlp_SwapFingerprint */

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 **********************************************************************************************************************/

/* Callbacks */
/**********************************************************************************************************************
  vFotaH_Appl_vSwUpdMConfirmation
**********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(void, VFOTAH_CODE) vFotaH_Appl_vSwUpdMConfirmation(
  vSwUpdM_ServiceIdType ConfirmedServiceId,
  Std_ReturnType Result)
{
  /* ----- Implementation ---------------------------------------------------------------------- */
  VFOTAH_DUMMY_STATEMENT(ConfirmedServiceId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */

  /* - Handle Switch-StateMachine. Do this synchronized with vSwUpdM: */
  if ((Result == E_OK) && (ConfirmedServiceId == VSWUPDM_SID_SHUTDOWN))
  {
    /* Shutdown possible, NvM_WriteAll pending */
  }
} /* vFotaH_Appl_vSwUpdMConfirmation */




/**********************************************************************************************************************
vFotaH_Appl_GetSoftwareVersion
**********************************************************************************************************************/
/*!
*
* Internal comment removed.
 *
 *
*/
FUNC(uint32, VFOTAH_CODE) vFotaH_Appl_GetSoftwareVersionAddr(vSwUpdM_ModuleIdType ModuleId)
{
  /* ----- Implementation ---------------------------------------------------------------------- */
  /* Return the address where the version information is located. Address is returned for each module seperately */
  if (ModuleId == vSwUpdMConf_vSwUpdMModule_vSwUpdMModule_LB0)
  {
    return 0x10000;
  }
  else
  {
    return 0x20000;
  }
} /* vFotaH_Appl_GetSoftwareVersion */


/**********************************************************************************************************************
vFotaH_Appl_CheckUpdateStart
**********************************************************************************************************************/
/*!
*
* Internal comment removed.
 *
 *
*/
FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_Appl_CheckUpdateStart(void)
{
  /* ----- Implementation ---------------------------------------------------------------------- */

  return E_OK;
} /* vFotaH_Appl_CheckUpdateStart */


/**********************************************************************************************************************
vFotaH_Appl_CheckProgrammingPreconditions
**********************************************************************************************************************/
/*!
*
* Internal comment removed.
 *
 *
*/
FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_Appl_CheckProgrammingPreconditions(void)
{
  /* ----- Implementation ---------------------------------------------------------------------- */

  return E_OK;
} /* vFotaH_Appl_CheckProgrammingPreconditions */


/**********************************************************************************************************************
vFotaH_Appl_CheckProgrammingDependencies
**********************************************************************************************************************/
/*!
*
* Internal comment removed.
 *
 *
*/
FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_Appl_CheckProgrammingDependencies(void)
{
  Std_ReturnType retVal;
  /* ----- Implementation ---------------------------------------------------------------------- */
  if (0 /* General Failure */)
  {
    retVal = VFOTAH_CHECK_PROGRAMMING_DEPENDENCIES_GENERAL_FAILURE;
  }
  else
  if (0 /* Hardware/Software incompatibility */)
  {
    retVal = VFOTAH_CHECK_PROGRAMMING_DEPENDENCIES_HWSW_INCOMP;
  }
  else
  if (0 /* Software/Software incompatibility */)
  {
    retVal = VFOTAH_CHECK_PROGRAMMING_DEPENDENCIES_SWSW_INCOMP;
  }
  else
  if (0 /* At least one module is missing */)
  {
    retVal = VFOTAH_CHECK_PROGRAMMING_DEPENDENCIES_BLOCK_MISSING;
  }
  else /* No issue detected, return success */
  {
    retVal = VFOTAH_CHECK_PROGRAMMING_DEPENDENCIES_SUCCESS;
  }

  return retVal;
} /* vFotaH_Appl_CheckProgrammingDependencies */


/**********************************************************************************************************************
vFotaH_Appl_RequestReset
**********************************************************************************************************************/
/*!
*
* Internal comment removed.
 *
 *
*/
FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_Appl_RequestReset(void)
{
  /* ----- Implementation ---------------------------------------------------------------------- */
  /* Request to perform a Reset after partition activation. Usually start in bootloader to perform the switch */
  return E_OK;
} /* vFotaH_Appl_Init */



/**********************************************************************************************************************
  vFotaH_Appl_Init
**********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(void, VFOTAH_CODE) vFotaH_Appl_Init(void)
{
  /* ----- Implementation ---------------------------------------------------------------------- */
} /* vFotaH_Appl_Init */


/**********************************************************************************************************************
 * vFotaH_Appl_MainFunction
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(void, VFOTAH_CODE) vFotaH_Appl_MainFunction(void)
{
  /* ----- Local Variables --------------------------------------------------------------------- */

  /* ----- Implementation ---------------------------------------------------------------------- */

} /* vFotaH_Appl_MainFunction */

#define VFOTAH_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e451 */

/**********************************************************************************************************************
 *  END OF FILE: vFotaH_Appl.c
 *********************************************************************************************************************/
