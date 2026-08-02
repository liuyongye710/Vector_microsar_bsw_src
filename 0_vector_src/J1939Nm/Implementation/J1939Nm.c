/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2022 Vector Informatik GmbH.                                                     All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  J1939Nm.c
 *       Module:  SAE J1939 Network Management (J1939Nm)
 *
 *  Description:  Implementation of the SAE J1939 Network Management module.
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

/**********************************************************************************************************************
 *  MISRA / PClint JUSTIFICATIONS
 *********************************************************************************************************************/

/* *INDENT-OFF* */
/* PRQA S 0292 EOF */ /* MD_MSR_Dir1.1 */
/* PRQA S 0715 EOF */ /* MD_MSR_Dir1.1_0715 */
/* PRQA S 0779 EOF */ /* MD_MSR_Rule5.2_0779 */
/* PRQA S 0850 EOF */ /* MD_MSR_MacroArgumentEmpty */
/* PRQA S 1503 EOF */ /* MD_MSR_Unreachable */
/* *INDENT-ON* */


/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

#define J1939NM_C

#include "J1939Nm.h"
#include "J1939Nm_Cbk.h"

#include "J1939Nm_Cfg.h"
#include "J1939Nm_Lcfg.h"
#include "J1939Nm_PBcfg.h"

#include "J1939Nm_Int.h"
#if ((J1939NM_DYNAMIC_ADDRESS_SUPPORT == STD_ON) || (J1939NM_GATEWAY_SUPPORT == STD_ON) || (J1939NM_NM_PG_SUPPORT == STD_ON) || (J1939NM_NAME_MANAGEMENT_SUPPORT == STD_ON))
# include "J1939Nm_Dynamic.h"
#endif

#include "BswM_J1939Nm.h"
#include "CanIf.h"
#include "Nm_Cbk.h"
#include "J1939Rm.h"

#if ((J1939NM_ADDRESSSTORAGEBLOCK == STD_ON) || (J1939NM_NAMESTORAGEBLOCK == STD_ON))
# include "NvM.h"
#endif

#include "SchM_J1939Nm.h"

#if (J1939NM_USE_ECUM_BSW_ERROR_HOOK == STD_ON)
# include "EcuM_Error.h"
#endif


/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/

/* Vendor specific BSW module version information */
#define J1939NM_MAJOR_SOURCE_VERSION            (9u)
#define J1939NM_MINOR_SOURCE_VERSION            (0u)
#define J1939NM_PATCH_SOURCE_VERSION            (0u)

/* Vendor specific BSW generator version information */
#define J1939NM_MAJOR_GENERATOR_VERSION         (4u)
#define J1939NM_MINOR_GENERATOR_VERSION         (0u)

/* Check the vendor specific version of J1939Nm module header file */
#if ((J1939NM_SW_MAJOR_VERSION != J1939NM_MAJOR_SOURCE_VERSION) || (J1939NM_SW_MINOR_VERSION != J1939NM_MINOR_SOURCE_VERSION) || (J1939NM_SW_PATCH_VERSION != J1939NM_PATCH_SOURCE_VERSION))
# error "Vendor specific version numbers of J1939Nm.c and J1939Nm.h are inconsistent"
#endif

/* Check the version of the configuration header file */
#if ((J1939NM_CFG_MAJOR_VERSION != J1939NM_MAJOR_GENERATOR_VERSION) || (J1939NM_CFG_MINOR_VERSION != J1939NM_MINOR_GENERATOR_VERSION))
# error "Vendor specific version numbers of J1939Nm.c and J1939Nm_Cfg.h are inconsistent!"
#endif


/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/

/*======================================= J1939NM_START_SEC_VAR_ZERO_INIT_8BIT ======================================*/
#define J1939NM_START_SEC_VAR_ZERO_INIT_8BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! Initialization state of the J1399Nm */
VAR(uint8, J1939NM_VAR_ZERO_INIT) J1939Nm_ModuleInitialized = J1939NM_UNINIT;

#define J1939NM_STOP_SEC_VAR_ZERO_INIT_8BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*======================================== J1939NM_STOP_SEC_VAR_ZERO_INIT_8BIT ======================================*/


/**********************************************************************************************************************
 *  INTERNAL DATA
 *********************************************************************************************************************/

/*=================================== J1939NM_START_SEC_VAR_ZERO_INIT_UNSPECIFIED ===================================*/
#define J1939NM_START_SEC_VAR_ZERO_INIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! Post-build configuration data of the J1939Nm */
#if (J1939NM_USE_INIT_POINTER == STD_ON)
/*!
* \spec
*   strong invariant J1939Nm_ConfigDataPtr == J1939Nm_Config_Ptr;
* \endspec
*/
P2CONST(J1939Nm_ConfigType, J1939NM_VAR_ZERO_INIT, J1939NM_PBCFG) J1939Nm_ConfigDataPtr = NULL_PTR;
#endif

#define J1939NM_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*==================================== J1939NM_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED ===================================*/


/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/*================================================ J1939NM_START_SEC_CODE ===========================================*/
#define J1939NM_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  J1939Nm_InternalSendAc()
 *********************************************************************************************************************/
/*! \brief       Transmits an AddressClaimed (AC) message.
 *  \details      -
 *  \param[in]   channelIdx      Internal index of the channel on which the AC shall be transmitted.
 *  \param[in]   nodeIdx         Index of the node that sends the AC.
 *  \param[in]   sourceAddress   The address that shall be claimed.
 *  \pre          -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \spec
 *    requires   channelIdx < J1939Nm_GetSizeOfChannel();
 *    requires   nodeIdx < J1939Nm_GetSizeOfNode();
 *  \endspec
 *********************************************************************************************************************/
J1939NM_LOCAL_INLINE FUNC(void, J1939NM_CODE) J1939Nm_InternalSendAc(const J1939Nm_SizeOfChannelType channelIdx,
                                                                     const J1939Nm_SizeOfNodeType nodeIdx,
                                                                     const uint8 sourceAddress);

/**********************************************************************************************************************
 *  J1939Nm_InternalCalcDelay()
 *********************************************************************************************************************/
/*! \brief       Calculate a random number of MainFunction cycles to delay BusOff recovery or transmission of AC.
 *  \details      -
 *  \param[in]   nodeIdx         Index of the node for which the delay shall be calculated.
 *  \param[in]   intern          TRUE: Calculate number of J1939Nm_MainFunction cycles,
 *                               FALSE: Calculate number of CanSM_MainFunction cycles.
 *  \return                      Number of J1939Nm or CanSMN MainFunction cycles, depending on parameter 'intern'.
 *  \pre          -
 *  \context     TASK|ISR
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \trace SPEC-2168261
 *  \spec
 *    requires   nodeIdx < J1939Nm_GetSizeOfNode();
 * \endspec
 *********************************************************************************************************************/
J1939NM_LOCAL_INLINE FUNC(uint8, J1939NM_CODE) J1939Nm_InternalCalcDelay(const J1939Nm_SizeOfNodeType nodeIdx,
                                                                         const boolean intern);

/**********************************************************************************************************************
 *  J1939Nm_InternalInit()
 *********************************************************************************************************************/
/*! \brief       Internal funtion to initialize the J1939 Network Management.
 *  \details      -
 *  \pre         The module must be in the uninitialized state.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *********************************************************************************************************************/
J1939NM_LOCAL_INLINE FUNC(void, J1939NM_CODE) J1939Nm_InternalInit(void);


/**********************************************************************************************************************
 *  J1939Nm_InternalInitRandomSeed()
 *********************************************************************************************************************/
/*! \brief       Internal funtion to initialize the random seeds.
 *  \details      -
 *  \pre         The module must be in the uninitialized state.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *********************************************************************************************************************/
J1939NM_LOCAL_INLINE FUNC(void, J1939NM_CODE) J1939Nm_InternalInitRandomSeed(void);


/**********************************************************************************************************************
 *  J1939Nm_InternalInitNodeChannelState()
 *********************************************************************************************************************/
/*! \brief       Internal funtion to initialize the node channel states.
 *  \details      -
 *  \pre         The module must be in the uninitialized state.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *********************************************************************************************************************/
J1939NM_LOCAL_INLINE FUNC(void, J1939NM_CODE) J1939Nm_InternalInitNodeChannelState(void);


/**********************************************************************************************************************
 *  J1939Nm_InternalInitChannelState()
 *********************************************************************************************************************/
/*! \brief       Internal funtion to initialize the channel states.
 *  \details      -
 *  \pre         The module must be in the uninitialized state.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *********************************************************************************************************************/
J1939NM_LOCAL_INLINE FUNC(void, J1939NM_CODE) J1939Nm_InternalInitChannelState(void);


/**********************************************************************************************************************
 *  J1939Nm_InternalConfTimeoutHandling()
 *********************************************************************************************************************/
/*! \brief       Handles the confirmation imeout.
 *  \details      -
 *  \pre          -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *********************************************************************************************************************/
J1939NM_LOCAL_INLINE FUNC(void, J1939NM_CODE) J1939Nm_InternalConfTimeoutHandling(void);


/**********************************************************************************************************************
 *  J1939Nm_InternalMainFunction()
 *********************************************************************************************************************/
/*! \brief       Internal main function of the J1939 Network Management.
 *  \details      -
 *  \pre          -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *********************************************************************************************************************/
J1939NM_LOCAL_INLINE FUNC(void, J1939NM_CODE) J1939Nm_InternalMainFunction(void);


/***********************************************************************************************************************
 *  J1939Nm_InternalMainFunctionHandleNodeStateClaiming()
 **********************************************************************************************************************/
/*! \brief       Handles node channel states an timeout at node state claiming during main function cycle.
 *  \details      -
 *  \param[out]  nodeChannelState  State of node channel..
 *  \param[out]  nmState           State of NM.
 *  \pre         Parameters must be valid.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 **********************************************************************************************************************/
J1939NM_LOCAL_INLINE FUNC(void, J1939NM_CODE)
J1939Nm_InternalMainFunctionHandleNodeStateClaiming(J1939Nm_NodeChannelStateType * nodeChannelState,
                                                    Nm_StateType * nmState);


/***********************************************************************************************************************
 *  J1939Nm_InternalMainFunctionHandleNodeStateAcDelayed()
 **********************************************************************************************************************/
/*! \brief       Handles node channel states an timeout at node state AcDelayed during main function cycle.
 *  \details      -
 *  \param[out]  nodeChannelState  State of node channel..
 *  \param[in]   nodeIdx           Internal index of the node for which the delay is calculated.
 *  \return      nmState:        State of NM.
 *  \pre         Parameters must be valid.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 **********************************************************************************************************************/
J1939NM_LOCAL_INLINE FUNC(void, J1939NM_CODE)
J1939Nm_InternalMainFunctionHandleNodeStateAcDelayed(J1939Nm_NodeChannelStateType * nodeChannelState,
                                                     J1939Nm_NodeIdxOfNodeChannelType nodeIdx);


/***********************************************************************************************************************
 *  J1939Nm_InternalMainFunctionHandleNodeStateAcPending()
 **********************************************************************************************************************/
/*! \brief       Handles node channel states an timeout at node state AcPending during main function cycle.
 *  \details      -
 *  \param[in]   nodeChannelState  State of node channel..
 *  \param[in]   nodeChannelIdx    Internal index of the node channel.
 *  \param[in]   channelIdx        Internal index of the channel.
 *  \param[in]   nodeIdx           Internal index of the node.
 *  \return      nmState:        State of NM.
 *  \pre         Parameters must be valid.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \spec
 *    requires   channelIdx < J1939Nm_GetSizeOfChannel();
 *    requires   nodeIdx < J1939Nm_GetSizeOfNode();
 *  \endspec
 **********************************************************************************************************************/
J1939NM_LOCAL_INLINE FUNC(void, J1939NM_CODE)
J1939Nm_InternalMainFunctionHandleNodeStateAcPending(const J1939Nm_NodeChannelStateType * nodeChannelState,
                                                     J1939Nm_NodeChannelChannelIndType nodeChannelIdx,
                                                     J1939Nm_SizeOfChannelType channelIdx,
                                                     J1939Nm_NodeIdxOfNodeChannelType nodeIdx);


/**********************************************************************************************************************
 *  J1939Nm_InternalRxIndication()
 *********************************************************************************************************************/
/*! \brief       Internal function that indicates the reception of Pdus
 *  \details      -
 *  \param[in]   RxPduId      Id of the Pdu (must be valid)
 *  \param[in]   info         Contains the length (SduLength) of the received I-PDU and a pointer to a buffer
 *                            (SduDataPtr) containing the I-PDU and MetaData. (must be valid)
 *  \pre         Parameters must be valid.
 *  \context     TASK|ISR
 *  \reentrant   TRUE for different RxPduIds.
 *  \synchronous TRUE
 *  \spec
 *    requires   (RxPduId < J1939Nm_GetSizeOfRxPdu()
 *               # if (J1939NM_INVALIDHNDOFRXPDU == STD_ON)
 *                 && (!J1939Nm_IsInvalidHndOfRxPdu(RxPduId))
 *               # endif;
 *    requires   $lengthOf(info->SduDataPtr) >= J1939NM_AC_PDU_LENGTH;
 *  \endspec
 *********************************************************************************************************************/
J1939NM_LOCAL_INLINE FUNC(void, J1939NM_CODE) J1939Nm_InternalRxIndication(PduIdType RxPduId,
                                                                           P2CONST(PduInfoType, AUTOMATIC,
                                                                                   J1939NM_APPL_DATA) info);



/**********************************************************************************************************************
 *  J1939Nm_InternalConfirmAc()
 *********************************************************************************************************************/
/*! \brief       Internal function that confirms the successful transmission of a J1939Nm AC PDU by the PduR.
 *  \details      -
 *  \param[in]   channelIdx    Index of the channel on which the pdu was transmitted.
 *  \param[out]  channelState  State of the channel on which the pdu was transmitted.
 *  \param[in]   pduState      State of the transmitted pdu.
 *  \pre         Parameters must be valid.
 *  \context     TASK|ISR
 *  \reentrant   TRUE for different pduStates resulting from different TxPduIds.
 *  \synchronous TRUE
 *********************************************************************************************************************/
J1939NM_LOCAL_INLINE FUNC(void, J1939NM_CODE) J1939Nm_InternalConfirmAc(J1939Nm_ChannelChannelIdxOfTxPduType channelIdx,
                                                                        J1939Nm_ChannelStateType * channelState,
                                                                        const J1939Nm_TxPduStateType * pduState);


/**********************************************************************************************************************
 *  J1939Nm_InternalAcRequestIndication()
 *********************************************************************************************************************/
/*! \brief       Internal function that indicates reception of a Ac Request PG.
 *  \details      -
 *  \param[in]   node            Node by which the request was received.
 *  \param[in]   channel         Channel on which the request was received.
 *  \param[in]   sourceAddress   Address of the node that sent the Request PG.
 *  \param[in]   destAddress     Address of this node or 0xFF for broadcast.
 *  \pre         Parameters must be valid.
 *  \context     TASK|ISR
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \spec
 *    requires   node < J1939Nm_GetSizeOfNode();
 *  \endspec
 *********************************************************************************************************************/
J1939NM_LOCAL_INLINE FUNC(void, J1939NM_CODE) J1939Nm_InternalAcRequestIndication(uint8 node, NetworkHandleType channel,
                                                                                  uint8 sourceAddress,
                                                                                  uint8 destAddress);


/***********************************************************************************************************************
 *  J1939Nm_InternalNetworkRequest()
 **********************************************************************************************************************/
/*! \brief       Internal function that requests the network, since ECU needs to communicate on the bus.
 *  \details      -
 *  \param[in]   channel         Identification of the NM-channel.
 *  \pre         Parameters must be valid.
 *  \context     TASK|ISR
 *  \reentrant   TRUE for different channels.
 *  \synchronous TRUE
 *  \spec
 *    requires   J1939Nm_Channel_Valid(channel);
 *  \endspec
 **********************************************************************************************************************/
J1939NM_LOCAL_INLINE FUNC(void, J1939NM_CODE)
J1939Nm_InternalNetworkRequest(CONST(NetworkHandleType, AUTOMATIC) channel);


/***********************************************************************************************************************
 *  J1939Nm_InternalSetStateAtNetworkRequest()
 **********************************************************************************************************************/
/*! \brief       Set the state of a channel during a network request.
 *  \details      -
 *  \param[in]   channelIdx      Internal index of the channel for which the state shall be changed.
 *  \param[out]  channelState    State of the channel
 *  \return      NM_STATE_OFFLINE:
 *               NM_STATE_NORMAL_OPERATION:
 *  \pre         Parameters must be valid.
 *  \context     TASK|ISR
 *  \reentrant   TRUE for different channels.
 *  \synchronous TRUE
 *  \spec
 *    requires   channelIdx < J1939Nm_GetSizeOfChannel();
 *  \endspec
 **********************************************************************************************************************/
J1939NM_LOCAL_INLINE FUNC(Nm_StateType, J1939NM_CODE)
J1939Nm_InternalSetStateAtNetworkRequest(J1939Nm_ChannelIdxOfComMChannelType channelIdx,
                                         J1939Nm_ChannelStateType * channelState);


/***********************************************************************************************************************
 *  J1939Nm_InternalNetworkRelease()
 **********************************************************************************************************************/
/*! \brief       Release the network, since ECU does not have to communicate on the bus.
 *  \details      -
 *  \param[in]   channel         Identification of the NM-channel.
 *  \pre         Parameters must be valid.
 *  \context     TASK|ISR
 *  \reentrant   TRUE for different channels.
 *  \synchronous FALSE
 *  \spec
 *    requires   J1939Nm_Channel_Valid(channel);
 *  \endspec
 **********************************************************************************************************************/
J1939NM_LOCAL_INLINE FUNC(void, J1939NM_CODE)
J1939Nm_InternalNetworkRelease(CONST(NetworkHandleType, AUTOMATIC) channel);


/***********************************************************************************************************************
 *  J1939Nm_InternalGetState()
 **********************************************************************************************************************/
/*! \brief       Returns the state and the mode of the network management.
 *  \details      -
 *  \param[in]   channel         Identification of the NM-channel.
 *  \param[out]  stateP          Pointer where state of the network management shall be copied to.
 *  \param[out]  modeP           Pointer where the mode of the network management shall be copied to.
 *  \pre         Parameters must be valid.
 *  \context     TASK|ISR
 *  \reentrant   TRUE
 *  \synchronous TRUE
 **********************************************************************************************************************/
J1939NM_LOCAL_INLINE FUNC(void, J1939NM_CODE)
J1939Nm_InternalGetState(CONST(NetworkHandleType, AUTOMATIC) channel,
                         CONSTP2VAR(Nm_StateType, AUTOMATIC, J1939NM_APPL_VAR) stateP,
                         CONSTP2VAR(Nm_ModeType, AUTOMATIC, J1939NM_APPL_VAR) modeP);


/***********************************************************************************************************************
 *  J1939Nm_InternalGetBusOffDelay()
 **********************************************************************************************************************/
/*! \brief       Called when a bus-off was detected by the CanSM, returns the number of CanSM main cycles to delay the
 *               recovery.
 *  \details      -
 *  \param[in]   channel         ComM network ID of the affected channel.
 *  \param[out]  delayCyclesPtr  Pointer to the location where the number of delay cycles shall be stored.
 *  \pre         delayCyclesPtr must be valid.
 *  \context     TASK|ISR
 *  \reentrant   TRUE for different networks.
 *  \synchronous TRUE
 **********************************************************************************************************************/
J1939NM_LOCAL_INLINE FUNC(void, J1939NM_CODE)
J1939Nm_InternalGetBusOffDelay(NetworkHandleType channel, P2VAR(uint8, AUTOMATIC, J1939NM_APPL_VAR) delayCyclesPtr);


#if (J1939NM_USESADDRESSARBITRATIONOFCHANNEL == STD_ON)
/**********************************************************************************************************************
 *  J1939Nm_InternalCheckAcCollisionOfTransmittedAc()
 *********************************************************************************************************************/
