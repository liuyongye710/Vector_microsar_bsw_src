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
/*!        \file  Eth_30_Tc3xx_LL_TrafficHandling_Int.h
 *        \brief  Lower layer traffic handling private header file
 *
 *      \details  Private inline implementations of lower layer traffic handling part of component.
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

#if !defined (ETH_30_TC3XX_LL_TRAFFIC_HANDLING_INT_H)
# define ETH_30_TC3XX_LL_TRAFFIC_HANDLING_INT_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "Eth_30_Tc3xx_LL_TrafficHandling_Ifc_Int.h"
# include "Eth_30_Tc3xx_Lcfg.h"

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
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_TrafficHandling_TransformRegValToBandwidth
 **********************************************************************************************************************/
/*! \brief       Transforms the register representation of the bandwidth into value represented in Bit/s
 *  \details     -
 *  \param[in]   regValue     Bandwidth in register representation
 *  \param[in]   trcvSpeed    Link speed related to the respective Ethernet controller
 *  \return      Bandwidth in Bit/s
 *  \context     ANY
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \config      ETH_30_TC3XX_DYNAMIC_TRAFFIC_SHAPING_SUPPORT == STD_ON
 *  \pre         -
 **********************************************************************************************************************/
ETH_30_TC3XX_LL_TRAFFIC_HANDLING_LOCAL_INLINE FUNC(uint32, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_TrafficHandling_TransformRegValToBandwidth(
  uint32 regValue,
  uint32 trcvSpeed);

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_TrafficHandling_TransformBandwidthToRegVal
 **********************************************************************************************************************/
/*! \brief       Transforms the bandwidth represented in Bit/s into register value
 *  \details     -
 *  \param[in]   bandwidth    Bandwidth in Bit/s
 *  \param[in]   trcvSpeed    Link speed related to the respective Ethernet controller
 *  \return      Bandwidth in register representation
 *  \context     ANY
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \config      ETH_30_TC3XX_DYNAMIC_TRAFFIC_SHAPING_SUPPORT == STD_ON
 *  \note        Value bandwidth must not exceed the value of trcvSpeed.
 **********************************************************************************************************************/
ETH_30_TC3XX_LL_TRAFFIC_HANDLING_LOCAL_INLINE FUNC(uint32, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_TrafficHandling_TransformBandwidthToRegVal(
  uint32 bandwidth,
  uint32 trcvSpeed); /* PRQA S 0779 */ /* MD_MSR_Rule5.2 */

/**********************************************************************************************************************
 *  LOCAL FUNCTION DEFINITION
 *********************************************************************************************************************/

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_TrafficHandling_TransformRegValToBandwidth
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 **********************************************************************************************************************/
ETH_30_TC3XX_LL_TRAFFIC_HANDLING_LOCAL_INLINE FUNC(uint32, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_TrafficHandling_TransformRegValToBandwidth( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
  uint32 regValue,
  uint32 trcvSpeed)
{
  float64 bandwidth;
  float64 cycleTime = (float64)ETH_30_TC3XX_REG_MTL_TXQ_X_QUANTUM_WEIGHT_CYCLE_TIME_100MB;

  /* #10 Set cycle time according to the set transceiver speed (100MBit / 1GBit) */
  if (trcvSpeed == ETH_TRCV_SPEED_1000MBITS_IN_BITS)
  {
    cycleTime = (float64)ETH_30_TC3XX_REG_MTL_TXQ_X_QUANTUM_WEIGHT_CYCLE_TIME_1GB;
  }

  /* #20 Transform the register representation of the bandwidth to Bit/s */
  bandwidth = ((((float64)(regValue)) * ((float64)ETH_30_TC3XX_NSEC_PER_SEC))/
                                   (cycleTime * ((float64)ETH_30_TC3XX_REG_MTL_TXQ_X_QUANTUM_WEIGHT_CBS_SCALING)));

  return (uint32)bandwidth;
} /* Eth_30_Tc3xx_LL_TrafficHandling_TransformRegValToBandwidth() */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_TrafficHandling_TransformBandwidthToRegVal
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 **********************************************************************************************************************/
ETH_30_TC3XX_LL_TRAFFIC_HANDLING_LOCAL_INLINE FUNC(uint32, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_TrafficHandling_TransformBandwidthToRegVal( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
  uint32 bandwidth,
  uint32 trcvSpeed)
{
  float64  regValue;
  float64  regValueMax = (float64)ETH_30_TC3XX_REG_MTL_TXQ_X_QUANTUM_WEIGHT_PORT_TX_RATE_100MB;
  float64 cycleTime   = (float64)ETH_30_TC3XX_REG_MTL_TXQ_X_QUANTUM_WEIGHT_CYCLE_TIME_100MB;

  /* #10 Set maximal possible register value and cycle time according the the set transceiver speec */
  if (trcvSpeed == ETH_TRCV_SPEED_1000MBITS_IN_BITS)
  {
    regValueMax = (float64)ETH_30_TC3XX_REG_MTL_TXQ_X_QUANTUM_WEIGHT_PORT_TX_RATE_1GB;
    cycleTime   = (float64)ETH_30_TC3XX_REG_MTL_TXQ_X_QUANTUM_WEIGHT_CYCLE_TIME_1GB;
  }

  /* #20 Transform bandwidth fraction resulting from given bandwidth and link speed into idle slope */
  regValue = ((float64)bandwidth * cycleTime * (float64)ETH_30_TC3XX_REG_MTL_TXQ_X_QUANTUM_WEIGHT_CBS_SCALING)/
                                  ((float64)ETH_30_TC3XX_NSEC_PER_SEC);

  /* #30 If the calculated register value exceeds the maximal possible value, use the maximal possible value instead */
  if (regValue > regValueMax)
  {
    regValue = regValueMax;
  }

  return (uint32)regValue;
} /* Eth_30_Tc3xx_LL_TrafficHandling_TransformBandwidthToRegVal() */

/**********************************************************************************************************************
 *  GLOBAL FUNCTION DEFINITION
 *********************************************************************************************************************/

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_TrafficHandling_SetShaperBandwidth
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
ETH_30_TC3XX_LL_TRAFFIC_HANDLING_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_TrafficHandling_SetShaperBandwidth( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
  uint8  ctrlIdx,
  uint8  descrRingIdx,
  uint32 bandwidth)
{
  /* #10 Transform bandwidth into register representation */
  uint32 localBandwidth = Eth_30_Tc3xx_LL_TrafficHandling_TransformBandwidthToRegVal(bandwidth, Eth_30_Tc3xx_GetTrcvSpeedOfEthCtrl(ctrlIdx));

  /* #20 Check if shaper of mid 0 priority descriptor ring is addressed */
  if(descrRingIdx == ETH_30_TC3XX_LL_MID_0_PRIO_QUEUE_IDX)
  {
    /* #210 Adapt bandwidth of shaper related to mid 0 priority descriptor ring */
    Eth_30_Tc3xx_Reg_Write(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MTL_TXQ1_QUANTUM_WEIGHT, localBandwidth);
  }
  /* #30 Check if shaper of mid 1 priority descriptor ring is addressed */
  else if(descrRingIdx == ETH_30_TC3XX_LL_MID_1_PRIO_QUEUE_IDX)
  {
    /* 310 Adapt bandwidth of shaper related to mid 1 priority descriptor ring */
    Eth_30_Tc3xx_Reg_Write(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MTL_TXQ2_QUANTUM_WEIGHT, localBandwidth);
  }
  else
  {
    /* #40 Adapt bandwidth of shaper related to high priority descriptor ring */
    /* * (core ensures that only high priority descriptor ring is addressed here) */
    Eth_30_Tc3xx_Reg_Write(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MTL_TXQ3_QUANTUM_WEIGHT, localBandwidth);
  }
} /* Eth_30_Tc3xx_LL_TrafficHandling_SetShaperBandwidth() */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_TrafficHandling_GetCurrentShaperBandwidth
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
ETH_30_TC3XX_LL_TRAFFIC_HANDLING_LOCAL_INLINE FUNC(uint32, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_TrafficHandling_GetCurrentShaperBandwidth( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
  uint8 ctrlIdx,
  uint8 descrRingIdx)
{
  uint32 bandwidth;

  /* #10 Check if shaper of mid 0 priority descriptor ring is addressed */
  if(descrRingIdx == ETH_30_TC3XX_LL_MID_0_PRIO_QUEUE_IDX)
  {
    /* #110 Retrieve register value of shaper of mid priority descriptor ring */
    bandwidth = Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MTL_TXQ1_QUANTUM_WEIGHT) &
        ETH_30_TC3XX_REG_MTL_TXQ_X_QUANTUM_WEIGHT_ISCQW_MASK;
  }
  /* #20 Check if shaper of mid 1 priority descriptor ring is addressed */
  else if(descrRingIdx == ETH_30_TC3XX_LL_MID_1_PRIO_QUEUE_IDX)
  {
    /* #210 Retrieve register value of shaper of mid priority descriptor ring */
    bandwidth = Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MTL_TXQ2_QUANTUM_WEIGHT) &
        ETH_30_TC3XX_REG_MTL_TXQ_X_QUANTUM_WEIGHT_ISCQW_MASK;
  }
  else
  {
    /* #30 Retrieve register value of shaper of high priority descriptor ring */
    /* (core ensures that only high priority descriptor ring is addressed here) */
    bandwidth = Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MTL_TXQ3_QUANTUM_WEIGHT) &
        ETH_30_TC3XX_REG_MTL_TXQ_X_QUANTUM_WEIGHT_ISCQW_MASK;
  }

  /* #40 Transform register representation of bandwidth into Bit/s */
  bandwidth = Eth_30_Tc3xx_LL_TrafficHandling_TransformRegValToBandwidth(bandwidth, Eth_30_Tc3xx_GetTrcvSpeedOfEthCtrl(ctrlIdx));

  return bandwidth;
} /* Eth_30_Tc3xx_LL_TrafficHandling_GetCurrentShaperBandwidth() */

#  define ETH_30_TC3XX_STOP_SEC_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
# endif
#endif /* ETH_30_TC3XX_LL_TRAFFIC_HANDLING_INT_H */

/**********************************************************************************************************************
 *  END OF FILE: Eth_30_Tc3xx_LL_TrafficHandling_Int.h
 *********************************************************************************************************************/
