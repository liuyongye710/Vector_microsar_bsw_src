/*
********************************************************************************
*
*  File name: Os_Monitor.c
*
*  Copyright Neusoft Reach Corporation. All rights reserved.
*
********************************************************************************
*
* History
*------------------------------------------------------------------------------
********************************************************************************
* Version: 3.0
* Author/Date: lixing/2022.08.30
* Change: New create.
* Cause: New
********************************************************************************
* Version: 3.1
* Author/Date: liG/2023.02.6
* Change: Adapt to the refactor OS.
* Cause: Update
********************************************************************************
* Version: 3.2
* Author/Date: liG/2023.04.14
* Change: Using valid macros.
* Cause: Bugfix
********************************************************************************
* Version: 3.3
* Author/Date: LiuJJ/2023.04.26
* Change: Solve ISR RunTime and RunTime_Max calculate error.
* Cause: Bugfix
********************************************************************************
* Version: 3.4
* Author/Date: LiuJJ/2023.05.05
* Change: Solve ISR interrupted RunTime calculate error.
* Cause: Bugfix
********************************************************************************
* Version: 3.5
* Author/Date: LiuJJ/2023.05.05
* Change: Macro written backwards.
* Cause: Bugfix
********************************************************************************
* Version: 3.6
* Author/Date: LiG/2023.05.05
* Change: Variable position adjustment.
* Cause: Bugfix
********************************************************************************
* Version: 3.7
* Author/Date: LiG/2023.6.8
* Change: Resolve timer flipping issue.
* Cause: Bugfix
********************************************************************************
* Version: 3.8
* Author/Date: LiG/2023.6.8
* Change: Multicore problem.
* Cause: Bugfix
********************************************************************************
* Version: 3.9
* Author/Date: LiG/2023.6.9
* Change: Coding specification.
* Cause: Bugfix
********************************************************************************
* Version: 3.10
* Author/Date: LiG/2023.6.9
* Change: Compiler Warning.
* Cause: Optimize
********************************************************************************
*/
/*
********************************************************************************
*    Includes
********************************************************************************
*/
#include "Os_Monitor_Cfg.h"
#include "Os_Monitor.h"
#include "Os_Task_Types.h"
#include "Os_Counter.h"
#if( OS_MONITOR_ENABLE == STD_ON )

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
*    Local Constants
********************************************************************************
*/
/*
********************************************************************************
*    Local Functions
********************************************************************************
*/
/*
********************************************************************************
*    Global Variables
********************************************************************************
*/
#define OS_START_SEC_GLOBAL_NOCACHE_VAR
#include "Os_MemMap.h"
VAR(TaskType, OS_VAR_INIT) Os_Monitor_CoreRunTask[OS_COREID_COUNT];
VAR(Os_Monitor_TaskStackType_st, OS_VAR_INIT) Os_Monitor_TaskStackPara[OS_TASKID_COUNT];
VAR(Os_Monitor_IsrStackType_st, OS_VAR_INIT) Os_Monitor_IsrStackPara[OS_ISRID_COUNT];
VAR(ISRType, OS_VAR_INIT) Os_Monitor_CoreRunIsr[OS_COREID_COUNT];
#define OS_STOP_SEC_GLOBAL_NOCACHE_VAR
#include "Os_MemMap.h"

