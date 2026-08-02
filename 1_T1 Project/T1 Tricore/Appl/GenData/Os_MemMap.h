/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *
 *                 This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                 Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                 All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  LICENSE
 *  -------------------------------------------------------------------------------------------------------------------
 *            Module: Os
 *           Program: MSR_Vector_SLP4
 *          Customer: China FAW Group Corporation
 *       Expiry Date: Not restricted
 *  Ordered Derivat.: TC297TA
 *    License Scope : The usage is restricted to CBD1600956_D02
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *              File: Os_MemMap.h
 *   Generation Time: 2020-07-28 17:15:44
 *           Project: FAW_MultiCore297_Demo - Version 1.0
 *          Delivery: CBD1600956_D02
 *      Tool Version: DaVinci Configurator  5.17.51 SP2
 *
 *
 *********************************************************************************************************************/


#include "Os_MemMap_OsCodeInt.h"
#include "Os_MemMap_OsSectionsInt.h"
#include "Os_MemMap_StacksInt.h"

/**********************************************************************************************************************
 *  CODE SECTIONS  (Tasking)
 *********************************************************************************************************************/

#ifdef OS_START_SEC_OS_COREINITHOOK_CODE /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OS_COREINITHOOK_CODE_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section code "OS_OS_COREINITHOOK_CODE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OS_COREINITHOOK_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OS_COREINITHOOK_CODE /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OS_COREINITHOOK_CODE_OPEN
#  error Section OS_OS_COREINITHOOK_CODE is currently not opened and so cannot be closed.
# endif
# undef OS_OS_COREINITHOOK_CODE_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section code restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OS_COREINITHOOK_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_Adc0Sr0_Isr_CODE /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_Adc0Sr0_Isr_CODE_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section code "OS_Adc0Sr0_Isr_CODE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_Adc0Sr0_Isr_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_Adc0Sr0_Isr_CODE /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_Adc0Sr0_Isr_CODE_OPEN
#  error Section OS_Adc0Sr0_Isr_CODE is currently not opened and so cannot be closed.
# endif
# undef OS_Adc0Sr0_Isr_CODE_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section code restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_Adc0Sr0_Isr_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_Adc1Sr0_Isr_CODE /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_Adc1Sr0_Isr_CODE_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section code "OS_Adc1Sr0_Isr_CODE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_Adc1Sr0_Isr_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_Adc1Sr0_Isr_CODE /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_Adc1Sr0_Isr_CODE_OPEN
#  error Section OS_Adc1Sr0_Isr_CODE is currently not opened and so cannot be closed.
# endif
# undef OS_Adc1Sr0_Isr_CODE_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section code restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_Adc1Sr0_Isr_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_Adc2Sr0_Isr_CODE /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_Adc2Sr0_Isr_CODE_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section code "OS_Adc2Sr0_Isr_CODE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_Adc2Sr0_Isr_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_Adc2Sr0_Isr_CODE /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_Adc2Sr0_Isr_CODE_OPEN
#  error Section OS_Adc2Sr0_Isr_CODE is currently not opened and so cannot be closed.
# endif
# undef OS_Adc2Sr0_Isr_CODE_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section code restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_Adc2Sr0_Isr_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_Adc3Sr0_Isr_CODE /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_Adc3Sr0_Isr_CODE_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section code "OS_Adc3Sr0_Isr_CODE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_Adc3Sr0_Isr_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_Adc3Sr0_Isr_CODE /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_Adc3Sr0_Isr_CODE_OPEN
#  error Section OS_Adc3Sr0_Isr_CODE is currently not opened and so cannot be closed.
# endif
# undef OS_Adc3Sr0_Isr_CODE_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section code restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_Adc3Sr0_Isr_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_Adc4Sr0_Isr_CODE /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_Adc4Sr0_Isr_CODE_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section code "OS_Adc4Sr0_Isr_CODE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_Adc4Sr0_Isr_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_Adc4Sr0_Isr_CODE /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_Adc4Sr0_Isr_CODE_OPEN
#  error Section OS_Adc4Sr0_Isr_CODE is currently not opened and so cannot be closed.
# endif
# undef OS_Adc4Sr0_Isr_CODE_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section code restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_Adc4Sr0_Isr_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_Adc5Sr0_Isr_CODE /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_Adc5Sr0_Isr_CODE_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section code "OS_Adc5Sr0_Isr_CODE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_Adc5Sr0_Isr_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_Adc5Sr0_Isr_CODE /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_Adc5Sr0_Isr_CODE_OPEN
#  error Section OS_Adc5Sr0_Isr_CODE is currently not opened and so cannot be closed.
# endif
# undef OS_Adc5Sr0_Isr_CODE_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section code restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_Adc5Sr0_Isr_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_Adc6Sr0_Isr_CODE /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_Adc6Sr0_Isr_CODE_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section code "OS_Adc6Sr0_Isr_CODE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_Adc6Sr0_Isr_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_Adc6Sr0_Isr_CODE /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_Adc6Sr0_Isr_CODE_OPEN
#  error Section OS_Adc6Sr0_Isr_CODE is currently not opened and so cannot be closed.
# endif
# undef OS_Adc6Sr0_Isr_CODE_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section code restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_Adc6Sr0_Isr_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_CanIsr_0_CODE /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_CanIsr_0_CODE_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section code "OS_CanIsr_0_CODE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_CanIsr_0_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_CanIsr_0_CODE /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_CanIsr_0_CODE_OPEN
#  error Section OS_CanIsr_0_CODE is currently not opened and so cannot be closed.
# endif
# undef OS_CanIsr_0_CODE_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section code restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_CanIsr_0_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_Isr_TIM02_CODE /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_Isr_TIM02_CODE_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section code "OS_Isr_TIM02_CODE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_Isr_TIM02_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_Isr_TIM02_CODE /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_Isr_TIM02_CODE_OPEN
#  error Section OS_Isr_TIM02_CODE is currently not opened and so cannot be closed.
# endif
# undef OS_Isr_TIM02_CODE_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section code restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_Isr_TIM02_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_Isr_TIM03_CODE /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_Isr_TIM03_CODE_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section code "OS_Isr_TIM03_CODE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_Isr_TIM03_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_Isr_TIM03_CODE /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_Isr_TIM03_CODE_OPEN
#  error Section OS_Isr_TIM03_CODE is currently not opened and so cannot be closed.
# endif
# undef OS_Isr_TIM03_CODE_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section code restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_Isr_TIM03_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_Task1000ms_Core0_CODE /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_Task1000ms_Core0_CODE_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section code "OS_Task1000ms_Core0_CODE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_Task1000ms_Core0_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_Task1000ms_Core0_CODE /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_Task1000ms_Core0_CODE_OPEN
#  error Section OS_Task1000ms_Core0_CODE is currently not opened and so cannot be closed.
# endif
# undef OS_Task1000ms_Core0_CODE_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section code restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_Task1000ms_Core0_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_Task1000ms_Core1_CODE /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_Task1000ms_Core1_CODE_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section code "OS_Task1000ms_Core1_CODE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_Task1000ms_Core1_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_Task1000ms_Core1_CODE /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_Task1000ms_Core1_CODE_OPEN
#  error Section OS_Task1000ms_Core1_CODE is currently not opened and so cannot be closed.
# endif
# undef OS_Task1000ms_Core1_CODE_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section code restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_Task1000ms_Core1_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_Task1000ms_Core2_CODE /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_Task1000ms_Core2_CODE_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section code "OS_Task1000ms_Core2_CODE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_Task1000ms_Core2_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_Task1000ms_Core2_CODE /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_Task1000ms_Core2_CODE_OPEN
#  error Section OS_Task1000ms_Core2_CODE is currently not opened and so cannot be closed.
# endif
# undef OS_Task1000ms_Core2_CODE_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section code restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_Task1000ms_Core2_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_Task100ms_Core0_CODE /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_Task100ms_Core0_CODE_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section code "OS_Task100ms_Core0_CODE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_Task100ms_Core0_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_Task100ms_Core0_CODE /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_Task100ms_Core0_CODE_OPEN
#  error Section OS_Task100ms_Core0_CODE is currently not opened and so cannot be closed.
# endif
# undef OS_Task100ms_Core0_CODE_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section code restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_Task100ms_Core0_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_Task100ms_Core1_CODE /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_Task100ms_Core1_CODE_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section code "OS_Task100ms_Core1_CODE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_Task100ms_Core1_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_Task100ms_Core1_CODE /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_Task100ms_Core1_CODE_OPEN
#  error Section OS_Task100ms_Core1_CODE is currently not opened and so cannot be closed.
# endif
# undef OS_Task100ms_Core1_CODE_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section code restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_Task100ms_Core1_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_Task100ms_Core2_CODE /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_Task100ms_Core2_CODE_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section code "OS_Task100ms_Core2_CODE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_Task100ms_Core2_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_Task100ms_Core2_CODE /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_Task100ms_Core2_CODE_OPEN
#  error Section OS_Task100ms_Core2_CODE is currently not opened and so cannot be closed.
# endif
# undef OS_Task100ms_Core2_CODE_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section code restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_Task100ms_Core2_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_Task10ms_Core0_CODE /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_Task10ms_Core0_CODE_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section code "OS_Task10ms_Core0_CODE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_Task10ms_Core0_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_Task10ms_Core0_CODE /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_Task10ms_Core0_CODE_OPEN
#  error Section OS_Task10ms_Core0_CODE is currently not opened and so cannot be closed.
# endif
# undef OS_Task10ms_Core0_CODE_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section code restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_Task10ms_Core0_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_Task10ms_Core1_CODE /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_Task10ms_Core1_CODE_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section code "OS_Task10ms_Core1_CODE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_Task10ms_Core1_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_Task10ms_Core1_CODE /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_Task10ms_Core1_CODE_OPEN
#  error Section OS_Task10ms_Core1_CODE is currently not opened and so cannot be closed.
# endif
# undef OS_Task10ms_Core1_CODE_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section code restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_Task10ms_Core1_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_Task10ms_Core2_CODE /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_Task10ms_Core2_CODE_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section code "OS_Task10ms_Core2_CODE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_Task10ms_Core2_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_Task10ms_Core2_CODE /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_Task10ms_Core2_CODE_OPEN
#  error Section OS_Task10ms_Core2_CODE is currently not opened and so cannot be closed.
# endif
# undef OS_Task10ms_Core2_CODE_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section code restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_Task10ms_Core2_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_Task1ms_Core0_CODE /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_Task1ms_Core0_CODE_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section code "OS_Task1ms_Core0_CODE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_Task1ms_Core0_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_Task1ms_Core0_CODE /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_Task1ms_Core0_CODE_OPEN
#  error Section OS_Task1ms_Core0_CODE is currently not opened and so cannot be closed.
# endif
# undef OS_Task1ms_Core0_CODE_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section code restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_Task1ms_Core0_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_Task1ms_Core1_CODE /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_Task1ms_Core1_CODE_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section code "OS_Task1ms_Core1_CODE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_Task1ms_Core1_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_Task1ms_Core1_CODE /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_Task1ms_Core1_CODE_OPEN
#  error Section OS_Task1ms_Core1_CODE is currently not opened and so cannot be closed.
# endif
# undef OS_Task1ms_Core1_CODE_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section code restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_Task1ms_Core1_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_Task1ms_Core2_CODE /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_Task1ms_Core2_CODE_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section code "OS_Task1ms_Core2_CODE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_Task1ms_Core2_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_Task1ms_Core2_CODE /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_Task1ms_Core2_CODE_OPEN
#  error Section OS_Task1ms_Core2_CODE is currently not opened and so cannot be closed.
# endif
# undef OS_Task1ms_Core2_CODE_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section code restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_Task1ms_Core2_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_Task200ms_Core0_CODE /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_Task200ms_Core0_CODE_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section code "OS_Task200ms_Core0_CODE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_Task200ms_Core0_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_Task200ms_Core0_CODE /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_Task200ms_Core0_CODE_OPEN
#  error Section OS_Task200ms_Core0_CODE is currently not opened and so cannot be closed.
# endif
# undef OS_Task200ms_Core0_CODE_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section code restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_Task200ms_Core0_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_Task200ms_Core1_CODE /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_Task200ms_Core1_CODE_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section code "OS_Task200ms_Core1_CODE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_Task200ms_Core1_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_Task200ms_Core1_CODE /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_Task200ms_Core1_CODE_OPEN
#  error Section OS_Task200ms_Core1_CODE is currently not opened and so cannot be closed.
# endif
# undef OS_Task200ms_Core1_CODE_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section code restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_Task200ms_Core1_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_Task200ms_Core2_CODE /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_Task200ms_Core2_CODE_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section code "OS_Task200ms_Core2_CODE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_Task200ms_Core2_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_Task200ms_Core2_CODE /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_Task200ms_Core2_CODE_OPEN
#  error Section OS_Task200ms_Core2_CODE is currently not opened and so cannot be closed.
# endif
# undef OS_Task200ms_Core2_CODE_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section code restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_Task200ms_Core2_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_Task20ms_Core0_CODE /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_Task20ms_Core0_CODE_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section code "OS_Task20ms_Core0_CODE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_Task20ms_Core0_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_Task20ms_Core0_CODE /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_Task20ms_Core0_CODE_OPEN
#  error Section OS_Task20ms_Core0_CODE is currently not opened and so cannot be closed.
# endif
# undef OS_Task20ms_Core0_CODE_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section code restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_Task20ms_Core0_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_Task20ms_Core1_CODE /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_Task20ms_Core1_CODE_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section code "OS_Task20ms_Core1_CODE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_Task20ms_Core1_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_Task20ms_Core1_CODE /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_Task20ms_Core1_CODE_OPEN
#  error Section OS_Task20ms_Core1_CODE is currently not opened and so cannot be closed.
# endif
# undef OS_Task20ms_Core1_CODE_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section code restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_Task20ms_Core1_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_Task20ms_Core2_CODE /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_Task20ms_Core2_CODE_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section code "OS_Task20ms_Core2_CODE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_Task20ms_Core2_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_Task20ms_Core2_CODE /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_Task20ms_Core2_CODE_OPEN
#  error Section OS_Task20ms_Core2_CODE is currently not opened and so cannot be closed.
# endif
# undef OS_Task20ms_Core2_CODE_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section code restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_Task20ms_Core2_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_Task500ms_Core0_CODE /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_Task500ms_Core0_CODE_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section code "OS_Task500ms_Core0_CODE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_Task500ms_Core0_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_Task500ms_Core0_CODE /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_Task500ms_Core0_CODE_OPEN
#  error Section OS_Task500ms_Core0_CODE is currently not opened and so cannot be closed.
# endif
# undef OS_Task500ms_Core0_CODE_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section code restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_Task500ms_Core0_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_Task500ms_Core1_CODE /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_Task500ms_Core1_CODE_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section code "OS_Task500ms_Core1_CODE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_Task500ms_Core1_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_Task500ms_Core1_CODE /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_Task500ms_Core1_CODE_OPEN
#  error Section OS_Task500ms_Core1_CODE is currently not opened and so cannot be closed.
# endif
# undef OS_Task500ms_Core1_CODE_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section code restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_Task500ms_Core1_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_Task500ms_Core2_CODE /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_Task500ms_Core2_CODE_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section code "OS_Task500ms_Core2_CODE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_Task500ms_Core2_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_Task500ms_Core2_CODE /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_Task500ms_Core2_CODE_OPEN
#  error Section OS_Task500ms_Core2_CODE is currently not opened and so cannot be closed.
# endif
# undef OS_Task500ms_Core2_CODE_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section code restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_Task500ms_Core2_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_Task50ms_Core0_CODE /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_Task50ms_Core0_CODE_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section code "OS_Task50ms_Core0_CODE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_Task50ms_Core0_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_Task50ms_Core0_CODE /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_Task50ms_Core0_CODE_OPEN
#  error Section OS_Task50ms_Core0_CODE is currently not opened and so cannot be closed.
# endif
# undef OS_Task50ms_Core0_CODE_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section code restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_Task50ms_Core0_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_Task50ms_Core1_CODE /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_Task50ms_Core1_CODE_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section code "OS_Task50ms_Core1_CODE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_Task50ms_Core1_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_Task50ms_Core1_CODE /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_Task50ms_Core1_CODE_OPEN
#  error Section OS_Task50ms_Core1_CODE is currently not opened and so cannot be closed.
# endif
# undef OS_Task50ms_Core1_CODE_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section code restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_Task50ms_Core1_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_Task50ms_Core2_CODE /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_Task50ms_Core2_CODE_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section code "OS_Task50ms_Core2_CODE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_Task50ms_Core2_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_Task50ms_Core2_CODE /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_Task50ms_Core2_CODE_OPEN
#  error Section OS_Task50ms_Core2_CODE is currently not opened and so cannot be closed.
# endif
# undef OS_Task50ms_Core2_CODE_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section code restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_Task50ms_Core2_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_Task5ms_Core0_CODE /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_Task5ms_Core0_CODE_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section code "OS_Task5ms_Core0_CODE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_Task5ms_Core0_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_Task5ms_Core0_CODE /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_Task5ms_Core0_CODE_OPEN
#  error Section OS_Task5ms_Core0_CODE is currently not opened and so cannot be closed.
# endif
# undef OS_Task5ms_Core0_CODE_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section code restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_Task5ms_Core0_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_Task5ms_Core1_CODE /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_Task5ms_Core1_CODE_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section code "OS_Task5ms_Core1_CODE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_Task5ms_Core1_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_Task5ms_Core1_CODE /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_Task5ms_Core1_CODE_OPEN
#  error Section OS_Task5ms_Core1_CODE is currently not opened and so cannot be closed.
# endif
# undef OS_Task5ms_Core1_CODE_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section code restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_Task5ms_Core1_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_Task5ms_Core2_CODE /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_Task5ms_Core2_CODE_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section code "OS_Task5ms_Core2_CODE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_Task5ms_Core2_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_Task5ms_Core2_CODE /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_Task5ms_Core2_CODE_OPEN
#  error Section OS_Task5ms_Core2_CODE is currently not opened and so cannot be closed.
# endif
# undef OS_Task5ms_Core2_CODE_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section code restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_Task5ms_Core2_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_TaskInit_Core0_CODE /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_TaskInit_Core0_CODE_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section code "OS_TaskInit_Core0_CODE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_TaskInit_Core0_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_TaskInit_Core0_CODE /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_TaskInit_Core0_CODE_OPEN
#  error Section OS_TaskInit_Core0_CODE is currently not opened and so cannot be closed.
# endif
# undef OS_TaskInit_Core0_CODE_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section code restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_TaskInit_Core0_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_TaskInit_Core1_CODE /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_TaskInit_Core1_CODE_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section code "OS_TaskInit_Core1_CODE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_TaskInit_Core1_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_TaskInit_Core1_CODE /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_TaskInit_Core1_CODE_OPEN
#  error Section OS_TaskInit_Core1_CODE is currently not opened and so cannot be closed.
# endif
# undef OS_TaskInit_Core1_CODE_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section code restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_TaskInit_Core1_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_TaskInit_Core2_CODE /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_TaskInit_Core2_CODE_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section code "OS_TaskInit_Core2_CODE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_TaskInit_Core2_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_TaskInit_Core2_CODE /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_TaskInit_Core2_CODE_OPEN
#  error Section OS_TaskInit_Core2_CODE is currently not opened and so cannot be closed.
# endif
# undef OS_TaskInit_Core2_CODE_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section code restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_TaskInit_Core2_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_TaskSchM_Core0_CODE /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_TaskSchM_Core0_CODE_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section code "OS_TaskSchM_Core0_CODE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_TaskSchM_Core0_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_TaskSchM_Core0_CODE /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_TaskSchM_Core0_CODE_OPEN
#  error Section OS_TaskSchM_Core0_CODE is currently not opened and so cannot be closed.
# endif
# undef OS_TaskSchM_Core0_CODE_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section code restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_TaskSchM_Core0_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_TaskSchM_Core1_CODE /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_TaskSchM_Core1_CODE_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section code "OS_TaskSchM_Core1_CODE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_TaskSchM_Core1_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_TaskSchM_Core1_CODE /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_TaskSchM_Core1_CODE_OPEN
#  error Section OS_TaskSchM_Core1_CODE is currently not opened and so cannot be closed.
# endif
# undef OS_TaskSchM_Core1_CODE_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section code restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_TaskSchM_Core1_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_TaskSchM_Core2_CODE /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_TaskSchM_Core2_CODE_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section code "OS_TaskSchM_Core2_CODE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_TaskSchM_Core2_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_TaskSchM_Core2_CODE /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_TaskSchM_Core2_CODE_OPEN
#  error Section OS_TaskSchM_Core2_CODE is currently not opened and so cannot be closed.
# endif
# undef OS_TaskSchM_Core2_CODE_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section code restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_TaskSchM_Core2_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif


/**********************************************************************************************************************
 *  CONST SECTIONS
 *********************************************************************************************************************/