/*! \brief       Checks for name and address collisions of transmitted AddressClaimed (AC) messages.
 *  \details      -
 *  \param[out]  info            AC PDU
 *  \param[in]   channelIdx      Internal index of the channel for which the AC collision is checked.
 *  \param[in]   nodeIdx         Internal index of the node for which the AC collision is checked.
 *  \param[out]  channelState    State of the channel.
 *  \param[out]  nodeChannelState   State of the node channel.
 *  \param[in]   nodeChannelIdx  Internal index of the node channel for which the AC collision is checked
 *  \param[in]   nodeAddress     Address of internal node.
 *  \param[out]  nameConflict    Displays name conflict of AC names.
 *  \return      nmState:        State of NM.
 *  \pre         Parameters must be valid.
 *  \context     TASK|ISR
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \spec
 *    requires   $lengthOf(info->SduDataPtr) >= J1939NM_AC_PDU_LENGTH;
 *    requires   nodeChannelIdx < J1939Nm_GetSizeOfNodeChannel();
 *  \endspec
 **********************************************************************************************************************/

J1939NM_LOCAL_INLINE FUNC(Nm_StateType, J1939NM_CODE)
J1939Nm_InternalCheckAcCollisionOfTransmittedAc(P2CONST(PduInfoType, AUTOMATIC, J1939NM_APPL_DATA) info,
                                                J1939Nm_ChannelChannelIdxOfRxPduType channelIdx,
                                                J1939Nm_NodeIdxOfNodeChannelType nodeIdx,
                                                J1939Nm_ChannelStateType * channelState,
                                                J1939Nm_NodeChannelStateType * nodeChannelState,
                                                J1939Nm_NodeChannelChannelIndType nodeChannelIdx, uint8 nodeAddress,
                                                boolean * nameConflict);
#endif

#define J1939NM_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*================================================ J1939NM_STOP_SEC_CODE ===========================================*/


/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/*================================================ J1939NM_START_SEC_CODE ===========================================*/
#define J1939NM_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  J1939Nm_InternalSendAc()
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
 */
/* *INDENT-OFF* */
/* PRQA S 6050 4 */ /* MD_MSR_STCAL */
/* *INDENT-ON* */
J1939NM_LOCAL_INLINE FUNC(void, J1939NM_CODE) J1939Nm_InternalSendAc(const J1939Nm_SizeOfChannelType channelIdx,
                                                                     const J1939Nm_SizeOfNodeType nodeIdx,
                                                                     const uint8 sourceAddress)
{
  J1939Nm_TxPduAcIdxOfChannelType txPduIdx = J1939Nm_GetTxPduAcIdxOfChannel(channelIdx);
  J1939Nm_TxPduStateType *pduState = &J1939Nm_GetTxPduState(J1939Nm_GetTxPduStateIdxOfTxPdu(txPduIdx));

  /* #10 Enter exclusive area J1939NM_EXCLUSIVE_AREA_TXPDULOCK. */
  SchM_Enter_J1939Nm_J1939NM_EXCLUSIVE_AREA_TXPDULOCK();
  /* #20 Check if the Pdu to use is free: */
  if (!pduState->Locked) /* PRQA S 4558 */ /* MD_MSR_AutosarBoolean */
  {
    pduState->Locked = TRUE; /* VCA_J1939NM_TXPDUSTATE_VIA_CHANNEL_CSL03 */
    /* #30 Leave exclusive area J1939NM_EXCLUSIVE_AREA_TXPDULOCK. */
    SchM_Exit_J1939Nm_J1939NM_EXCLUSIVE_AREA_TXPDULOCK();

    /* #40 Prepare the Pdu with the data to transmit. Set Confirmation timeout. \trace SPEC-2168279 */
    pduState->NodeId = (uint16) nodeIdx; /* VCA_J1939NM_TXPDUSTATE_VIA_CHANNEL_CSL03 */
    pduState->IsExtNodeId = FALSE; /* VCA_J1939NM_TXPDUSTATE_VIA_CHANNEL_CSL03 */
    pduState->ConfTimeout = J1939Nm_GetTxConfTimeout(); /* VCA_J1939NM_TXPDUSTATE_VIA_CHANNEL_CSL03 */

    {
      uint8 data[J1939NM_AC_PDU_LENGTH];
      PduInfoType pdu;

      pdu.SduDataPtr = data;
      pdu.SduLength =
        (PduLengthType) J1939NM_AC_FRAME_LENGTH + (PduLengthType) J1939Nm_GetMetaDataLengthOfTxPdu(txPduIdx);


      {
        /* #50 If J1939NM_NM_PG_SUPPORT or J1939NM_NAME_MANAGEMENT_SUPPORT is enabled: */
#if ((J1939NM_NM_PG_SUPPORT == STD_ON) || (J1939NM_NAME_MANAGEMENT_SUPPORT == STD_ON))
        const uint8 *currentNodeName = J1939Nm_GetCurrentNodeName(J1939Nm_GetCurrentNodeNameIdxOfNode(nodeIdx));
        /* #60 Enter exclusive area J1939NM_EXCLUSIVE_AREA_NAMELOCK. */
        SchM_Enter_J1939Nm_J1939NM_EXCLUSIVE_AREA_NAMELOCK();
        /* #70 Copy current node name. */
        J1939Nm_InternalCopyName(&(data[J1939NM_AC_NAME_BYTE1]), currentNodeName); /* VCA_J1939NM_CURRENTNODENAME_VIA_NODE_CSL03 */
        /* #80 Leave exclusive area J1939NM_EXCLUSIVE_AREA_NAMELOCK. */
        SchM_Exit_J1939Nm_J1939NM_EXCLUSIVE_AREA_NAMELOCK();
#else
        /* #90 Otherwise, get node name. */
        J1939Nm_NodeNameIdxOfNodeType nodeNameIdx = J1939Nm_GetNodeNameIdxOfNode(nodeIdx);

        J1939Nm_InternalGetName(data, nodeNameIdx);
#endif
        data[J1939NM_AC_SA_POS] = sourceAddress;
      }

      /* #100 Transmit pdu. \trace SPEC-2168275, SPEC-2168305 */
      /* #110 If transmission was unsuccessful, free pdu. */
      if (CanIf_Transmit(J1939Nm_GetPduIdOfTxPdu(txPduIdx), &pdu) != E_OK) /* VCA_J1939NM_UNDEF_FCTCALL_PTR2LOCAL */
      {
        pduState->Locked = FALSE; /* VCA_J1939NM_TXPDUSTATE_VIA_CHANNEL_CSL03 */
      }
#if ((J1939NM_DYNAMIC_ADDRESS_SUPPORT == STD_ON) || (J1939NM_USERCALLOUT == STD_ON))
      /* #120 Otherwise: */
      else
      {
# if (J1939NM_USERCALLOUT == STD_ON)
        /* #130 Forward source Ac content to callout function. */
        J1939Nm_GetUserCallout()(J1939Nm_GetComMChannelIdOfChannel(channelIdx), data[8], data); /* VCA_J1939NM_UNDEF_FCTCALL */
# endif

# if (J1939NM_DYNAMIC_ADDRESS_SUPPORT == STD_ON)
        /* #140 If channel uses dynamic addressing: */
        if (J1939Nm_IsUsesDynamicAddressingOfChannel(channelIdx))
        {
          /* #150 Update states. */
          /* Cast to void because a NAME conflict cannot occurr in this case. */
          (void) J1939Nm_InternalCheckAcCollision(channelIdx, &pdu, nodeIdx); /* VCA_J1939NM_FCTCALL_PTR2LOCAL */
#  if ((J1939NM_GATEWAY_SUPPORT == STD_ON))
          (void) J1939Nm_DynamicCheckAcCollision(channelIdx, &pdu, J1939NM_INVALID_NODE); /* VCA_J1939NM_FCTCALL_PTR2LOCAL */
#  endif
        }
# endif
      }
#endif
    }
  }
  /* #160 Otherwise, leave exclusive area J1939NM_EXCLUSIVE_AREA_TXPDULOCK. \trace SPEC-2168276 */
  else
  {
    SchM_Exit_J1939Nm_J1939NM_EXCLUSIVE_AREA_TXPDULOCK();
  }
} /* J1939Nm_InternalSendAc() */


/**********************************************************************************************************************
 *  J1939Nm_InternalCalcDelay()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
J1939NM_LOCAL_INLINE FUNC(uint8, J1939NM_CODE) J1939Nm_InternalCalcDelay(const J1939Nm_SizeOfNodeType nodeIdx,
                                                                         const boolean intern)
{
  J1939Nm_RandomSeedIdxOfNodeType randomSeedIdx = J1939Nm_GetRandomSeedIdxOfNode(nodeIdx);
  uint8 delayCycles;

  /* #10 Calculate and set random seed with mixed congruential generator: x(n+1) = a * x(n) + b */
  uint8 random = (uint8) ((J1939NM_RANDOM_FACTOR * J1939Nm_GetRandomSeed(randomSeedIdx)) + J1939NM_RANDOM_OFFSET);
  J1939Nm_SetRandomSeed(randomSeedIdx, random); /* VCA_J1939NM_RANDOMSEED_VIA_NODE_CSL03 */

  /* #20 If parameter intern is set, calulate J1939Nm main function cycles. */
  if (intern)
  {
    delayCycles = (uint8) (((uint32) J1939Nm_GetJ1939NmDelayFactor() * (uint32) random) / J1939NM_RANDOM_SCALING);
  }
  /* #30 Otherwise, calculate CanSM main function cycles. */
  else
  {
    delayCycles = (uint8) (((uint32) J1939Nm_GetCanSMDelayFactor() * (uint32) random) / J1939NM_RANDOM_SCALING);
  }

  return delayCycles;
} /* J1939Nm_InternalCalcDelay() */

#define J1939NM_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*================================================ J1939NM_STOP_SEC_CODE ============================================*/


/**********************************************************************************************************************
 *  INTERNAL FUNCTIONS
 *********************************************************************************************************************/

/*================================================ J1939NM_START_SEC_CODE ===========================================*/
#define J1939NM_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#if (J1939NM_USESADDRESSARBITRATIONOFCHANNEL == STD_ON)
/**********************************************************************************************************************
 *  J1939Nm_InternalCheckAcCollision()
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
/* *INDENT-OFF* */
/* PRQA S 6080 4 */ /* MD_MSR_STMIF */
/* *INDENT-ON* */
FUNC(boolean, J1939NM_CODE) J1939Nm_InternalCheckAcCollision(J1939Nm_ChannelChannelIdxOfRxPduType channelIdx,
                                                             P2CONST(PduInfoType, AUTOMATIC, J1939NM_APPL_DATA) info,
                                                             uint16 localNodeIdx)
{
  J1939Nm_ChannelStateType *channelState = &J1939Nm_GetChannelState(channelIdx);
  J1939Nm_NodeChannelChannelIndEndIdxOfChannelType nodeChannelIndIdx;
  uint8 sa = info->SduDataPtr[J1939NM_AC_SA_POS];
  Nm_StateType nmState = NM_STATE_OFFLINE;
  boolean nameConflict = FALSE;

  /* #10 Iterate over all nodes. */
  for (nodeChannelIndIdx = J1939Nm_GetNodeChannelChannelIndStartIdxOfChannel(channelIdx);
       nodeChannelIndIdx < J1939Nm_GetNodeChannelChannelIndEndIdxOfChannel(channelIdx); nodeChannelIndIdx++)
  {
    J1939Nm_NodeChannelChannelIndType nodeChannelIdx = J1939Nm_GetNodeChannelChannelInd(nodeChannelIndIdx);
    J1939Nm_NodeIdxOfNodeChannelType nodeIdx = J1939Nm_GetNodeIdxOfNodeChannel(nodeChannelIdx);
    J1939Nm_NodeChannelStateType *nodeChannelState =
      &J1939Nm_GetNodeChannelState(J1939Nm_GetNodeChannelStateIdxOfNodeChannel(nodeChannelIdx));

    /* #20 If nodes does not match local node and nodestate is (pre)normal or (pre)claiming: */
    if (nodeIdx != localNodeIdx)
    {
      if ((nodeChannelState->NodeState == J1939NM_NODESTATE_NORMAL) ||
          (nodeChannelState->NodeState == J1939NM_NODESTATE_CLAIMING) ||
          (nodeChannelState->NodeState == J1939NM_NODESTATE_PRE_CLAIMING) ||
          (nodeChannelState->NodeState == J1939NM_NODESTATE_PRE_NORMAL))
      {
        /* #30 Get node address. */
        uint8 nodeAddress;
# if (J1939NM_DYNAMIC_ADDRESS_SUPPORT == STD_ON)
        J1939Nm_CurrentNodeAddressIdxOfNodeChannelType currentNodeAddressIdx =
          J1939Nm_GetCurrentNodeAddressIdxOfNodeChannel(nodeChannelIdx);

        if (J1939Nm_IsUsesDynamicAddressingOfChannel(channelIdx))
        {
          nodeAddress = J1939Nm_GetCurrentNodeAddress(currentNodeAddressIdx);
        }
        else
# endif
        {
          nodeAddress = J1939Nm_GetNodeAddressOfNode(nodeIdx);
        }

        /*
         * #40 If node address equals source address of transmitted AC:
         *     T O D O: Always compare NAME and report if DET is enabled (see ALM+ issue 84909)
         */
        if (nodeAddress == sa)
        {
          /* #50 Check name or address collision and set network management state depending on kind of collison. */
          /*@ assert nodeChannelIdx < J1939Nm_GetSizeOfNodeChannel(); */ /* VCA_J1939NM_NODECHANNEL_VIA_CHANNEL_CSL03 */
          nmState = J1939Nm_InternalCheckAcCollisionOfTransmittedAc(info, channelIdx, nodeIdx, /* VCA_J1939NM_POINTERPASSEDTOPUBLICAPI */
                                                                    channelState, nodeChannelState, nodeChannelIdx,
                                                                    nodeAddress, &nameConflict);
        }
        /* #60 Otherwise, set network management state to normal. */
        else
        {
          if (nodeChannelState->NodeState == J1939NM_NODESTATE_NORMAL)
          {
            nmState = NM_STATE_NORMAL_OPERATION;
          }
        }
      }
    }
    /* #70 Otherwise, set network management state to normal. */
    else
    {
      if (nodeChannelState->NodeState == J1939NM_NODESTATE_NORMAL)
      {
        nmState = NM_STATE_NORMAL_OPERATION;
      }
    }
  }

  /* #80 Update channelstate. \trace SPEC-2168273 */
  if (nmState != channelState->NmState)
  {
    channelState->NmState = nmState; /* VCA_J1939NM_CHANNELSTATE_VIA_CHANNEL_CSL03 */
# if (J1939NM_NM_STATECHANGENOTIF == STD_ON)
    channelState->StatePending = TRUE; /* VCA_J1939NM_CHANNELSTATE_VIA_CHANNEL_CSL03 */
# endif
  }

  return nameConflict;
} /* J1939Nm_InternalCheckAcCollision() */
#endif


/**********************************************************************************************************************
 *  J1939Nm_InternalGetName()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, J1939NM_CODE) J1939Nm_InternalGetName(J1939Nm_NameType nodeName,
                                                 const J1939Nm_SizeOfNodeNameType nodeNameIdx)
{
  /* Copy node name belonging to provided index to array. */
  nodeName[J1939NM_NAME_BYTE8] = J1939Nm_GetNodeNameByte8OfNodeName(nodeNameIdx);
  nodeName[J1939NM_NAME_BYTE7] = J1939Nm_GetNodeNameByte7OfNodeName(nodeNameIdx);
  nodeName[J1939NM_NAME_BYTE6] = J1939Nm_GetNodeNameByte6OfNodeName(nodeNameIdx);
  nodeName[J1939NM_NAME_BYTE5] = J1939Nm_GetNodeNameByte5OfNodeName(nodeNameIdx);
  nodeName[J1939NM_NAME_BYTE4] = J1939Nm_GetNodeNameByte4OfNodeName(nodeNameIdx);
  nodeName[J1939NM_NAME_BYTE3] = J1939Nm_GetNodeNameByte3OfNodeName(nodeNameIdx);
  nodeName[J1939NM_NAME_BYTE2] = J1939Nm_GetNodeNameByte2OfNodeName(nodeNameIdx);
  nodeName[J1939NM_NAME_BYTE1] = J1939Nm_GetNodeNameByte1OfNodeName(nodeNameIdx);
} /* J1939Nm_InternalGetName() */


#if (((J1939NM_DYNAMIC_ADDRESS_SUPPORT == STD_ON) && (J1939NM_EXTERNAL_NODES_USED == STD_ON)) || (J1939NM_NM_PG_SUPPORT == STD_ON) || (J1939NM_GATEWAY_SUPPORT == STD_ON) || (J1939NM_NAME_MANAGEMENT_SUPPORT == STD_ON))
/**********************************************************************************************************************
 *  J1939Nm_InternalCopyName()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, J1939NM_CODE) J1939Nm_InternalCopyName(uint8 * newNodeName,
                                                  P2CONST(uint8, AUTOMATIC, J1939NM_APPL_DATA) oldNodeName)
{
  /* Copy provided node name array to another provided node name array. */
  newNodeName[J1939NM_NAME_BYTE8] = oldNodeName[J1939NM_NAME_BYTE8];
  newNodeName[J1939NM_NAME_BYTE7] = oldNodeName[J1939NM_NAME_BYTE7];
  newNodeName[J1939NM_NAME_BYTE6] = oldNodeName[J1939NM_NAME_BYTE6];
  newNodeName[J1939NM_NAME_BYTE5] = oldNodeName[J1939NM_NAME_BYTE5];
  newNodeName[J1939NM_NAME_BYTE4] = oldNodeName[J1939NM_NAME_BYTE4];
  newNodeName[J1939NM_NAME_BYTE3] = oldNodeName[J1939NM_NAME_BYTE3];
  newNodeName[J1939NM_NAME_BYTE2] = oldNodeName[J1939NM_NAME_BYTE2];
  newNodeName[J1939NM_NAME_BYTE1] = oldNodeName[J1939NM_NAME_BYTE1];
} /* J1939Nm_InternalCopyName() */
#endif


/**********************************************************************************************************************
 *  J1939Nm_InternalNameCompare()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
/* *INDENT-OFF* */
/* PRQA S 6080 3 */ /* MD_MSR_STMIF */
/* *INDENT-ON* */
FUNC(sint16_least, J1939NM_CODE) J1939Nm_InternalNameCompare(P2CONST(uint8, AUTOMATIC, J1939NM_APPL_DATA) ownNodeName,
                                                             P2CONST(uint8, AUTOMATIC, J1939NM_APPL_DATA) otherNodeName)
{
  /* Compare two node name arrays for differences. */
  sint16_least nameDiffers;

  nameDiffers = ((sint16_least) ownNodeName[J1939NM_NAME_BYTE8] - (sint16_least) otherNodeName[J1939NM_NAME_BYTE8]);
  if (nameDiffers == 0)
  {
    nameDiffers = ((sint16_least) ownNodeName[J1939NM_NAME_BYTE7] - (sint16_least) otherNodeName[J1939NM_NAME_BYTE7]);
    if (nameDiffers == 0)
    {
      nameDiffers = ((sint16_least) ownNodeName[J1939NM_NAME_BYTE6] - (sint16_least) otherNodeName[J1939NM_NAME_BYTE6]);
      if (nameDiffers == 0)
      {
        nameDiffers =
          ((sint16_least) ownNodeName[J1939NM_NAME_BYTE5] - (sint16_least) otherNodeName[J1939NM_NAME_BYTE5]);
        if (nameDiffers == 0)
        {
          nameDiffers =
            ((sint16_least) ownNodeName[J1939NM_NAME_BYTE4] - (sint16_least) otherNodeName[J1939NM_NAME_BYTE4]);
          if (nameDiffers == 0)
          {
            nameDiffers =
              ((sint16_least) ownNodeName[J1939NM_NAME_BYTE3] - (sint16_least) otherNodeName[J1939NM_NAME_BYTE3]);
            if (nameDiffers == 0)
            {
              nameDiffers =
                ((sint16_least) ownNodeName[J1939NM_NAME_BYTE2] - (sint16_least) otherNodeName[J1939NM_NAME_BYTE2]);
              if (nameDiffers == 0)
              {
                nameDiffers =
                  ((sint16_least) ownNodeName[J1939NM_NAME_BYTE1] - (sint16_least) otherNodeName[J1939NM_NAME_BYTE1]);
              }
            }
          }
        }
      }
    }
  }

  return nameDiffers;
} /* J1939Nm_InternalNameCompare() */

/**********************************************************************************************************************
 *  J1939Nm_InternalInit()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
J1939NM_LOCAL_INLINE FUNC(void, J1939NM_CODE) J1939Nm_InternalInit(void)
{
  /* Initialize all component variables. */
