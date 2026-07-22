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
/*!        \file  Eth_30_Tc3xx_LL_MacHdl_Int.h
 *        \brief  Lower layer private mac handling header file
 *
 *      \details  Private inline implementations of lower layer mac handling part of component.
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
#if !defined (ETH_30_TC3XX_LL_MACHDL_INT_H)
# define ETH_30_TC3XX_LL_MACHDL_INT_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "Eth_30_Tc3xx_LL_MacHdl_Ifc_Int.h"
# include "Eth_30_Tc3xx_Lcfg.h"

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 **********************************************************************************************************************/

# define ETH_30_TC3XX_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_WriteMacAddressToRegister
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_LL_MAC_HDL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_WriteMacAddressToRegister(
  uint8                                ctrlIdx,
  P2CONST(uint8, AUTOMATIC, ETH_30_TC3XX_VAR_NOINIT) macAddrPtr)
{
  /* #10 Write Mac address to registers */
  Eth_30_Tc3xx_Reg_Write(ctrlIdx, ETH_30_TC3XX_REG_OFFS_ADDR0_HIGH,
    (uint32)((uint32)macAddrPtr[5] <<  8u) | ((uint32)macAddrPtr[4]));
  Eth_30_Tc3xx_Reg_Write(ctrlIdx,  ETH_30_TC3XX_REG_OFFS_ADDR0_LOW,
    (uint32)((uint32)macAddrPtr[3] << 24u) |
            ((uint32)macAddrPtr[2] << 16u) |
            ((uint32)macAddrPtr[1] <<  8u) | ((uint32)macAddrPtr[0]));
} /* Eth_30_Tc3xx_LL_WriteMacAddressToRegister() */

# if (ETH_30_TC3XX_ENABLE_UPDATE_PHYS_ADDR_FILTER == STD_ON)
/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_EnablePromiscuousMode
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_LL_MAC_HDL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_EnablePromiscuousMode(
  uint8 ctrlIdx)
{
  /* #10 Enable promiscuous mode */
  Eth_30_Tc3xx_Reg_SetBitMask(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MAC_PACKET_FILTER, ETH_30_TC3XX_REG_PACKET_FILTER_PR);
} /* Eth_30_Tc3xx_LL_EnablePromiscuousMode() */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_DisablePromiscuousMode
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_LL_MAC_HDL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_DisablePromiscuousMode(
  uint8 ctrlIdx)
{
  /* #10 Disable promiscuous mode */
  Eth_30_Tc3xx_Reg_ClearBitMask(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MAC_PACKET_FILTER, ETH_30_TC3XX_REG_PACKET_FILTER_PR);
} /* Eth_30_Tc3xx_LL_DisablePromiscuousMode() */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_CloseAllMulticastFilters
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_LL_MAC_HDL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_CloseAllMulticastFilters(
  uint8 ctrlIdx)
{
  /* #10 Nothing to do here */
  ETH_30_TC3XX_DUMMY_STATEMENT(ctrlIdx); /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
} /* Eth_30_Tc3xx_LL_CloseAllMulticastFilters() */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_SetMulticastFilteringMode
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_LL_MAC_HDL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_SetMulticastFilteringMode(
  uint8 ctrlIdx)
{
  /* #10 Nothing to do here */
  ETH_30_TC3XX_DUMMY_STATEMENT(ctrlIdx); /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
} /* Eth_30_Tc3xx_LL_SetMulticastFilteringMode() */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_SetMulticastFilterBucketRegister
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_LL_MAC_HDL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_SetMulticastFilterBucketRegister(
  uint8  ctrlIdx,
  uint32 bucketMask,
  boolean isUpperReg)
{
  /* #10 Nothing to do here */
  ETH_30_TC3XX_DUMMY_STATEMENT(ctrlIdx); /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
  ETH_30_TC3XX_DUMMY_STATEMENT(bucketMask); /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
  ETH_30_TC3XX_DUMMY_STATEMENT(isUpperReg); /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
} /* Eth_30_Tc3xx_LL_SetUpperMulticastFilterBucketRegister() */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_ResetMulticastFilterBucketRegister
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_LL_MAC_HDL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_ResetMulticastFilterBucketRegister(
  uint8  ctrlIdx,
  uint32 bucketMask,
  boolean isUpperReg)
{
  /* #10 Nothing to do here */
  ETH_30_TC3XX_DUMMY_STATEMENT(ctrlIdx); /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
  ETH_30_TC3XX_DUMMY_STATEMENT(bucketMask); /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
  ETH_30_TC3XX_DUMMY_STATEMENT(isUpperReg); /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
} /* Eth_30_Tc3xx_LL_ResetUpperMulticastFilterBucketRegister() */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_CalculateMulticastFilterRegisterHash
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_LL_MAC_HDL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_CalculateMulticastFilterRegisterHash(
          uint8                                        ctrlIdx,
  P2CONST(uint8,   AUTOMATIC, ETH_30_TC3XX_VAR_NOINIT) macAddrPtr,
    P2VAR(uint8,   AUTOMATIC, ETH_30_TC3XX_VAR_NOINIT) hashPtr,
    P2VAR(boolean, AUTOMATIC, ETH_30_TC3XX_VAR_NOINIT) isUpperRegPtr,
    P2VAR(uint32,  AUTOMATIC, ETH_30_TC3XX_VAR_NOINIT) bucketMaskPtr)
{
  /* #10 Return dummy values */
  *hashPtr = 0u;                                                    /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
  *bucketMaskPtr = 0u;                                              /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
  *isUpperRegPtr = FALSE;                                           /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */

  ETH_30_TC3XX_DUMMY_STATEMENT(ctrlIdx); /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
  ETH_30_TC3XX_DUMMY_STATEMENT(macAddrPtr); /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
} /* Eth_30_Tc3xx_LL_CalculateMulticastFilterRegisterHash() */
# endif /* ETH_30_TC3XX_ENABLE_UPDATE_PHYS_ADDR_FILTER */

# define ETH_30_TC3XX_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* ETH_30_TC3XX_LL_MACHDL_INT_H */

/**********************************************************************************************************************
 *  END OF FILE: Eth_30_Tc3xx_LL_MacHdl_Int.h
 *********************************************************************************************************************/
