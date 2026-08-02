/**************************************************************************** 
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
*   Autosar Revision     : 
*   Autosar Conf.Variant :
*   SW Version           : 
*   Build Version        : 
*
*****************************************************************************/

/**
*   @file    eTPU_Cfg.h
*   @version 1.0.1
*
*   @brief   AUTOSAR 4.4.0 - Common Level Driver source file.
*   @details Autosar layer of eTPU MCAL driver.
*
*   @addtogroup eTPU
*   @{
*/


#ifndef ETPU_CFG_H_
#define ETPU_CFG_H_


#include "Compiler.h"
#include "StandardTypes.h"


#define ETPU_VENDOR_ID                       176
#define ETPU_MODULE_ID                       251
#define ETPU_AR_REL_MAJOR_VER                4
#define ETPU_AR_REL_MINOR_VER                4
#define ETPU_AR_REL_REV_VER                  0
#define ETPU_SW_MAJOR_VER                    1
#define ETPU_SW_MINOR_VER                    0
#define ETPU_SW_PATCH_VER                    1

#define ETPU_PRECOMPILE_SUPPORT        (STD_OFF)

#define ETPU_INSTANCE_NUM                    2

#define ETPU_INLINE                    LOCAL_INLINE

#define ETPU_INSTANCE_A_B_SUPPORT            (STD_ON)

#define ETPU_INSTANCE_C_SUPPORT              (STD_ON)

#endif /* ETPU_CFG_H_ */
