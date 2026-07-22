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
/**     \file     Mirror_DestChannelProtocolVector.c
 *      \brief    Mirror destination channel protocol (Vector) source file
 *
 *      \details  Implementation of Mirror destination channel protocol (Vector).
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
#define MIRROR_DESTCHANNELPROTOCOLVECTOR_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Mirror_DestChannelProtocolVector.h"
#include "Mirror_DestChannel.h"

#include "vstdlib.h"

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/
#define MIRROR_VECTOR_PROTOCOL_DOIP_PROTOCOL_VERSION_POS        (0x00u)
#define MIRROR_VECTOR_PROTOCOL_DOIP_INV_PROT_VERSION_POS        (0x01u)
#define MIRROR_VECTOR_PROTOCOL_DOIP_PAYLOAD_TYPE_POS            (0x02u)
#define MIRROR_VECTOR_PROTOCOL_DOIP_PAYLOAD_LEN_POS             (0x04u)

#define MIRROR_VECTOR_PROTOCOL_HDR_PROTOCOL_VERSION_POS         (0x08u)
#define MIRROR_VECTOR_PROTOCOL_HDR_SEQUENCE_NUMBER_POS          (0x09u)
#define MIRROR_VECTOR_PROTOCOL_HDR_BASE_TIMESTAMP_POS           (0x0Au)
#define MIRROR_VECTOR_PROTOCOL_HDR_LENGTH_POS                   (0x0Eu)

#define MIRROR_VECTOR_PROTOCOL_DATA_NETWORK_TYPE_POS            (0x02u)
#define MIRROR_VECTOR_PROTOCOL_DATA_NETWORK_ID_POS              (0x03u)
#define MIRROR_VECTOR_PROTOCOL_DATA_FRAME_ID_POS                (0x04u)
#define MIRROR_VECTOR_PROTOCOL_DATA_PAYLOAD_LEN_POS             (0x08u)

#define MIRROR_VECTOR_PROTOCOL_FIRST_DATA_PACKET_POS            (0x10u)
#define MIRROR_VECTOR_PROTOCOL_DATA_HEADER_SIZE                 (0x0Au)
#define MIRROR_VECTOR_PROTOCOL_NANOSECONDS_TO_MICROSECONDS      (1000u)

# define MIRROR_VECTOR_PROTOCOL_DOIP_HEADER_SIZE                (0x8u)
# define MIRROR_VECTOR_PROTOCOL_DOIP_PROT_VERSION               (0x02u)
# define MIRROR_VECTOR_PROTOCOL_DOIP_INV_PROT_VERSION           (0xFDu)
# define MIRROR_VECTOR_PROTOCOL_DOIP_PAYLOAD_TYPE               ((uint16)0xF002u)
# define MIRROR_VECTOR_PROTOCOL_PROT_VERSION                    (0x1u)

#define MIRROR_VECTOR_PROTOCOL_NETWORK_TYPE_MASK                (0x1Fu)

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/
/*================================================= MIRROR_START_SEC_CODE ===========================================*/
#define MIRROR_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e{451} */

#if ((MIRROR_DESTINATION_CHANNEL_IP == STD_ON) && (MIRROR_DESTINATION_CHANNEL_PROTOCOL_VECTOR == STD_ON))
/**********************************************************************************************************************
 *  Mirror_DestChannelProtocolVector_QueueUseNewElement()
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
FUNC(boolean, MIRROR_CODE) Mirror_DestChannelProtocolVector_QueueUseNewElement(Mirror_DestChannelIpContextType* destChannelCtx, uint8 length)
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
    if(((destChannelCtx->QueueIP.QueueElementWriteIdx + ((uint16)length + MIRROR_VECTOR_PROTOCOL_DATA_HEADER_SIZE)) > destChannelCtx->QueueIP.QueueElementLength) ||
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
} /* Mirror_DestChannelProtocolVector_QueueUseNewElement() */
#endif /* ((MIRROR_DESTINATION_CHANNEL_IP == STD_ON) && (MIRROR_DESTINATION_CHANNEL_PROTOCOL_VECTOR == STD_ON)) */

