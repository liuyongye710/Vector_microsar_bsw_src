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
/*!        \file  Eth_30_Tc3xx_IrqHandler_Ifc_Int.h
 *        \brief  Declaration of private Ethernet controller interrupt handler implementation
 *
 *      \details  Provides access to the private interrupt handler related API of the Ethernet controller driver.
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

#if !defined (ETH_30_TC3XX_IRQ_HANDLER_IFC_INT_H)
# define ETH_30_TC3XX_IRQ_HANDLER_IFC_INT_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "Eth_30_Tc3xx_Types_Int.h"

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/

# ifndef ETH_30_TC3XX_IRQ_HANDLER_LOCAL /* COV_ETH_COMPATIBILITY */
#  define ETH_30_TC3XX_IRQ_HANDLER_LOCAL                              static
# endif

# if !defined(ETH_30_TC3XX_IRQ_HANDLER_LOCAL_INLINE) /* COV_ETH_COMPATIBILITY */
#  define ETH_30_TC3XX_IRQ_HANDLER_LOCAL_INLINE                       LOCAL_INLINE
# endif /* ETH_30_TC3XX_IRQ_HANDLER_LOCAL_INLINE */

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 **********************************************************************************************************************/

# define ETH_30_TC3XX_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_GetAndClearHighestPrioPendingEventDescrRing
 **********************************************************************************************************************/
/*! \brief        Retrieves the descriptor ring related to the highest priority event pending and clears the event
 *  \details      -
 *  \param[in]    eventsPtr     Bit mask having bits set representing an event
 *  \return       Descriptor ring with the highest priority event, if no event is pending -> invalid descriptor ring
 *                value
 *  \context      ANY
 *  \reentrant    TRUE for different events
 *  \synchronous  TRUE
 *  \pre          -
 */
