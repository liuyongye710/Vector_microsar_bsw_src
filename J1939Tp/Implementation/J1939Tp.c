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
 *         File:  J1939Tp.c
 *       Module:  J1939 Transport Layer
 *
 *  Description:  Implementation of the SAE J1939 Transport Layer module.
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

#define J1939TP_C

#include "J1939Tp.h"
#include "J1939Tp_Cbk.h"

#include "J1939Tp_Int.h"
#include "J1939Tp_Direct.h"
#include "J1939Tp_Bam.h"
#include "J1939Tp_Cmdt.h"
#if (J1939TP_ETP_ENABLED == STD_ON)
# include "J1939Tp_Etp.h"
#endif
#if (J1939TP_FPP_ENABLED == STD_ON)
# include "J1939Tp_Fpp.h"
#endif

/*! \trace SPEC-2167286 */
#include "PduR_J1939Tp.h"
/*! \trace SPEC-2167287 */
#include "CanIf.h"

#include "SchM_J1939Tp.h"

#if (J1939TP_USE_ECUM_BSW_ERROR_HOOK == STD_ON)
# include "EcuM_Error.h"
#endif


/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/

/* Vendor specific BSW module version information */
#define J1939TP_MAJOR_SOURCE_VERSION            (4u)
#define J1939TP_MINOR_SOURCE_VERSION            (1u)
#define J1939TP_PATCH_SOURCE_VERSION            (0u)

/* Vendor specific BSW generator version information */
#define J1939TP_MAJOR_GENERATOR_VERSION         (1u)
#define J1939TP_MINOR_GENERATOR_VERSION         (6u)

/* Check the vendor specific version of J1939Tp module header file */
#if ((J1939TP_SW_MAJOR_VERSION != J1939TP_MAJOR_SOURCE_VERSION) || (J1939TP_SW_MINOR_VERSION != J1939TP_MINOR_SOURCE_VERSION) || (J1939TP_SW_PATCH_VERSION != J1939TP_PATCH_SOURCE_VERSION))
# error "Vendor specific version numbers of J1939Tp.c and J1939Tp.h are inconsistent"
#endif

/* Check the version of the configuration header file */
#if ((J1939TP_CFG_MAJOR_VERSION != J1939TP_MAJOR_GENERATOR_VERSION) || (J1939TP_CFG_MINOR_VERSION != J1939TP_MINOR_GENERATOR_VERSION))
# error "Vendor specific version numbers of J1939Tp.c and J1939Tp_Cfg.h are inconsistent!"
#endif


/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/

/*! Global module state \trace SPEC-2167294 */
#define J1939TP_UNINIT                          (0u)
#define J1939TP_INIT                            (1u)


/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/

/*======================================= J1939TP_START_SEC_VAR_ZERO_INIT_8BIT ======================================*/
#define J1939TP_START_SEC_VAR_ZERO_INIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*lint -restore */

/*! Initialization state of the J1399Tp */
J1939TP_LOCAL VAR(uint8, J1939TP_VAR_ZERO_INIT) J1939Tp_ModuleInitialized = J1939TP_UNINIT;

#define J1939TP_STOP_SEC_VAR_ZERO_INIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*lint -restore */
/*======================================= J1939TP_STOP_SEC_VAR_ZERO_INIT_8BIT =======================================*/


/**********************************************************************************************************************
 *  INTERNAL DATA
 *********************************************************************************************************************/

/*=================================== J1939TP_START_SEC_VAR_ZERO_INIT_UNSPECIFIED ===================================*/
#define J1939TP_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*lint -restore */

/*! Post-build configuration data of the J1939Tp */
#if (J1939TP_USE_INIT_POINTER == STD_ON)
/*!
* \spec
*   strong invariant J1939Tp_ConfigDataPtr == J1939Tp_Config_Ptr;
* \endspec
*/
P2CONST(J1939Tp_ConfigType, J1939TP_VAR_NOINIT, J1939TP_PBCFG) J1939Tp_ConfigDataPtr;
#endif

#define J1939TP_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*lint -restore */
/*=================================== J1939TP_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED ====================================*/


/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/*============================================== J1939TP_START_SEC_CODE =============================================*/
#define J1939TP_START_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*lint -restore */

#if (J1939TP_FPP_ENABLED == STD_ON)
/**********************************************************************************************************************
 * J1939Tp_InternalMain_TxPduFpp()
 *********************************************************************************************************************/
/*! \brief        Cyclic handling of confirmation of Tx PDUs.
 *  \details      Used for scheduling purposes and timeout supervision regarding Tx PDUs of transport protocol FPP
 *  \param[in]    txSduIdx    SDU index that is used to get Tx SDU state.
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *  \trace        SPEC-2167301
 *  \spec
 *    requires    txSduIdx < J1939Tp_GetSizeOfTxSdu();
 *  \endspec
 */
# if (J1939TP_INVALIDHNDOFTXSDU == STD_ON)
/*!
 *  \spec
 *    requires   !J1939Tp_IsInvalidHndOfTxSdu(txSduIdx);
 *  \endspec
 */
# endif
/*********************************************************************************************************************/
J1939TP_LOCAL_INLINE void J1939Tp_InternalMain_TxPduFpp(PduIdType txSduIdx);
#endif

#if ((J1939TP_BAM_TX_ENABLED == STD_ON) || (J1939TP_CMDT_ENABLED == STD_ON))
/**********************************************************************************************************************
 * J1939Tp_InternalMain_TxPduTpCm()
 *********************************************************************************************************************/
/*! \brief        Cyclic handling of Tx PDUs.
 *  \details      Used for scheduling purposes and timeout supervision regarding TP.CM PDUs of transport protocol CMDT
 *                and BAM.
 *  \param[in]    sduIdx    SDU index that is used to get SDU state.
 *  \param[in]    sduType   SDU type whose range is J1939TP_NSDU_CMDT_RX, J1939TP_NSDU_CMDT_TX, J1939TP_NSDU_BAM
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *  \trace        SPEC-2167301
 */
# if ((J1939TP_CMDT_RX_ENABLED == STD_ON) && ((J1939TP_BAM_TX_ENABLED == STD_ON) || (J1939TP_CMDT_TX_ENABLED == STD_ON)))
/*!
 *  \spec
 *    requires    ((sduType == J1939TP_NSDU_CMDT_RX) && (sduIdx < J1939Tp_GetSizeOfRxSdu())) || ((sduType != J1939TP_NSDU_CMDT_RX) && (sduIdx < J1939Tp_GetSizeOfTxSdu()));
 *  \endspec
 */
#  if (J1939TP_INVALIDHNDOFRXSDU == STD_ON)
/*!
 *  \spec
 *    requires   (sduType == J1939TP_NSDU_CMDT_RX) && (!J1939Tp_IsInvalidHndOfRxSdu(sduIdx));
 *  \endspec
 */
#  endif
#  if (J1939TP_INVALIDHNDOFTXSDU == STD_ON)
/*!
 *  \spec
 *    requires   (sduType != J1939TP_NSDU_CMDT_RX) && (!J1939Tp_IsInvalidHndOfTxSdu(sduIdx));
 *  \endspec
 */
#  endif
# elif (J1939TP_CMDT_RX_ENABLED == STD_ON)
/*!
 *  \spec
 *    requires    sduIdx < J1939Tp_GetSizeOfRxSdu();
 *  \endspec
 */
#  if (J1939TP_INVALIDHNDOFRXSDU == STD_ON)
/*!
 *  \spec
 *    requires   !J1939Tp_IsInvalidHndOfRxSdu(sduIdx);
 *  \endspec
 */
#  endif
# elif ((J1939TP_BAM_TX_ENABLED == STD_ON) || (J1939TP_CMDT_TX_ENABLED == STD_ON))
/*!
 *  \spec
 *    requires    sduIdx < J1939Tp_GetSizeOfTxSdu();
 *  \endspec
 */
#  if (J1939TP_INVALIDHNDOFTXSDU == STD_ON)
/*!
 *  \spec
 *    requires   !J1939Tp_IsInvalidHndOfTxSdu(sduIdx);
 *  \endspec
 */
#  endif
# endif
/*********************************************************************************************************************/
J1939TP_LOCAL_INLINE void J1939Tp_InternalMain_TxPduTpCm(PduIdType sduIdx, J1939Tp_NSduType sduType);
#endif

#if ((J1939TP_BAM_TX_ENABLED == STD_ON) || (J1939TP_CMDT_TX_ENABLED == STD_ON))
/**********************************************************************************************************************
 * J1939Tp_InternalMain_TxPduTpDt()
 *********************************************************************************************************************/
/*! \brief        Cyclic handling of confirmation of Tx PDUs.
 *  \details      Used for scheduling purposes and timeout supervision regarding TP.DT PDUs of transport protocol CMDT
 *                and BAM.
 *  \param[in]    txSduIdx    SDU index that is used to get Tx SDU state.
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *  \trace        SPEC-2167301
 *  \spec
 *    requires    txSduIdx < J1939Tp_GetSizeOfTxSdu();
 *  \endspec
 */
# if (J1939TP_INVALIDHNDOFTXSDU == STD_ON)
/*!
 *  \spec
 *    requires   !J1939Tp_IsInvalidHndOfTxSdu(txSduIdx);
 *  \endspec
 */
# endif
 /*********************************************************************************************************************/
J1939TP_LOCAL_INLINE void J1939Tp_InternalMain_TxPduTpDt(PduIdType txSduIdx);
#endif

#if (J1939TP_ETP_ENABLED == STD_ON)
/**********************************************************************************************************************
 * J1939Tp_InternalMain_TxPduEtpCm()
 *********************************************************************************************************************/
/*! \brief        Cyclic handling of Tx PDUs.
 *  \details      Used for scheduling purposes and timeout supervision regarding TP.CM PDUs of transport protocol ETP.
 *  \param[in]    sduIdx    SDU index that is used to get SDU state.
 *  \param[in]    sduType   SDU type whose range is J1939TP_NSDU_ETP_RX, J1939TP_NSDU_ETP_TX
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *  \trace        SPEC-2167301
 */
# if ((J1939TP_ETP_RX_ENABLED == STD_ON) && (J1939TP_ETP_TX_ENABLED == STD_ON))
/*!
 *  \spec
 *    requires    ((sduType == J1939TP_NSDU_ETP_RX) && (sduIdx < J1939Tp_GetSizeOfRxSdu())) || ((sduType == J1939TP_NSDU_ETP_TX) && (sduIdx < J1939Tp_GetSizeOfTxSdu()));
 *  \endspec
 */
#  if (J1939TP_INVALIDHNDOFRXSDU == STD_ON)
/*!
 *  \spec
 *    requires   (sduType == J1939TP_NSDU_ETP_RX) && (!J1939Tp_IsInvalidHndOfRxSdu(sduIdx));
 *  \endspec
 */
#  endif
#  if (J1939TP_INVALIDHNDOFTXSDU == STD_ON)
/*!
 *  \spec
 *    requires   (sduType == J1939TP_NSDU_ETP_TX) && (!J1939Tp_IsInvalidHndOfTxSdu(sduIdx));
 *  \endspec
 */
#  endif
# elif (J1939TP_ETP_RX_ENABLED == STD_ON)
/*!
 *  \spec
 *    requires    sduIdx < J1939Tp_GetSizeOfRxSdu();
 *  \endspec
 */
#  if (J1939TP_INVALIDHNDOFRXSDU == STD_ON)
/*!
 *  \spec
 *    requires   !J1939Tp_IsInvalidHndOfRxSdu(sduIdx);
 *  \endspec
 */
#  endif
# elif (J1939TP_ETP_TX_ENABLED == STD_ON)
/*!
 *  \spec
 *    requires    sduIdx < J1939Tp_GetSizeOfTxSdu();
 *  \endspec
 */
#  if (J1939TP_INVALIDHNDOFTXSDU == STD_ON)
/*!
 *  \spec
 *    requires   !J1939Tp_IsInvalidHndOfTxSdu(sduIdx);
 *  \endspec
 */
#  endif
# endif
/*********************************************************************************************************************/
J1939TP_LOCAL_INLINE void J1939Tp_InternalMain_TxPduEtpCm(PduIdType sduIdx, J1939Tp_NSduType sduType);
#endif

#if (J1939TP_ETP_TX_ENABLED == STD_ON)
/**********************************************************************************************************************
 * J1939Tp_InternalMain_TxPduEtpDt()
 *********************************************************************************************************************/
/*! \brief        Cyclic handling of Tx PDUs
 *  \details      Used for scheduling purposes and timeout supervision regarding TP.DT PDUs of transport protocol ETP.
 *  \param[in]    txSduIdx    SDU index that is used to get the Tx SDU state.
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *  \trace        SPEC-2167301
 *  \spec
 *    requires    txSduIdx < J1939Tp_GetSizeOfTxSdu();
 *  \endspec
 */
# if (J1939TP_INVALIDHNDOFTXSDU == STD_ON)
/*!
 *  \spec
 *    requires   !J1939Tp_IsInvalidHndOfTxSdu(txSduIdx);
 *  \endspec
 */
# endif
/*********************************************************************************************************************/
J1939TP_LOCAL_INLINE void J1939Tp_InternalMain_TxPduEtpDt(PduIdType txSduIdx);
#endif