#ifdef OS_START_SEC_GLOBALSHARED_CONST_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_GLOBALSHARED_CONST_BOOLEAN_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom "OS_GLOBALSHARED_CONST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom "OS_GLOBALSHARED_CONST_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_GLOBALSHARED_CONST_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_GLOBALSHARED_CONST_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_GLOBALSHARED_CONST_BOOLEAN_OPEN
#  error Section OS_GLOBALSHARED_CONST_BOOLEAN is currently not opened and so cannot be closed.
# endif
# undef OS_GLOBALSHARED_CONST_BOOLEAN_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_GLOBALSHARED_CONST_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_GLOBALSHARED_CONST_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_GLOBALSHARED_CONST_8BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom "OS_GLOBALSHARED_CONST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom "OS_GLOBALSHARED_CONST_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_GLOBALSHARED_CONST_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_GLOBALSHARED_CONST_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_GLOBALSHARED_CONST_8BIT_OPEN
#  error Section OS_GLOBALSHARED_CONST_8BIT is currently not opened and so cannot be closed.
# endif
# undef OS_GLOBALSHARED_CONST_8BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_GLOBALSHARED_CONST_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_GLOBALSHARED_CONST_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_GLOBALSHARED_CONST_16BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom "OS_GLOBALSHARED_CONST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom "OS_GLOBALSHARED_CONST_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_GLOBALSHARED_CONST_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_GLOBALSHARED_CONST_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_GLOBALSHARED_CONST_16BIT_OPEN
#  error Section OS_GLOBALSHARED_CONST_16BIT is currently not opened and so cannot be closed.
# endif
# undef OS_GLOBALSHARED_CONST_16BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_GLOBALSHARED_CONST_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_GLOBALSHARED_CONST_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_GLOBALSHARED_CONST_32BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom "OS_GLOBALSHARED_CONST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom "OS_GLOBALSHARED_CONST_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_GLOBALSHARED_CONST_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_GLOBALSHARED_CONST_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_GLOBALSHARED_CONST_32BIT_OPEN
#  error Section OS_GLOBALSHARED_CONST_32BIT is currently not opened and so cannot be closed.
# endif
# undef OS_GLOBALSHARED_CONST_32BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_GLOBALSHARED_CONST_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_GLOBALSHARED_CONST_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_GLOBALSHARED_CONST_UNSPECIFIED_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom "OS_GLOBALSHARED_CONST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom "OS_GLOBALSHARED_CONST_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_GLOBALSHARED_CONST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_GLOBALSHARED_CONST_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_GLOBALSHARED_CONST_UNSPECIFIED_OPEN
#  error Section OS_GLOBALSHARED_CONST_UNSPECIFIED is currently not opened and so cannot be closed.
# endif
# undef OS_GLOBALSHARED_CONST_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_GLOBALSHARED_CONST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_GLOBALSHARED_CONST_FAST_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_GLOBALSHARED_CONST_FAST_BOOLEAN_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom "OS_GLOBALSHARED_CONST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom "OS_GLOBALSHARED_CONST_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_GLOBALSHARED_CONST_FAST_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_GLOBALSHARED_CONST_FAST_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_GLOBALSHARED_CONST_FAST_BOOLEAN_OPEN
#  error Section OS_GLOBALSHARED_CONST_FAST_BOOLEAN is currently not opened and so cannot be closed.
# endif
# undef OS_GLOBALSHARED_CONST_FAST_BOOLEAN_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_GLOBALSHARED_CONST_FAST_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_GLOBALSHARED_CONST_FAST_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_GLOBALSHARED_CONST_FAST_8BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom "OS_GLOBALSHARED_CONST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom "OS_GLOBALSHARED_CONST_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_GLOBALSHARED_CONST_FAST_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_GLOBALSHARED_CONST_FAST_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_GLOBALSHARED_CONST_FAST_8BIT_OPEN
#  error Section OS_GLOBALSHARED_CONST_FAST_8BIT is currently not opened and so cannot be closed.
# endif
# undef OS_GLOBALSHARED_CONST_FAST_8BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_GLOBALSHARED_CONST_FAST_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_GLOBALSHARED_CONST_FAST_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_GLOBALSHARED_CONST_FAST_16BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom "OS_GLOBALSHARED_CONST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom "OS_GLOBALSHARED_CONST_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_GLOBALSHARED_CONST_FAST_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_GLOBALSHARED_CONST_FAST_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_GLOBALSHARED_CONST_FAST_16BIT_OPEN
#  error Section OS_GLOBALSHARED_CONST_FAST_16BIT is currently not opened and so cannot be closed.
# endif
# undef OS_GLOBALSHARED_CONST_FAST_16BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_GLOBALSHARED_CONST_FAST_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_GLOBALSHARED_CONST_FAST_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_GLOBALSHARED_CONST_FAST_32BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom "OS_GLOBALSHARED_CONST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom "OS_GLOBALSHARED_CONST_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_GLOBALSHARED_CONST_FAST_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_GLOBALSHARED_CONST_FAST_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_GLOBALSHARED_CONST_FAST_32BIT_OPEN
#  error Section OS_GLOBALSHARED_CONST_FAST_32BIT is currently not opened and so cannot be closed.
# endif
# undef OS_GLOBALSHARED_CONST_FAST_32BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_GLOBALSHARED_CONST_FAST_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_GLOBALSHARED_CONST_FAST_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_GLOBALSHARED_CONST_FAST_UNSPECIFIED_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom "OS_GLOBALSHARED_CONST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom "OS_GLOBALSHARED_CONST_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_GLOBALSHARED_CONST_FAST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_GLOBALSHARED_CONST_FAST_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_GLOBALSHARED_CONST_FAST_UNSPECIFIED_OPEN
#  error Section OS_GLOBALSHARED_CONST_FAST_UNSPECIFIED is currently not opened and so cannot be closed.
# endif
# undef OS_GLOBALSHARED_CONST_FAST_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_GLOBALSHARED_CONST_FAST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core0_CONST_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core0_CONST_BOOLEAN_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom "OS_OsApplication_Core0_CONST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom "OS_OsApplication_Core0_CONST_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core0_CONST_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core0_CONST_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core0_CONST_BOOLEAN_OPEN
#  error Section OS_OsApplication_Core0_CONST_BOOLEAN is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core0_CONST_BOOLEAN_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core0_CONST_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core0_CONST_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core0_CONST_8BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom "OS_OsApplication_Core0_CONST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom "OS_OsApplication_Core0_CONST_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core0_CONST_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core0_CONST_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core0_CONST_8BIT_OPEN
#  error Section OS_OsApplication_Core0_CONST_8BIT is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core0_CONST_8BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core0_CONST_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core0_CONST_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core0_CONST_16BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom "OS_OsApplication_Core0_CONST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom "OS_OsApplication_Core0_CONST_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core0_CONST_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core0_CONST_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core0_CONST_16BIT_OPEN
#  error Section OS_OsApplication_Core0_CONST_16BIT is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core0_CONST_16BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core0_CONST_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core0_CONST_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core0_CONST_32BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom "OS_OsApplication_Core0_CONST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom "OS_OsApplication_Core0_CONST_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core0_CONST_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core0_CONST_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core0_CONST_32BIT_OPEN
#  error Section OS_OsApplication_Core0_CONST_32BIT is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core0_CONST_32BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core0_CONST_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core0_CONST_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core0_CONST_UNSPECIFIED_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom "OS_OsApplication_Core0_CONST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom "OS_OsApplication_Core0_CONST_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core0_CONST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core0_CONST_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core0_CONST_UNSPECIFIED_OPEN
#  error Section OS_OsApplication_Core0_CONST_UNSPECIFIED is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core0_CONST_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core0_CONST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core0_CONST_FAST_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core0_CONST_FAST_BOOLEAN_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom "OS_OsApplication_Core0_CONST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom "OS_OsApplication_Core0_CONST_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core0_CONST_FAST_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core0_CONST_FAST_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core0_CONST_FAST_BOOLEAN_OPEN
#  error Section OS_OsApplication_Core0_CONST_FAST_BOOLEAN is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core0_CONST_FAST_BOOLEAN_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core0_CONST_FAST_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core0_CONST_FAST_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core0_CONST_FAST_8BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom "OS_OsApplication_Core0_CONST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom "OS_OsApplication_Core0_CONST_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core0_CONST_FAST_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core0_CONST_FAST_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core0_CONST_FAST_8BIT_OPEN
#  error Section OS_OsApplication_Core0_CONST_FAST_8BIT is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core0_CONST_FAST_8BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core0_CONST_FAST_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core0_CONST_FAST_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core0_CONST_FAST_16BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom "OS_OsApplication_Core0_CONST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom "OS_OsApplication_Core0_CONST_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core0_CONST_FAST_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core0_CONST_FAST_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core0_CONST_FAST_16BIT_OPEN
#  error Section OS_OsApplication_Core0_CONST_FAST_16BIT is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core0_CONST_FAST_16BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core0_CONST_FAST_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core0_CONST_FAST_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core0_CONST_FAST_32BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom "OS_OsApplication_Core0_CONST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom "OS_OsApplication_Core0_CONST_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core0_CONST_FAST_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core0_CONST_FAST_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core0_CONST_FAST_32BIT_OPEN
#  error Section OS_OsApplication_Core0_CONST_FAST_32BIT is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core0_CONST_FAST_32BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core0_CONST_FAST_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core0_CONST_FAST_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core0_CONST_FAST_UNSPECIFIED_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom "OS_OsApplication_Core0_CONST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom "OS_OsApplication_Core0_CONST_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core0_CONST_FAST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core0_CONST_FAST_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core0_CONST_FAST_UNSPECIFIED_OPEN
#  error Section OS_OsApplication_Core0_CONST_FAST_UNSPECIFIED is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core0_CONST_FAST_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core0_CONST_FAST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core1_CONST_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core1_CONST_BOOLEAN_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom "OS_OsApplication_Core1_CONST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom "OS_OsApplication_Core1_CONST_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core1_CONST_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core1_CONST_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core1_CONST_BOOLEAN_OPEN
#  error Section OS_OsApplication_Core1_CONST_BOOLEAN is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core1_CONST_BOOLEAN_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core1_CONST_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core1_CONST_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core1_CONST_8BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom "OS_OsApplication_Core1_CONST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom "OS_OsApplication_Core1_CONST_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core1_CONST_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core1_CONST_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core1_CONST_8BIT_OPEN
#  error Section OS_OsApplication_Core1_CONST_8BIT is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core1_CONST_8BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core1_CONST_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core1_CONST_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core1_CONST_16BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom "OS_OsApplication_Core1_CONST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom "OS_OsApplication_Core1_CONST_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core1_CONST_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core1_CONST_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core1_CONST_16BIT_OPEN
#  error Section OS_OsApplication_Core1_CONST_16BIT is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core1_CONST_16BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core1_CONST_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core1_CONST_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core1_CONST_32BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom "OS_OsApplication_Core1_CONST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom "OS_OsApplication_Core1_CONST_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core1_CONST_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core1_CONST_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core1_CONST_32BIT_OPEN
#  error Section OS_OsApplication_Core1_CONST_32BIT is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core1_CONST_32BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core1_CONST_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core1_CONST_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core1_CONST_UNSPECIFIED_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom "OS_OsApplication_Core1_CONST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom "OS_OsApplication_Core1_CONST_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core1_CONST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core1_CONST_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core1_CONST_UNSPECIFIED_OPEN
#  error Section OS_OsApplication_Core1_CONST_UNSPECIFIED is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core1_CONST_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core1_CONST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core1_CONST_FAST_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core1_CONST_FAST_BOOLEAN_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom "OS_OsApplication_Core1_CONST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom "OS_OsApplication_Core1_CONST_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core1_CONST_FAST_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core1_CONST_FAST_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core1_CONST_FAST_BOOLEAN_OPEN
#  error Section OS_OsApplication_Core1_CONST_FAST_BOOLEAN is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core1_CONST_FAST_BOOLEAN_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core1_CONST_FAST_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core1_CONST_FAST_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core1_CONST_FAST_8BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom "OS_OsApplication_Core1_CONST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom "OS_OsApplication_Core1_CONST_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core1_CONST_FAST_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core1_CONST_FAST_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core1_CONST_FAST_8BIT_OPEN
#  error Section OS_OsApplication_Core1_CONST_FAST_8BIT is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core1_CONST_FAST_8BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core1_CONST_FAST_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core1_CONST_FAST_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core1_CONST_FAST_16BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom "OS_OsApplication_Core1_CONST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom "OS_OsApplication_Core1_CONST_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core1_CONST_FAST_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core1_CONST_FAST_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core1_CONST_FAST_16BIT_OPEN
#  error Section OS_OsApplication_Core1_CONST_FAST_16BIT is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core1_CONST_FAST_16BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core1_CONST_FAST_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core1_CONST_FAST_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core1_CONST_FAST_32BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom "OS_OsApplication_Core1_CONST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom "OS_OsApplication_Core1_CONST_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core1_CONST_FAST_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core1_CONST_FAST_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core1_CONST_FAST_32BIT_OPEN
#  error Section OS_OsApplication_Core1_CONST_FAST_32BIT is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core1_CONST_FAST_32BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core1_CONST_FAST_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core1_CONST_FAST_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core1_CONST_FAST_UNSPECIFIED_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom "OS_OsApplication_Core1_CONST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom "OS_OsApplication_Core1_CONST_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core1_CONST_FAST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core1_CONST_FAST_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core1_CONST_FAST_UNSPECIFIED_OPEN
#  error Section OS_OsApplication_Core1_CONST_FAST_UNSPECIFIED is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core1_CONST_FAST_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core1_CONST_FAST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core2_CONST_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core2_CONST_BOOLEAN_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom "OS_OsApplication_Core2_CONST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom "OS_OsApplication_Core2_CONST_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core2_CONST_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core2_CONST_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core2_CONST_BOOLEAN_OPEN
#  error Section OS_OsApplication_Core2_CONST_BOOLEAN is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core2_CONST_BOOLEAN_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core2_CONST_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core2_CONST_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core2_CONST_8BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom "OS_OsApplication_Core2_CONST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom "OS_OsApplication_Core2_CONST_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core2_CONST_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core2_CONST_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core2_CONST_8BIT_OPEN
#  error Section OS_OsApplication_Core2_CONST_8BIT is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core2_CONST_8BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core2_CONST_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core2_CONST_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core2_CONST_16BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom "OS_OsApplication_Core2_CONST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom "OS_OsApplication_Core2_CONST_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core2_CONST_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core2_CONST_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core2_CONST_16BIT_OPEN
#  error Section OS_OsApplication_Core2_CONST_16BIT is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core2_CONST_16BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core2_CONST_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core2_CONST_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core2_CONST_32BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom "OS_OsApplication_Core2_CONST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom "OS_OsApplication_Core2_CONST_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core2_CONST_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core2_CONST_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core2_CONST_32BIT_OPEN
#  error Section OS_OsApplication_Core2_CONST_32BIT is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core2_CONST_32BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core2_CONST_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core2_CONST_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core2_CONST_UNSPECIFIED_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom "OS_OsApplication_Core2_CONST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom "OS_OsApplication_Core2_CONST_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core2_CONST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core2_CONST_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core2_CONST_UNSPECIFIED_OPEN
#  error Section OS_OsApplication_Core2_CONST_UNSPECIFIED is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core2_CONST_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core2_CONST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core2_CONST_FAST_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core2_CONST_FAST_BOOLEAN_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom "OS_OsApplication_Core2_CONST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom "OS_OsApplication_Core2_CONST_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core2_CONST_FAST_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core2_CONST_FAST_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core2_CONST_FAST_BOOLEAN_OPEN
#  error Section OS_OsApplication_Core2_CONST_FAST_BOOLEAN is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core2_CONST_FAST_BOOLEAN_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core2_CONST_FAST_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core2_CONST_FAST_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core2_CONST_FAST_8BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom "OS_OsApplication_Core2_CONST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom "OS_OsApplication_Core2_CONST_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core2_CONST_FAST_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core2_CONST_FAST_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core2_CONST_FAST_8BIT_OPEN
#  error Section OS_OsApplication_Core2_CONST_FAST_8BIT is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core2_CONST_FAST_8BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core2_CONST_FAST_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core2_CONST_FAST_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core2_CONST_FAST_16BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom "OS_OsApplication_Core2_CONST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom "OS_OsApplication_Core2_CONST_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core2_CONST_FAST_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core2_CONST_FAST_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core2_CONST_FAST_16BIT_OPEN
#  error Section OS_OsApplication_Core2_CONST_FAST_16BIT is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core2_CONST_FAST_16BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core2_CONST_FAST_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core2_CONST_FAST_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core2_CONST_FAST_32BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom "OS_OsApplication_Core2_CONST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom "OS_OsApplication_Core2_CONST_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core2_CONST_FAST_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core2_CONST_FAST_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core2_CONST_FAST_32BIT_OPEN
#  error Section OS_OsApplication_Core2_CONST_FAST_32BIT is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core2_CONST_FAST_32BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core2_CONST_FAST_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core2_CONST_FAST_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core2_CONST_FAST_UNSPECIFIED_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom "OS_OsApplication_Core2_CONST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom "OS_OsApplication_Core2_CONST_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core2_CONST_FAST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core2_CONST_FAST_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core2_CONST_FAST_UNSPECIFIED_OPEN
#  error Section OS_OsApplication_Core2_CONST_FAST_UNSPECIFIED is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core2_CONST_FAST_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core2_CONST_FAST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore0_CONST_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore0_CONST_BOOLEAN_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom "OS_SystemApplication_OsCore0_CONST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom "OS_SystemApplication_OsCore0_CONST_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore0_CONST_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore0_CONST_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore0_CONST_BOOLEAN_OPEN
#  error Section OS_SystemApplication_OsCore0_CONST_BOOLEAN is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore0_CONST_BOOLEAN_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore0_CONST_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore0_CONST_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore0_CONST_8BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom "OS_SystemApplication_OsCore0_CONST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom "OS_SystemApplication_OsCore0_CONST_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore0_CONST_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore0_CONST_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore0_CONST_8BIT_OPEN
#  error Section OS_SystemApplication_OsCore0_CONST_8BIT is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore0_CONST_8BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore0_CONST_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore0_CONST_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore0_CONST_16BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom "OS_SystemApplication_OsCore0_CONST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom "OS_SystemApplication_OsCore0_CONST_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore0_CONST_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore0_CONST_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore0_CONST_16BIT_OPEN
#  error Section OS_SystemApplication_OsCore0_CONST_16BIT is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore0_CONST_16BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore0_CONST_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore0_CONST_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore0_CONST_32BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom "OS_SystemApplication_OsCore0_CONST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom "OS_SystemApplication_OsCore0_CONST_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore0_CONST_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore0_CONST_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore0_CONST_32BIT_OPEN
#  error Section OS_SystemApplication_OsCore0_CONST_32BIT is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore0_CONST_32BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore0_CONST_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore0_CONST_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore0_CONST_UNSPECIFIED_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom "OS_SystemApplication_OsCore0_CONST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom "OS_SystemApplication_OsCore0_CONST_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore0_CONST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore0_CONST_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore0_CONST_UNSPECIFIED_OPEN
#  error Section OS_SystemApplication_OsCore0_CONST_UNSPECIFIED is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore0_CONST_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore0_CONST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore0_CONST_FAST_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore0_CONST_FAST_BOOLEAN_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom "OS_SystemApplication_OsCore0_CONST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom "OS_SystemApplication_OsCore0_CONST_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore0_CONST_FAST_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore0_CONST_FAST_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore0_CONST_FAST_BOOLEAN_OPEN
#  error Section OS_SystemApplication_OsCore0_CONST_FAST_BOOLEAN is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore0_CONST_FAST_BOOLEAN_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore0_CONST_FAST_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore0_CONST_FAST_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore0_CONST_FAST_8BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom "OS_SystemApplication_OsCore0_CONST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom "OS_SystemApplication_OsCore0_CONST_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore0_CONST_FAST_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore0_CONST_FAST_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore0_CONST_FAST_8BIT_OPEN
#  error Section OS_SystemApplication_OsCore0_CONST_FAST_8BIT is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore0_CONST_FAST_8BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore0_CONST_FAST_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore0_CONST_FAST_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore0_CONST_FAST_16BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom "OS_SystemApplication_OsCore0_CONST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom "OS_SystemApplication_OsCore0_CONST_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore0_CONST_FAST_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore0_CONST_FAST_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore0_CONST_FAST_16BIT_OPEN
#  error Section OS_SystemApplication_OsCore0_CONST_FAST_16BIT is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore0_CONST_FAST_16BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore0_CONST_FAST_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore0_CONST_FAST_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore0_CONST_FAST_32BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom "OS_SystemApplication_OsCore0_CONST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom "OS_SystemApplication_OsCore0_CONST_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore0_CONST_FAST_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore0_CONST_FAST_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore0_CONST_FAST_32BIT_OPEN
#  error Section OS_SystemApplication_OsCore0_CONST_FAST_32BIT is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore0_CONST_FAST_32BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore0_CONST_FAST_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore0_CONST_FAST_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore0_CONST_FAST_UNSPECIFIED_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom "OS_SystemApplication_OsCore0_CONST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom "OS_SystemApplication_OsCore0_CONST_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore0_CONST_FAST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore0_CONST_FAST_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore0_CONST_FAST_UNSPECIFIED_OPEN
#  error Section OS_SystemApplication_OsCore0_CONST_FAST_UNSPECIFIED is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore0_CONST_FAST_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore0_CONST_FAST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore1_CONST_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore1_CONST_BOOLEAN_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom "OS_SystemApplication_OsCore1_CONST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom "OS_SystemApplication_OsCore1_CONST_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore1_CONST_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore1_CONST_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore1_CONST_BOOLEAN_OPEN
#  error Section OS_SystemApplication_OsCore1_CONST_BOOLEAN is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore1_CONST_BOOLEAN_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore1_CONST_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore1_CONST_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore1_CONST_8BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom "OS_SystemApplication_OsCore1_CONST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom "OS_SystemApplication_OsCore1_CONST_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore1_CONST_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore1_CONST_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore1_CONST_8BIT_OPEN
#  error Section OS_SystemApplication_OsCore1_CONST_8BIT is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore1_CONST_8BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore1_CONST_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore1_CONST_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore1_CONST_16BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom "OS_SystemApplication_OsCore1_CONST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom "OS_SystemApplication_OsCore1_CONST_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore1_CONST_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore1_CONST_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore1_CONST_16BIT_OPEN
#  error Section OS_SystemApplication_OsCore1_CONST_16BIT is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore1_CONST_16BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore1_CONST_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore1_CONST_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore1_CONST_32BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom "OS_SystemApplication_OsCore1_CONST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom "OS_SystemApplication_OsCore1_CONST_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore1_CONST_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore1_CONST_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore1_CONST_32BIT_OPEN
#  error Section OS_SystemApplication_OsCore1_CONST_32BIT is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore1_CONST_32BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore1_CONST_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore1_CONST_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore1_CONST_UNSPECIFIED_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom "OS_SystemApplication_OsCore1_CONST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom "OS_SystemApplication_OsCore1_CONST_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore1_CONST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore1_CONST_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore1_CONST_UNSPECIFIED_OPEN
#  error Section OS_SystemApplication_OsCore1_CONST_UNSPECIFIED is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore1_CONST_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore1_CONST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore1_CONST_FAST_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore1_CONST_FAST_BOOLEAN_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom "OS_SystemApplication_OsCore1_CONST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom "OS_SystemApplication_OsCore1_CONST_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore1_CONST_FAST_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore1_CONST_FAST_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore1_CONST_FAST_BOOLEAN_OPEN
#  error Section OS_SystemApplication_OsCore1_CONST_FAST_BOOLEAN is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore1_CONST_FAST_BOOLEAN_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore1_CONST_FAST_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore1_CONST_FAST_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore1_CONST_FAST_8BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom "OS_SystemApplication_OsCore1_CONST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom "OS_SystemApplication_OsCore1_CONST_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore1_CONST_FAST_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore1_CONST_FAST_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore1_CONST_FAST_8BIT_OPEN
#  error Section OS_SystemApplication_OsCore1_CONST_FAST_8BIT is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore1_CONST_FAST_8BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore1_CONST_FAST_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore1_CONST_FAST_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore1_CONST_FAST_16BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom "OS_SystemApplication_OsCore1_CONST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom "OS_SystemApplication_OsCore1_CONST_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore1_CONST_FAST_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore1_CONST_FAST_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore1_CONST_FAST_16BIT_OPEN
#  error Section OS_SystemApplication_OsCore1_CONST_FAST_16BIT is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore1_CONST_FAST_16BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore1_CONST_FAST_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore1_CONST_FAST_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore1_CONST_FAST_32BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom "OS_SystemApplication_OsCore1_CONST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom "OS_SystemApplication_OsCore1_CONST_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore1_CONST_FAST_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore1_CONST_FAST_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore1_CONST_FAST_32BIT_OPEN
#  error Section OS_SystemApplication_OsCore1_CONST_FAST_32BIT is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore1_CONST_FAST_32BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore1_CONST_FAST_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore1_CONST_FAST_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore1_CONST_FAST_UNSPECIFIED_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom "OS_SystemApplication_OsCore1_CONST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom "OS_SystemApplication_OsCore1_CONST_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore1_CONST_FAST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore1_CONST_FAST_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore1_CONST_FAST_UNSPECIFIED_OPEN
#  error Section OS_SystemApplication_OsCore1_CONST_FAST_UNSPECIFIED is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore1_CONST_FAST_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore1_CONST_FAST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore2_CONST_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore2_CONST_BOOLEAN_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom "OS_SystemApplication_OsCore2_CONST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom "OS_SystemApplication_OsCore2_CONST_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore2_CONST_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore2_CONST_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore2_CONST_BOOLEAN_OPEN
#  error Section OS_SystemApplication_OsCore2_CONST_BOOLEAN is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore2_CONST_BOOLEAN_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore2_CONST_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore2_CONST_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore2_CONST_8BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom "OS_SystemApplication_OsCore2_CONST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom "OS_SystemApplication_OsCore2_CONST_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore2_CONST_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore2_CONST_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore2_CONST_8BIT_OPEN
#  error Section OS_SystemApplication_OsCore2_CONST_8BIT is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore2_CONST_8BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore2_CONST_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore2_CONST_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore2_CONST_16BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom "OS_SystemApplication_OsCore2_CONST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom "OS_SystemApplication_OsCore2_CONST_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore2_CONST_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore2_CONST_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore2_CONST_16BIT_OPEN
#  error Section OS_SystemApplication_OsCore2_CONST_16BIT is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore2_CONST_16BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore2_CONST_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore2_CONST_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore2_CONST_32BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom "OS_SystemApplication_OsCore2_CONST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom "OS_SystemApplication_OsCore2_CONST_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore2_CONST_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore2_CONST_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore2_CONST_32BIT_OPEN
#  error Section OS_SystemApplication_OsCore2_CONST_32BIT is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore2_CONST_32BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore2_CONST_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore2_CONST_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore2_CONST_UNSPECIFIED_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom "OS_SystemApplication_OsCore2_CONST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom "OS_SystemApplication_OsCore2_CONST_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore2_CONST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore2_CONST_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore2_CONST_UNSPECIFIED_OPEN
#  error Section OS_SystemApplication_OsCore2_CONST_UNSPECIFIED is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore2_CONST_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore2_CONST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore2_CONST_FAST_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore2_CONST_FAST_BOOLEAN_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom "OS_SystemApplication_OsCore2_CONST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom "OS_SystemApplication_OsCore2_CONST_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore2_CONST_FAST_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore2_CONST_FAST_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore2_CONST_FAST_BOOLEAN_OPEN
#  error Section OS_SystemApplication_OsCore2_CONST_FAST_BOOLEAN is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore2_CONST_FAST_BOOLEAN_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore2_CONST_FAST_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore2_CONST_FAST_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore2_CONST_FAST_8BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom "OS_SystemApplication_OsCore2_CONST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom "OS_SystemApplication_OsCore2_CONST_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore2_CONST_FAST_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore2_CONST_FAST_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore2_CONST_FAST_8BIT_OPEN
#  error Section OS_SystemApplication_OsCore2_CONST_FAST_8BIT is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore2_CONST_FAST_8BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore2_CONST_FAST_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore2_CONST_FAST_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore2_CONST_FAST_16BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom "OS_SystemApplication_OsCore2_CONST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom "OS_SystemApplication_OsCore2_CONST_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore2_CONST_FAST_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore2_CONST_FAST_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore2_CONST_FAST_16BIT_OPEN
#  error Section OS_SystemApplication_OsCore2_CONST_FAST_16BIT is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore2_CONST_FAST_16BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore2_CONST_FAST_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore2_CONST_FAST_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore2_CONST_FAST_32BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom "OS_SystemApplication_OsCore2_CONST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom "OS_SystemApplication_OsCore2_CONST_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore2_CONST_FAST_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore2_CONST_FAST_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore2_CONST_FAST_32BIT_OPEN
#  error Section OS_SystemApplication_OsCore2_CONST_FAST_32BIT is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore2_CONST_FAST_32BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore2_CONST_FAST_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore2_CONST_FAST_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore2_CONST_FAST_UNSPECIFIED_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom "OS_SystemApplication_OsCore2_CONST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom "OS_SystemApplication_OsCore2_CONST_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore2_CONST_FAST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore2_CONST_FAST_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore2_CONST_FAST_UNSPECIFIED_OPEN
#  error Section OS_SystemApplication_OsCore2_CONST_FAST_UNSPECIFIED is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore2_CONST_FAST_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearrom restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore2_CONST_FAST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif


/**********************************************************************************************************************
 *  VAR SECTIONS
 *********************************************************************************************************************/

