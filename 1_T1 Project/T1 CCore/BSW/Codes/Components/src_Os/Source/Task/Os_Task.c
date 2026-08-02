/*
********************************************************************************
*
*  File name: Os_Task.c
*
*  Copyright Neusoft Reach Corporation. All rights reserved.
*
********************************************************************************
*
* History
*-------------------------------------------------------------------------------
********************************************************************************
* Version: 3.0
* Author/Date: HanCL/2021.11.18
* Change: New create.
* Cause: New
********************************************************************************
* Version: 3.1
* Author/Date: LiG/2022.11.15
* Change: Increase judgment on the status of extended tasks.
* Cause: Bugfix
********************************************************************************
* Version: 3.2
* Author/Date: ZhangY/2022.11.18
* Change: Fix the bug of repeated execution of extended tasks.
* Cause: Bugfix
********************************************************************************
* Version: 3.3
* Author/Date: JiangGL/2022.11.23
* Change: Solve the problem of system exceptions caused by task switching.
* Cause: Bugfix
********************************************************************************
* Version: 3.4
* Author/Date: JiangGL/2022.11.24
* Change: Fix the bug of repeated execution of extended tasks.
*         Fix the problem that context switching is the same task.
* Cause: Bugfix
********************************************************************************
* Version: 3.5
* Author/Date: JiangGL/2022.12.25
* Change: Fix that when TerminateTask or ChainTask is not called to end the task, 
          errorHook is not called in the running state.
* Cause: Bugfix
********************************************************************************
* Version: 3.6
* Author/Date: LiG/2023.1.29
* Change: Resolve the CallErrorHook privilege level problem.
* Cause: Optimization
********************************************************************************
* Version: 3.7
* Author/Date: LiG/2023.2.14
* Change: Memory protection code optimization and notes optimization.
* Cause: Optimization
********************************************************************************
* Version: 3.8
* Author/Date: LiG/2023.2.15
* Change: Modified for QAC.
* Cause: Optimization
********************************************************************************
* Version: 3.9
* Author/Date: LiG/2023.3.28
* Change: Os_Task_WrongReturn function adds a self scheduling function.
* Cause: Bugfix
********************************************************************************
* Version: 3.10
* Author/Date: LiG/2023.4.4
* Change: Adapt to ORTI.
* Cause: Update
********************************************************************************
* Version: 3.11
* Author/Date: LiG/2023.4.4
* Change: Resolve compilation warnings and remove useless parameters.
* Cause: Update
********************************************************************************
* Version: 3.12
* Author/Date: LiG/2023.4.4
* Change: Resolve compilation issues.
* Cause: Update
********************************************************************************
* Version: 3.13
* Author/Date: LiG/2023.5.27
* Change: Modified for QAC.
* Cause: Optimization
********************************************************************************
* Version: 3.14
* Author/Date: ZhangY/2023.6.8
* Change: Resolve the issue of abnormal entry of the M core.
* Cause: Bugfix
********************************************************************************
*/
/*
********************************************************************************
*    Includes
********************************************************************************
*/
#include "Os_Cfg.h"
#include "Os_Task.h"
#include "Os_App.h"
#include "Os_Core.h"
#include "Os_Resource.h"
#include "Os_Spinlock.h"
#include "Os_Arch_Mach.h"
#include "Os_SysCall.h"
#include "Os_Stack.h"
#include "Os_MultiCore.h"
#include "Os_Hook.h"
#include "Os_MemProtection.h"
#include "Os.h"
#include "Os_Monitor_Cfg.h"
#if (OS_MONITOR_ENABLE == STD_ON)
#include "Os_Monitor.h"
#endif

/*
********************************************************************************
*    Local Macros
********************************************************************************
*/
/* Process pretask hooks. */
#define OS_PRETASKHOOK(taskCfg) do{ if((taskCfg)->preTaskHook != NULL_PTR)    \
                                    {(taskCfg)->preTaskHook();}               \
                                }while(0)                                     \

/* Process postask hooks. */
#define OS_POSTTASKHOOK(taskCfg) do{ if((taskCfg)->postTaskHook != NULL_PTR)  \
                                    {(taskCfg)->postTaskHook();}              \
                                }while(0)                                     \

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

static FUNC(void, OS_CODE) Os_Task_TaskReset
(
    P2CONST(Os_TaskCfgType, AUTOMATIC, OS_APPL_CONST) taskCfg
);

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
/*
********************************************************************************
* Function Name: Os_Task_TaskReset
*
* Explanation: Internal function uses to reset task.
*
* param: taskCfg: Reference to an task.
*
* retval: None
********************************************************************************
*/
static FUNC(void, OS_CODE) Os_Task_TaskReset
(
    P2CONST(Os_TaskCfgType, AUTOMATIC, OS_APPL_CONST) taskCfg
)
{
#if( OS_STACK_OVERFLOW_CHECK == STD_ON )
    /* Check stack overflow. */
    Os_Stack_Measure(taskCfg->contextCfg->stackEndAddr);
#endif
#if( OS_MONITOR_ENABLE == STD_ON )
    Os_Monitor_EndTimeDeal();
#endif
    /* Set core the next process id. */
    OS_CORE_SETPROTYPE(taskCfg->coreId, OS_POSTTASKHOOK_TYPE_MASK);
    /* Post-Task hook. */
    OS_POSTTASKHOOK(taskCfg);
    /* Set core the next process id. */
    OS_CORE_SETPROTYPE(taskCfg->coreId, OS_TASK_TYPE_MASK);
    /* If the task activation is not the maximum. */
    if( taskCfg->taskDyn->activationsCnt != taskCfg->maxActivations )
    {
        /* Set task state to READY. */
        taskCfg->taskDyn->state = READY;
        /*T1 task activation*/
        OSTH_TASK_RESET_ACTIVATION(taskCfg->coreId,taskCfg->taskId);
    }
    else
    {
        /* Set task state to SUSPENDED. */
        taskCfg->taskDyn->state = SUSPENDED;
        /*T1 task stop*/
        OSTH_TASK_RESET_TERMINATION(taskCfg->coreId,taskCfg->taskId);

    }

    /* Clear event mask. */
    taskCfg->taskDyn->eventDyn.Triggered = OS_ZERO_VALUE;
    taskCfg->taskDyn->eventDyn.Waiting = OS_ZERO_VALUE;
    /* Set task priority. */
    taskCfg->taskDyn->currentPrio = taskCfg->cfgPrio;

#if( (OS_CFG_SCALABILITY_CLASS == OS_SC2) || (OS_CFG_SCALABILITY_CLASS == OS_SC4) )
    if( OS_CORE_CHECKTPISENABLE(taskCfg->coreId) )
    {
        /* Reset current budget. */
        Os_Tp_ResetCurrentBudget(taskCfg->tpCfg, taskCfg->coreId);
    }
#endif
}

