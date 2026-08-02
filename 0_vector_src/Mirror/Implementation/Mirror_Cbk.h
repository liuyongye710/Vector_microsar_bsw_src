/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2019 Vector Informatik GmbH.                                                     All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/*!     \file:  Mirror_Cbk.h
 *      \brief: Callback header
 *
 *      \details:  Header of Callback implementation of the Bus Mirroring.
 *********************************************************************************************************************/
 /**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *********************************************************************************************************************/
 
#if !defined (MIRROR_CBK_H)
# define MIRROR_CBK_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Mirror_Cfg.h"
#include "Mirror_Lcfg.h"
#include "Mirror_PBcfg.h"

#if (MIRROR_SOURCE_CHANNEL_CAN == STD_ON)
# include "Can_GeneralTypes.h"
#endif /* (MIRROR_SOURCE_CHANNEL_CAN == STD_ON) */

#if (MIRROR_SOURCE_CHANNEL_LIN == STD_ON)
# include "LinIf.h"
#endif /* (MIRROR_SOURCE_CHANNEL_LIN == STD_ON) */

#if (MIRROR_SOURCE_CHANNEL_FLEXRAY == STD_ON)
# include "FrIf.h"
#endif /* (MIRROR_SOURCE_CHANNEL_FLEXRAY == STD_ON) */

 /**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
 /*============================================== MIRROR_START_SEC_CODE =============================================*/
# define MIRROR_START_SEC_CODE
/*lint -save -esym(961, 19.1) */
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e{451} */
/*lint -restore */

/**********************************************************************************************************************
 *  Mirror_RxIndication
 *********************************************************************************************************************/
/*! \brief        Indicates the reception of a Mirror PDU from the PduR.
 *  \details      This is only a dummy function which is needed by PduR.
 *  \param[in]    rxPduId         ID of the received N-PDU.
 *  \param[in]    pduInfoPtr      Contains the length (SduLength) of the received PDU and a pointer to a buffer
 *                                (SduDataPtr) containing the PDU.
 *  \pre          Module is initialized.
 *  \context      TASK|ISR
 *  \reentrant    TRUE for different rxPduIds.
 *  \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(void, MIRROR_CODE) Mirror_RxIndication(PduIdType rxPduId,
                                            P2CONST(PduInfoType, AUTOMATIC, MIRROR_APPL_DATA) pduInfoPtr);

/**********************************************************************************************************************
 *  Mirror_TxConfirmation
 *********************************************************************************************************************/
/*! \brief       Confirms the successful transmission of a Mirror PDU by the PduR.
 *  \details     -
 *  \param[in]   TxPduId         ID of the I-PDU that has been transmitted.
 *  \pre         Module is initialized.
 *  \context     TASK|ISR
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(void, MIRROR_CODE) Mirror_TxConfirmation(PduIdType TxPduId);

/**********************************************************************************************************************
 *  Mirror_TriggerTransmit
 *********************************************************************************************************************/
/*! \brief       Within this API, the upper layer module (called module) shall check whether the available data fits 
 *               into the buffer size reported by PfuInfoPtr->SudLength. If it fits, it shall copy its data into the 
 *               buffer provided by PduInfoPtr->SduDataPtr and update the length of the actual copied data in 
 *               PduInfoPtr->SduLength. If not, it returns E_NOT_OK without changing PduInfoPtr.
 *  \details     -
 *  \param[in]   TxPduId      Id of the SDU that is requested to be transmitted.
 *  \param[in]   PduInfoPtr   Contains a pointer to a buffer (SduDataPtr) to where the SDU data shall be copied, 
 *                            and the available buffer size in SduLength. On return, the service will indicate 
 *                            the length of the copied SDU data in SduLength.
 *  \return      E_OK: SDU has been copied and SduLength indicates the number of copied bytes.
 *  \return      E_NOT_OK: No SDU data has been copied. PduInfoPtr must not be used since it may contain Null pointer 
 *                         or point to invalid data.
 *  \pre         Module is initialized.
 *  \context     TASK|ISR
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, MIRROR_CODE) Mirror_TriggerTransmit(PduIdType TxPduId, PduInfoType* PduInfoPtr);

#if (MIRROR_SOURCE_CHANNEL_CAN == STD_ON)
/**********************************************************************************************************************
 *  Mirror_ReportCanFrame()
 *********************************************************************************************************************/
/*! \brief       Reports a received or transmitted CAN frame. 
 *  \details     All received CAN frames that pass the hardware acceptance filter are reported, independent of the 
 *               software filter configuration. Transmitted CAN frames are reported when the transmission is confirmed.
 *  \param[in]   controllerId ID of the CAN controller that received or transmitted the frame.
 *  \param[in]   canId        CAN ID of the CAN frame.
 *  \param[in]   length       Length of the CAN frame.
 *  \param[in]   payload      Content of the CAN frame.
 *  \pre         -
 *  \context     TASK|ISR
 *  \reentrant   TRUE for different controllerIds
 *  \synchronous TRUE
 *  \config      This service is only available if MIRROR_DESTINATION_CHANNEL_CAN == STD_ON.
 *********************************************************************************************************************/
