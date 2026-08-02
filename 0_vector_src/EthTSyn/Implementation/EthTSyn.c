/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2021 by Vector Informatik GmbH.                                                  All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/*!        \file  EthTSyn.c
 *        \brief  EthTSyn implementation
 *      \details  Contains the main implementation of the Time Sync over Ethernet (EthTSyn) AUTOSAR module
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *
 *  FILE VERSION
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the VERSION CHECK below.
 *********************************************************************************************************************/


#define ETHTSYN_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "EthTSyn_Int.h" /* PRQA S 3219, 0883 */ /* MD_EthTSyn_3219, MD_EthTSyn_0883 */
#include "EthTSyn_Master_Int.h"
#include "EthTSyn_Slave_Int.h" /* PRQA S 3219 */ /* MD_EthTSyn_3219 */
#include "EthTSyn_Pdelay_Int.h"
#if (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON)
# include "EthTSyn_SwtMgmt_Int.h"
# if (ETHTSYN_SWT_TIME_SYNC_SUPPORT == STD_ON)
#  include "EthTSyn_SwtTimeSync_Int.h" /* PRQA S 0777 */ /* MD_MSR_Rule5.1 */
# endif /* (ETHTSYN_SWT_TIME_SYNC_SUPPORT == STD_ON) */
#endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON) */

#if ( (ETHTSYN_MASTER_TIME_VALIDATION_SUPPORT == STD_ON) || (ETHTSYN_SLAVE_TIME_VALIDATION_SUPPORT == STD_ON) )
# include "EthTSyn_TimeValidation_Int.h"
#endif /* ( (ETHTSYN_MASTER_TIME_VALIDATION_SUPPORT == STD_ON) || (ETHTSYN_SLAVE_TIME_VALIDATION_SUPPORT == STD_ON) ) */

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/
/* vendor specific version information is BCD coded */
#if (  (ETHTSYN_SW_MAJOR_VERSION != (14u)) \
    || (ETHTSYN_SW_MINOR_VERSION != (0u)) \
    || (ETHTSYN_SW_PATCH_VERSION != (0u)) )
# error "Vendor specific version numbers of EthTSyn.c and EthTSyn.h are inconsistent"
#endif

/* Check the version of the configuration header file */
#if (  (ETHTSYN_CFG_MAJOR_VERSION != (14u)) \
    || (ETHTSYN_CFG_MINOR_VERSION != (0u)) )
# error "Version numbers of EthTSyn.c and EthTSyn_Cfg.h are inconsistent!"
#endif

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/
#define ETHTSYN_IEEE_802_1_AS_CLOCK_IDENTITY_BYTE_3                   0xFFu
#define ETHTSYN_IEEE_802_1_AS_CLOCK_IDENTITY_BYTE_4                   0xFEu

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
#define ETHTSYN_START_SEC_VAR_ZERO_INIT_8BIT
#include "EthTSyn_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

VAR(EthTSyn_StateEnumType, ETHTSYN_VAR_ZERO_INIT) EthTSyn_State = ETHTSYN_STATE_UNINIT;

#define ETHTSYN_STOP_SEC_VAR_ZERO_INIT_8BIT
#include "EthTSyn_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
#define ETHTSYN_START_SEC_CODE
#include "EthTSyn_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  EthTSyn_SetLocalClockIdentity
 *********************************************************************************************************************/
/*! \brief      Sets the local clock identity of the EthTSyn controller.
 *  \details    -
 *  \param[in]  EthTSynCtrlIdx   Index of the EthTSyn controller the clock identity should be set
 *                               [range: EthTSynCtrlIdx < EthTSyn_GetSizeOfCtrl()]
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *  \spec
 *    requires EthTSynCtrlIdx < EthTSyn_GetSizeOfCtrl();
 *  \endspec
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetLocalClockIdentity(
  EthTSyn_IntCtrlIdxType EthTSynCtrlIdx);

/**********************************************************************************************************************
 *  EthTSyn_InitPort
 *********************************************************************************************************************/
/*! \brief      Initializes an EthTSyn Port.
 *  \details    Initializes all component variables directly related to the passed EthTSyn Port.
 *  \param[in]  PortIdx   Index of the Port that should be initialized
 *                        [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *  \spec
 *    requires PortIdx < EthTSyn_GetSizeOfPort();
 *  \endspec
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_InitPort(
  EthTSyn_IntPortIdxType PortIdx);

/**********************************************************************************************************************
 *  EthTSyn_InitCtrl
 *********************************************************************************************************************/
/*! \brief      Initializes an EthTSyn controller.
 *  \details    Initializes all component variables directly related to the passed EthTSyn controller.
 *  \param[in]  EthTSynCtrlIdx   Index of the EthTSyn controller
 *                               [range: EthTSynCtrlIdx < EthTSyn_GetSizeOfCtrl()]
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *  \spec
 *    requires EthTSynCtrlIdx < EthTSyn_GetSizeOfCtrl();
 *  \endspec
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_InitCtrl(
  EthTSyn_CtrlIterType EthTSynCtrlIdx);

/**********************************************************************************************************************
 *  EthTSyn_ResetPortsAndPdelayOfCtrl
 *********************************************************************************************************************/
/*! \brief      Initializes all Ports of the passed EthTSyn controller.
 *  \details    -
 *  \param[in]  EthTSynCtrlIdx   Index of the EthTSyn controller the Ports should be initialized for.
 *                               [range: EthTSynCtrlIdx < EthTSyn_GetSizeOfCtrl()]
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *  \spec
 *    requires EthTSynCtrlIdx < EthTSyn_GetSizeOfCtrl();
 *  \endspec
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_ResetPortsAndPdelayOfCtrl(
  EthTSyn_IntCtrlIdxType EthTSynCtrlIdx);

#if (ETHTSYN_TX_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_TxConf_GetTxPortAndMsgType
 *********************************************************************************************************************/
/*! \brief      Get EthTSyn-Port and message type the TxConfirmation was called for.
 *  \details    -
 *  \param[in]  EthTSynCtrlIdx  Index of the EthTSyn controller
 *                              [range: EthTSynCtrlIdx < EthTSyn_GetSizeOfCtrl()]
 *  \param[in]  TxBufIdx        Transmission buffer index
 *  \param[out] MsgTypePtr      Type of the message the TxConfirmation was called for
 *  \return     EthTSyn_GetSizeOfPort() - Port or message type not found.
 *  \return     other values (< EthTSyn_GetSizeOfPort()) - Index of the Tx-Port. Message type is valid.
 *  \pre        Has to be called in the context of EthTSyn_TxConfirmation()
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *  \note       Out parameters are only modified in case of success (i.e. return == E_OK)
 *  \spec
 *    requires EthTSynCtrlIdx < EthTSyn_GetSizeOfCtrl();
 *  \endspec
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_IntPortIdxType, ETHTSYN_CODE) EthTSyn_TxConf_GetTxPortAndMsgType(
                EthTSyn_IntCtrlIdxType  EthTSynCtrlIdx,
                uint8                   TxBufIdx,
  ETHTSYN_P2VAR(uint8)                  MsgTypePtr);

/**********************************************************************************************************************
 *  EthTSyn_TxConf_GetEgressTsAsVlt
 *********************************************************************************************************************/
/*! \brief      Get the egress timestamp as internal virtual local time.
 *  \details    Gets either the HW egress timestamp converted to internal virtual local time or the current SW
 *              virtual local time.
 *  \param[in]  EthIfCtrlIdx   Index of the EthIf controller
 *  \param[in]  BufIdx         Index of the Ethernet Tx buffer
 *  \param[in]  TimeBaseId     The synchronized time base id for which the egress timestamp is required
 *  \return     The egress timestamp as internal virtual local time and its validity information
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  FALSE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_IntVltMgmtType, ETHTSYN_CODE) EthTSyn_TxConf_GetEgressTsAsVlt(
  uint8                         EthIfCtrlIdx,
  uint8                         BufIdx,
  StbM_SynchronizedTimeBaseType TimeBaseId);

/**********************************************************************************************************************
 *  EthTSyn_TxConf_AssignEgressTs
 *********************************************************************************************************************/
/*! \brief      Assigns the egress timestamp to state machine.
 *  \details    Assigns the passed egress timestamp to the state machine (and message of the state machine) which
 *              triggered the transmission of the message.
 *  \param[in]  PortIdx              Index of the EthTSyn port the message was transmitted on
 *                                   [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \param[in]  MsgType              The type of the transmitted message
 *  \param[in]  EgressIntVltMgmtPtr  The egress timestamp as internal virtual local time and its validity info
 *  \pre        For PortIdx the following constraints apply depending on MsgType
 *              ETHTSYN_MSG_TYPE_SYNC: EthTSyn_IsMasterPortUsedOfPort() == TRUE
 *              ETHTSYN_MSG_TYPE_PDELAY_REQ: EthTSyn_IsPdelayConfigUsedOfPort() == TRUE &&
 *                                           EthTSyn_GetPortIdxOfPdelayConfig() == PortIdx &&
 *                                           EthTSyn_IsPdelayInitiatorUsedOfPdelayConfig() == TRUE
 *              ETHTSYN_MSG_TYPE_PDELAY_RESP: EthTSyn_IsPdelayConfigUsedOfPort() == TRUE &&
 *                                            EthTSyn_GetPortIdxOfPdelayConfig() == PortIdx &&
 *                                            EthTSyn_IsPdelayResponderUsedOfPdelayConfig() == TRUE
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different PortIdx - MsgType tuples
 *  \spec
 *    requires PortIdx < EthTSyn_GetSizeOfPort();
 *  \endspec
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_TxConf_AssignEgressTs(
                  EthTSyn_IntPortIdxType  PortIdx,
                  uint8                   MsgType,
  ETHTSYN_P2CONST(EthTSyn_IntVltMgmtType) EgressIntVltMgmtPtr);

/**********************************************************************************************************************
 *  EthTSyn_TxConf_ProcessTxConfirmation
 *********************************************************************************************************************/
/*! \brief      Process the TxConfirmation, i.e. handle state machines.
 *  \details    -
 *  \param[in]  EthIfCtrlIdx  Index of the EthIf controller
 *  \param[in]  BufIdx        Index of the Ethernet Tx buffer
 *  \param[in]  PortIdx       Index of the Port the message was transmitted on
 *                            [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \param[in]  MsgType       Type of the message the TxConfirmation was called for
 *  \pre        For PortIdx the following constraints apply depending on MsgType
 *              ETHTSYN_MSG_TYPE_SYNC: EthTSyn_IsMasterPortUsedOfPort() == TRUE
 *              ETHTSYN_MSG_TYPE_FOLLOW_UP: EthTSyn_IsMasterPortUsedOfPort() == TRUE
 *              ETHTSYN_MSG_TYPE_PDELAY_REQ: EthTSyn_IsPdelayConfigUsedOfPort() == TRUE &&
 *                                           EthTSyn_GetPortIdxOfPdelayConfig() == PortIdx &&
 *                                           EthTSyn_IsPdelayInitiatorUsedOfPdelayConfig() == TRUE
 *              ETHTSYN_MSG_TYPE_PDELAY_RESP: EthTSyn_IsPdelayConfigUsedOfPort() == TRUE &&
 *                                            EthTSyn_GetPortIdxOfPdelayConfig() == PortIdx &&
 *                                            EthTSyn_IsPdelayResponderUsedOfPdelayConfig() == TRUE
 *  \pre        Has to be called in the context of EthTSyn_TxConfirmation()
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different PortIdx - MsgType tuples.
 *  \spec
 *    requires PortIdx < EthTSyn_GetSizeOfPort();
 *  \endspec
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_TxConf_ProcessTxConfirmation(
  uint8                   EthIfCtrlIdx,
  uint8                   BufIdx,
  EthTSyn_IntPortIdxType  PortIdx,
  uint8                   MsgType);
#endif /* (ETHTSYN_TX_SUPPORT == STD_ON) */

/**********************************************************************************************************************
 *  EthTSyn_RxInd_IntRxIndication
 *********************************************************************************************************************/
/*! \brief      Processing of an received Ethernet EthTSyn frame.
 *  \details    -
 *  \param[in]  CtrlIdx      Index of the EthIf controller
 *  \param[in]  DataPtr      The Ethernet Rx buffer pointer
 *  \param[in]  LenByte      Length of received data
 *  \return     ETHTSYN_E_NO_ERROR - No DET error detected
 *  \return     other values - DET error code in case an DET error was detected
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  FALSE
 *  \note       Internal implementation of the EthTSyn_RxIndication
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(uint8, ETHTSYN_CODE) EthTSyn_RxInd_IntRxIndication(
                  uint8  CtrlIdx,
  ETHTSYN_P2CONST(uint8) DataPtr,
                  uint16 LenByte);

/**********************************************************************************************************************
 *  EthTSyn_RxInd_GetIngressTsAsVlt
 *********************************************************************************************************************/
/*! \brief      Gets the ingress timestamp as internal virtual local time.
 *  \details    Gets either the HW ingress timestamp converted to internal virtual local time or the current SW
 *              virtual local time.
 *  \param[in]  EthIfCtrlIdx  Index of the EthIf controller
 *  \param[in]  RxBufPtr      The Ethernet Rx buffer pointer
 *  \return     The ingress timestamp as internal virtual local time and its validity information
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  FALSE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_IntVltMgmtType, ETHTSYN_CODE) EthTSyn_RxInd_GetIngressTsAsVlt(
                  uint8  EthIfCtrlIdx,
  ETHTSYN_P2CONST(uint8) RxBufPtr);

#if (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_OFF)
/**********************************************************************************************************************
 *  EthTSyn_RxInd_GetTimeDomainIdxFromRcvdMsg
 *********************************************************************************************************************/
 /*! \brief         Gets the time domain idx from a received emssage.
  *  \details       -
  *  \param[in]     RxBufPtr     The ethernet Rx buffer pointer
  *  \return        EthTSyn_GetSizeOfTimeDomain() - No valid time domain found
  *  \return        other values - Index of the corresponding time domain
  *  \pre           -
  *  \context       TASK|ISR2
  *  \reentrant     TRUE
  *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_IntTimeDomainIdxType, ETHTSYN_CODE) EthTSyn_RxInd_GetTimeDomainIdxFromRcvdMsg(
  ETHTSYN_P2CONST(uint8) RxBufPtr);
#endif /* (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_OFF) */

