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
/*!        \file  Wdg_30_Sbc_Timer.h
 *        \brief  Header file of Wdg_30_Sbc_Timer
 *
 *      \details  This sub-component provides timing services to other sub-component.
 *                This is an internal include file and shall not be included by other modules than Wdg_30_Sbc.
 *
 *********************************************************************************************************************/

#if !(defined WDG_30_SBC_TIMER_H)
#define WDG_30_SBC_TIMER_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Wdg_30_Sbc_Cfg.h"
#include "Wdg_30_Sbc_LL.h"

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
#define WDG_30_SBC_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 * Wdg_30_Sbc_Timer_Init()
 *********************************************************************************************************************/
/*! \brief       Init function of sub-component Wdg_30_Sbc_Timer
 *  \pre         -
 *  \context     ANY
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \return      E_OK on success.
 *               E_NOT_OK otherwise.
 *  \details     This function is used to initialize the sub-component Wdg_30_Sbc_Timer
 *  \trace       CREQ-105559, DSGN-Wdg22909
 *********************************************************************************************************************/
FUNC(Std_ReturnType, WDG_30_SBC_CODE) Wdg_30_Sbc_Timer_Init(void);

/**********************************************************************************************************************
 * Wdg_30_Sbc_Timer_SetTimeout()
 *********************************************************************************************************************/
/*! \brief       This function sets the permission 
 *  \pre         -
 *  \param[in]   timeout       Time for which the triggering of the watchdog hardware is allowed
 *  \param[in]   targetMode    Mode for which the trigger condition should be set (Valid: WDGIF_FAST_MDOE, WDGIF_SLOW_MODE)
 *  \context     ANY
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \details     The function is used to set up the the permission counter according to the passed timeout value and targetMode.
 *  \trace       CREQ-105561, DSGN-Wdg22900
 *********************************************************************************************************************/
FUNC(void, WDG_30_SBC_CODE) Wdg_30_Sbc_Timer_SetTimeout(uint16 timeout, WdgIf_ModeType targetMode);

/**********************************************************************************************************************
 * Wdg_30_Sbc_Timer_TriggerCbk()
 *********************************************************************************************************************/
/*! \brief       This is the callback function for GPT "TriggerTimer"
 *  \pre         -
 *  \context     ANY
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \details     If the component is set to a running mode (WDGIF_FAST_MODE, WDGIF_SLOW_MODE) this function is called
 *               cyclically to update trigger condition and handle watchdog triggering.
 *  \trace       CREQ-105560, CREQ-105563, DSGN-Wdg22903, DSGN-Wdg22983
 *********************************************************************************************************************/
FUNC(void, WDG_30_SBC_CODE) Wdg_30_Sbc_Timer_TriggerCbk(void);

/**********************************************************************************************************************
 * Wdg_30_Sbc_Timer_SetTriggerTiming()
 *********************************************************************************************************************/
/*! \brief       This function sets the trigger timing for a requested mode.
 *  \pre         -
 *  \param[in]   targetMode    Mode to which the trigger timing should be adapted.
 *  \context     ANY
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \details     This function provides a service to other functions to set the trigger timing according a passed mode.
 *  \trace       CREQ-105563, CREQ-105560, DSGN-Wdg22902
 *********************************************************************************************************************/
FUNC(void, WDG_30_SBC_CODE) Wdg_30_Sbc_Timer_SetTriggerTiming(WdgIf_ModeType targetMode);

#define WDG_30_SBC_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* WDG_30_SBC_TIMER_H */
/**********************************************************************************************************************
 *  END OF FILE: Wdg_30_Sbc_Timer.h
 *********************************************************************************************************************/