#if ((J1939NM_ADDRESSSTORAGEBLOCK == STD_ON) || (J1939NM_NAMESTORAGEBLOCK == STD_ON))

  Std_ReturnType result;
  uint8 errorStatus;

  result = NvM_GetErrorStatus(NvMConf___MultiBlockRequest, &errorStatus); /* VCA_J1939NM_UNDEF_FCTCALL_PTR2LOCAL */

  if ((result == E_OK) && (errorStatus != NVM_REQ_PENDING))
  {

# if (J1939NM_ADDRESSSTORAGEBLOCK == STD_ON)
    result = NvM_GetErrorStatus((NvM_BlockIdType) NvMConf_NvMBlockDescriptor_J1939Nm_CurrentNodeAddresses, &errorStatus); /* VCA_J1939NM_UNDEF_FCTCALL_PTR2LOCAL */

    if (result == E_OK)
    {

      if (errorStatus != NVM_REQ_OK)
      {
        (void) NvM_SetRamBlockStatus((NvM_BlockIdType) NvMConf_NvMBlockDescriptor_J1939Nm_CurrentNodeAddresses, TRUE);
      }
# endif

# if (J1939NM_NAMESTORAGEBLOCK == STD_ON)
      result = NvM_GetErrorStatus((NvM_BlockIdType) NvMConf_NvMBlockDescriptor_J1939Nm_CurrentNodeNames, &errorStatus); /* VCA_J1939NM_UNDEF_FCTCALL_PTR2LOCAL */

      if (result == E_OK)
      {

        if (errorStatus != NVM_REQ_OK)
        {
          (void) NvM_SetRamBlockStatus((NvM_BlockIdType) NvMConf_NvMBlockDescriptor_J1939Nm_CurrentNodeNames, TRUE);
        }
# endif

#endif



        J1939Nm_InternalInitRandomSeed(); /* PRQA S 2987 */ /* MD_J1939Nm_2.2 */

        J1939Nm_InternalInitNodeChannelState(); /* PRQA S 2987 */ /* MD_J1939Nm_2.2 */

        J1939Nm_InternalInitChannelState(); /* PRQA S 2987 */ /* MD_J1939Nm_2.2 */

        {
          J1939Nm_SizeOfTxPduStateType txPduStateIdx;

          for (txPduStateIdx = 0; txPduStateIdx < J1939Nm_GetSizeOfTxPduState(); txPduStateIdx++)
          {
            J1939Nm_GetTxPduState(txPduStateIdx).Locked = FALSE; /* VCA_J1939NM_TXPDUSTATE_CSL01 */
          }
        }

#if ((J1939NM_DYNAMIC_ADDRESS_SUPPORT == STD_ON) || (J1939NM_GATEWAY_SUPPORT == STD_ON) || (J1939NM_NM_PG_SUPPORT == STD_ON) || (J1939NM_NAME_MANAGEMENT_SUPPORT == STD_ON))
        J1939Nm_DynamicInit();
#endif

        J1939Nm_ModuleInitialized = J1939NM_INIT;


#if (J1939NM_NAMESTORAGEBLOCK == STD_ON)
      }
#endif

#if (J1939NM_ADDRESSSTORAGEBLOCK == STD_ON)
    }
#endif

#if ((J1939NM_ADDRESSSTORAGEBLOCK == STD_ON) || (J1939NM_NAMESTORAGEBLOCK == STD_ON))
  }
#endif
} /* J1939Nm_InternalInit() */


/**********************************************************************************************************************
 *  J1939Nm_InternalInitRandomSeed()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
J1939NM_LOCAL_INLINE FUNC(void, J1939NM_CODE) J1939Nm_InternalInitRandomSeed(void)
{
  J1939Nm_SizeOfNodeType nodeIdx;

  /* #10 Iterate over all nodes. */
  for (nodeIdx = 0; nodeIdx < J1939Nm_GetSizeOfNode(); nodeIdx++)
  {
    /* #20 Get nodename. */
#if ((J1939NM_NM_PG_SUPPORT == STD_ON) || (J1939NM_NAME_MANAGEMENT_SUPPORT == STD_ON))
    const uint8 *currentNodeName = J1939Nm_GetCurrentNodeName(J1939Nm_GetCurrentNodeNameIdxOfNode(nodeIdx));
#else
    J1939Nm_NodeNameIdxOfNodeType nodeNameIdx = J1939Nm_GetNodeNameIdxOfNode(nodeIdx);
    uint8 currentNodeName[J1939NM_NAME_LENGTH];

    J1939Nm_InternalGetName(currentNodeName, nodeNameIdx); /* VCA_J1939NM_CURRENTNODENAME_VIA_NODE_CSL03 */
#endif
    /* #30 Set random seed. */
    J1939Nm_SetRandomSeed(J1939Nm_GetRandomSeedIdxOfNode(nodeIdx), /* VCA_J1939NM_RANDOMSEED_VIA_NODE_CSL03 */
                          currentNodeName[J1939NM_NAME_BYTE1] + currentNodeName[J1939NM_NAME_BYTE2] +
                          currentNodeName[J1939NM_NAME_BYTE3] + currentNodeName[J1939NM_NAME_BYTE4] +
                          currentNodeName[J1939NM_NAME_BYTE5] + currentNodeName[J1939NM_NAME_BYTE6] +
                          currentNodeName[J1939NM_NAME_BYTE7] + currentNodeName[J1939NM_NAME_BYTE8]);
  }
} /* J1939Nm_InternalInitRandomSeed() */


/**********************************************************************************************************************
 *  J1939Nm_InternalInitNodeChannelState()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
J1939NM_LOCAL_INLINE FUNC(void, J1939NM_CODE) J1939Nm_InternalInitNodeChannelState(void)
{
  /* Init nodechannelstate for each nodechannel. */
  J1939Nm_SizeOfNodeChannelType nodeChannelIdx;

  for (nodeChannelIdx = 0; nodeChannelIdx < J1939Nm_GetSizeOfNodeChannel(); nodeChannelIdx++)
  {
    J1939Nm_NodeChannelStateType *nodeChannelState =
      &J1939Nm_GetNodeChannelState(J1939Nm_GetNodeChannelStateIdxOfNodeChannel(nodeChannelIdx));

    nodeChannelState->AcPending = FALSE; /* VCA_J1939NM_NODECHANNELSTATE_VIA_NODECHANNEL_CSL03 */
    nodeChannelState->AcDelayed = FALSE; /* VCA_J1939NM_NODECHANNELSTATE_VIA_NODECHANNEL_CSL03 */
    /* \trace SPEC-2168263 */
    nodeChannelState->NodeState = J1939NM_NODESTATE_BUS_SLEEP; /* VCA_J1939NM_NODECHANNELSTATE_VIA_NODECHANNEL_CSL03 */
    nodeChannelState->StatePending = FALSE; /* VCA_J1939NM_NODECHANNELSTATE_VIA_NODECHANNEL_CSL03 */
  }
} /* J1939Nm_InternalInitNodeChannelState() */


/**********************************************************************************************************************
 *  J1939Nm_InternalInitChannelState()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
J1939NM_LOCAL_INLINE FUNC(void, J1939NM_CODE) J1939Nm_InternalInitChannelState(void)
{
  /* Init channelstate for each channel. */
  J1939Nm_SizeOfChannelType channelIdx;

  for (channelIdx = 0; channelIdx < J1939Nm_GetSizeOfChannel(); channelIdx++)
  {
    J1939Nm_ChannelStateType *channelState = &J1939Nm_GetChannelState(channelIdx);

    channelState->NmMode = NM_MODE_BUS_SLEEP; /* VCA_J1939NM_CHANNELSTATE_VIA_CHANNEL_CSL03 */
    channelState->NmState = NM_STATE_BUS_SLEEP; /* VCA_J1939NM_CHANNELSTATE_VIA_CHANNEL_CSL03 */
    channelState->BusOff = FALSE; /* VCA_J1939NM_CHANNELSTATE_VIA_CHANNEL_CSL03 */
#if (J1939NM_NM_STATECHANGENOTIF == STD_ON)
    channelState->PreviousNmState = NM_STATE_BUS_SLEEP; /* VCA_J1939NM_CHANNELSTATE_VIA_CHANNEL_CSL03 */
    channelState->StatePending = FALSE; /* VCA_J1939NM_CHANNELSTATE_VIA_CHANNEL_CSL03 */
#endif
  }
} /* J1939Nm_InternalInitChannelState() */


/**********************************************************************************************************************
 *  J1939Nm_InternalConfTimeoutHandling()
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
/* *INDENT-OFF* */
/* PRQA S 6080 2 */ /* MD_MSR_STMIF */
/* *INDENT-ON* */
J1939NM_LOCAL_INLINE FUNC(void, J1939NM_CODE) J1939Nm_InternalConfTimeoutHandling(void)
{
  J1939Nm_SizeOfTxPduType txPduIdx;

  /* #10 Iterate over all TxPdus. */
  for (txPduIdx = 0; txPduIdx < J1939Nm_GetSizeOfTxPdu(); txPduIdx++)
  {
#if (J1939NM_INVALIDHNDOFTXPDU == STD_ON)
    if (!J1939Nm_IsInvalidHndOfTxPdu(txPduIdx))
#endif
    {
#if (J1939NM_EXISTS_TP_PDU_IFTYPEOFTXPDU == STD_ON)
      if (J1939Nm_GetIfTypeOfTxPdu(txPduIdx) == J1939NM_IF_PDU_IFTYPEOFTXPDU)
#endif
	    {
        J1939Nm_TxPduStateType *pduState = &J1939Nm_GetTxPduState(J1939Nm_GetTxPduStateIdxOfTxPdu(txPduIdx));

		/* #20 Check if the Pdu to use is used and decrease timeout: */
        if (pduState->Locked == TRUE)
        {
          --pduState->ConfTimeout; /* VCA_J1939NM_TXPDUSTATE_VIA_TXPDU_CSL03 */
    
          /* #30 Release pdu if confirmation timeout is elapsed. */
          if (pduState->ConfTimeout == 0u)
          {
#if (J1939NM_NM_PG_SUPPORT == STD_ON)
            /* #40 If it is a NM Tx pdu: deactivate pending name. */
            if (J1939Nm_GetPduTypeOfTxPdu(txPduIdx) == J1939NM_NM_TX_PDU_PDUTYPEOFTXPDU)
            {
              J1939Nm_DynamicDropPendingName();
            }
#endif

            /* #50 Trigger Pg again. \trace SPEC-2168279 */
            pduState->Locked = FALSE;
#if (J1939NM_RUNTIME_ERROR_REPORT == STD_ON)
            J1939Nm_ReportRuntimeError(J1939NM_SID_MAINFUNCTION, J1939NM_E_TIMEOUT_TXCONF);
#endif
          }
        }
      }
    }
  }
} /* J1939Nm_InternalConfTimeoutHandling() */


/**********************************************************************************************************************
 *  J1939Nm_InternalMainFunction()
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
/* *INDENT-OFF* */
/* PRQA S 6030, 6080 2 */ /* MD_MSR_STCYC, MD_MSR_STMIF */
/* *INDENT-ON* */
J1939NM_LOCAL_INLINE FUNC(void, J1939NM_CODE) J1939Nm_InternalMainFunction(void)
{
  J1939Nm_SizeOfChannelType channelIdx;

  /* #10 Iterate over all channels. */
  for (channelIdx = 0; channelIdx < J1939Nm_GetSizeOfChannel(); channelIdx++)
  {
    J1939Nm_ChannelStateType *channelState = &J1939Nm_GetChannelState(channelIdx);

    /* #20 If channel is online: Iterate over all nodes. */
    if ((!channelState->BusOff) && (channelState->NmMode == NM_MODE_NETWORK)) /* PRQA S 4558 */ /* MD_MSR_AutosarBoolean */
    {
      NetworkHandleType comMChannel = J1939Nm_GetComMChannelIdOfChannel(channelIdx);
      J1939Nm_NodeChannelChannelIndIterType nodeChannelIndIdx;

      Nm_StateType nmState = channelState->NmState;

      for (nodeChannelIndIdx = J1939Nm_GetNodeChannelChannelIndStartIdxOfChannel(channelIdx);
           nodeChannelIndIdx < J1939Nm_GetNodeChannelChannelIndEndIdxOfChannel(channelIdx); nodeChannelIndIdx++)
      {
        J1939Nm_NodeChannelChannelIndType nodeChannelIdx = J1939Nm_GetNodeChannelChannelInd(nodeChannelIndIdx);
        J1939Nm_NodeIdxOfNodeChannelType nodeIdx = J1939Nm_GetNodeIdxOfNodeChannel(nodeChannelIdx);
        J1939Nm_NodeChannelStateType *nodeChannelState =
          &J1939Nm_GetNodeChannelState(J1939Nm_GetNodeChannelStateIdxOfNodeChannel(nodeChannelIdx));

        /* #30 If node is not offline: */
        if (nodeChannelState->NodeState != J1939NM_NODESTATE_BUS_SLEEP) /* PRQA S 4558 */ /* MD_MSR_AutosarBoolean */
        {
          /* #40 If node is in state claiming: Handle timeouts and state changes in subfunction. */
          if (nodeChannelState->NodeState == J1939NM_NODESTATE_CLAIMING)
          {
            J1939Nm_InternalMainFunctionHandleNodeStateClaiming(nodeChannelState, &nmState);
          }

          /* #50 If node is in state Ac delayed: Handle timeouts and state changes in subfunction. */
          if (nodeChannelState->AcDelayed)
          {
            J1939Nm_InternalMainFunctionHandleNodeStateAcDelayed(nodeChannelState, nodeIdx);
          }

          /* #60 If node is in state Ac pending: Handle timeouts and state changes in subfunction. \trace SPEC-2168278 */
          if (nodeChannelState->AcPending)
          {
            /*@ assert nodeIdx < J1939Nm_GetSizeOfNode(); */ /* VCA_J1939NM_NODE_VIA_CHANNEL_CSL03 */
            J1939Nm_InternalMainFunctionHandleNodeStateAcPending(nodeChannelState, nodeChannelIdx, channelIdx, nodeIdx);
          }
        }

        /* #70 If node channel is pending: Make a BswM state change notification. \trace SPEC-2168305 */
        if (nodeChannelState->StatePending)
        {
          nodeChannelState->StatePending = FALSE; /* VCA_J1939NM_NODECHANNELSTATE_VIA_CHANNEL_CSL03 */

          BswM_J1939Nm_StateChangeNotification(comMChannel, (uint8) nodeIdx, nmState);
        }
      }

      if (nmState != channelState->NmState)
      {
        channelState->NmState = nmState;
#if (J1939NM_NM_STATECHANGENOTIF == STD_ON)
        channelState->StatePending = TRUE; /* VCA_J1939NM_CHANNELSTATE_VIA_CHANNEL_CSL03 */
#endif
      }

      /* #80 If channel is pending: Make a Nm state change notification. \trace SPEC-2168305 */
#if (J1939NM_NM_STATECHANGENOTIF == STD_ON)
      if (channelState->StatePending)
      {
        channelState->StatePending = FALSE;
        Nm_StateChangeNotification(comMChannel, channelState->PreviousNmState, channelState->NmState);
        channelState->PreviousNmState = channelState->NmState;
      }
#endif
    }
  }
} /* J1939Nm_InternalMainFunction() */