#if (ETHTSYN_SWT_MGMT_SUPPORT == STD_OFF)
/**********************************************************************************************************************
 *  EthTSyn_RxInd_ProcRcvdMsg
 *********************************************************************************************************************/
/*! \brief      Processes a received message.
 *  \details    Performs basic message checks, retrieves the port index on which the message was received and triggers
 *              the actual processing of the message.
 *  \param[in]  RxBufPtr             Pointer to the Rx-Buffer passed to the EthTSyn_RxIndication from EthIf
 *  \param[in]  LenByte              The received message length passed to EthTSyn_RxIndication() from EthIf
 *  \param[in]  EthTSynCtrlIdx       Index of the EthTSyn Ctrl the message was received on
 *                                   [range: EthTSynCtrlIdx < EthTSyn_GetSizeOfCtrl()]
 *  \param[in]  IngressTsVltMgmtPtr  The ingress timestamp as internal virtual local time and its validity info
 *  \return     ETHTSYN_E_NO_ERROR - Message was passed to sub-component for reception
 *  \return     other values - Any error occurred and message was not received. Corresponding error id is returned
 *  \pre        Has to be called in the context of EthTSyn_RxIndication()
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different EthTSyn controller indices.
 *  \spec
 *    requires EthTSynCtrlIdx < EthTSyn_GetSizeOfCtrl();
 *  \endspec
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(uint8, ETHTSYN_CODE) EthTSyn_RxInd_ProcRcvdMsg(
  ETHTSYN_P2CONST(uint8)                  RxBufPtr,
                  uint16                  LenByte,
                  EthTSyn_IntCtrlIdxType  EthTSynCtrlIdx,
  ETHTSYN_P2CONST(EthTSyn_IntVltMgmtType) IngressTsVltMgmtPtr);
#endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_OFF) */

#if (ETHTSYN_SWT_MGMT_SUPPORT == STD_OFF)
/**********************************************************************************************************************
 *  EthTSyn_RxInd_PerformBasicMsgChecksAndGetPort
 *********************************************************************************************************************/
/*! \brief      Performs basic message checks and gets the EthTSyn Port the message was received on.
 *  \details    -
 *  \param[in]  EthTSynCtrlIdx  Index of the EthTSyn Ctrl the message was received on
 *                              [range: EthTSynCtrlIdx < EthTSyn_GetSizeOfCtrl()]
 *  \param[in]  LenByte         The received message length passed to EthTSyn_RxIndication() from EthIf
 *  \param[in]  RxBufPtr        Pointer to the Rx-Buffer passed to the EthTSyn_RxIndication from EthIf
 *  \param[out] PortIdxPtr      Index of the EthTSyn Port the message was received on
 *  \return     ETHTSYN_E_NO_ERROR - Basic message checks passed. Out parameter is valid.
 *  \return     other values - Basic message check failed. Corresponding error id is returned.
 *  \pre        Has to be called in the context of EthTSyn_RxIndication()
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *  \note       Verification of message type, length and protocol version.
 *  \spec
 *    requires EthTSynCtrlIdx < EthTSyn_GetSizeOfCtrl();
 *  \endspec
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(uint8, ETHTSYN_CODE) EthTSyn_RxInd_PerformBasicMsgChecksAndGetPort(
                  EthTSyn_IntCtrlIdxType   EthTSynCtrlIdx,
                  uint16                   LenByte,
  ETHTSYN_P2CONST(uint8)                   RxBufPtr,
    ETHTSYN_P2VAR(EthTSyn_IntPortIdxType)  PortIdxPtr);
#endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_OFF) */

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  EthTSyn_SetLocalClockIdentity
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetLocalClockIdentity(
  EthTSyn_IntCtrlIdxType EthTSynCtrlIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Eth_PhysAddrType physAddr;
  ETHTSYN_P2VAR(EthTSyn_CtrlStateType) ctrlStatePtr = EthTSyn_GetAddrCtrlState(EthTSynCtrlIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Get the physical address for the EthIf controller of the passed EthTSyn controller. */
  EthIf_GetPhysAddr(EthTSyn_GetEthIfCtrlIdxOfCtrl(EthTSynCtrlIdx), &physAddr[0]);                                      /* VCA_ETHTSYN_REF_OF_LOC_VAR_PHYS_ADDR */

  /* #20 Derive the clock identity from the physical address according to IEEE802.1As and store it. */
  /* According to IEEE802.1As the clock identity is an EUI-64 derived by the EUI-48 MAC address in the following way:
   * 1. Assign higher three bytes of MAC address (OUI) to higher three of the clock identity
   * 2. Assign 0xFF and 0xFE to bytes 3 respectively 4 to clock identity
   * 3. Assign lower three bytes of MAC address to lower three bytes of the clock identity */
  ctrlStatePtr->ClockIdentity = (uint64)(
    ((uint64)physAddr[0u] << 56u) | ((uint64)physAddr[1u] << 48u) | ((uint64)physAddr[2u] << 40u) |
    ((uint64)ETHTSYN_IEEE_802_1_AS_CLOCK_IDENTITY_BYTE_3 << 32u) |
    ((uint64)ETHTSYN_IEEE_802_1_AS_CLOCK_IDENTITY_BYTE_4 << 24u) |
    ((uint64)physAddr[3u] << 16u) | ((uint64)physAddr[4u] << 8u) | ((uint64)physAddr[5u])
    );
} /* EthTSyn_SetLocalClockIdentity() */

/**********************************************************************************************************************
 *  EthTSyn_InitPort
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_InitPort(
  EthTSyn_IntPortIdxType PortIdx)
{
  /* ----- Implementation ----------------------------------------------- */
#if ( (ETHTSYN_MASTER_SUPPORT == STD_ON) && (ETHTSYN_SLAVE_SUPPORT == STD_ON) )
  /* #10 Check Port role. */
  if(EthTSyn_IsMasterPortUsedOfPort(PortIdx) == TRUE)
#endif /* ( (ETHTSYN_MASTER_SUPPORT == STD_ON) && (ETHTSYN_SLAVE_SUPPORT == STD_ON) ) */
  {
#if (ETHTSYN_MASTER_SUPPORT == STD_ON)
    /* #100 Master Port -> Trigger initialization of master port. */
    const EthTSyn_MasterPortIdxOfPortType masterPortIdx = EthTSyn_GetMasterPortIdxOfPort(PortIdx);
    /*@ assert masterPortIdx < EthTSyn_GetSizeOfMasterPort(); */                                                       /* VCA_ETHTSYN_OPT_IND_CSL03 */
    EthTSyn_Master_InitPort(masterPortIdx);
#endif /* (ETHTSYN_MASTER_SUPPORT == STD_ON) */
  }
#if ( (ETHTSYN_MASTER_SUPPORT == STD_ON) && (ETHTSYN_SLAVE_SUPPORT == STD_ON) )
  else
#endif /* ( (ETHTSYN_MASTER_SUPPORT == STD_ON) && (ETHTSYN_SLAVE_SUPPORT == STD_ON) ) */
  {
    /* #101 Slave Port -> Trigger initialization of slave port. */
#if (ETHTSYN_SLAVE_SUPPORT == STD_ON)
    const EthTSyn_SlavePortIdxOfPortType slavePortIdx = EthTSyn_GetSlavePortIdxOfPort(PortIdx);
    /*@ assert slavePortIdx < EthTSyn_GetSizeOfSlavePort(); */                                                         /* VCA_ETHTSYN_OPT_IND_CSL03 */
    EthTSyn_Slave_InitPort(slavePortIdx);
#endif /* (ETHTSYN_SLAVE_SUPPORT == STD_ON) */
  }

  /* #20 Initialize the debounce timer (if EthTSyn transmits any message). */
#if (ETHTSYN_TX_SUPPORT == STD_ON)
  EthTSyn_UtilTx_InitDebounceTimer(EthTSyn_GetPhysPortCfgIdxOfPort(PortIdx));
#endif /* (ETHTSYN_TX_SUPPORT == STD_ON) */
} /* End of EthTSyn_InitPort() */

/**********************************************************************************************************************
 * EthTSyn_InitCtrl
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_InitCtrl(
  EthTSyn_CtrlIterType EthTSynCtrlIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  ETHTSYN_CONSTP2VAR(EthTSyn_CtrlStateType) ctrlStatePtr = EthTSyn_GetAddrCtrlState(EthTSynCtrlIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* If module was not initialized yet, initialize transceiver link state. */
  if(EthTSyn_State == ETHTSYN_STATE_UNINIT)
  {
    ctrlStatePtr->TrcvLinkState = ETHTRCV_LINK_STATE_DOWN;
  }
  ctrlStatePtr->TransmissionMode = ETHTSYN_TX_ON;
  ctrlStatePtr->ClockIdentity = 0u;
} /* EthTSyn_InitCtrl() */

/**********************************************************************************************************************
 * EthTSyn_ResetPortsAndPdelayOfCtrl
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_ResetPortsAndPdelayOfCtrl(
  EthTSyn_IntCtrlIdxType EthTSynCtrlIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthTSyn_PortIndIterType portIter;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate all EthTSyn ports of the given EthTSyn controller. */
  for(portIter = EthTSyn_GetPortIndStartIdxOfCtrl(EthTSynCtrlIdx);
      portIter < EthTSyn_GetPortIndEndIdxOfCtrl(EthTSynCtrlIdx);
      portIter++)
  {
    const EthTSyn_IntPortIdxType portIdx = EthTSyn_GetPortInd(portIter);
    /*@ assert portIdx < EthTSyn_GetSizeOfPort(); */                                                                   /* VCA_ETHTSYN_PORT_IND_TABLE_CSL03 */

    /* #100 Init the current EthTSyn port. */
    EthTSyn_InitPort(portIdx);

    /* #101 Trigger Pdelay initialization. */
    if(EthTSyn_IsPdelayConfigUsedOfPort(portIdx) == TRUE)
    {
      EthTSyn_Pdelay_InitPdelayOfPort(portIdx);
    }
  }
} /* EthTSyn_ResetPortsAndPdelayOfCtrl() */

#if (ETHTSYN_TX_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_TxConf_GetTxPortAndMsgType
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
/* PRQA S 6050 1 */ /* MD_EthTSyn_6050_CslAccess */
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_IntPortIdxType, ETHTSYN_CODE) EthTSyn_TxConf_GetTxPortAndMsgType(
                EthTSyn_IntCtrlIdxType  EthTSynCtrlIdx,
                uint8                   TxBufIdx,
  ETHTSYN_P2VAR(uint8)                  MsgTypePtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthTSyn_PortIndIterType portIndIter;
  EthTSyn_IntPortIdxType portIdxRetVal = EthTSyn_GetSizeOfPort();

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all Ports of the EthTSyn controller. */
  for(portIndIter = EthTSyn_GetPortIndStartIdxOfCtrl(EthTSynCtrlIdx);
      portIndIter < EthTSyn_GetPortIndEndIdxOfCtrl(EthTSynCtrlIdx);
      portIndIter++)
  {
    const EthTSyn_PortIndType portIdx = EthTSyn_GetPortInd(portIndIter);
    /*@ assert portIdx < EthTSyn_GetSizeOfPort(); */                                                                   /* VCA_ETHTSYN_PORT_IND_TABLE_CSL03 */
    uint8 msgType = ETHTSYN_MSG_TYPE_INVALID;

    /* #100 Check if any message was transmitted on the current port using the given Tx-Buffer. */
# if (ETHTSYN_PDELAY_INITIATOR_SUPPORT == STD_ON)
    if(EthTSyn_Util_IsPdelayInitiator(portIdx) == TRUE)
    {
      const EthTSyn_PdelayConfigIdxOfPortType pDelayCfgIdx = EthTSyn_GetPdelayConfigIdxOfPort(portIdx);
      /*@ assert pDelayCfgIdx < EthTSyn_GetSizeOfPdelayConfig(); */                                                    /* VCA_ETHTSYN_IS_PD_INITIATOR_CSL03 */
      const EthTSyn_PdelayInitiatorIdxOfPdelayConfigType pDelayInitiatorIdx =
        EthTSyn_GetPdelayInitiatorIdxOfPdelayConfig(pDelayCfgIdx);
      /*@ assert pDelayInitiatorIdx < EthTSyn_GetSizeOfPdelayInitiator(); */                                           /* VCA_ETHTSYN_IS_PD_INITIATOR_CSL03 */
      const EthTSyn_PdelayReqSmIdxOfPdelayInitiatorType pDelayReqSmIdx =
        EthTSyn_GetPdelayReqSmIdxOfPdelayInitiator(pDelayInitiatorIdx);
      ETHTSYN_CONSTP2CONST(EthTSyn_PdelayReqSmType) pDelayReqSmPtr = EthTSyn_GetAddrPdelayReqSm(pDelayReqSmIdx);

      if(pDelayReqSmPtr->TxBuf.Index == TxBufIdx)
      {
        /* Port and message type found */
        msgType = ETHTSYN_MSG_TYPE_PDELAY_REQ;
      }
    }
# endif /* (ETHTSYN_PDELAY_INITIATOR_SUPPORT == STD_ON) */

# if (ETHTSYN_PDELAY_RESPONDER_SUPPORT == STD_ON)
    if(EthTSyn_Util_IsPdelayResponder(portIdx) == TRUE)
    {
      const EthTSyn_PdelayConfigIdxOfPortType pDelayCfgIdx = EthTSyn_GetPdelayConfigIdxOfPort(portIdx);
      /*@ assert pDelayCfgIdx < EthTSyn_GetSizeOfPdelayConfig(); */                                                    /* VCA_ETHTSYN_IS_PD_RESPONDER_CSL03 */
      const EthTSyn_PdelayResponderIdxOfPdelayConfigType pDelayResponderIdx =
        EthTSyn_GetPdelayResponderIdxOfPdelayConfig(pDelayCfgIdx);
      /*@ assert pDelayResponderIdx < EthTSyn_GetSizeOfPdelayResponder(); */                                           /* VCA_ETHTSYN_IS_PD_RESPONDER_CSL03 */
      const EthTSyn_PdelayRespSmIdxOfPdelayResponderType pDelayRespSmIdx =
        EthTSyn_GetPdelayRespSmIdxOfPdelayResponder(pDelayResponderIdx);
      ETHTSYN_CONSTP2CONST(EthTSyn_PdelayRespSmType) pDelayRespSmPtr = EthTSyn_GetAddrPdelayRespSm(pDelayRespSmIdx);

      if(pDelayRespSmPtr->TxBuf.Index == TxBufIdx)
      {
        msgType = ETHTSYN_MSG_TYPE_PDELAY_RESP;
      }
    }
# endif /* (ETHTSYN_PDELAY_RESPONDER_SUPPORT == STD_ON) */

# if (ETHTSYN_MASTER_SUPPORT == STD_ON)
    if(EthTSyn_IsMasterPortUsedOfPort(portIdx) == TRUE)
    {
      const EthTSyn_MasterPortIdxOfPortType masterPortIdx = EthTSyn_GetMasterPortIdxOfPort(portIdx);
      /*@ assert masterPortIdx < EthTSyn_GetSizeOfMasterPort(); */                                                     /* VCA_ETHTSYN_OPT_IND_CSL03 */
      EthTSyn_Master_PortSyncSend_CheckForMatchingTxConf(masterPortIdx, TxBufIdx, &msgType);
    }
# endif /* (ETHTSYN_MASTER_SUPPORT == STD_ON) */

    if(msgType != ETHTSYN_MSG_TYPE_INVALID)
    {
      /* #20 Port and message type found. Set out parameters and stop iteration of Ports. */
      portIdxRetVal = portIdx;
      (*MsgTypePtr) = msgType;
      break;
    }
  } /* END: Iteration of Ports for the given Controller */

  return portIdxRetVal;
} /* EthTSyn_TxConf_GetTxPortAndMsgType() */

