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
/**     \file     Mirror_DestChannelCan.c
 *      \brief    Mirror CAN destination channel source file
 *
 *      \details  Implementation of Mirror CAN destination channel.
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
#define MIRROR_DESTCHANNELCAN_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Mirror_DestChannelCan.h"
#include "Mirror.h"
#include "Mirror_Int.h"
#include "Mirror_DestChannel.h"

#include "SchM_Mirror.h"

#if (MIRROR_DEV_ERROR_REPORT == STD_ON)
# include "Det.h"
#endif

#if (MIRROR_DESTINATION_CHANNEL_CAN == STD_ON)
# include "CanIf.h"
#endif /* (MIRROR_DESTINATION_CHANNEL_CAN == STD_ON) */

#include "vstdlib.h"

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/
#define MIRROR_DESTCHANNELCAN_QUEUE_FIRST_BYTE_POS           (0u)
#define MIRROR_DESTCHANNELCAN_QUEUE_CANID_LENGTH             (4u)
#define MIRROR_DESTCHANNELCAN_QUEUE_WRITEOFFSET_UNUSED       (0u)
#define MIRROR_DESTCHANNELCAN_CANID_LENGTH                   (4u)

#define MIRROR_DESTCHANNELCAN_STATUS_FRAME_HEADER_LENGTH     (1u)
#define MIRROR_DESTCHANNELCAN_STATUS_FRAME_HEADER_POS        (0u)
#define MIRROR_DESTCHANNELCAN_STATUE_FRAME_LENGTH            (8u)
#define MIRROR_DESTCHANNELCAN_CAN_STATUS_LENGTH              (3u)
#define MIRROR_DESTCHANNELCAN_LIN_STATUS_LENGTH              (3u)
#define MIRROR_DESTCHANNELCAN_LIN_FRAME_STATUS_LENGTH        (4u)
#define MIRROR_DESTCHANNELCAN_STATUS_HEADER_PROT_VERSION_POS (0u)
#define MIRROR_DESTCHANNELCAN_STATUS_META_DATA_POS           (0u)
#define MIRROR_DESTCHANNELCAN_STATUS_NETWORK_ID_POS          (1u)
#define MIRROR_DESTCHANNELCAN_STATUS_NETWORK_STATE_POS       (2u)
#define MIRROR_DESTCHANNELCAN_STATUS_FRAME_ID_POS            (3u)
#define MIRROR_DESTCHANNELCAN_STATUS_FRAME_LOST_VALUE        (0x80u)

/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/
#define MIRROR_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e{451} */

/*! Message queue of the destination channel CAN. */
MIRROR_LOCAL VAR(Mirror_Queue, MIRROR_VAR_NOINIT) Mirror_DestChannelCan_Queue;

/*! Number of lost CAN frames. */
MIRROR_LOCAL VAR(boolean, MIRROR_VAR_NOINIT) Mirror_DestChannelCan_FrameLost;

/*! General state of the Mirror module. */
MIRROR_LOCAL VAR(Mirror_GeneralContextType*, MIRROR_VAR_NOINIT) Mirror_DestChannelCan_GeneralCtx;

#if ((MIRROR_DESTINATION_CHANNEL_CAN == STD_ON) && (MIRROR_STATUSCANIDOFDESTINATIONCHANNELCAN == STD_ON))
/*! Buffer for the status message. */
MIRROR_LOCAL VAR(uint8, MIRROR_VAR_NOINIT) Mirror_DestChannelCan_StatusFrameBuffer[MIRROR_DESTINATION_CHANNEL_CAN_QUEUE_ELEMENT_SIZE - MIRROR_DESTCHANNELCAN_QUEUE_CANID_LENGTH];

/*! Current write index of status message buffer */
MIRROR_LOCAL VAR(uint8, MIRROR_VAR_NOINIT) Mirror_DestChannelCan_StatusFrameBufferWriteIdx;
#endif /* ((MIRROR_DESTINATION_CHANNEL_CAN == STD_ON) && (MIRROR_STATUSCANIDOFDESTINATIONCHANNELCAN == STD_ON)) */

#define MIRROR_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e{451} */

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
/*================================================= MIRROR_START_SEC_CODE ===========================================*/
#define MIRROR_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e{451} */

#if (MIRROR_DESTINATION_CHANNEL_CAN == STD_ON)
/**********************************************************************************************************************
 *  Mirror_DestChannelCan_QueueInit()
 *********************************************************************************************************************/
/*! \brief       Function to initialize the queue
 *  \details     Function initialize a CAN queue.
 *  \pre         Module is initialized.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      This service is only available if MIRROR_DESTINATION_CHANNEL_CAN == STD_ON.
 *********************************************************************************************************************/
MIRROR_LOCAL_INLINE FUNC(void, MIRROR_CODE) Mirror_DestChannelCan_QueueInit(void);
#endif /* (MIRROR_DESTINATION_CHANNEL_CAN == STD_ON) */

#if (MIRROR_DESTINATION_CHANNEL_CAN == STD_ON)
/**********************************************************************************************************************
 *  Mirror_DestChannelCan_QueueRead()
 *********************************************************************************************************************/
/*! \brief         Function to read one element from the CAN queue.
 *  \details       -
 *  \param[in]     data   Buffer for the data to read of the queue.
 *  \param[in,out] length Length of the buffer/Length of the data.
 *  \param[in]     canID  CAN ID.
 *  \return        E_OK: A element from the queue is returned
 *  \return        E_NOT_OK: Queue read failed.
 *  \pre           Module is initialized.
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \config        This service is only available if MIRROR_DESTINATION_CHANNEL_CAN == STD_ON.
 *********************************************************************************************************************/
MIRROR_LOCAL_INLINE FUNC(Std_ReturnType, MIRROR_CODE) Mirror_DestChannelCan_QueueRead(uint8* data, uint16* length, uint32* canID);
#endif /* (MIRROR_DESTINATION_CHANNEL_CAN == STD_ON) */

#if (MIRROR_DESTINATION_CHANNEL_CAN == STD_ON)
/**********************************************************************************************************************
 *  Mirror_DestChannelCan_QueueWrite()
 *********************************************************************************************************************/
