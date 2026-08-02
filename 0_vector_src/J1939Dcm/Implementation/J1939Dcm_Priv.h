/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2022 by Vector Informatik GmbH.                                              All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  J1939Dcm_Priv.h
 *    Component:  MICROSAR Diagnostic Communication Manager for SAE J1939
 *       Module:  -
 *    Generator:  -
 *
 *  Description:  module internal definitions and macros for J1939 DCM
 *
 *********************************************************************************************************************/

#if !defined (J1939DCM_PRIV_H)
# define J1939DCM_PRIV_H

/*! Inclusion only allowed from J1939Dcm.c */
# if defined (J1939DCM_SOURCE)                                                                                                                       /* COV_J1939DCM_SUPPORT_ALWAYS */

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

/*! Version Information */

/*! Implementation version */
#  define J1939DCM_PRIV_MAJOR_VERSION                                (15u)
#  define J1939DCM_PRIV_MINOR_VERSION                                (1u)
#  define J1939DCM_PRIV_PATCH_VERSION                                (0u)

/**********************************************************************************************************************
 *  CONSTANT MACROS
 *********************************************************************************************************************/
/*! Message processing states */
#  define J1939DCM_MSG_STATE_IDLE                                    0x00u /*!< No message is currently processed */
#  define J1939DCM_MSG_STATE_WAIT                                    0x01u /*!< Wait for next periodic message transmission */
#  define J1939DCM_MSG_STATE_PREP_START                              0x10u /*!< Message preparation start */
#  define J1939DCM_MSG_STATE_PREP_DTCS                               0x12u /*!< Message preparation in progress: get DTCs */
#  define J1939DCM_MSG_STATE_PREP_LAMPDTC                            0x13u /*!< Message preparation in progress: get DTCs with lamp status */
#  define J1939DCM_MSG_STATE_PREP_FF                                 0x14u /*!< Message preparation in progress: get FreezeFrame */
#  define J1939DCM_MSG_STATE_CLEAR                                   0x15u /*!< Message preparation in progress: clear DTCs */
#  define J1939DCM_MSG_STATE_READINESS                               0x16u /*!< Message preparation in progress: get readiness */
#  define J1939DCM_MSG_STATE_TX                                      0x20u /*!< Trigger transmission of messages */
#  define J1939DCM_MSG_STATE_TXCONF                                  0x21u /*!< Wait for TxConfirmation */
#  define J1939DCM_MSG_STATE_SENDACK                                 0x22u /*!< Send ACK / NACK */

/*! Queue bitmaps */
#  define J1939DCM_QUEUE_EMPTY                                       0x00u /*!< Nothing have been queued */
#  define J1939DCM_QUEUE_STATE                                       0x01u /*!< state change has been queued */
#  define J1939DCM_QUEUE_REQ                                         0x02u /*!< Request for DM transmission has been queued */
#  define J1939DCM_QUEUE_DTC                                         0x04u /*!< DTC status change has been queued (DM1 only) */
#  define J1939DCM_QUEUE_TXCONF                                      0x08u /*!< TxConfirmation detected; DM transmission is finished */
#  define J1939DCM_QUEUE_TXFAIL                                      0x10u /*!< TxConfirmation detected, but transmission failed */

/*! Meta data information */
#  define J1939DCM_METADATA_SA_OFFSET                                0u    /*!< Meta-data offset for source address */
#  define J1939DCM_METADATA_DA_OFFSET                                1u    /*!< Meta-data offset for destination address */
#  define J1939DCM_METADATA_PDUF_OFFSET                              2u    /*!< Meta-data offset for PDU-format */
#  define J1939DCM_METADATA_PRIO_OFFSET                              3u    /*!< Meta-data offset for priority */

#  define J1939DCM_MAX_TX_METADATA_LEN                               4u    /*!< Maximum meta data length for transmission */

/*! Invalid values */
#  define J1939DCM_INVALID_NODE_HDL                                  0xFFu
#  define J1939DCM_INVALID_CHANNEL_HDL                               0xFFu
#  define J1939DCM_INVALID_MESSAGE_HDL                               0xFFu
#  define J1939DCM_INVALID_SPN                                       0xFFFFFFFFUL
#  define J1939DCM_INVALID_MEM_ADDRESS                               0xFFu

#  define J1939DCM_ADDRESS_BROADCAST                                 0xFFu

/*! Default priority for message transmission */
#  define J1939DCM_DEFAULT_PRIORITY                                  6u

/*! Helper switches */

/*! Support for any DM which needs SPNs / DTCs */
#  if ((J1939DCM_DM1_SUPPORT  == STD_ON) || \
      (J1939DCM_DM2_SUPPORT  == STD_ON) || \
      (J1939DCM_DM27_SUPPORT == STD_ON) || \
      (J1939DCM_DM35_SUPPORT == STD_ON) || \
      (J1939DCM_DM53_SUPPORT == STD_ON) || \
      (J1939DCM_DM54_SUPPORT == STD_ON))
#   define J1939DCM_NEED_DTC_HANDLER_SPN                             STD_ON
#  else
#   define J1939DCM_NEED_DTC_HANDLER_SPN                             STD_OFF
#  endif


/*! Support for any DM which needs Freeze Frames / DTCs */
#  if ((J1939DCM_DM4_SUPPORT  == STD_ON) || \
      (J1939DCM_DM24_SUPPORT == STD_ON) || \
      (J1939DCM_DM25_SUPPORT == STD_ON))
#   define J1939DCM_NEED_DTC_HANDLER_FF                              STD_ON
#  else
#   define J1939DCM_NEED_DTC_HANDLER_FF                              STD_OFF
#  endif

/*! Support for any DM which needs Lamps / DTCs */
#  if (J1939DCM_DM31_SUPPORT == STD_ON)
#   define J1939DCM_NEED_DTC_HANDLER_LAMP                            STD_ON
#  else
#   define J1939DCM_NEED_DTC_HANDLER_LAMP                            STD_OFF
#  endif

