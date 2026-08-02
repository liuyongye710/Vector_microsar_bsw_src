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
 *         File:  J1939Tp_Cmdt.c
 *       Module:  J1939 Transport Layer
 *
 *  Description:  Implementation of the CMDT sub-module of the SAE J1939 Transport Layer module.
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

/**********************************************************************************************************************
 *  MISRA / PClint JUSTIFICATIONS
 *********************************************************************************************************************/
/* *INDENT-OFF* */

/* PRQA S 0779 EOF */ /* MD_MSR_Rule5.2 */
/* PRQA S 0292 EOF */ /* MD_MSR_Dir1.1 */ 

/* *INDENT-ON* */


/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

#define J1939TP_CMDT_C

#include "J1939Tp_Cfg.h"

#if (J1939TP_CMDT_ENABLED == STD_ON)
# include "J1939Tp.h"
# include "J1939Tp_Int.h"
# include "J1939Tp_Cmdt.h"

/*! \trace SPEC-2167286 */
# include "PduR_J1939Tp.h"
/*! \trace SPEC-2167287 */
# include "CanIf.h"

# include "SchM_J1939Tp.h"


/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/

/* Vendor specific BSW module version information */
# define J1939TP_MAJOR_SOURCE_VERSION        (4u)
# define J1939TP_MINOR_SOURCE_VERSION        (1u)
# define J1939TP_PATCH_SOURCE_VERSION        (0u)

/* Check the version of J1939Tp module header file */
# if ((J1939TP_SW_MAJOR_VERSION != J1939TP_MAJOR_SOURCE_VERSION) || (J1939TP_SW_MINOR_VERSION != J1939TP_MINOR_SOURCE_VERSION) || (J1939TP_SW_PATCH_VERSION != J1939TP_PATCH_SOURCE_VERSION))
#  error "Vendor specific version numbers of J1939Tp_Cmdt.c and J1939Tp.h are inconsistent"
# endif


/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/*============================================== J1939TP_START_SEC_CODE =============================================*/
# define J1939TP_START_SEC_CODE
/*lint -save -esym(961, 19.1) */
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*lint -restore */

# if ((J1939TP_CMDT_RX_ENABLED == STD_ON) && (J1939TP_RXRETRYSUPPORTOFRXCHANNEL == STD_ON))
/**********************************************************************************************************************
*  J1939Tp_CmdtIncrementAndCheckRetryAttempts()
*********************************************************************************************************************/
/*! \brief      Increment and check the retry attempts
*  \details     This function increments the retry attempts and either aborts the connection if 
*               J1939TP_MAX_RETRY_ATTEMPTS reached or requests the missed data packets.
*  \param[in]   rxSduIdx               ID of the SDU
*  \pre         -
*  \context     TASK|ISR2
*  \reentrant   TRUE
*  \synchronous TRUE
*  \config      J1939TP_RXRETRYSUPPORTOFRXCHANNEL
*  \spec
*    requires   rxSduIdx < J1939Tp_GetSizeOfRxSdu();
*  \endspec
 */
#  if (J1939TP_INVALIDHNDOFRXSDU == STD_ON)
/*!
 *  \spec
 *    requires   !J1939Tp_IsInvalidHndOfRxSdu(rxSduIdx);
 *  \endspec
 */
#  endif
/*********************************************************************************************************************/
J1939TP_LOCAL_INLINE void J1939Tp_CmdtIncrementAndCheckRetryAttempts(PduIdType rxSduIdx);
# endif

# if (J1939TP_CMDT_TX_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  J1939Tp_CmdtInternalTransmitTpCmRts()
 *********************************************************************************************************************/
/*! \brief       Transmits a TP.CM_RTS frame
 *  \details     This function transmits a TP.CM frame of type request to send (RTS) for transport protocol CMDT.
 *  \param[in]   txSduIdx               ID of the SDU to be transmitted
 *  \pre         -
 *  \context     TASK|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \config      J1939TP_CMDT_TX_ENABLED
 *  \trace       CREQ-107402, CREQ-107399
 *  \spec
 *    requires   txSduIdx < J1939Tp_GetSizeOfTxSdu();
 *  \endspec
 */
#  if (J1939TP_INVALIDHNDOFTXSDU == STD_ON)
/*!
 *  \spec
 *    requires   !J1939Tp_IsInvalidHndOfTxSdu(txSduIdx);
 *  \endspec
 */
#  endif
/*********************************************************************************************************************/
J1939TP_LOCAL_INLINE void J1939Tp_CmdtInternalTransmitTpCmRts(PduIdType txSduIdx);
# endif

# if (J1939TP_CMDT_RX_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  J1939Tp_CmdtInternalTransmitTpCmCts()
 *********************************************************************************************************************/
/*! \brief       Transmits a TP.CM_CTS frame
 *  \details     This function transmits a TP.CM frame of type clear to send (CTS) for transport protocol CMDT.
 *  \param[in]   rxSduIdx               ID of the SDU to be transmitted
 *  \pre         -
 *  \context     TASK|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \config      J1939TP_CMDT_RX_ENABLED
 *  \trace       CREQ-107402, CREQ-107399
 *  \spec
 *    requires   rxSduIdx < J1939Tp_GetSizeOfRxSdu();
 *  \endspec
 */
#  if (J1939TP_INVALIDHNDOFRXSDU == STD_ON)
/*!
 *  \spec
 *    requires   !J1939Tp_IsInvalidHndOfRxSdu(rxSduIdx);
 *  \endspec
 */
#  endif
/*********************************************************************************************************************/
J1939TP_LOCAL_INLINE void J1939Tp_CmdtInternalTransmitTpCmCts(PduIdType rxSduIdx);
# endif

# if (J1939TP_CMDT_RX_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  J1939Tp_CmdtInternalTransmitTpCmEomack()
 *********************************************************************************************************************/
/*! \brief       Transmits a TP.CM_EOMACK frame
 *  \details     This function transmits a TP.CM frame of type End Of Message Acknowledge (EOMACK).
 *  \param[in]   rxSduIdx               ID of the SDU to be transmitted
 *  \pre         -
 *  \context     TASK|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \config      J1939TP_CMDT_RX_ENABLED
 *  \trace       CREQ-107402, CREQ-107399
 *  \spec
 *    requires   rxSduIdx < J1939Tp_GetSizeOfRxSdu();
 *  \endspec
  */
#  if (J1939TP_INVALIDHNDOFRXSDU == STD_ON)
/*!
 *  \spec
 *    requires   !J1939Tp_IsInvalidHndOfRxSdu(rxSduIdx);
 *  \endspec
 */
#  endif
/*********************************************************************************************************************/
J1939TP_LOCAL_INLINE void J1939Tp_CmdtInternalTransmitTpCmEomack(PduIdType rxSduIdx);
# endif

# if (J1939TP_CMDT_TX_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  J1939Tp_CmdtInternalTransmitTpAbortTx()
 *********************************************************************************************************************/
/*! \brief       Transmits an Abort frame
 *  \details     This function transmits an Abort frame to close a Tx connection.
 *  \param[in]   txSduIdx               ID of the SDU to be transmitted
 *  \pre         -
 *  \context     TASK|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \config      J1939TP_CMDT_TX_ENABLED
 *  \spec
 *    requires   txSduIdx < J1939Tp_GetSizeOfTxSdu();
 *  \endspec
 */
#  if (J1939TP_INVALIDHNDOFTXSDU == STD_ON)
/*!
 *  \spec
 *    requires   !J1939Tp_IsInvalidHndOfTxSdu(txSduIdx);
 *  \endspec
 */
#  endif
/*********************************************************************************************************************/
J1939TP_LOCAL_INLINE void J1939Tp_CmdtInternalTransmitTpAbortTx(PduIdType txSduIdx);
# endif

# if (J1939TP_CMDT_RX_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  J1939Tp_CmdtInternalTransmitTpAbortRx()
 *********************************************************************************************************************/
/*! \brief       Transmits an Abort frame
 *  \details     This function transmits an Abort frame to close an Rx connection.
 *  \param[in]   rxSduIdx               ID of the SDU to be transmitted
 *  \pre         -
 *  \context     TASK|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \config      J1939TP_CMDT_TX_ENABLED
 *  \spec
 *    requires   rxSduIdx < J1939Tp_GetSizeOfRxSdu();
 *  \endspec
 */
#  if (J1939TP_INVALIDHNDOFRXSDU == STD_ON)
/*!
 *  \spec
 *    requires   !J1939Tp_IsInvalidHndOfRxSdu(rxSduIdx);
 *  \endspec
 */
#  endif
/*********************************************************************************************************************/
J1939TP_LOCAL_INLINE void J1939Tp_CmdtInternalTransmitTpAbortRx(PduIdType rxSduIdx);
# endif

# if (J1939TP_CMDT_TX_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  J1939Tp_CmdtInternalTransmitTpDt()
 *********************************************************************************************************************/
/*! \brief       This function transmits a TP.DT frame
 *  \details     This function transmits a TP.DT frame of transport protocol CMDT.
 *  \param[in]   txSduIdx               ID of the SDU to be transmitted
 *  \pre         -
 *  \context     TASK|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \config      J1939TP_CMDT_TX_ENABLED
 *  \trace       CREQ-107402, CREQ-107399
 *  \spec
 *    requires   txSduIdx < J1939Tp_GetSizeOfTxSdu();
 *  \endspec
 */
#  if (J1939TP_INVALIDHNDOFTXSDU == STD_ON)
/*!
 *  \spec
 *    requires   !J1939Tp_IsInvalidHndOfTxSdu(txSduIdx);
 *  \endspec
 */
#  endif
/*********************************************************************************************************************/
J1939TP_LOCAL_INLINE void J1939Tp_CmdtInternalTransmitTpDt(PduIdType txSduIdx);
# endif

# if (J1939TP_CMDT_TX_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  J1939Tp_CmdtInternalTransmit_SearchConflictingTxChannel()
 *********************************************************************************************************************/
/*! \brief       Searches for an already established Tx connection
 *  \details     This function searches for a Tx connection that is already in use.
 *  \param[in]   txSduIdx             ID of the SDU to be transmitted
 *  \param[in]   txChannelIdx         ID of the given Tx channel
 *  \param[in]   sa                   Source address
 *  \param[in]   da                   Destination address
 *  \return      TRUE         A connection is already established
 *  \return      FALSE        No conflicts found
 *  \pre         -
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      J1939TP_CMDT_TX_ENABLED
 *********************************************************************************************************************/
J1939TP_LOCAL_INLINE boolean
J1939Tp_CmdtInternalTransmit_SearchConflictingTxChannel(PduIdType txSduIdx,
                                                        J1939Tp_TxChannelChannelIdxOfTxSduType txChannelIdx, uint8 sa,
                                                        uint8 da);
# endif

# if (J1939TP_CMDT_RX_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  J1939Tp_CmdtInternalRxIndication_AllocateRxChannel()
 *********************************************************************************************************************/
/*! \brief       Allocates a new connection
 *  \details     This function searches for a free connection for the incoming PDU
 *  \param[in]   rxPduIdx             ID of the incoming PDU
 *  \param[in]   sa                   Source address
 *  \param[in]   da                   Destination address
 *  \param[in]   pgn                  Parameter group number
 *  \param[out]  allocatedRxSduIdx    Pointer to found SDU
 *  \return      TRUE         A connection has been allocated
 *  \return      FALSE        There is no free connection available
 *  \pre         -
 *  \context     TASK|ISR2
 *  \reentrant   TRUE for different rxPduIdx
 *  \synchronous TRUE
 *  \config      J1939TP_CMDT_RX_ENABLED
 *  \spec
 *    requires   rxPduIdx < J1939Tp_GetSizeOfRxPdu();
 *  \endspec
 */
#  if (J1939TP_INVALIDHNDOFRXPDU == STD_ON)
/*!
 *  \spec
 *    requires   !J1939Tp_IsInvalidHndOfRxPdu(rxPduIdx);
 *  \endspec
 */
#  endif
/*********************************************************************************************************************/
J1939TP_LOCAL_INLINE boolean
J1939Tp_CmdtInternalRxIndication_AllocateRxChannel(PduIdType rxPduIdx, uint8 sa, uint8 da, uint32 pgn,
                                                   J1939Tp_RxSduRxNSduIdxOfRxChannelRxNSduType * allocatedRxSduIdx);
# endif

# if (J1939TP_CMDT_RX_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  J1939Tp_CmdtInternalRxIndication_ReceiveTpCmRts()
 *********************************************************************************************************************/
/*! \brief       Reception of a TP.CM_RTS frame
 *  \details     This function gets the data of a TP.CM frame of type request to send (RTS).
 *  \param[in]   rxSduIdx           ID of the SDU
 *  \param[in]   info               Contains the length (SduLength) of the received PDU and a pointer to a buffer
 *                                  (SduDataPtr) containing the PDU and the MetaData related to this PDU.
 *  \param[in]   sa                 Source address
 *  \param[in]   da                 Destination address
 *  \param[in]   size               Total message size
 *  \pre         -
 *  \context     TASK|ISR2
 *  \reentrant   TRUE for different rxSduIdx
 *  \synchronous TRUE
 *  \config      J1939TP_CMDT_RX_ENABLED
 *  \trace       CREQ-107401, CREQ-107399
 *  \spec
 *    requires   rxSduIdx < J1939Tp_GetSizeOfRxSdu();
 *  \endspec
 */
#  if (J1939TP_INVALIDHNDOFRXSDU == STD_ON)
/*!
 *  \spec
 *    requires   !J1939Tp_IsInvalidHndOfRxSdu(rxSduIdx);
 *  \endspec
 */
#  endif
/*********************************************************************************************************************/
J1939TP_LOCAL_INLINE void J1939Tp_CmdtInternalRxIndication_ReceiveTpCmRts(J1939Tp_RxSduRxNSduIdxOfRxChannelRxNSduType
                                                                          rxSduIdx, P2CONST(PduInfoType, AUTOMATIC,
                                                                                          J1939TP_APPL_DATA) info,
                                                                          uint8 sa, uint8 da, uint16 size);
# endif

# if (J1939TP_CMDT_TX_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  J1939Tp_CmdtInternalRxIndication_FindActiveTxChannel()
 *********************************************************************************************************************/
/*! \brief       Finds active Tx connection
 *  \details     This function finds an active Tx connection for the given rxPduIdx and sa.
 *  \param[in]   rxPduIdx             ID of the incoming PDU
 *  \param[in]   sa                   Source address
 *  \param[in]   da                   Destination address
 *  \param[out]  txSduIdx             Pointer to found SDU
 *  \return      TRUE         An active connection has been found
 *  \return      FALSE        No active connection
 *  \pre         -
 *  \context     TASK|ISR2
 *  \reentrant   TRUE for different rxPduIdx
 *  \synchronous TRUE
 *  \config      J1939TP_CMDT_TX_ENABLED
 *********************************************************************************************************************/
J1939TP_LOCAL_INLINE boolean
J1939Tp_CmdtInternalRxIndication_FindActiveTxChannel(PduIdType rxPduIdx, uint8 sa, uint8 da,
                                                     J1939Tp_TxSduTxNSduIdxOfTxChannelTxNSduType * txSduIdx);
# endif

# if (J1939TP_CMDT_TX_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  J1939Tp_CmdtInternalRxIndication_ReceiveTpCmCts()
 *********************************************************************************************************************/
/*! \brief       Reception of a TP.CM_CTS frame
 *  \details     This function gets the data of a TP.CM frame of type clear to send (CTS).
 *  \param[in]   txSduIdx           ID of the SDU
 *  \param[in]   info               Contains the length (SduLength) of the received PDU and a pointer to a buffer
 *                                  (SduDataPtr) containing the PDU and the MetaData related to this PDU.
 *  \param[in]   pgn                Parameter group number
 *  \pre         -
 *  \context     TASK|ISR2
 *  \reentrant   TRUE for different txSduIdx
 *  \synchronous TRUE
 *  \config      J1939TP_CMDT_TX_ENABLED
 *  \trace       CREQ-107401, CREQ-107399
 *  \spec
 *    requires   txSduIdx < J1939Tp_GetSizeOfTxSdu();
 *  \endspec
 */
#  if (J1939TP_INVALIDHNDOFTXSDU == STD_ON)
/*!
 *  \spec
 *    requires   !J1939Tp_IsInvalidHndOfTxSdu(txSduIdx);
 *  \endspec
 */
#  endif
/*********************************************************************************************************************/
J1939TP_LOCAL_INLINE void J1939Tp_CmdtInternalRxIndication_ReceiveTpCmCts(J1939Tp_TxSduTxNSduIdxOfTxChannelTxNSduType
                                                                          txSduIdx, CONSTP2CONST(PduInfoType, AUTOMATIC,
                                                                                               J1939TP_APPL_DATA) info,
                                                                          uint32 pgn);
# endif

# if (J1939TP_CMDT_TX_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  J1939Tp_CmdtInternalRxIndication_ReceiveTpCmEomack()
 *********************************************************************************************************************/
/*! \brief       Reception of a TP.CM_EOMACK frame
 *  \details     This function gets the data of a TP.CM frame of type End Of Message Acknowledge (EOMACK).
 *  \param[in]   txSduIdx           ID of the SDU
 *  \param[in]   info               Contains the length (SduLength) of the received PDU and a pointer to a buffer
 *                                  (SduDataPtr) containing the PDU and the MetaData related to this PDU.
 *  \param[in]   pgn                Parameter group number
 *  \pre         -
 *  \context     TASK|ISR2
 *  \reentrant   TRUE for different txSduIdx
 *  \synchronous TRUE
 *  \config      J1939TP_CMDT_TX_ENABLED
 *  \trace       CREQ-107401, CREQ-107399
 *  \spec
 *    requires   txSduIdx < J1939Tp_GetSizeOfTxSdu();
 *  \endspec
 */
#  if (J1939TP_INVALIDHNDOFTXSDU == STD_ON)
/*!
 *  \spec
 *    requires   !J1939Tp_IsInvalidHndOfTxSdu(txSduIdx);
 *  \endspec
 */
#  endif
/*********************************************************************************************************************/
J1939TP_LOCAL_INLINE void
J1939Tp_CmdtInternalRxIndication_ReceiveTpCmEomack(J1939Tp_TxSduTxNSduIdxOfTxChannelTxNSduType txSduIdx,
                                                   CONSTP2CONST(PduInfoType, AUTOMATIC, J1939TP_APPL_DATA) info,
                                                   uint32 pgn);
# endif

# if (J1939TP_CMDT_RX_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  J1939Tp_CmdtInternalRxIndication_FindActiveRxChannel()
 *********************************************************************************************************************/
/*! \brief       Finds active Rx connection
 *  \details     This function finds an active Rx connection for the given rxPduIdx and sa.
 *  \param[in]   rxPduIdx             ID of the incoming PDU
 *  \param[in]   sa                   Source address
 *  \param[in]   da                   Destination address
 *  \param[out]  rxSduIdx             Pointer to found SDU
 *  \return      TRUE         An active connection has been found
 *  \return      FALSE        No active connection
 *  \pre         -
 *  \context     TASK|ISR2
 *  \reentrant   TRUE for different rxPduIdx
 *  \synchronous TRUE
 *  \config      J1939TP_CMDT_RX_ENABLED
 *********************************************************************************************************************/
J1939TP_LOCAL_INLINE boolean
J1939Tp_CmdtInternalRxIndication_FindActiveRxChannel(PduIdType rxPduIdx, uint8 sa, uint8 da,
                                                     J1939Tp_RxSduRxNSduIdxOfRxChannelRxNSduType * rxSduIdx);
# endif

# if (J1939TP_CMDT_RX_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  J1939Tp_CmdtInternalRxIndication_ReceiveTpAbortRx()
 *********************************************************************************************************************/
/*! \brief       Receives an Abort frame
 *  \details     This function receives an Abort frame to close the Rx connection.
 *  \param[in]   rxSduIdx             ID of the SDU to be transmitted
 *  \param[in]   pgn                  Parameter group number
 *  \pre         -
 *  \context     TASK|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \config      J1939TP_CMDT_RX_ENABLED
 *  \spec
 *    requires   rxSduIdx < J1939Tp_GetSizeOfRxSdu();
 *  \endspec
*/
#  if (J1939TP_INVALIDHNDOFRXSDU == STD_ON)
/*!
 *  \spec
 *    requires   !J1939Tp_IsInvalidHndOfRxSdu(rxSduIdx);
 *  \endspec
 */