/*! \brief       Function to store data in the CAN queue.
 *  \details     -
 *  \param[in]   data    The data to store in the queue.
 *  \param[in]   length  Length of the data.
 *  \param[in]   canID   CAN Id.
 *  \return      E_OK: Data are written to the queue.
 *  \return      E_NOT_OK: Write operation failed.
 *  \pre         Module is initialized.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      This service is only available if MIRROR_DESTINATION_CHANNEL_CAN == STD_ON.
 *********************************************************************************************************************/
MIRROR_LOCAL_INLINE FUNC(Std_ReturnType, MIRROR_CODE) Mirror_DestChannelCan_QueueWrite(const uint8* data, uint16 length, const uint32* canID);
#endif /* (MIRROR_DESTINATION_CHANNEL_CAN == STD_ON) */

#if (MIRROR_DESTINATION_CHANNEL_CAN == STD_ON)
/**********************************************************************************************************************
 *  Mirror_DestChannelCan_QueueIsEmpty()
 *********************************************************************************************************************/
/*! \brief       Function that indicates if the queue is empty.
 *  \details     -
 *  \return      TRUE: The queue is empty.
 *  \return      FALSE: The queue is not empty.
 *  \pre         Module is initialized.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      This service is only available if MIRROR_DESTINATION_CHANNEL_CAN == STD_ON.
 *********************************************************************************************************************/
MIRROR_LOCAL_INLINE FUNC(boolean, MIRROR_CODE) Mirror_DestChannelCan_QueueIsEmpty(void);
#endif /* (MIRROR_DESTINATION_CHANNEL_CAN == STD_ON) */

#if (MIRROR_DESTINATION_CHANNEL_CAN == STD_ON)
/**********************************************************************************************************************
 *  Mirror_DestChannelCan_QueueTransmit()
 *********************************************************************************************************************/
/*! \brief       Function transmits a frame of the CAN queue.
 *  \details     Function read the next element to send from the queue and triggers the send function.
 *  \return      E_OK - success
 *  \return      E_NOT_OK - function has been called with invalid parameters.
 *  \pre         Module is initialized.
 *  \context     ISR
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      This service is only available if MIRROR_DESTINATION_CHANNEL_CAN == STD_ON.
 *********************************************************************************************************************/
MIRROR_LOCAL_INLINE FUNC(Std_ReturnType, MIRROR_CODE) Mirror_DestChannelCan_QueueTransmit(void);
#endif /* (MIRROR_DESTINATION_CHANNEL_CAN == STD_ON) */

#if (MIRROR_DESTINATION_CHANNEL_CAN == STD_ON)
/**********************************************************************************************************************
 *  Mirror_DestChannelCan_DirectTransmit()
 *********************************************************************************************************************/
/*! \brief       Fast transmit function for CAN - CAN mirroring.
 *  \details     Function is used when queuing is not necessary.
 *  \param[in]   canId        CAN ID of the CAn frame.
 *  \param[in]   length       Length of the CAn frame.
 *  \param[in]   payload      Content of the CAN frame.
 *  \return      E_NOT_OK - function has been called with invalid parameters.
 *  \return      E_OK - success
 *  \pre         Module is initialized.
 *  \context     ISR
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      This service is only available if MIRROR_DESTINATION_CHANNEL_CAN == STD_ON.
 *********************************************************************************************************************/
MIRROR_LOCAL_INLINE FUNC(Std_ReturnType, MIRROR_CODE) Mirror_DestChannelCan_DirectTransmit(Can_IdType canId, uint8 length, const uint8* payload);
#endif

#if ((MIRROR_DESTINATION_CHANNEL_CAN == STD_ON) && (MIRROR_STATUSCANIDOFDESTINATIONCHANNELCAN == STD_ON))
/**********************************************************************************************************************
 * Mirror_DestChannelCan_StatusMessageQueueNewStatusFrame()
 **********************************************************************************************************************/
/*! \brief       Functions queues a new status frame
 *  \details     -
 *  \pre         Module is initialized.
 *  \context     ISR
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      This service is only available if MIRROR_DESTINATION_CHANNEL_CAN == STD_ON and 
 *               MIRROR_STATUSCANIDOFDESTINATIONCHANNELCAN == STD_ON.
 *********************************************************************************************************************/
MIRROR_LOCAL_INLINE FUNC(void, MIRROR_CODE) Mirror_DestChannelCan_StatusMessageQueueNewStatusFrame(void);
#endif /* ((MIRROR_DESTINATION_CHANNEL_CAN == STD_ON) && (MIRROR_STATUSCANIDOFDESTINATIONCHANNELCAN == STD_ON)) */

#if ((MIRROR_DESTINATION_CHANNEL_CAN == STD_ON) && (MIRROR_STATUSCANIDOFDESTINATIONCHANNELCAN == STD_ON))
/**********************************************************************************************************************
 * Mirror_DestChannelCan_StatusMessageProcessSourceChannelState()
 **********************************************************************************************************************/
/*! \brief         Function add a new source channel status to the current status frame buffer
 *  \details       -
 *  \param[in]     newStatusBuffer              New status
 *  \param[in]     newStatusLength              Length of the new status
 *  \pre           Module is initialized.
 *  \context       ISR
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \config        This service is only available if MIRROR_DESTINATION_CHANNEL_CAN == STD_ON and
 *                 MIRROR_STATUSCANIDOFDESTINATIONCHANNELCAN == STD_ON.
 *********************************************************************************************************************/
MIRROR_LOCAL_INLINE FUNC(void, MIRROR_CODE) Mirror_DestChannelCan_StatusMessageProcessSourceChannelState(uint8* newStatusBuffer, uint8 newStatusLength);
#endif /* ((MIRROR_DESTINATION_CHANNEL_CAN == STD_ON) && (MIRROR_STATUSCANIDOFDESTINATIONCHANNELCAN == STD_ON)) */

#if ((MIRROR_DESTINATION_CHANNEL_CAN == STD_ON) && ((MIRROR_SOURCE_CHANNEL_CAN == STD_ON) || (MIRROR_SOURCE_CHANNEL_LIN == STD_ON)))
/**********************************************************************************************************************
 *  Mirror_DestChannelCan_ProcessFrame()
 *********************************************************************************************************************/
