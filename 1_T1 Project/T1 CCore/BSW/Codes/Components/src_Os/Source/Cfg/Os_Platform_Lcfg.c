/*
********************************************************************************
*
*  File name:	Os_Platform_Lcfg.c
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
/*
********************************************************************************
*    Includes
********************************************************************************
*/
#include "Std_Types.h"
#include "Os_Types_Cfg.h"
#include "Os_Platform_Lcfg.h"
#include "Os_Core_Types.h"
#include "Os_TaskQueue.h"
#include "Os_Tp_Lcfg.h"
#include "Os_MemProtection_Types.h"
#include "Os_SchdTb_Types.h"
#include "Os_Lcfg.h"
#include "Os_SchdTb_Lcfg.h"
#include "Os_Mp_Lcfg.h"

/*
********************************************************************************
*    Local Macros
********************************************************************************
*/
/*
********************************************************************************
*    Local Types
********************************************************************************
*/
/*
********************************************************************************
*    Local Variables
********************************************************************************
*/
/*
********************************************************************************
*    Local Functions
********************************************************************************
*/
#define OS_START_SEC_VAR_OSCORE0 
#include "Os_MemMap.h"
/* Core dynamic parameters start. */
static Os_CoreDynType OsCfg_Core_OsCore0_Dyn;

static Os_CoreIntStateType OsCfg_IntState_OsCore0_Dyn;

/* Core dynamic parameters end. */ 

/* App dynamic parameters start. */
static Os_AppDynType OsCfg_Appl_SystemApplication_OsCore_Core0_Dyn;
static Os_AppDynType OsCfg_Appl_App_Application_Core0_QM_Dyn;

/* App dynamic parameters end. */

/* Task dynamic parameters start. */
static Os_TaskDynType OsCfg_Task_Default_Init_Task_Core0_Dyn;
static Os_TaskDynType OsCfg_Task_Idle_Task_Core0_Dyn;
static Os_TaskDynType OsCfg_Task_Task_Init_Core0_QM_Dyn;
static Os_TaskDynType OsCfg_Task_Task_10ms_Core0_QM_Dyn;
static Os_TaskDynType OsCfg_Task_Task_20ms_Core0_QM_Dyn;
static Os_TaskDynType OsCfg_Task_Task_50ms_Core0_QM_Dyn;
static Os_TaskDynType OsCfg_Task_Task_100ms_Core0_QM_Dyn;
static Os_TaskDynType OsCfg_Task_Task_200ms_Core0_QM_Dyn;
static Os_TaskDynType OsCfg_Task_Task_500ms_Core0_QM_Dyn;
static Os_TaskDynType OsCfg_Task_Task_1000ms_Core0_QM_Dyn;
static Os_TaskDynType OsCfg_Task_Task_2ms_Core0_QM_Dyn;

/* Task dynamic parameters end. */

/* Isr dynamic parameters start. */
static Os_IsrDynType OsCfg_Isr_CounterIsr_SystemTimer_Core0_Dyn;
static Os_IsrDynType OsCfg_Isr_MultiCommIsr_OsCore_Core0_Dyn;
static Os_IsrDynType OsCfg_Isr_Os_Monitor_Isr_Dyn;

/* Isr dynamic parameters end. */

/* Counter dynamic parameters start. */
static Os_CounterSwDynType OsCfg_Counter_SystemTimer_Core0_Dyn;
static Os_CounterSwDynType OsCfg_Counter_Os_Monitor_Counter_Dyn;

/* Counter dynamic parameters end. */

/* Alarm dynamic parameters start. */
static Os_AlarmDynType OsCfg_Alarm_Rte_Al_TE_Task_10ms_Core0_QM_10ms_Dyn;
static Os_AlarmDynType OsCfg_Alarm_Rte_Al_TE_Task_20ms_Core0_QM_20ms_Dyn;
static Os_AlarmDynType OsCfg_Alarm_Rte_Al_TE_Task_50ms_Core0_QM_50ms_Dyn;
static Os_AlarmDynType OsCfg_Alarm_Rte_Al_TE_Task_100ms_Core0_QM_100ms_Dyn;
static Os_AlarmDynType OsCfg_Alarm_Rte_Al_TE_Task_200ms_Core0_QM_200ms_Dyn;
static Os_AlarmDynType OsCfg_Alarm_Rte_Al_TE_Task_500ms_Core0_QM_500ms_Dyn;
static Os_AlarmDynType OsCfg_Alarm_Rte_Al_TE_Task_1000ms_Core0_QM_1000ms_Dyn;
static Os_AlarmDynType OsCfg_Alarm_Rte_Al_TE_Task_2ms_Core0_QM_2ms_Dyn;

/* Alarm dynamic parameters end. */

/* Resource dynamic parameters start. */
static Os_ResourceDynType Os_Resource_Core0_Task_OsResource0_Dyn;
/* Resource dynamic parameters end. */

/* Scheduler dynamic parameters start. */
static Os_BitMapDynType OsCfg_Scheduler_BitMap_OsCore0_Dyn;
static Os_SchedulerDynType OsCfg_Scheduler_OsCore0_Dyn;
static Os_BitMapDataType OsCfg_BitMap_L1Data_OsCore0_Dyn[OS_BITMAP_LENGTH(OS_CFG_NUM_TASKQUEUES_OSCORE0)];

Os_TaskDynType* OsCfg_TaskQueueNodes0_Data_OsCore0[OS_CFG_SIZE_TASKQUEUE0_OSCORE0];
Os_TaskDynType* OsCfg_TaskQueueNodes1_Data_OsCore0[OS_CFG_SIZE_TASKQUEUE1_OSCORE0];
Os_TaskDynType* OsCfg_TaskQueueNodes2_Data_OsCore0[OS_CFG_SIZE_TASKQUEUE2_OSCORE0];
Os_TaskDynType* OsCfg_TaskQueueNodes3_Data_OsCore0[OS_CFG_SIZE_TASKQUEUE3_OSCORE0];
Os_TaskDynType* OsCfg_TaskQueueNodes4_Data_OsCore0[OS_CFG_SIZE_TASKQUEUE4_OSCORE0];
Os_TaskDynType* OsCfg_TaskQueueNodes5_Data_OsCore0[OS_CFG_SIZE_TASKQUEUE5_OSCORE0];
Os_TaskDynType* OsCfg_TaskQueueNodes6_Data_OsCore0[OS_CFG_SIZE_TASKQUEUE6_OSCORE0];
Os_TaskDynType* OsCfg_TaskQueueNodes7_Data_OsCore0[OS_CFG_SIZE_TASKQUEUE7_OSCORE0];
Os_TaskDynType* OsCfg_TaskQueueNodes8_Data_OsCore0[OS_CFG_SIZE_TASKQUEUE8_OSCORE0];
Os_TaskDynType* OsCfg_TaskQueueNodes9_Data_OsCore0[OS_CFG_SIZE_TASKQUEUE9_OSCORE0];
Os_TaskDynType* OsCfg_TaskQueueNodes10_Data_OsCore0[OS_CFG_SIZE_TASKQUEUE10_OSCORE0];

Os_TaskQueType OsCfg_TaskQueueNodes0_OsCore0;
Os_TaskQueType OsCfg_TaskQueueNodes1_OsCore0;
Os_TaskQueType OsCfg_TaskQueueNodes2_OsCore0;
Os_TaskQueType OsCfg_TaskQueueNodes3_OsCore0;
Os_TaskQueType OsCfg_TaskQueueNodes4_OsCore0;
Os_TaskQueType OsCfg_TaskQueueNodes5_OsCore0;
Os_TaskQueType OsCfg_TaskQueueNodes6_OsCore0;
Os_TaskQueType OsCfg_TaskQueueNodes7_OsCore0;
Os_TaskQueType OsCfg_TaskQueueNodes8_OsCore0;
Os_TaskQueType OsCfg_TaskQueueNodes9_OsCore0;
Os_TaskQueType OsCfg_TaskQueueNodes10_OsCore0;

static Os_PriQueueNodeType* Os_PriQueueNode_SystemTimer_Core0_0[OS_CFG_NUM_TASKQUEUES_SYSTEMTIMER_CORE0 + 1];
static Os_PriQueueNodeType* Os_PriQueueNode_SystemTimer_Core0_1[OS_CFG_NUM_TASKQUEUES_SYSTEMTIMER_CORE0 + 1];

/* Scheduler dynamic parameters end. */

#define OS_STOP_SEC_VAR_OSCORE0 
#include "Os_MemMap.h"

#define OS_START_SEC_INITVAR_OSCORE0 
#include "Os_MemMap.h"
/* Scheduler init dynamic parameters start. */
Os_TaskQueType* OsCfg_Scheduler_OsCore0_TaskQueues[OS_CFG_NUM_TASKQUEUES_OSCORE0] =
{
    &OsCfg_TaskQueueNodes0_OsCore0,
    &OsCfg_TaskQueueNodes1_OsCore0,
    &OsCfg_TaskQueueNodes2_OsCore0,
    &OsCfg_TaskQueueNodes3_OsCore0,
    &OsCfg_TaskQueueNodes4_OsCore0,
    &OsCfg_TaskQueueNodes5_OsCore0,
    &OsCfg_TaskQueueNodes6_OsCore0,
    &OsCfg_TaskQueueNodes7_OsCore0,
    &OsCfg_TaskQueueNodes8_OsCore0,
    &OsCfg_TaskQueueNodes9_OsCore0,
    &OsCfg_TaskQueueNodes10_OsCore0
};


Os_CntExpListCfgType Os_CntExpList_SystemTimer_Core0 =
{
    {
        {
            /* cntExpList[0]->priQueueNode       = */ Os_PriQueueNode_SystemTimer_Core0_0,
            /* cntExpList[0]->priQueueUseCounter = */ 0U,
            /* cntExpList[0]->priQueueSize       = */ OS_CFG_NUM_TASKQUEUES_SYSTEMTIMER_CORE0
        },
        {
            /* cntExpList[1]->priQueueNode       = */ Os_PriQueueNode_SystemTimer_Core0_1,
            /* cntExpList[1]->priQueueUseCounter = */ 0U,
            /* cntExpList[1]->priQueueSize       = */ OS_CFG_NUM_TASKQUEUES_SYSTEMTIMER_CORE0
        }
    },
    /* cntExplistMux = */ 0U
};
/* Scheduler init dynamic parameters end. */

#define OS_STOP_SEC_INITVAR_OSCORE0 
#include "Os_MemMap.h"

#define OS_START_SEC_VAR_OSCORE1 
#include "Os_MemMap.h"
/* Core dynamic parameters start. */
static Os_CoreDynType OsCfg_Core_OsCore1_Dyn;

static Os_CoreIntStateType OsCfg_IntState_OsCore1_Dyn;

/* Core dynamic parameters end. */ 

/* App dynamic parameters start. */
static Os_AppDynType OsCfg_Appl_SystemApplication_OsCore_Core1_Dyn;
static Os_AppDynType OsCfg_Appl_App_Application_Core1_QM_Dyn;

/* App dynamic parameters end. */

/* Task dynamic parameters start. */
static Os_TaskDynType OsCfg_Task_Default_Init_Task_Core1_Dyn;
static Os_TaskDynType OsCfg_Task_Idle_Task_Core1_Dyn;
static Os_TaskDynType OsCfg_Task_Task_Init_Core1_QM_Dyn;
static Os_TaskDynType OsCfg_Task_Task_5ms_Core1_QM_Dyn;
static Os_TaskDynType OsCfg_Task_Task_10ms_Core1_QM_Dyn;
static Os_TaskDynType OsCfg_Task_Task_20ms_Core1_QM_Dyn;
static Os_TaskDynType OsCfg_Task_Task_50ms_Core1_QM_Dyn;
static Os_TaskDynType OsCfg_Task_Task_100ms_Core1_QM_Dyn;
static Os_TaskDynType OsCfg_Task_Task_200ms_Core1_QM_Dyn;
static Os_TaskDynType OsCfg_Task_Task_500ms_Core1_QM_Dyn;
static Os_TaskDynType OsCfg_Task_Task_1000ms_Core1_QM_Dyn;

/* Task dynamic parameters end. */

/* Isr dynamic parameters start. */
static Os_IsrDynType OsCfg_Isr_CounterIsr_SystemTimer_Core1_Dyn;
static Os_IsrDynType OsCfg_Isr_MultiCommIsr_OsCore_Core1_Dyn;

/* Isr dynamic parameters end. */

/* Counter dynamic parameters start. */
static Os_CounterSwDynType OsCfg_Counter_SystemTimer_Core1_Dyn;

/* Counter dynamic parameters end. */

/* Alarm dynamic parameters start. */
static Os_AlarmDynType OsCfg_Alarm_Rte_Al_TE_Task_5ms_Core1_QM_5ms_Dyn;
static Os_AlarmDynType OsCfg_Alarm_Rte_Al_TE_Task_10ms_Core1_QM_10ms_Dyn;
static Os_AlarmDynType OsCfg_Alarm_Rte_Al_TE_Task_20ms_Core1_QM_20ms_Dyn;
static Os_AlarmDynType OsCfg_Alarm_Rte_Al_TE_Task_50ms_Core1_QM_50ms_Dyn;
static Os_AlarmDynType OsCfg_Alarm_Rte_Al_TE_Task_100ms_Core1_QM_100ms_Dyn;
static Os_AlarmDynType OsCfg_Alarm_Rte_Al_TE_Task_200ms_Core1_QM_200ms_Dyn;
static Os_AlarmDynType OsCfg_Alarm_Rte_Al_TE_Task_500ms_Core1_QM_500ms_Dyn;
static Os_AlarmDynType OsCfg_Alarm_Rte_Al_TE_Task_1000ms_Core1_QM_1000ms_Dyn;

/* Alarm dynamic parameters end. */

/* Resource dynamic parameters start. */
static Os_ResourceDynType Os_Resource_Core1_Task_OsResource1_Dyn;
/* Resource dynamic parameters end. */

/* Scheduler dynamic parameters start. */
static Os_BitMapDynType OsCfg_Scheduler_BitMap_OsCore1_Dyn;
static Os_SchedulerDynType OsCfg_Scheduler_OsCore1_Dyn;
static Os_BitMapDataType OsCfg_BitMap_L1Data_OsCore1_Dyn[OS_BITMAP_LENGTH(OS_CFG_NUM_TASKQUEUES_OSCORE1)];

Os_TaskDynType* OsCfg_TaskQueueNodes0_Data_OsCore1[OS_CFG_SIZE_TASKQUEUE0_OSCORE1];
Os_TaskDynType* OsCfg_TaskQueueNodes1_Data_OsCore1[OS_CFG_SIZE_TASKQUEUE1_OSCORE1];
Os_TaskDynType* OsCfg_TaskQueueNodes2_Data_OsCore1[OS_CFG_SIZE_TASKQUEUE2_OSCORE1];
Os_TaskDynType* OsCfg_TaskQueueNodes3_Data_OsCore1[OS_CFG_SIZE_TASKQUEUE3_OSCORE1];
Os_TaskDynType* OsCfg_TaskQueueNodes4_Data_OsCore1[OS_CFG_SIZE_TASKQUEUE4_OSCORE1];
Os_TaskDynType* OsCfg_TaskQueueNodes5_Data_OsCore1[OS_CFG_SIZE_TASKQUEUE5_OSCORE1];
Os_TaskDynType* OsCfg_TaskQueueNodes6_Data_OsCore1[OS_CFG_SIZE_TASKQUEUE6_OSCORE1];
Os_TaskDynType* OsCfg_TaskQueueNodes7_Data_OsCore1[OS_CFG_SIZE_TASKQUEUE7_OSCORE1];
Os_TaskDynType* OsCfg_TaskQueueNodes8_Data_OsCore1[OS_CFG_SIZE_TASKQUEUE8_OSCORE1];
Os_TaskDynType* OsCfg_TaskQueueNodes9_Data_OsCore1[OS_CFG_SIZE_TASKQUEUE9_OSCORE1];
Os_TaskDynType* OsCfg_TaskQueueNodes10_Data_OsCore1[OS_CFG_SIZE_TASKQUEUE10_OSCORE1];

Os_TaskQueType OsCfg_TaskQueueNodes0_OsCore1;
Os_TaskQueType OsCfg_TaskQueueNodes1_OsCore1;
Os_TaskQueType OsCfg_TaskQueueNodes2_OsCore1;
Os_TaskQueType OsCfg_TaskQueueNodes3_OsCore1;
Os_TaskQueType OsCfg_TaskQueueNodes4_OsCore1;
Os_TaskQueType OsCfg_TaskQueueNodes5_OsCore1;
Os_TaskQueType OsCfg_TaskQueueNodes6_OsCore1;
Os_TaskQueType OsCfg_TaskQueueNodes7_OsCore1;
Os_TaskQueType OsCfg_TaskQueueNodes8_OsCore1;
Os_TaskQueType OsCfg_TaskQueueNodes9_OsCore1;
Os_TaskQueType OsCfg_TaskQueueNodes10_OsCore1;

static Os_PriQueueNodeType* Os_PriQueueNode_SystemTimer_Core1_0[OS_CFG_NUM_TASKQUEUES_SYSTEMTIMER_CORE1 + 1];
static Os_PriQueueNodeType* Os_PriQueueNode_SystemTimer_Core1_1[OS_CFG_NUM_TASKQUEUES_SYSTEMTIMER_CORE1 + 1];

/* Scheduler dynamic parameters end. */

#define OS_STOP_SEC_VAR_OSCORE1 
#include "Os_MemMap.h"

#define OS_START_SEC_INITVAR_OSCORE1 
#include "Os_MemMap.h"
/* Scheduler init dynamic parameters start. */
Os_TaskQueType* OsCfg_Scheduler_OsCore1_TaskQueues[OS_CFG_NUM_TASKQUEUES_OSCORE1] =
{
    &OsCfg_TaskQueueNodes0_OsCore1,
    &OsCfg_TaskQueueNodes1_OsCore1,
    &OsCfg_TaskQueueNodes2_OsCore1,
    &OsCfg_TaskQueueNodes3_OsCore1,
    &OsCfg_TaskQueueNodes4_OsCore1,
    &OsCfg_TaskQueueNodes5_OsCore1,
    &OsCfg_TaskQueueNodes6_OsCore1,
    &OsCfg_TaskQueueNodes7_OsCore1,
    &OsCfg_TaskQueueNodes8_OsCore1,
    &OsCfg_TaskQueueNodes9_OsCore1,
    &OsCfg_TaskQueueNodes10_OsCore1
};


Os_CntExpListCfgType Os_CntExpList_SystemTimer_Core1 =
{
    {
        {
            /* cntExpList[0]->priQueueNode       = */ Os_PriQueueNode_SystemTimer_Core1_0,
            /* cntExpList[0]->priQueueUseCounter = */ 0U,
            /* cntExpList[0]->priQueueSize       = */ OS_CFG_NUM_TASKQUEUES_SYSTEMTIMER_CORE1
        },
        {
            /* cntExpList[1]->priQueueNode       = */ Os_PriQueueNode_SystemTimer_Core1_1,
            /* cntExpList[1]->priQueueUseCounter = */ 0U,
            /* cntExpList[1]->priQueueSize       = */ OS_CFG_NUM_TASKQUEUES_SYSTEMTIMER_CORE1
        }
    },
    /* cntExplistMux = */ 0U
};
/* Scheduler init dynamic parameters end. */

#define OS_STOP_SEC_INITVAR_OSCORE1 
#include "Os_MemMap.h"

#define OS_START_SEC_VAR_OSCORE2 
#include "Os_MemMap.h"
/* Core dynamic parameters start. */
static Os_CoreDynType OsCfg_Core_OsCore2_Dyn;

static Os_CoreIntStateType OsCfg_IntState_OsCore2_Dyn;

/* Core dynamic parameters end. */ 

/* App dynamic parameters start. */
static Os_AppDynType OsCfg_Appl_SystemApplication_OsCore_Core2_Dyn;
static Os_AppDynType OsCfg_Appl_App_Application_Core2_QM_Dyn;

/* App dynamic parameters end. */

/* Task dynamic parameters start. */
static Os_TaskDynType OsCfg_Task_Default_Init_Task_Core2_Dyn;
static Os_TaskDynType OsCfg_Task_Idle_Task_Core2_Dyn;
static Os_TaskDynType OsCfg_Task_Task_Init_Core2_QM_Dyn;
static Os_TaskDynType OsCfg_Task_Task_1ms_Core2_QM_Dyn;
static Os_TaskDynType OsCfg_Task_Task_4ms_Core2_QM_Dyn;
static Os_TaskDynType OsCfg_Task_Task_5ms_Core2_QM_Dyn;
static Os_TaskDynType OsCfg_Task_Task_10ms_Core2_QM_Dyn;
static Os_TaskDynType OsCfg_Task_Task_20ms_Core2_QM_Dyn;
static Os_TaskDynType OsCfg_Task_Task_50ms_Core2_QM_Dyn;
static Os_TaskDynType OsCfg_Task_Task_100ms_Core2_QM_Dyn;
static Os_TaskDynType OsCfg_Task_Task_200ms_Core2_QM_Dyn;
static Os_TaskDynType OsCfg_Task_Task_500ms_Core2_QM_Dyn;
static Os_TaskDynType OsCfg_Task_Task_1000ms_Core2_QM_Dyn;

/* Task dynamic parameters end. */