/*! Support for any DM which needs OBD */
#  if (J1939DCM_DM5_SUPPORT  == STD_ON)
#   define J1939DCM_NEED_DTC_HANDLER_OBD                             STD_ON
#  else
#   define J1939DCM_NEED_DTC_HANDLER_OBD                             STD_OFF
#  endif

/*! Support for any DM which needs the DTC handler */
#  if ((J1939DCM_NEED_DTC_HANDLER_SPN  == STD_ON) || \
      (J1939DCM_NEED_DTC_HANDLER_FF   == STD_ON) || \
      (J1939DCM_NEED_DTC_HANDLER_LAMP == STD_ON) || \
      (J1939DCM_NEED_DTC_HANDLER_OBD  == STD_ON))
#   define J1939DCM_NEED_DTC_HANDLER                                 STD_ON
#  else
#   define J1939DCM_NEED_DTC_HANDLER                                 STD_OFF
#  endif


/*! Support for any DM which needs the clear handler */
#  if ((J1939DCM_DM3_SUPPORT  == STD_ON) || \
      (J1939DCM_DM11_SUPPORT == STD_ON) || \
      (J1939DCM_DM55_SUPPORT == STD_ON))
#   define J1939DCM_NEED_CLEAR_HANDLER                               STD_ON
#  else
#   define J1939DCM_NEED_CLEAR_HANDLER                               STD_OFF
#  endif

/*! Support for any DM which needs is handled by the DMx processor */
#  if ((J1939DCM_DM2_SUPPORT  == STD_ON) || \
      (J1939DCM_DM3_SUPPORT  == STD_ON) || \
      (J1939DCM_DM4_SUPPORT  == STD_ON) || \
      (J1939DCM_DM5_SUPPORT  == STD_ON) || \
      (J1939DCM_DM11_SUPPORT == STD_ON) || \
      (J1939DCM_DM24_SUPPORT == STD_ON) || \
      (J1939DCM_DM25_SUPPORT == STD_ON) || \
      (J1939DCM_DM27_SUPPORT == STD_ON) || \
      (J1939DCM_DM31_SUPPORT == STD_ON) || \
      (J1939DCM_DM53_SUPPORT == STD_ON) || \
      (J1939DCM_DM54_SUPPORT == STD_ON) || \
      (J1939DCM_DM55_SUPPORT == STD_ON))
#   define J1939DCM_NEED_DMX_PROCESSOR                               STD_ON
#  else
#   define J1939DCM_NEED_DMX_PROCESSOR                               STD_OFF
#  endif

/*! Support DM1 processor */
#  if (J1939DCM_DM1_SUPPORT  == STD_ON)
#   define J1939DCM_NEED_DM1_PROCESSOR                               STD_ON
#  else
#   define J1939DCM_NEED_DM1_PROCESSOR                               STD_OFF
#  endif

/*! Support DM13 processor */
#  if (J1939DCM_DM13_SUPPORT  == STD_ON)
#   define J1939DCM_NEED_DM13_PROCESSOR                              STD_ON
#  else
#   define J1939DCM_NEED_DM13_PROCESSOR                              STD_OFF
#  endif

/*! Support DM35 processor */
#  if (J1939DCM_DM35_SUPPORT  == STD_ON)
#   define J1939DCM_NEED_DM35_PROCESSOR                              STD_ON
#  else
#   define J1939DCM_NEED_DM35_PROCESSOR                              STD_OFF
#  endif

#  if ((J1939DCM_NEED_DM1_PROCESSOR == STD_ON)  || \
      (J1939DCM_NEED_DM35_PROCESSOR == STD_ON) || \
      (J1939DCM_NEED_DMX_PROCESSOR == STD_ON))
#   define J1939DCM_NEED_DEM                                         STD_ON
#  else
#   define J1939DCM_NEED_DEM                                         STD_OFF
#  endif


/*! Support interface reception */
#  if ((J1939DCM_DM13_SUPPORT  == STD_ON) || \
      (J1939DCM_DM14_SUPPORT == STD_ON) || \
      (J1939DCM_DM17_SUPPORT == STD_ON))
#   define J1939DCM_NEED_IF_RECEPTION                                STD_ON
#  else
#   define J1939DCM_NEED_IF_RECEPTION                                STD_OFF
#  endif

/*! Support TP reception */
#  if ((J1939DCM_DM16_SUPPORT  == STD_ON) || \
      (J1939DCM_DM18_SUPPORT == STD_ON))
#   define J1939DCM_NEED_TP_RECEPTION                                STD_ON
#  else
#   define J1939DCM_NEED_TP_RECEPTION                                STD_OFF
#  endif

/*! Support interface transmission */
#  if ((J1939DCM_DM5_SUPPORT  == STD_ON) || \
      (J1939DCM_DM15_SUPPORT == STD_ON))
#   define J1939DCM_NEED_IF_TRANSMISSION                             STD_ON
#  else
#   define J1939DCM_NEED_IF_TRANSMISSION                             STD_OFF
#  endif

/*! Support TP transmission */
#  if ((J1939DCM_DM1_SUPPORT  == STD_ON) || \
      (J1939DCM_DM2_SUPPORT  == STD_ON) || \
      (J1939DCM_DM4_SUPPORT  == STD_ON) || \
      (J1939DCM_DM16_SUPPORT == STD_ON) || \
      (J1939DCM_DM18_SUPPORT == STD_ON) || \
      (J1939DCM_DM24_SUPPORT == STD_ON) || \
      (J1939DCM_DM25_SUPPORT == STD_ON) || \
      (J1939DCM_DM27_SUPPORT == STD_ON) || \
      (J1939DCM_DM31_SUPPORT == STD_ON) || \
      (J1939DCM_DM35_SUPPORT == STD_ON) || \
      (J1939DCM_DM53_SUPPORT == STD_ON) || \
      (J1939DCM_DM54_SUPPORT == STD_ON))
