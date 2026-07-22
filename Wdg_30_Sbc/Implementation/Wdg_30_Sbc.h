/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2016 by Vector Informatik GmbH.                                              All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/*!        \file  Wdg_30_Sbc.h
 *        \brief  Wdg_30_Sbc header file
 *
 *      \details  This component is a watchdog driver.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  AUTHOR IDENTITY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Name                          Initials      Company
 *  -------------------------------------------------------------------------------------------------------------------
 *  Matthias Scheid               virmid        Vector Informatik GmbH
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  2.00.00  2014-10-22   virmid  -             Initial version
 *  2.00.01  2015-01-22   virmid  ESCAN00080749 Immediately invalidate TriggerCondition when timeout param is 0
 *  2.01.00  2015-02-06   virmid  ESCAN00081092 Add ASR3 compatibility mode
 *  2.01.01  2015-09-01   virmid  ESCAN00084928 Write correct version info in ASR3 compatibility mode
 *  2.01.02  2015-09-16   virmid  ESCAN00085282 Renamed MemMep section makers
 *                        virmid  ESCAN00085286 Removed DET-check of preprocessor defined values
 *  3.00.00  2016-01-13   virmid  -             Development according to SafeBSW process
 *  3.01.00  2016-05-19   virmid  ESCAN00088917 Update implementation to DrvWd__coreAsr 3.01.00
 *********************************************************************************************************************/


#if !(defined WDG_30_SBC_H)
#define WDG_30_SBC_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Wdg_30_Sbc_Cfg.h"
#include "SchM_Wdg_30_Sbc.h"


/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/* ----- vendor, module and instance identification ----- */
# define WDG_30_SBC_VENDOR_ID                           (30u)
# define WDG_30_SBC_MODULE_ID                           (0x66u)
# define WDG_30_SBC_INSTANCE_ID                         (0u)

/* ----- AUTOSAR Software specification version information ----- */
# define WDG_30_SBC_AR_RELEASE_MAJOR_VERSION            (0x04u)
# define WDG_30_SBC_AR_RELEASE_MINOR_VERSION            (0x00u)
# define WDG_30_SBC_AR_RELEASE_REVISION_VERSION         (0x03u)

/* ----- Component version information ----- */
# define WDG_30_SBC_SW_MAJOR_VERSION                    (2u)
# define WDG_30_SBC_SW_MINOR_VERSION                    (1u)
# define WDG_30_SBC_SW_PATCH_VERSION                    (0u)

/* ----- API service IDs ----- */
# define WDG_30_SBC_SID_INIT                            (0x00u)
# define WDG_30_SBC_SID_SET_MODE                        (0x01u)
# define WDG_30_SBC_SID_SET_TRIGGER_CONDITION           (0x03u)
# define WDG_30_SBC_SID_GET_VERSION_INFO                (0x04u)
# define WDG_30_SBC_SID_CBK_GPT_TRIGGER                 (0x05u)
# define WDG_30_SBC_SID_TRIGGER                         (0x07u)

/* ----- Error codes ----- */
#define WDG_30_SBC_E_NO_ERROR                           (0x00u)
#define WDG_30_SBC_E_DRIVER_STATE                       (0x10u)
#define WDG_30_SBC_E_PARAM_MODE                         (0x11u)
#define WDG_30_SBC_E_PARAM_CONFIG                       (0x12u)
#define WDG_30_SBC_E_PARAM_TIMEOUT                      (0x13u)
#define WDG_30_SBC_E_PARAM_POINTER                      (0x14u)

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/
/*! critical section macros */
#if (STD_OFF == WDG_30_SBC_ASR3X_COMPATIBILITY)
/*! ASR4 project/ environment */
# define Wdg_30_Sbc_EnterCritical(Section)              SchM_Enter_Wdg_30_Sbc_##Section() /* PRQA S 0342 */ /* MD_Wdg_30_Sbc_342 */
# define Wdg_30_Sbc_ExitCritical(Section)               SchM_Exit_Wdg_30_Sbc_##Section() /* PRQA S 0342 */ /* MD_Wdg_30_Sbc_342 */
#else
/*! ASR3 project/ environment */
# define Wdg_30_Sbc_EnterCritical(Section)              SchM_Enter_Wdg_30_Sbc(Section) /* PRQA S 3453 */ /* MD_MSR_19.7 */
# define Wdg_30_Sbc_ExitCritical(Section)               SchM_Exit_Wdg_30_Sbc(Section) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#endif


/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
#define WDG_30_SBC_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 * Wdg_30_Sbc_Init()
 *********************************************************************************************************************/
/*! \brief       Initialization function
 *  \param[in]   ConfigPtr   Configuration structure for initializing the module
 *  \pre         The module is uninitialized
 *  \context     ANY
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \details     This function initializes the module Wdg_30_Sbc. It initializes all variables and sets the module state to
 *               initialized.
 *  \trace       CREQ-105559, DSGN-Wdg22909
 *********************************************************************************************************************/
FUNC(void, WDG_30_SBC_CODE) Wdg_30_Sbc_Init(P2CONST(Wdg_30_Sbc_ConfigType, AUTOMATIC, WDG_30_SBC_CONST) ConfigPtr);

