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
/*!        \file  EthTSyn_SwtMgmt_Int.c
 *        \brief  EthTSyn Switch Management source file - Internal Functions
 *      \details  EthTSyn Switch Management source file containing the EthTSyn Switch Management implementation of the
 *                EthTSyn module.
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

#define ETHTSYN_SWTMGMT_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "EthTSyn_SwtMgmt_Int.h"

#if (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON)
# include "EthTSyn_Int.h" /* PRQA S 0883 */ /* MD_EthTSyn_0883 */
# include "EthTSyn_Util_Int.h" /* PRQA S 3219 */ /* MD_EthTSyn_3219 */
# include "EthTSyn_Slave_Int.h" /* PRQA S 3219 */ /* MD_EthTSyn_3219 */
# include "EthTSyn_Master_Int.h"
# include "EthTSyn_Pdelay_Int.h"
# if (ETHTSYN_SWT_TIME_SYNC_SUPPORT == STD_ON)
#  include "EthTSyn_SwtTimeSync_Int.h"
# endif /* (ETHTSYN_SWT_TIME_SYNC_SUPPORT == STD_ON) */
# if ( (ETHTSYN_MASTER_TIME_VALIDATION_SUPPORT == STD_ON) || (ETHTSYN_SLAVE_TIME_VALIDATION_SUPPORT == STD_ON) )
#  include "EthTSyn_TimeValidation_Int.h"
# endif /* ( (ETHTSYN_MASTER_TIME_VALIDATION_SUPPORT == STD_ON) || (ETHTSYN_SLAVE_TIME_VALIDATION_SUPPORT == STD_ON) ) */
# if ( (ETHTSYN_MESSAGE_COMPLIANCE == STD_OFF) && (ETHTSYN_SITESYNCSYNCSM == STD_ON) )
#  include "EthTSyn_Crc_Int.h"
# endif /* ( (ETHTSYN_MESSAGE_COMPLIANCE == STD_OFF) && (ETHTSYN_SITESYNCSYNCSM == STD_ON) ) */

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/
/* Check the version of EthTSyn header file */
# if (  (ETHTSYN_SW_MAJOR_VERSION != (14u)) \
     || (ETHTSYN_SW_MINOR_VERSION != (0u)) \
     || (ETHTSYN_SW_PATCH_VERSION != (0u)) )
#  error "Vendor specific version numbers of EthTSyn_SwtMgmt.c and EthTSyn.h are inconsistent"
# endif

/* Check the version of the configuration header file */
# if (  (ETHTSYN_CFG_MAJOR_VERSION != (14u)) \
     || (ETHTSYN_CFG_MINOR_VERSION != (0u)) )
#  error "Version numbers of EthTSyn_SwtMgmt.c and EthTSyn_Cfg.h are inconsistent!"
# endif

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/
# define ETHTSYN_SWT_MGMT_MS_PER_S                                    (1000u)

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

# define ETHTSYN_START_SEC_CODE
# include "EthTSyn_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  RX
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_Rx_ProcMsgBuffer
 *********************************************************************************************************************/
/*! \brief          Processes a received message.
 *  \details        Checks if all required information for the received message is available and optionally processes
 *                  the message.
 *  \param[in]      RxBufIdx   Index of the Rx-Buffer to be processed
 *                             [range: RxBufIdx < EthTSyn_GetSizeOfSwtMgmtRxBuf()]
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      TRUE for different message buffers
 *  \spec
 *    requires RxBufIdx < EthTSyn_GetSizeOfSwtMgmtRxBuf();
 *  \endspec
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_Rx_ProcMsgBuffer(
  EthTSyn_SwtMgmtRxBufIterType RxBufIdx);

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_Rx_GetPortForMsgBuffer
 *********************************************************************************************************************/
/*! \brief      Retrieves the EthTSyn Port which matches the information of the buffered message.
 *  \details    -
 *  \param[in]  RxBufIdx   Index of the Rx-Buffer to be processed
 *                         [range: RxBufIdx < EthTSyn_GetSizeOfSwtMgmtRxBuf()]
 *  \return     EthTSyn_GetSizeOfPort() - no matching port was found
 *  \return     other values - the matching EthTSyn Port index
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *  \spec
 *    requires RxBufIdx < EthTSyn_GetSizeOfSwtMgmtRxBuf();
 *  \endspec
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_IntPortIdxType, ETHTSYN_CODE) EthTSyn_SwtMgmt_Rx_GetPortForMsgBuffer(
  EthTSyn_SwtMgmtRxBufIterType RxBufIdx);

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_Rx_ProcRcvdMsg
 *********************************************************************************************************************/
/*! \brief      Handles the processing of a received message (switch management).
 *  \details    -
 *  \param[in]  PortIdx    Index of the port the message was received on
 *                         [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \param[in]  RxBufIdx   Index of the Rx-Buffer to be processed
 *                         [range: RxBufIdx < EthTSyn_GetSizeOfSwtMgmtRxBuf()]
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different MsgBuffers
 *  \spec
 *    requires PortIdx < EthTSyn_GetSizeOfPort();
 *    requires RxBufIdx < EthTSyn_GetSizeOfSwtMgmtRxBuf();
 *  \endspec
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_Rx_ProcRcvdMsg(
  EthTSyn_IntPortIdxType       PortIdx,
  EthTSyn_SwtMgmtRxBufIterType RxBufIdx);

# if (ETHTSYN_SLAVE_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_Rx_FwdSyncMsgToEndStation
 *********************************************************************************************************************/
/*! \brief      Handles the forwarding of a received Sync message to the End-Station implementation.
 *  \details    -
 *  \param[in]  TimeDomainIdx   Index of the time domain the message was received on
 *                              [range: TimeDomainIdx < EthTSyn_GetSizeOfTimeDomain()]
 *  \param[in]  RxBufIdx        Index of the Rx-Buffer to be processed
 *                              [range: RxBufIdx < EthTSyn_GetSizeOfSwtMgmtRxBuf()]
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different TimeDomain indices
 *  \spec
 *    requires TimeDomainIdx < EthTSyn_GetSizeOfTimeDomain();
 *    requires RxBufIdx < EthTSyn_GetSizeOfSwtMgmtRxBuf();
 *  \endspec
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_Rx_FwdSyncMsgToEndStation(
  EthTSyn_IntTimeDomainIdxType TimeDomainIdx,
  EthTSyn_SwtMgmtRxBufIterType RxBufIdx);
# endif /* (ETHTSYN_SLAVE_SUPPORT == STD_ON) */

# if (ETHTSYN_SLAVE_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_Rx_GetSyncIngrTsAndSwtResTime
 *********************************************************************************************************************/
/*! \brief      Gets the Sync ingress timestamp and switch residence time
 *  \details    If switch and host are one time aware system, the switch ingress timestamp is considered as Sync
 *              ingress timestamp and the residence time is set to zero.
 *              Otherwise, the host ingress timestamp is considered as Sync ingress timestamp.
 *              If switch timestamping is available, the switch residence time is calculated.
 *              Otherwise, it is set to zero.
 *  \param[in]  RxBufIdx             Index of the Rx-Buffer to be processed
 *                                   [range: RxBufIdx < EthTSyn_GetSizeOfSwtMgmtRxBuf()]
 *  \param[out] IngressTsVltMgmtPtr  Virtual local time management object for the ingress timestamp
 *  \param[out] SwtResidenceTimePtr  Residence time
 *  \return     E_OK     - Writing to the timeRx frame object was successful.
 *  \return     E_NOT_OK - Writing to the timeRx frame object was not successful.
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different TimeDomain indices
 *  \spec
 *    requires RxBufIdx < EthTSyn_GetSizeOfSwtMgmtRxBuf();
 *  \endspec
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_SwtMgmt_Rx_GetSyncIngrTsAndSwtResTime(
                EthTSyn_SwtMgmtRxBufIterType  RxBufIdx,
  ETHTSYN_P2VAR(EthTSyn_IntVltMgmtType)       IngressTsVltMgmtPtr,
  ETHTSYN_P2VAR(EthTSyn_TimediffType)         SwtResidenceTimePtr);
# endif /* (ETHTSYN_SLAVE_SUPPORT == STD_ON) */

# if (ETHTSYN_SLAVE_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_Rx_FwdFupMsgToEndStation
 *********************************************************************************************************************/
/*! \brief          Handles the forwarding of a received FollowUp message to the End-Station implementation.
 *  \details        -
 *  \param[in]      TimeDomainIdx   Index of the time domain the message was received on
 *                                  [range: TimeDomainIdx < EthTSyn_GetSizeOfTimeDomain()]
 *  \param[in]      RxBufIdx        Index of the Rx-Buffer to be processed
 *                                  [range: RxBufIdx < EthTSyn_GetSizeOfSwtMgmtRxBuf()]
 *  \pre            -
 *  \context        TAKS|ISR2
 *  \reentrant      TRUE for different Port indices
 *  \spec
 *    requires TimeDomainIdx < EthTSyn_GetSizeOfTimeDomain();
 *    requires RxBufIdx < EthTSyn_GetSizeOfSwtMgmtRxBuf();
 *  \endspec
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_Rx_FwdFupMsgToEndStation(
  EthTSyn_IntTimeDomainIdxType TimeDomainIdx,
  EthTSyn_SwtMgmtRxBufIterType RxBufIdx);
# endif /* (ETHTSYN_SLAVE_SUPPORT == STD_ON) */

# if (ETHTSYN_PDELAY_RESPONDER_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_Rx_ProcRcvdPdReqMsg
 *********************************************************************************************************************/
/*! \brief      Processes a received Pdelay_Req message.
 *  \details    Checks if passed Port is ready to receive a Pdelay_Req message and optionally processes the message.
 *  \param[in]  PortIdx    Index of the EthTSyn Port the message was received on
 *                         [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \param[in]  RxBufIdx   Index of the Rx-Buffer to be processed
 *                         [range: RxBufIdx < EthTSyn_GetSizeOfSwtMgmtRxBuf()]
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different Port indices
 *  \spec
 *    requires PortIdx < EthTSyn_GetSizeOfPort();
 *    requires RxBufIdx < EthTSyn_GetSizeOfSwtMgmtRxBuf();
 *  \endspec
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_Rx_ProcRcvdPdReqMsg(
  EthTSyn_IntPortIdxType       PortIdx,
  EthTSyn_SwtMgmtRxBufIterType RxBufIdx);
# endif /* (ETHTSYN_PDELAY_RESPONDER_SUPPORT == STD_ON) */

# if (ETHTSYN_PDELAY_INITIATOR_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_Rx_ProcRcvdPdRespMsg
 *********************************************************************************************************************/
/*! \brief      Processes a received Pdelay_Resp message.
 *  \details    Checks if passed Port is ready to receive a Pdelay_Resp message and optionally processes the message.
 *  \param[in]  PortIdx    Index of the EthTSyn Port the message was received on
 *                         [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \param[in]  RxBufIdx   Index of the Rx-Buffer to be processed
 *                         [range: RxBufIdx < EthTSyn_GetSizeOfSwtMgmtRxBuf()]
 *  \pre        -
 *  \context    TAKS|ISR2
 *  \reentrant  TRUE for different Port indices
 *  \spec
 *    requires PortIdx < EthTSyn_GetSizeOfPort();
 *    requires RxBufIdx < EthTSyn_GetSizeOfSwtMgmtRxBuf();
 *  \endspec
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_Rx_ProcRcvdPdRespMsg(
  EthTSyn_IntPortIdxType       PortIdx,
  EthTSyn_SwtMgmtRxBufIterType RxBufIdx);

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_Rx_ProcRcvdPdRespFupMsg
 *********************************************************************************************************************/
/*! \brief      Processing of a received Pdelay_Resp_FollowUp message.
 *  \details    Checks if passed Port is ready to receive a Pdelay_Resp_FollowUp message and optionally processes the
 *              message.
 *  \param[in]  PortIdx    Index of the EthTSyn Port the message was received on
 *                         [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \param[in]  RxBufIdx   Index of the Rx-Buffer to be processed
 *                         [range: RxBufIdx < EthTSyn_GetSizeOfSwtMgmtRxBuf()]
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different Port indices
 *  \spec
 *    requires PortIdx < EthTSyn_GetSizeOfPort();
 *    requires RxBufIdx < EthTSyn_GetSizeOfSwtMgmtRxBuf();
 *  \endspec
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_Rx_ProcRcvdPdRespFupMsg(
  EthTSyn_IntPortIdxType       PortIdx,
  EthTSyn_SwtMgmtRxBufIterType RxBufIdx);
# endif /* (ETHTSYN_PDELAY_INITIATOR_SUPPORT == STD_ON) */

# if (ETHTSYN_SLAVE_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_Rx_ProcRcvdSyncMsg
 **********************************************************************************************************************/
/*! \brief      Processing of a received Sync message.
 *  \details    Checks if passed Port is ready to receive a Sync message and optionally processes the message.
 *  \param[in]  PortIdx   Index of the EthTSyn Port the message was received on
 *                        [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \param[in]  RxBufIdx  Index of the Rx-Buffer to be processed
 *                        [range: RxBufIdx < EthTSyn_GetSizeOfSwtMgmtRxBuf()]
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different Port indices
 *  \spec
 *    requires PortIdx < EthTSyn_GetSizeOfPort();
 *    requires RxBufIdx < EthTSyn_GetSizeOfSwtMgmtRxBuf();
 *  \endspec
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_Rx_ProcRcvdSyncMsg(
  EthTSyn_IntPortIdxType       PortIdx,
  EthTSyn_SwtMgmtRxBufIterType RxBufIdx);
# endif /* (ETHTSYN_SLAVE_SUPPORT == STD_ON) */

# if (ETHTSYN_SLAVE_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_Rx_IsPortReadyToRcvSync
 **********************************************************************************************************************/
/*! \brief      Checks if the given port is ready to receive a sync message.
 *  \details    Checks the PortRole, AsCapableState, SyncReceiveSm state and source port identity.
 *              In addition the Master-Slave-Conflict Detection is handled.
 *  \param[in]  PortIdx            Index of the EthTSyn Port the message was received on
 *                                 [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \param[in]  SrcClockIdentity   The source clock identity of the received Sync message
 *  \return     TRUE - Port is ready to receive sync message
 *  \return     FALSE - Port is not ready to receive sync message
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different Port indices
 *  \spec
 *    requires PortIdx < EthTSyn_GetSizeOfPort();
 *  \endspec
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_SwtMgmt_Rx_IsPortReadyToRcvSync(
  EthTSyn_IntPortIdxType  PortIdx,
  uint64                  SrcClockIdentity);
# endif /* (ETHTSYN_SLAVE_SUPPORT == STD_ON) */

# if (ETHTSYN_SLAVE_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_Rx_ProcRcvdFupMsg
 *********************************************************************************************************************/
/*! \brief      Processing of a received FollowUp message.
 *  \details    Checks if passed Port is ready to receive a FollowUp message and optionally processes the message.
 *              Processing the message includes forwarding the message to the End-Station if applicable.
 *  \param[in]  PortIdx    Index of the EthTSyn Port the message was received on
 *                         [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \param[in]  RxBufIdx   Index of the Rx-Buffer to be processed
 *                         [range: RxBufIdx < EthTSyn_GetSizeOfSwtMgmtRxBuf()]
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different Port indices
 *  \spec
 *    requires PortIdx < EthTSyn_GetSizeOfPort();
 *    requires RxBufIdx < EthTSyn_GetSizeOfSwtMgmtRxBuf();
 *  \endspec
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_Rx_ProcRcvdFupMsg(
  EthTSyn_IntPortIdxType       PortIdx,
  EthTSyn_SwtMgmtRxBufIterType RxBufIdx);
# endif /* (ETHTSYN_SLAVE_SUPPORT == STD_ON) */

# if (ETHTSYN_ANNOUNCE_RX_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_Rx_ProcRcvdAnnounceMsg
 *********************************************************************************************************************/
/*! \brief      Processing of a received Announce message.
 *  \details    Checks if passed Port is ready to receive an Announce message and optionally processes the message.
 *  \param[in]  PortIdx    Index of the EthTSyn Port the message was received on
 *                         [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \param[in]  RxBufIdx   Index of the Rx-Buffer to be processed
 *                         [range: RxBufIdx < EthTSyn_GetSizeOfSwtMgmtRxBuf()]
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different Port indices
 *  \spec
 *    requires PortIdx < EthTSyn_GetSizeOfPort();
 *    requires RxBufIdx < EthTSyn_GetSizeOfSwtMgmtRxBuf();
 *  \endspec
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_Rx_ProcRcvdAnnounceMsg(
  EthTSyn_IntPortIdxType       PortIdx,
  EthTSyn_SwtMgmtRxBufIterType RxBufIdx);
# endif /* (ETHTSYN_ANNOUNCE_RX_SUPPORT == STD_ON) */

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_Rx_PerformBasicMsgChecksAndGetRxBufIdx
 *********************************************************************************************************************/
/*! \brief       Performs basic message checks and gets a free Rx buffer.
 *  \details     Checks basic message information (e.g. ProtocolVersion), gets and locks a free Rx buffer.
 *               If any of the performed message checks fails, no Rx buffer is locked.
 *  \param[in]   LenByte     The received message length passed to EthTSyn_RxIndication() from EthIf
 *  \param[in]   DataPtr     Pointer to the Rx-Buffer passed to the EthTSyn_RxIndication from EthIf
 *  \param[out]  ErrorIdPtr  The corresponding error id in case any message check failed or no free buffer is available
 *  \return      EthTSyn_GetSizeOfSwtMgmtRxBuf - Message checks failed or no free message buffer available.
 *  \return      other values - Index of the next free Rx message buffer
 *  \pre         -
 *  \context     TASK|ISR2
 *  \reentrant   TRUE
 *  \note        The RxBufIdx returned via the corresponding out-parameter is always valid
 *               (< EthTSyn_GetSizeOfSwtMgmtRxBuf()) when ETHTSYN_E_NO_ERROR is returned.
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(uint8, ETHTSYN_CODE) EthTSyn_SwtMgmt_Rx_PerformBasicMsgChecksAndGetRxBufIdx(
                  uint16 LenByte,
  ETHTSYN_P2CONST(uint8) DataPtr,
    ETHTSYN_P2VAR(uint8) ErrorIdPtr);

# if (ETHTSYN_SLAVE_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_GetEndStationSlavePortIdx
 *********************************************************************************************************************/
/*! \brief      Get the End-Station Slave-Port Index of the passed TimeDomain.
 *  \details    -
 *  \param[in]  TimeDomainIdx   Index of the TimeDomain the slave port should be retrieved for
 *                              [range: TimeDomainIdx < EthTSyn_GetSizeOfTimeDomain()]
 *  \return     EthTSyn_GetSizeOfPort() - no End-Station Slave-Port found
 *  \return     other values - the corresponding port index of the End-Station Slave-Port. The value is always
 *                             < EthTSyn_GetSizeOfPort() and EthTSyn_IsSlavePortUsedOfPort() is always TRUE
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *  \spec
 *    requires TimeDomainIdx < EthTSyn_GetSizeOfTimeDomain();
 *  \endspec
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_IntPortIdxType, ETHTSYN_CODE) EthTSyn_SwtMgmt_GetEndStationSlavePortIdx(
  EthTSyn_IntTimeDomainIdxType TimeDomainIdx);

#  if (ETHTSYN_SWT_MGMT_BRIDGE_MODE == ETHTSYN_SWT_MGMT_BRIDGE_MODE_TRANSPARENT)
/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_GetSwitchSlavePortIdx
 *********************************************************************************************************************/
/*! \brief      Get the Switch Slave-Port Index of the given TimeDomain.
 *  \details    -
 *  \param[in]  TimeDomainIdx   Index of the TimeDomain the slave port should be retrieved for
 *                              [range: TimeDomainIdx < EthTSyn_GetSizeOfTimeDomain()]
 *  \return     EthTSyn_GetSizeOfSlavePort() - no Switch Slave-Port found
 *  \return     other values - the corresponding port index of the Switch Slave-Port
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *  \spec
 *    requires TimeDomainIdx < EthTSyn_GetSizeOfTimeDomain();
 *  \endspec
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_IntSlavePortIdxType, ETHTSYN_CODE) EthTSyn_SwtMgmt_GetSwitchSlavePortIdx(
  EthTSyn_TimeDomainIterType TimeDomainIdx);
#  endif /* (ETHTSYN_SWT_MGMT_BRIDGE_MODE == ETHTSYN_SWT_MGMT_BRIDGE_MODE_TRANSPARENT) */
# endif /* (ETHTSYN_SLAVE_SUPPORT == STD_ON) */

/**********************************************************************************************************************
 *  SITE SYNC SYNC STATE MACHINE
 *********************************************************************************************************************/
# if (ETHTSYN_SITESYNCSYNCSM == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_SiteSyncSync_ChgStateToTxSync
 *********************************************************************************************************************/
/*! \brief      Changes the state of the SiteSyncSyncSm to TX_SYNC.
 *  \details    -
 *  \param[in]  TimeDomainIdx   Index of the TimeDomain
 *                              [range: TimeDomainIdx < EthTSyn_GetSizeOfTimeDomain()]
 *  \pre        EthTSyn_IsSiteSyncSyncSmUsedOfTimeDomain(TimeDomainIdx) == TRUE
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different TimeDomain indices
 *  \spec
 *    requires TimeDomainIdx < EthTSyn_GetSizeOfTimeDomain();
 *  \endspec
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_SiteSyncSync_ChgStateToTxSync(
  EthTSyn_TimeDomainIterType TimeDomainIdx);

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_SiteSyncSync_HndlPendingState
 *********************************************************************************************************************/
/*! \brief      Handles the state ETHTSYN_S_SSS_SM_PENDING of the SiteSyncSync state machine.
 *  \details    -
 *  \param[in]  TimeDomainIdx   Index of the TimeDomain the SiteSyncSync state machine is processed for
 *                              [range: TimeDomainIdx < EthTSyn_GetSizeOfTimeDomain()]
 *  \pre        Should be called in the context of EthTSyn_SwtMgmt_SiteSyncSync_ProcSm() only
 *  \pre        EthTSyn_IsSiteSyncSyncSmUsedOfTimeDomain(TimeDomainIdx) == TRUE
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different TimeDomain indices
 *  \spec
 *    requires TimeDomainIdx < EthTSyn_GetSizeOfTimeDomain();
 *  \endspec
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_SiteSyncSync_HndlPendingState(
  EthTSyn_TimeDomainIterType TimeDomainIdx);

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_SiteSyncSync_HndlTxSyncState
 *********************************************************************************************************************/
/*! \brief      Handles the state ETHTSYN_S_SSS_SM_TX_SYNC of the SiteSyncSync state machine.
 *  \details    -
 *  \param[in]  TimeDomainIdx   Index of the TimeDomain the SiteSyncSync state machine is processed for
 *                              [range: TimeDomainIdx < EthTSyn_GetSizeOfTimeDomain()]
 *  \pre        Should be called in the context of EthTSyn_SwtMgmt_SiteSyncSync_ProcSm() only
 *  \pre        EthTSyn_IsSiteSyncSyncSmUsedOfTimeDomain(TimeDomainIdx) == TRUE
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different TimeDomain indices
 *  \spec
 *    requires TimeDomainIdx < EthTSyn_GetSizeOfTimeDomain();
 *  \endspec
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_SiteSyncSync_HndlTxSyncState(
  EthTSyn_TimeDomainIterType TimeDomainIdx);

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_SiteSyncSync_HndlSyncRetry
 *********************************************************************************************************************/
/*! \brief      Handles the Sync transmission retry mechanism.
 *  \details    -
 *  \param[in]  TimeDomainIdx   Index of the TimeDomain
 *                              [range: TimeDomainIdx < EthTSyn_GetSizeOfTimeDomain()]
 *  \pre        Should be called in the context of EthTSyn_SwtMgmt_SiteSyncSync_ProcSm() only
 *  \pre        EthTSyn_IsSiteSyncSyncSmUsedOfTimeDomain(TimeDomainIdx) == TRUE
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different TimeDomain indices
 *  \spec
 *    requires TimeDomainIdx < EthTSyn_GetSizeOfTimeDomain();
 *  \endspec
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_SiteSyncSync_HndlSyncRetry(
  EthTSyn_TimeDomainIterType TimeDomainIdx);

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_SiteSyncSync_HndlTxFupState
 *********************************************************************************************************************/
