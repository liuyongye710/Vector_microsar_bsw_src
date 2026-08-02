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
/*!        \file  EthTSyn_Slave_Int.c
 *        \brief  EthTSyn Slave source file - Internal Functions
 *      \details  EthTSyn Slave source file containing the EthTSyn Slave implementation of the EthTSyn module.
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

#define ETHTSYN_SLAVE_INT_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "EthTSyn_Slave_Int.h" /* PRQA S 3219, 0883 */ /* MD_EthTSyn_3219, MD_EthTSyn_0883 */

#if (ETHTSYN_SLAVE_SUPPORT == STD_ON)
# include "EthTSyn_Pdelay_Int.h"
# include "EthTSyn_SwtMgmt_Int.h"
# include "EthTSyn_Crc_Int.h"
# if (ETHTSYN_SLAVE_TIME_VALIDATION_SUPPORT == STD_ON)
#  include "EthTSyn_TimeValidation_Int.h"
# endif /* (ETHTSYN_SLAVE_TIME_VALIDATION_SUPPORT == STD_ON) */
/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/

/* Check the version of EthTSyn header file */
# if (  (ETHTSYN_SW_MAJOR_VERSION != (14u)) \
     || (ETHTSYN_SW_MINOR_VERSION != (0u)) \
     || (ETHTSYN_SW_PATCH_VERSION != (0u)) )
#  error "Vendor specific version numbers of EthTSyn_Slave_Int.c and EthTSyn.h are inconsistent"
# endif

/* Check the version of the configuration header file */
# if (  (ETHTSYN_CFG_MAJOR_VERSION != (14u)) \
     || (ETHTSYN_CFG_MINOR_VERSION != (0u)) )
#  error "Version numbers of EthTSyn_Slave_Int.c and EthTSyn_Cfg.h are inconsistent!"
# endif

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/

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
 *  EthTSyn_Slave_InitPortInternal
 *********************************************************************************************************************/
/*! \brief      Initializes the passed Slave-Port.
 *  \details    Initializes all component variables directly related to the passed EthTSyn Slave-Port.
 *  \param[in]  SlavePortIdx  Index of the slave port
 *                            [range: SlavePortIdx < EthTSyn_GetSizeOfSlavePort()]
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *  \spec
 *    requires SlavePortIdx < EthTSyn_GetSizeOfSlavePort();
 *  \endspec
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_Slave_InitPortInternal(
  EthTSyn_SlavePortIterType SlavePortIdx);

/**********************************************************************************************************************
 *  EthTSyn_Slave_ProcessSmSyncReceive
 *********************************************************************************************************************/
/*! \brief      Handles the processing of the Sync Receive state-machine for the passed Slave-Port.
 *  \details    -
 *  \param[in]  SlavePortIdx    Index of the slave port which state-machine should be processed
 *                              [range: SlavePortIdx < EthTSyn_GetSizeOfSlavePort()]
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different Slave-Port indices
 *  \spec
 *    requires SlavePortIdx < EthTSyn_GetSizeOfSlavePort();
 *  \endspec
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_Slave_ProcessSmSyncReceive(
  EthTSyn_SlavePortIterType SlavePortIdx);

# if (ETHTSYN_ANNOUNCE_RX_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_Slave_ProcessSmAnnounceReceive
 *********************************************************************************************************************/
/*! \brief      Processing of the Announce receive state-machine for the passed Slave-Port.
 *  \details    -
 *  \param[in]  SlavePortIdx    Index of the slave port which state-machine should be processed
 *                              [range: SlavePortIdx < EthTSyn_GetSizeOfSlavePort()]
 *  \pre        Constraint for SlavePortIdx: EthTSyn_IsAnnounceInfoUsedOfSlavePort() == TRUE
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different Slave-Port indices
 *  \spec
 *    requires SlavePortIdx < EthTSyn_GetSizeOfSlavePort();
 *  \endspec
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_Slave_ProcessSmAnnounceReceive(
  EthTSyn_SlavePortIterType SlavePortIdx);
# endif /* (ETHTSYN_ANNOUNCE_RX_SUPPORT == STD_ON) */

/**********************************************************************************************************************
 *  EthTSyn_SlaveRx_IsPortReadyToReceiveSync
 *********************************************************************************************************************/
/*! \brief      Checks if the passed Port is ready to receive a sync message.
 *  \details    Checks the PortRole, AsCapableState, SyncReceiveSm state and handles the
 *              Master-Slave-Conflict Detection.
 *  \param[in]  PortIdx             Index of EthTSyn port that shall receive the sync message
 *                                  [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \return     TRUE - Port is ready to receive the sync message
 *  \return     FALSE - Port is not ready to receive the sync message
 *  \pre        Constraint for PortIdx: EthTSyn_IsSlavePortUsedOfPort() == TRUE
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *  \spec
 *    requires PortIdx < EthTSyn_GetSizeOfPort();
 *  \endspec
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_SlaveRx_IsPortReadyToReceiveSync(
  EthTSyn_IntPortIdxType    PortIdx);

# if (ETHTSYN_MESSAGE_COMPLIANCE == STD_OFF)
/**********************************************************************************************************************
 *  EthTSyn_SlaveRx_HandleArFollowUpTlvs
 *********************************************************************************************************************/
/*! \brief         Handles the AUTOSAR (Sub-)Tlvs included in a FollowUp message.
 *  \details       This function validates the CRC of each AR (Sub-)Tlv included in the received FollowUp message
 *                 (if applicable), extracts the Status and UserData from the corresponding Sub-Tlv and handles the
 *                 Offset TimeDomain Sub-Tlvs.
 *  \param[in]     PortIdx            Index of the Port the message was received on
 *                                    [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \param[in]     RxBufPtr           Pointer to the Ethernet reception buffer of the received FollowUp message
 *  \param[in]     SyncIngressIntVlt  The sync ingress timestamp as internal virtual local time
 *  \param[out]    StatusPtr          Pointer to where to store the retrieved Status
 *  \param[in,out] UserDataPtr        In:  Pointer to Pointer to where to store the extracted UserData
 *                                    Out: NULL_PTR if UserData are not applicable
 *  \return        E_OK - Successfully retrieved handled Tlvs. FollowUp message can be received
 *  \return        E_NOT_OK - Failed to process the SubTlvs.
 *  \pre           Constraint for PortIdx: EthTSyn_IsSlavePortUsedOfPort() == TRUE
 *  \context       TASK|ISR2
 *  \reentrant     TRUE for different Port indices
 *  \spec
 *    requires PortIdx < EthTSyn_GetSizeOfPort();
 *  \endspec
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_SlaveRx_HandleArFollowUpTlvs(
                  EthTSyn_IntPortIdxType             PortIdx,
  ETHTSYN_P2CONST(uint8)                             RxBufPtr,
                  EthTSyn_IntVltType                 SyncIngressIntVlt,
    ETHTSYN_P2VAR(StbM_TimeBaseStatusType)           StatusPtr,
    ETHTSYN_P2VAR(ETHTSYN_P2VAR(StbM_UserDataType))  UserDataPtrPtr);

/**********************************************************************************************************************
 *  EthTSyn_SlaveRx_CheckArSubTlvCrc
 *********************************************************************************************************************/
/*! \brief      Validates the Type and the Crc (if applicable) of the given FollowUp Ar Sub-Tlv.
 *  \details    -
 *  \param[in]  PortIdx            Index of the Port the FollowUp message was received on
 *                                 [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \param[in]  RxBufPtr           Pointer to the Ethernet reception buffer of the received FollowUp message
 *  \param[in]  ArSubTlvOfs        Offset of the potential ArSubTlv within the received FollowUp message
 *  \return     E_OK - Check of Ar Sub Tlv passed.
 *  \return     E_NOT_OK - Check of Ar Sub Tlv failed.
 *  \pre        Constraint for PortIdx: EthTSyn_IsSlavePortUsedOfPort() == TRUE
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *  \spec
 *    requires PortIdx < EthTSyn_GetSizeOfPort();
 *  \endspec
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_SlaveRx_CheckArSubTlvCrc(
                  EthTSyn_IntPortIdxType  PortIdx,
  ETHTSYN_P2CONST(uint8)                  RxBufPtr,
                  uint32_least            ArSubTlvOfs);

#  if (ETHTSYN_OFS_TIME_DOMAIN_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_SlaveRx_HandleOfsSubTlvs
 *********************************************************************************************************************/
/*! \brief      Unpacks all Ofs-Sub-Tlvs and forwards the new Offset to the StbM.
 *  \details    -
 *  \param[in]  TimeDomainIdx      Index of the TimeDomain the FollowUp was received for
 *                                 [range: TimeDomainIdx < EthTSyn_GetSizeOfTimeDomain()]
 *  \param[in]  RxBufPtr           Pointer to the Ethernet reception buffer of the received FollowUp message
 *  \param[in]  SyncIngressIntVlt  The sync ingress timestamp as internal virtual local time
 *  \param[in]  SubTlvCount        The amount of the Ar Sub-Tlvs (including unknown Tlv-Types)
 *  \pre        The Pointer to the FirstSubTlv and the SubTlvCount must have been retrieved using
 *              EthTSyn_SlaveRx_GetFirstArSubTlvPtrAndCnt
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different TimeDomain indices
 *  \spec
 *    required TimeDomainIdx < EthTSyn_GetSizeOfTimeDomain();
 *  \endspec
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SlaveRx_HandleOfsSubTlvs(
                  EthTSyn_IntTimeDomainIdxType TimeDomainIdx,
  ETHTSYN_P2CONST(uint8)                       RxBufPtr,
                  EthTSyn_IntVltType           SyncIngressIntVlt,
                  uint8                        SubTlvCount);
#  endif /* (ETHTSYN_OFS_TIME_DOMAIN_SUPPORT == STD_ON) */

#  if (ETHTSYN_OFS_TIME_DOMAIN_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_SlaveRx_ProcessOfsSubTlv
 *********************************************************************************************************************/
