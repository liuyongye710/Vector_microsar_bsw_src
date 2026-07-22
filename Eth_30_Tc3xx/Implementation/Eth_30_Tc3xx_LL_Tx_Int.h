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
/*!        \file  Eth_30_Tc3xx_LL_Tx_Int.h
 *        \brief  Lower layer transceive private header file
 *
 *      \details  Private inline implementations of lower layer transceive part of component.
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
#if !defined (ETH_30_TC3XX_LL_TX_INT_H)
# define ETH_30_TC3XX_LL_TX_INT_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "Eth_30_Tc3xx_LL_Tx_Ifc_Int.h"
# include "Eth_30_Tc3xx_LL_CtrlModeHdl_Int.h"
# include "Eth_30_Tc3xx_IrqHandler_Int.h"
# include "Eth_30_Tc3xx_Lcfg.h"

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

# define ETH_30_TC3XX_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_PrepareTxDescriptorForIpChecksumOffloading
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_LL_TX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_PrepareTxDescriptorForIpChecksumOffloading(
  uint8                                ctrlIdx,
  Eth_30_Tc3xx_TxDescrHandlingIterType globalDescrRingIdx,
  Eth_30_Tc3xx_TxDescrIterType         globalDescrIdx)
{
  /* #10 Enable checksum offloading for IPv4-Header */
  if (Eth_30_Tc3xx_IsIpChecksumOffloadingEnabledOfEthCtrl(ctrlIdx) == TRUE)
  {
    Eth_30_Tc3xx_GetAddrTxDescr(globalDescrIdx)->TxDescrWord[ETH_30_TC3XX_DES3_IDX] |=    /* SBSW_ETH_30_TC3XX_LOCAL_PTR_ACCESS_CSL_PARAM_IDX_CSL01 */
        (ETH_30_TC3XX_TX3_DESC_IP_OFFLOAD << ETH_30_TC3XX_TX3_DESC_CIC_SHIFT);
  }
  ETH_30_TC3XX_DUMMY_STATEMENT(globalDescrRingIdx); /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
} /* Eth_30_Tc3xx_LL_PrepareTxDescriptorForIpChecksumOffloading() */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_PrepareTxDescriptorForProtocolChecksumOffloading
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_LL_TX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_PrepareTxDescriptorForProtocolChecksumOffloading(
  uint8                                ctrlIdx,
  Eth_30_Tc3xx_TxDescrHandlingIterType globalDescrRingIdx,
  Eth_30_Tc3xx_TxDescrIterType         globalDescrIdx)
{
  /* #10 Enable transport protocol offloading for this descriptor */
  if (Eth_30_Tc3xx_IsProtocolChecksumOffloadingEnabledOfEthCtrl(ctrlIdx) == TRUE)
  {
    Eth_30_Tc3xx_GetAddrTxDescr(globalDescrIdx)->TxDescrWord[ETH_30_TC3XX_DES3_IDX] |=    /* SBSW_ETH_30_TC3XX_LOCAL_PTR_ACCESS_CSL_PARAM_IDX_CSL01 */
        (ETH_30_TC3XX_TX3_DESC_TRANSPORT_OFFLOAD << ETH_30_TC3XX_TX3_DESC_CIC_SHIFT);
  }
  ETH_30_TC3XX_DUMMY_STATEMENT(globalDescrRingIdx); /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
} /* Eth_30_Tc3xx_LL_PrepareTxDescriptorForProtocolChecksumOffloading() */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_TriggerTransmission
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_LL_TX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_TriggerTransmission(
  uint8                                ctrlIdx,
  Eth_30_Tc3xx_TxDescrHandlingIterType globalDescrRingIdx,
  Eth_30_Tc3xx_TxDescrIterType         globalDescrIdx)
{
  Eth_30_Tc3xx_RegOffsetType regOffset = 0;
  P2VAR(Eth_30_Tc3xx_TxDescriptorType, AUTOMATIC, ETH_30_TC3XX_VAR_NOINIT) txDescr =
      Eth_30_Tc3xx_GetAddrTxDescr(globalDescrIdx);
  Eth_30_Tc3xx_TxDescrIterType tailPtrDescrIdx = globalDescrIdx;

  /* #10 Set descriptor as owned by DMA */
  txDescr->TxDescrWord[ETH_30_TC3XX_DES3_IDX] |= ETH_30_TC3XX_TX3_DESC_OWN;   /* SBSW_ETH_30_TC3XX_LOCAL_PTR_ACCESS_CSL_PARAM_IDX_CSL01 */

  /* #20 Calculate next tail pointer address with regard to wraparound */
  if (globalDescrIdx < (Eth_30_Tc3xx_GetTxDescrEndIdxOfTxDescrHandling(globalDescrRingIdx) - 1uL))
  {
    tailPtrDescrIdx++;
  }
  else
  {
    tailPtrDescrIdx = Eth_30_Tc3xx_GetTxDescrStartIdxOfTxDescrHandling(globalDescrRingIdx);
  }
  txDescr = Eth_30_Tc3xx_GetAddrTxDescr(tailPtrDescrIdx);

  /* #30 Set tail pointer to start transmission depending on the used descriptor ring index */
  if (globalDescrRingIdx == ETH_30_TC3XX_LL_HIGH_PRIO_QUEUE_IDX)
  {
    regOffset = ETH_30_TC3XX_REG_OFFS_DMA_CH3_TX_DESC_TAIL_PTR;
  }
  else if (globalDescrRingIdx == ETH_30_TC3XX_LL_MID_1_PRIO_QUEUE_IDX)
  {
    regOffset = ETH_30_TC3XX_REG_OFFS_DMA_CH2_TX_DESC_TAIL_PTR;
  }
  else if (globalDescrRingIdx == ETH_30_TC3XX_LL_MID_0_PRIO_QUEUE_IDX)
  {
    regOffset = ETH_30_TC3XX_REG_OFFS_DMA_CH1_TX_DESC_TAIL_PTR;
  }
  else
  {
    regOffset = ETH_30_TC3XX_REG_OFFS_DMA_CH0_TX_DESC_TAIL_PTR;
  }
  /* PRQA S 0303 1 */ /* MD_Eth_30_Tc3xx_0303 */
  Eth_30_Tc3xx_Reg_Write(ctrlIdx, regOffset, (uint32)(&(txDescr->TxDescrWord[ETH_30_TC3XX_DES0_IDX])));
} /* Eth_30_Tc3xx_LL_TriggerTransmission() */

