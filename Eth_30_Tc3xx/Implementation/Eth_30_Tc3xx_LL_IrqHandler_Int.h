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
/*!        \file  Eth_30_Tc3xx_LL_IrqHandler_Int.h
 *        \brief  Private header of lower layer part of the interrupt handler
 *
 *      \details  Private inline implementations of the lower layer interrupt handler.
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

#if !defined (ETH_30_TC3XX_LL_IRQ_HANDLER_INT_H)
# define ETH_30_TC3XX_LL_IRQ_HANDLER_INT_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "Eth_30_Tc3xx_LL_IrqHandler_Ifc_Int.h"
# include "Eth_30_Tc3xx_Rx.h"
# include "Eth_30_Tc3xx_Tx.h"
# include "Eth_30_Tc3xx_Rx_Int.h"
# include "Eth_30_Tc3xx_Tx_Int.h"
# include "Eth_30_Tc3xx_LL_Tx_Int.h"
# include "Eth_30_Tc3xx_LL_Rx_Int.h"
# include "Eth_30_Tc3xx_Lcfg.h"

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/

# ifndef ETH_30_TC3XX_LL_IRQ_HANDLER_LOCAL /* COV_ETH_COMPATIBILITY */
#  define ETH_30_TC3XX_LL_IRQ_HANDLER_LOCAL                           static
# endif

# ifndef ETH_30_TC3XX_LL_IRQ_HANDLER_LOCAL_INLINE /* COV_ETH_COMPATIBILITY */
#  define ETH_30_TC3XX_LL_IRQ_HANDLER_LOCAL_INLINE                    LOCAL_INLINE
# endif

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
 *  Eth_30_Tc3xx_IrqHdlrTx()
 **********************************************************************************************************************/
/*! \brief       Interrupt function for all transmit interrupts
 *  \details     -
 *  \param[in]   ctrlIdx  Identifier of Eth controller
 *  \param[in]   queueIdx Identifier of Eth controller queue
 *  \param[in]   regAddr  Interrupt register offset of the receive / transmission queue register
 *  \context     ISR1|ISR2
 *  \reentrant   TRUE for different Eth controllers
 *  \synchronous TRUE
 *  \pre         -
 */
ETH_30_TC3XX_LL_IRQ_HANDLER_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IrqHdlrTx(
    uint8 ctrlIdx,
    uint8 queueIdx,
    Eth_30_Tc3xx_RegOffsetType regAddr);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_IrqHdlrRx()
 **********************************************************************************************************************/
/*! \brief       Interrupt function for all receive interrupts
 *  \details     -
 *  \param[in]   ctrlIdx  Identifier of Eth controller
 *  \param[in]   queueIdx Identifier of Eth controller queue
 *  \param[in]   regAddr  Interrupt register offset of the receive / transmission queue register
 *  \context     ISR1|ISR2
 *  \reentrant   TRUE for different Eth controllers
 *  \synchronous TRUE
 *  \pre         -
 */
ETH_30_TC3XX_LL_IRQ_HANDLER_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IrqHdlrRx(
    uint8 ctrlIdx,
    uint8 queueIdx,
    Eth_30_Tc3xx_RegOffsetType regAddr);

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_IrqHdlrTx
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
ETH_30_TC3XX_LL_IRQ_HANDLER_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IrqHdlrTx( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
  uint8 ctrlIdx,
  uint8 queueIdx,
  Eth_30_Tc3xx_RegOffsetType regAddr)
{
  /* #10 Clear respective interrupt flags */
  Eth_30_Tc3xx_Reg_Write(ctrlIdx, regAddr, ETH_30_TC3XX_REG_DMA_CHN_STATUS_NIS | ETH_30_TC3XX_REG_DMA_CHN_STATUS_TI);

  /* #20 Check if controller mode is active */
  if( Eth_30_Tc3xx_GetCtrlModeOfEthCtrlState(ctrlIdx) == ETH_MODE_ACTIVE )
  {
    Eth_30_Tc3xx_TxProcessMaxframesOfEthCtrlTc3xxType maxFrames;
    /* #210 As long as there is a Tx frame to be confirmed and maxFrames did not overflow */
    for (maxFrames = 0; maxFrames < Eth_30_Tc3xx_GetTxProcessMaxframesOfEthCtrlTc3xx(ctrlIdx); maxFrames++){
      if (Eth_30_Tc3xx_LL_IsTxQueuePending(ctrlIdx, queueIdx) == TRUE)
      {
        /* #2110 Trigger transmission confirmation and reception handling */
        if (Eth_30_Tc3xx_IsVlanIdBasedFrameQueuingEnabledOfEthCtrl(ctrlIdx) == FALSE)
        {
          Eth_30_Tc3xx_TxConfirmation(ctrlIdx);
        }
        else
        {
          Eth_30_Tc3xx_TxConfirmationFifo(ctrlIdx, queueIdx);
        }
      }
      else
      {
        break;
      }
    }
  }
} /* Eth_30_Tc3xx_IrqHdlrTx() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_IrqHdlrRx
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
ETH_30_TC3XX_LL_IRQ_HANDLER_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IrqHdlrRx( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
  uint8 ctrlIdx,
  uint8 queueIdx,
  Eth_30_Tc3xx_RegOffsetType regAddr)
{
  Eth_RxStatusType rxStatus = ETH_NOT_RECEIVED;

  /* #10 Clear respective interrupt flags */
  Eth_30_Tc3xx_Reg_Write(ctrlIdx, regAddr, ETH_30_TC3XX_REG_DMA_CHN_STATUS_NIS | ETH_30_TC3XX_REG_DMA_CHN_STATUS_RI);

  /* #20 Check if controller mode is active */
  if( Eth_30_Tc3xx_GetCtrlModeOfEthCtrlState(ctrlIdx) == ETH_MODE_ACTIVE )
  {
    /* #210 As long as there is a Rx frame to be received and maxFrames did not overflow */
    Eth_30_Tc3xx_RxProcessMaxframesOfEthCtrlTc3xxType maxFrames;
    for (maxFrames = 0; maxFrames < Eth_30_Tc3xx_GetRxProcessMaxframesOfEthCtrlTc3xx(ctrlIdx); maxFrames++){
      if ((Eth_30_Tc3xx_LL_IsRxQueuePending(ctrlIdx, queueIdx) == TRUE) ||
            (rxStatus == ETH_RECEIVED_MORE_DATA_AVAILABLE))
      {
        /* #2110 Trigger transmission confirmation and reception handling */
        if (Eth_30_Tc3xx_IsVlanIdBasedFrameQueuingEnabledOfEthCtrl(ctrlIdx) == FALSE)
        {
          Eth_30_Tc3xx_Receive(ctrlIdx, &rxStatus);                             /* SBSW_ETH_30_TC3XX_REF_OF_STACK_VAR */
        }
        else
        {
          Eth_30_Tc3xx_ReceiveFifo(ctrlIdx, queueIdx, &rxStatus);                             /* SBSW_ETH_30_TC3XX_REF_OF_STACK_VAR */
        }
      }
      else
      {
        break;
      }
    }
  }
} /* Eth_30_Tc3xx_IrqHdlrRx() */

# define ETH_30_TC3XX_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* ETH_30_TC3XX_LL_IRQ_HANDLER_INT_H */

/**********************************************************************************************************************
 *  END OF FILE: Eth_30_Tc3xx_LL_IrqHandler_Int.h
 *********************************************************************************************************************/