/*! \brief       Handles the CAN destination channel specific actions to process the incoming CAN or LIN frame.
 *  \details     Function is only called for frames that passed the filter.
 *  \param[in]   frameId      ID of the frame.
 *  \param[in]   length       Length of the frame.
 *  \param[in]   payload      Content of the frame.
 *  \return      E_OK: The frame was successful queued or transmitted.
 *  \return      E_NOT_OK: The frame is lost.
 *  \pre         Module is initialized.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      This service is only available if MIRROR_DESTINATION_CHANNEL_CAN == STD_ON and 
 *               MIRROR_SOURCE_CHANNEL_CAN == STD_ON or MIRROR_SOURCE_CHANNEL_LIN == STD_ON.
 *********************************************************************************************************************/
FUNC(Std_ReturnType, MIRROR_CODE) Mirror_DestChannelCan_ProcessFrame(uint32 frameId, uint8 length, const uint8* payload);
#endif /* ((MIRROR_DESTINATION_CHANNEL_CAN == STD_ON) && ((MIRROR_SOURCE_CHANNEL_CAN == STD_ON) || (MIRROR_SOURCE_CHANNEL_LIN == STD_ON))) */

#define MIRROR_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e{451} */
/*================================================= MIRROR_STOP_SEC_CODE ============================================*/
/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/
/*================================================= MIRROR_START_SEC_CODE ===========================================*/
#define MIRROR_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e{451} */

#if (MIRROR_DESTINATION_CHANNEL_CAN == STD_ON)
/**********************************************************************************************************************
 *  Mirror_DestChannelCan_QueueInit()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
MIRROR_LOCAL_INLINE FUNC(void, MIRROR_CODE) Mirror_DestChannelCan_QueueInit(void)
{
  Mirror_DestinationChannelCanIdxOfDestComMChannelType channelIndex = Mirror_GetDestinationChannelCanIdxOfDestComMChannel(Mirror_DestChannelCan_GeneralCtx->CurrentDestChannelIndex);

  uint8* queueBuffer = &Mirror_GetDestinationQueueBuffer(MIRROR_DESTCHANNELCAN_QUEUE_FIRST_BYTE_POS);
  uint16 queueElementCount = Mirror_GetQueueSizeOfDestinationChannelCan(channelIndex);
  uint8 queueElementLength = (uint8)Mirror_GetTxPduLengthOfDestinationChannelCan(channelIndex) + MIRROR_DESTCHANNELCAN_QUEUE_CANID_LENGTH;

  /* #10 Trigger the initialization of the queue with the element count and length of the current destination channel. */
  Mirror_QueueInit(&Mirror_DestChannelCan_Queue, queueBuffer, queueElementCount, (uint16)queueElementLength);
} /* Mirror_DestChannelCan_QueueInit() */
#endif /* (MIRROR_DESTINATION_CHANNEL_CAN == STD_ON) */

#if (MIRROR_DESTINATION_CHANNEL_CAN == STD_ON)
/**********************************************************************************************************************
 *  Mirror_DestChannelCan_QueueRead()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 */
MIRROR_LOCAL_INLINE FUNC(Std_ReturnType, MIRROR_CODE) Mirror_DestChannelCan_QueueRead(uint8* data, uint16* length, uint32* canID)
{
  Std_ReturnType retVal;

  /* #10 Trigger the queue read operation of the next element for transmission. */
  retVal = Mirror_QueueRead(&Mirror_DestChannelCan_Queue, data, length);

  /* #20 If the read operation was successful, extract the CAN Id. */
  if(retVal == E_OK)
  {
    (*length) -= MIRROR_DESTCHANNELCAN_QUEUE_CANID_LENGTH;

    VStdLib_MemCpy(canID, &data[(*length)], MIRROR_DESTCHANNELCAN_QUEUE_CANID_LENGTH); /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */

    retVal = E_OK;
  }

  return retVal;
} /* Mirror_DestChannelCan_QueueRead() */
#endif /* (MIRROR_DESTINATION_CHANNEL_CAN == STD_ON) */

#if (MIRROR_DESTINATION_CHANNEL_CAN == STD_ON)
/**********************************************************************************************************************
 *  Mirror_DestChannelCan_QueueWrite()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 */
MIRROR_LOCAL_INLINE FUNC(Std_ReturnType, MIRROR_CODE) Mirror_DestChannelCan_QueueWrite(const uint8* data, uint16 length, const uint32* canID)
{
  uint8 queueElement[MIRROR_DESTINATION_CHANNEL_CAN_QUEUE_ELEMENT_SIZE];

  /* #10 Join the given data and CAN Id into one data buffer. */
  VStdLib_MemCpy(queueElement, data, length); /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */
  VStdLib_MemCpy(&queueElement[length], canID, MIRROR_DESTCHANNELCAN_QUEUE_CANID_LENGTH); /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */

  /* #20 Trigger the queue write operation for the given data. */
  return Mirror_QueueWrite(&Mirror_DestChannelCan_Queue, queueElement, (length + MIRROR_DESTCHANNELCAN_QUEUE_CANID_LENGTH), TRUE, MIRROR_DESTCHANNELCAN_QUEUE_WRITEOFFSET_UNUSED);
} /* Mirror_DestChannelCan_QueueWrite() */
#endif /* (MIRROR_DESTINATION_CHANNEL_CAN == STD_ON) */

#if (MIRROR_DESTINATION_CHANNEL_CAN == STD_ON)
/**********************************************************************************************************************
 *  Mirror_DestChannelCan_QueueIsEmpty()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
MIRROR_LOCAL_INLINE FUNC(boolean, MIRROR_CODE) Mirror_DestChannelCan_QueueIsEmpty(void)
{
  /* #10 Trigger the check if the queue is empty. */
  return Mirror_QueueIsEmpty(&Mirror_DestChannelCan_Queue);
} /* Mirror_DestChannelCan_QueueIsEmpty() */
#endif /* (MIRROR_DESTINATION_CHANNEL_CAN == STD_ON) */

#if (MIRROR_DESTINATION_CHANNEL_CAN == STD_ON)
/**********************************************************************************************************************
 * Mirror_DestChannelCan_QueueTransmit()
 **********************************************************************************************************************/
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
 *
 *
 *
 *
 *
 */