/*! \brief      Handles the state ETHTSYN_S_SSS_SM_TX_FUP of the SiteSyncSync state machine.
 *  \details    -
 *  \param[in]  TimeDomainIdx   Index of the TimeDomain the SiteSyncSync state machine is processed for
 *                              [range: TimeDomainIdx < EthTSyn_GetSizeOfTimeDomain()]
 *  \pre        Should be called in the context of EthTSyn_SwtMgmt_SiteSyncSync_ProcSm() only
 *  \pre        EthTSyn_IsSiteSyncSyncSmUsedOfTimeDomain(TimeDomainIdx) == TRUE
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different TimeDomain indices
 *  \spec
 *    requires TimeDomainIdx < EthTSyn_GetSizeOfTimeDomain();
 *  \endspec
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_SiteSyncSync_HndlTxFupState(
  EthTSyn_TimeDomainIterType TimeDomainIdx);

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_SiteSyncSync_HndlFupRetry
 *********************************************************************************************************************/
/*! \brief      Handles the FollowUp transmission retry mechanism.
 *  \details    -
 *  \param[in]  TimeDomainIdx   Index of the TimeDomain
 *                              [range: TimeDomainIdx < EthTSyn_GetSizeOfTimeDomain()]
 *  \pre        Should be called in the context of EthTSyn_SwtMgmt_SiteSyncSync_ProcSm() only
 *  \pre        EthTSyn_IsSiteSyncSyncSmUsedOfTimeDomain(TimeDomainIdx) == TRUE
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different TimeDomain indices
 *  \spec
 *    requires TimeDomainIdx < EthTSyn_GetSizeOfTimeDomain();
 *  \endspec
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_SiteSyncSync_HndlFupRetry(
  EthTSyn_TimeDomainIterType TimeDomainIdx);

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_SiteSyncSync_HndlRcvdFupAfterTimeoutState
 *********************************************************************************************************************/
/*! \brief      Handles the state ETHTSYN_S_SSS_SM_RCVD_FUP_AFTER_TIMEOUT of the SiteSyncSync state machine.
 *  \details    -
 *  \param[in]  TimeDomainIdx      Index of the TimeDomain the SiteSyncSync state machine is processed for
 *                                 [range: TimeDomainIdx < EthTSyn_GetSizeOfTimeDomain()]
 *  \pre        EthTSyn_IsSiteSyncSyncSmUsedOfTimeDomain(TimeDomainIdx) == TRUE
 *  \context    TAKS|ISR2
 *  \reentrant  TRUE for different TimeDomain indices
 *  \spec
 *    requires TimeDomainIdx < EthTSyn_GetSizeOfTimeDomain();
 *  \endspec
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_SiteSyncSync_HndlRcvdFupAfterTimeoutState(
  EthTSyn_TimeDomainIterType TimeDomainIdx);

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_SiteSyncSync_GetSyncCycleFromSyncMsg
 *********************************************************************************************************************/
/*! \brief      Calculates the sync message cycle (in EthTSyn main function cycles) from the passed sync message
 *  \details    -
 *  \param[in]  SyncMsgPtr  The sync message
 *  \return     The sync message cycle expressed in EthTSyn main function cycles
 *  \pre        -
 *  \context    TAKS|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(uint32, ETHTSYN_CODE) EthTSyn_SwtMgmt_SiteSyncSync_GetSyncCycleFromSyncMsg(
  ETHTSYN_P2CONST(uint8) SyncMsgPtr);

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_SiteSyncSync_RcvdSync
 **********************************************************************************************************************/
/*! \brief      Triggers a sync receive event against the SiteSyncSyncSm.
 *  \details    -
 *  \param[in]  PortIdx    Index of the EthTSyn Port the message was received on
 *                         [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \param[in]  RxBufIdx   Index of the Rx-Buffer to be processed
 *                         [range: RxBufIdx < EthTSyn_GetSizeOfSwtMgmtRxBuf()]
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different Port indices
 *  \spec
 *    requires PortIdx < EthTSyn_GetSizeOfPort();
 *    requires RxBufIdx < EthTSyn_GetSizeOfSwtMgmtRxBuf();
 *  \endspec
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_SiteSyncSync_RcvdSync(
  EthTSyn_IntPortIdxType       PortIdx,
  EthTSyn_SwtMgmtRxBufIterType RxBufIdx);

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_SiteSyncSync_RcvdFup
 **********************************************************************************************************************/
/*! \brief      Triggers a follow up receive event against the SiteSyncSyncSm.
 *  \details    -
 *  \param[in]  PortIdx    Index of the EthTSyn Port the message was received on
 *                         [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \param[in]  RxBufIdx   Index of the Rx-Buffer to be processed
 *                         [range: RxBufIdx < EthTSyn_GetSizeOfSwtMgmtRxBuf()]
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different Port indices
 *  \spec
 *    requires PortIdx < EthTSyn_GetSizeOfPort();
 *    requires RxBufIdx < EthTSyn_GetSizeOfSwtMgmtRxBuf();
 *  \endspec
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_SiteSyncSync_RcvdFup(
  EthTSyn_IntPortIdxType       PortIdx,
  EthTSyn_SwtMgmtRxBufIterType RxBufIdx);

# if (ETHTSYN_MESSAGE_COMPLIANCE == STD_OFF)
/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_SiteSyncSync_SetFupTimeSecuredTlvInfo
 **********************************************************************************************************************/
/*! \brief      Writes the FollowUp time secured TLV info to the SiteSyncSyncSm.
 *  \details    Checks if a time secured TLV is included in a received FollowUp. If so, the CRC is validated and the
 *              time secured TLV information is stored in the SiteSyncSyncSm.
 *  \param[in]  PortIdx         Index of the EthTSyn Port the FollowUp message was received on
 *                              [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \param[in]  RcvdFupMsgPtr   Pointer to the received FollowUp message
 *  \pre        The port identified by PortIdx has to belong to a time domain which uses the SiteSyncSyncSm (i.e.
 *              EthTSyn_IsSiteSyncSyncSmUsedOfTimeDomain(EthTSyn_GetTimeDomainIdxOfPort(PortIdx)) == TRUE)
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different Port indices
 *  \spec
 *    requires PortIdx < EthTSyn_GetSizeOfPort();
 *  \endspec
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_SiteSyncSync_SetFupTimeSecuredTlvInfo(
                  EthTSyn_IntPortIdxType PortIdx,
  ETHTSYN_P2CONST(uint8)                 RcvdFupMsgPtr);
# endif /* (ETHTSYN_MESSAGE_COMPLIANCE == STD_OFF) */

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_SiteSyncSync_TxFupMsg
 *********************************************************************************************************************/
/*! \brief      Triggers transmission of a FollowUp message on the provided master port.
 *  \details    -
 *  \param[in]  MasterPortIdx   Index of the master port
 *                              [range: MasterPortIdx < EthTSyn_GetSizeOfMasterPort()]
 *  \param[in]  FupMsgLen       Length of the FollowUp message in byte
 *  \return     E_OK - Successfully triggered FollowUp message transmission
 *  \return     E_NOT_OK - Failed to trigger FollowUp message transmission
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different master ports
 *  \spec
 *    requires MasterPortIdx < EthTSyn_GetSizeOfMasterPort();
 *  \endspec
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_SwtMgmt_SiteSyncSync_TxFupMsg(
  EthTSyn_MasterPortIterType MasterPortIdx,
  uint16                     FupMsgLen);

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_SiteSyncSync_CalcAndSetFupCorrField
 *********************************************************************************************************************/
/*! \brief      Calculates the FollowUp correction field value and sets it in the corresponding FollowUp message.
 *  \details    Computes the Switch/Software residence time of the corresponding sync message and adds it to the
 *              correction field of the FollowUp message. Adds the Pdelay of the Slave-Port as well.
 *  \param[in]  PortIdx     Index of the Port the FollowUp message should be transmitted on
 *                          [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \param[in]  TxBufPtr    Pointer to the Ethernet transmission buffer of the FollowUp message
 *  \pre        The FollowUp message (at least the old correction field) was already copied to the TxBuffer
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *  \spec
 *    requires PortIdx < EthTSyn_GetSizeOfPort();
 *  \endspec
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_SiteSyncSync_CalcAndSetFupCorrField(
                EthTSyn_PortIdxOfMasterPortType  PortIdx,
  ETHTSYN_P2VAR(uint8)                           TxBufPtr);

#  if (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_OFF)
/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_SiteSyncSync_CalcSyncSwResTime
 *********************************************************************************************************************/
/*! \brief          Calculates the software residence time of a forwarded sync message.
 *  \details        -
 *  \param[in]      PortIdx        Index of the EthTSyn port
 *                  [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \return         The calculated SW residence time
 *  \pre            Constraints for PortIdx:
 *                    - EthTSyn_IsMasterPortUsedOfPort() == TRUE
 *                    - EthTSyn_IsSiteSyncSyncSmUsedOfTimeDomain() == TRUE
 *  \context        TASK|ISR2
 *  \reentrant      TRUE for different PortIdx
 *  \spec
 *    requires PortIdx < EthTSyn_GetSizeOfPort();
 *  \endspec
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_TimediffType, ETHTSYN_CODE) EthTSyn_SwtMgmt_SiteSyncSync_CalcSyncSwResTime(
  EthTSyn_IntPortIdxType  PortIdx);
#  endif /* (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_OFF) */

#  if (ETHTSYN_MESSAGE_COMPLIANCE == STD_OFF)
/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_SiteSyncSync_UpdateTimeSecuredSubTlvCrc
 *********************************************************************************************************************/
/*! \brief          Updates the CRC of the TimeSecured Ar Sub-TLV of a transmitted/forwarded FollowUp message.
 *  \details        -
 *  \param[in]      PortIdx       Index of the EthTSyn port
 *                  [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \param[in]      FupTxBufPtr   Pointer to the Ethernet transmission buffer of the FollowUp message
 *  \pre            FollowUp message including all Ar Sub-TLVs is already copied to the passed TxBuffer
 *  \pre            The port identified by PortIdx has to be part of a time domain using the SiteSyncSyncSm
 *  \context        TASK|ISR2
 *  \reentrant      TRUE for different PortIdx
 *  \spec
 *    requires PortIdx < EthTSyn_GetSizeOfPort();
 *  \endspec
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_SiteSyncSync_UpdateTimeSecuredSubTlvCrc(
                EthTSyn_PortIdxOfMasterPortType PortIdx,
  ETHTSYN_P2VAR(uint8)                          FupTxBufPtr);

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_SiteSyncSync_GetTimeSecuredSubTlvStartIdx
 *********************************************************************************************************************/
/*! \brief          Gets the start index of the TimeSecured Ar Sub-TLV of a FollowUp message within its buffer.
 *  \details        -
 *  \param[in]      FupMsgPtr     Pointer to the buffer of the FollowUp message
 *  \param[in]      LenByte       Length of the FollowUp message in byte
 *  \return         LenByte - No TimeSecured Sub-TLV found in the FollowUp message
 *  \return         other values - Start index of the TimeSecured Sub-TLV within the FupBuffer
 *  \pre            FollowUp message including all Ar Sub-TLVs is already copied to the passed buffer
 *  \context        TASK|ISR2
 *  \reentrant      TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(uint16, ETHTSYN_CODE) EthTSyn_SwtMgmt_SiteSyncSync_GetTimeSecuredSubTlvStartIdx(
  ETHTSYN_P2CONST(uint8) FupMsgPtr,
                  uint16 LenByte);
#  endif /* (ETHTSYN_MESSAGE_COMPLIANCE == STD_OFF) */
# endif /* (ETHTSYN_SITESYNCSYNCSM == STD_ON) */

/**********************************************************************************************************************
 *  MANAGEMENT QUEUE HANDLING
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_MgmtQHndl_GetFreeElemIdx
 *********************************************************************************************************************/
/*! \brief          Gets and locks a free element of the passed queue.
 *  \details        -
 *  \param[in,out]   QueueFreeIdxPtr
 *                     In:  QueueSize - No free queue element available
 *                          other values - Index of the first free queue element
 *                     Out: QueueSize - No more free elements are available
 *                          other values - Index of the next free queue element
 *  \param[in,out]   QueueCurrProcIdxPtr
 *                     In:  QueueSize - No queue element is in use
 *                          other values - Index of the first used queue element
 *                     Out: Index of the first used queue element
 *  \param[in]      QueueSize  Total size of the element queue
 *  \return         QueueSize - No free element available
 *  \return         other values - Index of the free and now locked element
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      TRUE for different QueueFreeIdxPtr and QueueCurrProcIdxPtr
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(uint8, ETHTSYN_CODE) EthTSyn_SwtMgmt_MgmtQHndl_GetFreeElemIdx(
  ETHTSYN_P2VAR(uint8) QueueFreeIdxPtr,
  ETHTSYN_P2VAR(uint8) QueueCurrProcIdxPtr,
                uint8  QueueSize);

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_MgmtQHndl_ReleaseElem
 *********************************************************************************************************************/
/*! \brief          Releases the first used element of the passed queue.
 *  \details        -
 *  \param[in,out]   QueueFreeIdxPtr
 *                     In:  QueueSize - No free queue element available
 *                          other values - Index of the first free queue element
 *                     Out: Index of the next free queue element
 *  \param[in,out]   QueueCurrProcIdxPtr
 *                     In:  Index of the first used queue element
 *                     Out: QueueSize - No more queue elements are in use
 *                          other values - Index of the first used queue element
 *  \param[in]      QueueSize  Total size of the element queue
 *  \pre            At least one element of the passed queue is pending for processing, i.e.
 *                  (*QueueCurrProcIdx) < QueueSize
 *  \context        TASK|ISR2
 *  \reentrant      TRUE for different QueueIdx
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_MgmtQHndl_ReleaseElem(
  ETHTSYN_P2VAR(uint8) QueueFreeIdxPtr,
  ETHTSYN_P2VAR(uint8) QueueCurrProcIdxPtr,
                uint8  QueueSize);

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_MgmtQHndl_IncElemIdx
 *********************************************************************************************************************/
/*! \brief          Increments the passed queue element index and handles the index wrap-around.
 *  \details        -
 *  \param[in]      QueueSize  Total size of the element queue
 *  \param[in,out]  ElemIdxPtr
 *                     In:  Current element index
 *                     Out: Incremented element index (< QueueSize)
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_MgmtQHndl_IncElemIdx(
                uint8  QueueSize,
  ETHTSYN_P2VAR(uint8) ElemIdxPtr);

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_MgmtQHndl_IncElemProcIter
 *********************************************************************************************************************/
/*! \brief          Increments the passed queue element processing iterator.
 *  \details        -
 *  \param[in]      QueueFreeIdx      Index of the first free queue element
 *  \param[in]      QueueCurrProcIdx  Index of the first used queue element
 *                                    [range: QueueCurrProcIdx < QueueSize]
 *  \param[in]      QueueSize         Total size of the element queue
 *  \param[in,out]  QueueElemProcIterPtr
 *                     In:  Current iteration index
 *                     Out: QueueSize - End of queue was reached
 *                          other values - The next iteration index
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      TRUE
 *  \note           End of queue is reached when QueueElemIter reaches the 'QueueFreeIdx' or the 'QueueCurrProcIdx'
 *                  of the queue
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_MgmtQHndl_IncElemProcIter(
                uint8        QueueFreeIdx,
                uint8        QueueCurrProcIdx,
                uint8        QueueSize,
  ETHTSYN_P2VAR(uint8_least) QueueElemProcIterPtr);

/**********************************************************************************************************************
 *  RX BUFFER HANDLING
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_RxBufHndl_Poll
 *********************************************************************************************************************/
/*! \brief          Polls the RxMgmtObject of all pending received messages.
 *  \details        -
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_RxBufHndl_Poll(void);

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_RxBufHndl_IncIter
 *********************************************************************************************************************/
 /*! \brief          Increments the passed Rx-Buffer iterator.
  *  \details        -
  *  \param[in,out]  RxBufIterPtr
  *                    In: Current Rx-Buffer index
  *                    Out: EthTSyn_GetSizeOfSwtMgmtRxBuf() - No more pending Rx-Buffers
  *                         < EthTSyn_GetSizeOfSwtMgmtRxBuf() - Index of the next pending Rx-Buffer
  *  \pre            -
  *  \context        TASK|ISR2
  *  \reentrant      FALSE
  *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_RxBufHndl_IncIter(
  ETHTSYN_P2VAR(EthTSyn_SwtMgmtRxBufIterType) RxBufIterPtr);

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_RxBufHndl_ProcPending
 *********************************************************************************************************************/
/*! \brief          Processes pending received messages in strict order.
 *  \details        -
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_RxBufHndl_ProcPending(void);

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_RxBufHndl_GetFreeIdx
 *********************************************************************************************************************/
/*! \brief          Gets and locks the next free Rx buffer in the queue.
 *  \details        -
 *  \return         EthTSyn_GetSizeOfSwtMgmtRxBuf() - No free Rx buffer available
 *  \return         other values - Index of the free and now locked Rx buffer
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(uint8, ETHTSYN_CODE) EthTSyn_SwtMgmt_RxBufHndl_GetFreeIdx(void);

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_RxBufHndl_Release
 *********************************************************************************************************************/
/*! \brief          Releases the first locked Rx buffer in the queue.
 *  \details        -
 *  \pre            At least one Rx buffer is locked.
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_RxBufHndl_Release(void);

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_RxBufHndl_ReleaseAllPending
 *********************************************************************************************************************/
/*! \brief          Marks all pending Rx buffers of the passed EthTSyn controller as to be released.
 *  \details        -
 *  \param[in]      EthTSynCtrlIdx   Index of the EthTSyn controller
 *                  [range: EthTSynCtrlIdx < EthTSyn_GetSizeOfCtrl()]
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      TRUE for different EthTSynCtrlIdx
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_RxBufHndl_ReleaseAllPending(
  EthTSyn_IntCtrlIdxType EthTSynCtrlIdx);

/**********************************************************************************************************************
 *  TX MGMT OBJECT HANDLING
 *********************************************************************************************************************/
# if (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_TxMgmtObjHndl_Poll
 *********************************************************************************************************************/
/*! \brief          Polls the TxMgmtObject of all pending TxMgmtObjects.
 *  \details        -
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_TxMgmtObjHndl_Poll(void);

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_TxMgmtObjHndl_IncIter
 *********************************************************************************************************************/
 /*! \brief          Increments the passed TxMgmtObject iterator.
  *  \details        -
  *  \param[in,out]  TxMgmtObjIterPtr
  *                    In: Current TxMgmtObject index
  *                    Out: EthTSyn_GetSizeOfSwtMgmtTxMgmtObj() - No more pending TxMgmtObjects
  *                         < EthTSyn_GetSizeOfSwtMgmtTxMgmtObj - Index of the next pending TxMgmtObject
  *  \pre            -
  *  \context        TASK|ISR2
  *  \reentrant      FALSE
  *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_TxMgmtObjHndl_IncIter(
  ETHTSYN_P2VAR(EthTSyn_SwtMgmtTxMgmtObjCfgIterType) TxMgmtObjIterPtr);

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_TxMgmtObjHndl_ProcPending
 *********************************************************************************************************************/
/*! \brief          Processes pending TxMgmtObjects in strict order.
 *  \details        -
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_TxMgmtObjHndl_ProcPending(void);

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_TxMgmtObjHndl_CpyTs
 *********************************************************************************************************************/
/*! \brief          Copies the timestamp information of the TxMgmtObject to the linked state machine.
 *  \details        -
 *  \param[in]      TxMgmtObjIdx  Index of the Tx management object
  *                 [range: TxMgmtObjIdx < EthTSyn_GetSizeOfSwtMgmtTxMgmtObj()]
 *  \pre            State of the Tx management object is AVAILABLE
 *  \context        TASK|ISR2
 *  \reentrant      TRUE for different TxMgmtObjIdx
 *  \spec
 *    requires TxMgmtObjIdx < EthTSyn_GetSizeOfSwtMgmtTxMgmtObj();
 *  \endspec
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_TxMgmtObjHndl_CpyTs(
  EthTSyn_SwtMgmtTxMgmtObjCfgIterType TxMgmtObjIdx);

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_TxMgmtObjHndl_GetFreeIdx
 *********************************************************************************************************************/
 /*! \brief          Gets and locks the next free TxMgmtObject in the queue.
  *  \details        -
  *  \return         EthTSyn_GetSizeOfSwtMgmtTxMgmtObj() - No free TxMgmtObject available
  *  \return         other values - Index of the free and now locked TxMgmtObject
  *  \pre            -
  *  \context        TASK|ISR2
  *  \reentrant      FALSE
  *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(uint8, ETHTSYN_CODE) EthTSyn_SwtMgmt_TxMgmtObjHndl_GetFreeIdx(void);

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_TxMgmtObjHndl_Release
 *********************************************************************************************************************/
/*! \brief          Releases the first locked TxMgmtObject in the queue.
 *  \details        -
 *  \pre            At least one TxMgmtObject is locked.
 *  \pre            Has to be called with disabled interrupts.
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_TxMgmtObjHndl_Release(void);

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_TxMgmtObjHndl_ReleaseAllPending
 *********************************************************************************************************************/
/*! \brief          Marks all pending Tx management objects of the passed EthTSyn controller as to be released.
 *  \details        -
 *  \param[in]      EthTSynCtrlIdx   Index of the EthTSyn controller
 *                  [range: EthTSynCtrlIdx < EthTSyn_GetSizeOfCtrl()]
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      TRUE for different EthTSynCtrlIdx
 *  \spec
 *    requires EthTSynCtrlIdx < EthTSyn_GetSizeOfCtrl();
 *  \endspec
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_TxMgmtObjHndl_ReleaseAllPending(
  EthTSyn_IntCtrlIdxType EthTSynCtrlIdx);
# endif /* (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON) */

/**********************************************************************************************************************
 *  MGMT OBJECT HANDLING FUNCTION PROTOTYPES
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_CpyMgmtObjInfo
 *********************************************************************************************************************/
 /*! \brief          Copies the switch management object information to the EthTSyn management object.
  *  \details        -
  *  \param[in]      MgmtObjHndlIdx   Index of the management object handle
  *                                   [range: MgmtObjHndlIdx < EthTSyn_GetSizeOfSwtMgmtMgmtObjHndl()]
  *  \pre            Has to be called with disabled interrupts.
  *  \pre            EthSwtMgmtOjbPtr of the passed MgmtObjHndl has to be valid so the TxMgmtObj/RxBuf handle structure
  *                  has to be in state PENDING or WAIT_RELEASE.
  *  \context        TASK|ISR2
  *  \reentrant      TRUE
  *  \spec
  *     MgmtObjHndlIdx < EthTSyn_GetSizeOfSwtMgmtMgmtObjHndl();
  *  \endspec
  *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_CpyMgmtObjInfo(
  EthTSyn_SwtMgmtMgmtObjHndlIterType MgmtObjHndlIdx);

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_Rx_ProcMsgBuffer
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
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_Rx_ProcMsgBuffer(
  EthTSyn_SwtMgmtRxBufIterType RxBufIdx)
{
  /*
  * TimeDomainId is known from message
  * TimeDomainIdx can be retrieved using the TimeDomainId
  * The EthTSyn-Port can be found by iterating all Ports of the TimeDomain(Idx)
  * The EthTSyn-Port has to match the CtrlIdx and the SwtPortIdx
  * Within a TimeDomain only one Port for the pair of EthIf-Ctrl and Swt-Port can exist
  */

  /* ----- Implementation --------------------------------------------- */
  /* #10 Get matching EthTSyn Port and set message buffer state to processing. */
  const EthTSyn_IntPortIdxType portIdx = EthTSyn_SwtMgmt_Rx_GetPortForMsgBuffer(RxBufIdx);

  EthTSyn_SetStateOfSwtMgmtRxBuf(RxBufIdx, ETHTSYN_PROC_STATEOFSWTMGMTRXBUF);

  /* #20 If a valid port was found. */
  if(portIdx < EthTSyn_GetSizeOfPort())
  {
    /* #200 Process the message. */
    EthTSyn_SwtMgmt_Rx_ProcRcvdMsg(portIdx, RxBufIdx);
  }
# if (ETHTSYN_SWT_TIME_SYNC_SUPPORT == STD_ON)
  /* #30 Otherwise (if ETHTSYN_SWT_TIME_SYNC_SUPPORT == STD_ON). */
  else
  {
    /* #300 Handle the potential reception of a switch sync frame. */
    EthTSyn_SwtTimeSync_SwtSyncFrameHandleRx(RxBufIdx);
  }
# endif /* (ETHTSYN_SWT_TIME_SYNC_SUPPORT == STD_ON) */
} /* EthTSyn_SwtMgmt_Rx_ProcMsgBuffer() */

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_Rx_GetPortForMsgBuffer
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
 */
