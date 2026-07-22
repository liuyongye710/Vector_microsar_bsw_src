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
/*!        \file  Eth_30_Tc3xx_Statistics.c
 *        \brief  Statistics implementation of ethernet controller
 *
 *      \details  Statistics part of the Ethernet controller driver implementation.
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

/*lint -e438 */ /* Suppress ID438 because Config pointer only used in Post-Build Variant */
/*lint -e506 */ /* Suppress ID506 due to MD_MSR_14.1 */
/*lint -e537 */ /* Suppress ID537 due to MD_MSR_MemMap */
/*lint -e451 */ /* Suppress ID451 because MemMap.h cannot use a include guard */

#define ETH_30_TC3XX_STATISTICS_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Eth_30_Tc3xx_Statistics.h"
#include "Eth_30_Tc3xx_Statistics_Int.h"
#include "Eth_30_Tc3xx_Int.h"

#if (ETH_30_TC3XX_DEV_ERROR_DETECT == STD_ON)
# include "Det.h"
#endif /* ETH_30_TC3XX_DEV_ERROR_DETECT */

#define ETH_30_TC3XX_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  LOCAL DATA
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_Internal_GetCounterState
 **********************************************************************************************************************/
/*! \brief       Retrieves the value of an Ethernet statistics counter
 *  \details     Function retrieves the value of an Ethernet statistics counter by addressing the counter with the help
 *               of an offset into the Ethernet statistics counter register space.
 *  \param[in]   ctrlIdx    Identifier of the Ethernet controller
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]   ctrOffs    Offset of the counter into the Ethernet statistics counter register space
 *  \param[out]  ctrValPtr  Buffer to store the counter value
 *  \return      E_NOT_OK - Counter retrieval failed
 *  \return      E_OK - Counter successfully retrieved
 *  \context     ANY
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         Ethernet controller is initialized
 */
ETH_30_TC3XX_STATISTICS_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Internal_GetCounterState(
        uint8                         ctrlIdx,
        uint16                        ctrOffs,
  P2VAR(uint32, AUTOMATIC, AUTOMATIC) ctrValPtr);

#if (ETH_30_TC3XX_ENABLE_GET_ETHER_STATS_API == STD_ON)
/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Internal_GetRxStats()
 *********************************************************************************************************************/
/*! \brief       Returns list of reception statistics
 *  \details     Function returns the list of reception statistics from IETF RFC1213.
 *  \param[in]   ctrlIdx     Identifier of the Ethernet controller
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[out]  rxStatsPtr  List of read statistics values for reception
 *  \return      E_OK:     Success
 *               E_NOT_OK: RX-statistics could not be obtained
 *  \context     ANY
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 */
ETH_30_TC3XX_STATISTICS_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Internal_GetRxStats(
        uint8                                  ctrlIdx,
  P2VAR(Eth_RxStatsType, AUTOMATIC, AUTOMATIC) rxStatsPtr);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Internal_GetTxStats()
 *********************************************************************************************************************/
/*! \brief       Returns list of transmission statistics
 *  \details     Function returns the list of transmission statistics from IETF RFC1213.
 *  \param[in]   ctrlIdx     Identifier of the Ethernet controller
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[out]  txStatsPtr  List of read statistics values for transmission
 *  \return      E_OK:     Success
 *               E_NOT_OK: TX-statistics could not be obtained
 *  \context     ANY
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 */
ETH_30_TC3XX_STATISTICS_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Internal_GetTxStats(
        uint8                                  ctrlIdx,
  P2VAR(Eth_TxStatsType, AUTOMATIC, AUTOMATIC) txStatsPtr);
#endif /* ETH_30_TC3XX_ENABLE_GET_ETHER_STATS_API */

#if ( ETH_30_TC3XX_GET_AND_RESET_MEASUREMENT_DATA_API == STD_ON )
/***********************************************************************************************************************
 *  Eth_30_Tc3xx_Internal_GetAndResetMeasurementData
 **********************************************************************************************************************/
