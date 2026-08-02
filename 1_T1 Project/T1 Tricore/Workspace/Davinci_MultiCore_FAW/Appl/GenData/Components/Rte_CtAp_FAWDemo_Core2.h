/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *          File:  Rte_CtAp_FAWDemo_Core2.h
 *        Config:  FAW_MultiCore297_Demo.dpa
 *   ECU-Project:  iECU
 *
 *     Generator:  MICROSAR RTE Generator Version 4.18.0
 *                 RTE Core Version 1.18.0
 *       License:  Unlimited license CBD1600956 for China FAW Group Corporation
 *
 *   Description:  Application header file for SW-C <CtAp_FAWDemo_Core2>
 *********************************************************************************************************************/

/* double include prevention */
#ifndef _RTE_CTAP_FAWDEMO_CORE2_H
# define _RTE_CTAP_FAWDEMO_CORE2_H

# ifndef RTE_CORE
#  ifdef RTE_APPLICATION_HEADER_FILE
#   error Multiple application header files included.
#  endif
#  define RTE_APPLICATION_HEADER_FILE
#  ifndef RTE_PTR2ARRAYBASETYPE_PASSING
#   define RTE_PTR2ARRAYBASETYPE_PASSING
#  endif
# endif

# ifdef __cplusplus
extern "C"
{
# endif /* __cplusplus */

/* include files */

# include "Rte_CtAp_FAWDemo_Core2_Type.h"
# include "Rte_DataHandleType.h"


# define CtAp_FAWDemo_Core2_START_SEC_CODE
# include "CtAp_FAWDemo_Core2_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 * Runnable entities
 *********************************************************************************************************************/

# ifndef RTE_CORE
#  define RTE_RUNNABLE_Runnable1000ms_Core2 Runnable1000ms_Core2
#  define RTE_RUNNABLE_Runnable100ms_Core2 Runnable100ms_Core2
#  define RTE_RUNNABLE_Runnable10ms_Core2 Runnable10ms_Core2
#  define RTE_RUNNABLE_Runnable1ms_Core2 Runnable1ms_Core2
#  define RTE_RUNNABLE_Runnable200ms_Core2 Runnable200ms_Core2
#  define RTE_RUNNABLE_Runnable20ms_Core2 Runnable20ms_Core2
#  define RTE_RUNNABLE_Runnable500ms_Core2 Runnable500ms_Core2
#  define RTE_RUNNABLE_Runnable50ms_Core2 Runnable50ms_Core2
#  define RTE_RUNNABLE_Runnable5ms_Core2 Runnable5ms_Core2
# endif

FUNC(void, CtAp_FAWDemo_Core2_CODE) Runnable1000ms_Core2(void); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
FUNC(void, CtAp_FAWDemo_Core2_CODE) Runnable100ms_Core2(void); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
FUNC(void, CtAp_FAWDemo_Core2_CODE) Runnable10ms_Core2(void); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
FUNC(void, CtAp_FAWDemo_Core2_CODE) Runnable1ms_Core2(void); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
FUNC(void, CtAp_FAWDemo_Core2_CODE) Runnable200ms_Core2(void); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
FUNC(void, CtAp_FAWDemo_Core2_CODE) Runnable20ms_Core2(void); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
FUNC(void, CtAp_FAWDemo_Core2_CODE) Runnable500ms_Core2(void); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
FUNC(void, CtAp_FAWDemo_Core2_CODE) Runnable50ms_Core2(void); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
FUNC(void, CtAp_FAWDemo_Core2_CODE) Runnable5ms_Core2(void); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */

# define CtAp_FAWDemo_Core2_STOP_SEC_CODE
# include "CtAp_FAWDemo_Core2_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

# ifdef __cplusplus
} /* extern "C" */
# endif /* __cplusplus */

#endif /* _RTE_CTAP_FAWDEMO_CORE2_H */

/**********************************************************************************************************************
 MISRA 2004 violations and justifications
 *********************************************************************************************************************/

/* module specific MISRA deviations:
   MD_Rte_3451:  MISRA rule: 8.8
     Reason:     Schedulable entities are declared by the RTE and also by the BSW modules.
     Risk:       No functional risk.
     Prevention: Not required.

*/