/* PRQA S 6050, 6080 1 */ /* MD_EthTSyn_6050_CslAccess, MD_MSR_STMIF */
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_IntPortIdxType, ETHTSYN_CODE) EthTSyn_SwtMgmt_Rx_GetPortForMsgBuffer(
  EthTSyn_SwtMgmtRxBufIterType RxBufIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthTSyn_PortIndIterType portIndIter;
  EthTSyn_IntPortIdxType portIdx = EthTSyn_GetSizeOfPort();
  const EthTSyn_SwtMgmtMgmtObjHndlIdxOfSwtMgmtRxBufCfgType mgmtObjHndlIdx =
    EthTSyn_GetSwtMgmtMgmtObjHndlIdxOfSwtMgmtRxBufCfg(RxBufIdx);
  EthTSyn_SwtMgmt_MgmtInfoMgmtStructType mgmtInfoMgmt;

  /* ----- Implementation ----------------------------------------------- */
  mgmtInfoMgmt = EthTSyn_GetSwtMgmtInfoOfSwtMgmtMgmtObjHndl(mgmtObjHndlIdx);
  /* #10 If switch management information of received message is valid. */
  if(mgmtInfoMgmt.IsValid == TRUE)
  {
    const EthTSyn_CtrlIdxOfSwtMgmtRxBufType ethTSynCtrlIdx = EthTSyn_GetCtrlIdxOfSwtMgmtRxBuf(RxBufIdx);
    /*@ assert ethTSynCtrlIdx < EthTSyn_GetSizeOfCtrl(); */                                                            /* VCA_ETHTSYN_SWT_MGMT_RX_BUF_VALID_CTRL_IDX */
    /* #20 Iterate all EthTSyn ports of the EthTSyn controller the message was received on. */
    for(portIndIter = EthTSyn_GetPortIndStartIdxOfCtrl(ethTSynCtrlIdx);
        portIndIter < EthTSyn_GetPortIndEndIdxOfCtrl(ethTSynCtrlIdx);
        portIndIter++)
    {
      const EthTSyn_PortIndType tmpPortIdx = EthTSyn_GetPortInd(portIndIter);
      /*@ assert tmpPortIdx < EthTSyn_GetSizeOfPort(); */                                                              /* VCA_ETHTSYN_PORT_IND_TABLE_CSL03 */
      const EthTSyn_SwitchPortMgmtIdxOfPortType swtPortMgmtIdx = EthTSyn_GetSwitchPortMgmtIdxOfPort(tmpPortIdx);

      /* #30 If current port is a switch port. */
      if(swtPortMgmtIdx < EthTSyn_GetSizeOfSwitchPortMgmt())
      {
        /* #40 Check if switch port info matches. */
        /* PRQA S 3415 3 */ /* MD_EthTSyn_3415_CslReadOnly */
        if(
          (EthTSyn_GetPortIdxOfSwitchPortMgmt(swtPortMgmtIdx) == mgmtInfoMgmt.MgmtInfo.PortIdx) &&
          (EthTSyn_GetSwitchIdxOfSwitchPortMgmt(swtPortMgmtIdx) == mgmtInfoMgmt.MgmtInfo.SwitchIdx)
          )
        {
          const EthTSyn_TimeDomainIdxOfPortType timeDomainIdx = EthTSyn_GetTimeDomainIdxOfPort(tmpPortIdx);
          const EthTSyn_SwtMgmtRcvdMsgBufStartIdxOfSwtMgmtRxBufCfgType rcvdMsgBufStartIdx =
            EthTSyn_GetSwtMgmtRcvdMsgBufStartIdxOfSwtMgmtRxBufCfg(RxBufIdx);
          /* #50 If time domain matches. */
          if(EthTSyn_GetIdOfTimeDomain(timeDomainIdx) ==
            IpBase_GetUint8(EthTSyn_GetAddrSwtMgmtRcvdMsgBuf(rcvdMsgBufStartIdx), ETHTSYN_MSG_HDR_DOMAIN_NUM_OFS))
          {
            /* #60 Stop iteration because a matching port was found. */
            portIdx = (EthTSyn_IntPortIdxType)tmpPortIdx;
            break;
          }
        }
      }
    }
  }

  return portIdx;
} /* EthTSyn_SwtMgmt_Rx_GetPortForMsgBuffer() */

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_Rx_ProcRcvdMsg
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
/* PRQA S 6050 1 */ /* MD_EthTSyn_6050_MsgReception */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_Rx_ProcRcvdMsg(
  EthTSyn_IntPortIdxType       PortIdx,
  EthTSyn_SwtMgmtRxBufIterType RxBufIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  const EthTSyn_SwtMgmtRcvdMsgBufStartIdxOfSwtMgmtRxBufCfgType rcvdMsgBufStartIdx =
    EthTSyn_GetSwtMgmtRcvdMsgBufStartIdxOfSwtMgmtRxBufCfg(RxBufIdx);
  ETHTSYN_P2CONST(uint8) rcvdMsgPtr = EthTSyn_GetAddrSwtMgmtRcvdMsgBuf(rcvdMsgBufStartIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Get the message type of the received message and trigger the processing of the message accordingly. */
  /* Shift of ETHTSYN_MSG_HDR_MSG_TYPE_SHIFT is not required because it is 0. */
  switch(IpBase_GetUint8(rcvdMsgPtr, ETHTSYN_MSG_HDR_MSG_TYPE_OFS) & ETHTSYN_MSG_HDR_MSG_TYPE_MASK)
  {
# if (ETHTSYN_PDELAY_RESPONDER_SUPPORT == STD_ON)
  case ETHTSYN_MSG_TYPE_PDELAY_REQ:
    {
      /* Process Pdelay_Req message. */
      EthTSyn_SwtMgmt_Rx_ProcRcvdPdReqMsg(PortIdx, RxBufIdx);
      break;
    }
# endif /* (ETHTSYN_PDELAY_RESPONDER_SUPPORT == STD_ON) */

# if (ETHTSYN_PDELAY_INITIATOR_SUPPORT == STD_ON)
  case ETHTSYN_MSG_TYPE_PDELAY_RESP:
    {
      EthTSyn_SwtMgmt_Rx_ProcRcvdPdRespMsg(PortIdx, RxBufIdx);
      break;
    }

  case ETHTSYN_MSG_TYPE_PDELAY_RES_FOLLOW_UP:
    {
      EthTSyn_SwtMgmt_Rx_ProcRcvdPdRespFupMsg(PortIdx, RxBufIdx);
      break;
    }
# endif /* (ETHTSYN_PDELAY_INITIATOR_SUPPORT == STD_ON) */

# if (ETHTSYN_SLAVE_SUPPORT == STD_ON)
  case ETHTSYN_MSG_TYPE_SYNC:
    {
      EthTSyn_SwtMgmt_Rx_ProcRcvdSyncMsg(PortIdx, RxBufIdx);
      break;
    }

  case ETHTSYN_MSG_TYPE_FOLLOW_UP:
    {
      EthTSyn_SwtMgmt_Rx_ProcRcvdFupMsg(PortIdx, RxBufIdx);
      break;
    }
# else
  case ETHTSYN_MSG_TYPE_SYNC:
  {
    uint64 srcClockIdentity = IpBase_GetUint64(rcvdMsgPtr, ETHTSYN_MSG_HDR_SRC_PORT_IDENT_CLOCK_IDENT_OFS);
    (void)EthTSyn_UtilRx_SyncPortRoleCheckWithMasterSlaveConflictDetection(PortIdx, srcClockIdentity);
    break;
  }
# endif /* (ETHTSYN_SLAVE_SUPPORT == STD_ON) */

# if (ETHTSYN_ANNOUNCE_RX_SUPPORT == STD_ON)
  case ETHTSYN_MSG_TYPE_ANNOUNCE:
    {
      EthTSyn_SwtMgmt_Rx_ProcRcvdAnnounceMsg(PortIdx, RxBufIdx);
      break;
    }
# endif /* (ETHTSYN_ANNOUNCE_RX_SUPPORT == STD_ON) */

  default:
    {
      /* Nothing to do here. */
      break;
    }
  } /* END: switch(msgType) */
} /* EthTSyn_SwtMgmt_Rx_ProcRcvdMsg() */

# if (ETHTSYN_SLAVE_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_Rx_FwdSyncMsgToEndStation
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
/* PRQA S 6050 1 */ /* MD_EthTSyn_6050_CslAccess */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_Rx_FwdSyncMsgToEndStation(
  EthTSyn_IntTimeDomainIdxType TimeDomainIdx,
  EthTSyn_SwtMgmtRxBufIterType RxBufIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthTSyn_IntVltMgmtType ingressTsVltMgmt;
  EthTSyn_TimediffType swtResidenceTime;
  EthTSyn_IntPortIdxType portIdx = EthTSyn_SwtMgmt_GetEndStationSlavePortIdx(TimeDomainIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if the message has to be forwarded to the EthTSyn End-Station. */
  if (portIdx < EthTSyn_GetSizeOfPort())
  {
    const EthTSyn_SwtMgmtRcvdMsgBufStartIdxOfSwtMgmtRxBufCfgType rcvdMsgBufStartIdx =
      EthTSyn_GetSwtMgmtRcvdMsgBufStartIdxOfSwtMgmtRxBufCfg(RxBufIdx);
    ETHTSYN_P2CONST(uint8) rcvdMsgPtr = EthTSyn_GetAddrSwtMgmtRcvdMsgBuf(rcvdMsgBufStartIdx);

    /* #20 Get the Sync ingress timestamp and calculate the Sync switch residence time. */
    if (EthTSyn_SwtMgmt_Rx_GetSyncIngrTsAndSwtResTime(RxBufIdx, &ingressTsVltMgmt, &swtResidenceTime) == E_OK)
    {
      const EthTSyn_SlavePortIdxOfPortType slavePortIdx = EthTSyn_GetSlavePortIdxOfPort(portIdx);
      /*@ assert slavePortIdx < EthTSyn_GetSizeOfSlavePort(); */
      ETHTSYN_CONSTP2VAR(EthTSyn_SyncReceiveSmType) syncReceiveSmPtr = EthTSyn_GetAddrSyncReceiveSm(slavePortIdx);

      /* #30 Write switch residence time to sync receive SM. */
      ETHTSYN_ENTER_CRITICAL_SECTION_0();
      syncReceiveSmPtr->Sync.SwtResidenceTime = swtResidenceTime;
      ETHTSYN_LEAVE_CRITICAL_SECTION_0();

      /* #40 Forward Sync message to the End-Station slave port. */
      EthTSyn_SlaveRx_ProcRcvdSyncMsg(rcvdMsgPtr, portIdx, &ingressTsVltMgmt);
    }
  }
} /* EthTSyn_SwtMgmt_Rx_FwdSyncMsgToEndStation() */
# endif /* (ETHTSYN_SLAVE_SUPPORT == STD_ON) */

# if (ETHTSYN_SLAVE_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_Rx_GetSyncIngrTsAndSwtResTime
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
ETHTSYN_LOCAL_INLINE FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_SwtMgmt_Rx_GetSyncIngrTsAndSwtResTime(
                EthTSyn_SwtMgmtRxBufIterType  RxBufIdx,
  ETHTSYN_P2VAR(EthTSyn_IntVltMgmtType)       IngressTsVltMgmtPtr,
  ETHTSYN_P2VAR(EthTSyn_TimediffType)         SwtResidenceTimePtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
#  if (ETHTSYN_SWT_MGMT_ONE_TAS == STD_ON)
  /* #10 If host and switch are considered as one time aware system. */
  {
    const EthTSyn_SwtMgmtMgmtObjHndlIdxOfSwtMgmtRxBufCfgType mgmtObjHndlIdx =
      EthTSyn_GetSwtMgmtMgmtObjHndlIdxOfSwtMgmtRxBufCfg(RxBufIdx);
    EthTSyn_TsMgmtStructType swtIngrTsMgmt;

    /* #100 If the switch ingress timestamp is available, use it as sync ingress timestamp for further processing and
     *      set residence time to zero. */
    swtIngrTsMgmt = EthTSyn_GetSwtIngressTsMgmtOfSwtMgmtMgmtObjHndl(mgmtObjHndlIdx);
    if (swtIngrTsMgmt.State == ETHTSYN_TS_S_AVAILABLE)
    {
      (*IngressTsVltMgmtPtr) = EthTSyn_UtilVlt_TsMgmtToIntVltMgmt(&swtIngrTsMgmt);
      (*SwtResidenceTimePtr) = 0;

      retVal = E_OK;
    }
  }
#  else
  /* #20 Otherwise. */
  {
    EthTSyn_IntVltMgmtType hostIngressIntVltMgmt;

    /* #200 Check if the ingress timestamp of the host is valid. */
    hostIngressIntVltMgmt = EthTSyn_GetHostIngressIntVltMgmtOfSwtMgmtRxBuf(RxBufIdx);
    if (hostIngressIntVltMgmt.IntVltValid == TRUE)
    {
      /* #2000 If the host ingress timestamp is valid, use it as sync ingress timestamp for further processing. */
      (*IngressTsVltMgmtPtr) = hostIngressIntVltMgmt;

#   if (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON)
      /* #2001 If Switch timestamping is enabled. */
      {
        Std_ReturnType calcRetVal = E_NOT_OK;
        const EthTSyn_SwtMgmtMgmtObjHndlIdxOfSwtMgmtRxBufCfgType mgmtObjHndlIdx =
          EthTSyn_GetSwtMgmtMgmtObjHndlIdxOfSwtMgmtRxBufCfg(RxBufIdx);
        EthTSyn_TsMgmtStructType swtIngrTsMgmt;
        EthTSyn_TsMgmtStructType swtEgrTsMgmt;

        swtIngrTsMgmt = EthTSyn_GetSwtIngressTsMgmtOfSwtMgmtMgmtObjHndl(mgmtObjHndlIdx);
        swtEgrTsMgmt = EthTSyn_GetSwtEgressTsMgmtOfSwtMgmtMgmtObjHndl(mgmtObjHndlIdx);

        /* #20010 Try to compute the switch residence time of the sync message. */
        if ((swtIngrTsMgmt.State == ETHTSYN_TS_S_AVAILABLE) && (swtEgrTsMgmt.State == ETHTSYN_TS_S_AVAILABLE))
        {
          if(EthTSyn_Util_TimestampMinusTimestamp(&swtEgrTsMgmt.Ts, &swtIngrTsMgmt.Ts, SwtResidenceTimePtr) == E_OK)
          {
            /* #200100 Check calculated switch residence time for sensibility (i.e. >= 0). */
            if((*SwtResidenceTimePtr) >= 0)
            {
              calcRetVal = E_OK;
            }
          }
        }

        /* #20011 Use the configured default value for the residence time in case calculation failed. */
        if (calcRetVal != E_OK)
        {
          (*SwtResidenceTimePtr) = (EthTSyn_TimediffType)ETHTSYN_SWT_RX_TO_UPLINK_RESIDENCE_TIME_NS;
        }
      }
#   else
      /* #2002 Otherwise, set residence time to zero. */
      {
        (*SwtResidenceTimePtr) = 0;
      }
#   endif /* (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON) */

      retVal = E_OK;
    }
  }
#  endif /* (ETHTSYN_SWT_MGMT_ONE_TAS == STD_ON) */

  return retVal;
} /* EthTSyn_SwtMgmt_Rx_GetSyncIngrTsAndSwtResTime */
# endif /* (ETHTSYN_SLAVE_SUPPORT == STD_ON) */

# if (ETHTSYN_SLAVE_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_Rx_FwdFupMsgToEndStation
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_Rx_FwdFupMsgToEndStation(
  EthTSyn_IntTimeDomainIdxType TimeDomainIdx,
  EthTSyn_SwtMgmtRxBufIterType RxBufIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  const EthTSyn_IntPortIdxType endStationSlavePortIdx = EthTSyn_SwtMgmt_GetEndStationSlavePortIdx(TimeDomainIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if the message has to be forwarded to the EthTSyn End-Station. */
  if(endStationSlavePortIdx < EthTSyn_GetSizeOfPort())
  {
    const EthTSyn_SwtMgmtRcvdMsgBufStartIdxOfSwtMgmtRxBufCfgType rcvdMsgBufStartIdx =
      EthTSyn_GetSwtMgmtRcvdMsgBufStartIdxOfSwtMgmtRxBufCfg(RxBufIdx);

    /* #20 Pass the message to the end station implementation. */
    EthTSyn_SlaveRx_ProcRcvdFupMsg(EthTSyn_GetAddrSwtMgmtRcvdMsgBuf(rcvdMsgBufStartIdx), endStationSlavePortIdx);
  }
} /* EthTSyn_SwtMgmt_Rx_FwdFupMsgToEndStation() */
# endif /* (ETHTSYN_SLAVE_SUPPORT == STD_ON) */

# if (ETHTSYN_PDELAY_RESPONDER_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_Rx_ProcRcvdPdReqMsg
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_Rx_ProcRcvdPdReqMsg(
  EthTSyn_IntPortIdxType       PortIdx,
  EthTSyn_SwtMgmtRxBufIterType RxBufIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthTSyn_TsMgmtStructType ingressTsMgmt;
  const EthTSyn_SwtMgmtRcvdMsgBufStartIdxOfSwtMgmtRxBufCfgType rcvdMsgBufStartIdx =
    EthTSyn_GetSwtMgmtRcvdMsgBufStartIdxOfSwtMgmtRxBufCfg(RxBufIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Get the Pdelay_Req ingress timestamp. */
#  if (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON)
  ingressTsMgmt = EthTSyn_GetSwtIngressTsMgmtOfSwtMgmtMgmtObjHndl(
    EthTSyn_GetSwtMgmtMgmtObjHndlIdxOfSwtMgmtRxBufCfg(RxBufIdx));
#  else
  ingressTsMgmt = EthTSyn_UtilVlt_IntVltMgmtToTsMgmt(EthTSyn_GetAddrHostIngressIntVltMgmtOfSwtMgmtRxBuf(RxBufIdx));
#  endif /* (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON) */

  /* #20 Trigger processing of the received Pdelay_Req. */
  EthTSyn_Pdelay_ProcRcvdReqMsg(EthTSyn_GetAddrSwtMgmtRcvdMsgBuf(rcvdMsgBufStartIdx), &ingressTsMgmt, PortIdx);
} /* EthTSyn_SwtMgmt_Rx_ProcRcvdPdReqMsg() */
# endif /* (ETHTSYN_PDELAY_RESPONDER_SUPPORT == STD_ON) */

# if (ETHTSYN_PDELAY_INITIATOR_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_Rx_ProcRcvdPdRespMsg
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_Rx_ProcRcvdPdRespMsg(
  EthTSyn_IntPortIdxType       PortIdx,
  EthTSyn_SwtMgmtRxBufIterType RxBufIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthTSyn_TsMgmtStructType ingressTsMgmt;
  const EthTSyn_SwtMgmtRcvdMsgBufStartIdxOfSwtMgmtRxBufCfgType rcvdMsgBufStartIdx =
    EthTSyn_GetSwtMgmtRcvdMsgBufStartIdxOfSwtMgmtRxBufCfg(RxBufIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Get the Pdelay_Resp ingress timestamp. */
#  if (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON)
  ingressTsMgmt = EthTSyn_GetSwtIngressTsMgmtOfSwtMgmtMgmtObjHndl(
    EthTSyn_GetSwtMgmtMgmtObjHndlIdxOfSwtMgmtRxBufCfg(RxBufIdx));
#  else
    ingressTsMgmt = EthTSyn_UtilVlt_IntVltMgmtToTsMgmt(EthTSyn_GetAddrHostIngressIntVltMgmtOfSwtMgmtRxBuf(RxBufIdx));
#  endif /* (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON) */

  /* #20 Trigger processing of the received Pdelay_Resp. */
  EthTSyn_Pdelay_ProcRcvdRespMsg(EthTSyn_GetAddrSwtMgmtRcvdMsgBuf(rcvdMsgBufStartIdx), &ingressTsMgmt, PortIdx);
} /* EthTSyn_SwtMgmt_Rx_ProcRcvdPdRespMsg() */

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_Rx_ProcRcvdPdRespFupMsg
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_Rx_ProcRcvdPdRespFupMsg(
  EthTSyn_IntPortIdxType       PortIdx,
  EthTSyn_SwtMgmtRxBufIterType RxBufIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  const EthTSyn_SwtMgmtRcvdMsgBufStartIdxOfSwtMgmtRxBufCfgType rcvdMsgBufStartIdx =
    EthTSyn_GetSwtMgmtRcvdMsgBufStartIdxOfSwtMgmtRxBufCfg(RxBufIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Trigger processing of the received Pdelay_Resp_Fup. */
  EthTSyn_Pdelay_ProcRcvdRespFupMsg(EthTSyn_GetAddrSwtMgmtRcvdMsgBuf(rcvdMsgBufStartIdx), PortIdx);
} /* EthTSyn_SwtMgmt_Rx_ProcRcvdPdRespFupMsg() */
# endif /* (ETHTSYN_PDELAY_INITIATOR_SUPPORT == STD_ON) */

# if (ETHTSYN_SLAVE_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_Rx_ProcRcvdSyncMsg
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
 */
/* PRQA S 6050 1 */ /* MD_EthTSyn_6050_CslAccess */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_Rx_ProcRcvdSyncMsg(
  EthTSyn_IntPortIdxType       PortIdx,
  EthTSyn_SwtMgmtRxBufIterType RxBufIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  const EthTSyn_IntTimeDomainIdxType timeDomainIdx = EthTSyn_GetTimeDomainIdxOfPort(PortIdx);
  const EthTSyn_SwtMgmtRcvdMsgBufStartIdxOfSwtMgmtRxBufCfgType rcvdMsgBufStartIdx =
    EthTSyn_GetSwtMgmtRcvdMsgBufStartIdxOfSwtMgmtRxBufCfg(RxBufIdx);
  ETHTSYN_P2CONST(uint8) rcvdMsgPtr = EthTSyn_GetAddrSwtMgmtRcvdMsgBuf(rcvdMsgBufStartIdx);
  const uint64 msgSrcClockIdentity = IpBase_GetUint64(rcvdMsgPtr, ETHTSYN_MSG_HDR_SRC_PORT_IDENT_CLOCK_IDENT_OFS);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if sync message can be received on given Port. */
  if(EthTSyn_SwtMgmt_Rx_IsPortReadyToRcvSync(PortIdx, msgSrcClockIdentity) == TRUE)
  {
    const EthTSyn_SlavePortIdxOfPortType slavePortIdx = EthTSyn_GetSlavePortIdxOfPort(PortIdx);
    /*@ assert slavePortIdx < EthTSyn_GetSizeOfSlavePort(); */                                                         /* VCA_ETHTSYN_SYNC_PORT_ROLE_CHECK_PASSED */
#  if((ETHTSYN_SITESYNCSYNCSM == STD_ON) || (ETHTSYN_SWT_TIME_SYNC_SUPPORT == STD_ON))
    ETHTSYN_CONSTP2VAR(EthTSyn_SyncReceiveSmType) syncReceiveSmPtr = EthTSyn_GetAddrSyncReceiveSm(slavePortIdx);
#  endif /* (ETHTSYN_SITESYNCSYNCSM == STD_ON) || (ETHTSYN_SWT_TIME_SYNC_SUPPORT == STD_ON) */

    /* #20 Verify sequence Id and write sync message attributes to sync receive SM for later processing. */
    if(EthTSyn_SlaveRx_WriteSyncMsgToSyncReceiveSm(slavePortIdx, rcvdMsgPtr) == E_OK)
    {
      ETHTSYN_ENTER_CRITICAL_SECTION_0();

      /* #30 Reset sync Rx timeout. */
#  if (ETHTSYN_SITESYNCSYNCSM == STD_ON)
      syncReceiveSmPtr->Sync.SyncRxTimeoutCnt = EthTSyn_GetSwtMgmtSyncTimeoutOfTimeDomain(timeDomainIdx);
#  endif /* (ETHTSYN_SITESYNCSYNCSM == STD_ON) */

      /* #40 Write switch ingress timestamp to sync receive SM (if switch time sync is enabled). */
#  if (ETHTSYN_SWT_TIME_SYNC_SUPPORT == STD_ON)
      syncReceiveSmPtr->Sync.SwtIngressTsMgmt = EthTSyn_GetSwtIngressTsMgmtOfSwtMgmtMgmtObjHndl(
        EthTSyn_GetSwtMgmtMgmtObjHndlIdxOfSwtMgmtRxBufCfg(RxBufIdx));
#  endif /* (ETHTSYN_SWT_TIME_SYNC_SUPPORT == STD_ON) */

      ETHTSYN_LEAVE_CRITICAL_SECTION_0();

      /* #50 Handle SiteSyncSync state machine (if bridge mode is set to TRANSPARENT_CLOCK). */
#  if (ETHTSYN_SWT_MGMT_BRIDGE_MODE == ETHTSYN_SWT_MGMT_BRIDGE_MODE_TRANSPARENT)
      EthTSyn_SwtMgmt_SiteSyncSync_RcvdSync(PortIdx, RxBufIdx);
#  endif /* (ETHTSYN_SWT_MGMT_BRIDGE_MODE == ETHTSYN_SWT_MGMT_BRIDGE_MODE_TRANSPARENT) */

      /* #60 Forward Sync message to End-Station. */
      EthTSyn_SwtMgmt_Rx_FwdSyncMsgToEndStation(timeDomainIdx, RxBufIdx);
    }
  }
} /* EthTSyn_SwtMgmt_Rx_ProcRcvdSyncMsg() */
# endif /* (ETHTSYN_SLAVE_SUPPORT == STD_ON) */

# if (ETHTSYN_SLAVE_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_Rx_IsPortReadyToRcvSync
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
 */
/* PRQA S 6050 1 */ /* MD_EthTSyn_6050_CslAccess */
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_SwtMgmt_Rx_IsPortReadyToRcvSync(
  EthTSyn_IntPortIdxType PortIdx,
  uint64                 SrcClockIdentity)
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean isReady = FALSE;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Verify port role and handle possible Master-Slave conflict. */
  if(EthTSyn_UtilRx_SyncPortRoleCheckWithMasterSlaveConflictDetection(PortIdx, SrcClockIdentity) == TRUE)
  {
    const EthTSyn_SlavePortIdxOfPortType slavePortIdx = EthTSyn_GetSlavePortIdxOfPort(PortIdx);
    /*@ assert slavePortIdx < EthTSyn_GetSizeOfSlavePort(); */                                                         /* VCA_ETHTSYN_PORT_READY_TO_RCV_SYNC */
    ETHTSYN_CONSTP2VAR(EthTSyn_SyncReceiveSmType) syncReceiveSmPtr = EthTSyn_GetAddrSyncReceiveSm(slavePortIdx);
    /* #20 Check if port is AsCapable. */
    if(EthTSyn_Util_IsAsCapable(PortIdx) == TRUE)
    {
      /* #30 Check if SyncReceiveSm is capable to receive a Sync message in its current state. */
      if(
        (syncReceiveSmPtr->State == ETHTSYN_S_SYNC_RCV_SM_DISCARD ) ||
        (syncReceiveSmPtr->State == ETHTSYN_S_SYNC_RCV_SM_WAIT_SYNC )
        )
      {
        isReady = TRUE;
      }
#  if (ETHTSYN_SITESYNCSYNCSM == STD_ON)
      if (syncReceiveSmPtr->State == ETHTSYN_S_SYNC_RCV_SM_SYNC_TIMEOUT)
      {
        isReady = TRUE;
      }
#  endif /* (ETHTSYN_SITESYNCSYNCSM == STD_ON) */
    }

    /* #40 If port is not ready to receive the sync message. */
    if (isReady == FALSE)
    {
      const EthTSyn_TimeDomainIdxOfPortType timeDomainIdx = EthTSyn_GetTimeDomainIdxOfPort(PortIdx);
      const EthTSyn_IntPortIdxType portIdxOfEndStationSlavePort =
        EthTSyn_SwtMgmt_GetEndStationSlavePortIdx(timeDomainIdx);

      /* #400 Change state of SyncReceiveSm to DISCARD. */
      syncReceiveSmPtr->State = ETHTSYN_S_SYNC_RCV_SM_DISCARD;

      /* #401 Change state of end station SyncReceiveSm to DISCARD as well (if applicable). */
      if (portIdxOfEndStationSlavePort < EthTSyn_GetSizeOfPort())
      {
        const EthTSyn_SlavePortIdxOfPortType endStationSlavePortIdx =
          EthTSyn_GetSlavePortIdxOfPort(portIdxOfEndStationSlavePort);
        /*@ assert endStationSlavePortIdx < EthTSyn_GetSizeOfSlavePort(); */
        ETHTSYN_CONSTP2VAR(EthTSyn_SyncReceiveSmType) endStationSyncReceiveSmPtr =
          EthTSyn_GetAddrSyncReceiveSm(endStationSlavePortIdx);
        endStationSyncReceiveSmPtr->State = ETHTSYN_S_SYNC_RCV_SM_DISCARD;
      }
    }
  }

  return isReady;
} /* EthTSyn_SwtMgmt_Rx_IsPortReadyToRcvSync() */
# endif /* (ETHTSYN_SLAVE_SUPPORT == STD_ON) */

# if (ETHTSYN_SLAVE_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_Rx_ProcRcvdFupMsg
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
/* PRQA S 6050 1 */ /* MD_EthTSyn_6050_CslAccess */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_Rx_ProcRcvdFupMsg(
  EthTSyn_IntPortIdxType       PortIdx,
  EthTSyn_SwtMgmtRxBufIterType RxBufIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
    const EthTSyn_SwtMgmtRcvdMsgBufStartIdxOfSwtMgmtRxBufCfgType rcvdMsgBufStartIdx =
      EthTSyn_GetSwtMgmtRcvdMsgBufStartIdxOfSwtMgmtRxBufCfg(RxBufIdx);
    ETHTSYN_P2CONST(uint8) rcvdMsgPtr = EthTSyn_GetAddrSwtMgmtRcvdMsgBuf(rcvdMsgBufStartIdx);
    const EthTSyn_SlavePortIdxOfPortType slavePortIdx = EthTSyn_GetSlavePortIdxOfPort(PortIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Verify that port is slave port. */
  if(slavePortIdx < EthTSyn_GetSizeOfSlavePort())
  {
    /* #20 Check if the FollowUp message matches the former received Sync message. */
    if(EthTSyn_SlaveRx_IsFupMatchingSync(rcvdMsgPtr, PortIdx) == TRUE)
    {
#  if (ETHTSYN_MESSAGE_COMPLIANCE == STD_OFF)
      uint8 subTlvCntDummy = 0u;
#  endif /* (ETHTSYN_MESSAGE_COMPLIANCE == STD_OFF) */

      /* #30 Check validity of potential AR Sub-TLVs (if message compliance is disabled). */
#  if (ETHTSYN_MESSAGE_COMPLIANCE == STD_OFF)
      if(EthTSyn_SlaveRx_CheckArSubTlvsAndGetCnt(PortIdx, rcvdMsgPtr, &subTlvCntDummy) == E_OK)
#  endif /* (ETHTSYN_MESSAGE_COMPLIANCE == STD_OFF) */
      {
        const EthTSyn_IntTimeDomainIdxType timeDomainIdx = EthTSyn_GetTimeDomainIdxOfPort(PortIdx);
        ETHTSYN_CONSTP2VAR(EthTSyn_SyncReceiveSmType) syncReceiveSmPtr = EthTSyn_GetAddrSyncReceiveSm(slavePortIdx);

        ETHTSYN_ENTER_CRITICAL_SECTION_0();

        /* #40 Store message attributes. */
        syncReceiveSmPtr->FollowUp.SequenceId = IpBase_GetUint16(rcvdMsgPtr, ETHTSYN_MSG_HDR_SEQUENCE_ID_OFS);

        syncReceiveSmPtr->State = ETHTSYN_S_SYNC_RCV_SM_WAIT_SYNC;

        ETHTSYN_LEAVE_CRITICAL_SECTION_0();

        /* #50 Trigger provision of timestamp information for synchronization of switch if required. */
#  if (ETHTSYN_SWT_TIME_SYNC_SUPPORT == STD_ON)
        if(EthTSyn_SwtTimeSync_IsTimeDomainUsedForSwtSync(timeDomainIdx) == TRUE)
        {
          EthTSyn_SwtTimeSync_ProvideTimestampsFromSwtSlavePort(slavePortIdx, rcvdMsgPtr);
        }
#  endif /* (ETHTSYN_SWT_TIME_SYNC_SUPPORT == STD_ON) */

        /* #60 Handle SiteSyncSyncSm (if bridge mode is set to TRANSPARENT_CLOCK). */
#  if (ETHTSYN_SWT_MGMT_BRIDGE_MODE == ETHTSYN_SWT_MGMT_BRIDGE_MODE_TRANSPARENT)
        EthTSyn_SwtMgmt_SiteSyncSync_RcvdFup(PortIdx, RxBufIdx);
#  endif /* (ETHTSYN_SWT_MGMT_BRIDGE_MODE == ETHTSYN_SWT_MGMT_BRIDGE_MODE_TRANSPARENT) */

        /* #70 Forward FollowUp to End-Station if applicable. */
        EthTSyn_SwtMgmt_Rx_FwdFupMsgToEndStation(timeDomainIdx, RxBufIdx);
      }
    }
  } /* END: if(IsSlavePort) */

} /* EthTSyn_SwtMgmt_Rx_ProcRcvdFupMsg() */
# endif /* (ETHTSYN_SLAVE_SUPPORT == STD_ON) */

# if (ETHTSYN_ANNOUNCE_RX_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_Rx_ProcRcvdAnnounceMsg
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
/* PRQA S 6050 1 */ /* MD_EthTSyn_6050_CslAccess */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_Rx_ProcRcvdAnnounceMsg(
  EthTSyn_IntPortIdxType       PortIdx,
  EthTSyn_SwtMgmtRxBufIterType RxBufIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  const EthTSyn_SwtMgmtRcvdMsgBufStartIdxOfSwtMgmtRxBufCfgType rcvdMsgBufStartIdx =
    EthTSyn_GetSwtMgmtRcvdMsgBufStartIdxOfSwtMgmtRxBufCfg(RxBufIdx);
  ETHTSYN_P2CONST(uint8) rcvdMsgPtr = EthTSyn_GetAddrSwtMgmtRcvdMsgBuf(rcvdMsgBufStartIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if port is ready to receive announce message. */
  if(EthTSyn_UtilRx_IsPortReadyToReceiveAnnounce(PortIdx) == TRUE)
  {
    /* #20 Check for valid Announce message. */
    if(EthTSyn_UtilRx_QualifyAnnounceMsg(rcvdMsgPtr, PortIdx) == E_OK)
    {
      const EthTSyn_SlavePortIdxOfPortType slavePortIdx = EthTSyn_GetSlavePortIdxOfPort(PortIdx);
      /*@ assert slavePortIdx < EthTSyn_GetSizeOfSlavePort(); */                                                       /* VCA_ETHTSYN_IS_READY_TO_RCV_ANNOUNCE_CSL03 */
      const EthTSyn_AnnounceInfoIdxOfSlavePortType announceInfoIdx =
        EthTSyn_GetAnnounceInfoIdxOfSlavePort(slavePortIdx);
      /*@ assert announceInfoIdx < EthTSyn_GetSizeOfAnnounceInfo(); */                                                 /* VCA_ETHTSYN_IS_READY_TO_RCV_ANNOUNCE_CSL03 */
      const EthTSyn_TimeDomainIdxOfPortType timeDomainIdx = EthTSyn_GetTimeDomainIdxOfPort(PortIdx);
      ETHTSYN_CONSTP2VAR(EthTSyn_AnnounceReceiveSmType) announceRcvSmPtr =
        EthTSyn_GetAddrAnnounceReceiveSm(announceInfoIdx);

      /* reset announce timeout counter */
      announceRcvSmPtr->RxTimeoutCnt = EthTSyn_GetAnnounceAllowedRxDelayOfAnnounceInfo(announceInfoIdx);
      /* check if no Grandmaster is available */
      if(EthTSyn_IsGmPresentOfSystemState(timeDomainIdx) == FALSE)
      {
        EthTSyn_Slave_SetMasterPriorityVector(rcvdMsgPtr, timeDomainIdx);
      }
    }
  }
} /* EthTSyn_SwtMgmt_Rx_ProcRcvdAnnounceMsg() */
# endif /* (ETHTSYN_ANNOUNCE_RX_SUPPORT == STD_ON) */

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_Rx_PerformBasicMsgChecksAndGetRxBufIdx
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
 */
ETHTSYN_LOCAL_INLINE FUNC(uint8, ETHTSYN_CODE) EthTSyn_SwtMgmt_Rx_PerformBasicMsgChecksAndGetRxBufIdx(
                  uint16 LenByte,
  ETHTSYN_P2CONST(uint8) DataPtr,
    ETHTSYN_P2VAR(uint8) ErrorIdPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 freeRxBufIdx = EthTSyn_GetSizeOfSwtMgmtRxBuf();
  uint8 errorId;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Perform general message checks. */
  errorId = EthTSyn_UtilRx_CheckMessageGeneral(DataPtr, LenByte);

  /* #20 If general message checks where passed. */
  if(errorId == ETHTSYN_E_NO_ERROR)
  {
    /* #200 Check message type and length. */
    errorId = EthTSyn_UtilRx_CheckMessageTypeAndLength(DataPtr, LenByte);

    /* #201 If message type and length check was passed. */
    if(errorId == ETHTSYN_E_NO_ERROR)
    {
      /* #2010 Get and lock the next free Rx buffer. */
      freeRxBufIdx = EthTSyn_SwtMgmt_RxBufHndl_GetFreeIdx();

      /* #2011 If Rx buffer is available. */
      if(freeRxBufIdx < EthTSyn_GetSizeOfSwtMgmtRxBuf())
      {
        /* #20110 Check if Rx buffer is big enough to hold the received message. */
        if(LenByte <= EthTSyn_GetSwtMgmtRcvdMsgBufLengthOfSwtMgmtRxBufCfg(freeRxBufIdx))
        {
          /* #201010 Lock the Rx buffer and return its index. */
          EthTSyn_SetStateOfSwtMgmtRxBuf(freeRxBufIdx, ETHTSYN_LOCKED_STATEOFSWTMGMTRXBUF);
        }
        /* #20111 Otherwise. */
        else
        {
          /* #201110 Drop the message, release the buffer and set errorId to
           *         ETHTSYN_SWT_MGMT_E_MSG_BUFFER_PAYLOAD_OVERFLOW. */
          EthTSyn_SetStateOfSwtMgmtRxBuf(freeRxBufIdx, ETHTSYN_RELEASE_STATEOFSWTMGMTRXBUF);
          freeRxBufIdx = EthTSyn_GetSizeOfSwtMgmtRxBuf();
          errorId = ETHTSYN_SWT_MGMT_E_MSG_BUFFER_PAYLOAD_OVERFLOW;
        }
      }
      /* #2012 Otherwise, drop message and set errorId to ETHTSYN_SWT_MGMT_E_MSG_BUFFER_OVERFLOW. */
      else
      {
        errorId = ETHTSYN_SWT_MGMT_E_MSG_BUFFER_OVERFLOW;
      }
    }
  }

  (*ErrorIdPtr) = errorId;
  return freeRxBufIdx;
} /* EthTSyn_SwtMgmt_Rx_PerformBasicMsgChecksAndGetRxBufIdx() */

# if (ETHTSYN_SLAVE_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_GetEndStationSlavePortIdx
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_IntPortIdxType, ETHTSYN_CODE) EthTSyn_SwtMgmt_GetEndStationSlavePortIdx(
  EthTSyn_IntTimeDomainIdxType TimeDomainIdx)
{
/* ----- Local Variables ---------------------------------------------- */
  EthTSyn_IntPortIdxType slavePortIdx = EthTSyn_GetSizeOfPort();
  EthTSyn_SlavePortIterType slavePortIter;

  /* ----- Implementation ----------------------------------------------- */
  for(slavePortIter = EthTSyn_GetSlavePortStartIdxOfTimeDomain(TimeDomainIdx);
      slavePortIter < EthTSyn_GetSlavePortEndIdxOfTimeDomain(TimeDomainIdx);
      slavePortIter++)
  {
    const EthTSyn_IntPortIdxType tempSlavePortIdx =
      (EthTSyn_IntPortIdxType)EthTSyn_GetPortIdxOfSlavePort(slavePortIter);
    if(EthTSyn_Util_IsEndStationPort(tempSlavePortIdx) == TRUE)
    {
      slavePortIdx = tempSlavePortIdx;
      break;
    }
  }

  return slavePortIdx;
} /* EthTSyn_SwtMgmt_GetEndStationSlavePortIdx() */

#  if (ETHTSYN_SWT_MGMT_BRIDGE_MODE == ETHTSYN_SWT_MGMT_BRIDGE_MODE_TRANSPARENT)
/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_GetPortIdxOfSwitchSlavePort
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_IntSlavePortIdxType, ETHTSYN_CODE) EthTSyn_SwtMgmt_GetSwitchSlavePortIdx(
  EthTSyn_TimeDomainIterType TimeDomainIdx)
{
/* ----- Local Variables ---------------------------------------------- */
  EthTSyn_SlavePortIterType slavePortIter;
  EthTSyn_IntSlavePortIdxType slavePortIdx = EthTSyn_GetSizeOfSlavePort();

  /* ----- Implementation ----------------------------------------------- */
  for(slavePortIter = EthTSyn_GetSlavePortStartIdxOfTimeDomain(TimeDomainIdx);
      slavePortIter < EthTSyn_GetSlavePortEndIdxOfTimeDomain(TimeDomainIdx);
      slavePortIter++)
  {
    /*@ assert slavePortIter < EthTSyn_GetSizeOfSlavePort(); */                                                        /* VCA_ETHTSYN_0_N_IND_CSL03 */
    const EthTSyn_IntPortIdxType tempPortIdx = (EthTSyn_IntPortIdxType)EthTSyn_GetPortIdxOfSlavePort(slavePortIter);
    if(EthTSyn_Util_IsSwitchPort(tempPortIdx) == TRUE)
    {
      slavePortIdx = (EthTSyn_IntSlavePortIdxType)slavePortIter;
      break;
    }
  }

  return slavePortIdx;
} /* EthTSyn_SwtMgmt_GetPortIdxOfSwitchSlavePort() */
#  endif /* (ETHTSYN_SWT_MGMT_BRIDGE_MODE == ETHTSYN_SWT_MGMT_BRIDGE_MODE_TRANSPARENT) */
# endif /* (ETHTSYN_SLAVE_SUPPORT == STD_ON) */

/**********************************************************************************************************************
 *  SITE SYNC SYNC STATE MACHINE
 *********************************************************************************************************************/
# if (ETHTSYN_SITESYNCSYNCSM == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_SiteSyncSync_ChgStateToTxSync
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_SiteSyncSync_ChgStateToTxSync(
  EthTSyn_TimeDomainIterType TimeDomainIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  const EthTSyn_SiteSyncSyncSmIdxOfTimeDomainType siteSyncSyncSmIdx =
    EthTSyn_GetSiteSyncSyncSmIdxOfTimeDomain(TimeDomainIdx);
  /*@ assert siteSyncSyncSmIdx < EthTSyn_GetSizeOfSiteSyncSyncSm(); */                                                 /* VCA_ETHTSYN_INT_FUNC_IDX_PARAM */
  EthTSyn_SiteSyncSyncSmPtrType siteSyncSyncSmPtr = EthTSyn_GetAddrSiteSyncSyncSm(siteSyncSyncSmIdx);
  EthTSyn_MasterPortIterType masterPortIter;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Cancel all pending Sync-Cycles on each master port. */
  for(masterPortIter = EthTSyn_GetMasterPortStartIdxOfTimeDomain(TimeDomainIdx);
      masterPortIter < EthTSyn_GetMasterPortEndIdxOfTimeDomain(TimeDomainIdx);
      masterPortIter++)
  {
    EthTSyn_Master_PortSyncSend_CancelCycle(masterPortIter);
  }

  /* #20 Change state of the site sync sync state machine to TX_SYNC. */
  siteSyncSyncSmPtr->State = ETHTSYN_S_SSS_SM_TX_SYNC;
}

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_SiteSyncSync_HndlPendingState
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
/* PRQA S 6050 1 */ /* MD_EthTSyn_6050_CslAccess */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_SiteSyncSync_HndlPendingState(
    EthTSyn_TimeDomainIterType TimeDomainIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  const EthTSyn_SiteSyncSyncSmIdxOfTimeDomainType siteSyncSyncSmIdx =
    EthTSyn_GetSiteSyncSyncSmIdxOfTimeDomain(TimeDomainIdx);
  /*@ assert siteSyncSyncSmIdx < EthTSyn_GetSizeOfSiteSyncSyncSm(); */                                                 /* VCA_ETHTSYN_INT_FUNC_IDX_PARAM */
  EthTSyn_SiteSyncSyncSmPtrType siteSyncSyncSmPtr = EthTSyn_GetAddrSiteSyncSyncSm(siteSyncSyncSmIdx);

  /* ----- Implementation ----------------------------------------------- */
  ETHTSYN_ENTER_CRITICAL_SECTION_0();
  /* #10 Check if a sync rx timeout occurred. */
  if(siteSyncSyncSmPtr->SyncRxTimeoutDetected == TRUE)
  {
    boolean isAnyPortTxReady = FALSE;
    EthTSyn_MasterPortIterType masterPortIter;
    /* #20 Check if any master port is tx ready. */
    for(masterPortIter = EthTSyn_GetMasterPortStartIdxOfTimeDomain(TimeDomainIdx);
        masterPortIter < EthTSyn_GetMasterPortEndIdxOfTimeDomain(TimeDomainIdx);
        masterPortIter++)
    {
      const EthTSyn_PortIdxOfMasterPortType portIdx = EthTSyn_GetPortIdxOfMasterPort(masterPortIter);
      if(EthTSyn_IsTxReady(portIdx))
      {
        isAnyPortTxReady = TRUE;
        break;
      }
    }

    if(isAnyPortTxReady == TRUE)
    {
      /* #200 Check if the cycle counter for cyclic Sync/FollowUp forwarding in case of a sync rx timeout expired. */
      if(siteSyncSyncSmPtr->SyncTimeoutHndl.CycleCnt == 0u)
      {
        /* #2000 Prepare transmission of a new Sync/FollowUp cycle. */
        siteSyncSyncSmPtr->SyncTimeoutHndl.SequenceId++;
        IpBase_PutUint16(siteSyncSyncSmPtr->RcvdSyncMsgHndl.MsgHndl.RcvdMsg, ETHTSYN_MSG_HDR_SEQUENCE_ID_OFS,
          siteSyncSyncSmPtr->SyncTimeoutHndl.SequenceId);
        siteSyncSyncSmPtr->RcvdSyncMsgHndl.MsgHndl.TxRetryCnt =
          EthTSyn_GetSwtMgmtNumMsgFwdRetryOfTimeDomain(TimeDomainIdx);
        siteSyncSyncSmPtr->RcvdSyncMsgHndl.MsgHndl.TxPendingCnt =
          EthTSyn_GetMasterPortLengthOfTimeDomain(TimeDomainIdx);
        IpBase_PutUint16(siteSyncSyncSmPtr->RcvdFupMsgHndl.MsgHndl.RcvdMsg, ETHTSYN_MSG_HDR_SEQUENCE_ID_OFS,
          siteSyncSyncSmPtr->SyncTimeoutHndl.SequenceId);
        siteSyncSyncSmPtr->RcvdFupMsgHndl.MsgHndl.TxRetryCnt =
          EthTSyn_GetSwtMgmtNumMsgFwdRetryOfTimeDomain(TimeDomainIdx);
        siteSyncSyncSmPtr->RcvdFupMsgHndl.MsgHndl.TxPendingCnt =
          EthTSyn_GetMasterPortLengthOfTimeDomain(TimeDomainIdx);
        siteSyncSyncSmPtr->SyncTimeoutHndl.CycleCnt = siteSyncSyncSmPtr->SyncTimeoutHndl.CycleCntStartVal;

        /* #2001 Change the state of the site sync sync state machine to TX_SYNC. */
        EthTSyn_SwtMgmt_SiteSyncSync_ChgStateToTxSync(TimeDomainIdx);
      }
    }
    /* #30 Otherwise. */
    else
    {
      /* #300 Stop cyclic message 'forwarding' by resetting the sync rx timeout detected flag. */
      siteSyncSyncSmPtr->SyncRxTimeoutDetected = FALSE;
    }
  }
  ETHTSYN_LEAVE_CRITICAL_SECTION_0();
} /* EthTSyn_SwtMgmt_SiteSyncSync_HndlPendingState() */

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_SiteSyncSync_HndlTxSyncState
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_SiteSyncSync_HndlTxSyncState(
  EthTSyn_TimeDomainIterType TimeDomainIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  const EthTSyn_SiteSyncSyncSmIdxOfTimeDomainType siteSyncSyncSmIdx =
    EthTSyn_GetSiteSyncSyncSmIdxOfTimeDomain(TimeDomainIdx);
  /*@ assert siteSyncSyncSmIdx < EthTSyn_GetSizeOfSiteSyncSyncSm(); */                                                 /* VCA_ETHTSYN_INT_FUNC_IDX_PARAM */
  EthTSyn_SiteSyncSyncSmPtrType siteSyncSyncSmPtr = EthTSyn_GetAddrSiteSyncSyncSm(siteSyncSyncSmIdx);
  EthTSyn_MasterPortIterType masterPortIter;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all master Ports. */
  for(masterPortIter = EthTSyn_GetMasterPortStartIdxOfTimeDomain(TimeDomainIdx);
      masterPortIter < EthTSyn_GetMasterPortEndIdxOfTimeDomain(TimeDomainIdx);
      masterPortIter++)
  {
    /* #20 Try to trigger Sync message transmission on the current master port. */
    if(EthTSyn_Master_PortSyncSend_TxSync(masterPortIter, ETHTSYN_MSG_SYNC_LENGTH) == E_OK)
    {
      /* #30 Decrement the Sync TxPending counter in case transmission was triggered successfully. */
      siteSyncSyncSmPtr->RcvdSyncMsgHndl.MsgHndl.TxPendingCnt--;
    }
  } /* END: Iteration of master ports */

  /* #40 Handle the Sync transmission retry mechanism. */
  EthTSyn_SwtMgmt_SiteSyncSync_HndlSyncRetry(TimeDomainIdx);
} /* EthTSyn_SwtMgmt_SiteSyncSync_HndlTxSyncState() */

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_SiteSyncSync_HndlSyncRetry
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
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_SiteSyncSync_HndlSyncRetry(
  EthTSyn_TimeDomainIterType TimeDomainIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  const EthTSyn_SiteSyncSyncSmIdxOfTimeDomainType siteSyncSyncSmIdx =
    EthTSyn_GetSiteSyncSyncSmIdxOfTimeDomain(TimeDomainIdx);
  /*@ assert siteSyncSyncSmIdx < EthTSyn_GetSizeOfSiteSyncSyncSm(); */                                                 /* VCA_ETHTSYN_INT_FUNC_IDX_PARAM */
  EthTSyn_SiteSyncSyncSmPtrType siteSyncSyncSmPtr = EthTSyn_GetAddrSiteSyncSyncSm(siteSyncSyncSmIdx);
  boolean syncRetryTimeout = FALSE;

  /* ----- Implementation ----------------------------------------------- */
  ETHTSYN_ENTER_CRITICAL_SECTION_0();
  /* #10 Decrement the Sync retry counter if possible. */
  if(siteSyncSyncSmPtr->RcvdSyncMsgHndl.MsgHndl.TxRetryCnt > 0u)
  {
    siteSyncSyncSmPtr->RcvdSyncMsgHndl.MsgHndl.TxRetryCnt--;
  }
  /* #20 Otherwise, cancel Sync message transmission retry. */
  else
  {
    syncRetryTimeout = TRUE;
  }

  /* #30 Check if Sync message transmission is done or canceled. */
  if(
    (siteSyncSyncSmPtr->RcvdSyncMsgHndl.MsgHndl.TxPendingCnt == 0u) ||
    (syncRetryTimeout == TRUE)
    )
  {
    /* #40 Change state of the SiteSyncSyncSm to TX_FUP in case FollowUp message transmission is pending. */
    if(siteSyncSyncSmPtr->RcvdFupMsgHndl.MsgHndl.TxPendingCnt > 0u)
    {
      siteSyncSyncSmPtr->RcvdFupMsgHndl.MsgHndl.TxPendingCnt -=
        siteSyncSyncSmPtr->RcvdSyncMsgHndl.MsgHndl.TxPendingCnt;
      siteSyncSyncSmPtr->State = ETHTSYN_S_SSS_SM_TX_FUP;
    }
    /* #50 Otherwise, change the state of the SiteSyncSyncSm to PENDING. */
    else
    {
      siteSyncSyncSmPtr->State = ETHTSYN_S_SSS_SM_PENDING;
    }

    siteSyncSyncSmPtr->RcvdSyncMsgHndl.MsgHndl.TxPendingCnt = 0u;
  }
  ETHTSYN_LEAVE_CRITICAL_SECTION_0();
} /* EthTSyn_SwtMgmt_SiteSyncSync_HndlSyncRetry() */

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_SiteSyncSync_HndlTxFupState
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
/* PRQA S 6050 1 */ /* MD_EthTSyn_6050_CslAccess */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_SiteSyncSync_HndlTxFupState(
  EthTSyn_TimeDomainIterType TimeDomainIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  const EthTSyn_SiteSyncSyncSmIdxOfTimeDomainType siteSyncSyncSmIdx =
    EthTSyn_GetSiteSyncSyncSmIdxOfTimeDomain(TimeDomainIdx);
  /*@ assert siteSyncSyncSmIdx < EthTSyn_GetSizeOfSiteSyncSyncSm(); */                                                 /* VCA_ETHTSYN_INT_FUNC_IDX_PARAM */
  EthTSyn_SiteSyncSyncSmPtrType siteSyncSyncSmPtr = EthTSyn_GetAddrSiteSyncSyncSm(siteSyncSyncSmIdx);
  const uint16 fupMsgLen =
    IpBase_GetUint16(siteSyncSyncSmPtr->RcvdFupMsgHndl.MsgHndl.RcvdMsg, ETHTSYN_MSG_HDR_MSG_LENGTH_OFS);
  EthTSyn_MasterPortIterType masterPortIter;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all master Ports. */
  for(masterPortIter = EthTSyn_GetMasterPortStartIdxOfTimeDomain(TimeDomainIdx);
      masterPortIter < EthTSyn_GetMasterPortEndIdxOfTimeDomain(TimeDomainIdx);
      masterPortIter++)
  {
    /* #20 Try to trigger FollowUp message transmission on the current master port */
    if(EthTSyn_SwtMgmt_SiteSyncSync_TxFupMsg(masterPortIter, fupMsgLen) == E_OK)
    {
      /* #30 Decrement the FollowUp TxPending counter in case transmission was triggered successfully. */
      siteSyncSyncSmPtr->RcvdFupMsgHndl.MsgHndl.TxPendingCnt--;
    }
  }

  /* #40 Handle the FollowUp transmission retry mechanism. */
  EthTSyn_SwtMgmt_SiteSyncSync_HndlFupRetry(TimeDomainIdx);

} /* EthTSyn_SwtMgmt_SiteSyncSync_HndlTxFupState() */

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_SiteSyncSync_HndlFupRetry
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_SiteSyncSync_HndlFupRetry(
  EthTSyn_TimeDomainIterType TimeDomainIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  const EthTSyn_SiteSyncSyncSmIdxOfTimeDomainType siteSyncSyncSmIdx =
    EthTSyn_GetSiteSyncSyncSmIdxOfTimeDomain(TimeDomainIdx);
  /*@ assert siteSyncSyncSmIdx < EthTSyn_GetSizeOfSiteSyncSyncSm(); */                                                 /* VCA_ETHTSYN_INT_FUNC_IDX_PARAM */
  EthTSyn_SiteSyncSyncSmPtrType siteSyncSyncSmPtr = EthTSyn_GetAddrSiteSyncSyncSm(siteSyncSyncSmIdx);

  /* ----- Implementation ----------------------------------------------- */
  ETHTSYN_ENTER_CRITICAL_SECTION_0();
  /* #10 Decrement the FollowUp retry counter if possible. */
  if(siteSyncSyncSmPtr->RcvdFupMsgHndl.MsgHndl.TxRetryCnt > 0u)
  {
    siteSyncSyncSmPtr->RcvdFupMsgHndl.MsgHndl.TxRetryCnt--;
  }
  /* #20 Otherwise, cancel FollowUp message transmission retry. */
  else
  {
    siteSyncSyncSmPtr->RcvdFupMsgHndl.MsgHndl.TxPendingCnt = 0u;
  }

  /* #30 Check if FollowUp message transmission is done or canceled. */
  if(siteSyncSyncSmPtr->RcvdFupMsgHndl.MsgHndl.TxPendingCnt == 0u)
  {
    /* #40 Change the state of the SiteSyncSyncSm to PENDING. */
    siteSyncSyncSmPtr->State = ETHTSYN_S_SSS_SM_PENDING;
  }
  ETHTSYN_LEAVE_CRITICAL_SECTION_0();
} /* EthTSyn_SwtMgmt_SiteSyncSync_HndlFupRetry() */

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_SiteSyncSync_HndlRcvdFupAfterTimeoutState
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_SiteSyncSync_HndlRcvdFupAfterTimeoutState(
  EthTSyn_TimeDomainIterType TimeDomainIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  const EthTSyn_SiteSyncSyncSmIdxOfTimeDomainType siteSyncSyncSmIdx =
    EthTSyn_GetSiteSyncSyncSmIdxOfTimeDomain(TimeDomainIdx);
  /*@ assert siteSyncSyncSmIdx < EthTSyn_GetSizeOfSiteSyncSyncSm(); */                                                 /* VCA_ETHTSYN_INT_FUNC_IDX_PARAM */
  ETHTSYN_CONSTP2VAR(EthTSyn_SiteSyncSyncSmType) siteSyncSyncSmPtr = EthTSyn_GetAddrSiteSyncSyncSm(siteSyncSyncSmIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 FollowUp received after a sync timeout was detected. Reset the sync rx timeout detected flag. */
  siteSyncSyncSmPtr->SyncRxTimeoutDetected = FALSE;

  /* #20 Change state of the SiteSyncSyncSm to PENDING. */
  siteSyncSyncSmPtr->State = ETHTSYN_S_SSS_SM_PENDING;

} /* EthTSyn_SwtMgmt_SiteSyncSync_HndlRcvdFupAfterTimeoutState() */

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_SiteSyncSync_GetSyncCycleFromSyncMsg
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
ETHTSYN_LOCAL_INLINE FUNC(uint32, ETHTSYN_CODE) EthTSyn_SwtMgmt_SiteSyncSync_GetSyncCycleFromSyncMsg(
  ETHTSYN_P2CONST(uint8) SyncMsgPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  float64 syncCycleMf;
  float64 syncCycleSeconds = 1.0;
  sint8 logMsgInterval = (sint8)IpBase_GetUint8(SyncMsgPtr, ETHTSYN_MSG_HDR_LOG_MSG_INTERVAL_OFS);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 If the log message interval is zero. */
  if(logMsgInterval == 0)
  {
    /* #100 The cycle time is 1 second. */
  }
  /* #20 Otherwise. */
  else
  {
    float64 syncCycleBase;
    uint8 syncCycleExponent;
    uint8_least iter;

    /* #30 If the log message interval is negative. */
    if(logMsgInterval < 0)
    {
      /* #300 Use 1/2 as base and the absolute value of the log message interval as exponent for the cycle
       *      calculation. */
      syncCycleBase = 0.5;
      syncCycleExponent = (uint8)(-logMsgInterval);
    }
    /* #40 Otherwise, the log message interval is positive. */
    else
    {
      /* #400 Use 2 as base and the log message interval as exponent for the cycle calculation. */
      syncCycleBase = 2.0;
      syncCycleExponent = (uint8)logMsgInterval;
    }

    /* #50 Calculate the sync cycle time in seconds. */
    for(iter = 0; iter < syncCycleExponent; iter++)
    {
      syncCycleSeconds *= syncCycleBase;
    }
  }

  /* #60 Convert the cycle time into main function cycles. */
  syncCycleMf = syncCycleSeconds * (float64)ETHTSYN_SWT_MGMT_MS_PER_S;
  syncCycleMf /= (float64)ETHTSYN_MAIN_FUNCTION_CYCLE;
  syncCycleMf += 0.5; /* +0.5 for correct rounding. */

  return (uint32)syncCycleMf;
} /* EthTSyn_SwtMgmt_SiteSyncSync_GetSyncCycleFromSyncMsg() */

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_SiteSyncSync_RcvdSync
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
 */
/* PRQA S 6050 1 */ /* MD_EthTSyn_6050_CslAccess */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_SiteSyncSync_RcvdSync(
  EthTSyn_IntPortIdxType       PortIdx,
  EthTSyn_SwtMgmtRxBufIterType RxBufIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  const EthTSyn_IntTimeDomainIdxType timeDomainIdx = EthTSyn_GetTimeDomainIdxOfPort(PortIdx);
  const EthTSyn_SiteSyncSyncSmIdxOfTimeDomainType siteSyncSyncSmIdx =
    EthTSyn_GetSiteSyncSyncSmIdxOfTimeDomain(timeDomainIdx);
  const EthTSyn_SwtMgmtRcvdMsgBufStartIdxOfSwtMgmtRxBufCfgType rcvdMsgBufStartIdx =
    EthTSyn_GetSwtMgmtRcvdMsgBufStartIdxOfSwtMgmtRxBufCfg(RxBufIdx);
  ETHTSYN_P2CONST(uint8) rcvdMsgPtr = EthTSyn_GetAddrSwtMgmtRcvdMsgBuf(rcvdMsgBufStartIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 If site sync sync state machine is used. */
  if(siteSyncSyncSmIdx < EthTSyn_GetSizeOfSiteSyncSyncSm())
  {
    ETHTSYN_CONSTP2VAR(EthTSyn_SiteSyncSyncSmType) siteSyncSyncSmPtr =
      EthTSyn_GetAddrSiteSyncSyncSm(siteSyncSyncSmIdx);
    const uint16 rxSequenceId = IpBase_GetUint16(rcvdMsgPtr, ETHTSYN_MSG_HDR_SEQUENCE_ID_OFS);

    ETHTSYN_ENTER_CRITICAL_SECTION_0();
    /* #20 If a sync rx timeout was detected. */
    if(siteSyncSyncSmPtr->SyncRxTimeoutDetected == TRUE)
    {
      /* #200 Change state of the site sync sync state machine to RCVD_SYNC_AFTER_TIMEOUT and reset the sync message
       *      tx pending counter. */
      siteSyncSyncSmPtr->State = ETHTSYN_S_SSS_SM_RCVD_SYNC_AFTER_TIMEOUT;
      siteSyncSyncSmPtr->RcvdSyncMsgHndl.MsgHndl.TxPendingCnt = 0u;
      siteSyncSyncSmPtr->RcvdFupMsgHndl.MsgHndl.TxPendingCnt = 0u;
    }
    /* #30 Otherwise. */
    else
    {
      /* #300 Store the timestamps and required sync information in the site sync sync state machine for later
       *      calculation of residence time. */
#  if (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON)
      {
        const EthTSyn_SwtMgmtMgmtObjHndlIdxOfSwtMgmtRxBufCfgType mgmtObjHndlIdx =
          EthTSyn_GetSwtMgmtMgmtObjHndlIdxOfSwtMgmtRxBufCfg(RxBufIdx);

        siteSyncSyncSmPtr->RcvdSyncMsgHndl.SwtIngressTsMgmt =
          EthTSyn_GetSwtIngressTsMgmtOfSwtMgmtMgmtObjHndl(mgmtObjHndlIdx);
        siteSyncSyncSmPtr->RcvdSyncMsgHndl.SwtHostPortEgressTsMgmt =
          EthTSyn_GetSwtEgressTsMgmtOfSwtMgmtMgmtObjHndl(mgmtObjHndlIdx);
      }
#  else
      siteSyncSyncSmPtr->RcvdSyncMsgHndl.HostIngressIntVltMgmt =
        EthTSyn_GetHostIngressIntVltMgmtOfSwtMgmtRxBuf(RxBufIdx);
#  endif /* (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_OFF) */

      siteSyncSyncSmPtr->RcvdSyncMsgHndl.SlavePortPdelay = EthTSyn_Pdelay_GetCurrentPdelay(PortIdx);

      /* #301 Copy Message to SiteSyncSync Sync Message Buffer. */
      /*Hint: add the following VCA assertion when MOLE-1185 is released and adapt justification for call of MymCpy:
       * assert $lengthOf(siteSyncSyncSmPtr->RcvdSyncMsgHndl.MsgHndl.RcvdMsg) >= ETHTSYN_SWT_MGMT_RX_MSG_BUFFER_SIZE; */
      /* PRQA S 0315 2 */ /* MD_MSR_VStdLibCopy */
      VStdLib_MemCpy(siteSyncSyncSmPtr->RcvdSyncMsgHndl.MsgHndl.RcvdMsg, rcvdMsgPtr,                                   /* VCA_ETHTSYN_SWT_MGMT_RX_BUF_MEM_CPY */
        ETHTSYN_SWT_MGMT_RX_MSG_BUFFER_SIZE);
      siteSyncSyncSmPtr->RcvdSyncMsgHndl.MsgHndl.RcvdMsgSequenceId = rxSequenceId;

      /* #302 Set pending sync transmission of the SiteSyncSync state machine. */
      siteSyncSyncSmPtr->RcvdSyncMsgHndl.MsgHndl.TxPendingCnt = EthTSyn_GetMasterPortLengthOfTimeDomain(timeDomainIdx);
      siteSyncSyncSmPtr->RcvdSyncMsgHndl.MsgHndl.TxRetryCnt =
        EthTSyn_GetSwtMgmtNumMsgFwdRetryOfTimeDomain(timeDomainIdx);

      /* #303 Reset the Fup pending counter to suppress transmission of former delayed Fup messages. */
      siteSyncSyncSmPtr->RcvdFupMsgHndl.MsgHndl.TxPendingCnt = 0u;

      /* #304 Change SiteSyncSyncSm state to TX_SYNC. */
      EthTSyn_SwtMgmt_SiteSyncSync_ChgStateToTxSync(timeDomainIdx);
    }
    ETHTSYN_LEAVE_CRITICAL_SECTION_0();
  }
} /* EthTSyn_SwtMgmt_SiteSyncSync_RcvdSync() */

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_SiteSyncSync_RcvdFup
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
 */
/* PRQA S 6050 1 */ /* MD_EthTSyn_6050_CslAccess */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_SiteSyncSync_RcvdFup(
  EthTSyn_IntPortIdxType       PortIdx,
  EthTSyn_SwtMgmtRxBufIterType RxBufIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  const EthTSyn_IntTimeDomainIdxType timeDomainIdx = EthTSyn_GetTimeDomainIdxOfPort(PortIdx);
  const EthTSyn_SiteSyncSyncSmIdxOfTimeDomainType siteSyncSyncSmIdx =
    EthTSyn_GetSiteSyncSyncSmIdxOfTimeDomain(timeDomainIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 If site sync sync state machine is used. */
  if(siteSyncSyncSmIdx < EthTSyn_GetSizeOfSiteSyncSyncSm())
  {
    ETHTSYN_CONSTP2VAR(EthTSyn_SiteSyncSyncSmType) siteSyncSyncSmPtr =
      EthTSyn_GetAddrSiteSyncSyncSm(siteSyncSyncSmIdx);

    /* #20 Copy FollowUp message to SiteSyncSync state machine. */
    if(siteSyncSyncSmPtr->SyncRxTimeoutDetected == FALSE)
    {
      const EthTSyn_SwtMgmtRcvdMsgBufStartIdxOfSwtMgmtRxBufCfgType rcvdMsgBufStartIdx =
        EthTSyn_GetSwtMgmtRcvdMsgBufStartIdxOfSwtMgmtRxBufCfg(RxBufIdx);
      ETHTSYN_P2CONST(uint8) rcvdMsgPtr = EthTSyn_GetAddrSwtMgmtRcvdMsgBuf(rcvdMsgBufStartIdx);

      /*Hint: add the following VCA assertion when MOLE-1185 is released and adapt justification for call of MymCpy:
       * assert $lengthOf(siteSyncSyncSmPtr->RcvdFupMsgHndl.MsgHndl.RcvdMsg) >= ETHTSYN_SWT_MGMT_RX_MSG_BUFFER_SIZE; */
      VStdLib_MemCpy(siteSyncSyncSmPtr->RcvdFupMsgHndl.MsgHndl.RcvdMsg, rcvdMsgPtr, /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */ /* VCA_ETHTSYN_SWT_MGMT_RX_BUF_MEM_CPY */
        ETHTSYN_SWT_MGMT_RX_MSG_BUFFER_SIZE);
      siteSyncSyncSmPtr->RcvdFupMsgHndl.MsgHndl.RcvdMsgSequenceId =
        IpBase_GetUint16(rcvdMsgPtr, ETHTSYN_MSG_HDR_SEQUENCE_ID_OFS);
      siteSyncSyncSmPtr->RcvdFupMsgHndl.MsgHndl.TxPendingCnt = EthTSyn_GetMasterPortLengthOfTimeDomain(timeDomainIdx);
      siteSyncSyncSmPtr->RcvdFupMsgHndl.MsgHndl.TxRetryCnt =
        EthTSyn_GetSwtMgmtNumMsgFwdRetryOfTimeDomain(timeDomainIdx);

      /* PRQA S 0315 2 */ /* MD_MSR_VStdLibCopy */
      VStdLib_MemCpy(&siteSyncSyncSmPtr->SyncTimeoutHndl.LastValidRcvdSync,                                            /* VCA_ETHTSYN_MEM_CPY_SIZE_OF */
        &siteSyncSyncSmPtr->RcvdSyncMsgHndl, sizeof(EthTSyn_SiteSyncSyncSmRcvdSyncMsgHndlType));

# if (ETHTSYN_MESSAGE_COMPLIANCE == STD_OFF)
      EthTSyn_SwtMgmt_SiteSyncSync_SetFupTimeSecuredTlvInfo(PortIdx, rcvdMsgPtr);
# endif /* (ETHTSYN_MESSAGE_COMPLIANCE == STD_OFF) */
    }

    switch(siteSyncSyncSmPtr->State)
    {
      /* #400 If current state of SiteSyncSyncSm is PENDING. */
    case ETHTSYN_S_SSS_SM_PENDING:
      {
        /* #4000 Change state of SiteSyncSyncSm to ETHTSYN_S_SSS_SM_TX_FUP. */
        siteSyncSyncSmPtr->State = ETHTSYN_S_SSS_SM_TX_FUP;
        break;
      }

      /* #401 If current state of SiteSyncSyncSm is RCVD_SYNC_AFTER_TIMEOUT. */
    case ETHTSYN_S_SSS_SM_RCVD_SYNC_AFTER_TIMEOUT:
      {
        /* #4010 Handle FollowUp reception after Sync timeout and don't forward the received FollowUp message. */
        ETHTSYN_ENTER_CRITICAL_SECTION_0();
        EthTSyn_SwtMgmt_SiteSyncSync_HndlRcvdFupAfterTimeoutState(timeDomainIdx);
        siteSyncSyncSmPtr->RcvdFupMsgHndl.MsgHndl.TxPendingCnt = 0u;
        ETHTSYN_LEAVE_CRITICAL_SECTION_0();

        break;
      }

      /* #402 Otherwise, do nothing. */
    default:
      {
        /* Nothing to do here. */
        break;
      }
    }
  }
} /* EthTSyn_SwtMgmt_SiteSyncSync_RcvdFup() */

# if (ETHTSYN_MESSAGE_COMPLIANCE == STD_OFF)
/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_SiteSyncSync_SetFupTimeSecuredTlvInfo
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_SiteSyncSync_SetFupTimeSecuredTlvInfo(
                  EthTSyn_IntPortIdxType PortIdx,
  ETHTSYN_P2CONST(uint8)                 RcvdFupMsgPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint16 timeSecuredTlvStartIdx;
  uint16 fupMsgLen = IpBase_GetUint16(RcvdFupMsgPtr, ETHTSYN_MSG_HDR_MSG_LENGTH_OFS);
  EthTSyn_TimeDomainIdxOfPortType timeDomainIdx = EthTSyn_GetTimeDomainIdxOfPort(PortIdx);
  EthTSyn_SiteSyncSyncSmIdxOfTimeDomainType siteSyncSyncSmIdx =
    EthTSyn_GetSiteSyncSyncSmIdxOfTimeDomain(timeDomainIdx);
  /*@ assert siteSyncSyncSmIdx < EthTSyn_GetSizeOfSiteSyncSyncSm(); */                                                 /* VCA_ETHTSYN_INT_FUNC_IDX_PARAM */
  ETHTSYN_P2VAR(EthTSyn_SiteSyncSyncSmType) siteSyncSyncSmPtr = EthTSyn_GetAddrSiteSyncSyncSm(siteSyncSyncSmIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if a time secured AR-TLV is included in the received FollowUp message. */
  timeSecuredTlvStartIdx = EthTSyn_SwtMgmt_SiteSyncSync_GetTimeSecuredSubTlvStartIdx(RcvdFupMsgPtr, fupMsgLen);

  if(timeSecuredTlvStartIdx < fupMsgLen)
  {
    boolean isCrcValid;
    uint8 dataId;

    /* #100 Validate the CRC of the time secured AR-TLV. */
    dataId = EthTSyn_Util_GetFollowUpDataIdListEntry(timeDomainIdx,
      IpBase_GetUint16(RcvdFupMsgPtr, ETHTSYN_MSG_HDR_SEQUENCE_ID_OFS));
    isCrcValid = EthTSyn_Crc_ValidateSubTlvCrc(dataId, RcvdFupMsgPtr, timeSecuredTlvStartIdx);

    /* #101 Mark the TimeSecured TLV as included and store information about its start index and CRC validity in the
     *      SiteSyncSyncSm. */
    siteSyncSyncSmPtr->RcvdFupMsgHndl.TimeSecuredTlvInfo.IsTimeTlvCrcValid = isCrcValid;
    siteSyncSyncSmPtr->RcvdFupMsgHndl.TimeSecuredTlvInfo.TimeSecuredTlvStartIndex = timeSecuredTlvStartIdx;
    siteSyncSyncSmPtr->RcvdFupMsgHndl.TimeSecuredTlvInfo.IsTimeTlvIncluded = TRUE;
  }
  /* #20 Otherwise, mark TimeSecured TLV as not included in the SiteSyncSyncSm. */
  else
  {
    siteSyncSyncSmPtr->RcvdFupMsgHndl.TimeSecuredTlvInfo.IsTimeTlvIncluded = FALSE;
  }
} /* EthTSyn_SwtMgmt_SiteSyncSync_SetFupTimeSecuredTlvInfo() */
# endif /* (ETHTSYN_MESSAGE_COMPLIANCE == STD_OFF) */

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_SiteSyncSync_TxFupMsg
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_SwtMgmt_SiteSyncSync_TxFupMsg(
  EthTSyn_MasterPortIterType MasterPortIdx,
  uint16                     FupMsgLen)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK; /* PRQA S 2981 */ /* MD_EthTSyn_2981_RedundantInit */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if the Sync egress timestamp is ready for processing (if switch timestamping is used). */
#  if (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON)
  if(EthTSyn_Master_PortSyncSend_IsSyncSwtEgrTsReadyToProc(MasterPortIdx) == TRUE)
#  endif /* (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON) */
  {
    /* #20 Trigger FollowUp message transmission. */
    retVal = EthTSyn_Master_PortSyncSend_TxFup(MasterPortIdx, FupMsgLen);
  }

  return retVal;
} /* EthTSyn_SwtMgmt_SiteSyncSync_TxFupMsg() */

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_SiteSyncSync_CalcAndSetFupCorrField
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
 */
/* PRQA S 6050 1 */ /* MD_EthTSyn_6050_CslAccess */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_SiteSyncSync_CalcAndSetFupCorrField(
                EthTSyn_PortIdxOfMasterPortType  PortIdx,
  ETHTSYN_P2VAR(uint8)                           TxBufPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthTSyn_TimediffType swtResidenceTimeNs = 0; /* PRQA S 2981 */ /* MD_EthTSyn_2981_RedundantInit */
  const EthTSyn_TimeDomainIdxOfPortType timeDomainIdx = EthTSyn_GetTimeDomainIdxOfPort(PortIdx);
  const EthTSyn_SiteSyncSyncSmIdxOfTimeDomainType siteSyncSyncSmIdx =
    EthTSyn_GetSiteSyncSyncSmIdxOfTimeDomain(timeDomainIdx);

  /* ----- Implementation ----------------------------------------------- */
  if(siteSyncSyncSmIdx < EthTSyn_GetSizeOfSiteSyncSyncSm())
  {
    ETHTSYN_CONSTP2CONST(EthTSyn_SiteSyncSyncSmType) siteSyncSyncSmPtr =
      EthTSyn_GetAddrSiteSyncSyncSm(siteSyncSyncSmIdx);
#  if (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON)
  const EthTSyn_MasterPortIdxOfPortType masterPortIdx = EthTSyn_GetMasterPortIdxOfPort(PortIdx);
    EthTSyn_TsMgmtStructType syncEgrTsMgmt;

    /* #10 Switch timestamping. Check if sync ingress and egress timestamps are available. */
    syncEgrTsMgmt = EthTSyn_Master_PortSyncSend_GetSyncSwtEgrTsMgmt(masterPortIdx);
    if(
      (siteSyncSyncSmPtr->RcvdSyncMsgHndl.SwtIngressTsMgmt.State == ETHTSYN_TS_S_AVAILABLE) &&
      (syncEgrTsMgmt.State == ETHTSYN_TS_S_AVAILABLE)
      )
    {
      /* #100 Sync egress timestamp available. Compute switch residence time of the sync message. */
      if(EthTSyn_Util_TimestampMinusTimestamp(&syncEgrTsMgmt.Ts,
        &siteSyncSyncSmPtr->RcvdSyncMsgHndl.SwtIngressTsMgmt.Ts, &swtResidenceTimeNs) != E_OK)
      {
        /* #1000 Failed to compute switch residence time. Use default value. */
        swtResidenceTimeNs = (EthTSyn_TimediffType)
          (ETHTSYN_SWT_RX_TO_UPLINK_RESIDENCE_TIME_NS + ETHTSYN_SWT_UPLINK_TO_TX_RESIDENCE_TIME_NS);
      }
    }
    else
    {
      /* #101 Sync egress timestamp not available. Use default value for residence time. */
      swtResidenceTimeNs = (EthTSyn_TimediffType)
        (ETHTSYN_SWT_RX_TO_UPLINK_RESIDENCE_TIME_NS + ETHTSYN_SWT_UPLINK_TO_TX_RESIDENCE_TIME_NS);
    }
#  else
    /* #20 No Switch timestamping. Use the SW residence time of the sync message. */
    {
      swtResidenceTimeNs = EthTSyn_SwtMgmt_SiteSyncSync_CalcSyncSwResTime(PortIdx);
    }
#  endif /* (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON) */
    {
      EthTSyn_TimediffType followUpCorrectionFieldNs;

      /*
                    +----------+      Sync         +--------------------+ Sync
                    |  Master  +------------------>+S||    Bridge    ||M+--------->
                    +----------+t1               t2+--------------------+t3
                               +  Pdelay (t2-t1)   + Residence (t3-t2)  +
                               +<----------------->-<------------------>+
                               +                   +                    +
       */

      /* #30 Get the FollowUpCorrectionValue of the original FollowUp message. */
      followUpCorrectionFieldNs =
        (EthTSyn_TimediffType)IpBase_GetUint48(TxBufPtr, ETHTSYN_MSG_HDR_CORR_FIELD_OFS);

       /* #40 Add the Pdelay to the correction field. */
      followUpCorrectionFieldNs += (EthTSyn_TimediffType)siteSyncSyncSmPtr->RcvdSyncMsgHndl.SlavePortPdelay;

      /* #50 Check if the switch residence time is plausible and needs to be added to the FollowUp correction field
       *     (i.e. > 0). */
      if(swtResidenceTimeNs > 0)
      {
        /* #500 Add the switch residence time to the correction field. */
        followUpCorrectionFieldNs += swtResidenceTimeNs;
      }

      /* #70 Write the FollowUp correction field within the forwarded FollowUp message. */
      /* Multiply FollowUpCorrectionField by 2^16 (as specified by IEEE802.1AS) and copy it to the TxBuffer */
      IpBase_PutUint48(TxBufPtr, ETHTSYN_MSG_HDR_CORR_FIELD_OFS, (uint64)followUpCorrectionFieldNs);
    }
  }
} /* EthTSyn_SwtMgmt_SiteSyncSync_CalcAndSetFupCorrField() */

#  if (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_OFF)
/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_SiteSyncSync_CalcSyncSwResTime
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_TimediffType, ETHTSYN_CODE) EthTSyn_SwtMgmt_SiteSyncSync_CalcSyncSwResTime(
  EthTSyn_IntPortIdxType PortIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  const EthTSyn_TimeDomainIdxOfPortType timeDomainIdx = EthTSyn_GetTimeDomainIdxOfPort(PortIdx);
  const EthTSyn_MasterPortIdxOfPortType masterPortIdx = EthTSyn_GetMasterPortIdxOfPort(PortIdx);
  /*@ assert masterPortIdx < EthTSyn_GetSizeOfMasterPort(); */                                                         /* VCA_ETHTSYN_INT_FUNC_IDX_PARAM */
  const EthTSyn_SiteSyncSyncSmIdxOfTimeDomainType siteSyncSyncSmIdx =
    EthTSyn_GetSiteSyncSyncSmIdxOfTimeDomain(timeDomainIdx);
  /*@ assert siteSyncSyncSmIdx < EthTSyn_GetSizeOfSiteSyncSyncSm(); */                                                 /* VCA_ETHTSYN_INT_FUNC_IDX_PARAM */
  ETHTSYN_CONSTP2CONST(EthTSyn_SiteSyncSyncSmType) siteSyncSyncSmPtr =
    EthTSyn_GetAddrSiteSyncSyncSm(siteSyncSyncSmIdx);
  EthTSyn_TimediffType swtSwResidenceTime = 0;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if Sync ingress timestamp is available. */
  if(siteSyncSyncSmPtr->RcvdSyncMsgHndl.HostIngressIntVltMgmt.IntVltValid == TRUE)
  {
    EthTSyn_IntVltMgmtType hostEgrIntVltMgmt;

    /* #20 Check if Sync egress timestamp is available. */
    hostEgrIntVltMgmt = EthTSyn_Master_PortSyncSend_GetSyncHostEgrIntVltMgmt(masterPortIdx);
    if(hostEgrIntVltMgmt.IntVltValid == TRUE)
    {
      /* #30 Calculate the Sync SW residence time. */
      EthTSyn_TimediffType syncSwResTimeTemp = ((EthTSyn_TimediffType)hostEgrIntVltMgmt.IntVlt -
        (EthTSyn_TimediffType)siteSyncSyncSmPtr->RcvdSyncMsgHndl.HostIngressIntVltMgmt.IntVlt);

      /* #40 Perform sanity check of the calculated residence time (has to be greater 0). */
      if(syncSwResTimeTemp > 0)
      {
        swtSwResidenceTime = syncSwResTimeTemp;
      }
    }
  }

  return swtSwResidenceTime;
} /* EthTSyn_SwtMgmt_SiteSyncSync_CalcSyncSwResTime() */
#  endif /* (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_OFF) */

#  if (ETHTSYN_MESSAGE_COMPLIANCE == STD_OFF)
/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_SiteSyncSync_UpdateTimeSecuredSubTlvCrc
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
/* PRQA S 6050 1 */ /* MD_EthTSyn_6050_IpBase */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_SiteSyncSync_UpdateTimeSecuredSubTlvCrc(
                EthTSyn_PortIdxOfMasterPortType PortIdx,
  ETHTSYN_P2VAR(uint8)                          FupTxBufPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthTSyn_TimeDomainIdxOfPortType timeDomainIdx = EthTSyn_GetTimeDomainIdxOfPort(PortIdx);
  EthTSyn_SiteSyncSyncSmIdxOfTimeDomainType siteSyncSyncSmIdx =
    EthTSyn_GetSiteSyncSyncSmIdxOfTimeDomain(timeDomainIdx);
  /*@ assert siteSyncSyncSmIdx < EthTSyn_GetSizeOfSiteSyncSyncSm(); */                                                 /* VCA_ETHTSYN_INT_FUNC_IDX_PARAM */
  ETHTSYN_P2CONST(EthTSyn_SiteSyncSyncSmType) siteSyncSyncSmPtr = EthTSyn_GetAddrSiteSyncSyncSm(siteSyncSyncSmIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if a TimeSecured Sub-TLV is included in the former received FollowUp. */
  if(siteSyncSyncSmPtr->RcvdFupMsgHndl.TimeSecuredTlvInfo.IsTimeTlvIncluded == TRUE)
  {
    uint8 crcTimeFlags;
    uint8 dataId;
    uint8 crcTime0;
    uint8 crcTime1;
    ETHTSYN_P2VAR(uint8) timeSecuredTlvStartPtr =
      &FupTxBufPtr[siteSyncSyncSmPtr->RcvdFupMsgHndl.TimeSecuredTlvInfo.TimeSecuredTlvStartIndex];

    /* #20 Get the CRC_Time_Flags from the TimeSecured Sub-TLV. */
    crcTimeFlags = IpBase_GetUint8(timeSecuredTlvStartPtr, ETHTSYN_MSG_FUP_AR_SUB_TLV_TIME_SECURED_FLAGS_OFS);

    /* #30 Get the required DataId from configuration. */
    dataId = EthTSyn_Util_GetFollowUpDataIdListEntry(EthTSyn_GetTimeDomainIdxOfPort(PortIdx),
      IpBase_GetUint16(FupTxBufPtr, ETHTSYN_MSG_HDR_SEQUENCE_ID_OFS));

    /* #40 Re-calculate the CRC. */
    crcTime0 = EthTSyn_Crc_ComputeTime0Crc(dataId, crcTimeFlags, FupTxBufPtr);
    crcTime1 = EthTSyn_Crc_ComputeTime1Crc(dataId, crcTimeFlags, FupTxBufPtr);

    /* #50 Check if CRC of TimeSecured Sub-TLV was valid in the received FollowUp. */
    if(siteSyncSyncSmPtr->RcvdFupMsgHndl.TimeSecuredTlvInfo.IsTimeTlvCrcValid == FALSE)
    {
      /* #500 Invalidate the CRC. */
      crcTime0--;
      crcTime1--;
    }

    /* #60 Set CRC_TIME_0/1 */
    IpBase_PutUint8(timeSecuredTlvStartPtr, ETHTSYN_MSG_FUP_AR_SUB_TLV_TIME_SECURED_CRC_0_OFS, crcTime0);
    IpBase_PutUint8(timeSecuredTlvStartPtr, ETHTSYN_MSG_FUP_AR_SUB_TLV_TIME_SECURED_CRC_1_OFS, crcTime1);
  }
} /* EthTSyn_SwtMgmt_SiteSyncSync_UpdateTimeSecuredSubTlvCrc() */

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_SiteSyncSync_GetTimeSecuredSubTlvStartIdx
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
/* PRQA S 6080 1 */ /* MD_MSR_STMIF */
ETHTSYN_LOCAL_INLINE FUNC(uint16, ETHTSYN_CODE) EthTSyn_SwtMgmt_SiteSyncSync_GetTimeSecuredSubTlvStartIdx(
  ETHTSYN_P2CONST(uint8) FupMsgPtr,
                  uint16 LenByte)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint16 timeSecuredTlvStartIdx = LenByte;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if the message length indicates at least one AR-TLV. */
  if(LenByte >= (ETHTSYN_MSG_FOLLOW_UP_MIN_LENGTH + ETHTSYN_AR_TLV_HEADER_LENGTH))
  {
    uint16 totalSubTlvLen;

    /* #20 Check if at least one AR-TLV is included in the FollowUp message. */
    if(EthTSyn_UtilArTlv_CheckArTlvHeader(FupMsgPtr, LenByte, &totalSubTlvLen) == E_OK)
    {
      uint16 currSubTlvOfs = ETHTSYN_MSG_FUP_FIRST_AR_SUB_TLV_OFS;
      sint32 remainingLength = (sint32)totalSubTlvLen;
      boolean continueSearch = TRUE;

      /* #30 Search for the optional TimeSecured Sub-TLV. */
      do
      {
        uint8 tlvLength;

        tlvLength = ETHTSYN_AR_SUB_TLV_ABSTRACT_HDR_LENGTH;
        tlvLength += IpBase_GetUint8(FupMsgPtr,
          ((uint32_least)currSubTlvOfs + (uint32_least)ETHTSYN_MSG_FUP_AR_SUB_TLV_LEN_OFS));

        remainingLength -= (sint32)tlvLength;

        /* #300 Check if Sub-TLV fits in the message. */
        if(remainingLength >= 0)
        {
          /* #3000 Check if the current Sub-TLV is the TimeSecured Sub-TLV. */
          /* The Ar Sub Tlv type is located at ArSubTlvOfs + ETHTSYN_MSG_FUP_AR_SUB_TLV_TYPE_OFS.
           * ETHTSYN_MSG_FUP_AR_SUB_TLV_TYPE_OFS is zero and therefore can be omitted. */
          if(IpBase_GetUint8(FupMsgPtr, currSubTlvOfs) == ETHTSYN_AR_SUB_TLV_TYPE_TIME_SECURED)
          {
            /* #30000 Store the location of the TimeSecured Sub-TLV and cancel the search. */
            timeSecuredTlvStartIdx = currSubTlvOfs;
            continueSearch = FALSE;
          }

          /* Set offset to potential next Sub-TLV. */
          currSubTlvOfs += tlvLength;
        }
        /* #301 Otherwise, message is too small to hold this Sub-TLV -> cancel search. */
        else
        {
          continueSearch = FALSE;
        }
      } while((continueSearch == TRUE) && (remainingLength > (sint32)ETHTSYN_AR_SUB_TLV_ABSTRACT_HDR_LENGTH));
    }
  }

  return timeSecuredTlvStartIdx;
} /* EthTSyn_SwtMgmt_SiteSyncSync_GetTimeSecuredSubTlvStartIdx() */
#  endif /* (ETHTSYN_MESSAGE_COMPLIANCE == STD_OFF) */
# endif /* (ETHTSYN_SITESYNCSYNCSM == STD_ON) */

/**********************************************************************************************************************
 *  MANAGEMENT QUEUE HANDLING
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_MgmtQHndl_GetFreeElemIdx
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
 */
ETHTSYN_LOCAL_INLINE FUNC(uint8, ETHTSYN_CODE) EthTSyn_SwtMgmt_MgmtQHndl_GetFreeElemIdx(
  ETHTSYN_P2VAR(uint8) QueueFreeIdxPtr,
  ETHTSYN_P2VAR(uint8) QueueCurrProcIdxPtr,
                uint8  QueueSize)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 freeElemIdx = (*QueueFreeIdxPtr);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 If a free queue element is available. */
  if(freeElemIdx < QueueSize)
  {
    /* #20 If no queue element is locked yet. */
    if((*QueueCurrProcIdxPtr) >= QueueSize)
    {
      /* #200 Set the free queue element as the first locked element. */
      (*QueueCurrProcIdxPtr) = freeElemIdx;
    }

    /* #30 Increment the free queue element index. */
    EthTSyn_SwtMgmt_MgmtQHndl_IncElemIdx(QueueSize, QueueFreeIdxPtr);

    /* #40 If no more free queue elements are available. */
    if((*QueueFreeIdxPtr) == (*QueueCurrProcIdxPtr))
    {
      /* #400 Set the free queue element index to 'QueueSize'. */
      (*QueueFreeIdxPtr) = QueueSize;
    }
  }

  return freeElemIdx;
} /* EthTSyn_SwtMgmt_MgmtQHndl_GetFreeElemIdx() */

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_MgmtQHndl_ReleaseElem
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_MgmtQHndl_ReleaseElem(
  ETHTSYN_P2VAR(uint8) QueueFreeIdxPtr,
  ETHTSYN_P2VAR(uint8) QueueCurrProcIdxPtr,
                uint8  QueueSize)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 If no free queue element is available. */
  if((*QueueFreeIdxPtr) >= QueueSize)
  {
    /* #100 Set the 'QueueFreeIdx' to the element index which will be released. */
    (*QueueFreeIdxPtr) = (*QueueCurrProcIdxPtr);
  }

  /* #20 Increment the 'QueueCurrProcIdx' */
  EthTSyn_SwtMgmt_MgmtQHndl_IncElemIdx(QueueSize, QueueCurrProcIdxPtr);

  /* #30 If no more queue elements are pending, invalidate the 'QueueCurrProcIdx'. */
  if((*QueueCurrProcIdxPtr) == (*QueueFreeIdxPtr))
  {
    (*QueueCurrProcIdxPtr) = QueueSize;
  }
} /* EthTSyn_SwtMgmt_MgmtQHndl_ReleaseElem() */

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_MgmtQHndl_IncElemIdx
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_MgmtQHndl_IncElemIdx(
                uint8  QueueSize,
  ETHTSYN_P2VAR(uint8) ElemIdxPtr)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Increment the element index and check for overflow. */
  (*ElemIdxPtr)++;
  if((*ElemIdxPtr) >= QueueSize)
  {
    /* #20 Set the element index to '0' in case of wrap-around. */
    (*ElemIdxPtr) = 0u;
  }
} /* EthTSyn_SwtMgmt_MgmtQHndl_IncElemIdx() */

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_MgmtQHndl_IncElemProcIter
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_MgmtQHndl_IncElemProcIter(
                uint8        QueueFreeIdx,
                uint8        QueueCurrProcIdx,
                uint8        QueueSize,
  ETHTSYN_P2VAR(uint8_least) QueueElemProcIterPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 queueEndIdx;
  uint8 queueElemProcIterLoc = (uint8)(*QueueElemProcIterPtr);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Get the end index for the queue element processing iteration. */
  if(QueueFreeIdx < QueueSize)
  {
    /* In case a free element is available, the iteration shall be stopped when the first free element is reached. */
    queueEndIdx = QueueFreeIdx;
  }
  else
  {
    /* Otherwise, the iteration shall be stopped when all elements where processed, i.e. the original start index
     * ('QueueCurrProcIdx') is reached again. */
    queueEndIdx = QueueCurrProcIdx;
  }

  /* #20 Increment the iterator. */
  EthTSyn_SwtMgmt_MgmtQHndl_IncElemIdx(QueueSize, &queueElemProcIterLoc);

  /* #30 If end of queue is reached, set iterator to QueueSize. */
  if(queueElemProcIterLoc == queueEndIdx)
  {
    queueElemProcIterLoc = QueueSize;
  }

  (*QueueElemProcIterPtr) = (uint8_least)queueElemProcIterLoc;
} /* EthTSyn_SwtMgmt_MgmtQHndl_IncElemProcIter() */

/**********************************************************************************************************************
 *  RX BUFFER HANDLING
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_RxBufHndl_Poll
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
 */
/* PRQA S 6050 1 */ /* MD_EthTSyn_6050_CslAccess */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_RxBufHndl_Poll(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthTSyn_SwtMgmtRxBufIterType rxBufCurrProcIter;

  /* ----- Implementation ----------------------------------------------- */
  ETHTSYN_ENTER_CRITICAL_SECTION_0();
  /* #10 Iterate all pending received messages. */
  for(rxBufCurrProcIter = EthTSyn_GetSwtMgmtRxBufQueueCurrProcIdx();
      rxBufCurrProcIter < EthTSyn_GetSizeOfSwtMgmtRxBuf();
      EthTSyn_SwtMgmt_RxBufHndl_IncIter(&rxBufCurrProcIter))
  {
    /*@ assert rxBufCurrProcIter < EthTSyn_GetSizeOfSwtMgmtRxBufCfg(); */
    const EthTSyn_SwtMgmtMgmtObjHndlIdxOfSwtMgmtRxBufCfgType mgmtObjHndlIdx =
      EthTSyn_GetSwtMgmtMgmtObjHndlIdxOfSwtMgmtRxBufCfg(rxBufCurrProcIter);
    ETHTSYN_CONSTP2VAR(EthSwt_MgmtObjectType) ethSwtMgmtObjPtr =
      EthTSyn_GetEthSwtMgmtObjPtrOfSwtMgmtMgmtObjHndl(mgmtObjHndlIdx);
    /*@ assert $external(ethSwtMgmtObjPtr); */                                                                         /* VCA_ETHTSYN_ETH_SWT_MGMT_OBJ */

    /* #20 If state of Rx buffer and the included Rx management object is PENDING. */
    if(EthTSyn_GetStateOfSwtMgmtRxBuf(rxBufCurrProcIter) == ETHTSYN_PENDING_STATEOFSWTMGMTRXBUF)
    {
      /* #200 If switch management object is owned by EthTSyn. */
      if(ethSwtMgmtObjPtr->Ownership == ETHSWT_MGMT_OBJ_OWNED_BY_UPPER_LAYER)
      {
        /* #2000 Copy the switch management object information. */
        EthTSyn_SwtMgmt_CpyMgmtObjInfo(mgmtObjHndlIdx);

        /* #2001 Release the switch management object.*/
        ethSwtMgmtObjPtr->Ownership = ETHSWT_MGMT_OBJ_UNUSED;
        EthTSyn_SetEthSwtMgmtObjPtrOfSwtMgmtMgmtObjHndl(mgmtObjHndlIdx, NULL_PTR);

        /* #2002 Mark the received message as READY. */
        EthTSyn_SetStateOfSwtMgmtRxBuf(rxBufCurrProcIter, ETHTSYN_READY_STATEOFSWTMGMTRXBUF);
      }
    }
    /* #30 Otherwise, if state of Rx buffer is WAIT_RELEASE. */
    else if(EthTSyn_GetStateOfSwtMgmtRxBuf(rxBufCurrProcIter) == ETHTSYN_WAIT_RELEASE_STATEOFSWTMGMTRXBUF)
    {
      /* #300 If switch management object is owned by EthTSyn. */
      if(ethSwtMgmtObjPtr->Ownership == ETHSWT_MGMT_OBJ_OWNED_BY_UPPER_LAYER)
      {
        /* #3000 Release the switch management object. */
        ethSwtMgmtObjPtr->Ownership = ETHSWT_MGMT_OBJ_UNUSED;
        EthTSyn_SetEthSwtMgmtObjPtrOfSwtMgmtMgmtObjHndl(mgmtObjHndlIdx, NULL_PTR);

        /* #3001 Set Rx buffer state to RELEASE. */
        EthTSyn_SetStateOfSwtMgmtRxBuf(rxBufCurrProcIter, ETHTSYN_RELEASE_STATEOFSWTMGMTRXBUF);
      }
    }
    /* #40 Otherwise. */
    else
    {
      /* #400 Nothing to do. */
    }
  }
  ETHTSYN_LEAVE_CRITICAL_SECTION_0();
} /* EthTSyn_SwtMgmt_RxBufHndl_Poll() */

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_RxBufHndl_IncIter
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_RxBufHndl_IncIter(
  ETHTSYN_P2VAR(EthTSyn_SwtMgmtRxBufIterType) RxBufIterPtr)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Increment the Rx-Buffer iterator. */
  EthTSyn_SwtMgmt_MgmtQHndl_IncElemProcIter(EthTSyn_GetSwtMgmtRxBufQueueFreeIdx(),
    EthTSyn_GetSwtMgmtRxBufQueueCurrProcIdx(), EthTSyn_GetSizeOfSwtMgmtRxBuf(), RxBufIterPtr);
} /* EthTSyn_SwtMgmt_RxBufHndl_IncIter() */

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_RxBufHndl_ProcPending
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
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_RxBufHndl_ProcPending(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthTSyn_SwtMgmtRxBufIterType rxBufCurrProcIter;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate all pending received messages. */
  for(rxBufCurrProcIter = EthTSyn_GetSwtMgmtRxBufQueueCurrProcIdx();
      rxBufCurrProcIter < EthTSyn_GetSizeOfSwtMgmtRxBuf();
      EthTSyn_SwtMgmt_RxBufHndl_IncIter(&rxBufCurrProcIter))
  {
    /* #20 If message is ready for processing. */
    if(EthTSyn_GetStateOfSwtMgmtRxBuf(rxBufCurrProcIter) == ETHTSYN_READY_STATEOFSWTMGMTRXBUF)
    {
      /* #200 Process the received message. */
      EthTSyn_SwtMgmt_Rx_ProcMsgBuffer(rxBufCurrProcIter);

      /* #201 Release the message buffer. */
      EthTSyn_SwtMgmt_RxBufHndl_Release();
    }
    /* #30 Otherwise, if message buffer should be released. */
    else if (EthTSyn_GetStateOfSwtMgmtRxBuf(rxBufCurrProcIter) == ETHTSYN_RELEASE_STATEOFSWTMGMTRXBUF)
    {
      /* #300 Drop the message and release the message buffer. */
      EthTSyn_SwtMgmt_RxBufHndl_Release();
    }
    /* #40 Otherwise, stop iteration. */
    else
    {
      /* Iteration is stopped here, to ensure that messages are processed in the same order as they were received. */
      break;
    }
  }
} /* EthTSyn_SwtMgmt_RxBufHndl_ProcPending() */

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_RxBufHndl_GetFreeIdx
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(uint8, ETHTSYN_CODE) EthTSyn_SwtMgmt_RxBufHndl_GetFreeIdx(void)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Get and lock free Rx buffer index. */
  return EthTSyn_SwtMgmt_MgmtQHndl_GetFreeElemIdx(EthTSyn_GetAddrSwtMgmtRxBufQueueFreeIdx(),
    EthTSyn_GetAddrSwtMgmtRxBufQueueCurrProcIdx(), EthTSyn_GetSizeOfSwtMgmtRxBuf());
} /* EthTSyn_SwtMgmt_RxBufHndl_GetFreeIdx() */

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_RxBufHndl_Release
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_RxBufHndl_Release(void)
{
  /* ----- Implementation ----------------------------------------------- */
  ETHTSYN_ENTER_CRITICAL_SECTION_0();
  /* #10 Releases the first locked Rx buffer in the queue. */
  EthTSyn_SwtMgmt_MgmtQHndl_ReleaseElem(EthTSyn_GetAddrSwtMgmtRxBufQueueFreeIdx(),
    EthTSyn_GetAddrSwtMgmtRxBufQueueCurrProcIdx(), EthTSyn_GetSizeOfSwtMgmtRxBuf());
  ETHTSYN_LEAVE_CRITICAL_SECTION_0();
} /* EthTSyn_SwtMgmt_RxBufHndl_Release() */

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_RxBufHndl_ReleaseAllPending
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
/* PRQA S 6050 1 */ /* MD_EthTSyn_6050_CslAccess */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_RxBufHndl_ReleaseAllPending(
  EthTSyn_IntCtrlIdxType EthTSynCtrlIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthTSyn_SwtMgmtRxBufIterType rxBufCurrProcIter;

  /* ----- Implementation ----------------------------------------------- */
  ETHTSYN_ENTER_CRITICAL_SECTION_0();
  /* #10 Iterate all pending received messages. */
  for(rxBufCurrProcIter = EthTSyn_GetSwtMgmtRxBufQueueCurrProcIdx();
      rxBufCurrProcIter < EthTSyn_GetSizeOfSwtMgmtRxBuf();
      EthTSyn_SwtMgmt_RxBufHndl_IncIter(&rxBufCurrProcIter))
  {
    /* #20 If state of Rx buffer and the included Rx management object is PENDING. */
    if(EthTSyn_GetStateOfSwtMgmtRxBuf(rxBufCurrProcIter) == ETHTSYN_PENDING_STATEOFSWTMGMTRXBUF)
    {
      /* #200 If Rx buffer is mapped to the passed EthTSyn controller. */
      if(EthTSyn_GetCtrlIdxOfSwtMgmtRxBuf(rxBufCurrProcIter) == EthTSynCtrlIdx)
      {
        /* #2000 Set state of the Rx buffer to WAIT_RELEASE. */
        EthTSyn_SetStateOfSwtMgmtRxBuf(rxBufCurrProcIter, ETHTSYN_WAIT_RELEASE_STATEOFSWTMGMTRXBUF);
      }
    }
  }
  ETHTSYN_LEAVE_CRITICAL_SECTION_0();
} /* EthTSyn_SwtMgmt_RxBufHndl_ReleaseAllPending() */

/**********************************************************************************************************************
 *  TX MGMT OBJECT HANDLING
 *********************************************************************************************************************/
# if (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_TxMgmtObjHndl_Poll
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
 */
/* PRQA S 6050 1 */ /* MD_EthTSyn_6050_CslAccess */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_TxMgmtObjHndl_Poll(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthTSyn_SwtMgmtTxMgmtObjCfgIterType txMgmtObjCurrProcIter;

  /* ----- Implementation ----------------------------------------------- */
  ETHTSYN_ENTER_CRITICAL_SECTION_0();
  /* #10 Iterate all pending tx management objects. */
  for(txMgmtObjCurrProcIter = EthTSyn_GetSwtMgmtTxMgmtObjQueueCurrProcIdx();
      txMgmtObjCurrProcIter < EthTSyn_GetSizeOfSwtMgmtTxMgmtObj();
      EthTSyn_SwtMgmt_TxMgmtObjHndl_IncIter(&txMgmtObjCurrProcIter))
  {
    const EthTSyn_SwtMgmtMgmtObjHndlIdxOfSwtMgmtTxMgmtObjCfgType mgmtObjHndlIdx =
      EthTSyn_GetSwtMgmtMgmtObjHndlIdxOfSwtMgmtTxMgmtObjCfg(txMgmtObjCurrProcIter);
    ETHTSYN_CONSTP2VAR(EthSwt_MgmtObjectType) ethSwtMgmtObjPtr =
      EthTSyn_GetEthSwtMgmtObjPtrOfSwtMgmtMgmtObjHndl(mgmtObjHndlIdx);
    /*@ assert $external(ethSwtMgmtObjPtr); */                                                                         /* VCA_ETHTSYN_ETH_SWT_MGMT_OBJ */

    /* #20 If state of the Tx management object is PENDING. */
    if(EthTSyn_GetStateOfSwtMgmtTxMgmtObj(txMgmtObjCurrProcIter) == ETHTSYN_PENDING_STATEOFSWTMGMTTXMGMTOBJ)
    {
      /* #200 If switch management object is owned by EthTSyn. */
      if(ethSwtMgmtObjPtr->Ownership == ETHSWT_MGMT_OBJ_OWNED_BY_UPPER_LAYER)
      {
        /* #2000 Copy the switch management information. */
        EthTSyn_SwtMgmt_CpyMgmtObjInfo(mgmtObjHndlIdx);

        /* #2001 Release the switch management object. */
        ethSwtMgmtObjPtr->Ownership = ETHSWT_MGMT_OBJ_UNUSED;
        EthTSyn_SetEthSwtMgmtObjPtrOfSwtMgmtMgmtObjHndl(mgmtObjHndlIdx, NULL_PTR);

        /* #2002 Set state of the Tx management object to AVAILABLE. */
        EthTSyn_SetStateOfSwtMgmtTxMgmtObj(txMgmtObjCurrProcIter, ETHTSYN_AVAILABLE_STATEOFSWTMGMTTXMGMTOBJ);
      }
    }
    /* #30 Otherwise, if state of the Tx management object is WAIT_RELEASE. */
    else if(EthTSyn_GetStateOfSwtMgmtTxMgmtObj(txMgmtObjCurrProcIter) == ETHTSYN_WAIT_RELEASE_STATEOFSWTMGMTTXMGMTOBJ)
    {
      /* #300 If switch management object is owned by EthTSyn. */
      if(ethSwtMgmtObjPtr->Ownership == ETHSWT_MGMT_OBJ_OWNED_BY_UPPER_LAYER)
      {
        /* #3000 Release the switch management object. */
        ethSwtMgmtObjPtr->Ownership = ETHSWT_MGMT_OBJ_UNUSED;
        EthTSyn_SetEthSwtMgmtObjPtrOfSwtMgmtMgmtObjHndl(mgmtObjHndlIdx, NULL_PTR);

        /* #3001 Set Tx management object state to RELEASE. */
        EthTSyn_SetStateOfSwtMgmtTxMgmtObj(txMgmtObjCurrProcIter, ETHTSYN_RELEASE_STATEOFSWTMGMTTXMGMTOBJ);
      }
    }
    /* #40 Otherwise. */
    else
    {
      /* #400 Nothing to do. */
    }
  }
  ETHTSYN_LEAVE_CRITICAL_SECTION_0();
} /* EthTSyn_SwtMgmt_TxMgmtObjHndl_Poll() */

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_TxMgmtObjHndl_IncIter
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_TxMgmtObjHndl_IncIter(
  ETHTSYN_P2VAR(EthTSyn_SwtMgmtTxMgmtObjCfgIterType) TxMgmtObjIterPtr)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Increment the TxMgmtObj iterator. */
  EthTSyn_SwtMgmt_MgmtQHndl_IncElemProcIter(EthTSyn_GetSwtMgmtTxMgmtObjQueueFreeIdx(),
    EthTSyn_GetSwtMgmtTxMgmtObjQueueCurrProcIdx(), EthTSyn_GetSizeOfSwtMgmtTxMgmtObj(), TxMgmtObjIterPtr);
} /* EthTSyn_SwtMgmt_TxMgmtObjHndl_IncIter() */

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_TxMgmtObjHndl_ProcPending
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
/* PRQA S 6050 1 */ /* MD_EthTSyn_6050_CslAccess */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_TxMgmtObjHndl_ProcPending(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthTSyn_SwtMgmtTxMgmtObjCfgIterType txMgmtObjCurrProcIter;

  /* ----- Implementation ----------------------------------------------- */
  ETHTSYN_ENTER_CRITICAL_SECTION_0();
  /* #10 Iterate all pending tx management objects. */
  for(txMgmtObjCurrProcIter = EthTSyn_GetSwtMgmtTxMgmtObjQueueCurrProcIdx();
      txMgmtObjCurrProcIter < EthTSyn_GetSizeOfSwtMgmtTxMgmtObj();
      EthTSyn_SwtMgmt_TxMgmtObjHndl_IncIter(&txMgmtObjCurrProcIter))
  {
    /* #20 If Tx management object is ready for processing. */
    if(EthTSyn_GetStateOfSwtMgmtTxMgmtObj(txMgmtObjCurrProcIter) == ETHTSYN_AVAILABLE_STATEOFSWTMGMTTXMGMTOBJ)
    {
      /* #200 Copy the timestamp info. */
      EthTSyn_SwtMgmt_TxMgmtObjHndl_CpyTs(txMgmtObjCurrProcIter);

      /* #201 Release the Tx management object.*/
      EthTSyn_SwtMgmt_TxMgmtObjHndl_Release();
    }
    /* #30 Otherwise, if the Tx management object should be released. */
    else if(EthTSyn_GetStateOfSwtMgmtTxMgmtObj(txMgmtObjCurrProcIter) == ETHTSYN_RELEASE_STATEOFSWTMGMTTXMGMTOBJ)
    {
      /* #300 Release the Tx management object. */
      EthTSyn_SwtMgmt_TxMgmtObjHndl_Release();
    }
    /* #40 Otherwise, stop iteration. */
    else
    {
      /* Stop iteration here, to ensure that messages are processed in the same order as they where transmitted. */
      break;
    }
  }
  ETHTSYN_LEAVE_CRITICAL_SECTION_0();
} /* EthTSyn_SwtMgmt_TxMgmtObjHndl_ProcPending() */

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_TxMgmtObjHndl_CpyTs
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_TxMgmtObjHndl_CpyTs(
  EthTSyn_SwtMgmtTxMgmtObjCfgIterType TxMgmtObjIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthTSyn_TsMgmtStructPtrType smIngrTsMgmtPtr = EthTSyn_GetSmIngressTsMgmtPtrOfSwtMgmtTxMgmtObj(TxMgmtObjIdx);
  EthTSyn_TsMgmtStructPtrType smEgrTsMgmtPtr = EthTSyn_GetSmEgressTsMgmtPtrOfSwtMgmtTxMgmtObj(TxMgmtObjIdx);
  EthTSyn_SwtMgmtMgmtObjHndlIdxOfSwtMgmtTxMgmtObjCfgType swtMgmtObjHndlIdx =
    EthTSyn_GetSwtMgmtMgmtObjHndlIdxOfSwtMgmtTxMgmtObjCfg(TxMgmtObjIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 If switch ingress timestamp is required. */
  if(smIngrTsMgmtPtr != NULL_PTR)
  {
    /* #100 Copy the switch ingress timestamp to the mapped state machine. */
    (*smIngrTsMgmtPtr) = EthTSyn_GetSwtIngressTsMgmtOfSwtMgmtMgmtObjHndl(swtMgmtObjHndlIdx);
  }

  /* #20 If switch egress timestamp is required. */
  if(smEgrTsMgmtPtr != NULL_PTR)
  {
    /* #200 Copy the switch egress timestamp to the mapped state machine. */
    (*smEgrTsMgmtPtr) = EthTSyn_GetSwtEgressTsMgmtOfSwtMgmtMgmtObjHndl(swtMgmtObjHndlIdx);
  }

} /* EthTSyn_SwtMgmt_TxMgmtObjHndl_CpyTs() */

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_TxMgmtObjHndl_GetFreeIdx
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(uint8, ETHTSYN_CODE) EthTSyn_SwtMgmt_TxMgmtObjHndl_GetFreeIdx(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 freeTxMgmtObjIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Get and lock free Tx management object index. */
  freeTxMgmtObjIdx = EthTSyn_SwtMgmt_MgmtQHndl_GetFreeElemIdx(EthTSyn_GetAddrSwtMgmtTxMgmtObjQueueFreeIdx(),
    EthTSyn_GetAddrSwtMgmtTxMgmtObjQueueCurrProcIdx(), EthTSyn_GetSizeOfSwtMgmtTxMgmtObj());

  if(freeTxMgmtObjIdx < EthTSyn_GetSizeOfSwtMgmtTxMgmtObj())
  {
    EthTSyn_SetStateOfSwtMgmtTxMgmtObj(freeTxMgmtObjIdx, ETHTSYN_LOCKED_STATEOFSWTMGMTTXMGMTOBJ);

    /* #20 Set state machine timestamp pointers to NULL_PTR. */
    EthTSyn_SetSmIngressTsMgmtPtrOfSwtMgmtTxMgmtObj(freeTxMgmtObjIdx, NULL_PTR);
    EthTSyn_SetSmEgressTsMgmtPtrOfSwtMgmtTxMgmtObj(freeTxMgmtObjIdx, NULL_PTR);
  }

  return freeTxMgmtObjIdx;
} /* EthTSyn_SwtMgmt_TxMgmtObjHndl_GetFreeIdx() */

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_TxMgmtObjHndl_Release
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_TxMgmtObjHndl_Release(void)
{
  /* ----- Implementation ----------------------------------------------- */
  EthTSyn_SwtMgmt_MgmtQHndl_ReleaseElem(EthTSyn_GetAddrSwtMgmtTxMgmtObjQueueFreeIdx(),
    EthTSyn_GetAddrSwtMgmtTxMgmtObjQueueCurrProcIdx(), EthTSyn_GetSizeOfSwtMgmtTxMgmtObj());
} /* EthTSyn_SwtMgmt_TxMgmtObjHndl_Release() */

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_TxMgmtObjHndl_ReleaseAllPending
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
/* PRQA S 6050 1 */ /* MD_EthTSyn_6050_CslAccess */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_TxMgmtObjHndl_ReleaseAllPending(
  EthTSyn_IntCtrlIdxType EthTSynCtrlIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthTSyn_SwtMgmtTxMgmtObjCfgIterType txMgmtObjCurrProcIter;

  /* ----- Implementation ----------------------------------------------- */
  ETHTSYN_ENTER_CRITICAL_SECTION_0();
  /* #10 Iterate all pending tx management objects. */
  for(txMgmtObjCurrProcIter = EthTSyn_GetSwtMgmtTxMgmtObjQueueCurrProcIdx();
      txMgmtObjCurrProcIter < EthTSyn_GetSizeOfSwtMgmtTxMgmtObj();
      EthTSyn_SwtMgmt_TxMgmtObjHndl_IncIter(&txMgmtObjCurrProcIter))
  {
    /* #20 If state of the Tx management object is PENDING. */
    if(EthTSyn_GetStateOfSwtMgmtTxMgmtObj(txMgmtObjCurrProcIter) == ETHTSYN_PENDING_STATEOFSWTMGMTTXMGMTOBJ)
    {
      /* #200 If Tx management object is mapped to the passed EthTSyn controller. */
      if(EthTSyn_GetCtrlIdxOfSwtMgmtTxMgmtObj(txMgmtObjCurrProcIter) == EthTSynCtrlIdx)
      {
        /* #2000 Set state of the Tx management object to WAIT_RELEASE. */
        EthTSyn_SetStateOfSwtMgmtTxMgmtObj(txMgmtObjCurrProcIter, ETHTSYN_WAIT_RELEASE_STATEOFSWTMGMTTXMGMTOBJ);
      }
    }
  }
  ETHTSYN_LEAVE_CRITICAL_SECTION_0();
} /* EthTSyn_SwtMgmt_TxMgmtObjHndl_ReleaseAllPending() */
# endif /* (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON) */

/**********************************************************************************************************************
 *  MGMT OBJECT HANDLING FUNCTIONS
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_CpyMgmtObjInfo
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
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_CpyMgmtObjInfo(
  EthTSyn_SwtMgmtMgmtObjHndlIterType MgmtObjHndlIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  ETHTSYN_CONSTP2CONST(EthSwt_MgmtObjectType) ethSwtMgmtObjPtr =
    EthTSyn_GetEthSwtMgmtObjPtrOfSwtMgmtMgmtObjHndl(MgmtObjHndlIdx);
  EthTSyn_SwtMgmtInfoOfSwtMgmtMgmtObjHndlPtrType mgmtInfoPtr =
    EthTSyn_GetAddrSwtMgmtInfoOfSwtMgmtMgmtObjHndl(MgmtObjHndlIdx);

  /* ----- Implementation ----------------------------------------------- */
/* #10 If switch management info is valid. */
  if(ethSwtMgmtObjPtr->Validation.MgmtInfoValid == E_OK)
  {
    /* #100 Copy the switch management info and mark switch management info of EthTSyn switch management object
     *      as valid. */
    mgmtInfoPtr->MgmtInfo.SwitchIdx = ethSwtMgmtObjPtr->MgmtInfo.SwitchIdx;
    mgmtInfoPtr->MgmtInfo.PortIdx = ethSwtMgmtObjPtr->MgmtInfo.PortIdx;

    mgmtInfoPtr->IsValid = TRUE;
  }
  /* #20 Otherwise, invalidate switch management info of EthTSyn switch management object. */
  else
  {
    mgmtInfoPtr->IsValid = FALSE;
  }

# if (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON)
  /* #30 Copy switch timestamps (if ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON). */
  {
    EthTSyn_SwtEgressTsMgmtOfSwtMgmtMgmtObjHndlPtrType swtEgrTsMgmtPtr =
      EthTSyn_GetAddrSwtEgressTsMgmtOfSwtMgmtMgmtObjHndl(MgmtObjHndlIdx);
    EthTSyn_SwtIngressTsMgmtOfSwtMgmtMgmtObjHndlPtrType swtIngrTsMgmtPtr =
      EthTSyn_GetAddrSwtIngressTsMgmtOfSwtMgmtMgmtObjHndl(MgmtObjHndlIdx);

    /* #300 If switch egress timestamp is valid. */
    if(ethSwtMgmtObjPtr->Validation.EgressTimestampValid == E_OK)
    {
      /* #3000 Copy the switch egress timestamp and mark switch egress timestamp of EthTSyn switch management object
       *       as valid. */
      swtEgrTsMgmtPtr->Ts.secondsHi = ethSwtMgmtObjPtr->EgressTimestamp.secondsHi;
      swtEgrTsMgmtPtr->Ts.seconds = ethSwtMgmtObjPtr->EgressTimestamp.seconds;
      swtEgrTsMgmtPtr->Ts.nanoseconds = ethSwtMgmtObjPtr->EgressTimestamp.nanoseconds;

      swtEgrTsMgmtPtr->State = ETHTSYN_TS_S_AVAILABLE;
    }
    /* #301 Otherwise, invalidate switch egress timestamp of EthTSyn switch management object. */
    else
    {
      swtEgrTsMgmtPtr->State = ETHTSYN_TS_S_INVALID;
    }

    /* #302 If switch ingress timestamp is valid. */
    if(ethSwtMgmtObjPtr->Validation.IngressTimestampValid == E_OK)
    {
      /* #3020 Copy the switch ingress timestamp and mark switch ingress timestamp of EthTSyn switch management object
       *       as valid. */
      swtIngrTsMgmtPtr->Ts.secondsHi = ethSwtMgmtObjPtr->IngressTimestamp.secondsHi;
      swtIngrTsMgmtPtr->Ts.seconds = ethSwtMgmtObjPtr->IngressTimestamp.seconds;
      swtIngrTsMgmtPtr->Ts.nanoseconds = ethSwtMgmtObjPtr->IngressTimestamp.nanoseconds;

      swtIngrTsMgmtPtr->State = ETHTSYN_TS_S_AVAILABLE;
    }
    /* #303 Otherwise, invalidate switch ingress timestamp of EthTSyn switch management object. */
    else
    {
      swtIngrTsMgmtPtr->State = ETHTSYN_TS_S_INVALID;
    }
  }
# endif /* (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON) */
} /* EthTSyn_SwtMgmt_CpyMgmtObjInfo() */

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_MainFunction
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
 */
FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_MainFunction(void)
{
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
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Poll Rx-Management-Objects. */
    EthTSyn_SwtMgmt_RxBufHndl_Poll();

    /* #30 Process pending received messages. */
    EthTSyn_SwtMgmt_RxBufHndl_ProcPending();

# if (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON)
    /* #40 Poll Tx-Management-Objects (if ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT). */
    EthTSyn_SwtMgmt_TxMgmtObjHndl_Poll();

    /* #50 Process pending Tx-Management-Objects. */
    EthTSyn_SwtMgmt_TxMgmtObjHndl_ProcPending();
# endif /* (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON) */
  }

  /* ----- Development Error Report ------------------------------------- */
# if (ETHTSYN_DEV_ERROR_REPORT == STD_ON)
  /* #60 Report error to default error tracer (DET) if any occurred. */
  if(errorId != ETHTSYN_E_NO_ERROR)
  {
    (void)Det_ReportError(ETHTSYN_MODULE_ID, ETHTSYN_INSTANCE_ID, ETHTSYN_SID_SWT_MGMT_MAIN_FUNCTION, errorId);
  }
# else
  ETHTSYN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
# endif /* (ETHTSYN_DEV_ERROR_REPORT == STD_ON) */
} /* EthTSyn_SwtMgmt_MainFunction() */

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_Init
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
/* PRQA S 6050 1 */ /* MD_EthTSyn_6050_CslAccess */
FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_Init(void)
{
  /* ----- Local Variables ---------------------------------------------- */
# if (ETHTSYN_SITESYNCSYNCSM == STD_ON)
  EthTSyn_TimeDomainIterType timeDomainIter;
# endif /* (ETHTSYN_SLAVE_SUPPORT == STD_ON) */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Initialize Rx/Tx management object queue indices. */
  EthTSyn_SetSwtMgmtRxBufQueueCurrProcIdx(EthTSyn_GetSizeOfSwtMgmtRxBuf());
  EthTSyn_SetSwtMgmtRxBufQueueFreeIdx(0u);

# if (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON)
  EthTSyn_SetSwtMgmtTxMgmtObjQueueCurrProcIdx(EthTSyn_GetSizeOfSwtMgmtTxMgmtObj());
  EthTSyn_SetSwtMgmtTxMgmtObjQueueFreeIdx(0u);
# endif /* (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON) */

  /* #20 Initialize site sync sync state machine (if applicable). */
# if (ETHTSYN_SITESYNCSYNCSM == STD_ON)
  for(timeDomainIter = 0; timeDomainIter < EthTSyn_GetSizeOfTimeDomain(); timeDomainIter++)
  {
    const EthTSyn_SiteSyncSyncSmIdxOfTimeDomainType siteSyncSyncSmIdx =
      EthTSyn_GetSiteSyncSyncSmIdxOfTimeDomain(timeDomainIter);

    /* #2000 Initialize site sync sync state machine state if required. */
    if(siteSyncSyncSmIdx < EthTSyn_GetSizeOfSiteSyncSyncSm())
    {
      /* The site sync sync state machine is only used when a bridge slave port is present. So
       * EthTSyn_SwtMgmt_GetSwitchSlavePortIdx() will always return a valid value here. */
      const EthTSyn_IntSlavePortIdxType swtSlavePortIdx = EthTSyn_SwtMgmt_GetSwitchSlavePortIdx(timeDomainIter);
      /*@ assert swtSlavePortIdx < EthTSyn_GetSizeOfSlavePort(); */                                                    /* VCA_ETHTSYN_SITE_SYNC_SYNC_SWT_SLAVE_PORT_IDX */
      ETHTSYN_CONSTP2VAR(EthTSyn_SyncReceiveSmType) syncReceiveSmPtr = EthTSyn_GetAddrSyncReceiveSm(swtSlavePortIdx);
      ETHTSYN_CONSTP2VAR(EthTSyn_SiteSyncSyncSmType) siteSyncSyncSmPtr =
        EthTSyn_GetAddrSiteSyncSyncSm(siteSyncSyncSmIdx);

      siteSyncSyncSmPtr->SyncRxTimeoutDetected = FALSE;

      siteSyncSyncSmPtr->State = ETHTSYN_S_SSS_SM_PENDING;

      siteSyncSyncSmPtr->RcvdSyncMsgHndl.MsgHndl.TxRetryCnt = 0u;
      siteSyncSyncSmPtr->RcvdSyncMsgHndl.MsgHndl.TxPendingCnt = 0u;

      siteSyncSyncSmPtr->RcvdFupMsgHndl.MsgHndl.TxRetryCnt = 0u;
      siteSyncSyncSmPtr->RcvdFupMsgHndl.MsgHndl.TxPendingCnt = 0u;

#  if (ETHTSYN_MESSAGE_COMPLIANCE == STD_OFF)
      siteSyncSyncSmPtr->RcvdFupMsgHndl.TimeSecuredTlvInfo.IsTimeTlvIncluded = FALSE;
      siteSyncSyncSmPtr->RcvdFupMsgHndl.TimeSecuredTlvInfo.IsTimeTlvCrcValid = FALSE;
      siteSyncSyncSmPtr->RcvdFupMsgHndl.TimeSecuredTlvInfo.TimeSecuredTlvStartIndex = 0u;
#  endif /* (ETHTSYN_MESSAGE_COMPLIANCE == STD_OFF) */

      syncReceiveSmPtr->Sync.SyncRxTimeoutCnt = EthTSyn_GetSwtMgmtSyncTimeoutOfTimeDomain(timeDomainIter);


#  if (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON)
      siteSyncSyncSmPtr->RcvdSyncMsgHndl.SwtIngressTsMgmt.State = ETHTSYN_TS_S_UNDEFINED;
      siteSyncSyncSmPtr->RcvdSyncMsgHndl.SwtHostPortEgressTsMgmt.State = ETHTSYN_TS_S_UNDEFINED;
#  else
      siteSyncSyncSmPtr->RcvdSyncMsgHndl.HostIngressIntVltMgmt.IntVltValid = FALSE;
#  endif /* (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON) */
    }
  }
# endif /* (ETHTSYN_SITESYNCSYNCSM == STD_ON) */
} /* EthTSyn_SwtMgmt_Init() */

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_ReleasePendingSwtMgmtObj
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_ReleasePendingSwtMgmtObj(
  EthTSyn_IntCtrlIdxType EthTSynCtrlIdx)
{
  /* #10 Mark all pending RxMgmtObj of the passed EthIf controller as to be released. */
  EthTSyn_SwtMgmt_RxBufHndl_ReleaseAllPending(EthTSynCtrlIdx);

# if (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON)
  /* #20 Mark all pending TxMgmtObj of the passed EthIf controller as to be released
   *     (if ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON). */
  EthTSyn_SwtMgmt_TxMgmtObjHndl_ReleaseAllPending(EthTSynCtrlIdx);
# endif /* ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON */

} /* EthTSyn_SwtMgmt_ReleasePendingSwtMgmtObj() */