#   define J1939DCM_NEED_TP_TRANSMISSION                             STD_ON
#  else
#   define J1939DCM_NEED_TP_TRANSMISSION                             STD_OFF
#  endif

/*! Support memory access */
#  if ((J1939DCM_DM14_SUPPORT  == STD_ON) || \
      (J1939DCM_DM15_SUPPORT == STD_ON) || \
      (J1939DCM_DM16_SUPPORT == STD_ON) || \
      (J1939DCM_DM17_SUPPORT == STD_ON) || \
      (J1939DCM_DM18_SUPPORT == STD_ON))
#   define J1939DCM_NEED_MEM_ACCESS                                  STD_ON
#  else
#   define J1939DCM_NEED_MEM_ACCESS                                  STD_OFF
#  endif


/*! DM1 constants */
#  define J1939DCM_DM1_TIMEOUT                                       J1939Dcm_UtiMSecToCycles(1000u) /*!< Default DM1 timeout (1sec) */

/*! DM13 constants */
#  define J1939DCM_DM13_TIMEOUT                                      J1939Dcm_UtiMSecToCycles(6000u) /*!< Default DM13 timeout (6sec) */
#  define J1939DCM_DM13_BROADCAST_STOP                               0x00u                           /*!< Request to stop broadcast */
#  define J1939DCM_DM13_BROADCAST_START                              0x01u                           /*!< Request to start broadcast */
#  define J1939DCM_DM13_BROADCAST_RES                                0x02u                           /*!< Reserved */
#  define J1939DCM_DM13_BROADCAST_DC                                 0x03u                           /*!< Don't care 7 no action */
#  define J1939DCM_DM13_HOLD_ALL                                     0x00u                           /*!< Hold signal set for all devices */
#  define J1939DCM_DM13_HOLD_STATE_MODIFIED                          0x10u                           /*!< Hold signal set for broadcast state has been modified */
#  define J1939DCM_DM13_HOLD_NA                                      0xF0u                           /*!< Hold signal not available */

/*! DM35 constants */
#  define J1939DCM_DM35_TIMEOUT                                      J1939Dcm_UtiMSecToCycles(1000u) /*!< Default DM35 timeout (1sec) */


/*! DM DTC constants */
#  define J1939DCM_DM_MAX_DTCS                                       0xFFFFu /*!< Number of DTCs for non-DM1 message only limited by 16Bit */

/*! DM FF constants */
#  define J1939DCM_FF_MAX_DATA_LENGTH                                251u /*!< Max length of one freeze frame (data added by DEM) */
#  define J1939DCM_FF_SPN_OCC_LENGTH                                 4u   /*!< Length of SPN + occurrence counter (added by J1939Dcm) */
#  define J1939DCM_FF_HEADER_LENGTH                                  5u   /*!< Length of LEN + SPN + occurrence counter (added by J1939Dcm)*/
#  define J1939DCM_FF_LENGTH_OFFSET                                  0u   /*!< Offset of length byte within a reported freeze frame */
#  define J1939DCM_FF_DTC_OFFSET                                     1u   /*!< Offset of 1st DTC byte within a reported freeze frame */
#  define J1939DCM_FF_OCC_OFFSET                                     4u   /*!< Offset of occurrence counter within a reported freeze frame */
#  define J1939DCM_FF_DATA_OFFSET                                    5u   /*!< Offset of 1st data byte within a reported freeze frame */
/*!         +---+---+---+---+---+---+---+- ~ -++---+--
 *          |LEN|   S P N   |Occ| Data .....  ||LEN| ...
 *          +---+---+---+---+---+---+---+- ~ -++---+--
 * Offset:    0   1   2   3   4   5   ..         n
 */

/*! Memory Access constants */
#  define J1939DCM_MEM_ACCESS_MSG_LENGTH                             8u       /*!< Default length for DM14 and DM15 */


/**********************************************************************************************************************
 *  FUNCTION MACROS
 *********************************************************************************************************************/

/*! Helper macros */
/*! Construct 32-bit value from 4 8-bit values */
#  define J1939Dcm_UtiSduDataTo32Bit(dataPtr)                        (uint32)( (uint32)((uint32)((dataPtr)[0]) << 24)                                /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */\
                                                                     | (uint32)((uint32)((dataPtr)[1]) << 16) \
                                                                     | (uint32)((uint32)((dataPtr)[2]) << 8) \
                                                                     | (uint32)((uint32)((dataPtr)[3])) )

/*! Extract the byte next to the MSB of a DWORD value */
#  define J1939Dcm_UtiGetHiLoByte(data32)                            ((uint8)(((uint32)(data32))>>16))                                               /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Extract the byte next to the LSB of a DWORD value */
#  define J1939Dcm_UtiGetLoHiByte(data32)                            ((uint8)(((uint32)(data32))>>8))                                                /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Extract the LSB of a DWORD value */
#  define J1939Dcm_UtiGetLoLoByte(data32)                            ((uint8)(((uint32)(data32)) & 0xFFu))                                           /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/*! Get high byte of 16-bit value */
#  define J1939Dcm_Uti16BitGetHiByte(value)                          (uint8)(((uint16)(value) >> 8) & 0x00FFu)                                       /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Get low byte of 16-bit value */
#  define J1939Dcm_Uti16BitGetLoByte(value)                          (uint8)( (uint16)(value)       & 0x00FFu)                                       /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Converts absolute time to number-of-task cycles */
#  define J1939Dcm_UtiMSecToCycles(msec)                             ((uint16)((msec)/J1939DCM_TASK_CYCLE))                                          /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/*! Sets single or multiple bits in an atomic bit-set */
#  define J1939Dcm_UtiBitOpSet(bitRegisterType, bitRegister, bits)   ((bitRegister) |= (bitRegisterType)(bits))                                      /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Clears single or multiple bits in an atomic bit-set */
#  define J1939Dcm_UtiBitOpClr(bitRegisterType, bitRegister, bits)   ((bitRegister) &= (bitRegisterType)(~((bitRegisterType)(bits))))                /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Returns TRUE if at least one bit in an atomic bit-set is set */
#  define J1939Dcm_UtiBitOpTest(bitRegisterType, bitRegister, bits)  (((bitRegister) & (bitRegisterType)(bits)) != 0u)                               /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/*! Generic memory copy operation for array of elements (i.e. arrays of any data type) */
#  define J1939Dcm_UtiMemCopy(srcPtr, tgtPtr, length)                {uint16 lMemIter; for(lMemIter = 0u; lMemIter < (uint16)(length); ++lMemIter) {(tgtPtr)[lMemIter] = (srcPtr)[lMemIter];}} /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/*! Support dummy statement */
#  if (J1939DCM_USE_DUMMY_STATEMENT == STD_ON)
#   define J1939Dcm_IgnoreUnusedArgument(argument)                   J1939DCM_DUMMY_STATEMENT(argument);                                             /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#   define J1939Dcm_IgnoreUnusedArgument_CONST(argument)             J1939DCM_DUMMY_STATEMENT_CONST(argument);                                       /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#  else
#   define J1939Dcm_IgnoreUnusedArgument(argument)                                                                                                   /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#   define J1939Dcm_IgnoreUnusedArgument_CONST(argument)                                                                                             /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#  endif

