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
/**     \file     Mirror_DestChannelIP.c
 *      \brief    Mirror IP destination channel source file
 *
 *      \details  Implementation of Mirror IP destination channel.
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
#define MIRROR_DESTCHANNELIP_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Mirror_DestChannelIP.h"
#include "Mirror.h"
#include "Mirror_Int.h"
#include "Mirror_DestChannel.h"

#if (MIRROR_DESTINATION_CHANNEL_PROTOCOL_AUTOSAR == STD_ON)
# include "Mirror_DestChannelProtocolAsr.h"
#endif /* (MIRROR_DESTINATION_CHANNEL_PROTOCOL_AUTOSAR == STD_ON) */

#if (MIRROR_DESTINATION_CHANNEL_PROTOCOL_VECTOR == STD_ON)
# include "Mirror_DestChannelProtocolVector.h"
#endif /* (MIRROR_DESTINATION_CHANNEL_PROTOCOL_VECTOR == STD_ON) */

#include "SchM_Mirror.h"

#if (MIRROR_DEV_ERROR_REPORT == STD_ON)
# include "Det.h"
#endif

#include "vstdlib.h"

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/
#define MIRROR_DESTCHANNELIP_QUEUE_FIRST_BYTE_POS          (0u)
#define MIRROR_DESTCHANNELIP_QUEUE_INIT_ZERO               (0u)

#define MIRROR_PROTOCOL_DATA_HEADER_NO_FRAMEID_LENGTH      (0u)

#define MIRROR_PROTOCOL_CAN_STATUS_ONLY_LENGTH             (19u)
#define MIRROR_PROTOCOL_LIN_STATUS_ONLY_LENGTH             (19u)
#define MIRROR_PROTOCOL_FLEXRAY_STATUS_ONLY_LENGTH         (19u)

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/
#define MIRROR_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e{451} */

#if (MIRROR_DESTINATION_CHANNEL_IP == STD_ON)
/*! Current state of the IP destination channel */
MIRROR_LOCAL VAR(Mirror_DestChannelIpContextType, MIRROR_VAR_NOINIT) Mirror_DestChannelIp_Ctx;
#endif

/*! Global state of the Mirror module. */
MIRROR_LOCAL VAR(Mirror_GeneralContextType*, MIRROR_VAR_NOINIT) Mirror_DestChannelIp_GeneralCtx;

#define MIRROR_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e{451} */

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
/*================================================= MIRROR_START_SEC_CODE ===========================================*/
#define MIRROR_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e{451} */

#if (MIRROR_DESTINATION_CHANNEL_IP == STD_ON)
/**********************************************************************************************************************
 *  Mirror_DestChannelIp_QueueFinalizeElement()
 *********************************************************************************************************************/
/*! \brief          Function to finalize a queue element
 *  \details        Function is used before queue element is transmitted.
 *  \param[in,out]  element  The queue element
 *  \param[in]      length   Length information for the element header
 *  \pre            Module is initialized.
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \config         This service is only available if MIRROR_DESTINATION_CHANNEL_IP == STD_ON.
 *********************************************************************************************************************/
MIRROR_LOCAL_INLINE FUNC(void, MIRROR_CODE) Mirror_DestChannelIp_QueueFinalizeElement(uint8* element, uint16 length);
#endif /* (MIRROR_DESTINATION_CHANNEL_IP == STD_ON) */

#if (MIRROR_DESTINATION_CHANNEL_IP == STD_ON)
/**********************************************************************************************************************
 *  Mirror_DestChannelIp_QueueInit()
 *********************************************************************************************************************/
/*! \brief       Function to initialize the queue
 *  \details     Function initialize a IP queue.
 *  \pre         Module is initialized.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      This service is only available if MIRROR_DESTINATION_CHANNEL_IP == STD_ON.
 *********************************************************************************************************************/
MIRROR_LOCAL_INLINE FUNC(void, MIRROR_CODE) Mirror_DestChannelIp_QueueInit(void);
#endif /* (MIRROR_DESTINATION_CHANNEL_IP == STD_ON) */

#if (MIRROR_DESTINATION_CHANNEL_IP == STD_ON)
/**********************************************************************************************************************
 *  Mirror_DestChannelIp_QueueRead()
 *********************************************************************************************************************/
/*! \brief         Function to read one element from the IP queue.
 *  \details       -
 *  \param[out]    queueElement  Buffer for the data to read of the queue.
 *  \param[in,out] length        Length of the buffer/Length of the data.
 *  \return        E_OK: A element from the queue is returned
 *  \return        E_NOT_OK: Queue read failed.
 *  \pre           Module is initialized.
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \config        This service is only available if MIRROR_DESTINATION_CHANNEL_IP == STD_ON.
 *********************************************************************************************************************/
MIRROR_LOCAL_INLINE FUNC(Std_ReturnType, MIRROR_CODE) Mirror_DestChannelIp_QueueRead(uint8* queueElement, uint16* length);
#endif /* (MIRROR_DESTINATION_CHANNEL_IP == STD_ON) */

#if (MIRROR_DESTINATION_CHANNEL_IP == STD_ON)
/**********************************************************************************************************************
 *  Mirror_DestChannelIp_QueueWrite()
 *********************************************************************************************************************/
/*! \brief       Function to store data in the IP queue.
 *  \details     -
 *  \param[in]   newElement          The data to store in the queue.
 *  \param[in]   length              Length of the data
 *  \param[in]   useNewElement       Flag that indicates if a new element shall be used
 *  \return      E_OK: Data are stored in the queue
 *  \return      E_NOT_OK: Data are not stored in the queue
 *  \pre         Module is initialized.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      This service is only available if MIRROR_DESTINATION_CHANNEL_IP == STD_ON.
 *********************************************************************************************************************/
