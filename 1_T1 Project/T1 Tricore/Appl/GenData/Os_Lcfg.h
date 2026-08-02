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
 *              File: Os_Lcfg.h
 *   Generation Time: 2020-07-28 17:15:44
 *           Project: FAW_MultiCore297_Demo - Version 1.0
 *          Delivery: CBD1600956_D02
 *      Tool Version: DaVinci Configurator  5.17.51 SP2
 *
 *
 *********************************************************************************************************************/

#if !defined (OS_LCFG_H)                                                             /* PRQA S 0883 */ /* MD_Os_0883 */
# define OS_LCFG_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/* AUTOSAR includes */
# include "Std_Types.h"

/* Os module declarations */
# include "Os_Cfg.h"
# include "Os_Types.h"
# include "Os_Types_Lcfg.h"

/* Os kernel module dependencies */

/* Os hal dependencies */
# include "Os_Hal_Lcfg.h"

/* User file includes */


/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL CONSTANT DATA PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

# define OS_START_SEC_Task1000ms_Core0_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  Task1000ms_Core0()
 *********************************************************************************************************************/
extern FUNC(void, OS_TASK1000MS_CORE0_CODE) Os_Task_Task1000ms_Core0(void);

# define OS_STOP_SEC_Task1000ms_Core0_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


# define OS_START_SEC_Task1000ms_Core1_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  Task1000ms_Core1()
 *********************************************************************************************************************/
extern FUNC(void, OS_TASK1000MS_CORE1_CODE) Os_Task_Task1000ms_Core1(void);

# define OS_STOP_SEC_Task1000ms_Core1_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


# define OS_START_SEC_Task1000ms_Core2_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  Task1000ms_Core2()
 *********************************************************************************************************************/
extern FUNC(void, OS_TASK1000MS_CORE2_CODE) Os_Task_Task1000ms_Core2(void);

# define OS_STOP_SEC_Task1000ms_Core2_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


# define OS_START_SEC_Task100ms_Core0_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  Task100ms_Core0()
 *********************************************************************************************************************/
extern FUNC(void, OS_TASK100MS_CORE0_CODE) Os_Task_Task100ms_Core0(void);

# define OS_STOP_SEC_Task100ms_Core0_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


# define OS_START_SEC_Task100ms_Core1_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  Task100ms_Core1()
 *********************************************************************************************************************/
extern FUNC(void, OS_TASK100MS_CORE1_CODE) Os_Task_Task100ms_Core1(void);

# define OS_STOP_SEC_Task100ms_Core1_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


# define OS_START_SEC_Task100ms_Core2_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  Task100ms_Core2()
 *********************************************************************************************************************/
extern FUNC(void, OS_TASK100MS_CORE2_CODE) Os_Task_Task100ms_Core2(void);

# define OS_STOP_SEC_Task100ms_Core2_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


# define OS_START_SEC_Task10ms_Core0_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  Task10ms_Core0()
 *********************************************************************************************************************/
extern FUNC(void, OS_TASK10MS_CORE0_CODE) Os_Task_Task10ms_Core0(void);

# define OS_STOP_SEC_Task10ms_Core0_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


# define OS_START_SEC_Task10ms_Core1_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  Task10ms_Core1()
 *********************************************************************************************************************/
extern FUNC(void, OS_TASK10MS_CORE1_CODE) Os_Task_Task10ms_Core1(void);

# define OS_STOP_SEC_Task10ms_Core1_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


# define OS_START_SEC_Task10ms_Core2_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  Task10ms_Core2()
 *********************************************************************************************************************/
extern FUNC(void, OS_TASK10MS_CORE2_CODE) Os_Task_Task10ms_Core2(void);

# define OS_STOP_SEC_Task10ms_Core2_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


# define OS_START_SEC_Task1ms_Core0_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  Task1ms_Core0()
 *********************************************************************************************************************/
extern FUNC(void, OS_TASK1MS_CORE0_CODE) Os_Task_Task1ms_Core0(void);

# define OS_STOP_SEC_Task1ms_Core0_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


# define OS_START_SEC_Task1ms_Core1_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  Task1ms_Core1()
 *********************************************************************************************************************/
extern FUNC(void, OS_TASK1MS_CORE1_CODE) Os_Task_Task1ms_Core1(void);

# define OS_STOP_SEC_Task1ms_Core1_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


# define OS_START_SEC_Task1ms_Core2_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  Task1ms_Core2()
 *********************************************************************************************************************/
extern FUNC(void, OS_TASK1MS_CORE2_CODE) Os_Task_Task1ms_Core2(void);

# define OS_STOP_SEC_Task1ms_Core2_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


# define OS_START_SEC_Task200ms_Core0_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  Task200ms_Core0()
 *********************************************************************************************************************/