/**********************************************************************************************************************
 *  EthTSyn_TxConf_GetEgressTsAsVlt
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_IntVltMgmtType, ETHTSYN_CODE) EthTSyn_TxConf_GetEgressTsAsVlt(
  uint8                         EthIfCtrlIdx,
  uint8                         BufIdx,
  StbM_SynchronizedTimeBaseType TimeBaseId)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthTSyn_IntVltMgmtType intVltMgmt = {0u, FALSE};
# if (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_ON)
  Eth_TimeStampType ethEgressTs = { 0u, 0u, 0u };
  Eth_TimeStampQualType ethEgressTsQual = ETH_INVALID;
# else
  StbM_VirtualLocalTimeType currVlt = { 0u, 0u };
# endif /* (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_ON) */

  /* ----- Implementation ----------------------------------------------- */
# if (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_ON)
  /* #10 If HW-Timestamping is used, get the Ethernet egress timestamp via EthIf_GetEgressTimestamp() and convert it
   *     into an internal virtual local time. */
  if(EthIf_GetEgressTimestamp(EthIfCtrlIdx, BufIdx, &ethEgressTs, &ethEgressTsQual) == E_OK)                           /* VCA_ETHTSYN_REF_OF_LOC_VAR */
  {
    if(ethEgressTsQual == ETH_VALID)
    {
      intVltMgmt.IntVlt = EthTSyn_UtilVlt_TsToIntVlt(&ethEgressTs);
      intVltMgmt.IntVltValid = TRUE;
    }
  }
  ETHTSYN_DUMMY_STATEMENT(TimeBaseId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
# else
  /* #20 Other, SW-Timestamping is used. Get the current virtual local time from the StbM via
   *     StbM_GetCurrentVirtualLocalTime() and convert it into an internal virtual local time. */
  if(StbM_GetCurrentVirtualLocalTime(TimeBaseId, &currVlt) == E_OK)                                                    /* VCA_ETHTSYN_REF_OF_LOC_VAR */
  {
    intVltMgmt.IntVlt = EthTSyn_UtilVlt_VltToIntVlt(&currVlt);
    intVltMgmt.IntVltValid = TRUE;
  }
  ETHTSYN_DUMMY_STATEMENT(EthIfCtrlIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
  ETHTSYN_DUMMY_STATEMENT(BufIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
# endif /*  (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_ON) */

  return intVltMgmt;
} /* EthTSyn_TxConf_GetEgressTsAsVlt() */

/**********************************************************************************************************************
 *  EthTSyn_TxConf_AssignEgressTs
 *********************************************************************************************************************/
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
 */
/* PRQA S 6050 1 */ /* MD_EthTSyn_6050_CslAccess */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_TxConf_AssignEgressTs(
                  EthTSyn_IntPortIdxType  PortIdx,
                  uint8                   MsgType,
  ETHTSYN_P2CONST(EthTSyn_IntVltMgmtType) EgressIntVltMgmtPtr)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check the message type. */
  switch(MsgType)
  {
# if (ETHTSYN_MASTER_SUPPORT == STD_ON)
    /* #20 If message type is Sync (if Master support is enabled). */
  case ETHTSYN_MSG_TYPE_SYNC:
    {
      /* #200 Handle the sync egress timestamp. */
      const EthTSyn_MasterPortIdxOfPortType masterPortIdx = EthTSyn_GetMasterPortIdxOfPort(PortIdx);
      /*@ assert masterPortIdx < EthTSyn_GetSizeOfMasterPort(); */                                                     /* VCA_ETHTSYN_INT_FUNC_IDX_PARAM */
      EthTSyn_Master_PortSyncSend_ProvideSyncHostEgrIntVlt(masterPortIdx, EgressIntVltMgmtPtr);
      break;
    }
# endif /* (ETHTSYN_MASTER_SUPPORT == STD_ON) */

# if (ETHTSYN_PDELAY_INITIATOR_SUPPORT == STD_ON)
#  if (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_OFF)
    /* #30 If message type is Pdelay_Req (if Pdelay initiator support is enabled). */
  case ETHTSYN_MSG_TYPE_PDELAY_REQ:
    {
      /* #300 Assign the egress timestamp to the corresponding PdelayReqSm. */
      const EthTSyn_PdelayConfigIdxOfPortType pdelayCfgIdx = EthTSyn_GetPdelayConfigIdxOfPort(PortIdx);
      /*@ assert pdelayCfgIdx < EthTSyn_GetSizeOfPdelayConfig(); */                                                    /* VCA_ETHTSYN_INT_FUNC_IDX_PARAM */
      const EthTSyn_PdelayInitiatorIdxOfPdelayConfigType pdelayInitiatorIdx =
        EthTSyn_GetPdelayInitiatorIdxOfPdelayConfig(pdelayCfgIdx);
      /*@ assert pdelayInitiatorIdx < EthTSyn_GetSizeOfPdelayInitiator(); */                                           /* VCA_ETHTSYN_INT_FUNC_IDX_PARAM */
      const EthTSyn_PdelayReqSmIdxOfPdelayInitiatorType pdelayReqSmIdx =
        EthTSyn_GetPdelayReqSmIdxOfPdelayInitiator(pdelayInitiatorIdx);
      ETHTSYN_CONSTP2VAR(EthTSyn_PdelayReqSmType) pDelayReqSmPtr = EthTSyn_GetAddrPdelayReqSm(pdelayReqSmIdx);

      pDelayReqSmPtr->PdelayReq.EgressTsMgmt = EthTSyn_UtilVlt_IntVltMgmtToTsMgmt(EgressIntVltMgmtPtr);
      break;
    }
#  endif /* (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_OFF) */
# endif /* (ETHTSYN_PDELAY_INITIATOR_SUPPORT == STD_ON) */

# if (ETHTSYN_PDELAY_RESPONDER_SUPPORT == STD_ON)
#  if (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_OFF)
    /* #40 If message type is Pdelay_Resp (if Pdelay responder support is enabled). */
  case ETHTSYN_MSG_TYPE_PDELAY_RESP:
    {
      /* #400 Assign the egress timestamp to the corresponding PdelayRespSm. */
      const EthTSyn_PdelayConfigIdxOfPortType pdelayCfgIdx = EthTSyn_GetPdelayConfigIdxOfPort(PortIdx);
      /*@ assert pdelayCfgIdx < EthTSyn_GetSizeOfPdelayConfig(); */                                                    /* VCA_ETHTSYN_INT_FUNC_IDX_PARAM */
      const EthTSyn_PdelayResponderIdxOfPdelayConfigType pdelayResponderIdx =
        EthTSyn_GetPdelayResponderIdxOfPdelayConfig(pdelayCfgIdx);
      /*@ assert pdelayResponderIdx < EthTSyn_GetSizeOfPdelayResponder(); */                                           /* VCA_ETHTSYN_INT_FUNC_IDX_PARAM */
      const EthTSyn_PdelayRespSmIdxOfPdelayResponderType pdelayRespSmIdx =
        EthTSyn_GetPdelayRespSmIdxOfPdelayResponder(pdelayResponderIdx);
      ETHTSYN_CONSTP2VAR(EthTSyn_PdelayRespSmType) pDelayRespSmPtr = EthTSyn_GetAddrPdelayRespSm(pdelayRespSmIdx);

      pDelayRespSmPtr->PdelayResp.EgressTsMgmt = EthTSyn_UtilVlt_IntVltMgmtToTsMgmt(EgressIntVltMgmtPtr);
      break;
    }
#  endif /* (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_OFF) */
# endif /* (ETHTSYN_PDELAY_RESPONDER_SUPPORT == STD_ON) */

    /* #50 Otherwise, do nothing and discard egress timestamp. */
  default:
    {
      /* Nothing to do here. */
      break;
    }
  }
} /* EthTSyn_TxConf_AssignEgressTs() */

/**********************************************************************************************************************
 *  EthTSyn_TxConf_ProcessTxConfirmation
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
/* PRQA S 6050 1 */ /* MD_EthTSyn_6050_CslAccess */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_TxConf_ProcessTxConfirmation(
  uint8                  EthIfCtrlIdx,
  uint8                  BufIdx,
  EthTSyn_IntPortIdxType PortIdx,
  uint8                  MsgType)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Perform required actions for the message type. */
  switch(MsgType)
  {
# if (ETHTSYN_PDELAY_INITIATOR_SUPPORT == STD_ON)
  case ETHTSYN_MSG_TYPE_PDELAY_REQ:
    {
      const EthTSyn_PdelayConfigIdxOfPortType pDelayCfgIdx = EthTSyn_GetPdelayConfigIdxOfPort(PortIdx);
      /*@ assert pDelayCfgIdx < EthTSyn_GetSizeOfPdelayConfig(); */                                                    /* VCA_ETHTSYN_INT_FUNC_IDX_PARAM */
      const EthTSyn_PdelayInitiatorIdxOfPdelayConfigType pDelayInitiatorIdx =
        EthTSyn_GetPdelayInitiatorIdxOfPdelayConfig(pDelayCfgIdx);
      /*@ assert pDelayInitiatorIdx < EthTSyn_GetSizeOfPdelayInitiator(); */                                           /* VCA_ETHTSYN_INT_FUNC_IDX_PARAM */
      const EthTSyn_PdelayReqSmIdxOfPdelayInitiatorType pDelayReqSmIdx =
        EthTSyn_GetPdelayReqSmIdxOfPdelayInitiator(pDelayInitiatorIdx);

      EthTSyn_PdelayReqSmPtrType pDelayReqSmPtr = EthTSyn_GetAddrPdelayReqSm(pDelayReqSmIdx);

#  if (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON)
      EthTSyn_SwtMgmt_Tx_SetupTxMgmtObj(EthIfCtrlIdx, BufIdx, NULL_PTR, &pDelayReqSmPtr->PdelayReq.EgressTsMgmt);
#  endif /* (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON) */

      pDelayReqSmPtr->TxBuf.Index = ETHTSYN_INV_BUF_IDX;
      pDelayReqSmPtr->TxConfirmationPending--;

      break;
    }
# endif /* (ETHTSYN_PDELAY_INITIATOR_SUPPORT == STD_ON) */

# if (ETHTSYN_PDELAY_RESPONDER_SUPPORT == STD_ON)
  case ETHTSYN_MSG_TYPE_PDELAY_RESP:
    {
      const EthTSyn_PdelayConfigIdxOfPortType pDelayCfgIdx = EthTSyn_GetPdelayConfigIdxOfPort(PortIdx);
      /*@ assert pDelayCfgIdx < EthTSyn_GetSizeOfPdelayConfig(); */                                                    /* VCA_ETHTSYN_INT_FUNC_IDX_PARAM */
      const EthTSyn_PdelayResponderIdxOfPdelayConfigType pDelayResponderIdx =
        EthTSyn_GetPdelayResponderIdxOfPdelayConfig(pDelayCfgIdx);
      /*@ assert pDelayResponderIdx < EthTSyn_GetSizeOfPdelayResponder(); */                                           /* VCA_ETHTSYN_INT_FUNC_IDX_PARAM */
      const EthTSyn_PdelayRespSmIdxOfPdelayResponderType pDelayRespSmIdx =
        EthTSyn_GetPdelayRespSmIdxOfPdelayResponder(pDelayResponderIdx);

      EthTSyn_PdelayRespSmPtrType pDelayRespSmPtr = EthTSyn_GetAddrPdelayRespSm(pDelayRespSmIdx);

#  if (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON)
      EthTSyn_SwtMgmt_Tx_SetupTxMgmtObj(EthIfCtrlIdx, BufIdx, NULL_PTR, &pDelayRespSmPtr->PdelayResp.EgressTsMgmt);
#  endif /* (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON) */

      pDelayRespSmPtr->TxBuf.Index = ETHTSYN_INV_BUF_IDX;
      pDelayRespSmPtr->TxConfirmationPending--;

      break;
    }
# endif /* (ETHTSYN_PDELAY_RESPONDER_SUPPORT == STD_ON) */

# if (ETHTSYN_MASTER_SUPPORT == STD_ON)
  case ETHTSYN_MSG_TYPE_SYNC:
    {
      const EthTSyn_MasterPortIdxOfPortType masterPortIdx = EthTSyn_GetMasterPortIdxOfPort(PortIdx);
      /*@ assert masterPortIdx < EthTSyn_GetSizeOfMasterPort(); */                                                     /* VCA_ETHTSYN_INT_FUNC_IDX_PARAM */
      EthTSyn_Master_PortSyncSend_ProcSyncTxConf(masterPortIdx, EthIfCtrlIdx);
      break;
    }

  case ETHTSYN_MSG_TYPE_FOLLOW_UP:
    {
      const EthTSyn_MasterPortIdxOfPortType masterPortIdx = EthTSyn_GetMasterPortIdxOfPort(PortIdx);
      /*@ assert masterPortIdx < EthTSyn_GetSizeOfMasterPort(); */                                                     /* VCA_ETHTSYN_INT_FUNC_IDX_PARAM */
      EthTSyn_Master_PortSyncSend_ProcFupTxConf(masterPortIdx);
      break;
    }
# endif /* (ETHTSYN_MASTER_SUPPORT == STD_ON) */

  default:
    {
      /* Nothing to do here. */
      break;
    }
  } /* PRQA S 3315 */ /* MD_EthTSyn_3315 */

# if (ETHTSYN_MASTER_SUPPORT == STD_OFF)
  /* EthIfCtrlIdx is also used when Switch timestamping is enabled. However, a bridge configuration without
   * Master-Support is not sensible. Therefore a subsequent check if Switch timestamping is disabled as well is not
   * required. */
  ETHTSYN_DUMMY_STATEMENT(EthIfCtrlIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
# endif /* (ETHTSYN_MASTER_SUPPORT == STD_OFF) */
  ETHTSYN_DUMMY_STATEMENT(BufIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */

} /* EthTSyn_TxConf_ProcessTxConfirmation() */
#endif /* (ETHTSYN_TX_SUPPORT == STD_ON) */

/**********************************************************************************************************************
 *  EthTSyn_RxInd_IntRxIndication
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(uint8, ETHTSYN_CODE) EthTSyn_RxInd_IntRxIndication(
                  uint8  CtrlIdx,
  ETHTSYN_P2CONST(uint8) DataPtr,
                  uint16 LenByte)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId;
  EthTSyn_IntVltMgmtType ingressVltMgmt;
  EthTSyn_IntCtrlIdxType ethTSynCtrlIdx;

  /* ----- Implementation ----------------------------------------------- */
#if (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_OFF)
  /* Critical section is used to ensure that the time between invocation of RxIndication and getting the
     software ingress timestamp is minimized. */
  ETHTSYN_ENTER_CRITICAL_SECTION_GET_TS();
#endif /* (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_OFF) */

  /* #10 Get the ingress timestamp. */
  ingressVltMgmt = EthTSyn_RxInd_GetIngressTsAsVlt(CtrlIdx, DataPtr);

#if (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_OFF)
  /* Leave critical section (if SW-Timestamping is used). */
  ETHTSYN_LEAVE_CRITICAL_SECTION_GET_TS();
#endif /* (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_OFF) */

  /* #20 Get and verify EthTSyn controller. */
  ethTSynCtrlIdx = EthTSyn_Util_GetEthTSynCtrlFromEthIfCtrl(CtrlIdx);

  if(ethTSynCtrlIdx < EthTSyn_GetSizeOfCtrl())
  {
    /* #30 Verify link state. */
    if(EthTSyn_GetCtrlState(ethTSynCtrlIdx).TrcvLinkState == ETHTRCV_LINK_STATE_ACTIVE)
    {
#if (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON)
      /* #40 Switch management enabled. Pass the received Frame to the Switch management. */
      errorId = EthTSyn_SwtMgmt_Rx_HndlMsgReception(DataPtr, LenByte, ethTSynCtrlIdx, &ingressVltMgmt);
#else
      /* #50 Switch management disabled. Handle message reception. */
      errorId = EthTSyn_RxInd_ProcRcvdMsg(DataPtr, LenByte, ethTSynCtrlIdx, &ingressVltMgmt);
#endif /* ETHTSYN_SWT_MGMT_SUPPORT */
    }
    else
    {
      errorId = ETHTSYN_E_TRCV_DOWN;
    }
  }
  else
  {
    errorId = ETHTSYN_E_CTRL_IDX;
  }

  return errorId;
} /* EthTSyn_RxInd_IntRxIndication() */

/**********************************************************************************************************************
 *  EthTSyn_RxInd_GetIngressTsAsVlt
 *********************************************************************************************************************/
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
 */
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_IntVltMgmtType, ETHTSYN_CODE) EthTSyn_RxInd_GetIngressTsAsVlt(
                  uint8  EthIfCtrlIdx,
  ETHTSYN_P2CONST(uint8) RxBufPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthTSyn_IntVltMgmtType intVltMgmt = {0u, FALSE};

  /* ----- Implementation ----------------------------------------------- */
#if (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_ON)
  /* #10 If HW timestamping is used. */
  {
    Eth_TimeStampType ethIngressTs = { 0u, 0u, 0u };
    Eth_TimeStampQualType ethIngressTsQual = ETH_INVALID;

    /* #100 Get the Ethernet ingress timestamp via EthIf_GetIngressTimestamp() and convert it into an internal virtual
     *      local time in case the ingress timestamp was successfully retrieved and is valid. */
    /* PRQA S 0310, 0311, 3305 1 */ /* MD_EthTSyn_PtrCast_EthBuffer */
    if(EthIf_GetIngressTimestamp(EthIfCtrlIdx, (ETHTSYN_P2VAR(Eth_DataType))RxBufPtr,                                  /* VCA_ETHTSYN_ETHIF_CALLED_WITH_ETH_RX_TX_BUF_AND_LOC_VAR_REF */
        &ethIngressTs, &ethIngressTsQual) == E_OK)
    {
      if(ethIngressTsQual == ETH_VALID)
      {
        intVltMgmt.IntVlt = EthTSyn_UtilVlt_TsToIntVlt(&ethIngressTs);
        intVltMgmt.IntVltValid = TRUE;
      }
    }

  }
#else
  /* #20 Otherwise, SW timestamping is used. */
  {
    /* #200 Get the time domain from the received message and check if the time domain is known by the EthTSyn. */
    EthTSyn_IntTimeDomainIdxType timeDomainIdx = EthTSyn_RxInd_GetTimeDomainIdxFromRcvdMsg(RxBufPtr);

    if(timeDomainIdx < EthTSyn_GetSizeOfTimeDomain())
    {
      /* #2000 Get the current virtual local time from the StbM via StbM_GetCurrentVirtualLocalTime() and
       *       convert it into internal representation in case the time was retrieved successfully. */
      StbM_VirtualLocalTimeType stbmVlt = { 0u, 0u };
      StbM_SynchronizedTimeBaseType timeBaseId = EthTSyn_GetSynchronizedTimeBaseIdOfTimeDomain(timeDomainIdx);

      if(StbM_GetCurrentVirtualLocalTime(timeBaseId, &stbmVlt) == E_OK)                                                /* VCA_ETHTSYN_REF_OF_LOC_VAR */
      {
        intVltMgmt.IntVlt = EthTSyn_UtilVlt_VltToIntVlt(&stbmVlt);
        intVltMgmt.IntVltValid = TRUE;
      }
    }

    ETHTSYN_DUMMY_STATEMENT(EthIfCtrlIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
  }
#endif /* (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_ON) */

  return intVltMgmt;
} /* EthTSyn_RxInd_GetIngressTsAsVlt() */

#if (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_OFF)
/**********************************************************************************************************************
 *  EthTSyn_RxInd_GetTimeDomainIdxFromRcvdMsg
 *********************************************************************************************************************/
 /*!
  * Internal comment removed.
 *
 *
 *
 *
 *
  */
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_IntTimeDomainIdxType, ETHTSYN_CODE) EthTSyn_RxInd_GetTimeDomainIdxFromRcvdMsg(
  ETHTSYN_P2CONST(uint8) RxBufPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthTSyn_IntTimeDomainIdxType timeDomainIdx = EthTSyn_GetSizeOfTimeDomain();
  EthTSyn_TimeDomainIterType timeDomainIter;
  uint8 timeDomainIdFromMsg;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Get the time domain id from the received message. */
  timeDomainIdFromMsg = IpBase_GetUint8(RxBufPtr, ETHTSYN_MSG_HDR_DOMAIN_NUM_OFS);

  /* #20 Iterate all configured time domains of the EthTSyn. */
  for(timeDomainIter = 0u;
    timeDomainIter < EthTSyn_GetSizeOfTimeDomain();
    timeDomainIter++)
  {
    /* #30 If current time domain id matches the one from the received message, stop iteration and return the
     *     time domain index. */
    if(EthTSyn_GetIdOfTimeDomain(timeDomainIter) == timeDomainIdFromMsg)
    {
      timeDomainIdx = (EthTSyn_IntTimeDomainIdxType)timeDomainIter;
      break;
    }
  }

  return timeDomainIdx;
} /* EthTSyn_RxInd_GetTimeDomainIdxFromRcvdMsg() */
#endif /* (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_OFF) */