MIRROR_LOCAL_INLINE FUNC(Std_ReturnType, MIRROR_CODE) Mirror_DestChannelCan_QueueTransmit(void)
{
  Std_ReturnType retVal = E_NOT_OK;
  uint8* messageBuffer = &Mirror_GetDestinationChannelCanTransmitBuffer(0);

  /* #10 If the transmission PDU of the current destination channel is free to use: */
  if(Mirror_DestChannelCan_GeneralCtx->DestChannel_TxPduLocked == FALSE)
  {
    PduInfoType pdu;
    uint32 canId;
    Mirror_DestinationChannelCanIdxOfDestComMChannelType destChannelIndex;

    /* #20 Enter MIRROR_EXCLUSIVE_AREA_QUEUE. */
    SchM_Enter_Mirror_MIRROR_EXCLUSIVE_AREA_QUEUE();

    destChannelIndex = Mirror_GetDestinationChannelCanIdxOfDestComMChannel(Mirror_DestChannelCan_GeneralCtx->CurrentDestChannelIndex);

    /* #30 If the current destination channel uses trigger transmit: */
#if(MIRROR_USESTRIGGERTRANSMITOFDESTINATIONCHANNELCAN == STD_ON)
    if(Mirror_IsUsesTriggerTransmitOfDestinationChannelCan(destChannelIndex))  /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */
    {
      pdu.SduDataPtr = NULL_PTR;

      /* #40 If the queue contains data: */
      if(Mirror_DestChannelCan_QueueIsEmpty() == FALSE)
      {
        /* #50 Set the queue element length to the transmission PDU struct. */
        pdu.SduLength = Mirror_GetTxPduLengthOfDestinationChannelCan(destChannelIndex);

        retVal = E_OK;
      }
    }
    else
#endif
    /* #60 Otherwise, use direct transmit:  */
    {
      uint16 messageBufferLength = (uint16)Mirror_GetSizeOfDestinationChannelCanTransmitBuffer();

      pdu.SduDataPtr = (SduDataPtrType) messageBuffer;

      /* #70 Try to get data for transmission by triggering a read operation of the queue. */
      retVal = Mirror_DestChannelCan_QueueRead(messageBuffer, &messageBufferLength, &canId);

      pdu.SduLength = messageBufferLength;

      /* #80 If the read operation was successful, trigger the CanIf to update the CAN Id of the dynamic transmission PDU. */
      if(retVal == E_OK)
      {
        CanIf_SetDynamicTxId(Mirror_GetCanTxPduIdOfDestinationChannelCan(destChannelIndex), (Can_IdType)canId);
      }
    }

    /* #90 Leave MIRROR_EXCLUSIVE_AREA_QUEUE. */
    SchM_Exit_Mirror_MIRROR_EXCLUSIVE_AREA_QUEUE();

    /* #100 If there is a queue element that is ready for transmission: */
    if(retVal == E_OK)
    {
      /* #110 Trigger the transmission. */
      retVal = Mirror_DestChannel_Transmit(Mirror_DestChannelCan_GeneralCtx, &pdu, Mirror_GetPduRTxPduIdOfDestinationChannelCan(destChannelIndex));

      /* #120 If the transmission was not successful, set the frame lost flag. */
      if(retVal == E_NOT_OK)
      {
        Mirror_DestChannelCan_FrameLost = TRUE;
      }
    }
    /* #130 Otherwise, do nothing and return success. */
    else
    {
      retVal = E_OK;
    }
  }

  return retVal;
} /* Mirror_DestChannelCan_QueueTransmit() */
#endif /* (MIRROR_DESTINATION_CHANNEL_CAN == STD_ON) */

#if (MIRROR_DESTINATION_CHANNEL_CAN == STD_ON)
/**********************************************************************************************************************
 * Mirror_DestChannelCan_DirectTransmit()
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
MIRROR_LOCAL_INLINE FUNC(Std_ReturnType, MIRROR_CODE) Mirror_DestChannelCan_DirectTransmit(Can_IdType canId, uint8 length, const uint8* payload)
{
  Std_ReturnType retVal;
  PduInfoType mirror_CanPdu;
  uint8* messageBuffer = &Mirror_GetDestinationChannelCanTransmitBuffer(0u);
  Mirror_DestinationChannelCanIdxOfDestComMChannelType destChannelIndex = Mirror_GetDestinationChannelCanIdxOfDestComMChannel(Mirror_DestChannelCan_GeneralCtx->CurrentDestChannelIndex);

  /* #10 Set the data and length to the transmission PDU for the direct transmission. */
  VStdLib_MemCpy(messageBuffer, payload, length); /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */

  mirror_CanPdu.SduDataPtr = messageBuffer;
  mirror_CanPdu.SduLength = length;

  /* #20 Trigger the CanIf to update the CAN Id of the dynamic transmission PDU. */
  CanIf_SetDynamicTxId(Mirror_GetCanTxPduIdOfDestinationChannelCan(destChannelIndex), canId);

  /* #30 Trigger the transmission. */
  retVal = Mirror_DestChannel_Transmit(Mirror_DestChannelCan_GeneralCtx, &mirror_CanPdu, Mirror_GetPduRTxPduIdOfDestinationChannelCan(destChannelIndex));

  /* #40 If the transmission was not successful, set the frame lost flag. */
  if(retVal == E_NOT_OK)
  {
    Mirror_DestChannelCan_FrameLost = TRUE;
  }

  return retVal;
} /* Mirror_DestChannelCan_DirectTransmit() */
#endif /* (MIRROR_DESTINATION_CHANNEL_CAN == STD_ON) */

#if ((MIRROR_DESTINATION_CHANNEL_CAN == STD_ON) && (MIRROR_STATUSCANIDOFDESTINATIONCHANNELCAN == STD_ON))
/**********************************************************************************************************************
 * Mirror_DestChannelCan_StatusMessageQueueNewStatusFrame()
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
MIRROR_LOCAL_INLINE FUNC(void, MIRROR_CODE) Mirror_DestChannelCan_StatusMessageQueueNewStatusFrame(void)
{
  /* #10 Get the current destination channel. */
  Mirror_DestinationChannelCanIdxOfDestComMChannelType destChannelIndex = Mirror_GetDestinationChannelCanIdxOfDestComMChannel(Mirror_DestChannelCan_GeneralCtx->CurrentDestChannelIndex);

  /* #20 Get the CAN Id for the status message of the current destination channel. */
  uint32 canId = Mirror_GetStatusCanIdOfDestinationChannelCan(destChannelIndex);

  /* #30 Enter MIRROR_EXCLUSIVE_AREA_QUEUE. */
  SchM_Enter_Mirror_MIRROR_EXCLUSIVE_AREA_QUEUE();

  /* #40 Trigger the queuing of the current status frame and the corresponding CAN Id. */
  (void)Mirror_DestChannelCan_QueueWrite(Mirror_DestChannelCan_StatusFrameBuffer, Mirror_DestChannelCan_StatusFrameBufferWriteIdx, &canId);

  /* #50 Leave MIRROR_EXCLUSIVE_AREA_QUEUE. */
  SchM_Exit_Mirror_MIRROR_EXCLUSIVE_AREA_QUEUE();
} /* Mirror_DestChannelCan_StatusMessageQueueNewStatusFrame() */
#endif /* ((MIRROR_DESTINATION_CHANNEL_CAN == STD_ON) && (MIRROR_STATUSCANIDOFDESTINATIONCHANNELCAN == STD_ON)) */

