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
 *         File:  J1939Tp_Bam.c
 *       Module:  J1939 Transport Layer
 *
 *  Description:  Implementation of the BAM sub-module of the SAE J1939 Transport Layer module.
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

#define J1939TP_BAM_C

#include "J1939Tp_Cfg.h"

#if (J1939TP_BAM_ENABLED == STD_ON)
# include "J1939Tp.h"
# include "J1939Tp_Int.h"
# include "J1939Tp_Bam.h"

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
#  error "Vendor specific version numbers of J1939Tp_Bam.c and J1939Tp.h are inconsistent"
# endif


/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/*============================================== J1939TP_START_SEC_CODE =============================================*/
# define J1939TP_START_SEC_CODE
/*lint -save -esym(961, 19.1) */
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*lint -restore */

# if (J1939TP_BAM_TX_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  J1939Tp_BamInternalTransmitTpCmBam()
 *********************************************************************************************************************/
/*! \brief       This function transmits a TP.CM frame
 *  \details     This function transmits a TP.CM frame of transport protocol BAM.
 *  \param[in]   txSduIdx               ID of the SDU to be transmitted
 *  \pre         -
 *  \context     TASK|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \config      J1939TP_BAM_TX_ENABLED
 *  \trace       CREQ-107402, CREQ-107398
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
J1939TP_LOCAL_INLINE void J1939Tp_BamInternalTransmitTpCmBam(PduIdType txSduIdx);
# endif

# if (J1939TP_BAM_TX_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  J1939Tp_BamInternalTransmitTpDt()
 *********************************************************************************************************************/
/*! \brief       This function transmits a TP.DT frame
 *  \details     This function transmits a TP.DT frame of transport protocol BAM.
 *  \param[in]   txSduIdx             ID of the SDU to be transmitted
 *  \pre         -
 *  \context     TASK|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \config      J1939TP_BAM_TX_ENABLED
 *  \trace       CREQ-107402, CREQ-107398
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
J1939TP_LOCAL_INLINE void J1939Tp_BamInternalTransmitTpDt(PduIdType txSduIdx);
# endif

# if (J1939TP_BAM_TX_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  J1939Tp_BamInternalTransmit_SearchConflictingTxChannel()
 *********************************************************************************************************************/
/*! \brief       Searches for an already established Tx connection
 *  \details     This function searches for a Tx connection that is already in use.
 *  \param[in]   txSduIdx             ID of the SDU to be transmitted
 *  \param[in]   txChannelIdx         ID of the given Tx channel
 *  \param[in]   sa                   Source address
 *  \return      TRUE         A connection is already established
 *  \return      FALSE        No conflicts found
 *  \pre         -
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      J1939TP_BAM_TX_ENABLED
 *********************************************************************************************************************/
J1939TP_LOCAL_INLINE boolean
J1939Tp_BamInternalTransmit_SearchConflictingTxChannel(PduIdType txSduIdx,
                                                       J1939Tp_TxChannelChannelIdxOfTxSduType txChannelIdx, uint8 sa);
# endif

# if (J1939TP_BAM_RX_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  J1939Tp_BamInternalRxIndication_AllocateRxChannel()
 *********************************************************************************************************************/
/*! \brief       Allocates a new connection
 *  \details     This function searches for a free connection for the incoming PDU
 *  \param[in]   rxPduIdx             ID of the incoming PDU
 *  \param[in]   sa                   Source address
 *  \param[in]   pgn                  Parameter group number
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
J1939Tp_BamInternalRxIndication_AllocateRxChannel(PduIdType rxPduIdx, uint8 sa, uint32 pgn,
                                                  J1939Tp_RxSduRxNSduIdxOfRxChannelRxNSduType * allocatedRxSduIdx);
# endif

# if (J1939TP_BAM_RX_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  J1939Tp_BamInternalRxIndication_ReceiveTpCmBam()
 *********************************************************************************************************************/
/*! \brief       Reception of a TP.CM frame
 *  \details     This function gets the data of a TP.CM frame of transport protocol BAM.
 *  \param[in]   rxSduIdx           ID of the SDU
 *  \param[in]   info               Contains the length (SduLength) of the received PDU and a pointer to a buffer
 *                                  (SduDataPtr) containing the PDU and the MetaData related to this PDU.
 *  \param[in]   sa                 Source address
 *  \param[in]   size               Total message size
 *  \pre         -
 *  \context     TASK|ISR2
 *  \reentrant   TRUE for different rxSduIdx
 *  \synchronous TRUE
 *  \config      J1939TP_BAM_RX_ENABLED
 *  \trace       CREQ-107401, CREQ-107398
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
J1939TP_LOCAL_INLINE void J1939Tp_BamInternalRxIndication_ReceiveTpCmBam(J1939Tp_RxSduRxNSduIdxOfRxChannelRxNSduType
                                                                         rxSduIdx, P2CONST(PduInfoType, AUTOMATIC,
                                                                                         J1939TP_APPL_DATA) info,
                                                                         uint8 sa, uint16 size);
# endif

# if (J1939TP_BAM_RX_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  J1939Tp_BamInternalRxIndication_FindActiveRxChannel()
 *********************************************************************************************************************/
/*! \brief       Finds active Rx connection
 *  \details     This function finds an active Rx connection for the given rxPduIdx and sa.
 *  \param[in]   rxPduIdx     ID of the incoming PDU
 *  \param[in]   sa           Source address
 *  \param[out]  rxSduIdx     Pointer to found SDU
 *  \return      TRUE         An active connection has been found
 *  \return      FALSE        No active connection
 *  \pre         -
 *  \context     TASK|ISR2
 *  \reentrant   TRUE for different rxPduIdx
 *  \synchronous TRUE
 *  \config      J1939TP_BAM_RX_ENABLED
 *********************************************************************************************************************/
J1939TP_LOCAL_INLINE boolean
J1939Tp_BamInternalRxIndication_FindActiveRxChannel(PduIdType rxPduIdx, uint8 sa,
                                                    J1939Tp_RxSduRxNSduIdxOfRxChannelRxNSduType * rxSduIdx);
# endif

# if (J1939TP_BAM_RX_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  J1939Tp_BamInternalRxIndication_ReceiveTpDt()
 *********************************************************************************************************************/