#if (J1939TP_DIRECT_TX_ENABLED == STD_ON)
/**********************************************************************************************************************
 * J1939Tp_InternalMain_TxPduDirect()
 *********************************************************************************************************************/
/*! \brief        Cyclic handling of confirmation of Tx PDUs.
 *  \details      Used for scheduling purposes and timeout supervision regarding Tx PDUs of direct messages.
 *  \param[in]    txSduIdx    SDU index that is used to get the Tx SDU state.
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *  \trace        SPEC-2167301
 *  \spec
 *    requires    txSduIdx < J1939Tp_GetSizeOfTxSdu();
 *  \endspec
 */
# if (J1939TP_INVALIDHNDOFTXSDU == STD_ON)
/*!
 *  \spec
 *    requires   !J1939Tp_IsInvalidHndOfTxSdu(txSduIdx);
 *  \endspec
 */
# endif
/*********************************************************************************************************************/
J1939TP_LOCAL_INLINE void J1939Tp_InternalMain_TxPduDirect(PduIdType txSduIdx);
#endif

#if (J1939TP_TXPDU == STD_ON)
/**********************************************************************************************************************
 * J1939Tp_InternalMain_TxPdu()
 *********************************************************************************************************************/
/*! \brief        Cyclic handling of Tx PDUs.
 *  \details      Used for scheduling purposes and timeout supervision regarding Tx PDUs.
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
J1939TP_LOCAL_INLINE void J1939Tp_InternalMain_TxPdu(void);
#endif

#if (J1939TP_TXSDU == STD_ON)
/**********************************************************************************************************************
 * J1939Tp_InternalMain_TxSdu()
 *********************************************************************************************************************/
/*! \brief        Cyclic handling of Tx SDUs.
 *  \details      Used for scheduling purposes and timeout supervision regarding Tx SDUs.
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
J1939TP_LOCAL_INLINE void J1939Tp_InternalMain_TxSdu(void);
#endif

#if (J1939TP_RXSDU == STD_ON)
/**********************************************************************************************************************
 *  J1939Tp_InternalMain_RxSdu()
 *********************************************************************************************************************/
/*! \brief        Cyclic handling of Rx SDUs.
 *  \details      Used for scheduling purposes and timeout supervision regarding Rx SDUs.
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
J1939TP_LOCAL_INLINE void J1939Tp_InternalMain_RxSdu(void);
#endif

#if (J1939TP_TX_ENABLED == STD_ON)
/**********************************************************************************************************************
 * J1939Tp_InternalTransmit()
 *********************************************************************************************************************/
/*! \brief        Forwards to the corresponding transport protocol function
 *  \details      This function decides which transport protocol has to be used to process the transmission request.
 *  \param[in]    txSduId     ID of the J1939Tp N-SDU to be transmitted.
 *  \param[in]    pduInfoPtr  Pointer to J1939Tp N-SDU structure.
 *  \return       E_NOT_OK    The transmit request failed.
 *  \return       E_OK        The transmit request has been accepted.
 *  \pre          The pduInfoPtr parameter and its field SduDataPtr must not be NULL.
 *  \context      TASK|ISR2
 *  \reentrant    TRUE
 *  \synchronous  TRUE
 *  \spec
 *    requires   txSduId < J1939Tp_GetSizeOfTxSdu();
 *  \endspec
 */
# if (J1939TP_INVALIDHNDOFTXSDU == STD_ON)
/*!
 *  \spec
 *    requires   !J1939Tp_IsInvalidHndOfTxSdu(txSduIdx);
 *  \endspec
 */
# endif
/*********************************************************************************************************************/
J1939TP_LOCAL_INLINE Std_ReturnType J1939Tp_InternalTransmit(PduIdType txSduId,
                                                             P2CONST(PduInfoType, AUTOMATIC,
                                                                     J1939TP_APPL_DATA) pduInfoPtr);
#endif

#if (J1939TP_RXPDU == STD_ON)
/**********************************************************************************************************************
 *  J1939Tp_InternalRxIndication()
 *********************************************************************************************************************/
/*! \brief        Forwards to the corresponding transport protocol function
 *  \details      This function decides which transport protocol has to be used to process the reception.
 *  \param[in]    RxPduId         ID of the received PDU.
 *  \param[in]    PduInfoPtr      Contains the length (SduLength) of the received PDU and a pointer to a buffer
 *                                (SduDataPtr) containing the PDU and the MetaData related to this PDU.
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    TRUE for different RxPduIds.
 *  \synchronous  TRUE
 *  \trace        SPEC-2167307
 *  \spec
 *    requires   RxPduId < J1939Tp_GetSizeOfRxPdu();
 *  \endspec
 */
# if (J1939TP_INVALIDHNDOFRXPDU == STD_ON)
/*!
 *  \spec
 *    requires   !J1939Tp_IsInvalidHndOfRxPdu(RxPduId);
 *  \endspec
 */
# endif
/*********************************************************************************************************************/
J1939TP_LOCAL_INLINE void J1939Tp_InternalRxIndication(PduIdType RxPduId,
                                                       P2CONST(PduInfoType, AUTOMATIC, J1939TP_APPL_DATA) PduInfoPtr);
#endif

#if (J1939TP_TXPDU == STD_ON)
/***********************************************************************************************************************
 *  J1939Tp_InternalTxConfirmation()
 *********************************************************************************************************************/
/*! \brief        Forwards to the corresponding transport protocol function
 *  \details      This function decides which transport protocol has to be used to process the confirmation.
 *  \param[in]    txPduId         ID of the PDU that has been transmitted.
 *  \param[in]    sduIdx          SDU index that is used to get the Tx SDU state.
 *  \param[in]    sduType         SDU type whose range is J1939TP_NSDU_CMDT_RX, J1939TP_NSDU_CMDT_TX, J1939TP_NSDU_ETP_TX,
 *                                J1939TP_NSDU_ETP_RX, J1939TP_NSDU_BAM
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    TRUE for different txPduIds.
 *  \synchronous  TRUE
 *********************************************************************************************************************/
J1939TP_LOCAL_INLINE void J1939Tp_InternalTxConfirmation(PduIdType txPduId, PduIdType sduIdx, J1939Tp_NSduType sduType);
#endif

#define J1939TP_STOP_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*lint -restore */
/*============================================== J1939TP_STOP_SEC_CODE ==============================================*/


/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/*============================================== J1939TP_START_SEC_CODE =============================================*/
#define J1939TP_START_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*lint -restore */

#if ((J1939TP_BAM_TX_ENABLED == STD_ON) || (J1939TP_CMDT_TX_ENABLED == STD_ON) || (J1939TP_ETP_TX_ENABLED == STD_ON))
/***********************************************************************************************************************
 *  J1939Tp_InternalGetPriority()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(uint8, J1939TP_CODE) J1939Tp_InternalGetPriority(PduIdType txSduIdx,
                                                      P2CONST(PduInfoType, AUTOMATIC, J1939TP_APPL_DATA) info)
{
  uint8 pri = J1939TP_DEFAULT_PRIORITY;

# if (J1939TP_TXVARPRIOFTXCHANNEL == STD_ON)
  J1939Tp_TxChannelChannelIdxOfTxSduType txChannelIdx = J1939Tp_GetTxChannelChannelIdxOfTxSdu(txSduIdx); 

  /* If variable priority is set for this channel. */
  if (J1939Tp_IsTxVarPriOfTxChannel(txChannelIdx)) 
  {
    J1939Tp_MetaDataLengthOfTxSduType mdl = J1939Tp_GetMetaDataLengthOfTxSdu(txSduIdx);

    /*
     * If MetaData consists of the priority (4 Byte), take this priority.
     * Otherwise take the configured priority of this channel.
     */
    if (mdl > J1939TP_MDL_PRI_POS)
    {
      pri = J1939Tp_MDL_Get_PRI(info->SduDataPtr[J1939TP_MDL_PRI_POS]);
    }
    else
    {
      pri = (J1939Tp_GetTxPriOfTxChannel(txChannelIdx) << 2);
    }
  }
# endif

  J1939TP_DUMMY_STATEMENT(txSduIdx); /* PRQA S 3112, 1338, 2983 */ /* MD_MSR_DummyStmt */
  J1939TP_DUMMY_STATEMENT(info); /* PRQA S 3112, 1338, 2983 */ /* MD_MSR_DummyStmt */

  return pri;
}
#endif

