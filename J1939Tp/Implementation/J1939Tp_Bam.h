/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2021 Vector Informatik GmbH.                                                     All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  J1939Tp_Bam.h
 *       Module:  J1939 Transport Layer
 *
 *  Description:  Header of the BAM sub-module of the SAE J1939 Transport Layer module.
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *********************************************************************************************************************/

#if !(defined J1939TP_BAM_H)
# define J1939TP_BAM_H

# if (J1939TP_BAM_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  INTERNAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/*============================================== J1939TP_START_SEC_CODE =============================================*/
#  define J1939TP_START_SEC_CODE
/*lint -save -esym(961, 19.1) */
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*lint -restore */

#  if (J1939TP_BAM_TX_ENABLED == STD_ON)
/************************************************************************************************************
 *  J1939Tp_BamTransmit()
 ***********************************************************************************************************/
/*! \brief       Creates BAM frame
 *  \details     Creates the BAM frame according to its structure and is called by J1939Tp_Transmit.
 *  \param[in]   txSduIdx   ID of the J1939Tp N-SDU to be transmitted.
 *  \param[in]   info       Pointer to J1939Tp N-SDU structure.
 *  \return      E_NOT_OK - Creation failed, e.g. when the requested transmission would use a channel that is currently active
 *  \return      E_OK     - BAM frame has been created
 *  \pre         The info parameter and its field SduDataPtr must not be NULL.
 *  \context     TASK|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \config      J1939TP_BAM_TX_ENABLED
 *  \trace       SPEC-2167314
 *  \spec
 *    requires   txSduIdx < J1939Tp_GetSizeOfTxSdu();
 *  \endspec
 */
#   if (J1939TP_INVALIDHNDOFTXSDU == STD_ON)
/*!
 *  \spec
 *    requires   !J1939Tp_IsInvalidHndOfTxSdu(txSduIdx);
 *  \endspec
 */
#   endif
/*********************************************************************************************************************/
FUNC(Std_ReturnType, J1939TP_CODE) J1939Tp_BamTransmit(PduIdType txSduIdx,
                                                       P2CONST(PduInfoType, AUTOMATIC, J1939TP_APPL_DATA) info);
#  endif


#  if (J1939TP_BAM_TX_ENABLED == STD_ON)
/************************************************************************************************************
 *  J1939Tp_BamTxConfirmation()
 ***********************************************************************************************************/
/*! \brief       Confirms BAM transmission
 *  \details     Confirms the successful BAM transmission by the CanIf.
 *               Is called by the J1939Tp_TxConfirmation after successful transmission of a J1939Tp Tx N-PDU.
 *  \param[in]   txSduIdx    ID of the J1939Tp N-SDU that has been transmitted.
 *  \param[in]   txPduType   Type of PDU    range: J1939TP_TPCM_PDUTYPEOFTXPDU, J1939TP_TPDT_PDUTYPEOFTXPDU
 *  \pre         -
 *  \context     TASK|ISR2
 *  \reentrant   TRUE for different sduIdx
 *  \synchronous TRUE
 *  \config      J1939TP_BAM_TX_ENABLED
 *  \spec
 *    requires   txSduIdx < J1939Tp_GetSizeOfTxSdu();
 *  \endspec
 */
#   if (J1939TP_INVALIDHNDOFTXSDU == STD_ON)
/*!
 *  \spec
 *    requires   !J1939Tp_IsInvalidHndOfTxSdu(txSduIdx);
 *  \endspec
 */
#   endif
/*********************************************************************************************************************/
FUNC(void, J1939TP_CODE) J1939Tp_BamTxConfirmation(PduIdType txSduIdx, J1939Tp_PduTypeOfTxPduType txPduType);
#  endif


#  if (J1939TP_BAM_TX_ENABLED == STD_ON)
/************************************************************************************************************
 *  J1939Tp_BamTxMain()
 ***********************************************************************************************************/
