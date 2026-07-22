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
 *         File:  J1939Tp_Cmdt.h
 *       Module:  J1939 Transport Layer
 *
 *  Description:  Header of the CMDT sub-module of the SAE J1939 Transport Layer module.
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *********************************************************************************************************************/
 
/**********************************************************************************************************************
 *  MISRA / PClint JUSTIFICATIONS
 *********************************************************************************************************************/
/* *INDENT-OFF* */

/* PRQA S 0292 EOF */ /* MD_MSR_Dir1.1 */ 

/* *INDENT-ON* */

#if !(defined J1939TP_CMDT_H)
# define J1939TP_CMDT_H

# if (J1939TP_CMDT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  INTERNAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/*============================================== J1939TP_START_SEC_CODE =============================================*/
#  define J1939TP_START_SEC_CODE
/*lint -save -esym(961, 19.1) */
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*lint -restore */

#  if (J1939TP_CMDT_TX_ENABLED == STD_ON)
/************************************************************************************************************
 *  J1939Tp_CmdtTransmit()
 ***********************************************************************************************************/
/*! \brief       Initiates transmission of a CMDT N-SDU.
 *  \details     Creates the Cmdt frame according to its structure and is called by J1939Tp_Transmit.
 *  \param[in]   txSduIdx   ID of the J1939Tp N-SDU to be transmitted.
 *  \param[in]   info       Pointer to J1939Tp N-SDU structure.
 *  \return      E_NOT_OK - Creation failed, e.g. when the requested transmission would use a channel that is currently active
 *  \return      E_OK     - Cmdt frame has been created
 *  \pre         The info parameter and its field SduDataPtr must not be NULL.
 *  \context     TASK|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \config      J1939TP_CMDT_TX_ENABLED
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
FUNC(Std_ReturnType, J1939TP_CODE) J1939Tp_CmdtTransmit(PduIdType txSduIdx,
                                                        P2CONST(PduInfoType, AUTOMATIC, J1939TP_APPL_DATA) info);
#  endif

#  if (J1939TP_CMDT_TX_ENABLED == STD_ON)
/************************************************************************************************************
 *  J1939Tp_CmdtTxMain()
 ***********************************************************************************************************/
/*! \brief       Supervises Cmdt transmission timeouts
 *  \details     Used for scheduling purposes and timeout supervision of Cmdt transmissions.
 *  \param[in]   txSduIdx      ID of the J1939Tp N-SDU that has been transmitted.
 *  \pre         -
 *  \context     TASK
 *  \reentrant   TRUE for different txSduIdx
 *  \synchronous TRUE
 *  \config      J1939TP_CMDT_TX_ENABLED
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
FUNC(void, J1939TP_CODE) J1939Tp_CmdtTxMain(PduIdType txSduIdx);
#  endif

#  if (J1939TP_CMDT_RX_ENABLED == STD_ON)
/************************************************************************************************************
 *  J1939Tp_CmdtRxMain()
 ***********************************************************************************************************/
/*! \brief       Supervises Cmdt reception timeouts
 *  \details     Used for scheduling purposes and timeout supervision of Cmdt reception.
 *  \param[in]   rxSduIdx      ID of the J1939Tp N-SDU that has been received.
 *  \pre         -
 *  \context     TASK
 *  \reentrant   TRUE for different rxSduIdx
 *  \synchronous TRUE
 *  \config      J1939TP_CMDT_RX_ENABLED
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
FUNC(void, J1939TP_CODE) J1939Tp_CmdtRxMain(PduIdType rxSduIdx);
#  endif

/************************************************************************************************************
 *  J1939Tp_CmdtTxConfirmation()
 ***********************************************************************************************************/
/*! \brief       Confirms Cmdt transmission
 *  \details     Confirms the successful Cmdt transmission by the CanIf.
 *               Is called by the J1939Tp_TxConfirmation after successful transmission of a J1939Tp Tx N-PDU.
 *  \param[in]   sduIdx      ID of the J1939Tp N-SDU that has been transmitted.
 *  \param[in]   txPduType   Type of PDU    range: J1939TP_TPCM_PDUTYPEOFTXPDU, J1939TP_TPDT_PDUTYPEOFTXPDU
 *  \param[in]   sduType     Type of SDU    range: J1939TP_NSDU_CMDT_TX, J1939TP_NSDU_CMDT_RX
 *  \pre         -
 *  \context     TASK|ISR2
 *  \reentrant   TRUE for different sduIdx
 *  \synchronous TRUE
 *  \config      J1939TP_CMDT_TX_ENABLED
 */
