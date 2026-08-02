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
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  vFotaH.h
 *    Component:  vFotaH header file
 *       Module:  -
 *    Generator:  -
 *
 *  Description: Main header file containing all public API implementations
 *  
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  01.00.00  2019-02-22  vishr                 Create Boilerplate
 *  01.01.00  2020-03-02  vishr   STORY-12126   Ota_vFotaH_Vector: Support Basic use case (Rollback) + Implement Beta Tests
 *            2020-03-09  vishr   ESCAN00105819 Module is not erased in case of moduleStart(sync)
 *            2020-03-16  vishr   SWAT-895      Ota_vFotaH_Vector: Finish missing component features
 *            2020-04-07  vishr   ESCAN00106083 vFotaH is reporting wrong resume address for finalized segments.
 *  01.02.00  2020-04-16  vishr   SWAT-667      Ota_vFotaH_Vector: QM Absicherung
 *  01.03.00  2020-05-14  vishr   SWAT-667      Ota_vFotaH_Vector: QM Absicherung
 *  01.03.01  2020-11-27  vishr   ESCAN00107624 Session change is not resetting incomplete download sequence.
 *  02.00.00  2021-05-05  vishr   SWAT-1337     Implement R26 adaptations in Vector FOTA Handler
 *            2021-05-10  vishr   ESCAN00109287 Segment remains unfinalized when unintended ECU reset happens just after download is finished.
 *  03.00.00  2021-09-27  vishr   SWAT-1507     vFotaH_Vector: Decompression for OTA Download (Vector)
 *********************************************************************************************************************/

#if !defined(VFOTAH_H)
#define VFOTAH_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "vFotaH_Types.h"
#include "vFotaH_Lcfg.h"
#include "vFotaH_PBcfg.h"
#include "vFotaH_Services.h"

#if (VFOTAH_DEV_ERROR_REPORT == STD_ON)
# include "Det.h"
#endif

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

#define OTA_VFOTAH_VECTOR_COMPONENT_VERSION             (0x0300u)
#define OTA_VFOTAH_VECTOR_COMPONENT_RELEASE_VERSION     (0x00u)

/* vendor and module identification */
#define VFOTAH_VENDOR_ID                                (30u)
#define VFOTAH_MODULE_ID                                (255u)

/* Instance Ids */
#if !defined (VFOTAH_INSTANCE_ID)
# define VFOTAH_INSTANCE_ID                      (uint8)(0x00u)
#endif

/* AUTOSAR Software Specification Version Information */
#define VFOTAH_AR_MAJOR_VERSION                         (0x04u)
#define VFOTAH_AR_MINOR_VERSION                         (0x03u)
#define VFOTAH_AR_PATCH_VERSION                         (0x00u)

/* Component Version Information */
#define VFOTAH_SW_MAJOR_VERSION (OTA_VFOTAH_VECTOR_COMPONENT_VERSION >> 8u)
#define VFOTAH_SW_MINOR_VERSION (OTA_VFOTAH_VECTOR_COMPONENT_VERSION & 0x00FFu)
#define VFOTAH_SW_PATCH_VERSION (OTA_VFOTAH_VECTOR_COMPONENT_RELEASE_VERSION)

/* Use case definition */
#define VFOTAH_ACTIVE_USE_CASE_BASIC                    (0x00u)
#define VFOTAH_ACTIVE_USE_CASE_EXTENDED                 (0x01u)

/* Restart definition */
#define VFOTAH_PERFORM_NO_RESTART                       (0x00u)
#define VFOTAH_PERFORM_RESTART                          (0x01u)

/* Defines for vFotaH Initialization States */
/*  - States (vFotaH_InitializationStateType): */
#define VFOTAH_INIT_STATE_UNINITIALIZED (0x00u) /*!< vFotaH initialization state: Not initialized (before calling vFotaH_Init). */
#define VFOTAH_INIT_STATE_INIT_PENDING (0x01u) /*!< vFotaH initialization state: Initialization pending  (after calling vFotaH_Init). */
#define VFOTAH_INIT_STATE_SHUTDOWN_PENDING (0x02u) /*!< vFotaH initialize state: shutdown (After shutdown has been requested). */
#define VFOTAH_INIT_STATE_INITIALIZED (0x03u) /*!< vFotaH initialization state: Initialized (After Resume Infos are persisted). */

#if !defined ( VFOTAH_E_ROLLBACK_NOT_ALLOWED )
# define VFOTAH_E_ROLLBACK_NOT_ALLOWED          (0x03u)
#endif

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

#if (VFOTAH_DEV_ERROR_REPORT == STD_ON)
# if !defined vFotaH_DetReportError
/* PRQA S 3453 2 */ /* MD_MSR_FctLikeMacro */
#  define vFotaH_DetReportError(api, err)                                                                               \
  (void) Det_ReportError(VFOTAH_MODULE_ID, VFOTAH_INSTANCE_ID, (api), (err)) 
# endif
#else
# if !defined vFotaH_DetReportError
#  define vFotaH_DetReportError(api, err)
# endif
#endif

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/
#define VFOTAH_START_SEC_VAR_ZERO_INIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e451 */