#define OS_START_SEC_GLOBAL_NOCACHE_INITVAR
#include "Os_MemMap.h"
VAR(ISRType, OS_VAR_INIT) Last_isrId = INVALID_ISR;
VAR(uint32, OS_VAR_INIT)  Pre_IsrQnum[OS_COREID_COUNT] = {OS_ZERO_VALUE};
VAR(uint32, OS_VAR_INIT) RunTime_Max_init = MONITOR_VALUE_ZERO;
VAR(Os_Monitor_CoreCpuloadType_st, OS_VAR_INIT) Os_Monitor_CpuLoadkPara[OS_COREID_COUNT] = {MONITOR_VALUE_ZERO};
VAR(boolean, OS_VAR_INIT) Os_Monitor_Cat2Interrupttotask[OS_COREID_COUNT] = {FALSE};
VAR(boolean, OS_VAR_INIT) Os_Monitor_Init_status = FALSE;
VAR(uint8, OS_VAR_INIT) Os_Monitor_IsrInterruptFlag[OS_COREID_COUNT] = {MONITOR_VALUE_ZERO};
VAR(boolean, OS_VAR_INIT) Os_Monitor_TaskTerminateFlag[OS_COREID_COUNT] = {MONITOR_VALUE_ZERO};
VAR(ISRType, OS_VAR_INIT) Isr_Queue[OS_MONITOR_ISR_NEST_NUM][OS_COREID_COUNT] = {INVALID_ISR};
#define OS_STOP_SEC_GLOBAL_NOCACHE_INITVAR
#include "Os_MemMap.h"

/*
********************************************************************************
*    Global Constants
********************************************************************************
*/
#define OS_START_SEC_CODE
#include "Os_MemMap.h"
/*
*******************************************************************************
* Function Name: Os_Monitor_init
*
* Explanation: Get task configuration information and initialization structure.
*
* Parameters: None
*
* retval: None
*******************************************************************************
*/
FUNC(void, OS_CODE) Os_Monitor_init(void)
{
    Os_TaskDynType *taskDyn = NULL_PTR;
    uint8 taskIndex = MONITOR_VALUE_ZERO;
    uint8 coreIndex = MONITOR_VALUE_ZERO;
    uint8 isrIndex = MONITOR_VALUE_ZERO;

    for( taskIndex = CIRCLE_VALUE_ZERO; taskIndex < (uint8)OS_TASKID_COUNT; taskIndex++ )
    {
        Os_Monitor_TaskStackPara[taskIndex].RunTime_Max = MONITOR_VALUE_ZERO;
        Os_Monitor_TaskStackPara[taskIndex].TaskId = Os_TaskCfgData[taskIndex]->taskId;
        Os_Monitor_TaskStackPara[taskIndex].HomePriority = Os_TaskCfgData[taskIndex]->cfgPrio;

        taskDyn = (Os_TaskDynType *)Os_TaskCfgData[taskIndex]->taskDyn;
        Os_Monitor_TaskStackPara[taskIndex].Priority = taskDyn->currentPrio;
    }
    for( coreIndex = CIRCLE_VALUE_ZERO; coreIndex < OS_COREID_COUNT; coreIndex++ )
    {
        Os_Monitor_CpuLoadkPara[coreIndex].CoreStartRunTime = (uint32)Os_Counter_GetCntValue(Os_CounterCfgData[Os_Monitor_CoreUseCounterIndex[coreIndex]]);
        Os_Monitor_TaskStackPara[Os_Monitor_CoreidleTaskMapping[coreIndex]].StartResumesTime = Os_Monitor_CpuLoadkPara[coreIndex].CoreStartRunTime;
        Os_Monitor_TaskStackPara[Os_Monitor_CoreidleTaskMapping[coreIndex]].TimeSum = MONITOR_VALUE_ZERO;
        if( (uint8)Os_Monitor_CoreRunTask[coreIndex] != (uint8)CIRCLE_VALUE_ZERO )
        {
            Os_Monitor_TaskStackPara[Os_Monitor_CoreRunTask[coreIndex]].StartResumesTime = Os_Monitor_CpuLoadkPara[coreIndex].CoreStartRunTime;
        }
    }
    for( isrIndex = CIRCLE_VALUE_ZERO; isrIndex < (uint8)OS_ISRID_COUNT; isrIndex++ )
    {
        Os_Monitor_IsrStackPara[isrIndex].RunTime_Max = MONITOR_VALUE_ZERO;
        Os_Monitor_IsrStackPara[isrIndex].Id = Os_IsrCfgData[isrIndex]->isrId;
        Os_Monitor_IsrStackPara[isrIndex].Source.level = Os_IsrCfgData[isrIndex]->source->level;
        Os_Monitor_IsrStackPara[isrIndex].Source.number = Os_IsrCfgData[isrIndex]->source->number;
    }
    Os_Monitor_Init_status = TRUE;
}

