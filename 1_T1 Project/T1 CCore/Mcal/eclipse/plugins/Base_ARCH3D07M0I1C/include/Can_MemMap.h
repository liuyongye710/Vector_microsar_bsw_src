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
*   @file    Can_MemMap.h
*   @version 1.0.1
*
*   @brief   AUTOSAR 4.4.0 - Common Level Driver source file.
*   @details Autosar layer of MCAL driver.
*
*   @addtogroup MCAL
*   @{
*/

#ifndef CAN_MEMMAP_H
#define CAN_MEMMAP_H

#ifdef __cplusplus
extern "C"{
#endif

/*==============================================INCLUDE FILES=======================================*/
#include "StandardTypes.h"

/**************************************** CAN *******************************/
#ifdef CAN_START_SEC_CONFIG_DATA_8

    #undef CAN_START_SEC_CONFIG_DATA_8

    #undef MEMMAP_ERROR
    
    
#endif

#ifdef CAN_STOP_SEC_CONFIG_DATA_8

    #undef CAN_STOP_SEC_CONFIG_DATA_8

    #undef MEMMAP_ERROR
#endif

#ifdef CAN_START_SEC_CONFIG_DATA_16

    #undef CAN_START_SEC_CONFIG_DATA_16

    #undef MEMMAP_ERROR
    
    
#endif

#ifdef CAN_STOP_SEC_CONFIG_DATA_16

    #undef CAN_STOP_SEC_CONFIG_DATA_16

    #undef MEMMAP_ERROR
    
    
#endif

#ifdef CAN_START_SEC_CONFIG_DATA_32

    #undef CAN_START_SEC_CONFIG_DATA_32

    #undef MEMMAP_ERROR
    
    
#endif

#ifdef CAN_STOP_SEC_CONFIG_DATA_32

    #undef CAN_STOP_SEC_CONFIG_DATA_32

    #undef MEMMAP_ERROR
    
    
#endif

#ifdef CAN_START_SEC_CONFIG_DATA_UNSPECIFIED

    #undef CAN_START_SEC_CONFIG_DATA_UNSPECIFIED

    #undef MEMMAP_ERROR
    
    
#endif

#ifdef CAN_STOP_SEC_CONFIG_DATA_UNSPECIFIED

    #undef CAN_STOP_SEC_CONFIG_DATA_UNSPECIFIED

    #undef MEMMAP_ERROR
    
    
#endif

#ifdef CAN_START_SEC_CONST_BOOLEAN

    #undef CAN_START_SEC_CONST_BOOLEAN

    #undef MEMMAP_ERROR
    

#endif

#ifdef CAN_STOP_SEC_CONST_BOOLEAN

    #undef CAN_STOP_SEC_CONST_BOOLEAN

    #undef MEMMAP_ERROR
    
    
#endif

#ifdef CAN_START_SEC_CONST_8

    #undef CAN_START_SEC_CONST_8

    #undef MEMMAP_ERROR
    

#endif

#ifdef CAN_STOP_SEC_CONST_8

    #undef CAN_STOP_SEC_CONST_8

    #undef MEMMAP_ERROR
    
    
#endif

#ifdef CAN_START_SEC_CONST_16

    #undef CAN_START_SEC_CONST_16

    #undef MEMMAP_ERROR
    

#endif

#ifdef CAN_STOP_SEC_CONST_16

    #undef CAN_STOP_SEC_CONST_16

    #undef MEMMAP_ERROR
    
    
#endif

#ifdef CAN_START_SEC_CONST_32

    #undef CAN_START_SEC_CONST_32

    #undef MEMMAP_ERROR
    

#endif

#ifdef CAN_STOP_SEC_CONST_32

    #undef CAN_STOP_SEC_CONST_32

    #undef MEMMAP_ERROR
    
    
#endif

#ifdef CAN_START_SEC_CONST_UNSPECIFIED

    #undef CAN_START_SEC_CONST_UNSPECIFIED

    #undef MEMMAP_ERROR
    

#endif

#ifdef CAN_STOP_SEC_CONST_UNSPECIFIED

    #undef CAN_STOP_SEC_CONST_UNSPECIFIED

    #undef MEMMAP_ERROR
    
    
#endif

#ifdef CAN_START_SEC_CODE

    #undef CAN_START_SEC_CODE

    #undef MEMMAP_ERROR
    

#endif

#ifdef CAN_STOP_SEC_CODE

    #undef CAN_STOP_SEC_CODE

    #undef MEMMAP_ERROR
    
    
#endif

#ifdef CAN_START_SEC_RAMCODE

    #undef CAN_START_SEC_RAMCODE

    #undef MEMMAP_ERROR  

#endif

#ifdef CAN_STOP_SEC_RAMCODE

    #undef CAN_STOP_SEC_RAMCODE

    #undef MEMMAP_ERROR
  
#endif

#ifdef CAN_START_SEC_VAR_NO_INIT_BOOLEAN

    #undef CAN_START_SEC_VAR_NO_INIT_BOOLEAN

    #undef MEMMAP_ERROR
    

#endif

#ifdef CAN_STOP_SEC_VAR_NO_INIT_BOOLEAN

    #undef CAN_STOP_SEC_VAR_NO_INIT_BOOLEAN

    #undef MEMMAP_ERROR
    
    
#endif

#ifdef CAN_START_SEC_VAR_NO_INIT_8

    #undef CAN_START_SEC_VAR_NO_INIT_8

    #undef MEMMAP_ERROR
    

#endif

#ifdef CAN_STOP_SEC_VAR_NO_INIT_8

    #undef CAN_STOP_SEC_VAR_NO_INIT_8

    #undef MEMMAP_ERROR
    
    
#endif

#ifdef CAN_START_SEC_VAR_NO_INIT_16

    #undef CAN_START_SEC_VAR_NO_INIT_16

    #undef MEMMAP_ERROR
    

#endif

#ifdef CAN_STOP_SEC_VAR_NO_INIT_16

    #undef CAN_STOP_SEC_VAR_NO_INIT_16

    #undef MEMMAP_ERROR
    
    
#endif

#ifdef CAN_START_SEC_VAR_NO_INIT_32

    #undef CAN_START_SEC_VAR_NO_INIT_32

    #undef MEMMAP_ERROR
    

#endif

#ifdef CAN_STOP_SEC_VAR_NO_INIT_32

    #undef CAN_STOP_SEC_VAR_NO_INIT_32

    #undef MEMMAP_ERROR
    
    
#endif

#ifdef CAN_START_SEC_VAR_NO_INIT_UNSPECIFIED

    #undef CAN_START_SEC_VAR_NO_INIT_UNSPECIFIED

    #undef MEMMAP_ERROR
    

#endif

#ifdef CAN_STOP_SEC_VAR_NO_INIT_UNSPECIFIED

    #undef CAN_STOP_SEC_VAR_NO_INIT_UNSPECIFIED

    #undef MEMMAP_ERROR
    
    
#endif

#ifdef CAN_START_SEC_VAR_INIT_BOOLEAN

    #undef CAN_START_SEC_VAR_INIT_BOOLEAN

    #undef MEMMAP_ERROR
    

#endif

#ifdef CAN_STOP_SEC_VAR_INIT_BOOLEAN

    #undef CAN_STOP_SEC_VAR_INIT_BOOLEAN

    #undef MEMMAP_ERROR
    
    
#endif

#ifdef CAN_START_SEC_VAR_INIT_8

    #undef CAN_START_SEC_VAR_INIT_8

    #undef MEMMAP_ERROR
    

#endif

#ifdef CAN_STOP_SEC_VAR_INIT_8

    #undef CAN_STOP_SEC_VAR_INIT_8

    #undef MEMMAP_ERROR
    
    
#endif

#ifdef CAN_START_SEC_VAR_INIT_16

    #undef CAN_START_SEC_VAR_INIT_16

    #undef MEMMAP_ERROR
    

#endif

#ifdef CAN_STOP_SEC_VAR_INIT_16

    #undef CAN_STOP_SEC_VAR_INIT_16

    #undef MEMMAP_ERROR
    
    
#endif

#ifdef CAN_START_SEC_VAR_INIT_32

    #undef CAN_START_SEC_VAR_INIT_32

    #undef MEMMAP_ERROR
    

#endif

#ifdef CAN_STOP_SEC_VAR_INIT_32

    #undef CAN_STOP_SEC_VAR_INIT_32

    #undef MEMMAP_ERROR
    
    
#endif

#ifdef CAN_START_SEC_VAR_INIT_UNSPECIFIED

    #undef CAN_START_SEC_VAR_INIT_UNSPECIFIED

    #undef MEMMAP_ERROR
    

#endif

#ifdef CAN_STOP_SEC_VAR_INIT_UNSPECIFIED

    #undef CAN_STOP_SEC_VAR_INIT_UNSPECIFIED

    #undef MEMMAP_ERROR
    
    
#endif

#ifdef __cplusplus
}
#endif
#endif 