/* Isr dynamic parameters start. */
static Os_IsrDynType OsCfg_Isr_CounterIsr_SystemTimer_Core2_Dyn;
static Os_IsrDynType OsCfg_Isr_MultiCommIsr_OsCore_Core2_Dyn;
static Os_IsrDynType OsCfg_Isr_FlashDone_Isr_Dyn;
static Os_IsrDynType OsCfg_Isr_PIT0_CH4_Dyn;
static Os_IsrDynType OsCfg_Isr_PIT0_CH5_Dyn;
static Os_IsrDynType OsCfg_Isr_PIT0_CH6_Dyn;
static Os_IsrDynType OsCfg_Isr_Can1_Isr_Dyn;
static Os_IsrDynType OsCfg_Isr_Can2_Isr_Dyn;
static Os_IsrDynType OsCfg_Isr_Can3_Isr_Dyn;
static Os_IsrDynType OsCfg_Isr_Can4_Isr_Dyn;
static Os_IsrDynType OsCfg_Isr_Adc89_Grp0_Isr_Dyn;
static Os_IsrDynType OsCfg_Isr_Adc89_Grp1_Isr_Dyn;
static Os_IsrDynType OsCfg_Isr_Adc89_Grp2_Isr_Dyn;
static Os_IsrDynType OsCfg_Isr_Adc89_Grp3_Isr_Dyn;
static Os_IsrDynType OsCfg_Isr_Adc89_Grp4_Isr_Dyn;
static Os_IsrDynType OsCfg_Isr_Adc89_Grp5_Isr_Dyn;

/* Isr dynamic parameters end. */

/* Counter dynamic parameters start. */
static Os_CounterSwDynType OsCfg_Counter_SystemTimer_Core2_Dyn;

/* Counter dynamic parameters end. */

/* Alarm dynamic parameters start. */
static Os_AlarmDynType OsCfg_Alarm_Rte_Al_TE_Task_1ms_Core2_QM_1ms_Dyn;
static Os_AlarmDynType OsCfg_Alarm_Rte_Al_TE_Task_5ms_Core2_QM_5ms_Dyn;
static Os_AlarmDynType OsCfg_Alarm_Rte_Al_TE_Task_10ms_Core2_QM_10ms_Dyn;
static Os_AlarmDynType OsCfg_Alarm_Rte_Al_TE_Task_20ms_Core2_QM_20ms_Dyn;
static Os_AlarmDynType OsCfg_Alarm_Rte_Al_TE_Task_50ms_Core2_QM_50ms_Dyn;
static Os_AlarmDynType OsCfg_Alarm_Rte_Al_TE_Task_100ms_Core2_QM_100ms_Dyn;
static Os_AlarmDynType OsCfg_Alarm_Rte_Al_TE_Task_200ms_Core2_QM_200ms_Dyn;
static Os_AlarmDynType OsCfg_Alarm_Rte_Al_TE_Task_500ms_Core2_QM_500ms_Dyn;
static Os_AlarmDynType OsCfg_Alarm_Rte_Al_TE_Task_1000ms_Core2_QM_1000ms_Dyn;
static Os_AlarmDynType OsCfg_Alarm_Rte_Al_TE_Task_4ms_Core2_QM_4ms_Dyn;

/* Alarm dynamic parameters end. */

/* Resource dynamic parameters start. */
static Os_ResourceDynType Os_Resource_Core2_Task_OsResource2_Dyn;
/* Resource dynamic parameters end. */

/* Scheduler dynamic parameters start. */
static Os_BitMapDynType OsCfg_Scheduler_BitMap_OsCore2_Dyn;
static Os_SchedulerDynType OsCfg_Scheduler_OsCore2_Dyn;
static Os_BitMapDataType OsCfg_BitMap_L1Data_OsCore2_Dyn[OS_BITMAP_LENGTH(OS_CFG_NUM_TASKQUEUES_OSCORE2)];

Os_TaskDynType* OsCfg_TaskQueueNodes0_Data_OsCore2[OS_CFG_SIZE_TASKQUEUE0_OSCORE2];
Os_TaskDynType* OsCfg_TaskQueueNodes1_Data_OsCore2[OS_CFG_SIZE_TASKQUEUE1_OSCORE2];
Os_TaskDynType* OsCfg_TaskQueueNodes2_Data_OsCore2[OS_CFG_SIZE_TASKQUEUE2_OSCORE2];
Os_TaskDynType* OsCfg_TaskQueueNodes3_Data_OsCore2[OS_CFG_SIZE_TASKQUEUE3_OSCORE2];
Os_TaskDynType* OsCfg_TaskQueueNodes4_Data_OsCore2[OS_CFG_SIZE_TASKQUEUE4_OSCORE2];
Os_TaskDynType* OsCfg_TaskQueueNodes5_Data_OsCore2[OS_CFG_SIZE_TASKQUEUE5_OSCORE2];
Os_TaskDynType* OsCfg_TaskQueueNodes6_Data_OsCore2[OS_CFG_SIZE_TASKQUEUE6_OSCORE2];
Os_TaskDynType* OsCfg_TaskQueueNodes7_Data_OsCore2[OS_CFG_SIZE_TASKQUEUE7_OSCORE2];
Os_TaskDynType* OsCfg_TaskQueueNodes8_Data_OsCore2[OS_CFG_SIZE_TASKQUEUE8_OSCORE2];
Os_TaskDynType* OsCfg_TaskQueueNodes9_Data_OsCore2[OS_CFG_SIZE_TASKQUEUE9_OSCORE2];
Os_TaskDynType* OsCfg_TaskQueueNodes10_Data_OsCore2[OS_CFG_SIZE_TASKQUEUE10_OSCORE2];
Os_TaskDynType* OsCfg_TaskQueueNodes11_Data_OsCore2[OS_CFG_SIZE_TASKQUEUE11_OSCORE2];
Os_TaskDynType* OsCfg_TaskQueueNodes12_Data_OsCore2[OS_CFG_SIZE_TASKQUEUE12_OSCORE2];

Os_TaskQueType OsCfg_TaskQueueNodes0_OsCore2;
Os_TaskQueType OsCfg_TaskQueueNodes1_OsCore2;
Os_TaskQueType OsCfg_TaskQueueNodes2_OsCore2;
Os_TaskQueType OsCfg_TaskQueueNodes3_OsCore2;
Os_TaskQueType OsCfg_TaskQueueNodes4_OsCore2;
Os_TaskQueType OsCfg_TaskQueueNodes5_OsCore2;
Os_TaskQueType OsCfg_TaskQueueNodes6_OsCore2;
Os_TaskQueType OsCfg_TaskQueueNodes7_OsCore2;
Os_TaskQueType OsCfg_TaskQueueNodes8_OsCore2;
Os_TaskQueType OsCfg_TaskQueueNodes9_OsCore2;
Os_TaskQueType OsCfg_TaskQueueNodes10_OsCore2;
Os_TaskQueType OsCfg_TaskQueueNodes11_OsCore2;
Os_TaskQueType OsCfg_TaskQueueNodes12_OsCore2;

static Os_PriQueueNodeType* Os_PriQueueNode_SystemTimer_Core2_0[OS_CFG_NUM_TASKQUEUES_SYSTEMTIMER_CORE2 + 1];
static Os_PriQueueNodeType* Os_PriQueueNode_SystemTimer_Core2_1[OS_CFG_NUM_TASKQUEUES_SYSTEMTIMER_CORE2 + 1];

/* Scheduler dynamic parameters end. */

#define OS_STOP_SEC_VAR_OSCORE2 
#include "Os_MemMap.h"

#define OS_START_SEC_INITVAR_OSCORE2 
#include "Os_MemMap.h"
/* Scheduler init dynamic parameters start. */
Os_TaskQueType* OsCfg_Scheduler_OsCore2_TaskQueues[OS_CFG_NUM_TASKQUEUES_OSCORE2] =
{
    &OsCfg_TaskQueueNodes0_OsCore2,
    &OsCfg_TaskQueueNodes1_OsCore2,
    &OsCfg_TaskQueueNodes2_OsCore2,
    &OsCfg_TaskQueueNodes3_OsCore2,
    &OsCfg_TaskQueueNodes4_OsCore2,
    &OsCfg_TaskQueueNodes5_OsCore2,
    &OsCfg_TaskQueueNodes6_OsCore2,
    &OsCfg_TaskQueueNodes7_OsCore2,
    &OsCfg_TaskQueueNodes8_OsCore2,
    &OsCfg_TaskQueueNodes9_OsCore2,
    &OsCfg_TaskQueueNodes10_OsCore2,
    &OsCfg_TaskQueueNodes11_OsCore2,
    &OsCfg_TaskQueueNodes12_OsCore2
};


Os_CntExpListCfgType Os_CntExpList_SystemTimer_Core2 =
{
    {
        {
            /* cntExpList[0]->priQueueNode       = */ Os_PriQueueNode_SystemTimer_Core2_0,
            /* cntExpList[0]->priQueueUseCounter = */ 0U,
            /* cntExpList[0]->priQueueSize       = */ OS_CFG_NUM_TASKQUEUES_SYSTEMTIMER_CORE2
        },
        {
            /* cntExpList[1]->priQueueNode       = */ Os_PriQueueNode_SystemTimer_Core2_1,
            /* cntExpList[1]->priQueueUseCounter = */ 0U,
            /* cntExpList[1]->priQueueSize       = */ OS_CFG_NUM_TASKQUEUES_SYSTEMTIMER_CORE2
        }
    },
    /* cntExplistMux = */ 0U
};
/* Scheduler init dynamic parameters end. */

#define OS_STOP_SEC_INITVAR_OSCORE2 
#include "Os_MemMap.h"

#define OS_START_SEC_GLOBAL_NOCACHE_VAR 
#include "Os_MemMap.h"

/* Spinlock dynamic parameters start. */
/* Spinlock dynamic parameters end. */

#define OS_STOP_SEC_GLOBAL_NOCACHE_VAR 
#include "Os_MemMap.h"

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
#define OS_START_SEC_CODE 
#include "Os_MemMap.h"
void OsCfg_Scheduler_InitCallback_OsCore0(void)
{
    Os_TaskQue_Init(&OsCfg_TaskQueueNodes0_OsCore0, OsCfg_TaskQueueNodes0_Data_OsCore0, OS_CFG_SIZE_TASKQUEUE0_OSCORE0);
    Os_TaskQue_Init(&OsCfg_TaskQueueNodes1_OsCore0, OsCfg_TaskQueueNodes1_Data_OsCore0, OS_CFG_SIZE_TASKQUEUE1_OSCORE0);
    Os_TaskQue_Init(&OsCfg_TaskQueueNodes2_OsCore0, OsCfg_TaskQueueNodes2_Data_OsCore0, OS_CFG_SIZE_TASKQUEUE2_OSCORE0);
    Os_TaskQue_Init(&OsCfg_TaskQueueNodes3_OsCore0, OsCfg_TaskQueueNodes3_Data_OsCore0, OS_CFG_SIZE_TASKQUEUE3_OSCORE0);
    Os_TaskQue_Init(&OsCfg_TaskQueueNodes4_OsCore0, OsCfg_TaskQueueNodes4_Data_OsCore0, OS_CFG_SIZE_TASKQUEUE4_OSCORE0);
    Os_TaskQue_Init(&OsCfg_TaskQueueNodes5_OsCore0, OsCfg_TaskQueueNodes5_Data_OsCore0, OS_CFG_SIZE_TASKQUEUE5_OSCORE0);
    Os_TaskQue_Init(&OsCfg_TaskQueueNodes6_OsCore0, OsCfg_TaskQueueNodes6_Data_OsCore0, OS_CFG_SIZE_TASKQUEUE6_OSCORE0);
    Os_TaskQue_Init(&OsCfg_TaskQueueNodes7_OsCore0, OsCfg_TaskQueueNodes7_Data_OsCore0, OS_CFG_SIZE_TASKQUEUE7_OSCORE0);
    Os_TaskQue_Init(&OsCfg_TaskQueueNodes8_OsCore0, OsCfg_TaskQueueNodes8_Data_OsCore0, OS_CFG_SIZE_TASKQUEUE8_OSCORE0);
    Os_TaskQue_Init(&OsCfg_TaskQueueNodes9_OsCore0, OsCfg_TaskQueueNodes9_Data_OsCore0, OS_CFG_SIZE_TASKQUEUE9_OSCORE0);
    Os_TaskQue_Init(&OsCfg_TaskQueueNodes10_OsCore0, OsCfg_TaskQueueNodes10_Data_OsCore0, OS_CFG_SIZE_TASKQUEUE10_OSCORE0);
}

void OsCfg_Scheduler_InitCallback_OsCore1(void)
{
    Os_TaskQue_Init(&OsCfg_TaskQueueNodes0_OsCore1, OsCfg_TaskQueueNodes0_Data_OsCore1, OS_CFG_SIZE_TASKQUEUE0_OSCORE1);
    Os_TaskQue_Init(&OsCfg_TaskQueueNodes1_OsCore1, OsCfg_TaskQueueNodes1_Data_OsCore1, OS_CFG_SIZE_TASKQUEUE1_OSCORE1);
    Os_TaskQue_Init(&OsCfg_TaskQueueNodes2_OsCore1, OsCfg_TaskQueueNodes2_Data_OsCore1, OS_CFG_SIZE_TASKQUEUE2_OSCORE1);
    Os_TaskQue_Init(&OsCfg_TaskQueueNodes3_OsCore1, OsCfg_TaskQueueNodes3_Data_OsCore1, OS_CFG_SIZE_TASKQUEUE3_OSCORE1);
    Os_TaskQue_Init(&OsCfg_TaskQueueNodes4_OsCore1, OsCfg_TaskQueueNodes4_Data_OsCore1, OS_CFG_SIZE_TASKQUEUE4_OSCORE1);
    Os_TaskQue_Init(&OsCfg_TaskQueueNodes5_OsCore1, OsCfg_TaskQueueNodes5_Data_OsCore1, OS_CFG_SIZE_TASKQUEUE5_OSCORE1);
    Os_TaskQue_Init(&OsCfg_TaskQueueNodes6_OsCore1, OsCfg_TaskQueueNodes6_Data_OsCore1, OS_CFG_SIZE_TASKQUEUE6_OSCORE1);
    Os_TaskQue_Init(&OsCfg_TaskQueueNodes7_OsCore1, OsCfg_TaskQueueNodes7_Data_OsCore1, OS_CFG_SIZE_TASKQUEUE7_OSCORE1);
    Os_TaskQue_Init(&OsCfg_TaskQueueNodes8_OsCore1, OsCfg_TaskQueueNodes8_Data_OsCore1, OS_CFG_SIZE_TASKQUEUE8_OSCORE1);
    Os_TaskQue_Init(&OsCfg_TaskQueueNodes9_OsCore1, OsCfg_TaskQueueNodes9_Data_OsCore1, OS_CFG_SIZE_TASKQUEUE9_OSCORE1);
    Os_TaskQue_Init(&OsCfg_TaskQueueNodes10_OsCore1, OsCfg_TaskQueueNodes10_Data_OsCore1, OS_CFG_SIZE_TASKQUEUE10_OSCORE1);
}

void OsCfg_Scheduler_InitCallback_OsCore2(void)
{
    Os_TaskQue_Init(&OsCfg_TaskQueueNodes0_OsCore2, OsCfg_TaskQueueNodes0_Data_OsCore2, OS_CFG_SIZE_TASKQUEUE0_OSCORE2);
    Os_TaskQue_Init(&OsCfg_TaskQueueNodes1_OsCore2, OsCfg_TaskQueueNodes1_Data_OsCore2, OS_CFG_SIZE_TASKQUEUE1_OSCORE2);
    Os_TaskQue_Init(&OsCfg_TaskQueueNodes2_OsCore2, OsCfg_TaskQueueNodes2_Data_OsCore2, OS_CFG_SIZE_TASKQUEUE2_OSCORE2);
    Os_TaskQue_Init(&OsCfg_TaskQueueNodes3_OsCore2, OsCfg_TaskQueueNodes3_Data_OsCore2, OS_CFG_SIZE_TASKQUEUE3_OSCORE2);
    Os_TaskQue_Init(&OsCfg_TaskQueueNodes4_OsCore2, OsCfg_TaskQueueNodes4_Data_OsCore2, OS_CFG_SIZE_TASKQUEUE4_OSCORE2);
    Os_TaskQue_Init(&OsCfg_TaskQueueNodes5_OsCore2, OsCfg_TaskQueueNodes5_Data_OsCore2, OS_CFG_SIZE_TASKQUEUE5_OSCORE2);
    Os_TaskQue_Init(&OsCfg_TaskQueueNodes6_OsCore2, OsCfg_TaskQueueNodes6_Data_OsCore2, OS_CFG_SIZE_TASKQUEUE6_OSCORE2);
    Os_TaskQue_Init(&OsCfg_TaskQueueNodes7_OsCore2, OsCfg_TaskQueueNodes7_Data_OsCore2, OS_CFG_SIZE_TASKQUEUE7_OSCORE2);
    Os_TaskQue_Init(&OsCfg_TaskQueueNodes8_OsCore2, OsCfg_TaskQueueNodes8_Data_OsCore2, OS_CFG_SIZE_TASKQUEUE8_OSCORE2);
    Os_TaskQue_Init(&OsCfg_TaskQueueNodes9_OsCore2, OsCfg_TaskQueueNodes9_Data_OsCore2, OS_CFG_SIZE_TASKQUEUE9_OSCORE2);
    Os_TaskQue_Init(&OsCfg_TaskQueueNodes10_OsCore2, OsCfg_TaskQueueNodes10_Data_OsCore2, OS_CFG_SIZE_TASKQUEUE10_OSCORE2);
    Os_TaskQue_Init(&OsCfg_TaskQueueNodes11_OsCore2, OsCfg_TaskQueueNodes11_Data_OsCore2, OS_CFG_SIZE_TASKQUEUE11_OSCORE2);
    Os_TaskQue_Init(&OsCfg_TaskQueueNodes12_OsCore2, OsCfg_TaskQueueNodes12_Data_OsCore2, OS_CFG_SIZE_TASKQUEUE12_OSCORE2);
}

#define OS_STOP_SEC_CODE 
#include "Os_MemMap.h"

#define OS_START_SEC_CONST 
#include "Os_MemMap.h"
/* System config parameters start. */
const Os_SystemCfgType Os_SystemCfgData =
{
    /* isrRefs =     */ NULL_PTR,   
    /* isrCnt =      */ 0U,
    /* isrCat1Refs = */ NULL_PTR,   
    /* isrCat1Cnt =  */ 0U,
    /* counterRefs = */ NULL_PTR,   
    /* counterCnt =  */ 0U
};

/* System config parameters end. */

/* App config parameters start. */
const Os_AppCfgType OsCfg_Appl_SystemApplication_OsCore_Core0 =
{
    /* appDelayTimingViolation = */ FALSE,
    /* appTrust                = */ OS_APP_TRUSTED,
    /* appDyn                  = */ &OsCfg_Appl_SystemApplication_OsCore_Core0_Dyn,
    /* startupHook             = */ NULL_PTR,
    /* shutdownHook            = */ &ShutdownHook,
    /* errorHook               = */ &ErrorHook,
    /* coreId                  = */ OS_CORE_ID_0,
    /* restartTask             = */ NULL_PTR,
    /* appId                   = */ SYSTEMAPPLICATION_OSCORE_CORE0
};
const Os_AppCfgType OsCfg_Appl_App_Application_Core0_QM =
{
    /* appDelayTimingViolation = */ FALSE,
    /* appTrust                = */ OS_APP_TRUSTED,
    /* appDyn                  = */ &OsCfg_Appl_App_Application_Core0_QM_Dyn,
    /* startupHook             = */ NULL_PTR,
    /* shutdownHook            = */ NULL_PTR,
    /* errorHook               = */ NULL_PTR,
    /* coreId                  = */ OS_CORE_ID_0,
    /* restartTask             = */ NULL_PTR,
    /* appId                   = */ APP_APPLICATION_CORE0_QM
};
const Os_AppCfgType OsCfg_Appl_SystemApplication_OsCore_Core1 =
{
    /* appDelayTimingViolation = */ FALSE,
    /* appTrust                = */ OS_APP_TRUSTED,
    /* appDyn                  = */ &OsCfg_Appl_SystemApplication_OsCore_Core1_Dyn,
    /* startupHook             = */ NULL_PTR,
    /* shutdownHook            = */ &ShutdownHook,
    /* errorHook               = */ &ErrorHook,
    /* coreId                  = */ OS_CORE_ID_1,
    /* restartTask             = */ NULL_PTR,
    /* appId                   = */ SYSTEMAPPLICATION_OSCORE_CORE1
};
const Os_AppCfgType OsCfg_Appl_App_Application_Core1_QM =
{
    /* appDelayTimingViolation = */ FALSE,
    /* appTrust                = */ OS_APP_TRUSTED,
    /* appDyn                  = */ &OsCfg_Appl_App_Application_Core1_QM_Dyn,
    /* startupHook             = */ NULL_PTR,
    /* shutdownHook            = */ NULL_PTR,
    /* errorHook               = */ NULL_PTR,
    /* coreId                  = */ OS_CORE_ID_1,
    /* restartTask             = */ NULL_PTR,
    /* appId                   = */ APP_APPLICATION_CORE1_QM
};
const Os_AppCfgType OsCfg_Appl_SystemApplication_OsCore_Core2 =
{
    /* appDelayTimingViolation = */ FALSE,
    /* appTrust                = */ OS_APP_TRUSTED,
    /* appDyn                  = */ &OsCfg_Appl_SystemApplication_OsCore_Core2_Dyn,
    /* startupHook             = */ NULL_PTR,
    /* shutdownHook            = */ &ShutdownHook,
    /* errorHook               = */ &ErrorHook,
    /* coreId                  = */ OS_CORE_ID_2,
    /* restartTask             = */ NULL_PTR,
    /* appId                   = */ SYSTEMAPPLICATION_OSCORE_CORE2
};
const Os_AppCfgType OsCfg_Appl_App_Application_Core2_QM =
{
    /* appDelayTimingViolation = */ FALSE,
    /* appTrust                = */ OS_APP_TRUSTED,
    /* appDyn                  = */ &OsCfg_Appl_App_Application_Core2_QM_Dyn,
    /* startupHook             = */ NULL_PTR,
    /* shutdownHook            = */ NULL_PTR,
    /* errorHook               = */ NULL_PTR,
    /* coreId                  = */ OS_CORE_ID_2,
    /* restartTask             = */ NULL_PTR,
    /* appId                   = */ APP_APPLICATION_CORE2_QM
};
/* App config parameters end. */

