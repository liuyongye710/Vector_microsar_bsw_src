/*
********************************************************************************
*
*  File name:	Os_Types_Cfg.h
*
*  Copyright	Neusoft Reach Corporation. All rights reserved.
*
********************************************************************************
*
* History
*-------------------------------------------------------------------------------
********************************************************************************
* Version: 3.0
* Author/Date : HanCL/2021.11.23
* Change: New create.
* Cause: New
********************************************************************************
*/
#ifndef OS_TYPES_CFG_H_
#define OS_TYPES_CFG_H_

/*
********************************************************************************
*    Includes
********************************************************************************
*/
#include "Std_Types.h"

/*
********************************************************************************
*    Global Macros
********************************************************************************
*/
#define OS_MAX_INTCNTS OS_ISRID_COUNT
#define OS_CFG_COREPHYSICALID_COUNT                   (3U)
/*
********************************************************************************
*    Global Types
********************************************************************************
*/
/* OS-Application identifiers. */
typedef enum
{
    SYSTEMAPPLICATION_OSCORE_CORE0 = 0U,
    APP_APPLICATION_CORE0_QM = 1U,
    SYSTEMAPPLICATION_OSCORE_CORE1 = 2U,
    APP_APPLICATION_CORE1_QM = 3U,
    SYSTEMAPPLICATION_OSCORE_CORE2 = 4U,
    APP_APPLICATION_CORE2_QM = 5U,
    OS_APPID_COUNT  = 6U,
    INVALID_OSAPPLICATION = OS_APPID_COUNT
} ApplicationType;

/* Trusted function identifiers. */
typedef enum
{
    OS_TRUSTEDFUNCTIONID_COUNT = 0U
} TrustedFunctionIndexType;

/* Task identifiers. */
typedef enum
{
    DEFAULT_INIT_TASK_CORE0 = 0U,
    IDLE_TASK_CORE0 = 1U,
    TASK_INIT_CORE0_QM = 2U,
    TASK_10MS_CORE0_QM = 3U,
    TASK_20MS_CORE0_QM = 4U,
    TASK_50MS_CORE0_QM = 5U,
    TASK_100MS_CORE0_QM = 6U,
    TASK_200MS_CORE0_QM = 7U,
    TASK_500MS_CORE0_QM = 8U,
    TASK_1000MS_CORE0_QM = 9U,
    TASK_2MS_CORE0_QM = 10U,
    DEFAULT_INIT_TASK_CORE1 = 11U,
    IDLE_TASK_CORE1 = 12U,
    TASK_INIT_CORE1_QM = 13U,
    TASK_5MS_CORE1_QM = 14U,
    TASK_10MS_CORE1_QM = 15U,
    TASK_20MS_CORE1_QM = 16U,
    TASK_50MS_CORE1_QM = 17U,
    TASK_100MS_CORE1_QM = 18U,
    TASK_200MS_CORE1_QM = 19U,
    TASK_500MS_CORE1_QM = 20U,
    TASK_1000MS_CORE1_QM = 21U,
    DEFAULT_INIT_TASK_CORE2 = 22U,
    IDLE_TASK_CORE2 = 23U,
    TASK_INIT_CORE2_QM = 24U,
    TASK_1MS_CORE2_QM = 25U,
    TASK_4MS_CORE2_QM = 26U,
    TASK_5MS_CORE2_QM = 27U,
    TASK_10MS_CORE2_QM = 28U,
    TASK_20MS_CORE2_QM = 29U,
    TASK_50MS_CORE2_QM = 30U,
    TASK_100MS_CORE2_QM = 31U,
    TASK_200MS_CORE2_QM = 32U,
    TASK_500MS_CORE2_QM = 33U,
    TASK_1000MS_CORE2_QM = 34U,
    OS_TASKID_COUNT = 35U,
    INVALID_TASK = OS_TASKID_COUNT
} TaskType;

/* Category 2 ISR identifiers. */
typedef enum
{
    COUNTERISR_SYSTEMTIMER_CORE0 = 0U,
    MULTICOMMISR_OSCORE_CORE0 = 1U,
    OS_MONITOR_ISR = 2U,
    COUNTERISR_SYSTEMTIMER_CORE1 = 3U,
    MULTICOMMISR_OSCORE_CORE1 = 4U,
    COUNTERISR_SYSTEMTIMER_CORE2 = 5U,
    MULTICOMMISR_OSCORE_CORE2 = 6U,
    FLASHDONE_ISR = 7U,
    PIT0_CH4 = 8U,
    PIT0_CH5 = 9U,
    PIT0_CH6 = 10U,
    CAN1_ISR = 11U,
    CAN2_ISR = 12U,
    CAN3_ISR = 13U,
    CAN4_ISR = 14U,
    ADC89_GRP0_ISR = 15U,
    ADC89_GRP1_ISR = 16U,
    ADC89_GRP2_ISR = 17U,
    ADC89_GRP3_ISR = 18U,
    ADC89_GRP4_ISR = 19U,
    ADC89_GRP5_ISR = 20U,
    OS_ISRID_COUNT = 21U,
    INVALID_ISR = OS_ISRID_COUNT
} ISRType;

