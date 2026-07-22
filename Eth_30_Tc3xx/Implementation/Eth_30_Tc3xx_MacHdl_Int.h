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
/*!        \file  Eth_30_Tc3xx_MacHdl_Int.h
 *        \brief  Inline implementation of private Ethernet controller mac handling part
 *
 *      \details  Provides access to the private mac handling related inlined API of the Ethernet controller driver.
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
#if !defined (ETH_30_TC3XX_MACHDL_INT_H)
# define ETH_30_TC3XX_MACHDL_INT_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "Eth_30_Tc3xx_Types_Int.h"
# include "Eth_30_Tc3xx_MacHdl_Ifc_Int.h"
# include "Eth_30_Tc3xx_LL_MacHdl_Int.h"
# include "Eth_30_Tc3xx_Lcfg.h"

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/

# define ETH_30_TC3XX_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_IsBroadcast
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 */
ETH_30_TC3XX_MAC_HDL_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IsBroadcast( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
  P2CONST(uint8, AUTOMATIC, AUTOMATIC) macAddrPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8_least addrIdx;
  boolean     isBroadcast = TRUE;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all six bytes of the given MAC address */
  for (addrIdx = 0; addrIdx < ETH_PHYS_ADDR_LEN_BYTE; addrIdx++)
  {
    /* #110 The currently checked byte is not equal to 0xFF */
    if (macAddrPtr[(uint8)addrIdx] != 0xFFu)
    {
      /* #1110 Return that the given MAC-address is no broadcast address */
      isBroadcast = FALSE;
      break;
    }
  }
  return isBroadcast;
} /* Eth_30_Tc3xx_IsBroadcast() */

# define ETH_30_TC3XX_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* ETH_30_TC3XX_MACHDL_INT_H */

/**********************************************************************************************************************
 *  END OF FILE: Eth_30_Tc3xx_MacHdl_Int.h
 *********************************************************************************************************************/