/*! \brief       To Get and/or Reset the Measurement statistics.
 *  \details     This function can be used to retrieve and/or reset the measurement data counter statistics that are
 *               supported.
 *  \param[in]   ctrlIdx     Identifier of the Ethernet controller
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]   measIdx         Identifier of the type of measurement data to be retrieved or reset
 *  \param[in]   resetNeeded     Controls if the data determined by MeasIdx should be reset
 *                               FALSE - Reset of the data not requested
 *                               TRUE  - Reset of the data requested
 *  \param[out]  measurementData Pointer to store the the measurement data if Reset is set to FALSE
 *  \return      E_OK: Measurement data successfully retrieved or reset
 *               E_NOT_OK: Measurement data could not be retrieved or reset
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE for different Ethernet controllers
 *  \synchronous TRUE
 *  \pre         -
 */
ETH_30_TC3XX_STATISTICS_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Internal_GetAndResetMeasurementData(
        uint8                         ctrlIdx,
        Eth_MeasurementIdxType        measIdx,
        boolean                       resetNeeded,
  P2VAR(uint32, AUTOMATIC, AUTOMATIC) measurementData);

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_Internal_GetAndResetMeasDataSwCounter
 **********************************************************************************************************************/
/*! \brief       Retrieve and optionally reset a specific measurement data counter.
 *  \details     -
 *
 *  \param[out]  measurementDataPtr   Pointer to retrieve a measurement data counter value or
 *                                    NULL_PTR if no retrieval is intended
 *  \param[in]   measDataStatsCtrPtr  Pointer to a specific global measurement data statistics counter
 *  \param[in]   ResetNeeded          Controls if the data in measDataStatsCtrPtr should be reset
 *                                      FALSE - Reset of the data not requested
 *                                      TRUE  - Reset of the data requested
 *  \context     TASK
 *  \synchronous TRUE
 *  \pre         -
 */
ETH_30_TC3XX_STATISTICS_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Internal_GetAndResetMeasDataSwCounter(
  P2VAR(uint32, AUTOMATIC, AUTOMATIC)  measurementDataPtr,
  P2VAR(uint32, AUTOMATIC, AUTOMATIC)  measDataStatsCtrPtr,
        boolean                        ResetNeeded);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Internal_ClearMeasurementData
 *********************************************************************************************************************/
/*! \brief       Clears all measurement data statistic counters of the Eth Core
 *  \details     -
 *  \param[in]   CtrlIdx Identifier of the Ethernet controller
 *  \pre         -
 *  \context     TASK
 *  \reentrant   TRUE
 *********************************************************************************************************************/
ETH_30_TC3XX_STATISTICS_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Internal_ClearMeasurementData(
  uint8 ctrlIdx);
#endif /* ETH_30_TC3XX_GET_AND_RESET_MEASUREMENT_DATA_API */

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_Internal_GetCounterState
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 */
ETH_30_TC3XX_STATISTICS_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Internal_GetCounterState(
        uint8                         ctrlIdx,
        uint16                        ctrOffs,
  P2VAR(uint32, AUTOMATIC, AUTOMATIC) ctrValPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 If the counter offset to be read from is in the supported range of the hardware */
  /*lint -e{522} */
  if (Eth_30_Tc3xx_LL_GetMaxCounterOffset(ctrlIdx) >= ctrOffs)
  {
    /* #110 Call the hardware dependent interface to read the counter value */
    /*lint -e{522} */
    retVal = Eth_30_Tc3xx_LL_GetCounterValue(ctrlIdx, ctrOffs, ctrValPtr);                                            /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_PASS */
  }

  return retVal;
} /* Eth_30_Tc3xx_Internal_GetCounterState */

