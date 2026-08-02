/*
********************************************************************************
*
*  File name: Os_App.c
*
*  Copyright Neusoft Reach Corporation. All rights reserved.
*
********************************************************************************
*
* History
*-------------------------------------------------------------------------------
********************************************************************************
* Version: 3.0
* Author/Date: HanCL/2021.11.19
* Change: New create.
* Cause: New
********************************************************************************
* Version: 3.1
* Author/Date: LiuJJ/2022.11.23
* Change: If Current app is a not trust app, return E_OS_ACCESS before trigger
*         Os_MultiCore_Trigger.
* Cause: Bugfix
********************************************************************************
* Version: 3.2
* Author/Date: HanCL/2023.1.12
* Change: Modify SC1 to support calling APP interface.
* Cause: Update
********************************************************************************
* Version: 3.3
* Author/Date: LiG/2023.1.29
* Change: Resolve the CallErrorHook privilege level problem.
* Cause: Optimization
********************************************************************************
* Version: 3.4
* Author/Date: LiG/2023.2.15
* Change: Modified for QAC.
* Cause: Optimization
********************************************************************************
* Version: 3.5
* Author/Date: LiG/2023.5.25
* Change: Fix the issue where non credit applications cannot call
*         TerminateApplication to end themselves.
* Cause: Bugfix
********************************************************************************
* Version: 3.6
* Author/Date: LiG/2023.5.26
* Change: TerminateApplication is used across cores and cannot be terminated.
* Cause: Bugfix
********************************************************************************
* Version: 3.7
* Author/Date: LiG/2023.5.27
* Change: Modified for QAC.
* Cause: Optimization
********************************************************************************
*/
/*
********************************************************************************
*    Includes
********************************************************************************
*/
#include "Os_Cfg.h"
#include "Os_App.h"
#include "Os_Task.h"
#include "Os_Isr.h"
#include "Os_Core.h"
#include "Os_SysCall.h"
#include "Os_MultiCore.h"
#include "Os_Hook.h"
#include "Os_Orti.h"
#include "Os.h"

/*
********************************************************************************
*    Local Macros
********************************************************************************
*/
/* Get restart task for application configuration. */
#define OS_APP_GETRESTARTTASK(appId)    (Os_AppCfgData[appId]->RestartTask)
/* Get the application state. */
#define OS_APP_GETSTATE(appCfg)         ((appCfg)->appDyn->appState)
/* Set the application state. */
#define OS_APP_SETSTATE(appCfg, state)  ((appCfg)->appDyn->appState = (state))

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
/*
********************************************************************************
*    Global Constants
********************************************************************************
*/

#define OS_START_SEC_CODE
#include "Os_MemMap.h"
/*
********************************************************************************
* Function Name: Os_App_Init
*
* Explanation: Initialize the application.
*
* param: app: Reference to the application configuration.
*
* retval: None
********************************************************************************
*/
FUNC(void, OS_CODE) Os_App_Init
(
    P2CONST(Os_AppCfgType, AUTOMATIC, OS_APPL_CONST) app
)
{
    if( app != NULL_PTR )
    {
        app->appDyn->appState = APPLICATION_ACCESSIBLE;
    }
}

/*
********************************************************************************
* Function Name: Os_App_GetAppId
*
* Explanation: Uses to get application index.
*
* param: None
*
* retval: Application index.
********************************************************************************
*/
FUNC(ApplicationType, OS_CODE) Os_App_GetAppId(void)
{
    ApplicationType ret = INVALID_OSAPPLICATION;
    CoreIdType coreId;
    Os_ProcType procType;

    OS_ORTI_API_MONITOR_ENTRY(OSServiceId_GetApplicationID);
    /* Get logic core id. */
    coreId = Os_Core_GetLogicId();

    if( !OS_CORE_PROCESSTYPEMATCH(coreId, OS_GETAPPID_ACCESS) ) /* If the api is not accessible. */
    {
        if( !OS_CORE_APPISVALID(coreId) )   /* If the app is valid. */
        {
            procType = OS_CORE_GETPROTYPE(coreId);
            /* Whether the task is currently being processed. */
            if( OS_TASK_TYPE_MASK == procType )
            {
                TaskType taskId;

                taskId = OS_CORE_GETCURRENTTASKID(coreId);
                ret = OS_TASK_GETAPPID(OS_TASK_GETCFG(taskId));
            }
            else if( OS_ISR_CAT2_TYPE_MASK == procType )    /* Whether the isr is currently being processed. */
            {
                ISRType isrId;

                isrId = OS_CORE_GETCURRENTISRID(coreId);
                ret = OS_ISR_GETAPPID(OS_ISR_GETCFG(isrId));
            }
            else
            {
                ret = OS_CORE_GETAPPID(coreId);
            }
        }
    }
    OS_ORTI_API_MONITOR_EXIT(OSServiceId_GetApplicationID);

    return ret;
}

