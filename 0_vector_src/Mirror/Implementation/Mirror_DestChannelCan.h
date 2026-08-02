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
/*!     \file     Mirror_DestChannelCan.h
 *      \brief    Mirror CAN destination channel header file
 *
 *      \details  Header of implementation of CAN destination channel.
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
#if !defined (MIRROR_DESTCHANNELCAN_H)
# define MIRROR_DESTCHANNELCAN_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Mirror_Int.h"

#if (MIRROR_SOURCE_CHANNEL_CAN == STD_ON)
# include "Can_GeneralTypes.h"
#endif /* (MIRROR_SOURCE_CHANNEL_CAN == STD_ON) */

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
# define MIRROR_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e{451} */

#if (MIRROR_DESTINATION_CHANNEL_CAN == STD_ON)
/**********************************************************************************************************************
 *  Mirror_DestChannelCan_Init()
 *********************************************************************************************************************/
 /*! \brief       Initializes the CAN destination queue.
  *  \details     Initializes all pointer and the queue buffer.
  *  \param[in]   mirrorCtx General Mirror context
  *  \pre         This function must be called with interrupt disabled.
  *  \context     TASK
  *  \reentrant   FALSE
  *  \synchronous TRUE
  *  \config      This service is only available if MIRROR_DESTINATION_CHANNEL_CAN == STD_ON.
  *********************************************************************************************************************/
FUNC(void, MIRROR_CODE) Mirror_DestChannelCan_Init(Mirror_GeneralContextType* mirrorCtx);
#endif /* (MIRROR_DESTINATION_CHANNEL_CAN == STD_ON) */

#if (MIRROR_DESTINATION_CHANNEL_CAN == STD_ON)
/**********************************************************************************************************************
 *  Mirror_DestChannelCan_MainFunction()
 *********************************************************************************************************************/
/*! \brief       Internal main function for destination channel CAN.
 *  \details     Handles Tx Confirmation timeout.
 *  \pre         Module is initialized.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      This service is only available if MIRROR_DESTINATION_CHANNEL_CAN == STD_ON.
 *********************************************************************************************************************/
FUNC(void, MIRROR_CODE)Mirror_DestChannelCan_MainFunction(void);
#endif /* (MIRROR_DESTINATION_CHANNEL_CAN == STD_ON) */

#if ((MIRROR_DESTINATION_CHANNEL_CAN == STD_ON) && (MIRROR_SOURCE_CHANNEL_CAN == STD_ON))
/**********************************************************************************************************************
 *  Mirror_DestChannelCan_ProcessCanFrame()
 *********************************************************************************************************************/
/*! \brief       Handles the CAN destination channel specific actions to process the incoming CAN frame.
 *  \details     Function is only called for CAN frames that passed the filter.
 *  \param[in]   canId        CAN ID of the CAN frame.
 *  \param[in]   length       Length of the CAN frame.
 *  \param[in]   payload      Content of the CAN frame.
 *  \return      E_OK: The frame was successful queued or transmitted.
 *  \return      E_NOT_OK: The frame is lost.
 *  \pre         Module is initialized.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      This service is only available if MIRROR_DESTINATION_CHANNEL_CAN == STD_ON and 
 *               MIRROR_SOURCE_CHANNEL_CAN == STD_ON or MIRROR_SOURCE_CHANNEL_LIN == STD_ON.
 *********************************************************************************************************************/
FUNC(Std_ReturnType, MIRROR_CODE) Mirror_DestChannelCan_ProcessCanFrame(Can_IdType canId, uint8 length, const uint8* payload);
#endif /* ((MIRROR_DESTINATION_CHANNEL_CAN == STD_ON) && ((MIRROR_SOURCE_CHANNEL_CAN == STD_ON) || (MIRROR_SOURCE_CHANNEL_LIN == STD_ON))) */

#if ((MIRROR_DESTINATION_CHANNEL_CAN == STD_ON) && (MIRROR_SOURCE_CHANNEL_CAN == STD_ON))
/**********************************************************************************************************************
* Mirror_DestChannelCan_ProcessCanStatus()
**********************************************************************************************************************/
/*! \brief      Function handles the current state of a source network CAN.
*  \details     -
*  \param[in]   metaData          Meta data of the network
*  \param[in]   networkId         Id of the network
*  \param[in]   networkState      State of the network
*  \pre         Module is initialized.
*  \context     TASK
*  \reentrant   FALSE
*  \synchronous TRUE
*  \config      This service is only available if MIRROR_DESTINATION_CHANNEL_CAN == STD_ON AND
*               MIRROR_SOURCE_CHANNEL_CAN == STD_ON.
*********************************************************************************************************************/
FUNC(void, MIRROR_CODE) Mirror_DestChannelCan_ProcessCanStatus(uint8 metaData, uint8 networkId, uint8 networkState);
#endif /* ((MIRROR_DESTINATION_CHANNEL_CAN == STD_ON) && (MIRROR_SOURCE_CHANNEL_CAN == STD_ON)) */