#if (ETH_30_TC3XX_ENABLE_GET_ETHER_STATS_API == STD_ON)
/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Internal_GetRxStats()
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 */
ETH_30_TC3XX_STATISTICS_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Internal_GetRxStats(
        uint8                                  ctrlIdx,
  P2VAR(Eth_RxStatsType, AUTOMATIC, AUTOMATIC) rxStatsPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Set all statistics to invalid values */
  rxStatsPtr->RxStatsDropEvents           = ETH_30_TC3XX_TXRX_STATS_INVALID_COUNTER_VALUE;                               /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
  rxStatsPtr->RxStatsOctets               = ETH_30_TC3XX_TXRX_STATS_INVALID_COUNTER_VALUE;                               /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
  rxStatsPtr->RxStatsPkts                 = ETH_30_TC3XX_TXRX_STATS_INVALID_COUNTER_VALUE;                               /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
  rxStatsPtr->RxStatsBroadcastPkts        = ETH_30_TC3XX_TXRX_STATS_INVALID_COUNTER_VALUE;                               /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
  rxStatsPtr->RxStatsMulticastPkts        = ETH_30_TC3XX_TXRX_STATS_INVALID_COUNTER_VALUE;                               /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
  rxStatsPtr->RxStatsCrcAlignErrors       = ETH_30_TC3XX_TXRX_STATS_INVALID_COUNTER_VALUE;                               /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
  rxStatsPtr->RxStatsUndersizePkts        = ETH_30_TC3XX_TXRX_STATS_INVALID_COUNTER_VALUE;                               /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
  rxStatsPtr->RxStatsOversizePkts         = ETH_30_TC3XX_TXRX_STATS_INVALID_COUNTER_VALUE;                               /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
  rxStatsPtr->RxStatsFragments            = ETH_30_TC3XX_TXRX_STATS_INVALID_COUNTER_VALUE;                               /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
  rxStatsPtr->RxStatsJabbers              = ETH_30_TC3XX_TXRX_STATS_INVALID_COUNTER_VALUE;                               /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
  rxStatsPtr->RxStatsCollisions           = ETH_30_TC3XX_TXRX_STATS_INVALID_COUNTER_VALUE;                               /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
  rxStatsPtr->RxStatsPkts64Octets         = ETH_30_TC3XX_TXRX_STATS_INVALID_COUNTER_VALUE;                               /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
  rxStatsPtr->RxStatsPkts65to127Octets    = ETH_30_TC3XX_TXRX_STATS_INVALID_COUNTER_VALUE;                               /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
  rxStatsPtr->RxStatsPkts128to255Octets   = ETH_30_TC3XX_TXRX_STATS_INVALID_COUNTER_VALUE;                               /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
  rxStatsPtr->RxStatsPkts256to511Octets   = ETH_30_TC3XX_TXRX_STATS_INVALID_COUNTER_VALUE;                               /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
  rxStatsPtr->RxStatsPkts512to1023Octets  = ETH_30_TC3XX_TXRX_STATS_INVALID_COUNTER_VALUE;                               /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
  rxStatsPtr->RxStatsPkts1024to1518Octets = ETH_30_TC3XX_TXRX_STATS_INVALID_COUNTER_VALUE;                               /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
  rxStatsPtr->RxUnicastFrames             = ETH_30_TC3XX_TXRX_STATS_INVALID_COUNTER_VALUE;                               /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */

  /* #20 Enter exclusive area (Reason: Consistent result for the counters) */
  Eth_30_Tc3xx_EnterExclusiveArea(DATA); 
  /* #30 Read the RX statistics counter registers and report the results */
  retVal = Eth_30_Tc3xx_LL_GetRxStats(ctrlIdx, rxStatsPtr);                                                              /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_PASS */
  /* #40 Leave exclusive area */
  Eth_30_Tc3xx_ExitExclusiveArea(DATA); 

  return retVal;
} /* Eth_30_Tc3xx_Internal_GetRxStats */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Internal_GetTxStats()
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 */ 
ETH_30_TC3XX_STATISTICS_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Internal_GetTxStats(
        uint8                                  ctrlIdx,
  P2VAR(Eth_TxStatsType, AUTOMATIC, AUTOMATIC) txStatsPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Set all statistics to invalid values */
  txStatsPtr->TxNumberOfOctets = ETH_30_TC3XX_TXRX_STATS_INVALID_COUNTER_VALUE;  /* PRQA S 2982 */ /* MD_Eth_30_Tc3xx_2982 */ /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
  txStatsPtr->TxNUcastPkts     = ETH_30_TC3XX_TXRX_STATS_INVALID_COUNTER_VALUE;  /* PRQA S 2982 */ /* MD_Eth_30_Tc3xx_2982 */ /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
  txStatsPtr->TxUniCastPkts    = ETH_30_TC3XX_TXRX_STATS_INVALID_COUNTER_VALUE;  /* PRQA S 2982 */ /* MD_Eth_30_Tc3xx_2982 */ /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */

  /* #20 Enter exclusive area (Reason: Consistent result for the counters) */
  Eth_30_Tc3xx_EnterExclusiveArea(DATA); 
  /* #30 Read the TX statistics counter registers and report the results */
  retVal = Eth_30_Tc3xx_LL_GetTxStats(ctrlIdx, txStatsPtr);                                                              /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_PASS */

  /* #40 Leave exclusive area  */
  Eth_30_Tc3xx_ExitExclusiveArea(DATA); 

  return retVal;
} /* Eth_30_Tc3xx_Internal_GetTxStats */
#endif /* ETH_30_TC3XX_ENABLE_GET_ETHER_STATS_API */