/*! \brief      Processes the given Ofs Sub-Tlv.
 *  \details    Checks if the Offset TimeDomain passed via Ofs Sub-Tlv is valid for the passed TimeDomain. If it is
 *              valid, the new offset is forwarded to the StbM.
 *  \param[in]  TimeDomainIdx      Index of the TimeDomain the FollowUp was received for
 *                                 [range: TimeDomainIdx < EthTSyn_GetSizeOfTimeDomain()]
 *  \param[in]  SyncIngressIntVlt  The sync ingress timestamp as internal virtual local time
 *  \param[in]  OfsSubTlvStartPtr  Pointer to the start of the Ofs Sub-Tlv within the Ethernet reception buffer of the
 *                                 received FollowUp message
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different TimeDomain indices
 *  \spec
 *    required TimeDomainIdx < EthTSyn_GetSizeOfTimeDomain();
 *  \endspec
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SlaveRx_ProcessOfsSubTlv(
                  EthTSyn_IntTimeDomainIdxType TimeDomainIdx,
                  EthTSyn_IntVltType           SyncIngressIntVlt,
  ETHTSYN_P2CONST(uint8)                       OfsSubTlvStartPtr);
#  endif /* (ETHTSYN_OFS_TIME_DOMAIN_SUPPORT == STD_ON) */

/**********************************************************************************************************************
 *  EthTSyn_SlaveRx_GetUserDataFromSubTlv
 *********************************************************************************************************************/
/*! \brief      Checks if a UserData Sub-Tlv is present and retrieve the UserData.
 *  \details    -
 *  \param[in]  RxBufPtr        Pointer to the Ethernet reception buffer of the received FollowUp message
 *  \param[in]  SubTlvCount     The amount of the Ar Sub-Tlvs (including unknown Tlv-Types)
 *  \param[out] UserDataPtr     Pointer to where to store the retrieved UserData
 *  \return     E_OK - UserData Sub-Tlv found and successfully retrieved the UserData
 *  \return     E_NOT_OK - No UserData Sub-Tlv found or failed to retrieve the UserData
 *  \pre        The Pointer to the FirstSubTlv and the SubTlvCount must have been retrieved using
 *              EthTSyn_SlaveRx_GetFirstArSubTlvPtrAndCnt
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_SlaveRx_GetUserDataFromSubTlv(
  ETHTSYN_P2CONST(uint8)              RxBufPtr,
                  uint8               SubTlvCount,
    ETHTSYN_P2VAR(StbM_UserDataType)  UserDataPtr);

/**********************************************************************************************************************
 *  EthTSyn_SlaveRx_GetStatusFromSubTlv
 *********************************************************************************************************************/
/*! \brief      Checks if a Status Sub-Tlv is present and retrieve the Status.
 *  \details    -
 *  \param[in]  RxBufPtr        Pointer to the Ethernet reception buffer of the received FollowUp message
 *  \param[in]  SubTlvCount     The amount of the Ar Sub-Tlvs (including unknown Tlv-Types)
 *  \param[out] StatusPtr       Pointer to where to store the retrieved Status
 *  \return     E_OK - Status Sub-Tlv found and successfully retrieved the Status
 *  \return     E_NOT_OK - No Status Sub-Tlv found or failed to retrieve the Status
 *  \pre        The Pointer to the FirstSubTlv and the SubTlvCount must have been retrieved using
 *              EthTSyn_SlaveRx_GetFirstArSubTlvPtrAndCnt
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_SlaveRx_GetStatusFromSubTlv(
  ETHTSYN_P2CONST(uint8)                     RxBufPtr,
                  uint8                      SubTlvCount,
    ETHTSYN_P2VAR(StbM_TimeBaseStatusType)   StatusPtr);

/**********************************************************************************************************************
 *  EthTSyn_SlaveRx_ArSubTlvStatusToTimeBaseStatus
 *********************************************************************************************************************/
 /*! \brief         Converts the passes AUTOSAR Sub-TLV status into the StbmTimeBaseStatus.
 *  \details       -
 *  \param[in]     ArSubTlvStatus  The AUTOSAR Sub-TLV status
 *  \return        The passed AUTOSAR Sub-TLV status field as StbmTimeBaseStatus
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(StbM_TimeBaseStatusType, ETHTSYN_CODE) EthTSyn_SlaveRx_ArSubTlvStatusToTimeBaseStatus(
  uint8 ArSubTlvStatus);

# endif /* (ETHTSYN_MESSAGE_COMPLIANCE == STD_OFF) */

/**********************************************************************************************************************
 *  EthTSyn_SlaveRx_GetTimeDiffSinceSyncRx
 *********************************************************************************************************************/
/*! \brief      Computes the time passed since the reception of the corresponding Sync message.
 *  \details    -
 *  \param[in]  PortIdx                  Index of the Port the FollowUp message was received on
 *                                       [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \param[in]  SyncIngressVlt           The sync ingress timestamp as internal virtual local time
 *  \param[out] TimeDiffSinceSyncRxPtr   The time difference since the reception of the Sync message
 *  \param[out] CurrVltPtr               The current virtual local time. This value shall be used as virtual local time
 *                                       on invocation of StbM_BusSetGlobalTime.
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *  \spec
 *    requires PortIdx < EthTSyn_GetSizeOfPort();
 *  \endspec
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_SlaveRx_GetTimeDiffSinceSyncRx(
                  EthTSyn_IntPortIdxType     PortIdx,
                  EthTSyn_IntVltType         SyncIngressVlt,
    ETHTSYN_P2VAR(EthTSyn_TimediffType)      TimeDiffSinceSyncRxPtr,
    ETHTSYN_P2VAR(StbM_VirtualLocalTimeType) CurrVltPtr);

/**********************************************************************************************************************
 *  EthTSyn_SlaveRx_ProvideTimeToStbm
 *********************************************************************************************************************/
/*! \brief      Handles the call of StbM_BusSetGlobalTime() for a received FollowUp message (no Offset time domain).
 *  \details    -
 *  \param[in]  PortIdx                   Index of the Port the FollowUp message was received on
 *                                        [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \param[in]  MsgPtr                    Pointer to the Rx Buffer of the FollowUp message
 *  \param[in]  TimeDiffSinceSyncRx       The time difference passed since reception of the corresponding Sync message
 *  \param[in]  AddInfoPtr                Additional information provided to the StbM_BusSetGlobalTime:
 *                                          CurrVlt - The current virtual local time
 *                                          UserData - The User Data extracted form the UserData TLV (if present)
 *                                          TbStatus - The Time base status extracted from Status TLV (if present)
 *  \pre        Constraint for PortIdx: EthTSyn_IsSlavePortUsedOfPort() == TRUE
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different Port indices
 *  \spec
 *    requires PortIdx < EthTSyn_GetSizeOfPort();
 *  \endspec
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SlaveRx_ProvideTimeToStbm(
                  EthTSyn_IntPortIdxType                    PortIdx,
  ETHTSYN_P2CONST(uint8)                                    MsgPtr,
                  EthTSyn_TimediffType                      TimeDiffSinceSyncRx,
  ETHTSYN_P2CONST(EthTSyn_SlaveRx_BusSetGlobalTimeInfoType) AddInfoPtr);

# if (ETHTSYN_SITESYNCSYNCSM == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_Slave_SyncReceiveHandleSyncTimeout
 *********************************************************************************************************************/
