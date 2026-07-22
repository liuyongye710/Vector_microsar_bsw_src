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
/*!     \file     Mirror_DestChannel.h
 *      \brief    Mirror destination channel header file
 *
 *      \details  Header of destination channel implementation
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
#if !defined (MIRROR_DESTCHANNEL_H)
# define MIRROR_DESTCHANNEL_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Mirror_Int.h"

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
# define MIRROR_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e{451} */

#if ((MIRROR_DESTINATION_CHANNEL_IP == STD_ON) && ((MIRROR_DESTINATION_CHANNEL_PROTOCOL_AUTOSAR == STD_ON) || (MIRROR_DESTINATION_CHANNEL_PROTOCOL_VECTOR == STD_ON)))
/**********************************************************************************************************************
 *  Mirror_DestChannel_GetTime()
 *********************************************************************************************************************/
/*! \brief       Returns the current time.
 *  \details     -
 *  \param[out]  timeStamp Buffer for timestamp
 *  \return      E_OK: Returned timestamp is valid
 *  \return      E_NOT_OK: Returned timestamp is not valid.
 *  \pre         Module is initialized.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      This service is only available if MIRROR_DESTINATION_CHANNEL_IP == STD_ON and
 *               MIRROR_DESTINATION_CHANNEL_PROTOCOL_AUTOSAR == STD_ON or
 *               MIRROR_DESTINATION_CHANNEL_PROTOCOL_VECTOR == STD_ON.
 *********************************************************************************************************************/
FUNC(Std_ReturnType, MIRROR_CODE) Mirror_DestChannel_GetTime(StbM_TimeStampType* timeStamp);
#endif /* ((MIRROR_DESTINATION_CHANNEL_IP == STD_ON) && ((MIRROR_DESTINATION_CHANNEL_PROTOCOL_AUTOSAR == STD_ON) || (MIRROR_DESTINATION_CHANNEL_PROTOCOL_VECTOR == STD_ON))) */

#if ((MIRROR_DESTINATION_CHANNEL_IP == STD_ON) && ((MIRROR_DESTINATION_CHANNEL_PROTOCOL_AUTOSAR == STD_ON) || (MIRROR_DESTINATION_CHANNEL_PROTOCOL_VECTOR == STD_ON)))
/**********************************************************************************************************************
 *  Mirror_DestChannel_GetDataTimeStamp()
 *********************************************************************************************************************/
/*! \brief       Returns the relative time for the data element.
 *  \details     -
 *  \param[in]   baseTimeStamp Base time stamp of the queue element
 *  \param[out]  dataTime Time for the new data element
 *  \return      E_OK: Returned timestamp is valid
 *  \return      E_NOT_OK: Returned timestamp is not valid.
 *  \pre         Module is initialized.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      This service is only available if MIRROR_DESTINATION_CHANNEL_IP == STD_ON and
 *               MIRROR_DESTINATION_CHANNEL_PROTOCOL_AUTOSAR == STD_ON or
 *               MIRROR_DESTINATION_CHANNEL_PROTOCOL_VECTOR == STD_ON.
 *********************************************************************************************************************/
FUNC(Std_ReturnType, MIRROR_CODE) Mirror_DestChannel_GetDataTimeStamp(StbM_TimeStampType baseTimeStamp, uint16* dataTime);
#endif /* ((MIRROR_DESTINATION_CHANNEL_IP == STD_ON) && ((MIRROR_DESTINATION_CHANNEL_PROTOCOL_AUTOSAR == STD_ON) || (MIRROR_DESTINATION_CHANNEL_PROTOCOL_VECTOR == STD_ON))) */

#if ((MIRROR_DESTINATION_CHANNEL_IP == STD_ON) && ((MIRROR_DESTINATION_CHANNEL_PROTOCOL_AUTOSAR == STD_ON) || (MIRROR_DESTINATION_CHANNEL_PROTOCOL_VECTOR == STD_ON)))
/**********************************************************************************************************************
 *  Mirror_DestChannel_Swap16()
 *********************************************************************************************************************/