#if (J1939TP_FPP_TX_ENABLED == STD_ON)
/**********************************************************************************************************************
* J1939Tp_InternalMain_TxPduFpp()
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
J1939TP_LOCAL_INLINE void J1939Tp_InternalMain_TxPduFpp(PduIdType txSduIdx)
{
  J1939Tp_TxNSduStateType *txSduState = &J1939Tp_GetTxSduState(J1939Tp_GetTxSduStateIdxOfTxSdu(txSduIdx));

  /* If the state of the connection expects a confirmation of a first frame or an additional frame. */
  SchM_Enter_J1939Tp_J1939TP_EXCLUSIVE_AREA_TXNSDULOCK();
  if ((txSduState->State == J1939TP_STATE_FPP_FF_CONF) || (txSduState->State == J1939TP_STATE_FPP_AF_CONF))
  {
    /* Then inform the PduR about the missed confirmation and set its state to idle. */
    /* protected against late Tx confirmation */
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
#endif


#if ((J1939TP_BAM_TX_ENABLED == STD_ON) || (J1939TP_CMDT_ENABLED == STD_ON))
/**********************************************************************************************************************
* J1939Tp_InternalMain_TxPduTpCm()
**********************************************************************************************************************/
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
J1939TP_LOCAL_INLINE void J1939Tp_InternalMain_TxPduTpCm(PduIdType sduIdx, J1939Tp_NSduType sduType)
{
# if ((J1939TP_CMDT_RX_ENABLED == STD_ON) && ((J1939TP_BAM_TX_ENABLED == STD_ON) || (J1939TP_CMDT_TX_ENABLED == STD_ON)))
  /* If the connection management message is an Rx SDU of protocol type CMDT, */
  if (sduType == J1939TP_NSDU_CMDT_RX)
# endif
# if (J1939TP_CMDT_RX_ENABLED == STD_ON)
  {
    J1939Tp_RxNSduStateType *rxSduState = &J1939Tp_GetRxSduState(J1939Tp_GetRxSduStateIdxOfRxSdu(sduIdx));

    /* And if the connection state expects a confirmation either of a CTS, CTSWAIT, an EOMACK or an ABORT frame, */
    SchM_Enter_J1939Tp_J1939TP_EXCLUSIVE_AREA_RXNSDULOCK();
    if ((rxSduState->State == J1939TP_STATE_CMDT_CTS_CONF) || (rxSduState->State == J1939TP_STATE_CMDT_CTSWAIT_CONF) ||
        (rxSduState->State == J1939TP_STATE_CMDT_EOMACK_CONF) || (rxSduState->State == J1939TP_STATE_CMDT_ABORT_CONF))
    {
      /* If the connection is in a valid session, then inform the PduR about the missed indication and set its state to
         idle. */
      /* protected against late Tx confirmation */
      rxSduState->State = J1939TP_STATE_FINISH; /* VCA_J1939TP_RXSDUSTATE_VIA_RXSDU_CSL03 */
      SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_RXNSDULOCK();

      if (rxSduState->InSession == TRUE)
      {
        /*! \trace SPEC-2167305 */
        PduR_J1939TpRxIndication(J1939Tp_GetSduIdOfRxSdu(sduIdx), E_NOT_OK); 
      }

      /* no protection required - transition from uninterruptible state */
      rxSduState->State = J1939TP_STATE_IDLE; /* VCA_J1939TP_RXSDUSTATE_VIA_RXSDU_CSL03 */
    }
    else
    {
      SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_RXNSDULOCK();
    }
  }
# endif
# if ((J1939TP_CMDT_RX_ENABLED == STD_ON) && ((J1939TP_BAM_TX_ENABLED == STD_ON) || (J1939TP_CMDT_TX_ENABLED == STD_ON)))
  else /* (sduType == J1939TP_NSDU_CMDT_TX) || (sduType == J1939TP_NSDU_BAM) */
# endif
# if ((J1939TP_BAM_TX_ENABLED == STD_ON) || (J1939TP_CMDT_TX_ENABLED == STD_ON))
  {
    /* Otherwise the connection management message is a Tx SDU either of protocol BAM or CMDT. */
    J1939Tp_TxNSduStateType *txSduState = &J1939Tp_GetTxSduState(J1939Tp_GetTxSduStateIdxOfTxSdu(sduIdx));

    /* And if the connection state expects a confirmation either of a BAM, an RTS or an ABORT frame, */
    SchM_Enter_J1939Tp_J1939TP_EXCLUSIVE_AREA_TXNSDULOCK();
    if ((txSduState->State == J1939TP_STATE_BAM_BAM_CONF) || (txSduState->State == J1939TP_STATE_CMDT_RTS_CONF) ||
        (txSduState->State == J1939TP_STATE_CMDT_ABORT_CONF))
    {
      /* Then inform the PduR about the missed confirmation and set its state to idle. */
      /* protected against late Tx confirmation */
      txSduState->State = J1939TP_STATE_FINISH; /* VCA_J1939TP_TXSDUSTATE_VIA_TXSDU_CSL03 */
      SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_TXNSDULOCK();

      /*! \trace SPEC-2167303 */
      PduR_J1939TpTxConfirmation(J1939Tp_GetSduIdOfTxSdu(sduIdx), E_NOT_OK); 

      /* no protection required - transition from uninterruptible state */
      txSduState->State = J1939TP_STATE_IDLE; /* VCA_J1939TP_TXSDUSTATE_VIA_TXSDU_CSL03 */
    }
    else
    {
      SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_TXNSDULOCK();
    }
  }
# endif

  J1939TP_DUMMY_STATEMENT(sduType); /* PRQA S 3112, 1338, 2983 */ /* MD_MSR_DummyStmt */
}
#endif


#if ((J1939TP_BAM_TX_ENABLED == STD_ON) || (J1939TP_CMDT_TX_ENABLED == STD_ON))
/**********************************************************************************************************************
* J1939Tp_InternalMain_TxPduTpDt()
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
J1939TP_LOCAL_INLINE void J1939Tp_InternalMain_TxPduTpDt(PduIdType txSduIdx)
{
  J1939Tp_TxNSduStateType *txSduState = &J1939Tp_GetTxSduState(J1939Tp_GetTxSduStateIdxOfTxSdu(txSduIdx));

  /* If the state of the connection expects a confirmation of a data frame of BAM or CMDT, */
  SchM_Enter_J1939Tp_J1939TP_EXCLUSIVE_AREA_TXNSDULOCK();
  if ((txSduState->State == J1939TP_STATE_BAM_DATA_CONF) || (txSduState->State == J1939TP_STATE_CMDT_DATA_CONF))
  {
    /* Then inform the PduR about the missed confirmation and set its state to idle. */
    /* protected against late Tx confirmation */
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
#endif


#if (J1939TP_ETP_ENABLED == STD_ON)
/**********************************************************************************************************************
* J1939Tp_InternalMain_TxPduEtpCm()
**********************************************************************************************************************/
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
J1939TP_LOCAL_INLINE void J1939Tp_InternalMain_TxPduEtpCm(PduIdType sduIdx, J1939Tp_NSduType sduType)
{
# if ((J1939TP_ETP_RX_ENABLED == STD_ON) && (J1939TP_ETP_TX_ENABLED == STD_ON))
  /* If the connection management message is an Rx SDU of protocol type ETP, */
  if (sduType == J1939TP_NSDU_ETP_RX)
# endif
# if (J1939TP_ETP_RX_ENABLED == STD_ON)
  {
    J1939Tp_RxNSduStateType *rxSduState = &J1939Tp_GetRxSduState(J1939Tp_GetRxSduStateIdxOfRxSdu(sduIdx));

    /* And if the connection state expects a confirmation either of a CTS, CTSWAIT, an EOMACK or an ABORT frame, */
    SchM_Enter_J1939Tp_J1939TP_EXCLUSIVE_AREA_RXNSDULOCK();
    if ((rxSduState->State == J1939TP_STATE_ETP_CTS_CONF) ||
        (rxSduState->State == J1939TP_STATE_ETP_CTSWAIT_CONF) ||
        (rxSduState->State == J1939TP_STATE_ETP_EOMACK_CONF) || (rxSduState->State == J1939TP_STATE_ETP_ABORT_CONF))
    {
      /* If the connection is in a valid session, then inform the PduR about the missed indication and set its state to
         idle. */
      /* protected against late Tx confirmation */
      rxSduState->State = J1939TP_STATE_FINISH; /* VCA_J1939TP_RXSDUSTATE_VIA_RXSDU_CSL03 */
      SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_RXNSDULOCK();

      if (rxSduState->InSession == TRUE)
      {
        /*! \trace SPEC-2167305 */
        PduR_J1939TpRxIndication(J1939Tp_GetSduIdOfRxSdu(sduIdx), E_NOT_OK);      
      }

      /* no protection required - transition from uninterruptible state */
      rxSduState->State = J1939TP_STATE_IDLE; /* VCA_J1939TP_RXSDUSTATE_VIA_RXSDU_CSL03 */
    }
    else
    {
      SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_RXNSDULOCK();
    }
  }
# endif
# if ((J1939TP_ETP_RX_ENABLED == STD_ON) && (J1939TP_ETP_TX_ENABLED == STD_ON))
  else /* sduType == J1939TP_NSDU_ETP_TX */
# endif
# if (J1939TP_ETP_TX_ENABLED == STD_ON)
  {
    /* Otherwise the connection management message is a Tx SDU. */
    J1939Tp_TxNSduStateType *txSduState = &J1939Tp_GetTxSduState(J1939Tp_GetTxSduStateIdxOfTxSdu(sduIdx));

    /* And if the connection state expects a confirmation either of an RTS, a DPO or an ABORT frame, */
    SchM_Enter_J1939Tp_J1939TP_EXCLUSIVE_AREA_TXNSDULOCK();
    if ((txSduState->State == J1939TP_STATE_ETP_RTS_CONF) ||
        (txSduState->State == J1939TP_STATE_ETP_DPO_CONF) || (txSduState->State == J1939TP_STATE_ETP_ABORT_CONF))
    {
      /* Then inform the PduR about the missed confirmation and set its state to idle. */
      /* protected against late Tx confirmation */
      txSduState->State = J1939TP_STATE_FINISH; /* VCA_J1939TP_TXSDUSTATE_VIA_TXSDU_CSL03 */
      SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_TXNSDULOCK();

      /*! \trace SPEC-2167303 */
      PduR_J1939TpTxConfirmation(J1939Tp_GetSduIdOfTxSdu(sduIdx), E_NOT_OK); 

      /* no protection required - transition from uninterruptible state */
      txSduState->State = J1939TP_STATE_IDLE; /* VCA_J1939TP_TXSDUSTATE_VIA_TXSDU_CSL03 */
    }
    else
    {
      SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_TXNSDULOCK();
    }
  }
# endif

  J1939TP_DUMMY_STATEMENT(sduType); /* PRQA S 3112, 1338, 2983 */ /* MD_MSR_DummyStmt */
}
#endif


#if (J1939TP_ETP_TX_ENABLED == STD_ON)
/**********************************************************************************************************************
* J1939Tp_InternalMain_TxPduEtpDt()
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
J1939TP_LOCAL_INLINE void J1939Tp_InternalMain_TxPduEtpDt(PduIdType txSduIdx)
{
  J1939Tp_TxNSduStateType *txSduState = &J1939Tp_GetTxSduState(J1939Tp_GetTxSduStateIdxOfTxSdu(txSduIdx));

  /* If the state of the connection expects a confirmation of an ETP data frame, */
  SchM_Enter_J1939Tp_J1939TP_EXCLUSIVE_AREA_TXNSDULOCK();
  if (txSduState->State == J1939TP_STATE_ETP_DATA_CONF)
  {
    /* Then inform the PduR about the missed confirmation and set its state to idle. */
    /* protected against late Tx confirmation */
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
#endif


#if (J1939TP_DIRECT_TX_ENABLED == STD_ON)
/**********************************************************************************************************************
* J1939Tp_InternalMain_TxPduDirect()
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
J1939TP_LOCAL_INLINE void J1939Tp_InternalMain_TxPduDirect(PduIdType txSduIdx)
{
  J1939Tp_TxNSduStateType *txSduState = &J1939Tp_GetTxSduState(J1939Tp_GetTxSduStateIdxOfTxSdu(txSduIdx));

  /* If the state of the connection expects a confirmation of a direct data frame, */
  SchM_Enter_J1939Tp_J1939TP_EXCLUSIVE_AREA_TXNSDULOCK();
  if (txSduState->State == J1939TP_STATE_DIRECT_CONF)
  {
    /* Then inform the PduR about the missed confirmation and set its state to idle. */
    /* protected against late Tx confirmation */
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
#endif


#if (J1939TP_TXPDU == STD_ON)
/**********************************************************************************************************************
* J1939Tp_InternalMain_TxPdu()
**********************************************************************************************************************/
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
 */
J1939TP_LOCAL_INLINE void J1939Tp_InternalMain_TxPdu(void)
{
  J1939Tp_SizeOfTxPduType txPduIdx;

  /* Iterate over all Tx PDUs. */
  for (txPduIdx = 0; txPduIdx < J1939Tp_GetSizeOfTxPdu(); txPduIdx++)
  {
# if (J1939TP_INVALIDHNDOFTXPDU == STD_ON)
    if (!J1939Tp_IsInvalidHndOfTxPdu(txPduIdx))
# endif
    {
      J1939Tp_TxNPduStateType *txPduState = &J1939Tp_GetTxPduState(J1939Tp_GetTxPduStateIdxOfTxPdu(txPduIdx));

      /* If the Tx PDU is in use */
      SchM_Enter_J1939Tp_J1939TP_EXCLUSIVE_AREA_TXNPDULOCK();
      if (txPduState->Locked == TRUE)
      {
        --txPduState->ConfTimeout;  /* VCA_J1939TP_TXPDUSTATE_VIA_TXPDU_CSL03 */
        /* and its confirmation time is elapsed, */
        if (txPduState->ConfTimeout == 0u)
        {
          PduIdType sduIdx = txPduState->CurrentNSduId;
# if ((J1939TP_BAM_TX_ENABLED == STD_ON) || (J1939TP_CMDT_ENABLED == STD_ON) || (J1939TP_ETP_ENABLED == STD_ON))
          J1939Tp_NSduType sduType = txPduState->CurrentNSduType;
# endif

          /* protected against concurrent Tx confirmation */
          txPduState->Locked = FALSE;
          SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_TXNPDULOCK();

          J1939Tp_ReportRuntimeError(J1939TP_SID_MAINFUNCTION, J1939TP_E_TIMEOUT_TXCONF);

          /* then determine the type of the Tx PDU. */
          switch (J1939Tp_GetPduTypeOfTxPdu(txPduIdx))
          {
# if (J1939TP_FPP_TX_ENABLED == STD_ON)
          case J1939TP_FPP_PDUTYPEOFTXPDU:
            /* Process the FPP Tx PDU. */
            J1939Tp_InternalMain_TxPduFpp(sduIdx);
            break;
# endif

# if ((J1939TP_BAM_TX_ENABLED == STD_ON) || (J1939TP_CMDT_ENABLED == STD_ON))
          case J1939TP_TPCM_PDUTYPEOFTXPDU:
            /* Process the connection management PDU of transport protocol BAM or CMDT. */
            J1939Tp_InternalMain_TxPduTpCm(sduIdx, sduType);
            break;
# endif

# if ((J1939TP_BAM_TX_ENABLED == STD_ON) || (J1939TP_CMDT_TX_ENABLED == STD_ON))
          case J1939TP_TPDT_PDUTYPEOFTXPDU:
            /* Process the data transfer PDU of transport protocol BAM or CMDT. */
            J1939Tp_InternalMain_TxPduTpDt(sduIdx);
            break;
# endif

# if (J1939TP_ETP_ENABLED == STD_ON)
          case J1939TP_ETPCM_PDUTYPEOFTXPDU:
            /* Process the connection management PDU of transport protocol ETP. */
            J1939Tp_InternalMain_TxPduEtpCm(sduIdx, sduType);
            break;
# endif

# if (J1939TP_ETP_TX_ENABLED == STD_ON)
          case J1939TP_ETPDT_PDUTYPEOFTXPDU:
            /* Process the data transfer PDU of transport protocol ETP. */
            J1939Tp_InternalMain_TxPduEtpDt(sduIdx);
            break;
# endif

# if (J1939TP_DIRECT_TX_ENABLED == STD_ON)
          case J1939TP_DIRECT_PDUTYPEOFTXPDU:
            /* Process the direct Tx PDU. */
            J1939Tp_InternalMain_TxPduDirect(sduIdx);
            break;
# endif

          default: /* COV_J1939TP_SWITCHCASE_DEFAULT */
            break; /* MISRA */
          }
        }
        else
        {
          SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_TXNPDULOCK();
        }
      }
      else
      {
        SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_TXNPDULOCK();
      }
    }
  }
} /* J1939Tp_InternalMain_TxPdu */ /* PRQA S 6030, 6050, 6080 */ /* MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */
#endif


#if (J1939TP_TXSDU == STD_ON)
/**********************************************************************************************************************
* J1939Tp_InternalMain_TxSdu()
**********************************************************************************************************************/
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
 */
J1939TP_LOCAL_INLINE void J1939Tp_InternalMain_TxSdu(void)
{
  J1939Tp_SizeOfTxSduType txSduIdx;

  /* Iterate over all Tx SDUs. */
  for (txSduIdx = 0; txSduIdx < J1939Tp_GetSizeOfTxSdu(); txSduIdx++)
  {
    /*assert txSduIdx < J1939Tp_GetSizeOfTxSdu(); */
# if (J1939TP_INVALIDHNDOFTXSDU == STD_ON)
    if (!J1939Tp_IsInvalidHndOfTxSdu(txSduIdx))
# endif
    {
      const J1939Tp_TxNSduStateType *txSduState = &J1939Tp_GetTxSduState(J1939Tp_GetTxSduStateIdxOfTxSdu(txSduIdx));

# if (J1939TP_FPP_TX_ENABLED == STD_ON)
      /* If transport protocol is Fast Packet Protocol and the connection is not in a confirmation state, then process
         the FPP Tx SDU. */
      if (((txSduState->State & J1939TP_STATEMASK_FPP) != J1939TP_STATE_IDLE) &&
          ((txSduState->State & J1939TP_STATEMASK_CONF) == J1939TP_STATE_IDLE))
      {
        J1939Tp_FppTxMain(txSduIdx);
      }
# endif
# if ((J1939TP_FPP_TX_ENABLED == STD_ON) && ((J1939TP_BAM_TX_ENABLED == STD_ON) || (J1939TP_CMDT_TX_ENABLED == STD_ON) || (J1939TP_ETP_TX_ENABLED == STD_ON) || (J1939TP_DIRECT_TX_ENABLED == STD_ON)))
      else
# endif
# if ((J1939TP_BAM_TX_ENABLED == STD_ON) || (J1939TP_CMDT_TX_ENABLED == STD_ON) || (J1939TP_ETP_TX_ENABLED == STD_ON) || (J1939TP_DIRECT_TX_ENABLED == STD_ON))
      {
# endif
# if (J1939TP_BAM_TX_ENABLED == STD_ON)
        /* If transport protocol is Broadcast Announce Message and the connection is not in a confirmation state, then
           process the BAM Tx SDU. */
        if (((txSduState->State & J1939TP_STATEMASK_BAM) != J1939TP_STATE_IDLE) &&
            ((txSduState->State & J1939TP_STATEMASK_CONF) == J1939TP_STATE_IDLE))
        {
          J1939Tp_BamTxMain(txSduIdx);
        }
# endif
# if ((J1939TP_BAM_TX_ENABLED == STD_ON) && ((J1939TP_CMDT_TX_ENABLED == STD_ON) || (J1939TP_ETP_TX_ENABLED == STD_ON) || (J1939TP_DIRECT_TX_ENABLED == STD_ON)))
        else
# endif
# if ((J1939TP_CMDT_TX_ENABLED == STD_ON) || (J1939TP_ETP_TX_ENABLED == STD_ON) || (J1939TP_DIRECT_TX_ENABLED == STD_ON))
        {
# endif
# if (J1939TP_CMDT_TX_ENABLED == STD_ON)
          /* If transport protocol is Connection Mode Data Transfer and the connection is not in a confirmation state,
             then process the CMDT Tx SDU. */
          if (((txSduState->State & J1939TP_STATEMASK_CMDT) != J1939TP_STATE_IDLE) &&
              ((txSduState->State & J1939TP_STATEMASK_CONF) == J1939TP_STATE_IDLE))
          {
            J1939Tp_CmdtTxMain(txSduIdx);
          }
# endif
# if ((J1939TP_CMDT_TX_ENABLED == STD_ON) && ((J1939TP_ETP_TX_ENABLED == STD_ON) || (J1939TP_DIRECT_TX_ENABLED == STD_ON)))
          else
# endif
# if ((J1939TP_ETP_TX_ENABLED == STD_ON) || (J1939TP_DIRECT_TX_ENABLED == STD_ON))
          {
# endif
# if (J1939TP_ETP_TX_ENABLED == STD_ON)
            /* If transport protocol is Extended Transport Protocol and the connection is not in a confirmation state,
               then process the ETP Tx SDU. */
            if (((txSduState->State & J1939TP_STATEMASK_ETP) != J1939TP_STATE_IDLE) &&
                ((txSduState->State & J1939TP_STATEMASK_CONF) == J1939TP_STATE_IDLE))
            {
              J1939Tp_EtpTxMain(txSduIdx);
            }
# endif
# if ((J1939TP_ETP_TX_ENABLED == STD_ON) && (J1939TP_DIRECT_TX_ENABLED == STD_ON))
            else
# endif
# if (J1939TP_DIRECT_TX_ENABLED == STD_ON)
            {
              /* If it is a direct message and the connection is not in a confirmation state, then process the direct
                 Tx SDU. */
              if (((txSduState->State & J1939TP_STATEMASK_DIRECT) != J1939TP_STATE_IDLE) &&
                  ((txSduState->State & J1939TP_STATEMASK_CONF) == J1939TP_STATE_IDLE))
              {
                J1939Tp_DirectTxMain(txSduIdx);
              }
            }
# endif
# if ((J1939TP_ETP_TX_ENABLED == STD_ON) || (J1939TP_DIRECT_TX_ENABLED == STD_ON))
          }
# endif
# if ((J1939TP_CMDT_TX_ENABLED == STD_ON) || (J1939TP_ETP_TX_ENABLED == STD_ON) || (J1939TP_DIRECT_TX_ENABLED == STD_ON))
        }
# endif
# if ((J1939TP_BAM_TX_ENABLED == STD_ON) || (J1939TP_CMDT_TX_ENABLED == STD_ON) || (J1939TP_ETP_TX_ENABLED == STD_ON) || (J1939TP_DIRECT_TX_ENABLED == STD_ON))
      }
# endif
    }
  }
} /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif


#if (J1939TP_RXSDU == STD_ON)
/**********************************************************************************************************************
*  J1939Tp_InternalMain_RxSdu()
**********************************************************************************************************************/
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
J1939TP_LOCAL_INLINE void J1939Tp_InternalMain_RxSdu(void)
{
  J1939Tp_SizeOfRxSduType rxSduIdx;

  /* Iterate over all Rx SDUs. */
  for (rxSduIdx = 0; rxSduIdx < J1939Tp_GetSizeOfRxSdu(); rxSduIdx++)
  {
# if (J1939TP_INVALIDHNDOFRXSDU == STD_ON)
    if (!J1939Tp_IsInvalidHndOfRxSdu(rxSduIdx))
# endif
    {
      const J1939Tp_RxNSduStateType *rxSduState = &J1939Tp_GetRxSduState(J1939Tp_GetRxSduStateIdxOfRxSdu(rxSduIdx));

# if (J1939TP_FPP_RX_ENABLED == STD_ON)
      /* If transport protocol is Fast Packet Protocol, then process the FPP Rx SDU. */
      if ((rxSduState->State & J1939TP_STATEMASK_FPP) != J1939TP_STATE_IDLE)
      {
        J1939Tp_FppRxMain(rxSduIdx);
      }
# endif
# if ((J1939TP_FPP_RX_ENABLED == STD_ON) && ((J1939TP_BAM_RX_ENABLED == STD_ON) || (J1939TP_CMDT_RX_ENABLED == STD_ON) || (J1939TP_ETP_RX_ENABLED == STD_ON)))
      else
# endif
# if ((J1939TP_BAM_RX_ENABLED == STD_ON) || (J1939TP_CMDT_RX_ENABLED == STD_ON) || (J1939TP_ETP_RX_ENABLED == STD_ON))
      {
# endif
# if (J1939TP_BAM_RX_ENABLED == STD_ON)
        /* If transport protocol is Broadcast Announce Message, then process the BAM Rx SDU. */
        if ((rxSduState->State & J1939TP_STATEMASK_BAM) != J1939TP_STATE_IDLE)
        {
          J1939Tp_BamRxMain(rxSduIdx);
        }
# endif
# if ((J1939TP_BAM_RX_ENABLED == STD_ON) && ((J1939TP_CMDT_RX_ENABLED == STD_ON) || (J1939TP_ETP_RX_ENABLED == STD_ON)))
        else
# endif
# if ((J1939TP_CMDT_RX_ENABLED == STD_ON) || (J1939TP_ETP_RX_ENABLED == STD_ON))
        {
# endif
# if (J1939TP_CMDT_RX_ENABLED == STD_ON)
          /* If transport protocol is Connection Mode Data Transfer and the connection is not in a confirmation state,
             then process the CMDT Rx SDU. */
          if (((rxSduState->State & J1939TP_STATEMASK_CMDT) != J1939TP_STATE_IDLE) &&
              ((rxSduState->State & J1939TP_STATEMASK_CONF) == J1939TP_STATE_IDLE))
          {
            J1939Tp_CmdtRxMain(rxSduIdx);
          }
# endif
# if ((J1939TP_CMDT_RX_ENABLED == STD_ON) && (J1939TP_ETP_RX_ENABLED == STD_ON))
          else
# endif
# if (J1939TP_ETP_RX_ENABLED == STD_ON)
          {
            /* If transport protocol is Extended Transport Protocol and the connection is not in a confirmation state,
               then process the ETP Rx SDU. */
            if (((rxSduState->State & J1939TP_STATEMASK_ETP) != J1939TP_STATE_IDLE) &&
                ((rxSduState->State & J1939TP_STATEMASK_CONF) == J1939TP_STATE_IDLE))
            {
              J1939Tp_EtpRxMain(rxSduIdx);
            }
          }
# endif
# if ((J1939TP_CMDT_RX_ENABLED == STD_ON) || (J1939TP_ETP_RX_ENABLED == STD_ON))
        }
# endif
# if ((J1939TP_BAM_RX_ENABLED == STD_ON) || (J1939TP_CMDT_RX_ENABLED == STD_ON) || (J1939TP_ETP_RX_ENABLED == STD_ON))
      }
# endif
    }
  }
} /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif


#if (J1939TP_TX_ENABLED == STD_ON)
/**********************************************************************************************************************
*  J1939Tp_InternalTransmit()
**********************************************************************************************************************/
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
J1939TP_LOCAL_INLINE Std_ReturnType J1939Tp_InternalTransmit(PduIdType txSduId,
                                P2CONST(PduInfoType, AUTOMATIC, J1939TP_APPL_DATA) pduInfoPtr)
{
  J1939Tp_TxChannelChannelIdxOfTxSduType txChannelIdx = J1939Tp_GetTxChannelChannelIdxOfTxSdu(txSduId);
  Std_ReturnType result;

  /* Decide which transport protocol has to be used for the transmission. */
# if ((J1939TP_FPP_TX_ENABLED == STD_ON) && ((J1939TP_BAM_TX_ENABLED == STD_ON) || (J1939TP_CMDT_TX_ENABLED == STD_ON) || (J1939TP_ETP_TX_ENABLED == STD_ON)))
  /* If the protocol type is FPP */
  if (J1939Tp_GetTxProtocolTypeOfTxChannel(txChannelIdx) == J1939TP_PROTOCOL_FPP_TXPROTOCOLTYPEOFTXCHANNEL)
# endif
# if (J1939TP_FPP_TX_ENABLED == STD_ON)
  {
    /* Forward the transmission request to the transmit function of FPP. */
    result = J1939Tp_FppTransmit(txSduId, pduInfoPtr); /* VCA_J1939TP_EXCLUDE_FPP_ETP */
  }
# endif
# if ((J1939TP_FPP_TX_ENABLED == STD_ON) && ((J1939TP_BAM_TX_ENABLED == STD_ON) || (J1939TP_CMDT_TX_ENABLED == STD_ON) || (J1939TP_ETP_TX_ENABLED == STD_ON)))
  /* Otherwise */
  else
# endif
# if ((J1939TP_BAM_TX_ENABLED == STD_ON) || (J1939TP_CMDT_TX_ENABLED == STD_ON) || (J1939TP_ETP_TX_ENABLED == STD_ON))
  {
#  if (J1939TP_DIRECT_TX_ENABLED == STD_ON)
    /* If message length exceeds one CAN message. */
    if ((!J1939Tp_IsIsVariableOfTxSdu(txSduId)) || (pduInfoPtr->SduLength > 8u)) 
#  endif
    {
#  if ((J1939TP_BAM_TX_ENABLED == STD_ON) && ((J1939TP_CMDT_TX_ENABLED == STD_ON) || (J1939TP_ETP_TX_ENABLED == STD_ON)))
      /* If the protocol type is BAM or undefined and destination address is broadcast. */
      if ((J1939Tp_GetTxProtocolTypeOfTxChannel(txChannelIdx) == J1939TP_PROTOCOL_BAM_TXPROTOCOLTYPEOFTXCHANNEL) ||     /* COV_J1939TP_UNUSED_TX_PROTOCOL */
          ((J1939Tp_GetTxProtocolTypeOfTxChannel(txChannelIdx) == J1939TP_PROTOCOL_UNUSED_TXPROTOCOLTYPEOFTXCHANNEL) && /* COV_J1939TP_UNUSED_TX_PROTOCOL */
           (pduInfoPtr->SduDataPtr[J1939TP_MDL_DA_POS] == J1939TP_BROADCAST_ADDRESS)))/* COV_J1939TP_UNUSED_TX_PROTOCOL */
#  endif
#  if (J1939TP_BAM_TX_ENABLED == STD_ON)
      {
        /* Then forward the transmission request to the transmit function of BAM. */
        result = J1939Tp_BamTransmit(txSduId, pduInfoPtr);
      }
#  endif
#  if ((J1939TP_BAM_TX_ENABLED == STD_ON) && ((J1939TP_CMDT_TX_ENABLED == STD_ON) || (J1939TP_ETP_TX_ENABLED == STD_ON)))
      /* Otherwise */
      else
#  endif
#  if ((J1939TP_CMDT_TX_ENABLED == STD_ON) || (J1939TP_ETP_TX_ENABLED == STD_ON))
      {
#  endif
#  if ((J1939TP_CMDT_TX_ENABLED == STD_ON) && (J1939TP_ETP_TX_ENABLED == STD_ON))
        /* If the message can be send by CMDT protocol. */
        if (pduInfoPtr->SduLength <= J1939TP_MAX_LENGTH)
#  endif
#  if (J1939TP_CMDT_TX_ENABLED == STD_ON)
        {
          /* Then forward the transmission request to the transmit function of CMDT. */
          result = J1939Tp_CmdtTransmit(txSduId, pduInfoPtr);
        }
#  endif
#  if ((J1939TP_CMDT_TX_ENABLED == STD_ON) && (J1939TP_ETP_TX_ENABLED == STD_ON))
        /* Otherwise */
        else
#  endif
#  if (J1939TP_ETP_TX_ENABLED == STD_ON)
        {
          /* Forward the transmission request to the transmit function of ETP. */
          result = J1939Tp_EtpTransmit(txSduId, pduInfoPtr); /* VCA_J1939TP_EXCLUDE_FPP_ETP */
        }
#  endif
#  if ((J1939TP_CMDT_TX_ENABLED == STD_ON) || (J1939TP_ETP_TX_ENABLED == STD_ON))
      }
#  endif
    }
#  if (J1939TP_DIRECT_TX_ENABLED == STD_ON)
    /* Otherwise the message fits into one CAN message. */
    else
    {
      /* Directly transmit the message. */
      result = J1939Tp_DirectTransmit(txSduId, pduInfoPtr);
    }
#  endif
  }
# endif

  J1939TP_DUMMY_STATEMENT(txChannelIdx); /* PRQA S 3112, 1338, 2983 */ /* MD_MSR_DummyStmt */

  /* Return the result of the request. */
  return result;
}
#endif


#if (J1939TP_RXPDU == STD_ON)
/**********************************************************************************************************************
 *  J1939Tp_InternalRxIndication()
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
 */
J1939TP_LOCAL_INLINE void J1939Tp_InternalRxIndication(PduIdType RxPduId,
                                                       P2CONST(PduInfoType, AUTOMATIC, J1939TP_APPL_DATA) PduInfoPtr)
{
  /* If the payload length exceeds the MetaData length. */
  if (PduInfoPtr->SduLength > J1939TP_MDL_SIZE)
  {
    /* Calculate the real PDU length. */
    PduLengthType pduLen = PduInfoPtr->SduLength - J1939TP_MDL_SIZE;
    /* Extract the source address of the MetaData. */
    /* PRQA S 2985 1 */ /* MD_J1939Tp_2.2 */ 
    uint8 sa = PduInfoPtr->SduDataPtr[pduLen + J1939TP_MDL_SA_POS];

    /* If the source address is invalid */
    if (!J1939Tp_SA_Valid(sa))
    {
      /* Then report the runtime error of an invalid source address. */
      /*! \trace SPEC-2167310 */
      J1939Tp_ReportRuntimeError(J1939TP_SID_RXINDICATION, J1939TP_E_INVALID_SA);
    }
    /* Otherwise the source address is valid. */
    else
    {
      /* Then determine the type of the PDU. */
      J1939Tp_PduTypeOfRxPduType pduType = J1939Tp_GetPduTypeOfRxPdu(RxPduId); 
      switch (pduType)
      {
# if (J1939TP_FPP_RX_ENABLED == STD_ON)
        /* If the PDU type is FPP. */
      case J1939TP_FPP_PDUTYPEOFRXPDU:
        /* Then forward the reception indication to the receive function of FPP. */
        J1939Tp_FppRxIndication(RxPduId, PduInfoPtr, sa); /* VCA_J1939TP_EXCLUDE_FPP_ETP */
        break;
# endif

# if ((J1939TP_BAM_RX_ENABLED == STD_ON) || (J1939TP_CMDT_ENABLED == STD_ON))
        /* If the PDU type is a Connection Management or a Data frame. */
      case J1939TP_TPCM_PDUTYPEOFRXPDU:
#  if ((J1939TP_BAM_RX_ENABLED == STD_ON) || (J1939TP_CMDT_RX_ENABLED == STD_ON))
      case J1939TP_TPDT_PDUTYPEOFRXPDU:
#  endif
      {
        /* Then extract the destination address from the MetaData. */
        uint8 da = PduInfoPtr->SduDataPtr[pduLen + J1939TP_MDL_DA_POS];

#  if ((J1939TP_BAM_RX_ENABLED == STD_ON) && (J1939TP_CMDT_ENABLED == STD_ON))
        /* If the destination address is the broadcast address. */
        if (da == J1939TP_BROADCAST_ADDRESS)
#  endif
#  if (J1939TP_BAM_RX_ENABLED == STD_ON)
        {
          /* Then forward the reception indication to the receive function of BAM. */
          J1939Tp_BamRxIndication(RxPduId, PduInfoPtr, pduType, sa, da);
        }
#  endif
#  if ((J1939TP_BAM_RX_ENABLED == STD_ON) && (J1939TP_CMDT_ENABLED == STD_ON))
        /* Otherwise */
        else
#  endif
#  if (J1939TP_CMDT_ENABLED == STD_ON)
        {
          /* Forward the reception indication to the receive function of CMDT. */
          J1939Tp_CmdtRxIndication(RxPduId, PduInfoPtr, pduType, sa, da);
        }
#  endif
      }
        break;
# endif

# if (J1939TP_ETP_ENABLED == STD_ON)
        /* If the PDU type is an Extended Connection Management or an Extended Data frame. */
      case J1939TP_ETPCM_PDUTYPEOFRXPDU:
#  if (J1939TP_ETP_RX_ENABLED == STD_ON)
      case J1939TP_ETPDT_PDUTYPEOFRXPDU:
#  endif
        /* Then forward the reception indication to the receive function of ETP. */
        J1939Tp_EtpRxIndication(RxPduId, PduInfoPtr, pduType, sa); /* VCA_J1939TP_EXCLUDE_FPP_ETP */
        break;
# endif

# if (J1939TP_DIRECT_RX_ENABLED == STD_ON)
        /* If the PDU type is DIRECT. */
      case J1939TP_DIRECT_PDUTYPEOFRXPDU:
        /* Then forward the reception indication to the receive function of DIRECT. */
        J1939Tp_DirectRxIndication(RxPduId, PduInfoPtr, sa);
        break;
# endif

      default: /* COV_J1939TP_SWITCHCASE_DEFAULT */
        /*! \trace SPEC-2167354 */
        break; /* MISRA */
      }
    }
  }
# if (J1939TP_RUNTIME_ERROR_REPORT == STD_ON)
  /* Otherwise if RuntimeErrorReporting is enabled */
  else
  {
    /* Report the runtime error of an invalid Data Length Code. */
    J1939Tp_ReportRuntimeError(J1939TP_SID_RXINDICATION, J1939TP_E_INVALID_DLC);
  }
# endif
}
#endif


#if (J1939TP_TXPDU == STD_ON)
/***********************************************************************************************************************
 *  J1939Tp_InternalTxConfirmation()
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
 */
J1939TP_LOCAL_INLINE void J1939Tp_InternalTxConfirmation(PduIdType txPduId, PduIdType sduIdx, J1939Tp_NSduType sduType)
{
  /* Determine the type of the PDU */
  switch (J1939Tp_GetPduTypeOfTxPdu(txPduId))
  {
# if (J1939TP_FPP_TX_ENABLED == STD_ON)
    /* If the PDU type is FPP. */
  case J1939TP_FPP_PDUTYPEOFTXPDU:
  {
    const J1939Tp_TxNSduStateType *txSduState = &J1939Tp_GetTxSduState(J1939Tp_GetTxSduStateIdxOfTxSdu(sduIdx));

    /* And the state is not IDLE */
    if ((txSduState->State & J1939TP_STATEMASK_FPP) != J1939TP_STATE_IDLE)
    {
      /* Then forward the confirmation to the confirmation function of FPP. */
      J1939Tp_FppTxConfirmation(sduIdx);
    }
  }
    break;
# endif

# if ((J1939TP_BAM_TX_ENABLED == STD_ON) || (J1939TP_CMDT_ENABLED == STD_ON))
    /* If the PDU type is a Connection Management frame. */
  case J1939TP_TPCM_PDUTYPEOFTXPDU:
#  if ((J1939TP_BAM_TX_ENABLED == STD_ON) && (J1939TP_CMDT_ENABLED == STD_ON))
    /* And if the N-SDU is from type BAM. */
    if (sduType == J1939TP_NSDU_BAM)
#  endif
#  if (J1939TP_BAM_TX_ENABLED == STD_ON)
    {
      const J1939Tp_TxNSduStateType *txSduState = &J1939Tp_GetTxSduState(J1939Tp_GetTxSduStateIdxOfTxSdu(sduIdx));

      /* And the state is not IDLE */
      if ((txSduState->State & J1939TP_STATEMASK_BAM) != J1939TP_STATE_IDLE)
      {
        /* Then forward the confirmation to the confirmation function of BAM. */
        J1939Tp_BamTxConfirmation(sduIdx, J1939TP_TPCM_PDUTYPEOFTXPDU);
      }
    }
#  endif
#  if ((J1939TP_BAM_TX_ENABLED == STD_ON) && (J1939TP_CMDT_ENABLED == STD_ON))
    /* Otherwise */
    else
#  endif
#  if (J1939TP_CMDT_ENABLED == STD_ON)
    {
#   if ((J1939TP_CMDT_TX_ENABLED == STD_ON) && (J1939TP_CMDT_RX_ENABLED == STD_ON))
      /* If the N-SDU is from type CMDT_TX. */
      if (sduType == J1939TP_NSDU_CMDT_TX)
#   endif
#   if (J1939TP_CMDT_TX_ENABLED == STD_ON)
      {
        const J1939Tp_TxNSduStateType *txSduState = &J1939Tp_GetTxSduState(J1939Tp_GetTxSduStateIdxOfTxSdu(sduIdx));

        /* And the state is not IDLE */
        if ((txSduState->State & J1939TP_STATEMASK_CMDT) != J1939TP_STATE_IDLE)
        {
          /* Then forward the confirmation to the confirmation function of CMDT. */
          J1939Tp_CmdtTxConfirmation(sduIdx, J1939TP_TPCM_PDUTYPEOFTXPDU, sduType);
        }
      }
#   endif
#   if ((J1939TP_CMDT_TX_ENABLED == STD_ON) && (J1939TP_CMDT_RX_ENABLED == STD_ON))
      /* Otherwise */
      else
#   endif
#   if (J1939TP_CMDT_RX_ENABLED == STD_ON)
      {
        /* If the N-SDU is from type CMDT_RX. */
        if (sduType == J1939TP_NSDU_CMDT_RX)
        {
          const J1939Tp_RxNSduStateType *rxSduState = &J1939Tp_GetRxSduState(J1939Tp_GetRxSduStateIdxOfRxSdu(sduIdx));

          /* And the state is not IDLE */
          if ((rxSduState->State & J1939TP_STATEMASK_CMDT) != J1939TP_STATE_IDLE)
          {
            /* Then forward the confirmation to the confirmation function of CMDT. */
            J1939Tp_CmdtTxConfirmation(sduIdx, J1939TP_TPCM_PDUTYPEOFTXPDU, sduType);
          }
        }
      }
#   endif
    }
#  endif
    break;

#  if ((J1939TP_BAM_TX_ENABLED == STD_ON) || (J1939TP_CMDT_TX_ENABLED == STD_ON))
    /* If the PDU type is a Data frame. */
  case J1939TP_TPDT_PDUTYPEOFTXPDU:
#   if ((J1939TP_BAM_TX_ENABLED == STD_ON) && (J1939TP_CMDT_TX_ENABLED == STD_ON))
    /* If the N-SDU is from type BAM. */
    if (sduType == J1939TP_NSDU_BAM)
#   endif
#   if (J1939TP_BAM_TX_ENABLED == STD_ON)
    {
      const J1939Tp_TxNSduStateType *txSduState = &J1939Tp_GetTxSduState(J1939Tp_GetTxSduStateIdxOfTxSdu(sduIdx));

      /* And the state is not IDLE */
      if ((txSduState->State & J1939TP_STATEMASK_BAM) != J1939TP_STATE_IDLE)
      {
        /* Then forward the confirmation to the confirmation function of BAM. */
        J1939Tp_BamTxConfirmation(sduIdx, J1939TP_TPDT_PDUTYPEOFTXPDU);
      }
    }
#   endif
#   if ((J1939TP_BAM_TX_ENABLED == STD_ON) && (J1939TP_CMDT_TX_ENABLED == STD_ON))
    /* Otherwise */
    else
#   endif
#   if (J1939TP_CMDT_TX_ENABLED == STD_ON)
    {
      const J1939Tp_TxNSduStateType *txSduState = &J1939Tp_GetTxSduState(J1939Tp_GetTxSduStateIdxOfTxSdu(sduIdx));

      /* If the state is not IDLE */
      if ((txSduState->State & J1939TP_STATEMASK_CMDT) != J1939TP_STATE_IDLE)
      {
        /* Then forward the confirmation to the confirmation function of CMDT. */
        J1939Tp_CmdtTxConfirmation(sduIdx, J1939TP_TPDT_PDUTYPEOFTXPDU, sduType);
      }
    }
#   endif
    break;
#  endif
# endif

# if (J1939TP_ETP_ENABLED == STD_ON)
    /* If the PDU type is an Extended Connection Management frame. */
  case J1939TP_ETPCM_PDUTYPEOFTXPDU:
#  if ((J1939TP_ETP_TX_ENABLED == STD_ON) && (J1939TP_ETP_RX_ENABLED == STD_ON))
    /* If the N-SDU is from type ETP_TX. */
    if (sduType == J1939TP_NSDU_ETP_TX)
#  endif
#  if (J1939TP_ETP_TX_ENABLED == STD_ON)
    {
      const J1939Tp_TxNSduStateType *txSduState = &J1939Tp_GetTxSduState(J1939Tp_GetTxSduStateIdxOfTxSdu(sduIdx));

      /* And the state is not IDLE */
      if ((txSduState->State & J1939TP_STATEMASK_ETP) != J1939TP_STATE_IDLE)
      {
        /* Then forward the confirmation to the confirmation function of ETP. */
        J1939Tp_EtpTxConfirmation(sduIdx, J1939TP_ETPCM_PDUTYPEOFTXPDU, sduType);
      }
    }
#  endif
#  if ((J1939TP_ETP_TX_ENABLED == STD_ON) && (J1939TP_ETP_RX_ENABLED == STD_ON))
    /* Otherwise */
    else
#  endif
#  if (J1939TP_ETP_RX_ENABLED == STD_ON)
    {
      /* If the N-SDU is from type ETP_RX. */
      if (sduType == J1939TP_NSDU_ETP_RX)
      {
        const J1939Tp_RxNSduStateType *rxSduState = &J1939Tp_GetRxSduState(J1939Tp_GetRxSduStateIdxOfRxSdu(sduIdx));

        /* And the state is not IDLE */
        if ((rxSduState->State & J1939TP_STATEMASK_ETP) != J1939TP_STATE_IDLE)
        {
          /* Then forward the confirmation to the confirmation function of ETP. */
          J1939Tp_EtpTxConfirmation(sduIdx, J1939TP_ETPCM_PDUTYPEOFTXPDU, sduType);
        }
      }
    }
#  endif
    break;

#  if (J1939TP_ETP_TX_ENABLED == STD_ON)
    /* If the PDU type is an Extended Data frame. */
  case J1939TP_ETPDT_PDUTYPEOFTXPDU:
  {
    const J1939Tp_TxNSduStateType *txSduState = &J1939Tp_GetTxSduState(J1939Tp_GetTxSduStateIdxOfTxSdu(sduIdx));

    /* And the state is not IDLE */
    if ((txSduState->State & J1939TP_STATEMASK_ETP) != J1939TP_STATE_IDLE)
    {
      /* Then forward the confirmation to the confirmation function of ETP. */
      J1939Tp_EtpTxConfirmation(sduIdx, J1939TP_ETPDT_PDUTYPEOFTXPDU, sduType);
    }
  }
    break;
#  endif
# endif

# if (J1939TP_DIRECT_TX_ENABLED == STD_ON)
    /* If the PDU type is a direct frame. */
  case J1939TP_DIRECT_PDUTYPEOFTXPDU:
  {
    const J1939Tp_TxNSduStateType *txSduState = &J1939Tp_GetTxSduState(J1939Tp_GetTxSduStateIdxOfTxSdu(sduIdx));

    /* And the state is not IDLE */
    if ((txSduState->State & J1939TP_STATEMASK_DIRECT) != J1939TP_STATE_IDLE)
    {
      /* Then forward the confirmation to the confirmation function of DIRECT. */
      J1939Tp_DirectTxConfirmation(sduIdx);
    }
  }
    break;
# endif

  default: /* COV_J1939TP_SWITCHCASE_DEFAULT */
    break; /* MISRA */
  }

  J1939TP_DUMMY_STATEMENT(sduType); /* PRQA S 3112, 1338, 2983 */ /* MD_MSR_DummyStmt */
} /* J1939Tp_InternalTxConfirmation */ /* PRQA S 6030, 6080 */ /* MD_MSR_STCYC, MD_MSR_STMIF */
#endif

#define J1939TP_STOP_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*lint -restore */
/*============================================== J1939TP_STOP_SEC_CODE ==============================================*/


/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/*============================================== J1939TP_START_SEC_CODE =============================================*/
#define J1939TP_START_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*lint -restore */


/**********************************************************************************************************************
 *  J1939Tp_InitMemory()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, J1939TP_CODE) J1939Tp_InitMemory(void)
{
  /*! \trace SPEC-2167295 */
  J1939Tp_ModuleInitialized = J1939TP_UNINIT;
}


/**********************************************************************************************************************
 *  J1939Tp_Init()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, J1939TP_CODE) J1939Tp_Init(P2CONST(J1939Tp_ConfigType, AUTOMATIC, J1939TP_INIT_DATA) ConfigPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = J1939TP_E_NO_ERROR;

#if (J1939TP_USE_INIT_POINTER == STD_ON)
  J1939Tp_ConfigDataPtr = ConfigPtr;
#else
  J1939TP_DUMMY_STATEMENT(ConfigPtr); /* PRQA S 3112, 1338, 2983 */ /* MD_MSR_DummyStmt */
#endif

  /* ----- Development Error Checks ------------------------------------- */
  /*! \trace SPEC-2167364, SPEC-2167297, SPEC-2167298 */
  if (J1939Tp_ModuleInitialized == J1939TP_INIT)
  {
    errorId = J1939TP_E_REINIT;
  }
#if (J1939TP_USE_INIT_POINTER == STD_ON)
  else if (J1939Tp_ConfigDataPtr == NULL_PTR)
  {
# if (J1939TP_USE_ECUM_BSW_ERROR_HOOK == STD_ON)  /* COV_J1939TP_INIT_POINTER */
    EcuM_BswErrorHook(J1939TP_MODULE_ID, ECUM_BSWERROR_NULLPTR);
# endif
    errorId = J1939TP_E_PARAM_POINTER;
  }
# if (J1939TP_FINALMAGICNUMBER == STD_ON)  /* COV_J1939TP_INIT_POINTER */
  else if (J1939Tp_GetFinalMagicNumber() != J1939TP_FINAL_MAGIC_NUMBER)
  {
#  if (J1939TP_USE_ECUM_BSW_ERROR_HOOK == STD_ON)  /* COV_J1939TP_INIT_POINTER */
    EcuM_BswErrorHook(J1939TP_MODULE_ID, ECUM_BSWERROR_MAGICNUMBER);
#  endif
    errorId = J1939TP_E_INIT_FAILED;
  }
# endif
#endif
  else
  {
#if ((J1939TP_USE_INIT_POINTER == STD_OFF) && (J1939TP_DEV_ERROR_REPORT == STD_ON))
    if (ConfigPtr != NULL_PTR)
    {
      errorId = J1939TP_E_PARAM_POINTER;
    }
#endif

    /* ----- Implementation ----------------------------------------------- */
#if (J1939TP_TXPDU == STD_ON)
    {
      J1939Tp_SizeOfTxPduStateType txPduStateIdx;
      for (txPduStateIdx = 0; txPduStateIdx < J1939Tp_GetSizeOfTxPduState(); txPduStateIdx++)
      {
        J1939Tp_TxNPduStateType *txPduState = &J1939Tp_GetTxPduState(txPduStateIdx);
        /* no protection required - initialization may not happen while other APIs are still active and may not be
           interrupted */
        txPduState->Locked = FALSE;  /* VCA_J1939TP_TXPDUSTATE_CSL01 */
      }
    }
#endif

#if (J1939TP_TXSDU == STD_ON)
    {
      J1939Tp_SizeOfTxSduType txSduIdx;
      for (txSduIdx = 0; txSduIdx < J1939Tp_GetSizeOfTxSdu(); txSduIdx++)
      {
        J1939Tp_TxNSduStateType *txSduState = &J1939Tp_GetTxSduState(J1939Tp_GetTxSduStateIdxOfTxSdu(txSduIdx));

# if (J1939TP_FPP_TX_ENABLED == STD_ON)
        uint16 indexToSeqCnt = J1939Tp_GetFppTxSduSequenceCounterIdxOfTxSdu(txSduIdx);
        if (indexToSeqCnt != J1939TP_NO_FPPTXSDUSEQUENCECOUNTERIDXOFTXSDU)
        {
          J1939Tp_FppTxSduSequenceCounterType *sequenceCounter = &J1939Tp_GetFppTxSduSequenceCounter(indexToSeqCnt);
          (*sequenceCounter) = J1939TP_FPP_SC_INITIAL;  /* VCA_J1939TP_SEQCNT_VIA_TXSDU_CSL03 */
        }
# endif

        /* no protection required - initialization may not happen while other APIs are still active and may not be
           interrupted */
        txSduState->State = J1939TP_STATE_IDLE; /* VCA_J1939TP_TXSDUSTATE_CSL01 */
      }
    }
#endif

#if (J1939TP_RXSDU == STD_ON)
    {
      J1939Tp_SizeOfRxSduType rxSduIdx;

      for (rxSduIdx = 0; rxSduIdx < J1939Tp_GetSizeOfRxSdu(); rxSduIdx++)
      {
        J1939Tp_RxNSduStateType *rxSduState = &J1939Tp_GetRxSduState(J1939Tp_GetRxSduStateIdxOfRxSdu(rxSduIdx));

# if (J1939TP_FPP_RX_ENABLED == STD_ON)
        uint16 indexToSeqCnt = J1939Tp_GetFppRxSduSequenceCounterIdxOfRxSdu(rxSduIdx);
        if (indexToSeqCnt != J1939TP_NO_FPPRXSDUSEQUENCECOUNTERIDXOFRXSDU)
        {
          J1939Tp_FppRxSduSequenceCounterType *sequenceCounter = &J1939Tp_GetFppRxSduSequenceCounter(indexToSeqCnt);
          (*sequenceCounter) = J1939TP_FPP_SC_INVALID;  /* VCA_J1939TP_SEQCNT_VIA_RXSDU_CSL03 */
        }
# endif

        /* no protection required - initialization may not happen while other APIs are still active and may not be
           interrupted */
        rxSduState->State = J1939TP_STATE_IDLE; /* VCA_J1939TP_RXSDUSTATE_VIA_RXSDU_CSL03 */
      }
    }
#endif

    J1939Tp_ModuleInitialized = J1939TP_INIT;
  }

  /* ----- Development Error Report --------------------------------------- */
#if (J1939TP_DEV_ERROR_REPORT == STD_ON)
  if (errorId != J1939TP_E_NO_ERROR)
  {
    /*! \trace SPEC-2167289 */
    (void) J1939Tp_ReportDevError(J1939TP_SID_INIT, errorId);
  }
#else
  J1939TP_DUMMY_STATEMENT(errorId); /* PRQA S 3112, 1338, 2983 */ /* MD_MSR_DummyStmt */
#endif
} /* J1939Tp_Init */ /* PRQA S 6080 */ /* MD_MSR_STMIF */


/**********************************************************************************************************************
 *  J1939Tp_Shutdown()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, J1939TP_CODE) J1939Tp_Shutdown(void)
{
  /* Deviation from API pattern: The following check has no effect if reporting is disabled. */
#if (J1939TP_DEV_ERROR_REPORT == STD_ON)
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = J1939TP_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /*! \trace SPEC-2167297, SPEC-2167298 */
  /* Check initialization state. */
  if (J1939Tp_ModuleInitialized == J1939TP_UNINIT)
  {
    errorId = J1939TP_E_UNINIT;
  }
#endif

  /* ----- Implementation ----------------------------------------------- */
  /* Set internal state to J1939TP_UNINIT. */
  J1939Tp_ModuleInitialized = J1939TP_UNINIT;

  /* ----- Development Error Report --------------------------------------- */
#if (J1939TP_DEV_ERROR_REPORT == STD_ON)
  if (errorId != J1939TP_E_NO_ERROR)
  {
    /*! \trace SPEC-2167289 */
    (void) J1939Tp_ReportDevError(J1939TP_SID_SHUTDOWN, errorId);
  }
#endif
}


#if (J1939TP_VERSION_INFO_API == STD_ON)
/**********************************************************************************************************************
 *  J1939Tp_GetVersionInfo()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, J1939TP_CODE) J1939Tp_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, J1939TP_APPL_DATA) VersionInfo)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = J1939TP_E_NO_ERROR;

# if (J1939TP_DEV_ERROR_DETECT == STD_ON)
  /* Check plausibility of all input parameters. */
  if (VersionInfo == NULL_PTR)
  {
    errorId = J1939TP_E_PARAM_POINTER;
  }
  else
# endif
  {
    /* ----- Implementation ----------------------------------------------- */
    /* Write component data to VersionInfo. */
    VersionInfo->vendorID = J1939TP_VENDOR_ID;  /* VCA_J1939TP_VERSIONINFO */
    VersionInfo->moduleID = J1939TP_MODULE_ID;  /* VCA_J1939TP_VERSIONINFO */
    VersionInfo->sw_major_version = J1939TP_SW_MAJOR_VERSION; /* VCA_J1939TP_VERSIONINFO */
    VersionInfo->sw_minor_version = J1939TP_SW_MINOR_VERSION; /* VCA_J1939TP_VERSIONINFO */
    VersionInfo->sw_patch_version = J1939TP_SW_PATCH_VERSION; /* VCA_J1939TP_VERSIONINFO */
  }

  /* ----- Development Error Report --------------------------------------- */
# if (J1939TP_DEV_ERROR_REPORT == STD_ON)
  if (errorId != J1939TP_E_NO_ERROR)
  {
    /*! \trace SPEC-2167289 */
    (void) J1939Tp_ReportDevError(J1939TP_SID_GETVERSIONINFO, errorId);
  }
# else
  J1939TP_DUMMY_STATEMENT(errorId); /* PRQA S 3112, 1338, 2983 */ /* MD_MSR_DummyStmt */
# endif
}
#endif