/*! \brief      Checks if a sync receive timeout occurred and handles it.
 *  \details    Checks if a sync receive timeout occurred for the provided SyncReceive state machine. If so,
 *              the SyncReceive state machine is set to state ETHTSYN_S_SYNC_RCV_SM_SYNC_TIMEOUT, the SiteSyncSync
 *              state machine is set to state ETHTSYN_S_SSS_SM_SYNC_TIMEOUT and all SyncSend state machines assigned
 *              to the passed TimeDomain are set to state ETHTSYN_S_SYNC_SEND_SM_INITIALIZING.
 *  \param[in]  TimeDomainIdx     Index of the TimeDomain
 *                                [range: TimeDomainIdx < EthTSyn_GetSizeOfTimeDomain()]
 *  \param[in]  SyncReceiveSmPtr  Pointer to the Sync receive state machine
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *  \spec
 *    required TimeDomainIdx < EthTSyn_GetSizeOfTimeDomain();
 *  \endspec
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_Slave_SyncReceiveHandleSyncTimeout(
                EthTSyn_IntTimeDomainIdxType   TimeDomainIdx,
  ETHTSYN_P2VAR(EthTSyn_SyncReceiveSmType)     SyncReceiveSmPtr);
# endif /* (ETHTSYN_SITESYNCSYNCSM == STD_ON) */

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  EthTSyn_Slave_InitPortInternal
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
/* PRQA S 6050 1 */ /* MD_EthTSyn_6050_CslAccess */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_Slave_InitPortInternal(EthTSyn_SlavePortIterType SlavePortIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  ETHTSYN_P2VAR(EthTSyn_SyncReceiveSmType) syncReceiveSmPtr = EthTSyn_GetAddrSyncReceiveSm(SlavePortIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Initialize sync receive state machine. */
  VStdLib_MemClr(syncReceiveSmPtr, sizeof(EthTSyn_SyncReceiveSmType)); /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */
  syncReceiveSmPtr->PrevSeqIdValid = FALSE;

# if (ETHTSYN_SRC_PORT_IDENT_CHECK_SUPPORT == STD_ON)
  /* #20 Initialize optional master identity. */
  {
    const EthTSyn_MasterPortIdentityIdxOfSlavePortType masterPortIdentIdx =
      EthTSyn_GetMasterPortIdentityIdxOfSlavePort(SlavePortIdx);

    if(masterPortIdentIdx < EthTSyn_GetSizeOfMasterPortIdentity())
    {
      const EthTSyn_PortIdxOfSlavePortType portIdx = EthTSyn_GetPortIdxOfSlavePort(SlavePortIdx);
      const EthTSyn_TimeDomainIdxOfPortType timeDomainIdx = EthTSyn_GetTimeDomainIdxOfPort(portIdx);
      const EthTSyn_ClockIdentityOfMasterPortIdentityType clockIdentity =
        EthTSyn_GetClockIdentityOfMasterPortIdentity(masterPortIdentIdx);

      EthTSyn_SetGmPresentOfSystemState(timeDomainIdx, TRUE);
      EthTSyn_SetGmClockIdentityOfSystemState(timeDomainIdx, clockIdentity);
    }
  }
# endif /* (ETHTSYN_SRC_PORT_IDENT_CHECK_SUPPORT == STD_ON) */
} /* EthTSyn_Slave_InitPortInternal() */

/**********************************************************************************************************************
 *  EthTSyn_Slave_ProcessSmSyncReceive
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
/* PRQA S 6050 1 */ /* MD_EthTSyn_6050_CslAccess */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_Slave_ProcessSmSyncReceive(EthTSyn_SlavePortIterType SlavePortIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  ETHTSYN_CONSTP2VAR(EthTSyn_SyncReceiveSmType) syncReceiveSmPtr = EthTSyn_GetAddrSyncReceiveSm(SlavePortIdx);
# if (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON)
#  if (ETHTSYN_SWT_MGMT_BRIDGE_MODE == ETHTSYN_SWT_MGMT_BRIDGE_MODE_TRANSPARENT)
  const EthTSyn_PortIdxOfSlavePortType portIdx = EthTSyn_GetPortIdxOfSlavePort(SlavePortIdx);
  const EthTSyn_IntTimeDomainIdxType timeDomainIdx= EthTSyn_GetTimeDomainIdxOfPort(portIdx);
#  endif /* (ETHTSYN_SWT_MGMT_BRIDGE_MODE == ETHTSYN_SWT_MGMT_BRIDGE_MODE_TRANSPARENT) */
# endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON) */

  /* ----- Implementation ----------------------------------------------- */
  ETHTSYN_ENTER_CRITICAL_SECTION_0();
  /* #10 Check sync receive state machine state. */
  switch(syncReceiveSmPtr->State)
  {
  case ETHTSYN_S_SYNC_RCV_SM_WAIT_FUP:
    {
      /* #100 State: Waiting for follow up -> check for FollowUp receive timeout. */
      if(EthTSyn_GetFollowUpAllowedRxDelayOfSlavePort(SlavePortIdx) > 0u)
      {
        if(syncReceiveSmPtr->FollowUp.FollowUpRxTimeoutCnt == 0u)
        {
          syncReceiveSmPtr->State = ETHTSYN_S_SYNC_RCV_SM_WAIT_SYNC;
        }
      }
      break;
    }

# if (ETHTSYN_SITESYNCSYNCSM == STD_ON)
  case ETHTSYN_S_SYNC_RCV_SM_WAIT_SYNC:
    {
      /* #101 State: Waiting for sync (with switch management only) -> Handle possible sync timeout. */
      /* PRQA S 3415 2 */ /* MD_EthTSyn_3415_ReadOnly */
      if( (EthTSyn_GetSwtMgmtSyncTimeoutOfTimeDomain(timeDomainIdx) > 0u) &&
        (EthTSyn_Util_IsSwitchPort((EthTSyn_IntPortIdxType)portIdx) == TRUE) )
      {
        EthTSyn_Slave_SyncReceiveHandleSyncTimeout(timeDomainIdx, syncReceiveSmPtr);
      }
      break;
    }
# endif /* (ETHTSYN_SITESYNCSYNCSM == STD_ON) */
  default:
    {
      /* Nothing to do here. */
      break;
    }
  }
  ETHTSYN_LEAVE_CRITICAL_SECTION_0();

} /* EthTSyn_Slave_ProcessSmSyncReceive() */

# if (ETHTSYN_ANNOUNCE_RX_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_Slave_ProcessSmAnnounceReceive
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_Slave_ProcessSmAnnounceReceive(
  EthTSyn_SlavePortIterType SlavePortIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  const EthTSyn_PortIdxOfSlavePortType portIdx = EthTSyn_GetPortIdxOfSlavePort(SlavePortIdx);
  const EthTSyn_AnnounceInfoIdxOfSlavePortType announceInfoIdx = EthTSyn_GetAnnounceInfoIdxOfSlavePort(SlavePortIdx);
  /*@ assert announceInfoIdx < EthTSyn_GetSizeOfAnnounceInfo(); */                                                     /* VCA_ETHTSYN_INT_FUNC_IDX_PARAM */
  ETHTSYN_CONSTP2CONST(EthTSyn_AnnounceReceiveSmType) announceRcvSmPtr =
    EthTSyn_GetAddrAnnounceReceiveSm(announceInfoIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check for announce receive timeout and handle it. */
  if(announceRcvSmPtr->RxTimeoutCnt == 0u)
  {
    const EthTSyn_TimeDomainIdxOfPortType timeDomainIdx = EthTSyn_GetTimeDomainIdxOfPort(portIdx);
    EthTSyn_Slave_ResetMasterPriorityVector(timeDomainIdx);
  }

} /* EthTSyn_Slave_ProcessSmAnnounceReceive() */
# endif /* (ETHTSYN_ANNOUNCE_RX_SUPPORT == STD_ON) */

/**********************************************************************************************************************
 *  EthTSyn_SlaveRx_IsPortReadyToReceiveSync
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_SlaveRx_IsPortReadyToReceiveSync(
  EthTSyn_IntPortIdxType PortIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean isReady = FALSE;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if port is AsCapable. */
  if (EthTSyn_Util_IsAsCapable(PortIdx) == TRUE)
  {
    const EthTSyn_SlavePortIdxOfPortType slavePortIdx = EthTSyn_GetSlavePortIdxOfPort(PortIdx);
    /*@ assert slavePortIdx < EthTSyn_GetSizeOfSlavePort(); */                                                         /* VCA_ETHTSYN_INT_FUNC_IDX_PARAM */
    ETHTSYN_CONSTP2CONST(EthTSyn_SyncReceiveSmType) syncReceiveSmPtr = EthTSyn_GetAddrSyncReceiveSm(slavePortIdx);
    /* #20 Check sync receive state machine state. */
    if ((syncReceiveSmPtr->State == ETHTSYN_S_SYNC_RCV_SM_DISCARD) ||
      (syncReceiveSmPtr->State == ETHTSYN_S_SYNC_RCV_SM_WAIT_SYNC))
    {
      isReady = TRUE;
    }
  }

  return isReady;
} /* EthTSyn_SlaveRx_IsPortReadyToReceiveSync() */

# if (ETHTSYN_MESSAGE_COMPLIANCE == STD_OFF)
/**********************************************************************************************************************
 *  EthTSyn_SlaveRx_HandleArFollowUpTlvs
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
ETHTSYN_LOCAL_INLINE FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_SlaveRx_HandleArFollowUpTlvs(
                  EthTSyn_IntPortIdxType            PortIdx,
  ETHTSYN_P2CONST(uint8)                            RxBufPtr,
                  EthTSyn_IntVltType                SyncIngressIntVlt,
    ETHTSYN_P2VAR(StbM_TimeBaseStatusType)          StatusPtr,
    ETHTSYN_P2VAR(ETHTSYN_P2VAR(StbM_UserDataType)) UserDataPtrPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;
  uint8 subTlvCnt = 0u;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Handle possible FollowUp Tlvs: Get the offset of the first Ar Sub-Tlv, the Sub-Tlv count and optionally
         verify the CRC of the Sub-Tlvs. */
  retVal = EthTSyn_SlaveRx_CheckArSubTlvsAndGetCnt(PortIdx, RxBufPtr, &subTlvCnt);

  /* #20 In case the first Ar Sub-Tlv and the Sub-Tlv count could be retrieved successfully. */
  if ((retVal == E_OK) && (subTlvCnt > 0u))
  {
    /* #200 Get UserData from corresponding Sub-Tlv. */
    if (EthTSyn_SlaveRx_GetUserDataFromSubTlv(RxBufPtr, subTlvCnt, (*UserDataPtrPtr)) == E_NOT_OK)
    {
      /* #2000 In case retrieving the UserData failed set UserDataPtrPtr to NULL_PTR. */
      (*UserDataPtrPtr) = NULL_PTR;
    }
    /* #201 Get Status from corresponding Sub-Tlv. */
    if (EthTSyn_SlaveRx_GetStatusFromSubTlv(RxBufPtr, subTlvCnt, StatusPtr) == E_NOT_OK)
    {
      /* #2010 In case retrieving the Status failed set Status to '0'. */
      (*StatusPtr) = 0;
    }

    /* #202 Handle Offset Sub-Tlvs. */
#  if (ETHTSYN_OFS_TIME_DOMAIN_SUPPORT == STD_ON)
    EthTSyn_SlaveRx_HandleOfsSubTlvs(EthTSyn_GetTimeDomainIdxOfPort(PortIdx), RxBufPtr, SyncIngressIntVlt, subTlvCnt);
#  else
    ETHTSYN_DUMMY_STATEMENT(SyncIngressIntVlt); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#  endif /* (ETHTSYN_OFS_TIME_DOMAIN_SUPPORT == STD_ON) */
  }
  /* #30 Otherwise set UserDataPtrPtr to NULL_PTR and StatusPtr to '0' as default values for the out parameters. */
  else
  {
    (*StatusPtr) = 0;
    (*UserDataPtrPtr) = NULL_PTR;
  }

  return retVal;
} /* EthTSyn_SlaveRx_HandleArFollowUpTlvs() */

/**********************************************************************************************************************
 *  EthTSyn_SlaveRx_CheckArSubTlvCrc
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
ETHTSYN_LOCAL_INLINE FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_SlaveRx_CheckArSubTlvCrc(
                  EthTSyn_IntPortIdxType  PortIdx,
  ETHTSYN_P2CONST(uint8)                  RxBufPtr,
                  uint32_least            ArSubTlvOfs)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  const EthTSyn_SlavePortIdxOfPortType slavePortIdx = EthTSyn_GetSlavePortIdxOfPort(PortIdx);
  /*@ assert slavePortIdx < EthTSyn_GetSizeOfSlavePort(); */                                                           /* VCA_ETHTSYN_INT_FUNC_IDX_PARAM */
  const EthTSyn_RxCrcValidatedEnumType rxCrcValidated = EthTSyn_GetRxCrcValidatedOfSlavePort(slavePortIdx);
#  if (ETHTSYN_CRC_SUPPORT == STD_ON)
  const uint8 rxCrcValidatedFlags = EthTSyn_GetCrcFlagsRxValidatedOfSlavePort(slavePortIdx);
  boolean timeSecuredCrcFlagsValid = TRUE;