#  endif
/*********************************************************************************************************************/
J1939TP_LOCAL_INLINE void J1939Tp_CmdtInternalRxIndication_ReceiveTpAbortRx(J1939Tp_RxSduRxNSduIdxOfRxChannelRxNSduType
                                                                            rxSduIdx, uint32 pgn);
# endif

# if (J1939TP_CMDT_TX_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  J1939Tp_CmdtInternalRxIndication_ReceiveTpAbortTx()
 *********************************************************************************************************************/
/*! \brief       Receives an Abort frame
 *  \details     This function receives an Abort frame to close the Tx connection.
 *  \param[in]   txSduIdx             ID of the SDU to be transmitted
 *  \param[in]   pgn                  Parameter group number
 *  \pre         -
 *  \context     TASK|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \config      J1939TP_CMDT_TX_ENABLED
 *  \spec
 *    requires   txSduIdx < J1939Tp_GetSizeOfTxSdu();
 *  \endspec
 */
#  if (J1939TP_INVALIDHNDOFTXSDU == STD_ON)
/*!
 *  \spec
 *    requires   !J1939Tp_IsInvalidHndOfTxSdu(txSduIdx);
 *  \endspec
 */
#  endif
/*********************************************************************************************************************/
J1939TP_LOCAL_INLINE void J1939Tp_CmdtInternalRxIndication_ReceiveTpAbortTx(J1939Tp_TxSduTxNSduIdxOfTxChannelTxNSduType
                                                                            txSduIdx, uint32 pgn);
# endif

# if (J1939TP_CMDT_RX_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  J1939Tp_CmdtInternalRxIndication_ReceiveTpDt()
 *********************************************************************************************************************/
/*! \brief       Reception of a TP.DT frame
 *  \details     This function gets the data of a TP.DT frame of transport protocol CMDT.
 *  \param[in]   rxSduIdx           ID of the SDU
 *  \param[in]   info               Contains the length (SduLength) of the received PDU and a pointer to a buffer
 *                                  (SduDataPtr) containing the PDU and the MetaData related to this PDU.
 *  \pre         -
 *  \context     TASK|ISR2
 *  \reentrant   TRUE for different rxSduIdx
 *  \synchronous TRUE
 *  \config      J1939TP_CMDT_RX_ENABLED
 *  \trace       CREQ-107401, CREQ-107399
 *  \spec
 *    requires   rxSduIdx < J1939Tp_GetSizeOfRxSdu();
 *  \endspec
 */
#  if (J1939TP_INVALIDHNDOFRXSDU == STD_ON)
/*!
 *  \spec
 *    requires   !J1939Tp_IsInvalidHndOfRxSdu(rxSduIdx);
 *  \endspec
 */
#  endif
/*********************************************************************************************************************/
J1939TP_LOCAL_INLINE void J1939Tp_CmdtInternalRxIndication_ReceiveTpDt(J1939Tp_RxSduRxNSduIdxOfRxChannelRxNSduType
                                                                       rxSduIdx, CONSTP2CONST(PduInfoType, AUTOMATIC,
                                                                                            J1939TP_APPL_DATA) info);
# endif

# define J1939TP_STOP_SEC_CODE
/*lint -save -esym(961, 19.1) */
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*lint -restore */
/*============================================== J1939TP_STOP_SEC_CODE ==============================================*/


/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/*============================================== J1939TP_START_SEC_CODE =============================================*/
# define J1939TP_START_SEC_CODE
/*lint -save -esym(961, 19.1) */
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*lint -restore */

# if ((J1939TP_CMDT_RX_ENABLED == STD_ON) && (J1939TP_RXRETRYSUPPORTOFRXCHANNEL == STD_ON))
/**********************************************************************************************************************
*  J1939Tp_CmdtIncrementAndCheckRetryAttempts()
*********************************************************************************************************************/
/*!
* Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
*/
J1939TP_LOCAL_INLINE void J1939Tp_CmdtIncrementAndCheckRetryAttempts(PduIdType rxSduIdx)
{
  J1939Tp_RxNSduStateType *rxSduState = &J1939Tp_GetRxSduState(J1939Tp_GetRxSduStateIdxOfRxSdu(rxSduIdx));

  /* Increment the retry attempts by one and set the timeout. */
  rxSduState->RetryAttempts = rxSduState->RetryAttempts + 1u; /* VCA_J1939TP_RXSDUSTATE_VIA_RXSDU_CSL03 */
  rxSduState->TimeOut = J1939Tp_GetTime_Tr(); /*!< \trace SPEC-2167340 */ /* VCA_J1939TP_RXSDUSTATE_VIA_RXSDU_CSL03 */

  /* If the maximum amount of retry attempts are reached */
  if (rxSduState->RetryAttempts == J1939TP_MAX_RETRY_ATTEMPTS)
  {
    /* Then request the transmission of an abort frame and set the abort reason and the state
    accordingly. */
    /*! \trace SPEC-2167342 */
    rxSduState->AbortReason = J1939TP_CAR_RETRANSMIT; /* VCA_J1939TP_RXSDUSTATE_VIA_RXSDU_CSL03 */
    /* no protection required - transition from uninterruptible state */
    rxSduState->State = J1939TP_STATE_CMDT_ABORT_BUSY; /* VCA_J1939TP_RXSDUSTATE_VIA_RXSDU_CSL03 */

    J1939Tp_CmdtInternalTransmitTpAbortRx(rxSduIdx);
  }
  /* Otherwise */
  else
  {
    /* Then request the transmission of the connection management frame CTS. */
    J1939Tp_CmdtInternalTransmitTpCmCts(rxSduIdx);
  }
}
# endif


# if (J1939TP_CMDT_TX_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  J1939Tp_CmdtInternalTransmitTpCmRts()
 *********************************************************************************************************************/
/*!
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
J1939TP_LOCAL_INLINE void J1939Tp_CmdtInternalTransmitTpCmRts(PduIdType txSduIdx)
{
  J1939Tp_TxChannelChannelIdxOfTxSduType txChannelIdx = J1939Tp_GetTxChannelChannelIdxOfTxSdu(txSduIdx);
  J1939Tp_SizeOfTxPduType txPduIdx = J1939Tp_GetTxPduTxCmNPduIdxOfTxChannel(txChannelIdx);
  J1939Tp_TxNPduStateType *txPduState = &J1939Tp_GetTxPduState(J1939Tp_GetTxPduStateIdxOfTxPdu(txPduIdx));
  J1939Tp_TxNSduStateType *txSduState = &J1939Tp_GetTxSduState(J1939Tp_GetTxSduStateIdxOfTxSdu(txSduIdx));

  /* If the PDU is not in use. */
  SchM_Enter_J1939Tp_J1939TP_EXCLUSIVE_AREA_TXNPDULOCK();
  if (txPduState->Locked == FALSE)
  {
    /* Lock the PDU and set the initial confirmation timeout value. */
    txPduState->CurrentNSduType = J1939TP_NSDU_CMDT_TX; /* VCA_J1939TP_TXPDUSTATE_VIA_TXSDU_CSL03 */
    txPduState->CurrentNSduId = txSduIdx; /* VCA_J1939TP_TXPDUSTATE_VIA_TXSDU_CSL03 */
    txPduState->ConfTimeout = J1939Tp_GetTxConfTimeout(); /* VCA_J1939TP_TXPDUSTATE_VIA_TXSDU_CSL03 */
    /* protected against concurrent access to the same TP.CM N-PDU */
    txPduState->Locked = TRUE; /* VCA_J1939TP_TXPDUSTATE_VIA_TXSDU_CSL03 */
    SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_TXNPDULOCK();

    {
      /* Fill in the payload data of the Connection Management Request To Send frame. */
      uint32 pgn = (uint32) J1939Tp_GetPGNOfTxSdu(txSduIdx);
      uint8 data[J1939TP_NPDU_LENGTH];
      PduInfoType pdu;
      Std_ReturnType result;

      data[J1939TP_TPCM_CB] = (uint8) J1939TP_CB_RTS;
      data[J1939TP_TPCM_TMS_LO] = J1939Tp_Make_TMS_LO(txSduState->Size);
      data[J1939TP_TPCM_TMS_HI] = J1939Tp_Make_TMS_HI(txSduState->Size);
      data[J1939TP_TPCM_TNOP] = (uint8) txSduState->Packets;
      data[J1939TP_TPCM_MNOP] = txSduState->MaxBlock;
      data[J1939TP_TPCM_PGN_LO] = J1939Tp_Make_PGN_LO(pgn);
      data[J1939TP_TPCM_PGN_MD] = J1939Tp_Make_PGN_MD(pgn);
      data[J1939TP_TPCM_PGN_HI] = J1939Tp_Make_PGN_HI(pgn);
      data[J1939TP_NPDU_SA_POS] = txSduState->Sender;
      data[J1939TP_NPDU_DA_POS] = txSduState->Receiver;
      data[J1939TP_NPDU_PRI_POS] = txSduState->Priority;

      pdu.SduDataPtr = data;
      pdu.SduLength = J1939TP_NPDU_LENGTH;

      /* no protection required - transition from uninterruptible state */
      txSduState->State = J1939TP_STATE_CMDT_RTS_CONF; /* VCA_J1939TP_TXSDUSTATE_VIA_TXSDU_CSL03 */
      /* Request the transmission of the Connection Management frame from the lower layer. */
      result = CanIf_Transmit(J1939Tp_GetPduIdOfTxPdu(txPduIdx), &pdu); /* VCA_J1939TP_FCTCALL_PTR2LOCAL */

      /* If the request was not successful. */
      if (result != E_OK)
      {
        SchM_Enter_J1939Tp_J1939TP_EXCLUSIVE_AREA_TXNSDULOCK();

        /* Set the state back to CMDT RTS frame. */
        if (txSduState->State == J1939TP_STATE_CMDT_RTS_CONF)
        {
          /* no protection required - no further actions related to the locked state */
          txPduState->Locked = FALSE; /* VCA_J1939TP_TXPDUSTATE_VIA_TXSDU_CSL03 */

          /* protected against late Tx confirmation */
          txSduState->State = J1939TP_STATE_CMDT_RTS; /* VCA_J1939TP_TXSDUSTATE_VIA_TXSDU_CSL03 */

          SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_TXNSDULOCK();
        }
        else
        {
          SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_TXNSDULOCK();
        }
      }
    }
  }
  /* Otherwise */
  else
  {
    SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_TXNPDULOCK();

    /* Set the state back to RTS. */
    /* no protection required - transition from uninterruptible state */
    txSduState->State = J1939TP_STATE_CMDT_RTS; /* VCA_J1939TP_TXSDUSTATE_VIA_TXSDU_CSL03 */
  }
} /* J1939Tp_CmdtInternalTransmitTpCmRts */
# endif


# if (J1939TP_CMDT_RX_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  J1939Tp_CmdtInternalTransmitTpCmCts()
 *********************************************************************************************************************/
/*!
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
J1939TP_LOCAL_INLINE void J1939Tp_CmdtInternalTransmitTpCmCts(PduIdType rxSduIdx)
{
  J1939Tp_SizeOfTxPduType txPduIdx = J1939Tp_GetTxPduRxFcNPduIdxOfRxChannel(J1939Tp_GetRxChannelChannelIdxOfRxSdu(rxSduIdx));
  J1939Tp_TxNPduStateType *txPduState = &J1939Tp_GetTxPduState(J1939Tp_GetTxPduStateIdxOfTxPdu(txPduIdx));
  J1939Tp_RxNSduStateType *rxSduState = &J1939Tp_GetRxSduState(J1939Tp_GetRxSduStateIdxOfRxSdu(rxSduIdx));

  /* If the PDU is not in use. */
  SchM_Enter_J1939Tp_J1939TP_EXCLUSIVE_AREA_TXNPDULOCK();
  if (txPduState->Locked == FALSE)
  {
    /* Lock the PDU and set the initial confirmation timeout value. */
    txPduState->CurrentNSduType = J1939TP_NSDU_CMDT_RX; /* VCA_J1939TP_TXPDUSTATE_VIA_RXSDU_CSL03 */
    txPduState->CurrentNSduId = rxSduIdx; /* VCA_J1939TP_TXPDUSTATE_VIA_RXSDU_CSL03 */
    txPduState->ConfTimeout = J1939Tp_GetTxConfTimeout(); /* VCA_J1939TP_TXPDUSTATE_VIA_RXSDU_CSL03 */
    /* protected against concurrent access to the same TP.CM N-PDU */
    txPduState->Locked = TRUE; /* VCA_J1939TP_TXPDUSTATE_VIA_RXSDU_CSL03 */
    SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_TXNPDULOCK();

    {
      /* Fill in the payload data of the Connection Management message Clear To Send frame. */
      /*! \trace SPEC-2167327, SPEC-2167331 */
      uint8 block = J1939Tp_GetRxPacketsPerBlockOfRxChannel(J1939Tp_GetRxChannelChannelIdxOfRxSdu(rxSduIdx));
      uint8 data[J1939TP_NPDU_LENGTH]; /* must stay at the same level as pdu to avoid false QAC warning 3217 */
      PduInfoType pdu;
      uint8 maxblock;
      uint16 blocksize;
      BufReq_ReturnType tpResult = BUFREQ_OK;

      /* If the next block bigger than the remaining amount of packets */
      maxblock = ((uint8) rxSduState->Packets) - rxSduState->Sequence;
      if (block > maxblock)
      {
        /* Then cut the block to this value. */
        block = maxblock;
      }

      /* If it is the last block */
      /*! \trace SPEC-2167327 */
      if (block == maxblock)
      {
        /* Set the size of the remaining payload. */
        blocksize = (uint16) (rxSduState->Size - ((uint32) rxSduState->Sequence * (uint32) J1939TP_TPDT_DATA_SIZE));
      }
      /* Otherwise */
      else
      {
        /* Use the default blocksize */
        blocksize = (uint16) block *(uint16) J1939TP_TPDT_DATA_SIZE;
      }

      /*! \trace SPEC-2167328, SPEC-2167327 */
      /* If there is not enough buffer for the reception of a complete block */
      if (rxSduState->BufSize < blocksize)
      {
        /* Tell the upper layer we wait */
        pdu.SduLength = 0;
        pdu.SduDataPtr = NULL_PTR;
        tpResult = PduR_J1939TpCopyRxData(J1939Tp_GetSduIdOfRxSdu(rxSduIdx), &pdu, &rxSduState->BufSize); /* VCA_J1939TP_FCTCALL_PTR2LOCAL */ /* VCA_J1939TP_RXSDUSTATE_VIA_RXSDU_CSL03 */
      }

      /* If the request was successful, */
      if (tpResult == BUFREQ_OK)
      {
        /* If the buffer is at least as big as the blocksize or the timeout value has almost elapsed */
        if ((rxSduState->BufSize >= blocksize) || (rxSduState->TimeOut <= 1u))

        {
          uint32 pgn = (uint32) J1939Tp_GetPGNOfRxSdu(rxSduIdx); 
          Std_ReturnType result;

          /* If the buffer is at least as big as the blocksize */
          if (rxSduState->BufSize >= blocksize)
          {
            /* Then prepare the Connection Management message CTS. */
            rxSduState->NextBlock = rxSduState->Sequence + block; /* VCA_J1939TP_RXSDUSTATE_VIA_RXSDU_CSL03 */
            data[J1939TP_TPCM_NOP] = block; /*!< \trace SPEC-2167327 */

            data[J1939TP_TPCM_NPN] = rxSduState->Sequence + 1u;
          }
          /* Otherwise the buffer is not big enough */
          else
          {
            /* Then prepare the Connection Management message CTS to signalize waiting. */
            data[J1939TP_TPCM_NOP] = J1939TP_CTS_WAIT; /*!< \trace SPEC-2167329 */
            data[J1939TP_TPCM_NPN] = J1939TP_SNA_VALUE;
          }

          /* Fill in the payload data */
          data[J1939TP_TPCM_CB] = (uint8) J1939TP_CB_CTS;
          data[J1939TP_TPCM_RES4] = J1939TP_SNA_VALUE;
          data[J1939TP_TPCM_RES5] = J1939TP_SNA_VALUE;
          data[J1939TP_TPCM_PGN_LO] = J1939Tp_Make_PGN_LO(pgn);
          data[J1939TP_TPCM_PGN_MD] = J1939Tp_Make_PGN_MD(pgn);
          data[J1939TP_TPCM_PGN_HI] = J1939Tp_Make_PGN_HI(pgn);
          /* Fill in the MetaData. */
          data[J1939TP_NPDU_SA_POS] = rxSduState->Receiver;
          data[J1939TP_NPDU_DA_POS] = rxSduState->Sender;
          data[J1939TP_NPDU_PRI_POS] = rxSduState->Priority;

          pdu.SduDataPtr = data;
          pdu.SduLength = J1939TP_NPDU_LENGTH;

          /* If the buffer is at least as big as the blocksize */
          if (rxSduState->BufSize >= blocksize)
          {
            /* Then set the state to expect the confirmation of the CTS message. */
            /* no protection required - transition from uninterruptible state */
            rxSduState->State = J1939TP_STATE_CMDT_CTS_CONF; /* VCA_J1939TP_RXSDUSTATE_VIA_RXSDU_CSL03 */
          }
          /* Otherwise */
          else
          {
            /* Set the state to expect the confirmation of the CTSWAIT message. */
            /* no protection required - transition from uninterruptible state */
            rxSduState->State = J1939TP_STATE_CMDT_CTSWAIT_CONF; /* VCA_J1939TP_RXSDUSTATE_VIA_RXSDU_CSL03 */
          }

          /* Request the transmission of the CTS message from the lower layer. */
          result = CanIf_Transmit(J1939Tp_GetPduIdOfTxPdu(txPduIdx), &pdu); /* VCA_J1939TP_FCTCALL_PTR2LOCAL */

          /* If the request was not successful. */
          if (result != E_OK)
          {
            /* If a CTSWAIT messsage was requested. */
            SchM_Enter_J1939Tp_J1939TP_EXCLUSIVE_AREA_RXNSDULOCK();
            if (rxSduState->State == J1939TP_STATE_CMDT_CTSWAIT_CONF)
            {
              /* Set the state back to CTSWAIT. */
              /* no protection required - no further actions related to the locked state */
              txPduState->Locked = FALSE;  /* VCA_J1939TP_TXPDUSTATE_VIA_RXSDU_CSL03 */

              /* protected against late Tx confirmation */
              rxSduState->State = J1939TP_STATE_CMDT_CTSWAIT; /* VCA_J1939TP_RXSDUSTATE_VIA_RXSDU_CSL03 */

              SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_RXNSDULOCK();
            }
            /* Or if a CTS message was requested. */
            else if (rxSduState->State == J1939TP_STATE_CMDT_CTS_CONF)
            {
              /* Set the state back to CTS. */
              /* no protection required - no further actions related to the locked state */
              txPduState->Locked = FALSE;  /* VCA_J1939TP_TXPDUSTATE_VIA_RXSDU_CSL03 */

              /* protected against late Tx confirmation */
              rxSduState->State = J1939TP_STATE_CMDT_CTS; /* VCA_J1939TP_RXSDUSTATE_VIA_RXSDU_CSL03 */

              SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_RXNSDULOCK();
            }
            /* Otherwise */
            else
            {
              SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_RXNSDULOCK();
            }
          }
        }
        /* Otherwise the buffer is smaller than the blocksize or the timeout value is greater than 1.  */
        else
        { /* BufSize < blocksize || TimeOut > 1 */
          /* Then unlock the PDU. */
          /* no protection required - no further actions related to the locked state */
          txPduState->Locked = FALSE;   /* VCA_J1939TP_TXPDUSTATE_VIA_RXSDU_CSL03 */

          /* If the state is CTSWAIT_BUSY */
          if (rxSduState->State == J1939TP_STATE_CMDT_CTSWAIT_BUSY)
          {
            /* Then set the state back to CTSWAIT */
            /* no protection required - transition from uninterruptible state */
            rxSduState->State = J1939TP_STATE_CMDT_CTSWAIT; /* VCA_J1939TP_RXSDUSTATE_VIA_RXSDU_CSL03 */
          }
          /* For all other states */
          else
          {
            /* Set the state back to CTS */
            /* no protection required - transition from uninterruptible state */
            rxSduState->State = J1939TP_STATE_CMDT_CTS; /* VCA_J1939TP_RXSDUSTATE_VIA_RXSDU_CSL03 */
          }
        }
      }
      /* Otherwise */
      else
      {
        /* Unlock the PDU and set the abort reason, set the timeout value and request transmission of the abort frame. */
        /*! \trace SPEC-2167311 */
        /* no protection required - no further actions related to the locked state */
        txPduState->Locked = FALSE;  /* VCA_J1939TP_TXPDUSTATE_VIA_RXSDU_CSL03 */
        rxSduState->AbortReason = J1939TP_CAR_RESOURCES; /* VCA_J1939TP_RXSDUSTATE_VIA_RXSDU_CSL03 */
        rxSduState->TimeOut = J1939Tp_GetTime_Tr(); /*!< \trace SPEC-2167340 */ /* VCA_J1939TP_RXSDUSTATE_VIA_RXSDU_CSL03 */
        /* no protection required - transition from uninterruptible state */
        rxSduState->State = J1939TP_STATE_CMDT_ABORT_BUSY; /* VCA_J1939TP_RXSDUSTATE_VIA_RXSDU_CSL03 */

        J1939Tp_CmdtInternalTransmitTpAbortRx(rxSduIdx);
      }
    }
  }
  /* Otherwise the PDU is locked. */
  else
  {
    SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_TXNPDULOCK();

    /* Set the state back to either CTSWAIT or CTS. */
    if (rxSduState->State == J1939TP_STATE_CMDT_CTSWAIT_BUSY)
    {
      /* no protection required - transition from uninterruptible state */
      rxSduState->State = J1939TP_STATE_CMDT_CTSWAIT; /* VCA_J1939TP_RXSDUSTATE_VIA_RXSDU_CSL03 */
    }
    else
    {
      /* no protection required - transition from uninterruptible state */
      rxSduState->State = J1939TP_STATE_CMDT_CTS; /* VCA_J1939TP_RXSDUSTATE_VIA_RXSDU_CSL03 */
    }
  }
} /* J1939Tp_CmdtInternalTransmitTpCmCts */ /* PRQA S 6010, 6030, 6050, 6080 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */
# endif