/*
********************************************************************************
* Function Name: Os_Task_Init
*
* Explanation: uses to init task.
*
* param: taskCfg: Reference to an task.
*        AppModeType: Application mode.
*
* retval: None
********************************************************************************
*/
FUNC(void, OS_CODE) Os_Task_Init
(
    P2CONST(Os_TaskCfgType, AUTOMATIC, OS_APPL_CONST) taskCfg,
    AppModeType appMode
)
{
    /* Check the taskCfg is not NULL_PTR. */
    Os_ParamCheck(NULL_PTR != taskCfg);

    /* Initialize the stack. */
    Os_Arch_Context_Stack_Init(taskCfg->contextCfg);
    /* Set context pointer address. */
    taskCfg->taskDyn->context = taskCfg->contextCfg->contextDyn;
    /* Initialize the context. */
    Os_Arch_Context_Init(taskCfg->taskDyn->context, taskCfg->contextCfg);

#if( OS_CFG_RESOURCE_ENABLE == STD_ON )
    Os_List_Init(&taskCfg->taskDyn->resListHead);
#endif

#if( OS_CFG_SPINLOCK_ENABLE == STD_ON )
    Os_List_Init(&taskCfg->taskDyn->spinListHead);
#endif
    /* Clear event mask. */
    taskCfg->taskDyn->eventDyn.Triggered = OS_ZERO_VALUE;
    taskCfg->taskDyn->eventDyn.Waiting = OS_ZERO_VALUE;
    /* Set schedule type. */
    taskCfg->taskDyn->schdType = taskCfg->schdType;
    /* Set task id. */
    taskCfg->taskDyn->taskId = taskCfg->taskId;
    /* Set task priority. */
    taskCfg->taskDyn->currentPrio = taskCfg->cfgPrio;
    /* Set task state to SUSPENDED. */
    taskCfg->taskDyn->state = SUSPENDED;
    /* Set task activation counter. */
    taskCfg->taskDyn->activationsCnt = taskCfg->maxActivations;
    /* Set dynamic appId. */
    taskCfg->taskDyn->currentAppId = taskCfg->ownerAppId;
    /* If auto start. */
    if( (taskCfg->appMode & appMode) != OS_ZERO_VALUE )
    {
        /* Set task state to READY. */
        taskCfg->taskDyn->state = READY;
        /*T1 task activation*/
        OSTH_TASK_INIT_ACTIVATION(taskCfg->coreId,taskCfg->taskId);
        /* Decrease activation counter. */
        taskCfg->taskDyn->activationsCnt--;
        /* Insert tasks into the scheduler. */
        (void)Os_Schedler_InsertTask(OS_CORE_GETSCHEDULER(taskCfg->coreId), taskCfg->taskDyn);
    }
#if( (OS_CFG_SCALABILITY_CLASS == OS_SC2) || (OS_CFG_SCALABILITY_CLASS == OS_SC4) )
    if( OS_CORE_CHECKTPISENABLE(taskCfg->coreId) )
    {
        Os_Tp_Init(taskCfg->tpCfg);
    }
#endif

#if( (OS_CFG_ORTI_ENABLE == STD_ON) && (OS_CFG_ORTI_HOOK_ENABLE == STD_ON) )
    /* Call orti hook. */
    Os_Orit_TaskState_Trigger(taskCfg->coreId, taskCfg->taskId, OS_ORTI_TASK_INIT_TRIGGER);
#endif
}

/*
********************************************************************************
* Function Name: Os_Task_SetNextTaskData
*
* Explanation: Uses to set the next task parameter.
*
* param: nextCfg: Next task.
*
* retval: None
********************************************************************************
*/
FUNC(void, OS_CODE)  Os_Task_SetNextTaskData
(
    P2CONST(Os_TaskCfgType, AUTOMATIC, OS_APPL_CONST) nextCfg
)
{
#if( (OS_CFG_SCALABILITY_CLASS == OS_SC2) || (OS_CFG_SCALABILITY_CLASS == OS_SC4) )
    if( OS_CORE_CHECKTPISENABLE(nextCfg->coreId) )
    {
        Os_Tp_StartNextBudget(nextCfg->tpCfg, nextCfg->coreId);
    }
#endif

#if( (OS_CFG_SCALABILITY_CLASS == OS_SC3) || (OS_CFG_SCALABILITY_CLASS == OS_SC4) )
    /* The app is configured with memory protection. */
    (void)Os_Mp_Switch(TRUE, nextCfg->appMpCfg);
    /* The task is configured with memory protection. */
    (void)Os_Mp_Switch(FALSE, nextCfg->taskMpCfg);
    /* Switch to the next stack protection range.*/
    Os_Arch_MpStackSwitch(nextCfg->contextCfg->stackStartAddr, nextCfg->contextCfg->stackEndAddr);
#endif
    /* Get task running data. */
    Os_TaskDynType* next = OS_TASK_GETDYN(nextCfg);
    /* Set next task state to RUNNING. */
    next->state = RUNNING;
    /*T1 task start*/
    OSTH_TASK_SETNEXTTASKDATA_START(nextCfg->coreId,nextCfg->taskId);
    
    /* Set core current task dyn. */
    OS_CORE_SETCURRTASK(nextCfg->coreId,nextCfg->taskDyn);
    /* Set core current app. */
    OS_CORE_SETAPPID(nextCfg->coreId, nextCfg->taskDyn->currentAppId);
#if (OS_MONITOR_ENABLE == STD_ON)
    Os_Monitor_StartTimeDeal();
#endif
    /* Set core the next process id. */
    OS_CORE_SETPROTYPE(nextCfg->coreId, OS_PRETASKHOOK_TYPE_MASK);
    /* Pre-Task hook. */
    OS_PRETASKHOOK(nextCfg);
    /* Set core the next process id. */
    OS_CORE_SETPROTYPE(nextCfg->coreId, OS_TASK_TYPE_MASK);
}

/*
********************************************************************************
* Function Name: Os_Task_TaskSwitch
*
* Explanation: Uses to switch task.
*
* param: currentCfg: Reference to current task.
*        nextCfg: Reference to next task.
*
* retval: E_OS_OK: No error.
*         E_OS_PARAM_POINTER: A null pointer was given as argument.
********************************************************************************
*/
FUNC(Os_StatusType, OS_CODE) Os_Task_TaskSwitch
(
    P2CONST(Os_TaskCfgType, AUTOMATIC, OS_APPL_CONST) currentCfg,
    P2CONST(Os_TaskCfgType, AUTOMATIC, OS_APPL_CONST) nextCfg
)
{
    Os_StatusType ret = E_OS_OK;
    CoreIdType coreId = Os_Core_GetLogicId();

    /* If the input is not NULL. */
    if( (currentCfg != NULL_PTR) && (nextCfg != NULL_PTR) )
    {
        if( currentCfg != nextCfg )
        {
            Os_TaskDynType* current = OS_TASK_GETDYN(currentCfg);
#if( OS_STACK_OVERFLOW_CHECK == STD_ON )
            /* Check stack overflow. */
            Os_Stack_Measure(currentCfg->contextCfg->stackEndAddr);
#endif
#if( OS_MONITOR_ENABLE == STD_ON )
            Os_Monitor_TaskTerminateFlag[coreId] = TRUE;
            Os_Monitor_EndTimeDeal();
#endif
            /* Set core the next process id. */
            OS_CORE_SETPROTYPE(currentCfg->coreId, OS_POSTTASKHOOK_TYPE_MASK);
            /* Post-Task hook. */
            OS_POSTTASKHOOK(currentCfg);
            /* Set core the next process id. */
            OS_CORE_SETPROTYPE(currentCfg->coreId, OS_TASK_TYPE_MASK);
            /* If current task is extended task type. */
            if( OS_TASK_ET == currentCfg ->taskType )
            {
                current->state = WAITING;
                /*T1 task waiting*/
                OSTH_TASK_SWITCH_WAIT(currentCfg->coreId,currentCfg->taskId);
            }
            /* If current task state is not WAITING. */
            if( current->state != WAITING )
            {
                /* Set current task state to READY. */
                current->state = READY;
                /*T1 task release*/
                OSTH_TASK_SWITCH_RELEASE(currentCfg->coreId,currentCfg->taskId);
            }

#if( (OS_CFG_SCALABILITY_CLASS == OS_SC2) || (OS_CFG_SCALABILITY_CLASS == OS_SC4) )
            if( OS_CORE_CHECKTPISENABLE(currentCfg->coreId) )
            {
                /* if now tp is sys tp */
                if( OS_CORE_GETTPCURRENTBUDGET(currentCfg->coreId) != NULL_PTR )
                {
                    Os_Tp_SaveCurrenBudget(currentCfg->tpCfg, currentCfg->coreId);
                }
            }
#endif

#if( (OS_CFG_ORTI_ENABLE == STD_ON) && (OS_CFG_ORTI_HOOK_ENABLE == STD_ON) )
        /* Call orti hook. */
            Os_Orit_TaskState_Trigger(currentCfg->coreId, currentCfg->taskId, OS_ORTI_TASK_SWITCH_TRIGGER);
            Os_Orit_TaskState_Trigger(nextCfg->coreId, nextCfg->taskId, OS_ORTI_TASK_SWITCH_TRIGGER);
#endif

#if( OS_ARCH == ARCH_CONTEXT_M )
            Os_Arch_TaskSwitch_ForCortextM();
#else
            Os_Task_SetNextTaskData(nextCfg);
            Os_Arch_Context_Switch(currentCfg->taskDyn->context, nextCfg->taskDyn->context);
#endif
        }
    }
    else
    {
        ret = E_OS_PARAM_POINTER;
    }

    return ret;
}