/*
*******************************************************************************
* Function Name: Os_Monitor_TimeStackCount
*
* Explanation: Used for stack statistics and time calculation.
*
* Parameters: None
*
* retval: None
*******************************************************************************
*/
LOCAL_INLINE FUNC(void, OS_CODE) Os_Monitor_TimeStackCount(void)
{
    uint32 taskRunTimeSum = MONITOR_VALUE_ZERO;
    uint32 isrRunTimeSum = MONITOR_VALUE_ZERO;
    uint8 taskIndex = MONITOR_VALUE_ZERO;
    uint8 isrIndex = MONITOR_VALUE_ZERO;
    uint8 coreIndex = MONITOR_VALUE_ZERO;
    uint8 isrRunTimeNumIndex = MONITOR_VALUE_ZERO;
    uint8 TaskSnippetIndex = MONITOR_VALUE_ZERO;
#if(OS_MONITOR_EXTENDTASKCOUNT > MONITOR_VALUE_ZERO)
    uint8 extendTaskIndex = MONITOR_VALUE_ZERO;
#endif

    if( MONITOR_VALUE_ZERO == RunTime_Max_init ) RunTime_Max_init = MONITOR_FLAGVALUE;

    for( taskIndex = CIRCLE_VALUE_ZERO; taskIndex < (uint8)OS_TASKID_COUNT; taskIndex++ )
    {
        for( coreIndex = CIRCLE_VALUE_ZERO; coreIndex < (uint8)OS_COREID_COUNT; coreIndex++)
        {
            if( (uint8)Os_Monitor_CoreidleTaskMapping[coreIndex] == taskIndex )
            {
                break;
            }
        }
        if( coreIndex >= (uint8)OS_COREID_COUNT )
        {
#if(OS_MONITOR_EXTENDTASKCOUNT > MONITOR_VALUE_ZERO)
            for( extendTaskIndex = CIRCLE_VALUE_ZERO; extendTaskIndex < OS_MONITOR_EXTENDTASKCOUNT; extendTaskIndex++ )
            {
                if( Os_Monitor_ExtendTaskSubTimeNumber[extendTaskIndex].TaskId == taskIndex )
                {
                    taskRunTimeSum = MONITOR_VALUE_ZERO;
                    for( TaskSnippetIndex = CIRCLE_VALUE_ZERO; TaskSnippetIndex < Os_Monitor_TaskStackPara[taskIndex].RunTimenum; TaskSnippetIndex++ )
                    {
                        taskRunTimeSum += (uint32)Os_Monitor_TaskStackPara[taskIndex].RunTime[TaskSnippetIndex];
                    }
                    if( MONITOR_VALUE_ZERO < Os_Monitor_TaskStackPara[taskIndex].RunTimenum )
                    {
                        Os_Monitor_TaskStackPara[taskIndex].RunTime_Avg = taskRunTimeSum / Os_Monitor_TaskStackPara[taskIndex].RunTimenum;
                    }
                    break;
                }
            }

            if( OS_MONITOR_EXTENDTASKCOUNT <= extendTaskIndex )
#endif
            {
                taskRunTimeSum = MONITOR_VALUE_ZERO;
                for( TaskSnippetIndex = CIRCLE_VALUE_ZERO; TaskSnippetIndex < Os_Monitor_TaskStackPara[taskIndex].RunTimenum; TaskSnippetIndex++ )
                {
                    taskRunTimeSum += (uint32)Os_Monitor_TaskStackPara[taskIndex].RunTime[TaskSnippetIndex];
                }
                if( MONITOR_VALUE_ZERO < Os_Monitor_TaskStackPara[taskIndex].RunTimenum )
                {
                    Os_Monitor_TaskStackPara[taskIndex].RunTime_Avg = taskRunTimeSum / Os_Monitor_TaskStackPara[taskIndex].RunTimenum;
                }
            }
        }
    }
    for( isrIndex = CIRCLE_VALUE_ZERO; isrIndex < (uint8)OS_ISRID_COUNT; isrIndex++ )
    {
        isrRunTimeSum = MONITOR_VALUE_ZERO;
        for( isrRunTimeNumIndex = CIRCLE_VALUE_ZERO; isrRunTimeNumIndex < Os_Monitor_IsrStackPara[isrIndex].RunTimenum; isrRunTimeNumIndex++ )
        {
            isrRunTimeSum += (uint32)Os_Monitor_IsrStackPara[isrIndex].RunTime[isrRunTimeNumIndex];
        }
        Os_Monitor_IsrStackPara[isrIndex].RunTime_Avg = isrRunTimeSum / Os_Monitor_IsrStackPara[isrIndex].RunTimenum;
    }
}