#  endif /* (ETHTSYN_CRC_SUPPORT == STD_ON) */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if Crc is included and matches the configuration. Validate Crc if required. */
  /* The Ar Sub Tlv type is located at ArSubTlvOfs + ETHTSYN_MSG_FUP_AR_SUB_TLV_TYPE_OFS.
     ETHTSYN_MSG_FUP_AR_SUB_TLV_TYPE_OFS is zero and therefore can be omitted. */
  switch(IpBase_GetUint8(RxBufPtr, ArSubTlvOfs))
  {
    case ETHTSYN_AR_SUB_TLV_TYPE_TIME_SECURED:
      {
        /* #100 Time secured Tlv. Check if the CrcTimeFlags match the configuration. */
#  if (ETHTSYN_CRC_SUPPORT == STD_ON)
        /* PRQA S 4304 1 */ /* MD_MSR_AutosarBoolean */
        timeSecuredCrcFlagsValid = (boolean)(IpBase_GetUint8(RxBufPtr,
          (ArSubTlvOfs + ETHTSYN_MSG_FUP_AR_SUB_TLV_TIME_SECURED_FLAGS_OFS)) == rxCrcValidatedFlags);
#  endif /* (ETHTSYN_CRC_SUPPORT == STD_ON) */
      }
      /* no break */
    case ETHTSYN_AR_SUB_TLV_TYPE_OFS_SECURED: /* PRQA S 2003 */ /* MD_EthTSyn_2003 */
    case ETHTSYN_AR_SUB_TLV_TYPE_STATUS_SECURED:
    case ETHTSYN_AR_SUB_TLV_TYPE_USER_DATA_SECURED:
      {
        /* #101 Secured Tlv. Check if this is valid and if Crc validation is required. */
        if(rxCrcValidated == ETHTSYN_RX_CRC_VALIDATED_CRC_IGNORED)
        {
          /* #1010 Secured type valid. No validation of Crc required. */
          retVal = E_OK;
        }
#  if (ETHTSYN_CRC_SUPPORT == STD_ON)
        else if((rxCrcValidated == ETHTSYN_RX_CRC_VALIDATED_CRC_OPTIONAL) ||
          (rxCrcValidated == ETHTSYN_RX_CRC_VALIDATED_CRC_VALIDATED) )
        {
          /* #1011 Secured type valid. Validation of Crc required -> Validate Crc. */
          const uint8 dataId = EthTSyn_Util_GetFollowUpDataIdListEntry(EthTSyn_GetTimeDomainIdxOfPort(PortIdx),
            IpBase_GetUint16(RxBufPtr, ETHTSYN_MSG_HDR_SEQUENCE_ID_OFS));
          /* PRQA S 3415 2 */ /* MD_EthTSyn_3415_ReadOnly */
          if((timeSecuredCrcFlagsValid == TRUE) &&
              (EthTSyn_Crc_ValidateSubTlvCrc(dataId, RxBufPtr, ArSubTlvOfs) == TRUE))
          {
            retVal = E_OK;
          }
        }
#  endif /* (ETHTSYN_CRC_SUPPORT == STD_ON) */
        else
        {
          /* Nothing to do here. */
        }
        break;
      }

    case ETHTSYN_AR_SUB_TLV_TYPE_OFS_NOT_SECURED:
    case ETHTSYN_AR_SUB_TLV_TYPE_STATUS_NOT_SECURED:
    case ETHTSYN_AR_SUB_TLV_TYPE_USER_DATA_NOT_SECURED:
      {
        /* #102 Not Secured Sub-Tlv --> Check if this is valid. */
#  if (ETHTSYN_CRC_SUPPORT == STD_ON)
        if(rxCrcValidated != ETHTSYN_RX_CRC_VALIDATED_CRC_VALIDATED)
#  endif /* (ETHTSYN_CRC_SUPPORT == STD_ON) */
        {
          /* #1020 No Crc required -> receive message. */
          retVal = E_OK;
        }
        break;
      }

    default:
      {
        /* #103 Unknown Tlv-Type --> skip. */
        retVal = E_OK;
        break;
      }
  }

  return retVal;
} /* EthTSyn_SlaveRx_CheckArSubTlvCrc() */

#  if (ETHTSYN_OFS_TIME_DOMAIN_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_SlaveRx_HandleOfsSubTlvs
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
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SlaveRx_HandleOfsSubTlvs(
                  EthTSyn_IntTimeDomainIdxType TimeDomainIdx,
  ETHTSYN_P2CONST(uint8)                       RxBufPtr,
                  EthTSyn_IntVltType           SyncIngressIntVlt,
                  uint8                        SubTlvCount)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8_least subTlvCounter;

  /* Set 'currOfs' to the first potential Sub-Tlv. */
  uint32 currOfs = ETHTSYN_MSG_FUP_FIRST_AR_SUB_TLV_OFS;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if there are any offset time domains for the passed time domain. */
  if(EthTSyn_IsOffsetTimeDomainUsedOfTimeDomain(TimeDomainIdx) == TRUE)
  {
    /* #20 Iterate over all Sub-Tlvs. */
    for(subTlvCounter = 0u; subTlvCounter < SubTlvCount; subTlvCounter++)
    {
      ETHTSYN_P2CONST(uint8) currSubTlvStartPtr = &RxBufPtr[currOfs];
      const uint8 subTlvType = IpBase_GetUint8(currSubTlvStartPtr, ETHTSYN_MSG_FUP_AR_SUB_TLV_TYPE_OFS);

      /* #30 If current Sub-Tlv is Ofs Tlv. */
      if((subTlvType == ETHTSYN_AR_SUB_TLV_TYPE_OFS_NOT_SECURED) ||
        (subTlvType == ETHTSYN_AR_SUB_TLV_TYPE_OFS_SECURED))
      {
        /* #40 Process the offset time domain Sub-Tlv. */
        EthTSyn_SlaveRx_ProcessOfsSubTlv(TimeDomainIdx, SyncIngressIntVlt, currSubTlvStartPtr);

        /* #50 And continue with next Sub-Tlv.*/
      } /* END: if(Ofs-Sub-Tlv) */

      /* #60 Otherwise continue with next Sub-Tlv. */
      currOfs += ETHTSYN_AR_SUB_TLV_ABSTRACT_HDR_LENGTH;
      currOfs += IpBase_GetUint8(currSubTlvStartPtr, ETHTSYN_MSG_FUP_AR_SUB_TLV_LEN_OFS);
    } /* END: Iteration of Sub-Tlvs */
  } /* END: if(TimeDomain has Offset time domains) */

} /* EthTSyn_SlaveRx_HandleOfsSubTlvs() */
#  endif /* (ETHTSYN_OFS_TIME_DOMAIN_SUPPORT == STD_ON) */

#  if (ETHTSYN_OFS_TIME_DOMAIN_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_SlaveRx_ProcessOfsSubTlv
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
/* PRQA S 6050 1 */ /* MD_EthTSyn_6050_CslAccess */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SlaveRx_ProcessOfsSubTlv(
                  EthTSyn_IntTimeDomainIdxType TimeDomainIdx,
                  EthTSyn_IntVltType           SyncIngressIntVlt,
  ETHTSYN_P2CONST(uint8)                       OfsSubTlvStartPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthTSyn_OffsetTimeDomainIterType ofsTimeDomainIter;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Search matching offset time domain by iterating all offset time domains for the TimeDomain of the FollowUp. */
  for(ofsTimeDomainIter = EthTSyn_GetOffsetTimeDomainStartIdxOfTimeDomain(TimeDomainIdx);
      ofsTimeDomainIter < EthTSyn_GetOffsetTimeDomainEndIdxOfTimeDomain(TimeDomainIdx);
      ofsTimeDomainIter++)
  {
    /*@ assert ofsTimeDomainIter < EthTSyn_GetSizeOfOffsetTimeDomain(); */                                             /* VCA_ETHTSYN_0_N_IND_CSL03 */
    const uint8 ofsTimeDomainId =
      IpBase_GetUint8(OfsSubTlvStartPtr, ETHTSYN_MSG_FUP_AR_SUB_TLV_OFS_OFS_DOMAIN_NUM_OFS);

    if(ofsTimeDomainId == EthTSyn_GetIdOfOffsetTimeDomain(ofsTimeDomainIter))
    {
      /* #20 Matching Offset TimeDomain found -> Forward new offset to StbM. */
      StbM_TimeStampType timeStamp;
      StbM_UserDataType userData;
      StbM_MeasurementType measureData;
      const StbM_SynchronizedTimeBaseType synchronizedTimeBaseId =
          EthTSyn_GetSynchronizedTimeBaseIdOfOffsetTimeDomain(ofsTimeDomainIter);
      const uint8 ofsSubTlvStatus = IpBase_GetUint8(OfsSubTlvStartPtr, ETHTSYN_MSG_FUP_AR_SUB_TLV_OFS_STATUS_OFS);
      StbM_VirtualLocalTimeType syncIngressVlt;

      syncIngressVlt = EthTSyn_UtilVlt_IntVltToVlt(SyncIngressIntVlt);
      timeStamp.timeBaseStatus = EthTSyn_SlaveRx_ArSubTlvStatusToTimeBaseStatus(ofsSubTlvStatus);

      timeStamp.secondsHi = IpBase_GetUint16(OfsSubTlvStartPtr, ETHTSYN_MSG_FUP_AR_SUB_TLV_OFS_OFS_TIME_SEC_HI_OFS);
      timeStamp.seconds = IpBase_GetUint32(OfsSubTlvStartPtr, ETHTSYN_MSG_FUP_AR_SUB_TLV_OFS_OFS_TIME_SEC_LOW_OFS);
      timeStamp.nanoseconds = IpBase_GetUint32(OfsSubTlvStartPtr, ETHTSYN_MSG_FUP_AR_SUB_TLV_OFS_OFS_TIME_NSEC_OFS);

      userData.userDataLength = IpBase_GetUint8(OfsSubTlvStartPtr, ETHTSYN_MSG_FUP_AR_SUB_TLV_OFS_USER_DATA_LEN_OFS);
      userData.userByte0 = IpBase_GetUint8(OfsSubTlvStartPtr, ETHTSYN_MSG_FUP_AR_SUB_TLV_OFS_USER_DATA_BYTE_0_OFS);
      userData.userByte1 = IpBase_GetUint8(OfsSubTlvStartPtr, ETHTSYN_MSG_FUP_AR_SUB_TLV_OFS_USER_DATA_BYTE_1_OFS);
      userData.userByte2 = IpBase_GetUint8(OfsSubTlvStartPtr, ETHTSYN_MSG_FUP_AR_SUB_TLV_OFS_USER_DATA_BYTE_2_OFS);

      /* Pdelay not required for Offset TimeDomains. Therefore it can be set to '0' */
      measureData.pathDelay = 0u;

      (void)StbM_BusSetGlobalTime(synchronizedTimeBaseId, &timeStamp, &userData, &measureData, &syncIngressVlt);

      break;
    }
  } /* END: Iteration of Offset time domains */
} /* EthTSyn_SlaveRx_ProcessOfsSubTlv() */
#  endif /* (ETHTSYN_OFS_TIME_DOMAIN_SUPPORT == STD_ON) */