# if (J1939TP_CMDT_RX_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  J1939Tp_CmdtInternalTransmitTpCmEomack()
 *********************************************************************************************************************/
/*!
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
 */
J1939TP_LOCAL_INLINE void J1939Tp_CmdtInternalTransmitTpCmEomack(PduIdType rxSduIdx)
{
  J1939Tp_SizeOfTxPduType txPduIdx = J1939Tp_GetTxPduRxFcNPduIdxOfRxChannel(J1939Tp_GetRxChannelChannelIdxOfRxSdu(rxSduIdx));
  J1939Tp_TxNPduStateType *txPduState = &J1939Tp_GetTxPduState(J1939Tp_GetTxPduStateIdxOfTxPdu(txPduIdx));
  J1939Tp_RxNSduStateType *rxSduState = &J1939Tp_GetRxSduState(J1939Tp_GetRxSduStateIdxOfRxSdu(rxSduIdx));

  /* If the PDU is not in use. */
  SchM_Enter_J1939Tp_J1939TP_EXCLUSIVE_AREA_TXNPDULOCK();
  if (txPduState->Locked == FALSE)
  {
    /* Lock the PDU and set the initial confirmation timeout value. */
    txPduState->CurrentNSduType = J1939TP_NSDU_CMDT_RX; /* VCA_J1939TP_TXPDUSTATE_VIA_RXSDU_CSL03 */
    txPduState->CurrentNSduId = rxSduIdx; /* VCA_J1939TP_TXPDUSTATE_VIA_RXSDU_CSL03 */
    txPduState->ConfTimeout = J1939Tp_GetTxConfTimeout(); /* VCA_J1939TP_TXPDUSTATE_VIA_RXSDU_CSL03 */
    /* protected against concurrent access to the same TP.CM N-PDU */
    txPduState->Locked = TRUE; /* VCA_J1939TP_TXPDUSTATE_VIA_RXSDU_CSL03 */
    SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_TXNPDULOCK();

    {
      /* Fill in the payload data of the Connection Management message End Of Message Acknowledge. */
      uint32 pgn = (uint32) J1939Tp_GetPGNOfRxSdu(rxSduIdx);
      uint8 data[J1939TP_NPDU_LENGTH];
      PduInfoType pdu;
      Std_ReturnType result;

      data[J1939TP_TPCM_CB] = (uint8) J1939TP_CB_EOMACK;
      data[J1939TP_TPCM_TMS_LO] = J1939Tp_Make_TMS_LO(rxSduState->Size);
      data[J1939TP_TPCM_TMS_HI] = J1939Tp_Make_TMS_HI(rxSduState->Size);
      data[J1939TP_TPCM_TNOP] = (uint8) rxSduState->Packets;
      data[J1939TP_TPCM_RES5] = J1939TP_SNA_VALUE;
      data[J1939TP_TPCM_PGN_LO] = J1939Tp_Make_PGN_LO(pgn);
      data[J1939TP_TPCM_PGN_MD] = J1939Tp_Make_PGN_MD(pgn);
      data[J1939TP_TPCM_PGN_HI] = J1939Tp_Make_PGN_HI(pgn);
      /* Fill in the MetaData. */
      data[J1939TP_NPDU_SA_POS] = rxSduState->Receiver;
      data[J1939TP_NPDU_DA_POS] = rxSduState->Sender;
      data[J1939TP_NPDU_PRI_POS] = rxSduState->Priority;

      pdu.SduDataPtr = data;
      pdu.SduLength = J1939TP_NPDU_LENGTH;

      /* no protection required - transition from uninterruptible state */
      rxSduState->State = J1939TP_STATE_CMDT_EOMACK_CONF; /* VCA_J1939TP_RXSDUSTATE_VIA_RXSDU_CSL03 */
      /* Request the transmission of the Connection Management message from the lower layer. */
      result = CanIf_Transmit(J1939Tp_GetPduIdOfTxPdu(txPduIdx), &pdu); /* VCA_J1939TP_FCTCALL_PTR2LOCAL */

      /* If the request was not successful. */
      if (result != E_OK)
      {
        SchM_Enter_J1939Tp_J1939TP_EXCLUSIVE_AREA_RXNSDULOCK();
        /* Set the state back to EOMACK. */
        if (rxSduState->State == J1939TP_STATE_CMDT_EOMACK_CONF)
        {
          /* no protection required - no further actions related to the locked state */
          txPduState->Locked = FALSE; /* VCA_J1939TP_TXPDUSTATE_VIA_RXSDU_CSL03 */

          /* protected against late Tx confirmation */
          rxSduState->State = J1939TP_STATE_CMDT_EOMACK; /* VCA_J1939TP_RXSDUSTATE_VIA_RXSDU_CSL03 */

          SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_RXNSDULOCK();
        }
        else
        {
          SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_RXNSDULOCK();
        }
      }
    }
  }
  /* Otherwise the PDU is locked. */
  else
  {
    SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_TXNPDULOCK();

    /* Set the state back to EOMACK. */
    /* no protection required - transition from uninterruptible state */
    rxSduState->State = J1939TP_STATE_CMDT_EOMACK; /* VCA_J1939TP_RXSDUSTATE_VIA_RXSDU_CSL03 */
  }
} /* J1939Tp_CmdtInternalTransmitTpCmEomack */
# endif


# if (J1939TP_CMDT_TX_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  J1939Tp_CmdtInternalTransmitTpAbortTx()
 *********************************************************************************************************************/
/*!
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
 *
 *
 *
 */
J1939TP_LOCAL_INLINE void J1939Tp_CmdtInternalTransmitTpAbortTx(PduIdType txSduIdx)
{
  J1939Tp_TxChannelChannelIdxOfTxSduType channelIdx = J1939Tp_GetTxChannelChannelIdxOfTxSdu(txSduIdx);
  J1939Tp_SizeOfTxPduType txPduIdx = J1939Tp_GetTxPduTxCmNPduIdxOfTxChannel(channelIdx);
  J1939Tp_TxNPduStateType *txPduState = &J1939Tp_GetTxPduState(J1939Tp_GetTxPduStateIdxOfTxPdu(txPduIdx));
  J1939Tp_TxNSduStateType *txSduState = &J1939Tp_GetTxSduState(J1939Tp_GetTxSduStateIdxOfTxSdu(txSduIdx));

  /* If the PDU is not in use. */
  SchM_Enter_J1939Tp_J1939TP_EXCLUSIVE_AREA_TXNPDULOCK();
  if (txPduState->Locked == FALSE)
  {
    /* Lock the PDU and set the initial confirmation timeout value. */
    txPduState->CurrentNSduType = J1939TP_NSDU_CMDT_TX; /* VCA_J1939TP_TXPDUSTATE_VIA_TXSDU_CSL03 */
    txPduState->CurrentNSduId = txSduIdx; /* VCA_J1939TP_TXPDUSTATE_VIA_TXSDU_CSL03 */
    txPduState->ConfTimeout = J1939Tp_GetTxConfTimeout(); /* VCA_J1939TP_TXPDUSTATE_VIA_TXSDU_CSL03 */
    /* protected against concurrent access to the same TP.CM N-PDU */
    txPduState->Locked = TRUE; /* VCA_J1939TP_TXPDUSTATE_VIA_TXSDU_CSL03 */
    SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_TXNPDULOCK();

    {
      uint32 pgn = (uint32) J1939Tp_GetPGNOfTxSdu(txSduIdx); 
      uint8 data[J1939TP_NPDU_LENGTH];
      PduInfoType pdu;
      Std_ReturnType result;

      /* Prepare the PDU */
      data[J1939TP_TPCM_CB] = (uint8) J1939TP_CB_ABORT;
      data[J1939TP_TPCM_CAR] = (uint8) txSduState->AbortReason;
      data[J1939TP_TPCM_RES3] = J1939TP_SNA_VALUE;
      data[J1939TP_TPCM_RES4] = J1939TP_SNA_VALUE;
      data[J1939TP_TPCM_RES5] = J1939TP_SNA_VALUE;
      data[J1939TP_TPCM_PGN_LO] = J1939Tp_Make_PGN_LO(pgn);
      data[J1939TP_TPCM_PGN_MD] = J1939Tp_Make_PGN_MD(pgn);
      data[J1939TP_TPCM_PGN_HI] = J1939Tp_Make_PGN_HI(pgn);
      /* Fill in the MetaData. */
      data[J1939TP_NPDU_SA_POS] = txSduState->Sender;
      data[J1939TP_NPDU_DA_POS] = txSduState->Receiver;
      data[J1939TP_NPDU_PRI_POS] = txSduState->Priority;

      pdu.SduDataPtr = data;
      pdu.SduLength = J1939TP_NPDU_LENGTH;

      /* Request the transmission of the abort frame from the lower layer. */
      /* no protection required - transition from uninterruptible state */
      txSduState->State = J1939TP_STATE_CMDT_ABORT_CONF; /* VCA_J1939TP_TXSDUSTATE_VIA_TXSDU_CSL03 */
      result = CanIf_Transmit(J1939Tp_GetPduIdOfTxPdu(txPduIdx), &pdu); /* VCA_J1939TP_FCTCALL_PTR2LOCAL */

      /* If the request was not successful. */
      if (result != E_OK)
      {
        /* Set the state back to abort frame. */
        SchM_Enter_J1939Tp_J1939TP_EXCLUSIVE_AREA_TXNSDULOCK();
        if (txSduState->State == J1939TP_STATE_CMDT_ABORT_CONF)
        {
          /* no protection required - no further actions related to the locked state */
          txPduState->Locked = FALSE; /* VCA_J1939TP_TXPDUSTATE_VIA_TXSDU_CSL03 */

          /* protected against late Tx confirmation */
          txSduState->State = J1939TP_STATE_CMDT_ABORT; /* VCA_J1939TP_TXSDUSTATE_VIA_TXSDU_CSL03 */

          SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_TXNSDULOCK();
        }
        else
        {
          SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_TXNSDULOCK();
        }
      }
#  if (J1939TP_CMDT_RX_ENABLED == STD_ON)
      /* If the request was successful and a receive connection with CMDT is configured */
      else
      {
        J1939Tp_ComMChannelOfTxChannelType comMChannel = J1939Tp_GetComMChannelOfTxChannel(channelIdx);
        PduIdType pairedRxSduIdx;

        /* Iterate over all Rx SDUs to find the corresponding Rx SDU for this Tx SDU. */
        for (pairedRxSduIdx = 0; pairedRxSduIdx < J1939Tp_GetSizeOfRxSdu(); pairedRxSduIdx++)
        {
#   if (J1939TP_INVALIDHNDOFRXSDU == STD_ON)
          if (!J1939Tp_IsInvalidHndOfRxSdu(pairedRxSduIdx))
#   endif
          {
            J1939Tp_RxNSduStateType *pairedRxSduState =
              &J1939Tp_GetRxSduState(J1939Tp_GetRxSduStateIdxOfRxSdu(pairedRxSduIdx));

            if ((J1939Tp_GetComMChannelOfRxChannel(J1939Tp_GetRxChannelChannelIdxOfRxSdu(pairedRxSduIdx)) == comMChannel) && 
                ((pairedRxSduState->State & J1939TP_STATEMASK_CMDT) != J1939TP_STATE_IDLE) &&
                (pairedRxSduState->Sender == txSduState->Receiver) &&
                (pairedRxSduState->Receiver == txSduState->Sender) &&
                (J1939Tp_GetPGNOfRxSdu(pairedRxSduIdx) == pgn))
            {
              /* If the corresponding Rx connection is in state CTS, CSTWAIT, DATA_FIRST, DATA, EOMACK or ABORT */
              SchM_Enter_J1939Tp_J1939TP_EXCLUSIVE_AREA_RXNSDULOCK();
              if ((pairedRxSduState->State == J1939TP_STATE_CMDT_CTS) ||
                  (pairedRxSduState->State == J1939TP_STATE_CMDT_CTSWAIT) ||
                  (pairedRxSduState->State == J1939TP_STATE_CMDT_DATA_FIRST) ||
                  (pairedRxSduState->State == J1939TP_STATE_CMDT_DATA) ||
                  (pairedRxSduState->State == J1939TP_STATE_CMDT_EOMACK) ||
                  (pairedRxSduState->State == J1939TP_STATE_CMDT_ABORT))
              {
                /* protected against concurrent main function invocation or concurrent reception of TP.ConnAbort or
                   TP.DT message */
                /* If the connection is in a valid session, then inform the PduR about the missed indication and set
                   its state to idle. */
                pairedRxSduState->State = J1939TP_STATE_FINISH;
                SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_RXNSDULOCK();

                if (pairedRxSduState->InSession == TRUE)
                {
                  /*! \trace SPEC-2167305 */
                  PduR_J1939TpRxIndication(J1939Tp_GetSduIdOfRxSdu(pairedRxSduIdx), E_NOT_OK); 
                }

                /* no protection required - transition from uninterruptible state */
                pairedRxSduState->State = J1939TP_STATE_IDLE;
              }
              /* Otherwise */
              else
              {
                SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_RXNSDULOCK();

                /* Set the aborted flag true of the found Rx connection */
                pairedRxSduState->Aborted = TRUE; /* VCA_J1939TP_RXSDUSTATE_VIA_RXSDU_CSL03 */
              }

              break;
            }
          }
        }
      }
#  endif
    }
  }
  /* Otherwise */
  else
  {
    SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_TXNPDULOCK();

    /* Set the state back to ABORT. */
    /* no protection required - transition from uninterruptible state */
    txSduState->State = J1939TP_STATE_CMDT_ABORT; /* VCA_J1939TP_TXSDUSTATE_VIA_TXSDU_CSL03 */
  }
} /* J1939Tp_CmdtInternalTransmitTpAbortTx */ /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */
# endif


# if (J1939TP_CMDT_RX_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  J1939Tp_CmdtInternalTransmitTpAbortRx()
 *********************************************************************************************************************/
/*!
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
 *
 *
 *
 */
J1939TP_LOCAL_INLINE void J1939Tp_CmdtInternalTransmitTpAbortRx(PduIdType rxSduIdx)
{
  J1939Tp_RxChannelChannelIdxOfRxSduType rxChannelIdx = J1939Tp_GetRxChannelChannelIdxOfRxSdu(rxSduIdx); 
  J1939Tp_SizeOfTxPduType txPduIdx = J1939Tp_GetTxPduRxFcNPduIdxOfRxChannel(rxChannelIdx); 
  J1939Tp_TxNPduStateType *txPduState = &J1939Tp_GetTxPduState(J1939Tp_GetTxPduStateIdxOfTxPdu(txPduIdx));
  J1939Tp_RxNSduStateType *rxSduState = &J1939Tp_GetRxSduState(J1939Tp_GetRxSduStateIdxOfRxSdu(rxSduIdx));

  /* If the PDU is not in use. */
  SchM_Enter_J1939Tp_J1939TP_EXCLUSIVE_AREA_TXNPDULOCK();
  if (txPduState->Locked == FALSE)
  {
    /* Lock the PDU and set the initial confirmation timeout value. */
    txPduState->CurrentNSduType = J1939TP_NSDU_CMDT_RX; /* VCA_J1939TP_TXPDUSTATE_VIA_RXSDU_CSL03 */
    txPduState->CurrentNSduId = rxSduIdx; /* VCA_J1939TP_TXPDUSTATE_VIA_RXSDU_CSL03 */
    txPduState->ConfTimeout = J1939Tp_GetTxConfTimeout(); /* VCA_J1939TP_TXPDUSTATE_VIA_RXSDU_CSL03 */
    /* protected against concurrent access to the same TP.CM N-PDU */
    txPduState->Locked = TRUE; /* VCA_J1939TP_TXPDUSTATE_VIA_RXSDU_CSL03 */
    SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_TXNPDULOCK();

    {
      uint32 pgn = (uint32) J1939Tp_GetPGNOfRxSdu(rxSduIdx); 
      uint8 data[J1939TP_NPDU_LENGTH];
      PduInfoType pdu;
      Std_ReturnType result;

      /* Prepare the PDU */
      data[J1939TP_TPCM_CB] = (uint8) J1939TP_CB_ABORT;
      data[J1939TP_TPCM_CAR] = (uint8) rxSduState->AbortReason;
      data[J1939TP_TPCM_RES3] = J1939TP_SNA_VALUE;
      data[J1939TP_TPCM_RES4] = J1939TP_SNA_VALUE;
      data[J1939TP_TPCM_RES5] = J1939TP_SNA_VALUE;
      data[J1939TP_TPCM_PGN_LO] = J1939Tp_Make_PGN_LO(pgn);
      data[J1939TP_TPCM_PGN_MD] = J1939Tp_Make_PGN_MD(pgn);
      data[J1939TP_TPCM_PGN_HI] = J1939Tp_Make_PGN_HI(pgn);
      /* Fill in the MetaData. */
      data[J1939TP_NPDU_SA_POS] = rxSduState->Receiver;
      data[J1939TP_NPDU_DA_POS] = rxSduState->Sender;
      data[J1939TP_NPDU_PRI_POS] = rxSduState->Priority;

      pdu.SduDataPtr = data;
      pdu.SduLength = J1939TP_NPDU_LENGTH;

      /* Request the transmission of the abort frame from the lower layer. */
      /* no protection required - transition from uninterruptible state */
      rxSduState->State = J1939TP_STATE_CMDT_ABORT_CONF; /* VCA_J1939TP_RXSDUSTATE_VIA_RXSDU_CSL03 */
      result = CanIf_Transmit(J1939Tp_GetPduIdOfTxPdu(txPduIdx), &pdu); /* VCA_J1939TP_FCTCALL_PTR2LOCAL */

      /* If the request was not successful. */
      if (result != E_OK)
      {
        /* Set the state back to abort frame. */
        SchM_Enter_J1939Tp_J1939TP_EXCLUSIVE_AREA_RXNSDULOCK();
        if (rxSduState->State == J1939TP_STATE_CMDT_ABORT_CONF)
        {
          /* no protection required - no further actions related to the locked state */
          txPduState->Locked = FALSE; /* VCA_J1939TP_TXPDUSTATE_VIA_RXSDU_CSL03 */

          /* protected against late Tx confirmation */
          rxSduState->State = J1939TP_STATE_CMDT_ABORT; /* VCA_J1939TP_RXSDUSTATE_VIA_RXSDU_CSL03 */

          SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_RXNSDULOCK();
        }
        else
        {
          SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_RXNSDULOCK();
        }
      }
#  if (J1939TP_CMDT_TX_ENABLED == STD_ON)
      /* If the request was successful and a transmission connection with CMDT is configured */
      else
      {
        J1939Tp_ComMChannelOfRxChannelType comMChannel = J1939Tp_GetComMChannelOfRxChannel(rxChannelIdx);
        PduIdType pairedTxSduIdx;

        /* Iterate over all Tx SDUs to find the corresponding Tx SDU for this Rx SDU. */
        for (pairedTxSduIdx = 0; pairedTxSduIdx < J1939Tp_GetSizeOfTxSdu(); pairedTxSduIdx++)
        {
#   if (J1939TP_INVALIDHNDOFTXSDU == STD_ON)
          if (!J1939Tp_IsInvalidHndOfTxSdu(pairedTxSduIdx))
#   endif
          {
            J1939Tp_TxNSduStateType *pairedTxSduState = &J1939Tp_GetTxSduState(J1939Tp_GetTxSduStateIdxOfTxSdu(pairedTxSduIdx));

            /* If the corresponding Tx connection uses the same ComMChannel, PGN and has matching Sender and Receiver. */
            if ((J1939Tp_GetComMChannelOfTxChannel(J1939Tp_GetTxChannelChannelIdxOfTxSdu(pairedTxSduIdx)) == comMChannel) && 
                ((pairedTxSduState->State & J1939TP_STATEMASK_CMDT) != J1939TP_STATE_IDLE) &&
                (pairedTxSduState->Sender == rxSduState->Receiver) &&
                (pairedTxSduState->Receiver ==  rxSduState->Sender) &&
                (J1939Tp_GetPGNOfTxSdu(pairedTxSduIdx) == pgn))
            {
              /* And if the corresponding Tx connection is in state RTS, CTS, CSTWAIT, DATA or ABORT */
              SchM_Enter_J1939Tp_J1939TP_EXCLUSIVE_AREA_TXNSDULOCK();
              if ((pairedTxSduState->State == J1939TP_STATE_CMDT_RTS) ||
                  (pairedTxSduState->State == J1939TP_STATE_CMDT_CTS) ||
                  (pairedTxSduState->State == J1939TP_STATE_CMDT_CTSWAIT) ||
                  (pairedTxSduState->State == J1939TP_STATE_CMDT_ABORT) ||
                  (pairedTxSduState->State == J1939TP_STATE_CMDT_DATA))
              {
                /* protected against concurrent main function invocation or concurrent reception of TP.ConnAbort
                   message */
                /* Then inform the PduR about the missed confirmation and set its state to idle. */
                pairedTxSduState->State = J1939TP_STATE_FINISH; /* VCA_J1939TP_TXSDUSTATE_VIA_TXSDU_CSL03 */
                SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_TXNSDULOCK();

                /*! \trace SPEC-2167303 */
                PduR_J1939TpTxConfirmation(J1939Tp_GetSduIdOfTxSdu(pairedTxSduIdx), E_NOT_OK);

                /* no protection required - transition from uninterruptible state */
                pairedTxSduState->State = J1939TP_STATE_IDLE; /* VCA_J1939TP_TXSDUSTATE_VIA_TXSDU_CSL03 */
              }
              /* For all other states */
              else
              {
                SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_TXNSDULOCK();

                /* Set the aborted flag true of the found Rx connection */
                pairedTxSduState->Aborted = TRUE; /* VCA_J1939TP_TXSDUSTATE_VIA_TXSDU_CSL03 */
              }

              break;
            }
          }
        }
      }
#  endif
    }
  }
  /* Otherwise the PDU is locked. */
  else
  {
    SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_TXNPDULOCK();

    /* Set the state back to ABORT. */
    /* no protection required - transition from uninterruptible state */
    rxSduState->State = J1939TP_STATE_CMDT_ABORT; /* VCA_J1939TP_RXSDUSTATE_VIA_RXSDU_CSL03 */
  }
} /* J1939Tp_CmdtInternalTransmitTpAbortRx */ /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */
# endif


# if (J1939TP_CMDT_TX_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  J1939Tp_CmdtInternalTransmitTpDt()
 *********************************************************************************************************************/
/*!
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
J1939TP_LOCAL_INLINE void J1939Tp_CmdtInternalTransmitTpDt(PduIdType txSduIdx)
{
  J1939Tp_TxChannelChannelIdxOfTxSduType txChannelIdx = J1939Tp_GetTxChannelChannelIdxOfTxSdu(txSduIdx);
  J1939Tp_SizeOfTxPduType txPduIdx = J1939Tp_GetTxPduTxDtNPduIdxOfTxChannel(txChannelIdx);
  J1939Tp_TxNPduStateType *txPduState = &J1939Tp_GetTxPduState(J1939Tp_GetTxPduStateIdxOfTxPdu(txPduIdx));
  J1939Tp_TxNSduStateType *txSduState = &J1939Tp_GetTxSduState(J1939Tp_GetTxSduStateIdxOfTxSdu(txSduIdx));

  /* If the PDU is not in use. */
  SchM_Enter_J1939Tp_J1939TP_EXCLUSIVE_AREA_TXNPDULOCK();
  if (txPduState->Locked == FALSE)
  {
    /* Lock the PDU and set the initial confirmation timeout value. */
    txPduState->CurrentNSduType = J1939TP_NSDU_CMDT_TX; /* VCA_J1939TP_TXPDUSTATE_VIA_TXSDU_CSL03 */
    txPduState->CurrentNSduId = txSduIdx; /* VCA_J1939TP_TXPDUSTATE_VIA_TXSDU_CSL03 */
    txPduState->ConfTimeout = J1939Tp_GetTxConfTimeout(); /* VCA_J1939TP_TXPDUSTATE_VIA_TXSDU_CSL03 */
    /* protected against concurrent access to the same TP.DT N-PDU */
    txPduState->Locked = TRUE; /* VCA_J1939TP_TXPDUSTATE_VIA_TXSDU_CSL03 */
    SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_TXNPDULOCK();

    {
      uint8 data[J1939TP_NPDU_LENGTH];
      PduInfoType pdu;
      BufReq_ReturnType tpResult;

      /* Prepare the PDU */
      pdu.SduDataPtr = &data[J1939TP_TPDT_DATA];
      pdu.SduLength = J1939TP_TPDT_DATA_SIZE;

      /* If it is the last frame */
      if (txSduState->Sequence == txSduState->Packets)
      {
        /* Set the size of the remaining payload. */
        pdu.SduLength =
          (PduLengthType) ((txSduState->Size) -
                           (PduLengthType) ((PduLengthType) ((PduLengthType) (txSduState->Sequence) - 1u) *
                                            (PduLengthType) J1939TP_TPDT_DATA_SIZE));
      }

      /*! \trace SPEC-2167315, SPEC-2167317 */
#  if (J1939TP_TXRETRYSUPPORTOFTXCHANNEL == STD_ON)
      /* If TxRetrySupport is enabled */
      if (J1939Tp_IsTxRetrySupportOfTxChannel(J1939Tp_GetTxChannelChannelIdxOfTxSdu(txSduIdx)))
      {
        /* Then request the payload data from the upper layer for retransmission. */
        tpResult = PduR_J1939TpCopyTxData(J1939Tp_GetSduIdOfTxSdu(txSduIdx), &pdu, &txSduState->Retry, &txSduState->DataSize); /* VCA_J1939TP_FCTCALL_PTR2LOCAL */ /* VCA_J1939TP_TXSDUSTATE_VIA_TXSDU_CSL03 */
      }
      /* Otherwise */
      else
#  endif
      {
        /* Request the payload data from the upper layer. */
        tpResult = PduR_J1939TpCopyTxData(J1939Tp_GetSduIdOfTxSdu(txSduIdx), &pdu, NULL_PTR, &txSduState->DataSize);  /* VCA_J1939TP_FCTCALL_PTR2LOCAL */ /* VCA_J1939TP_TXSDUSTATE_VIA_TXSDU_CSL03 */
      }

      /* If the request was successful, */
      if (tpResult == BUFREQ_OK)
      {
        /* Fill in the payload data */
        uint8 pos;
        Std_ReturnType result;

        /* First byte is used for the sequence counter. */
        data[J1939TP_TPDT_SEQ] = txSduState->Sequence;

        /* For all unused payload bytes, */
        for (pos = J1939TP_TPDT_DATA + (uint8) pdu.SduLength; pos < J1939TP_FRAME_LENGTH; pos++)
        {
          /* Set the invalid value. */
          data[pos] = J1939TP_SNA_VALUE; /*!< \trace SPEC-2167353 */
        }

        /* Fill in the MetaData. */
        data[J1939TP_NPDU_SA_POS] = txSduState->Sender;
        data[J1939TP_NPDU_DA_POS] = txSduState->Receiver;
        data[J1939TP_NPDU_PRI_POS] = txSduState->Priority;

        pdu.SduDataPtr = data;
        pdu.SduLength = J1939TP_NPDU_LENGTH; /*!< \trace SPEC-2167352 */

        /* Request the transmission of the data frame from the lower layer. */
        /* no protection required - transition from uninterruptible state */
        txSduState->State = J1939TP_STATE_CMDT_DATA_CONF; /* VCA_J1939TP_TXSDUSTATE_VIA_TXSDU_CSL03 */
        result = CanIf_Transmit(J1939Tp_GetPduIdOfTxPdu(txPduIdx), &pdu); /* VCA_J1939TP_FCTCALL_PTR2LOCAL */

        /* If the request was not successful. */
        if (result != E_OK)
        {
          SchM_Enter_J1939Tp_J1939TP_EXCLUSIVE_AREA_TXNSDULOCK();

          /* Set the state back to data frame. */
          if (txSduState->State == J1939TP_STATE_CMDT_DATA_CONF)
          {
            /* no protection required - no further actions related to the locked state */
            txPduState->Locked = FALSE; /* VCA_J1939TP_TXPDUSTATE_VIA_TXSDU_CSL03 */

            /* protected against late Tx confirmation */
            txSduState->State = J1939TP_STATE_CMDT_DATA; /* VCA_J1939TP_TXSDUSTATE_VIA_TXSDU_CSL03 */

            SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_TXNSDULOCK();
          }
          else
          {
            SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_TXNSDULOCK();
          }
        }
      }
      /* Otherwise */
      else
      {
        /* Unlock the PDU. */
        /* no protection required - no further actions related to the locked state */
        txPduState->Locked = FALSE; /* VCA_J1939TP_TXPDUSTATE_VIA_TXSDU_CSL03 */

        /* If the upper layer request is busy */
        /*! \trace SPEC-2167316 */
        if (tpResult == BUFREQ_E_BUSY)
        {
          /* Then set the state back to data frame. */
          /* no protection required - transition from uninterruptible state */
          txSduState->State = J1939TP_STATE_CMDT_DATA; /* VCA_J1939TP_TXSDUSTATE_VIA_TXSDU_CSL03 */
        }
        /* Otherwise */
        else
        {
          /* Set abort reason and request transmission of the abort frame. */
          /*! \trace SPEC-2167320 */
          txSduState->AbortReason = J1939TP_CAR_RESOURCES; /* VCA_J1939TP_TXSDUSTATE_VIA_TXSDU_CSL03 */

          J1939Tp_CmdtInternalTransmitTpAbortTx(txSduIdx);
        }
      }
    }
  }
  /* Otherwise */
  else
  {
    SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_TXNPDULOCK();

    /* Set the state back to DATA. */
    /* no protection required - transition from uninterruptible state */
    txSduState->State = J1939TP_STATE_CMDT_DATA; /* VCA_J1939TP_TXSDUSTATE_VIA_TXSDU_CSL03 */
  }
} /* J1939Tp_CmdtInternalTransmitTpDt */ /* PRQA S 6050 */ /* MD_MSR_STCAL */
# endif


# if (J1939TP_CMDT_TX_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  J1939Tp_CmdtInternalTransmit_SearchConflictingTxChannel
 *********************************************************************************************************************/
/*!
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
J1939TP_LOCAL_INLINE boolean J1939Tp_CmdtInternalTransmit_SearchConflictingTxChannel(PduIdType txSduIdx,
                                                        J1939Tp_TxChannelChannelIdxOfTxSduType txChannelIdx,
                                                        uint8 sa,
                                                        uint8 da)
{
  J1939Tp_ComMChannelOfTxChannelType comMChannel = J1939Tp_GetComMChannelOfTxChannel(txChannelIdx);
  J1939Tp_SizeOfTxChannelType otherTxChannelIdx;
  boolean found = FALSE;

  /* Iterate over all Tx channels as long as no tx connection with the same characteristics has been found. */
  for (otherTxChannelIdx = 0; (otherTxChannelIdx < J1939Tp_GetSizeOfTxChannel()) && (found == FALSE); otherTxChannelIdx++)
  {
    /* If ComMChannel is the same */
    if (J1939Tp_GetComMChannelOfTxChannel(otherTxChannelIdx) == comMChannel)
    {
      J1939Tp_TxChannelTxNSduTxNSduTableIndEndIdxOfTxChannelType txSduIndIdx;

      /* Iterate over all SDUs on that channel */
      for (txSduIndIdx = J1939Tp_GetTxChannelTxNSduTxNSduTableIndStartIdxOfTxChannel(otherTxChannelIdx);
           txSduIndIdx < J1939Tp_GetTxChannelTxNSduTxNSduTableIndEndIdxOfTxChannel(otherTxChannelIdx); txSduIndIdx++)
      {
        J1939Tp_TxChannelTxNSduTxNSduTableIndType otherTxSduIdx =
          J1939Tp_GetTxSduTxNSduIdxOfTxChannelTxNSdu(J1939Tp_GetTxChannelTxNSduTxNSduTableInd(txSduIndIdx)); 

        /* If the SDU index is different */
        if (otherTxSduIdx != txSduIdx)
        {
          const J1939Tp_TxNSduStateType *otherTxSduState =
            &J1939Tp_GetTxSduState(J1939Tp_GetTxSduStateIdxOfTxSdu(otherTxSduIdx));

          /* And if the state is not IDLE and the Sender and Receiver match with the source and destination address. */
          if (((otherTxSduState->State & J1939TP_STATEMASK_CMDT) != J1939TP_STATE_IDLE) &&
              (otherTxSduState->Sender == sa) && (otherTxSduState->Receiver == da))
          {
            /* Then a Tx connection with the same characteristics has been found. */
            found = TRUE;

            break;
          }
        }
      }
    }
  }

  /* Return the result of the function. */
  return found;
} /* PRQA S 6080 */ /* MD_MSR_STMIF */
# endif


# if (J1939TP_CMDT_RX_ENABLED == STD_ON)
/**********************************************************************************************************************
* J1939Tp_CmdtInternalRxIndication_AllocateRxChannel()
*********************************************************************************************************************/
/*!
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
J1939TP_LOCAL_INLINE boolean J1939Tp_CmdtInternalRxIndication_AllocateRxChannel(PduIdType rxPduIdx,
                                                                                 uint8 sa,
                                                                                 uint8 da,
                                                                                 uint32 pgn,
                                                                                 J1939Tp_RxSduRxNSduIdxOfRxChannelRxNSduType * allocatedRxSduIdx)
{
  J1939Tp_RxPduRxChannelRxChannelTableIndEndIdxOfRxPduType rxPduRxChannelIdx;
  boolean found = FALSE;
  boolean allocated = FALSE;

  /*
   * Search for all Rx channels that use the reported PDU. It is not necessary to search for all Rx channels with the
   * same ComM channel, because there can only be one Rx PDU per ComM channel (ensured by CanIf).
   */
  for (rxPduRxChannelIdx = J1939Tp_GetRxPduRxChannelRxChannelTableIndStartIdxOfRxPdu(rxPduIdx);
       rxPduRxChannelIdx < J1939Tp_GetRxPduRxChannelRxChannelTableIndEndIdxOfRxPdu(rxPduIdx); rxPduRxChannelIdx++)
  {
    J1939Tp_RxChannelRxChannelIdxOfRxPduRxChannelType rxChannelIdx =
      J1939Tp_GetRxChannelRxChannelIdxOfRxPduRxChannel(rxPduRxChannelIdx);

#  if (J1939TP_BAM_RX_ENABLED == STD_ON)
    /* If the protocol type is not BAM (if RxProtocolType is enabled) */
    if (J1939Tp_GetRxProtocolTypeOfRxChannel(rxChannelIdx) != J1939TP_PROTOCOL_BAM_RXPROTOCOLTYPEOFRXCHANNEL)
#  endif
    {
      /* If a source address is configured for an Rx connection. */
      /*! \trace SPEC-2167348 */
      uint8 configuredSa = J1939Tp_GetRxSaOfRxChannel(rxChannelIdx);

      /* Verify that either the configured source address is undefined or is the given source address sa. */
      if ((configuredSa == J1939TP_NO_ADDRESS_CONFIGURED) || (configuredSa == sa))
      {
        /* If a destination address is configured for an Rx connection. */
        /*! \trace SPEC-2167348 */
        uint8 configuredDa = J1939Tp_GetRxDaOfRxChannel(rxChannelIdx);

        /* Verify that either the configured destination address is undefined or is the given destination address da. */
        if ((configuredDa == J1939TP_NO_ADDRESS_CONFIGURED) || (configuredDa == da))
        {
          J1939Tp_RxChannelRxNSduRxNSduTableIndEndIdxOfRxChannelType rxChannelSduIdx;

          /* Iterate over all Rx channels of the SDU from the given rxPduIdx. */
          for (rxChannelSduIdx = J1939Tp_GetRxChannelRxNSduRxNSduTableIndStartIdxOfRxChannel(rxChannelIdx);
               rxChannelSduIdx < J1939Tp_GetRxChannelRxNSduRxNSduTableIndEndIdxOfRxChannel(rxChannelIdx);
               rxChannelSduIdx++)
          {
            J1939Tp_RxSduRxNSduIdxOfRxChannelRxNSduType rxSduIdx =
              J1939Tp_GetRxSduRxNSduIdxOfRxChannelRxNSdu(rxChannelSduIdx); 
            J1939Tp_RxNSduStateType *rxSduState = &J1939Tp_GetRxSduState(J1939Tp_GetRxSduStateIdxOfRxSdu(rxSduIdx));

            /* If there is a connection in use that match the Sender and Receiver with the source and destination
               address. */
            if (((rxSduState->State & J1939TP_STATEMASK_CMDT) != J1939TP_STATE_IDLE) && 
                (rxSduState->Sender == sa) &&
                (rxSduState->Receiver == da))
            {
              /*! \trace SPEC-2167356 */
              J1939Tp_ReportRuntimeError(J1939TP_SID_RXINDICATION, J1939TP_E_UNTIMELY_RTS);

              SchM_Enter_J1939Tp_J1939TP_EXCLUSIVE_AREA_RXNSDULOCK();
              /* If the state is either CTS, CTSWAIT, DATA_FIRST, DATA, EOMACK or ABORT */
              if ((rxSduState->State == J1939TP_STATE_CMDT_CTS) || (rxSduState->State == J1939TP_STATE_CMDT_CTSWAIT) ||
                  (rxSduState->State == J1939TP_STATE_CMDT_DATA_FIRST) ||
                  (rxSduState->State == J1939TP_STATE_CMDT_DATA) ||
                  (rxSduState->State == J1939TP_STATE_CMDT_EOMACK) || (rxSduState->State == J1939TP_STATE_CMDT_ABORT))
              {
                /* If the connection is in a valid session, then inform the PduR about the missed indication and set
                   its state to idle. */
                /* protected against concurrent timeout and concurrent reception of TP.DT message */
                rxSduState->State = J1939TP_STATE_FINISH; /* VCA_J1939TP_RXSDUSTATE_VIA_RXPDU_CSL03 */
                SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_RXNSDULOCK();

                if (rxSduState->InSession == TRUE)
                {
                  /*! \trace SPEC-2167305 */
                  PduR_J1939TpRxIndication(J1939Tp_GetSduIdOfRxSdu(rxSduIdx), E_NOT_OK);
                }

                /* no protection required - transition from uninterruptible state */
                rxSduState->State = J1939TP_STATE_IDLE; /* VCA_J1939TP_RXSDUSTATE_VIA_RXPDU_CSL03 */
              }
              /* For all other states */
              else
              {
                SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_RXNSDULOCK();

                /* Set the aborted flag to true. */
                rxSduState->Aborted = TRUE; /* VCA_J1939TP_RXSDUSTATE_VIA_RXPDU_CSL03 */
              }
            }

            /* If no connection has been allocated so far and the PGN is equal. */
            /*! \trace SPEC-2167293, SPEC-2167356, SPEC-2167348 */
            if ((allocated == FALSE) && (pgn == (uint32) J1939Tp_GetPGNOfRxSdu(rxSduIdx)))
            {
              /* A new connection has been found. */
              found = TRUE;

              /* If the state is IDLE */
              SchM_Enter_J1939Tp_J1939TP_EXCLUSIVE_AREA_RXNSDULOCK();
              if (rxSduState->State == J1939TP_STATE_IDLE)
              {
                /* Set aborted and InSession flag to false. */
                rxSduState->Aborted = FALSE; /* VCA_J1939TP_RXSDUSTATE_VIA_RXPDU_CSL03 */
                rxSduState->InSession = FALSE; /* VCA_J1939TP_RXSDUSTATE_VIA_RXPDU_CSL03 */
                /* protected against concurrent reception of TP.CM_RTS message */ /* Check if this is necessary */
                rxSduState->State = J1939TP_STATE_CMDT_RTS_BUSY; /* VCA_J1939TP_RXSDUSTATE_VIA_RXPDU_CSL03 */
                SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_RXNSDULOCK();

                /* A new connection has been allocated. */
                allocated = TRUE;

                /* Return the found rxSduIdx and its state */
                *allocatedRxSduIdx = rxSduIdx;
              }
              else
              {
                SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_RXNSDULOCK();
              }
            }
          }
        }
      }
    }
  }