MIRROR_LOCAL_INLINE FUNC(Std_ReturnType, MIRROR_CODE) Mirror_DestChannelIp_QueueWrite(const uint8* newElement, uint16 length, boolean useNewElement);
#endif /* (MIRROR_DESTINATION_CHANNEL_IP == STD_ON) */

#if (MIRROR_DESTINATION_CHANNEL_IP == STD_ON)
/**********************************************************************************************************************
 *  Mirror_DestChannelIp_IsTransmitRequired()
 *********************************************************************************************************************/
/*! \brief       Function indicates if a transmit is required
 *  \details     -
 *  \return      TRUE: Transmit is required
 *  \return      FALSE: Transmit is not required
 *  \pre         Module is initialized.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      This service is only available if MIRROR_DESTINATION_CHANNEL_IP == STD_ON.
 *********************************************************************************************************************/
MIRROR_LOCAL_INLINE FUNC(boolean, MIRROR_APPL_CODE) Mirror_DestChannelIp_IsTransmitRequired(void);
#endif /* (MIRROR_DESTINATION_CHANNEL_IP == STD_ON) */

#if (MIRROR_DESTINATION_CHANNEL_IP == STD_ON)
/**********************************************************************************************************************
 *  Mirror_DestChannelIp_Transmit()
 *********************************************************************************************************************/
/*! \brief       Function transmits a frame of the IP queue.
 *  \details     Function read the next element to send from the queue and triggers the send function.
 *  \return      E_OK: Transmission successful.
 *  \return      E_NOT_OK: Transmission not successful.
 *  \pre         Module is initialized.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      This service is only available if MIRROR_DESTINATION_CHANNEL_IP == STD_ON.
 *********************************************************************************************************************/
MIRROR_LOCAL_INLINE FUNC(Std_ReturnType, MIRROR_CODE) Mirror_DestChannelIp_Transmit(void);
#endif /* (MIRROR_DESTINATION_CHANNEL_IP == STD_ON) */

#if ((MIRROR_DESTINATION_CHANNEL_IP == STD_ON) && (MIRROR_TRANSMISSIONDEADLINEOFDESTINATIONCHANNELIP == STD_ON))
/**********************************************************************************************************************
 *  Mirror_DestChannelIp_HandleTransmissionDeadline()
 *********************************************************************************************************************/
/*! \brief       Function handles the transmission deadline.
 *  \details     -
 *  \pre         Module is initialized.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      This service is only available if MIRROR_DESTINATION_CHANNEL_IP == STD_ON.
 *********************************************************************************************************************/
MIRROR_LOCAL_INLINE FUNC(void, MIRROR_CODE) Mirror_DestChannelIp_HandleTransmissionDeadline(void);
#endif /* ((MIRROR_DESTINATION_CHANNEL_IP == STD_ON) && (MIRROR_TRANSMISSIONDEADLINEOFDESTINATIONCHANNELIP == STD_ON)) */

#if (MIRROR_DESTINATION_CHANNEL_IP == STD_ON)
/**********************************************************************************************************************
 *  Mirror_DestChannelIp_HandleTxConfirmationTimeout()
 *********************************************************************************************************************/
/*! \brief       Function handles the Tx Confirmation timeout.
 *  \details     -
 *  \pre         Module is initialized.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      This service is only available if MIRROR_DESTINATION_CHANNEL_IP == STD_ON.
 *********************************************************************************************************************/
MIRROR_LOCAL_INLINE FUNC(void, MIRROR_CODE) Mirror_DestChannelIp_HandleTxConfirmationTimeout(void);
#endif /* (MIRROR_DESTINATION_CHANNEL_IP == STD_ON) */

#if ((MIRROR_DESTINATION_CHANNEL_IP == STD_ON) && ((MIRROR_SOURCE_CHANNEL_CAN == STD_ON) || (MIRROR_SOURCE_CHANNEL_LIN == STD_ON) || (MIRROR_SOURCE_CHANNEL_FLEXRAY == STD_ON)))
/**********************************************************************************************************************
 *  Mirror_DestChannelIp_ProcessFrame()
 *********************************************************************************************************************/
/*! \brief       Function to store a CAN, LIN or FlexRay frame in the queue.
 *  \details     -
 *  \param[in]   newElement     Buffer for the new element
 *  \param[in]   frameId        Frame Id
 *  \param[in]   frameIdLength  Length of the frame Id
 *  \param[in]   length         Length of the payload
 *  \param[in]   payload        Payload
 *  \param[in]   metaData       Meta data
 *  \param[in]   networkId      Network Id of the source channel
 *  \param[in]   networkState   Current state of the source channel
 *  \return      E_OK: Data stored in the queue.
 *  \return      E_NOT_OK: Queue is full, data not stored.
 *  \pre         Module is initialized.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      This service is only available if MIRROR_DESTINATION_CHANNEL_IP == STD_ON.
 *********************************************************************************************************************/
MIRROR_LOCAL_INLINE FUNC(Std_ReturnType, MIRROR_CODE) Mirror_DestChannelIp_ProcessFrame(uint8* newElement, uint32 frameId, uint8 frameIdLength,
                                                                    uint8 length, const uint8* payload, uint8 metaData,
                                                                    uint8 networkId, uint8 networkState);
#endif /* ((MIRROR_DESTINATION_CHANNEL_IP == STD_ON) && ((MIRROR_SOURCE_CHANNEL_CAN == STD_ON) || (MIRROR_SOURCE_CHANNEL_LIN == STD_ON) || (MIRROR_SOURCE_CHANNEL_FLEXRAY == STD_ON))) */