/*! \brief       Reception of a TP.DT frame
 *  \details     This function gets the data of a TP.DT frame of transport protocol BAM.
 *  \param[in]   rxSduIdx           ID of the SDU
 *  \param[in]   info               Contains the length (SduLength) of the received PDU and a pointer to a buffer
 *                                  (SduDataPtr) containing the PDU and the MetaData related to this PDU.
 *  \pre         -
 *  \context     TASK|ISR2
 *  \reentrant   TRUE for different rxSduIdx
 *  \synchronous TRUE
 *  \config      J1939TP_BAM_RX_ENABLED
 *  \trace       CREQ-107401, CREQ-107398
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
J1939TP_LOCAL_INLINE void J1939Tp_BamInternalRxIndication_ReceiveTpDt(J1939Tp_RxSduRxNSduIdxOfRxChannelRxNSduType
                                                                      rxSduIdx, P2CONST(PduInfoType, AUTOMATIC,
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


# if (J1939TP_BAM_TX_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  J1939Tp_BamInternalTransmitTpCmBam()
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
J1939TP_LOCAL_INLINE void J1939Tp_BamInternalTransmitTpCmBam(PduIdType txSduIdx)
{
  J1939Tp_TxChannelChannelIdxOfTxSduType txChannelIdx = J1939Tp_GetTxChannelChannelIdxOfTxSdu(txSduIdx);
  J1939Tp_SizeOfTxPduType txPduIdx = J1939Tp_GetTxPduTxCmNPduIdxOfTxChannel(txChannelIdx);
  J1939Tp_TxNPduStateType *txPduState = &J1939Tp_GetTxPduState(J1939Tp_GetTxPduStateIdxOfTxPdu(txPduIdx));

  SchM_Enter_J1939Tp_J1939TP_EXCLUSIVE_AREA_TXNPDULOCK();
  if (txPduState->Locked == FALSE)
  {
    /* Lock the PDU and set the initial confirmation timeout value. */
    txPduState->CurrentNSduType = J1939TP_NSDU_BAM; /* VCA_J1939TP_TXPDUSTATE_VIA_TXSDU_CSL03 */
    txPduState->CurrentNSduId = txSduIdx; /* VCA_J1939TP_TXPDUSTATE_VIA_TXSDU_CSL03 */
    txPduState->ConfTimeout = J1939Tp_GetTxConfTimeout(); /* VCA_J1939TP_TXPDUSTATE_VIA_TXSDU_CSL03 */
    /* protected against concurrent access to the same TP.CM N-PDU */
    txPduState->Locked = TRUE; /* VCA_J1939TP_TXPDUSTATE_VIA_TXSDU_CSL03 */
    SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_TXNPDULOCK();

    {
      /* Fill in the payload data of the Connection Management frame. */
      J1939Tp_TxNSduStateType *txSduState = &J1939Tp_GetTxSduState(J1939Tp_GetTxSduStateIdxOfTxSdu(txSduIdx));
      uint32 pgn = (uint32) J1939Tp_GetPGNOfTxSdu(txSduIdx);
      uint8 data[J1939TP_NPDU_LENGTH];
      PduInfoType pdu;
      Std_ReturnType result;

      data[J1939TP_TPCM_CB] = (uint8) J1939TP_CB_BAM;
      data[J1939TP_TPCM_TMS_LO] = J1939Tp_Make_TMS_LO(txSduState->Size);
      data[J1939TP_TPCM_TMS_HI] = J1939Tp_Make_TMS_HI(txSduState->Size);
      data[J1939TP_TPCM_TNOP] = (uint8) txSduState->Packets;
      data[J1939TP_TPCM_RES5] = J1939TP_SNA_VALUE;
      data[J1939TP_TPCM_PGN_LO] = J1939Tp_Make_PGN_LO(pgn);
      data[J1939TP_TPCM_PGN_MD] = J1939Tp_Make_PGN_MD(pgn);
      data[J1939TP_TPCM_PGN_HI] = J1939Tp_Make_PGN_HI(pgn);
      data[J1939TP_NPDU_SA_POS] = txSduState->Sender;
      data[J1939TP_NPDU_DA_POS] = J1939TP_BROADCAST_ADDRESS;
      data[J1939TP_NPDU_PRI_POS] = txSduState->Priority;

      pdu.SduDataPtr = data;
      pdu.SduLength = J1939TP_NPDU_LENGTH;

      /* no protection required - all exits from BAM state are in the scope of the Tx main function */
      txSduState->State = J1939TP_STATE_BAM_BAM_CONF; /* VCA_J1939TP_TXSDUSTATE_VIA_TXSDU_CSL03 */
      /* Request the transmission of the Connection Management frame from the lower layer. */
      result = CanIf_Transmit(J1939Tp_GetPduIdOfTxPdu(txPduIdx), &pdu); /* VCA_J1939TP_FCTCALL_PTR2LOCAL */

      /* If the request was not successful. */
      if (result != E_OK)
      {
        SchM_Enter_J1939Tp_J1939TP_EXCLUSIVE_AREA_TXNSDULOCK();

        /* Set the state back to Bam CM frame. */
        if (txSduState->State == J1939TP_STATE_BAM_BAM_CONF)
        {
          /* no protection required - no further actions related to the locked state */
          txPduState->Locked = FALSE; /* VCA_J1939TP_TXSDUSTATE_VIA_TXSDU_CSL03 */

          /* protected against late Tx confirmation */
          txSduState->State = J1939TP_STATE_BAM_BAM; /* VCA_J1939TP_TXSDUSTATE_VIA_TXSDU_CSL03 */

          SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_TXNSDULOCK();
        }
        else
        {
          SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_TXNSDULOCK();
        }
      }
    }
  }
  else
  {
    SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_TXNPDULOCK();
  }
} /* J1939Tp_BamInternalTransmitTpCmBam */
# endif


