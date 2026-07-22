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
/*!        \file  Eth_30_Tc3xx_LL_MiiAccess_Int.h
 *        \brief  Lower layer mii access private header file
 *
 *      \details  Private inline implementations of lower layer mii access part of component.
 *
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the version history in Eth_30_Tc3xx_LL.h
 *
 *  FILE VERSION
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the newest version in Eth_30_Tc3xx_LL.h
 *********************************************************************************************************************/
#if !defined (ETH_30_TC3XX_LL_MIIACCESS_INT_H)
# define ETH_30_TC3XX_LL_MIIACCESS_INT_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "Eth_30_Tc3xx_LL_MiiAccess_Ifc_Int.h"
# include "Eth_30_Tc3xx_Lcfg.h"

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/

# ifndef ETH_30_TC3XX_LL_MII_ACCESS_LOCAL /* COV_ETH_COMPATIBILITY */
#  define ETH_30_TC3XX_LL_MII_ACCESS_LOCAL                                       static
# endif

# ifndef ETH_30_TC3XX_LL_MII_ACCESS_LOCAL_INLINE /* COV_ETH_COMPATIBILITY */
#  define ETH_30_TC3XX_LL_MII_ACCESS_LOCAL_INLINE                                LOCAL_INLINE
# endif

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 **********************************************************************************************************************/

# define ETH_30_TC3XX_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_WriteMiiTrigger
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_LL_MII_ACCESS_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_WriteMiiTrigger(
  uint8  ctrlIdx,
  uint8  trcvIdx,
  uint8  regIdx,
  uint16 regVal)
{
  /* #10 Prepare MII register value */
  uint32 ctrlRegVal = ETH_30_TC3XX_REG_MDIO_ADDR_GB | ETH_30_TC3XX_REG_MDIO_ADDR_WRITE |
  ((((uint32)regIdx) << ETH_30_TC3XX_REG_MDIO_ADDR_RDA_SHIFT) & ETH_30_TC3XX_REG_MDIO_ADDR_RDA_MASK) |
  ((((uint32)trcvIdx) << ETH_30_TC3XX_REG_MDIO_ADDR_PA_SHIFT) & ETH_30_TC3XX_REG_MDIO_ADDR_PA_MASK) |
  (((uint32)Eth_30_Tc3xx_GetCsrClockRangeOfEthCtrlTc3xx(ctrlIdx)) & ETH_30_TC3XX_REG_MDIO_ADDR_CR_MASK);

  /* #20 Trigger a write command with the prepared values */
  /* PRQA S 0306 2 */ /* MD_Eth_30_Tc3xx_0306 */
  Eth_30_Tc3xx_Reg_Write(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MDIO_DATA, (uint32)regVal);
  Eth_30_Tc3xx_Reg_Write(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MDIO_ADDR, ctrlRegVal);
} /* Eth_30_Tc3xx_LL_WriteMiiTrigger() */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_ReadMiiTrigger
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_LL_MII_ACCESS_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_ReadMiiTrigger(
  uint8 ctrlIdx,
  uint8 trcvIdx,
  uint8 regIdx)
{
  /* #10 Prepare MII register value */
  uint32 ctrlRegVal = ETH_30_TC3XX_REG_MDIO_ADDR_GB | ETH_30_TC3XX_REG_MDIO_ADDR_READ |
  ((((uint32)regIdx) << ETH_30_TC3XX_REG_MDIO_ADDR_RDA_SHIFT) & ETH_30_TC3XX_REG_MDIO_ADDR_RDA_MASK) |
  ((((uint32)trcvIdx) << ETH_30_TC3XX_REG_MDIO_ADDR_PA_SHIFT) & ETH_30_TC3XX_REG_MDIO_ADDR_PA_MASK) |
  (((uint32)Eth_30_Tc3xx_GetCsrClockRangeOfEthCtrlTc3xx(ctrlIdx)) & ETH_30_TC3XX_REG_MDIO_ADDR_CR_MASK);

  /* #20 Trigger a read operation */
  /* PRQA S 0306 1 */ /* MD_Eth_30_Tc3xx_0306 */
  Eth_30_Tc3xx_Reg_Write(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MDIO_ADDR, ctrlRegVal);
} /* Eth_30_Tc3xx_LL_ReadMiiTrigger() */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_GetReadMiiResult
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_LL_MII_ACCESS_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_GetReadMiiResult(
        uint8                                       ctrlIdx,
  P2VAR(uint16, AUTOMATIC, ETH_30_TC3XX_VAR_NOINIT) regValPtr)
{
  /* #10 Read back the result of a Mii read operation */
  *regValPtr = (uint16)(Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MDIO_DATA) &     /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
                                                       ETH_30_TC3XX_REG_MDIO_DATA_MASK);
} /* Eth_30_Tc3xx_LL_GetReadMiiResult() */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_IsMiiOperationPending
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_LL_MII_ACCESS_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_IsMiiOperationPending(
  uint8 ctrlIdx)
{
  /* #10 Return status of MII interface busy bit */
  return Eth_30_Tc3xx_Reg_IsBitMaskSet(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MDIO_ADDR, ETH_30_TC3XX_REG_MDIO_ADDR_GB);
} /* Eth_30_Tc3xx_LL_IsMiiOperationPending() */

# define ETH_30_TC3XX_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* ETH_30_TC3XX_LL_MIIACCESS_INT_H */

/**********************************************************************************************************************
 *  END OF FILE: Eth_30_Tc3xx_LL_MiiAccess_Int.h
 *********************************************************************************************************************/
