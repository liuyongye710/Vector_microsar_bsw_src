/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *
 *                 This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                 Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                 All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  LICENSE
 *  -------------------------------------------------------------------------------------------------------------------
 *            Module: PduR
 *           Program: MSR_Vector_SLP4
 *          Customer: China FAW Group Corporation
 *       Expiry Date: Not restricted
 *  Ordered Derivat.: TC297TA
 *    License Scope : The usage is restricted to CBD1600956_D02
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *              File: PduR_Lcfg.h
 *   Generation Time: 2020-07-28 16:23:22
 *           Project: FAW_MultiCore297_Demo - Version 1.0
 *          Delivery: CBD1600956_D02
 *      Tool Version: DaVinci Configurator  5.17.51 SP2
 *
 *
 *********************************************************************************************************************/


#if !defined (PDUR_LCFG_H)
# define PDUR_LCFG_H

/**********************************************************************************************************************
 * MISRA JUSTIFICATION
 *********************************************************************************************************************/
/* PRQA S 0857 EOF */ /* MD_MSR_1.1_857 */

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
# include "PduR_Types.h"
# include "PduR_PBcfg.h"


/* include headers with symbolic name values */
/* \trace SPEC-2020167 */

#include "CanIf.h"
#include "Com_Cbk.h"




/**********************************************************************************************************************
 * GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL CONSTANT MACROS
**********************************************************************************************************************/
/** 
  \defgroup  PduRPCDataSwitches  PduR Data Switches  (PRE_COMPILE)
  \brief  These defines are used to deactivate data and their processing.
  \{
*/ 
#define PDUR_BMTXBUFFERARRAYRAM                                       STD_OFF  /**< Deactivateable: 'PduR_BmTxBufferArrayRam' Reason: 'the array is deactivated because the size is 0 in all variants and the piece of data is in the configuration class: PRE_COMPILE' */
#define PDUR_BMTXBUFFERINDROM                                         STD_OFF  /**< Deactivateable: 'PduR_BmTxBufferIndRom' Reason: 'the struct is deactivated because all elements are deactivated.' */
#define PDUR_BMTXBUFFERROMIDXOFBMTXBUFFERINDROM                       STD_OFF  /**< Deactivateable: 'PduR_BmTxBufferIndRom.BmTxBufferRomIdx' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define PDUR_BMTXBUFFERINSTANCERAM                                    STD_OFF  /**< Deactivateable: 'PduR_BmTxBufferInstanceRam' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define PDUR_BMTXBUFFERARRAYRAMREADIDXOFBMTXBUFFERINSTANCERAM         STD_OFF  /**< Deactivateable: 'PduR_BmTxBufferInstanceRam.BmTxBufferArrayRamReadIdx' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define PDUR_BMTXBUFFERARRAYRAMWRITEIDXOFBMTXBUFFERINSTANCERAM        STD_OFF  /**< Deactivateable: 'PduR_BmTxBufferInstanceRam.BmTxBufferArrayRamWriteIdx' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define PDUR_PDURBUFFERSTATEOFBMTXBUFFERINSTANCERAM                   STD_OFF  /**< Deactivateable: 'PduR_BmTxBufferInstanceRam.PduRBufferState' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define PDUR_TXBUFFERUSEDOFBMTXBUFFERINSTANCERAM                      STD_OFF  /**< Deactivateable: 'PduR_BmTxBufferInstanceRam.TxBufferUsed' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define PDUR_BMTXBUFFERINSTANCEROM                                    STD_OFF  /**< Deactivateable: 'PduR_BmTxBufferInstanceRom' Reason: 'the struct is deactivated because all elements are deactivated.' */
#define PDUR_BMTXBUFFERROMIDXOFBMTXBUFFERINSTANCEROM                  STD_OFF  /**< Deactivateable: 'PduR_BmTxBufferInstanceRom.BmTxBufferRomIdx' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define PDUR_BMTXBUFFERRAM                                            STD_OFF  /**< Deactivateable: 'PduR_BmTxBufferRam' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define PDUR_BMTXBUFFERARRAYRAMINSTANCESTOPIDXOFBMTXBUFFERRAM         STD_OFF  /**< Deactivateable: 'PduR_BmTxBufferRam.BmTxBufferArrayRamInstanceStopIdx' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define PDUR_BMTXBUFFERARRAYRAMREADIDXOFBMTXBUFFERRAM                 STD_OFF  /**< Deactivateable: 'PduR_BmTxBufferRam.BmTxBufferArrayRamReadIdx' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define PDUR_BMTXBUFFERARRAYRAMWRITEIDXOFBMTXBUFFERRAM                STD_OFF  /**< Deactivateable: 'PduR_BmTxBufferRam.BmTxBufferArrayRamWriteIdx' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define PDUR_PDURBUFFERSTATEOFBMTXBUFFERRAM                           STD_OFF  /**< Deactivateable: 'PduR_BmTxBufferRam.PduRBufferState' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define PDUR_RXLENGTHOFBMTXBUFFERRAM                                  STD_OFF  /**< Deactivateable: 'PduR_BmTxBufferRam.RxLength' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define PDUR_TPBUFMGRSTATEOFBMTXBUFFERRAM                             STD_OFF  /**< Deactivateable: 'PduR_BmTxBufferRam.TpBufMgrState' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define PDUR_BMTXBUFFERROM                                            STD_OFF  /**< Deactivateable: 'PduR_BmTxBufferRom' Reason: 'the struct is deactivated because all elements are deactivated.' */
#define PDUR_BMTXBUFFERARRAYRAMENDIDXOFBMTXBUFFERROM                  STD_OFF  /**< Deactivateable: 'PduR_BmTxBufferRom.BmTxBufferArrayRamEndIdx' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define PDUR_BMTXBUFFERARRAYRAMLENGTHOFBMTXBUFFERROM                  STD_OFF  /**< Deactivateable: 'PduR_BmTxBufferRom.BmTxBufferArrayRamLength' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define PDUR_BMTXBUFFERARRAYRAMSTARTIDXOFBMTXBUFFERROM                STD_OFF  /**< Deactivateable: 'PduR_BmTxBufferRom.BmTxBufferArrayRamStartIdx' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define PDUR_BMTXBUFFERINSTANCEROMENDIDXOFBMTXBUFFERROM               STD_OFF  /**< Deactivateable: 'PduR_BmTxBufferRom.BmTxBufferInstanceRomEndIdx' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define PDUR_BMTXBUFFERINSTANCEROMSTARTIDXOFBMTXBUFFERROM             STD_OFF  /**< Deactivateable: 'PduR_BmTxBufferRom.BmTxBufferInstanceRomStartIdx' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define PDUR_CONFIGID                                                 STD_ON
#define PDUR_COPYRXDATARXSMTRANSITION                                 STD_OFF  /**< Deactivateable: 'PduR_CopyRxDataRxSmTransition' Reason: 'the struct is deactivated because all elements are deactivated.' */
#define PDUR_FCTPTROFCOPYRXDATARXSMTRANSITION                         STD_OFF  /**< Deactivateable: 'PduR_CopyRxDataRxSmTransition.FctPtr' Reason: 'No transport protocol PduRBswModule configured. Evaluated DefinitionRef: /MICROSAR/PduR/PduRBswModules/PduRTransportProtocol' */
#define PDUR_COPYTXDATATXINSTSMTRANSITION                             STD_OFF  /**< Deactivateable: 'PduR_CopyTxDataTxInstSmTransition' Reason: 'the struct is deactivated because all elements are deactivated.' */
#define PDUR_FCTPTROFCOPYTXDATATXINSTSMTRANSITION                     STD_OFF  /**< Deactivateable: 'PduR_CopyTxDataTxInstSmTransition.FctPtr' Reason: 'No transport protocol PduRBswModule configured. Evaluated DefinitionRef: /MICROSAR/PduR/PduRBswModules/PduRTransportProtocol' */
#define PDUR_FIFOINITVALUES                                           STD_OFF  /**< Deactivateable: 'PduR_FiFoInitValues' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define PDUR_FINALMAGICNUMBER                                         STD_OFF  /**< Deactivateable: 'PduR_FinalMagicNumber' Reason: 'the module configuration does not support flashing of data.' */
#define PDUR_FINISHREADFMSMTRANSITION                                 STD_OFF  /**< Deactivateable: 'PduR_FinishReadFmSmTransition' Reason: 'the struct is deactivated because all elements are deactivated.' */
#define PDUR_FCTPTROFFINISHREADFMSMTRANSITION                         STD_OFF  /**< Deactivateable: 'PduR_FinishReadFmSmTransition.FctPtr' Reason: 'No queued Routing Paths available' */
#define PDUR_FINISHRECEPTIONRMSMTRANSITION                            STD_OFF  /**< Deactivateable: 'PduR_FinishReceptionRmSmTransition' Reason: 'the struct is deactivated because all elements are deactivated.' */
#define PDUR_FCTPTROFFINISHRECEPTIONRMSMTRANSITION                    STD_OFF  /**< Deactivateable: 'PduR_FinishReceptionRmSmTransition.FctPtr' Reason: 'No transport protocol PduRBswModule configured. Evaluated DefinitionRef: /MICROSAR/PduR/PduRBswModules/PduRTransportProtocol' */
#define PDUR_FINISHTRANSMISSIONRMSMTRANSITION                         STD_OFF  /**< Deactivateable: 'PduR_FinishTransmissionRmSmTransition' Reason: 'the struct is deactivated because all elements are deactivated.' */
#define PDUR_FCTPTROFFINISHTRANSMISSIONRMSMTRANSITION                 STD_OFF  /**< Deactivateable: 'PduR_FinishTransmissionRmSmTransition.FctPtr' Reason: 'No transport protocol PduRBswModule configured. Evaluated DefinitionRef: /MICROSAR/PduR/PduRBswModules/PduRTransportProtocol' */
#define PDUR_FINISHWRITEFMSMTRANSITION                                STD_OFF  /**< Deactivateable: 'PduR_FinishWriteFmSmTransition' Reason: 'the struct is deactivated because all elements are deactivated.' */
#define PDUR_FCTPTROFFINISHWRITEFMSMTRANSITION                        STD_OFF  /**< Deactivateable: 'PduR_FinishWriteFmSmTransition.FctPtr' Reason: 'No queued Routing Paths available' */
#define PDUR_FMFIFOELEMENTRAM                                         STD_OFF  /**< Deactivateable: 'PduR_FmFifoElementRam' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define PDUR_BMTXBUFFERROMIDXOFFMFIFOELEMENTRAM                       STD_OFF  /**< Deactivateable: 'PduR_FmFifoElementRam.BmTxBufferRomIdx' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define PDUR_DEDICATEDTXBUFFEROFFMFIFOELEMENTRAM                      STD_OFF  /**< Deactivateable: 'PduR_FmFifoElementRam.DedicatedTxBuffer' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define PDUR_RMDESTROMIDXOFFMFIFOELEMENTRAM                           STD_OFF  /**< Deactivateable: 'PduR_FmFifoElementRam.RmDestRomIdx' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define PDUR_STATEOFFMFIFOELEMENTRAM                                  STD_OFF  /**< Deactivateable: 'PduR_FmFifoElementRam.State' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define PDUR_FMFIFOINSTANCERAM                                        STD_OFF  /**< Deactivateable: 'PduR_FmFifoInstanceRam' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define PDUR_BMTXBUFFERINSTANCEROMIDXOFFMFIFOINSTANCERAM              STD_OFF  /**< Deactivateable: 'PduR_FmFifoInstanceRam.BmTxBufferInstanceRomIdx' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define PDUR_FMFIFOINSTANCEROM                                        STD_OFF  /**< Deactivateable: 'PduR_FmFifoInstanceRom' Reason: 'the struct is deactivated because all elements are deactivated.' */
#define PDUR_FMFIFOROMIDXOFFMFIFOINSTANCEROM                          STD_OFF  /**< Deactivateable: 'PduR_FmFifoInstanceRom.FmFifoRomIdx' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define PDUR_FMFIFORAM                                                STD_OFF  /**< Deactivateable: 'PduR_FmFifoRam' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define PDUR_FILLLEVELOFFMFIFORAM                                     STD_OFF  /**< Deactivateable: 'PduR_FmFifoRam.FillLevel' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define PDUR_FMFIFOELEMENTRAMREADIDXOFFMFIFORAM                       STD_OFF  /**< Deactivateable: 'PduR_FmFifoRam.FmFifoElementRamReadIdx' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define PDUR_FMFIFOELEMENTRAMWRITEIDXOFFMFIFORAM                      STD_OFF  /**< Deactivateable: 'PduR_FmFifoRam.FmFifoElementRamWriteIdx' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define PDUR_PENDINGCONFIRMATIONSOFFMFIFORAM                          STD_OFF  /**< Deactivateable: 'PduR_FmFifoRam.PendingConfirmations' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define PDUR_TPTXSMSTATEOFFMFIFORAM                                   STD_OFF  /**< Deactivateable: 'PduR_FmFifoRam.TpTxSmState' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define PDUR_FMFIFOROM                                                STD_OFF  /**< Deactivateable: 'PduR_FmFifoRom' Reason: 'the struct is deactivated because all elements are deactivated.' */
#define PDUR_FMFIFOELEMENTRAMENDIDXOFFMFIFOROM                        STD_OFF  /**< Deactivateable: 'PduR_FmFifoRom.FmFifoElementRamEndIdx' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define PDUR_FMFIFOELEMENTRAMLENGTHOFFMFIFOROM                        STD_OFF  /**< Deactivateable: 'PduR_FmFifoRom.FmFifoElementRamLength' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define PDUR_FMFIFOELEMENTRAMSTARTIDXOFFMFIFOROM                      STD_OFF  /**< Deactivateable: 'PduR_FmFifoRom.FmFifoElementRamStartIdx' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define PDUR_FMFLUSHFIFOELEMENT                                       STD_OFF  /**< Deactivateable: 'PduR_FmFlushFifoElement' Reason: 'the struct is deactivated because all elements are deactivated.' */
#define PDUR_FCTPTROFFMFLUSHFIFOELEMENT                               STD_OFF  /**< Deactivateable: 'PduR_FmFlushFifoElement.FctPtr' Reason: 'No queued IF Gateway Routing Paths available' */
#define PDUR_IFROUTINGSTATETABLE                                      STD_ON
#define PDUR_NEXTSTATE_FOR_INIT_IF_ROUTING_STATEOFIFROUTINGSTATETABLE STD_ON
#define PDUR_NEXTSTATE_FOR_WAIT_FOR_RXINDICATIONOFIFROUTINGSTATETABLE STD_ON
#define PDUR_NEXTSTATE_FOR_WAIT_FOR_TRIGGERTRANSMITOFIFROUTINGSTATETABLE STD_ON
#define PDUR_NEXTSTATE_FOR_WAIT_FOR_TXCONFIRMATIONOFIFROUTINGSTATETABLE STD_ON
#define PDUR_INITDATAHASHCODE                                         STD_OFF  /**< Deactivateable: 'PduR_InitDataHashCode' Reason: 'the module configuration does not support flashing of data.' */
#define PDUR_INITIALIZED                                              STD_ON
#define PDUR_MMROM                                                    STD_ON
#define PDUR_CANCELRECEIVESUPPORTEDOFMMROM                            STD_OFF  /**< Deactivateable: 'PduR_MmRom.CancelReceiveSupported' Reason: 'the value of PduR_CancelReceiveSupportedOfMmRom is always 'false' due to this, the array is deactivated.' */
#define PDUR_CHANGEPARAMETERSUPPORTEDOFMMROM                          STD_OFF  /**< Deactivateable: 'PduR_MmRom.ChangeParameterSupported' Reason: 'the value of PduR_ChangeParameterSupportedOfMmRom is always 'false' due to this, the array is deactivated.' */
#define PDUR_IFCANCELTRANSMITSUPPORTEDOFMMROM                         STD_OFF  /**< Deactivateable: 'PduR_MmRom.IfCancelTransmitSupported' Reason: 'the value of PduR_IfCancelTransmitSupportedOfMmRom is always 'false' due to this, the array is deactivated.' */
#define PDUR_LOIFCANCELTRANSMITFCTPTROFMMROM                          STD_OFF  /**< Deactivateable: 'PduR_MmRom.LoIfCancelTransmitFctPtr' Reason: 'the value of PduR_LoIfCancelTransmitFctPtrOfMmRom is always 'NULL_PTR' due to this, the array is deactivated.' */
#define PDUR_LOIFOFMMROM                                              STD_ON
#define PDUR_LOIFTRANSMITFCTPTROFMMROM                                STD_ON
#define PDUR_LOTPCANCELRECEIVEFCTPTROFMMROM                           STD_OFF  /**< Deactivateable: 'PduR_MmRom.LoTpCancelReceiveFctPtr' Reason: 'the value of PduR_LoTpCancelReceiveFctPtrOfMmRom is always 'NULL_PTR' due to this, the array is deactivated.' */
#define PDUR_LOTPCANCELTRANSMITFCTPTROFMMROM                          STD_OFF  /**< Deactivateable: 'PduR_MmRom.LoTpCancelTransmitFctPtr' Reason: 'the value of PduR_LoTpCancelTransmitFctPtrOfMmRom is always 'NULL_PTR' due to this, the array is deactivated.' */
#define PDUR_LOTPCHANGEPARAMETERFCTPTROFMMROM                         STD_OFF  /**< Deactivateable: 'PduR_MmRom.LoTpChangeParameterFctPtr' Reason: 'the value of PduR_LoTpChangeParameterFctPtrOfMmRom is always 'NULL_PTR' due to this, the array is deactivated.' */
#define PDUR_LOTPOFMMROM                                              STD_OFF  /**< Deactivateable: 'PduR_MmRom.LoTp' Reason: 'the value of PduR_LoTpOfMmRom is always 'false' due to this, the array is deactivated.' */
#define PDUR_LOTPTRANSMITFCTPTROFMMROM                                STD_OFF  /**< Deactivateable: 'PduR_MmRom.LoTpTransmitFctPtr' Reason: 'the value of PduR_LoTpTransmitFctPtrOfMmRom is always 'NULL_PTR' due to this, the array is deactivated.' */
#define PDUR_MASKEDBITSOFMMROM                                        STD_ON
#define PDUR_TPCANCELTRANSMITSUPPORTEDOFMMROM                         STD_OFF  /**< Deactivateable: 'PduR_MmRom.TpCancelTransmitSupported' Reason: 'the value of PduR_TpCancelTransmitSupportedOfMmRom is always 'false' due to this, the array is deactivated.' */
#define PDUR_UPIFOFMMROM                                              STD_ON
#define PDUR_UPIFRXINDICATIONFCTPTROFMMROM                            STD_ON
#define PDUR_UPIFTRIGGERTRANSMITFCTPTROFMMROM                         STD_OFF  /**< Deactivateable: 'PduR_MmRom.UpIfTriggerTransmitFctPtr' Reason: 'the value of PduR_UpIfTriggerTransmitFctPtrOfMmRom is always 'NULL_PTR' due to this, the array is deactivated.' */
#define PDUR_UPIFTXCONFIRMATIONFCTPTROFMMROM                          STD_OFF  /**< Deactivateable: 'PduR_MmRom.UpIfTxConfirmationFctPtr' Reason: 'the value of PduR_UpIfTxConfirmationFctPtrOfMmRom is always 'NULL_PTR' due to this, the array is deactivated.' */
#define PDUR_UPTPCOPYRXDATAFCTPTROFMMROM                              STD_OFF  /**< Deactivateable: 'PduR_MmRom.UpTpCopyRxDataFctPtr' Reason: 'the value of PduR_UpTpCopyRxDataFctPtrOfMmRom is always 'NULL_PTR' due to this, the array is deactivated.' */
#define PDUR_UPTPCOPYTXDATAFCTPTROFMMROM                              STD_OFF  /**< Deactivateable: 'PduR_MmRom.UpTpCopyTxDataFctPtr' Reason: 'the value of PduR_UpTpCopyTxDataFctPtrOfMmRom is always 'NULL_PTR' due to this, the array is deactivated.' */
#define PDUR_UPTPOFMMROM                                              STD_OFF  /**< Deactivateable: 'PduR_MmRom.UpTp' Reason: 'the value of PduR_UpTpOfMmRom is always 'false' due to this, the array is deactivated.' */
#define PDUR_UPTPSTARTOFRECEPTIONFCTPTROFMMROM                        STD_OFF  /**< Deactivateable: 'PduR_MmRom.UpTpStartOfReceptionFctPtr' Reason: 'the value of PduR_UpTpStartOfReceptionFctPtrOfMmRom is always 'NULL_PTR' due to this, the array is deactivated.' */
#define PDUR_UPTPTPRXINDICATIONFCTPTROFMMROM                          STD_OFF  /**< Deactivateable: 'PduR_MmRom.UpTpTpRxIndicationFctPtr' Reason: 'the value of PduR_UpTpTpRxIndicationFctPtrOfMmRom is always 'NULL_PTR' due to this, the array is deactivated.' */
#define PDUR_UPTPTPTXCONFIRMATIONFCTPTROFMMROM                        STD_OFF  /**< Deactivateable: 'PduR_MmRom.UpTpTpTxConfirmationFctPtr' Reason: 'the value of PduR_UpTpTpTxConfirmationFctPtrOfMmRom is always 'NULL_PTR' due to this, the array is deactivated.' */
#define PDUR_RECEPTIONINDICATIONQUEUE                                 STD_OFF  /**< Deactivateable: 'PduR_ReceptionIndicationQueue' Reason: '/ActiveEcuC/PduR/PduRGeneral[0:PduREnableDeferredReception] is configured to 'false'' */
#define PDUR_RMGDESTROMIDXOFRECEPTIONINDICATIONQUEUE                  STD_OFF  /**< Deactivateable: 'PduR_ReceptionIndicationQueue.RmGDestRomIdx' Reason: '/ActiveEcuC/PduR/PduRGeneral[0:PduREnableDeferredReception] is configured to 'false'' */
#define PDUR_RECEPTIONINDICATIONQUEUEREADIDX                          STD_OFF  /**< Deactivateable: 'PduR_ReceptionIndicationQueueReadIdx' Reason: 'All indirection targets are deactivated in all variants.' */
#define PDUR_RECEPTIONINDICATIONQUEUEWRITEIDX                         STD_OFF  /**< Deactivateable: 'PduR_ReceptionIndicationQueueWriteIdx' Reason: 'All indirection targets are deactivated in all variants.' */
#define PDUR_RMBUFFEREDIFPROPERTIESRAM                                STD_OFF  /**< Deactivateable: 'PduR_RmBufferedIfPropertiesRam' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define PDUR_IFSMSTATEOFRMBUFFEREDIFPROPERTIESRAM                     STD_OFF  /**< Deactivateable: 'PduR_RmBufferedIfPropertiesRam.IfSmState' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define PDUR_RMBUFFEREDIFPROPERTIESROM                                STD_OFF  /**< Deactivateable: 'PduR_RmBufferedIfPropertiesRom' Reason: 'the struct is deactivated because all elements are deactivated.' */
#define PDUR_BMTXBUFFERINDROMENDIDXOFRMBUFFEREDIFPROPERTIESROM        STD_OFF  /**< Deactivateable: 'PduR_RmBufferedIfPropertiesRom.BmTxBufferIndRomEndIdx' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define PDUR_BMTXBUFFERINDROMLENGTHOFRMBUFFEREDIFPROPERTIESROM        STD_OFF  /**< Deactivateable: 'PduR_RmBufferedIfPropertiesRom.BmTxBufferIndRomLength' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define PDUR_BMTXBUFFERINDROMSTARTIDXOFRMBUFFEREDIFPROPERTIESROM      STD_OFF  /**< Deactivateable: 'PduR_RmBufferedIfPropertiesRom.BmTxBufferIndRomStartIdx' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define PDUR_DEDICATEDTXBUFFEROFRMBUFFEREDIFPROPERTIESROM             STD_OFF  /**< Deactivateable: 'PduR_RmBufferedIfPropertiesRom.DedicatedTxBuffer' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define PDUR_FIFOINITVALUESENDIDXOFRMBUFFEREDIFPROPERTIESROM          STD_OFF  /**< Deactivateable: 'PduR_RmBufferedIfPropertiesRom.FiFoInitValuesEndIdx' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define PDUR_FIFOINITVALUESLENGTHOFRMBUFFEREDIFPROPERTIESROM          STD_OFF  /**< Deactivateable: 'PduR_RmBufferedIfPropertiesRom.FiFoInitValuesLength' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define PDUR_FIFOINITVALUESSTARTIDXOFRMBUFFEREDIFPROPERTIESROM        STD_OFF  /**< Deactivateable: 'PduR_RmBufferedIfPropertiesRom.FiFoInitValuesStartIdx' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define PDUR_FIFOINITVALUESUSEDOFRMBUFFEREDIFPROPERTIESROM            STD_OFF  /**< Deactivateable: 'PduR_RmBufferedIfPropertiesRom.FiFoInitValuesUsed' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define PDUR_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM                      STD_OFF  /**< Deactivateable: 'PduR_RmBufferedIfPropertiesRom.FifoType' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define PDUR_MAXPDULENGTHOFRMBUFFEREDIFPROPERTIESROM                  STD_OFF  /**< Deactivateable: 'PduR_RmBufferedIfPropertiesRom.MaxPduLength' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define PDUR_RMBUFFEREDTPPROPERTIESRAM                                STD_OFF  /**< Deactivateable: 'PduR_RmBufferedTpPropertiesRam' Reason: 'No TransportProtocol BswModule active.' */
#define PDUR_FMFIFOELEMENTRAMIDXOFRMBUFFEREDTPPROPERTIESRAM           STD_OFF  /**< Deactivateable: 'PduR_RmBufferedTpPropertiesRam.FmFifoElementRamIdx' Reason: 'No TransportProtocol BswModule active.' */
#define PDUR_TPRXSMSTATEOFRMBUFFEREDTPPROPERTIESRAM                   STD_OFF  /**< Deactivateable: 'PduR_RmBufferedTpPropertiesRam.TpRxSmState' Reason: 'No TransportProtocol BswModule active.' */
#define PDUR_RMBUFFEREDTPPROPERTIESROM                                STD_OFF  /**< Deactivateable: 'PduR_RmBufferedTpPropertiesRom' Reason: 'No TransportProtocol BswModule active.' */
#define PDUR_BMTXBUFFERINDROMENDIDXOFRMBUFFEREDTPPROPERTIESROM        STD_OFF  /**< Deactivateable: 'PduR_RmBufferedTpPropertiesRom.BmTxBufferIndRomEndIdx' Reason: 'No TransportProtocol BswModule active.' */
#define PDUR_BMTXBUFFERINDROMLENGTHOFRMBUFFEREDTPPROPERTIESROM        STD_OFF  /**< Deactivateable: 'PduR_RmBufferedTpPropertiesRom.BmTxBufferIndRomLength' Reason: 'No TransportProtocol BswModule active.' */
#define PDUR_BMTXBUFFERINDROMSTARTIDXOFRMBUFFEREDTPPROPERTIESROM      STD_OFF  /**< Deactivateable: 'PduR_RmBufferedTpPropertiesRom.BmTxBufferIndRomStartIdx' Reason: 'No TransportProtocol BswModule active.' */
#define PDUR_DEDICATEDTXBUFFEROFRMBUFFEREDTPPROPERTIESROM             STD_OFF  /**< Deactivateable: 'PduR_RmBufferedTpPropertiesRom.DedicatedTxBuffer' Reason: 'No TransportProtocol BswModule active.' */
#define PDUR_FMFIFOROMIDXOFRMBUFFEREDTPPROPERTIESROM                  STD_OFF  /**< Deactivateable: 'PduR_RmBufferedTpPropertiesRom.FmFifoRomIdx' Reason: 'No TransportProtocol BswModule active.' */
#define PDUR_METADATALENGTHOFRMBUFFEREDTPPROPERTIESROM                STD_OFF  /**< Deactivateable: 'PduR_RmBufferedTpPropertiesRom.MetaDataLength' Reason: 'No TransportProtocol BswModule active.' */
#define PDUR_METADATALENGTHUSEDOFRMBUFFEREDTPPROPERTIESROM            STD_OFF  /**< Deactivateable: 'PduR_RmBufferedTpPropertiesRom.MetaDataLengthUsed' Reason: 'No TransportProtocol BswModule active.' */
#define PDUR_TPTHRESHOLDOFRMBUFFEREDTPPROPERTIESROM                   STD_OFF  /**< Deactivateable: 'PduR_RmBufferedTpPropertiesRom.TpThreshold' Reason: 'No TransportProtocol BswModule active.' */
#define PDUR_RMDESTROM                                                STD_ON
#define PDUR_DIRECTIONOFRMDESTROM                                     STD_ON
#define PDUR_PDULENGTHHANDLINGSTRATEGYOFRMDESTROM                     STD_OFF  /**< Deactivateable: 'PduR_RmDestRom.PduLengthHandlingStrategy' Reason: 'the value of PduR_PduLengthHandlingStrategyOfRmDestRom is always '0' due to this, the array is deactivated.' */
#define PDUR_RMDESTRPGROMIDXOFRMDESTROM                               STD_OFF  /**< Deactivateable: 'PduR_RmDestRom.RmDestRpgRomIdx' Reason: 'the optional indirection is deactivated because RmDestRpgRomUsedOfRmDestRom is always 'FALSE' and the target of the indirection is of the Configuration Class 'PRE_COMPILE'.' */
#define PDUR_RMDESTRPGROMUSEDOFRMDESTROM                              STD_OFF  /**< Deactivateable: 'PduR_RmDestRom.RmDestRpgRomUsed' Reason: 'the optional indirection is deactivated because RmDestRpgRomUsedOfRmDestRom is always 'FALSE' and the target of the indirection is of the Configuration Class 'PRE_COMPILE'.' */
#define PDUR_RMGDESTROMIDXOFRMDESTROM                                 STD_ON
#define PDUR_RMSRCROMIDXOFRMDESTROM                                   STD_ON
#define PDUR_ROUTINGTYPEOFRMDESTROM                                   STD_ON
#define PDUR_RMDESTRPGRAM                                             STD_OFF  /**< Deactivateable: 'PduR_RmDestRpgRam' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define PDUR_ENABLEDCNTOFRMDESTRPGRAM                                 STD_OFF  /**< Deactivateable: 'PduR_RmDestRpgRam.EnabledCnt' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define PDUR_RMDESTRPGROM                                             STD_OFF  /**< Deactivateable: 'PduR_RmDestRpgRom' Reason: 'the struct is deactivated because all elements are deactivated.' */
#define PDUR_INITIALENABLEDCNTOFRMDESTRPGROM                          STD_OFF  /**< Deactivateable: 'PduR_RmDestRpgRom.InitialEnabledCnt' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define PDUR_RMDESTROMIDXOFRMDESTRPGROM                               STD_OFF  /**< Deactivateable: 'PduR_RmDestRpgRom.RmDestRomIdx' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define PDUR_RMDESTROMIFIDXOFRMDESTRPGROM                             STD_OFF  /**< Deactivateable: 'PduR_RmDestRpgRom.RmDestRomIfIdx' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define PDUR_RMDESTROMIFUSEDOFRMDESTRPGROM                            STD_OFF  /**< Deactivateable: 'PduR_RmDestRpgRom.RmDestRomIfUsed' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define PDUR_RMDESTROMUSEDOFRMDESTRPGROM                              STD_OFF  /**< Deactivateable: 'PduR_RmDestRpgRom.RmDestRomUsed' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define PDUR_RMDESTRPGROMIND                                          STD_OFF  /**< Deactivateable: 'PduR_RmDestRpgRomInd' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define PDUR_RMGDESTNTO1INFORAM                                       STD_OFF  /**< Deactivateable: 'PduR_RmGDestNto1InfoRam' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define PDUR_RMDESTROMIDXOFRMGDESTNTO1INFORAM                         STD_OFF  /**< Deactivateable: 'PduR_RmGDestNto1InfoRam.RmDestRomIdx' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define PDUR_TRANSMISSIONACTIVEOFRMGDESTNTO1INFORAM                   STD_OFF  /**< Deactivateable: 'PduR_RmGDestNto1InfoRam.TransmissionActive' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define PDUR_RMGDESTROM                                               STD_ON
#define PDUR_DESTHNDOFRMGDESTROM                                      STD_ON
#define PDUR_FMFIFOINSTANCEROMIDXOFRMGDESTROM                         STD_OFF  /**< Deactivateable: 'PduR_RmGDestRom.FmFifoInstanceRomIdx' Reason: 'the optional indirection is deactivated because FmFifoInstanceRomUsedOfRmGDestRom is always 'FALSE' and the target of the indirection is of the Configuration Class 'PRE_COMPILE'.' */
#define PDUR_FMFIFOINSTANCEROMUSEDOFRMGDESTROM                        STD_OFF  /**< Deactivateable: 'PduR_RmGDestRom.FmFifoInstanceRomUsed' Reason: 'the optional indirection is deactivated because FmFifoInstanceRomUsedOfRmGDestRom is always 'FALSE' and the target of the indirection is of the Configuration Class 'PRE_COMPILE'.' */
#define PDUR_MMROMIDXOFRMGDESTROM                                     STD_ON
#define PDUR_PDURDESTPDUPROCESSINGOFRMGDESTROM                        STD_ON
#define PDUR_RMBUFFEREDIFPROPERTIESROMIDXOFRMGDESTROM                 STD_OFF  /**< Deactivateable: 'PduR_RmGDestRom.RmBufferedIfPropertiesRomIdx' Reason: 'the optional indirection is deactivated because RmBufferedIfPropertiesRomUsedOfRmGDestRom is always 'FALSE' and the target of the indirection is of the Configuration Class 'PRE_COMPILE'.' */
#define PDUR_RMBUFFEREDIFPROPERTIESROMUSEDOFRMGDESTROM                STD_OFF  /**< Deactivateable: 'PduR_RmGDestRom.RmBufferedIfPropertiesRomUsed' Reason: 'the optional indirection is deactivated because RmBufferedIfPropertiesRomUsedOfRmGDestRom is always 'FALSE' and the target of the indirection is of the Configuration Class 'PRE_COMPILE'.' */
#define PDUR_RMDESTROMIDXOFRMGDESTROM                                 STD_ON
#define PDUR_RMDESTROMUSEDOFRMGDESTROM                                STD_ON
#define PDUR_RMGDESTNTO1INFORAMIDXOFRMGDESTROM                        STD_OFF  /**< Deactivateable: 'PduR_RmGDestRom.RmGDestNto1InfoRamIdx' Reason: 'the optional indirection is deactivated because RmGDestNto1InfoRamUsedOfRmGDestRom is always 'FALSE' and the target of the indirection is of the Configuration Class 'PRE_COMPILE'.' */
#define PDUR_RMGDESTNTO1INFORAMUSEDOFRMGDESTROM                       STD_OFF  /**< Deactivateable: 'PduR_RmGDestRom.RmGDestNto1InfoRamUsed' Reason: 'the optional indirection is deactivated because RmGDestNto1InfoRamUsedOfRmGDestRom is always 'FALSE' and the target of the indirection is of the Configuration Class 'PRE_COMPILE'.' */
#define PDUR_RMGDESTTPTXSTATERAMIDXOFRMGDESTROM                       STD_OFF  /**< Deactivateable: 'PduR_RmGDestRom.RmGDestTpTxStateRamIdx' Reason: 'No TransportProtocol BswModule active.' */
#define PDUR_RMGDESTTPTXSTATERAMUSEDOFRMGDESTROM                      STD_OFF  /**< Deactivateable: 'PduR_RmGDestRom.RmGDestTpTxStateRamUsed' Reason: 'No TransportProtocol BswModule active.' */
#define PDUR_SMGDESTROMIDXOFRMGDESTROM                                STD_OFF  /**< Deactivateable: 'PduR_RmGDestRom.SmGDestRomIdx' Reason: '/ActiveEcuC/PduR/PduRGeneral[0:PduRSwitching] is configured to 'false'' */
#define PDUR_SMGDESTROMUSEDOFRMGDESTROM                               STD_OFF  /**< Deactivateable: 'PduR_RmGDestRom.SmGDestRomUsed' Reason: '/ActiveEcuC/PduR/PduRGeneral[0:PduRSwitching] is configured to 'false'' */
#define PDUR_RMGDESTTPTXSTATERAM                                      STD_OFF  /**< Deactivateable: 'PduR_RmGDestTpTxStateRam' Reason: 'No TransportProtocol BswModule active.' */
#define PDUR_TPTXINSTSMSTATEOFRMGDESTTPTXSTATERAM                     STD_OFF  /**< Deactivateable: 'PduR_RmGDestTpTxStateRam.TpTxInstSmState' Reason: 'No TransportProtocol BswModule active.' */
#define PDUR_RMSRCROM                                                 STD_ON
#define PDUR_MMROMIDXOFRMSRCROM                                       STD_ON
#define PDUR_RMBUFFEREDTPPROPERTIESROMIDXOFRMSRCROM                   STD_OFF  /**< Deactivateable: 'PduR_RmSrcRom.RmBufferedTpPropertiesRomIdx' Reason: 'No TransportProtocol BswModule active.' */
#define PDUR_RMBUFFEREDTPPROPERTIESROMUSEDOFRMSRCROM                  STD_OFF  /**< Deactivateable: 'PduR_RmSrcRom.RmBufferedTpPropertiesRomUsed' Reason: 'No TransportProtocol BswModule active.' */
#define PDUR_RMDESTROMENDIDXOFRMSRCROM                                STD_ON
#define PDUR_RMDESTROMLENGTHOFRMSRCROM                                STD_ON
#define PDUR_RMDESTROMSTARTIDXOFRMSRCROM                              STD_ON
#define PDUR_SMSRCROMIDXOFRMSRCROM                                    STD_OFF  /**< Deactivateable: 'PduR_RmSrcRom.SmSrcRomIdx' Reason: '/ActiveEcuC/PduR/PduRGeneral[0:PduRSwitching] is configured to 'false'' */
#define PDUR_SMSRCROMUSEDOFRMSRCROM                                   STD_OFF  /**< Deactivateable: 'PduR_RmSrcRom.SmSrcRomUsed' Reason: '/ActiveEcuC/PduR/PduRGeneral[0:PduRSwitching] is configured to 'false'' */
#define PDUR_SRCHNDOFRMSRCROM                                         STD_OFF  /**< Deactivateable: 'PduR_RmSrcRom.SrcHnd' Reason: 'the value of PduR_SrcHndOfRmSrcRom is always 'PDUR_NO_SRCHNDOFRMSRCROM' due to this, the array is deactivated.' */
#define PDUR_TRIGGERTRANSMITSUPPORTEDOFRMSRCROM                       STD_OFF  /**< Deactivateable: 'PduR_RmSrcRom.TriggerTransmitSupported' Reason: 'No BswModule with TriggerTransmit active.' */
#define PDUR_TXCONFIRMATIONSUPPORTEDOFRMSRCROM                        STD_OFF  /**< Deactivateable: 'PduR_RmSrcRom.TxConfirmationSupported' Reason: 'No BswModule with TxConfirmation active.' */
#define PDUR_RMTRANSMITFCTPTR                                         STD_ON
#define PDUR_RPGRAM                                                   STD_OFF  /**< Deactivateable: 'PduR_RpgRam' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define PDUR_ENABLEDOFRPGRAM                                          STD_OFF  /**< Deactivateable: 'PduR_RpgRam.Enabled' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define PDUR_RPGROM                                                   STD_OFF  /**< Deactivateable: 'PduR_RpgRom' Reason: 'the struct is deactivated because all elements are deactivated.' */
#define PDUR_ENABLEDATINITOFRPGROM                                    STD_OFF  /**< Deactivateable: 'PduR_RpgRom.EnabledAtInit' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define PDUR_INVALIDHNDOFRPGROM                                       STD_OFF  /**< Deactivateable: 'PduR_RpgRom.InvalidHnd' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define PDUR_RMDESTRPGROMINDENDIDXOFRPGROM                            STD_OFF  /**< Deactivateable: 'PduR_RpgRom.RmDestRpgRomIndEndIdx' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define PDUR_RMDESTRPGROMINDSTARTIDXOFRPGROM                          STD_OFF  /**< Deactivateable: 'PduR_RpgRom.RmDestRpgRomIndStartIdx' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define PDUR_RMDESTRPGROMINDUSEDOFRPGROM                              STD_OFF  /**< Deactivateable: 'PduR_RpgRom.RmDestRpgRomIndUsed' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define PDUR_RXIF2DEST                                                STD_ON
#define PDUR_BSWMPDURRXINDICATIONCALLBACKOFRXIF2DEST                  STD_OFF  /**< Deactivateable: 'PduR_RxIf2Dest.BswMPduRRxIndicationCallback' Reason: 'Callback Support is not active' */
#define PDUR_INVALIDHNDOFRXIF2DEST                                    STD_OFF  /**< Deactivateable: 'PduR_RxIf2Dest.InvalidHnd' Reason: 'the value of PduR_InvalidHndOfRxIf2Dest is always 'false' due to this, the array is deactivated.' */
#define PDUR_RMSRCROMIDXOFRXIF2DEST                                   STD_ON
#define PDUR_RXTP2DEST                                                STD_OFF  /**< Deactivateable: 'PduR_RxTp2Dest' Reason: 'No transport protocol PduRBswModule configured. Evaluated DefinitionRef: /MICROSAR/PduR/PduRBswModules/PduRTransportProtocol' */
#define PDUR_BSWMPDURTPRXINDICATIONCALLBACKOFRXTP2DEST                STD_OFF  /**< Deactivateable: 'PduR_RxTp2Dest.BswMPduRTpRxIndicationCallback' Reason: 'No transport protocol PduRBswModule configured. Evaluated DefinitionRef: /MICROSAR/PduR/PduRBswModules/PduRTransportProtocol' */
#define PDUR_BSWMPDURTPSTARTOFRECEPTIONCALLBACKOFRXTP2DEST            STD_OFF  /**< Deactivateable: 'PduR_RxTp2Dest.BswMPduRTpStartOfReceptionCallback' Reason: 'No transport protocol PduRBswModule configured. Evaluated DefinitionRef: /MICROSAR/PduR/PduRBswModules/PduRTransportProtocol' */
#define PDUR_INVALIDHNDOFRXTP2DEST                                    STD_OFF  /**< Deactivateable: 'PduR_RxTp2Dest.InvalidHnd' Reason: 'No transport protocol PduRBswModule configured. Evaluated DefinitionRef: /MICROSAR/PduR/PduRBswModules/PduRTransportProtocol' */
#define PDUR_RMSRCROMIDXOFRXTP2DEST                                   STD_OFF  /**< Deactivateable: 'PduR_RxTp2Dest.RmSrcRomIdx' Reason: 'No transport protocol PduRBswModule configured. Evaluated DefinitionRef: /MICROSAR/PduR/PduRBswModules/PduRTransportProtocol' */
#define PDUR_RMSRCROMUSEDOFRXTP2DEST                                  STD_OFF  /**< Deactivateable: 'PduR_RxTp2Dest.RmSrcRomUsed' Reason: 'No transport protocol PduRBswModule configured. Evaluated DefinitionRef: /MICROSAR/PduR/PduRBswModules/PduRTransportProtocol' */
#define PDUR_RXTP2SRC                                                 STD_OFF  /**< Deactivateable: 'PduR_RxTp2Src' Reason: '(No PduRBswModule configured which uses the CancelReceive API.. Evaluated DefinitionRef: /MICROSAR/PduR/PduRBswModules/PduRCancelReceive) && (No PduRBswModule configured which uses the ChangeParameter API.. Evaluated DefinitionRef: /MICROSAR/PduR/PduRBswModules/PduRChangeParameterRequestApi)' */
#define PDUR_INVALIDHNDOFRXTP2SRC                                     STD_OFF  /**< Deactivateable: 'PduR_RxTp2Src.InvalidHnd' Reason: '(No PduRBswModule configured which uses the CancelReceive API.. Evaluated DefinitionRef: /MICROSAR/PduR/PduRBswModules/PduRCancelReceive) && (No PduRBswModule configured which uses the ChangeParameter API.. Evaluated DefinitionRef: /MICROSAR/PduR/PduRBswModules/PduRChangeParameterRequestApi)' */
#define PDUR_RMDESTROMIDXOFRXTP2SRC                                   STD_OFF  /**< Deactivateable: 'PduR_RxTp2Src.RmDestRomIdx' Reason: '(No PduRBswModule configured which uses the CancelReceive API.. Evaluated DefinitionRef: /MICROSAR/PduR/PduRBswModules/PduRCancelReceive) && (No PduRBswModule configured which uses the ChangeParameter API.. Evaluated DefinitionRef: /MICROSAR/PduR/PduRBswModules/PduRChangeParameterRequestApi)' */
#define PDUR_SIZEOFIFROUTINGSTATETABLE                                STD_ON
#define PDUR_SIZEOFMMROM                                              STD_ON
#define PDUR_SIZEOFRMDESTROM                                          STD_ON
#define PDUR_SIZEOFRMGDESTROM                                         STD_ON
#define PDUR_SIZEOFRMSRCROM                                           STD_ON
#define PDUR_SIZEOFRMTRANSMITFCTPTR                                   STD_ON
#define PDUR_SIZEOFRXIF2DEST                                          STD_ON
#define PDUR_SIZEOFTX2LO                                              STD_ON
#define PDUR_SIZEOFTXIF2UP                                            STD_ON
#define PDUR_SMDATAPLANEROM                                           STD_OFF  /**< Deactivateable: 'PduR_SmDataPlaneRom' Reason: '/ActiveEcuC/PduR/PduRGeneral[0:PduRSwitching] is configured to 'false'' */
#define PDUR_SMFIBRAMENDIDXOFSMDATAPLANEROM                           STD_OFF  /**< Deactivateable: 'PduR_SmDataPlaneRom.SmFibRamEndIdx' Reason: '/ActiveEcuC/PduR/PduRGeneral[0:PduRSwitching] is configured to 'false'' */
#define PDUR_SMFIBRAMSTARTIDXOFSMDATAPLANEROM                         STD_OFF  /**< Deactivateable: 'PduR_SmDataPlaneRom.SmFibRamStartIdx' Reason: '/ActiveEcuC/PduR/PduRGeneral[0:PduRSwitching] is configured to 'false'' */
#define PDUR_SMFIBRAMUSEDOFSMDATAPLANEROM                             STD_OFF  /**< Deactivateable: 'PduR_SmDataPlaneRom.SmFibRamUsed' Reason: '/ActiveEcuC/PduR/PduRGeneral[0:PduRSwitching] is configured to 'false'' */
#define PDUR_SMLINEARTATOSACALCULATIONSTRATEGYROMIDXOFSMDATAPLANEROM  STD_OFF  /**< Deactivateable: 'PduR_SmDataPlaneRom.SmLinearTaToSaCalculationStrategyRomIdx' Reason: '/ActiveEcuC/PduR/PduRGeneral[0:PduRSwitching] is configured to 'false'' */
#define PDUR_SMLINEARTATOSACALCULATIONSTRATEGYROMUSEDOFSMDATAPLANEROM STD_OFF  /**< Deactivateable: 'PduR_SmDataPlaneRom.SmLinearTaToSaCalculationStrategyRomUsed' Reason: '/ActiveEcuC/PduR/PduRGeneral[0:PduRSwitching] is configured to 'false'' */
#define PDUR_SMSATAFROMMETADATACALCULATIONSTRATEGYROMIDXOFSMDATAPLANEROM STD_OFF  /**< Deactivateable: 'PduR_SmDataPlaneRom.SmSaTaFromMetaDataCalculationStrategyRomIdx' Reason: '/ActiveEcuC/PduR/PduRGeneral[0:PduRSwitching] is configured to 'false'' */
#define PDUR_SMSATAFROMMETADATACALCULATIONSTRATEGYROMUSEDOFSMDATAPLANEROM STD_OFF  /**< Deactivateable: 'PduR_SmDataPlaneRom.SmSaTaFromMetaDataCalculationStrategyRomUsed' Reason: '/ActiveEcuC/PduR/PduRGeneral[0:PduRSwitching] is configured to 'false'' */
#define PDUR_SMFIBRAM                                                 STD_OFF  /**< Deactivateable: 'PduR_SmFibRam' Reason: '/ActiveEcuC/PduR/PduRGeneral[0:PduRSwitching] is configured to 'false'' */
#define PDUR_LEARNEDCONNECTIONIDOFSMFIBRAM                            STD_OFF  /**< Deactivateable: 'PduR_SmFibRam.LearnedConnectionId' Reason: '/ActiveEcuC/PduR/PduRGeneral[0:PduRSwitching] is configured to 'false'' */
#define PDUR_SMGDESTFILTERFCTPTR                                      STD_OFF  /**< Deactivateable: 'PduR_SmGDestFilterFctPtr' Reason: '/ActiveEcuC/PduR/PduRGeneral[0:PduRSwitching] is configured to 'false'' */
#define PDUR_SMGDESTROM                                               STD_OFF  /**< Deactivateable: 'PduR_SmGDestRom' Reason: '/ActiveEcuC/PduR/PduRGeneral[0:PduRSwitching] is configured to 'false'' */
#define PDUR_CONNECTIONIDOFSMGDESTROM                                 STD_OFF  /**< Deactivateable: 'PduR_SmGDestRom.ConnectionId' Reason: '/ActiveEcuC/PduR/PduRGeneral[0:PduRSwitching] is configured to 'false'' */
#define PDUR_METADATALENGTHOFSMGDESTROM                               STD_OFF  /**< Deactivateable: 'PduR_SmGDestRom.MetaDataLength' Reason: '/ActiveEcuC/PduR/PduRGeneral[0:PduRSwitching] is configured to 'false'' */
#define PDUR_SMDATAPLANEROMIDXOFSMGDESTROM                            STD_OFF  /**< Deactivateable: 'PduR_SmGDestRom.SmDataPlaneRomIdx' Reason: '/ActiveEcuC/PduR/PduRGeneral[0:PduRSwitching] is configured to 'false'' */
#define PDUR_SMGDESTFILTERFCTPTRIDXOFSMGDESTROM                       STD_OFF  /**< Deactivateable: 'PduR_SmGDestRom.SmGDestFilterFctPtrIdx' Reason: '/ActiveEcuC/PduR/PduRGeneral[0:PduRSwitching] is configured to 'false'' */
#define PDUR_SMLINEARTATOSACALCULATIONSTRATEGYGETSAFCTPTR             STD_OFF  /**< Deactivateable: 'PduR_SmLinearTaToSaCalculationStrategyGetSaFctPtr' Reason: '/ActiveEcuC/PduR/PduRGeneral[0:PduRSwitching] is configured to 'false'' */
#define PDUR_SMLINEARTATOSACALCULATIONSTRATEGYROM                     STD_OFF  /**< Deactivateable: 'PduR_SmLinearTaToSaCalculationStrategyRom' Reason: '/ActiveEcuC/PduR/PduRGeneral[0:PduRSwitching] is configured to 'false'' */
#define PDUR_MASKOFSMLINEARTATOSACALCULATIONSTRATEGYROM               STD_OFF  /**< Deactivateable: 'PduR_SmLinearTaToSaCalculationStrategyRom.Mask' Reason: '/ActiveEcuC/PduR/PduRGeneral[0:PduRSwitching] is configured to 'false'' */
#define PDUR_OFFSETOFSMLINEARTATOSACALCULATIONSTRATEGYROM             STD_OFF  /**< Deactivateable: 'PduR_SmLinearTaToSaCalculationStrategyRom.Offset' Reason: '/ActiveEcuC/PduR/PduRGeneral[0:PduRSwitching] is configured to 'false'' */
#define PDUR_SMSATAFROMMETADATACALCULATIONSTRATEGYROM                 STD_OFF  /**< Deactivateable: 'PduR_SmSaTaFromMetaDataCalculationStrategyRom' Reason: '/ActiveEcuC/PduR/PduRGeneral[0:PduRSwitching] is configured to 'false'' */
#define PDUR_SAMASKOFSMSATAFROMMETADATACALCULATIONSTRATEGYROM         STD_OFF  /**< Deactivateable: 'PduR_SmSaTaFromMetaDataCalculationStrategyRom.SaMask' Reason: '/ActiveEcuC/PduR/PduRGeneral[0:PduRSwitching] is configured to 'false'' */
#define PDUR_SASTARTBITOFSMSATAFROMMETADATACALCULATIONSTRATEGYROM     STD_OFF  /**< Deactivateable: 'PduR_SmSaTaFromMetaDataCalculationStrategyRom.SaStartBit' Reason: '/ActiveEcuC/PduR/PduRGeneral[0:PduRSwitching] is configured to 'false'' */
#define PDUR_TAMASKOFSMSATAFROMMETADATACALCULATIONSTRATEGYROM         STD_OFF  /**< Deactivateable: 'PduR_SmSaTaFromMetaDataCalculationStrategyRom.TaMask' Reason: '/ActiveEcuC/PduR/PduRGeneral[0:PduRSwitching] is configured to 'false'' */
#define PDUR_TASTARTBITOFSMSATAFROMMETADATACALCULATIONSTRATEGYROM     STD_OFF  /**< Deactivateable: 'PduR_SmSaTaFromMetaDataCalculationStrategyRom.TaStartBit' Reason: '/ActiveEcuC/PduR/PduRGeneral[0:PduRSwitching] is configured to 'false'' */
#define PDUR_SMSRCFILTERFCTPTR                                        STD_OFF  /**< Deactivateable: 'PduR_SmSrcFilterFctPtr' Reason: '/ActiveEcuC/PduR/PduRGeneral[0:PduRSwitching] is configured to 'false'' */
#define PDUR_SMSRCROM                                                 STD_OFF  /**< Deactivateable: 'PduR_SmSrcRom' Reason: '/ActiveEcuC/PduR/PduRGeneral[0:PduRSwitching] is configured to 'false'' */
#define PDUR_CONNECTIONIDOFSMSRCROM                                   STD_OFF  /**< Deactivateable: 'PduR_SmSrcRom.ConnectionId' Reason: '/ActiveEcuC/PduR/PduRGeneral[0:PduRSwitching] is configured to 'false'' */
#define PDUR_METADATALENGTHOFSMSRCROM                                 STD_OFF  /**< Deactivateable: 'PduR_SmSrcRom.MetaDataLength' Reason: '/ActiveEcuC/PduR/PduRGeneral[0:PduRSwitching] is configured to 'false'' */
#define PDUR_SMDATAPLANEROMIDXOFSMSRCROM                              STD_OFF  /**< Deactivateable: 'PduR_SmSrcRom.SmDataPlaneRomIdx' Reason: '/ActiveEcuC/PduR/PduRGeneral[0:PduRSwitching] is configured to 'false'' */
#define PDUR_SMLINEARTATOSACALCULATIONSTRATEGYGETSAFCTPTRIDXOFSMSRCROM STD_OFF  /**< Deactivateable: 'PduR_SmSrcRom.SmLinearTaToSaCalculationStrategyGetSaFctPtrIdx' Reason: '/ActiveEcuC/PduR/PduRGeneral[0:PduRSwitching] is configured to 'false'' */
#define PDUR_SMLINEARTATOSACALCULATIONSTRATEGYGETSAFCTPTRUSEDOFSMSRCROM STD_OFF  /**< Deactivateable: 'PduR_SmSrcRom.SmLinearTaToSaCalculationStrategyGetSaFctPtrUsed' Reason: '/ActiveEcuC/PduR/PduRGeneral[0:PduRSwitching] is configured to 'false'' */
#define PDUR_SMSRCFILTERFCTPTRIDXOFSMSRCROM                           STD_OFF  /**< Deactivateable: 'PduR_SmSrcRom.SmSrcFilterFctPtrIdx' Reason: '/ActiveEcuC/PduR/PduRGeneral[0:PduRSwitching] is configured to 'false'' */
#define PDUR_STARTOFRECEPTIONRXSMTRANSITION                           STD_OFF  /**< Deactivateable: 'PduR_StartOfReceptionRxSmTransition' Reason: 'the struct is deactivated because all elements are deactivated.' */
#define PDUR_FCTPTROFSTARTOFRECEPTIONRXSMTRANSITION                   STD_OFF  /**< Deactivateable: 'PduR_StartOfReceptionRxSmTransition.FctPtr' Reason: 'No transport protocol PduRBswModule configured. Evaluated DefinitionRef: /MICROSAR/PduR/PduRBswModules/PduRTransportProtocol' */
#define PDUR_TPACTIVATENEXTFIFOSMTRANSITION                           STD_OFF  /**< Deactivateable: 'PduR_TpActivateNextFifoSmTransition' Reason: 'the struct is deactivated because all elements are deactivated.' */
#define PDUR_FCTPTROFTPACTIVATENEXTFIFOSMTRANSITION                   STD_OFF  /**< Deactivateable: 'PduR_TpActivateNextFifoSmTransition.FctPtr' Reason: 'No transport protocol PduRBswModule configured. Evaluated DefinitionRef: /MICROSAR/PduR/PduRBswModules/PduRTransportProtocol' */
#define PDUR_TPACTIVATEREADFIFOSMTRANSITION                           STD_OFF  /**< Deactivateable: 'PduR_TpActivateReadFifoSmTransition' Reason: 'the struct is deactivated because all elements are deactivated.' */
#define PDUR_FCTPTROFTPACTIVATEREADFIFOSMTRANSITION                   STD_OFF  /**< Deactivateable: 'PduR_TpActivateReadFifoSmTransition.FctPtr' Reason: 'No queued Routing Paths available' */
#define PDUR_TPACTIVATEWRITEFIFOSMTRANSITION                          STD_OFF  /**< Deactivateable: 'PduR_TpActivateWriteFifoSmTransition' Reason: 'the struct is deactivated because all elements are deactivated.' */
#define PDUR_FCTPTROFTPACTIVATEWRITEFIFOSMTRANSITION                  STD_OFF  /**< Deactivateable: 'PduR_TpActivateWriteFifoSmTransition.FctPtr' Reason: 'No queued Routing Paths available' */
#define PDUR_TPCANCELRECEIVEFIFOSMTRANSITION                          STD_OFF  /**< Deactivateable: 'PduR_TpCancelReceiveFifoSmTransition' Reason: 'the struct is deactivated because all elements are deactivated.' */
#define PDUR_FCTPTROFTPCANCELRECEIVEFIFOSMTRANSITION                  STD_OFF  /**< Deactivateable: 'PduR_TpCancelReceiveFifoSmTransition.FctPtr' Reason: 'No transport protocol PduRBswModule configured. Evaluated DefinitionRef: /MICROSAR/PduR/PduRBswModules/PduRTransportProtocol' */
#define PDUR_TPCANCELTRANSMITTXINSTSMTRANSITION                       STD_OFF  /**< Deactivateable: 'PduR_TpCancelTransmitTxInstSmTransition' Reason: 'the struct is deactivated because all elements are deactivated.' */
#define PDUR_FCTPTROFTPCANCELTRANSMITTXINSTSMTRANSITION               STD_OFF  /**< Deactivateable: 'PduR_TpCancelTransmitTxInstSmTransition.FctPtr' Reason: 'No transport protocol PduRBswModule configured. Evaluated DefinitionRef: /MICROSAR/PduR/PduRBswModules/PduRTransportProtocol' */
#define PDUR_TPCHECKREADY2TRANSMITRMSMTRANSITION                      STD_OFF  /**< Deactivateable: 'PduR_TpCheckReady2TransmitRmSmTransition' Reason: 'the struct is deactivated because all elements are deactivated.' */
#define PDUR_FCTPTROFTPCHECKREADY2TRANSMITRMSMTRANSITION              STD_OFF  /**< Deactivateable: 'PduR_TpCheckReady2TransmitRmSmTransition.FctPtr' Reason: 'No transport protocol PduRBswModule configured. Evaluated DefinitionRef: /MICROSAR/PduR/PduRBswModules/PduRTransportProtocol' */
#define PDUR_TPDISABLEROUTINGTXSMTRANSITION                           STD_OFF  /**< Deactivateable: 'PduR_TpDisableRoutingTxSmTransition' Reason: 'No transport protocol PduRBswModule configured. Evaluated DefinitionRef: /MICROSAR/PduR/PduRBswModules/PduRTransportProtocol' */
#define PDUR_FCTPTROFTPDISABLEROUTINGTXSMTRANSITION                   STD_OFF  /**< Deactivateable: 'PduR_TpDisableRoutingTxSmTransition.FctPtr' Reason: 'No transport protocol PduRBswModule configured. Evaluated DefinitionRef: /MICROSAR/PduR/PduRBswModules/PduRTransportProtocol' */
#define PDUR_TPRXINDICATIONRXSMTRANSITION                             STD_OFF  /**< Deactivateable: 'PduR_TpRxIndicationRxSmTransition' Reason: 'the struct is deactivated because all elements are deactivated.' */
#define PDUR_FCTPTROFTPRXINDICATIONRXSMTRANSITION                     STD_OFF  /**< Deactivateable: 'PduR_TpRxIndicationRxSmTransition.FctPtr' Reason: 'No transport protocol PduRBswModule configured. Evaluated DefinitionRef: /MICROSAR/PduR/PduRBswModules/PduRTransportProtocol' */
#define PDUR_TPTRIGGERTRANSMITTXINSTSMTRANSITION                      STD_OFF  /**< Deactivateable: 'PduR_TpTriggerTransmitTxInstSmTransition' Reason: 'the struct is deactivated because all elements are deactivated.' */
#define PDUR_FCTPTROFTPTRIGGERTRANSMITTXINSTSMTRANSITION              STD_OFF  /**< Deactivateable: 'PduR_TpTriggerTransmitTxInstSmTransition.FctPtr' Reason: 'No transport protocol PduRBswModule configured. Evaluated DefinitionRef: /MICROSAR/PduR/PduRBswModules/PduRTransportProtocol' */
#define PDUR_TPTXCONFIRMATIONTXSMTRANSITION                           STD_OFF  /**< Deactivateable: 'PduR_TpTxConfirmationTxSmTransition' Reason: 'the struct is deactivated because all elements are deactivated.' */
#define PDUR_FCTPTROFTPTXCONFIRMATIONTXSMTRANSITION                   STD_OFF  /**< Deactivateable: 'PduR_TpTxConfirmationTxSmTransition.FctPtr' Reason: 'No transport protocol PduRBswModule configured. Evaluated DefinitionRef: /MICROSAR/PduR/PduRBswModules/PduRTransportProtocol' */
#define PDUR_TRANSMITREQUESTQUEUE                                     STD_OFF  /**< Deactivateable: 'PduR_TransmitRequestQueue' Reason: '/ActiveEcuC/PduR/PduRGeneral[0:PduREnableDeferredTransmission] is configured to 'false'' */
#define PDUR_RMGDESTROMIDXOFTRANSMITREQUESTQUEUE                      STD_OFF  /**< Deactivateable: 'PduR_TransmitRequestQueue.RmGDestRomIdx' Reason: '/ActiveEcuC/PduR/PduRGeneral[0:PduREnableDeferredTransmission] is configured to 'false'' */
#define PDUR_TRANSMITREQUESTQUEUEREADIDX                              STD_OFF  /**< Deactivateable: 'PduR_TransmitRequestQueueReadIdx' Reason: 'All indirection targets are deactivated in all variants.' */
#define PDUR_TRANSMITREQUESTQUEUEWRITEIDX                             STD_OFF  /**< Deactivateable: 'PduR_TransmitRequestQueueWriteIdx' Reason: 'All indirection targets are deactivated in all variants.' */
#define PDUR_TX2LO                                                    STD_ON
#define PDUR_BSWMPDURTRANSMITCALLBACKOFTX2LO                          STD_OFF  /**< Deactivateable: 'PduR_Tx2Lo.BswMPduRTransmitCallback' Reason: 'Callback Support is not active' */
#define PDUR_CANCELTRANSMITUSEDOFTX2LO                                STD_OFF  /**< Deactivateable: 'PduR_Tx2Lo.CancelTransmitUsed' Reason: 'the value of PduR_CancelTransmitUsedOfTx2Lo is always 'false' due to this, the array is deactivated.' */
#define PDUR_INVALIDHNDOFTX2LO                                        STD_OFF  /**< Deactivateable: 'PduR_Tx2Lo.InvalidHnd' Reason: 'the value of PduR_InvalidHndOfTx2Lo is always 'false' due to this, the array is deactivated.' */
#define PDUR_RMSRCROMIDXOFTX2LO                                       STD_ON
#define PDUR_RMSRCROMUSEDOFTX2LO                                      STD_ON
#define PDUR_RMTRANSMITFCTPTRIDXOFTX2LO                               STD_ON
#define PDUR_TXIF2UP                                                  STD_ON
#define PDUR_BSWMPDURTXCONFIRMATIONCALLBACKOFTXIF2UP                  STD_OFF  /**< Deactivateable: 'PduR_TxIf2Up.BswMPduRTxConfirmationCallback' Reason: 'Callback Support is not active' */
#define PDUR_INVALIDHNDOFTXIF2UP                                      STD_OFF  /**< Deactivateable: 'PduR_TxIf2Up.InvalidHnd' Reason: 'the value of PduR_InvalidHndOfTxIf2Up is always 'false' due to this, the array is deactivated.' */
#define PDUR_RMGDESTROMIDXOFTXIF2UP                                   STD_ON
#define PDUR_TXCONFIRMATIONUSEDOFTXIF2UP                              STD_OFF  /**< Deactivateable: 'PduR_TxIf2Up.TxConfirmationUsed' Reason: 'No tx confirmation PduRBswModule configured. Evaluated DefinitionRef: /MICROSAR/PduR/PduRBswModules/PduRTxConfirmation' */
#define PDUR_TXTP2SRC                                                 STD_OFF  /**< Deactivateable: 'PduR_TxTp2Src' Reason: 'No transport protocol PduRBswModule configured. Evaluated DefinitionRef: /MICROSAR/PduR/PduRBswModules/PduRTransportProtocol' */
#define PDUR_BSWMPDURTPTXCONFIRMATIONCALLBACKOFTXTP2SRC               STD_OFF  /**< Deactivateable: 'PduR_TxTp2Src.BswMPduRTpTxConfirmationCallback' Reason: 'No transport protocol PduRBswModule configured. Evaluated DefinitionRef: /MICROSAR/PduR/PduRBswModules/PduRTransportProtocol' */
#define PDUR_INVALIDHNDOFTXTP2SRC                                     STD_OFF  /**< Deactivateable: 'PduR_TxTp2Src.InvalidHnd' Reason: 'No transport protocol PduRBswModule configured. Evaluated DefinitionRef: /MICROSAR/PduR/PduRBswModules/PduRTransportProtocol' */
#define PDUR_RMGDESTROMIDXOFTXTP2SRC                                  STD_OFF  /**< Deactivateable: 'PduR_TxTp2Src.RmGDestRomIdx' Reason: 'No transport protocol PduRBswModule configured. Evaluated DefinitionRef: /MICROSAR/PduR/PduRBswModules/PduRTransportProtocol' */
#define PDUR_PCCONFIG                                                 STD_ON
#define PDUR_CONFIGIDOFPCCONFIG                                       STD_ON
#define PDUR_FINALMAGICNUMBEROFPCCONFIG                               STD_OFF  /**< Deactivateable: 'PduR_PCConfig.FinalMagicNumber' Reason: 'the module configuration does not support flashing of data.' */
#define PDUR_IFROUTINGSTATETABLEOFPCCONFIG                            STD_ON
#define PDUR_INITDATAHASHCODEOFPCCONFIG                               STD_OFF  /**< Deactivateable: 'PduR_PCConfig.InitDataHashCode' Reason: 'the module configuration does not support flashing of data.' */
#define PDUR_INITIALIZEDOFPCCONFIG                                    STD_ON
#define PDUR_MMROMOFPCCONFIG                                          STD_ON
#define PDUR_RMDESTROMOFPCCONFIG                                      STD_ON
#define PDUR_RMGDESTROMOFPCCONFIG                                     STD_ON
#define PDUR_RMSRCROMOFPCCONFIG                                       STD_ON
#define PDUR_RMTRANSMITFCTPTROFPCCONFIG                               STD_ON
#define PDUR_RXIF2DESTOFPCCONFIG                                      STD_ON
#define PDUR_SIZEOFIFROUTINGSTATETABLEOFPCCONFIG                      STD_ON
#define PDUR_SIZEOFMMROMOFPCCONFIG                                    STD_ON
#define PDUR_SIZEOFRMDESTROMOFPCCONFIG                                STD_ON
#define PDUR_SIZEOFRMGDESTROMOFPCCONFIG                               STD_ON
#define PDUR_SIZEOFRMSRCROMOFPCCONFIG                                 STD_ON
#define PDUR_SIZEOFRMTRANSMITFCTPTROFPCCONFIG                         STD_ON
#define PDUR_SIZEOFRXIF2DESTOFPCCONFIG                                STD_ON
#define PDUR_SIZEOFTX2LOOFPCCONFIG                                    STD_ON
#define PDUR_SIZEOFTXIF2UPOFPCCONFIG                                  STD_ON
#define PDUR_TX2LOOFPCCONFIG                                          STD_ON
#define PDUR_TXIF2UPOFPCCONFIG                                        STD_ON
/** 
  \}
*/ 