/*
********************************************************************************
* Function Name: Os_App_GetCurrentAppId
*
* Explanation: Uses to get currently application index.
*
* param: None
*
* retval: Currently application index.
********************************************************************************
*/
FUNC(ApplicationType, OS_CODE) Os_App_GetCurrentAppId(void)
{
    ApplicationType ret = INVALID_OSAPPLICATION;
    CoreIdType coreId;

    OS_ORTI_API_MONITOR_ENTRY(OSServiceId_GetCurrentApplicationID);
    /* Get logic core id. */
    coreId = Os_Core_GetLogicId();

    if( !OS_CORE_PROCESSTYPEMATCH(coreId, OS_GETCURRENTAPPID_ACCESS) ) /* If the api is not accessible. */
    {
        if( !OS_CORE_APPISVALID(coreId) )   /* If the app is valid. */
        {
            ret = OS_CORE_GETAPPID(coreId);
        }
    }
    OS_ORTI_API_MONITOR_EXIT(OSServiceId_GetCurrentApplicationID);

    return ret;
}

/*
********************************************************************************
* Function Name: Os_App_IntTerminationApp
*
* Explanation: Internal function to terminate application.
*
* param: appCfg: Application configuration.
*        restartOption: Either RESTART for doing a restart of the OS-Application
*                       or NO_RESTART if OS-Application shall not be restarted.
*
* retval: E_OS_OK: No error.
*         E_OS_ID: Invalid App Id.
*         E_OS_STATE: Invalid state does not allow terminating.
********************************************************************************
*/
FUNC(Os_StatusType, OS_CODE) Os_App_IntTerminationApp
(
    P2CONST(Os_AppCfgType, AUTOMATIC, OS_APPL_CONST) appCfg,
    RestartType restartOption
)
{
    Os_StatusType ret = E_OS_OK;

    if( APPLICATION_TERMINATED == OS_APP_GETSTATE(appCfg) )   /* If the app is terminated. */
    {
        ret = E_OS_STATE;
    }
    else
    {
        /* Termination all. */
        Os_Core_TerminationApp(appCfg->coreId, appCfg->AppId);
        if( RESTART == restartOption ) /* If the restartOption is equal RESTART. */
        {
            /* Set app state to restarting. */
            OS_APP_SETSTATE(appCfg, APPLICATION_RESTARTING);
            /* Active the restart task. */
            (void)Os_Task_ActivateTaskSimp(appCfg->RestartTask);
        }
        else
        {
            /* Set app state to terminated. */
            OS_APP_SETSTATE(appCfg, APPLICATION_TERMINATED);
        }
    }

    return ret;
}