/*
*******************************************************************************
* Function Name: Os_Monitor_GetCpuLoad
*
* Explanation: Used for load calculation.
*
* Parameters: None
*
* retval: None
*******************************************************************************
*/
LOCAL_INLINE FUNC(void, OS_CODE) Os_Monitor_GetCpuLoad(void)
{
    uint32 currentTimeData = MONITOR_VALUE_ZERO;
    uint32 useTime = MONITOR_VALUE_ZERO;
    uint8 coreIndex = MONITOR_VALUE_ZERO;
    uint8 taskIndex = MONITOR_VALUE_ZERO;
    uint8 isrIndex = MONITOR_VALUE_ZERO;

    for( coreIndex = CIRCLE_VALUE_ZERO; coreIndex < OS_COREID_COUNT; coreIndex++ )
    {
        currentTimeData = (uint32)Os_Counter_GetCntValue(Os_CounterCfgData[Os_Monitor_CoreUseCounterIndex[coreIndex]]);
        useTime = currentTimeData - (uint32)Os_Monitor_CpuLoadkPara[coreIndex].CoreStartRunTime;

        Os_Monitor_CpuLoadkPara[coreIndex].Cpuload =((float32)(useTime - Os_Monitor_TaskStackPara[Os_Monitor_CoreidleTaskMapping[coreIndex]].TimeSum)/(useTime))*MONITOR_COUNTDATA;
        
        Os_Monitor_CpuLoadkPara[coreIndex].CoreStartRunTime = currentTimeData;
        Os_Monitor_TaskStackPara[Os_Monitor_CoreidleTaskMapping[coreIndex]].TimeSum = MONITOR_VALUE_ZERO;
    }
    for( taskIndex = CIRCLE_VALUE_ZERO; taskIndex < (uint8)OS_TASKID_COUNT; taskIndex++ )
    {
        Os_Monitor_TaskStackPara[taskIndex].CpuLoad = ((float32)(Os_Monitor_TaskStackPara[taskIndex].TimeSum)/(useTime))*MONITOR_COUNTDATA;
        Os_Monitor_TaskStackPara[taskIndex].TimeSum = MONITOR_VALUE_ZERO;
        Os_Monitor_TaskStackPara[taskIndex].TimeSum_last = MONITOR_VALUE_ZERO;
    }
    for( isrIndex = CIRCLE_VALUE_ZERO; isrIndex < (uint8)OS_ISRID_COUNT; isrIndex++ )
    {
        Os_Monitor_IsrStackPara[isrIndex].CpuLoad = ((float32)(Os_Monitor_IsrStackPara[isrIndex].TimeSum)/(useTime))*MONITOR_COUNTDATA;
        Os_Monitor_IsrStackPara[isrIndex].TimeSum = MONITOR_VALUE_ZERO;
        Os_Monitor_IsrStackPara[isrIndex].TimeSum_last = MONITOR_VALUE_ZERO;
        Os_Monitor_IsrStackPara[isrIndex].RunTime[0] = MONITOR_VALUE_ZERO;
        Os_Monitor_IsrStackPara[isrIndex].RunTime[1] = MONITOR_VALUE_ZERO;
    }
}