/**********************************************************************************************************************
 *  J1939Nm_InternalRxIndication()
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
/* *INDENT-OFF* */
/* PRQA S 6080, 6030, 6050 3 */ /* MD_MSR_STMIF, MD_MSR_STCYC, MD_MSR_STCAL */
/* *INDENT-ON* */
J1939NM_LOCAL_INLINE FUNC(void, J1939NM_CODE)
J1939Nm_InternalRxIndication(PduIdType RxPduId, P2CONST(PduInfoType, AUTOMATIC, J1939NM_APPL_DATA) info)
{
#if ((J1939NM_USERCALLOUT == STD_ON) || (J1939NM_USESADDRESSARBITRATIONOFCHANNEL == STD_ON) || (J1939NM_NM_PG_SUPPORT == STD_ON) || ((J1939NM_GATEWAY_SUPPORT == STD_ON) && (J1939NM_DYNAMIC_ADDRESS_SUPPORT == STD_ON)) || ((J1939NM_NAME_MANAGEMENT_SUPPORT == STD_ON) && (J1939NM_EXTERNAL_NODES_USED == STD_ON)) || (J1939NM_CA_PG_SUPPORT == STD_ON))
  J1939Nm_ChannelChannelIdxOfRxPduType channelIdx = J1939Nm_GetChannelChannelIdxOfRxPdu(RxPduId);
  /*@ assert channelIdx < J1939Nm_GetSizeOfChannel(); */ /* VCA_J1939NM_CHANNEL_VIA_RXPDU_CSL03 */
#endif
#if ((J1939NM_USESADDRESSARBITRATIONOFCHANNEL == STD_ON) && ((J1939NM_DYNAMIC_ADDRESS_SUPPORT == STD_ON) || (J1939NM_GATEWAY_SUPPORT == STD_ON)))
  J1939Nm_ChannelStateType *channelState = &J1939Nm_GetChannelState(channelIdx);
#endif

#if ((J1939NM_NM_PG_SUPPORT == STD_ON) || (J1939NM_GATEWAY_SUPPORT == STD_ON) || (J1939NM_NAME_MANAGEMENT_SUPPORT == STD_ON) || (J1939NM_CA_PG_SUPPORT == STD_ON))
  /* #10 If pdu is an address claim pdu: */
  if (J1939Nm_GetPduTypeOfRxPdu(RxPduId) == J1939NM_AC_RX_PDU_PDUTYPEOFRXPDU)
#endif
  {
#if (J1939NM_CANIF_DLCCHECK == STD_OFF)
    if ((info->SduLength > J1939NM_AC_FRAME_LENGTH) && (info->SduLength <= J1939NM_AC_PDU_LENGTH))
#endif
    {
#if ((J1939NM_USERCALLOUT == STD_ON) || ((J1939NM_USESADDRESSARBITRATIONOFCHANNEL == STD_ON) && ((J1939NM_DYNAMIC_ADDRESS_SUPPORT == STD_ON) || (J1939NM_GATEWAY_SUPPORT == STD_ON))))
      uint8 sourceAddress = info->SduDataPtr[J1939NM_AC_SA_POS];
#endif

#if (J1939NM_USERCALLOUT == STD_ON)
      /* #20 Forward source address and Ac content to callout function. \trace SPEC-2168282 */
      J1939Nm_GetUserCallout()(J1939Nm_GetComMChannelIdOfChannel(channelIdx), sourceAddress, info->SduDataPtr); /* VCA_J1939NM_UNDEF_FCTCALL */
#endif

#if (J1939NM_USESADDRESSARBITRATIONOFCHANNEL == STD_ON)
      /*
       * #30 If channel uses address arbitration: Check name collision of incoming address claim message.
       *     \trace SPEC-2168280, SPEC-2168281
       */
      if (J1939Nm_IsUsesAddressArbitrationOfChannel(channelIdx))
      {
        boolean nameConflict;
# if ((J1939NM_DYNAMIC_ADDRESS_SUPPORT == STD_ON) && (J1939NM_GATEWAY_SUPPORT == STD_ON))
        boolean nameConflictDynamic;
# endif
# if (J1939NM_DYNAMIC_ADDRESS_SUPPORT == STD_ON)
        if (J1939Nm_IsUsesDynamicAddressingOfChannel(channelIdx))
# endif
        {
# if ((J1939NM_DYNAMIC_ADDRESS_SUPPORT == STD_ON) || (J1939NM_GATEWAY_SUPPORT == STD_ON))
          if (sourceAddress != J1939NM_NULL_ADDRESS)
          {
            J1939Nm_SetBusAddressAllocated(channelState, sourceAddress); /* VCA_J1939NM_CHANNELSTATE_VIA_CHANNEL_CSL03 */
          }
# endif
        }


        nameConflict = J1939Nm_InternalCheckAcCollision(channelIdx, info, J1939NM_INVALID_NODE); /* VCA_J1939NM_POINTERPASSEDTOPUBLICAPI */
# if ((J1939NM_DYNAMIC_ADDRESS_SUPPORT == STD_ON) && (J1939NM_GATEWAY_SUPPORT == STD_ON))
        nameConflictDynamic = J1939Nm_DynamicCheckAcCollision(channelIdx, info, J1939NM_INVALID_NODE); /* VCA_J1939NM_POINTERPASSEDTOPUBLICAPI */
# endif

        /* #40 If a name conflict occurs: Report an error. */
        if (nameConflict
# if ((J1939NM_DYNAMIC_ADDRESS_SUPPORT == STD_ON) && (J1939NM_GATEWAY_SUPPORT == STD_ON))
            || nameConflictDynamic
# endif
          )
        {
# if (J1939NM_RUNTIME_ERROR_REPORT == STD_ON)
          J1939Nm_ReportRuntimeError(J1939NM_SID_RXINDICATION, J1939NM_E_DUPLICATE_NAME);
# endif
        }
# if (((J1939NM_DYNAMIC_ADDRESS_SUPPORT == STD_ON) || (J1939NM_GATEWAY_SUPPORT == STD_ON)) && (J1939NM_EXTERNAL_NODES_USED == STD_ON))
        /* #50 Otherwise: Call function that handles an incoming address claim. */
        else
        {
          J1939Nm_DynamicAddressClaimedNotification(channelIdx, info, channelState); /* VCA_J1939NM_POINTERPASSEDTOPUBLICAPI */
        }
# endif
      }
#endif
    }
#if ((J1939NM_CANIF_DLCCHECK == STD_OFF) && (J1939NM_RUNTIME_ERROR_REPORT == STD_ON))
    else
    {
      J1939Nm_ReportRuntimeError(J1939NM_SID_RXINDICATION, J1939NM_E_INVALID_PDU_SIZE);
    }
#endif
  }
#if ((J1939NM_NM_PG_SUPPORT == STD_ON) || ((J1939NM_GATEWAY_SUPPORT == STD_ON) && (J1939NM_DYNAMIC_ADDRESS_SUPPORT == STD_ON)) || ((J1939NM_NAME_MANAGEMENT_SUPPORT == STD_ON) && (J1939NM_EXTERNAL_NODES_USED == STD_ON)))
  /* #60 If pdu is an name management pdu: Call function that handles an incoming name management request. */
# if ((J1939NM_EXISTS_NM_RX_BC_PDU_PDUTYPEOFRXPDU == STD_ON) || (((J1939NM_CA_PG_SUPPORT == STD_ON) || (J1939NM_GATEWAY_SUPPORT == STD_ON))&& (J1939NM_CANFDCHANNELOFCHANNEL == STD_ON)))
  else if (J1939Nm_GetPduTypeOfRxPdu(RxPduId) == J1939NM_NM_RX_PDU_PDUTYPEOFRXPDU)
# else
  else
# endif
  {
# if (J1939NM_CANIF_DLCCHECK == STD_OFF)
    if ((info->SduLength > J1939NM_NM_FRAME_LENGTH) && (info->SduLength <= J1939NM_NM_PDU_LENGTH))
# endif
    {
      J1939Nm_DynamicHandleNm(channelIdx, info->SduDataPtr); /* VCA_J1939NM_POINTERPASSEDTOPUBLICAPI */
    }
# if ((J1939NM_CANIF_DLCCHECK == STD_OFF) && (J1939NM_RUNTIME_ERROR_REPORT == STD_ON))
    else
    {
      J1939Nm_ReportRuntimeError(J1939NM_SID_RXINDICATION, J1939NM_E_INVALID_PDU_SIZE);
    }
# endif
  }
  /* FBFF J1939-22 */
# if (J1939NM_EXISTS_NM_RX_BC_PDU_PDUTYPEOFRXPDU == STD_ON)
#  if ((J1939NM_CA_PG_SUPPORT == STD_ON) || (J1939NM_GATEWAY_SUPPORT == STD_ON))
  else if (J1939Nm_GetPduTypeOfRxPdu(RxPduId) == J1939NM_NM_RX_BC_PDU_PDUTYPEOFRXPDU)
#  else
  else
#  endif
  {
    if ((info->SduLength > J1939NM_NM_FRAME_LENGTH) && (info->SduLength <= J1939NM_NM_BC_PDU_LENGTH))
    {
      J1939Nm_DynamicHandleNmFBFF(channelIdx, info->SduDataPtr); /* VCA_J1939NM_POINTERPASSEDTOPUBLICAPI */
    }
#  if (J1939NM_RUNTIME_ERROR_REPORT == STD_ON) 
    else
    {
      J1939Nm_ReportRuntimeError(J1939NM_SID_RXINDICATION, J1939NM_E_INVALID_PDU_SIZE);
    }
#  endif 
  }
# endif
#endif
# if (((J1939NM_CA_PG_SUPPORT == STD_ON) || (J1939NM_GATEWAY_SUPPORT == STD_ON)) && (J1939NM_CANFDCHANNELOFCHANNEL == STD_ON))
  else /* FD: CA Pdu */
  {
#  if (J1939NM_CA_PG_SUPPORT == STD_ON)
    if ((info->SduLength > J1939NM_CA_FRAME_LENGTH) && (info->SduLength <= J1939NM_CA_PDU_LENGTH))
    {
      J1939Nm_Fd_InternalProcessCa(channelIdx, info->SduDataPtr); /* VCA_J1939NM_POINTERPASSEDTOPUBLICAPI */
    }
#   if (J1939NM_RUNTIME_ERROR_REPORT == STD_ON)    
    else
    {
      J1939Nm_ReportRuntimeError(J1939NM_SID_RXINDICATION, J1939NM_E_INVALID_PDU_SIZE);
    }
#   endif   
#  else
	/* PRQA S 2016 */ /* MD_MSR_EmptyClause */
#  endif
  }
#endif
} /* J1939Nm_InternalRxIndication() */


/**********************************************************************************************************************
 *  J1939Nm_InternalConfirmAc()
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
/* *INDENT-OFF* */
/* PRQA S 6080 4 */ /* MD_MSR_STMIF */
/* *INDENT-ON* */
J1939NM_LOCAL_INLINE FUNC(void, J1939NM_CODE) J1939Nm_InternalConfirmAc(J1939Nm_ChannelChannelIdxOfTxPduType channelIdx,
                                                                        J1939Nm_ChannelStateType * channelState,
                                                                        const J1939Nm_TxPduStateType * pduState)
{
  uint16 nodeIdx = pduState->NodeId;

#if ((J1939NM_GATEWAY_SUPPORT == STD_ON) && (J1939NM_EXTERNAL_NODES_USED == STD_ON))
  /* #10 If it is a AC Pdu and was send from an external node, call the dynamic TxConfirmation function. */
  if (pduState->IsExtNodeId)
  {
    /*@ assert nodeIdx < J1939Nm_GetSizeOfExternalNode(); */ /* VCA_J1939NM_NODE_VIA_PDUSTATE_TXPDU */
    J1939Nm_DynamicTxConfirmation(nodeIdx, channelIdx);
  }
  /* #20 If it is an AC Pdu and was send from an internal node, iterate overall channels and update states. */
  else
#endif
  {
    J1939Nm_NodeChannelNodeIndEndIdxOfNodeType nodeChannelIndIdx;
    Nm_StateType nmState = channelState->NmState;

    /* #30 Typically, there are more nodes per channel than channels per node, so loop over channels. */
    /*@ assert nodeIdx < J1939Nm_GetSizeOfNode(); */ /* VCA_J1939NM_NODE_VIA_PDUSTATE_TXPDU */
    for (nodeChannelIndIdx = J1939Nm_GetNodeChannelNodeIndStartIdxOfNode(nodeIdx);
         nodeChannelIndIdx < J1939Nm_GetNodeChannelNodeIndEndIdxOfNode(nodeIdx); nodeChannelIndIdx++)
    {
      J1939Nm_NodeChannelNodeIndType nodeChannelIdx = J1939Nm_GetNodeChannelNodeInd(nodeChannelIndIdx);

      /* #40 If provided channel is found: */
      if (J1939Nm_GetChannelIdxOfNodeChannel(nodeChannelIdx) == channelIdx)
      {
        J1939Nm_NodeChannelStateType *nodeChannelState =
          &J1939Nm_GetNodeChannelState(J1939Nm_GetNodeChannelStateIdxOfNodeChannel(nodeChannelIdx));

        nodeChannelState->AcPending = FALSE; /* VCA_J1939NM_NODECHANNELSTATE_VIA_NODE_CSL03 */

        /* #50 If node is in state preclaiming: */
        if (nodeChannelState->NodeState == J1939NM_NODESTATE_PRE_CLAIMING)
        {
          /* #60 Enter state claiming and start delay timer. \trace SPEC-2168269 */
          nodeChannelState->NodeState = J1939NM_NODESTATE_CLAIMING; /* VCA_J1939NM_NODECHANNELSTATE_VIA_NODE_CSL03 */
          nodeChannelState->Timer = J1939Nm_GetNodeStartupDelay(); /* VCA_J1939NM_NODECHANNELSTATE_VIA_NODE_CSL03 */
        }

        /* #70 If node is state prenormal: */
        if (nodeChannelState->NodeState == J1939NM_NODESTATE_PRE_NORMAL)
        {
          /* #80 Enter state normal operation. \trace SPEC-2168266 */
          nodeChannelState->NodeState = J1939NM_NODESTATE_NORMAL; /* VCA_J1939NM_NODECHANNELSTATE_VIA_NODE_CSL03 */
          nodeChannelState->StatePending = TRUE; /* VCA_J1939NM_NODECHANNELSTATE_VIA_NODE_CSL03 */
          nmState = NM_STATE_NORMAL_OPERATION;
        }

#if (J1939NM_DYNAMIC_ADDRESS_SUPPORT == STD_ON)
        /* #90 If dynamic addressing is used, update address table. */
        if (J1939Nm_IsUsesDynamicAddressingOfChannel(channelIdx))
        {
          J1939Nm_PreviousNodeAddressIdxOfNodeChannelType previousAddressIdx =
            J1939Nm_GetPreviousNodeAddressIdxOfNodeChannel(nodeChannelIdx);
          uint8 currentAddress =
            J1939Nm_GetCurrentNodeAddress(J1939Nm_GetCurrentNodeAddressIdxOfNodeChannel(nodeChannelIdx));
          uint8 previousAddress = J1939Nm_GetPreviousNodeAddress(previousAddressIdx);

          if (currentAddress != previousAddress)
          {
            J1939Nm_SetPreviousNodeAddress(previousAddressIdx, currentAddress); /* VCA_J1939NM_PREVIOUSNODEADDRESS_VIA_NODE_CSL03 */

            if (currentAddress != J1939NM_NULL_ADDRESS)
            {
              CanIf_SetAddressTableEntry(J1939Nm_GetCanIfCtrlIdOfChannel(channelIdx),
                                         J1939Nm_GetNodeAddressOfNode(nodeIdx), currentAddress);
            }
          }
        }
#endif
        break;
      }
    }

    /* #100 Update states. */
    if (nmState != channelState->NmState)
    {
      channelState->NmState = nmState; /* VCA_J1939NM_CHANNELSTATE_VIA_CHANNEL_CSL03 */
#if (J1939NM_NM_STATECHANGENOTIF == STD_ON)
      channelState->StatePending = TRUE; /* VCA_J1939NM_CHANNELSTATE_VIA_CHANNEL_CSL03 */
#endif
    }
  }

} /* J1939Nm_InternalConfirmAc() */


/**********************************************************************************************************************
 *  J1939Nm_InternalAcRequestIndication()
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
/* *INDENT-OFF* */
/* PRQA S 6080 4 */ /* MD_MSR_STMIF */
/* *INDENT-ON* */
J1939NM_LOCAL_INLINE FUNC(void, J1939NM_CODE) J1939Nm_InternalAcRequestIndication(uint8 node, NetworkHandleType channel,
                                                                                  uint8 sourceAddress,
                                                                                  uint8 destAddress)
{
  J1939NM_DUMMY_STATEMENT(sourceAddress); /* PRQA S 1338, 2983 */ /* MD_MSR_DummyStmt */

  /* #10 If destination address is node or broadcast address: */
  if ((destAddress == J1939Nm_GetNodeAddressOfNode(node)) || (destAddress == J1939NM_BROADCAST_ADDRESS))
  {
    /* T O D O: Use for channel refresh, reset request timer (see ALM+ issue 84935) */
    J1939Nm_ChannelIdxOfComMChannelType channelIdx = J1939Nm_GetChannelIdxOfComMChannel(channel);
    J1939Nm_NodeChannelNodeIndEndIdxOfNodeType nodeChannelIndIdx;

    /* #20 Go through all node channels. */
    for (nodeChannelIndIdx = J1939Nm_GetNodeChannelNodeIndStartIdxOfNode(node);
         nodeChannelIndIdx < J1939Nm_GetNodeChannelNodeIndEndIdxOfNode(node); nodeChannelIndIdx++)
    {
      J1939Nm_NodeChannelNodeIndType nodeChannelIdx = J1939Nm_GetNodeChannelNodeInd(nodeChannelIndIdx);

      /* #30 If receiving channel is found: */
      if (channelIdx == J1939Nm_GetChannelIdxOfNodeChannel(nodeChannelIdx))
      {
        J1939Nm_NodeChannelStateType *nodeChannelState =
          &J1939Nm_GetNodeChannelState(J1939Nm_GetNodeChannelStateIdxOfNodeChannel(nodeChannelIdx));

        if (((destAddress == J1939NM_BROADCAST_ADDRESS) &&
             (nodeChannelState->NodeState != J1939NM_NODESTATE_WAIT_NETWORK)) ||
            ((destAddress == J1939Nm_GetNodeAddressOfNode(node)) &&
             ((nodeChannelState->NodeState == J1939NM_NODESTATE_NORMAL) ||
              (nodeChannelState->NodeState == J1939NM_NODESTATE_CLAIMING))))
        {
          uint8 nodeAddress = J1939NM_NULL_ADDRESS;

          /* #50 If node state is (pre)normal or (pre)claiming, get node address. */
          if ((nodeChannelState->NodeState == J1939NM_NODESTATE_NORMAL) ||
              (nodeChannelState->NodeState == J1939NM_NODESTATE_CLAIMING) ||
              (nodeChannelState->NodeState == J1939NM_NODESTATE_PRE_CLAIMING) ||
              (nodeChannelState->NodeState == J1939NM_NODESTATE_PRE_NORMAL))
          {
#if (J1939NM_DYNAMIC_ADDRESS_SUPPORT == STD_ON)
            if (J1939Nm_IsUsesDynamicAddressingOfChannel(channelIdx))
            {
              nodeAddress =
                J1939Nm_GetCurrentNodeAddress(J1939Nm_GetCurrentNodeAddressIdxOfNodeChannel(nodeChannelIdx));
            }
            else
#endif
            {
              nodeAddress = J1939Nm_GetNodeAddressOfNode(node);
            }
          }

          if (nodeAddress == J1939NM_NULL_ADDRESS)
          {
            /* #60 If node address equals null address, activate Ac delay. \trace SPEC-2168284 */
            nodeChannelState->AcDelayed = TRUE; /* VCA_J1939NM_NODECHANNELSTATE_VIA_NODE_CSL03 */
          }
          else
          {
            /* #70 Otherwise, activate Ac pending. \trace SPEC-2168275, SPEC-2168276, SPEC-2168277, SPEC-2168283 */
            nodeChannelState->AcPending = TRUE; /* VCA_J1939NM_NODECHANNELSTATE_VIA_NODE_CSL03 */
          }
        }

        break;
      }
    }
  }
} /* J1939Nm_InternalAcRequestIndication() */


/**********************************************************************************************************************
 *  J1939Nm_InternalNetworkRequest()
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
J1939NM_LOCAL_INLINE FUNC(void, J1939NM_CODE)
J1939Nm_InternalNetworkRequest(CONST(NetworkHandleType, AUTOMATIC) channel)
{
  J1939Nm_ChannelIdxOfComMChannelType channelIdx = J1939Nm_GetChannelIdxOfComMChannel(channel);
  /*@ assert channelIdx < J1939Nm_GetSizeOfChannel(); */ /* VCA_J1939NM_CHANNEL_VIA_COMMCHANNEL_CSL03 */
  J1939Nm_ChannelStateType *channelState = &J1939Nm_GetChannelState(channelIdx);

  /* #10 If channel is in sleeping mode: */
  if (channelState->NmMode == NM_MODE_BUS_SLEEP)
  {
#if ((J1939NM_DYNAMIC_ADDRESS_SUPPORT == STD_ON) || (J1939NM_USESADDRESSARBITRATIONOFCHANNEL == STD_ON))
    if (
# if (J1939NM_DYNAMIC_ADDRESS_SUPPORT == STD_ON)
         J1939Nm_IsUsesDynamicAddressingOfChannel(channelIdx)
# else
         J1939Nm_IsUsesAddressArbitrationOfChannel(channelIdx)
# endif
      )
#endif
      /* #20 Send address claim. */
    {
#if ((J1939NM_DYNAMIC_ADDRESS_SUPPORT == STD_ON) || ((J1939NM_GATEWAY_SUPPORT == STD_ON) && (J1939NM_EXTERNAL_NODES_USED == STD_ON) && (J1939NM_CHANNELNODEADDRESSMAPPING == STD_ON)))

      uint8_least i;

      for (i = 0; i < (uint8) J1939NM_BUSADDRESSSTATE_SIZE; i++)
      {
        channelState->BusAddressState[i] = J1939NM_BUSADDRESS_UNUSED; /* VCA_J1939NM_CHANNELSTATE_VIA_CHANNEL_CSL03 */
      }

      /* T O D O: Use J1939Nm_GetNodeStartupDelay in case of isobus channel (see ALM+ issue 79740) */
      channelState->Timer = J1939Nm_GetRequestResponseDelay(); /* VCA_J1939NM_CHANNELSTATE_VIA_CHANNEL_CSL03 */
      channelState->NetworkState = J1939NM_NETWORKSTATE_SCANNING; /* VCA_J1939NM_CHANNELSTATE_VIA_CHANNEL_CSL03 */
      (void) J1939Rm_SendRequest(J1939RM_NULLADDRESS_USER_ID, channel, J1939NM_PGN_AC, NULL_PTR, /* VCA_J1939NM_UNDEF_FCTCALL_PTR2NULL */
                                 J1939NM_BROADCAST_ADDRESS, J1939NM_DEFAULT_PRIORITY, FALSE);
#endif
    }


    /* #30 Set states. */
    {
      Nm_StateType nmState = J1939Nm_InternalSetStateAtNetworkRequest(channelIdx, channelState);

      if (nmState != channelState->NmState)
      {
        channelState->NmState = nmState; /* VCA_J1939NM_CHANNELSTATE_VIA_CHANNEL_CSL03 */
#if (J1939NM_NM_STATECHANGENOTIF == STD_ON)
        channelState->StatePending = TRUE; /* VCA_J1939NM_CHANNELSTATE_VIA_CHANNEL_CSL03 */
#endif
      }
    }

    /* #40 Report state change to the Nm. \trace SPEC-2168267 */
    channelState->NmMode = NM_MODE_NETWORK; /* VCA_J1939NM_CHANNELSTATE_VIA_CHANNEL_CSL03 */
    /* #50 Report mode change to Nm. \trace SPEC-2168264, SPEC-2168305 */
    Nm_NetworkMode(channel);
  }

} /* J1939Nm_InternalNetworkRequest() */


