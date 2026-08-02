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
/*!        \file  Eth_30_Tc3xx_LL_Statistics_Int.h
 *        \brief  Lower layer statistics private header file
 *
 *      \details  Private inline implementations of lower layer statistics part of component.
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
#if !defined (ETH_30_TC3XX_LL_STATISTICS_INT_H)
# define ETH_30_TC3XX_LL_STATISTICS_INT_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "Eth_30_Tc3xx_LL_Statistics_Ifc_Int.h"
# include "Eth_30_Tc3xx_LL_Statistics.h"
# include "Eth_30_Tc3xx_Lcfg.h"

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/

/*! Maximal value of Rx FIFO overflow counter register */
# define ETH_30_TC3XX_RX_FIFO_OVERFLOW_PACKETS_COUNT_MAX              (65535u)

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 **********************************************************************************************************************/

# define ETH_30_TC3XX_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_GetMaxCounterOffset
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_LL_STATISTICS_LOCAL_INLINE FUNC(uint16, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_GetMaxCounterOffset(
  uint8 ctrlIdx)
{
  ETH_30_TC3XX_DUMMY_STATEMENT(ctrlIdx); /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */ /*lint !e438 */

  /* #10 Return max counter offset */
  return ETH_30_TC3XX_MMC_COUNTER_MAX_OFFSET;
} /* Eth_30_Tc3xx_LL_GetMaxCounterOffset() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_GetCounterValue
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_LL_STATISTICS_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_GetCounterValue(
        uint8                                       ctrlIdx,
  Eth_30_Tc3xx_RegOffsetType                        counterOffset,
  P2VAR(uint32, AUTOMATIC, ETH_30_TC3XX_VAR_NOINIT) counterValPtr)
{
  /* #10 Get statistics register with related offset */
  Eth_30_Tc3xx_RegOffsetType regOffset = ETH_30_TC3XX_MMC_COUNTER_BASE_OFFSET + counterOffset;
  (*counterValPtr) = Eth_30_Tc3xx_Reg_Read(ctrlIdx, regOffset);                                     /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */

  return E_OK;
} /* Eth_30_Tc3xx_LL_GetCounterValue() */

# if (ETH_30_TC3XX_ENABLE_GET_ETHER_STATS_API == STD_ON)
/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_GetRxStats
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_LL_STATISTICS_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_GetRxStats(
        uint8                                                ctrlIdx,
  P2VAR(Eth_RxStatsType, AUTOMATIC, ETH_30_TC3XX_VAR_NOINIT) rxStatsPtr)
{
  /* #10 Read the reception statistics counter values */
  rxStatsPtr->RxStatsDropEvents =                                                           /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
      (Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MMC_RX_FIFO_OVFL)
     + Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MMC_RX_CRC_ERROR)
     + Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MMC_RX_ALIGN)
     + Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MMC_RX_RUNT)
     + Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MMC_RX_JABBER)
     + Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MMC_RX_UNDERSIZE_G)
     + Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MMC_RX_OVERSIZE_G));
  rxStatsPtr->RxStatsOctets =                                                               /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
       Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MMC_RX_OCTETS_GB);
  rxStatsPtr->RxStatsPkts =                                                                 /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
       Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MMC_RX_FRAMES);
  rxStatsPtr->RxStatsBroadcastPkts =                                                        /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
       Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MMC_RX_BROADCAST_FRAMES);
  rxStatsPtr->RxStatsMulticastPkts =                                                        /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
       Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MMC_RX_MULTICAST_FRAMES);
  rxStatsPtr->RxStatsCrcAlignErrors =                                                       /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
      (Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MMC_RX_CRC_ERROR)
     + Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MMC_RX_ALIGN));
  rxStatsPtr->RxStatsUndersizePkts =                                                        /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
       Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MMC_RX_UNDERSIZE_G);
  rxStatsPtr->RxStatsOversizePkts =                                                         /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
       Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MMC_RX_OVERSIZE_G);
  rxStatsPtr->RxStatsFragments =                                                            /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
       Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MMC_RX_RUNT);
  rxStatsPtr->RxStatsJabbers =                                                              /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
       Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MMC_RX_JABBER);
  rxStatsPtr->RxStatsPkts64Octets =                                                         /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
       Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MMC_RX_FRAMES_64);
  rxStatsPtr->RxStatsPkts65to127Octets =                                                    /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
       Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MMC_RX_FRAMES_64_TO_127);
  rxStatsPtr->RxStatsPkts128to255Octets =                                                   /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
       Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MMC_RX_FRAMES_128_TO_255);
  rxStatsPtr->RxStatsPkts256to511Octets =                                                   /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
       Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MMC_RX_FRAMES_256_TO_511);
  rxStatsPtr->RxStatsPkts512to1023Octets =                                                  /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
       Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MMC_RX_FRAMES_512_TO_1023);
  rxStatsPtr->RxStatsPkts1024to1518Octets =                                                 /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
       Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MMC_RX_FRAMES_1024_TO_MAX);
  rxStatsPtr->RxUnicastFrames =                                                             /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
       Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MMC_RX_UNICAST_G_FRAMES);
  rxStatsPtr->RxStatsCollisions =                                                           /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
      (Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MMC_TX_SINGLE_COL)
     + Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MMC_TX_MULTI_COL)
     + Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MMC_TX_LATE_COL)
     + Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MMC_TX_EXC_COL));

  return E_OK;
} /* Eth_30_Tc3xx_LL_GetRxStats() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_GetTxStats
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_LL_STATISTICS_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_GetTxStats(
        uint8                                                ctrlIdx,
  P2VAR(Eth_TxStatsType, AUTOMATIC, ETH_30_TC3XX_VAR_NOINIT) txStatsPtr)
{
  /* #10 Read the transmission statistics counter values */
  txStatsPtr->TxNumberOfOctets = Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MMC_TX_OCTETS_GB);        /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
  txStatsPtr->TxNUcastPkts    = (Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MMC_TX_BROADCASTS_GB)     /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
                               + Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MMC_TX_MULTICASTS_GB));
  txStatsPtr->TxUniCastPkts    = Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MMC_TX_UNICASTS_GB);      /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */

  return E_OK;
} /* Eth_30_Tc3xx_LL_GetTxStats() */
# endif /* ETH_30_TC3XX_ENABLE_GET_ETHER_STATS_API */