/** 
  \defgroup  PduRPCNoReferenceDefines  PduR No Reference Defines (PRE_COMPILE)
  \brief  These defines are used to indicate unused indexes in data relations.
  \{
*/ 
#define PDUR_NO_DESTHNDOFRMGDESTROM                                   255U
#define PDUR_NO_RMDESTROMIDXOFRMGDESTROM                              255U
#define PDUR_NO_RMSRCROMIDXOFTX2LO                                    255U
/** 
  \}
*/ 

/** 
  \defgroup  PduRPCEnumExistsDefines  PduR Enum Exists Defines (PRE_COMPILE)
  \brief  These defines can be used to deactivate enumeration based code sequences if the enumeration value does not exist in the configuration data.
  \{
*/ 
#define PDUR_EXISTS_WAIT_FOR_RXINDICATION_NEXTSTATE_FOR_INIT_IF_ROUTING_STATEOFIFROUTINGSTATETABLE STD_ON
#define PDUR_EXISTS_WAIT_FOR_TRIGGERTRANSMIT_NEXTSTATE_FOR_INIT_IF_ROUTING_STATEOFIFROUTINGSTATETABLE STD_ON
#define PDUR_EXISTS_WAIT_FOR_TXCONFIRMATION_NEXTSTATE_FOR_INIT_IF_ROUTING_STATEOFIFROUTINGSTATETABLE STD_OFF
#define PDUR_EXISTS_WAIT_FOR_RXINDICATION_NEXTSTATE_FOR_WAIT_FOR_RXINDICATIONOFIFROUTINGSTATETABLE STD_ON
#define PDUR_EXISTS_WAIT_FOR_TRIGGERTRANSMIT_NEXTSTATE_FOR_WAIT_FOR_RXINDICATIONOFIFROUTINGSTATETABLE STD_ON
#define PDUR_EXISTS_WAIT_FOR_TXCONFIRMATION_NEXTSTATE_FOR_WAIT_FOR_RXINDICATIONOFIFROUTINGSTATETABLE STD_ON
#define PDUR_EXISTS_WAIT_FOR_RXINDICATION_NEXTSTATE_FOR_WAIT_FOR_TRIGGERTRANSMITOFIFROUTINGSTATETABLE STD_OFF
#define PDUR_EXISTS_WAIT_FOR_TRIGGERTRANSMIT_NEXTSTATE_FOR_WAIT_FOR_TRIGGERTRANSMITOFIFROUTINGSTATETABLE STD_ON
#define PDUR_EXISTS_WAIT_FOR_TXCONFIRMATION_NEXTSTATE_FOR_WAIT_FOR_TRIGGERTRANSMITOFIFROUTINGSTATETABLE STD_ON
#define PDUR_EXISTS_WAIT_FOR_RXINDICATION_NEXTSTATE_FOR_WAIT_FOR_TXCONFIRMATIONOFIFROUTINGSTATETABLE STD_OFF
#define PDUR_EXISTS_WAIT_FOR_TRIGGERTRANSMIT_NEXTSTATE_FOR_WAIT_FOR_TXCONFIRMATIONOFIFROUTINGSTATETABLE STD_ON
#define PDUR_EXISTS_WAIT_FOR_TXCONFIRMATION_NEXTSTATE_FOR_WAIT_FOR_TXCONFIRMATIONOFIFROUTINGSTATETABLE STD_ON
#define PDUR_EXISTS_NO_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM     STD_OFF  /**< Deactivateable: 'PduR_RmBufferedIfPropertiesRom.FifoType' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define PDUR_EXISTS_T_T_SINGLE_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM STD_OFF  /**< Deactivateable: 'PduR_RmBufferedIfPropertiesRom.FifoType' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define PDUR_EXISTS_T_T_FIFO_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM STD_OFF  /**< Deactivateable: 'PduR_RmBufferedIfPropertiesRom.FifoType' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define PDUR_EXISTS_DIRECT_FIFO_BUFFER_FIFOTYPEOFRMBUFFEREDIFPROPERTIESROM STD_OFF  /**< Deactivateable: 'PduR_RmBufferedIfPropertiesRom.FifoType' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define PDUR_EXISTS_RX_DIRECTIONOFRMDESTROM                           STD_ON
#define PDUR_EXISTS_TX_DIRECTIONOFRMDESTROM                           STD_ON
#define PDUR_EXISTS_SHORTEN_PDULENGTHHANDLINGSTRATEGYOFRMDESTROM      STD_OFF  /**< Deactivateable: 'PduR_RmDestRom.PduLengthHandlingStrategy' Reason: 'the value of PduR_PduLengthHandlingStrategyOfRmDestRom is always '0' due to this, the array is deactivated.' */
#define PDUR_EXISTS_DISCARD_PDULENGTHHANDLINGSTRATEGYOFRMDESTROM      STD_OFF  /**< Deactivateable: 'PduR_RmDestRom.PduLengthHandlingStrategy' Reason: 'the value of PduR_PduLengthHandlingStrategyOfRmDestRom is always '0' due to this, the array is deactivated.' */
#define PDUR_EXISTS_IF_UNBUFFERED_RX_API_FWD_ROUTINGTYPEOFRMDESTROM   STD_ON
#define PDUR_EXISTS_IF_UNBUFFERED_TX_API_FWD_ROUTINGTYPEOFRMDESTROM   STD_ON
#define PDUR_EXISTS_IF_NOBUFFER_GATEWAY_ROUTINGTYPEOFRMDESTROM        STD_OFF
#define PDUR_EXISTS_IF_BUFFERED_ROUTINGTYPEOFRMDESTROM                STD_OFF
#define PDUR_EXISTS_TP_UNBUFFERED_RX_API_FWD_ROUTINGTYPEOFRMDESTROM   STD_OFF
#define PDUR_EXISTS_TP_UNBUFFERED_TX_API_FWD_ROUTINGTYPEOFRMDESTROM   STD_OFF
#define PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM                STD_OFF
#define PDUR_EXISTS_DEFERRED_PDURDESTPDUPROCESSINGOFRMGDESTROM        STD_OFF  /**< /ActiveEcuC/PduR/PduRGeneral[0:PduREnableDeferredReception] and /ActiveEcuC/PduR/PduRGeneral[0:PduREnableDeferredTransmission] are both disabled. */
#define PDUR_EXISTS_IMMEDIATE_PDURDESTPDUPROCESSINGOFRMGDESTROM       STD_ON
/** 
  \}
*/ 

