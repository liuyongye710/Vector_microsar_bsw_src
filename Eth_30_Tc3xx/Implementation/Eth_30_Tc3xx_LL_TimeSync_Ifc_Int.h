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
/*!        \file  Eth_30_Tc3xx_LL_TimeSync_Ifc_Int.h
 *        \brief  Lower layer time synchronization private header file
 *
 *      \details  Private declarations of lower layer time synchronization part of component.
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

#if !defined (ETH_30_TC3XX_LL_TIME_SYNC_IFC_INT_H)
# define ETH_30_TC3XX_LL_TIME_SYNC_IFC_INT_H

# if (ETH_30_TC3XX_ENABLE_TIMESYNC == STD_ON)
/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#  include "Eth_30_Tc3xx_LL_Types_Int.h"
#  include "Eth_30_Tc3xx_HwAccess_Int.h"

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/

#  ifndef ETH_30_TC3XX_LL_TIME_SYNC_LOCAL /* COV_ETH_COMPATIBILITY */
#   define ETH_30_TC3XX_LL_TIME_SYNC_LOCAL                            static
#  endif

#  ifndef ETH_30_TC3XX_LL_TIME_SYNC_LOCAL_INLINE /* COV_ETH_COMPATIBILITY */
#   define ETH_30_TC3XX_LL_TIME_SYNC_LOCAL_INLINE                     LOCAL_INLINE
#  endif

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
#  define ETH_30_TC3XX_START_SEC_CODE
#  include "MemMap.h" /* PRQA S 5087 1 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_TimeSync_StartTimesyncClock()
 *********************************************************************************************************************/
/*! \brief       Function for starting the timesync clock of the MAC
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller for which the timesync clock shall be started
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \config      ETH_30_TC3XX_ENABLE_TIMESYNC == STD_ON
 *  \pre         -
 */
ETH_30_TC3XX_LL_TIME_SYNC_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_TimeSync_StartTimesyncClock(
  uint8 ctrlIdx);

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_TimeSync_CaptureHwTime
 **********************************************************************************************************************/
/*! \brief       Captures the hardware timer of the Ethernet controller and returns the time stamp
 *  \details     -
 *  \param[in]   ctrlIdx      Identifier of Ethernet controller
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[out]  timeStampPtr Time stamp captured
 *  \context     ANY
 *  \synchronous TRUE
 *  \reentrant   TRUE for different Ethernet controllers
 *  \config      ETH_30_TC3XX_ENABLE_TIMESYNC == STD_ON
 *  \pre         -
 */
ETH_30_TC3XX_LL_TIME_SYNC_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_TimeSync_CaptureHwTime(
        uint8                                    ctrlIdx,
  P2VAR(Eth_TimeStampType, AUTOMATIC, ETH_30_TC3XX_VAR_NOINIT) timeStampPtr);

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_TimeSync_SetHwTime
 **********************************************************************************************************************/
/*! \brief       Sets the hardware and software part of the timer to the given time
 *  \details     -
 *  \param[in]   ctrlIdx      Identifier of Ethernet controller
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]   timeStampPtr Time to set
 *  \context     ANY
 *  \synchronous TRUE
 *  \reentrant   TRUE for different Ethernet controllers
 *  \config      ETH_30_TC3XX_ENABLE_TIMESYNC == STD_ON
 *  \pre         Exclusive area for hardware timer (EXCLUSIVE_AREA_TIME) entered
 **********************************************************************************************************************/
ETH_30_TC3XX_LL_TIME_SYNC_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_TimeSync_SetHwTime(
          uint8                                    ctrlIdx,
  P2CONST(Eth_TimeStampType, AUTOMATIC, ETH_30_TC3XX_VAR_NOINIT) timeStampPtr);

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_TimeSync_GetTxTimeStamp
 **********************************************************************************************************************/
/*! \brief       Retrieves the TX time stamp from the given descriptor
 *  \details     -
 *  \param[in]   ctrlIdx      Identifier of Ethernet controller
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]   globalRingIdx    Identifier of the TX descriptor ring
 *               [range: 0 <= globalRingIdx < Eth_30_Tc3xx_GetSizeOfTxDescrHandling()]
 *  \param[in]   globalDescrIdx   Identifier of the TX descriptor within the ring
 *               [range: 0 <= globalDescrIdx < Eth_30_Tc3xx_GetSizeOfTxDescr()]
 *  \param[out]  timeStampPtr Transmission time stamp
 *  \context     ANY
 *  \synchronous TRUE
 *  \reentrant   TRUE for different TX descriptor
 *  \config      ETH_30_TC3XX_ENABLE_TIMESYNC == STD_ON
 *  \pre         -
 **********************************************************************************************************************/
ETH_30_TC3XX_LL_TIME_SYNC_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_TimeSync_GetTxTimeStamp(
        uint8                                                  ctrlIdx,
        Eth_30_Tc3xx_RingIdxOfTxTsContextType                  globalRingIdx,
        Eth_30_Tc3xx_DescrIdxOfTxTsContextType                 globalDescrIdx,
  P2VAR(Eth_TimeStampType, AUTOMATIC, ETH_30_TC3XX_VAR_NOINIT) timeStampPtr);

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_TimeSync_GetRxTimeStamp
 **********************************************************************************************************************/
/*! \brief       Retrieves the RX time stamp from the given descriptor
 *  \details     -
 *  \param[in]   ctrlIdx       Identifier of Ethernet controller
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]   globalRingIdx    Identifier of the RX descriptor ring
 *               [range: 0 <= globalRingIdx < Eth_30_Tc3xx_GetSizeOfRxDescrHandling()]
 *  \param[in]   globalDescrIdx   Identifier of the RX descriptor within the ring
 *               [range: 0 <= globalDescrIdx < Eth_30_Tc3xx_GetSizeOfRxDescr()]
 *  \param[out]  timeStampPtr  Reception time stamp
 *  \context     ANY
 *  \synchronous TRUE
 *  \reentrant   TRUE for different RX descriptor
 *  \config      ETH_30_TC3XX_ENABLE_TIMESYNC == STD_ON
 *  \pre         -
 **********************************************************************************************************************/
ETH_30_TC3XX_LL_TIME_SYNC_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_TimeSync_GetRxTimeStamp(
        uint8                                                           ctrlIdx,
        Eth_30_Tc3xx_RingIdxOfRxTsContextStackType                      globalRingIdx,
        Eth_30_Tc3xx_DescrIdxOfRxTsContextStackType                     globalDescrIdx,
  P2VAR(Eth_TimeStampType, AUTOMATIC, ETH_30_TC3XX_VAR_NOINIT)          timeStampPtr);

#  define ETH_30_TC3XX_STOP_SEC_CODE
#  include "MemMap.h" /* PRQA S 5087 1 */ /* MD_MSR_MemMap */

# endif /* ETH_30_TC3XX_ENABLE_TIMESYNC */

#endif /* ETH_30_TC3XX_LL_TIME_SYNC_IFC_INT_H */

/**********************************************************************************************************************
 *  END OF FILE: Eth_30_Tc3xx_LL_TimeSync_Ifc_Int.h
 *********************************************************************************************************************/
