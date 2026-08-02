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
*   @file    ComStack_Cfg.h
*   @version 3.0.0
*
*   @brief   AUTOSAR 4.4.0 - Common Level Driver source file.
*   @details Autosar layer of MCAL driver.
*
*   @addtogroup Comstack_Cfg
*   @{
*/

#ifndef COMSTACK_CFG_H
#define COMSTACK_CFG_H

#ifdef __cplusplus
extern "C"{
#endif

/*==============================================INCLUDE FILES=======================================*/


/** 
* @brief   This type serve as a unique identifier of a PDU within a software module.
*          Allowed ranges: uint8 .. uint16
* @implements PduIdType_type
*/
typedef uint16       PduIdType;

/** 
* @brief   This type serve as length information of a PDU in bytes.
*          Allowed ranges: uint8 .. uint32 
* @implements PduLengthType_Type
*/
typedef uint32       PduLengthType; 

/*==================================================================================================
*                                 GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
*                                     FUNCTION PROTOTYPES
==================================================================================================*/


#ifdef __cplusplus
}
#endif
#endif 
