/*
********************************************************************************
*
*  File name: Os.h
*
*  Copyright Neusoft Reach Corporation. All rights reserved.
*
********************************************************************************
*
* History
*-------------------------------------------------------------------------------
********************************************************************************
* Version: 3.0
* Author/Date: HanCL/2021.11.16
* Change: New create.
* Cause: New
********************************************************************************
* Version: 3.1
* Author/Date: LiG/2022.11.21
* Change: Change OS_VAR_NOINIT to OS_VAR_NO_INIT.
* Cause: Bugfix
********************************************************************************
* Version: 3.2
* Author/Date: LiG/2023.2.14
* Change: Notes optimization.
* Cause: Optimization
********************************************************************************
* Version: 3.3
* Author/Date: LiG/2023.2.15
* Change: Add macro switch.
* Cause: Bugfix
********************************************************************************
* Version: 3.4
* Author/Date: LiG/2023.2.15
* Change: Modified for QAC.
* Cause: Optimization
********************************************************************************
* Version: 3.5
* Author/Date: LiG/2023.4.3
* Change: Remove the Cpload file.
* Cause: Optimization
********************************************************************************
* Version: 3.6
* Author/Date: LiG/2023.4.4
* Change: Adapt to ORTI.
* Cause: Update
********************************************************************************
* Version: 3.7
* Author/Date: LiG/2023.4.6
* Change: Modify version number.
* Cause: Update
********************************************************************************
* Version: 3.8
* Author/Date: LiG/2023.5.5
* Change: Modify version number.
* Cause: Update
********************************************************************************
* Version: 3.9
* Author/Date: LiuJJ/2023.5.15
* Change: Modify version number.
* Cause: Update
********************************************************************************
* Version: 3.10
* Author/Date: LiG/2023.5.19
* Change: Modify version number.
* Cause: Update
********************************************************************************
* Version: 3.11
* Author/Date: LiG/2023.5.27
* Change: Modify version number.
* Cause: Update
********************************************************************************
* Version: 3.12
* Author/Date: LiG/2023.6.9
* Change: Modify version number.
* Cause: Update
********************************************************************************
*/
#ifndef OS_H_
#define OS_H_

/*
********************************************************************************
*    Includes
********************************************************************************
*/
#include "Std_Types.h"
#include "Os_Cfg.h"
#include "Os_Types_Cfg.h"
#include "Os_Types.h"
#include "Os_Ioc_Lcfg.h"
#include "Os_Lcfg.h"
#include "Os_Monitor.h"

/*
********************************************************************************
*    Global Macros
********************************************************************************
*/
/* Vendor and module identification */
#define OS_VENDOR_ID                            (119U)
#define OS_MODULE_ID                            (1U)

/* Component version information */
#define OS_SW_MAJOR_VERSION                     (3U)
#define OS_SW_MINOR_VERSION                     (2U)
#define OS_SW_PATCH_VERSION                     (1U)