/*! Get lock on Dem. FALSE: access to DEM is possible; TRUE: DEM in use */
#  if (J1939DCM_NEED_DEM == STD_ON)
#   define J1939Dcm_DtcHandlerDemSemaphoreGetLocked()                J1939Dcm_DiagContext.CommonContext.DemAccessSemaphore
#   define J1939Dcm_DtcHandlerDemSemaphoreSetLocked(status)          J1939Dcm_DiagContext.CommonContext.DemAccessSemaphore = (status)                /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#  endif


/*! ComState access macros */
/*! Calculate channel mask */
#  define J1939Dcm_ComStateGetChannelMask(channelHdl)                ((J1939Dcm_ChannelSupportType)((J1939Dcm_ChannelSupportType)0x1u << (channelHdl))) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Set node-channel combination online */
#  define J1939Dcm_ComStateSetOnline(nodeHdl, channelHdl)            (J1939Dcm_UtiBitOpSet(J1939Dcm_ChannelSupportType, J1939Dcm_DiagContext.NodeContext[(nodeHdl)].ComState, (J1939Dcm_ComStateGetChannelMask(channelHdl)))) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Set node-channel combination offline */
#  define J1939Dcm_ComStateSetOffline(nodeHdl, channelHdl)           (J1939Dcm_UtiBitOpClr(J1939Dcm_ChannelSupportType, J1939Dcm_DiagContext.NodeContext[(nodeHdl)].ComState, (J1939Dcm_ComStateGetChannelMask(channelHdl)))) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Test whether a node-channel combination is online */
#  define J1939Dcm_ComStateIsOnline(nodeHdl, channelHdl)             (J1939Dcm_UtiBitOpTest(J1939Dcm_ChannelSupportType, J1939Dcm_DiagContext.NodeContext[(nodeHdl)].ComState, (J1939Dcm_ComStateGetChannelMask(channelHdl)))) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#  define J1939Dcm_ComStateIsOnlineAny(nodeHdl)                      (J1939Dcm_DiagContext.NodeContext[(nodeHdl)].ComState != 0u)                    /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/*! Queue bitmap access */
/*! Set a additional bit to requestPending */
#  define J1939Dcm_QueueBitOpSet(queue, bit)                         (J1939Dcm_UtiBitOpSet(uint8, ((queue)->RequestPending), (bit)))                 /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Clear a bit from requestPending */
#  define J1939Dcm_QueueBitOpClr(queue, bit)                         (J1939Dcm_UtiBitOpClr(uint8, ((queue)->RequestPending), (bit)))                 /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Test whether a bit is alread set */
#  define J1939Dcm_QueueBitOpTest(queue, bit)                        (J1939Dcm_UtiBitOpTest(uint8, ((queue)->RequestPending), (bit)))                /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Clear all bits of requestPending */
#  define J1939Dcm_QueueBitOPClrAll(queue)                           ((queue)->RequestPending = J1939DCM_QUEUE_EMPTY)                                /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/*! DM specific macros */
/*! Extract broadcast status for a specific network from DM13 payload: START, STOP, DONTCARE */
#  define J1939Dcm_DM13DataGetBroadcastStatus(messageData, networkType) (uint8)((uint32)((messageData) & (uint32)(0xC0000000uL >> (2u*(networkType)))) >> (30u - (2u*(networkType)))) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Extract holdup signal from DM13 payload: All devices, Not available */
#  define J1939Dcm_DM13DataGetHoldSignal(messageData)                (uint8)((messageData) & 0x000000F0uL)                                           /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Calculate broadcast status mask (equivalent to channel mask) */
#  define J1939Dcm_DM13BroadcastStatusMask(channelHdl)               (uint16)((uint16)0x1u << J1939Dcm_Cfg_GetChannelId((channelHdl)))               /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Activate broadcast of a channel */
#  define J1939Dcm_DM13SetBroadcastStatusActive(channelHdl)          (J1939Dcm_UtiBitOpSet(uint16, (J1939Dcm_DiagContext.CommonContext.DM13State.BroadcastStatusInformation), (J1939Dcm_DM13BroadcastStatusMask((channelHdl))))) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Deactivate broadcast of a channel */
#  define J1939Dcm_DM13ClearBroadcastStatusActive(channelHdl)        (J1939Dcm_UtiBitOpClr(uint16, (J1939Dcm_DiagContext.CommonContext.DM13State.BroadcastStatusInformation), (J1939Dcm_DM13BroadcastStatusMask((channelHdl))))) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Deactivate broadcast of all channels */
#  define J1939Dcm_DM13IsBroadcastStatusActive(channelHdl)           (J1939Dcm_UtiBitOpTest(uint16, (J1939Dcm_DiagContext.CommonContext.DM13State.BroadcastStatusInformation), (J1939Dcm_DM13BroadcastStatusMask((channelHdl))))) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/*! Extracts 3-bit Command from DM14 payload  */
#  define J1939Dcm_DM14GetCommand(messageDataPtr)                    (J1939Dcm_MemCommandType)(((messageDataPtr)[1] & 0x0Eu) >> 1)                   /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Extracts 2-byte key from DM14 payload */
#  define J1939Dcm_DM14GetKey(messageDataPtr)                        (uint16)(((uint16)(messageDataPtr)[7] << 8) | (uint16)(messageDataPtr)[6])      /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Extracts 11-bit Length from DM14 payload */
#  define J1939Dcm_DM14GetLength(messageDataPtr)                     (uint16)((((uint16)((messageDataPtr)[1] & (uint16)0xE0u)) << 3) | (uint16)(messageDataPtr)[0]) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Extracts 3-byte pointer from DM14 payload */
#  define J1939Dcm_DM14GetPointer(messageDataPtr)                    (uint32)(((uint32)(messageDataPtr)[4] << 16) | ((uint32)(messageDataPtr)[3] << 8) | (uint32)(messageDataPtr)[2]) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Extracts 1-byte pointer extension from DM14 payload */
#  define J1939Dcm_DM14GetPointerExt(messageDataPtr)                 (messageDataPtr)[5]                                                             /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Extracts 1-bit pointer type from DM14 payload */
#  define J1939Dcm_DM14GetPointerType(messageDataPtr)                (J1939Dcm_MemPointerTypeType)(((messageDataPtr)[1] & 0x10u) >> 4)               /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/*! Calculate the length of DM24 payload */
#  define J1939Dcm_DM24GetLength(nodeHdl)                            ((PduLengthType)J1939Dcm_GetCfg_SPNArrayEndIdxOfCfg_NodeTable((nodeHdl)) - (PduLengthType)J1939Dcm_GetCfg_SPNArrayStartIdxOfCfg_NodeTable((nodeHdl))) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/*! Activate DM35 for a channel */
#  define J1939Dcm_DM35SetChannelActive(channelMask, channelHdl)     (J1939Dcm_UtiBitOpSet(J1939Dcm_ChannelSupportType, (channelMask), (J1939Dcm_ComStateGetChannelMask(channelHdl)))) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Test whether DM35 is active for a channel */
#  define J1939Dcm_DM35ChannelIsActive(channelMask, channelHdl)      (J1939Dcm_UtiBitOpTest(J1939Dcm_ChannelSupportType, (channelMask), (J1939Dcm_ComStateGetChannelMask(channelHdl)))) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/*! Returns pointer to a configuration */
#  define J1939Dcm_Data_ConfigPtr()                                  J1939Dcm_ConfigDataPtr


/**********************************************************************************************************************
 *  DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
/*! General status structures */

/*! Buffer context */
struct J1939DCM_BUFFERCONTEXT_TAG
{
  PduInfoType   Buffer;
  PduLengthType AvailLen;
};
typedef struct J1939DCM_BUFFERCONTEXT_TAG J1939Dcm_BufferContextType;

/*! TX Pdu context, used to get the PduId and the meta data length from J1939Dcm_UtiGetPeerTxPduContextByDM */
struct J1939DCM_TXPDUCONTEXT_TAG
{
  PduIdType PduId;           /*!< PduId if found in J1939Dcm_UtiGetPeerTxPduContextByDM, otherwise J1939DCM_INVALID_PDU_ID */
  uint8     MetaDataLength;  /*!< Meta data length for the given Pdu or 0 if not found */
};
typedef struct J1939DCM_TXPDUCONTEXT_TAG J1939Dcm_TxPduContextType;

/*! Tx handler context */
struct J1939DCM_TXHANDLER_TAG
{
  P2VAR(J1939Dcm_BufferContextType, AUTOMATIC, J1939DCM_INTERNAL_DATA) BufferContext;                          /*!< Message to be transmitted */
  PduLengthType                                                        BufferIndex[J1939DCM_MAX_NUM_CHANNELS]; /*!< Position within buffer for each channel */
  uint16                                                               TxTimer;                                /*!< Timeout counter */
  uint8                                                                MetaData[J1939DCM_MAX_TX_METADATA_LEN]; /*!< Meta data bytes */
  uint8                                                                DM;                                     /*!< Message to be transmitted */
  volatile uint8                                                       UnconfirmedChannels;                    /*!< Number of channels waiting for TxConf */
  J1939Dcm_TxPathType                                                  TransmitPath;                           /*!< IF or TP transmission */
  J1939Dcm_NodeHdlType                                                 NodeHdl;                                /*!< Node which requested the transmission */
};
typedef struct J1939DCM_TXHANDLER_TAG J1939Dcm_TxHandlerType;

/*! Rx handler context */
struct J1939DCM_RXHANDLER_TAG
{
  J1939Dcm_AddressInfoType RxAddressInfo; /*!< Addressing info of currently active Rx connection */
  PduIdType                RxPduId;       /*!< RxPdu which is currently processed */
};
typedef struct J1939DCM_RXHANDLER_TAG J1939Dcm_RxHandlerType;

/*! DTC handler context */
struct J1939DCM_DTCHANDLER_TAG
{
  P2VAR(J1939Dcm_BufferContextType, AUTOMATIC, J1939DCM_INTERNAL_DATA) MessageData;    /*!< Buffer and size of DM to be transmitted */
  uint16                                                               NumDTCs;        /*!< Overall number of DTCs already retrieved */
  uint8                                                                NumDTCsInCycle; /*!< Number of DTCs retrieved during current task cycle */
};
typedef struct J1939DCM_DTCHANDLER_TAG J1939Dcm_DtcHandlerType;

/*! Clear handler context */
struct J1939DCM_CLEARHANDLER_TAG
{
  Dem_DTCOriginType              DTCOrigin;   /*!< Memory origin primary or secondary */
  Dem_J1939DcmSetClearFilterType ClearFilter; /*!< Filter for clear requests */
  J1939Dcm_NodeHdlType           ClearNode;   /*!< Node address for clear requests */
};
typedef struct J1939DCM_CLEARHANDLER_TAG J1939Dcm_ClearHandlerType;