/* Task config parameters start. */
const Os_TaskCfgType OsCfg_Task_Default_Init_Task_Core0 =
{
    /* contextCfg     = */ &OsCfg_Arch_Context_Default_Init_Task_Core0,
    /* ownerAppId     = */ SYSTEMAPPLICATION_OSCORE_CORE0,
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC2) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* tpCfg      = */ NULL_PTR,
#endif
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC3) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* appMpCfg       = */ NULL_PTR,
    /* taskMpCfg      = */ NULL_PTR,
#endif
    /* taskDyn        = */ &OsCfg_Task_Default_Init_Task_Core0_Dyn,
    /* cfgPrio        = */ 0U,
    /* schdType       = */ OS_TASK_NON,
    /* maxActivations = */ 100U,
    /* preTaskHook    = */ NULL_PTR,
    /* postTaskHook   = */ NULL_PTR,
    /* accessingApps  = */ (OS_SYSTEMAPPLICATION_OSCORE_CORE0_ACCESS |OS_APP_APPLICATION_CORE0_QM_ACCESS),
    /* taskId         = */ DEFAULT_INIT_TASK_CORE0,
    /* coreId         = */ OS_CORE_ID_0,
    /* taskType       = */ OS_TASK_BT,
    /* appMode        = */ OS_APPMODE_ANY
};
const Os_TaskCfgType OsCfg_Task_Idle_Task_Core0 =
{
    /* contextCfg     = */ &OsCfg_Arch_Context_Idle_Task_Core0,
    /* ownerAppId     = */ SYSTEMAPPLICATION_OSCORE_CORE0,
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC2) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* tpCfg      = */ NULL_PTR,
#endif
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC3) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* appMpCfg       = */ NULL_PTR,
    /* taskMpCfg      = */ NULL_PTR,
#endif
    /* taskDyn        = */ &OsCfg_Task_Idle_Task_Core0_Dyn,
    /* cfgPrio        = */ 10U,
    /* schdType       = */ OS_TASK_FULL,
    /* maxActivations = */ 100U,
    /* preTaskHook    = */ NULL_PTR,
    /* postTaskHook   = */ NULL_PTR,
    /* accessingApps  = */ (OS_SYSTEMAPPLICATION_OSCORE_CORE0_ACCESS |OS_APP_APPLICATION_CORE0_QM_ACCESS),
    /* taskId         = */ IDLE_TASK_CORE0,
    /* coreId         = */ OS_CORE_ID_0,
    /* taskType       = */ OS_TASK_BT,
    /* appMode        = */ OS_APPMODE_ANY
};
const Os_TaskCfgType OsCfg_Task_Task_Init_Core0_QM =
{
    /* contextCfg     = */ &OsCfg_Arch_Context_Task_Init_Core0_QM,
    /* ownerAppId     = */ APP_APPLICATION_CORE0_QM,
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC2) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* tpCfg      = */ NULL_PTR,
#endif
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC3) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* appMpCfg       = */ NULL_PTR,
    /* taskMpCfg      = */ NULL_PTR,
#endif
    /* taskDyn        = */ &OsCfg_Task_Task_Init_Core0_QM_Dyn,
    /* cfgPrio        = */ 1U,
    /* schdType       = */ OS_TASK_NON,
    /* maxActivations = */ 100U,
    /* preTaskHook    = */ NULL_PTR,
    /* postTaskHook   = */ NULL_PTR,
    /* accessingApps  = */ (OS_SYSTEMAPPLICATION_OSCORE_CORE0_ACCESS |OS_APP_APPLICATION_CORE0_QM_ACCESS),
    /* taskId         = */ TASK_INIT_CORE0_QM,
    /* coreId         = */ OS_CORE_ID_0,
    /* taskType       = */ OS_TASK_BT,
    /* appMode        = */ OS_APPMODE_NONE
};
const Os_TaskCfgType OsCfg_Task_Task_10ms_Core0_QM =
{
    /* contextCfg     = */ &OsCfg_Arch_Context_Task_10ms_Core0_QM,
    /* ownerAppId     = */ APP_APPLICATION_CORE0_QM,
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC2) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* tpCfg      = */ NULL_PTR,
#endif
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC3) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* appMpCfg       = */ NULL_PTR,
    /* taskMpCfg      = */ NULL_PTR,
#endif
    /* taskDyn        = */ &OsCfg_Task_Task_10ms_Core0_QM_Dyn,
    /* cfgPrio        = */ 3U,
    /* schdType       = */ OS_TASK_FULL,
    /* maxActivations = */ 100U,
    /* preTaskHook    = */ NULL_PTR,
    /* postTaskHook   = */ NULL_PTR,
    /* accessingApps  = */ (OS_SYSTEMAPPLICATION_OSCORE_CORE0_ACCESS |OS_APP_APPLICATION_CORE0_QM_ACCESS),
    /* taskId         = */ TASK_10MS_CORE0_QM,
    /* coreId         = */ OS_CORE_ID_0,
    /* taskType       = */ OS_TASK_BT,
    /* appMode        = */ OS_APPMODE_NONE
};
const Os_TaskCfgType OsCfg_Task_Task_20ms_Core0_QM =
{
    /* contextCfg     = */ &OsCfg_Arch_Context_Task_20ms_Core0_QM,
    /* ownerAppId     = */ APP_APPLICATION_CORE0_QM,
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC2) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* tpCfg      = */ NULL_PTR,
#endif
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC3) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* appMpCfg       = */ NULL_PTR,
    /* taskMpCfg      = */ NULL_PTR,
#endif
    /* taskDyn        = */ &OsCfg_Task_Task_20ms_Core0_QM_Dyn,
    /* cfgPrio        = */ 4U,
    /* schdType       = */ OS_TASK_FULL,
    /* maxActivations = */ 100U,
    /* preTaskHook    = */ NULL_PTR,
    /* postTaskHook   = */ NULL_PTR,
    /* accessingApps  = */ (OS_SYSTEMAPPLICATION_OSCORE_CORE0_ACCESS |OS_APP_APPLICATION_CORE0_QM_ACCESS),
    /* taskId         = */ TASK_20MS_CORE0_QM,
    /* coreId         = */ OS_CORE_ID_0,
    /* taskType       = */ OS_TASK_BT,
    /* appMode        = */ OS_APPMODE_NONE
};
const Os_TaskCfgType OsCfg_Task_Task_50ms_Core0_QM =
{
    /* contextCfg     = */ &OsCfg_Arch_Context_Task_50ms_Core0_QM,
    /* ownerAppId     = */ APP_APPLICATION_CORE0_QM,
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC2) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* tpCfg      = */ NULL_PTR,
#endif
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC3) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* appMpCfg       = */ NULL_PTR,
    /* taskMpCfg      = */ NULL_PTR,
#endif
    /* taskDyn        = */ &OsCfg_Task_Task_50ms_Core0_QM_Dyn,
    /* cfgPrio        = */ 5U,
    /* schdType       = */ OS_TASK_FULL,
    /* maxActivations = */ 100U,
    /* preTaskHook    = */ NULL_PTR,
    /* postTaskHook   = */ NULL_PTR,
    /* accessingApps  = */ (OS_SYSTEMAPPLICATION_OSCORE_CORE0_ACCESS |OS_APP_APPLICATION_CORE0_QM_ACCESS),
    /* taskId         = */ TASK_50MS_CORE0_QM,
    /* coreId         = */ OS_CORE_ID_0,
    /* taskType       = */ OS_TASK_BT,
    /* appMode        = */ OS_APPMODE_NONE
};
const Os_TaskCfgType OsCfg_Task_Task_100ms_Core0_QM =
{
    /* contextCfg     = */ &OsCfg_Arch_Context_Task_100ms_Core0_QM,
    /* ownerAppId     = */ APP_APPLICATION_CORE0_QM,
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC2) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* tpCfg      = */ NULL_PTR,
#endif
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC3) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* appMpCfg       = */ NULL_PTR,
    /* taskMpCfg      = */ NULL_PTR,
#endif
    /* taskDyn        = */ &OsCfg_Task_Task_100ms_Core0_QM_Dyn,
    /* cfgPrio        = */ 6U,
    /* schdType       = */ OS_TASK_FULL,
    /* maxActivations = */ 100U,
    /* preTaskHook    = */ NULL_PTR,
    /* postTaskHook   = */ NULL_PTR,
    /* accessingApps  = */ (OS_SYSTEMAPPLICATION_OSCORE_CORE0_ACCESS |OS_APP_APPLICATION_CORE0_QM_ACCESS),
    /* taskId         = */ TASK_100MS_CORE0_QM,
    /* coreId         = */ OS_CORE_ID_0,
    /* taskType       = */ OS_TASK_BT,
    /* appMode        = */ OS_APPMODE_NONE
};
const Os_TaskCfgType OsCfg_Task_Task_200ms_Core0_QM =
{
    /* contextCfg     = */ &OsCfg_Arch_Context_Task_200ms_Core0_QM,
    /* ownerAppId     = */ APP_APPLICATION_CORE0_QM,
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC2) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* tpCfg      = */ NULL_PTR,
#endif
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC3) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* appMpCfg       = */ NULL_PTR,
    /* taskMpCfg      = */ NULL_PTR,
#endif
    /* taskDyn        = */ &OsCfg_Task_Task_200ms_Core0_QM_Dyn,
    /* cfgPrio        = */ 7U,
    /* schdType       = */ OS_TASK_FULL,
    /* maxActivations = */ 100U,
    /* preTaskHook    = */ NULL_PTR,
    /* postTaskHook   = */ NULL_PTR,
    /* accessingApps  = */ (OS_SYSTEMAPPLICATION_OSCORE_CORE0_ACCESS |OS_APP_APPLICATION_CORE0_QM_ACCESS),
    /* taskId         = */ TASK_200MS_CORE0_QM,
    /* coreId         = */ OS_CORE_ID_0,
    /* taskType       = */ OS_TASK_BT,
    /* appMode        = */ OS_APPMODE_NONE
};
const Os_TaskCfgType OsCfg_Task_Task_500ms_Core0_QM =
{
    /* contextCfg     = */ &OsCfg_Arch_Context_Task_500ms_Core0_QM,
    /* ownerAppId     = */ APP_APPLICATION_CORE0_QM,
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC2) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* tpCfg      = */ NULL_PTR,
#endif
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC3) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* appMpCfg       = */ NULL_PTR,
    /* taskMpCfg      = */ NULL_PTR,
#endif
    /* taskDyn        = */ &OsCfg_Task_Task_500ms_Core0_QM_Dyn,
    /* cfgPrio        = */ 8U,
    /* schdType       = */ OS_TASK_FULL,
    /* maxActivations = */ 100U,
    /* preTaskHook    = */ NULL_PTR,
    /* postTaskHook   = */ NULL_PTR,
    /* accessingApps  = */ (OS_SYSTEMAPPLICATION_OSCORE_CORE0_ACCESS |OS_APP_APPLICATION_CORE0_QM_ACCESS),
    /* taskId         = */ TASK_500MS_CORE0_QM,
    /* coreId         = */ OS_CORE_ID_0,
    /* taskType       = */ OS_TASK_BT,
    /* appMode        = */ OS_APPMODE_NONE
};
const Os_TaskCfgType OsCfg_Task_Task_1000ms_Core0_QM =
{
    /* contextCfg     = */ &OsCfg_Arch_Context_Task_1000ms_Core0_QM,
    /* ownerAppId     = */ APP_APPLICATION_CORE0_QM,
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC2) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* tpCfg      = */ NULL_PTR,
#endif
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC3) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* appMpCfg       = */ NULL_PTR,
    /* taskMpCfg      = */ NULL_PTR,
#endif
    /* taskDyn        = */ &OsCfg_Task_Task_1000ms_Core0_QM_Dyn,
    /* cfgPrio        = */ 9U,
    /* schdType       = */ OS_TASK_FULL,
    /* maxActivations = */ 100U,
    /* preTaskHook    = */ NULL_PTR,
    /* postTaskHook   = */ NULL_PTR,
    /* accessingApps  = */ (OS_SYSTEMAPPLICATION_OSCORE_CORE0_ACCESS |OS_APP_APPLICATION_CORE0_QM_ACCESS),
    /* taskId         = */ TASK_1000MS_CORE0_QM,
    /* coreId         = */ OS_CORE_ID_0,
    /* taskType       = */ OS_TASK_BT,
    /* appMode        = */ OS_APPMODE_NONE
};
const Os_TaskCfgType OsCfg_Task_Task_2ms_Core0_QM =
{
    /* contextCfg     = */ &OsCfg_Arch_Context_Task_2ms_Core0_QM,
    /* ownerAppId     = */ APP_APPLICATION_CORE0_QM,
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC2) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* tpCfg      = */ NULL_PTR,
#endif
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC3) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* appMpCfg       = */ NULL_PTR,
    /* taskMpCfg      = */ NULL_PTR,
#endif
    /* taskDyn        = */ &OsCfg_Task_Task_2ms_Core0_QM_Dyn,
    /* cfgPrio        = */ 2U,
    /* schdType       = */ OS_TASK_FULL,
    /* maxActivations = */ 100U,
    /* preTaskHook    = */ NULL_PTR,
    /* postTaskHook   = */ NULL_PTR,
    /* accessingApps  = */ (OS_SYSTEMAPPLICATION_OSCORE_CORE0_ACCESS |OS_APP_APPLICATION_CORE0_QM_ACCESS),
    /* taskId         = */ TASK_2MS_CORE0_QM,
    /* coreId         = */ OS_CORE_ID_0,
    /* taskType       = */ OS_TASK_BT,
    /* appMode        = */ OS_APPMODE_NONE
};
const Os_TaskCfgType OsCfg_Task_Default_Init_Task_Core1 =
{
    /* contextCfg     = */ &OsCfg_Arch_Context_Default_Init_Task_Core1,
    /* ownerAppId     = */ SYSTEMAPPLICATION_OSCORE_CORE1,
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC2) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* tpCfg      = */ NULL_PTR,
#endif
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC3) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* appMpCfg       = */ NULL_PTR,
    /* taskMpCfg      = */ NULL_PTR,
#endif
    /* taskDyn        = */ &OsCfg_Task_Default_Init_Task_Core1_Dyn,
    /* cfgPrio        = */ 0U,
    /* schdType       = */ OS_TASK_NON,
    /* maxActivations = */ 100U,
    /* preTaskHook    = */ NULL_PTR,
    /* postTaskHook   = */ NULL_PTR,
    /* accessingApps  = */ (OS_SYSTEMAPPLICATION_OSCORE_CORE1_ACCESS |OS_APP_APPLICATION_CORE1_QM_ACCESS),
    /* taskId         = */ DEFAULT_INIT_TASK_CORE1,
    /* coreId         = */ OS_CORE_ID_1,
    /* taskType       = */ OS_TASK_BT,
    /* appMode        = */ OS_APPMODE_ANY
};
const Os_TaskCfgType OsCfg_Task_Idle_Task_Core1 =
{
    /* contextCfg     = */ &OsCfg_Arch_Context_Idle_Task_Core1,
    /* ownerAppId     = */ SYSTEMAPPLICATION_OSCORE_CORE1,
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC2) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* tpCfg      = */ NULL_PTR,
#endif
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC3) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* appMpCfg       = */ NULL_PTR,
    /* taskMpCfg      = */ NULL_PTR,
#endif
    /* taskDyn        = */ &OsCfg_Task_Idle_Task_Core1_Dyn,
    /* cfgPrio        = */ 10U,
    /* schdType       = */ OS_TASK_FULL,
    /* maxActivations = */ 100U,
    /* preTaskHook    = */ NULL_PTR,
    /* postTaskHook   = */ NULL_PTR,
    /* accessingApps  = */ (OS_SYSTEMAPPLICATION_OSCORE_CORE1_ACCESS |OS_APP_APPLICATION_CORE1_QM_ACCESS),
    /* taskId         = */ IDLE_TASK_CORE1,
    /* coreId         = */ OS_CORE_ID_1,
    /* taskType       = */ OS_TASK_BT,
    /* appMode        = */ OS_APPMODE_ANY
};
const Os_TaskCfgType OsCfg_Task_Task_Init_Core1_QM =
{
    /* contextCfg     = */ &OsCfg_Arch_Context_Task_Init_Core1_QM,
    /* ownerAppId     = */ APP_APPLICATION_CORE1_QM,
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC2) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* tpCfg      = */ NULL_PTR,
#endif
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC3) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* appMpCfg       = */ NULL_PTR,
    /* taskMpCfg      = */ NULL_PTR,
#endif
    /* taskDyn        = */ &OsCfg_Task_Task_Init_Core1_QM_Dyn,
    /* cfgPrio        = */ 1U,
    /* schdType       = */ OS_TASK_NON,
    /* maxActivations = */ 100U,
    /* preTaskHook    = */ NULL_PTR,
    /* postTaskHook   = */ NULL_PTR,
    /* accessingApps  = */ (OS_SYSTEMAPPLICATION_OSCORE_CORE1_ACCESS |OS_APP_APPLICATION_CORE1_QM_ACCESS),
    /* taskId         = */ TASK_INIT_CORE1_QM,
    /* coreId         = */ OS_CORE_ID_1,
    /* taskType       = */ OS_TASK_BT,
    /* appMode        = */ OS_APPMODE_NONE
};
const Os_TaskCfgType OsCfg_Task_Task_5ms_Core1_QM =
{
    /* contextCfg     = */ &OsCfg_Arch_Context_Task_5ms_Core1_QM,
    /* ownerAppId     = */ APP_APPLICATION_CORE1_QM,
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC2) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* tpCfg      = */ NULL_PTR,
#endif
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC3) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* appMpCfg       = */ NULL_PTR,
    /* taskMpCfg      = */ NULL_PTR,
#endif
    /* taskDyn        = */ &OsCfg_Task_Task_5ms_Core1_QM_Dyn,
    /* cfgPrio        = */ 2U,
    /* schdType       = */ OS_TASK_FULL,
    /* maxActivations = */ 100U,
    /* preTaskHook    = */ NULL_PTR,
    /* postTaskHook   = */ NULL_PTR,
    /* accessingApps  = */ (OS_SYSTEMAPPLICATION_OSCORE_CORE1_ACCESS |OS_APP_APPLICATION_CORE1_QM_ACCESS),
    /* taskId         = */ TASK_5MS_CORE1_QM,
    /* coreId         = */ OS_CORE_ID_1,
    /* taskType       = */ OS_TASK_BT,
    /* appMode        = */ OS_APPMODE_NONE
};
const Os_TaskCfgType OsCfg_Task_Task_10ms_Core1_QM =
{
    /* contextCfg     = */ &OsCfg_Arch_Context_Task_10ms_Core1_QM,
    /* ownerAppId     = */ APP_APPLICATION_CORE1_QM,
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC2) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* tpCfg      = */ NULL_PTR,
#endif
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC3) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* appMpCfg       = */ NULL_PTR,
    /* taskMpCfg      = */ NULL_PTR,
#endif
    /* taskDyn        = */ &OsCfg_Task_Task_10ms_Core1_QM_Dyn,
    /* cfgPrio        = */ 3U,
    /* schdType       = */ OS_TASK_FULL,
    /* maxActivations = */ 100U,
    /* preTaskHook    = */ NULL_PTR,
    /* postTaskHook   = */ NULL_PTR,
    /* accessingApps  = */ (OS_SYSTEMAPPLICATION_OSCORE_CORE1_ACCESS |OS_APP_APPLICATION_CORE1_QM_ACCESS),
    /* taskId         = */ TASK_10MS_CORE1_QM,
    /* coreId         = */ OS_CORE_ID_1,
    /* taskType       = */ OS_TASK_BT,
    /* appMode        = */ OS_APPMODE_NONE
};
const Os_TaskCfgType OsCfg_Task_Task_20ms_Core1_QM =
{
    /* contextCfg     = */ &OsCfg_Arch_Context_Task_20ms_Core1_QM,
    /* ownerAppId     = */ APP_APPLICATION_CORE1_QM,
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC2) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* tpCfg      = */ NULL_PTR,
#endif
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC3) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* appMpCfg       = */ NULL_PTR,
    /* taskMpCfg      = */ NULL_PTR,
#endif
    /* taskDyn        = */ &OsCfg_Task_Task_20ms_Core1_QM_Dyn,
    /* cfgPrio        = */ 4U,
    /* schdType       = */ OS_TASK_FULL,
    /* maxActivations = */ 100U,
    /* preTaskHook    = */ NULL_PTR,
    /* postTaskHook   = */ NULL_PTR,
    /* accessingApps  = */ (OS_SYSTEMAPPLICATION_OSCORE_CORE1_ACCESS |OS_APP_APPLICATION_CORE1_QM_ACCESS),
    /* taskId         = */ TASK_20MS_CORE1_QM,
    /* coreId         = */ OS_CORE_ID_1,
    /* taskType       = */ OS_TASK_BT,
    /* appMode        = */ OS_APPMODE_NONE
};
const Os_TaskCfgType OsCfg_Task_Task_50ms_Core1_QM =
{
    /* contextCfg     = */ &OsCfg_Arch_Context_Task_50ms_Core1_QM,
    /* ownerAppId     = */ APP_APPLICATION_CORE1_QM,
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC2) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* tpCfg      = */ NULL_PTR,
#endif
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC3) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* appMpCfg       = */ NULL_PTR,
    /* taskMpCfg      = */ NULL_PTR,
