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
/*!        \file  Eth_30_Vtt_LL_TrafficHandling.h
 *        \brief  Lower layer part of the traffic handling sub-module of the driver
 *
 *      \details  Contains the derivative specific implementation of the traffic handling sub-module of the
 *                Core Ethernet driver.
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

/* PRQA S 0779 EOF */ /* MD_MSR_5.1_779 */

#if !defined (ETH_30_VTT_LL_TRAFFIC_HANDLING_H)
# define ETH_30_VTT_LL_TRAFFIC_HANDLING_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "Eth_30_Vtt_Int.h"

# if (ETH_30_VTT_DYNAMIC_TRAFFIC_SHAPING_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
#  if !defined (ETH_30_VTT_LL_TRAFFICH_HANDLING_LOCAL) /* COV_ETH_COMPATIBILITY */
#   define ETH_30_VTT_LL_TRAFFICH_HANDLING_LOCAL                      LOCAL
#  endif /* ETH_30_VTT_LL_TRAFFICH_HANDLING_LOCAL */

#  if !defined (ETH_30_VTT_LL_TRAFFIC_HANDLING_LOCAL_INLINE) /* COV_ETH_COMPATIBILITY */
#   define ETH_30_VTT_LL_TRAFFIC_HANDLING_LOCAL_INLINE                LOCAL_INLINE
#  endif /* ETH_30_VTT_LL_TRAFFIC_HANDLING_LOCAL_INLINE */

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

#  define ETH_30_VTT_START_SEC_CODE
#  include "MemMap.h" /* PRQA S 5087 1 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION DEFINITION
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/***********************************************************************************************************************
 *  Eth_30_Vtt_LL_TrafficHandling_SetShaperBandwidth
 **********************************************************************************************************************/
/*! \brief       Sets the bandwidth of the shaper related to the descriptor ring
 *  \details     -
 *  \param[in]   ctrlIdx            Identifier of the Ethernet controller
 *               [range: 0 <= ctrlIdx < Eth_30_Vtt_GetSizeOfEthCtrl()]
 *  \param[in]   descrRingIdx  Descriptor ring the shaper is related to
 *               [range: 0 <= descrRingIdx < Eth_30_Vtt_GetSizeOfTxDescr()]
 *  \param[in]   bandwidth     Bandwidth that shall be applied
 *  \context     ANY
 *  \synchronous TRUE
 *  \reentrant   TRUE for different descriptor ring
 *  \pre         -
 **********************************************************************************************************************/
ETH_30_VTT_LL_TRAFFIC_HANDLING_LOCAL_INLINE FUNC(void, ETH_30_VTT_CODE) Eth_30_Vtt_LL_TrafficHandling_SetShaperBandwidth(
  uint8  ctrlIdx,
  uint8  descrRingIdx,
  uint32 bandwidth); /* PRQA S 0779 */ /* MD_MSR_5.1_779 */

/***********************************************************************************************************************
 *  Eth_30_Vtt_LL_TrafficHandling_GetCurrentShaperBandwidth
 **********************************************************************************************************************/
/*! \brief       Retrieves the bandwidth of the shaper related to the descriptor ring
 *  \details     -
 *  \param[in]   ctrlIdx       Identifier of the Ethernet controller
 *               [range: 0 <= ctrlIdx < Eth_30_Vtt_GetSizeOfEthCtrl()]
 *  \param[in]   descrRingIdx  Descriptor ring the shaper is related to
 *               [range: 0 <= descrRingIdx < Eth_30_Vtt_GetSizeOfTxDescr()]
 *  \return      Current bandwidth of the shaper
 *  \context     ANY
 *  \synchronous TRUE
 *  \reentrant   TRUE
 *  \pre         -
 **********************************************************************************************************************/
ETH_30_VTT_LL_TRAFFIC_HANDLING_LOCAL_INLINE FUNC(uint32, ETH_30_VTT_CODE) Eth_30_Vtt_LL_TrafficHandling_GetCurrentShaperBandwidth(
  uint8 ctrlIdx,
  uint8 descrRingIdx); /* PRQA S 0779 */ /* MD_MSR_5.1_779 */

/**********************************************************************************************************************
 *  GLOBAL FUNCTION DEFINITION
 *********************************************************************************************************************/

#  ifndef ETH_30_VTT_UNIT_TEST /* COV_ETH_TEST_SUITE_UNIT_TESTS */

/***********************************************************************************************************************
 *  Eth_30_Vtt_LL_TrafficHandling_SetShaperBandwidth
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 **********************************************************************************************************************/
ETH_30_VTT_LL_TRAFFIC_HANDLING_LOCAL_INLINE FUNC(void, ETH_30_VTT_CODE) Eth_30_Vtt_LL_TrafficHandling_SetShaperBandwidth( /* PRQA S 3219 */ /* MD_Eth_30_Vtt_3219 */
  uint8  ctrlIdx,
  uint8  descrRingIdx,
  uint32 bandwidth)
{
  /* #10 Nothing to do here */
  ETH_30_VTT_DUMMY_STATEMENT(ctrlIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */
  ETH_30_VTT_DUMMY_STATEMENT(descrRingIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */
  ETH_30_VTT_DUMMY_STATEMENT(bandwidth); /* PRQA S 3112 */ /* MD_MSR_14.2 */

} /* Eth_30_Vtt_LL_TrafficHandling_SetShaperBandwidth() */

/***********************************************************************************************************************
 *  Eth_30_Vtt_LL_TrafficHandling_GetCurrentShaperBandwidth
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 **********************************************************************************************************************/
ETH_30_VTT_LL_TRAFFIC_HANDLING_LOCAL_INLINE FUNC(uint32, ETH_30_VTT_CODE) Eth_30_Vtt_LL_TrafficHandling_GetCurrentShaperBandwidth( /* PRQA S 3219 */ /* MD_Eth_30_Vtt_3219 */
  uint8 ctrlIdx,
  uint8 descrRingIdx)
{
  uint32 bandwidth;

  /* #10 Nothing to do here */
  ETH_30_VTT_DUMMY_STATEMENT(ctrlIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */
  ETH_30_VTT_DUMMY_STATEMENT(descrRingIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */

  bandwidth = 0;

  return bandwidth;
} /* Eth_30_Vtt_LL_TrafficHandling_GetCurrentShaperBandwidth() */

#  endif /* ETH_30_VTT_UNIT_TEST */

#  define ETH_30_VTT_STOP_SEC_CODE
#  include "MemMap.h" /* PRQA S 5087 1 */ /* MD_MSR_19.1 */

# endif /* ETH_30_VTT_DYNAMIC_TRAFFIC_SHAPING_SUPPORT */

#endif /* ETH_30_VTT_LL_TRAFFIC_HANDLING_H */

/**********************************************************************************************************************
 *  END OF FILE: Eth_30_Vtt_LL_TrafficHandling.h
 *********************************************************************************************************************/