/*
*******************************************************************************
* Function Name: Os_Monitor_MainFunction
*
* Explanation: Module main function,count average execution time, stack, cpu load.
*
* Parameters: None
*
* retval: None
*******************************************************************************
*/
FUNC(void, OS_CODE) Os_Monitor_MainFunction(void)
{
    Os_Monitor_TimeStackCount();
    Os_Monitor_GetCpuLoad ();
}

/*
*******************************************************************************
* Function Name: Os_Monitor_TaskRecordTime
*
* Explanation: Standard task time record.
*
* Parameters: TaskID: task id,CoreId:core id,TicksCount:This execution time.
*
* retval: None
*******************************************************************************
*/
LOCAL_INLINE FUNC(void, OS_CODE) Os_Monitor_TaskRecordTime
(
    TaskType TaskID, CoreIdType CoreId, uint32 TicksCount
)
{
    uint8 runTimeNumIndex = MONITOR_VALUE_ZERO;
    uint32 recordTime = Os_Monitor_TaskStackPara[TaskID].TimeSum - Os_Monitor_TaskStackPara[TaskID].TimeSum_last;

    Os_Monitor_TaskStackPara[TaskID].TimeSum_last = Os_Monitor_TaskStackPara[TaskID].TimeSum;

    if( Os_Monitor_TaskStackPara[TaskID].RunTimenum < OS_MONITOR_BUFFSIZE )
    {
        Os_Monitor_TaskStackPara[TaskID].RunTime[Os_Monitor_TaskStackPara[TaskID].RunTimenum] = recordTime;
        Os_Monitor_TaskStackPara[TaskID].TimeSum = MONITOR_VALUE_ZERO;
        Os_Monitor_TaskStackPara[TaskID].RunTimenum++;
    }
    else
    {
        for( runTimeNumIndex = CIRCLE_VALUE_ZERO; runTimeNumIndex < ( Os_Monitor_TaskStackPara[TaskID].RunTimenum - MONITOR_BLANKBUFF ); runTimeNumIndex++ )
        {
            Os_Monitor_TaskStackPara[TaskID].RunTime[runTimeNumIndex] = Os_Monitor_TaskStackPara[TaskID].RunTime[runTimeNumIndex+1];
        }
        Os_Monitor_TaskStackPara[TaskID].RunTime[OS_MONITOR_BUFFSIZE-MONITOR_BLANKBUFF] = recordTime;
    }

    if( (RunTime_Max_init == MONITOR_FLAGVALUE) &&
        (Os_Monitor_TaskStackPara[TaskID].RunTime_Max < recordTime) && 
        (recordTime < MONITOR_LIMIT) )
    {
        Os_Monitor_TaskStackPara[TaskID].RunTime_Max = recordTime;
    }
}

/*
*******************************************************************************
* Function Name: Os_Monitor_CounterSub
*
* Explanation: Calculate the difference between two times.
*
* Parameters: Counter: Counter's configuration.
*             Value: Current value.
*             Sub: Last value.
*
* retval: None
*******************************************************************************
*/
FUNC(Os_TickType, OS_CODE) Os_Monitor_CounterSub
(
    P2CONST(Os_CounterBaseCfgType, AUTOMATIC, OS_CONST) Counter,
    Os_TickType Value,
    Os_TickType Sub
)
{
    Os_TickType result;

    /* Perform the operation */
    result = Value - Sub;

    /* Perform modulo. */
    if( Value < Sub )
    {
        result += (Counter->maxAllowValue + 1);
    }

    return result;
}