#define MIRROR_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e{451} */
/*================================================= MIRROR_STOP_SEC_CODE ============================================*/
/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/
/*================================================= MIRROR_START_SEC_CODE ===========================================*/
#define MIRROR_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e{451} */

#if (MIRROR_DESTINATION_CHANNEL_IP == STD_ON)
/**********************************************************************************************************************
 *  Mirror_DestChannelIp_QueueFinalizeElement()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 */
MIRROR_LOCAL_INLINE FUNC(void, MIRROR_CODE) Mirror_DestChannelIp_QueueFinalizeElement(uint8* element, uint16 length)
{
  /* #10 Trigger the finalization of the queue element (set message length in header)
   *     by calling the finalize function of either the AUTOSAR or Vector protocol handler depending on the used protocol. */
# if (MIRROR_DESTINATION_CHANNEL_PROTOCOL_AUTOSAR == STD_ON)
  Mirror_DestChannelProtocolAsr_QueueFinalizeElement(element, length);
# else
  Mirror_DestChannelProtocolVector_QueueFinalizeElement(element, length);
# endif

  /* #20 Reset the time stamp. */
  Mirror_DestChannelIp_Ctx.QueueIP.WriteTimeStamp.nanoseconds = 0u;
  Mirror_DestChannelIp_Ctx.QueueIP.WriteTimeStamp.seconds = 0u;
  Mirror_DestChannelIp_Ctx.QueueIP.WriteTimeStamp.secondsHi = 0u;
  Mirror_DestChannelIp_Ctx.QueueIP.WriteTimeStamp.timeBaseStatus = 0u;
} /* Mirror_DestChannelIp_QueueFinalizeElement() */
#endif /* (MIRROR_DESTINATION_CHANNEL_IP == STD_ON) */

#if (MIRROR_DESTINATION_CHANNEL_IP == STD_ON)
/**********************************************************************************************************************
 *  Mirror_DestChannelIp_QueueInit()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 */
MIRROR_LOCAL_INLINE FUNC(void, MIRROR_CODE) Mirror_DestChannelIp_QueueInit(void)
{
  Mirror_DestinationChannelIpIdxOfDestComMChannelType channelIndex = Mirror_GetDestinationChannelIpIdxOfDestComMChannel(Mirror_DestChannelIp_GeneralCtx->CurrentDestChannelIndex);

  uint8* queueBuffer = &Mirror_GetDestinationQueueBuffer(MIRROR_DESTCHANNELIP_QUEUE_FIRST_BYTE_POS);
  uint16 queueElementCount = Mirror_GetQueueSizeOfDestinationChannelIp(channelIndex);
  uint16 elementLength = Mirror_GetTxPduLengthOfDestinationChannelIp(channelIndex);

  /* #10 Initialize the configuration of the current destination channel to it's default parameter. */
  Mirror_DestChannelIp_Ctx.QueueIP.UseNewElementAfterTransmit = FALSE;
  Mirror_DestChannelIp_Ctx.QueueIP.QueueElementWriteIdx = MIRROR_DESTCHANNELIP_QUEUE_INIT_ZERO;

  Mirror_DestChannelIp_Ctx.QueueIP.WriteTimeStamp.nanoseconds = 0u;
  Mirror_DestChannelIp_Ctx.QueueIP.WriteTimeStamp.seconds = 0u;
  Mirror_DestChannelIp_Ctx.QueueIP.WriteTimeStamp.secondsHi = 0u;
  Mirror_DestChannelIp_Ctx.QueueIP.WriteTimeStamp.timeBaseStatus = 0u;
  Mirror_DestChannelIp_Ctx.QueueIP.QueueElementLength = elementLength;
  Mirror_DestChannelIp_Ctx.SeqNumber = MIRROR_DESTCHANNELIP_QUEUE_INIT_ZERO;

  /* #20 Trigger the initialization of the queue with the element count and length of the current destination channel. */
  Mirror_QueueInit(&(Mirror_DestChannelIp_Ctx.QueueIP.Queue), queueBuffer, queueElementCount, elementLength);
} /* Mirror_DestChannelIp_QueueInit() */
#endif /* (MIRROR_DESTINATION_CHANNEL_IP == STD_ON) */

#if (MIRROR_DESTINATION_CHANNEL_IP == STD_ON)
/**********************************************************************************************************************
 *  Mirror_DestChannelIp_QueueRead()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 */
MIRROR_LOCAL_INLINE FUNC(Std_ReturnType, MIRROR_CODE) Mirror_DestChannelIp_QueueRead(uint8* queueElement, uint16* length)
{
  Std_ReturnType retVal;
  
  /* #10 Trigger the queue read operation of the next element for transmission. */
  retVal = Mirror_QueueRead(&(Mirror_DestChannelIp_Ctx.QueueIP.Queue), queueElement, length);

  /* #20 If the read operation was successful, trigger the finalization of the queue element. */
  if(retVal == E_OK)
  {
    Mirror_DestChannelIp_QueueFinalizeElement(queueElement, (*length));
  }

  return retVal;
} /* Mirror_DestChannelIp_QueueRead() */
#endif /* (MIRROR_DESTINATION_CHANNEL_IP == STD_ON) */

#if (MIRROR_DESTINATION_CHANNEL_IP == STD_ON)
/**********************************************************************************************************************
 *  Mirror_DestChannelIp_QueueWrite()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 */
