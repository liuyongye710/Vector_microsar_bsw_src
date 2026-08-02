/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2019 by Vector Informatik GmbH.                                                  All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**     \file     Mirror_DestChannelProtocolAsr.c
 *      \brief    Mirror destination channel protocol (AUTOSAR) source file
 *
 *      \details  Implementation of Mirror destination channel protocol (AUTOSAR).
 *
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
#define MIRROR_DESTCHANNELPROTOCOLASR_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Mirror_DestChannelProtocolAsr.h"
#include "Mirror_DestChannel.h"

#include "vstdlib.h"

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/
#define MIRROR_DESTCHANNELIP_QUEUE_WRITEIDX_INIT                   (0u)

#define MIRROR_AUTOSAR_PROTOCOL_HEADER_VERSION                     (1u)
#define MIRROR_AUTOSAR_PROTOCOL_HEADER_NETWORK_STATE_FRAME_LOST    (0x80u)

#define MIRROR_AUTOSAR_PROTOCOL_HEADER_LENGTH                      (14u)
#define MIRROR_AUTOSAR_PROTOCOL_HEADER_VERSION_POS                 (0u)
#define MIRROR_AUTOSAR_PROTOCOL_HEADER_SEQUENCE_NUMBER_POS         (1u)
#define MIRROR_AUTOSAR_PROTOCOL_HEADER_TIMESTAMP_SECOND_HI_POS     (2u)
#define MIRROR_AUTOSAR_PROTOCOL_HEADER_TIMESTAMP_SECOND_POS        (4u)
#define MIRROR_AUTOSAR_PROTOCOL_HEADER_TIMESTAMP_NANOSECOND_POS    (8u)
#define MIRROR_AUTOSAR_PROTOCOL_HEADER_LENGTH_POS                  (12u)

#define MIRROR_AUTOSAR_PROTOCOL_DATA_HEADER_MAX_LENGTH             (10u)
#define MIRROR_AUTOSAR_PROTOCOL_DATA_HEADER_METADATA_POS           (2u)
#define MIRROR_AUTOSAR_PROTOCOL_DATA_HEADER_NETWORK_ID_POS         (3u)
#define MIRROR_AUTOSAR_PROTOCOL_DATA_HEADER_NETWORK_STATE_POS      (4u)

#define MIRROR_AUTOSAR_PROTOCOL_DATA_HEADER_TIMESTAMP_LENGTH       (2u)
#define MIRROR_AUTOSAR_PROTOCOL_DATA_HEADER_METADATA_LENGTH        (1u)
#define MIRROR_AUTOSAR_PROTOCOL_DATA_HEADER_NETWORK_ID_LENGTH      (1u)
#define MIRROR_AUTOSAR_PROTOCOL_DATA_HEADER_NETWORK_STATE_LENGTH   (1u)

#define MIRROR_AUTOSAR_PROTOCOL_DATA_HEADER_PAYLOAD_LENGTH_LENGTH  (1u)

#define MIRROR_AUTOSAR_PROTOCOL_DATA_HEADER_NETWORK_STATE_MASK     (0x80u)
#define MIRROR_AUTOSAR_PROTOCOL_DATA_HEADER_FRAME_ID_MASK          (0x40u)
#define MIRROR_AUTOSAR_PROTOCOL_DATA_HEADER_PAYLOAD_MASK           (0x20u)

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
/*================================================= MIRROR_START_SEC_CODE ===========================================*/
#define MIRROR_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e{451} */

#if ((MIRROR_DESTINATION_CHANNEL_IP == STD_ON) && (MIRROR_DESTINATION_CHANNEL_PROTOCOL_AUTOSAR == STD_ON))
/**********************************************************************************************************************
 *  Mirror_DestChannelProtocolAsr_QueueNewElementHeader()
 *********************************************************************************************************************/
/*! \brief          Function to initialize a new queue element header.
 *  \details        -
 *  \param[in,out]  newElement  Pointer to the new queue element
 *  \param[in]      timeStamp   Current time
 *  \param[in]      seqNumber   Current sequence number
 *  \pre            Module is initialized.
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \config         This service is only available if MIRROR_DESTINATION_CHANNEL_IP == STD_ON and
 *                  MIRROR_DESTINATION_CHANNEL_PROTOCOL_AUTOSAR == STD_ON.
 *********************************************************************************************************************/