/*
*******************************************************************************
* Function Name: Os_Monitor_StartTimeDeal
*
* Explanation: Processing task start time.
*
* Parameters: None
*
* retval: None
*******************************************************************************
*/
FUNC(void, OS_CODE) Os_Monitor_StartTimeDeal(void)
{
    TaskType TaskID = INVALID_TASK;
    CoreIdType CoreId = OS_CORE_ID_MASTER;
    uint32 ticksCount = MONITOR_VALUE_ZERO;
    uint32 currentTick = MONITOR_VALUE_ZERO;

    CoreId = GetCoreID();

    if( TRUE == Os_Monitor_Init_status )
    {
        if( MONITOR_FLAGVALUE == Os_Monitor_IsrInterruptFlag[CoreId] )
        {
            currentTick = (uint32)Os_Counter_GetCntValue(Os_CounterCfgData[Os_Monitor_CoreUseCounterIndex[CoreId]]);
            ticksCount = (uint32)Os_Monitor_CounterSub(Os_CounterCfgData[Os_Monitor_CoreUseCounterIndex[CoreId]], currentTick,
                    Os_Monitor_TaskStackPara[Os_Monitor_CoreRunTask[CoreId]].StartResumesTime);

            Os_Monitor_TaskStackPara[Os_Monitor_CoreRunTask[CoreId]].TimeSum += ticksCount;
        }
        else
        {
            if(( MONITOR_VALUE_ZERO == Os_Monitor_IsrInterruptFlag[CoreId] ) && ( GetTaskID(&TaskID) == E_OK ))
            {
                Os_Monitor_CoreRunTask[CoreId] = (TaskType) TaskID;
                currentTick = (uint32)Os_Counter_GetCntValue(Os_CounterCfgData[Os_Monitor_CoreUseCounterIndex[CoreId]]);
                Os_Monitor_TaskStackPara[TaskID].StartResumesTime = currentTick;
            }
        }
    }
    else
    {
        if(( MONITOR_VALUE_ZERO == Os_Monitor_IsrInterruptFlag[CoreId] ) && ( GetTaskID(&TaskID) == E_OK ))
        {
            Os_Monitor_CoreRunTask[CoreId] = (TaskType)TaskID;
        }
    }
}

/*
*******************************************************************************
* Function Name: Os_Monitor_EndTimeDeal
*
* Explanation: Processing task end time.
*
* Parameters: None
*
* retval: None
*******************************************************************************
*/
FUNC(void, OS_CODE) Os_Monitor_EndTimeDeal(void)
{
    TaskType TaskID = INVALID_TASK;
    CoreIdType CoreId = OS_CORE_ID_MASTER;
    uint32 ticksCount = MONITOR_VALUE_ZERO;
    uint32 currentTick = MONITOR_VALUE_ZERO;
    if( TRUE == Os_Monitor_Init_status )
    {
        CoreId = GetCoreID();

        TaskID = Os_Monitor_CoreRunTask[CoreId];
        if( FALSE == Os_Monitor_Cat2Interrupttotask[CoreId] )
        {
            currentTick = (uint32)Os_Counter_GetCntValue(Os_CounterCfgData[Os_Monitor_CoreUseCounterIndex[CoreId]]);
            ticksCount = (uint32)Os_Monitor_CounterSub(Os_CounterCfgData[Os_Monitor_CoreUseCounterIndex[CoreId]], currentTick, Os_Monitor_TaskStackPara[TaskID].StartResumesTime);

            Os_Monitor_TaskStackPara[Os_Monitor_CoreRunTask[CoreId]].TimeSum += ticksCount;
            /*If interreput sum,if Terminate RunTime[OS_MONITOR_BUFFSIZE]= sum, sum = 0*/
            if( TRUE == Os_Monitor_TaskTerminateFlag[CoreId] )
            {
                Os_Monitor_TaskRecordTime(TaskID, CoreId, ticksCount);
                Os_Monitor_TaskTerminateFlag[CoreId] = FALSE;
            }
            else
            {
                Os_Monitor_TaskStackPara[TaskID].TimeSum += ticksCount;
            }
        }
        else
        {
            Os_Monitor_Cat2Interrupttotask[CoreId] = FALSE;
        }
    }
}

