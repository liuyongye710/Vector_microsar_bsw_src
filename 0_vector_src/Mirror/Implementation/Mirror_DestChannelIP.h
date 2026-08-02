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
/*!     \file     Mirror_DestChannelIP.h
 *      \brief    Mirror IP destination channel header file
 *
 *      \details  Header of implementation of IP destination channel.
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
#if !defined (MIRROR_DESTCHANNELIP_H)
# define MIRROR_DESTCHANNELIP_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Mirror_Int.h"

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
# define MIRROR_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e{451} */

#if (MIRROR_DESTINATION_CHANNEL_IP == STD_ON)
/**********************************************************************************************************************
 *  Mirror_DestChannelIp_Init()
 *********************************************************************************************************************/
 /*! \brief       Initializes the destination buffers.
  *  \details     Initializes the header and data fields of the destination buffers with their default values.
  *  \param[in]   mirrorCtx General Mirror context
  *  \pre         This function must be called with interrupt disabled.
  *  \context     TASK
  *  \reentrant   FALSE
  *  \synchronous TRUE
  *  \config      This service is only available if MIRROR_DESTINATION_CHANNEL_IP == STD_ON.
  *********************************************************************************************************************/
FUNC(void, MIRROR_CODE) Mirror_DestChannelIp_Init(Mirror_GeneralContextType* mirrorCtx);
#endif /* (MIRROR_DESTINATION_CHANNEL_IP == STD_ON) */

#if (MIRROR_DESTINATION_CHANNEL_IP == STD_ON)
/**********************************************************************************************************************
 *  Mirror_DestChannelIp_MainFunction()
 *********************************************************************************************************************/
/*! \brief       Internal main function for destination channel IP.
 *  \details     Handles Tx Confirmation timeout and max PDU delay timeout.
 *  \pre         Module is initialized.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      This service is only available if MIRROR_DESTINATION_CHANNEL_IP == STD_ON.
 *********************************************************************************************************************/
FUNC(void, MIRROR_CODE)Mirror_DestChannelIp_MainFunction(void);
#endif /* (MIRROR_DESTINATION_CHANNEL_IP == STD_ON) */

#if ((MIRROR_DESTINATION_CHANNEL_IP == STD_ON) && (MIRROR_SOURCE_CHANNEL_CAN == STD_ON))
/**********************************************************************************************************************
 *  Mirror_DestChannelIp_ProcessCanFrame()
 *********************************************************************************************************************/
/*! \brief       Handles the Ip destination channel specific actions to process the incoming CAN frame.
 *  \details     Function is only called for CAN frames that passed the filter.
 *  \param[in]   canId        CAN ID of the CAn frame.
 *  \param[in]   length       Length of the CAn frame.
 *  \param[in]   payload      Content of the CAN frame.
 *  \param[in]   metaData          Meta Data.
 *  \param[in]   networkId         Network Id of the source channel
 *  \param[in]   networkState      State of the source channel
 *  \return      E_OK: The frame was successful queued.
 *  \return      E_NOT_OK: The frame is lost.
 *  \pre         Module is initialized.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      This service is only available if MIRROR_DESTINATION_CHANNEL_IP == STD_ON AND
                 MIRROR_SOURCE_CHANNEL_CAN == STD_ON.
 *********************************************************************************************************************/
FUNC(Std_ReturnType, MIRROR_CODE) Mirror_DestChannelIp_ProcessCanFrame(uint32 canId, uint8 length, const uint8* payload,
                                                                       uint8 metaData, uint8 networkId, uint8 networkState);
#endif /* ((MIRROR_DESTINATION_CHANNEL_IP == STD_ON) && (MIRROR_SOURCE_CHANNEL_CAN == STD_ON)) */

#if ((MIRROR_DESTINATION_CHANNEL_IP == STD_ON) && (MIRROR_SOURCE_CHANNEL_CAN == STD_ON))
/**********************************************************************************************************************
* Mirror_DestChannelIp_ProcessCanStatus()
**********************************************************************************************************************/
/*! \brief       Function handles the current state of a source network CAN.
*  \details     -
*  \param[in]   metaData          Meta data of the network
*  \param[in]   networkId         Id of the network
*  \param[in]   networkState      State of the network
*  \pre         Module is initialized.
*  \context     TASK
*  \reentrant   FALSE
*  \synchronous TRUE
*  \config      This service is only available if MIRROR_DESTINATION_CHANNEL_IP == STD_ON AND
*               MIRROR_SOURCE_CHANNEL_CAN == STD_ON.
*********************************************************************************************************************/
FUNC(void, MIRROR_CODE) Mirror_DestChannelIp_ProcessCanStatus(uint8 metaData, uint8 networkId, uint8 networkState);
#endif /* ((MIRROR_DESTINATION_CHANNEL_IP == STD_ON) && (MIRROR_SOURCE_CHANNEL_CAN == STD_ON)) */

