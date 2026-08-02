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
/*!        \file  Eth_30_Tc3xx_LL_Statistics_Ifc_Int.h
 *        \brief  Lower layer statistics private header file
 *
 *      \details  Private declaratiopns of lower layer statistics part of component.
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
#if !defined (ETH_30_TC3XX_LL_STATISTICS_IFC_INT_H)
# define ETH_30_TC3XX_LL_STATISTICS_IFC_INT_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "Eth_30_Tc3xx_LL_Types_Int.h"
# include "Eth_30_Tc3xx_HwAccess_Int.h"

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/

# ifndef ETH_30_TC3XX_LL_STATISTICS_LOCAL /* COV_ETH_COMPATIBILITY */
#  define ETH_30_TC3XX_LL_STATISTICS_LOCAL                                       static
# endif

# ifndef ETH_30_TC3XX_LL_STATISTICS_LOCAL_INLINE /* COV_ETH_COMPATIBILITY */
#  define ETH_30_TC3XX_LL_STATISTICS_LOCAL_INLINE                                LOCAL_INLINE
# endif

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

# define ETH_30_TC3XX_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_GetMaxCounterOffset
 *********************************************************************************************************************/
/*! \brief       Returns the maximum counter offset within the statistic counter register block
 *  \details     Function returns the maximum counter offset of the Ethernet controllers statistic counters register
 *               block.
 *               during retrieval of the counter value.
 *  \param[in]   ctrlIdx          Index of controller
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \return      Amount of statistic counters
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   TRUE - for different Ethernet controllers
 *  \pre         -
 */
ETH_30_TC3XX_LL_STATISTICS_LOCAL_INLINE FUNC(uint16, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_GetMaxCounterOffset(
  uint8 ctrlIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_GetCounterValue
 *********************************************************************************************************************/
/*! \brief       Retrieves the value of the given statistics counter
 *  \details     Function checks if a valid statistics counter is addressed within the counter register block and if
 *               so returns its value.
 *  \param[in]   ctrlIdx          Index of controller
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]   counterOffset    Offset into the statistic counter register block
 *  \param[out]  counterValPtr    Value of the statistics counter
 *  \return      E_OK - Counter value successfully retrieved
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   TRUE - for different Ethernet controllers and counters
 *  \pre         counterIdx must have been checked for being inbound of the statistics counter register block
 */
ETH_30_TC3XX_LL_STATISTICS_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_GetCounterValue(
        uint8                                       ctrlIdx,
        Eth_30_Tc3xx_RegOffsetType                  counterOffset,
  P2VAR(uint32, AUTOMATIC, ETH_30_TC3XX_VAR_NOINIT) counterValPtr);

# if (ETH_30_TC3XX_ENABLE_GET_ETHER_STATS_API == STD_ON)
/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_GetRxStats
 *********************************************************************************************************************/
/*! \brief       Retrieves the values of RX statistics counters
 *  \details     Function reads a set of reception statistics counters and returns their values.
 *  \param[in]   ctrlIdx    Index of controller
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[out]  rxStatsPtr Pointer to the address where the RX statistics counter values are stored
 *  \return      E_OK - RX statistics counters successfully retrieved
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   TRUE - for different Ethernet controllers
 *  \pre         ETH_30_TC3XX_EXCLUSIVE_AREA_DATA must be entered.
 *  \config      ETH_30_TC3XX_ENABLE_GET_ETHER_STATS_API == STD_ON
 */
ETH_30_TC3XX_LL_STATISTICS_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_GetRxStats(
        uint8                                                ctrlIdx,
  P2VAR(Eth_RxStatsType, AUTOMATIC, ETH_30_TC3XX_VAR_NOINIT) rxStatsPtr);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_GetTxStats
 *********************************************************************************************************************/
/*! \brief       Retrieves the values of TX statistics counters
 *  \details     Function reads a set of transmission statistics counters and returns their values.
 *  \param[in]   ctrlIdx    Index of controller
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[out]  txStatsPtr Pointer to the address where the TX statistics counter values are stored
 *  \return      E_OK - TX statistics counters successfully retrieved
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   TRUE - for different Ethernet controllers
 *  \pre         ETH_30_TC3XX_EXCLUSIVE_AREA_DATA must be entered.
 *  \config      ETH_30_TC3XX_ENABLE_GET_ETHER_STATS_API == STD_ON
 */
ETH_30_TC3XX_LL_STATISTICS_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_GetTxStats(
        uint8                                  ctrlIdx,
  P2VAR(Eth_TxStatsType, AUTOMATIC, AUTOMATIC) txStatsPtr);
# endif /* ETH_30_TC3XX_ENABLE_GET_ETHER_STATS_API */

# if (ETH_30_TC3XX_GET_AND_RESET_MEASUREMENT_DATA_API == STD_ON)
/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_GetDropInsuffRxBuffHwCounter()
 *********************************************************************************************************************/
/*! \brief       This function returns the number of reception drop events due to insufficient buffers.
 *  \details     Read the Hw counter of reception drop events due to insufficient buffers if exists and return the 
 *               counter value and if the counter is reset on read or not.
 *  \param[in]   ctrlIdx                    Index of controller
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[out]  isHwCtrResetOnReadPtr  Pointer to variable to store if the Hw counter is reset on read
 *  \param[out]  readCtrValuePtr        Pointer to variable where the read count of Rx frame drop is stored
 *  \return      E_OK - Hardware counter values are retrieved successfully
 *  \return      E_NOT_OK - Hardware counter is not available or unable to get the counter value
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 */
ETH_30_TC3XX_LL_STATISTICS_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_GetDropInsuffRxBuffHwCounter(
        uint8                                                                        ctrlIdx,
  P2VAR(Eth_30_Tc3xx_DropInsuffRxBuffOfEthMeasDataCounterType, AUTOMATIC, AUTOMATIC) readCtrValuePtr,
  P2VAR(boolean,                                              AUTOMATIC, AUTOMATIC)  isHwCtrResetOnReadPtr);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_ResetDropInsuffRxBuffHwCounter()
 *********************************************************************************************************************/
/*! \brief       This function resets the counter for reception drop events due to insufficient buffers
 *  \details     Reset the Hw counter used to store the count of number of reception drop events due to insufficient rx
 *               buffers. If the reset is not possible, it will be indicated to the caller.
 *  \param[in]   ctrlIdx          Index of controller
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \return      E_OK - Hardware counter reset successfully
 *  \return      E_NOT_OK - Hardware counter is not available or unable to reset the counter
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 */
ETH_30_TC3XX_LL_STATISTICS_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_ResetDropInsuffRxBuffHwCounter(
  uint8 ctrlIdx);
# endif /* ETH_30_TC3XX_GET_AND_RESET_MEASUREMENT_DATA_API */

# define ETH_30_TC3XX_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* ETH_30_TC3XX_LL_STATISTICS_IFC_INT_H */

/**********************************************************************************************************************
 *  END OF FILE: Eth_30_Tc3xx_LL_Statistics_Ifc_Int.h
 *********************************************************************************************************************/