/**********************************************************************************************************************
 *  J1939Tp_MainFunction()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(void, J1939TP_CODE) J1939Tp_MainFunction(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = J1939TP_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /*! \trace SPEC-2167297, SPEC-2167298 */
  /* Check initialization state of the component. */
  if (J1939Tp_ModuleInitialized == J1939TP_UNINIT)
  {
    errorId = J1939TP_E_UNINIT;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
#if (J1939TP_TXPDU == STD_ON)
    /* Process all Tx PDUs. */
    J1939Tp_InternalMain_TxPdu();
#endif

#if (J1939TP_TXSDU == STD_ON)
    /* Then process all Tx SDUs. */
    J1939Tp_InternalMain_TxSdu();
#endif

#if (J1939TP_RXSDU == STD_ON)
    /* Then process all Rx SDUs. */
    J1939Tp_InternalMain_RxSdu();
#endif
  }

  /* ----- Development Error Report --------------------------------------- */
#if (J1939TP_DEV_ERROR_REPORT == STD_ON)
  if (errorId != J1939TP_E_NO_ERROR)
  {
    /*! \trace SPEC-2167289 */
    (void) J1939Tp_ReportDevError(J1939TP_SID_MAINFUNCTION, errorId);
  }
#else
  J1939TP_DUMMY_STATEMENT(errorId); /* PRQA S 3112, 1338, 2983 */ /* MD_MSR_DummyStmt */