/** 
  \defgroup  PduRPCEnumDefines  PduR Enum Defines (PRE_COMPILE)
  \brief  These defines are the enumeration values of enumeration based CONST and VAR data.
  \{
*/ 
#define PDUR_WAIT_FOR_RXINDICATION_NEXTSTATE_FOR_INIT_IF_ROUTING_STATEOFIFROUTINGSTATETABLE 0x00U
#define PDUR_WAIT_FOR_TRIGGERTRANSMIT_NEXTSTATE_FOR_INIT_IF_ROUTING_STATEOFIFROUTINGSTATETABLE 0x01U
#define PDUR_WAIT_FOR_RXINDICATION_NEXTSTATE_FOR_WAIT_FOR_RXINDICATIONOFIFROUTINGSTATETABLE 0x00U
#define PDUR_WAIT_FOR_TRIGGERTRANSMIT_NEXTSTATE_FOR_WAIT_FOR_RXINDICATIONOFIFROUTINGSTATETABLE 0x01U
#define PDUR_WAIT_FOR_TXCONFIRMATION_NEXTSTATE_FOR_WAIT_FOR_RXINDICATIONOFIFROUTINGSTATETABLE 0x02U
#define PDUR_WAIT_FOR_TRIGGERTRANSMIT_NEXTSTATE_FOR_WAIT_FOR_TRIGGERTRANSMITOFIFROUTINGSTATETABLE 0x01U
#define PDUR_WAIT_FOR_TXCONFIRMATION_NEXTSTATE_FOR_WAIT_FOR_TRIGGERTRANSMITOFIFROUTINGSTATETABLE 0x02U
#define PDUR_WAIT_FOR_TRIGGERTRANSMIT_NEXTSTATE_FOR_WAIT_FOR_TXCONFIRMATIONOFIFROUTINGSTATETABLE 0x01U
#define PDUR_WAIT_FOR_TXCONFIRMATION_NEXTSTATE_FOR_WAIT_FOR_TXCONFIRMATIONOFIFROUTINGSTATETABLE 0x02U
#define PDUR_RX_DIRECTIONOFRMDESTROM                                  0x00U
#define PDUR_TX_DIRECTIONOFRMDESTROM                                  0x01U
#define PDUR_IF_UNBUFFERED_RX_API_FWD_ROUTINGTYPEOFRMDESTROM          0x00U
#define PDUR_IF_UNBUFFERED_TX_API_FWD_ROUTINGTYPEOFRMDESTROM          0x01U
#define PDUR_IMMEDIATE_PDURDESTPDUPROCESSINGOFRMGDESTROM              0x01U
/** 
  \}
*/ 