MIRROR_LOCAL_INLINE FUNC(Std_ReturnType, MIRROR_CODE) Mirror_DestChannelIp_QueueWrite(const uint8* newElement, uint16 length, boolean useNewElement)
{
  Std_ReturnType retVal;

  /* #10 Trigger the queue write operation for the given data. */
  retVal = Mirror_QueueWrite(&(Mirror_DestChannelIp_Ctx.QueueIP.Queue), newElement, length, useNewElement, Mirror_DestChannelIp_Ctx.QueueIP.QueueElementWriteIdx);

  /* #20 Update current position in queue element. */
  Mirror_DestChannelIp_Ctx.QueueIP.QueueElementWriteIdx += length;

  return retVal;
} /* Mirror_DestChannelIp_QueueWrite() */
#endif /* (MIRROR_DESTINATION_CHANNEL_IP == STD_ON) */

#if (MIRROR_DESTINATION_CHANNEL_IP == STD_ON)
/**********************************************************************************************************************
 *  Mirror_DestChannelIp_IsTransmitRequired()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
MIRROR_LOCAL_INLINE FUNC(boolean, MIRROR_APPL_CODE) Mirror_DestChannelIp_IsTransmitRequired(void)
{
  boolean retVal = FALSE;

  /* #10 Return TRUE, if there is a queue element ready for transmission. */
  if((Mirror_DestChannelIp_Ctx.QueueIP.Queue.QueueSize - Mirror_DestChannelIp_Ctx.QueueIP.Queue.FreeElements) > 1u)
  {
    retVal = TRUE;
  }

  return retVal;
} /* Mirror_DestChannelIp_IsTransmitRequired() */
#endif /* (MIRROR_DESTINATION_CHANNEL_IP == STD_ON) */

#if (MIRROR_DESTINATION_CHANNEL_IP == STD_ON)
/**********************************************************************************************************************
 * Mirror_DestChannelIp_Transmit()
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
 */
MIRROR_LOCAL_INLINE FUNC(Std_ReturnType, MIRROR_CODE) Mirror_DestChannelIp_Transmit(void)
{
  Std_ReturnType retVal = E_NOT_OK;
  PduInfoType pdu;
  uint8* messageBuffer = &Mirror_GetDestinationChannelIpTransmitBuffer(0u);

  /* #10 If the transmission PDU of the current destination channel is free to use: */
  if(Mirror_DestChannelIp_GeneralCtx->DestChannel_TxPduLocked == FALSE)
  {
    Mirror_DestinationChannelIpIdxOfDestComMChannelType destChannelIndex;

    /* #20 Enter MIRROR_EXCLUSIVE_AREA_QUEUE. */
    SchM_Enter_Mirror_MIRROR_EXCLUSIVE_AREA_QUEUE();

    destChannelIndex = Mirror_GetDestinationChannelIpIdxOfDestComMChannel(Mirror_DestChannelIp_GeneralCtx->CurrentDestChannelIndex);

    /* #30 If the current destination channel uses trigger transmit: */
#if(MIRROR_USESTRIGGERTRANSMITOFDESTINATIONCHANNELIP == STD_ON)
    if(Mirror_IsUsesTriggerTransmitOfDestinationChannelIp(destChannelIndex)) /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */
    {
      pdu.SduDataPtr = NULL_PTR;

      /* #40 If there is a queue element read for transmission: */
      if(Mirror_QueueIsEmpty(&(Mirror_DestChannelIp_Ctx.QueueIP.Queue)) == FALSE)
      {
        /* #50 Set the queue element length to the transmission PDU struct. */
        pdu.SduLength = Mirror_GetTxPduLengthOfDestinationChannelIp(destChannelIndex);

        retVal = E_OK;
      }
    }
    else
#endif
    /* #60 Otherwise, use direct transmit:  */
    {
      /* #70 If there is a queue element read for transmission, set the element length and data to the transmission PDU struct. */
      uint16 messageBufferLength = (uint16)Mirror_GetSizeOfDestinationChannelIpTransmitBuffer();

      pdu.SduDataPtr = (SduDataPtrType) messageBuffer;

      retVal = Mirror_DestChannelIp_QueueRead(messageBuffer, &messageBufferLength);

      pdu.SduLength = messageBufferLength;
    }

    /* #80 Leave MIRROR_EXCLUSIVE_AREA_QUEUE. */
    SchM_Exit_Mirror_MIRROR_EXCLUSIVE_AREA_QUEUE();

    /* #90 If there is a queue element ready for transmission: */
    if(retVal == E_OK)
    {
      /* #100 Trigger the transmission of the queue element. */
      retVal = Mirror_DestChannel_Transmit(Mirror_DestChannelIp_GeneralCtx, &pdu, Mirror_GetPduRTxPduIdOfDestinationChannelIp(destChannelIndex));

      /* #110 If the transmission was not successful, set the frame lost flag. */
      if(retVal == E_NOT_OK)
      {
        Mirror_DestChannelIp_Ctx.FrameLost = TRUE;
      }
    }
    /* #120 Otherwise, do nothing and return success. */
    else
    { 
      retVal = E_OK;
    }
  }

  return retVal;
} /* Mirror_DestChannelIp_Transmit() */
#endif /* (MIRROR_DESTINATION_CHANNEL_IP == STD_ON) */

#if ((MIRROR_DESTINATION_CHANNEL_IP == STD_ON) && (MIRROR_TRANSMISSIONDEADLINEOFDESTINATIONCHANNELIP == STD_ON))
/**********************************************************************************************************************
 * Mirror_DestChannelIp_HandleTransmissionDeadline()
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
 */