extern FUNC(void, OS_TASK200MS_CORE0_CODE) Os_Task_Task200ms_Core0(void);

# define OS_STOP_SEC_Task200ms_Core0_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


# define OS_START_SEC_Task200ms_Core1_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  Task200ms_Core1()
 *********************************************************************************************************************/
extern FUNC(void, OS_TASK200MS_CORE1_CODE) Os_Task_Task200ms_Core1(void);

# define OS_STOP_SEC_Task200ms_Core1_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


# define OS_START_SEC_Task200ms_Core2_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  Task200ms_Core2()
 *********************************************************************************************************************/
extern FUNC(void, OS_TASK200MS_CORE2_CODE) Os_Task_Task200ms_Core2(void);

# define OS_STOP_SEC_Task200ms_Core2_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


# define OS_START_SEC_Task20ms_Core0_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  Task20ms_Core0()
 *********************************************************************************************************************/
extern FUNC(void, OS_TASK20MS_CORE0_CODE) Os_Task_Task20ms_Core0(void);

# define OS_STOP_SEC_Task20ms_Core0_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


# define OS_START_SEC_Task20ms_Core1_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  Task20ms_Core1()
 *********************************************************************************************************************/
extern FUNC(void, OS_TASK20MS_CORE1_CODE) Os_Task_Task20ms_Core1(void);

# define OS_STOP_SEC_Task20ms_Core1_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


# define OS_START_SEC_Task20ms_Core2_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  Task20ms_Core2()
 *********************************************************************************************************************/
extern FUNC(void, OS_TASK20MS_CORE2_CODE) Os_Task_Task20ms_Core2(void);

# define OS_STOP_SEC_Task20ms_Core2_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


# define OS_START_SEC_Task500ms_Core0_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  Task500ms_Core0()
 *********************************************************************************************************************/
extern FUNC(void, OS_TASK500MS_CORE0_CODE) Os_Task_Task500ms_Core0(void);

# define OS_STOP_SEC_Task500ms_Core0_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


# define OS_START_SEC_Task500ms_Core1_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  Task500ms_Core1()
 *********************************************************************************************************************/
extern FUNC(void, OS_TASK500MS_CORE1_CODE) Os_Task_Task500ms_Core1(void);

# define OS_STOP_SEC_Task500ms_Core1_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


# define OS_START_SEC_Task500ms_Core2_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  Task500ms_Core2()
 *********************************************************************************************************************/
extern FUNC(void, OS_TASK500MS_CORE2_CODE) Os_Task_Task500ms_Core2(void);

# define OS_STOP_SEC_Task500ms_Core2_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


# define OS_START_SEC_Task50ms_Core0_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  Task50ms_Core0()
 *********************************************************************************************************************/
extern FUNC(void, OS_TASK50MS_CORE0_CODE) Os_Task_Task50ms_Core0(void);

# define OS_STOP_SEC_Task50ms_Core0_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


# define OS_START_SEC_Task50ms_Core1_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  Task50ms_Core1()
 *********************************************************************************************************************/
extern FUNC(void, OS_TASK50MS_CORE1_CODE) Os_Task_Task50ms_Core1(void);

# define OS_STOP_SEC_Task50ms_Core1_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


# define OS_START_SEC_Task50ms_Core2_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  Task50ms_Core2()
 *********************************************************************************************************************/
extern FUNC(void, OS_TASK50MS_CORE2_CODE) Os_Task_Task50ms_Core2(void);

# define OS_STOP_SEC_Task50ms_Core2_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


# define OS_START_SEC_Task5ms_Core0_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  Task5ms_Core0()
 *********************************************************************************************************************/
extern FUNC(void, OS_TASK5MS_CORE0_CODE) Os_Task_Task5ms_Core0(void);

# define OS_STOP_SEC_Task5ms_Core0_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


# define OS_START_SEC_Task5ms_Core1_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  Task5ms_Core1()
 *********************************************************************************************************************/
extern FUNC(void, OS_TASK5MS_CORE1_CODE) Os_Task_Task5ms_Core1(void);

# define OS_STOP_SEC_Task5ms_Core1_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


# define OS_START_SEC_Task5ms_Core2_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  Task5ms_Core2()
 *********************************************************************************************************************/
extern FUNC(void, OS_TASK5MS_CORE2_CODE) Os_Task_Task5ms_Core2(void);

# define OS_STOP_SEC_Task5ms_Core2_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


# define OS_START_SEC_TaskInit_Core0_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  TaskInit_Core0()
 *********************************************************************************************************************/
extern FUNC(void, OS_TASKINIT_CORE0_CODE) Os_Task_TaskInit_Core0(void);

# define OS_STOP_SEC_TaskInit_Core0_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


# define OS_START_SEC_TaskInit_Core1_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  TaskInit_Core1()
 *********************************************************************************************************************/