/** 
  \defgroup  PduRPCMaskedBitDefines  PduR Masked Bit Defines (PRE_COMPILE)
  \brief  These defines are masks to extract packed boolean data.
  \{
*/ 
#define PDUR_LOIFOFMMROM_MASK                                         0x02U
#define PDUR_UPIFOFMMROM_MASK                                         0x01U
/** 
  \}
*/ 

/** 
  \defgroup  PduRPCIsReducedToDefineDefines  PduR Is Reduced To Define Defines (PRE_COMPILE)
  \brief  If all values in a CONST array or an element in a CONST array of structs are equal, the define is STD_ON else STD_OFF.
  \{
*/ 
#define PDUR_ISDEF_NEXTSTATE_FOR_INIT_IF_ROUTING_STATEOFIFROUTINGSTATETABLE STD_OFF
#define PDUR_ISDEF_NEXTSTATE_FOR_WAIT_FOR_RXINDICATIONOFIFROUTINGSTATETABLE STD_OFF
#define PDUR_ISDEF_NEXTSTATE_FOR_WAIT_FOR_TRIGGERTRANSMITOFIFROUTINGSTATETABLE STD_OFF
#define PDUR_ISDEF_NEXTSTATE_FOR_WAIT_FOR_TXCONFIRMATIONOFIFROUTINGSTATETABLE STD_OFF
#define PDUR_ISDEF_LOIFOFMMROM                                        STD_OFF
#define PDUR_ISDEF_LOIFTRANSMITFCTPTROFMMROM                          STD_OFF
#define PDUR_ISDEF_MASKEDBITSOFMMROM                                  STD_OFF
#define PDUR_ISDEF_UPIFOFMMROM                                        STD_OFF
#define PDUR_ISDEF_UPIFRXINDICATIONFCTPTROFMMROM                      STD_OFF
#define PDUR_ISDEF_DIRECTIONOFRMDESTROM                               STD_OFF
#define PDUR_ISDEF_RMGDESTROMIDXOFRMDESTROM                           STD_OFF
#define PDUR_ISDEF_RMSRCROMIDXOFRMDESTROM                             STD_OFF
#define PDUR_ISDEF_ROUTINGTYPEOFRMDESTROM                             STD_OFF
#define PDUR_ISDEF_DESTHNDOFRMGDESTROM                                STD_OFF
#define PDUR_ISDEF_MMROMIDXOFRMGDESTROM                               STD_OFF
#define PDUR_ISDEF_PDURDESTPDUPROCESSINGOFRMGDESTROM                  STD_OFF
#define PDUR_ISDEF_RMDESTROMIDXOFRMGDESTROM                           STD_OFF
#define PDUR_ISDEF_RMDESTROMUSEDOFRMGDESTROM                          STD_OFF
#define PDUR_ISDEF_MMROMIDXOFRMSRCROM                                 STD_OFF
#define PDUR_ISDEF_RMDESTROMENDIDXOFRMSRCROM                          STD_OFF
#define PDUR_ISDEF_RMDESTROMLENGTHOFRMSRCROM                          STD_OFF
#define PDUR_ISDEF_RMDESTROMSTARTIDXOFRMSRCROM                        STD_OFF
#define PDUR_ISDEF_RMTRANSMITFCTPTR                                   STD_OFF
#define PDUR_ISDEF_RMSRCROMIDXOFRXIF2DEST                             STD_OFF
#define PDUR_ISDEF_RMSRCROMIDXOFTX2LO                                 STD_OFF
#define PDUR_ISDEF_RMSRCROMUSEDOFTX2LO                                STD_OFF
#define PDUR_ISDEF_RMTRANSMITFCTPTRIDXOFTX2LO                         STD_OFF
#define PDUR_ISDEF_RMGDESTROMIDXOFTXIF2UP                             STD_OFF
#define PDUR_ISDEF_IFROUTINGSTATETABLEOFPCCONFIG                      STD_ON
#define PDUR_ISDEF_INITIALIZEDOFPCCONFIG                              STD_ON
#define PDUR_ISDEF_MMROMOFPCCONFIG                                    STD_ON
#define PDUR_ISDEF_RMDESTROMOFPCCONFIG                                STD_ON
#define PDUR_ISDEF_RMGDESTROMOFPCCONFIG                               STD_ON
#define PDUR_ISDEF_RMSRCROMOFPCCONFIG                                 STD_ON
#define PDUR_ISDEF_RMTRANSMITFCTPTROFPCCONFIG                         STD_ON
#define PDUR_ISDEF_RXIF2DESTOFPCCONFIG                                STD_ON
#define PDUR_ISDEF_TX2LOOFPCCONFIG                                    STD_ON
#define PDUR_ISDEF_TXIF2UPOFPCCONFIG                                  STD_ON
/** 
  \}
*/ 