/**********************************************************************************************************************
 *  J1939Nm_InternalNetworkRelease()
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
J1939NM_LOCAL_INLINE FUNC(void, J1939NM_CODE)
J1939Nm_InternalNetworkRelease(CONST(NetworkHandleType, AUTOMATIC) channel)
{
  J1939Nm_ChannelIdxOfComMChannelType channelIdx = J1939Nm_GetChannelIdxOfComMChannel(channel);
  /*@ assert channelIdx < J1939Nm_GetSizeOfChannel(); */ /* VCA_J1939NM_CHANNEL_VIA_COMMCHANNEL_CSL03 */
  J1939Nm_ChannelStateType *channelState = &J1939Nm_GetChannelState(channelIdx);

  /* #10 If channel is in network mode: */
  if (channelState->NmMode == NM_MODE_NETWORK)
  {
    /* #20 Set state to sleep mode. */
    channelState->NmMode = NM_MODE_BUS_SLEEP; /* VCA_J1939NM_CHANNELSTATE_VIA_CHANNEL_CSL03 */
    channelState->NmState = NM_STATE_BUS_SLEEP; /* VCA_J1939NM_CHANNELSTATE_VIA_CHANNEL_CSL03 */

#if (J1939NM_NM_STATECHANGENOTIF == STD_ON)
    /* #30 Report state change to Nm. \trace SPEC-2168274, SPEC-2168305 */
    Nm_StateChangeNotification(channel, channelState->PreviousNmState, channelState->NmState);
    channelState->PreviousNmState = channelState->NmState; /* VCA_J1939NM_CHANNELSTATE_VIA_CHANNEL_CSL03 */
#endif

    {
      J1939Nm_NodeChannelChannelIndEndIdxOfChannelType nodeChannelIndIdx;

      /* #40 Iterate over all nodes: */
      for (nodeChannelIndIdx = J1939Nm_GetNodeChannelChannelIndStartIdxOfChannel(channelIdx);
           nodeChannelIndIdx < J1939Nm_GetNodeChannelChannelIndEndIdxOfChannel(channelIdx); nodeChannelIndIdx++)
      {
        J1939Nm_NodeChannelChannelIndType nodeChannelIdx = J1939Nm_GetNodeChannelChannelInd(nodeChannelIndIdx);
        J1939Nm_NodeIdxOfNodeChannelType nodeIdx = J1939Nm_GetNodeIdxOfNodeChannel(nodeChannelIdx);
        J1939Nm_NodeChannelStateType *nodeChannelState =
          &J1939Nm_GetNodeChannelState(J1939Nm_GetNodeChannelStateIdxOfNodeChannel(nodeChannelIdx));

        /* #50 Report state change to BswM. \trace SPEC-2168305 */
        BswM_J1939Nm_StateChangeNotification(channel, (uint8) nodeIdx, NM_STATE_BUS_SLEEP);

#if (J1939NM_DYNAMIC_ADDRESS_SUPPORT == STD_ON)
        /* #60 If channel uses dynamic addressing: Reset node address table. */
        if (J1939Nm_IsUsesDynamicAddressingOfChannel(channelIdx))
        {
          J1939Nm_SetPreviousNodeAddress(J1939Nm_GetPreviousNodeAddressIdxOfNodeChannel(nodeChannelIdx), /* VCA_J1939NM_PREVIOUSNODEADDRESS_VIA_CHANNEL_CSL03 */
                                         J1939NM_NULL_ADDRESS);

          if ((nodeChannelState->NodeState == J1939NM_NODESTATE_NORMAL) ||
              (nodeChannelState->NodeState == J1939NM_NODESTATE_CLAIMING))
          {
            CanIf_ResetAddressTableEntry(J1939Nm_GetCanIfCtrlIdOfChannel(channelIdx),
                                         J1939Nm_GetNodeAddressOfNode(nodeIdx));
          }
        }
#endif

        /* #70 Set nodechannel to sleep mode. \trace SPEC-2168274 */
        nodeChannelState->NodeState = J1939NM_NODESTATE_BUS_SLEEP; /* VCA_J1939NM_NODECHANNELSTATE_VIA_CHANNEL_CSL03 */
      }
    }

    /* #80 Release the dynamic network. */
#if ((J1939NM_DYNAMIC_ADDRESS_SUPPORT == STD_ON) || (J1939NM_GATEWAY_SUPPORT == STD_ON))
# if (J1939NM_DYNAMIC_ADDRESS_SUPPORT == STD_ON)
    if (J1939Nm_IsUsesDynamicAddressingOfChannel(channelIdx))
# endif
    {
# if (J1939NM_EXTERNAL_NODES_USED == STD_ON)
      J1939Nm_DynamicNetworkRelease(channelIdx);
# endif

      channelState->NetworkState = J1939NM_NETWORKSTATE_DOWN; /* VCA_J1939NM_CHANNELSTATE_VIA_CHANNEL_CSL03 */
    }
#endif

    /* #90 Report mode change to Nm. \trace SPEC-2168274, SPEC-2168305 */
    Nm_BusSleepMode(channel);
  }

} /* J1939Nm_InternalNetworkRelease() */


/**********************************************************************************************************************
 *  J1939Nm_InternalGetState()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
J1939NM_LOCAL_INLINE FUNC(void, J1939NM_CODE)
J1939Nm_InternalGetState(CONST(NetworkHandleType, AUTOMATIC) channel,
                         CONSTP2VAR(Nm_StateType, AUTOMATIC, J1939NM_APPL_VAR) stateP,
                         CONSTP2VAR(Nm_ModeType, AUTOMATIC, J1939NM_APPL_VAR) modeP)
{
  /* Get mode and state of channel. */
  J1939Nm_ChannelIdxOfComMChannelType channelIdx = J1939Nm_GetChannelIdxOfComMChannel(channel);
  const J1939Nm_ChannelStateType *channelState = &J1939Nm_GetChannelState(channelIdx);

  *modeP = channelState->NmMode; /* VCA_J1939NM_POINTERPASSEDTOPUBLICAPI */
  *stateP = channelState->NmState; /* VCA_J1939NM_POINTERPASSEDTOPUBLICAPI */
} /* J1939Nm_InternalGetState() */


/**********************************************************************************************************************
 *  J1939Nm_InternalGetBusOffDelay()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
J1939NM_LOCAL_INLINE FUNC(void, J1939NM_CODE)
J1939Nm_InternalGetBusOffDelay(NetworkHandleType channel, P2VAR(uint8, AUTOMATIC, J1939NM_APPL_VAR) delayCyclesPtr)
{
  uint8 maxDelayCycles = 0;

  J1939NM_DUMMY_STATEMENT(channel); /* PRQA S 1338, 2983 */ /* MD_MSR_DummyStmt */

  /* #10 If address arbitration is used for a valid channel: */
#if (J1939NM_USESADDRESSARBITRATIONOFCHANNEL == STD_ON)
  if (J1939Nm_Channel_Valid(channel)) /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */
  {
    J1939Nm_ChannelIdxOfComMChannelType channelIdx = J1939Nm_GetChannelIdxOfComMChannel(channel); /* VCA_J1939NM_CHANNEL_VIA_COMMCHANNEL_CSL03 */

    if (J1939Nm_IsUsesAddressArbitrationOfChannel(channelIdx))
    {
      J1939Nm_NodeChannelChannelIndEndIdxOfChannelType nodeChannelIndIdx;

      /* #20 Set bus-off state to true. */
      J1939Nm_GetChannelState(channelIdx).BusOff = TRUE; /* VCA_J1939NM_CHANNELSTATE_VIA_COMMCHANNEL_CSL03 */

      /* #30 Go through all node channels to get maximum of CanSM main cycles to delay recovery. */
      for (nodeChannelIndIdx = J1939Nm_GetNodeChannelChannelIndStartIdxOfChannel(channelIdx);
           nodeChannelIndIdx < J1939Nm_GetNodeChannelChannelIndEndIdxOfChannel(channelIdx); nodeChannelIndIdx++)
      {
        J1939Nm_NodeChannelChannelIndType nodeChannelIdx = J1939Nm_GetNodeChannelChannelInd(nodeChannelIndIdx);
        uint8 delayCycles;

        /* #40 Calculate random delay time. \trace SPEC-2168262 */
        J1939Nm_NodeIdxOfNodeChannelType nodeIdx = J1939Nm_GetNodeIdxOfNodeChannel(nodeChannelIdx);
        /*@ assert nodeIdx < J1939Nm_GetSizeOfNode(); */ /* VCA_J1939NM_NODE_VIA_COMMCHANNEL_CSL03 */
        delayCycles = J1939Nm_InternalCalcDelay((uint8) nodeIdx, FALSE);
        if (delayCycles > maxDelayCycles)
        {
          maxDelayCycles = delayCycles;
        }
      }
    }
  }
#endif

  *delayCyclesPtr = maxDelayCycles; /* VCA_J1939NM_POINTERPASSEDTOPUBLICAPI */
} /* J1939Nm_InternalGetBusOffDelay() */


/**********************************************************************************************************************
 *  J1939Nm_InternalSetStateAtNetworkRequest()
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
/* *INDENT-OFF* */
/* PRQA S 3673 4 */ /* MD_MSR_Rule8.13 */
/* *INDENT-ON* */
J1939NM_LOCAL_INLINE FUNC(Nm_StateType, J1939NM_CODE)
J1939Nm_InternalSetStateAtNetworkRequest(J1939Nm_ChannelIdxOfComMChannelType channelIdx,
                                         J1939Nm_ChannelStateType * channelState)
{
  Nm_StateType nmState = NM_STATE_OFFLINE;
  J1939Nm_NodeChannelChannelIndEndIdxOfChannelType nodeChannelIndIdx;

  J1939NM_DUMMY_STATEMENT(channelState); /* PRQA S 1338, 2983 */ /* MD_MSR_DummyStmt */

  /* #10 Iterate over all nodes: */
  for (nodeChannelIndIdx = J1939Nm_GetNodeChannelChannelIndStartIdxOfChannel(channelIdx);
       nodeChannelIndIdx < J1939Nm_GetNodeChannelChannelIndEndIdxOfChannel(channelIdx); nodeChannelIndIdx++)
  {
    J1939Nm_NodeChannelChannelIndType nodeChannelIdx = J1939Nm_GetNodeChannelChannelInd(nodeChannelIndIdx);
    /*@ assert nodeChannelIdx < J1939Nm_GetSizeOfNodeChannel(); */ /* VCA_J1939NM_NODECHANNEL_VIA_CHANNEL_CSL03 */
    J1939Nm_NodeChannelStateType *nodeChannelState =
      &J1939Nm_GetNodeChannelState(J1939Nm_GetNodeChannelStateIdxOfNodeChannel(nodeChannelIdx));
#if ((J1939NM_DYNAMIC_ADDRESS_SUPPORT == STD_ON) || ((J1939NM_USESADDRESSARBITRATIONOFCHANNEL == STD_ON) && (J1939NM_NODESTARTUPDELAYOFNODE == STD_ON)))
    J1939Nm_NodeIdxOfNodeChannelType nodeIdx = J1939Nm_GetNodeIdxOfNodeChannel(nodeChannelIdx);
# if (J1939NM_DYNAMIC_ADDRESS_SUPPORT == STD_ON)
    J1939Nm_NodeAddressSearchAlgorithmOfNodeType searchAlgorithm = J1939Nm_GetNodeAddressSearchAlgorithmOfNode(nodeIdx);
# endif
    uint8 nodeAddress = J1939Nm_GetNodeAddressOfNode(nodeIdx);
#endif

    /* #20 If channel uses dynamic addressing: Get/find node address. */
#if (J1939NM_DYNAMIC_ADDRESS_SUPPORT == STD_ON)
    if (J1939Nm_IsUsesDynamicAddressingOfChannel(channelIdx))
    {
      nodeAddress = J1939Nm_DynamicNetworkRequest(nodeIdx, nodeChannelIdx, channelState, nodeAddress);
    }

    /* #30 If channel uses dynamic addressing and search algorithm is iso global or request: */
    if (J1939Nm_IsUsesDynamicAddressingOfChannel(channelIdx) &&
        ((searchAlgorithm == J1939NM_REQUEST_NODEADDRESSSEARCHALGORITHMOFNODE) ||
         (searchAlgorithm == J1939NM_ISO_GLOBAL_NODEADDRESSSEARCHALGORITHMOFNODE)))
    {
      /* #40 Set node state to wait for network and activate pending state. \trace SPEC-2168264 */
      nodeChannelState->NodeState = J1939NM_NODESTATE_WAIT_NETWORK; /* VCA_J1939NM_NODECHANNELSTATE_VIA_CHANNEL_CSL03 */
      nodeChannelState->StatePending = TRUE; /* VCA_J1939NM_NODECHANNELSTATE_VIA_CHANNEL_CSL03 */
    }
    /* #50 Otherwise: */
    else
#endif
    {
#if (J1939NM_DYNAMIC_ADDRESS_SUPPORT == STD_ON)
      /* #60 If channel uses dynamic addressing: allocate bus address. */
      if (J1939Nm_IsUsesDynamicAddressingOfChannel(channelIdx))
      {
        J1939Nm_SetBusAddressAllocated(channelState, nodeAddress); /* VCA_J1939NM_CHANNELSTATE_VIA_CHANNEL_CSL03 */
      }
#endif

#if (J1939NM_USESADDRESSARBITRATIONOFCHANNEL == STD_ON)
      /* #70 If channel uses address arbitration: \trace SPEC-2168264 */
      if (J1939Nm_IsUsesAddressArbitrationOfChannel(channelIdx))
      {
        /* #80 Set in AC pending state. \trace SPEC-2168275, SPEC-2168276, SPEC-2168277 */
        nodeChannelState->AcPending = TRUE; /* VCA_J1939NM_NODECHANNELSTATE_VIA_CHANNEL_CSL03 */

# if (J1939NM_NODESTARTUPDELAYOFNODE == STD_ON)
        /*
         * #90 If startup of node is delayed, set state to preclaiming and to pending.
         * \trace SPEC-2168264, SPEC-2168265
         */
        if (J1939Nm_IsNodeStartUpDelayOfNode(nodeIdx) && (nodeAddress >= J1939NM_MIN_DELAY_ADDRESS)
            && (nodeAddress <= J1939NM_MAX_DELAY_ADDRESS))
        {
          nodeChannelState->NodeState = J1939NM_NODESTATE_PRE_CLAIMING; /* VCA_J1939NM_NODECHANNELSTATE_VIA_CHANNEL_CSL03 */
          nodeChannelState->StatePending = TRUE; /* VCA_J1939NM_NODECHANNELSTATE_VIA_CHANNEL_CSL03 */
        }
        else
# endif
          /* #100 Otherwise: */
        {
          /* #110 Enter state prenormal \trace SPEC-2168264, SPEC-2168266 */
          nodeChannelState->NodeState = J1939NM_NODESTATE_PRE_NORMAL; /* VCA_J1939NM_NODECHANNELSTATE_VIA_CHANNEL_CSL03 */
# if (J1939NM_J1939NM_E_ADDRESS_LOST == STD_ON)
          /* #120 Report error to Dem. \trace SPEC-2168286, SPEC-2168305 */
          Dem_ReportErrorStatus(J1939Nm_GetJ1939NM_E_ADDRESS_LOST(), DEM_EVENT_STATUS_PREPASSED);
# endif
        }
      }
      else
#endif
        /* #130 Otherwise: */
      {
        /* #140 Enter Nm state normaloperation. \trace SPEC-2168268 */
        nmState = NM_STATE_NORMAL_OPERATION;
        /* #150 Enter state normal and trigger Ac transmission. \trace SPEC-2168264 */
        nodeChannelState->NodeState = J1939NM_NODESTATE_NORMAL; /* VCA_J1939NM_NODECHANNELSTATE_VIA_CHANNEL_CSL03 */
        nodeChannelState->StatePending = TRUE; /* VCA_J1939NM_NODECHANNELSTATE_VIA_CHANNEL_CSL03 */
      }
    }
  }

  return nmState;
} /* J1939Nm_InternalSetStateAtNetworkRequest() */


/**********************************************************************************************************************
 *  J1939Nm_InternalMainFunctionHandleNodeStateClaiming()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
J1939NM_LOCAL_INLINE FUNC(void, J1939NM_CODE)
J1939Nm_InternalMainFunctionHandleNodeStateClaiming(J1939Nm_NodeChannelStateType * nodeChannelState,
                                                    Nm_StateType * nmState)
{
  /* #10 Update timer. */
  --nodeChannelState->Timer; /* VCA_J1939NM_NODECHANNELSTATE_VIA_CHANNEL_CSL03 */
  /* #20 If timeout is elapsed: */
  if (nodeChannelState->Timer == 0u)
  {
    /* #30 Enter state normal. \trace SPEC-2168270 */
    nodeChannelState->NodeState = J1939NM_NODESTATE_NORMAL; /* VCA_J1939NM_NODECHANNELSTATE_VIA_CHANNEL_CSL03 */
    nodeChannelState->StatePending = TRUE; /* VCA_J1939NM_NODECHANNELSTATE_VIA_CHANNEL_CSL03 */
    *nmState = NM_STATE_NORMAL_OPERATION;
#if (J1939NM_J1939NM_E_ADDRESS_LOST == STD_ON)
    /* #40 Report error to Dem. \trace SPEC-2168286, SPEC-2168305 */
    Dem_ReportErrorStatus(J1939Nm_GetJ1939NM_E_ADDRESS_LOST(), DEM_EVENT_STATUS_PREPASSED);
#endif
  }
} /* J1939Nm_InternalMainFunctionHandleNodeStateClaiming() */


/**********************************************************************************************************************
 *  J1939Nm_InternalMainFunctionHandleNodeStateAcDelayed()
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
J1939NM_LOCAL_INLINE FUNC(void, J1939NM_CODE)
J1939Nm_InternalMainFunctionHandleNodeStateAcDelayed(J1939Nm_NodeChannelStateType * nodeChannelState,
                                                     J1939Nm_NodeIdxOfNodeChannelType nodeIdx)
{
  /* AddressClaimed messages must not be sent until a pending address claimed message is due */
  nodeChannelState->AcPending = FALSE; /* VCA_J1939NM_NODECHANNELSTATE_VIA_CHANNEL_CSL03 */

  /* #20 If timeout is elapsed, set timer to new calculated delay. \trace SPEC-2168271 */
  if (nodeChannelState->Timer == 0u)
  {
    nodeChannelState->Timer = J1939Nm_InternalCalcDelay(nodeIdx, TRUE); /* VCA_J1939NM_NODECHANNELSTATE_VIA_CHANNEL_CSL03 */
  }
  /* #30 Oterwise: */
  else
  {
    /* #40 Update timer. */
    --nodeChannelState->Timer; /* VCA_J1939NM_NODECHANNELSTATE_VIA_CHANNEL_CSL03 */

    /* #50 If timeout is elapsed: */
    if (nodeChannelState->Timer == 0u)
    {
      /* #60 Cancel AcDelaying. \trace SPEC-2168271 */
      nodeChannelState->AcDelayed = FALSE; /* VCA_J1939NM_NODECHANNELSTATE_VIA_CHANNEL_CSL03 */
      /* #70 Start AcPending. \trace SPEC-2168275, SPEC-2168276, SPEC-2168277 */
      nodeChannelState->AcPending = TRUE; /* VCA_J1939NM_NODECHANNELSTATE_VIA_CHANNEL_CSL03 */
    }
  }
} /* J1939Nm_InternalMainFunctionHandleNodeStateAcDelayed() */


/**********************************************************************************************************************
 *  J1939Nm_InternalMainFunctionHandleNodeStateAcPending()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
J1939NM_LOCAL_INLINE FUNC(void, J1939NM_CODE)
J1939Nm_InternalMainFunctionHandleNodeStateAcPending(const J1939Nm_NodeChannelStateType * nodeChannelState,
                                                     J1939Nm_NodeChannelChannelIndType nodeChannelIdx,
                                                     J1939Nm_SizeOfChannelType channelIdx,
                                                     J1939Nm_NodeIdxOfNodeChannelType nodeIdx)
{
  /* #10 Set node address that shall be claimed to null address. \trace SPEC-2168271 */
  uint8 nodeAddress = J1939NM_NULL_ADDRESS;

  J1939NM_DUMMY_STATEMENT(nodeChannelIdx); /* PRQA S 1338, 2983 */ /* MD_MSR_DummyStmt */

  /* #20 If node state is (pre)normal or (pre)claiming: Set node address that shall be claimed to current address. */
  if ((nodeChannelState->NodeState == J1939NM_NODESTATE_NORMAL) ||
      (nodeChannelState->NodeState == J1939NM_NODESTATE_CLAIMING) ||
      (nodeChannelState->NodeState == J1939NM_NODESTATE_PRE_CLAIMING) ||
      (nodeChannelState->NodeState == J1939NM_NODESTATE_PRE_NORMAL))
  {
#if (J1939NM_DYNAMIC_ADDRESS_SUPPORT == STD_ON)
    if (J1939Nm_IsUsesDynamicAddressingOfChannel(channelIdx))
    {
      nodeAddress = J1939Nm_GetCurrentNodeAddress(J1939Nm_GetCurrentNodeAddressIdxOfNodeChannel(nodeChannelIdx));
    }
    else
#endif
    {
      nodeAddress = J1939Nm_GetNodeAddressOfNode(nodeIdx);
    }
  }

  /* #30 Send address claim message. \trace SPEC-2168271 */
  J1939Nm_InternalSendAc(channelIdx, nodeIdx, nodeAddress);
} /* J1939Nm_InternalMainFunctionHandleNodeStateAcPending() */