/**********************************************************************************************************************
 *  EthTSyn_SlaveRx_GetUserDataFromSubTlv
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
ETHTSYN_LOCAL_INLINE FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_SlaveRx_GetUserDataFromSubTlv(
  ETHTSYN_P2CONST(uint8)              RxBufPtr,
                  uint8               SubTlvCount,
    ETHTSYN_P2VAR(StbM_UserDataType)  UserDataPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  uint8_least subTlvCounter;
  /* Set 'currOfs' to the first potential Sub-Tlv. */
  uint32 currOfs = ETHTSYN_MSG_FUP_FIRST_AR_SUB_TLV_OFS;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate all Ar Sub-Tlvs. */
  for(subTlvCounter = 0; subTlvCounter < SubTlvCount; subTlvCounter++)
  {
    ETHTSYN_P2CONST(uint8) currSubTlvStartPtr = &RxBufPtr[currOfs];
    const uint8 subTlvType = IpBase_GetUint8(currSubTlvStartPtr, ETHTSYN_MSG_FUP_AR_SUB_TLV_TYPE_OFS);
    /* #20 If current Sub-Tlv is UserData Tlv. */
    if((subTlvType == ETHTSYN_AR_SUB_TLV_TYPE_USER_DATA_NOT_SECURED) ||
      (subTlvType == ETHTSYN_AR_SUB_TLV_TYPE_USER_DATA_SECURED))
    {
      /* #30 Store the UserData. */
      UserDataPtr->userDataLength =
        IpBase_GetUint8(currSubTlvStartPtr, ETHTSYN_MSG_FUP_AR_SUB_TLV_USER_DATA_UD_LEN_OFS);
      UserDataPtr->userByte0 =
        IpBase_GetUint8(currSubTlvStartPtr, ETHTSYN_MSG_FUP_AR_SUB_TLV_USER_DATA_UD_BYTE_0_OFS);
      UserDataPtr->userByte1 =
        IpBase_GetUint8(currSubTlvStartPtr, ETHTSYN_MSG_FUP_AR_SUB_TLV_USER_DATA_UD_BYTE_1_OFS);
      UserDataPtr->userByte2 =
        IpBase_GetUint8(currSubTlvStartPtr, ETHTSYN_MSG_FUP_AR_SUB_TLV_USER_DATA_UD_BYTE_2_OFS);

      retVal = E_OK;

      /* #40 And stop iteration of Sub-Tlvs. */
      break;
    }

    /* #50 Otherwise continue with next Sub-Tlv. */
    /* Increment the offset by the value of the Sub-Tlv length field and the length of the Sub-Tlv header which is not
       included in the length field. */
    currOfs += ETHTSYN_AR_SUB_TLV_ABSTRACT_HDR_LENGTH;
    currOfs += IpBase_GetUint8(currSubTlvStartPtr, ETHTSYN_MSG_FUP_AR_SUB_TLV_LEN_OFS);
  }

  return retVal;
} /* EthTSyn_SlaveRx_GetUserDataFromSubTlv() */

/**********************************************************************************************************************
 *  EthTSyn_SlaveRx_GetStatusFromSubTlv
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
ETHTSYN_LOCAL_INLINE FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_SlaveRx_GetStatusFromSubTlv(
  ETHTSYN_P2CONST(uint8)                    RxBufPtr,
                  uint8                     SubTlvCount,
    ETHTSYN_P2VAR(StbM_TimeBaseStatusType)  StatusPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  uint8_least subTlvCounter;

  /* Set 'currOfs' to the first potential Sub-Tlv. */
  uint32 currOfs = ETHTSYN_MSG_FUP_FIRST_AR_SUB_TLV_OFS;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate all Ar Sub-Tlvs. */
  for(subTlvCounter = 0; subTlvCounter < SubTlvCount; subTlvCounter++)
  {
    ETHTSYN_P2CONST(uint8) currSubTlvStartPtr = &RxBufPtr[currOfs];
    const uint8 subTlvType = IpBase_GetUint8(currSubTlvStartPtr, ETHTSYN_MSG_FUP_AR_SUB_TLV_TYPE_OFS);

    /* #20 If current Sub-Tlv is Status Tlv. */
    if((subTlvType == ETHTSYN_AR_SUB_TLV_TYPE_STATUS_NOT_SECURED) ||
      (subTlvType == ETHTSYN_AR_SUB_TLV_TYPE_STATUS_SECURED))
    {
      /* #30 Store the Status. */
      const uint8 arSubTlvStatus = IpBase_GetUint8(currSubTlvStartPtr, ETHTSYN_MSG_FUP_AR_SUB_TLV_STATUS_STATUS_OFS);

      (*StatusPtr) = EthTSyn_SlaveRx_ArSubTlvStatusToTimeBaseStatus(arSubTlvStatus);

      retVal = E_OK;

      /* #40 And stop iteration of Sub-Tlvs. */
      break;
    }

    /* #50 Otherwise continue with next Sub-Tlv. */
    /* Increment the offset by the value of the Sub-Tlv length field and the length of the Sub-Tlv header which is not
       included in the length field. */
    currOfs += ETHTSYN_AR_SUB_TLV_ABSTRACT_HDR_LENGTH;
    currOfs += IpBase_GetUint8(currSubTlvStartPtr, ETHTSYN_MSG_FUP_AR_SUB_TLV_LEN_OFS);
  }

  return retVal;
} /* EthTSyn_SlaveRx_GetStatusFromSubTlv() */

/**********************************************************************************************************************
 *  EthTSyn_SlaveRx_ArSubTlvStatusToTimeBaseStatus
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(StbM_TimeBaseStatusType, ETHTSYN_CODE) EthTSyn_SlaveRx_ArSubTlvStatusToTimeBaseStatus(
  uint8 ArSubTlvStatus)
{
  return (StbM_TimeBaseStatusType)(
    (ArSubTlvStatus << ETHTSYN_TIME_BASE_STATUS_SYNC_TO_GW_SHIFT) & ETHTSYN_TIME_BASE_STATUS_SYNC_TO_GW_MASK);
} /* EthTSyn_SlaveRx_ArSubTlvStatusToTimeBaseStatus() */

# endif /* (ETHTSYN_MESSAGE_COMPLIANCE == STD_OFF) */

/**********************************************************************************************************************
 *  EthTSyn_SlaveRx_GetTimeDiffSinceSyncRx
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
ETHTSYN_LOCAL_INLINE FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_SlaveRx_GetTimeDiffSinceSyncRx(
                EthTSyn_IntPortIdxType     PortIdx,
                EthTSyn_IntVltType         SyncIngressVlt,
  ETHTSYN_P2VAR(EthTSyn_TimediffType)      TimeDiffSinceSyncRxPtr,
  ETHTSYN_P2VAR(StbM_VirtualLocalTimeType) CurrVltPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  const EthTSyn_TimeDomainIdxOfPortType timeDomainIdx = EthTSyn_GetTimeDomainIdxOfPort(PortIdx);
  const StbM_SynchronizedTimeBaseType timeBaseId = EthTSyn_GetSynchronizedTimeBaseIdOfTimeDomain(timeDomainIdx);
  EthTSyn_UTimediffType unsignedTimeDiff;

/* ----- Implementation ----------------------------------------------- */
# if (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_ON)
  /* #10 If HW-Timestmapin is enabled. */
  {
    Eth_TimeStampType currEthTime = { 0u, 0u, 0u };
    Eth_TimeStampQualType currEthTimeQual = ETH_INVALID;
    const EthTSyn_CtrlIdxOfPortType ethTSynCtrlIdx = EthTSyn_GetCtrlIdxOfPort(PortIdx);
    const uint8 ethIfCtrlIdx = (uint8)EthTSyn_GetEthIfCtrlIdxOfCtrl(ethTSynCtrlIdx);
    Std_ReturnType ethGetCurrTimeRetVal;
    Std_ReturnType stbmGetCurrVltRetVal;
    StbM_VirtualLocalTimeType stbmCurrVlt = { 0u, 0u };

    /* #100 Get the current Ethernet time via EthIf_GetCurrentTime() and the current virtual local time via
     *      StbM_GetCurrentVirtualLocalTime(). Protect both calls from interruption to minimize the delay between the
     *      two function calls. */
    ETHTSYN_ENTER_CRITICAL_SECTION_GET_TS();
    ethGetCurrTimeRetVal = EthIf_GetCurrentTime(ethIfCtrlIdx, &currEthTimeQual, &currEthTime);                         /* VCA_ETHTSYN_REF_OF_LOC_VAR */
    stbmGetCurrVltRetVal = StbM_GetCurrentVirtualLocalTime(timeBaseId, &stbmCurrVlt);                                  /* VCA_ETHTSYN_REF_OF_LOC_VAR */
    ETHTSYN_LEAVE_CRITICAL_SECTION_GET_TS();

    /* #101 If Ethernet time was retrieved successfull and is valid. */
    if(ethGetCurrTimeRetVal == E_OK)
    {
      if(currEthTimeQual == ETH_VALID)
      {
        /* #1010 Compute the time difference and assign it to the corresponding out parameter. */
        EthTSyn_IntVltType currEthTimeAsVlt = EthTSyn_UtilVlt_TsToIntVlt(&currEthTime);
        unsignedTimeDiff = (currEthTimeAsVlt - SyncIngressVlt);
        (*TimeDiffSinceSyncRxPtr) = (EthTSyn_TimediffType)unsignedTimeDiff;

        /* #1011 If StbM uses Ethernet as time source, transform the current Ethernet time into a virutal local time,
         *       assign it to the corresponding out parameter and return with success */
        if(EthTSyn_IsStbMTimeSrcEqualOfPort(PortIdx) == TRUE)
        {
          (*CurrVltPtr) = EthTSyn_UtilVlt_IntVltToVlt(currEthTimeAsVlt);
          retVal = E_OK;
        }
        /* #1012 Otherwise, assign the current virtual local time retrived from the StbM to the corresponding out
         *       parameter and return the result of the former StbM_GetCurrentVirtualLocalTime() call. */
        else
        {
          (*CurrVltPtr) = stbmCurrVlt;
          retVal = stbmGetCurrVltRetVal;
        }
      }
    }
  }
