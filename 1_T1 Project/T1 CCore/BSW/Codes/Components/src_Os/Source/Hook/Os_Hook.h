/*
********************************************************************************
*
*  File name: Os_Hook.h
*
*  Copyright Neusoft Reach Corporation. All rights reserved.
*
********************************************************************************
*
* History
*-------------------------------------------------------------------------------
********************************************************************************
* Version: 3.0
* Author/Date: HanCL/2021.11.17
* Change: New create.
* Cause: New
********************************************************************************
*/
#ifndef OS_HOOK_H_
#define OS_HOOK_H_

/*
********************************************************************************
*    Includes
********************************************************************************
*/
#include "Std_Types.h"
#include "Os_Types.h"
#include "Os_Hook_Types.h"
#include "Os_Core_Types.h"

/*
********************************************************************************
*    Global Macros
********************************************************************************
*/
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
extern FUNC(void, OS_CODE) Os_Hook_CallStartupHook
(
    CoreIdType coreId
);
extern FUNC(void, OS_CODE) Os_CallPreTaskHook
(
    P2CONST(Os_TaskCfgType, AUTOMATIC, OS_APPL_CONST) task
);
extern FUNC(void, OS_CODE) Os_CallPostTaskHook
(
    P2CONST(Os_TaskCfgType, AUTOMATIC, OS_APPL_CONST) task
);
extern FUNC(void, OS_CODE) Os_Hook_CallShutdownHook
(
    CoreIdType coreId,
    StatusType error,
    boolean sync
);
extern FUNC(StatusType, OS_CODE) Os_Hook_CallErrorHook
(
    OSServiceIdType serviceId,
    StatusType error
);
extern FUNC(void, OS_CODE) Os_Hook_CallProtectionHook
(
    StatusType error
);

#endif /* OS_HOOK_H_ */
