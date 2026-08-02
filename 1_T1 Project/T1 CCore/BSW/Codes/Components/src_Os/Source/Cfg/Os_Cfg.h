/*
********************************************************************************
*
*  File name:	Os_Cfg.h
*
*  Copyright	Neusoft Reach Corporation. All rights reserved.
*
********************************************************************************
*
* History
*-------------------------------------------------------------------------------
********************************************************************************
* Version: 3.0
* Author/Date : HanCL/2021.11.23
* Change: New create.
* Cause: New
********************************************************************************
*/
#ifndef OS_CFG_H_
#define OS_CFG_H_

/*
********************************************************************************
*    Includes
********************************************************************************
*/
#include "Os_Arch_Cfg.h"
/*
********************************************************************************
*    Global Macros
********************************************************************************
*/
#define OS_CFG_ERRORHOOK_SYSTEM                       (STD_ON)
#define OS_CFG_SHUTDOWNHOOK_SYSTEM                    (STD_ON)
#define OS_CFG_STARTUPHOOK_SYSTEM                     (STD_OFF)
#define OS_CFG_PROTECTIONHOOK_SYSTEM                  (STD_OFF)
#define OS_CFG_SCALABILITY_CLASS                      (OS_SC1)
#define OS_CFG_ASSERTIONS_ENABLED                     (STD_OFF)
#define OS_MEMORY_PROTECTION                          (STD_OFF)
#define OS_CFG_RESOURCE_ENABLE                        (STD_ON)
#define OS_CFG_SPINLOCKNEST_ENABLE                    (STD_OFF)
#define OS_CFG_SPINLOCK_ENABLE                        (STD_OFF)
#define OS_CFG_SPINLOCKMAXNESTNUM                     (0U)
#define OS_CFG_TASK_PROC_NUM_GR64                     (STD_OFF)
#define OS_CFG_MULTI_CORE                             (STD_ON)
#define OS_CFG_IOC_ENABLE                             (STD_OFF)
#define OS_SYSTEM_MPU                                 (STD_OFF)
#define OS_CFG_TP_ENABLE                              ((OS_ZERO_VALUE << OS_CORE_ID_0) | (OS_ZERO_VALUE << OS_CORE_ID_1) | (OS_ZERO_VALUE << OS_CORE_ID_2))
#define OS_CORE_MPU                                   (STD_OFF)
#define OS_CFG_TRUSTFUN                               (STD_OFF)
#define OS_CFG_SCHDTB_ENABLE                          (STD_OFF)
#define OS_CFG_SCHDTBSYNC_ENABLE                      (STD_OFF)
#define OS_CFG_FPU_ENABLE                             (STD_ON)
#define OS_CFG_ORTI_ENABLE                            (STD_OFF)
#define OS_CFG_ORTI_API_MONITOR_ENABLE                (STD_OFF)
#define OS_CFG_ORTI_HOOK_ENABLE                       (STD_OFF)
#define OS_STACK_OVERFLOW_CHECK                       (STD_ON)
#define OS_ERRORHOOKFINISH                            (STD_OFF)
#define OS_APPMODE_NONE ((AppModeType)0U)
#define OSDEFAULTAPPMODE ((AppModeType)1U)
#define OS_APPMODE_ANY ((AppModeType)255U)


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

#endif /* OS_CFG_H_ */

