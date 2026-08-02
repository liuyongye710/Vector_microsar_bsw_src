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
*   Autosar Revision     : 
*   Autosar Conf.Variant :
*   SW Version           : 
*   Build Version        : 
*  
*****************************************************************************/

/**
*   @file    Lin_MemMap.h
*   @version 1.0.1
*
*   @brief   AUTOSAR 4.4.0 - Common Level Driver source file.
*   @details Autosar layer of Lin MCAL driver.
*
*   @addtogroup MCAL
*   @{
*/

#ifdef __cplusplus
extern "C"{
#endif

/*==============================================INCLUDE FILES=======================================*/
#include "StandardTypes.h"
/*=====================================SOURCE FILE VERSION INFORMATION==============================*/

/*============================================FILE VERSION CHECKS===================================*/

/*=================================================Constants========================================*/

/*===========================================VARIABLE DECLARATIONS==================================*/

/*============================================DEFINES AND MACROS====================================*/
#ifdef LIN_START_SEC_CONFIG_DATA_8

    #undef LIN_START_SEC_CONFIG_DATA_8

    #undef MEMMAP_ERROR
    
    
#endif

#ifdef LIN_STOP_SEC_CONFIG_DATA_8

    #undef LIN_STOP_SEC_CONFIG_DATA_8

    #undef MEMMAP_ERROR
    
    
#endif

#ifdef LIN_START_SEC_CONFIG_DATA_16

    #undef LIN_START_SEC_CONFIG_DATA_16

    #undef MEMMAP_ERROR
    
    
#endif

#ifdef LIN_STOP_SEC_CONFIG_DATA_16

    #undef LIN_STOP_SEC_CONFIG_DATA_16

    #undef MEMMAP_ERROR
    
    
#endif

#ifdef LIN_START_SEC_CONFIG_DATA_32

    #undef LIN_START_SEC_CONFIG_DATA_32

    #undef MEMMAP_ERROR
    
    
#endif

#ifdef LIN_STOP_SEC_CONFIG_DATA_32

    #undef LIN_STOP_SEC_CONFIG_DATA_32

    #undef MEMMAP_ERROR
    
    
#endif

#ifdef LIN_START_SEC_CONFIG_DATA_UNSPECIFIED

    #undef LIN_START_SEC_CONFIG_DATA_UNSPECIFIED

    #undef MEMMAP_ERROR
    
    
#endif

#ifdef LIN_STOP_SEC_CONFIG_DATA_UNSPECIFIED

    #undef LIN_STOP_SEC_CONFIG_DATA_UNSPECIFIED

    #undef MEMMAP_ERROR
    
    
#endif

#ifdef LIN_START_SEC_CONST_BOOLEAN

    #undef LIN_START_SEC_CONST_BOOLEAN

    #undef MEMMAP_ERROR
    

#endif

#ifdef LIN_STOP_SEC_CONST_BOOLEAN

    #undef LIN_STOP_SEC_CONST_BOOLEAN

    #undef MEMMAP_ERROR
    
    
#endif

#ifdef LIN_START_SEC_CONST_8

    #undef LIN_START_SEC_CONST_8

    #undef MEMMAP_ERROR
    

#endif

#ifdef LIN_STOP_SEC_CONST_8

    #undef LIN_STOP_SEC_CONST_8

    #undef MEMMAP_ERROR
    
    
#endif

#ifdef LIN_START_SEC_CONST_16

    #undef LIN_START_SEC_CONST_16

    #undef MEMMAP_ERROR
    

#endif

#ifdef LIN_STOP_SEC_CONST_16

    #undef LIN_STOP_SEC_CONST_16

    #undef MEMMAP_ERROR
    
    
#endif

#ifdef LIN_START_SEC_CONST_32

    #undef LIN_START_SEC_CONST_32

    #undef MEMMAP_ERROR
    

#endif

#ifdef LIN_STOP_SEC_CONST_32

    #undef LIN_STOP_SEC_CONST_32

    #undef MEMMAP_ERROR
    
    
#endif

#ifdef LIN_START_SEC_CONST_UNSPECIFIED

    #undef LIN_START_SEC_CONST_UNSPECIFIED

    #undef MEMMAP_ERROR
    

#endif

#ifdef LIN_STOP_SEC_CONST_UNSPECIFIED

    #undef LIN_STOP_SEC_CONST_UNSPECIFIED

    #undef MEMMAP_ERROR
    
    
#endif

#ifdef LIN_START_SEC_CODE

    #undef LIN_START_SEC_CODE

    #undef MEMMAP_ERROR
    

#endif

#ifdef LIN_STOP_SEC_CODE

    #undef LIN_STOP_SEC_CODE

    #undef MEMMAP_ERROR
    
    
#endif

#ifdef LIN_START_SEC_RAMCODE

    #undef LIN_START_SEC_RAMCODE

    #undef MEMMAP_ERROR
    

    

#endif

#ifdef LIN_STOP_SEC_RAMCODE

    #undef LIN_STOP_SEC_RAMCODE

    #undef MEMMAP_ERROR
    
  
#endif

#ifdef LIN_START_SEC_VAR_NO_INIT_BOOLEAN

    #undef LIN_START_SEC_VAR_NO_INIT_BOOLEAN

    #undef MEMMAP_ERROR
    

#endif

#ifdef LIN_STOP_SEC_VAR_NO_INIT_BOOLEAN

    #undef LIN_STOP_SEC_VAR_NO_INIT_BOOLEAN

    #undef MEMMAP_ERROR
    
    
#endif

#ifdef LIN_START_SEC_VAR_NO_INIT_8

    #undef LIN_START_SEC_VAR_NO_INIT_8

    #undef MEMMAP_ERROR
    

#endif

#ifdef LIN_STOP_SEC_VAR_NO_INIT_8

    #undef LIN_STOP_SEC_VAR_NO_INIT_8

    #undef MEMMAP_ERROR
    
    
#endif

#ifdef LIN_START_SEC_VAR_NO_INIT_16

    #undef LIN_START_SEC_VAR_NO_INIT_16

    #undef MEMMAP_ERROR
    

#endif

#ifdef LIN_STOP_SEC_VAR_NO_INIT_16

    #undef LIN_STOP_SEC_VAR_NO_INIT_16

    #undef MEMMAP_ERROR
    
    
#endif

#ifdef LIN_START_SEC_VAR_NO_INIT_32

    #undef LIN_START_SEC_VAR_NO_INIT_32

    #undef MEMMAP_ERROR
    

#endif

#ifdef LIN_STOP_SEC_VAR_NO_INIT_32

    #undef LIN_STOP_SEC_VAR_NO_INIT_32

    #undef MEMMAP_ERROR
    
    
#endif

#ifdef LIN_START_SEC_VAR_NO_INIT_UNSPECIFIED

    #undef LIN_START_SEC_VAR_NO_INIT_UNSPECIFIED

    #undef MEMMAP_ERROR
    

#endif

#ifdef LIN_STOP_SEC_VAR_NO_INIT_UNSPECIFIED

    #undef LIN_STOP_SEC_VAR_NO_INIT_UNSPECIFIED

    #undef MEMMAP_ERROR
    
    
#endif

#ifdef LIN_START_SEC_VAR_INIT_BOOLEAN

    #undef LIN_START_SEC_VAR_INIT_BOOLEAN

    #undef MEMMAP_ERROR
    

#endif

#ifdef LIN_STOP_SEC_VAR_INIT_BOOLEAN

    #undef LIN_STOP_SEC_VAR_INIT_BOOLEAN

    #undef MEMMAP_ERROR
    
    
#endif

#ifdef LIN_START_SEC_VAR_INIT_8

    #undef LIN_START_SEC_VAR_INIT_8

    #undef MEMMAP_ERROR
    

#endif

#ifdef LIN_STOP_SEC_VAR_INIT_8

    #undef LIN_STOP_SEC_VAR_INIT_8

    #undef MEMMAP_ERROR
    
    
#endif

#ifdef LIN_START_SEC_VAR_INIT_16

    #undef LIN_START_SEC_VAR_INIT_16

    #undef MEMMAP_ERROR
    

#endif

#ifdef LIN_STOP_SEC_VAR_INIT_16

    #undef LIN_STOP_SEC_VAR_INIT_16

    #undef MEMMAP_ERROR
    
    
#endif

#ifdef LIN_START_SEC_VAR_INIT_32

    #undef LIN_START_SEC_VAR_INIT_32

    #undef MEMMAP_ERROR
    

#endif

#ifdef LIN_STOP_SEC_VAR_INIT_32

    #undef LIN_STOP_SEC_VAR_INIT_32

    #undef MEMMAP_ERROR
    
    
#endif

#ifdef LIN_START_SEC_VAR_INIT_UNSPECIFIED

    #undef LIN_START_SEC_VAR_INIT_UNSPECIFIED

    #undef MEMMAP_ERROR
    

#endif

#ifdef LIN_STOP_SEC_VAR_INIT_UNSPECIFIED

    #undef LIN_STOP_SEC_VAR_INIT_UNSPECIFIED

    #undef MEMMAP_ERROR
    
    
#endif

#ifdef __cplusplus
}
#endif

/** @} */