/*
********************************************************************************
* Function Name: Os_Task_SetEvent
*
* Explanation: Internal function uses to set event.
*
* param: taskCfg: Reference to an task.
*
* retval: E_OS_OK: No error.
*         E_OS_PARAM_POINTER: A null pointer was given as argument.
********************************************************************************
*/
FUNC(Os_StatusType, OS_CODE) Os_Task_SetEvent
(
    P2CONST(Os_TaskCfgType, AUTOMATIC, OS_APPL_CONST) taskCfg
)
{
    Os_TaskDynType* nextDyn;
    Os_TaskDynType* currentDyn;
    const Os_TaskCfgType* currnetTaskCfg;
    CoreIdType currentCoreId;
    Os_StatusType ret = E_OS_OK;

    if( taskCfg != NULL_PTR )
    {
        /* Set current Core Id. */
        currentCoreId = taskCfg->coreId;

        if( WAITING == taskCfg->taskDyn->state )
        {
            /* Set task state to READY. */
            taskCfg->taskDyn->state = READY;
            /*T1 task release*/
            OSTH_TASK_SETEVENT_RELEASE(currentCoreId,taskCfg->taskId);
            /* Insert tasks into the scheduler. */
            ret = Os_Schedler_InsertTask(OS_CORE_GETSCHEDULER(currentCoreId), taskCfg->taskDyn);
        }

        if( (TRUE == OS_CORE_GETALLOWSCH(currentCoreId)) && (OS_CORE_CHECKCURRENTINTASK(currentCoreId)) )
        {
            /* Get current process task. */
            currentDyn = OS_CORE_GETCURRENTTASK(currentCoreId);
            /* Get current task configuration data. */
            currnetTaskCfg = OS_TASK_GETCFG(currentDyn->taskId);

            if( TRUE == Os_Schedler_NeedSchedle(OS_CORE_GETSCHEDULER(currentCoreId)) )
            {
                /* Execute a schedule. */
                nextDyn = Os_Schedler_Schedle(OS_CORE_GETSCHEDULER(currentCoreId));
                ret = Os_Task_TaskSwitch(currnetTaskCfg, OS_TASK_GETCFG(nextDyn->taskId));
            }
        }
    }
    else
    {
       ret = E_OS_PARAM_POINTER;
    }

    return ret;
}

/*
********************************************************************************
* Function Name: Os_Task_WaitEvent
*
* Explanation: Internal function uses to wait event.
*
* param: taskCfg: Reference to an task.
*
* retval: E_OS_OK: No error.
*         E_OS_PARAM_POINTER: A null pointer was given as argument.
********************************************************************************
*/
FUNC(Os_StatusType, OS_CODE) Os_Task_WaitEvent
(
    P2CONST(Os_TaskCfgType, AUTOMATIC, OS_APPL_CONST) taskCfg
)
{
    Os_TaskDynType* nextDyn;
    Os_StatusType ret;

    if( taskCfg != NULL_PTR )
    {
        /* Delete the task from the scheduler. */
        (void)Os_Schedler_DeleteTask(OS_CORE_GETSCHEDULER(taskCfg->coreId), taskCfg->taskDyn);
#if( (OS_CFG_SCALABILITY_CLASS == OS_SC2) || (OS_CFG_SCALABILITY_CLASS == OS_SC4) )
        if( OS_CORE_CHECKTPISENABLE(taskCfg->coreId) )
        {
            Os_Tp_ResetCurrentBudget(taskCfg->tpCfg, taskCfg->coreId);
        }
#endif
        /* Execute a schedule. */
        nextDyn = Os_Schedler_Schedle(OS_CORE_GETSCHEDULER(taskCfg->coreId));
        ret = Os_Task_TaskSwitch(taskCfg, OS_TASK_GETCFG(nextDyn->taskId));
    }
    else
    {
        ret = E_OS_PARAM_POINTER;
    }

    return ret;
}

/*
********************************************************************************
* Function Name: Os_Task_AppTerminateTask
*
* Explanation: Terminate task, uses to application termination.
*
* param: taskCfg: Reference to an task.
*
* retval: None
********************************************************************************
*/
FUNC(void, OS_CODE) Os_Task_AppTerminateTask
(
    P2CONST(Os_TaskCfgType, AUTOMATIC, OS_APPL_CONST) taskCfg
)
{
    CoreIdType coreId;

    /* Get logic core id. */
    coreId = Os_Core_GetLogicId();
    if( taskCfg != NULL_PTR ) /* If task id is out range. */
    {
        if( OS_TASK_MASK_RESOURCE(taskCfg) ) /* If the resource is release. */
        {
            Os_Resource_ForceReleaseAll(OS_TASK_GETRESLISTHEAD(taskCfg->taskDyn));
        }
        if( OS_TASK_MASK_SPINLOCK(taskCfg) ) /* If the spinlock is release. */
        {
            Os_Spinlock_ForceReleaseAll(OS_TASK_GETSPINLISTHEAD(taskCfg->taskDyn));
        }

#if( OS_STACK_OVERFLOW_CHECK == STD_ON )
        /* Check stack overflow. */
        Os_Stack_Measure(taskCfg->contextCfg->stackEndAddr);
#endif
        if( OS_CORE_PROCESSTYPEMATCH(coreId, OS_SYS_TYPE_MASK) ) /* If the api is not accessible. */
        {
            /* Set core the next process id. */
            OS_CORE_SETPROTYPE(taskCfg->coreId, OS_POSTTASKHOOK_TYPE_MASK);
            /* Post-Task hook. */
            OS_POSTTASKHOOK(taskCfg);
            /* Set core the next process id. */
            OS_CORE_SETPROTYPE(taskCfg->coreId, OS_TASK_TYPE_MASK);
        }
        /* Set task activation counter. */
        taskCfg->taskDyn->activationsCnt = taskCfg->maxActivations;
        /* Set task state to SUSPENDED. */
        taskCfg->taskDyn->state = SUSPENDED;
        /*T1 task stop*/
        OSTH_TASK_APPTERMINATETASK_TERMINATE(coreId, taskCfg->taskId);
        /* Clear event mask. */
        taskCfg->taskDyn->eventDyn.Triggered = OS_ZERO_VALUE;
        taskCfg->taskDyn->eventDyn.Waiting = OS_ZERO_VALUE;
        /* Set task priority. */
        taskCfg->taskDyn->currentPrio = taskCfg->cfgPrio;
        /* Delete the task from the scheduler. */
        (void)Os_Schedler_DeleteTaskAll(OS_CORE_GETSCHEDULER(taskCfg->coreId), taskCfg->taskDyn);

#if( (OS_CFG_SCALABILITY_CLASS == OS_SC2) || (OS_CFG_SCALABILITY_CLASS == OS_SC4) )
        if( OS_CORE_CHECKTPISENABLE(taskCfg->coreId) )
        {
            Os_Tp_ResetCurrentBudget(taskCfg->tpCfg, taskCfg->coreId);
        }
#endif
    }
}

