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
/*!        \file  Eth_30_Tc3xx_LL_Tx_Ifc_Int.h
 *        \brief  Lower layer transceive private header file
 *
 *      \details  Private declarations of lower layer transceive part of component.
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
#if !defined (ETH_30_TC3XX_LL_TX_IFC_INT_H)
# define ETH_30_TC3XX_LL_TX_IFC_INT_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "Eth_30_Tc3xx_LL_Types_Int.h"
# include "Eth_30_Tc3xx_HwAccess_Int.h"

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/

# ifndef ETH_30_TC3XX_LL_TX_LOCAL /* COV_ETH_COMPATIBILITY */
#  define ETH_30_TC3XX_LL_TX_LOCAL                                       static
# endif

# ifndef ETH_30_TC3XX_LL_TX_LOCAL_INLINE /* COV_ETH_COMPATIBILITY */
#  define ETH_30_TC3XX_LL_TX_LOCAL_INLINE                                LOCAL_INLINE
# endif


/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

# define ETH_30_TC3XX_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_PrepareTxDescriptorForIpChecksumOffloading()
 *********************************************************************************************************************/
/*! \brief       Function for enabling the IP checksum offload option in a TX descriptor
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller for which checksum offloading shall be enabled
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]   globalDescrRingIdx     Index of descriptor ring for which checksum offloading shall be enabled
 *               [range: 0 <= globalDescrRingIdx < Eth_30_Tc3xx_GetSizeOfTxDescrHandling()]
 *  \param[in]   globalDescrIdx         Index of descriptor for which checksum offloading shall be enabled
 *               [range: 0 <= globalDescrIdx < Eth_30_Tc3xx_GetSizeOfTxDescr()]
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 */
ETH_30_TC3XX_LL_TX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_PrepareTxDescriptorForIpChecksumOffloading(
  uint8                               ctrlIdx,
  Eth_30_Tc3xx_TxDescrHandlingIterType globalDescrRingIdx,
  Eth_30_Tc3xx_TxDescrIterType         globalDescrIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_PrepareTxDescriptorForProtocolChecksumOffloading()
 *********************************************************************************************************************/
/*! \brief       Function for enabling the Protocol checksum offload option in a TX descriptor
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller for which checksum offloading shall be enabled
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]   globalDescrRingIdx     Index of descriptor ring for which checksum offloading shall be enabled
 *               [range: 0 <= globalDescrRingIdx < Eth_30_Tc3xx_GetSizeOfTxDescrHandling()]
 *  \param[in]   globalDescrIdx         Index of descriptor for which checksum offloading shall be enabled
 *               [range: 0 <= globalDescrIdx < Eth_30_Tc3xx_GetSizeOfTxDescr()]
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 */
ETH_30_TC3XX_LL_TX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_PrepareTxDescriptorForProtocolChecksumOffloading(
  uint8                               ctrlIdx,
  Eth_30_Tc3xx_TxDescrHandlingIterType globalDescrRingIdx,
  Eth_30_Tc3xx_TxDescrIterType         globalDescrIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_TriggerTransmission()
 *********************************************************************************************************************/
/*! \brief       Function for starting the transmission of a already prepared buffer an descriptor
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller for which the transmission shall be triggered
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]   globalDescrRingIdx     Index of descriptor ring for which the transmission shall be triggered
 *               [range: 0 <= globalDescrRingIdx < Eth_30_Tc3xx_GetSizeOfTxDescrHandling()]
 *  \param[in]   globalDescrIdx         Index of descriptor for which the transmission shall be triggered
 *               [range: 0 <= globalDescrIdx < Eth_30_Tc3xx_GetSizeOfTxDescr()]
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 */
ETH_30_TC3XX_LL_TX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_TriggerTransmission(
  uint8                               ctrlIdx,
  Eth_30_Tc3xx_TxDescrHandlingIterType globalDescrRingIdx,
  Eth_30_Tc3xx_TxDescrIterType         globalDescrIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_PrepareTxDescriptorForTimestamping()
 *********************************************************************************************************************/
/*! \brief       Function for enabling the timestamping option for a TX descriptor
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller for which timestamping shall be prepared
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]   globalDescrRingIdx     Index of descriptor ring for which timestamping shall be prepared
 *               [range: 0 <= globalDescrRingIdx < Eth_30_Tc3xx_GetSizeOfTxDescrHandling()]
 *  \param[in]   globalDescrIdx         Index of descriptor for which timestamping shall be prepared
 *               [range: 0 <= globalDescrIdx < Eth_30_Tc3xx_GetSizeOfTxDescr()]
 *  \param[in]   bufIdx           Index of buffer for which timestamping shall be prepared
 *               [range: 0 <= bufIdx < Eth_30_Tc3xx_GetSizeOfTxBufferState()]
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 */
ETH_30_TC3XX_LL_TX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_PrepareTxDescriptorForTimestamping(
  uint8                               ctrlIdx,
  Eth_30_Tc3xx_TxDescrHandlingIterType globalDescrRingIdx,
  Eth_30_Tc3xx_TxDescrIterType         globalDescrIdx,
  Eth_30_Tc3xx_TxBufferStateIterType   bufIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_PrepareTxDescriptorForTransmission()
 *********************************************************************************************************************/
/*! \brief       Function for doing all necessary settings to prepare a TX descriptor for transmission
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller to be used for transmission
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]   globalDescrRingIdx     Index of descriptor ring to be used for transmission
 *               [range: 0 <= globalDescrRingIdx < Eth_30_Tc3xx_GetSizeOfTxDescrHandling()]
 *  \param[in]   globalDescrIdx         Index of descriptor to be transmitted
 *               [range: 0 <= globalDescrIdx < Eth_30_Tc3xx_GetSizeOfTxDescr()]
 *  \param[in]   bufIdx           Index of buffer to be transmitted
 *               [range: 0 <= bufIdx < Eth_30_Tc3xx_GetSizeOfTxBufferState()]
 *  \param[in]   lenByte          Length of frame to be transmitted
 *  \param[in]   bufPtr           Pointer to buffer to be transmitted
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 */
ETH_30_TC3XX_LL_TX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_PrepareTxDescriptorForTransmission(
          uint8                                                                   ctrlIdx,
          Eth_30_Tc3xx_TxDescrHandlingIterType                                    globalDescrRingIdx,
          Eth_30_Tc3xx_TxDescrIterType                                            globalDescrIdx,
          Eth_30_Tc3xx_TxBufferStateIterType                                      bufIdx,
          uint16                                                                  lenByte,
  P2CONST(uint8,                              AUTOMATIC, ETH_30_TC3XX_VAR_NOINIT) bufPtr);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_RechargeTxDescriptor()
 *********************************************************************************************************************/
/*! \brief       Function for recharging a TX descriptor, after the transmission of a frame was finished
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller for which the descriptor shall be recharged
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]   globalDescrRingIdx     Index of descriptor ring for which the descriptor shall be recharged
 *               [range: 0 <= globalDescrRingIdx < Eth_30_Tc3xx_GetSizeOfTxDescrHandling()]
 *  \param[in]   globalDescrIdx         Index of descriptor which shall be recharged
 *               [range: 0 <= globalDescrIdx < Eth_30_Tc3xx_GetSizeOfTxDescr()]
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 */
ETH_30_TC3XX_LL_TX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_RechargeTxDescriptor(
  uint8                               ctrlIdx,
  Eth_30_Tc3xx_TxDescrHandlingIterType globalDescrRingIdx,
  Eth_30_Tc3xx_TxDescrIterType         globalDescrIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_ResetTimestampingInTxDescriptor
 *********************************************************************************************************************/
/*! \brief       Resets the timestamping request for the given TX descriptor
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller for which the timestamping request shall be reset
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]   globalDescrRingIdx     Index of descriptor ring for which the timestamping request shall be reset
 *               [range: 0 <= globalDescrRingIdx < Eth_30_Tc3xx_GetSizeOfTxDescrHandling()]
 *  \param[in]   globalDescrIdx         Index of descriptor for which the timestamping request shall be reset
 *               [range: 0 <= globalDescrIdx < Eth_30_Tc3xx_GetSizeOfTxDescr()]
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 */
ETH_30_TC3XX_LL_TX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_ResetTimestampingInTxDescriptor(
  uint8                               ctrlIdx,
  Eth_30_Tc3xx_TxDescrHandlingIterType globalDescrRingIdx,
  Eth_30_Tc3xx_TxDescrIterType         globalDescrIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_IsTransmissionComplete()
 *********************************************************************************************************************/
/*! \brief       Function for checking if previous frame transmission completed
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller to be checked for completed frame transmission
 *  \return      E_NOT_OK - Previous frame transmission not completed within time out
 *  \return      E_OK - Previous frame transmission completed within time out
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 */
ETH_30_TC3XX_LL_TX_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_IsTransmissionComplete(
    uint8 ctrlIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_SetTxEvents()
 *********************************************************************************************************************/
/*! \brief       Sets the TX events for the respective descriptor rings
 *  \details     Function sets TX events by calling Eth_30_Tc3xx_SetTxEvent() for each TX descriptor ring having a
 *               pending TX event (respective interrupt flag set).
 *  \param[in]   ctrlIdx          Index of controller pending TX events shall be queried for
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 */
ETH_30_TC3XX_LL_TX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_SetTxEvents(
  uint8 ctrlIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_IsTxDescriptorOwnedByDriver()
 *********************************************************************************************************************/
/*! \brief       Function for retrieving the information, if a TX descriptor is owned by DMA or driver
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller for which the owner of a descriptor shall be checked
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]   globalDescrRingIdx     Index of descriptor ring for which the owner of a descriptor shall be checked
 *               [range: 0 <= globalDescrRingIdx < Eth_30_Tc3xx_GetSizeOfTxDescrHandling()]
 *  \param[in]   globalDescrIdx         Index of descriptor for which the owner shall be checked
 *               [range: 0 <= globalDescrIdx < Eth_30_Tc3xx_GetSizeOfTxDescr()]
 *  \return      TRUE - descriptor is owned by driver
 *  \return      FALSE - descriptor is owned by DMA
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 */
ETH_30_TC3XX_LL_TX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_IsTxDescriptorOwnedByDriver(
  uint8                                ctrlIdx,
  Eth_30_Tc3xx_TxDescrHandlingIterType globalDescrRingIdx,
  Eth_30_Tc3xx_TxDescrIterType         globalDescrIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_IsTxPending
 **********************************************************************************************************************/
/*! \brief       Checks for pending Tx events
 *  \details     -
 *  \param[in]   ctrlIdx  Identifier of the Ethernet controller.
 *  \return      FALSE - There is no Tx event pending that must be confirmed
 *  \return      TRUE - There is at least one Tx event pending that must be confirmed
 *  \context     TASK|ISR1|ISR2
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 */
ETH_30_TC3XX_LL_TX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_IsTxPending(
    uint8 ctrlIdx);

 /**********************************************************************************************************************
  *  Eth_30_Tc3xx_LL_IsTxQueuePending
 **********************************************************************************************************************/
 /*! \brief       Checks for pending Tx Queue events
  *  \details     The function checks for pending Tx Queue events and sets respective Tx event flags
  *  \param[in]   ctrlIdx       Identifier of the Ethernet controller.
  *  \param[in]   globalDescrRingIdx  Index of descriptor ring.
  *  \return      FALSE - There is no Tx event pending that must be confirmed
  *  \return      TRUE - There is at least one Tx Queue event pending that must be confirmed
  *  \context     TASK|ISR1|ISR2
  *  \synchronous TRUE
  *  \reentrant   FALSE
  *  \pre         -
  */
 ETH_30_TC3XX_LL_TX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_IsTxQueuePending(
     uint8 ctrlIdx,
     Eth_30_Tc3xx_TxDescrRingProcIterType globalDescrRingIdx);

# define ETH_30_TC3XX_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* ETH_30_TC3XX_LL_TX_IFC_INT_H */

/**********************************************************************************************************************
 *  END OF FILE: Eth_30_Tc3xx_LL_Tx_Ifc_Int.h
 *********************************************************************************************************************/
