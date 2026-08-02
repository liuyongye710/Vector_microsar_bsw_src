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
/*!     \file     Mirror_DestChannelProtocolVector.h
 *      \brief    Mirror destination channel protocol (Vector) header file
 *
 *      \details  Header of destination channel protocol (Vector) implementation
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
#if !defined (MIRROR_DESTCHANNELPROTOCOLVECTOR_H)
# define MIRROR_DESTCHANNELPROTOCOLVECTOR_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Mirror_Int.h"

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
# define MIRROR_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e{451} */

#if ((MIRROR_DESTINATION_CHANNEL_IP == STD_ON) && (MIRROR_DESTINATION_CHANNEL_PROTOCOL_VECTOR == STD_ON))
/**********************************************************************************************************************
 *  Mirror_DestChannelProtocolVector_QueueUseNewElement()
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
 *                  MIRROR_DESTINATION_CHANNEL_PROTOCOL_VECTOR == STD_ON.
 *********************************************************************************************************************/
FUNC(boolean, MIRROR_CODE) Mirror_DestChannelProtocolVector_QueueUseNewElement(Mirror_DestChannelIpContextType* destChannelCtx, uint8 length);
#endif /* ((MIRROR_DESTINATION_CHANNEL_IP == STD_ON) && (MIRROR_DESTINATION_CHANNEL_PROTOCOL_VECTOR == STD_ON)) */

#if ((MIRROR_DESTINATION_CHANNEL_IP == STD_ON) && (MIRROR_DESTINATION_CHANNEL_PROTOCOL_VECTOR == STD_ON))
/**********************************************************************************************************************
 *  Mirror_DestChannelProtocolVector_QueueNewElement()
 *********************************************************************************************************************/
/*! \brief          Function creates a new queue element
 *  \details        -
 *  \param[in,out]  destChannelCtx      Context of the destination channel
 *  \param[in]      newElement          Buffer for the new queue element
 *  \param[in]      payload             Data to store in the queue
 *  \param[in]      payloadLength       Length of the data
 *  \param[in]      frameId             Frame Id
 *  \param[in]      networkId           Network Id
 *  \param[in]      metaData            Meta data for the network state
 *  \param[in]      useNewElement       Flag that indicates if a new queue element must be used
 *  \param[in]      startTime           Time when the mirroring was started.
 *  \return         Length of the new queue element
 *  \pre            Module is initialized.
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \config         This service is only available if MIRROR_DESTINATION_CHANNEL_IP == STD_ON and
 *                  MIRROR_DESTINATION_CHANNEL_PROTOCOL_VECTOR == STD_ON.
 *********************************************************************************************************************/
FUNC(uint16, MIRROR_CODE) Mirror_DestChannelProtocolVector_QueueNewElement(Mirror_DestChannelIpContextType* destChannelCtx, 
                                                                        uint8* newElement, const uint8* payload, uint8 payloadLength,
                                                                        uint32 frameId, uint8 networkId, uint8 metaData,
                                                                        boolean useNewElement, StbM_TimeStampType startTime);
#endif /* ((MIRROR_DESTINATION_CHANNEL_IP == STD_ON) && (MIRROR_DESTINATION_CHANNEL_PROTOCOL_VECTOR == STD_ON)) */

#if ((MIRROR_DESTINATION_CHANNEL_IP == STD_ON) && (MIRROR_DESTINATION_CHANNEL_PROTOCOL_VECTOR == STD_ON))
/**********************************************************************************************************************
 *  Mirror_DestChannelProtocolVector_QueueFinalizeElement()
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
 *                  MIRROR_DESTINATION_CHANNEL_PROTOCOL_VECTOR == STD_ON.
 *********************************************************************************************************************/
FUNC(void, MIRROR_CODE) Mirror_DestChannelProtocolVector_QueueFinalizeElement(uint8* element, uint16 length);
#endif /* ((MIRROR_DESTINATION_CHANNEL_IP == STD_ON) && (MIRROR_DESTINATION_CHANNEL_PROTOCOL_VECTOR == STD_ON)) */

# define MIRROR_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e{451} */

#endif /* MIRROR_DESTCHANNELPROTOCOLVECTOR_H */

/**********************************************************************************************************************
 *  END OF FILE: Mirror_DestChannelProtocolVector.h
 *********************************************************************************************************************/