ETH_30_TC3XX_IRQ_HANDLER_LOCAL_INLINE FUNC(uint8, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetAndClearHighestPrioPendingEventDescrRing(
  P2VAR(uint16, AUTOMATIC, AUTOMATIC) eventsPtr);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_GetHighestPrioPendingEventDescrRing
 **********************************************************************************************************************/
/*! \brief        Retrieve the descriptor ring related to the highest priority event pending
 *  \details      -
 *  \param[in]    eventsPtr     Bit mask having bits set representing an event
 *  \param[out]   bitMaskPtr    Bit mask that can be used to clear the event
 *  \return       Descriptor ring with the highest priority event, if no event is pending -> invalid descriptor ring
 *                value
 *  \context      ANY
 *  \reentrant    TRUE for different events
 *  \synchronous  TRUE
 *  \pre          -
 */
ETH_30_TC3XX_IRQ_HANDLER_LOCAL_INLINE FUNC(uint8, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetHighestPrioPendingEventDescrRing(
  P2CONST(uint16, AUTOMATIC, AUTOMATIC) eventsPtr,
  P2VAR(uint16, AUTOMATIC, AUTOMATIC) bitMaskPtr);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_ClearPendingEventDescrRing
 **********************************************************************************************************************/
/*! \brief        Clears the event in the given events variable according to the given bit mask
 *  \details      -
 *  \param[in]    eventsPtr     Bit mask having bits set representing an event
 *  \param[out]   bitMaskPtr    Bit mask that to clear the event
 *  \context      ANY
 *  \reentrant    TRUE for different events
 *  \synchronous  TRUE
 *  \pre          -
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_IRQ_HANDLER_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_ClearPendingEventDescrRing(
  P2VAR(uint16, AUTOMATIC, AUTOMATIC) eventsPtr,
        uint16                        bitMask);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_SetRxEvent
 **********************************************************************************************************************/
/*! \brief        Sets an RX event for the given reception descriptor ring
 *  \details      -
 *  \param[in]    ctrlIdx       Identifier of the Ethernet controller.
 *                              [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]    descrRingIdx  Identifier of the reception descriptor ring of the Ethernet controller with index
 *                              ctrlIdx (local index).
 *                              [range: 0 <= (descrdescrRingIdx -
 *                              Eth_30_Tc3xx_GetRxDescrHandlingStartIdxOfEthCtrl(ctrlIdx)) <= descrdescrRingIdx <
 *                              Eth_30_Tc3xx_GetRxDescrHandlingEndIdxOfEthCtrl(ctrlIdx) -
 *                              Eth_30_Tc3xx_GetRxDescrHandlingStartIdxOfEthCtrl(ctrlIdx)]
 *  \context      ANY
 *  \reentrant    TRUE
 *  \synchronous  TRUE
 *  \pre          -
 */
ETH_30_TC3XX_IRQ_HANDLER_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_SetRxEvent(
  uint8 ctrlIdx,
  Eth_30_Tc3xx_RxDescrRingProcIterType descrRingIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_GetAndClearHighestPrioPendingRxEventDescrRing
 **********************************************************************************************************************/
/*! \brief        Retrieves the reception descriptor ring related to the highest priority RX event pending and clears
 *                the event
 *  \details      -
 *  \param[in]    ctrlIdx       Identifier of the Ethernet controller
 *                [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \return       Descriptor ring with the highest priority event, if no event is pending -> invalid descriptor ring
 *                value. (local descriptor ring index)
 *                [valid range: 0 <= (descrdescrRingIdx -
 *                Eth_30_Tc3xx_GetRxDescrHandlingStartIdxOfEthCtrl(ctrlIdx)) <= descrdescrRingIdx <
 *                Eth_30_Tc3xx_GetRxDescrHandlingEndIdxOfEthCtrl(ctrlIdx) -
 *                Eth_30_Tc3xx_GetRxDescrHandlingStartIdxOfEthCtrl(ctrlIdx)]
 *  \context      ANY
 *  \reentrant    TRUE for different Ethernet controllers
 *  \synchronous  TRUE
 *  \pre          -
 */
ETH_30_TC3XX_IRQ_HANDLER_LOCAL_INLINE FUNC(uint8, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetAndClearHighestPrioPendingRxEventDescrRing(
  uint8 ctrlIdx); /* PRQA S 0779 */ /* MD_MSR_5.1_779 */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_GetHighestPrioPendingRxEventDescrRing
 **********************************************************************************************************************/
/*! \brief        Retrieves the reception descriptor ring related to the highest priority RX event pending
 *  \details      -
 *  \param[in]    ctrlIdx       Identifier of the Ethernet controller
 *                [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \return       Descriptor ring with the highest priority event, if no event is pending -> invalid descriptor ring
 *                value. (local descriptor ring index)
 *                [valid range: 0 <= (descrdescrRingIdx -
 *                Eth_30_Tc3xx_GetRxDescrHandlingStartIdxOfEthCtrl(ctrlIdx)) <= descrdescrRingIdx <
 *                Eth_30_Tc3xx_GetRxDescrHandlingEndIdxOfEthCtrl(ctrlIdx) -
 *                Eth_30_Tc3xx_GetRxDescrHandlingStartIdxOfEthCtrl(ctrlIdx)]
 *  \context      ANY
 *  \reentrant    TRUE for different Ethernet controllers
 *  \synchronous  TRUE
 *  \pre          -
 */
ETH_30_TC3XX_IRQ_HANDLER_LOCAL_INLINE FUNC(uint8, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetHighestPrioPendingRxEventDescrRing(
  uint8 ctrlIdx); /* PRQA S 0779 */ /* MD_MSR_Rule5.2 */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_SetTxEvent
 **********************************************************************************************************************/
/*! \brief        Sets an TX event for the given transmission descriptor ring
 *  \details      -
 *  \param[in]    ctrlIdx       Identifier of the Ethernet controller
 *                [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]    descrRingIdx  Identifier of the transmission descriptor ring of the Ethernet controller with index
 *                              ctrlIdx (local index).
 *                              [range: 0 <= (descrdescrRingIdx -
 *                              Eth_30_Tc3xx_GetTxDescrHandlingStartIdxOfEthCtrl(ctrlIdx)) <= descrdescrRingIdx <
 *                              Eth_30_Tc3xx_GetTxDescrHandlingEndIdxOfEthCtrl(ctrlIdx) -
 *                              Eth_30_Tc3xx_GetTxDescrHandlingStartIdxOfEthCtrl(ctrlIdx)]
 *  \context      ANY
 *  \reentrant    TRUE
 *  \synchronous  TRUE
 *  \pre          -
 */
ETH_30_TC3XX_IRQ_HANDLER_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_SetTxEvent(
  uint8 ctrlIdx,
  Eth_30_Tc3xx_TxDescrRingProcIterType descrRingIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_GetAndClearHighestPrioPendingTxEventDescrRing
 **********************************************************************************************************************/
/*! \brief        Retrieves the transmission descriptor ring related to the highest priority TX event pending and clears
*                 the event
 *  \details      -
 *  \param[in]    ctrlIdx       Identifier of the Ethernet controller
 *                [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \return       Descriptor ring with the highest priority event, if no event is pending -> invalid descriptor ring
 *                value.
 *                [valid range: 0 <= (descrdescrRingIdx -
 *                Eth_30_Tc3xx_GetTxDescrHandlingStartIdxOfEthCtrl(ctrlIdx)) <= descrdescrRingIdx <
 *                Eth_30_Tc3xx_GetTxDescrHandlingEndIdxOfEthCtrl(ctrlIdx) -
 *                Eth_30_Tc3xx_GetTxDescrHandlingStartIdxOfEthCtrl(ctrlIdx)]
 *  \context      ANY
 *  \reentrant    TRUE for different Ethernet controllers
 *  \synchronous  TRUE
 *  \pre          -
 */
ETH_30_TC3XX_IRQ_HANDLER_LOCAL_INLINE FUNC(uint8, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetAndClearHighestPrioPendingTxEventDescrRing(
  uint8 ctrlIdx); /* PRQA S 0779 */ /* MD_MSR_5.1_779 */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_ProcessIsr
 **********************************************************************************************************************/
/*! \brief        Processes the interrupt events of a specific interrupt service routine
 *  \details      Function processes the interrupt event handler functions of a specific interrupt service routine.
 *                Additionally - if enabled during configuration - pre- and post-ISR-User-Functions are processed too.
 *  \param[in]    ctrlIdx    Module local identifier of the controller
 *  \param[in]    isrIdx     Interrupt service routine identifier
 *  \context      ISR1|ISR2
 *  \reentrant    TRUE for different interrupt service routines
 *  \pre          -
 **********************************************************************************************************************/
FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_ProcessIsr(
  uint8 ctrlIdx,
  uint8 isrIdx);

# define ETH_30_TC3XX_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* ETH_30_TC3XX_IRQ_HANDLER_IFC_INT_H */

/**********************************************************************************************************************
 *  END OF FILE: Eth_30_Tc3xx_IrqHandler_Int.h
 *********************************************************************************************************************/