#if (ETHTSYN_SWT_MGMT_SUPPORT == STD_OFF)
/**********************************************************************************************************************
 *  EthTSyn_RxInd_ProcRcvdMsg
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
/* PRQA S 6050 1 */ /* MD_EthTSyn_6050_MsgReception */
ETHTSYN_LOCAL_INLINE FUNC(uint8, ETHTSYN_CODE) EthTSyn_RxInd_ProcRcvdMsg(
  ETHTSYN_P2CONST(uint8)                  RxBufPtr,
                  uint16                  LenByte,
                  EthTSyn_IntCtrlIdxType  EthTSynCtrlIdx,
  ETHTSYN_P2CONST(EthTSyn_IntVltMgmtType) IngressTsVltMgmtPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId;
  EthTSyn_IntPortIdxType portIdx = EthTSyn_GetSizeOfPort();

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Perform basic message checks and get EthTSyn PortIdx. */
  errorId = EthTSyn_RxInd_PerformBasicMsgChecksAndGetPort(EthTSynCtrlIdx, LenByte, RxBufPtr, &portIdx);
  if(errorId == ETHTSYN_E_NO_ERROR)
  {
    /*@ assert portIdx < EthTSyn_GetSizeOfPort(); */                                                                   /* VCA_ETHTSYN_PORT_IDX_VALID_NO_ERROR_RETURNED */
    /* Port found -> continue processing of the message */
    /* #20 Get message type and process the message if applicable. */
    /* Shift of ETHTSYN_MSG_HDR_MSG_TYPE_SHIFT is not required because it is 0. */
    switch(IpBase_GetUint8(RxBufPtr, ETHTSYN_MSG_HDR_MSG_TYPE_OFS) & ETHTSYN_MSG_HDR_MSG_TYPE_MASK)
    {
# if (ETHTSYN_PDELAY_RESPONDER_SUPPORT == STD_ON)
    case ETHTSYN_MSG_TYPE_PDELAY_REQ:
      {
        EthTSyn_TsMgmtStructType ingressTsMgmt;
        ingressTsMgmt = EthTSyn_UtilVlt_IntVltMgmtToTsMgmt(IngressTsVltMgmtPtr);
        EthTSyn_Pdelay_ProcRcvdReqMsg(RxBufPtr, &ingressTsMgmt, portIdx);
        break;
      }
# endif /* (ETHTSYN_PDELAY_RESPONDER_SUPPORT == STD_ON) */

# if (ETHTSYN_PDELAY_INITIATOR_SUPPORT == STD_ON)
    case ETHTSYN_MSG_TYPE_PDELAY_RESP:
      {
        EthTSyn_TsMgmtStructType ingressTsMgmt;
        ingressTsMgmt = EthTSyn_UtilVlt_IntVltMgmtToTsMgmt(IngressTsVltMgmtPtr);
        EthTSyn_Pdelay_ProcRcvdRespMsg(RxBufPtr, &ingressTsMgmt, portIdx);
        break;
      }

    case ETHTSYN_MSG_TYPE_PDELAY_RES_FOLLOW_UP:
      {
        EthTSyn_Pdelay_ProcRcvdRespFupMsg(RxBufPtr, portIdx);
        break;
      }
# endif /* (ETHTSYN_PDELAY_INITIATOR_SUPPORT == STD_ON) */

    case ETHTSYN_MSG_TYPE_SYNC:
      {
        uint64 srcClockIdentity = IpBase_GetUint64(RxBufPtr, ETHTSYN_MSG_HDR_SRC_PORT_IDENT_CLOCK_IDENT_OFS);
# if (ETHTSYN_SLAVE_SUPPORT == STD_ON)
        if (EthTSyn_UtilRx_SyncPortRoleCheckWithMasterSlaveConflictDetection(portIdx, srcClockIdentity) == TRUE)
        {
          EthTSyn_SlaveRx_ProcRcvdSyncMsg(RxBufPtr, portIdx, IngressTsVltMgmtPtr);
        }
# else
        (void)EthTSyn_UtilRx_SyncPortRoleCheckWithMasterSlaveConflictDetection(portIdx, srcClockIdentity);
# endif /* (ETHTSYN_SLAVE_SUPPORT == STD_ON) */

        break;
      }

# if (ETHTSYN_SLAVE_SUPPORT == STD_ON)
    case ETHTSYN_MSG_TYPE_FOLLOW_UP:
      {
        EthTSyn_SlaveRx_ProcRcvdFupMsg(RxBufPtr, portIdx);
        break;
      }
# endif /* (ETHTSYN_SLAVE_SUPPORT == STD_ON) */

# if (ETHTSYN_ANNOUNCE_RX_SUPPORT == STD_ON)
    case ETHTSYN_MSG_TYPE_ANNOUNCE:
      {
        EthTSyn_Slave_ProcRcvdAnnounceMsg(RxBufPtr, portIdx);
        break;
      }
# endif /* (ETHTSYN_ANNOUNCE_RX_SUPPORT == STD_ON) */

    default:
      {
        /* Nothing to do here. */
        break;
      }
    }
  }

  ETHTSYN_DUMMY_STATEMENT(IngressTsVltMgmtPtr); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */

  return errorId;
} /* EthTSyn_RxInd_ProcRcvdMsg() */
#endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_OFF) */