MIRROR_LOCAL_INLINE FUNC(void, MIRROR_CODE) Mirror_DestChannelProtocolAsr_QueueNewElementHeader(uint8* newElement, 
                                                                                       StbM_TimeStampType timeStamp,
                                                                                       uint8 seqNumber);
#endif /* ((MIRROR_DESTINATION_CHANNEL_IP == STD_ON) && (MIRROR_DESTINATION_CHANNEL_PROTOCOL_AUTOSAR == STD_ON)) */

#if ((MIRROR_DESTINATION_CHANNEL_IP == STD_ON) && (MIRROR_DESTINATION_CHANNEL_PROTOCOL_AUTOSAR == STD_ON))
/**********************************************************************************************************************
 *  Mirror_DestChannelProtocolAsr_QueueNewElementDataHeader()
 *********************************************************************************************************************/
/*! \brief          Function to add the Header to a new queue element.
 *  \details        Header format depends on used protocol specification
 *  \param[in,out]  destChannelCtx Context of the destination channel
 *  \param[in,out]  newElement     The new queue element
 *  \param[in]      frameId        Frame Id
 *  \param[in]      frameIdLength  Length of the frame Id
 *  \param[in]      networkId      Network Id
 *  \param[in]      metaData       Meta data of the source network state
 *  \param[in]      networkState   State of the source network
 *  \param[in]      payloadLength  Length of the payload
 *  \param[in]      writeIndex     Write index
 *  \param[in]      timeStamp      Time stamp
 *  \return         The length of the data frame header
 *  \pre            Module is initialized.
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \config         This service is only available if MIRROR_DESTINATION_CHANNEL_IP == STD_ON and
 *                  MIRROR_DESTINATION_CHANNEL_PROTOCOL_AUTOSAR == STD_ON.
 *********************************************************************************************************************/
MIRROR_LOCAL_INLINE FUNC(uint8, MIRROR_CODE) Mirror_DestChannelProtocolAsr_QueueNewElementDataHeader(Mirror_DestChannelIpContextType* destChannelCtx, 
                                                                                            uint8* newElement,
                                                                                            uint32 frameId,
                                                                                            uint8 frameIdLength,
                                                                                            uint8 networkId,
                                                                                            uint8 metaData,
                                                                                            uint8 networkState,
                                                                                            uint8 payloadLength,
                                                                                            uint16 writeIndex,
                                                                                            uint16 timeStamp);
#endif /* ((MIRROR_DESTINATION_CHANNEL_IP == STD_ON) && (MIRROR_DESTINATION_CHANNEL_PROTOCOL_AUTOSAR == STD_ON)) */

#define MIRROR_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e{451} */
/*================================================= MIRROR_STOP_SEC_CODE ============================================*/
/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/
/*================================================= MIRROR_START_SEC_CODE ===========================================*/
#define MIRROR_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e{451} */

#if ((MIRROR_DESTINATION_CHANNEL_IP == STD_ON) && (MIRROR_DESTINATION_CHANNEL_PROTOCOL_AUTOSAR == STD_ON))
/**********************************************************************************************************************
 *  Mirror_DestChannelProtocolAsr_QueueNewElementHeader()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 */
MIRROR_LOCAL_INLINE FUNC(void, MIRROR_CODE) Mirror_DestChannelProtocolAsr_QueueNewElementHeader(uint8* newElement,
                                                                                       StbM_TimeStampType timeStamp,
                                                                                       uint8 seqNumber)
{
  /* #10 Create a new element header with the given data. */
  newElement[MIRROR_AUTOSAR_PROTOCOL_HEADER_VERSION_POS] = MIRROR_AUTOSAR_PROTOCOL_HEADER_VERSION;
  newElement[MIRROR_AUTOSAR_PROTOCOL_HEADER_SEQUENCE_NUMBER_POS] = seqNumber;

  /* #20 Store time stamp and length in big endian format. */
  Mirror_DestChannel_Swap16(timeStamp.secondsHi, &(newElement[MIRROR_AUTOSAR_PROTOCOL_HEADER_TIMESTAMP_SECOND_HI_POS]));
  Mirror_DestChannel_Swap32(timeStamp.seconds, &(newElement[MIRROR_AUTOSAR_PROTOCOL_HEADER_TIMESTAMP_SECOND_POS]));
  Mirror_DestChannel_Swap32(timeStamp.nanoseconds, &(newElement[MIRROR_AUTOSAR_PROTOCOL_HEADER_TIMESTAMP_NANOSECOND_POS]));
  Mirror_DestChannel_Swap16((uint16)0x0000u, &(newElement[MIRROR_AUTOSAR_PROTOCOL_HEADER_LENGTH_POS]));
} /* Mirror_DestChannelProtocolAsr_QueueNewElementHeader() */
#endif /* ((MIRROR_DESTINATION_CHANNEL_IP == STD_ON) && (MIRROR_DESTINATION_CHANNEL_PROTOCOL_AUTOSAR == STD_ON)) */