/*
********************************************************************************
* Function Name: Os_Task_AppTerminateTaskSwitch
*
* Explanation: Task switch, uses to application termination.
*
* param: appId: application index.
*
* retval: None
********************************************************************************
*/
FUNC(void, OS_CODE) Os_Task_AppTerminateTaskSwitch(ApplicationType appId)
{
    const Os_TaskCfgType* taskCfg;
    const Os_TaskCfgType* nextTaskCfg;
    Os_TaskDynType* currentDyn;
    Os_TaskDynType* nextDyn;
    CoreIdType coreId;

    /* Get the current logical core id. */
    coreId = Os_Core_GetLogicId();

    if( TRUE == OS_CORE_GETALLOWSCH(coreId) )
    {
        /* Execute a schedule. */
        nextDyn = Os_Schedler_Schedle(OS_CORE_GETSCHEDULER(coreId));
        /* Get current process task. */
        currentDyn = OS_CORE_GETCURRENTTASK(coreId);
        /* Get current task configuration data. */
        taskCfg = OS_TASK_GETCFG(currentDyn->taskId);
        /* Get next task configuration data. */
        nextTaskCfg = OS_TASK_GETCFG(nextDyn->taskId);
        /* If current task is belongs to the app. */
        if( appId == OS_TASK_GETAPPID(taskCfg) )
        {
#if( (OS_CFG_SCALABILITY_CLASS == OS_SC2) || (OS_CFG_SCALABILITY_CLASS == OS_SC4) )
            if( OS_CORE_CHECKTPISENABLE(taskCfg->coreId) )
            {
                Os_Tp_ResetCurrentBudget(taskCfg->tpCfg, taskCfg->coreId);
            }
#endif

#if( (OS_CFG_ORTI_ENABLE == STD_ON) && (OS_CFG_ORTI_HOOK_ENABLE == STD_ON) )
            /* Call orti hook. */
            Os_Orit_TaskState_Trigger(taskCfg->coreId, taskCfg->taskId, OS_ORTI_TASK_TERMINATED_TRIGGER);
#endif

#if( OS_ARCH == ARCH_CONTEXT_M )
            Os_Arch_TaskTerminate_ForCortextM();
#else
            Os_Task_SetNextTaskData(nextTaskCfg);
            Os_Arch_ResetContext_Switch(taskCfg->contextCfg, nextTaskCfg->taskDyn->context);
#endif
        }
        else
        {
            (void)Os_Task_TaskSwitch(taskCfg, nextTaskCfg);
        }
    }
}

/*
********************************************************************************
* Function Name: Os_Task_WrongReturn
*
* Explanation: Called when task wrong return.
*
* param: None
*
* retval: None
********************************************************************************
*/
FUNC(void, OS_CODE) Os_Task_WrongReturn(void)
{
    CoreIdType coreId;
    const Os_TaskCfgType* taskCfg;
    Os_Arch_IntState intState;

    /* Get the current logical core id. */
    coreId = Os_Core_GetLogicId();

    /* Disable interrupt. */
    Os_Arch_IntDisable(&intState);
    /* Get task configuration data. */
    taskCfg = OS_TASK_GETCFG(OS_CORE_GETCURRENTTASKID(coreId));

    /* Call error hook. */
    (void)Os_Hook_CallErrorHook(OSServiceId_TaskWrongReturn, E_OS_MISSINGEND);

    /* If the resource is release. */
    if( OS_TASK_MASK_RESOURCE(taskCfg) )
    {
        Os_Resource_ForceReleaseAll(OS_TASK_GETRESLISTHEAD(taskCfg->taskDyn));
    }
    /* If the spinlock is release. */
    if( OS_TASK_MASK_SPINLOCK(taskCfg) )
    {
        Os_Spinlock_ForceReleaseAll(OS_TASK_GETSPINLISTHEAD(taskCfg->taskDyn));
    }

    /* Increase activation counter. */
    taskCfg->taskDyn->activationsCnt++;
    /* Terminate a task. */
    Os_Task_TaskReset(taskCfg);

    /* Delete the task from the scheduler. */
    Os_Schedler_DeleteTask(OS_CORE_GETSCHEDULER(taskCfg->coreId), taskCfg->taskDyn);


#if( (OS_CFG_ORTI_ENABLE == STD_ON) && (OS_CFG_ORTI_HOOK_ENABLE == STD_ON) )
    /* Call orti hook. */
    Os_Orit_TaskState_Trigger(taskCfg->coreId, taskCfg->taskId, OS_ORTI_TASK_TERMINATED_TRIGGER);
#endif

#if( OS_ARCH == ARCH_CONTEXT_M )
    /* Execute a schedule. */
    (void)Os_Schedler_Schedle(OS_CORE_GETSCHEDULER(coreId));
    Os_Arch_TaskTerminate_ForCortextM();
    /* Enable interrupt. */
    Os_Arch_IntEnable(intState);
#else
    {
        Os_TaskDynType* nextDyn;
        const Os_TaskCfgType* nextTaskCfg;
        /* Execute a schedule. */
        nextDyn = Os_Schedler_Schedle(OS_CORE_GETSCHEDULER(coreId));
        nextTaskCfg = OS_TASK_GETCFG(nextDyn->taskId);
        Os_Task_SetNextTaskData(nextTaskCfg);
        Os_Arch_ResetContext_Switch(taskCfg->contextCfg, nextTaskCfg->taskDyn->context);
    }
#endif

    Os_FatalError();
}

/*
********************************************************************************
* Function Name: Os_Task_StartFirst
*
* Explanation: Uses to start first task.
*
* param: coreId: First task own core.
*
* retval: None
********************************************************************************
*/
FUNC(void, OS_CODE) Os_Task_StartFirst(CoreIdType coreId)
{
    const Os_TaskCfgType* taskCfg;
    Os_TaskDynType* taskNext;
    /* Execution schedule, get the new task. */
    taskNext = Os_Schedler_Schedle(OS_CORE_GETSCHEDULER(coreId));
    /* Set next task state to RUNNING .*/
    taskNext->state = RUNNING;
    /* Get next task data. */
    taskCfg = OS_TASK_GETCFG(taskNext->taskId);
    /*T1 task start*/
    OSTH_TASK_STARTFIRST_START(taskCfg->coreId,taskCfg->taskId);
#if( (OS_CFG_SCALABILITY_CLASS == OS_SC3) || (OS_CFG_SCALABILITY_CLASS == OS_SC4) )
    /* The app is configured with memory protection. */
    if( taskCfg->appMpCfg != NULL_PTR )
    {
        (void)Os_Mp_Switch(TRUE, taskCfg->appMpCfg);
    }
    /* The task is configured with memory protection. */
    if( taskCfg->taskMpCfg != NULL_PTR )
    {
        (void)Os_Mp_Switch(FALSE, taskCfg->taskMpCfg);
    }
    /* Switch to the next stack protection range.*/
    Os_Arch_MpStackSwitch(taskCfg->contextCfg->stackStartAddr, taskCfg->contextCfg->stackEndAddr);
#endif
    /* Set core current task dyn. */
    OS_CORE_SETCURRTASK(taskCfg->coreId,taskCfg->taskDyn);
    /* Set core current app. */
    OS_CORE_SETAPPID(taskCfg->coreId, taskCfg->taskDyn->currentAppId);
    /* Set core the next process id. */
    OS_CORE_SETPROTYPE(taskCfg->coreId, OS_PRETASKHOOK_TYPE_MASK);
    /* Pre-Task hook. */
    OS_PRETASKHOOK(taskCfg);
    /* Set core the next process id. */
    OS_CORE_SETPROTYPE(taskCfg->coreId, OS_TASK_TYPE_MASK);
#if( (OS_CFG_SCALABILITY_CLASS == OS_SC2) || (OS_CFG_SCALABILITY_CLASS == OS_SC4) )
    if( OS_CORE_CHECKTPISENABLE(taskCfg->coreId) )
    {
        Os_Tp_StartNextBudget(taskCfg->tpCfg, coreId);
    }
#endif

#if( (OS_CFG_ORTI_ENABLE == STD_ON) && (OS_CFG_ORTI_HOOK_ENABLE == STD_ON) )
    /* Call orti hook. */
    Os_Orit_TaskState_Trigger(taskCfg->coreId, taskCfg->taskId, OS_ORTI_TASK_STARTFIRST_TRIGGER);
#endif

    /* Context switch. */
    Os_Arch_Context_SwitchFirst(taskNext->context);
}