#if (ETH_30_TC3XX_GET_AND_RESET_MEASUREMENT_DATA_API == STD_ON)
/***********************************************************************************************************************
 *  Eth_30_Tc3xx_GetAndResetMeasurementData
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
ETH_30_TC3XX_STATISTICS_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Internal_GetAndResetMeasurementData(
        uint8                         ctrlIdx,
        Eth_MeasurementIdxType        measIdx,
        boolean                       resetNeeded,
  P2VAR(uint32, AUTOMATIC, AUTOMATIC) measurementData)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_OK;
  boolean isHwCtrResetOnRead;
  Eth_30_Tc3xx_DropInsuffRxBuffOfEthMeasDataCounterType readCounterValue;

  /* #10 Enter exclusive area (Reason: Update statistic counters in a consistent manner) */
  Eth_30_Tc3xx_EnterExclusiveArea(DATA_MULTI_CORE);

  switch(measIdx)
  {
    /* #20 If the MeasurementIdx is set to ETH_MEAS_ALL */
    case ETH_MEAS_ALL:
      /* #210 If a reset of the counter values is requested */
      if (resetNeeded == TRUE)
      {
        /* #2110 Reset all measurement data statistics */
        Eth_30_Tc3xx_Internal_ClearMeasurementData(ctrlIdx);
      }
      /* #220 If Reset needed is set to false */
      else
      {
        /* #2210 Return Not OK since MeasrementIdx ETH_MEAS_ALL only supported for reset of all statistics */
        retVal = E_NOT_OK;
      }
      break;

    /* #30 If the MeasurementIdx is set to ETH_MEAS_VENDOR_SPECIFIC_DROP_INSUFF_TX_BUFFER */
    case ETH_MEAS_VENDOR_SPECIFIC_DROP_INSUFF_TX_BUFFER:
      /* #310 Call the internal api to get and/or reset ETH_MEAS_VENDOR_SPECIFIC_DROP_INSUFF_TX_BUFFER counter */
      Eth_30_Tc3xx_Internal_GetAndResetMeasDataSwCounter(                                                                  /* SBSW_ETH_30_TC3XX_INT_FCT_PUB_PARAM_PTR_AND_CSL_MEM_PTR_PASS_MEASUREMENT_DATA */
          measurementData,
          Eth_30_Tc3xx_GetAddrDropInsuffTxBuffOfEthMeasDataCounter(ctrlIdx),
          resetNeeded);
      break;

    /* #40 If the MeasurementIdx is set to ETH_MEAS_VENDOR_SPECIFIC_WARN_FULL_RX_BUFFER */
    case ETH_MEAS_VENDOR_SPECIFIC_WARN_FULL_RX_BUFFER:
       /* #410 Call the internal api to get and/or reset ETH_MEAS_VENDOR_SPECIFIC_WARN_FULL_RX_BUFFER counter */
       Eth_30_Tc3xx_Internal_GetAndResetMeasDataSwCounter(                                                                  /* SBSW_ETH_30_TC3XX_INT_FCT_PUB_PARAM_PTR_AND_CSL_MEM_PTR_PASS_MEASUREMENT_DATA */
           measurementData,
           Eth_30_Tc3xx_GetAddrWarnFullRxBuffOfEthMeasDataCounter(ctrlIdx),
           resetNeeded);
       break;

    /* #50 If the MeasurementIdx is set to ETH_MEAS_VENDOR_SPECIFIC_DROP_INSUFF_RX_BUFFER */
    case ETH_MEAS_VENDOR_SPECIFIC_DROP_INSUFF_RX_BUFFER:
      /* #510 Read the counter value from the hardware */
      retVal = Eth_30_Tc3xx_LL_GetDropInsuffRxBuffHwCounter(                                                               /* SBSW_ETH_30_TC3XX_REF_OF_STACK_VAR */
          ctrlIdx,
          &readCounterValue,
          &isHwCtrResetOnRead);

      /* #520 Set the software counter variable to the read value */
      Eth_30_Tc3xx_SetDropInsuffRxBuffOfEthMeasDataCounter(ctrlIdx, readCounterValue);                                 /* SBSW_ETH_30_TC3XX_INT_FCT_IDX_PASS */

      /* #530 If a reset is requested for the counter */
      if(resetNeeded == TRUE)
      {
        /* #5310 Make sure the hardware counter is reset as well since it is not reset on read */
        retVal = Eth_30_Tc3xx_LL_ResetDropInsuffRxBuffHwCounter(ctrlIdx);
      }

      /* #540 Call the internal api to get and/or reset ETH_MEAS_VENDOR_SPECIFIC_DROP_INSUFF_RX_BUFFER counter */
      Eth_30_Tc3xx_Internal_GetAndResetMeasDataSwCounter(
            measurementData,
            Eth_30_Tc3xx_GetAddrDropInsuffRxBuffOfEthMeasDataCounter(ctrlIdx) ,                                            /* SBSW_ETH_30_TC3XX_INT_FCT_PUB_PARAM_PTR_AND_CSL_MEM_PTR_PASS_MEASUREMENT_DATA */
            resetNeeded);
      break;

    default:
      retVal = E_NOT_OK;
      break;
  }

  /* #70 Leave exclusive area */
  Eth_30_Tc3xx_ExitExclusiveArea(DATA_MULTI_CORE);

  return retVal;
} /* Eth_30_Tc3xx_Internal_GetAndResetMeasurementData() */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_Internal_GetAndResetMeasurementDataSwCounter
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
ETH_30_TC3XX_STATISTICS_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Internal_GetAndResetMeasDataSwCounter(
  P2VAR(uint32, AUTOMATIC, AUTOMATIC)  measurementDataPtr,
  P2VAR(uint32, AUTOMATIC, AUTOMATIC)  measDataStatsCtrPtr,
        boolean                        ResetNeeded)
{
  /* #20 Only provide measurement data statistics value if pointer is no NULL_PTR */
  if (measurementDataPtr != NULL_PTR)
  {
    (*measurementDataPtr) = (*measDataStatsCtrPtr);                                                                     /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_ACCESS_POSSIBLE_NULL_PTR_AFTER_NULL_PTR_CHECK */
  }
  /* #30 Only reset measurement data statistics value if reset is requested */
  if (ResetNeeded == TRUE)
  {
    (*measDataStatsCtrPtr) = 0u;                                                                                        /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
  }
} /* Eth_30_Tc3xx_Internal_GetAndResetMeasurementDataSwCounter */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Internal_ClearMeasurementData
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
ETH_30_TC3XX_STATISTICS_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Internal_ClearMeasurementData(uint8 ctrlIdx)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Enter exclusive area (Reason: Clear statistic counters in an atomic operation) */
  Eth_30_Tc3xx_EnterExclusiveArea(DATA); 

  /* #20 Clear all measurement data statistic counters */
  Eth_30_Tc3xx_SetDropInsuffTxBuffOfEthMeasDataCounter(ctrlIdx, 0u);                                                     /* SBSW_ETH_30_TC3XX_INT_FCT_IDX_PASS */
  Eth_30_Tc3xx_SetWarnFullRxBuffOfEthMeasDataCounter(ctrlIdx, 0u);                                                       /* SBSW_ETH_30_TC3XX_INT_FCT_IDX_PASS */
  Eth_30_Tc3xx_SetDropInsuffRxBuffOfEthMeasDataCounter(ctrlIdx, 0u);                                                     /* SBSW_ETH_30_TC3XX_INT_FCT_IDX_PASS */
  (void)Eth_30_Tc3xx_LL_ResetDropInsuffRxBuffHwCounter(ctrlIdx);

  /* #30 Leave exclusive area */
  Eth_30_Tc3xx_ExitExclusiveArea(DATA); 
} /* Eth_30_Tc3xx_Internal_ClearMeasurementData() */
#endif /* ETH_30_TC3XX_GET_AND_RESET_MEASUREMENT_DATA_API */

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_GetCounterState
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetCounterState(
        uint8                         CtrlIdx,
        uint16                        CtrOffs,
  P2VAR(uint32, AUTOMATIC, AUTOMATIC) CtrValPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = ETH_30_TC3XX_E_NO_ERROR;
  Std_ReturnType retVal = E_NOT_OK;  /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint8 localCtrlIdx = CtrlIdx;

  /* ----- Development Error Checks ------------------------------------- */
#if (ETH_30_TC3XX_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check plausibility of input parameters and initialization state */
  if (localCtrlIdx >= Eth_30_Tc3xx_GetSizeOfEthCtrl())
  {
    errorId = ETH_30_TC3XX_E_INV_CTRL_IDX;
  }
  else if (Eth_30_Tc3xx_ModuleInitialized == ETH_STATE_UNINIT)
  {
    errorId = ETH_30_TC3XX_E_NOT_INITIALIZED;
  }
  else if (CtrValPtr == NULL_PTR)
  {
    errorId = ETH_30_TC3XX_E_INV_POINTER;
  }
  else
#endif /* ETH_30_TC3XX_DEV_ERROR_DETECT */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Call the internal or host controller interface to read a statistic counter value */
#if (ETH_30_TC3XX_ENABLE_HOST_CTRL_INTERFACE == STD_OFF) /* COV_ETH_HOST_CTRL_INTERFACE */
    retVal = Eth_30_Tc3xx_Internal_GetCounterState(localCtrlIdx, CtrOffs, CtrValPtr);                                 /* SBSW_ETH_30_TC3XX_INT_FCT_PUB_PARAM_PTR_PASS */
#else
    retVal = Eth_30_Tc3xx_LL_HostCtrlIfc_GetCounterState(localCtrlIdx, CtrOffs, CtrValPtr);                              /* SBSW_ETH_30_TC3XX_INT_FCT_PUB_PARAM_PTR_PASS */
#endif /* ETH_30_TC3XX_ENABLE_HOST_CTRL_INTERFACE */
  }
  /* ----- Development Error Report --------------------------------------- */