#if ((MIRROR_DESTINATION_CHANNEL_IP == STD_ON) && (MIRROR_SOURCE_CHANNEL_LIN == STD_ON))
/**********************************************************************************************************************
 *  Mirror_DestChannelIp_ProcessLinFrame()
 *********************************************************************************************************************/
/*! \brief       Handles the Ip destination channel specific actions to process the incoming LIN frame.
 *  \details     Function is only called for LIN frames that passed the filter.
 *  \param[in]   canId             CAN ID of the frame.
 *  \param[in]   length            Length of the frame.
 *  \param[in]   payload           Content of the frame.
 *  \param[in]   metaData          Meta Data.
 *  \param[in]   networkId         Network Id of the source channel
 *  \param[in]   networkState      State of the source channel
 *  \return      E_OK: The frame was successful queued.
 *  \return      E_NOT_OK: The frame is lost.
 *  \pre         Module is initialized.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      This service is only available if MIRROR_DESTINATION_CHANNEL_IP == STD_ON AND
                 MIRROR_SOURCE_CHANNEL_LIN == STD_ON.
 *********************************************************************************************************************/
FUNC(Std_ReturnType, MIRROR_CODE) Mirror_DestChannelIp_ProcessLinFrame(uint8 id, uint8 length, const uint8* payload,
                                                                       uint8 metaData, uint8 networkId, uint8 networkState);
#endif /* ((MIRROR_DESTINATION_CHANNEL_IP == STD_ON) && (MIRROR_SOURCE_CHANNEL_LIN == STD_ON)) */

#if ((MIRROR_DESTINATION_CHANNEL_IP == STD_ON) && (MIRROR_SOURCE_CHANNEL_LIN == STD_ON))
/**********************************************************************************************************************
* Mirror_DestChannelIp_ProcessLinStatus()
**********************************************************************************************************************/
/*! \brief      Function checks the state for a given LIN source channel.
*  \details     -
*  \param[in]   metaData          Meta data of the network
*  \param[in]   networkId         Id of the network
*  \param[in]   networkState      State of the network
*  \pre         Module is initialized.
*  \context     TASK
*  \reentrant   FALSE
*  \synchronous TRUE
*  \config      This service is only available if MIRROR_DESTINATION_CHANNEL_IP == STD_ON AND
*               MIRROR_SOURCE_CHANNEL_LIN == STD_ON.
*********************************************************************************************************************/
FUNC(void, MIRROR_CODE) Mirror_DestChannelIp_ProcessLinStatus(uint8 metaData, uint8 networkId, uint8 networkState);
#endif /* ((MIRROR_DESTINATION_CHANNEL_IP == STD_ON) && (MIRROR_SOURCE_CHANNEL_LIN == STD_ON)) */

#if ((MIRROR_DESTINATION_CHANNEL_IP == STD_ON) && (MIRROR_SOURCE_CHANNEL_FLEXRAY == STD_ON))
/**********************************************************************************************************************
 *  Mirror_DestChannelIp_ProcessFlexRayFrame()
 *********************************************************************************************************************/
/*! \brief       Handles the Ip destination channel specific actions to process the incoming FlexRay frame.
 *  \details     Function is only called for FlexRay frames that passed the filter.
 *  \param[in]   frameId           Frame Id.
 *  \param[in]   frame             Payload and length of the frame.
 *  \param[in]   metaData          Meta Data.
 *  \param[in]   networkId         Network Id of the source channel
 *  \param[in]   networkState      State of the source channel
 *  \return      E_OK: The frame was successful queued.
 *  \return      E_NOT_OK: The frame is lost.
 *  \pre         Module is initialized.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      This service is only available if MIRROR_DESTINATION_CHANNEL_IP == STD_ON AND
                 MIRROR_SOURCE_CHANNEL_FLEXRAY == STD_ON.
 *********************************************************************************************************************/
