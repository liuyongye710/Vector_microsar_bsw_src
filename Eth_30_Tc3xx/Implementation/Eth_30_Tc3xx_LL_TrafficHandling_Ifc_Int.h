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
/*!        \file  Eth_30_Tc3xx_LL_TrafficHandling_Ifc_Int.h
 *        \brief  Lower layer traffic handling private header file
 *
 *      \details  Private declarations of lower layer traffic handling part of component
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

#if !defined (ETH_30_TC3XX_LL_TRAFFIC_HANDLING_IFC_INT_H)
# define ETH_30_TC3XX_LL_TRAFFIC_HANDLING_IFC_INT_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "Eth_30_Tc3xx_LL_Types_Int.h"
# include "Eth_30_Tc3xx_HwAccess_Int.h"

# if (ETH_30_TC3XX_DYNAMIC_TRAFFIC_SHAPING_SUPPORT == STD_ON)

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/

#  ifndef ETH_30_TC3XX_LL_TRAFFIC_HANDLING_LOCAL /* COV_ETH_COMPATIBILITY */
#   define ETH_30_TC3XX_LL_TRAFFIC_HANDLING_LOCAL                      static
#  endif

#  ifndef ETH_30_TC3XX_LL_TRAFFIC_HANDLING_LOCAL_INLINE /* COV_ETH_COMPATIBILITY */
#   define ETH_30_TC3XX_LL_TRAFFIC_HANDLING_LOCAL_INLINE               LOCAL_INLINE
#  endif

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

#  define ETH_30_TC3XX_START_SEC_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_TrafficHandling_SetShaperBandwidth
 **********************************************************************************************************************/
/*! \brief       Sets the bandwidth of the shaper related to the descriptor ring
 *  \details     -
 *  \param[in]   ctrlIdx            Identifier of the Ethernet controller
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]   descrRingIdx  Descriptor ring the shaper is related to
 *               [range: 0 <= descrRingIdx < Eth_30_Tc3xx_GetSizeOfTxDescr()]
 *  \param[in]   bandwidth     Bandwidth that shall be applied
 *  \context     ANY
 *  \synchronous TRUE
 *  \reentrant   TRUE for different descriptor ring
 *  \pre         -
 *  \config      ETH_30_TC3XX_DYNAMIC_TRAFFIC_SHAPING_SUPPORT == STD_ON
 **********************************************************************************************************************/
ETH_30_TC3XX_LL_TRAFFIC_HANDLING_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_TrafficHandling_SetShaperBandwidth(
  uint8  ctrlIdx,
  uint8  descrRingIdx,
  uint32 bandwidth); /* PRQA S 0779 */ /* MD_MSR_Rule5.2 */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_TrafficHandling_GetCurrentShaperBandwidth
 **********************************************************************************************************************/
/*! \brief       Retrieves the bandwidth of the shaper related to the descriptor ring
 *  \details     -
 *  \param[in]   ctrlIdx       Identifier of the Ethernet controller
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]   descrRingIdx  Descriptor ring the shaper is related to
 *               [range: 0 <= descrRingIdx < Eth_30_Tc3xx_GetSizeOfTxDescr()]
 *  \return      Current bandwidth of the shaper
 *  \context     ANY
 *  \synchronous TRUE
 *  \reentrant   TRUE
 *  \pre         -
 *  \config      ETH_30_TC3XX_DYNAMIC_TRAFFIC_SHAPING_SUPPORT == STD_ON
 **********************************************************************************************************************/
ETH_30_TC3XX_LL_TRAFFIC_HANDLING_LOCAL_INLINE FUNC(uint32, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_TrafficHandling_GetCurrentShaperBandwidth(
  uint8 ctrlIdx,
  uint8 descrRingIdx); /* PRQA S 0779 */ /* MD_MSR_Rule5.2 */

#  define ETH_30_TC3XX_STOP_SEC_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

# endif

#endif /* ETH_30_TC3XX_LL_TRAFFIC_HANDLING_IFC_INT_H */

/**********************************************************************************************************************
 *  END OF FILE: Eth_30_Tc3xx_LL_TrafficHandling_Ifc_Int.h
 *********************************************************************************************************************/