#  if (J1939TP_RUNTIME_ERROR_REPORT == STD_ON)
  /* If RuntimeErrorReporting is enabled and a connection has been found but has not yet been allocated. */
  if ((found == TRUE) && (allocated == FALSE))
  {
    /* Then report runtimer error that no free connection found for the incoming RTS. */
    /* Abort with reason 1 (see ALM+ issue 79145) */
    J1939Tp_ReportRuntimeError(J1939TP_SID_RXINDICATION, J1939TP_E_NO_CONNECTION);
  }
#  else
  J1939TP_DUMMY_STATEMENT(found); /* PRQA S 3112, 1338, 2983 */ /* MD_MSR_DummyStmt */
#  endif

  /* Return the allocation information for the new connection. */
  return allocated;
} /* PRQA S 6030, 6060, 6080 */ /* MD_MSR_STCYC, MD_MSR_STPAR, MD_MSR_STMIF */
# endif


# if (J1939TP_CMDT_RX_ENABLED == STD_ON)
J1939TP_LOCAL_INLINE void J1939Tp_CmdtInternalRxIndication_ReceiveTpCmRts(J1939Tp_RxSduRxNSduIdxOfRxChannelRxNSduType
                                                                          rxSduIdx, P2CONST(PduInfoType, AUTOMATIC,
                                                                                          J1939TP_APPL_DATA) info,
                                                                          uint8 sa, uint8 da, uint16 size)
{
  boolean invalidSize;
  uint8_least packets = (uint8_least) J1939Tp_Get_Packets(size);
  J1939Tp_RxNSduStateType *rxSduState = &J1939Tp_GetRxSduState(J1939Tp_GetRxSduStateIdxOfRxSdu(rxSduIdx));

#  if (J1939TP_RUNTIME_ERROR_REPORT == STD_ON)
  if (packets != info->SduDataPtr[J1939TP_TPCM_TNOP])
  {
    J1939Tp_ReportRuntimeError(J1939TP_SID_RXINDICATION, J1939TP_E_INVALID_TNOP);
  }

  if (info->SduDataPtr[J1939TP_TPCM_MNOP] == 0u)
  {
    J1939Tp_ReportRuntimeError(J1939TP_SID_RXINDICATION, J1939TP_E_INVALID_MNOP);
  }
#  endif

#  if (J1939TP_ISVARIABLEOFRXSDU == STD_ON)
  if (J1939Tp_IsIsVariableOfRxSdu(rxSduIdx))
  { 
    /* PRQA S 4304 1 */ /* MD_MSR_AutosarBoolean */
    invalidSize = (boolean) (size > J1939Tp_GetPduLengthOfRxSdu(rxSduIdx));
  }
  else
#  endif
  { 
    /* PRQA S 4304 1 */ /* MD_MSR_AutosarBoolean */
    invalidSize = (boolean) (size != J1939Tp_GetPduLengthOfRxSdu(rxSduIdx));
  }

  if (invalidSize == TRUE)
  {
    J1939Tp_ReportRuntimeError(J1939TP_SID_RXINDICATION, J1939TP_E_INVALID_SIZE);

    /* no protection required - transition from uninterruptible state */
    rxSduState->State = J1939TP_STATE_IDLE; /* VCA_J1939TP_RXSDUSTATE_VIA_RXSDU_CSL03 */
  }
  else
  {
    PduInfoType addrInfo;
    BufReq_ReturnType tpResult;

    rxSduState->Size = size; /* VCA_J1939TP_RXSDUSTATE_VIA_RXSDU_CSL03 */
    rxSduState->Packets = packets; /* VCA_J1939TP_RXSDUSTATE_VIA_RXSDU_CSL03 */
    rxSduState->Sender = sa; /* VCA_J1939TP_RXSDUSTATE_VIA_RXSDU_CSL03 */
    rxSduState->Receiver = da; /* VCA_J1939TP_RXSDUSTATE_VIA_RXSDU_CSL03 */
    rxSduState->Priority = J1939Tp_MDL_Get_PRI(info->SduDataPtr[J1939TP_NPDU_PRI_POS]); /* VCA_J1939TP_RXSDUSTATE_VIA_RXSDU_CSL03 */

    addrInfo.SduLength = J1939Tp_GetMetaDataLengthOfRxSdu(rxSduIdx); 
    addrInfo.SduDataPtr = &(info->SduDataPtr[J1939TP_NPDU_MDL_POS]);

    tpResult = PduR_J1939TpStartOfReception(J1939Tp_GetSduIdOfRxSdu(rxSduIdx), &addrInfo, (PduLengthType) size, /* VCA_J1939TP_FCTCALL_PTR2LOCAL */
                                            &rxSduState->BufSize);
    if (tpResult == BUFREQ_OK)
    {
      rxSduState->RetryAttempts = 0u; /* VCA_J1939TP_RXSDUSTATE_VIA_RXSDU_CSL03 */
      rxSduState->InSession = TRUE; /* VCA_J1939TP_RXSDUSTATE_VIA_RXSDU_CSL03 */
      rxSduState->Sequence = J1939TP_RX_SEQUENCE_INITIAL; /* VCA_J1939TP_RXSDUSTATE_VIA_RXSDU_CSL03 */
      rxSduState->TimeOut = J1939Tp_GetTime_Tr(); /*!< \trace SPEC-2167340 */ /* VCA_J1939TP_RXSDUSTATE_VIA_RXSDU_CSL03 */

      J1939Tp_CmdtInternalTransmitTpCmCts(rxSduIdx);
    }
    else
    {
      /*! \trace SPEC-2167310, SPEC-2167311 */
      rxSduState->AbortReason = J1939TP_CAR_RESOURCES; /* VCA_J1939TP_RXSDUSTATE_VIA_RXSDU_CSL03 */
      rxSduState->TimeOut = J1939Tp_GetTime_Tr(); /*!< \trace SPEC-2167340 */ /* VCA_J1939TP_RXSDUSTATE_VIA_RXSDU_CSL03 */

      J1939Tp_CmdtInternalTransmitTpAbortRx(rxSduIdx);
    }
  }
} /* PRQA S 6060 */ /* MD_MSR_STPAR */
# endif


# if (J1939TP_CMDT_TX_ENABLED == STD_ON)
J1939TP_LOCAL_INLINE boolean J1939Tp_CmdtInternalRxIndication_FindActiveTxChannel(PduIdType rxPduIdx,
                                                     uint8 sa,
                                                     uint8 da,
                                                     J1939Tp_TxSduTxNSduIdxOfTxChannelTxNSduType * txSduIdx)
{
  J1939Tp_RxPduTxChannelTxChannelTableIndEndIdxOfRxPduType rxPduTxChannelIdx;
  boolean found = FALSE;

  /* Search for all Tx channels that use the reported PDU. It is not necessary to search for all Tx channels with the
     same ComM channel, because there can only be one Rx PDU per ComM channel (ensured by CanIf). */
  for (rxPduTxChannelIdx = J1939Tp_GetRxPduTxChannelTxChannelTableIndStartIdxOfRxPdu(rxPduIdx);
       (rxPduTxChannelIdx < J1939Tp_GetRxPduTxChannelTxChannelTableIndEndIdxOfRxPdu(rxPduIdx)) && (found == FALSE);
       rxPduTxChannelIdx++)
  {
    J1939Tp_TxChannelTxChannelIdxOfRxPduTxChannelType txChannelIdx = J1939Tp_GetTxChannelTxChannelIdxOfRxPduTxChannel(rxPduTxChannelIdx);
    J1939Tp_TxChannelTxNSduTxNSduTableIndEndIdxOfTxChannelType txChannelSduIdx;

    for (txChannelSduIdx = J1939Tp_GetTxChannelTxNSduTxNSduTableIndStartIdxOfTxChannel(txChannelIdx);
         txChannelSduIdx < J1939Tp_GetTxChannelTxNSduTxNSduTableIndEndIdxOfTxChannel(txChannelIdx); txChannelSduIdx++)
    {
      const J1939Tp_TxNSduStateType *txSduState;

      *txSduIdx = J1939Tp_GetTxSduTxNSduIdxOfTxChannelTxNSdu(txChannelSduIdx); 
      txSduState = &J1939Tp_GetTxSduState(J1939Tp_GetTxSduStateIdxOfTxSdu(*txSduIdx));

      if ((((txSduState->State) & J1939TP_STATEMASK_CMDT) != J1939TP_STATE_IDLE) && ((txSduState->Receiver) == sa) &&
          ((txSduState->Sender) == da))
      {
        found = TRUE;

        break;
      }
    }
  }

  return found;
}
# endif


# if (J1939TP_CMDT_TX_ENABLED == STD_ON)
J1939TP_LOCAL_INLINE void J1939Tp_CmdtInternalRxIndication_ReceiveTpCmCts(J1939Tp_TxSduTxNSduIdxOfTxChannelTxNSduType txSduIdx,
                                                                          CONSTP2CONST(PduInfoType, AUTOMATIC, J1939TP_APPL_DATA) info,
                                                                          uint32 pgn)
{
  if (pgn == (uint32) J1939Tp_GetPGNOfTxSdu(txSduIdx))
  {
    J1939Tp_TxNSduStateType *txSduState;

    SchM_Enter_J1939Tp_J1939TP_EXCLUSIVE_AREA_TXNSDULOCK();

    txSduState = &J1939Tp_GetTxSduState(J1939Tp_GetTxSduStateIdxOfTxSdu(txSduIdx));

    if ((txSduState->State == J1939TP_STATE_CMDT_CTS) || (txSduState->State == J1939TP_STATE_CMDT_CTSWAIT))
    {
      /* protected against concurrent main function invocation and concurrent Tx abort */
      txSduState->State = J1939TP_STATE_CMDT_CTS_BUSY; /* VCA_J1939TP_TXSDUSTATE_VIA_TXSDU_CSL03 */
      SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_TXNSDULOCK();

      {
        uint8 block = info->SduDataPtr[J1939TP_TPCM_NOP];
        uint8 nextPacketNumber = info->SduDataPtr[J1939TP_TPCM_NPN];

        /*! \trace SPEC-2167333 */
        if (block == J1939TP_CTS_WAIT)
        {
#  if (J1939TP_RUNTIME_ERROR_REPORT == STD_ON)
          if (nextPacketNumber != J1939TP_TPCM_NPN_UNUSED)
          {
            J1939Tp_ReportRuntimeError(J1939TP_SID_RXINDICATION, J1939TP_E_INVALID_NPN);
          }
#  endif
          txSduState->TimeOut = J1939Tp_GetTime_T4(); /*!< \trace SPEC-2167340 */ /* VCA_J1939TP_TXSDUSTATE_VIA_TXSDU_CSL03 */
          /* no protection required - transition from uninterruptible state */
          txSduState->State = J1939TP_STATE_CMDT_CTSWAIT; /* VCA_J1939TP_TXSDUSTATE_VIA_TXSDU_CSL03 */
        }
        else
        {
          if ((nextPacketNumber == txSduState->Sequence)
#  if (J1939TP_TXRETRYSUPPORTOFTXCHANNEL == STD_ON)
              || ((J1939Tp_IsTxRetrySupportOfTxChannel(J1939Tp_GetTxChannelChannelIdxOfTxSdu(txSduIdx))) 
                  && (nextPacketNumber < txSduState->Sequence) && (nextPacketNumber != J1939TP_SEQUENCE_INVALID))
#  endif
            )
          {
            uint8 maxblock;

#  if (J1939TP_TXRETRYSUPPORTOFTXCHANNEL == STD_ON)
            if (J1939Tp_IsTxRetrySupportOfTxChannel(J1939Tp_GetTxChannelChannelIdxOfTxSdu(txSduIdx)))
            {
              if (nextPacketNumber < txSduState->Sequence)
              {
                txSduState->Retry.TpDataState = TP_DATARETRY; /* VCA_J1939TP_TXSDUSTATE_VIA_TXSDU_CSL03 */
                txSduState->Retry.TxTpDataCnt = /* VCA_J1939TP_TXSDUSTATE_VIA_TXSDU_CSL03 */
                  (PduLengthType) ((PduLengthType)
                                   ((PduLengthType) txSduState->Sequence -
                                    (PduLengthType) nextPacketNumber) * (PduLengthType) J1939TP_TPDT_DATA_SIZE);

                /* Set SN back to the requested one. */
                txSduState->Sequence = nextPacketNumber; /* VCA_J1939TP_TXSDUSTATE_VIA_TXSDU_CSL03 */
              }
              else
              { /* NPN == Sequence */
                if (txSduState->Sequence == J1939TP_TX_SEQUENCE_INITIAL)
                {
                  txSduState->Retry.TpDataState = TP_CONFPENDING; /* VCA_J1939TP_TXSDUSTATE_VIA_TXSDU_CSL03 */
                }
                else
                {
                  txSduState->Retry.TpDataState = TP_DATACONF; /* VCA_J1939TP_TXSDUSTATE_VIA_TXSDU_CSL03 */
                }

                txSduState->Retry.TxTpDataCnt = 0; /* VCA_J1939TP_TXSDUSTATE_VIA_TXSDU_CSL03 */
              }
            }
#  endif
            maxblock = ((uint8) txSduState->Packets) - (txSduState->Sequence - 1u); /* VCA_J1939TP_TXSDUSTATE_VIA_TXSDU_CSL03 */

            if (block > maxblock)
            {
              J1939Tp_ReportRuntimeError(J1939TP_SID_RXINDICATION, J1939TP_E_INVALID_NOP);
              block = maxblock;
            }

            txSduState->NextBlock = txSduState->Sequence + block; /* VCA_J1939TP_TXSDUSTATE_VIA_TXSDU_CSL03 */
            txSduState->TimeOut = J1939Tp_GetTime_Tr(); /*!< \trace SPEC-2167340 */ /* VCA_J1939TP_TXSDUSTATE_VIA_TXSDU_CSL03 */

            J1939Tp_CmdtInternalTransmitTpDt(txSduIdx);
          }
          else
          { /* NPN > txSduState->Sequence */
            /*! \trace SPEC-2167334, SPEC-2167336 */
            J1939Tp_ReportRuntimeError(J1939TP_SID_RXINDICATION, J1939TP_E_INVALID_NPN);

            /* Abort with reason SNA (no reason specified for TP.CTS requesting a sequence number that cannot be
               delivered) */
            txSduState->AbortReason = J1939TP_CAR_OTHER; /* VCA_J1939TP_TXSDUSTATE_VIA_TXSDU_CSL03 */
            txSduState->TimeOut = J1939Tp_GetTime_Tr(); /*!< \trace SPEC-2167340 */ /* VCA_J1939TP_TXSDUSTATE_VIA_TXSDU_CSL03 */

            J1939Tp_CmdtInternalTransmitTpAbortTx(txSduIdx);
          }
        }
      }
    }
    else
    {
      /* TP.CM_CTS shall be ignored if received unexpectedly */

      if (txSduState->State == J1939TP_STATE_CMDT_DATA)
      {
        /* protected against concurrent main function invocation and concurrent Tx abort */
        txSduState->State = J1939TP_STATE_CMDT_CTS_BUSY;/* VCA_J1939TP_TXSDUSTATE_VIA_TXSDU_CSL03 */
        SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_TXNSDULOCK();

        J1939Tp_ReportRuntimeError(J1939TP_SID_RXINDICATION, J1939TP_E_UNEXPECTED_CTS);

        /* Abort with reason 4 (CTS messages received when data transfer is in progress) */
        txSduState->AbortReason = J1939TP_CAR_UNTIMELY_CTS; /*!< \trace SPEC-2167355 */ /* VCA_J1939TP_TXSDUSTATE_VIA_TXSDU_CSL03 */
        txSduState->TimeOut = J1939Tp_GetTime_Tr(); /* VCA_J1939TP_TXSDUSTATE_VIA_TXSDU_CSL03 */

        J1939Tp_CmdtInternalTransmitTpAbortTx(txSduIdx);
      }
      else
      {
        SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_TXNSDULOCK();
        J1939Tp_ReportRuntimeError(J1939TP_SID_RXINDICATION, J1939TP_E_IGNORED_CTS);
      }
    }
  }
} /* PRQA S 6080, 6030 */ /* MD_MSR_STMIF, MD_MSR_STCYC */
# endif


# if (J1939TP_CMDT_TX_ENABLED == STD_ON)
J1939TP_LOCAL_INLINE void J1939Tp_CmdtInternalRxIndication_ReceiveTpCmEomack(J1939Tp_TxSduTxNSduIdxOfTxChannelTxNSduType txSduIdx,
                                                   CONSTP2CONST(PduInfoType, AUTOMATIC, J1939TP_APPL_DATA) info,
                                                   uint32 pgn)
{
  if (pgn == (uint32) J1939Tp_GetPGNOfTxSdu(txSduIdx)) 
  {
    J1939Tp_TxNSduStateType *txSduState;

    SchM_Enter_J1939Tp_J1939TP_EXCLUSIVE_AREA_TXNSDULOCK();

    txSduState = &J1939Tp_GetTxSduState(J1939Tp_GetTxSduStateIdxOfTxSdu(txSduIdx));

    if ((txSduState->State == J1939TP_STATE_CMDT_CTS) || (txSduState->State == J1939TP_STATE_CMDT_CTSWAIT))
    {
      /* protected against concurrent main function invocation and concurrent Tx abort */
      txSduState->State = J1939TP_STATE_FINISH; /* VCA_J1939TP_TXSDUSTATE_VIA_TXSDU_CSL03 */
      SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_TXNSDULOCK();

#  if (J1939TP_RUNTIME_ERROR_REPORT == STD_ON)
      if (txSduState->Size != (PduLengthType) ((uint16) J1939Tp_Get_TMS(info->SduDataPtr[J1939TP_TPCM_TMS_LO],
                                                                        info->SduDataPtr[J1939TP_TPCM_TMS_HI])))
      {
        J1939Tp_ReportRuntimeError(J1939TP_SID_RXINDICATION, J1939TP_E_INVALID_ATMS);
      }

      if (txSduState->Packets != info->SduDataPtr[J1939TP_TPCM_TNOP])
      {
        J1939Tp_ReportRuntimeError(J1939TP_SID_RXINDICATION, J1939TP_E_INVALID_ATNOP);
      }

      if (txSduState->Sequence != (uint8) (txSduState->Packets + 1u))
      {
        J1939Tp_ReportRuntimeError(J1939TP_SID_RXINDICATION, J1939TP_E_EARLY_EOMACK);
      }
#  endif

      /*! \trace SPEC-2167302 */
      PduR_J1939TpTxConfirmation(J1939Tp_GetSduIdOfTxSdu(txSduIdx), E_OK); 

      /* no protection required - transition from uninterruptible state */
      txSduState->State = J1939TP_STATE_IDLE; /* VCA_J1939TP_TXSDUSTATE_VIA_TXSDU_CSL03 */
    }
    else
    {
      SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_TXNSDULOCK();

      /* TP.CM_EndOfMsgAck shall be ignored if received unexpectedly */

      J1939Tp_ReportRuntimeError(J1939TP_SID_RXINDICATION, J1939TP_E_IGNORED_EOMACK);
    }
  }

#  if (J1939TP_RUNTIME_ERROR_REPORT == STD_OFF)
  J1939TP_DUMMY_STATEMENT_CONST(info); /* PRQA S 3112, 1338, 2983 */ /* MD_MSR_DummyStmt */
#  endif
}
# endif