#if (ETH_30_TC3XX_DEV_ERROR_REPORT == STD_ON)
  if (errorId != ETH_30_TC3XX_E_NO_ERROR)
  {
    (void)Det_ReportError(ETH_30_TC3XX_MODULE_ID, CtrlIdx, ETH_30_TC3XX_SID_GET_COUNTER_STATE, errorId);
  }
#else
  ETH_30_TC3XX_DUMMY_STATEMENT(errorId); /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
#endif /* ETH_30_TC3XX_DEV_ERROR_REPORT */

  return retVal;
} /* Eth_30_Tc3xx_GetCounterState */

#if (ETH_30_TC3XX_ENABLE_GET_ETHER_STATS_API == STD_ON)
/**********************************************************************************************************************
 *  Eth_30_Tc3xx_GetRxStats()
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetRxStats(
        uint8                                  CtrlIdx,
  P2VAR(Eth_RxStatsType, AUTOMATIC, AUTOMATIC) RxStatsPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;  /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint8 errorId = ETH_30_TC3XX_E_NO_ERROR;
  uint8 localCtrlIdx = CtrlIdx;

  /* ----- Development Error Checks ------------------------------------- */
# if (ETH_30_TC3XX_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check plausibility of input parameters and initialization state */
  /* Check initialization state of the component */
  if (Eth_30_Tc3xx_ModuleInitialized == ETH_STATE_UNINIT)
  {
    errorId = ETH_30_TC3XX_E_NOT_INITIALIZED;
  }
  /* Check parameter 'CtrlIdx' */
  else if (localCtrlIdx >= Eth_30_Tc3xx_GetSizeOfEthCtrl())
  {
    errorId = ETH_30_TC3XX_E_INV_CTRL_IDX;
  }
  /* Check parameter 'RxStatsPtr' */
  else if (RxStatsPtr == NULL_PTR)
  {
    errorId = ETH_30_TC3XX_E_INV_POINTER;
  }
  else