MIRROR_LOCAL_INLINE FUNC(void, MIRROR_CODE) Mirror_DestChannelIp_HandleTransmissionDeadline(void)
{
  Mirror_DestinationChannelIpIdxOfDestComMChannelType currentDestChannelIndex;

  /* #10 Enter MIRROR_EXCLUSIVE_AREA_TXPDU. */
  SchM_Enter_Mirror_MIRROR_EXCLUSIVE_AREA_TXPDU();

  currentDestChannelIndex = Mirror_GetDestinationChannelIpIdxOfDestComMChannel(Mirror_DestChannelIp_GeneralCtx->CurrentDestChannelIndex);

  /* #20 If the current destination channel supports the transmission deadline: */
  if(Mirror_GetTransmissionDeadlineOfDestinationChannelIp(currentDestChannelIndex) != MIRROR_NO_TRANSMISSIONDEADLINEOFDESTINATIONCHANNELIP)
  {
    /* #30 If the transmission deadline in enabled: */
    if(Mirror_DestChannelIp_Ctx.TransmissionDeadlineEnabled == TRUE)
    {
      /* #40 Update the transmission deadline timer. */
      ++Mirror_DestChannelIp_Ctx.TransmissionDeadline;

      /* #50 If the transmission deadline expired: */
      if(Mirror_DestChannelIp_Ctx.TransmissionDeadline >= Mirror_GetTransmissionDeadlineOfDestinationChannelIp(currentDestChannelIndex))
      {
        /* #60 If the transmission PDU is free for use: */
        if(Mirror_DestChannelIp_GeneralCtx->DestChannel_TxPduLocked == FALSE)
        {
          /* #70 Disable the transmission deadline and indicate that a new queue element must be used for write operations. */
          Std_ReturnType retVal;

          Mirror_DestChannelIp_Ctx.TransmissionDeadlineEnabled = FALSE;
          Mirror_DestChannelIp_Ctx.QueueIP.UseNewElementAfterTransmit = TRUE;

          SchM_Exit_Mirror_MIRROR_EXCLUSIVE_AREA_TXPDU();

          /* #80 Trigger the transmission. */
          retVal = Mirror_DestChannelIp_Transmit();

          if (retVal == E_NOT_OK)
          {
# if (MIRROR_RUNTIME_ERROR_REPORT == STD_ON)
            (void)Det_ReportRuntimeError(MIRROR_MODULE_ID, MIRROR_INSTANCE_ID_DET, MIRROR_SID_MAINFUNCTION, MIRROR_E_TRANSMIT_FAILED);
# endif
          }
        }
        /* #90 Otherwise, leave MIRROR_EXCLUSIVE_AREA_TXPDU. */
        else
        {
          SchM_Exit_Mirror_MIRROR_EXCLUSIVE_AREA_TXPDU();
        }
      }
      /* #100 Otherwise, leave MIRROR_EXCLUSIVE_AREA_TXPDU. */
      else
      {
        SchM_Exit_Mirror_MIRROR_EXCLUSIVE_AREA_TXPDU();
      }
    }
    /* #110 Otherwise, leave MIRROR_EXCLUSIVE_AREA_TXPDU. */
    else
    {
      SchM_Exit_Mirror_MIRROR_EXCLUSIVE_AREA_TXPDU();
    }
  }
  /* #120 Otherwise, leave MIRROR_EXCLUSIVE_AREA_TXPDU. */
  else
  {
    SchM_Exit_Mirror_MIRROR_EXCLUSIVE_AREA_TXPDU();
  }
  /* PRQA S 6080 1 */ /* MD_MSR_STMIF */
} /* Mirror_DestChannelIp_HandleTransmissionDeadline() */
#endif /* ((MIRROR_DESTINATION_CHANNEL_IP == STD_ON) && (MIRROR_TRANSMISSIONDEADLINEOFDESTINATIONCHANNELIP == STD_ON)) */

#if (MIRROR_DESTINATION_CHANNEL_IP == STD_ON)
/**********************************************************************************************************************
 * Mirror_DestChannelIp_HandleTxConfirmationTimeout()
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
 */