/*! Filtering handler context */
struct J1939DCM_FILTERHANDLER_TAG
{
  Dem_DTCOriginType               DTCOrigin;    /*!< Primary: Normation DTC or Secondary: ServiceOnly DTC */
  Dem_J1939DcmDTCStatusFilterType StatusFilter; /*!< Active previouslyActive Pending  DTCs */
  Dem_DTCKindType                 DTCKind;      /*!< EmissionRelated NonEmissionRelated All */
  J1939Dcm_NodeHdlType            FiltredNode;  /*!< Node address */
};
typedef struct J1939DCM_FILTERHANDLER_TAG J1939Dcm_FilterHandlerType;

/*! Memory handler context */
struct J1939DCM_MEMHANDLER_TAG
{
  J1939Dcm_BufferContextType TxData;                                                                  /*!< Data to be transmitted */
  PduIdType                  TxPduId;                                                                 /*!< Pdu to be transmitted */
  uint8                      MetaDataLength;                                                          /*!< Meta data length for the given Pdu */
  uint8                      DiagMessage;                                                             /*!< Message to be transmitted (J1939_DM_UNDEF if none) */
  uint8                      DestinationAddress;                                                      /*!< Destination address of pending transmission  */
  uint8                      DM15Buffer[J1939DCM_MEM_ACCESS_MSG_LENGTH + J1939DCM_DM15_METADATA_LEN]; /*!< DM15 data */
  J1939Dcm_NodeHdlType       NodeHdl;                                                                 /*!< Node for which transmission shall be triggered */
  J1939Dcm_ChannelHdlType    ChannelHdl;                                                              /*!< Channel for which transmission shall be triggered */
  J1939Dcm_MemMsgEventType   MessageEvent;                                                            /*!< Indication, whether a transmission shall be triggered */
};
typedef struct J1939DCM_MEMHANDLER_TAG J1939Dcm_MemHandlerType;

/* --- DM processing structures -------------------------------------------------------------------------------------*/
/*! Message processing context for DMs with DTCs */
struct J1939DCM_DMXSTATE_TAG
{
  J1939Dcm_BufferContextType BufferContext;                      /*!< Control structure for message buffer */
  uint8                      ProcessingState;                    /*!< Current status of message processing */
  boolean                    HasDemAccess;                       /*!< TRUE: DEM access in progress, semaphore is locked */
  J1939Dcm_ChannelHdlType    ChannelHdl;                         /*!< Channel for SendAck */
  J1939Dcm_MessageHdlType    MessageHdl;                         /*!< PGN for SendAck, TxPdu for Transmit */
  uint8                      ResponseDA;                         /*!< Address for response (Transmit) or ACK (SendAck) */
  J1939Rm_AckCode            Acknowledge;                        /*!< Acknowledge code for SendAck */
  uint8                      Buffer[J1939DCM_BUFFERSIZE_COMMON]; /*!< Buffer for DM message */
};
typedef struct J1939DCM_DMXSTATE_TAG J1939Dcm_DMxStateType;

/*! Queue information for DMs with DTCs */
struct J1939DCM_DMXQUEUE_TAG
{
  uint8                   RequestPending;     /*!< Bitmask with events affecting DM processing */
  uint8                   ResponseDA;         /*!< QUEUE_REQ: destination address for response */
  J1939Dcm_ChannelHdlType ChannelHdl;         /*!< QUEUE_REQ: channel for response */
  J1939Dcm_MessageHdlType MessageHdl;         /*!< QUEUE_REQ: DM to be transmitted */
  J1939Dcm_StateType      StateChangeRequest; /*!< QUEUE_STATE: new communication state */
};
typedef struct J1939DCM_DMXQUEUE_TAG J1939Dcm_DMxQueueType;

/*! Message processing context for DM1 */
struct J1939DCM_DM1STATE_TAG
{
  J1939Dcm_BufferContextType BufferContext;                     /*!< Control structure for message buffer */
  uint16                     Timer;                             /*!< Timeout counter for periodic transmission */
  PduIdType                  TxPdus[J1939DCM_MAX_NUM_CHANNELS]; /*!< Configured DM1 TxPdus for each channel */
  uint8                      ProcessingState;                   /*!< Current status of DM1 processing */
  uint8                      ResponseDA;                        /*!< Destination address for next DM1 transmission */
  uint8                      Buffer[J1939DCM_BUFFERSIZE_DM1];   /*!< Buffer for DM1 message */
  J1939Dcm_ChannelHdlType    ChannelHdl;                        /*!< Channel for single DM1 request */
  boolean                    DTCSTatusChanged;                  /*!< TRUE: DTC status already changed since last periodic Tx */
  boolean                    HasDemAccess;                      /*!< TRUE: DEM access in progress, semaphore is locked */
  boolean                    IsTimerExpired;                    /*!< TRUE: Timer was expired */
};
typedef struct J1939DCM_DM1STATE_TAG J1939Dcm_DM1StateType;

/*! Queue information for DM1 */
struct J1939DCM_DM1QUEUE_TAG
{
  uint8 RequestPending;                       /*!< Bitmask with DM1 triggers */
  J1939Dcm_StateType      StateChangeRequest; /*!< QUEUE_STATE: new communication state */
  uint8                   ResponseDA;         /*!< QUEUE_REQ: destination address for DM1 transmission */
  J1939Dcm_ChannelHdlType ChannelHdl;         /*!< QUEUE_REQ: channel for DM1 transmission */
};
typedef struct J1939DCM_DM1QUEUE_TAG J1939Dcm_DM1QueueType;