#if ((MIRROR_DESTINATION_CHANNEL_CAN == STD_ON) && (MIRROR_STATUSCANIDOFDESTINATIONCHANNELCAN == STD_ON))
/**********************************************************************************************************************
 * Mirror_DestChannelCan_StatusMessageProcessSourceChannelState()
 **********************************************************************************************************************/
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
 */
MIRROR_LOCAL_INLINE FUNC(void, MIRROR_CODE) Mirror_DestChannelCan_StatusMessageProcessSourceChannelState(uint8* newStatusBuffer, uint8 newStatusLength)
{
  /* #10 Get the current destination channel. */
  Mirror_DestinationChannelCanIdxOfDestComMChannelType destChannelIndex = Mirror_GetDestinationChannelCanIdxOfDestComMChannel(Mirror_DestChannelCan_GeneralCtx->CurrentDestChannelIndex);

  /* #20 If the current destination channel supports the status message: */
  if(Mirror_GetStatusCanIdOfDestinationChannelCan(destChannelIndex) != MIRROR_NO_STATUSCANIDOFDESTINATIONCHANNELCAN)
  {
    if(newStatusLength > 0u)
    {
      /* #30 If the given source channel state can not be added to the current status message */
      if (((Mirror_DestChannelCan_StatusFrameBufferWriteIdx) + newStatusLength) > (uint8)Mirror_GetTxPduLengthOfDestinationChannelCan(destChannelIndex))
      {
        /* #40 Trigger the queue write operation for the current status frame */
        Mirror_DestChannelCan_StatusMessageQueueNewStatusFrame();

        Mirror_DestChannelCan_StatusFrameBufferWriteIdx = MIRROR_DESTCHANNELCAN_STATUS_FRAME_HEADER_LENGTH;
      }

      /* #50 If the queue write operation was not successful, add the frame lost bit to the new status message */
      if(Mirror_DestChannelCan_FrameLost == TRUE)
      {
        newStatusBuffer[MIRROR_DESTCHANNELCAN_STATUS_META_DATA_POS] |= MIRROR_DESTCHANNELCAN_STATUS_FRAME_LOST_VALUE;

        Mirror_DestChannelCan_FrameLost = FALSE;
      }

      /* #60 Add the given source channel state to the new status message. */
      VStdLib_MemCpy(&Mirror_DestChannelCan_StatusFrameBuffer[Mirror_DestChannelCan_StatusFrameBufferWriteIdx], newStatusBuffer, newStatusLength); /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */

      Mirror_DestChannelCan_StatusFrameBufferWriteIdx += newStatusLength;
    }
  }
} /* Mirror_DestChannelCan_StatusMessageProcessSourceChannelState() */
#endif /* ((MIRROR_DESTINATION_CHANNEL_CAN == STD_ON) && (MIRROR_STATUSCANIDOFDESTINATIONCHANNELCAN == STD_ON)) */

#if ((MIRROR_DESTINATION_CHANNEL_CAN == STD_ON) && ((MIRROR_SOURCE_CHANNEL_CAN == STD_ON) || (MIRROR_SOURCE_CHANNEL_LIN == STD_ON)))
/**********************************************************************************************************************
 *  Mirror_DestChannelCan_ProcessFrame()
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
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, MIRROR_CODE) Mirror_DestChannelCan_ProcessFrame(uint32 frameId, uint8 length, const uint8* payload)
{
  Std_ReturnType retVal = E_NOT_OK;
  NetworkHandleType destChannelIndex;
  uint32 id = frameId;

  /* #10 Enter MIRROR_EXCLUSIVE_AREA_QUEUE. */
  SchM_Enter_Mirror_MIRROR_EXCLUSIVE_AREA_QUEUE();

  destChannelIndex = Mirror_DestChannelCan_GeneralCtx->CurrentDestChannelIndex;

  /* #20 If the incoming data length is not to big: */
  if(length <= Mirror_GetTxPduLengthOfDestinationChannelCan(Mirror_GetDestinationChannelCanIdxOfDestComMChannel(destChannelIndex)))
  {
    /* #30 If the current destination channel uses trigger transmit: */
#if(MIRROR_USESTRIGGERTRANSMITOFDESTINATIONCHANNELCAN == STD_ON)
    if(Mirror_IsUsesTriggerTransmitOfDestinationChannelCan(Mirror_GetDestinationChannelCanIdxOfDestComMChannel(destChannelIndex))) /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */
    {
      /* #40 Trigger the queue write operation for the given CAN frame. */
      retVal = Mirror_DestChannelCan_QueueWrite(payload, length, &id);

      /* #50 Leave MIRROR_EXCLUSIVE_AREA_QUEUE. */
      SchM_Exit_Mirror_MIRROR_EXCLUSIVE_AREA_QUEUE();
    }
    else
#endif
    /* #60 Otherwise */
    {
      boolean isQueueEmpty = Mirror_DestChannelCan_QueueIsEmpty();

      /* #70 If the queue is empty and the transmission PDU is free for use: */
      if((Mirror_DestChannelCan_GeneralCtx->DestChannel_TxPduLocked == FALSE) && (isQueueEmpty == TRUE))
      {
        /* #80 Leave MIRROR_EXCLUSIVE_AREA_QUEUE. */
        SchM_Exit_Mirror_MIRROR_EXCLUSIVE_AREA_QUEUE();

        /* #90 Trigger the direct transmission of the given CAN frame without queuing. */
        retVal = Mirror_DestChannelCan_DirectTransmit((Can_IdType)id, length, payload);
      }
      /* #100 Otherwise: */
      else
      {
        /* #110 Trigger the queue write operation for the given CAN frame. */
        retVal = Mirror_DestChannelCan_QueueWrite(payload, length, &id);

        /* #120 Leave MIRROR_EXCLUSIVE_AREA_QUEUE. */
        SchM_Exit_Mirror_MIRROR_EXCLUSIVE_AREA_QUEUE();
      }
    }

    /* #130 If the given CAN frame can not be processed, set the frame lost flag. */
    if(retVal == E_NOT_OK)
    {
      Mirror_DestChannelCan_FrameLost = TRUE;
    }
  }
  /* #140 Otherwise, leave MIRROR_EXCLUSIVE_AREA_QUEUE. */
  else
  {
    SchM_Exit_Mirror_MIRROR_EXCLUSIVE_AREA_QUEUE();
  }

  return retVal;
}
#endif /* ((MIRROR_DESTINATION_CHANNEL_CAN == STD_ON) && ((MIRROR_SOURCE_CHANNEL_CAN == STD_ON) || (MIRROR_SOURCE_CHANNEL_LIN == STD_ON))) */