MIRROR_LOCAL_INLINE FUNC(void, MIRROR_CODE) Mirror_DestChannelIp_HandleTxConfirmationTimeout(void)
{
  /* #10 Enter MIRROR_EXCLUSIVE_AREA_TXPDU. */
  SchM_Enter_Mirror_MIRROR_EXCLUSIVE_AREA_TXPDU();

  /* #20 If a transmission is in progress: */
  if(Mirror_DestChannelIp_GeneralCtx->DestChannel_TxPduLocked == TRUE)
  {
    /* Update the TxConfirmation timeout timer. */
    --Mirror_DestChannelIp_GeneralCtx->TxConfTimeout;

    /* #30 If the TxConfirmation timeout expired: */
    if(Mirror_DestChannelIp_GeneralCtx->TxConfTimeout == 0u)
    {
      /* #40 Release the lock of the transmission PDU. */
      Mirror_DestChannelIp_GeneralCtx->DestChannel_TxPduLocked = FALSE;

      /* #50 Set the frame lost flag. */
      Mirror_DestChannelIp_Ctx.FrameLost = TRUE;

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
  /* #80 Otherwise, leave MIRROR_EXCLUSIVE_AREA_TXPDU. */
  else
  {
    SchM_Exit_Mirror_MIRROR_EXCLUSIVE_AREA_TXPDU();
  }
} /* Mirror_DestChannelIp_HandleTxConfirmationTimeout() */
#endif /* (MIRROR_DESTINATION_CHANNEL_IP == STD_ON) */

#if ((MIRROR_DESTINATION_CHANNEL_IP == STD_ON) && ((MIRROR_SOURCE_CHANNEL_CAN == STD_ON) || (MIRROR_SOURCE_CHANNEL_LIN == STD_ON) || (MIRROR_SOURCE_CHANNEL_FLEXRAY == STD_ON)))
/**********************************************************************************************************************
 *  Mirror_DestChannelIp_ProcessFrame()
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
 */
MIRROR_LOCAL_INLINE FUNC(Std_ReturnType, MIRROR_CODE) Mirror_DestChannelIp_ProcessFrame(uint8* newElement, uint32 frameId, uint8 frameIdLength,
                                                                    uint8 length, const uint8* payload, uint8 metaData,
                                                                    uint8 networkId, uint8 networkState)
{
  Std_ReturnType retVal;
  boolean useNewElement;
  uint16 newElementLength;

  /* #10 Enter MIRROR_EXCLUSIVE_AREA_QUEUE. */
  SchM_Enter_Mirror_MIRROR_EXCLUSIVE_AREA_QUEUE();

  /* #20 If the AUTOSAR protocol is used: */
# if (MIRROR_DESTINATION_CHANNEL_PROTOCOL_AUTOSAR == STD_ON)
  /* #30 Check if a new queue element must be used. */
  useNewElement = Mirror_DestChannelProtocolAsr_QueueUseNewElement(&Mirror_DestChannelIp_Ctx, length);

  /* #40 Trigger the creation of a queue element using the AUTOSAR protocol format. */
  newElementLength = Mirror_DestChannelProtocolAsr_QueueNewElement(&Mirror_DestChannelIp_Ctx, newElement, payload, length, (uint32) frameId, frameIdLength, networkId, metaData, networkState, useNewElement);

  /* #50 Otherwise, use the Vector protocol: */
# else
  MIRROR_DUMMY_STATEMENT(frameIdLength); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  MIRROR_DUMMY_STATEMENT(networkState); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */

  /* #60 Check if a new queue element must be used. */
  useNewElement = Mirror_DestChannelProtocolVector_QueueUseNewElement(&Mirror_DestChannelIp_Ctx, length);

  /* #70 Trigger the creation of a queue element using the Vector protocol format. */
  newElementLength = Mirror_DestChannelProtocolVector_QueueNewElement(&Mirror_DestChannelIp_Ctx, newElement, payload, length, (uint32) frameId, networkId, metaData, useNewElement, Mirror_DestChannelIp_GeneralCtx->StartTime);
# endif

  /* #80 Trigger the queue operation of the given data. */
  retVal = Mirror_DestChannelIp_QueueWrite(newElement, newElementLength, useNewElement);

  /* #90 Set the frame lost flag, if the queue operation was not successful. */
  if(retVal == E_NOT_OK)
  {
    Mirror_DestChannelIp_Ctx.FrameLost = TRUE;
  }

  /* #100 Leave MIRROR_EXCLUSIVE_AREA_QUEUE. */
  SchM_Exit_Mirror_MIRROR_EXCLUSIVE_AREA_QUEUE();

  return retVal;
  /* PRQA S 6060 1 */ /* MD_MSR_STPAR */
} /* Mirror_DestChannelIp_ProcessFrame() */
#endif /* ((MIRROR_DESTINATION_CHANNEL_IP == STD_ON) && ((MIRROR_SOURCE_CHANNEL_CAN == STD_ON) || (MIRROR_SOURCE_CHANNEL_LIN == STD_ON) || (MIRROR_SOURCE_CHANNEL_FLEXRAY == STD_ON))) */

#define MIRROR_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e{451} */
/*================================================= MIRROR_STOP_SEC_CODE ============================================*/
/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/
/*================================================= MIRROR_START_SEC_CODE ===========================================*/
#define MIRROR_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e{451} */

#if (MIRROR_DESTINATION_CHANNEL_IP == STD_ON)
/**********************************************************************************************************************
 *  Mirror_DestChannelIp_Init()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, MIRROR_CODE) Mirror_DestChannelIp_Init(Mirror_GeneralContextType* mirrorCtx)
{
  /* #10 Initialize the general configuration of the destination channel. */
  Mirror_DestChannelIp_GeneralCtx = mirrorCtx;

  Mirror_DestChannelIp_GeneralCtx->DestChannel_TxPduLocked = FALSE;

#if(MIRROR_TRANSMISSIONDEADLINEOFDESTINATIONCHANNELIP == STD_ON)
  Mirror_DestChannelIp_Ctx.TransmissionDeadline = 0u;
  Mirror_DestChannelIp_Ctx.TransmissionDeadlineEnabled = FALSE;
#endif

  Mirror_DestChannelIp_Ctx.FrameLost = FALSE;

  /* #20 Trigger the initialization of the queue. */
  Mirror_DestChannelIp_QueueInit();
} /* Mirror_DestChannelIp_Init() */
#endif /* (MIRROR_DESTINATION_CHANNEL_IP == STD_ON) */

#if (MIRROR_DESTINATION_CHANNEL_IP == STD_ON)
/**********************************************************************************************************************
 *  Mirror_DestChannelIp_MainFunction()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, MIRROR_APPL_CODE) Mirror_DestChannelIp_MainFunction(void)
{
  /* #10 If a queue element is full and therefore must be transmitted: */
  if(Mirror_DestChannelIp_IsTransmitRequired() == TRUE)
  {
    Std_ReturnType retVal;

    /* #20 Trigger the transmission. */
    retVal = Mirror_DestChannelIp_Transmit();

    if (retVal == E_NOT_OK)
    {
# if (MIRROR_RUNTIME_ERROR_REPORT == STD_ON)
      (void)Det_ReportRuntimeError(MIRROR_MODULE_ID, MIRROR_INSTANCE_ID_DET, MIRROR_SID_MAINFUNCTION, MIRROR_E_TRANSMIT_FAILED);
# endif
    }
  }

  /* #30 Trigger the handling of the TxConfirmation timeout. */
  Mirror_DestChannelIp_HandleTxConfirmationTimeout();

#if (MIRROR_TRANSMISSIONDEADLINEOFDESTINATIONCHANNELIP == STD_ON)
  Mirror_DestChannelIp_HandleTransmissionDeadline();
#endif
} /* Mirror_DestChannelIp_MainFunction() */
#endif /* (MIRROR_DESTINATION_CHANNEL_IP == STD_ON) */