#ifdef OS_START_SEC_GLOBALSHARED_VAR_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_GLOBALSHARED_VAR_BOOLEAN_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_GLOBALSHARED_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_GLOBALSHARED_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_GLOBALSHARED_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_GLOBALSHARED_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_GLOBALSHARED_VAR_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_GLOBALSHARED_VAR_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_GLOBALSHARED_VAR_BOOLEAN_OPEN
#  error Section OS_GLOBALSHARED_VAR_BOOLEAN is currently not opened and so cannot be closed.
# endif
# undef OS_GLOBALSHARED_VAR_BOOLEAN_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_GLOBALSHARED_VAR_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_GLOBALSHARED_VAR_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_GLOBALSHARED_VAR_8BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_GLOBALSHARED_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_GLOBALSHARED_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_GLOBALSHARED_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_GLOBALSHARED_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_GLOBALSHARED_VAR_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_GLOBALSHARED_VAR_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_GLOBALSHARED_VAR_8BIT_OPEN
#  error Section OS_GLOBALSHARED_VAR_8BIT is currently not opened and so cannot be closed.
# endif
# undef OS_GLOBALSHARED_VAR_8BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_GLOBALSHARED_VAR_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_GLOBALSHARED_VAR_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_GLOBALSHARED_VAR_16BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_GLOBALSHARED_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_GLOBALSHARED_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_GLOBALSHARED_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_GLOBALSHARED_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_GLOBALSHARED_VAR_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_GLOBALSHARED_VAR_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_GLOBALSHARED_VAR_16BIT_OPEN
#  error Section OS_GLOBALSHARED_VAR_16BIT is currently not opened and so cannot be closed.
# endif
# undef OS_GLOBALSHARED_VAR_16BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_GLOBALSHARED_VAR_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_GLOBALSHARED_VAR_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_GLOBALSHARED_VAR_32BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_GLOBALSHARED_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_GLOBALSHARED_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_GLOBALSHARED_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_GLOBALSHARED_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_GLOBALSHARED_VAR_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_GLOBALSHARED_VAR_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_GLOBALSHARED_VAR_32BIT_OPEN
#  error Section OS_GLOBALSHARED_VAR_32BIT is currently not opened and so cannot be closed.
# endif
# undef OS_GLOBALSHARED_VAR_32BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_GLOBALSHARED_VAR_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_GLOBALSHARED_VAR_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_GLOBALSHARED_VAR_UNSPECIFIED_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_GLOBALSHARED_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_GLOBALSHARED_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_GLOBALSHARED_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_GLOBALSHARED_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_GLOBALSHARED_VAR_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_GLOBALSHARED_VAR_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_GLOBALSHARED_VAR_UNSPECIFIED_OPEN
#  error Section OS_GLOBALSHARED_VAR_UNSPECIFIED is currently not opened and so cannot be closed.
# endif
# undef OS_GLOBALSHARED_VAR_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_GLOBALSHARED_VAR_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_GLOBALSHARED_VAR_NOINIT_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_GLOBALSHARED_VAR_NOINIT_BOOLEAN_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_GLOBALSHARED_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_GLOBALSHARED_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_GLOBALSHARED_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_GLOBALSHARED_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_GLOBALSHARED_VAR_NOINIT_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_GLOBALSHARED_VAR_NOINIT_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_GLOBALSHARED_VAR_NOINIT_BOOLEAN_OPEN
#  error Section OS_GLOBALSHARED_VAR_NOINIT_BOOLEAN is currently not opened and so cannot be closed.
# endif
# undef OS_GLOBALSHARED_VAR_NOINIT_BOOLEAN_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_GLOBALSHARED_VAR_NOINIT_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_GLOBALSHARED_VAR_NOINIT_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_GLOBALSHARED_VAR_NOINIT_8BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_GLOBALSHARED_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_GLOBALSHARED_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_GLOBALSHARED_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_GLOBALSHARED_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_GLOBALSHARED_VAR_NOINIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_GLOBALSHARED_VAR_NOINIT_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_GLOBALSHARED_VAR_NOINIT_8BIT_OPEN
#  error Section OS_GLOBALSHARED_VAR_NOINIT_8BIT is currently not opened and so cannot be closed.
# endif
# undef OS_GLOBALSHARED_VAR_NOINIT_8BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_GLOBALSHARED_VAR_NOINIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_GLOBALSHARED_VAR_NOINIT_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_GLOBALSHARED_VAR_NOINIT_16BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_GLOBALSHARED_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_GLOBALSHARED_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_GLOBALSHARED_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_GLOBALSHARED_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_GLOBALSHARED_VAR_NOINIT_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_GLOBALSHARED_VAR_NOINIT_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_GLOBALSHARED_VAR_NOINIT_16BIT_OPEN
#  error Section OS_GLOBALSHARED_VAR_NOINIT_16BIT is currently not opened and so cannot be closed.
# endif
# undef OS_GLOBALSHARED_VAR_NOINIT_16BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_GLOBALSHARED_VAR_NOINIT_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_GLOBALSHARED_VAR_NOINIT_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_GLOBALSHARED_VAR_NOINIT_32BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_GLOBALSHARED_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_GLOBALSHARED_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_GLOBALSHARED_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_GLOBALSHARED_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_GLOBALSHARED_VAR_NOINIT_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_GLOBALSHARED_VAR_NOINIT_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_GLOBALSHARED_VAR_NOINIT_32BIT_OPEN
#  error Section OS_GLOBALSHARED_VAR_NOINIT_32BIT is currently not opened and so cannot be closed.
# endif
# undef OS_GLOBALSHARED_VAR_NOINIT_32BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_GLOBALSHARED_VAR_NOINIT_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_GLOBALSHARED_VAR_NOINIT_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_GLOBALSHARED_VAR_NOINIT_UNSPECIFIED_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_GLOBALSHARED_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_GLOBALSHARED_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_GLOBALSHARED_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_GLOBALSHARED_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_GLOBALSHARED_VAR_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_GLOBALSHARED_VAR_NOINIT_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_GLOBALSHARED_VAR_NOINIT_UNSPECIFIED_OPEN
#  error Section OS_GLOBALSHARED_VAR_NOINIT_UNSPECIFIED is currently not opened and so cannot be closed.
# endif
# undef OS_GLOBALSHARED_VAR_NOINIT_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_GLOBALSHARED_VAR_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_GLOBALSHARED_VAR_ZERO_INIT_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_GLOBALSHARED_VAR_ZERO_INIT_BOOLEAN_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss "OS_GLOBALSHARED_VAR_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_GLOBALSHARED_VAR_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss "OS_GLOBALSHARED_VAR_FAST_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_GLOBALSHARED_VAR_FAST_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_GLOBALSHARED_VAR_ZERO_INIT_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_GLOBALSHARED_VAR_ZERO_INIT_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_GLOBALSHARED_VAR_ZERO_INIT_BOOLEAN_OPEN
#  error Section OS_GLOBALSHARED_VAR_ZERO_INIT_BOOLEAN is currently not opened and so cannot be closed.
# endif
# undef OS_GLOBALSHARED_VAR_ZERO_INIT_BOOLEAN_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_GLOBALSHARED_VAR_ZERO_INIT_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_GLOBALSHARED_VAR_ZERO_INIT_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_GLOBALSHARED_VAR_ZERO_INIT_8BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss "OS_GLOBALSHARED_VAR_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_GLOBALSHARED_VAR_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss "OS_GLOBALSHARED_VAR_FAST_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_GLOBALSHARED_VAR_FAST_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_GLOBALSHARED_VAR_ZERO_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_GLOBALSHARED_VAR_ZERO_INIT_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_GLOBALSHARED_VAR_ZERO_INIT_8BIT_OPEN
#  error Section OS_GLOBALSHARED_VAR_ZERO_INIT_8BIT is currently not opened and so cannot be closed.
# endif
# undef OS_GLOBALSHARED_VAR_ZERO_INIT_8BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_GLOBALSHARED_VAR_ZERO_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_GLOBALSHARED_VAR_ZERO_INIT_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_GLOBALSHARED_VAR_ZERO_INIT_16BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss "OS_GLOBALSHARED_VAR_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_GLOBALSHARED_VAR_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss "OS_GLOBALSHARED_VAR_FAST_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_GLOBALSHARED_VAR_FAST_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_GLOBALSHARED_VAR_ZERO_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_GLOBALSHARED_VAR_ZERO_INIT_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_GLOBALSHARED_VAR_ZERO_INIT_16BIT_OPEN
#  error Section OS_GLOBALSHARED_VAR_ZERO_INIT_16BIT is currently not opened and so cannot be closed.
# endif
# undef OS_GLOBALSHARED_VAR_ZERO_INIT_16BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_GLOBALSHARED_VAR_ZERO_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_GLOBALSHARED_VAR_ZERO_INIT_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_GLOBALSHARED_VAR_ZERO_INIT_32BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss "OS_GLOBALSHARED_VAR_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_GLOBALSHARED_VAR_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss "OS_GLOBALSHARED_VAR_FAST_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_GLOBALSHARED_VAR_FAST_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_GLOBALSHARED_VAR_ZERO_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_GLOBALSHARED_VAR_ZERO_INIT_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_GLOBALSHARED_VAR_ZERO_INIT_32BIT_OPEN
#  error Section OS_GLOBALSHARED_VAR_ZERO_INIT_32BIT is currently not opened and so cannot be closed.
# endif
# undef OS_GLOBALSHARED_VAR_ZERO_INIT_32BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_GLOBALSHARED_VAR_ZERO_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_GLOBALSHARED_VAR_ZERO_INIT_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_GLOBALSHARED_VAR_ZERO_INIT_UNSPECIFIED_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss "OS_GLOBALSHARED_VAR_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_GLOBALSHARED_VAR_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss "OS_GLOBALSHARED_VAR_FAST_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_GLOBALSHARED_VAR_FAST_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_GLOBALSHARED_VAR_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_GLOBALSHARED_VAR_ZERO_INIT_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_GLOBALSHARED_VAR_ZERO_INIT_UNSPECIFIED_OPEN
#  error Section OS_GLOBALSHARED_VAR_ZERO_INIT_UNSPECIFIED is currently not opened and so cannot be closed.
# endif
# undef OS_GLOBALSHARED_VAR_ZERO_INIT_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_GLOBALSHARED_VAR_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_GLOBALSHARED_VAR_FAST_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_GLOBALSHARED_VAR_FAST_BOOLEAN_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_GLOBALSHARED_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_GLOBALSHARED_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_GLOBALSHARED_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_GLOBALSHARED_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_GLOBALSHARED_VAR_FAST_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_GLOBALSHARED_VAR_FAST_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_GLOBALSHARED_VAR_FAST_BOOLEAN_OPEN
#  error Section OS_GLOBALSHARED_VAR_FAST_BOOLEAN is currently not opened and so cannot be closed.
# endif
# undef OS_GLOBALSHARED_VAR_FAST_BOOLEAN_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_GLOBALSHARED_VAR_FAST_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_GLOBALSHARED_VAR_FAST_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_GLOBALSHARED_VAR_FAST_8BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_GLOBALSHARED_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_GLOBALSHARED_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_GLOBALSHARED_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_GLOBALSHARED_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_GLOBALSHARED_VAR_FAST_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_GLOBALSHARED_VAR_FAST_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_GLOBALSHARED_VAR_FAST_8BIT_OPEN
#  error Section OS_GLOBALSHARED_VAR_FAST_8BIT is currently not opened and so cannot be closed.
# endif
# undef OS_GLOBALSHARED_VAR_FAST_8BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_GLOBALSHARED_VAR_FAST_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_GLOBALSHARED_VAR_FAST_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_GLOBALSHARED_VAR_FAST_16BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_GLOBALSHARED_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_GLOBALSHARED_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_GLOBALSHARED_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_GLOBALSHARED_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_GLOBALSHARED_VAR_FAST_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_GLOBALSHARED_VAR_FAST_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_GLOBALSHARED_VAR_FAST_16BIT_OPEN
#  error Section OS_GLOBALSHARED_VAR_FAST_16BIT is currently not opened and so cannot be closed.
# endif
# undef OS_GLOBALSHARED_VAR_FAST_16BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_GLOBALSHARED_VAR_FAST_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_GLOBALSHARED_VAR_FAST_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_GLOBALSHARED_VAR_FAST_32BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_GLOBALSHARED_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_GLOBALSHARED_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_GLOBALSHARED_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_GLOBALSHARED_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_GLOBALSHARED_VAR_FAST_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_GLOBALSHARED_VAR_FAST_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_GLOBALSHARED_VAR_FAST_32BIT_OPEN
#  error Section OS_GLOBALSHARED_VAR_FAST_32BIT is currently not opened and so cannot be closed.
# endif
# undef OS_GLOBALSHARED_VAR_FAST_32BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_GLOBALSHARED_VAR_FAST_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_GLOBALSHARED_VAR_FAST_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_GLOBALSHARED_VAR_FAST_UNSPECIFIED_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_GLOBALSHARED_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_GLOBALSHARED_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_GLOBALSHARED_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_GLOBALSHARED_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_GLOBALSHARED_VAR_FAST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_GLOBALSHARED_VAR_FAST_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_GLOBALSHARED_VAR_FAST_UNSPECIFIED_OPEN
#  error Section OS_GLOBALSHARED_VAR_FAST_UNSPECIFIED is currently not opened and so cannot be closed.
# endif
# undef OS_GLOBALSHARED_VAR_FAST_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_GLOBALSHARED_VAR_FAST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_GLOBALSHARED_VAR_FAST_NOINIT_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_GLOBALSHARED_VAR_FAST_NOINIT_BOOLEAN_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_GLOBALSHARED_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_GLOBALSHARED_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_GLOBALSHARED_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_GLOBALSHARED_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_GLOBALSHARED_VAR_FAST_NOINIT_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_GLOBALSHARED_VAR_FAST_NOINIT_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_GLOBALSHARED_VAR_FAST_NOINIT_BOOLEAN_OPEN
#  error Section OS_GLOBALSHARED_VAR_FAST_NOINIT_BOOLEAN is currently not opened and so cannot be closed.
# endif
# undef OS_GLOBALSHARED_VAR_FAST_NOINIT_BOOLEAN_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_GLOBALSHARED_VAR_FAST_NOINIT_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_GLOBALSHARED_VAR_FAST_NOINIT_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_GLOBALSHARED_VAR_FAST_NOINIT_8BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_GLOBALSHARED_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_GLOBALSHARED_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_GLOBALSHARED_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_GLOBALSHARED_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_GLOBALSHARED_VAR_FAST_NOINIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_GLOBALSHARED_VAR_FAST_NOINIT_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_GLOBALSHARED_VAR_FAST_NOINIT_8BIT_OPEN
#  error Section OS_GLOBALSHARED_VAR_FAST_NOINIT_8BIT is currently not opened and so cannot be closed.
# endif
# undef OS_GLOBALSHARED_VAR_FAST_NOINIT_8BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_GLOBALSHARED_VAR_FAST_NOINIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_GLOBALSHARED_VAR_FAST_NOINIT_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_GLOBALSHARED_VAR_FAST_NOINIT_16BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_GLOBALSHARED_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_GLOBALSHARED_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_GLOBALSHARED_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_GLOBALSHARED_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_GLOBALSHARED_VAR_FAST_NOINIT_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_GLOBALSHARED_VAR_FAST_NOINIT_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_GLOBALSHARED_VAR_FAST_NOINIT_16BIT_OPEN
#  error Section OS_GLOBALSHARED_VAR_FAST_NOINIT_16BIT is currently not opened and so cannot be closed.
# endif
# undef OS_GLOBALSHARED_VAR_FAST_NOINIT_16BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_GLOBALSHARED_VAR_FAST_NOINIT_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_GLOBALSHARED_VAR_FAST_NOINIT_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_GLOBALSHARED_VAR_FAST_NOINIT_32BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_GLOBALSHARED_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_GLOBALSHARED_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_GLOBALSHARED_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_GLOBALSHARED_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_GLOBALSHARED_VAR_FAST_NOINIT_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_GLOBALSHARED_VAR_FAST_NOINIT_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_GLOBALSHARED_VAR_FAST_NOINIT_32BIT_OPEN
#  error Section OS_GLOBALSHARED_VAR_FAST_NOINIT_32BIT is currently not opened and so cannot be closed.
# endif
# undef OS_GLOBALSHARED_VAR_FAST_NOINIT_32BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_GLOBALSHARED_VAR_FAST_NOINIT_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_GLOBALSHARED_VAR_FAST_NOINIT_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_GLOBALSHARED_VAR_FAST_NOINIT_UNSPECIFIED_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_GLOBALSHARED_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_GLOBALSHARED_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_GLOBALSHARED_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_GLOBALSHARED_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_GLOBALSHARED_VAR_FAST_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_GLOBALSHARED_VAR_FAST_NOINIT_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_GLOBALSHARED_VAR_FAST_NOINIT_UNSPECIFIED_OPEN
#  error Section OS_GLOBALSHARED_VAR_FAST_NOINIT_UNSPECIFIED is currently not opened and so cannot be closed.
# endif
# undef OS_GLOBALSHARED_VAR_FAST_NOINIT_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_GLOBALSHARED_VAR_FAST_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_GLOBALSHARED_VAR_FAST_ZERO_INIT_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_GLOBALSHARED_VAR_FAST_ZERO_INIT_BOOLEAN_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss "OS_GLOBALSHARED_VAR_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_GLOBALSHARED_VAR_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss "OS_GLOBALSHARED_VAR_FAST_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_GLOBALSHARED_VAR_FAST_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_GLOBALSHARED_VAR_FAST_ZERO_INIT_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_GLOBALSHARED_VAR_FAST_ZERO_INIT_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_GLOBALSHARED_VAR_FAST_ZERO_INIT_BOOLEAN_OPEN
#  error Section OS_GLOBALSHARED_VAR_FAST_ZERO_INIT_BOOLEAN is currently not opened and so cannot be closed.
# endif
# undef OS_GLOBALSHARED_VAR_FAST_ZERO_INIT_BOOLEAN_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_GLOBALSHARED_VAR_FAST_ZERO_INIT_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_GLOBALSHARED_VAR_FAST_ZERO_INIT_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_GLOBALSHARED_VAR_FAST_ZERO_INIT_8BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss "OS_GLOBALSHARED_VAR_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_GLOBALSHARED_VAR_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss "OS_GLOBALSHARED_VAR_FAST_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_GLOBALSHARED_VAR_FAST_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_GLOBALSHARED_VAR_FAST_ZERO_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_GLOBALSHARED_VAR_FAST_ZERO_INIT_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_GLOBALSHARED_VAR_FAST_ZERO_INIT_8BIT_OPEN
#  error Section OS_GLOBALSHARED_VAR_FAST_ZERO_INIT_8BIT is currently not opened and so cannot be closed.
# endif
# undef OS_GLOBALSHARED_VAR_FAST_ZERO_INIT_8BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_GLOBALSHARED_VAR_FAST_ZERO_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_GLOBALSHARED_VAR_FAST_ZERO_INIT_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_GLOBALSHARED_VAR_FAST_ZERO_INIT_16BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss "OS_GLOBALSHARED_VAR_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_GLOBALSHARED_VAR_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss "OS_GLOBALSHARED_VAR_FAST_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_GLOBALSHARED_VAR_FAST_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_GLOBALSHARED_VAR_FAST_ZERO_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_GLOBALSHARED_VAR_FAST_ZERO_INIT_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_GLOBALSHARED_VAR_FAST_ZERO_INIT_16BIT_OPEN
#  error Section OS_GLOBALSHARED_VAR_FAST_ZERO_INIT_16BIT is currently not opened and so cannot be closed.
# endif
# undef OS_GLOBALSHARED_VAR_FAST_ZERO_INIT_16BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_GLOBALSHARED_VAR_FAST_ZERO_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_GLOBALSHARED_VAR_FAST_ZERO_INIT_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_GLOBALSHARED_VAR_FAST_ZERO_INIT_32BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss "OS_GLOBALSHARED_VAR_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_GLOBALSHARED_VAR_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss "OS_GLOBALSHARED_VAR_FAST_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_GLOBALSHARED_VAR_FAST_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_GLOBALSHARED_VAR_FAST_ZERO_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_GLOBALSHARED_VAR_FAST_ZERO_INIT_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_GLOBALSHARED_VAR_FAST_ZERO_INIT_32BIT_OPEN
#  error Section OS_GLOBALSHARED_VAR_FAST_ZERO_INIT_32BIT is currently not opened and so cannot be closed.
# endif
# undef OS_GLOBALSHARED_VAR_FAST_ZERO_INIT_32BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_GLOBALSHARED_VAR_FAST_ZERO_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_GLOBALSHARED_VAR_FAST_ZERO_INIT_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_GLOBALSHARED_VAR_FAST_ZERO_INIT_UNSPECIFIED_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss "OS_GLOBALSHARED_VAR_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_GLOBALSHARED_VAR_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss "OS_GLOBALSHARED_VAR_FAST_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_GLOBALSHARED_VAR_FAST_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_GLOBALSHARED_VAR_FAST_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_GLOBALSHARED_VAR_FAST_ZERO_INIT_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_GLOBALSHARED_VAR_FAST_ZERO_INIT_UNSPECIFIED_OPEN
#  error Section OS_GLOBALSHARED_VAR_FAST_ZERO_INIT_UNSPECIFIED is currently not opened and so cannot be closed.
# endif
# undef OS_GLOBALSHARED_VAR_FAST_ZERO_INIT_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_GLOBALSHARED_VAR_FAST_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_GLOBALSHARED_VAR_NOCACHE_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_GLOBALSHARED_VAR_NOCACHE_BOOLEAN_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_GLOBALSHARED_VAR_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_GLOBALSHARED_VAR_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_GLOBALSHARED_VAR_FAST_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_GLOBALSHARED_VAR_FAST_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_GLOBALSHARED_VAR_NOCACHE_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_GLOBALSHARED_VAR_NOCACHE_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_GLOBALSHARED_VAR_NOCACHE_BOOLEAN_OPEN
#  error Section OS_GLOBALSHARED_VAR_NOCACHE_BOOLEAN is currently not opened and so cannot be closed.
# endif
# undef OS_GLOBALSHARED_VAR_NOCACHE_BOOLEAN_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_GLOBALSHARED_VAR_NOCACHE_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_GLOBALSHARED_VAR_NOCACHE_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_GLOBALSHARED_VAR_NOCACHE_8BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_GLOBALSHARED_VAR_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_GLOBALSHARED_VAR_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_GLOBALSHARED_VAR_FAST_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_GLOBALSHARED_VAR_FAST_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_GLOBALSHARED_VAR_NOCACHE_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_GLOBALSHARED_VAR_NOCACHE_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_GLOBALSHARED_VAR_NOCACHE_8BIT_OPEN
#  error Section OS_GLOBALSHARED_VAR_NOCACHE_8BIT is currently not opened and so cannot be closed.
# endif
# undef OS_GLOBALSHARED_VAR_NOCACHE_8BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_GLOBALSHARED_VAR_NOCACHE_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_GLOBALSHARED_VAR_NOCACHE_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_GLOBALSHARED_VAR_NOCACHE_16BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_GLOBALSHARED_VAR_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_GLOBALSHARED_VAR_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_GLOBALSHARED_VAR_FAST_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_GLOBALSHARED_VAR_FAST_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_GLOBALSHARED_VAR_NOCACHE_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_GLOBALSHARED_VAR_NOCACHE_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_GLOBALSHARED_VAR_NOCACHE_16BIT_OPEN
#  error Section OS_GLOBALSHARED_VAR_NOCACHE_16BIT is currently not opened and so cannot be closed.
# endif
# undef OS_GLOBALSHARED_VAR_NOCACHE_16BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_GLOBALSHARED_VAR_NOCACHE_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_GLOBALSHARED_VAR_NOCACHE_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_GLOBALSHARED_VAR_NOCACHE_32BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_GLOBALSHARED_VAR_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_GLOBALSHARED_VAR_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_GLOBALSHARED_VAR_FAST_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_GLOBALSHARED_VAR_FAST_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_GLOBALSHARED_VAR_NOCACHE_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_GLOBALSHARED_VAR_NOCACHE_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_GLOBALSHARED_VAR_NOCACHE_32BIT_OPEN
#  error Section OS_GLOBALSHARED_VAR_NOCACHE_32BIT is currently not opened and so cannot be closed.
# endif
# undef OS_GLOBALSHARED_VAR_NOCACHE_32BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_GLOBALSHARED_VAR_NOCACHE_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_GLOBALSHARED_VAR_NOCACHE_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_GLOBALSHARED_VAR_NOCACHE_UNSPECIFIED_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_GLOBALSHARED_VAR_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_GLOBALSHARED_VAR_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_GLOBALSHARED_VAR_FAST_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_GLOBALSHARED_VAR_FAST_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_GLOBALSHARED_VAR_NOCACHE_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_GLOBALSHARED_VAR_NOCACHE_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_GLOBALSHARED_VAR_NOCACHE_UNSPECIFIED_OPEN
#  error Section OS_GLOBALSHARED_VAR_NOCACHE_UNSPECIFIED is currently not opened and so cannot be closed.
# endif
# undef OS_GLOBALSHARED_VAR_NOCACHE_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_GLOBALSHARED_VAR_NOCACHE_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_GLOBALSHARED_VAR_NOCACHE_NOINIT_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_GLOBALSHARED_VAR_NOCACHE_NOINIT_BOOLEAN_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_GLOBALSHARED_VAR_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_GLOBALSHARED_VAR_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_GLOBALSHARED_VAR_FAST_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_GLOBALSHARED_VAR_FAST_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_GLOBALSHARED_VAR_NOCACHE_NOINIT_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_GLOBALSHARED_VAR_NOCACHE_NOINIT_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_GLOBALSHARED_VAR_NOCACHE_NOINIT_BOOLEAN_OPEN
#  error Section OS_GLOBALSHARED_VAR_NOCACHE_NOINIT_BOOLEAN is currently not opened and so cannot be closed.
# endif
# undef OS_GLOBALSHARED_VAR_NOCACHE_NOINIT_BOOLEAN_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_GLOBALSHARED_VAR_NOCACHE_NOINIT_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_GLOBALSHARED_VAR_NOCACHE_NOINIT_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_GLOBALSHARED_VAR_NOCACHE_NOINIT_8BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_GLOBALSHARED_VAR_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_GLOBALSHARED_VAR_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_GLOBALSHARED_VAR_FAST_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_GLOBALSHARED_VAR_FAST_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_GLOBALSHARED_VAR_NOCACHE_NOINIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_GLOBALSHARED_VAR_NOCACHE_NOINIT_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_GLOBALSHARED_VAR_NOCACHE_NOINIT_8BIT_OPEN
#  error Section OS_GLOBALSHARED_VAR_NOCACHE_NOINIT_8BIT is currently not opened and so cannot be closed.
# endif
# undef OS_GLOBALSHARED_VAR_NOCACHE_NOINIT_8BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_GLOBALSHARED_VAR_NOCACHE_NOINIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_GLOBALSHARED_VAR_NOCACHE_NOINIT_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_GLOBALSHARED_VAR_NOCACHE_NOINIT_16BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_GLOBALSHARED_VAR_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_GLOBALSHARED_VAR_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_GLOBALSHARED_VAR_FAST_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_GLOBALSHARED_VAR_FAST_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_GLOBALSHARED_VAR_NOCACHE_NOINIT_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_GLOBALSHARED_VAR_NOCACHE_NOINIT_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_GLOBALSHARED_VAR_NOCACHE_NOINIT_16BIT_OPEN
#  error Section OS_GLOBALSHARED_VAR_NOCACHE_NOINIT_16BIT is currently not opened and so cannot be closed.
# endif
# undef OS_GLOBALSHARED_VAR_NOCACHE_NOINIT_16BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_GLOBALSHARED_VAR_NOCACHE_NOINIT_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_GLOBALSHARED_VAR_NOCACHE_NOINIT_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_GLOBALSHARED_VAR_NOCACHE_NOINIT_32BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_GLOBALSHARED_VAR_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_GLOBALSHARED_VAR_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_GLOBALSHARED_VAR_FAST_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_GLOBALSHARED_VAR_FAST_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_GLOBALSHARED_VAR_NOCACHE_NOINIT_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_GLOBALSHARED_VAR_NOCACHE_NOINIT_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_GLOBALSHARED_VAR_NOCACHE_NOINIT_32BIT_OPEN
#  error Section OS_GLOBALSHARED_VAR_NOCACHE_NOINIT_32BIT is currently not opened and so cannot be closed.
# endif
# undef OS_GLOBALSHARED_VAR_NOCACHE_NOINIT_32BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_GLOBALSHARED_VAR_NOCACHE_NOINIT_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_GLOBALSHARED_VAR_NOCACHE_NOINIT_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_GLOBALSHARED_VAR_NOCACHE_NOINIT_UNSPECIFIED_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_GLOBALSHARED_VAR_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_GLOBALSHARED_VAR_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_GLOBALSHARED_VAR_FAST_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_GLOBALSHARED_VAR_FAST_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_GLOBALSHARED_VAR_NOCACHE_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_GLOBALSHARED_VAR_NOCACHE_NOINIT_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_GLOBALSHARED_VAR_NOCACHE_NOINIT_UNSPECIFIED_OPEN
#  error Section OS_GLOBALSHARED_VAR_NOCACHE_NOINIT_UNSPECIFIED is currently not opened and so cannot be closed.
# endif
# undef OS_GLOBALSHARED_VAR_NOCACHE_NOINIT_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_GLOBALSHARED_VAR_NOCACHE_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_GLOBALSHARED_VAR_NOCACHE_ZERO_INIT_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_GLOBALSHARED_VAR_NOCACHE_ZERO_INIT_BOOLEAN_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss "OS_GLOBALSHARED_VAR_NOCACHE_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_GLOBALSHARED_VAR_NOCACHE_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss "OS_GLOBALSHARED_VAR_FAST_NOCACHE_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_GLOBALSHARED_VAR_FAST_NOCACHE_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_GLOBALSHARED_VAR_NOCACHE_ZERO_INIT_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_GLOBALSHARED_VAR_NOCACHE_ZERO_INIT_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_GLOBALSHARED_VAR_NOCACHE_ZERO_INIT_BOOLEAN_OPEN
#  error Section OS_GLOBALSHARED_VAR_NOCACHE_ZERO_INIT_BOOLEAN is currently not opened and so cannot be closed.
# endif
# undef OS_GLOBALSHARED_VAR_NOCACHE_ZERO_INIT_BOOLEAN_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_GLOBALSHARED_VAR_NOCACHE_ZERO_INIT_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_GLOBALSHARED_VAR_NOCACHE_ZERO_INIT_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_GLOBALSHARED_VAR_NOCACHE_ZERO_INIT_8BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss "OS_GLOBALSHARED_VAR_NOCACHE_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_GLOBALSHARED_VAR_NOCACHE_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss "OS_GLOBALSHARED_VAR_FAST_NOCACHE_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_GLOBALSHARED_VAR_FAST_NOCACHE_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_GLOBALSHARED_VAR_NOCACHE_ZERO_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_GLOBALSHARED_VAR_NOCACHE_ZERO_INIT_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_GLOBALSHARED_VAR_NOCACHE_ZERO_INIT_8BIT_OPEN
#  error Section OS_GLOBALSHARED_VAR_NOCACHE_ZERO_INIT_8BIT is currently not opened and so cannot be closed.
# endif
# undef OS_GLOBALSHARED_VAR_NOCACHE_ZERO_INIT_8BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_GLOBALSHARED_VAR_NOCACHE_ZERO_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_GLOBALSHARED_VAR_NOCACHE_ZERO_INIT_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_GLOBALSHARED_VAR_NOCACHE_ZERO_INIT_16BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss "OS_GLOBALSHARED_VAR_NOCACHE_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_GLOBALSHARED_VAR_NOCACHE_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss "OS_GLOBALSHARED_VAR_FAST_NOCACHE_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_GLOBALSHARED_VAR_FAST_NOCACHE_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_GLOBALSHARED_VAR_NOCACHE_ZERO_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_GLOBALSHARED_VAR_NOCACHE_ZERO_INIT_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_GLOBALSHARED_VAR_NOCACHE_ZERO_INIT_16BIT_OPEN
#  error Section OS_GLOBALSHARED_VAR_NOCACHE_ZERO_INIT_16BIT is currently not opened and so cannot be closed.
# endif
# undef OS_GLOBALSHARED_VAR_NOCACHE_ZERO_INIT_16BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_GLOBALSHARED_VAR_NOCACHE_ZERO_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_GLOBALSHARED_VAR_NOCACHE_ZERO_INIT_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_GLOBALSHARED_VAR_NOCACHE_ZERO_INIT_32BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss "OS_GLOBALSHARED_VAR_NOCACHE_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_GLOBALSHARED_VAR_NOCACHE_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss "OS_GLOBALSHARED_VAR_FAST_NOCACHE_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_GLOBALSHARED_VAR_FAST_NOCACHE_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_GLOBALSHARED_VAR_NOCACHE_ZERO_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_GLOBALSHARED_VAR_NOCACHE_ZERO_INIT_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_GLOBALSHARED_VAR_NOCACHE_ZERO_INIT_32BIT_OPEN
#  error Section OS_GLOBALSHARED_VAR_NOCACHE_ZERO_INIT_32BIT is currently not opened and so cannot be closed.
# endif
# undef OS_GLOBALSHARED_VAR_NOCACHE_ZERO_INIT_32BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_GLOBALSHARED_VAR_NOCACHE_ZERO_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_GLOBALSHARED_VAR_NOCACHE_ZERO_INIT_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_GLOBALSHARED_VAR_NOCACHE_ZERO_INIT_UNSPECIFIED_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss "OS_GLOBALSHARED_VAR_NOCACHE_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_GLOBALSHARED_VAR_NOCACHE_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss "OS_GLOBALSHARED_VAR_FAST_NOCACHE_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_GLOBALSHARED_VAR_FAST_NOCACHE_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_GLOBALSHARED_VAR_NOCACHE_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_GLOBALSHARED_VAR_NOCACHE_ZERO_INIT_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_GLOBALSHARED_VAR_NOCACHE_ZERO_INIT_UNSPECIFIED_OPEN
#  error Section OS_GLOBALSHARED_VAR_NOCACHE_ZERO_INIT_UNSPECIFIED is currently not opened and so cannot be closed.
# endif
# undef OS_GLOBALSHARED_VAR_NOCACHE_ZERO_INIT_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_GLOBALSHARED_VAR_NOCACHE_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core0_VAR_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core0_VAR_BOOLEAN_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_OsApplication_Core0_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core0_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_OsApplication_Core0_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core0_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core0_VAR_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core0_VAR_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core0_VAR_BOOLEAN_OPEN
#  error Section OS_OsApplication_Core0_VAR_BOOLEAN is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core0_VAR_BOOLEAN_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core0_VAR_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core0_VAR_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core0_VAR_8BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_OsApplication_Core0_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core0_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_OsApplication_Core0_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core0_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core0_VAR_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core0_VAR_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core0_VAR_8BIT_OPEN
#  error Section OS_OsApplication_Core0_VAR_8BIT is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core0_VAR_8BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core0_VAR_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core0_VAR_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core0_VAR_16BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_OsApplication_Core0_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core0_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_OsApplication_Core0_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core0_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core0_VAR_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core0_VAR_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core0_VAR_16BIT_OPEN
#  error Section OS_OsApplication_Core0_VAR_16BIT is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core0_VAR_16BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core0_VAR_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core0_VAR_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core0_VAR_32BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_OsApplication_Core0_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core0_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_OsApplication_Core0_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core0_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core0_VAR_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core0_VAR_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core0_VAR_32BIT_OPEN
#  error Section OS_OsApplication_Core0_VAR_32BIT is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core0_VAR_32BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core0_VAR_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core0_VAR_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core0_VAR_UNSPECIFIED_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_OsApplication_Core0_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core0_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_OsApplication_Core0_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core0_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core0_VAR_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core0_VAR_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core0_VAR_UNSPECIFIED_OPEN
#  error Section OS_OsApplication_Core0_VAR_UNSPECIFIED is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core0_VAR_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core0_VAR_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core0_VAR_NOINIT_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core0_VAR_NOINIT_BOOLEAN_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_OsApplication_Core0_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core0_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_OsApplication_Core0_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core0_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core0_VAR_NOINIT_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core0_VAR_NOINIT_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core0_VAR_NOINIT_BOOLEAN_OPEN
#  error Section OS_OsApplication_Core0_VAR_NOINIT_BOOLEAN is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core0_VAR_NOINIT_BOOLEAN_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core0_VAR_NOINIT_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core0_VAR_NOINIT_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core0_VAR_NOINIT_8BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_OsApplication_Core0_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core0_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_OsApplication_Core0_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core0_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core0_VAR_NOINIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core0_VAR_NOINIT_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core0_VAR_NOINIT_8BIT_OPEN
#  error Section OS_OsApplication_Core0_VAR_NOINIT_8BIT is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core0_VAR_NOINIT_8BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core0_VAR_NOINIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core0_VAR_NOINIT_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core0_VAR_NOINIT_16BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_OsApplication_Core0_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core0_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_OsApplication_Core0_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core0_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core0_VAR_NOINIT_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core0_VAR_NOINIT_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core0_VAR_NOINIT_16BIT_OPEN
#  error Section OS_OsApplication_Core0_VAR_NOINIT_16BIT is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core0_VAR_NOINIT_16BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core0_VAR_NOINIT_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core0_VAR_NOINIT_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core0_VAR_NOINIT_32BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_OsApplication_Core0_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core0_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_OsApplication_Core0_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core0_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core0_VAR_NOINIT_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core0_VAR_NOINIT_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core0_VAR_NOINIT_32BIT_OPEN
#  error Section OS_OsApplication_Core0_VAR_NOINIT_32BIT is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core0_VAR_NOINIT_32BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core0_VAR_NOINIT_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core0_VAR_NOINIT_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core0_VAR_NOINIT_UNSPECIFIED_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_OsApplication_Core0_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core0_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_OsApplication_Core0_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core0_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core0_VAR_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core0_VAR_NOINIT_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core0_VAR_NOINIT_UNSPECIFIED_OPEN
#  error Section OS_OsApplication_Core0_VAR_NOINIT_UNSPECIFIED is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core0_VAR_NOINIT_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core0_VAR_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core0_VAR_ZERO_INIT_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core0_VAR_ZERO_INIT_BOOLEAN_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss "OS_OsApplication_Core0_VAR_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core0_VAR_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss "OS_OsApplication_Core0_VAR_FAST_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core0_VAR_FAST_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core0_VAR_ZERO_INIT_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core0_VAR_ZERO_INIT_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core0_VAR_ZERO_INIT_BOOLEAN_OPEN
#  error Section OS_OsApplication_Core0_VAR_ZERO_INIT_BOOLEAN is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core0_VAR_ZERO_INIT_BOOLEAN_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core0_VAR_ZERO_INIT_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core0_VAR_ZERO_INIT_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core0_VAR_ZERO_INIT_8BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss "OS_OsApplication_Core0_VAR_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core0_VAR_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss "OS_OsApplication_Core0_VAR_FAST_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core0_VAR_FAST_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core0_VAR_ZERO_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core0_VAR_ZERO_INIT_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core0_VAR_ZERO_INIT_8BIT_OPEN
#  error Section OS_OsApplication_Core0_VAR_ZERO_INIT_8BIT is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core0_VAR_ZERO_INIT_8BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core0_VAR_ZERO_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core0_VAR_ZERO_INIT_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core0_VAR_ZERO_INIT_16BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss "OS_OsApplication_Core0_VAR_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core0_VAR_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss "OS_OsApplication_Core0_VAR_FAST_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core0_VAR_FAST_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core0_VAR_ZERO_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core0_VAR_ZERO_INIT_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core0_VAR_ZERO_INIT_16BIT_OPEN
#  error Section OS_OsApplication_Core0_VAR_ZERO_INIT_16BIT is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core0_VAR_ZERO_INIT_16BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core0_VAR_ZERO_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core0_VAR_ZERO_INIT_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core0_VAR_ZERO_INIT_32BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss "OS_OsApplication_Core0_VAR_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core0_VAR_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss "OS_OsApplication_Core0_VAR_FAST_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core0_VAR_FAST_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core0_VAR_ZERO_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core0_VAR_ZERO_INIT_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core0_VAR_ZERO_INIT_32BIT_OPEN
#  error Section OS_OsApplication_Core0_VAR_ZERO_INIT_32BIT is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core0_VAR_ZERO_INIT_32BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core0_VAR_ZERO_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core0_VAR_ZERO_INIT_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core0_VAR_ZERO_INIT_UNSPECIFIED_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss "OS_OsApplication_Core0_VAR_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core0_VAR_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss "OS_OsApplication_Core0_VAR_FAST_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core0_VAR_FAST_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core0_VAR_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core0_VAR_ZERO_INIT_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core0_VAR_ZERO_INIT_UNSPECIFIED_OPEN
#  error Section OS_OsApplication_Core0_VAR_ZERO_INIT_UNSPECIFIED is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core0_VAR_ZERO_INIT_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core0_VAR_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core0_VAR_FAST_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core0_VAR_FAST_BOOLEAN_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_OsApplication_Core0_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core0_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_OsApplication_Core0_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core0_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core0_VAR_FAST_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core0_VAR_FAST_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core0_VAR_FAST_BOOLEAN_OPEN
#  error Section OS_OsApplication_Core0_VAR_FAST_BOOLEAN is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core0_VAR_FAST_BOOLEAN_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core0_VAR_FAST_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core0_VAR_FAST_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core0_VAR_FAST_8BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_OsApplication_Core0_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core0_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_OsApplication_Core0_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core0_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core0_VAR_FAST_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core0_VAR_FAST_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core0_VAR_FAST_8BIT_OPEN
#  error Section OS_OsApplication_Core0_VAR_FAST_8BIT is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core0_VAR_FAST_8BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core0_VAR_FAST_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core0_VAR_FAST_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core0_VAR_FAST_16BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_OsApplication_Core0_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core0_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_OsApplication_Core0_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core0_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core0_VAR_FAST_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core0_VAR_FAST_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core0_VAR_FAST_16BIT_OPEN
#  error Section OS_OsApplication_Core0_VAR_FAST_16BIT is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core0_VAR_FAST_16BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core0_VAR_FAST_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core0_VAR_FAST_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core0_VAR_FAST_32BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_OsApplication_Core0_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core0_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_OsApplication_Core0_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core0_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core0_VAR_FAST_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core0_VAR_FAST_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core0_VAR_FAST_32BIT_OPEN
#  error Section OS_OsApplication_Core0_VAR_FAST_32BIT is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core0_VAR_FAST_32BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core0_VAR_FAST_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core0_VAR_FAST_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core0_VAR_FAST_UNSPECIFIED_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_OsApplication_Core0_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core0_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_OsApplication_Core0_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core0_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core0_VAR_FAST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core0_VAR_FAST_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core0_VAR_FAST_UNSPECIFIED_OPEN
#  error Section OS_OsApplication_Core0_VAR_FAST_UNSPECIFIED is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core0_VAR_FAST_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core0_VAR_FAST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core0_VAR_FAST_NOINIT_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core0_VAR_FAST_NOINIT_BOOLEAN_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_OsApplication_Core0_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core0_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_OsApplication_Core0_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core0_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core0_VAR_FAST_NOINIT_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core0_VAR_FAST_NOINIT_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core0_VAR_FAST_NOINIT_BOOLEAN_OPEN
#  error Section OS_OsApplication_Core0_VAR_FAST_NOINIT_BOOLEAN is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core0_VAR_FAST_NOINIT_BOOLEAN_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core0_VAR_FAST_NOINIT_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core0_VAR_FAST_NOINIT_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core0_VAR_FAST_NOINIT_8BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_OsApplication_Core0_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core0_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_OsApplication_Core0_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core0_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core0_VAR_FAST_NOINIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core0_VAR_FAST_NOINIT_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core0_VAR_FAST_NOINIT_8BIT_OPEN
#  error Section OS_OsApplication_Core0_VAR_FAST_NOINIT_8BIT is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core0_VAR_FAST_NOINIT_8BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core0_VAR_FAST_NOINIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core0_VAR_FAST_NOINIT_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core0_VAR_FAST_NOINIT_16BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_OsApplication_Core0_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core0_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_OsApplication_Core0_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core0_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core0_VAR_FAST_NOINIT_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core0_VAR_FAST_NOINIT_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core0_VAR_FAST_NOINIT_16BIT_OPEN
#  error Section OS_OsApplication_Core0_VAR_FAST_NOINIT_16BIT is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core0_VAR_FAST_NOINIT_16BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core0_VAR_FAST_NOINIT_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core0_VAR_FAST_NOINIT_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core0_VAR_FAST_NOINIT_32BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_OsApplication_Core0_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core0_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_OsApplication_Core0_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core0_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core0_VAR_FAST_NOINIT_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core0_VAR_FAST_NOINIT_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core0_VAR_FAST_NOINIT_32BIT_OPEN
#  error Section OS_OsApplication_Core0_VAR_FAST_NOINIT_32BIT is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core0_VAR_FAST_NOINIT_32BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core0_VAR_FAST_NOINIT_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core0_VAR_FAST_NOINIT_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core0_VAR_FAST_NOINIT_UNSPECIFIED_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_OsApplication_Core0_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core0_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_OsApplication_Core0_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core0_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core0_VAR_FAST_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core0_VAR_FAST_NOINIT_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core0_VAR_FAST_NOINIT_UNSPECIFIED_OPEN
#  error Section OS_OsApplication_Core0_VAR_FAST_NOINIT_UNSPECIFIED is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core0_VAR_FAST_NOINIT_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core0_VAR_FAST_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core0_VAR_FAST_ZERO_INIT_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core0_VAR_FAST_ZERO_INIT_BOOLEAN_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss "OS_OsApplication_Core0_VAR_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core0_VAR_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss "OS_OsApplication_Core0_VAR_FAST_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core0_VAR_FAST_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core0_VAR_FAST_ZERO_INIT_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core0_VAR_FAST_ZERO_INIT_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core0_VAR_FAST_ZERO_INIT_BOOLEAN_OPEN
#  error Section OS_OsApplication_Core0_VAR_FAST_ZERO_INIT_BOOLEAN is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core0_VAR_FAST_ZERO_INIT_BOOLEAN_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core0_VAR_FAST_ZERO_INIT_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core0_VAR_FAST_ZERO_INIT_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core0_VAR_FAST_ZERO_INIT_8BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss "OS_OsApplication_Core0_VAR_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core0_VAR_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss "OS_OsApplication_Core0_VAR_FAST_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core0_VAR_FAST_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core0_VAR_FAST_ZERO_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core0_VAR_FAST_ZERO_INIT_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core0_VAR_FAST_ZERO_INIT_8BIT_OPEN
#  error Section OS_OsApplication_Core0_VAR_FAST_ZERO_INIT_8BIT is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core0_VAR_FAST_ZERO_INIT_8BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core0_VAR_FAST_ZERO_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core0_VAR_FAST_ZERO_INIT_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core0_VAR_FAST_ZERO_INIT_16BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss "OS_OsApplication_Core0_VAR_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core0_VAR_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss "OS_OsApplication_Core0_VAR_FAST_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core0_VAR_FAST_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core0_VAR_FAST_ZERO_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core0_VAR_FAST_ZERO_INIT_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core0_VAR_FAST_ZERO_INIT_16BIT_OPEN
#  error Section OS_OsApplication_Core0_VAR_FAST_ZERO_INIT_16BIT is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core0_VAR_FAST_ZERO_INIT_16BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core0_VAR_FAST_ZERO_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core0_VAR_FAST_ZERO_INIT_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core0_VAR_FAST_ZERO_INIT_32BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss "OS_OsApplication_Core0_VAR_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core0_VAR_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss "OS_OsApplication_Core0_VAR_FAST_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core0_VAR_FAST_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core0_VAR_FAST_ZERO_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core0_VAR_FAST_ZERO_INIT_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core0_VAR_FAST_ZERO_INIT_32BIT_OPEN
#  error Section OS_OsApplication_Core0_VAR_FAST_ZERO_INIT_32BIT is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core0_VAR_FAST_ZERO_INIT_32BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core0_VAR_FAST_ZERO_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core0_VAR_FAST_ZERO_INIT_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core0_VAR_FAST_ZERO_INIT_UNSPECIFIED_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss "OS_OsApplication_Core0_VAR_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core0_VAR_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss "OS_OsApplication_Core0_VAR_FAST_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core0_VAR_FAST_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core0_VAR_FAST_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core0_VAR_FAST_ZERO_INIT_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core0_VAR_FAST_ZERO_INIT_UNSPECIFIED_OPEN
#  error Section OS_OsApplication_Core0_VAR_FAST_ZERO_INIT_UNSPECIFIED is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core0_VAR_FAST_ZERO_INIT_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core0_VAR_FAST_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core0_VAR_NOCACHE_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core0_VAR_NOCACHE_BOOLEAN_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_OsApplication_Core0_VAR_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core0_VAR_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_OsApplication_Core0_VAR_FAST_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core0_VAR_FAST_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core0_VAR_NOCACHE_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core0_VAR_NOCACHE_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core0_VAR_NOCACHE_BOOLEAN_OPEN
#  error Section OS_OsApplication_Core0_VAR_NOCACHE_BOOLEAN is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core0_VAR_NOCACHE_BOOLEAN_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core0_VAR_NOCACHE_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core0_VAR_NOCACHE_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core0_VAR_NOCACHE_8BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_OsApplication_Core0_VAR_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core0_VAR_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_OsApplication_Core0_VAR_FAST_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core0_VAR_FAST_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core0_VAR_NOCACHE_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core0_VAR_NOCACHE_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core0_VAR_NOCACHE_8BIT_OPEN
#  error Section OS_OsApplication_Core0_VAR_NOCACHE_8BIT is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core0_VAR_NOCACHE_8BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core0_VAR_NOCACHE_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core0_VAR_NOCACHE_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core0_VAR_NOCACHE_16BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_OsApplication_Core0_VAR_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core0_VAR_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_OsApplication_Core0_VAR_FAST_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core0_VAR_FAST_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core0_VAR_NOCACHE_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core0_VAR_NOCACHE_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core0_VAR_NOCACHE_16BIT_OPEN
#  error Section OS_OsApplication_Core0_VAR_NOCACHE_16BIT is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core0_VAR_NOCACHE_16BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core0_VAR_NOCACHE_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core0_VAR_NOCACHE_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core0_VAR_NOCACHE_32BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_OsApplication_Core0_VAR_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core0_VAR_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_OsApplication_Core0_VAR_FAST_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core0_VAR_FAST_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core0_VAR_NOCACHE_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core0_VAR_NOCACHE_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core0_VAR_NOCACHE_32BIT_OPEN
#  error Section OS_OsApplication_Core0_VAR_NOCACHE_32BIT is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core0_VAR_NOCACHE_32BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core0_VAR_NOCACHE_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core0_VAR_NOCACHE_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core0_VAR_NOCACHE_UNSPECIFIED_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_OsApplication_Core0_VAR_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core0_VAR_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_OsApplication_Core0_VAR_FAST_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core0_VAR_FAST_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core0_VAR_NOCACHE_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core0_VAR_NOCACHE_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core0_VAR_NOCACHE_UNSPECIFIED_OPEN
#  error Section OS_OsApplication_Core0_VAR_NOCACHE_UNSPECIFIED is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core0_VAR_NOCACHE_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core0_VAR_NOCACHE_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core0_VAR_NOCACHE_NOINIT_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core0_VAR_NOCACHE_NOINIT_BOOLEAN_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_OsApplication_Core0_VAR_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core0_VAR_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_OsApplication_Core0_VAR_FAST_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core0_VAR_FAST_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core0_VAR_NOCACHE_NOINIT_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core0_VAR_NOCACHE_NOINIT_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core0_VAR_NOCACHE_NOINIT_BOOLEAN_OPEN
#  error Section OS_OsApplication_Core0_VAR_NOCACHE_NOINIT_BOOLEAN is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core0_VAR_NOCACHE_NOINIT_BOOLEAN_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core0_VAR_NOCACHE_NOINIT_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core0_VAR_NOCACHE_NOINIT_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core0_VAR_NOCACHE_NOINIT_8BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_OsApplication_Core0_VAR_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core0_VAR_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_OsApplication_Core0_VAR_FAST_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core0_VAR_FAST_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core0_VAR_NOCACHE_NOINIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core0_VAR_NOCACHE_NOINIT_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core0_VAR_NOCACHE_NOINIT_8BIT_OPEN
#  error Section OS_OsApplication_Core0_VAR_NOCACHE_NOINIT_8BIT is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core0_VAR_NOCACHE_NOINIT_8BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core0_VAR_NOCACHE_NOINIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core0_VAR_NOCACHE_NOINIT_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core0_VAR_NOCACHE_NOINIT_16BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_OsApplication_Core0_VAR_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core0_VAR_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_OsApplication_Core0_VAR_FAST_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core0_VAR_FAST_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core0_VAR_NOCACHE_NOINIT_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core0_VAR_NOCACHE_NOINIT_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core0_VAR_NOCACHE_NOINIT_16BIT_OPEN
#  error Section OS_OsApplication_Core0_VAR_NOCACHE_NOINIT_16BIT is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core0_VAR_NOCACHE_NOINIT_16BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core0_VAR_NOCACHE_NOINIT_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core0_VAR_NOCACHE_NOINIT_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core0_VAR_NOCACHE_NOINIT_32BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_OsApplication_Core0_VAR_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core0_VAR_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_OsApplication_Core0_VAR_FAST_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core0_VAR_FAST_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core0_VAR_NOCACHE_NOINIT_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core0_VAR_NOCACHE_NOINIT_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core0_VAR_NOCACHE_NOINIT_32BIT_OPEN
#  error Section OS_OsApplication_Core0_VAR_NOCACHE_NOINIT_32BIT is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core0_VAR_NOCACHE_NOINIT_32BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core0_VAR_NOCACHE_NOINIT_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core0_VAR_NOCACHE_NOINIT_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core0_VAR_NOCACHE_NOINIT_UNSPECIFIED_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_OsApplication_Core0_VAR_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core0_VAR_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_OsApplication_Core0_VAR_FAST_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core0_VAR_FAST_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core0_VAR_NOCACHE_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core0_VAR_NOCACHE_NOINIT_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core0_VAR_NOCACHE_NOINIT_UNSPECIFIED_OPEN
#  error Section OS_OsApplication_Core0_VAR_NOCACHE_NOINIT_UNSPECIFIED is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core0_VAR_NOCACHE_NOINIT_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core0_VAR_NOCACHE_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core0_VAR_NOCACHE_ZERO_INIT_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core0_VAR_NOCACHE_ZERO_INIT_BOOLEAN_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss "OS_OsApplication_Core0_VAR_NOCACHE_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core0_VAR_NOCACHE_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss "OS_OsApplication_Core0_VAR_FAST_NOCACHE_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core0_VAR_FAST_NOCACHE_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core0_VAR_NOCACHE_ZERO_INIT_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core0_VAR_NOCACHE_ZERO_INIT_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core0_VAR_NOCACHE_ZERO_INIT_BOOLEAN_OPEN
#  error Section OS_OsApplication_Core0_VAR_NOCACHE_ZERO_INIT_BOOLEAN is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core0_VAR_NOCACHE_ZERO_INIT_BOOLEAN_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core0_VAR_NOCACHE_ZERO_INIT_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core0_VAR_NOCACHE_ZERO_INIT_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core0_VAR_NOCACHE_ZERO_INIT_8BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss "OS_OsApplication_Core0_VAR_NOCACHE_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core0_VAR_NOCACHE_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss "OS_OsApplication_Core0_VAR_FAST_NOCACHE_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core0_VAR_FAST_NOCACHE_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core0_VAR_NOCACHE_ZERO_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core0_VAR_NOCACHE_ZERO_INIT_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core0_VAR_NOCACHE_ZERO_INIT_8BIT_OPEN
#  error Section OS_OsApplication_Core0_VAR_NOCACHE_ZERO_INIT_8BIT is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core0_VAR_NOCACHE_ZERO_INIT_8BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core0_VAR_NOCACHE_ZERO_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core0_VAR_NOCACHE_ZERO_INIT_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core0_VAR_NOCACHE_ZERO_INIT_16BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss "OS_OsApplication_Core0_VAR_NOCACHE_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core0_VAR_NOCACHE_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss "OS_OsApplication_Core0_VAR_FAST_NOCACHE_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core0_VAR_FAST_NOCACHE_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core0_VAR_NOCACHE_ZERO_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core0_VAR_NOCACHE_ZERO_INIT_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core0_VAR_NOCACHE_ZERO_INIT_16BIT_OPEN
#  error Section OS_OsApplication_Core0_VAR_NOCACHE_ZERO_INIT_16BIT is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core0_VAR_NOCACHE_ZERO_INIT_16BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core0_VAR_NOCACHE_ZERO_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core0_VAR_NOCACHE_ZERO_INIT_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core0_VAR_NOCACHE_ZERO_INIT_32BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss "OS_OsApplication_Core0_VAR_NOCACHE_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core0_VAR_NOCACHE_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss "OS_OsApplication_Core0_VAR_FAST_NOCACHE_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core0_VAR_FAST_NOCACHE_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core0_VAR_NOCACHE_ZERO_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core0_VAR_NOCACHE_ZERO_INIT_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core0_VAR_NOCACHE_ZERO_INIT_32BIT_OPEN
#  error Section OS_OsApplication_Core0_VAR_NOCACHE_ZERO_INIT_32BIT is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core0_VAR_NOCACHE_ZERO_INIT_32BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core0_VAR_NOCACHE_ZERO_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core0_VAR_NOCACHE_ZERO_INIT_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core0_VAR_NOCACHE_ZERO_INIT_UNSPECIFIED_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss "OS_OsApplication_Core0_VAR_NOCACHE_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core0_VAR_NOCACHE_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss "OS_OsApplication_Core0_VAR_FAST_NOCACHE_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core0_VAR_FAST_NOCACHE_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core0_VAR_NOCACHE_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core0_VAR_NOCACHE_ZERO_INIT_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core0_VAR_NOCACHE_ZERO_INIT_UNSPECIFIED_OPEN
#  error Section OS_OsApplication_Core0_VAR_NOCACHE_ZERO_INIT_UNSPECIFIED is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core0_VAR_NOCACHE_ZERO_INIT_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core0_VAR_NOCACHE_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core1_VAR_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core1_VAR_BOOLEAN_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_OsApplication_Core1_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core1_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_OsApplication_Core1_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core1_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core1_VAR_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core1_VAR_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core1_VAR_BOOLEAN_OPEN
#  error Section OS_OsApplication_Core1_VAR_BOOLEAN is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core1_VAR_BOOLEAN_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core1_VAR_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core1_VAR_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core1_VAR_8BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_OsApplication_Core1_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core1_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_OsApplication_Core1_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core1_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core1_VAR_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core1_VAR_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core1_VAR_8BIT_OPEN
#  error Section OS_OsApplication_Core1_VAR_8BIT is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core1_VAR_8BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core1_VAR_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core1_VAR_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core1_VAR_16BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_OsApplication_Core1_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core1_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_OsApplication_Core1_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core1_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core1_VAR_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core1_VAR_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core1_VAR_16BIT_OPEN
#  error Section OS_OsApplication_Core1_VAR_16BIT is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core1_VAR_16BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core1_VAR_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core1_VAR_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core1_VAR_32BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_OsApplication_Core1_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core1_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_OsApplication_Core1_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core1_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core1_VAR_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core1_VAR_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core1_VAR_32BIT_OPEN
#  error Section OS_OsApplication_Core1_VAR_32BIT is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core1_VAR_32BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core1_VAR_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core1_VAR_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core1_VAR_UNSPECIFIED_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_OsApplication_Core1_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core1_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_OsApplication_Core1_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core1_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core1_VAR_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core1_VAR_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core1_VAR_UNSPECIFIED_OPEN
#  error Section OS_OsApplication_Core1_VAR_UNSPECIFIED is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core1_VAR_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core1_VAR_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core1_VAR_NOINIT_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core1_VAR_NOINIT_BOOLEAN_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_OsApplication_Core1_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core1_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_OsApplication_Core1_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core1_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core1_VAR_NOINIT_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core1_VAR_NOINIT_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core1_VAR_NOINIT_BOOLEAN_OPEN
#  error Section OS_OsApplication_Core1_VAR_NOINIT_BOOLEAN is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core1_VAR_NOINIT_BOOLEAN_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core1_VAR_NOINIT_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core1_VAR_NOINIT_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core1_VAR_NOINIT_8BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_OsApplication_Core1_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core1_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_OsApplication_Core1_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core1_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core1_VAR_NOINIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core1_VAR_NOINIT_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core1_VAR_NOINIT_8BIT_OPEN
#  error Section OS_OsApplication_Core1_VAR_NOINIT_8BIT is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core1_VAR_NOINIT_8BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core1_VAR_NOINIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core1_VAR_NOINIT_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core1_VAR_NOINIT_16BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_OsApplication_Core1_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core1_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_OsApplication_Core1_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core1_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core1_VAR_NOINIT_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core1_VAR_NOINIT_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core1_VAR_NOINIT_16BIT_OPEN
#  error Section OS_OsApplication_Core1_VAR_NOINIT_16BIT is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core1_VAR_NOINIT_16BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core1_VAR_NOINIT_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core1_VAR_NOINIT_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core1_VAR_NOINIT_32BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_OsApplication_Core1_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core1_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_OsApplication_Core1_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core1_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core1_VAR_NOINIT_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core1_VAR_NOINIT_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core1_VAR_NOINIT_32BIT_OPEN
#  error Section OS_OsApplication_Core1_VAR_NOINIT_32BIT is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core1_VAR_NOINIT_32BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core1_VAR_NOINIT_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core1_VAR_NOINIT_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core1_VAR_NOINIT_UNSPECIFIED_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_OsApplication_Core1_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core1_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_OsApplication_Core1_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core1_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core1_VAR_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core1_VAR_NOINIT_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core1_VAR_NOINIT_UNSPECIFIED_OPEN
#  error Section OS_OsApplication_Core1_VAR_NOINIT_UNSPECIFIED is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core1_VAR_NOINIT_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core1_VAR_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core1_VAR_ZERO_INIT_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core1_VAR_ZERO_INIT_BOOLEAN_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss "OS_OsApplication_Core1_VAR_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core1_VAR_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss "OS_OsApplication_Core1_VAR_FAST_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core1_VAR_FAST_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core1_VAR_ZERO_INIT_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core1_VAR_ZERO_INIT_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core1_VAR_ZERO_INIT_BOOLEAN_OPEN
#  error Section OS_OsApplication_Core1_VAR_ZERO_INIT_BOOLEAN is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core1_VAR_ZERO_INIT_BOOLEAN_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core1_VAR_ZERO_INIT_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core1_VAR_ZERO_INIT_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core1_VAR_ZERO_INIT_8BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss "OS_OsApplication_Core1_VAR_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core1_VAR_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss "OS_OsApplication_Core1_VAR_FAST_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core1_VAR_FAST_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core1_VAR_ZERO_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core1_VAR_ZERO_INIT_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core1_VAR_ZERO_INIT_8BIT_OPEN
#  error Section OS_OsApplication_Core1_VAR_ZERO_INIT_8BIT is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core1_VAR_ZERO_INIT_8BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core1_VAR_ZERO_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core1_VAR_ZERO_INIT_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core1_VAR_ZERO_INIT_16BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss "OS_OsApplication_Core1_VAR_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core1_VAR_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss "OS_OsApplication_Core1_VAR_FAST_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core1_VAR_FAST_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core1_VAR_ZERO_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core1_VAR_ZERO_INIT_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core1_VAR_ZERO_INIT_16BIT_OPEN
#  error Section OS_OsApplication_Core1_VAR_ZERO_INIT_16BIT is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core1_VAR_ZERO_INIT_16BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core1_VAR_ZERO_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core1_VAR_ZERO_INIT_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core1_VAR_ZERO_INIT_32BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss "OS_OsApplication_Core1_VAR_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core1_VAR_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss "OS_OsApplication_Core1_VAR_FAST_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core1_VAR_FAST_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core1_VAR_ZERO_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core1_VAR_ZERO_INIT_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core1_VAR_ZERO_INIT_32BIT_OPEN
#  error Section OS_OsApplication_Core1_VAR_ZERO_INIT_32BIT is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core1_VAR_ZERO_INIT_32BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core1_VAR_ZERO_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core1_VAR_ZERO_INIT_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core1_VAR_ZERO_INIT_UNSPECIFIED_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss "OS_OsApplication_Core1_VAR_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core1_VAR_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss "OS_OsApplication_Core1_VAR_FAST_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core1_VAR_FAST_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core1_VAR_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core1_VAR_ZERO_INIT_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core1_VAR_ZERO_INIT_UNSPECIFIED_OPEN
#  error Section OS_OsApplication_Core1_VAR_ZERO_INIT_UNSPECIFIED is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core1_VAR_ZERO_INIT_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core1_VAR_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core1_VAR_FAST_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core1_VAR_FAST_BOOLEAN_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_OsApplication_Core1_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core1_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_OsApplication_Core1_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core1_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core1_VAR_FAST_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core1_VAR_FAST_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core1_VAR_FAST_BOOLEAN_OPEN
#  error Section OS_OsApplication_Core1_VAR_FAST_BOOLEAN is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core1_VAR_FAST_BOOLEAN_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core1_VAR_FAST_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core1_VAR_FAST_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core1_VAR_FAST_8BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_OsApplication_Core1_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core1_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_OsApplication_Core1_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core1_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core1_VAR_FAST_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core1_VAR_FAST_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core1_VAR_FAST_8BIT_OPEN
#  error Section OS_OsApplication_Core1_VAR_FAST_8BIT is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core1_VAR_FAST_8BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core1_VAR_FAST_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core1_VAR_FAST_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core1_VAR_FAST_16BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_OsApplication_Core1_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core1_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_OsApplication_Core1_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core1_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core1_VAR_FAST_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core1_VAR_FAST_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core1_VAR_FAST_16BIT_OPEN
#  error Section OS_OsApplication_Core1_VAR_FAST_16BIT is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core1_VAR_FAST_16BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core1_VAR_FAST_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core1_VAR_FAST_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core1_VAR_FAST_32BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_OsApplication_Core1_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core1_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_OsApplication_Core1_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core1_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core1_VAR_FAST_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core1_VAR_FAST_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core1_VAR_FAST_32BIT_OPEN
#  error Section OS_OsApplication_Core1_VAR_FAST_32BIT is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core1_VAR_FAST_32BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core1_VAR_FAST_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core1_VAR_FAST_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core1_VAR_FAST_UNSPECIFIED_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_OsApplication_Core1_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core1_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_OsApplication_Core1_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core1_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core1_VAR_FAST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core1_VAR_FAST_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core1_VAR_FAST_UNSPECIFIED_OPEN
#  error Section OS_OsApplication_Core1_VAR_FAST_UNSPECIFIED is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core1_VAR_FAST_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core1_VAR_FAST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core1_VAR_FAST_NOINIT_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core1_VAR_FAST_NOINIT_BOOLEAN_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_OsApplication_Core1_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core1_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_OsApplication_Core1_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core1_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core1_VAR_FAST_NOINIT_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core1_VAR_FAST_NOINIT_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core1_VAR_FAST_NOINIT_BOOLEAN_OPEN
#  error Section OS_OsApplication_Core1_VAR_FAST_NOINIT_BOOLEAN is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core1_VAR_FAST_NOINIT_BOOLEAN_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core1_VAR_FAST_NOINIT_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core1_VAR_FAST_NOINIT_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core1_VAR_FAST_NOINIT_8BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_OsApplication_Core1_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core1_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_OsApplication_Core1_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core1_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core1_VAR_FAST_NOINIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core1_VAR_FAST_NOINIT_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core1_VAR_FAST_NOINIT_8BIT_OPEN
#  error Section OS_OsApplication_Core1_VAR_FAST_NOINIT_8BIT is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core1_VAR_FAST_NOINIT_8BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core1_VAR_FAST_NOINIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core1_VAR_FAST_NOINIT_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core1_VAR_FAST_NOINIT_16BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_OsApplication_Core1_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core1_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_OsApplication_Core1_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core1_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core1_VAR_FAST_NOINIT_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core1_VAR_FAST_NOINIT_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core1_VAR_FAST_NOINIT_16BIT_OPEN
#  error Section OS_OsApplication_Core1_VAR_FAST_NOINIT_16BIT is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core1_VAR_FAST_NOINIT_16BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core1_VAR_FAST_NOINIT_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core1_VAR_FAST_NOINIT_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core1_VAR_FAST_NOINIT_32BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_OsApplication_Core1_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core1_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_OsApplication_Core1_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core1_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core1_VAR_FAST_NOINIT_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core1_VAR_FAST_NOINIT_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core1_VAR_FAST_NOINIT_32BIT_OPEN
#  error Section OS_OsApplication_Core1_VAR_FAST_NOINIT_32BIT is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core1_VAR_FAST_NOINIT_32BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core1_VAR_FAST_NOINIT_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core1_VAR_FAST_NOINIT_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core1_VAR_FAST_NOINIT_UNSPECIFIED_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_OsApplication_Core1_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core1_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_OsApplication_Core1_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core1_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core1_VAR_FAST_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core1_VAR_FAST_NOINIT_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core1_VAR_FAST_NOINIT_UNSPECIFIED_OPEN
#  error Section OS_OsApplication_Core1_VAR_FAST_NOINIT_UNSPECIFIED is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core1_VAR_FAST_NOINIT_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core1_VAR_FAST_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core1_VAR_FAST_ZERO_INIT_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core1_VAR_FAST_ZERO_INIT_BOOLEAN_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss "OS_OsApplication_Core1_VAR_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core1_VAR_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss "OS_OsApplication_Core1_VAR_FAST_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core1_VAR_FAST_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core1_VAR_FAST_ZERO_INIT_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core1_VAR_FAST_ZERO_INIT_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core1_VAR_FAST_ZERO_INIT_BOOLEAN_OPEN
#  error Section OS_OsApplication_Core1_VAR_FAST_ZERO_INIT_BOOLEAN is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core1_VAR_FAST_ZERO_INIT_BOOLEAN_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core1_VAR_FAST_ZERO_INIT_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core1_VAR_FAST_ZERO_INIT_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core1_VAR_FAST_ZERO_INIT_8BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss "OS_OsApplication_Core1_VAR_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core1_VAR_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss "OS_OsApplication_Core1_VAR_FAST_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core1_VAR_FAST_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core1_VAR_FAST_ZERO_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core1_VAR_FAST_ZERO_INIT_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core1_VAR_FAST_ZERO_INIT_8BIT_OPEN
#  error Section OS_OsApplication_Core1_VAR_FAST_ZERO_INIT_8BIT is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core1_VAR_FAST_ZERO_INIT_8BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core1_VAR_FAST_ZERO_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core1_VAR_FAST_ZERO_INIT_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core1_VAR_FAST_ZERO_INIT_16BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss "OS_OsApplication_Core1_VAR_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core1_VAR_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss "OS_OsApplication_Core1_VAR_FAST_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core1_VAR_FAST_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core1_VAR_FAST_ZERO_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core1_VAR_FAST_ZERO_INIT_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core1_VAR_FAST_ZERO_INIT_16BIT_OPEN
#  error Section OS_OsApplication_Core1_VAR_FAST_ZERO_INIT_16BIT is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core1_VAR_FAST_ZERO_INIT_16BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core1_VAR_FAST_ZERO_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core1_VAR_FAST_ZERO_INIT_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core1_VAR_FAST_ZERO_INIT_32BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss "OS_OsApplication_Core1_VAR_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core1_VAR_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss "OS_OsApplication_Core1_VAR_FAST_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core1_VAR_FAST_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core1_VAR_FAST_ZERO_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core1_VAR_FAST_ZERO_INIT_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core1_VAR_FAST_ZERO_INIT_32BIT_OPEN
#  error Section OS_OsApplication_Core1_VAR_FAST_ZERO_INIT_32BIT is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core1_VAR_FAST_ZERO_INIT_32BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core1_VAR_FAST_ZERO_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core1_VAR_FAST_ZERO_INIT_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core1_VAR_FAST_ZERO_INIT_UNSPECIFIED_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss "OS_OsApplication_Core1_VAR_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core1_VAR_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss "OS_OsApplication_Core1_VAR_FAST_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core1_VAR_FAST_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core1_VAR_FAST_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core1_VAR_FAST_ZERO_INIT_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core1_VAR_FAST_ZERO_INIT_UNSPECIFIED_OPEN
#  error Section OS_OsApplication_Core1_VAR_FAST_ZERO_INIT_UNSPECIFIED is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core1_VAR_FAST_ZERO_INIT_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core1_VAR_FAST_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core1_VAR_NOCACHE_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core1_VAR_NOCACHE_BOOLEAN_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_OsApplication_Core1_VAR_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core1_VAR_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_OsApplication_Core1_VAR_FAST_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core1_VAR_FAST_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core1_VAR_NOCACHE_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core1_VAR_NOCACHE_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core1_VAR_NOCACHE_BOOLEAN_OPEN
#  error Section OS_OsApplication_Core1_VAR_NOCACHE_BOOLEAN is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core1_VAR_NOCACHE_BOOLEAN_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core1_VAR_NOCACHE_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core1_VAR_NOCACHE_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core1_VAR_NOCACHE_8BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_OsApplication_Core1_VAR_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core1_VAR_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_OsApplication_Core1_VAR_FAST_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core1_VAR_FAST_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core1_VAR_NOCACHE_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core1_VAR_NOCACHE_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core1_VAR_NOCACHE_8BIT_OPEN
#  error Section OS_OsApplication_Core1_VAR_NOCACHE_8BIT is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core1_VAR_NOCACHE_8BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core1_VAR_NOCACHE_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core1_VAR_NOCACHE_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core1_VAR_NOCACHE_16BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_OsApplication_Core1_VAR_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core1_VAR_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_OsApplication_Core1_VAR_FAST_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core1_VAR_FAST_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core1_VAR_NOCACHE_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core1_VAR_NOCACHE_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core1_VAR_NOCACHE_16BIT_OPEN
#  error Section OS_OsApplication_Core1_VAR_NOCACHE_16BIT is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core1_VAR_NOCACHE_16BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core1_VAR_NOCACHE_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core1_VAR_NOCACHE_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core1_VAR_NOCACHE_32BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_OsApplication_Core1_VAR_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core1_VAR_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_OsApplication_Core1_VAR_FAST_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core1_VAR_FAST_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core1_VAR_NOCACHE_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core1_VAR_NOCACHE_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core1_VAR_NOCACHE_32BIT_OPEN
#  error Section OS_OsApplication_Core1_VAR_NOCACHE_32BIT is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core1_VAR_NOCACHE_32BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core1_VAR_NOCACHE_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core1_VAR_NOCACHE_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core1_VAR_NOCACHE_UNSPECIFIED_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_OsApplication_Core1_VAR_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core1_VAR_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_OsApplication_Core1_VAR_FAST_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core1_VAR_FAST_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core1_VAR_NOCACHE_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core1_VAR_NOCACHE_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core1_VAR_NOCACHE_UNSPECIFIED_OPEN
#  error Section OS_OsApplication_Core1_VAR_NOCACHE_UNSPECIFIED is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core1_VAR_NOCACHE_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core1_VAR_NOCACHE_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core1_VAR_NOCACHE_NOINIT_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core1_VAR_NOCACHE_NOINIT_BOOLEAN_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_OsApplication_Core1_VAR_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core1_VAR_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_OsApplication_Core1_VAR_FAST_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core1_VAR_FAST_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core1_VAR_NOCACHE_NOINIT_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core1_VAR_NOCACHE_NOINIT_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core1_VAR_NOCACHE_NOINIT_BOOLEAN_OPEN
#  error Section OS_OsApplication_Core1_VAR_NOCACHE_NOINIT_BOOLEAN is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core1_VAR_NOCACHE_NOINIT_BOOLEAN_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core1_VAR_NOCACHE_NOINIT_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core1_VAR_NOCACHE_NOINIT_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core1_VAR_NOCACHE_NOINIT_8BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_OsApplication_Core1_VAR_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core1_VAR_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_OsApplication_Core1_VAR_FAST_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core1_VAR_FAST_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core1_VAR_NOCACHE_NOINIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core1_VAR_NOCACHE_NOINIT_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core1_VAR_NOCACHE_NOINIT_8BIT_OPEN
#  error Section OS_OsApplication_Core1_VAR_NOCACHE_NOINIT_8BIT is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core1_VAR_NOCACHE_NOINIT_8BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core1_VAR_NOCACHE_NOINIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core1_VAR_NOCACHE_NOINIT_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core1_VAR_NOCACHE_NOINIT_16BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_OsApplication_Core1_VAR_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core1_VAR_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_OsApplication_Core1_VAR_FAST_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core1_VAR_FAST_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core1_VAR_NOCACHE_NOINIT_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core1_VAR_NOCACHE_NOINIT_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core1_VAR_NOCACHE_NOINIT_16BIT_OPEN
#  error Section OS_OsApplication_Core1_VAR_NOCACHE_NOINIT_16BIT is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core1_VAR_NOCACHE_NOINIT_16BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core1_VAR_NOCACHE_NOINIT_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core1_VAR_NOCACHE_NOINIT_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core1_VAR_NOCACHE_NOINIT_32BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_OsApplication_Core1_VAR_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core1_VAR_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_OsApplication_Core1_VAR_FAST_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core1_VAR_FAST_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core1_VAR_NOCACHE_NOINIT_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core1_VAR_NOCACHE_NOINIT_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core1_VAR_NOCACHE_NOINIT_32BIT_OPEN
#  error Section OS_OsApplication_Core1_VAR_NOCACHE_NOINIT_32BIT is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core1_VAR_NOCACHE_NOINIT_32BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core1_VAR_NOCACHE_NOINIT_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core1_VAR_NOCACHE_NOINIT_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core1_VAR_NOCACHE_NOINIT_UNSPECIFIED_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_OsApplication_Core1_VAR_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core1_VAR_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_OsApplication_Core1_VAR_FAST_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core1_VAR_FAST_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core1_VAR_NOCACHE_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core1_VAR_NOCACHE_NOINIT_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core1_VAR_NOCACHE_NOINIT_UNSPECIFIED_OPEN
#  error Section OS_OsApplication_Core1_VAR_NOCACHE_NOINIT_UNSPECIFIED is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core1_VAR_NOCACHE_NOINIT_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core1_VAR_NOCACHE_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core1_VAR_NOCACHE_ZERO_INIT_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core1_VAR_NOCACHE_ZERO_INIT_BOOLEAN_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss "OS_OsApplication_Core1_VAR_NOCACHE_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core1_VAR_NOCACHE_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss "OS_OsApplication_Core1_VAR_FAST_NOCACHE_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core1_VAR_FAST_NOCACHE_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core1_VAR_NOCACHE_ZERO_INIT_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core1_VAR_NOCACHE_ZERO_INIT_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core1_VAR_NOCACHE_ZERO_INIT_BOOLEAN_OPEN
#  error Section OS_OsApplication_Core1_VAR_NOCACHE_ZERO_INIT_BOOLEAN is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core1_VAR_NOCACHE_ZERO_INIT_BOOLEAN_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core1_VAR_NOCACHE_ZERO_INIT_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core1_VAR_NOCACHE_ZERO_INIT_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core1_VAR_NOCACHE_ZERO_INIT_8BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss "OS_OsApplication_Core1_VAR_NOCACHE_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core1_VAR_NOCACHE_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss "OS_OsApplication_Core1_VAR_FAST_NOCACHE_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core1_VAR_FAST_NOCACHE_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core1_VAR_NOCACHE_ZERO_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core1_VAR_NOCACHE_ZERO_INIT_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core1_VAR_NOCACHE_ZERO_INIT_8BIT_OPEN
#  error Section OS_OsApplication_Core1_VAR_NOCACHE_ZERO_INIT_8BIT is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core1_VAR_NOCACHE_ZERO_INIT_8BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core1_VAR_NOCACHE_ZERO_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core1_VAR_NOCACHE_ZERO_INIT_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core1_VAR_NOCACHE_ZERO_INIT_16BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss "OS_OsApplication_Core1_VAR_NOCACHE_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core1_VAR_NOCACHE_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss "OS_OsApplication_Core1_VAR_FAST_NOCACHE_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core1_VAR_FAST_NOCACHE_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core1_VAR_NOCACHE_ZERO_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core1_VAR_NOCACHE_ZERO_INIT_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core1_VAR_NOCACHE_ZERO_INIT_16BIT_OPEN
#  error Section OS_OsApplication_Core1_VAR_NOCACHE_ZERO_INIT_16BIT is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core1_VAR_NOCACHE_ZERO_INIT_16BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core1_VAR_NOCACHE_ZERO_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core1_VAR_NOCACHE_ZERO_INIT_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core1_VAR_NOCACHE_ZERO_INIT_32BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss "OS_OsApplication_Core1_VAR_NOCACHE_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core1_VAR_NOCACHE_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss "OS_OsApplication_Core1_VAR_FAST_NOCACHE_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core1_VAR_FAST_NOCACHE_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core1_VAR_NOCACHE_ZERO_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core1_VAR_NOCACHE_ZERO_INIT_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core1_VAR_NOCACHE_ZERO_INIT_32BIT_OPEN
#  error Section OS_OsApplication_Core1_VAR_NOCACHE_ZERO_INIT_32BIT is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core1_VAR_NOCACHE_ZERO_INIT_32BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core1_VAR_NOCACHE_ZERO_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core1_VAR_NOCACHE_ZERO_INIT_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core1_VAR_NOCACHE_ZERO_INIT_UNSPECIFIED_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss "OS_OsApplication_Core1_VAR_NOCACHE_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core1_VAR_NOCACHE_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss "OS_OsApplication_Core1_VAR_FAST_NOCACHE_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core1_VAR_FAST_NOCACHE_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core1_VAR_NOCACHE_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core1_VAR_NOCACHE_ZERO_INIT_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core1_VAR_NOCACHE_ZERO_INIT_UNSPECIFIED_OPEN
#  error Section OS_OsApplication_Core1_VAR_NOCACHE_ZERO_INIT_UNSPECIFIED is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core1_VAR_NOCACHE_ZERO_INIT_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core1_VAR_NOCACHE_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core2_VAR_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core2_VAR_BOOLEAN_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_OsApplication_Core2_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core2_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_OsApplication_Core2_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core2_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core2_VAR_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core2_VAR_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core2_VAR_BOOLEAN_OPEN
#  error Section OS_OsApplication_Core2_VAR_BOOLEAN is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core2_VAR_BOOLEAN_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core2_VAR_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core2_VAR_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core2_VAR_8BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_OsApplication_Core2_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core2_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_OsApplication_Core2_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core2_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core2_VAR_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core2_VAR_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core2_VAR_8BIT_OPEN
#  error Section OS_OsApplication_Core2_VAR_8BIT is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core2_VAR_8BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core2_VAR_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core2_VAR_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core2_VAR_16BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_OsApplication_Core2_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core2_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_OsApplication_Core2_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core2_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core2_VAR_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core2_VAR_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core2_VAR_16BIT_OPEN
#  error Section OS_OsApplication_Core2_VAR_16BIT is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core2_VAR_16BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core2_VAR_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core2_VAR_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core2_VAR_32BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_OsApplication_Core2_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core2_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_OsApplication_Core2_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core2_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core2_VAR_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core2_VAR_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core2_VAR_32BIT_OPEN
#  error Section OS_OsApplication_Core2_VAR_32BIT is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core2_VAR_32BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core2_VAR_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core2_VAR_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core2_VAR_UNSPECIFIED_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_OsApplication_Core2_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core2_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_OsApplication_Core2_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core2_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core2_VAR_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core2_VAR_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core2_VAR_UNSPECIFIED_OPEN
#  error Section OS_OsApplication_Core2_VAR_UNSPECIFIED is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core2_VAR_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core2_VAR_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core2_VAR_NOINIT_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core2_VAR_NOINIT_BOOLEAN_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_OsApplication_Core2_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core2_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_OsApplication_Core2_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core2_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core2_VAR_NOINIT_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core2_VAR_NOINIT_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core2_VAR_NOINIT_BOOLEAN_OPEN
#  error Section OS_OsApplication_Core2_VAR_NOINIT_BOOLEAN is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core2_VAR_NOINIT_BOOLEAN_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core2_VAR_NOINIT_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core2_VAR_NOINIT_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core2_VAR_NOINIT_8BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_OsApplication_Core2_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core2_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_OsApplication_Core2_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core2_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core2_VAR_NOINIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core2_VAR_NOINIT_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core2_VAR_NOINIT_8BIT_OPEN
#  error Section OS_OsApplication_Core2_VAR_NOINIT_8BIT is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core2_VAR_NOINIT_8BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core2_VAR_NOINIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core2_VAR_NOINIT_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core2_VAR_NOINIT_16BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_OsApplication_Core2_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core2_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_OsApplication_Core2_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core2_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core2_VAR_NOINIT_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core2_VAR_NOINIT_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core2_VAR_NOINIT_16BIT_OPEN
#  error Section OS_OsApplication_Core2_VAR_NOINIT_16BIT is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core2_VAR_NOINIT_16BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core2_VAR_NOINIT_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core2_VAR_NOINIT_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core2_VAR_NOINIT_32BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_OsApplication_Core2_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core2_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_OsApplication_Core2_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core2_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core2_VAR_NOINIT_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core2_VAR_NOINIT_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core2_VAR_NOINIT_32BIT_OPEN
#  error Section OS_OsApplication_Core2_VAR_NOINIT_32BIT is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core2_VAR_NOINIT_32BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core2_VAR_NOINIT_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core2_VAR_NOINIT_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core2_VAR_NOINIT_UNSPECIFIED_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_OsApplication_Core2_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core2_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_OsApplication_Core2_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core2_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core2_VAR_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core2_VAR_NOINIT_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core2_VAR_NOINIT_UNSPECIFIED_OPEN
#  error Section OS_OsApplication_Core2_VAR_NOINIT_UNSPECIFIED is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core2_VAR_NOINIT_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core2_VAR_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core2_VAR_ZERO_INIT_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core2_VAR_ZERO_INIT_BOOLEAN_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss "OS_OsApplication_Core2_VAR_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core2_VAR_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss "OS_OsApplication_Core2_VAR_FAST_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core2_VAR_FAST_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core2_VAR_ZERO_INIT_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core2_VAR_ZERO_INIT_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core2_VAR_ZERO_INIT_BOOLEAN_OPEN
#  error Section OS_OsApplication_Core2_VAR_ZERO_INIT_BOOLEAN is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core2_VAR_ZERO_INIT_BOOLEAN_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core2_VAR_ZERO_INIT_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core2_VAR_ZERO_INIT_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core2_VAR_ZERO_INIT_8BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss "OS_OsApplication_Core2_VAR_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core2_VAR_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss "OS_OsApplication_Core2_VAR_FAST_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core2_VAR_FAST_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core2_VAR_ZERO_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core2_VAR_ZERO_INIT_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core2_VAR_ZERO_INIT_8BIT_OPEN
#  error Section OS_OsApplication_Core2_VAR_ZERO_INIT_8BIT is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core2_VAR_ZERO_INIT_8BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core2_VAR_ZERO_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core2_VAR_ZERO_INIT_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core2_VAR_ZERO_INIT_16BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss "OS_OsApplication_Core2_VAR_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core2_VAR_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss "OS_OsApplication_Core2_VAR_FAST_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core2_VAR_FAST_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core2_VAR_ZERO_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core2_VAR_ZERO_INIT_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core2_VAR_ZERO_INIT_16BIT_OPEN
#  error Section OS_OsApplication_Core2_VAR_ZERO_INIT_16BIT is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core2_VAR_ZERO_INIT_16BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core2_VAR_ZERO_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core2_VAR_ZERO_INIT_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core2_VAR_ZERO_INIT_32BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss "OS_OsApplication_Core2_VAR_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core2_VAR_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss "OS_OsApplication_Core2_VAR_FAST_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core2_VAR_FAST_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core2_VAR_ZERO_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core2_VAR_ZERO_INIT_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core2_VAR_ZERO_INIT_32BIT_OPEN
#  error Section OS_OsApplication_Core2_VAR_ZERO_INIT_32BIT is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core2_VAR_ZERO_INIT_32BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core2_VAR_ZERO_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core2_VAR_ZERO_INIT_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core2_VAR_ZERO_INIT_UNSPECIFIED_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss "OS_OsApplication_Core2_VAR_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core2_VAR_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss "OS_OsApplication_Core2_VAR_FAST_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core2_VAR_FAST_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core2_VAR_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core2_VAR_ZERO_INIT_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core2_VAR_ZERO_INIT_UNSPECIFIED_OPEN
#  error Section OS_OsApplication_Core2_VAR_ZERO_INIT_UNSPECIFIED is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core2_VAR_ZERO_INIT_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core2_VAR_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core2_VAR_FAST_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core2_VAR_FAST_BOOLEAN_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_OsApplication_Core2_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core2_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_OsApplication_Core2_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core2_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core2_VAR_FAST_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core2_VAR_FAST_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core2_VAR_FAST_BOOLEAN_OPEN
#  error Section OS_OsApplication_Core2_VAR_FAST_BOOLEAN is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core2_VAR_FAST_BOOLEAN_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core2_VAR_FAST_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core2_VAR_FAST_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core2_VAR_FAST_8BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_OsApplication_Core2_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core2_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_OsApplication_Core2_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core2_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core2_VAR_FAST_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core2_VAR_FAST_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core2_VAR_FAST_8BIT_OPEN
#  error Section OS_OsApplication_Core2_VAR_FAST_8BIT is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core2_VAR_FAST_8BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core2_VAR_FAST_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core2_VAR_FAST_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core2_VAR_FAST_16BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_OsApplication_Core2_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core2_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_OsApplication_Core2_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core2_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core2_VAR_FAST_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core2_VAR_FAST_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core2_VAR_FAST_16BIT_OPEN
#  error Section OS_OsApplication_Core2_VAR_FAST_16BIT is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core2_VAR_FAST_16BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core2_VAR_FAST_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core2_VAR_FAST_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core2_VAR_FAST_32BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_OsApplication_Core2_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core2_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_OsApplication_Core2_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core2_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core2_VAR_FAST_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core2_VAR_FAST_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core2_VAR_FAST_32BIT_OPEN
#  error Section OS_OsApplication_Core2_VAR_FAST_32BIT is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core2_VAR_FAST_32BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core2_VAR_FAST_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core2_VAR_FAST_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core2_VAR_FAST_UNSPECIFIED_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_OsApplication_Core2_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core2_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_OsApplication_Core2_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core2_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core2_VAR_FAST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core2_VAR_FAST_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core2_VAR_FAST_UNSPECIFIED_OPEN
#  error Section OS_OsApplication_Core2_VAR_FAST_UNSPECIFIED is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core2_VAR_FAST_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core2_VAR_FAST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core2_VAR_FAST_NOINIT_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core2_VAR_FAST_NOINIT_BOOLEAN_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_OsApplication_Core2_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core2_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_OsApplication_Core2_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core2_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core2_VAR_FAST_NOINIT_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core2_VAR_FAST_NOINIT_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core2_VAR_FAST_NOINIT_BOOLEAN_OPEN
#  error Section OS_OsApplication_Core2_VAR_FAST_NOINIT_BOOLEAN is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core2_VAR_FAST_NOINIT_BOOLEAN_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core2_VAR_FAST_NOINIT_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core2_VAR_FAST_NOINIT_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core2_VAR_FAST_NOINIT_8BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_OsApplication_Core2_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core2_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_OsApplication_Core2_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core2_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core2_VAR_FAST_NOINIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core2_VAR_FAST_NOINIT_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core2_VAR_FAST_NOINIT_8BIT_OPEN
#  error Section OS_OsApplication_Core2_VAR_FAST_NOINIT_8BIT is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core2_VAR_FAST_NOINIT_8BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core2_VAR_FAST_NOINIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core2_VAR_FAST_NOINIT_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core2_VAR_FAST_NOINIT_16BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_OsApplication_Core2_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core2_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_OsApplication_Core2_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core2_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core2_VAR_FAST_NOINIT_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core2_VAR_FAST_NOINIT_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core2_VAR_FAST_NOINIT_16BIT_OPEN
#  error Section OS_OsApplication_Core2_VAR_FAST_NOINIT_16BIT is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core2_VAR_FAST_NOINIT_16BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core2_VAR_FAST_NOINIT_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core2_VAR_FAST_NOINIT_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core2_VAR_FAST_NOINIT_32BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_OsApplication_Core2_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core2_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_OsApplication_Core2_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core2_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core2_VAR_FAST_NOINIT_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core2_VAR_FAST_NOINIT_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core2_VAR_FAST_NOINIT_32BIT_OPEN
#  error Section OS_OsApplication_Core2_VAR_FAST_NOINIT_32BIT is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core2_VAR_FAST_NOINIT_32BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core2_VAR_FAST_NOINIT_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core2_VAR_FAST_NOINIT_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core2_VAR_FAST_NOINIT_UNSPECIFIED_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_OsApplication_Core2_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core2_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_OsApplication_Core2_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core2_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core2_VAR_FAST_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core2_VAR_FAST_NOINIT_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core2_VAR_FAST_NOINIT_UNSPECIFIED_OPEN
#  error Section OS_OsApplication_Core2_VAR_FAST_NOINIT_UNSPECIFIED is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core2_VAR_FAST_NOINIT_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core2_VAR_FAST_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core2_VAR_FAST_ZERO_INIT_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core2_VAR_FAST_ZERO_INIT_BOOLEAN_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss "OS_OsApplication_Core2_VAR_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core2_VAR_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss "OS_OsApplication_Core2_VAR_FAST_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core2_VAR_FAST_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core2_VAR_FAST_ZERO_INIT_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core2_VAR_FAST_ZERO_INIT_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core2_VAR_FAST_ZERO_INIT_BOOLEAN_OPEN
#  error Section OS_OsApplication_Core2_VAR_FAST_ZERO_INIT_BOOLEAN is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core2_VAR_FAST_ZERO_INIT_BOOLEAN_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core2_VAR_FAST_ZERO_INIT_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core2_VAR_FAST_ZERO_INIT_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core2_VAR_FAST_ZERO_INIT_8BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss "OS_OsApplication_Core2_VAR_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core2_VAR_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss "OS_OsApplication_Core2_VAR_FAST_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core2_VAR_FAST_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core2_VAR_FAST_ZERO_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core2_VAR_FAST_ZERO_INIT_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core2_VAR_FAST_ZERO_INIT_8BIT_OPEN
#  error Section OS_OsApplication_Core2_VAR_FAST_ZERO_INIT_8BIT is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core2_VAR_FAST_ZERO_INIT_8BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core2_VAR_FAST_ZERO_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core2_VAR_FAST_ZERO_INIT_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core2_VAR_FAST_ZERO_INIT_16BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss "OS_OsApplication_Core2_VAR_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core2_VAR_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss "OS_OsApplication_Core2_VAR_FAST_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core2_VAR_FAST_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core2_VAR_FAST_ZERO_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core2_VAR_FAST_ZERO_INIT_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core2_VAR_FAST_ZERO_INIT_16BIT_OPEN
#  error Section OS_OsApplication_Core2_VAR_FAST_ZERO_INIT_16BIT is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core2_VAR_FAST_ZERO_INIT_16BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core2_VAR_FAST_ZERO_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core2_VAR_FAST_ZERO_INIT_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core2_VAR_FAST_ZERO_INIT_32BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss "OS_OsApplication_Core2_VAR_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core2_VAR_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss "OS_OsApplication_Core2_VAR_FAST_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core2_VAR_FAST_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core2_VAR_FAST_ZERO_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core2_VAR_FAST_ZERO_INIT_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core2_VAR_FAST_ZERO_INIT_32BIT_OPEN
#  error Section OS_OsApplication_Core2_VAR_FAST_ZERO_INIT_32BIT is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core2_VAR_FAST_ZERO_INIT_32BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core2_VAR_FAST_ZERO_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core2_VAR_FAST_ZERO_INIT_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core2_VAR_FAST_ZERO_INIT_UNSPECIFIED_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss "OS_OsApplication_Core2_VAR_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core2_VAR_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss "OS_OsApplication_Core2_VAR_FAST_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core2_VAR_FAST_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core2_VAR_FAST_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core2_VAR_FAST_ZERO_INIT_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core2_VAR_FAST_ZERO_INIT_UNSPECIFIED_OPEN
#  error Section OS_OsApplication_Core2_VAR_FAST_ZERO_INIT_UNSPECIFIED is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core2_VAR_FAST_ZERO_INIT_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core2_VAR_FAST_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core2_VAR_NOCACHE_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core2_VAR_NOCACHE_BOOLEAN_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_OsApplication_Core2_VAR_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core2_VAR_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_OsApplication_Core2_VAR_FAST_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core2_VAR_FAST_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core2_VAR_NOCACHE_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core2_VAR_NOCACHE_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core2_VAR_NOCACHE_BOOLEAN_OPEN
#  error Section OS_OsApplication_Core2_VAR_NOCACHE_BOOLEAN is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core2_VAR_NOCACHE_BOOLEAN_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core2_VAR_NOCACHE_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core2_VAR_NOCACHE_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core2_VAR_NOCACHE_8BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_OsApplication_Core2_VAR_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core2_VAR_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_OsApplication_Core2_VAR_FAST_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core2_VAR_FAST_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core2_VAR_NOCACHE_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core2_VAR_NOCACHE_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core2_VAR_NOCACHE_8BIT_OPEN
#  error Section OS_OsApplication_Core2_VAR_NOCACHE_8BIT is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core2_VAR_NOCACHE_8BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core2_VAR_NOCACHE_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core2_VAR_NOCACHE_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core2_VAR_NOCACHE_16BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_OsApplication_Core2_VAR_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core2_VAR_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_OsApplication_Core2_VAR_FAST_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core2_VAR_FAST_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core2_VAR_NOCACHE_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core2_VAR_NOCACHE_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core2_VAR_NOCACHE_16BIT_OPEN
#  error Section OS_OsApplication_Core2_VAR_NOCACHE_16BIT is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core2_VAR_NOCACHE_16BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core2_VAR_NOCACHE_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core2_VAR_NOCACHE_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core2_VAR_NOCACHE_32BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_OsApplication_Core2_VAR_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core2_VAR_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_OsApplication_Core2_VAR_FAST_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core2_VAR_FAST_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core2_VAR_NOCACHE_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core2_VAR_NOCACHE_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core2_VAR_NOCACHE_32BIT_OPEN
#  error Section OS_OsApplication_Core2_VAR_NOCACHE_32BIT is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core2_VAR_NOCACHE_32BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core2_VAR_NOCACHE_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core2_VAR_NOCACHE_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core2_VAR_NOCACHE_UNSPECIFIED_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_OsApplication_Core2_VAR_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core2_VAR_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_OsApplication_Core2_VAR_FAST_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core2_VAR_FAST_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core2_VAR_NOCACHE_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core2_VAR_NOCACHE_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core2_VAR_NOCACHE_UNSPECIFIED_OPEN
#  error Section OS_OsApplication_Core2_VAR_NOCACHE_UNSPECIFIED is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core2_VAR_NOCACHE_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core2_VAR_NOCACHE_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core2_VAR_NOCACHE_NOINIT_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core2_VAR_NOCACHE_NOINIT_BOOLEAN_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_OsApplication_Core2_VAR_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core2_VAR_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_OsApplication_Core2_VAR_FAST_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core2_VAR_FAST_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core2_VAR_NOCACHE_NOINIT_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core2_VAR_NOCACHE_NOINIT_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core2_VAR_NOCACHE_NOINIT_BOOLEAN_OPEN
#  error Section OS_OsApplication_Core2_VAR_NOCACHE_NOINIT_BOOLEAN is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core2_VAR_NOCACHE_NOINIT_BOOLEAN_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core2_VAR_NOCACHE_NOINIT_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core2_VAR_NOCACHE_NOINIT_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core2_VAR_NOCACHE_NOINIT_8BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_OsApplication_Core2_VAR_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core2_VAR_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_OsApplication_Core2_VAR_FAST_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core2_VAR_FAST_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core2_VAR_NOCACHE_NOINIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core2_VAR_NOCACHE_NOINIT_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core2_VAR_NOCACHE_NOINIT_8BIT_OPEN
#  error Section OS_OsApplication_Core2_VAR_NOCACHE_NOINIT_8BIT is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core2_VAR_NOCACHE_NOINIT_8BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core2_VAR_NOCACHE_NOINIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core2_VAR_NOCACHE_NOINIT_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core2_VAR_NOCACHE_NOINIT_16BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_OsApplication_Core2_VAR_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core2_VAR_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_OsApplication_Core2_VAR_FAST_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core2_VAR_FAST_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core2_VAR_NOCACHE_NOINIT_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core2_VAR_NOCACHE_NOINIT_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core2_VAR_NOCACHE_NOINIT_16BIT_OPEN
#  error Section OS_OsApplication_Core2_VAR_NOCACHE_NOINIT_16BIT is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core2_VAR_NOCACHE_NOINIT_16BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core2_VAR_NOCACHE_NOINIT_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core2_VAR_NOCACHE_NOINIT_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core2_VAR_NOCACHE_NOINIT_32BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_OsApplication_Core2_VAR_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core2_VAR_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_OsApplication_Core2_VAR_FAST_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core2_VAR_FAST_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core2_VAR_NOCACHE_NOINIT_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core2_VAR_NOCACHE_NOINIT_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core2_VAR_NOCACHE_NOINIT_32BIT_OPEN
#  error Section OS_OsApplication_Core2_VAR_NOCACHE_NOINIT_32BIT is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core2_VAR_NOCACHE_NOINIT_32BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core2_VAR_NOCACHE_NOINIT_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core2_VAR_NOCACHE_NOINIT_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core2_VAR_NOCACHE_NOINIT_UNSPECIFIED_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_OsApplication_Core2_VAR_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core2_VAR_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_OsApplication_Core2_VAR_FAST_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core2_VAR_FAST_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core2_VAR_NOCACHE_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core2_VAR_NOCACHE_NOINIT_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core2_VAR_NOCACHE_NOINIT_UNSPECIFIED_OPEN
#  error Section OS_OsApplication_Core2_VAR_NOCACHE_NOINIT_UNSPECIFIED is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core2_VAR_NOCACHE_NOINIT_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core2_VAR_NOCACHE_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core2_VAR_NOCACHE_ZERO_INIT_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core2_VAR_NOCACHE_ZERO_INIT_BOOLEAN_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss "OS_OsApplication_Core2_VAR_NOCACHE_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core2_VAR_NOCACHE_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss "OS_OsApplication_Core2_VAR_FAST_NOCACHE_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core2_VAR_FAST_NOCACHE_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core2_VAR_NOCACHE_ZERO_INIT_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core2_VAR_NOCACHE_ZERO_INIT_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core2_VAR_NOCACHE_ZERO_INIT_BOOLEAN_OPEN
#  error Section OS_OsApplication_Core2_VAR_NOCACHE_ZERO_INIT_BOOLEAN is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core2_VAR_NOCACHE_ZERO_INIT_BOOLEAN_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core2_VAR_NOCACHE_ZERO_INIT_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core2_VAR_NOCACHE_ZERO_INIT_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core2_VAR_NOCACHE_ZERO_INIT_8BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss "OS_OsApplication_Core2_VAR_NOCACHE_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core2_VAR_NOCACHE_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss "OS_OsApplication_Core2_VAR_FAST_NOCACHE_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core2_VAR_FAST_NOCACHE_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core2_VAR_NOCACHE_ZERO_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core2_VAR_NOCACHE_ZERO_INIT_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core2_VAR_NOCACHE_ZERO_INIT_8BIT_OPEN
#  error Section OS_OsApplication_Core2_VAR_NOCACHE_ZERO_INIT_8BIT is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core2_VAR_NOCACHE_ZERO_INIT_8BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core2_VAR_NOCACHE_ZERO_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core2_VAR_NOCACHE_ZERO_INIT_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core2_VAR_NOCACHE_ZERO_INIT_16BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss "OS_OsApplication_Core2_VAR_NOCACHE_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core2_VAR_NOCACHE_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss "OS_OsApplication_Core2_VAR_FAST_NOCACHE_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core2_VAR_FAST_NOCACHE_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core2_VAR_NOCACHE_ZERO_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core2_VAR_NOCACHE_ZERO_INIT_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core2_VAR_NOCACHE_ZERO_INIT_16BIT_OPEN
#  error Section OS_OsApplication_Core2_VAR_NOCACHE_ZERO_INIT_16BIT is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core2_VAR_NOCACHE_ZERO_INIT_16BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core2_VAR_NOCACHE_ZERO_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core2_VAR_NOCACHE_ZERO_INIT_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core2_VAR_NOCACHE_ZERO_INIT_32BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss "OS_OsApplication_Core2_VAR_NOCACHE_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core2_VAR_NOCACHE_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss "OS_OsApplication_Core2_VAR_FAST_NOCACHE_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core2_VAR_FAST_NOCACHE_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core2_VAR_NOCACHE_ZERO_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core2_VAR_NOCACHE_ZERO_INIT_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core2_VAR_NOCACHE_ZERO_INIT_32BIT_OPEN
#  error Section OS_OsApplication_Core2_VAR_NOCACHE_ZERO_INIT_32BIT is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core2_VAR_NOCACHE_ZERO_INIT_32BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core2_VAR_NOCACHE_ZERO_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_OsApplication_Core2_VAR_NOCACHE_ZERO_INIT_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_OsApplication_Core2_VAR_NOCACHE_ZERO_INIT_UNSPECIFIED_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss "OS_OsApplication_Core2_VAR_NOCACHE_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_OsApplication_Core2_VAR_NOCACHE_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss "OS_OsApplication_Core2_VAR_FAST_NOCACHE_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_OsApplication_Core2_VAR_FAST_NOCACHE_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_OsApplication_Core2_VAR_NOCACHE_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_OsApplication_Core2_VAR_NOCACHE_ZERO_INIT_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_OsApplication_Core2_VAR_NOCACHE_ZERO_INIT_UNSPECIFIED_OPEN
#  error Section OS_OsApplication_Core2_VAR_NOCACHE_ZERO_INIT_UNSPECIFIED is currently not opened and so cannot be closed.
# endif
# undef OS_OsApplication_Core2_VAR_NOCACHE_ZERO_INIT_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_OsApplication_Core2_VAR_NOCACHE_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore0_VAR_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore0_VAR_BOOLEAN_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_SystemApplication_OsCore0_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore0_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_SystemApplication_OsCore0_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore0_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore0_VAR_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore0_VAR_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore0_VAR_BOOLEAN_OPEN
#  error Section OS_SystemApplication_OsCore0_VAR_BOOLEAN is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore0_VAR_BOOLEAN_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore0_VAR_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore0_VAR_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore0_VAR_8BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_SystemApplication_OsCore0_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore0_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_SystemApplication_OsCore0_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore0_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore0_VAR_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore0_VAR_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore0_VAR_8BIT_OPEN
#  error Section OS_SystemApplication_OsCore0_VAR_8BIT is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore0_VAR_8BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore0_VAR_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore0_VAR_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore0_VAR_16BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_SystemApplication_OsCore0_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore0_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_SystemApplication_OsCore0_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore0_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore0_VAR_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore0_VAR_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore0_VAR_16BIT_OPEN
#  error Section OS_SystemApplication_OsCore0_VAR_16BIT is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore0_VAR_16BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore0_VAR_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore0_VAR_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore0_VAR_32BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_SystemApplication_OsCore0_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore0_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_SystemApplication_OsCore0_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore0_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore0_VAR_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore0_VAR_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore0_VAR_32BIT_OPEN
#  error Section OS_SystemApplication_OsCore0_VAR_32BIT is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore0_VAR_32BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore0_VAR_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore0_VAR_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore0_VAR_UNSPECIFIED_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_SystemApplication_OsCore0_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore0_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_SystemApplication_OsCore0_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore0_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore0_VAR_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore0_VAR_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore0_VAR_UNSPECIFIED_OPEN
#  error Section OS_SystemApplication_OsCore0_VAR_UNSPECIFIED is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore0_VAR_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore0_VAR_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore0_VAR_NOINIT_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore0_VAR_NOINIT_BOOLEAN_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_SystemApplication_OsCore0_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore0_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_SystemApplication_OsCore0_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore0_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore0_VAR_NOINIT_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore0_VAR_NOINIT_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore0_VAR_NOINIT_BOOLEAN_OPEN
#  error Section OS_SystemApplication_OsCore0_VAR_NOINIT_BOOLEAN is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore0_VAR_NOINIT_BOOLEAN_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore0_VAR_NOINIT_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore0_VAR_NOINIT_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore0_VAR_NOINIT_8BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_SystemApplication_OsCore0_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore0_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_SystemApplication_OsCore0_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore0_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore0_VAR_NOINIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore0_VAR_NOINIT_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore0_VAR_NOINIT_8BIT_OPEN
#  error Section OS_SystemApplication_OsCore0_VAR_NOINIT_8BIT is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore0_VAR_NOINIT_8BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore0_VAR_NOINIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore0_VAR_NOINIT_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore0_VAR_NOINIT_16BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_SystemApplication_OsCore0_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore0_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_SystemApplication_OsCore0_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore0_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore0_VAR_NOINIT_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore0_VAR_NOINIT_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore0_VAR_NOINIT_16BIT_OPEN
#  error Section OS_SystemApplication_OsCore0_VAR_NOINIT_16BIT is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore0_VAR_NOINIT_16BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore0_VAR_NOINIT_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore0_VAR_NOINIT_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore0_VAR_NOINIT_32BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_SystemApplication_OsCore0_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore0_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_SystemApplication_OsCore0_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore0_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore0_VAR_NOINIT_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore0_VAR_NOINIT_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore0_VAR_NOINIT_32BIT_OPEN
#  error Section OS_SystemApplication_OsCore0_VAR_NOINIT_32BIT is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore0_VAR_NOINIT_32BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore0_VAR_NOINIT_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore0_VAR_NOINIT_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore0_VAR_NOINIT_UNSPECIFIED_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_SystemApplication_OsCore0_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore0_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_SystemApplication_OsCore0_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore0_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore0_VAR_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore0_VAR_NOINIT_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore0_VAR_NOINIT_UNSPECIFIED_OPEN
#  error Section OS_SystemApplication_OsCore0_VAR_NOINIT_UNSPECIFIED is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore0_VAR_NOINIT_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore0_VAR_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore0_VAR_ZERO_INIT_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore0_VAR_ZERO_INIT_BOOLEAN_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss "OS_SystemApplication_OsCore0_VAR_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore0_VAR_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss "OS_SystemApplication_OsCore0_VAR_FAST_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore0_VAR_FAST_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore0_VAR_ZERO_INIT_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore0_VAR_ZERO_INIT_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore0_VAR_ZERO_INIT_BOOLEAN_OPEN
#  error Section OS_SystemApplication_OsCore0_VAR_ZERO_INIT_BOOLEAN is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore0_VAR_ZERO_INIT_BOOLEAN_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore0_VAR_ZERO_INIT_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore0_VAR_ZERO_INIT_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore0_VAR_ZERO_INIT_8BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss "OS_SystemApplication_OsCore0_VAR_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore0_VAR_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss "OS_SystemApplication_OsCore0_VAR_FAST_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore0_VAR_FAST_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore0_VAR_ZERO_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore0_VAR_ZERO_INIT_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore0_VAR_ZERO_INIT_8BIT_OPEN
#  error Section OS_SystemApplication_OsCore0_VAR_ZERO_INIT_8BIT is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore0_VAR_ZERO_INIT_8BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore0_VAR_ZERO_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore0_VAR_ZERO_INIT_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore0_VAR_ZERO_INIT_16BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss "OS_SystemApplication_OsCore0_VAR_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore0_VAR_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss "OS_SystemApplication_OsCore0_VAR_FAST_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore0_VAR_FAST_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore0_VAR_ZERO_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore0_VAR_ZERO_INIT_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore0_VAR_ZERO_INIT_16BIT_OPEN
#  error Section OS_SystemApplication_OsCore0_VAR_ZERO_INIT_16BIT is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore0_VAR_ZERO_INIT_16BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore0_VAR_ZERO_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore0_VAR_ZERO_INIT_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore0_VAR_ZERO_INIT_32BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss "OS_SystemApplication_OsCore0_VAR_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore0_VAR_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss "OS_SystemApplication_OsCore0_VAR_FAST_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore0_VAR_FAST_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore0_VAR_ZERO_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore0_VAR_ZERO_INIT_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore0_VAR_ZERO_INIT_32BIT_OPEN
#  error Section OS_SystemApplication_OsCore0_VAR_ZERO_INIT_32BIT is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore0_VAR_ZERO_INIT_32BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore0_VAR_ZERO_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore0_VAR_ZERO_INIT_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore0_VAR_ZERO_INIT_UNSPECIFIED_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss "OS_SystemApplication_OsCore0_VAR_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore0_VAR_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss "OS_SystemApplication_OsCore0_VAR_FAST_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore0_VAR_FAST_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore0_VAR_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore0_VAR_ZERO_INIT_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore0_VAR_ZERO_INIT_UNSPECIFIED_OPEN
#  error Section OS_SystemApplication_OsCore0_VAR_ZERO_INIT_UNSPECIFIED is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore0_VAR_ZERO_INIT_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore0_VAR_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore0_VAR_FAST_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore0_VAR_FAST_BOOLEAN_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_SystemApplication_OsCore0_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore0_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_SystemApplication_OsCore0_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore0_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore0_VAR_FAST_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore0_VAR_FAST_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore0_VAR_FAST_BOOLEAN_OPEN
#  error Section OS_SystemApplication_OsCore0_VAR_FAST_BOOLEAN is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore0_VAR_FAST_BOOLEAN_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore0_VAR_FAST_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore0_VAR_FAST_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore0_VAR_FAST_8BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_SystemApplication_OsCore0_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore0_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_SystemApplication_OsCore0_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore0_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore0_VAR_FAST_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore0_VAR_FAST_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore0_VAR_FAST_8BIT_OPEN
#  error Section OS_SystemApplication_OsCore0_VAR_FAST_8BIT is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore0_VAR_FAST_8BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore0_VAR_FAST_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore0_VAR_FAST_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore0_VAR_FAST_16BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_SystemApplication_OsCore0_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore0_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_SystemApplication_OsCore0_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore0_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore0_VAR_FAST_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore0_VAR_FAST_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore0_VAR_FAST_16BIT_OPEN
#  error Section OS_SystemApplication_OsCore0_VAR_FAST_16BIT is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore0_VAR_FAST_16BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore0_VAR_FAST_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore0_VAR_FAST_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore0_VAR_FAST_32BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_SystemApplication_OsCore0_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore0_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_SystemApplication_OsCore0_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore0_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore0_VAR_FAST_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore0_VAR_FAST_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore0_VAR_FAST_32BIT_OPEN
#  error Section OS_SystemApplication_OsCore0_VAR_FAST_32BIT is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore0_VAR_FAST_32BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore0_VAR_FAST_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore0_VAR_FAST_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore0_VAR_FAST_UNSPECIFIED_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_SystemApplication_OsCore0_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore0_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_SystemApplication_OsCore0_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore0_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore0_VAR_FAST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore0_VAR_FAST_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore0_VAR_FAST_UNSPECIFIED_OPEN
#  error Section OS_SystemApplication_OsCore0_VAR_FAST_UNSPECIFIED is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore0_VAR_FAST_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore0_VAR_FAST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore0_VAR_FAST_NOINIT_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore0_VAR_FAST_NOINIT_BOOLEAN_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_SystemApplication_OsCore0_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore0_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_SystemApplication_OsCore0_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore0_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore0_VAR_FAST_NOINIT_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore0_VAR_FAST_NOINIT_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore0_VAR_FAST_NOINIT_BOOLEAN_OPEN
#  error Section OS_SystemApplication_OsCore0_VAR_FAST_NOINIT_BOOLEAN is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore0_VAR_FAST_NOINIT_BOOLEAN_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore0_VAR_FAST_NOINIT_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore0_VAR_FAST_NOINIT_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore0_VAR_FAST_NOINIT_8BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_SystemApplication_OsCore0_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore0_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_SystemApplication_OsCore0_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore0_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore0_VAR_FAST_NOINIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore0_VAR_FAST_NOINIT_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore0_VAR_FAST_NOINIT_8BIT_OPEN
#  error Section OS_SystemApplication_OsCore0_VAR_FAST_NOINIT_8BIT is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore0_VAR_FAST_NOINIT_8BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore0_VAR_FAST_NOINIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore0_VAR_FAST_NOINIT_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore0_VAR_FAST_NOINIT_16BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_SystemApplication_OsCore0_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore0_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_SystemApplication_OsCore0_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore0_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore0_VAR_FAST_NOINIT_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore0_VAR_FAST_NOINIT_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore0_VAR_FAST_NOINIT_16BIT_OPEN
#  error Section OS_SystemApplication_OsCore0_VAR_FAST_NOINIT_16BIT is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore0_VAR_FAST_NOINIT_16BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore0_VAR_FAST_NOINIT_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore0_VAR_FAST_NOINIT_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore0_VAR_FAST_NOINIT_32BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_SystemApplication_OsCore0_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore0_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_SystemApplication_OsCore0_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore0_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore0_VAR_FAST_NOINIT_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore0_VAR_FAST_NOINIT_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore0_VAR_FAST_NOINIT_32BIT_OPEN
#  error Section OS_SystemApplication_OsCore0_VAR_FAST_NOINIT_32BIT is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore0_VAR_FAST_NOINIT_32BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore0_VAR_FAST_NOINIT_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore0_VAR_FAST_NOINIT_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore0_VAR_FAST_NOINIT_UNSPECIFIED_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_SystemApplication_OsCore0_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore0_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_SystemApplication_OsCore0_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore0_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore0_VAR_FAST_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore0_VAR_FAST_NOINIT_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore0_VAR_FAST_NOINIT_UNSPECIFIED_OPEN
#  error Section OS_SystemApplication_OsCore0_VAR_FAST_NOINIT_UNSPECIFIED is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore0_VAR_FAST_NOINIT_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore0_VAR_FAST_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore0_VAR_FAST_ZERO_INIT_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore0_VAR_FAST_ZERO_INIT_BOOLEAN_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss "OS_SystemApplication_OsCore0_VAR_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore0_VAR_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss "OS_SystemApplication_OsCore0_VAR_FAST_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore0_VAR_FAST_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore0_VAR_FAST_ZERO_INIT_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore0_VAR_FAST_ZERO_INIT_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore0_VAR_FAST_ZERO_INIT_BOOLEAN_OPEN
#  error Section OS_SystemApplication_OsCore0_VAR_FAST_ZERO_INIT_BOOLEAN is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore0_VAR_FAST_ZERO_INIT_BOOLEAN_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore0_VAR_FAST_ZERO_INIT_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore0_VAR_FAST_ZERO_INIT_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore0_VAR_FAST_ZERO_INIT_8BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss "OS_SystemApplication_OsCore0_VAR_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore0_VAR_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss "OS_SystemApplication_OsCore0_VAR_FAST_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore0_VAR_FAST_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore0_VAR_FAST_ZERO_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore0_VAR_FAST_ZERO_INIT_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore0_VAR_FAST_ZERO_INIT_8BIT_OPEN
#  error Section OS_SystemApplication_OsCore0_VAR_FAST_ZERO_INIT_8BIT is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore0_VAR_FAST_ZERO_INIT_8BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore0_VAR_FAST_ZERO_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore0_VAR_FAST_ZERO_INIT_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore0_VAR_FAST_ZERO_INIT_16BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss "OS_SystemApplication_OsCore0_VAR_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore0_VAR_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss "OS_SystemApplication_OsCore0_VAR_FAST_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore0_VAR_FAST_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore0_VAR_FAST_ZERO_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore0_VAR_FAST_ZERO_INIT_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore0_VAR_FAST_ZERO_INIT_16BIT_OPEN
#  error Section OS_SystemApplication_OsCore0_VAR_FAST_ZERO_INIT_16BIT is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore0_VAR_FAST_ZERO_INIT_16BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore0_VAR_FAST_ZERO_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore0_VAR_FAST_ZERO_INIT_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore0_VAR_FAST_ZERO_INIT_32BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss "OS_SystemApplication_OsCore0_VAR_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore0_VAR_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss "OS_SystemApplication_OsCore0_VAR_FAST_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore0_VAR_FAST_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore0_VAR_FAST_ZERO_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore0_VAR_FAST_ZERO_INIT_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore0_VAR_FAST_ZERO_INIT_32BIT_OPEN
#  error Section OS_SystemApplication_OsCore0_VAR_FAST_ZERO_INIT_32BIT is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore0_VAR_FAST_ZERO_INIT_32BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore0_VAR_FAST_ZERO_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore0_VAR_FAST_ZERO_INIT_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore0_VAR_FAST_ZERO_INIT_UNSPECIFIED_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss "OS_SystemApplication_OsCore0_VAR_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore0_VAR_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss "OS_SystemApplication_OsCore0_VAR_FAST_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore0_VAR_FAST_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore0_VAR_FAST_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore0_VAR_FAST_ZERO_INIT_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore0_VAR_FAST_ZERO_INIT_UNSPECIFIED_OPEN
#  error Section OS_SystemApplication_OsCore0_VAR_FAST_ZERO_INIT_UNSPECIFIED is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore0_VAR_FAST_ZERO_INIT_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore0_VAR_FAST_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore0_VAR_NOCACHE_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore0_VAR_NOCACHE_BOOLEAN_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_SystemApplication_OsCore0_VAR_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore0_VAR_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_SystemApplication_OsCore0_VAR_FAST_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore0_VAR_FAST_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore0_VAR_NOCACHE_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore0_VAR_NOCACHE_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore0_VAR_NOCACHE_BOOLEAN_OPEN
#  error Section OS_SystemApplication_OsCore0_VAR_NOCACHE_BOOLEAN is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore0_VAR_NOCACHE_BOOLEAN_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore0_VAR_NOCACHE_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore0_VAR_NOCACHE_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore0_VAR_NOCACHE_8BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_SystemApplication_OsCore0_VAR_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore0_VAR_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_SystemApplication_OsCore0_VAR_FAST_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore0_VAR_FAST_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore0_VAR_NOCACHE_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore0_VAR_NOCACHE_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore0_VAR_NOCACHE_8BIT_OPEN
#  error Section OS_SystemApplication_OsCore0_VAR_NOCACHE_8BIT is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore0_VAR_NOCACHE_8BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore0_VAR_NOCACHE_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore0_VAR_NOCACHE_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore0_VAR_NOCACHE_16BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_SystemApplication_OsCore0_VAR_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore0_VAR_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_SystemApplication_OsCore0_VAR_FAST_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore0_VAR_FAST_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore0_VAR_NOCACHE_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore0_VAR_NOCACHE_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore0_VAR_NOCACHE_16BIT_OPEN
#  error Section OS_SystemApplication_OsCore0_VAR_NOCACHE_16BIT is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore0_VAR_NOCACHE_16BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore0_VAR_NOCACHE_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore0_VAR_NOCACHE_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore0_VAR_NOCACHE_32BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_SystemApplication_OsCore0_VAR_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore0_VAR_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_SystemApplication_OsCore0_VAR_FAST_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore0_VAR_FAST_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore0_VAR_NOCACHE_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore0_VAR_NOCACHE_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore0_VAR_NOCACHE_32BIT_OPEN
#  error Section OS_SystemApplication_OsCore0_VAR_NOCACHE_32BIT is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore0_VAR_NOCACHE_32BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore0_VAR_NOCACHE_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore0_VAR_NOCACHE_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore0_VAR_NOCACHE_UNSPECIFIED_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_SystemApplication_OsCore0_VAR_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore0_VAR_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_SystemApplication_OsCore0_VAR_FAST_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore0_VAR_FAST_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore0_VAR_NOCACHE_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore0_VAR_NOCACHE_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore0_VAR_NOCACHE_UNSPECIFIED_OPEN
#  error Section OS_SystemApplication_OsCore0_VAR_NOCACHE_UNSPECIFIED is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore0_VAR_NOCACHE_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore0_VAR_NOCACHE_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore0_VAR_NOCACHE_NOINIT_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore0_VAR_NOCACHE_NOINIT_BOOLEAN_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_SystemApplication_OsCore0_VAR_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore0_VAR_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_SystemApplication_OsCore0_VAR_FAST_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore0_VAR_FAST_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore0_VAR_NOCACHE_NOINIT_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore0_VAR_NOCACHE_NOINIT_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore0_VAR_NOCACHE_NOINIT_BOOLEAN_OPEN
#  error Section OS_SystemApplication_OsCore0_VAR_NOCACHE_NOINIT_BOOLEAN is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore0_VAR_NOCACHE_NOINIT_BOOLEAN_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore0_VAR_NOCACHE_NOINIT_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore0_VAR_NOCACHE_NOINIT_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore0_VAR_NOCACHE_NOINIT_8BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_SystemApplication_OsCore0_VAR_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore0_VAR_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_SystemApplication_OsCore0_VAR_FAST_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore0_VAR_FAST_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore0_VAR_NOCACHE_NOINIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore0_VAR_NOCACHE_NOINIT_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore0_VAR_NOCACHE_NOINIT_8BIT_OPEN
#  error Section OS_SystemApplication_OsCore0_VAR_NOCACHE_NOINIT_8BIT is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore0_VAR_NOCACHE_NOINIT_8BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore0_VAR_NOCACHE_NOINIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore0_VAR_NOCACHE_NOINIT_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore0_VAR_NOCACHE_NOINIT_16BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_SystemApplication_OsCore0_VAR_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore0_VAR_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_SystemApplication_OsCore0_VAR_FAST_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore0_VAR_FAST_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore0_VAR_NOCACHE_NOINIT_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore0_VAR_NOCACHE_NOINIT_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore0_VAR_NOCACHE_NOINIT_16BIT_OPEN
#  error Section OS_SystemApplication_OsCore0_VAR_NOCACHE_NOINIT_16BIT is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore0_VAR_NOCACHE_NOINIT_16BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore0_VAR_NOCACHE_NOINIT_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore0_VAR_NOCACHE_NOINIT_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore0_VAR_NOCACHE_NOINIT_32BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_SystemApplication_OsCore0_VAR_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore0_VAR_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_SystemApplication_OsCore0_VAR_FAST_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore0_VAR_FAST_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore0_VAR_NOCACHE_NOINIT_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore0_VAR_NOCACHE_NOINIT_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore0_VAR_NOCACHE_NOINIT_32BIT_OPEN
#  error Section OS_SystemApplication_OsCore0_VAR_NOCACHE_NOINIT_32BIT is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore0_VAR_NOCACHE_NOINIT_32BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore0_VAR_NOCACHE_NOINIT_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore0_VAR_NOCACHE_NOINIT_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore0_VAR_NOCACHE_NOINIT_UNSPECIFIED_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_SystemApplication_OsCore0_VAR_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore0_VAR_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_SystemApplication_OsCore0_VAR_FAST_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore0_VAR_FAST_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore0_VAR_NOCACHE_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore0_VAR_NOCACHE_NOINIT_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore0_VAR_NOCACHE_NOINIT_UNSPECIFIED_OPEN
#  error Section OS_SystemApplication_OsCore0_VAR_NOCACHE_NOINIT_UNSPECIFIED is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore0_VAR_NOCACHE_NOINIT_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore0_VAR_NOCACHE_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore0_VAR_NOCACHE_ZERO_INIT_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore0_VAR_NOCACHE_ZERO_INIT_BOOLEAN_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss "OS_SystemApplication_OsCore0_VAR_NOCACHE_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore0_VAR_NOCACHE_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss "OS_SystemApplication_OsCore0_VAR_FAST_NOCACHE_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore0_VAR_FAST_NOCACHE_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore0_VAR_NOCACHE_ZERO_INIT_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore0_VAR_NOCACHE_ZERO_INIT_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore0_VAR_NOCACHE_ZERO_INIT_BOOLEAN_OPEN
#  error Section OS_SystemApplication_OsCore0_VAR_NOCACHE_ZERO_INIT_BOOLEAN is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore0_VAR_NOCACHE_ZERO_INIT_BOOLEAN_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore0_VAR_NOCACHE_ZERO_INIT_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore0_VAR_NOCACHE_ZERO_INIT_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore0_VAR_NOCACHE_ZERO_INIT_8BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss "OS_SystemApplication_OsCore0_VAR_NOCACHE_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore0_VAR_NOCACHE_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss "OS_SystemApplication_OsCore0_VAR_FAST_NOCACHE_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore0_VAR_FAST_NOCACHE_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore0_VAR_NOCACHE_ZERO_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore0_VAR_NOCACHE_ZERO_INIT_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore0_VAR_NOCACHE_ZERO_INIT_8BIT_OPEN
#  error Section OS_SystemApplication_OsCore0_VAR_NOCACHE_ZERO_INIT_8BIT is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore0_VAR_NOCACHE_ZERO_INIT_8BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore0_VAR_NOCACHE_ZERO_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore0_VAR_NOCACHE_ZERO_INIT_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore0_VAR_NOCACHE_ZERO_INIT_16BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss "OS_SystemApplication_OsCore0_VAR_NOCACHE_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore0_VAR_NOCACHE_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss "OS_SystemApplication_OsCore0_VAR_FAST_NOCACHE_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore0_VAR_FAST_NOCACHE_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore0_VAR_NOCACHE_ZERO_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore0_VAR_NOCACHE_ZERO_INIT_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore0_VAR_NOCACHE_ZERO_INIT_16BIT_OPEN
#  error Section OS_SystemApplication_OsCore0_VAR_NOCACHE_ZERO_INIT_16BIT is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore0_VAR_NOCACHE_ZERO_INIT_16BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore0_VAR_NOCACHE_ZERO_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore0_VAR_NOCACHE_ZERO_INIT_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore0_VAR_NOCACHE_ZERO_INIT_32BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss "OS_SystemApplication_OsCore0_VAR_NOCACHE_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore0_VAR_NOCACHE_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss "OS_SystemApplication_OsCore0_VAR_FAST_NOCACHE_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore0_VAR_FAST_NOCACHE_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore0_VAR_NOCACHE_ZERO_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore0_VAR_NOCACHE_ZERO_INIT_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore0_VAR_NOCACHE_ZERO_INIT_32BIT_OPEN
#  error Section OS_SystemApplication_OsCore0_VAR_NOCACHE_ZERO_INIT_32BIT is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore0_VAR_NOCACHE_ZERO_INIT_32BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore0_VAR_NOCACHE_ZERO_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore0_VAR_NOCACHE_ZERO_INIT_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore0_VAR_NOCACHE_ZERO_INIT_UNSPECIFIED_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss "OS_SystemApplication_OsCore0_VAR_NOCACHE_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore0_VAR_NOCACHE_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss "OS_SystemApplication_OsCore0_VAR_FAST_NOCACHE_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore0_VAR_FAST_NOCACHE_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore0_VAR_NOCACHE_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore0_VAR_NOCACHE_ZERO_INIT_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore0_VAR_NOCACHE_ZERO_INIT_UNSPECIFIED_OPEN
#  error Section OS_SystemApplication_OsCore0_VAR_NOCACHE_ZERO_INIT_UNSPECIFIED is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore0_VAR_NOCACHE_ZERO_INIT_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore0_VAR_NOCACHE_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore1_VAR_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore1_VAR_BOOLEAN_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_SystemApplication_OsCore1_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore1_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_SystemApplication_OsCore1_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore1_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore1_VAR_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore1_VAR_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore1_VAR_BOOLEAN_OPEN
#  error Section OS_SystemApplication_OsCore1_VAR_BOOLEAN is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore1_VAR_BOOLEAN_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore1_VAR_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore1_VAR_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore1_VAR_8BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_SystemApplication_OsCore1_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore1_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_SystemApplication_OsCore1_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore1_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore1_VAR_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore1_VAR_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore1_VAR_8BIT_OPEN
#  error Section OS_SystemApplication_OsCore1_VAR_8BIT is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore1_VAR_8BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore1_VAR_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore1_VAR_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore1_VAR_16BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_SystemApplication_OsCore1_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore1_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_SystemApplication_OsCore1_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore1_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore1_VAR_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore1_VAR_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore1_VAR_16BIT_OPEN
#  error Section OS_SystemApplication_OsCore1_VAR_16BIT is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore1_VAR_16BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore1_VAR_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore1_VAR_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore1_VAR_32BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_SystemApplication_OsCore1_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore1_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_SystemApplication_OsCore1_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore1_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore1_VAR_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore1_VAR_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore1_VAR_32BIT_OPEN
#  error Section OS_SystemApplication_OsCore1_VAR_32BIT is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore1_VAR_32BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore1_VAR_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore1_VAR_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore1_VAR_UNSPECIFIED_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_SystemApplication_OsCore1_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore1_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_SystemApplication_OsCore1_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore1_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore1_VAR_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore1_VAR_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore1_VAR_UNSPECIFIED_OPEN
#  error Section OS_SystemApplication_OsCore1_VAR_UNSPECIFIED is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore1_VAR_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore1_VAR_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore1_VAR_NOINIT_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore1_VAR_NOINIT_BOOLEAN_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_SystemApplication_OsCore1_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore1_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_SystemApplication_OsCore1_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore1_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore1_VAR_NOINIT_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore1_VAR_NOINIT_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore1_VAR_NOINIT_BOOLEAN_OPEN
#  error Section OS_SystemApplication_OsCore1_VAR_NOINIT_BOOLEAN is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore1_VAR_NOINIT_BOOLEAN_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore1_VAR_NOINIT_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore1_VAR_NOINIT_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore1_VAR_NOINIT_8BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_SystemApplication_OsCore1_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore1_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_SystemApplication_OsCore1_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore1_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore1_VAR_NOINIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore1_VAR_NOINIT_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore1_VAR_NOINIT_8BIT_OPEN
#  error Section OS_SystemApplication_OsCore1_VAR_NOINIT_8BIT is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore1_VAR_NOINIT_8BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore1_VAR_NOINIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore1_VAR_NOINIT_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore1_VAR_NOINIT_16BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_SystemApplication_OsCore1_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore1_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_SystemApplication_OsCore1_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore1_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore1_VAR_NOINIT_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore1_VAR_NOINIT_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore1_VAR_NOINIT_16BIT_OPEN
#  error Section OS_SystemApplication_OsCore1_VAR_NOINIT_16BIT is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore1_VAR_NOINIT_16BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore1_VAR_NOINIT_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore1_VAR_NOINIT_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore1_VAR_NOINIT_32BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_SystemApplication_OsCore1_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore1_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_SystemApplication_OsCore1_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore1_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore1_VAR_NOINIT_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore1_VAR_NOINIT_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore1_VAR_NOINIT_32BIT_OPEN
#  error Section OS_SystemApplication_OsCore1_VAR_NOINIT_32BIT is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore1_VAR_NOINIT_32BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore1_VAR_NOINIT_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore1_VAR_NOINIT_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore1_VAR_NOINIT_UNSPECIFIED_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_SystemApplication_OsCore1_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore1_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_SystemApplication_OsCore1_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore1_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore1_VAR_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore1_VAR_NOINIT_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore1_VAR_NOINIT_UNSPECIFIED_OPEN
#  error Section OS_SystemApplication_OsCore1_VAR_NOINIT_UNSPECIFIED is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore1_VAR_NOINIT_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore1_VAR_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore1_VAR_ZERO_INIT_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore1_VAR_ZERO_INIT_BOOLEAN_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss "OS_SystemApplication_OsCore1_VAR_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore1_VAR_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss "OS_SystemApplication_OsCore1_VAR_FAST_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore1_VAR_FAST_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore1_VAR_ZERO_INIT_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore1_VAR_ZERO_INIT_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore1_VAR_ZERO_INIT_BOOLEAN_OPEN
#  error Section OS_SystemApplication_OsCore1_VAR_ZERO_INIT_BOOLEAN is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore1_VAR_ZERO_INIT_BOOLEAN_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore1_VAR_ZERO_INIT_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore1_VAR_ZERO_INIT_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore1_VAR_ZERO_INIT_8BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss "OS_SystemApplication_OsCore1_VAR_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore1_VAR_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss "OS_SystemApplication_OsCore1_VAR_FAST_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore1_VAR_FAST_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore1_VAR_ZERO_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore1_VAR_ZERO_INIT_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore1_VAR_ZERO_INIT_8BIT_OPEN
#  error Section OS_SystemApplication_OsCore1_VAR_ZERO_INIT_8BIT is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore1_VAR_ZERO_INIT_8BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore1_VAR_ZERO_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore1_VAR_ZERO_INIT_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore1_VAR_ZERO_INIT_16BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss "OS_SystemApplication_OsCore1_VAR_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore1_VAR_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss "OS_SystemApplication_OsCore1_VAR_FAST_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore1_VAR_FAST_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore1_VAR_ZERO_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore1_VAR_ZERO_INIT_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore1_VAR_ZERO_INIT_16BIT_OPEN
#  error Section OS_SystemApplication_OsCore1_VAR_ZERO_INIT_16BIT is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore1_VAR_ZERO_INIT_16BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore1_VAR_ZERO_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore1_VAR_ZERO_INIT_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore1_VAR_ZERO_INIT_32BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss "OS_SystemApplication_OsCore1_VAR_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore1_VAR_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss "OS_SystemApplication_OsCore1_VAR_FAST_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore1_VAR_FAST_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore1_VAR_ZERO_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore1_VAR_ZERO_INIT_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore1_VAR_ZERO_INIT_32BIT_OPEN
#  error Section OS_SystemApplication_OsCore1_VAR_ZERO_INIT_32BIT is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore1_VAR_ZERO_INIT_32BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore1_VAR_ZERO_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore1_VAR_ZERO_INIT_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore1_VAR_ZERO_INIT_UNSPECIFIED_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss "OS_SystemApplication_OsCore1_VAR_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore1_VAR_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss "OS_SystemApplication_OsCore1_VAR_FAST_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore1_VAR_FAST_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore1_VAR_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore1_VAR_ZERO_INIT_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore1_VAR_ZERO_INIT_UNSPECIFIED_OPEN
#  error Section OS_SystemApplication_OsCore1_VAR_ZERO_INIT_UNSPECIFIED is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore1_VAR_ZERO_INIT_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore1_VAR_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore1_VAR_FAST_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore1_VAR_FAST_BOOLEAN_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_SystemApplication_OsCore1_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore1_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_SystemApplication_OsCore1_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore1_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore1_VAR_FAST_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore1_VAR_FAST_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore1_VAR_FAST_BOOLEAN_OPEN
#  error Section OS_SystemApplication_OsCore1_VAR_FAST_BOOLEAN is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore1_VAR_FAST_BOOLEAN_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore1_VAR_FAST_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore1_VAR_FAST_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore1_VAR_FAST_8BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_SystemApplication_OsCore1_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore1_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_SystemApplication_OsCore1_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore1_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore1_VAR_FAST_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore1_VAR_FAST_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore1_VAR_FAST_8BIT_OPEN
#  error Section OS_SystemApplication_OsCore1_VAR_FAST_8BIT is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore1_VAR_FAST_8BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore1_VAR_FAST_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore1_VAR_FAST_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore1_VAR_FAST_16BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_SystemApplication_OsCore1_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore1_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_SystemApplication_OsCore1_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore1_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore1_VAR_FAST_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore1_VAR_FAST_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore1_VAR_FAST_16BIT_OPEN
#  error Section OS_SystemApplication_OsCore1_VAR_FAST_16BIT is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore1_VAR_FAST_16BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore1_VAR_FAST_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore1_VAR_FAST_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore1_VAR_FAST_32BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_SystemApplication_OsCore1_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore1_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_SystemApplication_OsCore1_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore1_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore1_VAR_FAST_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore1_VAR_FAST_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore1_VAR_FAST_32BIT_OPEN
#  error Section OS_SystemApplication_OsCore1_VAR_FAST_32BIT is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore1_VAR_FAST_32BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore1_VAR_FAST_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore1_VAR_FAST_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore1_VAR_FAST_UNSPECIFIED_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_SystemApplication_OsCore1_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore1_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_SystemApplication_OsCore1_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore1_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore1_VAR_FAST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore1_VAR_FAST_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore1_VAR_FAST_UNSPECIFIED_OPEN
#  error Section OS_SystemApplication_OsCore1_VAR_FAST_UNSPECIFIED is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore1_VAR_FAST_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore1_VAR_FAST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore1_VAR_FAST_NOINIT_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore1_VAR_FAST_NOINIT_BOOLEAN_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_SystemApplication_OsCore1_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore1_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_SystemApplication_OsCore1_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore1_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore1_VAR_FAST_NOINIT_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore1_VAR_FAST_NOINIT_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore1_VAR_FAST_NOINIT_BOOLEAN_OPEN
#  error Section OS_SystemApplication_OsCore1_VAR_FAST_NOINIT_BOOLEAN is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore1_VAR_FAST_NOINIT_BOOLEAN_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore1_VAR_FAST_NOINIT_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore1_VAR_FAST_NOINIT_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore1_VAR_FAST_NOINIT_8BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_SystemApplication_OsCore1_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore1_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_SystemApplication_OsCore1_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore1_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore1_VAR_FAST_NOINIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore1_VAR_FAST_NOINIT_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore1_VAR_FAST_NOINIT_8BIT_OPEN
#  error Section OS_SystemApplication_OsCore1_VAR_FAST_NOINIT_8BIT is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore1_VAR_FAST_NOINIT_8BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore1_VAR_FAST_NOINIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore1_VAR_FAST_NOINIT_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore1_VAR_FAST_NOINIT_16BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_SystemApplication_OsCore1_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore1_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_SystemApplication_OsCore1_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore1_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore1_VAR_FAST_NOINIT_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore1_VAR_FAST_NOINIT_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore1_VAR_FAST_NOINIT_16BIT_OPEN
#  error Section OS_SystemApplication_OsCore1_VAR_FAST_NOINIT_16BIT is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore1_VAR_FAST_NOINIT_16BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore1_VAR_FAST_NOINIT_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore1_VAR_FAST_NOINIT_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore1_VAR_FAST_NOINIT_32BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_SystemApplication_OsCore1_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore1_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_SystemApplication_OsCore1_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore1_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore1_VAR_FAST_NOINIT_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore1_VAR_FAST_NOINIT_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore1_VAR_FAST_NOINIT_32BIT_OPEN
#  error Section OS_SystemApplication_OsCore1_VAR_FAST_NOINIT_32BIT is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore1_VAR_FAST_NOINIT_32BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore1_VAR_FAST_NOINIT_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore1_VAR_FAST_NOINIT_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore1_VAR_FAST_NOINIT_UNSPECIFIED_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_SystemApplication_OsCore1_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore1_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_SystemApplication_OsCore1_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore1_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore1_VAR_FAST_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore1_VAR_FAST_NOINIT_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore1_VAR_FAST_NOINIT_UNSPECIFIED_OPEN
#  error Section OS_SystemApplication_OsCore1_VAR_FAST_NOINIT_UNSPECIFIED is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore1_VAR_FAST_NOINIT_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore1_VAR_FAST_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore1_VAR_FAST_ZERO_INIT_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore1_VAR_FAST_ZERO_INIT_BOOLEAN_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss "OS_SystemApplication_OsCore1_VAR_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore1_VAR_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss "OS_SystemApplication_OsCore1_VAR_FAST_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore1_VAR_FAST_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore1_VAR_FAST_ZERO_INIT_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore1_VAR_FAST_ZERO_INIT_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore1_VAR_FAST_ZERO_INIT_BOOLEAN_OPEN
#  error Section OS_SystemApplication_OsCore1_VAR_FAST_ZERO_INIT_BOOLEAN is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore1_VAR_FAST_ZERO_INIT_BOOLEAN_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore1_VAR_FAST_ZERO_INIT_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore1_VAR_FAST_ZERO_INIT_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore1_VAR_FAST_ZERO_INIT_8BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss "OS_SystemApplication_OsCore1_VAR_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore1_VAR_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss "OS_SystemApplication_OsCore1_VAR_FAST_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore1_VAR_FAST_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore1_VAR_FAST_ZERO_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore1_VAR_FAST_ZERO_INIT_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore1_VAR_FAST_ZERO_INIT_8BIT_OPEN
#  error Section OS_SystemApplication_OsCore1_VAR_FAST_ZERO_INIT_8BIT is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore1_VAR_FAST_ZERO_INIT_8BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore1_VAR_FAST_ZERO_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore1_VAR_FAST_ZERO_INIT_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore1_VAR_FAST_ZERO_INIT_16BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss "OS_SystemApplication_OsCore1_VAR_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore1_VAR_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss "OS_SystemApplication_OsCore1_VAR_FAST_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore1_VAR_FAST_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore1_VAR_FAST_ZERO_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore1_VAR_FAST_ZERO_INIT_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore1_VAR_FAST_ZERO_INIT_16BIT_OPEN
#  error Section OS_SystemApplication_OsCore1_VAR_FAST_ZERO_INIT_16BIT is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore1_VAR_FAST_ZERO_INIT_16BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore1_VAR_FAST_ZERO_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore1_VAR_FAST_ZERO_INIT_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore1_VAR_FAST_ZERO_INIT_32BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss "OS_SystemApplication_OsCore1_VAR_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore1_VAR_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss "OS_SystemApplication_OsCore1_VAR_FAST_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore1_VAR_FAST_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore1_VAR_FAST_ZERO_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore1_VAR_FAST_ZERO_INIT_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore1_VAR_FAST_ZERO_INIT_32BIT_OPEN
#  error Section OS_SystemApplication_OsCore1_VAR_FAST_ZERO_INIT_32BIT is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore1_VAR_FAST_ZERO_INIT_32BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore1_VAR_FAST_ZERO_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore1_VAR_FAST_ZERO_INIT_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore1_VAR_FAST_ZERO_INIT_UNSPECIFIED_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss "OS_SystemApplication_OsCore1_VAR_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore1_VAR_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss "OS_SystemApplication_OsCore1_VAR_FAST_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore1_VAR_FAST_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore1_VAR_FAST_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore1_VAR_FAST_ZERO_INIT_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore1_VAR_FAST_ZERO_INIT_UNSPECIFIED_OPEN
#  error Section OS_SystemApplication_OsCore1_VAR_FAST_ZERO_INIT_UNSPECIFIED is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore1_VAR_FAST_ZERO_INIT_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore1_VAR_FAST_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore1_VAR_NOCACHE_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore1_VAR_NOCACHE_BOOLEAN_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_SystemApplication_OsCore1_VAR_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore1_VAR_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_SystemApplication_OsCore1_VAR_FAST_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore1_VAR_FAST_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore1_VAR_NOCACHE_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore1_VAR_NOCACHE_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore1_VAR_NOCACHE_BOOLEAN_OPEN
#  error Section OS_SystemApplication_OsCore1_VAR_NOCACHE_BOOLEAN is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore1_VAR_NOCACHE_BOOLEAN_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore1_VAR_NOCACHE_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore1_VAR_NOCACHE_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore1_VAR_NOCACHE_8BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_SystemApplication_OsCore1_VAR_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore1_VAR_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_SystemApplication_OsCore1_VAR_FAST_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore1_VAR_FAST_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore1_VAR_NOCACHE_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore1_VAR_NOCACHE_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore1_VAR_NOCACHE_8BIT_OPEN
#  error Section OS_SystemApplication_OsCore1_VAR_NOCACHE_8BIT is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore1_VAR_NOCACHE_8BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore1_VAR_NOCACHE_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore1_VAR_NOCACHE_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore1_VAR_NOCACHE_16BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_SystemApplication_OsCore1_VAR_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore1_VAR_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_SystemApplication_OsCore1_VAR_FAST_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore1_VAR_FAST_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore1_VAR_NOCACHE_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore1_VAR_NOCACHE_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore1_VAR_NOCACHE_16BIT_OPEN
#  error Section OS_SystemApplication_OsCore1_VAR_NOCACHE_16BIT is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore1_VAR_NOCACHE_16BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore1_VAR_NOCACHE_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore1_VAR_NOCACHE_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore1_VAR_NOCACHE_32BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_SystemApplication_OsCore1_VAR_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore1_VAR_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_SystemApplication_OsCore1_VAR_FAST_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore1_VAR_FAST_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore1_VAR_NOCACHE_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore1_VAR_NOCACHE_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore1_VAR_NOCACHE_32BIT_OPEN
#  error Section OS_SystemApplication_OsCore1_VAR_NOCACHE_32BIT is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore1_VAR_NOCACHE_32BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore1_VAR_NOCACHE_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore1_VAR_NOCACHE_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore1_VAR_NOCACHE_UNSPECIFIED_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_SystemApplication_OsCore1_VAR_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore1_VAR_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_SystemApplication_OsCore1_VAR_FAST_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore1_VAR_FAST_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore1_VAR_NOCACHE_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore1_VAR_NOCACHE_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore1_VAR_NOCACHE_UNSPECIFIED_OPEN
#  error Section OS_SystemApplication_OsCore1_VAR_NOCACHE_UNSPECIFIED is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore1_VAR_NOCACHE_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore1_VAR_NOCACHE_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore1_VAR_NOCACHE_NOINIT_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore1_VAR_NOCACHE_NOINIT_BOOLEAN_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_SystemApplication_OsCore1_VAR_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore1_VAR_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_SystemApplication_OsCore1_VAR_FAST_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore1_VAR_FAST_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore1_VAR_NOCACHE_NOINIT_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore1_VAR_NOCACHE_NOINIT_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore1_VAR_NOCACHE_NOINIT_BOOLEAN_OPEN
#  error Section OS_SystemApplication_OsCore1_VAR_NOCACHE_NOINIT_BOOLEAN is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore1_VAR_NOCACHE_NOINIT_BOOLEAN_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore1_VAR_NOCACHE_NOINIT_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore1_VAR_NOCACHE_NOINIT_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore1_VAR_NOCACHE_NOINIT_8BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_SystemApplication_OsCore1_VAR_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore1_VAR_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_SystemApplication_OsCore1_VAR_FAST_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore1_VAR_FAST_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore1_VAR_NOCACHE_NOINIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore1_VAR_NOCACHE_NOINIT_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore1_VAR_NOCACHE_NOINIT_8BIT_OPEN
#  error Section OS_SystemApplication_OsCore1_VAR_NOCACHE_NOINIT_8BIT is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore1_VAR_NOCACHE_NOINIT_8BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore1_VAR_NOCACHE_NOINIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore1_VAR_NOCACHE_NOINIT_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore1_VAR_NOCACHE_NOINIT_16BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_SystemApplication_OsCore1_VAR_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore1_VAR_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_SystemApplication_OsCore1_VAR_FAST_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore1_VAR_FAST_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore1_VAR_NOCACHE_NOINIT_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore1_VAR_NOCACHE_NOINIT_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore1_VAR_NOCACHE_NOINIT_16BIT_OPEN
#  error Section OS_SystemApplication_OsCore1_VAR_NOCACHE_NOINIT_16BIT is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore1_VAR_NOCACHE_NOINIT_16BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore1_VAR_NOCACHE_NOINIT_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore1_VAR_NOCACHE_NOINIT_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore1_VAR_NOCACHE_NOINIT_32BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_SystemApplication_OsCore1_VAR_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore1_VAR_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_SystemApplication_OsCore1_VAR_FAST_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore1_VAR_FAST_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore1_VAR_NOCACHE_NOINIT_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore1_VAR_NOCACHE_NOINIT_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore1_VAR_NOCACHE_NOINIT_32BIT_OPEN
#  error Section OS_SystemApplication_OsCore1_VAR_NOCACHE_NOINIT_32BIT is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore1_VAR_NOCACHE_NOINIT_32BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore1_VAR_NOCACHE_NOINIT_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore1_VAR_NOCACHE_NOINIT_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore1_VAR_NOCACHE_NOINIT_UNSPECIFIED_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_SystemApplication_OsCore1_VAR_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore1_VAR_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_SystemApplication_OsCore1_VAR_FAST_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore1_VAR_FAST_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore1_VAR_NOCACHE_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore1_VAR_NOCACHE_NOINIT_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore1_VAR_NOCACHE_NOINIT_UNSPECIFIED_OPEN
#  error Section OS_SystemApplication_OsCore1_VAR_NOCACHE_NOINIT_UNSPECIFIED is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore1_VAR_NOCACHE_NOINIT_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore1_VAR_NOCACHE_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore1_VAR_NOCACHE_ZERO_INIT_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore1_VAR_NOCACHE_ZERO_INIT_BOOLEAN_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss "OS_SystemApplication_OsCore1_VAR_NOCACHE_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore1_VAR_NOCACHE_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss "OS_SystemApplication_OsCore1_VAR_FAST_NOCACHE_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore1_VAR_FAST_NOCACHE_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore1_VAR_NOCACHE_ZERO_INIT_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore1_VAR_NOCACHE_ZERO_INIT_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore1_VAR_NOCACHE_ZERO_INIT_BOOLEAN_OPEN
#  error Section OS_SystemApplication_OsCore1_VAR_NOCACHE_ZERO_INIT_BOOLEAN is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore1_VAR_NOCACHE_ZERO_INIT_BOOLEAN_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore1_VAR_NOCACHE_ZERO_INIT_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore1_VAR_NOCACHE_ZERO_INIT_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore1_VAR_NOCACHE_ZERO_INIT_8BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss "OS_SystemApplication_OsCore1_VAR_NOCACHE_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore1_VAR_NOCACHE_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss "OS_SystemApplication_OsCore1_VAR_FAST_NOCACHE_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore1_VAR_FAST_NOCACHE_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore1_VAR_NOCACHE_ZERO_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore1_VAR_NOCACHE_ZERO_INIT_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore1_VAR_NOCACHE_ZERO_INIT_8BIT_OPEN
#  error Section OS_SystemApplication_OsCore1_VAR_NOCACHE_ZERO_INIT_8BIT is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore1_VAR_NOCACHE_ZERO_INIT_8BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore1_VAR_NOCACHE_ZERO_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore1_VAR_NOCACHE_ZERO_INIT_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore1_VAR_NOCACHE_ZERO_INIT_16BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss "OS_SystemApplication_OsCore1_VAR_NOCACHE_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore1_VAR_NOCACHE_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss "OS_SystemApplication_OsCore1_VAR_FAST_NOCACHE_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore1_VAR_FAST_NOCACHE_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore1_VAR_NOCACHE_ZERO_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore1_VAR_NOCACHE_ZERO_INIT_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore1_VAR_NOCACHE_ZERO_INIT_16BIT_OPEN
#  error Section OS_SystemApplication_OsCore1_VAR_NOCACHE_ZERO_INIT_16BIT is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore1_VAR_NOCACHE_ZERO_INIT_16BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore1_VAR_NOCACHE_ZERO_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore1_VAR_NOCACHE_ZERO_INIT_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore1_VAR_NOCACHE_ZERO_INIT_32BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss "OS_SystemApplication_OsCore1_VAR_NOCACHE_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore1_VAR_NOCACHE_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss "OS_SystemApplication_OsCore1_VAR_FAST_NOCACHE_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore1_VAR_FAST_NOCACHE_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore1_VAR_NOCACHE_ZERO_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore1_VAR_NOCACHE_ZERO_INIT_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore1_VAR_NOCACHE_ZERO_INIT_32BIT_OPEN
#  error Section OS_SystemApplication_OsCore1_VAR_NOCACHE_ZERO_INIT_32BIT is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore1_VAR_NOCACHE_ZERO_INIT_32BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore1_VAR_NOCACHE_ZERO_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore1_VAR_NOCACHE_ZERO_INIT_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore1_VAR_NOCACHE_ZERO_INIT_UNSPECIFIED_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss "OS_SystemApplication_OsCore1_VAR_NOCACHE_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore1_VAR_NOCACHE_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss "OS_SystemApplication_OsCore1_VAR_FAST_NOCACHE_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore1_VAR_FAST_NOCACHE_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore1_VAR_NOCACHE_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore1_VAR_NOCACHE_ZERO_INIT_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore1_VAR_NOCACHE_ZERO_INIT_UNSPECIFIED_OPEN
#  error Section OS_SystemApplication_OsCore1_VAR_NOCACHE_ZERO_INIT_UNSPECIFIED is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore1_VAR_NOCACHE_ZERO_INIT_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore1_VAR_NOCACHE_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore2_VAR_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore2_VAR_BOOLEAN_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_SystemApplication_OsCore2_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore2_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_SystemApplication_OsCore2_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore2_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore2_VAR_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore2_VAR_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore2_VAR_BOOLEAN_OPEN
#  error Section OS_SystemApplication_OsCore2_VAR_BOOLEAN is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore2_VAR_BOOLEAN_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore2_VAR_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore2_VAR_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore2_VAR_8BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_SystemApplication_OsCore2_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore2_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_SystemApplication_OsCore2_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore2_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore2_VAR_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore2_VAR_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore2_VAR_8BIT_OPEN
#  error Section OS_SystemApplication_OsCore2_VAR_8BIT is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore2_VAR_8BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore2_VAR_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore2_VAR_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore2_VAR_16BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_SystemApplication_OsCore2_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore2_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_SystemApplication_OsCore2_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore2_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore2_VAR_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore2_VAR_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore2_VAR_16BIT_OPEN
#  error Section OS_SystemApplication_OsCore2_VAR_16BIT is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore2_VAR_16BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore2_VAR_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore2_VAR_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore2_VAR_32BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_SystemApplication_OsCore2_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore2_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_SystemApplication_OsCore2_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore2_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore2_VAR_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore2_VAR_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore2_VAR_32BIT_OPEN
#  error Section OS_SystemApplication_OsCore2_VAR_32BIT is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore2_VAR_32BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore2_VAR_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore2_VAR_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore2_VAR_UNSPECIFIED_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_SystemApplication_OsCore2_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore2_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_SystemApplication_OsCore2_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore2_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore2_VAR_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore2_VAR_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore2_VAR_UNSPECIFIED_OPEN
#  error Section OS_SystemApplication_OsCore2_VAR_UNSPECIFIED is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore2_VAR_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore2_VAR_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore2_VAR_NOINIT_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore2_VAR_NOINIT_BOOLEAN_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_SystemApplication_OsCore2_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore2_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_SystemApplication_OsCore2_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore2_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore2_VAR_NOINIT_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore2_VAR_NOINIT_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore2_VAR_NOINIT_BOOLEAN_OPEN
#  error Section OS_SystemApplication_OsCore2_VAR_NOINIT_BOOLEAN is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore2_VAR_NOINIT_BOOLEAN_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore2_VAR_NOINIT_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore2_VAR_NOINIT_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore2_VAR_NOINIT_8BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_SystemApplication_OsCore2_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore2_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_SystemApplication_OsCore2_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore2_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore2_VAR_NOINIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore2_VAR_NOINIT_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore2_VAR_NOINIT_8BIT_OPEN
#  error Section OS_SystemApplication_OsCore2_VAR_NOINIT_8BIT is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore2_VAR_NOINIT_8BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore2_VAR_NOINIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore2_VAR_NOINIT_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore2_VAR_NOINIT_16BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_SystemApplication_OsCore2_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore2_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_SystemApplication_OsCore2_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore2_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore2_VAR_NOINIT_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore2_VAR_NOINIT_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore2_VAR_NOINIT_16BIT_OPEN
#  error Section OS_SystemApplication_OsCore2_VAR_NOINIT_16BIT is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore2_VAR_NOINIT_16BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore2_VAR_NOINIT_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore2_VAR_NOINIT_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore2_VAR_NOINIT_32BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_SystemApplication_OsCore2_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore2_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_SystemApplication_OsCore2_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore2_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore2_VAR_NOINIT_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore2_VAR_NOINIT_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore2_VAR_NOINIT_32BIT_OPEN
#  error Section OS_SystemApplication_OsCore2_VAR_NOINIT_32BIT is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore2_VAR_NOINIT_32BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore2_VAR_NOINIT_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore2_VAR_NOINIT_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore2_VAR_NOINIT_UNSPECIFIED_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_SystemApplication_OsCore2_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore2_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_SystemApplication_OsCore2_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore2_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore2_VAR_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore2_VAR_NOINIT_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore2_VAR_NOINIT_UNSPECIFIED_OPEN
#  error Section OS_SystemApplication_OsCore2_VAR_NOINIT_UNSPECIFIED is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore2_VAR_NOINIT_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore2_VAR_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore2_VAR_ZERO_INIT_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore2_VAR_ZERO_INIT_BOOLEAN_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss "OS_SystemApplication_OsCore2_VAR_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore2_VAR_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss "OS_SystemApplication_OsCore2_VAR_FAST_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore2_VAR_FAST_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore2_VAR_ZERO_INIT_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore2_VAR_ZERO_INIT_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore2_VAR_ZERO_INIT_BOOLEAN_OPEN
#  error Section OS_SystemApplication_OsCore2_VAR_ZERO_INIT_BOOLEAN is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore2_VAR_ZERO_INIT_BOOLEAN_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore2_VAR_ZERO_INIT_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore2_VAR_ZERO_INIT_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore2_VAR_ZERO_INIT_8BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss "OS_SystemApplication_OsCore2_VAR_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore2_VAR_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss "OS_SystemApplication_OsCore2_VAR_FAST_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore2_VAR_FAST_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore2_VAR_ZERO_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore2_VAR_ZERO_INIT_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore2_VAR_ZERO_INIT_8BIT_OPEN
#  error Section OS_SystemApplication_OsCore2_VAR_ZERO_INIT_8BIT is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore2_VAR_ZERO_INIT_8BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore2_VAR_ZERO_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore2_VAR_ZERO_INIT_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore2_VAR_ZERO_INIT_16BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss "OS_SystemApplication_OsCore2_VAR_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore2_VAR_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss "OS_SystemApplication_OsCore2_VAR_FAST_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore2_VAR_FAST_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore2_VAR_ZERO_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore2_VAR_ZERO_INIT_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore2_VAR_ZERO_INIT_16BIT_OPEN
#  error Section OS_SystemApplication_OsCore2_VAR_ZERO_INIT_16BIT is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore2_VAR_ZERO_INIT_16BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore2_VAR_ZERO_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore2_VAR_ZERO_INIT_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore2_VAR_ZERO_INIT_32BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss "OS_SystemApplication_OsCore2_VAR_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore2_VAR_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss "OS_SystemApplication_OsCore2_VAR_FAST_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore2_VAR_FAST_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore2_VAR_ZERO_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore2_VAR_ZERO_INIT_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore2_VAR_ZERO_INIT_32BIT_OPEN
#  error Section OS_SystemApplication_OsCore2_VAR_ZERO_INIT_32BIT is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore2_VAR_ZERO_INIT_32BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore2_VAR_ZERO_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore2_VAR_ZERO_INIT_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore2_VAR_ZERO_INIT_UNSPECIFIED_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss "OS_SystemApplication_OsCore2_VAR_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore2_VAR_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss "OS_SystemApplication_OsCore2_VAR_FAST_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore2_VAR_FAST_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore2_VAR_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore2_VAR_ZERO_INIT_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore2_VAR_ZERO_INIT_UNSPECIFIED_OPEN
#  error Section OS_SystemApplication_OsCore2_VAR_ZERO_INIT_UNSPECIFIED is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore2_VAR_ZERO_INIT_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore2_VAR_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore2_VAR_FAST_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore2_VAR_FAST_BOOLEAN_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_SystemApplication_OsCore2_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore2_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_SystemApplication_OsCore2_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore2_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore2_VAR_FAST_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore2_VAR_FAST_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore2_VAR_FAST_BOOLEAN_OPEN
#  error Section OS_SystemApplication_OsCore2_VAR_FAST_BOOLEAN is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore2_VAR_FAST_BOOLEAN_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore2_VAR_FAST_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore2_VAR_FAST_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore2_VAR_FAST_8BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_SystemApplication_OsCore2_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore2_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_SystemApplication_OsCore2_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore2_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore2_VAR_FAST_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore2_VAR_FAST_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore2_VAR_FAST_8BIT_OPEN
#  error Section OS_SystemApplication_OsCore2_VAR_FAST_8BIT is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore2_VAR_FAST_8BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore2_VAR_FAST_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore2_VAR_FAST_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore2_VAR_FAST_16BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_SystemApplication_OsCore2_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore2_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_SystemApplication_OsCore2_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore2_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore2_VAR_FAST_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore2_VAR_FAST_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore2_VAR_FAST_16BIT_OPEN
#  error Section OS_SystemApplication_OsCore2_VAR_FAST_16BIT is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore2_VAR_FAST_16BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore2_VAR_FAST_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore2_VAR_FAST_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore2_VAR_FAST_32BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_SystemApplication_OsCore2_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore2_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_SystemApplication_OsCore2_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore2_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore2_VAR_FAST_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore2_VAR_FAST_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore2_VAR_FAST_32BIT_OPEN
#  error Section OS_SystemApplication_OsCore2_VAR_FAST_32BIT is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore2_VAR_FAST_32BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore2_VAR_FAST_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore2_VAR_FAST_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore2_VAR_FAST_UNSPECIFIED_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_SystemApplication_OsCore2_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore2_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_SystemApplication_OsCore2_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore2_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore2_VAR_FAST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore2_VAR_FAST_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore2_VAR_FAST_UNSPECIFIED_OPEN
#  error Section OS_SystemApplication_OsCore2_VAR_FAST_UNSPECIFIED is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore2_VAR_FAST_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore2_VAR_FAST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore2_VAR_FAST_NOINIT_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore2_VAR_FAST_NOINIT_BOOLEAN_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_SystemApplication_OsCore2_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore2_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_SystemApplication_OsCore2_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore2_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore2_VAR_FAST_NOINIT_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore2_VAR_FAST_NOINIT_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore2_VAR_FAST_NOINIT_BOOLEAN_OPEN
#  error Section OS_SystemApplication_OsCore2_VAR_FAST_NOINIT_BOOLEAN is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore2_VAR_FAST_NOINIT_BOOLEAN_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore2_VAR_FAST_NOINIT_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore2_VAR_FAST_NOINIT_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore2_VAR_FAST_NOINIT_8BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_SystemApplication_OsCore2_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore2_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_SystemApplication_OsCore2_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore2_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore2_VAR_FAST_NOINIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore2_VAR_FAST_NOINIT_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore2_VAR_FAST_NOINIT_8BIT_OPEN
#  error Section OS_SystemApplication_OsCore2_VAR_FAST_NOINIT_8BIT is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore2_VAR_FAST_NOINIT_8BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore2_VAR_FAST_NOINIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore2_VAR_FAST_NOINIT_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore2_VAR_FAST_NOINIT_16BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_SystemApplication_OsCore2_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore2_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_SystemApplication_OsCore2_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore2_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore2_VAR_FAST_NOINIT_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore2_VAR_FAST_NOINIT_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore2_VAR_FAST_NOINIT_16BIT_OPEN
#  error Section OS_SystemApplication_OsCore2_VAR_FAST_NOINIT_16BIT is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore2_VAR_FAST_NOINIT_16BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore2_VAR_FAST_NOINIT_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore2_VAR_FAST_NOINIT_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore2_VAR_FAST_NOINIT_32BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_SystemApplication_OsCore2_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore2_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_SystemApplication_OsCore2_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore2_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore2_VAR_FAST_NOINIT_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore2_VAR_FAST_NOINIT_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore2_VAR_FAST_NOINIT_32BIT_OPEN
#  error Section OS_SystemApplication_OsCore2_VAR_FAST_NOINIT_32BIT is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore2_VAR_FAST_NOINIT_32BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore2_VAR_FAST_NOINIT_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore2_VAR_FAST_NOINIT_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore2_VAR_FAST_NOINIT_UNSPECIFIED_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_SystemApplication_OsCore2_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore2_VAR" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_SystemApplication_OsCore2_VAR_FAST_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore2_VAR_FAST" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore2_VAR_FAST_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore2_VAR_FAST_NOINIT_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore2_VAR_FAST_NOINIT_UNSPECIFIED_OPEN
#  error Section OS_SystemApplication_OsCore2_VAR_FAST_NOINIT_UNSPECIFIED is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore2_VAR_FAST_NOINIT_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore2_VAR_FAST_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore2_VAR_FAST_ZERO_INIT_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore2_VAR_FAST_ZERO_INIT_BOOLEAN_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss "OS_SystemApplication_OsCore2_VAR_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore2_VAR_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss "OS_SystemApplication_OsCore2_VAR_FAST_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore2_VAR_FAST_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore2_VAR_FAST_ZERO_INIT_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore2_VAR_FAST_ZERO_INIT_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore2_VAR_FAST_ZERO_INIT_BOOLEAN_OPEN
#  error Section OS_SystemApplication_OsCore2_VAR_FAST_ZERO_INIT_BOOLEAN is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore2_VAR_FAST_ZERO_INIT_BOOLEAN_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore2_VAR_FAST_ZERO_INIT_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore2_VAR_FAST_ZERO_INIT_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore2_VAR_FAST_ZERO_INIT_8BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss "OS_SystemApplication_OsCore2_VAR_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore2_VAR_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss "OS_SystemApplication_OsCore2_VAR_FAST_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore2_VAR_FAST_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore2_VAR_FAST_ZERO_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore2_VAR_FAST_ZERO_INIT_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore2_VAR_FAST_ZERO_INIT_8BIT_OPEN
#  error Section OS_SystemApplication_OsCore2_VAR_FAST_ZERO_INIT_8BIT is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore2_VAR_FAST_ZERO_INIT_8BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore2_VAR_FAST_ZERO_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore2_VAR_FAST_ZERO_INIT_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore2_VAR_FAST_ZERO_INIT_16BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss "OS_SystemApplication_OsCore2_VAR_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore2_VAR_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss "OS_SystemApplication_OsCore2_VAR_FAST_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore2_VAR_FAST_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore2_VAR_FAST_ZERO_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore2_VAR_FAST_ZERO_INIT_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore2_VAR_FAST_ZERO_INIT_16BIT_OPEN
#  error Section OS_SystemApplication_OsCore2_VAR_FAST_ZERO_INIT_16BIT is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore2_VAR_FAST_ZERO_INIT_16BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore2_VAR_FAST_ZERO_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore2_VAR_FAST_ZERO_INIT_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore2_VAR_FAST_ZERO_INIT_32BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss "OS_SystemApplication_OsCore2_VAR_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore2_VAR_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss "OS_SystemApplication_OsCore2_VAR_FAST_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore2_VAR_FAST_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore2_VAR_FAST_ZERO_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore2_VAR_FAST_ZERO_INIT_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore2_VAR_FAST_ZERO_INIT_32BIT_OPEN
#  error Section OS_SystemApplication_OsCore2_VAR_FAST_ZERO_INIT_32BIT is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore2_VAR_FAST_ZERO_INIT_32BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore2_VAR_FAST_ZERO_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore2_VAR_FAST_ZERO_INIT_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore2_VAR_FAST_ZERO_INIT_UNSPECIFIED_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss "OS_SystemApplication_OsCore2_VAR_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore2_VAR_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss "OS_SystemApplication_OsCore2_VAR_FAST_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore2_VAR_FAST_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore2_VAR_FAST_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore2_VAR_FAST_ZERO_INIT_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore2_VAR_FAST_ZERO_INIT_UNSPECIFIED_OPEN
#  error Section OS_SystemApplication_OsCore2_VAR_FAST_ZERO_INIT_UNSPECIFIED is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore2_VAR_FAST_ZERO_INIT_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore2_VAR_FAST_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore2_VAR_NOCACHE_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore2_VAR_NOCACHE_BOOLEAN_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_SystemApplication_OsCore2_VAR_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore2_VAR_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_SystemApplication_OsCore2_VAR_FAST_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore2_VAR_FAST_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore2_VAR_NOCACHE_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore2_VAR_NOCACHE_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore2_VAR_NOCACHE_BOOLEAN_OPEN
#  error Section OS_SystemApplication_OsCore2_VAR_NOCACHE_BOOLEAN is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore2_VAR_NOCACHE_BOOLEAN_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore2_VAR_NOCACHE_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore2_VAR_NOCACHE_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore2_VAR_NOCACHE_8BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_SystemApplication_OsCore2_VAR_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore2_VAR_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_SystemApplication_OsCore2_VAR_FAST_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore2_VAR_FAST_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore2_VAR_NOCACHE_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore2_VAR_NOCACHE_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore2_VAR_NOCACHE_8BIT_OPEN
#  error Section OS_SystemApplication_OsCore2_VAR_NOCACHE_8BIT is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore2_VAR_NOCACHE_8BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore2_VAR_NOCACHE_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore2_VAR_NOCACHE_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore2_VAR_NOCACHE_16BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_SystemApplication_OsCore2_VAR_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore2_VAR_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_SystemApplication_OsCore2_VAR_FAST_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore2_VAR_FAST_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore2_VAR_NOCACHE_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore2_VAR_NOCACHE_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore2_VAR_NOCACHE_16BIT_OPEN
#  error Section OS_SystemApplication_OsCore2_VAR_NOCACHE_16BIT is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore2_VAR_NOCACHE_16BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore2_VAR_NOCACHE_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore2_VAR_NOCACHE_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore2_VAR_NOCACHE_32BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_SystemApplication_OsCore2_VAR_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore2_VAR_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_SystemApplication_OsCore2_VAR_FAST_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore2_VAR_FAST_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore2_VAR_NOCACHE_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore2_VAR_NOCACHE_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore2_VAR_NOCACHE_32BIT_OPEN
#  error Section OS_SystemApplication_OsCore2_VAR_NOCACHE_32BIT is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore2_VAR_NOCACHE_32BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore2_VAR_NOCACHE_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore2_VAR_NOCACHE_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore2_VAR_NOCACHE_UNSPECIFIED_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_SystemApplication_OsCore2_VAR_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore2_VAR_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_SystemApplication_OsCore2_VAR_FAST_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore2_VAR_FAST_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore2_VAR_NOCACHE_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore2_VAR_NOCACHE_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore2_VAR_NOCACHE_UNSPECIFIED_OPEN
#  error Section OS_SystemApplication_OsCore2_VAR_NOCACHE_UNSPECIFIED is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore2_VAR_NOCACHE_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore2_VAR_NOCACHE_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore2_VAR_NOCACHE_NOINIT_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore2_VAR_NOCACHE_NOINIT_BOOLEAN_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_SystemApplication_OsCore2_VAR_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore2_VAR_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_SystemApplication_OsCore2_VAR_FAST_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore2_VAR_FAST_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore2_VAR_NOCACHE_NOINIT_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore2_VAR_NOCACHE_NOINIT_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore2_VAR_NOCACHE_NOINIT_BOOLEAN_OPEN
#  error Section OS_SystemApplication_OsCore2_VAR_NOCACHE_NOINIT_BOOLEAN is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore2_VAR_NOCACHE_NOINIT_BOOLEAN_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore2_VAR_NOCACHE_NOINIT_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore2_VAR_NOCACHE_NOINIT_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore2_VAR_NOCACHE_NOINIT_8BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_SystemApplication_OsCore2_VAR_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore2_VAR_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_SystemApplication_OsCore2_VAR_FAST_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore2_VAR_FAST_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore2_VAR_NOCACHE_NOINIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore2_VAR_NOCACHE_NOINIT_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore2_VAR_NOCACHE_NOINIT_8BIT_OPEN
#  error Section OS_SystemApplication_OsCore2_VAR_NOCACHE_NOINIT_8BIT is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore2_VAR_NOCACHE_NOINIT_8BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore2_VAR_NOCACHE_NOINIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore2_VAR_NOCACHE_NOINIT_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore2_VAR_NOCACHE_NOINIT_16BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_SystemApplication_OsCore2_VAR_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore2_VAR_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_SystemApplication_OsCore2_VAR_FAST_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore2_VAR_FAST_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore2_VAR_NOCACHE_NOINIT_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore2_VAR_NOCACHE_NOINIT_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore2_VAR_NOCACHE_NOINIT_16BIT_OPEN
#  error Section OS_SystemApplication_OsCore2_VAR_NOCACHE_NOINIT_16BIT is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore2_VAR_NOCACHE_NOINIT_16BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore2_VAR_NOCACHE_NOINIT_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore2_VAR_NOCACHE_NOINIT_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore2_VAR_NOCACHE_NOINIT_32BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_SystemApplication_OsCore2_VAR_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore2_VAR_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_SystemApplication_OsCore2_VAR_FAST_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore2_VAR_FAST_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore2_VAR_NOCACHE_NOINIT_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore2_VAR_NOCACHE_NOINIT_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore2_VAR_NOCACHE_NOINIT_32BIT_OPEN
#  error Section OS_SystemApplication_OsCore2_VAR_NOCACHE_NOINIT_32BIT is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore2_VAR_NOCACHE_NOINIT_32BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore2_VAR_NOCACHE_NOINIT_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore2_VAR_NOCACHE_NOINIT_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore2_VAR_NOCACHE_NOINIT_UNSPECIFIED_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear "OS_SystemApplication_OsCore2_VAR_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore2_VAR_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear "OS_SystemApplication_OsCore2_VAR_FAST_NOCACHE_NOINIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore2_VAR_FAST_NOCACHE" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore2_VAR_NOCACHE_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore2_VAR_NOCACHE_NOINIT_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore2_VAR_NOCACHE_NOINIT_UNSPECIFIED_OPEN
#  error Section OS_SystemApplication_OsCore2_VAR_NOCACHE_NOINIT_UNSPECIFIED is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore2_VAR_NOCACHE_NOINIT_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearnoclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma noclear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore2_VAR_NOCACHE_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore2_VAR_NOCACHE_ZERO_INIT_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore2_VAR_NOCACHE_ZERO_INIT_BOOLEAN_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss "OS_SystemApplication_OsCore2_VAR_NOCACHE_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore2_VAR_NOCACHE_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss "OS_SystemApplication_OsCore2_VAR_FAST_NOCACHE_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore2_VAR_FAST_NOCACHE_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore2_VAR_NOCACHE_ZERO_INIT_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore2_VAR_NOCACHE_ZERO_INIT_BOOLEAN /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore2_VAR_NOCACHE_ZERO_INIT_BOOLEAN_OPEN
#  error Section OS_SystemApplication_OsCore2_VAR_NOCACHE_ZERO_INIT_BOOLEAN is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore2_VAR_NOCACHE_ZERO_INIT_BOOLEAN_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore2_VAR_NOCACHE_ZERO_INIT_BOOLEAN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore2_VAR_NOCACHE_ZERO_INIT_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore2_VAR_NOCACHE_ZERO_INIT_8BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss "OS_SystemApplication_OsCore2_VAR_NOCACHE_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore2_VAR_NOCACHE_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss "OS_SystemApplication_OsCore2_VAR_FAST_NOCACHE_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore2_VAR_FAST_NOCACHE_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore2_VAR_NOCACHE_ZERO_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore2_VAR_NOCACHE_ZERO_INIT_8BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore2_VAR_NOCACHE_ZERO_INIT_8BIT_OPEN
#  error Section OS_SystemApplication_OsCore2_VAR_NOCACHE_ZERO_INIT_8BIT is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore2_VAR_NOCACHE_ZERO_INIT_8BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore2_VAR_NOCACHE_ZERO_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore2_VAR_NOCACHE_ZERO_INIT_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore2_VAR_NOCACHE_ZERO_INIT_16BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss "OS_SystemApplication_OsCore2_VAR_NOCACHE_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore2_VAR_NOCACHE_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss "OS_SystemApplication_OsCore2_VAR_FAST_NOCACHE_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore2_VAR_FAST_NOCACHE_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore2_VAR_NOCACHE_ZERO_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore2_VAR_NOCACHE_ZERO_INIT_16BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore2_VAR_NOCACHE_ZERO_INIT_16BIT_OPEN
#  error Section OS_SystemApplication_OsCore2_VAR_NOCACHE_ZERO_INIT_16BIT is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore2_VAR_NOCACHE_ZERO_INIT_16BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore2_VAR_NOCACHE_ZERO_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore2_VAR_NOCACHE_ZERO_INIT_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore2_VAR_NOCACHE_ZERO_INIT_32BIT_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss "OS_SystemApplication_OsCore2_VAR_NOCACHE_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore2_VAR_NOCACHE_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss "OS_SystemApplication_OsCore2_VAR_FAST_NOCACHE_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore2_VAR_FAST_NOCACHE_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore2_VAR_NOCACHE_ZERO_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore2_VAR_NOCACHE_ZERO_INIT_32BIT /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore2_VAR_NOCACHE_ZERO_INIT_32BIT_OPEN
#  error Section OS_SystemApplication_OsCore2_VAR_NOCACHE_ZERO_INIT_32BIT is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore2_VAR_NOCACHE_ZERO_INIT_32BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore2_VAR_NOCACHE_ZERO_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_START_SEC_SystemApplication_OsCore2_VAR_NOCACHE_ZERO_INIT_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_SystemApplication_OsCore2_VAR_NOCACHE_ZERO_INIT_UNSPECIFIED_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss "OS_SystemApplication_OsCore2_VAR_NOCACHE_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata "OS_SystemApplication_OsCore2_VAR_NOCACHE_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss "OS_SystemApplication_OsCore2_VAR_FAST_NOCACHE_ZERO_INIT_bss" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata "OS_SystemApplication_OsCore2_VAR_FAST_NOCACHE_ZERO_INIT" /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_START_SEC_SystemApplication_OsCore2_VAR_NOCACHE_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef OS_STOP_SEC_SystemApplication_OsCore2_VAR_NOCACHE_ZERO_INIT_UNSPECIFIED /* PRQA S 0883 */ /* MD_Os_0883 */
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# ifndef OS_SystemApplication_OsCore2_VAR_NOCACHE_ZERO_INIT_UNSPECIFIED_OPEN
#  error Section OS_SystemApplication_OsCore2_VAR_NOCACHE_ZERO_INIT_UNSPECIFIED is currently not opened and so cannot be closed.
# endif
# undef OS_SystemApplication_OsCore2_VAR_NOCACHE_ZERO_INIT_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section nearbss restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma section neardata restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# pragma clear restore /* PRQA S 3116 */ /* MD_MSR_1.1 */
# undef OS_STOP_SEC_SystemApplication_OsCore2_VAR_NOCACHE_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif



