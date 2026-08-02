/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2022 by Vector Informatik GmbH.                                                  All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/*!        \file  SoAd_Priv.h
 *        \brief  Socket Adaptor private header file
 *
 *      \details  Vector static private header file for AUTOSAR Socket Adaptor module. This header file contains
 *                module internal declarations.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *********************************************************************************************************************/

#if !defined(SOAD_PRIV_H)
# define SOAD_PRIV_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

# include "SoAd_Types.h"
# include "SoAd_Lcfg.h"
# include "SoAd_PBcfg.h"
# include "SchM_SoAd.h"

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

# define SOAD_BEGIN_CRITICAL_SECTION()              SchM_Enter_SoAd_SOAD_EXCLUSIVE_AREA_0()
# define SOAD_END_CRITICAL_SECTION()                SchM_Exit_SoAd_SOAD_EXCLUSIVE_AREA_0()

# define SOAD_BEGIN_CRITICAL_SECTION_1()            SchM_Enter_SoAd_SOAD_EXCLUSIVE_AREA_1()
# define SOAD_END_CRITICAL_SECTION_1()              SchM_Exit_SoAd_SOAD_EXCLUSIVE_AREA_1()

# if ( SOAD_MULTI_PARTITION == STD_ON ) /* COV_SOAD_QM_FEATURE_MULTI_PARTITION */
#  define SOAD_BEGIN_CRITICAL_SECTION_MEASUREMENT() SchM_Enter_SoAd_SOAD_EXCLUSIVE_AREA_MULTI_PARTITION()
#  define SOAD_END_CRITICAL_SECTION_MEASUREMENT()   SchM_Exit_SoAd_SOAD_EXCLUSIVE_AREA_MULTI_PARTITION()
# else
#  define SOAD_BEGIN_CRITICAL_SECTION_MEASUREMENT() SchM_Enter_SoAd_SOAD_EXCLUSIVE_AREA_0()
#  define SOAD_END_CRITICAL_SECTION_MEASUREMENT()   SchM_Exit_SoAd_SOAD_EXCLUSIVE_AREA_0()
# endif /* SOAD_MULTI_PARTITION == STD_ON */

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

# define SOAD_START_SEC_CODE
# include "SoAd_MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_Rule20.10_0342 */ /*lint !e451 */

/**********************************************************************************************************************
 *  SoAd_MainFunctionInstanceRx()
 *********************************************************************************************************************/
/*! \brief       Schedules the asynchronous reception handling.
 *  \details     -
 *  \param[in]   InstMapIdx   Instance Map index.
 *                            [range: InstMapIdx < SoAd_GetSizeOfInstanceMap()]
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(void, SOAD_CODE) SoAd_MainFunctionInstanceRx(SoAd_SizeOfInstanceMapType InstMapIdx);

/**********************************************************************************************************************
 *  SoAd_MainFunctionInstanceState()
 *********************************************************************************************************************/
/*! \brief       Schedules state handling.
 *  \details     -
 *  \param[in]   InstMapIdx   Instance Map index.
 *                            [range: InstMapIdx < SoAd_GetSizeOfInstanceMap()]
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(void, SOAD_CODE) SoAd_MainFunctionInstanceState(SoAd_SizeOfInstanceMapType InstMapIdx);

/**********************************************************************************************************************
 *  SoAd_MainFunctionInstanceTx()
 *********************************************************************************************************************/
/*! \brief       Schedules the asynchronous transmission handling.
 *  \details     -
 *  \param[in]   InstMapIdx   Instance Map index.
 *                            [range: InstMapIdx < SoAd_GetSizeOfInstanceMap()]
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(void, SOAD_CODE) SoAd_MainFunctionInstanceTx(SoAd_SizeOfInstanceMapType InstMapIdx);

# if ( SOAD_SINGLE_MAIN_FUNCTION == STD_ON )
/**********************************************************************************************************************
 *  SoAd_MainFunctionInstance()
 *********************************************************************************************************************/
/*! \brief       Schedules the asynchronous reception handling, the state handling and the asynchronous transmission
 *               handling.
 *  \details     -
 *  \param[in]   InstMapIdx   Instance Map index.
 *                            [range: InstMapIdx < SoAd_GetSizeOfInstanceMap()]
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(void, SOAD_CODE) SoAd_MainFunctionInstance(SoAd_SizeOfInstanceMapType InstMapIdx);
# endif /* SOAD_SINGLE_MAIN_FUNCTION == STD_ON */

# define SOAD_STOP_SEC_CODE
# include "SoAd_MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_Rule20.10_0342 */ /*lint !e451 */

#endif /* !defined(SOAD_PRIV_H) */