# if (J1939TP_CMDT_RX_ENABLED == STD_ON)
/*! \trace SPEC-2167348 */
J1939TP_LOCAL_INLINE boolean J1939Tp_CmdtInternalRxIndication_FindActiveRxChannel(PduIdType rxPduIdx,
                                                     uint8 sa,
                                                     uint8 da,
                                                     J1939Tp_RxSduRxNSduIdxOfRxChannelRxNSduType * rxSduIdx)
{
  J1939Tp_RxPduRxChannelRxChannelTableIndEndIdxOfRxPduType rxPduRxChannelIdx;
  boolean found = FALSE;

  /* Search for all Rx channels that use the reported PDU. It is not necessary to search for all Rx channels with the
     same ComM channel, because there can only be one Rx PDU per ComM channel (ensured by CanIf). */
  for (rxPduRxChannelIdx = J1939Tp_GetRxPduRxChannelRxChannelTableIndStartIdxOfRxPdu(rxPduIdx);
       (rxPduRxChannelIdx < J1939Tp_GetRxPduRxChannelRxChannelTableIndEndIdxOfRxPdu(rxPduIdx)) && (found == FALSE);
       rxPduRxChannelIdx++)
  {
    J1939Tp_RxChannelRxChannelIdxOfRxPduRxChannelType rxChannelIdx =
      J1939Tp_GetRxChannelRxChannelIdxOfRxPduRxChannel(rxPduRxChannelIdx); 
    J1939Tp_RxChannelRxNSduRxNSduTableIndEndIdxOfRxChannelType rxChannelRxSduIdx;

    for (rxChannelRxSduIdx = J1939Tp_GetRxChannelRxNSduRxNSduTableIndStartIdxOfRxChannel(rxChannelIdx);
         rxChannelRxSduIdx < J1939Tp_GetRxChannelRxNSduRxNSduTableIndEndIdxOfRxChannel(rxChannelIdx); rxChannelRxSduIdx++)
    {
      const J1939Tp_RxNSduStateType *rxSduState;
      
      *rxSduIdx = J1939Tp_GetRxSduRxNSduIdxOfRxChannelRxNSdu(rxChannelRxSduIdx); 
      rxSduState = &J1939Tp_GetRxSduState(J1939Tp_GetRxSduStateIdxOfRxSdu(*rxSduIdx));

      if (((rxSduState->State & J1939TP_STATEMASK_CMDT) != J1939TP_STATE_IDLE) &&
          (rxSduState->Sender == sa) &&
          (rxSduState->Receiver == da))
      {
        found = TRUE;

        break;
      }
    }
  }

  return found;
}
# endif


# if (J1939TP_CMDT_RX_ENABLED == STD_ON)
J1939TP_LOCAL_INLINE void J1939Tp_CmdtInternalRxIndication_ReceiveTpAbortRx(J1939Tp_RxSduRxNSduIdxOfRxChannelRxNSduType
                                                                            rxSduIdx, uint32 pgn)
{
  if (pgn == (uint32) J1939Tp_GetPGNOfRxSdu(rxSduIdx)) 
  {
    J1939Tp_RxNSduStateType *rxSduState;

    SchM_Enter_J1939Tp_J1939TP_EXCLUSIVE_AREA_RXNSDULOCK();

    rxSduState = &J1939Tp_GetRxSduState(J1939Tp_GetRxSduStateIdxOfRxSdu(rxSduIdx));

    if ((rxSduState->State == J1939TP_STATE_CMDT_CTS) || (rxSduState->State == J1939TP_STATE_CMDT_CTSWAIT) ||
        (rxSduState->State == J1939TP_STATE_CMDT_DATA_FIRST) || (rxSduState->State == J1939TP_STATE_CMDT_DATA) ||
        (rxSduState->State == J1939TP_STATE_CMDT_EOMACK) || (rxSduState->State == J1939TP_STATE_CMDT_ABORT))
    {
      /*
       * protected against concurrent main function invocation, concurrent Tx abort, and concurrent reception of TP.DT
       * message
       */
      rxSduState->State = J1939TP_STATE_FINISH; /* VCA_J1939TP_RXSDUSTATE_VIA_RXSDU_CSL03 */
      SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_RXNSDULOCK();

      if (rxSduState->InSession == TRUE)
      {
        /*! \trace SPEC-2167305 */
        PduR_J1939TpRxIndication(J1939Tp_GetSduIdOfRxSdu(rxSduIdx), E_NOT_OK); 
      }

      /* no protection required - transition from uninterruptible state */
      rxSduState->State = J1939TP_STATE_IDLE; /* VCA_J1939TP_RXSDUSTATE_VIA_RXSDU_CSL03 */
    }
    else
    {
      SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_RXNSDULOCK();

      rxSduState->Aborted = TRUE; /* VCA_J1939TP_RXSDUSTATE_VIA_RXSDU_CSL03 */
    }
  }
  else
  {
    J1939Tp_ReportRuntimeError(J1939TP_SID_RXINDICATION, J1939TP_E_IGNORED_ABORT);
  }
}
# endif


# if (J1939TP_CMDT_TX_ENABLED == STD_ON)
J1939TP_LOCAL_INLINE void J1939Tp_CmdtInternalRxIndication_ReceiveTpAbortTx(J1939Tp_TxSduTxNSduIdxOfTxChannelTxNSduType
                                                                            txSduIdx, uint32 pgn)
{
  if (pgn == (uint32) J1939Tp_GetPGNOfTxSdu(txSduIdx)) 
  {
    J1939Tp_TxNSduStateType *txSduState;

    SchM_Enter_J1939Tp_J1939TP_EXCLUSIVE_AREA_TXNSDULOCK();

    txSduState = &J1939Tp_GetTxSduState(J1939Tp_GetTxSduStateIdxOfTxSdu(txSduIdx));

    if ((txSduState->State == J1939TP_STATE_CMDT_RTS) || (txSduState->State == J1939TP_STATE_CMDT_CTS) ||
        (txSduState->State == J1939TP_STATE_CMDT_CTSWAIT) || (txSduState->State == J1939TP_STATE_CMDT_ABORT) ||
        (txSduState->State == J1939TP_STATE_CMDT_DATA))
    {
      /* protected against concurrent main function invocation and concurrent Tx abort */
      txSduState->State = J1939TP_STATE_FINISH; /* VCA_J1939TP_TXSDUSTATE_VIA_TXSDU_CSL03 */
      SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_TXNSDULOCK();

      /*! \trace SPEC-2167303 */
      PduR_J1939TpTxConfirmation(J1939Tp_GetSduIdOfTxSdu(txSduIdx), E_NOT_OK); 

      /* no protection required - transition from uninterruptible state */
      txSduState->State = J1939TP_STATE_IDLE; /* VCA_J1939TP_TXSDUSTATE_VIA_TXSDU_CSL03 */
    }
    else
    {
      SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_TXNSDULOCK();

      txSduState->Aborted = TRUE; /* VCA_J1939TP_TXSDUSTATE_VIA_TXSDU_CSL03 */
    }
  }
  else
  {
    J1939Tp_ReportRuntimeError(J1939TP_SID_RXINDICATION, J1939TP_E_IGNORED_ABORT);
  }
}
# endif


# if (J1939TP_CMDT_RX_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  J1939Tp_CmdtInternalRxIndication_ReceiveTpDt()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
J1939TP_LOCAL_INLINE void J1939Tp_CmdtInternalRxIndication_ReceiveTpDt(J1939Tp_RxSduRxNSduIdxOfRxChannelRxNSduType
                                                                       rxSduIdx, CONSTP2CONST(PduInfoType, AUTOMATIC,
                                                                                            J1939TP_APPL_DATA) info)
{
  J1939Tp_RxNSduStateType *rxSduState;

  SchM_Enter_J1939Tp_J1939TP_EXCLUSIVE_AREA_RXNSDULOCK();

  rxSduState = &J1939Tp_GetRxSduState(J1939Tp_GetRxSduStateIdxOfRxSdu(rxSduIdx));

  if ((rxSduState->State == J1939TP_STATE_CMDT_DATA_FIRST) || (rxSduState->State == J1939TP_STATE_CMDT_DATA))
  {
    /* protected against concurrent timeout and concurrent reception of TP.CM message */
    rxSduState->State = J1939TP_STATE_CMDT_DATA_BUSY; /* VCA_J1939TP_RXSDUSTATE_VIA_RXSDU_CSL03 */
    SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_RXNSDULOCK();

    if (rxSduState->Aborted == TRUE)
    {
      /* no protection required - transition from uninterruptible state */
      rxSduState->State = J1939TP_STATE_FINISH; /* VCA_J1939TP_RXSDUSTATE_VIA_RXSDU_CSL03 */

      /* InSession is active before the current state is reached */
      /*! \trace SPEC-2167305 */
      PduR_J1939TpRxIndication(J1939Tp_GetSduIdOfRxSdu(rxSduIdx), E_NOT_OK); 

      /* no protection required - transition from uninterruptible state */
      rxSduState->State = J1939TP_STATE_IDLE;  /* VCA_J1939TP_RXSDUSTATE_VIA_RXSDU_CSL03 */
    }
    else
    {
      rxSduState->Sequence++; /* VCA_J1939TP_RXSDUSTATE_VIA_RXSDU_CSL03 */

      /* Is expected SN received? */
      if (rxSduState->Sequence == info->SduDataPtr[J1939TP_TPDT_SEQ])
      {
        PduInfoType pdu;
        BufReq_ReturnType tpResult;

        pdu.SduDataPtr = &info->SduDataPtr[J1939TP_TPDT_DATA];
        pdu.SduLength = J1939TP_TPDT_DATA_SIZE;

#  if (J1939TP_RXRETRYSUPPORTOFRXCHANNEL == STD_ON)
        if (J1939Tp_IsRxRetrySupportOfRxChannel(J1939Tp_GetRxChannelChannelIdxOfRxSdu(rxSduIdx)))
        {
          rxSduState->RetryAttempts = 0; /* VCA_J1939TP_RXSDUSTATE_VIA_RXSDU_CSL03 */
        }
#  endif

        /* Calculate PDU length of last packet */
        if (rxSduState->Sequence == rxSduState->Packets)
        {
          pdu.SduLength =
            (PduLengthType) ((rxSduState->Size) -
                             (PduLengthType) (((PduLengthType) ((PduLengthType) (rxSduState->Sequence) - 1u) *
                                               (PduLengthType) J1939TP_TPDT_DATA_SIZE)));
        }

        tpResult = PduR_J1939TpCopyRxData(J1939Tp_GetSduIdOfRxSdu(rxSduIdx), &pdu, &rxSduState->BufSize); /* VCA_J1939TP_FCTCALL_PTR2LOCAL */ /* VCA_J1939TP_RXSDUSTATE_VIA_RXSDU_CSL03 */
        if (tpResult == BUFREQ_OK)
        {
          if (rxSduState->Sequence == rxSduState->Packets)
          {
            rxSduState->TimeOut = J1939Tp_GetTime_Tr(); /*!< \trace SPEC-2167340 */ /* VCA_J1939TP_RXSDUSTATE_VIA_RXSDU_CSL03 */

            J1939Tp_CmdtInternalTransmitTpCmEomack(rxSduIdx);
          }
          else if (rxSduState->Sequence == rxSduState->NextBlock)
          {
            rxSduState->TimeOut = J1939Tp_GetTime_Tr(); /*!< \trace SPEC-2167340 */ /* VCA_J1939TP_RXSDUSTATE_VIA_RXSDU_CSL03 */

            J1939Tp_CmdtInternalTransmitTpCmCts(rxSduIdx);
          }
          else
          {
            rxSduState->TimeOut = J1939Tp_GetTime_T1(); /*!< \trace SPEC-2167340 */ /* VCA_J1939TP_RXSDUSTATE_VIA_RXSDU_CSL03 */
            /* no protection required - transition from uninterruptible state */
            rxSduState->State = J1939TP_STATE_CMDT_DATA; /* VCA_J1939TP_RXSDUSTATE_VIA_RXSDU_CSL03 */
          }
        }
        else
        {
          /*! \trace SPEC-2167311 */
          rxSduState->AbortReason = J1939TP_CAR_RESOURCES; /* VCA_J1939TP_RXSDUSTATE_VIA_RXSDU_CSL03 */
          rxSduState->TimeOut = J1939Tp_GetTime_Tr(); /*!< \trace SPEC-2167340 */ /* VCA_J1939TP_RXSDUSTATE_VIA_RXSDU_CSL03 */

          J1939Tp_CmdtInternalTransmitTpAbortRx(rxSduIdx);
        }
      }
#  if (J1939TP_RXRETRYSUPPORTOFRXCHANNEL == STD_ON)
      else if (J1939Tp_IsRxRetrySupportOfRxChannel(J1939Tp_GetRxChannelChannelIdxOfRxSdu(rxSduIdx)) && 
               (rxSduState->Sequence < info->SduDataPtr[J1939TP_TPDT_SEQ]))
      {
        /* Missed minimum one packet -> Retry */
        rxSduState->TimeOut = J1939Tp_GetTime_T1(); /* VCA_J1939TP_RXSDUSTATE_VIA_RXSDU_CSL03 */
        rxSduState->State = J1939TP_STATE_CMDT_RETRY; /* VCA_J1939TP_RXSDUSTATE_VIA_RXSDU_CSL03 */
        /* Go back to last received SN. */
        rxSduState->Sequence--; /* VCA_J1939TP_RXSDUSTATE_VIA_RXSDU_CSL03 */
      }
#  endif
      else
      {
        /*! \trace SPEC-2167338, SPEC-2167339 */
        J1939Tp_ReportRuntimeError(J1939TP_SID_RXINDICATION, J1939TP_E_INVALID_SN);

        rxSduState->AbortReason = J1939TP_CAR_BAD_SEQ; /* VCA_J1939TP_RXSDUSTATE_VIA_RXSDU_CSL03 */
#  if (J1939TP_RXISOBUSCHANNELOFRXCHANNEL == STD_ON)
        if (J1939Tp_IsRxIsobusChannelOfRxChannel(J1939Tp_GetRxChannelChannelIdxOfRxSdu(rxSduIdx))) 
        {
          if ((rxSduState->Sequence - 1u) == info->SduDataPtr[J1939TP_TPDT_SEQ])
          {
            rxSduState->AbortReason = J1939TP_CAR_DUP_SEQ; /* VCA_J1939TP_RXSDUSTATE_VIA_RXSDU_CSL03 */
          }
        }
#  endif

        rxSduState->TimeOut = J1939Tp_GetTime_Tr(); /*!< \trace SPEC-2167340 */ /* VCA_J1939TP_RXSDUSTATE_VIA_RXSDU_CSL03 */

        J1939Tp_CmdtInternalTransmitTpAbortRx(rxSduIdx);
      }
    }
  }
#  if (J1939TP_RXRETRYSUPPORTOFRXCHANNEL == STD_ON)
  else if (J1939Tp_IsRxRetrySupportOfRxChannel(J1939Tp_GetRxChannelChannelIdxOfRxSdu(rxSduIdx)) && 
           (rxSduState->State == J1939TP_STATE_CMDT_RETRY))
  {
    /* Is last message of CTS Block received? */
    if (rxSduState->NextBlock == info->SduDataPtr[J1939TP_TPDT_SEQ])
    {
      /* protected against concurrent Tx abort and concurrent reception of TP.ConnAbort or TP.DT message */
      rxSduState->State = J1939TP_STATE_CMDT_CTS_BUSY; /* VCA_J1939TP_RXSDUSTATE_VIA_RXSDU_CSL03 */
      SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_RXNSDULOCK();

      J1939Tp_CmdtIncrementAndCheckRetryAttempts(rxSduIdx);
    }
    else
    {
      SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_RXNSDULOCK();
    }
  }
#  endif
  else
  {
    SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_RXNSDULOCK();

    /* TP.DT shall be ignored if received unexpectedly */
  }
} /* PRQA S 6050, 6080, 6030 */ /* MD_MSR_STCAL, MD_MSR_STMIF, MD_MSR_STCYC */
# endif

# define J1939TP_STOP_SEC_CODE
/*lint -save -esym(961, 19.1) */
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*lint -restore */
/*============================================== J1939TP_STOP_SEC_CODE ==============================================*/


/**********************************************************************************************************************
 *  INTERNAL FUNCTIONS
 *********************************************************************************************************************/

/*============================================== J1939TP_START_SEC_CODE =============================================*/
# define J1939TP_START_SEC_CODE
/*lint -save -esym(961, 19.1) */
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*lint -restore */


# if (J1939TP_CMDT_TX_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  J1939Tp_CmdtTxMain()
 *********************************************************************************************************************/
/*!
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
 *
 */
FUNC(void, J1939TP_CODE) J1939Tp_CmdtTxMain(PduIdType txSduIdx)
{
  J1939Tp_TxNSduStateType *txSduState = &J1939Tp_GetTxSduState(J1939Tp_GetTxSduStateIdxOfTxSdu(txSduIdx));

  /* If the aborted flag is set, */
  if (txSduState->Aborted == TRUE)
  {
    /* And the state of the connection is either RTS, CTS, CTSWAIT, ABORT or DATA, */
    SchM_Enter_J1939Tp_J1939TP_EXCLUSIVE_AREA_TXNSDULOCK();
    if ((txSduState->State == J1939TP_STATE_CMDT_RTS) || (txSduState->State == J1939TP_STATE_CMDT_CTS) ||
        (txSduState->State == J1939TP_STATE_CMDT_CTSWAIT) || (txSduState->State == J1939TP_STATE_CMDT_ABORT) ||
        (txSduState->State == J1939TP_STATE_CMDT_DATA))
    {
      /* Then inform the PduR about the missed confirmation and set its state to idle. */
      /* protected against concurrent Tx abort and concurrent reception of TP.ConnAbort */
      txSduState->State = J1939TP_STATE_FINISH; /* VCA_J1939TP_TXSDUSTATE_VIA_TXSDU_CSL03 */
      SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_TXNSDULOCK();

      /*! \trace SPEC-2167303 */
      PduR_J1939TpTxConfirmation(J1939Tp_GetSduIdOfTxSdu(txSduIdx), E_NOT_OK);

      /* no protection required - transition from uninterruptible state */
      txSduState->State = J1939TP_STATE_IDLE; /* VCA_J1939TP_TXSDUSTATE_VIA_TXSDU_CSL03 */
    }
    else
    {
      SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_TXNSDULOCK();
    }
  }
  /* Or if a timeout occurs, */
  else if (txSduState->TimeOut == 0u)
  {
#  if (J1939TP_RUNTIME_ERROR_REPORT == STD_ON)
    /* If RuntimeErrorReport is enabled, determine the current state and set the errorId accordingly. */
    uint8 errorId = J1939TP_E_NO_ERROR;

    switch (txSduState->State)
    {
    case J1939TP_STATE_CMDT_CTS:
      errorId = J1939TP_E_TIMEOUT_T3;
      break;

    case J1939TP_STATE_CMDT_CTSWAIT:
      errorId = J1939TP_E_TIMEOUT_T4;
      break;

    case J1939TP_STATE_CMDT_RTS:
    case J1939TP_STATE_CMDT_ABORT:
    case J1939TP_STATE_CMDT_DATA:
      errorId = J1939TP_E_TIMEOUT_TR;
      break;

    default: /* MISRA */ /* COV_J1939TP_CMDT_SWITCHCASE_DEFAULT */
      break;
    }

    J1939Tp_ReportRuntimeError(J1939TP_SID_MAINFUNCTION, errorId);
#  endif

    /* And the state of the connection is either RTS or abort frame, */
    SchM_Enter_J1939Tp_J1939TP_EXCLUSIVE_AREA_TXNSDULOCK();
    if ((txSduState->State == J1939TP_STATE_CMDT_RTS) || (txSduState->State == J1939TP_STATE_CMDT_ABORT))
    {
      /* Then inform the PduR about the missed confirmation and set its state to idle. */
      /* protected against concurrent Tx abort and concurrent reception of TP.ConnAbort */
      txSduState->State = J1939TP_STATE_FINISH; /* VCA_J1939TP_TXSDUSTATE_VIA_TXSDU_CSL03 */
      SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_TXNSDULOCK();

      /*! \trace SPEC-2167303 */
      PduR_J1939TpTxConfirmation(J1939Tp_GetSduIdOfTxSdu(txSduIdx), E_NOT_OK);

      /* no protection required - transition from uninterruptible state */
      txSduState->State = J1939TP_STATE_IDLE; /* VCA_J1939TP_TXSDUSTATE_VIA_TXSDU_CSL03 */
    }
    /* Or the state of the connection is either CTS, CTSWAIT or data frame, */
    else if ((txSduState->State == J1939TP_STATE_CMDT_CTS) || (txSduState->State == J1939TP_STATE_CMDT_CTSWAIT) ||
             (txSduState->State == J1939TP_STATE_CMDT_DATA))
    {
      /* Then request the transmission of an abort frame and set the abort reason, the timeout and the state
         accordingly. */
      /*! \trace SPEC-2167341 */
      txSduState->AbortReason = J1939TP_CAR_TIMEOUT; /* VCA_J1939TP_TXSDUSTATE_VIA_TXSDU_CSL03 */
      txSduState->TimeOut = J1939Tp_GetTime_Tr(); /*!< \trace SPEC-2167340 */ /* VCA_J1939TP_TXSDUSTATE_VIA_TXSDU_CSL03 */
      /* protected against concurrent Tx abort and concurrent reception of TP.ConnAbort */
      txSduState->State = J1939TP_STATE_CMDT_ABORT_BUSY; /* VCA_J1939TP_TXSDUSTATE_VIA_TXSDU_CSL03 */
      SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_TXNSDULOCK();

      J1939Tp_CmdtInternalTransmitTpAbortTx(txSduIdx);
    }
    else
    {
      SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_TXNSDULOCK();
    }
  }
  /* Otherwise */
  else
  {
    /* Decrement the timeout value by one and determine the current state. */
    --txSduState->TimeOut; /* VCA_J1939TP_TXSDUSTATE_VIA_TXSDU_CSL03 */

    SchM_Enter_J1939Tp_J1939TP_EXCLUSIVE_AREA_TXNSDULOCK();
    switch (txSduState->State)
    {
    case J1939TP_STATE_CMDT_RTS:
      /* If it is in state RTS, then request transmission of the connection management frame Request To Send. */
      /* protected against concurrent Tx abort and concurrent reception of TP.ConnAbort */
      txSduState->State = J1939TP_STATE_CMDT_RTS_BUSY; /* VCA_J1939TP_TXSDUSTATE_VIA_TXSDU_CSL03 */
      SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_TXNSDULOCK();

      J1939Tp_CmdtInternalTransmitTpCmRts(txSduIdx);
      break;

    case J1939TP_STATE_CMDT_ABORT:
      /* If it is in state abort frame, then request transmission of the abort frame. */
      /* protected against concurrent Tx abort and concurrent reception of TP.ConnAbort */
      txSduState->State = J1939TP_STATE_CMDT_ABORT_BUSY; /* VCA_J1939TP_TXSDUSTATE_VIA_TXSDU_CSL03 */
      SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_TXNSDULOCK();

      J1939Tp_CmdtInternalTransmitTpAbortTx(txSduIdx);
      break;

    case J1939TP_STATE_CMDT_DATA:
      /* If it is in state data frame, then request transmission of the data frame. */
      /* protected against concurrent Tx abort and concurrent reception of TP.ConnAbort */
      txSduState->State = J1939TP_STATE_CMDT_DATA_BUSY; /* VCA_J1939TP_TXSDUSTATE_VIA_TXSDU_CSL03 */
      SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_TXNSDULOCK();

      /*! \trace SPEC-2167316 */
      J1939Tp_CmdtInternalTransmitTpDt(txSduIdx);
      break;

    default:
      SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_TXNSDULOCK();
      break;
    }
  }
} /* J1939Tp_CmdtTxMain */ /* PRQA S 6030 */ /* MD_MSR_STCYC */
# endif