#endif
}



/**********************************************************************************************************************
 *  J1939Tp_Transmit()
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
 */
FUNC(Std_ReturnType, J1939TP_CODE) J1939Tp_Transmit(PduIdType TxSduId,
                                                    P2CONST(PduInfoType, AUTOMATIC, J1939TP_APPL_DATA) PduInfoPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = J1939TP_E_NO_ERROR;
  Std_ReturnType result = E_NOT_OK;

  /* ----- Development Error Checks ------------------------------------- */
  /*! \trace SPEC-2167297, SPEC-2167298 */
  /* Check initialization state. */
  if (J1939Tp_ModuleInitialized == J1939TP_UNINIT)
  {
    errorId = J1939TP_E_UNINIT;
  }
#if (J1939TP_DEV_ERROR_DETECT == STD_ON)
  /* Check parameter 'PduInfoPtr' */
  else if (PduInfoPtr == NULL_PTR)
  {
    errorId = J1939TP_E_PARAM_POINTER;
  }
# if (J1939TP_TXSDU == STD_ON)
  /* Check parameter 'TxSduId' */
  else if (TxSduId >= J1939Tp_GetSizeOfTxSdu())
  {
    errorId = J1939TP_E_INVALID_PDU_SDU_ID;
  }
#  if (J1939TP_INVALIDHNDOFTXSDU == STD_ON)
  /* Check parameter 'TxSduId' */
  else if (J1939Tp_IsInvalidHndOfTxSdu(TxSduId))
  {
    errorId = J1939TP_E_INVALID_PDU_SDU_ID;
  }
#  endif
#  if (J1939TP_ISVARIABLEOFTXSDU == STD_ON)
  /* Check parameter 'PduInfoPtr' */
  else if ((J1939Tp_IsIsVariableOfTxSdu(TxSduId)) && (PduInfoPtr->SduLength > J1939Tp_GetPduLengthOfTxSdu(TxSduId))) 
  {
    errorId = J1939TP_E_INVALID_LENGTH;
  }
  /* Check parameter 'PduInfoPtr' */
  else if ((!J1939Tp_IsIsVariableOfTxSdu(TxSduId)) && (PduInfoPtr->SduLength != J1939Tp_GetPduLengthOfTxSdu(TxSduId)))
  {
    errorId = J1939TP_E_INVALID_LENGTH;
  }
#  else
  /* Check parameter 'PduInfoPtr' */
  else if (PduInfoPtr->SduLength != J1939Tp_GetPduLengthOfTxSdu(TxSduId))
  {
    errorId = J1939TP_E_INVALID_LENGTH;
  }
#  endif
# endif
  /* Check parameter 'TxSduId' */
  else if (
# if (J1939TP_METADATALENGTHOFTXSDU == STD_ON)
            (J1939Tp_GetMetaDataLengthOfTxSdu(TxSduId) > 0u) &&
# endif
            (PduInfoPtr->SduDataPtr == NULL_PTR))
  {
    errorId = J1939TP_E_PARAM_POINTER;
  }
#endif
  else
  {
    /* ----- Implementation ----------------------------------------------- */
#if (J1939TP_TX_ENABLED == STD_ON)
    /* Request the transmission. */
    /*@ assert TxSduId < J1939Tp_GetSizeOfTxSdu(); */ /* VCA_J1939NM_TXSDU */
# if (J1939TP_INVALIDHNDOFTXSDU == STD_ON)
    /*@ assert !J1939Tp_IsInvalidHndOfTxSdu(TxSduId); */ /* VCA_J1939NM_TXSDU */
# endif
    result = J1939Tp_InternalTransmit(TxSduId, PduInfoPtr);
#else
    J1939TP_DUMMY_STATEMENT(TxSduId); /* PRQA S 3112, 1338, 2983 */ /* MD_MSR_DummyStmt */
    J1939TP_DUMMY_STATEMENT(PduInfoPtr); /* PRQA S 3112, 1338, 2983 */ /* MD_MSR_DummyStmt */
#endif
  }


  /* ----- Development Error Report --------------------------------------- */
#if (J1939TP_DEV_ERROR_REPORT == STD_ON)
  if (errorId != J1939TP_E_NO_ERROR)
  {
    /*! \trace SPEC-2167289 */
    (void) J1939Tp_ReportDevError(J1939TP_SID_TRANSMIT, errorId);
  }
#else
  J1939TP_DUMMY_STATEMENT(errorId); /* PRQA S 3112, 1338, 2983 */ /* MD_MSR_DummyStmt */
#endif

  /* Return the result of the request. */
  return result;
} /* J1939Tp_Transmit */ /* PRQA S 6080 */ /* MD_MSR_STMIF */


