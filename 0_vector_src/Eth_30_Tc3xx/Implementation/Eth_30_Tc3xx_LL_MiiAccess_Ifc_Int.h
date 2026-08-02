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
/*!        \file  Eth_30_Tc3xx_LL_MiiAccess_Ifc_Int.h
 *        \brief  Lower layer mii access private header file
 *
 *      \details  Private declarations of lower layer mii access part of component.
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
#if !defined (ETH_30_TC3XX_LL_MIIACCESS_IFC_INT_H)
# define ETH_30_TC3XX_LL_MIIACCESS_IFC_INT_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "Eth_30_Tc3xx_LL_Types_Int.h"
# include "Eth_30_Tc3xx_HwAccess_Int.h"

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
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

# define ETH_30_TC3XX_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_WriteMiiTrigger()
 *********************************************************************************************************************/
/*! \brief       Function for triggering a write operation on the MII Interface (MDIO line)
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller  for which the MII write operation shall be triggered
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]   trcvIdx          Index of transceiver for which the MII write operation shall be triggered
 *               [range: 0 <= trcvIdx < 32]
 *  \param[in]   regIdx           Index of register for which the MII write operation shall be triggered
 *               [range: 0 <= regIdx < 32]
 *  \param[in]   regVal           Register value that shall be written
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         ETH_30_TC3XX_EXCLUSIVE_AREA_MII must be entered.
 */
ETH_30_TC3XX_LL_MII_ACCESS_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_WriteMiiTrigger(
  uint8  ctrlIdx,
  uint8  trcvIdx,
  uint8  regIdx,
  uint16 regVal);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_ReadMiiTrigger()
 *********************************************************************************************************************/
/*! \brief       Function for triggering a read operation on the MII Interface (MDIO line)
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller for which the MII read operation shall be triggered
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]   trcvIdx          Index of transceiver for which the MII read operation shall be triggered
 *               [range: 0 <= trcvIdx < 32]
 *  \param[in]   regIdx           Index of register for which the MII read operation shall be triggered
 *               [range: 0 <= regIdx < 32]
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         ETH_30_TC3XX_EXCLUSIVE_AREA_MII must be entered.
 */
ETH_30_TC3XX_LL_MII_ACCESS_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_ReadMiiTrigger(
  uint8 ctrlIdx,
  uint8 trcvIdx,
  uint8 regIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_GetReadMiiResult()
 *********************************************************************************************************************/
/*! \brief       Function for retrieving the result of a read operation on the MII Interface (MDIO line)
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller for which the MII read operation result shall be retrieved
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[out]  regValPtr        Pointer to buffer where register value shall be stored
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         ETH_30_TC3XX_EXCLUSIVE_AREA_MII must be entered.
 */
ETH_30_TC3XX_LL_MII_ACCESS_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_GetReadMiiResult(
        uint8                                       ctrlIdx,
  P2VAR(uint16, AUTOMATIC, ETH_30_TC3XX_VAR_NOINIT) regValPtr);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_IsMiiOperationPending()
 *********************************************************************************************************************/
/*! \brief       Function for checking the completion of an operation on the MII Interface (MDIO line)
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller for which the MII operation completion shall be checked
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         ETH_30_TC3XX_EXCLUSIVE_AREA_MII must be entered.
 */
ETH_30_TC3XX_LL_MII_ACCESS_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_IsMiiOperationPending(
  uint8 ctrlIdx);


# define ETH_30_TC3XX_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* ETH_30_TC3XX_LL_MIIACCESS_IFC_INT_H */

/**********************************************************************************************************************
 *  END OF FILE: Eth_30_Tc3xx_LL_MiiAccess_Ifc_Int.h
 *********************************************************************************************************************/