# else
  /* #20 Otherwise, SW-Timestamping is used. */
  {
    /* #200 Get the current virtual local time via StbM_GetCurrentVirtualLocalTime() and assing it to the
     *      corresponding out parameter. */
    if(StbM_GetCurrentVirtualLocalTime(timeBaseId, CurrVltPtr) == E_OK)                                                /* VCA_ETHTSYN_INT_FUNC_PTR_PARAM_FWD */
    {
      /* #2000 Compute the time difference, assign it to the corresponding out parameter and return with success. */
      unsignedTimeDiff = (EthTSyn_UtilVlt_VltToIntVlt(CurrVltPtr) - SyncIngressVlt);
      (*TimeDiffSinceSyncRxPtr) = (EthTSyn_TimediffType)unsignedTimeDiff;
      retVal = E_OK;
    }
  }
# endif /* (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_ON) */

  return retVal;
} /* EthTSyn_SlaveRx_GetTimeDiffSinceSyncRx() */

/**********************************************************************************************************************
 *  EthTSyn_SlaveRx_ProvideTimeToStbm
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
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SlaveRx_ProvideTimeToStbm(
                    EthTSyn_IntPortIdxType                    PortIdx,
    ETHTSYN_P2CONST(uint8)                                    MsgPtr,
                    EthTSyn_TimediffType                      TimeDiffSinceSyncRx,
    ETHTSYN_P2CONST(EthTSyn_SlaveRx_BusSetGlobalTimeInfoType) AddInfoPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthTSyn_PdelayType pDelay;
  EthTSyn_GlobalTimestampType preciseOriginTimestamp;
  EthTSyn_TimediffType potCorrectionTime = TimeDiffSinceSyncRx;
  EthTSyn_TimediffType fupCorrField;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Get the precise origin timestamp from FollowUp message. */
  preciseOriginTimestamp.secondsHi = IpBase_GetUint16(MsgPtr, ETHTSYN_MSG_FUP_POT_SEC_HI_OFS);
  preciseOriginTimestamp.seconds = IpBase_GetUint32(MsgPtr, ETHTSYN_MSG_FUP_POT_SEC_LOW_OFS);
  preciseOriginTimestamp.nanoseconds = IpBase_GetUint32(MsgPtr, ETHTSYN_MSG_FUP_POT_NSEC_OFS);

  /* #20 Add the FollowUp correction field to the time difference. */
  fupCorrField = (EthTSyn_TimediffType)IpBase_GetUint48(MsgPtr, ETHTSYN_MSG_HDR_CORR_FIELD_OFS);
  potCorrectionTime += fupCorrField;

  /* #30 Add current Pdelay to the time difference. */
  pDelay = EthTSyn_Pdelay_GetCurrentPdelay(PortIdx);
  potCorrectionTime += (EthTSyn_TimediffType)pDelay;

  /* #40 Add the switch residence time to the time difference (if switch management is enabled). */
# if (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON)
  potCorrectionTime += EthTSyn_GetAddrSyncReceiveSm(EthTSyn_GetSlavePortIdxOfPort(PortIdx))->Sync.SwtResidenceTime;
# endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON) */

# if (ETHTSYN_SLAVE_TIME_VALIDATION_SUPPORT == STD_ON)
  /* #50 Provide the precise origin timestamp and the correction field of the received FollowUp message to the
   *     time validation unit (if slave time validation is enabled).*/
  EthTSyn_TimeValid_SlaveProvideFollowUpData(PortIdx, &preciseOriginTimestamp, fupCorrField);
  EthTSyn_TimeValid_SlaveProvideCurrPdelay(PortIdx, pDelay);
# endif /* (ETHTSYN_SLAVE_TIME_VALIDATION_SUPPORT == STD_ON) */

  /* #60 Compute the new time which should be passed to the StbM. */
  if(EthTSyn_Util_TimestampPlusTimediff(&preciseOriginTimestamp, &potCorrectionTime) == E_OK)
  {
# if (ETHTSYN_SLAVE_TIME_VALIDATION_SUPPORT == STD_ON)
    Std_ReturnType busSetGlobTimeRetVal;
# endif /* (ETHTSYN_SLAVE_TIME_VALIDATION_SUPPORT == STD_ON) */
    const EthTSyn_TimeDomainIdxOfPortType timeDomainIdx = EthTSyn_GetTimeDomainIdxOfPort(PortIdx);
    StbM_TimeStampType timeStampStbm;
    StbM_MeasurementType measureData;

    timeStampStbm.timeBaseStatus = AddInfoPtr->TbStatus;
    timeStampStbm.secondsHi = preciseOriginTimestamp.secondsHi;
    timeStampStbm.seconds = preciseOriginTimestamp.seconds;
    timeStampStbm.nanoseconds = preciseOriginTimestamp.nanoseconds;
    measureData.pathDelay = pDelay;

    /* #70 Provide new Time to the StbM. */
# if (ETHTSYN_SLAVE_TIME_VALIDATION_SUPPORT == STD_ON)
    busSetGlobTimeRetVal = StbM_BusSetGlobalTime(EthTSyn_GetSynchronizedTimeBaseIdOfTimeDomain(timeDomainIdx),
      &timeStampStbm, AddInfoPtr->UserDataPtr, &measureData, &AddInfoPtr->CurrVlt);

    /* #80 Inform the time validation unit that StbM_BusSetGlobalTime() was called in case of success
     *    (if slave time validation is enabled).*/
    if(busSetGlobTimeRetVal == E_OK)
    {
      EthTSyn_TimeValid_SlaveBusSetGlobalTimeCalled(PortIdx);
    }
# else
    (void)StbM_BusSetGlobalTime(EthTSyn_GetSynchronizedTimeBaseIdOfTimeDomain(timeDomainIdx),
      &timeStampStbm, AddInfoPtr->UserDataPtr, &measureData, &AddInfoPtr->CurrVlt);
# endif /* (ETHTSYN_SLAVE_TIME_VALIDATION_SUPPORT == STD_ON) */
  }
} /* EthTSyn_SlaveRx_ProvideTimeToStbm() */

# if (ETHTSYN_SITESYNCSYNCSM == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_Slave_SyncReceiveHandleSyncTimeout
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
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_Slave_SyncReceiveHandleSyncTimeout(
                EthTSyn_IntTimeDomainIdxType TimeDomainIdx,
  ETHTSYN_P2VAR(EthTSyn_SyncReceiveSmType)   SyncReceiveSmPtr)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if the site sync sync state machine is used for the passed time domain. */
  if(EthTSyn_IsSiteSyncSyncSmUsedOfTimeDomain(TimeDomainIdx) == TRUE)
  {
    /* #20 Check for Sync receive timeout. */
    if(SyncReceiveSmPtr->Sync.SyncRxTimeoutCnt == 0u)
    {
      /* #30 Sync receive timeout occurred -> Take up role as master now. */
      SyncReceiveSmPtr->State = ETHTSYN_S_SYNC_RCV_SM_SYNC_TIMEOUT;

      EthTSyn_SwtMgmt_SiteSyncSync_HndlSyncTimeout(TimeDomainIdx);
    }
  }
} /* EthTSyn_Slave_SyncReceiveHandleSyncTimeout() */
# endif /* (ETHTSYN_SITESYNCSYNCSM == STD_ON) */

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  EthTSyn_Slave_Init
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, ETHTSYN_CODE) EthTSyn_Slave_Init(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthTSyn_SlavePortIterType slavePortIter;
  EthTSyn_SystemStateIterType systemStateIter;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Reset system state. */
  for(systemStateIter = 0u;
      systemStateIter < EthTSyn_GetSizeOfSystemState();
      systemStateIter++)
  {
    EthTSyn_SetGmPresentOfSystemState(systemStateIter, FALSE);
  }
  /* #20 Initialize all slave ports. */
  for(slavePortIter = 0u; slavePortIter < EthTSyn_GetSizeOfSlavePort(); slavePortIter++)
  {
    EthTSyn_Slave_InitPortInternal(slavePortIter);
  }
} /* EthTSyn_Slave_Init() */

/**********************************************************************************************************************
 *  EthTSyn_Slave_InitPort
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, ETHTSYN_CODE) EthTSyn_Slave_InitPort(
  EthTSyn_IntSlavePortIdxType SlavePortIdx)
{
  EthTSyn_Slave_InitPortInternal(SlavePortIdx);
} /* EthTSyn_Slave_InitPort() */

