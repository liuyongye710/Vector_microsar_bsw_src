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
/*!        \file  Eth_30_Tc3xx_MacHdl_Ifc_Int.h
 *        \brief  Declaration of private Ethernet controller mac handling implementation
 *
 *      \details  Provides access to the private mac handling related API of the Ethernet controller driver.
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
#if !defined (ETH_30_TC3XX_MACHDL_IFC_INT_H)
# define ETH_30_TC3XX_MACHDL_IFC_INT_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "Eth_30_Tc3xx_Types_Int.h"

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/

# ifndef ETH_30_TC3XX_MAC_HDL_LOCAL /* COV_ETH_COMPATIBILITY */
#  define ETH_30_TC3XX_MAC_HDL_LOCAL                                          static
# endif

# ifndef ETH_30_TC3XX_MAC_HDL_LOCAL_INLINE /* COV_ETH_COMPATIBILITY */
#  define ETH_30_TC3XX_MAC_HDL_LOCAL_INLINE                                   LOCAL_INLINE
# endif

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

# define ETH_30_TC3XX_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_IsBroadcast
 **********************************************************************************************************************/
/*! \brief      Checks whether the MAC address is the broadcast address
 *  \details    -
 *  \param[in]  macAddrPtr  MAC address that shall be checked
 *  \return     FALSE - MAC address isn't broadcast address
 *  \return     TRUE  - MAC address is broadcast address
 *  \context    ANY
 *  \reentrant  TRUE
 *  \pre        -
 */
ETH_30_TC3XX_MAC_HDL_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IsBroadcast(
  P2CONST(uint8, AUTOMATIC, AUTOMATIC) macAddrPtr);

# define ETH_30_TC3XX_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* ETH_30_TC3XX_MACHDL_IFC_INT_H */

/**********************************************************************************************************************
 *  END OF FILE: Eth_30_Tc3xx_MacHdl_Ifc_Int.h
 *********************************************************************************************************************/