/*!
 * \exclusivearea SOAD_EXCLUSIVE_AREA_0
 * Ensures consistency while read, modify and write global variables which are accessed in multiple context (ISR/TASK).
 * \protects SoAd_EventQueueFlag, SoAd_EventQueueMgmt, SoAd_BestMatchSoConIdxList, SoAd_RouteGrpSoConDyn, SoAd_RxMgt,
 * SoAd_SocketDyn, SoAd_SoConDyn, SoAd_RcvRemAddr, SoAd_LocalAddrDyn, SoAd_TimeoutListUdpAlive, SoAd_TimeoutListMgmt,
 * SoAd_TimeoutListUdpAliveMap, SoAd_TimeoutListUdpAlive, SoAd_TimeoutListNPduUdpTxMap, SoAd_TimeoutListNPduUdpTx,
 * SoAd_TxMgt, SoAd_PduRouteDyn, SoAd_TcpTxQueueData, SoAd_TcpTxQueueMgt, SoAd_NPduUdpTxDyn, SoAd_NPduUdpTxBuffer,
 * SoAd_IpFragMgt, SoAd_IpFragBufConfigDyn, SoAd_TriggerBufConfigDyn, SoAd_MetaDataRxBufConfigDyn,
 * SoAd_MeasurementCounter
 * \usedin SoAd_EventQueue_AddElement, SoAd_EventQueue_GetNextElement, SoAd_RouteGrp_SetSpecificRoutingGroupState,
 * SoAd_Rx_GetSoConIdxByBestMatchAlg, SoAd_RxIfMetaDataBuf_Reserve, SoAd_RxIfMetaDataBuf_Release,
 * SoAd_RxTp_CancelReceive, SoAd_SoCon_TcpAcceptedGetSoConIdx, SoAd_SoCon_EventUdpClose,
 * SoAd_SoCon_EventTcpFinReceived, SoAd_SoCon_CheckForActiveOrPendingTransmit, SoAd_SoCon_SetRemoteAddrCheckAndSet,
 * SoAd_SoCon_ResetCloseMode, SoAd_SoCon_SetRemoteAddr, SoAd_SoCon_SetUniqueRemoteAddr,
 * SoAd_SoCon_UpdateUdpAliveTimeout, SoAd_SoCon_RequestOpenSoCon, SoAd_SoCon_RequestCloseSoCon,
 * SoAd_SoCon_OpenSoConOnReception, SoAd_SoCon_HandleUdpAliveTimeout, SoAd_SoCon_CheckAndGetRcvRemoteAddr,
 * SoAd_SoCon_LocalIpAddrAssignmentChg, SoAd_SoCon_UpdateRcvRemoteAddress, SoAd_SoCon_AssignSocketUdp,
 * SoAd_SoCon_OpenSocketTcpClientConnect, SoAd_SoCon_OpenSocketTcpServerListen, SoAd_SoCon_CloseSocketTcp,
 * SoAd_SoCon_CloseSocketTcpListen, SoAd_SoCon_TcpConnected, SoAd_SoCon_ReconnectOnRemoteAddrChg,
 * SoAd_SoCon_HandleReleaseRemAddr, SoAd_SoCon_ReleaseRemoteAddr, SoAd_TimeoutList_SetElement,
 * SoAd_TimeoutList_GetCurrentTimeout, SoAd_TimeoutList_CheckElements, SoAd_TimeoutList_RemoveElement,
 * SoAd_TxIf_CheckAndClearPendingTxConfirmation, SoAd_TxIf_TcpTransmit, SoAd_TxIf_UdpTransmitPdu,
 * SoAd_TxIf_TcpTxConfirmation, SoAd_TxTp_TransmitPdu, SoAd_Tx_TpCancelTransmit, SoAd_TxTp_CancelTransmit,
 * SoAd_TxTp_TransmitPduRouteDest, SoAd_TxTcpQueue_Clear, SoAd_TxTcpQueue_ReserveNextElement,
 * SoAd_TxTcpQueue_SetElement, SoAd_TxTcpQueue_TxConfirmation, SoAd_TxNPduUdp_QueueAddOrUpdateElement,
 * SoAd_TxNPduUdp_QueuePrepareTransmitSegment, SoAd_TxNPduUdp_QueueFinishTransmitSegment,
 * SoAd_TxNPduUdp_QueueTxConfirmation, SoAd_TxNPduUdp_BufferAddElement, SoAd_TxNPduUdp_BufferSend,
 * SoAd_TxIpFragBuf_Reserve, SoAd_TxIpFragBuf_Set, SoAd_TxIpFragBuf_Get, SoAd_TxIpFragBuf_Release,
 * SoAd_TxIfTriggerBuf_Reserve, SoAd_TxIfTriggerBuf_Release, SoAd_Anomaly_GetAndResetMeasurementData,
 * SoAd_Anomaly_IncCtrValue
 * \exclude All other functions provided by SoAd.
 * \length MEDIUM More than a few statements with a constant maximum runtime and a low call-tree.
 * \endexclusivearea
 *
 * \exclusivearea SOAD_EXCLUSIVE_AREA_1
 * Ensures that transmission requests are not rejected when a transmission in main function context is interrupted by a
 * transmission request from a different context.
 * \protects Transmission path in main function context for nPdu and routing group (data consistency is already ensured
 * by SOAD_EXCLUSIVE_AREA_0).
 * \usedin SoAd_TxNPduUdp_HandleTransmission, SoAd_RouteGrp_HandleIfTransmit
 * \exclude All other functions provided by SoAd.
 * \length LONG Calls to other BSW modules with an undefined maximum runtime.
 * \endexclusivearea
 *
 * \exclusivearea SOAD_EXCLUSIVE_AREA_MULTIINSTANCE
 * Ensures consistency while read, modify and write global variables which are accessed by multiple SoAd instances.
 * \protects SoAd_MeasurementCounter
 * \usedin SoAd_Anomaly_GetAndResetMeasurementData, SoAd_Anomaly_GetAndResetCtrValues, SoAd_Anomaly_IncCtrValue
 * \exclude All other functions provided by SoAd.
 * \length SHORT Only a few statements with a constant maximum runtime.
 * \endexclusivearea
 */

/**********************************************************************************************************************
 *  END OF FILE: SoAd_Priv.h
 *********************************************************************************************************************/
