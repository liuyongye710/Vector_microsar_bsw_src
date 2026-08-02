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
/*!        \file  Wdg_30_Sbc_LL.h
 *        \brief  Header file of Wdg_30_Sbc_LL.h
 *
 *      \details  This sub-component provides low level services to other sub-components. It manages hardware access of
 *                the module.
 *                This is an internal include file and shall not be included by other modules than Wdg_30_Sbc.
 *
 *********************************************************************************************************************/

#if !(defined WDG_30_SBC_LL_H)
#define WDG_30_SBC_LL_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "Wdg_30_Sbc_Cfg.h"


/**********************************************************************************************************************
 * GLOBAL MACROS
 *********************************************************************************************************************/
#define WDG_30_SBC_MODES_ALL       (0x7u)
#define WDG_30_SBC_MODES_FAST_SLOW (0x6u)
#define WDG_30_SBC_MODES_FAST_OFF  (0x5u)
#define WDG_30_SBC_MODES_FAST      (0x4u)


#define WDG_30_SBC_MODE_FAST       (0x4u)
#define WDG_30_SBC_MODE_SLOW       (0x2u)
#define WDG_30_SBC_MODE_OFF        (0x1u)


/*! /brief Bitfield that stores the supported modes */
#if (WDG_30_SBC_OFF_MODE_ALLOWED == STD_ON && WDG_30_SBC_SLOW_MODE_ALLOWED == STD_ON)
# define WDG_30_SBC_SUPPORTED_MODES WDG_30_SBC_MODES_ALL
#endif

#if (WDG_30_SBC_OFF_MODE_ALLOWED == STD_OFF && WDG_30_SBC_SLOW_MODE_ALLOWED == STD_ON)
# define WDG_30_SBC_SUPPORTED_MODES WDG_30_SBC_MODES_FAST_SLOW
#endif

#if (WDG_30_SBC_OFF_MODE_ALLOWED == STD_ON && WDG_30_SBC_SLOW_MODE_ALLOWED == STD_OFF)
# define WDG_30_SBC_SUPPORTED_MODES WDG_30_SBC_MODES_FAST_OFF
#endif

#if (WDG_30_SBC_OFF_MODE_ALLOWED == STD_OFF && WDG_30_SBC_SLOW_MODE_ALLOWED == STD_OFF) 
# define WDG_30_SBC_SUPPORTED_MODES WDG_30_SBC_MODES_FAST
#endif


#define WDG_30_SBC_IS_MODE_SUPPORTED(X) ((WDG_30_SBC_SUPPORTED_MODES & (X)) == (X)) /* PRQA S 3453 */ /* MD_MSR_19.6 */


/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
#define WDG_30_SBC_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 * Wdg_30_Sbc_LL_Init()
 *********************************************************************************************************************/
/*! \brief       Functions to initialize the sub-component Wdg_30_Sbc_LL
 *  \return      E_OK on success.
 *               E_NOT_OK otherwise.
 *  \pre         -
 *  \context     ANY
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \details     This function initializes the sub-component Wdg_30_Sbc_LL. It enables notifactions for the used 
 *               GptChannels and if configured performs an initial trigger by calling the trigger function of the 
 *               referenced Sbc module.
 *  \trace       CREQ-105559, DSGN-Wdg22909
 *********************************************************************************************************************/
FUNC(Std_ReturnType, WDG_30_SBC_CODE) Wdg_30_Sbc_LL_Init(void);


/**********************************************************************************************************************
 * Wdg_30_Sbc_LL_TriggerHw()
 *********************************************************************************************************************/
/*! \brief       Functions that triggers the watchdog hardware
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \details     This function triggers the watchdog hardware by calling the API of referenced Sbc module.
 *               It only gets called if the trigger condition is valid. 
 *  \trace       CREQ-105563, DSGN-Wdg22903
 *********************************************************************************************************************/
FUNC(void, WDG_30_SBC_CODE) Wdg_30_Sbc_LL_TriggerHw(void);


/**********************************************************************************************************************
 * Wdg_30_Sbc_LL_SetHwMode()
 *********************************************************************************************************************/
/*! \brief       Functions that sets the mode of watchdog hardware to requsted mode.
 *  \param[in]   Mode   Mode to which the watchdog hardware should be set
 *  \return      E_OK in case the mode change request was executed successfully.
 *               E_NOT_OK in case the mode change request was not successful.
 *  \pre         -
 *  \context     ANY
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \details     This function sets the mode of the watchdog hardware to requested mode by calling the API of referenced
 *               Sbc module. The function only gets called if the requested mode is reachable.
 *  \trace       CREQ-105560, DSGN-Wdg22902
 *********************************************************************************************************************/
FUNC(Std_ReturnType, WDG_30_SBC_CODE) Wdg_30_Sbc_LL_SetHwMode(WdgIf_ModeType Mode);


/**********************************************************************************************************************
 * Wdg_30_Sbc_LL_StartTriggerTimer()
 *********************************************************************************************************************/
/*! \brief       This function starts the timer that is used for watchdog trigger timing.
 *  \param[in]   Mode   Mode for which the timer should be started
 *  \pre         -
 *  \context     ANY
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \details     This function starts the timer that is used for watchdog trigger timing. It starts a configured
 *               GptChannel that calls the watchdog module cyclically.
 *  \trace       CREQ-105563, DSGN-Wdg22903
 *********************************************************************************************************************/
FUNC(void, WDG_30_SBC_CODE) Wdg_30_Sbc_LL_StartTriggerTimer(WdgIf_ModeType Mode);


#if (WDG_30_SBC_IS_MODE_SUPPORTED(WDG_30_SBC_MODE_SLOW) \
    || (WDG_30_SBC_IS_MODE_SUPPORTED(WDG_30_SBC_MODE_OFF) && WDG_30_SBC_DISABLE_ALLOWED == STD_ON))
/**********************************************************************************************************************
 * Wdg_30_Sbc_LL_StopTriggerTimer()
 *********************************************************************************************************************/
/*! \brief       This functions stops the timer that is used for watchdog trigger timing.
 *  \pre         -
 *  \context     ANY
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \details     This function stops the Gpt Channel that calles the watchdog module cyclically.
 *  \trace       CREQ-105563, DSGN-Wdg22903
 *********************************************************************************************************************/
FUNC(void, WDG_30_SBC_CODE) Wdg_30_Sbc_LL_StopTriggerTimer(void);
#endif

#define WDG_30_SBC_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* WDG_30_SBC_LL_H */

/**********************************************************************************************************************
 *  END OF FILE: Wdg_30_Sbc_LL.h
 *********************************************************************************************************************/
