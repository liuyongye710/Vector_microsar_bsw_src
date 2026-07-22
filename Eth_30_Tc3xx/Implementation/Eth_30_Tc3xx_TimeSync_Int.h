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
/*!        \file  Eth_30_Tc3xx_TimeSync_Int.h
 *        \brief  Inline implementation of private Ethernet controller hardware timeer
 *
 *      \details  Provides access to the private hardware timer related inlined API of the Ethernet controller driver.
 *
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the version history in Eth_30_Tc3xx.h
 *
 *  FILE VERSION
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the newest version in Eth_30_Tc3xx.h
 *********************************************************************************************************************/

#if !defined (ETH_30_TC3XX_TIME_SYNC_INT_H)
# define ETH_30_TC3XX_TIME_SYNC_INT_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "Eth_30_Tc3xx_TimeSync_Ifc_Int.h"
# include "Eth_30_Tc3xx_LL_TimeSync_Int.h"
# include "Eth_30_Tc3xx_Lcfg.h"

# if (ETH_30_TC3XX_ENABLE_TIMESYNC == STD_ON)
/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
/* Timer constants */
#  define ETH_30_TC3XX_TIME_SYNC_NSEC_PER_SEC                          (1000000000uL)

/* IEEE1588 time stamp */
/*! Seconds that can be represented by IEEE1588 time stamp */
#  define ETH_30_TC3XX_TIME_IEEE1588_MAX_SECONDS                       (0x0000FFFFFFFFFFFFuLL)
/*! Nanoseconds that can be represented by IEEE1588 time stamp */
#  define ETH_30_TC3XX_TIME_IEEE1588_MAX_NANOSECONDS                   (ETH_30_TC3XX_TIME_SYNC_NSEC_PER_SEC)
/*! ETH Min/Max values for Eth_TimestampType and Eth_TimediffType */
/* 32 bit seconds */
#  define ETH_30_TC3XX_TIMESTAMP_MAX_SECONDS                           (0xFFFFFFFFuL)
#  define ETH_30_TC3XX_TIMESTAMP_SECONDS_64BIT_MASK                    (0x00000000FFFFFFFFuLL)
/* 16 bit seconds hi */
#  define ETH_30_TC3XX_TIMESTAMP_MAX_SECONDS_HI                        (0xFFFFu)
#  define ETH_30_TC3XX_TIMESTAMP_SECONDS_HI_64BIT_MASK                 (0x0000FFFF00000000uLL)
#  define ETH_30_TC3XX_TIMESTAMP_SECONDS_HI_64BIT_SHIFT                (32u)
/* 10^9 nanoseconds per second */
#  define ETH_30_TC3XX_TIMESTAMP_MAX_NANOSECONDS                       (ETH_30_TC3XX_TIME_SYNC_NSEC_PER_SEC)
/* 63 bit max timediff in nanoseconds */
#  define ETH_30_TC3XX_TIMEDIFF_MAX_NANOSECONDS                        (0x7FFFFFFFFFFFFFFFuLL)
/* Seconds portion of a timediff */
#  define ETH_30_TC3XX_TIMEDIFF_MAX_SECONDS                            \
                                                                       (ETH_30_TC3XX_TIMEDIFF_MAX_NANOSECONDS / ETH_30_TC3XX_TIMESTAMP_MAX_NANOSECONDS)

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

#  define ETH_30_TC3XX_START_SEC_CODE
#  include "MemMap.h" /* PRQA S 5087 1 */ /* MD_MSR_MemMap */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_TimeSync_Init
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_TIME_SYNC_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_TimeSync_Init(
  uint8 CtrlIdx)
{
  Std_ReturnType    retVal;
  Eth_TimeStampType timestamp;

  /* #10 Set hardware time to zero by invoking the hardware dependent interface set timer API */
  timestamp.seconds = 0u;
  timestamp.secondsHi = 0u;
  timestamp.nanoseconds = 0u;

  retVal = Eth_30_Tc3xx_LL_TimeSync_SetHwTime(CtrlIdx, &timestamp);                                                      /* SBSW_ETH_30_TC3XX_REF_OF_STACK_VAR */
  return retVal;
} /* Eth_30_Tc3xx_TimeSync_Init() */

#  define ETH_30_TC3XX_STOP_SEC_CODE
#  include "MemMap.h" /* PRQA S 5087 1 */ /* MD_MSR_MemMap */

# endif /* ETH_30_TC3XX_ENABLE_TIMESYNC */

#endif /* ETH_30_TC3XX_TIME_SYNC_INT_H */

/**********************************************************************************************************************
 *  END OF FILE: Eth_30_Tc3xx_TimeSync_Int.h
 *********************************************************************************************************************/
