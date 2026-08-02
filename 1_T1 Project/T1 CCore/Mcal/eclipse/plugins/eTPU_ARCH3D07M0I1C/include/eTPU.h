/**************************************************************************** 
*
* Copyright (c) 2023  C*Core -   All Rights Reserved  
* 
* THIS SOFTWARE IS DISTRIBUTED "AS IS," AND ALL WARRANTIES ARE DISCLAIMED, 
* INCLUDING MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
* 
*   Project              : AUTOSAR 4.4.0 MCAL
*   Platform             : PowerPC e200
*   Peripheral           : 
*   Dependencies         : 
*
*   Autosar Version      : 4.4.0
*   Autosar Revision     : ASR_REL_4_4_REV_0000
*   Autosar Conf.Variant :
*   SW Version           : 
*   Build Version        : 
*
*****************************************************************************/

/**
*   @file    eTPU.h
*   @version 1.0.1
*
*   @brief   AUTOSAR 4.4.0 - Common Level Driver source file.
*   @details Autosar layer of eTPU MCAL driver.
*
*   @addtogroup eTPU
*   @{
*/

#ifndef ETPU_H_
#define ETPU_H_
#include "eTPU_LLDrivers.h"

#define ETPU_INSTANCE                        0
#define ETPU_E_PARAM_DATA                    4

extern VAR(eTPU_ConfigType, ETPU_VAR) etpuConfig[ETPU_INSTANCE_NUM];

FUNC(void, ETPU_CODE) eTPU_Init(P2CONST(eTPU_ConfigType, ETPU_CONST, ETPU_APPL_CONST) ConfigPtr);

#endif /* ETPU_H_ */