#if ((MIRROR_DESTINATION_CHANNEL_IP == STD_ON) && (MIRROR_DESTINATION_CHANNEL_PROTOCOL_VECTOR == STD_ON))
/**********************************************************************************************************************
 *  Mirror_DestChannelProtocolVector_QueueNewElement()
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
 *
 */
FUNC(uint16, MIRROR_CODE) Mirror_DestChannelProtocolVector_QueueNewElement(Mirror_DestChannelIpContextType* destChannelCtx, 
                                                                        uint8* newElement, const uint8* payload, uint8 payloadLength,
                                                                        uint32 frameId, uint8 networkId, uint8 metaData,
                                                                        boolean useNewElement, StbM_TimeStampType startTime)
{
  uint16 elementLength;
  uint16 tempWriteIndex = 0u;
  StbM_TimeStampType timeStamp;
  uint8 networkType;
  uint16 dataTimeStamp;

  (void)Mirror_DestChannel_GetTime(&timeStamp);

  elementLength = payloadLength;

  /* #10 If a new queue element shall be used: */
  if(useNewElement == TRUE)
  {
    /* #20 Update write index and length information */
    tempWriteIndex = MIRROR_VECTOR_PROTOCOL_FIRST_DATA_PACKET_POS;
    elementLength += MIRROR_VECTOR_PROTOCOL_FIRST_DATA_PACKET_POS;

    destChannelCtx->QueueIP.QueueElementWriteIdx = 0u;

    /* #30 Store current time. */
    destChannelCtx->QueueIP.WriteTimeStamp.nanoseconds = timeStamp.nanoseconds;
    destChannelCtx->QueueIP.WriteTimeStamp.seconds = timeStamp.seconds;
    destChannelCtx->QueueIP.WriteTimeStamp.secondsHi = timeStamp.secondsHi;
    destChannelCtx->QueueIP.WriteTimeStamp.timeBaseStatus = timeStamp.timeBaseStatus;

#if(MIRROR_TRANSMISSIONDEADLINEOFDESTINATIONCHANNELIP == STD_ON)
    destChannelCtx->TransmissionDeadline = 0u;
    destChannelCtx->TransmissionDeadlineEnabled = TRUE;
#endif

    /* #40 Create the DoIP Header */
    newElement[MIRROR_VECTOR_PROTOCOL_DOIP_PROTOCOL_VERSION_POS] = MIRROR_VECTOR_PROTOCOL_DOIP_PROT_VERSION;
    newElement[MIRROR_VECTOR_PROTOCOL_DOIP_INV_PROT_VERSION_POS] = MIRROR_VECTOR_PROTOCOL_DOIP_INV_PROT_VERSION;
    Mirror_DestChannel_Swap16(MIRROR_VECTOR_PROTOCOL_DOIP_PAYLOAD_TYPE, &newElement[MIRROR_VECTOR_PROTOCOL_DOIP_PAYLOAD_TYPE_POS]);

    /* #50 Create the Mirror Header */
    newElement[MIRROR_VECTOR_PROTOCOL_HDR_PROTOCOL_VERSION_POS] = MIRROR_VECTOR_PROTOCOL_PROT_VERSION;
    newElement[MIRROR_VECTOR_PROTOCOL_HDR_SEQUENCE_NUMBER_POS] = destChannelCtx->SeqNumber;

    Mirror_DestChannel_Swap32(((startTime.nanoseconds - destChannelCtx->QueueIP.WriteTimeStamp.nanoseconds) / MIRROR_VECTOR_PROTOCOL_NANOSECONDS_TO_MICROSECONDS), &(newElement[MIRROR_VECTOR_PROTOCOL_HDR_BASE_TIMESTAMP_POS]));

    destChannelCtx->SeqNumber++;
  }

  /* #60 Create the Mirror data Header */
  dataTimeStamp = (uint16)((timeStamp.nanoseconds - destChannelCtx->QueueIP.WriteTimeStamp.nanoseconds) / MIRROR_VECTOR_PROTOCOL_NANOSECONDS_TO_MICROSECONDS);
  Mirror_DestChannel_Swap16(dataTimeStamp, &newElement[tempWriteIndex]);

  networkType = (metaData & MIRROR_VECTOR_PROTOCOL_NETWORK_TYPE_MASK);

  /* #70 Recalculate the network type. The given type is according the AUTOSAR protocol. */
  if(networkType == 1u)
  {
#if(MIRROR_CAN_MIXED_ID_ENABLED == FALSE)
    if ((frameId & MIRROR_CAN_STANDARD_ID_FD_FLAG_VALUE) != MIRROR_CAN_STANDARD_ID_FD_FLAG_VALUE)
    {
      networkType = 0u;
    }
#else
    if((frameId & MIRROR_CAN_EXTENDED_ID_FD_FLAG_MASK) != MIRROR_CAN_EXTENDED_ID_FD_FLAG_MASK)
    {
      networkType = 0u;
    }
#endif
  }

  newElement[tempWriteIndex + MIRROR_VECTOR_PROTOCOL_DATA_NETWORK_TYPE_POS] = networkType;
  newElement[tempWriteIndex + MIRROR_VECTOR_PROTOCOL_DATA_NETWORK_ID_POS] = networkId;
  Mirror_DestChannel_Swap32(frameId, &newElement[tempWriteIndex + MIRROR_VECTOR_PROTOCOL_DATA_FRAME_ID_POS]);
  Mirror_DestChannel_Swap16((uint16)payloadLength, &newElement[tempWriteIndex + MIRROR_VECTOR_PROTOCOL_DATA_PAYLOAD_LEN_POS]);

  tempWriteIndex += MIRROR_VECTOR_PROTOCOL_DATA_HEADER_SIZE;
  elementLength += MIRROR_VECTOR_PROTOCOL_DATA_HEADER_SIZE;

  /* #80 Copy the given payload to the buffer. */
  if(payloadLength > 0u)
  {
    VStdLib_MemCpy((&newElement[tempWriteIndex]), payload, payloadLength); /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */
  }

  return elementLength;
  /* PRQA S 6060 1 */ /* MD_MSR_STPAR */
} /* Mirror_DestChannelProtocolVector_QueueNewElement() */
#endif /* ((MIRROR_DESTINATION_CHANNEL_IP == STD_ON) && (MIRROR_DESTINATION_CHANNEL_PROTOCOL_VECTOR == STD_ON)) */