/* Alarm identifiers. */
typedef enum
{
    RTE_AL_TE_TASK_10MS_CORE0_QM_10MS = 0U,
    RTE_AL_TE_TASK_20MS_CORE0_QM_20MS = 1U,
    RTE_AL_TE_TASK_50MS_CORE0_QM_50MS = 2U,
    RTE_AL_TE_TASK_100MS_CORE0_QM_100MS = 3U,
    RTE_AL_TE_TASK_200MS_CORE0_QM_200MS = 4U,
    RTE_AL_TE_TASK_500MS_CORE0_QM_500MS = 5U,
    RTE_AL_TE_TASK_1000MS_CORE0_QM_1000MS = 6U,
    RTE_AL_TE_TASK_2MS_CORE0_QM_2MS = 7U,
    RTE_AL_TE_TASK_5MS_CORE1_QM_5MS = 8U,
    RTE_AL_TE_TASK_10MS_CORE1_QM_10MS = 9U,
    RTE_AL_TE_TASK_20MS_CORE1_QM_20MS = 10U,
    RTE_AL_TE_TASK_50MS_CORE1_QM_50MS = 11U,
    RTE_AL_TE_TASK_100MS_CORE1_QM_100MS = 12U,
    RTE_AL_TE_TASK_200MS_CORE1_QM_200MS = 13U,
    RTE_AL_TE_TASK_500MS_CORE1_QM_500MS = 14U,
    RTE_AL_TE_TASK_1000MS_CORE1_QM_1000MS = 15U,
    RTE_AL_TE_TASK_1MS_CORE2_QM_1MS = 16U,
    RTE_AL_TE_TASK_5MS_CORE2_QM_5MS = 17U,
    RTE_AL_TE_TASK_10MS_CORE2_QM_10MS = 18U,
    RTE_AL_TE_TASK_20MS_CORE2_QM_20MS = 19U,
    RTE_AL_TE_TASK_50MS_CORE2_QM_50MS = 20U,
    RTE_AL_TE_TASK_100MS_CORE2_QM_100MS = 21U,
    RTE_AL_TE_TASK_200MS_CORE2_QM_200MS = 22U,
    RTE_AL_TE_TASK_500MS_CORE2_QM_500MS = 23U,
    RTE_AL_TE_TASK_1000MS_CORE2_QM_1000MS = 24U,
    RTE_AL_TE_TASK_4MS_CORE2_QM_4MS = 25U,
    OS_ALARMID_COUNT = 26U
} AlarmType;

/* Counter identifiers. */
typedef enum
{
    SYSTEMTIMER_CORE0 = 0U,
    OS_MONITOR_COUNTER = 1U,
    SYSTEMTIMER_CORE1 = 2U,
    SYSTEMTIMER_CORE2 = 3U,
    OS_COUNTERID_COUNT = 4U,
    INVALID_COUNTER = OS_COUNTERID_COUNT
} CounterType;

/* ScheduleTable identifiers. */
typedef enum
{
    OS_SCHTID_COUNT = 0U
} ScheduleTableType;

/* Resource identifiers. */
typedef enum
{
    CORE0_TASK_OSRESOURCE0 = 0U,
    CORE1_TASK_OSRESOURCE1 = 1U,
    CORE2_TASK_OSRESOURCE2 = 2U,
    OS_RESOURCEID_COUNT = 3U
} ResourceType;

/* Spinlock identifiers. */
typedef enum
{
    OS_SPINLOCKID_COUNT = 0U,
    INVALID_SPINLOCK = OS_SPINLOCKID_COUNT
} SpinlockIdType;

typedef enum
{
    OS_CORE_ID_0 = 0U,
    OS_CORE_ID_1 = 1U,
    OS_CORE_ID_2 = 2U,
    OS_CORE_ID_MASTER = 2U,
    OS_COREID_COUNT = 3U,
    INVALID_CORE = OS_COREID_COUNT
} CoreIdType;

/*
********************************************************************************
*    Global Variables
********************************************************************************
*/
/*
********************************************************************************
*    Global Constants
********************************************************************************
*/
/*
********************************************************************************
*    Global Functions
********************************************************************************
*/

#endif /* OS_TYPES_CFG_H_ */