/** 
  \defgroup  PduRPCEqualsAlwaysToDefines  PduR Equals Always To Defines (PRE_COMPILE)
  \brief  If all values in a CONST array or an element in a CONST array of structs are equal, the define contains the always equals value.
  \{
*/ 
#define PDUR_EQ2_NEXTSTATE_FOR_INIT_IF_ROUTING_STATEOFIFROUTINGSTATETABLE 
#define PDUR_EQ2_NEXTSTATE_FOR_WAIT_FOR_RXINDICATIONOFIFROUTINGSTATETABLE 
#define PDUR_EQ2_NEXTSTATE_FOR_WAIT_FOR_TRIGGERTRANSMITOFIFROUTINGSTATETABLE 
#define PDUR_EQ2_NEXTSTATE_FOR_WAIT_FOR_TXCONFIRMATIONOFIFROUTINGSTATETABLE 
#define PDUR_EQ2_LOIFOFMMROM                                          
#define PDUR_EQ2_LOIFTRANSMITFCTPTROFMMROM                            
#define PDUR_EQ2_MASKEDBITSOFMMROM                                    
#define PDUR_EQ2_UPIFOFMMROM                                          
#define PDUR_EQ2_UPIFRXINDICATIONFCTPTROFMMROM                        
#define PDUR_EQ2_DIRECTIONOFRMDESTROM                                 
#define PDUR_EQ2_RMGDESTROMIDXOFRMDESTROM                             
#define PDUR_EQ2_RMSRCROMIDXOFRMDESTROM                               
#define PDUR_EQ2_ROUTINGTYPEOFRMDESTROM                               
#define PDUR_EQ2_DESTHNDOFRMGDESTROM                                  
#define PDUR_EQ2_MMROMIDXOFRMGDESTROM                                 
#define PDUR_EQ2_PDURDESTPDUPROCESSINGOFRMGDESTROM                    
#define PDUR_EQ2_RMDESTROMIDXOFRMGDESTROM                             
#define PDUR_EQ2_RMDESTROMUSEDOFRMGDESTROM                            
#define PDUR_EQ2_MMROMIDXOFRMSRCROM                                   
#define PDUR_EQ2_RMDESTROMENDIDXOFRMSRCROM                            
#define PDUR_EQ2_RMDESTROMLENGTHOFRMSRCROM                            
#define PDUR_EQ2_RMDESTROMSTARTIDXOFRMSRCROM                          
#define PDUR_EQ2_RMTRANSMITFCTPTR                                     
#define PDUR_EQ2_RMSRCROMIDXOFRXIF2DEST                               
#define PDUR_EQ2_RMSRCROMIDXOFTX2LO                                   
#define PDUR_EQ2_RMSRCROMUSEDOFTX2LO                                  
#define PDUR_EQ2_RMTRANSMITFCTPTRIDXOFTX2LO                           
#define PDUR_EQ2_RMGDESTROMIDXOFTXIF2UP                               
#define PDUR_EQ2_IFROUTINGSTATETABLEOFPCCONFIG                        PduR_IfRoutingStateTable
#define PDUR_EQ2_INITIALIZEDOFPCCONFIG                                (&(PduR_Initialized))
#define PDUR_EQ2_MMROMOFPCCONFIG                                      PduR_MmRom
#define PDUR_EQ2_RMDESTROMOFPCCONFIG                                  PduR_RmDestRom
#define PDUR_EQ2_RMGDESTROMOFPCCONFIG                                 PduR_RmGDestRom
#define PDUR_EQ2_RMSRCROMOFPCCONFIG                                   PduR_RmSrcRom
#define PDUR_EQ2_RMTRANSMITFCTPTROFPCCONFIG                           PduR_RmTransmitFctPtr
#define PDUR_EQ2_RXIF2DESTOFPCCONFIG                                  PduR_RxIf2Dest
#define PDUR_EQ2_TX2LOOFPCCONFIG                                      PduR_Tx2Lo
#define PDUR_EQ2_TXIF2UPOFPCCONFIG                                    PduR_TxIf2Up
/** 
  \}
*/ 

/** 
  \defgroup  PduRPCSymbolicInitializationPointers  PduR Symbolic Initialization Pointers (PRE_COMPILE)
  \brief  Symbolic initialization pointers to be used in the call of a preinit or init function.
  \{
*/ 
#define PduR_Config_Ptr                                               NULL_PTR  /**< symbolic identifier which shall be used to initialize 'PduR' */
/** 
  \}
*/ 

/** 
  \defgroup  PduRPCInitializationSymbols  PduR Initialization Symbols (PRE_COMPILE)
  \brief  Symbolic initialization pointers which may be used in the call of a preinit or init function. Please note, that the defined value can be a 'NULL_PTR' and the address operator is not usable.
  \{
*/ 
#define PduR_Config                                                   NULL_PTR  /**< symbolic identifier which could be used to initialize 'PduR */
/** 
  \}
*/ 

/** 
  \defgroup  PduRPCGeneral  PduR General (PRE_COMPILE)
  \brief  General constant defines not associated with a group of defines.
  \{
*/ 
#define PDUR_CHECK_INIT_POINTER                                       STD_OFF  /**< STD_ON if the init pointer shall not be used as NULL_PTR and a check shall validate this. */
#define PDUR_FINAL_MAGIC_NUMBER                                       0x331EU  /**< the precompile constant to validate the size of the initialization structure at initialization time of PduR */
#define PDUR_INDIVIDUAL_POSTBUILD                                     STD_OFF  /**< the precompile constant to check, that the module is individual postbuildable. The module 'PduR' is not configured to be postbuild capable. */
#define PDUR_INIT_DATA                                                PDUR_CONST  /**< CompilerMemClassDefine for the initialization data. */
#define PDUR_INIT_DATA_HASH_CODE                                      -713907762L  /**< the precompile constant to validate the initialization structure at initialization time of PduR with a hashcode. The seed value is '0x331EU' */
#define PDUR_USE_ECUM_BSW_ERROR_HOOK                                  STD_OFF  /**< STD_ON if the EcuM_BswErrorHook shall be called in the ConfigPtr check. */
#define PDUR_USE_INIT_POINTER                                         STD_OFF  /**< STD_ON if the init pointer PduR shall be used. */
/** 
  \}
*/ 


/**********************************************************************************************************************
  CONFIGURATION CLASS: LINK
  SECTION: GLOBAL CONSTANT MACROS
**********************************************************************************************************************/
/** 
  \defgroup  PduRLTDataSwitches  PduR Data Switches  (LINK)
  \brief  These defines are used to deactivate data and their processing.
  \{
*/ 
#define PDUR_LTCONFIG                                                 STD_OFF  /**< Deactivateable: 'PduR_LTConfig' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
/** 
  \}
*/ 



/** BroadcastDummy */

#define PDUR_MAX_TRIGGER_TRANSMIT_PDU_SIZE 0


#if (PDUR_FMFIFOELEMENTRAM == STD_OFF)
  #define PduR_FmFifoElementRamIterType uint16
#endif

/**********************************************************************************************************************
 * GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/
/** 
  \defgroup  DataAccessMacros  Data Access Macros
  \brief  generated data access macros to abstract the generated data from the code to read and write CONST or VAR data.
  \{
*/ 
  /* PRQA S 3453 MACROS_3453 */  /* MD_CSL_3453 */
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL FUNCTION MACROS
**********************************************************************************************************************/
/** 
  \defgroup  PduRPCGetConstantDuplicatedRootDataMacros  PduR Get Constant Duplicated Root Data Macros (PRE_COMPILE)
  \brief  These macros can be used to read deduplicated by constance root data elements.
  \{
*/ 
#define PduR_GetConfigIdOfPCConfig()                                  0U  /**< DefinitionRef: /MICROSAR/PduR/PduRRoutingTables/PduRConfigurationId */
#define PduR_GetIfRoutingStateTableOfPCConfig()                       PduR_IfRoutingStateTable  /**< the pointer to PduR_IfRoutingStateTable */
#define PduR_GetInitializedOfPCConfig()                               (&(PduR_Initialized))  /**< the pointer to PduR_Initialized */
#define PduR_GetMmRomOfPCConfig()                                     PduR_MmRom  /**< the pointer to PduR_MmRom */
#define PduR_GetRmDestRomOfPCConfig()                                 PduR_RmDestRom  /**< the pointer to PduR_RmDestRom */
#define PduR_GetRmGDestRomOfPCConfig()                                PduR_RmGDestRom  /**< the pointer to PduR_RmGDestRom */
#define PduR_GetRmSrcRomOfPCConfig()                                  PduR_RmSrcRom  /**< the pointer to PduR_RmSrcRom */
#define PduR_GetRmTransmitFctPtrOfPCConfig()                          PduR_RmTransmitFctPtr  /**< the pointer to PduR_RmTransmitFctPtr */
#define PduR_GetRxIf2DestOfPCConfig()                                 PduR_RxIf2Dest  /**< the pointer to PduR_RxIf2Dest */
#define PduR_GetSizeOfIfRoutingStateTableOfPCConfig()                 4U  /**< the number of accomplishable value elements in PduR_IfRoutingStateTable */
#define PduR_GetSizeOfMmRomOfPCConfig()                               2U  /**< the number of accomplishable value elements in PduR_MmRom */
#define PduR_GetSizeOfRmDestRomOfPCConfig()                           2U  /**< the number of accomplishable value elements in PduR_RmDestRom */
#define PduR_GetSizeOfRmGDestRomOfPCConfig()                          2U  /**< the number of accomplishable value elements in PduR_RmGDestRom */
#define PduR_GetSizeOfRmSrcRomOfPCConfig()                            2U  /**< the number of accomplishable value elements in PduR_RmSrcRom */
#define PduR_GetSizeOfRmTransmitFctPtrOfPCConfig()                    1U  /**< the number of accomplishable value elements in PduR_RmTransmitFctPtr */
#define PduR_GetSizeOfRxIf2DestOfPCConfig()                           1U  /**< the number of accomplishable value elements in PduR_RxIf2Dest */
#define PduR_GetSizeOfTx2LoOfPCConfig()                               1U  /**< the number of accomplishable value elements in PduR_Tx2Lo */
#define PduR_GetSizeOfTxIf2UpOfPCConfig()                             1U  /**< the number of accomplishable value elements in PduR_TxIf2Up */
#define PduR_GetTx2LoOfPCConfig()                                     PduR_Tx2Lo  /**< the pointer to PduR_Tx2Lo */
#define PduR_GetTxIf2UpOfPCConfig()                                   PduR_TxIf2Up  /**< the pointer to PduR_TxIf2Up */
/** 
  \}
*/ 