/*
********************************************************************************
* Function Name: Os_App_TerminationApp
*
* Explanation: Uses to terminate application.
*
* param: appId: Application index.
*        restartOption: Either RESTART for doing a restart of the OS-Application
*                       or NO_RESTART if OS-Application shall not be restarted.
*
* retval: E_OS_OK: No error.
*         E_OS_ID: Invalid App Id.
*         E_OS_CALLEVEL: Called from invalid context.
*         E_OS_VALUE: Invalid restart option.
*         E_OS_DISABLEDINT: A service of the OS is called inside an interrupt
*                           disable/enable pair.
*         E_OS_ACCESS: Caller's access rights are not sufficient.
*         E_OS_STATE: Invalid state does not allow terminating.
********************************************************************************
*/
FUNC(Os_StatusType, OS_CODE) Os_App_TerminationApp
(
    ApplicationType appId,
    RestartType restartOption
)
{
    Os_StatusType ret;
    CoreIdType coreId;
    const Os_AppCfgType* desAppCfg;
    const Os_AppCfgType* curAppCfg;
    Os_Arch_IntState intState;

    OS_ORTI_API_MONITOR_ENTRY(OSServiceId_TerminateApplication);
    /* Get logic core id. */
    coreId = Os_Core_GetLogicId();
    /* Get current app configuration data. */
    curAppCfg = OS_APP_GETCFG(OS_CORE_GETAPPID(coreId));

    if( appId >= OS_APPID_COUNT )
    {
        ret = E_OS_ID;
    }
    else if( OS_CORE_MASK_INTERRUPT(coreId) ) /* If interrupts is disable. */
    {
        ret = E_OS_DISABLEDINT;
    }
    else if( OS_CORE_PROCESSTYPEMATCH(coreId, OS_TERMINATEAPP_ACCESS) ) /* If the api is not accessible. */
    {
        ret = E_OS_CALLEVEL;
    }
    else if( restartOption > NO_RESTART )   /* If the restartoption is invalid. */
    {
        ret = E_OS_VALUE;
    }
    else if( (NULL_PTR == OS_APP_GETRESTARTTASK(appId)) && (RESTART == restartOption) )
    {
        ret = E_OS_STATE;
    }
    /* If the current app is not trust app and target application isn't source current application . */
    else if( (OS_APP_NOTRUSTED == curAppCfg->appTrust) && (appId != curAppCfg->AppId) )
    {
        ret = E_OS_ACCESS;
    }
    else
    {
        /* Get tartget app configuration data. */
        desAppCfg = OS_APP_GETCFG(appId);

#if( OS_CFG_MULTI_CORE == STD_ON )
        if( coreId == OS_APP_GETCOREID(desAppCfg) )
#endif
        {
            if( APPLICATION_TERMINATED == OS_APP_GETSTATE(desAppCfg) )
            {
                ret = E_OS_STATE;
            }
            else
            {
                /* Disable interrupt. */
                Os_Arch_IntDisable(&intState);
                ret = Os_App_IntTerminationApp(desAppCfg, restartOption);
                Os_Task_AppTerminateTaskSwitch(appId);
                /* Enable interrupt. */
                Os_Arch_IntEnable(intState);
            }
        }
#if( OS_CFG_MULTI_CORE == STD_ON )
        else
        {
            Os_MultiCoreServeParamType parameter;
            parameter.Os_TerminateApplication.appId = appId;
            parameter.Os_TerminateApplication.restartOption = restartOption;
            /* Execute multi-core calling function. */
            ret = Os_MultiCore_Trigger(TRUE, coreId, OS_APP_GETCOREID(desAppCfg),
                                       Os_MCServe_TerminateApplication_ID, &parameter);
        }
#endif
    }
    OS_ORTI_API_MONITOR_EXIT(OSServiceId_TerminateApplication);

    return Os_Hook_CallErrorHook(OSServiceId_TerminateApplication, ret);
}