/**********************************************************************************************************************
 *  RX
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_Rx_HndlMsgReception
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
/* PRQA S 6050 1 */ /* MD_EthTSyn_6050_CslAccess */
FUNC(uint8, ETHTSYN_CODE) EthTSyn_SwtMgmt_Rx_HndlMsgReception(
  ETHTSYN_P2CONST(uint8)                  DataPtr,
                  uint16                  LenByte,
                  EthTSyn_IntCtrlIdxType  EthTSynCtrlIdx,
  ETHTSYN_P2CONST(EthTSyn_IntVltMgmtType) IngressIntVltMgmtPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 freeRxBufIdx;
  uint8 errorId = ETHTSYN_E_NO_ERROR;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Perform basic message checks and get a free message buffer. */
  freeRxBufIdx = EthTSyn_SwtMgmt_Rx_PerformBasicMsgChecksAndGetRxBufIdx(LenByte, DataPtr, &errorId);
  if(freeRxBufIdx < EthTSyn_GetSizeOfSwtMgmtRxBuf())
  {
    const EthTSyn_SwtMgmtMgmtObjHndlIdxOfSwtMgmtRxBufCfgType mgmtObjHndlIdx =
      EthTSyn_GetSwtMgmtMgmtObjHndlIdxOfSwtMgmtRxBufCfg(freeRxBufIdx);
    /* #20 Get the switch Rx management object from EthIf.
     *     If getting the switch Rx management object succeeded. */
    /* PRQA S 0310, 0311, 3305 2 */ /* MD_EthTSyn_PtrCast_EthBuffer */
    if(EthIf_GetRxMgmtObject(EthTSyn_GetEthIfCtrlIdxOfCtrl(EthTSynCtrlIdx), (ETHTSYN_P2VAR(Eth_DataType))DataPtr,
      EthTSyn_GetAddrEthSwtMgmtObjPtrOfSwtMgmtMgmtObjHndl(mgmtObjHndlIdx)) == E_OK)
    {
      const EthTSyn_SwtMgmtRcvdMsgBufStartIdxOfSwtMgmtRxBufCfgType rcvdMsgBufStartIdx =
        EthTSyn_GetSwtMgmtRcvdMsgBufStartIdxOfSwtMgmtRxBufCfg(freeRxBufIdx);

      EthTSyn_SetCtrlIdxOfSwtMgmtRxBuf(freeRxBufIdx, EthTSynCtrlIdx);

      /* #200 Assign the HostController ingress Timestamping. */
      EthTSyn_SetHostIngressIntVltMgmtOfSwtMgmtRxBuf(freeRxBufIdx, (*IngressIntVltMgmtPtr));

      /* #201 Copy the received message to the message buffer for later processing. */
      VStdLib_MemCpy(EthTSyn_GetAddrSwtMgmtRcvdMsgBuf(rcvdMsgBufStartIdx), DataPtr, LenByte); /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */ /* VCA_ETHTSYN_SWT_MGMT_RX_BUF_MEM_CPY */

      /* #202 Change the state of the Rx buffer to PENDING. */
      EthTSyn_SetStateOfSwtMgmtRxBuf(freeRxBufIdx, ETHTSYN_PENDING_STATEOFSWTMGMTRXBUF);
    }
    /* #30 Otherwise, drop the message and release the EthTSyn Rx buffer. */
    else
    {
      errorId = ETHTSYN_SWT_MGMT_E_GET_RX_MGMT_OBJ_FAILED;
      EthTSyn_SetStateOfSwtMgmtRxBuf(freeRxBufIdx, ETHTSYN_RELEASE_STATEOFSWTMGMTRXBUF);
    }
  }

  return errorId;
} /* EthTSyn_SwtMgmt_Rx_HndlMsgReception() */

