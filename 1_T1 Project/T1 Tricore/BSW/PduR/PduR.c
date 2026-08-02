/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2018 by Vector Informatik GmbH.                                                  All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  PduR.c
 *      Project:  Gw_AsrPduRCfg5
 *       Module:  MICROSAR PDU Router
 *    Generator:  Configurator 5
 *
 *  Description:  Vector implementation of AUTOSAR PDU Router
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

/**********************************************************************************************************************
 * LOCAL MISRA / PCLINT JUSTIFICATION
 *********************************************************************************************************************/
/* *INDENT-OFF* */
/* PRQA S 0779 EOF */ /* MD_MSR_5.1_779 */
/* PRQA S 0777 EOF */ /* MD_MSR_5.1_777 */
/* PRQA S 3355, 3356 EOF */ /* MD_CSL_3355_3356 */
/* *INDENT-ON* */

#define PDUR_SOURCE
/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "PduR.h"
#include "PduR_Bm.h"
#include "SchM_PduR.h"

#if ((PDUR_BSWMPDURRXINDICATIONCALLBACKOFRXIF2DEST == STD_ON) || (PDUR_BSWMPDURTPRXINDICATIONCALLBACKOFRXTP2DEST == STD_ON) || (PDUR_BSWMPDURTPSTARTOFRECEPTIONCALLBACKOFRXTP2DEST == STD_ON) || (PDUR_BSWMPDURTRANSMITCALLBACKOFTX2LO == STD_ON) || (PDUR_BSWMPDURTXCONFIRMATIONCALLBACKOFTXIF2UP == STD_ON) || (PDUR_BSWMPDURTPTXCONFIRMATIONCALLBACKOFTXTP2SRC == STD_ON))
# include "BswM_PduR.h"
#endif

#if(PDUR_USE_ECUM_BSW_ERROR_HOOK == STD_ON)
# include "EcuM_Error.h"
#endif

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * LOCAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
#if(PDUR_RPGROM == STD_ON)
/**********************************************************************************************************************
 * PduR_Init_RmDestRpgRom
 *********************************************************************************************************************/
/*! \brief      This function initializes the PDUR routing path groups.
 *  \details     -
 *  \pre        PduR_InitMemory() has been executed, if the start up code does not initialise variables.
 *  \note       The function must be called on task level and has not to be interrupted.
 *              by other administrative function calls.
 *  \warning    PduR_Init shall not pre-empt any PDUR function.
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_Init_RmDestRpgRom(void);
#endif

#if (PDUR_EXISTS_T_T_SINGLE_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmIf_Init_TTSingleBuffer
 *********************************************************************************************************************/
/*! \brief    This function initializes the single buffer with default values
 *  \details     -
 *  \pre      PduR_InitMemory() has been executed, if the start up code does not initialise variables.
 *  \note      The function must be called on task level and has not to be interrupted.
 *            by other administrative function calls.
 *  \warning  PduR_Init shall not pre-empt any PDUR function.
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_RmIf_Init_TTSingleBuffer(void);
#endif

#if (PDUR_DEDICATEDTXBUFFEROFRMBUFFEREDIFPROPERTIESROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmIf_Init_DedicatedTxBuffer
 *********************************************************************************************************************/
/*! \brief    This function assign dedicated buffer to routing pathways
 *  \details     -
 *  \pre      PduR_InitMemory() has been executed, if the start up code does not initialise variables.
 *  \note  The function must be called on task level and has not to be interrupted.
 *             by other administrative function calls.
 *  \warning  PduR_Init shall not pre-empt any PDUR function.
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_RmIf_Init_DedicatedTxBuffer(void);
#endif

#if (PDUR_DEDICATEDTXBUFFEROFRMBUFFEREDTPPROPERTIESROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmTp_Init_DedicatedTxBuffer
 *********************************************************************************************************************/
/*! \brief    This function assign dedicated buffer to routing pathways
 *  \details     -
 *  \pre      PduR_InitMemory() has been executed, if the start up code does not initialise variables.
 *  \note     The function must be called on task level and has not to be interrupted.
 *            by other administrative function calls.
 *  \warning  PduR_Init shall not pre-empt any PDUR function.
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_RmTp_Init_DedicatedTxBuffer(void);
#endif

#if(PDUR_FMFIFORAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Init_FmFifoRam
 *********************************************************************************************************************/
/*! \brief      This function initializes the FifoManager Fifo Ram
 *  \details     -
 *  \pre        PduR_InitMemory() has been executed, if the start up code does not initialise variables.
 *  \note       The function must be called on task level and has not to be interrupted.
 *              by other administrative function calls.
 *  \warning    PduR_Init shall not pre-empt any PDUR function.
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_Init_FmFifoRam(void);
#endif
#if (PDUR_FMFIFORAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Init_FmFifoElementRam
 *********************************************************************************************************************/
/*! \brief      This function initializes the FifoManager Fifo Element Ram
 *  \details    -
 *  \pre        PduR_InitMemory() has been executed, if the start up code does not initialise variables.
 *  \note       The function must be called on task level and has not to be interrupted.
 *              by other administrative function calls.
 *  \warning    PduR_Init shall not pre-empt any PDUR function.
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_Init_FmFifoElementRam(void);
#endif
#if(PDUR_FMFIFORAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Init_FmFifoInstanceRam
 *********************************************************************************************************************/
/*! \brief      This function initializes the FifoManager Fifo Element Instance Ram
 *  \details     -
 *  \pre        PduR_InitMemory() has been executed, if the start up code does not initialise variables.
 *  \note       The function must be called on task level and has not to be interrupted.
 *              by other administrative function calls.
 *  \warning    PduR_Init shall not pre-empt any PDUR function.
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_Init_FmFifoInstanceRam(void);
#endif

#if(PDUR_RMGDESTNTO1INFORAMIDXOFRMGDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_Rm_MultipleSourceHandler_Init
 *********************************************************************************************************************/
/*! \brief      This function initializes the PDUR fan in RAM variables.
 *  \details     -
 *  \pre        PduR_InitMemory() has been executed, if the start up code does not initialise variables.
 *  \note       The function must be called on task level and has not to be interrupted
 *              by other administrative function calls.
 *  \warning    PduR_Init shall not pre-empt any PDUR function.
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_Rm_MultipleSourceHandler_Init(void);
#endif

#if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_Init_GwTp
 *********************************************************************************************************************/
/*! \brief      This function initializes the PDUR transport protocol routings.
 *  \details     -
 *  \pre        PduR_InitMemory() has been executed, if the startup code does not initialise variables.
 *  \note       The function must be called on task level and has not to be interrupted.
 *              by other administrative function calls.
 *  \warning    PduR_Init shall not pre-empt any PDUR function.
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_Init_GwTp(void);
#endif

#if ((PDUR_TRANSMITREQUESTQUEUE == STD_ON) || (PDUR_RECEPTIONINDICATIONQUEUE == STD_ON)) /* COV_PDUR_VAR_ELISA_STD_OFF_XF_xf_xf */
/**********************************************************************************************************************
 * PduR_GetBufferedPduInfo
 *********************************************************************************************************************/
/*! \brief      Get the PduInfo stored in the TxBuffer.
 *  \details    -
 *  \param[in]  rmGDest                        Routing manager indirection Idx.
 *  \param[in]  info                           Empty PduInfo which will be filled with data.
 *  \param[in]  peekedfmFifoElementRamReadIdx  Index of the current element which is used by the routing.
 *  \return     E_OK                           Data has been successfully written to the info Pointer.
 *              E_NOT_OK                       No Data has been written to the into Pointer.
 *  \note       The function is called in context PduR_MainFunctionTx() or PduR_MainFunctionRx().
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_GetBufferedPduInfo(PduR_RmGDestRomIterType rmGDest, P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info,
                                                                     P2VAR(PduR_FmFifoElementRamIterType, AUTOMATIC, PDUR_APPL_DATA) peekedfmFifoElementRamReadIdx);
#endif

#if ((PDUR_EXISTS_IMMEDIATE_PDURDESTPDUPROCESSINGOFRMGDESTROM == STD_ON) && ((PDUR_EXISTS_DIRECT_FIFO_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON) || (PDUR_EXISTS_T_T_FIFO_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON) || (PDUR_EXISTS_T_T_SINGLE_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON))) /* COV_PDUR_VAR_ELISA_STD_ON_TF_tx_tf_tf_tf */
/**********************************************************************************************************************
 * PduR_PerformImmediateDestinationDataProcessing
 *********************************************************************************************************************/
/*! \brief      Perform routing to destination module.
 *  \details    -
 *  \param[in]  rmGDest                        Routing manager indirection Idx to global destination Pdu table.
 *  \param[in]  rmDest                         Routing manager indirection Idx.
 *  \param[in]  info                           Pointer to the destination buffer and the number of bytes to copy.
 *  \param[in]  fmFifoElementRamIdx            Fifo element Idx.
 *  \param[in]  useLock                        Shall the 'transmissionActive' Flag be set and considered for this transmission
 *  \return     E_OK                           The transmission was successfully.
 *              E_NOT_OK                       The transmission fails.
 *  \note       The function is called in context PduR_RmIf_FifoHandling() or PduR_RmIf_SingleBufferHandling().
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_PerformImmediateDestinationDataProcessing(PduR_RmGDestRomIdxOfRmDestRomType rmGDest, PduR_RmDestRomIterType rmDest,
                                                                                            P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info,
                                                                                            PduR_FmFifoElementRamWriteIdxOfFmFifoRamType fmFifoElementRamIdx, boolean useLock);
#endif

#if (PDUR_EXISTS_DEFERRED_PDURDESTPDUPROCESSINGOFRMGDESTROM == STD_ON)   /* COV_PDUR_VAR_ELISA_STD_OFF_XF */
/**********************************************************************************************************************
 * PduR_PerformDeferredDestinationDataProcessing
 *********************************************************************************************************************/
/*! \brief      Store transmit or indication request into queue.
 *  \details    -
 *  \param[in]  rmGDest                        Routing manager indirection Idx to global destination Pdu table.
 *  \param[in]  rmDest                         Routing manager indirection Idx.
 *  \return     E_OK                           No Queue overflow occured.
 *              E_NOT_OK                       Queue overflow occured.
 *  \note       The function is called in context PduR_RmIf_FifoHandling() or PduR_RmIf_SingleBufferHandling().
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_PerformDeferredDestinationDataProcessing(PduR_RmGDestRomIdxOfRmDestRomType rmGDest, PduR_RmDestRomIterType rmDest);
#endif

#if((PDUR_EXISTS_DIRECT_FIFO_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON) || (PDUR_EXISTS_T_T_FIFO_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON) || (PDUR_EXISTS_T_T_SINGLE_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON))
/**********************************************************************************************************************
 * PduR_Init_FiFoRoutingState
**********************************************************************************************************************/
/*! \brief     Initialize FiFo Routing State for communication interface routing.
 *  \details   -
 *  \pre       PduR_InitMemory() has been executed, if the startup code does not initialise variables.
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_Init_FiFoRoutingState(void);
#endif

#if ((PDUR_EXISTS_T_T_SINGLE_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON) || (PDUR_EXISTS_DIRECT_FIFO_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON) || (PDUR_EXISTS_T_T_FIFO_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON))
/**********************************************************************************************************************
 * PduR_Fm_FlushFiFo
 *********************************************************************************************************************/
/*! \brief      Reset Routing state. If FanIn routing is configured, reset FanIn RAM table.
 *  \details    -
 *  \param[in]  rmGDestRomIdx  routing manager indirection Idx.
 *  \note       The function is called in context PduR_RmIf_TxConfirmation or PduR_RmIf_TriggerTransmit
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_Fm_FlushFiFo(PduR_RmGDestRomIterType rmGDestRomIdx);
#endif

#if(PDUR_RMGDESTNTO1INFORAMIDXOFRMGDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_Rm_MultipleSourceHandler_Reset
 *********************************************************************************************************************/
/*! \brief      Reset RAM variables which hold the N:1 routing information.
 *  \details    -
 *  \param[in]  rmGDestRomIdx             Handle Id of the corresponding global Dest Pdu
 *  \note       The function is called  in context PduR_RmIf_MultipleSourceHandler_Transmit
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_Rm_MultipleSourceHandler_Reset(PduR_RmGDestRomIterType rmGDestRomIdx);
#endif

#if ((PDUR_EXISTS_T_T_FIFO_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON) || (PDUR_EXISTS_DIRECT_FIFO_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON) || (PDUR_EXISTS_T_T_SINGLE_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON))
/**********************************************************************************************************************
 * PduR_RmIf_CalcDlc
 *********************************************************************************************************************/
/*! \brief      Check if the DLC is shorter than the initial configured DLC. If the DLC is shorter the short DLC is
 *              returned. If the DLC is greater the initial DLC is returned.
 *  \details    -
 *  \param[in]  rmGDest           routing manager indirection Idx.
 *  \param[in]  info              contains the data pointer and its length.
 *  \note       The function is called in context of the PduR_RmIf_RxIndication API.
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(PduLengthType, PDUR_CODE) PduR_RmIf_CalcDlc(PduR_RmGDestRomIdxOfRmDestRomType rmGDest, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info);
#endif

#if((PDUR_EXISTS_DIRECT_FIFO_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON) || (PDUR_EXISTS_T_T_FIFO_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON) || (PDUR_EXISTS_T_T_SINGLE_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON))
/**********************************************************************************************************************
 * PduR_RmIf_CopyRxData
 *********************************************************************************************************************/
/*! \brief     Copy data to the buffer and performe state handling
 *  \details    -
 *  \param[in] fmFifoElementRamIdx   fifo element Idx.
 *  \param[in] pduLength             length to copy.
 *  \param[in] sduDataPtr            data pointer.
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_RmIf_CopyRxData(PduR_FmFifoElementRamIterType fmFifoElementRamIdx, PduR_BmTxBufferArrayRamIterType pduLength, SduDataPtrType sduDataPtr);
#endif

#if((PDUR_EXISTS_DIRECT_FIFO_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON) || (PDUR_EXISTS_T_T_FIFO_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON) || (PDUR_EXISTS_T_T_SINGLE_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON))
/**********************************************************************************************************************
 * PduR_RmIf_TransmitPreparation
 *********************************************************************************************************************/
/*! \brief      Perform buffer assignment and state handling before data transmission
 *  \details    -
 *  \param[in]  rmGDest routing manager indirection Idx.
 *  \param[in]  fmFifoElementRamIdx   fifo element Idx.
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_RmIf_TransmitPreparation(PduR_RmGDestRomIterType rmGDest, PduR_FmFifoElementRamIterType fmFifoElementRamIdx);
#endif

#if ((PDUR_EXISTS_DIRECT_FIFO_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON) || (PDUR_EXISTS_T_T_FIFO_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON))
/**********************************************************************************************************************
 * PduR_RmIf_FifoHandling
 *********************************************************************************************************************/
/*! \brief      Perform D-Fifo and TT- Fifo buffer and transmission handling
 *  \details    -
 *  \param[in]  rmDest   routing manager indirection Idx.
 *  \param[in]  rmGDest  routing manager indirection Idx to global destination Pdu table.
 *  \param[in]  info     Info pointer contains data and length
 *  \note       called in context of D-Fifo or TT- FiFo communication interface routing.
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_RmIf_FifoHandling(PduR_RmDestRomIterType rmDest, PduR_RmGDestRomIdxOfRmDestRomType rmGDest, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info);
#endif

#if(PDUR_EXISTS_IF_NOBUFFER_GATEWAY_ROUTINGTYPEOFRMDESTROM == STD_ON )
/**********************************************************************************************************************
   PduR_RmIf_RxIndicationNoBuffer
**********************************************************************************************************************/
/*! \brief       The function is called by the PduR to indicate the complete reception of a communication interface I-PDU.
 *  \details     The PDU Router evaluates the Gw I-PDU handle and performs appropriate handle and port conversion.
 *               The call is routed to an IF module using the appropriate I-PDU handle of the destination layer.
 *  \param[in]   rmDestIdx         ID of the received gateway I-PDU
 *  \param[in]   info              Payload information of the received I-PDU (pointer to data and data length).
 *  \return      none
 *  \pre         PduR_Init() is executed successfully.
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \trace       SPEC-1096, SPEC-2020151
 *  \note        The function is called by the PduR.
**********************************************************************************************************************/
LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_RmIf_RxIndicationNoBuffer(PduR_RmDestRomIterType rmDestIdx, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info);
#endif

#if((PDUR_EXISTS_T_T_FIFO_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON) || (PDUR_EXISTS_DIRECT_FIFO_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON) || (PDUR_EXISTS_T_T_SINGLE_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON))
/**********************************************************************************************************************
   PduR_RmIf_Forward2Buffer
**********************************************************************************************************************/
/*! \brief       The function is forwards the If Pdu to the corresponding buffer handling function.
 *  \param[in]   rmDestIdx         ID of the received gateway I-PDU
 *  \param[in]   info              Payload information of the received I-PDU (pointer to data and data length).
 *  \pre         PduR_Init() is executed successfully.
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \trace       SPEC-1096, SPEC-2020151
 *  \note        The function is called by the PduR.
**********************************************************************************************************************/
LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_RmIf_Forward2Buffer(PduR_RmDestRomIterType rmDestIdx, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info);
#endif

#if(PDUR_EXISTS_T_T_SINGLE_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON)
/**********************************************************************************************************************
   PduR_RmIf_RxIndicationTTSingleBuffer
**********************************************************************************************************************/
/*! \brief       The function is called by the PduR to indicate the complete reception of a communication interface I-PDU.
 *  \details     The PDU Router evaluates the Gw I-PDU handle and performs appropriate handle and port conversion.
 *               The call is routed to an IF module using the appropriate I-PDU handle of the destination layer.
 *  \param[in]   rmDestIdx         ID of the received gateway I-PDU
 *  \param[in]   info              Payload information of the received I-PDU (pointer to data and data length).
 *  \pre         PduR_Init() is executed successfully.
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \trace       SPEC-1096, SPEC-2020151
 *  \note        The function is called by the PduR.
**********************************************************************************************************************/
LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_RmIf_RxIndicationTTSingleBuffer(PduR_RmDestRomIterType rmDestIdx, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info);
#endif

#if((PDUR_EXISTS_T_T_FIFO_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON) || (PDUR_EXISTS_DIRECT_FIFO_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON))
/**********************************************************************************************************************
   PduR_RmIf_RxIndicationFifoBuffer
**********************************************************************************************************************/
/*! \brief       The function is called by the PduR to indicate the complete reception of a communication interface I-PDU.
 *  \details     The PDU Router evaluates the Gw I-PDU handle and performs appropriate handle and port conversion.
 *               The call is routed to an IF module using the appropriate I-PDU handle of the destination layer.
 *  \param[in]   rmDestIdx         ID of the received gateway I-PDU
 *  \param[in]   info              Payload information of the received I-PDU (pointer to data and data length).
 *  \return      none
 *  \pre         PduR_Init() is executed successfully.
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \trace       SPEC-1096, SPEC-2020151
 *  \note        The function is called by the PduR.
**********************************************************************************************************************/
LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_RmIf_RxIndicationFifoBuffer(PduR_RmDestRomIterType rmDestIdx, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info);
#endif

#if ((PDUR_EXISTS_DIRECT_FIFO_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON) || (PDUR_EXISTS_T_T_FIFO_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON))
/**********************************************************************************************************************
 * PduR_RmIf_FiFoDataProcessing
 *********************************************************************************************************************/
/*! \brief      Perform D-Fifo and TT- Fifo buffer and transmission handling
 *  \details    -
 *  \param[in]  rmDest               routing manager indirection Idx.
 *  \param[in]  rmGDest              routing manager indirection Idx to global destination Pdu table.
 *  \param[in]  fmFifoElementRamIdx  specific Fifo Element RAM index.
 *  \param[in]  pduLength            length to copy.
 *  \param[in]  sduDataPtr           data pointer.
 *  \note       called in context of D-Fifo or TT- FiFo communication interface routing.
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_RmIf_FiFoDataProcessing(PduR_RmDestRomIterType rmDest, PduR_RmGDestRomIterType rmGDest,
                                                                          PduR_FmFifoElementRamWriteIdxOfFmFifoRamType * fmFifoElementRamIdx,
                                                                          PduR_BmTxBufferArrayRamLengthOfBmTxBufferRomType pduLength, SduDataPtrType sduDataPtr);
#endif

#if(PDUR_EXISTS_T_T_SINGLE_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmIf_SingleBufferHandling
 *********************************************************************************************************************/
/*! \brief     perform Single buffer Fifo buffer and transmission handling ()
 *  \details    -
 *  \param[in] rmDest         routing manager indirection Idx.
 *  \param[in] rmGDest        routing manager indirection Idx to global destination Pdu table.
 *  \param[in] info           Info pointer contains data and length.
 *  \param[in] destPduInfo    Info pointer contains data and max Pdu length.
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_RmIf_SingleBufferHandling(PduR_RmDestRomIterType rmDest, PduR_RmGDestRomIdxOfRmDestRomType rmGDest, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info,
                                                                  P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) destPduInfo);
#endif

#if (PDUR_FMFIFORAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Fm_AssignFifoElement
 *********************************************************************************************************************/
/*! \brief       Helper function to allocate a FIFO element.
 *  \details    -
 *  \param[in]   fmFifoRamIdx        FIFO ID used for FIFO handling
 *  \param[out]  fmFifoElementRamIdx IDx to the next free FIFO Element.
 *  \return      E_OK                FIFO element could be allocated.
 *               E_NOT_OK            no FIFO element is available.
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_Fm_AssignFifoElement(PduR_FmFifoRamIterType fmFifoRamIdx,
                                                                       P2VAR(PduR_FmFifoElementRamWriteIdxOfFmFifoRamType, AUTOMATIC, PDUR_APPL_DATA) fmFifoElementRamIdx);
#endif

#if (((PDUR_TXCONFIRMATIONUSEDOFTXIF2UP == STD_ON) && ((PDUR_EXISTS_T_T_FIFO_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON) || (PDUR_EXISTS_DIRECT_FIFO_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON))) || (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON))
/**********************************************************************************************************************
 * PduR_Fm_Peek
 *********************************************************************************************************************/
/*!  \brief      Helper function which checks if any routing is ready to transmit in the FIFO
 *   \details    no dequeuing.
 *   \param[in]  fmFifoRamIdx        Index of the destination FIFO.
 *   \param[in]  fmFifoElementRamIdx Index of the current element which is used by the routing.
 *   \return     E_OK     if a routing is waiting for transmission.
 *               E_NOT_OK FIFO is empty
***********************************************************************************************************************/
LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_Fm_Peek(PduR_FmFifoRamIterType fmFifoRamIdx, P2VAR(PduR_FmFifoElementRamIterType, AUTOMATIC, PDUR_APPL_DATA) fmFifoElementRamIdx);
#endif

#if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_Fm_ActivateNext
 *********************************************************************************************************************/
/*! \brief       This function is called to activated the next pending element in the FiFo.
 *  \details    -
 *  \param[in]   fmFifoRamIdx        Index of the destination FIFO.
 *  \note        called in the functon FinishedReception or FinishedTransmission.
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_Fm_ActivateNext(PduR_FmFifoRamIterType fmFifoRamIdx);
#endif

#if ((PDUR_EXISTS_DIRECT_FIFO_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON) || (PDUR_EXISTS_T_T_FIFO_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON) || (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON))
/**********************************************************************************************************************
 * PduR_Fm_FreeFifoElement
 *********************************************************************************************************************/
/*! \brief      If no Tx Buffer is available for the FIFO element the FIFO must be freed.
 *  \details    -
 *  \param[in]  fmFifoRomIdx FIFO index.
 *  \param[in]  fmFifoElementRamWriteIdx previous write pointer (roll back).
 *  \note       The function is called in context of the PduR_RmTp_StartOfReception.
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_Fm_FreeFifoElement(PduR_FmFifoRomIterType fmFifoRomIdx, PduR_FmFifoElementRamWriteIdxOfFmFifoRamType fmFifoElementRamWriteIdx);
#endif

#if (PDUR_FMFIFORAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Fm_DissolveFifoElementTxBufferRelation
 *********************************************************************************************************************/
/*! \brief      ReleaseTx buffer Fifo Element connection in case of a shared buffer
 *  \details    -
 *  \param[in]  fmFifoElementRamIdx    Fifo State Id used for state handling
 *  \note       This function is called if the transmission is finished or aborted.
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_Fm_DissolveFifoElementTxBufferRelation(PduR_FmFifoElementRamIterType fmFifoElementRamIdx);
#endif

#if (PDUR_FMFIFORAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Fm_ReleaseFifoElement
 *********************************************************************************************************************/
/*! \brief      Reset Fifo Element.
 *  \details    -
 *  \param[in]  fmFifoElementRamIdx    Fifo State Id used for state handling.
 *  \note       This function is called if the transmission is finished or aborted.
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_Fm_ReleaseFifoElement(PduR_FmFifoElementRamIterType fmFifoElementRamIdx);
#endif

#if (PDUR_FMFIFORAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Fm_IsFifoElementAllocated
 *********************************************************************************************************************/
/*! \brief      Helper function to check if the queue element is in use.
 *  \details    -
 *  \param[in]  fmFifoElementRamIdx    Fifo State Id used for state handling.
 *  \return     E_OK                   if the queue is in use.
 *              E_NOT_OK               if the queue is not in use.
 *  \note                              This function is called if the transmission is finished or aborted.
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_Fm_IsFifoElementAllocated(PduR_FmFifoElementRamIterType fmFifoElementRamIdx);
#endif

#if (PDUR_METADATA_SUPPORT == STD_ON)
/**********************************************************************************************************************
 * PduR_RmTp_StartOfReceptionQueueMetaData
 *********************************************************************************************************************/
/*! \brief         This function writes meta data to the Tp buffer and adjusts the info->SduLength
 *                 if meta data is used.
 *  \details       -
 *  \param[in]     rmSrcIdx         Routing Manager Src Index
 *  \param[in]     pduLength        meta data length. (Meta data length are constant ROM)
 *  \param[in,out] sduDataPtr       Meta Data pointer .
 *  \param[out]    bufferSizePtr    pointer to data structure which will be used to return the size of the Pdu which
                                    can be copied to the buffer.
 *  \return        BUFREQ_OK        Buffer request was successful.
 *                 BUFREQ_E_NOT_OK  Currently no buffer available
 *  \note       This function is called in context of the StartOfReception.
 *             This function is called in context of the StartOfReceptionn and calls the
 *                                  PduR_Bm_PutData() to copy Meta data to the buffer.
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(BufReq_ReturnType, PDUR_CODE) PduR_RmTp_StartOfReceptionQueueMetaData(PduR_RmSrcRomIterType rmSrcIdx,
                                                                                        PduR_BmTxBufferArrayRamIterType pduLength,
                                                                                        SduDataPtrType sduDataPtr, P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) bufferSizePtr);
#endif

#if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmTp_LoAndUpTransmit
 *********************************************************************************************************************/
/*! \brief      This function triggers the transmission on the destination bus(es). In case of a
 *              1:N routing including a upper layer module StartOfReception/ CopyRxData/
 *              and the Indication API of the upper layer is called.
 *  \details    -
 *  \param[in]  rmSrcIdx         Src Id used for state handling
 *  \param[in]  rmDestIdx        Destination Id
 *  \return     E_OK             successful transmission.
 *              E_NOT_OK         transmission failing
 *  \note       This function is called in the transmit context.
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_RmTp_LoAndUpTransmit(PduR_RmSrcRomIterType rmSrcIdx, PduR_RmDestRomIterType rmDestIdx);
#endif

#if ((PDUR_UPTPOFMMROM == STD_ON) && (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON))
/**********************************************************************************************************************
 * PduR_RmTp_UpTransmit
 *********************************************************************************************************************/
/*! \brief      This function triggers the reception in an upper layer module in case of an
 *              1:N routing including an upper layer module StartOfReception/ CopyRxData/
 *              an the Indication API of the upper layer is called.
 *  \details    -
 *  \param[in]  rmSrcIdx                Routing Manager Src Idx.
 *  \param[in]  rmDestTpIdx             Routing Manager Dest Idx.
 *  \note                               This function is called in case of an 1:n routing.
 *  \trace      SPEC-2020176
 *  \return     BUFREQ_OK               Buffer request was successful.
 *              BUFREQ_E_NOT_OK         Currently no buffer available.
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_RmTp_UpTransmit(PduR_RmSrcRomIterType rmSrcIdx, PduR_RmDestRomIterType rmDestTpIdx);
#endif

#if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmTp_LoTransmit
 *********************************************************************************************************************/
/*! \brief      This function triggers the transmission in an lower layer module.
 *  \details    -
 *  \param[in]  rmSrcIdx       Routing Manager Src Index.
 *  \param[in]  rmDestTpIdx    Routing Manager Dest Index.
 *  \return     E_OK          Transmission successful.
 *              E_NOT_OK      Transmission not successful.
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_RmTp_LoTransmit(PduR_RmSrcRomIterType rmSrcIdx, PduR_RmDestRomIterType rmDestTpIdx);
#endif

#if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_Rm_ThresholdReached
 *********************************************************************************************************************/
/*! \brief      This function calculates the fill level and returns true if the configured threshold is reached.
 *  \details    -
 *  \param[in]  rmSrcIdx   Routing Manager Src Index
 *  \return                E_OK:     If threshold is reached.
 *                         E_NOT_OK: If threshold is not reached.
 *  \note                  The function is called in context of PduR_RmTp_StartOfReception or PduR_RmTp_CopyRxData.
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_Rm_ThresholdReached(PduR_RmSrcRomIterType rmSrcIdx);
#endif

#if ((PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON) || (PDUR_RMDESTROMUSEDOFRMDESTRPGROM == STD_ON))
 /**********************************************************************************************************************
 * PduR_TxSm_CancelTransmitPreparation
 *********************************************************************************************************************/
/*! \brief      This function is called to cancel all destination transmit calls of a source.
 *  \details    -
 *  \param[in]  fmFifoElementRamIdx     Fifo State Id used for state handling.
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_TxSm_CancelTransmitPreparation(PduR_FmFifoElementRamIterType fmFifoElementRamIdx);
#endif

#if((PDUR_EXISTS_TP_UNBUFFERED_TX_API_FWD_ROUTINGTYPEOFRMDESTROM == STD_ON) || (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON))
/**********************************************************************************************************************
   PduR_RmTp_MultipleSourceHandler_Transmit
**********************************************************************************************************************/
/*! \brief       The function is called by the PduR to trigger the transmission on the destination buses in case of a
 *                FanIn Transport Protocol Routing.
 *   \details     The PDU Router evaluates the Gw I-PDU handle and performs appropriate handle and port conversion.
 *                The call is routed to multiple TP module using the appropriate I-PDU handle of the destination layer.
 *   \param[in]   rmDestRomIdx             ID of the transmitted GwTp I-PDU.
 *   \param[in]   info                     the pointer to the data
 *   \pre         PduR_Init() is executed successfully.
 *   \context     TASK|ISR1|ISR2
 *   \reentrant   TRUE
 *   \synchronous TRUE
 *   \note        The function is called by the PduR.
**********************************************************************************************************************/
LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_RmTp_MultipleSourceHandler_Transmit(PduR_RmDestRomIterType rmDestRomIdx, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info);
#endif

#if((PDUR_EXISTS_TP_UNBUFFERED_TX_API_FWD_ROUTINGTYPEOFRMDESTROM == STD_ON) || (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON))
/**********************************************************************************************************************
  PduR_RmTp_MultipleSourceHandler_CopyTxData
**********************************************************************************************************************/
/*! \brief      This function is called by the PduR GwTp multiple times to query the transmit data of an I-PDU segment.
 *  \details    Each call to this function copies the next part of the transmit.
 *  \param[in]     rmGDestRomIdx            ID of the transmitted GwIf I-PDU
 *  \param[in]     info                        Pointer to the destination buffer and the number of bytes to copy.
 *                                          In case of gateway the PDU Router module will copy otherwise the source upper layer
 *                                          module will copy the data. If not enough transmit data is available, no data is copied.
 *
 *                                          A copy size of 0 can be used to indicate state changes in the retry parameter.
 *  \param[in]     retry                       not supported
 *  \param[out]    availableDataPtr            Indicates the remaining number of bytes that are available in the PduR Tx buffer.
 *                                          AvailableTxDataCntPtr can be used by TP modules that support dynamic payload lengths
 *                                          (e.g. Iso FrTp) to determine the size of the following CFs.
 *  \return     BufReq_ReturnType
 *              BUFREQ_OK                   The data has been copied to the transmit buffer successfully.
 *              BUFREQ_E_NOT_OK             PduR_Init() has not been called
 *                                          or the GwTpTxPduId is not valid
 *                                          or the GwTpTxPduId is not forwarded in this identity
 *                                          or the info is not valid
 *                                          or the request was not accepted by the upper layer and no data has been copied.
 *              BUFREQ_E_BUSY               The request cannot be processed because the TX data is not available
 *                                          and no data has been copied. The TP layer might retry later the copy process.
 *  \pre         PduR_Init() is executed success fully.
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \note        The function is called by the PduR GwTp.
**********************************************************************************************************************/
LOCAL_INLINE FUNC(BufReq_ReturnType, PDUR_CODE) PduR_RmTp_MultipleSourceHandler_CopyTxData(PduR_RmGDestRomIdxOfTxTp2SrcType rmGDestRomIdx, P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info,
                                                                                           P2VAR(RetryInfoType, AUTOMATIC, PDUR_APPL_DATA) retry, P2VAR(PduLengthType, AUTOMATIC,
                                                                                                                                                        PDUR_APPL_DATA) availableDataPtr);
#endif

#if((PDUR_EXISTS_TP_UNBUFFERED_TX_API_FWD_ROUTINGTYPEOFRMDESTROM == STD_ON) || (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON))
/**********************************************************************************************************************
  PduR_RmTp_MultipleSourceHandler_TpTxConfirmation
**********************************************************************************************************************/
/*! \brief        The function is called to confirm or abort a transport protocol I-PDU routing.
 *  \details      The PDU Router evaluates the Gw I-PDU handle and performs appropriate handle and port conversion.
 *                The call is routed to an upper Tp module or to the gateway depending on the pending Confirmation.
 *   \param[in]   rmGDestRomIdx          ID of the transmitted GwIf I-PDU
 *   \param[out]  result    not used, but expected due to function pointer table type
 *   \pre         PduR_Init() is executed successfully.
 *   \context     TASK|ISR1|ISR2
 *   \reentrant   TRUE
 *   \synchronous TRUE
 **********************************************************************************************************************/
LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_RmTp_MultipleSourceHandler_TpTxConfirmation(PduR_RmGDestRomIdxOfTxTp2SrcType rmGDestRomIdx, Std_ReturnType result);
#endif

#if((PDUR_TPCANCELTRANSMITSUPPORTEDOFMMROM == STD_ON) && (PDUR_EXISTS_TP_UNBUFFERED_TX_API_FWD_ROUTINGTYPEOFRMDESTROM == STD_ON))
/**********************************************************************************************************************
   PduR_RmTp_MultipleSourceHandler_CancelTransmit
**********************************************************************************************************************/
/*! \brief        The function is called by the PduR to cancel the transmission on the destination buses in case of a
 *                FanIn Transport Protocol Routing.
 *   \details     The PDU Router evaluates the Gw I-PDU handle and performs appropriate handle and port conversion.
 *                The call is routed to multiple TP module using the appropriate I-PDU handle of the destination layer.
 *   \param[in]   rmDestRomIdx             ID of the transmitted GwTp I-PDU.
 *   \pre         PduR_Init() is executed successfully.
 *   \context     TASK|ISR1|ISR2
 *   \reentrant   TRUE
 *   \synchronous TRUE
 *   \note        The function is called by the PduR.
**********************************************************************************************************************/
LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_RmTp_MultipleSourceHandler_CancelTransmit(PduR_RmDestRomIterType rmDestRomIdx);
#endif

#if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
  PduR_RmTp_TpTxConfirmation
**********************************************************************************************************************/
/** \brief      The function confirms a successful transmission of a GwTp TX SDU or to report an error that
 *              occurred during transmission.
 *  \details    -
 *  \param[in]   rmGDestRomIdx              lower layer Tp Handle that will be converted in the internal gateway handle.
 *  \param[out]  result                          Result of the TP transmission\n
 *               E_OK                            The TP transmission has been completed successfully.\n
 *               E_NOT_OK                        The PDU Router is in the PDUR_UNINIT state\n
 *                                              or the id is not valid\n
 *                                              or the id is not forwarded in this identity\n
 *                                              or the request was not accepted by the destination upper layer.\n
 *  \pre         PduR_Init() is executed successfully.
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \note        The function is called by the PduR GwTp.
***********************************************************************************************************************/
LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_RmTp_TpTxConfirmation(PduR_RmGDestRomIdxOfTxTp2SrcType rmGDestRomIdx, Std_ReturnType result);
#endif

#if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
  PduR_RmTp_CopyTxData
**********************************************************************************************************************/
/*! \brief      This function is called by the PduR GwTp to query the transmit data of an I-PDU segment.
 *  \details    Each call to this function copies the next part of the transmit.
 *  \param[in]      rmGDestRomIdx       ID of the GwTp I-PDU that will be transmitted.
 *  \param[in]      info              Pointer to the destination buffer and the number of bytes to copy.
 *                                In case of gateway the PDU Router module will copy otherwise the source upper layer
 *                                module will copy the data. If not enough transmit data is available, no data is copied.
 *
 *                                A copy size of 0 can be used to indicate state changes in the retry parameter.
 *  \param[in]  retry             not supported
 *  \param[out] availableDataPtr  Indicates the remaining number of bytes that are available in the PduR Tx buffer.
 *                                AvailableTxDataCntPtr can be used by TP modules that support dynamic payload lengths
 *                                (e.g. Iso FrTp) to determine the size of the following CFs.
 *  \return     BufReq_ReturnType
 *              BUFREQ_OK         The data has been copied to the transmit buffer successful.
 *              BUFREQ_E_NOT_OK   PduR_Init() has not been called
 *                                or the GwTpTxPduId is not valid
 *                                or the GwTpTxPduId is not forwarded in this identity
 *                                or the info is not valid
 *                                or the request was not accepted by the upper layer and no data has been copied.
 *              BUFREQ_E_BUSY     The request cannot be processed because the TX data is not available
 *                                and no data has been copied. The TP layer might retry later the copy process.
 *  \pre         PduR_Init() is executed success fully.
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \trace       SPEC-1096, SPEC-2020151
 *  \note        The function is called by the PduR GwTp.
**********************************************************************************************************************/
LOCAL_INLINE FUNC(BufReq_ReturnType, PDUR_CODE) PduR_RmTp_CopyTxData(PduR_RmGDestRomIdxOfTxTp2SrcType rmGDestRomIdx,
                                                                     P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info,
                                                                     P2VAR(RetryInfoType, AUTOMATIC, PDUR_APPL_DATA) retry, P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) availableDataPtr);
#endif

#if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
  PduR_RmTp_StartOfReception
**********************************************************************************************************************/
/** \brief        This function will be called by the GwTp at the start of receiving an I-PDU.
 *  \details      The I-PDU might be fragmented into multiple N-PDUs
 *                (FF with one or more following CFs) or might consist of a single N-PDU (SF).
 *   \param[in]       rmSrcIdx          Routing Manager source Id
 *   \param[in]   info              Pointer to the buffer (SduDataPtr) contains MetaData if this feature is enabled
 *   \param[in]   TpSduLength       Length of the entire GwTp TP SDU which will be received
 *   \param[out]   bufferSizePtr     Pointer to the receive buffer in the receiving module.
 *                                   This parameter will be used to compute Block Size (BS) in the transport protocol module.
 *   \return      BufReq_ReturnType
 *                BUFREQ_OK         Connection has been accepted. RxBufferSizePtr indicates the available receive buffer.
 *                BUFREQ_E_NOT_OK   PduR_Init() has not been called
 *                                  or the GwTpRxPduId is not valid
 *                                  or the GwTpRxPduId is not forwarded in this identity
 *                                  or the info is not valid
 *                                  or the request was not accepted by the upper layer.
 *   \pre         PduR_Init() is executed successfully.
 *   \context     TASK|ISR1|ISR2
 *   \reentrant   TRUE
 *   \synchronous TRUE
 *   \trace       SPEC-1096, SPEC-2020151
 *   \note        The function is called by the PduR.
***********************************************************************************************************************/
LOCAL_INLINE FUNC(BufReq_ReturnType, PDUR_CODE) PduR_RmTp_StartOfReception(PduR_RmSrcRomIdxOfRxTp2DestType rmSrcIdx,
                                                                           P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info,
                                                                           PduLengthType TpSduLength, P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) bufferSizePtr);
#endif

#if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
  PduR_RmTp_CopyRxData
**********************************************************************************************************************/
/*! \brief     This function is called by the PduR if data has to be to copied to the receiving module.
 *  \details   Several calls may be made during one transportation of an I-PDU.
 *  \param[in]   rmSrcIdx         Routing Manager source Id
 *  \param[in]   info               Pointer to the buffer (SduDataPtr) and its length (SduLength)
 *                                containing the data to be copied by PDU Router module in case of gateway
 *                                or upper layer module in case of reception.
 *  \param[out]  bufferSizePtr     Available receive buffer after data has been copied.
 *  \return    BufReq_ReturnType
 *             BUFREQ_OK         Buffer request accomplished successful.
 *             BUFREQ_E_NOT_OK   PduR_Init() has not been called
 *                                  or the GwTpRxPduId is not valid
 *                                  or the GwTpRxPduId is not forwarded in this identity
 *                                  or the info is not valid
 *                                  or the request was not accepted by the upper layer.
 *             BUFREQ_E_BUSY     Currently no buffer of the requested size is available.
 *                               It's up the requester to retry request for a certain time.
 *                               The request was not accepted by the upper layer.
 *             BUFREQ_E_OVFL     The upper TP module is not able to receive the number of bytes.
 *                               The request was not accepted by the upper layer.
 *  \pre         PduR_Init() is executed successfully.
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \trace       SPEC-1096, SPEC-2020151
 *  \note        The function is called by the PduR.
**********************************************************************************************************************/
LOCAL_INLINE FUNC(BufReq_ReturnType, PDUR_CODE) PduR_RmTp_CopyRxData(PduR_RmSrcRomIdxOfRxTp2DestType rmSrcIdx, P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info,
                                                                     P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) bufferSizePtr);
#endif

#if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
  PduR_RmTp_TpRxIndication
**********************************************************************************************************************/
/*! \brief      The function is called by the PduR GwTp to indicate the complete reception of a GwTp SDU
 *              or to report an error that occurred during reception.
 *  \details    -
 *              The PDU Router evaluates the Gw I-PDU handle and performs appropriate handle and port conversion.
 *              The call is routed to an upper TP module using the appropriate I-PDU handle of the destination layer.
 *  \param[in]      rmSrcIdx                    Routing Manager source Id
 *  \param[out] result                          Result of the TP reception.\n
 *              E_OK                            The TP reception has been completed successfully.\n
 *              E_NOT_OK                        The PDU Router is in the PDUR_UNINIT state\n
 *                                              or the id is not valid\n
 *                                              or the id is not forwarded in this identity\n
 *                                              or the request was not accepted by the destination upper layer.\n
 *  \return      none
 *  \pre         PduR_Init() is executed successfully.
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \trace       SPEC-1096, SPEC-2020151
 *  \note        The function is called by the PduR GwTp.
***********************************************************************************************************************/
LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_RmTp_TpRxIndication(PduR_RmSrcRomIdxOfRxTp2DestType rmSrcIdx, Std_ReturnType result);
#endif

#if (PDUR_RMDESTROMIFIDXOFRMDESTRPGROM == STD_ON)
/**********************************************************************************************************************
 * PduR_DisableIfRoutingAction
 *********************************************************************************************************************/
/*! \brief      This function flushes the Interface queue if the queue is in use while the RoutingPathGroup
 *              is disabled.
 *  \details     -
 *  \param[in]  rmDestRomIdx  Gateway Id used for state handling.
 *  \note       The function is called in the context of PduR_DisableIfRouting.
 *              Called in context of DisableRouting().
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_DisableIfRoutingAction(PduR_RmDestRomIfIdxOfRmDestRpgRomType rmDestRomIdx);
#endif

#if (PDUR_SMDATAPLANEROM == STD_ON)
/**********************************************************************************************************************
 * PduR_Sm_Init
 *********************************************************************************************************************/
/*! \brief      This function initializes the switching manager sub-module.
 *  \details     -
 *  \pre        PduR_InitMemory() has been executed, if the start up code does not initialise variables.
 *  \note       The function must be called on task level and has not to be interrupted
 *              by other administrative function calls.
 *  \warning    PduR_Init shall not pre-empt any PDUR function.
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_Sm_Init(void);
#endif
/**********************************************************************************************************************
 * PduR_Sm_SaTaFromMetaDataCalculationStrategy_GetSa
 *********************************************************************************************************************/
/*! \brief       This function extract the source address from the meta data.
 *  \details     -
 *  \param       smSaTaFromMetaDataCalculationStrategyRomIdx Source Target address Rom Idx
 *  \param       metaData  Meta data contains Source Target address
 *  \return      PduR_SmSaType   metaData + offset & mask;
 *  \pre         PduR_InitMemory() has been executed, if the start up code does not initialise variables.
 *  \note        Smart Learning.
 *********************************************************************************************************************/
#if(PDUR_SMSATAFROMMETADATACALCULATIONSTRATEGYROM == STD_ON)
LOCAL_INLINE FUNC(PduR_SmSaType, PDUR_CODE) PduR_Sm_SaTaFromMetaDataCalculationStrategy_GetSa(PduR_SmSaTaFromMetaDataCalculationStrategyRomIterType smSaTaFromMetaDataCalculationStrategyRomIdx,
                                                                                              uint32 metaData);
#endif
/**********************************************************************************************************************
 * PduR_Sm_SaTaFromMetaDataCalculationStrategy_GetTa
 *********************************************************************************************************************/
/*! \brief       This function extract the target address from the meta data.
 *  \details     -
 *  \param       smSaTaFromMetaDataCalculationStrategyRomIdx Source Target address Rom Idx.
 *  \param       metaData  Meta data contains Source Target address.
 *  \return      PduR_SmSaType   metaData + offset & mask.
 *  \pre         PduR_InitMemory() has been executed, if the start up code does not initialise variables.
 *  \note     Smart Learning.
 *********************************************************************************************************************/
#if(PDUR_SMSATAFROMMETADATACALCULATIONSTRATEGYROM == STD_ON)
LOCAL_INLINE FUNC(PduR_SmTaType, PDUR_CODE) PduR_Sm_SaTaFromMetaDataCalculationStrategy_GetTa(PduR_SmSaTaFromMetaDataCalculationStrategyRomIterType smSaTaFromMetaDataCalculationStrategyRomIdx,
                                                                                              uint32 metaData);
#endif
/**********************************************************************************************************************
 * PduR_Sm_GetMetaData
 *********************************************************************************************************************/
/*! \brief       This function extract meta data.
 *  \details     -
 *  \param       info contains metadata.
 *  \param       metaDataLength meta data length.
 *  \return      meta data.
 *  \pre         PduR_InitMemory() has been executed, if the start up code does not initialise variables.
 *  \note        Smart Learning.
 *********************************************************************************************************************/
#if(PDUR_SMDATAPLANEROM == STD_ON)
LOCAL_INLINE FUNC(uint32, PDUR_CODE) PduR_Sm_GetMetaData(P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info, uint8 metaDataLength);
#endif
 /*********************************************************************************************************************
 * PduR_Sm_GetMetaData
 *********************************************************************************************************************/
/*! \brief       This function updates the Fib table while a routing was learned.
 *  \details     -
 *  \param       sourceAdress    source adress
 *  \param       smDataPlaneIdx  Data plan Idx
 *  \param       learnedConnectionId  learned connection Id.
 *  \pre         PduR_InitMemory() has been executed, if the start up code does not initialise variables.
 *  \note        Smart Learning
 *********************************************************************************************************************/
#if(PDUR_SMDATAPLANEROM == STD_ON)
LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_Sm_UpdateFib(PduR_SmDataPlaneRomIterType smDataPlaneIdx, PduR_SmSaType sourceAdress, PduR_ConnectionIdOfSmSrcRomType learnedConnectionId);
#endif
/**********************************************************************************************************************
 * PduR_Sm_CheckLearned
 *********************************************************************************************************************/
/*! \brief       This function checks if a routing is learned.
 *  \details     -
 *  \param       smDataPlaneIdx   Data plane Idx.
 *  \param       targetAdress     target adress.
 *  \param       destConnection   destination connection Id.
 *  \return      PduR_FilterReturnType
 *                - PDUR_FILTER_PASS  Let the routing pass.
 *                - PDUR_FILTER_BLOCK Block the routing, it is not the learned destination connection
 *  \pre         PduR_InitMemory() has been executed, if the start up code does not initialise variables.
 *  \note        Smart Learning
 *********************************************************************************************************************/
#if(PDUR_SMDATAPLANEROM == STD_ON)
LOCAL_INLINE FUNC(PduR_FilterReturnType, PDUR_CODE) PduR_Sm_CheckLearned(PduR_SmDataPlaneRomIterType smDataPlaneIdx, PduR_SmTaType targetAdress, PduR_ConnectionIdOfSmGDestRomType destConnection);
#endif
#if ((PDUR_TRIGGERTRANSMITSUPPORTEDOFRMSRCROM == STD_ON) || (PDUR_EXISTS_T_T_SINGLE_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON) || (PDUR_EXISTS_T_T_FIFO_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON))
 /**********************************************************************************************************************
  PduR_RmIf_MultipleSourceHandler_TriggerTransmit
**********************************************************************************************************************/
/*! \brief       The function is called by the PduR to request the PduR TX I-PDU data before transmission in case of
 *               a FanIn routing.
 *  \details     The PDU Router evaluates the Gw I-PDU handle and performs appropriate handle and port conversion.
 *               The call is routed to an upper IF module or to the gateway using the appropriate I-PDU handle.
 *  \param[in]   rmGDestRomIdx        ID of the transmitted GwIf I-PDU
 *  \param[in]  info                        Payload information of the received I-PDU (pointer to data and data length).
 *  \return      Std_ReturnType    E_OK:     The SDU has been copied and the SduLength indicates
 *                                           the number of copied bytes.
 *                                 E_NOT_OK: The SDU has not been copied and the SduLength has not been set.
 *  \pre         PduR_Init() is executed successfully.
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \note        The function is called by the PduR.
***********************************************************************************************************************/
LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_RmIf_MultipleSourceHandler_TriggerTransmit(PduR_RmGDestRomIdxOfTxIf2UpType rmGDestRomIdx, P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info);
#endif

 /**********************************************************************************************************************
  PduR_Rm_GetSrcDestPdu
**********************************************************************************************************************/
/*! \brief       This functions returns the RmDest index of the last transmitted source DestPdu.
 *  \param[in]   rmGDestRomIdx        ID of the globalPdu
 *  \param[out]  rmDestRomIdx         ID of the source DestPdu
 *  \return      Std_ReturnType    E_OK:     The SDU has been copied and the SduLength indicates
 *                                           the number of copied bytes.
 *                                 E_NOT_OK: The SDU has not been copied and the SduLength has not been set.
 *  \pre         PduR_Init() is executed successfully.
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \note        The function is called by the PduR.
***********************************************************************************************************************/
LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_Rm_GetSrcDestPdu(PduR_RmGDestRomIterType rmGDestRomIdx, P2VAR(PduR_RmDestRomIterType, AUTOMATIC, PDUR_APPL_DATA) rmDestRomIdx);

#if (PDUR_TXCONFIRMATIONUSEDOFTXIF2UP == STD_ON)
/**********************************************************************************************************************
  PduR_RmIf_MultipleSourceHandler_TxConfirmation
**********************************************************************************************************************/
/*! \brief        The function is called by the PduR to indicate the complete transmission of a communication interface I-PDU.
 *  \details      The PDU Router evaluates the Gw I-PDU handle and performs appropriate handle and port conversion.
 *                The call is routed to an upper IF module or to the gateway depending on the pending Confirmation.
 *   \param[in]   rmGDestRomIdx           ID of the transmitted GwIf I-PDU
 *   \return      none
 *   \pre         PduR_Init() is executed successfully.
 *   \context     TASK|ISR1|ISR2
 *   \reentrant   TRUE
 *   \synchronous TRUE
 *   \note        The function is called by the PduR.
 **********************************************************************************************************************/
LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_RmIf_MultipleSourceHandler_TxConfirmation(PduR_RmGDestRomIdxOfTxIf2UpType rmGDestRomIdx);
#endif
#if ((PDUR_IFCANCELTRANSMITSUPPORTEDOFMMROM == STD_ON) && (PDUR_EXISTS_IF_UNBUFFERED_TX_API_FWD_ROUTINGTYPEOFRMDESTROM == STD_ON))
/**********************************************************************************************************************
 * PduR_RmIf_MultipleSourceHandler_CancelTransmit
 *********************************************************************************************************************/
/*! \brief        The function is called by the PduR to cancel the transmission on the destination buses in case of a
 *                FanIn Transport Protocol Routing.
 *  \details      The PDU Router evaluates the Gw I-PDU handle and performs appropriate handle and port conversion.
 *                The call is routed to multiple TP module using the appropriate I-PDU handle of the destination layer.
 *  \param[in]    rmDestRomIdx           ID of the destination Pdu
 *  \return       Std_ReturnType            cancelation successful.
 *  \pre          PduR_Init() is executed successfully.
 *  \context      TASK|ISR1|ISR2
 *  \reentrant    TRUE
 *  \synchronous  TRUE
 *  \note         The function is called by the PduR.
 **********************************************************************************************************************/
LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_RmIf_MultipleSourceHandler_CancelTransmit(PduR_RmDestRomIterType rmDestRomIdx);
#endif
#if( (PDUR_EXISTS_IF_UNBUFFERED_TX_API_FWD_ROUTINGTYPEOFRMDESTROM == STD_ON) || (PDUR_EXISTS_IF_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON) || (PDUR_EXISTS_IF_NOBUFFER_GATEWAY_ROUTINGTYPEOFRMDESTROM == STD_ON))
/**********************************************************************************************************************
  PduR_RmIf_MultipleSourceHandler_Transmit
**********************************************************************************************************************/
/*! \brief        The function is called by the PduR to trigger the transmission on the destination buses in case of a
 *                FanIn routing.
 *   \details     The PDU Router evaluates the Gw I-PDU handle and performs appropriate handle and port conversion.
 *                The call is routed to multiple IF module using the appropriate I-PDU handle of the destination layer.
 *   \param[in]   rmDestRomIdx              ID of the destination Pdu
 *   \param[in]   info                      Pointer to the destination buffer and the number of bytes to copy.
 *   \param[in]   useLock                   shall the 'transmissionActive' Flag be set and considered for this transmission
 *   \return      Std_ReturnType            Result of the multiple transmission.
 *                            E_OK          The transmission was successfully .\n
 *                            E_NOT_OK      The transmission fails.
 *   \pre         PduR_Init() is executed successfully.
 *   \context     TASK|ISR1|ISR2
 *   \reentrant   TRUE
 *   \synchronous TRUE
 *   \note        The function is called by the PduR.
**********************************************************************************************************************/
LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_RmIf_MultipleSourceHandler_Transmit(PduR_RmDestRomIterType rmDestRomIdx, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info, boolean useLock);
#endif

#if((PDUR_TXCONFIRMATIONUSEDOFTXIF2UP == STD_ON) && ((PDUR_EXISTS_T_T_FIFO_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON) || (PDUR_EXISTS_DIRECT_FIFO_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON)))
/**********************************************************************************************************************
  PduR_RmIf_TxConfirmation
**********************************************************************************************************************/
/*! \brief       The function is called by the PduR to indicate the complete transmission of a communication interface I-PDU.
 *  \details     The PDU Router evaluates the Gw I-PDU handle and performs appropriate handle and port conversion.
 *               The call is routed to an upper IF module using the appropriate I-PDU handle of the destination layer.
 *  param[in]    rmGDestRomIdx           ID of the transmitted GwIf I-PDU
 *  \return      none
 *  \pre         PduR_Init() is executed successfully.
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \note        The function is called by the PduR.
***********************************************************************************************************************/
LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_RmIf_TxConfirmation(PduR_RmGDestRomIdxOfTxIf2UpType rmGDestRomIdx);
#endif

#if((PDUR_EXISTS_T_T_SINGLE_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON) ||(PDUR_EXISTS_T_T_FIFO_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON))
/**********************************************************************************************************************
  PduR_RmIf_TriggerTransmit
**********************************************************************************************************************/
/*! \brief       The function is called by the PduR to request the PduR TX I-PDU data before transmission.
 *  \details     The PDU Router evaluates the Gw I-PDU handle and performs appropriate handle and port conversion.
 *               The call is routed to an upper IF module using the appropriate I-PDU handle of the destination layer.
 *  \param[in]   rmDestIdx         ID of the GwIf I-PDU that will be transmitted.
 *  \param[in]   info              Payload information of the received I-PDU (pointer to data and data length).
 *  \return      Std_ReturnType    E_OK:     The SDU has been copied and the SduLength indicates
 *                                           the number of copied bytes.
 *                                 E_NOT_OK: The SDU has not been copied and the SduLength has not been set.
 *  \pre         PduR_Init() is executed successfully.
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous FALSE
 *  \trace       SPEC-1096, SPEC-2020151
 *  \note        The function is called by the PduR.
**********************************************************************************************************************/
LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_RmIf_TriggerTransmit(PduR_RmDestRomIterType rmDestIdx, CONSTP2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info);
#endif

#if (PDUR_EXISTS_IF_NOBUFFER_GATEWAY_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
  PduR_RmIf_ProcessNoBufferedGwRouting
**********************************************************************************************************************/
/*! \brief       The function is called by the PduR to process no buffered gateway If Pdus
 *  \param[in]   rmDestIdx         ID of the GwIf I-PDU that will be transmitted.
 *  \param[in]   info              Payload information of the received I-PDU (pointer to data and data length).
 *  \return      Std_ReturnType    E_OK:     The SDU has been copied and the SduLength indicates
 *                                           the number of copied bytes.
 *                                 E_NOT_OK: The SDU has not been copied and the SduLength has not been set.
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
**********************************************************************************************************************/
LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_RmIf_ProcessNoBufferedGwRouting(PduR_RmDestRomIterType rmDestIdx, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info);
#endif

#if (PDUR_EXISTS_IF_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
  PduR_RmIf_ProcessBufferedRouting
**********************************************************************************************************************/
/*! \brief       The function is called by the PduR to process buffered If Pdus
 *  \param[in]   rmSrcIdx          Source Id.
 *  \param[in]   rmDestIdx         Destintaion Id.
 *  \param[in]   rmGDestRomIdx     G Dest Rom Table Id.
 *  \param[in]   info              Payload information of the received I-PDU (pointer to data and data length).
 *  \return      Std_ReturnType    E_OK:     The SDU has been copied and the SduLength indicates
 *                                           the number of copied bytes.
 *                                 E_NOT_OK: The SDU has not been copied and the SduLength has not been set.
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
**********************************************************************************************************************/
LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_RmIf_ProcessBufferedRouting(PduR_RmSrcRomIterType rmSrcIdx, PduR_RmDestRomIterType rmDestIdx, PduR_RmGDestRomIterType rmGDestRomIdx, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info);
#endif

#if ((PDUR_IFCANCELTRANSMITSUPPORTEDOFMMROM == STD_ON) || (PDUR_TPCANCELTRANSMITSUPPORTEDOFMMROM == STD_ON))
/**********************************************************************************************************************
 * PduR_Rm_CancelTransmit_MultiDest
 *********************************************************************************************************************/
/*!
 * \brief    The function calls the CancelTransmit function for every destination
 * \details     -
 * \param[in]    rmSrcIdx            internal RmSrcRom index
 * \return   Std_ReturnType
 *           E_OK              Cancellation was executed successfully by all the destination modules.
 *           E_NOT_OK          Cancellation was rejected by the destination module.
 * \pre      PduR_Init() is executed successfully.
 * \context  This function can be called on interrupt and task level and has not to be interrupted by other
 * \reentrant   TRUE
 * \synchronous TRUE
**********************************************************************************************************************/
LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_Rm_CancelTransmit_MultiDest(PduR_RmSrcRomIterType rmSrcIdx);
#endif
/**********************************************************************************************************************
 * LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * GLOBAL AND LOCAL FUNCTIONS
 *********************************************************************************************************************/
#define PDUR_START_SEC_CODE
#include "MemMap.h"    /* PRQA S 5087 */        /* MD_MSR_19.1 */

#if(PDUR_VERSION_INFO_API == STD_ON)
/**********************************************************************************************************************
 * PduR_GetVersionInfo
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, PDUR_APPL_DATA) versionInfo)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = PDUR_E_NO_ERROR;
# if (PDUR_DEV_ERROR_DETECT == STD_ON)  /* COV_PDUR_VAR_DEV_ERROR_DETECT */
  /* Check parameter 'ConfigPtr' */
  if(versionInfo == NULL_PTR)
  {
    errorId = PDUR_E_PARAM_POINTER;
  }
  else
# endif
  {
    versionInfo->vendorID = (uint16) PDUR_VENDOR_ID;    /* SBSW_PDUR_GETVERSION_PARAM */
    versionInfo->moduleID = (uint8) PDUR_MODULE_ID;     /* SBSW_PDUR_GETVERSION_PARAM */
    versionInfo->sw_major_version = (uint8) PDUR_SW_MAJOR_VERSION;      /* SBSW_PDUR_GETVERSION_PARAM */
    versionInfo->sw_minor_version = (uint8) PDUR_SW_MINOR_VERSION;      /* SBSW_PDUR_GETVERSION_PARAM */
    versionInfo->sw_patch_version = (uint8) PDUR_SW_PATCH_VERSION;      /* SBSW_PDUR_GETVERSION_PARAM */
  }
  /* ----- Development Error Report --------------------------------------- */
# if (PDUR_DEV_ERROR_REPORT == STD_ON)
  if(errorId != PDUR_E_NO_ERROR)
  {
    PduR_Det_ReportError(PDUR_FCT_VERSIONINFO, errorId);
  }
# else
  PDUR_DUMMY_STATEMENT(errorId);        /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
# endif
}       /* End of PduR_GetVersionInfo() */
#endif

/**********************************************************************************************************************
 * PduR_GetConfigurationId
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *********************************************************************************************************************/
FUNC(PduR_PBConfigIdType, PDUR_CODE) PduR_GetConfigurationId(void)
{
  uint16 configID = 0U;
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = PDUR_E_NO_ERROR;
  if(PduR_IsInitialized() == FALSE)
  {
    errorId = PDUR_E_INVALID_REQUEST;
  }
  else
  {
    configID = PduR_GetConfigId();
  }
  /* ----- Development Error Report --------------------------------------- */
#if (PDUR_DEV_ERROR_REPORT == STD_ON)
  if(errorId != PDUR_E_NO_ERROR)
  {
    PduR_Det_ReportError(PDUR_FCT_CONFIGURATIONID, errorId);
  }
#else
  PDUR_DUMMY_STATEMENT(errorId);        /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
#endif
  return configID;
}       /* End of PduR_GetConfigurationId() */

/* Upper Layer Interface APIs */
#if (PDUR_TX2LO == STD_ON)
/**********************************************************************************************************************
 * PduR_UpTransmit
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
 *********************************************************************************************************************/
FUNC(Std_ReturnType, PDUR_CODE) PduR_UpTransmit(PduIdType id, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = PDUR_E_NO_ERROR;
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Development Error Checks ------------------------------------- */
  /* Check initialization state of the component */
  if(PduR_IsInitialized() == FALSE)
  {
    errorId = PDUR_E_INVALID_REQUEST;
  }
# if (PDUR_DEV_ERROR_DETECT == STD_ON)  /* COV_PDUR_VAR_DEV_ERROR_DETECT */
  else if((id >= PduR_GetSizeOfTx2Lo())
#  if (PDUR_INVALIDHNDOFTX2LO == STD_ON)
          || (PduR_IsInvalidHndOfTx2Lo(id))
#  endif
    )
  {
    errorId = PDUR_E_PDU_ID_INVALID;
  }
# endif
  else
  {
    /* ----- Implementation ----------------------------------------------- */
# if (PDUR_BSWMPDURTRANSMITCALLBACKOFTX2LO == STD_ON)
    if(PduR_IsBswMPduRTransmitCallbackOfTx2Lo(id))
    {
      BswM_PduR_Transmit(id, info);     /* SBSW_PDUR_EXTERNAL_API_CALL_FORWARDING_ID_AND_PTR */
    }
# endif
    {
      retVal = PduR_GetRmTransmitFctPtr(PduR_GetRmTransmitFctPtrIdxOfTx2Lo(id)) (PduR_GetRmSrcRomIdxOfTx2Lo(id), info); /* SBSW_PDUR_EXTERNAL_API_CALL_FORWARDING_ID_AND_PTR */
    }
  }

  /* ----- Development Error Report --------------------------------------- */
# if (PDUR_DEV_ERROR_REPORT == STD_ON)
  if(errorId != PDUR_E_NO_ERROR)
  {
    PduR_Det_ReportError(PDUR_FCT_TX, errorId);
  }
# else
  PDUR_DUMMY_STATEMENT(errorId);        /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
# endif

  PDUR_DUMMY_STATEMENT(id);     /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(info);   /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */

  return retVal;
}
#endif

#if(PDUR_EXISTS_TP_UNBUFFERED_TX_API_FWD_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmTp_Transmit_MultiDest
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
FUNC(Std_ReturnType, PDUR_CODE) PduR_RmTp_Transmit_MultiDest(PduR_RmSrcRomIterType rmSrcIdx, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info)
{
  Std_ReturnType retVal = E_NOT_OK;
  PduR_RmDestRomIterType rmDestIdx;

  for(rmDestIdx = PduR_GetRmDestRomStartIdxOfRmSrcRom(rmSrcIdx); rmDestIdx < PduR_GetRmDestRomEndIdxOfRmSrcRom(rmSrcIdx); rmDestIdx++)
  {
    if(PduR_GetDirectionOfRmDestRom(rmDestIdx) == PDUR_TX_DIRECTIONOFRMDESTROM) /* PRQA S 3355 */ /* MD_CSL_3355_3356 */ /* COV_PDUR_FEATURE_ALWAYS_TRUE */
    {
# if (PDUR_RMDESTRPGROMIDXOFRMDESTROM == STD_ON)
      if((!PduR_IsRmDestRpgRomUsedOfRmDestRom(rmDestIdx)) || (0 != PduR_GetEnabledCntOfRmDestRpgRam(PduR_GetRmDestRpgRomIdxOfRmDestRom(rmDestIdx))))    /* PRQA S 3355, 3356 */ /* MD_CSL_3355_3356 */
# endif
      {
        retVal &= PduR_RmTp_MultipleSourceHandler_Transmit(rmDestIdx, info);    /* SBSW_PDUR_API_CALL_FORWARDING_ID_AND_PTR */
      }
    }
  }

  PDUR_DUMMY_STATEMENT(rmSrcIdx);       /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(info);   /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  return retVal;
}
#endif

/* Communication Interface APIs */
#if (PDUR_RXIF2DEST == STD_ON)
/**********************************************************************************************************************
 * PduR_LoIfRxIndication
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
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_LoIfRxIndication(PduIdType RxPduId, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = PDUR_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check initialization state of the component */
  if(PduR_IsInitialized() == FALSE)
  {
    errorId = PDUR_E_INVALID_REQUEST;
  }
# if (PDUR_DEV_ERROR_DETECT == STD_ON)  /* COV_PDUR_VAR_DEV_ERROR_DETECT */
  else if((RxPduId >= PduR_GetSizeOfRxIf2Dest())
#  if (PDUR_INVALIDHNDOFRXIF2DEST == STD_ON)
          || (PduR_IsInvalidHndOfRxIf2Dest(RxPduId))
#  endif
    )
  {
    errorId = PDUR_E_PDU_ID_INVALID;
  }
# endif
  else
  {
    /* #20 ----- Implementation ----------------------------------------------- */
    /* #30 BSWM callback */
# if (PDUR_BSWMPDURRXINDICATIONCALLBACKOFRXIF2DEST == STD_ON)
    if(PduR_IsBswMPduRRxIndicationCallbackOfRxIf2Dest(RxPduId))
    {
      /* #31 */
      BswM_PduR_RxIndication(RxPduId, info);    /* SBSW_PDUR_EXTERNAL_API_CALL_FORWARDING_ID_AND_PTR */
    }
# endif
    {
      /* #40 */
      (void) PduR_RmIf_RxIndication_MultiIf(PduR_GetRmSrcRomIdxOfRxIf2Dest(RxPduId), info);     /* SBSW_PDUR_EXTERNAL_API_CALL_FORWARDING_ID_AND_PTR */
    }
  }

  /* #50 ----- Development Error Report --------------------------------------- */
# if (PDUR_DEV_ERROR_REPORT == STD_ON)
  if(errorId != PDUR_E_NO_ERROR)
  {
    /* #51 */
    PduR_Det_ReportError(PDUR_FCT_IFRXIND, errorId);
  }
# else
  PDUR_DUMMY_STATEMENT(errorId);        /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
# endif

  PDUR_DUMMY_STATEMENT(RxPduId);        /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(info);   /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
}
#endif

#if (PDUR_TXIF2UP == STD_ON)
/**********************************************************************************************************************
 * PduR_LoIfTxConfirmation
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
 *********************************************************************************************************************/
/* PRQA S 6080 PDUR_LLIF_TXCONFIRMATION */ /* MD_MSR_STMIF */
FUNC(void, PDUR_CODE) PduR_LoIfTxConfirmation(PduIdType TxPduId)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = PDUR_E_NO_ERROR;

  /* #10 ----- Development Error Checks ------------------------------------- */
  /* Check initialization state of the component */
  if(PduR_IsInitialized() == FALSE)
  {
    errorId = PDUR_E_INVALID_REQUEST;
  }
# if (PDUR_DEV_ERROR_DETECT == STD_ON)  /* COV_PDUR_VAR_DEV_ERROR_DETECT */
  else if((TxPduId >= PduR_GetSizeOfTxIf2Up())
#  if (PDUR_INVALIDHNDOFTXIF2UP == STD_ON)
          || (PduR_IsInvalidHndOfTxIf2Up(TxPduId))
#  endif
    )
  {
    errorId = PDUR_E_PDU_ID_INVALID;
  }
# endif
  else
  {
    /* #20 ----- Implementation ----------------------------------------------- */
    /* #30 BSWM callback */
# if (PDUR_BSWMPDURTXCONFIRMATIONCALLBACKOFTXIF2UP == STD_ON)
    if(PduR_IsBswMPduRTxConfirmationCallbackOfTxIf2Up(TxPduId))
    {
      /* #31 */
      BswM_PduR_TxConfirmation(TxPduId);
    }
# endif
# if (PDUR_TXCONFIRMATIONUSEDOFTXIF2UP == STD_ON)  /* COV_PDUR_VAR_LINIF_SPECIAL_CONFIGURATION */
    if(PduR_IsTxConfirmationUsedOfTxIf2Up(TxPduId))
    {
      PduR_RmIf_MultipleSourceHandler_TxConfirmation(PduR_GetRmGDestRomIdxOfTxIf2Up(TxPduId));
    }
# endif
  }

  /* #50 ----- Development Error Report --------------------------------------- */
# if (PDUR_DEV_ERROR_REPORT == STD_ON)
  if(errorId != PDUR_E_NO_ERROR)
  {
    PduR_Det_ReportError(PDUR_FCT_IFTXCFM, errorId);
  }
# else
  PDUR_DUMMY_STATEMENT(errorId);        /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
# endif

  PDUR_DUMMY_STATEMENT(TxPduId);        /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
}
/* PRQA L:PDUR_LLIF_TXCONFIRMATION */
#endif

#if ((PDUR_TRIGGERTRANSMITSUPPORTEDOFRMSRCROM == STD_ON) || (PDUR_EXISTS_T_T_SINGLE_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON) || (PDUR_EXISTS_T_T_FIFO_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON))
/**********************************************************************************************************************
 * PduR_LoIfTriggerTransmit
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
 *********************************************************************************************************************/
FUNC(Std_ReturnType, PDUR_CODE) PduR_LoIfTriggerTransmit(PduIdType TxPduId, P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = PDUR_E_NO_ERROR;
  Std_ReturnType retVal = E_NOT_OK;

  /* #10 ----- Development Error Checks ------------------------------------- */
  /* Check initialization state of the component */
  if(PduR_IsInitialized() == FALSE)
  {
    errorId = PDUR_E_INVALID_REQUEST;
  }
# if (PDUR_DEV_ERROR_DETECT == STD_ON)  /* COV_PDUR_VAR_DEV_ERROR_DETECT */
#  if (PDUR_TXIF2UP == STD_ON)  /* COV_PDUR_VAR_DEPENDENT_SWITCH */
  else if((TxPduId >= PduR_GetSizeOfTxIf2Up())
#   if (PDUR_INVALIDHNDOFTXIF2UP == STD_ON)
          || (PduR_IsInvalidHndOfTxIf2Up(TxPduId))
#   endif
    )
  {
    errorId = PDUR_E_PDU_ID_INVALID;
  }
#  endif
# endif
  else
  {
    /* #20 ----- Implementation ----------------------------------------------- */
    retVal = PduR_RmIf_MultipleSourceHandler_TriggerTransmit(PduR_GetRmGDestRomIdxOfTxIf2Up(TxPduId), info);    /* SBSW_PDUR_EXTERNAL_API_CALL_FORWARDING_ID_AND_PTR */
  }

  /* ----- Development Error Report --------------------------------------- */
# if (PDUR_DEV_ERROR_REPORT == STD_ON)
  if(errorId != PDUR_E_NO_ERROR)
  {
    PduR_Det_ReportError(PDUR_FCT_TT, errorId);
  }
# else
  PDUR_DUMMY_STATEMENT(errorId);        /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
# endif

  PDUR_DUMMY_STATEMENT(TxPduId);        /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(info);   /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */

  return retVal;
}
#endif
/* Transport Protocol APIs */
#if (PDUR_RXTP2DEST == STD_ON)
/**********************************************************************************************************************
 * PduR_LoTpStartOfReception
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
 *********************************************************************************************************************/
FUNC(BufReq_ReturnType, PDUR_CODE) PduR_LoTpStartOfReception(PduIdType id, P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info, PduLengthType TpSduLength,
                                                             P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) bufferSizePtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = PDUR_E_NO_ERROR;
  BufReq_ReturnType retVal = BUFREQ_E_NOT_OK;

  /* ----- Development Error Checks ------------------------------------- */
  /* Check initialization state of the component */
  if(PduR_IsInitialized() == FALSE)
  {
    errorId = PDUR_E_INVALID_REQUEST;
  }
# if (PDUR_DEV_ERROR_DETECT == STD_ON)  /* COV_PDUR_VAR_DEV_ERROR_DETECT */
  else if((id >= PduR_GetSizeOfRxTp2Dest())
#  if (PDUR_INVALIDHNDOFRXTP2DEST == STD_ON)
          || (PduR_IsInvalidHndOfRxTp2Dest(id))
#  endif
    )
  {
    errorId = PDUR_E_PDU_ID_INVALID;
  }
# endif
  else
  {
    /* ----- Implementation ----------------------------------------------- */
# if (PDUR_BSWMPDURTPSTARTOFRECEPTIONCALLBACKOFRXTP2DEST == STD_ON)
    if(PduR_IsBswMPduRTpStartOfReceptionCallbackOfRxTp2Dest(id))
    {
      BswM_PduR_TpStartOfReception(id, info, TpSduLength, bufferSizePtr);       /* SBSW_PDUR_EXTERNAL_API_CALL_FORWARDING_ID_AND_PTR */
    }
# endif
    {
      PduR_RmSrcRomIdxOfRxTp2DestType rmSrcRomIdx = PduR_GetRmSrcRomIdxOfRxTp2Dest(id);
# if (PDUR_EXISTS_TP_UNBUFFERED_RX_API_FWD_ROUTINGTYPEOFRMDESTROM == STD_ON)
      PduR_RmDestRomStartIdxOfRmSrcRomType rmDestRomIdx = PduR_GetRmDestRomStartIdxOfRmSrcRom(rmSrcRomIdx);
#  if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
      if((PduR_GetRmDestRomLengthOfRmSrcRom(rmSrcRomIdx) == 1) && (PduR_GetRoutingTypeOfRmDestRom(rmDestRomIdx) == PDUR_TP_UNBUFFERED_RX_API_FWD_ROUTINGTYPEOFRMDESTROM))
#  endif
      { /* 1:1 Rx API Forwarding */
#  if (PDUR_RMDESTRPGROMIDXOFRMDESTROM == STD_ON)
        if((!PduR_IsRmDestRpgRomUsedOfRmDestRom(rmDestRomIdx)) || (0 != PduR_GetEnabledCntOfRmDestRpgRam(PduR_GetRmDestRpgRomIdxOfRmDestRom(rmDestRomIdx))))
#  endif
        {
          PduR_RmGDestRomIdxOfRmDestRomType rmGDestRomIdx = PduR_GetRmGDestRomIdxOfRmDestRom(rmDestRomIdx);
          retVal = PduR_GetUpTpStartOfReceptionFctPtrOfMmRom(PduR_GetMmRomIdxOfRmGDestRom(rmGDestRomIdx)) (PduR_GetDestHndOfRmGDestRom(rmGDestRomIdx), info, TpSduLength, bufferSizePtr);       /* SBSW_PDUR_EXTERNAL_API_CALL_FORWARDING_ID_AND_PTR */
        }
      }
# endif
# if ((PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON) && (PDUR_EXISTS_TP_UNBUFFERED_RX_API_FWD_ROUTINGTYPEOFRMDESTROM == STD_ON))
      else
# endif
# if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
      { /* buffered Tp Routings */
        retVal = PduR_RmTp_StartOfReception(rmSrcRomIdx, info, TpSduLength, bufferSizePtr);     /* SBSW_PDUR_EXTERNAL_API_CALL_FORWARDING_ID_AND_PTR */
      }
# endif
    }
  }

  /* ----- Development Error Report --------------------------------------- */
# if (PDUR_DEV_ERROR_REPORT == STD_ON)
  if(errorId != PDUR_E_NO_ERROR)
  {
    PduR_Det_ReportError(PDUR_FCT_SOR, errorId);
  }
# else
  PDUR_DUMMY_STATEMENT(errorId);        /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
# endif

  PDUR_DUMMY_STATEMENT(id);     /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(info);   /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(TpSduLength);    /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(bufferSizePtr);  /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */

  return retVal;
}
#endif
#if (PDUR_RXTP2DEST == STD_ON)
/**********************************************************************************************************************
 * PduR_LoTpCopyRxData
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
 *********************************************************************************************************************/
/* PRQA S 3673 1 */ /* MD_PduR_3673_AsrProto */
FUNC(BufReq_ReturnType, PDUR_CODE) PduR_LoTpCopyRxData(PduIdType id, P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info, P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) bufferSizePtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = PDUR_E_NO_ERROR;
  BufReq_ReturnType retVal = BUFREQ_E_NOT_OK;

  /* #10 ----- Development Error Checks ------------------------------------- */
  /* Check initialization state of the component */
  if(PduR_IsInitialized() == FALSE)
  {
    errorId = PDUR_E_INVALID_REQUEST;
  }
# if (PDUR_DEV_ERROR_DETECT == STD_ON)  /* COV_PDUR_VAR_DEV_ERROR_DETECT */
  else if((id >= PduR_GetSizeOfRxTp2Dest())
#  if (PDUR_INVALIDHNDOFRXTP2DEST == STD_ON)
          || (PduR_IsInvalidHndOfRxTp2Dest(id))
#  endif
    )
  {
    errorId = PDUR_E_PDU_ID_INVALID;
  }
# endif
  else
  {
    /* #20 ----- Implementation ----------------------------------------------- */
    {
      PduR_RmSrcRomIdxOfRxTp2DestType rmSrcRomIdx = PduR_GetRmSrcRomIdxOfRxTp2Dest(id);
# if (PDUR_EXISTS_TP_UNBUFFERED_RX_API_FWD_ROUTINGTYPEOFRMDESTROM == STD_ON)
      PduR_RmDestRomStartIdxOfRmSrcRomType rmDestRomIdx = PduR_GetRmDestRomStartIdxOfRmSrcRom(rmSrcRomIdx);
#  if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
      if((PduR_GetRmDestRomLengthOfRmSrcRom(rmSrcRomIdx) == 1) && (PduR_GetRoutingTypeOfRmDestRom(rmDestRomIdx) == PDUR_TP_UNBUFFERED_RX_API_FWD_ROUTINGTYPEOFRMDESTROM))
#  endif
      { /* 1:1 Rx API Forwarding */
#  if (PDUR_RMDESTRPGROMIDXOFRMDESTROM == STD_ON)
        if((!PduR_IsRmDestRpgRomUsedOfRmDestRom(rmDestRomIdx)) || (0 != PduR_GetEnabledCntOfRmDestRpgRam(PduR_GetRmDestRpgRomIdxOfRmDestRom(rmDestRomIdx))))
#  endif
        {
          PduR_RmGDestRomIdxOfRmDestRomType rmGDestRomIdx = PduR_GetRmGDestRomIdxOfRmDestRom(rmDestRomIdx);
          retVal = PduR_GetUpTpCopyRxDataFctPtrOfMmRom(PduR_GetMmRomIdxOfRmGDestRom(rmGDestRomIdx)) (PduR_GetDestHndOfRmGDestRom(rmGDestRomIdx), info, bufferSizePtr);  /* SBSW_PDUR_EXTERNAL_API_CALL_FORWARDING_ID_AND_PTR */
        }
      }
# endif
# if ((PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON) && (PDUR_EXISTS_TP_UNBUFFERED_RX_API_FWD_ROUTINGTYPEOFRMDESTROM == STD_ON))
      else
# endif
# if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
      { /* buffered Tp Routings */
        retVal = PduR_RmTp_CopyRxData(rmSrcRomIdx, info, bufferSizePtr);        /* SBSW_PDUR_EXTERNAL_API_CALL_FORWARDING_ID_AND_PTR */
      }
# endif
    }
  }

  /* #40 ----- Development Error Report --------------------------------------- */
# if (PDUR_DEV_ERROR_REPORT == STD_ON)
  if(errorId != PDUR_E_NO_ERROR)
  {
    PduR_Det_ReportError(PDUR_FCT_CPYRX, errorId);
  }
# else
  PDUR_DUMMY_STATEMENT(errorId);        /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
# endif

  PDUR_DUMMY_STATEMENT(id);     /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(info);   /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(bufferSizePtr);  /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */

  return retVal;
}
#endif
#if(PDUR_TXTP2SRC == STD_ON)
/**********************************************************************************************************************
 * PduR_LoTpCopyTxData
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
 *********************************************************************************************************************/
FUNC(BufReq_ReturnType, PDUR_CODE) PduR_LoTpCopyTxData(PduIdType id, P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info, P2VAR(RetryInfoType, AUTOMATIC, PDUR_APPL_DATA) retry,
                                                       P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) availableDataPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = PDUR_E_NO_ERROR;
  BufReq_ReturnType retVal = BUFREQ_E_NOT_OK;

  /* ----- Development Error Checks ------------------------------------- */
  /* Check initialization state of the component */
  if(PduR_IsInitialized() == FALSE)
  {
    errorId = PDUR_E_INVALID_REQUEST;
  }
# if (PDUR_DEV_ERROR_DETECT == STD_ON)  /* COV_PDUR_VAR_DEV_ERROR_DETECT */
  else if((id >= PduR_GetSizeOfTxTp2Src())
#  if (PDUR_INVALIDHNDOFTXTP2SRC == STD_ON)
          || (PduR_IsInvalidHndOfTxTp2Src(id))
#  endif
    )
  {
    errorId = PDUR_E_PDU_ID_INVALID;
  }
# endif
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    retVal = PduR_RmTp_MultipleSourceHandler_CopyTxData(PduR_GetRmGDestRomIdxOfTxTp2Src(id), info, retry, availableDataPtr);    /* SBSW_PDUR_API_CALL_FORWARDING_ID_AND_PTR */
  }

  /* ----- Development Error Report --------------------------------------- */
# if (PDUR_DEV_ERROR_REPORT == STD_ON)
  if(errorId != PDUR_E_NO_ERROR)
  {
    PduR_Det_ReportError(PDUR_FCT_CPYTX, errorId);
  }
# else
  PDUR_DUMMY_STATEMENT(errorId);        /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
# endif

  PDUR_DUMMY_STATEMENT(id);     /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(info);   /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(retry);  /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(availableDataPtr);       /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */

  return retVal;
}
#endif
#if (PDUR_RXTP2DEST == STD_ON)
/**********************************************************************************************************************
 * PduR_LoTpRxIndication
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
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_LoTpRxIndication(PduIdType id, Std_ReturnType result)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = PDUR_E_NO_ERROR;

  /* #10 ----- Development Error Checks ------------------------------------- */
  if(PduR_IsInitialized() == FALSE)
  {
    errorId = PDUR_E_INVALID_REQUEST;
  }
# if (PDUR_DEV_ERROR_DETECT == STD_ON)  /* COV_PDUR_VAR_DEV_ERROR_DETECT */
  else if((id >= PduR_GetSizeOfRxTp2Dest())
#  if (PDUR_INVALIDHNDOFRXTP2DEST == STD_ON)
          || (PduR_IsInvalidHndOfRxTp2Dest(id))
#  endif
    )
  {
    errorId = PDUR_E_PDU_ID_INVALID;
  }
# endif
  else
  {
    /* #20 ----- Implementation ----------------------------------------------- */
# if (PDUR_BSWMPDURTPRXINDICATIONCALLBACKOFRXTP2DEST == STD_ON)
    /* #30 BSWM callback */
    if(PduR_IsBswMPduRTpRxIndicationCallbackOfRxTp2Dest(id))
    {
      /* #31 */
      BswM_PduR_TpRxIndication(id, result);
    }
# endif
    {
      PduR_RmSrcRomIdxOfRxTp2DestType rmSrcRomIdx = PduR_GetRmSrcRomIdxOfRxTp2Dest(id);
# if (PDUR_EXISTS_TP_UNBUFFERED_RX_API_FWD_ROUTINGTYPEOFRMDESTROM == STD_ON)
      PduR_RmDestRomStartIdxOfRmSrcRomType rmDestRomIdx = PduR_GetRmDestRomStartIdxOfRmSrcRom(rmSrcRomIdx);
#  if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
      if((PduR_GetRmDestRomLengthOfRmSrcRom(rmSrcRomIdx) == 1) && (PduR_GetRoutingTypeOfRmDestRom(rmDestRomIdx) == PDUR_TP_UNBUFFERED_RX_API_FWD_ROUTINGTYPEOFRMDESTROM))
#  endif
      { /* 1:1 Rx API Forwarding */
        PduR_RmGDestRomIdxOfRmDestRomType rmGDestRomIdx = PduR_GetRmGDestRomIdxOfRmDestRom(rmDestRomIdx);
        PduR_GetUpTpTpRxIndicationFctPtrOfMmRom(PduR_GetMmRomIdxOfRmGDestRom(rmGDestRomIdx)) (PduR_GetDestHndOfRmGDestRom(rmGDestRomIdx), result);      /* SBSW_PDUR_EXTERNAL_API_CALL_FORWARDING_ID_AND_PTR */
      }
# endif
# if ((PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON) && (PDUR_EXISTS_TP_UNBUFFERED_RX_API_FWD_ROUTINGTYPEOFRMDESTROM == STD_ON))
      else
# endif
# if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
      { /* buffered Tp Routings */
        PduR_RmTp_TpRxIndication(rmSrcRomIdx, result);
      }
# endif
    }
  }

  /* #50 ----- Development Error Report --------------------------------------- */
# if (PDUR_DEV_ERROR_REPORT == STD_ON)
  if(errorId != PDUR_E_NO_ERROR)
  {
    PduR_Det_ReportError(PDUR_FCT_TPRXIND, errorId);
  }
# else
  PDUR_DUMMY_STATEMENT(errorId);        /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
# endif

  PDUR_DUMMY_STATEMENT(id);     /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(result); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
}
#endif
#if (PDUR_TXTP2SRC == STD_ON)
/**********************************************************************************************************************
 * PduR_LoTpTxConfirmation
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
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_LoTpTxConfirmation(PduIdType id, Std_ReturnType result)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = PDUR_E_NO_ERROR;

  /* #10 ----- Development Error Checks ------------------------------------- */
  /* Check initialization state of the component */
  if(PduR_IsInitialized() == FALSE)
  {
    errorId = PDUR_E_INVALID_REQUEST;
  }
# if (PDUR_DEV_ERROR_DETECT == STD_ON)  /* COV_PDUR_VAR_DEV_ERROR_DETECT */
  else if((id >= PduR_GetSizeOfTxTp2Src())
#  if (PDUR_INVALIDHNDOFTXTP2SRC == STD_ON)
          || (PduR_IsInvalidHndOfTxTp2Src(id))
#  endif
    )
  {
    errorId = PDUR_E_PDU_ID_INVALID;
  }
# endif
  else
  {
    /* ----- Implementation ----------------------------------------------- */
# if (PDUR_BSWMPDURTPTXCONFIRMATIONCALLBACKOFTXTP2SRC == STD_ON)
    /* #30 BSWM callback */
    if(PduR_IsBswMPduRTpTxConfirmationCallbackOfTxTp2Src(id))
    {
      /* #31 */
      BswM_PduR_TpTxConfirmation(id, result);
    }
# endif
    PduR_RmTp_MultipleSourceHandler_TpTxConfirmation(PduR_GetRmGDestRomIdxOfTxTp2Src(id), result);
  }

  /* ----- Development Error Report --------------------------------------- */
# if (PDUR_DEV_ERROR_REPORT == STD_ON)
  if(errorId != PDUR_E_NO_ERROR)
  {
    PduR_Det_ReportError(PDUR_FCT_TPTXCFM, errorId);
  }
# else
  PDUR_DUMMY_STATEMENT(errorId);        /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
# endif

  PDUR_DUMMY_STATEMENT(id);     /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(result); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
}
#endif
/* CancelReceive global without UseTag API */
#if (PDUR_CANCELRECEIVESUPPORTEDOFMMROM == STD_ON)
/**********************************************************************************************************************
 * PduR_CancelReceive
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
 *********************************************************************************************************************/
FUNC(Std_ReturnType, PDUR_CODE) PduR_CancelReceive(PduIdType id)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = PDUR_E_NO_ERROR;
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Development Error Checks ------------------------------------- */
  /* Check initialization state of the component */
  if(PduR_IsInitialized() == FALSE)
  {
    errorId = PDUR_E_INVALID_REQUEST;
  }
# if (PDUR_DEV_ERROR_DETECT == STD_ON)  /* COV_PDUR_VAR_DEV_ERROR_DETECT */
  else if((id >= PduR_GetSizeOfRxTp2Src())
#  if (PDUR_INVALIDHNDOFRXTP2SRC == STD_ON)
          || (PduR_IsInvalidHndOfRxTp2Src(id))
#  endif
    )
  {
    errorId = PDUR_E_PDU_ID_INVALID;
  }
# endif
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    PduR_RmDestRomIdxOfRxTp2SrcType rmDestRomIdx = PduR_GetRmDestRomIdxOfRxTp2Src(id);
    PduR_RmSrcRomIdxOfRmDestRomType rmSrcRomIdx = PduR_GetRmSrcRomIdxOfRmDestRom(rmDestRomIdx);
    PduR_MmRomIdxOfRmSrcRomType mmRomIdx = PduR_GetMmRomIdxOfRmSrcRom(rmSrcRomIdx);

    if(PduR_IsCancelReceiveSupportedOfMmRom(mmRomIdx)) /* COV_PDUR_FEATURE_ALWAYS_TRUE */
    {
# if (PDUR_RMDESTRPGROMIDXOFRMDESTROM == STD_ON)
      if((!PduR_IsRmDestRpgRomUsedOfRmDestRom(rmDestRomIdx)) || (0 != PduR_GetEnabledCntOfRmDestRpgRam(PduR_GetRmDestRpgRomIdxOfRmDestRom(rmDestRomIdx))))
# endif
      {
        PduR_SrcHndOfRmSrcRomType srcHnd = PduR_GetSrcHndOfRmSrcRom(rmSrcRomIdx);
        retVal = PduR_GetLoTpCancelReceiveFctPtrOfMmRom(mmRomIdx) (srcHnd);     /* SBSW_PDUR_EXTERNAL_API_CALL_FORWARDING_ID_ONLY */
      }
    }
  }

  /* ----- Development Error Report --------------------------------------- */
# if (PDUR_DEV_ERROR_REPORT == STD_ON)
  if(errorId != PDUR_E_NO_ERROR)
  {
    PduR_Det_ReportError(PDUR_FCT_CRX, errorId);
  }
# else
  PDUR_DUMMY_STATEMENT(errorId);        /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
# endif

  PDUR_DUMMY_STATEMENT(id);     /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */

  return retVal;
}
#endif
#if (PDUR_CHANGEPARAMETERSUPPORTEDOFMMROM == STD_ON)
/* ChangeParameter global without UseTag  API */
/**********************************************************************************************************************
 * PduR_ChangeParameter
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
 *********************************************************************************************************************/
FUNC(Std_ReturnType, PDUR_CODE) PduR_ChangeParameter(PduIdType id, TPParameterType parameter, uint16 value)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = PDUR_E_NO_ERROR;
  Std_ReturnType retVal = E_NOT_OK;

  /* #10 ----- Development Error Checks ------------------------------------- */
  /* Check initialization state of the component */
  if(PduR_IsInitialized() == FALSE)
  {
    errorId = PDUR_E_INVALID_REQUEST;
  }
# if (PDUR_DEV_ERROR_DETECT == STD_ON)  /* COV_PDUR_VAR_DEV_ERROR_DETECT */
  else if((id >= PduR_GetSizeOfRxTp2Src())
#  if (PDUR_INVALIDHNDOFRXTP2SRC == STD_ON)
          || (PduR_IsInvalidHndOfRxTp2Src(id))
#  endif
    )
  {
    errorId = PDUR_E_PDU_ID_INVALID;
  }
# endif
  else
  {
    /* #20 ----- Implementation ----------------------------------------------- */
    PduR_RmDestRomIdxOfRxTp2SrcType rmDestRomIdx = PduR_GetRmDestRomIdxOfRxTp2Src(id);
    PduR_RmSrcRomIdxOfRmDestRomType rmSrcRomIdx = PduR_GetRmSrcRomIdxOfRmDestRom(rmDestRomIdx);
    PduR_MmRomIdxOfRmSrcRomType mmRomIdx = PduR_GetMmRomIdxOfRmSrcRom(rmSrcRomIdx);

    /* #30 */
    if(PduR_IsChangeParameterSupportedOfMmRom(mmRomIdx)) /* COV_PDUR_FEATURE_ALWAYS_TRUE */
    {
      PduR_SrcHndOfRmSrcRomType srcHnd = PduR_GetSrcHndOfRmSrcRom(rmSrcRomIdx);
      retVal = PduR_GetLoTpChangeParameterFctPtrOfMmRom(mmRomIdx) (srcHnd, parameter, value);   /* SBSW_PDUR_EXTERNAL_API_CALL_FORWARDING_ID_ONLY */
    }
  }

  /* #40 ----- Development Error Report --------------------------------------- */
# if (PDUR_DEV_ERROR_REPORT == STD_ON)
  if(errorId != PDUR_E_NO_ERROR)
  {
    PduR_Det_ReportError(PDUR_FCT_CHPARA, errorId);
  }
# else
  PDUR_DUMMY_STATEMENT(errorId);        /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
# endif

  PDUR_DUMMY_STATEMENT(id);     /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(parameter);      /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(value);  /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */

  return retVal;
}
#endif
/* Communication Interface / Transport Protocol APIs */
#if ((PDUR_IFCANCELTRANSMITSUPPORTEDOFMMROM == STD_ON) || (PDUR_TPCANCELTRANSMITSUPPORTEDOFMMROM == STD_ON))
/**********************************************************************************************************************
 * PduR_CancelTransmit
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
 *********************************************************************************************************************/
FUNC(Std_ReturnType, PDUR_CODE) PduR_CancelTransmit(PduIdType id)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = PDUR_E_NO_ERROR;
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Development Error Checks ------------------------------------- */
  /* Check initialization state of the component */
  if(PduR_IsInitialized() == FALSE)
  {
    errorId = PDUR_E_INVALID_REQUEST;
  }
# if (PDUR_DEV_ERROR_DETECT == STD_ON)  /* COV_PDUR_VAR_DEV_ERROR_DETECT */
#  if (PDUR_TX2LO == STD_ON)    /* COV_PDUR_VAR_DEPENDENT_SWITCH */
  else if((id >= PduR_GetSizeOfTx2Lo())
#   if (PDUR_INVALIDHNDOFTX2LO == STD_ON)
          || (PduR_IsInvalidHndOfTx2Lo(id))
#   endif
    )
  {
    errorId = PDUR_E_PDU_ID_INVALID;
  }
#  endif
# endif
  else
  {
    /* ----- Implementation ----------------------------------------------- */
# if (PDUR_CANCELTRANSMITUSEDOFTX2LO  == STD_ON)        /* COV_PDUR_VAR_DEPENDENT_SWITCH */
    if(PduR_IsCancelTransmitUsedOfTx2Lo(id)) /* COV_PDUR_FEATURE_ALWAYS_TRUE */
    {
      retVal = PduR_Rm_CancelTransmit_MultiDest(PduR_GetRmSrcRomIdxOfTx2Lo(id));
    }
# endif
  }
  /* ----- Development Error Report --------------------------------------- */
# if (PDUR_DEV_ERROR_REPORT == STD_ON)
  if(errorId != PDUR_E_NO_ERROR)
  {
    PduR_Det_ReportError(PDUR_FCT_CTX, errorId);
  }
# else
  PDUR_DUMMY_STATEMENT(errorId);        /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
# endif

  PDUR_DUMMY_STATEMENT(id);     /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */

  return retVal;
}
#endif

#if ((PDUR_IFCANCELTRANSMITSUPPORTEDOFMMROM == STD_ON) || (PDUR_TPCANCELTRANSMITSUPPORTEDOFMMROM == STD_ON))
/**********************************************************************************************************************
 * PduR_Rm_CancelTransmit_MultiDest
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_Rm_CancelTransmit_MultiDest(PduR_RmSrcRomIterType rmSrcIdx)
{
  Std_ReturnType retVal = E_NOT_OK;

  PduR_RmDestRomIterType rmDestIdx;

  for(rmDestIdx = PduR_GetRmDestRomStartIdxOfRmSrcRom(rmSrcIdx); rmDestIdx < PduR_GetRmDestRomEndIdxOfRmSrcRom(rmSrcIdx); rmDestIdx++)
  {
# if (PDUR_RMDESTRPGROMIDXOFRMDESTROM == STD_ON)
    if((!PduR_IsRmDestRpgRomUsedOfRmDestRom(rmDestIdx)) || (0 != PduR_GetEnabledCntOfRmDestRpgRam(PduR_GetRmDestRpgRomIdxOfRmDestRom(rmDestIdx))))      /* PRQA S 3355, 3356 */ /* MD_CSL_3355_3356 */
# endif
    {
      switch (PduR_GetRoutingTypeOfRmDestRom(rmDestIdx))
      {
# if ((PDUR_EXISTS_IF_UNBUFFERED_TX_API_FWD_ROUTINGTYPEOFRMDESTROM == STD_ON) && (PDUR_IFCANCELTRANSMITSUPPORTEDOFMMROM == STD_ON))
        case PDUR_IF_UNBUFFERED_TX_API_FWD_ROUTINGTYPEOFRMDESTROM:
          if(PduR_IsIfCancelTransmitSupportedOfMmRom(PduR_GetMmRomIdxOfRmGDestRom(PduR_GetRmGDestRomIdxOfRmDestRom(rmDestIdx))))        /* PRQA S 3355 */ /* MD_CSL_3355_3356 */ /* COV_PDUR_FEATURE_ALWAYS_TRUE */
          {
            retVal &= PduR_RmIf_MultipleSourceHandler_CancelTransmit(rmDestIdx);
          }
          break;
# endif
# if ((PDUR_EXISTS_TP_UNBUFFERED_TX_API_FWD_ROUTINGTYPEOFRMDESTROM == STD_ON) && (PDUR_TPCANCELTRANSMITSUPPORTEDOFMMROM == STD_ON))
        case PDUR_TP_UNBUFFERED_TX_API_FWD_ROUTINGTYPEOFRMDESTROM:
          if(PduR_IsTpCancelTransmitSupportedOfMmRom(PduR_GetMmRomIdxOfRmGDestRom(PduR_GetRmGDestRomIdxOfRmDestRom(rmDestIdx))))        /* PRQA S 3355 */ /* MD_CSL_3355_3356 */ /* COV_PDUR_FEATURE_ALWAYS_TRUE */
          {
            retVal &= PduR_RmTp_MultipleSourceHandler_CancelTransmit(rmDestIdx);
          }
          break;
# endif
        default:       /* COV_PDUR_MISRA */
          /* Nothing to do: This should never be reached */
          break;
      }
    }
  }

  PDUR_DUMMY_STATEMENT(rmSrcIdx);       /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */

  return retVal;
}
#endif

/**********************************************************************************************************************
 * PduR_RmIf_Init_DedicatedTxBuffer
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
#if (PDUR_DEDICATEDTXBUFFEROFRMBUFFEREDIFPROPERTIESROM == STD_ON)
LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_RmIf_Init_DedicatedTxBuffer(void)
{
  PduR_RmGDestRomIterType rmGDestRomIdx;
  for(rmGDestRomIdx = 0; rmGDestRomIdx < PduR_GetSizeOfRmGDestRom(); rmGDestRomIdx++)
  {
    if(PduR_IsRmBufferedIfPropertiesRomUsedOfRmGDestRom(rmGDestRomIdx))
    {
      PduR_RmBufferedIfPropertiesRomIdxOfRmGDestRomType rmBufferedIfPropertiesRomIdx = PduR_GetRmBufferedIfPropertiesRomIdxOfRmGDestRom(rmGDestRomIdx);

      if(PduR_IsDedicatedTxBufferOfRmBufferedIfPropertiesRom(rmBufferedIfPropertiesRomIdx)) /* COV_PDUR_ONLY_DIRECT_BUFFER */
      {
        if(PduR_IsFmFifoInstanceRomUsedOfRmGDestRom(rmGDestRomIdx))     /* COV_PDUR_FATAL_ERROR */
        {
          PduR_FmFifoRomIterType fmFifoRomIdx = PduR_GetFmFifoRomIdxOfFmFifoInstanceRom(PduR_GetFmFifoInstanceRomIdxOfRmGDestRom(rmGDestRomIdx));
          PduR_FmFifoElementRamIterType possilbeFmFifoElementRamIdx;
          for(possilbeFmFifoElementRamIdx = PduR_GetFmFifoElementRamStartIdxOfFmFifoRom(fmFifoRomIdx); possilbeFmFifoElementRamIdx < PduR_GetFmFifoElementRamEndIdxOfFmFifoRom(fmFifoRomIdx);
              possilbeFmFifoElementRamIdx++)
          {
            PduR_FmFifoElementRamWriteIdxOfFmFifoRamType fmFifoElementRamIdx = 0U;
            if(PduR_Fm_AssignFifoElement(fmFifoRomIdx, &fmFifoElementRamIdx) == E_OK)   /* SBSW_PDUR_STACK_VARIABLE */ /* COV_PDUR_FATAL_ERROR */
            {
              PduLengthType bufferSizePtr = 0;
              PduR_BmTxBufferRomIdxOfBmTxBufferIndRomType allocatedTxBufferIdxPtr = 0U;
              if(PduR_Bm_AllocateTxBuffer(PduR_GetBmTxBufferIndRomStartIdxOfRmBufferedIfPropertiesRom(rmBufferedIfPropertiesRomIdx), PduR_GetBmTxBufferIndRomEndIdxOfRmBufferedIfPropertiesRom(rmBufferedIfPropertiesRomIdx), fmFifoElementRamIdx, 0, &bufferSizePtr, &allocatedTxBufferIdxPtr, FALSE) == BUFREQ_OK)    /* SBSW_PDUR_VALID_PTR_ENSURED_BY_CALLING_FUNCTION */ /* COV_PDUR_FATAL_ERROR */
              {
                PduR_Fm_AssignTxBuffer2FifoElement(fmFifoElementRamIdx, allocatedTxBufferIdxPtr);
                PduR_SetStateOfFmFifoElementRam(fmFifoElementRamIdx, PDUR_FM_ALLOCATED_WITH_BUFFER_STATEOFFMFIFOELEMENTRAM);    /* SBSW_PDUR_CSL03 */
                PduR_SetDedicatedTxBufferOfFmFifoElementRam(fmFifoElementRamIdx, TRUE); /* SBSW_PDUR_CSL03 */
              }
              else
              {
                PduR_Det_ReportError(PDUR_GWIF_INIT_DEDICATEDTXBUFFER, PDUR_E_FATAL);
              }
            }
            else
            {
              PduR_Det_ReportError(PDUR_GWIF_INIT_DEDICATEDTXBUFFER, PDUR_E_FATAL);
            }
          }
        }
        else
        {
          PduR_Det_ReportError(PDUR_GWIF_INIT_DEDICATEDTXBUFFER, PDUR_E_FATAL);
        }
      }
    }
  }
}       /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif

/**********************************************************************************************************************
 * PduR_RmIf_Init_TTSingleBuffer
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *********************************************************************************************************************/

#if (PDUR_EXISTS_T_T_SINGLE_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON)
LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_RmIf_Init_TTSingleBuffer(void)
{
  PduR_RmGDestRomIterType rmGDestRomIdx;
  for(rmGDestRomIdx = 0; rmGDestRomIdx < PduR_GetSizeOfRmGDestRom(); rmGDestRomIdx++)
  {
    if(PduR_IsRmBufferedIfPropertiesRomUsedOfRmGDestRom(rmGDestRomIdx) && PduR_IsFiFoInitValuesUsedOfRmBufferedIfPropertiesRom(PduR_GetRmBufferedIfPropertiesRomIdxOfRmGDestRom(rmGDestRomIdx))) /* COV_PDUR_FEATURE_ALWAYS_TRUE */
    {
      if(PduR_IsFmFifoInstanceRomUsedOfRmGDestRom(rmGDestRomIdx))       /* COV_PDUR_FATAL_ERROR */
      {
        PduR_RmBufferedIfPropertiesRomIdxOfRmGDestRomType rmBufferedIfPropertiesRomIdx = PduR_GetRmBufferedIfPropertiesRomIdxOfRmGDestRom(rmGDestRomIdx);
        PduR_FmFifoRomIterType fmFifoRomIdx = PduR_GetFmFifoRomIdxOfFmFifoInstanceRom(PduR_GetFmFifoInstanceRomIdxOfRmGDestRom(rmGDestRomIdx));
        PduR_FmFifoElementRamIterType fmFifoElementRamIdx;

        for(fmFifoElementRamIdx = PduR_GetFmFifoElementRamStartIdxOfFmFifoRom(fmFifoRomIdx); fmFifoElementRamIdx < PduR_GetFmFifoElementRamEndIdxOfFmFifoRom(fmFifoRomIdx); fmFifoElementRamIdx++)
        {
          PduR_BmTxBufferRomIterType bmTxBufferRomIdx = PduR_GetBmTxBufferRomIdxOfFmFifoElementRam(fmFifoElementRamIdx);
          PduR_BmTxBufferArrayRamIterType pduLength = PduR_GetFiFoInitValuesLengthOfRmBufferedIfPropertiesRom(rmBufferedIfPropertiesRomIdx);
          SduDataPtrType sduDataPtr = (SduDataPtrType) PduR_GetAddrFiFoInitValues(PduR_GetFiFoInitValuesStartIdxOfRmBufferedIfPropertiesRom(rmBufferedIfPropertiesRomIdx));     /* PRQA S 0311 */ /* MD_PduR_0311 */

          PduR_GetFctPtrOfTpActivateWriteFifoSmTransition(PduR_GetStateOfFmFifoElementRam(fmFifoElementRamIdx)) (fmFifoElementRamIdx);  /* SBSW_PDUR_CSL03 */
          (void) PduR_Bm_PutData(bmTxBufferRomIdx, pduLength, sduDataPtr);      /* SBSW_PDUR_STACK_VARIABLE */
          PduR_GetFctPtrOfFinishWriteFmSmTransition(PduR_GetStateOfFmFifoElementRam(fmFifoElementRamIdx)) (fmFifoElementRamIdx, E_OK);  /* SBSW_PDUR_CSL03 */
          PduR_RmIf_AssignAssociatedBuffer2Destination(bmTxBufferRomIdx, rmGDestRomIdx);
        }
      }
      else
      {
        PduR_Det_ReportError(PDUR_GWIF_INIT_TTSINGLEBUFFER, PDUR_E_FATAL);
      }
    }
  }
}
#endif

/**********************************************************************************************************************
 * PduR_RmTp_Init_DedicatedTxBuffer
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
#if (PDUR_DEDICATEDTXBUFFEROFRMBUFFEREDTPPROPERTIESROM == STD_ON)
LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_RmTp_Init_DedicatedTxBuffer(void)
{
  PduR_RmSrcRomIterType rmSrcRomIdx;
  for(rmSrcRomIdx = 0; rmSrcRomIdx < PduR_GetSizeOfRmSrcRom(); rmSrcRomIdx++)
  {
    if(PduR_IsRmBufferedTpPropertiesRomUsedOfRmSrcRom(rmSrcRomIdx))
    {
      PduR_RmBufferedTpPropertiesRomIdxOfRmSrcRomType rmBufferedTpPropertiesIdx = PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcRomIdx);

      if(PduR_IsDedicatedTxBufferOfRmBufferedTpPropertiesRom(rmBufferedTpPropertiesIdx))
      {
        /* Allocate FiFo element */
        PduR_FmFifoRomIterType fmFifoRomIdx = PduR_GetFmFifoRomIdxOfRmBufferedTpPropertiesRom(rmBufferedTpPropertiesIdx);
        PduR_FmFifoElementRamIterType possilbeFmFifoElementRamIdx;
        for(possilbeFmFifoElementRamIdx = PduR_GetFmFifoElementRamStartIdxOfFmFifoRom(fmFifoRomIdx); possilbeFmFifoElementRamIdx < PduR_GetFmFifoElementRamEndIdxOfFmFifoRom(fmFifoRomIdx);
            possilbeFmFifoElementRamIdx++)
        {
          PduR_FmFifoElementRamWriteIdxOfFmFifoRamType fmFifoElementRamIdx = 0U;
          if(PduR_Fm_AssignFifoElement(fmFifoRomIdx, &fmFifoElementRamIdx) == E_OK)     /* SBSW_PDUR_STACK_VARIABLE */ /* COV_PDUR_FATAL_ERROR */
          {
            PduLengthType bufferSizePtr = 0;
            PduR_BmTxBufferRomIdxOfBmTxBufferIndRomType allocatedTxBufferIdxPtr = 0U;
            /* Mapping Src Handle and current Fifo element */
            PduR_SetFmFifoElementRamIdxOfRmBufferedTpPropertiesRam(rmBufferedTpPropertiesIdx, fmFifoElementRamIdx);     /* SBSW_PDUR_CSL03 */

            /* Split Allocate and Assign buffer */
            if(PduR_Bm_AllocateTxBuffer(PduR_GetBmTxBufferIndRomStartIdxOfRmBufferedTpPropertiesRom(rmBufferedTpPropertiesIdx), PduR_GetBmTxBufferIndRomEndIdxOfRmBufferedTpPropertiesRom(rmBufferedTpPropertiesIdx), fmFifoElementRamIdx, 0, &bufferSizePtr, &allocatedTxBufferIdxPtr, TRUE) == BUFREQ_OK)     /* SBSW_PDUR_VALID_PTR_ENSURED_BY_CALLING_FUNCTION */ /* COV_PDUR_FATAL_ERROR */
            {
              PduR_Fm_AssignTxBuffer2FifoElement(fmFifoElementRamIdx, allocatedTxBufferIdxPtr);
              PduR_SetStateOfFmFifoElementRam(fmFifoElementRamIdx, PDUR_FM_ALLOCATED_WITH_BUFFER_STATEOFFMFIFOELEMENTRAM);      /* SBSW_PDUR_CSL01 */
              PduR_SetDedicatedTxBufferOfFmFifoElementRam(fmFifoElementRamIdx, TRUE);   /* SBSW_PDUR_CSL01 */
            }
            else
            {
              PduR_Det_ReportError(PDUR_GWTP_INIT_DEDICATEDTXBUFFER, PDUR_E_FATAL);
            }
          }
          else
          {
            PduR_Det_ReportError(PDUR_GWTP_INIT_DEDICATEDTXBUFFER, PDUR_E_FATAL);
          }
        }
      }
    }
  }
}       /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif

/**********************************************************************************************************************
 * PduR_Init
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
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_Init(P2CONST(PduR_PBConfigType, AUTOMATIC, PDUR_PBCFG) ConfigPtr)
{
/* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = PDUR_E_NO_ERROR;
  /* ----- Development Error Checks ------------------------------------- */

  /* Check initialization state of the component */
  if(PduR_IsInitialized() == TRUE)
  {
    errorId = PDUR_E_ALREADY_INITIALIZED;
  }
  else
  {
#if(PDUR_USE_INIT_POINTER == STD_ON)
    PduR_ConfigDataPtr = ConfigPtr;
    if(PduR_ConfigDataPtr == NULL_PTR)
    {
# if(PDUR_USE_ECUM_BSW_ERROR_HOOK == STD_ON)    /* COV_PDUR_VAR_DEPENDENT_SWITCH */
      EcuM_BswErrorHook(PDUR_MODULE_ID, ECUM_BSWERROR_NULLPTR);
# endif
      errorId = PDUR_E_NULL_POINTER;
    }
# if (PDUR_FINALMAGICNUMBER == STD_ON)  /* COV_PDUR_VAR_DEPENDENT_SWITCH */
    else if(PduR_GetFinalMagicNumber() != PDUR_FINAL_MAGIC_NUMBER)
    {
#  if(PDUR_USE_ECUM_BSW_ERROR_HOOK == STD_ON)   /* COV_PDUR_VAR_DEPENDENT_SWITCH */
      EcuM_BswErrorHook(PDUR_MODULE_ID, ECUM_BSWERROR_MAGICNUMBER);
#  endif
      errorId = PDUR_E_INIT_FAILED;
      PduR_ConfigDataPtr = (const PduR_PBConfigType *) NULL_PTR;
    }
    else
    {
      /* nothing to do */
    }
# endif
#else
    if(ConfigPtr != NULL_PTR)
    {
      errorId = PDUR_E_INIT_FAILED;
    }
#endif
    if(errorId == PDUR_E_NO_ERROR)
    {
#if(PDUR_RPGROM == STD_ON)
      PduR_Init_RmDestRpgRom();
#endif
#if(PDUR_RMGDESTNTO1INFORAMIDXOFRMGDESTROM == STD_ON)
      PduR_Rm_MultipleSourceHandler_Init();
#endif

      /* Init Buffer manager */
#if(PDUR_BMTXBUFFERRAM == STD_ON)
      PduR_Bm_Init();
#endif
/* Init Fifo manager */
#if(PDUR_FMFIFORAM == STD_ON)
      PduR_Init_FmFifoRam();
#endif
#if (PDUR_FMFIFORAM == STD_ON)
      PduR_Init_FmFifoElementRam();
#endif
#if(PDUR_FMFIFORAM == STD_ON)
      PduR_Init_FmFifoInstanceRam();
#endif

#if (PDUR_SMDATAPLANEROM == STD_ON)
      PduR_Sm_Init();
#endif

#if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
      PduR_Init_GwTp();
#endif

#if((PDUR_EXISTS_DIRECT_FIFO_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON) || (PDUR_EXISTS_T_T_FIFO_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON) || (PDUR_EXISTS_T_T_SINGLE_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON))
      PduR_Init_FiFoRoutingState();
#endif

#if (PDUR_DEDICATEDTXBUFFEROFRMBUFFEREDTPPROPERTIESROM == STD_ON)
      PduR_RmTp_Init_DedicatedTxBuffer();
#endif

#if (PDUR_DEDICATEDTXBUFFEROFRMBUFFEREDIFPROPERTIESROM == STD_ON)
      PduR_RmIf_Init_DedicatedTxBuffer();
#endif

#if(PDUR_EXISTS_T_T_SINGLE_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON)
      PduR_RmIf_Init_TTSingleBuffer();
#endif
      PduR_SetInitialized(TRUE);        /* SBSW_PDUR_CSL_VAR_ACCESS */

#if(PDUR_RECEPTIONINDICATIONQUEUE == STD_ON) /* COV_PDUR_VAR_ELISA_STD_OFF_XF */
      PduR_ReceptionIndicationQueueInit();
#endif

#if(PDUR_TRANSMITREQUESTQUEUE == STD_ON) /* COV_PDUR_VAR_ELISA_STD_OFF_XF */
      PduR_TransmitRequestQueueInit();
#endif

    }
  }
  /* ----- Development Error Report --------------------------------------- */
#if (PDUR_DEV_ERROR_REPORT == STD_ON)
  if(errorId != PDUR_E_NO_ERROR)
  {
    PduR_Det_ReportError(PDUR_FCT_INIT, errorId);
  }
#else
  PDUR_DUMMY_STATEMENT(errorId);        /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
#endif
}       /* End of PduR_Init() */ /* PRQA S 6050 */ /* MD_MSR_STCAL */

#if (PDUR_MAIN_FUNCTION_TX == STD_ON) /* COV_PDUR_VAR_ELISA_STD_OFF_XF */
/**********************************************************************************************************************
  PduR_MainFunctionTx
**********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_MainFunctionTx(void)
{
  if(PduR_IsInitialized())
  {
# if (PDUR_TRANSMITREQUESTQUEUE == STD_ON)      /* COV_PDUR_VAR_DEPENDENT_SWITCH */
    while(!PduR_IsTransmitRequestQueueEmpty())
    {
      PduR_FmFifoElementRamIterType peekedfmFifoElementRamReadIdx = 0;
      PduR_RmGDestRomIterType rmGDest = 0;
      Std_ReturnType readPduInfoRetVal = E_NOT_OK;
      Std_ReturnType retValTramsmit = E_NOT_OK;
      PduInfoType destPduInfo;

      /* Get queued global destination Pdu Id */
      rmGDest = PduR_GetRmGDestRomIdxOfTransmitRequestQueue(PduR_GetTransmitRequestQueueReadIdx());
      PduR_TransmitRequestQueueReadIdxIncrement();

      /* Get buffered PduInfo */
      readPduInfoRetVal = PduR_GetBufferedPduInfo(rmGDest, &destPduInfo, &peekedfmFifoElementRamReadIdx);       /* SBSW_PDUR_STACK_VARIABLE */

      if(readPduInfoRetVal == E_OK)
      {
        PduR_RmDestRomIdxOfFmFifoElementRamType rmDestRomIdx = PduR_GetRmDestRomIdxOfFmFifoElementRam(peekedfmFifoElementRamReadIdx);

#  if(PDUR_EXISTS_T_T_SINGLE_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON)
        if(PduR_GetFifoTypeOfRmBufferedIfPropertiesRom(PduR_GetRmBufferedIfPropertiesRomIdxOfRmGDestRom(rmGDest)) == PDUR_T_T_SINGLE_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM)
        {
          retValTramsmit = PduR_RmIf_MultipleSourceHandler_Transmit(rmDestRomIdx, &destPduInfo, FALSE); /* SBSW_PDUR_API_CALL_FORWARDING_ID_AND_PTR */
        }
        else
#  endif
        {
          retValTramsmit = PduR_RmIf_MultipleSourceHandler_Transmit(rmDestRomIdx, &destPduInfo, TRUE);  /* SBSW_PDUR_API_CALL_FORWARDING_ID_AND_PTR */
        }

        /* Reset routing if transmit failed and release the TxBuffer */
        if(retValTramsmit != E_OK)
        {
          PduR_Fm_FlushFiFo(rmGDest);
          PduR_Det_ReportError(PDUR_FCT_MAINFUNCTION_TX, PDUR_E_PDU_INSTANCES_LOST);
        }
      }
    }

# endif
  }
}
#endif

#if (PDUR_MAIN_FUNCTION_RX == STD_ON) /* COV_PDUR_VAR_ELISA_STD_OFF_XF */
/**********************************************************************************************************************
  PduR_MainFunctionRx
**********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_MainFunctionRx(void)
{
  if(PduR_IsInitialized() == TRUE)
  {
# if(PDUR_RECEPTIONINDICATIONQUEUE == STD_ON)   /* COV_PDUR_VAR_DEPENDENT_SWITCH */

    while(!PduR_IsReceptionIndicationQueueEmpty())
    {
      Std_ReturnType readPduInfoRetVal = E_NOT_OK;
      PduR_FmFifoElementRamIterType peekedfmFifoElementRamReadIdx = 0;
      PduR_RmGDestRomIterType rmGDest = 0;
      PduInfoType destPduInfo;

      /* Get queued global destination Pdu Id */
      rmGDest = PduR_GetRmGDestRomIdxOfReceptionIndicationQueue(PduR_GetReceptionIndicationQueueReadIdx());
      PduR_ReceptionIndicationQueueReadIdxIncrement();

      /* Get buffered PduInfo */
      readPduInfoRetVal = PduR_GetBufferedPduInfo(rmGDest, &destPduInfo, &peekedfmFifoElementRamReadIdx);       /* SBSW_PDUR_STACK_VARIABLE */

      if(readPduInfoRetVal == E_OK)
      {
        PduR_RmIf_TransmitPreparation(rmGDest, peekedfmFifoElementRamReadIdx);

        PduR_GetUpIfRxIndicationFctPtrOfMmRom(PduR_GetMmRomIdxOfRmGDestRom(rmGDest)) (PduR_GetDestHndOfRmGDestRom(rmGDest), &destPduInfo);      /* SBSW_PDUR_API_CALL_FORWARDING_ID_AND_PTR */
      }
    }
# endif
  }
}
#endif

#if(PDUR_FMFIFORAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Init_FmFifoRam
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_Init_FmFifoRam(void)
{
  PduR_FmFifoRamIterType fmFifoRamIdx;
  for(fmFifoRamIdx = 0; fmFifoRamIdx < PduR_GetSizeOfFmFifoRam(); fmFifoRamIdx++)
  {
# if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
    PduR_SetTpTxSmStateOfFmFifoRam(fmFifoRamIdx, PDUR_RM_TX_IDLE_TPTXSMSTATEOFFMFIFORAM);       /* SBSW_PDUR_CSL01 */
# endif
    PduR_SetPendingConfirmationsOfFmFifoRam(fmFifoRamIdx, 0);   /* SBSW_PDUR_CSL01 */
    PduR_SetFmFifoElementRamReadIdxOfFmFifoRam(fmFifoRamIdx, PduR_GetFmFifoElementRamStartIdxOfFmFifoRom(fmFifoRamIdx));        /* SBSW_PDUR_CSL01 */
    PduR_SetFmFifoElementRamWriteIdxOfFmFifoRam(fmFifoRamIdx, PduR_GetFmFifoElementRamStartIdxOfFmFifoRom(fmFifoRamIdx));       /* SBSW_PDUR_CSL01 */
    PduR_SetFillLevelOfFmFifoRam(fmFifoRamIdx, 0);      /* SBSW_PDUR_CSL01 */
  }
}
#endif

#if (PDUR_FMFIFORAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Init_FmFifoElementRam
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_Init_FmFifoElementRam(void)
{
  PduR_FmFifoElementRamIterType fmFifoElementRamIdx;
  for(fmFifoElementRamIdx = 0; fmFifoElementRamIdx < PduR_GetSizeOfFmFifoElementRam(); fmFifoElementRamIdx++)
  {
    PduR_SetStateOfFmFifoElementRam(fmFifoElementRamIdx, PDUR_FM_IDLE_STATEOFFMFIFOELEMENTRAM); /* SBSW_PDUR_CSL01 */
    PduR_SetBmTxBufferRomIdxOfFmFifoElementRam(fmFifoElementRamIdx, PDUR_NO_BMTXBUFFERROMIDXOFFMFIFOELEMENTRAM);        /* SBSW_PDUR_CSL01 */
    PduR_SetDedicatedTxBufferOfFmFifoElementRam(fmFifoElementRamIdx, FALSE);    /* SBSW_PDUR_CSL01 */
    PduR_SetRmDestRomIdxOfFmFifoElementRam(fmFifoElementRamIdx, PDUR_NO_RMDESTROMIDXOFFMFIFOELEMENTRAM);        /* SBSW_PDUR_CSL01 */
  }
}
#endif

#if(PDUR_FMFIFORAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Init_FmFifoInstanceRam
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_Init_FmFifoInstanceRam(void)
{
  PduR_FmFifoInstanceRamIterType fmFifoInstanceRamIdx;
  for(fmFifoInstanceRamIdx = 0; fmFifoInstanceRamIdx < PduR_GetSizeOfFmFifoInstanceRam(); fmFifoInstanceRamIdx++)
  {
    PduR_SetBmTxBufferInstanceRomIdxOfFmFifoInstanceRam(fmFifoInstanceRamIdx, PDUR_NO_BMTXBUFFERINSTANCEROMIDXOFFMFIFOINSTANCERAM);     /* SBSW_PDUR_CSL01 */
  }
}
#endif

#if(PDUR_RPGROM == STD_ON)
/**********************************************************************************************************************
 * PduR_Init_RmDestRpgRom
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_Init_RmDestRpgRom(void)
{
  {
    PduR_RmDestRpgRomIterType rmDestRpgRomIdx;
    for(rmDestRpgRomIdx = 0; rmDestRpgRomIdx < PduR_GetSizeOfRmDestRpgRom(); rmDestRpgRomIdx++)
    {
      PduR_SetEnabledCntOfRmDestRpgRam(rmDestRpgRomIdx, PduR_GetInitialEnabledCntOfRmDestRpgRom(rmDestRpgRomIdx));      /* SBSW_PDUR_CSL01 */
    }
  }
  {
    PduR_RpgRamIterType rpgIdx;
    for(rpgIdx = 0; rpgIdx < PduR_GetSizeOfRpgRam(); rpgIdx++)
    {
      PduR_SetEnabledOfRpgRam(rpgIdx, PduR_IsEnabledAtInitOfRpgRom(rpgIdx));    /* SBSW_PDUR_CSL01 */
    }
  }
}
#endif

#if(PDUR_RMGDESTNTO1INFORAMIDXOFRMGDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_Rm_MultipleSourceHandler_Init
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_Rm_MultipleSourceHandler_Init(void)
{
  PduR_RmGDestRomIterType rmGDestRomIdx;
  for(rmGDestRomIdx = 0; rmGDestRomIdx < PduR_GetSizeOfRmGDestRom(); rmGDestRomIdx++)
  {
    PduR_Rm_MultipleSourceHandler_Reset(rmGDestRomIdx);
  }
}
#endif

#if((PDUR_EXISTS_IF_UNBUFFERED_TX_API_FWD_ROUTINGTYPEOFRMDESTROM == STD_ON) || (PDUR_EXISTS_IF_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON) || (PDUR_EXISTS_IF_NOBUFFER_GATEWAY_ROUTINGTYPEOFRMDESTROM == STD_ON))
/**********************************************************************************************************************
 * PduR_RmIf_MultipleSourceHandler_Transmit
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_RmIf_MultipleSourceHandler_Transmit(PduR_RmDestRomIterType rmDestRomIdx, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info, boolean useLock)
{
  Std_ReturnType retVal = E_NOT_OK;
  SchM_Enter_PduR_PDUR_EXCLUSIVE_AREA_0();      /* PRQA S 3109 */ /* MD_MSR_14.3 */
  {
    PduR_RmGDestRomIdxOfRmDestRomType rmGDestRomIdx = PduR_GetRmGDestRomIdxOfRmDestRom(rmDestRomIdx);

# if(PDUR_RMGDESTNTO1INFORAMIDXOFRMGDESTROM == STD_ON)
    if(PduR_IsRmGDestNto1InfoRamUsedOfRmGDestRom(rmGDestRomIdx))
    {
      PduR_RmGDestNto1InfoRamIdxOfRmGDestRomType rmGDestNto1InfoIdx = PduR_GetRmGDestNto1InfoRamIdxOfRmGDestRom(rmGDestRomIdx);

      if(!PduR_IsTransmissionActiveOfRmGDestNto1InfoRam(rmGDestNto1InfoIdx)) /* COV_PDUR_NTO1_GW_ONLY_ROUTINGPATHS */
      {
        PduR_SetRmDestRomIdxOfRmGDestNto1InfoRam(rmGDestNto1InfoIdx, (PduR_RmDestRomIdxOfRmGDestNto1InfoRamType) rmDestRomIdx); /* SBSW_PDUR_CSL03 */
        PduR_SetTransmissionActiveOfRmGDestNto1InfoRam(rmGDestNto1InfoIdx, useLock);    /* SBSW_PDUR_CSL03 */

        retVal = PduR_GetLoIfTransmitFctPtrOfMmRom(PduR_GetMmRomIdxOfRmGDestRom(rmGDestRomIdx)) (PduR_GetDestHndOfRmGDestRom(rmGDestRomIdx), info);     /* SBSW_PDUR_API_CALL_FORWARDING_ID_AND_PTR */
        if(retVal != E_OK)
        {
          PduR_Rm_MultipleSourceHandler_Reset(rmGDestRomIdx);
        }
      }
    }
    else
# endif
    {
      retVal = PduR_GetLoIfTransmitFctPtrOfMmRom(PduR_GetMmRomIdxOfRmGDestRom(rmGDestRomIdx)) (PduR_GetDestHndOfRmGDestRom(rmGDestRomIdx), info);       /* SBSW_PDUR_API_CALL_FORWARDING_ID_AND_PTR */
    }
  }
  SchM_Exit_PduR_PDUR_EXCLUSIVE_AREA_0();       /* PRQA S 3109 */ /* MD_MSR_14.3 */

  PDUR_DUMMY_STATEMENT(useLock);
  return retVal;
}
#endif

#if ((PDUR_TRIGGERTRANSMITSUPPORTEDOFRMSRCROM == STD_ON) || (PDUR_EXISTS_T_T_SINGLE_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON) || (PDUR_EXISTS_T_T_FIFO_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON))
/**********************************************************************************************************************
 * PduR_RmIf_MultipleSourceHandler_TriggerTransmit
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_RmIf_MultipleSourceHandler_TriggerTransmit(PduR_RmGDestRomIdxOfTxIf2UpType rmGDestRomIdx, P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info)
{
  Std_ReturnType retVal = E_NOT_OK;
  {
    PduR_RmDestRomIterType rmDestRomIdx;

    if(PduR_Rm_GetSrcDestPdu(rmGDestRomIdx, &rmDestRomIdx) == E_OK)     /* SBSW_PDUR_STACK_VARIABLE */ /* COV_PDUR_NO_NTO1_ROUTINGPATHS */
    {
# if ((PDUR_EXISTS_T_T_SINGLE_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON) || (PDUR_EXISTS_T_T_FIFO_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON))
      if(PduR_GetRoutingTypeOfRmDestRom(rmDestRomIdx) == PDUR_IF_BUFFERED_ROUTINGTYPEOFRMDESTROM) /* COV_PDUR_FATAL_ERROR */
      {
        retVal = PduR_RmIf_TriggerTransmit(rmDestRomIdx, info); /* SBSW_PDUR_API_CALL_FORWARDING_ID_AND_PTR */
      }
      else
# endif
# if (PDUR_TRIGGERTRANSMITSUPPORTEDOFRMSRCROM == STD_ON)
      if(PduR_IsTriggerTransmitSupportedOfRmSrcRom(PduR_GetRmSrcRomIdxOfRmDestRom(rmDestRomIdx))) /* COV_PDUR_FATAL_ERROR */
      {
        retVal = PduR_GetUpIfTriggerTransmitFctPtrOfMmRom(PduR_GetMmRomIdxOfRmSrcRom(PduR_GetRmSrcRomIdxOfRmDestRom(rmDestRomIdx))) (PduR_GetSrcHndOfRmSrcRom(PduR_GetRmSrcRomIdxOfRmDestRom(rmDestRomIdx)), info);     /* SBSW_PDUR_API_CALL_FORWARDING_ID_AND_PTR */
      }
      else
# endif
      {
        PduR_Det_ReportError(PDUR_GWIF_MULTIPLESOURCEHANDLER_TRIGGERTRANSMIT, PDUR_E_PDU_ID_INVALID);
      }
    }
    else
    {
      PduR_Det_ReportError(PDUR_GWIF_MULTIPLESOURCEHANDLER_TRIGGERTRANSMIT, PDUR_E_PDU_ID_INVALID);
    }
  }
  return retVal;
}
#endif

/**********************************************************************************************************************
 * PduR_Rm_GetSrcDestPdu
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_Rm_GetSrcDestPdu(PduR_RmGDestRomIterType rmGDestRomIdx, P2VAR(PduR_RmDestRomIterType, AUTOMATIC, PDUR_APPL_DATA) rmDestRomIdx)
{
  Std_ReturnType retVal = E_OK;

#if(PDUR_RMGDESTNTO1INFORAMIDXOFRMGDESTROM == STD_ON)
  if(PduR_IsRmGDestNto1InfoRamUsedOfRmGDestRom(rmGDestRomIdx)) /* COV_PDUR_NTO1_NO_BUFFER_GW_ONLY_ROUTINGPATHS */
  {
    PduR_RmDestRomIterType localRmDestRomIdx = PduR_GetRmDestRomIdxOfRmGDestNto1InfoRam(PduR_GetRmGDestNto1InfoRamIdxOfRmGDestRom(rmGDestRomIdx));
    if(localRmDestRomIdx != PDUR_NO_RMDESTROMIDXOFRMGDESTNTO1INFORAM) /* COV_PDUR_NTO1_NO_BUFFER_GW_ONLY_ROUTINGPATHS */
    {
      *rmDestRomIdx = localRmDestRomIdx;        /* SBSW_PDUR_VALID_PTR_ENSURED_BY_CALLING_FUNCTION */
    }
    else
    {
      retVal = E_NOT_OK;
    }
  }
  else
#endif
  {
    *rmDestRomIdx = PduR_GetRmDestRomIdxOfRmGDestRom(rmGDestRomIdx);    /* SBSW_PDUR_VALID_PTR_ENSURED_BY_CALLING_FUNCTION */
  }

  return retVal;
}

#if ((PDUR_IFCANCELTRANSMITSUPPORTEDOFMMROM == STD_ON) && (PDUR_EXISTS_IF_UNBUFFERED_TX_API_FWD_ROUTINGTYPEOFRMDESTROM == STD_ON))
/**********************************************************************************************************************
 * PduR_RmIf_MultipleSourceHandler_CancelTransmit
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
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_RmIf_MultipleSourceHandler_CancelTransmit(PduR_RmDestRomIterType rmDestRomIdx)
{
  Std_ReturnType retVal = E_NOT_OK;
  SchM_Enter_PduR_PDUR_EXCLUSIVE_AREA_0();      /* PRQA S 3109 */ /* MD_MSR_14.3 */
  {
    PduR_RmGDestRomIdxOfRmDestRomType rmGDestRomIdx = PduR_GetRmGDestRomIdxOfRmDestRom(rmDestRomIdx);

# if(PDUR_RMGDESTNTO1INFORAMIDXOFRMGDESTROM == STD_ON)
    if(PduR_IsRmGDestNto1InfoRamUsedOfRmGDestRom(rmGDestRomIdx))
    {
      PduR_RmGDestNto1InfoRamIdxOfRmGDestRomType rmGDestNto1InfoIdx = PduR_GetRmGDestNto1InfoRamIdxOfRmGDestRom(rmGDestRomIdx);
      PduR_RmDestRomIterType lastTxdRmDestRomIdx;
      Std_ReturnType foundSrcPdu = PduR_Rm_GetSrcDestPdu(rmGDestRomIdx, &lastTxdRmDestRomIdx);  /* SBSW_PDUR_STACK_VARIABLE */

      if(PduR_IsTransmissionActiveOfRmGDestNto1InfoRam(rmGDestNto1InfoIdx) && (foundSrcPdu == E_OK) && (rmDestRomIdx == lastTxdRmDestRomIdx)) /* COV_PDUR_ROBUSTNESS */
      {
        retVal = PduR_GetLoIfCancelTransmitFctPtrOfMmRom(PduR_GetMmRomIdxOfRmGDestRom(rmGDestRomIdx)) (PduR_GetDestHndOfRmGDestRom(rmGDestRomIdx));     /* SBSW_PDUR_API_CALL_FORWARDING_ID_AND_PTR */
      }
      else
      {
        PduR_Det_ReportError(PDUR_GWIF_MULTIPLESOURCEHANDLER_CANCELTRANSMIT, PDUR_E_UNEXPECTED_CALL);
      }
    }
    else
# endif
    {
      retVal = PduR_GetLoIfCancelTransmitFctPtrOfMmRom(PduR_GetMmRomIdxOfRmGDestRom(rmGDestRomIdx)) (PduR_GetDestHndOfRmGDestRom(rmGDestRomIdx));       /* SBSW_PDUR_API_CALL_FORWARDING_ID_AND_PTR */
    }
  }
  SchM_Exit_PduR_PDUR_EXCLUSIVE_AREA_0();       /* PRQA S 3109 */ /* MD_MSR_14.3 */
  return retVal;
}
#endif

#if (PDUR_TXCONFIRMATIONUSEDOFTXIF2UP == STD_ON)
/**********************************************************************************************************************
 * PduR_RmIf_MultipleSourceHandler_TxConfirmation
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_RmIf_MultipleSourceHandler_TxConfirmation(PduR_RmGDestRomIdxOfTxIf2UpType rmGDestRomIdx)
{
  PduR_RmDestRomIterType rmDestRomIdx;

  if(PduR_Rm_GetSrcDestPdu(rmGDestRomIdx, &rmDestRomIdx) == E_OK)       /* SBSW_PDUR_STACK_VARIABLE */ /* COV_PDUR_NO_NTO1_ROUTINGPATHS */
  {
# if(PDUR_RMGDESTNTO1INFORAMIDXOFRMGDESTROM == STD_ON)
    PduR_Rm_MultipleSourceHandler_Reset(rmGDestRomIdx);
# endif

# if ((PDUR_TXCONFIRMATIONSUPPORTEDOFRMSRCROM == STD_ON) && (PDUR_EXISTS_IMMEDIATE_PDURDESTPDUPROCESSINGOFRMGDESTROM == STD_ON)) /* COV_PDUR_VAR_ELISA_STD_ON_TF_tf_tx */
#  if (PDUR_EXISTS_DEFERRED_PDURDESTPDUPROCESSINGOFRMGDESTROM == STD_ON) /* COV_PDUR_VAR_ELISA_STD_OFF_XF */
    if(PduR_GetPduRDestPduProcessingOfRmGDestRom(rmGDestRomIdx) == PDUR_IMMEDIATE_PDURDESTPDUPROCESSINGOFRMGDESTROM)
#  endif
    {
      PduR_RmSrcRomIdxOfRmDestRomType rmSrcRomIdx = PduR_GetRmSrcRomIdxOfRmDestRom(rmDestRomIdx);
      if(PduR_IsTxConfirmationSupportedOfRmSrcRom(rmSrcRomIdx)) /* COV_PDUR_FEATURE_ALWAYS_TRUE */
      {
        PduR_GetUpIfTxConfirmationFctPtrOfMmRom(PduR_GetMmRomIdxOfRmSrcRom(rmSrcRomIdx)) (PduR_GetSrcHndOfRmSrcRom(rmSrcRomIdx));       /* SBSW_PDUR_API_CALL_FORWARDING_ID_ONLY */
      }
    }
# endif
# if((PDUR_EXISTS_T_T_FIFO_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON) || (PDUR_EXISTS_DIRECT_FIFO_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON))
    if(PduR_GetRoutingTypeOfRmDestRom(rmDestRomIdx) == PDUR_IF_BUFFERED_ROUTINGTYPEOFRMDESTROM) /* COV_PDUR_FEATURE_ALWAYS_TRUE */
    {
      PduR_RmIf_TxConfirmation(rmGDestRomIdx);
    }
# endif
  }
  else
  {
    PduR_Det_ReportError(PDUR_GWIF_MULTIPLESOURCEHANDLER_TXCONFIRMATION, PDUR_E_PDU_ID_INVALID);
  }
}
#endif

#if(PDUR_RMGDESTNTO1INFORAMIDXOFRMGDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_Rm_MultipleSourceHandler_Reset
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_Rm_MultipleSourceHandler_Reset(PduR_RmGDestRomIterType rmGDestRomIdx)
{
  if(PduR_IsRmGDestNto1InfoRamUsedOfRmGDestRom(rmGDestRomIdx))
  {
    PduR_RmGDestNto1InfoRamIdxOfRmGDestRomType rmGDestNto1InfoIdx = PduR_GetRmGDestNto1InfoRamIdxOfRmGDestRom(rmGDestRomIdx);

    PduR_SetTransmissionActiveOfRmGDestNto1InfoRam(rmGDestNto1InfoIdx, FALSE);  /* SBSW_PDUR_IDX_PARAM_INTERNAL_FUNCTION */
    PduR_SetRmDestRomIdxOfRmGDestNto1InfoRam(rmGDestNto1InfoIdx, PDUR_NO_RMDESTROMIDXOFRMGDESTNTO1INFORAM);     /* SBSW_PDUR_IDX_PARAM_INTERNAL_FUNCTION */
  }
}
#endif

#if ((PDUR_TRANSMITREQUESTQUEUE == STD_ON) || (PDUR_RECEPTIONINDICATIONQUEUE == STD_ON)) /* COV_PDUR_VAR_ELISA_STD_OFF_XF_xf_xf */
/**********************************************************************************************************************
 * PduR_GetBufferedPduInfo
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_GetBufferedPduInfo(PduR_RmGDestRomIterType rmGDest, P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info,
                                                                     P2VAR(PduR_FmFifoElementRamIterType, AUTOMATIC, PDUR_APPL_DATA) peekedfmFifoElementRamReadIdx)
{
  Std_ReturnType retVal = E_NOT_OK;

  PduR_FmFifoInstanceRamIterType fmFifoRomInstanceIdx = PduR_GetFmFifoInstanceRomIdxOfRmGDestRom(rmGDest);
  PduR_FmFifoRamIterType fmFifoRomIdx = PduR_GetFmFifoRomIdxOfFmFifoInstanceRom(fmFifoRomInstanceIdx);
  *peekedfmFifoElementRamReadIdx = PduR_GetFmFifoElementRamReadIdxOfFmFifoRam(fmFifoRomIdx);    /* SBSW_PDUR_STACK_VARIABLE */

  /* Read data from the TxBuffer */
  if((PduR_Fm_IsFifoElementAllocated(*peekedfmFifoElementRamReadIdx) == E_OK) && (PduR_GetFillLevelOfFmFifoRam(fmFifoRomIdx) > 0))
  {
    PduR_RmIf_TransmitPreparation(rmGDest, *peekedfmFifoElementRamReadIdx);
    {
      PduR_RmDestRomIdxOfFmFifoElementRamType rmDestRomIdx = PduR_GetRmDestRomIdxOfFmFifoElementRam(*peekedfmFifoElementRamReadIdx);
      PduR_RmGDestRomIdxOfRmDestRomType rmGDestRomIdx = PduR_GetRmGDestRomIdxOfRmDestRom(rmDestRomIdx);
      PduR_BmTxBufferInstanceRomIterType bmTxBufferInstanceRomIdx = PduR_GetBmTxBufferInstanceRomIdxOfFmFifoInstanceRam(PduR_GetFmFifoInstanceRomIdxOfRmGDestRom(rmGDestRomIdx));

      PduR_Bm_CopyDataAsPtr(bmTxBufferInstanceRomIdx, info, info->SduLength);   /* SBSW_PDUR_API_CALL_FORWARDING_ID_AND_PTR */
      retVal = E_OK;
    }
  }

  return retVal;
}
#endif

#if ((PDUR_EXISTS_IMMEDIATE_PDURDESTPDUPROCESSINGOFRMGDESTROM == STD_ON) && ((PDUR_EXISTS_DIRECT_FIFO_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON) || (PDUR_EXISTS_T_T_FIFO_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON) || (PDUR_EXISTS_T_T_SINGLE_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON))) /* COV_PDUR_VAR_ELISA_STD_ON_TF_tx_tf_tf_tf */
/**********************************************************************************************************************
 * PduR_PerformImmediateDestinationDataProcessing
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_PerformImmediateDestinationDataProcessing(PduR_RmGDestRomIdxOfRmDestRomType rmGDest, PduR_RmDestRomIterType rmDest,
                                                                                            P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info,
                                                                                            PduR_FmFifoElementRamWriteIdxOfFmFifoRamType fmFifoElementRamIdx, boolean useLock)
{
  Std_ReturnType retVal = E_NOT_OK;

  /* Perform transmission to destination module */
  PduR_RmIf_TransmitPreparation(rmGDest, fmFifoElementRamIdx);
  retVal = PduR_RmIf_MultipleSourceHandler_Transmit(rmDest, info, useLock);     /* SBSW_PDUR_API_CALL_FORWARDING_ID_AND_PTR */

  return retVal;
}
#endif

#if (PDUR_EXISTS_DEFERRED_PDURDESTPDUPROCESSINGOFRMGDESTROM == STD_ON)   /* COV_PDUR_VAR_ELISA_STD_OFF_XF */
/**********************************************************************************************************************
 * PduR_PerformDeferredDestinationDataProcessing
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_PerformDeferredDestinationDataProcessing(PduR_RmGDestRomIdxOfRmDestRomType rmGDest, PduR_RmDestRomIterType rmDest)
{
  Std_ReturnType retVal = E_NOT_OK;
# if (PDUR_TRANSMITREQUESTQUEUE == STD_ON)      /* COV_PDUR_VAR_DEPENDENT_SWITCH */
  if(PduR_GetDirectionOfRmDestRom(rmDest) == PDUR_TX_DIRECTIONOFRMDESTROM)
  {
    if(!PduR_IsTransmitRequestQueueFull())
    {
      /* Store GDest Id into transmitRequest Queue */
      PduR_SetRmGDestRomIdxOfTransmitRequestQueue(PduR_GetTransmitRequestQueueWriteIdx(), rmGDest);     /* SBSW_PDUR_WRITE_TRANSMIT_OR_INDICATION_QUEUE */
      PduR_TransmitRequestQueueWriteIdxIncrement();
      retVal = E_OK;
    }
  }
  else
# endif
  {
# if(PDUR_RECEPTIONINDICATIONQUEUE == STD_ON)   /* COV_PDUR_VAR_DEPENDENT_SWITCH */
    if(!PduR_IsReceptionIndicationQueueFull())
    {
      /* Store GDest Id into indicationRequest Queue */
      PduR_SetRmGDestRomIdxOfReceptionIndicationQueue(PduR_GetReceptionIndicationQueueWriteIdx(), rmGDest);     /* SBSW_PDUR_WRITE_TRANSMIT_OR_INDICATION_QUEUE */
      PduR_ReceptionIndicationQueueWriteIdxIncrement();
      retVal = E_OK;
    }
# endif
  }

  PDUR_DUMMY_STATEMENT(rmGDest);
  PDUR_DUMMY_STATEMENT(rmDest);
  return retVal;
}
#endif

#if((PDUR_EXISTS_DIRECT_FIFO_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON) || (PDUR_EXISTS_T_T_FIFO_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON) || (PDUR_EXISTS_T_T_SINGLE_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON))
/**********************************************************************************************************************
 * PduR_Init_FiFoRoutingState
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_Init_FiFoRoutingState(void)
{
  PduR_RmBufferedIfPropertiesRomIterType rmBufferedIfPropertiesRamIdx;
  for(rmBufferedIfPropertiesRamIdx = 0; rmBufferedIfPropertiesRamIdx < PduR_GetSizeOfRmBufferedIfPropertiesRam(); rmBufferedIfPropertiesRamIdx++)
  {
    PduR_SetIfSmStateOfRmBufferedIfPropertiesRam(rmBufferedIfPropertiesRamIdx, PduR_GetNextState_For_Init_If_Routing_StateOfIfRoutingStateTable(PduR_GetFifoTypeOfRmBufferedIfPropertiesRom(rmBufferedIfPropertiesRamIdx)));    /* SBSW_PDUR_CSL03 */
  }
}
#endif

#if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_Init_GwTp
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_Init_GwTp(void)
{
  {
    PduR_RmGDestTpTxStateRamIterType rmGDestTpTxStateRamTpIdx;
    for(rmGDestTpTxStateRamTpIdx = 0; rmGDestTpTxStateRamTpIdx < PduR_GetSizeOfRmGDestTpTxStateRam(); rmGDestTpTxStateRamTpIdx++)
    {
      PduR_SetTpTxInstSmStateOfRmGDestTpTxStateRam(rmGDestTpTxStateRamTpIdx, PDUR_RM_TXINST_IDLE_TPTXINSTSMSTATEOFRMGDESTTPTXSTATERAM); /* SBSW_PDUR_CSL01 */
    }
  }
  {
    PduR_RmBufferedTpPropertiesRomIterType rmBufferedTpPropertiesRamIdx;
    for(rmBufferedTpPropertiesRamIdx = 0; rmBufferedTpPropertiesRamIdx < PduR_GetSizeOfRmBufferedTpPropertiesRam(); rmBufferedTpPropertiesRamIdx++)
    {
      PduR_SetTpRxSmStateOfRmBufferedTpPropertiesRam(rmBufferedTpPropertiesRamIdx, PDUR_RM_RX_IDLE_TPRXSMSTATEOFRMBUFFEREDTPPROPERTIESRAM);     /* SBSW_PDUR_CSL01 */
      PduR_SetFmFifoElementRamIdxOfRmBufferedTpPropertiesRam(rmBufferedTpPropertiesRamIdx, PDUR_NO_FMFIFOELEMENTRAMIDXOFRMBUFFEREDTPPROPERTIESRAM);     /* SBSW_PDUR_CSL01 */
    }
  }
}
#endif

/**********************************************************************************************************************
 * PduR_InitMemory
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_InitMemory(void)
{
  PduR_SetInitialized(FALSE);   /* SBSW_PDUR_CSL_VAR_ACCESS */
#if(PDUR_USE_INIT_POINTER == STD_ON)
  PduR_ConfigDataPtr = (P2CONST(PduR_PBConfigType, PDUR_VAR_ZERO_INIT, PDUR_PBCFG)) NULL_PTR;
#endif
}       /* End of PduR_InitMemory() */

#if(PDUR_EXISTS_T_T_SINGLE_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmIf_SingleBufferHandling
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
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_RmIf_SingleBufferHandling(PduR_RmDestRomIterType rmDest, PduR_RmGDestRomIdxOfRmDestRomType rmGDest, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info,
                                                                  P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) destPduInfo)
{
  PduR_FmFifoRomIterType fmFifoRomIdx = PduR_GetFmFifoRomIdxOfFmFifoInstanceRom(PduR_GetFmFifoInstanceRomIdxOfRmGDestRom(rmGDest));
  PduR_FmFifoElementRamWriteIdxOfFmFifoRamType fmFifoElementRamIdx = 0U;
  PduR_RmBufferedIfPropertiesRomIdxOfRmGDestRomType rmBufferedIfPropertiesRomIdx = PduR_GetRmBufferedIfPropertiesRomIdxOfRmGDestRom(rmGDest);

  PduR_Fm_FlushFiFo(rmGDest);
  PduR_SetIfSmStateOfRmBufferedIfPropertiesRam(rmBufferedIfPropertiesRomIdx, PDUR_WAIT_FOR_RXINDICATION_IFSMSTATEOFRMBUFFEREDIFPROPERTIESRAM);  /* SBSW_PDUR_CSL03 */
  if(PduR_Fm_AssignFifoElement(fmFifoRomIdx, &fmFifoElementRamIdx) == E_OK)     /* SBSW_PDUR_STACK_VARIABLE */ /* COV_PDUR_FATAL_ERROR */
  {
    PduLengthType bufferSizePtr = 0;
    PduR_BmTxBufferRomIdxOfBmTxBufferIndRomType allocatedTxBufferIdxPtr = 0U;
    /* Update fill level */
    PduR_IncFillLevelOfFmFifoRam(fmFifoRomIdx); /* SBSW_PDUR_CSL03 */
    if(PduR_Bm_AllocateTxBuffer(PduR_GetBmTxBufferIndRomStartIdxOfRmBufferedIfPropertiesRom(rmBufferedIfPropertiesRomIdx), PduR_GetBmTxBufferIndRomEndIdxOfRmBufferedIfPropertiesRom(rmBufferedIfPropertiesRomIdx), fmFifoElementRamIdx, (PduR_BmTxBufferArrayRamLengthOfBmTxBufferRomType) info->SduLength, &bufferSizePtr, &allocatedTxBufferIdxPtr, FALSE) == BUFREQ_OK)     /* SBSW_PDUR_VALID_PTR_ENSURED_BY_CALLING_FUNCTION */ /* COV_PDUR_FATAL_ERROR */
    {
      PduR_Fm_AssignTxBuffer2FifoElement(fmFifoElementRamIdx, allocatedTxBufferIdxPtr);
      PduR_SetStateOfFmFifoElementRam(fmFifoElementRamIdx, PDUR_FM_ALLOCATED_WITH_BUFFER_STATEOFFMFIFOELEMENTRAM);      /* SBSW_PDUR_CSL01 */
      PduR_SetRmDestRomIdxOfFmFifoElementRam(fmFifoElementRamIdx, (PduR_RmDestRomIdxOfFmFifoElementRamType) rmDest);    /* SBSW_PDUR_CSL01 */
      PduR_RmIf_CopyRxData(fmFifoElementRamIdx, (PduR_BmTxBufferArrayRamIterType) destPduInfo->SduLength, destPduInfo->SduDataPtr);     /* SBSW_PDUR_STACK_VARIABLE */

      switch (PduR_GetPduRDestPduProcessingOfRmGDestRom(rmGDest))
      {
# if (PDUR_EXISTS_IMMEDIATE_PDURDESTPDUPROCESSINGOFRMGDESTROM == STD_ON) /* COV_PDUR_VAR_ELISA_STD_ON_TX */
        case PDUR_IMMEDIATE_PDURDESTPDUPROCESSINGOFRMGDESTROM:
        {
          if(E_OK != PduR_PerformImmediateDestinationDataProcessing(rmGDest, rmDest, destPduInfo, fmFifoElementRamIdx, FALSE))  /* SBSW_PDUR_VALID_PTR_ENSURED_BY_CALLING_FUNCTION */
          {
            PduR_Det_ReportError(PDUR_GWIF_SINGLEBUFFERHANDLING, PDUR_E_PDU_INSTANCES_LOST);
          }
          break;
        }
# endif
# if (PDUR_EXISTS_DEFERRED_PDURDESTPDUPROCESSINGOFRMGDESTROM == STD_ON) /* COV_PDUR_VAR_ELISA_STD_OFF_XF */
        case PDUR_DEFERRED_PDURDESTPDUPROCESSINGOFRMGDESTROM:
        {
          if(E_OK != PduR_PerformDeferredDestinationDataProcessing(rmGDest, rmDest))
          {
            PduR_ReportRuntimeDetError(PDUR_GWIF_SINGLEBUFFERHANDLING, PDUR_E_REQUEST_QUEUE_OVERFLOW);
          }
          break;
        }
# endif
        default:       /* COV_PDUR_MISRA */
          /* Nothing to do: This should never be reached */
          break;
      }
    }
    else
    {
      PduR_Det_ReportError(PDUR_GWIF_SINGLEBUFFERHANDLING, PDUR_E_FATAL);
    }
  }
  else
  {
    PduR_Det_ReportError(PDUR_GWIF_SINGLEBUFFERHANDLING, PDUR_E_FATAL);
  }
}       /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

#if ((PDUR_EXISTS_DIRECT_FIFO_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON) || (PDUR_EXISTS_T_T_FIFO_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON))
/**********************************************************************************************************************
 * PduR_RmIf_FifoHandling
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
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_RmIf_FifoHandling(PduR_RmDestRomIterType rmDest, PduR_RmGDestRomIdxOfRmDestRomType rmGDest, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info)
{
  if(PduR_GetIfSmStateOfRmBufferedIfPropertiesRam(PduR_GetRmBufferedIfPropertiesRomIdxOfRmGDestRom(rmGDest)) == PDUR_WAIT_FOR_RXINDICATION_IFSMSTATEOFRMBUFFEREDIFPROPERTIESRAM)
  {
    PduR_FmFifoElementRamWriteIdxOfFmFifoRamType fmFifoElementRamIdx;

    if(PduR_RmIf_FiFoDataProcessing(rmDest, rmGDest, &fmFifoElementRamIdx, (PduR_BmTxBufferArrayRamLengthOfBmTxBufferRomType) info->SduLength, info->SduDataPtr) == E_OK)       /* SBSW_PDUR_STACK_VARIABLE */ /* COV_PDUR_ONLY_DIRECT_BUFFER */
    {
      switch (PduR_GetPduRDestPduProcessingOfRmGDestRom(rmGDest))
      {
# if (PDUR_EXISTS_IMMEDIATE_PDURDESTPDUPROCESSINGOFRMGDESTROM == STD_ON) /* COV_PDUR_VAR_ELISA_STD_ON_TX */
        case PDUR_IMMEDIATE_PDURDESTPDUPROCESSINGOFRMGDESTROM:
        {
          if(E_OK != PduR_PerformImmediateDestinationDataProcessing(rmGDest, rmDest, info, fmFifoElementRamIdx, TRUE))  /* SBSW_PDUR_VALID_PTR_ENSURED_BY_CALLING_FUNCTION */
          {
            PduR_Fm_FlushFiFo(rmGDest);
            PduR_Det_ReportError(PDUR_FCT_GWIF_FQ, PDUR_E_PDU_INSTANCES_LOST);
          }
          break;
        }
# endif
# if (PDUR_EXISTS_DEFERRED_PDURDESTPDUPROCESSINGOFRMGDESTROM == STD_ON)   /* COV_PDUR_VAR_ELISA_STD_OFF_XF */
        case PDUR_DEFERRED_PDURDESTPDUPROCESSINGOFRMGDESTROM:
        {
          if(E_OK != PduR_PerformDeferredDestinationDataProcessing(rmGDest, rmDest))
          {
            PduR_ReportRuntimeDetError(PDUR_FCT_GWIF_FQ, PDUR_E_REQUEST_QUEUE_OVERFLOW);
          }

#  if (PDUR_TXCONFIRMATIONSUPPORTEDOFRMSRCROM == STD_ON)
          {
            /* Call upper layer confirmation immediately */
            PduR_RmSrcRomIdxOfRmDestRomType rmSrcRomIdx = PduR_GetRmSrcRomIdxOfRmDestRom(rmDest);
            if(PduR_IsTxConfirmationSupportedOfRmSrcRom(rmSrcRomIdx))
            {
              PduR_GetUpIfTxConfirmationFctPtrOfMmRom(PduR_GetMmRomIdxOfRmSrcRom(rmSrcRomIdx)) (PduR_GetSrcHndOfRmSrcRom(rmSrcRomIdx)); /* SBSW_PDUR_API_CALL_FORWARDING_ID_ONLY */
            }
          }
#  endif
          break;
        }
# endif
        default:       /* COV_PDUR_MISRA */
          /* Nothing to do: This should never be reached */
          break;

      }
    }
  }
  else
  {
    PduR_FmFifoElementRamWriteIdxOfFmFifoRamType fmFifoElementRamIdx;
    if(PduR_RmIf_FiFoDataProcessing(rmDest, rmGDest, &fmFifoElementRamIdx, (PduR_BmTxBufferArrayRamLengthOfBmTxBufferRomType) info->SduLength, info->SduDataPtr) != E_OK)       /* SBSW_PDUR_STACK_VARIABLE */
    {
      PduR_Fm_FlushFiFo(rmGDest);
      PduR_Det_ReportError(PDUR_FCT_GWIF_FQ, PDUR_E_PDU_INSTANCES_LOST);
# if(PDUR_RMGDESTNTO1INFORAMIDXOFRMGDESTROM == STD_ON)
      PduR_Rm_MultipleSourceHandler_Reset(rmGDest);
# endif

# if (PDUR_ERROR_NOTIFICATION == STD_ON)        /* COV_PDUR_ERROR_NOTIFICATION */
      ErrorNotificationQueueOverflow(PduR_GetDestHndOfRmGDestRom(rmGDest));
# endif
      if(PduR_RmIf_FiFoDataProcessing(rmDest, rmGDest, &fmFifoElementRamIdx, (PduR_BmTxBufferArrayRamLengthOfBmTxBufferRomType) info->SduLength, info->SduDataPtr) == E_OK)     /* SBSW_PDUR_STACK_VARIABLE */ /* COV_PDUR_FATAL_ERROR */
      {
        switch (PduR_GetPduRDestPduProcessingOfRmGDestRom(rmGDest))
        {
# if (PDUR_EXISTS_IMMEDIATE_PDURDESTPDUPROCESSINGOFRMGDESTROM == STD_ON) /* COV_PDUR_VAR_ELISA_STD_ON_TX */
          case PDUR_IMMEDIATE_PDURDESTPDUPROCESSINGOFRMGDESTROM:
          {
            if(E_OK != PduR_PerformImmediateDestinationDataProcessing(rmGDest, rmDest, info, fmFifoElementRamIdx, TRUE))        /* SBSW_PDUR_VALID_PTR_ENSURED_BY_CALLING_FUNCTION */
            {
              PduR_Fm_FlushFiFo(rmGDest);
            }
          }
            break;
# endif
# if (PDUR_EXISTS_DEFERRED_PDURDESTPDUPROCESSINGOFRMGDESTROM == STD_ON) /* COV_PDUR_VAR_ELISA_STD_OFF_XF */
          case PDUR_DEFERRED_PDURDESTPDUPROCESSINGOFRMGDESTROM:
          {
            if(E_OK != PduR_PerformDeferredDestinationDataProcessing(rmGDest, rmDest))
            {
              PduR_ReportRuntimeDetError(PDUR_FCT_GWIF_FQ, PDUR_E_REQUEST_QUEUE_OVERFLOW);
            }
#  if (PDUR_TXCONFIRMATIONSUPPORTEDOFRMSRCROM == STD_ON)
            {
              /* Call upper layer confirmation immediately */
              PduR_RmSrcRomIdxOfRmDestRomType rmSrcRomIdx = PduR_GetRmSrcRomIdxOfRmDestRom(rmDest);
              if(PduR_IsTxConfirmationSupportedOfRmSrcRom(rmSrcRomIdx))
              {
                PduR_GetUpIfTxConfirmationFctPtrOfMmRom(PduR_GetMmRomIdxOfRmSrcRom(rmSrcRomIdx)) (PduR_GetSrcHndOfRmSrcRom(rmSrcRomIdx));       /* SBSW_PDUR_API_CALL_FORWARDING_ID_ONLY */
              }
            }
#  endif
            break;
          }
# endif
          default:     /* COV_PDUR_MISRA */
            /* Nothing to do: This should never be reached */
            break;
        }
      }
    }
  }
}       /* PRQA S 6030, 6080, 6050 */ /* MD_MSR_STCYC, MD_MSR_STMIF, MD_MSR_STCAL */
#endif

/**********************************************************************************************************************
 * PduR_RmIf_FiFoDataProcessing
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *********************************************************************************************************************/
#if ((PDUR_EXISTS_DIRECT_FIFO_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON) || (PDUR_EXISTS_T_T_FIFO_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON))
LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_RmIf_FiFoDataProcessing(PduR_RmDestRomIterType rmDest, PduR_RmGDestRomIterType rmGDest,
                                                                          PduR_FmFifoElementRamWriteIdxOfFmFifoRamType * fmFifoElementRamIdx,
                                                                          PduR_BmTxBufferArrayRamLengthOfBmTxBufferRomType pduLength, SduDataPtrType sduDataPtr)
{
  Std_ReturnType retVal = E_NOT_OK;
  PduR_FmFifoRomIterType fmFifoRomIdx = PduR_GetFmFifoRomIdxOfFmFifoInstanceRom(PduR_GetFmFifoInstanceRomIdxOfRmGDestRom(rmGDest));
  if(PduR_Fm_AssignFifoElement(fmFifoRomIdx, fmFifoElementRamIdx) == E_OK)      /* SBSW_PDUR_STACK_VARIABLE */
  {
    PduR_RmBufferedIfPropertiesRomIdxOfRmGDestRomType rmBufferedIfPropertiesRomIdx = PduR_GetRmBufferedIfPropertiesRomIdxOfRmGDestRom(rmGDest);
    PduLengthType bufferSizePtr = 0;
    PduR_BmTxBufferRomIdxOfBmTxBufferIndRomType allocatedTxBufferIdxPtr = 0U;
    /* Update fill level */
    PduR_IncFillLevelOfFmFifoRam(fmFifoRomIdx); /* SBSW_PDUR_CSL03 */
    if(PduR_Bm_AllocateTxBuffer(PduR_GetBmTxBufferIndRomStartIdxOfRmBufferedIfPropertiesRom(rmBufferedIfPropertiesRomIdx), PduR_GetBmTxBufferIndRomEndIdxOfRmBufferedIfPropertiesRom(rmBufferedIfPropertiesRomIdx), *fmFifoElementRamIdx, pduLength, &bufferSizePtr, &allocatedTxBufferIdxPtr, FALSE) == BUFREQ_OK)     /* SBSW_PDUR_VALID_PTR_ENSURED_BY_CALLING_FUNCTION */
    {
      PduR_Fm_AssignTxBuffer2FifoElement(*fmFifoElementRamIdx, allocatedTxBufferIdxPtr);
      PduR_SetStateOfFmFifoElementRam(*fmFifoElementRamIdx, PDUR_FM_ALLOCATED_WITH_BUFFER_STATEOFFMFIFOELEMENTRAM);     /* SBSW_PDUR_CSL01 */
      PduR_SetRmDestRomIdxOfFmFifoElementRam(*fmFifoElementRamIdx, (PduR_RmDestRomIdxOfFmFifoElementRamType) rmDest);   /* SBSW_PDUR_CSL01 */
      PduR_RmIf_CopyRxData(*fmFifoElementRamIdx, pduLength, sduDataPtr);        /* SBSW_PDUR_STACK_VARIABLE */
      retVal = E_OK;
    }
    else
    {
      PduR_Fm_FreeFifoElement(fmFifoRomIdx, *fmFifoElementRamIdx);
    }
  }
  return retVal;
}
#endif

#if(PDUR_EXISTS_IF_NOBUFFER_GATEWAY_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmIf_RxIndicationNoBuffer
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_RmIf_RxIndicationNoBuffer(PduR_RmDestRomIterType rmDestIdx, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info)
{
  SchM_Enter_PduR_PDUR_EXCLUSIVE_AREA_0();      /* PRQA S 3109 */ /* MD_MSR_14.3 */
  if(E_OK != PduR_RmIf_MultipleSourceHandler_Transmit(rmDestIdx, info, FALSE))  /* SBSW_PDUR_API_CALL_FORWARDING_ID_AND_PTR */
  {
    PduR_Det_ReportError(PDUR_FCT_GWIF_FQ, PDUR_E_PDU_INSTANCES_LOST);
  }
  SchM_Exit_PduR_PDUR_EXCLUSIVE_AREA_0();       /* PRQA S 3109 */ /* MD_MSR_14.3 */
}
#endif

#if((PDUR_EXISTS_T_T_FIFO_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON) || (PDUR_EXISTS_DIRECT_FIFO_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON) || (PDUR_EXISTS_T_T_SINGLE_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON))
/**********************************************************************************************************************
 * PduR_RmIf_Forward2Buffer
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_RmIf_Forward2Buffer(PduR_RmDestRomIterType rmDestIdx, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info)
{
# if(PDUR_EXISTS_T_T_SINGLE_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON)
  if(PduR_GetFifoTypeOfRmBufferedIfPropertiesRom(PduR_GetRmBufferedIfPropertiesRomIdxOfRmGDestRom(PduR_GetRmGDestRomIdxOfRmDestRom(rmDestIdx))) ==
     PDUR_T_T_SINGLE_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM) /* COV_PDUR_FEATURE_ALWAYS_TRUE */
  {
    PduR_RmIf_RxIndicationTTSingleBuffer(rmDestIdx, info);      /* SBSW_PDUR_API_CALL_FORWARDING_ID_AND_PTR */
  }
# endif
# if(((PDUR_EXISTS_T_T_FIFO_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON) || (PDUR_EXISTS_DIRECT_FIFO_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON)) && (PDUR_EXISTS_T_T_SINGLE_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON))
  else
# endif
# if((PDUR_EXISTS_T_T_FIFO_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON) || (PDUR_EXISTS_DIRECT_FIFO_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON))
  {
    PduR_RmIf_RxIndicationFifoBuffer(rmDestIdx, info);  /* SBSW_PDUR_API_CALL_FORWARDING_ID_AND_PTR */
  }
# endif
}
#endif

#if(PDUR_EXISTS_T_T_SINGLE_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmIf_RxIndicationTTSingleBuffer
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_RmIf_RxIndicationTTSingleBuffer(PduR_RmDestRomIterType rmDestIdx, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info)
{
  PduR_RmGDestRomIdxOfRmDestRomType rmGDest = PduR_GetRmGDestRomIdxOfRmDestRom(rmDestIdx);
  PduInfoType destPduInfo;
  SchM_Enter_PduR_PDUR_EXCLUSIVE_AREA_0();      /* PRQA S 3109 */ /* MD_MSR_14.3 */
  destPduInfo.SduDataPtr = info->SduDataPtr;
  destPduInfo.SduLength = PduR_RmIf_CalcDlc(rmGDest, info);     /* SBSW_PDUR_VALID_PTR_ENSURED_BY_CALLING_FUNCTION */
  PduR_RmIf_SingleBufferHandling(rmDestIdx, rmGDest, info, &destPduInfo);       /* SBSW_PDUR_STACK_VARIABLE */
  SchM_Exit_PduR_PDUR_EXCLUSIVE_AREA_0();       /* PRQA S 3109 */ /* MD_MSR_14.3 */
}
#endif

#if((PDUR_EXISTS_T_T_FIFO_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON) || (PDUR_EXISTS_DIRECT_FIFO_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON))
 /**********************************************************************************************************************
 * PduR_RmIf_RxIndicationFifoBuffer
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_RmIf_RxIndicationFifoBuffer(PduR_RmDestRomIterType rmDestIdx, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info)
{
  PduR_RmGDestRomIdxOfRmDestRomType rmGDest = PduR_GetRmGDestRomIdxOfRmDestRom(rmDestIdx);
  PduInfoType destPduInfo;
  SchM_Enter_PduR_PDUR_EXCLUSIVE_AREA_0();      /* PRQA S 3109 */ /* MD_MSR_14.3 */
  destPduInfo.SduDataPtr = info->SduDataPtr;
  destPduInfo.SduLength = PduR_RmIf_CalcDlc(rmGDest, info);     /* SBSW_PDUR_VALID_PTR_ENSURED_BY_CALLING_FUNCTION */
  PduR_RmIf_FifoHandling(rmDestIdx, rmGDest, &destPduInfo);     /* SBSW_PDUR_STACK_VARIABLE */
  SchM_Exit_PduR_PDUR_EXCLUSIVE_AREA_0();       /* PRQA S 3109 */ /* MD_MSR_14.3 */
}
#endif

#if((PDUR_EXISTS_DIRECT_FIFO_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON) || (PDUR_EXISTS_T_T_FIFO_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON) || (PDUR_EXISTS_T_T_SINGLE_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON))
 /**********************************************************************************************************************
 * PduR_RmIf_CopyRxData
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_RmIf_CopyRxData(PduR_FmFifoElementRamIterType fmFifoElementRamIdx, PduR_BmTxBufferArrayRamIterType pduLength, SduDataPtrType sduDataPtr)
{
  PduR_BmTxBufferRomIterType bmTxBufferRomIdx = PduR_GetBmTxBufferRomIdxOfFmFifoElementRam(fmFifoElementRamIdx);
  PduR_SetStateOfFmFifoElementRam(fmFifoElementRamIdx, PDUR_FM_ALLOCATED_WITH_BUFFER_STATEOFFMFIFOELEMENTRAM);  /* SBSW_PDUR_CSL01 */
  PduR_GetFctPtrOfTpActivateWriteFifoSmTransition(PduR_GetStateOfFmFifoElementRam(fmFifoElementRamIdx)) (fmFifoElementRamIdx);  /* SBSW_PDUR_CSL03 */
  (void) PduR_Bm_PutData(bmTxBufferRomIdx, pduLength, sduDataPtr);      /* SBSW_PDUR_STACK_VARIABLE */
  PduR_GetFctPtrOfFinishWriteFmSmTransition(PduR_GetStateOfFmFifoElementRam(fmFifoElementRamIdx)) (fmFifoElementRamIdx, E_OK);  /* SBSW_PDUR_CSL03 */
}
#endif

#if((PDUR_EXISTS_DIRECT_FIFO_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON) || (PDUR_EXISTS_T_T_FIFO_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON) || (PDUR_EXISTS_T_T_SINGLE_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON))
 /**********************************************************************************************************************
 * PduR_RmIf_TransmitPreparation
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_RmIf_TransmitPreparation(PduR_RmGDestRomIterType rmGDest, PduR_FmFifoElementRamIterType fmFifoElementRamIdx)
{
  PduR_BmTxBufferRomIterType bmTxBufferRomIdx = PduR_GetBmTxBufferRomIdxOfFmFifoElementRam(fmFifoElementRamIdx);
  PduR_RmBufferedIfPropertiesRomIdxOfRmGDestRomType rmBufferedIfPropertiesRomIdx = PduR_GetRmBufferedIfPropertiesRomIdxOfRmGDestRom(rmGDest);
  PduR_SetIfSmStateOfRmBufferedIfPropertiesRam(rmBufferedIfPropertiesRomIdx, PduR_GetNextState_For_Wait_For_RxIndicationOfIfRoutingStateTable(PduR_GetFifoTypeOfRmBufferedIfPropertiesRom(rmBufferedIfPropertiesRomIdx)));      /* SBSW_PDUR_IDX_PARAM_INTERNAL_FUNCTION */
  PduR_RmIf_AssignAssociatedBuffer2Destination(bmTxBufferRomIdx, rmGDest);
  PduR_GetFctPtrOfTpActivateReadFifoSmTransition(PduR_GetStateOfFmFifoElementRam(fmFifoElementRamIdx)) (fmFifoElementRamIdx);   /* SBSW_PDUR_CSL03 */
}
#endif

#if((PDUR_EXISTS_IF_UNBUFFERED_RX_API_FWD_ROUTINGTYPEOFRMDESTROM == STD_ON) || (PDUR_EXISTS_IF_UNBUFFERED_TX_API_FWD_ROUTINGTYPEOFRMDESTROM == STD_ON) || (PDUR_EXISTS_IF_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON) || (PDUR_EXISTS_IF_NOBUFFER_GATEWAY_ROUTINGTYPEOFRMDESTROM == STD_ON))
/**********************************************************************************************************************
 * PduR_RmIf_RxIndication_MultiIf
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *********************************************************************************************************************/
FUNC(Std_ReturnType, PDUR_CODE) PduR_RmIf_RxIndication_MultiIf(PduR_RmSrcRomIterType rmSrcIdx, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;

  {
    /* ----- Implementation ----------------------------------------------- */
    PduR_RmDestRomIterType rmDestIdx;

# if (PDUR_SMDATAPLANEROM == STD_ON)
    if(PduR_IsSmSrcRomUsedOfRmSrcRom(rmSrcIdx))
    {
      PduR_SmSrcRomIdxOfRmSrcRomType smSrcRomIdx = PduR_GetSmSrcRomIdxOfRmSrcRom(rmSrcIdx);
      PduR_GetSmSrcFilterFctPtr(PduR_GetSmSrcFilterFctPtrIdxOfSmSrcRom(smSrcRomIdx)) (smSrcRomIdx, info);       /* SBSW_PDUR_CSL03 */
    }
# endif
    for(rmDestIdx = PduR_GetRmDestRomStartIdxOfRmSrcRom(rmSrcIdx); rmDestIdx < PduR_GetRmDestRomEndIdxOfRmSrcRom(rmSrcIdx); rmDestIdx++)
    {
# if (PDUR_RMDESTRPGROMIDXOFRMDESTROM == STD_ON)
      if((!PduR_IsRmDestRpgRomUsedOfRmDestRom(rmDestIdx)) || (0 != PduR_GetEnabledCntOfRmDestRpgRam(PduR_GetRmDestRpgRomIdxOfRmDestRom(rmDestIdx))))
# endif
      {
        PduR_RmGDestRomIterType rmGDestRomIdx = PduR_GetRmGDestRomIdxOfRmDestRom(rmDestIdx);
# if (PDUR_SMDATAPLANEROM == STD_ON)
        PduR_FilterReturnType filterResult = PDUR_FILTER_PASS;
        if(PduR_IsSmGDestRomUsedOfRmGDestRom(rmGDestRomIdx))
        {
          PduR_SmGDestRomIdxOfRmGDestRomType smGDestRomIdx = PduR_GetSmGDestRomIdxOfRmGDestRom(rmGDestRomIdx);
          filterResult = PduR_GetSmGDestFilterFctPtr(PduR_GetSmGDestFilterFctPtrIdxOfSmGDestRom(smGDestRomIdx)) (smGDestRomIdx, info);  /* SBSW_PDUR_CSL03 */
        }
        if(filterResult == PDUR_FILTER_PASS)
# endif
        {
          switch (PduR_GetRoutingTypeOfRmDestRom(rmDestIdx))
          {
# if (PDUR_EXISTS_IF_UNBUFFERED_RX_API_FWD_ROUTINGTYPEOFRMDESTROM == STD_ON)
            case PDUR_IF_UNBUFFERED_RX_API_FWD_ROUTINGTYPEOFRMDESTROM:
              PduR_GetUpIfRxIndicationFctPtrOfMmRom(PduR_GetMmRomIdxOfRmGDestRom(rmGDestRomIdx)) (PduR_GetDestHndOfRmGDestRom(rmGDestRomIdx), info);    /* SBSW_PDUR_API_CALL_FORWARDING_ID_AND_PTR */
              retVal &= E_OK;
              break;
# endif
# if (PDUR_EXISTS_IF_UNBUFFERED_TX_API_FWD_ROUTINGTYPEOFRMDESTROM == STD_ON)
            case PDUR_IF_UNBUFFERED_TX_API_FWD_ROUTINGTYPEOFRMDESTROM:
              retVal &= PduR_RmIf_MultipleSourceHandler_Transmit(rmDestIdx, info, !PduR_IsRmDestRomUsedOfRmGDestRom(rmGDestRomIdx));    /* SBSW_PDUR_API_CALL_FORWARDING_ID_AND_PTR */
              break;
# endif
# if (PDUR_EXISTS_IF_NOBUFFER_GATEWAY_ROUTINGTYPEOFRMDESTROM == STD_ON)
            case PDUR_IF_NOBUFFER_GATEWAY_ROUTINGTYPEOFRMDESTROM:
              retVal &= PduR_RmIf_ProcessNoBufferedGwRouting(rmDestIdx, info); /* SBSW_PDUR_API_CALL_FORWARDING_ID_AND_PTR */
              break;
# endif
# if (PDUR_EXISTS_IF_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
            case PDUR_IF_BUFFERED_ROUTINGTYPEOFRMDESTROM:
              retVal &= PduR_RmIf_ProcessBufferedRouting(rmSrcIdx, rmDestIdx, rmGDestRomIdx, info); /* SBSW_PDUR_API_CALL_FORWARDING_ID_AND_PTR */
              break;
# endif
            default:   /* COV_PDUR_MISRA */
              /* Nothing to do: This should never be reached */
              break;
          }
        }
      }
    }
  }

  PDUR_DUMMY_STATEMENT(rmSrcIdx);       /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(info);   /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(retVal); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */

  return retVal;
}       /* PRQA S 6030, 6080 */ /* MD_MSR_STCYC, MD_MSR_STMIF */
#endif

#if (PDUR_EXISTS_IF_NOBUFFER_GATEWAY_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmIf_ProcessNoBufferedGwRouting
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *********************************************************************************************************************/
/* PRQA S 3673 1 */ /* MD_PduR_3673_AsrProto */
LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_RmIf_ProcessNoBufferedGwRouting(PduR_RmDestRomIterType rmDestIdx, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info)
{
  uint8 errorId = PDUR_E_NO_ERROR;
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Development Error Checks ------------------------------------- */
# if (PDUR_DEV_ERROR_DETECT == STD_ON)  /* COV_PDUR_VAR_DEV_ERROR_DETECT */
  /* Check parameter 'info' */
  if(info == NULL_PTR)
  {
    errorId = PDUR_E_PARAM_POINTER;
  }
  else if(info->SduDataPtr == NULL_PTR)
  {
    errorId = PDUR_E_PARAM_POINTER;
  }
  else
# endif
  {
    PduR_RmIf_RxIndicationNoBuffer(rmDestIdx, info);  /* SBSW_PDUR_API_CALL_FORWARDING_ID_AND_PTR */
    retVal = E_OK;
  }
/* ----- Development Error Report --------------------------------------- */
# if (PDUR_DEV_ERROR_REPORT == STD_ON)
  if(errorId != PDUR_E_NO_ERROR)
  {
    PduR_Det_ReportError(PDUR_FCT_MULTIIFRXIND, errorId);
  }
# endif
  PDUR_DUMMY_STATEMENT(errorId);       /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */

  return retVal;
}       /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif

#if (PDUR_EXISTS_IF_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmIf_ProcessBufferedRouting
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *********************************************************************************************************************/
/* PRQA S 3673 1 */ /* MD_PduR_3673_AsrProto */
LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_RmIf_ProcessBufferedRouting(PduR_RmSrcRomIterType rmSrcIdx, PduR_RmDestRomIterType rmDestIdx, PduR_RmGDestRomIterType rmGDestRomIdx, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info)
{
  uint8 errorId = PDUR_E_NO_ERROR;
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Development Error Checks ------------------------------------- */
# if (PDUR_DEV_ERROR_DETECT == STD_ON)  /* COV_PDUR_VAR_DEV_ERROR_DETECT */
  /* Check parameter 'info' */
  if(info == NULL_PTR)
  {
    errorId = PDUR_E_PARAM_POINTER;
  }
  else if(info->SduDataPtr == NULL_PTR)
  {
    errorId = PDUR_E_PARAM_POINTER;
  }
  else
# endif
  {
# if (PDUR_PDULENGTHHANDLINGSTRATEGYOFRMDESTROM == STD_ON)
    if((PduR_GetPduLengthHandlingStrategyOfRmDestRom(rmDestIdx) == PDUR_SHORTEN_PDULENGTHHANDLINGSTRATEGYOFRMDESTROM)
       || (info->SduLength <= PduR_GetMaxPduLengthOfRmBufferedIfPropertiesRom(PduR_GetRmBufferedIfPropertiesRomIdxOfRmGDestRom(rmGDestRomIdx))))
# endif
    {
# if (PDUR_TRIGGERTRANSMITSUPPORTEDOFRMSRCROM == STD_ON)
    if(PduR_IsTriggerTransmitSupportedOfRmSrcRom(rmSrcIdx))
    {
      uint8 sduData[PDUR_MAX_TRIGGER_TRANSMIT_PDU_SIZE] = { 0 };
      PduInfoType pduInfo;
      pduInfo.SduDataPtr = sduData;
      pduInfo.SduLength = PduR_GetMaxPduLengthOfRmBufferedIfPropertiesRom(PduR_GetRmBufferedIfPropertiesRomIdxOfRmGDestRom(rmGDestRomIdx));

      retVal &= PduR_GetUpIfTriggerTransmitFctPtrOfMmRom(PduR_GetMmRomIdxOfRmSrcRom(rmSrcIdx)) (PduR_GetSrcHndOfRmSrcRom(rmSrcIdx), &pduInfo);      /* SBSW_PDUR_CSL03 */
      PduR_RmIf_Forward2Buffer(rmDestIdx, &pduInfo);        /* SBSW_PDUR_API_CALL_FORWARDING_ID_AND_PTR */
    }
    else
# endif
      {
        PduR_RmIf_Forward2Buffer(rmDestIdx, info);    /* SBSW_PDUR_API_CALL_FORWARDING_ID_AND_PTR */
        retVal &= E_OK;
      }
    }
  }
/* ----- Development Error Report --------------------------------------- */
# if (PDUR_DEV_ERROR_REPORT == STD_ON)
  if(errorId != PDUR_E_NO_ERROR)
  {
    PduR_Det_ReportError(PDUR_FCT_MULTIIFRXIND, errorId);
  }
# endif
  PDUR_DUMMY_STATEMENT(errorId);       /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(rmSrcIdx);       /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(rmGDestRomIdx);       /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */

  return retVal;
}       /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif

#if ((PDUR_EXISTS_T_T_SINGLE_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON) || (PDUR_EXISTS_T_T_FIFO_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON))
/**********************************************************************************************************************
 * PduR_RmIf_TriggerTransmit
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *********************************************************************************************************************/
/* PRQA S 3673 1 */ /* MD_PduR_3673_AsrProto */
LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_RmIf_TriggerTransmit(PduR_RmDestRomIterType rmDestIdx, CONSTP2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info)
{
  Std_ReturnType retVal = E_NOT_OK;
  uint8 errorId = PDUR_E_NO_ERROR;
  /* ----- Development Error Checks ------------------------------------- */
# if (PDUR_DEV_ERROR_DETECT == STD_ON)  /* COV_PDUR_VAR_DEV_ERROR_DETECT */
  /* Check parameter 'info' */
  if(info == NULL_PTR)
  {
    errorId = PDUR_E_PARAM_POINTER;
  }
  else if(info->SduDataPtr == NULL_PTR)
  {
    errorId = PDUR_E_PARAM_POINTER;
  }
  else
# endif
  {
    SchM_Enter_PduR_PDUR_EXCLUSIVE_AREA_0();    /* PRQA S 3109 */ /* MD_MSR_14.3 */
    {
      PduR_RmGDestRomIterType rmGDestIdx = PduR_GetRmGDestRomIdxOfRmDestRom(rmDestIdx);
      PduR_BmTxBufferInstanceRomIterType bmTxBufferInstanceRomIdx = PduR_GetBmTxBufferInstanceRomIdxOfFmFifoInstanceRam(PduR_GetFmFifoInstanceRomIdxOfRmGDestRom(rmGDestIdx));

      if(bmTxBufferInstanceRomIdx != PDUR_NO_BMTXBUFFERINSTANCEROMIDXOFFMFIFOINSTANCERAM) /* COV_PDUR_ONLY_DIRECT_BUFFER */
      {
        if(info->SduLength >= ((PduR_BmTxBufferArrayRamIterType) PduR_Bm_GetLinearDataSizeInstance(bmTxBufferInstanceRomIdx)))
        {
          PduR_RmBufferedIfPropertiesRomIdxOfRmGDestRomType rmBufferedIfPropertiesRomIdx = PduR_GetRmBufferedIfPropertiesRomIdxOfRmGDestRom(rmGDestIdx);
          info->SduLength = (PduLengthType) PduR_Bm_GetLinearDataSizeInstance(bmTxBufferInstanceRomIdx);        /* SBSW_PDUR_VALID_PTR_ENSURED_BY_CALLING_FUNCTION */
          PduR_Bm_CopyData(bmTxBufferInstanceRomIdx, (PduR_BmTxBufferArrayRamIterType) info->SduLength, info->SduDataPtr);      /* SBSW_PDUR_STACK_VARIABLE */

# if (PDUR_EXISTS_T_T_FIFO_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON)
          if(PduR_GetIfSmStateOfRmBufferedIfPropertiesRam(rmBufferedIfPropertiesRomIdx) == PDUR_WAIT_FOR_TRIGGERTRANSMIT_IFSMSTATEOFRMBUFFEREDIFPROPERTIESRAM)
# endif
          {
            /* The Queue is not empty in this states return E_OK */
            PduR_SetIfSmStateOfRmBufferedIfPropertiesRam(rmBufferedIfPropertiesRomIdx, PduR_GetNextState_For_Wait_For_TriggerTransmitOfIfRoutingStateTable(PduR_GetFifoTypeOfRmBufferedIfPropertiesRom(rmBufferedIfPropertiesRomIdx))); /* SBSW_PDUR_IDX_PARAM_INTERNAL_FUNCTION */
            retVal = E_OK;
          }
# if (PDUR_EXISTS_T_T_FIFO_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON)
          else
          {
            PduR_Fm_FlushFiFo(rmGDestIdx);
#  if(PDUR_RMGDESTNTO1INFORAMIDXOFRMGDESTROM == STD_ON)
            PduR_Rm_MultipleSourceHandler_Reset(rmGDestIdx);
#  endif
          }
# endif
        }
      }
    }
    SchM_Exit_PduR_PDUR_EXCLUSIVE_AREA_0();     /* PRQA S 3109 */ /* MD_MSR_14.3 */
  }
  /* ----- Development Error Report --------------------------------------- */
# if (PDUR_DEV_ERROR_REPORT == STD_ON)
  if(errorId != PDUR_E_NO_ERROR)
  {
    PduR_Det_ReportError(PDUR_FCT_RMIF_TXTT, errorId);
  }
# else
  PDUR_DUMMY_STATEMENT(errorId);        /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
# endif
  return retVal;
}       /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif

#if((PDUR_TXCONFIRMATIONUSEDOFTXIF2UP == STD_ON) && ((PDUR_EXISTS_T_T_FIFO_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON) || (PDUR_EXISTS_DIRECT_FIFO_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON)))
/**********************************************************************************************************************
 * PduR_RmIf_TxConfirmation
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_RmIf_TxConfirmation(PduR_RmGDestRomIdxOfTxIf2UpType rmGDestRomIdx)
{
  /* ----- Implementation ----------------------------------------------- */
  SchM_Enter_PduR_PDUR_EXCLUSIVE_AREA_0();      /* PRQA S 3109 */ /* MD_MSR_14.3 */
  {
    PduR_RmBufferedIfPropertiesRomIdxOfRmGDestRomType rmBufferedIfPropertiesRomIdx = PduR_GetRmBufferedIfPropertiesRomIdxOfRmGDestRom(rmGDestRomIdx);

    if(PduR_GetIfSmStateOfRmBufferedIfPropertiesRam(rmBufferedIfPropertiesRomIdx) == PDUR_WAIT_FOR_TXCONFIRMATION_IFSMSTATEOFRMBUFFEREDIFPROPERTIESRAM)
    {
      PduR_FmFifoInstanceRamIterType fmFifoRomInstanceIdx = PduR_GetFmFifoInstanceRomIdxOfRmGDestRom(rmGDestRomIdx);

      PduR_FmFifoRamIterType fmFifoRomIdx = PduR_GetFmFifoRomIdxOfFmFifoInstanceRom(fmFifoRomInstanceIdx);
      PduR_FmFifoElementRamIterType fmFifoElementRamReadIdx = PduR_GetFmFifoElementRamReadIdxOfFmFifoRam(fmFifoRomIdx);
      PduR_FmFifoElementRamIterType peekedfmFifoElementRamReadIdx;
      PduR_GetFctPtrOfFinishReadFmSmTransition(PduR_GetStateOfFmFifoElementRam(fmFifoElementRamReadIdx)) (fmFifoElementRamReadIdx, E_OK);       /* SBSW_PDUR_CSL03 */
      PduR_Bm_ResetTxBufferInstance(PduR_GetBmTxBufferInstanceRomIdxOfFmFifoInstanceRam(PduR_GetFmFifoInstanceRomIdxOfRmGDestRom(rmGDestRomIdx)));
      PduR_SetIfSmStateOfRmBufferedIfPropertiesRam(rmBufferedIfPropertiesRomIdx, PduR_GetNextState_For_Init_If_Routing_StateOfIfRoutingStateTable(PduR_GetFifoTypeOfRmBufferedIfPropertiesRom(rmBufferedIfPropertiesRomIdx)));  /* SBSW_PDUR_IDX_PARAM_INTERNAL_FUNCTION */
      if(PduR_Fm_Peek(fmFifoRomIdx, &peekedfmFifoElementRamReadIdx) == E_OK)    /* SBSW_PDUR_STACK_VARIABLE */
      {
        PduR_RmIf_TransmitPreparation(rmGDestRomIdx, peekedfmFifoElementRamReadIdx);
        {
          PduInfoType destPduInfo;
          PduR_RmDestRomIdxOfFmFifoElementRamType rmDestRomIdx = PduR_GetRmDestRomIdxOfFmFifoElementRam(peekedfmFifoElementRamReadIdx);
          PduR_BmTxBufferInstanceRomIterType bmTxBufferInstanceRomIdx = PduR_GetBmTxBufferInstanceRomIdxOfFmFifoInstanceRam(PduR_GetFmFifoInstanceRomIdxOfRmGDestRom(rmGDestRomIdx));
          PduR_Bm_CopyDataAsPtr(bmTxBufferInstanceRomIdx, &destPduInfo, PduR_Bm_GetLinearDataSizeInstance(bmTxBufferInstanceRomIdx));   /* SBSW_PDUR_API_CALL_FORWARDING_ID_AND_PTR */
          if(E_OK != PduR_RmIf_MultipleSourceHandler_Transmit(rmDestRomIdx, &destPduInfo, TRUE))        /* SBSW_PDUR_API_CALL_FORWARDING_ID_AND_PTR */
          {
            PduR_Fm_FlushFiFo(rmGDestRomIdx);
            PduR_Det_ReportError(PDUR_FCT_RMIF_TXCONF, PDUR_E_PDU_INSTANCES_LOST);
          }
        }
      }
    }
    else
    {
      PduR_Fm_FlushFiFo(rmGDestRomIdx);
# if(PDUR_RMGDESTNTO1INFORAMIDXOFRMGDESTROM == STD_ON)
      PduR_Rm_MultipleSourceHandler_Reset(rmGDestRomIdx);
# endif
      PduR_Det_ReportError(PDUR_FCT_RMIF_TXCONF, PDUR_E_PDU_INSTANCES_LOST);
    }
  }
  SchM_Exit_PduR_PDUR_EXCLUSIVE_AREA_0();       /* PRQA S 3109 */ /* MD_MSR_14.3 */
}       /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

#if((PDUR_EXISTS_T_T_FIFO_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON) || (PDUR_EXISTS_DIRECT_FIFO_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON) || (PDUR_EXISTS_T_T_SINGLE_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON))
/**********************************************************************************************************************
 * PduR_RmIf_CalcDlc
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
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(PduLengthType, PDUR_CODE) PduR_RmIf_CalcDlc(PduR_RmGDestRomIdxOfRmDestRomType rmGDest, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info)
{
  /* if the length is shorter or equal use the provided length */
  PduLengthType dataLengthcopy = info->SduLength;
  /* MaxPduLength of no buffer routings is set to the maximum allowed value for this datatype, thus disabling this check */
  if(info->SduLength > PduR_GetMaxPduLengthOfRmBufferedIfPropertiesRom(PduR_GetRmBufferedIfPropertiesRomIdxOfRmGDestRom(rmGDest)))
  {
    /* if the provided length is greater than the maximum buffer size the value is truncated to this value. */
    dataLengthcopy = PduR_GetMaxPduLengthOfRmBufferedIfPropertiesRom(PduR_GetRmBufferedIfPropertiesRomIdxOfRmGDestRom(rmGDest));
  }
  PDUR_DUMMY_STATEMENT(rmGDest);        /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  return dataLengthcopy;
}
#endif

#if ((PDUR_EXISTS_T_T_SINGLE_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON) || (PDUR_EXISTS_DIRECT_FIFO_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON) || (PDUR_EXISTS_T_T_FIFO_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON))
/**********************************************************************************************************************
 * PduR_Fm_FlushFiFo
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_Fm_FlushFiFo(PduR_RmGDestRomIterType rmGDestRomIdx)
{
  PduR_FmFifoRomIterType fmFifoRomIdx = PduR_GetFmFifoRomIdxOfFmFifoInstanceRom(PduR_GetFmFifoInstanceRomIdxOfRmGDestRom(rmGDestRomIdx));
  PduR_FmFifoElementRamIterType fmFifoElementRamIdx;
  PduR_RmBufferedIfPropertiesRomIdxOfRmGDestRomType rmBufferedIfPropertiesRomIdx = PduR_GetRmBufferedIfPropertiesRomIdxOfRmGDestRom(rmGDestRomIdx);

  for(fmFifoElementRamIdx = PduR_GetFmFifoElementRamStartIdxOfFmFifoRom(fmFifoRomIdx); fmFifoElementRamIdx < PduR_GetFmFifoElementRamEndIdxOfFmFifoRom(fmFifoRomIdx); fmFifoElementRamIdx++)
  {
    PduR_GetFctPtrOfFmFlushFifoElement(PduR_GetStateOfFmFifoElementRam(fmFifoElementRamIdx)) (fmFifoElementRamIdx);     /* SBSW_PDUR_CSL01 */
  }
  PduR_SetIfSmStateOfRmBufferedIfPropertiesRam(rmBufferedIfPropertiesRomIdx, PduR_GetNextState_For_Init_If_Routing_StateOfIfRoutingStateTable(PduR_GetFifoTypeOfRmBufferedIfPropertiesRom(rmBufferedIfPropertiesRomIdx)));      /* SBSW_PDUR_IDX_PARAM_INTERNAL_FUNCTION */
  PduR_SetFillLevelOfFmFifoRam(fmFifoRomIdx, 0);        /* SBSW_PDUR_CSL01 */
  PduR_SetFmFifoElementRamReadIdxOfFmFifoRam(fmFifoRomIdx, PduR_GetFmFifoElementRamStartIdxOfFmFifoRom(fmFifoRomIdx));  /* SBSW_PDUR_CSL01 */
  PduR_SetFmFifoElementRamWriteIdxOfFmFifoRam(fmFifoRomIdx, PduR_GetFmFifoElementRamStartIdxOfFmFifoRom(fmFifoRomIdx)); /* SBSW_PDUR_CSL01 */
}
#endif

#if ((PDUR_EXISTS_T_T_SINGLE_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON) || (PDUR_EXISTS_DIRECT_FIFO_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON) || (PDUR_EXISTS_T_T_FIFO_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON))
/**********************************************************************************************************************
 * PduR_Fm_FlushFiFoElement_ReadActive
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_Fm_FlushFiFoElement_ReadActive(PduR_FmFifoElementRamIterType fmFifoElementRamIdx)
{
  PduR_BmTxBufferRomIdxOfFmFifoElementRamType bmTxBufferRomIdx = PduR_GetBmTxBufferRomIdxOfFmFifoElementRam(fmFifoElementRamIdx);
  PduR_BmTxBufferInstanceRomStartIdxOfBmTxBufferRomType bmTxBufferInstanceRomIdx = PduR_GetBmTxBufferInstanceRomStartIdxOfBmTxBufferRom(bmTxBufferRomIdx);
  PduR_Fm_ReleaseFifoElement(fmFifoElementRamIdx);
  if(PduR_IsDedicatedTxBufferOfFmFifoElementRam(fmFifoElementRamIdx))   /* COV_PDUR_ONLY_DEDICATED_BUFFER */
  {
    PduR_SetStateOfFmFifoElementRam(fmFifoElementRamIdx, PDUR_FM_ALLOCATED_WITH_BUFFER_STATEOFFMFIFOELEMENTRAM);        /* SBSW_PDUR_CSL01 */
  }
  else
  {
    PduR_SetStateOfFmFifoElementRam(fmFifoElementRamIdx, PDUR_FM_IDLE_STATEOFFMFIFOELEMENTRAM); /* SBSW_PDUR_CSL01 */
    PduR_Fm_DissolveFifoElementTxBufferRelation(fmFifoElementRamIdx);
  }
  PduR_Bm_ResetTxBuffer(bmTxBufferRomIdx);
  PduR_Bm_ResetTxBufferInstance(bmTxBufferInstanceRomIdx);
}
#endif

#if ((PDUR_EXISTS_T_T_SINGLE_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON) || (PDUR_EXISTS_DIRECT_FIFO_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON) || (PDUR_EXISTS_T_T_FIFO_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON))
/**********************************************************************************************************************
 * PduR_Fm_FlushFiFoElement_ReadInActive
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_Fm_FlushFiFoElement_ReadInActive(PduR_FmFifoElementRamIterType fmFifoElementRamIdx)
{
  PduR_BmTxBufferRomIdxOfFmFifoElementRamType bmTxBufferRomIdx = PduR_GetBmTxBufferRomIdxOfFmFifoElementRam(fmFifoElementRamIdx);
  PduR_Fm_ReleaseFifoElement(fmFifoElementRamIdx);
  if(PduR_IsDedicatedTxBufferOfFmFifoElementRam(fmFifoElementRamIdx))   /* COV_PDUR_ONLY_DEDICATED_BUFFER */
  {
    PduR_SetStateOfFmFifoElementRam(fmFifoElementRamIdx, PDUR_FM_ALLOCATED_WITH_BUFFER_STATEOFFMFIFOELEMENTRAM);        /* SBSW_PDUR_CSL01 */
  }
  else
  {
    PduR_SetStateOfFmFifoElementRam(fmFifoElementRamIdx, PDUR_FM_IDLE_STATEOFFMFIFOELEMENTRAM); /* SBSW_PDUR_CSL01 */
    PduR_Fm_DissolveFifoElementTxBufferRelation(fmFifoElementRamIdx);
  }
  PduR_Bm_ResetTxBuffer(bmTxBufferRomIdx);
}
#endif

#if ((PDUR_EXISTS_T_T_SINGLE_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON) || (PDUR_EXISTS_DIRECT_FIFO_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON) || (PDUR_EXISTS_T_T_FIFO_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON))
/**********************************************************************************************************************
 * PduR_Fm_FlushFiFoElement_NoAction
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_Fm_FlushFiFoElement_NoAction(PduR_FmFifoElementRamIterType fmFifoElementRamIdx)      /* COV_PDUR_ONLY_TT_SINGLE_BUFFER */
{
  PDUR_DUMMY_STATEMENT(fmFifoElementRamIdx);    /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
}
#endif

#if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmTp_StartOfReception
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *********************************************************************************************************************/
/* PRQA S 3673 3 */ /* MD_PduR_3673_AsrProto */
LOCAL_INLINE FUNC(BufReq_ReturnType, PDUR_CODE) PduR_RmTp_StartOfReception(PduR_RmSrcRomIdxOfRxTp2DestType rmSrcIdx,
                                                                           P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info,
                                                                           PduLengthType TpSduLength, P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) bufferSizePtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  BufReq_ReturnType retVal = BUFREQ_E_NOT_OK;
  uint8 errorId = PDUR_E_NO_ERROR;

# if (PDUR_DEV_ERROR_DETECT == STD_ON)  /* COV_PDUR_VAR_DEV_ERROR_DETECT */
  /* Check parameter bufferSizePtr */
  if(bufferSizePtr == NULL_PTR)
  {
    errorId = PDUR_E_PARAM_POINTER;
  }
#  if (PDUR_METADATA_SUPPORT == STD_ON)
  else if((PduR_IsMetaDataLengthUsedOfRmBufferedTpPropertiesRom(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx))) && ((info == NULL_PTR) || (info->SduDataPtr == NULL_PTR) || (info->SduLength < (PduLengthType) PduR_GetMetaDataLengthOfRmBufferedTpPropertiesRom(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx)))))        /* COV_PDUR_FEATURE_ALWAYS_TRUE */
  {
    errorId = PDUR_E_PARAM_POINTER;
  }
#  endif
  else
# endif
  {
    /* ----- Implementation ----------------------------------------------- */
    SchM_Enter_PduR_PDUR_EXCLUSIVE_AREA_0();    /* PRQA S 3109 */ /* MD_MSR_14.3 */
    {
      /* Handle src instance routing state */
      PduR_TpRxSmStateOfRmBufferedTpPropertiesRamType tpRxSmState = PduR_GetTpRxSmStateOfRmBufferedTpPropertiesRam(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx));
      /** Guard/Action: enqueue meta data **/
      retVal = PduR_GetFctPtrOfStartOfReceptionRxSmTransition(tpRxSmState) ((PduR_RmSrcRomIterType) rmSrcIdx, info, TpSduLength, bufferSizePtr);        /* SBSW_PDUR_CSL03 */
    }
    SchM_Exit_PduR_PDUR_EXCLUSIVE_AREA_0();     /* PRQA S 3109 */ /* MD_MSR_14.3 */
  }
# if (PDUR_DEV_ERROR_REPORT == STD_ON)
  if(errorId != PDUR_E_NO_ERROR)
  {
    PduR_Det_ReportError(PDUR_FCT_GWTP_SORX, errorId);
  }
# else
  PDUR_DUMMY_STATEMENT(errorId);        /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
# endif
  return retVal;
}
#endif

#if (PDUR_METADATA_SUPPORT == STD_ON)
/**********************************************************************************************************************
 * PduR_RmTp_StartOfReceptionQueueMetaData
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(BufReq_ReturnType, PDUR_CODE) PduR_RmTp_StartOfReceptionQueueMetaData(PduR_RmSrcRomIterType rmSrcIdx,
                                                                                        PduR_BmTxBufferArrayRamIterType pduLength,
                                                                                        SduDataPtrType sduDataPtr, P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) bufferSizePtr)
{
  BufReq_ReturnType retVal;
  PduR_BmTxBufferArrayRamIterType metadataStartPosition =
    pduLength - (PduR_BmTxBufferArrayRamIterType) PduR_GetMetaDataLengthOfRmBufferedTpPropertiesRom(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx));
  PduR_FmFifoElementRamIterType fmFifoElementRamWriteIdx = PduR_GetFmFifoElementRamIdxOfRmBufferedTpPropertiesRam(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx));
  PduR_BmTxBufferRomIterType bmTxBufferRomIdx = PduR_GetBmTxBufferRomIdxOfFmFifoElementRam(fmFifoElementRamWriteIdx);
  /* Metadata is appended after the payload data */
  /* Length information is used to enqueue the MetaData */
  pduLength = (PduR_BmTxBufferArrayRamIterType) PduR_GetMetaDataLengthOfRmBufferedTpPropertiesRom(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx));
  /* enqueue data will never fail in this context because the buffer is always empty */
  retVal = PduR_Bm_PutData((PduR_BmTxBufferRomIterType) bmTxBufferRomIdx, pduLength, &sduDataPtr[metadataStartPosition]);       /* SBSW_PDUR_STACK_VARIABLE */
  *bufferSizePtr = (PduLengthType) PduR_Bm_GetTotalBufferSize(bmTxBufferRomIdx);        /* SBSW_PDUR_VALID_PTR_ENSURED_BY_CALLING_FUNCTION */
  return retVal;
}
#endif
#if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmTp_CopyRxData
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *********************************************************************************************************************/
/* PRQA S 3673 2 */ /* MD_PduR_3673_AsrProto */
LOCAL_INLINE FUNC(BufReq_ReturnType, PDUR_CODE) PduR_RmTp_CopyRxData(PduR_RmSrcRomIdxOfRxTp2DestType rmSrcIdx, P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info,
                                                                     P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) bufferSizePtr)
{
  BufReq_ReturnType retVal = BUFREQ_E_NOT_OK;

  uint8 errorId = PDUR_E_NO_ERROR;
  /* ----- Development Error Checks ------------------------------------- */
# if (PDUR_DEV_ERROR_DETECT == STD_ON)  /* COV_PDUR_VAR_DEV_ERROR_DETECT */

  /* Check parameter 'info' */
  if(info == NULL_PTR)
  {
    errorId = PDUR_E_PARAM_POINTER;
  }
  else if((info->SduLength > 0) && (info->SduDataPtr == NULL_PTR))
  {
    errorId = PDUR_E_PARAM_POINTER;
  }
  else if(bufferSizePtr == NULL_PTR)
  {
    errorId = PDUR_E_PARAM_POINTER;
  }
  else
# endif
  {
    /* ----- Implementation ----------------------------------------------- */
    SchM_Enter_PduR_PDUR_EXCLUSIVE_AREA_0();    /* PRQA S 3109 */ /* MD_MSR_14.3 */
    {
      /* Handle src instance routing state */
      retVal = PduR_GetFctPtrOfCopyRxDataRxSmTransition(PduR_GetTpRxSmStateOfRmBufferedTpPropertiesRam(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx))) ((PduR_RmSrcRomIterType) rmSrcIdx, info->SduLength, info->SduDataPtr, bufferSizePtr); /* SBSW_PDUR_CSL03 */
    }
    SchM_Exit_PduR_PDUR_EXCLUSIVE_AREA_0();     /* PRQA S 3109 */ /* MD_MSR_14.3 */
  }
  /* ----- Development Error Report --------------------------------------- */
# if (PDUR_DEV_ERROR_REPORT == STD_ON)
  if(errorId != PDUR_E_NO_ERROR)
  {
    PduR_Det_ReportError(PDUR_FCT_GWTP_CPYRX, errorId);
  }
# else
  PDUR_DUMMY_STATEMENT(errorId);        /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
# endif
  return retVal;
}       /* PRQA S 6080, 6030, 6050 */ /* MD_MSR_STMIF, MD_MSR_STCYC, MD_MSR_STCAL */
#endif

#if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmTp_AssignAssociatedBuffer2Destination
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_RmTp_AssignAssociatedBuffer2Destination(PduR_BmTxBufferRomIterType bmTxBufferRomIdx, PduR_RmSrcRomIterType rmSrcIdx)
{
  PduR_RmDestRomStartIdxOfRmSrcRomType rmDestRomIdx;
  PduR_BmTxBufferInstanceRomStartIdxOfBmTxBufferRomType bmTxBufferInstanceRomIdx = PduR_GetBmTxBufferInstanceRomStartIdxOfBmTxBufferRom(bmTxBufferRomIdx);
  for(rmDestRomIdx = PduR_GetRmDestRomStartIdxOfRmSrcRom(rmSrcIdx); rmDestRomIdx < PduR_GetRmDestRomEndIdxOfRmSrcRom(rmSrcIdx); rmDestRomIdx++)
  {
    PduR_RmGDestRomIdxOfRmDestRomType rmGDestRomIdx = PduR_GetRmGDestRomIdxOfRmDestRom(rmDestRomIdx);

    PduR_Bm_AssignAssociatedBuffer2DestinationInstance(bmTxBufferRomIdx, bmTxBufferInstanceRomIdx);
    PduR_SetBmTxBufferInstanceRomIdxOfFmFifoInstanceRam(PduR_GetFmFifoInstanceRomIdxOfRmGDestRom(rmGDestRomIdx), bmTxBufferInstanceRomIdx);     /* SBSW_PDUR_CSL03 */
    bmTxBufferInstanceRomIdx++;
  }
}
#endif

#if ((PDUR_EXISTS_T_T_SINGLE_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON) || (PDUR_EXISTS_DIRECT_FIFO_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON) || (PDUR_EXISTS_T_T_FIFO_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON))
/**********************************************************************************************************************
 * PduR_RmIf_AssignAssociatedBuffer2Destination
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_RmIf_AssignAssociatedBuffer2Destination(PduR_BmTxBufferRomIterType bmTxBufferRomIdx, PduR_RmGDestRomIterType rmGDestRomIdx)
{
  PduR_BmTxBufferInstanceRomStartIdxOfBmTxBufferRomType bmTxBufferInstanceRomIdx = PduR_GetBmTxBufferInstanceRomStartIdxOfBmTxBufferRom(bmTxBufferRomIdx);
  PduR_Bm_AssignAssociatedBuffer2DestinationInstance(bmTxBufferRomIdx, bmTxBufferInstanceRomIdx);
  PduR_SetBmTxBufferInstanceRomIdxOfFmFifoInstanceRam(PduR_GetFmFifoInstanceRomIdxOfRmGDestRom(rmGDestRomIdx), bmTxBufferInstanceRomIdx);       /* SBSW_PDUR_CSL03 */
}
#endif

#if ((PDUR_UPTPOFMMROM == STD_ON) && (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON))
/**********************************************************************************************************************
 * PduR_RmTp_UpTransmit
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
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_RmTp_UpTransmit(PduR_RmSrcRomIterType rmSrcIdx, PduR_RmDestRomIterType rmDestTpIdx)
{
  Std_ReturnType retVal = E_NOT_OK;
  BufReq_ReturnType retValBufReq;
  PduLengthType bufferSizePtr = 0;
  /* Forwarding to an upper layer module */
  PduR_RmGDestRomIdxOfRmDestRomType rmGDestRomIdx = PduR_GetRmGDestRomIdxOfRmDestRom(rmDestTpIdx);
  PduR_BmTxBufferInstanceRomIterType bmTxBufferInstanceRomIdx = PduR_GetBmTxBufferInstanceRomIdxOfFmFifoInstanceRam(PduR_GetFmFifoInstanceRomIdxOfRmGDestRom(rmGDestRomIdx));
  /* If MetaData are available the pUpperLayerInfo points to MetaData */
  {
# if (PDUR_METADATA_SUPPORT == STD_ON )
    if(PduR_IsMetaDataLengthUsedOfRmBufferedTpPropertiesRom(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx)))
    {
      PduInfoType metaInfo;

      PduR_Bm_GetDataAsPtr(bmTxBufferInstanceRomIdx, &metaInfo, PduR_GetMetaDataLengthOfRmBufferedTpPropertiesRom(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx)));   /* SBSW_PDUR_API_CALL_FORWARDING_ID_AND_PTR */

      retValBufReq = PduR_GetUpTpStartOfReceptionFctPtrOfMmRom(PduR_GetMmRomIdxOfRmGDestRom(rmGDestRomIdx)) (PduR_GetDestHndOfRmGDestRom(rmGDestRomIdx), &metaInfo, (PduLengthType) PduR_Bm_GetTotalDataTranferredLength(bmTxBufferInstanceRomIdx), &bufferSizePtr);    /* SBSW_PDUR_API_CALL_FORWARDING_ID_AND_PTR */
    }
    else
# endif
    {
      retValBufReq = PduR_GetUpTpStartOfReceptionFctPtrOfMmRom(PduR_GetMmRomIdxOfRmGDestRom(rmGDestRomIdx)) (PduR_GetDestHndOfRmGDestRom(rmGDestRomIdx), (P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA)) NULL_PTR, (PduLengthType) PduR_Bm_GetTotalDataTranferredLength(bmTxBufferInstanceRomIdx), &bufferSizePtr);     /* SBSW_PDUR_API_CALL_FORWARDING_ID_AND_PTR */
    }
  }
  if(retValBufReq == BUFREQ_OK)
  {
    /* RfC 52242 - Transport Protocol Gateway Reception to upper layer modules is not functional */
    /* \trace SPEC-2020098 */
    if(bufferSizePtr < PduR_Bm_GetTotalDataTranferredLength(bmTxBufferInstanceRomIdx))
    {
      PduR_GetUpTpTpRxIndicationFctPtrOfMmRom(PduR_GetMmRomIdxOfRmGDestRom(rmGDestRomIdx)) (PduR_GetDestHndOfRmGDestRom(rmGDestRomIdx), E_NOT_OK);      /* SBSW_PDUR_API_CALL_FORWARDING_ID_ONLY */
    }
    else
    {
      PduInfoType info;

      PduR_Bm_GetDataAsPtr(bmTxBufferInstanceRomIdx, &info, PduR_Bm_GetLinearDataSizeInstance(bmTxBufferInstanceRomIdx));       /* SBSW_PDUR_API_CALL_FORWARDING_ID_ONLY */

      if(BUFREQ_OK == PduR_GetUpTpCopyRxDataFctPtrOfMmRom(PduR_GetMmRomIdxOfRmGDestRom(rmGDestRomIdx)) (PduR_GetDestHndOfRmGDestRom(rmGDestRomIdx), &info, &bufferSizePtr))     /* SBSW_PDUR_API_CALL_FORWARDING_ID_AND_PTR */
      {
        PduR_GetUpTpTpRxIndicationFctPtrOfMmRom(PduR_GetMmRomIdxOfRmGDestRom(rmGDestRomIdx)) (PduR_GetDestHndOfRmGDestRom(rmGDestRomIdx), E_OK);        /* SBSW_PDUR_API_CALL_FORWARDING_ID_ONLY */
        retVal = E_OK;
      }
      else      /* \trace SPEC-2020102 */
      {
        PduR_GetUpTpTpRxIndicationFctPtrOfMmRom(PduR_GetMmRomIdxOfRmGDestRom(rmGDestRomIdx)) (PduR_GetDestHndOfRmGDestRom(rmGDestRomIdx), E_NOT_OK);    /* SBSW_PDUR_API_CALL_FORWARDING_ID_ONLY */
      }
    }
  }
  PDUR_DUMMY_STATEMENT(rmSrcIdx);       /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  return retVal;
}
#endif
#if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
  PduR_RmTp_LoTransmit
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_RmTp_LoTransmit(PduR_RmSrcRomIterType rmSrcIdx, PduR_RmDestRomIterType rmDestTpIdx)
{
  Std_ReturnType retVal = E_NOT_OK;
  PduR_RmGDestRomIterType rmGDestRomIdx = PduR_GetRmGDestRomIdxOfRmDestRom(rmDestTpIdx);

  PduInfoType info;
  PduR_BmTxBufferInstanceRomIterType bmTxBufferInstanceRomIdx = PduR_GetBmTxBufferInstanceRomIdxOfFmFifoInstanceRam(PduR_GetFmFifoInstanceRomIdxOfRmGDestRom(rmGDestRomIdx));

  /* Get Data Pointer for Transmit */
  PduR_Bm_CopyDataAsPtr(bmTxBufferInstanceRomIdx, &info, PduR_Bm_GetTotalDataTranferredLength(bmTxBufferInstanceRomIdx));       /* SBSW_PDUR_API_CALL_FORWARDING_ID_AND_PTR */
# if (PDUR_METADATA_SUPPORT == STD_ON)
  if(PduR_IsMetaDataLengthUsedOfRmBufferedTpPropertiesRom(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx)))
  {
    /* Get Meta Daten Pointer for Transmit */
    PduR_Bm_GetDataAsPtr(bmTxBufferInstanceRomIdx, &info, (PduR_BmTxBufferArrayRamIterType) PduR_GetMetaDataLengthOfRmBufferedTpPropertiesRom(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx)));       /* SBSW_PDUR_API_CALL_FORWARDING_ID_AND_PTR */
  }
# endif
  /* Correction of the length according to AUTOSAR */
  info.SduLength = (PduLengthType) PduR_Bm_GetTotalDataTranferredLength(bmTxBufferInstanceRomIdx);
  if(E_OK == PduR_RmTp_MultipleSourceHandler_Transmit(rmDestTpIdx, &info))        /* SBSW_PDUR_API_CALL_FORWARDING_ID_AND_PTR */
  {
    retVal &= E_OK;
  }
  else
  {
    PduR_GetFctPtrOfTpTxConfirmationTxSmTransition(PduR_GetTpTxInstSmStateOfRmGDestTpTxStateRam(PduR_GetRmGDestTpTxStateRamIdxOfRmGDestRom(rmGDestRomIdx))) (rmGDestRomIdx, E_NOT_OK);  /* SBSW_PDUR_CSL03 */
  }
  PDUR_DUMMY_STATEMENT(rmSrcIdx);       /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  return retVal;
}
#endif
#if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
  PduR_RmTp_LoAndUpTransmit
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *********************************************************************************************************************/

LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_RmTp_LoAndUpTransmit(PduR_RmSrcRomIterType rmSrcIdx, PduR_RmDestRomIterType rmDestIdx)
{
  Std_ReturnType retVal = E_NOT_OK;
  /* Confirmations are decremented in the Context of LoAndUpTransmit and CopyTxData */
  {
    /* Iterate over all routing destinations (1:N) */
# if (PDUR_RMDESTRPGROMIDXOFRMDESTROM == STD_ON)
    if((PduR_IsRmDestRpgRomUsedOfRmDestRom(rmDestIdx)) && (0 == PduR_GetEnabledCntOfRmDestRpgRam(PduR_GetRmDestRpgRomIdxOfRmDestRom(rmDestIdx))))
    {
      PduR_RmGDestRomIterType rmGDestRomIdx = PduR_GetRmGDestRomIdxOfRmDestRom(rmDestIdx);
      PduR_GetFctPtrOfTpTxConfirmationTxSmTransition(PduR_GetTpTxInstSmStateOfRmGDestTpTxStateRam(PduR_GetRmGDestTpTxStateRamIdxOfRmGDestRom(rmGDestRomIdx))) (rmGDestRomIdx, E_NOT_OK);        /* SBSW_PDUR_CSL03 */
    }
    else
# endif
    {
      if(PduR_GetDirectionOfRmDestRom(rmDestIdx) == PDUR_TX_DIRECTIONOFRMDESTROM)       /* COV_PDUR_FEATURE_ALWAYS_TRUE */
      {
        retVal = PduR_RmTp_LoTransmit(rmSrcIdx, rmDestIdx);
      }
# if (PDUR_UPTPOFMMROM == STD_ON)
      else
      {
        PduR_RmGDestRomIterType rmGDestRomIdx = PduR_GetRmGDestRomIdxOfRmDestRom(rmDestIdx);
        if(E_OK == PduR_RmTp_UpTransmit(rmSrcIdx, rmDestIdx))
        {
          retVal &= E_OK;
          PduR_GetFctPtrOfTpTxConfirmationTxSmTransition(PduR_GetTpTxInstSmStateOfRmGDestTpTxStateRam(PduR_GetRmGDestTpTxStateRamIdxOfRmGDestRom(rmGDestRomIdx))) (rmGDestRomIdx, E_OK);        /* SBSW_PDUR_CSL03 */
        }
        else
        {
          PduR_GetFctPtrOfTpTxConfirmationTxSmTransition(PduR_GetTpTxInstSmStateOfRmGDestTpTxStateRam(PduR_GetRmGDestTpTxStateRamIdxOfRmGDestRom(rmGDestRomIdx))) (rmGDestRomIdx, E_NOT_OK);    /* SBSW_PDUR_CSL03 */
        }
      }
# endif
    }
  }
  return retVal;
}
#endif
#if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmTp_TpRxIndication
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_RmTp_TpRxIndication(PduR_RmSrcRomIdxOfRxTp2DestType rmSrcIdx, Std_ReturnType result)
{
  /* ----- Implementation ----------------------------------------------- */
  SchM_Enter_PduR_PDUR_EXCLUSIVE_AREA_0();      /* PRQA S 3109 */ /* MD_MSR_14.3 */
  {
    /* Handle src instance routing state */
    PduR_TpRxSmStateOfRmBufferedTpPropertiesRamType tpRxSmState = PduR_GetTpRxSmStateOfRmBufferedTpPropertiesRam(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx));
    PduR_GetFctPtrOfTpRxIndicationRxSmTransition(tpRxSmState) ((PduR_RmSrcRomIterType) rmSrcIdx, result);       /* SBSW_PDUR_CSL03 */
  }
  SchM_Exit_PduR_PDUR_EXCLUSIVE_AREA_0();       /* PRQA S 3109 */ /* MD_MSR_14.3 */
}
#endif

#if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmTp_CopyTxData
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *********************************************************************************************************************/
/* PRQA S 3673 3 */ /* MD_PduR_3673_AsrProto */
LOCAL_INLINE FUNC(BufReq_ReturnType, PDUR_CODE) PduR_RmTp_CopyTxData(PduR_RmGDestRomIdxOfTxTp2SrcType rmGDestRomIdx,
                                                                     P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info,
                                                                     P2VAR(RetryInfoType, AUTOMATIC, PDUR_APPL_DATA) retry, P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) availableDataPtr)
{
  BufReq_ReturnType retVal = BUFREQ_E_NOT_OK;
  uint8 errorId = PDUR_E_NO_ERROR;
  /* ----- Development Error Checks ------------------------------------- */
# if (PDUR_DEV_ERROR_DETECT == STD_ON)  /* COV_PDUR_VAR_DEV_ERROR_DETECT */
  /* parameter 'Handle Id' already checked by the caller API */
  /* Check parameter 'info' */
  if(info == NULL_PTR)
  {
    errorId = PDUR_E_PARAM_POINTER;
  }
  else if((info->SduLength > 0) && (info->SduDataPtr == NULL_PTR))
  {
    errorId = PDUR_E_PARAM_POINTER;
  }
  else if(availableDataPtr == NULL_PTR)
  {
    errorId = PDUR_E_PARAM_POINTER;
  }
  else
# endif
  {
    /* ----- Implementation ----------------------------------------------- */
    SchM_Enter_PduR_PDUR_EXCLUSIVE_AREA_0();    /* PRQA S 3109 */ /* MD_MSR_14.3 */
    {
      /* Handle global routing state */
      retVal = PduR_GetFctPtrOfCopyTxDataTxInstSmTransition(PduR_GetTpTxInstSmStateOfRmGDestTpTxStateRam(PduR_GetRmGDestTpTxStateRamIdxOfRmGDestRom(rmGDestRomIdx))) ((PduR_RmGDestRomIterType) rmGDestRomIdx, info->SduLength, info->SduDataPtr, retry, availableDataPtr);     /* SBSW_PDUR_CSL03 */
    }
    SchM_Exit_PduR_PDUR_EXCLUSIVE_AREA_0();     /* PRQA S 3109 */ /* MD_MSR_14.3 */
    PDUR_DUMMY_STATEMENT(retry);        /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  }
  /* ----- Development Error Report --------------------------------------- */
# if (PDUR_DEV_ERROR_REPORT == STD_ON)
  if(errorId != PDUR_E_NO_ERROR)
  {
    PduR_Det_ReportError(PDUR_FCT_GWTP_CPYTX, errorId);
  }
# else
  PDUR_DUMMY_STATEMENT(errorId);        /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
# endif
  return retVal;
}       /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif

#if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmTp_TpTxConfirmation
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_RmTp_TpTxConfirmation(PduR_RmGDestRomIdxOfTxTp2SrcType rmGDestRomIdx, Std_ReturnType result)
{
  /* ----- Implementation ----------------------------------------------- */
  SchM_Enter_PduR_PDUR_EXCLUSIVE_AREA_0();      /* PRQA S 3109 */ /* MD_MSR_14.3 */
  {
    /* Handle global routing state */
    PduR_GetFctPtrOfTpTxConfirmationTxSmTransition(PduR_GetTpTxInstSmStateOfRmGDestTpTxStateRam(PduR_GetRmGDestTpTxStateRamIdxOfRmGDestRom(rmGDestRomIdx))) ((PduR_RmGDestRomIterType) rmGDestRomIdx, result);  /* SBSW_PDUR_CSL03 */
  }
  SchM_Exit_PduR_PDUR_EXCLUSIVE_AREA_0();       /* PRQA S 3109 */ /* MD_MSR_14.3 */
}
#endif

#if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_Rm_ThresholdReached
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_Rm_ThresholdReached(PduR_RmSrcRomIterType rmSrcIdx)
{
  /* Trigger transmission if required */
  Std_ReturnType retVal = E_NOT_OK;
  PduR_FmFifoElementRamIterType fmFifoElementRamWriteIdx = PduR_GetFmFifoElementRamIdxOfRmBufferedTpPropertiesRam(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx));
  PduR_BmTxBufferArrayRamIterType availableTotalDataSize = PduR_Bm_GetLinearDataSize(PduR_GetBmTxBufferRomIdxOfFmFifoElementRam(fmFifoElementRamWriteIdx));
  /* MetaData length are not take into account to calculate the Threshold */
# if (PDUR_METADATA_SUPPORT == STD_ON )
  if(PduR_IsMetaDataLengthUsedOfRmBufferedTpPropertiesRom(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx)))    /* COV_PDUR_FEATURE_ALWAYS_TRUE */
  {
    availableTotalDataSize -= (PduR_BmTxBufferArrayRamIterType) PduR_GetMetaDataLengthOfRmBufferedTpPropertiesRom(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx));
  }
# endif
  /* Threshold reached or reception finished (sub state machine is in IDLE) */
  if(availableTotalDataSize >= PduR_GetTpThresholdOfRmBufferedTpPropertiesRom(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx)))
  {
    retVal = E_OK;
  }
  return retVal;
}
#endif

#if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM  == STD_ON)
/**********************************************************************************************************************
 * PduR_RxSm_StartOfReception_RmRxIdle
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
 *********************************************************************************************************************/
FUNC(BufReq_ReturnType, PDUR_CODE) PduR_RxSm_StartOfReception_RmRxIdle(PduR_RmSrcRomIterType rmSrcIdx,
                                                                       P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info, PduLengthType TpSduLength, P2VAR(PduLengthType, AUTOMATIC,
                                                                                                                                                              PDUR_APPL_DATA) bufferSizePtr)
{
  BufReq_ReturnType retVal = BUFREQ_OK;
  /* Allocate FiFo element */
  PduR_FmFifoRomIterType fmFifoRomIdx = PduR_GetFmFifoRomIdxOfRmBufferedTpPropertiesRom(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx));
  PduR_FmFifoElementRamWriteIdxOfFmFifoRamType fmFifoElementRamIdx = 0U;
  if(PduR_Fm_AssignFifoElement(fmFifoRomIdx, &fmFifoElementRamIdx) == E_OK)     /* SBSW_PDUR_STACK_VARIABLE */
  {
    PduR_BmTxBufferRomIdxOfBmTxBufferIndRomType allocatedTxBufferIdxPtr = 0U;
    /* Update fill level */
    PduR_IncFillLevelOfFmFifoRam(fmFifoRomIdx); /* SBSW_PDUR_CSL03 */
    /* Mapping Src Handle and current Fifo element */
    PduR_SetFmFifoElementRamIdxOfRmBufferedTpPropertiesRam(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx), fmFifoElementRamIdx);      /* SBSW_PDUR_CSL03 */
    /* Store related routing source in Fifo Manager Ram table: first destination is saved as it is only used to go to the corresponding RmSrc later */
    PduR_SetRmDestRomIdxOfFmFifoElementRam(fmFifoElementRamIdx, (PduR_RmDestRomIdxOfFmFifoElementRamType) PduR_GetRmDestRomStartIdxOfRmSrcRom(rmSrcIdx));       /* SBSW_PDUR_CSL03 */

    /* Split Allocate and Assign buffer */
    if(PduR_Bm_AllocateTxBuffer(PduR_GetBmTxBufferIndRomStartIdxOfRmBufferedTpPropertiesRom(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx)), PduR_GetBmTxBufferIndRomEndIdxOfRmBufferedTpPropertiesRom(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx)), fmFifoElementRamIdx, (PduR_BmTxBufferArrayRamLengthOfBmTxBufferRomType) TpSduLength, bufferSizePtr, &allocatedTxBufferIdxPtr, TRUE) == BUFREQ_OK)   /* SBSW_PDUR_VALID_PTR_ENSURED_BY_CALLING_FUNCTION */
    {
      PduR_Fm_AssignTxBuffer2FifoElement(fmFifoElementRamIdx, allocatedTxBufferIdxPtr);
      PduR_SetStateOfFmFifoElementRam(fmFifoElementRamIdx, PDUR_FM_ALLOCATED_WITH_BUFFER_STATEOFFMFIFOELEMENTRAM);      /* SBSW_PDUR_CSL01 */
# if  (PDUR_METADATA_SUPPORT == STD_ON )
      if(PduR_IsMetaDataLengthUsedOfRmBufferedTpPropertiesRom(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx)))        /* COV_PDUR_FEATURE_ALWAYS_TRUE */
      {
        retVal = PduR_RmTp_StartOfReceptionQueueMetaData(rmSrcIdx, info->SduLength, info->SduDataPtr, bufferSizePtr);   /* SBSW_PDUR_VALID_PTR_ENSURED_BY_CALLING_FUNCTION */
      }
      if(retVal != BUFREQ_OK)   /* COV_PDUR_FATAL_ERROR */
      {
        PduR_Det_ReportError(PDUR_RXSM_STARTOFRECEPTION, PDUR_E_FATAL);
      }
      else
# endif
      {
        PduR_SetTpRxSmStateOfRmBufferedTpPropertiesRam(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx), PDUR_RM_RX_ACTIVE_TPRXSMSTATEOFRMBUFFEREDTPPROPERTIESRAM);     /* SBSW_PDUR_IDX_PARAM_INTERNAL_FUNCTION */
        PduR_GetFctPtrOfTpActivateWriteFifoSmTransition(PduR_GetStateOfFmFifoElementRam(fmFifoElementRamIdx)) (fmFifoElementRamIdx);    /* SBSW_PDUR_CSL03 */
        /* Call CheckReady2Transmit() of the FIFO Element state machine */
        if((PduR_GetFctPtrOfTpCheckReady2TransmitRmSmTransition(PduR_GetTpTxSmStateOfFmFifoRam(fmFifoRomIdx)) (rmSrcIdx)) != E_OK)      /* SBSW_PDUR_CSL03 */
        {
          PduR_GetFctPtrOfTpRxIndicationRxSmTransition(PduR_GetTpRxSmStateOfRmBufferedTpPropertiesRam(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx))) (rmSrcIdx, E_NOT_OK);  /* SBSW_PDUR_CSL03 */
          retVal = BUFREQ_E_NOT_OK;
        }
      }
    }
    else
    {
      PduR_Fm_FreeFifoElement(fmFifoRomIdx, fmFifoElementRamIdx);
      retVal = BUFREQ_E_NOT_OK;
    }
  }
  else
  {
    retVal = BUFREQ_E_NOT_OK;
  }
  PDUR_DUMMY_STATEMENT(rmSrcIdx);       /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(info);   /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(TpSduLength);    /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(bufferSizePtr);  /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  return retVal;
}
#endif

#if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM  == STD_ON)
 /**********************************************************************************************************************
 * PduR_RxSm_StartOfReception_UnexpectedCall
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *********************************************************************************************************************/
/* PRQA S 3673 2 */ /* MD_PduR_3673_UnexpectedCall */
FUNC(BufReq_ReturnType, PDUR_CODE) PduR_RxSm_StartOfReception_UnexpectedCall(PduR_RmSrcRomIterType rmSrcIdx, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info, PduLengthType TpSduLength,
                                                                             P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) bufferSizePtr)
{
  PduR_Det_ReportError(PDUR_FCT_SOR, PDUR_E_UNEXPECTED_CALL);
  PDUR_DUMMY_STATEMENT(rmSrcIdx);       /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(info);   /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(TpSduLength);    /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(bufferSizePtr);  /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  return BUFREQ_E_NOT_OK;
}
#endif

#if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RxSm_CopyRxData_RmRxActive
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *********************************************************************************************************************/
/* PRQA S 3673 2 */ /* MD_PduR_3673_AsrProto */
FUNC(BufReq_ReturnType, PDUR_CODE) PduR_RxSm_CopyRxData_RmRxActive(PduR_RmSrcRomIterType rmSrcIdx, PduLengthType pduLength,
                                                                   SduDataPtrType sduDataPtr, P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) bufferSizePtr)
{
  BufReq_ReturnType retVal;
  /** Action: Enqueue data **/
  PduR_FmFifoElementRamIterType fmFifoElementRamWriteIdx = PduR_GetFmFifoElementRamIdxOfRmBufferedTpPropertiesRam(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx));
  PduR_BmTxBufferRomIterType txBufferElementIdx = PduR_GetBmTxBufferRomIdxOfFmFifoElementRam(fmFifoElementRamWriteIdx);

  retVal = PduR_Bm_PutData(txBufferElementIdx, (PduR_BmTxBufferArrayRamIterType) pduLength, sduDataPtr);        /* SBSW_PDUR_VALID_PTR_ENSURED_BY_CALLING_FUNCTION */

  if(retVal == BUFREQ_OK)
  {
    PduR_FmFifoRamIterType fmFifoRomIdx = PduR_GetFmFifoRomIdxOfRmBufferedTpPropertiesRom(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx));
    if(PduR_GetFctPtrOfTpCheckReady2TransmitRmSmTransition(PduR_GetTpTxSmStateOfFmFifoRam(fmFifoRomIdx)) (rmSrcIdx) != E_OK)    /* SBSW_PDUR_CSL03 */
    {
      retVal = BUFREQ_E_NOT_OK;
    }
  }
  *bufferSizePtr = (PduLengthType) PduR_Bm_GetTotalBufferSize(txBufferElementIdx);      /* SBSW_PDUR_VALID_PTR_ENSURED_BY_CALLING_FUNCTION */
  return retVal;
}
#endif

#if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RxSm_CopyRxData_Aborted
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *********************************************************************************************************************/
/* PRQA  S 3673 2 */ /* MD_PduR_3673_Abort */
FUNC(BufReq_ReturnType, PDUR_CODE) PduR_RxSm_CopyRxData_RmRxAborted(PduR_RmSrcRomIterType rmSrcIdx, PduLengthType pduLength,
                                                                    SduDataPtrType sduDataPtr, P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) bufferSizePtr)
{
  PDUR_DUMMY_STATEMENT(rmSrcIdx);       /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(pduLength);      /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(sduDataPtr);     /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(bufferSizePtr);  /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  return BUFREQ_E_NOT_OK;
}
#endif

#if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RxSm_CopyRxData_UnexpectedCall
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *********************************************************************************************************************/
/* PRQA  S 3673 2 */ /* MD_PduR_3673_UnexpectedCall */
FUNC(BufReq_ReturnType, PDUR_CODE) PduR_RxSm_CopyRxData_UnexpectedCall(PduR_RmSrcRomIterType rmSrcIdx, PduLengthType pduLength,
                                                                       SduDataPtrType sduDataPtr, P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) bufferSizePtr)
{
  PduR_Det_ReportError(PDUR_RXSM_COPYRXDATA_UNEXPECTEDCALL, PDUR_E_UNEXPECTED_CALL);
  PDUR_DUMMY_STATEMENT(rmSrcIdx);       /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(pduLength);      /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(sduDataPtr);     /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(bufferSizePtr);  /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  return BUFREQ_E_NOT_OK;
}
#endif

#if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RxSm_TpRxIndication_RmRxActiveOrRmRxAborted
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
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_RxSm_TpRxIndication_RmRxActiveOrRmRxAborted(PduR_RmSrcRomIterType rmSrcIdx, Std_ReturnType result)
{
  /** Action: Start transmission **/
  PduR_FmFifoRomIterType fmFifoRomIdx = PduR_GetFmFifoRomIdxOfRmBufferedTpPropertiesRom(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx));
  PduR_FmFifoElementRamIterType fmFifoElementRamWriteIdx = PduR_GetFmFifoElementRamIdxOfRmBufferedTpPropertiesRam(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx));
  PduR_GetFctPtrOfFinishReceptionRmSmTransition(PduR_GetTpTxSmStateOfFmFifoRam(fmFifoRomIdx)) (rmSrcIdx, result);       /* SBSW_PDUR_CSL03 */
  PduR_GetFctPtrOfFinishWriteFmSmTransition(PduR_GetStateOfFmFifoElementRam(fmFifoElementRamWriteIdx)) (fmFifoElementRamWriteIdx, result);      /* SBSW_PDUR_CSL03 */
  PduR_SetFmFifoElementRamIdxOfRmBufferedTpPropertiesRam(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx), PDUR_NO_FMFIFOELEMENTRAMIDXOFRMBUFFEREDTPPROPERTIESRAM);     /* SBSW_PDUR_CSL03 */
  PduR_SetTpRxSmStateOfRmBufferedTpPropertiesRam(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx), PDUR_RM_RX_IDLE_TPRXSMSTATEOFRMBUFFEREDTPPROPERTIESRAM);     /* SBSW_PDUR_CSL03 */
  PDUR_DUMMY_STATEMENT(result); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
}
#endif

#if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RxSm_TpRxIndication_UnexpectedCall
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_RxSm_TpRxIndication_UnexpectedCall(PduR_RmSrcRomIterType rmSrcIdx, Std_ReturnType result)
{
  PduR_Det_ReportError(PDUR_GWTP_RXSM_TPRXINDICATION_UNEXPECTEDCALL, PDUR_E_UNEXPECTED_CALL);
  PDUR_DUMMY_STATEMENT(rmSrcIdx);       /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(result); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
}
#endif

#if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RxSm_TpCancelReceive_RmRxActive
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_RxSm_TpCancelReceive_RmRxActive(PduR_RmSrcRomIterType rmSrcIdx)
{
  PduR_SetTpRxSmStateOfRmBufferedTpPropertiesRam(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx), PDUR_RM_RX_ABORTED_TPRXSMSTATEOFRMBUFFEREDTPPROPERTIESRAM);  /* SBSW_PDUR_CSL03 */
  PDUR_DUMMY_STATEMENT(rmSrcIdx);       /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
}
#endif

#if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RxSm_TpCancelReceive_RmRxAborted
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *********************************************************************************************************************/

FUNC(void, PDUR_CODE) PduR_RxSm_TpCancelReceive_RmRxAborted(PduR_RmSrcRomIterType rmSrcIdx)     /* COV_PDUR_DUMMY_FUNCTION */
{
  PDUR_DUMMY_STATEMENT(rmSrcIdx);       /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
}
#endif

#if ((PDUR_EXISTS_DIRECT_FIFO_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON) || (PDUR_EXISTS_T_T_FIFO_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON) || (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM  == STD_ON))
LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_Fm_FreeFifoElement(PduR_FmFifoRomIterType fmFifoRomIdx, PduR_FmFifoElementRamWriteIdxOfFmFifoRamType fmFifoElementRamWriteIdx)
{
  /* no buffer available -> roll back release FiFo */
  if(PduR_GetFillLevelOfFmFifoRam(fmFifoRomIdx) > 0)    /* COV_PDUR_FATAL_ERROR */
  {
    PduR_DecFillLevelOfFmFifoRam(fmFifoRomIdx); /* SBSW_PDUR_IDX_PARAM_INTERNAL_FUNCTION */
    PduR_SetFmFifoElementRamWriteIdxOfFmFifoRam(fmFifoRomIdx, fmFifoElementRamWriteIdx);        /* SBSW_PDUR_IDX_PARAM_INTERNAL_FUNCTION */

    if(!PduR_IsDedicatedTxBufferOfFmFifoElementRam(fmFifoElementRamWriteIdx))   /* COV_PDUR_FATAL_ERROR */
    {
      PduR_SetStateOfFmFifoElementRam(fmFifoElementRamWriteIdx, PDUR_FM_IDLE_STATEOFFMFIFOELEMENTRAM);  /* SBSW_PDUR_CSL01 */
    }
    else
    {
      PduR_Det_ReportError(PDUR_FM_FREEFIFOELEMENT, PDUR_E_FATAL);
    }
  }
  else
  {
    PduR_Det_ReportError(PDUR_FM_FREEFIFOELEMENT, PDUR_E_FATAL);
  }
}
#endif

#if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RxSm_TpCancelReceive_FatalError
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_RxSm_TpCancelReceive_FatalError(PduR_RmSrcRomIterType rmSrcIdx)      /* COV_PDUR_FATAL_ERROR */
{
  PduR_Det_ReportError(PDUR_RXSM_TPCANCELRECEIVE_FATALERROR, PDUR_E_FATAL);
  PDUR_DUMMY_STATEMENT(rmSrcIdx);       /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
}
#endif

#if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_Rm_CheckReady2Transmit_RmTxReceptionActive
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
 *********************************************************************************************************************/
FUNC(Std_ReturnType, PDUR_CODE) PduR_Rm_CheckReady2Transmit_RmTxReceptionActive(PduR_RmSrcRomIterType rmSrcIdx)
{
  Std_ReturnType retVal = E_NOT_OK;
  PduR_FmFifoElementRamIterType fmFifoElementRamWriteIdx = PduR_GetFmFifoElementRamIdxOfRmBufferedTpPropertiesRam(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx));
  PduR_FmFifoRamIterType fmFifoRamTpIdx = PduR_GetFmFifoRomIdxOfRmBufferedTpPropertiesRom(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx));
  PduR_FmFifoElementRamIterType fmFifoElementRamTPReadIdx = PduR_GetFmFifoElementRamReadIdxOfFmFifoRam(fmFifoRamTpIdx);

  if(fmFifoElementRamWriteIdx == fmFifoElementRamTPReadIdx) /* COV_PDUR_NO_NTO1_ROUTINGPATHS */
  {
    /* Check if Threshold reached */
         /** Guard/Action: enqueue meta data **/
    /* TpThreshold reached? RX Indication occurs */
    if(PduR_Rm_ThresholdReached(rmSrcIdx) == E_OK)
    {
      PduR_RmDestRomIterType rmDestTpIdx;
      PduR_SetTpTxSmStateOfFmFifoRam(fmFifoRamTpIdx, PDUR_RM_TX_RECEPTION_TRANSMISSION_ACTIVE_TPTXSMSTATEOFFMFIFORAM);  /* SBSW_PDUR_CSL03 */
      PduR_SetPendingConfirmationsOfFmFifoRam(fmFifoRamTpIdx, PduR_GetRmDestRomLengthOfRmSrcRom(rmSrcIdx));     /* SBSW_PDUR_CSL03 */
      /* Assign Tx Buffer */
      PduR_RmTp_AssignAssociatedBuffer2Destination(PduR_GetBmTxBufferRomIdxOfFmFifoElementRam(fmFifoElementRamTPReadIdx), rmSrcIdx);
      PduR_GetFctPtrOfTpActivateReadFifoSmTransition(PduR_GetStateOfFmFifoElementRam(fmFifoElementRamTPReadIdx)) (fmFifoElementRamTPReadIdx);   /* SBSW_PDUR_CSL03 */
      for(rmDestTpIdx = PduR_GetRmDestRomStartIdxOfRmSrcRom(rmSrcIdx); rmDestTpIdx < PduR_GetRmDestRomEndIdxOfRmSrcRom(rmSrcIdx); rmDestTpIdx++)
      {
        PduR_RmGDestRomIterType rmGDestRomIdx = PduR_GetRmGDestRomIdxOfRmDestRom(rmDestTpIdx);
        /* if any routings is sucessfull return E_OK */
        retVal &= (PduR_GetFctPtrOfTpTriggerTransmitTxInstSmTransition(PduR_GetTpTxInstSmStateOfRmGDestTpTxStateRam(PduR_GetRmGDestTpTxStateRamIdxOfRmGDestRom(rmGDestRomIdx))) (rmDestTpIdx)); /* SBSW_PDUR_CSL03 */
      }
      if(retVal != E_OK)
      {
        PduR_SetTpTxSmStateOfFmFifoRam(fmFifoRamTpIdx, PDUR_RM_TX_RECEPTION_ACTIVE_TPTXSMSTATEOFFMFIFORAM);     /* SBSW_PDUR_CSL03 */
      }
    }
    else
    {
      retVal = E_OK;
    }
  }
  else
  {
    retVal = E_OK;
  }
  return retVal;
}
#endif

#if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_Rm_CheckReady2Transmit_NoAction
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
FUNC(Std_ReturnType, PDUR_CODE) PduR_Rm_CheckReady2Transmit_NoAction(PduR_RmSrcRomIterType rmSrcIdx)
{
  PDUR_DUMMY_STATEMENT(rmSrcIdx);       /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  return E_OK;
}
#endif

#if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_Rm_FinishReception_RmTxReceptionActive
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_Rm_FinishReception_RmTxIdle(PduR_RmSrcRomIterType rmSrcIdx, Std_ReturnType result)
{
  Std_ReturnType retVal = E_NOT_OK;
  PduR_FmFifoRamIterType fmFifoRamTpIdx = PduR_GetFmFifoRomIdxOfRmBufferedTpPropertiesRom(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx));
  PduR_FmFifoElementRamIterType fmFifoElementRamTPReadIdx = PduR_GetFmFifoElementRamReadIdxOfFmFifoRam(fmFifoRamTpIdx);
  if(result == E_OK)    /* COV_PDUR_FATAL_ERROR */
  {
    PduR_RmDestRomIterType rmDestTpIdx;
    PduR_SetTpTxSmStateOfFmFifoRam(fmFifoRamTpIdx, PDUR_RM_TX_RECEPTION_FINISHED_TRANSMISSION_ACTIVE_TPTXSMSTATEOFFMFIFORAM);   /* SBSW_PDUR_CSL01 */
    PduR_SetPendingConfirmationsOfFmFifoRam(fmFifoRamTpIdx, PduR_GetRmDestRomLengthOfRmSrcRom(rmSrcIdx));       /* SBSW_PDUR_CSL03 */
    /* Assign Tx Buffer */
    PduR_RmTp_AssignAssociatedBuffer2Destination(PduR_GetBmTxBufferRomIdxOfFmFifoElementRam(fmFifoElementRamTPReadIdx), rmSrcIdx);
    PduR_GetFctPtrOfTpActivateReadFifoSmTransition(PduR_GetStateOfFmFifoElementRam(fmFifoElementRamTPReadIdx)) (fmFifoElementRamTPReadIdx);     /* SBSW_PDUR_CSL03 */
    for(rmDestTpIdx = PduR_GetRmDestRomStartIdxOfRmSrcRom(rmSrcIdx); rmDestTpIdx < PduR_GetRmDestRomEndIdxOfRmSrcRom(rmSrcIdx); rmDestTpIdx++)
    {
      PduR_RmGDestRomIterType rmGDestRomIdx = PduR_GetRmGDestRomIdxOfRmDestRom(rmDestTpIdx);
      /* if any routings is sucessfull return E_OK */
      retVal &= (PduR_GetFctPtrOfTpTriggerTransmitTxInstSmTransition(PduR_GetTpTxInstSmStateOfRmGDestTpTxStateRam(PduR_GetRmGDestTpTxStateRamIdxOfRmGDestRom(rmGDestRomIdx))) (rmDestTpIdx));   /* SBSW_PDUR_CSL03 */
    }
    if(retVal != E_OK)
    {
      PduR_SetTpTxSmStateOfFmFifoRam(fmFifoRamTpIdx, PDUR_RM_TX_IDLE_TPTXSMSTATEOFFMFIFORAM);   /* SBSW_PDUR_CSL01 */
    }
  }
  else
  {
    PduR_Det_ReportError(PDUR_FINISHRECEPTION, PDUR_E_FATAL);
  }
}
#endif
#if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM  == STD_ON)
/**********************************************************************************************************************
 * PduR_Rm_FinishReception_RmTxReceptionActive
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
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_Rm_FinishReception_RmTxReceptionActive(PduR_RmSrcRomIterType rmSrcIdx, Std_ReturnType result)
{
  PduR_FmFifoElementRamIterType fmFifoElementRamWriteIdx = PduR_GetFmFifoElementRamIdxOfRmBufferedTpPropertiesRam(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx));
  PduR_FmFifoRamIterType fmFifoRamIdx = PduR_GetFmFifoRomIdxOfRmBufferedTpPropertiesRom(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx));
  PduR_FmFifoElementRamIterType fmFifoElementRamTPReadIdx = PduR_GetFmFifoElementRamReadIdxOfFmFifoRam(fmFifoRamIdx);
  if(fmFifoElementRamWriteIdx == fmFifoElementRamTPReadIdx) /* COV_PDUR_NO_NTO1_ROUTINGPATHS */
  {
    if(result == E_OK)
    {
      Std_ReturnType retVal = E_NOT_OK;
      PduR_RmDestRomIterType rmDestIdx;
      PduR_SetTpTxSmStateOfFmFifoRam(fmFifoRamIdx, PDUR_RM_TX_RECEPTION_FINISHED_TRANSMISSION_ACTIVE_TPTXSMSTATEOFFMFIFORAM);   /* SBSW_PDUR_CSL01 */
      PduR_SetPendingConfirmationsOfFmFifoRam(fmFifoRamIdx, PduR_GetRmDestRomLengthOfRmSrcRom(rmSrcIdx));       /* SBSW_PDUR_CSL03 */
      /* Assign Tx Buffer */
      PduR_RmTp_AssignAssociatedBuffer2Destination(PduR_GetBmTxBufferRomIdxOfFmFifoElementRam(fmFifoElementRamTPReadIdx), rmSrcIdx);
      PduR_GetFctPtrOfTpActivateReadFifoSmTransition(PduR_GetStateOfFmFifoElementRam(fmFifoElementRamTPReadIdx)) (fmFifoElementRamTPReadIdx);   /* SBSW_PDUR_CSL03 */
      for(rmDestIdx = PduR_GetRmDestRomStartIdxOfRmSrcRom(rmSrcIdx); rmDestIdx < PduR_GetRmDestRomEndIdxOfRmSrcRom(rmSrcIdx); rmDestIdx++)
      {
        PduR_RmGDestRomIterType rmGDestRomIdx = PduR_GetRmGDestRomIdxOfRmDestRom(rmDestIdx);
        /* if any routings is sucessfull return E_OK */
        retVal &= (PduR_GetFctPtrOfTpTriggerTransmitTxInstSmTransition(PduR_GetTpTxInstSmStateOfRmGDestTpTxStateRam(PduR_GetRmGDestTpTxStateRamIdxOfRmGDestRom(rmGDestRomIdx))) (rmDestIdx));   /* SBSW_PDUR_CSL03 */
      }
      if(retVal != E_OK)
      {
        PduR_SetRmDestRomIdxOfFmFifoElementRam((fmFifoElementRamWriteIdx), PDUR_NO_RMDESTROMIDXOFFMFIFOELEMENTRAM);     /* SBSW_PDUR_CSL03 */
        PduR_Fm_ActivateNext(fmFifoRamIdx);
      }
    }
    else
    {
      PduR_GetFctPtrOfFinishWriteFmSmTransition(PduR_GetStateOfFmFifoElementRam(fmFifoElementRamWriteIdx)) (fmFifoElementRamWriteIdx, result);  /* SBSW_PDUR_CSL03 */
      PduR_SetFmFifoElementRamIdxOfRmBufferedTpPropertiesRam(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx), PDUR_NO_FMFIFOELEMENTRAMIDXOFRMBUFFEREDTPPROPERTIESRAM); /* SBSW_PDUR_CSL03 */
      PduR_SetTpTxSmStateOfFmFifoRam(fmFifoRamIdx, PDUR_RM_TX_IDLE_TPTXSMSTATEOFFMFIFORAM);     /* SBSW_PDUR_CSL01 */
      PduR_SetRmDestRomIdxOfFmFifoElementRam((fmFifoElementRamWriteIdx), PDUR_NO_RMDESTROMIDXOFFMFIFOELEMENTRAM);       /* SBSW_PDUR_CSL03 */
      PduR_Fm_ActivateNext(fmFifoRamIdx);
    }
  }
}
#endif

#if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_Rm_FinishReception_RmTxReceptionTransmissionActive
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_Rm_FinishReception_RmTxReceptionTransmissionActive(PduR_RmSrcRomIterType rmSrcIdx, Std_ReturnType result)
{
  PduR_FmFifoElementRamIterType fmFifoElementRamWriteIdx = PduR_GetFmFifoElementRamIdxOfRmBufferedTpPropertiesRam(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx));
  PduR_FmFifoRamIterType fmFifoRamIdx = PduR_GetFmFifoRomIdxOfRmBufferedTpPropertiesRom(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx));
  PduR_SetTpTxSmStateOfFmFifoRam(fmFifoRamIdx, PDUR_RM_TX_RECEPTION_FINISHED_TRANSMISSION_ACTIVE_TPTXSMSTATEOFFMFIFORAM);       /* SBSW_PDUR_CSL01 */
  if(result != E_OK)
  {
    PduR_TxSm_CancelTransmitPreparation(fmFifoElementRamWriteIdx);
  }
}
#endif

#if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_Rm_FinishReception_RmTxTransmissionFinished
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_Rm_FinishReception_RmTxTransmissionFinished(PduR_RmSrcRomIterType rmSrcIdx, Std_ReturnType result)
{
  PduR_FmFifoElementRamIterType fmFifoElementRamWriteIdx = PduR_GetFmFifoElementRamIdxOfRmBufferedTpPropertiesRam(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx));
  PduR_FmFifoRamIterType fmFifoRamIdx = PduR_GetFmFifoRomIdxOfRmBufferedTpPropertiesRom(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx));
  PduR_SetTpTxSmStateOfFmFifoRam(fmFifoRamIdx, PDUR_RM_TX_IDLE_TPTXSMSTATEOFFMFIFORAM); /* SBSW_PDUR_CSL01 */
  PduR_SetRmDestRomIdxOfFmFifoElementRam((fmFifoElementRamWriteIdx), PDUR_NO_RMDESTROMIDXOFFMFIFOELEMENTRAM);   /* SBSW_PDUR_CSL03 */
  PduR_Fm_ActivateNext(fmFifoRamIdx);
  PDUR_DUMMY_STATEMENT(result); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
}
#endif

#if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM   == STD_ON)
/**********************************************************************************************************************
 * PduR_Rm_FinishReception_NoAction
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_Rm_FinishReception_NoAction(PduR_RmSrcRomIterType rmSrcIdx, Std_ReturnType result)
{
  PDUR_DUMMY_STATEMENT(rmSrcIdx);       /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(result); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
}
#endif

#if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_Rm_FinishTransmission_RmTxReceptionFinishedTransmissionActive
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_Rm_FinishTransmission_RmTxReceptionFinishedTransmissionActive(PduR_RmDestRomIterType rmGDestRomIdx, Std_ReturnType result)
{
  PduR_FmFifoRomIterType fmFifoRomIdx = PduR_GetFmFifoRomIdxOfFmFifoInstanceRom(PduR_GetFmFifoInstanceRomIdxOfRmGDestRom(rmGDestRomIdx));
  if(PduR_GetPendingConfirmationsOfFmFifoRam(fmFifoRomIdx) == 0)
  {
    PduR_FmFifoElementRamIterType fmFifoElementRamReadIdx = PduR_GetFmFifoElementRamReadIdxOfFmFifoRam(fmFifoRomIdx);
    PduR_RmSrcRomIterType rmSrcIdx = PduR_GetRmSrcRomIdxOfRmDestRom(PduR_GetRmDestRomIdxOfFmFifoElementRam(fmFifoElementRamReadIdx));
    PduR_FmFifoRamIterType fmFifoRamIdx = PduR_GetFmFifoRomIdxOfRmBufferedTpPropertiesRom(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx));
    PduR_GetFctPtrOfFinishReadFmSmTransition(PduR_GetStateOfFmFifoElementRam(fmFifoElementRamReadIdx)) (fmFifoElementRamReadIdx, result);       /* SBSW_PDUR_CSL03 */
    PduR_SetTpTxSmStateOfFmFifoRam(fmFifoRomIdx, PDUR_RM_TX_IDLE_TPTXSMSTATEOFFMFIFORAM);       /* SBSW_PDUR_CSL03 */
    PduR_Fm_ActivateNext(fmFifoRamIdx);
  }
}
#endif

#if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_Rm_FinishTransmission_RmTxReceptionTransmissionActive
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_Rm_FinishTransmission_RmTxReceptionTransmissionActive(PduR_RmGDestRomIterType rmGDestRomIdx, Std_ReturnType result)
{
  PduR_FmFifoRomIterType fmFifoRomIdx = PduR_GetFmFifoRomIdxOfFmFifoInstanceRom(PduR_GetFmFifoInstanceRomIdxOfRmGDestRom(rmGDestRomIdx));
  if(PduR_GetPendingConfirmationsOfFmFifoRam(fmFifoRomIdx) == 0)
  {
    PduR_FmFifoElementRamIterType fmFifoElementRamTPReadIdx = PduR_GetFmFifoElementRamReadIdxOfFmFifoRam(fmFifoRomIdx);
    PduR_SetTpTxSmStateOfFmFifoRam(fmFifoRomIdx, PDUR_RM_TX_TRANSMISSION_FINISHED_TPTXSMSTATEOFFMFIFORAM);      /* SBSW_PDUR_CSL01 */
    PduR_GetFctPtrOfFinishReadFmSmTransition(PduR_GetStateOfFmFifoElementRam(fmFifoElementRamTPReadIdx)) (fmFifoElementRamTPReadIdx, result);   /* SBSW_PDUR_CSL03 */
    if(result != E_OK)
    {
      PduR_RmSrcRomIterType rmSrcIdx = PduR_GetRmSrcRomIdxOfRmDestRom(PduR_GetRmDestRomIdxOfFmFifoElementRam(fmFifoElementRamTPReadIdx));
      PduR_TpRxSmStateOfRmBufferedTpPropertiesRamType tpRxSmState = PduR_GetTpRxSmStateOfRmBufferedTpPropertiesRam(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx));
      PduR_GetFctPtrOfTpCancelReceiveFifoSmTransition(tpRxSmState) (rmSrcIdx);  /* SBSW_PDUR_CSL03 */
    }
  }
}
#endif

#if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_Rm_FinishTransmission_FatalError
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_Rm_FinishTransmission_FatalError(PduR_RmDestRomIterType rmGDestRomIdx, Std_ReturnType result)        /* COV_PDUR_FATAL_ERROR */
{
  PDUR_DUMMY_STATEMENT(rmGDestRomIdx);  /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(result); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
}
#endif

#if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_Rm_CheckReady2Transmit_RmTxIdle
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
 *********************************************************************************************************************/
FUNC(Std_ReturnType, PDUR_CODE) PduR_Rm_CheckReady2Transmit_RmTxIdle(PduR_RmSrcRomIterType rmSrcIdx)
{
  Std_ReturnType retVal = E_NOT_OK;
  /* Check if Threshold reached */
       /** Guard/Action: enqueue meta data **/
  /* TpThreshold reached? RX Indication occurs */
  PduR_FmFifoRamIterType fmFifoRamIdx = PduR_GetFmFifoRomIdxOfRmBufferedTpPropertiesRom(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx));
  PduR_FmFifoElementRamIterType fmFifoElementRamTPReadIdx = PduR_GetFmFifoElementRamReadIdxOfFmFifoRam(fmFifoRamIdx);
  if(PduR_Rm_ThresholdReached(rmSrcIdx) == E_OK)
  {
    PduR_RmDestRomIterType rmDestRomIdx;
    PduR_SetTpTxSmStateOfFmFifoRam(fmFifoRamIdx, PDUR_RM_TX_RECEPTION_TRANSMISSION_ACTIVE_TPTXSMSTATEOFFMFIFORAM);      /* SBSW_PDUR_CSL03 */
    PduR_SetPendingConfirmationsOfFmFifoRam(fmFifoRamIdx, PduR_GetRmDestRomLengthOfRmSrcRom(rmSrcIdx)); /* SBSW_PDUR_CSL03 */
    /* Assign Tx Buffer */
    PduR_RmTp_AssignAssociatedBuffer2Destination(PduR_GetBmTxBufferRomIdxOfFmFifoElementRam(fmFifoElementRamTPReadIdx), rmSrcIdx);
    PduR_GetFctPtrOfTpActivateReadFifoSmTransition(PduR_GetStateOfFmFifoElementRam(fmFifoElementRamTPReadIdx)) (fmFifoElementRamTPReadIdx);     /* SBSW_PDUR_CSL03 */
    for(rmDestRomIdx = PduR_GetRmDestRomStartIdxOfRmSrcRom(rmSrcIdx); rmDestRomIdx < PduR_GetRmDestRomEndIdxOfRmSrcRom(rmSrcIdx); rmDestRomIdx++)
    {
      PduR_RmGDestRomIterType rmGDestRomIdx = PduR_GetRmGDestRomIdxOfRmDestRom(rmDestRomIdx);
      /* if any routings is sucessfull return E_OK */
      retVal &= (PduR_GetFctPtrOfTpTriggerTransmitTxInstSmTransition(PduR_GetTpTxInstSmStateOfRmGDestTpTxStateRam(PduR_GetRmGDestTpTxStateRamIdxOfRmGDestRom(rmGDestRomIdx))) (rmDestRomIdx));  /* SBSW_PDUR_CSL03 */
    }
    if(retVal != E_OK)
    {
      PduR_SetTpTxSmStateOfFmFifoRam(fmFifoRamIdx, PDUR_RM_TX_RECEPTION_ACTIVE_TPTXSMSTATEOFFMFIFORAM); /* SBSW_PDUR_CSL03 */
    }
  }
  else
  {
    retVal = E_OK;
    PduR_SetTpTxSmStateOfFmFifoRam(fmFifoRamIdx, PDUR_RM_TX_RECEPTION_ACTIVE_TPTXSMSTATEOFFMFIFORAM);   /* SBSW_PDUR_CSL03 */
  }
  return retVal;
}
#endif

#if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_Fm_ActivateNext
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_Fm_ActivateNext(PduR_FmFifoRamIterType fmFifoRamIdx)
{
  PduR_FmFifoElementRamIterType peekedfmFifoElementRamTPReadIdx;
  if(PduR_Fm_Peek(fmFifoRamIdx, &peekedfmFifoElementRamTPReadIdx) == E_OK)      /* SBSW_PDUR_STACK_VARIABLE */
  {
    PduR_GetFctPtrOfTpActivateNextFifoSmTransition(PduR_GetStateOfFmFifoElementRam(peekedfmFifoElementRamTPReadIdx)) (peekedfmFifoElementRamTPReadIdx, E_OK);   /* SBSW_PDUR_CSL03 */
  }
}
#endif

#if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_Fm_ActivateNext_FmWriteFinishedReadPending
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_Fm_ActivateNext_FmWriteFinishedReadPending(PduR_FmFifoElementRamIterType fmFifoElementRamWriteIdx, Std_ReturnType result)
{
  PduR_RmSrcRomIterType rmSrcIdx = PduR_GetRmSrcRomIdxOfRmDestRom(PduR_GetRmDestRomIdxOfFmFifoElementRam(fmFifoElementRamWriteIdx));
  PduR_FmFifoRamIterType fmFifoRamIdx = PduR_GetFmFifoRomIdxOfRmBufferedTpPropertiesRom(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx));
  PduR_GetFctPtrOfFinishReceptionRmSmTransition(PduR_GetTpTxSmStateOfFmFifoRam(fmFifoRamIdx)) (rmSrcIdx, result);       /* SBSW_PDUR_CSL03 */
}
#endif

#if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_Fm_ActivateNext_FmWriteActive
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_Fm_ActivateNext_FmWriteActive(PduR_FmFifoElementRamIterType fmFifoElementRamWriteIdx, Std_ReturnType result)
{
  PduR_RmSrcRomIterType rmSrcIdx = PduR_GetRmSrcRomIdxOfRmDestRom(PduR_GetRmDestRomIdxOfFmFifoElementRam(fmFifoElementRamWriteIdx));
  PduR_FmFifoRamIterType fmFifoRamIdx = PduR_GetFmFifoRomIdxOfRmBufferedTpPropertiesRom(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx));
  PduR_GetFctPtrOfTpCheckReady2TransmitRmSmTransition(PduR_GetTpTxSmStateOfFmFifoRam(fmFifoRamIdx)) (rmSrcIdx); /* SBSW_PDUR_CSL03 */
  PDUR_DUMMY_STATEMENT(result); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
}
#endif

#if (PDUR_FMFIFORAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Fm_ActivateRead_FmWriteFinishedReadPending
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_Fm_ActivateRead_FmWriteFinishedReadPending(PduR_FmFifoElementRamIterType fmFifoElementRamWriteIdx)
{
  PduR_SetStateOfFmFifoElementRam(fmFifoElementRamWriteIdx, PDUR_FM_WRITE_FINISHED_READ_ACTIVE_STATEOFFMFIFOELEMENTRAM);        /* SBSW_PDUR_CSL03 */
}
#endif

#if (PDUR_FMFIFORAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Fm_ActivateRead_FmWriteActive
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_Fm_ActivateRead_FmWriteActive(PduR_FmFifoElementRamIterType fmFifoElementRamWriteIdx)
{
  PduR_SetStateOfFmFifoElementRam(fmFifoElementRamWriteIdx, PDUR_FM_WRITE_READ_ACTIVE_STATEOFFMFIFOELEMENTRAM); /* SBSW_PDUR_CSL03 */
}
#endif
#if (PDUR_FMFIFORAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Fm_ActivateRead_NoAction
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_Fm_ActivateRead_NoAction(PduR_FmFifoElementRamIterType fmFifoElementRamWriteIdx)     /* COV_PDUR_TP_ONLY */
{
  PDUR_DUMMY_STATEMENT(fmFifoElementRamWriteIdx);       /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
}
#endif

#if (PDUR_FMFIFORAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Fm_ActivateRead_FatalError
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_Fm_ActivateRead_FatalError(PduR_FmFifoElementRamIterType fmFifoElementRamWriteIdx)   /* COV_PDUR_FATAL_ERROR */
{
  PduR_Det_ReportError(PDUR_FMACTIVATEREAD, PDUR_E_FATAL);
  PDUR_DUMMY_STATEMENT(fmFifoElementRamWriteIdx);       /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
}
#endif

#if (PDUR_FMFIFORAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Fm_FinishWrite_NoAction
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_Fm_FinishWrite_NoAction(PduR_FmFifoElementRamIterType fmFifoElementRamWriteIdx, Std_ReturnType result)       /* COV_PDUR_TP_ONLY */
{
  PDUR_DUMMY_STATEMENT(fmFifoElementRamWriteIdx);       /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(result); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
}
#endif

#if (PDUR_FMFIFORAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Fm_FinishWrite_FmReadFinished
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
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_Fm_FinishWrite_FmReadFinished(PduR_FmFifoElementRamIterType fmFifoElementRamWriteIdx, Std_ReturnType result)
{
  /* Reset buffer */
  PduR_Bm_ResetTxBuffer(PduR_GetBmTxBufferRomIdxOfFmFifoElementRam(fmFifoElementRamWriteIdx));
  /* Reset Fifo element */
  PduR_Fm_ReleaseFifoElement(fmFifoElementRamWriteIdx);
  if(PduR_IsDedicatedTxBufferOfFmFifoElementRam(fmFifoElementRamWriteIdx)) /* COV_PDUR_ONLY_SHARED_BUFFER */
  {
    PduR_SetStateOfFmFifoElementRam(fmFifoElementRamWriteIdx, PDUR_FM_ALLOCATED_WITH_BUFFER_STATEOFFMFIFOELEMENTRAM);   /* SBSW_PDUR_CSL03 */
  }
  else
  {
    PduR_SetStateOfFmFifoElementRam(fmFifoElementRamWriteIdx, PDUR_FM_IDLE_STATEOFFMFIFOELEMENTRAM);    /* SBSW_PDUR_CSL03 */
    /* release buffer connection */
    PduR_Fm_DissolveFifoElementTxBufferRelation(fmFifoElementRamWriteIdx);
  }
  PDUR_DUMMY_STATEMENT(result); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
}
#endif
#if (PDUR_FMFIFORAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Fm_FinishWrite_FmWriteReadActive
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_Fm_FinishWrite_FmWriteReadActive(PduR_FmFifoElementRamIterType fmFifoElementRamWriteIdx, Std_ReturnType result)
{
  PduR_SetStateOfFmFifoElementRam(fmFifoElementRamWriteIdx, PDUR_FM_WRITE_FINISHED_READ_ACTIVE_STATEOFFMFIFOELEMENTRAM);        /* SBSW_PDUR_CSL03 */
  PDUR_DUMMY_STATEMENT(result); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
}
#endif
#if (PDUR_FMFIFORAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Fm_FinishWrite_FmWriteActive
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_Fm_FinishWrite_FmWriteActive(PduR_FmFifoElementRamIterType fmFifoElementRamWriteIdx, Std_ReturnType result)
{
  if(result == E_OK)
  {
    PduR_SetStateOfFmFifoElementRam(fmFifoElementRamWriteIdx, PDUR_FM_WRITE_FINISHED_READ_PENDING_STATEOFFMFIFOELEMENTRAM);     /* SBSW_PDUR_CSL03 */
  }
  else
  {
    /* Reset Fifo element */
    PduR_Fm_ReleaseFifoElement(fmFifoElementRamWriteIdx);
    /* Reset buffer */
    PduR_Bm_ResetTxBuffer(PduR_GetBmTxBufferRomIdxOfFmFifoElementRam(fmFifoElementRamWriteIdx));
    if(PduR_IsDedicatedTxBufferOfFmFifoElementRam(fmFifoElementRamWriteIdx)) /* COV_PDUR_ONLY_SHARED_BUFFER */
    {
      PduR_SetStateOfFmFifoElementRam(fmFifoElementRamWriteIdx, PDUR_FM_ALLOCATED_WITH_BUFFER_STATEOFFMFIFOELEMENTRAM); /* SBSW_PDUR_CSL03 */
    }
    else
    {
      /* Shared buffer */
      PduR_SetStateOfFmFifoElementRam(fmFifoElementRamWriteIdx, PDUR_FM_IDLE_STATEOFFMFIFOELEMENTRAM);  /* SBSW_PDUR_CSL03 */
      PduR_Fm_DissolveFifoElementTxBufferRelation(fmFifoElementRamWriteIdx);
    }
  }
}
#endif

#if (PDUR_FMFIFORAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Fm_FinishRead_FmWriteFinishedReadActive
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_Fm_FinishRead_FmWriteFinishedReadActive(PduR_FmFifoElementRamIterType fmFifoElementRamReadIdx, Std_ReturnType result)
{
  /* Reset Fifo element */
  PduR_Fm_ReleaseFifoElement(fmFifoElementRamReadIdx);
  /* Reset buffer */
  PduR_Bm_ResetTxBuffer(PduR_GetBmTxBufferRomIdxOfFmFifoElementRam(fmFifoElementRamReadIdx));
  if(PduR_IsDedicatedTxBufferOfFmFifoElementRam(fmFifoElementRamReadIdx)) /* COV_PDUR_ONLY_SHARED_BUFFER */
  {
    PduR_SetStateOfFmFifoElementRam(fmFifoElementRamReadIdx, PDUR_FM_ALLOCATED_WITH_BUFFER_STATEOFFMFIFOELEMENTRAM);    /* SBSW_PDUR_CSL03 */
  }
  else
  {
    PduR_SetStateOfFmFifoElementRam(fmFifoElementRamReadIdx, PDUR_FM_IDLE_STATEOFFMFIFOELEMENTRAM);     /* SBSW_PDUR_CSL03 */
    PduR_Fm_DissolveFifoElementTxBufferRelation(fmFifoElementRamReadIdx);
  }
  PDUR_DUMMY_STATEMENT(result); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
}
#endif

#if (PDUR_FMFIFORAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Fm_FinishRead_FmWriteReadActive
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_Fm_FinishRead_FmWriteReadActive(PduR_FmFifoElementRamIterType fmFifoElementRamReadIdx, Std_ReturnType result)
{
  PduR_SetStateOfFmFifoElementRam(fmFifoElementRamReadIdx, PDUR_FM_READ_FINISHED_STATEOFFMFIFOELEMENTRAM);      /* SBSW_PDUR_CSL03 */
  PDUR_DUMMY_STATEMENT(result); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
}
#endif

#if (PDUR_FMFIFORAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Fm_FinishRead_FatalError
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_Fm_FinishRead_FatalError(PduR_FmFifoElementRamIterType fmFifoElementRamReadIdx, Std_ReturnType result)       /* COV_PDUR_FATAL_ERROR */
{
  PduR_Det_ReportError(PDUR_FMFINISHREAD, PDUR_E_FATAL);
  PDUR_DUMMY_STATEMENT(fmFifoElementRamReadIdx);        /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(result); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
}
#endif

#if (PDUR_FMFIFORAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Fm_FinishRead_NoAction
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_Fm_FinishRead_NoAction(PduR_FmFifoElementRamIterType fmFifoElementRamReadIdx, Std_ReturnType result) /* COV_PDUR_TP_ONLY */
{
  PDUR_DUMMY_STATEMENT(fmFifoElementRamReadIdx);        /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(result); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
}
#endif

#if (PDUR_FMFIFORAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Fm_ActivateWrite_FmAllocatedWithBuffer
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_Fm_ActivateWrite_FmAllocatedWithBuffer(PduR_FmFifoElementRamIterType fmFifoElementRamWriteIdx)
{
  PduR_SetStateOfFmFifoElementRam(fmFifoElementRamWriteIdx, PDUR_FM_WRITE_ACTIVE_STATEOFFMFIFOELEMENTRAM);      /* SBSW_PDUR_CSL03 */
}
#endif

#if (PDUR_FMFIFORAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Fm_ActivateWrite_FatalError
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_Fm_ActivateWrite_FatalError(PduR_FmFifoElementRamIterType fmFifoElementRamWriteIdx)  /* COV_PDUR_FATAL_ERROR */
{
  PduR_Det_ReportError(PDUR_FM_ACTIVATEWRITE, PDUR_E_FATAL);
  PDUR_DUMMY_STATEMENT(fmFifoElementRamWriteIdx);       /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
}
#endif

#if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
 /**********************************************************************************************************************
 * PduR_TxSm_CancelTransmitPreparation
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_TxSm_CancelTransmitPreparation(PduR_FmFifoElementRamIterType fmFifoElementRamIdx)
{
  PduR_RmSrcRomIterType rmSrcIdx = PduR_GetRmSrcRomIdxOfRmDestRom(PduR_GetRmDestRomIdxOfFmFifoElementRam(fmFifoElementRamIdx));
  PduR_RmDestRomIterType rmDestRomIdx;
  for(rmDestRomIdx = PduR_GetRmDestRomStartIdxOfRmSrcRom(rmSrcIdx); rmDestRomIdx < PduR_GetRmDestRomEndIdxOfRmSrcRom(rmSrcIdx); rmDestRomIdx++)
  {
    PduR_RmGDestRomIterType rmGDestRomIdx = PduR_GetRmGDestRomIdxOfRmDestRom(rmDestRomIdx);
    if(PduR_GetTpTxInstSmStateOfRmGDestTpTxStateRam(PduR_GetRmGDestTpTxStateRamIdxOfRmGDestRom(rmGDestRomIdx)) == PDUR_RM_TXINST_ACTIVE_TPTXINSTSMSTATEOFRMGDESTTPTXSTATERAM)
    {
      PduR_GetFctPtrOfTpCancelTransmitTxInstSmTransition(PduR_GetTpTxInstSmStateOfRmGDestTpTxStateRam(PduR_GetRmGDestTpTxStateRamIdxOfRmGDestRom(rmGDestRomIdx))) (rmGDestRomIdx);      /* SBSW_PDUR_CSL03 */
    }
  }
}
#endif

#if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
 /**********************************************************************************************************************
 * PduR_Fm_ActivateNext_FatalError
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_Fm_ActivateNext_FatalError(PduR_FmFifoElementRamIterType fmFifoElementRamWriteIdx, Std_ReturnType result)    /* COV_PDUR_FATAL_ERROR */
{
  PduR_Det_ReportError(PDUR_FM_ACTIVATENEXT, PDUR_E_FATAL);
  PDUR_DUMMY_STATEMENT(fmFifoElementRamWriteIdx);       /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(result); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
}
#endif

#if ((PDUR_RMDESTROMUSEDOFRMDESTRPGROM == STD_ON) && (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON))
/**********************************************************************************************************************
 * PduR_Fm_DisableRouting_NoAction
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_Fm_DisableRouting_NoAction(PduR_RmGDestRomIterType rmGDestRomIdx)
{
  PDUR_DUMMY_STATEMENT(rmGDestRomIdx);  /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
}
#endif

#if ((PDUR_RMDESTROMUSEDOFRMDESTRPGROM == STD_ON) && (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON))
/**********************************************************************************************************************
 * PduR_Fm_DisableRouting_FmWriteFinishedReadActive
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_Fm_DisableRouting_FmWriteFinishedReadActive(PduR_RmGDestRomIterType rmGDestRomIdx)
{
  PduR_FmFifoRomIterType fmFifoRomIdx = PduR_GetFmFifoRomIdxOfFmFifoInstanceRom(PduR_GetFmFifoInstanceRomIdxOfRmGDestRom(rmGDestRomIdx));
  PduR_FmFifoElementRamIterType fmFifoElementRamReadIdx = PduR_GetFmFifoElementRamReadIdxOfFmFifoRam(fmFifoRomIdx);
  PduR_TxSm_CancelTransmitPreparation(fmFifoElementRamReadIdx);
}
#endif

#if ((PDUR_RMDESTROMUSEDOFRMDESTRPGROM == STD_ON) && (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON))
/**********************************************************************************************************************
 * PduR_Fm_DisableRouting_FmWriteActive
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_Fm_DisableRouting_FmWriteActive(PduR_RmGDestRomIterType rmGDestRomIdx)
{
  PduR_FmFifoRomIterType fmFifoRomIdx = PduR_GetFmFifoRomIdxOfFmFifoInstanceRom(PduR_GetFmFifoInstanceRomIdxOfRmGDestRom(rmGDestRomIdx));
  PduR_FmFifoElementRamIterType fmFifoElementRamReadIdx = PduR_GetFmFifoElementRamReadIdxOfFmFifoRam(fmFifoRomIdx);
  PduR_RmSrcRomIterType rmSrcIdx = PduR_GetRmSrcRomIdxOfRmDestRom(PduR_GetRmDestRomIdxOfFmFifoElementRam(fmFifoElementRamReadIdx));
  PduR_TpRxSmStateOfRmBufferedTpPropertiesRamType tpRxSmState = PduR_GetTpRxSmStateOfRmBufferedTpPropertiesRam(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx));
  PduR_GetFctPtrOfTpCancelReceiveFifoSmTransition(tpRxSmState) (rmSrcIdx);      /* SBSW_PDUR_CSL03 */
}
#endif

#if ((PDUR_RMDESTROMUSEDOFRMDESTRPGROM == STD_ON) && (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON))
/**********************************************************************************************************************
 * PduR_Fm_DisableRouting_FmWriteReadActive
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_Fm_DisableRouting_FmWriteReadActive(PduR_RmGDestRomIterType rmGDestRomIdx)
{
  PduR_FmFifoRomIterType fmFifoRomIdx = PduR_GetFmFifoRomIdxOfFmFifoInstanceRom(PduR_GetFmFifoInstanceRomIdxOfRmGDestRom(rmGDestRomIdx));
  PduR_FmFifoElementRamIterType fmFifoElementRamReadIdx = PduR_GetFmFifoElementRamReadIdxOfFmFifoRam(fmFifoRomIdx);
  PduR_RmSrcRomIterType rmSrcIdx = PduR_GetRmSrcRomIdxOfRmDestRom(PduR_GetRmDestRomIdxOfFmFifoElementRam(fmFifoElementRamReadIdx));
  PduR_TpRxSmStateOfRmBufferedTpPropertiesRamType tpRxSmState = PduR_GetTpRxSmStateOfRmBufferedTpPropertiesRam(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx));
  PduR_GetFctPtrOfTpCancelReceiveFifoSmTransition(tpRxSmState) (rmSrcIdx);      /* SBSW_PDUR_CSL03 */
  PduR_TxSm_CancelTransmitPreparation(fmFifoElementRamReadIdx);
}
#endif

#if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_TxInstSm_CopyTxData_RmTxinstActive
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *********************************************************************************************************************/
/* PRQA S 3673 4 */ /* MD_PduR_3673_AsrProto */
FUNC(BufReq_ReturnType, PDUR_CODE) PduR_TxInstSm_CopyTxData_RmTxinstActive(PduR_RmGDestRomIterType rmGDestRomIdx,
                                                                           PduLengthType pduLength,
                                                                           SduDataPtrType sduDataPtr,
                                                                           P2CONST(RetryInfoType, AUTOMATIC, PDUR_APPL_DATA) retry, P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) availableDataPtr)
{
  BufReq_ReturnType retVal;
  /* Get instance specific Tx Buffer element */
  PduR_BmTxBufferInstanceRomIterType bmTxBufferInstanceRomIdx = PduR_GetBmTxBufferInstanceRomIdxOfFmFifoInstanceRam(PduR_GetFmFifoInstanceRomIdxOfRmGDestRom(rmGDestRomIdx));

  /** Action: Dequeue data **/
  retVal = PduR_Bm_GetData(bmTxBufferInstanceRomIdx, (PduR_BmTxBufferArrayRamIterType) pduLength, sduDataPtr);  /* SBSW_PDUR_VALID_PTR_ENSURED_BY_CALLING_FUNCTION */
  *availableDataPtr = (PduLengthType) PduR_Bm_GetTotalDataSizeInstance(bmTxBufferInstanceRomIdx);       /* SBSW_PDUR_VALID_PTR_ENSURED_BY_CALLING_FUNCTION */

  PDUR_DUMMY_STATEMENT(retry);  /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  return retVal;
}
#endif

#if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_TxInstSm_CopyTxData_UnexpectedCall
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *********************************************************************************************************************/
/* PRQA  S 3673 3 */ /* MD_PduR_3673_UnexpectedCall */
FUNC(BufReq_ReturnType, PDUR_CODE) PduR_TxInstSm_CopyTxData_UnexpectedCall(PduR_RmGDestRomIterType rmGDestRomIdx, PduLengthType pduLength,
                                                                           SduDataPtrType sduDataPtr,
                                                                           P2CONST(RetryInfoType, AUTOMATIC, PDUR_APPL_DATA) retry, P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) availableDataPtr)
{
  PduR_Det_ReportError(PDUR_GWTP_TXINSTSM_COPYTXDATA_UNEXPECTEDCALL, PDUR_E_UNEXPECTED_CALL);
  PDUR_DUMMY_STATEMENT(rmGDestRomIdx);  /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(pduLength);      /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(sduDataPtr);     /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(retry);  /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(availableDataPtr);       /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  return BUFREQ_E_NOT_OK;
}
#endif

#if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
 /**********************************************************************************************************************
 * PduR_TxInstSm_CopyTxData_RmTxinstAborted
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *********************************************************************************************************************/
/* PRQA  S 3673 3 */ /* MD_PduR_3673_Abort */
FUNC(BufReq_ReturnType, PDUR_CODE) PduR_TxInstSm_CopyTxData_RmTxinstAborted(PduR_RmGDestRomIterType rmGDestRomIdx, PduLengthType pduLength,
                                                                            SduDataPtrType sduDataPtr,
                                                                            P2CONST(RetryInfoType, AUTOMATIC, PDUR_APPL_DATA) retry, P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) availableDataPtr)
{
  PDUR_DUMMY_STATEMENT(rmGDestRomIdx);  /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(pduLength);      /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(sduDataPtr);     /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(retry);  /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(availableDataPtr);       /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  return BUFREQ_E_NOT_OK;
}
#endif

#if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_TxInstSm_TpTxConfirmation_RmTxinstActiveOrRmTxinstAborted
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *

 *
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_TxInstSm_TpTxConfirmation_RmTxinstActiveOrRmTxinstAborted(PduR_RmGDestRomIterType rmGDestRomIdx, Std_ReturnType result)
{
  PduR_FmFifoRomIterType fmFifoRomIdx = PduR_GetFmFifoRomIdxOfFmFifoInstanceRom(PduR_GetFmFifoInstanceRomIdxOfRmGDestRom(rmGDestRomIdx));
  PduR_BmTxBufferInstanceRomIterType bmTxBufferInstanceRomIdx = PduR_GetBmTxBufferInstanceRomIdxOfFmFifoInstanceRam(PduR_GetFmFifoInstanceRomIdxOfRmGDestRom(rmGDestRomIdx));
  PduR_SetTpTxInstSmStateOfRmGDestTpTxStateRam(PduR_GetRmGDestTpTxStateRamIdxOfRmGDestRom(rmGDestRomIdx), PDUR_RM_TXINST_IDLE_TPTXINSTSMSTATEOFRMGDESTTPTXSTATERAM);    /* SBSW_PDUR_CSL03 */
  PduR_Bm_ResetTxBufferInstance(bmTxBufferInstanceRomIdx);
  PduR_DecPendingConfirmationsOfFmFifoRam(fmFifoRomIdx);        /* SBSW_PDUR_CSL03 */
  PduR_GetFctPtrOfFinishTransmissionRmSmTransition(PduR_GetTpTxSmStateOfFmFifoRam(fmFifoRomIdx)) (rmGDestRomIdx, result);       /* SBSW_PDUR_CSL03 */
  PDUR_DUMMY_STATEMENT(result); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
}
#endif

#if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_TxInstSm_TpTxConfirmation_UnexpectedCall
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_TxInstSm_TpTxConfirmation_UnexpectedCall(PduR_RmGDestRomIterType rmGDestRomIdx, Std_ReturnType result)
{
  PduR_Det_ReportError(PDUR_GWTP_TXINSTSM_TPTXCONFIRMATION_UNEXPECTEDCALL, PDUR_E_UNEXPECTED_CALL);
  PDUR_DUMMY_STATEMENT(rmGDestRomIdx);  /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(result); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
}
#endif

#if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_TxInstSm_TpTriggerTransmit_RmTxinstIdle
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *********************************************************************************************************************/
FUNC(Std_ReturnType, PDUR_CODE) PduR_TxInstSm_TpTriggerTransmit_RmTxinstIdle(PduR_RmDestRomIterType rmDestIdx)
{
  Std_ReturnType retVal = E_OK;
  PduR_RmGDestRomIterType rmGDestRomIdx = PduR_GetRmGDestRomIdxOfRmDestRom(rmDestIdx);
  PduR_FmFifoRomIterType fmFifoRomIdx = PduR_GetFmFifoRomIdxOfFmFifoInstanceRom(PduR_GetFmFifoInstanceRomIdxOfRmGDestRom(rmGDestRomIdx));
  PduR_FmFifoElementRamIterType fmFifoElementRamTPReadIdx = PduR_GetFmFifoElementRamReadIdxOfFmFifoRam(fmFifoRomIdx);
  PduR_RmSrcRomIterType rmSrcIdx = PduR_GetRmSrcRomIdxOfRmDestRom(PduR_GetRmDestRomIdxOfFmFifoElementRam(fmFifoElementRamTPReadIdx));
  /* If query is necessary to keep the correct order in case of a N:1 routing */
  PduR_SetTpTxInstSmStateOfRmGDestTpTxStateRam(PduR_GetRmGDestTpTxStateRamIdxOfRmGDestRom(rmGDestRomIdx), PDUR_RM_TXINST_ACTIVE_TPTXINSTSMSTATEOFRMGDESTTPTXSTATERAM);  /* SBSW_PDUR_CSL03 */
  if(PduR_RmTp_LoAndUpTransmit(rmSrcIdx, rmDestIdx) != E_OK)
  {
    retVal = E_NOT_OK;
  }
  return retVal;
}
#endif

#if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_TxInstSm_TpTriggerTransmit_FatalError
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *********************************************************************************************************************/
FUNC(Std_ReturnType, PDUR_CODE) PduR_TxInstSm_TpTriggerTransmit_FatalError(PduR_RmDestRomIterType rmDestIdx)    /* COV_PDUR_FATAL_ERROR */
{
  PduR_Det_ReportError(PDUR_RM_TPTRIGGERTRANSMIT_FATALERROR, PDUR_E_FATAL);
  PDUR_DUMMY_STATEMENT(rmDestIdx);      /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  return E_NOT_OK;
}
#endif

#if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_TxInstSm_TpCancelTransmit_FatalError
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *********************************************************************************************************************/
FUNC(Std_ReturnType, PDUR_CODE) PduR_TxInstSm_TpCancelTransmit_FatalError(PduR_RmDestRomIterType rmGDestRomIdx) /* COV_PDUR_FATAL_ERROR */
{
  PduR_Det_ReportError(PDUR_GWTP_TXINSTSM_TPCANCELTRANSMIT_FATALERROR, PDUR_E_FATAL);
  PDUR_DUMMY_STATEMENT(rmGDestRomIdx);  /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  return E_NOT_OK;
}
#endif

#if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_TxInstSm_TpCancelTransmit_RmTxinstActive
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *********************************************************************************************************************/
FUNC(Std_ReturnType, PDUR_CODE) PduR_TxInstSm_TpCancelTransmit_RmTxinstActive(PduR_RmDestRomIterType rmGDestRomIdx)
{
  PduR_SetTpTxInstSmStateOfRmGDestTpTxStateRam(PduR_GetRmGDestTpTxStateRamIdxOfRmGDestRom(rmGDestRomIdx), PDUR_RM_TXINST_ABORTED_TPTXINSTSMSTATEOFRMGDESTTPTXSTATERAM); /* SBSW_PDUR_CSL01 */
  return E_OK;
}
#endif

#if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_TxInstSm_TpCancelTransmit_RmTxinstAborted
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *********************************************************************************************************************/
FUNC(Std_ReturnType, PDUR_CODE) PduR_TxInstSm_TpCancelTransmit_RmTxinstAborted(PduR_RmDestRomIterType rmGDestRomIdx)    /* COV_PDUR_DUMMY_FUNCTION */
{
  /* nothing to do */
  PDUR_DUMMY_STATEMENT(rmGDestRomIdx);  /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  return E_OK;
}
#endif

#if (((PDUR_TXCONFIRMATIONUSEDOFTXIF2UP == STD_ON) && ((PDUR_EXISTS_T_T_FIFO_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON) || (PDUR_EXISTS_DIRECT_FIFO_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON))) || (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON))
/**********************************************************************************************************************
 * PduR_Fm_Peek
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
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_Fm_Peek(PduR_FmFifoRamIterType fmFifoRamIdx, P2VAR(PduR_FmFifoElementRamIterType, AUTOMATIC, PDUR_APPL_DATA) fmFifoElementRamIdx)
{
  Std_ReturnType retVal = E_NOT_OK;
  /* Start search on last read idx */
  PduR_FmFifoElementRamReadIdxOfFmFifoRamType fmFifoElementRamTPReadIdx = PduR_GetFmFifoElementRamReadIdxOfFmFifoRam(fmFifoRamIdx);
  /* FifoElements in the queue? */
  while(PduR_GetFillLevelOfFmFifoRam(fmFifoRamIdx) > 0)
  {
    /* Get next element */
    if(fmFifoElementRamTPReadIdx >= ((PduR_GetFmFifoElementRamEndIdxOfFmFifoRom(fmFifoRamIdx) - 1U)))
    {
      /* Wrap-around */
      fmFifoElementRamTPReadIdx = PduR_GetFmFifoElementRamStartIdxOfFmFifoRom(fmFifoRamIdx);
    }
    else
    {
      fmFifoElementRamTPReadIdx++;
    }
    *fmFifoElementRamIdx = fmFifoElementRamTPReadIdx;   /* SBSW_PDUR_VALID_PTR_ENSURED_BY_CALLING_FUNCTION */
    /* FifoElement active? */
    if(PduR_Fm_IsFifoElementAllocated(fmFifoElementRamTPReadIdx) == E_OK)
    {
      retVal = E_OK;
      PduR_DecFillLevelOfFmFifoRam(fmFifoRamIdx);       /* SBSW_PDUR_IDX_PARAM_INTERNAL_FUNCTION */
      PduR_SetFmFifoElementRamReadIdxOfFmFifoRam(fmFifoRamIdx, fmFifoElementRamTPReadIdx);      /* SBSW_PDUR_IDX_PARAM_INTERNAL_FUNCTION */
      break;
    }
    /* FifoElement is invalid -> Adapt fill level and update read pointer */
    else
    {
      PduR_DecFillLevelOfFmFifoRam(fmFifoRamIdx);       /* SBSW_PDUR_IDX_PARAM_INTERNAL_FUNCTION */
      PduR_SetFmFifoElementRamReadIdxOfFmFifoRam(fmFifoRamIdx, fmFifoElementRamTPReadIdx);      /* SBSW_PDUR_IDX_PARAM_INTERNAL_FUNCTION */
      /* must be done because the Index in not set back to the begining. The Idx move through the buffer and the next element is initialized with pending */
    }
  }
  return retVal;
}
#endif

#if (PDUR_FMFIFORAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Fm_AssignFifoElement
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
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_Fm_AssignFifoElement(PduR_FmFifoRamIterType fmFifoRamIdx,
                                                                       P2VAR(PduR_FmFifoElementRamWriteIdxOfFmFifoRamType, AUTOMATIC, PDUR_APPL_DATA) fmFifoElementRamIdx)
{
  Std_ReturnType retVal = E_NOT_OK;
  /* Start search on last write idx */
  PduR_FmFifoElementRamWriteIdxOfFmFifoRamType fmFifoElementRamWriteIdx = PduR_GetFmFifoElementRamWriteIdxOfFmFifoRam(fmFifoRamIdx);

  /* Free FifoElement available? */
  if(PduR_Fm_AllocateFifoElement(fmFifoElementRamWriteIdx) == E_OK)     /* COV_PDUR_ONLY_DEDICATED_BUFFER */
  {
    /* Return the found free FiFoElement */
    *fmFifoElementRamIdx = fmFifoElementRamWriteIdx;    /* SBSW_PDUR_VALID_PTR_ENSURED_BY_CALLING_FUNCTION */
    /* Get next fifo element */ /* Check if the write Idx is at the end (EndIdx -1) */
    if(fmFifoElementRamWriteIdx >= (PduR_GetFmFifoElementRamEndIdxOfFmFifoRom(fmFifoRamIdx) - 1U))      /* COV_PDUR_ONLY_DEDICATED_BUFFER */
    {
      /* Wrap-around */
      fmFifoElementRamWriteIdx = PduR_GetFmFifoElementRamStartIdxOfFmFifoRom(fmFifoRamIdx);
    }
    else
    {
      fmFifoElementRamWriteIdx++;
    }
    /* Update global FifoElement write pointer. This pointer points to the next available Fifo element. */
    PduR_SetFmFifoElementRamWriteIdxOfFmFifoRam(fmFifoRamIdx, fmFifoElementRamWriteIdx);        /* SBSW_PDUR_CSL03 */
    retVal = E_OK;
  }
  return retVal;
}
#endif

#if (PDUR_FMFIFORAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Fm_AssignFifoElement
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *********************************************************************************************************************/
FUNC(Std_ReturnType, PDUR_CODE) PduR_Fm_AllocateFifoElement(PduR_FmFifoElementRamIterType fmFifoElementRamWriteIdx)
{
  Std_ReturnType retVal = E_NOT_OK;
  if(PduR_Fm_IsFifoElementAllocated(fmFifoElementRamWriteIdx) != E_OK)
  {
    PduR_SetStateOfFmFifoElementRam(fmFifoElementRamWriteIdx, PDUR_FM_ALLOCATED_STATEOFFMFIFOELEMENTRAM);       /* SBSW_PDUR_CSL03 */
    retVal = E_OK;
  }
  return retVal;
}
#endif

#if (PDUR_FMFIFORAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Fm_IsFifoElementAllocated
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
*********************************************************************************************************************/
LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_Fm_IsFifoElementAllocated(PduR_FmFifoElementRamIterType fmFifoElementRamIdx)
{
  Std_ReturnType retVal = E_OK;
  /* Is a TxBuffer assigned/allocated to the FifoElement? */
  if(PduR_IsDedicatedTxBufferOfFmFifoElementRam(fmFifoElementRamIdx)) /* COV_PDUR_ONLY_SHARED_BUFFER */
  {
    if((PduR_GetStateOfFmFifoElementRam(fmFifoElementRamIdx) == (PduR_BmTxBufferInstanceRomIterType) PDUR_FM_ALLOCATED_WITH_BUFFER_STATEOFFMFIFOELEMENTRAM)) /* COV_PDUR_ONLY_SHARED_BUFFER */
    {
      retVal = E_NOT_OK;
    }
  }
  else
  {
    if((PduR_GetStateOfFmFifoElementRam(fmFifoElementRamIdx) == (PduR_BmTxBufferInstanceRomIterType) PDUR_FM_IDLE_STATEOFFMFIFOELEMENTRAM))
    {
      retVal = E_NOT_OK;
    }
  }
  return retVal;
}
#endif

#if (PDUR_FMFIFORAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Fm_AssignTxBuffer2FifoElement
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
  *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_Fm_AssignTxBuffer2FifoElement(PduR_FmFifoElementRamIterType fmFifoElementRamWriteIdx, PduR_BmTxBufferRomIdxOfFmFifoElementRamType bmTxBufferRomIdx)
{
  /* Initialize buffer and assign to FifoElement */
  PduR_SetStateOfFmFifoElementRam(fmFifoElementRamWriteIdx, PDUR_FM_ALLOCATED_WITH_BUFFER_STATEOFFMFIFOELEMENTRAM);     /* SBSW_PDUR_CSL01 */
  PduR_SetBmTxBufferRomIdxOfFmFifoElementRam(fmFifoElementRamWriteIdx, bmTxBufferRomIdx);       /* SBSW_PDUR_CSL03 */
}
#endif

#if (PDUR_FMFIFORAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Fm_DissolveFifoElementTxBufferRelation
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
  *********************************************************************************************************************/
LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_Fm_DissolveFifoElementTxBufferRelation(PduR_FmFifoElementRamIterType fmFifoElementRamIdx)
{
  PduR_SetBmTxBufferRomIdxOfFmFifoElementRam(fmFifoElementRamIdx, PDUR_NO_BMTXBUFFERROMIDXOFFMFIFOELEMENTRAM);  /* SBSW_PDUR_IDX_PARAM_INTERNAL_FUNCTION */
}
#endif

#if (PDUR_FMFIFORAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Fm_ReleaseFifoElement
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
  *********************************************************************************************************************/
LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_Fm_ReleaseFifoElement(PduR_FmFifoElementRamIterType fmFifoElementRamIdx)
{
  PduR_SetRmDestRomIdxOfFmFifoElementRam(fmFifoElementRamIdx, PDUR_NO_RMDESTROMIDXOFFMFIFOELEMENTRAM);  /* SBSW_PDUR_CSL03 */
  PduR_SetStateOfFmFifoElementRam(fmFifoElementRamIdx, PDUR_FM_IDLE_STATEOFFMFIFOELEMENTRAM);   /* SBSW_PDUR_CSL03 */
}
#endif

#if((PDUR_EXISTS_TP_UNBUFFERED_TX_API_FWD_ROUTINGTYPEOFRMDESTROM == STD_ON) || (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON))
/**********************************************************************************************************************
 * PduR_RmTp_MultipleSourceHandler_Transmit
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_RmTp_MultipleSourceHandler_Transmit(PduR_RmDestRomIterType rmDestRomIdx, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info)
{
  Std_ReturnType retVal = E_NOT_OK;
  SchM_Enter_PduR_PDUR_EXCLUSIVE_AREA_0();      /* PRQA S 3109 */ /* MD_MSR_14.3 */
  {
    PduR_RmGDestRomIdxOfRmDestRomType rmGDestRomIdx = PduR_GetRmGDestRomIdxOfRmDestRom(rmDestRomIdx);

# if(PDUR_RMGDESTNTO1INFORAMIDXOFRMGDESTROM == STD_ON)
    if(PduR_IsRmGDestNto1InfoRamUsedOfRmGDestRom(rmGDestRomIdx))
    {
      PduR_RmGDestNto1InfoRamIdxOfRmGDestRomType rmGDestNto1InfoIdx = PduR_GetRmGDestNto1InfoRamIdxOfRmGDestRom(rmGDestRomIdx);

      if(!PduR_IsTransmissionActiveOfRmGDestNto1InfoRam(rmGDestNto1InfoIdx))
      {
        PduR_SetRmDestRomIdxOfRmGDestNto1InfoRam(rmGDestNto1InfoIdx, (PduR_RmDestRomIdxOfRmGDestNto1InfoRamType) rmDestRomIdx); /* SBSW_PDUR_CSL03 */
        PduR_SetTransmissionActiveOfRmGDestNto1InfoRam(rmGDestNto1InfoIdx, TRUE);    /* SBSW_PDUR_CSL03 */

        retVal = PduR_GetLoTpTransmitFctPtrOfMmRom(PduR_GetMmRomIdxOfRmGDestRom(rmGDestRomIdx)) (PduR_GetDestHndOfRmGDestRom(rmGDestRomIdx), info);     /* SBSW_PDUR_API_CALL_FORWARDING_ID_AND_PTR */
        if(retVal != E_OK)
        {
          PduR_Rm_MultipleSourceHandler_Reset(rmGDestRomIdx);
        }
      }
    }
    else
# endif
    {
      retVal = PduR_GetLoTpTransmitFctPtrOfMmRom(PduR_GetMmRomIdxOfRmGDestRom(rmGDestRomIdx)) (PduR_GetDestHndOfRmGDestRom(rmGDestRomIdx), info);       /* SBSW_PDUR_API_CALL_FORWARDING_ID_AND_PTR */
    }
  }
  SchM_Exit_PduR_PDUR_EXCLUSIVE_AREA_0();       /* PRQA S 3109 */ /* MD_MSR_14.3 */
  return retVal;
}
#endif

#if((PDUR_EXISTS_TP_UNBUFFERED_TX_API_FWD_ROUTINGTYPEOFRMDESTROM == STD_ON) || (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON))
/**********************************************************************************************************************
 * PduR_RmTp_MultipleSourceHandler_TpTxConfirmation
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_RmTp_MultipleSourceHandler_TpTxConfirmation(PduR_RmGDestRomIdxOfTxTp2SrcType rmGDestRomIdx, Std_ReturnType result)
{
  SchM_Enter_PduR_PDUR_EXCLUSIVE_AREA_0();      /* PRQA S 3109 */ /* MD_MSR_14.3 */
  {
    PduR_RmDestRomIterType rmDestRomIdx;

    if(PduR_Rm_GetSrcDestPdu(rmGDestRomIdx, &rmDestRomIdx) == E_OK)     /* SBSW_PDUR_STACK_VARIABLE */ /* COV_PDUR_NO_NTO1_ROUTINGPATHS */
    {
# if(PDUR_RMGDESTNTO1INFORAMIDXOFRMGDESTROM == STD_ON)
      PduR_Rm_MultipleSourceHandler_Reset(rmGDestRomIdx);
# endif

      switch (PduR_GetRoutingTypeOfRmDestRom(rmDestRomIdx))
      {
# if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
        case PDUR_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM:
          PduR_RmTp_TpTxConfirmation(rmGDestRomIdx, result);
          break;
# endif
# if (PDUR_EXISTS_TP_UNBUFFERED_TX_API_FWD_ROUTINGTYPEOFRMDESTROM == STD_ON)
        case PDUR_TP_UNBUFFERED_TX_API_FWD_ROUTINGTYPEOFRMDESTROM:
        {
          PduR_RmSrcRomIdxOfRmDestRomType rmSrcRomIdx = PduR_GetRmSrcRomIdxOfRmDestRom(rmDestRomIdx);
          PduR_GetUpTpTpTxConfirmationFctPtrOfMmRom(PduR_GetMmRomIdxOfRmSrcRom(rmSrcRomIdx)) (PduR_GetSrcHndOfRmSrcRom(rmSrcRomIdx), result);     /* SBSW_PDUR_API_CALL_FORWARDING_ID_ONLY */
        }
          break;
# endif
        default: /* COV_PDUR_MISRA */
          break;
      }
    }
    else
    {
      PduR_Det_ReportError(PDUR_GWTP_MULTIPLESOURCEHANDLER_TPTXCONFIRMATION, PDUR_E_UNEXPECTED_CALL);
    }
  }
  SchM_Exit_PduR_PDUR_EXCLUSIVE_AREA_0();       /* PRQA S 3109 */ /* MD_MSR_14.3 */
}
#endif

#if((PDUR_EXISTS_TP_UNBUFFERED_TX_API_FWD_ROUTINGTYPEOFRMDESTROM == STD_ON) || (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON))
/**********************************************************************************************************************
 * PduR_RmTp_MultipleSourceHandler_CopyTxData
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(BufReq_ReturnType, PDUR_CODE) PduR_RmTp_MultipleSourceHandler_CopyTxData(PduR_RmGDestRomIdxOfTxTp2SrcType rmGDestRomIdx, P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info,
                                                                                           P2VAR(RetryInfoType, AUTOMATIC, PDUR_APPL_DATA) retry, P2VAR(PduLengthType, AUTOMATIC,
                                                                                                                                                        PDUR_APPL_DATA) availableDataPtr)
{
  BufReq_ReturnType retVal = BUFREQ_E_NOT_OK;
  SchM_Enter_PduR_PDUR_EXCLUSIVE_AREA_0();      /* PRQA S 3109 */ /* MD_MSR_14.3 */
  {
    PduR_RmDestRomIterType rmDestRomIdx;

    if(PduR_Rm_GetSrcDestPdu(rmGDestRomIdx, &rmDestRomIdx) == E_OK)     /* SBSW_PDUR_STACK_VARIABLE */ /* COV_PDUR_NO_NTO1_ROUTINGPATHS */
    {
# if (PDUR_RMDESTRPGROMIDXOFRMDESTROM == STD_ON)
      if((!PduR_IsRmDestRpgRomUsedOfRmDestRom(rmDestRomIdx)) || (0 != PduR_GetEnabledCntOfRmDestRpgRam(PduR_GetRmDestRpgRomIdxOfRmDestRom(rmDestRomIdx))))
# endif
      {
        switch (PduR_GetRoutingTypeOfRmDestRom(rmDestRomIdx))
        {
  # if (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
          case PDUR_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM:
            retVal = PduR_RmTp_CopyTxData(rmGDestRomIdx, info, retry, availableDataPtr);  /* SBSW_PDUR_API_CALL_FORWARDING_ID_AND_PTR */
            break;
  # endif
  # if (PDUR_EXISTS_TP_UNBUFFERED_TX_API_FWD_ROUTINGTYPEOFRMDESTROM == STD_ON)
          case PDUR_TP_UNBUFFERED_TX_API_FWD_ROUTINGTYPEOFRMDESTROM:
          {
            PduR_RmSrcRomIdxOfRmDestRomType rmSrcRomIdx = PduR_GetRmSrcRomIdxOfRmDestRom(rmDestRomIdx);
            retVal = PduR_GetUpTpCopyTxDataFctPtrOfMmRom(PduR_GetMmRomIdxOfRmSrcRom(rmSrcRomIdx)) (PduR_GetSrcHndOfRmSrcRom(rmSrcRomIdx), info, retry, availableDataPtr); /* SBSW_PDUR_API_CALL_FORWARDING_ID_AND_PTR */
          }
            break;
  # endif
          default: /* COV_PDUR_MISRA */
            break;
        }
      }
    }
    else
    {
      PduR_Det_ReportError(PDUR_GWTP_MULTIPLESOURCEHANDLER_COPYTXDATA, PDUR_E_UNEXPECTED_CALL);
    }
  }
  SchM_Exit_PduR_PDUR_EXCLUSIVE_AREA_0();       /* PRQA S 3109 */ /* MD_MSR_14.3 */
  return retVal;
}
#endif

#if((PDUR_TPCANCELTRANSMITSUPPORTEDOFMMROM == STD_ON) && (PDUR_EXISTS_TP_UNBUFFERED_TX_API_FWD_ROUTINGTYPEOFRMDESTROM == STD_ON))
/**********************************************************************************************************************
 * PduR_RmTp_MultipleSourceHandler_CancelTransmit
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
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_RmTp_MultipleSourceHandler_CancelTransmit(PduR_RmDestRomIterType rmDestRomIdx)
{
  Std_ReturnType retVal = E_NOT_OK;
  SchM_Enter_PduR_PDUR_EXCLUSIVE_AREA_0();      /* PRQA S 3109 */ /* MD_MSR_14.3 */
  {
    PduR_RmGDestRomIdxOfRmDestRomType rmGDestRomIdx = PduR_GetRmGDestRomIdxOfRmDestRom(rmDestRomIdx);

# if(PDUR_RMGDESTNTO1INFORAMIDXOFRMGDESTROM == STD_ON)
    if(PduR_IsRmGDestNto1InfoRamUsedOfRmGDestRom(rmGDestRomIdx))
    {
      PduR_RmGDestNto1InfoRamIdxOfRmGDestRomType rmGDestNto1InfoIdx = PduR_GetRmGDestNto1InfoRamIdxOfRmGDestRom(rmGDestRomIdx);
      PduR_RmDestRomIterType lastTxdRmDestRomIdx;
      Std_ReturnType foundSrcPdu = PduR_Rm_GetSrcDestPdu(rmGDestRomIdx, &lastTxdRmDestRomIdx);  /* SBSW_PDUR_STACK_VARIABLE */

      if(PduR_IsTransmissionActiveOfRmGDestNto1InfoRam(rmGDestNto1InfoIdx) && (foundSrcPdu == E_OK) && (rmDestRomIdx == lastTxdRmDestRomIdx)) /* COV_PDUR_ROBUSTNESS */
      {
        retVal = PduR_GetLoTpCancelTransmitFctPtrOfMmRom(PduR_GetMmRomIdxOfRmGDestRom(rmGDestRomIdx)) (PduR_GetDestHndOfRmGDestRom(rmGDestRomIdx));     /* SBSW_PDUR_API_CALL_FORWARDING_ID_AND_PTR */
      }
      else
      {
        PduR_Det_ReportError(PDUR_GWTP_MULTIPLESOURCEHANDLER_CANCELTRANSMIT, PDUR_E_UNEXPECTED_CALL);
      }
    }
    else
# endif
    {
      retVal = PduR_GetLoTpCancelTransmitFctPtrOfMmRom(PduR_GetMmRomIdxOfRmGDestRom(rmGDestRomIdx)) (PduR_GetDestHndOfRmGDestRom(rmGDestRomIdx));       /* SBSW_PDUR_API_CALL_FORWARDING_ID_AND_PTR */
    }
  }
  SchM_Exit_PduR_PDUR_EXCLUSIVE_AREA_0();       /* PRQA S 3109 */ /* MD_MSR_14.3 */
  return retVal;
}
#endif

#if (PDUR_SMDATAPLANEROM == STD_ON)
/**********************************************************************************************************************
 * PduR_Sm_Init
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_Sm_Init(void)
{
  PduR_SmFibRamIterType smFibRamIdx;
  for(smFibRamIdx = 0; smFibRamIdx < PduR_GetSizeOfSmFibRam(); smFibRamIdx++)
  {
    PduR_SetLearnedConnectionIdOfSmFibRam(smFibRamIdx, PDUR_SM_UNLEARNED_CONNECTION);   /* SBSW_PDUR_CSL01 */
  }
}
#endif

#if (PDUR_SMLINEARTATOSACALCULATIONSTRATEGYROM == STD_ON)
/**********************************************************************************************************************
 * PduR_Sm_LinearTaToSaCalculationStrategy_GetSa_AddOffset
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
FUNC(PduR_SmSaType, PDUR_CODE) PduR_Sm_LinearTaToSaCalculationStrategy_GetSa_AddOffset(PduR_SmLinearTaToSaCalculationStrategyRomIterType smLinearTaToSaCalculationStrategyIdx, uint32 metaData)
{
  PduR_MaskOfSmLinearTaToSaCalculationStrategyRomType mask = PduR_GetMaskOfSmLinearTaToSaCalculationStrategyRom(smLinearTaToSaCalculationStrategyIdx);
  PduR_OffsetOfSmLinearTaToSaCalculationStrategyRomType offset = PduR_GetOffsetOfSmLinearTaToSaCalculationStrategyRom(smLinearTaToSaCalculationStrategyIdx);
  PduR_SmSaType sourceAdress = (metaData + offset) & mask;
  return sourceAdress;
}
#endif

#if (PDUR_SMLINEARTATOSACALCULATIONSTRATEGYROM == STD_ON)
/**********************************************************************************************************************
 * PduR_Sm_LinearTaToSaCalculationStrategy_SubtractOffset
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *********************************************************************************************************************/
FUNC(PduR_SmSaType, PDUR_CODE) PduR_Sm_LinearTaToSaCalculationStrategy_GetSa_SubtractOffset(PduR_SmLinearTaToSaCalculationStrategyRomIterType smLinearTaToSaCalculationStrategyIdx, uint32 metaData)
{
  PduR_MaskOfSmLinearTaToSaCalculationStrategyRomType mask = PduR_GetMaskOfSmLinearTaToSaCalculationStrategyRom(smLinearTaToSaCalculationStrategyIdx);
  PduR_OffsetOfSmLinearTaToSaCalculationStrategyRomType offset = PduR_GetOffsetOfSmLinearTaToSaCalculationStrategyRom(smLinearTaToSaCalculationStrategyIdx);
  PduR_SmSaType sourceAdress = (metaData - offset) & mask;
  return sourceAdress;
}
#endif

#if (PDUR_SMSATAFROMMETADATACALCULATIONSTRATEGYROM == STD_ON)
/**********************************************************************************************************************
 * PduR_Sm_SaTaFromMetaDataCalculationStrategy_GetSa
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(PduR_SmSaType, PDUR_CODE) PduR_Sm_SaTaFromMetaDataCalculationStrategy_GetSa(PduR_SmSaTaFromMetaDataCalculationStrategyRomIterType smSaTaFromMetaDataCalculationStrategyRomIdx,
                                                                                              uint32 metaData)
{
  /* Get adress startbit / mask */
  PduR_SaStartBitOfSmSaTaFromMetaDataCalculationStrategyRomType saStartBitPos = PduR_GetSaStartBitOfSmSaTaFromMetaDataCalculationStrategyRom(smSaTaFromMetaDataCalculationStrategyRomIdx);
  PduR_SaMaskOfSmSaTaFromMetaDataCalculationStrategyRomType saMask = PduR_GetSaMaskOfSmSaTaFromMetaDataCalculationStrategyRom(smSaTaFromMetaDataCalculationStrategyRomIdx);

  /* Extract SA and TA from meta data */
  PduR_SmSaType sourceAdress = (metaData >> saStartBitPos) & saMask;
  return sourceAdress;
}
#endif

#if (PDUR_SMSATAFROMMETADATACALCULATIONSTRATEGYROM == STD_ON)
/**********************************************************************************************************************
 * PduR_Sm_SaTaFromMetaDataCalculationStrategy_GetTa
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(PduR_SmTaType, PDUR_CODE) PduR_Sm_SaTaFromMetaDataCalculationStrategy_GetTa(PduR_SmSaTaFromMetaDataCalculationStrategyRomIterType smSaTaFromMetaDataCalculationStrategyRomIdx,
                                                                                              uint32 metaData)
{
  /* Get adress startbit / mask */
  PduR_TaStartBitOfSmSaTaFromMetaDataCalculationStrategyRomType taStartBitPos = PduR_GetTaStartBitOfSmSaTaFromMetaDataCalculationStrategyRom(smSaTaFromMetaDataCalculationStrategyRomIdx);
  PduR_TaMaskOfSmSaTaFromMetaDataCalculationStrategyRomType taMask = PduR_GetTaMaskOfSmSaTaFromMetaDataCalculationStrategyRom(smSaTaFromMetaDataCalculationStrategyRomIdx);

  /* Extract SA and TA from meta data */
  PduR_SmTaType targetAdress = (metaData >> taStartBitPos) & taMask;
  return targetAdress;
}
#endif

#if (PDUR_SMDATAPLANEROM == STD_ON)
/**********************************************************************************************************************
 * PduR_Sm_GetMetaData
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(uint32, PDUR_CODE) PduR_Sm_GetMetaData(P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info, uint8 metaDataLength)
{
  uint32 metaData = 0;
  SduDataPtrType metaDataPtr = &info->SduDataPtr[info->SduLength - metaDataLength];
  uint8 itMetaData;
  for(itMetaData = metaDataLength; itMetaData > 0; itMetaData--)
  {
    metaData = (((uint32) (metaData << 8)) | metaDataPtr[itMetaData - 1]);
  }
  return metaData;
}
#endif

#if (PDUR_SMDATAPLANEROM == STD_ON)
/**********************************************************************************************************************
 * PduR_Sm_UpdateFib
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_Sm_UpdateFib(PduR_SmDataPlaneRomIterType smDataPlaneIdx, PduR_SmSaType sourceAdress, PduR_ConnectionIdOfSmSrcRomType learnedConnectionId)
{
  PduR_SmFibRamIterType smFibRamIdx = PduR_GetSmFibRamStartIdxOfSmDataPlaneRom(smDataPlaneIdx) + sourceAdress;
  SchM_Enter_PduR_PDUR_EXCLUSIVE_AREA_0();      /* PRQA S 3109 */ /* MD_MSR_14.3 */
  PduR_SetLearnedConnectionIdOfSmFibRam(smFibRamIdx, (PduR_LearnedConnectionIdOfSmFibRamType) learnedConnectionId);     /* SBSW_PDUR_CSL01 */
  SchM_Exit_PduR_PDUR_EXCLUSIVE_AREA_0();       /* PRQA S 3109 */ /* MD_MSR_14.3 */
}
#endif

#if (PDUR_SMDATAPLANEROM == STD_ON)
/**********************************************************************************************************************
 * PduR_Sm_CheckLearned
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(PduR_FilterReturnType, PDUR_CODE) PduR_Sm_CheckLearned(PduR_SmDataPlaneRomIterType smDataPlaneIdx, PduR_SmTaType targetAdress, PduR_ConnectionIdOfSmGDestRomType destConnection)
{
  PduR_FilterReturnType filterResult;
  PduR_SmFibRamIterType smFibRamIdx = PduR_GetSmFibRamStartIdxOfSmDataPlaneRom(smDataPlaneIdx) + targetAdress;
  PduR_LearnedConnectionIdOfSmFibRamType learnedConnectionId;

  SchM_Enter_PduR_PDUR_EXCLUSIVE_AREA_0();      /* PRQA S 3109 */ /* MD_MSR_14.3 */
  learnedConnectionId = PduR_GetLearnedConnectionIdOfSmFibRam(smFibRamIdx);
  SchM_Exit_PduR_PDUR_EXCLUSIVE_AREA_0();       /* PRQA S 3109 */ /* MD_MSR_14.3 */

  if((learnedConnectionId == PDUR_SM_UNLEARNED_CONNECTION) ||   /* Related connection is no learned yet. */
     (learnedConnectionId == destConnection))   /* Routing destination connection is the learned connection. */
  {
    filterResult = PDUR_FILTER_PASS;    /* Let the routing pass */
  }
  else
  {
    filterResult = PDUR_FILTER_BLOCK;   /* Block the routing, it is not the learned destination connection */
  }
  return filterResult;
}
#endif

#if(PDUR_SMDATAPLANEROM == STD_ON)
/**********************************************************************************************************************
 * PduR_Sm_SrcFilter_LinearTaToSaCalculationStrategy
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_Sm_SrcFilter_LinearTaToSaCalculationStrategy(PduR_SmSrcRomIdxOfRmSrcRomType smSrcRomIdx, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info)
{
  PduR_SmDataPlaneRomIterType smDataPlaneIdx = PduR_GetSmDataPlaneRomIdxOfSmSrcRom(smSrcRomIdx);
  PduR_SmLinearTaToSaCalculationStrategyRomIterType smLinearTaToSaCalculationStrategyIdx = PduR_GetSmLinearTaToSaCalculationStrategyRomIdxOfSmDataPlaneRom(smDataPlaneIdx);

  /* Get adress info from Pdu */
  uint32 metaData = PduR_Sm_GetMetaData(info, PduR_GetMetaDataLengthOfSmSrcRom(smSrcRomIdx));   /* SBSW_PDUR_VALID_PTR_ENSURED_BY_CALLING_FUNCTION */
  PduR_Sm_LinearTaToSaCalculationStrategy_GetSaFctPtrType getSaFctPtr =
    PduR_GetSmLinearTaToSaCalculationStrategyGetSaFctPtr(PduR_GetSmLinearTaToSaCalculationStrategyGetSaFctPtrIdxOfSmSrcRom(smSrcRomIdx));
  PduR_SmSaType sourceAdress = getSaFctPtr(smLinearTaToSaCalculationStrategyIdx, metaData);     /* SBSW_PDUR_CSL03 */

  /* Update FIB */
  PduR_Sm_UpdateFib(smDataPlaneIdx, sourceAdress, PduR_GetConnectionIdOfSmSrcRom(smSrcRomIdx));
}
#endif

#if(PDUR_SMLINEARTATOSACALCULATIONSTRATEGYROM == STD_ON)
/**********************************************************************************************************************
 * PduR_Sm_DestFilter_LinearTaToSaCalculationStrategy
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *********************************************************************************************************************/
FUNC(PduR_FilterReturnType, PDUR_CODE) PduR_Sm_DestFilter_LinearTaToSaCalculationStrategy(PduR_SmGDestRomIdxOfRmGDestRomType smGDestRomIdx, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info)
{
  PduR_SmDataPlaneRomIterType smDataPlaneIdx = PduR_GetSmDataPlaneRomIdxOfSmGDestRom(smGDestRomIdx);
  PduR_SmLinearTaToSaCalculationStrategyRomIterType smLinearTaToSaCalculationStrategyIdx = PduR_GetSmLinearTaToSaCalculationStrategyRomIdxOfSmDataPlaneRom(smDataPlaneIdx);

  /* Get target adress from meta data */
  uint32 metaData = PduR_Sm_GetMetaData(info, PduR_GetMetaDataLengthOfSmGDestRom(smGDestRomIdx));       /* SBSW_PDUR_VALID_PTR_ENSURED_BY_CALLING_FUNCTION */
  PduR_MaskOfSmLinearTaToSaCalculationStrategyRomType mask = PduR_GetMaskOfSmLinearTaToSaCalculationStrategyRom(smLinearTaToSaCalculationStrategyIdx);
  PduR_SmTaType targetAdress = metaData & mask;

  /* Check if destination is already known */
  return PduR_Sm_CheckLearned(smDataPlaneIdx, targetAdress, PduR_GetConnectionIdOfSmGDestRom(smGDestRomIdx));
}
#endif

#if (PDUR_SMSATAFROMMETADATACALCULATIONSTRATEGYROM == STD_ON)
/**********************************************************************************************************************
 * PduR_Sm_SrcFilter_SaTaFromMetaDataCalculationStrategy
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_Sm_SrcFilter_SaTaFromMetaDataCalculationStrategy(PduR_SmSrcRomIdxOfRmSrcRomType smSrcRomIdx, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info)
{
  PduR_SmDataPlaneRomIterType smDataPlaneRomIdx = PduR_GetSmDataPlaneRomIdxOfSmSrcRom(smSrcRomIdx);

  /* Get adress info from Pdu */
  uint32 metaData = PduR_Sm_GetMetaData(info, PduR_GetMetaDataLengthOfSmSrcRom(smSrcRomIdx));   /* SBSW_PDUR_VALID_PTR_ENSURED_BY_CALLING_FUNCTION */
  PduR_SmSaType sa = PduR_Sm_SaTaFromMetaDataCalculationStrategy_GetSa(PduR_GetSmSaTaFromMetaDataCalculationStrategyRomIdxOfSmDataPlaneRom(smDataPlaneRomIdx), metaData);

  /* Update FIB */
  PduR_Sm_UpdateFib(smDataPlaneRomIdx, sa, PduR_GetConnectionIdOfSmSrcRom(smSrcRomIdx));
}
#endif

#if (PDUR_SMSATAFROMMETADATACALCULATIONSTRATEGYROM == STD_ON)
/**********************************************************************************************************************
 * PduR_Sm_DestFilter_SaTaFromMetaDataCalculationStrategy
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *********************************************************************************************************************/
FUNC(PduR_FilterReturnType, PDUR_CODE) PduR_Sm_DestFilter_SaTaFromMetaDataCalculationStrategy(PduR_SmGDestRomIdxOfRmGDestRomType smGDestRomIdx, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info)
{
  PduR_SmDataPlaneRomIterType smDataPlaneRomIdx = PduR_GetSmDataPlaneRomIdxOfSmGDestRom(smGDestRomIdx);

  /* Get adress info from Pdu */
  uint32 metaData = PduR_Sm_GetMetaData(info, PduR_GetMetaDataLengthOfSmGDestRom(smGDestRomIdx));       /* SBSW_PDUR_VALID_PTR_ENSURED_BY_CALLING_FUNCTION */
  PduR_SmSaType ta = PduR_Sm_SaTaFromMetaDataCalculationStrategy_GetTa(PduR_GetSmSaTaFromMetaDataCalculationStrategyRomIdxOfSmDataPlaneRom(smDataPlaneRomIdx), metaData);

  /* Check if destination is already known */
  return PduR_Sm_CheckLearned(smDataPlaneRomIdx, ta, PduR_GetConnectionIdOfSmGDestRom(smGDestRomIdx));
}
#endif

#if (PDUR_RPGROM == STD_ON)
/**********************************************************************************************************************
 * PduR_EnableRouting
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_EnableRouting(PduR_RoutingPathGroupIdType id)
{
  uint8 errorId = PDUR_E_NO_ERROR;
  /* ----- Development Error Checks ------------------------------------- */
  /* Check parameter 'Handle Id' */
  if(PduR_IsInitialized() == FALSE)
  {
    errorId = PDUR_E_UNINIT;
  }
# if (PDUR_DEV_ERROR_DETECT == STD_ON)  /* COV_PDUR_VAR_DEV_ERROR_DETECT */
  else if(id >= PduR_GetSizeOfRpgRom())
  {
    errorId = PDUR_E_ROUTING_PATH_GROUP_ID_INVALID;
  }
#  if(PDUR_INVALIDHNDOFRPGROM == STD_ON)
  else if(PduR_IsInvalidHndOfRpgRom(id))
  {
    errorId = PDUR_E_ROUTING_PATH_GROUP_ID_INVALID;
  }
#  endif
# endif
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    SchM_Enter_PduR_PDUR_EXCLUSIVE_AREA_0();    /* PRQA S 3109 */ /* MD_MSR_14.3 */
    {
      if(!PduR_IsEnabledOfRpgRam(id))
      {
        PduR_RmDestRpgRomIndIterType rmDestRpgRomIndIdx;
        for(rmDestRpgRomIndIdx = PduR_GetRmDestRpgRomIndStartIdxOfRpgRom(id); rmDestRpgRomIndIdx < PduR_GetRmDestRpgRomIndEndIdxOfRpgRom(id); rmDestRpgRomIndIdx++)
        {
          PduR_RmDestRpgRomIndType rmDestRpgRomIdx = PduR_GetRmDestRpgRomInd(rmDestRpgRomIndIdx);
          PduR_SetEnabledCntOfRmDestRpgRam(rmDestRpgRomIdx, PduR_GetEnabledCntOfRmDestRpgRam(rmDestRpgRomIdx) + 1);     /* SBSW_PDUR_CSL03 */
        }
        PduR_SetEnabledOfRpgRam(id, TRUE);      /* SBSW_PDUR_CSL01 */
      }
      SchM_Exit_PduR_PDUR_EXCLUSIVE_AREA_0();   /* PRQA S 3109 */ /* MD_MSR_14.3 */
    }
  }
  /* ----- Development Error Report --------------------------------------- */
# if (PDUR_DEV_ERROR_REPORT == STD_ON)
  if(errorId != PDUR_E_NO_ERROR)
  {
    PduR_Det_ReportError(PDUR_FCT_ENABLEROUTING, errorId);
  }
# else
  PDUR_DUMMY_STATEMENT(errorId);        /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
# endif
}       /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif

#if (PDUR_RPGROM == STD_ON)
/**********************************************************************************************************************
 * PduR_DisableRouting
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_DisableRouting(PduR_RoutingPathGroupIdType id)
{
  uint8 errorId = PDUR_E_NO_ERROR;
  /* ----- Development Error Checks ------------------------------------- */
  /* Check parameter 'Handle Id' */
  if(PduR_IsInitialized() == FALSE)
  {
    errorId = PDUR_E_UNINIT;
  }
# if (PDUR_DEV_ERROR_DETECT == STD_ON)  /* COV_PDUR_VAR_DEV_ERROR_DETECT */
  else if(id >= PduR_GetSizeOfRpgRom())
  {
    errorId = PDUR_E_ROUTING_PATH_GROUP_ID_INVALID;
  }
#  if(PDUR_INVALIDHNDOFRPGROM == STD_ON)
  else if(PduR_IsInvalidHndOfRpgRom(id))
  {
    errorId = PDUR_E_ROUTING_PATH_GROUP_ID_INVALID;
  }
#  endif
# endif
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    SchM_Enter_PduR_PDUR_EXCLUSIVE_AREA_0();    /* PRQA S 3109 */ /* MD_MSR_14.3 */
    {
      /** Guard: Routing is disabled **/
      if(PduR_IsEnabledOfRpgRam(id))
      {
        PduR_RmDestRpgRomIndIterType rmDestRpgRomIndIdx;
        for(rmDestRpgRomIndIdx = PduR_GetRmDestRpgRomIndStartIdxOfRpgRom(id); rmDestRpgRomIndIdx < PduR_GetRmDestRpgRomIndEndIdxOfRpgRom(id); rmDestRpgRomIndIdx++)
        {
          PduR_RmDestRpgRomIndType rmDestRpgRomInd = PduR_GetRmDestRpgRomInd(rmDestRpgRomIndIdx);
# if (PDUR_RMDESTROMIFIDXOFRMDESTRPGROM == STD_ON)
          if(PduR_IsRmDestRomIfUsedOfRmDestRpgRom(rmDestRpgRomInd))     /* COV_PDUR_NO_RP_WITH_MIXED_RPG */
          {
            PduR_DisableIfRoutingAction(PduR_GetRmDestRomIfIdxOfRmDestRpgRom(rmDestRpgRomInd));
          }
# endif
# if ((PDUR_RMDESTROMUSEDOFRMDESTRPGROM == STD_ON) && (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON))
          if(PduR_IsRmDestRomUsedOfRmDestRpgRom(rmDestRpgRomInd))
          {
            PduR_RmGDestRomIterType rmGDestRomIdx = PduR_GetRmGDestRomIdxOfRmDestRom(PduR_GetRmDestRomIdxOfRmDestRpgRom(rmDestRpgRomInd));
            PduR_FmFifoRomIterType fmFifoRomIdx = PduR_GetFmFifoRomIdxOfFmFifoInstanceRom(PduR_GetFmFifoInstanceRomIdxOfRmGDestRom(rmGDestRomIdx));
            PduR_FmFifoElementRamIterType fmFifoElementRamTPReadIdx = PduR_GetFmFifoElementRamReadIdxOfFmFifoRam(fmFifoRomIdx);
            PduR_StateOfFmFifoElementRamType fifoSmState = PduR_GetStateOfFmFifoElementRam(fmFifoElementRamTPReadIdx);
            PduR_GetFctPtrOfTpDisableRoutingTxSmTransition(fifoSmState) (rmGDestRomIdx);        /* SBSW_PDUR_CSL03 */
          }
# endif
          PduR_SetEnabledCntOfRmDestRpgRam(rmDestRpgRomInd, (PduR_GetEnabledCntOfRmDestRpgRam(rmDestRpgRomInd) - 1));   /* SBSW_PDUR_CSL03 */
        }
        PduR_SetEnabledOfRpgRam(id, FALSE);     /* SBSW_PDUR_CSL01 */
      }
      SchM_Exit_PduR_PDUR_EXCLUSIVE_AREA_0();   /* PRQA S 3109 */ /* MD_MSR_14.3 */
    }
  }
  /* ----- Development Error Report --------------------------------------- */
# if (PDUR_DEV_ERROR_REPORT == STD_ON)
  if(errorId != PDUR_E_NO_ERROR)
  {
    PduR_Det_ReportError(PDUR_FCT_DISABLEROUTING, errorId);
  }
# else
  PDUR_DUMMY_STATEMENT(errorId);        /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
# endif
}       /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif

#if (PDUR_RMDESTROMIFIDXOFRMDESTRPGROM == STD_ON)
/**********************************************************************************************************************
 * PduR_DisableIfRoutingAction
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_DisableIfRoutingAction(PduR_RmDestRomIfIdxOfRmDestRpgRomType rmDestRomIdx)
{
  PduR_RmGDestRomIterType rmGDestIdx = PduR_GetRmGDestRomIdxOfRmDestRom(rmDestRomIdx);
# if ((PDUR_EXISTS_DIRECT_FIFO_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON) || (PDUR_EXISTS_T_T_FIFO_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON))
  if(PduR_IsFmFifoInstanceRomUsedOfRmGDestRom(rmGDestIdx))      /* COV_PDUR_FEATURE_ALWAYS_TRUE */
  {
    PduR_RmBufferedIfPropertiesRomIdxOfRmGDestRomType rmBufferedIfPropertiesRomIdx = PduR_GetRmBufferedIfPropertiesRomIdxOfRmGDestRom(rmGDestIdx);

    if(PduR_GetFillLevelOfFmFifoRam(PduR_GetFmFifoRomIdxOfFmFifoInstanceRom(PduR_GetFmFifoInstanceRomIdxOfRmGDestRom(rmGDestIdx))) > 0)
    {
      PduR_Fm_FlushFiFo(rmGDestIdx);
    }
    PduR_SetIfSmStateOfRmBufferedIfPropertiesRam(rmBufferedIfPropertiesRomIdx, PduR_GetNextState_For_Init_If_Routing_StateOfIfRoutingStateTable(PduR_GetFifoTypeOfRmBufferedIfPropertiesRom(rmBufferedIfPropertiesRomIdx)));    /* SBSW_PDUR_IDX_PARAM_INTERNAL_FUNCTION */
  }
# endif
# if(PDUR_RMGDESTNTO1INFORAMIDXOFRMGDESTROM == STD_ON)
  PduR_Rm_MultipleSourceHandler_Reset(rmGDestIdx);
# endif
  PDUR_DUMMY_STATEMENT(rmGDestIdx);        /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
}
#endif

#define PDUR_STOP_SEC_CODE
#include "MemMap.h"    /* PRQA S 5087 */        /* MD_MSR_19.1 */

/**********************************************************************************************************************
 * GLOBAL MISRA / PCLINT JUSTIFICATION
 *********************************************************************************************************************/
/* module specific MISRA deviations:

    MD_PduR_3673_AsrProto:
    Reason:     Function prototype is based on AUTOSAR specification. The function prototype which describe the
    interfaces vary between different specifications. No optimization possible.
    Risk:       Unexpected value modification.
    Prevention: Covered by code review.

    MD_PduR_3673_UnexpectedCall:
    Reason:     The function is called unexpectedly and must not do anything. But the function parameter prototype
                must be a pointer to var because the expected functions performes a write access.
    Risk:       Unexpected value modification.
    Prevention: Covered by code review.

    MD_PduR_3673_Abort:
    Reason:     The function is called unexpectedly because the routing is already aborted and must not do anything.
                But the function parameter prototype must be a pointer to var because the expected functions
                performes a write access.
    Risk:       Unexpected value modification.
    Prevention: Covered by code review.

    MD_PduR_0311:
    Reason:     Dangerous pointer cast results in loss of const qualification.
    Risk:       Write operation to ROM
    Prevention: Reviewed the complete code sequence. Only read operations are performed

*/

/* *INDENT-OFF* */
/* SBSW_JUSTIFICATION_BEGIN

  \ID SBSW_PDUR_IDX_PARAM_INTERNAL_FUNCTION
    \DESCRIPTION The index is passed to an internal function as parameter and is used within the function to write to a memory location.
    \COUNTERMEASURE \N The index is read by the calling function using the ComStackLib macros. The ComStackLib ensures that the index is valid.

  \ID SBSW_PDUR_VALID_PTR_ENSURED_BY_CALLING_FUNCTION
    \DESCRIPTION A pointer is written or passed to a function. The pointer can possibly be used to write to the corresponding memory location.
    \COUNTERMEASURE \N The calling function ensures that the pointer is valid.

  \ID SBSW_PDUR_STACK_VARIABLE
    \DESCRIPTION A pointer is passed to a function. The pointer can possibly be used to write to the corresponding memory location.
    \COUNTERMEASURE \N The pointer points to a local stack variable, therefore it's always valid.

  \ID SBSW_PDUR_GETVERSION_PARAM
    \DESCRIPTION    The PduR_GetVersionInfo writes to the 'versioninfo' pointer parameter. It is checked against NULL,
                    but this does not guarantee that the referenced memory is valid.
    \COUNTERMEASURE \N  Pointers passed to public PduR APIs point to a valid memory range. A general countermeasure is included in the safety manual.

  \ID SBSW_PDUR_API_CALL_FORWARDING_ID_AND_PTR
    \DESCRIPTION    The API is called with an Id and a pointer.
                    The API call is forwarded using a function pointer which is read using ComStackLib macros.

    \COUNTERMEASURE \N The function pointer is read using the passed Id and ComStackLib macros.
                       The Id is a SNV provided by the lower layer. It is checked when it was first passed to the PduR module.
                       The pointer is either forwarded and assumed to be valid or it is a local stack variable.

  \ID SBSW_PDUR_API_CALL_FORWARDING_ID_ONLY
    \DESCRIPTION    The API is called with an Id.
                    The API call is forwarded using a function pointer which is read using ComStackLib macros.
    \COUNTERMEASURE \R The function pointer is read using the passed Id and ComStackLib macros.
                       The Id is a SNV provided by the lower layer.
                       It is checked when it was first passed to the PduR module.

  \ID SBSW_PDUR_MEM_CPY_FIFOMGR
    \DESCRIPTION Call to copy RAM data to RAM
    \COUNTERMEASURE \N The passed pointers are either read by ComStackLib macros or are passed through and checked by one of the calling functions.
                       The size of the copy operation is always equal or less than the size of the destination buffer. This is ensured by the calling function.

  \ID SBSW_PDUR_MEM_CPY_RAM2RAM
    \DESCRIPTION Call to copy RAM data to RAM
    \COUNTERMEASURE \R The passed pointers are either read by ComStackLib macros or are passed through and checked by one of the calling functions.
                    \R The size of the copy operation is checked against the remaining free buffer space.

  \ID SBSW_PDUR_WRITE_TRANSMIT_OR_INDICATION_QUEUE
    \DESCRIPTION Data is written into the indication or transmit queue.
    \COUNTERMEASURE \R The passed index will always be within range of the indication or transmit queue as it is caluclated considering the length of the queue.

  \ID SBSW_PDUR_CSL01
    \DESCRIPTION Index Access is using ComStackLib
    \COUNTERMEASURE  \N Qualified use-case CSL01 of ComStackLib.

  \ID SBSW_PDUR_CSL02
    \DESCRIPTION  Access of Table1, via indirection over Table2
                  with same index using ComStackLib.
    \COUNTERMEASURE \N Qualified use-case CSL02 of ComStackLib

  \ID SBSW_PDUR_CSL03
    \DESCRIPTION Access to Table1 via indirection over Table2.
    \COUNTERMEASURE \N Qualified use-case CSL03 of ComStackLib

  \ID SBSW_PDUR_CSL_VAR_ACCESS
    \DESCRIPTION A ComStackLib generated variable is accessed.
    \COUNTERMEASURE \N The variable is written using a generated macro of the CSL. It immediately dereferences the variables address without pointer arithmetic.

  SBSW_JUSTIFICATION_END */

/*
  SBSW_PDUR_CSL01 Boundary check using generated identifiers:
  Table1 -- Size of the table itself

  SBSW_PDUR_CSL02 Arrays of same size:
  Table1 -- SizeRelation --> Table2

  SBSW_PDUR_CSL03: Usage of modelled indirections:
  Table1 -- Key Size Relation --> Table2
*/

/* COV_JUSTIFICATION_BEGIN
  \ID COV_PDUR_FEATURE_ALWAYS_TRUE
    \ACCEPT TX
    \ACCEPT TF tf xf
    \ACCEPT TF tf tf tf xf
    \ACCEPT TF tf tx
    \REASON Depending on the configuration the feature check can always be true. In this case the compiler removes the check.

  \ID COV_PDUR_ONLY_DIRECT_BUFFER
    \ACCEPT TX
    \REASON In configurations with only direct buffers this is always true. Buffer can't run out in the WAIT_FOR_RXINDICATION state as there always will be the shadow buffer.

  \ID COV_PDUR_ONLY_TT_SINGLE_BUFFER
    \ACCEPT XX
    \ACCEPT X
    \REASON The code can't be covered in configurations where only trigger transmit single buffer are used. The buffer is never empty and can't be flushed.

  \ID COV_PDUR_ONLY_DEDICATED_BUFFER
    \ACCEPT TX
    \REASON This configuration has only dedicated buffer and no shared buffer.

  \ID COV_PDUR_ONLY_SHARED_BUFFER
    \ACCEPT XF
    \ACCEPT XX
    \REASON This configuration has only shared buffer and no direct buffer.

  \ID COV_PDUR_NO_RP_WITH_MIXED_RPG
    \ACCEPT TX
    \REASON This condition is always true if only routing paths exist which destinations are assigned to none or the same routing path group.

  \ID COV_PDUR_NO_NTO1_ROUTINGPATHS
    \ACCEPT TX
    \REASON This condition is always true if no N:1 routing paths were configured.

  \ID COV_PDUR_NTO1_GW_ONLY_ROUTINGPATHS
    \ACCEPT TX
    \REASON This condition is always true if there are only N:1 gateway only routing paths configured.

  \ID COV_PDUR_NTO1_NO_BUFFER_GW_ONLY_ROUTINGPATHS
    \ACCEPT XF
    \ACCEPT XX
    \REASON This condition is never true if only no buffer gateway only N:1 routing paths exist.

  \ID COV_PDUR_RPG_FEATURE_CHECK
    \ACCEPT TF xf tf
    \ACCEPT TF tx tf
    \ACCEPT TX tf tx
    \REASON For postbuild configurations the feature has a runtime feature check. For none-postbuild configurations with routing path groups the first condition is always false.

  \ID COV_PDUR_RPG_FWD_CHECK
    \ACCEPT TF xf tf
    \ACCEPT TF tx tf
    \ACCEPT TX xf tx
    \REASON For postbuild configurations the feature has a runtime feature check. For none-postbuild configurations with routing path groups the first condition is always false.
            For gateway only configurations the last condition is always true as this conditions only checks the RPG status of API forwarding routing paths.

  \ID COV_PDUR_CONDITIONAL_DEPENDENCE
    \ACCEPT TF tf tf tx
    \ACCEPT TF tf tx tf
    \REASON The conditions are not independent due to short-circuit evaluation.

  \ID COV_PDUR_MISRA
    \ACCEPT X
    \ACCEPT TX
    \REASON [MSR_COV_MISRA]

  \ID COV_PDUR_IF_SDU_LENGTH_HANDLING
    \ACCEPT TX
    \ACCEPT XF
    \ACCEPT XX
    \REASON  If the provided length is greater than the maximum buffer size the value is truncated to this value. Therefore the code code not be reached in case of communication interface routing.

  \ID COV_PDUR_TX_BUFFER_USED
    \ACCEPT TX
    \REASON This statement could only reach in case of transport protocol routing. In case of a communication interface routing the buffer is always used because each destination has its own buffer.

  \ID COV_PDUR_TP_ONLY
   \ACCEPT X
   \REASON This function is only called in case of transport protocol routing. But it is active because of the Routing manager API are shared between transport protocol and communication interface.

  \ID COV_PDUR_IF_ONLY
   \ACCEPT X
   \ACCEPT XX
   \REASON This function is only called if buffered transport protocol routing paths exist. This is not the case for communication interface only configurations.

  \ID COV_PDUR_BUFFER_CALCULATION
   \ACCEPT X
   \REASON This function is not called in the context of this state. It still exists to have a correct and complete calculation function.

  \ID COV_PDUR_SINGLE_INSTANCE
   \ACCEPT TX
   \ACCEPT TF tf tx
   \REASON This statement could only reach in case of transport protocol routing. In case of a communication interface routing each destination has its own buffer and therefore multi Instance condition could never be fulfilled.

  \ID COV_PDUR_FATAL_ERROR
    \ACCEPT X
    \ACCEPT XF
    \ACCEPT TX
    \ACCEPT TF tx tf
    \REASON Fatal error check.

  \ID COV_PDUR_ROBUSTNESS
    \ACCEPT TF tx tf
    \ACCEPT TX tx tx
    \ACCEPT XF
    \ACCEPT TF tf tx tf
    \REASON This check increases robustness. Under normal circumstances it is never false/true.

  \ID COV_PDUR_DUMMY_FUNCTION
    \ACCEPT X
    \REASON Depending on the configuration the dummy function is not callable in all configuration variants.
            It is just a dummy function with out influencing the control- and data flow.

  \ID COV_PDUR_VAR_FATAL_ERROR
    \ACCEPT TX
    \REASON Fatal error check.

  \ID COV_PDUR_VAR_DEV_ERROR_DETECT
    \ACCEPT TX
    \REASON Det error detection must always be enabled for SafeBsw.

  \ID COV_PDUR_ERROR_NOTIFICATION
    \ACCEPT XF
    \REASON Always false. Feature is not part of SafeBsw.

  \ID COV_PDUR_VAR_DEPENDENT_SWITCH
    \ACCEPT TX
    \ACCEPT TX tx tx
    \REASON The nested switch depends on a previous switch.

  \ID COV_PDUR_VAR_ELISA_STD_OFF_XF
    \ACCEPT XF
    \REASON Feature must always be disabled for SafeBsw secured by the Elisa plugin.

  \ID COV_PDUR_VAR_LINIF_SPECIAL_CONFIGURATION
    \ACCEPT TX
    \REASON This can only be false for LinIf BswModule. Otherwise this Code part is always active if the API is active.

   \ID COV_PDUR_VAR_ELISA_STD_ON_TX
    \ACCEPT TX
    \REASON Feature must always be enabled for SafeBsw secured by the Elisa plugin.

  \ID COV_PDUR_VAR_ELISA_STD_ON_TF_tx_tf_tf_tf
    \ACCEPT  TF tx tf tf tf
    \REASON Feature must always be enabled for SafeBsw secured by the Elisa plugin.

  \ID COV_PDUR_VAR_ELISA_STD_OFF_XF_xf_xf
    \ACCEPT XF xf xf
    \REASON Feature must always be disabled for SafeBsw secured by the Elisa plugin.

  \ID COV_PDUR_VAR_ELISA_STD_ON_TF_tf_tx
    \ACCEPT TF tf tx
    \REASON Feature must always be enabled for SafeBsw secured by the Elisa plugin.

COV_JUSTIFICATION_END */

/* *INDENT-ON* */

/**********************************************************************************************************************
 * END OF FILE: PduR.c
 *********************************************************************************************************************/
