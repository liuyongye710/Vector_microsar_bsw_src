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
/*!        \file  Eth_30_Tc3xx_Statistics.h
 *        \brief  Statistics sub-module header of the Ethernet controller driver
 *
 *      \details  Provides access to the statistics related API of the Ethernet controller driver.
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
#if !defined (ETH_30_TC3XX_STATISTICS_H)
# define ETH_30_TC3XX_STATISTICS_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "Eth_30_Tc3xx_Types.h"
# include "Eth_30_Tc3xx_LL_Statistics.h"

/* ----- ETH API service IDs ----- */
/*!< Service ID: Eth_30_Tc3xx_GetCounterState() */
# define ETH_30_TC3XX_SID_GET_COUNTER_STATE                           (0x07u)
/*!< Service ID: Eth_30_Tc3xx_GetRxStats() */
# define ETH_30_TC3XX_SID_GET_RX_STATS                                (0x0Eu)
/*!< Service ID: Eth_30_Tc3xx_GetTxStats() */
# define ETH_30_TC3XX_SID_GET_TX_STATS                                (0x0Fu)
/*!< Service ID: Eth_30_Tc3xx_GetAndResetMeasurementData() */
# define ETH_30_TC3XX_SID_GET_AND_RESET_MEASUREMENT_DATA_API          (0x11u)

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

# define ETH_30_TC3XX_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_GetCounterState
 **********************************************************************************************************************/
/*! \brief       Retrieves the value of an Ethernet statistics counter
 *  \details     Function retrieves the value of an Ethernet statistics counter by addressing the counter with the help
 *               of an offset into the Ethernet statistics counter register space.
 *  \param[in]   CtrlIdx    Identifier of the Ethernet controller
 *  \param[in]   CtrOffs    Offset of the counter into the Ethernet statistics counter register space
 *  \param[out]  CtrValPtr  Buffer to store the counter value
 *  \return      E_NOT_OK - Counter retrieval failed
 *  \return      E_OK - Counter successfully retrieved
 *  \context     ANY
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         Ethernet controller is initialized
 *  \trace       CREQ-137705
 */
FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetCounterState(
        uint8                         CtrlIdx,
        uint16                        CtrOffs,
  P2VAR(uint32, AUTOMATIC, AUTOMATIC) CtrValPtr);

# if (ETH_30_TC3XX_ENABLE_GET_ETHER_STATS_API == STD_ON)
/**********************************************************************************************************************
 *  Eth_30_Tc3xx_GetRxStats()
 *********************************************************************************************************************/
/*! \brief       Returns list of reception statistics
 *  \details     Function returns the list of reception statistics from IETF RFC1213.
 *  \param[in]   CtrlIdx     Identifier of the Ethernet controller
 *  \param[out]  RxStatsPtr  List of read statistics values for reception
 *  \return      E_OK: success
 *               E_NOT_OK: RX-statistics could not be obtained
 *  \context     ANY
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \trace       CREQ-137827
 */
FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetRxStats(
        uint8                                  CtrlIdx,
  P2VAR(Eth_RxStatsType, AUTOMATIC, AUTOMATIC) RxStatsPtr);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_GetTxStats()
 *********************************************************************************************************************/
/*! \brief       Returns list of transmission statistics
 *  \details     Function returns the list of transmission statistics from IETF RFC1213.
 *  \param[in]   CtrlIdx     Identifier of the Ethernet controller
 *  \param[out]  TxStatsPtr  List of read statistics values for transmission
 *  \return      E_OK: success
 *               E_NOT_OK: TX-statistics could not be obtained
 *  \context     ANY
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \trace       CREQ-137827
 */
FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetTxStats(
        uint8                                  CtrlIdx,
  P2VAR(Eth_TxStatsType, AUTOMATIC, AUTOMATIC) TxStatsPtr);
# endif /* ETH_30_TC3XX_ENABLE_GET_ETHER_STATS_API */

# if (ETH_30_TC3XX_GET_AND_RESET_MEASUREMENT_DATA_API == STD_ON)
/***********************************************************************************************************************
 *  Eth_30_Tc3xx_GetAndResetMeasurementData
 **********************************************************************************************************************/
/*! \brief       To Get and/or Reset the Measurement statistics.
 *  \details     This function can be used to retrieve and/or reset the measurement data counter statistics that are
 *               supported.
 *  \param[in]   CtrlIdx         Identifier of the Ethernet controller
 *  \param[in]   MeasIdx         Identifier of the type of measurement data to be retrieved or reset
 *                ETH_MEAS_ALL - Only usable if ResetNeeded is TRUE, will reset all measured data
 *                ETH_MEAS_VENDOR_SPECIFIC_DROP_INSUFF_TX_BUFFER - Reset and/or retrieve amount of denied Tx buffer
 *                  provision requests due to unavailable buffer resources
 *                ETH_MEAS_VENDOR_SPECIFIC_WARN_FULL_RX_BUFFER - Reset and/or retrieve amount of warning events which
 *                  indicate that all Rx buffers are blocked by the software
 *                ETH_MEAS_VENDOR_SPECIFIC_DROP_INSUFF_RX_BUFFER - Reset and/or retrieve a mount of Rx frames dropped
 *                  due to unavailable buffer resources
 *  \param[in]   ResetNeeded     Controls if the data determined by MeasIdx should be reset
 *                               FALSE - Reset of the data not requested
 *                               TRUE  - Reset of the data requested
 *  \param[out]  MeasurementData Pointer to store the retrieved measurement data
 *  \return      E_OK: Measurement data successfully retrieved or reset
 *               E_NOT_OK: Measurement data could not be retrieved or reset
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE for different Ethernet controllers
 *  \synchronous TRUE
 *  \pre         Module is initialized
 *  \trace       CREQ-242848
 */
FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetAndResetMeasurementData(
        uint8                         CtrlIdx,
        Eth_MeasurementIdxType        MeasIdx,
        boolean                       ResetNeeded,
  P2VAR(uint32, AUTOMATIC, AUTOMATIC) MeasurementData);
# endif /* ETH_30_TC3XX_GET_AND_RESET_MEASUREMENT_DATA_API */

# define ETH_30_TC3XX_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* ETH_30_TC3XX_STATISTICS_H */

/**********************************************************************************************************************
 *  END OF FILE: Eth_30_Tc3xx_Statistics.h
 *********************************************************************************************************************/