/**********************************************************************************************************************
 *  J1939Tp_RxIndication()
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
FUNC(void, J1939TP_CODE) J1939Tp_RxIndication(PduIdType RxPduId,
                                              P2CONST(PduInfoType, AUTOMATIC, J1939TP_APPL_DATA) PduInfoPtr)
{
  /*! \trace SPEC-2167299 */
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = J1939TP_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /*! \trace SPEC-2167297, SPEC-2167298 */
  /* Check initialization state. */
  if (J1939Tp_ModuleInitialized == J1939TP_UNINIT)
  {
    errorId = J1939TP_E_UNINIT;
  }
#if (J1939TP_DEV_ERROR_DETECT == STD_ON)
  /* Check parameter 'PduInfoPtr' */
  else if (PduInfoPtr == NULL_PTR)
  {
    errorId = J1939TP_E_PARAM_POINTER;
  }
  /* Check parameter 'PduInfoPtr' */
  else if (PduInfoPtr->SduDataPtr == NULL_PTR)
  {
    errorId = J1939TP_E_PARAM_POINTER;
  }
# if (J1939TP_RXPDU == STD_ON)
  /* Check parameter 'RxPduId' */
  else if (RxPduId >= J1939Tp_GetSizeOfRxPdu())
  {
    errorId = J1939TP_E_INVALID_PDU_SDU_ID;
  }
