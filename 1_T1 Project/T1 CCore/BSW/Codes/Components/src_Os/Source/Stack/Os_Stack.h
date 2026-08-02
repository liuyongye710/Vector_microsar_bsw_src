/*
********************************************************************************
*
*  File name: Os_Stack.h
*
*  Copyright Neusoft Reach Corporation. All rights reserved.
*
********************************************************************************
*
* History
*-------------------------------------------------------------------------------
********************************************************************************
* Version: 3.0
* Author/Date: HanCL/2021.09.23
* Change: Add Autosar
* Cause: New
********************************************************************************
* Version: 3.1
* Author/Date: LiG/2022.11.21
* Change: Change OS_VAR_NOINIT to OS_VAR_NO_INIT.
* Cause: Bugfix
********************************************************************************
* Version: 3.2
* Author/Date: LiG/2023.2.15
* Change: Modified for QAC.
* Cause: Optimization
********************************************************************************
* Version: 3.3
* Author/Date: LiG/2023.3.24
* Change: Remove useless return values.
* Cause: Bugfix
********************************************************************************
*/
#ifndef OS_STACK_H_
#define OS_STACK_H_

/*
********************************************************************************
*    Includes
********************************************************************************
*/
#include "Os_Arch_Types.h"
#include "Os_Types.h"
#include "Os_Cfg.h"

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
extern FUNC(void, OS_CODE) Os_Stack_GetTaskStackUsage
(
    TaskType taskId,
    P2VAR(uint32, AUTOMATIC, OS_APPL_DATA) taskUsage
);
extern FUNC(void, OS_CODE) Os_Stack_GetIsrStackUsage
(
    ISRType isrId,
    P2VAR(uint32, AUTOMATIC, OS_APPL_DATA) isrUsage
);
extern FUNC(void, OS_CODE) Os_Stack_Init
(
    P2VAR(Os_Stack_Address, AUTOMATIC, OS_APPL_DATA) startAddr,
    P2VAR(Os_Stack_Address, AUTOMATIC, OS_APPL_DATA) endAddr
);

#if( OS_STACK_OVERFLOW_CHECK == STD_ON )
extern FUNC(void, OS_CODE) Os_Stack_Measure
(
    P2CONST(Os_Stack_Address, AUTOMATIC, OS_APPL_CONST) endAddr
);
#endif

#if( OS_CFG_MULTI_CORE == STD_ON )
extern FUNC(StatusType, OS_CODE) Os_Stack_TargetGetTaskStackUsage
(
    TaskType taskId,
    P2VAR(Os_Stack_Size, AUTOMATIC, OS_APPL_DATA) taskUsage
);
extern FUNC(StatusType, OS_CODE) Os_Stack_TargetGetIsrStackUsage
(
    ISRType isrId,
    P2VAR(Os_Stack_Size, AUTOMATIC, OS_APPL_DATA) isrUsage
);
#endif /* OS_CFG_MULTI_CORE == STD_ON */

#endif /* OS_STACK_H_ */