# if (ETH_30_TC3XX_GET_AND_RESET_MEASUREMENT_DATA_API == STD_ON)
/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_GetDropInsuffRxBuffHwCounter
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_LL_STATISTICS_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_GetDropInsuffRxBuffHwCounter(
        uint8                                                                       ctrlIdx,
  P2VAR(Eth_30_Tc3xx_DropInsuffRxBuffOfEthMeasDataCounterType, AUTOMATIC, AUTOMATIC) readCtrValuePtr,
  P2VAR(boolean,                                              AUTOMATIC, AUTOMATIC) isHwCtrResetOnReadPtr)
{
  Eth_30_Tc3xx_DropInsuffRxBuffOfEthMeasDataCounterType rxDropCounterValue;

  *isHwCtrResetOnReadPtr = FALSE;                                                       /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */

  /* #10 Retrieve the hardware counter of Rx frame drops due to insufficient Rx buffers */
  rxDropCounterValue = Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MMC_RX_FIFO_OVFL);

  /* #20 Check for the wrap around condition */
  if(rxDropCounterValue < Eth_30_Tc3xx_GetDropInsuffRxBuffResetOfEthMeasDataCounterReset(ctrlIdx))
  {
    /* #210 Calculate the Rx frame drop counter wrt the reset value considerig the wrap arount correction */
    (*readCtrValuePtr) = (ETH_30_TC3XX_RX_FIFO_OVERFLOW_PACKETS_COUNT_MAX - Eth_30_Tc3xx_GetDropInsuffRxBuffResetOfEthMeasDataCounterReset(ctrlIdx))    /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
                              + rxDropCounterValue;
  }
  else
  {
    /* #220 Calculate the Rx frame drop counter wrt the reset value */
    (*readCtrValuePtr) = (rxDropCounterValue - Eth_30_Tc3xx_GetDropInsuffRxBuffResetOfEthMeasDataCounterReset(ctrlIdx));  /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
  }
  return E_OK;
} /* Eth_30_Tc3xx_LL_GetDropInsuffRxBuffHwCounter() */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_ResetDropInsuffRxBuffHwCounter
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_LL_STATISTICS_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_ResetDropInsuffRxBuffHwCounter(
  uint8 ctrlIdx)
{
  /* #10 Only Read is allowed and Reset is not supported by the Tc3xx. Thus, the current counter value is stored in a
   *     reset value variable and E_OK is send */
  Eth_30_Tc3xx_SetDropInsuffRxBuffResetOfEthMeasDataCounterReset(ctrlIdx, Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MMC_RX_FIFO_OVFL));  /* SBSW_ETH_30_TC3XX_LOCAL_PTR_ACCESS_CSL_PARAM_IDX_CSL01 */
  return E_OK;
} /* Eth_30_Tc3xx_LL_ResetDropInsuffRxBuffHwCounter() */
# endif /* ETH_30_TC3XX_GET_AND_RESET_MEASUREMENT_DATA_API */

# define ETH_30_TC3XX_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* ETH_30_TC3XX_LL_STATISTICS_INT_H */

/**********************************************************************************************************************
 *  END OF FILE: Eth_30_Tc3xx_LL_Statistics_Int.h
 *********************************************************************************************************************/