/**********************************************************************************************************************
 *  EthTSyn_Slave_HandleCyclicTasks
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
/* PRQA S 6050 1 */ /* MD_EthTSyn_6050_CslAccess */
FUNC(void, ETHTSYN_CODE) EthTSyn_Slave_HandleCyclicTasks(
  EthTSyn_TimeDomainIterType TimeDomainIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthTSyn_SlavePortIterType slavePortIter;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate all Slave-Ports of the given TimeDomain */
  for(slavePortIter = EthTSyn_GetSlavePortStartIdxOfTimeDomain(TimeDomainIdx);
      slavePortIter < EthTSyn_GetSlavePortEndIdxOfTimeDomain(TimeDomainIdx);
      slavePortIter++)
  {
    /*@ assert slavePortIter < EthTSyn_GetSizeOfSlavePort(); */                                                        /* VCA_ETHTSYN_0_N_IND_CSL03 */
    EthTSyn_SyncReceiveSmPtrType syncReceiveSmPtr = EthTSyn_GetAddrSyncReceiveSm(slavePortIter);

    ETHTSYN_ENTER_CRITICAL_SECTION_0();

    /* #20 Handle announce receive state machine timeouts if applicable. */
# if (ETHTSYN_ANNOUNCE_RX_SUPPORT == STD_ON)
    {
      const EthTSyn_AnnounceInfoIdxOfSlavePortType announceInfoIdx =
        EthTSyn_GetAnnounceInfoIdxOfSlavePort(slavePortIter);
      if(announceInfoIdx < EthTSyn_GetSizeOfAnnounceInfo())
      {
        EthTSyn_AnnounceReceiveSmPtrType announceReceiveSmPtr = EthTSyn_GetAddrAnnounceReceiveSm(announceInfoIdx);
        if(announceReceiveSmPtr->RxTimeoutCnt > 0u)
        {
          (announceReceiveSmPtr->RxTimeoutCnt)--;
        }
        /* #200 Process announce receive state machine */
        EthTSyn_Slave_ProcessSmAnnounceReceive(slavePortIter);
      }
    }
# endif /* (ETHTSYN_ANNOUNCE_RX_SUPPORT == STD_ON) */

    /* #30 Handle sync receive state machine timeouts */
    if(syncReceiveSmPtr->FollowUp.FollowUpRxTimeoutCnt > 0u)
    {
      syncReceiveSmPtr->FollowUp.FollowUpRxTimeoutCnt--;
    }

# if (ETHTSYN_SITESYNCSYNCSM == STD_ON)
    if(syncReceiveSmPtr->Sync.SyncRxTimeoutCnt > 0u)
    {
      syncReceiveSmPtr->Sync.SyncRxTimeoutCnt--;
    }
# endif /* (ETHTSYN_SITESYNCSYNCSM == STD_ON) */

    ETHTSYN_LEAVE_CRITICAL_SECTION_0();

    /* #40 Process sync receive state machine. */
    EthTSyn_Slave_ProcessSmSyncReceive(slavePortIter);
  } /* END: Iteration Slave Ports */
} /* EthTSyn_Slave_HandleCyclicTasks() */

/**********************************************************************************************************************
 *  EthTSyn_SlaveRx_ProcRcvdSyncMsg
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
FUNC(void, ETHTSYN_CODE) EthTSyn_SlaveRx_ProcRcvdSyncMsg(
  ETHTSYN_P2CONST(uint8)                  RxBufPtr,
                  EthTSyn_IntPortIdxType  PortIdx,
  ETHTSYN_P2CONST(EthTSyn_IntVltMgmtType) IngressTsVltMgmtPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  const EthTSyn_SlavePortIdxOfPortType slavePortIdx = EthTSyn_GetSlavePortIdxOfPort(PortIdx);
  /*@ assert slavePortIdx < EthTSyn_GetSizeOfSlavePort(); */                                                           /* VCA_ETHTSYN_INT_FUNC_IDX_PARAM */
  /* Get Sync receive state machine Pointer */
  ETHTSYN_CONSTP2VAR(EthTSyn_SyncReceiveSmType) syncReceiveSmPtr = EthTSyn_GetAddrSyncReceiveSm(slavePortIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if port is able to receive the sync message and if ingress timestamp is valid. */
  if(
    (EthTSyn_SlaveRx_IsPortReadyToReceiveSync(PortIdx) == TRUE) &&
    (IngressTsVltMgmtPtr->IntVltValid == TRUE)
    )
  {
    /* #20 Write relevant information to the sync receive SM. */
    if(EthTSyn_SlaveRx_WriteSyncMsgToSyncReceiveSm(slavePortIdx, RxBufPtr) == E_OK)
    {
      /* #30 Write ingress timestamp to the sync receive SM. */
      ETHTSYN_ENTER_CRITICAL_SECTION_0();
      syncReceiveSmPtr->Sync.IngressTsVltMgmt = (*IngressTsVltMgmtPtr);
      ETHTSYN_LEAVE_CRITICAL_SECTION_0();

# if (ETHTSYN_SLAVE_TIME_VALIDATION_SUPPORT == STD_ON)
      /* #40 Start a new slave sync cycle in the time validation unit and report sync ingress timestamp
       *     (if slave time validation is enabled). */
      EthTSyn_TimeValid_SlaveStartCycle(PortIdx, IpBase_GetUint16(RxBufPtr, ETHTSYN_MSG_HDR_SEQUENCE_ID_OFS));
      EthTSyn_TimeValid_SlaveProvideSyncIngressData(PortIdx, &syncReceiveSmPtr->Sync.SourcePortIdentity,
        IngressTsVltMgmtPtr->IntVlt);
# endif /* (ETHTSYN_SLAVE_TIME_VALIDATION_SUPPORT == STD_ON) */
    }
  }
  /* #50 Otherwise, change state of sync receive SM to DISCARD. */
  else
  {
    ETHTSYN_ENTER_CRITICAL_SECTION_0();
    syncReceiveSmPtr->State = ETHTSYN_S_SYNC_RCV_SM_DISCARD;
    ETHTSYN_LEAVE_CRITICAL_SECTION_0();
  }
} /* EthTSyn_SlaveRx_ProcRcvdSyncMsg() */

/**********************************************************************************************************************
 *  EthTSyn_SlaveRx_WriteSyncMsgToSyncReceiveSm
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
/* PRQA S 6050 1 */ /* MD_EthTSyn_6050_CslAccess */
FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_SlaveRx_WriteSyncMsgToSyncReceiveSm(
                  EthTSyn_IntSlavePortIdxType SlavePortIdx,
  ETHTSYN_P2CONST(uint8)                      RxBufPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  ETHTSYN_CONSTP2VAR(EthTSyn_SyncReceiveSmType) syncReceiveSmPtr = EthTSyn_GetAddrSyncReceiveSm(SlavePortIdx);
  const uint16 rxSequenceId = IpBase_GetUint16(RxBufPtr, ETHTSYN_MSG_HDR_SEQUENCE_ID_OFS);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Verify sequence id. */
  if (((syncReceiveSmPtr->PrevSeqIdValid == TRUE) && (syncReceiveSmPtr->PrevSeqId != rxSequenceId)) ||
    (syncReceiveSmPtr->PrevSeqIdValid == FALSE))
  {
    ETHTSYN_ENTER_CRITICAL_SECTION_0();
    /* #20 Write sync log message interval, clock identity and port number to sync receive SM. */
    syncReceiveSmPtr->Sync.LogMessageInterval =
      (sint8)IpBase_GetUint8(RxBufPtr, ETHTSYN_MSG_HDR_LOG_MSG_INTERVAL_OFS);
    syncReceiveSmPtr->Sync.SourcePortIdentity.ClockIdentity =
      IpBase_GetUint64(RxBufPtr, ETHTSYN_MSG_HDR_SRC_PORT_IDENT_CLOCK_IDENT_OFS);
    syncReceiveSmPtr->Sync.SourcePortIdentity.PortNumber =
      IpBase_GetUint16(RxBufPtr, ETHTSYN_MSG_HDR_SRC_PORT_IDENT_PORT_NUM_OFS);

    /* #30 Write sequence Id to sync receive SM. */
    syncReceiveSmPtr->Sync.SequenceId = rxSequenceId;
    syncReceiveSmPtr->PrevSeqId = rxSequenceId;
    syncReceiveSmPtr->PrevSeqIdValid = TRUE;

    /* #40 Set FollowUp receive timeout if required. */
    if (EthTSyn_GetFollowUpAllowedRxDelayOfSlavePort(SlavePortIdx) > 0u)
    {
      syncReceiveSmPtr->FollowUp.FollowUpRxTimeoutCnt =
        EthTSyn_GetFollowUpAllowedRxDelayOfSlavePort(SlavePortIdx);
    }
    /* #50 Change state of sync receive SM to waiting for FollowUp. */
    syncReceiveSmPtr->State = ETHTSYN_S_SYNC_RCV_SM_WAIT_FUP;

    ETHTSYN_LEAVE_CRITICAL_SECTION_0();
    retVal = E_OK;
  }

  return retVal;
} /* EthTSyn_SlaveRx_WriteSyncMsgToSyncReceiveSm */

/**********************************************************************************************************************
 *  EthTSyn_SlaveRx_ProcRcvdFupMsg
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
FUNC(void, ETHTSYN_CODE) EthTSyn_SlaveRx_ProcRcvdFupMsg(
  ETHTSYN_P2CONST(uint8)                  RxBufPtr,
                  EthTSyn_IntPortIdxType  PortIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  const EthTSyn_SlavePortIdxOfPortType slavePortIdx = EthTSyn_GetSlavePortIdxOfPort(PortIdx);


  /* ----- Implementation ----------------------------------------------- */
# if (ETHTSYN_MASTER_SUPPORT == STD_ON)
#  if (ETHTSYN_SWT_MGMT_SUPPORT == STD_OFF)
  /* #10 Check that Rx-Port is Slave Port. */
  if(slavePortIdx < EthTSyn_GetSizeOfSlavePort()) /* This check is always TRUE when Master support is disabled. */
#  endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_OFF) */
# endif /* (ETHTSYN_MASTER_SUPPORT == STD_ON) */
  {
    /* #20 Check if the FollowUp message matches the former received Sync message. */
    if(EthTSyn_SlaveRx_IsFupMatchingSync(RxBufPtr, PortIdx) == TRUE)
    {
      ETHTSYN_CONSTP2VAR(EthTSyn_SyncReceiveSmType) syncReceiveSmPtr = EthTSyn_GetAddrSyncReceiveSm(slavePortIdx);
      EthTSyn_TimediffType timeDiff = 0;
      StbM_TimeBaseStatusType status = 0;
# if (ETHTSYN_MESSAGE_COMPLIANCE == STD_OFF)
      StbM_UserDataType userData;
      ETHTSYN_P2VAR(StbM_UserDataType) userDataPtr = &userData;
# else
      ETHTSYN_P2VAR(StbM_UserDataType) userDataPtr = NULL_PTR;
# endif /* (ETHTSYN_MESSAGE_COMPLIANCE == STD_OFF) */

# if (ETHTSYN_MESSAGE_COMPLIANCE == STD_OFF)
      /* #30 Check for Ar Tlvs. */
      if(EthTSyn_SlaveRx_HandleArFollowUpTlvs(PortIdx, RxBufPtr, syncReceiveSmPtr->Sync.IngressTsVltMgmt.IntVlt,
          &status, &userDataPtr) == E_OK)
# endif /* (ETHTSYN_MESSAGE_COMPLIANCE == STD_OFF) */
      {
        StbM_VirtualLocalTimeType currVlt = { 0u, 0u };
        /* #40 Provide time information to StbM. */
        if(EthTSyn_SlaveRx_GetTimeDiffSinceSyncRx(PortIdx, syncReceiveSmPtr->Sync.IngressTsVltMgmt.IntVlt,
            &timeDiff, &currVlt) == E_OK)
        {
          EthTSyn_SlaveRx_BusSetGlobalTimeInfoType addInfo;
          addInfo.CurrVlt = currVlt;
          addInfo.UserDataPtr = userDataPtr;
          addInfo.TbStatus = status;
          EthTSyn_SlaveRx_ProvideTimeToStbm(PortIdx, RxBufPtr, timeDiff, &addInfo);
        }
        syncReceiveSmPtr->State = ETHTSYN_S_SYNC_RCV_SM_WAIT_SYNC;
      }
    } /* END: if(processMsg == TRUE) */
  } /* END: if(Slave-Port) */
} /* EthTSyn_SlaveRx_ProcRcvdFupMsg() */