#define MIRROR_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e{451} */
/*================================================= MIRROR_STOP_SEC_CODE ============================================*/
/**********************************************************************************************************************
 *  GLOBAL FUNCTION
 *********************************************************************************************************************/
/*================================================= MIRROR_START_SEC_CODE ===========================================*/
#define MIRROR_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e{451} */

#if (MIRROR_DESTINATION_CHANNEL_CAN == STD_ON)
/**********************************************************************************************************************
 * Mirror_DestChannelCan_Init()
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, MIRROR_CODE) Mirror_DestChannelCan_Init(Mirror_GeneralContextType* mirrorCtx)
{
  /* #10 Initialize the general configuration of the destination channel. */
  Mirror_DestChannelCan_GeneralCtx = mirrorCtx;

  Mirror_DestChannelCan_GeneralCtx->DestChannel_TxPduLocked = FALSE;
  Mirror_DestChannelCan_FrameLost = FALSE;

#if (MIRROR_STATUSCANIDOFDESTINATIONCHANNELCAN == STD_ON)
  Mirror_DestChannelCan_StatusFrameBuffer[MIRROR_DESTCHANNELCAN_STATUS_FRAME_HEADER_POS] = MIRROR_STATUS_PROTOCOL_VERSION;
  Mirror_DestChannelCan_StatusFrameBufferWriteIdx = MIRROR_DESTCHANNELCAN_STATUS_FRAME_HEADER_LENGTH;
#endif /* (MIRROR_STATUSCANIDOFDESTINATIONCHANNELCAN == STD_ON) */

  /* #20 Trigger the initialization of the queue. */
  Mirror_DestChannelCan_QueueInit();
} /* Mirror_DestChannelCan_Init() */
#endif /* (MIRROR_DESTINATION_CHANNEL_CAN == STD_ON) */

#if (MIRROR_DESTINATION_CHANNEL_CAN == STD_ON)
/**********************************************************************************************************************
 *  Mirror_DestChannelCan_MainFunction()
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
 *
 *
 *
 *
 */
FUNC(void, MIRROR_CODE) Mirror_DestChannelCan_MainFunction(void)
{
  /* #10 Enter MIRROR_EXCLUSIVE_AREA_TXPDU. */
  SchM_Enter_Mirror_MIRROR_EXCLUSIVE_AREA_TXPDU();

  /* #20 If a transmission is in progress: */
  if(Mirror_DestChannelCan_GeneralCtx->DestChannel_TxPduLocked == TRUE)
  {
    /* #30 Update the TxConfirmation timeout timer */
    --Mirror_DestChannelCan_GeneralCtx->TxConfTimeout;

    /* #40 If the TxConfirmation timeout has expired: */
    if(Mirror_DestChannelCan_GeneralCtx->TxConfTimeout == 0u)
    {
      /* #50 Release the lock of the transmission PDU and set the frame lost flag. */
      Mirror_DestChannelCan_GeneralCtx->DestChannel_TxPduLocked = FALSE;

      Mirror_DestChannelCan_FrameLost = TRUE;

      /* #60 Leave MIRROR_EXCLUSIVE_AREA_TXPDU. */
      SchM_Exit_Mirror_MIRROR_EXCLUSIVE_AREA_TXPDU();

# if (MIRROR_RUNTIME_ERROR_REPORT == STD_ON)
      (void)Det_ReportRuntimeError(MIRROR_MODULE_ID, MIRROR_INSTANCE_ID_DET, MIRROR_SID_MAINFUNCTION, MIRROR_E_TRANSMIT_FAILED);
# endif
    }
    /* #70 Otherwise, leave MIRROR_EXCLUSIVE_AREA_TXPDU. */
    else
    {
      SchM_Exit_Mirror_MIRROR_EXCLUSIVE_AREA_TXPDU();
    }
  }
  /* #80 Otherwise: */
  else
  {
    Std_ReturnType retVal;

    /* #90 Leave MIRROR_EXCLUSIVE_AREA_TXPDU. */
    SchM_Exit_Mirror_MIRROR_EXCLUSIVE_AREA_TXPDU();

    /* #100 Trigger the transmission of the next queued message. */
    retVal = Mirror_DestChannelCan_QueueTransmit();

    if(retVal == E_NOT_OK)
    {
# if (MIRROR_RUNTIME_ERROR_REPORT == STD_ON)
      (void)Det_ReportRuntimeError(MIRROR_MODULE_ID, MIRROR_INSTANCE_ID_DET, MIRROR_SID_MAINFUNCTION, MIRROR_E_TRANSMIT_FAILED);
# endif
    }
  }

#if (MIRROR_STATUSCANIDOFDESTINATIONCHANNELCAN == STD_ON)
  /* #110 If there is a source channel state in the current status frame buffer,
   *      trigger the queue write operation for the current status frame buffer.  */
  if (Mirror_DestChannelCan_StatusFrameBufferWriteIdx > 1u)
  {
    Mirror_DestChannelCan_StatusMessageQueueNewStatusFrame();

    Mirror_DestChannelCan_StatusFrameBufferWriteIdx = MIRROR_DESTCHANNELCAN_STATUS_FRAME_HEADER_LENGTH;
  }
#endif
} /* Mirror_DestChannelCan_MainFunction() */
#endif /* (MIRROR_DESTINATION_CHANNEL_CAN == STD_ON) */