/** 
  \defgroup  PduRPCGetDataMacros  PduR Get Data Macros (PRE_COMPILE)
  \brief  These macros can be used to read CONST and VAR data.
  \{
*/ 
#define PduR_GetNextState_For_Init_If_Routing_StateOfIfRoutingStateTable(Index) (PduR_GetIfRoutingStateTableOfPCConfig()[(Index)].NextState_For_Init_If_Routing_StateOfIfRoutingStateTable)
#define PduR_GetNextState_For_Wait_For_RxIndicationOfIfRoutingStateTable(Index) (PduR_GetIfRoutingStateTableOfPCConfig()[(Index)].NextState_For_Wait_For_RxIndicationOfIfRoutingStateTable)
#define PduR_GetNextState_For_Wait_For_TriggerTransmitOfIfRoutingStateTable(Index) (PduR_GetIfRoutingStateTableOfPCConfig()[(Index)].NextState_For_Wait_For_TriggerTransmitOfIfRoutingStateTable)
#define PduR_GetNextState_For_Wait_For_TxConfirmationOfIfRoutingStateTable(Index) (PduR_GetIfRoutingStateTableOfPCConfig()[(Index)].NextState_For_Wait_For_TxConfirmationOfIfRoutingStateTable)
#define PduR_IsInitialized()                                          (((*(PduR_GetInitializedOfPCConfig()))) != FALSE)
#define PduR_GetLoIfTransmitFctPtrOfMmRom(Index)                      (PduR_GetMmRomOfPCConfig()[(Index)].LoIfTransmitFctPtrOfMmRom)
#define PduR_GetMaskedBitsOfMmRom(Index)                              (PduR_GetMmRomOfPCConfig()[(Index)].MaskedBitsOfMmRom)
#define PduR_GetUpIfRxIndicationFctPtrOfMmRom(Index)                  (PduR_GetMmRomOfPCConfig()[(Index)].UpIfRxIndicationFctPtrOfMmRom)
#define PduR_GetRmGDestRomIdxOfRmDestRom(Index)                       (PduR_GetRmDestRomOfPCConfig()[(Index)].RmGDestRomIdxOfRmDestRom)
#define PduR_GetPduRDestPduProcessingOfRmGDestRom(Index)              (PduR_GetRmGDestRomOfPCConfig()[(Index)].PduRDestPduProcessingOfRmGDestRom)
#define PduR_GetRmDestRomIdxOfRmGDestRom(Index)                       (PduR_GetRmGDestRomOfPCConfig()[(Index)].RmDestRomIdxOfRmGDestRom)
#define PduR_GetMmRomIdxOfRmSrcRom(Index)                             (PduR_GetRmSrcRomOfPCConfig()[(Index)].MmRomIdxOfRmSrcRom)
#define PduR_GetRmDestRomLengthOfRmSrcRom(Index)                      (PduR_GetRmSrcRomOfPCConfig()[(Index)].RmDestRomLengthOfRmSrcRom)
#define PduR_GetRmTransmitFctPtr(Index)                               (PduR_GetRmTransmitFctPtrOfPCConfig()[(Index)])
/** 
  \}
*/ 

/** 
  \defgroup  PduRPCGetBitDataMacros  PduR Get Bit Data Macros (PRE_COMPILE)
  \brief  These macros can be used to read bitcoded data elements.
  \{
*/ 
#define PduR_IsUpIfOfMmRom(Index)                                     (PDUR_UPIFOFMMROM_MASK == (PduR_GetMaskedBitsOfMmRom(Index) & PDUR_UPIFOFMMROM_MASK))  /**< Is the module a upper communication interface module. */
/** 
  \}
*/ 

/** 
  \defgroup  PduRPCGetDeduplicatedDataMacros  PduR Get Deduplicated Data Macros (PRE_COMPILE)
  \brief  These macros can be used to read deduplicated data elements.
  \{
*/ 
#define PduR_GetConfigId()                                            PduR_GetConfigIdOfPCConfig()
#define PduR_IsLoIfOfMmRom(Index)                                     (((!(PduR_IsUpIfOfMmRom(Index)))) != FALSE)  /**< Is the module a lower communication interface module. */
#define PduR_GetDirectionOfRmDestRom(Index)                           PduR_GetRmGDestRomIdxOfRmDestRom(Index)  /**< Direction of this Pdu: Rx or Tx */
#define PduR_GetRmSrcRomIdxOfRmDestRom(Index)                         ((PduR_RmSrcRomIdxOfRmDestRomType)((Index)))  /**< the index of the 1:1 relation pointing to PduR_RmSrcRom */
#define PduR_GetRoutingTypeOfRmDestRom(Index)                         PduR_GetRmGDestRomIdxOfRmDestRom(Index)  /**< Type of the Routing (API Forwarding, Gateway). */
#define PduR_GetDestHndOfRmGDestRom(Index)                            ((PduR_DestHndOfRmGDestRomType)((PduR_GetPduRDestPduProcessingOfRmGDestRom(Index) - 0x01U)))  /**< handle to be used as parameter for the StartOfReception, CopyRxData, Transmit or RxIndication function call. */
#define PduR_GetMmRomIdxOfRmGDestRom(Index)                           PduR_GetRmDestRomIdxOfRmGDestRom(Index)  /**< the index of the 1:1 relation pointing to PduR_MmRom */
#define PduR_IsRmDestRomUsedOfRmGDestRom(Index)                       (((boolean)(PduR_GetRmDestRomIdxOfRmGDestRom(Index) != PDUR_NO_RMDESTROMIDXOFRMGDESTROM)) != FALSE)  /**< TRUE, if the 0:1 relation has minimum 1 relation pointing to PduR_RmDestRom */
#define PduR_GetRmDestRomEndIdxOfRmSrcRom(Index)                      ((PduR_RmDestRomEndIdxOfRmSrcRomType)(((Index) + 1U)))  /**< the end index of the 1:n relation pointing to PduR_RmDestRom */
#define PduR_GetRmDestRomStartIdxOfRmSrcRom(Index)                    ((PduR_RmDestRomStartIdxOfRmSrcRomType)((Index)))  /**< the start index of the 1:n relation pointing to PduR_RmDestRom */
#define PduR_GetRmSrcRomIdxOfRxIf2Dest(Index)                         ((PduR_RmSrcRomIdxOfRxIf2DestType)(((Index) + 1U)))  /**< the index of the 1:1 relation pointing to PduR_RmSrcRom */
#define PduR_GetSizeOfIfRoutingStateTable()                           PduR_GetSizeOfIfRoutingStateTableOfPCConfig()
#define PduR_GetSizeOfMmRom()                                         PduR_GetSizeOfMmRomOfPCConfig()
#define PduR_GetSizeOfRmDestRom()                                     PduR_GetSizeOfRmDestRomOfPCConfig()
#define PduR_GetSizeOfRmGDestRom()                                    PduR_GetSizeOfRmGDestRomOfPCConfig()
#define PduR_GetSizeOfRmSrcRom()                                      PduR_GetSizeOfRmSrcRomOfPCConfig()
#define PduR_GetSizeOfRmTransmitFctPtr()                              PduR_GetSizeOfRmTransmitFctPtrOfPCConfig()
#define PduR_GetSizeOfRxIf2Dest()                                     PduR_GetSizeOfRxIf2DestOfPCConfig()
#define PduR_GetSizeOfTx2Lo()                                         PduR_GetSizeOfTx2LoOfPCConfig()
#define PduR_GetSizeOfTxIf2Up()                                       PduR_GetSizeOfTxIf2UpOfPCConfig()
#define PduR_GetRmSrcRomIdxOfTx2Lo(Index)                             ((PduR_RmSrcRomIdxOfTx2LoType)((Index)))  /**< the index of the 0:1 relation pointing to PduR_RmSrcRom */
#define PduR_IsRmSrcRomUsedOfTx2Lo(Index)                             (((boolean)(PduR_GetRmSrcRomIdxOfTx2Lo(Index) != PDUR_NO_RMSRCROMIDXOFTX2LO)) != FALSE)  /**< TRUE, if the 0:1 relation has minimum 1 relation pointing to PduR_RmSrcRom */
#define PduR_GetRmTransmitFctPtrIdxOfTx2Lo(Index)                     ((PduR_RmTransmitFctPtrIdxOfTx2LoType)((Index)))  /**< the index of the 1:1 relation pointing to PduR_RmTransmitFctPtr */
#define PduR_GetRmGDestRomIdxOfTxIf2Up(Index)                         ((PduR_RmGDestRomIdxOfTxIf2UpType)(((Index) + 1U)))  /**< the index of the 1:1 relation pointing to PduR_RmGDestRom */
/** 
  \}
*/ 

/** 
  \defgroup  PduRPCSetDataMacros  PduR Set Data Macros (PRE_COMPILE)
  \brief  These macros can be used to write data.
  \{
*/ 
#define PduR_SetInitialized(Value)                                    (*(PduR_GetInitializedOfPCConfig())) = (Value)
/** 
  \}
*/ 

/** 
  \defgroup  PduRPCHasMacros  PduR Has Macros (PRE_COMPILE)
  \brief  These macros can be used to detect at runtime a deactivated piece of information. TRUE in the CONFIGURATION_VARIANT PRE-COMPILE, TRUE or FALSE in the CONFIGURATION_VARIANT POST-BUILD.
  \{
*/ 
#define PduR_HasConfigId()                                            (TRUE != FALSE)
#define PduR_HasIfRoutingStateTable()                                 (TRUE != FALSE)
#define PduR_HasNextState_For_Init_If_Routing_StateOfIfRoutingStateTable() (TRUE != FALSE)
#define PduR_HasNextState_For_Wait_For_RxIndicationOfIfRoutingStateTable() (TRUE != FALSE)
#define PduR_HasNextState_For_Wait_For_TriggerTransmitOfIfRoutingStateTable() (TRUE != FALSE)
#define PduR_HasNextState_For_Wait_For_TxConfirmationOfIfRoutingStateTable() (TRUE != FALSE)
#define PduR_HasInitialized()                                         (TRUE != FALSE)
#define PduR_HasMmRom()                                               (TRUE != FALSE)
#define PduR_HasLoIfOfMmRom()                                         (TRUE != FALSE)
#define PduR_HasLoIfTransmitFctPtrOfMmRom()                           (TRUE != FALSE)
#define PduR_HasMaskedBitsOfMmRom()                                   (TRUE != FALSE)
#define PduR_HasUpIfOfMmRom()                                         (TRUE != FALSE)
#define PduR_HasUpIfRxIndicationFctPtrOfMmRom()                       (TRUE != FALSE)
#define PduR_HasRmDestRom()                                           (TRUE != FALSE)
#define PduR_HasDirectionOfRmDestRom()                                (TRUE != FALSE)
#define PduR_HasRmGDestRomIdxOfRmDestRom()                            (TRUE != FALSE)
#define PduR_HasRmSrcRomIdxOfRmDestRom()                              (TRUE != FALSE)
#define PduR_HasRoutingTypeOfRmDestRom()                              (TRUE != FALSE)
#define PduR_HasRmGDestRom()                                          (TRUE != FALSE)
#define PduR_HasDestHndOfRmGDestRom()                                 (TRUE != FALSE)
#define PduR_HasMmRomIdxOfRmGDestRom()                                (TRUE != FALSE)
#define PduR_HasPduRDestPduProcessingOfRmGDestRom()                   (TRUE != FALSE)
#define PduR_HasRmDestRomIdxOfRmGDestRom()                            (TRUE != FALSE)
#define PduR_HasRmDestRomUsedOfRmGDestRom()                           (TRUE != FALSE)
#define PduR_HasRmSrcRom()                                            (TRUE != FALSE)
#define PduR_HasMmRomIdxOfRmSrcRom()                                  (TRUE != FALSE)
#define PduR_HasRmDestRomEndIdxOfRmSrcRom()                           (TRUE != FALSE)
#define PduR_HasRmDestRomLengthOfRmSrcRom()                           (TRUE != FALSE)
#define PduR_HasRmDestRomStartIdxOfRmSrcRom()                         (TRUE != FALSE)
#define PduR_HasRmTransmitFctPtr()                                    (TRUE != FALSE)
#define PduR_HasRxIf2Dest()                                           (TRUE != FALSE)
#define PduR_HasRmSrcRomIdxOfRxIf2Dest()                              (TRUE != FALSE)
#define PduR_HasSizeOfIfRoutingStateTable()                           (TRUE != FALSE)
#define PduR_HasSizeOfMmRom()                                         (TRUE != FALSE)
#define PduR_HasSizeOfRmDestRom()                                     (TRUE != FALSE)
#define PduR_HasSizeOfRmGDestRom()                                    (TRUE != FALSE)
#define PduR_HasSizeOfRmSrcRom()                                      (TRUE != FALSE)
#define PduR_HasSizeOfRmTransmitFctPtr()                              (TRUE != FALSE)
#define PduR_HasSizeOfRxIf2Dest()                                     (TRUE != FALSE)
#define PduR_HasSizeOfTx2Lo()                                         (TRUE != FALSE)
#define PduR_HasSizeOfTxIf2Up()                                       (TRUE != FALSE)
#define PduR_HasTx2Lo()                                               (TRUE != FALSE)
#define PduR_HasRmSrcRomIdxOfTx2Lo()                                  (TRUE != FALSE)
#define PduR_HasRmSrcRomUsedOfTx2Lo()                                 (TRUE != FALSE)
#define PduR_HasRmTransmitFctPtrIdxOfTx2Lo()                          (TRUE != FALSE)
#define PduR_HasTxIf2Up()                                             (TRUE != FALSE)
#define PduR_HasRmGDestRomIdxOfTxIf2Up()                              (TRUE != FALSE)
#define PduR_HasPCConfig()                                            (TRUE != FALSE)
#define PduR_HasConfigIdOfPCConfig()                                  (TRUE != FALSE)
#define PduR_HasIfRoutingStateTableOfPCConfig()                       (TRUE != FALSE)
#define PduR_HasInitializedOfPCConfig()                               (TRUE != FALSE)
#define PduR_HasMmRomOfPCConfig()                                     (TRUE != FALSE)
#define PduR_HasRmDestRomOfPCConfig()                                 (TRUE != FALSE)
#define PduR_HasRmGDestRomOfPCConfig()                                (TRUE != FALSE)
#define PduR_HasRmSrcRomOfPCConfig()                                  (TRUE != FALSE)
#define PduR_HasRmTransmitFctPtrOfPCConfig()                          (TRUE != FALSE)
#define PduR_HasRxIf2DestOfPCConfig()                                 (TRUE != FALSE)
#define PduR_HasSizeOfIfRoutingStateTableOfPCConfig()                 (TRUE != FALSE)
#define PduR_HasSizeOfMmRomOfPCConfig()                               (TRUE != FALSE)
#define PduR_HasSizeOfRmDestRomOfPCConfig()                           (TRUE != FALSE)
#define PduR_HasSizeOfRmGDestRomOfPCConfig()                          (TRUE != FALSE)
#define PduR_HasSizeOfRmSrcRomOfPCConfig()                            (TRUE != FALSE)
#define PduR_HasSizeOfRmTransmitFctPtrOfPCConfig()                    (TRUE != FALSE)
#define PduR_HasSizeOfRxIf2DestOfPCConfig()                           (TRUE != FALSE)
#define PduR_HasSizeOfTx2LoOfPCConfig()                               (TRUE != FALSE)
#define PduR_HasSizeOfTxIf2UpOfPCConfig()                             (TRUE != FALSE)
#define PduR_HasTx2LoOfPCConfig()                                     (TRUE != FALSE)
#define PduR_HasTxIf2UpOfPCConfig()                                   (TRUE != FALSE)
/** 
  \}
*/ 

  /* PRQA L:MACROS_3453 */
/** 
  \}
*/ 

/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL ACCESS FUNCTION MACROS
**********************************************************************************************************************/

/** 
  \defgroup  DataAccessMacros  Data Access Macros
  \brief  generated data access macros to abstract the generated data from the code to read and write CONST or VAR data.
  \{
*/ 
  /* PRQA S 3453 MACROS_3453 */  /* MD_CSL_3453 */
/**********************************************************************************************************************
  CONFIGURATION CLASS: LINK
  SECTION: GLOBAL FUNCTION MACROS
**********************************************************************************************************************/
  /* PRQA L:MACROS_3453 */
/** 
  \}
*/ 

/**********************************************************************************************************************
  CONFIGURATION CLASS: LINK
  SECTION: GLOBAL ACCESS FUNCTION MACROS
**********************************************************************************************************************/