#if ((MIRROR_DESTINATION_CHANNEL_CAN == STD_ON) && (MIRROR_SOURCE_CHANNEL_LIN == STD_ON))
/**********************************************************************************************************************
 *  Mirror_DestChannelCan_ProcessLinFrame()
 *********************************************************************************************************************/
/*! \brief       Handles the CAN destination channel specific actions to process the incoming LIN frame.
 *  \details     Function is only called for LIN frames that passed the filter.
 *  \param[in]   linId         LIN Id of the frame.
 *  \param[in]   canId         ID of the frame.
 *  \param[in]   length        Length of the frame.
 *  \param[in]   payload       Content of the frame.
 *  \param[in]   metaData      Meta Data.
 *  \param[in]   networkId     Network Id of the source channel
 *  \param[in]   networkState  State of the source channel
 *  \return      E_OK: The frame was successful queued or transmitted.
 *  \return      E_NOT_OK: The frame is lost.
 *  \pre         Module is initialized.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      This service is only available if MIRROR_DESTINATION_CHANNEL_CAN == STD_ON AND
 *               MIRROR_SOURCE_CHANNEL_LIN == STD_ON.
 *********************************************************************************************************************/
FUNC(Std_ReturnType, MIRROR_CODE) Mirror_DestChannelCan_ProcessLinFrame(uint8 linId, uint32 canId, uint8 length, const uint8* payload,
                                                                        uint8 metaData, uint8 networkId, uint8 networkState);
#endif /* ((MIRROR_DESTINATION_CHANNEL_CAN == STD_ON) && (MIRROR_SOURCE_CHANNEL_LIN == STD_ON)) */

#if ((MIRROR_DESTINATION_CHANNEL_CAN == STD_ON) && (MIRROR_SOURCE_CHANNEL_LIN == STD_ON))
/**********************************************************************************************************************
* Mirror_DestChannelCan_ProcessLinStatus()
**********************************************************************************************************************/
/*! \brief      Function handles the current state of a source network LIN.
*  \details     -
*  \param[in]   metaData          Meta data of the network
*  \param[in]   networkId         Id of the network
*  \param[in]   networkState      State of the network
*  \pre         Module is initialized.
*  \context     TASK
*  \reentrant   FALSE
*  \synchronous TRUE
*  \config      This service is only available if MIRROR_DESTINATION_CHANNEL_CAN == STD_ON AND
*               MIRROR_SOURCE_CHANNEL_LIN == STD_ON.
*********************************************************************************************************************/
FUNC(void, MIRROR_CODE) Mirror_DestChannelCan_ProcessLinStatus(uint8 metaData, uint8 networkId, uint8 networkState);
#endif /* ((MIRROR_DESTINATION_CHANNEL_CAN == STD_ON) && (MIRROR_SOURCE_CHANNEL_LIN == STD_ON)) */

#if (MIRROR_DESTINATION_CHANNEL_CAN == STD_ON)
/**********************************************************************************************************************
 *  Mirror_DestChannelCan_TxConfirmation()
 *********************************************************************************************************************/
/*! \brief       Confirms the successful transmission of a Mirror PDU on a CAN channel by the PduR.
 *  \details     Trigger the transmission of the next frame for CAN-CAN mirroring.
 *  \pre         Module is initialized.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      This service is only available if MIRROR_DESTINATION_CHANNEL_CAN == STD_ON.
 *********************************************************************************************************************/
FUNC(void, MIRROR_CODE) Mirror_DestChannelCan_TxConfirmation(void);
#endif /* (MIRROR_DESTINATION_CHANNEL_CAN == STD_ON) */

#if (MIRROR_DESTINATION_CHANNEL_CAN == STD_ON)
/**********************************************************************************************************************
 *  Mirror_DestChannelCan_TriggerTransmit
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
FUNC(Std_ReturnType, MIRROR_CODE) Mirror_DestChannelCan_TriggerTransmit(PduInfoType* PduInfoPtr);
#endif /* (MIRROR_DESTINATION_CHANNEL_CAN == STD_ON) */

# define MIRROR_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e{451} */

#endif /* MIRROR_DESTCHANNELCAN_H */

/**********************************************************************************************************************
 *  END OF FILE: Mirror_DestChannelCan.h
 *********************************************************************************************************************/