#endif
    /* taskDyn        = */ &OsCfg_Task_Task_50ms_Core1_QM_Dyn,
    /* cfgPrio        = */ 5U,
    /* schdType       = */ OS_TASK_FULL,
    /* maxActivations = */ 100U,
    /* preTaskHook    = */ NULL_PTR,
    /* postTaskHook   = */ NULL_PTR,
    /* accessingApps  = */ (OS_SYSTEMAPPLICATION_OSCORE_CORE1_ACCESS |OS_APP_APPLICATION_CORE1_QM_ACCESS),
    /* taskId         = */ TASK_50MS_CORE1_QM,
    /* coreId         = */ OS_CORE_ID_1,
    /* taskType       = */ OS_TASK_BT,
    /* appMode        = */ OS_APPMODE_NONE
};
const Os_TaskCfgType OsCfg_Task_Task_100ms_Core1_QM =
{
    /* contextCfg     = */ &OsCfg_Arch_Context_Task_100ms_Core1_QM,
    /* ownerAppId     = */ APP_APPLICATION_CORE1_QM,
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC2) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* tpCfg      = */ NULL_PTR,
#endif
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC3) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* appMpCfg       = */ NULL_PTR,
    /* taskMpCfg      = */ NULL_PTR,
#endif
    /* taskDyn        = */ &OsCfg_Task_Task_100ms_Core1_QM_Dyn,
    /* cfgPrio        = */ 6U,
    /* schdType       = */ OS_TASK_FULL,
    /* maxActivations = */ 100U,
    /* preTaskHook    = */ NULL_PTR,
    /* postTaskHook   = */ NULL_PTR,
    /* accessingApps  = */ (OS_SYSTEMAPPLICATION_OSCORE_CORE1_ACCESS |OS_APP_APPLICATION_CORE1_QM_ACCESS),
    /* taskId         = */ TASK_100MS_CORE1_QM,
    /* coreId         = */ OS_CORE_ID_1,
    /* taskType       = */ OS_TASK_BT,
    /* appMode        = */ OS_APPMODE_NONE
};
const Os_TaskCfgType OsCfg_Task_Task_200ms_Core1_QM =
{
    /* contextCfg     = */ &OsCfg_Arch_Context_Task_200ms_Core1_QM,
    /* ownerAppId     = */ APP_APPLICATION_CORE1_QM,
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC2) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* tpCfg      = */ NULL_PTR,
#endif
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC3) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* appMpCfg       = */ NULL_PTR,
    /* taskMpCfg      = */ NULL_PTR,
#endif
    /* taskDyn        = */ &OsCfg_Task_Task_200ms_Core1_QM_Dyn,
    /* cfgPrio        = */ 7U,
    /* schdType       = */ OS_TASK_FULL,
    /* maxActivations = */ 100U,
    /* preTaskHook    = */ NULL_PTR,
    /* postTaskHook   = */ NULL_PTR,
    /* accessingApps  = */ (OS_SYSTEMAPPLICATION_OSCORE_CORE1_ACCESS |OS_APP_APPLICATION_CORE1_QM_ACCESS),
    /* taskId         = */ TASK_200MS_CORE1_QM,
    /* coreId         = */ OS_CORE_ID_1,
    /* taskType       = */ OS_TASK_BT,
    /* appMode        = */ OS_APPMODE_NONE
};
const Os_TaskCfgType OsCfg_Task_Task_500ms_Core1_QM =
{
    /* contextCfg     = */ &OsCfg_Arch_Context_Task_500ms_Core1_QM,
    /* ownerAppId     = */ APP_APPLICATION_CORE1_QM,
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC2) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* tpCfg      = */ NULL_PTR,
#endif
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC3) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* appMpCfg       = */ NULL_PTR,
    /* taskMpCfg      = */ NULL_PTR,
#endif
    /* taskDyn        = */ &OsCfg_Task_Task_500ms_Core1_QM_Dyn,
    /* cfgPrio        = */ 8U,
    /* schdType       = */ OS_TASK_FULL,
    /* maxActivations = */ 100U,
    /* preTaskHook    = */ NULL_PTR,
    /* postTaskHook   = */ NULL_PTR,
    /* accessingApps  = */ (OS_SYSTEMAPPLICATION_OSCORE_CORE1_ACCESS |OS_APP_APPLICATION_CORE1_QM_ACCESS),
    /* taskId         = */ TASK_500MS_CORE1_QM,
    /* coreId         = */ OS_CORE_ID_1,
    /* taskType       = */ OS_TASK_BT,
    /* appMode        = */ OS_APPMODE_NONE
};
const Os_TaskCfgType OsCfg_Task_Task_1000ms_Core1_QM =
{
    /* contextCfg     = */ &OsCfg_Arch_Context_Task_1000ms_Core1_QM,
    /* ownerAppId     = */ APP_APPLICATION_CORE1_QM,
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC2) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* tpCfg      = */ NULL_PTR,
#endif
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC3) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* appMpCfg       = */ NULL_PTR,
    /* taskMpCfg      = */ NULL_PTR,
#endif
    /* taskDyn        = */ &OsCfg_Task_Task_1000ms_Core1_QM_Dyn,
    /* cfgPrio        = */ 9U,
    /* schdType       = */ OS_TASK_FULL,
    /* maxActivations = */ 100U,
    /* preTaskHook    = */ NULL_PTR,
    /* postTaskHook   = */ NULL_PTR,
    /* accessingApps  = */ (OS_SYSTEMAPPLICATION_OSCORE_CORE1_ACCESS |OS_APP_APPLICATION_CORE1_QM_ACCESS),
    /* taskId         = */ TASK_1000MS_CORE1_QM,
    /* coreId         = */ OS_CORE_ID_1,
    /* taskType       = */ OS_TASK_BT,
    /* appMode        = */ OS_APPMODE_NONE
};
const Os_TaskCfgType OsCfg_Task_Default_Init_Task_Core2 =
{
    /* contextCfg     = */ &OsCfg_Arch_Context_Default_Init_Task_Core2,
    /* ownerAppId     = */ SYSTEMAPPLICATION_OSCORE_CORE2,
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC2) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* tpCfg      = */ NULL_PTR,
#endif
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC3) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* appMpCfg       = */ NULL_PTR,
    /* taskMpCfg      = */ NULL_PTR,
#endif
    /* taskDyn        = */ &OsCfg_Task_Default_Init_Task_Core2_Dyn,
    /* cfgPrio        = */ 0U,
    /* schdType       = */ OS_TASK_NON,
    /* maxActivations = */ 100U,
    /* preTaskHook    = */ NULL_PTR,
    /* postTaskHook   = */ NULL_PTR,
    /* accessingApps  = */ (OS_SYSTEMAPPLICATION_OSCORE_CORE2_ACCESS |OS_APP_APPLICATION_CORE2_QM_ACCESS),
    /* taskId         = */ DEFAULT_INIT_TASK_CORE2,
    /* coreId         = */ OS_CORE_ID_2,
    /* taskType       = */ OS_TASK_BT,
    /* appMode        = */ OS_APPMODE_ANY
};
const Os_TaskCfgType OsCfg_Task_Idle_Task_Core2 =
{
    /* contextCfg     = */ &OsCfg_Arch_Context_Idle_Task_Core2,
    /* ownerAppId     = */ SYSTEMAPPLICATION_OSCORE_CORE2,
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC2) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* tpCfg      = */ NULL_PTR,
#endif
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC3) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* appMpCfg       = */ NULL_PTR,
    /* taskMpCfg      = */ NULL_PTR,
#endif
    /* taskDyn        = */ &OsCfg_Task_Idle_Task_Core2_Dyn,
    /* cfgPrio        = */ 12U,
    /* schdType       = */ OS_TASK_FULL,
    /* maxActivations = */ 100U,
    /* preTaskHook    = */ NULL_PTR,
    /* postTaskHook   = */ NULL_PTR,
    /* accessingApps  = */ (OS_SYSTEMAPPLICATION_OSCORE_CORE2_ACCESS |OS_APP_APPLICATION_CORE2_QM_ACCESS),
    /* taskId         = */ IDLE_TASK_CORE2,
    /* coreId         = */ OS_CORE_ID_2,
    /* taskType       = */ OS_TASK_BT,
    /* appMode        = */ OS_APPMODE_ANY
};
const Os_TaskCfgType OsCfg_Task_Task_Init_Core2_QM =
{
    /* contextCfg     = */ &OsCfg_Arch_Context_Task_Init_Core2_QM,
    /* ownerAppId     = */ APP_APPLICATION_CORE2_QM,
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC2) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* tpCfg      = */ NULL_PTR,
#endif
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC3) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* appMpCfg       = */ NULL_PTR,
    /* taskMpCfg      = */ NULL_PTR,
#endif
    /* taskDyn        = */ &OsCfg_Task_Task_Init_Core2_QM_Dyn,
    /* cfgPrio        = */ 1U,
    /* schdType       = */ OS_TASK_NON,
    /* maxActivations = */ 100U,
    /* preTaskHook    = */ NULL_PTR,
    /* postTaskHook   = */ NULL_PTR,
    /* accessingApps  = */ (OS_SYSTEMAPPLICATION_OSCORE_CORE2_ACCESS |OS_APP_APPLICATION_CORE2_QM_ACCESS),
    /* taskId         = */ TASK_INIT_CORE2_QM,
    /* coreId         = */ OS_CORE_ID_2,
    /* taskType       = */ OS_TASK_BT,
    /* appMode        = */ OS_APPMODE_NONE
};
const Os_TaskCfgType OsCfg_Task_Task_1ms_Core2_QM =
{
    /* contextCfg     = */ &OsCfg_Arch_Context_Task_1ms_Core2_QM,
    /* ownerAppId     = */ APP_APPLICATION_CORE2_QM,
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC2) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* tpCfg      = */ NULL_PTR,
#endif
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC3) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* appMpCfg       = */ NULL_PTR,
    /* taskMpCfg      = */ NULL_PTR,
#endif
    /* taskDyn        = */ &OsCfg_Task_Task_1ms_Core2_QM_Dyn,
    /* cfgPrio        = */ 2U,
    /* schdType       = */ OS_TASK_FULL,
    /* maxActivations = */ 100U,
    /* preTaskHook    = */ NULL_PTR,
    /* postTaskHook   = */ NULL_PTR,
    /* accessingApps  = */ (OS_SYSTEMAPPLICATION_OSCORE_CORE2_ACCESS |OS_APP_APPLICATION_CORE2_QM_ACCESS),
    /* taskId         = */ TASK_1MS_CORE2_QM,
    /* coreId         = */ OS_CORE_ID_2,
    /* taskType       = */ OS_TASK_BT,
    /* appMode        = */ OS_APPMODE_NONE
};
const Os_TaskCfgType OsCfg_Task_Task_4ms_Core2_QM =
{
    /* contextCfg     = */ &OsCfg_Arch_Context_Task_4ms_Core2_QM,
    /* ownerAppId     = */ APP_APPLICATION_CORE2_QM,
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC2) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* tpCfg      = */ NULL_PTR,
#endif
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC3) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* appMpCfg       = */ NULL_PTR,
    /* taskMpCfg      = */ NULL_PTR,
#endif
    /* taskDyn        = */ &OsCfg_Task_Task_4ms_Core2_QM_Dyn,
    /* cfgPrio        = */ 3U,
    /* schdType       = */ OS_TASK_FULL,
    /* maxActivations = */ 100U,
    /* preTaskHook    = */ NULL_PTR,
    /* postTaskHook   = */ NULL_PTR,
    /* accessingApps  = */ (OS_SYSTEMAPPLICATION_OSCORE_CORE2_ACCESS |OS_APP_APPLICATION_CORE2_QM_ACCESS),
    /* taskId         = */ TASK_4MS_CORE2_QM,
    /* coreId         = */ OS_CORE_ID_2,
    /* taskType       = */ OS_TASK_BT,
    /* appMode        = */ OS_APPMODE_NONE
};
const Os_TaskCfgType OsCfg_Task_Task_5ms_Core2_QM =
{
    /* contextCfg     = */ &OsCfg_Arch_Context_Task_5ms_Core2_QM,
    /* ownerAppId     = */ APP_APPLICATION_CORE2_QM,
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC2) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* tpCfg      = */ NULL_PTR,
#endif
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC3) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* appMpCfg       = */ NULL_PTR,
    /* taskMpCfg      = */ NULL_PTR,
#endif
    /* taskDyn        = */ &OsCfg_Task_Task_5ms_Core2_QM_Dyn,
    /* cfgPrio        = */ 4U,
    /* schdType       = */ OS_TASK_FULL,
    /* maxActivations = */ 100U,
    /* preTaskHook    = */ NULL_PTR,
    /* postTaskHook   = */ NULL_PTR,
    /* accessingApps  = */ (OS_SYSTEMAPPLICATION_OSCORE_CORE2_ACCESS |OS_APP_APPLICATION_CORE2_QM_ACCESS),
    /* taskId         = */ TASK_5MS_CORE2_QM,
    /* coreId         = */ OS_CORE_ID_2,
    /* taskType       = */ OS_TASK_BT,
    /* appMode        = */ OS_APPMODE_NONE
};
const Os_TaskCfgType OsCfg_Task_Task_10ms_Core2_QM =
{
    /* contextCfg     = */ &OsCfg_Arch_Context_Task_10ms_Core2_QM,
    /* ownerAppId     = */ APP_APPLICATION_CORE2_QM,
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC2) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* tpCfg      = */ NULL_PTR,
#endif
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC3) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* appMpCfg       = */ NULL_PTR,
    /* taskMpCfg      = */ NULL_PTR,
#endif
    /* taskDyn        = */ &OsCfg_Task_Task_10ms_Core2_QM_Dyn,
    /* cfgPrio        = */ 5U,
    /* schdType       = */ OS_TASK_FULL,
    /* maxActivations = */ 100U,
    /* preTaskHook    = */ NULL_PTR,
    /* postTaskHook   = */ NULL_PTR,
    /* accessingApps  = */ (OS_SYSTEMAPPLICATION_OSCORE_CORE2_ACCESS |OS_APP_APPLICATION_CORE2_QM_ACCESS),
    /* taskId         = */ TASK_10MS_CORE2_QM,
    /* coreId         = */ OS_CORE_ID_2,
    /* taskType       = */ OS_TASK_BT,
    /* appMode        = */ OS_APPMODE_NONE
};
const Os_TaskCfgType OsCfg_Task_Task_20ms_Core2_QM =
{
    /* contextCfg     = */ &OsCfg_Arch_Context_Task_20ms_Core2_QM,
    /* ownerAppId     = */ APP_APPLICATION_CORE2_QM,
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC2) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* tpCfg      = */ NULL_PTR,
#endif
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC3) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* appMpCfg       = */ NULL_PTR,
    /* taskMpCfg      = */ NULL_PTR,
#endif
    /* taskDyn        = */ &OsCfg_Task_Task_20ms_Core2_QM_Dyn,
    /* cfgPrio        = */ 6U,
    /* schdType       = */ OS_TASK_FULL,
    /* maxActivations = */ 100U,
    /* preTaskHook    = */ NULL_PTR,
    /* postTaskHook   = */ NULL_PTR,
    /* accessingApps  = */ (OS_SYSTEMAPPLICATION_OSCORE_CORE2_ACCESS |OS_APP_APPLICATION_CORE2_QM_ACCESS),
    /* taskId         = */ TASK_20MS_CORE2_QM,
    /* coreId         = */ OS_CORE_ID_2,
    /* taskType       = */ OS_TASK_BT,
    /* appMode        = */ OS_APPMODE_NONE
};
const Os_TaskCfgType OsCfg_Task_Task_50ms_Core2_QM =
{
    /* contextCfg     = */ &OsCfg_Arch_Context_Task_50ms_Core2_QM,
    /* ownerAppId     = */ APP_APPLICATION_CORE2_QM,
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC2) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* tpCfg      = */ NULL_PTR,
#endif
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC3) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* appMpCfg       = */ NULL_PTR,
    /* taskMpCfg      = */ NULL_PTR,
#endif
    /* taskDyn        = */ &OsCfg_Task_Task_50ms_Core2_QM_Dyn,
    /* cfgPrio        = */ 7U,
    /* schdType       = */ OS_TASK_FULL,
    /* maxActivations = */ 100U,
    /* preTaskHook    = */ NULL_PTR,
    /* postTaskHook   = */ NULL_PTR,
    /* accessingApps  = */ (OS_SYSTEMAPPLICATION_OSCORE_CORE2_ACCESS |OS_APP_APPLICATION_CORE2_QM_ACCESS),
    /* taskId         = */ TASK_50MS_CORE2_QM,
    /* coreId         = */ OS_CORE_ID_2,
    /* taskType       = */ OS_TASK_BT,
    /* appMode        = */ OS_APPMODE_NONE
};
const Os_TaskCfgType OsCfg_Task_Task_100ms_Core2_QM =
{
    /* contextCfg     = */ &OsCfg_Arch_Context_Task_100ms_Core2_QM,
    /* ownerAppId     = */ APP_APPLICATION_CORE2_QM,
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC2) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* tpCfg      = */ NULL_PTR,
#endif
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC3) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* appMpCfg       = */ NULL_PTR,
    /* taskMpCfg      = */ NULL_PTR,
#endif
    /* taskDyn        = */ &OsCfg_Task_Task_100ms_Core2_QM_Dyn,
    /* cfgPrio        = */ 8U,
    /* schdType       = */ OS_TASK_FULL,
    /* maxActivations = */ 100U,
    /* preTaskHook    = */ NULL_PTR,
    /* postTaskHook   = */ NULL_PTR,
    /* accessingApps  = */ (OS_SYSTEMAPPLICATION_OSCORE_CORE2_ACCESS |OS_APP_APPLICATION_CORE2_QM_ACCESS),
    /* taskId         = */ TASK_100MS_CORE2_QM,
    /* coreId         = */ OS_CORE_ID_2,
    /* taskType       = */ OS_TASK_BT,
    /* appMode        = */ OS_APPMODE_NONE
};
const Os_TaskCfgType OsCfg_Task_Task_200ms_Core2_QM =
{
    /* contextCfg     = */ &OsCfg_Arch_Context_Task_200ms_Core2_QM,
    /* ownerAppId     = */ APP_APPLICATION_CORE2_QM,
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC2) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* tpCfg      = */ NULL_PTR,
#endif
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC3) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* appMpCfg       = */ NULL_PTR,
    /* taskMpCfg      = */ NULL_PTR,
#endif
    /* taskDyn        = */ &OsCfg_Task_Task_200ms_Core2_QM_Dyn,
    /* cfgPrio        = */ 9U,
    /* schdType       = */ OS_TASK_FULL,
    /* maxActivations = */ 100U,
    /* preTaskHook    = */ NULL_PTR,
    /* postTaskHook   = */ NULL_PTR,
    /* accessingApps  = */ (OS_SYSTEMAPPLICATION_OSCORE_CORE2_ACCESS |OS_APP_APPLICATION_CORE2_QM_ACCESS),
    /* taskId         = */ TASK_200MS_CORE2_QM,
    /* coreId         = */ OS_CORE_ID_2,
    /* taskType       = */ OS_TASK_BT,
    /* appMode        = */ OS_APPMODE_NONE
};
const Os_TaskCfgType OsCfg_Task_Task_500ms_Core2_QM =
{
    /* contextCfg     = */ &OsCfg_Arch_Context_Task_500ms_Core2_QM,
    /* ownerAppId     = */ APP_APPLICATION_CORE2_QM,
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC2) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* tpCfg      = */ NULL_PTR,
#endif
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC3) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* appMpCfg       = */ NULL_PTR,
    /* taskMpCfg      = */ NULL_PTR,
#endif
    /* taskDyn        = */ &OsCfg_Task_Task_500ms_Core2_QM_Dyn,
    /* cfgPrio        = */ 10U,
    /* schdType       = */ OS_TASK_FULL,
    /* maxActivations = */ 100U,
    /* preTaskHook    = */ NULL_PTR,
    /* postTaskHook   = */ NULL_PTR,
    /* accessingApps  = */ (OS_SYSTEMAPPLICATION_OSCORE_CORE2_ACCESS |OS_APP_APPLICATION_CORE2_QM_ACCESS),
    /* taskId         = */ TASK_500MS_CORE2_QM,
    /* coreId         = */ OS_CORE_ID_2,
    /* taskType       = */ OS_TASK_BT,
    /* appMode        = */ OS_APPMODE_NONE
};
const Os_TaskCfgType OsCfg_Task_Task_1000ms_Core2_QM =
{
    /* contextCfg     = */ &OsCfg_Arch_Context_Task_1000ms_Core2_QM,
    /* ownerAppId     = */ APP_APPLICATION_CORE2_QM,
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC2) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* tpCfg      = */ NULL_PTR,
#endif
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC3) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* appMpCfg       = */ NULL_PTR,
    /* taskMpCfg      = */ NULL_PTR,
