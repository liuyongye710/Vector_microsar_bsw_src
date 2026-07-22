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
 *  -----------------------------------------------------------------------------------------------------------------*/
/*!        \file  Eth_30_Vtt_LL_Types.h
 *        \brief  Public header file of Ethernet driver for data type access
 *
 *      \details  Contains data type declaration that shall be accessible in a public manner.
 *
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the version history in Eth_30_Vtt_LL.h
 *
 *  FILE VERSION
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the newest version in Eth_30_Vtt_LL.h
 *********************************************************************************************************************/

#if !defined (ETH_30_VTT_LL_TYPES_H)
# define ETH_30_VTT_LL_TYPES_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
# include "Platform_Types.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
/*! \brief Ethernet Rx descriptor structure. */
typedef struct {
  Eth_DataType* DataPtr;
  uint32 nanoseconds;
  uint32 seconds;
  uint16 secondsHi;
  uint16 AllowedPacketSize;
  uint16 ReceivedPacketSize;
  uint8 LastElement;
  boolean OwnedByDriver;
  boolean isTimeStampingEnabled;
} Eth_30_Vtt_RxDescriptorType;

/*! \brief Ethernet Tx descriptor structure. */
typedef struct {
  uint32 nanoseconds;
  uint32 seconds;
  uint16 secondsHi;
  uint8 OwnedByDriver;
  uint8 LastElement;
  boolean isTimeStampingEnabled;
} Eth_30_Vtt_TxDescriptorType;

#endif /* ETH_30_VTT_LL_TYPES_H */

/**********************************************************************************************************************
 *  END OF FILE: Eth_30_Vtt_LL_Types.h
 *********************************************************************************************************************/