#if ((MIRROR_DESTINATION_CHANNEL_CAN == STD_ON) && (MIRROR_SOURCE_CHANNEL_CAN == STD_ON))
/**********************************************************************************************************************
 *  Mirror_DestChannelCan_ProcessCanFrame()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, MIRROR_CODE) Mirror_DestChannelCan_ProcessCanFrame(Can_IdType canId, uint8 length, const uint8* payload)
{
  uint32 id = (uint32)canId;

  /* #10 Trigger the processing of the incoming CAN frame. */
  return Mirror_DestChannelCan_ProcessFrame(id, length, payload);
} /* Mirror_DestChannelCan_ProcessCanFrame() */
#endif /* ((MIRROR_DESTINATION_CHANNEL_CAN == STD_ON) && ((MIRROR_SOURCE_CHANNEL_CAN == STD_ON) || (MIRROR_SOURCE_CHANNEL_LIN == STD_ON))) */

#if ((MIRROR_DESTINATION_CHANNEL_CAN == STD_ON) && (MIRROR_SOURCE_CHANNEL_CAN == STD_ON))
/**********************************************************************************************************************
* Mirror_DestChannelCan_ProcessCanStatus()
**********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, MIRROR_CODE) Mirror_DestChannelCan_ProcessCanStatus(uint8 metaData, uint8 networkId, uint8 networkState)
{
#if (MIRROR_STATUSCANIDOFDESTINATIONCHANNELCAN == STD_ON)
  /* #10 Create a new source channel state according to the AUTOSAR protocol. */
  uint8 newStatusBuffer[MIRROR_DESTCHANNELCAN_STATUE_FRAME_LENGTH] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

  newStatusBuffer[MIRROR_DESTCHANNELCAN_STATUS_META_DATA_POS] = metaData;
  newStatusBuffer[MIRROR_DESTCHANNELCAN_STATUS_NETWORK_ID_POS] = networkId;
  newStatusBuffer[MIRROR_DESTCHANNELCAN_STATUS_NETWORK_STATE_POS] = networkState;

  /* #20 Trigger the write operation into the current status frame buffer. */
  Mirror_DestChannelCan_StatusMessageProcessSourceChannelState(newStatusBuffer, MIRROR_DESTCHANNELCAN_CAN_STATUS_LENGTH);
#else
  MIRROR_DUMMY_STATEMENT(metaData); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  MIRROR_DUMMY_STATEMENT(networkId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  MIRROR_DUMMY_STATEMENT(networkState); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
#endif
}
#endif /* ((MIRROR_DESTINATION_CHANNEL_CAN == STD_ON) && (MIRROR_SOURCE_CHANNEL_CAN == STD_ON)) */

#if ((MIRROR_DESTINATION_CHANNEL_CAN == STD_ON) && (MIRROR_SOURCE_CHANNEL_LIN == STD_ON))
/**********************************************************************************************************************
 *  Mirror_DestChannelCan_ProcessLinFrame()
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
FUNC(Std_ReturnType, MIRROR_CODE) Mirror_DestChannelCan_ProcessLinFrame(uint8 linId, uint32 canId, uint8 length, const uint8* payload,
                                                                        uint8 metaData, uint8 networkId, uint8 networkState)
{
  Std_ReturnType retVal = E_NOT_OK;

  /* #10 If a LIN frame without error is given, trigger the processing of it. */
  if(length > 0u)
  {
    retVal = Mirror_DestChannelCan_ProcessFrame(canId, length, payload);
  }
#if (MIRROR_STATUSCANIDOFDESTINATIONCHANNELCAN == STD_ON)
  /* #20 Otherwise: */
  else
  {
    NetworkHandleType currentDestChannelIndex;

    /* #30 Enter MIRROR_EXCLUSIVE_AREA_QUEUE. */
    SchM_Enter_Mirror_MIRROR_EXCLUSIVE_AREA_QUEUE();

    /* #40 Get the current destination channel. */
    currentDestChannelIndex = Mirror_DestChannelCan_GeneralCtx->CurrentDestChannelIndex;

    /* #50 Leave MIRROR_EXCLUSIVE_AREA_QUEUE. */
    SchM_Exit_Mirror_MIRROR_EXCLUSIVE_AREA_QUEUE();

    /* #60 If the current destination channel supports the statue message: */
    if(Mirror_GetStatusCanIdOfDestinationChannelCan(Mirror_GetDestinationChannelCanIdxOfDestComMChannel(currentDestChannelIndex)) != MIRROR_NO_STATUSCANIDOFDESTINATIONCHANNELCAN)
    {
      /* #70 Create a new source channel state according to the AUTOSAR protocol. */
      uint8 statusFrameBuffer[MIRROR_DESTCHANNELCAN_STATUE_FRAME_LENGTH];

      statusFrameBuffer[MIRROR_DESTCHANNELCAN_STATUS_HEADER_PROT_VERSION_POS] = MIRROR_STATUS_PROTOCOL_VERSION;
      statusFrameBuffer[MIRROR_DESTCHANNELCAN_STATUS_FRAME_HEADER_LENGTH + MIRROR_DESTCHANNELCAN_STATUS_META_DATA_POS] = metaData;
      statusFrameBuffer[MIRROR_DESTCHANNELCAN_STATUS_FRAME_HEADER_LENGTH + MIRROR_DESTCHANNELCAN_STATUS_NETWORK_ID_POS] = networkId;
      statusFrameBuffer[MIRROR_DESTCHANNELCAN_STATUS_FRAME_HEADER_LENGTH + MIRROR_DESTCHANNELCAN_STATUS_NETWORK_STATE_POS] = networkState;
      statusFrameBuffer[MIRROR_DESTCHANNELCAN_STATUS_FRAME_HEADER_LENGTH + MIRROR_DESTCHANNELCAN_STATUS_FRAME_ID_POS] = linId;

      /* #80 Trigger the processing of it. */
      retVal =  Mirror_DestChannelCan_ProcessFrame((uint32)Mirror_GetStatusCanIdOfDestinationChannelCan(Mirror_GetDestinationChannelCanIdxOfDestComMChannel(currentDestChannelIndex)),
                                                      (MIRROR_DESTCHANNELCAN_LIN_FRAME_STATUS_LENGTH + MIRROR_DESTCHANNELCAN_STATUS_FRAME_HEADER_LENGTH), statusFrameBuffer);
    }
  }