#if ((MIRROR_DESTINATION_CHANNEL_IP == STD_ON) && (MIRROR_DESTINATION_CHANNEL_PROTOCOL_AUTOSAR == STD_ON))
/**********************************************************************************************************************
 *  Mirror_DestChannelProtocolAsr_QueueNewElementDataHeader()
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
MIRROR_LOCAL_INLINE FUNC(uint8, MIRROR_CODE) Mirror_DestChannelProtocolAsr_QueueNewElementDataHeader(Mirror_DestChannelIpContextType* destChannelCtx, 
                                                                                            uint8* newElement,
                                                                                            uint32 frameId,
                                                                                            uint8 frameIdLength,
                                                                                            uint8 networkId,
                                                                                            uint8 metaData,
                                                                                            uint8 networkState,
                                                                                            uint8 payloadLength,
                                                                                            uint16 writeIndex,
                                                                                            uint16 timeStamp)
{
  uint8 headerLength = MIRROR_AUTOSAR_PROTOCOL_DATA_HEADER_TIMESTAMP_LENGTH +
                        MIRROR_AUTOSAR_PROTOCOL_DATA_HEADER_METADATA_LENGTH +
                        MIRROR_AUTOSAR_PROTOCOL_DATA_HEADER_NETWORK_ID_LENGTH;

  /* #10 Set time stamp of data header in big endian format. */
  Mirror_DestChannel_Swap16(timeStamp, &newElement[writeIndex]);

  /* #20 Set meta data and network Id. */
  newElement[writeIndex + MIRROR_AUTOSAR_PROTOCOL_DATA_HEADER_METADATA_POS] = metaData;
  newElement[writeIndex + MIRROR_AUTOSAR_PROTOCOL_DATA_HEADER_NETWORK_ID_POS] = networkId;

  /* Set the network state and frame lost flag if available. */
  if(((metaData & MIRROR_AUTOSAR_PROTOCOL_DATA_HEADER_NETWORK_STATE_MASK) == MIRROR_AUTOSAR_PROTOCOL_DATA_HEADER_NETWORK_STATE_MASK) ||
    (destChannelCtx->FrameLost == TRUE))
  {
    newElement[writeIndex + MIRROR_AUTOSAR_PROTOCOL_DATA_HEADER_NETWORK_STATE_POS] = networkState;

    if(destChannelCtx->FrameLost == TRUE)
    {
      newElement[writeIndex + MIRROR_AUTOSAR_PROTOCOL_DATA_HEADER_NETWORK_STATE_POS] |= MIRROR_AUTOSAR_PROTOCOL_HEADER_NETWORK_STATE_FRAME_LOST;

      destChannelCtx->FrameLost = FALSE;
    }

    headerLength += MIRROR_AUTOSAR_PROTOCOL_DATA_HEADER_NETWORK_STATE_LENGTH;
  }

  /* #30 Set the frame Id in big endian format if available. */
  if((metaData & MIRROR_AUTOSAR_PROTOCOL_DATA_HEADER_FRAME_ID_MASK) == MIRROR_AUTOSAR_PROTOCOL_DATA_HEADER_FRAME_ID_MASK)
  {
    if(frameIdLength == MIRROR_AUTOSAR_PROTOCOL_DATA_HEADER_CAN_FRAMEID_LENGTH)
    {
      Mirror_DestChannel_Swap32(frameId, &newElement[writeIndex + headerLength]);
    }
    else if(frameIdLength == MIRROR_AUTOSAR_PROTOCOL_DATA_HEADER_FLEXRAY_FRAMEID_LENGTH)
    {
      uint32 id = frameId;

      VStdLib_MemCpy((&newElement[writeIndex + headerLength]), &id, MIRROR_AUTOSAR_PROTOCOL_DATA_HEADER_FLEXRAY_FRAMEID_LENGTH); /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */
    }
    else if(frameIdLength == MIRROR_AUTOSAR_PROTOCOL_DATA_HEADER_LIN_FRAMEID_LENGTH)
    {
      newElement[writeIndex + headerLength] = (uint8)frameId;
    }
    else
    {
      /* MISRA */
    }

    headerLength += frameIdLength;
  }

  /* #40 Set the payload length if payload is available. */
  if((metaData & MIRROR_AUTOSAR_PROTOCOL_DATA_HEADER_PAYLOAD_MASK) == MIRROR_AUTOSAR_PROTOCOL_DATA_HEADER_PAYLOAD_MASK)
  {
    newElement[writeIndex + headerLength] = payloadLength;

    headerLength += MIRROR_AUTOSAR_PROTOCOL_DATA_HEADER_PAYLOAD_LENGTH_LENGTH;
  }

  return headerLength;
  /* PRQA S 6060 1 */ /* MD_MSR_STPAR */
} /* Mirror_DestChannelProtocolAsr_QueueNewElementDataHeader() */
#endif /* ((MIRROR_DESTINATION_CHANNEL_IP == STD_ON) && (MIRROR_DESTINATION_CHANNEL_PROTOCOL_AUTOSAR == STD_ON)) */