#if ((MIRROR_DESTINATION_CHANNEL_IP == STD_ON) && (MIRROR_SOURCE_CHANNEL_CAN == STD_ON))
/**********************************************************************************************************************
 *  Mirror_DestChannelIp_ProcessCanFrame()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, MIRROR_CODE) Mirror_DestChannelIp_ProcessCanFrame(uint32 canId, uint8 length, const uint8* payload,
                                                                       uint8 metaData, uint8 networkId, uint8 networkState)
{
  Std_ReturnType retVal;
  uint8 newElement[MIRROR_DESTINATION_CHANNEL_IP_QUEUE_ELEMENT_SIZE];

  /* #10 Trigger the processing of the given CAN frame. */
  retVal = Mirror_DestChannelIp_ProcessFrame(newElement, (uint32) canId, MIRROR_AUTOSAR_PROTOCOL_DATA_HEADER_CAN_FRAMEID_LENGTH, length, payload, metaData, networkId, networkState);

  return retVal;
  /* PRQA S 6060 1 */ /* MD_MSR_STPAR */
}/* Mirror_DestChannelIp_ProcessCanFrame() */
#endif /* ((MIRROR_DESTINATION_CHANNEL_IP == STD_ON) && (MIRROR_SOURCE_CHANNEL_CAN == STD_ON)) */

#if ((MIRROR_DESTINATION_CHANNEL_IP == STD_ON) && (MIRROR_SOURCE_CHANNEL_CAN == STD_ON))
/**********************************************************************************************************************
* Mirror_DestChannelIp_ProcessCanStatus()
**********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(void, MIRROR_CODE) Mirror_DestChannelIp_ProcessCanStatus(uint8 metaData, uint8 networkId, uint8 networkState)
{
  /* #10 If the AUTOSAR protocol is configured, trigger the processing of a CAN source channel state. */
#if (MIRROR_DESTINATION_CHANNEL_PROTOCOL_AUTOSAR == STD_ON)
  uint8 newElement[MIRROR_PROTOCOL_CAN_STATUS_ONLY_LENGTH];

  (void)Mirror_DestChannelIp_ProcessFrame(newElement, (uint32)0u, MIRROR_PROTOCOL_DATA_HEADER_NO_FRAMEID_LENGTH, 0u, NULL_PTR, metaData, networkId, networkState);
#else
  MIRROR_DUMMY_STATEMENT(metaData); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  MIRROR_DUMMY_STATEMENT(networkId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  MIRROR_DUMMY_STATEMENT(networkState); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
#endif
} /* Mirror_DestChannelIp_ProcessCanStatus() */
#endif /* ((MIRROR_DESTINATION_CHANNEL_IP == STD_ON) && (MIRROR_SOURCE_CHANNEL_CAN == STD_ON)) */

#if ((MIRROR_DESTINATION_CHANNEL_IP == STD_ON) && (MIRROR_SOURCE_CHANNEL_LIN == STD_ON))
/**********************************************************************************************************************
 *  Mirror_DestChannelIp_ProcessLinFrame()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, MIRROR_CODE) Mirror_DestChannelIp_ProcessLinFrame(uint8 id, uint8 length, const uint8* payload,
                                                                       uint8 metaData, uint8 networkId, uint8 networkState)
{
  Std_ReturnType retVal;
  uint8 newElement[MIRROR_DESTINATION_CHANNEL_IP_QUEUE_ELEMENT_SIZE];

  /* #10 Trigger the processing of the given LIN frame. */
  retVal = Mirror_DestChannelIp_ProcessFrame(newElement, (uint32) id, MIRROR_AUTOSAR_PROTOCOL_DATA_HEADER_LIN_FRAMEID_LENGTH, length, payload, metaData, networkId, networkState);

  return retVal;
  /* PRQA S 6060 1 */ /* MD_MSR_STPAR */
} /* Mirror_DestChannelIp_ProcessLinFrame() */
#endif /* ((MIRROR_DESTINATION_CHANNEL_IP == STD_ON) && (MIRROR_SOURCE_CHANNEL_LIN == STD_ON)) */

#if ((MIRROR_DESTINATION_CHANNEL_IP == STD_ON) && (MIRROR_SOURCE_CHANNEL_LIN == STD_ON))
/**********************************************************************************************************************
* Mirror_DestChannelIp_ProcessLinStatus()
**********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(void, MIRROR_CODE) Mirror_DestChannelIp_ProcessLinStatus(uint8 metaData, uint8 networkId, uint8 networkState)
{
  /* #10 If the AUTOSAR protocol is configured, trigger the processing of a LIN source channel state. */
#if (MIRROR_DESTINATION_CHANNEL_PROTOCOL_AUTOSAR == STD_ON)
  uint8 newElement[MIRROR_PROTOCOL_LIN_STATUS_ONLY_LENGTH];

  (void)Mirror_DestChannelIp_ProcessFrame(newElement, (uint32)0u, MIRROR_PROTOCOL_DATA_HEADER_NO_FRAMEID_LENGTH, 0u, NULL_PTR, metaData, networkId, networkState);
#else
  MIRROR_DUMMY_STATEMENT(metaData); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  MIRROR_DUMMY_STATEMENT(networkId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  MIRROR_DUMMY_STATEMENT(networkState); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
#endif
} /* Mirror_DestChannelIp_ProcessLinStatus() */
#endif /* ((MIRROR_DESTINATION_CHANNEL_IP == STD_ON) && (MIRROR_SOURCE_CHANNEL_LIN == STD_ON)) */