#if ((MIRROR_DESTINATION_CHANNEL_IP == STD_ON) && (MIRROR_DESTINATION_CHANNEL_PROTOCOL_VECTOR == STD_ON))
/**********************************************************************************************************************
 *  Mirror_DestChannelProtocolVector_QueueFinalizeElement()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(void, MIRROR_CODE) Mirror_DestChannelProtocolVector_QueueFinalizeElement(uint8* element, uint16 length)
{
  uint16 doIpLength = length - MIRROR_VECTOR_PROTOCOL_DOIP_HEADER_SIZE;

  /* #10 Set the length of the complete element to the DoIP and Mirror header. */
  Mirror_DestChannel_Swap32((uint32)doIpLength, &element[MIRROR_VECTOR_PROTOCOL_DOIP_PAYLOAD_LEN_POS]);
  Mirror_DestChannel_Swap16((length - MIRROR_VECTOR_PROTOCOL_DOIP_HEADER_SIZE), &element[MIRROR_VECTOR_PROTOCOL_HDR_LENGTH_POS]);
} /* Mirror_DestChannelProtocolVector_QueueFinalizeElement() */
#endif /* ((MIRROR_DESTINATION_CHANNEL_IP == STD_ON) && (MIRROR_DESTINATION_CHANNEL_PROTOCOL_VECTOR == STD_ON)) */

#define MIRROR_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e{451} */
/*================================================= MIRROR_STOP_SEC_CODE ============================================*/
/**********************************************************************************************************************
 *  END OF FILE: Mirror_DestChannelProtocolVector.c
 *********************************************************************************************************************/