#  if (J1939TP_INVALIDHNDOFRXPDU == STD_ON)
  /* Check parameter 'RxPduId' */
  else if (J1939Tp_IsInvalidHndOfRxPdu(RxPduId))
  {
    errorId = J1939TP_E_INVALID_PDU_SDU_ID;
  }
#  endif
# endif
#endif
  else
  {
    /* ----- Implementation ----------------------------------------------- */
#if (J1939TP_RXPDU == STD_ON)
    /* Forward the processing of the reception. */
    /*@ assert RxPduId < J1939Tp_GetSizeOfRxPdu(); */ /* VCA_J1939NM_RXPDU */
# if (J1939TP_INVALIDHNDOFRXPDU == STD_ON)
    /*@ assert !J1939Tp_IsInvalidHndOfRxPdu(RxPduId); */ /* VCA_J1939NM_RXPDU */
# endif
    J1939Tp_InternalRxIndication(RxPduId, PduInfoPtr);
#else
    J1939TP_DUMMY_STATEMENT(RxPduId); /* PRQA S 3112, 1338, 2983 */ /* MD_MSR_DummyStmt */
    J1939TP_DUMMY_STATEMENT(PduInfoPtr); /* PRQA S 3112, 1338, 2983 */ /* MD_MSR_DummyStmt */
#endif
  }

  /* ----- Development Error Report --------------------------------------- */
#if (J1939TP_DEV_ERROR_REPORT == STD_ON)
  if (errorId != J1939TP_E_NO_ERROR)
  {
    /*! \trace SPEC-2167289 */
    (void) J1939Tp_ReportDevError(J1939TP_SID_RXINDICATION, errorId);
  }
#else
  J1939TP_DUMMY_STATEMENT(errorId); /* PRQA S 3112, 1338, 2983 */ /* MD_MSR_DummyStmt */
#endif

} /* J1939Tp_RxIndication */ /* PRQA S 6080 */ /* MD_MSR_STMIF */


/**********************************************************************************************************************
 *  J1939Tp_TxConfirmation()
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
FUNC(void, J1939TP_CODE) J1939Tp_TxConfirmation(PduIdType TxPduId)
{
  /*! \trace SPEC-2167299 */
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = J1939TP_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /*! \trace SPEC-2167297, SPEC-2167298 */
  /* Check initialization state. */
  if (J1939Tp_ModuleInitialized == J1939TP_UNINIT)
  {
    errorId = J1939TP_E_UNINIT;
  }
#if ((J1939TP_TXPDU == STD_ON) && (J1939TP_DEV_ERROR_DETECT == STD_ON))
  /* Check parameter 'TxPduId' */
  else if (TxPduId >= J1939Tp_GetSizeOfTxPdu())
  {
    errorId = J1939TP_E_INVALID_PDU_SDU_ID;
  }
# if (J1939TP_INVALIDHNDOFTXPDU == STD_ON)
  /* Check parameter 'TxPduId' */
  else if (J1939Tp_IsInvalidHndOfTxPdu(TxPduId))
  {
    errorId = J1939TP_E_INVALID_PDU_SDU_ID;
  }
# endif
#endif
  else
  {
    /* ----- Implementation ----------------------------------------------- */
#if (J1939TP_TXPDU == STD_ON)
    /* If there exist at least one TxPdu */
    J1939Tp_TxNPduStateType *txPduState = &J1939Tp_GetTxPduState(J1939Tp_GetTxPduStateIdxOfTxPdu(TxPduId));

    /* If the PDU is locked */
    SchM_Enter_J1939Tp_J1939TP_EXCLUSIVE_AREA_TXNPDULOCK();
    if (txPduState->Locked == TRUE)
    {
      /* Then unlock the PDU and forward the processing of the confirmation. */
      PduIdType sduIdx = txPduState->CurrentNSduId;
      J1939Tp_NSduType sduType = txPduState->CurrentNSduType;

      /* protected against concurrent Tx confirmation timeout */
      txPduState->Locked = FALSE; /* VCA_J1939TP_TXPDUSTATE_VIA_TXPDU_CSL03 */
      SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_TXNPDULOCK();

      J1939Tp_InternalTxConfirmation(TxPduId, sduIdx, sduType);
    }
    /* Otherwise the PDU is not in use */
    else
    {
      SchM_Exit_J1939Tp_J1939TP_EXCLUSIVE_AREA_TXNPDULOCK();
    }
#else
    J1939TP_DUMMY_STATEMENT(TxPduId); /* PRQA S 3112, 1338, 2983 */ /* MD_MSR_DummyStmt */
#endif
  }

  /* ----- Development Error Report --------------------------------------- */
#if (J1939TP_DEV_ERROR_REPORT == STD_ON)
  if (errorId != J1939TP_E_NO_ERROR)
  {
    /*! \trace SPEC-2167289 */
    (void) J1939Tp_ReportDevError(J1939TP_SID_TXCONFIRMATION, errorId);
  }
#else
  J1939TP_DUMMY_STATEMENT(errorId); /* PRQA S 3112, 1338, 2983 */ /* MD_MSR_DummyStmt */
#endif
} /* J1939Tp_TxConfirmation */


