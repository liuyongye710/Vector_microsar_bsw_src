/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2019 by Vector Informatik GmbH.                                              All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/*!     \file     Mirror_DestChannelProtocolAsr.h
 *      \brief    Mirror destination channel protocol (AUTOSAR) header file
 *
 *      \details  Header of destination channel protocol (AUTOSAR) implementation
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
#if !defined (MIRROR_DESTCHANNELPROTOCOLASR_H)
# define MIRROR_DESTCHANNELPROTOCOLASR_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Mirror_Int.h"

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
# define MIRROR_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e{451} */

#if ((MIRROR_DESTINATION_CHANNEL_IP == STD_ON) && (MIRROR_DESTINATION_CHANNEL_PROTOCOL_AUTOSAR == STD_ON))
/**********************************************************************************************************************
 *  Mirror_DestChannelProtocolAsr_QueueUseNewElement()
 *********************************************************************************************************************/
/*! \brief          Function checks if a new queue element is needed
 *  \details        -
 *  \param[in,out]  destChannelCtx Context of the destination channel
 *  \param[in]      length  Length of the new data to be stored in the queue
 *  \return         TRUE: A new element must be used
 *  \return         FALSE: The new data can be stored in the current used element
 *  \pre            Module is initialized.
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \config         This service is only available if MIRROR_DESTINATION_CHANNEL_IP == STD_ON and
 *                  MIRROR_DESTINATION_CHANNEL_PROTOCOL_AUTOSAR == STD_ON.
 *********************************************************************************************************************/
FUNC(boolean, MIRROR_CODE) Mirror_DestChannelProtocolAsr_QueueUseNewElement(Mirror_DestChannelIpContextType* destChannelCtx, uint8 length);
#endif /* ((MIRROR_DESTINATION_CHANNEL_IP == STD_ON) && (MIRROR_DESTINATION_CHANNEL_PROTOCOL_AUTOSAR == STD_ON)) */

#if ((MIRROR_DESTINATION_CHANNEL_IP == STD_ON) && (MIRROR_DESTINATION_CHANNEL_PROTOCOL_AUTOSAR == STD_ON))
/**********************************************************************************************************************
 *  Mirror_DestChannelProtocolAsr_QueueNewElement()
 *********************************************************************************************************************/
/*! \brief          Function creates a new queue element
 *  \details        -
 *  \param[in,out]  destChannelCtx      Context of the destination channel
 *  \param[in]      newElement          Buffer for the new queue element
 *  \param[in]      payload             Data to store in the queue
 *  \param[in]      payloadLength       Length of the data
 *  \param[in]      frameId             Frame Id
 *  \param[in]      frameIdLength       Length of the frame Id
 *  \param[in]      networkId           Network Id
 *  \param[in]      metaData            Meta data for the network state
 *  \param[in]      networkState        Current source network state
 *  \param[in]      useNewElement       Flag that indicates if a new queue element must be used
 *  \return         Length of the new queue element
 *  \pre            Module is initialized.
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \config         This service is only available if MIRROR_DESTINATION_CHANNEL_IP == STD_ON and
 *                  MIRROR_DESTINATION_CHANNEL_PROTOCOL_AUTOSAR == STD_ON.
 *********************************************************************************************************************/
FUNC(uint16, MIRROR_CODE) Mirror_DestChannelProtocolAsr_QueueNewElement(Mirror_DestChannelIpContextType* destChannelCtx, 
                                                                        uint8* newElement, const uint8* payload, uint8 payloadLength,
                                                                        uint32 frameId, uint8 frameIdLength, uint8 networkId,
                                                                        uint8 metaData, uint8 networkState, boolean useNewElement);
#endif /* ((MIRROR_DESTINATION_CHANNEL_IP == STD_ON) && (MIRROR_DESTINATION_CHANNEL_PROTOCOL_AUTOSAR == STD_ON)) */

#if ((MIRROR_DESTINATION_CHANNEL_IP == STD_ON) && (MIRROR_DESTINATION_CHANNEL_PROTOCOL_AUTOSAR == STD_ON))
/**********************************************************************************************************************
 *  Mirror_DestChannelProtocolAsr_QueueFinalizeElement()
 *********************************************************************************************************************/
/*! \brief          Function to finalize a queue element
 *  \details        Function is used before queue element is transmitted.
 *  \param[in,out]  element  The queue element
 *  \param[in]      length   Length information for the element header
 *  \pre            Module is initialized.
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \config         This service is only available if MIRROR_DESTINATION_CHANNEL_IP == STD_ON and
 *                  MIRROR_DESTINATION_CHANNEL_PROTOCOL_AUTOSAR == STD_ON.
 *********************************************************************************************************************/
FUNC(void, MIRROR_CODE) Mirror_DestChannelProtocolAsr_QueueFinalizeElement(uint8* element, uint16 length);
#endif /* ((MIRROR_DESTINATION_CHANNEL_IP == STD_ON) && (MIRROR_DESTINATION_CHANNEL_PROTOCOL_AUTOSAR == STD_ON)) */

# define MIRROR_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e{451} */

#endif /* MIRROR_DESTCHANNELPROTOCOLASR_H */

/**********************************************************************************************************************
 *  END OF FILE: Mirror_DestChannelProtocolAsr.h
 *********************************************************************************************************************/
