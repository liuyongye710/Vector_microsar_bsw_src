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
 *         File:  J1939Tp_Direct.c
 *       Module:  J1939 Transport Layer
 *
 *  Description:  Implementation of the direct sub-module of the SAE J1939 Transport Layer module.
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

/* *INDENT-ON* */


/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

#define J1939TP_DIRECT_C

#include "J1939Tp_Cfg.h"

#if (J1939TP_DIRECT_ENABLED == STD_ON)
# include "J1939Tp.h"
# include "J1939Tp_Int.h"
# include "J1939Tp_Direct.h"

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
#  error "Vendor specific version numbers of J1939Tp_Direct.c and J1939Tp.h are inconsistent"
# endif


/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/*============================================== J1939TP_START_SEC_CODE =============================================*/
# define J1939TP_START_SEC_CODE
/*lint -save -esym(961, 19.1) */
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*lint -restore */

# if (J1939TP_DIRECT_TX_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  J1939Tp_DirectInternalTransmitTpDirect()
 *********************************************************************************************************************/
/*! \brief       This function transmits a direct frame
 *  \details     This function transmits a direct frame.
 *  \param[in]   txSduIdx               ID of the SDU to be transmitted
 *  \pre         -
 *  \context     TASK|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \config      J1939TP_DIRECT_TX_ENABLED
 *  \trace       CREQ-107402, CREQ-107397
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
J1939TP_LOCAL_INLINE void J1939Tp_DirectInternalTransmitTpDirect(PduIdType txSduIdx);
# endif

# if (J1939TP_DIRECT_RX_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  J1939Tp_DirectInternalRxIndication_AllocateRxChannel()
 *********************************************************************************************************************/
/*! \brief       Allocates a new connection
 *  \details     This function searches for a free connection for the incoming PDU
 *  \param[in]   rxPduIdx             ID of the incoming PDU
 *  \param[in]   sa                   Source address
 *  \param[in]   da                   Destination address
 *  \param[out]  allocatedRxSduIdx    Pointer to found SDU
 *  \return      TRUE         A connection has been allocated
 *  \return      FALSE        There is no free connection available
 *  \pre         -
 *  \context     TASK|ISR2
 *  \reentrant   TRUE for different rxPduIdx
 *  \synchronous TRUE
 *  \config      J1939TP_BAM_RX_ENABLED
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
J1939Tp_DirectInternalRxIndication_AllocateRxChannel(PduIdType rxPduIdx, uint8 sa, uint8 da,
                                                     J1939Tp_RxSduRxSduIdxOfRxPduRxSduType * allocatedRxSduIdx);
# endif

# if (J1939TP_DIRECT_RX_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  J1939Tp_DirectInternalRxIndication_ReceiveTpDirect()
 *********************************************************************************************************************/
/*! \brief       Reception of a direct frame
 *  \details     This function gets the data of a direct frame.
 *  \param[in]   rxSduIdx           ID of the SDU
 *  \param[in]   info               Contains the length (SduLength) of the received PDU and a pointer to a buffer
 *                                  (SduDataPtr) containing the PDU and the MetaData related to this PDU.
 *  \param[in]   pduLen             Length of the PDU
 *  \param[in]   sa                 Source address
 *  \param[in]   da                 Destination address
 *  \pre         -
 *  \context     TASK|ISR2
 *  \reentrant   TRUE for different rxSduIdx
 *  \synchronous TRUE
 *  \config      J1939TP_DIRECT_RX_ENABLED
 *  \trace       CREQ-107401, CREQ-107397
 *********************************************************************************************************************/
J1939TP_LOCAL_INLINE void J1939Tp_DirectInternalRxIndication_ReceiveTpDirect(J1939Tp_RxSduRxSduIdxOfRxPduRxSduType
                                                                             rxSduIdx, P2CONST(PduInfoType, AUTOMATIC,
                                                                                             J1939TP_APPL_DATA) info,
                                                                             PduLengthType pduLen, uint8 sa, uint8 da);
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