/*
********************************************************************************
* Function Name: Os_Task_ActivateTask
*
* Explanation: Uses to activate a task.
*
* param: taskId: Task reference.
*
* retval: E_OS_OK: No error.
*         E_OS_ID: Invalid taskId.
*         E_OS_CALLEVEL: Called from invalid context.
*         E_OS_DISABLEDINT: A service of the OS is called inside an interrupt
*                           disable/enable pair.
*         E_OS_ACCESS: Caller's access rights are not sufficient.
*         E_OS_STATE: Application is not accessible.
********************************************************************************
*/
FUNC(Os_StatusType, OS_CODE) Os_Task_ActivateTask(TaskType taskId)
{
    Os_StatusType ret;
    CoreIdType coreId;
    Os_TaskDynType* nextDyn;
    const Os_TaskCfgType* taskCfg;
    const Os_TaskCfgType* currentTaskCfg;
    Os_Arch_IntState intState;

    OS_ORTI_API_MONITOR_ENTRY(OSServiceId_ActivateTask);
    /* Get logic core id. */
    coreId = Os_Core_GetLogicId();

    if( taskId >= OS_TASKID_COUNT ) /* If task id in the range. */
    {
        ret = E_OS_ID;
    }
    else if( OS_CORE_MASK_INTERRUPT(coreId) ) /* If interrupts is disable. */
    {
        ret = E_OS_DISABLEDINT;
    }
    else if( OS_CORE_PROCESSTYPEMATCH(coreId, OS_ACTIVETASK_ACCESS) ) /* If the api is not accessible. */
    {
        ret = E_OS_CALLEVEL;
    }
    else
    {
        /* Get task configuration data. */
        taskCfg = OS_TASK_GETCFG(taskId);
        if( OS_APPMATCH(taskCfg->accessingApps, OS_CORE_GETAPPID(coreId)) ) /* If the application does not have permission. */
        {
             ret = E_OS_ACCESS;
        }
        else
        {
#if( OS_CFG_MULTI_CORE == STD_ON )
            /* If the activate task is the same core. */
            if( coreId == OS_TASK_GETCOREID(taskCfg) )
#endif
            {
                if( OS_APP_STATEOFF(taskCfg->ownerAppId) ) /* If the application is not accessible. */
                {
                    ret = E_OS_ACCESS;
                }
                else
                {
                    /* Disable interrupt. */
                    Os_Arch_IntDisable(&intState);
                    /* Activate a task. */
                    ret = Os_Task_ActivateTaskSimp(taskCfg);
                    /* Task switch. */
                    if( E_OS_OK == ret)
                    {
                        if( TRUE == OS_CORE_GETALLOWSCH(coreId) )
                        {
                            if( TRUE == Os_Schedler_NeedSchedle(OS_CORE_GETSCHEDULER(coreId)) )
                            {
                                /* Get current task. */
                                currentTaskCfg = OS_TASK_GETCFG(OS_CORE_GETCURRENTTASKID(coreId));
                                /* Execute a schedule. */
                                nextDyn = Os_Schedler_Schedle(OS_CORE_GETSCHEDULER(coreId));
                                ret = Os_Task_TaskSwitch(currentTaskCfg, OS_TASK_GETCFG(nextDyn->taskId));
                            }
                        }
                    }
                    /* Enable interrupt. */
                    Os_Arch_IntEnable(intState);
                }
            }

#if( OS_CFG_MULTI_CORE == STD_ON )
            else
            {
                /* Activate task of target core. */
                Os_MultiCoreServeParamType parameter;
                parameter.Os_ActivateTask.taskId = taskId;
                /* Execute multi-core calling function. */
                ret = Os_MultiCore_Trigger(TRUE, coreId, OS_TASK_GETCOREID(taskCfg),
                                           Os_MCServe_ActivateTask_ID, &parameter);
            }
#endif
        }
    }
    OS_ORTI_API_MONITOR_EXIT(OSServiceId_ActivateTask);

    return Os_Hook_CallErrorHook(OSServiceId_ActivateTask, ret);
}

/*
********************************************************************************
* Function Name: Os_Task_TerminateTask
*
* Explanation: Uses to terminate a task.
*
* param: None
*
* retval: E_OS_OK: No error.
*         E_OS_CALLEVEL: Called from invalid context.
*         E_OS_RESOURCE: Calling task occupies resources,.
*         E_OS_SPINLOCK: Spinlock is not released.
*         E_OS_DISABLEDINT: A service of the OS is called inside an interrupt
*                           disable/enable pair.
*         E_OS_ACCESS: Caller's access rights are not sufficient.
*         E_OS_STATE: Application is not accessible.
********************************************************************************
*/
FUNC(Os_StatusType, OS_CODE) Os_Task_TerminateTask(void)
{
    Os_StatusType ret;
    CoreIdType coreId;
    const Os_TaskCfgType* taskCfg;
    Os_Arch_IntState intState;

    OS_ORTI_API_MONITOR_ENTRY(OSServiceId_TerminateTask);
    /* Get the current logical core id. */
    coreId = Os_Core_GetLogicId();

    /* If current process is a task. */
    if( OS_CORE_PROCESSTYPEMATCH(coreId, OS_TERMINATETASK_ACCESS) )
    {
        ret = E_OS_CALLEVEL;
    }
    else if( OS_CORE_MASK_INTERRUPT(coreId) ) /* If interrupts is disable. */
    {
        ret = E_OS_DISABLEDINT;
    }
    else
    {
        /* Disable interrupt. */
        Os_Arch_IntDisable(&intState);
        /* Get current task. */
        taskCfg = OS_TASK_GETCFG(OS_CORE_GETCURRENTTASKID(coreId));
        if( OS_TASK_MASK_RESOURCE(taskCfg) )
        {
            Os_Resource_ForceReleaseAll(OS_TASK_GETRESLISTHEAD(taskCfg->taskDyn));
            ret = E_OS_RESOURCE;
        }
        else if( OS_TASK_MASK_SPINLOCK(taskCfg) )
        {
            Os_Spinlock_ForceReleaseAll(OS_TASK_GETSPINLISTHEAD(taskCfg->taskDyn));
            ret = E_OS_SPINLOCK;
        }
        else
        {
            /* Increase activation counter. */
            taskCfg->taskDyn->activationsCnt++;
#if( OS_MONITOR_ENABLE == STD_ON )
            Os_Monitor_TaskTerminateFlag[coreId] = TRUE;
#endif
            /* Terminate a task. */
            Os_Task_TaskReset(taskCfg);

            /* Delete the task from the scheduler. */
            ret = Os_Schedler_DeleteTask(OS_CORE_GETSCHEDULER(taskCfg->coreId), taskCfg->taskDyn);
        }
        /* Task switch. */
        if( E_OS_OK == ret )
        {

#if( (OS_CFG_ORTI_ENABLE == STD_ON) && (OS_CFG_ORTI_HOOK_ENABLE == STD_ON) )
            /* Call orti hook. */
            Os_Orit_TaskState_Trigger(taskCfg->coreId, taskCfg->taskId, OS_ORTI_TASK_TERMINATED_TRIGGER);
#endif

#if( OS_ARCH == ARCH_CONTEXT_M )
             /* Execute a schedule. */
            (void)Os_Schedler_Schedle(OS_CORE_GETSCHEDULER(coreId));
            Os_Arch_TaskTerminate_ForCortextM();
#else
            {
                Os_TaskDynType* nextDyn;
                const Os_TaskCfgType* nextTaskCfg;
                /* Execute a schedule. */
                nextDyn = Os_Schedler_Schedle(OS_CORE_GETSCHEDULER(coreId));
                nextTaskCfg = OS_TASK_GETCFG(nextDyn->taskId);
                Os_Task_SetNextTaskData(nextTaskCfg);
                Os_Arch_ResetContext_Switch(taskCfg->contextCfg, nextTaskCfg->taskDyn->context);
            }
#endif
        }
        /* Enable interrupt. */
        Os_Arch_IntEnable(intState);
    }
    OS_ORTI_API_MONITOR_EXIT(OSServiceId_TerminateTask);

    return Os_Hook_CallErrorHook(OSServiceId_TerminateTask, ret);
}

