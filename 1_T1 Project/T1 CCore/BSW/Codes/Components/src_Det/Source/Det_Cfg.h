/*
********************************************************************************
*
* File name: Det_Cfg.h
*
* Copyright 2018-2024 Neusoft Reach Corporation. All rights reserved.
*
********************************************************************************
*
* History
*-------------------------------------------------------------------------------
********************************************************************************
* Version: 1.0
* Author/Date: yong.zhang/2019.6.18
* Change: New created.
* Cause: New
********************************************************************************
* Version: 3.0
* Author/Date: FangT/2020.11.05
* Change: Modify the function name according to the AUTOSAR specification.
* Cause: Optimization
********************************************************************************
* Version: 3.1
* Author/Date : FangT/2020.11.06
* Change: Modify the function name according to the AUTOSAR specification.
* Cause: Optimization
********************************************************************************
* Version: 3.2
* Author/Date: ZengJX/2024.07.18
* Change: 1.Modify copyright information.
*         2.Fix Det memmap issue.
* Cause: Optimization
********************************************************************************
*/
#ifndef DET_CFG_H_
#define DET_CFG_H_

/*
********************************************************************************
*    Includes
********************************************************************************
*/
#include "Std_Types.h"

/*
********************************************************************************
*    Global Macros
********************************************************************************
*/
#define USE_DET                                  (STD_ON)
#define DET_FORWARD_TO_DLT                       (STD_OFF)
#define DET_VERSION_INFO_API                     (STD_OFF)
#define DET_ERR_HOOK_ENABLE                      (STD_OFF)
#define DET_RUNTIME_ERR_ENABLE                   (STD_OFF)
#define DET_TRANSIENT_FAULT_ENABLE               (STD_OFF)
#define DET_RUNTIME_ERR_CALLOUT_NUM              (1)
#define DET_TRANSIENT_FAULT_CALLOUT_NUM          (1)

/*
********************************************************************************
*    Global Types
********************************************************************************
*/
typedef Std_ReturnType (* Det_CalloutTableType)(uint16 ModuleId, uint8 InstanceId, uint8 ApiId, uint8 ErrorId);

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
#define DET_START_SEC_CONFIG_DATA
#include "Det_MemMap.h"
#define DET_STOP_SEC_CONFIG_DATA
#include "Det_MemMap.h"

/*
********************************************************************************
*    Global Functions
********************************************************************************
*/
#define DET_START_SEC_CODE
#include "Det_MemMap.h"
#define DET_STOP_SEC_CODE
#include "Det_MemMap.h"

#endif  /* DET_CFG_H_ */