# endif
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Call the internal or host controller interface to retrieve the reception statistics */
# if (ETH_30_TC3XX_ENABLE_HOST_CTRL_INTERFACE == STD_OFF) /* COV_ETH_HOST_CTRL_INTERFACE */
    retVal = Eth_30_Tc3xx_Internal_GetRxStats(localCtrlIdx, RxStatsPtr);                                                 /* SBSW_ETH_30_TC3XX_INT_FCT_PUB_PARAM_PTR_PASS */
# else
    retVal = Eth_30_Tc3xx_LL_HostCtrlIfc_GetRxStats(localCtrlIdx, RxStatsPtr);                                           /* SBSW_ETH_30_TC3XX_INT_FCT_PUB_PARAM_PTR_PASS */
# endif /* ETH_30_TC3XX_ENABLE_HOST_CTRL_INTERFACE */
  }
  /* ----- Development Error Report --------------------------------------- */
# if (ETH_30_TC3XX_DEV_ERROR_REPORT == STD_ON)
  if (errorId != ETH_30_TC3XX_E_NO_ERROR)
  {
    (void)Det_ReportError(ETH_30_TC3XX_MODULE_ID, CtrlIdx, ETH_30_TC3XX_SID_GET_RX_STATS, errorId);
  }
# else
  ETH_30_TC3XX_DUMMY_STATEMENT(errorId); /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