/*
********************************************************************************
* Function Name: Os_Task_ChainTask
*
* Explanation: Uses to chain task.
*
* param: TasktaskIdID: Reference to the sequential succeeding task to be activated.
*
* retval: E_OS_OK: No error.
*         E_OS_ID: Invalid taskId.
*         E_OS_CALLEVEL: Called from invalid context.
*         E_OS_RESOURCE: Calling task occupies resources,.
*         E_OS_SPINLOCK: Spinlock is not released.
*         E_OS_DISABLEDINT: A service of the OS is called inside an interrupt
*                           disable/enable pair.
*         E_OS_ACCESS: Caller's access rights are not sufficient.
*         E_OS_STATE: Application is not accessible.
********************************************************************************
*/
FUNC(Os_StatusType, OS_CODE) Os_Task_ChainTask(TaskType taskId)
{
    Os_StatusType ret = E_OS_OK;
    CoreIdType coreId;
#if( OS_ARCH != ARCH_CONTEXT_M )
    Os_TaskDynType* nextDyn;
    const Os_TaskCfgType* nextTaskCfg;
#endif
    const Os_TaskCfgType* taskCfg;
    const Os_TaskCfgType* currentTaskCfg;
    Os_Arch_IntState intState;

    OS_ORTI_API_MONITOR_ENTRY(OSServiceId_ChainTask);
    /* Get logic core id */
    coreId = Os_Core_GetLogicId();

    if( taskId >= OS_TASKID_COUNT ) /* If task id in the range. */
    {
        ret = E_OS_ID;
    }
    else if( OS_CORE_MASK_INTERRUPT(coreId) ) /* If interrupts is disable. */
    {
        ret = E_OS_DISABLEDINT;
    }
    else if( OS_CORE_PROCESSTYPEMATCH(coreId, OS_CHAINTASK_ACCESS) ) /* If the api is not accessible. */
    {
        ret = E_OS_CALLEVEL;
    }
    else
    {
        /* Get task configuration data. */
        taskCfg = OS_TASK_GETCFG(taskId);
        /* Get current task. */
        currentTaskCfg = OS_TASK_GETCFG(OS_CORE_GETCURRENTTASKID(coreId));

        if( OS_APPMATCH(taskCfg->accessingApps, OS_CORE_GETAPPID(coreId)) ) /* If the application does not have permission. */
        {
            ret = E_OS_ACCESS;
        }
        else if( OS_TASK_MASK_RESOURCE(currentTaskCfg) )
        {
            ret = E_OS_RESOURCE;
        }
        else if( OS_TASK_MASK_SPINLOCK(currentTaskCfg) )
        {
            ret = E_OS_SPINLOCK;
        }
        else
        {
#if( OS_CFG_MULTI_CORE == STD_ON )
            /* If the activate task is the same core. */
            if( coreId == OS_TASK_GETCOREID(taskCfg) )
#endif
            {
                if( OS_APP_STATEOFF(taskCfg->ownerAppId) ) /* If the application is not accessible. */
                {
                    ret = E_OS_ACCESS;
                }
                else
                {
                    /* Disable interrupt. */
                    Os_Arch_IntDisable(&intState);
                    /* If the next task is the current. */
                    if( taskId == (TaskType)OS_CORE_GETCURRENTTASKID(coreId) )
                    {
#if( (OS_CFG_SCALABILITY_CLASS == OS_SC2) || (OS_CFG_SCALABILITY_CLASS == OS_SC4) )
                        if( OS_CORE_CHECKTPISENABLE(taskCfg->coreId) )
                        {
                            /* Arrive timming protection. */
                            (void)Os_Tp_CheckFrameInterval(taskCfg->tpCfg);
                        }
#endif
                        /* Delete the task from the scheduler. */
                        (void)Os_Schedler_DeleteTask(OS_CORE_GETSCHEDULER(currentTaskCfg->coreId), currentTaskCfg->taskDyn);
                        /* Reset a task. */
                        Os_Task_TaskReset(currentTaskCfg);
                        /* Insert tasks into the scheduler. */
                        (void)Os_Schedler_InsertTask(OS_CORE_GETSCHEDULER(currentTaskCfg->coreId), currentTaskCfg->taskDyn);
                    }
                    else
                    {
                        /* Activate a task. */
                        ret = Os_Task_ActivateTaskSimp(taskCfg);
                        /* Task switch. */
                        if( E_OS_OK == ret )
                        {
                            /* Increase activation counter. */
                            currentTaskCfg->taskDyn->activationsCnt++;
                            /* Reset a task. */
                            Os_Task_TaskReset(currentTaskCfg);
                            /* Delete the task from the scheduler. */
                            (void)Os_Schedler_DeleteTask(OS_CORE_GETSCHEDULER(currentTaskCfg->coreId), currentTaskCfg->taskDyn);
                        }
                    }

                    if( E_OS_OK == ret )
                    {
#if( OS_ARCH == ARCH_CONTEXT_M )
                        /* Execute a schedule. */
                        (void)Os_Schedler_Schedle(OS_CORE_GETSCHEDULER(coreId));
                        Os_Arch_TaskTerminate_ForCortextM();
#else                        
                        /* Execute a schedule. */
                        nextDyn = Os_Schedler_Schedle(OS_CORE_GETSCHEDULER(coreId));
                        nextTaskCfg = OS_TASK_GETCFG(nextDyn->taskId);
                        Os_Task_SetNextTaskData(nextTaskCfg);
                        Os_Arch_ResetContext_Switch(currentTaskCfg->contextCfg, nextTaskCfg->taskDyn->context);
#endif
                    }
                    /* Enable interrupt. */
                    Os_Arch_IntEnable(intState);
                }
            }
#if( OS_CFG_MULTI_CORE == STD_ON )
            else
            {
                Os_MultiCoreServeParamType parameter;
                parameter.Os_ChainTask.taskId = taskId;
                /* Execute multi-core calling function. */
                ret = Os_MultiCore_Trigger(TRUE, coreId, OS_TASK_GETCOREID(taskCfg),
                                           Os_MCServe_ChainTask_ID, &parameter);
            }
#endif
        }
    }
    OS_ORTI_API_MONITOR_EXIT(OSServiceId_ChainTask);

    return Os_Hook_CallErrorHook(OSServiceId_ChainTask, ret);
}

/*
********************************************************************************
* Function Name: Os_Task_TaskSwitch_ForIsr
*
* Explanation: Uses to switch task in interrupts.
*
* param: currentCfg: Reference to current task.
*        nextCfg: Reference to next task.
*
* retval: E_OS_OK: No error.
*         E_OS_PARAM_POINTER: A null pointer was given as argument.
********************************************************************************
*/
FUNC(Os_StatusType, OS_CODE) Os_Task_TaskSwitch_ForIsr
(
    P2CONST(Os_TaskCfgType, AUTOMATIC, OS_APPL_CONST) currentCfg,
    P2CONST(Os_TaskCfgType, AUTOMATIC, OS_APPL_CONST) nextCfg
)
{
    Os_StatusType ret = E_OS_OK;

    /* If the input is not NULL. */
    if( (currentCfg != NULL_PTR) && (nextCfg != NULL_PTR) )
    {
        Os_TaskDynType* current = OS_TASK_GETDYN(currentCfg);
#if( OS_STACK_OVERFLOW_CHECK == STD_ON )
        /* Check stack overflow. */
        Os_Stack_Measure(currentCfg->contextCfg->stackEndAddr);
#endif

        /* Set core the next process id. */
        OS_CORE_SETPROTYPE(currentCfg->coreId, OS_POSTTASKHOOK_TYPE_MASK);
        /* Post-Task hook. */
        OS_POSTTASKHOOK(currentCfg);
        /* Set core the next process id. */
        OS_CORE_SETPROTYPE(currentCfg->coreId, OS_TASK_TYPE_MASK);
        /* If current task state is not WAITING. */
        if( current->state != WAITING )
        {
            /* Set current task state to READY. */
            current->state = READY;
            /*T1 task Pre-empt*/
            //OSTH_TASK_SWITCH_FORISR_PREEMPT(currentCfg->coreId, currentCfg->taskId);
        }
        /* Set next task parameter. */
        Os_Task_SetNextTaskData(nextCfg);
    }
    else
    {
        ret = E_OS_PARAM_POINTER;
    }

    return ret;
}