/**********************************************************************************************************************
 *  EthTSyn_SlaveRx_IsFupMatchingSync
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(boolean, ETHTSYN_CODE) EthTSyn_SlaveRx_IsFupMatchingSync(
  ETHTSYN_P2CONST(uint8)                  RxBufPtr,
                  EthTSyn_IntPortIdxType  PortIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean retVal = FALSE;
  const EthTSyn_SlavePortIdxOfPortType slavePortIdx = EthTSyn_GetSlavePortIdxOfPort(PortIdx);
  /*@ assert slavePortIdx < EthTSyn_GetSizeOfSlavePort(); */                                                           /* VCA_ETHTSYN_INT_FUNC_IDX_PARAM */
  ETHTSYN_CONSTP2CONST(EthTSyn_SyncReceiveSmType) syncReceiveSmPtr = EthTSyn_GetAddrSyncReceiveSm(slavePortIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check sync receive state machine state and matching sequence id */
  if ((syncReceiveSmPtr->State == ETHTSYN_S_SYNC_RCV_SM_WAIT_FUP) &&
    (syncReceiveSmPtr->Sync.SequenceId == IpBase_GetUint16(RxBufPtr, ETHTSYN_MSG_HDR_SEQUENCE_ID_OFS))) /* PRQA S 3415 */ /* MD_EthTSyn_3415_ReadOnly */
  {
    /* #20 Check for matching source port identity */
    if (EthTSyn_UtilRx_PortIdentityIsEqual(&syncReceiveSmPtr->Sync.SourcePortIdentity,
      &RxBufPtr[ETHTSYN_MSG_HDR_SRC_PORT_IDENTITY_OFS]) == TRUE)
    {
      retVal = TRUE;
    }
  }
  return retVal;
} /* EthTSyn_SlaveRx_IsFupMatchingSync */

# if (ETHTSYN_MESSAGE_COMPLIANCE == STD_OFF)
/**********************************************************************************************************************
 *  EthTSyn_SlaveRx_CheckArSubTlvsAndGetCnt
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
FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_SlaveRx_CheckArSubTlvsAndGetCnt(
                  EthTSyn_IntPortIdxType  PortIdx,
  ETHTSYN_P2CONST(uint8)                  RxBufPtr,
    ETHTSYN_P2VAR(uint8)                  SubTlvCntPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;
  uint16 subTlvTotalLength = 0u;
  uint8 subTlvCnt = 0u;
  const uint16 msgLength = IpBase_GetUint16(RxBufPtr, ETHTSYN_MSG_HDR_MSG_LENGTH_OFS);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if the message length indicates at least one AR-TLV. */
  if(msgLength >= (ETHTSYN_MSG_FOLLOW_UP_MIN_LENGTH + ETHTSYN_AR_TLV_HEADER_LENGTH))
  {
    /* #20 Check AR-TLV Header. */
    retVal = EthTSyn_UtilArTlv_CheckArTlvHeader(RxBufPtr, msgLength, &subTlvTotalLength);

    if(retVal == E_OK)
    {
      /* #30 Unpack and check Sub-TLVs. */
      uint32_least currSubTlvOfs = ETHTSYN_MSG_FUP_FIRST_AR_SUB_TLV_OFS;
      sint32 remainingLength = (sint32)subTlvTotalLength;

      do
      {
        uint8 tlvLength;

        tlvLength = ETHTSYN_AR_SUB_TLV_ABSTRACT_HDR_LENGTH;
        tlvLength += IpBase_GetUint8(RxBufPtr, (currSubTlvOfs + ETHTSYN_MSG_FUP_AR_SUB_TLV_LEN_OFS));

        remainingLength -= (sint32)tlvLength;

        /* #40 Check if Sub-TLV fits in the message. */
        if(remainingLength >= 0)
        {
          subTlvCnt++;

          /* Process Sub-Tlv */
          /* #400 Check if Crc is included and valid. */
          retVal = EthTSyn_SlaveRx_CheckArSubTlvCrc(PortIdx, RxBufPtr, currSubTlvOfs);

          /* Set offset to potential next Sub-TLV. */
          currSubTlvOfs += tlvLength;
        }
        else
        {
          /* #401 Message is to small too hold this Sub-TLV -> Drop message. */
          retVal = E_NOT_OK;
        }
      } while((retVal == E_OK) && (remainingLength > (sint32)ETHTSYN_AR_SUB_TLV_ABSTRACT_HDR_LENGTH));
    }
  }
  else
  {
    /* According to message length, no AR-TLV can be included in the message. This is valid. */
    retVal = E_OK;
  }

  /* #50 Write the Sub TLV count to the out parameter. */
  (*SubTlvCntPtr) = subTlvCnt;

  return retVal;
} /* EthTSyn_SlaveRx_CheckArSubTlvsAndGetCnt() */
# endif /* (ETHTSYN_MESSAGE_COMPLIANCE == STD_OFF) */

# if (ETHTSYN_SWT_MGMT_SUPPORT == STD_OFF)
#  if (ETHTSYN_ANNOUNCE_RX_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_Slave_ProcRcvdAnnounceMsg
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
/* PRQA S 6050 1 */ /* MD_EthTSyn_6050_CslAccess */
FUNC(void, ETHTSYN_CODE) EthTSyn_Slave_ProcRcvdAnnounceMsg(
  ETHTSYN_P2CONST(uint8)                  RxBufPtr,
                  EthTSyn_IntPortIdxType  PortIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthTSyn_IntTimeDomainIdxType timeDomainIdx = EthTSyn_GetTimeDomainIdxOfPort(PortIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if announce message can be received on the Port. */
  if(EthTSyn_UtilRx_IsPortReadyToReceiveAnnounce(PortIdx) == TRUE)
  {
    ETHTSYN_ENTER_CRITICAL_SECTION_0();
    /* #20 Validated the Announce Message. */
    if(EthTSyn_UtilRx_QualifyAnnounceMsg(RxBufPtr, PortIdx) == E_OK)
    {
      const EthTSyn_SlavePortIdxOfPortType slavePortIdx = EthTSyn_GetSlavePortIdxOfPort(PortIdx);
      /*@ assert slavePortIdx < EthTSyn_GetSizeOfSlavePort(); */                                                       /* VCA_ETHTSYN_IS_READY_TO_RCV_ANNOUNCE_CSL03 */
      const EthTSyn_AnnounceInfoIdxOfSlavePortType announceInfoIdx =
        EthTSyn_GetAnnounceInfoIdxOfSlavePort(slavePortIdx);
      /*@ assert announceInfoIdx < EthTSyn_GetSizeOfAnnounceInfo(); */                                                 /* VCA_ETHTSYN_IS_READY_TO_RCV_ANNOUNCE_CSL03 */
      ETHTSYN_CONSTP2VAR(EthTSyn_AnnounceReceiveSmType) announceReceiveSmPtr =
        EthTSyn_GetAddrAnnounceReceiveSm(announceInfoIdx);

      /* Reset announce timeout */
      announceReceiveSmPtr->RxTimeoutCnt = EthTSyn_GetAnnounceAllowedRxDelayOfAnnounceInfo(announceInfoIdx);

      /* #30 Set new Grandmaster if applicable. */
      if(EthTSyn_IsGmPresentOfSystemState(timeDomainIdx) == FALSE)
      {
        EthTSyn_Slave_SetMasterPriorityVector(RxBufPtr, timeDomainIdx);
      }
    }
    ETHTSYN_LEAVE_CRITICAL_SECTION_0();
  }

} /* EthTSyn_Slave_ProcRcvdAnnounceMsg() */
#  endif /* (ETHTSYN_ANNOUNCE_RX_SUPPORT == STD_ON) */
# endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_OFF) */

# if (ETHTSYN_ANNOUNCE_RX_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_Slave_SetMasterPriorityVector
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, ETHTSYN_CODE) EthTSyn_Slave_SetMasterPriorityVector(
  ETHTSYN_P2CONST(uint8)                        RxBufPtr,
                  EthTSyn_IntTimeDomainIdxType  TimeDomainIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  const uint64 clockIdentity = IpBase_GetUint64(RxBufPtr, ETHTSYN_MSG_ANNOUNCE_GM_IDENTITY_OFS);

  /* ----- Implementation ----------------------------------------------- */
  EthTSyn_SetGmClockIdentityOfSystemState(TimeDomainIdx, clockIdentity);
  EthTSyn_SetGmPresentOfSystemState(TimeDomainIdx, TRUE);
} /* EthTSyn_Slave_SetMasterPriorityVector() */

/**********************************************************************************************************************
 *  EthTSyn_Slave_ResetMasterPriorityVector
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, ETHTSYN_CODE) EthTSyn_Slave_ResetMasterPriorityVector(
  EthTSyn_IntTimeDomainIdxType TimeDomainIdx)
{
  /* ----- Implementation ----------------------------------------------- */
  EthTSyn_SetGmClockIdentityOfSystemState(TimeDomainIdx, 0);
  EthTSyn_SetGmPresentOfSystemState(TimeDomainIdx, FALSE);
} /* EthTSyn_Slave_ResetMasterPriorityVector() */
# endif /* (ETHTSYN_ANNOUNCE_RX_SUPPORT == STD_ON) */


# define ETHTSYN_STOP_SEC_CODE
# include "EthTSyn_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* (ETHTSYN_SLAVE_SUPPORT == STD_ON) */

/* Justification for module-specific MISRA deviations:
 * see file EthTSyn.c
*/
/**********************************************************************************************************************
 *  END OF FILE: EthTSyn_Slave_Int.c
 *********************************************************************************************************************/