# endif

  return retVal;
} /* Eth_30_Tc3xx_GetRxStats */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_GetTxStats()
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetTxStats(
        uint8                                  CtrlIdx,
  P2VAR(Eth_TxStatsType, AUTOMATIC, AUTOMATIC) TxStatsPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;  /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint8 errorId = ETH_30_TC3XX_E_NO_ERROR;
  uint8 localCtrlIdx = CtrlIdx;

  /* ----- Development Error Checks ------------------------------------- */
# if (ETH_30_TC3XX_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check plausibility of input parameters and initialization state */
  /* Check initialization state of the component */
  if (Eth_30_Tc3xx_ModuleInitialized == ETH_STATE_UNINIT)
  {
    errorId = ETH_30_TC3XX_E_NOT_INITIALIZED;
  }
  /* Check parameter 'CtrlIdx' */
  else if (localCtrlIdx >= Eth_30_Tc3xx_GetSizeOfEthCtrl())
  {
    errorId = ETH_30_TC3XX_E_INV_CTRL_IDX;
  }
  /* Check parameter 'TxStatsPtr' */
  else if (TxStatsPtr == NULL_PTR)
  {
    errorId = ETH_30_TC3XX_E_INV_POINTER;
  }
  else
# endif
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Call the internal or host controller interface to retrieve the transmission statistics */
# if (ETH_30_TC3XX_ENABLE_HOST_CTRL_INTERFACE == STD_OFF) /* COV_ETH_HOST_CTRL_INTERFACE */
    retVal = Eth_30_Tc3xx_Internal_GetTxStats(localCtrlIdx, TxStatsPtr);                                                 /* SBSW_ETH_30_TC3XX_INT_FCT_PUB_PARAM_PTR_PASS */
# else
    retVal = Eth_30_Tc3xx_LL_HostCtrlIfc_GetTxStats(localCtrlIdx, TxStatsPtr);                                           /* SBSW_ETH_30_TC3XX_INT_FCT_PUB_PARAM_PTR_PASS */
# endif /* ETH_30_TC3XX_ENABLE_HOST_CTRL_INTERFACE */
  }
  /* ----- Development Error Report --------------------------------------- */
