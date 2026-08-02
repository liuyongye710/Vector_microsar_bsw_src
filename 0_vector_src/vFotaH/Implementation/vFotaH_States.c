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
/*        \file  vFotaH_States.c
 *        \brief  vFotaH source file for state handling
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

#define VFOTAH_STATES_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "vFotaH_Priv.h"
#include "vFotaH_States.h"
#include "vFotaH_Services.h"
#include "vFotaH_vSwUpdM.h"
#include "SchM_vFotaH.h"

#include "NvM.h"
#include "vSwUpdM.h"

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/
/* vendor specific version information is BCD coded */
#if ((VFOTAH_SW_MAJOR_VERSION != (0x03)) || (VFOTAH_SW_MINOR_VERSION != (0x00)) || (VFOTAH_SW_PATCH_VERSION != (0x00)))
# error "Vendor specific version numbers of vFotaH.c and vFotaH.h are inconsistent"
#endif

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

#define VFOTAH_START_SEC_VAR_ZERO_INIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e451 */

VFOTAH_LOCAL VAR(boolean, VFOTAH_VAR_ZERO_INIT) vFotaH_IsvSwUpdMInitialized = FALSE;

#define VFOTAH_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED
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


/*
 *  State APIs
 */
/**********************************************************************************************************************
 * vFotaH_State_InitMemory
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(void, VFOTAH_CODE) vFotaH_State_InitMemory(void)
{
  /* ----- Implementation ---------------------------------------------------------------------- */
  vFotaH_IsvSwUpdMInitialized = FALSE;
} /* vFotaH_State_InitMemory */


/**********************************************************************************************************************
 * vFotaH_State_vSwUpdMInitNotification
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(void, VFOTAH_CODE) vFotaH_State_vSwUpdMInitNotification(void)
{
  /* ----- Implementation ---------------------------------------------------------------------- */
  vFotaH_IsvSwUpdMInitialized = TRUE;
} /* vFotaH_State_vSwUpdMInitNotification */


/**********************************************************************************************************************
* vFotaH_State_vSwUpdMInitRestart
**********************************************************************************************************************/
/*!
*
* Internal comment removed.
 *
 *
*/
FUNC(void, VFOTAH_CODE) vFotaH_State_vSwUpdMInitRestart(void)
{
  /* ----- Implementation ---------------------------------------------------------------------- */
  vFotaH_IsvSwUpdMInitialized = FALSE;
  vFotaH_InitializationSM_SetState(VFOTAH_INIT_STATE_INIT_PENDING);
} /* vFotaH_State_vSwUpdMInitNotification */



/**********************************************************************************************************************
 * vFotaH_State_HandleInitialization
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(void, VFOTAH_CODE) vFotaH_State_HandleInitialization(void)
{
  /* ----- Implementation ---------------------------------------------------------------------- */
  /* #-- Checks if the initialization is pending and ready to be performed.
   *       If ready, the final initialization steps are performed. */
  if (vFotaH_IsvSwUpdMInitialized == TRUE)
  {
    if (vFotaH_vSwUpdMIsBasicUseCase() == FALSE)
    {
      vFotaH_ActiveUseCase = VFOTAH_ACTIVE_USE_CASE_EXTENDED;
    }

    if (vFotaH_Serv_Init() == E_OK)
    {
      vFotaH_InitializationSM_SetState(VFOTAH_INIT_STATE_INITIALIZED);
      vFotaH_IsvSwUpdMInitialized = FALSE;
    }
  }
} /* vFotaH_State_HandleInitialization */


#define VFOTAH_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e451 */

/**********************************************************************************************************************
 *  END OF FILE: vFotaH_States.c
 *********************************************************************************************************************/