/*
********************************************************************************
* Function Name: Os_Task_GetTaskID
*
* Explanation: Uses to get taskId.
*
* param: taskId: Reference to the task which is currently running.
*
* retval: E_OS_OK: No error.
*         E_OS_ID: Invalid taskId.
*         E_OS_CALLEVEL: Called from invalid context.
*         E_OS_DISABLEDINT: A service of the OS is called inside an interrupt
*                           disable/enable pair.
*         E_OS_ACCESS: Caller's access rights are not sufficient.
********************************************************************************
*/
FUNC(Os_StatusType, OS_CODE) Os_Task_GetTaskID(TaskRefType taskId)
{
    Os_StatusType ret = E_OS_OK;
    CoreIdType coreId;

    OS_ORTI_API_MONITOR_ENTRY(OSServiceId_GetTaskID);
    /* Get logic core id. */
    coreId = Os_Core_GetLogicId();

    if( NULL_PTR == taskId )    /* If input is null point. */
    {
        ret = E_OS_PARAM_POINTER;
    }
    else if( OS_CORE_MASK_INTERRUPT(coreId) )   /* If interrupts is disable. */
    {
        ret = E_OS_DISABLEDINT;
    }
    else if( OS_CORE_PROCESSTYPEMATCH(coreId, OS_GETTASKID_ACCESS) ) /* If the api is not accessible. */
    {
        ret = E_OS_CALLEVEL;
    }
    else
    {
        *taskId = (TaskType)OS_CORE_GETCURRENTTASKID(coreId);
    }
    OS_ORTI_API_MONITOR_EXIT(OSServiceId_GetTaskID);

    return Os_Hook_CallErrorHook(OSServiceId_GetTaskID, ret);
}

/*
********************************************************************************
* Function Name: Os_Task_GetTaskState
*
* Explanation: Uses to get task state.
*
* param: taskId: Task reference.
*        state: Reference to the state of the task.
*
* retval: E_OS_OK: No error.
*         E_OS_ID: Invalid taskId.
*         E_OS_CALLEVEL: Called from invalid context.
*         E_OS_PARAM_POINTER: A null pointer was given as argument.
*         E_OS_DISABLEDINT: A service of the OS is called inside an interrupt
*                           disable/enable pair.
*         E_OS_ACCESS: Caller's access rights are not sufficient.
********************************************************************************
*/
FUNC(Os_StatusType, OS_CODE) Os_Task_GetTaskState(TaskType taskId, TaskStateRefType state)
{
    Os_StatusType ret = E_OS_OK;
    CoreIdType coreId;
    const Os_TaskCfgType* taskCfg;

    OS_ORTI_API_MONITOR_ENTRY(OSServiceId_GetTaskState);
    /* Get logic core id. */
    coreId = Os_Core_GetLogicId();

    if( NULL_PTR == state ) /* If input is null point. */
    {
        ret = E_OS_PARAM_POINTER;
    }
    else if( taskId >= OS_TASKID_COUNT ) /* If task id is out range. */
    {
        ret = E_OS_ID;
    }
    else if( OS_CORE_MASK_INTERRUPT(coreId) )   /* If interrupts is disable. */
    {
        ret = E_OS_DISABLEDINT;
    }
    else if( OS_CORE_PROCESSTYPEMATCH(coreId, OS_GETTASKSTATE_ACCESS) ) /* If the api is not accessible. */
    {
        ret = E_OS_CALLEVEL;
    }
    else
    {
        /* Get task configuration data. */
        taskCfg = OS_TASK_GETCFG(taskId);

#if( OS_CFG_MULTI_CORE == STD_ON )
        /* If the activate task is the same core. */
        if( coreId == taskCfg->coreId )
#endif
        {
            if( OS_APPMATCH(taskCfg->accessingApps, OS_CORE_GETAPPID(coreId)) ) /* If the application does not have permission. */
            {
                ret = E_OS_ACCESS;
            }
            else if( OS_APP_STATEOFF(taskCfg->ownerAppId) ) /* If the application is not accessible. */
            {
                ret = E_OS_ACCESS;
            }
            else
            {
                *state = (taskCfg->taskDyn->state);
            }
        }
#if( OS_CFG_MULTI_CORE == STD_ON )
        else
        {
            Os_MultiCoreServeParamType parameter;
            parameter.Os_GetTaskState.taskId = taskId;
            parameter.Os_GetTaskState.state = state;
            /* Execute multi-core calling function. */
            ret = Os_MultiCore_Trigger(TRUE, coreId, OS_TASK_GETCOREID(taskCfg),
                                       Os_MCServe_GetTaskState_ID, &parameter);
        }
#endif
    }
    OS_ORTI_API_MONITOR_EXIT(OSServiceId_GetTaskState);

    return Os_Hook_CallErrorHook(OSServiceId_GetTaskState, ret);
}

#if( OS_CFG_MULTI_CORE == STD_ON )
/*
********************************************************************************
* Function Name: Os_TargetActivateTask
*
* Explanation: Multicore function to activate task.
*
* param: taskId: Task reference.
*
* retval: E_OS_OK: No error.
*         E_OS_ID: Invalid taskId.
*         E_OS_CORE: Core is not available.
*         E_OS_STATE: Application is not accessible.
*         E_OS_PARAM_POINTER: A null pointer was given as argument.
*         E_OS_LIMIT: Maximum task activations reached.
********************************************************************************
*/
FUNC(Os_StatusType, OS_CODE) Os_TargetActivateTask(TaskType taskId)
{
    Os_StatusType ret;
    CoreIdType coreId;
    CoreIdType desCoreId;
    const Os_TaskCfgType* taskCfg;

    if( taskId >= OS_TASKID_COUNT )
    {
        ret = E_OS_ID;
    }
    else
    {
        /* Get task configuration data. */
        taskCfg = OS_TASK_GETCFG(taskId);
        if( OS_APP_STATEOFF(taskCfg->ownerAppId) ) /* If the application is not accessible. */
        {
            ret = E_OS_ACCESS;
        }
        else
        {
            /* Get the current logical core id. */
            coreId = Os_Core_GetLogicId();
            desCoreId = taskCfg->coreId;
            /* If the activate task is the same core. */
            if( coreId == desCoreId )
            {
                /* Activate a task. */
                ret = Os_Task_ActivateTaskSimp(taskCfg);
            }
            else
            {
                ret = E_OS_CORE;
            }
        }
    }

    return ret;
}

/*
********************************************************************************
* Function Name: Os_TargetGetTaskState
*
* Explanation: Multicore function to get task state.
*
* param: taskId: Task reference.
*        state: Reference to the state of the task.
*
* retval: E_OS_OK: No error.
*         E_OS_ID: Invalid taskId.
*         E_OS_CORE: Core is not available.
********************************************************************************
*/
FUNC(Os_StatusType, OS_CODE) Os_TargetGetTaskState(TaskType taskId, TaskStateRefType state)
{
    Os_StatusType ret = E_OS_OK;
    CoreIdType coreId;
    CoreIdType desCoreId;
    const Os_TaskCfgType* taskCfg;

    if( taskId >= OS_TASKID_COUNT )
    {
        ret = E_OS_ID;
    }
    else
    {
        /* Get the current logical core id. */
        coreId = Os_Core_GetLogicId();
        /* Get task configuration data. */
        taskCfg = OS_TASK_GETCFG(taskId);
        desCoreId = taskCfg->coreId;
        /* If the activate task is the same core. */
        if( coreId == desCoreId )
        {
            *state = (taskCfg->taskDyn->state);
        }
        else
        {
            ret = E_OS_CORE;
        }
    }

    return ret;
}
#endif