# if (ETH_30_TC3XX_ENABLE_TIMESYNC == STD_ON)
/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_PrepareTxDescriptorForTimestamping
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_LL_TX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_PrepareTxDescriptorForTimestamping(
  uint8                                ctrlIdx,
  Eth_30_Tc3xx_TxDescrHandlingIterType globalDescrRingIdx,
  Eth_30_Tc3xx_TxDescrIterType         globalDescrIdx,
  Eth_30_Tc3xx_TxBufferStateIterType   bufIdx)
{
  /* #10 Enable timestamping for the given descriptor if feature is enabled */
  Eth_30_Tc3xx_GetAddrTxDescr(globalDescrIdx)->TxDescrWord[ETH_30_TC3XX_DES2_IDX] |=        /* SBSW_ETH_30_TC3XX_LOCAL_PTR_ACCESS_CSL_PARAM_IDX_CSL01 */
                                                                                    ETH_30_TC3XX_TX2_DESC_TTSE;

  ETH_30_TC3XX_DUMMY_STATEMENT(bufIdx); /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
  ETH_30_TC3XX_DUMMY_STATEMENT(globalDescrRingIdx); /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
  ETH_30_TC3XX_DUMMY_STATEMENT(ctrlIdx); /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
} /* Eth_30_Tc3xx_LL_PrepareTxDescriptorForTimestamping() */
# endif /* ETH_30_TC3XX_ENABLE_TIMESYNC */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_PrepareTxDescriptorForTransmission
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_LL_TX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_PrepareTxDescriptorForTransmission(
          uint8                                                                   ctrlIdx,
          Eth_30_Tc3xx_TxDescrHandlingIterType                                    globalDescrRingIdx,
          Eth_30_Tc3xx_TxDescrIterType                                            globalDescrIdx,
          Eth_30_Tc3xx_TxBufferStateIterType                                      bufIdx,
          uint16                                                                  lenByte,
  P2CONST(uint8,                              AUTOMATIC, ETH_30_TC3XX_VAR_NOINIT) bufPtr)
{
  P2VAR(Eth_30_Tc3xx_TxDescriptorType, AUTOMATIC, ETH_30_TC3XX_VAR_NOINIT) txDescr =
      Eth_30_Tc3xx_GetAddrTxDescr(globalDescrIdx);

  /* #10 Set buffer address, interrupt on completion, first + last descriptor */
  /* PRQA S 0306 1 */ /* MD_Eth_30_Tc3xx_0306 */
  txDescr->TxDescrWord[ETH_30_TC3XX_DES0_IDX] = (uint32)(bufPtr);                       /* SBSW_ETH_30_TC3XX_LOCAL_PTR_ACCESS_CSL_PARAM_IDX_CSL01 */

  txDescr->TxDescrWord[ETH_30_TC3XX_DES2_IDX] = (uint32)(ETH_30_TC3XX_TX2_DESC_IOC |    /* SBSW_ETH_30_TC3XX_LOCAL_PTR_ACCESS_CSL_PARAM_IDX_CSL01 */
                                                        (ETH_30_TC3XX_TX2_DESC_BUF1_LEN_MASK & (uint32)lenByte));

  txDescr->TxDescrWord[ETH_30_TC3XX_DES3_IDX] = (uint32)(ETH_30_TC3XX_TX3_DESC_FD |     /* SBSW_ETH_30_TC3XX_LOCAL_PTR_ACCESS_CSL_PARAM_IDX_CSL01 */
                                                         ETH_30_TC3XX_TX3_DESC_LD |
                                                        (ETH_30_TC3XX_TX3_DESC_FL_MASK & ((uint32)lenByte +
                                                                                          ETH_30_TC3XX_HDR_LEN_BYTE)));

  ETH_30_TC3XX_DUMMY_STATEMENT(bufIdx); /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
  ETH_30_TC3XX_DUMMY_STATEMENT(globalDescrRingIdx); /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */
  ETH_30_TC3XX_DUMMY_STATEMENT(ctrlIdx); /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */
} /* Eth_30_Tc3xx_LL_PrepareTxDescriptorForTransmission() */ /* PRQA S 6060 */ /* MD_MSR_STPAR */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_RechargeTxDescriptor
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_LL_TX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_RechargeTxDescriptor(
  uint8                                ctrlIdx,
  Eth_30_Tc3xx_TxDescrHandlingIterType globalDescrRingIdx,
  Eth_30_Tc3xx_TxDescrIterType         globalDescrIdx)
{
  /* #10 Nothing to do here */
  ETH_30_TC3XX_DUMMY_STATEMENT(ctrlIdx); /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
  ETH_30_TC3XX_DUMMY_STATEMENT(globalDescrRingIdx); /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
  ETH_30_TC3XX_DUMMY_STATEMENT(globalDescrIdx); /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
} /* Eth_30_Tc3xx_LL_RechargeTxDescriptor() */