# if (J1939TP_CMDT_RX_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  J1939Tp_CmdtRxMain()
 *********************************************************************************************************************/
/*!
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
FUNC(void, J1939TP_CODE) J1939Tp_CmdtRxMain(PduIdType rxSduIdx)
{
  J1939Tp_RxNSduStateType *rxSduState = &J1939Tp_GetRxSduState(J1939Tp_GetRxSduStateIdxOfRxSdu(rxSduIdx));

  /* If the aborted flag is set, */
  if (rxSduState->Aborted == TRUE)
  {
    /* And the state of the connection is either CTS, CTSWAIT, DATA_FIRST, DATA, EOMACK or ABORT, */
    SchM_Enter_J1939Tp_J1939TP_EXCLUSIVE_AREA_RXNSDULOCK();
    if ((rxSduState->State == J1939TP_STATE_CMDT_CTS) || (rxSduState->State == J1939TP_STATE_CMDT_CTSWAIT) ||
        (rxSduState->State == J1939TP_STATE_CMDT_DATA_FIRST) || (rxSduState->State == J1939TP_STATE_CMDT_DATA) ||
        (rxSduState->State == J1939TP_STATE_CMDT_EOMACK) || (rxSduState->State == J1939TP_STATE_CMDT_ABORT))
    {
      /* If the connection is in a valid session, then inform the PduR about the missed indication and set its state to
         idle. */
      /* protected against concurrent Tx abort and concurrent reception of TP.ConnAbort or TP.DT message */
      rxSduState->State = J1939TP_STATE_FINISH; /* VCA_J1939TP_RXSDUSTATE_VIA_RXSDU_CSL03 */
      SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_RXNSDULOCK();

      if (rxSduState->InSession == TRUE)
      {
        /*! \trace SPEC-2167305 */
        PduR_J1939TpRxIndication(J1939Tp_GetSduIdOfRxSdu(rxSduIdx), E_NOT_OK);
      }

      /* no protection required - transition from uninterruptible state */
      rxSduState->State = J1939TP_STATE_IDLE; /* VCA_J1939TP_RXSDUSTATE_VIA_RXSDU_CSL03 */
    }
    else
    {
      SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_RXNSDULOCK();
    }
  }
  /* Or if a timeout occurs, */
  else if (rxSduState->TimeOut == 0u)
  {
#  if (J1939TP_RUNTIME_ERROR_REPORT == STD_ON)
    /* If RuntimeErrorReport is enabled, determine the current state and set the errorId accordingly. */
    uint8 errorId = J1939TP_E_NO_ERROR;

    switch (rxSduState->State)
    {
    case J1939TP_STATE_CMDT_CTS:
    case J1939TP_STATE_CMDT_EOMACK:
    case J1939TP_STATE_CMDT_ABORT:
      errorId = J1939TP_E_TIMEOUT_TR;
      break;

    case J1939TP_STATE_CMDT_CTSWAIT:
      errorId = J1939TP_E_TIMEOUT_TH;
      break;

    case J1939TP_STATE_CMDT_DATA_FIRST:
      errorId = J1939TP_E_TIMEOUT_T2;
      break;

    case J1939TP_STATE_CMDT_DATA:
    case J1939TP_STATE_CMDT_RETRY:
      errorId = J1939TP_E_TIMEOUT_T1;
      break;

    default: /* MISRA */ /* COV_J1939TP_CMDT_SWITCHCASE_DEFAULT */
      break;
    }

    J1939Tp_ReportRuntimeError(J1939TP_SID_MAINFUNCTION, errorId);
#  endif

    /* And the state of the connection is abort frame, */
    SchM_Enter_J1939Tp_J1939TP_EXCLUSIVE_AREA_RXNSDULOCK();
    if (rxSduState->State == J1939TP_STATE_CMDT_ABORT)
    {
      /* If the connection is in a valid session, then inform the PduR about the missed indication and set its state to
         idle. */
      /* protected against concurrent Tx abort and concurrent reception of TP.ConnAbort message */
      rxSduState->State = J1939TP_STATE_FINISH; /* VCA_J1939TP_RXSDUSTATE_VIA_RXSDU_CSL03 */
      SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_RXNSDULOCK();

      if (rxSduState->InSession == TRUE)
      {
        /*! \trace SPEC-2167305 */
        PduR_J1939TpRxIndication(J1939Tp_GetSduIdOfRxSdu(rxSduIdx), E_NOT_OK);
      }

      /* no protection required - transition from uninterruptible state */
      rxSduState->State = J1939TP_STATE_IDLE; /* VCA_J1939TP_RXSDUSTATE_VIA_RXSDU_CSL03 */
    }
    /* Or the state of the connection is either CTS, CTSWAIT, DATA_FIRST, EOMACK or DATA, */
    else if ((rxSduState->State == J1939TP_STATE_CMDT_CTS) || (rxSduState->State == J1939TP_STATE_CMDT_CTSWAIT) ||
             (rxSduState->State == J1939TP_STATE_CMDT_DATA_FIRST) || (rxSduState->State == J1939TP_STATE_CMDT_DATA) ||
             (rxSduState->State == J1939TP_STATE_CMDT_EOMACK))
    {
#  if (J1939TP_RXRETRYSUPPORTOFRXCHANNEL == STD_ON)
      /* If RxRetrySupport is enabled and the connection is in state DATA_FIRST or DATA */
      if (((rxSduState->State == J1939TP_STATE_CMDT_DATA_FIRST) || (rxSduState->State == J1939TP_STATE_CMDT_DATA)) && J1939Tp_IsRxRetrySupportOfRxChannel(J1939Tp_GetRxChannelChannelIdxOfRxSdu(rxSduIdx)))
      {
        /* protected against concurrent Tx abort and concurrent reception of TP.ConnAbort or TP.DT message */
        rxSduState->State = J1939TP_STATE_CMDT_CTS_BUSY; /* VCA_J1939TP_RXSDUSTATE_VIA_RXSDU_CSL03 */
        SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_RXNSDULOCK();

        J1939Tp_CmdtIncrementAndCheckRetryAttempts(rxSduIdx);
      }
      /* Otherwise */
      else
#  endif
      {
        /* Then request the transmission of an abort frame and set the abort reason, the timeout and the state
           accordingly. */
        /*! \trace SPEC-2167342 */
        rxSduState->AbortReason = J1939TP_CAR_TIMEOUT; /* VCA_J1939TP_RXSDUSTATE_VIA_RXSDU_CSL03 */
        rxSduState->TimeOut = J1939Tp_GetTime_Tr(); /*!< \trace SPEC-2167340 */ /* VCA_J1939TP_RXSDUSTATE_VIA_RXSDU_CSL03 */
        /* protected against concurrent Tx abort and concurrent reception of TP.ConnAbort or TP.DT message */
        rxSduState->State = J1939TP_STATE_CMDT_ABORT_BUSY; /* VCA_J1939TP_RXSDUSTATE_VIA_RXSDU_CSL03 */
        SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_RXNSDULOCK();

        J1939Tp_CmdtInternalTransmitTpAbortRx(rxSduIdx);
      }
    }
#  if (J1939TP_RXRETRYSUPPORTOFRXCHANNEL == STD_ON)
    /* Or if the state is RETRY in case RxRetrySupport is enabled */
    else if (J1939Tp_IsRxRetrySupportOfRxChannel(J1939Tp_GetRxChannelChannelIdxOfRxSdu(rxSduIdx)) && 
             (rxSduState->State == J1939TP_STATE_CMDT_RETRY))
    {
      /* protected against concurrent Tx abort and concurrent reception of TP.ConnAbort or TP.DT message */
      rxSduState->State = J1939TP_STATE_CMDT_CTS_BUSY; /* VCA_J1939TP_RXSDUSTATE_VIA_RXSDU_CSL03 */
      SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_RXNSDULOCK();

      J1939Tp_CmdtIncrementAndCheckRetryAttempts(rxSduIdx);
    }
#  endif
    else
    {
      SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_RXNSDULOCK();
    }
  }
  /* Otherwise */
  else
  {
    /* Decrement the timeout value by one and determine the current state. */
    --rxSduState->TimeOut; /* VCA_J1939TP_RXSDUSTATE_VIA_RXSDU_CSL03 */

    SchM_Enter_J1939Tp_J1939TP_EXCLUSIVE_AREA_RXNSDULOCK();
    switch (rxSduState->State)
    {
    case J1939TP_STATE_CMDT_CTS:
      /* If it is in state CTS, then request transmission of the connection management frame Clear To Send. */
      /* protected against concurrent Tx abort and concurrent reception of TP.ConnAbort message */
      rxSduState->State = J1939TP_STATE_CMDT_CTS_BUSY; /* VCA_J1939TP_RXSDUSTATE_VIA_RXSDU_CSL03 */
      SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_RXNSDULOCK();

      J1939Tp_CmdtInternalTransmitTpCmCts(rxSduIdx);
      break;

    case J1939TP_STATE_CMDT_CTSWAIT:
      /* If it is in state CTSWAIT, then request transmission of wait frame. */
      /* protected against concurrent Tx abort and concurrent reception of TP.ConnAbort message */
      rxSduState->State = J1939TP_STATE_CMDT_CTSWAIT_BUSY; /* VCA_J1939TP_RXSDUSTATE_VIA_RXSDU_CSL03 */
      SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_RXNSDULOCK();

      J1939Tp_CmdtInternalTransmitTpCmCts(rxSduIdx);
      break;

    case J1939TP_STATE_CMDT_EOMACK:
      /* If it is in state EOMACK, then request transmission of the End Of Message ACKnowledge frame. */
      /* protected against concurrent Tx abort and concurrent reception of TP.ConnAbort message */
      rxSduState->State = J1939TP_STATE_CMDT_EOMACK_BUSY; /* VCA_J1939TP_RXSDUSTATE_VIA_RXSDU_CSL03 */
      SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_RXNSDULOCK();

      J1939Tp_CmdtInternalTransmitTpCmEomack(rxSduIdx);
      break;

    case J1939TP_STATE_CMDT_ABORT:
      /* If it is in state abort frame, then request transmission of the abort frame. */
      /* protected against concurrent Tx abort and concurrent reception of TP.ConnAbort message */
      rxSduState->State = J1939TP_STATE_CMDT_ABORT_BUSY; /* VCA_J1939TP_RXSDUSTATE_VIA_RXSDU_CSL03 */
      SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_RXNSDULOCK();

      J1939Tp_CmdtInternalTransmitTpAbortRx(rxSduIdx);
      break;

    default:
      SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_RXNSDULOCK();
      break;
    }
  }
} /* J1939Tp_CmdtRxMain */ /* PRQA S 6030, 6050, 6080 */ /* MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */
# endif


# if (J1939TP_CMDT_TX_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  J1939Tp_CmdtTransmit()
 *********************************************************************************************************************/
/*!
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
 *
 */
FUNC(Std_ReturnType, J1939TP_CODE) J1939Tp_CmdtTransmit(PduIdType txSduIdx,
                                                        P2CONST(PduInfoType, AUTOMATIC, J1939TP_APPL_DATA) info)
{
  Std_ReturnType result = E_NOT_OK;

  /* Verify that the SDU length does not exceed J1939TP_MAX_LENGTH. */
  if (info->SduLength > J1939TP_MAX_LENGTH) /* PRQA S 2992, 2996 */ /* MD_J1939Tp_14.3_Cmdt, MD_MSR_RetVal */
  { /* PRQA S 2880 */ /* MD_J1939Tp_14.1_2880 */
    /*! \trace SPEC-2167289 */
    J1939Tp_ReportDevError(J1939TP_SID_TRANSMIT, J1939TP_E_INVALID_LENGTH); /* PRQA S 2880 */ /* MD_MSR_Unreachable */
  }
  else
  {
    J1939Tp_TxNSduStateType *txSduState = &J1939Tp_GetTxSduState(J1939Tp_GetTxSduStateIdxOfTxSdu(txSduIdx));

    /* Proceed If the state is IDLE */
    SchM_Enter_J1939Tp_J1939TP_EXCLUSIVE_AREA_TXNSDULOCK();
    if (txSduState->State == J1939TP_STATE_IDLE)
    {
      /* Then set the state to RTS_BUSY and set the aborted flag to false. */
      txSduState->Aborted = FALSE; /* VCA_J1939TP_TXSDUSTATE_VIA_TXSDU_CSL03 */
      /* protected against a reentrant call for the same N-SDU */ /* Check if this is necessary */
      txSduState->State = J1939TP_STATE_CMDT_RTS_BUSY;
      SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_TXNSDULOCK();

      {
        J1939Tp_TxChannelChannelIdxOfTxSduType txChannelIdx = J1939Tp_GetTxChannelChannelIdxOfTxSdu(txSduIdx);
        uint8 da, sa;
        boolean found;

        /* Determine source and destination address */
        /*! \trace SPEC-2167312 */
        if (J1939Tp_GetTxSaOfTxChannel(txChannelIdx) == J1939TP_NO_ADDRESS_CONFIGURED) 
        {
          sa = info->SduDataPtr[J1939TP_MDL_SA_POS];
        }
        else
        {
          sa = J1939Tp_GetTxSaOfTxChannel(txChannelIdx);
        }

        /*! \trace SPEC-2167312 */
        if (J1939Tp_GetTxDaOfTxChannel(txChannelIdx) == J1939TP_NO_ADDRESS_CONFIGURED)
        {
          da = info->SduDataPtr[J1939TP_MDL_DA_POS];
        }
        else
        {
          da = J1939Tp_GetTxDaOfTxChannel(txChannelIdx);
        }

        /* Search for connections with the same characteristics. */
        found = J1939Tp_CmdtInternalTransmit_SearchConflictingTxChannel(txSduIdx, txChannelIdx, sa, da);

        /* If no connection was found */
        /*! \trace SPEC-2167293 */
        if (found == FALSE)
        {
#  if (J1939TP_TXRETRYSUPPORTOFTXCHANNEL == STD_ON)
          /* If TxRetrySupport is enabled */
          if (J1939Tp_IsTxRetrySupportOfTxChannel(txChannelIdx))
          {
            /* Then initialize the TpDataState with TP_CONFPENDING. */
            txSduState->Retry.TpDataState = TP_CONFPENDING; /* VCA_J1939TP_TXSDUSTATE_VIA_TXSDU_CSL03 */
            txSduState->Retry.TxTpDataCnt = 0u; /* VCA_J1939TP_TXSDUSTATE_VIA_TXSDU_CSL03 */
          }
#  endif
          /* Prepares the data to be transmitted. */
          txSduState->Size = info->SduLength; /* VCA_J1939TP_TXSDUSTATE_VIA_TXSDU_CSL03 */
          txSduState->Packets = (uint32) (J1939Tp_Get_Packets((uint32) (info->SduLength))); /* VCA_J1939TP_TXSDUSTATE_VIA_TXSDU_CSL03 */
          /*! \trace SPEC-2167324 */
          txSduState->MaxBlock = J1939Tp_GetTxMaxPacketsPerBlockOfTxChannel(txChannelIdx);  /* VCA_J1939TP_TXSDUSTATE_VIA_TXSDU_CSL03 */
          txSduState->Sender = sa; /* VCA_J1939TP_TXSDUSTATE_VIA_TXSDU_CSL03 */
          txSduState->Receiver = da; /* VCA_J1939TP_TXSDUSTATE_VIA_TXSDU_CSL03 */
          txSduState->Priority = J1939Tp_InternalGetPriority(txSduIdx, info); /* VCA_J1939TP_TXSDUSTATE_VIA_TXSDU_CSL03 */
          txSduState->Sequence = J1939TP_TX_SEQUENCE_INITIAL; /* VCA_J1939TP_TXSDUSTATE_VIA_TXSDU_CSL03 */
          txSduState->TimeOut = J1939Tp_GetTime_Tr(); /*!< \trace SPEC-2167340 */ /* VCA_J1939TP_TXSDUSTATE_VIA_TXSDU_CSL03 */

          /* Request the transmission of a Connection Management message Request To Send. */
          J1939Tp_CmdtInternalTransmitTpCmRts(txSduIdx);

          /* Set the return value to successful. */
          result = E_OK;
        }
        /* Otherwise a connection with the same characteristics already exists. */
        else
        {
          /* Then set the state to IDLE. */
          /* no protection required - transition from uninterruptible state */
          txSduState->State = J1939TP_STATE_IDLE;
        }
      }
    }
    /* For all other states */
    else
    {
      SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_TXNSDULOCK();
    }
  }

  /* Return the result of the function. */
  return result;
} /* J1939Tp_CmdtTransmit */
# endif


/**********************************************************************************************************************
 *  J1939Tp_CmdtTxConfirmation()
 *********************************************************************************************************************/
