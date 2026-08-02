/*
********************************************************************************
*
*  File name: Os_App.h
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
* Author/Date: LiG/2023.2.15
* Change: Modified for QAC.
* Cause: Optimization
********************************************************************************
*/
#ifndef OS_APP_H_
#define OS_APP_H_

/*
********************************************************************************
*    Includes
********************************************************************************
*/
#include "Os_App_Types.h"
#include "Os_Arch_Lcfg.h"
#include "Os_Cfg.h"

/*
********************************************************************************
*    Global Macros
********************************************************************************
*/
/* Determine whether the application permissions match. */
#define OS_APPMATCH(mask, appId)        (((mask) & ((uint32)OS_ONE_VALUE << (uint8)(appId))) == OS_ZERO_VALUE)
/* Get the application static configuration through id. */
#define OS_APP_GETCFG(appId)            (Os_AppCfgData[appId])
/* Determines whether the application is active and accessible. */
#define OS_APP_STATEOFF(appId)          (Os_AppCfgData[appId]->appDyn->appState != APPLICATION_ACCESSIBLE)
/* Get the application system error hook. */
#define Os_APPGETSYSERRORHOOK(coreId)   (Os_CoreCfgData[coreId]->systemApp->errorHook)
/* Get the application error hook. */
#define Os_APPGETERRORHOOK(appId)       (Os_AppCfgData[appId]->errorHook)
/* Get the application startup hook. */
#define Os_APPGETSTARTUPHOOK(appId)     (Os_AppCfgData[appId]->startupHook)
/* Get the application shutdown hook. */
#define Os_APPGETSHUDOWNHOOK(appId)     (Os_AppCfgData[appId]->shutdownHook)
/* Get the application id through static configuration. */
#define Os_APPGETAPPID(appCfg)          ((appCfg)->AppId)
/* Get the application is trust type. */
#define OS_APPGETTRUSTED(appId)         (Os_AppCfgData[appId]->appTrust)
/* Get the core id to which the alarm belongs through
   the alarm static configuration. */
#define OS_APP_GETCOREID(appCfg)        ((appCfg)->coreId)
/* Determine whether the application configures DelayTimingViolation. */
#define OS_APP_GETDELAYTIMING(appId)    (Os_AppCfgData[appId]->appDelayTimingViolation)

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
extern FUNC(void, OS_CODE) Os_App_Init
(
    P2CONST(Os_AppCfgType, AUTOMATIC, OS_APPL_CONST) app
);
extern FUNC(Os_StatusType, OS_CODE) Os_App_IntTerminationApp
(
    P2CONST(Os_AppCfgType, AUTOMATIC, OS_APPL_CONST) appCfg,
    RestartType restartOption
);
extern FUNC(Os_StatusType, OS_CODE) Os_App_TerminationApp
(
    ApplicationType appId,
    RestartType restartOption
);
extern FUNC(ApplicationType, OS_CODE) Os_App_GetAppId(void);
extern FUNC(ApplicationType, OS_CODE) Os_App_GetCurrentAppId(void);
extern FUNC(StatusType, OS_CODE) Os_App_GetAppState
(
    ApplicationType appId,
    ApplicationStateRefType value
);
#if( OS_CFG_MULTI_CORE == STD_ON )
extern FUNC(StatusType, OS_CODE) Os_App_TragetTerminationApp
(
    ApplicationType appId,
    RestartType restartOption
);
extern FUNC(StatusType, OS_CODE) Os_App_TragetGetAppState
(
    ApplicationType appId,
    ApplicationStateRefType value
);
#endif /* OS_CFG_MULTI_CORE == STD_ON */

#endif /* OS_APP_H_ */