# if (ETH_30_TC3XX_ENABLE_TIMESYNC == STD_ON)
/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_ResetTimestampingInTxDescriptor
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_LL_TX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_ResetTimestampingInTxDescriptor(
  uint8                                ctrlIdx,
  Eth_30_Tc3xx_TxDescrHandlingIterType globalDescrRingIdx,
  Eth_30_Tc3xx_TxDescrIterType         globalDescrIdx)
{
  /* #10 Reset PTP descriptor flag */
  if (Eth_30_Tc3xx_IsTimeSynEnabledOfEthCtrl(ctrlIdx) == TRUE)
  {
    Eth_30_Tc3xx_GetAddrTxDescr(globalDescrIdx)->TxDescrWord[ETH_30_TC3XX_DES2_IDX] &=    /* SBSW_ETH_30_TC3XX_LOCAL_PTR_ACCESS_CSL_PARAM_IDX_CSL01 */
        (uint32)~ETH_30_TC3XX_TX2_DESC_TTSE;
  }
  ETH_30_TC3XX_DUMMY_STATEMENT(globalDescrRingIdx); /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
} /* Eth_30_Tc3xx_LL_ResetTimestampingInTxDescriptor() */
# endif /* ETH_30_TC3XX_ENABLE_TIMESYNC */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_IsTransmissionComplete
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
ETH_30_TC3XX_LL_TX_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_IsTransmissionComplete( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
    uint8 ctrlIdx)
{
  Std_ReturnType retVal = E_NOT_OK;
  uint32_least hwLoopTimeout;
  volatile Eth_30_Tc3xx_RegWidthType regValTxQ0 = 0;
  volatile Eth_30_Tc3xx_RegWidthType regValTxQ1 = 0;
  volatile Eth_30_Tc3xx_RegWidthType regValTxQ2 = 0;
  volatile Eth_30_Tc3xx_RegWidthType regValTxQ3 = 0;

  for(hwLoopTimeout = 0u; hwLoopTimeout < Eth_30_Tc3xx_GetResetLoopCyclesOfEthCtrl(ctrlIdx); hwLoopTimeout++)
  {
    /* #10 Read all used MTL_TXQi_DEBUG registers (default TXQ0, with QoS all available) */
    regValTxQ0 = Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MTL_TXQ0_DEBUG);
    if(Eth_30_Tc3xx_IsMultiQueueConfigEnabledOfEthCtrl(ctrlIdx) == TRUE)
    {
      regValTxQ1 = Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MTL_TXQ1_DEBUG);
      if(Eth_30_Tc3xx_GetAmountOfTxQueuesOfEthCtrl(ctrlIdx) > ETH_30_TC3XX_LL_QOS_2_QUEUES_CONFIGURED)
      {
        regValTxQ2 = Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MTL_TXQ2_DEBUG);
      }
      if(Eth_30_Tc3xx_GetAmountOfTxQueuesOfEthCtrl(ctrlIdx) > ETH_30_TC3XX_LL_QOS_3_QUEUES_CONFIGURED)
      {
        regValTxQ3 = Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MTL_TXQ3_DEBUG);
      }
    }

    /* #20 Check the appropriate bits if transmission is complete */
    if(((regValTxQ0 & ETH_30_TC3XX_REG_MTL_TXQ_X_DEBUG_TRCSTS_MASK) != ETH_30_TC3XX_REG_MTL_TXQ_X_DEBUG_TXQ_READ_STATE) &&
       ((regValTxQ1 & ETH_30_TC3XX_REG_MTL_TXQ_X_DEBUG_TRCSTS_MASK) != ETH_30_TC3XX_REG_MTL_TXQ_X_DEBUG_TXQ_READ_STATE) &&
       ((regValTxQ2 & ETH_30_TC3XX_REG_MTL_TXQ_X_DEBUG_TRCSTS_MASK) != ETH_30_TC3XX_REG_MTL_TXQ_X_DEBUG_TXQ_READ_STATE) &&
       ((regValTxQ3 & ETH_30_TC3XX_REG_MTL_TXQ_X_DEBUG_TRCSTS_MASK) != ETH_30_TC3XX_REG_MTL_TXQ_X_DEBUG_TXQ_READ_STATE) &&
       ((regValTxQ0 & ETH_30_TC3XX_REG_MTL_TXQ_X_DEBUG_TXQSTS_MASK) == ETH_30_TC3XX_REG_MTL_TXQ_X_DEBUG_TXQ_EMPTY)      &&
       ((regValTxQ1 & ETH_30_TC3XX_REG_MTL_TXQ_X_DEBUG_TXQSTS_MASK) == ETH_30_TC3XX_REG_MTL_TXQ_X_DEBUG_TXQ_EMPTY)      &&
       ((regValTxQ2 & ETH_30_TC3XX_REG_MTL_TXQ_X_DEBUG_TXQSTS_MASK) == ETH_30_TC3XX_REG_MTL_TXQ_X_DEBUG_TXQ_EMPTY)      &&
       ((regValTxQ3 & ETH_30_TC3XX_REG_MTL_TXQ_X_DEBUG_TXQSTS_MASK) == ETH_30_TC3XX_REG_MTL_TXQ_X_DEBUG_TXQ_EMPTY))
    {
      /* #210 Set return value to E_OK if completed for every TX queue, 
              otherwise check again if timeout cycle counter not exceeded */
      retVal = E_OK;
      break;
    }
  }

  return retVal;
} /* Eth_30_Tc3xx_LL_IsTransmissionComplete() */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_SetTxEvents
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_LL_TX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_SetTxEvents(
  uint8 ctrlIdx)
{
  /* #10 Trigger Tx event evaluation */
  (void)Eth_30_Tc3xx_LL_IsTxPending(ctrlIdx);
} /* Eth_30_Tc3xx_LL_SetTxEvents() */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_IsTxDescriptorOwnedByDriver
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_LL_TX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_IsTxDescriptorOwnedByDriver(
  uint8                                ctrlIdx,
  Eth_30_Tc3xx_TxDescrHandlingIterType globalDescrRingIdx,
  Eth_30_Tc3xx_TxDescrIterType         globalDescrIdx)
{

  ETH_30_TC3XX_DUMMY_STATEMENT(ctrlIdx); /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */
  ETH_30_TC3XX_DUMMY_STATEMENT(globalDescrRingIdx); /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */

  /* #10 Return status of OWN bit in Tx descriptor */
  return (boolean)(((uint32)(ETH_30_TC3XX_TX3_DESC_OWN &
          Eth_30_Tc3xx_GetAddrTxDescr(globalDescrIdx)->TxDescrWord[ETH_30_TC3XX_DES3_IDX])) == 0uL);
} /* Eth_30_Tc3xx_LL_IsTxDescriptorOwnedByDriver() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_IsTxPending
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 */
ETH_30_TC3XX_LL_TX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_IsTxPending(
  uint8 ctrlIdx)
{
  Eth_30_Tc3xx_TxDescrRingProcIterType descrRingCount;
  boolean isTxPend = FALSE;

  /* #10 Iterate over all used queues */
  for (descrRingCount = (Eth_30_Tc3xx_TxDescrRingProcIterType)Eth_30_Tc3xx_GetTxDescrHandlingEndIdxOfEthCtrl(ctrlIdx); descrRingCount > Eth_30_Tc3xx_GetTxDescrHandlingStartIdxOfEthCtrl(ctrlIdx); descrRingCount--)
  {
    Eth_30_Tc3xx_TxDescrRingProcIterType descrRingIdx = (uint8)(descrRingCount - 1u);

    /* #110 If any checked TX queue has pending TX frames */
    if (Eth_30_Tc3xx_LL_IsTxQueuePending(ctrlIdx, descrRingIdx) == TRUE)
    {
      /* #1110 Return that a TX event is pending */
      isTxPend = TRUE;
    }
  }

  return isTxPend;
} /* Eth_30_Tc3xx_LL_IsTxPending() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_IsTxQueuePending
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
ETH_30_TC3XX_LL_TX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_IsTxQueuePending(
  uint8 ctrlIdx,
  Eth_30_Tc3xx_TxDescrRingProcIterType globalDescrRingIdx)
{
  boolean isTxPend = FALSE;
  Eth_30_Tc3xx_CurProcPosOfTxDescrRingProcType curTxDescrIdx = Eth_30_Tc3xx_GetCurProcPosOfTxDescrRingProc(globalDescrRingIdx)
                                                               + Eth_30_Tc3xx_GetTxDescrStartIdxOfTxDescrHandling(globalDescrRingIdx);

  /* PRQA S 3415 3 */ /* MD_Eth_30_Tc3xx_3415 */
  /* #10 Check if next descriptor to process is passed to driver already */
  if ((Eth_30_Tc3xx_LL_IsTxDescriptorOwnedByDriver(ctrlIdx, globalDescrRingIdx, curTxDescrIdx) == TRUE) &&
      (Eth_30_Tc3xx_GetTxReadyOfTxDescrState(curTxDescrIdx) == ETH_30_TC3XX_DESCRIPTOR_READY))
  {
    /* #110 Is passed, set respective events for the core and signal the caller that he should trigger a re-check
     *      after processing of the checked descriptor only when VLAN-ID based frame queuing is disabled,
     *      when VLAN-ID based frame queuing is enabled, the DMA Idx is retained and only the corresponding
     *      descriptor ring is processed and not based on Tx event */
    if (Eth_30_Tc3xx_IsVlanIdBasedFrameQueuingEnabledOfEthCtrl(ctrlIdx) != TRUE)
    {
      Eth_30_Tc3xx_SetTxEvent(ctrlIdx, (uint8)globalDescrRingIdx);
    }
    isTxPend = TRUE;
  }

  return isTxPend;
} /* Eth_30_Tc3xx_LL_IsTxQueuePending() */

# define ETH_30_TC3XX_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* ETH_30_TC3XX_LL_TX_INT_H */

/**********************************************************************************************************************
 *  END OF FILE: Eth_30_Tc3xx_LL_Tx_Int.h
 *********************************************************************************************************************/