/*! \brief       Function converts the given value from host byte order to network byte order.
 *  \details     Can be used for two byte values.
 *  \param[in]   value      Value to convert.
 *  \param[out]  destBuffer Buffer for the converted value.
 *  \return      E_NOT_OK - Function has been called with invalid parameters.
 *  \return      E_OK - success
 *  \pre         Module is initialized.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      This service is only available if MIRROR_DESTINATION_CHANNEL_IP == STD_ON and
 *               MIRROR_DESTINATION_CHANNEL_PROTOCOL_AUTOSAR == STD_ON or
 *               MIRROR_DESTINATION_CHANNEL_PROTOCOL_VECTOR == STD_ON.
 *********************************************************************************************************************/
FUNC(void, MIRROR_CODE) Mirror_DestChannel_Swap16(uint16 value, P2VAR(uint8, AUTOMATIC, MIRROR_APPL_DATA) destBuffer);
#endif /* ((MIRROR_DESTINATION_CHANNEL_IP == STD_ON) && ((MIRROR_DESTINATION_CHANNEL_PROTOCOL_AUTOSAR == STD_ON) || (MIRROR_DESTINATION_CHANNEL_PROTOCOL_VECTOR == STD_ON))) */

#if ((MIRROR_DESTINATION_CHANNEL_IP == STD_ON) && ((MIRROR_DESTINATION_CHANNEL_PROTOCOL_AUTOSAR == STD_ON) || (MIRROR_DESTINATION_CHANNEL_PROTOCOL_VECTOR == STD_ON)))
/**********************************************************************************************************************
 *  Mirror_DestChannel_Swap32()
 *********************************************************************************************************************/
/*! \brief       Function converts the given value from host byte order to network byte order.
 *  \details     Can be used for four byte values.
 *  \param[in]   value      Value to convert.
 *  \param[out]  destBuffer Buffer for the converted value.
 *  \return      E_NOT_OK - Function has been called with invalid parameters.
 *  \return      E_OK - success
 *  \pre         Module is initialized.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      This service is only available if MIRROR_DESTINATION_CHANNEL_IP == STD_ON and
 *               MIRROR_DESTINATION_CHANNEL_PROTOCOL_AUTOSAR == STD_ON or
 *               MIRROR_DESTINATION_CHANNEL_PROTOCOL_VECTOR == STD_ON.
 *********************************************************************************************************************/
FUNC(void, MIRROR_CODE) Mirror_DestChannel_Swap32(uint32 value, P2VAR(uint8, AUTOMATIC, MIRROR_APPL_DATA) destBuffer);
#endif /* ((MIRROR_DESTINATION_CHANNEL_IP == STD_ON) && ((MIRROR_DESTINATION_CHANNEL_PROTOCOL_AUTOSAR == STD_ON) || (MIRROR_DESTINATION_CHANNEL_PROTOCOL_VECTOR == STD_ON))) */

/**********************************************************************************************************************
 *  Mirror_DestChannel_Transmit()
 *********************************************************************************************************************/
/*! \brief         Function transmits a PDU on the destination channel.
 *  \details       Function is used from IP and CAN destination channel.+
 *  \param[in,out] mirrorCtx Mirror context.
 *  \param[in]     mirrorPdu  PDU to transmit.
 *  \param[in]     id         Tx Pdu Id of the current destination channel.
 *  \return        E_NOT_OK - function has been called with invalid parameters.
 *  \return        E_OK - success
 *  \pre           Module is initialized.
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
  *********************************************************************************************************************/
FUNC(Std_ReturnType, MIRROR_CODE) Mirror_DestChannel_Transmit(Mirror_GeneralContextType* mirrorCtx, const PduInfoType* mirrorPdu, PduIdType id);

# define MIRROR_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e{451} */

#endif /* MIRROR_DESTCHANNEL_H */

/**********************************************************************************************************************
 *  END OF FILE: Mirror_DestChannel.h
 *********************************************************************************************************************/
