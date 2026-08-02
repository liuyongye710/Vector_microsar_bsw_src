/*
********************************************************************************
*
*  File name: Os_Isr.c
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
* Author/Date: LiG/2022.11.21
* Change: Change OS_VAR_NOINIT to OS_VAR_NO_INIT.
* Cause: Bugfix
********************************************************************************
* Version: 3.2
* Author/Date: LiG/2022.11.25
* Change: Change Os_Arch_Context_Switch to Os_Arch_Context_Switch_ISR.
* Cause: Optimizate
********************************************************************************
* Version: 3.3
* Author/Date: JiangGL/2022.12.25
* Change: 1.Fix the problem that the IsrID cannot be obtained in errorHook after 
          the interrupt stack overflow is detected.
          2.Fix memory protection exceptions.
* Cause: Bugfix
********************************************************************************
* Version: 3.4
* Author/Date: ZhangY/2023.01.09
* Change: Add macro definitions for variables to resolve compiler warnings.
* Cause: Optimizate
********************************************************************************
* Version: 3.5
* Author/Date: LiG/2023.1.29
* Change: Resolve the CallErrorHook privilege level problem.
* Cause: Optimization
********************************************************************************
* Version: 3.6
* Author/Date: LiG/2023.2.14
* Change: Memory protection code optimization and annotation optimization.
* Cause: Optimization
********************************************************************************
* Version: 3.7
* Author/Date: LiG/2023.2.15
* Change: Modified for QAC.
* Cause: Optimization
********************************************************************************
* Version: 3.8
* Author/Date: LiG/2023.4.4
* Change: Adapt to ORTI.
* Cause: Update
********************************************************************************
* Version: 3.9
* Author/Date: LiuJJ/2023.05.05
* Change: Solve ISR interrupted RunTime calculate error.
* Cause: Bugfix
********************************************************************************
* Version: 3.10
* Author/Date: LiG/2023.05.19
* Change: Solving the problem of array bounds crossing.
* Cause: Bugfix
********************************************************************************
* Version: 3.11
* Author/Date: LiG/2023.05.26
* Change: Optimize variable names.
* Cause: Optimize
********************************************************************************
* Version: 3.12
* Author/Date: LiG/2023.5.27
* Change: Modified for QAC.
* Cause: Optimization
********************************************************************************
* Version: 3.13
* Author/Date: LiG/2023.5.27
* Change: Modify the reviewed useless variables.
* Cause: Optimization
********************************************************************************
*/
/*
********************************************************************************
*    Includes
********************************************************************************
*/
#include "T1_AppInterface.h"/* for T1 */
#include "T1_Neusar.h"/* for T1 */
#include "Os_Cfg.h"
#include "Os_Isr.h"
#include "Os_Task.h"
#include "Os_Core.h"
#include "Os_Resource.h"
#include "Os_Spinlock.h"
#include "Os_App.h"
#include "Os_Stack.h"
#include "Os_Arch_Context.h"
#include "Os_SysCall.h"
#include "Os_MemProtection.h"
#include "Os_Orti.h"
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
/* Get the isr processing entry function of the isr configuration. */
#define OS_ISR_GETPROFUNC(isrCfg)    ((isrCfg)->contextCfg->entryAddr)
/* Determine the resource is release. */
#define OS_ISR_MASK_RESOURCE(isrCfg) ((isrCfg)->isrDyn->resListHead.nextNode != NULL_PTR)
/* Determine the spinlock is release. */
#define OS_ISR_MASK_SPINLOCK(isrCfg) ((isrCfg)->isrDyn->spinListHead.nextNode != NULL_PTR)

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
LOCAL_INLINE FUNC(void, OS_CODE) Os_Isr_CallCallbackDirect
(
    P2CONST(Os_IsrCfgType, AUTOMATIC, OS_APPL_CONST) isrCfg,
    CoreIdType coreId
);
#if( (OS_CFG_SCALABILITY_CLASS == OS_SC2) || (OS_CFG_SCALABILITY_CLASS == OS_SC3) || (OS_CFG_SCALABILITY_CLASS == OS_SC4) )
LOCAL_INLINE FUNC(void, OS_CODE) Os_Isr_RestoreNextIsrProtection
(
    P2CONST(Os_IsrCfgType, AUTOMATIC, OS_APPL_CONST) isrCfg,
    CoreIdType coreId
);
LOCAL_INLINE FUNC(void, OS_CODE) Os_Isr_RestoreNextTaskProtection
(
    P2CONST(Os_TaskCfgType, AUTOMATIC, OS_APPL_CONST) taskCfg,
    CoreIdType coreId
);
#endif
LOCAL_INLINE FUNC(void, OS_CODE) Os_Isr_RestoreInterruptedTask
(
    P2CONST(Os_TaskCfgType, AUTOMATIC, OS_APPL_CONST) intedTaskCfg,
    CoreIdType coreId
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
* Function Name: Os_Isr_CallCallbackDirect
*
* Explanation: Internal function to call callback directly in isr entry.
*
* param: isrCfg: Reference to an isr.
*
* retval: None
********************************************************************************
*/
LOCAL_INLINE FUNC(void, OS_CODE) Os_Isr_CallCallbackDirect
(
    P2CONST(Os_IsrCfgType, AUTOMATIC, OS_APPL_CONST) isrCfg,
    CoreIdType coreId
)
{
    ISRType isrId;

    Os_IsrCbkType isrcallback = (Os_IsrCbkType)OS_ISR_GETPROFUNC(isrCfg);
    OSTH_ISR_CALLCBDRT_STOP(coreId, isrCfg->isrId);
    /* Enable interrupt. */
    Os_Arch_IntEnableAll();
    isrcallback();
    isrId = OS_CORE_GETCURRENTISRID(coreId);

    if( OS_ISR_MASK_RESOURCE(isrCfg) ) /* If the resource is release. */
    {
        Os_Resource_ForceReleaseAll(OS_ISR_GETRESLISTHEAD(isrCfg->isrDyn));
        (void)Os_Hook_CallErrorHook(OSServiceId_Os_Isr_Exit, E_OS_RESOURCE);
    }
    if( OS_ISR_MASK_SPINLOCK(isrCfg) ) /* If the spinlock is release. */
    {
        Os_Spinlock_ForceReleaseAll(OS_ISR_GETSPINLISTHEAD(isrCfg->isrDyn));
        (void)Os_Hook_CallErrorHook(OSServiceId_Os_Isr_Exit, E_OS_SPINLOCK);
    }
    if( OS_CORE_MASK_INTERRUPT(coreId) && OS_ISR_ISTPISR(isrId) ) /* If interrupts is disable. */
    {
        Os_Core_CleanInterrupts(coreId);
        (void)Os_Hook_CallErrorHook(OSServiceId_Os_Isr_Exit, E_OS_DISABLEDINT);
    }

    /* Disable interrupt. */
    Os_Arch_IntDisableAll();
}

#if( (OS_CFG_SCALABILITY_CLASS == OS_SC2) || (OS_CFG_SCALABILITY_CLASS == OS_SC3) || (OS_CFG_SCALABILITY_CLASS == OS_SC4) )
/*
********************************************************************************
* Function Name: Os_Isr_RestoreNextIsrProtection
*
* Explanation: Restore next isr protection data.
*
* param: isrCfg: Reference to an isr.
*        coreId: Core logic index.
*
* retval: None
********************************************************************************
*/
LOCAL_INLINE FUNC(void, OS_CODE) Os_Isr_RestoreNextIsrProtection
(
    P2CONST(Os_IsrCfgType, AUTOMATIC, OS_APPL_CONST) isrCfg,
    CoreIdType coreId
)
{
#if( (OS_CFG_SCALABILITY_CLASS == OS_SC3) || (OS_CFG_SCALABILITY_CLASS == OS_SC4) )

    /* Switch to the next application protection range.*/
    (void)Os_Mp_Switch(TRUE, isrCfg->appMpCfg);
    /* Switch to the next protection range.*/
    (void)Os_Mp_Switch(FALSE, isrCfg->isrMpCfg);
    /* Switch to the next stack protection range.*/
    Os_Arch_MpStackSwitch(isrCfg->contextCfg->stackStartAddr, isrCfg->contextCfg->stackEndAddr);
#endif

#if( (OS_CFG_SCALABILITY_CLASS == OS_SC2) || (OS_CFG_SCALABILITY_CLASS == OS_SC4) )
    if( OS_CORE_CHECKTPISENABLE(isrCfg->coreId) )
    {
        Os_Tp_StartNextBudget(isrCfg->tpCfg, coreId);
    }
#endif
}

/*
********************************************************************************
* Function Name: Os_Isr_RestoreNextTaskProtection
*
* Explanation: Restore next task protection data.
*
* param: isrCfg: Reference to an task.
*        coreId: Core logic index.
*
* retval: None
********************************************************************************
*/
LOCAL_INLINE FUNC(void, OS_CODE) Os_Isr_RestoreNextTaskProtection
(
    P2CONST(Os_TaskCfgType, AUTOMATIC, OS_APPL_CONST) taskCfg,
    CoreIdType coreId
)
{
#if( (OS_CFG_SCALABILITY_CLASS == OS_SC3) || (OS_CFG_SCALABILITY_CLASS == OS_SC4) )
    /* Switch to the next application protection range.*/
    (void)Os_Mp_Switch(TRUE, taskCfg->appMpCfg);
    /* Switch to the next protection range.*/
    (void)Os_Mp_Switch(FALSE, taskCfg->taskMpCfg);
    /* Switch to the next stack protection range.*/
    Os_Arch_MpStackSwitch(taskCfg->contextCfg->stackStartAddr, taskCfg->contextCfg->stackEndAddr);
#endif

#if( (OS_CFG_SCALABILITY_CLASS == OS_SC2) || (OS_CFG_SCALABILITY_CLASS == OS_SC4) )
    if( OS_CORE_CHECKTPISENABLE(taskCfg->coreId) )
    {
        Os_Tp_StartNextBudget(taskCfg->tpCfg, coreId);
    }
#endif
}
#endif

/*
********************************************************************************
* Function Name: Os_Isr_RestoreInterruptedTask
*
* Explanation:  To restore interrupted task.
*
* param: intedTaskCfg: Interrupted task.
*        coreId: Core logic index.
*
* retval: None
********************************************************************************
*/
LOCAL_INLINE FUNC(void, OS_CODE) Os_Isr_RestoreInterruptedTask
(
    P2CONST(Os_TaskCfgType, AUTOMATIC, OS_APPL_CONST) intedTaskCfg,
    CoreIdType coreId
)
{
 #if (OS_MONITOR_ENABLE == STD_ON)
     Os_Monitor_StartTimeDeal();
 #endif
    /* Set core task dyn. */
    OS_CORE_SETCURRTASK(coreId, intedTaskCfg->taskDyn);

#if( (OS_CFG_SCALABILITY_CLASS == OS_SC2) || (OS_CFG_SCALABILITY_CLASS == OS_SC3) || (OS_CFG_SCALABILITY_CLASS == OS_SC4) )
    Os_Isr_RestoreNextTaskProtection(intedTaskCfg, coreId);
#endif
    /* Set core current app. */
    OS_CORE_SETAPPID(coreId, intedTaskCfg->taskDyn->currentAppId);
    /* Set core process type. */
    OS_CORE_SETPROTYPE(coreId, OS_TASK_TYPE_MASK);
}

/*
********************************************************************************
* Function Name: Os_Isr_DisableAllInterrupts
*
* Explanation: Uses to disable all interrupts for which the hardware supports
*              disabling.
*
* param: None
*
* retval: None
********************************************************************************
*/
FUNC(void, OS_CODE) Os_Isr_DisableAllInterrupts(void)
{
#if( OS_ARCH_INTMASKLEVE_SUPPORT == STD_ON )
    Os_Arch_SetIntMaskLevel(OS_CAT1_MASKLEVE);
#else
    Os_Arch_IntDisableAll();
#endif
}

/*
********************************************************************************
* Function Name: Os_Isr_EnableAllInterrupts
*
* Explanation: Uses to restore the state saved by DisableAllInterrupts.
*
* param: level: the interrupt mask level that was interrupted if support interrupt
*               mask level.
*
* retval: None
********************************************************************************
*/
FUNC(void, OS_CODE) Os_Isr_EnableAllInterrupts
(
#if( OS_ARCH_INTMASKLEVE_SUPPORT == STD_ON )
Os_IntLevelType level
#else
void
#endif
)
{

#if( OS_ARCH_INTMASKLEVE_SUPPORT == STD_ON )
    Os_Arch_SetIntMaskLevel(level);
#else
    Os_Arch_IntEnableAll();
#endif
}

/*
********************************************************************************
* Function Name: Os_Isr_SuspendOSInterrupts
*
* Explanation: Uses to save the recognition status of interrupts of category 2
*              and disables the recognition of these interrupts.
*
* param: None
*
* retval: None
********************************************************************************
*/
FUNC(void, OS_CODE) Os_Isr_SuspendOSInterrupts(void)
{
#if( OS_ARCH_INTMASKLEVE_SUPPORT == STD_ON )
    Os_Arch_SetIntMaskLevel(OS_CAT2_MASKLEVE);
#else
    Os_Arch_IntDisableAll();
#endif
}

/*
********************************************************************************
* Function Name: Os_Isr_ResumeOSInterrupts
*
* Explanation: Uses to restore the recognition status of interrupts saved by the
*              SuspendOSInterrupts service.
*
* param: level: the interrupt mask level that was interrupted if support interrupt
*               mask level.
*
* retval: None
********************************************************************************
*/
FUNC(void, OS_CODE) Os_Isr_ResumeOSInterrupts
(
#if( OS_ARCH_INTMASKLEVE_SUPPORT == STD_ON )
Os_IntLevelType level
#else
void
#endif
)
{
#if( OS_ARCH_INTMASKLEVE_SUPPORT == STD_ON )
    Os_Arch_SetIntMaskLevel(level);
#else
    Os_Arch_IntEnableAll();
#endif
}

/*
********************************************************************************
* Function Name: Os_Isr_GetISRID
*
* Explanation: Uses to get the information about the ISRID.
*
* param: None
*
* retval: Reference to the isr which is currently running.
********************************************************************************
*/
FUNC(ISRType, OS_CODE) Os_Isr_GetISRID(void)
{
    CoreIdType coreId;
    ISRType isrId = INVALID_ISR;
    Os_ProcType currentProcType;

    OS_ORTI_API_MONITOR_ENTRY(OSServiceId_GetISRID);
    /* Get the current logical core id. */
    coreId = Os_Core_GetLogicId();
    currentProcType = OS_CORE_GETPROTYPE(coreId);

    if( OS_ISR_CAT2_TYPE_MASK == currentProcType )
    {
        isrId = OS_CORE_GETCURRENTISRID(coreId);
    }
    else if( (OS_ERRHOOK_TYPE_MASK == currentProcType) || (OS_PROTECTHOOK_TYPE_MASK == currentProcType) )
    {
        /* Determine whether it is not the last interrupt. */
        if( OS_ZERO_VALUE != OS_CORE_GETINTCNTS(coreId) )
        {
            isrId = OS_CORE_GETCURRENTISRID(coreId);
        }
    }
    else
    {
        /* Do nothing. */
    }
    OS_ORTI_API_MONITOR_EXIT(OSServiceId_GetISRID);

    return isrId;
}

/*
********************************************************************************
* Function Name: Os_Isr_Init
*
* Explanation: Uses to init isr information.
*
* param: isrCfg: Reference to an isr.
*
* retval: None
********************************************************************************
*/
FUNC(void, OS_CODE) Os_Isr_Init
(
    P2CONST(Os_IsrCfgType, AUTOMATIC, OS_APPL_CONST) isrCfg
)
{
    /* Check the isrCfg is not NULL_PTR. */
    Os_ParamCheck(NULL_PTR != isrCfg);

    /* Initialize the stack. */
    Os_Arch_Context_Stack_Init(isrCfg->contextCfg);
    /* Set context pointer address. */
    isrCfg->isrDyn->context = isrCfg->contextCfg->contextDyn;
    /* Initialize the context. */
    Os_Arch_Context_Init(isrCfg->isrDyn->context, isrCfg->contextCfg);

#if( OS_CFG_RESOURCE_ENABLE == STD_ON )
    Os_List_Init(&isrCfg->isrDyn->resListHead);
#endif

#if( OS_CFG_SPINLOCK_ENABLE == STD_ON )
    Os_List_Init(&isrCfg->isrDyn->resListHead);
#endif

    /* Set isr id. */
    isrCfg->isrDyn->isrId = isrCfg->isrId;
    /* Set dynamic appId. */
    isrCfg->isrDyn->currentAppId = isrCfg->ownerAppId;
#if( OS_MONITOR_ENABLE == STD_ON )
    uint8 monitorCore = OS_ZERO_VALUE;
    for(monitorCore = OS_ZERO_VALUE; monitorCore < (uint8)OS_COREID_COUNT; monitorCore++)
    {
        Os_Monitor_CoreRunIsr[monitorCore] = INVALID_ISR;
    }
#endif
#if( (OS_CFG_SCALABILITY_CLASS == OS_SC2) || (OS_CFG_SCALABILITY_CLASS == OS_SC4) )
    if( OS_CORE_CHECKTPISENABLE(isrCfg->coreId) )
    {
        Os_Tp_Init(isrCfg->tpCfg);
    }
#endif

#if( (OS_CFG_ORTI_ENABLE == STD_ON) && (OS_CFG_ORTI_HOOK_ENABLE == STD_ON) )
    /* Call orti hook. */
    Os_Orit_IsrState_Trigger(isrCfg->coreId, isrCfg->isrId, OS_ORTI_ISR_INIT, OS_ORTI_ISR_INIT_TRIGGER);
#endif
}

/*
********************************************************************************
* Function Name: Os_Isr_EnableSource
*
* Explanation: Uses to enable isr source.
*
* param: isrSource: Hardware interrupt information.
*
* retval: None
********************************************************************************
*/
FUNC(void, OS_CODE) Os_Isr_EnableSource
(
    P2CONST(Os_Arch_IsrSourceType, AUTOMATIC, OS_APPL_CONST) isrSource
)
{
    Os_Arch_IntEnableSource(isrSource);
}

/*
********************************************************************************
* Function Name: Os_Isr_DisableSource
*
* Explanation: Uses to disable isr source.
*
* param: isrSource: Hardware interrupt information.
*
* retval: None
********************************************************************************
*/
FUNC(void, OS_CODE) Os_Isr_DisableSource
(
        P2CONST(Os_Arch_IsrSourceType, AUTOMATIC, OS_APPL_CONST) isrSource
)
{
    Os_Arch_IntDisableSource(isrSource);
}

/*
********************************************************************************
* Function Name: Os_Isr_AppTerminateIsr
*
* Explanation: Uses to terminate isr.
*
* param: isrCfg: Reference to an isr.
*
* retval: None
********************************************************************************
*/
FUNC(void, OS_CODE) Os_Isr_AppTerminateIsr
(
    P2CONST(Os_IsrCfgType, AUTOMATIC, OS_APPL_CONST) isrCfg
)
{
    /* Disable interrupt source. */
    Os_Isr_DisableSource(OS_ISR_GETISRSOURCE(isrCfg));

    if( OS_ISR_MASK_RESOURCE(isrCfg) ) /* If the resource is release. */
    {
        Os_Resource_ForceReleaseAll(OS_ISR_GETRESLISTHEAD(isrCfg->isrDyn));
    }
    if( OS_ISR_MASK_SPINLOCK(isrCfg) ) /* If the spinlock is release. */
    {
        Os_Spinlock_ForceReleaseAll(OS_ISR_GETSPINLISTHEAD(isrCfg->isrDyn));
    }
}

/*
********************************************************************************
* Function Name: Os_Isr_Entry
*
* Explanation: Category 2 isr entry.
*
* param: isrCfg: Reference to an isr.
*        currentContext: interrupted context.
*
* retval: The next context that needs to run.
********************************************************************************
*/
FUNC(void, OS_CODE) Os_Isr_Entry
(
    P2CONST(Os_IsrCfgType, AUTOMATIC, OS_APPL_CONST) isrCfg,
    P2VAR(Os_Arch_ContextDynType*, AUTOMATIC, OS_APPL_DATA) currentContext
)
{
    CoreIdType coreId;
    Os_Arch_ContextDynType* tmpContext;
    Os_Arch_ContextDynType** nextContext;
#if( OS_STACK_OVERFLOW_CHECK == STD_ON )
    const Os_TaskCfgType* taskCfg;
#endif
    Os_ParamCheck(NULL_PTR != isrCfg);

    /* Get the current logical core id. */
    coreId = Os_Core_GetLogicId();
    /* Disable interrupt. */
    Os_Arch_IntDisableAll();
    /* Disable scheduler. */
    OS_CORE_DISABLESCH(coreId);

#if( OS_STACK_OVERFLOW_CHECK == STD_ON )
    /* Check stack overflow. */
    taskCfg = OS_TASK_GETCFG(OS_CORE_GETCURRENTTASKID(coreId));
    Os_Stack_Measure(taskCfg->contextCfg->stackEndAddr);
#endif
#if( OS_MONITOR_ENABLE == STD_ON )
    Os_Monitor_IsrEntry(coreId, isrCfg);
    Os_Monitor_StartTimeDeal();
#endif
#if( (OS_CFG_SCALABILITY_CLASS == OS_SC2) || (OS_CFG_SCALABILITY_CLASS == OS_SC4) )
    if( OS_CORE_CHECKTPISENABLE(coreId) )
    {
        const Os_TpCfgType* currentTpCfg;
        if( FALSE == (isrCfg->ifTpIsr) )
        {
            (void)Os_Tp_CheckFrameInterval(isrCfg->tpCfg);
            if( OS_TASK_TYPE_MASK == OS_CORE_GETPROTYPE(coreId) )
            {
                currentTpCfg = OS_TASK_GETCFG(OS_CORE_GETCURRENTTASKID(coreId))->tpCfg;
                Os_Tp_SaveCurrenBudget(currentTpCfg, coreId);
            }
            else if( OS_ISR_CAT2_TYPE_MASK == OS_CORE_GETPROTYPE(coreId) )
            {
                currentTpCfg = OS_ISR_GETCFG(OS_CORE_GETCURRENTISRID(coreId))->tpCfg;
                Os_Tp_SaveCurrenBudget(currentTpCfg, coreId);
            }
            else
            {
                /* Do nothing. */
            }
            Os_Tp_StartNextBudget(isrCfg->tpCfg, coreId);
        }
    }
#endif
    /* Set core process type. */
    OS_CORE_SETPROTYPE(coreId, OS_ISR_CAT2_TYPE_MASK);
    /* Set core isr dyn. */
    OS_CORE_SETCURRISR(coreId, isrCfg->isrDyn);
    /* Push current context to the core context buffer. */
    Os_Core_IsrBuffPush(coreId, currentContext);
    /*T1 isr start*/
    OSTH_ISR_ENTRY_START(coreId, isrCfg->isrId);
#if( (OS_CFG_ORTI_ENABLE == STD_ON) && (OS_CFG_ORTI_HOOK_ENABLE == STD_ON) )
    /* Call orti hook. */
    Os_Orit_IsrState_Trigger(isrCfg->coreId, isrCfg->isrId, OS_ORTI_ISR_START, OS_ORTI_ISR_ENTRY_TRIGGER);
#endif
    /* If the isr is belongs to system app. */
    if( OS_IFSYSAPP(coreId, isrCfg->ownerAppId) )
    {
        /* Set core current app. */
        OS_CORE_SETAPPID(coreId, isrCfg->isrDyn->currentAppId);
        tmpContext = Os_Core_IsrGetIsrBuff(coreId);
        Os_Arch_Stack_Switch(tmpContext, isrCfg->isrDyn->context);
        Os_Isr_CallCallbackDirect(isrCfg, coreId);
        Os_Arch_Stack_Restore(tmpContext);
        /* Init current isr Sp. */
        Os_Arch_ContextSp_Init(isrCfg->isrDyn->context,isrCfg->contextCfg);
    }
    else
    {
#if( (OS_CFG_SCALABILITY_CLASS == OS_SC3) || (OS_CFG_SCALABILITY_CLASS == OS_SC4) )

        /* Switch to the next application protection range.*/
        (void)Os_Mp_Switch(TRUE, isrCfg->appMpCfg);
        /* Switch to the next protection range.*/
        (void)Os_Mp_Switch(FALSE, isrCfg->isrMpCfg);
        /* Switch to the next stack protection range.*/
        Os_Arch_MpStackSwitch(isrCfg->contextCfg->stackStartAddr, isrCfg->contextCfg->stackEndAddr);
#endif
        /* Set core current app. */
        OS_CORE_SETAPPID(coreId, isrCfg->isrDyn->currentAppId);
        tmpContext = Os_Core_IsrGetIsrBuff(coreId);
        Os_Arch_Context_Switch_ISR(tmpContext, isrCfg->isrDyn->context);
    }

    /* Acknowledge that interrupt handling. */
    Os_Arch_ClearPendingIRQ(isrCfg->source);

#if( OS_STACK_OVERFLOW_CHECK == STD_ON )
    /* Check stack overflow. */
    Os_Stack_Measure(isrCfg->contextCfg->stackEndAddr);
#endif

    /* Pop the current context. */
    nextContext = Os_Core_IsrBuffPop(coreId);
#if( (OS_CFG_ORTI_ENABLE == STD_ON) && (OS_CFG_ORTI_HOOK_ENABLE == STD_ON) )
    /* Call orti hook. */
    Os_Orit_IsrState_Trigger(isrCfg->coreId, isrCfg->isrId, OS_ORTI_ISR_END, OS_ORTI_ISR_ENTRY_TRIGGER);
#endif

#if( (OS_CFG_SCALABILITY_CLASS == OS_SC2) || (OS_CFG_SCALABILITY_CLASS == OS_SC4) )
    if( OS_CORE_CHECKTPISENABLE(isrCfg->coreId) )
    {
        if( FALSE == (isrCfg->ifTpIsr) )
        {
            /* Reset current budget. */
            Os_Tp_ResetCurrentBudget(isrCfg->tpCfg, isrCfg->coreId);
        }
     }
#endif
     /* Enable scheduler. */
     OS_CORE_ALLOWSCH(coreId);

    /* Determine whether it is not the last interrupt. */
    if( OS_ZERO_VALUE != OS_CORE_GETINTCNTS(coreId) )
    {
        ISRType isrId;
        const Os_IsrCfgType* intedIsrCfg;
        isrId = ((Os_IsrDynType*)nextContext)->isrId;
        intedIsrCfg = OS_ISR_GETCFG(isrId);
#if (OS_MONITOR_ENABLE == STD_ON)
        Os_Monitor_IsrExit(coreId, isrCfg); 
#endif

#if( (OS_CFG_SCALABILITY_CLASS == OS_SC2) || (OS_CFG_SCALABILITY_CLASS == OS_SC3) || (OS_CFG_SCALABILITY_CLASS == OS_SC4) )
        Os_Isr_RestoreNextIsrProtection(intedIsrCfg, coreId);
#endif
        /* Set core isr dyn. */
        OS_CORE_SETCURRISR(coreId, intedIsrCfg->isrDyn);
        /* Set core current app. */
        OS_CORE_SETAPPID(coreId, intedIsrCfg->ownerAppId);
    }
    else
    {
        TaskType taskId;
        const Os_TaskCfgType* intedTaskCfg;
#if( OS_ARCH != ARCH_CONTEXT_M )
        const Os_TaskCfgType* nextTaskCfg;
#endif
#if (OS_MONITOR_ENABLE == STD_ON)
        Os_Monitor_IsrExit(coreId, isrCfg);
#endif
        /* Get current task configure data. */
        taskId = ((Os_TaskDynType*)nextContext)->taskId;
        intedTaskCfg = OS_TASK_GETCFG(taskId);
        if( TRUE == Os_Schedler_NeedSchedle(OS_CORE_GETSCHEDULER(coreId)) )
        {
            Os_TaskDynType* nextTask;

            /* Execution schedule. */
            nextTask = Os_Schedler_Schedle(OS_CORE_GETSCHEDULER(coreId));
#if( OS_ARCH == ARCH_CONTEXT_M )
            Os_Arch_IfGetTaskContext_ForCortextM(nextTask->context, *nextContext);
            Os_Isr_RestoreInterruptedTask(intedTaskCfg, coreId);
#else
            /* Get next task configure data. */
            nextTaskCfg = OS_TASK_GETCFG(nextTask->taskId);
            /* Switch to the next task. */
            (void)Os_Task_TaskSwitch_ForIsr(intedTaskCfg, nextTaskCfg);
            /* Set next context. */
            Os_Arch_SetNextContext(nextTask->context);
#endif
        }
        else
        {
            /* To restore interrupted task. */
            Os_Isr_RestoreInterruptedTask(intedTaskCfg, coreId);
        }
    }
}

/*
********************************************************************************
* Function Name: Os_Isr_Exit
*
* Explanation: Category 2 isr exit.
*
* param: None
*
* retval: None
********************************************************************************
*/
FUNC(void, OS_CODE) Os_Isr_Exit(void)
{
    ISRType isrId;
    const Os_IsrCfgType* isrCfg;

    CoreIdType coreId = Os_Core_GetLogicId();
    Os_Arch_ContextDynType* nextContext = Os_Core_IsrGetIsrBuff(coreId);
    /* Get current isr configuration data. */
    isrId = OS_CORE_GETCURRENTISRID(coreId);
    isrCfg = OS_ISR_GETCFG(isrId);
    /*T1 isr stop*/
    OSTH_ISR_EXIT_STOP(coreId,isrId);

    if( OS_ISR_MASK_RESOURCE(isrCfg) ) /* If the resource is release. */
    {
        Os_Resource_ForceReleaseAll(OS_ISR_GETRESLISTHEAD(isrCfg->isrDyn));
        (void)Os_Hook_CallErrorHook(OSServiceId_Os_Isr_Exit, E_OS_RESOURCE);
    }
    if( OS_ISR_MASK_SPINLOCK(isrCfg) ) /* If the spinlock is release. */
    {
        Os_Spinlock_ForceReleaseAll(OS_ISR_GETSPINLISTHEAD(isrCfg->isrDyn));
        (void)Os_Hook_CallErrorHook(OSServiceId_Os_Isr_Exit, E_OS_SPINLOCK);
    }
    if( OS_CORE_MASK_INTERRUPT(coreId) ) /* If interrupts is disable. */
    {
        Os_Core_CleanInterrupts(coreId);
        (void)Os_Hook_CallErrorHook(OSServiceId_Os_Isr_Exit, E_OS_DISABLEDINT);
    }

    /* Disable interrupt. */
    Os_Arch_IntDisableAll();
    Os_Arch_ResetContext_Switch(isrCfg->contextCfg, nextContext);
}

/*
********************************************************************************
* Function Name: Os_SysCallIsrExit
*
* Explanation: System call function, category 2 isr exit.
*
* param: None
*
* retval: None
********************************************************************************
*/
FUNC(void, OS_CODE) Os_SysCallIsrExit(void)
{

#if( OS_ARCH == ARCH_CONTEXT_M )
    Os_Isr_Exit();
#else
#if( OS_MEMORY_PROTECTION == STD_ON )
    Os_SysCallParamType sysCallParam;
    Os_SysCall(Os_Syscall_Isr_Exit_ID, &sysCallParam);
#else
    Os_Isr_Exit();
#endif
#endif
}

/*
********************************************************************************
* Function Name: GetISRID
*
* Explanation: Standard API function, uses to get the information about the ISRID.
*
* param: None
*
* retval: Reference to the isr which is currently running.
********************************************************************************
*/
FUNC(ISRType, OS_CODE) GetISRID(void)
{
    ISRType isrId;

#if( OS_MEMORY_PROTECTION == STD_ON )
    Os_SysCallParamType sysCallParam;
    Os_SysCall(Os_Syscall_GetIsrId_ID, &sysCallParam);
    isrId = sysCallParam.Os_GetISRID.retVal;
#else
    isrId = Os_Isr_GetISRID();
#endif

    return isrId;
}

#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"