/**********************************************************************************************************************
 *  TX
 *********************************************************************************************************************/
# if (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_Tx_SetupTxMgmtObj
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
 */
/* PRQA S 6050 1 */ /* MD_EthTSyn_6050_CslAccess */
FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_Tx_SetupTxMgmtObj(
                uint8                     EthIfCtrlIdx,
                uint8                     BufIdx,
  ETHTSYN_P2VAR(EthTSyn_TsMgmtStructType) IngressTsMgmtPtr,
  ETHTSYN_P2VAR(EthTSyn_TsMgmtStructType) EgressTsMgmtPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthTSyn_TsStateEnumType tsState = ETHTSYN_TS_S_INVALID;
  uint8 freeTxMgmtObjIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Get a free Tx management object. */
  freeTxMgmtObjIdx = EthTSyn_SwtMgmt_TxMgmtObjHndl_GetFreeIdx();
  if(freeTxMgmtObjIdx < EthTSyn_GetSizeOfSwtMgmtTxMgmtObj())
  {
    const EthTSyn_SwtMgmtMgmtObjHndlIdxOfSwtMgmtTxMgmtObjCfgType mgmtObjHndlIdx =
      EthTSyn_GetSwtMgmtMgmtObjHndlIdxOfSwtMgmtTxMgmtObjCfg(freeTxMgmtObjIdx);

    /* #20 Get the switch management object via EthIf_GetTxMgmtObject().
           If getting the switch management object was successful. */
    if(EthIf_GetTxMgmtObject(EthIfCtrlIdx, BufIdx,
      EthTSyn_GetAddrEthSwtMgmtObjPtrOfSwtMgmtMgmtObjHndl(mgmtObjHndlIdx)) == E_OK)
    {
      /* #200 Map the state machine to the Tx management object and mark it as pending. */
      EthTSyn_SetCtrlIdxOfSwtMgmtTxMgmtObj(freeTxMgmtObjIdx, EthTSyn_Util_GetEthTSynCtrlFromEthIfCtrl(EthIfCtrlIdx));
      EthTSyn_SetSmIngressTsMgmtPtrOfSwtMgmtTxMgmtObj(freeTxMgmtObjIdx, IngressTsMgmtPtr);
      EthTSyn_SetSmEgressTsMgmtPtrOfSwtMgmtTxMgmtObj(freeTxMgmtObjIdx, EgressTsMgmtPtr);
      EthTSyn_SetStateOfSwtMgmtTxMgmtObj(freeTxMgmtObjIdx, ETHTSYN_PENDING_STATEOFSWTMGMTTXMGMTOBJ);

      tsState = ETHTSYN_TS_S_PENDING;
    }
    /* #30 Otherwise, mark the Tx management object as to be released. */
    else
    {
      EthTSyn_SetStateOfSwtMgmtTxMgmtObj(freeTxMgmtObjIdx, ETHTSYN_RELEASE_STATEOFSWTMGMTTXMGMTOBJ);
    }
  }

  /* #40 Set requested timestamp states. */
  if(IngressTsMgmtPtr != NULL_PTR)
  {
    IngressTsMgmtPtr->State = tsState;
  }
  if(EgressTsMgmtPtr != NULL_PTR)
  {
    EgressTsMgmtPtr->State = tsState;
  }
} /* EthTSyn_SwtMgmt_Tx_SetupTxMgmtObj() */
# endif /* (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON) */