/**********************************************************************************************************************
 * Wdg_30_Sbc_SetTriggerCondition()
 *********************************************************************************************************************/
/*! \brief       Sets the watchdog timeout
 *  \param[in]   timeout     Duration of timeout period in milliseconds
 *  \pre         The module is initialized
 *  \context     ANY
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \details     This API is used by WdgIf to set the timeout period in which the watchdog driver is allowed to trigger
 *               the watchdog hardware.
 *               In case the value 0 is passed as timeout parameter the module will cause a reset as soon as possible.
 *  \trace       CREQ-105561, DSGN-Wdg22900
 *********************************************************************************************************************/
FUNC(void, WDG_30_SBC_CODE) Wdg_30_Sbc_SetTriggerCondition(uint16 timeout);

/**********************************************************************************************************************
 * Wdg_30_Sbc_SetMode()
 *********************************************************************************************************************/
/*! \brief       Changes the mode of the watchdog module / hardware
 *  \param[in]   Mode     Mode to which the module / hardware should be set
 *  \return      E_OK - Mode switch executed successfully
 *  \return      E_NOT_OK - Mode switch failed
 *  \pre         The module is initialized
 *  \context     ANY
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \details     This API is used by WdgIf to set the mode of the watchdog to a given mode.
 *  \note        In case a the mode change of the hardware fails the internal mode remains unchanged and the mode of
 *               the hardware is undefined.
 *  \trace       CREQ-105560, CREQ-106194, CREQ-106195, CREQ-106196, DSGN-Wdg22902, DSGN-Wdg22983
 *********************************************************************************************************************/
FUNC(Std_ReturnType, WDG_30_SBC_CODE) Wdg_30_Sbc_SetMode(WdgIf_ModeType Mode);

/**********************************************************************************************************************
 * Wdg_30_Sbc_GetVersionInfo()
 *********************************************************************************************************************/
/*! \brief       Returns the version information of this module
 *  \param[out]  versioninfo    Pointer to where to store the version information
 *  \pre         The module is initialized
 *  \config      WDG_30_SBC_VERSION_INFO_API == STD_ON
 *  \context     ANY
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \details     This API returns version information, vendor ID and AUTOSAR module ID of the component. \n
 *               If ASR3 compatibility is enabled for this module also the instance id is returned. \n
 *               The values are decimal-coded. \n
 *               If the given output parameter is a NULL_PTR the API throws DET WDG_30_SBC_E_PARAM_VERSIONINFO.
 *  \trace       CREQ-105608
 *********************************************************************************************************************/
# if (WDG_30_SBC_VERSION_INFO_API == STD_ON)
FUNC(void, WDG_30_SBC_CODE) Wdg_30_Sbc_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, WDG_30_SBC_APPL_DATA) versioninfo);
# endif

/**********************************************************************************************************************
 * Wdg_30_Sbc_Trigger()
 *********************************************************************************************************************/
/*! \brief       Triggers the watchdog in ASR3 watchdog stacks
 *  \pre         ASR3 compatibility must be enabled
 *  \config      WDG_30_SBC_ASR3X_COMPATIBILITY == STD_ON
 *  \context     ANY
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \details     This API provides a wrapper-functionality that allows this module to be used in ASR3-conform watchdog
 *               stacks. It has to be called cyclically from WdgIf to reset the trigger condition with a configured
 *               timeout.
 *  \trace       DSGN-Wdg22984
 *********************************************************************************************************************/
# if (WDG_30_SBC_ASR3X_COMPATIBILITY == STD_ON)
FUNC(void, WDG_30_SBC_CODE) Wdg_30_Sbc_Trigger(void);
# endif

#define WDG_30_SBC_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*!
*\exclusivearea WDG_30_SBC_EXCLUSIVE_AREA_0
* Ensures consistency during mode change
* \protects Wdg_30_Sbc_Mode_currentMode, Wdg_30_Sbc_Timer_permissionCounter, mode consistency
* \usedin Wdg_30_Sbc_Mode_SetMode
* \exclude Wdg_30_Sbc_Mode_DoModeChange
* \length SHORT Hardware mode is changed, Timer is reconfigured.
*\endexclusivearea

*\exclusivearea WDG_30_SBC_EXCLUSIVE_AREA_1
* Ensures consistency during modification of trigger condition
* \protects Wdg_30_Sbc_TrgCnd_ConditionFlag, Wdg_30_Sbc_TrgCnd_ExpiredFlag
* \usedin Wdg_30_Sbc_TrgCnd_SetCondition, Wdg_30_Sbc_TrgCnd_ResetCondition, Wdg_30_Sbc_TrgCnd_InvalidateCondition
* \exclude All functions provided by sub-component Wdg_30_Sbc_TrgCnd
* \length SHORT Variables are set
*\endexclusivearea
*/

/* Justification for module-specific MISRA deviations:
MD_Wdg_30_Sbc_342:
Misra Rule 19.13
  Reason: Glue operator used to abstract AUTOSAR SchM access.
  Risk: Compiler does not support the glue operator.
  Prevention: Module supports only ANSI Compiler. Integration tests verify that the code compiles.
*/

#endif /* WDG_30_SBC_H */
/**********************************************************************************************************************
 *  END OF FILE: Wdg_30_Sbc.h
 *********************************************************************************************************************/
