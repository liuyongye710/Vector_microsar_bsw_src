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
/*!        \file  Eth_30_Tc3xx_LL_CtrlModeHdl_Int.h
 *        \brief  Controller mode handling private header file
 *
 *      \details  Private inline implementations of controller mode handling of component.
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
#if !defined (ETH_30_TC3XX_LL_CTRLMODEHDL_INT_H)
# define ETH_30_TC3XX_LL_CTRLMODEHDL_INT_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "Eth_30_Tc3xx_LL_CtrlModeHdl_Ifc_Int.h"
# include "Eth_30_Tc3xx_LL_Rx_Int.h"
# include "Eth_30_Tc3xx_LL_Tx_Int.h"
# include "Eth_30_Tc3xx_LL_Int.h"
# include "Eth_30_Tc3xx_Int.h"
# include "Eth_30_Tc3xx_Lcfg.h"

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/

# define ETH_30_TC3XX_ALIGN_PADDING                                   (2u)

# define ETH_30_TC3XX_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  Eth_30_Eth_30_Tc3xx_LL_ResetKernel()
 *********************************************************************************************************************/
/*! \brief       Function for resetting the Kernel
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller which shall be reset
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \return      E_OK - Kernel reset successfully performed
 *  \return      E_NOT_OK - Kernel reset timeout
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 */
ETH_30_TC3XX_LL_CTRL_MODE_HDL_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_ResetKernel(
  uint8 ctrlIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_DisableInterrupts()
 *********************************************************************************************************************/
/*! \brief       Function for disabling the Ethernet depended interrupts
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller which shall be reset
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 */
ETH_30_TC3XX_LL_CTRL_MODE_HDL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_DisableInterrupts(
  uint8 ctrlIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_SetRxDescriptorBaseAdresses()
 *********************************************************************************************************************/
/*! \brief       Function for setting the descriptor base addresses of the Rx queues
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller which shall be reset
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 */
ETH_30_TC3XX_LL_CTRL_MODE_HDL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_SetRxDescriptorBaseAddresses(
  uint8 ctrlIdx);


/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_SetTxDescriptorBaseAdresses()
 *********************************************************************************************************************/
/*! \brief       Function for setting the descriptor base addresses of the Tx queues
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller which shall be reset
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 */
ETH_30_TC3XX_LL_CTRL_MODE_HDL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_SetTxDescriptorBaseAddresses(
  uint8 ctrlIdx);

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_ResetKernel
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_LL_CTRL_MODE_HDL_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_ResetKernel(
    uint8 ctrlIdx)
{
  Std_ReturnType retVal = E_OK;
  uint32_least hwLoopTimeout = 0uL;
  /* #10 Apply a kernel reset to the GETH module:
   *       Write to corresponding RST bits of KRST0/1 registers to request a kernel reset. */
  Eth_30_Tc3xx_Reg_Write_Protected(ctrlIdx, ETH_30_TC3XX_REG_OFFS_KERNEL_RESET_REGISTER0,
                                            ETH_30_TC3XX_REG_KERNEL_RESET_REGISTER0_RST);
  Eth_30_Tc3xx_Reg_Write_Protected(ctrlIdx, ETH_30_TC3XX_REG_OFFS_KERNEL_RESET_REGISTER1,
                                            ETH_30_TC3XX_REG_KERNEL_RESET_REGISTER1_RST);

  /* #20 Check if kernel reset is finished */
  while (Eth_30_Tc3xx_Reg_ReadBits_Protected(ctrlIdx, ETH_30_TC3XX_REG_OFFS_KERNEL_RESET_REGISTER0,
                                                      ETH_30_TC3XX_REG_KERNEL_RESET_REGISTER0_RSTSTAT) == 0uL)
  {
    /* still busy */
    if (hwLoopTimeout > Eth_30_Tc3xx_GetResetLoopCyclesOfEthCtrl(ctrlIdx))
    {
      ETH_30_TC3XX_DEM_REPORT_ERROR_STATUS_ETH_E_ACCESS(ctrlIdx);
      retVal = E_NOT_OK;
      break;
    }
    hwLoopTimeout++;
  }

  /* #30 The reset status flag KRST0.RSTSTAT may be cleared afterwards
   *     by writing to bit CLR in the KRSTCLR register */
  Eth_30_Tc3xx_Reg_Write_Protected(ctrlIdx, ETH_30_TC3XX_REG_OFFS_KERNEL_RESET_STATUS_CLEAR,
                                            ETH_30_TC3XX_REG_OFFS_KERNEL_RESET_STATUS_CLEAR_CLR);

  return retVal;
} /* Eth_30_Tc3xx_LL_ResetKernel() */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_DisableInterrupts
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_LL_CTRL_MODE_HDL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_DisableInterrupts(
    uint8 ctrlIdx)
{
  /* #10 Globally disable interrupts
   *     (No Eth-ISR pending/running at the moment this function is called) */
  Eth_30_Tc3xx_Reg_Write(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MAC_INT_EN, 0u);
  Eth_30_Tc3xx_Reg_Write(ctrlIdx, ETH_30_TC3XX_REG_OFFS_DMA_CH0_INT_EN, 0u);
  if (Eth_30_Tc3xx_IsMultiQueueConfigEnabledOfEthCtrl(ctrlIdx) == TRUE)
  {
    Eth_30_Tc3xx_Reg_Write(ctrlIdx, ETH_30_TC3XX_REG_OFFS_DMA_CH1_INT_EN, 0u);
    if(Eth_30_Tc3xx_GetAmountOfRxQueuesOfEthCtrl(ctrlIdx) > ETH_30_TC3XX_LL_QOS_2_QUEUES_CONFIGURED)
    {
      Eth_30_Tc3xx_Reg_Write(ctrlIdx, ETH_30_TC3XX_REG_OFFS_DMA_CH2_INT_EN, 0u);
    }
    if(Eth_30_Tc3xx_GetAmountOfRxQueuesOfEthCtrl(ctrlIdx) > ETH_30_TC3XX_LL_QOS_3_QUEUES_CONFIGURED)
    {
      Eth_30_Tc3xx_Reg_Write(ctrlIdx, ETH_30_TC3XX_REG_OFFS_DMA_CH3_INT_EN, 0u);
    }
  }
} /* Eth_30_Tc3xx_LL_DisableInterrupts() */


/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_SetRxDescriptorBaseAddresses()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_LL_CTRL_MODE_HDL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_SetRxDescriptorBaseAddresses(
  uint8 ctrlIdx)
{
  uint8_least queueIdx;
  uint8 hwQueueIdx;

  /* #10 Iterate over used Rx queues */
  for (queueIdx = Eth_30_Tc3xx_GetRxDescrHandlingStartIdxOfEthCtrl(ctrlIdx);
       queueIdx < Eth_30_Tc3xx_GetRxDescrHandlingEndIdxOfEthCtrl(ctrlIdx); queueIdx++)
  {
    Eth_30_Tc3xx_RegOffsetType regOffsetRxDescRingLen;
    Eth_30_Tc3xx_RegOffsetType regOffsetRxDescStartAddr;
    Eth_30_Tc3xx_RegOffsetType regOffsetRxDescTailAddr;

    /* #110 Get Rx descriptor counts and addresses */
    uint32 rxDescCount = (uint32)Eth_30_Tc3xx_GetRxDescrEndIdxOfRxDescrHandling(queueIdx) -
                         (uint32)Eth_30_Tc3xx_GetRxDescrStartIdxOfRxDescrHandling(queueIdx);

    /* PRQA S 0306 3 */ /* MD_Eth_30_Tc3xx_0306 */
    uint32 rxDescAddr = (uint32) Eth_30_Tc3xx_GetAddrRxDescr(
                                 Eth_30_Tc3xx_GetRxDescrStartIdxOfRxDescrHandling(queueIdx));
    uint32 rxDescLastAddr = (uint32) Eth_30_Tc3xx_GetAddrRxDescr(
                                    (Eth_30_Tc3xx_GetRxDescrEndIdxOfRxDescrHandling(queueIdx) - 1u ));

    hwQueueIdx = (uint8)(queueIdx - Eth_30_Tc3xx_GetRxDescrHandlingStartIdxOfEthCtrl(ctrlIdx));
    switch (hwQueueIdx)
    {
    case ETH_30_TC3XX_LL_MID_0_PRIO_QUEUE_IDX:
      regOffsetRxDescRingLen   = ETH_30_TC3XX_REG_OFFS_DMA_CH1_RX_DESC_RING_LEN;
      regOffsetRxDescStartAddr = ETH_30_TC3XX_REG_OFFS_DMA_CH1_RX_DESC_LIST_ADDR;
      regOffsetRxDescTailAddr  = ETH_30_TC3XX_REG_OFFS_DMA_CH1_RX_DESC_TAIL_PTR;
      break;
    case ETH_30_TC3XX_LL_MID_1_PRIO_QUEUE_IDX:
      regOffsetRxDescRingLen   = ETH_30_TC3XX_REG_OFFS_DMA_CH2_RX_DESC_RING_LEN;
      regOffsetRxDescStartAddr = ETH_30_TC3XX_REG_OFFS_DMA_CH2_RX_DESC_LIST_ADDR;
      regOffsetRxDescTailAddr  = ETH_30_TC3XX_REG_OFFS_DMA_CH2_RX_DESC_TAIL_PTR;
      break;
    case ETH_30_TC3XX_LL_HIGH_PRIO_QUEUE_IDX:
      regOffsetRxDescRingLen   = ETH_30_TC3XX_REG_OFFS_DMA_CH3_RX_DESC_RING_LEN;
      regOffsetRxDescStartAddr = ETH_30_TC3XX_REG_OFFS_DMA_CH3_RX_DESC_LIST_ADDR;
      regOffsetRxDescTailAddr  = ETH_30_TC3XX_REG_OFFS_DMA_CH3_RX_DESC_TAIL_PTR;
      break;
    default:
      regOffsetRxDescRingLen   = ETH_30_TC3XX_REG_OFFS_DMA_CH0_RX_DESC_RING_LEN;
      regOffsetRxDescStartAddr = ETH_30_TC3XX_REG_OFFS_DMA_CH0_RX_DESC_LIST_ADDR;
      regOffsetRxDescTailAddr  = ETH_30_TC3XX_REG_OFFS_DMA_CH0_RX_DESC_TAIL_PTR;
      break;
    }

    /* #120 Announce ring length to hardware */
    Eth_30_Tc3xx_Reg_Write(ctrlIdx, regOffsetRxDescRingLen, ETH_30_TC3XX_REG_DMA_CHN_RX_DESC_RING_LEN &
                            (Eth_30_Tc3xx_RegWidthType)((2u * rxDescCount) - 1u)); /* -1 described in manual */

    /* #130 Announce descriptor ring to the hardware */
    Eth_30_Tc3xx_Reg_Write(ctrlIdx, regOffsetRxDescStartAddr, rxDescAddr);

    /* #140 Rx Tail Pointer points to the last descriptor */
    Eth_30_Tc3xx_Reg_Write(ctrlIdx, regOffsetRxDescTailAddr, rxDescLastAddr);
  }
}


/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_SetTxDescriptorBaseAddresses()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */ /* prqa s 3219 1 */ /* md_eth_30_tc3xx_3219 */
ETH_30_TC3XX_LL_CTRL_MODE_HDL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_SetTxDescriptorBaseAddresses(
  uint8 ctrlIdx)
{
  uint8_least queueIdx;
  uint8 hwQueueIdx;

  /* #10 Iterate over used Tx queues */
  for (queueIdx = Eth_30_Tc3xx_GetTxDescrHandlingStartIdxOfEthCtrl(ctrlIdx);
       queueIdx < Eth_30_Tc3xx_GetTxDescrHandlingEndIdxOfEthCtrl(ctrlIdx); queueIdx++)
  {
    Eth_30_Tc3xx_RegOffsetType regOffsetTxDescRingLen;
    Eth_30_Tc3xx_RegOffsetType regOffsetTxDescStartAddr;
    Eth_30_Tc3xx_RegOffsetType regOffsetTxDescTailAddr;

    /* #110 Get Tx descriptor counts and addresses */
    uint32 txDescCount = (uint32)Eth_30_Tc3xx_GetTxDescrEndIdxOfTxDescrHandling(queueIdx) -
                         (uint32)Eth_30_Tc3xx_GetTxDescrStartIdxOfTxDescrHandling(queueIdx);

    /* PRQA S 0306 3 */ /* MD_Eth_30_Tc3xx_0306 */
    uint32 txDescAddr = (uint32) Eth_30_Tc3xx_GetAddrTxDescr(
                                 Eth_30_Tc3xx_GetTxDescrStartIdxOfTxDescrHandling(queueIdx));

    hwQueueIdx = (uint8)(queueIdx - Eth_30_Tc3xx_GetTxDescrHandlingStartIdxOfEthCtrl(ctrlIdx));
    switch (hwQueueIdx)
    {
    case ETH_30_TC3XX_LL_MID_0_PRIO_QUEUE_IDX:
      regOffsetTxDescRingLen   = ETH_30_TC3XX_REG_OFFS_DMA_CH1_TX_DESC_RING_LEN;
      regOffsetTxDescStartAddr = ETH_30_TC3XX_REG_OFFS_DMA_CH1_TX_DESC_LIST_ADDR;
      regOffsetTxDescTailAddr  = ETH_30_TC3XX_REG_OFFS_DMA_CH1_TX_DESC_TAIL_PTR;
      break;
    case ETH_30_TC3XX_LL_MID_1_PRIO_QUEUE_IDX:
      regOffsetTxDescRingLen   = ETH_30_TC3XX_REG_OFFS_DMA_CH2_TX_DESC_RING_LEN;
      regOffsetTxDescStartAddr = ETH_30_TC3XX_REG_OFFS_DMA_CH2_TX_DESC_LIST_ADDR;
      regOffsetTxDescTailAddr  = ETH_30_TC3XX_REG_OFFS_DMA_CH2_TX_DESC_TAIL_PTR;
      break;
    case ETH_30_TC3XX_LL_HIGH_PRIO_QUEUE_IDX:
      regOffsetTxDescRingLen   = ETH_30_TC3XX_REG_OFFS_DMA_CH3_TX_DESC_RING_LEN;
      regOffsetTxDescStartAddr = ETH_30_TC3XX_REG_OFFS_DMA_CH3_TX_DESC_LIST_ADDR;
      regOffsetTxDescTailAddr  = ETH_30_TC3XX_REG_OFFS_DMA_CH3_TX_DESC_TAIL_PTR;
      break;
    default:
      regOffsetTxDescRingLen   = ETH_30_TC3XX_REG_OFFS_DMA_CH0_TX_DESC_RING_LEN;
      regOffsetTxDescStartAddr = ETH_30_TC3XX_REG_OFFS_DMA_CH0_TX_DESC_LIST_ADDR;
      regOffsetTxDescTailAddr  = ETH_30_TC3XX_REG_OFFS_DMA_CH0_TX_DESC_TAIL_PTR;
      break;
    }

    /* #120 Announce ring length to hardware */
    Eth_30_Tc3xx_Reg_Write(ctrlIdx, regOffsetTxDescRingLen, ETH_30_TC3XX_REG_DMA_CHN_TX_DESC_RING_LEN &
                            (Eth_30_Tc3xx_RegWidthType)(txDescCount - 1u)); /* -1 described in manual */

    /* #130 Announce descriptor ring to the hardware */
    Eth_30_Tc3xx_Reg_Write(ctrlIdx, regOffsetTxDescStartAddr, txDescAddr);

    /* #140 Tx Tail Pointer points to the first descriptor */
    Eth_30_Tc3xx_Reg_Write(ctrlIdx, regOffsetTxDescTailAddr, txDescAddr);
  }

}

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_ResetCounters
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_LL_CTRL_MODE_HDL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_ResetCounters(
  uint8 ctrlIdx)
{
  /* #10 Reset statistic counters */
  Eth_30_Tc3xx_Reg_ClearBitMask(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MMC_CNTRL, ETH_30_TC3XX_REG_MMC_CNTRL_RST);
} /* Eth_30_Tc3xx_LL_ResetCounters() */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_SetDescriptorBaseAddresses
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_LL_CTRL_MODE_HDL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_SetDescriptorBaseAddresses(
  uint8 ctrlIdx)
{
 /* #10 Set the Tx descriptor base addresses */
  Eth_30_Tc3xx_LL_SetTxDescriptorBaseAddresses(ctrlIdx);
 /* #20 Set the Rx descriptor base addresses */
  Eth_30_Tc3xx_LL_SetRxDescriptorBaseAddresses(ctrlIdx);
} /* Eth_30_Tc3xx_LL_SetDescriptorBaseAddresses() */ /* PRQA S 6050 */ /* MD_MSR_STCAL */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_InitializeRxDescriptor
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_LL_CTRL_MODE_HDL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_InitializeRxDescriptor(
  uint8                                       ctrlIdx,
  Eth_30_Tc3xx_RxDescrHandlingIterType        globalDescrRingIdx,
  Eth_30_Tc3xx_RxDescrIterType                globalDescrIdx,
  Eth_30_Tc3xx_MappedBufferOfRxDescrStateType rxBufIdx)
{
  /* #10 Write buffer address to descriptor */
  P2VAR(Eth_30_Tc3xx_RxDescriptorType, AUTOMATIC, ETH_30_TC3XX_VAR_NOINIT) rxDescr = Eth_30_Tc3xx_GetAddrRxDescr(globalDescrIdx);
  Eth_30_Tc3xx_RxBufferIterType rxBufOffset = ((Eth_30_Tc3xx_RxBufferIterType)Eth_30_Tc3xx_GetRxBufferStartIdxOfRxBufferHandling(globalDescrRingIdx) +
       (rxBufIdx * (Eth_30_Tc3xx_RxBufferIterType)Eth_30_Tc3xx_GetAlignedSegSizeOfRxBufferHandling(globalDescrRingIdx)) +
      ETH_30_TC3XX_ALIGN_PADDING);

  /* PRQA S 0306 1 */ /* MD_Eth_30_Tc3xx_0306 */
  rxDescr->RxDescrWord[ETH_30_TC3XX_DES0_IDX] = ((uint32) Eth_30_Tc3xx_GetAddrRxBuffer(rxBufOffset));   /* SBSW_ETH_30_TC3XX_LOCAL_PTR_ACCESS_CSL_PARAM_IDX_CSL01 */
  rxDescr->RxDescrWord[ETH_30_TC3XX_DES1_IDX] = 0u;                                                     /* SBSW_ETH_30_TC3XX_LOCAL_PTR_ACCESS_CSL_PARAM_IDX_CSL01 */
  rxDescr->RxDescrWord[ETH_30_TC3XX_DES2_IDX] = 0u;                                                     /* SBSW_ETH_30_TC3XX_LOCAL_PTR_ACCESS_CSL_PARAM_IDX_CSL01 */

/* #20 Set descriptor as owned by DMA, enable interrupt on completion */
  rxDescr->RxDescrWord[ETH_30_TC3XX_DES3_IDX] = (uint32)(ETH_30_TC3XX_RX3_DESC_OWN |                    /* SBSW_ETH_30_TC3XX_LOCAL_PTR_ACCESS_CSL_PARAM_IDX_CSL01 */
                                                         ETH_30_TC3XX_RX3_DESC_IOC |
                                                         ETH_30_TC3XX_RX3_DESC_BUF1V);

  /* #30 Initialize context descriptor to be able to capture timestamps */
  rxDescr->RxDescrWord[ETH_30_TC3XX_CNTXT_DES0_IDX] = 0u;                                               /* SBSW_ETH_30_TC3XX_LOCAL_PTR_ACCESS_CSL_PARAM_IDX_CSL01 */
  rxDescr->RxDescrWord[ETH_30_TC3XX_CNTXT_DES1_IDX] = 0u;                                               /* SBSW_ETH_30_TC3XX_LOCAL_PTR_ACCESS_CSL_PARAM_IDX_CSL01 */
  rxDescr->RxDescrWord[ETH_30_TC3XX_CNTXT_DES2_IDX] = 0u;                                               /* SBSW_ETH_30_TC3XX_LOCAL_PTR_ACCESS_CSL_PARAM_IDX_CSL01 */
  rxDescr->RxDescrWord[ETH_30_TC3XX_CNTXT_DES3_IDX] = (uint32)ETH_30_TC3XX_RX3_DESC_OWN;                /* SBSW_ETH_30_TC3XX_LOCAL_PTR_ACCESS_CSL_PARAM_IDX_CSL01 */
  ETH_30_TC3XX_DUMMY_STATEMENT(ctrlIdx); /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
} /* Eth_30_Tc3xx_LL_InitializeRxDescriptor() */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_InitializeTxDescriptor
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_LL_CTRL_MODE_HDL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_InitializeTxDescriptor(
  uint8                               ctrlIdx,
  Eth_30_Tc3xx_TxDescrHandlingIterType globalDescrRingIdx,
  Eth_30_Tc3xx_TxDescrIterType         globalDescrIdx)
{
  P2VAR(Eth_30_Tc3xx_TxDescriptorType, AUTOMATIC, ETH_30_TC3XX_VAR_NOINIT) txDescr =
      Eth_30_Tc3xx_GetAddrTxDescr(globalDescrIdx);

  /* #10 Reset TX descriptor, set as owned by driver. No context descriptor needed for TX */
  txDescr->TxDescrWord[ETH_30_TC3XX_DES0_IDX] = 0u;                                             /* SBSW_ETH_30_TC3XX_LOCAL_PTR_ACCESS_CSL_PARAM_IDX_CSL01 */
  txDescr->TxDescrWord[ETH_30_TC3XX_DES1_IDX] = 0u;                                             /* SBSW_ETH_30_TC3XX_LOCAL_PTR_ACCESS_CSL_PARAM_IDX_CSL01 */
  txDescr->TxDescrWord[ETH_30_TC3XX_DES2_IDX] = 0u;                                             /* SBSW_ETH_30_TC3XX_LOCAL_PTR_ACCESS_CSL_PARAM_IDX_CSL01 */
  txDescr->TxDescrWord[ETH_30_TC3XX_DES3_IDX] = 0u;                                             /* SBSW_ETH_30_TC3XX_LOCAL_PTR_ACCESS_CSL_PARAM_IDX_CSL01 */

  ETH_30_TC3XX_DUMMY_STATEMENT(ctrlIdx); /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
  ETH_30_TC3XX_DUMMY_STATEMENT(globalDescrRingIdx); /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
} /* Eth_30_Tc3xx_LL_InitializeTxDescriptor() */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_InitDescriptorStateVariables
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_LL_CTRL_MODE_HDL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_InitDescriptorStateVariables(
  uint8 ctrlIdx)
{
  /* #10 Nothing to do here */
  ETH_30_TC3XX_DUMMY_STATEMENT(ctrlIdx); /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
} /* Eth_30_Tc3xx_LL_InitDescriptorStateVariables() */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_EnableMac
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_LL_CTRL_MODE_HDL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_EnableMac(
  uint8 ctrlIdx)
{

  /* #10 Enable MAC */
   Eth_30_Tc3xx_Reg_ClearBitMask(ctrlIdx, ETH_30_TC3XX_REG_OFFS_PMT_CTRL, ETH_30_TC3XX_REG_PMT_CTRL_PWR_DOWN);

  /* #20 Enable frame transmission and reception in DMA module */
  Eth_30_Tc3xx_Reg_SetBitMask(ctrlIdx, ETH_30_TC3XX_REG_OFFS_DMA_CH0_RX_CNTRL, ETH_30_TC3XX_REG_DMA_CHN_RX_CNTRL_SR);
  Eth_30_Tc3xx_Reg_SetBitMask(ctrlIdx, ETH_30_TC3XX_REG_OFFS_DMA_CH0_TX_CNTRL, ETH_30_TC3XX_REG_DMA_CHN_TX_CNTRL_ST);

  /* #30 If QoS feature is enabled configure DMA (transmission/reception) channes for all descriptor rings */
  if(Eth_30_Tc3xx_IsMultiQueueConfigEnabledOfEthCtrl(ctrlIdx) == TRUE)
  {
    Eth_30_Tc3xx_Reg_SetBitMask(ctrlIdx, ETH_30_TC3XX_REG_OFFS_DMA_CH1_RX_CNTRL, ETH_30_TC3XX_REG_DMA_CHN_RX_CNTRL_SR);
    Eth_30_Tc3xx_Reg_SetBitMask(ctrlIdx, ETH_30_TC3XX_REG_OFFS_DMA_CH1_TX_CNTRL, ETH_30_TC3XX_REG_DMA_CHN_TX_CNTRL_ST);

    if(Eth_30_Tc3xx_GetAmountOfRxQueuesOfEthCtrl(ctrlIdx) > ETH_30_TC3XX_LL_QOS_2_QUEUES_CONFIGURED)
    {
      Eth_30_Tc3xx_Reg_SetBitMask(ctrlIdx, ETH_30_TC3XX_REG_OFFS_DMA_CH2_RX_CNTRL, ETH_30_TC3XX_REG_DMA_CHN_RX_CNTRL_SR);
    }
    if(Eth_30_Tc3xx_GetAmountOfTxQueuesOfEthCtrl(ctrlIdx) > ETH_30_TC3XX_LL_QOS_2_QUEUES_CONFIGURED)
    {
      Eth_30_Tc3xx_Reg_SetBitMask(ctrlIdx, ETH_30_TC3XX_REG_OFFS_DMA_CH2_TX_CNTRL, ETH_30_TC3XX_REG_DMA_CHN_TX_CNTRL_ST);
    }
    if(Eth_30_Tc3xx_GetAmountOfRxQueuesOfEthCtrl(ctrlIdx) > ETH_30_TC3XX_LL_QOS_3_QUEUES_CONFIGURED)
    {
      Eth_30_Tc3xx_Reg_SetBitMask(ctrlIdx, ETH_30_TC3XX_REG_OFFS_DMA_CH3_RX_CNTRL, ETH_30_TC3XX_REG_DMA_CHN_RX_CNTRL_SR);
    }
    if(Eth_30_Tc3xx_GetAmountOfTxQueuesOfEthCtrl(ctrlIdx) > ETH_30_TC3XX_LL_QOS_3_QUEUES_CONFIGURED)
    {
      Eth_30_Tc3xx_Reg_SetBitMask(ctrlIdx, ETH_30_TC3XX_REG_OFFS_DMA_CH3_TX_CNTRL, ETH_30_TC3XX_REG_DMA_CHN_TX_CNTRL_ST);
    }
  }

  /* #40 Enable frame transmission and reception in MAC */
  Eth_30_Tc3xx_Reg_SetBitMask(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MAC_CFG, ETH_30_TC3XX_REG_CFG_RE_TE);
} /* Eth_30_Tc3xx_LL_EnableMac() */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_ResetMac
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
 *
 *
 *
 *
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_LL_CTRL_MODE_HDL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_ResetMac(
  uint8 ctrlIdx)
{
  Eth_30_Tc3xx_RegWidthType rpsxStatusBit;
  Eth_30_Tc3xx_RegWidthType tpsxStatusBit;
  Eth_30_Tc3xx_EthCtrlMiiInterfaceOfEthCtrlTc3xxType miiModeType = Eth_30_Tc3xx_GetEthCtrlMiiInterfaceOfEthCtrlTc3xx(ctrlIdx);
  /* #10 Check the RPSx and TPSx status bit fields in register DMA_DEBUG_STATUS0/1 (Finish active transfers and make
   *     sure that transmitters and receivers are set to stopped state is done -> MAC is already disabled by previous
   *     LL_PreResetMac() function call from the driver core part) */
  rpsxStatusBit = Eth_30_Tc3xx_Reg_ReadBits(
         ctrlIdx, ETH_30_TC3XX_REG_OFFS_DMA_DEBUG_STATUS0, ETH_30_TC3XX_REG_DMA_DEBUG_STATUS0_TPS_RPS_MASK);

  tpsxStatusBit = Eth_30_Tc3xx_Reg_ReadBits(
         ctrlIdx, ETH_30_TC3XX_REG_OFFS_DMA_DEBUG_STATUS1, ETH_30_TC3XX_REG_DMA_DEBUG_STATUS1_TPS_RPS_MASK);
  if ((rpsxStatusBit == 0uL) && (tpsxStatusBit == 0uL))
  {
    const uint8 fSPBCycles70 = 70u;
    uint8 isTxQiRegEmpty;
    uint8 isRxQiRegEmpty;

    /* #110 It may be required to wait 70 fSPB cycles after the last reset before checking if RXQSTS in MTL_RXQ0_DEBUG
     *      and MTL_RXQi_DEBUG are zero (one register read of ETH_30_TC3XX_REG_OFFS_HW_FEATURE0 takes more than one fSPB
     *      cycle of time) */
    Eth_30_Tc3xx_LL_WaitfSPBCycles(ctrlIdx, fSPBCycles70);

    /* #120 Check that content all MTL_RXQi_DEBUG and MTL_TXQi_DEBUG registers is equal to zero */
    isRxQiRegEmpty = Eth_30_Tc3xx_LL_IsRxQiDebugRegEmpty(ctrlIdx, ETH_30_TC3XX_REG_MTL_RXQ_X_DEBUG_ALL_NOT_RESERVED_MASK);
    isTxQiRegEmpty = Eth_30_Tc3xx_LL_IsTxQiDebugRegEmpty(ctrlIdx, ETH_30_TC3XX_REG_MTL_TXQ_X_DEBUG_ALL_NOT_RESERVED_MASK);

    if ((isTxQiRegEmpty == E_OK) && (isRxQiRegEmpty == E_OK))
    {
      Std_ReturnType tmpVal;

      /* #1210 Globally disable interrupts */
      Eth_30_Tc3xx_LL_DisableInterrupts(ctrlIdx);

      /* #1220 Deactivate Endinit protection */
      Appl_UnlockEndinit();

      /* #1230 If RGMII mode is used ensure GETH_GPCTL.EPR = 000B and GETH_SKEWCTL = 0x0 */
      if(miiModeType == ETH_RGMII_MODE)
      {
        Eth_30_Tc3xx_Reg_Write_Protected(ctrlIdx, ETH_30_TC3XX_REG_OFFS_ETH_GPCTL, 0u);
        Eth_30_Tc3xx_Reg_Write_Protected(ctrlIdx, ETH_30_TC3XX_REG_OFFS_SKEWCTL, 0u);
      }

      /* #1240 Reset the Kernel */
      tmpVal = Eth_30_Tc3xx_LL_ResetKernel(ctrlIdx);

      /* #1250 Re-activate Endinit protection */
      Appl_LockEndinit();

      /* #1260 Continue further reset procedure only if kernel reset was successful */
      if (tmpVal == E_OK)
      {
        const uint8 fSPBCycles4  =  4u;
        const uint8 fSPBCycles35 = 35u;

        /* #12610 Wait 35 fSPB cycles */
        Eth_30_Tc3xx_LL_WaitfSPBCycles(ctrlIdx, fSPBCycles35);
        /* #12620 Check the Mii Mode is  MII/RMII mode */
        if((miiModeType == ETH_MII_MODE) || (miiModeType == ETH_RMII_MODE))
        {
          /* #126210 Wait again 35 fSPB cycles ( making it 70fSPB for RMII and MII mode) */
          Eth_30_Tc3xx_LL_WaitfSPBCycles(ctrlIdx, fSPBCycles35);
          /* #126220 Check if RXQSTS in MTL_RXQ0_DEBUG and MTL_RXQi_DEBUG are zero */
          tmpVal = Eth_30_Tc3xx_LL_IsRxQiDebugRegEmpty(ctrlIdx, ETH_30_TC3XX_REG_MTL_RXQ_X_DEBUG_PRXQ_RXQSTS_MASK);
        }
        /* #12630 Continue if RXQSTS in MTL_RXQ0_DEBUG and MTL_RXQi_DEBUG are empty  */
        if(tmpVal == E_OK)
        {
          /* #126310 Set GETH_GPCTL.EPR and GETH_SKEWCTL if required (GETH_SKEWCTL will be set afterwards by the
           *         default register initialization) */
          Appl_UnlockEndinit();
          Eth_30_Tc3xx_Reg_Write_Protected(ctrlIdx, ETH_30_TC3XX_REG_OFFS_ETH_GPCTL,
                                                    Eth_30_Tc3xx_GetPinRoutingOfEthCtrlTc3xx(ctrlIdx));
          Appl_LockEndinit();

          /* #126320 Perform a software reset by writing to the DMA_MODE.SWR bit */
          Eth_30_Tc3xx_Reg_SetBitMask(ctrlIdx, ETH_30_TC3XX_REG_OFFS_DMA_MODE, ETH_30_TC3XX_REG_DMA_MODE_SWR);

          /* #126330 Wait 4 fSPB cycles */
          Eth_30_Tc3xx_LL_WaitfSPBCycles(ctrlIdx, fSPBCycles4);
        }
        /* #12640 Then check if DMA_MODE.SWR = 0B -> this will be done in the consecutive
         *        LL_IsResetMacFinished() function call from the driver core part */
      }
    }
  }
}  /* Eth_30_Tc3xx_LL_ResetMac() */ /* PRQA S 6050 */ /* MD_MSR_STCAL */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_IsResetMacFinished
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_LL_CTRL_MODE_HDL_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_IsResetMacFinished(
  uint8 ctrlIdx)
{
  /* #10 Return status of MAC reset bit */
  /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */
  return (boolean)((Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_DMA_MODE) &
                                                   ETH_30_TC3XX_REG_DMA_MODE_SWR) == 0uL);
} /* Eth_30_Tc3xx_LL_IsResetMacFinished() */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_DisableMac
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_LL_CTRL_MODE_HDL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_DisableMac(
  uint8 ctrlIdx)
{
  /* #10 Disable frame transmission in DMA module */
  Eth_30_Tc3xx_Reg_ClearBitMask(ctrlIdx, ETH_30_TC3XX_REG_OFFS_DMA_CH0_TX_CNTRL, ETH_30_TC3XX_REG_DMA_CHN_TX_CNTRL_ST);

  if(Eth_30_Tc3xx_IsMultiQueueConfigEnabledOfEthCtrl(ctrlIdx) == TRUE)
  {
    Eth_30_Tc3xx_Reg_ClearBitMask(ctrlIdx, ETH_30_TC3XX_REG_OFFS_DMA_CH1_TX_CNTRL,
                                           ETH_30_TC3XX_REG_DMA_CHN_TX_CNTRL_ST);
    if(Eth_30_Tc3xx_GetAmountOfTxQueuesOfEthCtrl(ctrlIdx) > ETH_30_TC3XX_LL_QOS_2_QUEUES_CONFIGURED)
    {
      Eth_30_Tc3xx_Reg_ClearBitMask(ctrlIdx, ETH_30_TC3XX_REG_OFFS_DMA_CH2_TX_CNTRL,
                                            ETH_30_TC3XX_REG_DMA_CHN_TX_CNTRL_ST);
    }
    if(Eth_30_Tc3xx_GetAmountOfTxQueuesOfEthCtrl(ctrlIdx) > ETH_30_TC3XX_LL_QOS_3_QUEUES_CONFIGURED)
    { 
      Eth_30_Tc3xx_Reg_ClearBitMask(ctrlIdx, ETH_30_TC3XX_REG_OFFS_DMA_CH3_TX_CNTRL,
                                            ETH_30_TC3XX_REG_DMA_CHN_TX_CNTRL_ST);
    }
  }

  /* #20 Only continue if previous frame transmissions completed within timeout */
  if(Eth_30_Tc3xx_LL_IsTransmissionComplete(ctrlIdx) == E_OK)
  {
    /* #210 Disable the MAC transmitter and receiver */
    Eth_30_Tc3xx_Reg_ClearBitMask(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MAC_CFG, ETH_30_TC3XX_REG_CFG_RE_TE);

    /* #220 Only continue if data in Rx Fifo was transfered within timeout */
    if(Eth_30_Tc3xx_LL_IsRxFifoTransferredToSystem(ctrlIdx) == E_OK)
    {
      /* #2210 Disable frame reception in DMA module */
      Eth_30_Tc3xx_Reg_ClearBitMask(ctrlIdx, ETH_30_TC3XX_REG_OFFS_DMA_CH0_RX_CNTRL, ETH_30_TC3XX_REG_DMA_CHN_RX_CNTRL_SR);
      if(Eth_30_Tc3xx_IsMultiQueueConfigEnabledOfEthCtrl(ctrlIdx) == TRUE)
      {
        Eth_30_Tc3xx_Reg_ClearBitMask(ctrlIdx, ETH_30_TC3XX_REG_OFFS_DMA_CH1_RX_CNTRL,
                                               ETH_30_TC3XX_REG_DMA_CHN_RX_CNTRL_SR);
        if(Eth_30_Tc3xx_GetAmountOfRxQueuesOfEthCtrl(ctrlIdx) > ETH_30_TC3XX_LL_QOS_2_QUEUES_CONFIGURED)
        {
          Eth_30_Tc3xx_Reg_ClearBitMask(ctrlIdx, ETH_30_TC3XX_REG_OFFS_DMA_CH2_RX_CNTRL,
                                                ETH_30_TC3XX_REG_DMA_CHN_RX_CNTRL_SR);
        }
        if(Eth_30_Tc3xx_GetAmountOfRxQueuesOfEthCtrl(ctrlIdx) > ETH_30_TC3XX_LL_QOS_3_QUEUES_CONFIGURED)
        {
          Eth_30_Tc3xx_Reg_ClearBitMask(ctrlIdx, ETH_30_TC3XX_REG_OFFS_DMA_CH3_RX_CNTRL,
                                                ETH_30_TC3XX_REG_DMA_CHN_RX_CNTRL_SR);
        }
      }
    }
  }
} /* Eth_30_Tc3xx_LL_DisableMac() */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_IsMacEnabled
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_LL_CTRL_MODE_HDL_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE)  Eth_30_Tc3xx_LL_IsMacEnabled(
  uint8 ctrlIdx)
{
  /* #10 Return status of MAC transmission / reception enabled bits */
  return Eth_30_Tc3xx_Reg_IsBitMaskSet(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MAC_CFG, ETH_30_TC3XX_REG_CFG_RE_TE);
} /* Eth_30_Tc3xx_LL_IsMacEnabled() */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_PreResetMac
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_LL_CTRL_MODE_HDL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_PreResetMac(
  uint8 ctrlIdx)
{
  /* #10 Check if MAC is enabled */
  if (Eth_30_Tc3xx_LL_IsMacEnabled(ctrlIdx) == TRUE)
  {
    /* #110 If MAC is enabled, disable MAC first for a following reset */
    Eth_30_Tc3xx_LL_DisableMac(ctrlIdx);
  }

} /* Eth_30_Tc3xx_LL_PreResetMac() */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_WaitfSPBCycles
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_LL_CTRL_MODE_HDL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_WaitfSPBCycles(
    uint8 ctrlIdx,
    uint8 fspbcycles )
{
  uint8_least fSPBCyclesCounter;
  Eth_30_Tc3xx_RegWidthType regVal;
  ETH_30_TC3XX_DUMMY_STATEMENT(ctrlIdx); /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */ /*lint !e438 */

  /* #10 Provides the necessary fspB cycles delay */
  for (fSPBCyclesCounter = 0; fSPBCyclesCounter <= fspbcycles; fSPBCyclesCounter++)
  {
    regVal = Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_HW_FEATURE0);
    ETH_30_TC3XX_DUMMY_STATEMENT(regVal); /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
  }
}

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_IsRxQiDebugRegEmpty
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
ETH_30_TC3XX_LL_CTRL_MODE_HDL_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_IsRxQiDebugRegEmpty(
    uint8 ctrlIdx,
    uint32 debugRegMask )
{
  Std_ReturnType retVal = E_NOT_OK;
  Eth_30_Tc3xx_RegWidthType mtlRxq0Debugbits;
  Eth_30_Tc3xx_RegWidthType mtlRxq1Debugbits;
  Eth_30_Tc3xx_RegWidthType mtlRxq2Debugbits;
  Eth_30_Tc3xx_RegWidthType mtlRxq3Debugbits;

  /* #10 Read RxQiDebug register bits */
  mtlRxq0Debugbits = Eth_30_Tc3xx_Reg_ReadBits(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MTL_RXQ0_DEBUG,
                                                        debugRegMask);
  mtlRxq1Debugbits = Eth_30_Tc3xx_Reg_ReadBits(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MTL_RXQ1_DEBUG,
                                                        debugRegMask);
  mtlRxq2Debugbits = Eth_30_Tc3xx_Reg_ReadBits(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MTL_RXQ2_DEBUG,
                                                        debugRegMask);
  mtlRxq3Debugbits = Eth_30_Tc3xx_Reg_ReadBits(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MTL_RXQ3_DEBUG,
                                                        debugRegMask);
  if((mtlRxq0Debugbits == 0uL) && (mtlRxq1Debugbits == 0uL) &&
     (mtlRxq2Debugbits == 0uL) && (mtlRxq3Debugbits == 0uL))
  {
    /* #110 Return E_OK on RxQi registers are empty */
    retVal = E_OK;
  }
  return retVal;
}

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_IsTxQiDebugRegEmpty
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
ETH_30_TC3XX_LL_CTRL_MODE_HDL_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_IsTxQiDebugRegEmpty(
    uint8 ctrlIdx,
    uint32 debugRegMask )
{
  Std_ReturnType retVal = E_NOT_OK;
  Eth_30_Tc3xx_RegWidthType mtlTxq0Debugbits;
  Eth_30_Tc3xx_RegWidthType mtlTxq1Debugbits;
  Eth_30_Tc3xx_RegWidthType mtlTxq2Debugbits;
  Eth_30_Tc3xx_RegWidthType mtlTxq3Debugbits;

  /* #10 Read TxQiDebug register bits */
  mtlTxq0Debugbits = Eth_30_Tc3xx_Reg_ReadBits(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MTL_TXQ0_DEBUG,
                                                        debugRegMask);
  mtlTxq1Debugbits = Eth_30_Tc3xx_Reg_ReadBits(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MTL_TXQ1_DEBUG,
                                                        debugRegMask);
  mtlTxq2Debugbits = Eth_30_Tc3xx_Reg_ReadBits(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MTL_TXQ2_DEBUG,
                                                        debugRegMask);
  mtlTxq3Debugbits = Eth_30_Tc3xx_Reg_ReadBits(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MTL_TXQ3_DEBUG,
                                                        debugRegMask);

  if((mtlTxq0Debugbits == 0uL) && (mtlTxq1Debugbits == 0uL) &&
     (mtlTxq2Debugbits == 0uL) && (mtlTxq3Debugbits == 0uL))
  {
    /* #110 Return E_OK on TxQi registers are empty */
    retVal = E_OK;
  }
  return retVal;
}

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_RearmMacForReception
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_LL_CTRL_MODE_HDL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_RearmMacForReception(
  uint8                                ctrlIdx,
  Eth_30_Tc3xx_RxDescrHandlingIterType globalDescrRingIdx)
{
  /* #10 Nothing to do here */
  ETH_30_TC3XX_DUMMY_STATEMENT(ctrlIdx); /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
  ETH_30_TC3XX_DUMMY_STATEMENT(globalDescrRingIdx); /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
} /* Eth_30_Tc3xx_LL_RearmMacForReception() */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_PerformAdditionalHwConfig
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_LL_CTRL_MODE_HDL_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_PerformAdditionalHwConfig(
  uint8 ctrlIdx)
{
  Std_ReturnType retVal = E_OK;

/* #10 Perform VLAN-ID based frame queuing configuration if enabled */
#  if (ETH_30_TC3XX_ENABLE_VLANID_BASED_FRAME_QUEUING == STD_ON)

  Eth_30_Tc3xx_RegWidthType vlanTagDataVal;
  Eth_30_Tc3xx_RegWidthType vlanTagCtrlVal;
  uint8 vlanFilterIdx;
  uint16 vlanId;
  uint32 queueIdx;
  uint8 retryCountIdx;

  const Eth_30_Tc3xx_VlanIdRxDescrRingMapStartIdxOfVlanIdBasedQueuingHandlingType vlanIdRxDescrMapStartIdx = 
                                     Eth_30_Tc3xx_GetVlanIdRxDescrRingMapStartIdxOfVlanIdBasedQueuingHandling(ctrlIdx);
  const Eth_30_Tc3xx_VlanIdRxDescrRingMapEndIdxOfVlanIdBasedQueuingHandlingType vlanIdRxDescrMapEndIdx = 
                                     Eth_30_Tc3xx_GetVlanIdRxDescrRingMapEndIdxOfVlanIdBasedQueuingHandling(ctrlIdx);

  for (vlanFilterIdx = vlanIdRxDescrMapStartIdx; vlanFilterIdx < vlanIdRxDescrMapEndIdx; vlanFilterIdx++)
  {
    retVal = E_NOT_OK;

    /* #110 Retrieve the VLAN ID and its corresponding queue mapping from configuration */
    vlanId = Eth_30_Tc3xx_GetVlanIdOfVlanIdRxDescrRingMap(vlanFilterIdx);
    queueIdx = (uint32)Eth_30_Tc3xx_GetQueueIndexOfVlanIdRxDescrRingMap(vlanFilterIdx);

    /* #120 Prepare MAC_VLAN_TAG_DATA register value with VLAN_ID filter information */
    vlanTagDataVal = ETH_30_TC3XX_MAC_VLAN_TAG_DATA_MASK;
    vlanTagDataVal |= (queueIdx << ETH_30_TC3XX_MAC_VLAN_TAG_DATA_DMACHN_SHIFT);
    vlanTagDataVal |= vlanId;

    /* #140 Write the VLAN-ID filter information to VLAN_TAG_DATA register */
    Eth_30_Tc3xx_Reg_Write(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MAC_VLAN_TAG_DATA, vlanTagDataVal);

    /* #150 Prepare MAC_VLAN_TAG_CONTROL register value */
    vlanTagCtrlVal = ((Eth_30_Tc3xx_RegWidthType)vlanFilterIdx << ETH_30_TC3XX_MAC_VLAN_TAG_CTRL_OFS_SHIFT)
        | ETH_30_TC3XX_MAC_VLAN_TAG_CTRL_OB_MASK;

    /* #160 Create VLAN ID Filter bank based on the filter info written to VLAN_TAG_DATA register */
    Eth_30_Tc3xx_Reg_Write(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MAC_VLAN_TAG_CTRL, vlanTagCtrlVal);

    /* #170 Wait for indirect write to be finished */
    for (retryCountIdx = 0u; retryCountIdx < Eth_30_Tc3xx_GetResetLoopCyclesOfEthCtrl(ctrlIdx); retryCountIdx++ )
    {
      vlanTagCtrlVal = Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MAC_VLAN_TAG_CTRL);
      if ((vlanTagCtrlVal & ETH_30_TC3XX_MAC_VLAN_TAG_CTRL_OB_MASK) != ETH_30_TC3XX_MAC_VLAN_TAG_CTRL_OB_MASK)
      {
        retVal = E_OK;
        break;
      }
    }

    if (retVal != E_OK)
    {
      break;
    }
  }
#  endif /* ETH_30_TC3XX_ENABLE_VLANID_BASED_FRAME_QUEUING */
  ETH_30_TC3XX_DUMMY_STATEMENT(ctrlIdx); /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */ /*lint !e438 */

  return retVal;
} /* Eth_30_Tc3xx_LL_PerformAdditionalHwConfig */

# define ETH_30_TC3XX_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* ETH_30_TC3XX_LL_CTRLMODEHDL_INT_H */

/**********************************************************************************************************************
 *  END OF FILE: Eth_30_Tc3xx_CtrlModeHdl_Int.h
 *********************************************************************************************************************/