#if (J1939NM_USESADDRESSARBITRATIONOFCHANNEL == STD_ON)
/**********************************************************************************************************************
 *  J1939Nm_InternalCheckAcCollisionOfTransmittedAc()
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
 *
 *
 *
 *
 *
 */
/* *INDENT-OFF* */
/* PRQA S 6030, 6050, 6060, 3673 9 */ /* MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STPAR, MD_MSR_Rule8.13 */
/* *INDENT-ON* */
J1939NM_LOCAL_INLINE FUNC(Nm_StateType, J1939NM_CODE)
J1939Nm_InternalCheckAcCollisionOfTransmittedAc(P2CONST(PduInfoType, AUTOMATIC, J1939NM_APPL_DATA) info,
                                                J1939Nm_ChannelChannelIdxOfRxPduType channelIdx,
                                                J1939Nm_NodeIdxOfNodeChannelType nodeIdx,
                                                J1939Nm_ChannelStateType * channelState,
                                                J1939Nm_NodeChannelStateType * nodeChannelState,
                                                J1939Nm_NodeChannelChannelIndType nodeChannelIdx, uint8 nodeAddress,
                                                boolean * nameConflict)
{
  Nm_StateType nmState = NM_STATE_OFFLINE;
  uint8 dynamicNodeAddress = nodeAddress;

# if ((J1939NM_NM_PG_SUPPORT == STD_ON) || (J1939NM_NAME_MANAGEMENT_SUPPORT == STD_ON))
  const uint8 *currentNodeName = J1939Nm_GetCurrentNodeName(J1939Nm_GetCurrentNodeNameIdxOfNode(nodeIdx));
# else
  J1939Nm_NodeNameIdxOfNodeType nodeNameIdx = J1939Nm_GetNodeNameIdxOfNode(nodeIdx);
  uint8 currentNodeName[J1939NM_NAME_LENGTH];
# endif
  sint16_least nameDiffers;

  J1939NM_DUMMY_STATEMENT(channelState); /* PRQA S 1338, 2983 */ /* MD_MSR_DummyStmt */
  J1939NM_DUMMY_STATEMENT(nodeChannelIdx); /* PRQA S 1338, 2983 */ /* MD_MSR_DummyStmt */
  J1939NM_DUMMY_STATEMENT(dynamicNodeAddress); /* PRQA S 1338, 2983 */ /* MD_MSR_DummyStmt */

  /*
   * #10 If J1939NM_NM_PG_SUPPORT or J1939NM_NAME_MANAGEMENT_SUPPORT is enabled:
   *       Enter exclusive area J1939NM_EXCLUSIVE_AREA_NAMELOCK.
   */
# if ((J1939NM_NM_PG_SUPPORT == STD_ON) || (J1939NM_NAME_MANAGEMENT_SUPPORT == STD_ON))
  SchM_Enter_J1939Nm_J1939NM_EXCLUSIVE_AREA_NAMELOCK();
# else
  J1939Nm_InternalGetName(currentNodeName, nodeNameIdx);
# endif

  /* #20 Compare current node name with name which was received or sent with AC. */
  nameDiffers = J1939Nm_InternalNameCompare(currentNodeName, &(info->SduDataPtr[J1939NM_AC_NAME_BYTE1]));

  /*
   * #30 If J1939NM_NM_PG_SUPPORT or J1939NM_NAME_MANAGEMENT_SUPPORT is enabled:
   *       Leave exclusive area J1939NM_EXCLUSIVE_AREA_NAMELOCK.
   */
# if ((J1939NM_NM_PG_SUPPORT == STD_ON) || (J1939NM_NAME_MANAGEMENT_SUPPORT == STD_ON))
  SchM_Exit_J1939Nm_J1939NM_EXCLUSIVE_AREA_NAMELOCK();
# endif

  /* #40 If names are equal: */
  if (nameDiffers == 0)
  {
    /* #50 Inform calling function about name conflict. */
    *nameConflict = TRUE;

    /* #60 Set Ac state to pending. \trace SPEC-2168275, SPEC-2168276, SPEC-2168277 */
    nodeChannelState->AcPending = TRUE; /* VCA_J1939NM_NODECHANNELSTATE_VIA_CHANNEL_CSL03 */

    /* #70 If node state is normal, set Nm state to normal. */
    if (nodeChannelState->NodeState == J1939NM_NODESTATE_NORMAL)
    {
      nmState = NM_STATE_NORMAL_OPERATION;
    }
  }
  /* #80 If current node name is greater: */
  else if (nameDiffers > 0)
  {
# if (J1939NM_NODECHANNELSHAREDFROMNODECHANNELINDUSEDOFNODECHANNEL == STD_ON)
    J1939Nm_NodeChannelSharedFromNodeChannelIndIterType sharedNodeChannelIndIdx;
# endif

# if (J1939NM_DYNAMIC_ADDRESS_SUPPORT == STD_ON)
    /*
     * J1939Nm_ClearBusAddressAllocated must not be called because the previously claimed address has been claimed by another node
     */
    boolean aac;
    SchM_Enter_J1939Nm_J1939NM_EXCLUSIVE_AREA_NAMELOCK();
    aac = J1939Nm_IsAAC(currentNodeName);
    SchM_Exit_J1939Nm_J1939NM_EXCLUSIVE_AREA_NAMELOCK();

    if (J1939Nm_IsUsesDynamicAddressingOfChannel(channelIdx) && aac)
    {
      dynamicNodeAddress = J1939Nm_DynamicFindFreeAddress(dynamicNodeAddress, J1939Nm_GetNodeAddressOfNode(nodeIdx),
                                                          J1939Nm_GetFirstDynamicAddressOfNode(nodeIdx),
                                                          J1939Nm_GetLastDynamicAddressOfNode(nodeIdx), channelState);
    }
    else
    {
      dynamicNodeAddress = J1939NM_NULL_ADDRESS;
    }

    /* #90 If channel uses no dynamic addressing or adress configuration capability is not ACC: */
    if (dynamicNodeAddress == J1939NM_NULL_ADDRESS)
# endif
    {
      /*
       * #100 Set state to AC lost.
       * \trace SPEC-2168271, SPEC-2168281
       */
      nodeChannelState->NodeState = J1939NM_NODESTATE_ACLOST; /* VCA_J1939NM_NODECHANNELSTATE_VIA_CHANNEL_CSL03 */
# if (J1939NM_J1939NM_E_ADDRESS_LOST == STD_ON)
      /* #110 Report error to Dem. \trace SPEC-2168286, SPEC-2168305 */
      Dem_ReportErrorStatus(J1939Nm_GetJ1939NM_E_ADDRESS_LOST(), DEM_EVENT_STATUS_PREFAILED);
# endif
      /* #120 Report state change to BswM. \trace SPEC-2168272, SPEC-2168305 */
      BswM_J1939Nm_StateChangeNotification(J1939Nm_GetComMChannelIdOfChannel(channelIdx), (uint8) nodeIdx,
                                           NM_STATE_OFFLINE);

      /* #130 Insert random delay to avoid BusOff in case several nodes fail to claim an address at the same time */
      nodeChannelState->AcDelayed = TRUE; /* VCA_J1939NM_NODECHANNELSTATE_VIA_CHANNEL_CSL03 */

# if (J1939NM_NODECHANNELSHAREDFROMNODECHANNELINDUSEDOFNODECHANNEL == STD_ON)
      for (sharedNodeChannelIndIdx =
           J1939Nm_GetNodeChannelSharedFromNodeChannelIndStartIdxOfNodeChannel(nodeChannelIdx);
           sharedNodeChannelIndIdx <
           J1939Nm_GetNodeChannelSharedFromNodeChannelIndEndIdxOfNodeChannel(nodeChannelIdx); sharedNodeChannelIndIdx++)
      {
        J1939Nm_NodeChannelSharedFromNodeChannelIndType sharedNodeChannelIdx =
          J1939Nm_GetNodeChannelSharedFromNodeChannelInd(sharedNodeChannelIndIdx);
        J1939Nm_NodeChannelStateIdxOfNodeChannelType sharedNodeChannelStateIdx =
          J1939Nm_GetNodeChannelStateIdxOfNodeChannel(sharedNodeChannelIdx);
        J1939Nm_GetNodeChannelState(sharedNodeChannelStateIdx).AcDelayed = TRUE; /* VCA_J1939NM_NODECHANNELSTATE_VIA_CHANNEL_CSL03 */
      }
# endif
    }
# if (J1939NM_DYNAMIC_ADDRESS_SUPPORT == STD_ON)
    /* #140 Otherwise: */
    else
    {
      /* #150 Allocate bus address. */
      J1939Nm_SetBusAddressAllocated(channelState, dynamicNodeAddress); /* VCA_J1939NM_CHANNELSTATE_VIA_CHANNEL_CSL03 */

      /* #160 Queue Ac for later transmission. \trace SPEC-2168275, SPEC-2168276, SPEC-2168277 */
      nodeChannelState->AcPending = TRUE; /* VCA_J1939NM_NODECHANNELSTATE_VIA_CHANNEL_CSL03 */

#  if (J1939NM_NODECHANNELSHAREDFROMNODECHANNELINDUSEDOFNODECHANNEL == STD_ON)
      for (sharedNodeChannelIndIdx =
           J1939Nm_GetNodeChannelSharedFromNodeChannelIndStartIdxOfNodeChannel(nodeChannelIdx);
           sharedNodeChannelIndIdx <
           J1939Nm_GetNodeChannelSharedFromNodeChannelIndEndIdxOfNodeChannel(nodeChannelIdx); sharedNodeChannelIndIdx++)
      {
        J1939Nm_NodeChannelSharedFromNodeChannelIndType sharedNodeChannelIdx =
          J1939Nm_GetNodeChannelSharedFromNodeChannelInd(sharedNodeChannelIndIdx);
        J1939Nm_NodeChannelStateIdxOfNodeChannelType sharedNodeChannelStateIdx =
          J1939Nm_GetNodeChannelStateIdxOfNodeChannel(sharedNodeChannelIdx);
        J1939Nm_GetNodeChannelState(sharedNodeChannelStateIdx).AcPending = TRUE; /* VCA_J1939NM_NODECHANNELSTATE_VIA_CHANNEL_CSL03 */
      }
#  endif

      /* #170 If node state is normal, set Nm state to normal. */
      if (nodeChannelState->NodeState == J1939NM_NODESTATE_NORMAL)
      {
        nmState = NM_STATE_NORMAL_OPERATION;
      }
    }

    /* #180 If channel uses dynamic addressing: */
    if (J1939Nm_IsUsesDynamicAddressingOfChannel(channelIdx))
    {
      /* #190 save NULL or new address. */
      J1939Nm_CurrentNodeAddressIdxOfNodeChannelType currentNodeAddressIdx =
        J1939Nm_GetCurrentNodeAddressIdxOfNodeChannel(nodeChannelIdx);
      J1939Nm_SetCurrentNodeAddress(currentNodeAddressIdx, dynamicNodeAddress); /* VCA_J1939NM_CURRENTNODEADDRESS_VIA_NODECHANNEL_CSL03 */

      /* #200 Set NvM status and reset CanIf table entry. */
#  if (J1939NM_ADDRESSSTORAGEBLOCK == STD_ON)
      (void) NvM_SetRamBlockStatus((NvM_BlockIdType) NvMConf_NvMBlockDescriptor_J1939Nm_CurrentNodeAddresses, TRUE);
#  endif

      CanIf_ResetAddressTableEntry(J1939Nm_GetCanIfCtrlIdOfChannel(channelIdx), J1939Nm_GetNodeAddressOfNode(nodeIdx));
    }
# endif
  }
  /* #210 If current node name is lower: */
  else
  {
    /* #220 Activate Ac pending. \trace SPEC-2168275, SPEC-2168276, SPEC-2168277, SPEC-2168280 */
    nodeChannelState->AcPending = TRUE; /* VCA_J1939NM_NODECHANNELSTATE_VIA_CHANNEL_CSL03 */

    /* #230 the node of the received AC lost against a local node, and shall therefore not reserve its address */
    info->SduDataPtr[J1939NM_AC_SA_POS] = J1939NM_NULL_ADDRESS; /* VCA_J1939NM_POINTERPASSEDTOPUBLICAPI */

    /* #240 If node state is normal, set Nm state to normal. */
    if (nodeChannelState->NodeState == J1939NM_NODESTATE_NORMAL)
    {
      nmState = NM_STATE_NORMAL_OPERATION;
    }
  }


  return nmState;

} /* J1939Nm_InternalCheckAcCollisionOfTransmittedAc() */
#endif


#define J1939NM_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*============================================== J1939NM_STOP_SEC_CODE ==============================================*/


/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/*============================================== J1939NM_START_SEC_CODE =============================================*/
#define J1939NM_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


/**********************************************************************************************************************
 *  J1939Nm_InitMemory()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, J1939NM_CODE) J1939Nm_InitMemory(void)
{
  /* #10 Set the J1939Nm to not initialized. */
  J1939Nm_ModuleInitialized = J1939NM_UNINIT;

#if (J1939NM_ADDRESSSTORAGEBLOCK == STD_ON)
  asbReset = FALSE;
#endif

#if (J1939NM_NAMESTORAGEBLOCK == STD_ON)
  nsbReset = FALSE;
#endif
} /* J1939Nm_InitMemory() */


/**********************************************************************************************************************
 *  J1939Nm_Init()
 *********************************************************************************************************************/
/* \trace SPEC-2168256
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
FUNC(void, J1939NM_CODE) J1939Nm_Init(P2CONST(J1939Nm_ConfigType, AUTOMATIC, J1939NM_PBCFG) config)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = J1939NM_E_NO_ERROR; /* PRQA S 2981 */ /* MD_MSR_RetVal */

  J1939NM_DUMMY_STATEMENT(config); /* PRQA S 1338, 2983 */ /* MD_MSR_DummyStmt */

#if (J1939NM_USE_INIT_POINTER == STD_ON)
  J1939Nm_ConfigDataPtr = config;
#endif

  /* ----- Development Error Checks ------------------------------------- */

  /* #10 Check that the J1939Nm is not initialized yet. \trace SPEC-2168259 */
  if (J1939Nm_ModuleInitialized == J1939NM_INIT)
  {
    errorId = J1939NM_E_REINIT; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  }
#if (J1939NM_USE_INIT_POINTER == STD_ON)
  /* #20 If "J1939NM_USE_INIT_POINTER" is enabled, Check that the configuration data pointer is set. */
  else if (J1939Nm_ConfigDataPtr == NULL_PTR)
  {
# if (J1939NM_USE_ECUM_BSW_ERROR_HOOK == STD_ON) /* COV_J1939NM_INIT_POINTER */
    EcuM_BswErrorHook(J1939NM_MODULE_ID, ECUM_BSWERROR_NULLPTR);
# endif
# if (J1939NM_DEV_ERROR_DETECT == STD_ON)
    errorId = J1939NM_E_PARAM_POINTER;
# endif
  }
# if (J1939NM_FINALMAGICNUMBER == STD_ON) /* COV_J1939NM_INIT_POINTER */
  /* #30 Check the final magic number is correct. */
  else if (J1939Nm_GetFinalMagicNumber() != J1939NM_FINAL_MAGIC_NUMBER)
  {
#  if (J1939NM_USE_ECUM_BSW_ERROR_HOOK == STD_ON) /* COV_J1939NM_INIT_POINTER */
    EcuM_BswErrorHook(J1939NM_MODULE_ID, ECUM_BSWERROR_MAGICNUMBER);
#  endif
#  if (J1939NM_DEV_ERROR_DETECT == STD_ON)
    errorId = J1939NM_E_INIT_FAILED;
#  endif
  }
# endif
#endif
  /* #40 If the initial checks are passed or not required: */
  else
  {
    /* #50 If "J1939NM_USE_INIT_POINTER" is disabled, check that the configuration data pointer is not set. */
#if ((J1939NM_USE_INIT_POINTER == STD_OFF) && (J1939NM_DEV_ERROR_DETECT == STD_ON))
    if (config != NULL_PTR)
    {
      errorId = J1939NM_E_PARAM_POINTER; /* PRQA S 2981 */ /* MD_MSR_RetVal */
    }
#endif

    /* ----- Implementation ----------------------------------------------- */
    /* #60 Proceed with initialization. */
    J1939Nm_InternalInit();
  }

  /* ----- Development Error Report --------------------------------------- */
#if (J1939NM_DEV_ERROR_REPORT == STD_ON)
  if (errorId != J1939NM_E_NO_ERROR)
  {
    /* \trace SPEC-2168285 */
    J1939Nm_ReportDetError(J1939NM_SID_INIT, errorId);
  }
#else
  J1939NM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983 */ /* MD_MSR_DummyStmt */
#endif
} /* J1939Nm_Init() */


/**********************************************************************************************************************
 *  J1939Nm_DeInit()
 *********************************************************************************************************************/
/* \trace SPEC-2168257
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, J1939NM_CODE) J1939Nm_DeInit(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = J1939NM_E_NO_ERROR; /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check that the J1939Nm is initialized. */
  if (J1939Nm_ModuleInitialized == J1939NM_UNINIT)
  {
    errorId = J1939NM_E_UNINIT; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  }

  /* #20 Set state of J1939Nm to not initialized. */
  J1939Nm_ModuleInitialized = J1939NM_UNINIT;

  /* ----- Development Error Report ------------------------------------- */
#if (J1939NM_DEV_ERROR_REPORT == STD_ON)
  if (errorId != J1939NM_E_NO_ERROR)
  {
    /* \trace SPEC-2168258, SPEC-2168285 */
    J1939Nm_ReportDetError(J1939NM_SID_DEINIT, errorId);
  }
#else
  J1939NM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983 */ /* MD_MSR_DummyStmt */
#endif
} /* J1939Nm_DeInit() */


/**********************************************************************************************************************
 *  J1939Nm_GetVersionInfo()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
#if (J1939NM_VERSION_INFO_API == STD_ON)
FUNC(void, J1939NM_CODE) J1939Nm_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, J1939NM_APPL_VAR) versionInfo)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = J1939NM_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check if version information pointer is set. */
# if (J1939NM_DEV_ERROR_DETECT == STD_ON)
  if (versionInfo == NULL_PTR)
  {
    errorId = J1939NM_E_PARAM_POINTER;
  }
  /* #20 If the initial checks are passed or not required: */
  else
# endif
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #30 Copy required information. */
    versionInfo->vendorID = J1939NM_VENDOR_ID; /* VCA_J1939NM_VERSIONINFO */
    versionInfo->moduleID = J1939NM_MODULE_ID; /* VCA_J1939NM_VERSIONINFO */
    versionInfo->sw_major_version = J1939NM_SW_MAJOR_VERSION; /* VCA_J1939NM_VERSIONINFO */
    versionInfo->sw_minor_version = J1939NM_SW_MINOR_VERSION; /* VCA_J1939NM_VERSIONINFO */
    versionInfo->sw_patch_version = J1939NM_SW_PATCH_VERSION; /* VCA_J1939NM_VERSIONINFO */
  }

  /* ----- Development Error Report ------------------------------------- */
# if (J1939NM_DEV_ERROR_REPORT == STD_ON)
  if (errorId != J1939NM_E_NO_ERROR)
  {
    /* \trace SPEC-2168285 */
    J1939Nm_ReportDetError(J1939NM_SID_GETVERSIONINFO, errorId);
  }
# else
  J1939NM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983 */ /* MD_MSR_DummyStmt */
# endif
} /* J1939Nm_GetVersionInfo() */
#endif


/**********************************************************************************************************************
 *  J1939Nm_MainFunction()
 *********************************************************************************************************************/
/*! \brief      Main function of the J1939Nm. Used for scheduling purposes and timeout supervision.
 *  \details     -
 *  \pre         -
 *  \context    TASK
 *  \note       The main function must be called cyclically with a timing corresponding to the configured Main Function
 *              Period.
 *  \trace SPEC-2168260
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
FUNC(void, J1939NM_CODE) J1939Nm_MainFunction(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = J1939NM_E_NO_ERROR; /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check that the J1939Nm is initialized. \trace SPEC-2168258 */
  if (J1939Nm_ModuleInitialized == J1939NM_UNINIT)
  {
    errorId = J1939NM_E_UNINIT; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  }
  /* #20 If the initial checks are passed: */
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #30 Process confirmation timeout. */
    J1939Nm_InternalConfTimeoutHandling();

