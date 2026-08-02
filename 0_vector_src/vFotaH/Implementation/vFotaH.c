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
/*        \file   vFotaH.c
 *        \brief  vFotaH source file
 *
 *      \details  Main source file containing all public API implementations
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

#define VFOTAH_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "SchM_vFotaH.h"
#include "vFotaH.h"
#include "vFotaH_Priv.h"
#include "vFotaH_States.h"
#include "vFotaH_vSwUpdM.h"
#include "vFotaH_Appl.h"
#include "vSwUpdM.h"

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/
/* vendor specific version information is BCD coded */
#if ((VFOTAH_SW_MAJOR_VERSION != (0x03)) || (VFOTAH_SW_MINOR_VERSION != (0x00)) || (VFOTAH_SW_PATCH_VERSION != (0x00)))
# error "Vendor specific version numbers of vFotaH.c and vFotaH.h are inconsistent"
#endif

/* AUTOSAR version information check has to match definition in header file */
#if ((VFOTAH_AR_MAJOR_VERSION != (0x04)) || (VFOTAH_AR_MINOR_VERSION != (0x03)) || (VFOTAH_AR_PATCH_VERSION != (0x00)))
# error "AUTOSAR Specification Version numbers of vFotaH.c and vFotaH.h are inconsistent!"
#endif

/* versions of all included header files shall be checked, configuration is just an example */
#if ((VFOTAH_CFG_MAJOR_VERSION != (0x01)) || (VFOTAH_CFG_MINOR_VERSION != (0x03)))
# error "Version numbers of vFotaH.c and vFotaH_Cfg.h are inconsistent!"
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

/**********************************************************************************************************************
 *  GLOBAL DATA
 **********************************************************************************************************************/
#define VFOTAH_START_SEC_VAR_ZERO_INIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e451 */

VFOTAH_LOCAL VAR(vFotaH_InitializationStateType, VFOTAH_VAR_ZERO_INIT) vFotaH_InitializationState_Current = VFOTAH_INIT_STATE_UNINITIALIZED; /*!< vFotaH initialization state: Current state. */
/* PRQA S 1514 1 */ /* MD_vFotaH_1514 */

VAR(uint8, VFOTAH_VAR_ZERO_INIT) vFotaH_ActiveUseCase = VFOTAH_ACTIVE_USE_CASE_BASIC; /*!< 
 * Active use case:
 *   Type for the active use case; the extended (3 partitions, with external
 *   flash) or the basic (2 partitions, all in internal flash). */

#define VFOTAH_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e451 */


#define VFOTAH_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e451 */

#if (VFOTAH_USE_INIT_POINTER == STD_ON)
P2CONST(vFotaH_ConfigType, AUTOMATIC, VFOTAH_PBCFG) vFotaH_ConfigDataPtr;
#endif

#define VFOTAH_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e451 */


/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 **********************************************************************************************************************/
#define VFOTAH_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e451 */

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 **********************************************************************************************************************/

/*
 *  Initialization State APIs
 */
/**********************************************************************************************************************
 * vFotaH_InitializationSM_GetState
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(vFotaH_InitializationStateType, VFOTAH_CODE) vFotaH_InitializationSM_GetState(void)
{
  /* ----- Implementation ---------------------------------------------------------------------- */
  /* #-- Return the current initialization state */
  return vFotaH_InitializationState_Current;
} /* vFotaH_InitializationSM_GetState */

/**********************************************************************************************************************
 * vFotaH_InitializationSM_SetState
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(void, VFOTAH_CODE) vFotaH_InitializationSM_SetState(vFotaH_InitializationStateType NewState)
{
  /* ----- Implementation ---------------------------------------------------------------------- */
  /* #-- Set the new initialization state */
  vFotaH_InitializationState_Current = NewState;
} /* vFotaH_InitializationSM_SetState */


/**********************************************************************************************************************
 * vFotaH_InitMemory
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(void, VFOTAH_CODE) vFotaH_InitMemory(void)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #-- Initializes memory variables to 0 if no startup code is available and call subsequent APIs. */
  vFotaH_ActiveUseCase = VFOTAH_ACTIVE_USE_CASE_BASIC;

  vFotaH_State_InitMemory();
  vFotaH_InitializationSM_SetState(VFOTAH_INIT_STATE_UNINITIALIZED);
  vFotaH_Serv_InitMemory();
} /* vFotaH_InitMemory */

/**********************************************************************************************************************
 * vFotaH_Init
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(void, VFOTAH_CODE) vFotaH_Init(P2CONST(vFotaH_ConfigType, AUTOMATIC, VFOTAH_APPL_CONST) ConfigPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal_vSwUpdM;
  vFotaH_ErrorCode errorId = VFOTAH_E_NO_ERROR;

#if (VFOTAH_USE_INIT_POINTER == STD_ON)
  vFotaH_ConfigDataPtr = ConfigPtr;
#else
  VFOTAH_DUMMY_STATEMENT(ConfigPtr); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e438 */
#endif

  /* ----- Development Error Checks ------------------------------------- */
  /* #-- If Dev Error Detect is enabled and vFotaH is already initialized, report an error. */