/**********************************************************************************************************************
 *  EthTSyn_RxInd_PerformBasicMsgChecksAndGetPort
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
#if (ETHTSYN_SWT_MGMT_SUPPORT == STD_OFF)
/* PRQA S 6050 1 */ /* MD_EthTSyn_6050_CslAccess */
ETHTSYN_LOCAL_INLINE FUNC(uint8, ETHTSYN_CODE) EthTSyn_RxInd_PerformBasicMsgChecksAndGetPort(
                  EthTSyn_IntCtrlIdxType  EthTSynCtrlIdx,
                  uint16                  LenByte,
  ETHTSYN_P2CONST(uint8)                  RxBufPtr,
    ETHTSYN_P2VAR(EthTSyn_IntPortIdxType) PortIdxPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Perform general message checks. */
  errorId = EthTSyn_UtilRx_CheckMessageGeneral(RxBufPtr, LenByte);
  if(errorId == ETHTSYN_E_NO_ERROR)
  {
    /* #20 General message checks passed. Check message type and length. */
    errorId = EthTSyn_UtilRx_CheckMessageTypeAndLength(RxBufPtr, LenByte);
    if(errorId == ETHTSYN_E_NO_ERROR)
    {
      EthTSyn_PortIndIterType portIndIter;
      errorId = ETHTSYN_E_NO_PORT_FOUND;
      /* #30 Valid message type and length. Get the EthTSyn Port. */
      for(portIndIter = EthTSyn_GetPortIndStartIdxOfCtrl(EthTSynCtrlIdx);
          portIndIter < EthTSyn_GetPortIndEndIdxOfCtrl(EthTSynCtrlIdx);
          portIndIter++)
      {
        const EthTSyn_PortIndType tmpPort = EthTSyn_GetPortInd(portIndIter);
        /*@ assert tmpPort < EthTSyn_GetSizeOfPort(); */                                                               /* VCA_ETHTSYN_PORT_IND_TABLE_CSL03 */
        const EthTSyn_TimeDomainIdxOfPortType timeDomainIdx = EthTSyn_GetTimeDomainIdxOfPort(tmpPort);
        if(EthTSyn_GetIdOfTimeDomain(timeDomainIdx) == IpBase_GetUint8(RxBufPtr, ETHTSYN_MSG_HDR_DOMAIN_NUM_OFS))
        {
          /* #300 EthTSyn Port found. */
          (*PortIdxPtr) = tmpPort;
          errorId = ETHTSYN_E_NO_ERROR;
          break;
        }
      }
    }
  }

  return errorId;
} /* EthTSyn_RxInd_PerformBasicMsgChecksAndGetPort() */
#endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_OFF) */

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  EthTSyn_RxIndication
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
/* PRQA S 3673 8 */ /* MD_EthTSyn_3673_Ar */
/* PRQA S 6060, 6080 1 */ /* MD_MSR_STPAR, MD_MSR_STMIF */
FUNC(void, ETHTSYN_CODE) EthTSyn_RxIndication(
                uint8                  CtrlIdx,
                Eth_FrameType          FrameType,
                boolean                IsBroadcast,
                EthTSyn_PhyAddrPtrType PhysAddrPtr,
  ETHTSYN_P2VAR(uint8)                 DataPtr,
                uint16                 LenByte)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = ETHTSYN_E_NO_ERROR; /* PRQA S 2981 */ /* MD_EthTSyn_2981_ErrorId */

  /* ----- Development Error Checks ------------------------------------- */
#if (ETHTSYN_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check plausibility of input parameters. */
  if(EthTSyn_State == ETHTSYN_STATE_UNINIT)
  {
    errorId = ETHTSYN_E_NOT_INITIALIZED;
  }
  else if((DataPtr == NULL_PTR) || (PhysAddrPtr == NULL_PTR))
  {
    errorId = ETHTSYN_E_PARAM_POINTER;
  }
  else if(FrameType != ETHTSYN_FRAME_TYPE)
  {
    errorId = ETHTSYN_E_FRAME_TYPE;
  }
  else
#endif /* (ETHTSYN_DEV_ERROR_DETECT == STD_ON) */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Trigger the message reception. */
    errorId = EthTSyn_RxInd_IntRxIndication(CtrlIdx, DataPtr, LenByte);
  }

#if (ETHTSYN_DEV_ERROR_DETECT == STD_OFF)
  ETHTSYN_DUMMY_STATEMENT(FrameType); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
  ETHTSYN_DUMMY_STATEMENT(PhysAddrPtr); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* (ETHTSYN_DEV_ERROR_DETECT == STD_OFF) */
  ETHTSYN_DUMMY_STATEMENT(IsBroadcast); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */

  /* ----- Development Error Report ------------------------------------- */
#if (ETHTSYN_DEV_ERROR_REPORT == STD_ON)
  /* #30 Report error to default error tracer (DET) if any occurred. */
  if (errorId != ETHTSYN_E_NO_ERROR)
  {
    (void)Det_ReportError(ETHTSYN_MODULE_ID, ETHTSYN_INSTANCE_ID, ETHTSYN_SID_RX_INDICATION, errorId);
  }
#else
  ETHTSYN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif

} /* EthTSyn_RxIndication() */