#if ((J1939NM_DYNAMIC_ADDRESS_SUPPORT == STD_ON) || (J1939NM_GATEWAY_SUPPORT == STD_ON) || (J1939NM_NM_PG_SUPPORT == STD_ON) || (J1939NM_NAME_MANAGEMENT_SUPPORT == STD_ON))
    /* #40 Proceed with dynamic main function */
    J1939Nm_DynamicMainFunction();
#endif

    /* #50 Proceed with internal main function. */
    J1939Nm_InternalMainFunction();
  }

  /* ----- Development Error Report ------------------------------------- */
#if (J1939NM_DEV_ERROR_REPORT == STD_ON)
  if (errorId != J1939NM_E_NO_ERROR)
  {
    /* \trace SPEC-2168285 */
    J1939Nm_ReportDetError(J1939NM_SID_MAINFUNCTION, errorId);
  }
#else
  J1939NM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983 */ /* MD_MSR_DummyStmt */
#endif
} /* J1939Nm_MainFunction() */


/**********************************************************************************************************************
 *  J1939Nm_RxIndication()
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
/* *INDENT-OFF* */
/* PRQA S 6080 3 */ /* MD_MSR_STMIF */
/* *INDENT-ON* */
FUNC(void, J1939NM_CODE)
J1939Nm_RxIndication(PduIdType RxPduId, P2CONST(PduInfoType, AUTOMATIC, J1939NM_APPL_DATA) info)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = J1939NM_E_NO_ERROR; /* PRQA S 2981 */ /* MD_MSR_RetVal */

  J1939NM_DUMMY_STATEMENT(RxPduId); /* PRQA S 1338, 2983 */ /* MD_MSR_DummyStmt */
  J1939NM_DUMMY_STATEMENT(info); /* PRQA S 1338, 2983 */ /* MD_MSR_DummyStmt */

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check that the J1939Nm is initialized. \trace SPEC-2168258 */
  if (J1939Nm_ModuleInitialized == J1939NM_UNINIT)
  {
    errorId = J1939NM_E_UNINIT; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  }
#if (J1939NM_DEV_ERROR_DETECT == STD_ON)
  /* #20 Check if the ID of the received PDU is valid. \trace SPEC-2168287 */
  else if ((RxPduId >= J1939Nm_GetSizeOfRxPdu())
# if (J1939NM_INVALIDHNDOFRXPDU == STD_ON)
           || (J1939Nm_IsInvalidHndOfRxPdu(RxPduId))
# endif
    )
  {
    errorId = J1939NM_E_INVALID_PDU_SDU_ID; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  }
# if (J1939NM_EXISTS_TP_PDU_IFTYPEOFRXPDU == STD_ON)
  /* #30 Check if the If type of the received PDU is valid. */
  else if (J1939Nm_GetIfTypeOfRxPdu(RxPduId) == J1939NM_TP_PDU_IFTYPEOFRXPDU)
  {
    errorId = J1939NM_E_INVALID_PDU_SDU_ID; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  }
# endif
  /* #40 Check if the Pdu info pointer is set. */
  else if (info == NULL_PTR)
  {
    errorId = J1939NM_E_PARAM_POINTER; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  }
  /* #50 Check if the Sdu data pointer is set. */
  else if (info->SduDataPtr == NULL_PTR)
  {
    errorId = J1939NM_E_PARAM_POINTER; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  }
# if ((J1939NM_USERCALLOUT == STD_ON) || ((J1939NM_USESADDRESSARBITRATIONOFCHANNEL == STD_ON) && ((J1939NM_DYNAMIC_ADDRESS_SUPPORT == STD_ON) || (J1939NM_GATEWAY_SUPPORT == STD_ON))))
  /* #60 Check that the source address is valid. */
  else if (!J1939Nm_SA_Valid(info->SduDataPtr[J1939NM_AC_SA_POS]))
  {
    errorId = J1939NM_E_INVALID_ADDRESS; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  }
# endif
#endif
  /* #70 If the initial checks are passed or not required: */
  else
  {
    /* ----- Implementation ----------------------------------------------- */

    /* #80 Proceed with the internal RxIndication function. */
    /*@ assert info && $external(info->SduDataPtr); */ /* VCA_J1939NM_POINTERPASSEDTOPUBLICAPI */
    J1939Nm_InternalRxIndication(RxPduId, info); /* VCA_J1939NM_POINTERPASSEDTOPUBLICAPI */
  }

  /* ----- Development Error Report ------------------------------------- */
#if (J1939NM_DEV_ERROR_REPORT == STD_ON)
  if (errorId != J1939NM_E_NO_ERROR)
  {
    /* \trace SPEC-2168285 */
    J1939Nm_ReportDetError(J1939NM_SID_RXINDICATION, errorId);
  }
#else
  J1939NM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983 */ /* MD_MSR_DummyStmt */
#endif
} /* J1939Nm_RxIndication() */

/**********************************************************************************************************************
 *  J1939Nm_TxConfirmation()
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
FUNC(void, J1939NM_CODE) J1939Nm_TxConfirmation(PduIdType TxPduId)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = J1939NM_E_NO_ERROR; /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check that the J1939Nm is initialized. \trace SPEC-2168258 */
  if (J1939Nm_ModuleInitialized == J1939NM_UNINIT)
  {
    errorId = J1939NM_E_UNINIT; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  }
#if (J1939NM_DEV_ERROR_DETECT == STD_ON)
  /* #20 Check if the ID of the transmitted PDU is valid. \trace SPEC-2168285, SPEC-2168287 */
  else if ((TxPduId >= J1939Nm_GetSizeOfTxPdu())
# if (J1939NM_INVALIDHNDOFTXPDU == STD_ON)
           || (J1939Nm_IsInvalidHndOfTxPdu(TxPduId))
# endif
    )
  {
    errorId = J1939NM_E_INVALID_PDU_SDU_ID; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  }
# if (J1939NM_EXISTS_TP_PDU_IFTYPEOFTXPDU == STD_ON)
  /* #30 Check if the If type of the received PDU is valid. */
  else if (J1939Nm_GetIfTypeOfTxPdu(TxPduId) == J1939NM_TP_PDU_IFTYPEOFTXPDU)
  {
      errorId = J1939NM_E_INVALID_PDU_SDU_ID; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  }
# endif
#endif
  /* #40 If the initial checks are passed or not required: */
  else
  {
    /* ----- Implementation ----------------------------------------------- */

    J1939Nm_ChannelChannelIdxOfTxPduType channelIdx = J1939Nm_GetChannelChannelIdxOfTxPdu(TxPduId);
    /*@ assert channelIdx < J1939Nm_GetSizeOfChannel(); */ /* VCA_J1939NM_CHANNEL_VIA_TXPDU_CSL03 */
    J1939Nm_ChannelStateType *channelState = &J1939Nm_GetChannelState(channelIdx);
    J1939Nm_TxPduStateType *pduState = &J1939Nm_GetTxPduState(J1939Nm_GetTxPduStateIdxOfTxPdu(TxPduId));

    /* #50 Release the state of the confirmed Tx Pdu. */
    pduState->Locked = FALSE; /* VCA_J1939NM_TXPDUSTATE_VIA_CHANNEL_CSL03 */

    /* #60 If it is an AC pdu, confirm it. */
#if ((J1939NM_NM_PG_SUPPORT == STD_ON) || (J1939NM_GATEWAY_SUPPORT == STD_ON) || (J1939NM_NAME_MANAGEMENT_SUPPORT == STD_ON))
    if (J1939Nm_GetPduTypeOfTxPdu(TxPduId) == J1939NM_AC_TX_PDU_PDUTYPEOFTXPDU)
#endif
    {
      J1939Nm_InternalConfirmAc(channelIdx, channelState, pduState);
    }
#if (((J1939NM_NM_PG_SUPPORT == STD_ON) || (J1939NM_GATEWAY_SUPPORT == STD_ON) || ((J1939NM_NAME_MANAGEMENT_SUPPORT == STD_ON) && (J1939NM_EXTERNAL_NODES_USED == STD_ON))) && (J1939NM_NMQUEUE == STD_ON))
    /* #70 If it is a NM pdu, send next Nm pdu from queue. */
    else
    {
      J1939Nm_InternalProcessNmQueue(channelIdx);
    }
#endif
  }

  /* ----- Development Error Report ------------------------------------- */
#if (J1939NM_DEV_ERROR_REPORT == STD_ON)
  if (errorId != J1939NM_E_NO_ERROR)
  {
    /* \trace SPEC-2168285 */
    J1939Nm_ReportDetError(J1939NM_SID_TXCONFIRMATION, errorId);
  }
#else
  J1939NM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983 */ /* MD_MSR_DummyStmt */
#endif
} /* J1939Nm_TxConfirmation() */


/**********************************************************************************************************************
 *  J1939Nm_RequestIndication()
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
/* *INDENT-OFF* */
/* PRQA S 6030, 6060, 6080 4 */ /* MD_MSR_STCYC, MD_MSR_STPAR, MD_MSR_STMIF */
/* *INDENT-ON* */
FUNC(void, J1939NM_CODE) J1939Nm_RequestIndication(uint8 node, NetworkHandleType channel, uint32 requestedPgn,
                                                   P2CONST(J1939Rm_ExtIdInfoType, AUTOMATIC, J1939NM_APPL_DATA)
                                                   extIdInfo, uint8 sourceAddress, uint8 destAddress, uint8 priority)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = J1939NM_E_NO_ERROR; /* PRQA S 2981 */ /* MD_MSR_RetVal */

  J1939NM_DUMMY_STATEMENT(requestedPgn); /* PRQA S 1338, 2983 */ /* MD_MSR_DummyStmt */
  J1939NM_DUMMY_STATEMENT(extIdInfo); /* PRQA S 1338, 2983 */ /* MD_MSR_DummyStmt */
  J1939NM_DUMMY_STATEMENT(sourceAddress); /* PRQA S 1338, 2983 */ /* MD_MSR_DummyStmt */
  J1939NM_DUMMY_STATEMENT(priority); /* PRQA S 1338, 2983 */ /* MD_MSR_DummyStmt */

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check that the J1939Nm is initialized. \trace SPEC-2168258 */
  if (J1939Nm_ModuleInitialized == J1939NM_UNINIT)
  {
    errorId = J1939NM_E_UNINIT; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  }
#if (J1939NM_DEV_ERROR_DETECT == STD_ON)
  /* #20 Check if the ID of the node is valid. \trace SPEC-2168302 */
  else if (node >= J1939Nm_GetSizeOfNode())
  {
    errorId = J1939NM_E_INVALID_NODE; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  }
  /* #30 Check that the channel is valid. \trace SPEC-2168288 */
  else if (!J1939Nm_Channel_Valid(channel)) /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */
  {
    errorId = J1939NM_E_INVALID_NETWORK_ID; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  }
  /* #40 Check that the PGN is valid. \trace SPEC-2168302 */
  else if ((requestedPgn != J1939NM_PGN_AC) && (requestedPgn != J1939NM_PGN_NM))
  {
    errorId = J1939NM_E_INVALID_PGN; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  }
  /* #50 Check that the source address is valid. \trace SPEC-2168302 */
  else if (!J1939Nm_SA_Valid(sourceAddress))
  {
    errorId = J1939NM_E_INVALID_ADDRESS; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  }
  /* #60 Check that the destination address is valid. \trace SPEC-2168302 */
  else if (!J1939Nm_DA_Valid(destAddress))
  {
    errorId = J1939NM_E_INVALID_ADDRESS; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  }
  /* #70 Check that the priority is valid. \trace SPEC-2168302 */
  else if (!J1939Nm_Priority_Valid(priority))
  {
    errorId = J1939NM_E_INVALID_PRIO; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  }
#endif
  /* #80 If the initial checks are passed or not required: */
  else
  {
    /* ----- Implementation ----------------------------------------------- */

    /* #90 If it is an AC pdu, indicate request and handle Ac. */
    /*@ assert node < J1939Nm_GetSizeOfNode(); */ /* VCA_J1939NM_NODE */
#if (J1939NM_NM_PG_SUPPORT == STD_ON)
    if (requestedPgn == J1939NM_PGN_AC)
#endif
    {
      J1939Nm_InternalAcRequestIndication(node, channel, sourceAddress, destAddress);
    }
#if (J1939NM_NM_PG_SUPPORT == STD_ON)
    /* #100 If it is a NM pdu with correct destination address, send Nm message. */
    else
    {
      if (destAddress == J1939Nm_GetNodeAddressOfNode(node))
      {
        J1939Nm_ChannelIdxOfComMChannelType channelIdx = J1939Nm_GetChannelIdxOfComMChannel(channel);
        /*@ assert channelIdx < J1939Nm_GetSizeOfChannel(); */ /* VCA_J1939NM_CHANNEL_VIA_COMMCHANNEL_CSL03 */
        J1939Nm_DynamicNmRequestIndication(channelIdx, node, sourceAddress, destAddress);
      }
    }
#endif
  }

  /* ----- Development Error Report ------------------------------------- */
#if (J1939NM_DEV_ERROR_REPORT == STD_ON)
  if (errorId != J1939NM_E_NO_ERROR)
  {
    /* \trace SPEC-2168285 */
    J1939Nm_ReportDetError(J1939NM_SID_REQUESTINDICATION, errorId);
  }
#else
  J1939NM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983 */ /* MD_MSR_DummyStmt */
#endif
} /* J1939Nm_RequestIndication() */


/**********************************************************************************************************************
 *  J1939Nm_NetworkRequest()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, J1939NM_CODE) J1939Nm_NetworkRequest(CONST(NetworkHandleType, AUTOMATIC) channel)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType result = E_NOT_OK;
  uint8 errorId = J1939NM_E_NO_ERROR; /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check that the J1939Nm is initialized. \trace SPEC-2168258 */
  if (J1939Nm_ModuleInitialized == J1939NM_UNINIT)
  {
    errorId = J1939NM_E_UNINIT; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  }
#if (J1939NM_DEV_ERROR_DETECT == STD_ON)
  /* #20 Check that the channel is valid. \trace SPEC-2168288 */
  else if (!J1939Nm_Channel_Valid(channel)) /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */
  {
    errorId = J1939NM_E_INVALID_NETWORK_ID; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  }
#endif
  /* #30 If the initial checks are passed or not required: */
  else
  {
    /* ----- Implementation ----------------------------------------------- */

    /* #40 Proceed with the internal J1939Nm_NetworkRequest function. */
    J1939Nm_InternalNetworkRequest(channel); /* VCA_J1939NM_COMMCHANNEL */
    result = E_OK;
  }

  /* ----- Development Error Report ------------------------------------- */
#if (J1939NM_DEV_ERROR_REPORT == STD_ON)
  if (errorId != J1939NM_E_NO_ERROR)
  {
    /* \trace SPEC-2168285 */
    J1939Nm_ReportDetError(J1939NM_SID_NETWORKREQUEST, errorId);
  }
#else
  J1939NM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983 */ /* MD_MSR_DummyStmt */
#endif

  return result;
} /* J1939Nm_NetworkRequest() */


/**********************************************************************************************************************
 *  J1939Nm_NetworkRelease()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, J1939NM_CODE) J1939Nm_NetworkRelease(CONST(NetworkHandleType, AUTOMATIC) channel)
{

  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType result = E_NOT_OK;
  uint8 errorId = J1939NM_E_NO_ERROR; /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check that the J1939Nm is initialized. \trace SPEC-2168258 */
  if (J1939Nm_ModuleInitialized == J1939NM_UNINIT)
  {
    errorId = J1939NM_E_UNINIT; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  }
#if (J1939NM_DEV_ERROR_DETECT == STD_ON)
  /* #20 Check that the channel is valid. \trace SPEC-2168288 */
  else if (!J1939Nm_Channel_Valid(channel)) /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */
  {
    errorId = J1939NM_E_INVALID_NETWORK_ID; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  }
#endif
  /* #30 If the initial checks are passed or not required: */
  else
  {
    /* ----- Implementation ----------------------------------------------- */

    /* #40 Proceed with the internal J1939Nm_NetworkRelease function. */
    J1939Nm_InternalNetworkRelease(channel); /* VCA_J1939NM_COMMCHANNEL */
    result = E_OK;
  }

  /* ----- Development Error Report ------------------------------------- */
#if (J1939NM_DEV_ERROR_REPORT == STD_ON)
  if (errorId != J1939NM_E_NO_ERROR)
  {
    /* \trace SPEC-2168285 */
    J1939Nm_ReportDetError(J1939NM_SID_NETWORKRELEASE, errorId);
  }
#else
  J1939NM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983 */ /* MD_MSR_DummyStmt */
#endif

  return result;
} /* J1939Nm_NetworkRelease() */


/**********************************************************************************************************************
 *  J1939Nm_GetState()
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
FUNC(Std_ReturnType, J1939NM_CODE) J1939Nm_GetState(CONST(NetworkHandleType, AUTOMATIC) channel,
                                                    CONSTP2VAR(Nm_StateType, AUTOMATIC, J1939NM_APPL_VAR) stateP,
                                                    CONSTP2VAR(Nm_ModeType, AUTOMATIC, J1939NM_APPL_VAR) modeP)
{

  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType result = E_NOT_OK;
  uint8 errorId = J1939NM_E_NO_ERROR; /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check that the J1939Nm is initialized. \trace SPEC-2168258 */
  if (J1939Nm_ModuleInitialized == J1939NM_UNINIT)
  {
    errorId = J1939NM_E_UNINIT; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  }
#if (J1939NM_DEV_ERROR_DETECT == STD_ON)
  /* #20 Check that the channel is valid. \trace SPEC-2168288 */
  else if (!J1939Nm_Channel_Valid(channel)) /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */
  {
    errorId = J1939NM_E_INVALID_NETWORK_ID; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  }
  /* #30 Check if the stateP data pointer is set. */
  else if (stateP == NULL_PTR)
  {
    errorId = J1939NM_E_PARAM_POINTER; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  }
  /* #40 Check if the modeP data pointer is set. */
  else if (modeP == NULL_PTR)
  {
    errorId = J1939NM_E_PARAM_POINTER; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  }
#endif
  /* #50 If the initial checks are passed or not required: */
  else
  {
    /* ----- Implementation ----------------------------------------------- */

    /* #60 Proceed with the internal J1939Nm_GetState function. */
    J1939Nm_InternalGetState(channel, stateP, modeP);
    result = E_OK;
  }

  /* ----- Development Error Report ------------------------------------- */
#if (J1939NM_DEV_ERROR_REPORT == STD_ON)
  if (errorId != J1939NM_E_NO_ERROR)
  {
    /* \trace SPEC-2168285 */
    J1939Nm_ReportDetError(J1939NM_SID_GETSTATE, errorId);
  }
#else
  J1939NM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983 */ /* MD_MSR_DummyStmt */
#endif

  return result;
} /* J1939Nm_GetState() */


/**********************************************************************************************************************
 *  J1939Nm_GetBusOffDelay()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(void, J1939NM_CODE) J1939Nm_GetBusOffDelay(NetworkHandleType channel,
                                                P2VAR(uint8, AUTOMATIC, J1939NM_APPL_VAR) delayCyclesPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = J1939NM_E_NO_ERROR; /* PRQA S 2981 */ /* MD_MSR_RetVal */

  J1939NM_DUMMY_STATEMENT(channel); /* PRQA S 1338, 2983 */ /* MD_MSR_DummyStmt */

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check that the J1939Nm is initialized. \trace SPEC-2168258 */
  if (J1939Nm_ModuleInitialized == J1939NM_UNINIT)
  {
    errorId = J1939NM_E_UNINIT; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  }
#if (J1939NM_DEV_ERROR_DETECT == STD_ON)
  /* #20 Check if the delayCyclesPtr data pointer is set. */
  else if (delayCyclesPtr == NULL_PTR)
  {
    errorId = J1939NM_E_PARAM_POINTER; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  }
#endif
  /* #30 If the initial checks are passed or not required: */
  else
  {
    /* ----- Implementation ----------------------------------------------- */

    /* #40 Proceed with the internal J1939Nm_GetBusOffDelay function. */
    J1939Nm_InternalGetBusOffDelay(channel, delayCyclesPtr);
  }

  /* ----- Development Error Report ------------------------------------- */