/*!
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
FUNC(void, J1939TP_CODE) J1939Tp_CmdtTxConfirmation(PduIdType sduIdx, J1939Tp_PduTypeOfTxPduType txPduType,
                                                    J1939Tp_NSduType sduType)
{
# if ((J1939TP_CMDT_TX_ENABLED == STD_ON) && (J1939TP_CMDT_RX_ENABLED == STD_ON))
  /* Process confirmation of a Tx NSDU. */
  if (sduType == J1939TP_NSDU_CMDT_TX)
# endif
# if (J1939TP_CMDT_TX_ENABLED == STD_ON)
  {
    J1939Tp_TxNSduStateType *txSduState = &J1939Tp_GetTxSduState(J1939Tp_GetTxSduStateIdxOfTxSdu(sduIdx));

    /* When the Pdu is a command message,
     * determine the SDU's state.
     *    In state J1939TP_STATE_CMDT_RTS_CONF:
     *       Set Timeout to T3.
     *       Set state to J1939TP_STATE_CMDT_CTS.
     *    In state J1939TP_STATE_CMDT_ABORT_CONF:
     *       Set state to J1939TP_STATE_FINISH.
     *       Inform the PduR about the negative confirmation.
     *       Set state to J1939TP_STATE_IDLE. 
     */
    if (txPduType == J1939TP_TPCM_PDUTYPEOFTXPDU)
    {
      SchM_Enter_J1939Tp_J1939TP_EXCLUSIVE_AREA_TXNSDULOCK();
      switch (txSduState->State)
      {
      case J1939TP_STATE_CMDT_RTS_CONF:
        /*!< \trace SPEC-2167340 */
        txSduState->TimeOut = J1939Tp_GetTime_T3();  /* VCA_J1939TP_TXSDUSTATE_VIA_TXSDU_CSL03 */
        /* protected against concurrent transmission failure and early Tx confirmation timeout */
        txSduState->State = J1939TP_STATE_CMDT_CTS; /* VCA_J1939TP_TXSDUSTATE_VIA_TXSDU_CSL03 */
        SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_TXNSDULOCK();
        break;

      case J1939TP_STATE_CMDT_ABORT_CONF:
        /* protected against concurrent transmission failure and early Tx confirmation timeout */
        txSduState->State = J1939TP_STATE_FINISH; /* VCA_J1939TP_TXSDUSTATE_VIA_TXSDU_CSL03 */
        SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_TXNSDULOCK();

        /*! \trace SPEC-2167303 */
        PduR_J1939TpTxConfirmation(J1939Tp_GetSduIdOfTxSdu(sduIdx), E_NOT_OK); 

        /* no protection required - transition from uninterruptible state */
        txSduState->State = J1939TP_STATE_IDLE; /* VCA_J1939TP_TXSDUSTATE_VIA_TXSDU_CSL03 */
        break;

      default:
        SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_TXNSDULOCK();
        break;
      }
    }
    /* When the Pdu is a data message,
     * determine the SDU's state.
     *    In state J1939TP_STATE_CMDT_DATA_CONF:
     *       Increment the sequence counter.
     *       If the sequence number equals the number of the NextBlock,
     *           Set Timeout to T3.
     *           Set state to J1939TP_STATE_CMDT_CTS.
     *       Otherwise
     *           Set the retry TpDataState to TP_CONFPENDING.
     *           Initialize the retry TxTpDataCnt to 0.
     *           Set the Timeout to Tr.
     *           Set state to J1939TP_STATE_DATA_BUSY.
     *           Request a transmission of the next data message.
     */
    else /* txPduType == J1939TP_TPDT_PDUTYPEOFTXPDU */
    {
      SchM_Enter_J1939Tp_J1939TP_EXCLUSIVE_AREA_TXNSDULOCK();
      if (txSduState->State == J1939TP_STATE_CMDT_DATA_CONF)
      {
        txSduState->Sequence++; /* VCA_J1939TP_TXSDUSTATE_VIA_TXSDU_CSL03 */

        if (txSduState->Sequence == txSduState->NextBlock)
        {
          /*!< \trace SPEC-2167340 */
          txSduState->TimeOut = J1939Tp_GetTime_T3();  /* VCA_J1939TP_TXSDUSTATE_VIA_TXSDU_CSL03 */
          /* protected against concurrent transmission failure and early Tx confirmation timeout */
          txSduState->State = J1939TP_STATE_CMDT_CTS; /* VCA_J1939TP_TXSDUSTATE_VIA_TXSDU_CSL03 */
          SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_TXNSDULOCK();
        }
        else
        {
          txSduState->Retry.TpDataState = TP_CONFPENDING; /* VCA_J1939TP_TXSDUSTATE_VIA_TXSDU_CSL03 */
          txSduState->Retry.TxTpDataCnt = 0u; /* VCA_J1939TP_TXSDUSTATE_VIA_TXSDU_CSL03 */
          txSduState->TimeOut = J1939Tp_GetTime_Tr(); /*!< \trace SPEC-2167340 */ /* VCA_J1939TP_TXSDUSTATE_VIA_TXSDU_CSL03 */
          /* protected against concurrent transmission failure and early Tx confirmation timeout */
          txSduState->State = J1939TP_STATE_CMDT_DATA_BUSY; /* VCA_J1939TP_TXSDUSTATE_VIA_TXSDU_CSL03 */
          SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_TXNSDULOCK();

          J1939Tp_CmdtInternalTransmitTpDt(sduIdx);
        }
      }
      else
      {
        SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_TXNSDULOCK();
      }
    }
  }
# endif
# if ((J1939TP_CMDT_TX_ENABLED == STD_ON) && (J1939TP_CMDT_RX_ENABLED == STD_ON))
  /* Process confirmation of an Rx NSDU. */
  else  /* J1939TP_NSDU_CMDT_RX */
# endif
# if (J1939TP_CMDT_RX_ENABLED == STD_ON)
  {
    /* Determine the SDU's state.
     *   In state J1939TP_STATE_CMDT_CTSWAIT_CONF:
     *      Set Timeout to Th.
     *      Set state to J1939TP_STATE_CMDT_CTSWAIT.
     *   In state J1939TP_STATE_CMDT_CTS_CONF:
     *      Set Timeout to T2.
     *      Set state to J1939TP_STATE_CMDT_DATA_FIRST.
     *   In state J1939TP_STATE_CMDT_EOMACK_CONF:
     *      Set state to J1939TP_STATE_FINISH.
     *      Indicate the reception to PduR.
     *      Set state to J1939TP_STATE_IDLE.
     *   In state J1939TP_STATE_CMDT_ABORT_CONF:
     *      Set state to J1939TP_STATE_FINISH.
     *      If InSession,
     *         Indicate the negative reception to PduR.
     *      Set state to J1939TP_STATE_IDLE.
     */
    J1939Tp_RxNSduStateType *rxSduState = &J1939Tp_GetRxSduState(J1939Tp_GetRxSduStateIdxOfRxSdu(sduIdx));

    SchM_Enter_J1939Tp_J1939TP_EXCLUSIVE_AREA_RXNSDULOCK();
    switch (rxSduState->State)
    {
    case J1939TP_STATE_CMDT_CTSWAIT_CONF:
      rxSduState->TimeOut = J1939Tp_GetTime_Th(); /*!< \trace SPEC-2167340 */ /* VCA_J1939TP_RXSDUSTATE_VIA_RXSDU_CSL03 */
      /* protected against concurrent transmission failure and early Tx confirmation timeout */
      rxSduState->State = J1939TP_STATE_CMDT_CTSWAIT; /* VCA_J1939TP_RXSDUSTATE_VIA_RXSDU_CSL03 */
      SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_RXNSDULOCK();
      break;

    case J1939TP_STATE_CMDT_CTS_CONF:
      rxSduState->TimeOut = J1939Tp_GetTime_T2(); /*!< \trace SPEC-2167340 */ /* VCA_J1939TP_RXSDUSTATE_VIA_RXSDU_CSL03 */
      /* protected against concurrent transmission failure and early Tx confirmation timeout */
      rxSduState->State = J1939TP_STATE_CMDT_DATA_FIRST; /* VCA_J1939TP_RXSDUSTATE_VIA_RXSDU_CSL03 */
      SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_RXNSDULOCK();
      break;

    case J1939TP_STATE_CMDT_EOMACK_CONF:
      /* protected against early Tx confirmation timeout */
      rxSduState->State = J1939TP_STATE_FINISH; /* VCA_J1939TP_RXSDUSTATE_VIA_RXSDU_CSL03 */
      SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_RXNSDULOCK();

      /* InSession is active before the current state is reached */
      /*! \trace SPEC-2167304 */
      PduR_J1939TpRxIndication(J1939Tp_GetSduIdOfRxSdu(sduIdx), E_OK); 

      /* no protection required - transition from uninterruptible state */
      rxSduState->State = J1939TP_STATE_IDLE; /* VCA_J1939TP_RXSDUSTATE_VIA_RXSDU_CSL03 */
      break;

    case J1939TP_STATE_CMDT_ABORT_CONF:
      /* protected against concurrent transmission failure and early Tx confirmation timeout */
      rxSduState->State = J1939TP_STATE_FINISH; /* VCA_J1939TP_RXSDUSTATE_VIA_RXSDU_CSL03 */
      SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_RXNSDULOCK();

      if (rxSduState->InSession == TRUE)
      {
        /*! \trace SPEC-2167305 */
        PduR_J1939TpRxIndication(J1939Tp_GetSduIdOfRxSdu(sduIdx), E_NOT_OK); 
      }

      /* no protection required - transition from uninterruptible state */
      rxSduState->State = J1939TP_STATE_IDLE; /* VCA_J1939TP_RXSDUSTATE_VIA_RXSDU_CSL03 */
      break;

    default:
      SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_RXNSDULOCK();
      break;
    }
  }
# endif

  J1939TP_DUMMY_STATEMENT(txPduType); /* PRQA S 3112, 1338, 2983 */ /* MD_MSR_DummyStmt */
  J1939TP_DUMMY_STATEMENT(sduType); /* PRQA S 3112, 1338, 2983 */ /* MD_MSR_DummyStmt */
} /* J1939Tp_CmdtTxConfirmation */ /* PRQA S 6030 */ /* MD_MSR_STCYC */


/**********************************************************************************************************************
 *  J1939Tp_CmdtRxIndication()
 *********************************************************************************************************************/
/*!
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
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(void, J1939TP_CODE) J1939Tp_CmdtRxIndication(PduIdType rxPduIdx,
                                                  P2CONST(PduInfoType, AUTOMATIC, J1939TP_APPL_DATA) info,
                                                  J1939Tp_PduTypeOfRxPduType rxPduType, uint8 sa, uint8 da)
{
# if (J1939TP_CANIF_DLCCHECK == STD_OFF)
  /* Make sure that the Pdu's length is J1939TP_NPDU_LENGTH. */
  if (info->SduLength == J1939TP_NPDU_LENGTH)
# endif
  { 
    /* When the destination address is invalid,
     *    report the runtime error J1939TP_E_INVALID_DA.
     */
    if (!J1939Tp_DA_Valid(da))
    {
      /*! \trace SPEC-2167310 */
      J1939Tp_ReportRuntimeError(J1939TP_SID_RXINDICATION, J1939TP_E_INVALID_DA);
    }
    /* Otherwise, */
    else
    {
      /* If the destination address is the broadcast address,
       *    and if the control byte is different from J1939TP_CB_BAM,
       *        then report the runtime error J1939TP_E_INVALID_CONTROL_BYTE.
       */
      if (da == J1939TP_BROADCAST_ADDRESS)
      {
        /*! \trace SPEC-2167310 */
# if (J1939TP_RUNTIME_ERROR_REPORT == STD_ON)
        if (info->SduDataPtr[J1939TP_TPCM_CB] != J1939TP_CB_BAM)
        {
          J1939Tp_ReportRuntimeError(J1939TP_SID_RXINDICATION, J1939TP_E_INVALID_CONTROL_BYTE);
        }
# endif
      }
      /* Otherwise, */
      else
      {
        /* If the Rx Pdu is a command message,
         *    Get the PGN and report the runtime error J1939TP_E_INVALID_PGN if it is invalid.
         *    Otherwise
         *       The control byte is J1939TP_CB_RTS:
         *          Get the message size and report the runtime error J1939TP_E_INVALID_TMS if it is greater than J1939TP_MAX_LENGTH.
         *          Otherwise
         *             If there is a free connection for the incoming PDU,
         *                Process the reception of a Request to Send message.
         *       The control byte is J1939TP_CB_CTS:
         *          If an active connection is found for this Pdu,
         *             Process the reception of a Clear to Send message.
         *       The control byte is J1939TP_CB_EOMACK:
         *          If an active connection is found for this Pdu,
         *             Process the reception of an End of Message Acknowledge.
         *       The control byte is J1939TP_CB_ABORT:
         *          If there is an invalid Connection Abort Reason,
         *             Report the runtime error J1939TP_E_INVALID_CAR.
         *          If an active Rx connection is found for this Rx Pdu,
         *             Process the reception of an Abort message.
         *          If an active Tx connection is found for this Rx Pdu,
         *             Process the reception of an Abort message.
         *       Otherwise:
         *          Report the runtime error J1939TP_E_INVALID_CONTROL_BYTE.
         * If the Rx Pdu is a data message,
         *    If an active connection is found for this Pdu,
         *       Process the reception of a data message.
         */
        if (rxPduType == J1939TP_TPCM_PDUTYPEOFRXPDU)
        {
          /* PRQA S 1891 1 */ /* MD_J1939Tp_10.7 */
          uint32 pgn = J1939Tp_Get_PGN(info->SduDataPtr[J1939TP_TPCM_PGN_LO], info->SduDataPtr[J1939TP_TPCM_PGN_MD],
                                       info->SduDataPtr[J1939TP_TPCM_PGN_HI]);

          if (!J1939Tp_PGN_Valid(pgn))
          {
            /*! \trace SPEC-2167310 */
            J1939Tp_ReportRuntimeError(J1939TP_SID_RXINDICATION, J1939TP_E_INVALID_PGN);
          }
          else
          {
            /* PRQA S 4342 1 */ /* MD_J1939Tp_10.5 */
            J1939Tp_ControlByteType cb = (J1939Tp_ControlByteType) (info->SduDataPtr[J1939TP_TPCM_CB]);

            switch (cb)
            {
            case J1939TP_CB_RTS:
# if (J1939TP_CMDT_RX_ENABLED == STD_ON)
            {
              uint16 size = J1939Tp_Get_TMS(info->SduDataPtr[J1939TP_TPCM_TMS_LO],
                                            info->SduDataPtr[J1939TP_TPCM_TMS_HI]);

              if (size > J1939TP_MAX_LENGTH)
              {
                J1939Tp_ReportRuntimeError(J1939TP_SID_RXINDICATION, J1939TP_E_INVALID_TMS);
              }
              else
              {
                J1939Tp_RxSduRxNSduIdxOfRxChannelRxNSduType rxSduIdx = 0u;

                if (J1939Tp_CmdtInternalRxIndication_AllocateRxChannel(rxPduIdx, sa, da, pgn, &rxSduIdx) == TRUE)
                {
                  J1939Tp_CmdtInternalRxIndication_ReceiveTpCmRts(rxSduIdx, info, sa, da, size);
                }
              }
            }
# endif
              break;

            case J1939TP_CB_CTS:
# if (J1939TP_CMDT_TX_ENABLED == STD_ON)
            {
              J1939Tp_TxSduTxNSduIdxOfTxChannelTxNSduType txSduIdx = 0u;

              if (J1939Tp_CmdtInternalRxIndication_FindActiveTxChannel(rxPduIdx, sa, da, &txSduIdx) == TRUE)
              {
                J1939Tp_CmdtInternalRxIndication_ReceiveTpCmCts(txSduIdx, info, pgn);
              }
            }
# endif
              break;

            case J1939TP_CB_EOMACK:
# if (J1939TP_CMDT_TX_ENABLED == STD_ON)
            {
              J1939Tp_TxSduTxNSduIdxOfTxChannelTxNSduType txSduIdx = 0u;

              if (J1939Tp_CmdtInternalRxIndication_FindActiveTxChannel(rxPduIdx, sa, da, &txSduIdx) == TRUE)
              {
                J1939Tp_CmdtInternalRxIndication_ReceiveTpCmEomack(txSduIdx, info, pgn);
              }
            }
# endif
              break;

            case J1939TP_CB_ABORT:
# if (J1939TP_RUNTIME_ERROR_REPORT == STD_ON)
            {
              boolean carValid;

#  if (J1939TP_ONISOBUSOFRXPDU == STD_ON)
              if (J1939Tp_IsOnIsobusOfRxPdu(rxPduIdx))
              {
                /* PRQA S 1881, 4304 1 */ /* MD_MSR_AutosarBoolean */
                carValid = (boolean) J1939Tp_CAR_ISO_Valid((uint8) (info->SduDataPtr[J1939TP_TPCM_CAR]));
              }
              else
#  endif
              {
                /* PRQA S 1881, 4304 1 */ /* MD_MSR_AutosarBoolean */
                carValid = (boolean) J1939Tp_CAR_Valid((uint8) (info->SduDataPtr[J1939TP_TPCM_CAR]));
              }

              if (carValid == FALSE)
              {
                J1939Tp_ReportRuntimeError(J1939TP_SID_RXINDICATION, J1939TP_E_INVALID_CAR);
              }
            }
# endif

# if (J1939TP_CMDT_RX_ENABLED == STD_ON)
            {
              J1939Tp_RxSduRxNSduIdxOfRxChannelRxNSduType rxSduIdx = 0u;

              if (J1939Tp_CmdtInternalRxIndication_FindActiveRxChannel(rxPduIdx, sa, da, &rxSduIdx) == TRUE)
              {
                /*! \trace SPEC-2167344 */
                J1939Tp_CmdtInternalRxIndication_ReceiveTpAbortRx(rxSduIdx, pgn);
              }
            }
# endif

# if (J1939TP_CMDT_TX_ENABLED == STD_ON)
            {
              J1939Tp_TxSduTxNSduIdxOfTxChannelTxNSduType txSduIdx = 0u;

              if (J1939Tp_CmdtInternalRxIndication_FindActiveTxChannel(rxPduIdx, sa, da, &txSduIdx) == TRUE)
              {
                /*! \trace SPEC-2167343 */
                J1939Tp_CmdtInternalRxIndication_ReceiveTpAbortTx(txSduIdx, pgn);
              }
            }
# endif
              /* Report J1939TP_E_IGNORED_ABORT also if the abort refers to a configured but inactive connection */
              break;

            default: /* PRQA S 2016 */ /* MD_MSR_EmptyClause */
              J1939Tp_ReportRuntimeError(J1939TP_SID_RXINDICATION, J1939TP_E_INVALID_CONTROL_BYTE);
              break;
            }
          }
        }
# if (J1939TP_CMDT_RX_ENABLED == STD_ON)
        else /* rxPduType == J1939TP_TPDT_PDUTYPEOFRXPDU */
        {
          J1939Tp_RxSduRxNSduIdxOfRxChannelRxNSduType rxSduIdx = 0u;

          if (J1939Tp_CmdtInternalRxIndication_FindActiveRxChannel(rxPduIdx, sa, da, &rxSduIdx) == TRUE)
          {
            J1939Tp_CmdtInternalRxIndication_ReceiveTpDt(rxSduIdx, info);
          }
        }
# endif
      }
    }
  }
# if ((J1939TP_CANIF_DLCCHECK == STD_OFF) && (J1939TP_RUNTIME_ERROR_REPORT == STD_ON))
  /* Otherwise, */
  else
  {
    /* Report the runtime error J1939TP_E_INVALID_DLC. */
    J1939Tp_ReportRuntimeError(J1939TP_SID_RXINDICATION, J1939TP_E_INVALID_DLC);
  }
# endif
} /* J1939Tp_CmdtRxIndication */ /* PRQA S 6030, 6050, 6080 */ /* MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */


# define J1939TP_STOP_SEC_CODE
/*lint -save -esym(961, 19.1) */
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*lint -restore */
/*============================================== J1939TP_STOP_SEC_CODE ==============================================*/
#endif


/* COV_JUSTIFICATION_BEGIN

\ID COV_J1939TP_CMDT_SWITCHCASE_DEFAULT
  \ACCEPT X
  \REASON Switch case has a default part for MISRA checks which is not reachable.

\ID COV_J1939TP_VERSION
  \ACCEPT XF xf xf xf
  \REASON [COV_MSR_CONFIG]

\ID COV_J1939TP_GNU
  \ACCEPT XF xf
  \ACCEPT XX xx
  \REASON [COV_MSR_UNSUPPORTED]

COV_JUSTIFICATION_END */
