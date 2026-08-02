
/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2021 by Vector Informatik GmbH.                                              All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *           File:  Lin_Types.h
 *      Component:  AUTOSAR LIN Driver
 *         Module:  DrvLin_VttCanoeAsr / DrvLin_CanoeemuAsr
 *      Generator:  DrvLin_VttCanoeAsr / DrvLin_CanoeemuAsr
 *
 *  Target system:  Canoe
 *       Compiler:  Ansi

 *    Derivatives:  VTT/EMU
 *
 *    Description:  Type definitions of the AUTOSAR LIN Driver
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *********************************************************************************************************************/

#if !defined (LIN_TYPES_H)
# define LIN_TYPES_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
# include "ComStack_Types.h"
# include "Lin_GeneralTypes.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
# define LIN_TPS_MAJOR_VERSION 11u
# define LIN_TPS_MINOR_VERSION 2u
# define LIN_TPS_PATCH_VERSION 1u

# define Lin_ChannelDataBufferSize             8u

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
typedef volatile struct Lin_RegisterStructTag   /* !< Hardware register layout */
{
  uint8 dummy;
} Lin_RegisterStruct;


/**********************************************************************************************************************
 *  TYPE AND DEFINE DEFINITIONS FOR INTERNAL USE IN LIN DRIVER
 *********************************************************************************************************************/
/*! Pointer to hardware register base address of channel. */
typedef Lin_RegisterStruct *Lin_RegisterStructPtr;

typedef uint8 Lin_DataBufferType[Lin_ChannelDataBufferSize];

typedef uint8 Lin_ChannelConfigIdxOfChannelHwType;

#endif /* LIN_TYPES_H */

/**********************************************************************************************************************
 *  END OF FILE: Lin_Types.h
 *********************************************************************************************************************/