/**********************************************************************************************************************
 * GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
/* Communication Interface APIs */
typedef P2FUNC(Std_ReturnType, PDUR_APPL_CODE, PduR_TransmitFctPtrType) (PduIdType, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA));
typedef P2FUNC(Std_ReturnType, PDUR_APPL_CODE, PduR_TriggerTransmitFctPtrType) (PduIdType, P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA));
typedef P2FUNC(void, PDUR_APPL_CODE, PduR_IfRxIndicationType) (PduIdType, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA));
typedef P2FUNC(void, PDUR_APPL_CODE, PduR_IfTxConfirmationFctPtrType) (PduIdType);

/* Transport Protocol APIs */
typedef P2FUNC(BufReq_ReturnType, PDUR_APPL_CODE, PduR_StartOfReceptionFctPtrType) (PduIdType, P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA), PduLengthType, P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA));

typedef P2FUNC(BufReq_ReturnType, PDUR_APPL_CODE, PduR_CopyRxDataFctPtrType) (PduIdType, P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA), P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA));

typedef P2FUNC(BufReq_ReturnType, PDUR_APPL_CODE, PduR_CopyTxDataFctPtrType) (PduIdType, P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA), P2VAR(RetryInfoType, AUTOMATIC, PDUR_APPL_DATA), P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA));

typedef P2FUNC(void, PDUR_APPL_CODE, PduR_TpRxIndicationFctPtrType) (PduIdType, Std_ReturnType);

typedef P2FUNC(void, PDUR_APPL_CODE, PduR_TpTxConfirmationFctPtrType) (PduIdType, Std_ReturnType);


#if ((PDUR_IFCANCELTRANSMITSUPPORTEDOFMMROM == STD_ON) || (PDUR_TPCANCELTRANSMITSUPPORTEDOFMMROM == STD_ON))
typedef P2FUNC(Std_ReturnType, PDUR_APPL_CODE, PduR_CancelTransmitFctPtrType)(PduIdType);
#endif
#if (PDUR_CANCELRECEIVESUPPORTEDOFMMROM == STD_ON)
typedef P2FUNC(Std_ReturnType, PDUR_APPL_CODE, PduR_CancelReceiveFctPtrType) (PduIdType);
#endif
#if (PDUR_CHANGEPARAMETERSUPPORTEDOFMMROM == STD_ON)
typedef P2FUNC(Std_ReturnType, PDUR_APPL_CODE, PduR_ChangeParameterFctPtrType) (PduIdType, TPParameterType, uint16);
#endif

typedef P2FUNC(void, PDUR_CODE, PduR_DisableRoutingFctPtrType) (PduR_RoutingPathGroupIdType);


/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL SIMPLE DATA TYPES AND STRUCTURES
**********************************************************************************************************************/
/** 
  \defgroup  PduRPCIterableTypes  PduR Iterable Types (PRE_COMPILE)
  \brief  These type definitions are used to iterate over an array with least processor cycles for variable access as possible.
  \{
*/ 
/**   \brief  type used to iterate PduR_IfRoutingStateTable */
typedef uint8_least PduR_IfRoutingStateTableIterType;

/**   \brief  type used to iterate PduR_MmRom */
typedef uint8_least PduR_MmRomIterType;

/**   \brief  type used to iterate PduR_RmDestRom */
typedef uint8_least PduR_RmDestRomIterType;

/**   \brief  type used to iterate PduR_RmGDestRom */
typedef uint8_least PduR_RmGDestRomIterType;

/**   \brief  type used to iterate PduR_RmSrcRom */
typedef uint8_least PduR_RmSrcRomIterType;

/**   \brief  type used to iterate PduR_RmTransmitFctPtr */
typedef uint8_least PduR_RmTransmitFctPtrIterType;

/**   \brief  type used to iterate PduR_RxIf2Dest */
typedef uint8_least PduR_RxIf2DestIterType;

/**   \brief  type used to iterate PduR_Tx2Lo */
typedef uint8_least PduR_Tx2LoIterType;

/**   \brief  type used to iterate PduR_TxIf2Up */
typedef uint8_least PduR_TxIf2UpIterType;

/** 
  \}
*/ 

/** 
  \defgroup  PduRPCValueTypes  PduR Value Types (PRE_COMPILE)
  \brief  These type definitions are used for value based data representations.
  \{
*/ 
/**   \brief  value based type definition for PduR_ConfigId */
typedef uint8 PduR_ConfigIdType;

/**   \brief  value based type definition for PduR_NextState_For_Init_If_Routing_StateOfIfRoutingStateTable */
typedef uint8 PduR_NextState_For_Init_If_Routing_StateOfIfRoutingStateTableType;

/**   \brief  value based type definition for PduR_NextState_For_Wait_For_RxIndicationOfIfRoutingStateTable */
typedef uint8 PduR_NextState_For_Wait_For_RxIndicationOfIfRoutingStateTableType;

/**   \brief  value based type definition for PduR_NextState_For_Wait_For_TriggerTransmitOfIfRoutingStateTable */
typedef uint8 PduR_NextState_For_Wait_For_TriggerTransmitOfIfRoutingStateTableType;

/**   \brief  value based type definition for PduR_NextState_For_Wait_For_TxConfirmationOfIfRoutingStateTable */
typedef uint8 PduR_NextState_For_Wait_For_TxConfirmationOfIfRoutingStateTableType;

/**   \brief  value based type definition for PduR_Initialized */
typedef boolean PduR_InitializedType;

/**   \brief  value based type definition for PduR_LoIfOfMmRom */
typedef boolean PduR_LoIfOfMmRomType;

/**   \brief  value based type definition for PduR_MaskedBitsOfMmRom */
typedef uint8 PduR_MaskedBitsOfMmRomType;

/**   \brief  value based type definition for PduR_UpIfOfMmRom */
typedef boolean PduR_UpIfOfMmRomType;

/**   \brief  value based type definition for PduR_DirectionOfRmDestRom */
typedef uint8 PduR_DirectionOfRmDestRomType;

/**   \brief  value based type definition for PduR_RmGDestRomIdxOfRmDestRom */
typedef uint8 PduR_RmGDestRomIdxOfRmDestRomType;

/**   \brief  value based type definition for PduR_RmSrcRomIdxOfRmDestRom */
typedef uint8 PduR_RmSrcRomIdxOfRmDestRomType;

/**   \brief  value based type definition for PduR_RoutingTypeOfRmDestRom */
typedef uint8 PduR_RoutingTypeOfRmDestRomType;

/**   \brief  value based type definition for PduR_DestHndOfRmGDestRom */
typedef uint8 PduR_DestHndOfRmGDestRomType;

/**   \brief  value based type definition for PduR_MmRomIdxOfRmGDestRom */
typedef uint8 PduR_MmRomIdxOfRmGDestRomType;

/**   \brief  value based type definition for PduR_PduRDestPduProcessingOfRmGDestRom */
typedef uint8 PduR_PduRDestPduProcessingOfRmGDestRomType;

/**   \brief  value based type definition for PduR_RmDestRomIdxOfRmGDestRom */
typedef uint8 PduR_RmDestRomIdxOfRmGDestRomType;

/**   \brief  value based type definition for PduR_RmDestRomUsedOfRmGDestRom */
typedef boolean PduR_RmDestRomUsedOfRmGDestRomType;

/**   \brief  value based type definition for PduR_MmRomIdxOfRmSrcRom */
typedef uint8 PduR_MmRomIdxOfRmSrcRomType;

/**   \brief  value based type definition for PduR_RmDestRomEndIdxOfRmSrcRom */
typedef uint8 PduR_RmDestRomEndIdxOfRmSrcRomType;

/**   \brief  value based type definition for PduR_RmDestRomLengthOfRmSrcRom */
typedef uint8 PduR_RmDestRomLengthOfRmSrcRomType;

/**   \brief  value based type definition for PduR_RmDestRomStartIdxOfRmSrcRom */
typedef uint8 PduR_RmDestRomStartIdxOfRmSrcRomType;

/**   \brief  value based type definition for PduR_RmSrcRomIdxOfRxIf2Dest */
typedef uint8 PduR_RmSrcRomIdxOfRxIf2DestType;

/**   \brief  value based type definition for PduR_SizeOfIfRoutingStateTable */
typedef uint8 PduR_SizeOfIfRoutingStateTableType;

/**   \brief  value based type definition for PduR_SizeOfMmRom */
typedef uint8 PduR_SizeOfMmRomType;

/**   \brief  value based type definition for PduR_SizeOfRmDestRom */
typedef uint8 PduR_SizeOfRmDestRomType;

/**   \brief  value based type definition for PduR_SizeOfRmGDestRom */
typedef uint8 PduR_SizeOfRmGDestRomType;

/**   \brief  value based type definition for PduR_SizeOfRmSrcRom */
typedef uint8 PduR_SizeOfRmSrcRomType;

/**   \brief  value based type definition for PduR_SizeOfRmTransmitFctPtr */
typedef uint8 PduR_SizeOfRmTransmitFctPtrType;

/**   \brief  value based type definition for PduR_SizeOfRxIf2Dest */
typedef uint8 PduR_SizeOfRxIf2DestType;

/**   \brief  value based type definition for PduR_SizeOfTx2Lo */
typedef uint8 PduR_SizeOfTx2LoType;

/**   \brief  value based type definition for PduR_SizeOfTxIf2Up */
typedef uint8 PduR_SizeOfTxIf2UpType;

/**   \brief  value based type definition for PduR_RmSrcRomIdxOfTx2Lo */
typedef uint8 PduR_RmSrcRomIdxOfTx2LoType;

/**   \brief  value based type definition for PduR_RmSrcRomUsedOfTx2Lo */
typedef boolean PduR_RmSrcRomUsedOfTx2LoType;

/**   \brief  value based type definition for PduR_RmTransmitFctPtrIdxOfTx2Lo */
typedef uint8 PduR_RmTransmitFctPtrIdxOfTx2LoType;

/**   \brief  value based type definition for PduR_RmGDestRomIdxOfTxIf2Up */
typedef uint8 PduR_RmGDestRomIdxOfTxIf2UpType;

/** 
  \}
*/ 


/**********************************************************************************************************************
  CONFIGURATION CLASS: LINK
  SECTION: GLOBAL SIMPLE DATA TYPES AND STRUCTURES
**********************************************************************************************************************/

#if(PDUR_RMSRCROM == STD_ON)
typedef P2FUNC(Std_ReturnType, PDUR_APPL_CODE, PduR_RmTransmitFctPtrType) (PduR_RmSrcRomIterType, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA));
#endif
#if(PDUR_RMDESTROM == STD_ON)
typedef P2FUNC(void, PDUR_APPL_CODE, PduR_RmIfRxIndicationType) (PduR_RmDestRomIterType, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA));
#endif

#if(PDUR_FMFIFORAM == STD_ON)
typedef P2FUNC(BufReq_ReturnType, PDUR_APPL_CODE, PduR_StartOfReceptionFifoSmFctPtrType) (PduR_RmSrcRomIterType, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA), PduLengthType, P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA));
typedef P2FUNC(BufReq_ReturnType, PDUR_APPL_CODE, PduR_CopyRxDataFifoSmFctPtrType) (PduR_RmSrcRomIterType, PduLengthType, SduDataPtrType, P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA));
typedef P2FUNC(void, PDUR_APPL_CODE, PduR_TpRxIndicationFifoSmFctPtrType) (PduR_RmSrcRomIterType, Std_ReturnType);
typedef P2FUNC(void, PDUR_APPL_CODE, PduR_TpCancelReceiveFctPtrType) (PduR_RmSrcRomIterType);

typedef P2FUNC(BufReq_ReturnType, PDUR_APPL_CODE, PduR_CopyTxDataFifoSmFctPtrType) (PduR_RmGDestRomIterType, PduLengthType, SduDataPtrType, P2CONST(RetryInfoType, AUTOMATIC, PDUR_APPL_DATA), P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA));
typedef P2FUNC(Std_ReturnType, PDUR_APPL_CODE, PduR_TpTriggerTransmitFctPtrType) (PduR_RmDestRomIterType);
typedef P2FUNC(void, PDUR_APPL_CODE, PduR_TpTxConfirmationFifoSmFctPtrType) (PduR_RmGDestRomIterType, Std_ReturnType);
typedef P2FUNC(Std_ReturnType, PDUR_APPL_CODE, PduR_TpCancelTransmitFctPtrType)(PduR_RmDestRomIterType);
typedef P2FUNC(void, PDUR_CODE, PduR_TpDisableRoutingFctPtrType) (PduR_RmGDestRomIterType);

typedef P2FUNC(Std_ReturnType, PDUR_APPL_CODE, PduR_CheckReady2TransmitFctPtrType) (PduR_RmSrcRomIterType);

typedef P2FUNC(void, PDUR_APPL_CODE, PduR_FinishReceptionFctPtrType) (PduR_RmSrcRomIterType, Std_ReturnType);

typedef P2FUNC(void, PDUR_APPL_CODE, PduR_FinishTransmissionFctPtrType) (PduR_RmSrcRomIterType, Std_ReturnType);

typedef P2FUNC(void, PDUR_APPL_CODE, PduR_ActivateNextFctPtrType) (PduR_FmFifoElementRamIterType, Std_ReturnType);
#endif

#if(PDUR_FINISHREADFMSMTRANSITION  == STD_ON)
typedef P2FUNC(void, PDUR_APPL_CODE, PduR_FinishReadFctPtrType) (PduR_FmFifoElementRamIterType, Std_ReturnType);
#endif
#if (PDUR_FINISHWRITEFMSMTRANSITION  == STD_ON)
typedef P2FUNC(void, PDUR_APPL_CODE, PduR_FinishWriteFctPtrType) (PduR_FmFifoElementRamIterType, Std_ReturnType);
#endif
#if (PDUR_TPACTIVATEREADFIFOSMTRANSITION == STD_ON)
typedef P2FUNC(void, PDUR_APPL_CODE, PduR_ActivateReadFctPtrType) (PduR_FmFifoElementRamIterType);
#endif
#if (PDUR_TPACTIVATEWRITEFIFOSMTRANSITION == STD_ON)
typedef P2FUNC(void, PDUR_APPL_CODE, PduR_ActivateWriteFctPtrType) (PduR_FmFifoElementRamIterType);
#endif

#if (PDUR_FMFLUSHFIFOELEMENT == STD_ON)
typedef P2FUNC(void, PDUR_APPL_CODE, PduR_Fm_FlushFiFoElementPtrType) (PduR_FmFifoElementRamIterType);
#endif

#if(PDUR_SMDATAPLANEROM == STD_ON)
typedef uint8 PduR_FilterReturnType;
# define PDUR_FILTER_PASS  0u
# define PDUR_FILTER_BLOCK 1u

typedef uint32 PduR_SmSaType;
typedef uint32 PduR_SmTaType;

#define PDUR_SM_UNLEARNED_CONNECTION 0u
typedef P2FUNC(PduR_SmSaType, PDUR_CODE, PduR_Sm_LinearTaToSaCalculationStrategy_GetSaFctPtrType) (PduR_SmLinearTaToSaCalculationStrategyRomIterType, uint32);
typedef P2FUNC(void, PDUR_CODE, PduR_Sm_SrcFilterFctPtrType) (PduR_SmSrcRomIdxOfRmSrcRomType, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA));
typedef P2FUNC(PduR_FilterReturnType, PDUR_CODE, PduR_Sm_DestFilterFctPtrType) (PduR_SmGDestRomIdxOfRmGDestRomType, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA));
#endif

/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL COMPLEX DATA TYPES AND STRUCTURES
**********************************************************************************************************************/
/** 
  \defgroup  PduRPCStructTypes  PduR Struct Types (PRE_COMPILE)
  \brief  These type definitions are used for structured data representations.
  \{
*/ 
/**   \brief  type used in PduR_IfRoutingStateTable */
typedef struct sPduR_IfRoutingStateTableType
{
  PduR_NextState_For_Init_If_Routing_StateOfIfRoutingStateTableType NextState_For_Init_If_Routing_StateOfIfRoutingStateTable;
  PduR_NextState_For_Wait_For_RxIndicationOfIfRoutingStateTableType NextState_For_Wait_For_RxIndicationOfIfRoutingStateTable;
  PduR_NextState_For_Wait_For_TriggerTransmitOfIfRoutingStateTableType NextState_For_Wait_For_TriggerTransmitOfIfRoutingStateTable;
  PduR_NextState_For_Wait_For_TxConfirmationOfIfRoutingStateTableType NextState_For_Wait_For_TxConfirmationOfIfRoutingStateTable;
} PduR_IfRoutingStateTableType;

/**   \brief  type used in PduR_MmRom */
typedef struct sPduR_MmRomType
{
  PduR_MaskedBitsOfMmRomType MaskedBitsOfMmRom;  /**< contains bitcoded the boolean data of PduR_LoIfOfMmRom, PduR_UpIfOfMmRom */
  PduR_IfRxIndicationType UpIfRxIndicationFctPtrOfMmRom;  /**< Upper layer communication interface Rx indication function pointers. */
  PduR_TransmitFctPtrType LoIfTransmitFctPtrOfMmRom;  /**< Lower layer If transmit function pointers */
} PduR_MmRomType;

/**   \brief  type used in PduR_RmDestRom */
typedef struct sPduR_RmDestRomType
{
  PduR_RmGDestRomIdxOfRmDestRomType RmGDestRomIdxOfRmDestRom;  /**< the index of the 1:1 relation pointing to PduR_RmGDestRom */
} PduR_RmDestRomType;

/**   \brief  type used in PduR_RmGDestRom */
typedef struct sPduR_RmGDestRomType
{
  PduR_PduRDestPduProcessingOfRmGDestRomType PduRDestPduProcessingOfRmGDestRom;  /**< Is Processing Type of destination PDU. */
  PduR_RmDestRomIdxOfRmGDestRomType RmDestRomIdxOfRmGDestRom;  /**< the index of the 0:1 relation pointing to PduR_RmDestRom */
} PduR_RmGDestRomType;

/**   \brief  type used in PduR_RmSrcRom */
typedef struct sPduR_RmSrcRomType
{
  PduR_MmRomIdxOfRmSrcRomType MmRomIdxOfRmSrcRom;  /**< the index of the 1:1 relation pointing to PduR_MmRom */
  PduR_RmDestRomLengthOfRmSrcRomType RmDestRomLengthOfRmSrcRom;  /**< the number of relations pointing to PduR_RmDestRom */
} PduR_RmSrcRomType;

/**   \brief  type used in PduR_RxIf2Dest */
typedef struct sPduR_RxIf2DestType
{
  uint8 PduR_RxIf2DestNeverUsed;  /**< dummy entry for the structure in the configuration variant precompile which is not used by the code. */
} PduR_RxIf2DestType;