/* Autosar version information */
#define OS_AR_RELEASE_MAJOR_VERSION             (4U) 
#define OS_AR_RELEASE_MINOR_VERSION             (2U) 
#define OS_AR_RELEASE_REVISION_VERSION          (2U)
/*
********************************************************************************
*    Global Types
********************************************************************************
*/
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
extern FUNC(void, OS_CODE) Os_Init(void);
extern FUNC(void, OS_CODE) StartOS(AppModeType Mode);
extern FUNC(void, OS_CODE) StartCore
(
    CoreIdType CoreID,
    P2VAR(StatusType, AUTOMATIC, OS_APPL_DATA) Status
);
extern FUNC(void, OS_CODE) ShutdownOS(StatusType Error);
extern FUNC(StatusType, OS_CODE) GetAlarm(AlarmType AlarmID, TickRefType Tick);
extern FUNC(StatusType, OS_CODE) SetRelAlarm
(
    AlarmType AlarmID,
    TickType Increment,
    TickType Cycle
);
extern FUNC(StatusType, OS_CODE) SetAbsAlarm
(
    AlarmType AlarmID,
    TickType Start,
    TickType Cycle
);
extern FUNC(StatusType, OS_CODE) CancelAlarm(AlarmType AlarmID);
extern FUNC(StatusType, OS_CODE) GetAlarmBase
(
    AlarmType AlarmID,
    AlarmBaseRefType Info
);
extern FUNC(StatusType, OS_CODE) IncrementCounter(CounterType CounterID);
extern FUNC(StatusType, OS_CODE) GetCounterValue
(
    CounterType CounterID,
    TickRefType Value
);
extern FUNC(StatusType, OS_CODE) GetElapsedValue
(
    CounterType CounterID,
    TickRefType Value,
    TickRefType ElapsedValue
);
extern FUNC(ISRType, OS_CODE) GetISRID(void);
extern FUNC(CoreIdType, OS_CODE) GetCoreID(void);
extern FUNC(void, OS_CODE) StartNonAutosarCore
(
    CoreIdType CoreID,
    P2CONST(StatusType, AUTOMATIC, OS_APPL_CONST) Status
);
extern FUNC(StatusType, OS_CODE) DisableInterruptSource
(
    ISRType ISRID
);
extern FUNC(StatusType, OS_CODE) EnableInterruptSource
(
    ISRType ISRID,
    boolean ClearPending
);
extern FUNC(StatusType, OS_CODE) ClearPendingInterrupt(ISRType ISRID);
extern FUNC(void, OS_CODE) DisableAllInterrupts(void);
extern FUNC(void, OS_CODE) EnableAllInterrupts(void);
extern FUNC(void, OS_CODE) SuspendAllInterrupts(void);
extern FUNC(void, OS_CODE) ResumeAllInterrupts(void);
extern FUNC(void, OS_CODE) SuspendOSInterrupts(void);
extern FUNC(void, OS_CODE) ResumeOSInterrupts(void);
extern FUNC(StatusType, OS_CODE) ActivateTask(TaskType TaskID);
extern FUNC(StatusType, OS_CODE) TerminateTask(void);
extern FUNC(StatusType, OS_CODE) ChainTask(TaskType TaskID);
extern FUNC(StatusType, OS_CODE) Schedule(void);
extern FUNC(StatusType, OS_CODE) GetTaskID(TaskRefType TaskID);
extern FUNC(StatusType, OS_CODE) GetTaskState
(
    TaskType TaskID,
    TaskStateRefType State
);
extern FUNC(StatusType, OS_CODE) SetEvent(TaskType TaskID, EventMaskType Mask);
extern FUNC(StatusType, OS_CODE) ClearEvent(EventMaskType Mask);
extern FUNC(StatusType, OS_CODE) GetEvent(TaskType TaskID, EventMaskRefType Mask);
extern FUNC(StatusType, OS_CODE) WaitEvent(EventMaskType Mask);
extern FUNC(StatusType, OS_CODE) GetResource(ResourceType ResID);
extern FUNC(StatusType, OS_CODE) ReleaseResource(ResourceType ResID);
extern FUNC(StatusType, OS_CODE) GetSpinlock(SpinlockIdType SpinlockId);
extern FUNC(StatusType, OS_CODE) ReleaseSpinlock(SpinlockIdType SpinlockId);
extern FUNC(StatusType, OS_CODE) TryToGetSpinlock
(
    SpinlockIdType SpinlockId,
    P2VAR(TryToGetSpinlockType, AUTOMATIC, OS_APPL_DATA) Success
);
extern FUNC(void, OS_CODE) ShutdownAllCores(StatusType Error);
extern FUNC(StatusType, OS_CODE) CallTrustedFunction
(
    TrustedFunctionIndexType FunctionIndex,
    TrustedFunctionParameterRefType FunctionParams
);
extern FUNC(StatusType, OS_CODE) StartScheduleTableRel
(
    ScheduleTableType ScheduleTableID,
    TickType Offset
);
extern FUNC(StatusType, OS_CODE) StartScheduleTableAbs
(
    ScheduleTableType ScheduleTableID,
    TickType Start
);

#if( (OS_CFG_SCALABILITY_CLASS == OS_SC2) || (OS_CFG_SCALABILITY_CLASS == OS_SC4) )
extern FUNC(StatusType, OS_CODE) StartScheduleTableSynchron
(
    ScheduleTableType ScheduleTableID
);
extern FUNC(StatusType, OS_CODE) SyncScheduleTable
(
    ScheduleTableType ScheduleTableID,
    TickType Value
);
extern FUNC(StatusType, OS_CODE) SetScheduleTableAsync
(
    ScheduleTableType ScheduleTableID
);
#endif /* ( (OS_CFG_SCALABILITY_CLASS == OS_SC2) || (OS_CFG_SCALABILITY_CLASS == OS_SC4) ) */
extern FUNC(StatusType, OS_CODE) GetScheduleTableStatus
(
    ScheduleTableType ScheduleTableID,
    ScheduleTableStatusRefType ScheduleStatus
);
extern FUNC(StatusType, OS_CODE) NextScheduleTable
(
    ScheduleTableType ScheduleTableID_From,
    ScheduleTableType ScheduleTableID_To
);
extern FUNC(StatusType, OS_CODE) StopScheduleTable
(
    ScheduleTableType ScheduleTableID
);
extern FUNC(StatusType, OS_CODE) TerminateApplication
(
    ApplicationType Application,
    RestartType RestartOption
);
extern FUNC(ApplicationType, OS_CODE) GetApplicationID(void);
extern FUNC(ApplicationType, OS_CODE) GetCurrentApplicationID(void);
extern FUNC(StatusType, OS_CODE) GetApplicationState
(
    ApplicationType Application,
    ApplicationStateRefType Value
);
extern FUNC(uint32, OS_CODE) GetTaskStackUsage(TaskType TaskID);
extern FUNC(uint32, OS_CODE) GetISRStackUsage(ISRType IsrID);
extern FUNC(void, OS_CODE) Os_Monitor_init(void);
extern FUNC(void, OS_CODE) Os_Monitor_MainFunction(void);

#endif /* OS_H_ */
