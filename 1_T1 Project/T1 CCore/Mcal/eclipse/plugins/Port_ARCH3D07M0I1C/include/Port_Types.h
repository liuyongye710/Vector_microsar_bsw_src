/**************************************************************************** 
* 
* Copyright (c) 2023  C*Core -   All Rights Reserved  
* 
* THIS SOFTWARE IS DISTRIBUTED "AS IS," AND ALL WARRANTIES ARE DISCLAIMED, 
* INCLUDING MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
* 
*   Project              : AUTOSAR 4.4.0 MCAL
*   Platform             : PowerPC e200
*   Peripheral           : PORT
*   Dependencies         : -
*
*   Autosar Version      : 4.4.0
*   Autosar Revision     : 
*   Autosar Conf.Variant :
*   SW Version           : 
*   Build Version        : 
*  
*****************************************************************************/

/**
*   @file    Port_Types.h
*   @version 3.0.0
*
*   @brief   AUTOSAR 4.4.0 - Common Level Driver source file.
*   @details Autosar layer of Port MCAL driver.
*
*   @addtogroup Port
*   @{
*/

#ifndef PORT_TYPES_H
#define PORT_TYPES_H

#ifdef __cplusplus
extern "C"
{
#endif

/* ==============================================INCLUDE FILES======================================= */
#include "Port_Register.h"
#include "Platform_Types.h"
#include "Mcal.h"

/* =====================================SOURCE FILE VERSION INFORMATION============================== */
#define PORT_H_SIUL2_VENDOR_ID_TYPES                     176
#define PORT_H_SIUL2_AR_REL_MAJ_VER_TY                   4
#define PORT_H_SIUL2_AR_REL_MIN_VER_TY                   4
#define PORT_H_SIUL2_AR_REL_REV_VER_TY                   0
#define PORT_H_SIUL2_SW_MAJOR_VER_TY                     3
#define PORT_H_SIUL2_SW_MINOR_VER_TY                     0
#define PORT_H_SIUL2_SW_PATCH_VER_TY                     0

/* ==================================FILE VERSION CHECKS============================================= */

#if (PORT_H_SIUL2_VENDOR_ID_TYPES != REGESYS_SIUL2_VENDOR_ID)
    #error "NON-MATCHED DATA : REGESYS_SIUL2_VENDOR_ID"
#endif

#if (PORT_H_SIUL2_AR_REL_MAJ_VER_TY != REGESYS_SIUL2_AR_REL_MAJOR_VER)
    #error "NON-MATCHED DATA : REGESYS_SIUL2_AR_REL_MAJOR_VER"
#endif

#if (PORT_H_SIUL2_AR_REL_MIN_VER_TY != REGESYS_SIUL2_AR_REL_MINOR_VER)
    #error "NON-MATCHED DATA : REGESYS_SIUL2_AR_REL_MINOR_VER"
#endif

#if (PORT_H_SIUL2_AR_REL_REV_VER_TY != REGESYS_SIUL2_AR_REL_REV_VER)
    #error "NON-MATCHED DATA : REGESYS_SIUL2_AR_REL_REV_VER"
#endif

#if (PORT_H_SIUL2_SW_MAJOR_VER_TY != REGESYS_SIUL2_SW_MAJOR_VERSION)
    #error "NON-MATCHED DATA : REGESYS_SIUL2_SW_MAJOR_VERSION"
#endif

#if (PORT_H_SIUL2_SW_MINOR_VER_TY != REGESYS_SIUL2_SW_MINOR_VERSION)
    #error "NON-MATCHED DATA : REGESYS_SIUL2_SW_MINOR_VERSION"
#endif

#if (PORT_H_SIUL2_SW_PATCH_VER_TY != REGESYS_SIUL2_SW_PATCH_VERSION)
    #error "NON-MATCHED DATA : REGESYS_SIUL2_SW_PATCH_VERSION"
#endif
/* =============================================CONSTANTS============================================ */

/**
* @brief Possible output status of a port pin.
*/
#define  PORT_PIN_LEVEL_LOW_U8         ((uint8)0)
#define  PORT_PIN_LEVEL_HIGH_U8        ((uint8)1)
#define  PORT_PIN_LEVEL_NOTCHANGED_U8  ((uint8)2)

/* =========================================DEFINES AND MACROS======================================= */


/* ==============================================ENUMS=============================================== */


/* =======================================STRUCTURES AND OTHER TYPEDEFS============================== */

/**
* @brief Data type for the symbolic name of a port pin.
* @details Shall cover all available port pins. The type should be chosen for the specific MCU
*         platform (best performance).
* @implements Port_PinType_typedef
*/
typedef uint32 Port_PinType;

/**
* @brief Possible directions of a port pin.
* @implements Port_PinDirectionType_enumeration 
*/
typedef enum
{
    PORT_PIN_IN = 0,        /**< @brief Sets port pin as input. */
    PORT_PIN_OUT = 1,           /**< @brief Sets port pin as output. */
} Port_PinDirectionType;

/**
* @brief Different port pin modes.
* @details A port pin shall be configurable with a number of port pin modes (type Port_PinModeType).
*        The type Port_PinModeType shall be used with the function call Port_SetPinMode
* @implements Port_PinModeType_typedef
*/
typedef uint8 Port_PinModeType;

/*
* @brief Data type for the number, mentioned in platform spec, of a port pin.
*        It is the same with the index of the PCR/MSCR register.
* @details Shall cover all available port pins.
* 
*/
typedef uint16 Port_InternalPinIdType;


/**
* @brief   A SIUL2 register value.
* @details A port register shall be written with a 32 bits value (type Port_RegValueType).
*          The type Port_RegValueType shall be used with the function call Port_SetPinMode
* 
*/
typedef uint32 Port_RegValueType;

/**
* @brief   Single pin configuration.
* @details This structure contains all configuration parameters of a single pin
*          identified by @p SIUPin.
* 
* @api
*/
typedef struct
{
    VAR(Port_InternalPinIdType, PORT_VAR) u16Port_SIUPin; /**< @brief Pin Defined on Part SIUx */
    VAR(uint32,                 PORT_VAR) u32Port_ODC;    /**< @brief Pad Output Driver Control Configuration */
    VAR(uint32,                 PORT_VAR) u32Port_MSCR;   /**< @brief Pad Control Register */
    VAR(uint8,                  PORT_VAR) u8Port_PDDir;   /**< @brief Pad Data Direction */
    VAR(uint8,                  PORT_VAR) u8Port_PDO;     /**< @brief Pad Data Output */
    VAR(boolean,                PORT_VAR) bPort_DC;       /**< @brief Direction changebility*/
    VAR(boolean,                PORT_VAR) bPort_MC;       /**< @brief Mode changebility*/
    VAR(boolean,                PORT_VAR) bPort_GPIO;     /**< @brief GPIO initial mode*/
} Port_Siul2_PinConfigType;

/**
* @brief   Default pin configuration.
* @details This structure contains all configuration parameters of a Default pin
*
* @api
*/
typedef struct
{
    VAR(uint32, PORT_VAR)   u32Port_MSCR;   /**< Pad Control Register */
    VAR(uint8,  PORT_VAR)   u8Port_PDO;    /**< Pad Data Output */
    VAR(uint8,  PORT_VAR)   u32Port_ISEL8; 
} Port_Siul2_UnUsedPinConfigType;

/**
* @brief Data type used for Pad Selection Multiplexed Configuration.
* @details This type should be chosen for the specific MCU platform (best performance).
*
* @api
*/
typedef uint32 Port_Siul2_PadSelConfigType;

/* ====================================GLOBAL VARIABLE DECLARATIONS================================== */


/* ========================================FUNCTION PROTOTYPES======================================= */


#ifdef __cplusplus
}
#endif
/* PORT_TYPES_H */
#endif
/** @} */
