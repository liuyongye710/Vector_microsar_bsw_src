/*
********************************************************************************
*
*  File name: Os_Spinlock.h
*
*  Copyright Neusoft Reach Corporation. All rights reserved.
*
********************************************************************************
*
* History
*-------------------------------------------------------------------------------
********************************************************************************
* Version: 3.0
* Author/Date: HanCL/2021.11.23
* Change: New create.
* Cause: New
********************************************************************************
* Version: 3.1
* Author/Date: LiG/2022.11.21
* Change: Change OS_VAR_NOINIT to OS_VAR_NO_INIT.
* Cause: Bugfix
********************************************************************************
*/
#ifndef OS_SPINLOCK_H_
#define OS_SPINLOCK_H_

/*
********************************************************************************
*    Includes
********************************************************************************
*/
#include "Os_Spinlock_Types.h"
#include "Std_Types.h"
#include "Os_Platform_Lcfg.h"
#include "Os_Task.h"
#include "Os_Isr.h"
#include "Os_App.h"

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
extern FUNC(void, OS_CODE) Os_Spinlock_Init
(
    P2CONST(Os_SpinlockCfgType, AUTOMATIC, OS_APPL_CONST) spinlockCfg
);
extern FUNC(void, OS_CODE) Os_Spinlock_IntlGetSpinlock
(
    SpinlockIdType spinlockId,
    CoreIdType coreId
);
extern FUNC(void, OS_CODE) Os_Spinlock_IntlReleaseSpinlock
(
    SpinlockIdType spinlockId,
    CoreIdType coreId
);
extern FUNC(Os_StatusType, OS_CODE) Os_Spinlock_GetSpinlock(SpinlockIdType spinlockId);
extern FUNC(Os_StatusType, OS_CODE) Os_Spinlock_ReleaseSpinlock(SpinlockIdType spinlockId);
extern FUNC(Os_StatusType, OS_CODE) Os_Spinlock_TryToGetSpinlock
(
    SpinlockIdType spinlockId,
    P2VAR(TryToGetSpinlockType, AUTOMATIC, OS_APPL_DATA) success
);
extern FUNC(void, OS_CODE) Os_Spinlock_ForceReleaseAll
(
    P2VAR(Os_ListNodeType, AUTOMATIC, OS_APPL_DATA) spinListHead
);

#endif /* OS_SPINLOCK_H_ */