/*
*******************************************************************************
* Function Name: Os_Monitor_IsrRecordTime
*
* Explanation: Record isrcat2 execution time.
*
* Parameters: IsrId: isrcat2 id.
*             TicksCount: execution time.
*             CoreId: core id.
*             IsrFinished: Finish flag.
* retval: None
*******************************************************************************
*/
FUNC(void, OS_CODE) Os_Monitor_IsrRecordTime(ISRType IsrId, uint32 TicksCount, CoreIdType CoreId, uint32 IsrFinished)
{
    uint32 recordTime = TicksCount;

    Os_Monitor_IsrStackPara[IsrId].TimeSum += TicksCount;
    /* Record whole runtime. */
    if ( MONITOR_ISR_FINISHED == IsrFinished )
    {
        Os_Monitor_IsrStackPara[IsrId].RunTime[MONITOR_ISR_UNFINISHED] = recordTime + Os_Monitor_IsrStackPara[IsrId].RunTime[MONITOR_ISR_FINISHED];
        Os_Monitor_IsrStackPara[IsrId].RunTime[MONITOR_ISR_FINISHED] = MONITOR_VALUE_ZERO;
        Os_Monitor_CoreRunIsr[CoreId] = INVALID_ISR;
    }
    /* Record interrupted runtime. */
    else 
    {
        Os_Monitor_IsrStackPara[IsrId].RunTime[MONITOR_ISR_FINISHED] += recordTime;
        Os_Monitor_CoreRunIsr[CoreId] = INVALID_ISR;
    }
    if( (RunTime_Max_init == MONITOR_FLAGVALUE) &&
        (Os_Monitor_IsrStackPara[IsrId].RunTime_Max < Os_Monitor_IsrStackPara[IsrId].RunTime[MONITOR_ISR_UNFINISHED]) &&
        (Os_Monitor_IsrStackPara[IsrId].RunTime[MONITOR_ISR_UNFINISHED] < MONITOR_ISR_LIMIT) &&
        (IsrFinished == OS_ONE_VALUE))
    {
        Os_Monitor_IsrStackPara[IsrId].RunTime_Max = Os_Monitor_IsrStackPara[IsrId].RunTime[MONITOR_ISR_UNFINISHED];
    }
}

/*
*******************************************************************************
* Function Name: Os_Monitor_IsrEntry
*
* Explanation: Record isrcat2 execution time.
*
* Parameters: CoreId: core id. 
*             isrCfg: Reference to an isr.
* retval: None
*******************************************************************************
*/
FUNC(void, OS_CODE) Os_Monitor_IsrEntry
(
    CoreIdType coreId,
    P2CONST(Os_IsrCfgType, AUTOMATIC, OS_APPL_CONST) isrCfg
)
{
    uint32 ticksCurrent = OS_ZERO_VALUE;
    uint32 useTicksCount = OS_ZERO_VALUE;

    Pre_IsrQnum[coreId] = Os_Monitor_IsrInterruptFlag[coreId];
    Isr_Queue[Os_Monitor_IsrInterruptFlag[coreId]][coreId] = isrCfg->isrId; 
    Os_Monitor_IsrInterruptFlag[coreId] = Os_Monitor_IsrInterruptFlag[coreId] + OS_ONE_VALUE;

    /* Only one isr. */
    if( Os_Monitor_IsrInterruptFlag[coreId] == OS_ONE_VALUE ) 
    {
        ticksCurrent = Os_Counter_GetCntValue(Os_CounterCfgData[Os_Monitor_CoreUseCounterIndex[coreId]]);
        Os_Monitor_IsrStackPara[isrCfg->isrId].StartResumesTime = ticksCurrent;
    }
    /* Isr nest occured. */
    else 
    {
        /* record current StartTime. */
        ticksCurrent = Os_Counter_GetCntValue(Os_CounterCfgData[Os_Monitor_CoreUseCounterIndex[coreId]]);
        Os_Monitor_IsrStackPara[isrCfg->isrId].StartResumesTime = ticksCurrent;

        /* record last UseTime. */
        Pre_IsrQnum[coreId] = Pre_IsrQnum[coreId] - OS_ONE_VALUE;
        Last_isrId = Isr_Queue[Pre_IsrQnum[coreId]][coreId];
        useTicksCount = Os_Monitor_CounterSub(Os_CounterCfgData[Os_Monitor_CoreUseCounterIndex[coreId]], ticksCurrent,
                                          Os_Monitor_IsrStackPara[Last_isrId].StartResumesTime);
        Os_Monitor_IsrRecordTime(Last_isrId, useTicksCount, coreId, MONITOR_ISR_UNFINISHED);

    }

}