FUNC(Std_ReturnType, MIRROR_CODE) Mirror_DestChannelIp_ProcessFlexRayFrame(uint32 frameId, const PduInfoType* frame,
                                                                           uint8 metaData, uint8 networkId,
                                                                           uint8 networkState);
#endif /* ((MIRROR_DESTINATION_CHANNEL_IP == STD_ON) && (MIRROR_SOURCE_CHANNEL_LIN == STD_ON)) */

#if ((MIRROR_DESTINATION_CHANNEL_IP == STD_ON) && (MIRROR_SOURCE_CHANNEL_FLEXRAY == STD_ON))
/**********************************************************************************************************************
* Mirror_DestChannelIp_ProcessFlexRayStatus()
**********************************************************************************************************************/
/*! \brief      Function checks the state for a given FlexRay source channel.
*  \details     -
*  \param[in]   metaData          Meta data of the network
*  \param[in]   networkId         Id of the network
*  \param[in]   networkState      State of the network
*  \pre         Module is initialized.
*  \context     TASK
*  \reentrant   FALSE
*  \synchronous TRUE
*  \config      This service is only available if MIRROR_DESTINATION_CHANNEL_IP == STD_ON AND
*               MIRROR_SOURCE_CHANNEL_FLEXRAY == STD_ON.
*********************************************************************************************************************/
FUNC(void, MIRROR_CODE) Mirror_DestChannelIp_ProcessFlexRayStatus(uint8 metaData, uint8 networkId, uint8 networkState);
#endif /* ((MIRROR_DESTINATION_CHANNEL_IP == STD_ON) && (MIRROR_SOURCE_CHANNEL_FLEXRAY == STD_ON)) */

#if (MIRROR_DESTINATION_CHANNEL_IP == STD_ON)
/**********************************************************************************************************************
 *  Mirror_DestChannelIp_TxConfirmation()
 *********************************************************************************************************************/
/*! \brief       Confirms the successful transmission of a Mirror PDU on a IP channel by the PduR.
 *  \details     Trigger the transmission of the next frame.
 *  \pre         Module is initialized.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      This service is only available if MIRROR_DESTINATION_CHANNEL_CAN == STD_ON.
 *********************************************************************************************************************/
FUNC(void, MIRROR_CODE) Mirror_DestChannelIp_TxConfirmation(void);
#endif /* (MIRROR_DESTINATION_CHANNEL_IP == STD_ON) */

#if (MIRROR_DESTINATION_CHANNEL_IP == STD_ON)
/**********************************************************************************************************************
 *  Mirror_DestChannelIp_TriggerTransmit
 *********************************************************************************************************************/
/*! \brief       Within this API, the upper layer module (called module) shall check whether the available data fits 
 *               into the buffer size reported by PfuInfoPtr->SudLength. If it fits, it shall copy its data into the 
 *               buffer provided by PduInfoPtr->SduDataPtr and update the length of the actual copied data in 
 *               PduInfoPtr->SduLength. If not, it returns E_NOT_OK without changing PduInfoPtr.
 *  \details     -
 *  \param[in]   PduInfoPtr   Contains a pointer to a buffer (SduDataPtr) to where the SDU data shall be copied, 
 *                            and the available buffer size in SduLength. On return, the service will indicate 
 *                            the length of the copied SDU data in SduLength.
 *  \return      E_OK: SDU has been copied and SduLength indicates the number of copied bytes.
 *  \return      E_NOT_OK: No SDU data has been copied. PduInfoPtr must not be used since it may contain Null pointer
 *                         or point to invalid data.
 *  \pre         Module is initialized.
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \context     TASK
 *  \config      This service is only available if MIRROR_DESTINATION_CHANNEL_CAN == STD_ON.
 *********************************************************************************************************************/
FUNC(Std_ReturnType, MIRROR_CODE) Mirror_DestChannelIp_TriggerTransmit(PduInfoType* PduInfoPtr);
#endif /* (MIRROR_DESTINATION_CHANNEL_IP == STD_ON) */

# define MIRROR_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e{451} */

#endif /* MIRROR_DESTCHANNELIP_H */

/**********************************************************************************************************************
 *  END OF FILE: Mirror_DestChannelIP.h
 *********************************************************************************************************************/