/*
********************************************************************************
* Function Name: Os_App_GetAppState
*
* Explanation: Uses to get application state.
*
* param: appId: Application index.
*        value: The current state of the application.
*
* retval: E_OS_OK: No error.
*         E_OS_ID: Invalid App Id.
*         E_OS_CALLEVEL: Called from invalid context.
*         E_OS_PARAM_POINTER: A null pointer was given as argument.
*         E_OS_DISABLEDINT: A service of the OS is called inside an interrupt
*                           disable/enable pair.
********************************************************************************
*/
FUNC(StatusType, OS_CODE) Os_App_GetAppState
(
    ApplicationType appId,
    ApplicationStateRefType value
)
{
    Os_StatusType ret = E_OS_OK;
    CoreIdType coreId;
    const Os_AppCfgType* appCfg;

    OS_ORTI_API_MONITOR_ENTRY(OSServiceId_GetApplicationState);
    /* Get logic core id. */
    coreId = Os_Core_GetLogicId();

    if( NULL_PTR == value )
    {
       ret = E_OS_PARAM_POINTER;
    }
    else if( appId >= OS_APPID_COUNT )
    {
       ret = E_OS_ID;
    }
    else if( OS_CORE_MASK_INTERRUPT(coreId) ) /* If interrupts is disable. */
    {
       ret = E_OS_DISABLEDINT;
    }
    else if( OS_CORE_PROCESSTYPEMATCH(coreId, OS_GETAPPSTATE_ACCESS) ) /* If the api is not accessible. */
    {
       ret = E_OS_CALLEVEL;
    }
    else
    {
        /* Get app configuration data. */
        appCfg = OS_APP_GETCFG(appId);
#if( OS_CFG_MULTI_CORE == STD_ON )
        if( coreId == OS_APP_GETCOREID(appCfg) )
#endif
        {
           *value = OS_APP_GETSTATE(appCfg);
        }

#if( OS_CFG_MULTI_CORE == STD_ON )
        else
        {
            Os_MultiCoreServeParamType parameter;
            parameter.Os_GetApplicationState.appId = appId;
            parameter.Os_GetApplicationState.value = value;
            /* Execute multi-core calling function. */
            ret = Os_MultiCore_Trigger(TRUE, coreId, OS_APP_GETCOREID(appCfg),
                                       Os_MCServe_GetApplicationState_ID, &parameter);
        }
#endif
    }
    OS_ORTI_API_MONITOR_EXIT(OSServiceId_GetApplicationState);

    return Os_Hook_CallErrorHook(OSServiceId_GetApplicationState, ret);
}

#if( OS_CFG_MULTI_CORE == STD_ON )
/*
********************************************************************************
* Function Name: Os_App_TragetTerminationApp
*
* Explanation: Multicore function to terminate application.
*
* param: appId: Application index.
*        restartOption: Either RESTART for doing a restart of the OS-Application
*                       or NO_RESTART if OS-Application shall not be restarted.
*
* retval: E_OS_OK: No error.
*         E_OS_ID: Invalid App Id.
*         E_OS_CORE: Core is not available.
*         E_OS_ACCESS: Caller's access rights are not sufficient.
********************************************************************************
*/
FUNC(StatusType, OS_CODE) Os_App_TragetTerminationApp
(
    ApplicationType appId,
    RestartType restartOption
)
{
    Os_StatusType ret;
    CoreIdType coreId;
    const Os_AppCfgType* appCfg;

    if( appId >= OS_APPID_COUNT )
    {
        ret = E_OS_ID;
    }
    else
    {
        /* Get alarm configuration data. */
        appCfg = OS_APP_GETCFG(appId);
        /* Get logic core id. */
        coreId = Os_Core_GetLogicId();
        if( coreId == appCfg->coreId )
        {
            if( APPLICATION_RESTARTING == OS_APP_GETSTATE(appCfg) )
            {
                ret = E_OS_ACCESS;
            }
            else
            {
                ret = Os_App_IntTerminationApp(appCfg, restartOption);
                Os_Task_AppTerminateTaskSwitch(appId);
            }
        }
        else
        {
            ret = E_OS_CORE;
        }
    }

    return ret;
}

/*
********************************************************************************
* Function Name: Os_App_TragetGetAppState
*
* Explanation: Multicore function to get application state.
*
* param: appId: Application index.
*        value: The current state of the application.
*
* retval: E_OS_OK: No error.
*         E_OS_ID: Invalid App Id.
*         E_OS_CORE: Core is not available.
********************************************************************************
*/
FUNC(StatusType, OS_CODE) Os_App_TragetGetAppState
(
    ApplicationType appId,
    ApplicationStateRefType value
)
{
    Os_StatusType ret = E_OS_OK;
    CoreIdType coreId;
    const Os_AppCfgType* appCfg;

    if( appId >= OS_APPID_COUNT )
    {
        ret = E_OS_ID;
    }
    else
    {
        /* Get alarm configuration data. */
        appCfg = OS_APP_GETCFG(appId);
        /* Get logic core id. */
        coreId = Os_Core_GetLogicId();
        if( coreId == appCfg->coreId )
        {
            *value = OS_APP_GETSTATE(appCfg);
        }
        else
        {
            ret = E_OS_CORE;
        }
    }

    return ret;
}
#endif /* OS_CFG_MULTI_CORE == STD_ON */