/**********************************************************************************************************************
 *  J1939Tp_ChangeParameter()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
/* *INDENT-OFF* */
FUNC(Std_ReturnType, J1939TP_CODE) J1939Tp_ChangeParameter(PduIdType id, TPParameterType parameter, uint16 value) /* COV_J1939TP_UNUSED_FUNC_CHANGEPARAMETER */
/* *INDENT-ON* */
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType result = E_NOT_OK;
  uint8 errorId = J1939TP_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /*! \trace SPEC-2167297, SPEC-2167298 */
  if (J1939Tp_ModuleInitialized == J1939TP_UNINIT) /* COV_J1939TP_UNUSED_FUNC_CHANGEPARAMETER */
  {
    errorId = J1939TP_E_UNINIT;
  }
#if (J1939TP_DEV_ERROR_DETECT == STD_ON)
  else if (parameter != TP_BS) /* COV_J1939TP_UNUSED_FUNC_CHANGEPARAMETER */
  {
    errorId = J1939TP_E_INVALID_CHANGE_PARAM;
  }
  else if ((value == J1939TP_BS_MIN) || (value > J1939TP_BS_MAX)) /* COV_J1939TP_UNUSED_FUNC_CHANGEPARAMETER */
  {
    errorId = J1939TP_E_INVALID_CHANGE_VALUE;
  }
# if (J1939TP_RXSDU == STD_ON)
  else if (id >= J1939Tp_GetSizeOfRxSdu()) /* COV_J1939TP_UNUSED_FUNC_CHANGEPARAMETER */
  {
    errorId = J1939TP_E_INVALID_PDU_SDU_ID;
  }
#  if (J1939TP_INVALIDHNDOFRXSDU == STD_ON)
  else if (J1939Tp_IsInvalidHndOfRxSdu(id)) /* COV_J1939TP_UNUSED_FUNC_CHANGEPARAMETER */
  {
    errorId = J1939TP_E_INVALID_PDU_SDU_ID;
  }
#  endif
# endif
  else
#endif
  {
    /* ----- Implementation ----------------------------------------------- */
  }

  /* ----- Development Error Report --------------------------------------- */
#if (J1939TP_DEV_ERROR_REPORT == STD_ON)
  if (errorId != J1939TP_E_NO_ERROR) /* COV_J1939TP_UNUSED_FUNC_CHANGEPARAMETER */
  {
    /*! \trace SPEC-2167289 */
    (void) J1939Tp_ReportDevError(J1939TP_SID_CHANGEPARAMETER, errorId);
  }
#else
  J1939TP_DUMMY_STATEMENT(errorId); /* PRQA S 3112, 1338, 2983 */ /* MD_MSR_DummyStmt */
#endif
  J1939TP_DUMMY_STATEMENT(id); /* PRQA S 3112, 1338, 2983 */ /* MD_MSR_DummyStmt */
  J1939TP_DUMMY_STATEMENT(parameter); /* PRQA S 3112, 1338, 2983 */ /* MD_MSR_DummyStmt */
  J1939TP_DUMMY_STATEMENT(value); /* PRQA S 3112, 1338, 2983 */ /* MD_MSR_DummyStmt */

  return result;
} /* J1939Tp_ChangeParameter */ /* PRQA S 6080 */ /* MD_MSR_STMIF */


/**********************************************************************************************************************
 *  J1939Tp_CancelReceive()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, J1939TP_CODE) J1939Tp_CancelReceive(PduIdType RxSduId) /* COV_J1939TP_UNUSED_FUNC_CANCELRECEIVE */
{
  J1939TP_DUMMY_STATEMENT(RxSduId); /* PRQA S 3112, 1338, 2983 */ /* MD_MSR_DummyStmt */

  /*! \trace SPEC-2167289 */
  J1939Tp_ReportDevError(J1939TP_SID_CANCELRECEIVE, J1939TP_E_DUMMY_API);

  return E_NOT_OK;
}


/**********************************************************************************************************************
 *  J1939Tp_CancelTransmit()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, J1939TP_CODE) J1939Tp_CancelTransmit(PduIdType TxPduId) /* COV_J1939TP_UNUSED_FUNC_CANCELTRANSMIT */
{
  J1939TP_DUMMY_STATEMENT(TxPduId); /* PRQA S 3112, 1338, 2983 */ /* MD_MSR_DummyStmt */

  /*! \trace SPEC-2167289 */
  J1939Tp_ReportDevError(J1939TP_SID_CANCELTRANSMIT, J1939TP_E_DUMMY_API);

  return E_NOT_OK;
}

#define J1939TP_STOP_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*lint -restore */
/*============================================== J1939TP_STOP_SEC_CODE ==============================================*/


/* Module specific MISRA deviations:

MD_J1939Tp_2.2
  Reason:     The bit masking is used here for security and comprehensibility.
  Risk:       No risk, because only warning that the operation is redundant.
  Prevention: N/A

MD_J1939Tp_14.1_2880
  Reason:     Depending on the configured PduLengthType, this code is never executed.
  Risk:       When PduLengthType is uint8, depending on compiler optimizations dead code might be included.
  Prevention: Set PduLengthType to uin16 or uint32, or enable appropriate compiler optimizations.

MD_J1939Tp_14.3_Cmdt
  Reason:     Controlling expressions shall not be invariant, but in this case it depends on the value of J1939TP_MAX_LENGTH.
  Risk:       None
  Prevention: N/A

MD_J1939Tp_10.5
  Reason:     The value of an expression should not be cast to an inappropriate essential type like the enum
  Risk:       when the result of the info->SduDataPtr[J1939TP_ETPCM_CB]) don't match a value of the list of enumeration
  Prevention: N/A

MD_J1939Tp_10.7
  Reason:     A uint8 parameter could be cast to a uint32 variable. But the uint8 is lower than uint32. Therefore
              these cases must be checked, and the error handling code is then detected as operand shall not have wider essential type.
  Risk:       None
  Prevention: N/A
   
MD_J1939Tp_10.4_Etp
  Reason:     Depending on the configured PduLengthType.
  Risk:       When PduLengthType is uint8 or uint16, the code will no longer be executable.
  Prevention: Set PduLengthType to uint32.

MD_J1939Tp_10.5_Etp
  Reason:     The value of an expression should not be cast to an inappropriate essential type like the enum
  Risk:       when the result of the info->SduDataPtr[J1939TP_ETPCM_CB]) don't match a value of the list of enumeration
  Prevention: N/A

MD_J1939Tp_10.7_Etp
  Reason:     A uint8 parameter could be cast to a uint32 variable. But the uint8 is lower than uint32. Therefore
              these cases must be checked, and the error handling code is then detected as operand shall not have wider essential type.
  Risk:       None
  Prevention: N/A
   
MD_J1939Tp_14.1_2880_Etp
  Reason:     Depending on the configured PduLengthType, this code is never executed.
  Risk:       When PduLengthType is uint8 or uint16, depending on compiler optimizations dead code might be included.
  Prevention: Set PduLengthType to uint32, or enable appropriate compiler optimizations.

MD_J1939Tp_14.3_Etp
  Reason:     Controlling expressions shall not be invariant, but in this case it depends on the value of J1939TP_ETP_MAX_LENGTH.
  Risk:       None
  Prevention: N/A
*/


/* SBSW_JUSTIFICATION_BEGIN

\ID VCA_J1939TP_EXCLUDE_FPP_ETP
 \DESCRIPTION Calling undefined Fpp and Etp functions
 \COUNTERMEASURE \M Fpp and Etp are currently excluded from the Safe process and thus are not relevant.
                    Verify that (J1939TP_FPP_ENABLED == STD_OFF), (J1939TP_FPP_TX_ENABLED == STD_OFF), (J1939TP_FPP_RX_ENABLED == STD_OFF),
                    (J1939TP_ETP_ENABLED == STD_OFF), (J1939TP_ETP_TX_ENABLED == STD_OFF), (J1939TP_ETP_RX_ENABLED == STD_OFF)

\ID VCA_J1939TP_FCTCALL_PTR2LOCAL
 \DESCRIPTION    Function call with a pointer to a local variable as argument.
 \COUNTERMEASURE \N Pointers to local variables can be safely considered to be valid.

\ID VCA_J1939NM_RXPDU
 \DESCRIPTION Valid RxPdu is needed
 \COUNTERMEASURE \R The DET check of the function verifies that RxPdu is valid using CSL01 generated identifiers

\ID VCA_J1939TP_RXSDUSTATE_VIA_RXPDU_CSL03
 \DESCRIPTION Access to RxSduState via indirection over RxPdu
 \COUNTERMEASURE \N Qualified use-case CSL03 of ComStackLib

\ID VCA_J1939TP_RXSDUSTATE_VIA_RXSDU_CSL03
 \DESCRIPTION Access to RxSduState via indirection over RxSdu
 \COUNTERMEASURE \N Qualified use-case CSL03 of ComStackLib

\ID VCA_J1939TP_SEQCNT_VIA_RXSDU_CSL03
 \DESCRIPTION Access of sequence counter via indirection over RxSdu
 \COUNTERMEASURE \N Qualified use-case CSL03 of ComStackLib

\ID VCA_J1939TP_SEQCNT_VIA_TXSDU_CSL03
 \DESCRIPTION Access of sequence counter via indirection over TxSdu
 \COUNTERMEASURE \N Qualified use-case CSL03 of ComStackLib

\ID VCA_J1939TP_TXPDUSTATE_CSL01
 \DESCRIPTION Access of TxPduState using ComStackLib
 \COUNTERMEASURE \N Qualified use-case CSL01 of ComStackLib

\ID VCA_J1939TP_TXPDUSTATE_VIA_RXSDU_CSL03
 \DESCRIPTION Access to TxPduState via indirection over RxSdu
 \COUNTERMEASURE \N Qualified use-case CSL03 of ComStackLib

\ID VCA_J1939TP_TXPDUSTATE_VIA_TXPDU_CSL03
 \DESCRIPTION Access to TxPduState via indirection over TxPdu
 \COUNTERMEASURE \N Qualified use-case CSL03 of ComStackLib

\ID VCA_J1939TP_TXPDUSTATE_VIA_TXSDU_CSL03
 \DESCRIPTION Access to TxPduState via indirection over TxSdu
 \COUNTERMEASURE \N Qualified use-case CSL03 of ComStackLib

\ID VCA_J1939NM_TXSDU
 \DESCRIPTION Valid TxSdu is needed
 \COUNTERMEASURE \R The DET check of the function verifies that TxSdu is valid using CSL01 generated identifiers

\ID VCA_J1939TP_TXSDUSTATE_CSL01
 \DESCRIPTION Access of TxSduState using ComStackLib
 \COUNTERMEASURE \N Qualified use-case CSL01 of ComStackLib

\ID VCA_J1939TP_TXSDUSTATE_VIA_TXSDU_CSL03
 \DESCRIPTION Access of TxSduState via indirection over TxSdu
 \COUNTERMEASURE \N Qualified use-case CSL03 of ComStackLib

\ID VCA_J1939TP_VERSIONINFO
 \DESCRIPTION The function J1939Tp_GetVersionInfo writes to the object referenced by parameter VersionInfo
 \COUNTERMEASURE \N The caller ensures that the pointers passed to the parameters VersionInfo is valid

   SBSW_JUSTIFICATION_END */

/* COV_JUSTIFICATION_BEGIN

\ID COV_J1939TP_INIT_POINTER
  \ACCEPT tx
  \REASON J1939TP_USE_ECUM_BSW_ERROR_HOOK and J1939TP_FINALMAGICNUMBER are always STD_ON when the parent preprocessor define J1939TP_USE_INIT_POINTER is STD_ON.

\ID COV_J1939TP_DUMMY_STMNT
  \ACCEPT tx
  \REASON J1939TP_TXVARPRIOFTXCHANNEL is always STD_ON when the function J1939Tp_InternalGetPriority is called.

\ID COV_J1939TP_UNUSED_FUNC_CANCELRECEIVE
  \ACCEPT X
  \ACCEPT XX
  \REASON Function J1939Tp_CancelReceive is not used yet.

\ID COV_J1939TP_UNUSED_FUNC_CANCELTRANSMIT
  \ACCEPT X
  \ACCEPT XX
  \REASON Function J1939Tp_CancelTransmit is not used yet.

\ID COV_J1939TP_UNUSED_FUNC_CHANGEPARAMETER
  \ACCEPT X
  \ACCEPT XX
  \ACCEPT XX xx xx
  \REASON Function J1939Tp_ChangeParameter is not used yet.

\ID COV_J1939TP_SWITCHCASE_DEFAULT
  \ACCEPT X
  \REASON Switch case has a default part for MISRA checks which is not reachable.

\ID COV_J1939TP_UNUSED_TX_PROTOCOL
  \ACCEPT TF tf xf xx
  \ACCEPT XX xx xx xx
  \REASON In the test configuration J1939Tp_03 there must be no CMDT connections. Thus no connection with undefined protocol type can be configured because otherwise CMDT would automatically be enabled.


--- Preprocessor Coverage Justifications ------------------------------------------------------------------------------

\ID COV_J1939TP_INIT_POINTER
  \ACCEPT TX
  \REASON J1939TP_USE_ECUM_BSW_ERROR_HOOK and J1939TP_FINALMAGICNUMBER are always STD_ON when the parent preprocessor define J1939TP_USE_INIT_POINTER is STD_ON.



COV_JUSTIFICATION_END */