#if (ETHTSYN_VERSION_INFO_API == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_GetVersionInfo
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, ETHTSYN_CODE) EthTSyn_GetVersionInfo(
  ETHTSYN_P2VAR(Std_VersionInfoType) VersionInfoPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = ETHTSYN_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if (ETHTSYN_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check VersionInfoPtr for NULL pointer. note: no uninit check is performed. */
  if(VersionInfoPtr == NULL_PTR)
  {
    errorId = ETHTSYN_E_PARAM_POINTER;
  }
  else
# endif
  {
    /* ----- Implementation --------------------------------------------- */
    /* #20 Set version info with corresponding macros from component header. */
    VersionInfoPtr->vendorID = (uint16)ETHTSYN_VENDOR_ID;
    VersionInfoPtr->moduleID = (uint16)ETHTSYN_MODULE_ID;
    VersionInfoPtr->sw_major_version = (uint8)ETHTSYN_SW_MAJOR_VERSION;
    VersionInfoPtr->sw_minor_version = (uint8)ETHTSYN_SW_MINOR_VERSION;
    VersionInfoPtr->sw_patch_version = (uint8)ETHTSYN_SW_PATCH_VERSION;
  }

  /* ----- Development Error Report ------------------------------------- */
# if (ETHTSYN_DEV_ERROR_REPORT == STD_ON)
  /* #30 Report error to default error tracer (DET) if any occurred. */
  if(errorId != ETHTSYN_E_NO_ERROR)
  {
    (void)Det_ReportError(ETHTSYN_MODULE_ID, ETHTSYN_INSTANCE_ID, ETHTSYN_SID_GET_VERSION_INFO, errorId);
  }
# else
  ETHTSYN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
# endif
} /* EthTSyn_GetVersionInfo() */
#endif /* (ETHTSYN_VERSION_INFO_API == STD_ON) */


/**********************************************************************************************************************
 *  EthTSyn_MainFunction
 *********************************************************************************************************************/
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
 */
/* PRQA S 6050 1 */ /* MD_EthTSyn_6050_CslAccess */
FUNC(void, ETHTSYN_CODE) EthTSyn_MainFunction(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = ETHTSYN_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if (ETHTSYN_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check initialization state of component. */
  if(EthTSyn_State == ETHTSYN_STATE_UNINIT)
  {
    errorId = ETHTSYN_E_NOT_INITIALIZED;
  }
  else
#endif /* (ETHTSYN_DEV_ERROR_DETECT == STD_ON) */
  {
    /* ----- Implementation ----------------------------------------------- */
    EthTSyn_TimeDomainIterType timeDomainIter;
#if (ETHTSYN_TX_SUPPORT == STD_ON)
    EthTSyn_PhysPortIterType physPortIter;
#endif /* (ETHTSYN_TX_SUPPORT == STD_ON) */

    /* #20 Decrement all debounce timer (if EthTSyn transmits any message). */
#if (ETHTSYN_TX_SUPPORT == STD_ON)
    for(physPortIter = 0u; physPortIter < EthTSyn_GetSizeOfPhysPort(); physPortIter++)
    {
      EthTSyn_UtilTx_DecDebounceTimer(physPortIter);
    }
#endif /* (ETHTSYN_TX_SUPPORT == STD_ON) */

    /* #30 Invoke main function of time validation unit (if TimeValidation feature is enabled). */
#if ( (ETHTSYN_MASTER_TIME_VALIDATION_SUPPORT == STD_ON) || (ETHTSYN_SLAVE_TIME_VALIDATION_SUPPORT == STD_ON) )
    EthTSyn_TimeValid_MainFunction();
#endif /* ( (ETHTSYN_MASTER_TIME_VALIDATION_SUPPORT == STD_ON) || (ETHTSYN_SLAVE_TIME_VALIDATION_SUPPORT == STD_ON) ) */

    /* #40 Iterate all TimeDomains. */
    for(timeDomainIter = 0; timeDomainIter < EthTSyn_GetSizeOfTimeDomain(); timeDomainIter++)
    {
      /* #400 Handle cyclic tasks for Master-Ports. */
#if (ETHTSYN_MASTER_SUPPORT == STD_ON)
      EthTSyn_Master_HandleCyclicTasks(timeDomainIter);
#endif /* (ETHTSYN_MASTER_SUPPORT == STD_ON) */

      /* #401 Handle cyclic tasks for Slave-Ports. */
#if (ETHTSYN_SLAVE_SUPPORT == STD_ON)
      EthTSyn_Slave_HandleCyclicTasks(timeDomainIter);
#endif /* (ETHTSYN_SLAVE_SUPPORT == STD_ON) */

      /* #402 Process site sync sync state machine if applicable. */
#if (ETHTSYN_SITESYNCSYNCSM == STD_ON)
      if(EthTSyn_IsSiteSyncSyncSmUsedOfTimeDomain(timeDomainIter) == TRUE)
      {
        /* SiteSyncSync state machine */
        EthTSyn_SwtMgmt_SiteSyncSync_ProcSm(timeDomainIter);
      }
#endif /* (ETHTSYN_SITESYNCSYNCSM == STD_ON) */
    } /* END: Iteration of TimeDomains */

    /* #50 Handle cyclic task for Pdelay. */
#if ( (ETHTSYN_PDELAY_INITIATOR_SUPPORT == STD_ON) || (ETHTSYN_PDELAY_RESPONDER_SUPPORT == STD_ON) )
    EthTSyn_Pdelay_HandleCyclicTasks();
#endif /* ( (ETHTSYN_PDELAY_INITIATOR_SUPPORT == STD_ON) || (ETHTSYN_PDELAY_RESPONDER_SUPPORT == STD_ON) ) */

    /* #60 Handle cycle tasks for switch time sync. */
#if (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON)
# if (ETHTSYN_SWT_TIME_SYNC_SUPPORT == STD_ON)
    EthTSyn_SwtTimeSync_HandleCyclicTasks();
# endif /* (ETHTSYN_SWT_TIME_SYNC_SUPPORT == STD_ON) */
#endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON) */

  }

  /* ----- Development Error Report ------------------------------------- */
#if (ETHTSYN_DEV_ERROR_REPORT == STD_ON)
  /* #70 Report error to default error tracer (DET) if any occurred. */
  if(errorId != ETHTSYN_E_NO_ERROR)
  {
    (void)Det_ReportError(ETHTSYN_MODULE_ID, ETHTSYN_INSTANCE_ID, ETHTSYN_SID_MAIN_FUNCTION, errorId);
  }
#else
  ETHTSYN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* (ETHTSYN_DEV_ERROR_REPORT == STD_ON) */

} /* EthTSyn_MainFunction() */

/**********************************************************************************************************************
 *  EthTSyn_InitMemory
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, ETHTSYN_CODE)  EthTSyn_InitMemory(void)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Set module state to unitialized. */
  EthTSyn_State = ETHTSYN_STATE_UNINIT;
}

/**********************************************************************************************************************
 *  EthTSyn_Init
 *********************************************************************************************************************/
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
 */
/* PRQA S 6050 1 */ /* MD_EthTSyn_6050_CslAccess */
FUNC(void, ETHTSYN_CODE) EthTSyn_Init(
  P2CONST(EthTSyn_ConfigType, AUTOMATIC, ETHTSYN_INIT_DATA) CfgPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = ETHTSYN_E_NO_ERROR; /* PRQA S 2981 */ /* MD_MSR_RetVal */

  EthTSyn_ConfigDataPtr = CfgPtr;

  /* ----- Development Error Checks ------------------------------------- */
#if (ETHTSYN_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check plausibility of input parameters. */
  if(CfgPtr == NULL_PTR)
  {
    errorId = ETHTSYN_E_PARAM_POINTER;
  }
  else
#endif /* (ETHTSYN_DEV_ERROR_DETECT == STD_ON) */
  {
    /* ----- Implementation --------------------------------------------- */
    EthTSyn_CtrlIterType ethTSynCtrlIter;
#if (ETHTSYN_TX_SUPPORT == STD_ON)
    EthTSyn_PhysPortIterType physPortIter;
#endif /* (ETHTSYN_TX_SUPPORT == STD_ON) */

    /* #100 Initialize Master sub module. */
#if (ETHTSYN_MASTER_SUPPORT == STD_ON)
# if (ETHTSYN_DEV_ERROR_DETECT == STD_ON)
    errorId = EthTSyn_Master_Init();
# else
    (void)EthTSyn_Master_Init();
# endif /* (ETHTSYN_DEV_ERROR_DETECT == STD_ON) */
#endif /* (ETHTSYN_MASTER_SUPPORT == STD_ON) */

    /* #101 Initialize Slave sub module. */
#if (ETHTSYN_SLAVE_SUPPORT == STD_ON)
    EthTSyn_Slave_Init();
#endif /* (ETHTSYN_SLAVE_SUPPORT == STD_ON) */

    /* #102 Initialize Pdelay sub module. */
    EthTSyn_Pdelay_Init();

    /* #103 Initialize SwtMgmt sub module. */
#if (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON)
    EthTSyn_SwtMgmt_Init();

    /* #1030 Initialize SwtTimeSync sub module. */
# if (ETHTSYN_SWT_TIME_SYNC_SUPPORT == STD_ON)
    EthTSyn_SwtTimeSync_Init();
# endif /* (ETHTSYN_SWT_TIME_SYNC_SUPPORT == STD_ON) */
#endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON) */

#if ( (ETHTSYN_MASTER_TIME_VALIDATION_SUPPORT == STD_ON) || (ETHTSYN_SLAVE_TIME_VALIDATION_SUPPORT == STD_ON) )
    /* #104 Initialize time validation sub module (if TimeValidation feature is enabled). */
    EthTSyn_TimeValid_Init();
#endif /* ( (ETHTSYN_MASTER_TIME_VALIDATION_SUPPORT == STD_ON) || (ETHTSYN_SLAVE_TIME_VALIDATION_SUPPORT == STD_ON) ) */

    /* #105 Initialize all EthTSyn controllers. */
    for(ethTSynCtrlIter = 0u; ethTSynCtrlIter < EthTSyn_GetSizeOfCtrl(); ethTSynCtrlIter++)
    {
      EthTSyn_InitCtrl(ethTSynCtrlIter);
    }

    /* #106 Initialize the debounce timers of all ports if applicable. */
#if (ETHTSYN_TX_SUPPORT == STD_ON)
    for(physPortIter = 0u; physPortIter < EthTSyn_GetSizeOfPhysPort(); physPortIter++)
    {
      EthTSyn_UtilTx_InitDebounceTimer(physPortIter);
    }
#endif /* (ETHTSYN_TX_SUPPORT == STD_ON) */

    /* #107 Set module state to initialized in case no error occurred during initialization. */
#if (ETHTSYN_MASTER_SUPPORT == STD_ON)
# if (ETHTSYN_DEV_ERROR_DETECT == STD_ON)
    if(errorId == ETHTSYN_E_NO_ERROR)
# endif /* (ETHTSYN_DEV_ERROR_DETECT == STD_ON) */
#endif /* (ETHTSYN_MASTER_SUPPORT == STD_ON) */
    {
      EthTSyn_State = ETHTSYN_STATE_INIT;
    }
  }

  /* ----- Development Error Report ------------------------------------- */
#if (ETHTSYN_DEV_ERROR_REPORT == STD_ON)
  /* #20 Report error to default error tracer (DET) if any occurred. */
  if(errorId != ETHTSYN_E_NO_ERROR)
  {
    (void)Det_ReportError(ETHTSYN_MODULE_ID, ETHTSYN_INSTANCE_ID, ETHTSYN_SID_INIT, errorId);
  }
#else
  ETHTSYN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* (ETHTSYN_DEV_ERROR_REPORT == STD_ON) */
} /* EthTSyn_Init() */

/**********************************************************************************************************************
 *  EthTSyn_TrcvLinkStateChg
 *********************************************************************************************************************/
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
 */
/* PRQA S 6050 1 */ /* MD_EthTSyn_6050_CslAccess */
FUNC(void, ETHTSYN_CODE) EthTSyn_TrcvLinkStateChg(
  uint8                 CtrlIdx,
  EthTrcv_LinkStateType TrcvLinkState)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = ETHTSYN_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if (ETHTSYN_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check initialization state of the component. */
  if(EthTSyn_State == ETHTSYN_STATE_UNINIT)
  {
    errorId = ETHTSYN_E_NOT_INITIALIZED;
  }
  else
#endif /* (ETHTSYN_DEV_ERROR_DETECT == STD_ON) */
  {
    /* ----- Implementation --------------------------------------------- */
    /* #20 Get EthTSyn Controller of the passed EthIf Controller. */
    const EthTSyn_IntCtrlIdxType ethTSynCtrlIdx = EthTSyn_Util_GetEthTSynCtrlFromEthIfCtrl(CtrlIdx);

    if(ethTSynCtrlIdx < EthTSyn_GetSizeOfCtrl())
    {
      ETHTSYN_CONSTP2VAR(EthTSyn_CtrlStateType) ctrlStatePtr = EthTSyn_GetAddrCtrlState(ethTSynCtrlIdx);

      /* #30 Check the passed transceiver link state. */
      switch(TrcvLinkState)
      {
        /* #40 Handle transceiver link state down. */
      case ETHTRCV_LINK_STATE_DOWN:
        {
          /* #400 In case transceiver link state changed from active to down. */
          if(ctrlStatePtr->TrcvLinkState == ETHTRCV_LINK_STATE_ACTIVE)
          {
            /* #4000 Store new transceiver link state. */
            ctrlStatePtr->TrcvLinkState = ETHTRCV_LINK_STATE_DOWN;

            /* #4001 Remove multicast frame reception via EthIf_UpdatePhysAddrFilter(). */
            (void)EthIf_UpdatePhysAddrFilter(CtrlIdx, EthTSyn_DestinationMac, ETH_REMOVE_FROM_FILTER);
            /* #4002 Reset Ports and Pdelay values of the controller. */
            EthTSyn_ResetPortsAndPdelayOfCtrl(ethTSynCtrlIdx);
#if (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON)
# if (ETHTSYN_SWT_TIME_SYNC_SUPPORT == STD_ON)
            /* #4003 Disable switch sync frame (if ETHTSYN_SWT_TIME_SYNC_SUPPORT == STD_ON). */
            EthTSyn_SwtTimeSync_SwtSyncFrameStop(CtrlIdx);
# endif /* (ETHTSYN_SWT_TIME_SYNC_SUPPORT == STD_ON) */

            /* #4004 Release all pending switch management objects mapped to the passed EthIf controller
             *      (if ETHTSYN_SWT_MGMT_SUPPORT == STD_ON). */
            EthTSyn_SwtMgmt_ReleasePendingSwtMgmtObj(ethTSynCtrlIdx);
#endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON) */
          }

          break;
        }

        /* #50 Handle transceiver link state up. */
      case ETHTRCV_LINK_STATE_ACTIVE:
        {
          /* #500 In case transceiver link state changed from down to active. */
          if(ctrlStatePtr->TrcvLinkState == ETHTRCV_LINK_STATE_DOWN)
          {
            /* #5000 Store new transceiver link state. */
            ctrlStatePtr->TrcvLinkState = ETHTRCV_LINK_STATE_ACTIVE;

            /* #5001 Initialize EthTSyn controller and the local clock identity. */
            EthTSyn_InitCtrl(ethTSynCtrlIdx);
            EthTSyn_SetLocalClockIdentity(ethTSynCtrlIdx);
            /* #5002 Add multicast frame reception via EthIf_UpdatePhysAddrFilter(). */
            (void)EthIf_UpdatePhysAddrFilter(CtrlIdx, EthTSyn_DestinationMac, ETH_ADD_TO_FILTER);
#if (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON)
# if (ETHTSYN_SWT_TIME_SYNC_SUPPORT == STD_ON)
            /* #5003 Enable switch sync frame. */
            EthTSyn_SwtTimeSync_SwtSyncFrameStart(CtrlIdx);
# endif /* (ETHTSYN_SWT_TIME_SYNC_SUPPORT == STD_ON) */
#endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON) */
          }

          break;
        }

        /* #60 Handle other values of transceiver link state. */
      default:
        {
          /* #600 Invalid value of transceiver link state. Optionally set errorId to ETHTSYN_E_PARAM and do nothing. */
#if (ETHTSYN_DEV_ERROR_REPORT == STD_ON)
          errorId = ETHTSYN_E_PARAM;
#endif /* (ETHTSYN_DEV_ERROR_REPORT == STD_ON) */
          break;
        }
      }
    }
    /* No DET for invalid Ctrl Idx, because EthIf calls TrcvLinkStateChg functions for every registered UpperLayer
       and each configured EthIf controller. */
  }

  /* ----- Development Error Report ------------------------------------- */
#if (ETHTSYN_DEV_ERROR_REPORT == STD_ON)
  /* #70 Report error to default error tracer (DET) if any occurred. */
  if(errorId != ETHTSYN_E_NO_ERROR)
  {
    (void)Det_ReportError(ETHTSYN_MODULE_ID, ETHTSYN_INSTANCE_ID, ETHTSYN_SID_TRCV_LINK_STATE_CHG, errorId);
  }
#else
  ETHTSYN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* (ETHTSYN_DEV_ERROR_REPORT == STD_ON) */
} /* EthTSyn_TrcvLinkStateChg() */

/**********************************************************************************************************************
 *  EthTSyn_TxConfirmation
 *********************************************************************************************************************/
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
 */
/* PRQA S 6050 1 */ /* MD_EthTSyn_6050_CslAccess */
FUNC(void, ETHTSYN_CODE) EthTSyn_TxConfirmation(
  uint8 CtrlIdx,
  uint8 BufIdx)
{
#if (ETHTSYN_TX_SUPPORT == STD_ON)
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = ETHTSYN_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if (ETHTSYN_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check plausibility of input parameters. */
  if(EthTSyn_State == ETHTSYN_STATE_UNINIT)
  {
    errorId = ETHTSYN_E_NOT_INITIALIZED;
  }
  else
# endif /* (ETHTSYN_DEV_ERROR_DETECT == STD_ON) */
  {
    /* ----- Implementation --------------------------------------------- */
    EthTSyn_IntCtrlIdxType ethtsynCtrlIdx;
    EthTSyn_IntPortIdxType portIdx = EthTSyn_GetSizeOfPort();
    uint8 msgType = ETHTSYN_MSG_TYPE_INVALID;
    EthTSyn_IntVltMgmtType egressVltMgmt = {0u, FALSE};
# if (ETHTSYN_SWT_TIME_SYNC_SUPPORT == STD_ON)
    EthTSyn_SwitchSyncFrameCfgIterType swtSyncFrameIdx = EthTSyn_GetSizeOfSwitchSyncFrameCfg();
# endif /* (ETHTSYN_SWT_TIME_SYNC_SUPPORT == STD_ON) */

# if (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_OFF)
    /* For SW-Timestamping the critical section is used to ensure a minimal delay between EthTSyn_TxConfirmation
     * Invocation and collecting the egress timestamp */
    ETHTSYN_ENTER_CRITICAL_SECTION_GET_TS();
# endif /* (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_OFF) */

    /* #20 Get the corresponding EthTSyn controller. */
    ethtsynCtrlIdx = EthTSyn_Util_GetEthTSynCtrlFromEthIfCtrl(CtrlIdx);
    if(ethtsynCtrlIdx < EthTSyn_GetSizeOfCtrl())
    {
      EthTSyn_IntTimeDomainIdxType timeDomainIdx = EthTSyn_GetSizeOfTimeDomain();

      /* #30 Try to find a matching EthTSyn Port and Message type. */
      portIdx = EthTSyn_TxConf_GetTxPortAndMsgType(ethtsynCtrlIdx, BufIdx, &msgType);
      if(portIdx < EthTSyn_GetSizeOfPort())
      {
        /* #300 Mark port and message type as found and get the time domain of the port. */
        timeDomainIdx = EthTSyn_GetTimeDomainIdxOfPort(portIdx);
      }
# if (ETHTSYN_SWT_TIME_SYNC_SUPPORT == STD_ON)
      /* #40 Otherwise, try to find a matching switch sync frame and get the corresponding time domain. */
      else
      {
        swtSyncFrameIdx = EthTSyn_SwtTimeSync_TxConfGetSwtSyncFrameIdx(CtrlIdx, BufIdx);

        if(swtSyncFrameIdx < EthTSyn_GetSizeOfSwitchSyncFrameCfg())
        {
          EthTSyn_SwitchTimeSyncCfgIdxOfSwitchSyncFrameCfgType swtTimeSyncCfgIdx =
            EthTSyn_GetSwitchTimeSyncCfgIdxOfSwitchSyncFrameCfg(swtSyncFrameIdx);
          timeDomainIdx = EthTSyn_GetTimeDomainIdxOfSwitchTimeSyncCfg(swtTimeSyncCfgIdx);
        }
      }
# endif /* (ETHTSYN_SWT_TIME_SYNC_SUPPORT == STD_ON) */

      /* #50 Get the egress timestamp in case a valid time domain was found. */
      if(timeDomainIdx < EthTSyn_GetSizeOfTimeDomain())
      {
        StbM_SynchronizedTimeBaseType timeBaseId = EthTSyn_GetSynchronizedTimeBaseIdOfTimeDomain(timeDomainIdx);
        egressVltMgmt = EthTSyn_TxConf_GetEgressTsAsVlt(CtrlIdx, BufIdx, timeBaseId);
      }
    }
# if (ETHTSYN_DEV_ERROR_REPORT == STD_ON)
    else
    {
      errorId = ETHTSYN_E_CTRL_IDX;
    }
# endif /* (ETHTSYN_DEV_ERROR_REPORT == STD_ON) */

# if (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_OFF)
    /* Leave the critical section after the SW egress timestamp was retrieved and before further processing of the
     * TxConfirmation. */
    ETHTSYN_LEAVE_CRITICAL_SECTION_GET_TS();
# endif /* (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_OFF) */

    /* #60 If a matching port and transmitted message was found. */
    if(portIdx < EthTSyn_GetSizeOfPort())
    {
      /* #600 Assign the egress timestamp. */
      EthTSyn_TxConf_AssignEgressTs(portIdx, msgType, &egressVltMgmt);

      /* #601 Process TxConfirmation. */
      EthTSyn_TxConf_ProcessTxConfirmation(CtrlIdx, BufIdx, portIdx, msgType); /*lint !e522 */
    }
# if (ETHTSYN_SWT_TIME_SYNC_SUPPORT == STD_ON)
    /* #70 If a matching switch sync frame was found. */
    else if (swtSyncFrameIdx < EthTSyn_GetSizeOfSwitchSyncFrameCfg())
    {
      /* #700 Process the switch sync frame TxConfirmation. */
      EthTSyn_SwtTimeSync_SwtSyncFrameTxConfirmation(swtSyncFrameIdx, &egressVltMgmt);
    }
    /* #80 Otherwise. */
    else
    {
      /* #800 No matching transmitted message was found. Discard the TxConfirmation.*/
    }
# endif /* (ETHTSYN_SWT_TIME_SYNC_SUPPORT == STD_ON) */
  }

  /* ----- Development Error Report ------------------------------------- */
# if (ETHTSYN_DEV_ERROR_REPORT == STD_ON)
  /* #90 Report error to default error tracer (DET) if any occurred. */
  if(errorId != ETHTSYN_E_NO_ERROR)
  {
    (void)Det_ReportError(ETHTSYN_MODULE_ID, ETHTSYN_INSTANCE_ID, ETHTSYN_SID_TX_CONFIRMATION, errorId);
  }
# else
  ETHTSYN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
# endif /* (ETHTSYN_DEV_ERROR_REPORT == STD_ON) */
#else
  ETHTSYN_DUMMY_STATEMENT(CtrlIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
  ETHTSYN_DUMMY_STATEMENT(BufIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* (ETHTSYN_TX_SUPPORT == STD_ON) */
} /* EthTSyn_TxConfirmation() */

/**********************************************************************************************************************
 *  EthTSyn_SetTransmissionMode
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, ETHTSYN_CODE) EthTSyn_SetTransmissionMode(
  uint8                        CtrlIdx,
  EthTSyn_TransmissionModeType Mode)
{
  /* ------ Local Variables -----------------------------------------------*/
  uint8 errorId = ETHTSYN_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if (ETHTSYN_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check plausibility of input parameters. */
  if(EthTSyn_State == ETHTSYN_STATE_UNINIT)
  {
    errorId = ETHTSYN_E_NOT_INITIALIZED;
  }
  else if((Mode != ETHTSYN_TX_ON) && (Mode != ETHTSYN_TX_OFF))
  {
    errorId = ETHTSYN_E_PARAM;
  }
  else
#endif /* (ETHTSYN_DEV_ERROR_DETECT == STD_ON) */
  {
    /* ----- Implementation --------------------------------------------- */
    /* #20 Set the transmission mode of the corresponding EthTSyn controller. */
    const EthTSyn_IntCtrlIdxType ethtsynCtrlIdx = EthTSyn_Util_GetEthTSynCtrlFromEthIfCtrl(CtrlIdx);

    if(ethtsynCtrlIdx < EthTSyn_GetSizeOfCtrl())
    {
      (EthTSyn_GetAddrCtrlState(ethtsynCtrlIdx))->TransmissionMode = Mode;
    }
#if (ETHTSYN_DEV_ERROR_REPORT == STD_ON)
    else
    {
      errorId = ETHTSYN_E_CTRL_IDX;
    }
#endif /* (ETHTSYN_DEV_ERROR_REPORT == STD_ON) */
  }

  /* ----- Development Error Report ------------------------------------- */
#if (ETHTSYN_DEV_ERROR_REPORT == STD_ON)
  /* #30 Report error to default error tracer (DET) if any occurred. */
  if(errorId != ETHTSYN_E_NO_ERROR)
  {
    (void)Det_ReportError(ETHTSYN_MODULE_ID, ETHTSYN_INSTANCE_ID, ETHTSYN_SID_SET_TRANSMISSION_MODE, errorId);
  }
#else
  ETHTSYN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif

} /* EthTSyn_SetTransmissionMode() */

#define ETHTSYN_STOP_SEC_CODE
#include "EthTSyn_MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* Justifications for module-specific MISRA deviations:

  MD_EthTSyn_PtrCast_EthBuffer: MISRA rule 11.3 (A cast should not be performed between a pointer to object type and a
                                                  different pointer to object type)
                                MISRA rule 11.8 (A cast shall not be performed that removes any const or volatile
                                                 qualification from the type addressed by a pointer)
                                 QAC: 0310 - Casting to different object pointer type
                                      3305 - Pointer cast to stricter alignment.
                                      0311 - Dangerous pointer cast results in loss of const qualification
      Reason:     An Ethernet Rx/Tx buffer is provided to the EthTSyn as pointer to Eth_DataType. This data type is
                  Platform depended. Therefore for internal processing the EthTSyn uses an uint8 pointer and byte-wise
                  access to avoid mis-aligned access. However EthIf APIs expect a P2VAR with data type Eth_DataType.
                  Therefore when calling an EthIf API the Ethernet Rx/Tx buffer pointer is casted to P2VAR(Eth_DataType)
                  again.
      Risk:       No risk. Pointer was originally provided as pointer to Eth_DataType. In addition the object addressed
                  the pointer parameter is not modified within the called API. The parameter is specified as 'in'
                  parameter by AUTOSAR.
      Prevention: None.
  MD_EthTSyn_0311: MISRA rule 11.8 (A cast shall not be performed that removes any const or volatile qualification
                                    from the type addressed by a pointer)
                   QAC: Dangerous pointer cast results in loss of const qualification
      Reason:     Called API expects a P2VAR.
      Risk:       No risk. The object addressed by the pointer parameter is not modified within the called API.
                  The parameters is specified as 'in' parameter by AUTOSAR.
      Prevention: Covered by code review.
  MD_EthTSyn_3673_Ar: MISRA rule 8.13 (A pointer parameter in a function prototype should be declared as pointer to
                                       const if the pointer is not used to modify the addressed object)
                      QAC: The object addressed by the pointer parameter '%s' is not modified and so the pointer could
                           be of type 'pointer to const'
      Reason:     The parameter is of type P2VAR due to AUTOSAR specification
      Risk:       Unnoticed/unwilling modification of in-parameter.
      Prevention: Covered by code review
  MD_EthTSyn_3415_CslReadOnly: MISRA rule 13.5 (The right hand operand of a logical && or || operator shall not contain
                                                side effects)
                               QAC: The right hand operand of '&&' or '||' has side effects
     Reason:     No side effects possible because the (inline) function only wraps a read-only access to a
                 variable/constant. Used to justify read-only access to constants/variables via inline function
                 generated by the ComStackLib (CSL). (e.g.: EthTSyn_Get*())
     Risk:       Right hand operand does not influence the program/control flow therefor the lazy evaluation applied
                 by the compiler has no effect.
     Prevention: None.
  MD_EthTSyn_3415_ReadOnly: MISRA rule 13.5 (The right hand operand of a logical && or || shall not contain side
                                             effects)
                            QAC: The right hand operand of '&&' or '||' has side effects
      Reason:     No side effect possible because the function does not modify any variable.
                  It is intended that this function is only called if the first check failed (||) / succeeded (&&).
      Risk:       No risk. No assignments are done in conditional statements
      Prevention: Covered by code review.
  MD_EthTSyn_2003: MISRA rule 16.3 (An unconditional break statement shall terminate every non-empty switch clause)
                   QAC: The preceding non-empty 'case' or 'default' clause does not end with an explicit 'break' or
                        'return' statement.
      Reason:    Fall through case to reuse code parts common among different cases.
      Risk:      Right hand operand does not influence the program/control flow therefor the lazy evaluation applied
                 by the compiler has no effect.
     Prevention: None.
  MD_EthTSyn_0883: MISRA rule 1.3: Include file code is not protected against repeated inclusion
      Reason:     Wrong MISRA Warning. Standard Include Guard is present.
      Risk:       No risk.
      Prevention: Covered by code review.
  MD_EthTSyn_3219: MISRA rule 2.1 (There shall be no unreachable code).
                   QAC: Static function '%s()' is not used within this translation unit.
      Reason:     Some internal functions are used within different sub-modules of the EthTSyn. However they might not
                  be used in every sub-module.
      Risk:       Functions which are superfluous in a specific configuration may remain undetected which leads to a
                  small resource overhead.
      Prevention: Covered by code review.
  MD_EthTSyn_2995: MISRA rule 14.3 (Boolean operations whose results are invariant shall not be permitted)
                   QAC: The result of this logical operation is always 'true'.
      Reason:     This logical operation is only 'always true' for specific preprocessor variants.
      Risk:       Possible programming error might not be detected.
      Prevention: Covered by runtime tests in different variants.
  MD_EthTSyn_2996: MISRA rule 14.3 (Boolean operations whose results are invariant shall not be permitted)
                   QAC: The result of this logical operation is always 'false'.
      Reason:     This logical operation is only 'always false' for specific preprocessor variants.
      Risk:       Possible programming error might not be detected.
      Prevention: Covered by runtime tests in different variants.
  MD_EthTSyn_6050_CslAccess: MISRA rule N/A
                             QAC:  Number of distinct function calls defined by HIS shall be in range 0..7
      Reason:     Number of distinct function calls is only too high due to trivial inline functions for accessing the
                  ComStackLib data. Complexity of the function does not increase compared to ComStackLib access via
                  macros.
      Risk:       High complexity of functions.
      Prevention: Design and code review + clearly structured and commented code.
  MD_EthTSyn_6050_IpBase: MISRA rule N/A
                             QAC:  Number of distinct function calls defined by HIS shall be in range 0..7
      Reason:     Number of distinct function calls is only too high due to trivial inline functions for byte-wise
                  read/write access of Ethernet Rx/Tx buffer via IpBase. Complexity of the function does not increase
                  compared to IpBase access via macros or direct buffer access.
      Risk:       High complexity of functions.
      Prevention: Design and code review + clearly structured and commented code.
  MD_EthTSyn_6050_InlineFunc: MISRA rule N/A
                              QAC:  Number of distinct function calls defined by HIS shall be in range 0..7
      Reason:     Number of distinct function calls is only too high due to trivial inline functions for byte-wise
                  read/write access of Ethernet Rx/Tx buffer via IpBase or generated data access
                  (combination of MD_EthTSyn_6050_CslAccess and MD_EthTSyn_6050_IpBase). Complexity of the function
                  does not increase compared to usage of macros or direct access.
      Risk:       High complexity of functions.
      Prevention: Design and code review + clearly structured and commented code.
  MD_EthTSyn_6050_MsgReception: MISRA rule N/A
                                QAC:  Number of distinct function calls defined by HIS shall be in range 0..7
      Reason:     On message reception, the message is forwarded to a corresponding sub-module depending on the
                  message type. Each message type requires an own function. In addition some preparation steps are done
                  in order to unify the message specific reception functions. This leads to more distinct function calls
                  with in the general message reception routine. However, the complexity and readability of this
                  general function is still ensured due to clearly structured and commented code.
      Risk:       High complexity of functions.
      Prevention: Design and code review + clearly structured and commented code.
  MD_EthTSyn_0779_CslAccessName: MISRA rule 1.3 (Identifiers (internal and external) shall not rely on the significance
                                                of more than 31 characters)
                                 QAC: [U] Identifier does not differ from other identifier(s) (e.g. '%s') within the
                                      specified number of significant characters
      Reason:     The identifiers are generated by the ComStackLib based on the names of the underlying data.
      Risk:       A compiler might not correctly pre-process the software what might result in incorrect code.
      Prevention: Each delivery is integrated and tested on the real target system. In addition, preprocessors and
                  compilers used in current MICROSAR projects are not expected to suffer from this (historic)
                  limitation. Compiler selection and validation is done by ECU supplier.
  MD_EthTSyn_1257_Snv: MISRA rule 10.3 (The value of an expression shall not be assigned to an object with a narrower
                                        essential type or of a different essential type category.)
                       QAC: An integer constant suffixed with L or LL is being converted to a type of lower rank on
                            assignment.
      Reason:     Symbolic name value is used in a generated structure as handle. The Snv is generated with 'uL' suffix
                  but the used data type is smaller.
      Risk:       No risk. It is ensured by the ComStackLib that the used data type can hold the SNV.
      Prevention: None.
  MD_EthTSyn_2981_ErrorId: MISRA rule 2.2 (There shall be no dead code)
                           QAC: This initialization is redundant. The value of this object is never used before being
                                modified.
      Reason:     Depending on setting of ETHTSYN_DEV_ERROR_DETECT and ETHTSYN_DEV_ERROR_REPORT the initialization
                  might be redundant.
      Risk:       The redundant initialization code might be confusing.
      Prevention: We stick to our well-known code pattern for all API functions.
  MD_EthTSyn_2981_RedundantInit: MISRA rule 2.2 (There shall be no dead code)
                                 QAC: This initialization is redundant. The value of this object is never used before
                                      being modified.
      Reason:     Modification of the variable might depend on the preprocessor settings. Initialization is always done
                  to increase readability and robustness.
      Risk:       The redundant initialization code might be confusing.
      Prevention: None.
  MD_EthTSyn_2987_GlobalDataInit: MISRA rule 2.2 (There shall be no dead code)
                                  QAC: This function call produces no side effects and is redundant.
      Reason:     Global data is initialized inside the called function by using the ComStackLib. Therefore, the
                  function call is required.
      Risk:       None.
      Prevention: None.
  MD_EthTSyn_3315: MISRA rule 16.6 (Every switch statement shall have at least two switch-clauses)
                   QAC: This 'switch' statement contains only a single path - it is redundant.
      Reason:     The amount of switch-clauses depends on the preprocessor setting. For better readability the
                  switch statement is not removed by preprocessor when all switch-clauses but the default are removed
                  by preprocessor.
      Risk:       The switch statement with a default case only might be confusing.
      Prevention: Well structured code.

*/

/* Safe BSW assumptions:

  Runtime Checking:
    The EthTSyn makes use of the ComStackLib Runtime Checking feature. Due to this feature, the GenData access is
    modeled via a configuration pointer by the ComStackLib. For all subsequent defined countermeasures it is
    essential that the EthTSyn_Init function and the config pointer check were executed. The config pointer passed
    to the EthTSyn_Init is provided by the ComStackLib as well.

  Size Relations:
    EthTSyn_AnnounceReceiveSm <-> EthTSyn_AnnounceInfo
    EthTSyn_CtrlState <-> EthTSyn_Ctrl
    EthTSyn_PdelayInfo <-> EthTSyn_PdelayConfig
    EthTSyn_SyncReceiveSm <-> EthTSyn_SlavePort
    EthTSyn_SyncSendSm <-> EthTSyn_MasterPort
    EthTSyn_PortSyncSendSm <-> EthTSyn_MasterPort
    EthTSyn_SystemState <-> EthTSyn_TimeDomain
    EthTSyn_TimeBaseUpdateCounter <-> EthTSyn_TimeDomain
    EthTSyn_TimeValidMasterData <-> EthTSyn_TimeValidMasterCfg
    EthTSyn_TimeValidSlaveData <-> EthTSyn_TimeValidSlaveCfg
    EthTSyn_TimeValidPdReqData <-> EthTSyn_TimeValidPdReqCfg
    EthTSyn_TimeValidPdRespData <-> EthTSyn_TimeValidPdRespCfg
    EthTSyn_SwtMgmtRxBuf <-> EthTSyn_SwtMgmtRxBufCfg

  Indirections:
    EthTSyn_SwtMgmtRxBufCfg -> 1:N to EthTSyn_SwtMgmtRcvdMsgBuf
    EthTSyn_SwtTimeSyncRateRegulatorCfg -> 1:N EthTSyn_RateMeasurement

  These assumptions are modeled in ComStackLib
*/

/* VCA_JUSTIFICATION_BEGIN

  \ID VCA_ETHTSYN_REF_OF_LOC_VAR_PHYS_ADDR
    \DESCRIPTION      Local array for physical address is passed as pointer argument (or pointer to first element of
                      the array).
    \COUNTERMEASURE   \N Array is created with a length of 6 which is enough to hold the physical address. As it is
                         created locally, memory will always be valid.

  \ID VCA_ETHTSYN_PORT_IND_TABLE_CSL03
    \DESCRIPTION      Port index is retrieved via indirection table generated by ComStackLib.
    \COUNTERMEASURE   \N The indirection is modeled as 1:N unsorted indirection. Therefore, the port index retrieved
                         via the indirection table (EthTSyn_PortInd) is always valid when a valid PortIndIdx is used.
                         Validity of PortIndIdx is ensured. Defaults to qualified use-case CSL03 of ComStackLib.

  \ID VCA_ETHTSYN_PORT_IDX_VALID_NO_ERROR_RETURNED
    \DESCRIPTION      Port index is returned as out-parameter by a function and not checks against
                      EthTSyn_GetSizeOfPort() subsequently by the caller.
    \COUNTERMEASURE   \N Internal function used to retrieve the port index will always provide a valid port index when
                         the return valid is positive (i.e. E_OK or E_NO_ERROR). This belongs to the functions:
                         - EthTSyn_RxInd_PerformBasicMsgChecksAndGetPort()

  \ID VCA_ETHTSYN_TX_BUF_VALID
    \DESCRIPTION      Ethernet Tx-Buffer pointer is used without additional check for NULL_PTR and/or length
                      verification.
    \COUNTERMEASURE   \S The internal function EthTSyn_UtilTx_ProvideTxBuffer() is used to retrieve the Tx-Buffer from
                         the lower layer. In case it returns with E_OK, the Tx-Buffer pointer is always valid
                         (i.e. pointing to a valid Tx-Buffer provided by the lower layer) and at least as big as
                         requested.
                         SMI-233513

  \ID VCA_ETHTSYN_REF_OF_LOC_VAR
    \DESCRIPTION      Pointer to local variable or struct element member is passed as function argument.
    \COUNTERMEASURE   \N [CM_ETHTSYN_LOC_VAR_REF]

  \ID VCA_ETHTSYN_ETHIF_CALLED_WITH_ETH_RX_TX_BUF_AND_LOC_VAR_REF
    \DESCRIPTION      A function with pointer parameters is directly called, but the function is not
                      defined within the analyzed sources. VCA is unable to determine the
                      behavior of the function.
    \COUNTERMEASURE   \N Validity of the pointer(s) is checked by review. The pointer to the Ethernet Rx/Tx buffer
                         is forwarded. In addition, a reference to local variable(s) is passed as pointer.

  \ID VCA_ETHTSYN_INT_FUNC_PTR_PARAM_FWD
    \DESCRIPTION      Forwarding of passed pointer or pointer element.
    \COUNTERMEASURE   \N [CM_ETHTSYN_INT_FUNC_PARAM_PTR_FW] and [CM_ETHTSYN_INT_FUNC_IDX_PARAM]

  \ID VCA_ETHTSYN_OPT_IND_CSL03
    \DESCRIPTION      An optional indirection index is used with former check of the availability via the corresponding
                      EthTSyn_Is*UsedOf*() function. VCA is unable to detect this.
    \COUNTERMEASURE   \N The presence of the optional indirection is ensured by former check using the corresponding
                         EthTSyn_Is*UsedOf*() function provided by ComStackLib. In case of Master/Slave port
                         indirection, it is also valid to check only e.g. for Master and in case it is not used, Slave
                         CSL03 of ComStackLib.

  \ID VCA_ETHTSYN_SWT_MGMT_PORT_OPT_IND_CSL03
    \DESCRIPTION      An optional indirection index is used without direct former check of the availability. VCA is
                      unable to detect the check via internal function.
    \COUNTERMEASURE   \N The function EthTSyn_Util_IsSwitchPort() is used to verify that the EthTSyn Port is a switch
                         port. In this case, the SwitchMgmtPort indirection is present (EthTSyn_Util_IsSwitchPort()
                         breaks done to using the EthTSyn_IsSwitchMgmtPortUsedOfPort() function of CSL).
                         This then defaults to qualified use-case CSL03 of ComStackLib.
                         In case EthTSyn_IsValidForSwtTimeSyncOfMasterPort() returns TRUE, the indirection is present.

  \ID VCA_ETHTSYN_SITE_SYNC_SYNC_SWT_SLAVE_PORT_IDX
    \DESCRIPTION      Slave port index retrieved by EthTSyn_SwtMgmt_GetSwitchSlavePortIdx() is used without additional
                      verification.
    \COUNTERMEASURE   \N For a time domain using the site sync sync state machine,
                      EthTSyn_SwtMgmt_GetSwitchSlavePortIdx() always returns a valid slave port index.

  \ID VCA_ETHTSYN_ETH_SWT_MGMT_OBJ
    \DESCRIPTION      Pointer to the EthSwtMgmtObj is stored in a global EthTSyn internal RxBuf or TxMgmtObj handling
                      structures and is later used while processing the RxBuf/TxMgmtObj.
    \COUNTERMEASURE   \S The EthSwtMgmtObj is retrieved via the corresponding EthIf API. When the API returns E_OK
                         it is assumed that the EthSwtMgmtObj pointer was set to a valid EthSwtMgmtObj. When the
                         EthTSyn internal handling structure is in state PENDING or WAIT_RELEASE, the corresponding
                         EthSwtMgmtObj pointer is always valid and a write operation is allowed when the state of the
                         EthSwtMgmtObj is OWNED_BY_UPPER_LAYER. [SMI-585337]

  \ID VCA_ETHTSYN_SYNC_PORT_ROLE_CHECK_PASSED
    \DESCRIPTION      Slave port index is used without additional check.
    \COUNTERMEASURE   \N When EthTSyn_UtilRx_SyncPortRoleCheckWithMasterSlaveConflictDetection() returns TRUE, the
                      slave port index for the corresponding port is always valid.

  \ID VCA_ETHTSYN_PORT_READY_TO_RCV_SYNC
    \DESCRIPTION      Slave port index is used without additional check.
    \COUNTERMEASURE   \N When EthTSyn_SwtMgmt_Rx_IsPortReadyToRcvSync() returns TRUE, the slave port index for the
                         corresponding port is always valid.

  \ID VCA_ETHTSYN_SWT_MGMT_RX_BUF_VALID_CTRL_IDX
    \DESCRIPTION      EthTSyn controller index stored in the SwtMgmtRxBuf is used without additional verification.
    \COUNTERMEASURE   \N The stored controller index is always valid in case the SwtMgmtRxBuf is in state READY or PROC.

  \ID VCA_ETHTSYN_INT_FUNC_IDX_PARAM
    \DESCRIPTION      Index modeled by (optional) indirection or size relation is used without additional verification.
    \COUNTERMEASURE   \N [CM_ETHTSYN_INT_FUNC_IDX_PARAM]

  \ID VCA_ETHTSYN_ACTIVE_PD_PORT_CSL03
    \DESCRIPTION      Pdelay config index is used without additional check.
    \COUNTERMEASURE   \N When a port is identified as active Pdelay port via EthTSyn_Util_IsActivePdelayPort(), the
                         Pdelay config index is always valid because EthTSyn_Util_IsActivePdelayPort() only returns
                         TRUE when this optional indirection is present. This defaults to qualified use-case CSL03 of
                         the ComStackLib.

  \ID VCA_ETHTSYN_IS_PD_INITIATOR_CSL03
    \DESCRIPTION      Pdelay config index or Pdelay initiator index is used without additional check.
    \COUNTERMEASURE   \N When a port is identified as Pdelay initiator via EthTSyn_Util_IsPdelayInitiator(), both the
                         Pdelay config index and the Pdelay initiator index are valid because
                         EthTSyn_Util_IsPdelayInitiator() only returns TRUE when both optional indirections are
                         present. This defaults to qualified use-case CSL03 of the ComStackLib.

  \ID VCA_ETHTSYN_IS_READY_TO_RCV_PD_RESP_RESP_FUP_CSL03
    \DESCRIPTION      Pdelay config index or Pdelay initiator index is used without additional check.
    \COUNTERMEASURE   \N When a port is identified to be ready to receive a Pdelay_Resp or Pdelay_Resp_Fup via
                         EthTSyn_PdelayRx_IsReadyToReceivePdelayResp() respectively
                         EthTSyn_PdelayRx_IsReadyToReceivePdelayRespFup(), both the
                         Pdelay config index and the Pdelay initiator index are valid because
                         these functions only returns TRUE when both optional indirections are
                         present. This defaults to qualified use-case CSL03 of the ComStackLib.

  \ID VCA_ETHTSYN_IS_PD_RESPONDER_CSL03
    \DESCRIPTION      Pdelay config index or Pdelay responder index is used without additional check.
    \COUNTERMEASURE   \N When a port is identified as Pdelay responder via EthTSyn_Util_IsPdelayResponder(), both the
                         Pdelay config index and the Pdelay responder index are valid because
                         EthTSyn_Util_IsPdelayResponder() only returns TRUE when both optional indirections are
                         present. This defaults to qualified use-case CSL03 of the ComStackLib.

  \ID VCA_ETHTSYN_0_N_IND_CSL03
    \DESCRIPTION      Iteration of 0:N indirection. VCA is unable to detect validity of resulting index.
    \COUNTERMEASURE   \N The iteration index will always be valid when iterating from Start to End index. This
                         is qualified use-case CSL03 of the ComStackLib.

  \ID VCA_ETHTSYN_IS_READY_TO_RCV_ANNOUNCE_CSL03
    \DESCRIPTION      Slave port index of Announce info index is used without additional check.
    \COUNTERMEASURE   \N When a port is identified to be ready to receive a Announce message via
                         EthTSyn_UtilRx_IsPortReadyToReceiveAnnounce(), both the Slave port index and the Announce
                         info index are valid because this function  only returns TRUE when both optional indirections
                         are present. This defaults to qualified use-case CSL03 of the ComStackLib.

  \ID VCA_ETHTSYN_FUP_DATA_ID_LIST_IDX_CSL03
    \DESCRIPTION      Data id list index is calculated and used without additional check.
    \COUNTERMEASURE   \N The FollowUp Data ID List is modeled by 0..N indirection. Before the index is calculated,
                         it is verified that this indirection is present. The index is then calculated by transforming
                         the message SequenceId (SequenceId%listSize) and using the valid start index of the 0..N
                         indirection. This always results in a valid index.

  \ID VCA_ETHTSYN_MEM_CPY_LEN_ASSERTED
    \DESCRIPTION      VStdLib_MemCpy is used to copy data.
    \COUNTERMEASURE   \N The length of the target array is ensured by prior assertion (might be done via function
                         spec as well).

  \ID VCA_ETHTSYN_MEM_CPY_FIX_LEN
    \DESCRIPTION      VStdLib_MemCpy is used to copy data.
    \COUNTERMEASURE   \N The length of the target array is fix (constant macro) and so is the length of the copied
                         data. The target array is always big enough to hold the copied data.

  \ID VCA_ETHTSYN_SWT_MGMT_RX_BUF_MEM_CPY
    \DESCRIPTION      VStdLib_MemCpy is used to copy data to a switch management message buffer.
    \COUNTERMEASURE   \N Upon reception of a message, a free EthTSyn internal switch management buffer is retrieved
                         via EthTSyn_SwtMgmt_Rx_PerformBasicMsgChecksAndGetRxBufIdx. This function only returns a
                         valid buffer index in case the buffer is big enough to hold the received message. An
                         additional verification of the buffer length is therefore not required.

  \ID VCA_ETHTSYN_MEM_CPY_SIZE_OF
    \DESCRIPTION      VStdLib_MemCpy is used to copy a whole structure.
    \COUNTERMEASURE   \N Copy target is a structure and sizeOf is used as copy length. Therefore, the target is always
                         big enough.

VCA_JUSTIFICATION_END */

/*
  \CM CM_ETHTSYN_INT_FUNC_PARAM_PTR_FW It is assumed that pointers passed to internal functions are pointing to valid
                                       memory and are not NULL_PTR (unless otherwise stated in function header).
                                       The validity of the pointer has to be ensured by the caller. This also applies
                                       if the passed pointer is pointing to a struct and a specific struct member is
                                       forwarded as pointer.

  \CM CM_ETHTSYN_LOC_VAR_REF Pointer is generated by referencing a local variable or a struct member of a local variable
                             via the address operator.

  \CM CM_ETHTSYN_INT_FUNC_IDX_PARAM For internal functions it is common that only one index (e.g. PortIdx) is passed as
                                    argument. Depending on the function context and/or another parameter, specific
                                    preconditions have to be fulfilled for this index parameters. The valid range and
                                    the preconditions for the index parameter are described in the function header and
                                    have to be ensured by the caller. The usage of the index parameter then defaults
                                    to a combination of the qualified use-cases CSL01, CSL02 and CSL03 of ComStackLib.
 */

/* COV_JUSTIFICATION_BEGIN

  \ID COV_ETHTSYN_TESTSUITE_INSTRUMENTATION
    \ACCEPT TX
    \REASON This code is only deactivated by test suite for unit testing purpose.

COV_JUSTIFICATION_END */

/**********************************************************************************************************************
 *  END OF FILE: EthTSyn.c
 *********************************************************************************************************************/