#  if ((J1939TP_CMDT_TX_ENABLED == STD_ON) && (J1939TP_CMDT_RX_ENABLED == STD_ON))
/*!
 *  \spec
 *    requires    ((sduType == J1939TP_NSDU_CMDT_TX) && (sduIdx < J1939Tp_GetSizeOfTxSdu())) || ((sduType != J1939TP_NSDU_CMDT_TX) && (sduIdx < J1939Tp_GetSizeOfRxSdu()));
 *  \endspec
 */
#   if (J1939TP_INVALIDHNDOFTXSDU == STD_ON)
/*!
 *  \spec
 *    requires   (sduType == J1939TP_NSDU_CMDT_TX) && (!J1939Tp_IsInvalidHndOfTxSdu(sduIdx));
 *  \endspec
 */
#   endif
#   if (J1939TP_INVALIDHNDOFRXSDU == STD_ON)
/*!
 *  \spec
 *    requires   (sduType != J1939TP_NSDU_CMDT_TX) && (!J1939Tp_IsInvalidHndOfRxSdu(sduIdx));
 *  \endspec
 */
#   endif
#  elif (J1939TP_CMDT_TX_ENABLED == STD_ON)
/*!
 *  \spec
 *    requires    sduIdx < J1939Tp_GetSizeOfTxSdu();
 *  \endspec
 */
#   if (J1939TP_INVALIDHNDOFTXSDU == STD_ON)
/*!
 *  \spec
 *    requires   !J1939Tp_IsInvalidHndOfTxSdu(sduIdx);
 *  \endspec
 */
#   endif
#  elif (J1939TP_CMDT_RX_ENABLED == STD_ON)
/*!
 *  \spec
 *    requires    sduIdx < J1939Tp_GetSizeOfRxSdu();
 *  \endspec
 */
#   if (J1939TP_INVALIDHNDOFRXSDU == STD_ON)
 /*!
 *  \spec
 *    requires   !J1939Tp_IsInvalidHndOfRxSdu(sduIdx);
 *  \endspec
 */
#   endif
#  endif
/***********************************************************************************************************/
FUNC(void, J1939TP_CODE) J1939Tp_CmdtTxConfirmation(PduIdType sduIdx, J1939Tp_PduTypeOfTxPduType txPduType,
                                                    J1939Tp_NSduType sduType);

/************************************************************************************************************
 *  J1939Tp_CmdtRxIndication()
 ***********************************************************************************************************/
/*! \brief       Indicates Cmdt reception
 *  \details     Indicates the Cmdt reception of an N-PDU from the CanIf.
 *  \param[in]   rxPduIdx    ID of the J1939Tp N-PDU that has been transmitted.
 *  \param[in]   info        Pointer to J1939Tp N-PDU structure.
 *  \param[in]   rxPduType   Type of PDU    range: J1939TP_TPCM_PDUTYPEOFRXPDU, J1939TP_TPDT_PDUTYPEOFRXPDU
 *  \pre         -
 *  \context     TASK|ISR2
 *  \reentrant   TRUE for different rxPduIdx
 *  \synchronous TRUE
 *  \config      J1939TP_CMDT_RX_ENABLED
 *  \trace       SPEC-2167307
 ***********************************************************************************************************/
FUNC(void, J1939TP_CODE) J1939Tp_CmdtRxIndication(PduIdType rxPduIdx,
                                                  P2CONST(PduInfoType, AUTOMATIC, J1939TP_APPL_DATA) info,
                                                  J1939Tp_PduTypeOfRxPduType rxPduType, uint8 sa, uint8 da);

#  define J1939TP_STOP_SEC_CODE
/*lint -save -esym(961, 19.1) */
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*lint -restore */
/*============================================== J1939TP_STOP_SEC_CODE ==============================================*/

# endif /* (J1939TP_CMDT_ENABLED == STD_ON) */

#endif /* !(defined J1939TP_CMDT_H) */

/**********************************************************************************************************************
 *  END OF FILE: J1939Tp_Cmdt.h
 *********************************************************************************************************************/