# if (J1939TP_BAM_TX_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  J1939Tp_BamInternalTransmitTpDt()
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
J1939TP_LOCAL_INLINE void J1939Tp_BamInternalTransmitTpDt(PduIdType txSduIdx)
{
  J1939Tp_TxChannelChannelIdxOfTxSduType txChannelIdx = J1939Tp_GetTxChannelChannelIdxOfTxSdu(txSduIdx);
  J1939Tp_SizeOfTxPduType txPduIdx = J1939Tp_GetTxPduTxDtNPduIdxOfTxChannel(txChannelIdx);
  J1939Tp_TxNPduStateType *txPduState = &J1939Tp_GetTxPduState(J1939Tp_GetTxPduStateIdxOfTxPdu(txPduIdx));

  /* If the PDU is not in use. */
  SchM_Enter_J1939Tp_J1939TP_EXCLUSIVE_AREA_TXNPDULOCK();
  if (txPduState->Locked == FALSE)
  {
    /* Lock the PDU and set the initial confirmation timeout value. */
    txPduState->CurrentNSduType = J1939TP_NSDU_BAM; /* VCA_J1939TP_TXPDUSTATE_VIA_TXSDU_CSL03 */
    txPduState->CurrentNSduId = txSduIdx; /* VCA_J1939TP_TXPDUSTATE_VIA_TXSDU_CSL03 */
    txPduState->ConfTimeout = J1939Tp_GetTxConfTimeout(); /* VCA_J1939TP_TXPDUSTATE_VIA_TXSDU_CSL03 */
    /* protected against concurrent access to the same TP.DT N-PDU */
    txPduState->Locked = TRUE; /* VCA_J1939TP_TXPDUSTATE_VIA_TXSDU_CSL03 */
    SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_TXNPDULOCK();

    {
      J1939Tp_TxNSduStateType *txSduState = &J1939Tp_GetTxSduState(J1939Tp_GetTxSduStateIdxOfTxSdu(txSduIdx));
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

      /* Request the payload data from the upper layer. */
      /*! \trace SPEC-2167315, SPEC-2167318 */
      tpResult = PduR_J1939TpCopyTxData(J1939Tp_GetSduIdOfTxSdu(txSduIdx), &pdu, NULL_PTR, &txSduState->DataSize); /* VCA_J1939TP_FCTCALL_PTR2LOCAL */

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
        data[J1939TP_NPDU_DA_POS] = J1939TP_BROADCAST_ADDRESS;
        data[J1939TP_NPDU_PRI_POS] = txSduState->Priority;

        pdu.SduDataPtr = data;
        pdu.SduLength = J1939TP_NPDU_LENGTH; /*!< \trace SPEC-2167352 */

        /* Request the transmission of the data frame from the lower layer. */
        /* no protection required - all exits from data state are in the scope of the Tx main function */
        txSduState->State = J1939TP_STATE_BAM_DATA_CONF; /* VCA_J1939TP_TXSDUSTATE_VIA_TXSDU_CSL03 */
        result = CanIf_Transmit(J1939Tp_GetPduIdOfTxPdu(txPduIdx), &pdu); /* VCA_J1939TP_FCTCALL_PTR2LOCAL */

        /* If the request was not successful. */
        if (result != E_OK)
        {
          SchM_Enter_J1939Tp_J1939TP_EXCLUSIVE_AREA_TXNSDULOCK();

          /* Set the state back to data frame. */
          if (txSduState->State == J1939TP_STATE_BAM_DATA_CONF)
          {
            /* no protection required - no further actions related to the locked state */
            txPduState->Locked = FALSE; /* VCA_J1939TP_TXPDUSTATE_VIA_TXSDU_CSL03 */

            /* protected against late Tx confirmation */
            txSduState->State = J1939TP_STATE_BAM_DATA; /* VCA_J1939TP_TXSDUSTATE_VIA_TXSDU_CSL03 */

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
        /*! \trace SPEC-2167316 */
        /* no protection required - no further actions related to the locked state */
        txPduState->Locked = FALSE; /* VCA_J1939TP_TXPDUSTATE_VIA_TXSDU_CSL03 */

        /* If the upper layer request is not busy */
        if (tpResult != BUFREQ_E_BUSY)
        {
          /* Then inform the PduR about the missed confirmation and set the state to idle. */
          /*! \trace SPEC-2167320 */
          /* no protection required - all exits from data state are in the scope of the Tx main function */
          txSduState->State = J1939TP_STATE_FINISH; /* VCA_J1939TP_TXSDUSTATE_VIA_TXSDU_CSL03 */

          /*! \trace SPEC-2167303 */
          PduR_J1939TpTxConfirmation(J1939Tp_GetSduIdOfTxSdu(txSduIdx), E_NOT_OK);

          /* no protection required - transition from uninterruptible state */
          txSduState->State = J1939TP_STATE_IDLE; /* VCA_J1939TP_TXSDUSTATE_VIA_TXSDU_CSL03 */
        }
      }
    }
  }
  else
  {
    SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_TXNPDULOCK();
  }
} /* J1939Tp_BamInternalTransmitTpDt */
# endif


# if (J1939TP_BAM_TX_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  J1939Tp_BamInternalTransmit_SearchConflictingTxChannel()
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
J1939TP_LOCAL_INLINE boolean J1939Tp_BamInternalTransmit_SearchConflictingTxChannel(PduIdType txSduIdx,
                                                       J1939Tp_TxChannelChannelIdxOfTxSduType txChannelIdx,
                                                       uint8 sa)
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
      J1939Tp_TxChannelTxNSduTxNSduTableIndEndIdxOfTxChannelType sduIndIdx;

      /* Iterate over all SDUs on that channel */
      for (sduIndIdx = J1939Tp_GetTxChannelTxNSduTxNSduTableIndStartIdxOfTxChannel(otherTxChannelIdx);
           sduIndIdx < J1939Tp_GetTxChannelTxNSduTxNSduTableIndEndIdxOfTxChannel(otherTxChannelIdx); sduIndIdx++)
      {
        J1939Tp_TxChannelTxNSduTxNSduTableIndType otherSduIdx =
          J1939Tp_GetTxSduTxNSduIdxOfTxChannelTxNSdu(J1939Tp_GetTxChannelTxNSduTxNSduTableInd(sduIndIdx)); 

        /* If the SDU index is different */
        if (otherSduIdx != txSduIdx)
        {
          const J1939Tp_TxNSduStateType *otherTxSduState =
            &J1939Tp_GetTxSduState(J1939Tp_GetTxSduStateIdxOfTxSdu(otherSduIdx));

          /* And if the state is not IDLE and the Sender matches with the source address. */
          if (((otherTxSduState->State & J1939TP_STATEMASK_BAM) != J1939TP_STATE_IDLE) &&
              (otherTxSduState->Sender == sa))
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


# if (J1939TP_BAM_RX_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  J1939Tp_BamInternalRxIndication_AllocateRxChannel()
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
 */
J1939TP_LOCAL_INLINE boolean J1939Tp_BamInternalRxIndication_AllocateRxChannel(PduIdType rxPduIdx,
                                                  uint8 sa,
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
    J1939Tp_RxChannelRxChannelIdxOfRxPduRxChannelType rxChannelIdx = J1939Tp_GetRxChannelRxChannelIdxOfRxPduRxChannel(rxPduRxChannelIdx);

#  if (J1939TP_CMDT_RX_ENABLED == STD_ON)
    /* If the protocol type is not CMDT. */
    if (J1939Tp_GetRxProtocolTypeOfRxChannel(rxChannelIdx) != J1939TP_PROTOCOL_CMDT_RXPROTOCOLTYPEOFRXCHANNEL)
#  endif
    {
      /* If a source address is configured for an Rx connection. */
      /*! \trace SPEC-2167348 */
      uint8 configuredSa = J1939Tp_GetRxSaOfRxChannel(rxChannelIdx);

      /* Verify that either the configured source address is undefined or is the given source address sa. */
      if ((configuredSa == J1939TP_NO_ADDRESS_CONFIGURED) || (configuredSa == sa))
      {
        J1939Tp_RxChannelRxNSduRxNSduTableIndEndIdxOfRxChannelType rxChannelSduIdx;

        /* Iterate over all Rx channels and their N-SDUs */
        for (rxChannelSduIdx = J1939Tp_GetRxChannelRxNSduRxNSduTableIndStartIdxOfRxChannel(rxChannelIdx);
             rxChannelSduIdx < J1939Tp_GetRxChannelRxNSduRxNSduTableIndEndIdxOfRxChannel(rxChannelIdx);
             rxChannelSduIdx++)
        {
          J1939Tp_RxSduRxNSduIdxOfRxChannelRxNSduType rxSduIdx =
            J1939Tp_GetRxSduRxNSduIdxOfRxChannelRxNSdu(rxChannelSduIdx); 
          J1939Tp_RxNSduStateType *rxSduState = &J1939Tp_GetRxSduState(J1939Tp_GetRxSduStateIdxOfRxSdu(rxSduIdx));

          /* If the found Rx connection's state is active and the Sender is equal to the given source address. */
          if (((rxSduState->State & J1939TP_STATEMASK_BAM) != J1939TP_STATE_IDLE) && (rxSduState->Sender == sa))
          {
            J1939Tp_ReportRuntimeError(J1939TP_SID_RXINDICATION, J1939TP_E_UNTIMELY_BAM);

            /* If the Rx connection's state is DATA */
            SchM_Enter_J1939Tp_J1939TP_EXCLUSIVE_AREA_RXNSDULOCK();
            if (rxSduState->State == J1939TP_STATE_BAM_DATA)
            {
              /* Then inform the PduR about the missed indication and set its state to idle. */
              /* protected against concurrent timeout and concurrect reception of TP.DT message */
              rxSduState->State = J1939TP_STATE_FINISH; /* VCA_J1939TP_RXSDUSTATE_VIA_RXPDU_CSL03 */
              SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_RXNSDULOCK();

              /*! \trace SPEC-2167305 */
              PduR_J1939TpRxIndication(J1939Tp_GetSduIdOfRxSdu(rxSduIdx), E_NOT_OK);

              /* no protection required - transition from uninterruptible state */
              rxSduState->State = J1939TP_STATE_IDLE; /* VCA_J1939TP_RXSDUSTATE_VIA_RXPDU_CSL03 */
            }
            /* For all other states. */
            else
            {
              SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_RXNSDULOCK();

              /* Set the aborted flag to true. */
              rxSduState->Aborted = TRUE; /* VCA_J1939TP_RXSDUSTATE_VIA_RXPDU_CSL03 */
            }
          }

          /* If no connection has been allocated so far and the PGN is equal to the configured one. */
          /*! \trace SPEC-2167293, SPEC-2167348 */
          if ((allocated == FALSE) && (pgn == (uint32) J1939Tp_GetPGNOfRxSdu(rxSduIdx)))
          {
            /* A new connection has been found. */
            found = TRUE;

            /* If the state is IDLE */
            SchM_Enter_J1939Tp_J1939TP_EXCLUSIVE_AREA_RXNSDULOCK();
            if (rxSduState->State == J1939TP_STATE_IDLE)
            {
              /* Set aborted flag to false. */
              rxSduState->Aborted = FALSE; /* VCA_J1939TP_RXSDUSTATE_VIA_RXPDU_CSL03 */
              /* protected against concurrent reception of TP.CM message */ /* Check if this is necessary */
              rxSduState->State = J1939TP_STATE_BAM_BAM_BUSY; /* VCA_J1939TP_RXSDUSTATE_VIA_RXPDU_CSL03 */
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

#  if (J1939TP_RUNTIME_ERROR_REPORT == STD_ON)
  /* If RuntimeErrorReporting is enabled and a connection has been found but has not yet been allocated. */
  if ((found == TRUE) && (allocated == FALSE))
  {
    /* Then report runtimer error that no free connection found for the incoming BAM connection */
    J1939Tp_ReportRuntimeError(J1939TP_SID_RXINDICATION, J1939TP_E_NO_CONNECTION);
  }
#  else
  J1939TP_DUMMY_STATEMENT(found); /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */
#  endif

  /* Return the allocation information for the new connection. */
  return allocated;
} /* J1939Tp_BamInternalRxIndication_AllocateRxChannel */ /* PRQA S 6080 */ /* MD_MSR_STMIF */
# endif


# if (J1939TP_BAM_RX_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  J1939Tp_BamInternalRxIndication_ReceiveTpCmBam()
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
J1939TP_LOCAL_INLINE void J1939Tp_BamInternalRxIndication_ReceiveTpCmBam(J1939Tp_RxSduRxNSduIdxOfRxChannelRxNSduType rxSduIdx,
                                                                         P2CONST(PduInfoType, AUTOMATIC, J1939TP_APPL_DATA) info,
                                                                         uint8 sa,
                                                                         uint16 size)
{
  boolean invalidSize;
  J1939Tp_RxNSduStateType *rxSduState = &J1939Tp_GetRxSduState(J1939Tp_GetRxSduStateIdxOfRxSdu(rxSduIdx));
  uint8_least packets = (uint8_least) J1939Tp_Get_Packets(size);


#  if (J1939TP_RUNTIME_ERROR_REPORT == STD_ON)
  /* Verify that 'packets' correspond to the Total Number Of Packets value. */
  if (packets != info->SduDataPtr[J1939TP_TPCM_TNOP])
  {
    /* If not, then report the runtime error J1939TP_E_INVALID_TNOP. */
    J1939Tp_ReportRuntimeError(J1939TP_SID_RXINDICATION, J1939TP_E_INVALID_TNOP);
  }
#  endif

#  if (J1939TP_ISVARIABLEOFRXSDU == STD_ON)
  /* If the SDU size is variable */
  if (J1939Tp_IsIsVariableOfRxSdu(rxSduIdx))
  {
    /* Then an invalid size is there when the total message size is greater than the configured length. */
    invalidSize = (boolean) (size > J1939Tp_GetPduLengthOfRxSdu(rxSduIdx)); /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */
  }
  /* Otherwise */
  else
#  endif
  {
    /* An invalid size is there when the total message size is not equal with the configured length. */
    /* PRQA S 4304 1 */ /* MD_MSR_AutosarBoolean */
    invalidSize = (boolean) (size != J1939Tp_GetPduLengthOfRxSdu(rxSduIdx));
  }

  /* If the size is invalid */
  if (invalidSize == TRUE)
  {
    /* Report the runtimer error J1939TP_E_INVALID_SIZE and set the state to IDLE. */
    J1939Tp_ReportRuntimeError(J1939TP_SID_RXINDICATION, J1939TP_E_INVALID_SIZE);

    /* no protection required - transition from uninterruptible state */
    rxSduState->State = J1939TP_STATE_IDLE; /* VCA_J1939TP_RXSDUSTATE_VIA_RXSDU_CSL03 */
  }
  /* Otherwise the size is valid */
  else
  {
    PduInfoType addrInfo;
    BufReq_ReturnType tpResult;

    addrInfo.SduLength = J1939Tp_GetMetaDataLengthOfRxSdu(rxSduIdx);
    addrInfo.SduDataPtr = &(info->SduDataPtr[J1939TP_NPDU_MDL_POS]);

    /* Request the start of the reception from the upper layer. */
    tpResult = PduR_J1939TpStartOfReception(J1939Tp_GetSduIdOfRxSdu(rxSduIdx), &addrInfo, (PduLengthType) size, /* VCA_J1939TP_FCTCALL_PTR2LOCAL */
                                            &(rxSduState->BufSize));
    /* If the request was successful */
    if (tpResult == BUFREQ_OK)
    {
      /* Then get the payload data. */
      rxSduState->Size = size; /* VCA_J1939TP_RXSDUSTATE_VIA_RXSDU_CSL03 */
      rxSduState->Packets = packets; /* VCA_J1939TP_RXSDUSTATE_VIA_RXSDU_CSL03 */
      rxSduState->Sender = sa; /* VCA_J1939TP_RXSDUSTATE_VIA_RXSDU_CSL03 */
      rxSduState->Receiver = J1939TP_BROADCAST_ADDRESS; /* VCA_J1939TP_RXSDUSTATE_VIA_RXSDU_CSL03 */
      rxSduState->Sequence = J1939TP_RX_SEQUENCE_INITIAL; /* VCA_J1939TP_RXSDUSTATE_VIA_RXSDU_CSL03 */

      /* Set the timeout and the state to DATA that expects a data frame. */
      rxSduState->TimeOut = J1939Tp_GetTime_T1(); /*!< \trace SPEC-2167345 */ /* VCA_J1939TP_RXSDUSTATE_VIA_RXSDU_CSL03 */
      /* no protection required - transition from uninterruptible state */
      rxSduState->State = J1939TP_STATE_BAM_DATA; /* VCA_J1939TP_RXSDUSTATE_VIA_RXSDU_CSL03 */
    }
    /* Otherwise */
    else
    {
      /* Set the state to IDLE. */
      /*! \trace SPEC-2167310, SPEC-2167311 */
      /* no protection required - transition from uninterruptible state */
      rxSduState->State = J1939TP_STATE_IDLE; /* VCA_J1939TP_RXSDUSTATE_VIA_RXSDU_CSL03 */
    }
  }
}
# endif


# if (J1939TP_BAM_RX_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  J1939Tp_BamInternalRxIndication_FindActiveRxChannel()
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
J1939TP_LOCAL_INLINE boolean J1939Tp_BamInternalRxIndication_FindActiveRxChannel(PduIdType rxPduIdx,
                                                    uint8 sa,
                                                    J1939Tp_RxSduRxNSduIdxOfRxChannelRxNSduType * rxSduIdx)
{
  J1939Tp_RxPduRxChannelRxChannelTableIndEndIdxOfRxPduType rxPduRxChannelIdx;
  boolean found = FALSE;

  /* Iterate over all Rx channels that correspond to the given rxPduIdx as long as no active connection has been found. */
  for (rxPduRxChannelIdx = J1939Tp_GetRxPduRxChannelRxChannelTableIndStartIdxOfRxPdu(rxPduIdx);
       (rxPduRxChannelIdx < J1939Tp_GetRxPduRxChannelRxChannelTableIndEndIdxOfRxPdu(rxPduIdx)) && (found == FALSE);
       rxPduRxChannelIdx++)
  {
    J1939Tp_RxChannelRxChannelIdxOfRxPduRxChannelType rxChannelIdx = J1939Tp_GetRxChannelRxChannelIdxOfRxPduRxChannel(rxPduRxChannelIdx);
    J1939Tp_RxChannelRxNSduRxNSduTableIndEndIdxOfRxChannelType rxChannelSduIdx;

    /* Iterate over all Rx SDUs that correspond to the given Rx channel. */
    for (rxChannelSduIdx = J1939Tp_GetRxChannelRxNSduRxNSduTableIndStartIdxOfRxChannel(rxChannelIdx);
         rxChannelSduIdx < J1939Tp_GetRxChannelRxNSduRxNSduTableIndEndIdxOfRxChannel(rxChannelIdx); rxChannelSduIdx++)
    {
      const J1939Tp_RxNSduStateType *rxSduState;

      *rxSduIdx = J1939Tp_GetRxSduRxNSduIdxOfRxChannelRxNSdu(rxChannelSduIdx);
      rxSduState = &J1939Tp_GetRxSduState(J1939Tp_GetRxSduStateIdxOfRxSdu(*rxSduIdx));

      /* If the connection is in use and the Sender matches with the source address. */
      if (((rxSduState->State & J1939TP_STATEMASK_BAM) != J1939TP_STATE_IDLE) && (rxSduState->Sender == sa))
      {
        /* Then an active connection with the given characteristics has been found. */
        found = TRUE;

        break;
      }
    }
  }

  /* Return the result. */
  return found;
}
# endif


# if (J1939TP_BAM_RX_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  J1939Tp_BamInternalRxIndication_ReceiveTpDt()
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
 */
J1939TP_LOCAL_INLINE void J1939Tp_BamInternalRxIndication_ReceiveTpDt(J1939Tp_RxSduRxNSduIdxOfRxChannelRxNSduType
                                                                      rxSduIdx, P2CONST(PduInfoType, AUTOMATIC,
                                                                                      J1939TP_APPL_DATA) info)
{
  J1939Tp_RxNSduStateType *rxSduState = &J1939Tp_GetRxSduState(J1939Tp_GetRxSduStateIdxOfRxSdu(rxSduIdx));

  /* If the state expects a data frame. */
  SchM_Enter_J1939Tp_J1939TP_EXCLUSIVE_AREA_RXNSDULOCK();
  if (rxSduState->State == J1939TP_STATE_BAM_DATA)
  {
    /* protected against concurrent timeout and concurrent reception of TP.CM message */
    rxSduState->State = J1939TP_STATE_BAM_DATA_BUSY; /* VCA_J1939TP_RXSDUSTATE_VIA_RXSDU_CSL03 */
    SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_RXNSDULOCK();

    /* If the Aborted flag is set */
    if (rxSduState->Aborted == TRUE)
    {
      /* Then inform the PduR about the missed indication and set its state to idle. */
      /* no protection required - transition from uninterruptible state */
      rxSduState->State = J1939TP_STATE_FINISH; /* VCA_J1939TP_RXSDUSTATE_VIA_RXSDU_CSL03 */

      /*! \trace SPEC-2167305 */
      PduR_J1939TpRxIndication(J1939Tp_GetSduIdOfRxSdu(rxSduIdx), E_NOT_OK);

      /* no protection required - transition from uninterruptible state */
      rxSduState->State = J1939TP_STATE_IDLE; /* VCA_J1939TP_RXSDUSTATE_VIA_RXSDU_CSL03 */
    }
    /* Otherwise */
    else
    {
      /* Increment the Sequence number. */
      rxSduState->Sequence++; /* VCA_J1939TP_RXSDUSTATE_VIA_RXSDU_CSL03 */

      /* Verify that the Sequence number does match with the received one. */
      if (rxSduState->Sequence == info->SduDataPtr[J1939TP_TPDT_SEQ])
      {
        /* Then prepare the PDU. */
        PduInfoType pdu;
        BufReq_ReturnType tpResult;

        pdu.SduDataPtr = &info->SduDataPtr[J1939TP_TPDT_DATA];
        pdu.SduLength = J1939TP_TPDT_DATA_SIZE;

        /* If it is the last frame */
        if (rxSduState->Sequence == rxSduState->Packets)
        {
          /* Set the size of the remaining payload. */
          pdu.SduLength =
            (PduLengthType) ((rxSduState->Size) -
                             (PduLengthType) ((PduLengthType) ((PduLengthType) (rxSduState->Sequence) - 1u) *
                                              (PduLengthType) J1939TP_TPDT_DATA_SIZE));
        }

        /* Request the payload data from the upper layer. */
        tpResult = PduR_J1939TpCopyRxData(J1939Tp_GetSduIdOfRxSdu(rxSduIdx), &pdu, &rxSduState->BufSize); /* VCA_J1939TP_FCTCALL_PTR2LOCAL */ /* VCA_J1939TP_RXSDUSTATE_VIA_RXSDU_CSL03 */

        /* If the request was successful */
        if (tpResult == BUFREQ_OK)
        {
          /* If it is the last frame */
          if (rxSduState->Sequence == rxSduState->Packets)
          {
            /* Then inform the PduR about the successful indication and set its state to idle. */
            /* no protection required - transition from uninterruptible state */
            rxSduState->State = J1939TP_STATE_FINISH; /* VCA_J1939TP_RXSDUSTATE_VIA_RXSDU_CSL03 */

            /*! \trace SPEC-2167304 */
            PduR_J1939TpRxIndication(J1939Tp_GetSduIdOfRxSdu(rxSduIdx), E_OK); 

            /* no protection required - transition from uninterruptible state */
            rxSduState->State = J1939TP_STATE_IDLE; /* VCA_J1939TP_RXSDUSTATE_VIA_RXSDU_CSL03 */
          }
          /* Otherwise */
          else
          {
            /* Set the timeout and the state to DATA that expects another data frame. */
            rxSduState->TimeOut = J1939Tp_GetTime_T1(); /*!< \trace SPEC-2167345 */ /* VCA_J1939TP_RXSDUSTATE_VIA_RXSDU_CSL03 */
            /* no protection required - transition from uninterruptible state */
            rxSduState->State = J1939TP_STATE_BAM_DATA; /* VCA_J1939TP_RXSDUSTATE_VIA_RXSDU_CSL03 */
          }
        }
        /* Otherwise */
        else
        {
          /* Inform the PduR about the missed indication and set the state to idle. */
          /*! \trace SPEC-2167311 */
          /* no protection required - transition from uninterruptible state */
          rxSduState->State = J1939TP_STATE_FINISH; /* VCA_J1939TP_RXSDUSTATE_VIA_RXSDU_CSL03 */

          /*! \trace SPEC-2167305 */
          PduR_J1939TpRxIndication(J1939Tp_GetSduIdOfRxSdu(rxSduIdx), E_NOT_OK); 

          /* no protection required - transition from uninterruptible state */
          rxSduState->State = J1939TP_STATE_IDLE; /* VCA_J1939TP_RXSDUSTATE_VIA_RXSDU_CSL03 */
        }
      }
      /* Otherwise */
      else
      {
        /*! \trace SPEC-2167347 */
        /* no protection required - transition from uninterruptible state */
        rxSduState->State = J1939TP_STATE_FINISH; /* VCA_J1939TP_RXSDUSTATE_VIA_RXSDU_CSL03 */

        J1939Tp_ReportRuntimeError(J1939TP_SID_RXINDICATION, J1939TP_E_INVALID_SN);

        /*! \trace SPEC-2167305 */
        PduR_J1939TpRxIndication(J1939Tp_GetSduIdOfRxSdu(rxSduIdx), E_NOT_OK); 

        /* no protection required - transition from uninterruptible state */
        rxSduState->State = J1939TP_STATE_IDLE; /* VCA_J1939TP_RXSDUSTATE_VIA_RXSDU_CSL03 */
      }
    }
  }
  /* Otherwise */
  else
  {
    /* The data frame is ignored because it has been received unexpectedly. */
    SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_RXNSDULOCK();
  }
} /* PRQA S 6080 */ /* MD_MSR_STMIF */
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


# if (J1939TP_BAM_TX_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  J1939Tp_BamTxMain()
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
FUNC(void, J1939TP_CODE) J1939Tp_BamTxMain(PduIdType txSduIdx)
{
  J1939Tp_TxNSduStateType *txSduState = &J1939Tp_GetTxSduState(J1939Tp_GetTxSduStateIdxOfTxSdu(txSduIdx));

  /* If a timeout occurs, */
  if (txSduState->TimeOut == 0u)
  {
    /*! \trace SPEC-2167345 */
    J1939Tp_ReportRuntimeError(J1939TP_SID_MAINFUNCTION, J1939TP_E_TIMEOUT_TR);

    /* And the state of the connection is either BAM or data frame, */
    if ((txSduState->State == J1939TP_STATE_BAM_BAM) || (txSduState->State == J1939TP_STATE_BAM_DATA))
    {
      /* Then inform the PduR about the missed confirmation and set its state to idle. */
      /* no protection required - all exits from BAM and data states are in the scope of this function */
      txSduState->State = J1939TP_STATE_FINISH; /* VCA_J1939TP_TXSDUSTATE_VIA_TXSDU_CSL03 */

      /*! \trace SPEC-2167303 */
      PduR_J1939TpTxConfirmation(J1939Tp_GetSduIdOfTxSdu(txSduIdx), E_NOT_OK);

      /* no protection required - transition from uninterruptible state */
      txSduState->State = J1939TP_STATE_IDLE; /* VCA_J1939TP_TXSDUSTATE_VIA_TXSDU_CSL03 */
    }
  }
  /* Otherwise */
  else
  {
    /* Decrement the timeout value by one and determine the current state. */
    --txSduState->TimeOut; /* VCA_J1939TP_TXSDUSTATE_VIA_TXSDU_CSL03 */

    switch (txSduState->State)
    {
    case J1939TP_STATE_BAM_BAM:
      /* If it is in state BAM, then request transmission of the connection management frame. */
      J1939Tp_BamInternalTransmitTpCmBam(txSduIdx);
      break;

    case J1939TP_STATE_BAM_DATA:
      /* If it is in state data frame, then request transmission of the data frame only after at least 50ms have
         elapsed. */
      if (txSduState->TimeOut <= (J1939Tp_GetTime_Tr() - J1939Tp_GetTime_Bam())) /*!< \trace SPEC-2167345 */
      {
        /*! \trace SPEC-2167316 */
        J1939Tp_BamInternalTransmitTpDt(txSduIdx);
      }
      break;

    default: /* COV_J1939TP_SWITCHCASE_DEFAULT */
      break;
    }
  }
} /* J1939Tp_BamTxMain */
# endif


# if (J1939TP_BAM_RX_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  J1939Tp_BamRxMain()
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
FUNC(void, J1939TP_CODE) J1939Tp_BamRxMain(PduIdType rxSduIdx)
{
  J1939Tp_RxNSduStateType *rxSduState = &J1939Tp_GetRxSduState(J1939Tp_GetRxSduStateIdxOfRxSdu(rxSduIdx));

  /* If the aborted flag is set, */
  if (rxSduState->Aborted == TRUE)
  {
    /* And the state of the connection is AF */
    SchM_Enter_J1939Tp_J1939TP_EXCLUSIVE_AREA_RXNSDULOCK();
    if (rxSduState->State == J1939TP_STATE_BAM_DATA)
    {
      /* Then inform the PduR about the missed indication and set its state to idle. */
      /* protected against concurrent reception of TP.DT message */
      rxSduState->State = J1939TP_STATE_FINISH; /* VCA_J1939TP_RXSDUSTATE_VIA_RXSDU_CSL03 */
      SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_RXNSDULOCK();

      /*! \trace SPEC-2167305 */
      PduR_J1939TpRxIndication(J1939Tp_GetSduIdOfRxSdu(rxSduIdx), E_NOT_OK);

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
    /*! \trace SPEC-2167345 */
    J1939Tp_ReportRuntimeError(J1939TP_SID_MAINFUNCTION, J1939TP_E_TIMEOUT_T1);

    /* And the state of the connection is DATA, */
    SchM_Enter_J1939Tp_J1939TP_EXCLUSIVE_AREA_RXNSDULOCK();
    if (rxSduState->State == J1939TP_STATE_BAM_DATA)
    {
      /* Then inform the PduR about the missed indication and set its state to idle. */
      /* protected against concurrent reception of TP.DT message */
      rxSduState->State = J1939TP_STATE_FINISH; /* VCA_J1939TP_RXSDUSTATE_VIA_RXSDU_CSL03 */
      SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_RXNSDULOCK();

      /*! \trace SPEC-2167305 */
      PduR_J1939TpRxIndication(J1939Tp_GetSduIdOfRxSdu(rxSduIdx), E_NOT_OK);

      /* no protection required - transition from uninterruptible state */
      rxSduState->State = J1939TP_STATE_IDLE; /* VCA_J1939TP_RXSDUSTATE_VIA_RXSDU_CSL03 */
    }
    else
    {
      SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_RXNSDULOCK();
    }
  }
  /* Otherwise */
  else
  {
    /* Decrement the timeout value by one. */
    --rxSduState->TimeOut; /* VCA_J1939TP_RXSDUSTATE_VIA_RXSDU_CSL03 */
  }
} /* J1939Tp_BamRxMain */
# endif


# if (J1939TP_BAM_TX_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  J1939Tp_BamTransmit()
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
 */
FUNC(Std_ReturnType, J1939TP_CODE) J1939Tp_BamTransmit(PduIdType txSduIdx,
                                                       P2CONST(PduInfoType, AUTOMATIC, J1939TP_APPL_DATA) info)
{
  Std_ReturnType result = E_NOT_OK;

  /* Verify that the SDU length does not exceed J1939TP_MAX_LENGTH. */
  if (info->SduLength > J1939TP_MAX_LENGTH)
  {
    /*! \trace SPEC-2167289 */
    J1939Tp_ReportDevError(J1939TP_SID_TRANSMIT, J1939TP_E_INVALID_LENGTH);
  }
  else
  {
    J1939Tp_TxNSduStateType *txSduState = &J1939Tp_GetTxSduState(J1939Tp_GetTxSduStateIdxOfTxSdu(txSduIdx));

    /* Proceed If the state is IDLE */
    SchM_Enter_J1939Tp_J1939TP_EXCLUSIVE_AREA_TXNSDULOCK();
    if (txSduState->State == J1939TP_STATE_IDLE)
    {
      /* Then set the state to BAM_BUSY. */
      /* protected against a reentrant call for the same N-SDU */ /* Check if this is necessary */
      txSduState->State = J1939TP_STATE_BAM_BAM_BUSY;
      SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_TXNSDULOCK();

      {
        J1939Tp_TxChannelChannelIdxOfTxSduType txChannelIdx = J1939Tp_GetTxChannelChannelIdxOfTxSdu(txSduIdx);
        uint8 sa;
        boolean found;

        /* Determine the source address */
        /*! \trace SPEC-2167312 */
        if (J1939Tp_GetTxSaOfTxChannel(txChannelIdx) == J1939TP_NO_ADDRESS_CONFIGURED)
        {
          sa = info->SduDataPtr[J1939TP_MDL_SA_POS];
        }
        else
        {
          sa = J1939Tp_GetTxSaOfTxChannel(txChannelIdx);
        }

        /* Search for connections with the same characteristics. */
        found = J1939Tp_BamInternalTransmit_SearchConflictingTxChannel(txSduIdx, txChannelIdx, sa);

        /* If no connection was found */
        /*! \trace SPEC-2167293 */
        if (found == FALSE)
        {
          /* Prepares the data to be transmitted. */
          txSduState->Size = info->SduLength; /* VCA_J1939TP_TXSDUSTATE_VIA_TXSDU_CSL03 */
          txSduState->Packets = (uint32) (J1939Tp_Get_Packets((uint32) (info->SduLength))); /* VCA_J1939TP_TXSDUSTATE_VIA_TXSDU_CSL03 */
          txSduState->Sender = sa; /* VCA_J1939TP_TXSDUSTATE_VIA_TXSDU_CSL03 */
          txSduState->Receiver = J1939TP_BROADCAST_ADDRESS; /* VCA_J1939TP_TXSDUSTATE_VIA_TXSDU_CSL03 */
          txSduState->Priority = J1939Tp_InternalGetPriority(txSduIdx, info); /* VCA_J1939TP_TXSDUSTATE_VIA_TXSDU_CSL03 */
          txSduState->Sequence = J1939TP_TX_SEQUENCE_INITIAL; /* VCA_J1939TP_TXSDUSTATE_VIA_TXSDU_CSL03 */
          txSduState->TimeOut = J1939Tp_GetTime_Tr(); /*!< \trace SPEC-2167345 */ /* VCA_J1939TP_TXSDUSTATE_VIA_TXSDU_CSL03 */
          /* no protection required - transition from uninterruptible state */
          txSduState->State = J1939TP_STATE_BAM_BAM;

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
} /* End of J1939Tp_BamTransmit */
# endif


/**********************************************************************************************************************
 *  J1939Tp_BamTxConfirmation()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */

# if (J1939TP_BAM_TX_ENABLED == STD_ON)
FUNC(void, J1939TP_CODE) J1939Tp_BamTxConfirmation(PduIdType txSduIdx, J1939Tp_PduTypeOfTxPduType txPduType)
{
  J1939Tp_TxNSduStateType *txSduState = &J1939Tp_GetTxSduState(J1939Tp_GetTxSduStateIdxOfTxSdu(txSduIdx));

  if (txPduType == J1939TP_TPCM_PDUTYPEOFTXPDU)
  {
    SchM_Enter_J1939Tp_J1939TP_EXCLUSIVE_AREA_TXNSDULOCK();
    if (txSduState->State == J1939TP_STATE_BAM_BAM_CONF)
    {
      /* advance state to send first TP.DT frame */
      txSduState->TimeOut = J1939Tp_GetTime_Tr(); /*!< \trace SPEC-2167345 */ /* VCA_J1939TP_TXSDUSTATE_VIA_TXSDU_CSL03 */
      /* protected against concurrent transmission failure and early Tx confirmation timeout */
      txSduState->State = J1939TP_STATE_BAM_DATA; /* VCA_J1939TP_TXSDUSTATE_VIA_TXSDU_CSL03 */
    }
    SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_TXNSDULOCK();
  }
  else /* txPduType == J1939TP_TPDT_PDUTYPEOFTXPDU */
  {
    SchM_Enter_J1939Tp_J1939TP_EXCLUSIVE_AREA_TXNSDULOCK();
    if (txSduState->State == J1939TP_STATE_BAM_DATA_CONF)
    {
      if (txSduState->Sequence == txSduState->Packets)
      {
        /* protected against concurrent transmission failure and early Tx confirmation timeout */
        txSduState->State = J1939TP_STATE_FINISH; /* VCA_J1939TP_TXSDUSTATE_VIA_TXSDU_CSL03 */
        SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_TXNSDULOCK();

        /*! \trace SPEC-2167302 */
        PduR_J1939TpTxConfirmation(J1939Tp_GetSduIdOfTxSdu(txSduIdx), E_OK); 

        /* no protection required - transition from uninterruptible state */
        txSduState->State = J1939TP_STATE_IDLE; /* VCA_J1939TP_TXSDUSTATE_VIA_TXSDU_CSL03 */
      }
      else
      {
        /* advance state to send next TP.DT frame */
        txSduState->Sequence++; /* VCA_J1939TP_TXSDUSTATE_VIA_TXSDU_CSL03 */
        txSduState->TimeOut = J1939Tp_GetTime_Tr(); /*!< \trace SPEC-2167345 */ /* VCA_J1939TP_TXSDUSTATE_VIA_TXSDU_CSL03 */
        /* protected against concurrent transmission failure and early Tx confirmation timeout */
        txSduState->State = J1939TP_STATE_BAM_DATA; /* VCA_J1939TP_TXSDUSTATE_VIA_TXSDU_CSL03 */
        SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_TXNSDULOCK();
      }
    }
    else
    {
      SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_TXNSDULOCK();
    }
  }
} /* J1939Tp_BamTxConfirmation */
# endif


# if (J1939TP_BAM_RX_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  J1939Tp_BamRxIndication()
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
FUNC(void, J1939TP_CODE) J1939Tp_BamRxIndication(PduIdType rxPduIdx,
                                                 P2CONST(PduInfoType, AUTOMATIC, J1939TP_APPL_DATA) info,
                                                 J1939Tp_PduTypeOfRxPduType rxPduType, uint8 sa, uint8 da)
{
#  if (J1939TP_CANIF_DLCCHECK == STD_OFF)
  /* Verify that the SDU length is J1939TP_NPDU_LENGTH (if CanIfDlcCheck is disabled). */
  if (info->SduLength == J1939TP_NPDU_LENGTH)
#  endif
  {
    /* Verify that the destination address is the broadcast address. */
    if (da != J1939TP_BROADCAST_ADDRESS)
    {
      /*! \trace SPEC-2167310 */
#  if (J1939TP_RUNTIME_ERROR_REPORT == STD_ON)
      /* If it is not the broadcast address and the control byte is J1939TP_CB_BAM */
      if (info->SduDataPtr[J1939TP_TPCM_CB] == J1939TP_CB_BAM)
      {
        /* Then report the runtime error J1939TP_E_INVALID_CONTROL_BYTE */

        J1939Tp_ReportRuntimeError(J1939TP_SID_RXINDICATION, J1939TP_E_INVALID_CONTROL_BYTE);
      }
#  endif
    }
    else
    {
      /* If the PDU type is a Connection Management frame. */
      if (rxPduType == J1939TP_TPCM_PDUTYPEOFRXPDU)
      {
        /* And if the control byte is J1939TP_CB_BAM */
        if (info->SduDataPtr[J1939TP_TPCM_CB] == J1939TP_CB_BAM)
        {
          /* PRQA S 1891 1 */ /* MD_J1939Tp_10.7 */
          uint32 pgn = (uint32) (J1939Tp_Get_PGN(info->SduDataPtr[J1939TP_TPCM_PGN_LO], info->SduDataPtr[J1939TP_TPCM_PGN_MD],
                                                 info->SduDataPtr[J1939TP_TPCM_PGN_HI]));

          /* Verify that the PGN is valid. */
          if (!J1939Tp_PGN_Valid(pgn))
          {
            /* If the PGN is invalid report the runtime error J1939TP_E_INVALID_PGN. */
            /*! \trace SPEC-2167310 */
            J1939Tp_ReportRuntimeError(J1939TP_SID_RXINDICATION, J1939TP_E_INVALID_PGN);
          }
          else
          {
            uint16 size = J1939Tp_Get_TMS(info->SduDataPtr[J1939TP_TPCM_TMS_LO], info->SduDataPtr[J1939TP_TPCM_TMS_HI]);

            /* Verify that the total message size does not exceed J1939TP_MAX_LENGTH. */
            if (size > J1939TP_MAX_LENGTH)
            {
              /* Otherwise report runtime error J1939TP_E_INVALID_TMS. */
              J1939Tp_ReportRuntimeError(J1939TP_SID_RXINDICATION, J1939TP_E_INVALID_TMS);
            }
            else
            {
              J1939Tp_RxSduRxNSduIdxOfRxChannelRxNSduType rxSduIdx = 0u;

              /* Allocate a free channel and start the reception of the Connection Management frame. */
              if (J1939Tp_BamInternalRxIndication_AllocateRxChannel(rxPduIdx, sa, pgn, &rxSduIdx) == TRUE)
              {
                J1939Tp_BamInternalRxIndication_ReceiveTpCmBam(rxSduIdx, info, sa, size);
              }
            }
          }
        }
        /* Otherwise */
        else
        {
          /* Report the runtime error J1939TP_E_INVALID_CONTROL_BYTE */
          J1939Tp_ReportRuntimeError(J1939TP_SID_RXINDICATION, J1939TP_E_INVALID_CONTROL_BYTE);
        }
      }
      /* Otherwise the PDU type is a Data frame. */
      else /* if (rxPduType == J1939TP_TPDT_PDUTYPEOFRXPDU) */
      {
        J1939Tp_RxSduRxNSduIdxOfRxChannelRxNSduType rxSduIdx = 0u;

        /* Find the active connection and start the reception of a data frame. */
        if (J1939Tp_BamInternalRxIndication_FindActiveRxChannel(rxPduIdx, sa, &rxSduIdx) == TRUE)
        {
          J1939Tp_BamInternalRxIndication_ReceiveTpDt(rxSduIdx, info);
        }
      }
    }
  }
#  if ((J1939TP_CANIF_DLCCHECK == STD_OFF) && (J1939TP_RUNTIME_ERROR_REPORT == STD_ON))
  /* Otherwise */
  else
  {
    /* Report the runtime error J1939TP_E_INVALID_DLC. */
    J1939Tp_ReportRuntimeError(J1939TP_SID_RXINDICATION, J1939TP_E_INVALID_DLC);
  }
#  endif
} /* J1939Tp_BamRxIndication */ /* PRQA S 6080 */ /* MD_MSR_STMIF */
# endif


# define J1939TP_STOP_SEC_CODE
/*lint -save -esym(961, 19.1) */
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*lint -restore */
/*============================================== J1939TP_STOP_SEC_CODE ==============================================*/
#endif

/* COV_JUSTIFICATION_BEGIN

\ID COV_J1939TP_SWITCHCASE_DEFAULT
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
