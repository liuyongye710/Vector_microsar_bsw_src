/**************************************************************************** 
* 
* Copyright (c) 2022  C*Core -   All Rights Reserved  
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
*   @file    Platform_Types.h
*   @version 3.0.0
*
*   @brief   AUTOSAR 4.4.0 - Common Level Driver source file.
*   @details Autosar layer of MCAL driver.
*
*   @addtogroup PLATFORM
*   @{
*/

#ifndef PLATFORM_TYPES_H
#define PLATFORM_TYPES_H

#ifdef __cplusplus
extern "C"{
#endif

#define PLATFORM_VENDOR_ID                      176
#define PLATFORM_AR_RELEASE_MAJOR_VERSION       4
#define PLATFORM_AR_RELEASE_MINOR_VERSION       4
#define PLATFORM_AR_RELEASE_REVISION_VERSION    0
#define PLATFORM_SW_MAJOR_VERSION               3
#define PLATFORM_SW_MINOR_VERSION               0
#define PLATFORM_SW_PATCH_VERSION               0

/*==================================================================================================
*                                      FILE VERSION CHECKS
==================================================================================================*/

/*==================================================================================================
*                                           CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                       DEFINES AND MACROS
==================================================================================================*/
/**
* @brief          8bit Type Processor
* @implements     CPU_TYPE_enumeration
*/
#define CPU_TYPE_8 8

/**
* @brief          16bit Type Processor
* @implements     CPU_TYPE_enumeration
*/
#define CPU_TYPE_16 16

/**
* @brief          32bit Type Processor
* @implements     CPU_TYPE_enumeration
*/
#define CPU_TYPE_32 32

/**
* @brief          64bit Type Processor
* @implements     CPU_TYPE_enumeration
*/
#define CPU_TYPE_64 64

/**
* @brief          MSB First Processor
* @implements     CPU_BIT_ORDER_enumeration
*/
#define MSB_FIRST 0

/**
* @brief          LSB First Processor
* @implements     CPU_BIT_ORDER_enumeration
*/
#define LSB_FIRST 1

/**
* @brief          HIGH_BYTE_FIRST Processor
* @implements     CPU_BYTE_ORDER_enumeration
*/
#define HIGH_BYTE_FIRST 0

/** 
* @brief          LOW_BYTE_FIRST Processor
* @implements     CPU_BYTE_ORDER_enumeration
*/
#define LOW_BYTE_FIRST 1

/** 
* @brief          Processor type
* @implements     CPU_TYPE_enumeration
*/
#define CPU_TYPE (CPU_TYPE_32)  
/** 
* @brief          Bit order on register level.
* @implements     CPU_BIT_ORDER_enumeration
*/
#define CPU_BIT_ORDER (MSB_FIRST)

/** 
* @brief The byte order on memory level shall be indicated in the platform types header file using 
*        the symbol CPU_BYTE_ORDER.
* @implements     CPU_BYTE_ORDER_enumeration
*/
#define CPU_BYTE_ORDER (HIGH_BYTE_FIRST)

#ifndef TRUE
    /** 
    * @brief Boolean true value
    * @implements TRUE_FALSE_enumeration
    */
    #define TRUE 1
#endif
#ifndef FALSE
    /** 
    * @brief Boolean false value
    * @implements TRUE_FALSE_enumeration
    */
    #define FALSE 0
#endif

/*==================================================================================================
                                             ENUMS
==================================================================================================*/

/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/
#if (CPU_TYPE == CPU_TYPE_64)

typedef unsigned char boolean;

typedef unsigned char uint8;

typedef unsigned short uint16;

typedef short int16;

typedef unsigned int uint32;

typedef unsigned long long uint64;

typedef signed char sint8;

typedef signed short sint16;

typedef signed int sint32;

typedef signed long long sint64;

typedef unsigned int uint8_least;

typedef unsigned int uint16_least;

typedef unsigned int uint32_least;

typedef signed int sint8_least;

typedef signed int sint16_least;

typedef signed int sint32_least;

typedef float float32;

typedef double float64;

#elif (CPU_TYPE == CPU_TYPE_32)

typedef unsigned char boolean;

typedef unsigned char uint8;

typedef unsigned short uint16;

typedef short int16;

typedef unsigned long uint32;

typedef unsigned long long uint64;

typedef signed char sint8;

typedef signed short sint16;

typedef signed long sint32;

typedef signed long long sint64;

typedef unsigned long uint8_least;

typedef unsigned long uint16_least;

typedef unsigned long uint32_least;

typedef signed long sint8_least;

typedef signed long sint16_least;

typedef signed long sint32_least;

typedef float float32;

typedef double float64;

#elif (CPU_TYPE == CPU_TYPE_16)

typedef unsigned char boolean;

typedef unsigned char uint8;

typedef unsigned short uint16;

typedef short int16;

typedef unsigned long uint32;

typedef unsigned long long uint64;

typedef signed char sint8;

typedef signed short sint16;

typedef signed long sint32;

typedef signed long long sint64;

typedef unsigned long uint8_least;

typedef unsigned long uint16_least;

typedef unsigned long uint32_least;

typedef signed long sint8_least;

typedef signed long sint16_least;

typedef signed long sint32_least;

typedef float float32;

typedef double float64;
#endif

/*==================================================================================================
*                                 GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
*                                    FUNCTION PROTOTYPES
==================================================================================================*/

#ifdef __cplusplus
}
#endif
#endif 