/**********************************************************************************************************************
 *  SITE SYNC SYNC STATE MACHINE
 *********************************************************************************************************************/
# if (ETHTSYN_SITESYNCSYNCSM == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_SiteSyncSync_ProcSm
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
 */
FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_SiteSyncSync_ProcSm(
  EthTSyn_TimeDomainIterType TimeDomainIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  const EthTSyn_SiteSyncSyncSmIdxOfTimeDomainType siteSyncSyncSmIdx =
    EthTSyn_GetSiteSyncSyncSmIdxOfTimeDomain(TimeDomainIdx);
  /*@ assert siteSyncSyncSmIdx < EthTSyn_GetSizeOfSiteSyncSyncSm(); */                                                 /* VCA_ETHTSYN_INT_FUNC_IDX_PARAM */
  EthTSyn_SiteSyncSyncSmPtrType siteSyncSyncSmPtr = EthTSyn_GetAddrSiteSyncSyncSm(siteSyncSyncSmIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Handle the cyclic transmission counter. */
  if(siteSyncSyncSmPtr->SyncTimeoutHndl.CycleCnt > 0u)
  {
    siteSyncSyncSmPtr->SyncTimeoutHndl.CycleCnt--;
  }

  /* #20 Check the state of the SiteSyncSync state machine. */
  switch(siteSyncSyncSmPtr->State)
  {
    /* #30 If state of SiteSyncSync state machine is PENDING. */
    case ETHTSYN_S_SSS_SM_PENDING:
      {
        /* #300 Handle the PENDING state. */
        EthTSyn_SwtMgmt_SiteSyncSync_HndlPendingState(TimeDomainIdx);
        break;
      }

    /* #40 If state of SiteSyncSync state machine is TX_SYNC. */
  case ETHTSYN_S_SSS_SM_TX_SYNC:
    {
      /* #400 Handle Send Sync state. */
      EthTSyn_SwtMgmt_SiteSyncSync_HndlTxSyncState(TimeDomainIdx);
      break; /* END: ETHTSYN_SITE_SYNC_SYNC_SM_SEND_SYNC */
    }

    /* #50 If state of SiteSyncSync state machine is TX_FUP. */
  case ETHTSYN_S_SSS_SM_TX_FUP:
    {
      /* #500 Handle Send FollowUp state. */
      EthTSyn_SwtMgmt_SiteSyncSync_HndlTxFupState(TimeDomainIdx);
      break; /* END: ETHTSYN_S_SSS_SM_TX_FUP */
    }

    /* #60 Otherwise, do nothing. */
  default:
    {
      /* Nothing to do here. */
      break;
    }
  }
} /* EthTSyn_SwtMgmt_SiteSyncSync_ProcSm() */

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_SiteSyncSync_HndlSyncTimeout
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
 */
FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_SiteSyncSync_HndlSyncTimeout(
  EthTSyn_IntTimeDomainIdxType TimeDomainIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  const EthTSyn_SiteSyncSyncSmIdxOfTimeDomainType siteSyncSyncSmIdx =
      EthTSyn_GetSiteSyncSyncSmIdxOfTimeDomain(TimeDomainIdx);
  EthTSyn_SiteSyncSyncSmPtrType siteSyncSyncSmPtr = EthTSyn_GetAddrSiteSyncSyncSm(siteSyncSyncSmIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 If the current buffered sync message does not match the follow up massage. */
  if(siteSyncSyncSmPtr->RcvdSyncMsgHndl.MsgHndl.RcvdMsgSequenceId !=
      siteSyncSyncSmPtr->RcvdFupMsgHndl.MsgHndl.RcvdMsgSequenceId)
  {
    /* #100 Restore the last valid buffered sync massage. This massage will match the follow up massage.  */
    /* PRQA S 0315 3 */ /* MD_MSR_VStdLibCopy */
    VStdLib_MemCpy(&siteSyncSyncSmPtr->RcvdSyncMsgHndl,                                                                /* VCA_ETHTSYN_MEM_CPY_SIZE_OF */
      &siteSyncSyncSmPtr->SyncTimeoutHndl.LastValidRcvdSync,
      sizeof(EthTSyn_SiteSyncSyncSmRcvdSyncMsgHndlType));
  }

  /* #20 Check if the sync ingress timestamp is available. */
#  if (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON)
  if(siteSyncSyncSmPtr->RcvdSyncMsgHndl.SwtIngressTsMgmt.State == ETHTSYN_TS_S_AVAILABLE)
#  else
  if(siteSyncSyncSmPtr->RcvdSyncMsgHndl.HostIngressIntVltMgmt.IntVltValid == TRUE)
#  endif /* (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON) */
  {
    /* #200 Prepare cyclic message forwarding during sync timeout. */
    siteSyncSyncSmPtr->SyncTimeoutHndl.SequenceId = siteSyncSyncSmPtr->RcvdSyncMsgHndl.MsgHndl.RcvdMsgSequenceId;
    /* Set cycle counter to one to transmit the first Sync within the next main function */
    siteSyncSyncSmPtr->SyncTimeoutHndl.CycleCnt = 1u;
    siteSyncSyncSmPtr->SyncTimeoutHndl.CycleCntStartVal =
      EthTSyn_SwtMgmt_SiteSyncSync_GetSyncCycleFromSyncMsg(siteSyncSyncSmPtr->RcvdSyncMsgHndl.MsgHndl.RcvdMsg);

    /* #201 Set the sync timeout detected flag. */
    siteSyncSyncSmPtr->SyncRxTimeoutDetected = TRUE;
  }

  /* #30 Change the state of the site sync sync state machine to PENDING. */
  siteSyncSyncSmPtr->State = ETHTSYN_S_SSS_SM_PENDING;
} /* EthTSyn_SwtMgmt_SiteSyncSync_HndlSyncTimeout() */

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_SiteSyncSync_CpySync
 *********************************************************************************************************************/
 /*!
  * Internal comment removed.
 *
 *
 *
  */
 /* PRQA S 6050 1 */ /* MD_EthTSyn_6050_CslAccess */
FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_SiteSyncSync_CpySync(
                EthTSyn_PortIdxOfMasterPortType PortIdx,
  ETHTSYN_P2VAR(uint8)                          BufferPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  const EthTSyn_TimeDomainIdxOfPortType timeDomainIdx = EthTSyn_GetTimeDomainIdxOfPort(PortIdx);
  const EthTSyn_SiteSyncSyncSmIdxOfTimeDomainType siteSyncSyncSmIdx =
    EthTSyn_GetSiteSyncSyncSmIdxOfTimeDomain(timeDomainIdx);
  /*@ assert siteSyncSyncSmIdx < EthTSyn_GetSizeOfSiteSyncSyncSm(); */                                                 /* VCA_ETHTSYN_INT_FUNC_IDX_PARAM */
  ETHTSYN_CONSTP2CONST(EthTSyn_SiteSyncSyncSmType) siteSyncSyncSmPtr = EthTSyn_GetAddrSiteSyncSyncSm(siteSyncSyncSmIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Copy Sync message from SiteSyncSync state machine to TxBuffer. */
  /*@ assert $lengthOf(BufferPtr) >= ETHTSYN_MSG_SYNC_LENGTH; */
  VStdLib_MemCpy(BufferPtr, siteSyncSyncSmPtr->RcvdSyncMsgHndl.MsgHndl.RcvdMsg, ETHTSYN_MSG_SYNC_LENGTH); /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */ /* VCA_ETHTSYN_MEM_CPY_LEN_ASSERTED */

  /* #20 Manipulate SourcePortIdentity fields within the message header if required. */
  if(EthTSyn_IsSwtMgmtKeepSrcPortIdentityOfTimeDomain(timeDomainIdx) == FALSE)
  {
    /* Use 'Own' source port identity */
    const uint16 portNumber = (uint16)EthTSyn_GetNumberOfPort(PortIdx);
    const EthTSyn_CtrlIdxOfPortType ctrlIdx = EthTSyn_GetCtrlIdxOfPort(PortIdx);
    ETHTSYN_CONSTP2CONST(EthTSyn_CtrlStateType) ctrlStatePtr = EthTSyn_GetAddrCtrlState(ctrlIdx);

    IpBase_PutUint64(BufferPtr, ETHTSYN_MSG_HDR_SRC_PORT_IDENT_CLOCK_IDENT_OFS, ctrlStatePtr->ClockIdentity);

    IpBase_PutUint16(BufferPtr, ETHTSYN_MSG_HDR_SRC_PORT_IDENT_PORT_NUM_OFS, portNumber);
  }
} /* EthTSyn_SwtMgmt_SiteSyncSync_CpySync() */

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_SiteSyncSync_CpyFup
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
/* PRQA S 6050 1 */ /* MD_EthTSyn_6050_CslAccess */
FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_SiteSyncSync_CpyFup(
                EthTSyn_PortIdxOfMasterPortType  PortIdx,
  ETHTSYN_P2VAR(uint8)                           BufferPtr,
                uint16                           LenByte)
{
  /* ----- Local Variables ---------------------------------------------- */
  const EthTSyn_TimeDomainIdxOfPortType timeDomainIdx = EthTSyn_GetTimeDomainIdxOfPort(PortIdx);
  const EthTSyn_SiteSyncSyncSmIdxOfTimeDomainType siteSyncSyncSmIdx =
    EthTSyn_GetSiteSyncSyncSmIdxOfTimeDomain(timeDomainIdx);
  /*@ assert siteSyncSyncSmIdx < EthTSyn_GetSizeOfSiteSyncSyncSm(); */                                                 /* VCA_ETHTSYN_INT_FUNC_IDX_PARAM */
  ETHTSYN_CONSTP2CONST(EthTSyn_SiteSyncSyncSmType) siteSyncSyncSmPtr = EthTSyn_GetAddrSiteSyncSyncSm(siteSyncSyncSmIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Copy the FollowUp message from SideSyncSync state machine to TxBuffer. */
  VStdLib_MemCpy(BufferPtr, siteSyncSyncSmPtr->RcvdFupMsgHndl.MsgHndl.RcvdMsg, LenByte); /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */ /* VCA_ETHTSYN_MEM_CPY_LEN_ASSERTED */

  /* #20 Manipulate the SourcePortIdentity if required. */
  if(EthTSyn_IsSwtMgmtKeepSrcPortIdentityOfTimeDomain(timeDomainIdx) == FALSE)
  {
    /* Use 'Own' source port identity */
    const uint16 portNumber = (uint16)EthTSyn_GetNumberOfPort(PortIdx);
    const EthTSyn_CtrlIdxOfPortType ctrlIdx = EthTSyn_GetCtrlIdxOfPort(PortIdx);
    ETHTSYN_CONSTP2CONST(EthTSyn_CtrlStateType) ctrlStatePtr = EthTSyn_GetAddrCtrlState(ctrlIdx);

    IpBase_PutUint64(BufferPtr, ETHTSYN_MSG_HDR_SRC_PORT_IDENT_CLOCK_IDENT_OFS, ctrlStatePtr->ClockIdentity);

    IpBase_PutUint16(BufferPtr, ETHTSYN_MSG_HDR_SRC_PORT_IDENT_PORT_NUM_OFS, portNumber);
  }

  /* #30 Compute and set the FollowUp correction field. */
  EthTSyn_SwtMgmt_SiteSyncSync_CalcAndSetFupCorrField(PortIdx, BufferPtr);

  /* #40 Update the TimeSecured Sub-TLV CRC if required (if message compliance is disabled) */
#  if (ETHTSYN_MESSAGE_COMPLIANCE == STD_OFF)
  EthTSyn_SwtMgmt_SiteSyncSync_UpdateTimeSecuredSubTlvCrc(PortIdx, BufferPtr);
#  endif /* (ETHTSYN_MESSAGE_COMPLIANCE == STD_OFF) */
} /* EthTSyn_SwtMgmt_SiteSyncSync_CpyFup() */
# endif /* (ETHTSYN_SITESYNCSYNCSM == STD_ON) */

# define ETHTSYN_STOP_SEC_CODE
# include "EthTSyn_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* ETHTSYN_SWT_MGMT_SUPPORT */

/* Justification for module-specific MISRA deviations:
 * see file EthTSyn.c
*/

/**********************************************************************************************************************
 *  END OF FILE: EthTSyn_SwtMgmt.c
 *********************************************************************************************************************/