#if (J1939NM_DEV_ERROR_REPORT == STD_ON)
  if (errorId != J1939NM_E_NO_ERROR)
  {
    /* \trace SPEC-2168285 */
    J1939Nm_ReportDetError(J1939NM_SID_GETBUSOFFDELAY, errorId);
  }
#else
  J1939NM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983 */ /* MD_MSR_DummyStmt */
#endif
} /* J1939Nm_GetBusOffDelay() */


/**********************************************************************************************************************
 *  J1939Nm_BusOffEnd()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(void, J1939NM_CODE) J1939Nm_BusOffEnd(NetworkHandleType channel)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = J1939NM_E_NO_ERROR; /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check that the J1939Nm is initialized. \trace SPEC-2168258 */
  if (J1939Nm_ModuleInitialized == J1939NM_UNINIT)
  {
    errorId = J1939NM_E_UNINIT; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  }
  /* #20 If the initial checks are passed or not required: */
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #30 If channel is valid */
    if (J1939Nm_Channel_Valid(channel)) /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */
    {
      /* #40 Set BusOff to FALSE */
      J1939Nm_GetChannelState(J1939Nm_GetChannelIdxOfComMChannel(channel)).BusOff = FALSE; /* VCA_J1939NM_CHANNELSTATE_VIA_COMMCHANNEL_CSL03 */
    }
  }

  /* ----- Development Error Report ------------------------------------- */
#if (J1939NM_DEV_ERROR_REPORT == STD_ON)
  if (errorId != J1939NM_E_NO_ERROR)
  {
    /* \trace SPEC-2168285 */
    J1939Nm_ReportDetError(J1939NM_SID_BUSOFFEND, errorId);
  }
#else
  J1939NM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983 */ /* MD_MSR_DummyStmt */
#endif
} /* J1939Nm_BusOffEnd() */


/**********************************************************************************************************************
 *  Dummy Functions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  J1939Nm_CheckRemoteSleepIndication()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
/* *INDENT-OFF* */
/* PRQA S 3673 4 */ /* MD_MSR_Rule8.13 */
/* *INDENT-ON* */
FUNC(Std_ReturnType, J1939NM_CODE) J1939Nm_CheckRemoteSleepIndication(CONST(NetworkHandleType, AUTOMATIC) channel,
                                                                      CONSTP2VAR(boolean, AUTOMATIC,
                                                                                 J1939NM_APPL_VAR) nmRemoteSleepIndPtr)
{
  J1939NM_DUMMY_STATEMENT_CONST(channel); /* PRQA S 1338, 2983 */ /* MD_MSR_DummyStmt */
  J1939NM_DUMMY_STATEMENT_CONST(nmRemoteSleepIndPtr); /* PRQA S 1338, 2983 */ /* MD_MSR_DummyStmt */

  J1939Nm_ReportDetError(J1939NM_SID_CHECKREMOTESLEEPINDICATION, J1939NM_E_DUMMY_API);

  /* Note: This function is not yet implemented, and returns always E_NOT_OK. */
  return E_NOT_OK;
} /* J1939Nm_CheckRemoteSleepIndication() */


/**********************************************************************************************************************
 *  J1939Nm_DisableCommunication()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, J1939NM_CODE) J1939Nm_DisableCommunication(CONST(NetworkHandleType, AUTOMATIC) channel)
{
  J1939NM_DUMMY_STATEMENT_CONST(channel); /* PRQA S 1338, 2983 */ /* MD_MSR_DummyStmt */

  J1939Nm_ReportDetError(J1939NM_SID_DISABLECOMMUNICATION, J1939NM_E_DUMMY_API);

  /* Note: This function is not yet implemented, and returns always E_NOT_OK. */
  return E_NOT_OK;
} /* J1939Nm_DisableCommunication() */


/**********************************************************************************************************************
 *  J1939Nm_EnableCommunication()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, J1939NM_CODE) J1939Nm_EnableCommunication(CONST(NetworkHandleType, AUTOMATIC) channel)
{
  J1939NM_DUMMY_STATEMENT_CONST(channel); /* PRQA S 1338, 2983 */ /* MD_MSR_DummyStmt */

  J1939Nm_ReportDetError(J1939NM_SID_ENABLECOMMUNICATION, J1939NM_E_DUMMY_API);

  /* Note: This function is not yet implemented, and returns always E_NOT_OK. */
  return E_NOT_OK;
} /* J1939Nm_EnableCommunication() */


/**********************************************************************************************************************
 *  J1939Nm_GetLocalNodeIdentifier()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
/* *INDENT-OFF* */
/* PRQA S 3673 4 */ /* MD_MSR_Rule8.13 */
/* *INDENT-ON* */
FUNC(Std_ReturnType, J1939NM_CODE) J1939Nm_GetLocalNodeIdentifier(CONST(NetworkHandleType, AUTOMATIC) channel,
                                                                  CONSTP2VAR(uint8, AUTOMATIC,
                                                                             J1939NM_APPL_VAR) nmNodeIdPtr)
{
  J1939NM_DUMMY_STATEMENT_CONST(channel); /* PRQA S 1338, 2983 */ /* MD_MSR_DummyStmt */
  J1939NM_DUMMY_STATEMENT_CONST(nmNodeIdPtr); /* PRQA S 1338, 2983 */ /* MD_MSR_DummyStmt */

  J1939Nm_ReportDetError(J1939NM_SID_GETLOCALNODEIDENTIFIER, J1939NM_E_DUMMY_API);

  /* Note: This function is not yet implemented, and returns always E_NOT_OK. */
  return E_NOT_OK;
} /* J1939Nm_GetLocalNodeIdentifier() */


/**********************************************************************************************************************
 *  J1939Nm_GetNodeIdentifier()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
/* *INDENT-OFF* */
/* PRQA S 3673 3 */ /* MD_MSR_Rule8.13 */
/* *INDENT-ON* */
FUNC(Std_ReturnType, J1939NM_CODE) J1939Nm_GetNodeIdentifier(CONST(NetworkHandleType, AUTOMATIC) channel,
                                                             CONSTP2VAR(uint8, AUTOMATIC, J1939NM_APPL_VAR) nmNodeIdPtr)
{
  J1939NM_DUMMY_STATEMENT_CONST(channel); /* PRQA S 1338, 2983 */ /* MD_MSR_DummyStmt */
  J1939NM_DUMMY_STATEMENT_CONST(nmNodeIdPtr); /* PRQA S 1338, 2983 */ /* MD_MSR_DummyStmt */

  J1939Nm_ReportDetError(J1939NM_SID_GETNODEIDENTIFIER, J1939NM_E_DUMMY_API);

  /* Note: This function is not yet implemented, and returns always E_NOT_OK. */
  return E_NOT_OK;
} /* J1939Nm_GetNodeIdentifier() */


/**********************************************************************************************************************
 *  J1939Nm_GetPduData()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
/* *INDENT-OFF* */
/* PRQA S 3673 3 */ /* MD_MSR_Rule8.13 */
/* *INDENT-ON* */
FUNC(Std_ReturnType, J1939NM_CODE) J1939Nm_GetPduData(CONST(NetworkHandleType, AUTOMATIC) channel,
                                                      CONSTP2VAR(uint8, AUTOMATIC, J1939NM_APPL_VAR) nmPduDataPtr)
{
  J1939NM_DUMMY_STATEMENT_CONST(channel); /* PRQA S 1338, 2983 */ /* MD_MSR_DummyStmt */
  J1939NM_DUMMY_STATEMENT_CONST(nmPduDataPtr); /* PRQA S 1338, 2983 */ /* MD_MSR_DummyStmt */

  J1939Nm_ReportDetError(J1939NM_SID_GETPDUDATA, J1939NM_E_DUMMY_API);

  /* Note: This function is not yet implemented, and returns always E_NOT_OK. */
  return E_NOT_OK;
} /* J1939Nm_GetPduData() */


/**********************************************************************************************************************
 *  J1939Nm_GetUserData()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
/* *INDENT-OFF* */
/* PRQA S 3673 3 */ /* MD_MSR_Rule8.13 */
/* *INDENT-ON* */
FUNC(Std_ReturnType, J1939NM_CODE) J1939Nm_GetUserData(CONST(NetworkHandleType, AUTOMATIC) channel,
                                                       CONSTP2VAR(uint8, AUTOMATIC, J1939NM_APPL_VAR) nmUserDataPtr)
{
  J1939NM_DUMMY_STATEMENT_CONST(channel); /* PRQA S 1338, 2983 */ /* MD_MSR_DummyStmt */
  J1939NM_DUMMY_STATEMENT_CONST(nmUserDataPtr); /* PRQA S 1338, 2983 */ /* MD_MSR_DummyStmt */

  J1939Nm_ReportDetError(J1939NM_SID_GETUSERDATA, J1939NM_E_DUMMY_API);

  /* Note: This function is not yet implemented, and returns always E_NOT_OK. */
  return E_NOT_OK;
} /* J1939Nm_GetUserData() */


/**********************************************************************************************************************
 *  J1939Nm_PassiveStartUp()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, J1939NM_CODE) J1939Nm_PassiveStartUp(CONST(NetworkHandleType, AUTOMATIC) channel)
{
  J1939NM_DUMMY_STATEMENT_CONST(channel); /* PRQA S 1338, 2983 */ /* MD_MSR_DummyStmt */

  J1939Nm_ReportDetError(J1939NM_SID_PASSIVESTARTUP, J1939NM_E_DUMMY_API);

  /* Note: This function is not yet implemented, and returns always E_NOT_OK. */
  return E_NOT_OK;
} /* J1939Nm_PassiveStartUp() */


/**********************************************************************************************************************
 *  J1939Nm_RepeatMessageRequest()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, J1939NM_CODE) J1939Nm_RepeatMessageRequest(CONST(NetworkHandleType, AUTOMATIC) channel)
{
  J1939NM_DUMMY_STATEMENT_CONST(channel); /* PRQA S 1338, 2983 */ /* MD_MSR_DummyStmt */

  J1939Nm_ReportDetError(J1939NM_SID_REPEATMESSAGEREQUEST, J1939NM_E_DUMMY_API);

  /* Note: This function is not yet implemented, and returns always E_NOT_OK. */
  return E_NOT_OK;
} /* J1939Nm_RepeatMessageRequest() */


/**********************************************************************************************************************
 *  J1939Nm_RequestBusSynchronization()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, J1939NM_CODE) J1939Nm_RequestBusSynchronization(CONST(NetworkHandleType, AUTOMATIC) channel)
{
  J1939NM_DUMMY_STATEMENT_CONST(channel); /* PRQA S 1338, 2983 */ /* MD_MSR_DummyStmt */

  J1939Nm_ReportDetError(J1939NM_SID_REQUESTBUSSYNCHRONIZATION, J1939NM_E_DUMMY_API);

  /* Note: This function is not yet implemented, and returns always E_NOT_OK. */
  return E_NOT_OK;
} /* J1939Nm_RequestBusSynchronization() */


/**********************************************************************************************************************
 *  J1939Nm_SetSleepReadyBit()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, J1939NM_CODE) J1939Nm_SetSleepReadyBit(CONST(NetworkHandleType, AUTOMATIC) channel,
                                                            CONST(boolean, AUTOMATIC) nmSleepReadyBit)
{
  J1939NM_DUMMY_STATEMENT_CONST(channel); /* PRQA S 1338, 2983 */ /* MD_MSR_DummyStmt */
  J1939NM_DUMMY_STATEMENT_CONST(nmSleepReadyBit); /* PRQA S 1338, 2983 */ /* MD_MSR_DummyStmt */

  J1939Nm_ReportDetError(J1939NM_SID_SETSLEEPREADYBIT, J1939NM_E_DUMMY_API);

  /* Note: This function is not yet implemented, and returns always E_NOT_OK. */
  return E_NOT_OK;
} /* J1939Nm_SetSleepReadyBit() */


/**********************************************************************************************************************
 *  J1939Nm_SetUserData()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, J1939NM_CODE) J1939Nm_SetUserData(CONST(NetworkHandleType, AUTOMATIC) channel,
                                                       CONSTP2CONST(uint8, AUTOMATIC, J1939NM_APPL_DATA) nmUserDataPtr)
{
  J1939NM_DUMMY_STATEMENT_CONST(channel); /* PRQA S 1338, 2983 */ /* MD_MSR_DummyStmt */
  J1939NM_DUMMY_STATEMENT_CONST(nmUserDataPtr); /* PRQA S 1338, 2983 */ /* MD_MSR_DummyStmt */

  J1939Nm_ReportDetError(J1939NM_SID_SETUSERDATA, J1939NM_E_DUMMY_API);

  /* Note: This function is not yet implemented, and returns always E_NOT_OK. */
  return E_NOT_OK;
} /* J1939Nm_SetUserData() */

#define J1939NM_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*================================================ J1939NM_STOP_SEC_CODE ============================================*/


/* Module specific MISRA deviations:

 MD_J1939Nm_2.2
      Reason:     No deviation in postbuild usecase. The function call produces side effects.
      Risk:       None
      Prevention: N/A
*/


/* VCA_JUSTIFICATION_BEGIN

\ID VCA_J1939NM_CHANNEL_VIA_COMMCHANNEL_CSL03
 \DESCRIPTION Access to Channel via indirection over ComMChannel
 \COUNTERMEASURE \N Qualified use-case CSL03 of ComStackLib

\ID VCA_J1939NM_CHANNEL_VIA_RXPDU_CSL03
 \DESCRIPTION Access of Channel via indirection over RxPdu
 \COUNTERMEASURE \N Qualified use-case CSL03 of ComStackLib

\ID VCA_J1939NM_CHANNEL_VIA_TXPDU_CSL03
 \DESCRIPTION Access of Channel via indirection over TxPdu
 \COUNTERMEASURE \N Qualified use-case CSL03 of ComStackLib

\ID VCA_J1939NM_CHANNELSTATE_VIA_CHANNEL_CSL03
 \DESCRIPTION Access to ChannelState via indirection over Channel
 \COUNTERMEASURE \N Qualified use-case CSL03 of ComStackLib

\ID VCA_J1939NM_CHANNELSTATE_VIA_COMMCHANNEL_CSL03
 \DESCRIPTION Access to ChannelState via indirection over ComMChannel
 \COUNTERMEASURE \N Qualified use-case CSL03 of ComStackLib

\ID VCA_J1939NM_COMMCHANNEL
 \DESCRIPTION Valid ComMChannel is needed
 \COUNTERMEASURE \R The DET check of the function verifies that ComMChannel is valid using CSL01 generated identifiers

\ID VCA_J1939NM_CURRENTNODEADDRESS_VIA_NODECHANNEL_CSL03
 \DESCRIPTION Access to CurrentNodeAddress via indirection over NodeChannel
 \COUNTERMEASURE \N Qualified use-case CSL03 of ComStackLib

\ID VCA_J1939NM_CURRENTNODENAME_VIA_NODE_CSL03
 \DESCRIPTION Access to CurrentNodeName via indirection over Node
 \COUNTERMEASURE \N Qualified use-case CSL03 of ComStackLib

\ID VCA_J1939NM_FCTCALL_PTR2LOCAL
 \DESCRIPTION Function call with a pointer to a local variable as argument
 \COUNTERMEASURE \N Pointers to local variables can be safely considered to be valid.

\ID VCA_J1939NM_NODE
 \DESCRIPTION Valid Node is needed
 \COUNTERMEASURE \R The DET check of the function verifies that Node is valid using CSL01 generated identifiers

\ID VCA_J1939NM_NODE_VIA_CHANNEL_CSL03
 \DESCRIPTION Access of Node via indirection over Channel
 \COUNTERMEASURE \N Qualified use-case CSL03 of ComStackLib

\ID VCA_J1939NM_NODE_VIA_COMMCHANNEL_CSL03
 \DESCRIPTION Access to Node via indirection over ComMChannel
 \COUNTERMEASURE \N Qualified use-case CSL03 of ComStackLib

VCA_J1939NM_NODE_VIA_PDUSTATE_TXPDU
 \DESCRIPTION PduState of TxPdu must contain valid Node related to IsExtNodeId flag
 \COUNTERMEASURE \N PduState Of TxPdu is only set in internal functions. In these functions it is ensured that only valid nodes related to IsExtNodeId flag are set.

\ID VCA_J1939NM_NODECHANNEL_VIA_CHANNEL_CSL03
 \DESCRIPTION Access to NodeChannel via indirection over Channel
 \COUNTERMEASURE \N Qualified use-case CSL03 of ComStackLib

\ID VCA_J1939NM_NODECHANNELSTATE_VIA_CHANNEL_CSL03
 \DESCRIPTION Access to NodeChannelState via indirection over Channel
 \COUNTERMEASURE \N Qualified use-case CSL03 of ComStackLib

\ID VCA_J1939NM_NODECHANNELSTATE_VIA_NODE_CSL03
 \DESCRIPTION Access to NodeChannelState via indirection over Node
 \COUNTERMEASURE \N Qualified use-case CSL03 of ComStackLib

\ID VCA_J1939NM_NODECHANNELSTATE_VIA_NODECHANNEL_CSL03
 \DESCRIPTION Access of NodeChannelState via indirection over NodeChannel
 \COUNTERMEASURE \N Qualified use-case CSL03 of ComStackLib

\ID VCA_J1939NM_POINTERPASSEDTOPUBLICAPI
 \DESCRIPTION Function call with a pointer passed to public J1939Nm API as argument
 \COUNTERMEASURE \S Pointers passed to public J1939Nm APIs point to a valid memory range. A general countermeasure is included in the safety manual SMI-494148.

\ID VCA_J1939NM_PREVIOUSNODEADDRESS_VIA_CHANNEL_CSL03
 \DESCRIPTION Access to PreviousNodeAddress via indirection over Channel
 \COUNTERMEASURE \N Qualified use-case CSL03 of ComStackLib

\ID VCA_J1939NM_PREVIOUSNODEADDRESS_VIA_NODE_CSL03
 \DESCRIPTION Access to PreviousNodeAddress via indirection over Node
 \COUNTERMEASURE \N Qualified use-case CSL03 of ComStackLib

\ID VCA_J1939NM_RANDOMSEED_VIA_NODE_CSL03
 \DESCRIPTION Access to RandomSeed via indirection over Node
 \COUNTERMEASURE \N Qualified use-case CSL03 of ComStackLib

\ID VCA_J1939NM_TXPDUSTATE_CSL01
 \DESCRIPTION Access of TxPduState using ComStackLib
 \COUNTERMEASURE \N Qualified use-case CSL01 of ComStackLib

\ID VCA_J1939NM_TXPDUSTATE_VIA_CHANNEL_CSL03
 \DESCRIPTION Access of PduState via indirection over Channel
 \COUNTERMEASURE \N Qualified use-case CSL03 of ComStackLib

\ID VCA_J1939NM_TXPDUSTATE_VIA_TXPDU_CSL03
 \DESCRIPTION Access of PduState via indirection over TxPdu
 \COUNTERMEASURE \N Qualified use-case CSL03 of ComStackLib

\ID VCA_J1939NM_UNDEF_FCTCALL
 \DESCRIPTION Function call via a function pointer
 \COUNTERMEASURE \S Function pointers must be valid and checked with an integration test. A general countermeasure is included in the safety manual SMI-4.

\ID VCA_J1939NM_UNDEF_FCTCALL_PTR2LOCAL
 \DESCRIPTION Function call with a pointer to a local variable as argument
 \COUNTERMEASURE \N Pointers to local variables can be safely considered to be valid.

\ID VCA_J1939NM_UNDEF_FCTCALL_PTR2NULL
 \DESCRIPTION Function call with a pointer to NULL as argument
 \COUNTERMEASURE \N Pointers to NULL can be safely considered to be valid if NULL_PTR is a valid value

\ID VCA_J1939NM_VERSIONINFO
 \DESCRIPTION The function J1939Nm_GetVersionInfo writes to the object referenced by parameter VersionInfo
 \COUNTERMEASURE \N The caller ensures that the pointers passed to the parameters VersionInfo is valid

   VCA_JUSTIFICATION_END */


/* COV_JUSTIFICATION_BEGIN

--- Preprocessor Coverage Justifications ------------------------------------------------------------------------------

\ID COV_J1939NM_INIT_POINTER
  \ACCEPT TX
  \REASON J1939NM_USE_ECUM_BSW_ERROR_HOOK and J1939NM_FINALMAGICNUMBER are always STD_ON when the parent preprocessor define J1939NM_USE_INIT_POINTER is STD_ON.

COV_JUSTIFICATION_END */