/*! Message processing context for DM13 */
struct J1939DCM_DM13STATE_TAG
{
  uint16 BroadcastDisableTimer;      /*!< Timeout counter while broadcast is disabled */
  uint16 BroadcastStatusInformation; /*!< Bit mask provided to the BSWM */
  uint8  NumActiveBroadcastChannels; /*!< Channels with active broadcast; if 0, stop DM1 & DM35 */
};
typedef struct J1939DCM_DM13STATE_TAG J1939Dcm_DM13StateType;

/*! Queue information for DM13 */
struct J1939DCM_DM13QUEUE_TAG
{
  boolean RequestPending;                              /*!< TRUE: DM13 have been received but not yet processed */
  uint8   BroadcastCommand[J1939DCM_MAX_NUM_CHANNELS]; /*!< Broadcast command of last DM13 (start, stop, none) */
  uint8   HoldSignal;                                  /*!< Hold signal of last DM13 */
};
typedef struct J1939DCM_DM13QUEUE_TAG J1939Dcm_DM13QueueType;


/*! Message processing context for DM35 */
struct J1939DCM_DM35STATE_TAG
{
  J1939Dcm_BufferContextType  BufferContext;                      /*!< Control structure for message buffer */
  uint16                      Timer;                              /*!< Timeout counter for periodic transmission */
  J1939Dcm_ChannelSupportType ActiveChannels;                     /*!< Bitmask of channels which transmit DM35 */
  PduIdType                   TxPdus[J1939DCM_MAX_NUM_CHANNELS];  /*!< TxPdus for each channel */
  uint8                       ProcessingState;                    /*!< Current status of DM35 processing */
  uint8                       Buffer[J1939DCM_BUFFERSIZE_COMMON]; /*!< Buffer for DM35 message */
  boolean                     HasDemAccess;                       /*!< TRUE: DEM access in progress, semaphore is locked */
};
typedef struct J1939DCM_DM35STATE_TAG J1939Dcm_DM35StateType;

/*! Queue information for DM35 */
struct J1939DCM_DM35QUEUE_TAG
{
  J1939Dcm_ChannelSupportType RequestedChannels;  /*!< QUEUE_REQ: channels for which DM35 shall be transmitted  */
  uint8                       RequestPending;     /*!< Bitmask with DM35 triggers */
  J1939Dcm_StateType          StateChangeRequest; /*!< QUEUE_STATE: new communication state */
};
typedef struct J1939DCM_DM35QUEUE_TAG J1939Dcm_DM35QueueType;

/*! Data container for node dependent context */
struct J1939DCM_NODECONTEXT_TAG
{
#  if (J1939DCM_NEED_DM1_PROCESSOR == STD_ON)
  J1939Dcm_DM1StateType DM1State;                          /*!< Node specific DM1 state */
#  endif
#  if (J1939DCM_NEED_DM35_PROCESSOR == STD_ON)
  J1939Dcm_DM35StateType DM35State;                        /*!< Node specific DM35 state */
#  endif
#  if (J1939DCM_NEED_DMX_PROCESSOR == STD_ON)
  J1939Dcm_DMxStateType DMxState;                          /*!< Node specific DMx state */
#  endif
#  if (J1939DCM_NEED_DMX_PROCESSOR == STD_ON)
  volatile J1939Dcm_DMxQueueType DMxQueue;                 /*!< Node specific DMx queue */
#  endif
#  if (J1939DCM_NEED_DM35_PROCESSOR == STD_ON)
  volatile J1939Dcm_DM35QueueType DM35Queue;               /*!< Node specific DM35 queue */
#  endif
#  if (J1939DCM_NEED_DM1_PROCESSOR == STD_ON)
  volatile J1939Dcm_DM1QueueType DM1Queue;                 /*!< Node specific DM1 queue */
#  endif
  J1939Dcm_ChannelSupportType ComState;                    /*!< Communication states of channels in a specific node. */
  J1939Dcm_NodeHdlType    NodeHdl;                         /*!< Node handle */
};
typedef struct J1939DCM_NODECONTEXT_TAG J1939Dcm_NodeContextType;
typedef CONSTP2VAR(J1939Dcm_NodeContextType, TYPEDEF, J1939DCM_INTERNAL_DATA) J1939Dcm_NodeContextPtrType;

#  if (J1939DCM_NEED_DM1_PROCESSOR == STD_ON)
typedef CONSTP2VAR(J1939Dcm_DM1StateType, TYPEDEF, J1939DCM_INTERNAL_DATA) J1939Dcm_DM1StatePtrType;
typedef CONSTP2CONST(J1939Dcm_DM1StateType, TYPEDEF, J1939DCM_INTERNAL_DATA) J1939Dcm_DM1StateReadPtrType;
typedef CONSTP2CONST(J1939Dcm_DM1QueueType, TYPEDEF, J1939DCM_INTERNAL_DATA) J1939Dcm_DM1QueueReadPtrType;
typedef volatile CONSTP2VAR(J1939Dcm_DM1QueueType, TYPEDEF, J1939DCM_INTERNAL_DATA) J1939Dcm_DM1QueuePtrType;
#  endif

#  if (J1939DCM_NEED_DM35_PROCESSOR == STD_ON)
typedef CONSTP2VAR(J1939Dcm_DM35StateType, TYPEDEF, J1939DCM_INTERNAL_DATA) J1939Dcm_DM35StatePtrType;
typedef CONSTP2CONST(J1939Dcm_DM35QueueType, TYPEDEF, J1939DCM_INTERNAL_DATA) J1939Dcm_DM35QueueReadPtrType;
typedef volatile CONSTP2VAR(J1939Dcm_DM35QueueType, TYPEDEF, J1939DCM_INTERNAL_DATA) J1939Dcm_DM35QueuePtrType;
#  endif