#endif
    /* taskDyn        = */ &OsCfg_Task_Task_1000ms_Core2_QM_Dyn,
    /* cfgPrio        = */ 11U,
    /* schdType       = */ OS_TASK_FULL,
    /* maxActivations = */ 100U,
    /* preTaskHook    = */ NULL_PTR,
    /* postTaskHook   = */ NULL_PTR,
    /* accessingApps  = */ (OS_SYSTEMAPPLICATION_OSCORE_CORE2_ACCESS |OS_APP_APPLICATION_CORE2_QM_ACCESS),
    /* taskId         = */ TASK_1000MS_CORE2_QM,
    /* coreId         = */ OS_CORE_ID_2,
    /* taskType       = */ OS_TASK_BT,
    /* appMode        = */ OS_APPMODE_NONE
};
/* Task config parameters end. */

/* Isr config parameters start. */
const Os_IsrCfgType OsCfg_Isr_CounterIsr_SystemTimer_Core0 =
{
    /* ifcounterIsr = */ TRUE,
    /* ifTpIsr     = */ FALSE,
    /* contextCfg  = */ &OsCfg_Arch_Context_CounterIsr_SystemTimer_Core0,
    /* ownerAppId  = */ SYSTEMAPPLICATION_OSCORE_CORE0,
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC2) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* tpCfg   = */ NULL_PTR,
#endif
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC3) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* appMpCfg    = */ NULL_PTR,
    /* isrMpCfg    = */ NULL_PTR,
#endif
    /* isrDyn      = */ &OsCfg_Isr_CounterIsr_SystemTimer_Core0_Dyn,
    /* source      = */ &OsCfg_Arch_Source_CounterIsr_SystemTimer_Core0,
    /* coreId      = */ OS_CORE_ID_0,
    /* isrId       = */ COUNTERISR_SYSTEMTIMER_CORE0,
    /* counterId   = */ SYSTEMTIMER_CORE0
};
const Os_IsrCfgType OsCfg_Isr_MultiCommIsr_OsCore_Core0 =
{
    /* ifcounterIsr = */ FALSE,
    /* ifTpIsr     = */ FALSE,
    /* contextCfg  = */ &OsCfg_Arch_Context_MultiCommIsr_OsCore_Core0,
    /* ownerAppId  = */ SYSTEMAPPLICATION_OSCORE_CORE0,
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC2) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* tpCfg   = */ NULL_PTR,
#endif
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC3) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* appMpCfg    = */ NULL_PTR,
    /* isrMpCfg    = */ NULL_PTR,
#endif
    /* isrDyn      = */ &OsCfg_Isr_MultiCommIsr_OsCore_Core0_Dyn,
    /* source      = */ &OsCfg_Arch_Source_MultiCommIsr_OsCore_Core0,
    /* coreId      = */ OS_CORE_ID_0,
    /* isrId       = */ MULTICOMMISR_OSCORE_CORE0,
    /* counterId   = */ ((CounterType)0U)
};
const Os_IsrCfgType OsCfg_Isr_Os_Monitor_Isr =
{
    /* ifcounterIsr = */ TRUE,
    /* ifTpIsr     = */ FALSE,
    /* contextCfg  = */ &OsCfg_Arch_Context_Os_Monitor_Isr,
    /* ownerAppId  = */ SYSTEMAPPLICATION_OSCORE_CORE0,
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC2) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* tpCfg   = */ NULL_PTR,
#endif
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC3) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* appMpCfg    = */ NULL_PTR,
    /* isrMpCfg    = */ NULL_PTR,
#endif
    /* isrDyn      = */ &OsCfg_Isr_Os_Monitor_Isr_Dyn,
    /* source      = */ &OsCfg_Arch_Source_Os_Monitor_Isr,
    /* coreId      = */ OS_CORE_ID_0,
    /* isrId       = */ OS_MONITOR_ISR,
    /* counterId   = */ OS_MONITOR_COUNTER
};
const Os_IsrCfgType OsCfg_Isr_CounterIsr_SystemTimer_Core1 =
{
    /* ifcounterIsr = */ TRUE,
    /* ifTpIsr     = */ FALSE,
    /* contextCfg  = */ &OsCfg_Arch_Context_CounterIsr_SystemTimer_Core1,
    /* ownerAppId  = */ SYSTEMAPPLICATION_OSCORE_CORE1,
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC2) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* tpCfg   = */ NULL_PTR,
#endif
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC3) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* appMpCfg    = */ NULL_PTR,
    /* isrMpCfg    = */ NULL_PTR,
#endif
    /* isrDyn      = */ &OsCfg_Isr_CounterIsr_SystemTimer_Core1_Dyn,
    /* source      = */ &OsCfg_Arch_Source_CounterIsr_SystemTimer_Core1,
    /* coreId      = */ OS_CORE_ID_1,
    /* isrId       = */ COUNTERISR_SYSTEMTIMER_CORE1,
    /* counterId   = */ SYSTEMTIMER_CORE1
};
const Os_IsrCfgType OsCfg_Isr_MultiCommIsr_OsCore_Core1 =
{
    /* ifcounterIsr = */ FALSE,
    /* ifTpIsr     = */ FALSE,
    /* contextCfg  = */ &OsCfg_Arch_Context_MultiCommIsr_OsCore_Core1,
    /* ownerAppId  = */ SYSTEMAPPLICATION_OSCORE_CORE1,
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC2) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* tpCfg   = */ NULL_PTR,
#endif
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC3) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* appMpCfg    = */ NULL_PTR,
    /* isrMpCfg    = */ NULL_PTR,
#endif
    /* isrDyn      = */ &OsCfg_Isr_MultiCommIsr_OsCore_Core1_Dyn,
    /* source      = */ &OsCfg_Arch_Source_MultiCommIsr_OsCore_Core1,
    /* coreId      = */ OS_CORE_ID_1,
    /* isrId       = */ MULTICOMMISR_OSCORE_CORE1,
    /* counterId   = */ ((CounterType)0U)
};
const Os_IsrCfgType OsCfg_Isr_CounterIsr_SystemTimer_Core2 =
{
    /* ifcounterIsr = */ TRUE,
    /* ifTpIsr     = */ FALSE,
    /* contextCfg  = */ &OsCfg_Arch_Context_CounterIsr_SystemTimer_Core2,
    /* ownerAppId  = */ SYSTEMAPPLICATION_OSCORE_CORE2,
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC2) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* tpCfg   = */ NULL_PTR,
#endif
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC3) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* appMpCfg    = */ NULL_PTR,
    /* isrMpCfg    = */ NULL_PTR,
#endif
    /* isrDyn      = */ &OsCfg_Isr_CounterIsr_SystemTimer_Core2_Dyn,
    /* source      = */ &OsCfg_Arch_Source_CounterIsr_SystemTimer_Core2,
    /* coreId      = */ OS_CORE_ID_2,
    /* isrId       = */ COUNTERISR_SYSTEMTIMER_CORE2,
    /* counterId   = */ SYSTEMTIMER_CORE2
};
const Os_IsrCfgType OsCfg_Isr_MultiCommIsr_OsCore_Core2 =
{
    /* ifcounterIsr = */ FALSE,
    /* ifTpIsr     = */ FALSE,
    /* contextCfg  = */ &OsCfg_Arch_Context_MultiCommIsr_OsCore_Core2,
    /* ownerAppId  = */ SYSTEMAPPLICATION_OSCORE_CORE2,
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC2) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* tpCfg   = */ NULL_PTR,
#endif
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC3) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* appMpCfg    = */ NULL_PTR,
    /* isrMpCfg    = */ NULL_PTR,
#endif
    /* isrDyn      = */ &OsCfg_Isr_MultiCommIsr_OsCore_Core2_Dyn,
    /* source      = */ &OsCfg_Arch_Source_MultiCommIsr_OsCore_Core2,
    /* coreId      = */ OS_CORE_ID_2,
    /* isrId       = */ MULTICOMMISR_OSCORE_CORE2,
    /* counterId   = */ ((CounterType)0U)
};
const Os_IsrCfgType OsCfg_Isr_FlashDone_Isr =
{
    /* ifcounterIsr = */ FALSE,
    /* ifTpIsr     = */ FALSE,
    /* contextCfg  = */ &OsCfg_Arch_Context_FlashDone_Isr,
    /* ownerAppId  = */ SYSTEMAPPLICATION_OSCORE_CORE2,
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC2) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* tpCfg   = */ NULL_PTR,
#endif
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC3) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* appMpCfg    = */ NULL_PTR,
    /* isrMpCfg    = */ NULL_PTR,
#endif
    /* isrDyn      = */ &OsCfg_Isr_FlashDone_Isr_Dyn,
    /* source      = */ &OsCfg_Arch_Source_FlashDone_Isr,
    /* coreId      = */ OS_CORE_ID_2,
    /* isrId       = */ FLASHDONE_ISR,
    /* counterId   = */ ((CounterType)0U)
};
const Os_IsrCfgType OsCfg_Isr_PIT0_CH4 =
{
    /* ifcounterIsr = */ FALSE,
    /* ifTpIsr     = */ FALSE,
    /* contextCfg  = */ &OsCfg_Arch_Context_PIT0_CH4,
    /* ownerAppId  = */ SYSTEMAPPLICATION_OSCORE_CORE2,
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC2) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* tpCfg   = */ NULL_PTR,
#endif
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC3) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* appMpCfg    = */ NULL_PTR,
    /* isrMpCfg    = */ NULL_PTR,
#endif
    /* isrDyn      = */ &OsCfg_Isr_PIT0_CH4_Dyn,
    /* source      = */ &OsCfg_Arch_Source_PIT0_CH4,
    /* coreId      = */ OS_CORE_ID_2,
    /* isrId       = */ PIT0_CH4,
    /* counterId   = */ ((CounterType)0U)
};
const Os_IsrCfgType OsCfg_Isr_PIT0_CH5 =
{
    /* ifcounterIsr = */ FALSE,
    /* ifTpIsr     = */ FALSE,
    /* contextCfg  = */ &OsCfg_Arch_Context_PIT0_CH5,
    /* ownerAppId  = */ SYSTEMAPPLICATION_OSCORE_CORE2,
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC2) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* tpCfg   = */ NULL_PTR,
#endif
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC3) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* appMpCfg    = */ NULL_PTR,
    /* isrMpCfg    = */ NULL_PTR,
#endif
    /* isrDyn      = */ &OsCfg_Isr_PIT0_CH5_Dyn,
    /* source      = */ &OsCfg_Arch_Source_PIT0_CH5,
    /* coreId      = */ OS_CORE_ID_2,
    /* isrId       = */ PIT0_CH5,
    /* counterId   = */ ((CounterType)0U)
};
const Os_IsrCfgType OsCfg_Isr_PIT0_CH6 =
{
    /* ifcounterIsr = */ FALSE,
    /* ifTpIsr     = */ FALSE,
    /* contextCfg  = */ &OsCfg_Arch_Context_PIT0_CH6,
    /* ownerAppId  = */ SYSTEMAPPLICATION_OSCORE_CORE2,
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC2) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* tpCfg   = */ NULL_PTR,
#endif
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC3) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* appMpCfg    = */ NULL_PTR,
    /* isrMpCfg    = */ NULL_PTR,
#endif
    /* isrDyn      = */ &OsCfg_Isr_PIT0_CH6_Dyn,
    /* source      = */ &OsCfg_Arch_Source_PIT0_CH6,
    /* coreId      = */ OS_CORE_ID_2,
    /* isrId       = */ PIT0_CH6,
    /* counterId   = */ ((CounterType)0U)
};
const Os_IsrCfgType OsCfg_Isr_Can1_Isr =
{
    /* ifcounterIsr = */ FALSE,
    /* ifTpIsr     = */ FALSE,
    /* contextCfg  = */ &OsCfg_Arch_Context_Can1_Isr,
    /* ownerAppId  = */ SYSTEMAPPLICATION_OSCORE_CORE2,
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC2) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* tpCfg   = */ NULL_PTR,
#endif
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC3) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* appMpCfg    = */ NULL_PTR,
    /* isrMpCfg    = */ NULL_PTR,
#endif
    /* isrDyn      = */ &OsCfg_Isr_Can1_Isr_Dyn,
    /* source      = */ &OsCfg_Arch_Source_Can1_Isr,
    /* coreId      = */ OS_CORE_ID_2,
    /* isrId       = */ CAN1_ISR,
    /* counterId   = */ ((CounterType)0U)
};
const Os_IsrCfgType OsCfg_Isr_Can2_Isr =
{
    /* ifcounterIsr = */ FALSE,
    /* ifTpIsr     = */ FALSE,
    /* contextCfg  = */ &OsCfg_Arch_Context_Can2_Isr,
    /* ownerAppId  = */ SYSTEMAPPLICATION_OSCORE_CORE2,
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC2) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* tpCfg   = */ NULL_PTR,
#endif
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC3) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* appMpCfg    = */ NULL_PTR,
    /* isrMpCfg    = */ NULL_PTR,
#endif
    /* isrDyn      = */ &OsCfg_Isr_Can2_Isr_Dyn,
    /* source      = */ &OsCfg_Arch_Source_Can2_Isr,
    /* coreId      = */ OS_CORE_ID_2,
    /* isrId       = */ CAN2_ISR,
    /* counterId   = */ ((CounterType)0U)
};
const Os_IsrCfgType OsCfg_Isr_Can3_Isr =
{
    /* ifcounterIsr = */ FALSE,
    /* ifTpIsr     = */ FALSE,
    /* contextCfg  = */ &OsCfg_Arch_Context_Can3_Isr,
    /* ownerAppId  = */ SYSTEMAPPLICATION_OSCORE_CORE2,
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC2) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* tpCfg   = */ NULL_PTR,
#endif
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC3) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* appMpCfg    = */ NULL_PTR,
    /* isrMpCfg    = */ NULL_PTR,
#endif
    /* isrDyn      = */ &OsCfg_Isr_Can3_Isr_Dyn,
    /* source      = */ &OsCfg_Arch_Source_Can3_Isr,
    /* coreId      = */ OS_CORE_ID_2,
    /* isrId       = */ CAN3_ISR,
    /* counterId   = */ ((CounterType)0U)
};
const Os_IsrCfgType OsCfg_Isr_Can4_Isr =
{
    /* ifcounterIsr = */ FALSE,
    /* ifTpIsr     = */ FALSE,
    /* contextCfg  = */ &OsCfg_Arch_Context_Can4_Isr,
    /* ownerAppId  = */ SYSTEMAPPLICATION_OSCORE_CORE2,
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC2) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* tpCfg   = */ NULL_PTR,
#endif
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC3) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* appMpCfg    = */ NULL_PTR,
    /* isrMpCfg    = */ NULL_PTR,
#endif
    /* isrDyn      = */ &OsCfg_Isr_Can4_Isr_Dyn,
    /* source      = */ &OsCfg_Arch_Source_Can4_Isr,
    /* coreId      = */ OS_CORE_ID_2,
    /* isrId       = */ CAN4_ISR,
    /* counterId   = */ ((CounterType)0U)
};
const Os_IsrCfgType OsCfg_Isr_Adc89_Grp0_Isr =
{
    /* ifcounterIsr = */ FALSE,
    /* ifTpIsr     = */ FALSE,
    /* contextCfg  = */ &OsCfg_Arch_Context_Adc89_Grp0_Isr,
    /* ownerAppId  = */ SYSTEMAPPLICATION_OSCORE_CORE2,
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC2) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* tpCfg   = */ NULL_PTR,
#endif
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC3) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* appMpCfg    = */ NULL_PTR,
    /* isrMpCfg    = */ NULL_PTR,
#endif
    /* isrDyn      = */ &OsCfg_Isr_Adc89_Grp0_Isr_Dyn,
    /* source      = */ &OsCfg_Arch_Source_Adc89_Grp0_Isr,
    /* coreId      = */ OS_CORE_ID_2,
    /* isrId       = */ ADC89_GRP0_ISR,
    /* counterId   = */ ((CounterType)0U)
};
const Os_IsrCfgType OsCfg_Isr_Adc89_Grp1_Isr =
{
    /* ifcounterIsr = */ FALSE,
    /* ifTpIsr     = */ FALSE,
    /* contextCfg  = */ &OsCfg_Arch_Context_Adc89_Grp1_Isr,
    /* ownerAppId  = */ SYSTEMAPPLICATION_OSCORE_CORE2,
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC2) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* tpCfg   = */ NULL_PTR,
#endif
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC3) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* appMpCfg    = */ NULL_PTR,
    /* isrMpCfg    = */ NULL_PTR,
#endif
    /* isrDyn      = */ &OsCfg_Isr_Adc89_Grp1_Isr_Dyn,
    /* source      = */ &OsCfg_Arch_Source_Adc89_Grp1_Isr,
    /* coreId      = */ OS_CORE_ID_2,
    /* isrId       = */ ADC89_GRP1_ISR,
    /* counterId   = */ ((CounterType)0U)
};
const Os_IsrCfgType OsCfg_Isr_Adc89_Grp2_Isr =
{
    /* ifcounterIsr = */ FALSE,
    /* ifTpIsr     = */ FALSE,
    /* contextCfg  = */ &OsCfg_Arch_Context_Adc89_Grp2_Isr,
    /* ownerAppId  = */ SYSTEMAPPLICATION_OSCORE_CORE2,
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC2) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* tpCfg   = */ NULL_PTR,
#endif
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC3) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* appMpCfg    = */ NULL_PTR,
    /* isrMpCfg    = */ NULL_PTR,
#endif
    /* isrDyn      = */ &OsCfg_Isr_Adc89_Grp2_Isr_Dyn,
    /* source      = */ &OsCfg_Arch_Source_Adc89_Grp2_Isr,
    /* coreId      = */ OS_CORE_ID_2,
    /* isrId       = */ ADC89_GRP2_ISR,
    /* counterId   = */ ((CounterType)0U)
};
const Os_IsrCfgType OsCfg_Isr_Adc89_Grp3_Isr =
{
    /* ifcounterIsr = */ FALSE,
    /* ifTpIsr     = */ FALSE,
    /* contextCfg  = */ &OsCfg_Arch_Context_Adc89_Grp3_Isr,
    /* ownerAppId  = */ SYSTEMAPPLICATION_OSCORE_CORE2,
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC2) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* tpCfg   = */ NULL_PTR,
#endif
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC3) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* appMpCfg    = */ NULL_PTR,
    /* isrMpCfg    = */ NULL_PTR,
#endif
    /* isrDyn      = */ &OsCfg_Isr_Adc89_Grp3_Isr_Dyn,
    /* source      = */ &OsCfg_Arch_Source_Adc89_Grp3_Isr,
    /* coreId      = */ OS_CORE_ID_2,
    /* isrId       = */ ADC89_GRP3_ISR,
    /* counterId   = */ ((CounterType)0U)
};
const Os_IsrCfgType OsCfg_Isr_Adc89_Grp4_Isr =
{
    /* ifcounterIsr = */ FALSE,
    /* ifTpIsr     = */ FALSE,
    /* contextCfg  = */ &OsCfg_Arch_Context_Adc89_Grp4_Isr,
    /* ownerAppId  = */ SYSTEMAPPLICATION_OSCORE_CORE2,
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC2) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* tpCfg   = */ NULL_PTR,
#endif
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC3) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* appMpCfg    = */ NULL_PTR,
    /* isrMpCfg    = */ NULL_PTR,
#endif
    /* isrDyn      = */ &OsCfg_Isr_Adc89_Grp4_Isr_Dyn,
    /* source      = */ &OsCfg_Arch_Source_Adc89_Grp4_Isr,
    /* coreId      = */ OS_CORE_ID_2,
    /* isrId       = */ ADC89_GRP4_ISR,
    /* counterId   = */ ((CounterType)0U)
};
const Os_IsrCfgType OsCfg_Isr_Adc89_Grp5_Isr =
{
    /* ifcounterIsr = */ FALSE,
    /* ifTpIsr     = */ FALSE,
    /* contextCfg  = */ &OsCfg_Arch_Context_Adc89_Grp5_Isr,
    /* ownerAppId  = */ SYSTEMAPPLICATION_OSCORE_CORE2,
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC2) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* tpCfg   = */ NULL_PTR,
#endif
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC3) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* appMpCfg    = */ NULL_PTR,
    /* isrMpCfg    = */ NULL_PTR,
#endif
    /* isrDyn      = */ &OsCfg_Isr_Adc89_Grp5_Isr_Dyn,
    /* source      = */ &OsCfg_Arch_Source_Adc89_Grp5_Isr,
    /* coreId      = */ OS_CORE_ID_2,
    /* isrId       = */ ADC89_GRP5_ISR,
    /* counterId   = */ ((CounterType)0U)
};
const Os_IsrCat1CfgType OsCfg_Cat1Isr_GTM_ATOM10 =
{
    /* source    = */ &OsCfg_Arch_Source_GTM_ATOM10,
    /* coreId    = */ OS_CORE_ID_0
};
const Os_IsrCat1CfgType OsCfg_Cat1Isr_SIUL_External_Interrupt_0 =
{
    /* source    = */ &OsCfg_Arch_Source_SIUL_External_Interrupt_0,
    /* coreId    = */ OS_CORE_ID_0
};
const Os_IsrCat1CfgType OsCfg_Cat1Isr_SIUL_External_Interrupt_1 =
{
    /* source    = */ &OsCfg_Arch_Source_SIUL_External_Interrupt_1,
    /* coreId    = */ OS_CORE_ID_0
};
const Os_IsrCat1CfgType OsCfg_Cat1Isr_EDMA_CH80 =
{
    /* source    = */ &OsCfg_Arch_Source_EDMA_CH80,
    /* coreId    = */ OS_CORE_ID_0
};
const Os_IsrCat1CfgType OsCfg_Cat1Isr_GTM_ATOM40 =
{
    /* source    = */ &OsCfg_Arch_Source_GTM_ATOM40,
    /* coreId    = */ OS_CORE_ID_1
};
/* Isr config parameters end. */