extern FUNC(void, OS_TASKINIT_CORE1_CODE) Os_Task_TaskInit_Core1(void);

# define OS_STOP_SEC_TaskInit_Core1_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


# define OS_START_SEC_TaskInit_Core2_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  TaskInit_Core2()
 *********************************************************************************************************************/
extern FUNC(void, OS_TASKINIT_CORE2_CODE) Os_Task_TaskInit_Core2(void);

# define OS_STOP_SEC_TaskInit_Core2_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


# define OS_START_SEC_TaskSchM_Core0_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  TaskSchM_Core0()
 *********************************************************************************************************************/
extern FUNC(void, OS_TASKSCHM_CORE0_CODE) Os_Task_TaskSchM_Core0(void);

# define OS_STOP_SEC_TaskSchM_Core0_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


# define OS_START_SEC_TaskSchM_Core1_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  TaskSchM_Core1()
 *********************************************************************************************************************/
extern FUNC(void, OS_TASKSCHM_CORE1_CODE) Os_Task_TaskSchM_Core1(void);

# define OS_STOP_SEC_TaskSchM_Core1_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


# define OS_START_SEC_TaskSchM_Core2_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  TaskSchM_Core2()
 *********************************************************************************************************************/
extern FUNC(void, OS_TASKSCHM_CORE2_CODE) Os_Task_TaskSchM_Core2(void);

# define OS_STOP_SEC_TaskSchM_Core2_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


# define OS_START_SEC_Adc0Sr0_Isr_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  Adc0Sr0_Isr()
 *********************************************************************************************************************/
extern FUNC(void, OS_ADC0SR0_ISR_CODE) Os_Isr_Adc0Sr0_Isr(void);

# define OS_STOP_SEC_Adc0Sr0_Isr_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


# define OS_START_SEC_Adc1Sr0_Isr_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  Adc1Sr0_Isr()
 *********************************************************************************************************************/
extern FUNC(void, OS_ADC1SR0_ISR_CODE) Os_Isr_Adc1Sr0_Isr(void);

# define OS_STOP_SEC_Adc1Sr0_Isr_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


# define OS_START_SEC_Adc2Sr0_Isr_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  Adc2Sr0_Isr()
 *********************************************************************************************************************/
extern FUNC(void, OS_ADC2SR0_ISR_CODE) Os_Isr_Adc2Sr0_Isr(void);

# define OS_STOP_SEC_Adc2Sr0_Isr_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


# define OS_START_SEC_Adc3Sr0_Isr_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  Adc3Sr0_Isr()
 *********************************************************************************************************************/
extern FUNC(void, OS_ADC3SR0_ISR_CODE) Os_Isr_Adc3Sr0_Isr(void);

# define OS_STOP_SEC_Adc3Sr0_Isr_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


# define OS_START_SEC_Adc4Sr0_Isr_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  Adc4Sr0_Isr()
 *********************************************************************************************************************/
extern FUNC(void, OS_ADC4SR0_ISR_CODE) Os_Isr_Adc4Sr0_Isr(void);

# define OS_STOP_SEC_Adc4Sr0_Isr_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


# define OS_START_SEC_Adc5Sr0_Isr_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  Adc5Sr0_Isr()
 *********************************************************************************************************************/
extern FUNC(void, OS_ADC5SR0_ISR_CODE) Os_Isr_Adc5Sr0_Isr(void);

# define OS_STOP_SEC_Adc5Sr0_Isr_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


# define OS_START_SEC_Adc6Sr0_Isr_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  Adc6Sr0_Isr()
 *********************************************************************************************************************/
extern FUNC(void, OS_ADC6SR0_ISR_CODE) Os_Isr_Adc6Sr0_Isr(void);

# define OS_STOP_SEC_Adc6Sr0_Isr_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


# define OS_START_SEC_CanIsr_0_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  CanIsr_0()
 *********************************************************************************************************************/
extern FUNC(void, OS_CANISR_0_CODE) Os_Isr_CanIsr_0(void);

# define OS_STOP_SEC_CanIsr_0_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


# define OS_START_SEC_Isr_TIM02_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  Isr_TIM02()
 *********************************************************************************************************************/
extern FUNC(void, OS_ISR_TIM02_CODE) Os_Isr_Isr_TIM02(void);

# define OS_STOP_SEC_Isr_TIM02_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


# define OS_START_SEC_Isr_TIM03_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  Isr_TIM03()
 *********************************************************************************************************************/
extern FUNC(void, OS_ISR_TIM03_CODE) Os_Isr_Isr_TIM03(void);

# define OS_STOP_SEC_Isr_TIM03_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#endif /* OS_LCFG_H */

/**********************************************************************************************************************
 *  END OF FILE: Os_Lcfg.h
 *********************************************************************************************************************/