#define MIRROR_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e{451} */
/*================================================= MIRROR_STOP_SEC_CODE ============================================*/
/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/
/*================================================= MIRROR_START_SEC_CODE ===========================================*/
#define MIRROR_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e{451} */

#if ((MIRROR_DESTINATION_CHANNEL_IP == STD_ON) && (MIRROR_DESTINATION_CHANNEL_PROTOCOL_AUTOSAR == STD_ON))
/**********************************************************************************************************************
 *  Mirror_DestChannelProtocolAsr_QueueUseNewElement()
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
FUNC(boolean, MIRROR_CODE) Mirror_DestChannelProtocolAsr_QueueUseNewElement(Mirror_DestChannelIpContextType* destChannelCtx, uint8 length)
{
  StbM_TimeStampType timeStamp;
  uint16 dataTime;
  boolean useNewElement = FALSE;

  /* #10 If the last transmit was triggered by the transmission deadline, a new queue element is needed*/
  if(destChannelCtx->QueueIP.UseNewElementAfterTransmit == TRUE)
  {
    destChannelCtx->QueueIP.UseNewElementAfterTransmit = FALSE;
    useNewElement = TRUE;
  }
  /* #20 Otherwise: */
  else
  {
    Std_ReturnType retVal = Mirror_DestChannel_GetTime(&timeStamp);

    if(retVal == E_OK)
    {
      retVal = Mirror_DestChannel_GetDataTimeStamp(timeStamp, &dataTime);
    }

    /* #30 If the new data do not fit in the current queue element, or a data time stamp overflow is detected, use a new element. */
    if(((destChannelCtx->QueueIP.QueueElementWriteIdx + ((uint16)length + MIRROR_AUTOSAR_PROTOCOL_DATA_HEADER_MAX_LENGTH)) > destChannelCtx->QueueIP.QueueElementLength) ||
        (retVal == E_NOT_OK))
    {
      useNewElement = TRUE;
    }

    /* #40 If the queue is empty, use a new element. */
    if(Mirror_QueueIsEmpty(&(destChannelCtx->QueueIP.Queue)) == TRUE)
    {
      useNewElement = TRUE;
    }
  }

  return useNewElement;
} /* Mirror_DestChannelProtocolAsr_QueueUseNewElement() */
#endif /* ((MIRROR_DESTINATION_CHANNEL_IP == STD_ON) && (MIRROR_DESTINATION_CHANNEL_PROTOCOL_AUTOSAR == STD_ON)) */

#if ((MIRROR_DESTINATION_CHANNEL_IP == STD_ON) && (MIRROR_DESTINATION_CHANNEL_PROTOCOL_AUTOSAR == STD_ON))
/**********************************************************************************************************************
 *  Mirror_DestChannelProtocolAsr_QueueNewElement()
 *********************************************************************************************************************/