/* Counter config parameters start. */
const Os_CounterPitCfgType OsCfg_Counter_SystemTimer_Core0 =
{
    {
        /* counterBase->Os_CntExpList = */ &Os_CntExpList_SystemTimer_Core0,
        /* counterBase->maxAllowValue = */ 0x3FFFFFFFU,
        /* counterBase->minCycle      = */ 1U,
        /* counterBase->ticksPerBase  = */ 1U,
        /* counterBase->counterType   = */ OS_COUNTER_PIT,
        /* counterBase->coreId        = */ OS_CORE_ID_0,
        /* counterBase->ownerAppId    = */ SYSTEMAPPLICATION_OSCORE_CORE0,
        /* counterBase->counterId     = */ SYSTEMTIMER_CORE0,
        /* counterBase->accessingApps = */ (OS_SYSTEMAPPLICATION_OSCORE_CORE0_ACCESS |OS_APP_APPLICATION_CORE0_QM_ACCESS)
    },
    /* counterDyn                     = */ &OsCfg_Counter_SystemTimer_Core0_Dyn,
    /* HwConfig                       = */ &OsCfg_Arch_TimerPit_SystemTimer_Core0
};
const Os_CounterPitCfgType OsCfg_Counter_SystemTimer_Core1 =
{
    {
        /* counterBase->Os_CntExpList = */ &Os_CntExpList_SystemTimer_Core1,
        /* counterBase->maxAllowValue = */ 0x3FFFFFFFU,
        /* counterBase->minCycle      = */ 1U,
        /* counterBase->ticksPerBase  = */ 1U,
        /* counterBase->counterType   = */ OS_COUNTER_PIT,
        /* counterBase->coreId        = */ OS_CORE_ID_1,
        /* counterBase->ownerAppId    = */ SYSTEMAPPLICATION_OSCORE_CORE1,
        /* counterBase->counterId     = */ SYSTEMTIMER_CORE1,
        /* counterBase->accessingApps = */ (OS_SYSTEMAPPLICATION_OSCORE_CORE1_ACCESS |OS_APP_APPLICATION_CORE1_QM_ACCESS)
    },
    /* counterDyn                     = */ &OsCfg_Counter_SystemTimer_Core1_Dyn,
    /* HwConfig                       = */ &OsCfg_Arch_TimerPit_SystemTimer_Core1
};
const Os_CounterPitCfgType OsCfg_Counter_SystemTimer_Core2 =
{
    {
        /* counterBase->Os_CntExpList = */ &Os_CntExpList_SystemTimer_Core2,
        /* counterBase->maxAllowValue = */ 0x3FFFFFFFU,
        /* counterBase->minCycle      = */ 1U,
        /* counterBase->ticksPerBase  = */ 1U,
        /* counterBase->counterType   = */ OS_COUNTER_PIT,
        /* counterBase->coreId        = */ OS_CORE_ID_2,
        /* counterBase->ownerAppId    = */ SYSTEMAPPLICATION_OSCORE_CORE2,
        /* counterBase->counterId     = */ SYSTEMTIMER_CORE2,
        /* counterBase->accessingApps = */ (OS_SYSTEMAPPLICATION_OSCORE_CORE2_ACCESS |OS_APP_APPLICATION_CORE2_QM_ACCESS)
    },
    /* counterDyn                     = */ &OsCfg_Counter_SystemTimer_Core2_Dyn,
    /* HwConfig                       = */ &OsCfg_Arch_TimerPit_SystemTimer_Core2
};
const Os_CounterHrtCfgType OsCfg_Counter_Os_Monitor_Counter =
{
    {
        /* counterBase->Os_CntExpList = */ NULL_PTR,
        /* counterBase->maxAllowValue = */ 0xFFFFFFFFU,
        /* counterBase->minCycle      = */ 1U,
        /* counterBase->ticksPerBase  = */ 1U,
        /* counterBase->counterType   = */ OS_COUNTER_HRT,
        /* counterBase->coreId        = */ OS_CORE_ID_0,
        /* counterBase->ownerAppId    = */ SYSTEMAPPLICATION_OSCORE_CORE0,
        /* counterBase->counterId     = */ OS_MONITOR_COUNTER,
        /* counterBase->accessingApps = */ (OS_SYSTEMAPPLICATION_OSCORE_CORE0_ACCESS |OS_APP_APPLICATION_CORE0_QM_ACCESS)
    },
    /* counterDyn                     = */ &OsCfg_Counter_Os_Monitor_Counter_Dyn,
    /* HwConfig                       = */ &OsCfg_Arch_TimerHrt_Os_Monitor_Counter
};
/* Counter config parameters end. */

