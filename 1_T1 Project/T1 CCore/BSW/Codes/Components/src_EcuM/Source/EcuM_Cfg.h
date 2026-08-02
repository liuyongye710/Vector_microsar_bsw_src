/*
********************************************************************************
*
* File name: EcuM_Cfg.h
*
* Copyright 2019-2024 Neusoft Reach Corporation. All rights reserved.
*
********************************************************************************
*
*  History
*-------------------------------------------------------------------------------
********************************************************************************
* Version: 2.0
* Author/Date : yong.zhang/2019.11.26
* Change: New created.
* Cause: New
********************************************************************************
* Version: 2.1
* Author/Date: guoziyang/2020.11.18
* Change: Modify compilation warning.
* Cause: Optimization
********************************************************************************
* Version: 2.2
* Author/Date: GuoZY/2021.10.28
* Change: Increase the header file to include.(Os.h) 
* Cause: Optimization
********************************************************************************
* Version: 2.3
* Author/Date: GuoZY/2021.12.10
* Change: Add conditional compilation for Mcu.h.
* Cause: Optimization
********************************************************************************
* Version: 2.4
* Author/Date: GuoZY/2021.12.17
* Change: Delete type definition.
* Cause: Optimization
********************************************************************************
* Version: 3.0
* Author/Date: TianL/2024.8.5
* Change: Modify copyright.
* Cause: Update
********************************************************************************
*/
#ifndef ECUM_CFG_H_
#define ECUM_CFG_H_

/*
********************************************************************************
*    Includes
********************************************************************************
*/
#include "Std_Types.h"
#include "EcuM_Types.h"
#include "Os.h"

/*
********************************************************************************
*    Global Macros
********************************************************************************
*/
#define ECUM_POSTBUILD_VARIANT_SUPPORT    (STD_OFF)
#define ECUM_CORE_ID_MASTER               (OS_CORE_ID_MASTER)

/* EcuM_WakeupSourceType */
#define ECUM_WKSOURCE_NONE                       (EcuM_WakeupSourceType)(0x00000000UL)
#define ECUM_WKSOURCE_ALL_SOURCES                (EcuM_WakeupSourceType)(~((EcuM_WakeupSourceType)0x00UL))
#define ECUM_WKSOURCE_POWER                      (EcuM_WakeupSourceType)(1UL)
#define ECUM_WKSOURCE_RESET                      (EcuM_WakeupSourceType)(2UL)
#define ECUM_WKSOURCE_INTERNAL_RESET             (EcuM_WakeupSourceType)(4UL)
#define ECUM_WKSOURCE_INTERNAL_WDG               (EcuM_WakeupSourceType)(8UL)
#define ECUM_WKSOURCE_EXTERNAL_WDG               (EcuM_WakeupSourceType)(16UL)   

#define CAN_MatrixDCDCV0120250305_VR82BV              (EcuM_WakeupSourceType)(32UL)  
#define FAW_PTCAN_MCU_V141_D3_sO0              (EcuM_WakeupSourceType)(64UL)  
#define FAW_MCD_MCU_Voxyrf              (EcuM_WakeupSourceType)(128UL)  
#define FAW__HVACDCDC2__V20DBC_OjcG_c              (EcuM_WakeupSourceType)(256UL)  
#define ECUM_DEFAULT_APP_MODE                                               (1U)
#define ECUM_DEFAULT_RESET_MODEREF                                          (0U)
#define ECUM_DEFAULT_SHUTDOWN_TARGET                                        (ECUM_STATE_OFF)
#define ECUM_DEFAULT_SLEEP_MODEREF                                          (0U)
#define ECUM_GODOWN_ALLOWED_USER                                            (0U)
#define ECUM_MAINFUNCTION_PERIOD                                            (5U)
#define ECUM_NORMAL_MCU_MODEREF                                             (0xFFU)
#define ECUM_NUMBER_OF_CORES                                                (3U)
#define ECUM_RESET_MODE_COUNT                                               (0U)
#define ECUM_SHUTDOWN_CAUSE_COUNT                                           (0U)
#define ECUM_SLEEP_MODE_COUNT                                               (0U)
#define ECUM_WAKEUP_SOURCE_LIST                                             (9U)
#define ECUM_CHECK_TIMEOUT                                                  (STD_OFF)
#define ECUM_DEV_ERROR_REPORT                                               (STD_OFF)
#define ECUM_INCLUDE_DET                                                    (STD_OFF)
#define ECUM_RESETLOOP_DETECTION                                            (STD_OFF)
#define ECUM_RESET_REASON_REF                                               (STD_OFF)
#define ECUM_SET_PROGRAMABLE_INTERRUPTS                                     (STD_OFF)
#define ECUM_VALIDATION_TIMEOUT                                             (STD_OFF)
#define ECUM_VERSIONINFO_API                                                (STD_ON)
#define ECUM_RESOURCE_CORE0 CORE0_TASK_OSRESOURCE0
#define ECUM_RESOURCE_CORE1 CORE1_TASK_OSRESOURCE1
#define ECUM_RESOURCE_CORE2 CORE2_TASK_OSRESOURCE2

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
#define ECUM_START_SEC_GLOBAL_VAR_NO_INIT
#include "EcuM_MemMap.h"

#if( ECUM_WAKEUP_SOURCE_LIST > 0U )
extern VAR(uint32, ECUM_VAR_NO_INIT) EcuM_ValidationTimeoutArray[ECUM_WAKEUP_SOURCE_LIST];
#endif

#define ECUM_STOP_SEC_GLOBAL_VAR_NO_INIT
#include "EcuM_MemMap.h"

/*
********************************************************************************
*    Global Constants
********************************************************************************
*/
#define ECUM_START_SEC_CONFIG_DATA
#include "EcuM_MemMap.h"

#if( ECUM_WAKEUP_SOURCE_LIST > 0U )
extern CONST(EcuM_WakeupSourceListType, ECUM_CONFIG_DATA) EcuM_WakeupSourceList[ECUM_WAKEUP_SOURCE_LIST];
#endif

#if( ECUM_GODOWN_ALLOWED_USER > 0U )
extern CONST(uint8, ECUM_CONFIG_DATA) EcuM_GoDownAllowedUser[ECUM_GODOWN_ALLOWED_USER];
#endif

#if( ECUM_SLEEP_MODE_COUNT > 0U )
extern CONST(EcuM_SleepModeType, ECUM_CONFIG_DATA) Ecum_SleepMode[ECUM_SLEEP_MODE_COUNT];
#endif

extern CONST(EcuM_ConfigParaType, ECUM_CONFIG_DATA) EcuM_ConfigParaData[ECUM_NUMBER_OF_CORES];

#define ECUM_STOP_SEC_CONFIG_DATA
#include "EcuM_MemMap.h"

/*
********************************************************************************
*    Global Functions
********************************************************************************
*/

#endif  /* ECUM_CFG_H_ */