/*!
 *
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
FUNC(uint16, MIRROR_CODE) Mirror_DestChannelProtocolAsr_QueueNewElement(Mirror_DestChannelIpContextType* destChannelCtx, 
                                                                        uint8* newElement, const uint8* payload, uint8 payloadLength,
                                                                        uint32 frameId, uint8 frameIdLength, uint8 networkId,
                                                                        uint8 metaData, uint8 networkState, boolean useNewElement)
{
  uint16 elementLength;
  uint16 tempWriteIndex = 0u;
  uint8 dataHeaderLength;
  StbM_TimeStampType timeStamp;
  uint16 dataTimeStamp = 0u;

  elementLength = payloadLength;

  /* #10 If a new queue element shall be used: */
  if(useNewElement == TRUE)
  {
    /* #20 Update write index and length information */
    (void)Mirror_DestChannel_GetTime(&timeStamp);

    destChannelCtx->QueueIP.QueueElementWriteIdx = MIRROR_DESTCHANNELIP_QUEUE_WRITEIDX_INIT;
    tempWriteIndex = MIRROR_AUTOSAR_PROTOCOL_HEADER_LENGTH;
    elementLength += MIRROR_AUTOSAR_PROTOCOL_HEADER_LENGTH;

    /* #30 Trigger the creation of the queue element header. */
    Mirror_DestChannelProtocolAsr_QueueNewElementHeader(newElement, timeStamp, destChannelCtx->SeqNumber);

    /* #40 Update sequence number */
    destChannelCtx->SeqNumber++;

    /* #50 Store current time. */
    destChannelCtx->QueueIP.WriteTimeStamp.nanoseconds = timeStamp.nanoseconds;
    destChannelCtx->QueueIP.WriteTimeStamp.seconds = timeStamp.seconds;
    destChannelCtx->QueueIP.WriteTimeStamp.secondsHi = timeStamp.secondsHi;
    destChannelCtx->QueueIP.WriteTimeStamp.timeBaseStatus = timeStamp.timeBaseStatus;

#if (MIRROR_TRANSMISSIONDEADLINEOFDESTINATIONCHANNELIP == STD_ON)
    destChannelCtx->TransmissionDeadline = 0u;
    destChannelCtx->TransmissionDeadlineEnabled = TRUE;
#endif
  }
  else
  {
    (void)Mirror_DestChannel_GetDataTimeStamp(destChannelCtx->QueueIP.WriteTimeStamp, &dataTimeStamp);
  }

  /* #60 Trigger the creation of the data Header */
  dataHeaderLength = Mirror_DestChannelProtocolAsr_QueueNewElementDataHeader(destChannelCtx, newElement, frameId, frameIdLength, networkId, metaData, networkState, payloadLength, tempWriteIndex, dataTimeStamp);
  tempWriteIndex += dataHeaderLength;
  elementLength += dataHeaderLength;

  /* #70 Copy the given payload to the buffer. */
  if(payloadLength > 0u)
  {
    VStdLib_MemCpy((&newElement[tempWriteIndex]), payload, payloadLength); /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */
  }

  return elementLength;
  /* PRQA S 6060 1 */ /* MD_MSR_STPAR */
} /* Mirror_DestChannelProtocolAsr_QueueNewElement() */
#endif /* ((MIRROR_DESTINATION_CHANNEL_IP == STD_ON) && (MIRROR_DESTINATION_CHANNEL_PROTOCOL_AUTOSAR == STD_ON)) */

#if ((MIRROR_DESTINATION_CHANNEL_IP == STD_ON) && (MIRROR_DESTINATION_CHANNEL_PROTOCOL_AUTOSAR == STD_ON))
/*!
 *
 * Internal comment removed.
 *
 *
 */
/**********************************************************************************************************************
 *  Mirror_DestChannelProtocolAsr_QueueFinalizeElement()
 *********************************************************************************************************************/
FUNC(void, MIRROR_CODE) Mirror_DestChannelProtocolAsr_QueueFinalizeElement(uint8* element, uint16 length)
{
  /* #10 Set the length of the complete element to the header. */
  Mirror_DestChannel_Swap16((length - MIRROR_AUTOSAR_PROTOCOL_HEADER_LENGTH), &element[MIRROR_AUTOSAR_PROTOCOL_HEADER_LENGTH_POS]);
} /* Mirror_DestChannelProtocolAsr_QueueFinalizeElement() */
#endif /* ((MIRROR_DESTINATION_CHANNEL_IP == STD_ON) && (MIRROR_DESTINATION_CHANNEL_PROTOCOL_AUTOSAR == STD_ON)) */

#define MIRROR_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e{451} */
/*================================================= MIRROR_STOP_SEC_CODE ============================================*/
/**********************************************************************************************************************
 *  END OF FILE: Mirror_DestChannelProtocolAsr.c
 *********************************************************************************************************************/