#else
  MIRROR_DUMMY_STATEMENT(linId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  MIRROR_DUMMY_STATEMENT(metaData); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  MIRROR_DUMMY_STATEMENT(networkId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  MIRROR_DUMMY_STATEMENT(networkState); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
#endif /* (MIRROR_STATUSCANIDOFDESTINATIONCHANNELCAN == STD_ON) */

  return retVal;
  /* PRQA S 6060 1 */ /* MD_MSR_STPAR */
} /* Mirror_DestChannelCan_ProcessLinFrame() */
#endif /* ((MIRROR_DESTINATION_CHANNEL_CAN == STD_ON) && (MIRROR_SOURCE_CHANNEL_LIN == STD_ON)) */

#if ((MIRROR_DESTINATION_CHANNEL_CAN == STD_ON) && (MIRROR_SOURCE_CHANNEL_LIN == STD_ON))
/**********************************************************************************************************************
* Mirror_DestChannelCan_ProcessLinStatus()
**********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, MIRROR_CODE) Mirror_DestChannelCan_ProcessLinStatus(uint8 metaData, uint8 networkId, uint8 networkState)
{
#if (MIRROR_STATUSCANIDOFDESTINATIONCHANNELCAN == STD_ON)
  /* #10 Create a new source channel state according to the AUTOSAR protocol. */
  uint8 newStatusBuffer[MIRROR_DESTCHANNELCAN_STATUE_FRAME_LENGTH] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

  newStatusBuffer[MIRROR_DESTCHANNELCAN_STATUS_META_DATA_POS] = metaData;
  newStatusBuffer[MIRROR_DESTCHANNELCAN_STATUS_NETWORK_ID_POS] = networkId;
  newStatusBuffer[MIRROR_DESTCHANNELCAN_STATUS_NETWORK_STATE_POS] = networkState;

  /* #20 Trigger the write operation into the current status frame buffer. */
  Mirror_DestChannelCan_StatusMessageProcessSourceChannelState(newStatusBuffer, MIRROR_DESTCHANNELCAN_LIN_STATUS_LENGTH);
#else
  MIRROR_DUMMY_STATEMENT(metaData); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  MIRROR_DUMMY_STATEMENT(networkId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  MIRROR_DUMMY_STATEMENT(networkState); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
#endif
}
#endif /* ((MIRROR_DESTINATION_CHANNEL_CAN == STD_ON) && (MIRROR_SOURCE_CHANNEL_LIN == STD_ON)) */

#if (MIRROR_DESTINATION_CHANNEL_CAN == STD_ON)
/**********************************************************************************************************************
 *  Mirror_DestChannelCan_TxConfirmation()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, MIRROR_CODE) Mirror_DestChannelCan_TxConfirmation(void)
{
  /* #10 Check if the Mirror module is initialized. */
  if(Mirror_DestChannelCan_GeneralCtx->GlobalMode == MIRROR_ACTIVE)
  {
    Std_ReturnType retVal;

    /* #20 Trigger the transmit of the next queued element. */
    retVal= Mirror_DestChannelCan_QueueTransmit();

    if(retVal == E_NOT_OK)
    {
# if (MIRROR_RUNTIME_ERROR_REPORT == STD_ON)
      (void)Det_ReportRuntimeError(MIRROR_MODULE_ID, MIRROR_INSTANCE_ID_DET, MIRROR_SID_TXCONFIRMATION, MIRROR_E_TRANSMIT_FAILED);
# endif
    }
  }
} /* Mirror_DestChannelCan_TxConfirmation() */
#endif /* (MIRROR_DESTINATION_CHANNEL_CAN == STD_ON) */

#if (MIRROR_DESTINATION_CHANNEL_CAN == STD_ON)
/**********************************************************************************************************************
 *  Mirror_DestChannelCan_TriggerTransmit()
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
FUNC(Std_ReturnType, MIRROR_CODE) Mirror_DestChannelCan_TriggerTransmit(PduInfoType* PduInfoPtr)
{
  Std_ReturnType retVal = E_NOT_OK;

  /* #10 Check if the Mirror module is initialized. */
  if(Mirror_DestChannelCan_GeneralCtx->GlobalMode == MIRROR_ACTIVE)
  {
    uint16 bufferLength = (uint16)Mirror_GetSizeOfDestinationChannelCanTransmitBuffer();
    uint8* messageBuffer = &Mirror_GetDestinationChannelCanTransmitBuffer(0u);
    uint32 canId;

    /* #20 Enter MIRROR_EXCLUSIVE_AREA_QUEUE. */
    SchM_Enter_Mirror_MIRROR_EXCLUSIVE_AREA_QUEUE();

    /* #30 Read the next element that is ready for transmission from the queue. */
    retVal = Mirror_DestChannelCan_QueueRead(messageBuffer, &bufferLength, &canId);

    /* #40 Leave MIRROR_EXCLUSIVE_AREA_QUEUE. */
    SchM_Exit_Mirror_MIRROR_EXCLUSIVE_AREA_QUEUE();

    /* #50 If the read operation was successful: */
    if(retVal == E_OK)
    {
      /* #60 If the given data buffer is big enough, copy the data. */
      if(PduInfoPtr->SduLength >= bufferLength)
      {
        VStdLib_MemCpy(PduInfoPtr->SduDataPtr, messageBuffer, bufferLength); /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */
        PduInfoPtr->SduLength = bufferLength;
      }
      /* #70 Otherwise, discard the data and set the frame lost flag. */
      else
      {
        Mirror_DestChannelCan_FrameLost = TRUE;
      }

      /* #80 Set the CAN Id for the transmission in CanIf. */
      CanIf_SetDynamicTxId(Mirror_GetCanTxPduIdOfDestinationChannelCan(Mirror_GetDestinationChannelCanIdxOfDestComMChannel(Mirror_DestChannelCan_GeneralCtx->CurrentDestChannelIndex)), (Can_IdType)canId);
    }
  }

  return retVal;
} /* Mirror_DestChannelCan_TriggerTransmit() */
#endif /* (MIRROR_DESTINATION_CHANNEL_CAN == STD_ON) */

#define MIRROR_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e{451} */
/*================================================= MIRROR_STOP_SEC_CODE ============================================*/
/**********************************************************************************************************************
 *  END OF FILE: Mirror_DestChannelCan.c
 *********************************************************************************************************************/