/* Alarm config parameters start. */
const Os_AlarmCfgType OsCfg_Alarm_Rte_Al_TE_Task_10ms_Core0_QM_10ms =
{
    /* alarmMode      = */ OS_ALARM_REL,
    /* appMode        = */ OS_APPMODE_NONE,
    /* counter        = */ (const Os_CounterBaseCfgType*)&OsCfg_Counter_SystemTimer_Core0,
    /* cntExpKind     = */ OS_CNTEXP_ALRM_AT,
    {
        /* workParam  = */ .taskId = TASK_10MS_CORE0_QM
    },
    /* alarmDyn       = */ &OsCfg_Alarm_Rte_Al_TE_Task_10ms_Core0_QM_10ms_Dyn,
    /* accessingApps  = */ (OS_SYSTEMAPPLICATION_OSCORE_CORE0_ACCESS |OS_SYSTEMAPPLICATION_OSCORE_CORE1_ACCESS |
                          OS_SYSTEMAPPLICATION_OSCORE_CORE2_ACCESS |OS_APP_APPLICATION_CORE0_QM_ACCESS),
    /* ownerAppId     = */ APP_APPLICATION_CORE0_QM,
    /* coreId         = */ OS_CORE_ID_0,
    /* alarmTime      = */ 1U,
    /* autoCycle      = */ 1U,
    /* alarm_CallBack = */ NULL_PTR,
    /* alarmId        = */ RTE_AL_TE_TASK_10MS_CORE0_QM_10MS
};
const Os_AlarmCfgType OsCfg_Alarm_Rte_Al_TE_Task_20ms_Core0_QM_20ms =
{
    /* alarmMode      = */ OS_ALARM_REL,
    /* appMode        = */ OS_APPMODE_NONE,
    /* counter        = */ (const Os_CounterBaseCfgType*)&OsCfg_Counter_SystemTimer_Core0,
    /* cntExpKind     = */ OS_CNTEXP_ALRM_AT,
    {
        /* workParam  = */ .taskId = TASK_20MS_CORE0_QM
    },
    /* alarmDyn       = */ &OsCfg_Alarm_Rte_Al_TE_Task_20ms_Core0_QM_20ms_Dyn,
    /* accessingApps  = */ (OS_SYSTEMAPPLICATION_OSCORE_CORE0_ACCESS |OS_SYSTEMAPPLICATION_OSCORE_CORE1_ACCESS |
                          OS_SYSTEMAPPLICATION_OSCORE_CORE2_ACCESS |OS_APP_APPLICATION_CORE0_QM_ACCESS),
    /* ownerAppId     = */ APP_APPLICATION_CORE0_QM,
    /* coreId         = */ OS_CORE_ID_0,
    /* alarmTime      = */ 1U,
    /* autoCycle      = */ 1U,
    /* alarm_CallBack = */ NULL_PTR,
    /* alarmId        = */ RTE_AL_TE_TASK_20MS_CORE0_QM_20MS
};
const Os_AlarmCfgType OsCfg_Alarm_Rte_Al_TE_Task_50ms_Core0_QM_50ms =
{
    /* alarmMode      = */ OS_ALARM_REL,
    /* appMode        = */ OS_APPMODE_NONE,
    /* counter        = */ (const Os_CounterBaseCfgType*)&OsCfg_Counter_SystemTimer_Core0,
    /* cntExpKind     = */ OS_CNTEXP_ALRM_AT,
    {
        /* workParam  = */ .taskId = TASK_50MS_CORE0_QM
    },
    /* alarmDyn       = */ &OsCfg_Alarm_Rte_Al_TE_Task_50ms_Core0_QM_50ms_Dyn,
    /* accessingApps  = */ (OS_SYSTEMAPPLICATION_OSCORE_CORE0_ACCESS |OS_SYSTEMAPPLICATION_OSCORE_CORE1_ACCESS |
                          OS_SYSTEMAPPLICATION_OSCORE_CORE2_ACCESS |OS_APP_APPLICATION_CORE0_QM_ACCESS),
    /* ownerAppId     = */ APP_APPLICATION_CORE0_QM,
    /* coreId         = */ OS_CORE_ID_0,
    /* alarmTime      = */ 1U,
    /* autoCycle      = */ 1U,
    /* alarm_CallBack = */ NULL_PTR,
    /* alarmId        = */ RTE_AL_TE_TASK_50MS_CORE0_QM_50MS
};
const Os_AlarmCfgType OsCfg_Alarm_Rte_Al_TE_Task_100ms_Core0_QM_100ms =
{
    /* alarmMode      = */ OS_ALARM_REL,
    /* appMode        = */ OS_APPMODE_NONE,
    /* counter        = */ (const Os_CounterBaseCfgType*)&OsCfg_Counter_SystemTimer_Core0,
    /* cntExpKind     = */ OS_CNTEXP_ALRM_AT,
    {
        /* workParam  = */ .taskId = TASK_100MS_CORE0_QM
    },
    /* alarmDyn       = */ &OsCfg_Alarm_Rte_Al_TE_Task_100ms_Core0_QM_100ms_Dyn,
    /* accessingApps  = */ (OS_SYSTEMAPPLICATION_OSCORE_CORE0_ACCESS |OS_SYSTEMAPPLICATION_OSCORE_CORE1_ACCESS |
                          OS_SYSTEMAPPLICATION_OSCORE_CORE2_ACCESS |OS_APP_APPLICATION_CORE0_QM_ACCESS),
    /* ownerAppId     = */ APP_APPLICATION_CORE0_QM,
    /* coreId         = */ OS_CORE_ID_0,
    /* alarmTime      = */ 1U,
    /* autoCycle      = */ 1U,
    /* alarm_CallBack = */ NULL_PTR,
    /* alarmId        = */ RTE_AL_TE_TASK_100MS_CORE0_QM_100MS
};
const Os_AlarmCfgType OsCfg_Alarm_Rte_Al_TE_Task_200ms_Core0_QM_200ms =
{
    /* alarmMode      = */ OS_ALARM_REL,
    /* appMode        = */ OS_APPMODE_NONE,
    /* counter        = */ (const Os_CounterBaseCfgType*)&OsCfg_Counter_SystemTimer_Core0,
    /* cntExpKind     = */ OS_CNTEXP_ALRM_AT,
    {
        /* workParam  = */ .taskId = TASK_200MS_CORE0_QM
    },
    /* alarmDyn       = */ &OsCfg_Alarm_Rte_Al_TE_Task_200ms_Core0_QM_200ms_Dyn,
    /* accessingApps  = */ (OS_SYSTEMAPPLICATION_OSCORE_CORE0_ACCESS |OS_SYSTEMAPPLICATION_OSCORE_CORE1_ACCESS |
                          OS_SYSTEMAPPLICATION_OSCORE_CORE2_ACCESS |OS_APP_APPLICATION_CORE0_QM_ACCESS),
    /* ownerAppId     = */ APP_APPLICATION_CORE0_QM,
    /* coreId         = */ OS_CORE_ID_0,
    /* alarmTime      = */ 1U,
    /* autoCycle      = */ 1U,
    /* alarm_CallBack = */ NULL_PTR,
    /* alarmId        = */ RTE_AL_TE_TASK_200MS_CORE0_QM_200MS
};
const Os_AlarmCfgType OsCfg_Alarm_Rte_Al_TE_Task_500ms_Core0_QM_500ms =
{
    /* alarmMode      = */ OS_ALARM_REL,
    /* appMode        = */ OS_APPMODE_NONE,
    /* counter        = */ (const Os_CounterBaseCfgType*)&OsCfg_Counter_SystemTimer_Core0,
    /* cntExpKind     = */ OS_CNTEXP_ALRM_AT,
    {
        /* workParam  = */ .taskId = TASK_500MS_CORE0_QM
    },
    /* alarmDyn       = */ &OsCfg_Alarm_Rte_Al_TE_Task_500ms_Core0_QM_500ms_Dyn,
    /* accessingApps  = */ (OS_SYSTEMAPPLICATION_OSCORE_CORE0_ACCESS |OS_SYSTEMAPPLICATION_OSCORE_CORE1_ACCESS |
                          OS_SYSTEMAPPLICATION_OSCORE_CORE2_ACCESS |OS_APP_APPLICATION_CORE0_QM_ACCESS),
    /* ownerAppId     = */ APP_APPLICATION_CORE0_QM,
    /* coreId         = */ OS_CORE_ID_0,
    /* alarmTime      = */ 1U,
    /* autoCycle      = */ 1U,
    /* alarm_CallBack = */ NULL_PTR,
    /* alarmId        = */ RTE_AL_TE_TASK_500MS_CORE0_QM_500MS
};
const Os_AlarmCfgType OsCfg_Alarm_Rte_Al_TE_Task_1000ms_Core0_QM_1000ms =
{
    /* alarmMode      = */ OS_ALARM_REL,
    /* appMode        = */ OS_APPMODE_NONE,
    /* counter        = */ (const Os_CounterBaseCfgType*)&OsCfg_Counter_SystemTimer_Core0,
    /* cntExpKind     = */ OS_CNTEXP_ALRM_AT,
    {
        /* workParam  = */ .taskId = TASK_1000MS_CORE0_QM
    },
    /* alarmDyn       = */ &OsCfg_Alarm_Rte_Al_TE_Task_1000ms_Core0_QM_1000ms_Dyn,
    /* accessingApps  = */ (OS_SYSTEMAPPLICATION_OSCORE_CORE0_ACCESS |OS_SYSTEMAPPLICATION_OSCORE_CORE1_ACCESS |
                          OS_SYSTEMAPPLICATION_OSCORE_CORE2_ACCESS |OS_APP_APPLICATION_CORE0_QM_ACCESS),
    /* ownerAppId     = */ APP_APPLICATION_CORE0_QM,
    /* coreId         = */ OS_CORE_ID_0,
    /* alarmTime      = */ 1U,
    /* autoCycle      = */ 1U,
    /* alarm_CallBack = */ NULL_PTR,
    /* alarmId        = */ RTE_AL_TE_TASK_1000MS_CORE0_QM_1000MS
};
const Os_AlarmCfgType OsCfg_Alarm_Rte_Al_TE_Task_2ms_Core0_QM_2ms =
{
    /* alarmMode      = */ OS_ALARM_REL,
    /* appMode        = */ OS_APPMODE_NONE,
    /* counter        = */ (const Os_CounterBaseCfgType*)&OsCfg_Counter_SystemTimer_Core0,
    /* cntExpKind     = */ OS_CNTEXP_ALRM_AT,
    {
        /* workParam  = */ .taskId = TASK_2MS_CORE0_QM
    },
    /* alarmDyn       = */ &OsCfg_Alarm_Rte_Al_TE_Task_2ms_Core0_QM_2ms_Dyn,
    /* accessingApps  = */ (OS_SYSTEMAPPLICATION_OSCORE_CORE0_ACCESS |OS_SYSTEMAPPLICATION_OSCORE_CORE1_ACCESS |
                          OS_SYSTEMAPPLICATION_OSCORE_CORE2_ACCESS |OS_APP_APPLICATION_CORE0_QM_ACCESS),
    /* ownerAppId     = */ APP_APPLICATION_CORE0_QM,
    /* coreId         = */ OS_CORE_ID_0,
    /* alarmTime      = */ 1U,
    /* autoCycle      = */ 1U,
    /* alarm_CallBack = */ NULL_PTR,
    /* alarmId        = */ RTE_AL_TE_TASK_2MS_CORE0_QM_2MS
};
const Os_AlarmCfgType OsCfg_Alarm_Rte_Al_TE_Task_5ms_Core1_QM_5ms =
{
    /* alarmMode      = */ OS_ALARM_REL,
    /* appMode        = */ OS_APPMODE_NONE,
    /* counter        = */ (const Os_CounterBaseCfgType*)&OsCfg_Counter_SystemTimer_Core1,
    /* cntExpKind     = */ OS_CNTEXP_ALRM_AT,
    {
        /* workParam  = */ .taskId = TASK_5MS_CORE1_QM
    },
    /* alarmDyn       = */ &OsCfg_Alarm_Rte_Al_TE_Task_5ms_Core1_QM_5ms_Dyn,
    /* accessingApps  = */ (OS_SYSTEMAPPLICATION_OSCORE_CORE0_ACCESS |OS_SYSTEMAPPLICATION_OSCORE_CORE1_ACCESS |
                          OS_SYSTEMAPPLICATION_OSCORE_CORE2_ACCESS |OS_APP_APPLICATION_CORE1_QM_ACCESS),
    /* ownerAppId     = */ APP_APPLICATION_CORE1_QM,
    /* coreId         = */ OS_CORE_ID_1,
    /* alarmTime      = */ 1U,
    /* autoCycle      = */ 1U,
    /* alarm_CallBack = */ NULL_PTR,
    /* alarmId        = */ RTE_AL_TE_TASK_5MS_CORE1_QM_5MS
};
const Os_AlarmCfgType OsCfg_Alarm_Rte_Al_TE_Task_10ms_Core1_QM_10ms =
{
    /* alarmMode      = */ OS_ALARM_REL,
    /* appMode        = */ OS_APPMODE_NONE,
    /* counter        = */ (const Os_CounterBaseCfgType*)&OsCfg_Counter_SystemTimer_Core1,
    /* cntExpKind     = */ OS_CNTEXP_ALRM_AT,
    {
        /* workParam  = */ .taskId = TASK_10MS_CORE1_QM
    },
    /* alarmDyn       = */ &OsCfg_Alarm_Rte_Al_TE_Task_10ms_Core1_QM_10ms_Dyn,
    /* accessingApps  = */ (OS_SYSTEMAPPLICATION_OSCORE_CORE0_ACCESS |OS_SYSTEMAPPLICATION_OSCORE_CORE1_ACCESS |
                          OS_SYSTEMAPPLICATION_OSCORE_CORE2_ACCESS |OS_APP_APPLICATION_CORE1_QM_ACCESS),
    /* ownerAppId     = */ APP_APPLICATION_CORE1_QM,
    /* coreId         = */ OS_CORE_ID_1,
    /* alarmTime      = */ 1U,
    /* autoCycle      = */ 1U,
    /* alarm_CallBack = */ NULL_PTR,
    /* alarmId        = */ RTE_AL_TE_TASK_10MS_CORE1_QM_10MS
};
const Os_AlarmCfgType OsCfg_Alarm_Rte_Al_TE_Task_20ms_Core1_QM_20ms =
{
    /* alarmMode      = */ OS_ALARM_REL,
    /* appMode        = */ OS_APPMODE_NONE,
    /* counter        = */ (const Os_CounterBaseCfgType*)&OsCfg_Counter_SystemTimer_Core1,
    /* cntExpKind     = */ OS_CNTEXP_ALRM_AT,
    {
        /* workParam  = */ .taskId = TASK_20MS_CORE1_QM
    },
    /* alarmDyn       = */ &OsCfg_Alarm_Rte_Al_TE_Task_20ms_Core1_QM_20ms_Dyn,
    /* accessingApps  = */ (OS_SYSTEMAPPLICATION_OSCORE_CORE0_ACCESS |OS_SYSTEMAPPLICATION_OSCORE_CORE1_ACCESS |
                          OS_SYSTEMAPPLICATION_OSCORE_CORE2_ACCESS |OS_APP_APPLICATION_CORE1_QM_ACCESS),
    /* ownerAppId     = */ APP_APPLICATION_CORE1_QM,
    /* coreId         = */ OS_CORE_ID_1,
    /* alarmTime      = */ 1U,
    /* autoCycle      = */ 1U,
    /* alarm_CallBack = */ NULL_PTR,
    /* alarmId        = */ RTE_AL_TE_TASK_20MS_CORE1_QM_20MS
};
const Os_AlarmCfgType OsCfg_Alarm_Rte_Al_TE_Task_50ms_Core1_QM_50ms =
{
    /* alarmMode      = */ OS_ALARM_REL,
    /* appMode        = */ OS_APPMODE_NONE,
    /* counter        = */ (const Os_CounterBaseCfgType*)&OsCfg_Counter_SystemTimer_Core1,
    /* cntExpKind     = */ OS_CNTEXP_ALRM_AT,
    {
        /* workParam  = */ .taskId = TASK_50MS_CORE1_QM
    },
    /* alarmDyn       = */ &OsCfg_Alarm_Rte_Al_TE_Task_50ms_Core1_QM_50ms_Dyn,
    /* accessingApps  = */ (OS_SYSTEMAPPLICATION_OSCORE_CORE0_ACCESS |OS_SYSTEMAPPLICATION_OSCORE_CORE1_ACCESS |
                          OS_SYSTEMAPPLICATION_OSCORE_CORE2_ACCESS |OS_APP_APPLICATION_CORE1_QM_ACCESS),
    /* ownerAppId     = */ APP_APPLICATION_CORE1_QM,
    /* coreId         = */ OS_CORE_ID_1,
    /* alarmTime      = */ 1U,
    /* autoCycle      = */ 1U,
    /* alarm_CallBack = */ NULL_PTR,
    /* alarmId        = */ RTE_AL_TE_TASK_50MS_CORE1_QM_50MS
};
const Os_AlarmCfgType OsCfg_Alarm_Rte_Al_TE_Task_100ms_Core1_QM_100ms =
{
    /* alarmMode      = */ OS_ALARM_REL,
    /* appMode        = */ OS_APPMODE_NONE,
    /* counter        = */ (const Os_CounterBaseCfgType*)&OsCfg_Counter_SystemTimer_Core1,
    /* cntExpKind     = */ OS_CNTEXP_ALRM_AT,
    {
        /* workParam  = */ .taskId = TASK_100MS_CORE1_QM
    },
    /* alarmDyn       = */ &OsCfg_Alarm_Rte_Al_TE_Task_100ms_Core1_QM_100ms_Dyn,
    /* accessingApps  = */ (OS_SYSTEMAPPLICATION_OSCORE_CORE0_ACCESS |OS_SYSTEMAPPLICATION_OSCORE_CORE1_ACCESS |
                          OS_SYSTEMAPPLICATION_OSCORE_CORE2_ACCESS |OS_APP_APPLICATION_CORE1_QM_ACCESS),
    /* ownerAppId     = */ APP_APPLICATION_CORE1_QM,
    /* coreId         = */ OS_CORE_ID_1,
    /* alarmTime      = */ 1U,
    /* autoCycle      = */ 1U,
    /* alarm_CallBack = */ NULL_PTR,
    /* alarmId        = */ RTE_AL_TE_TASK_100MS_CORE1_QM_100MS
};
const Os_AlarmCfgType OsCfg_Alarm_Rte_Al_TE_Task_200ms_Core1_QM_200ms =
{
    /* alarmMode      = */ OS_ALARM_REL,
    /* appMode        = */ OS_APPMODE_NONE,
    /* counter        = */ (const Os_CounterBaseCfgType*)&OsCfg_Counter_SystemTimer_Core1,
    /* cntExpKind     = */ OS_CNTEXP_ALRM_AT,
    {
        /* workParam  = */ .taskId = TASK_200MS_CORE1_QM
    },
    /* alarmDyn       = */ &OsCfg_Alarm_Rte_Al_TE_Task_200ms_Core1_QM_200ms_Dyn,
    /* accessingApps  = */ (OS_SYSTEMAPPLICATION_OSCORE_CORE0_ACCESS |OS_SYSTEMAPPLICATION_OSCORE_CORE1_ACCESS |
                          OS_SYSTEMAPPLICATION_OSCORE_CORE2_ACCESS |OS_APP_APPLICATION_CORE1_QM_ACCESS),
    /* ownerAppId     = */ APP_APPLICATION_CORE1_QM,
    /* coreId         = */ OS_CORE_ID_1,
    /* alarmTime      = */ 1U,
    /* autoCycle      = */ 1U,
    /* alarm_CallBack = */ NULL_PTR,
    /* alarmId        = */ RTE_AL_TE_TASK_200MS_CORE1_QM_200MS
};
const Os_AlarmCfgType OsCfg_Alarm_Rte_Al_TE_Task_500ms_Core1_QM_500ms =
{
    /* alarmMode      = */ OS_ALARM_REL,
    /* appMode        = */ OS_APPMODE_NONE,
    /* counter        = */ (const Os_CounterBaseCfgType*)&OsCfg_Counter_SystemTimer_Core1,
    /* cntExpKind     = */ OS_CNTEXP_ALRM_AT,
    {
        /* workParam  = */ .taskId = TASK_500MS_CORE1_QM
    },
    /* alarmDyn       = */ &OsCfg_Alarm_Rte_Al_TE_Task_500ms_Core1_QM_500ms_Dyn,
    /* accessingApps  = */ (OS_SYSTEMAPPLICATION_OSCORE_CORE0_ACCESS |OS_SYSTEMAPPLICATION_OSCORE_CORE1_ACCESS |
                          OS_SYSTEMAPPLICATION_OSCORE_CORE2_ACCESS |OS_APP_APPLICATION_CORE1_QM_ACCESS),
    /* ownerAppId     = */ APP_APPLICATION_CORE1_QM,
    /* coreId         = */ OS_CORE_ID_1,
    /* alarmTime      = */ 1U,
    /* autoCycle      = */ 1U,
    /* alarm_CallBack = */ NULL_PTR,
    /* alarmId        = */ RTE_AL_TE_TASK_500MS_CORE1_QM_500MS
};
const Os_AlarmCfgType OsCfg_Alarm_Rte_Al_TE_Task_1000ms_Core1_QM_1000ms =
{
    /* alarmMode      = */ OS_ALARM_REL,
    /* appMode        = */ OS_APPMODE_NONE,
    /* counter        = */ (const Os_CounterBaseCfgType*)&OsCfg_Counter_SystemTimer_Core1,
    /* cntExpKind     = */ OS_CNTEXP_ALRM_AT,
    {
        /* workParam  = */ .taskId = TASK_1000MS_CORE1_QM
    },
    /* alarmDyn       = */ &OsCfg_Alarm_Rte_Al_TE_Task_1000ms_Core1_QM_1000ms_Dyn,
    /* accessingApps  = */ (OS_SYSTEMAPPLICATION_OSCORE_CORE0_ACCESS |OS_SYSTEMAPPLICATION_OSCORE_CORE1_ACCESS |
                          OS_SYSTEMAPPLICATION_OSCORE_CORE2_ACCESS |OS_APP_APPLICATION_CORE1_QM_ACCESS),
    /* ownerAppId     = */ APP_APPLICATION_CORE1_QM,
    /* coreId         = */ OS_CORE_ID_1,
    /* alarmTime      = */ 1U,
    /* autoCycle      = */ 1U,
    /* alarm_CallBack = */ NULL_PTR,
    /* alarmId        = */ RTE_AL_TE_TASK_1000MS_CORE1_QM_1000MS
};
const Os_AlarmCfgType OsCfg_Alarm_Rte_Al_TE_Task_1ms_Core2_QM_1ms =
{
    /* alarmMode      = */ OS_ALARM_REL,
    /* appMode        = */ OS_APPMODE_NONE,
    /* counter        = */ (const Os_CounterBaseCfgType*)&OsCfg_Counter_SystemTimer_Core2,
    /* cntExpKind     = */ OS_CNTEXP_ALRM_AT,
    {
        /* workParam  = */ .taskId = TASK_1MS_CORE2_QM
    },
    /* alarmDyn       = */ &OsCfg_Alarm_Rte_Al_TE_Task_1ms_Core2_QM_1ms_Dyn,
    /* accessingApps  = */ (OS_SYSTEMAPPLICATION_OSCORE_CORE0_ACCESS |OS_SYSTEMAPPLICATION_OSCORE_CORE1_ACCESS |
                          OS_SYSTEMAPPLICATION_OSCORE_CORE2_ACCESS |OS_APP_APPLICATION_CORE2_QM_ACCESS),
    /* ownerAppId     = */ APP_APPLICATION_CORE2_QM,
    /* coreId         = */ OS_CORE_ID_2,
    /* alarmTime      = */ 1U,
    /* autoCycle      = */ 1U,
    /* alarm_CallBack = */ NULL_PTR,
    /* alarmId        = */ RTE_AL_TE_TASK_1MS_CORE2_QM_1MS
};
const Os_AlarmCfgType OsCfg_Alarm_Rte_Al_TE_Task_5ms_Core2_QM_5ms =
{
    /* alarmMode      = */ OS_ALARM_REL,
    /* appMode        = */ OS_APPMODE_NONE,
    /* counter        = */ (const Os_CounterBaseCfgType*)&OsCfg_Counter_SystemTimer_Core2,
    /* cntExpKind     = */ OS_CNTEXP_ALRM_AT,
    {
        /* workParam  = */ .taskId = TASK_5MS_CORE2_QM
    },
    /* alarmDyn       = */ &OsCfg_Alarm_Rte_Al_TE_Task_5ms_Core2_QM_5ms_Dyn,
    /* accessingApps  = */ (OS_SYSTEMAPPLICATION_OSCORE_CORE0_ACCESS |OS_SYSTEMAPPLICATION_OSCORE_CORE1_ACCESS |
                          OS_SYSTEMAPPLICATION_OSCORE_CORE2_ACCESS |OS_APP_APPLICATION_CORE2_QM_ACCESS),
    /* ownerAppId     = */ APP_APPLICATION_CORE2_QM,
    /* coreId         = */ OS_CORE_ID_2,
    /* alarmTime      = */ 1U,
    /* autoCycle      = */ 1U,
    /* alarm_CallBack = */ NULL_PTR,
    /* alarmId        = */ RTE_AL_TE_TASK_5MS_CORE2_QM_5MS
};
const Os_AlarmCfgType OsCfg_Alarm_Rte_Al_TE_Task_10ms_Core2_QM_10ms =
{
    /* alarmMode      = */ OS_ALARM_REL,
    /* appMode        = */ OS_APPMODE_NONE,
    /* counter        = */ (const Os_CounterBaseCfgType*)&OsCfg_Counter_SystemTimer_Core2,
    /* cntExpKind     = */ OS_CNTEXP_ALRM_AT,
    {
        /* workParam  = */ .taskId = TASK_10MS_CORE2_QM
    },
    /* alarmDyn       = */ &OsCfg_Alarm_Rte_Al_TE_Task_10ms_Core2_QM_10ms_Dyn,
    /* accessingApps  = */ (OS_SYSTEMAPPLICATION_OSCORE_CORE0_ACCESS |OS_SYSTEMAPPLICATION_OSCORE_CORE1_ACCESS |
                          OS_SYSTEMAPPLICATION_OSCORE_CORE2_ACCESS |OS_APP_APPLICATION_CORE2_QM_ACCESS),
    /* ownerAppId     = */ APP_APPLICATION_CORE2_QM,
    /* coreId         = */ OS_CORE_ID_2,
    /* alarmTime      = */ 1U,
    /* autoCycle      = */ 1U,
    /* alarm_CallBack = */ NULL_PTR,
    /* alarmId        = */ RTE_AL_TE_TASK_10MS_CORE2_QM_10MS
};
const Os_AlarmCfgType OsCfg_Alarm_Rte_Al_TE_Task_20ms_Core2_QM_20ms =
{
    /* alarmMode      = */ OS_ALARM_REL,
    /* appMode        = */ OS_APPMODE_NONE,
    /* counter        = */ (const Os_CounterBaseCfgType*)&OsCfg_Counter_SystemTimer_Core2,
    /* cntExpKind     = */ OS_CNTEXP_ALRM_AT,
    {
        /* workParam  = */ .taskId = TASK_20MS_CORE2_QM
    },
    /* alarmDyn       = */ &OsCfg_Alarm_Rte_Al_TE_Task_20ms_Core2_QM_20ms_Dyn,
    /* accessingApps  = */ (OS_SYSTEMAPPLICATION_OSCORE_CORE0_ACCESS |OS_SYSTEMAPPLICATION_OSCORE_CORE1_ACCESS |
                          OS_SYSTEMAPPLICATION_OSCORE_CORE2_ACCESS |OS_APP_APPLICATION_CORE2_QM_ACCESS),
    /* ownerAppId     = */ APP_APPLICATION_CORE2_QM,
    /* coreId         = */ OS_CORE_ID_2,
    /* alarmTime      = */ 1U,
    /* autoCycle      = */ 1U,
    /* alarm_CallBack = */ NULL_PTR,
    /* alarmId        = */ RTE_AL_TE_TASK_20MS_CORE2_QM_20MS
};
const Os_AlarmCfgType OsCfg_Alarm_Rte_Al_TE_Task_50ms_Core2_QM_50ms =
{
    /* alarmMode      = */ OS_ALARM_REL,
    /* appMode        = */ OS_APPMODE_NONE,
    /* counter        = */ (const Os_CounterBaseCfgType*)&OsCfg_Counter_SystemTimer_Core2,
    /* cntExpKind     = */ OS_CNTEXP_ALRM_AT,
    {
        /* workParam  = */ .taskId = TASK_50MS_CORE2_QM
    },
    /* alarmDyn       = */ &OsCfg_Alarm_Rte_Al_TE_Task_50ms_Core2_QM_50ms_Dyn,
    /* accessingApps  = */ (OS_SYSTEMAPPLICATION_OSCORE_CORE0_ACCESS |OS_SYSTEMAPPLICATION_OSCORE_CORE1_ACCESS |
                          OS_SYSTEMAPPLICATION_OSCORE_CORE2_ACCESS |OS_APP_APPLICATION_CORE2_QM_ACCESS),
    /* ownerAppId     = */ APP_APPLICATION_CORE2_QM,
    /* coreId         = */ OS_CORE_ID_2,
    /* alarmTime      = */ 1U,
    /* autoCycle      = */ 1U,
    /* alarm_CallBack = */ NULL_PTR,
    /* alarmId        = */ RTE_AL_TE_TASK_50MS_CORE2_QM_50MS
};
const Os_AlarmCfgType OsCfg_Alarm_Rte_Al_TE_Task_100ms_Core2_QM_100ms =
{
    /* alarmMode      = */ OS_ALARM_REL,
    /* appMode        = */ OS_APPMODE_NONE,
    /* counter        = */ (const Os_CounterBaseCfgType*)&OsCfg_Counter_SystemTimer_Core2,
    /* cntExpKind     = */ OS_CNTEXP_ALRM_AT,
    {
        /* workParam  = */ .taskId = TASK_100MS_CORE2_QM
    },
    /* alarmDyn       = */ &OsCfg_Alarm_Rte_Al_TE_Task_100ms_Core2_QM_100ms_Dyn,
    /* accessingApps  = */ (OS_SYSTEMAPPLICATION_OSCORE_CORE0_ACCESS |OS_SYSTEMAPPLICATION_OSCORE_CORE1_ACCESS |
                          OS_SYSTEMAPPLICATION_OSCORE_CORE2_ACCESS |OS_APP_APPLICATION_CORE2_QM_ACCESS),
    /* ownerAppId     = */ APP_APPLICATION_CORE2_QM,
    /* coreId         = */ OS_CORE_ID_2,
    /* alarmTime      = */ 1U,
    /* autoCycle      = */ 1U,
    /* alarm_CallBack = */ NULL_PTR,
    /* alarmId        = */ RTE_AL_TE_TASK_100MS_CORE2_QM_100MS
};
const Os_AlarmCfgType OsCfg_Alarm_Rte_Al_TE_Task_200ms_Core2_QM_200ms =
{
    /* alarmMode      = */ OS_ALARM_REL,
    /* appMode        = */ OS_APPMODE_NONE,
    /* counter        = */ (const Os_CounterBaseCfgType*)&OsCfg_Counter_SystemTimer_Core2,
    /* cntExpKind     = */ OS_CNTEXP_ALRM_AT,
    {
        /* workParam  = */ .taskId = TASK_200MS_CORE2_QM
    },
    /* alarmDyn       = */ &OsCfg_Alarm_Rte_Al_TE_Task_200ms_Core2_QM_200ms_Dyn,
    /* accessingApps  = */ (OS_SYSTEMAPPLICATION_OSCORE_CORE0_ACCESS |OS_SYSTEMAPPLICATION_OSCORE_CORE1_ACCESS |
                          OS_SYSTEMAPPLICATION_OSCORE_CORE2_ACCESS |OS_APP_APPLICATION_CORE2_QM_ACCESS),
    /* ownerAppId     = */ APP_APPLICATION_CORE2_QM,
    /* coreId         = */ OS_CORE_ID_2,
    /* alarmTime      = */ 1U,
    /* autoCycle      = */ 1U,
    /* alarm_CallBack = */ NULL_PTR,
    /* alarmId        = */ RTE_AL_TE_TASK_200MS_CORE2_QM_200MS
};
const Os_AlarmCfgType OsCfg_Alarm_Rte_Al_TE_Task_500ms_Core2_QM_500ms =
{
    /* alarmMode      = */ OS_ALARM_REL,
    /* appMode        = */ OS_APPMODE_NONE,
    /* counter        = */ (const Os_CounterBaseCfgType*)&OsCfg_Counter_SystemTimer_Core2,
    /* cntExpKind     = */ OS_CNTEXP_ALRM_AT,
    {
        /* workParam  = */ .taskId = TASK_500MS_CORE2_QM
    },
    /* alarmDyn       = */ &OsCfg_Alarm_Rte_Al_TE_Task_500ms_Core2_QM_500ms_Dyn,
    /* accessingApps  = */ (OS_SYSTEMAPPLICATION_OSCORE_CORE0_ACCESS |OS_SYSTEMAPPLICATION_OSCORE_CORE1_ACCESS |
                          OS_SYSTEMAPPLICATION_OSCORE_CORE2_ACCESS |OS_APP_APPLICATION_CORE2_QM_ACCESS),
    /* ownerAppId     = */ APP_APPLICATION_CORE2_QM,
    /* coreId         = */ OS_CORE_ID_2,
    /* alarmTime      = */ 1U,
    /* autoCycle      = */ 1U,
    /* alarm_CallBack = */ NULL_PTR,
    /* alarmId        = */ RTE_AL_TE_TASK_500MS_CORE2_QM_500MS
};
const Os_AlarmCfgType OsCfg_Alarm_Rte_Al_TE_Task_1000ms_Core2_QM_1000ms =
{
    /* alarmMode      = */ OS_ALARM_REL,
    /* appMode        = */ OS_APPMODE_NONE,
    /* counter        = */ (const Os_CounterBaseCfgType*)&OsCfg_Counter_SystemTimer_Core2,
    /* cntExpKind     = */ OS_CNTEXP_ALRM_AT,
    {
        /* workParam  = */ .taskId = TASK_1000MS_CORE2_QM
    },
    /* alarmDyn       = */ &OsCfg_Alarm_Rte_Al_TE_Task_1000ms_Core2_QM_1000ms_Dyn,
    /* accessingApps  = */ (OS_SYSTEMAPPLICATION_OSCORE_CORE0_ACCESS |OS_SYSTEMAPPLICATION_OSCORE_CORE1_ACCESS |
                          OS_SYSTEMAPPLICATION_OSCORE_CORE2_ACCESS |OS_APP_APPLICATION_CORE2_QM_ACCESS),
    /* ownerAppId     = */ APP_APPLICATION_CORE2_QM,
    /* coreId         = */ OS_CORE_ID_2,
    /* alarmTime      = */ 1U,
    /* autoCycle      = */ 1U,
    /* alarm_CallBack = */ NULL_PTR,
    /* alarmId        = */ RTE_AL_TE_TASK_1000MS_CORE2_QM_1000MS
};
const Os_AlarmCfgType OsCfg_Alarm_Rte_Al_TE_Task_4ms_Core2_QM_4ms =
{
    /* alarmMode      = */ OS_ALARM_REL,
    /* appMode        = */ OS_APPMODE_NONE,
    /* counter        = */ (const Os_CounterBaseCfgType*)&OsCfg_Counter_SystemTimer_Core2,
    /* cntExpKind     = */ OS_CNTEXP_ALRM_AT,
    {
        /* workParam  = */ .taskId = TASK_4MS_CORE2_QM
    },
    /* alarmDyn       = */ &OsCfg_Alarm_Rte_Al_TE_Task_4ms_Core2_QM_4ms_Dyn,
    /* accessingApps  = */ (OS_SYSTEMAPPLICATION_OSCORE_CORE0_ACCESS |OS_SYSTEMAPPLICATION_OSCORE_CORE1_ACCESS |
                          OS_SYSTEMAPPLICATION_OSCORE_CORE2_ACCESS |OS_APP_APPLICATION_CORE2_QM_ACCESS),
    /* ownerAppId     = */ APP_APPLICATION_CORE2_QM,
    /* coreId         = */ OS_CORE_ID_2,
    /* alarmTime      = */ 1U,
    /* autoCycle      = */ 1U,
    /* alarm_CallBack = */ NULL_PTR,
    /* alarmId        = */ RTE_AL_TE_TASK_4MS_CORE2_QM_4MS
};
/* Alarm config parameters end. */

/* Spinlock config parameters start. */
/* Spinlock config parameters end. */

/* Resource config parameters start. */
const Os_ResourceCfgType OsCfg_Resource_Core0_Task_OsResource0 =
{
    /* rsrcType      = */ OS_RESOURCE_TASK,
    {
        /* rsrcParam     = */ .taskPrio = 2U
    },
    /* rsrcId        = */ CORE0_TASK_OSRESOURCE0,
    /* coreId        = */ OS_CORE_ID_0,
    /* accessingApps = */ OS_APP_APPLICATION_CORE0_QM_ACCESS,
    /* resouceDyn    = */ &Os_Resource_Core0_Task_OsResource0_Dyn
};
const Os_ResourceCfgType OsCfg_Resource_Core1_Task_OsResource1 =
{
    /* rsrcType      = */ OS_RESOURCE_TASK,
    {
        /* rsrcParam     = */ .taskPrio = 2U
    },
    /* rsrcId        = */ CORE1_TASK_OSRESOURCE1,
    /* coreId        = */ OS_CORE_ID_1,
    /* accessingApps = */ OS_APP_APPLICATION_CORE1_QM_ACCESS,
    /* resouceDyn    = */ &Os_Resource_Core1_Task_OsResource1_Dyn
};
const Os_ResourceCfgType OsCfg_Resource_Core2_Task_OsResource2 =
{
    /* rsrcType      = */ OS_RESOURCE_TASK,
    {
        /* rsrcParam     = */ .taskPrio = 4U
    },
    /* rsrcId        = */ CORE2_TASK_OSRESOURCE2,
    /* coreId        = */ OS_CORE_ID_2,
    /* accessingApps = */ OS_APP_APPLICATION_CORE2_QM_ACCESS,
    /* resouceDyn    = */ &Os_Resource_Core2_Task_OsResource2_Dyn
};
/* Resource config parameters end. */