# if (ETH_30_TC3XX_DEV_ERROR_REPORT == STD_ON)
  if (errorId != ETH_30_TC3XX_E_NO_ERROR)
  {
    (void)Det_ReportError(ETH_30_TC3XX_MODULE_ID, CtrlIdx, ETH_30_TC3XX_SID_GET_TX_STATS, errorId);
  }
# else
  ETH_30_TC3XX_DUMMY_STATEMENT(errorId); /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
# endif

  return retVal;
} /* Eth_30_Tc3xx_GetTxStats() */
#endif /* ETH_30_TC3XX_ENABLE_GET_ETHER_STATS_API */

#if (ETH_30_TC3XX_GET_AND_RESET_MEASUREMENT_DATA_API == STD_ON)
/***********************************************************************************************************************
 *  Eth_30_Tc3xx_GetAndResetMeasurementData
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetAndResetMeasurementData(
  uint8                               CtrlIdx,
  Eth_MeasurementIdxType              MeasIdx,
  boolean                             ResetNeeded,
  P2VAR(uint32, AUTOMATIC, AUTOMATIC) MeasurementData)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;  /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint8 errorId = ETH_30_TC3XX_E_NO_ERROR;
  uint8 localCtrlIdx = CtrlIdx;

  /* ----- Development Error Checks ------------------------------------- */
# if (ETH_30_TC3XX_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check plausibility of input parameters and initialization state */
  /* Check initialization state of the component */
  if (Eth_30_Tc3xx_ModuleInitialized == ETH_STATE_UNINIT)
  {
    errorId = ETH_30_TC3XX_E_NOT_INITIALIZED;
  }
  /* Check parameter 'CtrlIdx' */
  else if (CtrlIdx >= Eth_30_Tc3xx_GetSizeOfEthCtrl())
  {
    errorId = ETH_30_TC3XX_E_INV_CTRL_IDX;
  }
  else
# endif
  {
    /* #20 Call the internal or host controller interface to retrieve and/or reset the measurement data */
# if (ETH_30_TC3XX_ENABLE_HOST_CTRL_INTERFACE == STD_OFF) /* COV_ETH_HOST_CTRL_INTERFACE */
    retVal = Eth_30_Tc3xx_Internal_GetAndResetMeasurementData(localCtrlIdx, MeasIdx, ResetNeeded, MeasurementData);      /* SBSW_ETH_30_TC3XX_INT_FCT_PUB_PARAM_PTR_PASS */
# else
    retVal = Eth_30_Tc3xx_LL_HostCtrlIfc_GetAndResetMeasurementData(localCtrlIdx, MeasIdx, ResetNeeded, MeasurementData);/* SBSW_ETH_30_TC3XX_INT_FCT_PUB_PARAM_PTR_PASS */
# endif /* ETH_30_TC3XX_ENABLE_HOST_CTRL_INTERFACE */
  }
  /* ----- Development Error Report --------------------------------------- */
# if (ETH_30_TC3XX_DEV_ERROR_REPORT == STD_ON)
  if (errorId != ETH_30_TC3XX_E_NO_ERROR)
  {
    (void)Det_ReportError(
        ETH_30_TC3XX_MODULE_ID,
        CtrlIdx,
        ETH_30_TC3XX_SID_GET_AND_RESET_MEASUREMENT_DATA_API,
        errorId);
  }
# else
  ETH_30_TC3XX_DUMMY_STATEMENT(errorId); /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
# endif

  return retVal;
} /* Eth_30_Tc3xx_GetAndResetMeasurementData() */ /* PRQA S 6050, 6080 */ /* MD_MSR_STPAR, MD_MSR_STMIF */
#endif /* ETH_30_TC3XX_GET_AND_RESET_MEASUREMENT_DATA_API */

#define ETH_30_TC3XX_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
/**********************************************************************************************************************
 *  END OF FILE: Eth_30_Tc3xx_Statistics.c
 *********************************************************************************************************************/
