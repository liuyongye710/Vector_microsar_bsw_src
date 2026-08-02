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
/*!        \file  Eth_30_Tc3xx_LL_Rx_Ifc_Int.h
 *        \brief  Lower layer reception private header file
 *
 *      \details  Private declarations of lower layer reception part of component.
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
#if !defined (ETH_30_TC3XX_LL_RX_IFC_INT_H)
# define ETH_30_TC3XX_LL_RX_IFC_INT_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "Eth_30_Tc3xx_LL_Types_Int.h"
# include "Eth_30_Tc3xx_HwAccess_Int.h"
# include "Eth_30_Tc3xx_LL_CtrlModeHdl_Ifc_Int.h"

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/

# ifndef ETH_30_TC3XX_LL_RX_LOCAL /* COV_ETH_COMPATIBILITY */
#  define ETH_30_TC3XX_LL_RX_LOCAL                                       static
# endif

# ifndef ETH_30_TC3XX_LL_RX_LOCAL_INLINE /* COV_ETH_COMPATIBILITY */
#  define ETH_30_TC3XX_LL_RX_LOCAL_INLINE                                LOCAL_INLINE
# endif

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

# define ETH_30_TC3XX_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_IsRxDescriptorOwnedByDriver()
 *********************************************************************************************************************/
