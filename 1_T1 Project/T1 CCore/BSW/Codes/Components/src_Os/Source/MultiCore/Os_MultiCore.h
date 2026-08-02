/*
********************************************************************************
*
*  File name: Os_MultiCore.h
*
*  Copyright Neusoft Reach Corporation. All rights reserved.
*
********************************************************************************
*
* History
*-------------------------------------------------------------------------------
********************************************************************************
* Version: 3.0
* Author/Date: HanCL/2021.11.24
* Change: New create.
* Cause: New
********************************************************************************
* Version: 3.1
* Author/Date: WangJP/2022.12.10
* Change: Modification of coding standard.
* Cause: Optimize
********************************************************************************
* Version: 3.2
* Author/Date: LiG/2023.2.15
* Change: Modified for QAC.
* Cause: Optimization
********************************************************************************
*/
#ifndef OS_MULTICORE_H_
#define OS_MULTICORE_H_

/*
********************************************************************************
*    Includes
********************************************************************************
*/
#include "Os_MultiCore_Types.h"
#include "Std_Types.h"
#include "Os_Cfg.h"

#if( OS_CFG_MULTI_CORE == STD_ON )
/*
********************************************************************************
*    Global Macros
********************************************************************************
*/
/* Multi-core synchronization initialization value. */
#define OS_MULTISYNCINIT                        (0xFF)
/* Multi-core synchronization for the first time. */
#define OS_MULTISYNCFIRST                       (0x01)
/* Multi-core synchronization for the second time. */
#define OS_MULTISYNCSECOND                      (0x02)
/* Multi-core synchronization for the third time. */
#define OS_MULTISYNCTHIRD                       (0x03)
/* Multi-core synchronization for the fourth time. */
#define OS_MULTISYNCFOURTH                      (0x04)
#define OS_SETMULTISYNCCOUNTER(coreId, counter) (Os_MultiCoreSync[coreId] = (counter))

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
extern volatile VAR(uint8, OS_VAR_NO_INIT) Os_MultiCoreSync[OS_COREID_COUNT];

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
extern void Os_MultiCore_Sync
(
    CoreIdType coreId,
    uint8 syncCounter
);
extern Os_StatusType Os_MultiCore_Trigger
(
    boolean isSync,
    CoreIdType srcCore,
    CoreIdType desCore,
    Os_MCServe_FuncId funcId,
    Os_MultiCoreServeParamType* param
);
extern OS_ISR(Os_MultiCoreServer_Handler);
#endif /* OS_CFG_MULTI_CORE == STD_ON */

#endif /* OS_MULTICORE_H_ */