FUNC(void, MIRROR_CODE) Mirror_ReportCanFrame(uint8 controllerId, Can_IdType canId, uint8 length, const uint8* payload);
#endif /* (MIRROR_SOURCE_CHANNEL_CAN == STD_ON) */

#if (MIRROR_SOURCE_CHANNEL_LIN == STD_ON)
/**********************************************************************************************************************
 *  Mirror_ReportLinFrame()
 *********************************************************************************************************************/
/*! \brief       Reports a received or transmitted LIN frame.
 *  \details     -
 *  \param[in]   network ComM channel associated with the LIN channel on which the frame was received or transmitted.
 *  \param[in]   pid     Protected ID of the LIN frame.
 *  \param[in]   pdu     Content of the LIN frame.
 *  \param[in]   status  Rx/Tx status of the frame access through the LIN driver.
 *  \pre         -
 *  \context     TASK|ISR
 *  \reentrant   TRUE for different networks
 *  \synchronous TRUE
 *  \config      This service is only available if MIRROR_SOURCE_CHANNEL_LIN == STD_ON.
 *********************************************************************************************************************/
FUNC(void, MIRROR_CODE) Mirror_ReportLinFrame(NetworkHandleType network, Lin_FramePidType pid, const PduInfoType* pdu, Lin_StatusType status);
#endif /* (MIRROR_SOURCE_CHANNEL_LIN == STD_ON) */

#if (MIRROR_SOURCE_CHANNEL_FLEXRAY == STD_ON)
/**********************************************************************************************************************
 *  Mirror_ReportFlexRayFrame()
 *********************************************************************************************************************/
/*! \brief       Reports a received or transmitted FlexRay frame or a Tx conflict.
 *  \details     -
 *  \param[in]   controllerId  FlexRay controller that received/transmitted the frame.
 *  \param[in]   slotId        Id of the slot in which the received/transmitted frame is located.
 *  \param[in]   cycle         Cycle in which the reception/transmission takes place.
 *  \param[in]   frChannel     FlexRay channels(s) on which the recpetion/transmission takes place.
 *  \param[in]   frame         Content of the FlexRay frame, or NULL when a txConflict is reported.
 *  \param[in]   txConflict    TRUE in case a txConflict has been detected, FALSE otherwise.
 *  \pre         -
 *  \context     TASK|ISR
 *  \reentrant   TRUE for different networks
 *  \synchronous TRUE
 *  \config      This service is only available if MIRROR_SOURCE_CHANNEL_FLEXRAY == STD_ON.
 *********************************************************************************************************************/
FUNC(void, MIRROR_CODE) Mirror_ReportFlexRayFrame(uint8 controllerId, uint16 slotId, uint8 cycle, Fr_ChannelType frChannel, const PduInfoType* frame, boolean txConflict);
#endif /* (MIRROR_SOURCE_CHANNEL_FLEXRAY == STD_ON) */

#if (MIRROR_SOURCE_CHANNEL_FLEXRAY == STD_ON)
/**********************************************************************************************************************
 *  Mirror_ReportFlexRayChannelStatus()
 *********************************************************************************************************************/
/*! \brief       Reports the aggregated channel status for FlexRay channels A and B of a cluster.
 *  \details     The status is encoded as specified in SWS_FR_00558.
 *  \param[in]   clusterId       FlexRay cluster for which the status is reported.
 *  \param[in]   channelAStatus  Status of FlexRay channel A.
 *  \param[in]   channelBStatus  Status of FlexRay channel B.
 *  \pre         -
 *  \context     TASK|ISR
 *  \reentrant   TRUE for different clusterIds.
 *  \synchronous TRUE
 *  \config      This service is only available if MIRROR_SOURCE_CHANNEL_FLEXRAY == STD_ON.
 *********************************************************************************************************************/
FUNC(void, MIRROR_CODE) Mirror_ReportFlexRayChannelStatus(uint8 clusterId, uint16 channelAStatus, uint16 channelBStatus);
#endif /* (MIRROR_SOURCE_CHANNEL_FLEXRAY == STD_ON) */

# define MIRROR_STOP_SEC_CODE
/*lint -save -esym(961, 19.1) */
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e{451} */
/*lint -restore */
/*============================================== MIRROR_STOP_SEC_CODE ==============================================*/

#endif /* MIRROR_CBK_H */

/**********************************************************************************************************************
 *  END OF FILE: Mirror_Cbk.h
 *********************************************************************************************************************/