/*! \brief       Function for retrieving the information, if a RX descriptor is owned by DMA or driver
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller for which the owner of a descriptor shall be checked
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]   globalDescrRingIdx     Index of descriptor ring for which the owner of a descriptor shall be checked
 *               [range: 0 <= globalDescrRingIdx < Eth_30_Tc3xx_GetSizeOfRxDescrHandling()]
 *  \param[in]   globalDescrIdx         Index of descriptor for which the owner shall be checked
 *               [range: 0 <= globalDescrIdx < Eth_30_Tc3xx_GetSizeOfEthRxDescr()]
 *  \return      TRUE - descriptor is owned by driver
 *  \return      FALSE - descriptor is owned by DMA
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 */
ETH_30_TC3XX_LL_RX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_IsRxDescriptorOwnedByDriver(
  uint8                                ctrlIdx,
  Eth_30_Tc3xx_RxDescrHandlingIterType globalDescrRingIdx,
  Eth_30_Tc3xx_RxDescrIterType         globalDescrIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_IsErrorInRxDescriptor()
 *********************************************************************************************************************/
/*! \brief       Function for retrieving the information, if a error flag was set in a RX descriptor
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller for which the owner of a descriptor shall be checked
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]   globalDescrRingIdx     Index of descriptor ring for which the owner of a descriptor shall be checked
 *               [range: 0 <= globalDescrRingIdx < Eth_30_Tc3xx_GetSizeOfRxDescrHandling()]
 *  \param[in]   globalDescrIdx         Index of descriptor for which the owner shall be checked
 *               [range: 0 <= globalDescrIdx < Eth_30_Tc3xx_GetSizeOfRxDescr()]
 *  \return      TRUE - error flag is set in descriptor
 *  \return      FALSE - no error flags is set in descriptor
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 */
ETH_30_TC3XX_LL_RX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_IsErrorInRxDescriptor(
  uint8                                ctrlIdx,
  Eth_30_Tc3xx_RxDescrHandlingIterType globalDescrRingIdx,
  Eth_30_Tc3xx_RxDescrIterType         globalDescrIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_SetRxEvents()
 *********************************************************************************************************************/
/*! \brief       Sets the RX events for the respective descriptor rings
 *  \details     Functions sets RX events by calling Eth_30_Tc3xx_SetRxEvent() for each RX descriptor ring having a
 *               pending RX event (respective interrupt flag set).
 *  \param[in]   ctrlIdx          Index of controller pending RX events shall be queried for
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 */
ETH_30_TC3XX_LL_RX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_SetRxEvents(
  uint8 ctrlIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_RechargeRxDescriptor()
 *********************************************************************************************************************/
/*! \brief       Function for recharging a RX descriptor, after the reception of a frame was finished
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller for which the descriptor shall be recharged
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]   globalDescrRingIdx     Index of descriptor ring for which the descriptor shall be recharged
 *               [range: 0 <= globalDescrRingIdx < Eth_30_Tc3xx_GetSizeOfRxDescrHandling()]
 *  \param[in]   globalDescrIdx         Index of descriptor which shall be recharged
 *               [range: 0 <= globalDescrIdx < Eth_30_Tc3xx_GetSizeOfRxDescr()]
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 */
ETH_30_TC3XX_LL_RX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_RechargeRxDescriptor(
  uint8                                ctrlIdx,
  Eth_30_Tc3xx_RxDescrHandlingIterType globalDescrRingIdx,
  Eth_30_Tc3xx_RxDescrIterType         globalDescrIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_AdaptRxDescriptorRingAfterReception
 *********************************************************************************************************************/
/*! \brief       Function for HW specific RX descriptor operations which are necessary after a frame has been received
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller for which the descriptor shall be adapted
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]   globalDescrRingIdx     Index of descriptor ring for which the descriptor shall be adapted
 *               [range: 0 <= globalDescrRingIdx < Eth_30_Tc3xx_GetSizeOfRxDescrHandling()]
 *  \param[in]   globalDescrIdx        Index of descriptor which shall be adapted
 *               [range: 0 <= globalDescrIdx < Eth_30_Tc3xx_GetSizeOfRxDescr()]
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 */
ETH_30_TC3XX_LL_RX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_AdaptRxDescriptorRingAfterReception(
  uint8                                ctrlIdx,
  Eth_30_Tc3xx_RxDescrHandlingIterType globalDescrRingIdx,
  Eth_30_Tc3xx_RxDescrIterType         globalDescrIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_GetFrameLengthFromRxDescriptor
 *********************************************************************************************************************/
/*! \brief       Function for retrieving the frame length of a received frame from a RX descriptor
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller for which the frame length shall be retrieved
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]   globalDescrRingIdx     Index of descriptor ring for which the frame length shall be retrieved
 *               [range: 0 <= globalDescrRingIdx < Eth_30_Tc3xx_GetSizeOfRxDescrHandling()]
 *  \param[in]   globalDescrIdx         Index of descriptor for which the frame length shall be retrieved
 *               [range: 0 <= globalDescrIdx < Eth_30_Tc3xx_GetSizeOfRxDescr()]
 *  \return      Length extracted from a RX descriptor
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 */
ETH_30_TC3XX_LL_RX_LOCAL_INLINE FUNC(uint16, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_GetFrameLengthFromRxDescriptor(
  uint8                                ctrlIdx,
  Eth_30_Tc3xx_RxDescrHandlingIterType globalDescrRingIdx,
  Eth_30_Tc3xx_RxDescrIterType         globalDescrIdx);
/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_IsRxPending
 **********************************************************************************************************************/
/*! \brief       Checks for pending Rx events
 *  \details     -
 *  \param[in]   ctrlIdx  Identifier of the Ethernet controller.
 *  \return      FALSE - There is no Rx event pending that must be notified
 *  \return      TRUE - There is at least one Rx event pending that must be notified
 *  \context     TASK|ISR1|ISR2
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 */
ETH_30_TC3XX_LL_RX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_IsRxPending(
    uint8 ctrlIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_IsRxQueuePending
 **********************************************************************************************************************/
/*! \brief       Checks for pending Rx Queue events
 *  \details     The function checks for pending Rx Queue events and sets respective Rx event flags
 *  \param[in]   ctrlIdx  Identifier of the Ethernet controller.
 *  \param[in]   globalDescrRingIdx  Index of descriptor ring.
 *  \return      FALSE - There is no Rx event pending that must be notified
 *  \return      TRUE - There is at least one Rx event pending that must be notified
 *  \context     TASK|ISR1|ISR2
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 */
ETH_30_TC3XX_LL_RX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_IsRxQueuePending(
    uint8 ctrlIdx,
    Eth_30_Tc3xx_RxDescrRingProcIterType globalDescrRingIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_IsRxFifoTransferredToSystem()
 *********************************************************************************************************************/
/*! \brief       Function for checking if data in Rx FIFO is transferred to system memory
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller to be checked if data in Rx FIFO is transferred to system memory
 *  \return      E_NOT_OK - Data in Rx FIFO was not transferred to system within time out
 *  \return      E_OK - Data in Rx FIFO was transferred to system within time out
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 */
ETH_30_TC3XX_LL_RX_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_IsRxFifoTransferredToSystem(
    uint8 ctrlIdx);

# define ETH_30_TC3XX_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* ETH_30_TC3XX_LL_RX_IFC_INT_H */
/**********************************************************************************************************************
 *  END OF FILE: Eth_30_Tc3xx_LL_Rx_Ifc_Int.h
 *********************************************************************************************************************/
