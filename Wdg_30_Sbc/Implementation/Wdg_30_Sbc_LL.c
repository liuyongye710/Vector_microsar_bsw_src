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
/*!        \file  Wdg_30_Sbc_LL.c
 *        \brief  Implementation of sub-module Wdg_30_Sbc_LL
 *                This is an internal include file and shall not be included by other modules than Wdg_30_Sbc.
 *
 *      \details  This sub-module provides low level services to other sub-modules. It manages hardware access of
 *                the module.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *********************************************************************************************************************/

#define WDG_30_SBC_SOURCE

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "Wdg_30_Sbc_LL.h"

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

#if !defined (WDG_30_SBC_LOCAL) /* COV_WDG_30_SBC_COMPATIBILITY */
# define WDG_30_SBC_LOCAL static
#endif

#if !defined (WDG_30_SBC_LOCAL_INLINE) /* COV_WDG_30_SBC_COMPATIBILITY */
# define WDG_30_SBC_LOCAL_INLINE LOCAL_INLINE
#endif

/**********************************************************************************************************************
 * GLOBAL FUNCTIONS
 *********************************************************************************************************************/
#define WDG_30_SBC_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  Wdg_30_Sbc_LL_Init()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, WDG_30_SBC_CODE) Wdg_30_Sbc_LL_Init(void)
{

  /* #10 Enable Gpt notification for trigger timer */
  Gpt_EnableNotification(Wdg_30_Sbc_ConfigPtr->TriggerTimer);

  /* #20 Call trigger function of Sbc if it is required */
#if(WDG_30_SBC_INITIAL_TRIGGER == STD_ON)
  Wdg_30_Sbc_ConfigPtr->SbcTriggerFctPtr(WDG_30_SBC_WDG_PERIPHERAL_ID); /* SBSW_WDG_30_SBC_1 */
#endif

  return E_OK;
}

/**********************************************************************************************************************
 *  Wdg_30_Sbc_LL_TriggerHw()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, WDG_30_SBC_CODE) Wdg_30_Sbc_LL_TriggerHw(void)
{
  /* #10 Trigger the watchdog hardware */
  Wdg_30_Sbc_ConfigPtr->SbcTriggerFctPtr(WDG_30_SBC_WDG_PERIPHERAL_ID); /* SBSW_WDG_30_SBC_1 */
}

/**********************************************************************************************************************
 *  Wdg_30_Sbc_LL_SetHwMode()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, WDG_30_SBC_CODE) Wdg_30_Sbc_LL_SetHwMode(WdgIf_ModeType Mode)
{
  /* #10 Translate Mode from WdgIf_ModeType to Sbc_WdgModeType  */
  Sbc_WdgModeType sbcMode = (Sbc_WdgModeType)(Mode+1);

  /* #20 Change mode on hardware */
  return Wdg_30_Sbc_ConfigPtr->SbcSetModeFctPtr(WDG_30_SBC_WDG_PERIPHERAL_ID, sbcMode); /* SBSW_WDG_30_SBC_1 */
}


/**********************************************************************************************************************
 *  Wdg_30_Sbc_LL_StartTriggerTimer()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, WDG_30_SBC_CODE) Wdg_30_Sbc_LL_StartTriggerTimer(WdgIf_ModeType Mode)
{
  /* PRQA S 3382 3 */ /* MD_Wdg_30_Sbc_3382 */
  /* PRQA S 3689 2 */ /* MD_Wdg_30_Sbc_3689 */
  /* #10 Start trigger timer */
  Gpt_StartTimer(Wdg_30_Sbc_ConfigPtr->TriggerTimer, Wdg_30_Sbc_ConfigPtr->TriggerTimerCounter[WDG_30_SBC_MODE_INDEX(Mode)]);
}

#if (WDG_30_SBC_IS_MODE_SUPPORTED(WDG_30_SBC_MODE_SLOW) \
    || (WDG_30_SBC_IS_MODE_SUPPORTED(WDG_30_SBC_MODE_OFF) && WDG_30_SBC_DISABLE_ALLOWED == STD_ON))
/**********************************************************************************************************************
 *  Wdg_30_Sbc_LL_StopTriggerTimer()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, WDG_30_SBC_CODE) Wdg_30_Sbc_LL_StopTriggerTimer(void)
{
  Gpt_StopTimer(Wdg_30_Sbc_ConfigPtr->TriggerTimer);
}
#endif

#define WDG_30_SBC_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* START_COVERAGE_JUSTIFICATION

  \ID COV_WDG_30_SBC_COMPATIBILITY
  \ACCEPT TX
  \REASON [COV_MSR_COMPATIBILITY]

END_COVERAGE_JUSTIFICATION */ 


/* SBSW_JUSTIFICATION_BEGIN
    \ID SBSW_WDG_30_SBC_1
      \DESCRIPTION Function pointer from function pointer member of config structure is called
      \COUNTERMEASURE \N  The compiler performs type check and therefore assures that valid function pointer is called.
                          Reference of pointer structure is retrieved by array access in Wdg_30_Sbc_LL.c.
SBSW_JUSTIFICATION_END */

/* Justification for module-specific MISRA deviations:

 MD_Wdg_30_Sbc_3382:
 Misra Rule 21.1
 Reason: '#define WDG_30_SBC_MODE_INDEX(X) (uint8)(X)-1u' is used to calculate a corresponding array index
 for a passed mode. If the macro would be used with X = WDGIF_OFF_MODE (0) a wrap-around would happen.
 As the macro only is used with X = WDGIF_SLOW_MODE (1) or WDGIF_FAST_MODE (2) this wrap-around never
 will  happen.
 Risk: No risk.
 Prevention: Code inspection.

 MD_Wdg_30_Sbc_3689:
 Misra Rule 21.1
 Reason: '#define WDG_30_SBC_MODE_INDEX(X) (uint8)(X)-1u' is used to calculate a corresponding array index
 for a passed mode. If the macro would be used with X = WDGIF_OFF_MODE (0) an access outside the array
 boundaries would happen. As the macro only is used with X = WDGIF_SLOW_MODE (1) or WDGIF_FAST_MODE (2)
 the access will always be inside the array boundaries.
 Risk: No risk.
 Prevention: Code inspection.
 */

/**********************************************************************************************************************
 *  END OF FILE: Wdg_30_Sbc_LL.c
 *********************************************************************************************************************/