/*
********************************************************************************
* Function Name: TerminateApplication
*
* Explanation: This service terminates the OS-Application to which the calling
*              Task/Category 2 ISR/application specific error hook belongs.
*
* param: Application: Application index.
*        RestartOption: Either RESTART for doing a restart of the OS-Application
*                       or NO_RESTART if OS-Application shall not be restarted.
*
* retval: E_OS_OK: No error.
*         E_OS_ID: Invalid App Id.
*         E_OS_CALLEVEL: Called from invalid context.
*         E_OS_VALUE: Invalid restart option.
*         E_OS_DISABLEDINT: A service of the OS is called inside an interrupt
*                           disable/enable pair.
*         E_OS_ACCESS: Caller's access rights are not sufficient.
*         E_OS_STATE: Invalid state does not allow terminating.
********************************************************************************
*/
FUNC(StatusType, OS_CODE) TerminateApplication
(
    ApplicationType Application,
    RestartType RestartOption
)
{
    StatusType status;

#if( OS_MEMORY_PROTECTION == STD_ON )
    Os_SysCallParamType sysCallParam;

    sysCallParam.Os_TerminateApplication.appId = Application;
    sysCallParam.Os_TerminateApplication.restartOption = RestartOption;
    Os_SysCall(Os_Syscall_TerminateApplication_ID, &sysCallParam);
    status = sysCallParam.Os_TerminateApplication.retVal;
#else
    status = Os_App_TerminationApp(Application, RestartOption);
#endif

    return status;
}

/*
********************************************************************************
* Function Name: GetApplicationID
*
* Explanation: This service determines the OS-Application (a unique identifier
*              has to be allocated to each application) where the caller originally
*              belongs to (was configured to).
*
* param: None
*
* retval: Application index.
********************************************************************************
*/
FUNC(ApplicationType, OS_CODE) GetApplicationID(void)
{
    ApplicationType appId;

#if( OS_MEMORY_PROTECTION == STD_ON )
        Os_SysCallParamType sysCallParam;

        Os_SysCall(Os_Syscall_GetApplicationId_ID, &sysCallParam);
        appId = sysCallParam.Os_GetApplicationID.retVal;
#else
        appId = Os_App_GetAppId();
#endif

    return appId;
}

/*
********************************************************************************
* Function Name: GetCurrentApplicationID
*
* Explanation: This service determines the OS-Application where the caller of
*              the service is currently executing.
*
* param: None
*
* retval: Currently application index.
********************************************************************************
*/
FUNC(ApplicationType, OS_CODE) GetCurrentApplicationID(void)
{
    ApplicationType appId;

#if( OS_MEMORY_PROTECTION == STD_ON )
    Os_SysCallParamType sysCallParam;

    Os_SysCall(Os_Syscall_GetCurrentApplicationId_ID, &sysCallParam);
    appId = sysCallParam.Os_GetCurrentApplicationID.retVal;
#else
    appId = Os_App_GetCurrentAppId();
#endif

    return appId;
}

/*
********************************************************************************
* Function Name: GetApplicationState
*
* Explanation: This service returns the current state of an OS-Application.
*
* param: Application: Application index.
*        Value: The current state of the application.
*
* retval: E_OS_OK: No error.
*         E_OS_ID: Invalid App Id.
*         E_OS_CALLEVEL: Called from invalid context.
*         E_OS_PARAM_POINTER: A null pointer was given as argument.
*         E_OS_DISABLEDINT: A service of the OS is called inside an interrupt
*                           disable/enable pair.
********************************************************************************
*/
FUNC(StatusType, OS_CODE) GetApplicationState
(
    ApplicationType Application,
    ApplicationStateRefType Value
)
{
    StatusType status;

#if( OS_MEMORY_PROTECTION == STD_ON )
    Os_SysCallParamType sysCallParam;

    sysCallParam.Os_GetApplicationState.appId = Application;
    sysCallParam.Os_GetApplicationState.value = Value;
    Os_SysCall(Os_Syscall_GetApplicationState_ID, &sysCallParam);
    status = sysCallParam.Os_GetApplicationState.retVal;
#else
    status = Os_App_GetAppState(Application, Value);
#endif

    return status;
}

#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"