/*
*******************************************************************************
* Function Name: Os_Monitor_IsrExit
*
* Explanation: Record isrcat2 execution time.
*
* Parameters: CoreId: core id. 
*             isrCfg: Reference to an isr.
* retval: None
*******************************************************************************
*/
FUNC(void, OS_CODE) Os_Monitor_IsrExit
(
    CoreIdType coreId,
    P2CONST(Os_IsrCfgType, AUTOMATIC, OS_APPL_CONST) isrCfg
)
{
    uint32 ticksCurrent = OS_ZERO_VALUE;
    uint32 useTicksCount = OS_ZERO_VALUE;

    Pre_IsrQnum[coreId] = Os_Monitor_IsrInterruptFlag[coreId];

    Os_Monitor_CoreRunIsr[coreId] = isrCfg->isrId;
    /* only one isr. */
    if( Os_Monitor_IsrInterruptFlag[coreId] == OS_ONE_VALUE ) 
    {

        ticksCurrent = Os_Counter_GetCntValue(Os_CounterCfgData[Os_Monitor_CoreUseCounterIndex[coreId]]);
        useTicksCount = Os_Monitor_CounterSub(Os_CounterCfgData[Os_Monitor_CoreUseCounterIndex[coreId]], ticksCurrent,
                                              Os_Monitor_IsrStackPara[Os_Monitor_CoreRunIsr[coreId]].StartResumesTime);

        Os_Monitor_IsrRecordTime(isrCfg->isrId, useTicksCount, coreId, MONITOR_ISR_FINISHED);

    }
    else
    {
        /* for current isr */
        ticksCurrent = Os_Counter_GetCntValue(Os_CounterCfgData[Os_Monitor_CoreUseCounterIndex[coreId]]);
        useTicksCount = Os_Monitor_CounterSub(Os_CounterCfgData[Os_Monitor_CoreUseCounterIndex[coreId]], ticksCurrent,
                                              Os_Monitor_IsrStackPara[Os_Monitor_CoreRunIsr[coreId]].StartResumesTime);

        Os_Monitor_IsrRecordTime(isrCfg->isrId, useTicksCount, coreId, MONITOR_ISR_FINISHED);

        /* for last isr. */
        /* get current isr Qnum */
        Pre_IsrQnum[coreId] = Pre_IsrQnum[coreId] - OS_ONE_VALUE; 
        /* get last isr Qnum */
        Pre_IsrQnum[coreId] = Pre_IsrQnum[coreId] - OS_ONE_VALUE;
        Last_isrId = Isr_Queue[Pre_IsrQnum[coreId]][coreId];
        Os_Monitor_IsrStackPara[Last_isrId].StartResumesTime = ticksCurrent;
    }
    /* Exit from current ISR. */
    Os_Monitor_IsrInterruptFlag[coreId] = Os_Monitor_IsrInterruptFlag[coreId] - OS_ONE_VALUE;
}

#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"

#endif
