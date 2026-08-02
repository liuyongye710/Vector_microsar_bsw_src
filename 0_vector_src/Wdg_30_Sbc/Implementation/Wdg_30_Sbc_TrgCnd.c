/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2016 by Vector Informatik GmbH.                                                  All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/*!        \file  Wdg_30_Sbc_TrgCnd.c
 *        \brief  Implementation of sub-module Wdg_30_Sbc_TriggerCondition.
 *
 *      \details  This sub-module manages the trigger condition of the watchdog module.
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

#define WDG_30_SBC_SOURCE

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "Wdg_30_Sbc_TrgCnd.h"
#include "Wdg_30_Sbc_TrgCnd_Cbk.h"

#include "Wdg_30_Sbc_Timer.h"

#include "Wdg_30_Sbc.h"

/**********************************************************************************************************************
 * LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

#if !defined (WDG_30_SBC_LOCAL) /* COV_WDG_30_SBC_COMPATIBILITY */
# define WDG_30_SBC_LOCAL static
#endif

#if !defined (WDG_30_SBC_LOCAL_INLINE) /* COV_WDG_30_SBC_COMPATIBILITY */
# define WDG_30_SBC_LOCAL_INLINE LOCAL_INLINE
#endif

/**********************************************************************************************************************
 * LOCAL VARIABLES
 *********************************************************************************************************************/
#define WDG_30_SBC_START_SEC_VAR_CLEARED_8
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* /brief Variable to store the current value state of the TriggerCondition */
WDG_30_SBC_LOCAL VAR(boolean, WDG_30_SBC_VAR) Wdg_30_Sbc_TrgCnd_conditionFlag = FALSE;

/* /brief Variable to store the information if the TriggerCondition already is expired */
WDG_30_SBC_LOCAL VAR(boolean, WDG_30_SBC_VAR) Wdg_30_Sbc_TrgCnd_expiredFlag = FALSE;

#define WDG_30_SBC_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 * GLOBAL FUNCTIONS
 *********************************************************************************************************************/
#define WDG_30_SBC_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  Wdg_30_Sbc_TrgCnd_CheckCondition()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(boolean, WDG_30_SBC_CODE) Wdg_30_Sbc_TrgCnd_CheckCondition(void)
{
  /* #10 Return trigger condition */
  return Wdg_30_Sbc_TrgCnd_conditionFlag;
}

/**********************************************************************************************************************
 *  Wdg_30_Sbc_TrgCnd_InvalidateCondition()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, WDG_30_SBC_CODE) Wdg_30_Sbc_TrgCnd_InvalidateCondition(void)
{
  Wdg_30_Sbc_EnterCritical(WDG_30_SBC_EXCLUSIVE_AREA_1);
  /* >>> CRITICAL AREA START >>> */

  /* #10 Set expired flag */
  Wdg_30_Sbc_TrgCnd_expiredFlag = TRUE;

  /* #20 Delete condition flag */
  Wdg_30_Sbc_TrgCnd_conditionFlag = FALSE;

  /* <<< CRITICAL AREA START <<< */ 
  Wdg_30_Sbc_ExitCritical(WDG_30_SBC_EXCLUSIVE_AREA_1);
}

/**********************************************************************************************************************
 *  Wdg_30_Sbc_TrgCnd_SetCondition()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(void, WDG_30_SBC_CODE) Wdg_30_Sbc_TrgCnd_SetCondition(uint16 timeout, WdgIf_ModeType targetMode)
{

/* #10 If WDGIF_OFF_MODE is supported and disabling the watchdog is allowed */
#if(WDG_30_SBC_IS_MODE_SUPPORTED(WDG_30_SBC_MODE_OFF) && WDG_30_SBC_DISABLE_ALLOWED == STD_ON)
  /* #12 If requested mode is WDGIF_OFF_MODE, do nothing */
  if(targetMode == WDGIF_OFF_MODE) {
    /* Nothing to be done */
  }
  else 
#endif /* WDG_30_SBC_IS_MODE_SUPPORTED(WDG_30_SBC_MODE_OFF) && WDG_30_SBC_DISABLE_ALLOWED == STD_ON */
  /* #15 If timeout parameter equals 0 */
  if (timeout == 0)
  {
    /* #17 Invalidate trigger condition */
    Wdg_30_Sbc_TrgCnd_InvalidateCondition();
  }
  /* #20 If trigger condition did not expire yet */
  else if (Wdg_30_Sbc_TrgCnd_expiredFlag == FALSE)
  {
    Wdg_30_Sbc_EnterCritical(WDG_30_SBC_EXCLUSIVE_AREA_1);
    /* >>> CRITICAL AREA START >>> */

    /* #22 Set trigger condition to valid */
    Wdg_30_Sbc_TrgCnd_conditionFlag = TRUE;

    /* #24 Setup permission timer */
    Wdg_30_Sbc_Timer_SetTimeout(timeout, targetMode);

    /* <<< CRITICAL AREA START <<< */ 
    Wdg_30_Sbc_ExitCritical(WDG_30_SBC_EXCLUSIVE_AREA_1);
  }
  else
  {
    /* Nothing to be done */
  }
}

#if(WDG_30_SBC_IS_MODE_SUPPORTED(WDG_30_SBC_MODE_OFF) && WDG_30_SBC_DISABLE_ALLOWED == STD_ON)
/**********************************************************************************************************************
 *  Wdg_30_Sbc_TrgCnd_resetCondition()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, WDG_30_SBC_CODE) Wdg_30_Sbc_TrgCnd_ResetCondition(void)
{
  Wdg_30_Sbc_EnterCritical(WDG_30_SBC_EXCLUSIVE_AREA_1);
  /* >>> CRITICAL AREA START >>> */

  /* #10 Set Wdg_30_Sbc_TrgCnd_ConditionFlag to FALSE */
  Wdg_30_Sbc_TrgCnd_conditionFlag = FALSE;

  /* <<< CRITICAL AREA START <<< */ 
  Wdg_30_Sbc_ExitCritical(WDG_30_SBC_EXCLUSIVE_AREA_1);
}
#endif /* (WDG_30_SBC_IS_MODE_SUPPORTED(WDG_30_SBC_MODE_OFF) && WDG_30_SBC_DISABLE_ALLOWED == STD_ON) */


#define WDG_30_SBC_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* START_COVERAGE_JUSTIFICATION

  \ID COV_WDG_30_SBC_COMPATIBILITY
  \ACCEPT TX
  \REASON [COV_MSR_COMPATIBILITY]

END_COVERAGE_JUSTIFICATION */ 

/**********************************************************************************************************************
 *  END OF FILE: Wdg_30_Sbc_TrgCnd.c
 *********************************************************************************************************************/