/*! \brief       Supervises BAM transmission timeouts
 *  \details     Used for scheduling purposes and timeout supervision of BAM transmissions.
 *  \param[in]   txSduIdx      ID of the J1939Tp N-SDU that has been transmitted.
 *  \pre         -
 *  \context     TASK
 *  \reentrant   TRUE for different txSduIdx
 *  \synchronous TRUE
 *  \config      J1939TP_BAM_TX_ENABLED
 *  \note        The main function must be called cyclically with a timing corresponding to the configured main
 *               function period.
 *  \spec
 *    requires   txSduIdx < J1939Tp_GetSizeOfTxSdu();
 *  \endspec
 */
 #   if (J1939TP_INVALIDHNDOFTXSDU == STD_ON)
/*!
 *  \spec
 *    requires   !J1939Tp_IsInvalidHndOfTxSdu(txSduIdx);
 *  \endspec
 */
#   endif
/*********************************************************************************************************************/
FUNC(void, J1939TP_CODE) J1939Tp_BamTxMain(PduIdType txSduIdx);
#  endif

#  if (J1939TP_BAM_RX_ENABLED == STD_ON)
/************************************************************************************************************
 *  J1939Tp_BamRxIndication()
 ***********************************************************************************************************/
/*! \brief       Forwards to the appropriate PDU type
 *  \details     This function decides which type of PDU is received. That is either a TP.CM or TP.DT
 *  \param[in]   rxPduIdx    ID of the J1939Tp N-PDU that has been transmitted.
 *  \param[in]   info        Contains the length (SduLength) of the received PDU and a pointer to a buffer
 *                                (SduDataPtr) containing the PDU and the MetaData related to this PDU.

 *  \param[in]   rxPduType   Type of PDU    range: J1939TP_TPCM_PDUTYPEOFRXPDU, J1939TP_TPDT_PDUTYPEOFRXPDU
 *  \pre         -
 *  \context     TASK|ISR2
 *  \reentrant   TRUE for different rxPduIdx
 *  \synchronous TRUE
 *  \config      J1939TP_BAM_RX_ENABLED
 *  \trace       SPEC-2167307
 *  \spec
 *    requires   rxPduIdx < J1939Tp_GetSizeOfRxPdu();
 *  \endspec
 */
 #   if (J1939TP_INVALIDHNDOFRXPDU == STD_ON)
/*!
 *  \spec
 *    requires   !J1939Tp_IsInvalidHndOfRxPdu(rxPduIdx);
 *  \endspec
 */
#   endif
/*********************************************************************************************************************/
FUNC(void, J1939TP_CODE) J1939Tp_BamRxIndication(PduIdType rxPduIdx,
                                                 P2CONST(PduInfoType, AUTOMATIC, J1939TP_APPL_DATA) info,
                                                 J1939Tp_PduTypeOfRxPduType rxPduType, uint8 sa, uint8 da);
#  endif

#  if (J1939TP_BAM_RX_ENABLED == STD_ON)
/************************************************************************************************************
 *  J1939Tp_BamRxMain()
 ***********************************************************************************************************/
/*! \brief       Supervises BAM reception timeouts
 *  \details     Used for scheduling purposes and timeout supervision of BAM reception.
 *  \param[in]   rxSduIdx      ID of the J1939Tp N-SDU that has been received.
 *  \pre         -
 *  \context     TASK
 *  \reentrant   TRUE for different rxSduIdx
 *  \synchronous TRUE
 *  \config      J1939TP_BAM_RX_ENABLED
 *  \note        The main function must be called cyclically with a timing corresponding to the configured main
 *               function period.
 *  \spec
 *    requires   rxSduIdx < J1939Tp_GetSizeOfRxSdu();
 *  \endspec
 */
#   if (J1939TP_INVALIDHNDOFRXSDU == STD_ON)
/*!
 *  \spec
 *    requires   !J1939Tp_IsInvalidHndOfRxSdu(rxSduIdx);
 *  \endspec
 */
#   endif
/*********************************************************************************************************************/
FUNC(void, J1939TP_CODE) J1939Tp_BamRxMain(PduIdType rxSduIdx);
#  endif

#  define J1939TP_STOP_SEC_CODE
/*lint -save -esym(961, 19.1) */
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*lint -restore */
/*============================================== J1939TP_STOP_SEC_CODE ==============================================*/

# endif /* (J1939TP_BAM_ENABLED == STD_ON) */

#endif /* !(defined J1939TP_BAM_H) */

/**********************************************************************************************************************
 *  END OF FILE: J1939Tp_Bam.h
 *********************************************************************************************************************/