#  if (J1939DCM_NEED_DMX_PROCESSOR == STD_ON)
typedef CONSTP2VAR(J1939Dcm_DMxStateType, TYPEDEF, J1939DCM_INTERNAL_DATA) J1939Dcm_DMxStatePtrType;
typedef CONSTP2CONST(J1939Dcm_DMxStateType, TYPEDEF, J1939DCM_INTERNAL_DATA) J1939Dcm_DMxStateReadPtrType;
typedef CONSTP2CONST(J1939Dcm_DMxQueueType, TYPEDEF, J1939DCM_INTERNAL_DATA) J1939Dcm_DMxQueueReadPtrType;
typedef volatile CONSTP2VAR(J1939Dcm_DMxQueueType, TYPEDEF, J1939DCM_INTERNAL_DATA) J1939Dcm_DMxQueuePtrType;
#  endif

/*! Data container for node independent context */
struct J1939DCM_COMMONCONTEXT_TAG
{
#  if (J1939DCM_NEED_MEM_ACCESS == STD_ON)
  J1939Dcm_MemHandlerType MemHandlerState;                 /*!< Memory handler state used with memory DMs */
#  endif

J1939Dcm_TxHandlerType TxHandlerState;                     /*!< Tx handler state */

#  if (J1939DCM_NEED_DTC_HANDLER == STD_ON)
  J1939Dcm_DtcHandlerType DtcHandlerState;                 /*!< DTC handler state used with get DTCs DMs */
#  endif
#  if (J1939DCM_NEED_TP_RECEPTION == STD_ON)
  J1939Dcm_RxHandlerType RxHandlerState;                   /*!< Rx handler state */
#  endif
#  if (J1939DCM_NEED_CLEAR_HANDLER == STD_ON)
  J1939Dcm_ClearHandlerType ClearHandlerState;             /*!< Clear handler state used with clear DTCs DMs */
#  endif
#  if (J1939DCM_NEED_DM13_PROCESSOR == STD_ON)
  volatile J1939Dcm_DM13QueueType DM13Queue;               /*!< Node specific DM13 queue */
  J1939Dcm_DM13StateType DM13State;                        /*!< Node specific DM13 state */
#  endif
#  if(J1939DCM_NEED_DEM)
  boolean DemAccessSemaphore;                              /*!< Dem access semaphore used to control DEM access */
#  endif
};
typedef struct J1939DCM_COMMONCONTEXT_TAG J1939Dcm_CommonContextType;
#  if (J1939DCM_NEED_DM13_PROCESSOR == STD_ON)
typedef CONSTP2VAR(J1939Dcm_CommonContextType, TYPEDEF, J1939DCM_INTERNAL_DATA) J1939Dcm_CommonContextPtrType;
#  endif

#  if (J1939DCM_NEED_DM13_PROCESSOR == STD_ON)
typedef CONSTP2VAR(J1939Dcm_DM13StateType, TYPEDEF, J1939DCM_INTERNAL_DATA) J1939Dcm_DM13StatePtrType;
typedef CONSTP2CONST(J1939Dcm_DM13QueueType, TYPEDEF, J1939DCM_INTERNAL_DATA) J1939Dcm_DM13QueueReadPtrType;
typedef volatile CONSTP2VAR(J1939Dcm_DM13QueueType, TYPEDEF, J1939DCM_INTERNAL_DATA) J1939Dcm_DM13QueuePtrType;
#  endif

#  if (J1939DCM_NEED_DTC_HANDLER == STD_ON)
  typedef CONSTP2VAR(J1939Dcm_DtcHandlerType, TYPEDEF, J1939DCM_INTERNAL_DATA) J1939Dcm_DtcHandlerPtrType;
#  endif

#  if (J1939DCM_NEED_CLEAR_HANDLER == STD_ON)
  typedef CONSTP2VAR(J1939Dcm_ClearHandlerType, TYPEDEF, J1939DCM_INTERNAL_DATA) J1939Dcm_ClearHandlerPtrType;
  typedef CONSTP2CONST(J1939Dcm_ClearHandlerType, TYPEDEF, J1939DCM_INTERNAL_DATA) J1939Dcm_ClearHandlerReadPtrType;
#  endif

#  if (J1939DCM_NEED_MEM_ACCESS == STD_ON)
  typedef CONSTP2VAR(J1939Dcm_MemHandlerType, TYPEDEF, J1939DCM_INTERNAL_DATA) J1939Dcm_MemHandlerPtrType;
  typedef CONSTP2CONST(J1939Dcm_MemHandlerType, TYPEDEF, J1939DCM_INTERNAL_DATA) J1939Dcm_MemHandlerReadPtrType;
#  endif

#  if (J1939DCM_NEED_TP_RECEPTION == STD_ON)
  typedef CONSTP2VAR(J1939Dcm_RxHandlerType, TYPEDEF, J1939DCM_INTERNAL_DATA) J1939Dcm_RxHandlerPtrType;
  typedef CONSTP2CONST(J1939Dcm_RxHandlerType, TYPEDEF, J1939DCM_INTERNAL_DATA) J1939Dcm_RxHandlerReadPtrType;
#  endif

typedef CONSTP2VAR(J1939Dcm_TxHandlerType, TYPEDEF, J1939DCM_INTERNAL_DATA) J1939Dcm_TxHandlerPtrType;
typedef CONSTP2CONST(J1939Dcm_TxHandlerType, TYPEDEF, J1939DCM_INTERNAL_DATA) J1939Dcm_TxHandlerReadPtrType;

/*! Data container for all diagnostic messages and their relevant information */
struct J1939DCM_DIAGCONTEXT_TAG
{
  J1939Dcm_NodeContextType       NodeContext[J1939DCM_MAX_NUM_NODES];  /*!< Node dependent context */
  J1939Dcm_CommonContextType     CommonContext;                        /*!< Node independent context */
};
typedef struct J1939DCM_DIAGCONTEXT_TAG J1939Dcm_DiagContextType;

/* --- General utilities structures ---------------------------------------------------------------------------------  */
typedef J1939Dcm_Cfg_BusTypeArrayOfCfg_ChannelTableType J1939Dcm_NetworkType;

# endif /* J1939DCM_SOURCE */
#endif /* J1939DCM_PRIV_H */

/**********************************************************************************************************************
 *  END OF FILE: J1939Dcm_Priv.h
 *********************************************************************************************************************/