# if (J1939TP_DIRECT_TX_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  J1939Tp_DirectInternalTransmitTpDirect()
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
 */
J1939TP_LOCAL_INLINE void J1939Tp_DirectInternalTransmitTpDirect(PduIdType txSduIdx)
{
  J1939Tp_SizeOfTxPduType pduIdx = J1939Tp_GetTxPduDirectNPduIdxOfTxSdu(txSduIdx); 
  J1939Tp_TxNPduStateType *txPduState = &J1939Tp_GetTxPduState(J1939Tp_GetTxPduStateIdxOfTxPdu(pduIdx));
  J1939Tp_TxNSduStateType *txSduState = &J1939Tp_GetTxSduState(J1939Tp_GetTxSduStateIdxOfTxSdu(txSduIdx));

  /* If the PDU is not in use. */
  SchM_Enter_J1939Tp_J1939TP_EXCLUSIVE_AREA_TXNPDULOCK();
  if (txPduState->Locked == FALSE)
  {
    /* Lock the PDU and set the initial confirmation timeout value. */
    txPduState->CurrentNSduType = J1939TP_NSDU_DIRECT; /* VCA_J1939TP_TXPDUSTATE_VIA_TXSDU_CSL03 */
    txPduState->CurrentNSduId = txSduIdx; /* VCA_J1939TP_TXPDUSTATE_VIA_TXSDU_CSL03 */
    txPduState->ConfTimeout = J1939Tp_GetTxConfTimeout(); /* VCA_J1939TP_TXPDUSTATE_VIA_TXSDU_CSL03 */
    /* protected against concurrent access to the same direct N-PDU */
    txPduState->Locked = TRUE; /* VCA_J1939TP_TXPDUSTATE_VIA_TXSDU_CSL03 */
    SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_TXNPDULOCK();

    {
      uint8 data[J1939TP_NPDU_LENGTH];
      PduInfoType pdu;
      BufReq_ReturnType tpResult;

      /* Prepare the PDU */
      pdu.SduDataPtr = data;
      pdu.SduLength = (PduLengthType) txSduState->Size;

      /* Request the payload data from the upper layer. */
      /*! \trace SPEC-2167315, SPEC-2167317 */
      tpResult = PduR_J1939TpCopyTxData(J1939Tp_GetSduIdOfTxSdu(txSduIdx), &pdu, NULL_PTR, &txSduState->DataSize); /* VCA_J1939TP_FCTCALL_PTR2LOCAL */ /* VCA_J1939TP_TXSDUSTATE_VIA_TXSDU_CSL03 */

      /* If the request was successful, */
      if (tpResult == BUFREQ_OK)
      {
        /* Fill in the payload data */
        Std_ReturnType result;
        uint8 pos;
        uint32 pgn = (uint32) J1939Tp_GetPGNOfTxSdu(txSduIdx); 

        /* For all unused payload bytes, */
        for (pos = (uint8) txSduState->Size; pos < J1939TP_FRAME_LENGTH; pos++)
        {
          /* Set the invalid value. */
          data[pos] = J1939TP_SNA_VALUE; /*!< \trace SPEC-2167353 */
        }

        /* Fill in the MetaData. */
        data[J1939TP_NPDU_SA_POS] = txSduState->Sender;

        if (J1939Tp_GetPduFormatOfTxSdu(txSduIdx) == J1939TP_PDU1_PDUFORMATOFTXSDU)
        {
          data[J1939TP_NPDU_DA_POS] = txSduState->Receiver;
        }
        else
        {
          data[J1939TP_NPDU_GE_POS] = (uint8) J1939Tp_PGN_GetPDUS(pgn);
        }

        data[J1939TP_NPDU_PDUF_POS] = J1939Tp_PGN_GetPDUF(pgn);
        /* PRQA S 2986 1 */ /* MD_J1939Tp_2.2 */
        data[J1939TP_NPDU_DP_POS] = J1939Tp_PGN_GetDP(pgn) | txSduState->Priority;

        pdu.SduLength = J1939TP_NPDU_LENGTH; /*!< \trace SPEC-2167352 */

        /* Request the transmission of the data frame from the lower layer. */
        /* no protection required - all exits from pending and busy state are in the scope of the calling functions */
        txSduState->State = J1939TP_STATE_DIRECT_CONF;  /* VCA_J1939TP_TXSDUSTATE_VIA_TXSDU_CSL03 */
        result = CanIf_Transmit(J1939Tp_GetPduIdOfTxPdu(pduIdx), &pdu); /* VCA_J1939TP_FCTCALL_PTR2LOCAL */

        /* If the request was not successful. */
        if (result != E_OK)
        {
          SchM_Enter_J1939Tp_J1939TP_EXCLUSIVE_AREA_TXNSDULOCK();

          /* Set the state back to data frame. */
          if (txSduState->State == J1939TP_STATE_DIRECT_CONF)
          {
            /* no protection required - no further actions related to the locked state */
            txPduState->Locked = FALSE;  /* VCA_J1939TP_TXPDUSTATE_VIA_TXSDU_CSL03 */

            /* protected against late Tx confirmation */
            txSduState->State = J1939TP_STATE_DIRECT; /* VCA_J1939TP_TXSDUSTATE_VIA_TXSDU_CSL03 */

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
        txPduState->Locked = FALSE;  /* VCA_J1939TP_TXPDUSTATE_VIA_TXSDU_CSL03 */

        /* If the upper layer request is busy */
        if (tpResult == BUFREQ_E_BUSY)
        {
          /* Then set the state back to data frame. */
          /*! \trace SPEC-2167316 */
          /* no protection required - all exits from pending and busy state are in the scope of the calling functions */
          txSduState->State = J1939TP_STATE_DIRECT;  /* VCA_J1939TP_TXSDUSTATE_VIA_TXSDU_CSL03 */
        }
        /* For all other reasons */
        else
        {
          /* Inform the PduR about the missed confirmation and set the state to idle. */
          /*! \trace SPEC-2167320 */
          /* no protection required - all exits from pending and busy state are in the scope of the calling functions */
          txSduState->State = J1939TP_STATE_FINISH;  /* VCA_J1939TP_TXSDUSTATE_VIA_TXSDU_CSL03 */

          /*! \trace SPEC-2167303 */
          PduR_J1939TpTxConfirmation(J1939Tp_GetSduIdOfTxSdu(txSduIdx), E_NOT_OK); 

          /* no protection required - transition from uninterruptible state */
          txSduState->State = J1939TP_STATE_IDLE;  /* VCA_J1939TP_TXSDUSTATE_VIA_TXSDU_CSL03 */
        }
      }
    }
  }
  else
  {
    SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_TXNPDULOCK();

    /* Set the state back to DIRECT. */
    /* no protection required - all exits from busy state are in the scope of the calling functions */
    txSduState->State = J1939TP_STATE_DIRECT;  /* VCA_J1939TP_TXSDUSTATE_VIA_TXSDU_CSL03 */
  }
} /* J1939Tp_InternalTransmitTpDirect */
# endif


# if (J1939TP_DIRECT_RX_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  J1939Tp_DirectInternalRxIndication_AllocateRxChannel()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
J1939TP_LOCAL_INLINE boolean J1939Tp_DirectInternalRxIndication_AllocateRxChannel(PduIdType rxPduIdx,
                                                     uint8 sa,
                                                     uint8 da,
                                                     J1939Tp_RxSduRxSduIdxOfRxPduRxSduType * allocatedRxSduIdx)
{
  J1939Tp_RxPduRxSduRxSduTableIndEndIdxOfRxPduType pduSduIdx;
  boolean allocated = FALSE;

  for (pduSduIdx = J1939Tp_GetRxPduRxSduRxSduTableIndStartIdxOfRxPdu(rxPduIdx);
       pduSduIdx < J1939Tp_GetRxPduRxSduRxSduTableIndEndIdxOfRxPdu(rxPduIdx); pduSduIdx++)
  {
    J1939Tp_RxSduRxSduIdxOfRxPduRxSduType rxSduIdx = J1939Tp_GetRxSduRxSduIdxOfRxPduRxSdu(pduSduIdx);
    J1939Tp_RxChannelChannelIdxOfRxSduType rxChannelIdx = J1939Tp_GetRxChannelChannelIdxOfRxSdu(rxSduIdx);

    /*! \trace SPEC-2167348 */
    uint8 configuredSa = J1939Tp_GetRxSaOfRxChannel(rxChannelIdx);
    if ((configuredSa == J1939TP_NO_ADDRESS_CONFIGURED) || (configuredSa == sa))
    {
      /*! \trace SPEC-2167348 */
      uint8 configuredDa = J1939Tp_GetRxDaOfRxChannel(rxChannelIdx);
      /* Check whether the following tests cannot be removed, because DA was already set to broadcast for PDU2 */
      if ((J1939Tp_GetPduFormatOfRxPdu(rxPduIdx) == J1939TP_PDU2_PDUFORMATOFRXPDU) || (
#   if (J1939TP_EXISTS_PROTOCOL_CMDT_RXPROTOCOLTYPEOFRXCHANNEL == STD_ON)
          (J1939Tp_GetRxProtocolTypeOfRxChannel(rxChannelIdx) != J1939TP_PROTOCOL_CMDT_RXPROTOCOLTYPEOFRXCHANNEL) &&
#   endif
#   if (J1939TP_EXISTS_PROTOCOL_ETP_RXPROTOCOLTYPEOFRXCHANNEL == STD_ON)
           (J1939Tp_GetRxProtocolTypeOfRxChannel(rxChannelIdx) != J1939TP_PROTOCOL_ETP_RXPROTOCOLTYPEOFRXCHANNEL) &&
#   endif
           (da == J1939TP_BROADCAST_ADDRESS)) || (
#   if (J1939TP_EXISTS_PROTOCOL_BAM_RXPROTOCOLTYPEOFRXCHANNEL == STD_ON)
          (J1939Tp_GetRxProtocolTypeOfRxChannel(rxChannelIdx) != J1939TP_PROTOCOL_BAM_RXPROTOCOLTYPEOFRXCHANNEL) &&
#   endif
           ((configuredDa == J1939TP_NO_ADDRESS_CONFIGURED) || (configuredDa == da))))
      {
        J1939Tp_RxNSduStateType *rxSduState = &J1939Tp_GetRxSduState(J1939Tp_GetRxSduStateIdxOfRxSdu(rxSduIdx));

        SchM_Enter_J1939Tp_J1939TP_EXCLUSIVE_AREA_RXNSDULOCK();
        if (rxSduState->State == J1939TP_STATE_IDLE)
        {
          /* protected against concurrent reception of the same direct N-PDU */ /* Check if this is necessary */
          rxSduState->State = J1939TP_STATE_DIRECT_BUSY; /* VCA_J1939TP_RXSDUSTATE_VIA_RXPDU_CSL03 */
          SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_RXNSDULOCK();

          allocated = TRUE;
          *allocatedRxSduIdx = rxSduIdx;

          break; /* stop search for free N-SDU */
        }
        else
        {
          SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_RXNSDULOCK();
        }
      }
    }
  }

#  if (J1939TP_RUNTIME_ERROR_REPORT == STD_ON)
  if (allocated == FALSE)
  {
    /* No free connection found for incoming direct frame */

    J1939Tp_ReportRuntimeError(J1939TP_SID_RXINDICATION, J1939TP_E_NO_CONNECTION);
  }
#  else
  J1939TP_DUMMY_STATEMENT(allocated); /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
#  endif

  return allocated;
}
# endif


# if (J1939TP_DIRECT_RX_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  J1939Tp_DirectInternalRxIndication_ReceiveTpDirect()
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
J1939TP_LOCAL_INLINE void J1939Tp_DirectInternalRxIndication_ReceiveTpDirect(J1939Tp_RxSduRxSduIdxOfRxPduRxSduType rxSduIdx,
                                                                    P2CONST(PduInfoType, AUTOMATIC, J1939TP_APPL_DATA) info,
                                                                    PduLengthType pduLen,
                                                                    uint8 sa,
                                                                    uint8 da)
{
  uint8 metaData[J1939TP_MDL_SIZE];
  BufReq_ReturnType tpResult;
  PduInfoType addrInfo;
  PduLengthType bufSize;

  addrInfo.SduLength = J1939Tp_GetMetaDataLengthOfRxSdu(rxSduIdx);
  addrInfo.SduDataPtr = metaData;

  metaData[J1939TP_MDL_SA_POS] = sa;
  metaData[J1939TP_MDL_DA_POS] = da;
  metaData[J1939TP_MDL_PDUF_POS] = J1939TP_SNA_VALUE;
  metaData[J1939TP_MDL_PRI_POS] = J1939Tp_MDL_Get_PRI(info->SduDataPtr[pduLen + J1939TP_MDL_PRI_POS]);

  tpResult = PduR_J1939TpStartOfReception(J1939Tp_GetSduIdOfRxSdu(rxSduIdx), &addrInfo, pduLen, &bufSize); /* VCA_J1939TP_FCTCALL_PTR2LOCAL */
  if (tpResult == BUFREQ_OK)
  {
    Std_ReturnType result = E_NOT_OK;

    if (bufSize >= pduLen)
    {
      PduInfoType pdu;

      pdu.SduDataPtr = info->SduDataPtr;
      pdu.SduLength = pduLen;

      tpResult = PduR_J1939TpCopyRxData(J1939Tp_GetSduIdOfRxSdu(rxSduIdx), &pdu, &bufSize); /* VCA_J1939TP_FCTCALL_PTR2LOCAL */
      if (tpResult == BUFREQ_OK)
      {
        result = E_OK;
      }
    }

    PduR_J1939TpRxIndication(J1939Tp_GetSduIdOfRxSdu(rxSduIdx), result);
  }
}
# endif

# define J1939TP_STOP_SEC_CODE
/*lint -save -esym(961, 19.1) */
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*lint -restore */
/*============================================== J1939TP_STOP_SEC_CODE ==============================================*/


/**********************************************************************************************************************
 *  INTERNAL FUNCTIONS
 *********************************************************************************************************************/


# if (J1939TP_DIRECT_TX_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  J1939Tp_DirectTxMain()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
FUNC(void, J1939TP_CODE) J1939Tp_DirectTxMain(PduIdType txSduIdx)
{
  J1939Tp_TxNSduStateType *txSduState = &J1939Tp_GetTxSduState(J1939Tp_GetTxSduStateIdxOfTxSdu(txSduIdx));

  /* If the state is DIRECT */
  if (txSduState->State == J1939TP_STATE_DIRECT)
  {
    /* And if a timeout occurs */
    if (txSduState->TimeOut == 0u)
    {
      /* Then inform the PduR about the missed confirmation and set its state to idle. */
      /* no protection required - all exits from pending state are in the scope of this function */
      txSduState->State = J1939TP_STATE_FINISH; /* VCA_J1939TP_TXSDUSTATE_VIA_TXSDU_CSL03 */

      J1939Tp_ReportRuntimeError(J1939TP_SID_MAINFUNCTION, J1939TP_E_TIMEOUT_TR);

      /*! \trace SPEC-2167303 */
      PduR_J1939TpTxConfirmation(J1939Tp_GetSduIdOfTxSdu(txSduIdx), E_NOT_OK);

      /* no protection required - transition from uninterruptible state */
      txSduState->State = J1939TP_STATE_IDLE; /* VCA_J1939TP_TXSDUSTATE_VIA_TXSDU_CSL03 */
    }
    /* Otherwise */
    else
    {
      /* Decrement the timeout value by one and request the transmission of the direct frame. */
      --txSduState->TimeOut; /* VCA_J1939TP_TXSDUSTATE_VIA_TXSDU_CSL03 */

      /*! \trace SPEC-2167316 */
      J1939Tp_DirectInternalTransmitTpDirect(txSduIdx);
    }
  }
} /* J1939Tp_DirectTxMain */
# endif


# if (J1939TP_DIRECT_TX_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  J1939Tp_DirectTransmit()
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
FUNC(Std_ReturnType, J1939TP_CODE) J1939Tp_DirectTransmit(PduIdType txSduIdx,
                                                          P2CONST(PduInfoType, AUTOMATIC, J1939TP_APPL_DATA) info)
{
  J1939Tp_TxNSduStateType *txSduState = &J1939Tp_GetTxSduState(J1939Tp_GetTxSduStateIdxOfTxSdu(txSduIdx));
  Std_ReturnType result = E_NOT_OK;

  /* Proceed If the state is IDLE */
  SchM_Enter_J1939Tp_J1939TP_EXCLUSIVE_AREA_TXNSDULOCK();
  if (txSduState->State == J1939TP_STATE_IDLE)
  {
    /* Then set the state to DIRECT_BUSY. */
    /* protected against a reentrant call for the same N-SDU */ /* Check if this is necessary */
    txSduState->State = J1939TP_STATE_DIRECT_BUSY;
    SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_TXNSDULOCK();

    {
      J1939Tp_MetaDataLengthOfTxSduType mdl = J1939Tp_GetMetaDataLengthOfTxSdu(txSduIdx);
      J1939Tp_TxChannelChannelIdxOfTxSduType txChannelIdx = J1939Tp_GetTxChannelChannelIdxOfTxSdu(txSduIdx);
      uint8 pri, da, sa;

      /* Determine the priority, source and destination address */
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
      if ((J1939Tp_GetTxProtocolTypeOfTxChannel(txChannelIdx) == J1939TP_PROTOCOL_BAM_TXPROTOCOLTYPEOFTXCHANNEL) ||
          ((J1939Tp_GetTxProtocolTypeOfTxChannel(txChannelIdx) == J1939TP_PROTOCOL_UNUSED_TXPROTOCOLTYPEOFTXCHANNEL) &&
           (info->SduDataPtr[J1939TP_MDL_DA_POS] == J1939TP_BROADCAST_ADDRESS)))
      {
        da = J1939TP_BROADCAST_ADDRESS;
      }
      else if (J1939Tp_GetTxDaOfTxChannel(txChannelIdx) == J1939TP_NO_ADDRESS_CONFIGURED)
      {
        da = info->SduDataPtr[J1939TP_MDL_DA_POS];
      }
      else
      {
        da = J1939Tp_GetTxDaOfTxChannel(txChannelIdx);
      }

      if (mdl > J1939TP_MDL_PRI_POS)
      {
        pri = J1939Tp_MDL_Get_PRI(info->SduDataPtr[J1939TP_MDL_PRI_POS]);
      }
      else
      {
        pri = J1939Tp_GetTxPriOfTxChannel(txChannelIdx) << 2;
      }

      /* Prepares the data to be transmitted. */
      txSduState->Size = info->SduLength; /* VCA_J1939TP_TXSDUSTATE_VIA_TXSDU_CSL03 */
      txSduState->Sender = sa; /* VCA_J1939TP_TXSDUSTATE_VIA_TXSDU_CSL03 */
      txSduState->Receiver = da; /* VCA_J1939TP_TXSDUSTATE_VIA_TXSDU_CSL03 */
      txSduState->Priority = pri; /* VCA_J1939TP_TXSDUSTATE_VIA_TXSDU_CSL03 */
      txSduState->TimeOut = J1939Tp_GetTime_Tr(); /* VCA_J1939TP_TXSDUSTATE_VIA_TXSDU_CSL03 */

      /* Request the transmission of a direct frame. */
      J1939Tp_DirectInternalTransmitTpDirect(txSduIdx);

      /* Set the return value to successful. */
      result = E_OK;
    }
  }
  /* For all other states */
  else
  {
    SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_TXNSDULOCK();
  }

  /* Return the result of the function. */
  return result;
} /* J1939Tp_DirectTransmit */
# endif


# if (J1939TP_DIRECT_TX_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  J1939Tp_DirectTxConfirmation()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, J1939TP_CODE) J1939Tp_DirectTxConfirmation(PduIdType txSduIdx)
{
  J1939Tp_TxNSduStateType *txSduState = &J1939Tp_GetTxSduState(J1939Tp_GetTxSduStateIdxOfTxSdu(txSduIdx));

  SchM_Enter_J1939Tp_J1939TP_EXCLUSIVE_AREA_TXNSDULOCK();
  if (txSduState->State == J1939TP_STATE_DIRECT_CONF)
  {
    /* protected against concurrent transmission failure and early Tx confirmation timeout */
    txSduState->State = J1939TP_STATE_FINISH; /* VCA_J1939TP_TXSDUSTATE_VIA_TXSDU_CSL03 */
    SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_TXNSDULOCK();

    /*! \trace SPEC-2167302 */
    PduR_J1939TpTxConfirmation(J1939Tp_GetSduIdOfTxSdu(txSduIdx), E_OK); 

    txSduState->State = J1939TP_STATE_IDLE; /* VCA_J1939TP_TXSDUSTATE_VIA_TXSDU_CSL03 */
  }
  else
  {
    SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_TXNSDULOCK();
  }
} /* J1939Tp_DirectTxConfirmation */
# endif


# if (J1939TP_DIRECT_RX_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  J1939Tp_DirectRxIndication()
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
FUNC(void, J1939TP_CODE) J1939Tp_DirectRxIndication(PduIdType rxPduIdx,
                                                    P2CONST(PduInfoType, AUTOMATIC, J1939TP_APPL_DATA) info, uint8 sa)
{
  PduLengthType pduLen = info->SduLength - J1939TP_MDL_SIZE;
  uint8 da = info->SduDataPtr[pduLen + J1939TP_MDL_DA_POS];

  if (J1939Tp_GetPduFormatOfRxPdu(rxPduIdx) == J1939TP_PDU2_PDUFORMATOFRXPDU)
  {
    da = J1939TP_BROADCAST_ADDRESS;
  }

  if (!J1939Tp_DA_Valid(da))
  {
    /*! \trace SPEC-2167310 */
    J1939Tp_ReportRuntimeError(J1939TP_SID_RXINDICATION, J1939TP_E_INVALID_DA);
  }
  else
  {
    J1939Tp_RxSduRxSduIdxOfRxPduRxSduType rxSduIdx = 0u;

    if (J1939Tp_DirectInternalRxIndication_AllocateRxChannel(rxPduIdx, sa, da, &rxSduIdx) == TRUE)
    {
      J1939Tp_RxNSduStateType *rxSduState = &J1939Tp_GetRxSduState(J1939Tp_GetRxSduStateIdxOfRxSdu(rxSduIdx));

      J1939Tp_DirectInternalRxIndication_ReceiveTpDirect(rxSduIdx, info, pduLen, sa, da);

      /* no protection required - transition from uninterruptible state */
      rxSduState->State = J1939TP_STATE_IDLE;  /* VCA_J1939TP_RXSDUSTATE_VIA_RXPDU_CSL03 */
    }
  }
} /* J1939Tp_DirectRxIndication */
# endif


/*============================================== J1939TP_START_SEC_CODE =============================================*/
# define J1939TP_START_SEC_CODE
/*lint -save -esym(961, 19.1) */
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*lint -restore */


# define J1939TP_STOP_SEC_CODE
/*lint -save -esym(961, 19.1) */
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*lint -restore */
/*============================================== J1939TP_STOP_SEC_CODE ==============================================*/
#endif


/* COV_JUSTIFICATION_BEGIN

\ID COV_J1939TP_VERSION
  \ACCEPT XF xf xf xf
  \REASON [COV_MSR_CONFIG]

COV_JUSTIFICATION_END */

