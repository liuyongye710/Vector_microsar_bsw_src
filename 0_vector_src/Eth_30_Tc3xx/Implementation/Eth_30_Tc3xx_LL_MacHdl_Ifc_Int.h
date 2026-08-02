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
/*!        \file  Eth_30_Tc3xx_LL_MacHdl_Ifc_Int.h
 *        \brief  Lower layer private mac handling header file
 *
 *      \details  Private declarations of lower layer mac handling part of component.
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
#if !defined (ETH_30_TC3XX_LL_MACHDL_IFC_INT_H)
# define ETH_30_TC3XX_LL_MACHDL_IFC_INT_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "Eth_30_Tc3xx_LL_Types_Int.h"
# include "Eth_30_Tc3xx_HwAccess_Int.h"

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/

# ifndef ETH_30_TC3XX_LL_MAC_HDL_LOCAL /* COV_ETH_COMPATIBILITY */
#  define ETH_30_TC3XX_LL_MAC_HDL_LOCAL                                       static
# endif

# ifndef ETH_30_TC3XX_LL_MAC_HDL_LOCAL_INLINE /* COV_ETH_COMPATIBILITY */
#  define ETH_30_TC3XX_LL_MAC_HDL_LOCAL_INLINE                                LOCAL_INLINE
# endif

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

# define ETH_30_TC3XX_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_WriteMacAddressToRegister()
 *********************************************************************************************************************/
/*! \brief       Function for writing the configured MAC address to the hardware register
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller for which the MAC address shall be set
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]   macAddrPtr       Pointer to physical address to be set
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 */
ETH_30_TC3XX_LL_MAC_HDL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_WriteMacAddressToRegister(
          uint8                                      ctrlIdx,
  P2CONST(uint8, AUTOMATIC, ETH_30_TC3XX_VAR_NOINIT) macAddrPtr);

# if (ETH_30_TC3XX_ENABLE_UPDATE_PHYS_ADDR_FILTER == STD_ON)
/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_EnablePromiscuousMode()
 *********************************************************************************************************************/
/*! \brief       Function for enabling the promiscuous mode
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller for which promiscuous mode shall be enabled
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 *  \config      ETH_30_TC3XX_ENABLE_UPDATE_PHYS_ADDR_FILTER == STD_ON
 */
ETH_30_TC3XX_LL_MAC_HDL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_EnablePromiscuousMode(
  uint8 ctrlIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_DisablePromiscuousMode()
 *********************************************************************************************************************/
/*! \brief       Function for disabling the promiscuous mode
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller for which promiscuous mode shall be disabled
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 *  \config      ETH_30_TC3XX_ENABLE_UPDATE_PHYS_ADDR_FILTER == STD_ON
 */
ETH_30_TC3XX_LL_MAC_HDL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_DisablePromiscuousMode(
  uint8 ctrlIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_CloseAllMulticastFilters()
 *********************************************************************************************************************/
/*! \brief       Function for closing all multicast filters
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller for which all multicast filters shall be closed
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 *  \config     ETH_30_TC3XX_ENABLE_UPDATE_PHYS_ADDR_FILTER == STD_ON
 */
ETH_30_TC3XX_LL_MAC_HDL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_CloseAllMulticastFilters(
  uint8 ctrlIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_SetMulticastFilteringMode()
 *********************************************************************************************************************/
/*! \brief       Function for enabling a certain multicast filter mode
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller for which the multicast filter mode shall be set
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 *  \config      ETH_30_TC3XX_ENABLE_UPDATE_PHYS_ADDR_FILTER == STD_ON
 */
ETH_30_TC3XX_LL_MAC_HDL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_SetMulticastFilteringMode(
  uint8 ctrlIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_SetMulticastFilterBucketRegister()
 *********************************************************************************************************************/
/*! \brief       Function for writing the multicast filter bucket register
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller for which the multicast bucket register shall be set
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]   bucketMask       Mask which shall be set
 *  \param[in]   isUpperReg       Selects upper or lower register
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 *  \config      ETH_30_TC3XX_ENABLE_UPDATE_PHYS_ADDR_FILTER == STD_ON
 */
ETH_30_TC3XX_LL_MAC_HDL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_SetMulticastFilterBucketRegister(
  uint8  ctrlIdx,
  uint32 bucketMask,
  boolean isUpperReg);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_ResetMulticastFilterBucketRegister()
 *********************************************************************************************************************/
/*! \brief       Function writing resetting bits in the multicast filter bucket register
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller for which the multicast bucket register shall be set
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]   bucketMask       Mask which shall be reset
 *  \param[in]   isUpperReg       Selects upper or lower register
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 *  \config      ETH_30_TC3XX_ENABLE_UPDATE_PHYS_ADDR_FILTER == STD_ON
 */
ETH_30_TC3XX_LL_MAC_HDL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_ResetMulticastFilterBucketRegister(
  uint8  ctrlIdx,
  uint32 bucketMask,
  boolean isUpperReg);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_CalculateMulticastFilterRegisterHash()
 *********************************************************************************************************************/
/*! \brief       Function for calculating a multicast filter hash value
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller for which the multicast bucket register shall be set
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]   macAddrPtr       Pointer to the physical address for which a hash shall be calculated
 *  \param[out]  hashPtr          Pointer to the variable which contains the calculated hash
 *  \param[out]  isUpperRegPtr    Pointer to the variable which contains the decision which filter register shall be
 *                                used
 *  \param[out]  bucketMaskPtr    Pointer to the variable which contains the mask for the filter register
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 *  \config      ETH_30_TC3XX_ENABLE_UPDATE_PHYS_ADDR_FILTER == STD_ON
 */
ETH_30_TC3XX_LL_MAC_HDL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_CalculateMulticastFilterRegisterHash(
          uint8                                        ctrlIdx,
  P2CONST(uint8,   AUTOMATIC, ETH_30_TC3XX_VAR_NOINIT) macAddrPtr,
    P2VAR(uint8,   AUTOMATIC, ETH_30_TC3XX_VAR_NOINIT) hashPtr,
    P2VAR(boolean, AUTOMATIC, ETH_30_TC3XX_VAR_NOINIT) isUpperRegPtr,
    P2VAR(uint32,  AUTOMATIC, ETH_30_TC3XX_VAR_NOINIT) bucketMaskPtr);
# endif /* ETH_30_TC3XX_ENABLE_UPDATE_PHYS_ADDR_FILTER */

# define ETH_30_TC3XX_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* ETH_30_TC3XX_LL_MACHDL_IFC_INT_H */

/**********************************************************************************************************************
 *  END OF FILE: Eth_30_Tc3xx_LL_MacHdl_Ifc_Int.h
 *********************************************************************************************************************/