extern VAR(uint8, VFOTAH_VAR_ZERO_INIT) vFotaH_ActiveUseCase;

#define VFOTAH_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e451 */

#define VFOTAH_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e451 */

#if (VFOTAH_USE_INIT_POINTER == STD_ON)
extern P2CONST(vFotaH_ConfigType, AUTOMATIC, VFOTAH_PBCFG)  vFotaH_ConfigDataPtr;
#endif

#define VFOTAH_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e451 */

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
#define VFOTAH_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e451 */


/**********************************************************************************************************************
 *  vFotaH_InitializationSM_GetState()
 *********************************************************************************************************************/
/*! \fn          vFotaH_InitializationSM_GetState
 *  \brief       Returns the current state of the vFotaH initialization state machine.
 *  \details     -
 *  \return      Current state of vFotaH state machine.
 *  \context     TASK|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     states
 *********************************************************************************************************************/
FUNC(vFotaH_InitializationStateType, VFOTAH_CODE) vFotaH_InitializationSM_GetState(void);


/**********************************************************************************************************************
 *  vFotaH_InitializationSM_SetState()
 *********************************************************************************************************************/
/*! \fn          vFotaH_InitializationSM_SetState
 *  \brief       Sets the new initialization state.
 *  \details     -
 *  \context     TASK|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     states
 *********************************************************************************************************************/
FUNC(void, VFOTAH_CODE) vFotaH_InitializationSM_SetState(vFotaH_InitializationStateType NewState);

/**********************************************************************************************************************
 *  vFotaH_InitMemory()
 *********************************************************************************************************************/
/*! \fn          vFotaH_InitMemory
 *  \brief       Pre-initializes the vFotaH.
 *  \details     Initialization of data which has to be available before vFotaH_Init.
 *  \context     TASK|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     general
 *********************************************************************************************************************/
FUNC(void, VFOTAH_CODE) vFotaH_InitMemory(void);

/**********************************************************************************************************************
 *  vFotaH_Init()
 *********************************************************************************************************************/
/*! \fn          vFotaH_Init
 *  \brief       Initializes the vFotaH.
 *  \details     -
 *  \param[in]   ConfigPtr    Pointer to the configuration data.
 *  \context     TASK|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     general
 *********************************************************************************************************************/
FUNC(void, VFOTAH_CODE) vFotaH_Init(P2CONST(vFotaH_ConfigType, AUTOMATIC, VFOTAH_APPL_CONST) ConfigPtr);

#if (VFOTAH_VERSION_INFO_API == STD_ON)
/**********************************************************************************************************************
 *  vFotaH_GetVersionInfo()
 *********************************************************************************************************************/
/*! \fn          vFotaH_GetVersionInfo
 *  \brief       Returns the version information.
 *  \details     Returns version information, vendor ID and AUTOSAR module ID of the component.
 *  \param[out]  VersionInfo             Pointer to where to store the version information. Parameter must not be NULL.
 *  \context     TASK|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \config      This function is only available if VFOTAH_VERSION_INFO_API = STD_ON.
 *  \ingroup     general
 *********************************************************************************************************************/
FUNC(void, VFOTAH_CODE) vFotaH_GetVersionInfo(
  P2VAR(Std_VersionInfoType, AUTOMATIC, VFOTAH_APPL_VAR) VersionInfo);
#endif

/**********************************************************************************************************************
 *  vFotaH_MainFunction
 *********************************************************************************************************************/
/*!
 * \fn           void vFotaH_MainFunction(void)
 * \brief        Monitors and controls the continuous execution of the vFotaH state handling.
 * \details      -
 * \pre          -
 * \context      TASK|ISR
 * \reentrant    FALSE
 * \synchronous  TRUE
 * \ingroup      general
 *********************************************************************************************************************/
/* FUNC(void, VFOTAH_CODE) vFotaH_MainFunction(void); */


/**********************************************************************************************************************
*  vFotaH_Shutdown()
*********************************************************************************************************************/
/*! \fn          vFotaH_Shutdown
 *  \brief       Shuts down the vFotaH and the vSwUpdM.
 *  \details     -
 *  \param[in]   RestartSelect Select whether a restart shall be performed. Use either VFOTAH_PERFORM_RESTART to tell
 *                             the vFotaH to be available again or VFOTAH_PERFORM_NO_RESTART to prepare it for reset.
 *  \return      E_NOT_OK    An (DET) error occurred or the shutdown request is still pending.
 *  \return      E_OK        The shutdown request is executed successfully.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     general
*********************************************************************************************************************/
FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_Shutdown(uint8 RestartSelect);


#define VFOTAH_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e451 */


/* Justification for module-specific MISRA deviations:

MD_vFotaH_3218: rule 8.9
Reason:     The variable is located globally for the AUTOSAR memory mapping to be effective.
Risk:       None
Prevention: None

MD_vFotaH_3673/9: rule 8.13
Reason:     The type is given by another component, const not possible.
Risk:       None
Prevention: None

*/

#endif /* VFOTAH_H */

/**********************************************************************************************************************
 *  END OF FILE: vFotaH.h
 *********************************************************************************************************************/