#if ((MIRROR_DESTINATION_CHANNEL_IP == STD_ON) && (MIRROR_SOURCE_CHANNEL_FLEXRAY == STD_ON))
/**********************************************************************************************************************
 *  Mirror_DestChannelIp_ProcessFlexRayFrame()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, MIRROR_CODE) Mirror_DestChannelIp_ProcessFlexRayFrame(uint32 frameId, const PduInfoType* frame,
                                                                           uint8 metaData, uint8 networkId,
                                                                           uint8 networkState)
{
  Std_ReturnType retVal;
  uint8 newElement[MIRROR_DESTINATION_CHANNEL_IP_QUEUE_ELEMENT_SIZE];

  /* #10 Trigger the processing of the given FlexRay frame. */
  retVal = Mirror_DestChannelIp_ProcessFrame(newElement, frameId, MIRROR_AUTOSAR_PROTOCOL_DATA_HEADER_FLEXRAY_FRAMEID_LENGTH, (uint8)frame->SduLength, frame->SduDataPtr, metaData, networkId, networkState);

  return retVal;
} /* Mirror_DestChannelIp_ProcessFlexRayFrame() */
#endif /* ((MIRROR_DESTINATION_CHANNEL_IP == STD_ON) && (MIRROR_SOURCE_CHANNEL_LIN == STD_ON)) */

#if ((MIRROR_DESTINATION_CHANNEL_IP == STD_ON) && (MIRROR_SOURCE_CHANNEL_FLEXRAY == STD_ON))
/**********************************************************************************************************************
* Mirror_DestChannelIp_ProcessFlexRayStatus()
**********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(void, MIRROR_CODE) Mirror_DestChannelIp_ProcessFlexRayStatus(uint8 metaData, uint8 networkId, uint8 networkState)
{
  /* #10 If the AUTOSAR protocol is configured, trigger the processing of a FlexRay source channel state. */
#if (MIRROR_DESTINATION_CHANNEL_PROTOCOL_AUTOSAR == STD_ON)
  uint8 newElement[MIRROR_PROTOCOL_FLEXRAY_STATUS_ONLY_LENGTH];

  (void)Mirror_DestChannelIp_ProcessFrame(newElement, (uint32)0u, MIRROR_PROTOCOL_DATA_HEADER_NO_FRAMEID_LENGTH, 0u, NULL_PTR, metaData, networkId, networkState);
#else
  MIRROR_DUMMY_STATEMENT(metaData); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  MIRROR_DUMMY_STATEMENT(networkId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  MIRROR_DUMMY_STATEMENT(networkState); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
#endif
} /* Mirror_DestChannelIp_ProcessFlexRayStatus() */
#endif /* ((MIRROR_DESTINATION_CHANNEL_IP == STD_ON) && (MIRROR_SOURCE_CHANNEL_FLEXRAY == STD_ON)) */

#if (MIRROR_DESTINATION_CHANNEL_IP == STD_ON)
/**********************************************************************************************************************
 *  Mirror_DestChannelIp_TxConfirmation()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, MIRROR_CODE) Mirror_DestChannelIp_TxConfirmation(void)
{
  /* #10 Check if the Mirror module is initialized. */
  if(Mirror_DestChannelIp_GeneralCtx->GlobalMode == MIRROR_ACTIVE)
  {
    /* #20 If a queue element is full and therefore must be transmitted: */
    if(Mirror_DestChannelIp_IsTransmitRequired() == TRUE)
    {
      Std_ReturnType retVal;

      /* #30 Trigger the transmission. */
      retVal = Mirror_DestChannelIp_Transmit();

      if (retVal == E_NOT_OK)
      {
# if (MIRROR_RUNTIME_ERROR_REPORT == STD_ON)
        (void)Det_ReportRuntimeError(MIRROR_MODULE_ID, MIRROR_INSTANCE_ID_DET, MIRROR_SID_MAINFUNCTION, MIRROR_E_TRANSMIT_FAILED);
# endif
      }
    }
  }
} /* Mirror_DestChannelIp_TxConfirmation() */
#endif /* (MIRROR_DESTINATION_CHANNEL_IP == STD_ON) */

#if (MIRROR_DESTINATION_CHANNEL_IP == STD_ON)
/**********************************************************************************************************************
 *  Mirror_DestChannelIp_TriggerTransmit()
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
FUNC(Std_ReturnType, MIRROR_CODE) Mirror_DestChannelIp_TriggerTransmit(PduInfoType* PduInfoPtr)
{
  Std_ReturnType retVal = E_NOT_OK;

  /* #10 Check if the Mirror module is initialized. */
  if(Mirror_DestChannelIp_GeneralCtx->GlobalMode == MIRROR_ACTIVE)
  {
    uint16 bufferLength = (uint16)Mirror_GetSizeOfDestinationChannelIpTransmitBuffer();
    uint8* messageBuffer = &Mirror_GetDestinationChannelIpTransmitBuffer(0u);

    /* #20 Enter MIRROR_EXCLUSIVE_AREA_QUEUE. */
    SchM_Enter_Mirror_MIRROR_EXCLUSIVE_AREA_QUEUE();

    /* #30 Read the next element that is ready for transmission from the queue. */
    retVal = Mirror_DestChannelIp_QueueRead(messageBuffer, &bufferLength);

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
        Mirror_DestChannelIp_Ctx.FrameLost = TRUE;
      }
    }
  }

  return retVal;
} /* Mirror_DestChannelIp_TriggerTransmit() */
#endif /* (MIRROR_DESTINATION_CHANNEL_IP == STD_ON) */

#define MIRROR_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e{451} */
/*================================================= MIRROR_STOP_SEC_CODE ============================================*/
/**********************************************************************************************************************
 *  END OF FILE: Mirror_DestChannelIP.c
 *********************************************************************************************************************/