# if (VFOTAH_DEV_ERROR_DETECT == STD_ON)
  if (vFotaH_InitializationSM_GetState() != VFOTAH_INIT_STATE_UNINITIALIZED)
  {
    errorId = VFOTAH_E_ALREADY_INITIALIZED;
  }
#  if (VFOTAH_USE_INIT_POINTER == STD_ON)
  else
  if (ConfigPtr == NULL_PTR)
  {
    errorId = VFOTAH_E_INV_POINTER;
  }
#  endif
  /* #-- Otherwise, execute the initialization. */
  else
# endif
  /* ----- Implementation ----------------------------------------------- */
  {
    /* #-- Triggers initialization; If vSwUpdM reports an error, trigger a DET error. */
    vFotaH_vSwUpdMInit();
    vFotaH_Serv_PreInit();
    vFotaH_InitializationSM_SetState(VFOTAH_INIT_STATE_INIT_PENDING);
    retVal_vSwUpdM = vSwUpdM_Start();

    /* #-- If an error occured by restoring the FOTA state or starting the vSwUpdM, report an DET error. */
    if (retVal_vSwUpdM != E_OK) /* Only OK allowed. */
    {
      errorId = VFOTAH_E_INV_CONFIG;
    }
  }

  /* ----- Development Error Report --------------------------------------- */
# if (VFOTAH_DEV_ERROR_REPORT == STD_ON)
  if (errorId != VFOTAH_E_NO_ERROR)
  {
    vFotaH_DetReportError(VFOTAH_SID_INIT, errorId);
  }
# else
  VFOTAH_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e438 */
# endif
} /* vFotaH_Init */

#if (VFOTAH_VERSION_INFO_API == STD_ON)
/**********************************************************************************************************************
 *  vFotaH_GetVersionInfo()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, VFOTAH_CODE) vFotaH_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, VFOTAH_APPL_VAR) VersionInfo)
{
  /* ----- Local Variables ---------------------------------------------- */
  vFotaH_ErrorCode errorId = VFOTAH_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 If Dev Error Detect is enabled and the version pointer is invalid, report an error. */
# if (VFOTAH_DEV_ERROR_DETECT == STD_ON)
  if (VersionInfo == NULL_PTR)
  {
    errorId = VFOTAH_E_INV_POINTER;
  }
  /* #20 Otherwise, set the version info accordingly. */
  else
# endif
  /* ----- Implementation ----------------------------------------------- */
  {
    VersionInfo->vendorID         = (VFOTAH_VENDOR_ID);
    VersionInfo->moduleID         = (VFOTAH_MODULE_ID);
    VersionInfo->sw_major_version = (uint8)(VFOTAH_SW_MAJOR_VERSION);
    VersionInfo->sw_minor_version = (uint8)(VFOTAH_SW_MINOR_VERSION);
    VersionInfo->sw_patch_version = (uint8)(VFOTAH_SW_PATCH_VERSION);
  }

  /* ----- Development Error Report --------------------------------------- */
# if (VFOTAH_DEV_ERROR_REPORT == STD_ON)
  if (errorId != VFOTAH_E_NO_ERROR)
  {
    vFotaH_DetReportError(VFOTAH_SID_GET_VERSION_INFO, errorId);
  }
# else
  VFOTAH_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e438 */
# endif
} /* vFotaH_GetVersionInfo */
#endif /* (VFOTAH_VERSION_INFO_API == STD_ON) */

/***********************************************************************************************************************
 *  vFotaH_MainFunction
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, VFOTAH_CODE) vFotaH_MainFunction(void)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 If the vFotaH is still not initialized, handle it. */
  if (vFotaH_InitializationSM_GetState() != VFOTAH_INIT_STATE_INITIALIZED)
  {
    vFotaH_State_HandleInitialization();
  }
  /* #20 Otherwise, handle frequent checks. */
  else
  {
    /* #90 Call the cyclic occurring unit MainFunctions. */
    vFotaH_ServicesMainFunction();
    vFotaH_Appl_MainFunction();
  }
} /* vFotaH_MainFunction */


/***********************************************************************************************************************
 *  vFotaH_Shutdown
**********************************************************************************************************************/
/*!
*
* Internal comment removed.
 *
 *
*/
FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_Shutdown(uint8 RestartSelect)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  vFotaH_InitializationStateType initState = vFotaH_InitializationSM_GetState();

  /* ----- Implementation ----------------------------------------------- */
  if (initState == VFOTAH_INIT_STATE_INITIALIZED)
  {
    /* #10 We go back to initialized state via vSwUpdM_Start again in the regular handler. */
    vFotaH_InitializationSM_SetState(VFOTAH_INIT_STATE_SHUTDOWN_PENDING);
    vFotaH_vSwUpdMReset();
    retVal = vFotaH_vSwUpdMShutdown(RestartSelect);
  }

  return retVal;
} /* vFotaH_Shutdown */


#define VFOTAH_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e451 */

/**********************************************************************************************************************
 *  END OF FILE: vFotaH.c
 *********************************************************************************************************************/