/*
********************************************************************************
* Function Name: Os_SysCallTaskWrongReturn
*
* Explanation: System call function, called when task wrong return.
*
* param: None
*
* retval: None
********************************************************************************
*/
FUNC(void, OS_CODE) Os_SysCallTaskWrongReturn(void)
{
#if ( OS_MEMORY_PROTECTION == STD_ON )
    Os_SysCallParamType sysCallParam;
    Os_SysCall(Os_Syscall_Task_Wrongreturn_ID, &sysCallParam);
#else
    Os_Task_WrongReturn();
#endif
}

/*
********************************************************************************
* Function Name: ActivateTask
*
* Explanation: Standard API function, uses to activate a task.
*
* param: TaskID: Task reference.
*
* retval: E_OS_OK: No error.
*         E_OS_ID: Invalid TaskID.
*         E_OS_CALLEVEL: Called from invalid context.
*         E_OS_DISABLEDINT: A service of the OS is called inside an interrupt
*                           disable/enable pair.
*         E_OS_ACCESS: Caller's access rights are not sufficient.
*         E_OS_STATE: Application is not accessible.
********************************************************************************
*/
FUNC(StatusType, OS_CODE) ActivateTask(TaskType TaskID)
{
    Os_StatusType ret;

#if( OS_MEMORY_PROTECTION == STD_ON )
    Os_SysCallParamType sysCallParam;
    sysCallParam.Os_ActivateTask.taskId = TaskID;
    Os_SysCall(Os_Syscall_ActivateTask_ID, &sysCallParam);
    ret = sysCallParam.Os_ActivateTask.retVal;
#else
    ret = Os_Task_ActivateTask(TaskID);
#endif

    return ret;
}

/*
********************************************************************************
* Function Name: TerminateTask
*
* Explanation: Standard API function, uses to terminate a task.
*
* param: None
*
* retval: E_OS_OK: No error.
*         E_OS_ID: Invalid TaskID.
*         E_OS_CALLEVEL: Called from invalid context.
*         E_OS_RESOURCE: Calling task occupies resources,.
*         E_OS_SPINLOCK: Spinlock is not released.
*         E_OS_DISABLEDINT: A service of the OS is called inside an interrupt
*                           disable/enable pair.
*         E_OS_ACCESS: Caller's access rights are not sufficient.
*         E_OS_STATE: Application is not accessible.
********************************************************************************
*/
FUNC(StatusType, OS_CODE) TerminateTask(void)
{
    StatusType ret;

#if( OS_MEMORY_PROTECTION == STD_ON )
    Os_SysCallParamType sysCallParam;
    Os_SysCall(Os_Syscall_TerminateTask_ID, &sysCallParam);
    ret = sysCallParam.Os_TerminateTask.retVal;
#else
    ret = Os_Task_TerminateTask();
#endif

    return ret;
}

/*
********************************************************************************
* Function Name: ChainTask
*
* Explanation: Standard API function, uses to chain task.
*
* param: TaskID: Reference to the sequential succeeding task to be activated.
*
* retval: E_OS_OK: No error.
*         E_OS_ID: Invalid TaskID.
*         E_OS_CALLEVEL: Called from invalid context.
*         E_OS_RESOURCE: Calling task occupies resources,.
*         E_OS_SPINLOCK: Spinlock is not released.
*         E_OS_DISABLEDINT: A service of the OS is called inside an interrupt
*                           disable/enable pair.
*         E_OS_ACCESS: Caller's access rights are not sufficient.
*         E_OS_STATE: Application is not accessible.
********************************************************************************
*/
FUNC(StatusType, OS_CODE) ChainTask(TaskType TaskID)
{
    StatusType ret;

#if( OS_MEMORY_PROTECTION == STD_ON )
    Os_SysCallParamType sysCallParam;
    sysCallParam.Os_ChainTask.taskId = TaskID;
    Os_SysCall(Os_Syscall_ChainTask_ID, &sysCallParam);
    ret = sysCallParam.Os_ChainTask.retVal;
#else
    ret = Os_Task_ChainTask(TaskID);
#endif

    return ret;
}

/*
********************************************************************************
* Function Name: Schedule
*
* Explanation: If a higher-priority task is ready, the internal resource of the
*              task is released, the current task is put intothe ready state, its
*              context is saved and the higher-priority task is executed.Otherwise
*              the calling task is continued.
*
* param: None
*
* retval: E_OK              No Error.
*         E_OS_CALLEVEL     (EXTENDED status:) The service was called from any
*                                             context which is not allowed.
*         E_OS_RESOURCE     (EXTENDED status:) The service was called from a task
*                                             which holds an OS resource.
*         E_OS_SPINLOCK     (EXTENDED status:) The service was called from a task
*                                             which holds a spinlock.
*         E_OS_DISABLEDINT  (Service Protection:) The service was called with
*                                                disabled interrupts.
********************************************************************************
*/
FUNC(StatusType, OS_CODE) Schedule(void)
{
    StatusType ret;

    ret = Os_Schedler_Schedule();

    return ret;
}

/*
********************************************************************************
* Function Name: GetTaskID
*
* Explanation: Standard API function, uses to get taskId.
*
* param: TaskID: Reference to the task which is currently running.
*
* retval: E_OS_OK: No error.
*         E_OS_ID: Invalid TaskID.
*         E_OS_CALLEVEL: Called from invalid context.
*         E_OS_DISABLEDINT: A service of the OS is called inside an interrupt
*                           disable/enable pair.
*         E_OS_ACCESS: Caller's access rights are not sufficient.
********************************************************************************
*/
FUNC(StatusType, OS_CODE) GetTaskID(TaskRefType TaskID)
{
    StatusType ret;

#if( OS_MEMORY_PROTECTION == STD_ON )
    Os_SysCallParamType sysCallParam;
    sysCallParam.Os_GetTaskID.taskId = TaskID;
    Os_SysCall(Os_Syscall_GetTaskId_ID, &sysCallParam);
    ret = sysCallParam.Os_GetTaskID.retVal;
#else
    ret = Os_Task_GetTaskID(TaskID);
#endif

    return ret;
}

/*
********************************************************************************
* Function Name: GetTaskState
*
* Explanation: Standard API function, uses to get task state.
*
* param: TaskID: Task reference.
*        State: Reference to the state of the task.
*
* retval: E_OS_OK: No error.
*         E_OS_ID: Invalid taskId.
*         E_OS_CALLEVEL: Called from invalid context.
*         E_OS_PARAM_POINTER: A null pointer was given as argument.
*         E_OS_DISABLEDINT: A service of the OS is called inside an interrupt
*                           disable/enable pair.
*         E_OS_ACCESS: Caller's access rights are not sufficient.
********************************************************************************
*/
FUNC(StatusType, OS_CODE) GetTaskState(TaskType TaskID, TaskStateRefType State)
{
    StatusType ret;

#if( OS_MEMORY_PROTECTION == STD_ON )
    Os_SysCallParamType sysCallParam;
    sysCallParam.Os_GetTaskState.taskId = TaskID;
    sysCallParam.Os_GetTaskState.state = State;
    Os_SysCall(Os_Syscall_GetTaskState_ID, &sysCallParam);
    ret = sysCallParam.Os_GetTaskState.retVal;
#else
    ret = Os_Task_GetTaskState(TaskID, State);
#endif

    return ret;
}

#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"