/**   \brief  type used in PduR_Tx2Lo */
typedef struct sPduR_Tx2LoType
{
  uint8 PduR_Tx2LoNeverUsed;  /**< dummy entry for the structure in the configuration variant precompile which is not used by the code. */
} PduR_Tx2LoType;

/**   \brief  type used in PduR_TxIf2Up */
typedef struct sPduR_TxIf2UpType
{
  uint8 PduR_TxIf2UpNeverUsed;  /**< dummy entry for the structure in the configuration variant precompile which is not used by the code. */
} PduR_TxIf2UpType;

/** 
  \}
*/ 

/** 
  \defgroup  PduRPCRootPointerTypes  PduR Root Pointer Types (PRE_COMPILE)
  \brief  These type definitions are used to point from the config root to symbol instances.
  \{
*/ 
/**   \brief  type used to point to PduR_IfRoutingStateTable */
typedef P2CONST(PduR_IfRoutingStateTableType, TYPEDEF, PDUR_CONST) PduR_IfRoutingStateTablePtrType;

/**   \brief  type used to point to PduR_Initialized */
typedef P2VAR(PduR_InitializedType, TYPEDEF, PDUR_VAR_ZERO_INIT) PduR_InitializedPtrType;

/**   \brief  type used to point to PduR_MmRom */
typedef P2CONST(PduR_MmRomType, TYPEDEF, PDUR_CONST) PduR_MmRomPtrType;

/**   \brief  type used to point to PduR_RmDestRom */
typedef P2CONST(PduR_RmDestRomType, TYPEDEF, PDUR_CONST) PduR_RmDestRomPtrType;

/**   \brief  type used to point to PduR_RmGDestRom */
typedef P2CONST(PduR_RmGDestRomType, TYPEDEF, PDUR_CONST) PduR_RmGDestRomPtrType;

/**   \brief  type used to point to PduR_RmSrcRom */
typedef P2CONST(PduR_RmSrcRomType, TYPEDEF, PDUR_CONST) PduR_RmSrcRomPtrType;

/**   \brief  type used to point to PduR_RmTransmitFctPtr */
typedef P2CONST(PduR_RmTransmitFctPtrType, TYPEDEF, PDUR_CONST) PduR_RmTransmitFctPtrPtrType;

/**   \brief  type used to point to PduR_RxIf2Dest */
typedef P2CONST(PduR_RxIf2DestType, TYPEDEF, PDUR_CONST) PduR_RxIf2DestPtrType;

/**   \brief  type used to point to PduR_Tx2Lo */
typedef P2CONST(PduR_Tx2LoType, TYPEDEF, PDUR_CONST) PduR_Tx2LoPtrType;

/**   \brief  type used to point to PduR_TxIf2Up */
typedef P2CONST(PduR_TxIf2UpType, TYPEDEF, PDUR_CONST) PduR_TxIf2UpPtrType;

/** 
  \}
*/ 

/** 
  \defgroup  PduRPCRootValueTypes  PduR Root Value Types (PRE_COMPILE)
  \brief  These type definitions are used for value representations in root arrays.
  \{
*/ 
/**   \brief  type used in PduR_PCConfig */
typedef struct sPduR_PCConfigType
{
  uint8 PduR_PCConfigNeverUsed;  /**< dummy entry for the structure in the configuration variant precompile which is not used by the code. */
} PduR_PCConfigType;

typedef PduR_PCConfigType PduR_PBConfigType;  /**< A structure type is present for data in each configuration class. This typedef redefines the probably different name to the specified one. */

/** 
  \}
*/ 


/**********************************************************************************************************************
  CONFIGURATION CLASS: LINK
  SECTION: GLOBAL COMPLEX DATA TYPES AND STRUCTURES
**********************************************************************************************************************/


/**********************************************************************************************************************
 * GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL DATA PROTOTYPES
**********************************************************************************************************************/
/**********************************************************************************************************************
  PduR_IfRoutingStateTable
**********************************************************************************************************************/
/** 
  \var    PduR_IfRoutingStateTable
  \brief  Contains state transition for Communication Interface routings
  \details
  Element                                   Description
  NextState_For_Init_If_Routing_State   
  NextState_For_Wait_For_RxIndication   
  NextState_For_Wait_For_TriggerTransmit
  NextState_For_Wait_For_TxConfirmation 
*/ 
#define PDUR_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
extern CONST(PduR_IfRoutingStateTableType, PDUR_CONST) PduR_IfRoutingStateTable[4];
#define PDUR_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  PduR_MmRom
**********************************************************************************************************************/
/** 
  \var    PduR_MmRom
  \brief  Module manager: Contains all function pointers of the bordering modules.
  \details
  Element                   Description
  MaskedBits                contains bitcoded the boolean data of PduR_LoIfOfMmRom, PduR_UpIfOfMmRom
  UpIfRxIndicationFctPtr    Upper layer communication interface Rx indication function pointers.
  LoIfTransmitFctPtr        Lower layer If transmit function pointers
*/ 
#define PDUR_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
extern CONST(PduR_MmRomType, PDUR_CONST) PduR_MmRom[2];
#define PDUR_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  PduR_RmDestRom
**********************************************************************************************************************/
/** 
  \var    PduR_RmDestRom
  \brief  PduR RoutiongPathManager destPdu Table
  \details
  Element          Description
  RmGDestRomIdx    the index of the 1:1 relation pointing to PduR_RmGDestRom
*/ 
#define PDUR_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
extern CONST(PduR_RmDestRomType, PDUR_CONST) PduR_RmDestRom[2];
#define PDUR_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  PduR_RmGDestRom
**********************************************************************************************************************/
/** 
  \var    PduR_RmGDestRom
  \brief  PduR RoutiongPathManager global destPdu Table
  \details
  Element                  Description
  PduRDestPduProcessing    Is Processing Type of destination PDU.
  RmDestRomIdx             the index of the 0:1 relation pointing to PduR_RmDestRom
*/ 
#define PDUR_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
extern CONST(PduR_RmGDestRomType, PDUR_CONST) PduR_RmGDestRom[2];
#define PDUR_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  PduR_RmSrcRom
**********************************************************************************************************************/
/** 
  \var    PduR_RmSrcRom
  \brief  PduR RoutiongManager SrcPdu Table
  \details
  Element            Description
  MmRomIdx           the index of the 1:1 relation pointing to PduR_MmRom
  RmDestRomLength    the number of relations pointing to PduR_RmDestRom
*/ 
#define PDUR_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
extern CONST(PduR_RmSrcRomType, PDUR_CONST) PduR_RmSrcRom[2];
#define PDUR_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  PduR_RmTransmitFctPtr
**********************************************************************************************************************/
/** 
  \var    PduR_RmTransmitFctPtr
  \brief  Internal routing manager Transmit functions.
*/ 
#define PDUR_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
extern CONST(PduR_RmTransmitFctPtrType, PDUR_CONST) PduR_RmTransmitFctPtr[1];
#define PDUR_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  PduR_Initialized
**********************************************************************************************************************/
/** 
  \var    PduR_Initialized
  \brief  Initialization state of PduR. TRUE, if PduR_Init() has been called, else FALSE
*/ 
#define PDUR_START_SEC_VAR_ZERO_INIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
extern VAR(PduR_InitializedType, PDUR_VAR_ZERO_INIT) PduR_Initialized;
#define PDUR_STOP_SEC_VAR_ZERO_INIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */


/**********************************************************************************************************************
  CONFIGURATION CLASS: LINK
  SECTION: GLOBAL DATA PROTOTYPES
**********************************************************************************************************************/


#define PDUR_START_SEC_VAR_ZERO_INIT_UNSPECIFIED
#include "MemMap.h"    /* PRQA S 5087 */        /* MD_MSR_19.1 */

#if(PDUR_USE_INIT_POINTER == STD_ON)
extern P2CONST(PduR_PBConfigType, PDUR_VAR_ZERO_INIT, PDUR_PBCFG) PduR_ConfigDataPtr;
#endif

#define PDUR_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED
#include "MemMap.h"    /* PRQA S 5087 */        /* MD_MSR_19.1 */

/**********************************************************************************************************************
 * GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL FUNCTION PROTOTYPES
**********************************************************************************************************************/

/**********************************************************************************************************************
  CONFIGURATION CLASS: LINK
  SECTION: GLOBAL FUNCTION PROTOTYPES
**********************************************************************************************************************/


/**********************************************************************************************************************
 * LOCAL GEN FUNCTION PROTOTYPES
 *********************************************************************************************************************/
# ifdef PDUR_SOURCE
#if(PDUR_RECEPTIONINDICATIONQUEUE == STD_ON)
/**********************************************************************************************************************
 * PduR_ReceptionIndicationQueueInit
 *********************************************************************************************************************/
/*! \brief   Initializes the queue parameters
 *  \details -
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_ReceptionIndicationQueueInit(void);
#endif

#if(PDUR_RECEPTIONINDICATIONQUEUE == STD_ON)
/**********************************************************************************************************************
 * PduR_IsReceptionIndicationQueueFull
 *********************************************************************************************************************/
/*! \brief   Checks if the queue is full
 *  \details -
 *  \return  TRUE  - If the queue is full
 *            FALSE - If the queue is not full
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_IsReceptionIndicationQueueFull(void);
#endif

#if(PDUR_RECEPTIONINDICATIONQUEUE == STD_ON)
/**********************************************************************************************************************
 * PduR_IsReceptionIndicationQueueEmpty
 *********************************************************************************************************************/
/*! \brief   Checks if the queue is empty
 *  \details -
 *  \return  TRUE  - If the queue is empty
 *            FALSE - If the queue is not empty
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_IsReceptionIndicationQueueEmpty(void);
#endif

#if(PDUR_RECEPTIONINDICATIONQUEUE == STD_ON)
/**********************************************************************************************************************
 * PduR_ReceptionIndicationQueueWriteIdxIncrement
 *********************************************************************************************************************/
/*! \brief   Increments the queue write index
 *  \details -
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_ReceptionIndicationQueueWriteIdxIncrement(void);
#endif

#if(PDUR_RECEPTIONINDICATIONQUEUE == STD_ON)
/**********************************************************************************************************************
 * PduR_ReceptionIndicationQueueReadIdxIncrement
 *********************************************************************************************************************/
/*! \brief   Increments the queue read index
 *  \details -
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_ReceptionIndicationQueueReadIdxIncrement(void);
#endif

#if(PDUR_TRANSMITREQUESTQUEUE == STD_ON)
/**********************************************************************************************************************
 * PduR_TransmitRequestQueueInit
 *********************************************************************************************************************/
/*! \brief   Initializes the queue parameters
 *  \details -
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_TransmitRequestQueueInit(void);
#endif

#if(PDUR_TRANSMITREQUESTQUEUE == STD_ON)
/**********************************************************************************************************************
 * PduR_IsTransmitRequestQueueFull
 *********************************************************************************************************************/
/*! \brief   Checks if the queue is full
 *  \details -
 *  \return  TRUE  - If the queue is full
 *            FALSE - If the queue is not full
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_IsTransmitRequestQueueFull(void);
#endif

#if(PDUR_TRANSMITREQUESTQUEUE == STD_ON)
/**********************************************************************************************************************
 * PduR_IsTransmitRequestQueueEmpty
 *********************************************************************************************************************/
/*! \brief   Checks if the queue is empty
 *  \details -
 *  \return  TRUE  - If the queue is empty
 *            FALSE - If the queue is not empty
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_IsTransmitRequestQueueEmpty(void);
#endif

#if(PDUR_TRANSMITREQUESTQUEUE == STD_ON)
/**********************************************************************************************************************
 * PduR_TransmitRequestQueueWriteIdxIncrement
 *********************************************************************************************************************/
/*! \brief   Increments the queue write index
 *  \details -
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_TransmitRequestQueueWriteIdxIncrement(void);
#endif

#if(PDUR_TRANSMITREQUESTQUEUE == STD_ON)
/**********************************************************************************************************************
 * PduR_TransmitRequestQueueReadIdxIncrement
 *********************************************************************************************************************/
/*! \brief   Increments the queue read index
 *  \details -
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_TransmitRequestQueueReadIdxIncrement(void);
#endif


# endif

/**********************************************************************************************************************
 * LOCAL GEN FUNCTIONS
 *********************************************************************************************************************/
# ifdef PDUR_SOURCE
#if(PDUR_RECEPTIONINDICATIONQUEUE == STD_ON)
/**********************************************************************************************************************
 * PduR_ReceptionIndicationQueueInit
 *********************************************************************************************************************/
/*!
 * \internal
 * - Initialize read and write index
 * \endinternal
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_ReceptionIndicationQueueInit(void)
{
  PduR_SetReceptionIndicationQueueReadIdx(0); /* SBSW_PDUR_CSL_VAR_ACCESS */
  PduR_SetReceptionIndicationQueueWriteIdx(0); /* SBSW_PDUR_CSL_VAR_ACCESS */
}
#endif

#if(PDUR_RECEPTIONINDICATIONQUEUE == STD_ON)
/**********************************************************************************************************************
 * PduR_IsReceptionIndicationQueueFull
 *********************************************************************************************************************/
/*!
 * \internal
 * - return true if the queue is full
 * \endinternal
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_IsReceptionIndicationQueueFull(void)
{
  boolean ret = FALSE;
  if(PduR_GetReceptionIndicationQueueReadIdx() == ((PduR_GetReceptionIndicationQueueWriteIdx() + 1) % PduR_GetSizeOfReceptionIndicationQueue()))
  {
    ret = TRUE;
  }
  return ret;
}
#endif

#if(PDUR_RECEPTIONINDICATIONQUEUE == STD_ON)
/**********************************************************************************************************************
 * PduR_IsReceptionIndicationQueueEmpty
 *********************************************************************************************************************/
/*!
 * \internal
 * - return true if the queue is empty
 * \endinternal
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_IsReceptionIndicationQueueEmpty(void)
{
  boolean ret = FALSE;
  if(PduR_GetReceptionIndicationQueueReadIdx() == PduR_GetReceptionIndicationQueueWriteIdx())
  {
    ret = TRUE;
  }
  return ret;
}
#endif

#if(PDUR_RECEPTIONINDICATIONQUEUE == STD_ON)
/**********************************************************************************************************************
 * PduR_ReceptionIndicationQueueWriteIdxIncrement
 *********************************************************************************************************************/
/*!
 * \internal
 * - increment the write index
 * \endinternal
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_ReceptionIndicationQueueWriteIdxIncrement(void)
{
  PduR_SetReceptionIndicationQueueWriteIdx((PduR_GetReceptionIndicationQueueWriteIdx() + 1) % PduR_GetSizeOfReceptionIndicationQueue()); /* SBSW_PDUR_CSL_VAR_ACCESS */
}
#endif

#if(PDUR_RECEPTIONINDICATIONQUEUE == STD_ON)
/**********************************************************************************************************************
 * PduR_ReceptionIndicationQueueReadIdxIncrement
 *********************************************************************************************************************/
/*!
 * \internal
 * - increment the read index
 * \endinternal
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_ReceptionIndicationQueueReadIdxIncrement(void)
{
  PduR_SetReceptionIndicationQueueReadIdx((PduR_GetReceptionIndicationQueueReadIdx() + 1) % PduR_GetSizeOfReceptionIndicationQueue()); /* SBSW_PDUR_CSL_VAR_ACCESS */
}
#endif

#if(PDUR_TRANSMITREQUESTQUEUE == STD_ON)
/**********************************************************************************************************************
 * PduR_TransmitRequestQueueInit
 *********************************************************************************************************************/
/*!
 * \internal
 * - Initialize read and write index
 * \endinternal
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_TransmitRequestQueueInit(void)
{
  PduR_SetTransmitRequestQueueReadIdx(0); /* SBSW_PDUR_CSL_VAR_ACCESS */
  PduR_SetTransmitRequestQueueWriteIdx(0); /* SBSW_PDUR_CSL_VAR_ACCESS */
}
#endif

#if(PDUR_TRANSMITREQUESTQUEUE == STD_ON)
/**********************************************************************************************************************
 * PduR_IsTransmitRequestQueueFull
 *********************************************************************************************************************/
/*!
 * \internal
 * - return true if the queue is full
 * \endinternal
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_IsTransmitRequestQueueFull(void)
{
  boolean ret = FALSE;
  if(PduR_GetTransmitRequestQueueReadIdx() == ((PduR_GetTransmitRequestQueueWriteIdx() + 1) % PduR_GetSizeOfTransmitRequestQueue()))
  {
    ret = TRUE;
  }
  return ret;
}
#endif

#if(PDUR_TRANSMITREQUESTQUEUE == STD_ON)
/**********************************************************************************************************************
 * PduR_IsTransmitRequestQueueEmpty
 *********************************************************************************************************************/
/*!
 * \internal
 * - return true if the queue is empty
 * \endinternal
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_IsTransmitRequestQueueEmpty(void)
{
  boolean ret = FALSE;
  if(PduR_GetTransmitRequestQueueReadIdx() == PduR_GetTransmitRequestQueueWriteIdx())
  {
    ret = TRUE;
  }
  return ret;
}
#endif

#if(PDUR_TRANSMITREQUESTQUEUE == STD_ON)
/**********************************************************************************************************************
 * PduR_TransmitRequestQueueWriteIdxIncrement
 *********************************************************************************************************************/
/*!
 * \internal
 * - increment the write index
 * \endinternal
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_TransmitRequestQueueWriteIdxIncrement(void)
{
  PduR_SetTransmitRequestQueueWriteIdx((PduR_GetTransmitRequestQueueWriteIdx() + 1) % PduR_GetSizeOfTransmitRequestQueue()); /* SBSW_PDUR_CSL_VAR_ACCESS */
}
#endif

#if(PDUR_TRANSMITREQUESTQUEUE == STD_ON)
/**********************************************************************************************************************
 * PduR_TransmitRequestQueueReadIdxIncrement
 *********************************************************************************************************************/
/*!
 * \internal
 * - increment the read index
 * \endinternal
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_TransmitRequestQueueReadIdxIncrement(void)
{
  PduR_SetTransmitRequestQueueReadIdx((PduR_GetTransmitRequestQueueReadIdx() + 1) % PduR_GetSizeOfTransmitRequestQueue()); /* SBSW_PDUR_CSL_VAR_ACCESS */
}
#endif


# endif

#endif  /* PDUR_LCFG_H */
/**********************************************************************************************************************
 * END OF FILE: PduR_Lcfg.h
 *********************************************************************************************************************/