/* Scheduler config parameters start. */
const Os_SchedulerCfgType OsCfg_Scheduler_OsCore0 =
{
    {
        /* bitMap->bitMapDyn = */ &OsCfg_Scheduler_BitMap_OsCore0_Dyn,
        /* bitMap->l1Data    = */ OsCfg_BitMap_L1Data_OsCore0_Dyn,
        /* bitMap->length    = */ OS_BITMAP_LENGTH(OS_CFG_NUM_TASKQUEUES_OSCORE0),
        /* bitMap->bitNum    = */ OS_BITMAP_NUM(OS_CFG_NUM_TASKQUEUES_OSCORE0)
    },
    /* schdDyn               = */ &OsCfg_Scheduler_OsCore0_Dyn,
    /* taskQueues            = */ OsCfg_Scheduler_OsCore0_TaskQueues,
    /* queuesNumber          = */ OS_CFG_NUM_TASKQUEUES_OSCORE0,
    /* taskQueInit           = */ OsCfg_Scheduler_InitCallback_OsCore0
};

const Os_SchedulerCfgType OsCfg_Scheduler_OsCore1 =
{
    {
        /* bitMap->bitMapDyn = */ &OsCfg_Scheduler_BitMap_OsCore1_Dyn,
        /* bitMap->l1Data    = */ OsCfg_BitMap_L1Data_OsCore1_Dyn,
        /* bitMap->length    = */ OS_BITMAP_LENGTH(OS_CFG_NUM_TASKQUEUES_OSCORE1),
        /* bitMap->bitNum    = */ OS_BITMAP_NUM(OS_CFG_NUM_TASKQUEUES_OSCORE1)
    },
    /* schdDyn               = */ &OsCfg_Scheduler_OsCore1_Dyn,
    /* taskQueues            = */ OsCfg_Scheduler_OsCore1_TaskQueues,
    /* queuesNumber          = */ OS_CFG_NUM_TASKQUEUES_OSCORE1,
    /* taskQueInit           = */ OsCfg_Scheduler_InitCallback_OsCore1
};

const Os_SchedulerCfgType OsCfg_Scheduler_OsCore2 =
{
    {
        /* bitMap->bitMapDyn = */ &OsCfg_Scheduler_BitMap_OsCore2_Dyn,
        /* bitMap->l1Data    = */ OsCfg_BitMap_L1Data_OsCore2_Dyn,
        /* bitMap->length    = */ OS_BITMAP_LENGTH(OS_CFG_NUM_TASKQUEUES_OSCORE2),
        /* bitMap->bitNum    = */ OS_BITMAP_NUM(OS_CFG_NUM_TASKQUEUES_OSCORE2)
    },
    /* schdDyn               = */ &OsCfg_Scheduler_OsCore2_Dyn,
    /* taskQueues            = */ OsCfg_Scheduler_OsCore2_TaskQueues,
    /* queuesNumber          = */ OS_CFG_NUM_TASKQUEUES_OSCORE2,
    /* taskQueInit           = */ OsCfg_Scheduler_InitCallback_OsCore2
};

/* Scheduler config parameters end. */

/* Core config parameters start. */
const Os_CoreCfgType OsCfg_Core_OsCore0 =
{
    /* corePhyId          = */ 0U,
    /* coreIfAutoStart    = */ FALSE,
    /* coreIfAutoSarOs    = */ TRUE,
    /* coreIfMaster       = */ FALSE,
    /* coreCoreLogicId    = */ OS_CORE_ID_0,
    /* coreStartAddr      = */ (uint32)(&_start),
    /* idleTask           = */ &OsCfg_Task_Idle_Task_Core0,
    /* initTask           = */ &OsCfg_Task_Default_Init_Task_Core0,
    /* intStateCfg        = */ &OsCfg_IntState_OsCore0_Dyn,
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC2) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* tpBaseCfg          = */ NULL_PTR,
#endif
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC3) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* memoryProtection   = */ NULL_PTR,
#endif
    /* scheduler          = */ &OsCfg_Scheduler_OsCore0,
    /* contextCfg         = */ &OsCfg_Arch_Context_Kernal_OsCore0,
    /* systemApp          = */ &OsCfg_Appl_SystemApplication_OsCore_Core0,
    /* appRefs            = */ &Os_AppCfgData[SYSTEMAPPLICATION_OSCORE_CORE0],
    /* appCnt             = */ 2U,
    /* taskRefs           = */ &Os_TaskCfgData[DEFAULT_INIT_TASK_CORE0],
    /* taskCnt            = */ 11U,
    /* isrRefs            = */ &Os_IsrCfgData[COUNTERISR_SYSTEMTIMER_CORE0],
    /* isrCnt             = */ 3U,
    /* isrCat1Refs        = */ &Os_Cat1IsrCfgData_OsCore0[0],
    /* isrCat1Cnt         = */ 4U,
    /* counterRefs        = */ &Os_CounterCfgData[SYSTEMTIMER_CORE0],
    /* counterCnt         = */ 2U,
    /* alarmRefs          = */ &Os_AlarmCfgData[RTE_AL_TE_TASK_10MS_CORE0_QM_10MS],
    /* alarmCnt           = */ 8U,
#if ( OS_CFG_RESOURCE_ENABLE == STD_ON )
    /* resourceRefs       = */ &Os_ResourceCfgData[CORE0_TASK_OSRESOURCE0],
    /* resourceCnt        = */ 1U,
#endif
#if ( OS_CFG_SCHDTB_ENABLE == STD_ON )
    /* schTbRefs          = */ NULL_PTR,
    /* schdTbCount        = */ 0U,
#endif
#if ( OS_CFG_IOC_ENABLE== STD_ON )
    /* iocRefs            = */ NULL_PTR,
    /* iocCnt             = */ 0U,
#endif
    /* protectionHook     = */ NULL_PTR,
    /* coreDyn            = */ &OsCfg_Core_OsCore0_Dyn,
    /* multiCommIsrSource = */ &OsCfg_Arch_Source_MultiCommIsr_OsCore_Core0
};
const Os_CoreCfgType OsCfg_Core_OsCore1 =
{
    /* corePhyId          = */ 1U,
    /* coreIfAutoStart    = */ FALSE,
    /* coreIfAutoSarOs    = */ TRUE,
    /* coreIfMaster       = */ FALSE,
    /* coreCoreLogicId    = */ OS_CORE_ID_1,
    /* coreStartAddr      = */ (uint32)(&_start),
    /* idleTask           = */ &OsCfg_Task_Idle_Task_Core1,
    /* initTask           = */ &OsCfg_Task_Default_Init_Task_Core1,
    /* intStateCfg        = */ &OsCfg_IntState_OsCore1_Dyn,
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC2) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* tpBaseCfg          = */ NULL_PTR,
#endif
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC3) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* memoryProtection   = */ NULL_PTR,
#endif
    /* scheduler          = */ &OsCfg_Scheduler_OsCore1,
    /* contextCfg         = */ &OsCfg_Arch_Context_Kernal_OsCore1,
    /* systemApp          = */ &OsCfg_Appl_SystemApplication_OsCore_Core1,
    /* appRefs            = */ &Os_AppCfgData[SYSTEMAPPLICATION_OSCORE_CORE1],
    /* appCnt             = */ 2U,
    /* taskRefs           = */ &Os_TaskCfgData[DEFAULT_INIT_TASK_CORE1],
    /* taskCnt            = */ 11U,
    /* isrRefs            = */ &Os_IsrCfgData[COUNTERISR_SYSTEMTIMER_CORE1],
    /* isrCnt             = */ 2U,
    /* isrCat1Refs        = */ &Os_Cat1IsrCfgData_OsCore1[0],
    /* isrCat1Cnt         = */ 1U,
    /* counterRefs        = */ &Os_CounterCfgData[SYSTEMTIMER_CORE1],
    /* counterCnt         = */ 1U,
    /* alarmRefs          = */ &Os_AlarmCfgData[RTE_AL_TE_TASK_5MS_CORE1_QM_5MS],
    /* alarmCnt           = */ 8U,
#if ( OS_CFG_RESOURCE_ENABLE == STD_ON )
    /* resourceRefs       = */ &Os_ResourceCfgData[CORE1_TASK_OSRESOURCE1],
    /* resourceCnt        = */ 1U,
#endif
#if ( OS_CFG_SCHDTB_ENABLE == STD_ON )
    /* schTbRefs          = */ NULL_PTR,
    /* schdTbCount        = */ 0U,
#endif
#if ( OS_CFG_IOC_ENABLE== STD_ON )
    /* iocRefs            = */ NULL_PTR,
    /* iocCnt             = */ 0U,
#endif
    /* protectionHook     = */ NULL_PTR,
    /* coreDyn            = */ &OsCfg_Core_OsCore1_Dyn,
    /* multiCommIsrSource = */ &OsCfg_Arch_Source_MultiCommIsr_OsCore_Core1
};
const Os_CoreCfgType OsCfg_Core_OsCore2 =
{
    /* corePhyId          = */ 2U,
    /* coreIfAutoStart    = */ TRUE,
    /* coreIfAutoSarOs    = */ TRUE,
    /* coreIfMaster       = */ TRUE,
    /* coreCoreLogicId    = */ OS_CORE_ID_2,
    /* coreStartAddr      = */ 0U,
    /* idleTask           = */ &OsCfg_Task_Idle_Task_Core2,
    /* initTask           = */ &OsCfg_Task_Default_Init_Task_Core2,
    /* intStateCfg        = */ &OsCfg_IntState_OsCore2_Dyn,
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC2) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* tpBaseCfg          = */ NULL_PTR,
#endif
#if ((OS_CFG_SCALABILITY_CLASS == OS_SC3) || (OS_CFG_SCALABILITY_CLASS == OS_SC4))
    /* memoryProtection   = */ NULL_PTR,
#endif
    /* scheduler          = */ &OsCfg_Scheduler_OsCore2,
    /* contextCfg         = */ &OsCfg_Arch_Context_Kernal_OsCore2,
    /* systemApp          = */ &OsCfg_Appl_SystemApplication_OsCore_Core2,
    /* appRefs            = */ &Os_AppCfgData[SYSTEMAPPLICATION_OSCORE_CORE2],
    /* appCnt             = */ 2U,
    /* taskRefs           = */ &Os_TaskCfgData[DEFAULT_INIT_TASK_CORE2],
    /* taskCnt            = */ 13U,
    /* isrRefs            = */ &Os_IsrCfgData[COUNTERISR_SYSTEMTIMER_CORE2],
    /* isrCnt             = */ 16U,
    /* isrCat1Refs        = */ &Os_Cat1IsrCfgData_OsCore2[0],
    /* isrCat1Cnt         = */ 0U,
    /* counterRefs        = */ &Os_CounterCfgData[SYSTEMTIMER_CORE2],
    /* counterCnt         = */ 1U,
    /* alarmRefs          = */ &Os_AlarmCfgData[RTE_AL_TE_TASK_1MS_CORE2_QM_1MS],
    /* alarmCnt           = */ 10U,
#if ( OS_CFG_RESOURCE_ENABLE == STD_ON )
    /* resourceRefs       = */ &Os_ResourceCfgData[CORE2_TASK_OSRESOURCE2],
    /* resourceCnt        = */ 1U,
#endif
#if ( OS_CFG_SCHDTB_ENABLE == STD_ON )
    /* schTbRefs          = */ NULL_PTR,
    /* schdTbCount        = */ 0U,
#endif
#if ( OS_CFG_IOC_ENABLE== STD_ON )
    /* iocRefs            = */ NULL_PTR,
    /* iocCnt             = */ 0U,
#endif
    /* protectionHook     = */ NULL_PTR,
    /* coreDyn            = */ &OsCfg_Core_OsCore2_Dyn,
    /* multiCommIsrSource = */ &OsCfg_Arch_Source_MultiCommIsr_OsCore_Core2
};
/* Core config parameters end. */

const Os_CoreCfgType* Os_CoreCfgData[OS_COREID_COUNT + 1] = 
{
    &OsCfg_Core_OsCore0,
    &OsCfg_Core_OsCore1,
    &OsCfg_Core_OsCore2,
    NULL_PTR
};
const Os_AppCfgType* Os_AppCfgData[OS_APPID_COUNT + 1] = 
{
    &OsCfg_Appl_SystemApplication_OsCore_Core0,
    &OsCfg_Appl_App_Application_Core0_QM,
    &OsCfg_Appl_SystemApplication_OsCore_Core1,
    &OsCfg_Appl_App_Application_Core1_QM,
    &OsCfg_Appl_SystemApplication_OsCore_Core2,
    &OsCfg_Appl_App_Application_Core2_QM,
    NULL_PTR
};
const Os_TaskCfgType* Os_TaskCfgData[OS_TASKID_COUNT + 1] = 
{
    &OsCfg_Task_Default_Init_Task_Core0,
    &OsCfg_Task_Idle_Task_Core0,
    &OsCfg_Task_Task_Init_Core0_QM,
    &OsCfg_Task_Task_10ms_Core0_QM,
    &OsCfg_Task_Task_20ms_Core0_QM,
    &OsCfg_Task_Task_50ms_Core0_QM,
    &OsCfg_Task_Task_100ms_Core0_QM,
    &OsCfg_Task_Task_200ms_Core0_QM,
    &OsCfg_Task_Task_500ms_Core0_QM,
    &OsCfg_Task_Task_1000ms_Core0_QM,
    &OsCfg_Task_Task_2ms_Core0_QM,
    &OsCfg_Task_Default_Init_Task_Core1,
    &OsCfg_Task_Idle_Task_Core1,
    &OsCfg_Task_Task_Init_Core1_QM,
    &OsCfg_Task_Task_5ms_Core1_QM,
    &OsCfg_Task_Task_10ms_Core1_QM,
    &OsCfg_Task_Task_20ms_Core1_QM,
    &OsCfg_Task_Task_50ms_Core1_QM,
    &OsCfg_Task_Task_100ms_Core1_QM,
    &OsCfg_Task_Task_200ms_Core1_QM,
    &OsCfg_Task_Task_500ms_Core1_QM,
    &OsCfg_Task_Task_1000ms_Core1_QM,
    &OsCfg_Task_Default_Init_Task_Core2,
    &OsCfg_Task_Idle_Task_Core2,
    &OsCfg_Task_Task_Init_Core2_QM,
    &OsCfg_Task_Task_1ms_Core2_QM,
    &OsCfg_Task_Task_4ms_Core2_QM,
    &OsCfg_Task_Task_5ms_Core2_QM,
    &OsCfg_Task_Task_10ms_Core2_QM,
    &OsCfg_Task_Task_20ms_Core2_QM,
    &OsCfg_Task_Task_50ms_Core2_QM,
    &OsCfg_Task_Task_100ms_Core2_QM,
    &OsCfg_Task_Task_200ms_Core2_QM,
    &OsCfg_Task_Task_500ms_Core2_QM,
    &OsCfg_Task_Task_1000ms_Core2_QM,
    NULL_PTR
};
const Os_IsrCfgType* Os_IsrCfgData[OS_ISRID_COUNT + 1] = 
{
    &OsCfg_Isr_CounterIsr_SystemTimer_Core0,
    &OsCfg_Isr_MultiCommIsr_OsCore_Core0,
    &OsCfg_Isr_Os_Monitor_Isr,
    &OsCfg_Isr_CounterIsr_SystemTimer_Core1,
    &OsCfg_Isr_MultiCommIsr_OsCore_Core1,
    &OsCfg_Isr_CounterIsr_SystemTimer_Core2,
    &OsCfg_Isr_MultiCommIsr_OsCore_Core2,
    &OsCfg_Isr_FlashDone_Isr,
    &OsCfg_Isr_PIT0_CH4,
    &OsCfg_Isr_PIT0_CH5,
    &OsCfg_Isr_PIT0_CH6,
    &OsCfg_Isr_Can1_Isr,
    &OsCfg_Isr_Can2_Isr,
    &OsCfg_Isr_Can3_Isr,
    &OsCfg_Isr_Can4_Isr,
    &OsCfg_Isr_Adc89_Grp0_Isr,
    &OsCfg_Isr_Adc89_Grp1_Isr,
    &OsCfg_Isr_Adc89_Grp2_Isr,
    &OsCfg_Isr_Adc89_Grp3_Isr,
    &OsCfg_Isr_Adc89_Grp4_Isr,
    &OsCfg_Isr_Adc89_Grp5_Isr,
    NULL_PTR
};
const Os_IsrCat1CfgType* Os_Cat1IsrCfgData_OsCore0[OS_CFG_NUM_CAT1ISR_OSCORE0 + 1] = 
{
    &OsCfg_Cat1Isr_GTM_ATOM10,
    &OsCfg_Cat1Isr_SIUL_External_Interrupt_0,
    &OsCfg_Cat1Isr_SIUL_External_Interrupt_1,
    &OsCfg_Cat1Isr_EDMA_CH80,
    NULL_PTR
};
const Os_IsrCat1CfgType* Os_Cat1IsrCfgData_OsCore1[OS_CFG_NUM_CAT1ISR_OSCORE1 + 1] = 
{
    &OsCfg_Cat1Isr_GTM_ATOM40,
    NULL_PTR
};
const Os_IsrCat1CfgType* Os_Cat1IsrCfgData_OsCore2[OS_CFG_NUM_CAT1ISR_OSCORE2 + 1] = 
{
    NULL_PTR
};
const Os_CounterBaseCfgType* Os_CounterCfgData[OS_COUNTERID_COUNT + 1] = 
{
    (const Os_CounterBaseCfgType*)&OsCfg_Counter_SystemTimer_Core0,
    (const Os_CounterBaseCfgType*)&OsCfg_Counter_Os_Monitor_Counter,
    (const Os_CounterBaseCfgType*)&OsCfg_Counter_SystemTimer_Core1,
    (const Os_CounterBaseCfgType*)&OsCfg_Counter_SystemTimer_Core2,
    NULL_PTR
};
const Os_AlarmCfgType* Os_AlarmCfgData[OS_ALARMID_COUNT + 1] = 
{
    &OsCfg_Alarm_Rte_Al_TE_Task_10ms_Core0_QM_10ms,
    &OsCfg_Alarm_Rte_Al_TE_Task_20ms_Core0_QM_20ms,
    &OsCfg_Alarm_Rte_Al_TE_Task_50ms_Core0_QM_50ms,
    &OsCfg_Alarm_Rte_Al_TE_Task_100ms_Core0_QM_100ms,
    &OsCfg_Alarm_Rte_Al_TE_Task_200ms_Core0_QM_200ms,
    &OsCfg_Alarm_Rte_Al_TE_Task_500ms_Core0_QM_500ms,
    &OsCfg_Alarm_Rte_Al_TE_Task_1000ms_Core0_QM_1000ms,
    &OsCfg_Alarm_Rte_Al_TE_Task_2ms_Core0_QM_2ms,
    &OsCfg_Alarm_Rte_Al_TE_Task_5ms_Core1_QM_5ms,
    &OsCfg_Alarm_Rte_Al_TE_Task_10ms_Core1_QM_10ms,
    &OsCfg_Alarm_Rte_Al_TE_Task_20ms_Core1_QM_20ms,
    &OsCfg_Alarm_Rte_Al_TE_Task_50ms_Core1_QM_50ms,
    &OsCfg_Alarm_Rte_Al_TE_Task_100ms_Core1_QM_100ms,
    &OsCfg_Alarm_Rte_Al_TE_Task_200ms_Core1_QM_200ms,
    &OsCfg_Alarm_Rte_Al_TE_Task_500ms_Core1_QM_500ms,
    &OsCfg_Alarm_Rte_Al_TE_Task_1000ms_Core1_QM_1000ms,
    &OsCfg_Alarm_Rte_Al_TE_Task_1ms_Core2_QM_1ms,
    &OsCfg_Alarm_Rte_Al_TE_Task_5ms_Core2_QM_5ms,
    &OsCfg_Alarm_Rte_Al_TE_Task_10ms_Core2_QM_10ms,
    &OsCfg_Alarm_Rte_Al_TE_Task_20ms_Core2_QM_20ms,
    &OsCfg_Alarm_Rte_Al_TE_Task_50ms_Core2_QM_50ms,
    &OsCfg_Alarm_Rte_Al_TE_Task_100ms_Core2_QM_100ms,
    &OsCfg_Alarm_Rte_Al_TE_Task_200ms_Core2_QM_200ms,
    &OsCfg_Alarm_Rte_Al_TE_Task_500ms_Core2_QM_500ms,
    &OsCfg_Alarm_Rte_Al_TE_Task_1000ms_Core2_QM_1000ms,
    &OsCfg_Alarm_Rte_Al_TE_Task_4ms_Core2_QM_4ms,
    NULL_PTR
};
const Os_SpinlockCfgType* Os_SpinlockCfgData[OS_SPINLOCKID_COUNT + 1] = 
{
    NULL_PTR
};
const Os_ResourceCfgType* Os_ResourceCfgData[OS_RESOURCEID_COUNT + 1] = 
{
    &OsCfg_Resource_Core0_Task_OsResource0,
    &OsCfg_Resource_Core1_Task_OsResource1,
    &OsCfg_Resource_Core2_Task_OsResource2,
    NULL_PTR
};
#define OS_STOP_SEC_CONST 
#include "Os_MemMap.h"
